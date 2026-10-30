#!/usr/bin/env python3
"""F699: inspect original whole 2FA action with true 2FB following in full boss.

Freshly build ONE 00543210 native-shaped VC7.1 C++ TU; compare the
entire original native 971-B, 279-x86 action and its 31 physical PE/COFF
fields. Keep actual x87/CFG and downstream 2FB stack-negative evidence.
All previous 27 strictly backed nonterminal native cases and after-RET
943-byte switch data must remain valid in the SAME full parent.
This is not an independent callable function or byte-exact adoption.
"""
from __future__ import annotations
import difflib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f699-fighter-approach-volley'
ACTOR=0x00543210
ACTION=0x2FA
NEXT=0x2FB
END=0x302
NATIVE_SIZE=971
NATIVE_X86=279
COMPILED_SIZE=973
COMPILED_X86=281
ORIGINAL_FIELD_ORDINALS=(9,24,36,43,48,51,64,74,83,96,101,107,
                         117,127,139,151,153,156,164,176,180,197,199,
                         206,216,223,237,244,252,260,277)
TARGET_SYMBOLS={
    0x00453E20:'ResetAt453E20',
    0x0040FAC0:'SetNativeActionAt40FAC0',
    0x00454EE0:'ContactAt454EE0',
    0x0040FB40:'SetAuxActionAt40FB40',
    0x0040FA30:'GetNativeActionAt40FA30',
    0x00412D90:'F699AbsAt00412D90',
    0x00455580:'RandomBoundaryAt455580',
    0x00453D40:'PrepareActionAt453D40',
    0x00453C80:'At453C80',
    0x0065782C:'g_ThresholdAt0065782C',
    0x00658058:'g_JumpGroundCorrectionAt00658058',
    0x00657874:'g_F699_SideOffsetAt00657874',
    0x00657884:'g_F699_SideEdgeAt00657884',
    0x0065787C:'g_F699_DistanceAt0065787C',
    0x006714D0:'g_CloudOpponentAt006714D0',
    0x00657888:'g_ContactProjectionAt00657888',
}
EXPECTED_OPCODE_EDITS=[
    ('replace',46,47,46,47,['jp'],['jne']),
    ('replace',110,111,110,111,['jp'],['jne']),
    ('replace',129,130,129,131,['fcomp'],['fld','fcompp']),
    ('replace',141,142,142,144,['fcomp'],['fld','fcompp']),
    ('insert',191,191,193,194,[],['fld']),
    ('delete',193,194,196,196,['fld'],[]),
    ('replace',202,203,204,205,['jp'],['jne']),
]


def need(ok, message):
    if not ok:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing original checker '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def native_case(reader,pe,real,boss,mapped,fields_tool,action,next_action,size,nx):
    by={x['action']:int(x['handler'],16) for x in mapped}
    lo,hi=by[action],by[next_action]
    ins=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
    need(boss['address']<lo<hi<boss['address']+boss['size']
         and hi-lo==size and len(ins)==nx
         and ins[-1].mnemonic=='jmp' and ins[-1].op_str=='0x5515c2',
         f'original action 0x{action:X} entire CODE boundary invalid')
    return ins,fields_tool.original_fields(ins),lo,hi


def source_with_2fa(prior):
    old='        case 0x2FA: g_FighterProbeMarker = 763; break;'
    need(prior.count(old)==1,'the original source-backed 2FB parent lost its native 2FA placeholder')
    src=prior.replace(old,'#include "FighterApproachVolleyF699.inc"')
    decl='extern float g_ThresholdAt0065782C;'
    need(src.count(decl)==1,'genuine original threshold declaration missing')
    src=src.replace(decl,decl+'\n'
      'extern float g_F699_SideOffsetAt00657874;\n'
      'extern float g_F699_SideEdgeAt00657884;\n'
      'extern float g_F699_DistanceAt0065787C;\n'
      'extern "C" float __cdecl F699AbsAt00412D90(float);')
    need(src.count('#include "FighterGroundedVolleyF696.inc"')==1
         and src.count('#include "FighterAngleStormF684.inc"')==1,
         '2FA C++ must be embedded between original native 2F9 and original 2FB source')
    return src


def full_case_fields(refs,original,source,original_fields,want):
    refs_in=[r for r in refs if source[0].address<=r['offset']
             <source[-1].address+source[-1].size]
    need(len(refs_in)==len(original_fields)==want,
         'entire real native case PE/COFF physical field ownership changed')
    for (ordinal,target,mn),r in zip(original_fields,refs_in):
        need(target in TARGET_SYMBOLS and r['type']==('REL32' if mn=='call' else 'DIR32')
             and r['addend']==0 and r['local_symbol_offset'] is None
             and TARGET_SYMBOLS[target] in r['symbol'],
             f'original native PE x86{ordinal} target {target:#x} cannot be attributed to typed source field')
        owner=[k for k,x in enumerate(source)
               if x.address<=r['offset']<x.address+x.size]
        need(len(owner)==1 and source[owner[0]].mnemonic==mn,
             f'original native PE x86{ordinal}: compiled field is not owned by equivalent original instruction')
    return refs_in


def main():
    f696=load('f699_f696','scripts/verify-fighter-grounded-volley-f696.py')
    reader=load('f699_reader','scripts/compare-coff-function.py')
    f676=load('f699_fields','scripts/verify-fighter-cloud-burst-f676.py')
    acts=load('f699_acts','scripts/report-fighter-action-handlers.py')
    f598=load('f699_f598','scripts/verify-fighter-singleton-contact-f598.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    native,original_fields,lo,hi=native_case(reader,pe,real,boss,mapped,f676,
                                                   ACTION,NEXT,NATIVE_SIZE,NATIVE_X86)
    need(lo==0x005509CC and hi==0x00550D97
         and len(original_fields)==len(ORIGINAL_FIELD_ORDINALS)
         and tuple(i for i,_,_ in original_fields)==ORIGINAL_FIELD_ORDINALS,
         'true original 2FA whole 279-x86/31-field extent or field ordinals changed')
    native2fb,fields2fb,lo2fb,hi2fb=native_case(reader,pe,real,boss,mapped,f676,
                                                 NEXT,END,647,181)
    source,deps,h=f696.source_for_entire_parent(reader,pe,real,boss,report,mapped)
    source=source_with_2fa(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-2FA.cpp'
    obj=OUT/'Boss00543210-2FA.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,text=True,capture_output=True,timeout=220)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,'pinned serial VC7.1 full 58KB parent compile failed: '+result.stderr[-650:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    ins=[]
    for x in real.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    configs=[i for i,x in enumerate(ins) if
             [y.mnemonic for y in ins[i:i+3]]==['push','push','push']
             and [y.op_str for y in ins[i:i+3]]==['0xff0000','4','3']]
    need(len(configs)==2,'two original source-backed 2F9 and 2FB storm prologues required')
    begin=configs[0]+381
    end=configs[-1]
    candidate=ins[begin:end]
    need(len(candidate)==COMPILED_X86 and sum(x.size for x in candidate)==COMPILED_SIZE
         and candidate[0].mnemonic=='mov'
         and candidate[0].op_str=='edx, dword ptr [ebp - 0x18]'
         and candidate[-1].mnemonic=='jmp',
         'new original 2FA action actual complete compiled native shape wrong')
    field_source=full_case_fields(refs,native,candidate,original_fields,len(ORIGINAL_FIELD_ORDINALS))
    seq=difflib.SequenceMatcher(a=[x.mnemonic for x in native],
                                b=[x.mnemonic for x in candidate],autojunk=False)
    differences=[(tag,i,j,a,b,[x.mnemonic for x in native[i:j]],
                    [x.mnemonic for x in candidate[a:b]])
                 for tag,i,j,a,b in seq.get_opcodes() if tag!='equal']
    need(differences==EXPECTED_OPCODE_EDITS,
         f'original real opcode differences changed, do not claim strict/exact: {differences}')
    # The case has two real C++ floating expression evaluation-order extra
    # FLD+FCOMPP comparisons; do not erase those distinct native instructions.
    need(native[129].mnemonic==native[141].mnemonic=='fcomp'
         and [(candidate[i].mnemonic,candidate[i+1].mnemonic)
              for i in (129,142)]==[('fld','fcompp')]*2,
         'original 2FA float comparison geometry improperly normalized')
    need(native[229].op_str=='dword ptr [ebp - 0x1f8], eax'
         and native[230].op_str=='dword ptr [ebp - 0x1f8]'
         and candidate[231].op_str=='dword ptr [ebp - 0x7c], edx'
         and candidate[232].op_str=='dword ptr [ebp - 0x7c]',
         'actual original/sourced 2FA integer-to-float scratch EBP roles changed')
    # New 2FA is immediately followed by the genuine prior 2FB source.
    next_marker=next((i for i in range(end,len(ins)) if ins[i].mnemonic=='mov'
                      and ins[i].op_str.endswith(', 0x303')),None)
    need(next_marker is not None,'complete native 2FB source/next 302 marker missing')
    next_source=ins[end:next_marker]
    need(len(next_source)==len(native2fb)==181 and sum(x.size for x in next_source)==641
         and next_source[-1].mnemonic==candidate[-1].mnemonic=='jmp'
         and candidate[-1].op_str==next_source[-1].op_str,
         'new 2FA C++ silently changed complete following original 2FB shared exit or x86 geometry')
    need([(i,a.mnemonic,b.mnemonic) for i,(a,b) in enumerate(zip(native2fb,next_source))
          if a.mnemonic!=b.mnemonic]
         ==[(64,'mov','fld'),(65,'fld','mov'),(75,'mov','fld'),(76,'fld','mov')],
         'true following original 2FB has new unreported x87 opcode differences')
    next_fields=[r for r in refs if next_source[0].address<=r['offset']<next_source[-1].address+next_source[-1].size]
    need(len(next_fields)==len(fields2fb)==17
         and all(a['type']==('REL32' if m=='call' else 'DIR32')
                 and a['addend']==0 and a['local_symbol_offset'] is None
                 for a,(_,target,m) in zip(next_fields,fields2fb)),
         'all 17 original following 2FB typed original fields regressed')
    need(sum(a!=b for a,b in zip(f598.normalized(native2fb),f598.normalized(next_source)))==109,
         'new 2FA C++ changed honest downstream 2FB 109 mismatched GPR/CFG roles')
    old=f696.verify_prior_parent_context(reader,pe,real,boss,report,mapped,code,refs,deps,h,
                    expected_receiver_uses=2468,following_native_2fa=True)
    need(old['previous_27_nonterminal_context_strict_original_cases_rechecked']
         and old['original_after_RET_switch_DATA_rechecked_on_this_source']
         and old['prior_2f9_nonfield_GPR_mismatches']==236
         and old['prior_terminal_31b_real_gpr_negative']==43,
         'actual prior original case/afterRET proof regressed in new full parent')
    receipt={
       'original_whole_fighter_boss_entry':f'0x{ACTOR:08X}',
       'original_complete_boss_CODE_bytes_NONEXACT':boss['size'],
       'original_complete_boss_afterRET_DATA_bytes':boss['postret_size'],
       'original_full_native_2FA_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
       'original_true_2FA_x86':len(native),
       'source_full_original_case_x86':len(candidate),
       'original_2FA_full_CODE_bytes':NATIVE_SIZE,
       'source_2FA_full_CODE_bytes':sum(x.size for x in candidate),
       'original_typed_PE_COFF_fields_verified_in_order':len(field_source),
       'genuine_opcode_edits':differences,
       'full_original_next_2FB_native_CODE_bytes':hi2fb-lo2fb,
       'new_source_next_2FB_full_x86':len(next_source),
       'new_source_next_2FB_CODE_bytes':sum(x.size for x in next_source),
       'next_2FB_original_typed_fields_rechecked':len(next_fields),
       'previous_strict_and_nonstrict_original_context':old,
       'strict_2FA_inner_case':False,
       'entire_original_boss_exact':False,
       'accepted_new_whole_game_FUNCTION_CODE_bytes':0,
    }
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F699 newly recovered whole native action2FA 971 original CODE B/279 x86 '
          '/31 physically typed original PE/COFF fields; fresh native-shaped '
          '58KB parent emits 973 B/281 x86 and 31/31 matching symbol fields: '
          'NONSTRICT (two extra FLD/FCOMPP operations, genuine branch/GPR '
          'and stack-order differences). Following original 2FB remains 181 '
          'x86/17 fields but source changed 635->641 B. Previous 27 strict '
          'context cases, negative controls and 943-byte afterRET DATA '
          'rechecked. No whole CODE acceptance or full cold replay.')


if __name__=='__main__':
    main()
