#!/usr/bin/env python3
"""Cold-replay whole replay-browser cleanup policies with independent complete game context."""
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
BASE=module('browser_lifetime_common','verify-guarded-sprite-list-origins.py')
HISTORY=module('browser_lifetime_history','verify-character-list-front-origins.py')
bind=HISTORY.bind
compare_whole=HISTORY.compare_whole
SOURCE=BASE.SOURCE
rows=BASE.rows
digest=BASE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/replay-browser-lifetime-origin-evidence.json'
MANIFEST_SHA256='429dd162e34b2aa7f3762686ca535af31d782e6a70f94b2cbfc3502ebbee790a'
PLAN_DIGESTS={'evidence_id': '10a1e8b8f3a6881a3ac17e57a78e30f4563a5e88eaeb11a97977c0e2dea95e1f', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '232e7555913d7d0af76b664ac3d62511748f098f5bebf36ca3e4b88e93abbd16', 'anchors': '5f4b37dc5f41bee9f1eff3a5d14394e2748bcd543b1969d98185318471b73baa', 'context': 'f356c750c64931824065d2808df4f5ba8b0bb539fc7228c421afa7408b5b9780', 'canonical': '70c9f52a6fb17bd759c191075c299e090bab95e19a492b52cb7dd3af23dd1da4', 'unselected_sha256': '2b34df1cc6e1b77f18be77012a47ae89558137af3ce122a11a262c69a5128772', 'public_control': 'fe6336f8dfb9a3379b91d5a2209e4603faa6a4ef94246c3d20945958a5d2a1f7', 'cold_dependencies': '5465ee219e60f3a7491a2b82e7057ffaa5c95cf9d8995a19e3f2868e8ba29757', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': 'd3242c436a7c44a7e2d7823f60d2c66f76541b09aa1e954a951217d4df53a965', 'interpretation': '8dc2c33847d3f492d9461f91a3c90360086fe013ca6886e92ce9363ec33bd092'}
WHOLE={'0x0042C560':265}
CONFIDENCE='whole-replay-browser-selection-persistence-owned-array-and-child-cleanup-with-independent-filename-producer-and-registered-lifetime'


def included_headers(output):
    """Bind every actual SDK include to the fixed compiler host mapping."""
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        value=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()=='z:/':path=Path(value[2:])
        elif value in ['probes/VC7GameContextPolicies.cpp']:path=ROOT/value
        else:raise ValueError('Browser lifetime include loses its actual fixed host/cwd mapping')
        relative=str(path.relative_to(ROOT))
        if relative not in ['probes/VC7GameContextPolicies.cpp'] and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Browser lifetime imports unrelated source')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Browser lifetime immutable schema differs')
    for k,h in PLAN_DIGESTS.items():
        if metadata_digest(m[k])!=h:raise ValueError('Browser lifetime complete immutable evidence differs: '+k)
    if m['evidence_id']!='R245' or {r['address']:r['size'] for r in m['functions']}!=WHOLE:
        raise ValueError('Browser lifetime bounded whole scope differs')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];mutable={'proposed_name','module','owner','evidence','notes'}
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['signature','calling_convention','source_file'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='ReplayBrowserScene',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R245')):
            raise ValueError('Browser lifetime gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};os={r['address']:r for r in rows('function-origins.csv')};selected={r['address']:r for r in m['functions']}
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Browser lifetime original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:
            r=selected[a];state='original' if evidence_only else 'accepted';expected=dict(function=r[state+'_function'],origin=r[state+'_origin'])
        if dict(function=fs[a],origin=os[a])!=expected:raise ValueError('Browser lifetime scoped canonical ownership differs: '+a)


def verify_native(m,target,c,flow):
    auth=module('browser_lifetime_native_cfg','verify-authored-origins.py');records={r['address']:r for r in m['functions']+m['anchors']};decoded={}
    for a,r in records.items():
        at=int(a,16);raw=c.pe_bytes_at(target,at,r['size']);ins=SOURCE.instructions(raw,at,flow)
        if a in ['0x00640F15','0x0064169D','0x006416A2','0x0065596E','0x00655976','0x00655981','0x0065598C']:
            destination={'0x00640F15':0x642a61,'0x0064169D':0x640f15,'0x006416A2':0x64159d,'0x0065596E':0x431f40,'0x00655976':0x420420,'0x00655981':0x42db80,'0x0065598C':0x4143b0}[a]
            if (ins[-1]['mnemonic']!='jmp' or ins[-1]['operands']!=hex(destination)
                    or f'0x{destination:08X}' not in records):raise ValueError('Browser lifetime array/scalar delete loses its independently complete bound tail')
            cfg=flow.flow(raw,at,[0],[],{at+len(raw)-4:destination},{})
        else:cfg=list(auth.verify_body(raw,at,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))
        if (digest(raw)!=r['body_sha256'] or cfg!=r['cfg'] or len(ins)!=r['instruction_count']
                or metadata_digest(ins)!=r['instructions_sha256'] or (r['instructions'] is not None and ins!=r['instructions'])):
            raise ValueError('Browser lifetime whole native owner/CFG differs: '+a)
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Browser lifetime original independent authored record differs')
        for name,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(name) if q['address']==a]!=r[key]:raise ValueError('Browser lifetime full original switch records differ')
        decoded[a]=ins
    for a,witnesses in m['context']['witnesses'].items():
        BASE.BASE.BASE.require(decoded[a],{int(k):tuple(v) for k,v in witnesses.items()})
    for r in m['context']['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or digest(raw)!=r['sha256']:raise ValueError('Browser lifetime claims external alignment')
    fs={r['address']:r for r in rows('functions.csv')};eh=module('browser_lifetime_frames','compiler_eh.py')
    for frame in m['context']['frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('Browser lifetime loses a real whole lifetime frame')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in fs},set())
    verify_context(m,target,c,flow)
    if m['historical_snapshots']:raise ValueError('Browser lifetime selected original snapshot audit differs')


def verify_control(m,body,target,c,coff,flow):
    extra=module('browser_lifetime_carrier','sdk_x3d_carriers.py');inventory=module('browser_lifetime_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;weak=module('browser_lifetime_weak','verify-standard-exception-origins.py');ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Browser lifetime entire emission differs')
    definitions=coff.parse_symbols(body,c.coff_name)[1]
    if [weak.read_weak_reference(body,d['symbol'],c,coff,0) for d in definitions if d['storage']==105]!=ctl['weak_references']:raise ValueError('Browser lifetime real weak references differ')
    sections={}
    for r in ctl['sections']:
        raw,fields,source=extra.section_carrier(body,r['section'],c,coff)
        if SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or digest(raw)!=r['sha256']:raise ValueError('Browser lifetime whole COFF/AUX/source differs')
        sections[r['section']]=(raw,fields)
    providers={r['symbol']:r for r in ctl['providers']}
    weak_symbol='??_EReplayBrowserLifetimeObservation@@UAEPAXI@Z'
    alias=next(r for r in ctl['weak_references'] if r['symbol']==weak_symbol)
    fallback=providers[alias['fallback_symbol']]
    if (alias['source_definition']['section'] or alias['search_characteristics']!=2
            or providers[weak_symbol]['address']!=fallback['address']
            or (fallback['section'],fallback['offset'])!=(alias['fallback_definition']['section'],alias['fallback_definition']['offset'])
            or not any(r['role']=='positive' and r['source_definition']==alias['fallback_definition'] and r['source_size']==44 and r['address']==fallback['address'] for r in ctl['comparisons'])):
        raise ValueError('Browser lifetime weak E loses actual complete defining G fallback')
    for r in ctl['comparisons']:
        raw,fields=sections[r['section']];source=next(q['source'] for q in ctl['sections'] if q['section']==r['section'])
        if r['source_definition'] not in source['definitions']:raise ValueError('Browser lifetime genuine source definition differs')
        for f,b in zip(fields,r['bindings']):
            p=providers[f['symbol']]
            if p['address']!=b['target']:raise ValueError('Browser lifetime field loses coherent whole provider')
            if p['section']:
                if (f['symbol_section'],f['symbol_offset'])!=(p['section'],p['offset']):raise ValueError('Browser lifetime field substitutes fresh defining section/offset')
            elif f['symbol_section']:raise ValueError('Browser lifetime external loses actual declaration')
        linked,proof=bind(raw,fields,int(r['address'],16),r['bindings'],flow,r['roots'])
        if proof!=r['linked_flow']:raise ValueError('Browser lifetime complete linked control flow differs')
        compare_whole(r,linked,c.pe_bytes_at(target,int(r['address'],16),r['target_size']))
    for r in ctl['layouts']:
        raw=sections[r['section']][0]
        if len(raw)!=4*len(r['values']) or list(struct.unpack('<'+'I'*len(r['values']),raw))!=r['values']:raise ValueError('Browser lifetime whole generic layout differs')


def replay(m,evidence_only=False):
    c=module('browser_lifetime_target','compare-coff-function.py');coff=module('browser_lifetime_coff','coff_data.py');flow=module('browser_lifetime_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Browser lifetime target identity differs')
    for p,h in m['retained_sha256'].items():
        if digest((ROOT/p).read_bytes())!=h:raise ValueError('Browser lifetime retained input differs: '+p)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    for command in m['cold_dependencies']:
        r=subprocess.run([str(ROOT/'scripts/repo-python'),*command],cwd=ROOT,capture_output=True,text=True)
        if r.returncode:raise ValueError('Browser lifetime whole retained cold proof failed: '+r.stderr[-1800:])
        print(r.stdout.strip())
    ctl=m['public_control'];scratch=ROOT/'build/origin-replay-browser-lifetime-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'ReplayBrowserLifetime.obj';r=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if r.returncode or included_headers(r.stdout+r.stderr)!=ctl['headers']:raise ValueError('Browser lifetime cold compiler/header proof failed; no cached fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Browser lifetime immutable manifest differs')
    replay(m,args.evidence_only)
    print('R245:one whole authored replay browser destruction265; real saved selection, owned filename arrays and child cleanup with full producer/selector/initializer, three observed table slots and complete EH/shared metadata; fresh explicit265 and genuine implicit/empty controls; whole old deque/destructor cold graph preserved; no original private layout/ABI/source/mapping/exact credit.')



def verify_context(m,target,c,flow):
    ctx=m['context'];permissions=module('browser_lifetime_permissions','verify-sdk-x3d-origins.py')
    records={r['address']:r for r in m['functions']+m['anchors']}
    for r in ctx['carriers']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if digest(raw)!=r['sha256'] or permissions.image_permissions(target,int(r['address'],16),r['size'])!=r['permissions']:raise ValueError('Browser lifetime complete original EH/table/data carrier differs')
        if r.get('instructions') and SOURCE.instructions(raw,int(r['address'],16),flow)!=r['instructions']:raise ValueError('Browser lifetime whole shared EH instructions differ')
    for r in ctx['imports']:
        imports=module('browser_lifetime_imports','verify-import-origins.py').pe_imports(target,c)
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('Browser lifetime actual file API differs')
    for r in ctx['strings']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if digest(raw)!=r['sha256'] or raw[:-1].decode('cp932')!=r['text'] or raw[-1:]!=b'\0':raise ValueError('Browser lifetime full replay file wildcard differs')
    if ctx['table']['words']!=['0x0042DAC0','0x0042C670','0x0042CA60']:raise ValueError('Browser lifetime observed table loses deleting/selection/render callbacks')
    raw=c.pe_bytes_at(target,int(ctx['table']['address'],16),12)
    if [f'0x{x:08X}' for x in struct.unpack('<3I',raw)]!=ctx['table']['words']:raise ValueError('Browser lifetime actual original table pointers differ')

if __name__=='__main__':main()
