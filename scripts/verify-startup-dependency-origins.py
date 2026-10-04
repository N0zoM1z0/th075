#!/usr/bin/env python3
"""Cold-replay R115 startup dependencies without promoting unresolved chains."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
PROFILE = ['/Od','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/I','src']
ACCEPTED = {'0x0064544F':'__SEH_epilog','0x00649735':'__heap_init',
            '0x0064971B':'___heap_select','0x0064A6CD':'___sbh_heap_init'}
PENDING = {'0x00645414':'seh-handler-binding-unresolved',
           '0x006422B2':'crt-error-chain-bindings-unresolved',
           '0x0064228D':'crt-error-chain-bindings-unresolved',
           '0x00648FF5':'crt-command-line-multibyte-bindings-unresolved'}
GLOBALS = {'__crtheap':'0x0068FA78','___active_heap':'0x0068FA7C',
           '___sbh_pHeaderList':'0x0068FA64','___sbh_pHeaderScan':'0x0068FA6C',
           '___sbh_pHeaderDefer':'0x0068FA5C','___sbh_cntHeaderList':'0x0068FA60',
           '___sbh_threshold':'0x0068FA68','___sbh_sizeHeaderList':'0x0068FA70',
           '__osplatform':'0x0068E2E8','__winmajor':'0x0068E2F4'}


def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def zero_fill_region(target,address,size):
    """Check PE loader zero-fill geometry, never read nonexistent file bytes."""
    pe=struct.unpack_from('<I',target,0x3C)[0]
    optional=pe+24
    image_base=struct.unpack_from('<I',target,optional+28)[0]
    table=optional+struct.unpack_from('<H',target,pe+20)[0]
    for i in range(struct.unpack_from('<H',target,pe+6)[0]):
        raw,virtual,rva,raw_size,_,_,_,_,_,flags=struct.unpack_from('<8sIIIIIIHHI',target,table+40*i)
        base=image_base+rva
        if (base+raw_size<=address and address+size<=base+virtual
                and flags&0x40000000 and flags&0x80000000 and not flags&0x20000000):
            return {'section':raw.rstrip(b'\0').decode('ascii'),'base':f'0x{base:08X}',
                    'raw_size':raw_size,'virtual_size':virtual,'flags':f'0x{flags:08X}'}
    raise ValueError('CRT mutable data is not a complete writable PE zero-fill region')


def check_common_definition(symbol):
    if symbol['section']!=0 or symbol['storage']!=2 or symbol['type'] or symbol['offset']!=4:
        raise ValueError('heap common declaration is not a complete four-byte object')


def check_alias_definition(primary,alias):
    if (primary['section']<=0 or primary['section']!=alias['section']
            or primary['offset']!=alias['offset'] or alias['storage']!=2):
        raise ValueError('stack probe alias does not share the complete primary definition')


def check_import_binding(binding,imports):
    match=re.fullmatch(r'__imp__([A-Za-z][A-Za-z0-9_]*)@([0-9]+)',binding['symbol'])
    if (match is None or imports.get(int(binding['target_address'],16))!=
            (binding['dll'],binding['import_name']) or match[1]!=binding['import_name']):
        raise ValueError('CRT API lacks its independent raw PE import identity')


def check_diagnostic_ledger(row,functions,origins):
    key=row['address']
    if key=='0x006503A9' and origins[key].get('evidence_id')=='R123':
        module('codepage_startup_reconciliation','verify-codepage-nls-origins.py').check_historical_root(row,functions[key],origins[key])
        return
    recorded=row['ledger_size']
    if recorded is None:
        if key in functions:
            raise ValueError('non-inventoried diagnostic unexpectedly gains a candidate')
        return
    function=functions[key]
    if int(function['size'])==recorded:
        return
    if origins[key]['evidence_id'] == 'R120':
        module('runtime_cycle_context_reconciliation', 'origin_reconciliation.py').check_root(row, function, origins[key])
        return
    # R116 reconciles this already-frozen entire 48-byte source body. Keep
    # R115's historical 47-byte candidate snapshot and complete source extent.
    origin=origins[key]
    if (key!='0x006440A5' or recorded!=47 or row['size']!=48
            or int(function['size'])!=48 or function['span_end']!=row['span_end']
            or origin['origin']!='library' or origin['evidence_id']!='R116'
            or function['owner']!='library' or function['status']!='excluded'
            or function['proposed_name']!='___crtExitProcess'):
        raise ValueError('unaccepted diagnostic candidate extent differs')


def verify_plan(manifest):
    rows={r['address']:r for r in manifest['functions']}
    if (len(rows)!=8 or set(rows)!=set(ACCEPTED)|set(PENDING)
            or sum(r['size'] for r in rows.values())!=421
            or {k for k,r in rows.items() if r['decision']=='library'}!=set(ACCEPTED)
            or any(rows[k]['decision']!='pending' or rows[k]['uncertainty']!=reason for k,reason in PENDING.items())):
        raise ValueError('R115 bounded cohort or retained pending decisions differ')
    for key,symbol in ACCEPTED.items():
        if rows[key]['coff_symbol']!=symbol:
            raise ValueError('complete heap/epilog source identity differs')
    if {r['symbol']:r['target_address'] for r in manifest['globals']}!=GLOBALS or len(manifest['globals'])!=10:
        raise ValueError('heap/version globals lose their observed source-typed relationships')
    for row in rows.values():
        for binding in row['relocation_bindings']:
            if row['decision']=='pending':
                if binding['target_kind'] not in ('diagnostic','import'):
                    raise ValueError('pending CRT source graph promotes an unverified binding')
                continue
            kind=binding['target_kind']
            destination=binding['target_address']
            if kind=='callee':
                if destination not in ACCEPTED or binding['symbol']!=ACCEPTED[destination] or binding['type']!='REL32':
                    raise ValueError('heap callee lacks its complete independently compared source body')
            elif kind=='global':
                if binding['type']!='DIR32' or GLOBALS.get(binding['symbol'])!=destination or binding['addend']:
                    raise ValueError('heap global field lacks its actual whole-source data control')
            elif kind!='import':
                raise ValueError('accepted CRT source graph contains a diagnostic field')
    calls=[(b['offset'],b['target_address']) for b in rows['0x00649735']['relocation_bindings'] if b['target_kind']=='callee']
    if calls!=[(33,'0x0064971B'),(53,'0x0064A6CD')]:
        raise ValueError('heap initializer loses its actual selector/small-block calls')
    layout=manifest['sdk_layout']
    if layout['values']!=[148,0,4,8,12,16] or layout['size']!=24 or layout['symbol']!='_VersionInfoLayoutProbe':
        raise ValueError('version globals lack the independent complete SDK layout control')
    context=manifest['entry_context']
    witnesses={r['site']:(r['mnemonic'],r['operands']) for r in context['instruction_witnesses']}
    expected={'0x00642338':('mov','edi, 0x94'),'0x00642349':('mov','dword ptr [esi], edi'),
              '0x0064234B':('push','esi'),'0x0064234C':('call','dword ptr [0x657090]'),
              '0x00642352':('mov','ecx, dword ptr [esi + 0x10]'),
              '0x00642355':('mov','dword ptr [0x68e2e8], ecx'),
              '0x0064235B':('mov','eax, dword ptr [esi + 4]'),
              '0x0064235E':('mov','dword ptr [0x68e2f4], eax')}
    if any(witnesses.get(site)!=value for site,value in expected.items()):
        raise ValueError('version globals lack actual GetVersionExA result-field provenance')
    if {'site':'0x006423F5','target':'0x00649735'} not in context['body_facts']['direct_calls']:
        raise ValueError('heap initialization lacks its actual entry call')
    boundaries=manifest['diagnostic_boundaries']
    exit_rows=[r for r in boundaries if r['address']=='0x006440A5']
    if (len(exit_rows)!=1 or exit_rows[0]['ledger_size']!=47 or exit_rows[0]['size']!=48
            or exit_rows[0]['extent_status']!='candidate-omits-terminal-int3'):
        raise ValueError('diagnostic exit source cannot truncate its auxiliary extent')
    if (len(boundaries)!=8 or sum(r['size'] for r in boundaries)!=1144
            or any(r['decision']!='diagnostic' for r in boundaries)
            or {r['address'] for r in boundaries}!=
            {'0x00645468','0x00648C70','0x00648E11','0x006440A5','0x006504F9','0x006503A9','0x006515F3','0x0065152C'}):
        raise ValueError('unresolved exception/error/multibyte boundaries gain origin credit')
    if next(r for r in boundaries if r['address']=='0x00645468')['ledger_size'] is not None:
        raise ValueError('non-inventoried exception handler cannot gain candidate credit')
    literals=manifest['literal_controls']
    required={(r['member_offset'],b['symbol'],b['target_address']) for r in rows.values() for b in r['relocation_bindings'] if b['symbol'].startswith('??_C@')}
    required.update((r['member_offset'],b['symbol'],b['target_address']) for r in boundaries for b in r['relocation_bindings'] if b['symbol'].startswith('??_C@'))
    if (len(literals)!=8 or sum(r['data_size'] for r in literals)!=121
            or {(r['member_offset'],r['symbol'],r['target_address']) for r in literals}!=required):
        raise ValueError('diagnostic literal fields lack their whole readonly source definitions')
    alias=manifest['stack_probe_alias']
    if alias['coff_symbol']!='__chkstk' or alias['alias']!='__alloca_probe' or alias['size']!=61 or alias['address']!='0x00642510':
        raise ValueError('existing stack probe loses its complete same-address alias evidence')
    return rows


def check_ledger(row,functions,origins,evidence_only):
    if row['address'] in ('0x0064232C', '0x00648FF5') and origins.get(row['address'], {}).get('evidence_id') == 'R126':
        module('environment_startup_reconciliation', 'verify-environment-startup-origins.py').check_historical_root(
            row, functions[row['address']], origins[row['address']])
        return
    if row['address'] == '0x006422B2' and origins.get(row['address'], {}).get('evidence_id') == 'R121':
        module('startup_registration_reconciliation', 'verify-startup-registration-origins.py').check_historical_startup(
            row, functions[row['address']], origins[row['address']])
        return
    if row['address'] in PENDING and origins.get(row['address'], {}).get('evidence_id') == 'R120':
        module('runtime_cycle_reconciliation', 'origin_reconciliation.py').check_root(
            row, functions[row['address']], origins[row['address']])
        return
    key,address,size=row['address'],int(row['address'],16),row['size']
    function,origin=functions[key],origins[key]
    if (int(function['size'])!=size or function['span_end']!=row['span_end']
            or int(row['span_end'],16)!=address+size-1
            or any(address<int(k,16)<address+size for k in functions)):
        raise ValueError('new startup acceptance has an unresolved complete extent/interior')
    if function['source_file'] or function['match_percent']!='0.00':
        raise ValueError('origin archive comparison cannot grant source or exact credit')
    if evidence_only:
        return
    if key in ACCEPTED:
        if (origin['origin']!='library' or origin['disposition']!='exclude' or origin['evidence_id']!='R115'
                or function['owner']!='library' or function['status']!='excluded' or function['proposed_name']!=ACCEPTED[key]):
            raise ValueError('R115 accepted library ledger differs')
    elif (key=='0x00645414' and origin['origin']=='library' and origin['disposition']=='exclude'
            and origin['evidence_id']=='R117' and function['owner']=='library'
            and function['status']=='excluded' and function['proposed_name']=='__SEH_prolog'):
        # R117 independently closes the complete handler's validation/unwind/NLG
        # edges. Preserve this historical pending record and its whole source body.
        return
    elif (origin['origin']!='unknown' or origin['disposition']!='review' or origin['evidence_id']!='R115'
            or origin['confidence']!=row['uncertainty'] or function['owner'] or function['status']!='unclassified'):
        raise ValueError('R115 pending chain gains unearned ownership')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args()
    comparison=module('sd_target','compare-coff-function.py')
    runtime=module('sd_archive','verify-runtime-origins.py')
    record=module('sd_compare','verify-vendor-record-origins.py')
    sdk=module('sd_cfg','verify-sdk-origins.py')
    coff=module('sd_symbols','coff_data.py')
    imports_module=module('sd_imports','verify-import-origins.py')
    lifetime=module('sd_facts','verify-game-lifetime-origins.py')
    authored=module('sd_extent','verify-authored-origins.py')
    external=module('sd_literal','verify-runtime-external-origins.py')
    compiler=module('sd_sections','verify-compiler-origins.py')
    target=comparison.verified_target()
    manifest=json.loads((ROOT/'config/startup-dependency-origin-evidence.json').read_text())
    if manifest['evidence_id']!='R115' or manifest['target_sha256']!=hashlib.sha256(target).hexdigest():
        raise ValueError('R115 pinned target/evidence differs')
    rows=verify_plan(manifest)
    functions={r['address']:r for r in record.rows('functions.csv')}
    origins={r['address']:r for r in record.rows('function-origins.csv')}
    imports=imports_module.pe_imports(target,comparison)
    sections=compiler.sections(target)
    archive=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest()!=manifest['archive_sha256']:
        raise ValueError('pinned CRT archive differs')
    members={offset:(name,data) for offset,name,data in runtime.archive_members(archive)}
    def member(row):
        name,data=members[row['member_offset']]
        if name!=row['member'] or hashlib.sha256(data).hexdigest()!=row['member_sha256']:
            raise ValueError('cold extracted complete CRT member differs')
        return data
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    decoder.detail=True
    scratch=ROOT/'build/origin-startup-dependency-verification'
    scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path=Path(temporary)/'VendorMember.obj'
        for literal in manifest['literal_controls']:
            data=member(literal)
            source=external.readonly_member_data(data,literal['symbol'],literal,comparison.coff_name)
            actual=comparison.pe_bytes_at(target,int(literal['target_address'],16),len(source))
            external.check_scalar(source,actual,literal['data_size'],sections,int(literal['target_address'],16))
        # Each mutable binding has a real defining COMMON or entire BSS section.
        for global_row in manifest['globals']:
            data=member(global_row)
            entries=coff.parse_symbols(data,comparison.coff_name)[1]
            found=[s for s in entries if s['symbol']==global_row['symbol']]
            if len(found)!=1 or found[0]!=global_row['source_definition']:
                raise ValueError('CRT global defining symbol differs')
            symbol=found[0]
            if global_row['definition_kind']=='common':
                check_common_definition(symbol)
            elif global_row['definition_kind']=='bss-section':
                header=struct.unpack_from('<8sIIIIIIHHI',data,20+(symbol['section']-1)*40)
                definitions=[s for s in entries if s['section']==symbol['section'] and s['storage']==2]
                if (header[3]!=72 or header[4] or header[7] or not header[9]&0x80
                        or definitions!=global_row['whole_bss_definitions']
                        or int(global_row['target_address'],16)-symbol['offset']!=0x68E2E4):
                    raise ValueError('OS globals lose the whole vendor BSS topology')
                zero_fill_region(target,0x68E2E4,72)
            else:
                raise ValueError('unproved mutable data definition')
            if zero_fill_region(target,int(global_row['target_address'],16),4)!=global_row['zero_fill_region']:
                raise ValueError('CRT global PE zero-fill geometry differs')
        layout=manifest['sdk_layout']
        probe=ROOT/layout['probe']
        if layout['profile']!=PROFILE or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256']:
            raise ValueError('SDK layout natural probe/profile differs')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned SDK/CRT interpretation header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*PROFILE],cwd=ROOT,
                       capture_output=True,text=True,check=True)
        data=path.read_bytes()
        definition=next(s for s in coff.parse_symbols(data,comparison.coff_name)[1] if s['symbol']==layout['symbol'])
        raw,names=coff.readonly_section(data,definition['section'],comparison.coff_name)
        if (definition['offset'] or len(raw)!=24 or names!=[{'symbol':layout['symbol'],'offset':0}]
                or list(struct.unpack('<6I',raw))!=layout['values'] or hashlib.sha256(raw).hexdigest()!=layout['sha256']):
            raise ValueError('cold SDK layout does not cover its whole readonly definition')
        for row in manifest['functions']+manifest['diagnostic_boundaries']+[manifest['stack_probe_alias']]:
            key,address=row['address'],int(row['address'],16)
            if key in rows:
                check_ledger(row,functions,origins,args.evidence_only)
            elif row['decision']=='diagnostic':
                check_diagnostic_ledger(row,functions,origins)
            data=member(row)
            path.write_bytes(data)
            # An auxiliary extent is mandatory, including static functions and INT3.
            source,relocations=comparison.object_function(path,row['coff_symbol'])
            actual=comparison.pe_bytes_at(target,address,row['size'])
            if (len(source)!=row['size'] or hashlib.sha256(source).hexdigest()!=row['source_sha256']
                    or hashlib.sha256(actual).hexdigest()!=row['body_sha256']):
                raise ValueError('complete startup source/target extent/hash differs')
            bindings=[{k:b[k] for k in ('offset','type','symbol','addend','target_address')} for b in row['relocation_bindings']]
            solved=comparison.solved_relocations(source,actual,relocations,address)
            if len(solved)!=len(bindings):
                raise ValueError('startup source omits a typed relocation')
            mask=set()
            for b,r,s in zip(bindings,relocations,solved):
                if b!={'offset':r['offset'],'type':r['type'],'symbol':r['symbol'],'addend':r['addend'],
                       'target_address':s['solved_destination']}:
                    raise ValueError('complete startup typed relocation differs')
                mask.update(range(r['offset'],r['offset']+4))
            if any(source[i]!=actual[i] for i in range(len(actual)) if i not in mask):
                raise ValueError('startup source differs outside every declared field')
            instructions=list(decoder.disasm(actual,address))
            if (sum(i.size for i in instructions)!=row['size'] or lifetime.body_facts(instructions)!=row['body_facts']):
                raise ValueError('startup complete instruction inventory differs')
            if row['decision']=='library':
                record.compare_complete_body(source,relocations,actual,address,bindings,comparison,sdk)
            if row.get('cfg') is not None and list(authored.verify_body(actual,address))!=row['cfg']:
                raise ValueError('startup whole body CFG differs')
            for binding in row['relocation_bindings']:
                if binding['target_kind']=='import':
                    check_import_binding(binding,imports)
            if row is manifest['stack_probe_alias']:
                entries=coff.parse_symbols(data,comparison.coff_name)[1]
                primary=next(s for s in entries if s['symbol']=='__chkstk')
                alias=next(s for s in entries if s['symbol']=='__alloca_probe')
                check_alias_definition(primary,alias)
                if (source!=actual or relocations
                        or origins[key]['evidence_id']!=row['origin_evidence'] or origins[key]['origin']!='library'):
                    raise ValueError('stack probe alias is not the same full independently reviewed definition')
        context=manifest['entry_context']
        if origins[context['address']]['evidence_id'] == 'R126':
            module('environment_entry_context', 'verify-environment-startup-origins.py').check_historical_context(
                context, functions[context['address']], origins[context['address']])
        if (int(functions[context['address']]['size'])!=context['size']
                or functions[context['address']]['span_end']!=context['span_end']):
            raise ValueError('entry context ledger loses its complete extent')
        address=int(context['address'],16)
        actual=comparison.pe_bytes_at(target,address,context['size'])
        instructions=list(decoder.disasm(actual,address))
        if (hashlib.sha256(actual).hexdigest()!=context['body_sha256']
                or list(authored.verify_body(actual,address))!=context['cfg']
                or lifetime.body_facts(instructions)!=context['body_facts']):
            raise ValueError('entry observation loses its whole extent/CFG')
        by_site={f'0x{i.address:08X}':i for i in instructions}
        for witness in context['instruction_witnesses']:
            instruction=by_site[witness['site']]
            if (instruction.mnemonic,instruction.op_str)!=(witness['mnemonic'],witness['operands']):
                raise ValueError('OS version/heap lifecycle independent instruction witness differs')
        if imports.get(0x657090)!=('KERNEL32.dll','GetVersionExA'):
            raise ValueError('OS version context lacks GetVersionExA raw identity')
    if runtime.main()!=0:
        raise ValueError('retained R006/R025 archive anchors failed')
    print('R115 origins OK: four library bodies / 196 bytes, closed heap graph / 17 fields and full SDK layout; '
          'four historical pending startup records / 225 bytes retained; eight complete diagnostic source bodies / 1144 bytes; '
          'eight whole literals / 121 bytes and existing 61-byte stack probe alias verified; no source or exact credit.')
    return 0


if __name__=='__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
