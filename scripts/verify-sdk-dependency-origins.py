#!/usr/bin/env python3
"""Cold-replay complete SDK dependencies through independently accepted whole parents."""
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
spec=importlib.util.spec_from_file_location('sdk_dependency_endpoint',ROOT/'scripts/verify-vector-endpoint-origins.py')
ENDPOINT=importlib.util.module_from_spec(spec);spec.loader.exec_module(ENDPOINT)
PAIRED=ENDPOINT.PAIRED;module=ENDPOINT.module;digest=PAIRED.digest
MANIFEST_SHA256='5d824965f665db683f064d0ea5d2e90d7acb3bcbabc347af8c34dbe33d26ba77'
CONFIDENCE='complete-vc7-sdk-dependency-with-independent-whole-library-parent-fields'
KEYS={'0x00415F60':44,'0x00422290':151,'0x0042E120':151,'0x0045AFB0':50,'0x0045B640':108}
PROFILE=['/Od','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/I','src','/showIncludes']
LAYOUT=[2,20,60,116,20,20,20,1,1,1,1,1,20,20,1]
PARENTS=['0x00415A80','0x00421DD0','0x0042DEF0','0x0045A7E0','0x0045B2B0']
CONTEXTS=['0x00422270','0x0042E100','0x00422610','0x0042E390','0x004229C0','0x0042E580']
BOUNDARIES=['0x004223C0','0x004223E0','0x00422420','0x0042E250','0x0042E270','0x0042E2B0','0x0045AFA0']
ORDINARY_POP_DIFFERENCES={43:(0xF8,0xFC),46:(0xF8,0xFC),49:(0xFC,0xF8),58:(0xFC,0xF8),66:(0xFC,0xF8),72:(0xFC,0xF8),81:(0xF8,0xFC),96:(0xFC,0xF8)}


def verify_control_bytes(row,raw,linked,actual):
    if (len(raw)!=row['size'] or len(linked)!=row['size'] or len(actual)!=row['size']
            or digest(raw)!=row['source_sha256'] or digest(actual)!=row['body_sha256']):
        raise ValueError('SDK dependency loses complete source or target bytes: '+row['address'])
    if row['role']=='whole-ordinary-pop-alternative':
        differences={i:(a,b) for i,(a,b) in enumerate(zip(linked,actual)) if a!=b}
        if row['size']!=151 or differences!=ORDINARY_POP_DIFFERENCES:
            raise ValueError('SDK dependency entire ordinary pop alternative differs from its frozen negative comparison')
    elif linked!=actual:
        raise ValueError('SDK dependency full unmasked positive comparison differs: '+row['address'])


def manifest():return json.loads((ROOT/'config/sdk-dependency-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id']!='R164' or m['target_sha256']!=PAIRED.manifest()['target_sha256']
            or m['probe']!='probes/VC7SDKDependencyContexts.cpp' or m['profile']!=PROFILE
            or len(m['headers'])!=28 or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=5
            or len(m['controls'])!=39 or sum(r['size'] for r in m['controls'])!=1988 or sum(len(r['bindings']) for r in m['controls'])!=57
            or len(m['emission'])!=55 or sum(r['size'] for r in m['emission'])!=2360
            or m['layout_values']!=LAYOUT or m['layout'] not in m['emission'] or m['layout']['size']!=60
            or len(m['retained'])!=17 or len(m['snapshots'])!=41):
        raise ValueError('SDK dependency loses bounded complete source, real fields, parent/ordinary emission or layout')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function']
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='library' or new['status']!='excluded' or new['module']!='VC7STL'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R164')):
            raise ValueError('SDK dependency changes original extent or grants false ownership/source/private ABI/exact credit')
    controls=m['controls'];records={r['address']:r for r in m['functions']}
    if ([r['address'] for r in controls[:16]]!=list(KEYS)+PARENTS+CONTEXTS
            or [r['size'] for r in controls[5:]]!=[22,177,177,51,29,25,25,25,25,15,5]+[25]*6+[5,5,11,8,27,36,27,36,5,44,44,151,151,50,108,25,25]
            or [r['role'] for r in controls]!=['candidate-sdk-owner']*5+['retained-whole-library-parent']*5+['whole-independent-operation-context']*6
             +['retained-whole-library-boundary']*6+['whole-independent-operation-context']*2+['retained-whole-library-boundary','retained-placement-new',
               'whole-sdk-eh-carrier','whole-sdk-eh-state','whole-ordinary-eh-carrier','whole-ordinary-eh-state','retained-placement-delete','retained-compiler-wrapper']
             +['byte-equal-ordinary-alternative','whole-ordinary-pop-alternative','whole-ordinary-pop-alternative']
             +['byte-equal-ordinary-alternative']*4):
        raise ValueError('SDK dependency replaces or truncates independent source/parent/ordinary/EH controls')
    routes={'0x00415F60':[],'0x00422290':['0x00422270','0x00422610'],'0x0042E120':['0x0042E100','0x0042E390'],
            '0x0045AFB0':['0x0045AAE0'],'0x0045B640':['0x00656391','0x00000000','0x00000000','0x004063D0','0x004591E0','0x00000000']}
    for i,r in enumerate(controls):
        section,d=r['section'],r['source_definition']
        if (section not in m['emission'] or d not in section['definitions'] or section['size']!=r['size']
                or section['source_sha256']!=r['source_sha256'] or len(section['fields'])!=len(r['bindings'])):
            raise ValueError('SDK dependency loses entire defining section or genuine field ownership')
        if r['kind']=='code' and (d['offset'] or d['storage']!=2 or d['type']!=32):
            raise ValueError('SDK dependency regular source lacks a full own defining function')
        if i<5 and (d['symbol']!=records[r['address']]['symbol'] or 'Ordinary' in d['symbol']
                or [b['target_address'] for b in r['bindings']]!=routes[r['address']]):
            raise ValueError('SDK dependency replaces actual SDK operation, record or placement destinations')
        if i>=32 and 'Ordinary' not in d['symbol']:
            raise ValueError('SDK dependency loses distinct complete byte-equal ordinary source')
        if r['kind']=='eh-code' and (r['size']!=27 or d['offset']!=17):
            raise ValueError('SDK dependency truncates actual placement cleanup/handler carrier')
        if r['kind']=='state-data' and (r['size']!=36 or d['offset']!=8):
            raise ValueError('SDK dependency truncates actual unwind and FuncInfo state')
        for field,b in zip(section['fields'],r['bindings']):
            if (b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address'])
                    or field['type'] not in ('DIR32','REL32') or field['offset']+4>r['size']):
                raise ValueError('SDK dependency masks, substitutes or omits a genuine actual field')
    if [r['address'] for r in controls[32:]]!=list(KEYS)+['0x00422270','0x0042E100']:
        raise ValueError('SDK dependency changes complete ordinary alternative coverage')
    snapshots={r['address']:r for r in m['snapshots']}
    protected={'0x00422610':25,'0x0042E390':25,'0x004229C0':15,'0x0042E580':5,'0x004212A0':72,
         '0x004591E0':417,'0x0045AAE0':368,'0x004229D0':28,'0x0040F9F0':15,'0x0040E000':158,'0x005F84B0':167,
         '0x00641FB8':11,'0x00641DAA':11,'0x0040D8E0':19}
    for a,size in protected.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':
            raise ValueError('SDK dependency resolves independent record/lifetime/copy/destruction/math ambiguity')
    for a,origin,evidence,size in [('0x00422A20','compiler','R037',44),('0x00412300','library','R160',5),('0x006407B8','library','R142',54),
              ('0x00640F15','library','R142',5),('0x00415A80','library','R074',22),('0x00421DD0','library','R072',177),
              ('0x0042DEF0','library','R072',177),('0x0045A7E0','library','R033',51),('0x0045B2B0','library','R033',29)]:
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!=origin or r['origin']['evidence_id']!=evidence:
            raise ValueError('SDK dependency discards independently accepted compiler/library/runtime parent')
    negative=m['negative_backward'];d=negative['source_definition'];section=negative['section']
    if (negative['address']!='0x0045AFB0' or negative['target_size']!=50 or negative['size']!=48 or section['size']!=48
            or section not in m['emission'] or d not in section['definitions'] or not d['symbol'].startswith('??$_Copy_backward_opt@PAU')
            or d['offset'] or d['type']!=32 or d['storage']!=2 or negative['bindings']!=[dict(offset=37,type='REL32',symbol='??4Copy116Observation@@QAEAAU0@ABU0@@Z',addend=0,target_address='0x0045AAE0')]):
        raise ValueError('SDK dependency replaces full distinct backward operation with a prefix or unrelated member')
    for r in m['retained']:
        if r['file'] not in m['retained_sha256'] or r['record']['address']!=r['address']:
            raise ValueError('SDK dependency loses exact original independent source record')
    if (len(m['retained_frames'])!=1 or m['retained_frames'][0]['handler_address']!='0x00656391'
            or m['retained_frames'][0]['state_count']!='1' or m['retained_frames'][0]['evidence_id']!='R020'):
        raise ValueError('SDK dependency loses original complete placement frame registration')


def check_ledger(row,function,origin,evidence_only=False):ENDPOINT.check_ledger(row,function,origin,evidence_only)


def accepted_snapshot(snapshot,function,origin):
    m=manifest()
    if digest((ROOT/'config/sdk-dependency-origin-evidence.json').read_bytes())!=MANIFEST_SHA256:
        raise ValueError('SDK dependency immutable complete evidence differs')
    verify_plan(m);r=next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin'])
                and function==r['accepted_function'] and origin==r['accepted_origin'])


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [('config/sdk-dependency-origin-evidence.json',MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('SDK dependency immutable probe/prior evidence differs: '+path)
    c=module('sdk_target','compare-coff-function.py');coff=module('sdk_coff','coff_data.py');extent=module('sdk_extent','verify-vendor-record-origins.py')
    cfg=module('sdk_cfg','verify-authored-origins.py');eh=module('sdk_eh','compiler_eh.py');target=c.verified_target();rows=PAIRED.BUFFER.PRIOR.PRIOR.rows
    if digest(target)!=m['target_sha256']:raise ValueError('SDK dependency pinned target differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};records={r['address']:r for r in m['functions']}
    for r in m['functions']:check_ledger(r,functions[r['address']],origins[r['address']],args.evidence_only)
    for r in m['snapshots']:
        a=r['address']
        if a in records:check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('SDK dependency changes original accepted/protected canonical boundary')
        body=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(body)!=r['body_sha256']:raise ValueError('SDK dependency entire independent boundary differs')
        if a in ('0x004591E0','0x0045AAE0','0x004212A0'):cfg.verify_body(body,int(a,16))
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())['functions'] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('SDK dependency original source/typed-parent/compiler/runtime record differs')
    for frame in m['retained_frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('SDK dependency original registered frame differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions},set())
    scratch=ROOT/'build/origin-sdk-dependency-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'SDKDependencyContexts.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or PAIRED.BUFFER.PRIOR.PRIOR.included_headers(result.stdout+result.stderr)!=m['headers']:
            raise ValueError('SDK dependency complete cold source or actual header ownership differs')
        data=path.read_bytes()
        if PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('SDK dependency entire ordinary code/EH/data emission differs')
        catalog={}
        def add(symbol,address):
            if symbol in catalog and catalog[symbol]!=address:raise ValueError('SDK dependency overrides independently complete defining source')
            catalog[symbol]=address
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):add(d['symbol'],int(r['address'],16)+d['offset'])
        snapshots={r['address']:r for r in m['snapshots']};retained={r['address']:r for r in m['retained']}
        for r in m['controls']:
            for field,b in zip(r['section']['fields'],r['bindings']):
                name,a=b['symbol'],b['target_address']
                if name in catalog:
                    if catalog[name]!=int(a,16):raise ValueError('SDK dependency substitutes actual complete source operation')
                    continue
                if name=='__except_list':
                    if a!='0x00000000' or field['symbol']!=dict(symbol=name,offset=0,section=0,type=0,storage=2):raise ValueError('SDK dependency FS offset is not ordinary PE data')
                elif a not in snapshots:raise ValueError('SDK dependency external field lacks its full independent canonical boundary')
                elif r['address'] in PARENTS+BOUNDARIES:
                    old=json.loads(retained[r['address']]['record']['relocation_bindings'])
                    if not any(x['offset']==b['offset'] and x['type']==b['type'] and x['addend']==b['addend'] and x['target_address']==a
                        and x['symbol'].split('@',1)[0]==name.split('@',1)[0] for x in old):raise ValueError('SDK dependency replaces original same-family whole parent/helper field')
                elif a not in ('0x004591E0','0x0045AAE0','0x004212A0','0x006407B8','0x00640F15'):
                    raise ValueError('SDK dependency external field lies outside independent opaque copy/lifetime/runtime boundaries')
                add(name,int(a,16))
        decoder=Cs(CS_ARCH_X86,CS_MODE_32)
        for r in m['controls']:
            raw,linked=ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            verify_control_bytes(r,raw,linked,actual)
            if r['kind']=='code':
                if r['address']=='0x00422A20':
                    d=r['source_definition'];ss=r['section']
                    if d['offset'] or [x for x in ss['definitions'] if x['type']==32 and x['storage']==2]!=[d] or not ss['flags']&0x20 or not ss['flags']&0x1000:
                        raise ValueError('SDK dependency generated wrapper loses entire unique defining COMDAT')
                elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:
                    raise ValueError('SDK dependency regular source loses full positive own AUX extent')
                cfg.verify_body(actual,int(r['address'],16))
                if r['role']=='whole-ordinary-pop-alternative':cfg.verify_body(linked,int(r['address'],16))
            elif r['kind']=='eh-code':
                ins=list(decoder.disasm(actual,int(r['address'],16)))
                if (sum(x.size for x in ins)!=27 or not any(x.address==int(r['address'],16)+17 and x.mnemonic=='mov' for x in ins)
                        or ins[-1].mnemonic!='jmp' or ins[-1].op_str!='0x6407b8'):
                    raise ValueError('SDK dependency truncates placement cleanup/handler shared-tail code')
        negative=m['negative_backward'];raw,linked=ENDPOINT.link(data,negative,catalog,c)
        if (len(raw)!=48 or len(linked)!=48 or extent.complete_aux_section_size(data,negative['source_definition']['symbol'],c.coff_name)!=48
                or linked==c.pe_bytes_at(target,int(negative['address'],16),negative['target_size'])):
            raise ValueError('SDK dependency loses complete genuine backward alternative or accepts a prefix')
        cfg.verify_body(linked,int(negative['address'],16))
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<15I',raw))!=LAYOUT:raise ValueError('SDK dependency complete actual observation layout differs')
    print('R164 origins OK: five full SDK dependencies / 504 bytes through unchanged complete R074/R072/R033 library parents; 39 whole source/code/EH/state controls / 1988 bytes and 57 unmasked actual fields; 37 complete positive comparisons / 1686 bytes and two entire ordinary-pop negative comparisons / 302 bytes; all 55 cold ordinary sections / 2360 bytes, 28 actual SDK headers and full 60-byte layout; five ordinary controls / 252 bytes are fully byte-equal, while each whole ordinary pop differs at eight local-stack displacement bytes; genuine full backward copy / 48 differs from actual forward copy / 50; placement frame, whole cleanup/handler/state, original compiler/runtime parents and opaque assignment/copy/lifetime boundaries retained; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
