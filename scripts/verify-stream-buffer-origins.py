#!/usr/bin/env python3
"""Replay the bounded R133 stream buffer and close dependency graph."""
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
ACCEPTED = {'0x0065163C': ('__filbuf', 225), '0x006443FE': ('__flsbuf', 281), '0x0064F01B': ('__getbuf', 68), '0x0064F05F': ('__isatty', 42), '0x0065171D': ('__ungetc_lk', 108), '0x006548B8': ('__close', 155)}
LEDGER_SIZES = {'0x0065163C': 225, '0x006443FE': 281, '0x0064F01B': 68, '0x0064F05F': 42, '0x0065171D': 108, '0x006548B8': 155}
AUXILIARIES = {}
LABELS = {'0x0065492F': ('0x006548B8', 8, 119, '$L20316')}
STATE = {(889344, '$T20318', '0x006675A8', 12), (935822, '___badioinfo', '0x006707D0', 36), (1832966, '__cflush', '0x0068E704', 4), (1832966, '__iob', '0x00670928', 640)}
LAYOUT_OBJECTS = [{'symbol': '_StreamBufferLayoutProbe', 'offset': 0, 'size': 212, 'storage_span': 212, 'values': [4, 4, 4, 1, 2, 32, 0, 4, 8, 12, 16, 20, 24, 28, 20, 640, 4096, 512, 1, 2, 4, 8, 16, 32, 64, 128, 256, 1024, 8192, 1, 2, 32, 64, 128, 36, 0, 4, 5, 8, 12, 24, 5, 32, 64, 2048, 256, 140, 8, 12, 4294967295, 2, 4, 4096]}]
LAYOUT_HEADERS = {'crt/src/internal.h', 'crt/src/stdio.h', 'crt/src/file2.h', 'crt/src/mtdll.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/msdos.h', 'PlatformSDK/Include/WinNT.h', 'crt/src/io.h'}
CALL_CONTROLS = [{'coff_symbol': '_StreamByteLoadControl', 'size': 13, 'source_sha256': '0c67b0ba1bd47675ff97a85e3f3f70e3b0edc5ec3172079f2182985945982e15', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x0000000C', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax]'}, {'site': '0x00000008', 'mnemonic': 'movzx', 'operands': 'eax, byte ptr [ecx]'}, {'site': '0x0000000B', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000000C', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_StreamPushbackCallControl', 'size': 21, 'source_sha256': '18178217ccd6124c0580a72a4a7a6920bc64c5bef7b0f93975f536bbe96f2b97', 'relocation_metadata': [{'offset': 12, 'type': 'REL32', 'symbol': '__ungetc_lk', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000014', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000000B', 'target': '0x00000010'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0xc]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'call', 'operands': '0x10'}, {'site': '0x00000010', 'mnemonic': 'add', 'operands': 'esp, 8'}, {'site': '0x00000013', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000014', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/_flsbuf.c', 'crt/src/ioinit.c', 'crt/src/ungetc.c', 'crt/src/close.c', 'crt/src/_filbuf.c', 'crt/src/isatty.c', 'crt/src/_file.c', 'crt/src/_getbuf.c'}
CONFIDENCE = 'complete-vendor-stream-buffer-code-data-eh-abi-provenance'
LABEL_CONFIDENCE = 'interior-cleanup-in-complete-vendor-stream-buffer-primary'

ANCHORS = [('0x00653A81', '__read', 171, 979230, 'R132'), ('0x0064EF70', '__write', 171, 991338, 'R132'), ('0x0064ECF7', '__lseek', 171, 946790, 'R132'), ('0x00644331', '_malloc', 18, 816374, 'R120'), ('0x00645414', '__SEH_prolog', 59, 1244382, 'R117'), ('0x006520A7', '__lock_fhandle', 160, 964304, 'R132'), ('0x00654835', '__close_lk', 131, 889344, 'R132'), ('0x00647F98', '__errno', 9, 280602, 'R120'), ('0x00652147', '__unlock_fhandle', 34, 964304, 'R132'), ('0x00647FA1', '___doserrno', 9, 280602, 'R132'), ('0x0064544F', '__SEH_epilog', 17, 1244382, 'R115')]
IO_PROTOCOL = {'file_size': 32, 'pointer_offset': 0, 'count_offset': 4, 'base_offset': 8, 'flag_offset': 12, 'handle_offset': 16, 'charbuf_offset': 20, 'bufsiz_offset': 24, 'tmpname_offset': 28, 'file_entries': 20, 'file_array_size': 640, 'buffer_size': 4096, 'small_buffer_size': 512, 'fallback_buffer_size': 2, 'stdin_index': 0, 'stdout_index': 1, 'stderr_index': 2, 'badioinfo_size': 36, 'badioinfo_handle': -1, 'badioinfo_flags': 128, 'badioinfo_pipech': 10, 'handle_group_shift': 5, 'handle_group_mask': 31, 'handle_arrays': 64, 'handle_stride': 36, 'close_scope_offset': 116, 'close_cleanup_offset': 119}

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/stream-buffer-origin-evidence.json').read_text())
    identity = module('stream_buffer_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R133' or m['target_sha256'] != identity.TARGET:
        raise ValueError('Stream-buffer target identity differs')
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
    if len(m['functions']) != 6 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete stream-buffer cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('stream-buffer function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=0 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('stream-buffer loses complete auxiliary owners')
    if (len(m['interior_labels']) != 1 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('stream-buffer shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('stream-buffer independent complete anchors differ')
    if any(m[k] for k in ('scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('stream-buffer graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 4 or sum(r['size'] for r in m['state_data']) != 692
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('stream-buffer graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 212 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural stream-buffer operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R132',manifest='low-io-origin-evidence.json')]:
        raise ValueError('stream-buffer loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('stream-buffer graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('stream-buffer shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('stream-buffer direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('stream-buffer table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if m['stream_protocol'] != IO_PROTOCOL or m['call_controls'] != CALL_CONTROLS:
        raise ValueError('stream-buffer FILE/handle/narrow-byte/cdecl protocol differs')
    if any(m[k] for k in ('retained_labels','diagnostic_contexts','code_carriers',
                          'extent_reconciliations','source_alternatives')):
        raise ValueError('stream-buffer gains unreviewed owners or duplicate origin credit')
    common=m['common_globals']
    if (len(common)!=3 or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in common}
            != {(935822,'___pioinfo','0x0068FAA0',256),(935822,'__nhandle','0x0068FA80',4),
                (1832966,'__bufin','0x0068EA40',4096)}
            or any(r['source_definition']['section']!=0 or r['source_definition']['storage']!=2
                   or r['source_definition']['offset']!=r['size'] for r in common)):
        raise ValueError('stream-buffer loses complete handle/input COMMON/loader definitions')
    if set(m['vendor_sources'])!=VENDOR_SOURCES:
        raise ValueError('stream-buffer loses pinned complete vendor sources')
    scope=next(r for r in m['state_data'] if r['symbol']=='$T20318')
    fields=scope['relocations']
    if (scope['size']!=12 or len(fields)!=1 or fields[0]['offset']!=8
            or fields[0]['code_entry']['owner']!='0x006548B8'
            or fields[0]['code_entry']['source_offset']!=116):
        raise ValueError('close scope must retain pre-label register restoration')
    iob=next(r for r in m['state_data'] if r['symbol']=='__iob')
    fields=iob['relocations']
    if (iob['size']!=640 or len(fields)!=2 or [b['offset'] for b in fields]!=[0,8]
            or any(b['type']!='DIR32' or b['target_kind']!='state' or b['symbol']!='__bufin'
                   or b['target_address']!='0x0068EA40' or b['addend'] for b in fields)):
        raise ValueError('FILE array loses both actual stdin/input-buffer fields')
    stdout_fields=[b for b in graph['0x006443FE']['relocation_bindings'] if b['symbol']=='__iob']
    if (len(stdout_fields)!=2 or [b['addend'] for b in stdout_fields]!=[32,64]
            or any(b['target_address']!='0x00670928' or b['type']!='DIR32' for b in stdout_fields)):
        raise ValueError('flush loses actual stdout/stderr array-entry offsets')
    cflush=next(r for r in m['state_data'] if r['symbol']=='__cflush')
    if (cflush['source_section']['size']!=4 or not int(cflush['source_section']['flags'],16)&0x80
            or 'zero_fill_region' not in cflush or cflush['relocations']):
        raise ValueError('cflush must retain its actual defining BSS section')
    witnesses=lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required={
        '0x0065163C':{('cmp','ecx, -1'),('mov','edi, 0x6707d0'),('cmp','cl, 0x82'),
            ('or','edx, 0x2000'),('cmp','dword ptr [esi + 0x18], 0x200'),
            ('mov','dword ptr [esi + 0x18], 0x1000'),('movzx','eax, byte ptr [ecx]')},
        '0x006443FE':{('cmp','esi, 0x670948'),('cmp','esi, 0x670968'),('test','al, 0x10'),
            ('mov','eax, 0x6707d0'),('test','byte ptr [eax + 4], 0x20'),('and','eax, 0xff')},
        '0x0064F01B':{('inc','dword ptr [0x68e704]'),('push','0x1000'),
            ('lea','eax, [ecx + 0x14]'),('mov','dword ptr [ecx + 0x18], 2'),
            ('mov','dword ptr [ecx + 0x18], 0x1000'),('and','dword ptr [ecx + 4], 0')},
        '0x0064F05F':{('cmp','eax, dword ptr [0x68fa80]'),('sar','ecx, 5'),('and','eax, 0x1f'),
            ('lea','eax, [eax + eax*8]'),('and','eax, 0x40')},
        '0x0065171D':{('cmp','ebx, -1'),('test','byte ptr [esi + 0xc], 0x40'),
            ('cmp','byte ptr [eax], bl'),('mov','byte ptr [eax], bl'),
            ('inc','dword ptr [esi + 4]'),('and','eax, 0xffffffef'),('and','eax, 0xff')},
        '0x006548B8':{('cmp','ebx, dword ptr [0x68fa80]'),('sar','eax, 5'),('and','eax, 0x1f'),
            ('lea','esi, [eax + eax*8]'),('shl','esi, 2'),
            ('test','byte ptr [eax + esi + 4], 1'),('mov','dword ptr [eax], 9'),
            ('and','dword ptr [eax], 0'),('ret','')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):
            raise ValueError('stream-buffer loses actual allocation/EOF/append/string/handle/close witnesses')


def check_initial_streams(target, comparison):
    # Check actual whole arrays after link; process-mutated runtime state is unknown.
    values=list(struct.unpack('<160I',comparison.pe_bytes_at(target,0x670928,640)))
    expected=[0x68EA40,0,0x68EA40,257,0,0,4096,0,
              0,0,0,2,1,0,0,0,0,0,0,2,2,0,0,0]+[0]*136
    if values!=expected:
        raise ValueError('whole initial FILE array loses all twenty actual records')
    bad=comparison.pe_bytes_at(target,0x6707D0,36)
    if (struct.unpack_from('<i',bad)[0]!=-1 or bad[4]!=128 or bad[5]!=10
            or struct.unpack_from('<i',bad,8)[0]!=0):
        raise ValueError('whole invalid-handle record loses actual sentinel/text/lookahead/lock state')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('stream-buffer function loses its complete own AUX extent')
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
        raise ValueError('stream-buffer cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('stream-buffer loses complete origin-only extent')
    if (origin['evidence_id'] != 'R133' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('stream-buffer canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('stream-buffer shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R133' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('stream-buffer shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('stream-buffer external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('stream-buffer member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('stream_buffer_old','verify-runtime-error-origins.py')
    c = module('stream_buffer_target','compare-coff-function.py')
    archive_reader = module('stream_buffer_archive','verify-runtime-origins.py')
    coff = module('stream_buffer_coff','coff_data.py')
    startup = module('stream_buffer_geometry','verify-startup-dependency-origins.py')
    record = module('stream_buffer_ledger','verify-vendor-record-origins.py')
    facts = module('stream_buffer_facts','verify-game-lifetime-origins.py')
    imports_module = module('stream_buffer_imports','verify-import-origins.py')
    literal = module('stream_buffer_scalar','verify-runtime-external-origins.py')
    sections = module('stream_buffer_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete stream-buffer source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('stream-buffer complete primary loses an actual interior candidate')
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
            raise ValueError('stream-buffer whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('stream-buffer source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('stream-buffer state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('stream-buffer whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('stream-buffer initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('stream-buffer complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('stream-buffer state loses whole writable target storage')
        else:
            literal.check_scalar(linked,actual,row['size'],target_sections,a)
    check_initial_streams(target,c)
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
    scratch = ROOT / 'build/origin-stream-buffer-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural stream-buffer control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned stream-buffer control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_StreamBufferLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural stream-buffer data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural handle/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete stream-buffer vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete narrow-byte/cdecl typed pushback controls differ')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R132'):
                    raise ValueError('stream-buffer retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('stream-buffer complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('stream-buffer full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual,a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('stream-buffer whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('stream-buffer complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('stream-buffer field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('stream-buffer code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('stream-buffer local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('stream-buffer direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('stream-buffer direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('stream-buffer same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('stream-buffer shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('stream-buffer complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('stream-buffer data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-low-io-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R132 graph replay failed: '+result.stderr[-1500:])
    print('R133 origins OK: six complete library primaries / 879 bytes / 29 fields; one existing eight-byte cleanup entry; eleven retained anchors / 950 bytes / 62 fields; four whole data sections / 692 bytes / three fields and three loader-zero COMMON / 4356 bytes; cold 212-byte FILE/handle/SDK layout, 13-byte narrow-byte and 21-byte cdecl typed pushback controls; entire 20-record FILE array and bad-handle carrier; full retained R132 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
