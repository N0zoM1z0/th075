#!/usr/bin/env python3
"""Cold-replay whole effect owner policies with independent complete game context."""
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
BASE=module('effect_owner_common','verify-guarded-sprite-list-origins.py')
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/effect-owner-binding-origin-evidence.json'
MANIFEST_SHA256='f05fcecfb44b753f2061a0d04b3562941563922e1ddee7f92be525a444b1e0e2'
PLAN_DIGESTS={'evidence_id': 'ef59919151890ff3ea597658df7cbae681d89ce9ac601459df14dbb3df3ad356', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '534dc73130f10a900efed6fed7784aa9766be13a0c4a3334759cb104563f65c9', 'anchors': 'a5f6b2eef0ef30f06dbbbf5766b41251e90cc57e295d170958b2bc9c853c125e', 'context': 'e6231a0ed336c6b088dd62aca1e8095b3ada7b06d63d71f8f316a7d3acb1a8af', 'canonical': 'fd9682e6d7cf188558125ce01a80c9588f5d1164ed07a668a3ea1ce048bf04e0', 'unselected_sha256': 'a9c3c0d6077228eb8c0adb40ab8f1475b6ea9a9042a8d9366f1aaaa446c8170d', 'public_control': '0781a5a80215eedbdd77b044eaf4c8df0a132efa6ba161ca1475c1970f83dd5e', 'cold_dependencies': '538ee07ee588e60d0ad265ddea498ba2293c9f4eb93fa06f7358f435e2babc22', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': '4d240ed64569aefd924b7d745dffdf89899d2bf6c26e0ce4e50ae5d8a5073bba', 'interpretation': '70edabf1c9bbf28314c2a369ed4cab356ce2a7fa6b98d043eac5e722f5a30083'}
WHOLE={'0x0045BA10':21}
CONFIDENCE='whole-post-construction-fighter-reference-binding-with-independent-effect-allocation-initialization-and-spawn-consumption'


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Effect owner immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Effect owner complete immutable evidence differs: '+k)
    if m['evidence_id']!='R241' or {r['address']:r['size'] for r in m['functions']}!=WHOLE:
        raise ValueError('Effect owner bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='BattleEffectManager',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R241')):
            raise ValueError('Effect owner gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Effect owner original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Effect owner scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('effect_owner_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']};decoded={}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']));ins=SOURCE.instructions(raw,at,flow)
        if (digest(raw)!=r['body_sha256'] or cfg!=r['cfg'] or len(ins)!=r['instruction_count']
                or metadata_digest(ins)!=r['instructions_sha256'] or (r['instructions'] is not None and ins!=r['instructions'])):
            raise ValueError('Effect owner whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Effect owner original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Effect owner full original switch records differ')
        decoded[a]=ins
    for a,witnesses in m['context']['witnesses'].items():
        BASE.BASE.BASE.require(decoded[a],{int(k):tuple(v) for k,v in witnesses.items()})
    for r in m['context']['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Effect owner claims external alignment')
    ctx=m['context'];old=module('effect_owner_original_policy','verify-game-parent-policy-origins.py');plan=json.loads((ROOT/ctx['prior_policy']['path']).read_text())
    old.verify_plan(plan)
    for r in ctx['prior_policy']['functions']:
        if r not in plan['functions']:raise ValueError('Effect owner replaces an original complete policy record')
        native=records[r['address']]
        ins=decoded[r['address']]
        witnesses=[dict(site=f"0x{int(r['address'],16)+i['offset']:08X}",mnemonic=i['mnemonic'],operands=i['operands']) for i in ins]
        if (native['size']!=r['size'] or native['body_sha256']!=r['body_sha256'] or native['cfg']!=r['cfg']
                or witnesses!=r['witnesses'] or native['authored_record']!=r['accepted_authored_record']):
            raise ValueError('Effect owner truncates the original complete constructed manager')
    for r in ctx['prior_policy']['anchors']:
        if r not in plan['anchors']:raise ValueError('Effect owner replaces its original entire fighter parent')
        native=records[r['address']]
        if native['size']!=r['size'] or native['body_sha256']!=r['record']['body_sha256'] or native['authored_record']!=r['record']:
            raise ValueError('Effect owner truncates its independent original fighter parent')
    fs={r['address']:r for r in rows('functions.csv')};eh=module('effect_owner_frames','compiler_eh.py')
    for frame in ctx['frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('Effect owner loses a real whole lifetime frame')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in fs},set())
    lifetime=json.loads((ROOT/'config/game-lifetime-origin-evidence.json').read_text())
    table=ctx['vtable']
    if table not in lifetime['vtables']:raise ValueError('Effect owner replaces original scene-base vtable evidence')
    raw=c.pe_bytes_at(target,int(table['address'],16),table['size'])
    sections=module('effect_owner_sections','verify-compiler-origins.py').sections(target)
    if (digest(raw)!=table['body_sha256'] or [f'0x{x:08X}' for x in struct.unpack('<3I',raw)]!=table['slots']
            or not any(a<=int(table['address'],16) and int(table['address'],16)+len(raw)<=a+n and flags&0x40000000 and not flags&0xa0000000 for a,n,flags in sections)):
        raise ValueError('Effect owner scene-base readonly vtable differs')
    if m['historical_snapshots']:raise ValueError('Effect owner selected original snapshot audit differs')


def verify_comparison(r,raw,target_bytes,fields):
    if fields or r['bindings'] or len(raw)!=r['source_size'] or len(target_bytes)!=r['target_size']:
        raise ValueError('Effect owner comparison crops an extent or invents a source field')
    if r['role']=='positive':
        if raw!=target_bytes:raise ValueError('Effect owner complete unmasked positive differs')
    elif r['role']=='negative':
        differences=[dict(offset=i,source=raw[i] if i<len(raw) else None,target=target_bytes[i] if i<len(target_bytes) else None)
            for i in range(max(len(raw),len(target_bytes))) if (raw[i] if i<len(raw) else None)!=(target_bytes[i] if i<len(target_bytes) else None)]
        if raw==target_bytes or differences!=r['differences']:
            raise ValueError('Effect owner negative masks or discards genuine differences')
    else:raise ValueError('Effect owner source alternative role differs')


def verify_control(m,body,target,c,coff,flow):
    extra=module('effect_owner_source_carrier','sdk_x3d_carriers.py');inventory=module('effect_owner_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('effect_owner_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Effect owner full code/data/AUX/field emission differs')
    definitions=coff.parse_symbols(body,c.coff_name)[1]
    actual_weak=[weak.read_weak_reference(body,d['symbol'],c,coff,0) for d in definitions if d['storage']==105]
    if actual_weak!=ctl['weak_references']:raise ValueError('Effect owner real weak alias/AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Effect owner whole source/COFF/AUX differs')
        if 'instructions' in r and SOURCE.instructions(raw,0,flow)!=r['instructions']:raise ValueError('Effect owner full natural instructions differ')
        sections[r['section']]=(raw,fields)
    for r in ctl['comparisons']:
        section=next(q for q in ctl['sections'] if q['section']==r['section']);raw,fields=sections[r['section']]
        if r['source_definition'] not in section['source']['definitions'] or r['source_definition']['offset'] or r['source_definition']['type']!=32 or r['source_definition']['storage']!=2:
            raise ValueError('Effect owner source alternative loses its complete defining owner')
        verify_comparison(r,raw,c.pe_bytes_at(target,int(r['address'],16),r['target_size']),fields)
        if flow.flow(raw,int(r['address'],16),[0],[],{}, {})!=r['flow']:
            raise ValueError('Effect owner complete natural alternative CFG differs')
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:
            raise ValueError('Effect owner generic sizeof observations invent a private layout')


def replay(m,evidence_only=False):
    c=module('effect_owner_target','compare-coff-function.py');coff=module('effect_owner_coff','coff_data.py');flow=module('effect_owner_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Effect owner target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Effect owner retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for command in m['cold_dependencies']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),*command],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Effect owner full retained lifetime source proof failed: '+repr(command)+'\n'+result.stderr[-1800:])
        if result.stdout.strip():print(result.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-effect-owner-binding-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'EffectOwnerBinding.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or module('effect_owner_headers','verify-deque-size-context-origins.py').included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Effect owner cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Effect owner immutable manifest differs')
    replay(m,args.evidence_only)
    print('R241:one whole authored fighter-reference binding21; complete post-construction allocation and effect-spawn consumption; full cold R108 explicit/implicit alternatives retained; two natural21 positives and whole24/26/15/13 negatives; scene constructor34 remains unknown; no original private layout/ABI/source/mapping or exact credit.')

if __name__=='__main__':main()
