#!/usr/bin/env python3
"""Replay complete custom game policies, whole independent parents and source controls."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('game_parent_sdk',ROOT/'scripts/verify-sdk-dependency-origins.py')
SDK=importlib.util.module_from_spec(spec);spec.loader.exec_module(SDK)
PAIRED=SDK.PAIRED;ENDPOINT=SDK.ENDPOINT;module=SDK.module;digest=SDK.digest
MANIFEST_SHA256='9d81bb9ab16f401bfcc986f59b091479813279e9f7f130dd42f31715a74c5900'
KEYS={'0x00410F30':104,'0x0045B760':203,'0x0045B920':131,'0x005F7140':162}
WITNESS_COUNTS={'0x00410F30':29,'0x0045B760':42,'0x0045B920':38,'0x005F7140':54}
DEFAULT_WRITES=[('0x0045B77B','word ptr [ecx + 0x80], 0'),('0x0045B787','dword ptr [edx + 0x7c], 0'),
 ('0x0045B791','word ptr [eax + 0x82], 0'),('0x0045B79D','dword ptr [ecx + 0x8c], 0'),('0x0045B7AA','dword ptr [edx + 0x90], 0'),
 ('0x0045B7B7','dword ptr [eax + 0x94], 0'),('0x0045B7C4','dword ptr [ecx + 0x98], 0'),('0x0045B7D1','dword ptr [edx + 0x50], 0'),
 ('0x0045B7DB','dword ptr [eax + 0x54], 0'),('0x0045B7E5','dword ptr [ecx + 0x58], 0'),('0x0045B7EF','dword ptr [edx + 0x5c], 0'),
 ('0x0045B7F9','dword ptr [eax + 0x4c], 0'),('0x0045B803','word ptr [ecx + 0x84], 0'),('0x0045B80F','word ptr [edx + 0x86], 0'),
 ('0x0045B81B','word ptr [eax + 0x88], 0')]
CONTROL_ADDRESSES=['0x00410F30','0x0045B920','0x005F7140','0x00411C30','0x00411D60','0x00411C70','0x004110F0',
 '0x0045BEE0','0x0045BF30','0x0045C0E0','0x005F8110','0x005F8130','0x005F82D0','0x0045C480','0x005F8A00','0x00655010','0x00668170','0x006563A0','0x00669C54']
CONTROL_SIZES=[104,131,162,56,153,19,22,72,19,19,17,68,19,177,177,21,36,32,36]
ROLES=['candidate-natural-policy']*3+['whole-independent-operation-context']*4+['retained-whole-library-boundary','retained-whole-library-boundary',
 'whole-clear-destructor-alternative','retained-whole-library-boundary','retained-whole-library-boundary',
 'whole-clear-destructor-alternative','retained-whole-library-boundary','retained-whole-library-boundary']
LAYOUT=[20,20,84,84,40,4,4,12,20]
ANCHORS={'0x00456B60':(1186,'R045','0x00410F30','0x00456F92'),'0x004769B0':(134,'R050','0x0045B760','0x004769BA'),
 '0x004567B0':(345,'R045','0x0045B920','0x00456894'),'0x004176F0':(3232,'R065','0x005F7140','0x0041835F')}


def manifest():return json.loads((ROOT/'config/game-parent-policy-origin-evidence.json').read_text())


def verify_implicit_extent(row,data=None,coff_name=None):
    section,d=row['section'],row['source_definition']
    if (section['size']!=row['size'] or d['offset'] or d['type']!=32 or d['storage']!=2
            or [x for x in section['definitions'] if x['type']==32 and x['storage']==2]!=[d]
            or not section['flags']&0x20 or not section['flags']&0x1000):
        raise ValueError('game parent policy implicit negative loses its entire unique defining code COMDAT')
    if data is not None:
        _,_,_,symbols_offset,count,_,_=struct.unpack_from('<HHIIIHH',data)
        strings_offset=symbols_offset+count*18;length=struct.unpack_from('<I',data,strings_offset)[0];strings=data[strings_offset:strings_offset+length]
        matches=[];index=0
        while index<count:
            raw,value,number,kind,storage,aux=struct.unpack_from('<8sIhHBB',data,symbols_offset+index*18)
            if coff_name(raw,strings)==d['symbol'] and number>0:matches.append((value,number,kind,storage,aux))
            index+=1+aux
        if matches!=[(0,section['section'],32,2,0)]:
            raise ValueError('game parent policy implicit negative changes its observed missing primary AUX metadata')


def verify_plan(m):
    if (m['evidence_id']!='R166' or m['target_sha256']!=SDK.manifest()['target_sha256']
            or m['probe']!='probes/VC7GameContextPolicies.cpp' or m['profile']!=SDK.PROFILE or len(m['headers'])!=29
            or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=4
            or [r['address'] for r in m['controls']]!=CONTROL_ADDRESSES or [r['size'] for r in m['controls']]!=CONTROL_SIZES
            or sum(len(r['bindings']) for r in m['controls'])!=63 or len(m['emission'])!=146 or sum(r['size'] for r in m['emission'])!=6709
            or len(m['snapshots'])!=88 or len(m['retained'])!=11 or len(m['retained_frames'])!=2
            or m['layout'] not in m['emission'] or m['layout']['size']!=36 or m['layout_values']!=LAYOUT):
        raise ValueError('game parent policy loses complete bounded source, target, fields, EH/data or emission')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];ae=r['accepted_authored_record']
        if (r['decision']!='authored' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!='GameContextPolicy' or new['owner']!='authored' or new['status']!='unclassified'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='authored',subsystem='GameContextPolicy',disposition='authored',
                    confidence='complete-custom-game-policy-with-whole-authored-parent-and-source-controls',evidence_id='R166')
                or ae!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),
                    internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R166') or len(r['witnesses'])!=WITNESS_COUNTS[a]):
            raise ValueError('game parent policy changes bounded extent or grants false source/private ABI/mapping/exact credit')
        if a=='0x0045B760' and [w for w in r['witnesses'] if w['mnemonic']=='mov' and w['operands'].endswith(', 0')]!=[dict(site=site,mnemonic='mov',operands=operands) for site,operands in DEFAULT_WRITES]:
            raise ValueError('game parent policy loses an actual sparse custom default write')
    if [r['role'] for r in m['controls']]!=ROLES+['whole-policy-eh-carrier','whole-policy-eh-state']*2:
        raise ValueError('game parent policy replaces whole independent/alias/EH controls')
    routes=[['0x0065501B','0x00000000','0x00000000','0x00411C30','0x004110F0','0x00000000'],
      ['0x006563B6','0x00000000','0x00000000','0x0045BF30','0x0045BEE0','0x00641C78','0x0045C0E0','0x00000000'],
      ['0x005F8110','0x005F8130','0x00640F15','0x005F82D0']*2]
    prefixes=['??0ListPolicyObservation','??0ArrayPolicyObservation','?clearOwned@PointerPolicyObservation']
    for i,r in enumerate(m['controls']):
        section,d=r['section'],r['source_definition']
        if (section not in m['emission'] or d not in section['definitions'] or section['size']!=r['size']
                or section['source_sha256']!=r['source_sha256'] or len(section['fields'])!=len(r['bindings'])):
            raise ValueError('game parent policy truncates full defining code/data or field ownership')
        if r['kind']=='code' and (d['offset'] or d['storage']!=2 or d['type']!=32):raise ValueError('game parent policy source lacks its own full function')
        if i<3 and (not d['symbol'].startswith(prefixes[i]) or [b['target_address'] for b in r['bindings']]!=routes[i]):
            raise ValueError('game parent policy substitutes the actual custom operation or its real ABI/children')
        if i in (9,12) and not d['symbol'].startswith('?clear@?$deque@'):
            raise ValueError('game parent policy loses the whole SDK clear/destructor source ambiguity')
        if r['kind']=='eh-code' and (d['offset']!=(11 if i==15 else 22) or r['size']!=(21 if i==15 else 32)):
            raise ValueError('game parent policy slices a cleanup/handler shared carrier')
        if r['kind']=='state-data' and (d['offset']!=8 or r['size']!=36):raise ValueError('game parent policy slices unwind/FuncInfo data')
        for field,b in zip(section['fields'],r['bindings']):
            if (b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address'])
                    or field['type'] not in ('REL32','DIR32') or field['offset']+4>r['size']):
                raise ValueError('game parent policy masks or substitutes a genuine source field')
    negatives=m['negatives']
    if [(r['address'],r['size'],r['target_size']) for r in negatives]!=[('0x00410F30',25,104),('0x0045B920',40,131),('0x0045B760',31,203)]:
        raise ValueError('game parent policy loses entire distinct implicit-construction alternatives')
    for r,prefix,destinations in zip(negatives,['??0ImplicitListObservation','??0ImplicitArrayObservation','??0ImplicitVirtualObservation'],
            [['0x00411C30'],['0x0045BF30','0x0045BEE0','0x00641C78'],['0x00458650','0x00659064']]):
        section,d=r['section'],r['source_definition']
        if (r['role']!='whole-implicit-construction-negative' or section not in m['emission'] or section['size']!=r['size']
                or d not in section['definitions'] or not d['symbol'].startswith(prefix) or d['offset'] or d['storage']!=2 or d['type']!=32
                or section['source_sha256']!=r['source_sha256'] or [b['target_address'] for b in r['bindings']]!=destinations
                or len(section['fields'])!=len(r['bindings'])):
            raise ValueError('game parent policy replaces whole implicit controls with prefixes or unrelated sources')
        for field,b in zip(section['fields'],r['bindings']):
            if b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address']):
                raise ValueError('game parent policy negative hides a real field')
        verify_implicit_extent(r)
    if {r['address'] for r in m['anchors']}!=set(ANCHORS) or len(m['anchors'])!=4:
        raise ValueError('game parent policy loses its full independent game parents')
    for r in m['anchors']:
        size,evidence,child,site=ANCHORS[r['address']]
        if (r['size']!=size or r['origin']['origin']!='authored' or r['origin']['evidence_id']!=evidence
                or r['child']!=child or r['call_site']!=site or int(r['record']['size'])!=size or r['record']['evidence_id']!=evidence
                or not r['window_size'] or r['function']['owner']!='authored'):
            raise ValueError('game parent policy replaces independent whole ownership/argument context')
    loader=next(r for r in m['anchors'] if r['address']=='0x004176F0')
    if loader['switches'] or [(r['table_address'],r['table_size']) for r in loader['direct_switches']]!=[('0x00418390','44'),('0x004183BC','20')]:
        raise ValueError('game parent policy truncates either complete guarded battle-loader switch table')
    snapshots={r['address']:r for r in m['snapshots']}
    protected={'0x00411C30':56,'0x00411D60':153,'0x00411C70':19,'0x004110F0':22,'0x00458650':31,'0x00458670':23,
      '0x004229C0':15,'0x0042E580':5,'0x004212A0':72,'0x004591E0':417,'0x0045AAE0':368,'0x0040D8E0':19,'0x004229D0':28,
      '0x0040F9F0':15,'0x0040E000':158,'0x005F84B0':167,'0x00641FB8':11,'0x00641DAA':11}
    for a,size in protected.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('game parent policy resolves an independent helper/lifetime/copy/math ambiguity')
    r=snapshots['0x0045BEE0']
    if r['size']!=72 or r['origin']['origin']!='library' or r['origin']['evidence_id']!='R073':
        raise ValueError('game parent policy discards the independently accepted whole SDK constructor')
    r=snapshots['0x0045B880']
    if r['size']!=149 or r['origin']['origin']!='unknown':
        raise ValueError('game parent policy classifies an independently unknown selected slot target')
    if m['selected_slot']!=dict(address='0x00659064',target='0x0045B880',size=4,body_sha256=m['selected_slot']['body_sha256']):
        raise ValueError('game parent policy expands one observed virtual slot into a whole vtable/layout claim')
    if [r['handler_address'] for r in m['retained_frames']]!=['0x0065501B','0x006563B6']:
        raise ValueError('game parent policy loses its original complete registered frames')


def verify_negative(raw,linked,actual,row):
    if (len(raw)!=row['size'] or len(linked)!=row['size'] or len(actual)!=row['target_size']
            or digest(raw)!=row['source_sha256'] or linked==actual):
        raise ValueError('game parent policy compares a negative prefix or gives it positive source credit')


def preserved_snapshot(row,function,origin):
    if function==row['function'] and origin==row['origin']:return True
    if row['address'] not in ('0x004110F0','0x00411C30','0x00411C70','0x00411D60','0x00411FE0',
            '0x004120C0','0x00412130','0x00412170','0x004121A0','0x004123E0','0x00412420','0x004125A0'):
        return False
    later=module('game_parent_list_transition','verify-list-policy-dependency-origins.py')
    return later.accepted_snapshot(dict(function=row['function'],origin=row['origin']),function,origin)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [('config/game-parent-policy-origin-evidence.json',MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('game parent policy immutable probe/prior evidence differs: '+path)
    c=module('game_parent_target','compare-coff-function.py');coff=module('game_parent_coff','coff_data.py');cfg=module('game_parent_cfg','verify-authored-origins.py')
    extent=module('game_parent_extent','verify-vendor-record-origins.py');eh=module('game_parent_eh','compiler_eh.py');target=c.verified_target();rows=cfg.rows
    if digest(target)!=m['target_sha256']:raise ValueError('game parent policy target identity differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']}
    if {a for a,r in authored.items() if r['evidence_id']=='R166'}!=(set() if args.evidence_only else set(KEYS)):
        raise ValueError('game parent policy authored extent registry differs from canonical acceptance')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only)
        if not args.evidence_only and authored[a]!=r['accepted_authored_record']:raise ValueError('game parent policy canonical authored evidence differs')
        body=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg']:
            raise ValueError('game parent policy entire extent/body/CFG differs')
        witnesses=[dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,int(a,16))]
        if witnesses!=r['witnesses']:raise ValueError('game parent policy loses complete observed field/loop/call behavior')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif not preserved_snapshot(r,functions[a],origins[a]):raise ValueError('game parent policy alters unrelated canonical owner/boundary')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('game parent policy complete independent body snapshot differs')
    for r in m['anchors']:
        a=r['address'];body=c.pe_bytes_at(target,int(a,16),r['size'])
        if authored[a]!=r['record'] or functions[a]!=r['function'] or origins[a]!=r['origin'] or digest(body)!=r['record']['body_sha256']:
            raise ValueError('game parent policy original whole authored-parent record differs')
        for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [x for x in rows(filename) if x['address']==a]!=r[key]:raise ValueError('game parent policy original full guarded switch registry differs')
        counts=cfg.verify_body(body,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches'])
        if counts!=(int(r['record']['return_count']),int(r['record']['internal_branch_count'])):raise ValueError('game parent policy whole parent CFG differs')
        window=c.pe_bytes_at(target,int(r['window_start'],16),r['window_size']);ins=list(decoder.disasm(window,int(r['window_start'],16)))
        if digest(window)!=r['window_sha256'] or sum(x.size for x in ins)!=len(window) or not any(f'0x{x.address:08X}'==r['call_site'] and x.mnemonic=='call' and x.op_str==hex(int(r['child'],16)) for x in ins):
            raise ValueError('game parent policy loses its actual whole-parent argument/return call window')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r.get('collection','functions')] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('game parent policy original retained SDK/runtime evidence differs')
    for frame in m['retained_frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('game parent policy original frame registration differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions},set())
    slot=m['selected_slot'];raw=c.pe_bytes_at(target,int(slot['address'],16),4)
    sections=module('game_parent_sections','verify-compiler-origins.py').sections(target)
    if (digest(raw)!=slot['body_sha256'] or struct.unpack('<I',raw)[0]!=int(slot['target'],16)
            or not any(base<=int(slot['address'],16) and int(slot['address'],16)+4<=base+size and flags&0x40000000 and not flags&0xA0000000 for base,size,flags in sections)):
        raise ValueError('game parent policy selected readonly virtual slot differs')
    scratch=ROOT/'build/origin-game-parent-policy-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'GameContextPolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or PAIRED.BUFFER.PRIOR.PRIOR.included_headers(result.stdout+result.stderr)!=m['headers']:
            raise ValueError('game parent policy cold source/actual include ownership differs')
        data=path.read_bytes()
        if PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('game parent policy full ordinary code/EH/data emission differs')
        catalog={}
        def add(name,address):
            if name in catalog and catalog[name]!=address:raise ValueError('game parent policy overrides a coherent defining SDK/ordinary source')
            catalog[name]=address
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):add(d['symbol'],int(r['address'],16)+d['offset'])
        snapshots={r['address']:r for r in m['snapshots']}
        for r in m['controls']:
            for field,b in zip(r['section']['fields'],r['bindings']):
                name,a=b['symbol'],b['target_address']
                if name not in catalog:
                    if name=='__except_list':
                        if a!='0x00000000' or field['symbol']!=dict(symbol=name,offset=0,section=0,type=0,storage=2):raise ValueError('game parent policy FS offset is not PE data')
                    elif a not in snapshots:raise ValueError('game parent policy external field lacks its complete actual canonical boundary')
                add(name,int(a,16))
        for r in m['controls']:
            raw,linked=ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:
                raise ValueError('game parent policy complete unmasked comparison differs: '+r['address'])
            if r['kind']=='code':
                if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('game parent policy source lacks full positive own AUX extent')
                cfg.verify_body(actual,int(r['address'],16))
            elif r['kind']=='eh-code':
                ins=list(decoder.disasm(actual,int(r['address'],16)))
                if sum(x.size for x in ins)!=r['size'] or not any(x.address==int(r['address'],16)+r['source_definition']['offset'] and x.mnemonic=='mov' for x in ins) or ins[-1].mnemonic!='jmp' or ins[-1].op_str!='0x6407b8':
                    raise ValueError('game parent policy truncates the whole cleanup/handler shared-tail carrier')
        for r in m['negatives']:
            for b in r['bindings']:
                if b['symbol'] not in catalog and b['target_address'] not in snapshots and b['target_address']!=slot['address']:
                    raise ValueError('game parent policy negative substitutes an unrelated opaque boundary')
                add(b['symbol'],int(b['target_address'],16))
            raw,linked=ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['target_size']);verify_negative(raw,linked,actual,r)
            verify_implicit_extent(r,data,c.coff_name)
            cfg.verify_body(linked,int(r['address'],16))
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<9I',raw))!=LAYOUT:raise ValueError('game parent policy full observation layout differs')
    print('R166 origins OK: four complete custom game policies / 600 bytes; three whole natural policy matches / 397 bytes and independent full 203-byte sparse-default target policy; 19 entire source/code/EH/state comparisons / 1340 bytes and 63 real unmasked fields; three whole implicit-construction negatives / 96 bytes never compare prefixes; four unchanged whole authored parents / 4897 bytes with both complete guarded switch tables / 64 bytes; all 146 cold ordinary sections / 6709 bytes, 29 actual SDK headers and full 36-byte probe layout; one selected virtual slot does not establish a whole vtable/class extent; SDK clear/destructor aliases, existing R073 constructor and independently unknown list/deque/base/lifetime/copy/math policies retained; no reconstructed source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
