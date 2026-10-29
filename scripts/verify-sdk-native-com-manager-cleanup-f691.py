#!/usr/bin/env python3
"""F691: native 0061F125 entire 249-byte COM manager release/unlink exact.

Cold-build exactly ONE pinned VC7.1 /O1 normal C++ TU, verify all
104 original PE instruction widths/operands and all five true
zero-addend DIR32 original import/global fields. Require linked bytes
249/249 and original native COM slot +E0/+8, eight-element twin
release loop, actual import calls and head-pointer unlink semantics.
Historical source origin is UNKNOWN; no authored exact CODE credit.
Never cold-replay all 943 units.
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
SOURCE=ROOT/'probes/SDKNativeCOMManagerCleanupF691.cpp'
OUT=ROOT/'.analysis/f691-native-com-manager-cleanup'
ADDR=0x0061F125
SIZE=249
X86=104
SYMBOL='?Clear@SDKCOMManagerF691@@QAEXXZ'
COFF={
 129:('DIR32','__imp__ImportedReleasePair@8',0x00657048),
 185:('DIR32','__imp__ImportedFree@4',0x0065704C),
 199:('DIR32','__imp__ImportedDispose@4',0x0065702C),
 205:('DIR32','?g_SDKCOMManagerHeadF691@@3PAVSDKCOMManagerF691@@A',0x0068E264),
 210:('DIR32','?g_SDKCOMManagerHeadF691@@3PAVSDKCOMManagerF691@@A',0x0068E264),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def reader_tool():
    sp=importlib.util.spec_from_file_location('f691_reader',ROOT/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'canonical native original PE reader missing')
    m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m)
    return m


def fresh_source():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'original-249byte-COM-release-manager.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
          '/O1','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=ROOT,env=env,
          capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'pinned original VC7.1 /O1 complete manager compile failed: '+p.stderr[-450:])
    return obj


def verify_native(reader,pe,decoder,obj,functions,origins):
    info=functions.get(ADDR)
    need(info is not None and int(info['size'])==SIZE,
         'genuine original 0061F125 249-byte registered whole extent changed')
    origin=origins[f'0x{ADDR:08X}']
    need(origin['origin']=='unknown' and origin['disposition']=='review',
         'original COM manager historical source provenance no longer UNKNOWN')
    native=reader.pe_bytes_at(pe,ADDR,SIZE)
    cpp,fields=reader.object_function(obj,SYMBOL,expected_size=SIZE)
    need(len(fields)==len(COFF)==5 and {f['offset'] for f in fields}==set(COFF),
         'all five native physical source PE/COFF fields must agree')
    linked=bytearray(cpp)
    for f in fields:
        kind,symbol,target=COFF[f['offset']]
        need(kind==f['type']=='DIR32'
             and f['symbol']==symbol and f['addend']==0
             and f['local_symbol_offset'] is None
             and cpp[f['offset']:f['offset']+4]==bytes(4)
             and struct.unpack_from('<I',native,f['offset'])[0]==target,
             f'original true import/global DIR32 at +{f["offset"]} differs')
        struct.pack_into('<I',linked,f['offset'],target)
    need(bytes(linked)==native,
         'entire original 249 linked machine CODE bytes not bit identical')
    actual=list(decoder.disasm(native,ADDR))
    source=list(decoder.disasm(bytes(linked),ADDR))
    need(len(actual)==len(source)==X86
         and sum(x.size for x in actual)==sum(x.size for x in source)==SIZE
         and all((a.size,a.mnemonic,a.op_str)==(b.size,b.mnemonic,b.op_str)
                 for a,b in zip(actual,source))
         and actual[0].mnemonic=='push' and actual[0].op_str=='ebp'
         and actual[-1].mnemonic=='ret',
         'original entire 249-byte x86 function width/mnemonics/operand order/return differs')
    need(actual[11].mnemonic==actual[19].mnemonic=='call'
         and actual[11].op_str==actual[19].op_str=='dword ptr [edx + 0xe0]'
         and actual[20].mnemonic=='push' and actual[20].op_str=='ebx'
         and actual[21].mnemonic=='push' and actual[21].op_str=='edi'
         and actual[22].op_str=='8'
         and actual[23].op_str=='edi, [esi + 0x10]'
         and all(actual[i].mnemonic=='call' and actual[i].op_str=='dword ptr [ecx + 8]'
                 for i in (30,37,47,54))
         and actual[40].mnemonic=='dec' and actual[40].op_str=='ebx'
         and actual[65].op_str==actual[74].op_str=='edi'
         and actual[81].op_str=='dword ptr [0x65704c]'
         and actual[86].op_str=='dword ptr [0x65702c]',
         'genuine native original COM handle slots, eight-index twin releases or imported lifetime incorrect')
    need(actual[87].op_str=='dword ptr [0x68e264], ebp'
         and actual[88].op_str=='eax, 0x68e264'
         and actual[90].op_str=='ecx, dword ptr [eax]'
         and actual[91].op_str=='ecx, esi'
         and actual[93].op_str=='eax, [ecx + 0xac]'
         and actual[94].op_str=='dword ptr [eax], ebp'
         and actual[95].mnemonic=='jne'
         and actual[99].op_str=='ecx, dword ptr [ecx + 0xac]'
         and actual[100].op_str=='dword ptr [eax], ecx',
         'genuine original global singly linked COM manager head/next unlink algorithm changed')
    return {'original_whole_native_PE_function':f'0x{ADDR:08X}',
            'original_entire_linked_MACHINE_CODE_exact_bytes':SIZE,
            'original_entire_x86_instructions':X86,
            'original_actual_zero_addend_typed_DIR32_fields':len(fields),
            'genuine_original_two_stdcall_COM_virtual_slots':['+0xE0','+8'],
            'genuine_original_com_release_loop_elements':8,
            'original_list_head_PE_address':'0x0068E264',
            'original_link_next_member_offset':'0xAC',
            'genuine_original_native_import_targets':[
                '0x00657048','0x0065704C','0x0065702C'],
            'actual_original_source_historical_author':'unknown',
            'new_accepted_whole_game_authored_CODE_bytes':0}


def original_direct_callers(reader,pe,decoder,functions):
    found=[]
    for src,meta in functions.items():
        for i in decoder.disasm(reader.pe_bytes_at(pe,src,int(meta['size'])),src):
            if i.mnemonic=='call' and i.op_str==f'0x{ADDR:x}':
                found.append({'original_PE_direct_CALL':f'0x{i.address:08X}',
                              'registered_original_caller':f'0x{src:08X}',
                              'current_caller_origin':meta['owner']})
    return found


def main():
    reader=reader_tool();pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions={int(x['address'],16):x for x in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={x['address']:x for x in csv.DictReader(stream)}
    need(len(functions)==len(origins)==4351,'pinned original registered function inventory changed')
    obj=fresh_source()
    proof=verify_native(reader,pe,decoder,obj,functions,origins)
    graph=original_direct_callers(reader,pe,decoder,functions)
    receipt={'pinned_original_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'ordinary_Cplusplus_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'exact_complete_original_native_COM_manager_release_and_unlink':proof,
             'genuine_original_registered_direct_CALLers':graph,
             'new_source_backed_whole_original_origin_unknown_count':1,
             'new_complete_source_backed_original_native_CODE_bytes':SIZE,
             'new_game_authored_whole_function_exact_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F691: one original complete 0061F125 COM cleanup and linked-list unlink '
          'whole function: all 249/249 authentic linked native CODE bytes, '
          '104/104 real original x86 instructions and five zero-addend DIR32 '
          'true PE/COFF import/head fields. Original source owner UNKNOWN; '
          f'{len(graph)} original registered direct CALLers. One small '
          'pinned VC7.1 /O1 TU only, zero authored CODE credit, no full replay.')


if __name__=='__main__':
    main()
