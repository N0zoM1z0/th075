#!/usr/bin/env python3
"""F718: native fighter 2DD and 2DE two complete original source cases.

Verify physically bounded 680/660 CODE B, 189/189 x86 and 19/18
original PE/COFF field owners in one freshly compiled entire
00543210 C++ parent, with real x87/EBP nonexactness. Recheck older
source-backed cases, 26 strict original internal context cases,
genuine 2EF/2F0/2F1 negatives, and ALL 943 original afterRET DATA
in the SAME new parent. No false case/whole-function exact credit.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f718-fighter-double-volley'
ACTOR=0x00543210
ACTIONS=(0x2DD,0x2DE)
NATIVE={0x2DD:(0x0054EAAB,0x0054ED53,680,189,19),
        0x2DE:(0x0054ED53,0x0054EFE7,660,189,18)}
SOURCE_START={0x2DD:7800,0x2DE:7989}
NATIVE_EBP={
 0x2DD:{101:('0x1a0','0xc0'),102:('0x1a0','0xc0'),
        122:('0x1a4','0xc4'),123:('0x1a4','0xc4')},
 0x2DE:{147:('0x1a8','0xc8'),148:('0x1a8','0xc8')},
}
SOURCE_WRONG_GPR={0x2DD:80,0x2DE:0}
FIELD_SYMBOLS={
 0x00454BC0:'ConfigureStormAt454BC0',
 0x00453E20:'ResetAt453E20',
 0x00453D40:'PrepareActionAt453D40',
 0x0065782C:'g_ThresholdAt0065782C',
 0x006581E0:'g_NewDragAt006581E0',
 0x00657480:'g_StopThresholdAt00657480',
 0x0040FB40:'SetAuxActionAt40FB40',
 0x00657868:'g_F714_ShotYAt00657868',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00455580:'RandomBoundaryAt455580',
 0x006714D0:'g_CloudOpponentAt006714D0',
 0x00659090:'g_F718_FallingDragAt00659090',
 0x00657CF8:'g_F718_BounceMinAt00657CF8',
 0x00453C80:'SpawnRawXYAt453C80',
}
SOURCE_STORM_PRIOR=(7099,7631,7800,7989)
SOURCE_STORM_LATER=(9274,9936,10117)
SOURCE_302_END=10378
SOURCE_SAVED_THIS='0x28'
SOURCE_SAVED_THIS_MOV_COUNT=3015


def need(cond,message):
    if not cond:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'original selected evidence absent: '+path)
    mod=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=mod
    spec.loader.exec_module(mod)
    return mod


def source_with_double_volley(src):
    for action in ACTIONS:
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(marker)==1,f'original physical {action:#x} parent marker not unique')
        src=src.replace(marker,
                        '#include "FighterDoubleVolleyF718.inc"' if action==0x2DD else '')
    needle='extern float g_F715_DecisionHeightAt006593D0;'
    need(src.count(needle)==1,'original native F715 global declaration changed')
    src=src.replace(needle,needle+'\nextern float g_F718_FallingDragAt00659090;\n'
                    'extern float g_F718_BounceMinAt00657CF8;')
    need(src.count('#include "FighterDoubleVolleyF718.inc"')==1,
         'two original complete volley cases must be included as one genuine normal source')
    return src


def verify_two_native_actions(f701,f676,f598,reader,pe,real,boss,mapped,ins,refs,*,
                              following_native_2df=False,source_starts=None,source_ebp_shift=0,
                              source_expected_GPR=None):
    starts=SOURCE_START if source_starts is None else source_starts
    need(all(action in starts for action in ACTIONS),'source original 2DD/2DE starts missing')
    by={x['action']:int(x['handler'],16) for x in mapped}
    result=[]
    for action in ACTIONS:
        lo,hi,native_bytes,nx,expected_fields=NATIVE[action]
        need(by[action]==lo and by[0x2DE if action==0x2DD else 0x2DF]==hi
             and hi-lo==native_bytes and boss['address']<lo<hi<boss['address']+boss['size'],
             f'original physical 2DD/2DE native PE extent changed at {action:#x}')
        original=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        start=starts[action]
        generated=ins[start:start+nx]
        need(len(original)==len(generated)==nx
             and sum(x.size for x in original)==sum(x.size for x in generated)==native_bytes
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(original,generated))
             and original[-1].mnemonic==generated[-1].mnemonic=='jmp'
             and original[-1].op_str=='0x5515c2',
             f'whole original source/native {action:#x} 189-x86 opcode/width geometry differs')
        orig_fields=f676.original_fields(original)
        fields=f701.compare_typed_fields(orig_fields,generated,refs,FIELD_SYMBOLS,
                                          tuple(i for i,_,_ in orig_fields))
        need(len(fields)==len(orig_fields)==expected_fields,
             f'original {action:#x} all typed PE/COFF fields do not have true native x86 owners')
        original_absolute={i for i,t,m in orig_fields if m!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(original),
                                              f598.normalized(generated)))
               if a!=b and i not in original_absolute]
        expected=(source_expected_GPR or {}).get(action,SOURCE_WRONG_GPR[action])
        need(len(wrong)==expected and (not wrong or wrong[0]==5),
             f'native {action:#x} actual reg/CFG normalized roles changed {wrong[:8]}')
        for ordinal,(native_slot,source_slot) in NATIVE_EBP[action].items():
            source_slot=f"0x{int(source_slot,16)+source_ebp_shift:x}"
            a,b=original[ordinal],generated[ordinal]
            need(a.size==b.size==6
                 and f'[ebp - {native_slot}]' in a.op_str
                 and f'[ebp - {source_slot}]' in b.op_str
                 and a.mnemonic==b.mnemonic,
                 f'original {action:#x} physical x86{ordinal} float temp EBP owner was masked')
        if action==0x2DD:
            need([original[i].op_str for i in (107,128)]==['0x329','0x387']
                 and [generated[i].op_str for i in (107,128)]==['0x329','0x387']
                 and original[170].mnemonic==generated[170].mnemonic=='call'
                 and original[187].mnemonic==generated[187].mnemonic=='call',
                 'native 2DD full two real projectile kinds and terminal stage calls changed')
        else:
            need(original[115].op_str==generated[115].op_str=='0x3c'
                 and original[153].op_str==generated[153].op_str=='0x329'
                 and original[168].op_str==generated[168].op_str=='0xc'
                 and original[185].op_str==generated[185].op_str=='0x17',
                 'native 2DE phase7 raw shot and phase16/25 progression differs')
        result.append({
           'original_action':f'0x{action:03X}',
           'original_physical_start':f'0x{lo:08X}',
           'original_next_case':f'0x{hi:08X}',
           'native_entire_CODE_bytes':native_bytes,
           'source_entire_CODE_bytes':sum(x.size for x in generated),
           'native_and_generated_x86_positions':nx,
           'all_original_zero_addend_typed_PE_COFF_references':len(fields),
           'genuine_normalized_original_GPR_CFG_differences':len(wrong),
           'actual_original_and_compiler_EBP_x87_scratch':NATIVE_EBP[action],
           'native_case_byte_exact':False})
    after=starts[0x2DE]+NATIVE[0x2DE][3]
    need([x.mnemonic for x in ins[starts[0x2DE]:starts[0x2DE]+3]]
         ==['push','push','push'],
         'native 2DE must retain its true original storm header')
    if following_native_2df:
        need([x.mnemonic for x in ins[after:after+3]]==['push','push','push']
             and [x.op_str for x in ins[after:after+3]]==['0xff0000','4','3'],
             'native 2DE must lead to independently verified full native 2DF source')
    else:
        need(ins[after].mnemonic=='mov'
             and ins[after].op_str.endswith(', 0x2e0'),
             'original 2DE must lead to its former real 2DF source placeholder')
    return result


def main():
    f696=load('f718_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f718_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f718_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f718_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f708=load('f718_f708','scripts/verify-fighter-twin-burst-f708.py')
    f711=load('f718_f711','scripts/verify-fighter-falling-radials-f711.py')
    f714=load('f718_f714','scripts/verify-fighter-complex-movement-f714-f715.py')
    f672=load('f718_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f718_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f718_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f718_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f718_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f718_reader','scripts/compare-coff-function.py')
    acts=load('f718_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    src,modules,helpers=f714.combine_source(f706,f708,f711,f696,f699,f701,f672,
                                            reader,pe,real,boss,report,mapped)
    src=source_with_double_volley(src)
    obj=f706.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-double-volley.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-double-volley.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    two=verify_two_native_actions(f701,f676,f598,reader,pe,real,boss,mapped,emitted,refs)
    prior_2db_2dc=f714.audit_cases(f701,f676,f598,f699,reader,pe,real,boss,mapped,
                                      emitted,refs,following_native_2dd=True)
    prior_2d0_2d1=f711.compare_native_radials(reader,pe,real,f676,f598,f701,boss,mapped,
                                              emitted,refs,following_native_2db=True)
    prev_twins=f708.check_native_cases(f701,f676,f598,reader,pe,real,boss,mapped,emitted,refs)
    prev_originals,first=f706.native_cases_and_compiled_start(
                         f672,reader,pe,real,boss,mapped,emitted,refs)
    prev_five,end=f706.verify_five_native_cases(f672,f598,f701,prev_originals,emitted,refs,first)
    need(end==6623,'original 259-25D selected full action bounds regressed')
    late,source302end=f706.check_later_native_physical(
        f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,
        emitted,refs,expected_storm_starts=SOURCE_STORM_LATER,
        preceding_storm_starts=SOURCE_STORM_PRIOR)
    need(source302end==SOURCE_302_END,
         'native 2DD/2DE source changed complete original 302 end/31B boundary')
    context=f696.verify_prior_parent_context(
        reader,pe,real,boss,report,mapped,code,refs,modules,helpers,
        expected_receiver_uses=SOURCE_SAVED_THIS_MOV_COUNT,following_native_2fa=True,
        source_receiver_slot=SOURCE_SAVED_THIS,source_scratch_slot='0x40',
        source_scratch_shift=32,source_f684_slot_shift=132,
        source_native_302_end_ordinal=source302end,
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=end,
        following_native_2bf=True,source_storm_bytes=928,
        source_storm_width_differences=f706.SOURCE_STORM_WIDTHS,
        source_2ef_expected_GPR_mismatches=144,
        source_2f0_2f1_expected_GPR_counts={0x2F0:(175,0),0x2F1:(170,0)})
    need(context['actual_source_context_nonterminal_strict_case_count']==26
         and context['original_2ef_real_GPR_regression']==144
         and context['original_2f0_2f1_real_GPR_mismatches']==[175,170]
         and context['original_after_RET_switch_DATA_rechecked_on_this_source'],
         'previous original strict and 2EF GPR phase negatives or complete 943B afterRET DATA regressed')
    receipt={
      'original_whole_boss':'0x00543210',
      'original_entire_giant_CODE_bytes_NONEXACT':boss['size'],
      'original_independent_afterRET_switch_DATA_bytes':boss['postret_size'],
      'new_true_original_complete_internal_action_source':two,
      'new_source_backed_original_internal_CODE_bytes_NOT_CREDITED':1340,
      'new_original_physical_typed_PE_COFF_fields':37,
      'new_original_x86_mnemonic_and_width_positions':378,
      'previous_original_2DB_and_2DC':prior_2db_2dc,
      'previous_original_2D0_and_2D1':prior_2d0_2d1,
      'previous_original_2BF_and_2C4':prev_twins,
      'previous_original_five_259_through_25D':prev_five,
      'previous_original_2F8_through_302':late,
      'previous_strict_original_cases_GPR_negatives_and_complete_afterRET_DATA':context,
      'whole_original_game_FUNCTION_byte_exact':False,
      'new_accepted_complete_GAME_FUNCTION_CODE_bytes':0,
    }
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F718 original 00543210 twin complete physical 2DD/2DE actions: 680+660 '
          'original CODE B, 189+189 real x86 positions, 19+18 original typed PE/COFF '
          'fields exactly owned at native x86 ordinals, normal VC7.1 C++ '
          'in one full 58KB parent; 2DD still 80 real GPR differences, '
          '2DE zero normalized GPR differences but original EBP scratch '
          '0x1A8 vs compiler 0xC8. NONSTRICT, no credit. Earlier 2DB/2DC, '
          '2D0/2D1, 2BF/2C4, five 259-25D, 2F8-302 original contexts, '
          '26 context-strict prior cases, real 2EF/2F0/2F1 GPR negatives '
          'and the independent whole original 943B afterRET table rechecked. '
          'No 943-unit mass replay or accepted exact giant.')


if __name__=='__main__':
    main()
