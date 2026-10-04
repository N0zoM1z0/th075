#!/usr/bin/env python3
"""Replay the bounded R125 complete initializer, IO, exception and signal dependency graph."""
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
ACCEPTED = {'0x0064411D': ('__cinit', 106), '0x00648052': ('___sse2_available_init', 206), '0x0064801D': ('_has_osfxsr_set', 53), '0x0064654C': ('?__CxxUnhandledExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z', 78), '0x00649693': ('__RTC_Initialize', 68), '0x00649449': ('__ioinit', 510), '0x00646478': ('?terminate@@YAXXZ', 53), '0x0064FF58': ('?_ValidateExecute@@YAHP6GHXZ@Z', 24), '0x00650517': ('_abort', 24), '0x0065364F': ('_raise', 377), '0x0065346E': ('_siglookup', 46)}
AUXILIARY = {'0x0064F08F': ('___initstdio', 169), '0x0064659A': ('?__CxxSetUnhandledExceptionFilter@@YAHXZ', 19), '0x00640579': ('__fpclear', 1), '0x006496D7': ('__RTC_Terminate', 68)}
COMMON = {'___sse2_available': ('0x0068FBA4', 4), '___use_sse2_mathfcns': ('0x0068FBA0', 4), '___pioinfo': ('0x0068FAA0', 256), '__nhandle': ('0x0068FA80', 4), '__nstream': ('0x0068FA40', 4), '___piob': ('0x0068EA20', 4), '__bufin': ('0x0068EA40', 4096)}
CONFIDENCE = 'complete-vendor-initializer-io-exception-signal-code-data-layout-provenance'
LABEL_CONFIDENCE = 'interior-cleanup-label-in-complete-vendor-raise-primary'
LAYOUT = [36, 0, 4, 5, 8, 12, 24, 5, 32, 64, 2048, 1152, 256, 32, 0, 4, 8, 12, 16, 20, 24, 28, 20, 640, 512, 4096, 1, 8, 64, 128, 1, 2, 256, 68, 50, 52, 4294967286, 4294967285, 4294967284, 2, 3, 140, 108, 84, 88, 92, 12, 0, 4, 8, 2, 4, 8, 11, 15, 21, 22, 140, 0, 80, 0, 16, 20, 15, 8, 0, 4, 4294967295, 0, 1, 4, 4, 4]
LAYOUT_HEADERS = {'crt/src/internal.h', 'crt/src/cruntime.h', 'crt/src/mtdll.h', 'crt/src/file2.h', 'crt/src/msdos.h', 'crt/src/signal.h', 'PlatformSDK/Include/WinNT.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/excpt.h', 'crt/src/stdio.h', 'crt/src/float.h'}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/initializer-startup-origin-evidence.json').read_text())
    reconciliation = module('codepage_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R125' or m['target_sha256'] != reconciliation.TARGET:
        raise ValueError('initializer target identity differs')
    return m


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 11 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete initializer cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != size or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record' or row['indirect_jumps']):
            raise ValueError('initializer loses its whole own auxiliary extent/control flow')
    if (len(m['auxiliary_bodies']) != 4
            or {r['address']: (r['coff_symbol'], r['size']) for r in m['auxiliary_bodies']} != AUXILIARY
            or any(r['decision'] != 'library-control' or r['ledger_size'] is not None
                   or r['code_size'] != r['size'] for r in m['auxiliary_bodies'])):
        raise ValueError('whole auxiliary initializer controls become fabricated candidates')
    if m['diagnostic_contexts'] or m['pending_labels']:
        raise ValueError('initializer graph acquires unresolved diagnostic dependencies')
    if len(m['anchors']) != 17 or sum(r['size'] for r in m['anchors']) != 1286:
        raise ValueError('independent complete initializer anchors differ')
    graph = {**rows, **{r['address']: r for r in m['auxiliary_bodies'] + m['anchors']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                dest = graph.get(b['target_address'])
                if not dest or dest['coff_symbol'] != b['symbol'] or dest['decision'] not in ('library', 'library-control', 'anchor'):
                    raise ValueError('initializer retains an unreviewed actual code/callback definition')
            elif b['target_kind'] not in ('state', 'import', 'scope-table', 'literal'):
                raise ValueError('initializer retains an unresolved data/API/EH binding')
    if (len(m['interior_labels']) != 1 or m['interior_labels'][0] !=
            dict(address='0x0065378A', size=13, parent='0x0065364F', source_offset=315,
                 source_symbol='$L20094', eh_source_offset=307, eh_source_symbol='$L20092',
                 decision='library', extent_basis='interior-label-in-complete-vendor-primary')):
        raise ValueError('raise cleanup loses its earlier EH head and actual shared entry')
    if (len(m['state_data']) != 6 or sum(r['size'] for r in m['state_data']) != 824
            or len(m['scope_tables']) != 5 or sum(r['size'] for r in m['scope_tables']) != 60
            or len(m['range_markers']) != 8 or sum(r['size'] for r in m['range_markers']) != 32
            or len(m['initializer_registrations']) != 6 or sum(r['size'] for r in m['initializer_registrations']) != 24
            or len(m['literal_controls']) != 1 or m['literal_controls'][0]['data_size'] != 13):
        raise ValueError('whole initializer state/scopes/registrations/literals differ')
    expected_state = {('___security_cookie', '0x0066FE30', 4), ('_pOldExceptFilter', '0x0068E340', 4),
                      ('__iob', '0x00670928', 640), ('__fltused', '0x0066FE34', 20),
                      ('_ctrlc_action', '0x0068E780', 20), ('__XcptActTab', '0x00670748', 136)}
    if {(r['symbol'], r['target_address'], r['size']) for r in m['state_data']} != expected_state:
        raise ValueError('initializer data cannot become convenient array/carrier prefixes')
    if len(m['common_globals']) != 7 or {r['symbol']: (r['target_address'], r['size']) for r in m['common_globals']} != COMMON:
        raise ValueError('initializer COMMON loses whole defining arrays and objects')
    for r in m['common_globals']:
        check_common(r, r['source_definition'])
    if m['sdk_layout']['size'] != 292 or m['sdk_layout']['values'] != LAYOUT:
        raise ValueError('natural IO/thread/exception/SDK layout and constants differ')
    if m['static_probe']['profile'] != module('initializer_profile', 'verify-runtime-error-origins.py').PROFILE:
        raise ValueError('static initializer fixture loses its explicit cold profile')
    if m['retained_controls'] != [dict(evidence_id='R124', manifest='floating-point-origin-evidence.json'),
                                  dict(evidence_id='R024', manifest='compiler-static-evidence.csv')]:
        raise ValueError('initializer loses independent cold runtime/compiler controls')
    check_callback_graph(m, graph)
    previous = json.loads((ROOT / 'config/floating-point-origin-evidence.json').read_text())
    identity = module('initializer_identity', 'origin_reconciliation.py')
    for row in previous['functions'] + previous['auxiliary_bodies']:
        if row['address'] in graph:
            identity.same_source(row, graph[row['address']])
    return rows


def check_callback_graph(m, graph):
    ranges = {r['address']: r for r in m['callback_ranges']}
    if len(m['callback_ranges']) != 4 or {k: r['size'] for k, r in ranges.items()} != {
            '0x0066C038': 28, '0x0066C000': 56, '0x00667948': 8, '0x00667940': 8}:
        raise ValueError('complete actual initializer callback ranges differ')
    prior = json.loads((ROOT / 'config/floating-point-origin-evidence.json').read_text())
    for r in prior['callback_ranges']:
        current = ranges[r['address']]
        if any(current[k] != r[k] for k in ('address', 'size', 'sha256', 'entries')):
            raise ValueError('initializer changes observed callback range provenance')
    if any(ranges[k]['entries'] != ['0x00000000', '0x00000000'] for k in ('0x00667940', '0x00667948')):
        raise ValueError('RTC range has an unreviewed actual callback')
    for address in ranges['0x0066C038']['entries'][1:-1]:
        if address not in graph or graph[address]['decision'] not in ('library', 'library-control', 'anchor'):
            raise ValueError('cinit inherits origin before every actual XI callback closes')
    registers = {r['target_address']: r for r in m['initializer_registrations']}
    if set(registers) != {'0x0066C03C', '0x0066C040', '0x0066C044', '0x0066C048', '0x0066C04C', '0x0066C004'}:
        raise ValueError('initializer registration loses a whole source defining cell')
    entries = {int(r['address'], 16) + n * 4: address for r in ranges.values() for n, address in enumerate(r['entries'])}
    for row in registers.values():
        if len(row['relocations']) != 1:
            raise ValueError('initializer cell has incomplete typed callback provenance')
        b = row['relocations'][0]; dest = graph.get(b['target_address'])
        if (b['type'] != 'DIR32' or b['offset'] or b['addend'] or not dest
                or b['symbol'] != dest['coff_symbol']
                or entries.get(int(row['target_address'], 16)) != b['target_address']):
            raise ValueError('initializer source cell does not bind its real complete callback')
    evidence = module('initializer_static_evidence', 'verify-vendor-record-origins.py').rows('compiler-static-evidence.csv')
    expected = [r for r in evidence if r['address'] in ranges['0x0066C000']['entries'][2:-1]]
    if len(expected) != 11 or m['compiler_callbacks'] != expected:
        raise ValueError('XC callbacks lose independent complete compiler-emission provenance')
    if (ranges['0x0066C000']['entries'][1] not in graph
            or len(ranges['0x0066C000']['entries']) != len(expected) + 3):
        raise ValueError('XC callback graph retains an unreviewed real entry')


def check_common(row, definition):
    if (definition['symbol'] != row['symbol'] or definition['section'] != 0 or definition['storage'] != 2
            or definition['type'] or definition['offset'] != row['size']
            or (row['target_address'], row['size']) != COMMON.get(row['symbol'])):
        raise ValueError('initializer COMMON loses its actual complete defining object')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('initializer loses complete origin-only extent')
    if (origin['evidence_id'] != 'R125' or origin['origin'] != 'library' or origin['subsystem'] != 'VC71CRT'
            or origin['disposition'] != 'exclude' or origin['confidence'] != CONFIDENCE
            or function['owner'] != 'library' or function['module'] != 'VC71CRT'
            or function['status'] != 'excluded' or function['proposed_name'] != row['coff_symbol']):
        raise ValueError('initializer accepted library ledger differs')


def check_label(row, function, origin, functions, origins, rows):
    parent = rows.get(row['parent'])
    if not parent or parent['address'] != '0x0065364F':
        raise ValueError('raise cleanup loses its complete accepted primary')
    check_ledger(parent, functions[parent['address']], origins[parent['address']])
    if (origin['evidence_id'] != 'R125' or origin['origin'] != 'library' or origin['disposition'] != 'exclude'
            or origin['confidence'] != LABEL_CONFIDENCE or origin['subsystem'] != 'VC71CRT'
            or function['owner'] != 'library' or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != 13
            or int(function['span_end'], 16) != int(row['address'], 16) + 12
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('raise cleanup gains unsupported standalone/source credit')


def check_historical_root(row, function, origin):
    if row['address'] != '0x0064411D':
        raise ValueError('initializer historical reconciliation is outside cinit')
    current = next(r for r in manifest()['functions'] if r['address'] == row['address'])
    module('initializer_historical_identity', 'origin_reconciliation.py').same_source(row, current)
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
    scratch = ROOT / 'build/origin-initializer-startup-verification'
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
                if row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R124':
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
        for fragment in m['interior_labels']:
            parent = parents[fragment['parent']]
            defs = coff.parse_symbols(member(parent), c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == parent['coff_symbol'])
            for symbol, offset in [(fragment['source_symbol'], fragment['source_offset']),
                                   (fragment['eh_source_symbol'], fragment['eh_source_offset'])]:
                entry = next(d for d in defs if d['symbol'] == symbol)
                if entry['section'] != primary['section'] or entry['offset'] - primary['offset'] != offset:
                    raise ValueError('raise cleanup loses its complete source parent labels')
            if int(fragment['address'], 16) != int(parent['address'], 16) + fragment['source_offset']:
                raise ValueError('raise cleanup has a fabricated entry')
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
        static = m['static_probe']; probe = ROOT / static['probe']
        if (hashlib.sha256(probe.read_bytes()).hexdigest() != static['probe_sha256']
                or hashlib.sha256((ROOT / static['source_header']).read_bytes()).hexdigest() != static['source_header_sha256']):
            raise ValueError('cold static fixture loses its exact source/header identity')
        subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(probe), str(path), *static['profile']],
                       cwd=ROOT, capture_output=True, text=True, check=True)
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-static-origins.py',
                                 '--probe', str(path)], cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('independent whole static callback replay failed: ' + result.stderr[-1500:])
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-floating-point-origins.py'], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('retained independent runtime replay failed: ' + result.stderr[-1500:])
    print('R125 origins OK: eleven complete library candidates / 1545 bytes / 77 fields; one existing shared cleanup label / 13 overlapping bytes; four whole auxiliary controls / 257 bytes / 21 fields; full XI/XC/RTC and FP callback provenance, whole IO/signal state and natural 292-byte layout, cold R024 static emissions and retained R124 graph; PE entry remains pending; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
