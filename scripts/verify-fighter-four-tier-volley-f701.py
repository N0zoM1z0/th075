#!/usr/bin/env python3
"""F701: reconstruct original complete 0x302 inside freshly built 58KB boss.

Attest native 0055101E..005513C5 (935 B, 261 x86, 28 PE/COFF fields),
all codegen starts/widths and all typed source field owners. The four
real distinct 6/6/8/8 projectile loops are natural VC7.1 C++, but
EBP lifetime and GPR phase remain NONSTRICT, NOT whole-function exact.
In the SAME full source parent, recheck preceding authentic 2FA/2FB,
27 context-strict earlier case interiors, all known native negatives
and the genuine separate 943-byte afterRET dispatch data. Compiles
only one selected whole boss, never replays all 943 accepted units.
"""
from __future__ import annotations
import difflib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f701-fighter-four-tier-volley'
ACTOR=0x00543210
ACTION=0x302
END=0x31B
ORIGINAL_BYTES=935
ORIGINAL_X86=261
SOURCE_BYTES=935
SOURCE_X86=261
NATIVE_FIELD_ORDINALS=(4,22,25,39,45,49,52,60,74,92,98,101,
                       126,131,136,138,163,168,173,175,200,205,
                       210,212,237,242,247,259)
NATIVE_FIELD_SYMBOLS={
 0x00454BC0:'ConfigureStormAt454BC0',
 0x00453E20:'ResetAt453E20',
 0x0065782C:'g_ThresholdAt0065782C',
 0x0040FB40:'SetAuxActionAt40FB40',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00455580:'RandomBoundaryAt455580',
 0x00453D40:'PrepareActionAt453D40',
 0x006714D0:'g_CloudOpponentAt006714D0',
 0x00658268:'g_F701_VolleyYAt00658268',
 0x00453A70:'SpawnFloatXYAt453A70',
}
LOOP_INDEXES={104:('0x34','0x18'),141:('0x38','0x1c'),
              178:('0x3c','0x20'),215:('0x40','0x24')}
X87_INTEGER_SLOTS={76:('0x208','0x9c'),77:('0x208','0x9c'),
                   116:('0x20c','0xa0'),117:('0x20c','0xa0'),
                   153:('0x210','0xa4'),154:('0x210','0xa4'),
                   190:('0x214','0xa8'),191:('0x214','0xa8'),
                   227:('0x218','0xac'),228:('0x218','0xac')}
FLOAT_Y_ORDINALS=(125,162,199,236)
FOLLOWING_2FB_OPCODE_SWAPS=((64,'mov','fld'),(65,'fld','mov'),
                            (75,'mov','fld'),(76,'fld','mov'))


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None, f'missing native checker: {path}')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def fields_in_source(refs,src):
    return [r for r in refs if src[0].address<=r['offset']<src[-1].address+src[-1].size]


def compare_typed_fields(native,src,refs,source_names,expected_ordinals,*,
                         ordinal_strict=True):
    """Require the real original physical x86 owner of every typed relocation.

    This tests ALL original call/global references, with exact ABI relocation
    types, original destination symbol and zero addend, but does not call
    any case byte-exact or hide other native operand differences.
    """
    fields=fields_in_source(refs,src)
    need(len(fields)==len(native)==len(expected_ordinals),
         'original physical PE/COFF relocations or x86 ordinal count differs')
    need(tuple(i for i,_,_ in native)==expected_ordinals,
         'real original native typed PE field ordinals changed')
    for (index,destination,mnemonic),reloc in zip(native,fields):
        need(destination in source_names
             and reloc['type']==('REL32' if mnemonic=='call' else 'DIR32')
             and reloc['addend']==0 and reloc['local_symbol_offset'] is None
             and source_names[destination] in reloc['symbol'],
             f'original native target {destination:#x} at x86{index}: physical PE/COFF source provenance mismatch')
        owner=[j for j,x in enumerate(src)
               if x.address<=reloc['offset']<x.address+x.size]
        need(len(owner)==1 and src[owner[0]].mnemonic==mnemonic
             and (not ordinal_strict or owner==[index]),
             f'original x86{index}: generated typed field moved to an invalid instruction {owner}')
    return fields


def source_with_302(source):
    """Insert actual complete 302 source into an original-shaped parent."""
    old='        case 0x302: g_FighterProbeMarker = 771; break;'
    need(source.count(old)==1, 'true complete native 302 source placeholder missing')
    source=source.replace(old,'#include "FighterFourTierVolleyF701.inc"')
    decl='extern float g_ThresholdAt0065782C;'
    need(source.count(decl)==1,'native original global threshold source declaration missing')
    source=source.replace(decl,decl+'\nextern float g_F701_VolleyYAt00658268;')
    need(all(source.count('#include "'+name+'"')==1 for name in (
         'FighterAngleStormF684.inc','FighterApproachVolleyF699.inc',
         'FighterGroundedVolleyF696.inc','FighterFourTierVolleyF701.inc')),
         'all four adjacent real parent case source fragments must be present')
    return source


def compile_original_full_parent(f696,f699,reader,pe,real,boss,report,mapped):
    source,modules,helpers=f696.source_for_entire_parent(reader,pe,real,boss,report,mapped)
    source=f699.source_with_2fa(source)
    source=source_with_302(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-302.cpp'
    obj=OUT/'Boss00543210-302.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,'original whole boss pinned VC7.1 serial compiler failed: '+result.stderr[-700:])
    return obj,modules,helpers


def original_boss_case(reader,pe,real,boss,mapped,f676,action,next_action,size,x86):
    by={x['action']:int(x['handler'],16) for x in mapped}
    lo,hi=by[action],by[next_action]
    need(boss['address']<lo<hi<boss['address']+boss['size'] and hi-lo==size,
         f'original action0x{action:X} physical CODE extent not original')
    native=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
    need(len(native)==x86 and sum(x.size for x in native)==size
         and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
         f'original action0x{action:X} full 32-bit x86/CFG boundaries not original')
    return native,f676.original_fields(native),lo,hi


def main():
    f696=load('f701_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f701_f699','scripts/verify-fighter-approach-volley-f699.py')
    f676=load('f701_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f701_f598','scripts/verify-fighter-singleton-contact-f598.py')
    reader=load('f701_reader','scripts/compare-coff-function.py')
    acts=load('f701_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    native,real_fields,lo,hi=original_boss_case(reader,pe,real,boss,mapped,f676,
                                                 ACTION,END,ORIGINAL_BYTES,ORIGINAL_X86)
    need(lo==0x0055101E and hi==0x005513C5
         and tuple(i for i,_,_ in real_fields)==NATIVE_FIELD_ORDINALS,
         'original whole 302 native extent/28 physical PE field ordinals cannot be attested')
    native2fa,fields2fa,_,_=original_boss_case(reader,pe,real,boss,mapped,f676,
                                                0x2FA,0x2FB,971,279)
    native2fb,fields2fb,_,_=original_boss_case(reader,pe,real,boss,mapped,f676,
                                                0x2FB,0x302,647,181)
    obj,modules,h=compile_original_full_parent(f696,f699,reader,pe,real,boss,report,mapped)
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    starts=[i for i,x in enumerate(emitted)
            if [y.mnemonic for y in emitted[i:i+3]]==['push']*3
            and [y.op_str for y in emitted[i:i+3]]==['0xff0000','4','3']]
    need(len(starts)==3,'the genuine three separate original storm configure cases 2F9,2FB,302 are absent')
    start,end=starts[-1],starts[-1]+SOURCE_X86
    compiled=emitted[start:end]
    need(len(compiled)==len(native)==ORIGINAL_X86
         and sum(x.size for x in compiled)==SOURCE_BYTES==ORIGINAL_BYTES
         and all(a.size==b.size and a.mnemonic==b.mnemonic for a,b in zip(native,compiled))
         and compiled[0].op_str=='0xff0000'
         and compiled[-1].mnemonic=='jmp',
         'real original complete 935B/261 x86 302 mnemonic and physical instruction extent changed')
    fields=compare_typed_fields(real_fields,compiled,refs,NATIVE_FIELD_SYMBOLS,
                                NATIVE_FIELD_ORDINALS)
    # F596 lvalue expression order fixes each authentic original FLD self-Y
    # followed by physical FADD [0x00658268] (not the compiler's inverse).
    for i in FLOAT_Y_ORDINALS:
        need(native[i].mnemonic==compiled[i].mnemonic=='fld'
             and native[i+1].mnemonic==compiled[i+1].mnemonic=='fadd'
             and '+ 0x48]' in native[i].op_str and '+ 0x48]' in compiled[i].op_str
             and native[i+1].op_str=='dword ptr [0x658268]'
             and compiled[i+1].op_str=='dword ptr [0]',
             f'original 302 volley tier at x86{i} float evaluation / physical PE global ordering changed')
    for i,(original_slot,source_slot) in LOOP_INDEXES.items():
        need(native[i].op_str==f'dword ptr [ebp - {original_slot}], 0'
             and compiled[i].op_str==f'dword ptr [ebp - {source_slot}], 0',
             f'original real tier-loop index x86{i} EBP roles cannot be masked')
    for i,(original_slot,source_slot) in X87_INTEGER_SLOTS.items():
        need(f'[ebp - {original_slot}]' in native[i].op_str
             and f'[ebp - {source_slot}]' in compiled[i].op_str
             and native[i].size==compiled[i].size==6,
             f'original x86{i} true 302 int-to-x87 source/scratch ownership is not native')
    norm=f598.normalized(native),f598.normalized(compiled)
    absolute={i for i,dest,mn in real_fields if mn!='call'}
    wrong=[i for i,(a,b) in enumerate(zip(*norm)) if a!=b and i not in absolute]
    need(len(wrong)==136 and wrong[0]==5,
         f'genuine 302 native GPR/CFG nonfield mismatches changed: {len(wrong)}; never claim strict')
    need(emitted[end].mnemonic=='mov'
         and emitted[end].op_str=='edx, dword ptr [ebp - 0x28]',
         'next original physical native 31B must begin immediately after 935-B source 302')

    # Authentic adjacent previous actions in the SAME freshly compiled
    # giant must be rechecked; their actual EBP displacements can widen.
    prev2fa=emitted[starts[0]+381:starts[1]]
    need(len(prev2fa)==281 and sum(x.size for x in prev2fa)==979,
         'restoring full 302 changed previous native 2FA physical x86 boundaries')
    compare_typed_fields(fields2fa,prev2fa,refs,f699.TARGET_SYMBOLS,
                         f699.ORIGINAL_FIELD_ORDINALS,ordinal_strict=False)
    edits=difflib.SequenceMatcher(a=[x.mnemonic for x in native2fa],
                                  b=[x.mnemonic for x in prev2fa],autojunk=False)
    differences=[(tag,i,j,a,b,[x.mnemonic for x in native2fa[i:j]],
                    [x.mnemonic for x in prev2fa[a:b]])
                 for tag,i,j,a,b in edits.get_opcodes() if tag!='equal']
    need(differences==f699.EXPECTED_OPCODE_EDITS,
         'original previous 2FA 281 source x86/31-field native differences changed')
    need(native2fa[229].op_str=='dword ptr [ebp - 0x1f8], eax'
         and prev2fa[231].op_str=='dword ptr [ebp - 0x8c], edx'
         and native2fa[230].size==prev2fa[232].size==6,
         'original upstream 2FA x87 scratch source ownership and actual wide operands changed')
    prev2fb=emitted[starts[1]:start]
    need(len(prev2fb)==181 and sum(x.size for x in prev2fb)==647,
         'new original 302 changed complete preceding 2FB source beyond observed x87 stack widening')
    compare_typed_fields(fields2fb,prev2fb,refs,f696.EXPECTED_SYMBOLS,
                         f696.ORIGINAL_FIELD_ORDINALS)
    swaps=tuple((i,a.mnemonic,b.mnemonic) for i,(a,b) in enumerate(zip(native2fb,prev2fb))
                if a.mnemonic!=b.mnemonic)
    need(swaps==FOLLOWING_2FB_OPCODE_SWAPS
         and all(a.size==b.size for a,b in zip(native2fb,prev2fb)),
         'authentic previous 2FB 181-x86 now exhibits different original x87 geometry')
    prev2fb_fields={i for i,dest,mn in fields2fb if mn!='call'}
    wrong_prev2fb=[i for i,(a,b) in enumerate(zip(f598.normalized(native2fb),
                                                   f598.normalized(prev2fb)))
                   if a!=b and i not in prev2fb_fields]
    need(len(wrong_prev2fb)==106 and wrong_prev2fb[0]==5,
         'actual preceding full 2FB register role negative incorrectly accepted or changed')

    # Checks the old 27 genuinely strict *inner cases*, negative contexts,
    # independently owned complete afterRET DATA, and exact saved-this
    # identity. The actual extra 302 loops change the compiler frame:
    # source -0x28 (original -0x44), F684 scratch +20 and narrower
    # 2F9 x87 scratch count 12 not 16 (two pairs naturally widen).
    parent=f696.verify_prior_parent_context(
       reader,pe,real,boss,report,mapped,code,refs,modules,h,
       expected_receiver_uses=2527,following_native_2fa=True,
       source_receiver_slot='0x28',source_scratch_slot='0x40',
       source_scratch_shift=32,source_f684_slot_shift=20,
       source_native_302_end_ordinal=end,source_2f9_expected_size=1331,
       source_2f9_wide_ordinals=(78,79,94,95,124,125,151,152,167,168,197,198))
    need(parent['previous_27_nonterminal_context_strict_original_cases_rechecked']
         and parent['original_after_RET_switch_DATA_rechecked_on_this_source']
         and parent['prior_2f9_nonfield_GPR_mismatches']==236
         and parent['prior_terminal_31b_real_gpr_negative']==43,
         'prior full native fighter exact-context and negative evidence regressed')
    summary={
       'original_whole_fighter':'0x00543210',
       'original_whole_CODE_still_NONEXACT':boss['size'],
       'original_separate_afterRET_switch_DATA':boss['postret_size'],
       'native_action':'0x302','native_start':f'0x{lo:08X}',
       'native_next_handler_start':f'0x{hi:08X}',
       'entire_native_CODE_bytes':ORIGINAL_BYTES,
       'entire_source_CODE_bytes':sum(x.size for x in compiled),
       'native_x86_instructions':len(native),
       'source_x86_instructions':len(compiled),
       'identical_whole_case_mnemonic_and_width_positions':len(compiled),
       'all_28_physical_original_typed_PE_COFF_fields_attested':len(fields),
       'authentic_original_float_load_and_global_fadd_order_positions':list(FLOAT_Y_ORDINALS),
       'original_real_different_loop_index_EBP_positions':LOOP_INDEXES,
       'original_real_different_x87_scratch_EBP_positions':X87_INTEGER_SLOTS,
       'genuine_native_nonfield_GPR_CFG_mismatch_count':len(wrong),
       'original_2fa_source_context_compiled_979_bytes_281_x86_31_fields':True,
       'original_2fb_source_context_compiled_647_bytes_181_x86_17_fields':True,
       'original_2fb_genuine_reg_role_mismatches':len(wrong_prev2fb),
       'prior_full_parent_native_verified':parent,
       'entire_case_strict_native':False,
       'entire_boss_exact':False,
       'new_accepted_whole_GAME_FUNCTION_CODE_bytes':0,
    }
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F701 full native boss 00543210 action302: 935 native/935 real VC7.1 source B, '
          '261/261 original mnemonic+width positions, 28/28 original physical typed COFF '
          'fields, all four genuine 6/6/8/8 tier loops. Source read-only float '
          'lvalues fixed four native Y FLD/FADD operand orders, but 136 actual '
          'nonfield GPR/CFG roles and original EBP scratch/index slots differ: '
          'NONSTRICT. Same entire parent rechecks 2FA 281/979/31, 2FB 181/647/17, '
          'earlier 27 strict contextual cases and complete 943-B afterRET DATA. '
          'No false independent case/whole-boss exact credit or full replay.')


if __name__=='__main__':
    main()
