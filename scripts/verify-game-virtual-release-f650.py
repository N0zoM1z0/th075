#!/usr/bin/env python3
"""F650: TWO new entire original native stdcall-vcall and free leaves.

Cold-compile only one affected ordinary VC7.1 C++ TU; independently
check 27+43 whole original PE machine CODE bytes, 14+17 original x86
roles and genuine zero-addend REL32 CRT free destination 00640F15.
Also decode true original callers in the 4351 native CODE extents.
Never duplicate prior F595 004135F0 accepted-as-source evidence;
source-origin stays UNKNOWN, zero new authored exact credit, no 943
all-unit cold replay.
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
SOURCE=ROOT/'probes/GameComVirtualAndConditionalReleaseF650.cpp'
OUT=ROOT/'.analysis/f650-game-virtual-release'
CASES={
    0x004170B0:{'size':27,'x86':14,'symbol':'?Dispatch@VirtualDispatchOwnerF650@@QAEXXZ',
                'fields':{},'calls':1,'authored_calls':0},
    0x004588B0:{'size':43,'x86':17,'symbol':'?Release@ConditionalReleaseOwnerF650@@QAEXXZ',
                'fields':{32:('REL32',0x00640F15,'_free')},'calls':6,'authored_calls':1},
}


def need(ok,why):
    if not ok:raise ValueError(why)


def reader_module():
    spec=importlib.util.spec_from_file_location('f650_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'native original COFF reader missing')
    m=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=m
    spec.loader.exec_module(m)
    return m


def cold_build():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'two-complete-original-object-leaves.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    process=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(process.stdout+process.stderr)
    need(process.returncode==0,
         'actual original pinned VC7.1 native leaf C++ compile failed: '+process.stderr[-530:])
    return obj


def check_whole(reader,pe,decoder,obj,addr,control):
    size=control['size'];nbytes=reader.pe_bytes_at(pe,addr,size)
    source,fields=reader.object_function(obj,control['symbol'],expected_size=size)
    native=list(decoder.disasm(nbytes,addr));gen=list(decoder.disasm(source,addr))
    need(len(source)==len(nbytes)==size
         and len(native)==len(gen)==control['x86']
         and sum(x.size for x in native)==sum(x.size for x in gen)==size
         and all((a.address,a.size,a.mnemonic,a.op_str if a.mnemonic!='call' else a.mnemonic)==
                 (b.address,b.size,b.mnemonic,b.op_str if b.mnemonic!='call' else b.mnemonic)
                 for a,b in zip(native,gen))
         and native[-1].mnemonic==gen[-1].mnemonic=='ret',
         f'{addr:#x}: actual original complete native PE x86/source opcode/width roles differ')
    expected_fields=control['fields']
    need(len(fields)==len(expected_fields),
         f'{addr:#x}: true native physical PE COFF count differs')
    linked=bytearray(source)
    for offset,(type_,target,sym) in expected_fields.items():
        found=[f for f in fields if f['offset']==offset]
        need(len(found)==1 and found[0]['type']==type_
             and found[0]['symbol']==sym and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None,
             f'{addr:#x}: genuine original COFF CRT source symbol/type/addend differs at {offset}')
        instruction=next((x for x in native if x.address<=addr+offset<x.address+x.size),None)
        need(instruction is not None and instruction.mnemonic=='call'
             and instruction.op_str==f'0x{target:x}',
             f'{addr:#x}: real original native PE free() call target not {target:#x}')
        val=(target-(addr+offset+4))&0xFFFFFFFF
        need(struct.unpack_from('<I',nbytes,offset)[0]==val
             and source[offset:offset+4]==b'\0'*4,
             f'{addr:#x}: native original PE REL32 operand not original physical offset32')
        struct.pack_into('<I',linked,offset,val)
    need(bytes(linked)==nbytes,
         f'{addr:#x}: entire genuine original 27/43B machine CODE bytes NOT identical')
    if addr==0x004170B0:
        need(native[8].mnemonic=='mov' and native[8].op_str=='ecx, dword ptr [ecx]'
             and native[9].mnemonic=='push' and native[9].op_str=='eax'
             and native[10].mnemonic=='call' and native[10].op_str=='dword ptr [ecx + 8]',
             'genuine native original stdcall third-virtual-call pointer/receiver ABI changed')
    else:
        need(native[2].mnemonic=='sub' and native[2].op_str=='esp, 8'
             and native[5].mnemonic=='cmp' and native[5].op_str=='dword ptr [eax + 8], 0'
             and native[6].mnemonic=='je'
             and native[9].mnemonic=='mov' and native[9].op_str=='dword ptr [ebp - 4], edx'
             and native[13].mnemonic=='add' and native[13].op_str=='esp, 4',
             'genuine original conditional release native pointer lifetime/stack changed')
    return {'actual_native_entire_original_address':f'0x{addr:08X}',
            'original_complete_native_CODE_bytes_identical':size,
            'complete_native_x86_roles':len(native),
            'all_physical_original_PE_targeted_CO_FF_fields':len(fields),
            'entire_original_linked_machine_CODE_equal':True,
            'original_source_origin':'unknown',
            'new_accepted_authored_exact_CODE_bytes':0}


def native_callers(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        rows=list(csv.DictReader(stream))
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={x['address']:x for x in csv.DictReader(stream)}
    need(len(rows)==4351,'original registered native function extents unexpectedly changed')
    for addr in CASES:
        origin=origins[f'0x{addr:08X}']
        need(origin['origin']=='unknown' and origin['disposition']=='review',
             f'{addr:#x}: historical original author-vs-vendor source ownership changed')
    uses={addr:[] for addr in CASES}
    for row in rows:
        start=int(row['address'],16)
        for x in decoder.disasm(reader.pe_bytes_at(pe,start,int(row['size'])),start):
            if x.mnemonic=='call' and x.op_str.startswith('0x'):
                target=int(x.op_str,16)
                if target in uses:
                    uses[target].append({'actual_original_PE_direct_CALL':f'0x{x.address:08X}',
                                         'original_registered_caller':row['address'],
                                         'current_original_caller_origin':row['owner'],
                                         'original_caller_provisional_name':row['proposed_name']})
    for addr,info in CASES.items():
        matches=uses[addr]
        authored=sum(q['current_original_caller_origin']=='authored' for q in matches)
        need(len(matches)==info['calls'] and authored==info['authored_calls'],
             f'{addr:#x}: original direct native PE caller provenance has changed')
    return uses


def main():
    reader=reader_module();pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    obj=cold_build()
    receipts=[]
    for addr,info in CASES.items():
        result=check_whole(reader,pe,decoder,obj,addr,info)
        receipts.append(result)
        print(f'F650 native {addr:#010x}: whole original '
              f'{result["original_complete_native_CODE_bytes_identical"]}/'
              f'{result["original_complete_native_CODE_bytes_identical"]} '
              f'linked CODE bytes, {result["complete_native_x86_roles"]} native x86, '
              f'{result["all_physical_original_PE_targeted_CO_FF_fields"]} true physical '
              'PE/COFF fields; original provenance UNKNOWN',flush=True)
    graph=native_callers(reader,pe,decoder)
    total=(len(receipts),sum(q['original_complete_native_CODE_bytes_identical'] for q in receipts),
           sum(q['complete_native_x86_roles'] for q in receipts),
           sum(q['all_physical_original_PE_targeted_CO_FF_fields'] for q in receipts))
    need(total==(2,70,31,1),f'original whole native source 2/70/31/1 accounting changed {total}')
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps({
       'pinned_original_pe_sha256':hashlib.sha256(pe).hexdigest(),
       'normal_vc71_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
       'original_pinned_compiler_flags':'/Od /Ob0 /Gy /GR- /GX- /GS /Zi',
       'two_new_distinct_whole_original_native_functions':receipts,
       'actual_real_original_PE_direct_call_graph':{f'0x{x:08X}':v for x,v in graph.items()},
       'independent_actual_native_registered_function_extents_scanned':4351,
       'new_source_backed_whole_original_CODE_bytes_UNCREDITED':70,
       'historical_prior_F595_004135F0_not_counted_again':True,
       'new_accepted_authored_whole_functions':0,
       'full_943_unit_cold_replay_performed':False},indent=2)+'\n')
    print('F650 two newly reconstructed complete original game functions, '
          '70/70 original native linked CODE bytes, 31/31 original x86, '
          '1 original PE-targeted typed COFF free() call. Prior F595 '
          'three-field setter NOT double-counted; original provenance '
          'still UNKNOWN, no authored exact credit or all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F650 actual original TH075 full native COM/free source proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
