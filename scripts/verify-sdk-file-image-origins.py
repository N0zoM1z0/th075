#!/usr/bin/env python3
"""Reopen complete pinned D3DX COMDATs and bind every real field without masking."""
from __future__ import annotations
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import struct
import subprocess
import sys
import tempfile
import capstone

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-file-image-origin-evidence.json'
MANIFEST_SHA256 = '7765c1d0980044422c8f3e287707930e3327d089e61e7211f257c6732a3c78b6'
KEYS = {'0x0061FF67':269,'0x0060BF05':272,'0x0060C015':202,'0x0060C0DF':65,
        '0x0061FB45':110,'0x0061FC33':179,'0x00618EC7':224,'0x006111EA':701,
        '0x0060EC42':195,'0x0060ED05':1814,'0x0060F41B':740,'0x0060F9D1':1191,
        '0x0060FE78':646,'0x0063B803':993,'0x00629921':66}
CONFIDENCE = 'whole-pinned-sdk-comdat-with-independent-callee-import-and-scalar-fields'
# R148 recursively replays R135, R125 and R119; avoid repeating those cold chains.
DEPENDENCIES = ['runtime','runtime-leaf','allocation-api','standard-exception','floor-math','sdk']

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result

def digest(data):
    return hashlib.sha256(data).hexdigest()

def rows(filename):
    with (ROOT/filename).open(newline='') as stream:
        return list(csv.DictReader(stream))

def verify_plan(m, *, evidence_id='R184', keys=None, field_count=83, retained_count=10, dependencies=None):
    keys=KEYS if keys is None else keys
    dependencies=DEPENDENCIES if dependencies is None else dependencies
    if (m['evidence_id']!=evidence_id or {r['address']:r['size'] for r in m['functions']}!=keys
            or len(m['functions'])!=len(keys) or sum(len(r['fields']) for r in m['functions'])!=field_count
            or len(m['retained'])!=retained_count or m['dependency_verifiers']!=dependencies
            or m['library']!='d3dx8.lib' or m['archive_sha256']!='39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28'):
        raise ValueError('SDK file/image loses complete bounded vendor scope')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function']
        mutable={'proposed_name','module','status','owner','evidence','notes'}
        expected_origin=dict(address=r['address'],origin='library',subsystem='D3DX8',
                             disposition='exclude',confidence=CONFIDENCE,evidence_id=evidence_id)
        if (r['original_origin']['origin']!='unknown' or r['accepted_origin']!=expected_origin
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='library' or new['status']!='excluded' or new['module']!='D3DX8'
                or int(old['size'])!=r['size'] or old['address']!=r['address']
                or int(old['span_end'],16)!=int(r['address'],16)+r['size']-1
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00'
                or len(r['fields'])!=len(r['bindings']) or r['extent_basis']!='single-function-complete-code-section'):
            raise ValueError('SDK file/image alters native extent or grants source/ABI/exact credit')
    catalog={}
    for r in m['retained']:
        name=r['requested_symbol'];a=int(r['address'],16)
        if name in catalog:raise ValueError('SDK file/image duplicates a retained symbol')
        catalog[name]=a
    for r in m['functions']:
        for b in r['bindings']:
            name=b['symbol'];a=int(b['target_address'],16)
            if name in catalog and catalog[name]!=a:raise ValueError('SDK file/image overrides coherent symbol identity')
            catalog[name]=a
    if m['catalog']!={k:f'0x{v:08X}' for k,v in sorted(catalog.items())}:
        raise ValueError('SDK file/image loses coherent complete binding catalogue')

def bind_fields(code, fields, bindings, address, callees, imports, scalar_reader):
    """Allow only complete known callees, actual named PE IATs and same-member scalars."""
    if len(fields)!=len(bindings):raise ValueError('SDK field coverage mismatch')
    result=bytearray(code);seen=set();calls={};data={}
    for f,b in zip(fields,bindings):
        offset=f['offset'];name=f['symbol'];destination=int(b['target_address'],16)
        if (offset in seen or offset<1 or offset+4>len(code)
                or f['addend']!=0 or f['local_symbol_offset'] is not None
                or {k:b[k] for k in f}!=f or struct.unpack_from('<I',code,offset)[0]!=0):
            raise ValueError('SDK field metadata, extent or addend mismatch')
        seen.add(offset)
        if f['type']=='REL32':
            if f['type_id']!=20 or code[offset-1]!=0xE8 or callees.get(name)!=destination or b['kind']!='callee':
                raise ValueError('SDK call lacks independently complete source callee')
            value=(destination-address-offset-4)&0xffffffff;calls[address+offset]=destination
        elif f['type']=='DIR32' and f['type_id']==6:
            value=destination;data[address+offset]=destination
            if name.startswith('__imp__'):
                match=re.fullmatch(r'__imp__([^@]+)@[0-9]+',name)
                if (not match or imports.get(destination)!=(b.get('dll'),b.get('name'))
                        or match.group(1)!=b.get('name') or b['kind']!='import'):
                    raise ValueError('SDK IAT lacks exact PE DLL/name and source symbol identity')
            elif name.startswith('__real@'):
                literal=scalar_reader(name,destination)
                if b['kind']!='scalar' or literal.hex()!=b.get('literal_hex'):
                    raise ValueError('SDK scalar lacks complete same-member source identity')
            else:raise ValueError('SDK DIR32 is not an independently supported import/scalar')
        else:raise ValueError('SDK relocation type unsupported')
        struct.pack_into('<I',result,offset,value)
    return result,calls,data

def flow_counts(code, address):
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.detail=True
    instructions=list(decoder.disasm(bytes(code),address))
    if sum(i.size for i in instructions)!=len(code):raise ValueError('SDK incomplete native decoding')
    return [sum(i.group(capstone.CS_GRP_RET) for i in instructions),sum(i.group(capstone.CS_GRP_JUMP) for i in instructions)]

def verify_alias(definitions, primary, alias):
    p=[r for r in definitions if r['symbol']==primary and r['section']>0]
    a=[r for r in definitions if r['symbol']==alias and r['section']>0]
    if (len(p)!=1 or len(a)!=1 or p[0]['offset']!=0 or p[0]['type']!=32 or p[0]['storage']!=2
            or a[0]['offset']!=p[0]['offset'] or a[0]['section']!=p[0]['section']
            or a[0]['type']!=0 or a[0]['storage']!=2):
        raise ValueError('SDK stack-probe alias lacks same complete primary definition')

def replay_manifest(m, evidence_only=False):
    """Share complete source/ledger/CFG checks without weakening each bounded plan."""
    c=module('sdk_file_target','compare-coff-function.py');sdk=module('sdk_file_comdat','verify-sdk-origins.py')
    runtime=module('sdk_file_archive','verify-runtime-origins.py');coff=module('sdk_file_data','coff_data.py')
    geometry=module('sdk_file_geometry','verify-compiler-origins.py');cfg=module('sdk_file_cfg','verify-authored-origins.py')
    target=c.verified_target();imports=module('sdk_file_imports','verify-import-origins.py').pe_imports(target,c)
    if digest(target)!=m['target_sha256']:raise ValueError('SDK target identity differs')
    functions={r['address']:r for r in rows('config/functions.csv')};origins={r['address']:r for r in rows('config/function-origins.csv')}
    archives={};callees={}
    def member(library,offset):
        if library not in ('libcmt.lib','d3dx8.lib'):raise ValueError('SDK unsupported archive')
        if library not in archives:
            path=ROOT/('.tools/msvc710/Vc7/lib' if library=='libcmt.lib' else '.tools/msvc710/Vc7/PlatformSDK/Lib')/library
            raw=path.read_bytes();archives[library]=(digest(raw),{o:(n,b) for o,n,b in runtime.archive_members(raw)})
        h,members=archives[library]
        return h,*members[int(offset)]
    scratch=ROOT/'build/origin-sdk-file-image-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        object_path=Path(dirname)/'vendor.obj'
        for r in m['retained']:
            a=r['address'];old=r['record']
            if r.get('collection'):
                present=old in json.loads((ROOT/r['file']).read_text())[r['collection']]
            else:present=old in rows(r['file'])
            if not present or functions[a]!=r['function'] or origins[a]!=r['origin'] or origins[a]['origin']!='library':
                raise ValueError('SDK retained complete source record/ledger differs')
            h,name,body=member(r['library'],old['member_offset'])
            if h!=r['archive_sha256'] or name!=old['member'] or digest(body)!=r['member_sha256']:
                raise ValueError('SDK retained pinned source member differs')
            # Existing _floor owns a 64-byte primary and a complete 289-byte shared ledger
            # carrier. Preserve both extents and its original full branch protocol; no
            # new floor credit or artificial 64-byte ledger boundary is introduced.
            object_path.write_bytes(body)
            raw,fields=c.object_function(object_path,r['primary_symbol'],sdk.complete_comdat_size(body,r['primary_symbol'],c.coff_name) if r['library']=='d3dx8.lib' else None)
            if len(raw)!=r['source_size'] or digest(raw)!=r['source_sha256'] or fields!=r['fields']:
                raise ValueError('SDK retained whole own primary source extent differs')
            actual=c.pe_bytes_at(target,int(a,16),int(functions[a]['size']))
            if digest(actual)!=r['ledger_body_sha256']:raise ValueError('SDK retained entire native carrier differs')
            linked=bytearray(raw)
            if len(fields)!=len(r['bindings']):raise ValueError('SDK retained real field coverage differs')
            for f,b in zip(fields,r['bindings']):
                if any(f[k]!=b[k] for k in ('offset','type','symbol','addend','local_symbol_offset')):
                    raise ValueError('SDK retained genuine field differs')
                off=f['offset'];dest=int(b['target_address'],16)
                if f['addend'] or f['local_symbol_offset'] is not None or f['type'] not in ('REL32','DIR32'):
                    raise ValueError('SDK retained field outside original supported protocol')
                value=(dest-int(a,16)-off-4)&0xffffffff if f['type']=='REL32' else dest
                struct.pack_into('<I',linked,off,value)
            if bytes(linked)!=actual[:len(raw)]:raise ValueError('SDK retained complete primary bytes differ')
            if r['requested_symbol']!=r['primary_symbol']:
                _,defs=coff.parse_symbols(body,c.coff_name);verify_alias(defs,r['primary_symbol'],r['requested_symbol'])
                alias=[d for d in defs if d['symbol'] in (r['primary_symbol'],r['requested_symbol']) and d['section']>0]
                if alias!=r['alias_definitions']:raise ValueError('SDK actual full source alias metadata differs')
            callees[r['requested_symbol']]=int(a,16)
        for r in m['functions']:
            a=r['address'];state='original' if evidence_only else 'accepted'
            if functions[a]!=r[state+'_function'] or origins[a]!=r[state+'_origin']:
                raise ValueError('SDK bounded acceptance ledger differs: '+a)
            if any(int(a,16)<int(q,16)<int(a,16)+r['size'] for q in functions):
                raise ValueError('SDK complete extent hides another inventoried entry')
            h,name,body=member(m['library'],r['member_offset'])
            if h!=m['archive_sha256'] or name!=r['member'] or digest(body)!=r['member_sha256']:
                raise ValueError('SDK complete pinned archive/member identity differs')
            size=sdk.complete_comdat_size(body,r['symbol'],c.coff_name)
            if size!=r['size']:raise ValueError('SDK complete own COMDAT extent differs')
            object_path.write_bytes(body);raw,fields=c.object_function(object_path,r['symbol'],size)
            if digest(raw)!=r['source_sha256'] or fields!=r['fields']:raise ValueError('SDK whole source bytes/actual fields differ')
            def scalar(name,dest):
                literal=sdk.real_constant(body,name,c.coff_name)
                if not any(base<=dest and dest+len(literal)<=base+n and flags&0x40000000 and not flags&0x80000000
                           for base,n,flags in geometry.sections(target)):
                    raise ValueError('SDK scalar target is not complete readonly storage')
                if c.pe_bytes_at(target,dest,len(literal))!=literal:raise ValueError('SDK complete target scalar bytes differ')
                return literal
            linked,calls,data=bind_fields(raw,fields,r['bindings'],int(a,16),callees,imports,scalar)
            actual=c.pe_bytes_at(target,int(a,16),size)
            if bytes(linked)!=actual or digest(actual)!=r['body_sha256']:raise ValueError('SDK unmasked whole body comparison differs: '+a)
            if sdk.verify_control_flow(linked,int(a,16),calls,data)!=r['indirect_call_count'] or flow_counts(actual,int(a,16))!=r['cfg']:
                raise ValueError('SDK full control flow, exits or actual dispatch differs')

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    parser.add_argument('--replay-dependencies',action='store_true',help='Cold-replay every retained complete provenance graph serially.')
    args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,h in [(EVIDENCE,MANIFEST_SHA256),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=h:raise ValueError('SDK immutable evidence differs: '+path)
    replay_manifest(m,args.evidence_only)
    if args.replay_dependencies:
        for name in DEPENDENCIES:
            result=subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts'/('verify-'+name+'-origins.py'))],cwd=ROOT,capture_output=True,text=True)
            if result.returncode:raise ValueError('SDK retained full provenance replay failed: '+name+' '+result.stderr[-1200:])
            print(result.stdout.strip().splitlines()[-1])
    print('R184 origins OK: 15 whole pinned D3DX8 COMDATs /7667 bytes; all83 real fields independently bound without masking;10 retained full source/ledger carriers and genuine stack-probe alias; actual PE IATs and complete same-member readonly scalars; full native branches/exits and24 unchanged indirect calls; no source, ABI, mapping or exact credit.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
