#!/usr/bin/env python3
"""F708: two real 452-byte native fighter burst cases in one whole parent.

Cold build only original-shaped 00543210 C++ source, with all recovered
259-25D, 2BF/2C4 and 2F8-302 action logic together. Re-read full native
2BF/2C4 physical 131-x86/452-B/16-field extents, real x87 order,
authentic IMUL sign and EBP negatives, and earlier strict cases plus all
943 separate afterRET DATA. NEVER accept separate cases as whole exact.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
from pathlib import Path
import re
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f708-fighter-twin-burst-native'
ACTOR=0x00543210
CASES=(0x2BF,0x2C4)
NATIVE_CODE=452
NATIVE_X86=131
ORIGINAL_FIELD_ORDINALS={
 0x2BF:(13,16,21,24,27,34,48,63,65,73,88,102,109,123,126,129),
 0x2C4:(13,16,21,24,27,34,48,63,65,73,84,91,105,112,126,129),
}
SYMBOLS={
 0x00453E20:'ResetAt453E20',
 0x00657888:'g_ContactProjectionAt00657888',
 0x00453E80:'InitTrajectoryAt453E80',
 0x00453D60:'PrepareActionAt453D60',
 0x00453D40:'PrepareActionAt453D40',
 0x00659238:'g_BurstXAt00659238',
 0x00453C80:'SpawnAt453C80',
 0x00453B50:'SpawnSevenAt453B50',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x006591EC:'g_BarrageY1At006591EC',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0046D000:'StartAnimationAt46D000',
}
ACTUAL_SOURCE_STARTS={0x2BF:6831,0x2C4:6962}
EBP_SCRATCH={
 0x2BF:{40:('0x154','0x8c'),41:('0x154','0x8c'),
         94:('0x158','0x90'),95:('0x158','0x90'),
        115:('0x15c','0x94'),116:('0x15c','0x94')},
 0x2C4:{40:('0x16c','0x98'),41:('0x16c','0x98'),
         97:('0x170','0x9c'),98:('0x170','0x9c'),
        118:('0x174','0xa0'),119:('0x174','0xa0')},
}
SOURCE_GPR_NEGATIVES={0x2BF:2,0x2C4:66}
SOURCE_ORIGINAL_RECEIVER_RELOADS=2714
SOURCE_STORM_STARTS=(8207,8869,9050)


def need(test,msg):
    if not test:raise ValueError(msg)


def load(name,relative):
    s=importlib.util.spec_from_file_location(name,ROOT/relative)
    need(s is not None and s.loader is not None,'missing original-source verifier '+str(relative))
    m=importlib.util.module_from_spec(s)
    sys.modules[name]=m
    s.loader.exec_module(m)
    return m


def source_for_genuine_twins(source):
    """One actual C++ body for each physical case, no duplicate symbols."""
    for action in CASES:
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(marker)==1,f'original physical case {action:#x} marker absent')
        source=source.replace(marker,
          '#include "FighterTwinBurstF708.inc"' if action==0x2BF else '')
    method='void SpawnMixedAt453C80(int,int,float,char,int);'
    need(source.count(method)==1,'borrowed 453C80 actual source signature changed')
    source=source.replace(method,
        method+' void SpawnSevenAt453B50(int,int,int,char,int,int,int);')
    need(source.count('#include "FighterTwinBurstF708.inc"')==1
         and source.count('void SpawnSevenAt453B50(int,int,int,char,int,int,int);')==1,
         'two original burst cases need single normal source include and full game-call ABI')
    return source


def check_native_cases(f701,f676,f598,reader,pe,real,boss,mapped,emitted,refs,*,source_starts=None,
                       source_ebp_shift_by_action=None,source_expected_GPR=None):
    starts=ACTUAL_SOURCE_STARTS if source_starts is None else source_starts
    need(all(k in starts for k in CASES),'native 2BF/2C4 source starts must both be attested')
    by={x['action']:int(x['handler'],16) for x in mapped}
    candidates=[]
    for ref in refs:
        if 'SpawnSevenAt453B50' not in ref['symbol'] or ref['type']!='REL32':continue
        ordinal=next((i for i,x in enumerate(emitted)
                      if x.address<=ref['offset']<x.address+x.size),None)
        if ordinal is None or ordinal<63:continue
        start=ordinal-63
        if (emitted[start].mnemonic=='mov' and emitted[start+46].mnemonic=='push'
           and emitted[start+46].op_str in ('0x73','0x74')):
            candidates.append((emitted[start+46].op_str,start))
    need(sorted(candidates)==[('0x73',starts[0x2BF]),
                              ('0x74',starts[0x2C4])],
         f'actual original source typed 453B50 whole case-anchors changed: {candidates}')
    results=[]
    for action in CASES:
        start=starts[action]
        lo=by[action]
        hi=by[0x2C0 if action==0x2BF else 0x2C5]
        need(hi-lo==NATIVE_CODE and (lo,hi)==({
             0x2BF:(0x54D489,0x54D64D),0x2C4:(0x54DC0E,0x54DDD2)}[action]),
             f'original whole physical {action:#x} native PE bound no longer confirmed')
        native=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        candidate=emitted[start:start+NATIVE_X86]
        need(len(native)==len(candidate)==NATIVE_X86
             and sum(x.size for x in candidate)==NATIVE_CODE
             and native[-1].mnemonic==candidate[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'complete original native {action:#x} 452-B/131-x86 not preserved')
        nf=f676.original_fields(native)
        fields=f701.compare_typed_fields(nf,candidate,refs,SYMBOLS,
                                       ORIGINAL_FIELD_ORDINALS[action])
        need(len(fields)==16,f'actual 16 original physical {action:#x} typed fields missing')
        # Real source `float(direction * -20)+X` evaluates the signed
        # direction before X and recreates 130/131 native mnemonics,
        # but native IMUL +0x14 and FSUBR differ from source -0x14/FADD.
        wrong_mn=[(i,a.mnemonic,b.mnemonic) for i,(a,b) in enumerate(zip(native,candidate))
                  if a.mnemonic!=b.mnemonic]
        need(wrong_mn==[(43,'fsubr','fadd')]
             and all(a.size==b.size for a,b in zip(native,candidate))
             and native[39].op_str.endswith(', 0x14')
             and candidate[39].op_str.endswith(', -0x14')
             and native[41].mnemonic==candidate[41].mnemonic=='fild'
             and native[43].mnemonic=='fsubr' and candidate[43].mnemonic=='fadd',
             f'authentic {action:#x} 130/131 opcode x87/source IMUL negative changed')
        for ordinal,(native_slot,source_slot) in EBP_SCRATCH[action].items():
            extra=(source_ebp_shift_by_action or {}).get(action,0)
            source_slot=f"0x{int(source_slot,16)+extra:x}"
            need(f'[ebp - {native_slot}]' in native[ordinal].op_str
                 and f'[ebp - {source_slot}]' in candidate[ordinal].op_str
                 and native[ordinal].size==candidate[ordinal].size==6,
                 f'native {action:#x} original x86{ordinal} genuine six-byte scratch offset not checked')
        norm_native=f598.normalized(native)
        norm_source=f598.normalized(candidate)
        typed_direct={i for i,target,mn in nf if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(norm_native,norm_source))
               if a!=b and i not in typed_direct]
        expected=(source_expected_GPR or {}).get(action,
                    (SOURCE_GPR_NEGATIVES[action],39 if action==0x2BF else 0))
        need(len(wrong)==expected[0] and wrong[0]==expected[1],
             f'genuine {action:#x} GPR/CFG source roles changed: {wrong[:10]}')
        need(candidate[46].op_str==('0x73' if action==0x2BF else '0x74')
             and candidate[61].op_str=='0x334'
             and candidate[63].mnemonic=='call'
             and candidate[63].op_str.startswith('0x')
             and candidate[130].op_str==emitted[starts[0x2BF]+130].op_str,
             f'original complete {action:#x} 73/74 and 334 shots/shared exit changed')
        if action==0x2BF:
            need([candidate[i].op_str for i in (100,121,124,127)]
                 ==['0x328','0x33c','0x1f4','0xa'],
                 'original native 2BF shot ordering/action changed')
        else:
            need([candidate[i].op_str for i in (82,103,124,127)]
                 ==['0x2ee','0x32b','0x33d','0xe'],
                 'original native 2C4 2EE-before-shots original action grammar changed')
        results.append({'original_native_action':f'0x{action:X}',
             'original_physical_PE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
             'entire_original_native_CODE_bytes':NATIVE_CODE,
             'new_source_CODE_bytes':sum(x.size for x in candidate),
             'entire_original_and_source_x86_instructions':NATIVE_X86,
             'source_same_native_mnemonics':NATIVE_X86-len(wrong_mn),
             'all_physical_original_typed_PE_COFF_fields':len(fields),
             'genuine_original_wrong_nonfield_GPR_x87_positions':len(wrong),
             'real_original_native_EBP_scratch_offsets':EBP_SCRATCH[action],
             'whole_original_game_function_EXACT':False})
    need(emitted[starts[0x2BF]+NATIVE_X86].mnemonic=='mov'
         and emitted[starts[0x2C4]+NATIVE_X86].mnemonic=='mov',
         'both original 131-x86 full native bodies must include original following action boundary')
    return results


def main():
    f696=load('f708_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f708_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f708_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f708_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f672=load('f708_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f708_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f708_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f708_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f708_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f708_reader','scripts/compare-coff-function.py')
    acts=load('f708_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    original_source,prior_deps,prior_helpers=f706.source_for_new_combined_parent(
         f696,f699,f701,f672,reader,pe,real,boss,report,mapped)
    source=source_for_genuine_twins(original_source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-two-bursts.cpp'
    cpp.write_text(source)
    obj=f706.compile_whole_parent(source)
    # Preserve the selected build in the F708 research directory as well;
    # F706's shared compiler helper uses its own ignored output path.
    shutil.copyfile(obj,OUT/'Boss00543210-two-bursts.obj')
    buildlog=obj.with_name('compiler.log')
    if buildlog.exists():
        shutil.copyfile(buildlog,OUT/'compiler.log')
    code,refs=reader.object_function(obj,
        f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    twins=check_native_cases(f701,f676,f598,reader,pe,real,boss,mapped,emitted,refs)
    originals,first=f706.native_cases_and_compiled_start(
         f672,reader,pe,real,boss,mapped,emitted,refs)
    five,end=f706.verify_five_native_cases(f672,f598,f701,originals,emitted,refs,first)
    need(end==6623,'native 259-25D source full five body bounds changed')
    later,source302end=f706.check_later_native_physical(
        f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,
        emitted,refs,expected_storm_starts=SOURCE_STORM_STARTS)
    need(source302end==9311,'full original 302 new entire source end moved')
    context=f696.verify_prior_parent_context(
        reader,pe,real,boss,report,mapped,code,refs,prior_deps,prior_helpers,
        expected_receiver_uses=SOURCE_ORIGINAL_RECEIVER_RELOADS+1,
        following_native_2fa=True,source_receiver_slot='0x28',
        source_scratch_slot='0x40',source_scratch_shift=32,
        source_f684_slot_shift=92,source_native_302_end_ordinal=source302end,
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=end,
        following_native_2bf=True,source_storm_bytes=928,
        source_storm_width_differences=f706.SOURCE_STORM_WIDTHS)
    need(context['previous_27_nonterminal_context_strict_original_cases_rechecked']
         and context['original_after_RET_switch_DATA_rechecked_on_this_source']
         and context['prior_2f9_nonfield_GPR_mismatches']==236,
         'genuine all earlier source/native previous strict and afterRET DATA regressed')
    receipt={
       'original_native_whole_boss':'0x00543210',
       'whole_original_CODE_bytes_UNMATCHED':boss['size'],
       'separate_native_afterRET_switch_DATA_bytes':boss['postret_size'],
       'genuine_twin_burst_original_native_actions':twins,
       'two_new_real_original_internal_CODE_bytes_not_credited':NATIVE_CODE*2,
       'two_recovered_x86_source_positions':NATIVE_X86*2,
       'two_original_physical_PE_COFF_fields':32,
       'prior_five_259_25D_actions_still_nonstrict':five,
       'prior_later_2F8_through_302_contexts_still_nonstrict':later,
       'prior_27_strict_nonterminal_cases_and_entire_original_afterRET':context,
       'whole_game_FUNCTION_exact':False,
       'new_accepted_whole_game_function_CODE_bytes':0,
    }
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F708 original entire 00543210 native 2BF/2C4: two complete 452/452-B, '
          '131/131-x86 burst cases, 16+16 genuine typed PE/COFF fields. '
          'Native signed-X negative-direction expression recovers both '
          '130/131 source mnemonics and all original x86 start/width roles; '
          'real FSUBR/FADD, signed IMUL and EBP source slots still NONEXACT. '
          'Same full parent verifies five 259-25D cases, prior 2F8-302, '
          '27 previous context-strict original internal game cases and all '
          '943 independently owned original afterRET DATA bytes. '
          '0 new exact whole functions, no mass 943-unit cold replay.')


if __name__=='__main__':
    main()
