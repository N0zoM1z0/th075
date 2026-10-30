#!/usr/bin/env python3
"""F714/F715: reproduce complete original native 2DB (1024B/290 x86)
and 2DC (602B/169 x86) in ONE original-shaped 00543210 fighter TU.

Check all 52 true PE/COFF typed fields, raw original instruction
geometry, original x87 and EBP negative positions. Recheck all prior
recoveries and the entire independently owned 943-byte afterRET DATA
in this newly compiled parent. The whole 58KB function is NONEXACT;
no internal-case function exactness credit or full 943-unit replay.
"""
from __future__ import annotations
import difflib
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f714-fighter-boss-movement'
BOSS=0x00543210
ORIGINAL={0x2DB:(0x0054E451,0x0054E851,1024,290,34),
          0x2DC:(0x0054E851,0x0054EAAB,602,169,18)}
SOURCE_CASE_STARTS={0x2DB:7339,0x2DC:7631}
SOURCE_2DB_CODE_B=1032
SOURCE_2DB_X86=292
EXPECTED_2DB_MNEMONIC_EDITS=(
 ('replace',129,130,129,131),
 ('replace',132,133,133,134),
 ('replace',141,142,142,144),
 ('replace',144,145,146,147),
 ('insert',210,210,212,213),
 ('delete',212,213,215,215),
 ('replace',221,222,223,224))
# This is an EBP original source-owner negative, not a cosmetic offset.
EBP={0x2DB:{248:('0x194','0xb4'),249:('0x194','0xb4')},
     0x2DC:{76:('0x198','0xb8'),77:('0x198','0xb8'),
             100:('0x19c','0xbc'),101:('0x19c','0xbc')}}
NATIVE_CONTEXT_WRONG={0x2DB:236,0x2DC:95}
F714_GLOBAL_SYMBOLS={
 0x00454BC0:'ConfigureStormAt454BC0',
 0x00453D40:'PrepareActionAt453D40',
 0x0065782C:'g_ThresholdAt0065782C',
 0x0040FB40:'SetAuxActionAt40FB40',
 0x00657868:'g_F714_ShotYAt00657868',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x006714D0:'g_CloudOpponentAt006714D0',
 0x0065747C:'g_F714_DecelerationAt0065747C',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00455580:'RandomBoundaryAt455580',
}


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,relative):
    spec=importlib.util.spec_from_file_location(name,ROOT/relative)
    need(spec is not None and spec.loader is not None,'original verifier unavailable: '+relative)
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def combine_source(f706,f708,f711,f696,f699,f701,f672,reader,pe,real,boss,report,mapped):
    src,modules,h=f706.source_for_new_combined_parent(
         f696,f699,f701,f672,reader,pe,real,boss,report,mapped)
    src=f708.source_for_genuine_twins(src)
    src=f711.source_with_radials(src)
    for action,filename in ((0x2DB,'FighterApproachPhaseF715.inc'),
                            (0x2DC,'FighterBossMovementF714.inc')):
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(marker)==1,f'actual full original action {action:#x} marker absent')
        src=src.replace(marker,'#include "'+filename+'"')
        need(src.count('#include "'+filename+'"')==1,
             'missing authentic distinct original action C++ source '+filename)
    decl='extern float g_F711_ReverseRandomAt00659A0C;'
    need(src.count(decl)==1,'original selected VC7.1 source true global 00659A0C declaration changed')
    src=src.replace(decl,decl+'\nextern float g_F714_ShotYAt00657868;\n'
        'extern float g_F714_DecelerationAt0065747C;\n'
        'extern float g_F715_DecisionHeightAt006593D0;')
    return src,modules,h


def audit_cases(f701,f676,f598,f699,reader,pe,real,boss,mapped,emitted,refs,*,
                following_native_2dd=False):
    by={x['action']:int(x['handler'],16) for x in mapped}
    results=[]
    for action in (0x2DB,0x2DC):
        addr,hi,nb,nx,nfields=ORIGINAL[action]
        need(by[action]==addr and by[0x2DC if action==0x2DB else 0x2DD]==hi
             and hi-addr==nb and boss['address']<addr<hi<boss['address']+boss['size'],
             f'original native {action:#x} whole physical interval not verified')
        native=list(real.disasm(reader.pe_bytes_at(pe,addr,hi-addr),addr))
        source_start=SOURCE_CASE_STARTS[action]
        source_nx=nx if action==0x2DC else SOURCE_2DB_X86
        gen=emitted[source_start:source_start+source_nx]
        need(len(native)==nx and sum(x.size for x in native)==nb
             and len(gen)==source_nx
             and sum(x.size for x in gen)==(nb if action==0x2DC else SOURCE_2DB_CODE_B)
             and native[-1].mnemonic==gen[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'whole original {action:#x} 1024/602 bounded source/CFG geometry changed')
        original_fields=f676.original_fields(native)
        symbols=(dict(f699.TARGET_SYMBOLS) if action==0x2DB
                 else dict(F714_GLOBAL_SYMBOLS))
        if action==0x2DB:
            symbols[0x006593D0]='g_F715_DecisionHeightAt006593D0'
            symbols[0x00657888]='g_ContactProjectionAt00657888'
        fields=f701.compare_typed_fields(original_fields,gen,refs,symbols,
                tuple(i for i,target,mn in original_fields),ordinal_strict=action==0x2DC)
        need(len(fields)==len(original_fields)==nfields,
             f'original {action:#x}: all original physical relocation targets/owners missing')
        if action==0x2DC:
            need(all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(native,gen))
                 and native[0].op_str==gen[0].op_str=='0xff0000'
                 and native[106].op_str==gen[106].op_str=='0x387'
                 and native[82].op_str==gen[82].op_str=='0x333',
                 'whole original 2DC 602B/169 x86 width/opcode/projectiles mismatched')
        else:
            seq=difflib.SequenceMatcher(a=[x.mnemonic for x in native],
                b=[x.mnemonic for x in gen],autojunk=False)
            changes=tuple((tag,a1,a2,b1,b2) for tag,a1,a2,b1,b2 in seq.get_opcodes() if tag!='equal')
            need(changes==EXPECTED_2DB_MNEMONIC_EDITS
                 and native[129].mnemonic==native[141].mnemonic=='fcomp'
                 and gen[129].mnemonic==gen[142].mnemonic=='fld'
                 and gen[130].mnemonic==gen[143].mnemonic=='fcompp'
                 and native[183].op_str==gen[185].op_str=='0x2df'
                 and native[193].op_str==gen[195].op_str=='0x2dc'
                 and native[197].op_str==gen[199].op_str=='0x2dc',
                 f'original 2DB two extra x87 load compare and double 2DC decision changed: {changes}')
        # Compare physical original source GPR and stack independently.
        absolute={i for i,t,mn in original_fields if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),f598.normalized(gen)))
               if a!=b and i not in absolute]
        need(len(wrong)==NATIVE_CONTEXT_WRONG[action] and wrong[0] in (0,5),
             f'actual original {action:#x} source GPR/CFG negative unexpectedly changed')
        for i,(native_slot,src_slot) in EBP[action].items():
            j=i if action==0x2DC else i+2
            need(f'[ebp - {native_slot}]' in native[i].op_str
                 and f'[ebp - {src_slot}]' in gen[j].op_str
                 and native[i].size==gen[j].size==6,
                 f'original {action:#x} genuine typed six-byte EBP scratch owner at x86{i} changed')
        results.append({'native_original_action':f'0x{action:X}',
                        'physical_original_start':f'0x{addr:08X}',
                        'original_next_action_start':f'0x{hi:08X}',
                        'native_entire_CODE_B':nb,'new_generated_entire_source_CODE_B':sum(x.size for x in gen),
                        'native_x86':nx,'new_source_x86':len(gen),
                        'all_zero_addend_original_PE_COFF_references':len(fields),
                        'real_native_GPR_CFG_negative_count':len(wrong),
                        'real_native_vs_compiler_EBP_scratch_operands':EBP[action],
                        'source_original_case_byte_exact':False})
    next_after_2dc=SOURCE_CASE_STARTS[0x2DC]+ORIGINAL[0x2DC][3]
    need(emitted[SOURCE_CASE_STARTS[0x2DB]+SOURCE_2DB_X86].op_str=='0xff0000',
         'native 2DB must lead into whole original 2DC storm')
    if following_native_2dd:
        need([x.mnemonic for x in emitted[next_after_2dc:next_after_2dc+3]]
             ==['push','push','push']
             and [x.op_str for x in emitted[next_after_2dc:next_after_2dc+3]]
             ==['0xff0000','4','3'],
             'real full native 2DC must lead to independently verified source-backed 2DD storm')
    else:
        need(emitted[next_after_2dc].mnemonic=='mov'
             and emitted[next_after_2dc].op_str.endswith(', 0x2de'),
             'native full 2DC must lead to its original source placeholder 2DD')
    return results


def main():
    f696=load('f714_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f714_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f714_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f714_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f708=load('f714_f708','scripts/verify-fighter-twin-burst-f708.py')
    f711=load('f714_f711','scripts/verify-fighter-falling-radials-f711.py')
    f672=load('f714_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f714_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f714_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f714_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f714_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f714_reader','scripts/compare-coff-function.py')
    acts=load('f714_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    source,mods,h=combine_source(f706,f708,f711,f696,f699,f701,f672,
                                   reader,pe,real,boss,report,mapped)
    obj=f706.compile_whole_parent(source)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-2DB-2DC.cpp').write_text(source)
    shutil.copyfile(obj,OUT/'Boss00543210-2DB-2DC.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler-both.log')
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ')
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    new=audit_cases(f701,f676,f598,f699,reader,pe,real,boss,mapped,emitted,refs)
    prior_radial=f711.compare_native_radials(reader,pe,real,f676,f598,f701,boss,mapped,emitted,refs,
                                            following_native_2db=True)
    previous_twin=f708.check_native_cases(f701,f676,f598,reader,pe,real,boss,mapped,emitted,refs)
    original_five,start=f706.native_cases_and_compiled_start(
        f672,reader,pe,real,boss,mapped,emitted,refs)
    previous_five,real25Dend=f706.verify_five_native_cases(
        f672,f598,f701,original_five,emitted,refs,start)
    need(real25Dend==6623,'real previous original five 259-25D case geometry changed')
    later,source302end=f706.check_later_native_physical(
        f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,
        emitted,refs,expected_storm_starts=(8900,9562,9743),
        preceding_storm_starts=(7099,7631))
    need(source302end==10004,
         'new physical native 302 complete action end/31B original boundary changed')
    previous_context=f696.verify_prior_parent_context(
        reader,pe,real,boss,report,mapped,code,refs,mods,h,
        expected_receiver_uses=2904,following_native_2fa=True,
        source_receiver_slot='0x28',source_scratch_slot='0x40',
        source_scratch_shift=32,source_f684_slot_shift=120,
        source_native_302_end_ordinal=source302end,
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=real25Dend,
        following_native_2bf=True,source_storm_bytes=928,
        source_storm_width_differences=f706.SOURCE_STORM_WIDTHS,
        source_2ef_expected_GPR_mismatches=144,
        source_2f0_2f1_expected_GPR_counts={0x2F0:(175,0),0x2F1:(170,0)})
    need(previous_context['actual_source_context_nonterminal_strict_case_count']==26
         and previous_context['original_2ef_real_GPR_regression']==144
         and previous_context['original_2f0_2f1_real_GPR_mismatches']==[175,170]
         and previous_context['original_after_RET_switch_DATA_rechecked_on_this_source'],
         'the 26 prior strict internal cases or honest source GPR negatives/943B DATA regressed')
    summary={'original_boss':'0x00543210',
       'entire_original_FUNCTION_CODE_bytes_still_nonexact':boss['size'],
       'original_separately_owned_switch_afterRET_DATA_B':boss['postret_size'],
       'two_new_original_complete_physical_action_bodies':new,
       'new_original_native_internal_CODE_bytes_NOT_CREDITED':1626,
       'new_original_typed_PE_COFF_fields':52,
       'new_original_native_complete_x86_positions':459,
       'previous_original_2D0_2D1_bodies':prior_radial,
       'previous_original_2BF_2C4_bodies':previous_twin,
       'previous_original_259_25D_bodies':previous_five,
       'previous_later_original_2F8_through_302':later,
       'actual_original_26_context_strict_and_2EF_2F0_2F1_regressions_and_DATA':previous_context,
       'original_complete_game_FUNCTION_exact':False,
       'new_accepted_original_game_CODE_B':0}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F714/F715 newly restored full 00543210 original boss action2DB: '
          '1024 physical native B/290 x86/34 typed PE/COFF fields vs 1032 VC7.1 B/292 x86 '
          'with two extra x87 load/compare instructions; 2DC original 602 B/169 x86/18 '
          'fields reproduced with exact opcode/width positions. Both natural C++ '
          'actions retain full native semantics and call fields; genuine register and '
          'stack owner differences remain NONSTRICT. Earlier real 2D0/2D1, 2BF/2C4, '
          'five 259-25D, late 2F8-302 cases, 26 earlier context-strict cases, '
          'explicit original 2EF=144, 2F0/2F1=175/170 GPR negatives and entire '
          '943B original afterRET DATA rechecked in same freshly compiled whole parent. '
          'No accepted independent case/function CODE and no all-unit cold replay.')


if __name__=='__main__':
    main()
