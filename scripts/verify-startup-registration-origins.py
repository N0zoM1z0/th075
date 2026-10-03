#!/usr/bin/env python3
"""Replay the bounded R121 startup/registration graph without treating labels as functions."""
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
    '0x006422B2': ('_fast_error_exit', 36), '0x00646603': ('__mtdeletelocks', 85),
    '0x00646166': ('__mtterm', 29), '0x0064168B': ('_atexit', 18),
    '0x00641653': ('__onexit', 56), '0x006415AB': ('__onexit_lk', 128),
    '0x00646756': ('_realloc', 429), '0x00646903': ('__msize', 118),
    '0x006440D5': ('__lockexit', 9), '0x006440DE': ('__unlockexit', 9),
}
PENDING = {
    '0x00646389': 'crt-thread-initialization-locale-cleanup-dependencies-unresolved',
    '0x0064411D': 'crt-cinit-floating-point-conversion-control-dependencies-unresolved',
}
CONFIDENCE = 'complete-vendor-startup-registration-code-data-api-eh-provenance'
LABEL_CONFIDENCE = 'complete-interior-label-of-reviewed-vendor-parent'



def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/startup-registration-origin-evidence.json').read_text())
    reconciliation = module('registration_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R121' or m['target_sha256'] != reconciliation.TARGET:
        raise ValueError('startup registration target identity differs')
    return m


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 12 or set(rows) != set(ACCEPTED) | set(PENDING):
        raise ValueError('bounded startup registration cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record'):
            raise ValueError('accepted registration dependency loses complete own source extent')
    if any(rows[key]['decision'] != 'pending' or rows[key]['uncertainty'] != reason for key, reason in PENDING.items()):
        raise ValueError('open locale/floating-point parents gain ownership')
    if (rows['0x00646389']['size'] != 239 or rows['0x0064411D']['size'] != 106
            or rows['0x00641653']['ledger_size'] != 50 or rows['0x00646903']['ledger_size'] != 106):
        raise ValueError('historical parent or complete cleanup extent differs')
    reconciliation = module('registration_source_identity', 'origin_reconciliation.py')
    historical = json.loads((ROOT / 'config/startup-dependency-origin-evidence.json').read_text())
    reconciliation.same_source(next(r for r in historical['functions'] if r['address'] == '0x006422B2'), rows['0x006422B2'])
    graph = {**rows, **{r['address']: r for r in m['anchors']}}
    if len(m['anchors']) != 19 or sum(r['size'] for r in m['anchors']) != 4280:
        raise ValueError('complete independent startup anchors differ')
    for key in ACCEPTED:
        for b in rows[key]['relocation_bindings']:
            if b['target_kind'] == 'callee':
                dest = graph.get(b['target_address'])
                if not dest or dest['decision'] not in ('library', 'anchor') or dest['coff_symbol'] != b['symbol']:
                    raise ValueError('accepted registration graph retains an unreviewed callee')
            elif b['target_kind'] not in ('state', 'import', 'scope-table'):
                raise ValueError('accepted registration graph retains unresolved provenance')
    if [(r['address'],r['size'],r['parent'],r['source_offset'],r['eh_source_offset']) for r in m['interior_labels']] != [
            ('0x00641685',6,'0x00641653',50,50), ('0x00646970',9,'0x00646903',109,106),
            ('0x006468BE',9,'0x00646756',360,352)]:
        raise ValueError('registration cleanup loses actual full parent and EH entry')
    if any(r['decision'] != 'library' or r['extent_basis'] != 'interior-label-in-complete-vendor-primary' for r in m['interior_labels']):
        raise ValueError('registration interior becomes fabricated standalone source')
    if [(r['address'],r['size'],r['parent'],r['source_offset'],r['eh_source_offset'],r['decision']) for r in m['pending_labels']] != [
            ('0x00646339',9,'0x00646207',306,301,'pending'),('0x00646345',9,'0x00646207',318,315,'pending')]:
        raise ValueError('unclosed fiber cleanup loses its original labels')
    if [(r['symbol'],r['target_address'],r['size']) for r in m['state_data']] != [
            ('__aenvptr','0x0068E2CC',12), ('__locktable','0x00670150',288),
            ('__newmode','0x0068E700',4), ('___tlsindex','0x0067013C',4),
            ('_gpFlsAlloc','0x0068E330',16), ('__XcptActTab','0x00670748',136),
            ('__fltused','0x0066FE34',20)]:
        raise ValueError('whole defining lock/TLS/FP state differs')
    if (len(m['common_globals']) != 5 or len(m['scope_tables']) != 5
            or sum(r['size'] for r in m['scope_tables']) != 72
            or len(m['literal_controls']) != 7 or sum(r['data_size'] for r in m['literal_controls']) != 89
            or len(m['range_markers']) != 10 or len(m['callback_ranges']) != 5):
        raise ValueError('complete registration/storage/scope/API controls differ')
    if {(r['address'],r['size'],r['ledger_size'],r['decision']) for r in m['diagnostic_contexts']} != {
            ('0x00646207',327,None,'diagnostic'),('0x006496D7',68,None,'diagnostic'),
            ('0x006405C2',30,30,'diagnostic'),('0x00642B09',208,208,'diagnostic'),
            ('0x0064057A',56,56,'diagnostic'),('0x0064520F',41,41,'diagnostic'),
            ('0x006451BD',18,18,'diagnostic')}:
        raise ValueError('complete unresolved locale/FP/RTC contexts gain candidate credit')
    if m['retained_controls'] != [dict(evidence_id='R120',manifest='runtime-cycle-origin-evidence.json')]:
        raise ValueError('startup graph loses its independent cold runtime controls')
    return rows


def check_ledger(row, function, origin):
    if row['address'] == '0x00646389' and origin.get('evidence_id') == 'R122':
        module('locale_thread_reconciliation', 'verify-locale-thread-origins.py').check_historical_root(
            row, function, origin)
        return
    key = row['address']
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('startup registration loses complete origin-only extent')
    if key in ACCEPTED:
        if (origin['evidence_id'] != 'R121' or origin['origin'] != 'library'
                or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
                or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
                or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
                or function['proposed_name'] != row['coff_symbol']):
            raise ValueError('startup registration library ledger differs')
    elif (origin['evidence_id'] != 'R121' or origin['origin'] != 'unknown'
            or origin['disposition'] != 'review' or origin['confidence'] != PENDING[key]
            or function['owner'] or function['module'] or function['status'] != 'unclassified'):
        raise ValueError('unclosed startup locale/FP parent gains ownership')


def check_historical_startup(row, function, origin):
    if row['address'] != '0x006422B2':
        raise ValueError('historical R121 reconciliation is outside its startup source')
    current = next(r for r in manifest()['functions'] if r['address'] == row['address'])
    module('registration_historical_identity', 'origin_reconciliation.py').same_source(row, current)
    check_ledger(current, function, origin)


def check_label(row, function, origin, functions, origins, rows):
    if row['decision'] == 'pending' and origin.get('evidence_id') == 'R122':
        module('locale_thread_label_reconciliation', 'verify-locale-thread-origins.py').check_historical_label(
            row, function, origin, functions, origins)
        return
    if row['decision'] == 'library':
        parent = rows[row['parent']]
        if parent['decision'] != 'library' or parent['address'] not in ACCEPTED:
            raise ValueError('interior startup cleanup retains an unaccepted parent')
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
        expected_origin, disposition, confidence, status = 'library', 'exclude', LABEL_CONFIDENCE, 'excluded'
        owner, subsystem = 'library', 'VC71CRT'
    else:
        expected_origin, disposition, confidence, status = 'unknown', 'review', row['uncertainty'], 'unclassified'
        owner, subsystem = '', ''
    if (origin['evidence_id'] != 'R121' or origin['origin'] != expected_origin or origin['disposition'] != disposition
            or origin['confidence'] != confidence or origin['subsystem'] != subsystem
            or function['owner'] != owner or function['module'] != subsystem or function['status'] != status
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16)+row['size']-1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('interior startup cleanup gains unsupported parent/source credit')


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
    m = manifest()
    rows = verify_plan(m)
    functions = {r['address']: r for r in record.rows('functions.csv')}
    origins = {r['address']: r for r in record.rows('function-origins.csv')}
    for key, row in rows.items():
        actual_interiors = {k for k in functions if int(key, 16) < int(k, 16) < int(key, 16) + row['size']}
        expected_interiors = {r['address'] for r in m['interior_labels'] if r['parent'] == key}
        if actual_interiors != expected_interiors:
            raise ValueError('complete runtime primary has an undeclared interior candidate')
    for row in m['diagnostic_contexts']:
        key = row['address']
        if row['ledger_size'] is None:
            if key in functions:
                raise ValueError('non-inventoried diagnostic gains candidate credit')
        elif int(functions[key]['size']) != row['ledger_size']:
            raise ValueError('unaccepted diagnostic candidate boundary differs')
    for key in ('0x00646207', '0x006496D7'):
        row = next(r for r in m['diagnostic_contexts'] if r['address'] == key)
        actual_interiors = {k for k in functions if int(key, 16) < int(k, 16) < int(key, 16) + row['size']}
        expected_interiors = {r['address'] for r in m['pending_labels'] if r['parent'] == key}
        if actual_interiors != expected_interiors:
            raise ValueError('non-inventoried diagnostic loses actual interior provenance')
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
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    scratch = ROOT / 'build/origin-startup-registration-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path = Path(temp) / 'VendorMember.obj'
        for row in m['functions'] + m['anchors'] + m['diagnostic_contexts']:
            key, a = row['address'], int(row['address'], 16)
            if key in rows and not args.evidence_only:
                check_ledger(row, functions[key], origins[key])
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
                if row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R120':
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
        parents = {**rows, **{r['address']: r for r in m['diagnostic_contexts']}}
        for fragment in m['interior_labels'] + m['pending_labels']:
            parent = parents[fragment['parent']]
            defs = coff.parse_symbols(member(parent), c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == parent['coff_symbol'])
            for symbol, offset in [(fragment['source_symbol'], fragment['source_offset']), (fragment['eh_source_symbol'], fragment['eh_source_offset'])]:
                entry = next(d for d in defs if d['symbol'] == symbol)
                if entry['section'] != primary['section'] or entry['offset'] - primary['offset'] != offset:
                    raise ValueError('interior cleanup loses complete source parent label')
            if int(fragment['address'], 16) != int(parent['address'], 16) + fragment['source_offset']:
                raise ValueError('interior cleanup has a fabricated entry')
            if not args.evidence_only:
                check_label(fragment, functions[fragment['address']], origins[fragment['address']], functions, origins, rows)
        for scope in m['scope_tables']:
            owner = parents[scope['parent']]
            defs = coff.parse_symbols(member(scope), c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == owner['coff_symbol'])
            for b in scope['relocations']:
                label = next(d for d in defs if d['symbol'] == b['symbol'])
                if label['section'] != primary['section'] or int(b['target_address'], 16) != int(owner['address'], 16) + label['offset'] - primary['offset']:
                    raise ValueError('runtime EH pointer loses actual full parent source label')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-runtime-cycle-origins.py'], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('retained independent runtime replay failed: ' + result.stderr[-1500:])
    print('R121 origins OK: ten complete library bodies / 917 bytes / 71 typed fields; three interior labels / 24 overlapping bytes; two startup parents / 345 bytes and two fiber labels retained as historical pending snapshots; complete source/data/API/EH provenance and independent cold R120 controls; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
