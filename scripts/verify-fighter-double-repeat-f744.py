#!/usr/bin/env python3
"""F744: complete original 19A and 19B real grounded double-repeat fighter.

Compile ONE whole native-shaped 00543210 fighter using genuine VC7.1 C++.
Compare two real complete 607-B/166-x86 original actions, all 34
actual typed PE/COFF original relocations at the same ORIGINAL x86
ordinal, and native FCOMP/float member-FLD/global-FMUL CFG. Original
GPR mnemonic+WIDTH registers (after legitimate receiver normalization)
are exact, but physical EBP slots are NOT. Recheck earlier complete
19C/19E/1A0/1A1, 190–198, 13 later GPR contexts, and entire 943-B
native after-RET DATA with 156 physical target-aligned DIR32 entries.
199/19D/19F share original default, NOT standalone authored CODE.
No fake locals, byte grafting, split-case credit or 964-unit replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f744-fighter-double-repeat'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
CASES=(0x19A,0x19B)
NATIVE={
 0x19A:(0x00549D5C,0x00549FBB,607,166,17,6078,
        ((97,98,'0xb8','0x88'),(145,146,'0xbc','0x8c'))),
 0x19B:(0x00549FBB,0x0054A21A,607,166,17,6244,
        ((97,98,'0xc0','0x90'),(145,146,'0xc4','0x94'))),
}
NEXT={0x19A:0x19B,0x19B:0x19C}
SYMBOLS={
 0x00657F74:'g_BounceScaleAt00657F74',
 0x0065782C:'g_ThresholdAt0065782C',
 0x00659A24:'g_F737_RoundY0At00659A24',
 0x00659A20:'g_F737_RoundY1At00659A20',
 0x00453E20:'ResetAt453E20',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x00453D40:'PrepareActionAt453D40',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0046D000:'StartAnimationAt46D000',
 0x0040FB40:'SetAuxActionAt40FB40',
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,rel):
    sp=importlib.util.spec_from_file_location(name,ROOT/rel)
    need(sp is not None and sp.loader is not None,'original PE or VC7.1 helper missing: '+rel)
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def source_with_19a_19b(src):
    for action in CASES:
        old=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(old)==1,
             f'original physical native action {action:#x} unresolved placeholder absent')
        src=src.replace(old,'#include "FighterDoubleRepeatF744.inc"' if action==0x19A else '')
    need(src.count('#include "FighterDoubleRepeatF744.inc"')==1,
         'two complete original 607-B native game actions must be present exactly once')
    need('POS54=(*(&POS54))*g_BounceScaleAt00657F74;' in
         (ROOT/'probes/FighterDoubleRepeatF744.inc').read_text(),
         'native actor FLD before 657F74-global FMUL real field ownership source not restored')
    for bad in (0x19A,0x19B):
        need(f'case 0x{bad:X}: g_FighterProbeMarker' not in src,
             'real original 19A/19B must NOT remain placeholder-marked')
    return src


def verify_whole_19a_19b(rd,pe,d,f676,f701,f598,by,ins,refs):
    rows=[]
    for action in CASES:
        lo,hi,code_native,nx,nfields,start,scratch=NATIVE[action]
        need(by[action]==lo and by[NEXT[action]]==hi and hi-lo==code_native,
             f'original physical complete {action:#x} native CODE bounds changed')
        native=list(d.disasm(rd.pe_bytes_at(pe,lo,code_native),lo))
        generated=ins[start:start+nx]
        need(len(native)==len(generated)==nx
             and sum(x.size for x in native)==sum(x.size for x in generated)==code_native
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(native,generated))
             and native[-1].mnemonic==generated[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'original native {action:#x} genuine entire 607B/166 x86 opcode/width/order wrong')
        originals=f676.original_fields(native)
        fields=f701.compare_typed_fields(originals,generated,refs,SYMBOLS,
                                          tuple(i for i,_,_ in originals))
        need(len(originals)==len(fields)==nfields,
             f'original {action:#x} ALL physical 17 native PE/COFF fields not owned by authentic x86')
        # These two global-multiply x87 expressions previously compiled
        # FLD GLOBAL + FMUL ACTOR; the real member-lvalue C++ restores
        # original FLD ACTOR + physically typed GLOBAL FMUL at 14/19.
        for n in (14,19):
            need(native[n].mnemonic==generated[n].mnemonic=='fmul'
                 and native[n].op_str=='dword ptr [0x657f74]'
                 and generated[n].op_str=='dword ptr [0]'
                 and native[n].size==generated[n].size==6,
                 f'original {action:#x} real x87 actor-FLD/global-FMUL order not fixed')
        for n in (36,52):
            need(native[n].mnemonic==generated[n].mnemonic=='fcomp'
                 and native[n].op_str=='dword ptr [0x65782c]'
                 and generated[n].op_str=='dword ptr [0]'
                 and native[n+2].op_str==generated[n+2].op_str=='ah, 0x41'
                 and native[n+3].mnemonic==generated[n+3].mnemonic=='jp',
                 f'original {action:#x} real ground x87 FCOMP/TEST AH41/JP is incorrect')
        for mi,fi,old,actual in scratch:
            for n,mnem in ((mi,'mov'),(fi,'fild')):
                x,y=native[n],generated[n]
                need(x.mnemonic==y.mnemonic==mnem
                     and x.size==y.size==6
                     and f'[ebp - {old}]' in x.op_str
                     and f'[ebp - {actual}]' in y.op_str,
                     f'original {action:#x} genuine used native/source 6B integer-x87 stack slot at {n} not checked')
        absfields={i for i,target,mnem in originals if mnem!='call'}
        gpr=[i for i,(x,y) in enumerate(zip(f598.normalized(native),
                                             f598.normalized(generated)))
             if x!=y and i not in absfields]
        need(not gpr,f'original {action:#x} normalized native GPR/CFG operand mismatches {gpr[:10]}')
        angle='dword ptr [edx + 0x314], 0xc1a00000'
        if action==0x19A:
            need(native[96].op_str==generated[96].op_str=='edx, edx, 0x23'
                 and native[144].op_str==generated[144].op_str=='eax, eax, 0x23'
                 and native[84].op_str==generated[84].op_str=='dword ptr [eax + 0x314], 0',
                 'native 19A physical stage4/5 original zero angle or signed 35 direction lost')
        else:
            need(native[96].op_str==generated[96].op_str=='ecx, ecx, 0x1b'
                 and native[144].op_str==generated[144].op_str=='edx, edx, 0x1b'
                 and native[84].op_str==generated[84].op_str==angle,
                 'native 19B physical stage4/5 -20 angle and signed 27 direction lost')
        need(native[103].op_str==generated[103].op_str=='0x330'
             and native[151].op_str==generated[151].op_str=='0x330'
             and native[106].op_str==generated[106].op_str=='0x64'
             and native[154].op_str==generated[154].op_str=='0x14'
             and native[157].op_str==generated[157].op_str=='4',
             f'original {action:#x} two genuine stage4/5 330 shots/animation100/20/action4 not recovered')
        rows.append({'native_original_action':f'0x{action:X}',
          'original_entire_PE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
          'original_entire_CODE_bytes':code_native,
          'current_source_entire_CODE_bytes':sum(x.size for x in generated),
          'original_and_Cpp_x86_mnemonics_AND_WIDTHS':nx,
          'original_true_typed_PE_COFF_physical_fields':len(fields),
          'native_physical_657F74_FMUL_at_both_ordinals':[14,19],
          'two_original_FCOMP_65782C_ordinals':[36,52],
          'actual_native_and_source_x87_scratch_EBP_offsets':[
              {'native_MOV_ordinal':mi,'native_FILD_ordinal':fi,
               'original_used_EBP':old,'actual_compiler_EBP':actual}
              for mi,fi,old,actual in scratch],
          'normalized_nonfield_GPR_CFG_mismatches':0,
          'original_whole_game_function_byte_exact':False})
    need(ins[6078].mnemonic==ins[6244].mnemonic==ins[6410].mnemonic=='mov'
         and ins[6410].op_str=='ecx, dword ptr [ebp - 0x3c]',
         'original 198->19A->19B->19C case C++ source start ordinals changed')
    return rows


def main():
    rd=load('f744_rd','scripts/compare-coff-function.py')
    acts=load('f744_acts','scripts/report-fighter-action-handlers.py')
    f676=load('f744_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f701=load('f744_typed','scripts/verify-fighter-four-tier-volley-f701.py')
    f598=load('f744_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f728=load('f744_728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f744_729','scripts/verify-fighter-return-boundary-f729.py')
    f731=load('f744_731','scripts/verify-fighter-aim-return-f731.py')
    f732=load('f744_732','scripts/verify-fighter-following-native-f732.py')
    f734=load('f744_734','scripts/verify-fighter-eight-round-f734.py')
    f737=load('f744_737','scripts/verify-fighter-eight-ground-f737.py')
    f740=load('f744_740','scripts/verify-fighter-repeat-shot-f740.py')
    f743=load('f744_743','scripts/verify-fighter-later-early-f743.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    for original_default in (0x199,0x19D,0x19F):
        need(by[original_default]==0x00551598,
             'physical native 199/19D/19F are shared dispatch default, never standalone actions')
    source,compiler=f728.source_for_complete_parent(rd,pe,d,boss,report,mapped)
    source=f729.source_with_return_boundaries(source)
    source=f731.source_with_aim_return(source)
    source=f732.whole_source_with_following(source)
    source=f734.source_with_three(source)
    source=f737.with_194_195(source)
    source=f740.source_with_repeat_shots(source)
    source=f743.source_with_four(source)
    source=source_with_19a_19b(source)
    obj=compiler.compile_whole_parent(source)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-19A-19B.cpp').write_text(source)
    shutil.copyfile(obj,OUT/'Boss00543210-19A-19B.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=rd.object_function(obj,SYMBOL)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    new=verify_whole_19a_19b(rd,pe,d,f676,f701,f598,by,ins,refs)
    following=f743.verify_native_four(rd,pe,d,f676,f701,f598,by,ins,refs,
                                      following_complete_19A_19B=True)
    preceding=f740.verify_all_three_native(rd,pe,d,f676,f701,f598,by,ins,refs,
                                            following_complete_19A=True)
    prev194=f737.check_entire_cases(rd,pe,d,f676,f701,f598,by,ins,refs,
                                    following_native_196=True)
    prev190=f734.new_native_actions(rd,pe,d,f676,f701,f598,by,ins,refs,
                                    following_native_194=True,source_x87_slot_shift=8)
    mapped=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    context=dict(f737.SELECTED_ACTUAL_CONTEXT)
    context[0x1F4]=(538,149,538,18,0)
    old=f737.check_selected_context(rd,pe,d,f676,f598,by,ins,refs,mapped,
                                    source_1f4_start=6744,source_expected_context=context)
    data=f728.complete_native_switch_DATA(rd,pe,d,boss,code,ins,refs,
                           source_1f5_start=6893,source_1f6_start=7042)
    need(len(new)==2
         and sum(r['original_entire_CODE_bytes'] for r in new)==1214
         and sum(r['original_and_Cpp_x86_mnemonics_AND_WIDTHS'] for r in new)==332
         and sum(r['original_true_typed_PE_COFF_physical_fields'] for r in new)==34
         and [x['true_normalized_nonfield_GPR_CFG_differences'] for x in following]==[0]*4
         and len(old)==13 and all(r['real_nonfield_GPR_CFG_differences']==0 for r in old)
         and data['original_nonrelocation_afterRET_BYTES_equal']==319,
         'new original 19A/19B native PE/COFF or 13 earlier register-phase original contexts not verified')
    receipt={'original_whole_fighter':'0x00543210',
       'original_complete_58KB_GAME_CODE_NONEXACT':boss['size'],
       'two_original_complete_physically_bounded_19A_19B_sources':new,
       'new_original_internal_SOURCE_CODE_BYTES_NOT_CREDITED':1214,
       'new_original_mnemonic_and_width_source_positions':332,
       'new_true_typed_PE_COFF_fields':34,
       'previous_original_19C_19E_1A0_1A1_true_GPR_phase_RESTORED':following,
       'previous_original_196_197_198_real_Cpp_source':preceding,
       'previous_original_194_195_real_source':prev194,
       'previous_original_190_191_192_real_source':prev190,
       'thirteen_original_physical_prior_contexts_all_GPR_strict_in_THIS_parent':old,
       'full_943B_original_native_afterRET_DATA':data,
       'original_199_19D_19F_are_SHARED_DEFAULT':True,
       'original_whole_GAME_function_byte_exact':False,
       'new_original_exact_authored_GAME_CODE_BYTES':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F744 original 00543210 two complete 19A/19B game source: native '
          '607+607 B /166+166 native x86/17+17 genuine typed PE fields '
          'at all original owning instruction ordinals. Natural VC7.1 '
          'source exact native OPCODE and WIDTH geometry; two real '
          'POS54 actor-lvalue sources restore physical FLD ACTOR + '
          'FMUL original global 657F74 ordinal19, avoiding prior '
          'wrong FLD GLOBAL/FMUL member. GPR normalized roles now '
          '0 in both 19A/19B and ALL four neighboring 19C/19E/1A0/1A1, '
          'and all 13 earlier complete original 1F4/1F5/.../200/201 '
          'source contexts. But REAL native x87 EBP -0xB8..-0xD4 '
          'vs source -0x88..-0xA4, saved this native -0x44 vs '
          'source -0x3c: giant NONEXACT. All native 190-198 and '
          'entire 943B afterRET DATA including 156 original/source '
          'DIR32 x86 targets +319 exact sparse bytes rechecked. '
          '199/19D/19F shared native default, no independent CODE. '
          'Zero new whole exact CODE, no 964-unit cold replay.')


if __name__=='__main__':
    main()
