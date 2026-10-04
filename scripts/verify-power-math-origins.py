#!/usr/bin/env python3
"""Replay R146 complete power dispatch, SSE/default parents, tables and shared entries."""
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
CONFIDENCE = 'complete-vendor-power-parent-carrier-table-dispatch-sdk-provenance'
LABEL_CONFIDENCE = 'interior-entry-in-complete-vendor-power-parent'
LAYOUT_OBJECTS = [{'symbol': '_PowerMathLayoutProbe',
  'offset': 0,
  'size': 104,
  'storage_span': 104,
  'values': [4, 4, 8, 32, 0, 4, 8, 16, 24, 10, 1, 2, 3, 4, 5, 6, 524319, 16, 8, 4, 2, 1, 768, 0, 1, 0]}]
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
 'crt/src/ctype.h',
 'crt/src/excpt.h',
 'crt/src/float.h',
 'crt/src/fpieee.h',
 'crt/src/malloc.h',
 'crt/src/math.h',
 'crt/src/stdarg.h',
 'crt/src/stddef.h',
 'crt/src/stdlib.h',
 'crt/src/string.h',
 'include/mmintrin.h',
 'include/tvout.h',
 'include/xmmintrin.h'}
METADATA_DIGESTS = {'functions': '328e56d5e11943ea2666edc486a6bb7a754bb8d08c5c244d268fcb29d1249eb3',
 'auxiliary_bodies': '19e4c90cda9d3b722984cf7e8bc642b10c1b042a243543f7a582ce982bc31c34',
 'anchors': '1c13fc7f6ef90cd8085d9afce3347f3bea0cd6fdbb84b6acb68ebfb409a89eeb',
 'interior_labels': '82e28e88d6f6d7d1686980a38859895ca7c4449802ce3582aea1ecc21964116a',
 'state_data': '9ac584e6d3c08ca2cc4316da3a807b5a06c73ac3eb66738e2aafbef0b8b2518f',
 'common_globals': '6cf7ae12695c3ebfc54b96df14fd92cc2e2894e73f2c5fdccdeabb18cf88b29e',
 'common_alternatives': 'd2c317cd1fd189ec308cd231dd9d123db933d76e5675eb46b5087f3a70b65ef3',
 'power_protocol': 'cc3bf9f4e1a63222f47dd2385b9d9cbbf3a8ed90a4c6dee7e9373b1d68fe9a5b',
 'register_contracts': '3f520e6484887b3c49936a35e39874e603bf9df87d4d9cca2a92eb1528727c68',
 'code_carriers': 'bbc855dc1d36234caad6417d7ba9ca75e1f1f6989625a28b0d7316e454d7f928',
 'source_alternatives': '9403e8c79528f28d58e02782b7a6cea06b7f3b66d891161d78b3462bbac8a371',
 'extent_reconciliations': 'fec3804a363c383f81c24155819858e67e09774657759949360e51f28466a533',
 'retained_source_controls': 'f257bad6b55f6f6997439727a762088c19777364ec304b4f07087c76323a918a',
 'call_controls': '10224d687e0454baeca5990c48de2162bbd3b47c8baf204dfc27257df691e5fd',
 'code_definitions': '446b141cd2bc3f696794b2ba88613bb80393a825ee71fcf9da048b6b06ed8abb',
 'state_uses': 'efc7908778036fe41ee6d40db59df4d8c565432afc81858fc9f52ef7ece11f1c'}

def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

prior = module('power_prior', 'verify-standard-exception-origins.py')
carrier_prior = module('power_carrier_prior', 'verify-vector-math-parent-origins.py')
check_code_entry = prior.check_code_entry
read_weak_reference = prior.read_weak_reference
decode_code = prior.decode_code
check_scope_records = prior.check_scope_records
resolve_state_reference = prior.resolve_state_reference
check_catalog_entry = prior.check_catalog_entry
object_code = prior.object_code
check_interior_entry = carrier_prior.check_interior_entry

def manifest():
    m = json.loads((ROOT / 'config/power-math-origin-evidence.json').read_text())
    identity = module('power_math_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R146' or m['target_sha256'] != identity.TARGET:
        raise ValueError('power-math target identity differs')
    return m

def verify_plan(m):
    rows = {r['address']:r for r in m['functions']}
    expected = {'0x00643770':('__CIpow',59,84), '0x0064DC60':('__CIpow_pentium4',2886,25)}
    if len(m['functions']) != 2 or set(rows) != set(expected):
        raise ValueError('bounded complete power cohort differs')
    for key,(symbol,size,ledger_size) in expected.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != ledger_size or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record'
                or row['code_regions'] != [dict(offset=0,size=size)]
                or int(row['span_end'],16) != int(key,16)+size-1):
            raise ValueError('power function loses complete own AUX extent')
    if any(m[k] for k in ('retained_labels','diagnostic_contexts','scope_tables','range_markers',
                          'initializer_registrations','callback_ranges','literal_controls',
                          'retained_thunks','probe_generated_data','probe_generated_code',
                          'source_weak_references')):
        raise ValueError('power graph gains unsupported dependencies')
    if (len(m['auxiliary_bodies']) != 5 or len(m['anchors']) != 9
            or len(m['interior_labels']) != 2 or len(m['state_data']) != 6
            or sum(r['size'] for r in m['state_data']) != 14862
            or len(m['common_globals']) != 1 or len(m['code_carriers']) != 1
            or len(m['source_alternatives']) != 3
            or m['retained_controls'] != [dict(evidence_id='R130',manifest='vector-math-parent-origin-evidence.json')]
            or m['sdk_layout']['source_section_size'] != 104
            or m['sdk_layout']['objects'] != LAYOUT_OBJECTS
            or set(m['sdk_layout']['headers']) != LAYOUT_HEADERS or m['vendor_sources']):
        raise ValueError('power full source/data/SDK/retained extent inventory differs')
    for key,digest in METADATA_DIGESTS.items():
        if metadata_digest(m[key]) != digest:
            raise ValueError('reviewed complete power '+key+' inventory differs')
    graph = {**rows,**{r['address']:r for r in m['auxiliary_bodies']+m['anchors']}}
    for row in m['functions']+m['auxiliary_bodies']:
        if (row['code_regions'] != [dict(offset=0,size=row['size'])]
                or row['code_size'] != row['size'] or row['indirect_calls'] or row['indirect_jumps']):
            raise ValueError('power graph loses full code or gains unresolved dispatch')
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b,graph)
            elif b['target_kind'] != 'state' or b['type'] != 'DIR32':
                raise ValueError('power typed field loses independent code/data provenance')
    for label in m['interior_labels']:
        parent = graph[label['parent']]
        if (label['decision'] != 'library' or label['extent_basis'] != 'interior-entry-in-complete-vendor-primary'
                or int(label['address'],16) != int(label['parent'],16)+label['source_offset']
                or label['size']+label['source_offset'] != parent['size']):
            raise ValueError('power entry loses its complete defining parent/tail')
    check_power_protocol(m,graph)
    return rows


def check_power_protocol(m,graph):
    root = graph['0x00643770']; sse = graph['0x0064DC60']; default = graph['0x006437AB']
    witness = lambda row: {(w['mnemonic'],w['operands']) for w in row['instruction_witnesses']}
    if not {('cmp','dword ptr [0x68fba0], 0'),('je','0x6437ab'),
            ('stmxcsr','dword ptr [esp + 4]'),('and','eax, 0x1f80'),('cmp','eax, 0x1f80'),
            ('fnstcw','word ptr [esp]'),('and','ax, 0x7f'),('cmp','ax, 0x7f'),
            ('lea','esp, [esp + 8]'),('jne','0x6437ab'),('jmp','0x64dc60')} <= witness(root):
        raise ValueError('power wrapper loses actual SSE/x87 mask/default dispatch')
    if (not {('fxch','st(1)'),('fstp','qword ptr [esp]'),('fstp','qword ptr [esp + 8]'),
             ('and','esp, 0xfffffff0'),('call','0x64dc79')} <= witness(sse)
            or sse['instruction_witnesses'][10] != dict(site='0x0064DC79',mnemonic='movlpd',operands='xmm0, qword ptr [esp + 4]')):
        raise ValueError('power SSE intrinsic loses its actual exported +25 stack entry')
    if not {('fxch','st(1)'),('fstp','qword ptr [esp]'),('fst','qword ptr [esp + 8]'),
            ('mov','eax, dword ptr [esp + 0xc]'),('call','0x6437cd'),
            ('mov','ecx, eax'),('cmp','word ptr [esp], 0x27f')} <= witness(default):
        raise ValueError('power fallback loses full CI/C/static-start register protocol')
    table = next(r for r in m['state_data'] if r['member_offset']==2835570)
    if (table['size'] != 14640 or table['target_address'] != '0x00663A00'
            or table['source_anchor']['symbol'] != 'SIGMASK' or table['source_anchor']['offset'] != 14480
            or table['source_section']['relocations']):
        raise ValueError('power constant anchor loses its entire actual defining table section')


def link_complete(source,fields,row,state_map,imports,startup,graph,catalog):
    """Link independently defined fields and compare complete source bytes unmasked."""
    metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
    expected = [{k:b[k] for k in ('offset','type','symbol','addend','local_symbol_offset')}
                for b in row['relocation_bindings']]
    if len(source) != row['size'] or metadata != expected:
        raise ValueError('complete power relocation topology differs')
    linked = bytearray(source); covered = set(); a = int(row['address'],16)
    for field,binding in zip(fields,row['relocation_bindings']):
        off = field['offset']; span = set(range(off,off+4))
        if field['type'] not in ('DIR32','REL32') or off<0 or off+4>len(source) or span&covered:
            raise ValueError('power typed field overlaps or escapes its complete extent')
        covered |= span
        if binding['target_kind'] in ('callee','code-entry'):
            check_code_entry(binding,graph); check_catalog_entry(binding,catalog)
            entry = binding['code_entry']; owner = graph[entry['owner']]
            dest = int(owner['address'],16)+entry['source_offset']
        elif binding['target_kind'] == 'state':
            dest = state_map.get((row['member_offset'],field['symbol']))
            if dest is None or field['type'] != 'DIR32':
                raise ValueError('power field lacks an independent whole defining data owner')
        else:
            raise ValueError('power field has no independently reviewed binding')
        if dest != int(binding['target_address'],16):
            raise ValueError('power field cannot override the independent source owner')
        value = dest+field['addend']
        if field['type'] == 'REL32':value -= a+off+4
        struct.pack_into('<I',linked,off,value&0xffffffff)
    return bytes(linked)


def check_retained_source(m,origins,functions):
    prior_manifest = json.loads((ROOT/'config/vector-math-parent-origin-evidence.json').read_text())
    for row in m['anchors']:
        key = row['address']
        if key in functions:
            origin = origins[key]
            if origin['origin'] != row['origin'] or origin['evidence_id'] != row['origin_evidence']:
                raise ValueError('retained complete power code origin differs')
        else:
            if key not in {r['address'] for r in m['retained_source_controls']}:
                raise ValueError('non-inventory power anchor has no independent complete prior source control')
        if row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R130':
            raise ValueError('power loses independently replayed full R130 anchor')
    for control in m['retained_source_controls']:
        row = next(r for r in m['anchors']+m['auxiliary_bodies'] if r['address']==control['address'])
        old = next(r for r in prior_manifest['auxiliary_bodies'] if r['address']==control['address'])
        for key in ('member_offset','coff_symbol','size','source_sha256','body_sha256'):
            if row[key] != old[key] or row[key] != control[key]:
                raise ValueError('power loses complete retained non-inventory source owner')
    return prior_manifest


def check_common_provenance(m,members,c,coff):
    retained = json.loads((ROOT/'config/vector-math-parent-origin-evidence.json').read_text())
    for row in m['common_globals']:
        proof = next(r for r in m['common_alternatives'] if r['symbol']==row['symbol'])
        old = next(r for r in retained['common_globals'] if r['symbol']==row['symbol'])
        if old != row or old != proof['retained_definition'] or proof['retained_evidence_id'] != 'R130':
            raise ValueError('power SSE COMMON loses independent full R130 provenance')
        actual = []
        for off,(_,data) in members.items():
            try:defs = coff.parse_symbols(data,c.coff_name)[1]
            except ValueError:continue
            actual.extend(dict(member_offset=off,source_definition=d) for d in defs
                          if d['symbol']==row['symbol'] and d['storage']==2
                          and (d['section']!=0 or d['offset']>0))
        if (actual != proof['definitions'] or actual != [dict(member_offset=row['member_offset'],source_definition=row['source_definition'])]):
            raise ValueError('power SSE COMMON has an unreviewed whole-archive alternative')


def check_alternative(row,path,members,c,coff,target):
    name,data = members[row['member_offset']]
    if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
        raise ValueError('complete power alternative member identity differs')
    path.write_bytes(data)
    raw,fields = carrier_prior.whole_code_section(data,row,c,coff)
    actual = c.pe_bytes_at(target,int(row['address'],16),row['size'])
    mask = {i for f in fields for i in range(f['offset'],f['offset']+4)}
    differences = [i for i in range(len(raw)) if i not in mask and raw[i]!=actual[i]]
    if (row['decision'] != 'rejected-whole-section-alternative' or not differences
            or differences != row['non_field_difference_offsets'] or len(fields)!=row['relocation_count']
            or hashlib.sha256(raw).hexdigest()!=row['source_sha256']
            or hashlib.sha256(actual).hexdigest()!=row['body_sha256']):
        raise ValueError('full power alternative no longer distinguishes the source family')
    wrapper = row['wrapper']; body,fields = c.object_function(path,wrapper['coff_symbol'])
    actual = c.pe_bytes_at(target,int(wrapper['target_address'],16),wrapper['size'])
    mask = {i for f in fields for i in range(f['offset'],f['offset']+4)}
    metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
    if (len(body)!=wrapper['size'] or hashlib.sha256(body).hexdigest()!=wrapper['source_sha256']
            or metadata!=wrapper['relocation_metadata']
            or [i for i in range(len(body)) if i not in mask and body[i]!=actual[i]]!=wrapper['non_field_difference_offsets']):
        raise ValueError('whole same-shaped wrapper alternative evidence differs')


def whole_defining_section(data,symbol,comparison,coff):
    definitions = coff.parse_symbols(data,comparison.coff_name)[1]
    found = [d for d in definitions if d['symbol']==symbol and d['section']>0]
    if len(found) != 1:
        raise ValueError('power whole data lacks one actual defining anchor')
    anchor = found[0]
    header = struct.unpack_from('<8sIIIIIIHHI',data,20+(anchor['section']-1)*40)
    if header[9]&0x80:
        # Complete uninitialized storage has no initialized source byte pointer.
        old = module('power_uninitialized_data','verify-runtime-error-origins.py')
        raw,desc = old.whole_section(data,symbol,comparison,coff)
        if raw is not None or anchor['offset'] != 0:
            raise ValueError('power whole uninitialized data anchor/storage differs')
        return raw,desc,anchor
    return prior.whole_defining_section(data,symbol,comparison,coff)

def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('power-math loses complete origin-only extent')
    if (origin['evidence_id'] != 'R146' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('power-math canonical complete library acceptance differs')

def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('power-math shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R146' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('power-math shared entry gains unsupported standalone/source/exact credit')

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
    layout_section = next(d['section'] for d in definitions if d['symbol']=='_PowerMathLayoutProbe')
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
    old = module('power_math_old','verify-runtime-error-origins.py')
    c = module('power_math_target','compare-coff-function.py')
    archive_reader = module('power_math_archive','verify-runtime-origins.py')
    coff = module('power_math_coff','coff_data.py')
    startup = module('power_math_geometry','verify-startup-dependency-origins.py')
    record = module('power_math_ledger','verify-vendor-record-origins.py')
    facts = module('power_math_facts','verify-game-lifetime-origins.py')
    imports_module = module('power_math_imports','verify-import-origins.py')
    literal = module('power_math_scalar','verify-runtime-external-origins.py')
    sections = module('power_math_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete power-math source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('power-math complete primary loses an actual interior candidate')
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
            raise ValueError('power-math whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('power-math source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('power-math state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('power-math whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('power-math initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('power-math complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('power-math state loses whole writable target storage')
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
    check_common_provenance(m,members,c,coff)
    check_retained_source(m,origins,functions)
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-power-math-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src','/Zc:wchar_t']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural power-math control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned power-math control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_PowerMathLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural power-math data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural exception/thread SDK offsets or ABI constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete power-math vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete power-math ABI/SEH/C++ controls differ')
        check_probe_generated(data,path,m,c,coff,old,decoder,facts)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'] and d['section']>0)
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('power-math complete own source extent/hash differs')
            if row['decision'] == 'anchor':
                old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            elif link_complete(source,fields,row,state_map,imports,startup,graph,m['code_definitions']) != actual:
                raise ValueError('complete power relocated source/target bytes differ')
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('power-math full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('power-math whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('power-math complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('power-math field lacks member-local/whole strong data provenance')
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
            raise ValueError('power-math code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('power-math local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('power-math direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('power-math direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('power-math same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('power-math shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('power-math complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('power-math data pointer does not reach a complete actual code entry')
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
        for carrier in m['code_carriers']:
            data = member(carrier)
            carrier_prior.verify_code_carrier(carrier,data,target,c,coff,old,graph)
            raw,fields = carrier_prior.whole_code_section(data,carrier,c,coff)
            if link_complete(raw,fields,carrier,state_map,imports,startup,graph,m['code_definitions']) != c.pe_bytes_at(target,int(carrier['address'],16),carrier['size']):
                raise ValueError('whole power carrier loses complete independently relocated bytes')
        for alternative in m['source_alternatives']:
            check_alternative(alternative,path,members,c,coff,target)
    for script in ('verify-vector-math-parent-origins.py',):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('retained independent full R130 replay failed: '+result.stderr[-1500:])
    print('R146 origins OK: two complete power primaries / 2945 bytes / 61 fields; two existing actual SSE/default shared entries; five whole auxiliary controls / 787 bytes / 32 fields; nine independently retained full anchors / 1957 bytes / 66 fields; whole 650-byte pow wrapper/default carrier and actual zero-AUX NOP; six whole data sections / 14862 bytes / four fields including complete 14640-byte pow table at an interior SIGMASK anchor; independently retained SSE COMMON; three rejected full atan/log/log10 source carriers preserve equal-shaped wrapper ambiguity until actual complete operation binding; cold actual 104-byte SDK layout / five controls / 160 bytes / three fields / 77 pinned headers; full retained R130 cold replay; local origin-only acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
