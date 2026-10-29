#!/usr/bin/env python3
"""F673: strict entire original physical 0x2BC fighter ground-wave case.

Only one original-shaped 00543210 giant VC7.1 parent is newly compiled.
Verify full true 692-byte native 208-x86 case extent, every one of its
20 typed original PE/COFF fields, non-relocation GPR/x87 and raw stack
roles; all prior 25 context-strict native cases, actual 186/18A/18B/258
EBP negatives and full after-RET compressed switch DATA in same object.
No whole-parent exact acceptance, no all-943 cold replay.
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
OUT=ROOT/'.analysis/f673-fighter-ground-wave'
ACTOR=0x00543210
ACTION=0x2BC
NEXT=0x2BF
ORIGINAL_X86=208
ORIGINAL_BYTES=692
FIELDS={
     13:(0x00453E20,'call','ResetAt453E20'),
     16:(0x00657888,'fsub','g_ContactProjectionAt00657888'),
     21:(0x00453E80,'call','InitTrajectoryAt453E80'),
     24:(0x00453D60,'call','PrepareActionAt453D60'),
     31:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
     39:(0x00453C80,'call','SpawnMixedAt453C80'),
     50:(0x00659888,'fsub','g_FallDecelerationAt00659888'),
     55:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
     79:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
     85:(0x0040FB40,'call','SetAuxActionAt40FB40'),
     97:(0x00453E60,'call','InitTrajectoryAt453E60'),
     99:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    107:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    138:(0x00453A70,'call','SpawnDirectedAt453A70'),
    149:(0x00453A70,'call','SpawnDirectedAt453A70'),
    152:(0x0046D000,'call','StartAnimationAt46D000'),
    155:(0x00453D40,'call','PrepareActionAt453D40'),
    170:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    190:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    206:(0x0040FB40,'call','SetAuxActionAt40FB40'),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing source '+str(path))
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def actual_native(reader,pe,dec,boss,mapped):
    by={entry['action']:int(entry['handler'],16) for entry in mapped}
    lo,hi=by[ACTION],by[NEXT]
    native=list(dec.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
    need(boss['address']<lo<hi<boss['address']+boss['size']
         and hi-lo==ORIGINAL_BYTES and len(native)==ORIGINAL_X86
         and sum(x.size for x in native)==ORIGINAL_BYTES
         and native[0].mnemonic=='mov'
         and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
         'genuine original 0x2BC full PE native case geometry/exit changed')
    # Independently observed large native stage and branch behavior, not
    # just a compiler object that happens to have 208 instructions.
    need(native[9].op_str=='word ptr [ecx + 0xf00], 0'
         and native[19].op_str=='0x28'
         and native[22].op_str=='0x17'
         and native[37].op_str=='0x73'
         and native[42].op_str.endswith(', 3')
         and native[46].op_str.endswith(', 0xb')
         and native[63].op_str.endswith(', 0xa')
         and native[67].op_str.endswith(', 0xe')
         and native[95].op_str=='0x40000000'
         and native[117].op_str.endswith(', 0x41700000')
         and native[119].op_str.endswith(', 0x3f59999a')
         and native[136].op_str=='0x326'
         and native[147].op_str=='0x33b'
         and native[150].op_str=='0x1f4'
         and native[153].op_str=='8'
         and native[166].op_str.endswith(', 7')
         and native[186].op_str.endswith(', 9')
         and native[204].op_str=='0xc',
         'original large 2BC multi-stage movement, shot and short-counter roles changed')
    for ordinal,(dest,mn,_) in FIELDS.items():
        x=native[ordinal]
        want=f'0x{dest:x}' if mn=='call' else f'dword ptr [0x{dest:x}]'
        need(x.mnemonic==mn and x.op_str==want,
             f'original real PE target {dest:#x} at 2BC x86{ordinal} changed')
    return native,lo,hi


def source_with_groundwave(source):
    decl='void InitTrajectoryAt453E60(float);'
    need(source.count(decl)==1,'current full fighter source native trajectory decl missing')
    source=source.replace(decl,decl+' void InitTrajectoryAt453E80(int);')
    g='extern float g_ContactProjectionAt00657888;'
    need(source.count(g)==1,'actual selected full parent native float global declaration missing')
    source=source.replace(g,g+'\nextern float g_FallDecelerationAt00659888;')
    marker='        case 0x2BC: g_FighterProbeMarker = 701; break;'
    need(source.count(marker)==1,'actual original physical native 2BC source placeholder missing')
    source=source.replace(marker,'#include "FighterGroundWaveF673.inc"')
    need(source.count('        case 0x2BF: g_FighterProbeMarker = 704; break;')==1,
         'next physical native 2BF source marker missing')
    return source


def verify_groundwave(reader,dec,code,refs,native,shared_exit,h):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    # Marker 25D is deliberately an unresolved native predecessor in
    # this selected source context. Its unique physical previous MOV
    # and shared-exit JMP anchor original source case 2BC exactly.
    marks=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        i=next((j for j,x in enumerate(ins) if x.address<=f['offset']<x.address+x.size),None)
        if i is not None and ins[i].mnemonic=='mov' and ins[i].op_str.endswith(', 0x25e'):
            marks.append(i)
    need(len(marks)==1 and ins[marks[0]+1].mnemonic=='jmp',
         'original source previous native 25D placeholder not unique')
    pos=marks[0]+2
    original,lo,hi=native
    gen=ins[pos:pos+len(original)]
    need(len(gen)==ORIGINAL_X86 and gen[-1].mnemonic=='jmp'
         and gen[-1].op_str==shared_exit
         and all(a.size==b.size for a,b in zip(original,gen))
         and gen[-1].address+gen[-1].size-gen[0].address==ORIGINAL_BYTES,
         'original whole 2BC native x86 count, width, exit or 692-byte geometry differs')
    physical=[f for f in refs if gen[0].address<=f['offset']<gen[-1].address+gen[-1].size]
    need(len(physical)==len(FIELDS),
         'all twenty actual PE/COFF field owners in original 2BC required')
    for ordinal,(target,mn,symbol) in FIELDS.items():
        a,b=original[ordinal],gen[ordinal]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
             f'2BC original native physical target at x86{ordinal} differs')
        found=[f for f in physical if b.address<=f['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and symbol in found[0]['symbol'],
             f'original 2BC true PE-targeted COFF symbol/field at x86{ordinal} differs')
    left,right=h['f598'].normalized(original),h['f598'].normalized(gen)
    absolutes={i for i,(target,mn,symbol) in FIELDS.items() if mn!='call'}
    wrong=[(i,a,b) for i,(a,b) in enumerate(zip(left,right)) if a!=b and i not in absolutes]
    need(not wrong,f'original 2BC true GPR/x87/CFG operand role differs: {wrong[:7]}')
    # The F598 matcher masks all EBP offsets: independently disallow
    # unbacked stack-local changes, except the verified saved receiver.
    raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(original,gen))
         if i not in absolutes and a.mnemonic!='call'
         and not a.mnemonic.startswith('j')
         and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
    need(not raw,f'original 2BC non-field raw EBP/local operand mismatch: {raw[:8]}')
    need(ins[pos+ORIGINAL_X86].mnemonic=='mov'
         and ins[pos+ORIGINAL_X86].op_str.endswith(', 0x2c0'),
         'true following native 2BF placeholder must immediately follow original 2BC')
    return {'actual_original_native_action':'0x2BC',
            'original_complete_PE_start':f'0x{lo:08X}',
            'original_physical_next_handler':f'0x{hi:08X}',
            'original_whole_native_x86_count':len(original),
            'source_strict_original_internal_CODE_bytes':hi-lo,
            'real_original_typed_PE_COFF_fields':len(physical),
            'new_accepted_whole_authored_FUNCTION_CODE_bytes':0}


def main():
    f651=load('f673_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f673_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f673_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f673_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f673_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f673_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f673_f664','scripts/verify-fighter-special-stage-f664.py')
    f668=load('f673_f668','scripts/verify-fighter-counter-special-f668.py')
    f669=load('f673_f669','scripts/verify-fighter-post-counter-f669.py')
    f671=load('f673_f671','scripts/verify-fighter-four-shot-barrage-f671.py')
    h=f651.load_helpers()
    reader=load('f673_reader','scripts/compare-coff-function.py')
    acts=load('f673_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original=actual_native(reader,pe,dec,boss,mapped)
    old651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    old653=f653.native_cases(reader,pe,dec,boss,mapped)
    old654=f654.original_native(reader,pe,dec,boss,mapped)
    old656=f656.native_cases(reader,pe,dec,boss,mapped)
    old657=f657.native_cases(reader,pe,dec,boss,mapped)
    old661=f661.true_native(reader,pe,dec,boss,mapped)
    old664=f664.original_cases(reader,pe,dec,boss,mapped)
    old668=f668.physical_original(reader,pe,dec,boss,mapped)
    old669=f669.original_native(reader,pe,dec,boss,mapped)
    old671=f671.original_case(reader,pe,dec,boss,mapped)
    source=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
    source=f653.replace_following_cases(source)
    source=f654.source_with_finish(source)
    source=f656.source_with_native_stages(source)
    source=f657.source_with_stage_186_189(source)
    source=f661.parent_source(source)
    source=f664.source_with_cases(source)
    source=f668.source_with_special(source)
    source=f669.add_native_cases(source)
    source=f671.source_with_barrage(source)
    source=source_with_groundwave(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-original-2BC-ground-wave.cpp'
    obj=OUT/'Boss00543210-original-2BC-ground-wave.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned VC7.1 selected full original giant compile failed: '+cp.stderr[-550:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,old651,h,following_native=0x12C)
    a,idx=f653.verify_new(reader,pe,dec,code,refs,old,old653,h,following_native=0x12F)
    b,idx=f654.verify_new(reader,pe,dec,code,refs,old654,old,idx,h,following_native=0x131)
    c,idx=f656.verify_native(reader,pe,dec,code,refs,old656,old,idx,h,following_native=0x186)
    d,negative186,idx=f657.verify_new(reader,pe,dec,code,refs,old657,old,idx,h,following_native=0x18A)
    negative661=f661.verify_nonstrict(reader,pe,dec,code,refs,old661,old,idx,h)
    ok664,idx=f664.verify_new_code(reader,pe,dec,code,refs,boss,mapped,old664,h,following_native=0x252)
    wholeins=[]
    for x in dec.disasm(code,0):
        wholeins.append(x)
        if x.mnemonic=='ret':break
    shared=wholeins[old['continuation_source_ordinal']-1].op_str
    ok668,idx=f668.verify_inner(reader,pe,dec,code,refs,old668,idx,shared,h,following_native=0x255)
    ok669,idx=f669.verify_native(reader,pe,dec,code,refs,old669,idx,shared,h,following_native=0x258)
    negative671=f671.verify_negative(reader,pe,dec,code,refs,old671,idx,shared,h)
    new=verify_groundwave(reader,dec,code,refs,original,shared,h)
    receipt={'original_selected_giant':'0x00543210',
             'original_entire_whole_parent_CODE_bytes_still_NONEXACT':boss['size'],
             'original_separate_after_RET_switch_DATA_bytes':boss['postret_size'],
             'all_previous_25_context_strict_original_cases_verified_in_same_new_parent':True,
             'all_previous_original_186_18A_18B_258_nonexact_scratch_controls_verified':True,
             'entire_original_after_RET_dispatch_DATA_verified':True,
             'new_strict_complete_original_native_case':new,
             'new_strict_internal_CODE_bytes':new['source_strict_original_internal_CODE_bytes'],
             'new_accepted_entire_authored_game_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F673 selected whole original giant 00543210: new strictly source-backed '
          f'0x2BC entire physical handler {new["original_whole_native_x86_count"]} real x86, '
          f'{new["source_strict_original_internal_CODE_bytes"]} genuine original inner CODE B, '
          f'{new["real_original_typed_PE_COFF_fields"]} genuine PE/COFF fields; '
          'all previous 25 strict original cases, 186/18A/18B/258 real EBP negatives '
          'and full independent after-RET DATA rechecked in SAME newly compiled '
          'full parent. Enclosing 58K giant is NONEXACT, zero new independently '
          'accepted authored CODE, no 943-unit mass replay.')


if __name__=='__main__':
    main()
