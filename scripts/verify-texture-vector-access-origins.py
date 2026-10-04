#!/usr/bin/env python3
"""Cold-replay full texture-vector access/erase graph with independent whole policies."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('texture_vector_prior',ROOT/'scripts/verify-replay-deque-front-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/texture-vector-access-origin-evidence.json'
MANIFEST_SHA256='69e2d6a01358b088121cef02d4153cf307429921dc0b1ac8d2891ccb732297a3'
CONFIDENCE='complete-vc7-texture-vector-access-size-erase-and-whole-game-context'
KEYS={'0x0040DCE0': 31, '0x0040DD00': 31, '0x0040DD60': 49, '0x0040DFD0': 45, '0x0040E4A0': 28, '0x0040E4C0': 19, '0x0040E4E0': 32}
LAYOUT=[44,16,4,4,16,1]
EXTERNAL={'??1TextureAccessObservation@@QAE@XZ': '0x0040D8E0', '??3@YAXPAX@Z': '0x00640F15'}
PROTECTED=dict(PRIOR.PRIOR.PRIOR.PROTECTED,**{'0x0040E9B0': 16, '0x0040E000': 158})
ORDINARY=[('0x0040DCE0', 31, '?begin@OrdinaryTextureAccess@@QAE?AViterator@?$vector@UTextureAccessObservation@@V?$allocator@UTextureAccessObservation@@@std@@@std@@XZ', ['0x0040E4A0']), ('0x0040DD00', 31, '?end@OrdinaryTextureAccess@@QAE?AViterator@?$vector@UTextureAccessObservation@@V?$allocator@UTextureAccessObservation@@@std@@@std@@XZ', ['0x0040E4A0']), ('0x0040DD60', 49, '?entry@OrdinaryTextureAccess@@QAEAAUTextureAccessObservation@@I@Z', ['0x0040DCE0', '0x0040DFD0', '0x0040E4C0'])]
ROUTES={'0x0040DCE0': ['0x0040E4A0'], '0x0040DD00': ['0x0040E4A0'], '0x0040DD60': ['0x0040DCE0', '0x0040DFD0', '0x0040E4C0'], '0x0040DFD0': ['0x0040E4E0'], '0x0040DD20': [], '0x0040DDC0': ['0x0040E500', '0x0040F270', '0x0040E120'], '0x0040E4A0': ['0x0040E990'], '0x0040E4C0': ['0x0040E9B0'], '0x0040E4E0': [], '0x0040E500': ['0x0040E9C0'], '0x0040F270': ['0x0040F5A0', '0x0040F5B0'], '0x0040E120': ['0x0040F2B0'], '0x0040E990': [], '0x0040E9B0': [], '0x0040E9C0': [], '0x0040F5A0': [], '0x0040F5B0': [], '0x0040F2B0': ['0x0040F5A0', '0x0040F5F0'], '0x0040F5F0': ['0x0040F860'], '0x0040F860': ['0x0040F9F0'], '0x0040F9F0': ['0x0040FA00'], '0x0040FA00': ['0x0040D8E0', '0x00640F15']}


def manifest():return json.loads((ROOT/EVIDENCE).read_text())


def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        text=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if text[:3].lower()!='z:/':raise ValueError('replay include loses actual host mapping')
        path=Path(text[2:]);relative=str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):raise ValueError('replay gains unrelated include owner')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if (m['evidence_id']!='R173' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7TextureVectorAccess.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=27 or len(m['functions'])!=7 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=25 or sum(r['size'] for r in m['controls'])!=926
            or sum(len(r['bindings']) for r in m['controls'])!=27 or len(m['emission'])!=35
            or sum(r['size'] for r in m['emission'])!=1129 or len(m['snapshots'])!=55 or len(m['retained'])!=5
            or m['layout'] not in m['emission'] or m['layout']['size']!=24 or m['layout_values']!=LAYOUT or m['external']!=EXTERNAL):
        raise ValueError('texture vector loses bounded whole source/field/emission/layout scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];control=next(x for x in m['controls'][:22] if x['address']==a)
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!='VC7STL' or new['status']!='excluded' or new['owner']!='library' or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R173')
                or r['symbol']!=control['source_definition']['symbol'] or r['body_sha256']!=control['body_sha256'] or r['cfg']!=control['cfg'] or not r['witnesses']):
            raise ValueError('texture vector loses own SDK owner or adds false source/private ABI/exact credit')
    if [(r['address'],r['size']) for r in m['controls'][:6]]!=[('0x0040DCE0',31),('0x0040DD00',31),('0x0040DD60',49),('0x0040DFD0',45),('0x0040DD20',57),('0x0040DDC0',99)]:
        raise ValueError('texture vector loses whole index/arithmetic/size/erase roots')
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition'];kind='compiler-code' if r['address']=='0x0040FA00' else 'code';role='byte-equal-ordinary-alternative' if i>=22 else 'retained-whole-compiler-context' if kind=='compiler-code' else 'closed-whole-sdk-context'
        if (r['kind']!=kind or r['role']!=role or ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])):
            raise ValueError('texture vector slices entire defining source or substitutes a different owner')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type']!='REL32' or f['offset']+4>r['size']:
                raise ValueError('texture vector drops, substitutes or masks a real field')
    actual=[(r['address'],r['size'],r['source_definition']['symbol'],[b['target_address'] for b in r['bindings']]) for r in m['controls'][22:]]
    if actual!=ORDINARY:raise ValueError('texture vector loses entire ordinary endpoint/index alternatives')
    controls={r['address']:r for r in m['controls'][:22]}
    for a,targets in ROUTES.items():
        if [b['target_address'] for b in controls[a]['bindings']]!=targets:raise ValueError('texture vector overrides actual closed source routes')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('texture vector resolves independent opaque getter/destruction/lifetime/assignment owner')
    if snapshots['0x0040FA00']['origin']['origin']!='compiler' or snapshots['0x0040FA00']['origin']['evidence_id']!='R037':raise ValueError('texture vector reclassifies original compiler deleting thunk')
    if {r['address']:r['size'] for r in m['anchors']}!={'0x0040B280':727,'0x0040B560':575} or any(r['origin']['origin']!='authored' or r['origin']['evidence_id']!='R019' or r['record']['evidence_id']!='R019' for r in m['anchors']):
        raise ValueError('texture vector loses full independent bitmap-directory policies')
    edges=[]
    for r in m['anchors']:
        edges.extend(dict(parent=r['address'],site=x['site'],target=f'0x{int(x["operands"],16):08X}') for x in r['witnesses'] if x['mnemonic']=='call' and x['operands'].startswith('0x') and f'0x{int(x["operands"],16):08X}' in controls)
    if m['parent_edges']!=edges or len(edges)!=33:raise ValueError('texture vector loses full independent game value/index/erase consumers')
    if [(r['address'],r.get('collection')) for r in m['retained']]!=[('0x0040DCE0','functions'),('0x0040DD00','functions'),('0x0040E4A0','functions'),('0x00640F15','functions'),('0x0040FA00',None)]:
        raise ValueError('texture vector loses original full pending/runtime/compiler records')


def accepted_snapshot(snapshot,function,origin):
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('texture vector immutable manifest differs')
    m=manifest();verify_plan(m);r=next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin']) and function==r['accepted_function'] and origin==r['accepted_origin'])


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('replay immutable source/prior evidence differs: '+path)
    c=module('replay_target','compare-coff-function.py');coff=module('replay_coff','coff_data.py');cfg=module('replay_cfg','verify-authored-origins.py');extent=module('replay_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    if digest(target)!=m['target_sha256']:raise ValueError('replay target identity differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witnesses(body,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,int(a,16))]
    if any(r['evidence_id']=='R173' for r in authored.values()):raise ValueError('replay adds false authored extent credit')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);body=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg'] or witnesses(body,a)!=r['witnesses']:raise ValueError('replay entire accepted body/CFG/instructions differ')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('replay changes unrelated original canonical record')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('replay whole original snapshot differs')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r['collection']] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('texture vector original full pending/runtime/compiler evidence differs')
    for r in m['anchors']:
        a=r['address'];body=c.pe_bytes_at(target,int(a,16),r['size'])
        if functions[a]!=r['function'] or origins[a]!=r['origin'] or authored[a]!=r['record'] or digest(body)!=r['record']['body_sha256'] or witnesses(body,a)!=r['witnesses']:raise ValueError('replay whole independent game policy differs')
        for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [x for x in rows(filename) if x['address']==a]!=r[key]:raise ValueError('replay original game switch evidence differs')
        if cfg.verify_body(body,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches'])!=(int(r['record']['return_count']),int(r['record']['internal_branch_count'])):raise ValueError('replay entire game policy CFG differs')
    scratch=ROOT/'build/origin-texture-vector-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'TextureVectorAccess.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('replay cold source/actual include ownership differs')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('replay entire ordinary emission differs')
        catalog={}
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):
                    name,a=d['symbol'],int(r['address'],16)+d['offset']
                    if name in catalog and catalog[name]!=a:raise ValueError('replay overrides one coherent source definition')
                    catalog[name]=a
        for r in m['controls']:
            for b in r['bindings']:
                if catalog.get(b['symbol'],int(EXTERNAL[b['symbol']],16) if b['symbol'] in EXTERNAL else None)!=int(b['target_address'],16):raise ValueError('replay real field loses its entire actual defining source')
            for b in r['bindings']:
                if b['symbol'] in EXTERNAL:catalog[b['symbol']]=int(EXTERNAL[b['symbol']],16)
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:raise ValueError('replay whole unmasked source comparison differs: '+r['address'])
            if r['kind']=='compiler-code':module('texture_implicit','verify-game-parent-policy-origins.py').verify_implicit_extent(r,data,c.coff_name)
            elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('texture vector full own primary AUX differs')
            if list(cfg.verify_body(actual,int(r['address'],16)))!=r['cfg']:raise ValueError('texture vector whole positive CFG differs')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<6I',raw))!=LAYOUT:raise ValueError('replay complete readonly layout differs')
    print('R173 origins OK: seven whole SDK vector access dependencies / 235 bytes; full R019 bitmap-directory policies / 1302 bytes and 33 actual value/index/erase edges; independent stride and size observations44; 25 entire SDK/ordinary/compiler controls / 926 bytes and 27 real unmasked fields; all 35 cold ordinary sections / 1129 bytes, 27 actual SDK headers and whole 24-byte layout; 55 canonical/body snapshots and five full prior pending/runtime/compiler records preserved; ordinary31/31/49-byte endpoint/index alternatives are byte-equal; 16-byte getter, 15-byte destruction and 158-byte assignment remain unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
