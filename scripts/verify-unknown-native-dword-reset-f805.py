#!/usr/bin/env python3
"""F805: original 00454C00 24B/9-x86 single DWORD reset.

One-source full VC7.1 native exact code-generation proof and four
typed field controls. Int/unsigned/float all produce same original
24B machine code; signed word/byte change memory-store width. No
independent original call owner; provenance stays unknown/review and
no formal authored exact CODE credit. No corpus-wide cold replay.
"""
from __future__ import annotations
import csv
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f805-native-borrowed-reset'
SOURCE=ROOT/'probes/UnknownNativeDwordResetF805.cpp'
ORIGINAL=0x00454C00
SIZE=24
SYM='?ResetStatus@BorrowedStateFlagF805@@QAEXXZ'

def need(p,reason):
    if not p:raise ValueError(reason)

def load():
    sp=importlib.util.spec_from_file_location('f805_reader',ROOT/'scripts/compare-coff-function.py')
    m=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=m
    sp.loader.exec_module(m)
    return m

def native_codegen(name,text):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/(name+'.cpp')
    obj=OUT/(name+'.obj')
    cpp.write_text(text)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/(name+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'F805 target C++ source build failed '+name+
         (run.stdout+run.stderr)[-450:])
    return obj

def main():
    rd=load()
    pe=rd.verified_target()
    origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    listed={r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    address='0x00454C00'
    need(origins[address]['origin']=='unknown'
         and origins[address]['disposition']=='review'
         and listed[address]['status']=='unclassified'
         and int(listed[address]['size'])==SIZE,
         'original provenance/whole-native candidate has been changed without review')
    original=rd.pe_bytes_at(pe,ORIGINAL,SIZE)
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(d.disasm(original,ORIGINAL))
    need(len(native)==9 and sum(x.size for x in native)==SIZE
         and native[-1].mnemonic=='ret'
         and native[5].mnemonic=='mov' and
         native[5].op_str=='dword ptr [eax + 0x47c], 0',
         'whole native original DWORD zero store/ABI unverified')
    source=SOURCE.read_text()
    need('BORROWED observed' in source and source.count('unsigned int statusAt47C;')==1,
         'borrowed native actual field identity lost')
    variants={
      'unsigned-native':source,
      'signed-dword':source.replace('unsigned int statusAt47C;','int statusAt47C;'),
      'float-dword':source.replace('unsigned int statusAt47C;','float statusAt47C;').replace('statusAt47C = 0;','statusAt47C = 0.0f;'),
      'signed-word':source.replace('unsigned int statusAt47C;','signed short statusAt47C;'),
      'unsigned-byte':source.replace('unsigned int statusAt47C;','unsigned char statusAt47C;'),
    }
    expected={'unsigned-native':(SIZE,9,True),'signed-dword':(SIZE,9,True),
              'float-dword':(SIZE,9,True),'signed-word':(23,9,False),
              'unsigned-byte':(21,9,False)}
    result=[]
    for name,text in variants.items():
        obj=native_codegen(name,text)
        code,refs=rd.object_function(obj,SYM)
        ins=list(d.disasm(code,0))
        count,instructions,equal=expected[name]
        need(len(code)==count and len(ins)==instructions
             and len(refs)==0 and (code==original)==equal,
             'whole original F805 native field/width mismatch '+name)
        result.append({'variant':name,'original_complete_CODE_B':SIZE,
            'compiler_full_CODE_B':len(code),'native_original_x86':9,
            'compiler_x86':len(ins),'actual_original_COFF_fields':0,
            'entire_original_machine_CODE_equal':equal})
    report={'original_function':'0x00454C00',
            'original_owner_provenance':'unknown; no independent game owner/caller attested',
            'physically_observed_this_field_offset':'0x47C',
            'physically_proven_zero_store_width_B':4,
            'original_complete_CODE_B':SIZE,'original_whole_x86':9,
            'three_independent_Cpp_types_same_native_machine_code':True,
            'source_field_nominal_type':'unproved (dword-sized int/unsigned/float codegen equal)',
            'whole_source_variants':result,'real_pe_fields':0,
            'authored_exact_accepted_delta':0,'all_unit_cold_replay_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+chr(10))
    print('F805 original 00454C00: full native 24B/9 x86/zero PE refs reproduced from natural borrowed state reset. Three distinct dword types all exact, narrower 23B/21B wrong. Historical provenance unknown: no authored credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F805 whole original PE source check FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
