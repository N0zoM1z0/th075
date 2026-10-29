#!/usr/bin/env python3
"""F665: four NEW original complete origin-UNKNOWN 19-byte thiscall forwards.

Rebuild only ONE tiny VC7.1 C++ TU, verify four distinct registered
original PE whole CODE extents byte-for-byte with their real REL32
COFF field targets and independent direct native CALL graph. A byte
match never proves original game authorship or historical class layout.
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
SOURCE=ROOT/'probes/GameNativeForwarderLeavesF665.cpp'
OUT=ROOT/'.analysis/f665-native-forwarder-leaves'
CASES={
    0x00458A80:('ForwarderOwnerA_F665',0x00458DA0),
    0x00458B50:('ForwarderOwnerB_F665',0x00458FC0),
    0x00458C20:('ForwarderOwnerC_F665',0x00459140),
    0x005F8020:('ForwarderOwnerD_F665',0x005F85E0),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def canonical_reader():
    spec=importlib.util.spec_from_file_location('f665_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'missing verified native PE/COFF original reader')
    m=importlib.util.module_from_spec(spec);sys.modules[spec.name]=m;spec.loader.exec_module(m)
    return m


def compile_entire_leaf_source():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'four-original-entire-native-member-forwarders.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    process=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(process.stdout+process.stderr)
    need(process.returncode==0,'pinned VC7.1 small original source compile failed: '+process.stderr[-500:])
    return obj


def true_complete_original(reader,pe,decoder,obj,addr,owner,target,functions,origins):
    originalinfo=functions.get(addr)
    need(originalinfo is not None and int(originalinfo['size'])==19,
         f'{addr:#x}: actual registered original full native CODE boundaries changed')
    info=origins[f'0x{addr:08X}']
    need(info['origin']=='unknown' and info['disposition']=='review',
         f'{addr:#x}: original function source origin not historically unknown')
    symbol=f'?Forward@{owner}@@QAEXXZ'
    native=reader.pe_bytes_at(pe,addr,19)
    generated,fields=reader.object_function(obj,symbol,expected_size=19)
    n=list(decoder.disasm(native,addr));g=list(decoder.disasm(generated,addr))
    need(len(n)==len(g)==9 and sum(x.size for x in n)==19
         and sum(x.size for x in g)==19 and n[-1].mnemonic==g[-1].mnemonic=='ret',
         f'{addr:#x}: genuine native full source x86 extent/epilogue changed')
    need(len(fields)==1 and fields[0]['offset']==11
         and fields[0]['type']=='REL32'
         and fields[0]['symbol']==f'?Inner@{owner}@@QAEXXZ'
         and fields[0]['addend']==0 and fields[0]['local_symbol_offset'] is None,
         f'{addr:#x}: not a real exact original native zero-addend REL32 target field')
    need(n[5].mnemonic==g[5].mnemonic=='call'
         and n[5].address==addr+10
         and n[5].op_str==f'0x{target:x}'
         and generated[11:15]==b'\0'*4
         and all((a.size,a.mnemonic)==(b.size,b.mnemonic) for a,b in zip(n,g))
         and all(a.op_str==b.op_str for i,(a,b) in enumerate(zip(n,g)) if i!=5),
         f'{addr:#x}: genuine original physical original CALL or other machine roles differ')
    value=(target-(addr+15))&0xFFFFFFFF
    need(struct.unpack_from('<I',native,11)[0]==value,
         f'{addr:#x}: actual original PE call displacement differs')
    linked=bytearray(generated);struct.pack_into('<I',linked,11,value)
    need(bytes(linked)==native,
         f'{addr:#x}: original entire linked native 19 CODE bytes not exact')
    return {'original_registered_native_function':f'0x{addr:08X}',
            'original_whole_NATIVE_CODE_bytes_identical':19,
            'actual_original_native_complete_x86_instructions':9,
            'physically_typed_original_PE_COFF_REL32_fields':1,
            'original_native_genuine_CALL_target':f'0x{target:08X}',
            'original_provenance':'unknown',
            'new_accepted_authored_whole_FUNCTION_CODE_bytes':0}


def native_callers(reader,pe,decoder,functions):
    links={addr:[] for addr in CASES}
    for caller,metadata in functions.items():
        for n in decoder.disasm(reader.pe_bytes_at(pe,caller,int(metadata['size'])),caller):
            if n.mnemonic=='call' and n.op_str.startswith('0x'):
                callee=int(n.op_str,16)
                if callee in links:
                    links[callee].append({'actual_original_native_PE_CALL':f'0x{n.address:08X}',
                                          'original_registered_caller':f'0x{caller:08X}',
                                          'current_caller_origin':metadata['owner']})
    return links


def main():
    reader=canonical_reader();pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions={int(row['address'],16):row for row in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={row['address']:row for row in csv.DictReader(stream)}
    need(len(functions)==len(origins)==4351,'original registered function inventory changed')
    obj=compile_entire_leaf_source()
    results=[true_complete_original(reader,pe,decoder,obj,addr,owner,target,functions,origins)
             for addr,(owner,target) in CASES.items()]
    need(len(results)==4 and sum(r['original_whole_NATIVE_CODE_bytes_identical'] for r in results)==76
         and sum(r['actual_original_native_complete_x86_instructions'] for r in results)==36,
         'four independently original native 19-byte member-forwarder totals changed')
    graph=native_callers(reader,pe,decoder,functions)
    receipt={'genuine_pinned_original_native_PE_sha256':hashlib.sha256(pe).hexdigest(),
             'normal_ordinary_CPP_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'four_distinct_original_complete_native_source_backed_functions':results,
             'original_PE_direct_CALL_graph':{f'0x{addr:08X}':rows for addr,rows in graph.items()},
             'count_new_original_full_source_backed_unknown_functions':4,
             'new_original_source_backed_whole_native_CODE_bytes':76,
             'new_accepted_authored_whole_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F665 four NEW complete original PE origin-UNKNOWN native member '
          'forwarders: 4/4 linked whole CODE exact, 76 original native CODE B, '
          '36 full native x86 and 4 genuine physically linked typed REL32 '
          'COFF fields; zero authored CODE accepted; only one small VC7.1 TU, '
          'no 943-unit cold replay.')
    for addr,rows in graph.items():
        authored=sum(r['current_caller_origin']=='authored' for r in rows)
        print(f'  native {addr:#010x}: {len(rows)} original direct CALLs, '
              f'{authored} currently authored caller instructions')


if __name__=='__main__':
    main()
