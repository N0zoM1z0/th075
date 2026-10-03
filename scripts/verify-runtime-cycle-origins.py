#!/usr/bin/env python3
"""Replay the bounded R120 CRT runtime cycle without treating labels as functions."""
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
ROOTS = {
    '0x00648C70': ('__NMSG_WRITE', 375), '0x00648E11': ('__FF_MSGBANNER', 57),
    '0x00640611': ('@__security_check_cookie@4', 14), '0x006405E0': ('_report_failure', 49),
    '0x0064529E': ('___security_error_handler', 328), '0x0064425B': ('__exit', 17),
    '0x00644187': ('_doexit', 195), '0x00646725': ('__lock', 49),
    '0x00646685': ('__mtinitlocknum', 160), '0x0064162B': ('___onexitinit', 40),
    '0x00644331': ('_malloc', 18), '0x00644305': ('__nh_malloc', 44),
    '0x0064428A': ('__heap_alloc', 123), '0x00642A61': ('_free', 113),
    '0x00647F98': ('__errno', 9), '0x00646196': ('__getptd', 113),
    '0x00644343': ('_calloc', 187), '0x0064228D': ('__amsg_exit', 37),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def verify_plan(m):
    reconciliation = module('cycle_reconciliation_plan', 'origin_reconciliation.py')
    prior = {n: json.loads((ROOT / f'config/{n}-origin-evidence.json').read_text())
             for n in ['startup-dependency', 'runtime-error', 'security-eh',
                       'termination-lock', 'allocator-thread']}
    historical = {r['address']: r for p in prior.values() for r in p['functions']
                  if r['decision'] == 'pending'}
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 18 or set(rows) != set(ROOTS):
        raise ValueError('bounded runtime cycle cohort differs')
    for key, (symbol, size) in ROOTS.items():
        r = rows[key]
        if (r['decision'] != 'library' or r['coff_symbol'] != symbol or r['size'] != size
                or r['extent_basis'] != 'function-auxiliary-record'):
            raise ValueError('runtime cycle loses whole own source extent')
        reconciliation.same_source(historical[key], r)
    graph = {**rows, **{r['address']: r for r in m['anchors']}}
    if len(m['anchors']) != 18 or sum(r['size'] for r in m['anchors']) != 3114:
        raise ValueError('runtime cycle loses complete independent code controls')
    for r in rows.values():
        for b in r['relocation_bindings']:
            if b['target_kind'] == 'callee':
                dest = graph.get(b['target_address'])
                if not dest or b['symbol'] not in [dest['coff_symbol'], *dest.get('source_aliases', [])]:
                    raise ValueError('runtime cycle retains unresolved code dependency')
            elif b['target_kind'] not in ('import', 'state', 'scope-table', 'literal'):
                raise ValueError('runtime cycle retains an unreviewed relocation')
    expected = prior['termination-lock']['pending_funclets'] + prior['allocator-thread']['pending_funclets']
    if len(m['interior_labels']) != 5:
        raise ValueError('runtime cycle loses declared interior labels')
    for old, new in zip(expected, m['interior_labels']):
        if any(old[k] != new[k] for k in ('address', 'size', 'parent', 'source_offset', 'source_symbol')):
            raise ValueError('runtime interior label loses historical identity')
        if new['decision'] != 'library' or new['extent_basis'] != 'interior-label-in-complete-vendor-primary':
            raise ValueError('runtime interior label becomes a fabricated standalone body')
    if (len(m['state_data']) != 15 or sum(r['size'] for r in m['state_data']) != 1048
            or len(m['common_globals']) != 11 or len(m['scope_tables']) != 7
            or len(m['literal_controls']) != 38 or sum(r['data_size'] for r in m['literal_controls']) != 1513):
        raise ValueError('runtime cycle loses complete defining data controls')
    for name in ('common_globals', 'range_markers', 'callback_ranges', 'onexit_registration'):
        expected = (prior['allocator-thread'][name] + prior['termination-lock'][name]
                    if name == 'common_globals' else prior['termination-lock'][name])
        if m[name] != expected:
            raise ValueError('runtime cycle loses actual COMMON/initializer provenance')
    if [(r['symbol'], r['target_address'], r['parent']) for r in m['scope_tables'][-2:]] != [
            ('$T19882', '0x00660E68', '0x006405E0'), ('$T20027', '0x006614D8', '0x0064529E')]:
        raise ValueError('runtime failure loses complete source EH scopes')
    if [(r['address'], r['size'], r['decision']) for r in m['diagnostic_contexts']] != [
            ('0x00646389', 239, 'diagnostic')]:
        raise ValueError('FLS initializer context gains unearned acceptance')
    if m['retained_controls'] != [dict(evidence_id=f'R{i}', manifest=n+'-origin-evidence.json')
            for i, n in zip(range(115, 120), prior)]:
        raise ValueError('runtime cycle loses cold independent controls')
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    old = module('cycle_old', 'verify-runtime-error-origins.py')
    c = old.module('cycle_target', 'compare-coff-function.py')
    archive_reader = old.module('cycle_archive', 'verify-runtime-origins.py')
    coff = old.module('cycle_coff', 'coff_data.py')
    startup = old.module('cycle_geometry', 'verify-startup-dependency-origins.py')
    security = old.module('cycle_sections', 'verify-security-eh-origins.py')
    imports_module = old.module('cycle_imports', 'verify-import-origins.py')
    record = old.module('cycle_ledger', 'verify-vendor-record-origins.py')
    facts = old.module('cycle_facts', 'verify-game-lifetime-origins.py')
    literal = old.module('cycle_literal', 'verify-runtime-external-origins.py')
    sections = old.module('cycle_pe_sections', 'verify-compiler-origins.py')
    reconciliation = old.module('cycle_reconciliation', 'origin_reconciliation.py')
    target = c.verified_target()
    m = reconciliation.manifest()
    rows = verify_plan(m)
    functions = {r['address']: r for r in record.rows('functions.csv')}
    origins = {r['address']: r for r in record.rows('function-origins.csv')}
    for key, row in rows.items():
        actual_interiors = {k for k in functions if int(key, 16) < int(k, 16) < int(key, 16) + row['size']}
        expected_interiors = {r['address'] for r in m['interior_labels'] if r['parent'] == key}
        if actual_interiors != expected_interiors:
            raise ValueError('complete runtime primary has an undeclared interior candidate')
    imports = imports_module.pe_imports(target, c)
    target_sections = sections.sections(target)
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest() != m['archive_sha256']:
        raise ValueError('pinned CRT archive differs')
    members = {o: (n, d) for o, n, d in archive_reader.archive_members(archive)}

    def member(row):
        name, data = members[row['member_offset']]
        if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
            raise ValueError('complete source member identity differs')
        return data

    state_map, scope_map = {}, {}
    for row in m['state_data'] + m['scope_tables'] + m['range_markers'] + [m['onexit_registration']]:
        raw, desc = old.whole_section(member(row), row['symbol'], c, coff)
        a = int(row['target_address'], 16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('whole defining data topology differs')
        if 'section_name' in row and security.source_section_name(member(row), row['symbol'], c, coff) != row['section_name']:
            raise ValueError('initializer loses its actual CRT subsection')
        for definition in desc['definitions']:
            state_map[definition['symbol']] = a + definition['offset']
        if raw is None:
            if (not int(desc['flags'], 16) & 0x80 or desc['relocations']
                    or startup.zero_fill_region(target, a, row['size']) != row['zero_fill_region']):
                raise ValueError('runtime state loses actual loader zero-fill geometry')
            continue
        actual = c.pe_bytes_at(target, a, len(raw))
        linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('whole initialized data fields differ')
        for field, b in zip(desc['relocations'], row['relocations']):
            if {k: b[k] for k in field} != field:
                raise ValueError('data relocation metadata differs')
            struct.pack_into('<I', linked, field['offset'], (int(b['target_address'], 16) + field['addend']) & 0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('whole initialized data comparison differs')
        if row in m['state_data'] and not any(base <= a and a + row['size'] <= base + size
                and flags & 0x80000000 and not flags & 0x20000000 for base, size, flags in target_sections):
            raise ValueError('runtime state loses full writable target storage')
        if row in m['scope_tables']:
            literal.check_scalar(actual, actual, row['size'], target_sections, a)
            if struct.unpack_from('<I', raw)[0] != 0xffffffff:
                raise ValueError('runtime scope loses enclosing-level sentinel')
            scope_map[row['symbol']] = a
    for row in m['common_globals']:
        defs = [d for d in coff.parse_symbols(member(row), c.coff_name)[1] if d['symbol'] == row['symbol']]
        if defs != [row['source_definition']]:
            raise ValueError('actual COMMON definition differs')
        startup.check_common_definition(defs[0])
        a = int(row['target_address'], 16)
        if startup.zero_fill_region(target, a, 4) != row['zero_fill_region']:
            raise ValueError('COMMON runtime storage lacks loader provenance')
        state_map[row['symbol']] = a
    literal_map = {}
    for row in m['literal_controls']:
        source = literal.readonly_member_data(member(row), row['symbol'], row, c.coff_name)
        a = int(row['target_address'], 16)
        literal.check_scalar(source, c.pe_bytes_at(target, a, len(source)), len(source), target_sections, a)
        literal_map[(row['member_offset'], row['symbol'])] = a
    for row in m['callback_ranges']:
        actual = c.pe_bytes_at(target, int(row['address'], 16), row['size'])
        if (hashlib.sha256(actual).hexdigest() != row['sha256'] or
                [f'0x{x:08X}' for x in struct.unpack('<'+'I'*(len(actual)//4), actual)] != row['entries']):
            raise ValueError('whole callback range differs')
    table = next(r for r in m['state_data'] if r['symbol'] == '_rterrs')
    for b in table['relocations']:
        if literal_map.get((table['member_offset'], b['symbol'])) != int(b['target_address'], 16):
            raise ValueError('runtime error table lacks whole defining message')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    scratch = ROOT / 'build/origin-runtime-cycle-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path = Path(temp) / 'VendorMember.obj'
        for row in m['functions'] + m['anchors'] + m['diagnostic_contexts']:
            key, a = row['address'], int(row['address'], 16)
            if key in rows and not args.evidence_only:
                reconciliation.check_root(row, functions[key], origins[key])
            elif row['decision'] == 'anchor' and (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']):
                raise ValueError('retained independent code origin differs')
            path.write_bytes(member(row))
            source, fields = c.object_function(path, row['coff_symbol'])
            actual = c.pe_bytes_at(target, a, row['size'])
            if (len(source) != row['size'] or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('complete own source auxiliary extent/hash differs')
            old.compare_fields(source, fields, actual, a, row['relocation_bindings'], c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('full local relocation provenance differs')
            if row['decision'] == 'anchor':
                if row['control_flow_basis'] != 'Independent retained full runtime/shared-tail evidence through R119':
                    raise ValueError('anchor loses its independent full control-flow replay')
                for alias in row.get('source_aliases', []):
                    defs = coff.parse_symbols(member(row), c.coff_name)[1]
                    startup.check_alias_definition(next(d for d in defs if d['symbol'] == row['coff_symbol']), next(d for d in defs if d['symbol'] == alias))
                continue
            ins = list(decoder.disasm(actual, a))
            starts = {i.address for i in ins}
            if sum(i.size for i in ins) != row['size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('whole runtime instruction inventory differs')
            branches = [dict(site=f'0x{i.address:08X}', target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP)]
            if branches != row['branches']:
                raise ValueError('whole runtime branch inventory differs')
            for i in ins:
                if i.group(CS_GRP_JUMP) and i.operands[0].imm not in starts:
                    if not any(b['type'] == 'REL32' and b['target_kind'] == 'callee'
                               and b['offset'] == i.address-a+i.imm_offset
                               and int(b['target_address'], 16) == i.operands[0].imm for b in row['relocation_bindings']):
                        raise ValueError('runtime branch exits without complete typed callee')
            if [dict(site=f'0x{i.address:08X}', operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM] != row['indirect_calls']:
                raise ValueError('whole callback/API inventory differs')
            if [dict(site=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str) for i in ins] != row['instruction_witnesses']:
                raise ValueError('whole runtime callback/API/ABI witnesses differ')
            for b in row['relocation_bindings']:
                kind, dest = b['target_kind'], int(b['target_address'], 16)
                if kind == 'import':
                    startup.check_import_binding(b, imports)
                elif kind == 'state' and (b['type'] != 'DIR32' or state_map.get(b['symbol']) != dest):
                    raise ValueError('runtime state lacks defining provenance')
                elif kind == 'scope-table' and scope_map.get(b['symbol']) != dest:
                    raise ValueError('runtime scope loses complete definition')
                elif kind == 'literal' and literal_map.get((row['member_offset'], b['symbol'])) != dest:
                    raise ValueError('runtime literal loses complete definition')
        for fragment in m['interior_labels']:
            parent = rows[fragment['parent']]
            defs = coff.parse_symbols(member(parent), c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == parent['coff_symbol'])
            for symbol, offset in [(fragment['source_symbol'], fragment['source_offset']), (fragment['eh_source_symbol'], fragment['eh_source_offset'])]:
                entry = next(d for d in defs if d['symbol'] == symbol)
                if entry['section'] != primary['section'] or entry['offset'] - primary['offset'] != offset:
                    raise ValueError('interior cleanup loses complete source parent label')
            if int(fragment['address'], 16) != int(parent['address'], 16) + fragment['source_offset']:
                raise ValueError('interior cleanup has a fabricated entry')
            if not args.evidence_only:
                reconciliation.check_label(fragment, functions[fragment['address']], origins[fragment['address']], functions, origins)
        for scope in m['scope_tables']:
            owner = rows[scope['parent']]
            defs = coff.parse_symbols(member(scope), c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == owner['coff_symbol'])
            for b in scope['relocations']:
                label = next(d for d in defs if d['symbol'] == b['symbol'])
                if label['section'] != primary['section'] or int(b['target_address'], 16) != int(owner['address'], 16) + label['offset'] - primary['offset']:
                    raise ValueError('runtime EH pointer loses actual full parent source label')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-allocator-thread-origins.py'], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('retained independent runtime replay failed: ' + result.stderr[-1500:])
    print('R120 origins OK: 18 complete library bodies / 1928 bytes / 166 typed fields; five existing interior labels / 50 overlapping bytes; complete defining code/data/API/EH provenance and cold R115-R119 controls; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
