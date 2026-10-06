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
BASE=module('effect_lifetime_common','verify-guarded-sprite-list-origins.py')
HISTORY=module('effect_lifetime_history','verify-character-list-front-origins.py')
bind=HISTORY.bind
compare_whole=HISTORY.compare_whole
project_rows=HISTORY.project_rows
retained_transitions=HISTORY.retained_transitions
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/effect-manager-lifetime-origin-evidence.json'
MANIFEST_SHA256='116da4a1fc4c1bbc5547cb4d84b7dcfa414b579b0c3113b8d4f10b4d462e375e'
PLAN_DIGESTS={'evidence_id': 'f6e2fa0de3dbc9f16e033424f8885cc937543867639123f53819ea371bb88f31', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '9f8abb66555adab583f434912c8e249b10cfb601c6b235d4702aad01e3690485', 'anchors': '83d869686fce0c916609bdfb23ec60ff1fcfd8729d4f064f9cd693b99baae279', 'context': 'bbbb8bee6a299f89202e6901d8105c5650245842140c1370613bba89d86e3ad8', 'canonical': '1a4a04c21f09a6aaaed569b149f46d95a50913b7c121315e3cee4c71bbf8b6e3', 'unselected_sha256': '0dcc3490f03a5fa305f59a4749014dcbc2e6d479f042c0f461e520523ce035bc', 'public_control': '8dc9935f847d4f99f502cc2d97215d7277a3c7feaafe9c9eb9d95ec94b581e22', 'retained_replays': 'ba2016ff8b11d69038aa9cb044b04dc0a047b4f0064493e6afa54d5344f7aef1', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': 'd447a86be04e8c92e365e53f9b497c3c6315b6da484a7aa5c775977e270ad1b1', 'interpretation': 'a129f94a2933bad1f93a434d49494ad082b4504579cf96e9ced4400028e9e513'}
WHOLE={'0x0045B9B0':85}
CONFIDENCE='whole-custom-owned-effect-cleanup-before-member-array-destruction-with-independent-pair-and-registered-eh'


def included_headers(output):
    """Bind the actual relative /I probes include to the fixed repository cwd."""
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        value=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()=='z:/':path=Path(value[2:])
        elif value in ['probes/VC7GameContextPolicies.cpp']:path=ROOT/value
        else:raise ValueError('Character front include loses its actual fixed host/cwd mapping')
        relative=str(path.relative_to(ROOT))
        if relative not in ['probes/VC7GameContextPolicies.cpp'] and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Character front imports unrelated source')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Effect lifetime immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Effect lifetime complete immutable evidence differs: '+k)
    if m['evidence_id']!='R244' or {r['address']:r['size'] for r in m['functions']}!=WHOLE:
        raise ValueError('Effect lifetime bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='BattleEffectManager',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R244')):
            raise ValueError('Effect lifetime gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Effect lifetime original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Effect lifetime scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('effect_lifetime_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']};decoded={}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);ins=SOURCE.instructions(raw,at,flow)
        if a=='0x00640F15':
            if (len(raw)!=5 or len(ins)!=1 or ins[0]['mnemonic']!='jmp' or ins[0]['operands']!='0x642a61'
                    or '0x00642A61' not in records):raise ValueError('Effect lifetime scalar delete loses its independently complete free tail')
            cfg=flow.flow(raw,at,[0],[],{at+1:0x642a61},{})
        else:cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if (digest(raw)!=r['body_sha256'] or cfg!=r['cfg'] or len(ins)!=r['instruction_count']
                or metadata_digest(ins)!=r['instructions_sha256'] or (r['instructions'] is not None and ins!=r['instructions'])):
            raise ValueError('Effect lifetime whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Effect lifetime original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Effect lifetime full original switch records differ')
        decoded[a]=ins
    for a,witnesses in m['context']['witnesses'].items():
        BASE.BASE.BASE.require(decoded[a],{int(k):tuple(v) for k,v in witnesses.items()})
    for r in m['context']['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Effect lifetime claims external alignment')
    ctx=m['context'];old=module('effect_lifetime_original_policy','verify-game-parent-policy-origins.py');plan=json.loads((ROOT/ctx['prior_policy']['path']).read_text())
    old.verify_plan(plan)
    for r in ctx['prior_policy']['functions']:
        if r not in plan['functions']:raise ValueError('Effect lifetime replaces an original complete policy record')
        native=records[r['address']]
        ins=decoded[r['address']]
        witnesses=[dict(site=f"0x{int(r['address'],16)+i['offset']:08X}",mnemonic=i['mnemonic'],operands=i['operands']) for i in ins]
        if (native['size']!=r['size'] or native['body_sha256']!=r['body_sha256'] or native['cfg']!=r['cfg']
                or witnesses!=r['witnesses'] or native['authored_record']!=r['accepted_authored_record']):
            raise ValueError('Effect lifetime truncates the original complete constructed manager')
    for r in ctx['prior_policy']['anchors']:
        if r not in plan['anchors']:raise ValueError('Effect lifetime replaces its original entire fighter parent')
        native=records[r['address']]
        if native['size']!=r['size'] or native['body_sha256']!=r['record']['body_sha256'] or native['authored_record']!=r['record']:
            raise ValueError('Effect lifetime truncates its independent original fighter parent')
    fs={r['address']:r for r in rows('functions.csv')};eh=module('effect_lifetime_frames','compiler_eh.py')
    for frame in ctx['frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('Effect lifetime loses a real whole lifetime frame')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in fs},set())
    if m['historical_snapshots']:raise ValueError('Effect lifetime selected original snapshot audit differs')


def replay_retained_scope(m,scope_name):
    """Run the unchanged entire old cold proof with its explicitly guarded history view."""
    verify_plan(m)
    scopes=[r for r in m['retained_replays']['scopes'] if r['evidence_id']==scope_name]
    if len(scopes)!=1:raise ValueError('Effect lifetime retained scope is not unique')
    scope=scopes[0];path=ROOT/scope['path'];plan=json.loads(path.read_text())
    old=module('effect_lifetime_retained_'+scope_name,Path(scope['script']).name)
    if (digest(path.read_bytes())!=scope['manifest_sha256'] or old.MANIFEST_SHA256!=scope['manifest_sha256']
            or digest((ROOT/scope['script']).read_bytes())!=scope['script_sha256']):
        raise ValueError('Effect lifetime changes original whole retained script/source plan')
    old.verify_plan(plan);transitions=retained_transitions(m,scope)
    for q in scope['transitions']:
        if q['snapshot']!=plan['snapshots'][q['snapshot_index']]:
            raise ValueError('Effect lifetime changes an old literal scoped snapshot')
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
    extra=module('effect_lifetime_carrier','sdk_x3d_carriers.py');inventory=module('effect_lifetime_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('effect_lifetime_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Effect lifetime entire emission differs')
    definitions=coff.parse_symbols(body,c.coff_name)[1]
    if [weak.read_weak_reference(body,d['symbol'],c,coff,0) for d in definitions if d['storage']==105]!=ctl['weak_references']:raise ValueError('Effect lifetime real weak references differ')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:raise ValueError('Effect lifetime whole COFF/AUX/source differs')
        sections[r['section']]=(raw,fields)
    providers={r['symbol']:r for r in ctl['providers']}
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];source=next(q['source'] for q in ctl['sections'] if q['section']==r['section'])
        if r['source_definition'] not in source['definitions']:raise ValueError('Effect lifetime genuine source definition differs')
        for f,b in zip(fields,r['bindings']):
            p=providers[f['symbol']]
            if p['address']!=b['target']:raise ValueError('Effect lifetime field loses coherent whole provider')
            if p['section']:
                if (f['symbol_section'],f['symbol_offset'])!=(p['section'],p['offset']):raise ValueError('Effect lifetime field substitutes fresh defining section/offset')
            elif f['symbol_section']:raise ValueError('Effect lifetime external loses actual declaration')
        linked,proof=bind(raw,fields,int(r['address'],16),r['bindings'],flow,r['roots'])
        if proof!=r['linked_flow']:raise ValueError('Effect lifetime complete linked control flow differs')
        compare_whole(r,linked,c.pe_bytes_at(target,int(r['address'],16),r['target_size']))
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:raise ValueError('Effect lifetime whole generic layout differs')


def replay(m,evidence_only=False):
    c=module('effect_lifetime_target','compare-coff-function.py');coff=module('effect_lifetime_coff','coff_data.py');flow=module('effect_lifetime_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Effect lifetime target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Effect lifetime retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for scope in m['retained_replays']['scopes']:
        command=("import importlib.util,json;from pathlib import Path;"
            "s=importlib.util.spec_from_file_location('lifetime_retained',Path('scripts/verify-effect-manager-lifetime-origins.py'));"
            "v=importlib.util.module_from_spec(s);s.loader.exec_module(v);"
            "v.replay_retained_scope(json.loads(Path(v.EVIDENCE).read_text()),"+repr(scope['evidence_id'])+")")
        r=subprocess.run([str(ROOT/'scripts/repo-python'),'-c',command],cwd=ROOT,capture_output=True,text=True)
        if r.returncode:raise ValueError('Effect lifetime entire original retained cold proof failed: '+r.stderr[-1800:])
        print(r.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-effect-manager-lifetime-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'EffectManagerLifetime.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Effect lifetime cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Effect lifetime immutable manifest differs')
    replay(m,args.evidence_only)
    print('R244:one whole authored effect-manager destruction85; custom owned-pointer cleanup precedes complete four-deque array destruction, scalar deleting pair and whole registered cleanup/handler/metadata; ordinary implicit/empty32 negatives; entire unchanged R166 cold proof with twelve checked historical successor pairs; geometry empty constructors retain unknown; no private original layout/ABI/source/mapping/exact credit.')

if __name__=='__main__':main()
