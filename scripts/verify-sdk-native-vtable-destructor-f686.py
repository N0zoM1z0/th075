#!/usr/bin/env python3
"""F686: full 19-B, 5-x86 original SDK-style virtual destructor exact source.

Only one tiny normal VC7.1 /O1 C++ translation unit is cold-compiled.
Check authentic original 0061535A whole PE function extent, true
virtual-vtable DIR32, CDECL free REL32, raw +0x104C resource member,
and all 19 linked native machine bytes. Source author stays UNKNOWN.
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
OUT=ROOT/'.analysis/f686-sdk-native-vtable-destructor'
SOURCE=ROOT/'probes/SDKNativeVtableDestructorF686.cpp'
ADDR=0x0061535A
SIZE=19
X86=5
VTABLE=0x0065DA54
FREE_TARGET=0x00640F15
SYMBOL='??1SDKNativeVtableDestructorF686@@UAE@XZ'
VTABLE_SYMBOL='??_7SDKNativeVtableDestructorF686@@6B@'


def need(ok,msg):
    if not ok:raise ValueError(msg)


def reader_tool():
    s=importlib.util.spec_from_file_location('f686_reader',ROOT/'scripts/compare-coff-function.py')
    need(s is not None and s.loader is not None,'original pinned PE/COFF reader missing')
    mod=importlib.util.module_from_spec(s);sys.modules[s.name]=mod;s.loader.exec_module(mod)
    return mod


def fresh_source():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'original-19byte-virtual-dtor.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
            '/O1','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'pinned VC7.1 real native virtual destructor failed: '+proc.stderr[-500:])
    return obj


def verify_native(reader,pe,decoder,obj,functions,origins):
    info=functions.get(ADDR)
    need(info is not None and int(info['size'])==SIZE,
         'original full SDK virtual destructor registered PE extent changed')
    origin=origins[f'0x{ADDR:08X}']
    need(origin['origin']=='unknown' and origin['disposition']=='review',
         'historical original virtual destructor owner is no longer UNKNOWN')
    original=reader.pe_bytes_at(pe,ADDR,SIZE)
    code,refs=reader.object_function(obj,SYMBOL,expected_size=SIZE)
    need(len(refs)==2,'real original virtual dtor must own two actual typed physical source references')
    field_by_offset={f['offset']:f for f in refs}
    need(set(field_by_offset)=={8,13},
         'actual original vtable/source native CALL physical field offsets changed')
    v=field_by_offset[8];free=field_by_offset[13]
    need(v['type']=='DIR32' and v['symbol']==VTABLE_SYMBOL
         and v['addend']==0 and v['local_symbol_offset'] is None
         and free['type']=='REL32' and free['symbol']=='_free'
         and free['addend']==0 and free['local_symbol_offset'] is None,
         'original two genuine native source PE/COFF types, zero addends or names changed')
    need(code[8:12]==bytes(4) and code[13:17]==bytes(4)
         and struct.unpack_from('<I',original,8)[0]==VTABLE
         and struct.unpack_from('<I',original,13)[0]==(FREE_TARGET-(ADDR+17))&0xFFFFFFFF,
         'real original native PE vtable/free target or unlinked source field changed')
    linked=bytearray(code)
    struct.pack_into('<I',linked,8,VTABLE)
    struct.pack_into('<I',linked,13,(FREE_TARGET-(ADDR+17))&0xFFFFFFFF)
    need(bytes(linked)==original,
         'all 19 original linked virtual destructor native machine bytes differ')
    raw=list(decoder.disasm(original,ADDR))
    gen=list(decoder.disasm(bytes(linked),ADDR))
    need(len(raw)==len(gen)==X86
         and sum(x.size for x in raw)==sum(x.size for x in gen)==SIZE
         and all((a.mnemonic,a.size,a.op_str)==(b.mnemonic,b.size,b.op_str)
                 for a,b in zip(raw,gen))
         and raw[0].mnemonic=='push'
         and raw[0].op_str=='dword ptr [ecx + 0x104c]'
         and raw[1].op_str=='dword ptr [ecx], 0x65da54'
         and raw[2].mnemonic=='call' and raw[2].op_str=='0x640f15'
         and raw[3].mnemonic=='pop' and raw[3].op_str=='ecx'
         and raw[4].mnemonic=='ret',
         'genuine original full native virtual vtable/load/free/CDECL return ABI differs')
    return {'original_registered_native_whole_function':f'0x{ADDR:08X}',
            'entire_original_linked_CODE_bytes_exact':SIZE,
            'original_full_x86_instructions_exact':X86,
            'genuine_original_typed_PE_COFF_fields':2,
            'original_vtable_PE_target':f'0x{VTABLE:08X}',
            'original_direct_CRT_free_PE_target':f'0x{FREE_TARGET:08X}',
            'true_resource_pointer_offset':'0x104C',
            'original_source_provenance':'unknown',
            'new_game_authored_whole_FUNCTION_CODE_credit':0}


def callers_graph(reader,pe,decoder,functions):
    found=[]
    for addr,meta in functions.items():
        for x in decoder.disasm(reader.pe_bytes_at(pe,addr,int(meta['size'])),addr):
            if x.mnemonic=='call' and x.op_str==f'0x{ADDR:x}':
                found.append({'real_original_CALL':f'0x{x.address:08X}',
                              'original_registered_caller':f'0x{addr:08X}',
                              'current_caller_origin':meta['owner']})
    return found


def main():
    reader=reader_tool();pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions={int(row['address'],16):row for row in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={row['address']:row for row in csv.DictReader(stream)}
    need(len(functions)==len(origins)==4351,'registered native original inventory differs')
    obj=fresh_source();proof=verify_native(reader,pe,dec,obj,functions,origins)
    callers=callers_graph(reader,pe,dec,functions)
    receipt={'pinned_original_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'ordinary_C++_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'original_complete_native_byte_exact_virtual_destructor':proof,
             'actual_original_registered_direct_CALLers':callers,
             'new_origin_UNKNOWN_complete_original_source_backed_functions':1,
             'new_unknown_complete_original_CODE_bytes':SIZE,
             'accepted_new_whole_authored_game_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F686: entire source-unknown original native 0061535A virtual destructor '
          '19/19 linked CODE bytes, 5 complete original x86, two genuine '
          'zero-addend PE/COFF fields (vtable DIR32 and CRT CDECL free REL32). '
          f'Original registered direct CALLers {len(callers)}. VC7.1 /O1 only '
          'one small TU cold compiled, historical source owner UNKNOWN; '
          'zero authored CODE credit, no 943-unit replay.')


if __name__=='__main__':
    main()
