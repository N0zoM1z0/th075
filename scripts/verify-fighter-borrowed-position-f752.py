#!/usr/bin/env python3
"""F752 original complete 05D/05E direct actor/opponent FCOMP grammar.

Recompile ONE whole original-shaped 58KB VC7.1 fighter from independently
tracked natural C++ fragments. Borrowed physically observed float member
views (+0x44, never allocated) restore BOTH original 337B/101-x86
physical game-case interiors, ALL 16 PE typed fields at original native
instructions, native GPR/branch widths, and native saved-this EBP−0x44.
Compare nonfield CODE differences including real cross-parent jumps;
recheck 059/060/061/062, all 27 later original actions and complete
943B switch DATA with 156 physical DIR32 entries. No fake standalone
inner-case credit or all-967-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f752-fighter-native-borrowed-position'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'


def need(ok,what):
    if not ok: raise ValueError(what)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'original physical PE verifier unavailable: '+path)
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def source_with_typed_borrowed_faces(src,f749):
    src=f749.source_with_six(src)
    original='#include "FighterEarlyBounceF747.inc"'
    need(src.count(original)==1,'must replace only native 059/05D/05E source fragment')
    src=src.replace(original,'#include "FighterEarlyBounceTypedF752.inc"')
    need(src.count('#include "FighterEarlyBounceTypedF752.inc"')==1,
         'original 05D/05E direct borrowed-member C++ must be in entire giant')
    return src


def verify_native_local_control_bytes(rd,pe,d,mapper,ins,code,refs):
    """Check complete 337B cases, acknowledging only their two relative
    jumps outside the local case. This is diagnostic; NEVER formal CODE.
    """
    original_cases={0x5D:0x0054526D,0x5E:0x005453BE}
    rows=[]
    for act,lo in original_cases.items():
        orig=rd.pe_bytes_at(pe,lo,337)
        st=mapper[lo]
        source=code[st:st+337]
        need(len(source)==337,'original 337B case generated a shorter source region')
        fields=[r for r in refs if st<=r['offset']<st+337]
        need(len(fields)==8,'original 05D/05E exact 8 physical PE/COFF fields missing')
        mask={i for r in fields for i in range(r['offset']-st,r['offset']-st+4)}
        differences=[i for i in range(337) if i not in mask and orig[i]!=source[i]]
        need(differences==[103,104,333,334],
             f'physical native original {act:#x} unexpected nonrelocated byte differences {differences[:18]}')
        native_inst=list(d.disasm(orig,lo))
        source_inst=list(d.disasm(source,st))
        need(len(native_inst)==len(source_inst)==101
             and native_inst[31].mnemonic==source_inst[31].mnemonic=='jmp'
             and native_inst[100].mnemonic==source_inst[100].mnemonic=='jmp'
             and all(native_inst[i].size==source_inst[i].size
                     for i in range(101)),
             'only original native shared-tail relative JMP displacements may differ')
        true_native_tail='0x5515c2'
        source_tail=source_inst[31].op_str
        actual_compiled_x86_starts={x.address for x in ins}
        need(int(source_tail,16) in actual_compiled_x86_starts,
             'actual full-parent source shared-tail target must be a decoded x86 instruction')
        for ix in (31,100):
            need(native_inst[ix].op_str==true_native_tail
                 and source_inst[ix].op_str==source_tail,
                 'native original 05D/05E and complete source must each land at their own genuine common tail')
        rows.append({'original_native_case':f'0x{act:X}',
          'original_entire_case_CODE_B':337,'generated_entire_case_CODE_B':337,
          'physically_typed_PE_COFF_fields':8,
          'original_nonfield_bytes_identical':301,
          'total_nonfield_original_bytes':305,
          'only_cross_parent_SHARED_tail_JMP_relative_offset_differences':differences,
          'real_original_x86_fcomp_positions':[59,69],
          'original_entire_game_FUNCTION_exact':False})
    return rows


def main():
    rd=load('f752rd','scripts/compare-coff-function.py')
    acts=load('f752acts','scripts/report-fighter-action-handlers.py')
    f676=load('f752fields','scripts/verify-fighter-cloud-burst-f676.py')
    f701=load('f752typed','scripts/verify-fighter-four-tier-volley-f701.py')
    f598=load('f752norm','scripts/verify-fighter-singleton-contact-f598.py')
    f728=load('f752728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f752729','scripts/verify-fighter-return-boundary-f729.py')
    f731=load('f752731','scripts/verify-fighter-aim-return-f731.py')
    f732=load('f752732','scripts/verify-fighter-following-native-f732.py')
    f734=load('f752734','scripts/verify-fighter-eight-round-f734.py')
    f737=load('f752737','scripts/verify-fighter-eight-ground-f737.py')
    f740=load('f752740','scripts/verify-fighter-repeat-shot-f740.py')
    f743=load('f752743','scripts/verify-fighter-later-early-f743.py')
    f744=load('f752744','scripts/verify-fighter-double-repeat-f744.py')
    f749=load('f752749','scripts/verify-fighter-early-resource-f749.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==BOSS)
    report,mapped=acts.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    src,compiler=f728.source_for_complete_parent(rd,pe,d,boss,report,mapped)
    src=f729.source_with_return_boundaries(src)
    src=f731.source_with_aim_return(src)
    src=f732.whole_source_with_following(src)
    src=f734.source_with_three(src)
    src=f737.with_194_195(src)
    src=f740.source_with_repeat_shots(src)
    src=f743.source_with_four(src)
    src=f744.source_with_19a_19b(src)
    src=source_with_typed_borrowed_faces(src,f749)
    obj=compiler.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-typed-05D-05E.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-typed-05D-05E.obj')
    if obj.with_name('compiler.log').exists():shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=rd.object_function(obj,SYMBOL)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins[3].op_str=='dword ptr [ebp - 0x44], ecx',
         'real original whole fighter saved this EBP-0x44 must remain genuinely restored')
    mapper=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    current=f749.original_native_and_source(rd,pe,d,f676,f701,f598,by,ins,refs,mapper,
                                             native_direct_opponent_fcomp=True)
    older=f749.check_other_original_contexts(rd,pe,d,f676,f598,by,ins,refs,mapper,
                                              native_source_1f4_start=7406)
    table=f728.complete_native_switch_DATA(rd,pe,d,boss,code,ins,refs,
                                           source_1f5_start=7555,source_1f6_start=7704)
    bytes_verified=verify_native_local_control_bytes(rd,pe,d,mapper,ins,code,refs)
    need(len(current)==6 and len(older)==27 and len(bytes_verified)==2
         and sum(x['original_entire_CODE_bytes'] for x in current)==2373
         and all(x['genuine_normalized_nonfield_GPR_CFG_errors']==0 for x in current if x['original_native_action'] in ('0x05D','0x05E','0x062'))
         and table['original_nonrelocation_afterRET_BYTES_equal']==319,
         'full native original 05D/05E + early six + 27 original context or afterRET source not verified')
    receipt={'entire_original_00543210_CODE_B_still_NONEXACT':boss['size'],
             'new_05D_05E_actual_native_and_CPP_337B_direct_FCOMP':bytes_verified,
             'six_original_early_actions_in_same_one_fighter_parent':current,
             'other_27_original_physical_source_action_contexts':older,
             'native_943B_afterRET_switch_DATA':table,
             'actual_original_saved_this_EBP':'0x44',
             'new_complete_whole_game_FUNCTION_exact_CODE_B':0,
             'whole_original_game_FUNCTION_exact':False}
    (OUT/'f752-verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F752 natural typed borrowed actor/opponent member xAt44 restores original 05D/05E full 337B/101 x86 each, all ordered native mnemonics, widths, GPR operands, both direct FCOMP memory ordinals 59/69, and ALL 8+8 original physically typed PE/COFF fields. Original/compiler case body 301/305 nonfield B each equal; the ONLY four nonfield differences per case are two shared tail JMP rel32 displacements from the still NONEXACT whole 58KB parent. Original entire saved this EBP-0x44 remains real. Six early + 27 later full native case contexts and whole 943B original afterRET DATA with 156 typed DIR32 x86 labels/319 exact sparse B rechecked. NO standalone case credit or 967-unit cold replay.')

if __name__=='__main__':main()
