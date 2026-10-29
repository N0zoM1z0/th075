#!/usr/bin/env python3
"""F672: five complete original 259..25D source-backed NONSTRICT cases.

Cold-build ONE complete original-shaped 00543210 C++ fighter parent.
Check genuine original physical case intervals, 434 whole native x86
roles, 42 real zero-addend typed PE/COFF fields, exactly 24 physical
integer-to-float EBP scratch instruction mismatches. In the same new
parent recheck 25 earlier strict cases, original 258/186/18A/18B EBP
negatives, strict 2BC ground-wave and full after-RET switch DATA.
Never accept these five native interiors or whole enclosing giant exact.
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
OUT=ROOT/'.analysis/f672-fighter-eight-shot-source'
ACTOR=0x00543210
CASES=(0x259,0x25A,0x25B,0x25C,0x25D)
NEXT={0x259:0x25A,0x25A:0x25B,0x25B:0x25C,0x25C:0x25D,0x25D:0x2BC}
GEOMETRY={0x259:(210,733,685,20),0x25A:(60,198,192,6),
          0x25B:(60,198,192,6),0x25C:(52,170,164,5),
          0x25D:(52,170,164,5)}
# Real native EBP scratch ownership, not a magic width mask.
SLOTS={
  0x259:{47:('0x124','0x3c'),48:('0x124','0x3c'),
         68:('0x128','0x40'),69:('0x128','0x40'),
         91:('0x12c','0x44'),92:('0x12c','0x44'),
        112:('0x130','0x48'),113:('0x130','0x48'),
        135:('0x134','0x4c'),136:('0x134','0x4c'),
        156:('0x138','0x50'),157:('0x138','0x50'),
        179:('0x13c','0x54'),180:('0x13c','0x54'),
        200:('0x140','0x58'),201:('0x140','0x58')},
  0x25A:{40:('0x144','0x5c'),41:('0x144','0x5c')},
  0x25B:{40:('0x148','0x60'),41:('0x148','0x60')},
  0x25C:{32:('0x14c','0x64'),33:('0x14c','0x64')},
  0x25D:{32:('0x150','0x68'),33:('0x150','0x68')},
}
SYMBOLS={
  0x00453E20:'ResetAt453E20',0x0040FA30:'GetNativeActionAt40FA30',
  0x0040FAC0:'SetNativeActionAt40FAC0',0x0046D000:'StartAnimationAt46D000',
  0x00453A70:'SpawnFloatXYAt453A70',
  0x006591F8:'g_EightShotY0At006591F8',
  0x00658264:'g_EightShotY1At00658264',
  0x0065908C:'g_BarrageY3At0065908C',
  0x00658268:'g_EightShotY2At00658268',
  0x00657F74:'g_BounceScaleAt00657F74',
  0x00657888:'g_ContactProjectionAt00657888',
  0x0065928C:'g_OneShotYAt0065928C',
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing original source '+str(path))
    mod=importlib.util.module_from_spec(spec);sys.modules[name]=mod;spec.loader.exec_module(mod)
    return mod


def original_fields(native):
    result=[]
    for i,x in enumerate(native):
        if x.mnemonic=='call' and re.fullmatch(r'0x[0-9a-f]+',x.op_str):
            result.append((i,int(x.op_str,16),'call'))
        elif x.mnemonic.startswith('f') and re.fullmatch(r'dword ptr \[0x[0-9a-f]+\]',x.op_str):
            result.append((i,int(x.op_str.split('[0x')[1][:-1],16),x.mnemonic))
    return result


def original_cases(reader,pe,dec,boss,mapped):
    by={m['action']:int(m['handler'],16) for m in mapped}
    cases={}
    for a in CASES:
        lo,hi=by[a],by[NEXT[a]]
        native=list(dec.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        count,orig_size,source_size,ref_count=GEOMETRY[a]
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and hi-lo==orig_size and len(native)==count
             and sum(x.size for x in native)==orig_size
             and native[0].mnemonic=='mov'
             and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
             f'original {a:#x} full physical native case extent/exit changed')
        fields=original_fields(native)
        need(len(fields)==ref_count and all(target in SYMBOLS for i,target,mn in fields),
             f'{a:#x} original genuine actual PE field targets/count changed')
        if a==0x259:
            need(native[30].op_str=='0xfa'
                 and [native[i].op_str for i in (53,74,97,118,141,162,185,206)]
                      ==['0x321','0x322']*4,
                 'native original 259 stage5 actual eight-shot original resource pattern changed')
        elif a in (0x25A,0x25B):
            need(native[10].mnemonic=='fmul' and native[15].mnemonic=='fmul'
                 and native[46].op_str==('0x32b' if a==0x25A else '0x32d'),
                 f'native {a:#x} actual bounce-scale/one-shot semantics changed')
        else:
            need(native[11].mnemonic=='call' and native[11].op_str=='0x453e20'
                 and native[38].op_str==('0x332' if a==0x25C else '0x333'),
                 f'native {a:#x} stage5 shot kind or reset semantic changed')
        cases[a]=(native,lo,hi,fields)
    return cases


def source_with_cases(source):
    decl='extern float g_BarrageY3At0065908C;'
    need(source.count(decl)==1,'authentic previous 258 full parent float declarations missing')
    source=source.replace(decl,decl+('\\nextern float g_EightShotY0At006591F8;\\n'
                                     'extern float g_EightShotY1At00658264;\\n'
                                     'extern float g_EightShotY2At00658268;\\n'
                                     'extern float g_OneShotYAt0065928C;').replace('\\n','\n'))
    first='        case 0x259: g_FighterProbeMarker = 602; break;'
    need(source.count(first)==1,'true original native 259 source marker missing')
    source=source.replace(first,'#include "FighterEightShotAndFollowF672.inc"')
    for a in (0x25A,0x25B,0x25C,0x25D):
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        need(source.count(marker)==1,f'original true physical {a:#x} marker missing')
        source=source.replace(marker,'')
    need(source.count('#include "FighterGroundWaveF673.inc"')==1,
         'true source-backed original 2BC ground wave must follow these native cases')
    return source


def verify_nonstrict(reader,dec,code,refs,originals,start,shared,h):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ordinal=start
    receipts=[]
    for action in CASES:
        native,lo,hi,fields=originals[action]
        generated=ins[ordinal:ordinal+len(native)]
        count,orig_bytes,gen_bytes,nfields=GEOMETRY[action]
        need(len(generated)==count
             and sum(x.size for x in generated)==gen_bytes
             and generated[-1].mnemonic=='jmp'
             and generated[-1].op_str==shared,
             f'{action:#x}: original whole native instruction count/compiled geometry or exit changed')
        physical=[f for f in refs if generated[0].address<=f['offset']<generated[-1].address+generated[-1].size]
        need(len(physical)==len(fields)==nfields,
             f'{action:#x}: actual original PE/COFF field count and ownership changed')
        for i,target,mn in fields:
            a,b=native[i],generated[i]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
                 f'{action:#x}: actual native PE-targeted original x86{i} changed')
            reloc=[f for f in physical if b.address<=f['offset']<b.address+b.size]
            need(len(reloc)==1 and reloc[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and reloc[0]['addend']==0 and reloc[0]['local_symbol_offset'] is None
                 and SYMBOLS[target] in reloc[0]['symbol'],
                 f'{action:#x}: true source COFF symbol/typed field for original PE {target:#x} wrong')
        wrong_widths=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,generated))
                      if a.size!=b.size]
        need(wrong_widths==[(i,6,3) for i in SLOTS[action]],
             f'{action:#x}: expected authentic EBP wide local conversion width differences changed {wrong_widths}')
        ln,rn=h['f598'].normalized(native),h['f598'].normalized(generated)
        abs_fields={i for i,t,mn in fields if mn!='call'}
        mismatches=[(i,a,b) for i,(a,b) in enumerate(zip(ln,rn))
                    if a!=b and i not in abs_fields]
        need(not mismatches,
             f'{action:#x}: original non-field register/x87/branch roles changed {mismatches[:8]}')
        # Broad F598 normalization masks ALL EBP slots. Independently
        # prove the original meaningful source conversion differences.
        raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(native,generated))
             if i not in abs_fields and a.mnemonic!='call'
             and not a.mnemonic.startswith('j')
             and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
        need([i for i,a,b in raw]==list(SLOTS[action])
             and all(f'[ebp - {original_slot}]' in native[i].op_str
                     and f'[ebp - {generated_slot}]' in generated[i].op_str
                     for i,(original_slot,generated_slot) in SLOTS[action].items()),
             f'{action:#x}: real original physical EBP scratch mismatch pattern changed: {raw[:8]}')
        receipts.append({'original_native_action':f'0x{action:03X}',
                         'original_real_physical_start':f'0x{lo:08X}',
                         'original_real_next_handler':f'0x{hi:08X}',
                         'complete_original_native_x86_count':len(native),
                         'original_native_complete_inner_CODE_bytes':hi-lo,
                         'normal_CPP_generated_internal_CODE_bytes':gen_bytes,
                         'real_typed_PE_COFF_fields':len(physical),
                         'original_genuine_EBP_scratch_wrong_ordinals':list(SLOTS[action]),
                         'strict_original_native_case':False,
                         'whole_GAME_FUNCTION_CODE_accepted_bytes':0})
        ordinal+=len(native)
    need(ins[ordinal].mnemonic=='mov'
         and ins[ordinal].op_str=='eax, dword ptr [ebp - 8]'
         and ins[ordinal+1].mnemonic=='movsx'
         and ins[ordinal+1].op_str=='ecx, word ptr [eax + 0x62]',
         'actual original 2BC ground wave body must immediately follow 25D')
    return receipts,ordinal


def main():
    f651=load('f672_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f672_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f672_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f672_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f672_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f672_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f672_f664','scripts/verify-fighter-special-stage-f664.py')
    f668=load('f672_f668','scripts/verify-fighter-counter-special-f668.py')
    f669=load('f672_f669','scripts/verify-fighter-post-counter-f669.py')
    f671=load('f672_f671','scripts/verify-fighter-four-shot-barrage-f671.py')
    f673=load('f672_f673','scripts/verify-fighter-ground-wave-f673.py')
    h=f651.load_helpers()
    reader=load('f672_reader','scripts/compare-coff-function.py')
    acts=load('f672_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals=original_cases(reader,pe,dec,boss,mapped)
    n651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    n653=f653.native_cases(reader,pe,dec,boss,mapped)
    n654=f654.original_native(reader,pe,dec,boss,mapped)
    n656=f656.native_cases(reader,pe,dec,boss,mapped)
    n657=f657.native_cases(reader,pe,dec,boss,mapped)
    n661=f661.true_native(reader,pe,dec,boss,mapped)
    n664=f664.original_cases(reader,pe,dec,boss,mapped)
    n668=f668.physical_original(reader,pe,dec,boss,mapped)
    n669=f669.original_native(reader,pe,dec,boss,mapped)
    n671=f671.original_case(reader,pe,dec,boss,mapped)
    n673=f673.actual_native(reader,pe,dec,boss,mapped)
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
    source=f673.source_with_groundwave(source)
    source=source_with_cases(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-259-through-25D-native-negative.cpp'
    obj=OUT/'Boss00543210-259-through-25D-native-negative.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned VC7.1 full original-shaped fighter source compile failed: '+cp.stderr[-500:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,n651,h,following_native=0x12C)
    _,idx=f653.verify_new(reader,pe,dec,code,refs,old,n653,h,following_native=0x12F)
    _,idx=f654.verify_new(reader,pe,dec,code,refs,n654,old,idx,h,following_native=0x131)
    _,idx=f656.verify_native(reader,pe,dec,code,refs,n656,old,idx,h,following_native=0x186)
    _,neg186,idx=f657.verify_new(reader,pe,dec,code,refs,n657,old,idx,h,following_native=0x18A)
    neg661=f661.verify_nonstrict(reader,pe,dec,code,refs,n661,old,idx,h)
    _,idx=f664.verify_new_code(reader,pe,dec,code,refs,boss,mapped,n664,h,following_native=0x252)
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    shared=ins[old['continuation_source_ordinal']-1].op_str
    _,idx=f668.verify_inner(reader,pe,dec,code,refs,n668,idx,shared,h,following_native=0x255)
    _,idx=f669.verify_native(reader,pe,dec,code,refs,n669,idx,shared,h,following_native=0x258)
    neg671,idx=f671.verify_negative(reader,pe,dec,code,refs,n671,idx,shared,h,following_native=0x259)
    negative,idx=verify_nonstrict(reader,dec,code,refs,originals,idx,shared,h)
    strict673=f673.verify_groundwave(reader,dec,code,refs,n673,shared,h,start_ordinal=idx)
    receipt={'original_selected_giant':'0x00543210',
             'whole_original_parent_CODE_bytes_still_NONEXACT':boss['size'],
             'entire_separate_after_RET_original_switch_DATA_bytes':boss['postret_size'],
             'all_25_earlier_context_strict_original_cases_reverified':True,
             'original_complex_258_four_shot_EBP_negative_reverified':True,
             'four_earlier_original_EBP_scratch_negative_controls_preserved':True,
             'original_2BC_large_ground_wave_strict_in_same_source_context':True,
             'entire_original_afterRET_switch_DATA_preserved':True,
             'five_new_nonexact_original_native_stage_259_through_25D_bodies':negative,
             'real_original_source_backed_nonexact_inner_CODE_bytes':sum(x['original_native_complete_inner_CODE_bytes'] for x in negative),
             'new_strict_native_case_bodies':0,
             'new_accepted_whole_authored_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F672 original whole selected giant 00543210: five complete native '
          f'259/25A/25B/25C/25D source-backed but NONSTRICT cases, '
          f'{sum(x["complete_original_native_x86_count"] for x in negative)} genuine original x86, '
          f'{receipt["real_original_source_backed_nonexact_inner_CODE_bytes"]} original case CODE bytes, '
          f'{sum(x["real_typed_PE_COFF_fields"] for x in negative)} authentic original PE/COFF fields; '
          'exactly 24 genuine EBP integer-to-float scratch operands wrong, '
          'no added strict/native whole credit. All 25 earlier strict cases, '
          'original EBP negatives, 2BC strict case and complete afterRET '
          'DATA reverified in SAME fresh VC7.1 parent. No 943-unit replay.')


if __name__=='__main__':
    main()
