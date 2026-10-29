#!/usr/bin/env python3
"""F656: five real native late stages 0x131/0x133-0x136 in giant 00543210.

Compiles ONE genuine whole-parent VC7.1 C++ probe, with all nine earlier
CF/D0/D1/D2/12C/12D/12E/12F/130 handlers. Verifies each complete
native case extent, x86/CFG/GPR/x87 and all real typed COFF fields,
then all original after-RET switch DATA. No whole-boss exact credit.
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
OUT=ROOT/'.analysis/f656-fighter-native-late-stages'
ACTOR=0x00543210
ACTIONS=(0x131,0x133,0x134,0x135,0x136)
NEXT={0x131:0x133,0x133:0x134,0x134:0x135,0x135:0x136,0x136:0x186}
SIZES={0x131:(81,280),0x133:(110,370),0x134:(61,219),0x135:(102,349),0x136:(80,266)}
# Real native instruction ordinal -> (original physical PE target,
# true x86 mnemonic, exact generated physical COFF symbol).
FIELDS={
    0x131:{10:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           16:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           37:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           45:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           56:(0x00453D60,'call','PrepareActionAt453D60'),
           79:(0x00453D60,'call','PrepareActionAt453D60')},
    0x133:{20:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           26:(0x006581E0,'fsub','g_NewDragAt006581E0'),
           31:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           38:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           46:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           57:(0x00453D60,'call','PrepareActionAt453D60'),
           70:(0x00453A70,'call','SpawnDirectedAt453A70'),
           91:(0x00453D60,'call','PrepareActionAt453D60'),
          108:(0x00453A70,'call','SpawnDirectedAt453A70')},
    0x134:{13:(0x00453E20,'call','ResetAt453E20'),
           24:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
           29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           38:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           46:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           59:(0x00453D60,'call','PrepareActionAt453D60')},
    0x135:{13:(0x00453E20,'call','ResetAt453E20'),
           24:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
           29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           47:(0x00657478,'fsub','g_SubtractAt00657478'),
           52:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           59:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           67:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
          100:(0x00453A70,'call','SpawnDirectedAt453A70')},
    0x136:{13:(0x00453E20,'call','ResetAt453E20'),
           24:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
           29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           38:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           46:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           67:(0x00453A70,'call','SpawnDirectedAt453A70'),
           78:(0x00453D60,'call','PrepareActionAt453D60')},
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing original native source '+str(path))
    m=importlib.util.module_from_spec(spec);sys.modules[name]=m;spec.loader.exec_module(m)
    return m


def native_cases(reader,pe,decoder,boss,mapped):
    by={r['action']:int(r['handler'],16) for r in mapped}
    need(by[0x132]==by[0x50] and by[0x132]!=by[0x133],
         '0x132 is original DEFAULT handler, not a new physical native case')
    results={}
    for action in ACTIONS:
        first,last=by[action],by[NEXT[action]]
        n=list(decoder.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        count,size=SIZES[action]
        need(boss['address']<first<last<boss['address']+boss['size']
             and len(n)==count and last-first==size
             and sum(x.size for x in n)==size
             and n[0].mnemonic=='mov' and n[-1].mnemonic=='jmp'
             and n[-1].op_str=='0x5515c2',
             f'{action:#x} true native original full physical handler bounds/exit differ')
        # Validate independently observed native case semantics, not merely
        # a shape copied from another actor/handler.
        if action==0x131:
            need(n[12].op_str=='ah, 0x41' and n[54].op_str=='0x1c'
                 and n[59].op_str.endswith(', 5') and n[71].op_str.endswith(', 6')
                 and n[77].op_str=='0x1d',
                 'original 131: real floor test, stage3/5/6 transitions changed')
        elif action==0x133:
            need(n[22].op_str=='ah, 0x41' and n[23].mnemonic=='jne'
                 and n[55].op_str=='0x1c' and n[68].op_str=='0x341'
                 and n[80].op_str.endswith(', 0x41700000')
                 and n[89].op_str=='0x1c' and n[106].op_str=='0x342',
                 'original 133: stage3/6/8 two projectile native transitions changed')
        elif action==0x134:
            need(n[48].mnemonic=='mov' and '+ 0xf00]' in n[48].op_str
                 and n[51].op_str.endswith(', 1') and n[57].op_str=='0x1d',
                 'original 134: stage1 and true extra flag-clear changed')
        elif action==0x135:
            need(n[39].op_str.endswith(', 0xa') and n[43].op_str.endswith(', 0xb')
                 and n[79].op_str.endswith(', 0x41a00000')
                 and n[98].op_str=='0x33f',
                 'original 135: stage7 impulse and stage10 0x33F projectile changed')
        else:
            need(n[49].op_str.endswith(', 5') and n[65].op_str=='0x33e'
                 and n[70].op_str.endswith(', 6') and n[76].op_str=='0x1d',
                 'original 136: native stage5 0x33E shot and stage6 animation changed')
        for ordinal,(target,mn,_) in FIELDS[action].items():
            x=n[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(x.mnemonic==mn and x.op_str==want,
                 f'{action:#x}: original physical PE native field x86{ordinal} {target:#x} changed')
        results[action]=(n,first,last)
    return results


def source_with_native_stages(src):
    decl='extern float g_FallingLateDragAt00659240;'
    need(src.count(decl)==1,'full giant source native original float declarations missing')
    src=src.replace(decl,decl+'\nextern float g_NewDragAt006581E0;')
    a='        case 0x131: g_FighterProbeMarker = 306; break;'
    b='        case 0x133: g_FighterProbeMarker = 308; break;'
    need(src.count(a)==src.count(b)==1,'real original 131/133 physical native markers missing')
    src=src.replace(a,'#include "FighterLateGroundF656.inc"')
    src=src.replace(b,'#include "FighterLateShotsF656.inc"')
    for action in (0x134,0x135,0x136):
        mark=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(mark)==1,f'original 0x{action:X} physical native marker missing')
        src=src.replace(mark,'')
    need(src.count('        case 0x186: g_FighterProbeMarker = 391; break;')==1,
         'true next physical native handler 186 is absent')
    return src


def verify_native(reader,pe,dec,code,refs,originals,older,next_ordinal,h):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    offset=next_ordinal
    strict=[]
    for action in ACTIONS:
        n,first,last=originals[action]
        gen=ins[offset:offset+len(n)]
        need(len(gen)==len(n) and gen[-1].mnemonic=='jmp'
             and gen[-1].op_str==ins[older['continuation_source_ordinal']-1].op_str
             and all(x.size==y.size for x,y in zip(n,gen))
             and gen[-1].address+gen[-1].size-gen[0].address==last-first,
             f'{action:#x}: full original native length/CFG/shared-exit geometry wrong')
        physical=[f for f in refs if gen[0].address<=f['offset']<gen[-1].address+gen[-1].size]
        need(len(physical)==len(FIELDS[action]),
             f'{action:#x}: true native PE fields physical ownership differs')
        for ordinal,(target,mn,symbol) in FIELDS[action].items():
            original,compiled=n[ordinal],gen[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(original.mnemonic==compiled.mnemonic==mn and original.op_str==want,
                 f'{action:#x}: physical original native PE-targeted instruction ordinal {ordinal} differs')
            actual=[f for f in physical if compiled.address<=f['offset']<compiled.address+compiled.size]
            need(len(actual)==1
                 and actual[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and actual[0]['addend']==0 and actual[0]['local_symbol_offset'] is None
                 and symbol in actual[0]['symbol'],
                 f'{action:#x}: original genuine typed PE-targeted COFF field x86{ordinal} differs')
        lhs,rhs=h['f598'].normalized(n),h['f598'].normalized(gen)
        absfields={i for i,(_,mn,_) in FIELDS[action].items() if mn!='call'}
        mismatch=[(i,x,y) for i,(x,y) in enumerate(zip(lhs,rhs))
                  if x!=y and i not in absfields]
        need(not mismatch,
             f'{action:#x}: non-field original native GPR/x87/CFG register roles differ: {mismatch[:8]}')
        strict.append({'original_native_action':f'0x{action:03X}',
                       'original_complete_physical_start':f'0x{first:08X}',
                       'original_complete_physical_next':f'0x{last:08X}',
                       'original_complete_x86_instructions':len(n),
                       'original_entire_internal_CODE_bytes':last-first,
                       'physically_typed_PE_COFF_fields':len(physical),
                       'accepted_whole_independent_function_bytes':0})
        offset+=len(n)
    need(ins[offset].mnemonic=='mov' and ins[offset].op_str.endswith(', 0x187'),
         'last genuine native 0x136 must end before next physical handler 0x186 marker')
    return strict


def main():
    f651=load('f656_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f656_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f656_f654','scripts/verify-fighter-falling-finish-f654.py')
    h=f651.load_helpers()
    reader=load('f656_reader','scripts/compare-coff-function.py')
    acts=load('f656_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    native=native_cases(reader,pe,dec,boss,mapped)
    native_651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    native_653=f653.native_cases(reader,pe,dec,boss,mapped)
    native_654=f654.original_native(reader,pe,dec,boss,mapped)
    src=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
    src=f653.replace_following_cases(src)
    src=f654.source_with_finish(src)
    src=source_with_native_stages(src)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-fourteen-real-native-stages.cpp'
    obj=OUT/'Boss00543210-fourteen-real-native-stages.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'genuine pinned VC7.1 complete selected parent failed: '+proc.stderr[-600:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,native_651,h,following_native=0x12C)
    prev653,start654=f653.verify_new(reader,pe,dec,code,refs,old,native_653,h,following_native=0x12F)
    prev654,start656=f654.verify_new(reader,pe,dec,code,refs,native_654,old,start654,h,following_native=0x131)
    strict=verify_native(reader,pe,dec,code,refs,native,old,start656,h)
    result={'original_selected_giant':'0x00543210',
            'whole_original_parent_CODE_bytes_still_NONEXACT':boss['size'],
            'separately_owned_original_after_RET_switch_DATA_bytes':boss['postret_size'],
            'same_recompiled_parent_CF_D0_D1_D2_12C_12D_12E_12F_130_strict_and_after_RET':True,
            'previous_strict_653_cases':len(prev653),'previous_strict_654_cases':len(prev654),
            'original_0x132_is_default_handler_not_separate_case':True,
            'new_strict_native_case_interiors':strict,
            'new_strict_original_native_internal_CODE_bytes':sum(x['original_entire_internal_CODE_bytes'] for x in strict),
            'accepted_new_whole_original_authored_FUNCTION_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F656 original giant 00543210: five complete native 131/133/134/135/136 interiors '
          f'{sum(x["original_complete_x86_instructions"] for x in strict)} original x86, '
          f'{result["new_strict_original_native_internal_CODE_bytes"]} original inner CODE B, '
          f'{sum(x["physically_typed_PE_COFF_fields"] for x in strict)} genuine typed PE/COFF fields; '
          '9 prior strict cases and entire afterRET jump DATA rechecked in SAME new complete '
          'parent COFF. Native 132 is default, not separate physical handler. '
          'Whole giant remains NONEXACT, no independent CODE credit or full cold replay.')


if __name__=='__main__':
    main()
