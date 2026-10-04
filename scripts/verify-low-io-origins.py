#!/usr/bin/env python3
"""Replay the bounded R132 low-io, file handle and error dependency graph."""
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
ACCEPTED = {'0x0064EC83': ('__lseek_lk', 116), '0x0064ECF7': ('__lseek', 171), '0x006523AC': ('__lseeki64_lk', 131), '0x0064EF70': ('__write', 171), '0x00653A81': ('__read', 171), '0x00654835': ('__close_lk', 131), '0x00652066': ('__get_osfhandle', 65), '0x00647FAA': ('__dosmaperr', 115), '0x006520A7': ('__lock_fhandle', 160), '0x00647FA1': ('___doserrno', 9), '0x00652147': ('__unlock_fhandle', 34), '0x0064EDA2': ('__write_lk', 462), '0x006538A6': ('__read_lk', 475), '0x00651FE7': ('__free_osfhnd', 127)}
LEDGER_SIZES = {'0x0064EC83': 116, '0x0064ECF7': 171, '0x006523AC': 131, '0x0064EF70': 171, '0x00653A81': 171, '0x00654835': 131, '0x00652066': 65, '0x00647FAA': 115, '0x006520A7': 148, '0x00647FA1': 9, '0x00652147': 34, '0x0064EDA2': 462, '0x006538A6': 475, '0x00651FE7': 127}
AUXILIARIES = {}
LABELS = {'0x0064ED7E': ('0x0064ECF7', 8, 135, '$L20662'), '0x0064EFF7': ('0x0064EF70', 8, 135, '$L20376'), '0x00653B08': ('0x00653A81', 8, 135, '$L20375'), '0x0065213E': ('0x006520A7', 9, 151, '$L20250')}
STATE = {(1756238, '__aexit_rtn', '0x0066FF10', 8), (946790, '$T20664', '0x00667330', 12), (280602, '_errtable', '0x00670480', 360), (1236214, '___security_cookie', '0x0066FE30', 4), (991338, '$T20378', '0x00667340', 12), (979230, '$T20377', '0x00667540', 12), (964304, '$T20252', '0x00667448', 12)}
LAYOUT_OBJECTS = [{'symbol': '_LowIoLayoutProbe', 'offset': 0, 'size': 192, 'storage_span': 192, 'values': [4, 4, 4, 8, 36, 0, 4, 5, 8, 12, 24, 5, 32, 64, 2048, 1152, 256, 140, 8, 12, 8, 0, 4, 8, 0, 4, 1, 2, 4, 8, 16, 32, 64, 128, 9, 22, 13, 8, 32, 28, 6, 19, 36, 188, 202, 4294967286, 4294967285, 4294967284]}]
LAYOUT_HEADERS = {'crt/src/io.h', 'crt/src/mtdll.h', 'crt/src/internal.h', 'PlatformSDK/Include/WinNT.h', 'PlatformSDK/Include/WinBase.h', 'PlatformSDK/Include/WinError.h', 'crt/src/msdos.h', 'crt/src/errno.h'}
CALL_CONTROLS = [{'coff_symbol': '_FileOffsetIdentityControl', 'size': 11, 'source_sha256': '68b0e911184e98d4a1b0ccdd8ac3af49305f9580ed579d6e42aef261780767ee', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x0000000A', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0xc]'}, {'site': '0x00000009', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000000A', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/lseek.c', 'crt/src/osfinfo.c', 'crt/src/dosmap.c', 'crt/src/lseeki64.c', 'crt/src/ioinit.c', 'crt/src/read.c', 'crt/src/write.c', 'crt/src/close.c', 'crt/src/crt0.c'}
CONFIDENCE = 'complete-vendor-low-io-code-data-api-eh-abi-provenance'
LABEL_CONFIDENCE = 'interior-cleanup-in-complete-vendor-low-io-primary'

ANCHORS = [('0x0064232C', '_WinMainCRTStartup', 469, 1756238, 'R126'), ('0x00646725', '__lock', 49, 1698134, 'R120'), ('0x0065053F', '___crtInitCritSecAndSpinCount', 139, 1364582, 'R118'), ('0x00640B66', '__local_unwind2', 104, 1210238, 'R025'), ('0x00646658', '__unlock', 21, 1698134, 'R118'), ('0x00640611', '@__security_check_cookie@4', 14, 1230768, 'R120'), ('0x0064425B', '__exit', 17, 1663884, 'R120'), ('0x00645414', '__SEH_prolog', 59, 1244382, 'R117'), ('0x0064544F', '__SEH_epilog', 17, 1244382, 'R115'), ('0x00647F98', '__errno', 9, 280602, 'R120'), ('0x00646196', '__getptd', 113, 1724384, 'R120')]
IO_PROTOCOL = {'ioinfo_size': 36, 'osfile_offset': 4, 'pipech_offset': 5, 'lockinitflag_offset': 8, 'critical_section_offset': 12, 'critical_section_size': 24, 'handle_group_shift': 5, 'handle_group_mask': 31, 'handle_arrays': 64, 'maximum_handles': 2048, 'thread_size': 140, 'errno_offset': 8, 'doserrno_offset': 12, 'error_entry_size': 8, 'error_entries': 45, 'lseek_cleanup_offset': 135, 'write_cleanup_offset': 135, 'read_cleanup_offset': 135, 'lock_cleanup_offset': 151, 'app_type': 2}
ERROR_TABLE_VALUES = [1, 22, 2, 2, 3, 2, 4, 24, 5, 13, 6, 9, 7, 12, 8, 12, 9, 12, 10, 7, 11, 8, 12, 22, 13, 22, 15, 2, 16, 13, 17, 18, 18, 2, 33, 13, 53, 2, 65, 13, 67, 2, 80, 17, 82, 13, 83, 13, 87, 22, 89, 11, 108, 13, 109, 32, 112, 28, 114, 9, 6, 22, 128, 10, 129, 10, 130, 9, 131, 22, 132, 13, 145, 41, 158, 13, 161, 2, 164, 11, 167, 13, 183, 17, 206, 2, 215, 11, 1816, 12]
DEFINITION_CHOICES = [{'symbol': '___app_type', 'selected_member_offset': 1756238, 'selected_parent': '0x0064232C', 'selected_evidence': 'R126', 'whole_data_symbol': '__aexit_rtn', 'target_address': '0x0066FF14', 'alternatives': [{'member_offset': 1655960, 'member': 'build\\intel\\mt_obj\\crt0.obj', 'member_sha256': 'd811c6f8dbcfe9535457c01c05450bd4b853bb603d7c270368136a81e73ca19c', 'source_definition': {'symbol': '___app_type', 'offset': 4, 'section': 2, 'type': 0, 'storage': 2}}, {'member_offset': 1689142, 'member': 'build\\intel\\mt_obj\\dllcrt0.obj', 'member_sha256': 'ed6026d7c9d783fd697b64d0d81048aabc63abadc61f50144ba4acc9314dcccd', 'source_definition': {'symbol': '___app_type', 'offset': 16, 'section': 2, 'type': 0, 'storage': 2}}, {'member_offset': 1739076, 'member': 'build\\intel\\mt_obj\\wcrt0.obj', 'member_sha256': '5e92eb7ef5802ad977f49df7717f8e8155b5be58645cb948f5b66bb43cda76d4', 'source_definition': {'symbol': '___app_type', 'offset': 4, 'section': 2, 'type': 0, 'storage': 2}}, {'member_offset': 1756238, 'member': 'build\\intel\\mt_obj\\wincrt0.obj', 'member_sha256': '3bd6dd6f97cfd5e38c2eda581b9ec779c95e06fb9a18545369f93b0005c912bf', 'source_definition': {'symbol': '___app_type', 'offset': 4, 'section': 2, 'type': 0, 'storage': 2}}, {'member_offset': 1779372, 'member': 'build\\intel\\mt_obj\\wwincrt0.obj', 'member_sha256': '06c52fd03c8df22126fd9bed6ee91a57bcec3d99f4ccadd197b6c6e77f413041', 'source_definition': {'symbol': '___app_type', 'offset': 4, 'section': 2, 'type': 0, 'storage': 2}}], 'basis': 'Previously independently accepted complete GUI entry defines its own strong application-type state; alternatives retained, no executable-wide source-unit inference'}]

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/low-io-origin-evidence.json').read_text())
    identity = module('low_io_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R132' or m['target_sha256'] != identity.TARGET:
        raise ValueError('Low-IO target identity differs')
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
    if len(m['functions']) != 14 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete low-io cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('low-io function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=0 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('low-io loses complete auxiliary owners')
    if (len(m['interior_labels']) != 4 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('low-io shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('low-io independent complete anchors differ')
    if any(m[k] for k in ('scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('low-io graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 7 or sum(r['size'] for r in m['state_data']) != 420
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('low-io graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 192 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural low-io operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R131',manifest='time-zone-origin-evidence.json')]:
        raise ValueError('low-io loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('low-io graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('low-io shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('low-io direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('low-io table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if m['io_protocol'] != IO_PROTOCOL or m['call_controls'] != CALL_CONTROLS:
        raise ValueError('low-io handle/thread/int64 protocol differs')
    if any(m[k] for k in ('retained_labels','diagnostic_contexts','code_carriers',
                          'extent_reconciliations','source_alternatives')):
        raise ValueError('low-io gains unreviewed owners or duplicate origin credit')
    common=m['common_globals']
    if (len(common)!=2 or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in common}
            != {(935822,'___pioinfo','0x0068FAA0',256),(935822,'__nhandle','0x0068FA80',4)}
            or any(r['source_definition']['section']!=0 or r['source_definition']['storage']!=2
                   or r['source_definition']['offset']!=r['size'] for r in common)):
        raise ValueError('handle table loses complete COMMON/loader definitions')
    if set(m['vendor_sources'])!=VENDOR_SOURCES:
        raise ValueError('low-io loses pinned complete vendor sources')
    scopes={r['symbol']:r for r in m['state_data'] if r['symbol'].startswith('$T')}
    expected={'$T20664':('0x0064ECF7',132),'$T20378':('0x0064EF70',132),
              '$T20377':('0x00653A81',132),'$T20252':('0x006520A7',148)}
    if set(scopes)!=set(expected):raise ValueError('low-io loses full cleanup scopes')
    for symbol,(owner,offset) in expected.items():
        row=scopes[symbol];fields=row['relocations']
        if (row['size']!=12 or len(fields)!=1 or fields[0]['offset']!=8
                or fields[0]['code_entry']['owner']!=owner
                or fields[0]['code_entry']['source_offset']!=offset):
            raise ValueError('low-io scope must retain pre-label stack adjustment')
    witnesses=lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    for key in ('0x0064ECF7','0x0064EF70','0x00653A81'):
        if not {('cmp','ebx, dword ptr [0x68fa80]'),('sar','eax, 5'),('and','eax, 0x1f'),
                ('lea','esi, [eax + eax*8]'),('shl','esi, 2'),
                ('test','byte ptr [eax + esi + 4], 1'),('ret','')}<=witnesses(key):
            raise ValueError('low-io wrapper loses actual bounds/36-byte/FOPEN/cdecl protocol')
    required={
        '0x006520A7':{('cmp','dword ptr [esi + 8], ebx'),('lea','eax, [esi + 0xc]')},
        '0x00647FA1':{('add','eax, 0xc'),('ret','')},
        '0x00652147':{('lea','eax, [ecx + eax*4 + 0xc]'),('ret','')},
        '0x0064EC83':{('cmp','edi, -1'),('test','eax, eax'),('and','byte ptr [eax], 0xfd')},
        '0x006523AC':{('lea','ecx, [ebp - 4]'),('cmp','eax, edi'),('and','byte ptr [eax], 0xfd')},
        '0x0064EDA2':{('test','byte ptr [eax + esi + 4], 0x20'),('test','byte ptr [eax + 4], 0x80'),('cmp','dl, 0xa')},
        '0x006538A6':{('cmp','al, 0x1a'),('cmp','al, 0xd'),('cmp','al, 0xa'),('or','byte ptr [esi], 2')},
        '0x00654835':{('cmp','esi, 1'),('cmp','esi, 2'),('cmp','eax, edi')},
        '0x00651FE7':{('cmp','dword ptr [0x66ff14], 1'),('or','dword ptr [esi + eax], 0xffffffff')},
        '0x00647FAA':{('cmp','esi, 0x2d'),('cmp','ecx, 0x13'),('cmp','ecx, 0x24'),('cmp','ecx, 0xbc'),('cmp','ecx, 0xca')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):raise ValueError('low-io loses full error/seek/text/alias/lock witnesses')
    if m['error_table_values']!=ERROR_TABLE_VALUES or len(ERROR_TABLE_VALUES)!=90:
        raise ValueError('error map loses full ordered 45-entry table including duplicate OS code')
    if m['definition_choices']!=DEFINITION_CHOICES:
        raise ValueError('application-type state loses actual GUI defining parent/alternatives')
    choice=m['definition_choices'][0];parent=graph[choice['selected_parent']]
    carrier=next(r for r in m['state_data'] if r['symbol']=='__aexit_rtn')
    definitions=[d for d in carrier['source_section']['definitions'] if d['symbol']=='___app_type']
    if (parent['member_offset']!=choice['selected_member_offset'] or parent['origin_evidence']!='R126'
            or carrier['member_offset']!=parent['member_offset'] or carrier['size']!=8
            or len(definitions)!=1 or definitions[0]['offset']!=4 or definitions[0]['storage']!=2
            or int(carrier['target_address'],16)+4!=int(choice['target_address'],16)
            or len(carrier['relocations'])!=1 or carrier['relocations'][0]['offset']!=0
            or carrier['relocations'][0]['code_entry']['owner']!='0x0064425B'):
        raise ValueError('application-type state loses entire actual GUI owner and exit pointer')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('low-io function loses its complete own AUX extent')
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
        raise ValueError('low-io cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('low-io loses complete origin-only extent')
    if (origin['evidence_id'] != 'R132' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('low-io canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('low-io shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R132' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('low-io shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('low-io external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('low-io member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('low_io_old','verify-runtime-error-origins.py')
    c = module('low_io_target','compare-coff-function.py')
    archive_reader = module('low_io_archive','verify-runtime-origins.py')
    coff = module('low_io_coff','coff_data.py')
    startup = module('low_io_geometry','verify-startup-dependency-origins.py')
    record = module('low_io_ledger','verify-vendor-record-origins.py')
    facts = module('low_io_facts','verify-game-lifetime-origins.py')
    imports_module = module('low_io_imports','verify-import-origins.py')
    literal = module('low_io_scalar','verify-runtime-external-origins.py')
    sections = module('low_io_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete low-io source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('low-io complete primary loses an actual interior candidate')
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest() != m['archive_sha256']:
        raise ValueError('pinned whole CRT archive differs')
    members = {off:(name,data) for off,name,data in archive_reader.archive_members(archive)}
    def member(row):
        name,data = members[row['member_offset']]
        if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
            raise ValueError('complete source member identity differs')
        return data
    actual_choices=[]
    for off,(name,data) in members.items():
        try: definitions=coff.parse_symbols(data,c.coff_name)[1]
        except ValueError: continue
        for definition in definitions:
            if definition['symbol']=='___app_type' and definition['storage']==2 and definition['section']>0:
                actual_choices.append(dict(member_offset=off,member=name,
                    member_sha256=hashlib.sha256(data).hexdigest(),source_definition=definition))
    if actual_choices!=m['definition_choices'][0]['alternatives']:
        raise ValueError('application-type strong alternatives differ from complete archive')
    target_sections = sections.sections(target); imports = imports_module.pe_imports(target,c)
    state_map = {}; global_state = {}
    for row in m['state_data']:
        raw,desc = old.whole_section(member(row),row['symbol'],c,coff)
        a = int(row['target_address'],16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('low-io whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('low-io source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('low-io state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('low-io whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('low-io initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('low-io complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('low-io state loses whole writable target storage')
        else:
            literal.check_scalar(linked,actual,row['size'],target_sections,a)
    table=next(r for r in m['state_data'] if r['symbol']=='_errtable')
    if list(struct.unpack('<90I',c.pe_bytes_at(target,int(table['target_address'],16),360)))!=ERROR_TABLE_VALUES:
        raise ValueError('actual whole ordered OS error mapping differs')
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
    scratch = ROOT / 'build/origin-low-io-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural low-io control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned low-io control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_LowIoLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural low-io data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural handle/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete low-io vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete cdecl EDX:EAX file-offset ABI differs')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R131'):
                    raise ValueError('low-io retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('low-io complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('low-io full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual,a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('low-io whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('low-io complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('low-io field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('low-io code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('low-io local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('low-io direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('low-io direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('low-io same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('low-io shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('low-io complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('low-io data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-time-zone-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R131 graph replay failed: '+result.stderr[-1500:])
    print('R132 origins OK: fourteen complete library primaries / 2338 bytes / 109 fields; four existing cleanup entries / 33 overlapping bytes; eleven retained anchors / 1011 bytes / 72 fields; seven whole data sections / 420 bytes / five fields and two loader-zero COMMON / 260 bytes; cold 192-byte handle/thread/SDK layout and 11-byte cdecl EDX:EAX control; actual GUI application-state source with all five strong alternatives; full retained R131 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
