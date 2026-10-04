#!/usr/bin/env python3
"""Cold-replay the independent four-byte vector access graph and whole game policies."""
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
spec=importlib.util.spec_from_file_location('secondary_vector_prior',ROOT/'scripts/verify-texture-vector-access-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/secondary-texture-access-origin-evidence.json'
MANIFEST_SHA256='4727bd2e3809b9c7c4de52e24044d35167402bc11eb660ea87a538a31d65b2c0'
CONFIDENCE='complete-vc7-secondary-vector-access-and-whole-game-context'
KEYS={'0x0040DEE0': 49, '0x0040E530': 19}
LAYOUT=[4,16,4,4,16,4]
EXTERNAL={}
PROTECTED=dict(PRIOR.PROTECTED,**{'0x0040EA20':16})
ORDINARY=[('0x0040E1F0', 31, '?begin@OrdinarySecondaryTextureAccess@@QAE?AViterator@?$vector@USecondaryTextureAccessObservation@@V?$allocator@USecondaryTextureAccessObservation@@@std@@@std@@XZ', ['0x0040E9E0']), ('0x0040DEE0', 49, '?entry@OrdinarySecondaryTextureAccess@@QAEAAUSecondaryTextureAccessObservation@@I@Z', ['0x0040E1F0', '0x0040E550', '0x0040E530']), ('0x0040E530', 19, '?value@OrdinarySecondaryTextureIterator@@QBEAAUSecondaryTextureAccessObservation@@XZ', ['0x0040EA20'])]
ROUTES={'0x0040DEE0': ['0x0040E1F0', '0x0040E550', '0x0040E530'], '0x0040E530': ['0x0040EA20'], '0x0040E1F0': ['0x0040E9E0'], '0x0040E550': ['0x0040EA00'], '0x0040EA20': [], '0x0040E9E0': ['0x0040F120'], '0x0040EA00': [], '0x0040F120': []}


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
    if (m['evidence_id']!='R174' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7SecondaryTextureAccess.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=27 or len(m['functions'])!=2 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=11 or sum(r['size'] for r in m['controls'])!=343
            or sum(len(r['bindings']) for r in m['controls'])!=12 or len(m['emission'])!=15
            or sum(r['size'] for r in m['emission'])!=414 or len(m['snapshots'])!=43 or len(m['retained'])!=2
            or m['layout'] not in m['emission'] or m['layout']['size']!=24 or m['layout_values']!=LAYOUT or m['external']!=EXTERNAL):
        raise ValueError('texture vector loses bounded whole source/field/emission/layout scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];control=next(x for x in m['controls'][:8] if x['address']==a)
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!='VC7STL' or new['status']!='excluded' or new['owner']!='library' or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R174')
                or r['symbol']!=control['source_definition']['symbol'] or r['body_sha256']!=control['body_sha256'] or r['cfg']!=control['cfg'] or not r['witnesses']):
            raise ValueError('texture vector loses own SDK owner or adds false source/private ABI/exact credit')
    if [(r['address'],r['size']) for r in m['controls'][:8]]!=[('0x0040DEE0', 49), ('0x0040E530', 19), ('0x0040E1F0', 31), ('0x0040E550', 45), ('0x0040EA20', 16), ('0x0040E9E0', 28), ('0x0040EA00', 32), ('0x0040F120', 24)]:
        raise ValueError('secondary vector loses whole independently measured access graph')
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition'];kind='code';role='byte-equal-ordinary-alternative' if i>=8 else 'closed-whole-sdk-context'
        if (r['kind']!=kind or r['role']!=role or ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])):
            raise ValueError('texture vector slices entire defining source or substitutes a different owner')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type']!='REL32' or f['offset']+4>r['size']:
                raise ValueError('texture vector drops, substitutes or masks a real field')
    actual=[(r['address'],r['size'],r['source_definition']['symbol'],[b['target_address'] for b in r['bindings']]) for r in m['controls'][8:]]
    if actual!=ORDINARY:raise ValueError('texture vector loses entire ordinary endpoint/index alternatives')
    controls={r['address']:r for r in m['controls'][:8]}
    for a,targets in ROUTES.items():
        if [b['target_address'] for b in controls[a]['bindings']]!=targets:raise ValueError('texture vector overrides actual closed source routes')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('texture vector resolves independent opaque getter/destruction/lifetime/assignment owner')
    if {r['address']:r['size'] for r in m['anchors']}!={'0x0040AD80':177,'0x0040AE40':434} or any(r['origin']['origin']!='authored' or r['origin']['evidence_id']!='R017' or r['record']['evidence_id']!='R017' for r in m['anchors']):
        raise ValueError('secondary vector loses independent whole texture resource policies')
    edges=[]
    for r in m['anchors']:
        edges.extend(dict(parent=r['address'],site=x['site'],target=f'0x{int(x["operands"],16):08X}') for x in r['witnesses'] if x['mnemonic']=='call' and x['operands'].startswith('0x') and f'0x{int(x["operands"],16):08X}' in controls)
    if m['parent_edges']!=edges or len(edges)!=5:raise ValueError('texture vector loses full independent game value/index/erase consumers')
    if [(r['address'],r.get('collection')) for r in m['retained']]!=[('0x0040E1F0','functions'),('0x0040E9E0','functions')]:
        raise ValueError('secondary vector loses original whole accepted endpoint records')



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
    if any(r['evidence_id']=='R174' for r in authored.values()):raise ValueError('replay adds false authored extent credit')
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
    scratch=ROOT/'build/origin-secondary-texture-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'SecondaryTextureAccess.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
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
    print('R174 origins OK: two whole SDK vector access dependencies / 68 bytes; full R017 resource policies / 611 bytes and five actual index edges; independent stride4; 11 entire SDK/ordinary controls / 343 bytes and 12 real unmasked fields; all 15 cold ordinary sections / 414 bytes, 27 actual SDK headers and whole 24-byte layout; 43 canonical/body snapshots and two full prior accepted endpoint records preserved; ordinary31/49/19-byte alternatives are byte-equal; const getter remains unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
