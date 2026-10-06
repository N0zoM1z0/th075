#!/usr/bin/env python3
"""Cold-replay whole archive iterator source chains and complete file-iteration context."""
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
BASE=module('archive_iterator_common','verify-archive-catalog-use-origins.py')
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
bind=BASE.bind
EVIDENCE='config/archive-iterator-operation-origin-evidence.json'
MANIFEST_SHA256='f371d0c970a5a893cd3ce367c8a8a9267af0fb7de3739ed8930bd884ff5a366c'
PLAN_DIGESTS={'evidence_id': '5cb8d08f9cb1c8ad1b9713e03c303d617c659fb4c8210843159312458cc42aa8', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '5f3f63f773c4b2d25809db65fdbeaa35ccf298d019ebbaf13579b9cbb905fe75', 'anchors': '8eb43d5964af62494e87b4e891d72c66f6160ad29fe351e427cafba5c1ccf37a', 'context': '50c67e4613f687246968d8346bd4c0f4a86559635ded6a4bb5e109c78e87ebe9', 'canonical': 'b52a40821dc08884ede03ac1c6d6cd31bd98bf90d283b70590e02f59608babba', 'unselected_sha256': 'fb3a1e1493b2e145bb60d7c4e1f3a092459972971b95acdc4e9befecee28fb59', 'public_control': 'ecffc979821826fb36c2e32d3d6825162b691dd5ef8b872273de0059b665f390', 'retained_replays': 'f01936f320cd5b20fb9cbabf5953634310828206b691d1d46e7644795470a6e8', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': '23f75a02b04319229a0d4dc1a473e7487e5e04ac6afad23c52d0b161250ecc2c', 'interpretation': '785e0649e48a7731bd1fc2b872ada3d4e6af074738fd123908c8ea90523e9050'}
WHOLE={'0x0041E060':19,'0x0041E080':42,'0x0041EF20':19,'0x0041EF40':22,'0x0041F790':25,'0x0041F7B0':35}
CONFIDENCE='whole-vc71-archive-iterator-source-chain-with-independent-container-provenance-and-file-iteration-context'


def included_headers(output):
    """Bind the actual relative /I probes include to the fixed repository cwd."""
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        value=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()=='z:/':path=Path(value[2:])
        elif value in ['probes/VC7ArchiveListPolicies.cpp','probes/VC7ListIteratorPolicies.cpp','probes/VC7ListPolicyDependencies.cpp','probes/VC7GameContextPolicies.cpp']:path=ROOT/value
        else:raise ValueError('Archive iterator include loses its actual fixed host/cwd mapping')
        relative=str(path.relative_to(ROOT))
        if relative not in ['probes/VC7ArchiveListPolicies.cpp','probes/VC7ListIteratorPolicies.cpp','probes/VC7ListPolicyDependencies.cpp','probes/VC7GameContextPolicies.cpp'] and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Archive iterator imports unrelated source')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Archive iterator immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Archive iterator complete immutable evidence differs: '+k)
    if m['evidence_id']!='R242' or {r['address']:r['size'] for r in m['functions']}!=WHOLE or m['historical_snapshots']:
        raise ValueError('Archive iterator bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','status','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='library' or new['status']!='excluded' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='VC7STL',
                    disposition='exclude',confidence=CONFIDENCE,evidence_id='R242')):
            raise ValueError('Archive iterator gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Archive iterator original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Archive iterator scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('archive_iterator_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,at,flow)!=r['instructions'] or cfg!=r['cfg']:
            raise ValueError('Archive iterator whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Archive iterator original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Archive iterator full original switch records differ')
    ctx=m['context']
    for a,witnesses in ctx['witnesses'].items():
        BASE.BASE.require(records[a]['instructions'],{int(k):tuple(v) for k,v in witnesses.items()})
    imports=module('archive_iterator_imports','verify-import-origins.py').pe_imports(target,c)
    for r in ctx['imports']:
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('Archive iterator actual file import differs')
    old=module('archive_iterator_original','verify-archive-list-policy-origins.py');plan=json.loads((ROOT/ctx['prior_policy']['path']).read_text())
    old.verify_plan(plan)
    for r in ctx['prior_policy']['functions']:
        if r not in plan['functions']:raise ValueError('Archive iterator replaces original whole list provenance')
        native=records[r['address']]
        if native['size']!=r['size'] or native['body_sha256']!=r['body_sha256'] or native['cfg']!=r['cfg']:
            raise ValueError('Archive iterator truncates independent original container context')
    for r in ctx['header_definitions']:
        raw=(ROOT/r['path']).read_bytes();lines=raw.decode('ascii').splitlines(keepends=True)
        if digest(raw)!=r['whole_sha256'] or ''.join(lines[r['start']-1:r['end']])!=r['text']:
            raise ValueError('Archive iterator original whole header/member definition differs')
    for r in ctx['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Archive iterator claims external alignment')


def validate_bindings(r,fields,owners):
    if len(fields)!=len(r['bindings']):raise ValueError('Archive iterator omits a genuine source field')
    for f,b in zip(fields,r['bindings']):
        symbol=f['symbol'];provider=symbol
        for alternative in r.get('compatible_declarations',[]):
            if symbol==alternative['symbol']:
                if f['symbol_section'] or f['symbol_type']!=32 or f['symbol_storage']!=2:
                    raise ValueError('Archive iterator ordinary alternative loses its genuine external declaration')
                provider=alternative['provider_symbol']
        if provider not in owners or owners[provider]!=b['target']:
            raise ValueError('Archive iterator field has no whole independently defined operation provider')
        if f['type']!='REL32' or f['addend']!=0:
            raise ValueError('Archive iterator false call type/addend')


def compare_whole(r,linked,target_bytes):
    if len(linked)!=r['source_size'] or len(target_bytes)!=r['target_size']:
        raise ValueError('Archive iterator alternative crops source or target extent')
    if r['role']=='positive':
        if len(linked)!=len(target_bytes) or linked!=target_bytes:raise ValueError('Archive iterator complete unmasked positive differs')
    elif r['role']=='negative':
        differences=[dict(offset=i,source=(linked[i] if i<len(linked) else None),target=(target_bytes[i] if i<len(target_bytes) else None))
            for i in range(max(len(linked),len(target_bytes))) if (linked[i] if i<len(linked) else None)!=(target_bytes[i] if i<len(target_bytes) else None)]
        if linked==target_bytes or differences!=r['differences']:
            raise ValueError('Archive iterator alternative masks or discards complete genuine differences')
    else:raise ValueError('Archive iterator source alternative role differs')


def project_rows(name,actual,transitions):
    """Return literal historical pairs only after exact accepted-successor readback."""
    if name not in ['functions.csv','function-origins.csv']:return actual
    kind='function' if name=='functions.csv' else 'origin';out=[];seen=set()
    for row in actual:
        a=row['address']
        if a in transitions:
            transition=transitions[a]
            if row!=transition['accepted_'+kind]:
                raise ValueError('Archive iterator historical view accepts an unapproved current transition')
            out.append(transition['original_'+kind]);seen.add(a)
        else:out.append(row)
    if seen!=set(transitions):raise ValueError('Archive iterator historical view loses a complete successor pair')
    return out


def retained_transitions(m,scope):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};transitions={}
    for q in scope['transitions']:
        successor=m['retained_replays']['successors'][q['successor_index']]
        owner=module('archive_iterator_successor_'+successor['evidence_id'],Path(successor['script']).name)
        path=ROOT/successor['path'];plan=json.loads(path.read_text())
        if (digest(path.read_bytes())!=successor['manifest_sha256']
                or owner.MANIFEST_SHA256!=successor['manifest_sha256']
                or digest((ROOT/successor['script']).read_bytes())!=successor['script_sha256']):
            raise ValueError('Archive iterator successor whole proof identity differs')
        owner.verify_plan(plan)
        matches=[r for r in plan['functions'] if r['address']==q['address']]
        if len(matches)!=1 or matches[0]!=q['record']:
            raise ValueError('Archive iterator successor has no exact bounded complete transition')
        r=matches[0]
        if (q['snapshot']['function']!=r['original_function'] or q['snapshot']['origin']!=r['original_origin']
                or fs[r['address']]!=r['accepted_function'] or os[r['address']]!=r['accepted_origin']):
            raise ValueError('Archive iterator rewrites a literal old unknown or current accepted pair')
        transitions[r['address']]=r
    return transitions


def replay_retained_scope(m,scope_name):
    """Run the unchanged entire old cold proof with its explicitly guarded history view."""
    verify_plan(m)
    scopes=[r for r in m['retained_replays']['scopes'] if r['evidence_id']==scope_name]
    if len(scopes)!=1:raise ValueError('Archive iterator retained scope is not unique')
    scope=scopes[0];path=ROOT/scope['path'];plan=json.loads(path.read_text())
    old=module('archive_iterator_retained_'+scope_name,Path(scope['script']).name)
    if (digest(path.read_bytes())!=scope['manifest_sha256'] or old.MANIFEST_SHA256!=scope['manifest_sha256']
            or digest((ROOT/scope['script']).read_bytes())!=scope['script_sha256']):
        raise ValueError('Archive iterator changes original whole retained script/source plan')
    old.verify_plan(plan);transitions=retained_transitions(m,scope)
    for q in scope['transitions']:
        if q['snapshot']!=plan['snapshots'][q['snapshot_index']]:
            raise ValueError('Archive iterator changes an old literal scoped snapshot')
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
    extra=module('archive_iterator_source_carrier','sdk_x3d_carriers.py');inventory=module('archive_iterator_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('archive_iterator_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Archive iterator full code/data/AUX/field emission differs')
    definitions=coff.parse_symbols(body,c.coff_name)[1]
    actual_weak=[weak.read_weak_reference(body,d['symbol'],c,coff,0) for d in definitions if d['storage']==105]
    if actual_weak!=ctl['weak_references']:raise ValueError('Archive iterator real weak AUX/fallback differs')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:
            raise ValueError('Archive iterator whole source/COFF/AUX differs')
        sections[r['section']]=(raw,fields)
    owners={};provider_sections={}
    for r in ctl['providers']:
        source=next(s['source'] for s in ctl['sections'] if s['section']==r['section'])
        definitions=[d for d in source['definitions'] if d['symbol']==r['symbol'] and d['type']==32 and d['storage']==2]
        if len(definitions)!=1 or definitions[0]['offset'] or not source['flags']&0x20 or not source['flags']&0x1000:
            raise ValueError('Archive iterator source loses its complete unique defining method')
        raw,fields=sections[r['section']]
        if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or 'ArchiveValueObservation' not in r['symbol']:
            raise ValueError('Archive iterator imports a wrong whole payload/source family')
        owners[r['symbol']]=r['address'];provider_sections[r['symbol']]=r['section']
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];validate_bindings(r,fields,owners)
        source=next(s['source'] for s in ctl['sections'] if s['section']==r['section'])
        if r['source_definition'] not in source['definitions'] or r['source_definition']['offset'] or r['source_definition']['type']!=32 or r['source_definition']['storage']!=2:
            raise ValueError('Archive iterator source comparison lacks a full defining method')
        if not r.get('compatible_declarations'):
            for f in fields:
                if (f['symbol_section']!=provider_sections[f['symbol']] or f['symbol_offset'] or f['symbol_storage']!=2 or f['symbol_type']!=32):
                    raise ValueError('Archive iterator real call does not bind its complete fresh defining owner')
        linked,proof=bind(raw,fields,int(r['address'],16),r['bindings'],flow,[0])
        if proof!=r['linked_flow']:raise ValueError('Archive iterator whole alternative CFG differs')
        compare_whole(r,linked,c.pe_bytes_at(target,int(r['address'],16),r['target_size']))
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:
            raise ValueError('Archive iterator generic sizeof observations invent a private layout')


def replay(m,evidence_only=False):
    c=module('archive_iterator_target','compare-coff-function.py');coff=module('archive_iterator_coff','coff_data.py');flow=module('archive_iterator_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Archive iterator target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Archive iterator retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for scope in m['retained_replays']['scopes']:
        command=("import importlib.util,json;from pathlib import Path;"
            "p=Path('scripts/verify-archive-iterator-operation-origins.py');"
            "s=importlib.util.spec_from_file_location('archive_iterator_retained_entry',p);"
            "v=importlib.util.module_from_spec(s);s.loader.exec_module(v);"
            "v.replay_retained_scope(json.loads(Path(v.EVIDENCE).read_text()),"+repr(scope['evidence_id'])+")")
        result=subprocess.run([str(ROOT/'scripts/repo-python'),'-c',command],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('Archive iterator full retained cold source proof failed: '+scope['evidence_id']+'\n'+result.stderr[-1800:])
        if result.stdout.strip():print(result.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-archive-iterator-operation-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'ArchiveIteratorOperations.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Archive iterator cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Archive iterator immutable manifest differs')
    replay(m,args.evidence_only)
    print('R242:six whole library archive iterator operations162; complete unmasked arrow/dereference and postfix/prefix source-owner chains, independent complete list and archive write/named-seek context; whole ordinary19/42 alternatives retained; entire historical R169 cold replay with eight verified successor pairs; opaque node helpers stay unknown; no original private type/layout/ABI/source/mapping or exact credit.')

if __name__=='__main__':main()
