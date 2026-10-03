#!/usr/bin/env python3
"""Replay R117 whole CRT security/SEH bodies and preserve unresolved termination roots."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM
import importlib.util

ROOT=Path(__file__).resolve().parents[1]
ACCEPTED={'0x00645238':'___security_init_cookie','0x0064FCF7':'__ValidateEH3RN',
          '0x00640B24':'__global_unwind2','0x00645414':'__SEH_prolog',
          '0x00640BF1':'__NLG_Notify1','0x00640BFA':'__NLG_Notify'}
PENDING={'0x006405E0':'security-failure-handler-termination-unresolved',
         '0x0064529E':'security-user-handler-termination-unresolved',
         '0x0064425B':'crt-doexit-lock-callback-state-unresolved'}
LAYOUT=[28,4,8,24,28,4,20,24,0x1000000,0xCC,64,60,0,6,20,24,
        0x5A4D,0x4550,0x10B,40,8,12,36,0x80000000,8,0,4,8,0,4]
REQUIRED_WITNESSES={
    '0x00645247':('cmp','eax, 0xbb40e64e'),
    '0x0064524F':('lea','eax, [ebp - 8]'),
    '0x00645253':('call','dword ptr [0x657188]'),
    '0x00645259':('mov','esi, dword ptr [ebp - 4]'),
    '0x0064525C':('xor','esi, dword ptr [ebp - 8]'),
    '0x0064527B':('call','dword ptr [0x6571a4]'),
    '0x00645289':('mov','dword ptr [0x66fe30], esi'),
    '0x00645291':('mov','dword ptr [0x66fe30], 0xbb40e64e'),
    '0x0064FD0A':('mov','eax, dword ptr fs:[0x18]'),
    '0x0064FD16':('mov','ecx, dword ptr [eax + 8]'),
    '0x0064FD20':('cmp','ebx, dword ptr [eax + 4]'),
    '0x0064FDA3':('push','0x1c'),
    '0x0064FDA5':('lea','eax, [ebp - 0x20]'),
    '0x0064FDAA':('call','dword ptr [0x657100]'),
    '0x0064FDB8':('cmp','dword ptr [ebp - 8], 0x1000000'),
    '0x0064FDC5':('test','byte ptr [ebp - 0xc], 0xcc'),
    '0x0064FDCB':('mov','ecx, dword ptr [ebp - 0x1c]'),
    '0x0064FDCE':('cmp','word ptr [ecx], 0x5a4d'),
    '0x0064FDD9':('mov','eax, dword ptr [ecx + 0x3c]'),
    '0x0064FDEA':('cmp','word ptr [eax + 0x18], 0x10b'),
    '0x0064FE1B':('test','byte ptr [ecx + 0x27], 0x80'),
    '0x0064FEA4':('mov','ebx, dword ptr [0x657104]'),
    '0x0064FEB1':('call','ebx'),
    '0x0064FF11':('call','ebx'),
    '0x006454B0':('mov','eax, dword ptr [edi + ecx*4 + 4]'),
    '0x006454C7':('call','eax'),
    '0x006454F2':('mov','eax, dword ptr [edi + ecx*4 + 8]'),
    '0x00645501':('mov','eax, dword ptr [edi + ecx*4 + 8]'),
    '0x0064550F':('call','eax'),
    '0x00644162':('mov','esi, 0x66c000'),
    '0x00644169':('mov','edi, 0x66c034'),
    '0x00644173':('mov','eax, dword ptr [esi]'),
    '0x00644179':('call','eax'),
    '0x0064417B':('add','esi, 4'),
    '0x0064417E':('cmp','esi, edi'),
    '0x00644180':('jb','0x644173'),
}


def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def verify_plan(manifest):
    rows={r['address']:r for r in manifest['functions']}
    if (len(rows)!=9 or set(rows)!=set(ACCEPTED)|set(PENDING)
            or {k for k,r in rows.items() if r['decision']=='library'}!=set(ACCEPTED)
            or sum(rows[k]['size'] for k in ACCEPTED)!=779
            or any(rows[k]['decision']!='pending' or rows[k]['uncertainty']!=reason for k,reason in PENDING.items())):
        raise ValueError('R117 complete cohort or unresolved termination decisions differ')
    if any(rows[k]['coff_symbol']!=symbol or rows[k]['extent_basis']!='function-auxiliary-record' for k,symbol in ACCEPTED.items()):
        raise ValueError('accepted security/SEH body lacks its own complete source identity')
    if rows['0x006405E0']['size']!=49 or rows['0x006405E0']['span_end']!='0x00640610':
        raise ValueError('pending failure source truncates its embedded filter/terminal INT3')
    handler=manifest['handler_context']
    if (handler['address']!='0x00645468' or handler['size']!=230 or handler['ledger_size'] is not None
            or handler['decision']!='closed-dependency' or handler['coff_symbol']!='__except_handler3'):
        raise ValueError('non-inventoried whole SEH handler gains candidate credit')
    auxiliary=manifest['auxiliary_contexts']
    if [(r['address'],r['size'],r['coff_symbol'],r['ledger_size'],r['decision']) for r in auxiliary]!=[
            ('0x00640B44',34,'__unwind_handler',None,'closed-dependency')]:
        raise ValueError('local unwind registration lacks its whole non-inventoried handler')
    graph={**rows,handler['address']:handler,**{r['address']:r for r in auxiliary+manifest['anchors']}}
    for row in [*(rows[k] for k in ACCEPTED),handler,*auxiliary,*manifest['anchors']]:
        for b in row['relocation_bindings']:
            if b['target_kind']=='callee':
                callee=graph.get(b['target_address'])
                if not callee or callee['decision'] not in ('library','anchor','closed-dependency') or callee['coff_symbol']!=b['symbol']:
                    raise ValueError('SEH edge lacks its independently compared whole source callee')
            elif b['target_kind'] not in ('import','state','continuation','import-thunk'):
                raise ValueError('accepted SEH body retains an unresolved field')
        if any(call['target']!='0x00654B54' and (call['target'] not in graph
                or graph[call['target']]['decision'] not in ('library','anchor','closed-dependency'))
                for call in row['body_facts']['direct_calls']):
            raise ValueError('fixed same-section call lacks its complete independent callee')
    shared=manifest['nlg_shared_tail']
    if shared!={'address':'0x00640BF1','size':33,'site':'0x00640BF8','target':'0x00640C04',
                'owner':'0x00640BFA','cleanup':4,'source_offsets':[205,214]}:
        raise ValueError('NLG entry lacks its complete shared-tail carrier and RET 4')
    if manifest['sdk_layout']['size']!=120 or manifest['sdk_layout']['values']!=LAYOUT:
        raise ValueError('security validation loses complete SDK TIB/memory/PE/entropy layout')
    states=manifest['state_data']
    if [(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in states]!=[
            (1201902,'_nValidPages','0x0068E720',76),(1210238,'__NLG_Destination','0x0066FE50',16),
            (1236214,'___security_cookie','0x0066FE30',4),(1237072,'_user_handler','0x0068E32C',4)]:
        raise ValueError('CRT states lack complete actual defining sections')
    registration=manifest['initializer_registration']
    if (registration['section_name']!='.CRT$XCAA' or registration['target_address']!='0x0066C004'
            or registration['size']!=4 or registration['relocations']!=[
                {'offset':0,'type':'DIR32','symbol':'___security_init_cookie','addend':0,'target_address':'0x00645238'}]):
        raise ValueError('cookie initializer lacks the whole actual CRT registration')
    table=manifest['initializer_table']
    if (table['address']!='0x0066C000' or table['end_marker']!='0x0066C034' or table['size']!=56
            or len(table['entries'])!=14 or table['entries'][0]!='0x00000000'
            or table['entries'][1]!='0x00645238' or table['entries'][-1]!='0x00000000'):
        raise ValueError('cookie registration lacks full merged startup table and end marker')
    if [(r['symbol'],r['target_address'],r['section_name'],r['size']) for r in manifest['initializer_markers']]!=[
            ('___xc_a','0x0066C000','.CRT$XCA',4),('___xc_z','0x0066C034','.CRT$XCZ',4)]:
        raise ValueError('initializer traversal lacks complete defining source boundary markers')
    contexts=manifest['diagnostic_contexts']
    if {(r['address'],r['size'],r['decision']) for r in contexts}!={
            ('0x0064411D',106,'diagnostic'),('0x00644187',195,'diagnostic')}:
        raise ValueError('initializer/termination context loses its whole own auxiliary extent')
    witnesses={w['site']:(w['mnemonic'],w['operands']) for row in list(rows.values())+[handler]+contexts for w in row['instruction_witnesses']}
    if any(witnesses.get(site)!=operation for site,operation in REQUIRED_WITNESSES.items()):
        raise ValueError('SDK fields, indirect API/scope callbacks or initializer range lack actual witnesses')
    required={(r['member_offset'],b['symbol'],b['target_address']) for r in rows.values() for b in r['relocation_bindings'] if b['target_kind']=='literal'}
    if len(manifest['literal_controls'])!=9 or {(r['member_offset'],r['symbol'],r['target_address']) for r in manifest['literal_controls']}!=required:
        raise ValueError('security error strings lack every whole source literal definition')
    return rows


def source_section_name(data,symbol,c,coff):
    definition=next(d for d in coff.parse_symbols(data,c.coff_name)[1] if d['symbol']==symbol)
    name=struct.unpack_from('<8s',data,20+(definition['section']-1)*40)[0].rstrip(b'\0')
    if name.startswith(b'/'):
        offset,count=struct.unpack_from('<II',data,8)
        return data[offset+18*count+int(name[1:]):].split(b'\0',1)[0].decode('ascii')
    return name.decode('ascii')


def check_ledger(row,functions,origins,evidence_only):
    if row['address'] in PENDING and origins.get(row['address'], {}).get('evidence_id') == 'R120':
        module('runtime_cycle_reconciliation', 'origin_reconciliation.py').check_root(
            row, functions[row['address']], origins[row['address']])
        return
    key=row['address'];function=functions[key]
    expected=48 if key=='0x006405E0' else row['size']
    if (int(function['size'])!=expected or int(function['span_end'],16)!=int(key,16)+expected-1
            or any(int(key,16)<int(k,16)<int(key,16)+row['size'] for k in functions)):
        raise ValueError('security/EH candidate has an unaccepted boundary change')
    if function['source_file'] or function['match_percent']!='0.00':
        raise ValueError('archive origin cannot grant source or exact credit')
    if evidence_only:return
    origin=origins[key]
    if key in ACCEPTED:
        if (origin['origin']!='library' or origin['disposition']!='exclude' or origin['evidence_id']!='R117'
                or function['owner']!='library' or function['status']!='excluded' or function['proposed_name']!=ACCEPTED[key]):
            raise ValueError('R117 complete library ledger differs')
    elif (origin['origin']!='unknown' or origin['disposition']!='review' or origin['evidence_id']!='R117'
            or origin['confidence']!=PENDING[key] or function['owner'] or function['status']!='unclassified'):
        raise ValueError('pending security termination chain gains ownership')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    old=module('security_error','verify-runtime-error-origins.py')
    c=old.module('security_target','compare-coff-function.py')
    archive_reader=old.module('security_archive','verify-runtime-origins.py')
    coff=old.module('security_coff','coff_data.py')
    startup=old.module('security_geometry','verify-startup-dependency-origins.py')
    import_reader=old.module('security_imports','verify-import-origins.py')
    record=old.module('security_ledger','verify-vendor-record-origins.py')
    facts=old.module('security_facts','verify-game-lifetime-origins.py')
    literal=old.module('security_literal','verify-runtime-external-origins.py')
    sections=old.module('security_sections','verify-compiler-origins.py')
    target=c.verified_target();manifest=json.loads((ROOT/'config/security-eh-origin-evidence.json').read_text())
    if manifest['evidence_id']!='R117' or hashlib.sha256(target).hexdigest()!=manifest['target_sha256']:
        raise ValueError('R117 target identity differs')
    rows=verify_plan(manifest);functions={r['address']:r for r in record.rows('functions.csv')};origins={r['address']:r for r in record.rows('function-origins.csv')}
    imports=import_reader.pe_imports(target,c);target_sections=sections.sections(target)
    archive=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest()!=manifest['archive_sha256']:raise ValueError('pinned CRT archive differs')
    members={o:(n,d) for o,n,d in archive_reader.archive_members(archive)}
    def member(row):
        name,data=members[row['member_offset']]
        if name!=row['member'] or hashlib.sha256(data).hexdigest()!=row['member_sha256']:raise ValueError('whole cold source member differs')
        return data
    for row in manifest['literal_controls']:
        raw=literal.readonly_member_data(member(row),row['symbol'],row,c.coff_name);a=int(row['target_address'],16)
        literal.check_scalar(raw,c.pe_bytes_at(target,a,len(raw)),len(raw),target_sections,a)
    state_map={}
    for row in manifest['state_data']+[manifest['initializer_registration']]+manifest['initializer_markers']:
        raw,description=old.whole_section(member(row),row['symbol'],c,coff);a=int(row['target_address'],16)
        if description!=row['source_section'] or description['size']!=row['size']:raise ValueError('whole source state topology differs')
        if 'section_name' in row and source_section_name(member(row),row['symbol'],c,coff)!=row['section_name']:
            raise ValueError('initializer association is not its actual whole CRT source section')
        for definition in description['definitions']:state_map[definition['symbol']]=a+definition['offset']
        if raw is None:
            if not int(description['flags'],16)&0x80 or description['relocations'] or startup.zero_fill_region(target,a,row['size'])!=row['zero_fill_region']:
                raise ValueError('EH cache/callback lacks complete loader zero-fill geometry')
        else:
            actual=c.pe_bytes_at(target,a,len(raw));linked=bytearray(raw)
            if len(description['relocations'])!=len(row['relocations']):raise ValueError('whole state fields differ')
            for field,b in zip(description['relocations'],row['relocations']):
                if {k:b[k] for k in field}!=field:raise ValueError('whole state relocation differs')
                struct.pack_into('<I',linked,field['offset'],(int(b['target_address'],16)+field['addend'])&0xffffffff)
            if linked!=actual or hashlib.sha256(raw).hexdigest()!=row['source_sha256'] or hashlib.sha256(actual).hexdigest()!=row['body_sha256']:
                raise ValueError('complete initialized state comparison differs')
            if row['symbol']=='___security_cookie' and struct.unpack('<I',raw)[0]!=0xBB40E64E:raise ValueError('cookie default/source guard differs')
            if row['symbol']=='__NLG_Destination' and struct.unpack('<4I',raw)!=(0x19930520,0,0,0):raise ValueError('whole NLG signature/state differs')
    table=manifest['initializer_table'];raw=c.pe_bytes_at(target,int(table['address'],16),table['size'])
    if hashlib.sha256(raw).hexdigest()!=table['sha256'] or [f'0x{x:08X}' for x in struct.unpack('<14I',raw)]!=table['entries']:
        raise ValueError('whole merged initializer table differs')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32);decoder.detail=True
    scratch=ROOT/'build/origin-security-eh-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        path=Path(temp)/'VendorMember.obj';layout=manifest['sdk_layout'];probe=ROOT/layout['probe']
        if layout['profile']!=old.PROFILE or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256']:raise ValueError('natural SDK probe identity/profile differs')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:raise ValueError('pinned SDK interpretation header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*old.PROFILE],cwd=ROOT,capture_output=True,text=True,check=True)
        data=path.read_bytes();definition=next(e for e in coff.parse_symbols(data,c.coff_name)[1] if e['symbol']==layout['symbol']);raw,names=coff.readonly_section(data,definition['section'],c.coff_name)
        if definition['offset'] or names!=[{'symbol':layout['symbol'],'offset':0}] or len(raw)!=120 or list(struct.unpack('<30I',raw))!=LAYOUT:
            raise ValueError('cold SDK control loses its complete readonly layout array')
        for row in manifest['functions']+[manifest['handler_context']]+manifest['auxiliary_contexts']+manifest['anchors']+manifest['diagnostic_contexts']:
            key=row['address'];a=int(key,16)
            if key in rows:check_ledger(row,functions,origins,args.evidence_only)
            elif row['decision']=='closed-dependency':
                if key in functions or any(a<int(k,16)<a+row['size'] for k in functions):raise ValueError('non-inventoried handler overlaps or gains candidate credit')
            elif row['decision']=='anchor':
                if origins[key]['origin']!=row['origin'] or origins[key]['evidence_id']!=row['origin_evidence']:raise ValueError('retained anchor origin differs')
            elif int(functions[key]['size'])!=row['ledger_size']:raise ValueError('diagnostic context boundary differs')
            path.write_bytes(member(row));source,fields=c.object_function(path,row['coff_symbol']);actual=c.pe_bytes_at(target,a,row['size'])
            if len(source)!=row['size'] or hashlib.sha256(source).hexdigest()!=row['source_sha256'] or hashlib.sha256(actual).hexdigest()!=row['body_sha256']:raise ValueError('whole own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            ins=list(decoder.disasm(actual,a));starts={i.address for i in ins}
            if sum(i.size for i in ins)!=row['size'] or facts.body_facts(ins)!=row['body_facts']:raise ValueError('whole security/SEH instruction inventory differs')
            branches=[{'site':f'0x{i.address:08X}','target':f'0x{i.operands[0].imm:08X}'} for i in ins if i.group(CS_GRP_JUMP)]
            if branches!=row['branches']:raise ValueError('whole security/SEH branch inventory differs')
            if row['decision'] in ('library','closed-dependency') and any(int(b['target'],16) not in starts and not (key=='0x00640BF1' and b['target']=='0x00640C04') for b in branches):raise ValueError('accepted security/SEH has an unresolved shared branch')
            indirect=[{'site':f'0x{i.address:08X}','operand':i.op_str} for i in ins if i.mnemonic=='call' and i.operands[0].type!=X86_OP_IMM]
            if indirect!=row['indirect_calls']:raise ValueError('whole dynamic callback/API inventory differs')
            witnesses=[{'site':f'0x{i.address:08X}','mnemonic':i.mnemonic,'operands':i.op_str} for i in ins]
            if witnesses!=row['instruction_witnesses']:raise ValueError('complete source-typed API/layout/cache/callback witnesses differ')
            for b in row['relocation_bindings']:
                kind=b['target_kind']
                if kind=='import':startup.check_import_binding(b,imports)
                elif kind=='state' and (state_map.get(b['symbol'])!=int(b['target_address'],16) or b['type']!='DIR32'):raise ValueError('actual state field lacks whole source-definition provenance')
                elif kind=='continuation' and (key!='0x00640B24' or b['target_address']!='0x00640B3C' or b['symbol']!='_gu_return' or b['local_symbol_offset']!=24 or 0x640B3C not in starts):raise ValueError('RtlUnwind continuation is not the actual local source label')
                elif kind=='import-thunk':
                    if b['target_address']!='0x00654B54' or b['symbol']!='_RtlUnwind@16':raise ValueError('global unwind has a substituted import thunk')
                    import_reader.check_thunk(c.pe_bytes_at(target,0x654B54,6),0x657180,imports.get(0x657180),'KERNEL32.dll','RtlUnwind')
        # Both own auxiliary extents are contiguous in the same pinned exsup section.
        pair=[rows['0x00640BF1'],rows['0x00640BFA']]
        definitions=coff.parse_symbols(member(pair[0]),c.coff_name)[1]
        source_defs=[next(d for d in definitions if d['symbol']==row['coff_symbol']) for row in pair]
        if source_defs[0]['section']!=source_defs[1]['section'] or [d['offset'] for d in source_defs]!=[205,214] or pair[0]['size']!=9 or pair[1]['size']!=24:
            raise ValueError('NLG shared source carrier omits an entry extent')
        carrier=c.pe_bytes_at(target,0x640BF1,33);starts={i.address for i in decoder.disasm(carrier,0x640BF1)}
        if 0x640C04 not in starts or pair[1]['body_facts']['returns']!=[{'site':'0x00640C0F','cleanup':4}]:raise ValueError('NLG full shared tail loses RET 4')
    for script in ('verify-runtime-error-origins.py','verify-import-origins.py'):
        result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('retained runtime/import replay failed: '+result.stderr[-1000:])
    print('R117 origins OK: six library bodies / 779 bytes; two closed non-inventoried handlers / 264 bytes, full 33-byte NLG shared tail, '
          'whole SDK layouts and actual loader/state/initializer provenance; three termination roots / 394 bytes retained as historical pending snapshots; current ownership recorded separately; no source or exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
