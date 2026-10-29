#!/usr/bin/env python3
"""F680: five true entire origin-unknown 5/6/11/14B original SDK leaves.

One small fresh pinned VC7.1 /O1 C++ object. Require all five registered
original whole function extents, x86, raw linked CODE bytes and every
physical original IAT DIR32/call REL32 (zero addend, real symbol).
No accepted authored CODE credit without independently proven owner.
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
SOURCE=ROOT/'probes/SDKNativeHelperLeavesF680.cpp'
OUT=ROOT/'.analysis/f680-sdk-native-helper-leaves'
# Entire original registered native function extents; one physical field
# per callee/IAT except original 00614BC6 (true direct this-returner).
CASES={
    0x0060EA69:(14,6,'?Cleanup@FreeImportedMember@@QAEXXZ',9,'DIR32',
                '__imp__ImportedFree@4',0x0065704C),
    0x0061FB37:(14,7,'?Cleanup@FreeDirectMember@@QAEXXZ',8,'REL32',
                '_SDKCFree',0x00640F15),
    0x00614BC6:(6,3,'?Reset@ClearReturnMember@@QAEPAV1@XZ',None,None,None,None),
    0x0060C120:(11,4,'?MaybeFinish@SentinelMember@@QAEXXZ',6,'REL32',
                '?Finish@SentinelMember@@QAEXXZ',0x0060C0DF),
    0x00620132:(5,1,'?Forward@NativeForwarder@@QAEXXZ',1,'REL32',
                '?Target@NativeForwarder@@QAEXXZ',0x0061FE0A),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def reader_tool():
    spec=importlib.util.spec_from_file_location('f680_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'canonical original native PE/COFF reader missing')
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module;spec.loader.exec_module(module)
    return module


def new_object():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'five-native-source-unknown-whole-helpers.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
             '/O1','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'original pinned VC7.1 O1 C++ ABI source failed: '+cp.stderr[-450:])
    return obj


def physical_whole(reader,pe,dec,obj,addr,contract,functions,origins):
    size,x86,symbol,offset,kind,callee_symbol,callee=contract
    native_meta=functions.get(addr)
    need(native_meta is not None and int(native_meta['size'])==size,
         f'original registered {addr:#x} whole PE CODE extent differs')
    original_origin=origins[f'0x{addr:08X}']
    need(original_origin['origin']=='unknown' and original_origin['disposition']=='review',
         f'actual original {addr:#x} attribution no longer unknown/review')
    native=reader.pe_bytes_at(pe,addr,size)
    source,fields=reader.object_function(obj,symbol,expected_size=size)
    linked=bytearray(source)
    if offset is None:
        need(not fields and callee is None,
             f'{addr:#x}: original no-relocation real member return source changed')
    else:
        need(len(fields)==1 and fields[0]['offset']==offset
             and fields[0]['type']==kind and fields[0]['addend']==0
             and fields[0]['local_symbol_offset'] is None
             and fields[0]['symbol']==callee_symbol and callee is not None,
             f'{addr:#x}: actual source physical original typed COFF field changed')
        need(source[offset:offset+4]==bytes(4),
             f'{addr:#x}: original physical COFF source field was not genuine zero-addend')
        original_operand=struct.unpack_from('<I',native,offset)[0]
        if kind=='REL32':
            want=(callee-(addr+offset+4))&0xFFFFFFFF
        else:
            want=callee
        need(original_operand==want,
             f'{addr:#x}: genuine original PE native callee/IAT target changed')
        struct.pack_into('<I',linked,offset,want)
    need(bytes(linked)==native,
         f'{addr:#x}: whole original linked PE CODE bytes not byte exact')
    true=list(dec.disasm(native,addr))
    generated=list(dec.disasm(bytes(linked),addr))
    need(len(true)==len(generated)==x86
         and sum(a.size for a in true)==sum(a.size for a in generated)==size
         and all((a.mnemonic,a.op_str,a.size)==(b.mnemonic,b.op_str,b.size)
                 for a,b in zip(true,generated)),
         f'{addr:#x}: original native whole x86 ABI/mnemonics/width/epilogue differs')
    need(true[-1].mnemonic in ('ret','jmp'),
         f'{addr:#x}: incomplete original entire native final exit')
    if addr==0x0060EA69:
        need(true[4].mnemonic=='call' and true[4].op_str=='dword ptr [0x65704c]'
             and true[-1].mnemonic=='ret',
             'true imported STDCALL cleanup must CALL actual original PE IAT')
    elif addr==0x0061FB37:
        need(true[4].mnemonic=='call' and true[5].op_str=='ecx'
             and true[6].mnemonic=='ret',
             'true direct CDECL cleanup requires native stack pop before return')
    elif addr==0x00614BC6:
        need(true[0].op_str=='eax, ecx'
             and true[1].mnemonic=='and' and true[1].op_str=='dword ptr [eax], 0'
             and true[-1].mnemonic=='ret',
             'original optimized chainable this-return member reset semantics changed')
    elif addr==0x0060C120:
        need(true[0].op_str=='dword ptr [ecx], -1'
             and true[2].mnemonic=='jmp' and true[2].op_str=='0x60c0df'
             and true[3].mnemonic=='ret',
             'real sentinel-guarded tailcall and physical RET differ')
    elif addr==0x00620132:
        need(true[0].mnemonic=='jmp' and true[0].op_str=='0x61fe0a',
             'real registered native whole jump-only member forwarder differs')
    return {'original_registered_complete_PE_function':f'0x{addr:08X}',
            'original_entire_native_linked_CODE_bytes_exact':size,
            'original_entire_x86_instructions':x86,
            'actual_original_zero_addend_typed_PE_COFF_fields':len(fields),
            'original_physical_target':f'0x{callee:08X}' if callee is not None else None,
            'original_source_owner':'unknown',
            'accepted_new_game_authored_whole_CODE_bytes':0}


def actual_native_direct_callers(reader,pe,dec,functions):
    result={addr:[] for addr in CASES}
    for caller,meta in functions.items():
        for ins in dec.disasm(reader.pe_bytes_at(pe,caller,int(meta['size'])),caller):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                dest=int(ins.op_str,16)
                if dest in result:
                    result[dest].append({'original_PE_CALL':f'0x{ins.address:08X}',
                                         'original_registered_caller':f'0x{caller:08X}',
                                         'current_caller_origin':meta['owner']})
    return result


def main():
    reader=reader_tool();pe=reader.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions={int(r['address'],16):r for r in csv.DictReader(stream)}
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origins={r['address']:r for r in csv.DictReader(stream)}
    need(len(functions)==len(origins)==4351,'actual original registered source inventory differs')
    obj=new_object()
    receipts=[physical_whole(reader,pe,dec,obj,addr,control,functions,origins)
              for addr,control in CASES.items()]
    need(len(receipts)==5
         and sum(x['original_entire_native_linked_CODE_bytes_exact'] for x in receipts)==50
         and sum(x['original_entire_x86_instructions'] for x in receipts)==21
         and sum(x['actual_original_zero_addend_typed_PE_COFF_fields'] for x in receipts)==4,
         'five distinct original registered source-backed whole native helper totals changed')
    callers=actual_native_direct_callers(reader,pe,dec,functions)
    output={'pinned_original_native_PE_SHA256':hashlib.sha256(pe).hexdigest(),
            'ordinary_C++_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            'five_new_original_entire_native_source_backed_functions':receipts,
            'genuine_original_registered_direct_CALLers':{f'0x{addr:08X}':a for addr,a in callers.items()},
            'new_complete_origin_unknown_function_count':5,
            'new_original_linked_source_backed_whole_CODE_bytes':50,
            'new_accepted_authored_entire_game_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(output,indent=2)+'\n')
    print('F680 five genuine complete original source-UNKNOWN optimized helper '
          'functions: 50/50 entire linked native CODE B, 21 full native x86, '
          'four actual zero-addend typed PE/COFF call/IAT fields. Normal '
          'pinned VC7.1 /O1, no authored credit, no all-unit cold replay.')
    for addr,rows in callers.items():
        print(f'  original native {addr:#010x}: {len(rows)} registered direct CALLs; '
              f'{sum(r["current_caller_origin"]=="authored" for r in rows)} authored callers')


if __name__=='__main__':
    main()
