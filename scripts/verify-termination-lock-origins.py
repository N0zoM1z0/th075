#!/usr/bin/env python3
"""Cold-replay R118 CRT lock/termination controls with explicit unresolved allocator roots."""
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
from capstone import Cs,CS_ARCH_X86,CS_MODE_32,CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM

ROOT=Path(__file__).resolve().parents[1]
ACCEPTED={'0x00646658':'__unlock','0x006440E7':'__initterm','0x006465BA':'__mtinitlocks',
          '0x0065053F':'___crtInitCritSecAndSpinCount','0x0065052F':'___crtInitCritSecNoSpinCount@8'}
PENDING={'0x00644187':'crt-termination-lock-onexit-bindings-unresolved',
         '0x00646725':'crt-lock-lazy-initializer-error-chain-unresolved',
         '0x00646685':'crt-lazy-lock-allocator-tls-boundaries-unresolved',
         '0x0064162B':'crt-onexit-allocator-bindings-unresolved'}
LAYOUT=[24,0,4,8,12,16,20,4,8,0xC0000017]
FLAGS=[1,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1]+[0]*17
REQUIRED={
    '0x0064665E':('push','dword ptr [eax*8 + 0x670150]'),
    '0x00646665':('call','dword ptr [0x6571d4]'),
    '0x006465BE':('mov','edi, 0x68e348'),
    '0x006465C3':('cmp','dword ptr [esi*8 + 0x670154], 1'),
    '0x006465D6':('push','0xfa0'),
    '0x006465DD':('add','edi, 0x18'),
    '0x006465E0':('call','0x65053f'),
    '0x006465EC':('cmp','esi, 0x24'),
    '0x00650554':('cmp','dword ptr [0x68e2e8], 1'),
    '0x00650562':('call','dword ptr [0x6570a8]'),
    '0x0065056C':('push','0x6673dc'),
    '0x00650572':('call','dword ptr [0x6570a0]'),
    '0x00650578':('mov','dword ptr [0x68e770], eax'),
    '0x00650581':('mov','eax, 0x65052f'),
    '0x00650586':('mov','dword ptr [0x68e770], eax'),
    '0x00650595':('call','eax'),
    '0x006505AD':('cmp','dword ptr [ebp - 0x1c], 0xc0000017'),
    '0x006505B6':('push','8'),
    '0x006505B8':('call','dword ptr [0x6571b8]'),
    '0x00650533':('call','dword ptr [0x6570ec]'),
    '0x0065053C':('ret','8'),
    '0x006440E8':('mov','esi, eax'),
    '0x006440F2':('call','eax'),
    '0x006440F4':('add','esi, 4'),
    '0x006440F7':('cmp','esi, dword ptr [esp + 8]'),
    '0x006441F5':('push','0x66c05c'),
    '0x006441FA':('mov','eax, 0x66c054'),
    '0x006441FF':('call','0x6440e7'),
    '0x00644205':('push','0x66c068'),
    '0x0064420A':('mov','eax, 0x66c060'),
    '0x0064420F':('call','0x6440e7'),
}


def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result


def verify_plan(m):
    rows={r['address']:r for r in m['functions']}
    if (len(rows)!=9 or set(rows)!=set(ACCEPTED)|set(PENDING)
            or {k for k,r in rows.items() if r['decision']=='library'}!=set(ACCEPTED)
            or sum(rows[k]['size'] for k in ACCEPTED)!=273
            or any(rows[k]['decision']!='pending' or rows[k]['uncertainty']!=reason for k,reason in PENDING.items())):
        raise ValueError('R118 bounded cohort or unresolved allocator/termination decisions differ')
    for k,sym in ACCEPTED.items():
        if rows[k]['coff_symbol']!=sym or rows[k]['extent_basis']!='function-auxiliary-record':raise ValueError('accepted lock body lacks its whole source identity')
    lazy=rows['0x00646685'];funclets=m['pending_funclets']
    if (lazy['size']!=160 or lazy['ledger_size']!=151 or lazy['span_end']!='0x00646724'
            or funclets!=[
                {'address':'0x0064671C','size':9,'parent':'0x00646685','source_offset':151,'source_symbol':'$L20182','decision':'pending',
                 'uncertainty':'crt-lock-finally-parent-bindings-unresolved'},
                {'address':'0x00644236','size':14,'parent':'0x00644187','source_offset':175,'source_symbol':'$L20876','decision':'pending',
                 'uncertainty':'crt-exit-cleanup-parent-bindings-unresolved'}]):
        raise ValueError('lazy lock loses its complete source extent and pending interior finally entry')
    graph={**rows,**{r['address']:r for r in m['anchors']}}
    for k in ACCEPTED:
        for b in rows[k]['relocation_bindings']:
            if b['target_kind']=='callee':
                callee=graph.get(b['target_address'])
                if not callee or callee['decision'] not in ('library','anchor') or callee['coff_symbol']!=b['symbol']:
                    raise ValueError('lock edge lacks a complete independently checked source callee')
            elif b['target_kind'] not in ('import','state','literal','scope-table'):
                raise ValueError('accepted lock body retains an unresolved field')
    if m['sdk_layout']['size']!=40 or m['sdk_layout']['values']!=LAYOUT:raise ValueError('lock storage lacks full SDK layout/error controls')
    if [(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']]!=[
            (1698134,'__locktable','0x00670150',288),(1698134,'_lclcritsects','0x0068E348',336),
            (1364582,'?__crtInitCritSecAndSpinCount@?1??0@@9@9','0x0068E770',4),
            (1663884,'__umaskval','0x0068E2E4',72)]:raise ValueError('lock/cache/version state lacks whole defining source topology')
    if m['lock_flags']!=FLAGS or sum(FLAGS)!=14:raise ValueError('whole 36-entry table loses its fourteen static slots')
    scopes=m['scope_tables']
    if [(r['symbol'],r['target_address'],r['size']) for r in scopes]!=[
            ('$T19908','0x00667408',12),('$T20187','0x006615D0',12),('$T20885','0x00661200',12)]:raise ValueError('EH scopes lose whole defining sections')
    if scopes[0]['relocations']!=[
            {'offset':4,'type':'DIR32','symbol':'$L19903','addend':0,'target_address':'0x0065059C'},
            {'offset':8,'type':'DIR32','symbol':'$L19904','addend':0,'target_address':'0x006505AA'}]:
        raise ValueError('accepted dynamic API lacks its complete actual filter/handler scope bindings')
    if [(r['symbol'],r['target_address'],r['section_name'],r['size']) for r in m['range_markers']]!=[
            ('___xp_a','0x0066C054','.CRT$XPA',4),('___xp_z','0x0066C05C','.CRT$XPZ',4),
            ('___xt_a','0x0066C060','.CRT$XTA',4),('___xt_z','0x0066C068','.CRT$XTZ',4),
            ('___xi_a','0x0066C038','.CRT$XIA',4),('___xi_z','0x0066C050','.CRT$XIZ',4)]:
        raise ValueError('callback ranges lack actual complete boundary markers')
    if [(r['address'],r['size'],len(r['entries'])) for r in m['callback_ranges']]!=[
            ('0x0066C054',12,3),('0x0066C060',12,3),('0x0066C038',28,7)]:
        raise ValueError('callback tables are truncated or lose end markers')
    registration=m['onexit_registration']
    if (registration['section_name']!='.CRT$XIC' or registration['target_address']!='0x0066C03C'
            or registration['size']!=4 or registration['relocations']!=[
                {'offset':0,'type':'DIR32','symbol':'___onexitinit','addend':0,'target_address':'0x0064162B'}]):
        raise ValueError('onexit registration lacks its complete original subsection/field')
    contexts=m['diagnostic_contexts']
    if {(r['address'],r['size']) for r in contexts}!={('0x00646389',239),('0x0064411D',106),('0x00644331',18),('0x00647F98',9),('0x00642A61',113),('0x0064228D',37)}:
        raise ValueError('lock/allocator/TLS context loses its complete own source body')
    witnesses={w['site']:(w['mnemonic'],w['operands']) for r in list(rows.values())+contexts for w in r['instruction_witnesses']}
    if any(witnesses.get(site)!=value for site,value in REQUIRED.items()):raise ValueError('actual lock/API/fallback/range witnesses differ')
    required={(r['member_offset'],b['symbol'],b['target_address']) for r in list(rows.values())+contexts for b in r['relocation_bindings'] if b['target_kind']=='literal'}
    if len(m['literal_controls'])!=7 or {(r['member_offset'],r['symbol'],r['target_address']) for r in m['literal_controls']}!=required:
        raise ValueError('dynamic/TLS source strings lack all complete readonly definitions')
    return rows


def check_ledger(row,functions,origins,evidence_only):
    if row['address'] in PENDING and origins.get(row['address'], {}).get('evidence_id') == 'R120':
        module('runtime_cycle_reconciliation', 'origin_reconciliation.py').check_root(
            row, functions[row['address']], origins[row['address']])
        return
    key=row['address'];function=functions[key];expected=row.get('ledger_size',row['size'])
    if int(function['size'])!=expected or int(function['span_end'],16)!=int(key,16)+expected-1:raise ValueError('unaccepted lock/termination boundary changes')
    interiors=[k for k in functions if int(key,16)<int(k,16)<int(key,16)+row['size']]
    expected_interiors={'0x00646685':['0x0064671C'],'0x00644187':['0x00644236']}.get(key,[])
    if interiors!=expected_interiors:raise ValueError('lock extent has an undeclared interior candidate')
    if function['source_file'] or function['match_percent']!='0.00':raise ValueError('origin replay cannot grant source or exact credit')
    if evidence_only:return
    origin=origins[key]
    if key in ACCEPTED:
        if (origin['origin']!='library' or origin['disposition']!='exclude' or origin['evidence_id']!='R118'
                or function['owner']!='library' or function['status']!='excluded' or function['proposed_name']!=ACCEPTED[key]):raise ValueError('R118 library ledger differs')
    elif (origin['origin']!='unknown' or origin['disposition']!='review' or origin['evidence_id']!='R118'
            or origin['confidence']!=PENDING[key] or function['owner'] or function['status']!='unclassified'):
        raise ValueError('unresolved allocator/lock chain gains ownership')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    old=module('lock_helpers','verify-runtime-error-origins.py');security=module('lock_scope','verify-security-eh-origins.py')
    c=old.module('lock_target','compare-coff-function.py');archive_reader=old.module('lock_archive','verify-runtime-origins.py')
    coff=old.module('lock_coff','coff_data.py');startup=old.module('lock_geometry','verify-startup-dependency-origins.py')
    imports_module=old.module('lock_imports','verify-import-origins.py');record=old.module('lock_ledger','verify-vendor-record-origins.py')
    facts=old.module('lock_facts','verify-game-lifetime-origins.py');literal=old.module('lock_literal','verify-runtime-external-origins.py')
    sections=old.module('lock_sections','verify-compiler-origins.py')
    target=c.verified_target();m=json.loads((ROOT/'config/termination-lock-origin-evidence.json').read_text())
    if m['evidence_id']!='R118' or hashlib.sha256(target).hexdigest()!=m['target_sha256']:raise ValueError('R118 target identity differs')
    rows=verify_plan(m);functions={r['address']:r for r in record.rows('functions.csv')};origins={r['address']:r for r in record.rows('function-origins.csv')}
    imports=imports_module.pe_imports(target,c);target_sections=sections.sections(target)
    archive=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest()!=m['archive_sha256']:raise ValueError('pinned CRT archive differs')
    members={o:(n,d) for o,n,d in archive_reader.archive_members(archive)}
    def member(row):
        name,data=members[row['member_offset']]
        if name!=row['member'] or hashlib.sha256(data).hexdigest()!=row['member_sha256']:raise ValueError('whole cold source member differs')
        return data
    state_map={};scope_map={}
    for row in m['state_data']+m['scope_tables']+m['range_markers']+[m['onexit_registration']]:
        raw,description=old.whole_section(member(row),row['symbol'],c,coff);a=int(row['target_address'],16)
        if description!=row['source_section'] or description['size']!=row['size']:raise ValueError('whole source data topology differs')
        if 'section_name' in row and security.source_section_name(member(row),row['symbol'],c,coff)!=row['section_name']:raise ValueError('callback marker/initializer is not its actual source subsection')
        for definition in description['definitions']:state_map[definition['symbol']]=a+definition['offset']
        if raw is None:
            if not int(description['flags'],16)&0x80 or description['relocations'] or startup.zero_fill_region(target,a,row['size'])!=row['zero_fill_region']:raise ValueError('whole static/cache storage lacks loader zero-fill geometry')
        else:
            actual=c.pe_bytes_at(target,a,len(raw));linked=bytearray(raw)
            if len(description['relocations'])!=len(row['relocations']):raise ValueError('whole source data fields differ')
            for field,b in zip(description['relocations'],row['relocations']):
                if {k:b[k] for k in field}!=field:raise ValueError('whole data relocation metadata differs')
                struct.pack_into('<I',linked,field['offset'],(int(b['target_address'],16)+field['addend'])&0xffffffff)
            if linked!=actual or hashlib.sha256(raw).hexdigest()!=row['source_sha256'] or hashlib.sha256(actual).hexdigest()!=row['body_sha256']:raise ValueError('whole initialized data comparison differs')
            if row['symbol']=='__locktable' and (list(struct.unpack('<72I',raw))[::2]!=[0]*36 or list(struct.unpack('<72I',raw))[1::2]!=FLAGS):raise ValueError('complete pointer/type lock table differs')
            if row in m['scope_tables']:
                literal.check_scalar(actual,actual,row['size'],target_sections,a);scope_map[row['symbol']]=a
                if struct.unpack_from('<I',raw)[0]!=0xffffffff:raise ValueError('whole scope table loses enclosing-level sentinel')
    for row in m['common_globals']:
        definitions=[d for d in coff.parse_symbols(member(row),c.coff_name)[1] if d['symbol']==row['symbol']]
        if definitions!=[row['source_definition']]:raise ValueError('onexit common definition differs')
        startup.check_common_definition(definitions[0]);a=int(row['target_address'],16)
        if startup.zero_fill_region(target,a,4)!=row['zero_fill_region']:raise ValueError('actual onexit storage lacks common/loader provenance')
        state_map[row['symbol']]=a
    for row in m['callback_ranges']:
        a=int(row['address'],16);raw=c.pe_bytes_at(target,a,row['size'])
        if hashlib.sha256(raw).hexdigest()!=row['sha256'] or [f'0x{x:08X}' for x in struct.unpack('<'+str(row['size']//4)+'I',raw)]!=row['entries']:raise ValueError('complete merged callback range differs')
    for row in m['literal_controls']:
        source=literal.readonly_member_data(member(row),row['symbol'],row,c.coff_name);a=int(row['target_address'],16)
        literal.check_scalar(source,c.pe_bytes_at(target,a,len(source)),len(source),target_sections,a)
        if a==0x66159C and source!=b'kernel32.dll\0':raise ValueError('dynamic critical-section DLL literal differs')
        if a==0x6673DC and source!=b'InitializeCriticalSectionAndSpinCount\0':raise ValueError('dynamic critical-section export literal differs')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32);decoder.detail=True
    scratch=ROOT/'build/origin-termination-lock-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path=Path(temp)/'VendorMember.obj';layout=m['sdk_layout'];probe=ROOT/layout['probe']
        if layout['profile']!=old.PROFILE or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256']:raise ValueError('natural critical-section probe differs')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:raise ValueError('pinned SDK critical-section header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*old.PROFILE],cwd=ROOT,capture_output=True,text=True,check=True)
        data=path.read_bytes();definition=next(d for d in coff.parse_symbols(data,c.coff_name)[1] if d['symbol']==layout['symbol']);raw,names=coff.readonly_section(data,definition['section'],c.coff_name)
        if definition['offset'] or names!=[{'symbol':layout['symbol'],'offset':0}] or len(raw)!=40 or list(struct.unpack('<10I',raw))!=LAYOUT:raise ValueError('whole cold readonly critical-section layout array differs')
        for row in m['functions']+m['anchors']+m['diagnostic_contexts']:
            key=row['address'];a=int(key,16)
            if key in rows:check_ledger(row,functions,origins,args.evidence_only)
            elif row['decision']=='anchor':
                if origins[key]['origin']!=row['origin'] or origins[key]['evidence_id']!=row['origin_evidence']:raise ValueError('retained complete anchor origin differs')
            elif int(functions[key]['size'])!=row['ledger_size']:raise ValueError('unaccepted allocator/TLS context extent differs')
            path.write_bytes(member(row));source,fields=c.object_function(path,row['coff_symbol']);actual=c.pe_bytes_at(target,a,row['size'])
            if len(source)!=row['size'] or hashlib.sha256(source).hexdigest()!=row['source_sha256'] or hashlib.sha256(actual).hexdigest()!=row['body_sha256']:raise ValueError('complete own auxiliary extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields]!=[b['local_symbol_offset'] for b in row['relocation_bindings']]:raise ValueError('full local relocation provenance differs')
            ins=list(decoder.disasm(actual,a));starts={i.address for i in ins}
            if sum(i.size for i in ins)!=row['size'] or facts.body_facts(ins)!=row['body_facts']:raise ValueError('whole lock/termination instruction inventory differs')
            branches=[{'site':f'0x{i.address:08X}','target':f'0x{i.operands[0].imm:08X}'} for i in ins if i.group(CS_GRP_JUMP)]
            if branches!=row['branches'] or any(int(b['target'],16) not in starts for b in branches):raise ValueError('whole lock/termination branch closure differs')
            indirect=[{'site':f'0x{i.address:08X}','operand':i.op_str} for i in ins if i.mnemonic=='call' and i.operands[0].type!=X86_OP_IMM]
            if indirect!=row['indirect_calls']:raise ValueError('whole callback/API inventory differs')
            if [{'site':f'0x{i.address:08X}','mnemonic':i.mnemonic,'operands':i.op_str} for i in ins]!=row['instruction_witnesses']:raise ValueError('full API/cache/ABI/loop witnesses differ')
            for b in row['relocation_bindings']:
                kind=b['target_kind']
                if kind=='import':startup.check_import_binding(b,imports)
                elif kind=='state' and (b['type']!='DIR32' or state_map.get(b['symbol'])!=int(b['target_address'],16)):raise ValueError('state binding loses complete source-definition provenance')
                elif kind=='scope-table' and scope_map.get(b['symbol'])!=int(b['target_address'],16):raise ValueError('scope pointer loses its complete readonly definition')
        # The source's finally is a label inside the whole 160-byte primary,
        # not a separately fabricated nine-byte source function.
        for fragment in m['pending_funclets']:
            parent=rows[fragment['parent']];defs=coff.parse_symbols(member(parent),c.coff_name)[1]
            primary=next(d for d in defs if d['symbol']==parent['coff_symbol']);entry=next(d for d in defs if d['symbol']==fragment['source_symbol'])
            if entry['section']!=primary['section'] or entry['offset']-primary['offset']!=fragment['source_offset']:raise ValueError('interior cleanup loses its actual source parent label')
            f=functions[fragment['address']];o=origins[fragment['address']]
            if o['evidence_id'] == 'R120':
                module('runtime_cycle_label_reconciliation', 'origin_reconciliation.py').check_label(
                    fragment, f, o, functions, origins)
                continue
            if int(f['size'])!=fragment['size'] or f['source_file'] or f['match_percent']!='0.00' or o['origin']!='unknown' or f['owner'] or f['status']!='unclassified':raise ValueError('pending parent cleanup gains source/exact/origin credit')
            if not args.evidence_only and (o['evidence_id']!='R118' or o['confidence']!=fragment['uncertainty']):raise ValueError('pending cleanup ledger loses its explicit uncertainty')
        # Re-read both label definitions for every scope pointer, including the
        # accepted wrapper's filter/handler inside its entire own primary body.
        for scope in m['scope_tables']:
            defs=coff.parse_symbols(member(scope),c.coff_name)[1];owner=rows[scope['parent']]
            primary=next(d for d in defs if d['symbol']==owner['coff_symbol'])
            for b in scope['relocations']:
                label=next(d for d in defs if d['symbol']==b['symbol'])
                if label['section']!=primary['section'] or int(b['target_address'],16)!=int(owner['address'],16)+label['offset']-primary['offset']:
                    raise ValueError('EH label pointer is not inside its complete defining source parent')
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-security-eh-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:raise ValueError('retained security/runtime replay failed: '+result.stderr[-1000:])
    print('R118 origins OK: five library bodies / 273 bytes; whole 36-entry lock table / 288 bytes, '
          'fourteen static critical sections / 336 bytes, complete dynamic API/fallback/EH bindings and callback ranges; '
          'four roots / 444 source bytes and two interior cleanup candidates / 23 bytes retained as historical pending snapshots; current ownership recorded separately; no source or exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
