#!/usr/bin/env python3
"""Cold-replay entire front helpers and independently observed whole-game consumers."""
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
spec=importlib.util.spec_from_file_location('replay_front_prior',ROOT/'scripts/verify-replay-deque-iterator-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/replay-deque-front-origin-evidence.json'
MANIFEST_SHA256='b96e349e1284ca20adde1a3fa512593ebc6aab968a9051b1c6f2add9f2252354'
CONFIDENCE='complete-vc7-front-graph-and-whole-game-consumer-widths'
KEYS={'0x00454D50':32,'0x00454E10':32,'0x004464C0':32}
LAYOUT=PRIOR.LAYOUT+[1,2,4,20,20,20,20]
FRONTS=[('E','0x00454D50','0x004143D0','0x00414950'),('G','0x00454E10','0x004145C0','0x00414A00'),('K','0x004464C0','0x004147B0','0x00414AB0')]
PARENTS={'0x00452F10':2815,'0x00455580':139,'0x00445A00':1958}
BATCHES={'0x00452F10':'R045','0x00455580':'R109','0x00445A00':'R065'}
OBSERVATIONS=[dict(parent='0x00452F10',candidate='0x00454D50',call_site='0x00452FB6',load_site='0x00452FBB',width=1),dict(parent='0x00455580',candidate='0x00454E10',call_site='0x004555AE',load_site='0x004555B3',width=2),dict(parent='0x00445A00',candidate='0x004464C0',call_site='0x00445A49',load_site='0x00445A4E',width=4)]


def manifest():return json.loads((ROOT/EVIDENCE).read_text())


def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        text=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if text[:3].lower()!='z:/':raise ValueError('replay include loses actual host mapping')
        path=Path(text[2:]);relative=str(path.relative_to(ROOT))
        if relative!='probes/VC7ReplayDequeIterators.cpp' and not relative.startswith('.tools/msvc710/Vc7/include/'):raise ValueError('replay gains unrelated include owner')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    old=PRIOR.manifest();PRIOR.verify_plan(old)
    if (m['evidence_id']!='R172' or m['target_sha256']!=old['target_sha256']
            or m['probe']!='probes/VC7ReplayDequeFront.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=28 or len(m['functions'])!=3 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=42 or sum(r['size'] for r in m['controls'])!=1620
            or sum(len(r['bindings']) for r in m['controls'])!=30 or len(m['emission'])!=51
            or sum(r['size'] for r in m['emission'])!=2111 or len(m['snapshots'])!=76 or len(m['retained'])!=15
            or m['layout'] not in m['emission'] or m['layout']['size']!=76 or m['layout_values']!=LAYOUT):
        raise ValueError('front loses bounded full source/field/emission/layout scope')
    for before,after in zip(old['controls'],m['controls'][:38]):
        if any(before[k]!=after[k] for k in ('address','size','kind','role','source_sha256','body_sha256','bindings','cfg')) or before['source_definition']['symbol']!=after['source_definition']['symbol']:
            raise ValueError('front changes a previous whole SDK or ordinary control')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r,(t,a,begin,deref) in zip(m['functions'],FRONTS):
        original,new=r['original_function'],r['accepted_function'];control=next(x for x in m['controls'][38:41] if x['address']==a)
        if (r['address']!=a or r['decision']!='library' or r['original_origin']['origin']!='unknown' or original['address']!=a or int(original['size'])!=32
                or {k:v for k,v in original.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!='VC7STL' or new['status']!='excluded' or new['owner']!='library' or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R172')
                or r['symbol']!=control['source_definition']['symbol'] or r['body_sha256']!=control['body_sha256'] or r['cfg']!=control['cfg'] or not r['witnesses']
                or not r['symbol'].startswith('?front@?$deque@'+t) or [b['target_address'] for b in control['bindings']]!=[begin,deref]):
            raise ValueError('front loses whole genuine SDK owner/field graph or grants false source/private ABI/exact credit')
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition'];ordinary=i in (36,37,41)
        if (r['kind']!='code' or r['role']!=('byte-equal-ordinary-alternative' if ordinary else 'closed-whole-sdk-context') or ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])):
            raise ValueError('front slices its entire defining source or substitutes an alternative')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type']!='REL32' or f['offset']+4>r['size']:
                raise ValueError('front drops, substitutes or masks a real field')
    r=m['controls'][41]
    if r['address']!='0x00454D50' or r['size']!=32 or r['source_definition']['symbol']!='?first@OrdinaryReplayFront@@QAEAAEXZ' or [b['target_address'] for b in r['bindings']]!=['0x004143D0','0x00414950']:
        raise ValueError('front loses whole ordinary derived first() alternative')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PRIOR.PRIOR.PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('front resolves an independent opaque owner')
    if {r['address']:r['size'] for r in m['anchors']}!=PARENTS or any(r['origin']['origin']!='authored' or r['origin']['evidence_id']!=BATCHES[r['address']] or r['record']['evidence_id']!=BATCHES[r['address']] for r in m['anchors']):
        raise ValueError('front loses a full independent authored game policy')
    edges=[]
    for r in m['anchors']:
        edges.extend(dict(parent=r['address'],site=x['site'],target=f'0x{int(x["operands"],16):08X}') for x in r['witnesses'] if x['mnemonic']=='call' and x['operands'].startswith('0x') and f'0x{int(x["operands"],16):08X}' in KEYS)
    if m['parent_edges']!=edges or len(edges)!=8:raise ValueError('front loses actual whole-parent consumer calls')
    if [{k:v for k,v in r.items() if k!='load'} for r in m['consumer_observations']]!=OBSERVATIONS:raise ValueError('front replaces independent actual width observations')
    for r in m['consumer_observations']:
        parent=next(a for a in m['anchors'] if a['address']==r['parent']);load=next(x for x in parent['witnesses'] if x['site']==r['load_site'])
        if r['load']!=load or load['mnemonic']!='mov' or ('byte ptr','word ptr','dword ptr')[(1,2,4).index(r['width'])] not in load['operands'] or '[eax]' not in load['operands']:
            raise ValueError('front loses actual byte/word/dword consumer instructions')
    expected=old['retained']+[dict(file=PRIOR.EVIDENCE,address=r['address'],collection='functions',record=r) for r in old['functions']]+[dict(file=PRIOR.EVIDENCE,address='0x00413DE0',collection='anchors',record=old['anchors'][0])]
    if m['retained']!=expected:raise ValueError('front replaces full previous accepted SDK/game/peer records')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('replay immutable source/prior evidence differs: '+path)
    c=module('replay_target','compare-coff-function.py');coff=module('replay_coff','coff_data.py');cfg=module('replay_cfg','verify-authored-origins.py');extent=module('replay_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    if digest(target)!=m['target_sha256']:raise ValueError('replay target identity differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witnesses(body,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,int(a,16))]
    if any(r['evidence_id']=='R172' for r in authored.values()):raise ValueError('replay adds false authored extent credit')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);body=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg'] or witnesses(body,a)!=r['witnesses']:raise ValueError('replay entire accepted body/CFG/instructions differ')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('replay changes unrelated original canonical record')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('replay whole original snapshot differs')
    for r in m['retained']:
        if r['record'] not in json.loads((ROOT/r['file']).read_text())[r['collection']]:raise ValueError('replay original complete peer evidence differs')
    for r in m['anchors']:
        a=r['address'];body=c.pe_bytes_at(target,int(a,16),r['size'])
        if functions[a]!=r['function'] or origins[a]!=r['origin'] or authored[a]!=r['record'] or digest(body)!=r['record']['body_sha256'] or witnesses(body,a)!=r['witnesses']:raise ValueError('replay whole independent game policy differs')
        for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [x for x in rows(filename) if x['address']==a]!=r[key]:raise ValueError('replay original game switch evidence differs')
        if cfg.verify_body(body,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches'])!=(int(r['record']['return_count']),int(r['record']['internal_branch_count'])):raise ValueError('replay entire game policy CFG differs')
    decoder.detail=True
    from capstone.x86 import X86_OP_MEM, X86_REG_EAX
    for r in m['consumer_observations']:
        ins=next(decoder.disasm(c.pe_bytes_at(target,int(r['load_site'],16),16),int(r['load_site'],16)))
        operand=ins.operands[-1]
        if ins.mnemonic!='mov' or operand.type!=X86_OP_MEM or operand.size!=r['width'] or operand.mem.base!=X86_REG_EAX or operand.mem.index or operand.mem.disp:
            raise ValueError('front actual memory operand width/base differs')
    scratch=ROOT/'build/origin-replay-front-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'ReplayDequeFront.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
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
                if catalog.get(b['symbol'])!=int(b['target_address'],16):raise ValueError('replay real field loses its entire actual defining source')
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:raise ValueError('replay whole unmasked source comparison differs: '+r['address'])
            if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size'] or list(cfg.verify_body(actual,int(r['address'],16)))!=r['cfg']:raise ValueError('replay full own primary AUX/CFG differs')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<19I',raw))!=LAYOUT:raise ValueError('replay complete readonly layout differs')
    print('R172 origins OK: three entire SDK front helpers / 96 bytes; three full independent R045/R109/R065 game policies / 4912 bytes and eight actual front consumer edges; byte/word/dword loads independently observed; 42 whole SDK/ordinary controls / 1620 bytes and 30 genuine unmasked fields; all 51 cold ordinary sections / 2111 bytes, 27 SDK headers plus the pinned prior probe include and whole 76-byte layout; 76 canonical/body snapshots and 15 original accepted records preserved; entire ordinary first() alternative is byte-equal; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
