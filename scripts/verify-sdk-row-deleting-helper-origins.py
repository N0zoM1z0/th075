#!/usr/bin/env python3
"""Recheck original SDK compiler deleting scaffold and honest cold source alternatives."""
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
BASE=module('row_deletion_common','verify-guarded-sprite-list-origins.py')
HISTORY=module('row_deletion_history','verify-character-list-front-origins.py')
bind=HISTORY.bind
compare_whole=HISTORY.compare_whole
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/sdk-row-deleting-helper-origin-evidence.json'
MANIFEST_SHA256='7f434aaf7577199ef70489680d45cbd4732a1140c3e67c032cca0fe5afa3da6d'
PLAN_DIGESTS={'evidence_id': '3d18d097a63588a29110fee04b18cf960d9989ee45185e7703417e0a1d5f84f5', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '2d9f3f6dafa0eb8a8b2118857fab610d09c68cfd9fe3157995bfb23d176bd459', 'anchors': 'f69f2f09a3c102ce9031f07df4d58fa49923429f21adaffcc2b51c0448ba860e', 'context': '7295cd3e39356acdca4ba8999a0f97357e1694896df4e92ba3501043dae9c0e8', 'archive_records': '2a7118eb0f0b61c2f6425a8169ff420768e17cd87dc05338d9f895df90db490c', 'canonical': 'd26311125b738113eeb4591f79332983ade8572d998cd884170c2dedac2ecf7d', 'unselected_sha256': 'c0b74951a64cdbe704c766299f75c7b31d265cd4cb394452054c361c03d36a57', 'public_control': '7a2b4b9909ee4ca526740a0e58eb2cef1b26c3178e69f216824281fdb6282921', 'retained_scope': '5357d46b122404d02c96bf0a5970e887926f4ea6e2185550f14df1dc35045e69', 'historical_snapshots': '467ae1500f9b2763d6281653bfe447b62a3889ded4f0f93aa3f4b6e0581a336e', 'retained_sha256': '08f422ff2391545bba3adae5c52d5fd82f12d3b886ee61addfa20699b2410f7d', 'interpretation': '85f501f216b91defc3874410682ccd51bd62c24e50f77ddb92b594b36c7c838b'}
WHOLE={'0x006114A7':76}
CONFIDENCE='whole-original-sdk-compiler-vector-deleting-scaffold-and-independent-cold-emission-with-real-array-delete-entry-difference'


def included_headers(output):
    """Bind every actual SDK include to the fixed compiler host mapping."""
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        value=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()=='z:/':path=Path(value[2:])
        elif value in ['probes/VC7GameContextPolicies.cpp']:path=ROOT/value
        else:raise ValueError('Row deletion include loses its actual fixed host/cwd mapping')
        relative=str(path.relative_to(ROOT))
        if relative not in ['probes/VC7GameContextPolicies.cpp'] and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Row deletion imports unrelated source')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Row deletion immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Row deletion complete immutable evidence differs: '+k)
    if m['evidence_id']!='R246' or {r['address']:r['size'] for r in m['functions']}!=WHOLE:
        raise ValueError('Row deletion bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','status','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='compiler' or new['status']!='excluded' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='compiler',subsystem='VC71Compiler',
                    disposition='exclude',confidence=CONFIDENCE,evidence_id='R246')):
            raise ValueError('Row deletion gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Row deletion original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Row deletion scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('row_deletion_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']};decoded={}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);ins=SOURCE.instructions(raw,at,flow)
        if a in ['0x00640F15','0x0064169D','0x006416A2','0x0065596E','0x00655976','0x00655981','0x0065598C']:
            destination={'0x00640F15':0x642a61,'0x0064169D':0x640f15,'0x006416A2':0x64159d,'0x0065596E':0x431f40,'0x00655976':0x420420,'0x00655981':0x42db80,'0x0065598C':0x4143b0}[a]
            if (ins[-1]['mnemonic']!='jmp' or ins[-1]['operands']!=hex(destination)
                    or f'0x{destination:08X}' not in records):raise ValueError('Row deletion array/scalar delete loses its independently complete bound tail')
            cfg=flow.flow(raw,at,[0],[],{at+len(raw)-4:destination},{})
        else:cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if (digest(raw)!=r['body_sha256'] or cfg!=r['cfg'] or len(ins)!=r['instruction_count']
                or metadata_digest(ins)!=r['instructions_sha256'] or (r['instructions'] is not None and ins!=r['instructions'])):
            raise ValueError('Row deletion whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Row deletion original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Row deletion full original switch records differ')
        decoded[a]=ins
    for a,witnesses in m['context']['witnesses'].items():
        BASE.BASE.BASE.require(decoded[a],{int(k):tuple(v) for k,v in witnesses.items()})
    for r in m['context']['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Row deletion claims external alignment')
    fs={r['address']:r for r in rows('functions.csv')};eh=module('row_deletion_frames','compiler_eh.py')
    for frame in m['context']['frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('Row deletion loses a real whole lifetime frame')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in fs},set())
    verify_context(m,target,c,flow)
    for r in m['historical_snapshots']:
        item=json.loads((ROOT/r['path']).read_text())
        for key in r['trail']:item=item[key]
        if item!=r['record']:raise ValueError('Row deletion rewrites an old literal selected snapshot')


def verify_control(m,body,target,c,coff,flow):
    extra=module('row_deletion_carrier','sdk_x3d_carriers.py');inventory=module('row_deletion_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('row_deletion_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Row deletion entire emission differs')
    definitions=coff.parse_symbols(body,c.coff_name)[1]
    if [weak.read_weak_reference(body,d['symbol'],c,coff,0) for d in definitions if d['storage']==105]!=ctl['weak_references']:raise ValueError('Row deletion real weak references differ')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:raise ValueError('Row deletion whole COFF/AUX/source differs')
        sections[r['section']]=(raw,fields)
    providers={r['symbol']:r for r in ctl['providers']}
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];source=next(q['source'] for q in ctl['sections'] if q['section']==r['section'])
        if r['source_definition'] not in source['definitions']:raise ValueError('Row deletion genuine source definition differs')
        for f,b in zip(fields,r['bindings']):
            p=providers[f['symbol']]
            if p['address']!=b['target']:raise ValueError('Row deletion field loses coherent whole provider')
            if p['section']:
                if (f['symbol_section'],f['symbol_offset'])!=(p['section'],p['offset']):raise ValueError('Row deletion field substitutes fresh defining section/offset')
            elif f['symbol_section']:raise ValueError('Row deletion external loses actual declaration')
        linked,proof=bind(raw,fields,int(r['address'],16),r['bindings'],flow,r['roots'])
        if proof!=r['linked_flow']:raise ValueError('Row deletion complete linked control flow differs')
        compare_whole(r,linked,c.pe_bytes_at(target,int(r['address'],16),r['target_size']))
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:raise ValueError('Row deletion whole generic layout differs')


def replay(m,evidence_only=False):
    c=module('row_deletion_target','compare-coff-function.py');coff=module('row_deletion_coff','coff_data.py');flow=module('row_deletion_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Row deletion target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Row deletion retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    code="import importlib.util;from pathlib import Path;p=Path('scripts/verify-sdk-row-deleting-helper-origins.py');s=importlib.util.spec_from_file_location('retained_row',p);v=importlib.util.module_from_spec(s);s.loader.exec_module(v);v.replay_retained("+repr(evidence_only)+")"
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'-c',code],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:raise ValueError('Row deletion whole old R198 cold proof failed: '+result.stdout[-1600:]+result.stderr[-1600:])
    print(result.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-sdk-row-deleting-helper-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'RowArrayDeletion.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Row deletion cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Row deletion immutable manifest differs')
    replay(m,args.evidence_only)
    print('R246: one complete compiler vector-deleting helper76; whole original SDK body/callback and unchanged full R198 cold main; genuine fresh E76 retains actual array-delete difference39/40/41, full callback9 matches; scalar31 and ordinary16 controls remain negative; no private SDK layout, global compiler profile, source/mapping/exact credit.')



def verify_context(m,target,c,flow):
    old=json.loads((ROOT/m['retained_scope']['path']).read_text())
    runtime=module('row_archive','verify-runtime-origins.py');coff=module('row_archive_coff','coff_data.py');extra=module('row_archive_sections','sdk_x3d_carriers.py')
    archive=(ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(archive)!=old['archive_sha256']:raise ValueError('Row deletion original SDK archive differs')
    members={o:(n,b) for o,n,b in runtime.archive_members(archive)}
    for r in m['archive_records']:
        if r not in old['sections']:raise ValueError('Row deletion replaces original complete SDK source record')
        name,body=members[r['member_offset']]
        if name!=r['member'] or digest(body)!=r['member_sha256']:raise ValueError('Row deletion original defining member differs')
        raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff)
        if fields!=r['fields'] or source!=r['source'] or digest(raw)!=r['source_sha256']:raise ValueError('Row deletion crops original source/fields/COFF/AUX')
        bindings=[dict(offset=f['offset'],type=f['type'],symbol=f['symbol'],target=b['target_address']) for f,b in zip(fields,r['bindings'])]
        linked,proof=bind(raw,fields,int(r['base'],16),bindings,flow,r['roots'])
        if linked!=c.pe_bytes_at(target,int(r['base'],16),r['size']) or digest(linked)!=r['body_sha256']:raise ValueError('Row deletion whole original typed comparison differs')


def historical_rows(name,actual,record,evidence_only):
    if name not in ['functions.csv','function-origins.csv']:return actual
    kind='function' if name=='functions.csv' else 'origin';out=[];seen=0
    for row in actual:
        if row['address']==record['address']:
            expected=record[('original' if evidence_only else 'accepted')+'_'+kind]
            if row!=expected:raise ValueError('Row deletion unapproved historical successor pair')
            row=record['original_'+kind];seen+=1
        out.append(row)
    if seen!=1:raise ValueError('Row deletion historical view loses its unique pair')
    return out


def replay_retained(evidence_only=False):
    """Run the unchanged entire R198 main with one verified read-only ledger view."""
    from types import SimpleNamespace
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Row deletion manifest identity differs')
    verify_canonical(m,evidence_only);scope=m['retained_scope'];path=ROOT/scope['path'];old=module('row_retained_R198',Path(scope['script']).name);plan=json.loads(path.read_text())
    if digest(path.read_bytes())!=scope['manifest_sha256'] or old.MANIFEST_SHA256!=scope['manifest_sha256'] or digest((ROOT/scope['script']).read_bytes())!=scope['script_sha256']:raise ValueError('Row deletion old complete script/manifest differs')
    old.verify_plan(plan);record=m['functions'][0];source=next(r for r in plan['sections'] if r['base']==record['address'])
    if (source['function'],source['origin'])!=(record['original_function'],record['original_origin']):raise ValueError('Row deletion old literal unknown pair differs')
    original_csv=old.csv
    def reader(handle,*args,**kwargs):
        parsed=list(original_csv.DictReader(handle,*args,**kwargs));path=Path(handle.name)
        if path.parent==ROOT/'config':return historical_rows(path.name,parsed,record,evidence_only)
        return parsed
    old.csv=SimpleNamespace(DictReader=reader)
    try:old.main()
    finally:old.csv=original_csv


if __name__=='__main__':main()
