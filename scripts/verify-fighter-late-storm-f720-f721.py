#!/usr/bin/env python3
"""F720/F721: whole native 2DF/2E5 original C++ in a complete fighter boss.

One fresh VC7.1 full original-shaped 00543210 parent; verify original
602/798 CODE B, 169/223 x86 and 18/20 physically typed PE/COFF
fields, original TEST AH,5 and FUCOMPP, exact ordered GPR/CFG roles
except real original-versus-source EBP owner. The reconstructed 2E5
naturally restores ORIGINAL 2EF strict internal context (no 144 GPR
mismatches): independently recheck all preceding original cases,
nonexact controls and the entire original afterRET 943B DATA.
No separate inner case credit, no full 943-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f720-fighter-late-storm'
ACTOR=0x00543210
ACTIONS=(0x2DF,0x2E5)
NATIVE={0x2DF:(0x0054EFE7,0x0054F241,602,169,18),
        0x2E5:(0x0054F241,0x0054F55F,798,223,20)}
SOURCE_START={0x2DF:8178,0x2E5:8347}
SOURCE_TRUE_AFTER_2E5=8570
SOURCE_STORMS_PRIOR=(7099,7631,7800,7989,8178,8347)
SOURCE_STORMS_LATER=(9662,10324,10505)
SOURCE_TRUE_302_END=10766
SOURCE_SAVED_THIS_MOV_USES=3119
ORIGINAL_X87_STACK={
 0x2DF:{76:('0x1ac','0xcc'),77:('0x1ac','0xcc'),
        100:('0x1b0','0xd0'),101:('0x1b0','0xd0')},
 0x2E5:{106:('0x1b4','0xd4'),107:('0x1b4','0xd4'),
        122:('0x1b8','0xd8'),123:('0x1b8','0xd8'),
        165:('0x1bc','0xdc'),166:('0x1bc','0xdc'),
        185:('0x1c0','0xe0'),186:('0x1c0','0xe0'),
        210:('0x1c4','0xe4'),211:('0x1c4','0xe4')},
}
ORIGINAL_2E5_SYMBOLS={
 0x00454BC0:'ConfigureStormAt454BC0',
 0x00453E20:'ResetAt453E20',
 0x00453B50:'SpawnSevenAt453B50',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00455580:'RandomBoundaryAt455580',
 0x006714D0:'g_CloudOpponentAt006714D0',
 0x00453D40:'PrepareActionAt453D40',
 0x0065782C:'g_ThresholdAt0065782C',
 0x006591EC:'g_BarrageY1At006591EC',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0040FB40:'SetAuxActionAt40FB40',
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing native source verifier '+path)
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def source_with_both(src):
    for action,filename in ((0x2DF,'FighterLateStormF720.inc'),
                            (0x2E5,'FighterRandomVolleyF721.inc')):
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(marker)==1,f'original native {action:#x} source placeholder missing')
        src=src.replace(marker,'#include "'+filename+'"')
        need(src.count('#include "'+filename+'"')==1,
             f'complete normal original {action:#x} handler must be represented in whole source')
    return src


def prove_both(f701,f714,f676,f598,reader,pe,real,boss,mapped,ins,refs,*,
               source_starts=None,source_ebp_shift=0,source_after_2e5=None):
    starts=SOURCE_START if source_starts is None else source_starts
    after_2e5=SOURCE_TRUE_AFTER_2E5 if source_after_2e5 is None else source_after_2e5
    need(all(action in starts for action in ACTIONS),'real original 2DF/2E5 source starts absent')
    by={x['action']:int(x['handler'],16) for x in mapped}
    result=[]
    for action in ACTIONS:
        lo,hi,size,nx,nfields=NATIVE[action]
        next_action=0x2E5 if action==0x2DF else 0x2EF
        need(by[action]==lo and by[next_action]==hi
             and hi-lo==size and boss['address']<lo<hi<boss['address']+boss['size'],
             f'{action:#x}: original complete physical original handler bounds incorrect')
        original=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        start=starts[action]
        generated=ins[start:start+nx]
        need(len(original)==len(generated)==nx
             and sum(x.size for x in original)==sum(x.size for x in generated)==size
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(original,generated))
             and original[-1].mnemonic==generated[-1].mnemonic=='jmp'
             and original[-1].op_str=='0x5515c2',
             f'original {action:#x} complete source-backed x86 mnemonic/width geometry changed')
        orig_fields=f676.original_fields(original)
        symbols=f714.F714_GLOBAL_SYMBOLS if action==0x2DF else ORIGINAL_2E5_SYMBOLS
        physical=f701.compare_typed_fields(orig_fields,generated,refs,symbols,
                              tuple(i for i,_,_ in orig_fields))
        need(len(physical)==len(orig_fields)==nfields,
             f'{action:#x}: all original physical zero-addend PE/COFF fields not preserved')
        # Original pure-GPR role identity is genuine, but saving `this`
        # at its compiler slot is a separate true EBP mismatch.
        absolute={i for i,t,m in orig_fields if m!='call'}
        bad=[i for i,(a,b) in enumerate(zip(f598.normalized(original),
                                            f598.normalized(generated)))
             if a!=b and i not in absolute]
        need(not bad,f'{action:#x} original nonfield source register/CFG phase not actually restored: {bad[:8]}')
        for i,(original_slot,source_slot) in ORIGINAL_X87_STACK[action].items():
            source_slot=f"0x{int(source_slot,16)+source_ebp_shift:x}"
            a,b=original[i],generated[i]
            need(a.mnemonic==b.mnemonic and a.size==b.size==6
                 and f'[ebp - {original_slot}]' in a.op_str
                 and f'[ebp - {source_slot}]' in b.op_str,
                 f'{action:#x}: source x86{i} original floating scratch stack ownership still differs')
        if action==0x2DF:
            need(original[128].mnemonic==generated[128].mnemonic=='test'
                 and original[128].op_str==generated[128].op_str=='ah, 5'
                 and original[129].mnemonic==generated[129].mnemonic=='jp'
                 and original[82].op_str==generated[82].op_str=='0x333'
                 and original[106].op_str==generated[106].op_str=='0x387',
                 'native 2DF strict less-than X clamp did not restore TEST AH,5 and real two shots')
        else:
            need([x.mnemonic for x in original[76:81]]
                 ==[x.mnemonic for x in generated[76:81]]
                 ==['fld','fld','fucompp','fnstsw','test']
                 and original[80].op_str==generated[80].op_str=='ah, 0x44'
                 and original[33].op_str==generated[33].op_str=='0x38e'
                 and original[128].op_str==generated[128].op_str=='0x386'
                 and original[191].op_str==generated[191].op_str=='0x384'
                 and original[216].op_str==generated[216].op_str=='0x388',
                 'native 2E5 genuine FUCOMPP, shots and stage progression wrong')
        result.append({'original_action':f'0x{action:03X}',
             'original_actual_PE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
             'native_complete_CODE_B':size,
             'new_source_complete_CODE_B':sum(x.size for x in generated),
             'native_and_compiler_real_x86_mnemonic_width_positions':nx,
             'original_typed_PE_COFF_fields_in_native_x86_order':len(physical),
             'real_original_nonfield_normalized_GPR_CFG_mismatches':0,
             'genuine_original_and_compiler_EBP_x87_owners':ORIGINAL_X87_STACK[action],
             'native_case_strict_byte_exact':False,
             'new_accepted_whole_game_FUNCTION_CODE_B':0})
    need([x.mnemonic for x in ins[starts[0x2DF]:starts[0x2DF]+3]]
         ==['push','push','push']
         and [x.mnemonic for x in ins[starts[0x2E5]:starts[0x2E5]+3]]
         ==['push','push','push']
         and ins[after_2e5].mnemonic=='mov'
         and ins[after_2e5].op_str=='edx, dword ptr [ebp - 0x28]'
         and ins[after_2e5+1].op_str=='eax, word ptr [edx + 0x62]',
         'real complete 2DF->2E5->2EF source must retain original physical immediate handler order')
    return result


def main():
    f696=load('f720_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f720_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f720_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f720_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f708=load('f720_f708','scripts/verify-fighter-twin-burst-f708.py')
    f711=load('f720_f711','scripts/verify-fighter-falling-radials-f711.py')
    f714=load('f720_f714','scripts/verify-fighter-complex-movement-f714-f715.py')
    f718=load('f720_f718','scripts/verify-fighter-double-volley-f718.py')
    f672=load('f720_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f720_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f720_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f720_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f720_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f720_reader','scripts/compare-coff-function.py')
    acts=load('f720_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    src,modules,h=f714.combine_source(f706,f708,f711,f696,f699,f701,f672,
                                        reader,pe,real,boss,report,mapped)
    src=f718.source_with_double_volley(src)
    src=source_with_both(src)
    obj=f706.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-2DF-2E5.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-2DF-2E5.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,
        f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    new=prove_both(f701,f714,f676,f598,reader,pe,real,boss,mapped,emitted,refs)
    prior2DD2DE=f718.verify_two_native_actions(f701,f676,f598,reader,pe,real,boss,mapped,
                                               emitted,refs,following_native_2df=True)
    old2DB2DC=f714.audit_cases(f701,f676,f598,f699,reader,pe,real,boss,mapped,
                                emitted,refs,following_native_2dd=True)
    old2D0D1=f711.compare_native_radials(reader,pe,real,f676,f598,f701,boss,mapped,
                                        emitted,refs,following_native_2db=True)
    old2BFC4=f708.check_native_cases(f701,f676,f598,reader,pe,real,boss,mapped,emitted,refs)
    originals,first=f706.native_cases_and_compiled_start(f672,reader,pe,real,boss,mapped,emitted,refs)
    older_five,end=f706.verify_five_native_cases(f672,f598,f701,originals,emitted,refs,first)
    need(end==6623,'five original 259-25D complete source cases regressed')
    late,source302end=f706.check_later_native_physical(
        f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,emitted,refs,
        expected_storm_starts=SOURCE_STORMS_LATER,
        preceding_storm_starts=SOURCE_STORMS_PRIOR)
    need(source302end==SOURCE_TRUE_302_END,
         'real source 2DF/2E5 changed physical native 302 end/31B boundary')
    context=f696.verify_prior_parent_context(
        reader,pe,real,boss,report,mapped,code,refs,modules,h,
        expected_receiver_uses=SOURCE_SAVED_THIS_MOV_USES,
        following_native_2fa=True,
        source_receiver_slot='0x28',source_scratch_slot='0x40',
        source_scratch_shift=32,source_f684_slot_shift=160,
        source_native_302_end_ordinal=source302end,
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=end,
        following_native_2bf=True,source_storm_bytes=928,
        source_storm_width_differences=f706.SOURCE_STORM_WIDTHS,
        source_2f0_2f1_expected_GPR_counts={0x2F0:(147,39),0x2F1:(170,0)},
        source_native_2e5_end_ordinal=SOURCE_TRUE_AFTER_2E5)
    need(context['previous_27_nonterminal_context_strict_original_cases_rechecked']
         and context['actual_source_context_nonterminal_strict_case_count']==27
         and context['original_2ef_real_GPR_regression']==0
         and context['original_2f0_2f1_real_GPR_mismatches']==[147,170]
         and context['original_after_RET_switch_DATA_rechecked_on_this_source'],
         'actual source 2DF/2E5 must genuinely RESTORE strict original 2EF while preserving original afterRET')
    receipt={
      'original_native_entire_fighter':'0x00543210',
      'original_whole_giant_CODE_still_NONEXACT':boss['size'],
      'original_full_afterRET_switch_DATA_bytes':boss['postret_size'],
      'new_physically_verified_original_complete_actions':new,
      'new_source_backed_original_internal_CODE_NOT_CREDITED':1400,
      'new_original_native_x86_mnemonic_width_positions':392,
      'new_all_original_physically_typed_PE_COFF_fields':38,
      'new_original_2EF_788B_strict_context_RESTORED':True,
      'previous_real_native_2DD_2DE':prior2DD2DE,
      'previous_real_native_2DB_2DC':old2DB2DC,
      'previous_real_native_2D0_2D1':old2D0D1,
      'previous_real_native_2BF_2C4':old2BFC4,
      'previous_real_native_259_25D':older_five,
      'previous_real_native_2F8_302':late,
      'prior_27_original_strict_contexts_and_all_afterRET_DATA':context,
      'original_whole_game_fighter_function_exact':False,
      'new_accepted_original_game_FUNCTION_CODE_bytes':0,
    }
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F720/F721 new full original 00543210 native 2DF 602B/169 x86/18 original '
          'typed COFF refs, 2E5 798B/223 x86/20 original typed refs: all '
          '392 native opcode/width/GPR phase positions and 38 physical typed '
          'references match normal C++ in a complete VC7.1 giant parent. '
          'Native original 2DF `POS<0` restores TEST AH,5; 2E5 original '
          'owner equality restores true native FLD/FLD/FUCOMPP. Original EBP '
          'scratch offsets still differ; both actions NONEXACT. Significant '
          'cross-case gain: original 2EF 788B/224 x86/20 fields now STRICT '
          'context again (0 real GPR errors), preserving other 26 strict '
          'previous nonterminal native cases and 943B real afterRET DATA. '
          '2F0 still 147, 2F1 still 170 real GPR mismatches; whole original '
          '58KB boss still NONEXACT, zero newly credited whole game functions. '
          'Only one changed giant compiled, no all-943 cold replay.')


if __name__=='__main__':
    main()
