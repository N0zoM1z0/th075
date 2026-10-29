#!/usr/bin/env python3
"""F675: four original full SDK state constructors, unknown source owner.

One tiny ordinary C++ TU cold-built under genuine pinned VC7.1 /O1.
Validate four *entire* registered original optimized native CODE
functions, all x86/ABI, one true DIR32 vftable symbol/address per
function and every linked original machine byte. Original provenance
stays UNKNOWN; zero whole game-authored CODE credit or mass replay.
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
SOURCE=ROOT/'probes/SDKNativeStateConstructorsF675.cpp'
OUT=ROOT/'.analysis/f675-sdk-native-state-source'
# All four native complete original function bounds, not just prefixes.
# Names and inferred virtual method are ONLY compiler-grammar proxies;
# original SDK object types/authorship remain unknown.
CASES={
  0x00608F7B:(27,8,'SDKProbeA',0x0065D348,6),
  0x00609AA4:(30,9,'SDKProbeB',0x0065D374,6),
  0x00609F58:(39,12,'SDKProbeC',0x0065D39C,6),
  0x006200DA:(24,6,'SDKProbeD',0x0065DE1C,12),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def reader_tool():
    spec=importlib.util.spec_from_file_location('f675_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'missing canonical original PE/COFF reader')
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module;spec.loader.exec_module(module)
    return module


def fresh_native_cpp():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'four-optimized-original-SDK-native-constructors.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
             '/O1','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,'genuine VC7.1 /O1 native constructor source compilation failed: '+result.stderr[-500:])
    return obj


def verify_original(reader,pe,decoder,obj,addr,control,functions,origins):
    size,count,cls,vtable,offset=control
    record=functions.get(addr)
    need(record is not None and int(record['size'])==size,
         f'original {addr:#x} complete function boundary/size changed')
    info=origins[f'0x{addr:08X}']
    need(info['origin']=='unknown' and info['disposition']=='review',
         f'original SDK constructor {addr:#x} provenance is not UNKNOWN')
    native=reader.pe_bytes_at(pe,addr,size)
    mangled=f'??0{cls}@@QAE@XZ'
    generated,fields=reader.object_function(obj,mangled,expected_size=size)
    need(len(fields)==1 and fields[0]['offset']==offset
         and fields[0]['type']=='DIR32'
         and fields[0]['symbol']==f'??_7{cls}@@6B@'
         and fields[0]['addend']==0
         and fields[0]['local_symbol_offset'] is None,
         f'{addr:#x}: original optimized native vtable field is not a true zero-addend DIR32')
    need(generated[offset:offset+4]==b'\x00'*4
         and struct.unpack_from('<I',native,offset)[0]==vtable,
         f'{addr:#x}: actual original native vtable PE address/field differs')
    patched=bytearray(generated)
    struct.pack_into('<I',patched,offset,vtable)
    need(bytes(patched)==native,
         f'{addr:#x}: entire original linked SDK native CODE bytes differ')
    a=list(decoder.disasm(native,addr))
    b=list(decoder.disasm(bytes(patched),addr))
    need(len(a)==len(b)==count
         and sum(x.size for x in a)==sum(x.size for x in b)==size
         and a[-1].mnemonic==b[-1].mnemonic=='ret'
         and all((x.size,x.mnemonic,x.op_str)==(y.size,y.mnemonic,y.op_str)
                 for x,y in zip(a,b))
         and a[0].op_str=='eax, ecx',
         f'{addr:#x}: full original optimized x86 mnemonic/operand roles changed')
    if addr==0x006200DA:
        need(a[1].mnemonic==a[2].mnemonic=='and'
             and a[1].op_str=='dword ptr [eax + 0xc], 0'
             and a[2].op_str=='dword ptr [eax + 8], 0',
             'actual SDK native 6200DA O1 field-masking source semantics changed')
    else:
        need(a[1].mnemonic=='xor' and a[1].op_str=='ecx, ecx'
             and a[2].mnemonic=='mov' and a[2].op_str==f'dword ptr [eax], 0x{vtable:x}'
             and a[3].op_str=='dword ptr [eax + 4], 1',
             f'{addr:#x}: optimized SDK native reference/virtual table initialization changed')
    return {'actual_original_complete_function_start':f'0x{addr:08X}',
            'original_linked_entire_CODE_bytes_exact':size,
            'original_whole_native_x86_instructions':count,
            'genuine_typed_PE_COFF_DIR32_fields':1,
            'original_native_vftable_target':f'0x{vtable:08X}',
            'genuine_native_profile':'VC7.1 /O1 /Ob0 /Gy /GR- /GX- /GS /Zi',
            'original_source_owner':'unknown',
            'new_accepted_whole_authored_CODE_bytes':0}


def registered_direct_callers(reader,pe,dec,functions):
    links={addr:[] for addr in CASES}
    for src,metadata in functions.items():
        for x in dec.disasm(reader.pe_bytes_at(pe,src,int(metadata['size'])),src):
            if x.mnemonic=='call' and x.op_str.startswith('0x'):
                callee=int(x.op_str,16)
                if callee in links:
                    links[callee].append({'original_PE_CALL':f'0x{x.address:08X}',
                                          'original_registered_caller':f'0x{src:08X}',
                                          'current_caller_origin':metadata['owner']})
    return links


def main():
    reader=reader_tool();pe=reader.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions={int(r['address'],16):r for r in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={r['address']:r for r in csv.DictReader(stream)}
    need(len(functions)==len(origins)==4351,'registered original native PE candidate inventory changed')
    obj=fresh_native_cpp()
    verified=[verify_original(reader,pe,dec,obj,addr,control,functions,origins)
              for addr,control in CASES.items()]
    need(len(verified)==4 and sum(x['original_linked_entire_CODE_bytes_exact'] for x in verified)==120
         and sum(x['original_whole_native_x86_instructions'] for x in verified)==35,
         'original full-native optimized SDK constructor count/bytes changed')
    graph=registered_direct_callers(reader,pe,dec,functions)
    receipt={'pinned_user_original_NATIVE_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'ordinary_Cplusplus_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'four_genuine_entire_original_native_functions':verified,
             'registered_original_direct_PE_CALL_graph':{f'0x{addr:08X}':v for addr,v in graph.items()},
             'new_original_source_backed_unknown_complete_function_count':4,
             'original_complete_source_backed_native_CODE_bytes':120,
             'accepted_game_authored_entire_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F675: four new original complete optimized SDK virtual-state native '
          'constructors, all 120/120 original linked CODE B, 35 native x86, '
          'four genuine PE-targeted typed DIR32 vtable source fields. '
          'All original historical source owners UNKNOWN, zero authored '
          'CODE credit. One small pinned VC7.1 /O1 cold TU; no mass replay.')
    for addr,rows in graph.items():
        authored=sum(r['current_caller_origin']=='authored' for r in rows)
        print(f'  original native {addr:#010x}: {len(rows)} direct registered CALLs, '
              f'{authored} currently authored caller instructions')


if __name__=='__main__':
    main()
