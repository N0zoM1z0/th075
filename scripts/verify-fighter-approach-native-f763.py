#!/usr/bin/env python3
"""F763: one whole fighter compile proving original 2DB 1024B/290 x86.

This is full original 00543210 source context, NOT a split-case game exact
claim. All real typed PE targets and authentic native jump exceptions checked.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f763-approach-native-whole'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
CASE=(0x0054E451,0x0054E851,1024,290,34)


def need(ok,description):
    if not ok:raise ValueError(description)


def load(tag,relative):
    sp=importlib.util.spec_from_file_location(tag,ROOT/relative)
    need(sp is not None and sp.loader is not None,'missing original target helper '+relative)
    x=importlib.util.module_from_spec(sp)
    sys.modules[tag]=x
    sp.loader.exec_module(x)
    return x


def cold_one(src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F763-full.cpp'
    obj=OUT/'Boss00543210-F763-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,text=True,capture_output=True,timeout=220)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned whole original VC7.1 C++ build failed '+(cp.stdout+cp.stderr)[-900:])
    return obj


def main():
    f759=load('f763_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f760=load('f763_f760','scripts/verify-fighter-complex-stage-cc-ce-f760.py')
    f762=load('f763_f762','scripts/verify-fighter-typed-returns-f762.py')
    f734=load('f763_f734','scripts/verify-fighter-eight-round-f734.py')
    rd=load('f763_rd','scripts/compare-coff-function.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    source,boss=f762.make_parent(f759)
    old='#include "FighterApproachPhaseF715.inc"'
    need(source.count(old)==1,'real 2DB original C++ action placeholder/old source missing')
    source=source.replace(old,'#include "FighterApproachNativeF763.inc"')
    obj=cold_one(source)
    code,refs=rd.object_function(obj,SYM)
    ins=f760.code_instructions(d,code)
    ret=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and ret==58269 and len(code)==ret+943,
         'whole original 58KB CODE deficit and 943B afterRET DATA not accounted')
    mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    # The native case is complete, not just its convenient 15-byte block.
    complete=f762.original_case(rd,pe,d,code,refs,ins,mapping,0x2DB,CASE)
    need(complete['native_nonfield_nontail_bytes_identical']>800 and
         complete['authentic_original_PE_COFF_fields']==34,
         'real native original complete 2DB physical fields or bytes not recovered')
    earlier=[f762.original_case(rd,pe,d,code,refs,ins,mapping,c,r)
             for c,r in f762.ORIGINAL.items()]
    need(len(earlier)==3 and all(q['native_nonfield_nontail_bytes_identical']>900
                                for q in earlier),
         'previous original 1F6/1F7/1F8 strict native code regressed')
    # Recheck all seven previous real game case interiors in same NEW parent.
    by={0xC8:0x0054737F,0xC9:0x0054756F,0xCA:0x00547717,
        0xCB:0x005478CE,0xCC:0x00547A8B}
    previous,tail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapping,by)
    ccs=[f760.physical_case(rd,pe,d,code,refs,ins,mapping,c,r,check_targets=True)
         for c,r in f760.ORIG.items()]
    after=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    # Remaining 2FA deliberately still separate and NONEXACT; don't mask it.
    native_2fa=(0x005509CC,0x00550D97)
    nfa=[x for x in d.disasm(rd.pe_bytes_at(pe,native_2fa[0],native_2fa[1]-native_2fa[0]),native_2fa[0])]
    sfa=[x for x in ins if mapping[native_2fa[0]]<=x.address<mapping[native_2fa[1]]]
    need(len(nfa)==279 and len(sfa)==281 and
         mapping[native_2fa[1]]-mapping[native_2fa[0]]==979,
         'remaining real 2FA plus-two-x87 compiler source mismatch unexpectedly changed')
    report={'whole_original_game_function':'0x00543210',
            'true_original_whole_CODE_B':58294,
            'current_one_compiler_whole_CODE_B':ret,
            'native_whole_CODE_B_still_missing':58294-ret,
            'recovered_real_2DB_whole_case':complete,
            'previous_reverified_native_1F6_1F7_1F8':earlier,
            'reverified_four_C8_CB':previous,
            'reverified_three_CC_CD_CE':ccs,
            'still_nonnative_original_2FA_source_CODE_B':979,
            'original_2FA_CODE_B':971,
            'original_afterRET_separate_DATA':after,
            'complete_giant_byte_exact':False,
            'new_exact_callable_game_CODE_credit':0,
            'all_accepted_units_cold_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F763 native original 2DB: entire 1024 CODE B /290 x86 /34 true PE/COFF'
          ' fields, NO other original bytes differ outside authentic parent-tail JMPs',flush=True)
    print('F763 entire original fighter: 58269/58294 CODE B, STILL NONEXACT;'
          ' 2FA remains 979 emitted vs 971 original; zero new formal CODE',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F763 one whole native original 2DB verification FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
