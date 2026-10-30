#!/usr/bin/env python3
"""F722: real original 2BF->2C0->2C1->2C4 native fighter action order.

Cold-build ONE full original-shaped VC7.1 giant with actual native
2C0/2C1 source inserted BETWEEN genuine previously reconstructed
2BF/2C4, then reattest all genuine whole original case boundaries,
41 true typed PE/COFF fields, actual nonexact source x87 and EBP,
all prior native source cases, 27 strict contextual interiors and
complete independent 943B afterRET switch DATA. No case FUNCTION
exact credit or 943-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f722-fighter-early-pair'
BOSS=0x00543210
NATIVE_ACTIONS={0x2C0:(0x0054D64D,0x0054D93E,753,218,21),
                0x2C1:(0x0054D93E,0x0054DC0E,720,214,20)}
ORIGINAL_CPP_ORDER=(0x2BF,0x2C0,0x2C1,0x2C4)
CPP_START={0x2BF:6831,0x2C0:6962,0x2C1:7180,0x2C4:7394}
STORM_PRIOR=(7527,8059,8228,8417,8606,8775)
STORM_LATE=(10090,10752,10933)
CPP_302_END=11194
CPP_SOURCE_RECEIVER_MOV_USES=3247
CPP_SCRATCH_SHIFT=12
ORIGINAL_X87_STACK={
 0x2C0:{114:('0x160','0x98'),115:('0x160','0x98'),
        176:('0x164','0x9c'),177:('0x164','0x9c')},
 0x2C1:{136:('0x168','0xa0'),137:('0x168','0xa0')},
}
ORIGINAL_TARGET_SYMS={
 0x00453E20:('ResetAt453E20',),
 0x0065782C:('g_ThresholdAt0065782C',),
 0x00659090:('g_F718_FallingDragAt00659090',),
 0x00657CF8:('g_F718_BounceMinAt00657CF8',),
 0x0040FB40:('SetAuxActionAt40FB40',),
 0x0040FA30:('GetNativeActionAt40FA30',),
 0x0040FAC0:('SetNativeActionAt40FAC0',),
 0x00657888:('g_ContactProjectionAt00657888',),
 0x00453E80:('InitTrajectoryAt453E80',),
 0x00453D60:('PrepareActionAt453D60',),
 0x0065826C:('g_F722_BurstYAt0065826C',),
 0x00453C80:('SpawnAt453C80','SpawnMixedAt453C80','SpawnRawXYAt453C80'),
 0x00453D40:('PrepareActionAt453D40',),
 0x0046D000:('StartAnimationAt46D000',),
 0x00657868:('g_F714_ShotYAt00657868',),
 0x00453A70:('SpawnFloatXYAt453A70','SpawnDirectedAt453A70'),
 0x00453E60:('InitTrajectoryAt453E60',),
 0x00659A10:('g_F722_LowYAt00659A10',),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing PE/COFF original-source verifier '+str(path))
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def native_order_source(src):
    """Insert original true 2C0/2C1 between original 2BF and 2C4.

    Existing F708 source contains genuine distinct full 2BF and 2C4
    cases in one include. Its relative C++ ordering originally skipped
    physical 2C0/2C1 placeholders; only the NEW combined source is
    split into actual physical original control-flow order. Older
    canonical F708 source remains unchanged and independently verified.
    """
    f708=(ROOT/'probes/FighterTwinBurstF708.inc').read_text()
    a=f708.index('        case 0x2BF: {')
    b=f708.index('        case 0x2C4: {',a)
    first,second=f708[a:b],f708[b:]
    need(first.count('case 0x2BF:')==1 and second.count('case 0x2C4:')==1,
         'authentic original 2BF and 2C4 source cases not independently preserved')
    include='#include "FighterTwinBurstF708.inc"'
    need(src.count(include)==1,'original source F708 native twin source include missing')
    src=src.replace(include,first+'\n#include "FighterEarlyPairF722.inc"\n'+second)
    for action in (0x2C0,0x2C1):
        placeholder=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(placeholder)==1,f'original case {action:#x} dummy marker missing')
        src=src.replace(placeholder,'')
    needle='extern float g_F718_BounceMinAt00657CF8;'
    need(src.count(needle)==1,'original native float 00657CF8 global declaration changed')
    src=src.replace(needle,needle+'\nextern float g_F722_BurstYAt0065826C;\n'
                    'extern float g_F722_LowYAt00659A10;')
    need(src.count('#include "FighterEarlyPairF722.inc"')==1
         and all(src.count('case 0x'+format(a,'X')+':')==1 for a in (0x2BF,0x2C4)),
         'all original 2BF->2C0->2C1->2C4 meaningful case source orders required')
    return src


def physical_fields(native_fields,generated,refs,source_symbols=None):
    names=ORIGINAL_TARGET_SYMS if source_symbols is None else source_symbols
    fields=[r for r in refs if generated[0].address<=r['offset']<generated[-1].address+generated[-1].size]
    need(len(native_fields)==len(fields),'original PE/COFF native/source physical field count changed')
    for (ordinal,original_target,mnemonic),ref in zip(native_fields,fields):
        need(original_target in names
             and any(name in ref['symbol'] for name in names[original_target])
             and ref['type']==('REL32' if mnemonic=='call' else 'DIR32')
             and ref['addend']==0 and ref['local_symbol_offset'] is None,
             f'original physical PE target {original_target:#x} native x86{ordinal}: wrong typed original source symbol')
        owner=[i for i,x in enumerate(generated)
               if x.address<=ref['offset']<x.address+x.size]
        need(owner==[ordinal]
             and generated[ordinal].mnemonic==mnemonic,
             f'original physical native target {original_target:#x} is not owned by original x86{ordinal} instruction')
    return fields


def verify_new_cases(reader,pe,real,f676,f598,boss,mapped,emitted,refs,*,
                     following_native_2c5=False):
    by={x['action']:int(x['handler'],16) for x in mapped}
    report=[]
    for action in (0x2C0,0x2C1):
        lo,hi,size,nx,nfields=NATIVE_ACTIONS[action]
        need(by[action]==lo and by[0x2C1 if action==0x2C0 else 0x2C4]==hi
             and hi-lo==size and boss['address']<lo<hi<boss['address']+boss['size'],
             f'actual original game physical native {action:#x} 753/720 CODE bounds changed')
        native=list(real.disasm(reader.pe_bytes_at(pe,lo,size),lo))
        start=CPP_START[action]
        compiled=emitted[start:start+nx]
        need(len(native)==len(compiled)==nx
             and sum(x.size for x in native)==sum(x.size for x in compiled)==size
             and native[-1].mnemonic==compiled[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2'
             and all(a.size==b.size for a,b in zip(native,compiled)),
             f'original {action:#x} complete native/source original x86 width/exit differs')
        nf=f676.original_fields(native)
        fields=physical_fields(nf,compiled,refs)
        need(len(fields)==nfields,f'original {action:#x} physical original typed PE/COFF fields differ')
        mn=[(i,a.mnemonic,b.mnemonic) for i,(a,b) in enumerate(zip(native,compiled))
            if a.mnemonic!=b.mnemonic]
        need(mn==([(117,'fsubr','fadd')] if action==0x2C0 else []),
             f'original whole {action:#x} x87 instruction order differs: {mn}')
        if action==0x2C0:
            need(native[113].op_str=='edx, edx, 0x2e'
                 and compiled[113].op_str=='edx, edx, -0x2e'
                 and native[117].op_str==compiled[117].op_str=='dword ptr [eax + 0x44]',
                 'native 2C0 original positive IMUL/FSUBR differs from algebraic negative source FADD')
        else:
            need(native[142].op_str==compiled[142].op_str=='0x32a'
                 and native[153].op_str==compiled[153].op_str=='0x340'
                 and native[156].op_str==compiled[156].op_str=='0x1f4',
                 'original 2C1 full native projectile/animation sequence changed')
        absfields={i for i,target,mn in nf if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(compiled)))
               if a!=b and i not in absfields]
        need(wrong==([113,117] if action==0x2C0 else []),
             f'original {action:#x} genuine normalized GPR/x87 roles changed: {wrong[:8]}')
        for i,(original_slot,source_slot) in ORIGINAL_X87_STACK[action].items():
            a,b=native[i],compiled[i]
            need(a.size==b.size==6 and a.mnemonic==b.mnemonic
                 and f'[ebp - {original_slot}]' in a.op_str
                 and f'[ebp - {source_slot}]' in b.op_str,
                 f'original {action:#x} genuine six-byte EBP temp at native x86{i} changed')
        report.append({'native_action':f'0x{action:X}',
            'original_entire_physical_PE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
            'original_entire_CODE_bytes':size,'source_entire_CODE_bytes':sum(x.size for x in compiled),
            'original_native_and_compiler_x86':nx,
            'all_original_physical_typed_PE_COFF_fields':len(fields),
            'real_native_mnemonic_differences':mn,
            'real_normalized_nonfield_GPR_CFG_differences':wrong,
            'source_wrong_EBP_scratch_owners':ORIGINAL_X87_STACK[action],
            'whole_original_game_FUNCTION_exact':False})
    for a,next_a in zip(ORIGINAL_CPP_ORDER,ORIGINAL_CPP_ORDER[1:]):
        nx=131 if a in (0x2BF,0x2C4) else NATIVE_ACTIONS[a][3]
        need(emitted[CPP_START[a]+nx].address==emitted[CPP_START[next_a]].address,
             'original 2BF->2C0->2C1->2C4 source must remain physically contiguous in native order')
    after=CPP_START[0x2C4]+131
    if following_native_2c5:
        need(emitted[after].mnemonic=='mov'
             and emitted[after].op_str=='ecx, dword ptr [ebp - 0x28]'
             and emitted[after+1].op_str=='edx, word ptr [ecx + 0x62]'
             and [x.mnemonic for x in emitted[after+239:after+242]]==['push']*3,
             'source original 2C4 must lead into whole authentic 2C5, then 2D0 storm')
    else:
        need(emitted[after].mnemonic=='mov'
             and emitted[after].op_str.endswith(', 0x2c6')
             and [x.mnemonic for x in emitted[7527:7530]]==['push','push','push'],
             'original full 2C4 must lead to former 2C5 placeholder then true 2D0')
    return report


def main():
    f696=load('f722_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f722_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f722_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f722_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f708=load('f722_f708','scripts/verify-fighter-twin-burst-f708.py')
    f711=load('f722_f711','scripts/verify-fighter-falling-radials-f711.py')
    f714=load('f722_f714','scripts/verify-fighter-complex-movement-f714-f715.py')
    f718=load('f722_f718','scripts/verify-fighter-double-volley-f718.py')
    f720=load('f722_f720','scripts/verify-fighter-late-storm-f720-f721.py')
    f672=load('f722_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f722_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f722_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f722_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f722_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f722_reader','scripts/compare-coff-function.py')
    acts=load('f722_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    src,modules,helpers=f714.combine_source(f706,f708,f711,f696,f699,f701,f672,
                                             reader,pe,real,boss,report,mapped)
    src=f718.source_with_double_volley(src)
    src=f720.source_with_both(src)
    src=native_order_source(src)
    obj=f706.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-native-order.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-native-order.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler-native-order.log')
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ')
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    new=verify_new_cases(reader,pe,real,f676,f598,boss,mapped,emitted,refs)
    previous_twins=f708.check_native_cases(f701,f676,f598,reader,pe,real,boss,mapped,
                          emitted,refs,source_starts={0x2BF:6831,0x2C4:7394},
                          source_ebp_shift_by_action={0x2BF:0,0x2C4:CPP_SCRATCH_SHIFT},
                          source_expected_GPR={0x2BF:(2,39),0x2C4:(2,39)})
    previous_radials=f711.compare_native_radials(reader,pe,real,f676,f598,f701,
                          boss,mapped,emitted,refs,following_native_2db=True,
                          source_starts={0x2D0:7527,0x2D1:7647},source_ebp_shift=CPP_SCRATCH_SHIFT,
                          source_next_2db_registers=('edx','eax'))
    previous_movement=f714.audit_cases(f701,f676,f598,f699,reader,pe,real,boss,mapped,
                          emitted,refs,following_native_2dd=True,
                          source_starts={0x2DB:7767,0x2DC:8059},source_ebp_shift=CPP_SCRATCH_SHIFT,
                          source_expected_GPR={0x2DB:(235,0),0x2DC:(80,5)})
    previous_double=f718.verify_two_native_actions(f701,f676,f598,reader,pe,real,boss,mapped,
                          emitted,refs,following_native_2df=True,
                          source_starts={0x2DD:8228,0x2DE:8417},source_ebp_shift=CPP_SCRATCH_SHIFT,
                          source_expected_GPR={0x2DD:0,0x2DE:0})
    previous_late=f720.prove_both(f701,f714,f676,f598,reader,pe,real,boss,mapped,
                          emitted,refs,source_starts={0x2DF:8606,0x2E5:8775},
                          source_after_2e5=8998,source_ebp_shift=CPP_SCRATCH_SHIFT)
    oldcases,first=f706.native_cases_and_compiled_start(f672,reader,pe,real,boss,mapped,emitted,refs)
    oldfive,end=f706.verify_five_native_cases(f672,f598,f701,oldcases,emitted,refs,first)
    need(end==6623,'prior actual original 259-25D C++ cases regressed in native ordered source')
    later,source302end=f706.check_later_native_physical(
           f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,
           emitted,refs,expected_storm_starts=STORM_LATE,
           preceding_storm_starts=STORM_PRIOR)
    need(source302end==CPP_302_END,
         'original late fighter 302 935-B case and actual following 31B boundary changed')
    original_context=f696.verify_prior_parent_context(
        reader,pe,real,boss,report,mapped,code,refs,modules,helpers,
        expected_receiver_uses=CPP_SOURCE_RECEIVER_MOV_USES,following_native_2fa=True,
        source_receiver_slot='0x28',source_scratch_slot='0x40',
        source_scratch_shift=32,source_f684_slot_shift=172,
        source_native_302_end_ordinal=source302end,
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=end,
        following_native_2bf=True,source_storm_bytes=928,
        source_storm_width_differences=f706.SOURCE_STORM_WIDTHS,
        source_2f0_2f1_expected_GPR_counts={0x2F0:(147,39),0x2F1:(170,0)},
        source_native_2e5_end_ordinal=8998)
    need(original_context['previous_27_nonterminal_context_strict_original_cases_rechecked']
         and original_context['actual_source_context_nonterminal_strict_case_count']==27
         and original_context['original_2ef_real_GPR_regression']==0
         and original_context['original_2f0_2f1_real_GPR_mismatches']==[147,170]
         and original_context['original_after_RET_switch_DATA_rechecked_on_this_source'],
         'real physical 2C0/2C1 insertion unexpectedly broke previous strict cases or entire 943B switch DATA')
    receipt={
       'pinned_original':'Japanese TH075 v1.11',
       'original_whole_giant_fighter':'0x00543210',
       'original_whole_giant_CODE_bytes_still_NONEXACT':boss['size'],
       'original_separate_afterRET_switch_DATA_bytes':boss['postret_size'],
       'restored_true_original_action_order':list(map(lambda a:f'0x{a:X}',ORIGINAL_CPP_ORDER)),
       'new_complete_native_original_source_actions':new,
       'new_source_backed_native_internal_CODE_bytes_NOT_CREDITED':1473,
       'all_original_native_new_x86_positions':432,
       'new_original_native_typed_PE_COFF_fields':41,
       'prior_physically_ordered_twin_bursts':previous_twins,
       'prior_original_2D0_2D1':previous_radials,
       'prior_original_2DB_2DC':previous_movement,
       'prior_original_2DD_2DE':previous_double,
       'prior_original_2DF_2E5':previous_late,
       'prior_original_259_25D':oldfive,
       'prior_original_2F8_through_302':later,
       'all_prior_27_context_strict_2EF_and_943B_afterRET_native':original_context,
       'whole_original_game_function_exact':False,
       'new_accepted_complete_GAME_function_CODE_bytes':0,
    }
    (OUT/'native-order-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F722 full original 00543210 C++ reorders genuine 2BF->2C0->2C1->2C4 '
          'to native physical sequence; 2C0 source 753B/218 x86/21 typed native PE refs '
          'with one true original FSUBR vs source FADD and IMUL ±46 difference, '
          '2C1 720B/214 x86/20 typed native PE refs and ZERO normalized '
          'GPR/CFG differences. All 432 native x86 instruction widths, 431/432 native mnemonic positions '
          'and 41 original physical zero-addend fields attested, EBP x87 scratch '
          'remains wrong. One newly compiled giant also rechecks all previous '
          'original contexts and 27 strict internal cases incl 2EF, full '
          '943B afterRET original DATA. Whole authored giant NONEXACT, zero '
          'accepted independent whole-function CODE, no full cold replay.')


if __name__=='__main__':
    main()
