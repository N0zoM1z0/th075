#!/usr/bin/env python3
"""Replay complete file policies with actual paths, imports and game context."""
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
spec=importlib.util.spec_from_file_location('file_resource_prior',ROOT/'scripts/verify-remaining-lifetime-policy-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=PRIOR.module;digest=PRIOR.digest
EVIDENCE='config/file-resource-policy-origin-evidence.json'
MANIFEST_SHA256='35ad6c3a092b0e7ced612e6629fddd935b47fcd13c04d9bce40e604057f117f6'
KEYS={'0x00427300':298,'0x0041D6C0':133}
LAYOUT=[1,108,12,12]
DIFFERENCES=[40,43,56,92,104,114,153,156,162,166,194,195,196,197,198,199,200,201,202,203,204,205,206,208,216,220,224,229,233,239,246,258,268]
DESTINATIONS=['0x00657C90','0x00657130','0x00657058','0x006416A2','0x0065712C','0x00657138','0x00657CA0','0x00657130','0x00657124','0x00657138','0x0064169D']
IMPORTS=[dict(address=a,dll='KERNEL32.dll',name=n) for a,n in [('0x00657130','CreateFileA'),('0x00657058','GetFileSize'),('0x0065712C','ReadFile'),('0x00657138','CloseHandle'),('0x00657124','WriteFile')]]
POLICIES=[('music-file-conversion',298,'?encode@MusicFilePolicyObservation@@QAEXXZ'),('readable-file-insertion',130,'?append@ReadableFilePolicyObservation@@QAEXPBD@Z')]

def manifest():return json.loads((ROOT/EVIDENCE).read_text())

def verify_plan(m):
    if (m['evidence_id']!='R179' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7FileResourcePolicies.cpp' or m['profile']!=SDK.PROFILE
            or len(m['functions'])!=2 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['policies'])!=2 or len(m['emission'])!=86 or sum(r['size'] for r in m['emission'])!=4266
            or len(m['headers'])!=28 or len(m['snapshots'])!=143 or len({r['address'] for r in m['snapshots']})!=143
            or {r['address']:r['size'] for r in m['anchors']}!={'0x00426DD0':916,'0x0041CF80':245,'0x0041D510':429}
            or len(m['retained'])!=4 or m['layout'] not in m['emission'] or m['layout']['size']!=16 or m['layout_values']!=LAYOUT
            or m['import_slots']!=IMPORTS or m['protected']!=PRIOR.manifest()['protected']):
        raise ValueError('file resource loses bounded full policy/source/context scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];owner='MusicRoom' if a=='0x00427300' else 'DataArchive'
        if (r['decision']!='authored' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!=owner or new['owner']!='authored' or new['status']!='unclassified'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00' or 'symbol' in r
                or r['accepted_origin']!=dict(address=a,origin='authored',subsystem=owner,disposition='authored',confidence='complete-custom-file-policy-with-independent-game-resource-context',evidence_id='R179')
                or r['accepted_authored_record']!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R179')):
            raise ValueError('file resource loses independent ownership or adds false source/private ABI/exact credit')
    records={r['address']:r for r in m['functions']}
    expected_calls={'0x00427300':['dword ptr [0x657130]','dword ptr [0x657058]','0x6416a2','dword ptr [0x65712c]','dword ptr [0x657138]','dword ptr [0x657130]','dword ptr [0x657124]','dword ptr [0x657138]','0x64169d'],
                    '0x0041D6C0':['dword ptr [0x657130]','dword ptr [0x657058]','0x641b80','dword ptr [0x657138]','0x41d9c0','0x640611']}
    for a,expected in expected_calls.items():
        if [r['operands'] for r in records[a]['witnesses'] if r['mnemonic']=='call']!=expected:raise ValueError('file resource actual operation/call order differs')
    required={'0x00427300':[('0x0042731B','push','0x657c90'),('0x0042738C','push','0x657ca0'),('0x004273A0','mov','byte ptr [ebp - 0x12], 0x5c'),('0x004273A4','mov','byte ptr [ebp - 0x11], 0x5a'),('0x004273CF','xor','edx, eax'),('0x004273E1','add','eax, edx'),('0x004273EA','add','ecx, 0x3d'),('0x004273C0','jae','0x4273f2')],
              '0x0041D6C0':[('0x0041D6F8','mov','dword ptr [ebp - 0x10], 0'),('0x0041D70B','mov','dword ptr [ebp - 0x14], eax'),('0x0041D6F0','cmp','dword ptr [ebp - 4], -1'),('0x0041D6F6','jmp','0x41d737'),('0x0041D712','lea','eax, [ebp - 0x78]'),('0x0041D72F','add','ecx, 4'),('0x0041D742','ret','4')]}
    for a,expected in required.items():
        if not set(expected)<={(r['site'],r['mnemonic'],r['operands']) for r in records[a]['witnesses']}:raise ValueError('file resource loses explicit path/key/guard/insertion policy')
    anchor=next(r for r in m['anchors'] if r['address']=='0x00426DD0')
    if not {('0x00426DDD','push','0x657c80'),('0x00426E31','mov','byte ptr [ebp - 0x22], 0x5c'),('0x00426E35','mov','byte ptr [ebp - 9], 0x5a'),('0x00426E7B','add','eax, 0x3d')}<={(r['site'],r['mnemonic'],r['operands']) for r in anchor['witnesses']}:
        raise ValueError('file resource loses independent whole music loader path/key context')
    for r,(role,size,symbol) in zip(m['policies'],POLICIES):
        if (r['role'],r['size'],r['source_definition']['symbol'])!=(role,size,symbol) or r['section'] not in m['emission'] or 'target_positive' in r:
            raise ValueError('file resource loses full source-operation control or invents target positive')
        if r['call_symbols']!=[q['symbol']['symbol'] for q in r['section']['fields'] if q['type']=='REL32']:raise ValueError('file resource source call order loses genuine fields')
    if m['policies'][0]['call_symbols']!=['??_U@YAPAXI@Z','??_V@YAXPAX@Z'] or m['policies'][1]['call_symbols']!=['_strcpy','?push_back@?$list@UFileNamePolicyObservation@@V?$allocator@UFileNamePolicyObservation@@@std@@@std@@QAEXABUFileNamePolicyObservation@@@Z','@__security_check_cookie@4']:
        raise ValueError('file resource loses natural source allocation/list/cleanup operations')
    n=m['negative'];fields=n['section']['fields']
    if (n['address']!='0x00427300' or n['size']!=298 or n['section']!=m['policies'][0]['section'] or n['differences']!=DIFFERENCES
            or n['source_definition']!=m['policies'][0]['source_definition'] or len(fields)!=11 or len(n['bindings'])!=11
            or [b['target_address'] for b in n['bindings']]!=DESTINATIONS
            or [{k:b[k] for k in ('offset','type','symbol','addend')} for b in n['bindings']]!=[dict(offset=q['offset'],type=q['type'],symbol=q['symbol']['symbol'],addend=q['addend']) for q in fields]):
        raise ValueError('file resource masks a whole source negative or changes genuine bindings')
    if [(r['address'],r['size'],r['text']) for r in m['strings']]!=[('0x00657C90',14,'musicroom.csv'),('0x00657CA0',14,'musicroom.dat')]:raise ValueError('file resource loses complete fixed filename controls')
    for r in m['strings']:
        if r['section'] not in m['emission'] or r['section']['fields'] or r['size']!=r['section']['size']:raise ValueError('file resource truncates original string extent')
    q=m['independent_catalog_string']
    if q['address']!='0x00657C80' or q['text']!='musicroom.dat' or q['size']!=14:raise ValueError('file resource conflates independent filename locations')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in m['protected'].items():
        if snapshots[a]['size']!=size or snapshots[a]['origin']['origin']!='unknown':raise ValueError('file resource changes protected opaque ownership')
    if snapshots['0x0041D9C0']['origin']['origin']!='library':raise ValueError('file resource borrows list wrapper ownership')

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('file resource immutable source/prior evidence differs: '+path)
    c=module('file_target','compare-coff-function.py');coff=module('file_coff','coff_data.py');cfg=module('file_cfg','verify-authored-origins.py');extent=module('file_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witness(raw,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(raw,int(a,16))]
    if digest(target)!=m['target_sha256'] or {a for a,r in authored.items() if r['evidence_id']=='R179'}!=(set() if args.evidence_only else set(KEYS)):raise ValueError('file resource target/authored registry differs')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only)
        if not args.evidence_only and authored[a]!=r['accepted_authored_record']:raise ValueError('file resource accepted authored record differs')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('file resource changes unrelated canonical context')
        if int(functions[a]['size'])!=r['size'] or digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('file resource entire target snapshot differs')
    for r in [*m['functions'],*m['anchors']]:
        a=r['address'];raw=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(raw)!=r['body_sha256'] or witness(raw,a)!=r['witnesses'] or list(cfg.verify_body(raw,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches']))!=r['cfg']:raise ValueError('file resource entire policy/anchor/CFG differs')
        if any(int(a,16)<int(q,16)<int(a,16)+r['size'] for q in functions):raise ValueError('file resource extent contains another function')
        for file,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(file) if q['address']==a]!=r[key]:raise ValueError('file resource original complete switch evidence differs')
        if 'record' in r and (authored[a]!=r['record'] or functions[a]!=r['function'] or origins[a]!=r['origin']):raise ValueError('file resource original full authored anchor differs')
    for r in m['retained']:
        if r['record'] not in json.loads((ROOT/r['file']).read_text())[r['collection']]:raise ValueError('file resource original full archive/list record differs')
    imports=module('file_imports','verify-import-origins.py').pe_imports(target,c)
    for r in IMPORTS:
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('file resource actual PE import differs')
    q=m['independent_catalog_string'];raw=c.pe_bytes_at(target,int(q['address'],16),q['size'])
    if raw!=q['text'].encode()+b'\0' or digest(raw)!=q['body_sha256']:raise ValueError('file resource original independent catalog string differs')
    scratch=ROOT/'build/origin-file-resource-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'FileResourcePolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or PRIOR.PRIOR.included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('file resource cold source/actual include ownership differs')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('file resource complete ordinary emission differs')
        for r in m['policies']:
            head=struct.unpack_from('<8sIIIIIIHHI',data,20+(r['section']['section']-1)*40);raw=data[head[4]:head[4]+head[3]]
            if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or witness(raw,'0x00000000')!=r['witnesses'] or list(cfg.verify_body(raw,0))!=r['cfg']:raise ValueError('file resource whole source operation differs')
            if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('file resource loses own entire primary AUX')
        n=m['negative'];catalog={b['symbol']:int(b['target_address'],16) for b in n['bindings']}
        raw,linked=SDK.ENDPOINT.link(data,n,catalog,c);actual=c.pe_bytes_at(target,0x427300,298)
        if len(raw)!=298 or len(linked)!=298 or digest(raw)!=n['source_sha256'] or digest(actual)!=n['body_sha256'] or [i for i,(a,b) in enumerate(zip(linked,actual)) if a!=b]!=DIFFERENCES:raise ValueError('file resource whole unmasked source negative differs')
        for r in m['strings']:
            raw,_=coff.readonly_section(data,r['section']['section'],c.coff_name);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if raw!=r['text'].encode()+b'\0' or raw!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256'] or catalog[r['source_definition']['symbol']]!=int(r['address'],16):raise ValueError('file resource complete own filename/binding differs')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<4I',raw))!=LAYOUT:raise ValueError('file resource entire readonly source layout differs')
    print('R179 origins OK: two complete authored file policies /431 bytes; two whole source-operation controls /428 bytes; whole298-byte negative binds11 actual fields and retains33 differences; two complete filename controls /28 bytes and independent musicroom.dat loader/key context;86 ordinary sections /4266 bytes,28 SDK headers and16-byte layout;143 snapshots,40 protected unknowns,1590 bytes of authored anchors and four original archive/list records preserved; no source/private ABI/mapping/exact credit, exact stays60.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
