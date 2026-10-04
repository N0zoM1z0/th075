#!/usr/bin/env python3
"""Cold-replay whole list iterator/insertion/erase and exception dependency graphs."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('iterator_prior',ROOT/'scripts/verify-list-policy-dependency-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/list-iterator-policy-origin-evidence.json'
MANIFEST_SHA256='55c6b19bff1713585d9617cf418deeee7d2f0bddfce7d42d27f3f15cccb3f394'
KEYS={'0x00411C90':42,'0x00411CC0':31,'0x00411CE0':17,'0x00411D00':40,'0x00411D30':42,
 '0x00411E00':19,'0x00411E20':42,'0x004121C0':28,'0x00411F20':186,'0x00411EA0':115,
 '0x004121E0':19,'0x00412200':22,'0x00412240':189,'0x00412310':126,'0x00412460':25,
 '0x00412480':35,'0x004124D0':22,'0x00412510':53,'0x00412550':44}
CONFIDENCE='complete-vc7-list-iterator-with-whole-game-parents-and-closed-source-eh-graph'
LAYOUT=PRIOR.LAYOUT+[4,4,12,1,4]
PROTECTED=dict(PRIOR.PROTECTED,**{'0x004124B0':16,'0x004124C0':11,'0x004122C9':52})
EH={'0x00655040':(27,17),'0x00655060':(18,8),'0x00654D20':(18,8),'0x00654D40':(18,8),
 '0x00654D60':(18,8),'0x00654D80':(10,0)}
STATE={'0x006681E4':(88,60),'0x0066823C':(36,8),'0x00667A6C':(36,8),
 '0x00667A90':(36,8),'0x00667AB4':(36,8),'0x00667AD8':(132,104)}
EXTERNAL={'??0exception@@QAE@ABV0@@Z':'0x00640C9A','??0exception@@QAE@XZ':'0x00640C4C',
 '??1exception@@UAE@XZ':'0x00640CE4','??2@YAPAXI@Z':'0x0064159D','??3@YAXPAX@Z':'0x00640F15',
 '??DOrdinaryListArrowObservation@@QBEAAUListValueObservation@@XZ':'0x004121E0',
 '??EOrdinaryListIteratorObservation@@QAEAAU0@XZ':'0x00412200','??_7type_info@@6B@':'0x00660EDC',
 '??_Elength_error@std@@UAEPAXI@Z':'0x00404C70','??_Elogic_error@std@@UAEPAXI@Z':'0x00404BC0',
 '?_Xlen@_String_base@std@@QBEXXZ':'0x00654B0E','?_Xran@_String_base@std@@QBEXXZ':'0x00654ACE',
 '__CxxThrowException@8':'0x00640C12','___CxxFrameHandler':'0x006407B8','__except_list':'0x00000000',
 '_memcpy':'0x00640F20','_memmove':'0x00641260','_strlen':'0x00640620'}


def manifest():return json.loads((ROOT/EVIDENCE).read_text())


def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        text=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if text[:3].lower()!='z:/':raise ValueError('iterator include loses its actual host mapping')
        path=Path(text[2:]);relative=str(path.relative_to(ROOT))
        if relative not in ('probes/VC7GameContextPolicies.cpp','probes/VC7ListPolicyDependencies.cpp') and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('iterator gains an unreviewed include owner')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if (m['evidence_id']!='R168' or m['target_sha256']!=SDK.manifest()['target_sha256']
            or m['probe']!='probes/VC7ListIteratorPolicies.cpp' or m['profile']!=SDK.PROFILE or len(m['headers'])!=31
            or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=19
            or len(m['controls'])!=93 or sum(r['size'] for r in m['controls'])!=4248
            or sum(len(r['bindings']) for r in m['controls'])!=210 or len(m['emission'])!=225
            or sum(r['size'] for r in m['emission'])!=10007 or len(m['snapshots'])!=182 or len(m['retained'])!=16
            or m['external']!=EXTERNAL or m['layout'] not in m['emission'] or m['layout']['size']!=76 or m['layout_values']!=LAYOUT):
        raise ValueError('iterator loses complete bounded functions, fields, ordinary emission or layout')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];allowed=mutable|({'size','span_end'} if a=='0x00412240' else set())
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a
                or int(old['size'])!=(137 if a=='0x00412240' else r['size'])
                or {k:v for k,v in old.items() if k not in allowed}!={k:v for k,v in new.items() if k not in allowed}
                or new['size']!=str(r['size']) or new['span_end']!=f'0x{int(a,16)+r["size"]-1:08X}'
                or new['module']!='VC7STL' or new['owner']!='library' or new['status']!='excluded'
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R168')):
            raise ValueError('iterator alters unrelated boundary or grants false source/private ABI/mapping/exact credit')
        control=next(x for x in m['controls'] if x['address']==a)
        if r['symbol']!=control['source_definition']['symbol'] or r['cfg']!=control['cfg'] or r['body_sha256']!=control['body_sha256'] or not r['witnesses'] or 'Ordinary' in r['symbol']:
            raise ValueError('iterator substitutes genuine full defining SDK source/CFG with a short shape')
    if [r['address'] for r in m['controls'][:7]]!=list(KEYS)[:7]:raise ValueError('iterator loses all seven original complete SDK roots')
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition']
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])
                or r['role']!=('byte-equal-ordinary-alternative' if i>=90 else 'closed-whole-sdk-context')):
            raise ValueError('iterator truncates an entire defining code/data carrier or ordinary alternative')
        if r['kind']=='code' and (d['offset'] or d['type']!=32 or d['storage']!=2):raise ValueError('iterator loses own complete regular definition')
        if r['kind']=='eh-code' and EH.get(r['address'])!=(r['size'],d['offset']):raise ValueError('iterator slices cleanup/handler shared tail')
        if r['address'] in STATE and (r['kind']!='state-data' or STATE[r['address']]!=(r['size'],d['offset'])):
            raise ValueError('iterator slices complete EH/state/try metadata')
        for field,b in zip(ss['fields'],r['bindings']):
            if (b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address'])
                    or field['type'] not in ('REL32','DIR32') or field['offset']+4>r['size']):
                raise ValueError('iterator masks, substitutes or drops a real field')
    ordinary=m['controls'][90:]
    if [(r['address'],r['size']) for r in ordinary]!=[('0x00411CE0',17),('0x00411E00',19),('0x00411E20',42)] or any('Ordinary' not in r['source_definition']['symbol'] for r in ordinary):
        raise ValueError('iterator loses entire distinct size/arrow/postincrement alternatives')
    if [[b['target_address'] for b in r['bindings']] for r in ordinary]!=[[],['0x004121E0'],['0x00412200']]:
        raise ValueError('iterator ordinary field substitutes the actual operation')
    buy=next(r for r in m['controls'] if r['address']=='0x00412240');catch=[d for d in buy['section']['definitions'] if d['type']==32 and d['storage']==3]
    if len(catch)!=1 or catch[0]['offset']!=137 or not catch[0]['symbol'].startswith('$L'):
        raise ValueError('iterator value-node allocation loses complete local catch/shared tail')
    state=next(r for r in m['controls'] if r['address']=='0x006681E4')
    if not any(b['target_address']=='0x004122C9' for b in state['bindings']):raise ValueError('iterator loses actual catch-table linkage')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('iterator resolves an independently opaque getter/destruction/catch/lifetime/copy/math owner')
    if {r['address']:r['size'] for r in m['anchors']}!={'0x00411000':183,'0x00411110':746} or any(r['origin']['origin']!='authored' or r['origin']['evidence_id']!='R035' or r['record']['evidence_id']!='R035' for r in m['anchors']):
        raise ValueError('iterator loses full independent authored game policies')
    if {r['handler_address'] for r in m['retained_frames']}!={f'0x{int(a,16)+off:08X}' for a,(size,off) in EH.items()} or len(m['retained_frames'])!=6:
        raise ValueError('iterator loses original registered exception frames')
    definitions=sorted([(d['symbol'],d['offset']) for d in m['layout']['definitions'] if d['storage']==2],key=lambda d:d[1])
    if definitions!=[('_GameContextLayout',0),('_ListDependencyLayout',36),('_ListIteratorLayout',56),('_OrdinaryListIteratorLayout',64)]:
        raise ValueError('iterator slices one of the four complete observer arrays')
    slot=m['selected_slot']
    if slot!=dict(address='0x00660EDC',size=4,body_sha256=slot['body_sha256']):raise ValueError('iterator expands a selected type-info slot into a whole vtable claim')


def accepted_snapshot(snapshot,function,origin):
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('iterator immutable manifest differs')
    m=manifest();verify_plan(m);r=next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin'])
                and function==r['accepted_function'] and origin==r['accepted_origin'])


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('iterator immutable source/prior evidence differs: '+path)
    c=module('iterator_target','compare-coff-function.py');coff=module('iterator_coff','coff_data.py');cfg=module('iterator_cfg','verify-authored-origins.py')
    extent=module('iterator_extent','verify-vendor-record-origins.py');eh=module('iterator_eh','compiler_eh.py');target=c.verified_target();rows=cfg.rows
    if digest(target)!=m['target_sha256']:raise ValueError('iterator target identity differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']}
    if any(r['evidence_id']=='R168' for r in authored.values()):raise ValueError('iterator adds false authored extent credit')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witnesses(body,address):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,address)]
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);body=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg'] or witnesses(body,int(a,16))!=r['witnesses']:
            raise ValueError('iterator entire accepted extent/CFG/instructions differ')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('iterator changes unrelated original canonical record')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('iterator original complete body snapshot differs')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r.get('collection','functions')] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('iterator original full source/runtime record differs')
    for r in m['anchors']:
        a=r['address'];body=c.pe_bytes_at(target,int(a,16),r['size'])
        if functions[a]!=r['function'] or origins[a]!=r['origin'] or authored[a]!=r['record'] or digest(body)!=r['record']['body_sha256'] or witnesses(body,int(a,16))!=r['witnesses']:
            raise ValueError('iterator original full authored-parent evidence differs')
        for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [x for x in rows(filename) if x['address']==a]!=r[key]:raise ValueError('iterator original parent switch evidence differs')
        counts=cfg.verify_body(body,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches'])
        if counts!=(int(r['record']['return_count']),int(r['record']['internal_branch_count'])):raise ValueError('iterator complete game policy CFG differs')
    for frame in m['retained_frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('iterator original EH registration differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions},set())
    slot=m['selected_slot'];sections=module('iterator_sections','verify-compiler-origins.py').sections(target)
    if digest(c.pe_bytes_at(target,int(slot['address'],16),4))!=slot['body_sha256'] or not any(base<=int(slot['address'],16) and int(slot['address'],16)+4<=base+size and flags&0x40000000 and not flags&0xA0000000 for base,size,flags in sections):
        raise ValueError('iterator selected readonly type-info slot differs')
    scratch=ROOT/'build/origin-list-iterator-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'ListIteratorPolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('iterator cold source/actual include ownership differs')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('iterator full ordinary code/EH/RTTI/data emission differs')
        catalog={}
        def add(name,address):
            if name in catalog and catalog[name]!=address:raise ValueError('iterator overrides a coherent complete defining SDK/ordinary symbol')
            catalog[name]=address
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):add(d['symbol'],int(r['address'],16)+d['offset'])
        for r in m['controls']:
            for b in r['bindings']:
                name,a=b['symbol'],b['target_address']
                if name not in catalog and EXTERNAL.get(name)!=a:raise ValueError('iterator external field loses its independent complete code/selected-data boundary')
                add(name,int(a,16))
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:
                raise ValueError('iterator entire unmasked comparison differs: '+r['address'])
            if r['kind']=='code':
                if r['address'] in ('0x00405340','0x00405370'):PRIOR.PRIOR.verify_implicit_extent(r,data,c.coff_name)
                elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:
                    raise ValueError('iterator regular positive loses complete primary AUX extent')
                if list(cfg.verify_body(actual,int(r['address'],16)))!=r['cfg']:raise ValueError('iterator entire positive CFG differs')
            elif r['kind']=='eh-code':
                ins=list(decoder.disasm(actual,int(r['address'],16)))
                if sum(x.size for x in ins)!=r['size'] or ins[-1].mnemonic!='jmp' or ins[-1].op_str!='0x6407b8':raise ValueError('iterator slices actual cleanup/handler carrier')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<19I',raw))!=LAYOUT:raise ValueError('iterator complete combined layout differs')
    print('R168 origins OK: nineteen complete SDK list iterator/insert/erase dependencies / 1097 bytes; full 189-byte value-node allocation includes local catch and shared tail; unchanged full R035 game policies / 929 bytes; 93 entire positive source/code/EH/throw/RTTI/data controls / 4248 bytes and 210 genuine unmasked fields, including three byte-equal ordinary controls / 78 bytes; all 225 cold ordinary sections / 10007 bytes, 29 SDK headers plus two pinned prior probe includes and whole 76-byte layout; six original registered frames, existing compiler/runtime/library classifications and all protected opaque getters/destruction/catch/lifetime/copy/math owners preserved; original payload/private game layout and method spelling unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
