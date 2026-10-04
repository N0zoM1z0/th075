#!/usr/bin/env python3
"""Replay complete R143 derived RTTI exception families and source alternatives."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
CONFIDENCE = 'complete-vendor-derived-exception-family-rtti-weak-alternative-abi-provenance'
ACCEPTED = {'0x00640D38': ('??1bad_cast@@UAE@XZ', 11),
 '0x00640D74': ('??1bad_typeid@@UAE@XZ', 11),
 '0x00640DAF': ('??1__non_rtti_object@@UAE@XZ', 11)}
LEDGER_SIZES = {'0x00640D38': 11, '0x00640D74': 11, '0x00640DAF': 11}
AUXILIARIES = {'0x00640D07': ('??0bad_cast@@QAE@PBD@Z', 25),
 '0x00640D20': ('??0bad_cast@@QAE@ABV0@@Z', 24),
 '0x00640D43': ('??0bad_typeid@@QAE@PBD@Z', 25),
 '0x00640D5C': ('??0bad_typeid@@QAE@ABV0@@Z', 24),
 '0x00640D7F': ('??0__non_rtti_object@@QAE@PBD@Z', 24),
 '0x00640D97': ('??0__non_rtti_object@@QAE@ABV0@@Z', 24),
 '0x00640C5D': ('??0exception@@QAE@ABQBD@Z', 61),
 '0x00640CFA': ('?what@exception@@UBEPBDXZ', 13)}
LABELS = {}
ANCHORS = [('0x00640CE4', '??1exception@@UAE@XZ', 22, 442622, 'R142', 'library'),
 ('0x00640C9A', '??0exception@@QAE@ABV0@@Z', 74, 442622, 'R142', 'library'),
 ('0x00640620',
  '_strlen',
  139,
  2200788,
  'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG',
  'library'),
 ('0x00644331', '_malloc', 18, 816374, 'R120', 'library'),
 ('0x00641B80', '_strcpy', 7, 2186124, 'R116', 'library'),
 ('0x00640DF5', '??_Gbad_cast@@UAEPAXI@Z', 28, 442622, 'R038', 'compiler'),
 ('0x00640E11', '??_Gbad_typeid@@UAEPAXI@Z', 28, 442622, 'R038', 'compiler'),
 ('0x00640E2D', '??_G__non_rtti_object@@UAEPAXI@Z', 28, 442622, 'R038', 'compiler'),
 ('0x00640DBA', '??_Gexception@@UAEPAXI@Z', 28, 442622, 'R038', 'compiler'),
 ('0x00640E8F', '??_Gtype_info@@UAEPAXI@Z', 28, 462402, 'R038', 'compiler')]
STATE = {(442622, '??_7__non_rtti_object@@6B@', '0x00660ECC', 12),
 (442622, '??_7bad_cast@@6B@', '0x00660EB4', 12),
 (442622, '??_7bad_typeid@@6B@', '0x00660EC0', 12),
 (442622, '??_7exception@@6B@', '0x00660E94', 12),
 (442622, '??_C@_0BC@EOODALEL@Unknown?5exception?$AA@', '0x00660EA0', 18),
 (442622, '??_R0?AV__non_rtti_object@@@8', '0x0066FE98', 32),
 (442622, '??_R0?AVbad_cast@@@8', '0x0066FE64', 23),
 (442622, '??_R0?AVbad_typeid@@@8', '0x0066FE7C', 25),
 (442622, '??_R0?AVexception@@@8', '0x0066C1BC', 24),
 (442622, '??_R1A@?0A@A@__non_rtti_object@@8', '0x006677D0', 24),
 (442622, '??_R1A@?0A@A@bad_cast@@8', '0x00667740', 24),
 (442622, '??_R1A@?0A@A@bad_typeid@@8', '0x00667788', 24),
 (442622, '??_R1A@?0A@A@exception@@8', '0x006676FC', 24),
 (442622, '??_R2__non_rtti_object@@8', '0x006677E8', 13),
 (442622, '??_R2bad_cast@@8', '0x00667758', 9),
 (442622, '??_R2bad_typeid@@8', '0x006677A0', 9),
 (442622, '??_R2exception@@8', '0x00667714', 5),
 (442622, '??_R3__non_rtti_object@@8', '0x006677F8', 16),
 (442622, '??_R3bad_cast@@8', '0x00667764', 16),
 (442622, '??_R3bad_typeid@@8', '0x006677AC', 16),
 (442622, '??_R3exception@@8', '0x0066771C', 16),
 (442622, '??_R4__non_rtti_object@@6B@', '0x00667808', 20),
 (442622, '??_R4bad_cast@@6B@', '0x00667774', 20),
 (442622, '??_R4bad_typeid@@6B@', '0x006677BC', 20),
 (442622, '??_R4exception@@6B@', '0x0066772C', 20),
 (462402, '??_7type_info@@6B@', '0x00660ED8', 8),
 (462402, '??_R0?AVtype_info@@@8', '0x0066FEB8', 24),
 (462402, '??_R1A@?0A@A@type_info@@8', '0x0066781C', 24),
 (462402, '??_R2type_info@@8', '0x00667834', 5),
 (462402, '??_R3type_info@@8', '0x0066783C', 16),
 (462402, '??_R4type_info@@6B@', '0x0066784C', 20)}
LAYOUT_OBJECTS = [{'symbol': '_DerivedExceptionLayoutProbe',
  'offset': 0,
  'size': 32,
  'storage_span': 32,
  'values': [4, 12, 12, 12, 12, 12, 12, 12]}]
LAYOUT_HEADERS = {'crt/src/cruntime.h',
 'crt/src/cstddef',
 'crt/src/eh.h',
 'crt/src/exception',
 'crt/src/new',
 'crt/src/stddef.h',
 'crt/src/stdexcpt.h',
 'crt/src/typeinfo.h',
 'crt/src/use_ansi.h',
 'crt/src/xstddef',
 'crt/src/yvals.h'}
DERIVED_PROTOCOL = {'sdk_class_sizes': [12, 12, 12, 12],
 'vtable_address_point_offset': 4,
 'derived_vtable_complete_size': 12,
 'derived_base_array_complete_sizes': [9, 9, 13],
 'derived_descriptor_complete_sizes': [23, 25, 32],
 'constructor_callee_cleanup': 4,
 'destructor_exit': 'Tail jump directly to complete base exception destructor; no standalone RET',
 'non_rtti_destructor_stage': 'Writes bad_typeid vtable then tail-jumps to exception destructor',
 'weak_search_characteristics': 2,
 'private_source_status': 'stdexcpt.cpp is absent; full supplied COFF owners and actual SDK headers are '
                          'evidence',
 'name_status': 'Source roles supported by paired complete vtable/RTTI/constructors/compiler callbacks; '
                'original target names remain provisional',
 'runtime_unknowns': 'Original complete linker inputs/search decisions beyond supplied archive, current '
                     'cached RTTI state, object/message ownership, allocation and exception outcomes; no '
                     'complete original game owner inferred'}
FAMILY_GRAPH = [{'source_class': 'bad_cast',
  'destructor': '0x00640D38',
  'message_constructor': '0x00640D07',
  'copy_constructor': '0x00640D20',
  'compiler_deleting_callback': '0x00640DF5',
  'constructed_vtable_address_point': '0x00660EB8',
  'destructor_vtable_address_point': '0x00660EB8',
  'source_vtable_symbol': '??_7bad_cast@@6B@',
  'source_weak_symbol': '??_Ebad_cast@@UAEPAXI@Z',
  'source_fallback_symbol': '??_Gbad_cast@@UAEPAXI@Z',
  'source_destructor_symbol': '??1bad_cast@@UAE@XZ',
  'rtti_bases': ['bad_cast', 'exception']},
 {'source_class': 'bad_typeid',
  'destructor': '0x00640D74',
  'message_constructor': '0x00640D43',
  'copy_constructor': '0x00640D5C',
  'compiler_deleting_callback': '0x00640E11',
  'constructed_vtable_address_point': '0x00660EC4',
  'destructor_vtable_address_point': '0x00660EC4',
  'source_vtable_symbol': '??_7bad_typeid@@6B@',
  'source_weak_symbol': '??_Ebad_typeid@@UAEPAXI@Z',
  'source_fallback_symbol': '??_Gbad_typeid@@UAEPAXI@Z',
  'source_destructor_symbol': '??1bad_typeid@@UAE@XZ',
  'rtti_bases': ['bad_typeid', 'exception']},
 {'source_class': '__non_rtti_object',
  'destructor': '0x00640DAF',
  'message_constructor': '0x00640D7F',
  'copy_constructor': '0x00640D97',
  'compiler_deleting_callback': '0x00640E2D',
  'constructed_vtable_address_point': '0x00660ED0',
  'destructor_vtable_address_point': '0x00660EC4',
  'source_vtable_symbol': '??_7__non_rtti_object@@6B@',
  'source_weak_symbol': '??_E__non_rtti_object@@UAEPAXI@Z',
  'source_fallback_symbol': '??_G__non_rtti_object@@UAEPAXI@Z',
  'source_destructor_symbol': '??1__non_rtti_object@@UAE@XZ',
  'rtti_bases': ['__non_rtti_object', 'bad_typeid', 'exception']}]
SOURCE_WEAK_REFERENCES = [{'member_offset': 442622,
  'symbol': '??_Ebad_cast@@UAEPAXI@Z',
  'source_definition': {'symbol': '??_Ebad_cast@@UAEPAXI@Z',
                        'offset': 0,
                        'section': 0,
                        'type': 32,
                        'storage': 105},
  'symbol_index': 112,
  'auxiliary_count': 1,
  'fallback_symbol': '??_Gbad_cast@@UAEPAXI@Z',
  'fallback_symbol_index': 111,
  'fallback_reference': {'symbol': '??_Gbad_cast@@UAEPAXI@Z',
                         'offset': 0,
                         'section': 0,
                         'type': 32,
                         'storage': 2},
  'fallback_definition': {'symbol': '??_Gbad_cast@@UAEPAXI@Z',
                          'offset': 0,
                          'section': 75,
                          'type': 32,
                          'storage': 2},
  'search_characteristics': 2,
  'strong_archive_definitions': []},
 {'member_offset': 442622,
  'symbol': '??_Ebad_typeid@@UAEPAXI@Z',
  'source_definition': {'symbol': '??_Ebad_typeid@@UAEPAXI@Z',
                        'offset': 0,
                        'section': 0,
                        'type': 32,
                        'storage': 105},
  'symbol_index': 172,
  'auxiliary_count': 1,
  'fallback_symbol': '??_Gbad_typeid@@UAEPAXI@Z',
  'fallback_symbol_index': 171,
  'fallback_reference': {'symbol': '??_Gbad_typeid@@UAEPAXI@Z',
                         'offset': 0,
                         'section': 0,
                         'type': 32,
                         'storage': 2},
  'fallback_definition': {'symbol': '??_Gbad_typeid@@UAEPAXI@Z',
                          'offset': 0,
                          'section': 78,
                          'type': 32,
                          'storage': 2},
  'search_characteristics': 2,
  'strong_archive_definitions': []},
 {'member_offset': 442622,
  'symbol': '??_E__non_rtti_object@@UAEPAXI@Z',
  'source_definition': {'symbol': '??_E__non_rtti_object@@UAEPAXI@Z',
                        'offset': 0,
                        'section': 0,
                        'type': 32,
                        'storage': 105},
  'symbol_index': 232,
  'auxiliary_count': 1,
  'fallback_symbol': '??_G__non_rtti_object@@UAEPAXI@Z',
  'fallback_symbol_index': 231,
  'fallback_reference': {'symbol': '??_G__non_rtti_object@@UAEPAXI@Z',
                         'offset': 0,
                         'section': 0,
                         'type': 32,
                         'storage': 2},
  'fallback_definition': {'symbol': '??_G__non_rtti_object@@UAEPAXI@Z',
                          'offset': 0,
                          'section': 81,
                          'type': 32,
                          'storage': 2},
  'search_characteristics': 2,
  'strong_archive_definitions': []},
 {'member_offset': 442622,
  'symbol': '??_Eexception@@UAEPAXI@Z',
  'source_definition': {'symbol': '??_Eexception@@UAEPAXI@Z',
                        'offset': 0,
                        'section': 0,
                        'type': 32,
                        'storage': 105},
  'symbol_index': 18,
  'auxiliary_count': 1,
  'fallback_symbol': '??_Gexception@@UAEPAXI@Z',
  'fallback_symbol_index': 17,
  'fallback_reference': {'symbol': '??_Gexception@@UAEPAXI@Z',
                         'offset': 0,
                         'section': 0,
                         'type': 32,
                         'storage': 2},
  'fallback_definition': {'symbol': '??_Gexception@@UAEPAXI@Z',
                          'offset': 0,
                          'section': 69,
                          'type': 32,
                          'storage': 2},
  'search_characteristics': 2,
  'strong_archive_definitions': []},
 {'member_offset': 462402,
  'symbol': '??_Etype_info@@UAEPAXI@Z',
  'source_definition': {'symbol': '??_Etype_info@@UAEPAXI@Z',
                        'offset': 0,
                        'section': 0,
                        'type': 32,
                        'storage': 105},
  'symbol_index': 18,
  'auxiliary_count': 1,
  'fallback_symbol': '??_Gtype_info@@UAEPAXI@Z',
  'fallback_symbol_index': 17,
  'fallback_reference': {'symbol': '??_Gtype_info@@UAEPAXI@Z',
                         'offset': 0,
                         'section': 0,
                         'type': 32,
                         'storage': 2},
  'fallback_definition': {'symbol': '??_Gtype_info@@UAEPAXI@Z',
                          'offset': 0,
                          'section': 13,
                          'type': 32,
                          'storage': 2},
  'search_characteristics': 2,
  'strong_archive_definitions': []}]
METADATA_DIGESTS = {'scope_tables': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945',
 'call_controls': '82a0d87e71784ee65738c712a9741d9554999105375344281d9890ec5af674ca',
 'probe_generated_data': '069001594828f84b91a667d5c6e8a9abaac6583272716374e5884eb4e59082eb',
 'probe_generated_code': 'eee3338798350607b46ef39cdfeba2876843f9cb8d7de86237d9819a74c94b26',
 'runtime_dispatch': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945',
 'extent_reconciliations': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945',
 'family_graph': 'ba95cc342d2729adb4284aa30f207d623d268be08acb50d942cda5b459427fbd',
 'source_alternatives': 'a3cb09ea13bdc3bb7188f6d5028b8ad5c66da2c74c6a077ab1295d160cf35f37'}

def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

prior = module('derived_exception_prior', 'verify-standard-exception-origins.py')
check_code_entry = prior.check_code_entry
whole_defining_section = prior.whole_defining_section
read_weak_reference = prior.read_weak_reference
decode_code = prior.decode_code
check_scope_records = prior.check_scope_records
resolve_state_reference = prior.resolve_state_reference
check_catalog_entry = prior.check_catalog_entry

def manifest():
    m = json.loads((ROOT / 'config/derived-exception-origin-evidence.json').read_text())
    identity = module('derived_exception_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R143' or m['target_sha256'] != identity.TARGET:
        raise ValueError('derived-exception target identity differs')
    return m


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(rows) != 3 or len(m['functions']) != 3 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete derived-exception cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key] or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'], 16) != int(key, 16) + size - 1):
            raise ValueError('derived-exception function loses complete own AUX extent')
    aux = {r['address']: (r['coff_symbol'], r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies']) != 8 or aux != AUXILIARIES or any(
            r['decision'] != 'library-control' or r['extent_basis'] != 'function-auxiliary-record'
            or r['code_size'] != r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16) != int(r['address'],16) + r['size'] - 1
            for r in m['auxiliary_bodies']):
        raise ValueError('derived-exception auxiliary controls gain invented inventory credit')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'], r['size'], r['source_offset'], r['source_symbol'])
             for r in m['interior_labels']} != LABELS or any(
            r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary'
            for r in m['interior_labels'])):
        raise ValueError('derived-exception labels lose complete source parents')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence'],r['origin'])
            for r in m['anchors']] != ANCHORS:
        raise ValueError('derived-exception independent full anchors differ')
    if any(m[k] for k in ('range_markers','initializer_registrations','callback_ranges',
                          'literal_controls','retained_labels','diagnostic_contexts','common_globals',
                          'code_carriers')):
        raise ValueError('derived-exception graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 31 or sum(r['size'] for r in m['state_data']) != 543 or
            {(r['member_offset'],r['symbol'],r['target_address'],r['size'])
             for r in m['state_data']} != STATE):
        raise ValueError('derived-exception loses complete defining data sections')
    if (m['sdk_layout']['source_section_size'] != 32 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS
            or set(m['sdk_layout']['headers']) != LAYOUT_HEADERS
            or m['vendor_sources']):
        raise ValueError('derived-exception loses actual SDK or available source context')
    if m['retained_controls'] != [dict(evidence_id='R142',manifest='standard-exception-origin-evidence.json')]:
        raise ValueError('derived-exception loses full retained independent R142 (including R038) graph')
    if m['derived_protocol'] != DERIVED_PROTOCOL or m['family_graph'] != FAMILY_GRAPH or m['register_contracts']:
        raise ValueError('derived-exception private ABI/SDK facts or unknowns differ')
    if m['retained_thunks']:
        raise ValueError('derived-exception changes independent compiler thunk ownership')
    for key, digest in METADATA_DIGESTS.items():
        if metadata_digest(m[key]) != digest:
            raise ValueError('derived-exception reviewed complete '+key+' inventory differs')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors']}}
    for row in graph.values():
        if row['code_regions'] != [dict(offset=0,size=row['size'])] or row['code_size'] != row['size']:
            raise ValueError('derived-exception loses complete code partition')
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] == 'import-thunk':
                raise ValueError('standard exception has no reviewed new import thunk')
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('derived-exception field lacks typed code/data/API provenance')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('derived-exception shared branch loses complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('derived-exception edge loses actual typed transfer')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('derived-exception defining data loses full typed provenance')
            if b['target_kind'] == 'code-entry':
                check_code_entry(b,graph)
    if m['source_weak_references'] != SOURCE_WEAK_REFERENCES:
        raise ValueError('derived-exception actual weak fallback records differ')
    check_derived_protocol(m, graph)
    return rows

def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('derived-exception loses complete origin-only extent')
    if (origin['evidence_id'] != 'R143' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('derived-exception canonical complete library acceptance differs')

def object_code(path,row,comparison,coff):
    if row['extent_basis']=='function-auxiliary-record':
        return comparison.object_function(path,row['coff_symbol'])
    if row['extent_basis']!='whole-defining-code-section-without-AUX' or row['coff_symbol'] not in ('??_Gexception@@UAEPAXI@Z','??_Gtype_info@@UAEPAXI@Z','??_Gbad_cast@@UAEPAXI@Z','??_Gbad_typeid@@UAEPAXI@Z','??_G__non_rtti_object@@UAEPAXI@Z'):
        raise ValueError('derived-exception source code loses own AUX or complete no-AUX control section')
    data = path.read_bytes();definitions = coff.parse_symbols(data,comparison.coff_name)[1]
    primary = next(d for d in definitions if d['symbol']==row['coff_symbol'] and d['section']>0)
    h = struct.unpack_from('<8sIIIIIIHHI',data,20+(primary['section']-1)*40)
    desc = dict(size=h[3],flags=f'0x{h[9]:08X}',definitions=[d for d in definitions if d['section']==primary['section']])
    if primary['offset']!=0 or desc!=row['source_code_section'] or h[3]!=row['size']:
        raise ValueError('compiler scalar control loses entire defining code section')
    return comparison.object_function(path,row['coff_symbol'],row['size'])

def check_probe_generated(data,path,m,comparison,coff,old,decoder,facts):
    definitions = coff.parse_symbols(data,comparison.coff_name)[1]
    count = struct.unpack_from('<H',data,2)[0]
    headers = [struct.unpack_from('<8sIIIIIIHHI',data,20+i*40) for i in range(count)]
    for row in m['probe_generated_data']:
        raw,desc,anchor = whole_defining_section(data,row['symbol'],comparison,coff)
        if anchor!=row['source_anchor']:
            raise ValueError('cold model whole data source anchor differs')
        if desc != row['source_section'] or hashlib.sha256(raw).hexdigest() != row['source_sha256']:
            raise ValueError('cold natural EH model loses whole generated defining data')
    for row in m['probe_generated_code']:
        entry = next(d for d in definitions if d['symbol']==row['coff_symbol'] and d['section']>0)
        header = headers[entry['section']-1]
        section_defs = [d for d in definitions if d['section']==entry['section'] and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')]
        if (entry != row['source_definition'] or entry['offset'] != 0 or header[3] != row['size']
                or f'0x{header[9]:08X}' != row['flags'] or section_defs != row['source_definitions']
                or row['extent_basis'] != 'whole-defining-code-section-without-AUX'):
            raise ValueError('cold natural EH carrier loses complete no-AUX defining code section')
        symbol_offset,symbol_count = struct.unpack_from('<II',data,8)
        string_offset = symbol_offset + symbol_count*18
        strings = data[string_offset:string_offset+struct.unpack_from('<I',data,string_offset)[0]]
        index = 0
        auxiliary = None
        while index < symbol_count:
            name,_,_,_,_,aux = struct.unpack_from('<8sIhHBB',data,symbol_offset+index*18)
            if comparison.coff_name(name,strings) == row['coff_symbol']:
                auxiliary = aux
                break
            index += 1+aux
        if auxiliary != 0:
            raise ValueError('cold model EH carrier no-AUX provenance differs')
        raw,fields = comparison.object_function(path,row['coff_symbol'],row['size'])
        ins = list(decoder.disasm(raw,0))
        metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
        if (sum(i.size for i in ins) != len(raw) or metadata != row['relocation_metadata']
                or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or facts.body_facts(ins) != row['body_facts']):
            raise ValueError('cold natural EH carrier loses full code/typed metadata')
    # Every initialized model section except the whole SDK layout must appear;
    # this prevents accepting a descriptor prefix while dropping its neighbours.
    expected = {next(d['section'] for d in definitions if d['symbol']==r['symbol'])
                for r in m['probe_generated_data']}
    layout_section = next(d['section'] for d in definitions if d['symbol']=='_DerivedExceptionLayoutProbe')
    actual = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x40 and h[9]&0x40000000
              and not h[9]&0x20000000 and h[0].rstrip(b'\0') not in (b'.debug$S',b'.debug$T',b'.debug$F',b'.drectve')}
    if actual != expected | {layout_section}:
        raise ValueError('cold natural EH model loses an entire generated initialized section')
    owned = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['call_controls']}
    carriers = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['probe_generated_code']}
    code_sections = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x20}
    if owned & carriers or owned | carriers != code_sections:
        raise ValueError('cold natural model loses a complete generated code section')

def check_derived_protocol(m, graph):
    """Require complete paired roles while retaining equal-body source ambiguity."""
    data = {(r['member_offset'],r['symbol']):r for r in m['state_data']}
    for family in m['family_graph']:
        destructor = graph[family['destructor']]
        if (destructor['coff_symbol'] != family['source_destructor_symbol']
                or destructor['body_facts']['returns']
                or destructor['indirect_calls'] or destructor['indirect_jumps']
                or len(destructor['instruction_witnesses']) != 2):
            raise ValueError('derived destructor loses complete vtable-store/base-tail protocol')
        instructions = [(r['mnemonic'],r['operands']) for r in destructor['instruction_witnesses']]
        expected = [('mov','dword ptr [ecx], '+hex(int(family['destructor_vtable_address_point'],16))),
                    ('jmp','0x640ce4')]
        if instructions != expected:
            raise ValueError('derived destructor changes its actual destruction-stage vtable or base tail')
        fields = destructor['relocation_bindings']
        stage = 'bad_typeid' if family['source_class']=='__non_rtti_object' else family['source_class']
        if ([(b['offset'],b['type'],b['symbol'],b['target_address']) for b in fields] !=
                [(2,'DIR32','??_7'+stage+'@@6B@',family['destructor_vtable_address_point']),
                 (7,'REL32','??1exception@@UAE@XZ','0x00640CE4')]):
            raise ValueError('derived destructor loses full typed stage/base fields')
        vtable = data[(442622,family['source_vtable_symbol'])]
        if (vtable['size']!=12 or vtable['source_anchor']['offset']!=4
                or int(vtable['target_address'],16)+4!=int(family['constructed_vtable_address_point'],16)):
            raise ValueError('derived family loses whole prefixed constructed vtable')
        callback = vtable['relocations'][1]
        if (callback['offset']!=4 or callback['symbol']!=family['source_weak_symbol']
                or callback['target_address']!=family['compiler_deleting_callback']
                or callback['source_weak_reference']['fallback_symbol']!=family['source_fallback_symbol']
                or callback['code_entry']['owner']!=family['compiler_deleting_callback']):
            raise ValueError('derived family loses paired actual weak/compiler callback')
        scalar = graph[family['compiler_deleting_callback']]
        incoming = next((b for b in scalar['relocation_bindings'] if b['symbol']==family['source_destructor_symbol']),None)
        if (scalar['origin']!='compiler' or scalar['origin_evidence']!='R038'
                or scalar['coff_symbol']!=family['source_fallback_symbol'] or scalar['size']!=28
                or not incoming or incoming['type']!='REL32' or incoming['offset']!=4
                or incoming['target_address']!=family['destructor']):
            raise ValueError('derived family loses independent complete R038 incoming destructor context')
        for key,base in [('message_constructor','0x00640D43' if stage!=family['source_class'] else '0x00640C5D'),
                         ('copy_constructor','0x00640D5C' if stage!=family['source_class'] else '0x00640C9A')]:
            constructor = graph[family[key]]
            if (constructor['decision']!='library-control'
                    or not any(b['type']=='DIR32' and b['symbol']==family['source_vtable_symbol']
                               and b['target_address']==family['constructed_vtable_address_point']
                               for b in constructor['relocation_bindings'])
                    or not any(b['type']=='REL32' and b['target_address']==base for b in constructor['relocation_bindings'])
                    or len(constructor['body_facts']['returns'])!=1
                    or constructor['body_facts']['returns'][0]['cleanup']!=4):
                raise ValueError('derived family loses whole non-inventory constructor/base ABI context')
        array = data[(442622,'??_R2'+family['source_class']+'@@8')]
        if (array['size']!=4*len(family['rtti_bases'])+1
                or [b['symbol'] for b in array['relocations']] !=
                   ['??_R1A@?0A@A@'+base+'@@8' for base in family['rtti_bases']]):
            raise ValueError('derived family loses full RTTI base array and all trailing bytes')
    rows = {r['address']:r for r in m['functions']}
    if rows['0x00640D74']['source_sha256']!=rows['0x00640DAF']['source_sha256']:
        raise ValueError('equal destructor bodies must remain explicit source alternatives')
    expected = {'??1bad_cast@@UAE@XZ':['0x00640D38'],
                '??1bad_typeid@@UAE@XZ':['0x00640D74','0x00640DAF'],
                '??1__non_rtti_object@@UAE@XZ':['0x00640D74','0x00640DAF']}
    if (len(m['source_alternatives'])!=3 or
            {r['coff_symbol']:[x['target_address'] for x in r['full_linked_results'] if x['complete_match']]
             for r in m['source_alternatives']}!=expected):
        raise ValueError('derived family omits complete equal-body source alternatives')
    for row in m['auxiliary_bodies']:
        if any(r['cleanup']!=4 for r in row['body_facts']['returns']) and row['address']!='0x00640CFA':
            raise ValueError('derived constructor changes actual member callee cleanup')
    dispatch = [dict(owner=r['address'],calls=r['indirect_calls'],jumps=r['indirect_jumps'])
                for r in m['functions']+m['auxiliary_bodies'] if r['indirect_calls'] or r['indirect_jumps']]
    if dispatch!=m['runtime_dispatch']:
        raise ValueError('derived family changes complete indirect dispatch inventory')


def check_source_alternatives(m,members,state_map,global_state,path,comparison,coff):
    """Cold-read every complete alternative and bind fields through proved owners."""
    target = comparison.verified_target()
    for alternative in m['source_alternatives']:
        name,data = members[alternative['member_offset']]
        if name!=alternative['member'] or hashlib.sha256(data).hexdigest()!=alternative['member_sha256']:
            raise ValueError('source alternative loses full archive member identity')
        path.write_bytes(data)
        raw,fields = comparison.object_function(path,alternative['coff_symbol'])
        definitions = coff.parse_symbols(data,comparison.coff_name)[1]
        primary = next(d for d in definitions if d['symbol']==alternative['coff_symbol'] and d['section']>0)
        metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
        if (len(raw)!=alternative['size'] or alternative['extent_basis']!='function-auxiliary-record'
                or primary!=alternative['source_definition'] or metadata!=alternative['relocation_metadata']
                or hashlib.sha256(raw).hexdigest()!=alternative['source_sha256']):
            raise ValueError('source alternative loses full own AUX/typed field identity')
        observed = []
        for row in m['functions']:
            a = int(row['address'],16); linked = bytearray(raw)
            for field in fields:
                if field['type']=='DIR32':
                    dest = state_map.get((alternative['member_offset'],field['symbol']))
                    if dest is None:
                        candidates = global_state.get(field['symbol'],set())
                        if len(candidates)!=1:
                            raise ValueError('source alternative lacks independently proved whole state owner')
                        dest = next(iter(candidates))
                    value = dest+field['addend']
                elif field['type']=='REL32' and field['symbol']=='??1exception@@UAE@XZ':
                    base = next(r for r in m['anchors'] if r['coff_symbol']==field['symbol'])
                    value = int(base['address'],16)+field['addend']-a-field['offset']-4
                else:
                    raise ValueError('source alternative gains an unreviewed typed field')
                struct.pack_into('<I',linked,field['offset'],value&0xffffffff)
            observed.append(dict(target_address=row['address'],complete_match=bytes(linked)==comparison.pe_bytes_at(target,a,len(raw)),
                                 linked_sha256=hashlib.sha256(linked).hexdigest()))
        if observed!=alternative['full_linked_results']:
            raise ValueError('source alternative changes complete relocated comparison results')

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('derived_exception_old','verify-runtime-error-origins.py')
    c = module('derived_exception_target','compare-coff-function.py')
    archive_reader = module('derived_exception_archive','verify-runtime-origins.py')
    coff = module('derived_exception_coff','coff_data.py')
    startup = module('derived_exception_geometry','verify-startup-dependency-origins.py')
    record = module('derived_exception_ledger','verify-vendor-record-origins.py')
    facts = module('derived_exception_facts','verify-game-lifetime-origins.py')
    imports_module = module('derived_exception_imports','verify-import-origins.py')
    literal = module('derived_exception_scalar','verify-runtime-external-origins.py')
    sections = module('derived_exception_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete derived-exception source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('derived-exception complete primary loses an actual interior candidate')
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest() != m['archive_sha256']:
        raise ValueError('pinned whole CRT archive differs')
    members = {off:(name,data) for off,name,data in archive_reader.archive_members(archive)}
    def member(row):
        name,data = members[row['member_offset']]
        if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
            raise ValueError('complete source member identity differs')
        return data
    target_sections = sections.sections(target); imports = imports_module.pe_imports(target,c)
    state_map = {}; global_state = {}
    for row in m['state_data']:
        raw,desc,anchor = whole_defining_section(member(row),row['symbol'],c,coff)
        if anchor != row['source_anchor']:
            raise ValueError('whole source data changes its actual interior address-point anchor')
        a = int(row['target_address'],16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('derived-exception whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('derived-exception source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('derived-exception state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('derived-exception whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('derived-exception initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('derived-exception complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('derived-exception state loses whole writable target storage')
        else:
            literal.check_scalar(linked,actual,row['size'],target_sections,a)
    for row in m['common_globals']:
        definitions=coff.parse_symbols(member(row),c.coff_name)[1]
        actual=next((d for d in definitions if d['symbol']==row['symbol'] and d['section']==0),None)
        a=int(row['target_address'],16)
        if actual!=row['source_definition'] or actual['offset']!=row['size'] or startup.zero_fill_region(target,a,row['size'])!=row['zero_fill_region']:
            raise ValueError('complete COMMON definition/loader zero-fill differs')
        state_map[(row['member_offset'],row['symbol'])]=a
        global_state.setdefault(row['symbol'],set()).add(a)
    for use in m['state_uses']:
        state_map[(use['member_offset'],use['symbol'])] = resolve_state_reference(use,state_map,global_state)
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-derived-exception-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src','/Zc:wchar_t','/GR']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural derived-exception control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned derived-exception control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_DerivedExceptionLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural derived-exception data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural exception/thread SDK offsets or ABI constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete derived-exception vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete derived-exception ABI/SEH/C++ controls differ')
        check_probe_generated(data,path,m,c,coff,old,decoder,facts)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R142'):
                    raise ValueError('derived-exception retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'] and d['section']>0)
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('derived-exception complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('derived-exception full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('derived-exception whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('derived-exception complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('derived-exception field lacks member-local/whole strong data provenance')
        for scope in m['scope_tables']:
            data_row = next(r for r in m['state_data'] if r['symbol']==scope['symbol'] and r['member_offset']==scope['member_offset'])
            check_scope_records(scope,data_row,c.pe_bytes_at(target,int(scope['address'],16),scope['size']),graph,decoded)
        for reference in m['source_weak_references']:
            actual_reference = read_weak_reference(members[reference['member_offset']][1],reference['symbol'],c,coff,reference['member_offset'])
            if actual_reference != reference:
                raise ValueError('actual weak source COFF AUX/search/fallback differs')
            strong = []
            for off,(_,data) in members.items():
                try:definitions = coff.parse_symbols(data,c.coff_name)[1]
                except ValueError:continue
                strong.extend(dict(member_offset=off,source_definition=d) for d in definitions if d['symbol']==reference['symbol'] and d['section']>0 and d['storage']==2)
            if strong != reference['strong_archive_definitions']:
                raise ValueError('weak reference gains an unreviewed strong archive alternative')
        for row in m['state_data']:
            for b in row['relocations']:
                if 'source_weak_reference' in b:
                    ref = b['source_weak_reference']
                    if (ref not in m['source_weak_references'] or ref['member_offset']!=row['member_offset']
                            or b['symbol']!=ref['symbol'] or b['code_entry']['source_definition']!=ref['fallback_definition']):
                        raise ValueError('weak vtable callback loses actual fallback source definition')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('derived-exception code entry catalog differs from actual complete source definitions')
        bindings = [b for r in m['functions']+m['auxiliary_bodies'] for b in r['relocation_bindings'] if 'code_entry' in b]
        bindings += [b for r in m['state_data'] for b in r['relocations'] if 'code_entry' in b]
        for b in bindings:
            check_catalog_entry(b,observed_catalog)
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = object_code(path,row,c,coff)
            source_ins = {i.address-row['source_definition']['offset']:i for i in decode_code(row,code,row['source_definition']['offset'],decoder)}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('derived-exception local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('derived-exception direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('derived-exception direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('derived-exception same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('derived-exception shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('derived-exception complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('derived-exception data pointer does not reach a complete actual code entry')
        check_source_alternatives(m,members,state_map,global_state,path,c,coff)
    for script in ('verify-standard-exception-origins.py',):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('retained independent full R142 (including R038) replay failed: '+result.stderr[-1500:])
    print('R143 origins OK: three complete derived exception destructors / 33 bytes / six fields; eight complete non-inventory constructors/what controls / 220 bytes / 17 fields; ten full retained anchors / 400 bytes / 18 fields preserve five library and five R038 compiler origins; 31 whole vtable/RTTI/literal sections / 543 bytes / 48 fields; five actual weak AUX/search/fallback records; explicit complete equal-body source alternatives and paired constructor/vtable/RTTI/deleting-callback provenance; cold actual SDK layout and all natural ABI/RTTI model code and data sections; full retained R142/R038 cold replay; local origin-only acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
