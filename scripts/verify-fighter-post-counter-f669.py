#!/usr/bin/env python3
"""F669: three more strict complete native action cases 255/256/257.

Rebuild ONLY one selected 00543210 full original-shaped VC7.1 parent,
validate all earlier strict original case bodies and original after-RET
switch DATA, then each complete new physical native PE case instruction
and genuine zero-addend typed PE/COFF field. Giant still whole-NONEXACT.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f669-fighter-post-counter'
ACTOR=0x00543210
ACTIONS=(0x255,0x256,0x257)
NEXT={0x255:0x256,0x256:0x257,0x257:0x258}
GEOMETRY={0x255:(72,248),0x256:(52,176),0x257:(72,248)}
FIELD_REFS={
  0x255:{9:(0x00453E20,'call','ResetAt453E20'),
         19:(0x0040FA30,'call','GetNativeActionAt40FA30'),
         27:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
         42:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
         50:(0x00453C80,'call','SpawnMixedAt453C80'),
         70:(0x0040FB40,'call','SetAuxActionAt40FB40')},
  0x256:{9:(0x00453E20,'call','ResetAt453E20'),
         19:(0x0040FA30,'call','GetNativeActionAt40FA30'),
         27:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
         42:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
         50:(0x00453C80,'call','SpawnMixedAt453C80')},
  0x257:{9:(0x00453E20,'call','ResetAt453E20'),
         19:(0x0040FA30,'call','GetNativeActionAt40FA30'),
         27:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
         42:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
         50:(0x00453C80,'call','SpawnMixedAt453C80'),
         70:(0x0040FB40,'call','SetAuxActionAt40FB40')},
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing original source '+str(path))
    mod=importlib.util.module_from_spec(spec);sys.modules[name]=mod;spec.loader.exec_module(mod)
    return mod


def original_native(reader,pe,decoder,boss,mapped):
    by={r['action']:int(r['handler'],16) for r in mapped}
    native={}
    for action in ACTIONS:
        lo,hi=by[action],by[NEXT[action]]
        ins=list(decoder.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        length,size=GEOMETRY[action]
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and len(ins)==length and hi-lo==size
             and sum(x.size for x in ins)==size
             and ins[0].mnemonic=='mov'
             and ins[-1].mnemonic=='jmp' and ins[-1].op_str=='0x5515c2',
             f'{action:#x}: actual original whole native extent/exit changed')
        need(ins[9].mnemonic=='call' and ins[9].op_str=='0x453e20'
             and ins[25].mnemonic=='push' and ins[25].op_str=='9'
             and ins[30].mnemonic=='cmp' and ins[30].op_str.endswith(', 5')
             and ins[41].mnemonic=='fld' and '+ 0x48]' in ins[41].op_str
             and ins[42].mnemonic=='fadd' and ins[42].op_str=='dword ptr [0x657888]'
             and ins[48].mnemonic=='push' and ins[48].op_str=='0x37',
             f'{action:#x}: genuine stage-5 sprite, raw x/float y and stage exit changed')
        if action!=0x256:
            need(ins[53].mnemonic=='cmp' and ins[53].op_str.endswith(', 8')
                 and ins[61].mnemonic=='cmp' and ins[61].op_str.endswith(', 1')
                 and ins[65].mnemonic=='add' and ins[65].op_str.endswith(', 1')
                 and ins[68].mnemonic=='push' and ins[68].op_str=='6',
                 f'{action:#x}: original stage-8 one-shot short counter/aux stage differs')
        for ordinal,(target,mn,_) in FIELD_REFS[action].items():
            insn=ins[ordinal]
            expected=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(insn.mnemonic==mn and insn.op_str==expected,
                 f'{action:#x}: original true PE-targeted native x86{ordinal} field differs')
        native[action]=(ins,lo,hi)
    return native


def add_native_cases(source):
    original='        case 0x255: g_FighterProbeMarker = 598; break;'
    need(source.count(original)==1,'original physical 255 case marker missing')
    source=source.replace(original,'#include "FighterPostCounterF669.inc"')
    for a in (0x256,0x257):
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        need(source.count(marker)==1,f'original physical {a:#x} source marker missing')
        source=source.replace(marker,'')
    need(source.count('        case 0x258: g_FighterProbeMarker = 601; break;')==1,
         'genuine next original native 258 physical case marker missing')
    return source


def verify_native(reader,pe,decoder,code,refs,originals,start,shared_exit,h):
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ordinal=start
    verified=[]
    for action in ACTIONS:
        native,lo,hi=originals[action]
        gen=ins[ordinal:ordinal+len(native)]
        need(len(gen)==len(native) and gen[-1].mnemonic=='jmp'
             and gen[-1].op_str==shared_exit
             and all(a.size==b.size for a,b in zip(native,gen))
             and gen[-1].address+gen[-1].size-gen[0].address==hi-lo,
             f'{action:#x}: physical original whole CODE geometry or native shared exit differs')
        physical=[f for f in refs if gen[0].address<=f['offset']<gen[-1].address+gen[-1].size]
        need(len(physical)==len(FIELD_REFS[action]),
             f'{action:#x}: original true typed PE/COFF count/ownership not preserved')
        for i,(target,mn,sym) in FIELD_REFS[action].items():
            a,b=native[i],gen[i]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
                 f'{action:#x}: native real original PE target at x86{i} differs')
            field=[r for r in physical if b.address<=r['offset']<b.address+b.size]
            need(len(field)==1 and field[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and field[0]['addend']==0 and field[0]['local_symbol_offset'] is None
                 and sym in field[0]['symbol'],
                 f'{action:#x}: real PE source x86{i} typed original COFF relocation missing')
        norm_native,norm_compiled=h['f598'].normalized(native),h['f598'].normalized(gen)
        floats={i for i,(target,mn,symbol) in FIELD_REFS[action].items() if mn!='call'}
        bad=[(i,a,b) for i,(a,b) in enumerate(zip(norm_native,norm_compiled)) if a!=b and i not in floats]
        need(not bad,f'{action:#x}: genuine original native GPR/x87/CFG instruction role mismatch {bad[:8]}')
        raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(native,gen))
             if i not in floats and a.mnemonic!='call'
             and not a.mnemonic.startswith('j')
             and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
        need(not raw,f'{action:#x}: original raw EBP local/operand roles differ {raw[:8]}')
        verified.append({'original_native_action':f'0x{action:03X}',
                         'actual_native_original_start':f'0x{lo:08X}',
                         'actual_original_next_handler':f'0x{hi:08X}',
                         'original_whole_native_x86_instructions':len(native),
                         'strict_real_original_internal_CODE_bytes':hi-lo,
                         'actual_original_typed_PE_COFF_fields':len(physical),
                         'accepted_new_whole_authored_function_CODE_bytes':0})
        ordinal+=len(native)
    need(ins[ordinal].mnemonic=='mov' and ins[ordinal].op_str.endswith(', 0x259'),
         'new native 257 body must physically end before original 258 marker')
    return verified


def main():
    f651=load('f669_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f669_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f669_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f669_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f669_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f669_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f669_f664','scripts/verify-fighter-special-stage-f664.py')
    f668=load('f669_f668','scripts/verify-fighter-counter-special-f668.py')
    h=f651.load_helpers()
    reader=load('f669_reader','scripts/compare-coff-function.py')
    acts=load('f669_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original=original_native(reader,pe,dec,boss,mapped)
    n651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    n653=f653.native_cases(reader,pe,dec,boss,mapped)
    n654=f654.original_native(reader,pe,dec,boss,mapped)
    n656=f656.native_cases(reader,pe,dec,boss,mapped)
    n657=f657.native_cases(reader,pe,dec,boss,mapped)
    n661=f661.true_native(reader,pe,dec,boss,mapped)
    n664=f664.original_cases(reader,pe,dec,boss,mapped)
    n668=f668.physical_original(reader,pe,dec,boss,mapped)
    source=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
    source=f653.replace_following_cases(source)
    source=f654.source_with_finish(source)
    source=f656.source_with_native_stages(source)
    source=f657.source_with_stage_186_189(source)
    source=f661.parent_source(source)
    source=f664.source_with_cases(source)
    source=f668.source_with_special(source)
    source=add_native_cases(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-strict-255-256-257.cpp'
    obj=OUT/'Boss00543210-strict-255-256-257.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'pinned VC7.1 original complete parent compile failed: '+proc.stderr[-450:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,n651,h,following_native=0x12C)
    a,idx=f653.verify_new(reader,pe,dec,code,refs,old,n653,h,following_native=0x12F)
    b,idx=f654.verify_new(reader,pe,dec,code,refs,n654,old,idx,h,following_native=0x131)
    c,idx=f656.verify_native(reader,pe,dec,code,refs,n656,old,idx,h,following_native=0x186)
    d,neg186,idx=f657.verify_new(reader,pe,dec,code,refs,n657,old,idx,h,following_native=0x18A)
    neg661=f661.verify_nonstrict(reader,pe,dec,code,refs,n661,old,idx,h)
    ok664,idx=f664.verify_new_code(reader,pe,dec,code,refs,boss,mapped,n664,h,following_native=0x252)
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    shared=ins[old['continuation_source_ordinal']-1].op_str
    ok668,idx=f668.verify_inner(reader,pe,dec,code,refs,n668,idx,shared,h,following_native=0x255)
    verified=verify_native(reader,pe,dec,code,refs,original,idx,shared,h)
    receipt={'real_selected_fighter_giant':'0x00543210',
             'whole_parent_CODE_bytes_still_NONEXACT':boss['size'],
             'original_after_RET_independent_DATA_bytes':boss['postret_size'],
             'all_previous_22_strict_original_cases_verified_same_new_parent':True,
             'three_actual_original_EBP_scratch_cases_remain_NONSTRICT':True,
             'full_original_afterRET_switch_DATA_reverified':True,
             'new_strict_native_cases':verified,
             'original_new_strict_internal_CODE_bytes':sum(r['strict_real_original_internal_CODE_bytes'] for r in verified),
             'new_accepted_whole_function_authored_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F669 original entire selected giant 00543210: three newly strict '
          f'complete 255/256/257 native cases, {sum(x["original_whole_native_x86_instructions"] for x in verified)} '
          f'original x86, {receipt["original_new_strict_internal_CODE_bytes"]} native internal CODE B, '
          f'{sum(x["actual_original_typed_PE_COFF_fields"] for x in verified)} genuine typed PE/COFF fields. '
          'All preceding 22 context-strict cases, 3 EBP negatives and entire afterRET DATA '
          'rechecked in SAME freshly compiled full parent; giant whole NONEXACT, '
          'no new authored exact function/bytes or full replay.')


if __name__=='__main__':
    main()
