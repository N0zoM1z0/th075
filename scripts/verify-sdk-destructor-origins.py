#!/usr/bin/env python3
"""Reopen explicit SDK destructors and preserve independently generated wrappers."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('sdk_destructor_parent',ROOT/'scripts/verify-sdk-interface-origins.py')
PARENT=importlib.util.module_from_spec(spec);spec.loader.exec_module(PARENT)
module=PARENT.module;digest=PARENT.digest
EVIDENCE='config/sdk-destructor-origin-evidence.json'
MANIFEST_SHA256='506e7fac5ff1cc392d381c1e16373fc15f9d0285158793ddfff0d5658262ccd1'
KEYS={'0x0061FE0A':21,'0x00609EEF':34,'0x0060A7D2':34}
CONFIDENCE='whole-pinned-sdk-destructor-with-independent-interface-and-explicit-cleanup-context'
PROFILE=['/Od','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/showIncludes']


def verify_plan(m):
    if (m['evidence_id']!='R187' or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=3
            or len(m['controls'])!=7 or [r['size'] for r in m['controls']]!=[5,15,44,35,15,44,35]
            or len(m['emission'])!=8 or sum(r['size'] for r in m['emission'])!=205 or len(m['headers'])!=84
            or len(m['wrappers'])!=3 or {r['record']['destructor_address'] for r in m['wrappers']}!=set(KEYS)
            or m['probe']!='probes/VC7SDKReleasePolicies.cpp' or m['profile']!=PROFILE
            or m['layout_values']!=[4,4,4] or m['layout'] not in m['emission'] or m['layout']['size']!=12
            or sum(len(r['source_record']['fields']) for r in m['functions'])!=6):
        raise ValueError('SDK destructor loses whole explicit/generated/owner scope')
    prior=json.loads((ROOT/'config/sdk-interface-origin-evidence.json').read_text());old={r['address']:r for r in prior['code']}
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];original,new=r['original_function'],r['accepted_function']
        if (r['source_record']!=old[a] or original!=old[a]['function'] or r['original_origin']!=old[a]['origin']
                or r['original_origin']['origin']!='unknown' or new['owner']!='library' or new['status']!='excluded' or new['module']!='D3DX8'
                or {k:v for k,v in original.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or int(original['size'])!=r['size'] or int(original['span_end'],16)!=int(a,16)+r['size']-1
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['body_sha256']!=old[a]['body_sha256']
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='D3DX8',disposition='exclude',confidence=CONFIDENCE,evidence_id='R187')):
            raise ValueError('SDK destructor alters original source/native facts or grants ABI/source/exact credit')
    for r in m['controls']:
        if r['section'] not in m['emission'] or r['size']!=r['section']['size'] or 'target_address' in r or 'target_positive' in r:
            raise ValueError('SDK source policy control becomes a false original owner/comparison')
    if m['controls'][0]['section']['fields'] or m['controls'][0]['calls'] or m['controls'][0]['indirect_calls']:
        raise ValueError('SDK implicit raw-pointer destruction gains an invented cleanup call')
    for index,slot in [(3,28),(6,44)]:
        if m['controls'][index]['indirect_calls']!=1 or m['controls'][index]['api_slots']!=[slot]:
            raise ValueError('SDK explicit public cleanup loses actual interface call slot')
    for index,callee in [(1,'??_GExplicitSurfaceLease@@QAEPAXI@Z'),(4,'??_GExplicitEnvMapLease@@QAEPAXI@Z')]:
        if m['controls'][index]['call_symbols']!=[callee]:raise ValueError('SDK explicit end caller loses genuine generated wrapper route')
    for index,callee in [(2,'??1ExplicitSurfaceLease@@QAE@XZ'),(5,'??1ExplicitEnvMapLease@@QAE@XZ')]:
        if m['controls'][index]['call_symbols']!=[callee,'??3@YAXPAX@Z'] or m['controls'][index]['size']!=44:
            raise ValueError('SDK source wrapper loses its entire flag/destructor/delete policy')


def retained_digest_matches(path,expected):
    actual=digest((ROOT/path).read_bytes())
    if actual==expected:return True
    allowed={'scripts/verify-sdk-interface-origins.py': ('57f9ded32b394ddff62911e474b269da98c90152fff9a79c2c0a170059f1464c', '75b3979be88b4d60a24a67adc971c161f00086e310b162de4bf2ce2ff0fe42ae')}
    return allowed.get(path)==(expected,actual)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,h in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if not retained_digest_matches(path,h):raise ValueError('SDK destructor immutable source/prior evidence differs: '+path)
    c=module('destructor_target','compare-coff-function.py');rt=module('destructor_archive','verify-runtime-origins.py');coff=module('destructor_coff','coff_data.py');sdk=module('destructor_extent','verify-sdk-origins.py');cfg=module('destructor_cfg','verify-authored-origins.py');inventory=module('destructor_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target=c.verified_target();functions={r['address']:r for r in PARENT.BASE.rows('config/functions.csv')};origins={r['address']:r for r in PARENT.BASE.rows('config/function-origins.csv')};prior=json.loads((ROOT/'config/sdk-interface-origin-evidence.json').read_text());catalog={k:int(v,16) for k,v in prior['catalog'].items()}
    archive=(ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(target)!=m['target_sha256'] or digest(archive)!=m['archive_sha256']:raise ValueError('SDK destructor target/archive identity differs')
    members={o:(n,b) for o,n,b in rt.archive_members(archive)};scratch=ROOT/'build/origin-sdk-destructor-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'Destructor.obj'
        for r in m['functions']:
            a=r['address'];old=r['source_record'];state='original' if args.evidence_only else 'accepted'
            if functions[a]!=r[state+'_function'] or origins[a]!=r[state+'_origin']:raise ValueError('SDK destructor canonical acceptance differs')
            if any(int(a,16)<int(q,16)<int(a,16)+r['size'] for q in functions):raise ValueError('SDK destructor extent hides another inventoried entry')
            name,body=members[old['member_offset']]
            if name!=old['member'] or digest(body)!=old['member_sha256'] or sdk.complete_comdat_size(body,old['symbol'],c.coff_name)!=r['size']:
                raise ValueError('SDK destructor loses whole independently derived own COMDAT')
            obj.write_bytes(body);raw,fields=c.object_function(obj,old['symbol'],r['size']);linked,calls,data=PARENT.link_code(raw,fields,old['bindings'],int(a,16),catalog);actual=c.pe_bytes_at(target,int(a,16),r['size'])
            if fields!=old['fields'] or digest(raw)!=old['source_sha256'] or linked!=actual or digest(actual)!=r['body_sha256'] or list(cfg.verify_body(actual,int(a,16)))!=old['cfg'] or sdk.verify_control_flow(linked,int(a,16),calls,data)!=old['indirect_call_count']:
                raise ValueError('SDK destructor whole unmasked fields/CFG differ')
        for r in m['wrappers']:
            a=r['record']['address'];actual=c.pe_bytes_at(target,int(a,16),28)
            if r['record'] not in PARENT.BASE.rows('config/optimized-deleting-origin-evidence.csv') or functions[a]!=r['function'] or origins[a]!=r['origin'] or digest(actual)!=r['record']['body_sha256']:
                raise ValueError('SDK destructor changes independently generated R038 wrapper facts')
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(obj),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or PARENT.included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('SDK destructor cold public policy/actual includes differ')
        emitted=obj.read_bytes()
        if inventory(emitted,c,coff)!=m['emission']:raise ValueError('SDK destructor drops a full ordinary source code/data section')
        for r in m['controls']:
            size=sdk.complete_comdat_size(emitted,r['symbol'],c.coff_name);raw,fields=c.object_function(obj,r['symbol'],size)
            decoder=module('destructor_capstone','verify-sdk-origins.py').capstone.Cs(sdk.capstone.CS_ARCH_X86,sdk.capstone.CS_MODE_32);decoder.detail=True;ins=list(decoder.disasm(bytes(raw),0));w=[dict(site=i.address,mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            indirect=[i for i in ins if i.group(sdk.capstone.CS_GRP_CALL) and i.operands[0].type!=sdk.capstone.x86.X86_OP_IMM]
            slots=[i.operands[0].mem.disp for i in indirect if i.operands[0].type==sdk.capstone.x86.X86_OP_MEM]
            if size!=r['size'] or digest(raw)!=r['source_sha256'] or fields!=r['fields'] or list(cfg.verify_body(raw,0))!=r['cfg'] or w!=r['witnesses'] or len(indirect)!=r['indirect_calls'] or slots!=r['api_slots']:
                raise ValueError('SDK destructor whole generated/public policy facts differ')
        raw,_=coff.readonly_section(emitted,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<3I',raw))!=[4,4,4]:raise ValueError('SDK observer complete pointer layout differs')
    for filename in ('verify-sdk-interface-origins.py','verify-optimized-deleting-origins.py'):
        result=subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts'/filename)],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('SDK destructor retained whole provenance replay failed: '+result.stderr[-1400:])
        print(result.stdout.strip().splitlines()[-1])
    print('R187 origins OK: three entire explicit SDK destructor policies /89 bytes with all6 genuine fields;whole R186 interface/GUID/owner graph retained;seven full natural implicit/explicit/generated public controls /193 bytes,eight ordinary sections /205 bytes,84 actual headers,12-byte observer layout;three R038 wrappers preserved and all53 /1484 bytes cold-replayed;no private game layout,source,ABI,mapping or exact credit.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
