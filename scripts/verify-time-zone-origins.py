#!/usr/bin/env python3
"""Replay the bounded R131 time-zone, environment and calendar dependency graph."""
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
ACCEPTED = {'0x0064197E': ('_localtime', 384), '0x00647778': ('__tzset_lk', 680), '0x00647BD8': ('__isindst_lk', 391), '0x00647D5F': ('___tzset', 76), '0x00647DE0': ('__isindst', 62), '0x00647E1E': ('_gmtime', 263), '0x00647A20': ('_cvtdate', 440), '0x006506C5': ('__getenv_lk', 129), '0x00653816': ('___wtomb_environ', 144), '0x006537C8': ('__mbsnbicoll', 78), '0x00654660': ('___crtsetenv', 469), '0x0065422E': ('___crtCompareStringA', 900), '0x0065497E': ('__mbschr', 123), '0x006545FF': ('_copy_environ', 97), '0x006545B2': ('_findenv', 77), '0x00654212': ('_strncnt', 28), '0x00642AD2': ('__strdup', 43)}
LEDGER_SIZES = {'0x0064197E': 384, '0x00647778': 680, '0x00647BD8': 391, '0x00647D5F': 67, '0x00647DE0': 53, '0x00647E1E': 263, '0x00647A20': 440, '0x006506C5': 129, '0x00653816': 144, '0x006537C8': 78, '0x00654660': 469, '0x0065422E': 900, '0x0065497E': 336, '0x006545FF': 97, '0x006545B2': 77, '0x00654212': 28, '0x00642AD2': 43}
AUXILIARIES = {'0x00654A10': ('_strchr', 190), '0x00654A00': ('_$$$00001', 16)}
LABELS = {'0x00647993': ('0x00647778', 9, 539, '$L20316'), '0x00647DA2': ('0x00647D5F', 9, 67, '$L20368'), '0x00647E15': ('0x00647DE0', 9, 53, '$L20394')}
STATE = {(2355650, '$T20398', '0x00661778', 12), (2355650, '_dststart', '0x00670460', 24), (1256142, '??_C@_13NOLLCAOD@?$AA?$AA?$AA?$AA@', '0x006639D0', 4), (2355650, '$T20372', '0x00661758', 12), (1409460, '___lc_handle', '0x0068E6B4', 32), (2355650, '??_C@_02CLFPBFFP@TZ?$AA@', '0x00661744', 3), (1256142, '?f_use@?1??__crtCompareStringA@@9@9', '0x0068E79C', 4), (2355650, '$T20326', '0x00661748', 12), (1663884, '__umaskval', '0x0068E2E4', 72), (2354040, '__timezone', '0x006703C8', 152), (1236214, '___security_cookie', '0x0066FE30', 4), (2309648, '__lpdays', '0x00670CDC', 104), (2317270, '_tb', '0x0068E550', 36), (2355650, '_tzinfo', '0x0068E498', 184), (1256142, '$T20293', '0x00667590', 24)}
LAYOUT_OBJECTS = [{'symbol': '_TimeZoneLayoutProbe', 'offset': 0, 'size': 212, 'storage_span': 212, 'values': [4, 4, 4, 4, 2, 36, 0, 4, 8, 12, 16, 20, 24, 28, 32, 140, 68, 96, 544, 4, 8, 12, 28, 16, 0, 2, 4, 6, 8, 10, 12, 14, 172, 0, 4, 68, 84, 88, 152, 168, 12, 0, 4, 8, 6, 7, 86400, 31536000, 126230400, 2147483647, 259200, 2147224447, 1]}]
LAYOUT_HEADERS = {'crt/src/ctime.h', 'crt/src/mtdll.h', 'PlatformSDK/Include/WinNT.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/string.h', 'crt/src/stdlib.h', 'crt/src/limits.h', 'crt/src/cruntime.h', 'crt/src/time.h'}
CALL_CONTROLS = [{'coff_symbol': '_NarrowDupCallControl', 'size': 17, 'source_sha256': '1c268736a240e2202586552f52b8eb7a8cdf71939cb2129e2fb15cfe8a5723bc', 'relocation_metadata': [{'offset': 8, 'type': 'REL32', 'symbol': '__strdup', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000010', 'cleanup': 0}], 'direct_calls': [{'site': '0x00000007', 'target': '0x0000000C'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'call', 'operands': '0xc'}, {'site': '0x0000000C', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x0000000F', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000010', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_WideDupCallControl', 'size': 17, 'source_sha256': '1c268736a240e2202586552f52b8eb7a8cdf71939cb2129e2fb15cfe8a5723bc', 'relocation_metadata': [{'offset': 8, 'type': 'REL32', 'symbol': '__wcsdup', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000010', 'cleanup': 0}], 'direct_calls': [{'site': '0x00000007', 'target': '0x0000000C'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'call', 'operands': '0xc'}, {'site': '0x0000000C', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x0000000F', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000010', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/a_cmp.c', 'crt/src/getenv.c', 'crt/src/wtombenv.c', 'crt/src/mbschr.c', 'crt/src/setenv.c', 'crt/src/strdup.c', 'crt/src/mbsnbico.c', 'crt/src/intel/strchr.asm', 'crt/src/localtim.c', 'crt/src/gmtime.c', 'crt/src/tzset.c'}
CONFIDENCE = 'complete-vendor-time-zone-calendar-environment-code-data-api-eh-abi-provenance'
LABEL_CONFIDENCE = 'interior-cleanup-in-complete-vendor-time-zone-primary'

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/time-zone-origin-evidence.json').read_text())
    identity = module('time_zone_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R131' or m['target_sha256'] != identity.TARGET:
        raise ValueError('Time-zone target identity differs')
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
    if len(m['functions']) != 17 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete time-zone cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('time-zone function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=2 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('time-zone loses complete auxiliary owners')
    if (len(m['interior_labels']) != 3 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('time-zone shared entries lose complete source parents or gain standalone credit')
    if len(m['anchors']) != 21 or sum(r['size'] for r in m['anchors']) != 2607:
        raise ValueError('time-zone independent complete anchors differ')
    if any(m[k] for k in ('scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('time-zone graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 15 or sum(r['size'] for r in m['state_data']) != 679
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('time-zone graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 212 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural time-zone operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R130',manifest='vector-math-parent-origin-evidence.json')]:
        raise ValueError('time-zone loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('time-zone graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('time-zone shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('time-zone direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('time-zone table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    check_carrier_plan(m, graph)
    if ([(r['address'],r['member_offset'],r['size'],r['selected_parent'],r['selected_member_offset'])
         for r in m['source_alternatives']]!=[('0x006545FF',1550570,97,'0x00654660',1440012),
                                            ('0x00654212',1269308,28,'0x0065422E',1256142)]):
        raise ValueError('equivalent complete vendor alternatives lose actual local source parents')
    for alternative in m['source_alternatives']:
        owner=graph[alternative['address']];parent=graph[alternative['selected_parent']]
        fields=[b for b in parent['relocation_bindings'] if b['symbol']==owner['coff_symbol']]
        if (owner['member_offset']!=parent['member_offset'] or owner['member_offset']!=alternative['selected_member_offset']
                or owner['source_definition']['storage']!=3 or not fields
                or any(b['code_entry']['owner']!=owner['address'] or b['code_entry']['source_definition']!=owner['source_definition'] for b in fields)):
            raise ValueError('local helper loses complete defining caller/typed source symbol')
    return rows


def check_parent_protocol(m, graph):
    expected=dict(time_t_size=4,tm_size=36,thread_size=140,gmtimebuf_offset=68,ptmbcinfo_offset=96,
        mbcinfo_size=544,time_lock=6,environment_lock=7,day_seconds=86400,four_year_seconds=126230400,
        localtime_margin=259200,localtime_upper_bound=2147224447,tzinfo_size=172,transition_size=12,
        tzset_cleanup_offset=539,tzset_scope_entry_offset=534,once_cleanup_offset=67,dst_cleanup_offset=53,
        strchr_whole_section_size=206)
    if m['time_protocol']!=expected or m['call_controls']!=CALL_CONTROLS:
        raise ValueError('time-zone calendar/thread/transition/call protocol differs')
    witnesses=lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    if not {('cmp','eax, 0x3f480'),('cmp','eax, 0x7ffc0b7f'),('mov','dword ptr [esi + 0x20], 1')}<=witnesses('0x0064197E'):
        raise ValueError('localtime loses actual signed epoch margins/DST result field')
    if not {('cmp','dword ptr [edi + 0x44], 0'),('push','0x24'),
            ('mov','dword ptr [edi + 0x44], eax'),('mov','ecx, dword ptr [edi + 0x44]')}<=witnesses('0x00647E1E'):
        raise ValueError('gmtime loses actual thread slot/whole tm allocation')
    for key in ('0x00647D5F','0x00647DE0'):
        if ('push','6') not in witnesses(key) or ('ret','') not in witnesses(key):
            raise ValueError('time-zone wrapper loses actual time-lock/cdecl return')
    if ('push','7') not in witnesses('0x00647778'):
        raise ValueError('TZ reader loses actual environment-lock protocol')
    scopes={r['symbol']:r for r in m['state_data'] if r['symbol'].startswith('$T')}
    expected_scopes={'$T20326':('0x00647778',[8],[534]),'$T20372':('0x00647D5F',[8],[67]),
        '$T20398':('0x00647DE0',[8],[53]),'$T20293':('0x0065422E',[4,8,16,20],[424,428,578,582])}
    if set(scopes)!=set(expected_scopes):raise ValueError('time-zone graph loses full source scopes')
    for symbol,(owner,offsets,entries) in expected_scopes.items():
        fields=scopes[symbol]['relocations']
        if (scopes[symbol]['size']!=(24 if symbol=='$T20293' else 12)
                or [b['offset'] for b in fields]!=offsets
                or [b['code_entry']['source_offset'] for b in fields]!=entries
                or any(b['target_kind']!='code-entry' or b['code_entry']['owner']!=owner for b in fields)):
            raise ValueError('scope loses actual full filter/handler/cleanup provenance')
    timezone=next(r for r in m['state_data'] if r['symbol']=='__timezone')
    if (timezone['size']!=152 or [b['offset'] for b in timezone['relocations']]!=[144,148]
            or any(b['target_kind']!='state' for b in timezone['relocations'])):
        raise ValueError('timezone loses full initial names/pointer carrier')
    calendar=next(r for r in m['state_data'] if r['symbol']=='__lpdays')
    if calendar['size']!=104 or calendar['relocations']:
        raise ValueError('calendar loses both complete 13-element month tables')
    if any(m[k] for k in ('retained_labels','diagnostic_contexts')):
        raise ValueError('time-zone gains unreviewed code or duplicate origin credit')
    common=m['common_globals']
    if (len(common)!=2 or {(r['symbol'],r['target_address'],r['size']) for r in common}
            != {('___env_initialized','0x0068FBA8',4),('___ptmbcinfo','0x0068E7F8',4)}
            or any(r['source_definition']['section']!=0 or r['source_definition']['storage']!=2
                   or r['source_definition']['offset']!=4 for r in common)):
        raise ValueError('environment/MBCS flags lose complete COMMON/loader definitions')
    if set(m['vendor_sources'])!=VENDOR_SOURCES:
        raise ValueError('time-zone source/layout evidence loses pinned complete vendor sources')


def check_carrier_plan(m, graph):
    carriers=m['code_carriers']
    if len(carriers)!=1:
        raise ValueError('strchr loses entire defining source section')
    row=carriers[0]
    if (row['address']!='0x00654A00' or row['symbol']!='_$$$00001' or row['size']!=206
            or row['gaps'] or row['relocation_bindings']
            or row['components']!=[dict(owner='0x00654A00',offset=0,size=16),dict(owner='0x00654A10',offset=16,size=190)]):
        raise ValueError('strchr carrier loses both complete own-AUX entries')
    for part in row['components']:
        owner=graph.get(part['owner'])
        if (not owner or owner['member_offset']!=row['member_offset'] or owner['size']!=part['size']
                or owner['source_definition']['section']!=row['source_section']['number']
                or owner['source_definition']['offset']!=part['offset']
                or int(owner['address'],16)!=int(row['address'],16)+part['offset']):
            raise ValueError('strchr carrier loses actual defining same-section owner')
    reconciliations=m['extent_reconciliations']
    if len(reconciliations)!=1:
        raise ValueError('mbschr cannot discard its entire old provisional extent')
    row=reconciliations[0];parts=row['components']
    if (row['address']!='0x0065497E' or row['original_size']!=336 or row['original_span_end']!='0x00654ACD'
            or len(parts)!=3 or parts[0]!=dict(kind='complete-own-AUX',owner='0x0065497E',offset=0,size=123)
            or parts[2]!=dict(kind='whole-other-defining-code-section',owner='0x00654A00',offset=130,size=206)
            or parts[1]['kind']!='observed-target-alignment' or parts[1]['offset']!=123 or parts[1]['size']!=7
            or parts[1]['address']!='0x006549F9' or parts[1]['credit']!='none'
            or graph['0x0065497E']['ledger_size']!=336 or graph['0x0065497E']['size']!=123):
        raise ValueError('mbschr extent loses complete bodies or invents padding credit')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('time-zone function loses its complete own AUX extent')
    return comparison.object_function(path,row['coff_symbol'])


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
        raise ValueError('time-zone cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('time-zone loses complete origin-only extent')
    if (origin['evidence_id'] != 'R131' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('time-zone canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('time-zone shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R131' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('time-zone shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('time-zone external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('time-zone member-local data reference changes its actual defining object')
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


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('time_zone_old','verify-runtime-error-origins.py')
    c = module('time_zone_target','compare-coff-function.py')
    archive_reader = module('time_zone_archive','verify-runtime-origins.py')
    coff = module('time_zone_coff','coff_data.py')
    startup = module('time_zone_geometry','verify-startup-dependency-origins.py')
    record = module('time_zone_ledger','verify-vendor-record-origins.py')
    facts = module('time_zone_facts','verify-game-lifetime-origins.py')
    imports_module = module('time_zone_imports','verify-import-origins.py')
    literal = module('time_zone_scalar','verify-runtime-external-origins.py')
    sections = module('time_zone_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete time-zone source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('time-zone complete primary loses an actual interior candidate')
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
            raise ValueError('time-zone whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('time-zone source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('time-zone state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('time-zone whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('time-zone initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('time-zone complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('time-zone state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-time-zone-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural time control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned time control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_TimeZoneLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural time data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural time/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete time-zone vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete narrow/wide duplication ABI/typed calls differ')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R130'):
                    raise ValueError('time-zone retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('time-zone complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('time-zone full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual,a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('time-zone whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('time-zone complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('time-zone field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('time-zone code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('time-zone local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('time-zone direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('time-zone direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('time-zone same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('time-zone shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('time-zone complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('time-zone data pointer does not reach a complete actual code entry')
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
            data=member(alternative);path.write_bytes(data);source,fields=c.object_function(path,alternative['coff_symbol'])
            actual=c.pe_bytes_at(target,int(alternative['address'],16),alternative['size'])
            definitions=coff.parse_symbols(data,c.coff_name)[1]
            definition=next(d for d in definitions if d['symbol']==alternative['coff_symbol'])
            mask={i for field in fields for i in range(field['offset'],field['offset']+4)}
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=alternative['size'] or definition!=alternative['source_definition']
                    or alternative['decision']!='equivalent-complete-vendor-alternative'
                    or [i for i in range(len(source)) if i not in mask and source[i]!=actual[i]]!=alternative['non_field_difference_offsets']
                    or metadata!=alternative['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=alternative['source_sha256']
                    or hashlib.sha256(actual).hexdigest()!=alternative['body_sha256']):
                raise ValueError('whole vendor alternatives lose complete equivalent source bodies')
        for reconciliation in m['extent_reconciliations']:
            actual=c.pe_bytes_at(target,int(reconciliation['address'],16),reconciliation['original_size'])
            if hashlib.sha256(actual).hexdigest()!=reconciliation['body_sha256']:
                raise ValueError('entire original mbschr provisional extent differs')
            padding=reconciliation['components'][1];a=int(padding['address'],16)
            raw=c.pe_bytes_at(target,a,padding['size']);ins=list(decoder.disasm(raw,a))
            witnesses=[dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            if (len(ins)!=7 or any(i.mnemonic!='int3' for i in ins)
                    or witnesses!=padding['instructions'] or hashlib.sha256(raw).hexdigest()!=padding['body_sha256']):
                raise ValueError('observed alignment cannot conceal unreviewed code/data')
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-vector-math-parent-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R130 graph replay failed: '+result.stderr[-1500:])
    print('R131 origins OK: seventeen complete library primaries / 4384 bytes / 237 fields; three existing nine-byte cleanup entries; two complete auxiliary owners / 206 bytes and whole strchr section; entire 336-byte old mbschr extent reconciled; twenty-one retained anchors / 2607 bytes / 108 fields; fifteen whole data sections / 679 bytes / nine fields and two loader-zero COMMON; cold 212-byte time/thread/SDK layout, narrow/wide typed call controls and complete equivalent vendor alternatives; full retained R130 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
