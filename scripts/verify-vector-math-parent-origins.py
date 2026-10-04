#!/usr/bin/env python3
"""Replay the bounded R130 vector/math parent, math exception and array construction graph."""
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
ACCEPTED = {'0x00641C78': ('??_L@YGXPAXIHP6EX0@Z1@Z', 98), '0x00647362': ('__handle_qnan2', 95), '0x00647479': ('__except2', 201), '0x00641FD0': ('_log10', 63), '0x00642120': ('_ceil', 64), '0x00648140': ('__CIlog10_pentium4', 644), '0x006485D7': ('___libm_error_support', 654), '0x00648865': ('__ceil_default', 211), '0x0064E81E': ('__powhlp', 354), '0x0064E7B0': ('__d_inttype', 110), '0x0065151B': ('__frnd', 17)}
LEDGER_SIZES = {'0x00641C78': 74, '0x00647362': 95, '0x00647479': 201, '0x00641FD0': 152, '0x00642120': 285, '0x00648140': 24, '0x006485D7': 654, '0x00648865': 211, '0x0064E81E': 354, '0x0064E7B0': 110, '0x0065151B': 17}
AUXILIARIES = {'0x00642010': ('__CIlog10', 59), '0x0064204B': ('__CIlog10_default', 213), '0x00642160': ('__ceil_pentium4', 221), '0x00646BEE': ('__fast_exit', 13), '0x00646A73': ('_$$$00003', 215), '0x006483D0': ('_$$$00001', 519), '0x00650F81': ('__safe_fdivr', 21), '0x00650790': ('_fdiv_main_routine', 279), '0x006508A7': ('__adj_fdiv_r', 1183)}
LABELS = {'0x00641CC2': ('0x00641C78', 24, 74, '$L322'), '0x00648158': ('0x00648140', 6, 24, '__log10_pentium4'), '0x0064815E': ('0x00648140', 614, 30, None)}
STATE = {(2486736, '__indefinite', '0x00670270', 44), (2864098, '??_C@_04MLLJIGOK@atan?$AA@', '0x006616C8', 5), (2864098, '??_C@_04GFPJNGEK@ceil?$AA@', '0x006616A4', 5), (2864098, '??_C@_04HPAFEEIN@exp2?$AA@', '0x00662128', 5), (2864098, '??_C@_03KHJOGHMM@exp?$AA@', '0x0065D530', 4), (2721394, 'LOG_name', '0x0066FF00', 8), (2864098, '??_C@_04KGLCPMCP@log2?$AA@', '0x00662138', 5), (2555558, '__real@3ff0000000000000', '0x00657D00', 8), (2864098, '??_C@_03MGHMBJCF@log?$AA@', '0x0065D52C', 4), (2555558, '_newcw', '0x00670650', 4), (2686488, '__real@3ff0000000000000', '0x00657D00', 8), (365830, '$T327', '0x00660F00', 12), (2864098, '??_C@_05EOHGHCHD@exp10?$AA@', '0x00662130', 6), (2864098, '??_C@_05PBJFFIGL@floor?$AA@', '0x0066169C', 6), (2799558, '_One', '0x00660F30', 72), (2505946, '__infinity', '0x006705F0', 90), (2686488, '__real@4000000000000000', '0x006583F0', 8), (2864098, '__pmatherr', '0x0067064C', 4), (2864098, '??_C@_04EHEDPDJG@modf?$AA@', '0x0066168C', 5), (2930386, '__matherr_flag', '0x00670CD8', 4), (2530034, 'fdiv_risc_table', '0x00670D50', 352), (2559836, 'One', '0x00661600', 68), (2432134, '___fastflag', '0x0068E2C0', 8), (2864098, '??_C@_03JGHBODFD@pow?$AA@', '0x00661700', 4), (2686488, '__real@0000000000000000', '0x0065F4C8', 8), (2864098, '??_C@_05HGHHAHAP@log10?$AA@', '0x006616F8', 6), (1236214, '___security_cookie', '0x0066FE30', 4), (2931994, '__d_inf', '0x00670388', 40), (2828512, 'emask', '0x006617A0', 2336)}
LAYOUT_OBJECTS = [{'symbol': '_VectorMathParentLayoutProbe', 'offset': 0, 'size': 52, 'storage_span': 52, 'values': [4, 4, 8, 32, 0, 4, 8, 16, 24, 4, 10, 1, 0]}]
LAYOUT_HEADERS = {'PlatformSDK/Include/WinBase.h', 'crt/src/fpieee.h', 'crt/src/math.h', 'PlatformSDK/Include/WinNT.h'}
CALLBACK_CONTROL = {'coff_symbol': '_VectorMathParentCallbackProbe@8', 'size': 13, 'source_sha256': '3b90c5d57fa4656263948a91f0fafbbbd3f4e275dfc1140459c441f9e0fd38ea', 'body_facts': {'returns': [{'site': '0x0000000A', 'cleanup': 8}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 0xc]'}, {'site': '0x00000009', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000000A', 'mnemonic': 'ret', 'operands': '8'}]}
CONFIDENCE = 'complete-vendor-vector-math-parent-code-data-dispatch-abi-provenance'
LABEL_CONFIDENCE = 'interior-entry-in-complete-vendor-vector-math-parent'

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/vector-math-parent-origin-evidence.json').read_text())
    identity = module('vector_math_parent_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R130' or m['target_sha256'] != identity.TARGET:
        raise ValueError('FP dispatch target identity differs')
    return m


def check_code_entry(binding, graph):
    entry = binding['code_entry']; owner = graph.get(entry['owner'])
    if not owner or owner['decision'] not in ('library','library-control','anchor'):
        raise ValueError('dispatch retains an unreviewed actual code entry')
    source = entry['source_definition']; primary = owner['source_definition']
    if (entry['source_member_offset'] != owner['member_offset']
            or source['symbol'] != binding['symbol'] or source['section'] != primary['section']
            or source['offset'] - primary['offset'] != entry['source_offset']
            or source['storage'] not in (2,3,6)
            or not 0 <= entry['source_offset'] < owner['size']
            or int(binding['target_address'],16) != int(owner['address'],16) + entry['source_offset']):
        raise ValueError('dispatch code pointer loses its actual defining source owner/entry')


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 11 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete vector/math parent cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != ('whole-defining-code-section' if key=='0x00641C78' else 'function-auxiliary-record')
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('vector/math parent function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=9 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('vector/math parent loses complete auxiliary owners')
    if (len(m['interior_labels']) != 3 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('vector/math parent shared entries lose complete source parents or gain standalone credit')
    if len(m['anchors']) != 21 or sum(r['size'] for r in m['anchors']) != 2430:
        raise ValueError('vector/math parent independent complete anchors differ')
    if any(m[k] for k in ('scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('vector/math parent graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 29 or sum(r['size'] for r in m['state_data']) != 3133
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('vector/math parent graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 52 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural vector/math parent operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R129',manifest='short-runtime-origin-evidence.json')]:
        raise ValueError('vector/math parent loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('vector/math parent graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('vector/math parent shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('vector/math parent direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('vector/math parent table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    check_carrier_plan(m, graph)
    alternatives = [(r['address'],r['symbol'],r['size'],len(r['non_field_difference_offsets']))
                    for r in m['source_alternatives']]
    if alternatives != [('0x00641FD0','_atan',282,74),('0x00641FD0','_log',336,3),
                        ('0x00642120','_modf',328,223),('0x00642120','_floor',289,33)]:
        raise ValueError('whole source alternatives lose actual distinguishing bodies')
    return rows


def check_parent_protocol(m, graph):
    expected = dict(vector_parent='0x00641C78',vector_size=98,vector_cleanup_offset=74,
        constructor_callback='dword ptr [ebp + 0x14]',unwind_callback_parameter='dword ptr [ebp + 0x18]',
        constructor_receiver='ecx, esi',vector_return_bytes=20,log10_carrier_size=336,ceil_carrier_size=285,
        log10_c_entry_offset=24,log10_core_offset=30,libm_error_support='0x006485D7',
        default_matherr='0x006506C2',default_matherr_slot='0x0067064C',fdiv_dispatch_entries=64)
    if m['parent_protocol']!=expected or m['callback_control']!=CALLBACK_CONTROL:
        raise ValueError('vector/math parent callback/operand/dispatch protocol differs')
    witnesses = lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    vector=graph['0x00641C78']
    required={('mov','ecx, esi'),('cmp','eax, dword ptr [ebp + 0x10]'),
        ('add','esi, dword ptr [ebp + 0xc]'),('inc','dword ptr [ebp - 0x1c]'),
        ('ret','0x14'),('push','dword ptr [ebp + 0x18]'),('push','dword ptr [ebp - 0x1c]')}
    if (not required<=witnesses(vector['address']) or len(vector['indirect_calls'])!=1
            or vector['indirect_calls'][0]['operand']!=expected['constructor_callback'] or vector['indirect_jumps']):
        raise ValueError('constructor loses actual count/receiver/callback/unwind/stdcall provenance')
    scope=next(r for r in m['state_data'] if r['symbol']=='$T327')
    if (scope['size']!=12 or len(scope['relocations'])!=1 or scope['relocations'][0]['offset']!=8
            or scope['relocations'][0]['code_entry']['owner']!=vector['address']
            or scope['relocations'][0]['code_entry']['source_offset']!=74):
        raise ValueError('constructor scope loses complete actual cleanup binding')
    if not {('fld','qword ptr [ebp + 0xc]'),('fadd','qword ptr [ebp + 0x14]'),
            ('push','dword ptr [ebp + 0x1c]')}<=witnesses('0x00647362'):
        raise ValueError('qnan2 loses both actual operand slots/control word')
    if not {('fld','qword ptr [ebp + 0x10]'),('fld','qword ptr [ebp + 0x18]'),
            ('fld','qword ptr [ebp + 0x20]'),('push','dword ptr [ebp + 0x28]')}<=witnesses('0x00647479'):
        raise ValueError('except2 loses both actual operands/result/control word')
    callback=next(r for r in m['state_data'] if r['symbol']=='__pmatherr')
    if (callback['size']!=4 or len(callback['relocations'])!=1
            or callback['relocations'][0]['target_kind']!='code-entry'
            or callback['relocations'][0]['target_address']!='0x006506C2'
            or callback['relocations'][0]['code_entry']['owner']!='0x006506C2'
            or len(graph['0x006485D7']['indirect_calls'])!=3
            or any(b['operand']!='dword ptr [0x67064c]' for b in graph['0x006485D7']['indirect_calls'])):
        raise ValueError('libm error support loses actual initialized default matherr pointer/calls')
    table=next(r for r in m['state_data'] if r['symbol']=='fdiv_risc_table')
    if (table['size']!=352 or len(table['relocations'])!=64
            or [b['offset'] for b in table['relocations']]!=list(range(94,350,4))
            or any(b['target_kind']!='code-entry' or b['code_entry']['owner']!='0x006508A7' for b in table['relocations'])
            or graph['0x006508A7']['indirect_jumps']!=[dict(site='0x006508AD',operand='dword ptr [eax*4 + 0x670dae]')]):
        raise ValueError('fdiv loses complete 64-entry source dispatch/owner')
    common=m['common_globals']
    if (len(common)!=1 or common[0]['symbol']!='___use_sse2_mathfcns' or common[0]['size']!=4
            or common[0]['target_address']!='0x0068FBA0'
            or common[0]['source_definition']!=dict(symbol='___use_sse2_mathfcns',offset=4,section=0,type=0,storage=2)):
        raise ValueError('SSE2 flag loses complete COMMON/loader provenance')
    retained=m['retained_labels']
    if (len(retained)!=1 or retained[0]['address']!='0x00646B43' or retained[0]['parent']!='0x00646A73'
            or retained[0]['size']!=7 or retained[0]['source_offset']!=208 or retained[0]['origin_evidence']!='R127'
            or retained[0]['decision']!='retained' or retained[0]['source_symbol']!='__rtchsifneg'):
        raise ValueError('retained R127 shared entry gains duplicate credit or loses full owner')
    if m['diagnostic_contexts']:
        raise ValueError('vector/math parent graph gains unresolved code dependencies')


def check_carrier_plan(m, graph):
    expected=[('0x00641FD0','_log10',336,[('0x00641FD0',0,63),('0x00642010',64,59),('0x0064204B',123,213)],[(63,1)]),
              ('0x00642120','_ceil',285,[('0x00642120',0,64),('0x00642160',64,221)],[])]
    if len(m['code_carriers'])!=2:
        raise ValueError('full code carriers cannot be replaced with primary prefixes')
    for row,(address,symbol,size,components,gaps) in zip(m['code_carriers'],expected):
        if (row['address']!=address or row['symbol']!=symbol or row['size']!=size
                or [(c['owner'],c['offset'],c['size']) for c in row['components']]!=components
                or [(g['offset'],g['size']) for g in row['gaps']]!=gaps):
            raise ValueError('full code carrier loses every complete source owner/alignment byte')
        coverage=set(); fields=[]
        for part in row['components']:
            owner=graph.get(part['owner'])
            if (not owner or owner['size']!=part['size'] or owner['member_offset']!=row['member_offset']
                    or owner['source_definition']['section']!=row['source_section']['number']
                    or owner['source_definition']['offset']!=part['offset']
                    or int(owner['address'],16)!=int(row['address'],16)+part['offset']):
                raise ValueError('carrier component loses its complete own source AUX extent')
            span=set(range(part['offset'],part['offset']+part['size']))
            if coverage&span:raise ValueError('carrier owns overlapping source extents')
            coverage.update(span)
            for binding in owner['relocation_bindings']:
                binding=dict(binding);binding['offset']+=part['offset']
                if binding['local_symbol_offset'] is not None:binding['local_symbol_offset']+=part['offset']
                fields.append(binding)
        for gap in row['gaps']:coverage.update(range(gap['offset'],gap['offset']+gap['size']))
        if coverage!=set(range(size)) or fields!=row['relocation_bindings']:
            raise ValueError('carrier loses complete bytes or typed fields across all own extents')


def check_code_section(row, data, coff, comparison):
    definitions=coff.parse_symbols(data,comparison.coff_name)[1]
    primary=next(d for d in definitions if d['symbol']==row['coff_symbol'])
    header=struct.unpack_from('<8sIIIIIIHHI',data,20+(primary['section']-1)*40)
    section=dict(size=header[3],flags=f'0x{header[9]:08X}',
                 definitions=[d for d in definitions if d['section']==primary['section']])
    global_functions=[d for d in section['definitions'] if d['storage']==2 and d['type']==32]
    if (section!=row['source_code_section'] or header[3]!=row['size'] or primary['offset']
            or primary['type']!=32 or primary['storage']!=2 or global_functions!=[primary]
            or not header[9]&0x20 or not header[9]&0x20000000
            or not header[9]&0x40000000 or header[9]&0x80000000):
        raise ValueError('aux-less vector constructor loses its entire sole defining code section')


def object_code(path, row, comparison, coff):
    if row['extent_basis']=='function-auxiliary-record':
        return comparison.object_function(path,row['coff_symbol'])
    if row['extent_basis']!='whole-defining-code-section' or row['address']!='0x00641C78':
        raise ValueError('unsupported complete code extent basis')
    check_code_section(row,path.read_bytes(),coff,comparison)
    try:
        comparison.object_function(path,row['coff_symbol'])
    except ValueError as error:
        if str(error)!='function symbol lacks a definition auxiliary record':
            raise
    else:
        raise ValueError('whole-section vector control unexpectedly gains an AUX extent')
    return comparison.object_function(path,row['coff_symbol'],row['source_code_section']['size'])


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
        if (label['source_definition'] is not None or offset!=30 or label['entry_call_offset']!=17
                or label['predecessor_offset']!=24
                or label['source_entry_basis']!='internal-call-and-C-entry-fallthrough'):
            raise ValueError('unnamed log10 core gains an invented source definition')
        source_base=parent['source_definition']['offset']
        call=next((i for i in source_ins if i.address==source_base+17),None)
        target_call=next((i for i in target_ins if i.address==base+17),None)
        predecessor=next((i for i in source_ins if i.address==source_base+24),None)
        if (not call or call.mnemonic!='call' or call.operands[0].type!=X86_OP_IMM
                or call.operands[0].imm!=source_base+30 or not target_call or target_call.operands[0].imm!=base+30
                or not predecessor or predecessor.mnemonic!='movlpd' or predecessor.size!=6
                or predecessor.address+predecessor.size!=source_base+30):
            raise ValueError('unnamed log10 core loses actual call/C-entry fallthrough')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('vector/math parent loses complete origin-only extent')
    if (origin['evidence_id'] != 'R130' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('vector/math parent canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('vector/math parent shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R130' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('vector/math parent shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('vector/math parent external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('vector/math parent member-local data reference changes its actual defining object')
    return dest


def whole_code_section(data, carrier, comparison, coff):
    definitions=coff.parse_symbols(data,comparison.coff_name)[1]
    primary=next(d for d in definitions if d['symbol']==carrier['symbol'] and d['section']>0)
    header=struct.unpack_from('<8sIIIIIIHHI',data,20+(primary['section']-1)*40)
    descriptor=dict(number=primary['section'],size=header[3],flags=f'0x{header[9]:08X}',
                    definitions=[d for d in definitions if d['section']==primary['section']])
    if (primary['offset'] or descriptor!=carrier['source_section'] or header[3]!=carrier['size']
            or not header[9]&0x20 or not header[9]&0x20000000 or not header[9]&0x40000000 or header[9]&0x80000000):
        raise ValueError('whole defining code carrier/source header differs')
    raw=bytearray(data[header[4]:header[4]+header[3]])
    if len(raw)!=header[3]:raise ValueError('truncated whole source code carrier')
    symbol_offset,count=struct.unpack_from('<II',data,8);strings_offset=symbol_offset+18*count
    strings=data[strings_offset:strings_offset+struct.unpack_from('<I',data,strings_offset)[0]]
    indexed={};index=0
    while index<count:
        name,value,section,typ,storage,aux=struct.unpack_from('<8sIhHBB',data,symbol_offset+18*index)
        indexed[index]=(comparison.coff_name(name,strings),value,section)
        index+=1+aux
    fields=[]
    for index in range(header[7]):
        offset,target,typ=struct.unpack_from('<IIH',data,header[5]+10*index)
        if offset+4>len(raw) or typ not in (6,20) or target not in indexed:
            raise ValueError('whole code carrier has unsupported/cross-boundary typed fields')
        name,value,section=indexed[target]
        fields.append(dict(offset=offset,type_id=typ,type='DIR32' if typ==6 else 'REL32',symbol=name,
            addend=struct.unpack_from('<I',raw,offset)[0],local_symbol_offset=value if section==primary['section'] else None))
    return raw,fields


def verify_code_carrier(carrier, data, target, comparison, coff, old, graph):
    raw,fields=whole_code_section(data,carrier,comparison,coff)
    a=int(carrier['address'],16);actual=comparison.pe_bytes_at(target,a,carrier['size'])
    if hashlib.sha256(raw).hexdigest()!=carrier['source_sha256'] or hashlib.sha256(actual).hexdigest()!=carrier['body_sha256']:
        raise ValueError('full code carrier source/target hashes differ')
    old.compare_fields(raw,fields,actual,a,carrier['relocation_bindings'],comparison)
    if [f['local_symbol_offset'] for f in fields]!=[b['local_symbol_offset'] for b in carrier['relocation_bindings']]:
        raise ValueError('full code carrier loses every local typed field')
    for gap in carrier['gaps']:
        if raw[gap['offset']:gap['offset']+gap['size']]!=b'\x90' or actual[gap['offset']:gap['offset']+gap['size']]!=b'\x90':
            raise ValueError('source-emitted alignment NOP differs')
        # The vendor's zero-length AUX is alignment, not a one-byte function.
        symbol_offset,count=struct.unpack_from('<II',data,8);strings_offset=symbol_offset+18*count
        strings=data[strings_offset:strings_offset+struct.unpack_from('<I',data,strings_offset)[0]];index=0;found=False
        while index<count:
            name,value,section,typ,storage,aux=struct.unpack_from('<8sIhHBB',data,symbol_offset+18*index)
            if comparison.coff_name(name,strings)=='_$$$00002':
                found=(value==63 and section==carrier['source_section']['number'] and typ==32 and aux>=1
                       and struct.unpack_from('<I',data,symbol_offset+18*(index+1)+4)[0]==0)
            index+=1+aux
        if not found:raise ValueError('alignment marker loses its actual zero-length function AUX')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('vector_math_parent_old','verify-runtime-error-origins.py')
    c = module('vector_math_parent_target','compare-coff-function.py')
    archive_reader = module('vector_math_parent_archive','verify-runtime-origins.py')
    coff = module('vector_math_parent_coff','coff_data.py')
    startup = module('vector_math_parent_geometry','verify-startup-dependency-origins.py')
    record = module('vector_math_parent_ledger','verify-vendor-record-origins.py')
    facts = module('vector_math_parent_facts','verify-game-lifetime-origins.py')
    imports_module = module('vector_math_parent_imports','verify-import-origins.py')
    literal = module('vector_math_parent_scalar','verify-runtime-external-origins.py')
    sections = module('vector_math_parent_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete vector/math parent source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('vector/math parent complete primary loses an actual interior candidate')
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
        raw,desc = old.whole_section(member(row),row['symbol'],c,coff)
        a = int(row['target_address'],16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('vector/math parent whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('vector/math parent source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('vector/math parent state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('vector/math parent whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('vector/math parent initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('vector/math parent complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('vector/math parent state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-fp-dispatch-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural math control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned math control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_VectorMathParentLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural math data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural math/math offsets or bitfields differ')
        callback=m['callback_control']; source,fields=c.object_function(path,callback['coff_symbol'])
        ins=list(decoder.disasm(source,0))
        if (len(source)!=callback['size'] or fields or hashlib.sha256(source).hexdigest()!=callback['source_sha256']
                or facts.body_facts(ins)!=callback['body_facts']
                or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=callback['instructions']):
            raise ValueError('cold complete natural member callback ABI differs')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R129'):
                    raise ValueError('vector/math parent retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('vector/math parent complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('vector/math parent full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual,a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('vector/math parent whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('vector/math parent complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('vector/math parent field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('vector/math parent code entry catalog differs from actual complete source definitions')
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = object_code(path,row,c,coff)
            source_ins = {i.address-row['source_definition']['offset']:i for i in decoder.disasm(code,row['source_definition']['offset'])}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('vector/math parent local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('vector/math parent direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('vector/math parent direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('vector/math parent same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('vector/math parent shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('vector/math parent complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('vector/math parent data pointer does not reach a complete actual code entry')
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
            verify_code_carrier(carrier,member(carrier),target,c,coff,old,graph)
        for alternative in m['source_alternatives']:
            raw,fields=whole_code_section(member(alternative),alternative,c,coff)
            actual=c.pe_bytes_at(target,int(alternative['address'],16),alternative['size'])
            mask={i for field in fields for i in range(field['offset'],field['offset']+4)}
            differences=[i for i in range(len(raw)) if i not in mask and raw[i]!=actual[i]]
            if (alternative['decision']!='rejected-whole-section-alternative'
                    or differences!=alternative['non_field_difference_offsets']
                    or len(fields)!=alternative['relocation_count']
                    or hashlib.sha256(raw).hexdigest()!=alternative['source_sha256']
                    or hashlib.sha256(actual).hexdigest()!=alternative['body_sha256']):
                raise ValueError('whole alternative comparison no longer distinguishes source family')
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-short-runtime-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R129 graph replay failed: '+result.stderr[-1500:])
    print('R130 origins OK: eleven complete library primaries / 2511 bytes / 99 fields; three existing shared entries; nine complete auxiliary controls / 2723 bytes / 51 fields; twenty-one retained anchors / 2430 bytes / 57 fields; whole log10/ceil code carriers / 621 bytes; twenty-nine whole data sections / 3133 bytes / 70 fields and one loader-zero COMMON; cold 52-byte layout and 13-byte member-call control; retained full R129 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
