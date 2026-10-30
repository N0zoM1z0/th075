#!/usr/bin/env python3
"""F778: true 00551598 game action fallback in one whole 58KB VC7.1 fighter.

Original 239 table action IDs target the same 32-B/10-x86 native guard.
Compared complete original PE and all genuine COFF fields, preserving four
real register differences and 11 still missing CODE bytes. Internal case is
NOT accepted byte-exact CODE. No accepted-unit all-corpus cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f778-fighter-default-native-whole'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
NATIVE_BEGIN=0x00551598
NATIVE_GUARD_END=0x005515B8
NATIVE_END=0x005515C7


def need(ok,why):
    if not ok:raise ValueError(why)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing tracked original PE helper '+path)
    m=importlib.util.module_from_spec(sp)
    sys.modules[tag]=m
    sp.loader.exec_module(m)
    return m


def source_for_one_full_parent(f759,f762):
    source,boss=f762.make_parent(f759)
    for old,new in [
        ('#include "FighterApproachPhaseF715.inc"','#include "FighterApproachNativeF763.inc"'),
        ('#include "FighterApproachVolleyF699.inc"','#include "FighterApproachVolleyNativeF764.inc"'),
        ('#include "FighterAngleStormF684.inc"','#include "FighterAngleStormTypedF767.inc"'),
        ('#include "FighterStormVolleyF681.inc"','#include "FighterStormVolleyTypedF768.inc"'),
        ('#include "FighterGroundedVolleyF696.inc"','#include "FighterGroundedVolleyTypedF771.inc"')]:
        need(source.count(old)==1,'missing whole-original game source fragment '+old)
        source=source.replace(old,new)
    anchor='void FighterSwitchF598_Boss00543210::Advance() {'
    need(source.count(anchor)==1,'whole native class source missing')
    source=source.replace(anchor,'#include "FighterBorrowedXYViewF771.hpp"\n'+anchor)
    marker='        default: g_FighterProbeMarker = 0;'
    need(source.count(marker)==1,'native old fake default marker missing')
    source=source.replace(marker,'#include "FighterNativeDefaultF778.inc"')
    return source,boss


def cold_one_compiled_giant(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F778-full.cpp'
    obj=OUT/'Boss00543210-F778-full.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,'VC7.1 entire native source compilation failed '+
         (result.stdout+result.stderr)[-1000:])
    return obj


def original_default_original_guard(rd,pe,d,code,refs,ins,mapping):
    source_start=mapping[NATIVE_BEGIN]
    original=rd.pe_bytes_at(pe,NATIVE_BEGIN,NATIVE_GUARD_END-NATIVE_BEGIN)
    native=list(d.disasm(original,NATIVE_BEGIN))
    generated=[x for x in ins if source_start<=x.address<source_start+32]
    need(len(original)==32 and len(native)==len(generated)==10,
         'original default guard real 32B/10-x86 boundary not recovered')
    need(all(a.mnemonic==b.mnemonic and a.size==b.size and
             a.address-NATIVE_BEGIN==b.address-source_start
             for a,b in zip(native,generated)),
         'original whole default source opcode/size/start not matched')
    fields=[x for x in refs if source_start<=x['offset']<source_start+32]
    need(len(fields)==2,'native default getter/setter two original calls missing')
    masks=set();targets=[]
    for x in fields:
        off=x['offset']-source_start
        need(x['type']=='REL32' and x['addend']==0 and x['local_symbol_offset'] is None
             and all(k not in masks and 0<=k<32 for k in range(off,off+4)),
             'native original default physical call relocation invalid')
        masks.update(range(off,off+4))
        raw=int.from_bytes(original[off:off+4],'little')
        disp=raw if raw<2**31 else raw-2**32
        actual=NATIVE_BEGIN+off+4+disp
        match=re.search(r'At([0-9A-Fa-f]{6,8})(?=[^0-9A-Fa-f]|$)',x['symbol'])
        need(match is not None and actual==int(match.group(1),16),
             'original PE default-handler target does not match native COFF')
        targets.append(actual)
    need(targets==[0x0040FA30,0x0040FAC0],
         'original default getter/setter source calls not in original order')
    original_nonfield_bad=[k for k in range(32) if k not in masks and
         original[k]!=code[source_start+k]]
    need(original_nonfield_bad==[10,12,16,19],
         'native original default four real register operand byte differences changed: '+
         str(original_nonfield_bad))
    tail=[x for x in ins if x.address>=source_start]
    original_tail=list(d.disasm(rd.pe_bytes_at(pe,NATIVE_BEGIN,NATIVE_END-NATIVE_BEGIN),NATIVE_BEGIN))
    need(len(tail)==13 and len(original_tail)==16 and
         tail[-3].mnemonic=='mov' and tail[-2].mnemonic=='pop' and tail[-1].mnemonic=='ret',
         'original 2-byte JMP and 8-byte code before epilogue remain truly missing')
    return {'original_shared_fallback':'0x00551598',
            'original_guaranteed_guard_CODE_B':32,
            'source_guard_CODE_B':32,
            'original_and_source_guard_x86_mnemonic_width_ordinals':10,
            'genuine_native_zero_addend_physical_CALL_fields':2,
            'original_PE_destinations':[f'0x{x:08X}' for x in targets],
            'still_wrong_true_guard_GPR_bytes':len(original_nonfield_bad),
            'first_wrong_offsets':original_nonfield_bad,
            'remaining_original_2B_JMP_and_8B_unmapped_tail_NOT_EXACT':10,
            'source_default_game_behavior_restored':True,
            'complete_game_boss_exact':False}


def main():
    f759=load('f778_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f760=load('f778_f760','scripts/verify-fighter-complex-stage-cc-ce-f760.py')
    f762=load('f778_f762','scripts/verify-fighter-typed-returns-f762.py')
    f764=load('f778_f764','scripts/verify-fighter-approach-volley-native-f764.py')
    f767=load('f778_f767','scripts/verify-fighter-angle-storm-typed-f767.py')
    f768=load('f778_f768','scripts/verify-fighter-storm-volley-typed-f768.py')
    f771=load('f778_f771','scripts/verify-fighter-grounded-volley-typed-f771.py')
    f734=load('f778_f734','scripts/verify-fighter-eight-round-f734.py')
    actions=load('f778_actions','scripts/report-fighter-action-handlers.py')
    rd=load('f778_reader','scripts/compare-coff-function.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    source,boss=source_for_one_full_parent(f759,f762)
    report,mapped=actions.report_boss(rd,pe,d,boss)
    need(int(report['default'],16)==NATIVE_BEGIN and
         sum(int(x['handler'],16)==NATIVE_BEGIN for x in mapped)==239,
         'PE jump-table native default handler not original 239 action aliases')
    obj=cold_one_compiled_giant(source)
    code,refs=rd.object_function(obj,SYM)
    ins=f760.code_instructions(d,code)
    end=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and boss['postret_size']==943 and end==58283
         and len(ins)==16468 and len(code)==end+943,
         'original full boss still 11B short and 3 x86 short, NOT exact')
    mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    guard=original_default_original_guard(rd,pe,d,code,refs,ins,mapping)
    # Every previously established complete original-source action still
    # recompiles within this one full parent; do not assume old OBJ valid.
    f2fb=f771.check_original_complete_case(rd,pe,d,code,refs,ins,mapping)
    f2f8=f768.verify_original_2f8(rd,pe,d,code,refs,ins,mapping)
    f2f9=f767.verify_native_2f9(rd,pe,d,code,refs,ins,mapping)
    f2fa=f764.whole_game_native_2fa(rd,pe,d,code,refs,ins,mapping)
    f2db=f762.original_case(rd,pe,d,code,refs,ins,mapping,0x2DB,
         (0x0054E451,0x0054E851,1024,290,34))
    three=[f762.original_case(rd,pe,d,code,refs,ins,mapping,c,x)
           for c,x in f762.ORIGINAL.items()]
    c8,tail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapping,
         {0xC8:0x0054737F,0xC9:0x0054756F,0xCA:0x00547717,
          0xCB:0x005478CE,0xCC:0x00547A8B})
    cc=[f760.physical_case(rd,pe,d,code,refs,ins,mapping,c,x,check_targets=True)
        for c,x in f760.ORIG.items()]
    after=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    report={'entire_original_game_function':'0x00543210',
            'original_whole_CODE_B':58294,'reconstructed_entire_CODE_B':end,
            'native_CALLABLE_CODE_shortfall_B':boss['size']-end,
            'true_shared_default_native_behavior':guard,
            'independently_proven_original_239_action_aliases':239,
            'rechecked_F771_original_2FB':f2fb,
            'rechecked_F768_original_2F8':f2f8,
            'rechecked_F767_original_2F9':f2f9,
            'rechecked_F764_original_2FA':f2fa,
            'rechecked_F763_original_2DB':f2db,
            'rechecked_F762_three_1F6_1F7_1F8':three,
            'rechecked_F759_C8_CB':c8,'rechecked_F760_CC_CD_CE':cc,
            'original_separately_owned_afterRET_DATA':after,
            'native_whole_byte_exact':False,
            'new_formal_accepted_callable_CODE_credit':0,
            'full_all_units_cold_replayed':False}
    OUT.joinpath('verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F778 original default 00551598 shared by 239 native action IDs; '
          'original 32B/10 x86/2 physical target fields, exactly native '
          'mnemonics/width, FOUR real GPR operand bytes still NONEXACT',flush=True)
    print('F778 full native 00543210 boss source now 58283/58294 CODE B; '
          'still 11B/3-x86 deficit plus many native GPR differences; '
          '943 separate native jump DATA verified, no full cold replay',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F778 whole original fighter PE proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
