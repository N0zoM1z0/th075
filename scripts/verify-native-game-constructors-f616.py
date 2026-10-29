#!/usr/bin/env python3
"""F616: original 34+23+31-byte game constructor source reconstruction.

Cold-build only two selected ordinary VC7.1 source TUs (explicit and
implicit default ctor), compare all THREE complete Japanese TH075
native CODE extents, all x86 instruction sizes/GPR/CFG, and real five
physical typed PE/COFF destinations to their actual native callees
and vtable DWORDs. Independent caller graph scans 4351 original
registered x86 extents. Original authored-vs-vendor provenance is
UNKNOWN; ZERO new authored exact credit or full all-unit cold replay.
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
from collections import Counter,defaultdict
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
EXPLICIT=ROOT/'probes/NativeGameConstructorsF616.cpp'
IMPLICIT=ROOT/'probes/NativeGameConstructorsImplicitF616.cpp'
OUT=ROOT/'.analysis/f616-native-constructors/verified'
CASES=(
 ('0x004251C0',34,13,'??0SceneBaseWithMemberF616@@QAE@XZ',
  {12:('DIR32',0x00657B88,'??_7SceneBaseWithMemberF616@@6B@'),
   23:('REL32',0x00417210,'??0GameMemberF616@@QAE@XZ')}),
 ('0x00458670',23,10,'??0AuxiliaryBaseF616@@QAE@XZ',
  {12:('DIR32',0x0065904C,'??_7AuxiliaryBaseF616@@6B@')}),
 ('0x00458650',31,12,'??0AuxiliaryDerivedF616@@QAE@XZ',
  {11:('REL32',0x00458670,'??0AuxiliaryBaseF616@@QAE@XZ'),
   20:('DIR32',0x00659038,'??_7AuxiliaryDerivedF616@@6B@')}),
)


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing original PE reader')
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def compile_one(name,source):
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/(name+'.obj')
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=160)
    (OUT/(name+'.log')).write_text(p.stdout+p.stderr)
    need(p.returncode==0,
         f'{name}: original native VC7.1 natural default ctor TU did not compile: {p.stderr[-450:]}')
    return obj


def check_full(reader,pe,decoder,obj,case,mode):
    where,size,count,sym,fields=case
    address=int(where,16)
    native=reader.pe_bytes_at(pe,address,size)
    # Original PE has complete native source extent. Implicit compiler
    # special members can lack a COFF function-definition auxiliary
    # record even while their whole CODE genuinely exists, so pass
    # the original full verified extent explicitly.
    code,refs=reader.object_function(obj,sym,expected_size=size)
    original=list(decoder.disasm(native,address))
    generated=list(decoder.disasm(code,address))
    need(len(code)==len(native)==size and len(original)==len(generated)==count
         and sum(x.size for x in original)==sum(x.size for x in generated)==size
         and original[-1].mnemonic==generated[-1].mnemonic=='ret'
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(original,generated)),
         f'{mode} {where}: complete native CODE x86 instruction count/order/geometry differs')
    need(len(refs)==len(fields),
         f'{mode} {where}: exact original physical COFF field count differs')
    linked=bytearray(code)
    field_ranges=set()
    receipts=[]
    for offset,(typ,target,symbol) in fields.items():
        originalfield=[r for r in refs if r['offset']==offset]
        need(len(originalfield)==1 and originalfield[0]['type']==typ
             and originalfield[0]['symbol']==symbol and originalfield[0]['addend']==0
             and originalfield[0]['local_symbol_offset'] is None,
             f'{mode} {where}: physical typed COFF at +{offset:#x} target differs: {originalfield}')
        field_ranges.update(range(offset,offset+4))
        origvalue=struct.unpack_from('<I',native,offset)[0]
        want=target if typ=='DIR32' else (target-(address+offset+4))&0xFFFFFFFF
        need(origvalue==want and struct.unpack_from('<I',code,offset)[0]==0,
             f'{mode} {where}: real native original PE absolute/relative target at +{offset:#x} differs')
        struct.pack_into('<I',linked,offset,want)
        ins=next((x for x in original if x.address<=address+offset<x.address+x.size),None)
        need(ins is not None and (ins.mnemonic=='call' if typ=='REL32' else ins.mnemonic=='mov'),
             f'{mode} {where}: COFF source opcode not a true native CALL/vtable MOV')
        receipts.append({'original_byte_offset':f'+0x{offset:X}',
                         'type':typ,'original_native_target':f'0x{target:08X}',
                         'real_source_COFF_symbol':symbol,'zero_addend':True})
    matched=sum(native[i]==code[i] for i in range(size) if i not in field_ranges)
    need(matched==size-4*len(fields) and bytes(linked)==native,
         f'{mode} {where}: original native fully target-resolved whole CODE differs')
    return {'original_native_start':where,'original_whole_CODE_bytes':size,
            'native_complete_x86_instructions':count,
            'native_nonfield_CODE_bytes_equal':matched,
            'real_original_typed_vtable_and_CALL_COFF_fields':receipts,
            'native_CODE_exact_after_mapping_real_original_reloc_targets':True,
            'full_native_vtable_object_data_verified':False,
            'original_author_written_vs_implicit_special_member': 'UNKNOWN',
            'official_accepted_new_authored_CODE_bytes':0}


def independent_callers(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as file:
        rows=list(csv.DictReader(file))
    addresses={int(row[0],16) for row in CASES}
    calls=defaultdict(list)
    for row in rows:
        start=int(row['address'],16)
        for ins in decoder.disasm(reader.pe_bytes_at(pe,start,int(row['size'])),start):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                dest=int(ins.op_str,16)
                if dest in addresses:
                    calls[f'0x{dest:08X}'].append({
                        'original_native_caller_function':row['address'],
                        'original_native_CALL_instruction':f'0x{ins.address:08X}',
                        'current_caller_origin':row['owner'],
                        'current_caller_proposed_name':row['proposed_name']})
    scene=calls['0x004251C0']
    derived=calls['0x00458650']
    base=calls['0x00458670']
    need(len(rows)==4351 and len(scene)==15
         and len(derived)==2 and len(base)==2
         and all(x['current_caller_origin']=='authored' for x in scene+derived)
         and len([x for x in base if x['current_caller_origin']=='authored'])==1
         and len([x for x in base if x['original_native_caller_function']=='0x00458650'])==1,
         'native original author/library caller distribution for 3 game constructors changed')
    return {'original_complete_function_boundaries_scanned':len(rows),
            'original_real_direct_CALLs_by_ctor':dict(calls),
            'native_15_distinct_authored_scene_initializers_call_scene_ctor':True,
            'game_user_not_original_source_ctor_author_proof':True}


def main():
    reader=load('f616_reader',ROOT/'scripts/compare-coff-function.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/function-origins.csv').open(newline='') as file:
        origin={row['address']:row for row in csv.DictReader(file)}
    need(all(origin[row[0]]['origin']=='unknown'
             and origin[row[0]]['disposition']=='review' for row in CASES),
         'native original constructor ownership status changed: inspect real origin before credit')
    explicit=compile_one('ordinary-explicit',EXPLICIT)
    implicit=compile_one('ordinary-implicit',IMPLICIT)
    full={}
    for label,obj in [('explicit-source',explicit),('implicit-source',implicit)]:
        rows=[check_full(reader,pe,decoder,obj,case,label) for case in CASES]
        full[label]=rows
        for row in rows:
            print(f'F616 {label} {row["original_native_start"]}: '
                  f'{row["original_whole_CODE_bytes"]}/{row["original_whole_CODE_bytes"]} '
                  f'original target-resolved CODE bytes, '
                  f'{row["native_complete_x86_instructions"]} native x86, '
                  f'{len(row["real_original_typed_vtable_and_CALL_COFF_fields"])} true COFF refs; '
                  'original written-vs-implicit provenance UNKNOWN',flush=True)
    # Real complete machine-code evidence exists for BOTH natural
    # explicitly written empty constructor definitions and compiler-
    # synthesized implicit default constructors. Do not conflate exact
    # codegen grammar with original game author vs library ownership.
    callers=independent_callers(reader,pe,decoder)
    summary={'native_original_EXE_sha256':hashlib.sha256(pe).hexdigest(),
             'explicit_source_sha256':hashlib.sha256(EXPLICIT.read_bytes()).hexdigest(),
             'implicit_source_sha256':hashlib.sha256(IMPLICIT.read_bytes()).hexdigest(),
             'both_natural_CXX_source_profiles':'VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi',
             'original_whole_native_CODE_by_compiler_alternative':full,
             'native_original_callers':callers,
             'source_reproducible_real_CODE_bytes':sum(x[1] for x in CASES),
             'complete_game_functions_accepted_exact_authored_new':0,
             'credited_new_original_authored_CODE_bytes':0,
             'full_943_unit_cold_replay':False}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(f'F616: 3 genuine original whole constructor CODE functions, '
          f'{summary["source_reproducible_real_CODE_bytes"]} original bytes / '
          '5 real typed original PE vtable/callee fields, BOTH explicit and implicit '
          'natural VC7.1 C++ reproduce full originals after real-target relocation. '
          'Original ownership unknown, ZERO accepted authored CODE, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F616 original Japanese TH075 natural constructor source failed:',exc,file=sys.stderr)
        raise SystemExit(1)
