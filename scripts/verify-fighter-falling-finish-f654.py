#!/usr/bin/env python3
"""F654: genuine 0x12F/0x130 following seven strict cases in fighter 00543210.

Cold-compile only the selected full original C++ parent once; independently
verify all original PE extents/typed COFF references, new case instruction
roles/CFG, preceding strict seven cases and complete separate after-RET DATA.
A source-backed giant interior does NOT earn any whole-function CODE credit.
"""
from __future__ import annotations
import json
import os
from pathlib import Path
import subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f654-fighter-falling-finish'
ACTOR=0x00543210
ACTIONS=(0x12F,0x130)
NEXT={0x12F:0x130,0x130:0x131}
SIZES={0x12F:(82,288),0x130:(79,261)}
FIELDS={
  0x12F:{13:(0x00453E20,'call','ResetAt453E20'),
         28:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
         33:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
         47:(0x00659240,'fsub','g_FallingLateDragAt00659240'),
         52:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
         59:(0x0040FA30,'call','GetNativeActionAt40FA30'),
         67:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
         80:(0x00453D60,'call','PrepareActionAt453D60')},
  0x130:{10:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
         16:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
         37:(0x0040FA30,'call','GetNativeActionAt40FA30'),
         45:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
         56:(0x00453D60,'call','PrepareActionAt453D60'),
         77:(0x00453A70,'call','SpawnDirectedAt453A70')},
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def original_native(reader,pe,decoder,boss,mapped):
    by={x['action']:int(x['handler'],16) for x in mapped}
    result={}
    for action in ACTIONS:
        lo,hi=by[action],by[NEXT[action]]
        n=list(decoder.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        count,size=SIZES[action]
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and hi-lo==size and len(n)==count
             and sum(x.size for x in n)==size
             and n[0].mnemonic=='mov' and n[-1].mnemonic=='jmp'
             and n[-1].op_str=='0x5515c2',
             f'original {action:#x} real physical native extent/exit differs')
        if action==0x12F:
            need(n[24].mnemonic=='cmp' and n[24].op_str.endswith(', 4')
                 and n[43].mnemonic=='cmp' and n[43].op_str.endswith(', 3')
                 and n[77].mnemonic=='mov' and n[77].op_str.endswith(', 0x41c80000')
                 and n[65].mnemonic=='push' and n[65].op_str=='2',
                 'native 0x12F early/late drag, native stage4 impulse or action transition changed')
        else:
            need(n[12].mnemonic=='test' and n[12].op_str=='ah, 0x41'
                 and n[13].mnemonic=='jp' and n[14].op_str=='0xa'
                 and n[18].mnemonic=='mov' and '+ 0x48]' in n[18].op_str
                 and n[65].op_str=='1' and n[75].op_str=='0x339'
                 and n[70].mnemonic=='mov' and '+ 0x48]' in n[70].op_str,
                 'native 0x130 x87 ground collision, raw x/y projectile and bounce state changed')
        for ordinal,(target,mn,_) in FIELDS[action].items():
            instr=n[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(instr.mnemonic==mn and instr.op_str==want,
                 f'original {action:#x} physical original PE x86{ordinal} target {target:#x} differs')
        result[action]=(n,lo,hi)
    return result


def source_with_finish(src):
    old='extern float g_JumpGroundCorrectionAt00658058;'
    need(src.count(old)==1,'original parent global float source declaration absent')
    src=src.replace(old,old+'\nextern float g_FallingLateDragAt00659240;')
    first='        case 0x12F: g_FighterProbeMarker = 304; break;'
    second='        case 0x130: g_FighterProbeMarker = 305; break;'
    need(src.count(first)==1 and src.count(second)==1,
         'real native next 12F and 130 source markers absent')
    src=src.replace(first,'#include "FighterFallingFinishF654.inc"')
    src=src.replace(second,'')
    need(src.count('        case 0x131: g_FighterProbeMarker = 306; break;')==1,
         'real following 0x131 original source handler missing')
    return src


def verify_new(reader,pe,dec,code,refs,originals,old,earlier,h,following_native=None):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    offset=earlier
    result=[]
    for action in ACTIONS:
        original,lo,hi=originals[action]
        gen=ins[offset:offset+len(original)]
        need(len(gen)==len(original) and gen[-1].mnemonic=='jmp'
             and gen[-1].op_str==ins[old['continuation_source_ordinal']-1].op_str
             and all(a.size==b.size for a,b in zip(original,gen))
             and gen[-1].address+gen[-1].size-gen[0].address==hi-lo,
             f'{action:#x}: complete original native instruction count, geometry or shared exit changed')
        fields=[f for f in refs if gen[0].address<=f['offset']<gen[-1].address+gen[-1].size]
        need(len(fields)==len(FIELDS[action]),
             f'{action:#x}: original native PE/COFF fields count not fully preserved')
        for ordinal,(target,mn,sym) in FIELDS[action].items():
            n,g=original[ordinal],gen[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(n.mnemonic==g.mnemonic==mn and n.op_str==want,
                 f'{action:#x}: original real PE-targeted native x86{ordinal} differs')
            actual=[f for f in fields if g.address<=f['offset']<g.address+g.size]
            need(len(actual)==1 and actual[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and actual[0]['addend']==0
                 and actual[0]['local_symbol_offset'] is None
                 and sym in actual[0]['symbol'],
                 f'{action:#x}: missing real original native symbol/typed physical PE/COFF at x86{ordinal}')
        lhs,rhs=h['f598'].normalized(original),h['f598'].normalized(gen)
        absolute_float={i for i,(target,mn,sym) in FIELDS[action].items() if mn!='call'}
        mismatches=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs))
                    if a!=b and i not in absolute_float]
        need(not mismatches,f'{action:#x}: native original non-field GPR/x87/CFG differences: {mismatches[:10]}')
        result.append({'original_action':f'0x{action:X}',
                       'complete_native_start':f'0x{lo:08X}',
                       'complete_native_next':f'0x{hi:08X}',
                       'real_original_native_x86_instructions':len(original),
                       'real_original_native_internal_CODE_bytes':hi-lo,
                       'true_PE_targeted_typed_COFF_fields':len(fields),
                       'new_credited_whole_function_bytes':0})
        offset+=len(original)
    if following_native is None:
        need(ins[offset].mnemonic=='mov' and ins[offset].op_str.endswith(', 0x132'),
             'case 0x130 must physically end before original following 0x131 marker')
    else:
        need(following_native==0x131 and ins[offset].mnemonic=='mov'
             and ins[offset].op_str=='ecx, dword ptr [ebp - 8]'
             and ins[offset+1].mnemonic=='mov'
             and ins[offset+1].op_str=='edx, dword ptr [ebp - 8]',
             'native 0x131 must immediately follow 0x130 in generated whole original giant')
    return result,offset


def main():
    from importlib.util import spec_from_file_location,module_from_spec
    import sys
    def load(name,path):
        spec=spec_from_file_location(name,ROOT/path)
        need(spec is not None and spec.loader is not None,'missing source '+str(path))
        m=module_from_spec(spec);sys.modules[name]=m;spec.loader.exec_module(m);return m
    f651=load('f654_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f654_f653','scripts/verify-fighter-falling-recovery-f653.py')
    h=f651.load_helpers()
    reader=load('f654_reader','scripts/compare-coff-function.py')
    acts=load('f654_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    new_native=original_native(reader,pe,dec,boss,mapped)
    old_native={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    f653_native=f653.native_cases(reader,pe,dec,boss,mapped)
    src=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
    src=f653.replace_following_cases(src)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-nine-consecutive-native-cases.cpp'
    obj=OUT/'Boss00543210-nine-consecutive-native-cases.obj'
    cpp.write_text(source_with_finish(src))
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'pinned VC7.1 entire parent source failed: '+proc.stderr[-500:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,old_native,h,following_native=0x12C)
    strict_653,following=f653.verify_new(reader,pe,dec,code,refs,old,f653_native,h,following_native=0x12F)
    strict,_=verify_new(reader,pe,dec,code,refs,new_native,old,following,h)
    result={'original_parent':'0x00543210','original_entire_parent_CODE_bytes':boss['size'],
            'original_parent_still_NONEXACT':True,'complete_after_RET_jump_DATA_bytes':boss['postret_size'],
            'same_new_parent_all_prior_CF_D0_D1_D2_12C_12D_12E_strict_and_after_RET':True,
            'preceding_12C_12D_12E_strict_count':len(strict_653),
            'new_strict_native_case_interiors':strict,
            'new_strict_original_native_inner_CODE_bytes':sum(x['real_original_native_internal_CODE_bytes'] for x in strict),
            'new_accepted_independent_whole_game_function_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F654 selected whole fighter 00543210: 0x12F+0x130 fully strict '
          f'original {sum(x["real_original_native_x86_instructions"] for x in strict)} x86, '
          f'{result["new_strict_original_native_inner_CODE_bytes"]} internal CODE B, '
          f'{sum(x["true_PE_targeted_typed_COFF_fields"] for x in strict)} typed physical PE/COFF fields; '
          'seven preceding original cases and full afterRET DATA strict in SAME cold parent; '
          'entire 58K giant remains nonexact; no whole-function credit or mass cold replay.')


if __name__=='__main__':
    main()
