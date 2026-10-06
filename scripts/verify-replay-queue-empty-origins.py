#!/usr/bin/env python3
"""Cold-replay primary replay-input exhaustion and complete genuine library alternatives."""
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile
ROOT=Path(__file__).resolve().parents[1]
def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    value=importlib.util.module_from_spec(spec);spec.loader.exec_module(value);return value
BASE=module('replay_queue_common','verify-sprite-render-parameter-origins.py')
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/replay-queue-empty-origin-evidence.json'
MANIFEST_SHA256='3dbbcaea7887bab375cc8a5f0d37dc6d2746199992ec94058ca78f684deb4cb5'
PLAN_DIGESTS={'evidence_id': 'cbb1c9d99e89c6020562f765ea8c7039f55d769f90232a649e6e800c0c82fdf8', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '45d848393e98c6f1a87ec5d611397044df9dc27207518c6304f0054b71732692', 'anchors': '6bc364a6ce1bde71299af9c4ec7c9254d2f4cdbba343a017a24e382323215bd1', 'context': '6f982c3b35f6d75e373cfda4ced1657a978962a297049e085bacb304037b416a', 'canonical': 'd6270475aa96ce50ab9977a54b17a9e18d7f534dc70041a39a90a233dcd8818d', 'unselected_sha256': '481063a2cab31fa6c60a9d421bd0e7ff7e687cbcc7a2fef9b15928fedc7015e2', 'public_control': 'c2fbbd25bfcdcc8d95f10c816b4fb696fd921766ddcd14f632f68b6bf1e268a8', 'cold_dependencies': '7c7ee198851077a6d03ba35f16a3317d81c27ffe06f619f7fdc75ded5bf6c5cc', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': 'c22caddb88972aa9db2637481eb30af4807ff28337a17ecc6b8ea0fce9ae28f6', 'interpretation': '871112ea9f4b26a76fda538ec8fa73dc06c0e2ee3e33117a693cb82bfd73895c'}
WHOLE={'0x004142D0':35}
CONFIDENCE='whole-primary-replay-input-queue-exhaustion-with-independent-serialized-byte-load-live-consumption-and-battle-completion-context'


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Replay queue immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Replay queue complete immutable evidence differs: '+k)
    if m['evidence_id']!='R240' or {r['address']:r['size'] for r in m['functions']}!=WHOLE:
        raise ValueError('Replay queue bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='ReplayRecords',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R240')):
            raise ValueError('Replay queue gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Replay queue original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Replay queue scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('replay_queue_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']};decoded={}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']));ins=SOURCE.instructions(raw,at,flow)
        if (digest(raw)!=r['body_sha256'] or cfg!=r['cfg'] or len(ins)!=r['instruction_count']
                or metadata_digest(ins)!=r['instructions_sha256'] or (r['instructions'] is not None and ins!=r['instructions'])):
            raise ValueError('Replay queue whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Replay queue original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Replay queue full original switch records differ')
        decoded[a]=ins
    for a,witnesses in m['context']['witnesses'].items():
        BASE.BASE.BASE.BASE.require(decoded[a],{int(k):tuple(v) for k,v in witnesses.items()})
    for r in m['context']['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Replay queue claims external alignment')
    ctx=m['context'];storage=BASE.BASE.BASE.virtual_storage(target,0x671750,420)
    if storage!=ctx['storage'] or storage['permissions']!=0xc0000000:
        raise ValueError('Replay queue minimum observed writable storage differs')
    if not storage['file_backed'] or digest(c.pe_bytes_at(target,0x671750,420))!=ctx['storage_sha256']:
        raise ValueError('Replay queue actual whole file-backed minimum storage differs')
    # A virtual PE extent does not fabricate file-backed bytes or initial values.
    imports=module('replay_queue_imports','verify-import-origins.py').pe_imports(target,c)
    for r in ctx['imports']:
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('Replay queue actual raw-PE file import differs')
    for r in ctx['header_definitions']:
        raw=(ROOT/r['path']).read_bytes();lines=raw.decode('ascii').splitlines(keepends=True)
        if digest(raw)!=r['whole_sha256'] or ''.join(lines[r['start']-1:r['end']])!=r['text']:
            raise ValueError('Replay queue original complete library definition differs')
    for r in ctx['records']:
        p=ROOT/r['path'];document=json.loads(p.read_text()) if p.suffix=='.json' else rows(p.name)
        if p.suffix=='.json':document=document[r['collection']]
        if r['record'] not in document:raise ValueError('Replay queue original complete SDK/provider record differs')
    if m['historical_snapshots']:raise ValueError('Replay queue selected historical snapshot audit differs')


def verify_comparison(r,linked,target_bytes):
    if len(linked)!=r['source_size'] or len(target_bytes)!=r['target_size']:
        raise ValueError('Replay queue comparison crops an extent')
    if r['role']=='positive':
        if linked!=target_bytes:raise ValueError('Replay queue complete unmasked positive differs')
    elif r['role']=='negative':
        differences=[dict(offset=i,source=linked[i] if i<len(linked) else None,target=target_bytes[i] if i<len(target_bytes) else None)
            for i in range(max(len(linked),len(target_bytes))) if (linked[i] if i<len(linked) else None)!=(target_bytes[i] if i<len(target_bytes) else None)]
        if linked==target_bytes or differences!=r['differences']:
            raise ValueError('Replay queue negative masks or discards genuine differences')
    else:raise ValueError('Replay queue source alternative role differs')


def verify_binding_owners(r,fields,owners):
    if len(fields)!=len(r['bindings']):raise ValueError('Replay queue omits a real source field')
    for f,b in zip(fields,r['bindings']):
        if f['type']!='REL32' or f['addend']!=0 or owners.get(f['symbol'])!=b['target']:
            raise ValueError('Replay queue call lacks its independently proved full typed public provider')


def verify_control(m,body,target,c,coff,flow):
    extra=module('replay_queue_source_carrier','sdk_x3d_carriers.py');inventory=module('replay_queue_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('replay_queue_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Replay queue full code/data/AUX/field emission differs')
    for r in ctl['weak_references']:
        if weak.read_weak_reference(body,r['symbol'],c,coff,0)!=r:raise ValueError('Replay queue real weak alias/AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Replay queue whole source/COFF/AUX differs')
        if 'instructions' in r and SOURCE.instructions(raw,0,flow)!=r['instructions']:raise ValueError('Replay queue full natural instructions differ')
        sections[r['section']]=(raw,fields)
    owners={r['symbol']:r['address'] for r in ctl['providers']}
    for p in ctl['providers']:
        raw,fields=sections[p['section']]
        prior=m['context']['records'][p['record_index']]['record']
        if fields or len(raw)!=p['size'] or digest(raw)!=prior['source_sha256']:
            raise ValueError('Replay queue public provider loses its complete original source body')
        source=next(r['source'] for r in ctl['sections'] if r['section']==p['section'])
        if not any(d['symbol']==p['symbol'] and d['type']==32 and d['storage']==2 and d['offset']==0 for d in source['definitions']):
            raise ValueError('Replay queue public provider loses its actual fresh defining owner')
        if p['record_index']==0 and p['symbol']!=prior['coff_symbol']:
            raise ValueError('Replay queue size source type differs from the full original alternative')
        if p['record_index']==1 and (prior['family_key']!='?empty' or not p['symbol'].startswith('?empty@?$deque@')):
            raise ValueError('Replay queue maps an unrelated original SDK operation')
        if raw!=c.pe_bytes_at(target,int(p['address'],16),p['size']):
            raise ValueError('Replay queue whole unmasked original public provider differs')
    for r in ctl['comparisons']:
        section=next(q for q in ctl['sections'] if q['section']==r['section']);raw,fields=sections[r['section']]
        if r['source_definition'] not in section['source']['definitions'] or r['source_definition']['offset'] or r['source_definition']['type']!=32 or r['source_definition']['storage']!=2:
            raise ValueError('Replay queue source alternative loses its complete defining owner')
        verify_binding_owners(r,fields,owners)
        linked,proof=BASE.BASE.bind(raw,fields,int(r['address'],16),r['bindings'],flow,[0])
        if proof!=r['flow']:raise ValueError('Replay queue complete natural alternative CFG differs')
        verify_comparison(r,linked,c.pe_bytes_at(target,int(r['address'],16),r['target_size']))
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:
            raise ValueError('Replay queue generic sizeof observations invent a private layout')


def replay(m,evidence_only=False):
    c=module('replay_queue_target','compare-coff-function.py');coff=module('replay_queue_coff','coff_data.py');flow=module('replay_queue_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Replay queue target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Replay queue retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for script in m['cold_dependencies']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Replay queue full retained list source proof failed: '+script+'\n'+result.stderr[-1800:])
        if result.stdout.strip():print(result.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-replay-queue-empty-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'ReplayQueueEmpty.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or module('replay_queue_headers','verify-deque-size-context-origins.py').included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Replay queue cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Replay queue immutable manifest differs')
    replay(m,args.evidence_only)
    print('R240:one whole authored primary replay-input exhaustion35; complete serialized byte load/write, live input consumption and battle-completion context; cold original R149/R086 deque provenance; whole SDK size17/empty25 and four complete library/compact/borrowed negatives; actual AL result preserved; private owner/layout/source/ABI and exact state unclaimed.')

if __name__=='__main__':main()
