#!/usr/bin/env python3
"""F711: two complete native 2D0/2D1 real original falling-radial actions.

Cold build ONE whole native-shaped 00543210 C++ parent containing both
real 416B/120-x86 actions, earlier genuine 259/2BF/2C4, and later
2F8-302. Verify all authentic 15 PE/COFF fields per case, every
instruction start/opcode/size, signed global/float evaluation, original
EBP scratches, previous source-context strict cases (26 still strict and 2EF now GPR-nonexact) and the entire
943-byte independently owned afterRET DATA. NONSTRICT != accepted exact.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
from pathlib import Path
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f711-fighter-two-falling-radials'
BOSS=0x00543210
ACTIONS=(0x2D0,0x2D1)
PHYSICAL={0x2D0:(0x0054E111,0x0054E2B1),0x2D1:(0x0054E2B1,0x0054E451)}
SOURCE_START={0x2D0:7099,0x2D1:7219}
NATIVE_BYTES=416
NATIVE_X86=120
ORIGINAL_FIELDS=(4,19,29,36,43,46,49,57,70,73,86,100,107,115,118)
SYMBOLS={
 0x00454BC0:'ConfigureStormAt454BC0',
 0x0065782C:'g_ThresholdAt0065782C',
 0x00658290:'g_ApproachLowerAt00658290',
 0x00453E20:'ResetAt453E20',
 0x0040FB40:'SetAuxActionAt40FB40',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00455580:'RandomBoundaryAt455580',
 0x006592A4:'g_ApproachUpperAt006592A4',
 0x00659A0C:'g_F711_ReverseRandomAt00659A0C',
 0x00658268:'g_EightShotY2At00658268',
 0x00453C80:'At453C80',
 0x00453D60:'PrepareActionAt453D60',
}
EBP={0x2D0:{71:('0x184','0xa4'),72:('0x184','0xa4'),
             92:('0x188','0xa8'),93:('0x188','0xa8')},
     0x2D1:{71:('0x18c','0xac'),72:('0x18c','0xac'),
             92:('0x190','0xb0'),93:('0x190','0xb0')}}
EXPECTED_REAL_GPR_MISMATCH=60
STORM_STARTS=(8443,9105,9286)
PRECEDING_STORM=(7099,)
SOURCE_302_END=9547


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,relative):
    spec=importlib.util.spec_from_file_location(name,ROOT/relative)
    need(spec is not None and spec.loader is not None,'missing native target checker '+str(relative))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def source_with_radials(source):
    for action in ACTIONS:
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(marker)==1,f'original physical action{action:#x} source marker no longer unique')
        source=source.replace(marker,'#include "FighterFallingRadialsF711.inc"'
                              if action==0x2D0 else '')
    decl='extern float g_ApproachUpperAt006592A4;'
    need(source.count(decl)==1,'original native g_ApproachUpperAt006592A4 declaration missing')
    source=source.replace(decl,decl+'\nextern float g_F711_ReverseRandomAt00659A0C;')
    need(source.count('#include "FighterFallingRadialsF711.inc"')==1
         and source.count('#include "FighterTwinBurstF708.inc"')==1,
         'must include both authentic original 2BF/2C4 and 2D0/2D1 source')
    return source


def compare_native_radials(reader,pe,real,f676,f598,f701,boss,mapped,emitted,refs,*,following_native_2db=False):
    by={x['action']:int(x['handler'],16) for x in mapped}
    reviewed=[]
    for action in ACTIONS:
        lo,hi=PHYSICAL[action]
        next_action=0x2D1 if action==0x2D0 else 0x2DB
        need(by[action]==lo and by[next_action]==hi
             and boss['address']<lo<hi<boss['address']+boss['size']
             and hi-lo==NATIVE_BYTES,
             f'{action:#x}: physical original PE handler boundaries wrong')
        native=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        start=SOURCE_START[action]
        compiled=emitted[start:start+NATIVE_X86]
        need(len(native)==len(compiled)==NATIVE_X86
             and sum(x.size for x in native)==sum(x.size for x in compiled)==NATIVE_BYTES
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(native,compiled))
             and native[-1].mnemonic==compiled[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'{action:#x}: original 416B/120-x86 complete compiled original geometry changed')
        fields=f676.original_fields(native)
        phy=f701.compare_typed_fields(fields,compiled,refs,SYMBOLS,ORIGINAL_FIELDS)
        need(len(phy)==15 and native[0].op_str==compiled[0].op_str
             and native[0].op_str==('0xff0000' if action==0x2D0 else '0xff'),
             f'{action:#x}: original source PE 15 typed COFF fields or storm config changed')
        for i,(original_slot,source_slot) in EBP[action].items():
            need(f'[ebp - {original_slot}]' in native[i].op_str
                 and f'[ebp - {source_slot}]' in compiled[i].op_str
                 and native[i].size==compiled[i].size==6,
                 f'{action:#x} genuine original x87 int scratch x86{i} not attested')
        original_zero={i for i,dest,mn in fields if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),f598.normalized(compiled)))
               if a!=b and i not in original_zero]
        need(len(wrong)==EXPECTED_REAL_GPR_MISMATCH and wrong[0]==5,
             f'{action:#x}: actual source/native GPR/CFG roles changed: {wrong[:8]}')
        # Crucial: native widths/typed refs are now aligned, but the
        # compiler's EBP scratch data uses the wrong SOURCE local owner.
        need(native[71].mnemonic==compiled[71].mnemonic=='mov'
             and native[72].mnemonic==compiled[72].mnemonic=='fild'
             and native[73].mnemonic==compiled[73].mnemonic
             and (native[73].mnemonic==('fadd' if action==0x2D0 else 'fsubr'))
             and native[98].op_str==compiled[98].op_str=='0x7d'
             and native[113].op_str==compiled[113].op_str=='0x7e'
             and native[116].op_str==compiled[116].op_str=='0x1f',
             f'{action:#x}: genuine original random direction/7D+7E shot semantics changed')
        need(emitted[start+NATIVE_X86].mnemonic in ('push','mov'),
             f'{action:#x}: original entire source boundary crosses another action')
        reviewed.append({'action':f'0x{action:03X}',
            'native_physical_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
            'original_complete_action_CODE_bytes':NATIVE_BYTES,
            'new_compiled_COMPLETE_action_CODE_bytes':NATIVE_BYTES,
            'original_and_compiler_x86_instructions':NATIVE_X86,
            'all_original_typed_PE_COFF_refs':len(phy),
            'original_native_wrong_GPR_CFG_positions':len(wrong),
            'actual_original_and_source_integer_x87_EBP_slots':EBP[action],
            'native_internal_case_byte_exact':False})
    need(emitted[SOURCE_START[0x2D0]+NATIVE_X86].mnemonic=='push'
         and emitted[SOURCE_START[0x2D0]+NATIVE_X86].op_str=='0xff',
         'native original full 2D0 must directly lead into true 2D1 storm')
    if following_native_2db:
        j=SOURCE_START[0x2D1]+NATIVE_X86
        need(emitted[j].mnemonic=='mov'
             and emitted[j].op_str=='eax, dword ptr [ebp - 0x28]'
             and emitted[j+1].mnemonic=='movsx'
             and emitted[j+1].op_str=='ecx, word ptr [eax + 0x62]',
             'native original full 2D1 must lead into independently verified real 2DB C++')
    else:
        need(emitted[SOURCE_START[0x2D1]+NATIVE_X86].mnemonic=='mov'
             and emitted[SOURCE_START[0x2D1]+NATIVE_X86].op_str.endswith(', 0x2dc'),
             'native original full 2D1 must lead into the 2DB source placeholder')
    return reviewed


def main():
    f696=load('f711_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f711_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f711_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f711_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f708=load('f711_f708','scripts/verify-fighter-twin-burst-f708.py')
    f672=load('f711_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f711_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f711_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f711_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f711_f598','scripts/verify-fighter-singleton-contact-f598.py')
    rd=load('f711_reader','scripts/compare-coff-function.py')
    acts=load('f711_acts','scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(rd,pe,real,boss)
    source,modules,helpers=f706.source_for_new_combined_parent(
         f696,f699,f701,f672,rd,pe,real,boss,report,mapped)
    source=f708.source_for_genuine_twins(source)
    source=source_with_radials(source)
    obj=f706.compile_whole_parent(source)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-dual.cpp').write_text(source)
    shutil.copyfile(obj,OUT/'Boss00543210-dual.obj')
    otherlog=obj.with_name('compiler.log')
    if otherlog.exists():shutil.copyfile(otherlog,OUT/'compiler.log')
    code,refs=rd.object_function(obj,f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ')
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    dual=compare_native_radials(rd,pe,real,f676,f598,f701,boss,mapped,emitted,refs)
    twins=f708.check_native_cases(f701,f676,f598,rd,pe,real,boss,mapped,emitted,refs)
    originals,start=f706.native_cases_and_compiled_start(
         f672,rd,pe,real,boss,mapped,emitted,refs)
    five,end=f706.verify_five_native_cases(f672,f598,f701,originals,emitted,refs,start)
    need(end==6623,'original real preceding 259-25D physical source interval changed')
    later,source302end=f706.check_later_native_physical(
        f701,f696,f699,f676,f681,f684,f598,rd,pe,real,boss,mapped,
        emitted,refs,expected_storm_starts=STORM_STARTS,
        preceding_storm_starts=PRECEDING_STORM)
    need(source302end==SOURCE_302_END,
         'restoring real 2D0/2D1 broke original 302 935-byte source whole-case boundary')
    old=f696.verify_prior_parent_context(
        rd,pe,real,boss,report,mapped,code,refs,modules,helpers,
        expected_receiver_uses=2781,following_native_2fa=True,
        source_receiver_slot='0x28',source_scratch_slot='0x40',
        source_scratch_shift=32,source_f684_slot_shift=108,
        source_native_302_end_ordinal=source302end,
        source_2ef_expected_GPR_mismatches=144,
        source_2f0_2f1_expected_GPR_counts={0x2F0:(175,0),0x2F1:(170,0)},
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=end,
        following_native_2bf=True,source_storm_bytes=928,
        source_storm_width_differences=f706.SOURCE_STORM_WIDTHS)
    need(old['actual_source_context_nonterminal_strict_case_count']==26
         and old['original_2ef_real_GPR_regression']==144
         and old['original_after_RET_switch_DATA_rechecked_on_this_source']
         and old['original_2f0_2f1_real_GPR_mismatches']==[175,170]
         and old['prior_2f9_nonfield_GPR_mismatches']==236
         and old['prior_terminal_31b_real_gpr_negative']==43,
         'prior original giant native strict contexts or physical 943-byte afterRET DATA changed')
    summary={'original_whole_boss':'0x00543210',
             'original_whole_CODE_BYTES_NonExact':boss['size'],
             'original_independently_owned_afterRET_DATA_B':boss['postret_size'],
             'new_complete_native_2D0_2D1_handlers':dual,
             'both_original_game_action_CODE_B_not_credited':832,
             'both_native_x86_mnemonic_and_width_positions':240,
             'both_original_zero_addend_PE_COFF_fields':30,
             'eight_actual_natural_Cpp_compiler_forms_including_baseline':8,
             'previous_twin_native_actions':twins,
             'previous_five_259_25D_actions':five,
             'previous_2F8_2F9_2FA_2FB_302_contexts':later,
             'previous_27_strict_native_nonterminal_actions_and_full_afterRET_data':old,
             'whole_function_byte_exact':False,
             'new_accepted_whole_game_function_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F711 full native original fighter 00543210: complete source-backed '
          '2D0/2D1 falling radial 416B/120 x86/15 genuine typed original PE/COFF '
          'fields each. All 240 original mnemonic+width positions and all 30 '
          'physical references line up in freshly compiled whole parent; actual '
          'GPR/CFG and EBP real scratch owners still nonexact. Prior 2BF/2C4, '
          '259-25D, 2F8-302, 26 context-strict earlier game action interiors, prior 2EF now 144 genuine GPR regressions and '
          'full 943-byte afterRET original DATA rechecked. Giant still NONEXACT, '
          'zero accepted whole function CODE, no full 943-unit replay.')


if __name__=='__main__':
    main()
