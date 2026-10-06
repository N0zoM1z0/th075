#!/usr/bin/env python3
"""Cold-replay guarded sprite-list consumption and original library/owner alternatives."""
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
BASE=module('sprite_list_common','verify-archive-catalog-use-origins.py')
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
bind=BASE.bind
EVIDENCE='config/guarded-sprite-list-origin-evidence.json'
MANIFEST_SHA256='7928ef70065b69fc93c49265ac3324b6e822cfe3a6a3879e67c6b8fe5d984482'
PLAN_DIGESTS={'evidence_id': 'a76ced87afc2814bf259abe105378dba0157e0513773d8fedee04a89b658d92c', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '3ecf3a123f4fc9e81a137412ff14316c1b29610b67b2f7b2e27b82faf3f3532d', 'anchors': 'bcd04625b7c48d258ebfe843130e345e0aa5f2b9b5bfae728eedd9fb0c0b3d2d', 'context': '3c294779e36f3d4f0692f8cf7cba090b7326ad25aba8fae0878b0cc895809c43', 'canonical': 'c72d4c8910b4b61c04e1e2aa4f91b976ee3ca8b185580d0f5f0acb3eeeb641a4', 'unselected_sha256': '4fa256d157ddbb43b5995c442473eac054cf961c37b0f9189b47adcf414e679d', 'public_control': '3ebd015a2c1e6c9aeeb59089c73b1ba193ba2ca4cb8308c96522d12b7f1af763', 'retained_replays': '26c8f9cace1390ba669a17631135ba857e967b582b38f78c961d79ec9f009b87', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': '7259447929f46a4c4aefc4d04665287372340bc280d077bd0dbf152d912f839c', 'interpretation': '0f06e76ef6200c85f842297f335b1820da7f9c709e63b4c3349d61d46030502f'}
WHOLE={'0x004110C0':37}
CONFIDENCE='whole-guarded-sprite-record-consumption-with-independent-append-render-repeated-pop-and-original-list-context'


def included_headers(output):
    """Bind the actual relative /I probes include to the fixed repository cwd."""
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        value=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()=='z:/':path=Path(value[2:])
        elif value=='probes/VC7ListPolicyDependencies.cpp':path=ROOT/value
        else:raise ValueError('Sprite list include loses its actual fixed host/cwd mapping')
        relative=str(path.relative_to(ROOT))
        if relative not in ['probes/VC7ListPolicyDependencies.cpp','probes/VC7GameContextPolicies.cpp'] and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Sprite list imports unrelated source')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Sprite list immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Sprite list complete immutable evidence differs: '+k)
    if m['evidence_id']!='R238' or {r['address']:r['size'] for r in m['functions']}!=WHOLE or m['historical_snapshots']:
        raise ValueError('Sprite list bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='SpriteSequence',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R238')):
            raise ValueError('Sprite list gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Sprite list original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Sprite list scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('sprite_list_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,at,flow)!=r['instructions'] or cfg!=r['cfg']:
            raise ValueError('Sprite list whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Sprite list original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Sprite list full original switch records differ')
    ctx=m['context']
    for a,witnesses in ctx['witnesses'].items():
        BASE.BASE.require(records[a]['instructions'],{int(k):tuple(v) for k,v in witnesses.items()})
    observed=ctx['condition_byte']
    if digest(c.pe_bytes_at(target,int(observed['address'],16),observed['size']))!=observed['sha256']:
        raise ValueError('Sprite list actual driver condition byte differs')
    for r in ctx['source_records']:
        if r['record'] not in json.loads((ROOT/r['path']).read_text())[r['collection']]:
            raise ValueError('Sprite list changes original complete SDK/ordinary source evidence')
    for r in ctx['header_definitions']:
        raw=(ROOT/r['path']).read_bytes();lines=raw.decode('ascii').splitlines(keepends=True)
        if digest(raw)!=r['whole_sha256'] or ''.join(lines[r['start']-1:r['end']])!=r['text']:
            raise ValueError('Sprite list original whole header/member definition differs')
    for r in ctx['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Sprite list claims external alignment')


def validate_bindings(r,fields,owners):
    if len(fields)!=len(r['bindings']):raise ValueError('Sprite list omits a genuine source field')
    for f,b in zip(fields,r['bindings']):
        if f['symbol'] not in owners or owners[f['symbol']]!=b['target']:
            raise ValueError('Sprite list field lacks an independent whole defining owner')
        if f['type']!='REL32' or f['addend']!=0:
            raise ValueError('Sprite list false public operation call type/addend')


def compare_whole(r,linked,target_bytes):
    if len(linked)!=r['source_size'] or len(target_bytes)!=r['target_size']:
        raise ValueError('Sprite list alternative crops source or target extent')
    if r['role']=='positive':
        if len(linked)!=len(target_bytes) or linked!=target_bytes:raise ValueError('Sprite list complete unmasked positive differs')
    elif r['role']=='negative':
        differences=[dict(offset=i,source=(linked[i] if i<len(linked) else None),target=(target_bytes[i] if i<len(target_bytes) else None))
            for i in range(max(len(linked),len(target_bytes))) if (linked[i] if i<len(linked) else None)!=(target_bytes[i] if i<len(target_bytes) else None)]
        if linked==target_bytes or differences!=r['differences']:
            raise ValueError('Sprite list alternative masks or discards complete genuine differences')
    else:raise ValueError('Sprite list source alternative role differs')


def project_rows(name,actual,transitions):
    """Return literal historical pairs only after exact accepted-successor readback."""
    if name not in ['functions.csv','function-origins.csv']:return actual
    kind='function' if name=='functions.csv' else 'origin';out=[];seen=set()
    for row in actual:
        a=row['address']
        if a in transitions:
            transition=transitions[a]
            if row!=transition['accepted_'+kind]:
                raise ValueError('Sprite list historical view accepts an unapproved current transition')
            out.append(transition['original_'+kind]);seen.add(a)
        else:out.append(row)
    if seen!=set(transitions):raise ValueError('Sprite list historical view loses a complete successor pair')
    return out


def retained_transitions(m,scope):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};transitions={}
    for q in scope['transitions']:
        successor=m['retained_replays']['successors'][q['successor_index']]
        owner=module('sprite_successor_'+successor['evidence_id'],Path(successor['script']).name)
        path=ROOT/successor['path'];plan=json.loads(path.read_text())
        if (digest(path.read_bytes())!=successor['manifest_sha256']
                or owner.MANIFEST_SHA256!=successor['manifest_sha256']
                or digest((ROOT/successor['script']).read_bytes())!=successor['script_sha256']):
            raise ValueError('Sprite list successor whole proof identity differs')
        owner.verify_plan(plan)
        matches=[r for r in plan['functions'] if r['address']==q['address']]
        if len(matches)!=1 or matches[0]!=q['record']:
            raise ValueError('Sprite list successor has no exact bounded complete transition')
        r=matches[0]
        if (q['snapshot']['function']!=r['original_function'] or q['snapshot']['origin']!=r['original_origin']
                or fs[r['address']]!=r['accepted_function'] or os[r['address']]!=r['accepted_origin']):
            raise ValueError('Sprite list rewrites a literal old unknown or current accepted pair')
        transitions[r['address']]=r
    return transitions


def replay_retained_scope(m,scope_name):
    """Run the unchanged entire old cold proof with its explicitly guarded history view."""
    verify_plan(m)
    scopes=[r for r in m['retained_replays']['scopes'] if r['evidence_id']==scope_name]
    if len(scopes)!=1:raise ValueError('Sprite list retained scope is not unique')
    scope=scopes[0];path=ROOT/scope['path'];plan=json.loads(path.read_text())
    old=module('sprite_retained_'+scope_name,Path(scope['script']).name)
    if (digest(path.read_bytes())!=scope['manifest_sha256'] or old.MANIFEST_SHA256!=scope['manifest_sha256']
            or digest((ROOT/scope['script']).read_bytes())!=scope['script_sha256']):
        raise ValueError('Sprite list changes original whole retained script/source plan')
    old.verify_plan(plan);transitions=retained_transitions(m,scope)
    for q in scope['transitions']:
        if q['snapshot']!=plan['snapshots'][q['snapshot_index']]:
            raise ValueError('Sprite list changes an old literal scoped snapshot')
    original_module=old.module
    def scoped_module(name,filename):
        value=original_module(name,filename)
        if filename=='verify-authored-origins.py':
            original_rows=value.rows
            value.rows=lambda dataset:project_rows(dataset,original_rows(dataset),transitions)
        return value
    old.module=scoped_module
    try:old.main()
    finally:old.module=original_module


def verify_control(m,body,target,c,coff,flow):
    extra=module('sprite_list_source_carrier','sdk_x3d_carriers.py');inventory=module('sprite_list_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('sprite_list_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Sprite list full code/data/AUX/field emission differs')
    for r in ctl['weak_references']:
        if weak.read_weak_reference(body,r['symbol'],c,coff,0)!=r:raise ValueError('Sprite list real weak alias/AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Sprite list whole source/COFF/AUX differs')
        if 'instructions' in r and SOURCE.instructions(raw,0,flow)!=r['instructions']:raise ValueError('Sprite list full natural instructions differ')
        sections[r['section']]=(raw,fields)
    # Only full source-owned public list operations are common external call providers.
    owners={r['symbol']:r['address'] for r in ctl['providers']}
    for r in ctl['providers']:
        prior=r['prior_record'];raw,fields=sections[r['section']]
        if r['source']!=next(s['source'] for s in ctl['sections'] if s['section']==r['section']):
            raise ValueError('Sprite list public provider loses its actual defining section')
        if prior!=m['context']['source_records'][r['record_index']]['record']:
            raise ValueError('Sprite list original public provider record differs')
        if r['symbol']!=prior['source_definition']['symbol'] or len(raw)!=prior['size']:
            raise ValueError('Sprite list public operation alias/type/source extent differs')
        if digest(raw)!=prior['source_sha256'] or len(fields)!=len(prior['bindings']):
            raise ValueError('Sprite list original full public source/fields differ')
        for f,b in zip(fields,prior['bindings']):
            if any(f[k]!=b[k] for k in ['offset','type','symbol','addend']):
                raise ValueError('Sprite list original public source field semantics differ')
            definitions=next(q['source']['definitions'] for q in ctl['sections'] if q['section']==f['symbol_section'])
            if not any(d['symbol']==f['symbol'] and d['type']==32 and d['offset']==f['symbol_offset'] for d in definitions):
                raise ValueError('Sprite list source call loses its entire fresh defining owner')
        bindings=[dict(offset=f['offset'],type=f['type'],symbol=f['symbol'],target=b['target_address']) for f,b in zip(fields,prior['bindings'])]
        linked,proof=bind(raw,fields,int(r['address'],16),bindings,flow,[0])
        if linked!=c.pe_bytes_at(target,int(r['address'],16),len(raw)) or proof!=r['linked_flow']:
            raise ValueError('Sprite list whole independently linked public provider differs')
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];validate_bindings(r,fields,owners)
        linked,proof=bind(raw,fields,int(r['address'],16),r['bindings'],flow,[0])
        if proof!=r['linked_flow']:raise ValueError('Sprite list whole ordinary/library alternative CFG differs')
        compare_whole(r,linked,c.pe_bytes_at(target,int(r['address'],16),r['target_size']))
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:
            raise ValueError('Sprite list generic sizeof observations invent a private layout')


def replay(m,evidence_only=False):
    c=module('sprite_list_target','compare-coff-function.py');coff=module('sprite_list_coff','coff_data.py');flow=module('sprite_list_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Sprite list target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Sprite list retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for scope in m['retained_replays']['scopes']:
        command=("import importlib.util,json;from pathlib import Path;"
            "p=Path('scripts/verify-guarded-sprite-list-origins.py');"
            "s=importlib.util.spec_from_file_location('sprite_retained_entry',p);"
            "v=importlib.util.module_from_spec(s);s.loader.exec_module(v);"
            "v.replay_retained_scope(json.loads(Path(v.EVIDENCE).read_text()),"+repr(scope['evidence_id'])+")")
        result=subprocess.run([str(ROOT/'scripts/repo-python'),'-c',command],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Sprite list full retained cold source proof failed: '+scope['evidence_id']+'\n'+result.stderr[-1800:])
        if result.stdout.strip():print(result.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-guarded-sprite-list-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'GuardedSpriteList.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Sprite list cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Sprite list immutable manifest differs')
    replay(m,args.evidence_only)
    print('R238:one whole authored guarded sprite-list consumption37; independent complete packet append/render and repeated driver calls; full original list size/pop providers; cold ordinary guard and entire unguarded-library/borrowed alternatives; private owner/layout/source/ABI and exact state unclaimed.')

if __name__=='__main__':main()
