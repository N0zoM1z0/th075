#!/usr/bin/env python3
"""Cold-replay whole archive catalog first-user policy and genuine source alternatives."""
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
BASE=module('catalog_common','verify-music-scene-lifetime-origins.py')
SOURCE=BASE.SOURCE
HEADERS=BASE.HEADERS
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
bind=BASE.bind
EVIDENCE='config/archive-catalog-use-origin-evidence.json'
MANIFEST_SHA256='33292559e16ded74fa505961ada05d361ccca98edf9a2310a3f6edae52249e2c'
PLAN_DIGESTS={'evidence_id': '06808e7a29cf2028d846c1223a9284ef2a03f99312b1c013ed27cc374728a64c', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'bb3b114bc7269c753744bb29a0c80994ff54f911ef2ffe5719148e72a64afaf8', 'anchors': 'da7996c8f2c458e3bf1f11bf883454fc556cb37b51d19a5bc0d5e83e9d03073d', 'context': '819632a357c4b9ffda7ecda0e3b9f2c364a6bfc1745023684fa7910230038c0e', 'canonical': '9a3d2798cd33168c69775788d4628284368fd59d2ab606d124e19842291f5906', 'unselected_sha256': '2a8a9f72110012d85935b446c2976066fbe4e3f222ad03beed9228e11fe24520', 'public_control': '4af8a14cd9707519851bb923d1c8b0cb729391243d8cc110440fa3a02319ddc6', 'cold_dependencies': 'b670829e7ebee2a825b0ea118a9f444596e8d6637f98aa0dbe818d1e0a1927ce', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': '6671b8e88ee8fc53d863c03c50123d642335c3e57ba04f85af83939643e87e5e', 'interpretation': '796413eed428c96d4c191be87ced2997eedd675a704caa71aba71c586d987265'}
WHOLE={'0x0041CE10':56}
CONFIDENCE='whole-first-user-archive-catalog-policy-with-independent-named-file-and-paired-count-container-context'


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Catalog use immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Catalog use complete immutable evidence differs: '+k)
    if (m['evidence_id']!='R237' or {r['address']:r['size'] for r in m['functions']}!=WHOLE
            or m['historical_snapshots'] or len(m['public_control']['comparisons'])!=8):
        raise ValueError('Catalog use bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='ArchiveCatalog',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R237')):
            raise ValueError('Catalog use gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Catalog use original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Catalog use scoped canonical ownership differs: '+a)


def virtual_storage(target,address,size):
    """Observe PE virtual storage without fabricating file-backed BSS bytes."""
    pe=struct.unpack_from('<I',target,0x3c)[0]
    count=struct.unpack_from('<H',target,pe+6)[0];optional=struct.unpack_from('<H',target,pe+20)[0]
    image_base=struct.unpack_from('<I',target,pe+24+28)[0]
    for i in range(count):
        at=pe+24+optional+40*i;h=struct.unpack_from('<8sIIIIIIHHI',target,at)
        base=image_base+h[2]
        if base<=address and address+size<=base+h[1]:
            return dict(section=h[0].rstrip(b'\0').decode('ascii'),section_header_sha256=digest(target[at:at+40]),
                base=f'0x{base:08X}',virtual_size=h[1],raw_size=h[3],raw_offset=h[4],
                permissions=h[9]&0xe0000000,address=f'0x{address:08X}',size=size,
                file_backed=address+size<=base+min(h[1],h[3]))
    raise ValueError('Catalog shared storage is outside a complete PE virtual section')


def verify_native(m,target,c,flow):
    auth=module('catalog_native_cfg','verify-authored-origins.py');permissions=module('catalog_permissions','verify-sdk-x3d-origins.py');records={r['address']:r for r in m['functions']+m['anchors']}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size'])
        if a in ['0x00640F15','0x0064169D']:
            cfg=flow.flow(raw,at,[0],[],{at+1:r['tail_destination']},{})
        else:cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,at,flow)!=r['instructions'] or cfg!=r['cfg']:
            raise ValueError('Catalog use whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Catalog use original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Catalog use full original switch records differ')
    for a,witnesses in m['context']['witnesses'].items():
        BASE.require(records[a]['instructions'],{int(k):tuple(v) for k,v in witnesses.items()})
    storage=virtual_storage(target,0x68be04,44)
    if storage!=m['context']['storage'] or storage['permissions']!=0xc0000000:
        raise ValueError('Catalog use observes non-writable shared storage')
    imports=module('catalog_imports','verify-import-origins.py').pe_imports(target,c)
    for r in m['context']['imports']:
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('Catalog use actual complete PE import identity differs')
    for r in m['context']['strings']:
        at=int(r['address'],16);raw=c.pe_bytes_at(target,at,r['size'])
        if (digest(raw)!=r['sha256'] or raw[:-1].decode('cp932')!=r['text'] or raw[-1:]!=b'\0'
                or permissions.image_permissions(target,at,r['size'])!=0x40000000):
            raise ValueError('Catalog use complete real archive path/name string differs')
    for r in m['context']['header_definitions']:
        raw=(ROOT/r['path']).read_bytes();lines=raw.decode('ascii').splitlines(keepends=True)
        if digest(raw)!=r['whole_sha256'] or ''.join(lines[r['start']-1:r['end']])!=r['text']:
            raise ValueError('Catalog use original whole header/member definition differs')
    for r in m['context']['vendor_records']:
        if r['record'] not in rows(r['path']):raise ValueError('Catalog use changes original typed deque-family evidence')
    for r in m['context']['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Catalog use claims external alignment')


def verify_source_owner(r,fields):
    basis=r['independent_vendor_record']
    if basis is None:
        if r['size']!=56 or r['address']!='0x0041CE10' or len(fields)!=7:
            raise ValueError('Catalog use crops the whole ordinary/template policy')
        if [b['target'] for b in r['bindings']]!=['0x0068BE04','0x0068BE08','0x0041DCD0','0x0068BE1C','0x0041DF50','0x0068BE04','0x0068BE04']:
            raise ValueError('Catalog use breaks actual paired count/receiver ownership')
        if [f['offset'] for f in fields]!=[9,17,22,27,32,37,45]:
            raise ValueError('Catalog use actual complete seven source fields differ')
        call_fields=[f for f in fields if f['type']=='REL32']
        if len(call_fields)!=2 or any(not f['symbol'].startswith('?clear@?$deque@') for f in call_fields):
            raise ValueError('Catalog use relabels public clear as a private destructor')
        return
    if r['address']!=basis['address'] or str(r['size'])!=basis['size']:
        raise ValueError('Catalog use rewrites a complete existing vendor extent')
    old=json.loads(basis['relocation_bindings'])
    if len(old)!=len(fields) or len(fields)!=len(r['bindings']):raise ValueError('Catalog use omits an actual typed vendor field')
    for f,o,b in zip(fields,old,r['bindings']):
        if ((f['offset'],f['type'],f['addend'],f['symbol'].split('@',1)[0])
                !=(o['offset'],o['type'],o['addend'],o['symbol'].split('@',1)[0])
                or b['target']!=o['target_address']):
            raise ValueError('Catalog use typed source descendant ownership differs')
    if r['size']==19:
        if (len(fields)!=1 or not fields[0]['symbol'].startswith('?_Tidy@?$deque@')
                or basis['callee_address']!=r['bindings'][0]['target']):
            raise ValueError('Catalog use false clear/destructor to Tidy binding')


def verify_control(m,body,target,c,coff,flow):
    extra=module('catalog_source_carrier','sdk_x3d_carriers.py');inventory=module('catalog_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('catalog_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Catalog use full code/data/AUX/field emission differs')
    for r in ctl['weak_references']:
        if weak.read_weak_reference(body,r['symbol'],c,coff,0)!=r:raise ValueError('Catalog use real weak alias/AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Catalog use whole source/COFF/AUX differs')
        if 'instructions' in r and SOURCE.instructions(raw,0,flow)!=r['instructions']:raise ValueError('Catalog use full natural instructions differ')
        sections[r['section']]=(raw,fields)
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];verify_source_owner(r,fields)
        at=int(r['address'],16);linked,proof=bind(raw,fields,at,r['bindings'],flow,r['roots'])
        if len(linked)!=r['size'] or proof!=r['linked_flow'] or linked!=c.pe_bytes_at(target,at,r['size']):
            raise ValueError('Catalog use whole unmasked source comparison differs')
    ordinary,template=[sections[r['section']][0] for r in ctl['comparisons'] if r['size']==56]
    if ordinary!=template:raise ValueError('Catalog use invents distinct original template spelling')
    methods={d['symbol']:r['size'] for r in ctl['sections'] for d in r['source']['definitions'] if d['type']==32}
    if any(methods[k]!=n for k,n in ctl['alternatives'].items()) or sorted(ctl['alternatives'].values())!=[56,56,75,78]:
        raise ValueError('Catalog use whole implicit/template alternatives differ')
    r=ctl['layout'];raw=sections[r['section']][0]
    if len(raw)!=24 or list(struct.unpack('<6I',raw))!=[1,1,20,20,40,4]:
        raise ValueError('Catalog use generic observations gain a private owner layout')


def replay(m,evidence_only=False):
    c=module('catalog_target','compare-coff-function.py');coff=module('catalog_coff','coff_data.py');flow=module('catalog_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Catalog use target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Catalog use retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for script in m['cold_dependencies']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Catalog use full retained source/callee/archive proof failed: '+script+'\n'+result.stderr[-1500:])
    ctl=m['public_control'];scratch=ROOT/'build/origin-archive-catalog-use-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'ArchiveCatalogUse.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or HEADERS(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Catalog use cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Catalog use immutable manifest differs')
    replay(m,args.evidence_only)
    print('R237:one whole authored archive first-user policy56; independent paired count/catalog/file/main context; complete original clear/destructor/Tidy source owners; full cold ordinary/template/implicit alternatives; original spelling/type/layout/ABI and exact state unclaimed.')

if __name__=='__main__':main()
