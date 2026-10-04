#!/usr/bin/env python3
"""Cold-replay whole replay deque iterator graphs with independent game policy."""
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
spec=importlib.util.spec_from_file_location('replay_iterator_prior',ROOT/'scripts/verify-character-list-policy-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/replay-deque-iterator-origin-evidence.json'
MANIFEST_SHA256='16750d50025a197b097c494ff49f6778fa490f4303669871f45ad3e8aa18d83e'
CONFIDENCE='complete-vc7-replay-deque-iterator-graph-and-whole-game-policy'
KEYS={'0x00414930':22,'0x004149E0':22,'0x004145C0':35,'0x004145F0':41,
      '0x00414A90':22,'0x004147B0':35,'0x004147E0':41,'0x004155A0':33,
      '0x004156B0':33,'0x00415670':32,'0x004157C0':33,'0x00415780':32}
LAYOUT=[1,2,4,20,20,20,8,8,8,8,8,8]
ROOTS=[('E','0x00414930','0x004155A0','0x004143D0','0x00414400','0x00415560','0x00415E60'),
       ('G','0x004149E0','0x004156B0','0x004145C0','0x004145F0','0x00415670','0x00415E90'),
       ('K','0x00414A90','0x004157C0','0x004147B0','0x004147E0','0x00415780','0x00415EC0')]


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
    if (m['evidence_id']!='R171' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7ReplayDequeIterators.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=27 or len(m['functions'])!=12 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=38 or sum(r['size'] for r in m['controls'])!=1492
            or sum(len(r['bindings']) for r in m['controls'])!=22 or len(m['emission'])!=43
            or sum(r['size'] for r in m['emission'])!=1903 or len(m['snapshots'])!=70
            or m['layout'] not in m['emission'] or m['layout']['size']!=48 or m['layout_values']!=LAYOUT
            or len(m['retained'])!=2):raise ValueError('replay loses bounded whole source/field/emission/layout scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function']
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a
                or int(old['size'])!=r['size'] or new['size']!=str(r['size'])
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['span_end']!=f'0x{int(a,16)+r["size"]-1:08X}'
                or new['module']!='VC7STL' or new['status']!='excluded' or new['owner']!='library'
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R171')):
            raise ValueError('replay changes unrelated extent/ABI or gives false authored/source/exact credit')
        control=next(x for x in m['controls'][:36] if x['address']==a)
        if r['symbol']!=control['source_definition']['symbol'] or r['body_sha256']!=control['body_sha256'] or r['cfg']!=control['cfg'] or not r['witnesses']:
            raise ValueError('replay substitutes whole SDK definition or complete instructions')
    controls={r['address']:r for r in m['controls'][:36]}
    if len(controls)!=36:raise ValueError('replay duplicates a distinct SDK definition')
    for t,iterator,const,begin,end,node,const_node in ROOTS:
        for a,prefix,size,dest in [(iterator,'??0iterator',22,const),(const,'??0const_iterator',33,None),
                                   (begin,'?begin',35,node),(end,'?end',41,node),
                                   (node,'??0iterator',32,const_node),(const_node,'??0const_iterator',33,None)]:
            r=controls[a]
            if r['size']!=size or not r['source_definition']['symbol'].startswith(prefix+'@?$deque@'+t):
                raise ValueError('replay loses actual whole specialization identity')
            if [b['target_address'] for b in r['bindings']]!=([] if dest is None else [dest]):
                raise ValueError('replay replaces actual default/node/endpoint call graph')
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition']
        if (r['kind']!='code' or r['role']!=('closed-whole-sdk-context' if i<36 else 'byte-equal-ordinary-alternative')
                or ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or ss['source_sha256']!=r['source_sha256']
                or len(ss['fields'])!=len(r['bindings'])):raise ValueError('replay slices full own defining source or substitutes an alternative')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type']!='REL32' or f['offset']+4>r['size']:
                raise ValueError('replay drops, substitutes or masks a real field')
    ordinary=m['controls'][36:]
    if ([(r['address'],r['size'],r['source_definition']['symbol']) for r in ordinary]!=[
            ('0x004155A0',33,'??0OrdinaryReplayConstIterator@@QAE@XZ'),('0x00414930',22,'??0OrdinaryReplayIterator@@QAE@XZ')]
            or ordinary[0]['bindings'] or [b['target_address'] for b in ordinary[1]['bindings']]!=['0x004155A0']):
        raise ValueError('replay loses entire ordinary base/derived constructor alternatives')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PRIOR.PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('replay resolves an independent protected short/lifetime/catch owner')
    if {r['address']:r['size'] for r in m['anchors']}!={'0x00413DE0':1252} or any(r['origin']['origin']!='authored' or r['origin']['evidence_id']!='R035' or r['record']['evidence_id']!='R035' for r in m['anchors']):
        raise ValueError('replay loses the full independent authored policy')
    w=m['anchors'][0]['witnesses'];edges=[dict(site=x['site'],target=f'0x{int(x["operands"],16):08X}') for x in w if x['mnemonic']=='call' and x['operands'].startswith('0x') and f'0x{int(x["operands"],16):08X}' in controls]
    if m['parent_edges']!=edges or len(edges)!=26 or not set(KEYS)&{r['target'] for r in edges}:
        raise ValueError('replay loses genuine complete parent instructions and iterator consumers')
    if sorted((r['address'],r['collection']) for r in m['retained'])!=[('0x00424500','nodes'),('0x00445530','nodes')]:
        raise ValueError('replay substitutes frozen independent SDK peer evidence')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('replay immutable source/prior evidence differs: '+path)
    c=module('replay_target','compare-coff-function.py');coff=module('replay_coff','coff_data.py');cfg=module('replay_cfg','verify-authored-origins.py');extent=module('replay_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    if digest(target)!=m['target_sha256']:raise ValueError('replay target identity differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witnesses(body,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,int(a,16))]
    if any(r['evidence_id']=='R171' for r in authored.values()):raise ValueError('replay adds false authored extent credit')
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
    scratch=ROOT/'build/origin-replay-iterator-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'ReplayDequeIterators.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
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
        if list(struct.unpack('<12I',raw))!=LAYOUT:raise ValueError('replay complete readonly layout differs')
    print('R171 origins OK: twelve whole SDK deque iterator dependencies / 381 bytes; full independent R035 game policy / 1252 bytes and 26 real consumer edges; 38 entire SDK/ordinary controls / 1492 bytes, 22 real unmasked fields; all 43 cold ordinary sections / 1903 bytes, 27 actual SDK headers and whole 48-byte layout; 70 canonical/body snapshots and both independent peer records preserved; observed widths1/2/4 do not recover original element types; ordinary 22/33-byte alternatives are byte-equal; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
