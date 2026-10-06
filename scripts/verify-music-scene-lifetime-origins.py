#!/usr/bin/env python3
"""Cold-replay whole music scene/record policies and preserve real allocation-route differences."""
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
BASE=module('music_lifetime_common','verify-scene-texture-cleanup-origins.py')
SOURCE=BASE.SOURCE
HEADERS=BASE.HEADERS
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
bind=BASE.bind
EVIDENCE='config/music-scene-lifetime-origin-evidence.json'
MANIFEST_SHA256='3585911a97c2dfb713892494cfb5a7c0b3549bd215f326b3425e24acaa74c09e'
PLAN_DIGESTS={'evidence_id': 'f2b1529c69cccc83f1d910e5b179d33d61907c3496a6154ce0857a45ac1358e9', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '302af430520eb1aaa86156a88a07f900ab8d9974d65933d4b23d78cdb42c6183', 'context': 'c7b1a1a4d9dd7b6b85619aab457b19c0b95c4c7bdb948f5b34126096116824cd', 'anchors': 'f832c8f92f7ab248887796f87daa5c3f00ccd81afff512e8e36e716096726529', 'canonical': '096362b5e42d39caf9026907af6eefd79bef20823d3fe9487e3479d6da59acf2', 'unselected_sha256': '7cc33f1479f5364598ae95627129d2d73bb9fb852f75c6ed5cd4c3f6f654e214', 'public_control': 'f181668920c195c0e2daf127ee476c169cdd91a688a80cdf7a5eb9797c2283ac', 'cold_dependencies': '629c8bf6d6628db86532011819bf1b744b9d23faa278cc4c6f907e8f2f518983', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': '1b249b65f3ce0e4242838813267e537920d87ce6f173cd9ba9cdbba6826d2c50', 'interpretation': '50ba5ab254c9e2ae3860ae45120b32f6f0ce9900f04916be18a31ac17157833f'}
WHOLE={'0x004258D0':244,'0x00427430':50,'0x00427470':82}
CONFIDENCE='whole-game-music-scene-record-policy-with-independent-catalog-render-array-and-source-lifetime-context'


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Music lifetime immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Music lifetime complete immutable evidence differs: '+k)
    if (m['evidence_id']!='R236' or {r['address']:r['size'] for r in m['functions']}!=WHOLE
            or m['historical_snapshots'] or len(m['public_control']['comparisons'])!=7):
        raise ValueError('Music lifetime bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem=new['module'],
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R236')):
            raise ValueError('Music lifetime gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Music lifetime original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Music lifetime scoped canonical ownership differs: '+a)


def require(instructions,expected):
    by={i['offset']:(i['mnemonic'],i['operands']) for i in instructions}
    if any(by.get(at)!=pair for at,pair in expected.items()):raise ValueError('Music lifetime independent whole owner/array/catalog witness differs')


def verify_native(m,target,c,flow):
    auth=module('music_native_cfg','verify-authored-origins.py');permissions=module('music_permissions','verify-sdk-x3d-origins.py');native={};records={r['address']:r for r in m['functions']+m['anchors']}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);native[a]=raw
        if r.get('kind')=='whole-mixed-vendor-code-data':
            if (a!='0x00640F20' or r['size']!=829 or r['cfg'] is not None or r['instructions'] is not None
                    or r['source_record'] not in rows('runtime-local-evidence.csv') or digest(raw)!=r['body_sha256']):
                raise ValueError('Music lifetime crops the complete mixed memcpy code/table carrier')
            module('music_local_vendor','verify-runtime-local-origins.py').main()
            continue
        if a in ['0x00640F15','0x0064169D','0x006416A2']:
            cfg=flow.flow(raw,at,[0],[],{at+1:r['tail_destination']},{})
        else:cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,at,flow)!=r['instructions'] or cfg!=r['cfg']:
            raise ValueError('Music lifetime whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Music lifetime original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Music lifetime full original switch records differ')
    ctx=m['context']
    require(records['0x00425750']['instructions'],{48:('mov','dword ptr [eax], 0x657cb0'),
        54:('push','0x427470'),59:('push','0x427430'),64:('push','0x3c'),66:('push','0x10'),
        71:('add','ecx, 0x1c'),75:('call','0x641c78'),143:('mov','dword ptr [eax + 8], ecx'),
        175:('call','0x40bb80'),199:('call','0x401c20'),226:('call','0x401c20'),
        250:('call','0x401c20'),274:('call','0x401c20'),305:('call','0x426dd0')})
    require(records['0x004258D0']['instructions'],{170:('call','0x407d70'),175:('push','0x28'),
        177:('call','0x419cb0'),185:('call','0x419df0'),194:('push','0x427470'),
        199:('push','0x3c'),201:('push','0x10'),206:('add','ecx, 0x1c'),210:('call','0x641d4a')})
    require(records['0x00641C78']['instructions'],{26:('cmp','eax, dword ptr [ebp + 0x10]'),
        36:('call','dword ptr [ebp + 0x14]'),39:('add','esi, dword ptr [ebp + 0xc]'),71:('ret','0x14')})
    require(records['0x00641D4A']['instructions'],{16:('mov','esi, dword ptr [ebp + 0xc]'),
        21:('imul','eax, dword ptr [ebp + 0x10]'),40:('mov','ecx, dword ptr [ebp + 8]'),
        43:('call','dword ptr [ebp + 0x14]'),69:('ret','0x10')})
    require(records['0x00426DD0']['instructions'],{501:('shl','eax, 4'),510:('mov','dword ptr [ecx + eax + 0x24], edx'),
        583:('mov','byte ptr [edx + ecx], 0'),623:('shl','ecx, 4'),632:('mov','dword ptr [edx + ecx + 0x20], eax'),
        705:('mov','byte ptr [eax + edx], 0'),745:('shl','edx, 4'),754:('mov','dword ptr [eax + edx + 0x28], ecx'),
        480:('call','0x6416a2'),602:('call','0x6416a2'),724:('call','0x6416a2'),
        549:('call','0x640f20'),671:('call','0x640f20'),793:('call','0x640f20')})
    for a,witnesses in ctx['renderer_witnesses'].items():require(records[a]['instructions'],{int(k):tuple(v) for k,v in witnesses.items()})
    for r in ctx['strings']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if (digest(raw)!=r['sha256'] or raw[:-1].decode('cp932')!=r['text'] or raw[-1:]!=b'\0'
                or permissions.image_permissions(target,a,r['size'])!=0x40000000):raise ValueError('Music lifetime complete real game asset/catalog string differs')
    table=ctx['table'];a=int(table['address'],16);raw=c.pe_bytes_at(target,a,12)
    if (digest(raw)!=table['sha256'] or list(struct.unpack('<3I',raw))!=table['words']
            or digest(c.pe_bytes_at(target,a+12,4))!=table['following_sha256'] or permissions.image_permissions(target,a,12)!=0x40000000):
        raise ValueError('Music lifetime actual observed table/next data differs')
    deleting=table['words'][0]
    if deleting+15+struct.unpack_from('<i',native[f'0x{deleting:08X}'],11)[0]!=0x4258d0:
        raise ValueError('Music lifetime actual paired deleting table slot differs')
    for r in ctx['exception_parts']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if digest(raw)!=r['sha256'] or permissions.image_permissions(target,a,r['size'])!=r['permissions']:
            raise ValueError('Music lifetime complete two-state EH carrier differs')
        if 'instructions' in r and SOURCE.instructions(raw,a,flow)!=r['instructions']:raise ValueError('Music lifetime full EH instructions differ')
        if 'following_sha256' in r and digest(c.pe_bytes_at(target,a+r['size'],8))!=r['following_sha256']:
            raise ValueError('Music lifetime claims adjacent next-owner EH data')
    for r in ctx['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Music lifetime claims external alignment')


def compare_alternative(r,linked,actual,fields,target,c,flow):
    """Compare all bytes; scalar source calls keep their real scalar owner."""
    if len(linked)!=82 or len(actual)!=82 or r['address']!='0x00427470':raise ValueError('Music record full alternative extent differs')
    if [(f['offset'],f['type'],f['symbol'],f['addend']) for f in fields]!=[(o,'REL32','??3@YAXPAX@Z',0) for o in [29,50,71]]:
        raise ValueError('Music record scalar source declaration/fields differ')
    if any(b['target']!='0x00640F15' for b in r['bindings']):raise ValueError('Music record falsely binds scalar source to array-delete owner')
    actual_calls=[i for i in SOURCE.instructions(actual,0x427470,flow) if i['mnemonic']=='call']
    if [(i['offset'],i['operands']) for i in actual_calls]!=[(28,'0x64169d'),(49,'0x64169d'),(70,'0x64169d')]:
        raise ValueError('Music record actual complete array-delete routes differ')
    array=c.pe_bytes_at(target,0x64169d,5);scalar=c.pe_bytes_at(target,0x640f15,5)
    if (array[:1]!=b'\xe9' or 0x64169d+5+struct.unpack_from('<i',array,1)[0]!=0x640f15
            or scalar[:1]!=b'\xe9' or 0x640f15+5+struct.unpack_from('<i',scalar,1)[0]!=0x642a61):
        raise ValueError('Music record actual complete array/scalar/free owners differ')
    differences=[dict(offset=i,source=x,target=y) for i,(x,y) in enumerate(zip(linked,actual)) if x!=y]
    if differences!=r['differences'] or len(differences)!=6:
        raise ValueError('Music record masks/crops/corrects the six genuine deallocator-route byte differences')


def verify_control(m,body,target,c,coff,flow):
    extra=module('music_source_carrier','sdk_x3d_carriers.py');inventory=module('music_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('music_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Music lifetime full code/data/AUX/field emission differs')
    for r in ctl['weak_references']:
        if weak.read_weak_reference(body,r['symbol'],c,coff,0)!=r:raise ValueError('Music lifetime real weak alias/AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Music lifetime whole source/COFF/AUX differs')
        if 'instructions' in r and SOURCE.instructions(raw,0,flow)!=r['instructions']:raise ValueError('Music lifetime full natural instructions differ')
        sections[r['section']]=(raw,fields)
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];a=int(r['address'],16);linked,proof=bind(raw,fields,a,r['bindings'],flow,r['roots']);actual=c.pe_bytes_at(target,a,r['size'])
        if len(linked)!=r['size'] or proof!=r['linked_flow']:raise ValueError('Music lifetime whole ordinary entry/call/data flow differs')
        if r['role']=='scalar-array-delete-route-alternative':compare_alternative(r,linked,actual,fields,target,c,flow)
        elif r['role']=='whole-byte-equal' and linked==actual:pass
        else:raise ValueError('Music lifetime whole unmasked positive comparison differs')
    methods={d['symbol']:r['size'] for r in ctl['sections'] for d in r['source']['definitions'] if d['type']==32}
    if any(methods[k]!=n for k,n in ctl['alternatives'].items()) or sorted(ctl['alternatives'].values())!=[5,19,50,82,244]:
        raise ValueError('Music lifetime complete genuine implicit/ordinary alternatives differ')
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:
            raise ValueError('Music lifetime natural compact observation gains private padding')


def replay(m,evidence_only=False):
    c=module('music_target','compare-coff-function.py');coff=module('music_coff','coff_data.py');flow=module('music_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Music lifetime target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Music lifetime retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for script in m['cold_dependencies']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Music lifetime full retained source/callback/allocation/texture proof failed: '+script+'\n'+result.stderr[-1500:])
    ctl=m['public_control'];scratch=ROOT/'build/origin-music-scene-lifetime-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'MusicSceneLifetime.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or HEADERS(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Music lifetime cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Music lifetime immutable manifest differs')
    replay(m,args.evidence_only)
    print('R236:three whole music scene/record origins376; complete independent catalog/render/audio/texture and CRT array60x16 owners; full cold natural244/50 and normal/EH/deleting controls; actual six record-deallocation route bytes retained; implicit alternatives distinct; no original private layout/source/ABI or exact credit.')

if __name__=='__main__':main()
