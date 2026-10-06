#!/usr/bin/env python3
"""Cold-replay whole sprite parameter policies with independent complete game context."""
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
BASE=module('sprite_parameter_common','verify-guarded-sprite-list-origins.py')
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/sprite-render-parameter-origin-evidence.json'
MANIFEST_SHA256='c0045f055de670c4e8f69649ff1f0f31535af4149f547e4ea3f9ad424b218c8c'
PLAN_DIGESTS={'evidence_id': '31a8dd659aae4ed11c415f7316825b295ad805de16af0f8c1c062c2e0725c38a', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '3044701c3246bcac9aabae6de6d358d71411b9180113ba9830ac51e94b038a4d', 'anchors': '971635aad52aeb04e7a2ec5c6338f326a793f69592d9e9c386dcfa8eed82c088', 'context': '51c906ed448a3638c7aba27652615ce5e3a90dcc788f097906b1f368926f705c', 'frame_context': 'ce1ca89fe882422fa7c9111c5164bd124f7f871f6cbd8d02e82fc07e84c74ea1', 'canonical': '909078e9e8c25d58ee533dbdf420aeaee3900f949ed93e54686e60dc842507bf', 'unselected_sha256': '27ccf1d4433390c212fdd7e9e59c8e80e35e31342384492202039180e923cac4', 'public_control': 'de5727bc710ff4c052fb5e18f4facbb0efbb2c7111faee660aba8af2190ce855', 'cold_dependencies': '1394682985bdbbacde0a6cb0d8b0f277ad1d8a3069420430a778a0547ca7defd', 'historical_snapshots': '209a2577c27f8fa709bf03124e5680273a82b067641da4424a13e5bb2f2b07da', 'retained_sha256': 'b27790743410f5c2ba11aa4b9ba093049f22178b59726fde7d1e28a4c228b243', 'interpretation': 'cd6e4bf36ffe4532383be77a9cdbd3165c331f9e088664df70566d3e612b857f'}
WHOLE={'0x00410FA0':22,'0x00410FE0':22}
CONFIDENCE='whole-sprite-sampling-and-color-mask-writes-with-independent-created-owner-selection-action-and-draw-context'


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Sprite parameter immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Sprite parameter complete immutable evidence differs: '+k)
    if m['evidence_id']!='R239' or {r['address']:r['size'] for r in m['functions']}!=WHOLE:
        raise ValueError('Sprite parameter bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='SpriteSequence',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R239')):
            raise ValueError('Sprite parameter gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Sprite parameter original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Sprite parameter scoped canonical ownership differs: '+a)


def verify_history(m):
    selected={r['address']:r for r in m['functions']}
    for h in m['historical_snapshots']:
        document=json.loads((ROOT/h['path']).read_text());value=document
        for key in h['trail']:value=value[key]
        r=selected[h['record']['address']];kind=h['trail'][-1]
        if value!=h['record'] or kind not in ['function','origin'] or value!=r['original_'+kind]:
            raise ValueError('Sprite parameter rewrites a literal original unknown snapshot')
    prior=m['frame_context'];p=ROOT/prior['path'];old=module('sprite_parameter_original_frame',Path(prior['script']).name);plan=json.loads(p.read_text())
    if (digest(p.read_bytes())!=prior['manifest_sha256'] or old.MANIFEST_SHA256!=prior['manifest_sha256']
            or digest((ROOT/prior['script']).read_bytes())!=prior['script_sha256']):
        raise ValueError('Sprite parameter original frame context identity differs')
    old.verify_plan(plan)
    if (plan['game_context']!=prior['game_context'] or plan['parents']!=prior['parents']
            or plan['functions']!=prior['functions'] or plan['retained_unknowns']!=prior['retained_unknowns']):
        raise ValueError('Sprite parameter replaces the complete original created-owner/game-call context')
    return old,plan


def verify_native(m,target,c,flow):
    auth=module('sprite_parameter_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']};decoded={}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']));ins=SOURCE.instructions(raw,at,flow)
        if (digest(raw)!=r['body_sha256'] or cfg!=r['cfg'] or len(ins)!=r['instruction_count']
                or metadata_digest(ins)!=r['instructions_sha256'] or (r['instructions'] is not None and ins!=r['instructions'])):
            raise ValueError('Sprite parameter whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Sprite parameter original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Sprite parameter full original switch records differ')
        decoded[a]=ins
    for a,witnesses in m['context']['witnesses'].items():
        BASE.BASE.BASE.require(decoded[a],{int(k):tuple(v) for k,v in witnesses.items()})
    for r in m['context']['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Sprite parameter claims external alignment')
    original,plan=verify_history(m)
    # Reopen the original pure native game-context proof independently. Its unrelated
    # vector cold CLI has stale R227 snapshots; no old plan or runtime is patched.
    original.verify_native_context(plan,target,c,flow)
    for r in plan['functions']+plan['parents']:
        actual=records[r['address']]
        if (actual['size']!=r['size'] or actual['body_sha256']!=r['body_sha256'] or actual['cfg']!=r['cfg']
                or (r.get('instructions_sha256') and actual['instructions_sha256']!=r['instructions_sha256'])):
            raise ValueError('Sprite parameter truncates a complete original native frame/selection/owner record')
    for r in plan['parents']:
        if r['record'] not in rows(Path(plan['authored_path']).name) and r['record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Sprite parameter original full parent record is absent')
    for r in plan['functions']:
        if r['accepted_origin']['origin']=='authored' and r['record'] not in rows(Path(plan['authored_path']).name):
            raise ValueError('Sprite parameter original complete native policy record is absent')


def verify_comparison(r,raw,target_bytes,fields):
    if fields or r['bindings'] or len(raw)!=r['source_size'] or len(target_bytes)!=r['target_size']:
        raise ValueError('Sprite parameter comparison crops an extent or invents a source field')
    if r['role']=='positive':
        if raw!=target_bytes:raise ValueError('Sprite parameter complete unmasked positive differs')
    elif r['role']=='negative':
        differences=[dict(offset=i,source=raw[i] if i<len(raw) else None,target=target_bytes[i] if i<len(target_bytes) else None)
            for i in range(max(len(raw),len(target_bytes))) if (raw[i] if i<len(raw) else None)!=(target_bytes[i] if i<len(target_bytes) else None)]
        if raw==target_bytes or differences!=r['differences']:
            raise ValueError('Sprite parameter negative masks or discards genuine differences')
    else:raise ValueError('Sprite parameter source alternative role differs')


def verify_control(m,body,target,c,coff,flow):
    extra=module('sprite_parameter_source_carrier','sdk_x3d_carriers.py');inventory=module('sprite_parameter_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('sprite_parameter_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Sprite parameter full code/data/AUX/field emission differs')
    for r in ctl['weak_references']:
        if weak.read_weak_reference(body,r['symbol'],c,coff,0)!=r:raise ValueError('Sprite parameter real weak alias/AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Sprite parameter whole source/COFF/AUX differs')
        if 'instructions' in r and SOURCE.instructions(raw,0,flow)!=r['instructions']:raise ValueError('Sprite parameter full natural instructions differ')
        sections[r['section']]=(raw,fields)
    for r in ctl['comparisons']:
        section=next(q for q in ctl['sections'] if q['section']==r['section']);raw,fields=sections[r['section']]
        if r['source_definition'] not in section['source']['definitions'] or r['source_definition']['offset'] or r['source_definition']['type']!=32 or r['source_definition']['storage']!=2:
            raise ValueError('Sprite parameter source alternative loses its complete defining owner')
        verify_comparison(r,raw,c.pe_bytes_at(target,int(r['address'],16),r['target_size']),fields)
        if flow.flow(raw,int(r['address'],16),[0],[],{}, {})!=r['flow']:
            raise ValueError('Sprite parameter complete natural alternative CFG differs')
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:
            raise ValueError('Sprite parameter generic sizeof observations invent a private layout')


def replay(m,evidence_only=False):
    c=module('sprite_parameter_target','compare-coff-function.py');coff=module('sprite_parameter_coff','coff_data.py');flow=module('sprite_parameter_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Sprite parameter target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Sprite parameter retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for script in m['cold_dependencies']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Sprite parameter full retained list source proof failed: '+script+'\n'+result.stderr[-1800:])
        if result.stdout.strip():print(result.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-sprite-render-parameter-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'SpriteRenderParameters.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or BASE.included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Sprite parameter cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Sprite parameter immutable manifest differs')
    replay(m,args.evidence_only)
    print('R239:two whole authored sprite parameter writes44; independent complete original frame/selection/created-owner/action native context and whole packet/drawing consumers; full cold R238 list source graphs; ordinary/template methods22 and entire borrowed-field alternatives13; historical snapshots unchanged; original spelling/type/layout/ABI and exact state unclaimed.')

if __name__=='__main__':main()
