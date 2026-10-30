#!/usr/bin/env python3
"""F706: exact original geometry in a more complete giant fighter C++ context.

Build ONE whole original-shaped 00543210 parent (real 259-25D, 2F8-302)
from tracked natural source, checking each native case, every physical typed
PE/COFF field, independent EBP scratch and original after-RET switch DATA.
The native giant remains NONEXACT: no split inner-case credit, no all-unit
cold replay, and contextual source matching never proves historical class.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f706-fighter-combined-native-case-context'
ACTOR=0x00543210
SOURCE_CASES=(0x259,0x25A,0x25B,0x25C,0x25D)
SOURCE_259_FIRST=6189
SOURCE_259_END=6623
SOURCE_302_END=9053
SOURCE_GIANT_THIS_SLOT='0x28'
SOURCE_THIS_MV_USES=2643
# Fresh full-parent lifetime placement. These real source slots come from
# independently used integer-to-float conversion operands; never normalize.
SOURCE_F672_SLOTS={
 0x259:{47:'0x5c',48:'0x5c',68:'0x60',69:'0x60',91:'0x64',92:'0x64',
        112:'0x68',113:'0x68',135:'0x6c',136:'0x6c',156:'0x70',
        157:'0x70',179:'0x74',180:'0x74',200:'0x78',201:'0x78'},
 0x25A:{40:'0x7c',41:'0x7c'},
 0x25B:{40:'0x80',41:'0x80'},
 0x25C:{32:'0x84',33:'0x84'},
 0x25D:{32:'0x88',33:'0x88'},
}
ORIGINAL_SOURCE_CASE_BYTES={0x259:685,0x25A:192,0x25B:192,0x25C:170,0x25D:170}
ORIGINAL_WIDE_ORDINALS={0x259:(47,48,68,69,91,92,112,113,135,136,156,157,179,180,200,201),
                        0x25A:(40,41),0x25B:(40,41),0x25C:(),0x25D:()}
SOURCE_STORM_WIDTHS={39:(4,3),41:(6,4),42:(6,3),43:(3,6),44:(3,6)}
SOURCE_F684_SLOTS=(78,79,94,95,124,125,151,152,167,168,197,198,273,274,330,331)


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing original checker '+str(path))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def source_for_new_combined_parent(f696,f699,f701,f672,reader,pe,real,boss,report,mapped):
    source,modules,helpers=f696.source_for_entire_parent(reader,pe,real,boss,report,mapped)
    source=f699.source_with_2fa(source)
    source=f701.source_with_302(source)
    source=f672.source_with_cases(source)
    need(all(source.count('#include "'+name+'"')==1 for name in (
         'FighterEightShotAndFollowF672.inc','FighterStormVolleyF681.inc',
         'FighterAngleStormF684.inc','FighterApproachVolleyF699.inc',
         'FighterGroundedVolleyF696.inc','FighterFourTierVolleyF701.inc')),
         'full original parent must include all actual natural game action source cases')
    return source,modules,helpers


def compile_whole_parent(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-259-thru-302.cpp'
    obj=OUT/'Boss00543210-259-thru-302.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
           '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
           cwd=ROOT,env=env,capture_output=True,text=True,timeout=230)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'real pinned VC7.1 complete selected fighter compile failed: '+cp.stderr[-550:])
    return obj


def native_cases_and_compiled_start(f672,reader,pe,real,boss,mapped,ins,refs):
    native=f672.original_cases(reader,pe,real,boss,mapped)
    # Native action259's stage5 contains one original animation call
    # preceded by 0xFA, then literal angle member -10.0f assignment.
    # The specific original x86 ordinal is 32. Other native actions
    # may call animation; select by all surrounding *real* instructions
    # and a typed original REL32 symbol instead of a guessed offset.
    anchors=[]
    for field in refs:
        if 'StartAnimationAt46D000' not in field['symbol'] or field['type']!='REL32':continue
        ordinal=next((i for i,x in enumerate(ins)
                      if x.address<=field['offset']<x.address+x.size),None)
        if ordinal is None or ordinal<33 or ordinal+2>=len(ins):continue
        if (ins[ordinal].mnemonic=='call' and ins[ordinal-2].mnemonic=='push'
                and ins[ordinal-2].op_str=='0xfa'
                and ins[ordinal+2].mnemonic=='mov'
                and ins[ordinal+2].op_str.endswith(', 0xc1200000')):
            anchors.append(ordinal)
    need(len(anchors)==1,'original unique 259 native animation, shot-angle and typed CALL anchor changed')
    start=anchors[0]-32
    need(start==SOURCE_259_FIRST
         and ins[start].mnemonic=='mov'
         and ins[start].op_str=='eax, dword ptr [ebp - 0x28]',
         'original complete action259 start or context-specific saved receiver moved')
    return native,start


def verify_five_native_cases(f672,f598,f701,originals,ins,refs,start):
    ix=start
    results=[]
    for action in SOURCE_CASES:
        native,lo,hi,original_fields=originals[action]
        count,original_size,older_source_bytes,original_field_count=f672.GEOMETRY[action]
        source=ins[ix:ix+count]
        need(len(source)==len(native)==count
             and source[-1].mnemonic=='jmp'
             and sum(x.size for x in source)==ORIGINAL_SOURCE_CASE_BYTES[action]
             and len(original_fields)==original_field_count,
             f'original action{action:#x}: complete native/source 259-25D body or shared exit changed')
        # Original typed fields: their physical owning instruction ordinal,
        # type, addend and symbol are checked independently, not just count.
        source_fields=f701.compare_typed_fields(original_fields,source,refs,
              f672.SYMBOLS,tuple(i for i,target,mn in original_fields))
        need(len(source_fields)==original_field_count,
             f'{action:#x} full source/PE field count differs')
        wrong_mn=[i for i,(a,b) in enumerate(zip(native,source)) if a.mnemonic!=b.mnemonic]
        need(not wrong_mn,
             f'{action:#x} actual original shot/float/CFG opcode sequence differs: {wrong_mn[:6]}')
        real_widths=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,source)) if a.size!=b.size]
        need(real_widths==[(i,6,3) for i in ORIGINAL_WIDE_ORDINALS[action]],
             f'{action:#x}: real original int-to-x87 source EBP operand widths changed {real_widths}')
        for ordinal,(original_slot,_) in f672.SLOTS[action].items():
            src_slot=SOURCE_F672_SLOTS[action][ordinal]
            need(f'[ebp - {original_slot}]' in native[ordinal].op_str
                 and f'[ebp - {src_slot}]' in source[ordinal].op_str,
                 f'{action:#x} native x86{ordinal} true scratch ownership was masked')
        nshape=f598.normalized(native)
        cshape=f598.normalized(source)
        absolute={i for i,target,mn in original_fields if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(nshape,cshape)) if a!=b and i not in absolute]
        need(not wrong,f'{action:#x} native/source original GPR/x87/CFG roles changed: {wrong[:8]}')
        # The broad prior normalization intentionally erases ALL EBP
        # displacements; independently prove the only non-field operand
        # differences are the 24 authentic named x87 scratch positions.
        raw=[i for i,(a,b) in enumerate(zip(native,source))
             if i not in absolute and a.mnemonic!='call'
             and not a.mnemonic.startswith('j')
             and a.op_str.replace('[ebp - 0x44]','[ebp - 0x28]')!=b.op_str]
        need(raw==list(f672.SLOTS[action]),
             f'{action:#x} genuine raw source EBP/local mismatch roles changed {raw[:9]}')
        results.append({'original_action':f'0x{action:X}',
                        'original_native_start':f'0x{lo:08X}',
                        'original_next_handler':f'0x{hi:08X}',
                        'original_whole_case_CODE_bytes':original_size,
                        'new_source_whole_case_CODE_bytes':sum(x.size for x in source),
                        'full_x86_positions':count,
                        'actual_typed_PE_COFF_fields':len(source_fields),
                        'remaining_real_source_EBP_scratch_mismatches':len(raw),
                        'original_native_wider_x87_scratch_instructions':len(real_widths),
                        'context_strict_original_case':False})
        ix+=count
    need(ix==SOURCE_259_END
         and ins[ix].mnemonic=='mov'
         and ins[ix].op_str=='eax, dword ptr [ebp - 0x28]',
         'complete 259-25D source does not end at original physical 2BC')
    return results,ix


def check_later_native_physical(f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,ins,refs):
    storm_starts=[i for i,x in enumerate(ins)
                  if [y.mnemonic for y in ins[i:i+3]]==['push']*3
                  and [y.op_str for y in ins[i:i+3]]==['0xff0000','4','3']]
    need(len(storm_starts)==3,'real 2F9,2FB,302 storm entries missing')
    need(storm_starts==[7949,8611,8792],
         'native 259 through 302 parent case and original source order changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    frames=[('0x2F8',0x2F8,0x2F9,storm_starts[0]-252,storm_starts[0],928,252,23,f681.FIELD_SYMBOLS),
            ('0x2F9',0x2F9,0x2FA,storm_starts[0],storm_starts[0]+381,1367,381,34,f684.PE_TARGETS),
            ('0x2FA',0x2FA,0x2FB,storm_starts[0]+381,storm_starts[1],979,281,31,f699.TARGET_SYMBOLS),
            ('0x2FB',0x2FB,0x302,storm_starts[1],storm_starts[2],647,181,17,f696.EXPECTED_SYMBOLS),
            ('0x302',0x302,0x31B,storm_starts[2],storm_starts[2]+261,935,261,28,f701.NATIVE_FIELD_SYMBOLS)]
    reviewed=[]
    for label,action,next_action,start,end,size,nx,nfields,symbols in frames:
        native_addr=by[action]
        native_size=by[next_action]-native_addr
        real_native=list(real.disasm(reader.pe_bytes_at(pe,native_addr,native_size),native_addr))
        original_fields=f676.original_fields(real_native)
        source=ins[start:end]
        need(len(real_native)==len(source) if action!=0x2FA else len(source)==nx,
             f'original {label} source/native instruction alignment changed')
        need(len(source)==nx and sum(x.size for x in source)==size
             and len(original_fields)==nfields,
             f'{label} original source case length, x86 instructions or PE/COFF refs changed')
        fields=f701.compare_typed_fields(original_fields,source,refs,symbols,
                  tuple(i for i,target,mn in original_fields),ordinal_strict=action!=0x2FA)
        need(len(fields)==nfields,f'original {label} typed original source COFF fields changed')
        if action in (0x2F8,0x2F9,0x302):
            need(len(real_native)==nx, f'{label} original whole x86 count is not physically attested')
        if action==0x2F9:
            need(all(a.size==b.size for a,b in zip(real_native,source))
                 and len([(i,a.mnemonic,b.mnemonic) for i,(a,b) in enumerate(zip(real_native,source))
                          if a.mnemonic!=b.mnemonic])==8,
                 'original 2F9 reconstructed native scratch/float width still nonexact')
        if action==0x302:
            need(all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(real_native,source)),
                 'previous original 302 935B/261 native opcode geometry regressed')
        reviewed.append({'action':label,'original_full_CODE_bytes':native_size,
                         'source_full_CODE_bytes':size,
                         'source_full_x86':len(source),
                         'all_original_typed_PE_COFF_fields':len(fields)})
    return reviewed,storm_starts[-1]+261


def main():
    f696=load('f706_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f706_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f706_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f672=load('f706_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    f681=load('f706_f681','scripts/verify-fighter-storm-terminal-f681.py')
    f684=load('f706_f684','scripts/verify-fighter-angle-storm-f684.py')
    f676=load('f706_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f706_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f706_reader','scripts/compare-coff-function.py')
    acts=load('f706_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    source,dependencies,helpers=source_for_new_combined_parent(
        f696,f699,f701,f672,reader,pe,real,boss,report,mapped)
    obj=compile_whole_parent(source)
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    generated=[]
    for x in real.disasm(code,0):
        generated.append(x)
        if x.mnemonic=='ret':break
    originals,start=native_cases_and_compiled_start(f672,reader,pe,real,boss,mapped,generated,refs)
    five,end=verify_five_native_cases(f672,f598,f701,originals,generated,refs,start)
    later,source302end=check_later_native_physical(
         f701,f696,f699,f676,f681,f684,f598,reader,pe,real,boss,mapped,generated,refs)
    need(source302end==SOURCE_302_END,
         'the entire original 302 935-byte source does not lead to native terminal 31B')
    # The new *genuine source* 259/25D loops allocate a larger frame,
    # changing preceding 2F8/2F9 scratch widths without changing their
    # source syntax. Re-attest true compiler receiver MOV ownership,
    # previous 27 strict nonterminal cases, every previous nonstrict
    # case and the complete independently owned afterRET DATA.
    context=f696.verify_prior_parent_context(
        reader,pe,real,boss,report,mapped,code,refs,dependencies,helpers,
        expected_receiver_uses=SOURCE_THIS_MV_USES,following_native_2fa=True,
        source_receiver_slot=SOURCE_GIANT_THIS_SLOT,source_scratch_slot='0x40',
        source_scratch_shift=32,source_f684_slot_shift=68,
        source_native_302_end_ordinal=source302end,
        source_2f9_expected_size=1367,source_2f9_wide_ordinals=(),
        following_native_259=True,source_259_25D_end_ordinal=end,
        source_storm_bytes=928,source_storm_width_differences=SOURCE_STORM_WIDTHS)
    need(context['previous_27_nonterminal_context_strict_original_cases_rechecked']
         and context['original_after_RET_switch_DATA_rechecked_on_this_source']
         and context['prior_2f9_nonfield_GPR_mismatches']==236
         and context['prior_terminal_31b_real_gpr_negative']==43,
         'actual previous original context and complete afterRET data not preserved')
    summary={
       'target':'pinned Japanese TH075 1.11',
       'native_whole_boss_start':'0x00543210',
       'original_whole_giant_CODE_bytes_still_NONEXACT':boss['size'],
       'original_separately_owned_afterRET_DATA_bytes':boss['postret_size'],
       'native_five_259_through_25D_original_source_contexts':five,
       'new_full_parent_source_five_original_CODE_bytes':sum(x['original_whole_case_CODE_bytes'] for x in five),
       'new_full_parent_source_five_generated_CODE_bytes':sum(x['new_source_whole_case_CODE_bytes'] for x in five),
       'native_previous_five_x87_width_discrepancies_now':sum(x['original_native_wider_x87_scratch_instructions'] for x in five),
       'all_later_full_original_source_bodies_in_same_parent':later,
       'original_2f8_full_size_now_restored':928,
       'original_2f9_full_1367B_x86_widths_now_restored':True,
       'full_native_previous_2f9_remaining_GPR_mismatches':236,
       'all_prior_27_strict_nonterminal_cases_and_entire_afterRET_original':context,
       'full_parent_exact':False,
       'new_accepted_game_FUNCTION_CODE_bytes':0,
    }
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F706 newly combined real 00543210 giant full parent: native 259-25D five '
          'complete bodies 434 x86/1469 original CODE B/42 original physical typed '
          'fields with 1409 emitted B, 0 nonfield register errors but 24 actual EBP '
          'scratch operand mismatches. Real 25C/25D now original 170B/170B widths. '
          'Other genuine upstream case contexts: source 2F8 now 928B original width, '
          '2F9 now 1367B/381 native x86/34 PE-typed fields with ALL original '
          'instruction widths, 2FA 979B/281, 2FB 647B/181, 302 935B/261. '
          'Original 2F9 still has 236 GPR/x87 mismatches; no whole exactness. '
          'Same freshly compiled giant retains preceding 27 strict contextual '
          'cases, real negative controls and original 943-B afterRET DATA. '
          'No fake padded locals, inner-case CODE credit or 943-unit replay.')


if __name__=='__main__':
    main()
