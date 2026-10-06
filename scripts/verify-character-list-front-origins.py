#!/usr/bin/env python3
"""Cold-replay whole character list front source chains and complete character-record context."""
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
BASE=module('character_front_common','verify-archive-catalog-use-origins.py')
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
bind=BASE.bind
EVIDENCE='config/character-list-front-origin-evidence.json'
MANIFEST_SHA256='2cdf210897cd45171f52cddccd7440d31959ec116356281f435cf39bdd29d818'
PLAN_DIGESTS={'evidence_id': '7e65daa131cb28269974e7309d37e5e2fef0eea4558c38f11e991deb27826870', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'a49db23f1341bcf9cd381833451780b26ff57fda716dd86b09e67e19472f9cca', 'anchors': '115c242b15144ae905f37917aff2176914fba004469637d51bb3cb89daf836ba', 'context': 'd5fcccf5a57423d8c837d7de4952c503e107060024f5241fcb1e16670f943636', 'canonical': 'bfde3e21824da35915920775619f20a3a338dfd1032f46d373fe32ff73f010c2', 'unselected_sha256': '461bad1b4450638c188773c2cb40580ea5e36426443d7a9c07a665861c77df82', 'public_control': '58bf965925ae5b8ed7816eba70afb0a6b4528d8d3ab903ca656ebbf50fc9613e', 'retained_replays': '2804c5f4b9800c1325749b0c167e99f7fdec72bf53e7fd75015c8b667c95c41e', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': 'f416e2e2727525a2dbe4b2e4251c62916143e8f08360b501ff90f50506c095c5', 'interpretation': '3ddfb17b2e4a26542be140a53eac174b909e92fb88056062c737370ee2607dd1'}
WHOLE={'0x00540220':32,'0x00540240':19,'0x00540260':25}
CONFIDENCE='whole-vc71-character-list-front-source-chain-with-independent-container-provenance-and-record-consumption'


def included_headers(output):
    """Bind the actual relative /I probes include to the fixed repository cwd."""
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        value=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()=='z:/':path=Path(value[2:])
        elif value in ['probes/VC7CharacterListPolicies.cpp','probes/VC7ArchiveListPolicies.cpp','probes/VC7ListIteratorPolicies.cpp','probes/VC7ListPolicyDependencies.cpp','probes/VC7GameContextPolicies.cpp']:path=ROOT/value
        else:raise ValueError('Character front include loses its actual fixed host/cwd mapping')
        relative=str(path.relative_to(ROOT))
        if relative not in ['probes/VC7CharacterListPolicies.cpp','probes/VC7ArchiveListPolicies.cpp','probes/VC7ListIteratorPolicies.cpp','probes/VC7ListPolicyDependencies.cpp','probes/VC7GameContextPolicies.cpp'] and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Character front imports unrelated source')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Character front immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Character front complete immutable evidence differs: '+k)
    if m['evidence_id']!='R243' or {r['address']:r['size'] for r in m['functions']}!=WHOLE or m['historical_snapshots']:
        raise ValueError('Character front bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','status','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='library' or new['status']!='excluded' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='VC7STL',
                    disposition='exclude',confidence=CONFIDENCE,evidence_id='R243')):
            raise ValueError('Character front gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Character front original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Character front scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('character_front_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,at,flow)!=r['instructions'] or cfg!=r['cfg']:
            raise ValueError('Character front whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Character front original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Character front full original switch records differ')
    ctx=m['context']
    for a,witnesses in ctx['witnesses'].items():
        BASE.BASE.require(records[a]['instructions'],{int(k):tuple(v) for k,v in witnesses.items()})
    imports=module('character_front_imports','verify-import-origins.py').pe_imports(target,c)
    for r in ctx['imports']:
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('Character front actual file import differs')
    old=module('character_front_original','verify-character-list-policy-origins.py');plan=json.loads((ROOT/ctx['prior_policy']['path']).read_text())
    old.verify_plan(plan)
    for r in ctx['prior_policy']['functions']:
        if r not in plan['functions']:raise ValueError('Character front replaces original whole list provenance')
        native=records[r['address']]
        if native['size']!=r['size'] or native['body_sha256']!=r['body_sha256'] or native['cfg']!=r['cfg']:
            raise ValueError('Character front truncates independent original container context')
    for r in ctx['header_definitions']:
        raw=(ROOT/r['path']).read_bytes();lines=raw.decode('ascii').splitlines(keepends=True)
        if digest(raw)!=r['whole_sha256'] or ''.join(lines[r['start']-1:r['end']])!=r['text']:
            raise ValueError('Character front original whole header/member definition differs')
    for r in ctx['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Character front claims external alignment')


def validate_bindings(r,fields,owners):
    if len(fields)!=len(r['bindings']):raise ValueError('Character front omits a genuine source field')
    for f,b in zip(fields,r['bindings']):
        symbol=f['symbol'];provider=symbol
        for alternative in r.get('compatible_declarations',[]):
            if symbol==alternative['symbol']:
                if f['symbol_section'] or f['symbol_type']!=32 or f['symbol_storage']!=2:
                    raise ValueError('Character front ordinary alternative loses its genuine external declaration')
                provider=alternative['provider_symbol']
        if provider not in owners or owners[provider]!=b['target']:
            raise ValueError('Character front field has no whole independently defined operation provider')
        if f['type']!='REL32' or f['addend']!=0:
            raise ValueError('Character front false call type/addend')


def compare_whole(r,linked,target_bytes):
    if len(linked)!=r['source_size'] or len(target_bytes)!=r['target_size']:
        raise ValueError('Character front alternative crops source or target extent')
    if r['role']=='positive':
        if len(linked)!=len(target_bytes) or linked!=target_bytes:raise ValueError('Character front complete unmasked positive differs')
    elif r['role']=='negative':
        differences=[dict(offset=i,source=(linked[i] if i<len(linked) else None),target=(target_bytes[i] if i<len(target_bytes) else None))
            for i in range(max(len(linked),len(target_bytes))) if (linked[i] if i<len(linked) else None)!=(target_bytes[i] if i<len(target_bytes) else None)]
        if linked==target_bytes or differences!=r['differences']:
            raise ValueError('Character front alternative masks or discards complete genuine differences')
    else:raise ValueError('Character front source alternative role differs')


def project_rows(name,actual,transitions):
    """Return literal historical pairs only after exact accepted-successor readback."""
    if name not in ['functions.csv','function-origins.csv']:return actual
    kind='function' if name=='functions.csv' else 'origin';out=[];seen=set()
    for row in actual:
        a=row['address']
        if a in transitions:
            transition=transitions[a]
            if row!=transition['accepted_'+kind]:
                raise ValueError('Character front historical view accepts an unapproved current transition')
            out.append(transition['original_'+kind]);seen.add(a)
        else:out.append(row)
    if seen!=set(transitions):raise ValueError('Character front historical view loses a complete successor pair')
    return out


def retained_transitions(m,scope):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};transitions={}
    for q in scope['transitions']:
        successor=m['retained_replays']['successors'][q['successor_index']]
        owner=module('character_front_successor_'+successor['evidence_id'],Path(successor['script']).name)
        path=ROOT/successor['path'];plan=json.loads(path.read_text())
        if (digest(path.read_bytes())!=successor['manifest_sha256']
                or owner.MANIFEST_SHA256!=successor['manifest_sha256']
                or digest((ROOT/successor['script']).read_bytes())!=successor['script_sha256']):
            raise ValueError('Character front successor whole proof identity differs')
        owner.verify_plan(plan)
        matches=[r for r in plan['functions'] if r['address']==q['address']]
        if len(matches)!=1 or matches[0]!=q['record']:
            raise ValueError('Character front successor has no exact bounded complete transition')
        r=matches[0]
        if (q['snapshot']['function']!=r['original_function'] or q['snapshot']['origin']!=r['original_origin']
                or fs[r['address']]!=r['accepted_function'] or os[r['address']]!=r['accepted_origin']):
            raise ValueError('Character front rewrites a literal old unknown or current accepted pair')
        transitions[r['address']]=r
    return transitions


def replay_retained_scope(m,scope_name):
    """Run the unchanged entire old cold proof with its explicitly guarded history view."""
    verify_plan(m)
    scopes=[r for r in m['retained_replays']['scopes'] if r['evidence_id']==scope_name]
    if len(scopes)!=1:raise ValueError('Character front retained scope is not unique')
    scope=scopes[0];path=ROOT/scope['path'];plan=json.loads(path.read_text())
    old=module('character_front_retained_'+scope_name,Path(scope['script']).name)
    if (digest(path.read_bytes())!=scope['manifest_sha256'] or old.MANIFEST_SHA256!=scope['manifest_sha256']
            or digest((ROOT/scope['script']).read_bytes())!=scope['script_sha256']):
        raise ValueError('Character front changes original whole retained script/source plan')
    old.verify_plan(plan);transitions=retained_transitions(m,scope)
    for q in scope['transitions']:
        if q['snapshot']!=plan['snapshots'][q['snapshot_index']]:
            raise ValueError('Character front changes an old literal scoped snapshot')
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
    extra=module('character_front_source_carrier','sdk_x3d_carriers.py');inventory=module('character_front_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('character_front_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Character front full code/data/AUX/field emission differs')
    definitions=coff.parse_symbols(body,c.coff_name)[1]
    actual_weak=[weak.read_weak_reference(body,d['symbol'],c,coff,0) for d in definitions if d['storage']==105]
    if actual_weak!=ctl['weak_references']:raise ValueError('Character front real weak AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Character front whole source/COFF/AUX differs')
        sections[r['section']]=(raw,fields)
    owners={};provider_sections={}
    for r in ctl['providers']:
        source=next(s['source'] for s in ctl['sections'] if s['section']==r['section'])
        definitions=[d for d in source['definitions'] if d['symbol']==r['symbol'] and d['type']==32 and d['storage']==2]
        if len(definitions)!=1 or definitions[0]['offset'] or not source['flags']&0x20 or not source['flags']&0x1000:
            raise ValueError('Character front source loses its complete unique defining method')
        raw,fields=sections[r['section']]
        if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or 'CharacterValueObservation' not in r['symbol']:
            raise ValueError('Character front imports a wrong whole payload/source family')
        owners[r['symbol']]=r['address'];provider_sections[r['symbol']]=r['section']
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];validate_bindings(r,fields,owners)
        source=next(s['source'] for s in ctl['sections'] if s['section']==r['section'])
        if r['source_definition'] not in source['definitions'] or r['source_definition']['offset'] or r['source_definition']['type']!=32 or r['source_definition']['storage']!=2:
            raise ValueError('Character front source comparison lacks a full defining method')
        if not r.get('compatible_declarations'):
            for f in fields:
                if (f['symbol_section']!=provider_sections[f['symbol']] or f['symbol_offset'] or f['symbol_storage']!=2 or f['symbol_type']!=32):
                    raise ValueError('Character front real call does not bind its complete fresh defining owner')
        linked,proof=bind(raw,fields,int(r['address'],16),r['bindings'],flow,[0])
        if proof!=r['linked_flow']:raise ValueError('Character front whole alternative CFG differs')
        compare_whole(r,linked,c.pe_bytes_at(target,int(r['address'],16),r['target_size']))
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:
            raise ValueError('Character front generic sizeof observations invent a private layout')


def replay(m,evidence_only=False):
    c=module('character_front_target','compare-coff-function.py');coff=module('character_front_coff','coff_data.py');flow=module('character_front_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Character front target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Character front retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for scope in m['retained_replays']['scopes']:
        command=("import importlib.util,json;from pathlib import Path;"
            "p=Path('scripts/verify-character-list-front-origins.py');"
            "s=importlib.util.spec_from_file_location('character_front_retained_entry',p);"
            "v=importlib.util.module_from_spec(s);s.loader.exec_module(v);"
            "v.replay_retained_scope(json.loads(Path(v.EVIDENCE).read_text()),"+repr(scope['evidence_id'])+")")
        result=subprocess.run([str(ROOT/'scripts/repo-python'),'-c',command],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Character front full retained cold source proof failed: '+scope['evidence_id']+'\n'+result.stderr[-1800:])
        if result.stdout.strip():print(result.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-character-list-front-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'CharacterListFront.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Character front cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Character front immutable manifest differs')
    replay(m,args.evidence_only)
    print('R243:three whole library character list front/dereference operations76; complete unmasked SDK front/begin/dereference source-owner closure, independent original character-list provenance and whole39999-byte consumer; entire ordinary front32 remains equivalent; complete original R170 cold proof with nine checked successor pairs; opaque payload11 remains unknown; no source/private layout/ABI/mapping/exact credit.')

if __name__=='__main__':main()
