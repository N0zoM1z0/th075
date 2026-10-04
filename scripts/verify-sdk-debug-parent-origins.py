#!/usr/bin/env python3
"""Replay complete D3DX parents while retaining a generic buffer-init ambiguity."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT=Path(__file__).resolve().parents[1]
import importlib.util
spec=importlib.util.spec_from_file_location('sdk_debug_shared',ROOT/'scripts/verify-sdk-file-image-origins.py')
BASE=importlib.util.module_from_spec(spec);spec.loader.exec_module(BASE)
EVIDENCE='config/sdk-debug-parent-origin-evidence.json'
MANIFEST_SHA256='aa0b86119baf570d7308dfe0cca2123e2ef646a20ad108c862adea7b062d4a1c'
KEYS={'0x0060D11A':375,'0x0060D044':214,'0x0061FC02':49,'0x00610F96':48,'0x006255A0':38}

def verify_plan(m):
    BASE.verify_plan(m,evidence_id='R185',keys=KEYS,field_count=16,retained_count=6,dependencies=['sdk-file-image','sdk'])
    p=m['pending'];record=p['comparison'];ctor=next((r for r in m['retained'] if r['requested_symbol']=='??0CD3DXSzStack@@QAE@XZ'),None)
    if (ctor is None or p['address']!='0x0061FE1F' or p['size']!=38 or p['origin']['origin']!='unknown'
            or p['function']['owner'] or 'accepted_origin' in p or record['symbol']!='?Init@CD3DXBuffer@@UAEJK@Z'
            or record['address']!=p['address'] or int(p['function']['size'])!=38
            or int(p['function']['span_end'],16)!=int(p['address'],16)+37
            or record['size']!=38 or len(record['fields'])!=1 or record['bindings'][0]['symbol']!='??2@YAPAXI@Z'
            or ctor['address']!='0x0061FBEF' or ctor['source_size']!=19
            or 'reviewed complete vendor constructor and push context' not in m['functions'][2]['accepted_function']['notes']):
        raise ValueError('SDK debug loses full typed owner context or resolves ambiguous buffer initialization')

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,h in [(EVIDENCE,MANIFEST_SHA256),*m['retained_sha256'].items()]:
        if BASE.digest((ROOT/path).read_bytes())!=h:raise ValueError('SDK debug immutable evidence differs: '+path)
    # Same retained source/ABI inputs: replay the complete R184 source archive graph
    # and original SDK typed short-owner evidence, without repeating cold chains.
    for filename in ('verify-sdk-file-image-origins.py','verify-sdk-origins.py'):
        result=subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts'/filename)],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('SDK debug complete original library graph failed: '+result.stderr[-1200:])
        print(result.stdout.strip().splitlines()[-1])
    BASE.replay_manifest(m,args.evidence_only)
    c=BASE.module('debug_pending_target','compare-coff-function.py');runtime=BASE.module('debug_pending_archive','verify-runtime-origins.py');sdk=BASE.module('debug_pending_extent','verify-sdk-origins.py');target=c.verified_target()
    p=m['pending'];r=p['comparison'];functions={q['address']:q for q in BASE.rows('config/functions.csv')};origins={q['address']:q for q in BASE.rows('config/function-origins.csv')}
    if functions[p['address']]!=p['function'] or origins[p['address']]!=p['origin']:raise ValueError('SDK debug changes original pending buffer-init row')
    archive=(ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if BASE.digest(archive)!=m['archive_sha256']:raise ValueError('SDK debug pending archive differs')
    name,body=next((name,body) for off,name,body in runtime.archive_members(archive) if off==r['member_offset'])
    if name!=r['member'] or BASE.digest(body)!=r['member_sha256'] or sdk.complete_comdat_size(body,r['symbol'],c.coff_name)!=r['size']:
        raise ValueError('SDK debug pending entire own COMDAT differs')
    import tempfile
    with tempfile.TemporaryDirectory(dir=ROOT/'build/origin-sdk-file-image-verification') as temp:
        path=Path(temp)/'pending.obj';path.write_bytes(body);raw,fields=c.object_function(path,r['symbol'],r['size'])
        if fields!=r['fields'] or BASE.digest(raw)!=r['source_sha256']:raise ValueError('SDK debug pending complete source fields differ')
        callees={q['requested_symbol']:int(q['address'],16) for q in m['retained']}
        linked,calls,data=BASE.bind_fields(raw,fields,r['bindings'],int(p['address'],16),callees,{},lambda n,a:None)
        actual=c.pe_bytes_at(target,int(p['address'],16),r['size'])
        if linked!=actual or BASE.digest(actual)!=r['body_sha256'] or BASE.flow_counts(actual,int(p['address'],16))!=r['cfg'] or sdk.verify_control_flow(linked,int(p['address'],16),calls,data)!=r['indirect_call_count']:
            raise ValueError('SDK debug pending full unmasked comparison differs')
    print('R185 origins OK: five whole D3DX parents/leaves /724 bytes,all16 genuine calls unmasked;six full retained source records including complete SDK stack constructor;complete38-byte buffer initializer matches but stays unknown without independent owning context;R184 and original typed SDK provenance preserved;no source/ABI/mapping/exact credit.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
