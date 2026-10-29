#!/usr/bin/env python3
"""F687: two entire native optimized COM owner dtors, 58/64 original bytes.

One small C++ translation unit is freshly compiled under pinned VC7.1
/O1. Independently compare full original 58/22 and 64/27 native x86,
true vtables, two real thiscall cleanup REL32 targets, imported free
DIR32 and the two indirect stdcall COM slots +8/+0xE0.
Original historical source owner UNKNOWN; no authored CODE credit.
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
OUT=ROOT/'.analysis/f687-native-com-owner-source'
SOURCE=ROOT/'probes/SDKNativeCOMOwnerDestructorsF687.cpp'
CASES={
    0x00608D8E:(58,22,'??1SDKResourceOwnerF687@@UAE@XZ',0x0065D348,
          {10:('DIR32','??_7SDKResourceOwnerF687@@6B@',0x0065D348),
           17:('REL32','?Reset@SDKResourceF687@@QAEXXZ',0x0061F42F),
           25:('REL32','?Destroy@SDKResourceF687@@QAEXXZ',0x0061F452),
           39:('DIR32','__imp__ImportedFree@4',0x0065704C)}),
    0x00608F96:(64,27,'??1SDKCOMOwnerF687@@UAE@XZ',0x0065D374,
          {10:('DIR32','??_7SDKCOMOwnerF687@@6B@',0x0065D374)}),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def reader_tool():
    sp=importlib.util.spec_from_file_location('f687_reader',ROOT/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'pinned original PE/COFF reader missing')
    m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m)
    return m


def build_one_source_object():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'original-two-optimized-COM-owners.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
           '/O1','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
           cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned VC7.1 real optimized SDK dtor source compile failed: '+cp.stderr[-500:])
    return obj


def verify_exact_native(reader,pe,dec,obj,addr,contract,functions,origins):
    size,count,sym,vtable,fields_by_offset=contract
    meta=functions.get(addr)
    need(meta is not None and int(meta['size'])==size,
         f'{addr:#x}: original PE entire registered native CODE function extent changed')
    original_origin=origins[f'0x{addr:08X}']
    need(original_origin['origin']=='unknown' and original_origin['disposition']=='review',
         f'{addr:#x}: original historical provenance no longer UNKNOWN')
    native=reader.pe_bytes_at(pe,addr,size)
    generated,refs=reader.object_function(obj,sym,expected_size=size)
    need(len(refs)==len(fields_by_offset)
         and {f['offset'] for f in refs}==set(fields_by_offset),
         f'{addr:#x}: all true original physical typed source COFF relocations required')
    linked=bytearray(generated)
    for f in refs:
        kind,symbol,target=fields_by_offset[f['offset']]
        need(f['type']==kind and f['symbol']==symbol
             and f['addend']==0 and f['local_symbol_offset'] is None,
             f'{addr:#x}: real PE/COFF physical vtable/cleanup/IAT symbol field at {f["offset"]} differs')
        expected=(target-(addr+f['offset']+4))&0xFFFFFFFF if kind=='REL32' else target
        need(generated[f['offset']:f['offset']+4]==bytes(4)
             and struct.unpack_from('<I',native,f['offset'])[0]==expected,
             f'{addr:#x}: original native physical field target not independently confirmed')
        struct.pack_into('<I',linked,f['offset'],expected)
    need(bytes(linked)==native,
         f'{addr:#x}: all {size} actual original PE machine CODE bytes NOT exact')
    orig=list(dec.disasm(native,addr))
    compiled=list(dec.disasm(bytes(linked),addr))
    need(len(orig)==len(compiled)==count
         and sum(x.size for x in orig)==sum(x.size for x in compiled)==size
         and all((x.mnemonic,x.op_str,x.size)==(y.mnemonic,y.op_str,y.size)
                 for x,y in zip(orig,compiled))
         and orig[0].mnemonic=='push' and orig[0].op_str=='esi'
         and orig[1].mnemonic=='mov' and orig[1].op_str=='esi, ecx'
         and orig[-2].mnemonic=='pop' and orig[-2].op_str=='esi'
         and orig[-1].mnemonic=='ret',
         f'{addr:#x}: original complete native 58/64-byte vtable/COM dtor x86 grammar changed')
    need(orig[4].mnemonic=='mov' and orig[4].op_str==f'dword ptr [esi], 0x{vtable:x}',
         f'{addr:#x}: original vtable assignment after native null-check changed')
    if addr==0x00608D8E:
        need(orig[2].op_str=='ecx, dword ptr [esi + 0x48]'
             and orig[6].op_str=='0x61f42f'
             and orig[8].op_str=='0x61f452'
             and orig[13].op_str=='dword ptr [0x65704c]'
             and orig[14].op_str=='esi, dword ptr [esi + 0x4c]'
             and orig[19].op_str=='dword ptr [eax + 8]',
             'true SDK native resource cleanup, import IAT or COM release slot incorrect')
    else:
        need(orig[2].op_str=='eax, dword ptr [esi + 8]'
             and orig[6].op_str=='ecx, dword ptr [esi + 0x14]'
             and orig[12].op_str=='dword ptr [edx + 0xe0]'
             and orig[13].op_str=='ecx, dword ptr [esi + 0x10]'
             and orig[20].op_str=='dword ptr [edx + 0xe0]'
             and orig[24].op_str=='dword ptr [eax + 8]'
             and orig[23].mnemonic=='push' and orig[23].op_str=='esi',
             'true original native two COM handle 0xE0 calls and stdcall release +8 changed')
    return {'actual_original_whole_native_function':f'0x{addr:08X}',
            'exact_complete_original_linked_CODE_bytes':size,
            'complete_original_x86_instructions':count,
            'true_original_typed_PE_COFF_fields':len(refs),
            'native_source_compiler_profile':'VC7.1 /O1 /Ob0 /Gy /GR- /GX- /GS /Zi',
            'actual_original_vftable_target':f'0x{vtable:08X}',
            'COM_virtual_stdcall_slots':[8] if addr==0x00608D8E else [0xE0,8],
            'historical_original_class_source_owner':'unknown',
            'new_accepted_whole_authored_CODE_bytes':0}


def actual_registered_callers(reader,pe,dec,functions):
    graph={addr:[] for addr in CASES}
    for start,meta in functions.items():
        for x in dec.disasm(reader.pe_bytes_at(pe,start,int(meta['size'])),start):
            if x.mnemonic=='call' and x.op_str.startswith('0x'):
                dest=int(x.op_str,16)
                if dest in graph:
                    graph[dest].append({'original_PE_direct_CALL':f'0x{x.address:08X}',
                                        'original_registered_caller':f'0x{start:08X}',
                                        'caller_current_origin':meta['owner']})
    return graph


def main():
    reader=reader_tool();pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions={int(row['address'],16):row for row in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={row['address']:row for row in csv.DictReader(stream)}
    need(len(functions)==len(origins)==4351,'original native registered candidate inventory changed')
    obj=build_one_source_object()
    proven=[verify_exact_native(reader,pe,dec,obj,addr,contract,functions,origins)
            for addr,contract in CASES.items()]
    need(len(proven)==2
         and sum(x['exact_complete_original_linked_CODE_bytes'] for x in proven)==122
         and sum(x['complete_original_x86_instructions'] for x in proven)==49
         and sum(x['true_original_typed_PE_COFF_fields'] for x in proven)==5,
         'actual two original optimized COM destructor whole-function totals changed')
    callers=actual_registered_callers(reader,pe,dec,functions)
    need(all(len(v)==1 and v[0]['caller_current_origin']=='compiler'
                 for v in callers.values()),
         'original native COM owner caller provenance/direct CALL evidence changed')
    receipt={'pinned_user_original_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'natural_ordinary_cpp_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'genuine_two_entire_original_byte_exact_COM_owner_destructors':proven,
             'native_original_registered_direct_callers':{f'0x{addr:08X}':x for addr,x in callers.items()},
             'new_origin_unknown_source_backed_whole_original_count':2,
             'new_true_original_complete_CODE_bytes':122,
             'new_accepted_entire_authored_game_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F687: two genuine complete optimized virtual COM/resource owner '
          'destructors 00608D8E/00608F96 exactly 58+64 = 122/122 original '
          'linked CODE bytes, 22+27 = 49 native x86, 4+1 = five true '
          'physical typed PE/COFF fields; original native virtual stdcall '
          'slot +8 and dual +0xE0 calls. One small pinned VC7.1 /O1 '
          'C++ cold build; original source owners still UNKNOWN, zero '
          'new authored CODE credit, no mass cold replay.')


if __name__=='__main__':
    main()
