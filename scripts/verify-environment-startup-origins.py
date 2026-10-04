#!/usr/bin/env python3
"""Replay the bounded R126 complete environment, command-line, PE entry and exception graph."""
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
ACCEPTED = {'0x0064232C': ('_WinMainCRTStartup', 469), '0x00649327': ('___crtGetEnvironmentStringsA', 290), '0x00649285': ('__setargv', 162), '0x00649052': ('__setenvp', 199), '0x00648FF5': ('__wincmdln', 93), '0x00648E76': ('__XcptFilter', 356), '0x00649119': ('_parse_cmdline', 364), '0x006515F3': ('__ismbblead', 17), '0x0064424A': ('_exit', 17), '0x0064426C': ('__cexit', 15), '0x0065152C': ('_x_ismbbtype', 51)}
AUXILIARY = {'0x0064427B': ('__c_exit', 15)}
COMMON = {'__acmdln': ('0x0068FBC4', 4), '___mbctype_initialized': ('0x0068FBB4', 4), '___env_initialized': ('0x0068FBA8', 4), '__mbctype': ('0x0068E800', 257)}
STATE = {('___newctype', '0x006626B0', 1284), ('?_pgmname@?1??_setargv@@9@9', '0x0068E578', 261), ('?f_use@?1??__crtGetEnvironmentStringsA@@9@9', '0x0068E680', 4), ('__pctype', '0x006708C0', 8), ('__XcptActTab', '0x00670748', 136), ('__umaskval', '0x0068E2E4', 72), ('__aenvptr', '0x0068E2CC', 12)}
CONFIDENCE = 'complete-vendor-environment-commandline-pe-startup-code-data-api-eh-provenance'
LAYOUT = [4, 2, 260, 261, 257, 4, 0, 120, 148, 0, 4, 8, 12, 16, 68, 44, 48, 1, 10, 64, 60, 23117, 17744, 267, 523, 248, 264, 24, 24, 116, 132, 232, 248, 14, 140, 84, 88, 92, 12, 0, 4, 8, 4, 8, 11, 129, 130, 131, 132, 133, 134, 138, 4294967295, 0, 1]
LAYOUT_HEADERS = {'crt/src/stdlib.h', 'crt/src/cruntime.h', 'crt/src/excpt.h', 'crt/src/mbctype.h', 'crt/src/signal.h', 'PlatformSDK/Include/WinBase.h', 'PlatformSDK/Include/WinNT.h', 'crt/src/float.h', 'crt/src/mtdll.h'}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/environment-startup-origin-evidence.json').read_text())
    reconciliation = module('codepage_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R126' or m['target_sha256'] != reconciliation.TARGET:
        raise ValueError('initializer target identity differs')
    return m


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 11 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded environment startup cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != size or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record' or row['indirect_jumps']):
            raise ValueError('startup loses its whole own auxiliary extent/control flow')
    if (len(m['auxiliary_bodies']) != 1
            or {r['address']: (r['coff_symbol'], r['size']) for r in m['auxiliary_bodies']} != AUXILIARY
            or any(r['decision'] != 'library-control' or r['ledger_size'] is not None
                   or r['code_size'] != r['size'] for r in m['auxiliary_bodies'])):
        raise ValueError('c_exit control gains fabricated candidate credit')
    for key in ('diagnostic_contexts', 'pending_labels', 'interior_labels', 'range_markers',
                'initializer_registrations', 'callback_ranges'):
        if m[key]:
            raise ValueError('startup graph gains unresolved or invented dependencies')
    if len(m['anchors']) != 19 or sum(r['size'] for r in m['anchors']) != 2675:
        raise ValueError('independent whole startup anchors differ')
    graph = {**rows, **{r['address']: r for r in m['auxiliary_bodies'] + m['anchors']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                dest = graph.get(b['target_address'])
                symbols = [] if not dest else [dest['coff_symbol'], *dest.get('source_aliases', [])]
                if not dest or b['symbol'] not in symbols or dest['decision'] not in ('library', 'library-control', 'anchor'):
                    raise ValueError('startup retains an unreviewed actual complete callee')
            elif b['target_kind'] == 'authored-entry':
                if (row['address'] != '0x0064232C' or b['symbol'] != '_WinMain@16'
                        or b['offset'] != 384 or b['type'] != 'REL32' or b['addend']
                        or b['target_address'] != '0x00602A60'):
                    raise ValueError('startup game call loses actual typed stdcall provenance')
            elif b['target_kind'] not in ('state', 'import', 'scope-table', 'literal'):
                raise ValueError('startup retains unresolved data/API/EH provenance')
    if (len(m['state_data']) != 7 or sum(r['size'] for r in m['state_data']) != 1777
            or {(r['symbol'], r['target_address'], r['size']) for r in m['state_data']} != STATE):
        raise ValueError('startup loses whole defining sections or accepts convenient prefixes')
    if len(m['common_globals']) != 4 or {r['symbol']: (r['target_address'], r['size']) for r in m['common_globals']} != COMMON:
        raise ValueError('startup loses full actual COMMON definitions')
    for r in m['common_globals']:
        check_common(r, r['source_definition'])
    if (len(m['scope_tables']) != 1 or m['scope_tables'][0]['size'] != 12
            or m['scope_tables'][0]['parent'] != '0x0064232C'
            or len(m['scope_tables'][0]['relocations']) != 2
            or len(m['literal_controls']) != 1 or m['literal_controls'][0]['data_size'] != 1):
        raise ValueError('startup loses full EH scope and null command-line literal')
    if m['sdk_layout']['size'] != 220 or m['sdk_layout']['values'] != LAYOUT:
        raise ValueError('startup loses natural PE32/PE32+ SDK and vendor layout controls')
    expected = json.loads((ROOT / 'config/event-queue-origin-evidence.json').read_text())
    game = next(r for r in expected['contexts'] if r['address'] == '0x00602A60')
    if (m['game_entry'] != game or game['size'] != 2987 or not game['accepted']
            or game['role'] != 'GameApplication::RunAt00602A60'
            or game['body_facts']['returns'] != [dict(site='0x00603608', cleanup=16)]):
        raise ValueError('startup cannot infer game entry origin or ABI from a vendor symbol')
    if m['retained_controls'] != [dict(evidence_id='R125', manifest='initializer-startup-origin-evidence.json'),
                                  dict(evidence_id='R114', manifest='queue-lifetime-origin-evidence.json')]:
        raise ValueError('startup loses independent retained runtime and game evidence')
    reject = m['rejected_alternatives']
    if (len(reject) != 1 or reject[0]['address'] != '0x00649119' or reject[0]['size'] != 405
            or reject[0]['coff_symbol'] != '_parse_cmdline' or reject[0]['member_offset'] != 1646140
            or reject[0]['reason'] != 'complete-own-405-byte-alternative-differs-from-target'):
        raise ValueError('startup substitutes rejected wildcard parser or a source prefix')
    choices = m['definition_choices']
    if choices != [dict(symbol='__acmdln', selected_member_offset=1756238,
                        alternatives=[1655960,1689142,1756238],
                        basis='actual-complete-matching-WinMainCRTStartup-own-COMMON-definition'),
                   dict(symbol='__aenvptr', selected_member_offset=1756238,
                        alternatives=[1655960,1689142,1739076,1756238,1779372],
                        basis='actual-complete-matching-WinMainCRTStartup-own-whole-12-byte-BSS-section')]:
        raise ValueError('startup data loses the actual matching root definition choice')
    return rows


def check_common(row, definition):
    if (definition['symbol'] != row['symbol'] or definition['section'] != 0 or definition['storage'] != 2
            or definition['type'] or definition['offset'] != row['size']
            or (row['target_address'], row['size']) != COMMON.get(row['symbol'])):
        raise ValueError('startup COMMON loses its actual complete defining object')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('startup loses complete origin-only extent')
    if (origin['evidence_id'] != 'R126' or origin['origin'] != 'library' or origin['subsystem'] != 'VC71CRT'
            or origin['disposition'] != 'exclude' or origin['confidence'] != CONFIDENCE
            or function['owner'] != 'library' or function['module'] != 'VC71CRT'
            or function['status'] != 'excluded' or function['proposed_name'] != row['coff_symbol']):
        raise ValueError('startup accepted library ledger differs')


def check_historical_root(row, function, origin):
    if row['address'] not in ('0x0064232C', '0x00648FF5'):
        raise ValueError('startup historical reconciliation is outside its frozen pending roots')
    current = next(r for r in manifest()['functions'] if r['address'] == row['address'])
    identity = module('startup_historical_identity', 'origin_reconciliation.py')
    if 'archive_source' in row:
        archive = row['archive_source']
        old = dict(address=row['address'], size=row['size'], span_end=row['span_end'],
                   body_sha256=row['body_sha256'], coff_symbol=archive['symbol'],
                   source_sha256=archive['body_sha256'],
                   **{k: archive[k] for k in ('member_offset','member','member_sha256')},
                   relocation_bindings=archive['relocations'])
        identity.same_source(old, current)
        if row['body_facts'] != current['body_facts']:
            raise ValueError('historical entry complete control flow differs')
    else:
        identity.same_source(row, current)
    check_ledger(current, function, origin)


def check_historical_context(row, function, origin):
    if row['address'] != '0x0064232C':
        raise ValueError('startup context reconciliation is outside the PE entry')
    current = next(r for r in manifest()['functions'] if r['address'] == row['address'])
    for key in ('address','size','span_end','body_sha256','body_facts'):
        if row[key] != current[key]:
            raise ValueError('historical PE entry whole context differs: ' + key)
    witnesses = {w['site']: w for w in current['instruction_witnesses']}
    if any(witnesses.get(w['site']) != w for w in row['instruction_witnesses']):
        raise ValueError('historical PE entry instruction provenance differs')
    check_ledger(current, function, origin)


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
    for row in m['auxiliary_bodies']:
        key = row['address']
        if key in functions:
            raise ValueError('non-inventoried library control gains a candidate')
        actual_interiors = {k for k in functions if int(key, 16) < int(k, 16) < int(key, 16) + row['size']}
        expected_interiors = {r['address'] for r in m['interior_labels'] if r['parent'] == key}
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

    for choice in m['definition_choices']:
        actual_members = []
        for offset, (_, data) in members.items():
            try:
                defs = coff.parse_symbols(data,c.coff_name)[1]
            except ValueError:
                continue
            if any(d['symbol'] == choice['symbol'] and d['storage'] == 2
                   and (d['section'] > 0 or d['section'] == 0 and d['offset'] > 0) for d in defs):
                actual_members.append(offset)
        if actual_members != choice['alternatives'] or choice['selected_member_offset'] != rows['0x0064232C']['member_offset']:
            raise ValueError('startup data choice loses actual strong/COMMON source definitions')
    state_map, scope_map = {}, {}
    for row in m['state_data'] + m['scope_tables'] + m['range_markers'] + m['initializer_registrations']:
        raw, desc = old.whole_section(member(row), row['symbol'], c, coff)
        a = int(row['target_address'], 16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('whole defining data topology differs')
        if 'section_name' in row and security.source_section_name(member(row), row['symbol'], c, coff) != row['section_name']:
            raise ValueError('initializer loses its actual CRT subsection')
        for definition in desc['definitions']:
            state_map[definition['symbol']] = a + definition['offset']
        if row in m['state_data'] and row['writable'] != bool(int(desc['flags'], 16) & 0x80000000):
            raise ValueError('defining data loses actual source mutability')
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
        if row in m['state_data']:
            writable=bool(int(desc['flags'],16)&0x80000000)
            if writable and not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('initializer state loses whole writable target storage')
            if not writable:
                literal.check_scalar(raw,actual,row['size'],target_sections,a)
        if row in m['scope_tables']:
            literal.check_scalar(actual, actual, row['size'], target_sections, a)
            if struct.unpack_from('<I', raw)[0] != 0xffffffff:
                raise ValueError('runtime scope loses enclosing-level sentinel')
            scope_map[row['symbol']] = a
    for row in m['common_globals']:
        definitions = [d for d in coff.parse_symbols(member(row), c.coff_name)[1] if d['symbol'] == row['symbol']]
        if len(definitions) != 1 or definitions[0] != row['source_definition']:
            raise ValueError('actual initializer COMMON definition differs')
        check_common(row, definitions[0])
        a = int(row['target_address'], 16)
        if startup.zero_fill_region(target, a, row['size']) != row['zero_fill_region']:
            raise ValueError('COMMON runtime storage lacks loader provenance')
        state_map[row['symbol']] = a
    literal_map = {}
    for row in m['literal_controls']:
        source = literal.readonly_member_data(member(row), row['symbol'], row, c.coff_name)
        a = int(row['target_address'], 16)
        literal.check_scalar(source, c.pe_bytes_at(target, a, len(source)), len(source), target_sections, a)
        literal_map[(row['member_offset'], row['symbol'])] = a
    for row in m['state_data'] + m['initializer_registrations']:
        for b in row['relocations']:
            code_map={r['coff_symbol']:int(r['address'],16) for r in m['functions']+m['auxiliary_bodies']+m['anchors'] if r['decision']!='pending'}
            dest=state_map.get(b['symbol'],literal_map.get((row['member_offset'],b['symbol']),code_map.get(b['symbol'])))
            if b['type']!='DIR32' or dest!=int(b['target_address'],16):
                raise ValueError('initialized pointer loses whole defining provenance')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    scratch = ROOT / 'build/origin-environment-startup-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path = Path(temp) / 'VendorMember.obj'
        for layout_key,values,headers in [('sdk_layout',LAYOUT,LAYOUT_HEADERS)]:
            layout=m[layout_key];probe=ROOT/layout['probe'];profile=old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
            if layout['profile']!=profile or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256'] or set(layout['headers'])!=headers:
                raise ValueError('natural initializer control loses its exact source/profile/headers')
            for filename,digest in layout['headers'].items():
                if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                    raise ValueError('pinned initializer control header differs')
            subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
            data=path.read_bytes();definition=next(d for d in coff.parse_symbols(data,c.coff_name)[1] if d['symbol']==layout['symbol'])
            raw,names=coff.readonly_section(data,definition['section'],c.coff_name)
            if (definition['offset'] or names!=[dict(symbol=layout['symbol'],offset=0)]
                    or len(raw)!=layout['size'] or list(struct.unpack('<'+'I'*len(values),raw))!=values):
                raise ValueError('cold whole natural initializer/IO/SDK layout differs')
        for observed in m['callback_ranges']:
            raw=c.pe_bytes_at(target,int(observed['address'],16),observed['size'])
            if (hashlib.sha256(raw).hexdigest()!=observed['sha256']
                    or [f'0x{x:08X}' for x in struct.unpack('<'+'I'*(len(raw)//4),raw)]!=observed['entries']):
                raise ValueError('whole observed initializer/RTC range differs')
            if observed['address'] in ('0x00667940','0x00667948') and observed['entries']!=['0x00000000','0x00000000']:
                raise ValueError('RTC range has an unreviewed actual callback')
        for row in m['functions'] + m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']:
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
                if row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R125':
                    raise ValueError('anchor loses its independent full control-flow replay')
                for alias in row.get('source_aliases', []):
                    defs = coff.parse_symbols(member(row), c.coff_name)[1]
                    startup.check_alias_definition(next(d for d in defs if d['symbol'] == row['coff_symbol']), next(d for d in defs if d['symbol'] == alias))
                continue
            ins = list(decoder.disasm(actual[:row['code_size']], a))
            starts = {i.address for i in ins}
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('whole runtime instruction inventory differs')
            branches = [dict(site=f'0x{i.address:08X}', target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type==X86_OP_IMM]
            if branches != row['branches']:
                raise ValueError('whole runtime branch inventory differs')
            for i in ins:
                if i.group(CS_GRP_JUMP) and i.operands[0].type==X86_OP_IMM and i.operands[0].imm not in starts:
                    if not any(b['type'] == 'REL32' and b['target_kind'] == 'callee'
                               and b['offset'] == i.address-a+i.imm_offset
                               and int(b['target_address'], 16) == i.operands[0].imm for b in row['relocation_bindings']):
                        raise ValueError('runtime branch exits without complete typed callee')
            if [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type!=X86_OP_IMM]!=row.get('indirect_jumps',[]):
                raise ValueError('whole initializer indirect-jump inventory differs')
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
        parents = {**rows, **{r['address']: r for r in m['auxiliary_bodies']+m['diagnostic_contexts']}}
        for scope in m['scope_tables']:
            owner = parents[scope['parent']]
            defs = coff.parse_symbols(member(scope), c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == owner['coff_symbol'])
            for b in scope['relocations']:
                label = next(d for d in defs if d['symbol'] == b['symbol'])
                if label['section'] != primary['section'] or int(b['target_address'], 16) != int(owner['address'], 16) + label['offset'] - primary['offset']:
                    raise ValueError('runtime EH pointer loses actual full parent source label')
        for rejected in m['rejected_alternatives']:
            path.write_bytes(member(rejected))
            source, fields = c.object_function(path, rejected['coff_symbol'])
            actual = c.pe_bytes_at(target, int(rejected['address'],16), rejected['size'])
            mask = {i for f in fields for i in range(f['offset'],f['offset']+4)}
            if (len(source) != 405 or hashlib.sha256(source).hexdigest() != rejected['source_sha256']
                    or all(source[i] == actual[i] for i in range(len(source)) if i not in mask)):
                raise ValueError('rejected whole parser source loses its actual differing body')
        game = m['game_entry']; a = int(game['address'],16)
        actual = c.pe_bytes_at(target,a,game['size'])
        if (hashlib.sha256(actual).hexdigest() != game['body_sha256']
                or facts.body_facts(list(decoder.disasm(actual,a))) != game['body_facts']
                or origins[game['address']]['origin'] != 'authored'
                or origins[game['address']]['evidence_id'] != 'R113'
                or int(functions[game['address']]['size']) != game['size']):
            raise ValueError('independent complete authored game entry differs')
        pe = struct.unpack_from('<I', target, 0x3C)[0]
        if (struct.unpack_from('<H',target,pe+24)[0] != 0x10b
                or sum(struct.unpack_from('<I',target,pe+24+o)[0] for o in (16,28)) != 0x64232C):
            raise ValueError('startup is not the supplied target PE entry')
    for script in ('verify-initializer-startup-origins.py','verify-queue-lifetime-origins.py'):
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/' + script],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('retained independent complete graph replay failed: ' + result.stderr[-1500:])
    print('R126 origins OK: eleven complete library candidates / 2033 bytes / 100 fields; one whole auxiliary c_exit / 15 bytes / one field; nineteen independent whole anchors / 2675 bytes / 173 fields; complete defining environment/argv/exception/ctype sections and COMMON, 12-byte scope, natural 220-byte PE32/PE32+ layout; independent authored game entry and retained cold R125/R114 controls; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
