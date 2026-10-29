#!/usr/bin/env python3
"""F658: 19 complete original source-UNKNOWN native leaf byte identities.

Cold-build only one small ordinary VC7.1 TU. Compare entire genuine PE
function CODE byte-for-byte, including each full instruction stream and
zero actual COFF fields; keep all original source ownership UNKNOWN.
Scan original registered direct CALLs only as contextual evidence.
"""
from __future__ import annotations
import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/GameUnattributedSimpleLeavesF658.cpp'
OUT=ROOT/'.analysis/f658-unattributed-simple-leaves'
# Actual original PE function extent, number of native x86 instructions,
# COFF symbol name produced by genuine pinned VC7.1. These are NOT
# historical name/type or author-identity declarations.
CASES={
  0x00412580:(5,4,'_Empty_00412580'),
  0x00412600:(5,4,'_Empty_00412600'),
  0x0041F9F0:(5,4,'_Empty_0041F9F0'),
  0x0041FDF0:(5,4,'_Empty_0041FDF0'),
  0x0042E580:(5,4,'_Empty_0042E580'),
  0x00532480:(5,4,'_Empty_00532480'),
  0x00532500:(5,4,'_Empty_00532500'),
  0x00411E80:(8,5,'_IdentityArg_00411E80'),
  0x0041E100:(8,5,'_IdentityArg_0041E100'),
  0x00531D80:(8,5,'_IdentityArg_00531D80'),
  0x00411E90:(11,6,'_Plus4_00411E90'),
  0x0041E110:(11,6,'_Plus4_0041E110'),
  0x00531D90:(11,6,'_Plus4_00531D90'),
  0x004124C0:(11,6,'_Plus8_004124C0'),
  0x0040E9B0:(16,9,'?Get@FirstField_0040E9B0@@QAEPAXXZ'),
  0x0040EA20:(16,9,'?Get@FirstField_0040EA20@@QAEPAXXZ'),
  0x004124B0:(16,9,'?Get@FirstField_004124B0@@QAEPAXXZ'),
  0x00532350:(16,9,'?Get@FirstField_00532350@@QAEPAXXZ'),
  0x0041E330:(14,8,'?Get@Receiver_0041E330@@QAEPAV1@XZ'),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def canonical_reader():
    spec=importlib.util.spec_from_file_location('f658_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'missing canonical original PE/COFF parser')
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module
    spec.loader.exec_module(module)
    return module


def fresh_cpp_object():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'nineteen-original-whole-native-leaves.obj'
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    process=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
           '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=ROOT,
           env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(process.stdout+process.stderr)
    need(process.returncode==0,'pinned VC7.1 new source compilation failed: '+process.stderr[-500:])
    return obj


def verify_entire_one(reader,pe,decoder,obj,addr,control,functions,origins):
    size,num,symbol=control
    need(addr in functions and int(functions[addr]['size'])==size,
         f'{addr:#x}: original registered full CODE function boundary changed')
    info=origins[f'0x{addr:08X}']
    need(info['origin']=='unknown' and info['disposition']=='review',
         f'{addr:#x}: historical original source attribution status differs')
    native=reader.pe_bytes_at(pe,addr,size)
    generated,fields=reader.object_function(obj,symbol,expected_size=size)
    original_x86=list(decoder.disasm(native,addr))
    generated_x86=list(decoder.disasm(generated,addr))
    need(not fields and len(native)==len(generated)==size
         and len(original_x86)==len(generated_x86)==num
         and sum(x.size for x in original_x86)==sum(x.size for x in generated_x86)==size
         and original_x86[-1].mnemonic==generated_x86[-1].mnemonic=='ret'
         and all((a.size,a.mnemonic,a.op_str)==(b.size,b.mnemonic,b.op_str)
                 for a,b in zip(original_x86,generated_x86))
         and native==generated,
         f'{addr:#x}: entire genuine PE native 5/8/11/14/16-byte CODE is not source-byte-exact')
    return {'native_original_full_start':f'0x{addr:08X}',
            'original_complete_native_CODE_bytes_identical':size,
            'original_full_native_x86_instructions':num,
            'actual_physical_COFF_relocations':0,
            'provisional_source_grammar_symbol':symbol,
            'original_source_origin':'unknown',
            'new_authored_exact_function_credit':0}


def actual_native_callers(reader,pe,decoder,functions):
    graph={addr:[] for addr in CASES}
    for address,record in functions.items():
        for ins in decoder.disasm(reader.pe_bytes_at(pe,address,int(record['size'])),address):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                target=int(ins.op_str,16)
                if target in graph:
                    graph[target].append({'original_PE_CALL':f'0x{ins.address:08X}',
                                          'original_caller_start':f'0x{address:08X}',
                                          'current_caller_classification':record['owner']})
    return graph


def main():
    reader=canonical_reader();pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as f:
        functions={int(x['address'],16):x for x in csv.DictReader(f)}
    with (ROOT/'config/function-origins.csv').open(newline='') as f:
        origins={x['address']:x for x in csv.DictReader(f)}
    need(len(functions)==len(origins)==4351,'registered original native function inventory changed')
    obj=fresh_cpp_object()
    results=[verify_entire_one(reader,pe,decoder,obj,addr,control,functions,origins)
             for addr,control in CASES.items()]
    actual=(len(results),sum(r['original_complete_native_CODE_bytes_identical'] for r in results),
            sum(r['original_full_native_x86_instructions'] for r in results),
            sum(r['actual_physical_COFF_relocations'] for r in results))
    need(actual==(19,181,111,0),f'actual original 19/181/111/0 whole-byte proof changed: {actual}')
    callers=actual_native_callers(reader,pe,decoder,functions)
    receipt={'pinned_native_original_PE_sha256':hashlib.sha256(pe).hexdigest(),
             'natural_Cplusplus_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'original_complete_NATIVE_source_matches':results,
             'independent_original_PE_direct_CALL_graph':{f'0x{addr:08X}':v for addr,v in callers.items()},
             'count_entire_distinct_origin_UNKNOWN_functions':len(results),
             'original_entire_unknown_NATIVE_CODE_bytes':actual[1],
             'new_authored_exact_whole_function_bytes':0}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F658: fresh VC7.1 entire native original PE leaf proof: 19 distinct '
          'origin-UNKNOWN entire functions, 181/181 native CODE bytes, '
          '111 native x86 roles, zero genuine COFF fields. No authored CODE '
          'credit, no original provenance changes or mass cold replay.')
    for addr,rows in callers.items():
        print(f' original {addr:#010x}: {len(rows)} native direct caller instructions; '
              f'{sum(r["current_caller_classification"]=="authored" for r in rows)} '
              'currently authored caller instructions')


if __name__=='__main__':
    main()
