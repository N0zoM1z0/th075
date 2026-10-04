#!/usr/bin/env python3
"""Replay complete R142 C++ throw/frame and standard exception/RTTI provenance."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
CONFIDENCE = 'complete-vendor-standard-exception-throw-frame-rtti-weak-scope-abi-provenance'
LABEL_CONFIDENCE = 'finally-entry-in-complete-vendor-type-info-destructor'
ACCEPTED = {'0x00640C12': ('__CxxThrowException@8', 58),
 '0x00640C9A': ('??0exception@@QAE@ABV0@@Z', 74),
 '0x00640E49': ('??1type_info@@UAE@XZ', 70),
 '0x006407B8': ('___CxxFrameHandler', 54),
 '0x00640C4C': ('??0exception@@QAE@XZ', 17),
 '0x00640DD6': ('??4exception@@QAEAAV0@ABV0@@Z', 31),
 '0x00640F15': ('??3@YAXPAX@Z', 5),
 '0x00640CE4': ('??1exception@@UAE@XZ', 22)}
LEDGER_SIZES = {'0x00640C12': 58,
 '0x00640C9A': 74,
 '0x00640E49': 61,
 '0x006407B8': 54,
 '0x00640C4C': 17,
 '0x00640DD6': 31,
 '0x00640F15': 5,
 '0x00640CE4': 22}
AUXILIARIES = {'0x00640CFA': ('?what@exception@@UBEPBDXZ', 13)}
LABELS = {'0x00640E86': ('0x00640E49', 9, 61, '$L19209')}
ANCHORS = [('0x00640620',
  '_strlen',
  139,
  2200788,
  'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG',
  'library'),
 ('0x00644331', '_malloc', 18, 816374, 'R120', 'library'),
 ('0x00641B80', '_strcpy', 7, 2186124, 'R116', 'library'),
 ('0x00645414', '__SEH_prolog', 59, 1244382, 'R117', 'library'),
 ('0x00646725', '__lock', 49, 1698134, 'R120', 'library'),
 ('0x00642A61', '_free', 113, 794604, 'R120', 'library'),
 ('0x0064544F', '__SEH_epilog', 17, 1244382, 'R115', 'library'),
 ('0x00646658', '__unlock', 21, 1698134, 'R118', 'library'),
 ('0x006460BB', '___InternalCxxFrameHandler', 162, 379030, 'R141', 'library'),
 ('0x00640DBA', '??_Gexception@@UAEPAXI@Z', 28, 442622, 'R038', 'compiler'),
 ('0x00640E8F', '??_Gtype_info@@UAEPAXI@Z', 28, 462402, 'R038', 'compiler')]
STATE = {(416746, '?ExceptionTemplate@?1??_CxxThrowException@@9@8@4UEHExceptionRecord@@B', '0x00660E74', 32),
 (442622, '??_7exception@@6B@', '0x00660E94', 12),
 (442622, '??_C@_0BC@EOODALEL@Unknown?5exception?$AA@', '0x00660EA0', 18),
 (442622, '??_R0?AVexception@@@8', '0x0066C1BC', 24),
 (442622, '??_R1A@?0A@A@exception@@8', '0x006676FC', 24),
 (442622, '??_R2exception@@8', '0x00667714', 5),
 (442622, '??_R3exception@@8', '0x0066771C', 16),
 (442622, '??_R4exception@@6B@', '0x0066772C', 20),
 (462402, '$T19215', '0x00660EE0', 12),
 (462402, '??_7type_info@@6B@', '0x00660ED8', 8),
 (462402, '??_R0?AVtype_info@@@8', '0x0066FEB8', 24),
 (462402, '??_R1A@?0A@A@type_info@@8', '0x0066781C', 24),
 (462402, '??_R2type_info@@8', '0x00667834', 5),
 (462402, '??_R3type_info@@8', '0x0066783C', 16),
 (462402, '??_R4type_info@@6B@', '0x0066784C', 20)}
LAYOUT_OBJECTS = [{'symbol': '_StandardExceptionLayoutProbe',
  'offset': 0,
  'size': 88,
  'storage_span': 88,
  'values': [4, 4, 4, 4, 80, 0, 4, 16, 20, 1, 15, 12, 12, 12, 12, 12, 12, 4, 8, 4, 4, 1]}]
LAYOUT_HEADERS = {'PlatformSDK/Include/BaseTsd.h',
 'PlatformSDK/Include/CGuid.h',
 'PlatformSDK/Include/CdErr.h',
 'PlatformSDK/Include/CommDlg.h',
 'PlatformSDK/Include/Dde.h',
 'PlatformSDK/Include/Ddeml.h',
 'PlatformSDK/Include/Dlgs.h',
 'PlatformSDK/Include/Guiddef.h',
 'PlatformSDK/Include/Imm.h',
 'PlatformSDK/Include/LZExpand.h',
 'PlatformSDK/Include/MMSystem.h',
 'PlatformSDK/Include/Mcx.h',
 'PlatformSDK/Include/MsXml.h',
 'PlatformSDK/Include/Nb30.h',
 'PlatformSDK/Include/OAIdl.h',
 'PlatformSDK/Include/ObjBase.h',
 'PlatformSDK/Include/ObjIdl.h',
 'PlatformSDK/Include/Ole2.h',
 'PlatformSDK/Include/OleAuto.h',
 'PlatformSDK/Include/OleIdl.h',
 'PlatformSDK/Include/PopPack.h',
 'PlatformSDK/Include/PrSht.h',
 'PlatformSDK/Include/PropIdl.h',
 'PlatformSDK/Include/PshPack1.h',
 'PlatformSDK/Include/PshPack2.h',
 'PlatformSDK/Include/PshPack4.h',
 'PlatformSDK/Include/PshPack8.h',
 'PlatformSDK/Include/Reason.h',
 'PlatformSDK/Include/Rpc.h',
 'PlatformSDK/Include/RpcAsync.h',
 'PlatformSDK/Include/RpcDce.h',
 'PlatformSDK/Include/RpcDceP.h',
 'PlatformSDK/Include/RpcNdr.h',
 'PlatformSDK/Include/RpcNsi.h',
 'PlatformSDK/Include/RpcNsip.h',
 'PlatformSDK/Include/RpcNtErr.h',
 'PlatformSDK/Include/ServProv.h',
 'PlatformSDK/Include/ShellAPI.h',
 'PlatformSDK/Include/StrAlign.h',
 'PlatformSDK/Include/Unknwn.h',
 'PlatformSDK/Include/UrlMon.h',
 'PlatformSDK/Include/WTypes.h',
 'PlatformSDK/Include/WinBase.h',
 'PlatformSDK/Include/WinCon.h',
 'PlatformSDK/Include/WinCrypt.h',
 'PlatformSDK/Include/WinDef.h',
 'PlatformSDK/Include/WinEFS.h',
 'PlatformSDK/Include/WinError.h',
 'PlatformSDK/Include/WinGDI.h',
 'PlatformSDK/Include/WinIoCtl.h',
 'PlatformSDK/Include/WinNT.h',
 'PlatformSDK/Include/WinNetWk.h',
 'PlatformSDK/Include/WinNls.h',
 'PlatformSDK/Include/WinPerf.h',
 'PlatformSDK/Include/WinReg.h',
 'PlatformSDK/Include/WinSCard.h',
 'PlatformSDK/Include/WinSmCrd.h',
 'PlatformSDK/Include/WinSock.h',
 'PlatformSDK/Include/WinSpool.h',
 'PlatformSDK/Include/WinSvc.h',
 'PlatformSDK/Include/WinUser.h',
 'PlatformSDK/Include/WinVer.h',
 'PlatformSDK/Include/Windows.h',
 'crt/src/cruntime.h',
 'crt/src/cstddef',
 'crt/src/ctype.h',
 'crt/src/eh.h',
 'crt/src/exception',
 'crt/src/excpt.h',
 'crt/src/new',
 'crt/src/stdarg.h',
 'crt/src/stddef.h',
 'crt/src/stdexcpt.h',
 'crt/src/stdlib.h',
 'crt/src/string.h',
 'crt/src/typeinfo',
 'crt/src/typeinfo.h',
 'crt/src/use_ansi.h',
 'crt/src/xstddef',
 'crt/src/yvals.h',
 'include/tvout.h'}
STANDARD_PROTOCOL = {'sdk_exception_size': 12,
 'sdk_type_info_size': 12,
 'message_pointer_offset': 4,
 'ownership_flag_offset': 8,
 'throw_template_size': 32,
 'sdk_exception_record_size': 80,
 'throw_template_values': [3765269347, 1, 0, 0, 3, 429065504, 0, 0],
 'throw_parameter_count': 3,
 'throw_magic_parameter_offset': 20,
 'throw_object_parameter_offset': 24,
 'throw_descriptor_parameter_offset': 28,
 'throw_callee_cleanup': 8,
 'copy_callee_cleanup': 4,
 'assignment_callee_cleanup': 4,
 'frame_handler_caller_cleanup': 32,
 'type_info_lock_number': 14,
 'type_info_finally_offset': 61,
 'vtable_address_point_offset': 4,
 'exception_vtable_complete_size': 12,
 'type_info_vtable_complete_size': 8,
 'rtti_base_array_complete_size': 5,
 'rtti_base_array_note': 'Complete source section is five bytes; its one pointer is not accepted as a '
                         'four-byte prefix',
 'source_basis': 'Full pinned COFF owners, all state/RTTI/callback fields, actual weak external AUX '
                 'tag/search records and complete defining sections; private original '
                 'throw/stdexcpt/typinfo/trnsctrl implementation files unavailable',
 'abi_basis': 'Complete real supplied SDK exception/type_info interfaces and independent '
              'ownership/raise/throw/member models; no private EHExceptionRecord or complete original game '
              'object invented',
 'runtime_unknowns': 'Original complete private throw metadata identities/layouts, original linker '
                     'input/search decisions beyond pinned archive evidence, object/message ownership and '
                     'allocation outcomes, current RTTI cached-name state, exception delivery and handler '
                     'outcomes'}
REGISTER_CONTRACTS = {'0x006407B8': {'incoming': ['EAX is saved as opaque function metadata',
                             'EBP+8/+12/+16/+20 supply four handler inputs'],
                'outgoing': ['Eight stack arguments to InternalCxxFrameHandler',
                             'Three trailing arguments are zero',
                             '32 bytes of caller cleanup'],
                'basis': 'Full source/target shim and naturally generated EH handler EAX metadata carriers; '
                         'no invented conventional private prototype'}}
SOURCE_WEAK_REFERENCES = [{'member_offset': 442622,
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
METADATA_DIGESTS = {'scope_tables': '6f001986cda4274b590970c9c4fce5b8a86ff22611946396e1df29c031bb13a0',
 'call_controls': '2092aeddc1d31b4a7fcdc27df942ddf735bb3a9a8755e14595e6031e621e9c25',
 'probe_generated_data': '84b37358589167668323c97b7c214ad8c449be4d1e802e46e5339d3294bab51a',
 'probe_generated_code': '57dee043e048c606dc1a46122f52a2e83144b507a4436d204f9bb5e1a48940d1',
 'runtime_dispatch': '1423f87d46ef9aac27a0fb70126a5762ab57a657090423c5f990a7eefc19a267',
 'extent_reconciliations': '7169b91349a287ab8a3a24c870240928d82d94891db2be60aa893342c3551cbd'}

def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

def manifest():
    m = json.loads((ROOT / 'config/standard-exception-origin-evidence.json').read_text())
    identity = module('standard_exception_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R142' or m['target_sha256'] != identity.TARGET:
        raise ValueError('standard-exception target identity differs')
    return m

def check_code_entry(binding, graph):
    entry = binding['code_entry']; owner = graph.get(entry['owner'])
    if not owner or owner['decision'] not in ('library','library-control','anchor'):
        raise ValueError('dispatch retains an unreviewed actual code entry')
    source = entry['source_definition']; primary = owner['source_definition']
    if (entry['source_member_offset'] != owner['member_offset']
            or source['symbol'] != binding.get('source_weak_reference',{}).get('fallback_symbol',binding['symbol']) or source['section'] != primary['section']
            or source['offset'] - primary['offset'] != entry['source_offset']
            or source['storage'] not in (2,3,6)
            or not any(r['offset']<=entry['source_offset']<r['offset']+r['size'] for r in owner['code_regions'])
            or int(binding['target_address'],16) != int(owner['address'],16) + entry['source_offset']):
        raise ValueError('dispatch code pointer loses its actual defining source owner/entry')

def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(rows) != 8 or len(m['functions']) != 8 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete standard-exception cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key] or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'], 16) != int(key, 16) + size - 1):
            raise ValueError('standard-exception function loses complete own AUX extent')
    aux = {r['address']: (r['coff_symbol'], r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies']) != 1 or aux != AUXILIARIES or any(
            r['decision'] != 'library-control' or r['extent_basis'] != 'function-auxiliary-record'
            or r['code_size'] != r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16) != int(r['address'],16) + r['size'] - 1
            for r in m['auxiliary_bodies']):
        raise ValueError('standard-exception auxiliary controls gain invented inventory credit')
    if (len(m['interior_labels']) != 1 or
            {r['address']: (r['parent'], r['size'], r['source_offset'], r['source_symbol'])
             for r in m['interior_labels']} != LABELS or any(
            r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary'
            for r in m['interior_labels'])):
        raise ValueError('standard-exception labels lose complete source parents')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence'],r['origin'])
            for r in m['anchors']] != ANCHORS:
        raise ValueError('standard-exception independent full anchors differ')
    if any(m[k] for k in ('range_markers','initializer_registrations','callback_ranges',
                          'literal_controls','retained_labels','diagnostic_contexts','common_globals',
                          'code_carriers','source_alternatives')):
        raise ValueError('standard-exception graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 15 or sum(r['size'] for r in m['state_data']) != 260 or
            {(r['member_offset'],r['symbol'],r['target_address'],r['size'])
             for r in m['state_data']} != STATE):
        raise ValueError('standard-exception loses complete defining data sections')
    if (m['sdk_layout']['source_section_size'] != 88 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS
            or set(m['sdk_layout']['headers']) != LAYOUT_HEADERS
            or set(m['vendor_sources']) != {'crt/src/exsup.inc'}):
        raise ValueError('standard-exception loses actual SDK or available source context')
    if m['retained_controls'] != [dict(evidence_id='R141',manifest='exception-frame-origin-evidence.json'),dict(evidence_id='R038',manifest='optimized-deleting-origin-evidence.csv')]:
        raise ValueError('standard-exception loses full retained independent R141/R038 graph')
    if m['standard_protocol'] != STANDARD_PROTOCOL or m['register_contracts'] != REGISTER_CONTRACTS:
        raise ValueError('standard-exception private ABI/SDK facts or unknowns differ')
    if m['retained_thunks']:
        raise ValueError('standard-exception changes independent compiler thunk ownership')
    for key, digest in METADATA_DIGESTS.items():
        if metadata_digest(m[key]) != digest:
            raise ValueError('standard-exception reviewed complete '+key+' inventory differs')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors']}}
    for row in graph.values():
        if row['code_regions'] != [dict(offset=0,size=row['size'])] or row['code_size'] != row['size']:
            raise ValueError('standard-exception loses complete code partition')
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] == 'import-thunk':
                raise ValueError('standard exception has no reviewed new import thunk')
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('standard-exception field lacks typed code/data/API provenance')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('standard-exception shared branch loses complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('standard-exception edge loses actual typed transfer')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('standard-exception defining data loses full typed provenance')
            if b['target_kind'] == 'code-entry':
                check_code_entry(b,graph)
    if m['source_weak_references'] != SOURCE_WEAK_REFERENCES:
        raise ValueError('standard-exception actual weak fallback records differ')
    check_standard_protocol(m, graph)
    return rows

def whole_defining_section(data,symbol,comparison,coff):
    """Read the entire section even when its vtable address point is interior."""
    _,entries = coff.parse_symbols(data,comparison.coff_name)
    found = [e for e in entries if e['symbol']==symbol and e['section']>0]
    if len(found) != 1:
        raise ValueError('whole defining data has no unique source anchor')
    entry = found[0]
    header = struct.unpack_from('<8sIIIIIIHHI',data,20+(entry['section']-1)*40)
    size,offset = header[3],header[4]
    if not size or not 0 <= entry['offset'] < size or not offset or offset+size>len(data):
        raise ValueError('whole defining initialized data extent differs')
    raw = data[offset:offset+size]
    definitions = [e for e in entries if e['section']==entry['section'] and e['storage'] in (2,3) and not e['symbol'].startswith('.')]
    symoff,count = struct.unpack_from('<II',data,8)
    stringoff = symoff+count*18
    strings = data[stringoff:stringoff+struct.unpack_from('<I',data,stringoff)[0]]
    indexed = {};index = 0
    while index < count:
        name,_,_,_,_,aux = struct.unpack_from('<8sIhHBB',data,symoff+index*18)
        indexed[index] = comparison.coff_name(name,strings)
        index += 1+aux
    fields = []
    for index in range(header[7]):
        field,target,typ = struct.unpack_from('<IIH',data,header[5]+index*10)
        if field+4>size or typ!=6 or target not in indexed:
            raise ValueError('whole defining data has unsupported typed field')
        fields.append(dict(offset=field,type='DIR32',symbol=indexed[target],addend=struct.unpack_from('<I',raw,field)[0]))
    return raw,dict(size=size,flags=f'0x{header[9]:08X}',definitions=definitions,relocations=fields),entry


def read_weak_reference(data,symbol,comparison,coff,member_offset):
    symoff,count = struct.unpack_from('<II',data,8)
    stringoff = symoff+count*18
    strings = data[stringoff:stringoff+struct.unpack_from('<I',data,stringoff)[0]]
    records = {};index = 0
    while index < count:
        name,value,section,typ,storage,aux = struct.unpack_from('<8sIhHBB',data,symoff+index*18)
        records[index] = (dict(symbol=comparison.coff_name(name,strings),offset=value,section=section,type=typ,storage=storage),aux)
        index += 1+aux
    found = [(index,d,aux) for index,(d,aux) in records.items() if d['symbol']==symbol and d['storage']==105]
    if len(found)!=1:
        raise ValueError('weak source reference lacks one actual COFF AUX record')
    index,d,aux = found[0]
    if aux!=1 or d['section']!=0 or d['offset']!=0:
        raise ValueError('weak source reference has unsupported COFF definition')
    tag,characteristics = struct.unpack_from('<II',data,symoff+(index+1)*18)
    fallback = records.get(tag)
    if not fallback or characteristics!=2 or fallback[0]['storage']!=2 or fallback[0]['section']!=0:
        raise ValueError('weak source reference changes actual search mode or fallback tag')
    definitions = coff.parse_symbols(data,comparison.coff_name)[1]
    strong = [e for e in definitions if e['symbol']==fallback[0]['symbol'] and e['storage']==2 and e['section']>0]
    if len(strong)!=1:
        raise ValueError('weak fallback lacks one complete defining source body')
    return dict(member_offset=member_offset,symbol=symbol,source_definition=d,symbol_index=index,auxiliary_count=aux,
                fallback_symbol=fallback[0]['symbol'],fallback_symbol_index=tag,fallback_reference=fallback[0],
                fallback_definition=strong[0],search_characteristics=characteristics,strong_archive_definitions=[])


def check_standard_protocol(m,graph):
    witnesses = lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required = {
        '0x006407B8': {('mov','dword ptr [ebp - 4], eax'),('xor','eax, eax'),('add','esp, 0x20')},
        '0x00640C12': {('mov','dword ptr [ebp - 8], eax'),('mov','dword ptr [ebp - 4], eax'),('lea','eax, [ebp - 0xc]'),('ret','8')},
        '0x00640C9A': {('mov','eax, dword ptr [edi + 8]'),('mov','dword ptr [esi + 8], eax'),('inc','eax'),('mov','dword ptr [esi + 4], eax'),('ret','4')},
        '0x00640CE4': {('cmp','dword ptr [ecx + 8], 0'),('push','dword ptr [ecx + 4]'),('call','0x642a61')},
        '0x00640DD6': {('cmp','esi, dword ptr [esp + 8]'),('call','0x640ce4'),('call','0x640c9a'),('ret','4')},
        '0x00640E49': {('push','0xe'),('call','0x646725'),('call','0x646658'),('call','0x640e86'),('mov','esi, dword ptr [esi + 4]')},
        '0x00640C4C': {('and','dword ptr [eax + 4], 0'),('and','dword ptr [eax + 8], 0')},
        '0x00640F15': {('jmp','0x642a61')},
        '0x00640CFA': {('mov','eax, dword ptr [ecx + 4]'),('mov','eax, 0x660ea0')},
    }
    for key,expected in required.items():
        if not expected <= witnesses(key):
            raise ValueError('standard-exception actual ownership/ABI/finally witness differs for '+key)
    cleanup = {'0x00640C12':8,'0x00640C9A':4,'0x00640DD6':4}
    for row in m['functions']:
        if any(r['cleanup']!=cleanup.get(row['address'],0) for r in row['body_facts']['returns']):
            raise ValueError('standard-exception observed callee cleanup differs')
    if graph['0x00640F15']['body_facts']['returns']:
        raise ValueError('operator delete gains fake return after free tail')
    actual = [dict(owner=r['address'],calls=r['indirect_calls'],jumps=r['indirect_jumps'])
              for r in m['functions']+m['auxiliary_bodies'] if r['indirect_calls'] or r['indirect_jumps']]
    if actual != m['runtime_dispatch']:
        raise ValueError('standard-exception RaiseException/dispatch inventory differs')
    binding = next((b for b in graph['0x00640C12']['relocation_bindings'] if b['target_kind']=='import'),None)
    if (not binding or binding['symbol']!='__imp__RaiseException@16' or binding['type']!='DIR32'
            or binding['target_address']!='0x00657184' or binding['dll']!='KERNEL32.dll'
            or binding['import_name']!='RaiseException'):
        raise ValueError('throw lacks actual complete RaiseException source/API identity')


def decode_code(row,raw,address,decoder):
    return [i for region in row['code_regions']
            for i in decoder.disasm(raw[region['offset']:region['offset']+region['size']],address+region['offset'])]

def check_scope_records(scope, data, raw, graph, decoded):
    if (scope['record_size'] != 12 or scope['size'] != data['size']
            or scope['size'] != 12*len(scope['records']) or data['writable']
            or scope['callbacks'] != data['relocations']):
        raise ValueError('scope loses complete readonly whole defining records/fields')
    expected_fields = set()
    for index, record in enumerate(scope['records']):
        enclosing, filter_ptr, handler = struct.unpack_from('<iII',raw,index*12)
        if (record != dict(index=index,enclosing=enclosing,
                           filter=f'0x{filter_ptr:08X}' if filter_ptr else None,handler=f'0x{handler:08X}')
                or not -1 <= enclosing < index or handler == 0):
            raise ValueError('scope record loses actual enclosing/filter/handler topology')
        for field_offset, value in ((index*12+4,filter_ptr),(index*12+8,handler)):
            if not value:
                continue
            expected_fields.add(field_offset)
            field = next((b for b in data['relocations'] if b['offset']==field_offset),None)
            if (not field or field['target_kind'] != 'code-entry'
                    or field['code_entry']['owner'] != scope['owner']
                    or int(field['target_address'],16) != value):
                raise ValueError('scope callback loses actual complete source owner')
            check_code_entry(field,graph)
            if value not in {i.address for i in decoded[scope['owner']]}:
                raise ValueError('scope callback is not an actual whole-parent instruction start')
    if expected_fields != {b['offset'] for b in data['relocations']}:
        raise ValueError('scope omits or fabricates typed callbacks')

def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('standard-exception loses complete origin-only extent')
    if (origin['evidence_id'] != 'R142' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('standard-exception canonical complete library acceptance differs')

def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('standard-exception shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R142' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('standard-exception shared entry gains unsupported standalone/source/exact credit')

def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('standard-exception external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('standard-exception member-local data reference changes its actual defining object')
    return dest

def object_code(path,row,comparison,coff):
    if row['extent_basis']=='function-auxiliary-record':
        return comparison.object_function(path,row['coff_symbol'])
    if row['extent_basis']!='whole-defining-code-section-without-AUX' or row['coff_symbol'] not in ('??_Gexception@@UAEPAXI@Z','??_Gtype_info@@UAEPAXI@Z'):
        raise ValueError('standard-exception source code loses own AUX or complete no-AUX control section')
    data = path.read_bytes();definitions = coff.parse_symbols(data,comparison.coff_name)[1]
    primary = next(d for d in definitions if d['symbol']==row['coff_symbol'] and d['section']>0)
    h = struct.unpack_from('<8sIIIIIIHHI',data,20+(primary['section']-1)*40)
    desc = dict(size=h[3],flags=f'0x{h[9]:08X}',definitions=[d for d in definitions if d['section']==primary['section']])
    if primary['offset']!=0 or desc!=row['source_code_section'] or h[3]!=row['size']:
        raise ValueError('compiler scalar control loses entire defining code section')
    return comparison.object_function(path,row['coff_symbol'],row['size'])


def check_interior_entry(label, parent, definitions, target_ins, source_ins):
    offset=label['source_offset'];base=int(parent['address'],16)
    if int(label['address'],16)!=base+offset or base+offset not in {i.address for i in target_ins}:
        raise ValueError('shared entry loses actual complete-owner instruction start')
    if label['source_symbol'] is not None:
        actual=next((d for d in definitions if d['symbol']==label['source_symbol']
                     and d['section']==parent['source_definition']['section']),None)
        if (actual!=label['source_definition'] or actual is None or actual['storage'] not in (2,3,6)
                or actual['offset']-parent['source_definition']['offset']!=offset):
            raise ValueError('shared entry loses actual full-owner defining source symbol')
    else:
        raise ValueError('standard-exception cleanup gains an invented source entry')
    if parent['source_definition']['offset'] + offset not in {i.address for i in source_ins}:
        raise ValueError('cleanup body label is not an actual source instruction start')
    entry = label['scope_entry_offset']
    if (offset != entry or base + entry not in {i.address for i in target_ins}
            or label['size'] != parent['size'] - offset):
        raise ValueError('cleanup label loses full parent tail or actual finally scope entry')

def check_catalog_entry(binding, catalog):
    entry = binding['code_entry']
    if not any(r['owner'] == entry['owner'] and r['member_offset'] == entry['source_member_offset']
               and r['source_offset'] == entry['source_offset'] and r['source_definition'] == entry['source_definition']
               and r['target_address'] == binding['target_address'] and r['source_definition']['symbol'] == binding.get('source_weak_reference',{}).get('fallback_symbol',binding['symbol'])
               for r in catalog):
        raise ValueError('typed code entry is absent from complete actual COFF definitions')

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
    layout_section = next(d['section'] for d in definitions if d['symbol']=='_StandardExceptionLayoutProbe')
    actual = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x40 and h[9]&0x40000000
              and not h[9]&0x20000000 and h[0].rstrip(b'\0') not in (b'.debug$S',b'.debug$T',b'.debug$F',b'.drectve')}
    if actual != expected | {layout_section}:
        raise ValueError('cold natural EH model loses an entire generated initialized section')
    owned = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['call_controls']}
    carriers = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['probe_generated_code']}
    code_sections = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x20}
    if owned & carriers or owned | carriers != code_sections:
        raise ValueError('cold natural model loses a complete generated code section')

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('standard_exception_old','verify-runtime-error-origins.py')
    c = module('standard_exception_target','compare-coff-function.py')
    archive_reader = module('standard_exception_archive','verify-runtime-origins.py')
    coff = module('standard_exception_coff','coff_data.py')
    startup = module('standard_exception_geometry','verify-startup-dependency-origins.py')
    record = module('standard_exception_ledger','verify-vendor-record-origins.py')
    facts = module('standard_exception_facts','verify-game-lifetime-origins.py')
    imports_module = module('standard_exception_imports','verify-import-origins.py')
    literal = module('standard_exception_scalar','verify-runtime-external-origins.py')
    sections = module('standard_exception_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete standard-exception source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('standard-exception complete primary loses an actual interior candidate')
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
            raise ValueError('standard-exception whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('standard-exception source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('standard-exception state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('standard-exception whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('standard-exception initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('standard-exception complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('standard-exception state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-standard-exception-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src','/Zc:wchar_t']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural standard-exception control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned standard-exception control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_StandardExceptionLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural standard-exception data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural exception/thread SDK offsets or ABI constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete standard-exception vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete standard-exception ABI/SEH/C++ controls differ')
        check_probe_generated(data,path,m,c,coff,old,decoder,facts)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R141'):
                    raise ValueError('standard-exception retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'] and d['section']>0)
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('standard-exception complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('standard-exception full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('standard-exception whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('standard-exception complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('standard-exception field lacks member-local/whole strong data provenance')
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
            raise ValueError('standard-exception code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('standard-exception local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('standard-exception direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('standard-exception direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('standard-exception same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('standard-exception shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('standard-exception complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('standard-exception data pointer does not reach a complete actual code entry')
        for label in m['interior_labels']+m['retained_labels']:
            parent = graph[label['parent']]
            path.write_bytes(member(parent))
            defs = coff.parse_symbols(member(parent),c.coff_name)[1]
            source,_=object_code(path,parent,c,coff)
            source_ins=list(decoder.disasm(source,parent['source_definition']['offset']))
            check_interior_entry(label,parent,defs,decoded[parent['address']],source_ins)
            if label['decision']=='retained':
                origin=origins[label['address']];function=functions[label['address']]
                if origin['evidence_id']!=label['origin_evidence'] or origin['origin']!='library' or int(function['size'])!=label['size'] or function['source_file'] or function['match_percent']!='0.00':
                    raise ValueError('retained shared entry gains unsupported new acceptance')
            elif not args.evidence_only:
                check_label(label,functions[label['address']],origins[label['address']],functions,origins,graph)
    for script in ('verify-exception-frame-origins.py','verify-optimized-deleting-origins.py'):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('retained independent full R141/R038 replay failed: '+result.stderr[-1500:])
    print('R142 origins OK: eight complete C++ throw/frame/standard exception primaries / 331 bytes / 20 fields; one existing finally entry; complete non-inventory what control / 13 bytes / one field; eleven full anchors / 641 bytes / 26 fields preserve nine library and two R038 compiler origins; fifteen whole template/vtable/RTTI/scope/literal data sections / 260 bytes / 18 fields including interior vtable address points and full five-byte base arrays; actual weak source AUX/search/fallback provenance; cold 88-byte SDK layout, 22 whole natural controls, eight whole generated data sections and three complete no-AUX code carriers; full retained R141/R038 cold replay; local origin-only acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
