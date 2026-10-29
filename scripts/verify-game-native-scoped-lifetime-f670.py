#!/usr/bin/env python3
"""F670: whole original 00423B20 one-byte stack-scoped RAII grammar.

Cold-build only one small pinned VC7.1 C++ TU; require 26/26 entire
native original PE machine bytes after authentic two zero-addend REL32
COFF field destinations and separately observe actual registered
native direct callers. This remains origin UNKNOWN, no authored credit.
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
SOURCE=ROOT/'probes/GameNativeScopedLifetimeF670.cpp'
OUT=ROOT/'.analysis/f670-native-scoped-lifetime'
ADDR=0x00423B20
SIZE=26
TARGETS={10:(0x004239F0,'??0SmallScopedLifetimeF670@@QAE@H@Z'),
         18:(0x00423A90,'??1SmallScopedLifetimeF670@@QAE@XZ')}
SYMBOL='_NativeLocalScopeF670'


def need(ok,msg):
    if not ok:raise ValueError(msg)


def reader_tool():
    spec=importlib.util.spec_from_file_location('f670_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'original pinned native PE reader absent')
    m=importlib.util.module_from_spec(spec);sys.modules[spec.name]=m;spec.loader.exec_module(m)
    return m


def new_source_object():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'scoped-byte-lifetime-native.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned original VC7.1 scoped-local source compile failed: '+cp.stderr[-500:])
    return obj


def main():
    r=reader_tool();pe=r.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        registered={int(row['address'],16):row for row in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={row['address']:row for row in csv.DictReader(stream)}
    need(len(registered)==len(origins)==4351 and ADDR in registered
         and int(registered[ADDR]['size'])==SIZE,
         'original registered complete native function boundary/inventory changed')
    origin=origins[f'0x{ADDR:08X}']
    need(origin['origin']=='unknown' and origin['disposition']=='review',
         'actual original historical native source origin is no longer unknown')
    obj=new_source_object()
    native=r.pe_bytes_at(pe,ADDR,SIZE)
    code,fields=r.object_function(obj,SYMBOL,expected_size=SIZE)
    actual=list(dec.disasm(native,ADDR))
    compiled=list(dec.disasm(code,ADDR))
    need(len(actual)==len(compiled)==11
         and sum(x.size for x in actual)==sum(x.size for x in compiled)==SIZE
         and compiled[-1].mnemonic==actual[-1].mnemonic=='ret'
         and all(a.size==b.size and a.mnemonic==b.mnemonic
                 for a,b in zip(actual,compiled)),
         'original entire 26-byte function x86 ABI, prologue or epilogue differs')
    need(actual[4].mnemonic==actual[6].mnemonic=='lea'
         and actual[4].op_str==actual[6].op_str=='ecx, [ebp - 1]'
         and compiled[4].op_str==compiled[6].op_str=='ecx, [ebp - 1]'
         and actual[3].mnemonic==compiled[3].mnemonic=='push'
         and actual[3].op_str==compiled[3].op_str=='0x10',
         'actual original one-byte stack scoped value or ctor argument changed')
    need(len(fields)==len(TARGETS)==2,
         'actual original complete native 2 PE/COFF field ownership changed')
    linked=bytearray(code)
    for offset,(target,sym) in TARGETS.items():
        reloc=[f for f in fields if f['offset']==offset]
        need(len(reloc)==1 and reloc[0]['type']=='REL32'
             and reloc[0]['symbol']==sym and reloc[0]['addend']==0
             and reloc[0]['local_symbol_offset'] is None,
             f'original true ctor/dtor COFF physical REL32 target at +{offset} differs')
        source_call=next((ins for ins in actual
                          if ins.mnemonic=='call' and ins.address==ADDR+offset-1),None)
        need(source_call is not None and source_call.op_str==f'0x{target:x}'
             and code[offset:offset+4]==b'\x00'*4,
             f'actual real native PE CALL target at {ADDR+offset-1:#x} differs')
        displacement=(target-(ADDR+offset+4))&0xFFFFFFFF
        need(struct.unpack_from('<I',native,offset)[0]==displacement,
             f'actual original PE physical linked displacement at +{offset} differs')
        struct.pack_into('<I',linked,offset,displacement)
    need(bytes(linked)==native,
         'complete original 26 native bytes still differ after only true PE-linked fields')
    actual_callers=[]
    for addr,info in registered.items():
        for ins in dec.disasm(r.pe_bytes_at(pe,addr,int(info['size'])),addr):
            if ins.mnemonic=='call' and ins.op_str==f'0x{ADDR:x}':
                actual_callers.append({'original_native_CALL_address':f'0x{ins.address:08X}',
                                       'original_registered_caller':f'0x{addr:08X}',
                                       'current_caller_origin':info['owner']})
    report={'original_pinned_PE_SHA256':hashlib.sha256(pe).hexdigest(),
            'ordinary_normal_cpp_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            'original_whole_function_start':f'0x{ADDR:08X}',
            'original_whole_native_CODE_bytes_exact':SIZE,
            'entire_original_x86_instructions_exact':len(actual),
            'original_true_typed_REL32_PE_COFF_fields':len(fields),
            'original_linked_native_MACHINE_CODE_identical':True,
            'one_byte_addressable_original_scoped_local_EBP':'-1',
            'genuine_original_ctor_destination':'0x004239F0',
            'genuine_original_dtor_destination':'0x00423A90',
            'original_PE_direct_registered_CALLers':actual_callers,
            'historical_original_source_origin':'unknown',
            'new_authored_exact_whole_function_CODE_credit':0}
    (OUT/'summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F670: original entire native 00423B20 scoped lifetime source: '
          '26/26 complete PE-linked CODE B, 11 x86, two genuine zero-addend '
          'REL32 fields to original constructor/destructor. Original native '
          f'registered direct callers {len(actual_callers)}. Origin UNKNOWN; '
          'zero authored whole-function credit, one small cold build, '
          'no all-unit replay.')


if __name__=='__main__':
    main()
