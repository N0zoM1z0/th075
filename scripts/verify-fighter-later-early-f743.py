#!/usr/bin/env python3
"""F743: full native original 19C/19E/1A0/1A1 original giant action source.

Build ONE entire VC7.1 original-shaped fighter parent. Four complete
physical native PE actions (218/366/309/309 original CODE B;
62/104/84/84 x86, 7/11/7/7 physical typed fields) now have
meaningful C++ action state, float collision and 0x335 shots.
Check every original instruction mnemonic/width and physical COFF
owner ordinal/target/type/addend, but explicitly preserve real GPR
33/59/53/53 and EBP scratch failures: no inner-case exact claim.
The original 19A/19B source remains UNRECOVERED, and 199/19D/19F
point to a shared native switch default, not separate 0-byte functions.
Retest original 190-198, earlier native 13 case register regressions,
and complete 943 original afterRET DATA/156 genuine x86 jump targets.
Never run full 964-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f743-fighter-later-early'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
CASES=(0x19C,0x19E,0x1A0,0x1A1)
ORIGINAL={
 0x19C:(0x0054A21A,0x0054A2F4,218,62,7,6082,33,49,50,'0xc8','0x88'),
 0x19E:(0x0054A2F4,0x0054A462,366,104,11,6144,59,91,92,'0xcc','0x8c'),
 0x1A0:(0x0054A462,0x0054A597,309,84,7,6248,53,64,65,'0xd0','0x90'),
 0x1A1:(0x0054A597,0x0054A6CC,309,84,7,6332,53,64,65,'0xd4','0x94'),
}
NEXT={0x19C:0x19E,0x19E:0x1A0,0x1A0:0x1A1,0x1A1:0x1F4}
SYMBOLS={
 0x00453E20:'ResetAt453E20',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00453D40:'PrepareActionAt453D40',
 0x00659A14:'g_F743_Y19CAt00659A14',
 0x00659A20:'g_F737_RoundY1At00659A20',
 0x00659288:'g_F743_Y1A0At00659288',
 0x0065782C:'g_ThresholdAt0065782C',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0046D000:'StartAnimationAt46D000',
 0x0040FB40:'SetAuxActionAt40FB40',
}
PRIOR_REAL_GPR={
 0x1F4:(538,149,538,18,71),
 0x1F5:(538,149,538,18,71),
 0x1FA:(287,82,287,9,50),
 0x1FB:(603,174,603,15,111),
 0x1FE:(526,153,526,14,96),
 0x1FF:(526,153,526,14,96),
 0x200:(343,102,343,8,67),
 0x201:(436,126,436,9,85),
 0x2D0:(416,120,416,15,60),
 0x2D1:(416,120,416,15,60),
 0x2DD:(680,189,680,19,80),
 0x2DE:(660,189,660,18,0),
 0x2EF:(788,224,788,20,0),
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,rel):
    sp=importlib.util.spec_from_file_location(name,ROOT/rel)
    need(sp is not None and sp.loader is not None,'missing verified native PE helper '+rel)
    mod=importlib.util.module_from_spec(sp)
    sys.modules[name]=mod
    sp.loader.exec_module(mod)
    return mod


def source_with_four(src):
    for action in CASES:
        old=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(old)==1,
             f'physical game action {action:#x} old source marker missing or duplicated')
        src=src.replace(old,'#include "FighterLaterEarlyF743.inc"' if action==0x19C else '')
    anchor='extern float g_F740_ShotY2At00659A18;'
    need(src.count(anchor)==1,'real F740 source global declaration not found')
    src=src.replace(anchor,anchor+'\n'
        'extern float g_F743_Y19CAt00659A14;\n'
        'extern float g_F743_Y1A0At00659288;')
    need(src.count('#include "FighterLaterEarlyF743.inc"')==1,
         'all four native real case C++ bodies must be compiled exactly once')
    for unhandled in (0x19A,0x19B):
        need(f'case 0x{unhandled:X}: g_FighterProbeMarker' in src,
             'original physically shared 19A/19B must remain visibly NOT recovered')
    return src


def verify_native_four(rd,pe,d,f676,f701,f598,by,ins,refs,*,
                       following_complete_19A_19B=False):
    rows=[]
    for action in CASES:
        lo,hi,nb,nx,nfields,start,gpr,mi,fi,old_slot,new_slot=ORIGINAL[action]
        if following_complete_19A_19B:
            # Two actually compiled source 166-x86 cases replace two prior
            # placeholder 2-x86 markers: ordinal shift = 2*(166-2).
            start+=328
            gpr=0
            new_slot=f'0x{int(new_slot,16)+0x10:x}'
        need(by[action]==lo and by[NEXT[action]]==hi and hi-lo==nb,
             f'original complete native physical PE handler bounds changed for {action:#x}')
        native=list(d.disasm(rd.pe_bytes_at(pe,lo,nb),lo))
        gen=ins[start:start+nx]
        need(len(native)==len(gen)==nx
             and sum(x.size for x in native)==sum(x.size for x in gen)==nb
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(native,gen))
             and native[-1].mnemonic==gen[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'original entire {action:#x} x86 ordered mnemonic, WIDTH or tail mismatch')
        fields=f676.original_fields(native)
        physical=f701.compare_typed_fields(fields,gen,refs,SYMBOLS,
                                          tuple(i for i,_,_ in fields))
        need(len(fields)==len(physical)==nfields,
             f'original {action:#x} original PE/C++ 7/11 real typed fields missing')
        for ordinal,mn in ((mi,'mov'),(fi,'fild')):
            a,b=native[ordinal],gen[ordinal]
            need(a.mnemonic==b.mnemonic==mn
                 and f'[ebp - {old_slot}]' in a.op_str
                 and f'[ebp - {new_slot}]' in b.op_str,
                 f'original {action:#x} genuine used x87 stack owner at x86 {ordinal} not proven')
        absfields={i for i,t,mn in fields if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(gen)))
               if a!=b and i not in absfields]
        need(len(wrong)==gpr,
             f'original {action:#x} real current whole-parent nonfield GPR/CFG phase changed: {wrong[:8]}')
        if action==0x19C:
            need(native[26].op_str.endswith(', 5') and gen[26].op_str.endswith(', 5')
                 and native[48].op_str.endswith(', 0x28') and gen[48].op_str.endswith(', 0x28')
                 and native[55].op_str==gen[55].op_str=='0x335'
                 and native[58].op_str==gen[58].op_str=='0xc8',
                 'original 19C stage5 direction40 kind335 animation200 lost')
        elif action==0x19E:
            need(native[18].op_str==gen[18].op_str=='ah, 0x41'
                 and native[19].mnemonic==gen[19].mnemonic=='jne'
                 and native[32].op_str==gen[32].op_str=='ah, 0x41'
                 and native[33].mnemonic==gen[33].mnemonic=='jp'
                 and native[90].op_str.endswith(', 0x1b') and gen[90].op_str.endswith(', 0x1b')
                 and native[97].op_str==gen[97].op_str=='0x335',
                 'original 19E real two physical x87 branch masks or shot27 lost')
        else:
            need(native[20].mnemonic==gen[20].mnemonic=='fcomp'
                 and native[22].op_str==gen[22].op_str=='ah, 0x41'
                 and native[23].mnemonic==gen[23].mnemonic=='jp'
                 and native[63].op_str.endswith(', 0x2d' if action==0x1A0 else ', 0x1b')
                 and gen[63].op_str.endswith(', 0x2d' if action==0x1A0 else ', 0x1b')
                 and native[70].op_str==gen[70].op_str=='0x335'
                 and native[80].op_str==gen[80].op_str=='9',
                 f'original {action:#x} native stage4 45/27 shot and landing predicate differ')
        rows.append({'native_original_action':f'0x{action:X}',
            'original_entire_PE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
            'original_entire_CODE_B':nb,
            'source_entire_CODE_B':sum(x.size for x in gen),
            'original_and_source_ordered_x86_mnemonics_AND_WIDTHS':nx,
            'real_typed_PE_COFF_original_fields_owned_at_native_x86_ordinal':len(physical),
            'true_normalized_nonfield_GPR_CFG_differences':gpr,
            'original_real_used_x87_EBP_scratch':old_slot,
            'compiler_real_used_x87_EBP_scratch':new_slot,
            'native_internal_case_or_game_function_byte_exact':False})
    source_shift=328 if following_complete_19A_19B else 0
    for k in (6082,6144,6248,6332,6416):
        need(ins[k+source_shift].mnemonic=='mov',
             f'original physical 19C/19E/1A0/1A1/1F4 source start shifted: x86{k+source_shift}')
    need(ins[6416+source_shift].op_str.endswith('[ebp - 0x3c]'),
         'last native 1A1 C++ case must hand off to true original 1F4 source')
    return rows


def main():
    rd=load('f743_rd','scripts/compare-coff-function.py')
    acts=load('f743_actions','scripts/report-fighter-action-handlers.py')
    f676=load('f743_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f701=load('f743_typed','scripts/verify-fighter-four-tier-volley-f701.py')
    f598=load('f743_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f728=load('f743_728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f743_729','scripts/verify-fighter-return-boundary-f729.py')
    f731=load('f743_731','scripts/verify-fighter-aim-return-f731.py')
    f732=load('f743_732','scripts/verify-fighter-following-native-f732.py')
    f734=load('f743_734','scripts/verify-fighter-eight-round-f734.py')
    f737=load('f743_737','scripts/verify-fighter-eight-ground-f737.py')
    f740=load('f743_740','scripts/verify-fighter-repeat-shot-f740.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    src,compiler=f728.source_for_complete_parent(rd,pe,d,boss,report,mapped)
    src=f729.source_with_return_boundaries(src)
    src=f731.source_with_aim_return(src)
    src=f732.whole_source_with_following(src)
    src=f734.source_with_three(src)
    src=f737.with_194_195(src)
    src=f740.source_with_repeat_shots(src)
    src=source_with_four(src)
    obj=compiler.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-19C-1A1.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-19C-1A1.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=rd.object_function(obj,SYMBOL)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    new=verify_native_four(rd,pe,d,f676,f701,f598,by,ins,refs)
    preceding=f740.verify_all_three_native(rd,pe,d,f676,f701,f598,by,ins,refs)
    prior194=f737.check_entire_cases(rd,pe,d,f676,f701,f598,by,ins,refs,
                                    following_native_196=True)
    prior190=f734.new_native_actions(rd,pe,d,f676,f701,f598,by,ins,refs,
                             following_native_194=True,source_x87_slot_shift=8)
    mapped=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    previous=f737.check_selected_context(rd,pe,d,f676,f598,by,ins,refs,
                mapped,source_1f4_start=6416,source_expected_context=PRIOR_REAL_GPR)
    afterret=f728.complete_native_switch_DATA(rd,pe,d,boss,code,ins,refs,
                source_1f5_start=6565,source_1f6_start=6714)
    need(len(new)==4
         and sum(x['original_entire_CODE_B'] for x in new)==1202
         and sum(x['original_and_source_ordered_x86_mnemonics_AND_WIDTHS'] for x in new)==334
         and sum(x['real_typed_PE_COFF_original_fields_owned_at_native_x86_ordinal'] for x in new)==32
         and [x['real_nonfield_GPR_CFG_differences'] for x in previous]
              ==[x[-1] for x in PRIOR_REAL_GPR.values()]
         and afterret['original_nonrelocation_afterRET_BYTES_equal']==319,
         'physical original four later source cases/PE fields or earlier context GPR not verified')
    receipt={'original_whole_fighter':'0x00543210',
        'whole_original_58KB_CODE_remains_NONEXACT':boss['size'],
        'four_new_full_physically_bounded_internal_Cpp_handlers':new,
        'new_original_source_backed_INTERNAL_CODE_bytes_NOT_CREDITED':1202,
        'new_native_334_original_x86_mnemonic_AND_width_positions':334,
        'new_native_PE_COFF_physical_typed_refs':32,
        'original_previous_196_197_198_rechecked':preceding,
        'original_previous_194_195_rechecked':prior194,
        'original_previous_190_191_192_rechecked':prior190,
        'new_parent_actual_13_prior_original_GPR_phase_NEGATIVES':previous,
        'entire_original_943B_native_afterRET_switch_DATA':afterret,
        'original_19A_19B_source_still_missing':True,
        'whole_original_GAME_function_byte_exact':False,
        'new_accepted_authored_complete_game_CODE_B':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F743 original full giant 19C/19E/1A0/1A1: pinned actual native '
          '218/366/309/309 CODE B, 62/104/84/84 native x86, '
          '7/11/7/7 true physical typed PE/COFF fields each. '
          'Same entire VC7.1 C++ parent emits exactly ALL 1202 original '
          'CODE widths and all 334 mnemonic positions and all 32 actual '
          'native PE relocation owners, but real GPR errors 33/59/53/53 '
          'and original EBP -0xC8/-0xCC/-0xD0/-0xD4 vs generated '
          '-0x88/-0x8C/-0x90/-0x94: NONEXACT whole game. '
          'Earlier 190-198 complete original cases and 13 previous native '
          'GPR phases including genuine new regressions rechecked. '
          'Native 19A/19B still unimplemented, default 199/19D/19F '
          'remains shared. Entire separate 943 native afterRET DATA, '
          '156 genuine x86-aligned DIR32 entries, 319 original sparse '
          'bytes verified; zero original complete callable CODE accepted.')


if __name__=='__main__':
    main()
