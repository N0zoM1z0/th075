#!/usr/bin/env python3
"""Cold-compare allocator destroy wrappers with independent full deque parents."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('allocator_sdk',ROOT/'scripts/verify-sdk-dependency-origins.py')
SDK=importlib.util.module_from_spec(spec);spec.loader.exec_module(SDK)
ENDPOINT=SDK.ENDPOINT;PAIRED=SDK.PAIRED;module=SDK.module;digest=SDK.digest
MANIFEST_SHA256='e4128317328d7680988551c6fbe71e3779cd82a0d8366ff35df4d562900ca78b'
CONFIDENCE='complete-vc7-allocator-destroy-with-independent-whole-deque-parent-fields'
KEYS={'0x00422610':25,'0x0042E390':25}
ADDRESSES=list(KEYS)+['0x00422290','0x0042E120','0x00422270','0x0042E100','0x004229C0','0x0042E580','0x00422A20']+list(KEYS)+['0x004229C0','0x0042E580']
SIZES=[25,25,151,151,25,25,15,5,44,25,25,15,5]
ROLES=['candidate-sdk-owner']*2+['retained-whole-library-parent']*2+['whole-operation-context']*4+['retained-compiler-wrapper']+['byte-equal-ordinary-alternative']*4
LAYOUT=SDK.LAYOUT+[1,1]


def manifest():return json.loads((ROOT/'config/allocator-destroy-origin-evidence.json').read_text())


def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        text=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if text[:3].lower()!='z:/':raise ValueError('allocator include lacks its actual host mapping')
        path=Path(text[2:]);relative=str(path.relative_to(ROOT))
        if relative!='probes/VC7SDKDependencyContexts.cpp' and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('allocator source gains an unreviewed include owner')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if (m['evidence_id']!='R165' or m['target_sha256']!=SDK.manifest()['target_sha256']
            or m['probe']!='probes/VC7AllocatorDestroyContexts.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=29 or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=2
            or [r['address'] for r in m['controls']]!=ADDRESSES or [r['size'] for r in m['controls']]!=SIZES
            or [r['role'] for r in m['controls']]!=ROLES or sum(len(r['bindings']) for r in m['controls'])!=12
            or len(m['emission'])!=61 or sum(r['size'] for r in m['emission'])!=2472
            or len(m['snapshots'])!=41 or len(m['retained'])!=4
            or m['layout'] not in m['emission'] or m['layout']['size']!=68 or m['layout_values']!=LAYOUT):
        raise ValueError('allocator destruction loses complete bounded source/parents/ordinary controls or fields')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function']
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=25
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!='VC7STL' or new['owner']!='library' or new['status']!='excluded'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R165')):
            raise ValueError('allocator destruction grants false extent/ownership/source/private ABI/exact credit')
    routes=[['0x004229C0'],['0x0042E580'],['0x00422270','0x00422610'],['0x0042E100','0x0042E390'],[],[],
            ['0x00422A20'],[],['0x004212A0','0x00640F15'],['0x004229C0'],['0x0042E580'],['0x00422A20'],[]]
    for i,r in enumerate(m['controls']):
        section,d=r['section'],r['source_definition']
        if (section not in m['emission'] or d not in section['definitions'] or section['size']!=r['size']
                or d['offset'] or d['storage']!=2 or d['type']!=32 or section['source_sha256']!=r['source_sha256']
                or len(section['fields'])!=len(r['bindings']) or [b['target_address'] for b in r['bindings']]!=routes[i]):
            raise ValueError('allocator destruction truncates source/parent/ordinary extent or substitutes real operation')
        if i<2 and (d['symbol']!=m['functions'][i]['symbol'] or not d['symbol'].startswith('?destroy@?$allocator@U')):
            raise ValueError('allocator destruction replaces genuine SDK source with ordinary alternative')
        if i in (2,3) and not d['symbol'].startswith('?pop_back@?$deque@U'):
            raise ValueError('allocator destruction loses genuine complete independent deque parent')
        if i>=9 and 'Ordinary' not in d['symbol']:raise ValueError('allocator destruction loses distinct full ordinary alternative')
        for field,b in zip(section['fields'],r['bindings']):
            if (b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address'])
                    or field['type'] not in ('REL32','DIR32') or field['offset']+4>r['size']):
                raise ValueError('allocator destruction masks or overrides actual source-owned field')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in {'0x004229C0':15,'0x0042E580':5,'0x004212A0':72,'0x004591E0':417,'0x0045AAE0':368,
                   '0x0040D8E0':19,'0x004229D0':28,'0x0040F9F0':15,'0x0040E000':158,'0x005F84B0':167,'0x00641FB8':11,'0x00641DAA':11}.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('allocator destruction resolves independent opaque child/policy')
    for a,origin,evidence,size in [('0x00422290','library','R164',151),('0x0042E120','library','R164',151),
            ('0x00422A20','compiler','R037',44),('0x00640F15','library','R142',5)]:
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!=origin or r['origin']['evidence_id']!=evidence:
            raise ValueError('allocator destruction changes independent parent/compiler/runtime evidence')
    definitions=[(d['symbol'],d['offset']) for d in m['layout']['definitions'] if d['storage']==2]
    if sorted(definitions,key=lambda d:d[1])!=[('_SDKDependencyLayout',0),('_AllocatorDestroyLayout',60)]:
        raise ValueError('allocator destruction loses either actual readonly observation definition')
    for r in m['retained']:
        if r['file'] not in m['retained_sha256'] or r['record']['address']!=r['address']:
            raise ValueError('allocator destruction loses original whole parent/compiler/runtime record')


def accepted_snapshot(snapshot,function,origin):
    m=manifest()
    if digest((ROOT/'config/allocator-destroy-origin-evidence.json').read_bytes())!=MANIFEST_SHA256:
        raise ValueError('allocator destruction immutable evidence differs')
    verify_plan(m);r=next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin'])
                and function==r['accepted_function'] and origin==r['accepted_origin'])


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [('config/allocator-destroy-origin-evidence.json',MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('allocator destruction immutable source/prior evidence differs: '+path)
    c=module('allocator_target','compare-coff-function.py');coff=module('allocator_coff','coff_data.py');extent=module('allocator_extent','verify-vendor-record-origins.py');cfg=module('allocator_cfg','verify-authored-origins.py')
    target=c.verified_target();rows=PAIRED.BUFFER.PRIOR.PRIOR.rows
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};records={r['address']:r for r in m['functions']}
    if digest(target)!=m['target_sha256']:raise ValueError('allocator destruction target identity differs')
    for r in m['functions']:SDK.check_ledger(r,functions[r['address']],origins[r['address']],args.evidence_only)
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('allocator destruction alters unrelated accepted/pending canonical row')
        body=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(body)!=r['body_sha256']:raise ValueError('allocator destruction full canonical body differs')
        if a=='0x004212A0':cfg.verify_body(body,int(a,16))
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())['functions'] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('allocator destruction original independent evidence record differs')
    scratch=ROOT/'build/origin-allocator-destroy-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'AllocatorDestroyContexts.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:
            raise ValueError('allocator destruction cold source/actual include ownership differs')
        data=path.read_bytes()
        if PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('allocator destruction whole ordinary emission differs')
        catalog={}
        def add(name,address):
            if name in catalog and catalog[name]!=address:raise ValueError('allocator destruction aliases independent complete source owners')
            catalog[name]=address
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):add(d['symbol'],int(r['address'],16)+d['offset'])
        for r in m['controls']:
            for b in r['bindings']:
                name,a=b['symbol'],int(b['target_address'],16)
                if name not in catalog and a not in (0x004212A0,0x00640F15):raise ValueError('allocator destruction external field lacks independent lifetime/runtime boundary')
                add(name,a)
            raw,linked=ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:
                raise ValueError('allocator destruction full unmasked comparison differs: '+r['address'])
            if r['address']=='0x00422A20':
                d=r['source_definition'];ss=r['section']
                if [x for x in ss['definitions'] if x['type']==32 and x['storage']==2]!=[d] or not ss['flags']&0x20 or not ss['flags']&0x1000:
                    raise ValueError('allocator destruction compiler wrapper loses complete unique defining COMDAT')
            elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:
                raise ValueError('allocator destruction loses complete positive own source AUX extent')
            cfg.verify_body(actual,int(r['address'],16))
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<17I',raw))!=LAYOUT:raise ValueError('allocator destruction entire observation layout differs')
    print('R165 origins OK: two complete allocator destroy wrappers / 50 bytes through unchanged whole R164 deque parents / 302 bytes; 13 full controls / 536 bytes and 12 real unmasked fields; four full ordinary alternatives / 70 bytes are byte-equal without resolving original declarations or independent destruction children; all 61 cold ordinary sections / 2472 bytes, 28 SDK headers plus the original pinned probe include and whole combined 68-byte observer layout; 15-/5-byte destruction children and 72-byte game lifetime remain unknown; R037 compiler/R142 runtime and all protected records preserved; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
