#!/usr/bin/env python3
"""F648: eight complete native game-facing state/member adapter leaves.

Cold compile ONLY the affected single pinned VC7.1 C++ source TU.
Compare each entire original 15/22/24/27/28-B native function,
all 73 x86 roles, six physical true zero-addend REL32 COFF target
fields, and actual original direct caller graph. Their historical
C++ authored-vs-library/compiler ownership remains UNKNOWN: no exact
authored acceptance, fake locals, ASM or 943-unit cold replay.
"""
from __future__ import annotations
import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/GameStateSetterAndMemberForwardF648.cpp'
OUT=ROOT/'.analysis/f648-game-state-forward-verified'
# Original physically registered complete native PE CODE extents.
# C++ class/symbol names are provisional compiler-grammar hypotheses.
CASES={
    0x00410FC0:(24,10,'?Set@ModeSetterF648@@QAEXF@Z',None,None,0,0),
    0x0045B6F0:(27,13,'?Advance@PointerAdvanceF648@@QAEPAV1@XZ',None,None,1,0),
    0x00458770:(22,10,'?ResetMember@StateOwnerF648@@QAEXXZ',14,0x00411C70,1,0),
    0x004229D0:(28,12,'??0StatefulOwnerF648@@QAE@H@Z',15,0x00422A50,1,0),
    0x0040F9F0:(15,7,'?ForwardAt40F9F0@@YAXPAVObjectAt40FA00F648@@@Z',9,0x0040FA00,1,0),
    0x004229C0:(15,7,'?ForwardAt4229C0@@YAXPAVObjectAt422A20F648@@@Z',9,0x00422A20,1,0),
    0x0045B6B0:(15,7,'?ForwardAt45B6B0@@YAXPAVObjectAt45B6C0F648@@@Z',9,0x0045B6C0,1,0),
    0x005FAAD0:(15,7,'?ForwardAt5FAAD0@@YAXPAVObjectAt5FAAE0F648@@@Z',9,0x005FAAE0,1,0),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def reader_module():
    name='f648_reader'
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'original PE/COFF reader missing')
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def build():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'eight-complete-native-game-leaves.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,
         'original pinned VC7.1 normal whole small-source C++ compilation failed: '+cp.stderr[-470:])
    return obj


def compare_whole(reader,pe,decoder,obj,addr,info):
    size,count,symbol,offset,target,_,_=info
    original=reader.pe_bytes_at(pe,addr,size)
    produced,fields=reader.object_function(obj,symbol,expected_size=size)
    n=list(decoder.disasm(original,addr));g=list(decoder.disasm(produced,addr))
    need(len(original)==len(produced)==size
         and len(n)==len(g)==count
         and sum(x.size for x in n)==sum(x.size for x in g)==size
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(n,g))
         and n[-1].mnemonic==g[-1].mnemonic=='ret',
         f'{addr:#x}: complete original 15/22/24/27/28-byte native x86 source geometry differs')
    need(len(fields)==(1 if offset is not None else 0),
         f'{addr:#x}: actual native original source COFF fields wrong')
    linked=bytearray(produced)
    if offset is not None:
        f=fields[0]
        need(f['offset']==offset and f['type']=='REL32'
             and f['addend']==0 and f['local_symbol_offset'] is None
             and f['symbol'] and f['symbol'].startswith('?'),
             f'{addr:#x}: genuine typed zero-addend PE target at +{offset:#x} differs')
        ins=next((x for x in n if x.address<=addr+offset<x.address+x.size),None)
        need(ins is not None and ins.mnemonic=='call' and ins.op_str==f'0x{target:x}',
             f'{addr:#x}: native original game CALL PE destination {target:#x} not genuine')
        relative=(target-(addr+offset+4)) & 0xFFFFFFFF
        need(struct.unpack_from('<I',original,offset)[0]==relative
             and produced[offset:offset+4]==b'\0'*4,
             f'{addr:#x}: original physically owned REL32 call bytes are not correct')
        struct.pack_into('<I',linked,offset,relative)
    need(bytes(linked)==original,
         f'{addr:#x}: original whole linked native machine CODE byte mismatch; no partial exact credit')
    return {'actual_original_whole_registered_function':f'0x{addr:08X}',
            'original_complete_native_CODE_bytes':size,
            'entire_original_x86_instructions':count,
            'original_full_native_linked_bytes_identical':True,
            'genuine_original_typed_PE_COFF_targets':len(fields),
            'true_original_native_callee':None if target is None else f'0x{target:08X}',
            'provisional_normal_CPP_compiler_source':symbol,
            'original_source_provenance':'unknown',
            'new_accepted_authored_whole_CODE_bytes':0}


def original_callers(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        original_functions=list(csv.DictReader(stream))
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        provenance={x['address']:x for x in csv.DictReader(stream)}
    need(len(original_functions)==4351,
         'pinned original whole function extent cohort changed')
    for addr in CASES:
        origin=provenance[f'0x{addr:08X}']
        need(origin['origin']=='unknown' and origin['disposition']=='review',
             f'{addr:#x}: historical authored-vs-generated provenance changed')
    direct={addr:[] for addr in CASES}
    for row in original_functions:
        begin=int(row['address'],16)
        for instruction in decoder.disasm(reader.pe_bytes_at(pe,begin,int(row['size'])),begin):
            if instruction.mnemonic=='call' and instruction.op_str.startswith('0x'):
                target=int(instruction.op_str,16)
                if target in direct:
                    direct[target].append({
                         'actual_original_native_CALL_instruction':f'0x{instruction.address:08X}',
                         'original_registered_parent':row['address'],
                         'current_parent_origin':row['owner'],
                         'provisional_parent_name':row['proposed_name']})
    for addr,info in CASES.items():
        count=len(direct[addr])
        authored=sum(x['current_parent_origin']=='authored' for x in direct[addr])
        need((count,authored)==info[5:7],
             f'{addr:#x}: original game direct-call graph count changed {count}/{authored}')
    return direct


def main():
    rd=reader_module()
    pe=rd.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    obj=build()
    rows=[]
    for addr,info in CASES.items():
        row=compare_whole(rd,pe,decoder,obj,addr,info)
        rows.append(row)
        print(f'F648 native {addr:#010x}: {row["original_complete_native_CODE_bytes"]}/'
              f'{row["original_complete_native_CODE_bytes"]} original WHOLE linked CODE bytes, '
              f'{row["entire_original_x86_instructions"]} native x86, '
              f'{row["genuine_original_typed_PE_COFF_targets"]} real physical PE-targeted refs; '
              'original historical source owner UNKNOWN',flush=True)
    direct=original_callers(rd,pe,decoder)
    total=(len(rows),sum(x['original_complete_native_CODE_bytes'] for x in rows),
           sum(x['entire_original_x86_instructions'] for x in rows),
           sum(x['genuine_original_typed_PE_COFF_targets'] for x in rows))
    need(total==(8,161,73,6),
         f'actual original full native code accounting changed {total}')
    report={'pinned_original_PE_SHA256':hashlib.sha256(pe).hexdigest(),
            'ordinary_CXX_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            'actual_normal_VC71_compiler_profile':'/Od /Ob0 /Gy /GR- /GX- /GS /Zi',
            'entire_source_backed_native_original_functions':rows,
            'independent_all_registered_native_original_CODE_extents_scanned':4351,
            'genuine_original_native_direct_CALL_graph':{
                f'0x{addr:08X}':v for addr,v in direct.items()},
            'eight_complete_original_source_backed_CODE_bytes_uncredited':161,
            'new_authored_whole_exact_functions':0,
            'new_accepted_whole_authored_CODE_bytes':0,
            'all_unit_cold_replay_performed':False}
    (OUT/'summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F648 eight ENTIRE original native game-facing functions, '
          '161/161 machine CODE bytes, 73/73 x86, six genuine typed '
          'PE/COFF original calls; all provenance unknown, ZERO new '
          'accepted authored whole exact CODE. No 943-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F648 original Japanese TH075 complete state/forward leaf proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
