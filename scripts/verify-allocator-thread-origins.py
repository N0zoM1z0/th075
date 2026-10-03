#!/usr/bin/env python3
"""Cold-replay whole R119 heap dependencies and retain the open lock/TLS cycle."""
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
ACCEPTED = {
    '0x0064EC68': ('__callnewh', 27),
    '0x0064A715': ('___sbh_find_block', 43),
    '0x0064A740': ('___sbh_free_block', 792),
    '0x0064B339': ('___sbh_alloc_block', 764),
    '0x0064AA58': ('___sbh_alloc_new_region', 183),
    '0x0064615D': ('___crtTlsAlloc@4', 9),
}
PENDING = {
    '0x00644331': 'crt-malloc-heap-lock-cycle-unresolved',
    '0x00644305': 'crt-nh-malloc-heap-lock-cycle-unresolved',
    '0x0064428A': 'crt-heap-allocation-lock-error-cycle-unresolved',
    '0x00642A61': 'crt-free-lazy-lock-error-cycle-unresolved',
    '0x00647F98': 'crt-errno-thread-allocation-error-cycle-unresolved',
    '0x00646196': 'crt-thread-allocation-error-cycle-unresolved',
    '0x00644343': 'crt-calloc-lazy-lock-error-cycle-unresolved',
}
LAYOUT = [20, 0, 4, 8, 12, 16, 16836, 0, 4, 68, 196, 324, 516, 0, 4,
          8, 0, 4, 12, 0, 4, 8, 4, 0, 16, 4096, 32768, 1048576, 12, 4080,
          8, 8192, 4096, 16384, 32768, 4, 140, 0, 4, 8, 20, 84]
FRAGMENTS = [
    dict(address='0x006442FC', size=9, parent='0x0064428A', source_offset=114,
         source_symbol='$L19916', eh_source_symbol='$L19914', eh_source_offset=111,
         decision='pending', uncertainty='crt-heap-allocation-cleanup-parent-unresolved'),
    dict(address='0x006443ED', size=9, parent='0x00644343', source_offset=170,
         source_symbol='$L19915', eh_source_symbol='$L19913', eh_source_offset=167,
         decision='pending', uncertainty='crt-calloc-cleanup-parent-unresolved'),
    dict(address='0x00642AB4', size=9, parent='0x00642A61', source_offset=83,
         source_symbol='$L19900', eh_source_symbol='$L19900', eh_source_offset=83,
         decision='pending', uncertainty='crt-free-cleanup-parent-unresolved'),
]
REQUIRED = {
    '0x0064A72B': ('sub', 'edx, dword ptr [eax + 0xc]'),
    '0x0064A72E': ('cmp', 'edx, 0x100000'),
    '0x0064A736': ('add', 'eax, 0x14'),
    '0x0064A75E': ('imul', 'ecx, ecx, 0x204'),
    '0x0064A764': ('lea', 'ecx, [ecx + eax + 0x144]'),
    '0x0064A975': ('push', '0x4000'),
    '0x0064AA1E': ('call', '0x641260'),
    '0x0064AAA5': ('push', '0x41c4'),
    '0x0064AAAA': ('push', '8'),
    '0x0064AACB': ('push', '0x2000'),
    '0x0064AAD0': ('push', '0x100000'),
    '0x0064EC68': ('mov', 'eax, dword ptr [0x68e6fc]'),
    '0x0064EC71': ('push', 'dword ptr [esp + 4]'),
    '0x0064EC75': ('call', 'eax'),
    '0x0064615D': ('call', 'dword ptr [0x6571b4]'),
    '0x00646163': ('ret', '4'),
    '0x006461B2': ('push', '0x8c'),
    '0x006461D7': ('mov', 'dword ptr [esi + 0x54], 0x670748'),
    '0x006461DE': ('mov', 'dword ptr [esi + 0x14], 1'),
    '0x00647F9D': ('add', 'eax, 8'),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if (len(m['functions']) != 13 or set(rows) != set(ACCEPTED) | set(PENDING)
            or {k for k, r in rows.items() if r['decision'] == 'library'} != set(ACCEPTED)
            or any(rows[k]['decision'] != 'pending' or rows[k]['uncertainty'] != reason
                   for k, reason in PENDING.items())):
        raise ValueError('R119 cohort or open lock/TLS cycle decisions differ')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size
                or row['extent_basis'] != 'function-auxiliary-record'):
            raise ValueError('accepted dependency loses its complete own source identity')
    parent = rows['0x0064428A']
    if (parent['size'] != 123 or parent['ledger_size'] != 111
            or parent['span_end'] != '0x00644304' or m['pending_funclets'] != FRAGMENTS):
        raise ValueError('complete allocation source loses its interior cleanup or EH head')
    if sum(rows[k]['size'] for k in PENDING) != 607:
        raise ValueError('open allocator/TLS roots lose whole source extents')
    graph = {**rows, **{r['address']: r for r in m['anchors']}}
    if {(r['address'], r['coff_symbol'], r['size'], r['origin_evidence']) for r in m['anchors']} != {
            ('0x00645414', '__SEH_prolog', 59, 'R117'), ('0x0064544F', '__SEH_epilog', 17, 'R115'),
            ('0x00646658', '__unlock', 21, 'R118'), ('0x00649735', '__heap_init', 81, 'R115'),
            ('0x0064A6CD', '___sbh_heap_init', 72, 'R115'), ('0x00641260', '_memmove', 829, 'R025'),
            ('0x0064AB0F', '___sbh_alloc_new_group', 262, 'R098')}:
        raise ValueError('complete independently replayed heap anchors differ')
    for key in ACCEPTED:
        for b in rows[key]['relocation_bindings']:
            if b['target_kind'] == 'callee':
                callee = graph.get(b['target_address'])
                if (not callee or callee['decision'] not in ('library', 'anchor')
                        or callee['coff_symbol'] != b['symbol']):
                    raise ValueError('accepted heap dependency retains an unreviewed callee')
            elif b['target_kind'] not in ('import', 'state'):
                raise ValueError('accepted heap dependency retains an unresolved field')
    if m['sdk_layout']['size'] != 168 or m['sdk_layout']['values'] != LAYOUT:
        raise ValueError('complete CRT heap/thread layout control differs')
    expected_state = [
        (844948, '?_pnhHeap@@3P6AHI@ZA', '0x0068E6FC', 4),
        (855984, '__newmode', '0x0068E700', 4),
        (1724384, '___tlsindex', '0x0067013C', 4),
        (1724384, '_gpFlsAlloc', '0x0068E330', 16),
        (1528714, '__XcptActTab', '0x00670748', 136),
        (1698134, '__locktable', '0x00670150', 288),
    ]
    if [(r['member_offset'], r['symbol'], r['target_address'], r['size'])
            for r in m['state_data']] != expected_state:
        raise ValueError('whole callback/mode/TLS/exception/lock defining state differs')
    expected_common = {
        '__crtheap': '0x0068FA78', '___active_heap': '0x0068FA7C',
        '___sbh_pHeaderList': '0x0068FA64', '___sbh_pHeaderScan': '0x0068FA6C',
        '___sbh_pHeaderDefer': '0x0068FA5C', '___sbh_cntHeaderList': '0x0068FA60',
        '___sbh_threshold': '0x0068FA68', '___sbh_sizeHeaderList': '0x0068FA70',
        '___sbh_indGroupDefer': '0x0068FA74',
    }
    if (len(m['common_globals']) != 9 or
            {g['symbol']: g['target_address'] for g in m['common_globals']} != expected_common):
        raise ValueError('heap storage lacks all actual COMMON definitions')
    if [(r['symbol'], r['target_address'], r['size'], r['relocations'])
            for r in m['scope_tables']] != [
        ('$T19920', '0x00661210', 12, [dict(offset=8, type='DIR32', symbol='$L19914', addend=0, target_address='0x006442F9')]),
        ('$T19906', '0x00660F88', 12, [dict(offset=8, type='DIR32', symbol='$L19900', addend=0, target_address='0x00642AB4')]),
        ('$T19921', '0x00661220', 12, [dict(offset=8, type='DIR32', symbol='$L19913', addend=0, target_address='0x006443EA')]),
    ]:
        raise ValueError('whole allocator EH scopes lose actual parent label bindings')
    if {(r['address'], r['size']) for r in m['diagnostic_contexts']} != {
            ('0x00646389', 239), ('0x00646725', 49), ('0x00646685', 160), ('0x0064228D', 37)}:
        raise ValueError('complete lock/TLS/error context differs')
    literals = {(r['member_offset'], b['symbol'], b['target_address'])
                for r in m['diagnostic_contexts'] for b in r['relocation_bindings']
                if b['target_kind'] == 'literal'}
    if (len(m['literal_controls']) != 5 or
            {(r['member_offset'], r['symbol'], r['target_address'])
             for r in m['literal_controls']} != literals):
        raise ValueError('FLS dispatch lacks all whole readonly literal definitions')
    witnesses = {w['site']: (w['mnemonic'], w['operands'])
                 for r in m['functions'] + m['diagnostic_contexts']
                 for w in r['instruction_witnesses']}
    if any(witnesses.get(site) != value for site, value in REQUIRED.items()):
        raise ValueError('heap layout/API/callback/TLS/ABI witnesses differ')
    return rows


def check_ledger(row, functions, origins, evidence_only):
    if row['address'] in PENDING and origins.get(row['address'], {}).get('evidence_id') == 'R120':
        module('runtime_cycle_reconciliation', 'origin_reconciliation.py').check_root(
            row, functions[row['address']], origins[row['address']])
        return
    key = row['address']
    function = functions[key]
    if (int(function['size']) != row['ledger_size'] or
            int(function['span_end'], 16) != int(key, 16) + row['ledger_size'] - 1):
        raise ValueError('allocator ledger boundary changed without acceptance')
    expected_interiors = [f['address'] for f in FRAGMENTS if f['parent'] == key]
    interiors = [k for k in functions if int(key, 16) < int(k, 16) < int(key, 16) + row['size']]
    if interiors != expected_interiors:
        raise ValueError('complete allocator extent has an undeclared interior candidate')
    if function['source_file'] or function['match_percent'] != '0.00':
        raise ValueError('origin evidence cannot grant source or exact credit')
    if evidence_only:
        return
    origin = origins[key]
    if key in ACCEPTED:
        if (origin['origin'] != 'library' or origin['disposition'] != 'exclude'
                or origin['evidence_id'] != 'R119' or function['owner'] != 'library'
                or function['status'] != 'excluded' or function['proposed_name'] != ACCEPTED[key][0]):
            raise ValueError('R119 library ledger differs')
    elif (origin['origin'] != 'unknown' or origin['disposition'] != 'review'
          or origin['evidence_id'] != 'R119' or origin['confidence'] != PENDING[key]
          or function['owner'] or function['status'] != 'unclassified'):
        raise ValueError('open allocator/TLS cycle gains ownership')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    old = module('allocator_helpers', 'verify-runtime-error-origins.py')
    c = old.module('allocator_target', 'compare-coff-function.py')
    archive_reader = old.module('allocator_archive', 'verify-runtime-origins.py')
    coff = old.module('allocator_coff', 'coff_data.py')
    startup = old.module('allocator_geometry', 'verify-startup-dependency-origins.py')
    imports_module = old.module('allocator_imports', 'verify-import-origins.py')
    record = old.module('allocator_ledger', 'verify-vendor-record-origins.py')
    facts = old.module('allocator_facts', 'verify-game-lifetime-origins.py')
    literal = old.module('allocator_literal', 'verify-runtime-external-origins.py')
    sections = old.module('allocator_sections', 'verify-compiler-origins.py')
    target = c.verified_target()
    m = json.loads((ROOT / 'config/allocator-thread-origin-evidence.json').read_text())
    if m['evidence_id'] != 'R119' or hashlib.sha256(target).hexdigest() != m['target_sha256']:
        raise ValueError('R119 target identity differs')
    rows = verify_plan(m)
    functions = {r['address']: r for r in record.rows('functions.csv')}
    origins = {r['address']: r for r in record.rows('function-origins.csv')}
    imports = imports_module.pe_imports(target, c)
    target_sections = sections.sections(target)
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest() != m['archive_sha256']:
        raise ValueError('pinned CRT archive differs')
    members = {o: (n, d) for o, n, d in archive_reader.archive_members(archive)}

    def member(row):
        name, data = members[row['member_offset']]
        if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
            raise ValueError('whole cold source member differs')
        return data

    state_map, scope_map = {}, {}
    for row in m['state_data'] + m['scope_tables']:
        raw, description = old.whole_section(member(row), row['symbol'], c, coff)
        a = int(row['target_address'], 16)
        if description != row['source_section'] or description['size'] != row['size']:
            raise ValueError('whole defining data topology differs')
        for definition in description['definitions']:
            state_map[definition['symbol']] = a + definition['offset']
        if raw is None:
            if (not int(description['flags'], 16) & 0x80 or description['relocations']
                    or startup.zero_fill_region(target, a, row['size']) != row['zero_fill_region']):
                raise ValueError('whole callback/mode/FLS storage lacks loader zero-fill geometry')
        else:
            if row in m['state_data'] and not any(
                    base <= a and a + row['size'] <= base + size
                    and flags & 0x80000000 and not flags & 0x20000000
                    for base, size, flags in target_sections):
                raise ValueError('mutable CRT state lacks complete writable PE storage')
            actual = c.pe_bytes_at(target, a, len(raw))
            linked = bytearray(raw)
            if len(description['relocations']) != len(row['relocations']):
                raise ValueError('whole initialized data fields differ')
            for field, b in zip(description['relocations'], row['relocations']):
                if {k: b[k] for k in field} != field:
                    raise ValueError('data relocation metadata differs')
                struct.pack_into('<I', linked, field['offset'], (int(b['target_address'], 16) + field['addend']) & 0xffffffff)
            if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('whole initialized data comparison differs')
            if row in m['scope_tables']:
                literal.check_scalar(actual, actual, row['size'], target_sections, a)
                if struct.unpack_from('<I', raw)[0] != 0xffffffff:
                    raise ValueError('whole allocator scope loses enclosing-level sentinel')
                scope_map[row['symbol']] = a
    for row in m['common_globals']:
        definitions = [d for d in coff.parse_symbols(member(row), c.coff_name)[1] if d['symbol'] == row['symbol']]
        if definitions != [row['source_definition']]:
            raise ValueError('actual heap COMMON definition differs')
        startup.check_common_definition(definitions[0])
        a = int(row['target_address'], 16)
        if startup.zero_fill_region(target, a, 4) != row['zero_fill_region']:
            raise ValueError('actual heap storage lacks common/loader provenance')
        state_map[row['symbol']] = a
    for row in m['literal_controls']:
        source = literal.readonly_member_data(member(row), row['symbol'], row, c.coff_name)
        a = int(row['target_address'], 16)
        literal.check_scalar(source, c.pe_bytes_at(target, a, len(source)), len(source), target_sections, a)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    scratch = ROOT / 'build/origin-allocator-thread-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path = Path(temp) / 'VendorMember.obj'
        layout = m['sdk_layout']
        probe = ROOT / layout['probe']
        profile = old.PROFILE + ['/D_CRTBLD', '/D_MT', '/I', '.tools/msvc710/Vc7/crt/src']
        if layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']:
            raise ValueError('natural CRT layout probe differs')
        if set(layout['headers']) != {'crt/src/winheap.h', 'crt/src/mtdll.h', 'crt/src/cruntime.h', 'PlatformSDK/Include/WinNT.h'}:
            raise ValueError('complete pinned CRT layout headers differ')
        for filename, digest in layout['headers'].items():
            if hashlib.sha256((ROOT / '.tools/msvc710/Vc7' / filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned CRT layout header differs')
        subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(probe), str(path), *profile],
                       cwd=ROOT, capture_output=True, text=True, check=True)
        data = path.read_bytes()
        definition = next(d for d in coff.parse_symbols(data, c.coff_name)[1] if d['symbol'] == layout['symbol'])
        raw, names = coff.readonly_section(data, definition['section'], c.coff_name)
        if (definition['offset'] or names != [dict(symbol=layout['symbol'], offset=0)]
                or len(raw) != 168 or list(struct.unpack('<42I', raw)) != LAYOUT):
            raise ValueError('whole cold readonly CRT layout array differs')
        for row in m['functions'] + m['anchors'] + m['diagnostic_contexts']:
            key = row['address']
            a = int(key, 16)
            if key in rows:
                check_ledger(row, functions, origins, args.evidence_only)
            elif row['decision'] == 'anchor':
                if origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']:
                    raise ValueError('retained complete heap anchor origin differs')
            elif int(functions[key]['size']) != row['ledger_size']:
                module('runtime_cycle_context_reconciliation', 'origin_reconciliation.py').check_root(
                    row, functions[key], origins[key])
            path.write_bytes(member(row))
            source, fields = c.object_function(path, row['coff_symbol'])
            actual = c.pe_bytes_at(target, a, row['size'])
            if (len(source) != row['size'] or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('complete own auxiliary extent/hash differs')
            old.compare_fields(source, fields, actual, a, row['relocation_bindings'], c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('full local relocation provenance differs')
            if key == '0x00641260':
                # R025 independently owns the whole code and embedded switch
                # data extent. Linear disassembly must not turn that data into
                # instructions or truncate this complete byte/field comparison.
                if row['control_flow_basis'] != 'R025 full code/switch-data extent replay via R118':
                    raise ValueError('mixed memmove extent loses its complete independent control')
                continue
            ins = list(decoder.disasm(actual, a))
            starts = {i.address for i in ins}
            if sum(i.size for i in ins) != row['size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('whole allocator/thread instruction inventory differs')
            branches = [dict(site=f'0x{i.address:08X}', target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP)]
            if branches != row['branches'] or any(int(b['target'], 16) not in starts for b in branches):
                raise ValueError('whole allocator/thread branch closure differs')
            indirect = [dict(site=f'0x{i.address:08X}', operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            if indirect != row['indirect_calls']:
                raise ValueError('whole callback/API inventory differs')
            if [dict(site=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str) for i in ins] != row['instruction_witnesses']:
                raise ValueError('full heap/API/callback/ABI witnesses differ')
            for b in row['relocation_bindings']:
                kind = b['target_kind']
                if kind == 'import':
                    startup.check_import_binding(b, imports)
                elif kind == 'state' and (b['type'] != 'DIR32' or state_map.get(b['symbol']) != int(b['target_address'], 16)):
                    raise ValueError('heap/thread state loses complete defining provenance')
                elif kind == 'scope-table' and scope_map.get(b['symbol']) != int(b['target_address'], 16):
                    raise ValueError('allocator scope loses its complete source definition')
        # Interior cleanup entries are labels in complete primary source bodies.
        for fragment in m['pending_funclets']:
            parent = rows[fragment['parent']]
            defs = coff.parse_symbols(member(parent), c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == parent['coff_symbol'])
            for symbol, offset in [(fragment['source_symbol'], fragment['source_offset']),
                                   (fragment['eh_source_symbol'], fragment['eh_source_offset'])]:
                entry = next(d for d in defs if d['symbol'] == symbol)
                if entry['section'] != primary['section'] or entry['offset'] - primary['offset'] != offset:
                    raise ValueError('interior cleanup loses its whole source parent label')
            f, o = functions[fragment['address']], origins[fragment['address']]
            if o['evidence_id'] == 'R120':
                module('runtime_cycle_label_reconciliation', 'origin_reconciliation.py').check_label(
                    fragment, f, o, functions, origins)
                continue
            if (int(f['size']) != fragment['size'] or int(f['span_end'], 16) != int(fragment['address'], 16) + fragment['size'] - 1
                    or f['source_file'] or f['match_percent'] != '0.00' or o['origin'] != 'unknown'
                    or o['disposition'] != 'review' or f['owner'] or f['status'] != 'unclassified'):
                raise ValueError('pending allocation cleanup gains source/exact/origin credit')
            if not args.evidence_only and (o['evidence_id'] != 'R119' or o['confidence'] != fragment['uncertainty']):
                raise ValueError('pending cleanup loses its explicit uncertainty')
        for scope in m['scope_tables']:
            defs = coff.parse_symbols(member(scope), c.coff_name)[1]
            owner = rows[scope['parent']]
            primary = next(d for d in defs if d['symbol'] == owner['coff_symbol'])
            for b in scope['relocations']:
                label = next(d for d in defs if d['symbol'] == b['symbol'])
                if (label['section'] != primary['section'] or
                        int(b['target_address'], 16) != int(owner['address'], 16) + label['offset'] - primary['offset']):
                    raise ValueError('allocator EH label is not inside its complete source parent')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-termination-lock-origins.py'],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('retained lock/runtime replay failed: ' + result.stderr[-1000:])
    print('R119 origins OK: six library dependencies / 1818 bytes; complete small-block allocation/free/region graph, '
          'new-handler callback and RET 4 TLS fallback; full CRT layout / 168 bytes and defining data/API/EH provenance; '
          'seven roots / 607 source bytes and three interior cleanup candidates / 27 bytes retained as historical pending snapshots; current ownership recorded separately; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
