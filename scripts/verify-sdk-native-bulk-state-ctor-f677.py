#!/usr/bin/env python3
"""F677: entire original optimized 104-byte SDK-like zeroing constructor.

Compile only ONE small, ordinary pinned VC7.1 /O1 /Oi C++ TU.
Independently verify true original 34-instruction/104-byte native PE
extent, exact original memory zeroing loop and REP STOSD, real vtable
DIR32 field and 104 linked original bytes. Never credit original
source ownership beyond UNKNOWN; no all-unit replay.
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
SOURCE=ROOT/'probes/SDKNativeBulkStateCtorF677.cpp'
OUT=ROOT/'.analysis/f677-native-sdk-bulk-ctor'
ADDR=0x0060B728
SIZE=104
X86=34
VFTABLE=0x0065D3C0
OFFSET=10
SYMBOL='??0SDKProbeE@@QAE@XZ'
VFSYM='??_7SDKProbeE@@6B@'


def need(ok,msg):
    if not ok:raise ValueError(msg)


def reader_tool():
    s=importlib.util.spec_from_file_location('f677_reader',ROOT/'scripts/compare-coff-function.py')
    need(s is not None and s.loader is not None,'missing original PE/COFF native source parser')
    m=importlib.util.module_from_spec(s);sys.modules[s.name]=m;s.loader.exec_module(m)
    return m


def compile_original_optimized_source():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'original-SDK-bulk-state-constructor.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
          '/O1','/Oi','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned original VC7.1 /O1 /Oi compile failed: '+cp.stderr[-550:])
    return obj


def verify_native(reader,pe,decoder,obj,functions,origins):
    info=functions.get(ADDR)
    need(info is not None and int(info['size'])==SIZE,
         'original 0060B728 complete registered native function extent changed')
    origin=origins[f'0x{ADDR:08X}']
    need(origin['origin']=='unknown' and origin['disposition']=='review',
         'original SDK bulk-state source origin no longer UNKNOWN')
    native=reader.pe_bytes_at(pe,ADDR,SIZE)
    compiled,fields=reader.object_function(obj,SYMBOL,expected_size=SIZE)
    need(len(fields)==1 and fields[0]['type']=='DIR32'
         and fields[0]['offset']==OFFSET and fields[0]['symbol']==VFSYM
         and fields[0]['addend']==0 and fields[0]['local_symbol_offset'] is None,
         'native entire optimized constructor must have exact one zero-addend vftable DIR32 COFF field')
    need(struct.unpack_from('<I',native,OFFSET)[0]==VFTABLE
         and compiled[OFFSET:OFFSET+4]==b'\x00'*4,
         'actual original native PE/vtable physical reference value differs')
    linked=bytearray(compiled)
    struct.pack_into('<I',linked,OFFSET,VFTABLE)
    need(bytes(linked)==native,
         'entire original 104 CODE bytes do not match normal newly compiled source')
    n=list(decoder.disasm(native,ADDR));g=list(decoder.disasm(bytes(linked),ADDR))
    need(len(n)==len(g)==X86
         and sum(x.size for x in n)==sum(x.size for x in g)==SIZE
         and all((a.size,a.mnemonic,a.op_str)==(b.size,b.mnemonic,b.op_str)
                 for a,b in zip(n,g))
         and n[-1].mnemonic==g[-1].mnemonic=='ret',
         'original entire 34 native x86/104-byte physical instruction roles/epilogue differ')
    need(n[0].op_str=='edx, ecx' and n[1].op_str=='esi'
         and n[2].op_str=='esi, esi' and n[3].op_str=='edi'
         and n[4].op_str=='2'
         and n[5].op_str==f'dword ptr [edx], 0x{VFTABLE:x}'
         and n[14].op_str=='eax, [edx + 0x40]'
         and n[16].op_str=='dword ptr [eax - 8], esi'
         and n[17].op_str=='dword ptr [eax], esi'
         and n[20].mnemonic=='jne'
         and n[22].op_str=='ecx, 0x104'
         and n[23].op_str=='edi, [edx + 0x50]'
         and n[24].mnemonic=='rep stosd'
         and n[26].op_str=='dword ptr [edx + 0x460], esi'
         and n[29].op_str=='dword ptr [edx + 0x490], esi',
         'actual original optimized two-member loop or full 0x410B REP STOSD initialization grammar changed')
    return {'complete_original_native_PE_start':f'0x{ADDR:08X}',
            'original_entire_CODE_bytes_exact':SIZE,
            'original_entire_native_x86_instructions':X86,
            'actual_original_typed_PE_COFF_DIR32_fields':1,
            'actual_original_vftable_PE_target':f'0x{VFTABLE:08X}',
            'native_two_member_zeroing_loop_trip_count':2,
            'native_REP_STOSD_real_DWORD_count':0x104,
            'original_first_bulk_zero_offset':'0x50',
            'original_last_bulk_zero_offset_exclusive':'0x460',
            'pinned_source_compiler_profile':'VC7.1 /O1 /Oi /Ob0 /Gy /GR- /GX- /GS /Zi',
            'historical_original_source_owner':'unknown',
            'new_accepted_whole_GAME_AUTHORED_CODE_bytes':0}


def original_registered_callers(reader,pe,decoder,functions):
    callers=[]
    for addr,meta in functions.items():
        for x in decoder.disasm(reader.pe_bytes_at(pe,addr,int(meta['size'])),addr):
            if x.mnemonic=='call' and x.op_str==f'0x{ADDR:x}':
                callers.append({'original_native_CALL':f'0x{x.address:08X}',
                                'original_registered_caller':f'0x{addr:08X}',
                                'current_caller_origin':meta['owner']})
    return callers


def main():
    reader=reader_tool();pe=reader.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions={int(row['address'],16):row for row in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={row['address']:row for row in csv.DictReader(stream)}
    need(len(functions)==len(origins)==4351,'original registered native inventory changed')
    obj=compile_original_optimized_source()
    proof=verify_native(reader,pe,dec,obj,functions,origins)
    callers=original_registered_callers(reader,pe,dec,functions)
    need(len(callers)==1 and callers[0]['current_caller_origin']=='library',
         'original 0060B728 registered native direct caller count/role changed')
    receipt={'pinned_original_native_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'natural_cpp_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'true_whole_native_optimized_ctor_source_backed':proof,
             'registered_original_direct_CALLs':callers,
             'new_distinct_whole_native_origin_UNKNOWN_functions':1,
             'new_complete_original_source_backed_native_CODE_bytes':SIZE,
             'new_accepted_whole_authored_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F677: original complete optimized 0060B728 SDK-like constructor '
          '104/104 real linked CODE B, 34/34 whole native x86, one genuine '
          'original zero-addend DIR32 vftable field, authentic two-trip '
          'member loop and 0x104-DWORD REP STOSD. Normal pinned VC7.1 '
          '/O1 /Oi C++ source; owner UNKNOWN, zero authored CODE credit. '
          'Only one small TU cold compiled, no mass replay.')


if __name__=='__main__':
    main()
