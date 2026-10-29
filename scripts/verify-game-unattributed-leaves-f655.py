#!/usr/bin/env python3
"""F655: seven original complete origin-UNKNOWN leaf CODE functions.

Cold-build only one original-sized C++ source TU under pinned VC7.1.
Require full byte identity after real typed COFF REL32 link, native
extent/x86/ABI, real PE target and a decoded native direct-call graph.
None is credited as authored CODE without separate ownership evidence.
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
SOURCE=ROOT/'probes/GameUnattributedLeavesF655.cpp'
OUT=ROOT/'.analysis/f655-unattributed-leaf-source'
# Cases are seven different original registered PE extents, not just
# seven names for the same compiled function body.
CASES={
    0x004138D0:(11,7,'?NoOp@EmptyReceiverA_F655@@QAEXXZ',{}),
    0x004169D0:(11,7,'?NoOp@EmptyReceiverB_F655@@QAEXXZ',{}),
    0x0041F7F0:(11,6,'_AfterHeaderA_F655',{}),
    0x00540280:(11,6,'_AfterHeaderB_F655',{}),
    0x00441FD0:(5,4,'_EmptyFreeA_F655',{}),
    0x0045B630:(5,4,'_EmptyFreeB_F655',{}),
    0x00409490:(19,9,'?Forward@DelegateMember_F655@@QAEXXZ',
                {11:('REL32',0x00409860,'?Finish@DelegateMember_F655@@QAEXXZ')}),
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load_reader():
    spec=importlib.util.spec_from_file_location('f655_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'missing canonical COFF reader')
    m=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=m
    spec.loader.exec_module(m)
    return m


def compile_source():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'seven-complete-original-native-leaves.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=ROOT,
             env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'native pinned compiler failed: '+proc.stderr[-500:])
    return obj


def verify_whole(reader,pe,decoder,obj,addr,control,origins,functions):
    size,num,symbol,fields_expected=control
    need(addr in functions and functions[addr]['size']==str(size),
         f'original registered function boundary/size changed {addr:#x}')
    origin=origins[f'0x{addr:08X}']
    need(origin['origin']=='unknown' and origin['disposition']=='review',
         f'{addr:#x} native provenance changed: must not silently accept authored CODE')
    original=reader.pe_bytes_at(pe,addr,size)
    gen,fields=reader.object_function(obj,symbol,expected_size=size)
    o=list(decoder.disasm(original,addr));g=list(decoder.disasm(gen,addr))
    need(len(o)==len(g)==num and sum(x.size for x in o)==sum(x.size for x in g)==size
         and o[-1].mnemonic==g[-1].mnemonic=='ret'
         and all(a.size==b.size and a.mnemonic==b.mnemonic
                 and (a.op_str==b.op_str or a.mnemonic=='call')
                 for a,b in zip(o,g)),
         f'{addr:#x}: full original exact x86 geometry/noncall roles changed')
    need(len(fields)==len(fields_expected),
         f'{addr:#x}: physical original PE/COFF field count not complete')
    linked=bytearray(gen)
    for offset,(kind,target,sym) in fields_expected.items():
        f=[r for r in fields if r['offset']==offset]
        need(len(f)==1 and f[0]['type']==kind
             and f[0]['addend']==0 and f[0]['symbol']==sym
             and f[0]['local_symbol_offset'] is None,
             f'{addr:#x}: native physical PE/COFF original callee symbol/field differs')
        native=next((x for x in o if x.address<=addr+offset<x.address+x.size),None)
        need(native is not None and native.mnemonic=='call'
             and native.op_str==f'0x{target:x}'
             and gen[offset:offset+4]==b'\x00'*4,
             f'{addr:#x}: original native real original REL32 call target/field changed')
        displacement=(target-(addr+offset+4))&0xFFFFFFFF
        need(struct.unpack_from('<I',original,offset)[0]==displacement,
             f'{addr:#x}: original physically linked PE relocation displacement changed')
        struct.pack_into('<I',linked,offset,displacement)
    need(bytes(linked)==original,
         f'{addr:#x}: entire original native CODE bytes are not identical after true relocation')
    return {'original_full_registered_address':f'0x{addr:08X}',
            'entire_original_NATIVE_CODE_bytes_exact':size,
            'entire_original_native_x86_instructions':num,
            'physical_original_typed_PE_COFF_fields':len(fields),
            'complete_original_native_CODE_identical':True,
            'historical_source_origin':'unknown',
            'new_accepted_authored_exact_whole_bytes':0}


def native_call_graph(reader,pe,decoder,functions):
    links={addr:[] for addr in CASES}
    for address,record in functions.items():
        for n in decoder.disasm(reader.pe_bytes_at(pe,address,int(record['size'])),address):
            if n.mnemonic=='call' and n.op_str.startswith('0x'):
                callee=int(n.op_str,16)
                if callee in links:
                    links[callee].append({'original_direct_native_CALL':f'0x{n.address:08X}',
                                          'original_registered_caller':f'0x{address:08X}',
                                          'current_caller_classification':record['owner'],
                                          'caller_name_is_provisional':record['proposed_name']})
    return links


def main():
    reader=load_reader();pe=reader.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as f:
        functions={int(r['address'],16):r for r in csv.DictReader(f)}
    with (ROOT/'config/function-origins.csv').open(newline='') as f:
        origins={r['address']:r for r in csv.DictReader(f)}
    need(len(functions)==4351 and len(origins)==4351,
         'registered original native function candidates changed')
    obj=compile_source()
    result=[verify_whole(reader,pe,dec,obj,a,control,origins,functions)
            for a,control in CASES.items()]
    total=(len(result),sum(q['entire_original_NATIVE_CODE_bytes_exact'] for q in result),
           sum(q['entire_original_native_x86_instructions'] for q in result),
           sum(q['physical_original_typed_PE_COFF_fields'] for q in result))
    need(total==(7,73,43,1),f'entire original native leaf accounting changed: {total}')
    graph=native_call_graph(reader,pe,dec,functions)
    payload={'pinned_original_native_PE_sha256':hashlib.sha256(pe).hexdigest(),
             'normal_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'genuine_native_original_complete_leaves':result,
             'actual_original_PE_direct_CALL_graph':{f'0x{addr:08X}':v for addr,v in graph.items()},
             'new_source_backed_whole_unknown_functions':7,
             'original_complete_unknown_native_CODE_bytes':73,
             'original_complete_x86_roles':43,
             'genuine_original_PE_COFF_fields':1,
             'new_accepted_game_authored_exact_whole_functions':0}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(payload,indent=2)+'\n')
    print('F655: seven distinct complete original PE native origin-UNKNOWN '
          'functions; 73/73 linked native CODE bytes, 43 whole x86 instructions '
          'and one genuine REL32 source-to-original native callee field all match. '
          'Real original caller graph recorded; zero authored-function credit; '
          'only one small TU compiled, no full replay.')
    for addr,matches in graph.items():
        count=sum(c['current_caller_classification']=='authored' for c in matches)
        print(f'  native {addr:#010x}: original registered direct calls {len(matches)}, '
              f'currently authored caller occurrences {count}')


if __name__=='__main__':
    main()
