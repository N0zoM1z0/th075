#!/usr/bin/env python3
"""F618: true original complete 45-byte background-owner default constructor.

Two independently cold-compiled ordinary VC7.1 source TUs, explicit
and implicit default constructors, both reproduce the *whole* original
45-byte code after resolving three typed original native PE targets.
Read 4351 genuine original function extents for 36 real authored CALLs.
Authored vs implicit-generated source origin remains UNKNOWN and no
whole-function accepted authored byte credit is warranted.
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
EXPLICIT=ROOT/'probes/BackgroundOwnerConstructorsF618.cpp'
IMPLICIT=ROOT/'probes/BackgroundOwnerConstructorsImplicitF618.cpp'
OUT=ROOT/'.analysis/f618-background-owner-verified'
SYMBOL='??0BackgroundOwnerF618@@QAE@XZ'
NATIVE=0x00449DE0
SIZE=45
FIELDS={
   12:('DIR32',0x0065844C,'??_7BackgroundOwnerF618@@6B@'),
   23:('REL32',0x00412620,'??0BackgroundMemberAt4F618@@QAE@XZ'),
   34:('REL32',0x0040AD80,'??0BackgroundMemberAt18F618@@QAE@XZ'),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'native original PE reader missing')
    reader=importlib.util.module_from_spec(spec)
    sys.modules[name]=reader
    spec.loader.exec_module(reader)
    return reader


def compile_one(label,source):
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/(label+'.obj')
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=160)
    (OUT/(label+'.log')).write_text(result.stdout+result.stderr)
    need(result.returncode==0,
         f'{label}: pinned MSVC VC7.1 original constructor source failed: {result.stderr[-460:]}')
    return obj


def verify_one(reader,pe,decoder,obj,label):
    native=reader.pe_bytes_at(pe,NATIVE,SIZE)
    code,refs=reader.object_function(obj,SYMBOL,expected_size=SIZE)
    original=list(decoder.disasm(native,NATIVE))
    generated=list(decoder.disasm(code,NATIVE))
    need(len(code)==len(native)==SIZE and len(original)==len(generated)==16
         and sum(x.size for x in original)==sum(x.size for x in generated)==SIZE
         and original[-1].mnemonic==generated[-1].mnemonic=='ret'
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(original,generated)),
         f'{label}: original native complete 45B/16 x86 extent or assembly width changed')
    need(len(refs)==len(FIELDS)==3,
         f'{label}: true game ctor 3 physically typed PE/COFF fields missing')
    linked=bytearray(code)
    excluded=set()
    receipts=[]
    for off,(typ,target,symbol) in FIELDS.items():
        fields=[x for x in refs if x['offset']==off]
        need(len(fields)==1 and fields[0]['type']==typ
             and fields[0]['symbol']==symbol
             and fields[0]['addend']==0
             and fields[0]['local_symbol_offset'] is None,
             f'{label}: source original typed vtable/call target {target:#x} at {off:#x} differs')
        nativeval=struct.unpack_from('<I',native,off)[0]
        want=target if typ=='DIR32' else (target-(NATIVE+off+4))&0xFFFFFFFF
        need(nativeval==want and code[off:off+4]==b'\x00'*4,
             f'{label}: original PE native vtable/relative callee at physical +{off:#x} differs')
        ins=next((x for x in original if x.address<=NATIVE+off<x.address+x.size),None)
        need(ins is not None and (ins.mnemonic=='call' if typ=='REL32' else ins.mnemonic=='mov'),
             f'{label}: original PE actually typed 32-bit x86 field is not correct CALL/MOV')
        struct.pack_into('<I',linked,off,want)
        excluded.update(range(off,off+4))
        receipts.append({'original_own_CODE_field_offset':f'+0x{off:X}',
                         'real_original_native_PE_target':f'0x{target:08X}',
                         'original_source_COFF_symbol':symbol,'typed_COFF':typ,
                         'actual_COFF_addend_zero':True})
    matches=sum(native[i]==code[i] for i in range(SIZE) if i not in excluded)
    need(matches==SIZE-4*len(FIELDS)==33 and bytes(linked)==native,
         f'{label}: original full linked CODE differs despite other geometry')
    return {'source_alternative':label,
            'original_native_whole_function':'0x00449DE0',
            'whole_original_native_CODE_bytes':SIZE,
            'complete_original_x86_instructions':16,
            'physical_real_typed_COFF_fields':receipts,
            'nonfield_source_bytes_equal':matches,
            'final_all_native_linked_original_CODE_byte_equal':True,
            'original_explicit_vs_generated_source_provenance':'UNKNOWN',
            'new_accepted_whole_authored_CODE_bytes':0}


def scan_original_callers(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as file:
        functions=list(csv.DictReader(file))
    uses=[]
    for row in functions:
        addr=int(row['address'],16)
        for inst in decoder.disasm(reader.pe_bytes_at(pe,addr,int(row['size'])),addr):
            if inst.mnemonic=='call' and inst.op_str==f'0x{NATIVE:x}':
                uses.append({'native_parent_function':row['address'],
                             'original_native_CALL':f'0x{inst.address:08X}',
                             'current_parent_origin':row['owner'],
                             'current_parent_provisional_name':row['proposed_name']})
    need(len(functions)==4351 and len(uses)==36
         and len({x['native_parent_function'] for x in uses})==36
         and all(x['current_parent_origin']=='authored' for x in uses)
         and all(x['current_parent_provisional_name'].startswith('BackgroundStage::LoadBG')
                 for x in uses),
         'original native 36 background-loader game CALL sites unexpectedly changed')
    return {'native_complete_registered_function_extents_decoded':len(functions),
            'real_native_direct_uses':uses,
            'original_callers_are_game_authored':True,
            'game_use_does_not_establish_constructor_source_written_vs_compiler_generated':True}


def main():
    rd=load('f618_reader',ROOT/'scripts/compare-coff-function.py')
    pe=rd.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/function-origins.csv').open(newline='') as f:
        origins={x['address']:x for x in csv.DictReader(f)}
    need(origins['0x00449DE0']['origin']=='unknown'
         and origins['0x00449DE0']['disposition']=='review',
         'real original constructor origin is no longer unknown; reassess classification')
    explicit=compile_one('explicit-source',EXPLICIT)
    implicit=compile_one('implicit-source',IMPLICIT)
    modes=[verify_one(rd,pe,dec,obj,name) for name,obj in
           [('explicit',explicit),('implicit',implicit)]]
    graph=scan_original_callers(rd,pe,dec)
    summary={'actual_original_executable_sha256':hashlib.sha256(pe).hexdigest(),
             'explicit_source_sha256':hashlib.sha256(EXPLICIT.read_bytes()).hexdigest(),
             'implicit_source_sha256':hashlib.sha256(IMPLICIT.read_bytes()).hexdigest(),
             'actual_pinned_compiler_profile':'VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi',
             'native_complete_original_function_source_alternatives':modes,
             'native_original_registered_caller_graph':graph,
             'new_authored_whole_function_match_units':0,
             'new_accepted_authored_original_CODE_bytes':0,
             'all_unit_cold_replay':False}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    for m in modes:
        print(f'F618 {m["source_alternative"]}: native original 0x00449DE0 whole '
              f'{SIZE}/{SIZE} linked original CODE bytes, 16/16 complete x86, '
              '3 original typed vtable/ctor COFF targets; source ownership UNKNOWN',flush=True)
    print(f'F618: {len(graph["real_native_direct_uses"])} genuine direct authored '
          'background loader CALL instructions to native game constructor, '
          'but explicit and implicit C++ generate identical full original CODE. '
          'Zero new accepted authored bytes, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F618 pinned TH075 original background owner constructor failed:',e,file=sys.stderr)
        raise SystemExit(1)
