#!/usr/bin/env python3
"""F724: reconstruct whole native 2C5 831B/239-x86 case in one full boss.

Read original complete 0054DDD2..0054E111 PE, 23 typed physical
PE/COFF fields and source wrong native x87/EBP. Actual original
2BF->2C0->2C1->2C4->2C5 native order is retained. Cold-compile
only one original-shaped giant VC7.1 TU; recheck all prior real
actions, 27 context-strict original internal bodies and full 943B
afterRET DATA in SAME parent. No inner-case game FUNCTION credit.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f724-fighter-followup-pair'
ACTOR=0x00543210
NATIVE_START=0x0054DDD2
NATIVE_END=0x0054E111
ORIGINAL_CODE_B=831
ORIGINAL_X86=239
ORIGINAL_PHYSICAL_FIELDS=23
SOURCE_START=7525
SOURCE_LATE_STORM_PRIOR=(7764,8296,8465,8654,8843,9012)
SOURCE_LATE_STORM_MAIN=(10327,10989,11170)
SOURCE_302_END=11431
SOURCE_SCRATCH_SHIFT=24
SOURCE_THIS_MOV_USES=3317
ORIGINAL_NATIVE_STACK={
 109:('0x178','0xb0'),110:('0x178','0xb0'),
 156:('0x17c','0xb4'),157:('0x17c','0xb4'),
 197:('0x180','0xb8'),198:('0x180','0xb8'),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'original PE/COFF verifier missing: '+path)
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def source_with_2c5(source):
    previous='        case 0x2C5: g_FighterProbeMarker = 710; break;'
    need(source.count(previous)==1,'original 2C5 source placeholder not unique')
    source=source.replace(previous,'#include "FighterFollowupBurstF724.inc"')
    old='extern float g_F722_LowYAt00659A10;'
    need(source.count(old)==1,'true original 2C1 float global declaration missing')
    source=source.replace(old,old+'\nextern float g_F724_ShotYAt00659488;')
    need(source.count('#include "FighterFollowupBurstF724.inc"')==1
         and source.count('#include "FighterEarlyPairF722.inc"')==1,
         'new 2C5 must appear exactly once after source 2C0/2C1')
    return source


def validate_real_2c5(reader,pe,real,f676,f598,f722,boss,mapped,ins,refs):
    by={x['action']:int(x['handler'],16) for x in mapped}
    need(by[0x2C5]==NATIVE_START and by[0x2D0]==NATIVE_END
         and NATIVE_END-NATIVE_START==ORIGINAL_CODE_B
         and boss['address']<NATIVE_START<NATIVE_END<boss['address']+boss['size'],
         'true original 2C5 native complete 831-byte physical PE extent changed')
    native=list(real.disasm(reader.pe_bytes_at(pe,NATIVE_START,ORIGINAL_CODE_B),NATIVE_START))
    source=ins[SOURCE_START:SOURCE_START+ORIGINAL_X86]
    need(len(native)==len(source)==ORIGINAL_X86
         and sum(x.size for x in native)==sum(x.size for x in source)==ORIGINAL_CODE_B
         and all(a.size==b.size for a,b in zip(native,source))
         and native[-1].mnemonic==source[-1].mnemonic=='jmp'
         and native[-1].op_str=='0x5515c2',
         'whole original 2C5 physical 831B/239 x86 source width or native CFG exit differs')
    original_fields=f676.original_fields(native)
    symbols=dict(f722.ORIGINAL_TARGET_SYMS)
    symbols[0x00659488]=('g_F724_ShotYAt00659488',)
    fields=f722.physical_fields(original_fields,source,refs,symbols)
    need(len(original_fields)==len(fields)==ORIGINAL_PHYSICAL_FIELDS,
         'all 23 original physical typed native PE/COFF fields not retained at original ordinals')
    bad=[(i,a.mnemonic,b.mnemonic) for i,(a,b) in enumerate(zip(native,source))
         if a.mnemonic!=b.mnemonic]
    need(bad==[(112,'fsubr','fadd')]
         and native[108].op_str=='edx, edx, 0x2e'
         and source[108].op_str=='edx, edx, -0x2e'
         and native[112].op_str==source[112].op_str=='dword ptr [eax + 0x44]',
         'original 2C5 true IMUL +46/FSUBR vs source equivalent -46/FADD negative differs')
    abs_fields={i for i,target,mn in original_fields if mn!='call'}
    wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),f598.normalized(source)))
           if a!=b and i not in abs_fields]
    need(wrong==[108,112],
         f'original complete 2C5 GPR/CFG source phase mismatch changed: {wrong[:8]}')
    for i,(native_slot,source_slot) in ORIGINAL_NATIVE_STACK.items():
        a,b=native[i],source[i]
        need(a.mnemonic==b.mnemonic and a.size==b.size==6
             and f'[ebp - {native_slot}]' in a.op_str
             and f'[ebp - {source_slot}]' in b.op_str,
             f'2C5 original native x86{i} actual integer-to-x87 scratch EBP ownership not preserved')
    need([source[i].op_str for i in (115,141,162,203)]==['0x74','0x3c','0x344','0x32e']
         and source[165].op_str=='0x1f4' and source[167].mnemonic=='call'
         and source[220].mnemonic==source[237].mnemonic=='call'
         and [x.mnemonic for x in ins[SOURCE_START+ORIGINAL_X86:SOURCE_START+ORIGINAL_X86+3]]
          ==['push','push','push'],
         'real original native 2C5 74/3C/344/32E and 2D0 case boundary changed')
    return {'native_entire_physical_interval':[f'0x{NATIVE_START:08X}',f'0x{NATIVE_END:08X}'],
       'original_entire_CODE_bytes':ORIGINAL_CODE_B,
       'current_generated_entire_CODE_bytes':sum(x.size for x in source),
       'native_and_source_entire_x86':ORIGINAL_X86,
       'all_true_original_typed_PE_COFF_fields':len(fields),
       'original_nonfield_GPR_CFG_differences':wrong,
       'original_full_case_real_wrong_EBP_owners':ORIGINAL_NATIVE_STACK,
       'original_2C5_byte_exact':False}


def main():
    f696=load('f724_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f724_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f724_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f724_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f708=load('f724_f708','scripts/verify-fighter-twin-burst-f708.py')
    f711=load('f724_f711','scripts/verify-fighter-falling-radials-f711.py')
    f714=load('f724_f714','scripts/verify-fighter-complex-movement-f714-f715.py')
    f718=load('f724_f718','scripts/verify-fighter-double-volley-f718.py')
    f720=load('f724_f720','scripts/verify-fighter-late-storm-f720-f721.py')
    f722=load('f724_f722','scripts/verify-fighter-native-order-f722.py')
    f672=load('f724_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f724_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f724_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f724_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f724_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f724_reader','scripts/compare-coff-function.py')
    acts=load('f724_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    parent,modules,helpers=f714.combine_source(f706,f708,f711,f696,f699,f701,f672,
                                                reader,pe,real,boss,report,mapped)
    parent=f718.source_with_double_volley(parent)
    parent=f720.source_with_both(parent)
    parent=f722.native_order_source(parent)
    parent=source_with_2c5(parent)
    obj=f706.compile_whole_parent(parent)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-2C5.cpp').write_text(parent)
    shutil.copyfile(obj,OUT/'Boss00543210-2C5.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,
              f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    emitted=[]
    for ins in real.disasm(code,0):
        emitted.append(ins)
        if ins.mnemonic=='ret':break
    new=validate_real_2c5(reader,pe,real,f676,f598,f722,boss,mapped,emitted,refs)
    previous_pair=f722.verify_new_cases(reader,pe,real,f676,f598,boss,mapped,
                                       emitted,refs,following_native_2c5=True)
    earlier_twins=f708.check_native_cases(f701,f676,f598,reader,pe,real,boss,mapped,
                 emitted,refs,source_starts={0x2BF:6831,0x2C4:7394},
                 source_ebp_shift_by_action={0x2BF:0,0x2C4:12},
                 source_expected_GPR={0x2BF:(2,39),0x2C4:(2,39)})
    previous_radials=f711.compare_native_radials(reader,pe,real,f676,f598,f701,
                 boss,mapped,emitted,refs,following_native_2db=True,
                 source_starts={0x2D0:7764,0x2D1:7884},
                 source_ebp_shift=SOURCE_SCRATCH_SHIFT,
                 source_next_2db_registers=('ecx','edx'),
                 source_expected_GPR={0x2D0:0,0x2D1:0})
    previous_movement=f714.audit_cases(f701,f676,f598,f699,reader,pe,real,boss,mapped,
                 emitted,refs,following_native_2dd=True,
                 source_starts={0x2DB:8004,0x2DC:8296},
                 source_ebp_shift=SOURCE_SCRATCH_SHIFT,
                 source_expected_GPR={0x2DB:(159,89),0x2DC:(1,128)})
    previous_double=f718.verify_two_native_actions(f701,f676,f598,reader,pe,real,boss,mapped,
                 emitted,refs,following_native_2df=True,
                 source_starts={0x2DD:8465,0x2DE:8654},
                 source_ebp_shift=SOURCE_SCRATCH_SHIFT,
                 source_expected_GPR={0x2DD:0,0x2DE:0})
    previous_late=f720.prove_both(f701,f714,f676,f598,reader,pe,real,boss,mapped,
                 emitted,refs,source_starts={0x2DF:8843,0x2E5:9012},
                 source_after_2e5=9235,source_ebp_shift=SOURCE_SCRATCH_SHIFT)
    original_five,start=f706.native_cases_and_compiled_start(f672,reader,pe,real,boss,mapped,
                                                               emitted,refs)
    previous_five,end=f706.verify_five_native_cases(f672,f598,f701,original_five,
                                                    emitted,refs,start)
    need(end==6623,'actual original preceding 259-25D five case boundaries moved')
    later,source302end=f706.check_later_native_physical(
         f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,emitted,refs,
         expected_storm_starts=SOURCE_LATE_STORM_MAIN,
         preceding_storm_starts=SOURCE_LATE_STORM_PRIOR)
    need(source302end==SOURCE_302_END,
         'original late 302 native 935-B source or following 31B boundary changed')
    context=f696.verify_prior_parent_context(
        reader,pe,real,boss,report,mapped,code,refs,modules,helpers,
        expected_receiver_uses=SOURCE_THIS_MOV_USES,following_native_2fa=True,
        source_receiver_slot='0x28',source_scratch_slot='0x40',
        source_scratch_shift=32,source_f684_slot_shift=184,
        source_native_302_end_ordinal=source302end,
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=end,
        following_native_2bf=True,source_storm_bytes=928,
        source_storm_width_differences=f706.SOURCE_STORM_WIDTHS,
        source_2f0_2f1_expected_GPR_counts={0x2F0:(147,39),0x2F1:(170,0)},
        source_native_2e5_end_ordinal=9235)
    need(context['previous_27_nonterminal_context_strict_original_cases_rechecked']
         and context['actual_source_context_nonterminal_strict_case_count']==27
         and context['original_2ef_real_GPR_regression']==0
         and context['original_2f0_2f1_real_GPR_mismatches']==[147,170]
         and context['original_after_RET_switch_DATA_rechecked_on_this_source'],
         'real 2C5 source must preserve prior strict 2EF and independent whole native afterRET DATA')
    receipt={'original_boss_whole_function':'0x00543210',
      'original_boss_total_CODE_bytes_NONEXACT':boss['size'],
      'original_separate_afterRET_switch_DATA_bytes':boss['postret_size'],
      'new_full_original_native_action_2C5':new,
      'new_original_internal_ACTION_CODE_bytes_NOT_CREDITED':ORIGINAL_CODE_B,
      'new_original_physical_native_x86_instructions':ORIGINAL_X86,
      'new_original_zero_addend_typed_PE_COFF_fields':ORIGINAL_PHYSICAL_FIELDS,
      'prior_original_full_2C0_2C1':previous_pair,
      'prior_original_full_2BF_2C4':earlier_twins,
      'prior_original_full_2D0_2D1':previous_radials,
      'prior_original_full_2DB_2DC':previous_movement,
      'prior_original_full_2DD_2DE':previous_double,
      'prior_original_full_2DF_2E5':previous_late,
      'prior_original_full_five_259_25D':previous_five,
      'prior_original_late_2F8_302':later,
      'prior_original_27_strict_context_2EF_and_whole_afterRET_DATA':context,
      'whole_original_GAME_function_exact':False,
      'new_accepted_exact_GAME_function_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F724 native original 00543210 action2C5 whole 831B/239 x86/23 authentic '
          'physical PE/COFF fields restored as actual normal VC7.1 C++ with all '
          'native x86 instruction widths and 238/239 native mnemonics. Genuine '
          'IMUL +46/FSUBR native vs source -46/FADD and 3 actual EBP scratch '
          'owners remain nonexact. In the SAME whole original-shaped giant, '
          'new genuine action improves 2D0 and 2D1 original GPR mismatch '
          '60->0, 2DB 235->159 and 2DC 80->1; 2EF remains native STRICT '
          'inside 27 prior strict context cases; original physical typed '
          'fields and full 943B afterRET switch DATA rechecked. No new '
          'accepted whole original function CODE, no 943-unit cold replay.')


if __name__=='__main__':
    main()
