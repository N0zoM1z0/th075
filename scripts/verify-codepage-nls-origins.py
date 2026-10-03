#!/usr/bin/env python3
"""Replay the bounded R123 complete codepage/NLS graph and actual enclosing cleanup extents."""
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
ACCEPTED = {'0x006504F9': ('___initmbctable', 30), '0x006503A9': ('__setmbcp', 336), '0x00650209': ('__setmbcp_lk', 400), '0x0064FFE5': ('_setSBCS', 41), '0x0065000E': ('_setSBUpLow', 396), '0x0065019A': ('___updatetmbcinfo', 111), '0x0064DA08': ('___crtGetStringTypeA', 442), '0x0065275D': ('___crtLCMapStringA', 956), '0x006518B9': ('__resetstkoflw', 227), '0x00651D5F': ('___ansicp', 67), '0x00651DA2': ('___convertcp', 457), '0x00642619': ('_atol', 136), '0x00642DEB': ('___updatetlocinfo', 59), '0x0064980B': ('___isctype_mt', 119), '0x00642BD9': ('___updatetlocinfo_lk', 193)}
CONFIDENCE = 'complete-vendor-codepage-nls-code-data-layout-api-eh-provenance'
LABEL_CONFIDENCE = 'complete-interior-label-of-reviewed-vendor-parent'
LAYOUT = [20, 0, 4, 6, 12, 28, 0, 4, 12, 16, 20, 36, 4, 48, 4, 16, 240, 544, 16, 12, 28, 285, 84, 4, 12, 40, 72, 1, 256, 512, 1024, 1, 8, 4100, 120, 4096, 4, 256, 1, 1, 2, 2, 4]
COMMON = {'___mbctype_initialized': ('0x0068FBB4', 4), '___mbcodepage': ('0x0068E904', 4), '___ptmbcinfo': ('0x0068E7F8', 4), '___ismbcodepage': ('0x0068E7FC', 4), '___mblcid': ('0x0068E7F4', 4), '___mbulinfo': ('0x0068E910', 12), '__mbctype': ('0x0068E800', 257), '__mbcasemap': ('0x0068E920', 256)}
LABELS = [('0x006504F0', '0x006503A9', 327, 327), ('0x00650200', '0x0065019A', 102, 99), ('0x00642E1D', '0x00642DEB', 50, 50)]
RECONCILED = {'0x006503A9': (327,336), '0x0065019A': (99,111), '0x00642DEB': (50,59)}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/codepage-nls-origin-evidence.json').read_text())
    reconciliation = module('codepage_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R123' or m['target_sha256'] != reconciliation.TARGET:
        raise ValueError('codepage/NLS target identity differs')
    return m


def verify_plan(m):
    rows={r['address']:r for r in m['functions']}
    if len(m['functions'])!=15 or set(rows)!=set(ACCEPTED):
        raise ValueError('bounded complete codepage/NLS graph differs')
    for key,(symbol,size) in ACCEPTED.items():
        row=rows[key]
        if (row['coff_symbol']!=symbol or row['size']!=size or row['decision']!='library'
                or row['extent_basis']!='function-auxiliary-record'):
            raise ValueError('codepage function loses complete own auxiliary extent')
        if row['ledger_size']!=RECONCILED.get(key,(size,size))[0]:
            raise ValueError('reconciled extent loses its historical provisional boundary')
    if m['auxiliary_bodies'] or m['diagnostic_contexts'] or m['pending_labels']:
        raise ValueError('closed codepage graph gains an unreviewed context')
    graph={**rows,**{r['address']:r for r in m['anchors']}}
    if len(m['anchors'])!=14 or sum(r['size'] for r in m['anchors'])!=1142:
        raise ValueError('independent complete codepage anchors differ')
    for row in rows.values():
        for b in row['relocation_bindings']:
            if b['target_kind']=='callee':
                dest=graph.get(b['target_address'])
                if (not dest or b['symbol'] not in [dest['coff_symbol']]+dest.get('source_aliases',[])
                        or dest['decision'] not in ('library','anchor')):
                    raise ValueError('closed codepage graph retains an unreviewed callee')
            elif b['target_kind'] not in ('state','import','scope-table','literal'):
                raise ValueError('closed codepage graph loses defining provenance')
    if [(r['address'],r['parent'],r['source_offset'],r['eh_source_offset']) for r in m['interior_labels']]!=LABELS:
        raise ValueError('codepage cleanup loses actual entry or earlier EH head')
    if any(r['size']!=9 or r['decision']!='library' or r['extent_basis']!='interior-label-in-complete-vendor-primary' for r in m['interior_labels']):
        raise ValueError('interior cleanup becomes a fabricated standalone function')
    if (len(m['state_data'])!=12 or sum(r['size'] for r in m['state_data'])!=2296
            or len(m['scope_tables'])!=6 or sum(r['size'] for r in m['scope_tables'])!=96
            or len(m['literal_controls'])!=44 or sum(r['data_size'] for r in m['literal_controls'])!=267):
        raise ValueError('complete codepage defining data/scopes/literals differ')
    critical={(r['symbol'],r['target_address'],r['size']) for r in m['state_data']}
    if not {('___rgctypeflag','0x00670BE0',248),('___lc_handle','0x0068E6B4',32),
            ('__umaskval','0x0068E2E4',72),('__clocalestr','0x0066FF20',403),
            ('___newctype','0x006626B0',1284)} <= critical:
        raise ValueError('full codepage and locale carriers become convenient fields')
    if len(m['common_globals'])!=8 or {r['symbol']:(r['target_address'],r['size']) for r in m['common_globals']}!=COMMON:
        raise ValueError('codepage arrays lose actual complete COMMON storage')
    if m['sdk_layout']['size']!=172 or m['sdk_layout']['values']!=LAYOUT:
        raise ValueError('whole natural codepage/SDK layout differs')
    if m['retained_controls']!=[dict(evidence_id='R122',manifest='locale-thread-origin-evidence.json')]:
        raise ValueError('codepage graph loses cold independent locale controls')
    old=json.loads((ROOT/'config/locale-thread-origin-evidence.json').read_text())
    identity=module('codepage_source_identity','origin_reconciliation.py')
    for row in old['functions']+old['diagnostic_contexts']:
        if row['address'] in rows:identity.same_source(row,rows[row['address']])
    return rows


def check_ledger(row,function,origin):
    if (int(function['size'])!=row['size'] or function['span_end']!=row['span_end']
            or function['source_file'] or function['match_percent']!='0.00'):
        raise ValueError('codepage loses whole origin-only extent')
    if (origin['evidence_id']!='R123' or origin['origin']!='library' or origin['subsystem']!='VC71CRT'
            or origin['disposition']!='exclude' or origin['confidence']!=CONFIDENCE
            or function['owner']!='library' or function['module']!='VC71CRT'
            or function['status']!='excluded' or function['proposed_name']!=row['coff_symbol']):
        raise ValueError('codepage library ledger differs')


def check_label(row,function,origin,functions,origins,rows):
    parent=rows.get(row['parent'])
    if not parent or parent['address'] not in ACCEPTED:
        raise ValueError('cleanup loses its complete accepted primary')
    check_ledger(parent,functions[parent['address']],origins[parent['address']])
    if (origin['evidence_id']!='R123' or origin['origin']!='library' or origin['disposition']!='exclude'
            or origin['confidence']!=LABEL_CONFIDENCE or origin['subsystem']!='VC71CRT'
            or function['owner']!='library' or function['module']!='VC71CRT' or function['status']!='excluded'
            or function['proposed_name'] or int(function['size'])!=9
            or int(function['span_end'],16)!=int(row['address'],16)+8
            or function['source_file'] or function['match_percent']!='0.00'):
        raise ValueError('codepage label gains unsupported standalone/source credit')


def check_common(row,definition):
    if (definition['symbol']!=row['symbol'] or definition['section']!=0 or definition['storage']!=2
            or definition['type'] or definition['offset']!=row['size']
            or (row['target_address'],row['size'])!=COMMON.get(row['symbol'])):
        raise ValueError('codepage COMMON loses actual full defining array/object')


def check_historical_root(row,function,origin):
    if row['address'] not in ('0x006504F9','0x006503A9','0x00650209'):
        raise ValueError('historical codepage guard is outside the reviewed graph')
    current=next(r for r in manifest()['functions'] if r['address']==row['address'])
    module('codepage_historical_identity','origin_reconciliation.py').same_source(row,current)
    check_ledger(current,function,origin)


def check_historical_label(row,function,origin,functions,origins):
    m=manifest();matches=[r for r in m['interior_labels'] if r['address']==row['address']]
    if len(matches)!=1 or row['address']!='0x006504F0' or any(row[k]!=matches[0][k] for k in ('address','size','parent','source_offset','source_symbol','eh_source_offset','eh_source_symbol')):
        raise ValueError('historical codepage label loses its actual source identity')
    rows=verify_plan(m)
    for current in rows.values():check_ledger(current,functions[current['address']],origins[current['address']])
    check_label(matches[0],function,origin,functions,origins,rows)


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
    for row in m['state_data'] + m['scope_tables']:
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
                raise ValueError('locale state loses whole writable target storage')
            if not writable:
                literal.check_scalar(raw,actual,row['size'],target_sections,a)
        if row in m['scope_tables']:
            literal.check_scalar(actual, actual, row['size'], target_sections, a)
            if struct.unpack_from('<I', raw)[0] != 0xffffffff:
                raise ValueError('runtime scope loses enclosing-level sentinel')
            scope_map[row['symbol']] = a
    for row in m['common_globals']:
        defs = [d for d in coff.parse_symbols(member(row), c.coff_name)[1] if d['symbol'] == row['symbol']]
        if defs != [row['source_definition']]:
            raise ValueError('actual COMMON definition differs')
        check_common(row,defs[0])
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
    for row in m['state_data']:
        for b in row['relocations']:
            dest=state_map.get(b['symbol'],literal_map.get((row['member_offset'],b['symbol'])))
            if b['type']!='DIR32' or dest!=int(b['target_address'],16):
                raise ValueError('initialized locale pointer loses whole defining provenance')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    scratch = ROOT / 'build/origin-codepage-nls-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path = Path(temp) / 'VendorMember.obj'
        layout=m['sdk_layout'];probe=ROOT/layout['probe'];profile=old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if layout['profile']!=profile or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256']:
            raise ValueError('natural codepage layout probe differs')
        if set(layout['headers'])!={'crt/src/mtdll.h', 'PlatformSDK/Include/WinNT.h', 'crt/src/locale.h', 'crt/src/cruntime.h', 'PlatformSDK/Include/WinBase.h', 'PlatformSDK/Include/WinNls.h', 'crt/src/mbctype.c'}:
            raise ValueError('pinned complete codepage layout headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned CRT header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data=path.read_bytes();definition=next(d for d in coff.parse_symbols(data,c.coff_name)[1] if d['symbol']==layout['symbol'])
        raw,names=coff.readonly_section(data,definition['section'],c.coff_name)
        if definition['offset'] or names!=[dict(symbol=layout['symbol'],offset=0)] or len(raw)!=172 or list(struct.unpack('<43I',raw))!=LAYOUT:
            raise ValueError('cold complete natural codepage/SDK layout differs')
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
                if row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R122':
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
        parents = {**rows, **{r['address']: r for r in m['auxiliary_bodies']+m['diagnostic_contexts']}}
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
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-locale-thread-origins.py'], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('retained independent runtime replay failed: ' + result.stderr[-1500:])
    print('R123 origins OK: fifteen complete library bodies / 3970 bytes / 209 typed fields; three interior labels / 27 overlapping bytes; fourteen independent complete anchors; full codepage/NLS/locale/SDK/state/API/EH graph, natural cold layout / 172 bytes and retained R122 controls; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
