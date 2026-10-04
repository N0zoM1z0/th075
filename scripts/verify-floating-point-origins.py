#!/usr/bin/env python3
"""Replay the bounded R124 complete FP conversion/control graph and complete embedded parser table."""
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
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_EAX

ROOT = Path(__file__).resolve().parents[1]
ACCEPTED = {'0x006405C2': ('__fpmath', 30), '0x0064057A': ('__cfltcvt_init', 56), '0x0064520F': ('__ms_p5_mp_test_fdiv', 41), '0x006451BD': ('__setdefaultprecision', 18), '0x0064FBE8': ('__controlfp', 22), '0x0064516C': ('__cfltcvt', 81), '0x00644E5F': ('__fassign', 62), '0x00645070': ('__cftof', 98), '0x006450D2': ('__cftog', 154), '0x00644F68': ('__cftoe', 108), '0x0064F7B3': ('__atodbl', 61), '0x0064F82E': ('__atoflt', 61), '0x0064F3E5': ('_tolower', 34), '0x00642800': ('_isdigit', 58), '0x0064F31D': ('___tolower_mt', 200), '0x0064F99C': ('__fltout2', 108), '0x00644FD4': ('__cftof2', 156), '0x00644EBA': ('__cftoe2', 174), '0x00652CD1': ('___strgtold12', 1076), '0x0064F70B': ('__ld12tod', 22), '0x0064F721': ('__ld12tof', 22), '0x00653151': ('_$I10_OUTPUT', 654), '0x00652BF3': ('___mtold12', 222), '0x0065418C': ('___multtenpow12', 134), '0x00644E9D': ('__shift', 29), '0x00653F5A': ('___ld12mul', 562), '0x0064FA08': ('__fptrap', 9)}
AUXILIARY = {'0x00644DFA': ('__cropzeros', 75), '0x00644DBE': ('__forcdecpt', 60), '0x00644E45': ('__positive', 26), '0x00640579': ('__fpclear', 1), '0x006496D7': ('__RTC_Terminate', 68)}
PENDING = {'0x0064411D': 'crt-cinit-initializer-callback-dependencies-unresolved'}
CONFIDENCE = 'complete-vendor-fp-conversion-control-code-data-layout-api-eh-provenance'
LAYOUT = [8, 8, 8, 24, 4, 4, 4, 4, 4, 4, 16, 0, 4, 8, 12, 524319, 1, 2, 4, 8, 16, 524288, 768, 0, 256, 512, 768, 196608, 0, 65536, 131072, 262144, 262144, 0, 589855, 4]
LOCALE_LAYOUT = [84, 4, 12, 24, 40, 72, 36, 2, 4, 4, 0, 4, 4]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/floating-point-origin-evidence.json').read_text())
    reconciliation = module('codepage_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R124' or m['target_sha256'] != reconciliation.TARGET:
        raise ValueError('floating-point target identity differs')
    return m


def verify_plan(m):
    rows={r['address']:r for r in m['functions']}
    if len(m['functions'])!=28 or set(rows)!=set(ACCEPTED)|set(PENDING):
        raise ValueError('bounded complete FP cohort differs')
    for key,(symbol,size) in ACCEPTED.items():
        row=rows[key]
        if (row['coff_symbol']!=symbol or row['size']!=size or row['decision']!='library'
                or row['extent_basis']!='function-auxiliary-record'):
            raise ValueError('FP function loses its complete own source extent')
        if row['ledger_size']!=(1028 if key=='0x00652CD1' else size):
            raise ValueError('parser loses its original provisional boundary')
    pending=rows['0x0064411D']
    if pending['decision']!='pending' or pending['size']!=106 or pending['uncertainty']!=PENDING['0x0064411D']:
        raise ValueError('cinit inherits FP ownership with unresolved initializer callbacks')
    if (len(m['auxiliary_bodies'])!=5 or
            {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}!=AUXILIARY
            or any(r['decision']!='library-control' or r['ledger_size'] is not None for r in m['auxiliary_bodies'])):
        raise ValueError('whole non-inventoried FP controls become fabricated candidates')
    if m['diagnostic_contexts'] or m['interior_labels'] or m['pending_labels'] or m['common_globals']:
        raise ValueError('FP cohort gains fabricated contexts/labels/COMMON')
    graph={**rows,**{r['address']:r for r in m['auxiliary_bodies']+m['anchors']}}
    if len(m['anchors'])!=24 or sum(r['size'] for r in m['anchors'])!=3732:
        raise ValueError('independent complete FP anchors differ')
    for row in [rows[k] for k in ACCEPTED]+m['auxiliary_bodies']+[graph['0x0064FBB6']]:
        if row['code_size']!=(1028 if row['address']=='0x00652CD1' else row['size']):
            raise ValueError('FP code or parser table is hidden from the full extent')
        for b in row['relocation_bindings']:
            if b['target_kind']=='callee':
                dest=graph.get(b['target_address'])
                if not dest or dest['coff_symbol']!=b['symbol'] or dest['decision'] not in ('library','library-control','anchor'):
                    raise ValueError('FP graph retains an unreviewed actual callee/callback')
            elif b['target_kind']=='local':
                if (row['address']!='0x00652CD1' or b['type']!='DIR32' or b['local_symbol_offset'] is None
                        or int(b['target_address'],16)!=int(row['address'],16)+b['local_symbol_offset']):
                    raise ValueError('parser table loses its actual same-source local labels')
            elif b['target_kind'] not in ('state','import','scope-table','literal'):
                raise ValueError('FP graph retains an unresolved code/data/API binding')
    parser=rows['0x00652CD1']
    tables=parser.get('embedded_tables',[])
    if (len(tables)!=1 or tables[0]['offset']!=1028 or tables[0]['size']!=48 or len(tables[0]['entries'])!=12
            or parser['indirect_jumps']!=[dict(site='0x00652D34',operand='dword ptr [eax*4 + 0x6530d5]')]):
        raise ValueError('complete guarded parser dispatch loses its twelve-entry table')
    if (len(m['state_data'])!=12 or sum(r['size'] for r in m['state_data'])!=2744
            or len(m['scope_tables'])!=1 or m['scope_tables'][0]['size']!=12
            or len(m['literal_controls'])!=50 or sum(r['data_size'] for r in m['literal_controls'])!=334
            or len(m['range_markers'])!=6 or len(m['callback_ranges'])!=3):
        raise ValueError('complete FP state/scopes/literals/initializer observations differ')
    if not {('__cfltcvt_tab','0x00670120',24),('__fltused','0x0066FE34',20),
            ('__pow10pos','0x00670EB0',700),('_DoubleFormat','0x00670BB0',48),
            ('___fastflag','0x0068E2C0',8),('___mb_cur_max','0x00670910',12)} <= {
                (r['symbol'],r['target_address'],r['size']) for r in m['state_data']}:
        raise ValueError('FP carriers cannot become convenient pointer/table prefixes')
    if (m['sdk_layout']['size']!=144 or m['sdk_layout']['values']!=LAYOUT
            or m['locale_layout']['size']!=52 or m['locale_layout']['values']!=LOCALE_LAYOUT):
        raise ValueError('natural FP/locale/API layouts and masks differ')
    if m['dynamic_api']!=dict(parent='0x0064520F',call_site='0x00645230',register='eax',module_literal='KERNEL32',export_literal='IsProcessorFeaturePresent',feature=0,stack_bytes=4,fallback='0x006451CF'):
        raise ValueError('division-test dispatch loses its actual API/ABI/fallback provenance')
    if m['retained_controls']!=[dict(evidence_id='R123',manifest='codepage-nls-origin-evidence.json')]:
        raise ValueError('FP graph loses cold independent runtime controls')
    old=json.loads((ROOT/'config/startup-registration-origin-evidence.json').read_text())
    identity=module('fp_source_identity','origin_reconciliation.py')
    for row in old['functions']+old['diagnostic_contexts']:
        dest=graph.get(row['address'])
        if dest and row['address'] not in ('0x00642B09',):identity.same_source(row,dest)
    return rows


def check_ledger(row,function,origin):
    if row['address']=='0x0064411D' and origin.get('evidence_id')=='R125':
        module('initializer_cinit_reconciliation','verify-initializer-startup-origins.py').check_historical_root(
            row,function,origin)
        return
    if (int(function['size'])!=row['size'] or function['span_end']!=row['span_end']
            or function['source_file'] or function['match_percent']!='0.00'):
        raise ValueError('FP loses complete origin-only extent')
    if row['address'] in ACCEPTED:
        if (origin['evidence_id']!='R124' or origin['origin']!='library' or origin['subsystem']!='VC71CRT'
                or origin['disposition']!='exclude' or origin['confidence']!=CONFIDENCE
                or function['owner']!='library' or function['module']!='VC71CRT'
                or function['status']!='excluded' or function['proposed_name']!=row['coff_symbol']):
            raise ValueError('FP accepted library ledger differs')
    elif (origin['evidence_id']!='R124' or origin['origin']!='unknown' or origin['subsystem']
            or origin['disposition']!='review' or origin['confidence']!=PENDING[row['address']]
            or function['owner'] or function['module'] or function['status']!='unclassified'):
        raise ValueError('unclosed initializer parent gains unsupported ownership')


def check_historical_root(row,function,origin):
    if row['address']!='0x0064411D':
        raise ValueError('FP historical reconciliation is outside its pending startup parent')
    current=next(r for r in manifest()['functions'] if r['address']==row['address'])
    module('fp_historical_identity','origin_reconciliation.py').same_source(row,current)
    check_ledger(current,function,origin)


def check_parser_table(row,actual,ins):
    a=int(row['address'],16);tables=row.get('embedded_tables',[])
    if row['address']!='0x00652CD1':
        if tables:raise ValueError('unreviewed embedded FP table')
        return
    t=tables[0];starts={i.address for i in ins}
    entries=[f'0x{x:08X}' for x in struct.unpack('<12I',actual[1028:1076])]
    fields=[b for b in row['relocation_bindings'] if b['offset']>=1028]
    if (entries!=t['entries'] or [b['offset'] for b in fields]!=list(range(1028,1076,4))
            or any(b['type']!='DIR32' or b['target_kind']!='local' or int(b['target_address'],16) not in starts
                   or b['target_address']!=entries[n] for n,b in enumerate(fields))):
        raise ValueError('full parser table fields do not bind actual code instruction starts')
    jump=next(i for i in ins if i.address==0x652D34)
    if (jump.operands[0].type!=X86_OP_MEM or jump.operands[0].mem.base
            or jump.operands[0].mem.index!=X86_REG_EAX or jump.operands[0].mem.scale!=4
            or jump.operands[0].mem.disp!=a+1028):
        raise ValueError('parser dispatch loses actual local table addressing')
    if not any(b['offset']==jump.address-a+jump.disp_offset and b['target_kind']=='local'
               and b['local_symbol_offset']==1028 for b in row['relocation_bindings']):
        raise ValueError('parser dispatch has no typed whole-table reference')
    guard=[(i.address,i.mnemonic,i.op_str) for i in ins if i.address in (0x652D2B,0x652D2E)]
    if guard!=[(0x652D2B,'cmp','eax, 0xb'),(0x652D2E,'ja','0x652fa7')]:
        raise ValueError('parser dispatch loses its actual unsigned twelve-entry guard')


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
    for row in m['state_data'] + m['scope_tables'] + m['range_markers']:
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
    literal_map = {}
    for row in m['literal_controls']:
        source = literal.readonly_member_data(member(row), row['symbol'], row, c.coff_name)
        a = int(row['target_address'], 16)
        literal.check_scalar(source, c.pe_bytes_at(target, a, len(source)), len(source), target_sections, a)
        literal_map[(row['member_offset'], row['symbol'])] = a
    for row in m['state_data']:
        for b in row['relocations']:
            code_map={r['coff_symbol']:int(r['address'],16) for r in m['functions']+m['auxiliary_bodies']+m['anchors'] if r['decision']!='pending'}
            dest=state_map.get(b['symbol'],literal_map.get((row['member_offset'],b['symbol']),code_map.get(b['symbol'])))
            if b['type']!='DIR32' or dest!=int(b['target_address'],16):
                raise ValueError('initialized locale pointer loses whole defining provenance')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    scratch = ROOT / 'build/origin-floating-point-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path = Path(temp) / 'VendorMember.obj'
        for layout_key,values,headers in [('sdk_layout',LAYOUT,{'crt/src/float.h','crt/src/fltintrn.h','crt/src/cruntime.h'}),
                ('locale_layout',LOCALE_LAYOUT,{'crt/src/mtdll.h','crt/src/locale.h','crt/src/cruntime.h','PlatformSDK/Include/WinNT.h','PlatformSDK/Include/WinBase.h'})]:
            layout=m[layout_key];probe=ROOT/layout['probe'];profile=old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
            if layout['profile']!=profile or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256'] or set(layout['headers'])!=headers:
                raise ValueError('natural FP control loses its exact source/profile/headers')
            for filename,digest in layout['headers'].items():
                if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                    raise ValueError('pinned FP control header differs')
            subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
            data=path.read_bytes();definition=next(d for d in coff.parse_symbols(data,c.coff_name)[1] if d['symbol']==layout['symbol'])
            raw,names=coff.readonly_section(data,definition['section'],c.coff_name)
            if (definition['offset'] or names!=[dict(symbol=layout['symbol'],offset=0)]
                    or len(raw)!=layout['size'] or list(struct.unpack('<'+'I'*len(values),raw))!=values):
                raise ValueError('cold whole natural FP/locale/API layout differs')
        for observed in m['callback_ranges']:
            raw=c.pe_bytes_at(target,int(observed['address'],16),observed['size'])
            if (hashlib.sha256(raw).hexdigest()!=observed['sha256']
                    or [f'0x{x:08X}' for x in struct.unpack('<'+'I'*(len(raw)//4),raw)]!=observed['entries']):
                raise ValueError('whole observed initializer/RTC range differs')
            if observed['address']=='0x00667948' and observed['entries']!=['0x00000000','0x00000000']:
                raise ValueError('RTC termination range has an unreviewed actual callback')
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
                if row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R123':
                    raise ValueError('anchor loses its independent full control-flow replay')
                for alias in row.get('source_aliases', []):
                    defs = coff.parse_symbols(member(row), c.coff_name)[1]
                    startup.check_alias_definition(next(d for d in defs if d['symbol'] == row['coff_symbol']), next(d for d in defs if d['symbol'] == alias))
                if key!='0x0064FBB6':continue
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
            check_parser_table(row,actual,ins)
            if [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type!=X86_OP_IMM]!=row.get('indirect_jumps',[]):
                raise ValueError('whole FP indirect-jump inventory differs')
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
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-codepage-nls-origins.py'], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('retained independent runtime replay failed: ' + result.stderr[-1500:])
    print('R124 origins OK: 27 complete library candidates / 4252 bytes / 142 fields; five complete non-inventoried controls / 230 bytes / 10 fields; full 48-byte parser table, six-slot trap/registration carrier, complete FP/locale/API cold layouts / 196 bytes, whole defining data and retained R123 controls; cinit initializer callbacks remain pending; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
