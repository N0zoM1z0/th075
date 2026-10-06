#!/usr/bin/env python3
"""Cold-replay complete scene resource cleanup and independent paired lifetime owners."""
import argparse
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import importlib.util

ROOT=Path(__file__).resolve().parents[1]
def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    value=importlib.util.module_from_spec(spec);spec.loader.exec_module(value);return value
BASE=module('cleanup_common','verify-scene-shared-value-origins.py')
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/scene-resource-cleanup-origin-evidence.json'
MANIFEST_SHA256='63e3d06ca902c40cfe7fa767639ba697f5705bb4bd048494adac7cab3157ceec'
PLAN_DIGESTS={'evidence_id': 'dc1928af76941eeee0e59e1e7c6a8ee0b2a2b17a49ac2194464af25ac941f29a', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '36ba686cfe18422c53576970329bc1ea0edf38a59f138d958f5ba4b3abb629ca', 'contexts': '2209dcbc703485fbd5a4e87f22089fb126ec6684c36c35924aa297c82620877a', 'anchors': '14971ac0b560d980a0b7ebb341d3c98e95d430794e27580bc1c44a277e2a20b7', 'canonical': '7e84d5d6bc3355fafee93255f68ce73e3cc9303a17f6272f066749eb06535f77', 'unselected_sha256': '403a09fb6a4706f91a8c39a8f3706b5b007f110fb25bbb8c257200c7db9f0219', 'public_control': 'cd2779173922da1b7362a5991e9620af0508d9c76dbd891e49a2223eefb4040e', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': 'c7ef853f34224e4e8de412266e3094522cdb3df7fe100cacfd441c1b10217b48', 'interpretation': 'f37fd531aadee5dc534c493f1e434a59218e24a3370b42e62fb33576e9599ab3'}
WHOLE={f'0x{a:08X}':127 for a in [0x4252b0,0x425550,0x42a2c0,0x42b300,0x42e870]}
CONFIDENCE='whole-game-scene-resource-policy-with-independent-asset-initializer-and-complete-natural-lifetime-graph'


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Scene cleanup immutable schema differs')
    for k,sha in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=sha:raise ValueError('Scene cleanup complete immutable evidence differs: '+k)
    if (m['evidence_id']!='R234' or {r['address']:r['size'] for r in m['functions']}!=WHOLE
            or len(m['contexts'])!=5 or m['historical_snapshots']):raise ValueError('Scene cleanup bounded scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem=new['module'],
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R234')):
            raise ValueError('Scene cleanup assigns unsupported original source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    selected={r['address']:r for r in m['functions']};fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Scene cleanup original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Scene cleanup scoped ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('cleanup_auth','verify-authored-origins.py');permissions=module('cleanup_permissions','verify-sdk-x3d-origins.py')
    native={}
    for r in m['functions']+m['anchors']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size']);native[r['address']]=raw
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or (flow.flow(raw,a,[0],[],{a+1:0x642a61},{}) if a==0x640f15 else list(auth.verify_body(raw,a,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches'])))!=r['cfg']):
            raise ValueError('Scene cleanup complete game/compiler/runtime owner or CFG differs: '+r['address'])
        if r.get('authored_record') and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Scene cleanup independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==r['address']]!=r[key]:raise ValueError('Scene cleanup original complete switch records differ')
    for ctx in m['contexts']:
        ctor=next(r for r in m['anchors'] if r['address']==ctx['constructor']);root=next(r for r in m['functions'] if r['address']==ctx['cleanup'])
        by={i['offset']:(i['mnemonic'],i['operands']) for i in ctor['instructions']}
        if (by.get(48)!=('mov',f"dword ptr [eax], {hex(int(ctx['table']['address'],16))}")
                or by.get(113)!=('mov','dword ptr [edx + 8], eax')
                or by.get(145)!=('call','0x40bb80')):
            raise ValueError('Scene cleanup loses independent same-table/field/asset initialization')
        if ctor['authored_record'] is None:raise ValueError('Scene cleanup initializer is not independently authored')
        for s in ctx['strings']:
            raw=c.pe_bytes_at(target,int(s['address'],16),s['size'])
            if (digest(raw)!=s['sha256'] or raw[:-1].decode('cp932')!=s['text'] or raw[-1: ]!=b'\0'
                    or permissions.image_permissions(target,int(s['address'],16),s['size'])!=0x40000000):
                raise ValueError('Scene cleanup actual full readonly game asset string differs')
        table=ctx['table'];a=int(table['address'],16);raw=c.pe_bytes_at(target,a,12)
        if (digest(raw)!=table['sha256'] or list(struct.unpack('<3I',raw))!=table['words']
                or digest(c.pe_bytes_at(target,a+12,4))!=table['following_sha256']
                or permissions.image_permissions(target,a,12)!=0x40000000):
            raise ValueError('Scene cleanup loses observed paired readonly table slots')
        deleting=next(r for r in m['anchors'] if int(r['address'],16)==table['words'][0])
        if (int(deleting['address'],16)+15+struct.unpack_from('<i',native[deleting['address']],11)[0]!=int(root['address'],16)):
            raise ValueError('Scene cleanup paired deleting table slot does not bind the whole destructor')
        for part in ctx['exception_parts']:
            a=int(part['address'],16);raw=c.pe_bytes_at(target,a,part['size'])
            if digest(raw)!=part['sha256'] or permissions.image_permissions(target,a,part['size'])!=part['permissions']:
                raise ValueError('Scene cleanup full handler/unwind/FuncInfo extent differs')
            if 'instructions' in part and SOURCE.instructions(raw,a,flow)!=part['instructions']:
                raise ValueError('Scene cleanup complete original exception instructions differ')
            if 'following_sha256' in part and digest(c.pe_bytes_at(target,a+part['size'],8))!=part['following_sha256']:
                raise ValueError('Scene cleanup claims adjacent next-owner unwind data')
        for b in ctx['boundaries']:
            raw=c.pe_bytes_at(target,int(b['address'],16),b['size'])
            if raw!=b'\xcc'*b['size'] or digest(raw)!=b['sha256']:raise ValueError('Scene cleanup claims external INT3 alignment')


def bind(raw,fields,address,bindings,flow,roots):
    linked=bytearray(raw);calls={};data={}
    if [f['offset'] for f in fields]!=[b['offset'] for b in bindings]:raise ValueError('Scene cleanup omits an actual source relocation')
    for f,b in zip(fields,bindings):
        if f['type']!=b['type'] or f['symbol']!=b['symbol'] or f['addend']!=0:
            raise ValueError('Scene cleanup replaces actual complete source field/addend')
        destination=int(b['target'],16);encoded=destination
        if f['type']=='REL32':encoded=destination-(address+f['offset']+4);calls[address+f['offset']]=destination
        elif f['type']=='DIR32':data[address+f['offset']]=destination
        else:raise ValueError('Scene cleanup unsupported field type')
        struct.pack_into('<I',linked,f['offset'],encoded&0xffffffff)
    return linked,flow.flow(linked,address,roots,fields,calls,data) if roots else None


def verify_control(m,body,target,c,coff,flow):
    extra=module('cleanup_carrier','sdk_x3d_carriers.py');inventory=module('cleanup_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Scene cleanup whole ordinary code/data/AUX/field emission differs')
    weak=module('cleanup_weak','verify-standard-exception-origins.py')
    for r in ctl['weak_references']:
        if weak.read_weak_reference(body,r['symbol'],c,coff,0)!=r:
            raise ValueError('Scene cleanup replaces actual whole weak AUX/deleting fallback')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Scene cleanup full natural source/COFF/AUX differs')
        if 'instructions' in r and SOURCE.instructions(raw,0,flow)!=r['instructions']:
            raise ValueError('Scene cleanup ordinary complete instructions differ')
        sections[r['section']]=(raw,fields)
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];a=int(r['address'],16);linked,proof=bind(raw,fields,a,r['bindings'],flow,r['roots'])
        if (len(linked)!=r['size'] or linked!=c.pe_bytes_at(target,a,r['size']) or proof!=r['linked_flow']):
            raise ValueError('Scene cleanup complete unmasked natural/native code/data/flow differs')
    code={d['symbol']:r for r in ctl['sections'] for d in r['source']['definitions'] if d['type']==32}
    sizes={k:code[k]['size'] for k in ctl['alternatives']}
    if sizes!=ctl['alternatives'] or sorted(sizes.values())!=[19,63,75,127]:
        raise ValueError('Scene cleanup loses raw-pointer and owned-member implicit alternatives')
    layout=ctl['layout_section'];raw=sections[layout][0]
    if len(raw)!=16 or list(struct.unpack('<4I',raw))!=[1,8,12,12]:
        raise ValueError('Scene cleanup compact complete observations become a padded private owner')


def replay(m,evidence_only=False):
    c=module('cleanup_target','compare-coff-function.py');coff=module('cleanup_coff','coff_data.py');flow=module('cleanup_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Scene cleanup target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Scene cleanup retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    ctl=m['public_control'];scratch=ROOT/'build/origin-scene-resource-cleanup-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'SceneResourceCleanup.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or SOURCE.HEADERS(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Scene cleanup cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Scene cleanup immutable manifest differs')
    replay(m,args.evidence_only)
    print('R234:five whole game cleanup policies635; independent paired initializers, observed tables and whole resource/base/deleting/runtime owners; full cold127/44/18/36 code/EH comparisons and genuine implicit lifetime alternatives; original private layout/source/ABI unknown, no exact credit.')

if __name__=='__main__':main()
