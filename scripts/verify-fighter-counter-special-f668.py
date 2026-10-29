#!/usr/bin/env python3
"""F668: verify genuine native 252/253/254 in selected whole 00543210.

Rebuild exactly ONE complete original-shaped fighter parent using pinned
VC7.1. Strict full-case x86/CFG/width/GPR/typed PE-field proof for three
new source-backed native interiors, all older 19 strict context cases,
three retained scratch negatives and independently owned after-RET DATA.
The enclosing 58K giant remains NONEXACT; no full 943-unit replay.
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
OUT=ROOT/'.analysis/f668-fighter-counter-special'
ACTOR=0x00543210
ACTIONS=(0x252,0x253,0x254)
NEXT={0x252:0x253,0x253:0x254,0x254:0x255}
GEOMETRY={0x252:(72,260),0x253:(72,259),0x254:(63,225)}
FIELD_REFS={
    0x252:{14:(0x00453E20,'call','ResetAt453E20'),
           33:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           41:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           56:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
           64:(0x00453C80,'call','SpawnMixedAt453C80'),
           67:(0x00453D60,'call','PrepareActionAt453D60')},
    0x253:{14:(0x00453E20,'call','ResetAt453E20'),
           33:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           41:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           56:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
           64:(0x00453C80,'call','SpawnMixedAt453C80'),
           67:(0x00453D60,'call','PrepareActionAt453D60')},
    0x254:{14:(0x00453E20,'call','ResetAt453E20'),
           24:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           32:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           47:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
           55:(0x00453C80,'call','SpawnMixedAt453C80'),
           58:(0x00453D60,'call','PrepareActionAt453D60')},
}


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing source '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def physical_original(reader,pe,dec,boss,mapped):
    by={x['action']:int(x['handler'],16) for x in mapped}
    out={}
    for action in ACTIONS:
        lo,hi=by[action],by[NEXT[action]]
        original=list(dec.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        count,length=GEOMETRY[action]
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and len(original)==count and hi-lo==length
             and sum(x.size for x in original)==length
             and original[0].mnemonic=='mov'
             and original[-1].mnemonic=='jmp' and original[-1].op_str=='0x5515c2',
             f'{action:#x}: genuine full original PE case extent/exit differs')
        need(original[9].mnemonic=='mov' and '+ 0x366]' in original[9].op_str
             and original[10].mnemonic=='sub' and original[10].op_str.endswith(', 1')
             and original[62 if action!=0x254 else 53].mnemonic=='push'
             and original[62 if action!=0x254 else 53].op_str=='0x37',
             f'{action:#x}: original signed counter decrement or sprite kind differs')
        if action in (0x252,0x253):
            need(original[24].op_str.endswith('+ 0x3b6]')
                 and original[31].mnemonic=='mov'
                 and original[31].op_str.endswith(', 0x3e8'),
                 f'{action:#x}: genuine original conditional resource-stage reset differs')
        else:
            need(original[23].mnemonic=='mov'
                 and original[24].mnemonic=='call',
                 '0x254 must not invent the 252/253 additional resource predicate')
        for ordinal,(dest,mn,_) in FIELD_REFS[action].items():
            x=original[ordinal]
            expected=f'0x{dest:x}' if mn=='call' else f'dword ptr [0x{dest:x}]'
            need(x.mnemonic==mn and x.op_str==expected,
                 f'{action:#x}: genuine original PE field target {dest:#x} at x86{ordinal} changed')
        out[action]=(original,lo,hi)
    return out


def source_with_special(source):
    declaration='void SpawnRawXYAt453C80(int,int,int,char,int);'
    need(source.count(declaration)==1,'original previous selected parent raw-call declaration absent')
    source=source.replace(declaration,
           declaration+' void SpawnMixedAt453C80(int,int,float,char,int);')
    marker='        case 0x252: g_FighterProbeMarker = 595; break;'
    need(source.count(marker)==1,'physical original 252 source placeholder absent')
    source=source.replace(marker,'#include "FighterCounterSpecialF668.inc"')
    for action in (0x253,0x254):
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(marker)==1,f'physical native {action:#x} source placeholder missing')
        source=source.replace(marker,'')
    need(source.count('        case 0x255: g_FighterProbeMarker = 598; break;')==1,
         'genuine following 255 physical native C++ source marker missing')
    return source


def verify_inner(reader,pe,dec,code,refs,originals,start,original_shared_exit,h):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ordinal=start
    verified=[]
    for action in ACTIONS:
        native,lo,hi=originals[action]
        compiled=ins[ordinal:ordinal+len(native)]
        need(len(compiled)==len(native)
             and compiled[-1].mnemonic=='jmp'
             and compiled[-1].op_str==original_shared_exit
             and all(a.size==b.size for a,b in zip(native,compiled))
             and compiled[-1].address+compiled[-1].size-compiled[0].address==hi-lo,
             f'{action:#x}: native whole physical instruction geometry or shared exit changed')
        physical=[f for f in refs
                  if compiled[0].address<=f['offset']<compiled[-1].address+compiled[-1].size]
        need(len(physical)==len(FIELD_REFS[action]),
             f'{action:#x}: genuine original 6 typed COFF fields count/ownership differs')
        for i,(target,mn,sym) in FIELD_REFS[action].items():
            orig,gen=native[i],compiled[i]
            expected=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(orig.mnemonic==gen.mnemonic==mn and orig.op_str==expected,
                 f'{action:#x}: genuine native original PE destination at ordinal {i} changed')
            field=[f for f in physical if gen.address<=f['offset']<gen.address+gen.size]
            need(len(field)==1 and field[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and field[0]['addend']==0 and field[0]['local_symbol_offset'] is None
                 and sym in field[0]['symbol'],
                 f'{action:#x}: generated real COFF field for original {target:#x} missing')
        lhs,rhs=h['f598'].normalized(native),h['f598'].normalized(compiled)
        absfloat={i for i,(dest,mn,sym) in FIELD_REFS[action].items() if mn!='call'}
        mism=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b and i not in absfloat]
        need(not mism,f'{action:#x}: original native GPR/x87/CFG roles mismatch {mism[:8]}')
        # Old comparator erases arbitrary EBP stack slots, so recheck them
        # independently and accept ONLY original saved-this EBP-44 to new EBP-8.
        raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(native,compiled))
             if i not in absfloat and a.mnemonic!='call'
             and not a.mnemonic.startswith('j')
             and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
        need(not raw,f'{action:#x}: true original raw EBP / nonfield operand mismatch {raw[:8]}')
        verified.append({'original_action':f'0x{action:03X}',
                         'complete_original_native_start':f'0x{lo:08X}',
                         'next_original_native_handler':f'0x{hi:08X}',
                         'real_original_complete_x86_instructions':len(native),
                         'strict_internal_original_CODE_bytes':hi-lo,
                         'original_physical_typed_PE_COFF_fields':len(physical),
                         'new_accepted_whole_function_BYTES':0})
        ordinal+=len(native)
    need(ins[ordinal].mnemonic=='mov' and ins[ordinal].op_str.endswith(', 0x256'),
         'three new actual native 252/253/254 cases must end at original 255 marker')
    return verified


def main():
    f651=load('f668_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f668_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f668_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f668_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f668_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f668_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f668_f664','scripts/verify-fighter-special-stage-f664.py')
    h=f651.load_helpers()
    reader=load('f668_reader','scripts/compare-coff-function.py')
    acts=load('f668_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals=physical_original(reader,pe,dec,boss,mapped)
    prior651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    prior653=f653.native_cases(reader,pe,dec,boss,mapped)
    prior654=f654.original_native(reader,pe,dec,boss,mapped)
    prior656=f656.native_cases(reader,pe,dec,boss,mapped)
    prior657=f657.native_cases(reader,pe,dec,boss,mapped)
    prior661=f661.true_native(reader,pe,dec,boss,mapped)
    prior664=f664.original_cases(reader,pe,dec,boss,mapped)
    source=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
    source=f653.replace_following_cases(source)
    source=f654.source_with_finish(source)
    source=f656.source_with_native_stages(source)
    source=f657.source_with_stage_186_189(source)
    source=f661.parent_source(source)
    source=f664.source_with_cases(source)
    source=source_with_special(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-252-253-254-native.cpp'
    obj=OUT/'Boss00543210-252-253-254-native.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'actual selected full-parent pinned VC7.1 compile failed: '+cp.stderr[-500:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,prior651,h,following_native=0x12C)
    a,ordinal=f653.verify_new(reader,pe,dec,code,refs,old,prior653,h,following_native=0x12F)
    b,ordinal=f654.verify_new(reader,pe,dec,code,refs,prior654,old,ordinal,h,following_native=0x131)
    c,ordinal=f656.verify_native(reader,pe,dec,code,refs,prior656,old,ordinal,h,following_native=0x186)
    d,negative186,ordinal=f657.verify_new(reader,pe,dec,code,refs,prior657,old,ordinal,h,following_native=0x18A)
    negative661=f661.verify_nonstrict(reader,pe,dec,code,refs,prior661,old,ordinal,h)
    strict664,following=f664.verify_new_code(reader,pe,dec,code,refs,boss,mapped,prior664,h,following_native=0x252)
    # Source references from all the previous validators, plus the shared
    # original after-RET compressed switch table, have been rechecked in
    # the SAME newly compiled full parent.
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(following>=len(ins)-len(ins)//2 and ins[following-1].mnemonic=='jmp',
         'original 252 physical follow-on ordinal/previous shared native exit not found')
    shared_exit=ins[old['continuation_source_ordinal']-1].op_str
    strict=verify_inner(reader,pe,dec,code,refs,originals,following,shared_exit,h)
    receipt={'original_selected_giant':'0x00543210',
             'original_entire_parent_CODE_bytes_still_NONEXACT':boss['size'],
             'separately_owned_after_RET_DATA_bytes':boss['postret_size'],
             'all_prior_19_strict_cases_same_full_parent_verified':True,
             'all_prior_original_EBP_negative_controls_remain_NONSTRICT':True,
             'original_complete_after_RET_switch_DATA_verified':True,
             'new_strict_native_original_case_interiors':strict,
             'new_original_strict_internal_CODE_bytes':sum(x['strict_internal_original_CODE_bytes'] for x in strict),
             'new_whole_authored_exact_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F668 selected original whole fighter 00543210: three strict native '
          f'252/253/254 case interiors, {sum(x["real_original_complete_x86_instructions"] for x in strict)} '
          f'original x86, {receipt["new_original_strict_internal_CODE_bytes"]} genuine '
          f'original internal CODE B, {sum(x["original_physical_typed_PE_COFF_fields"] for x in strict)} '
          'real typed PE/COFF fields. All previous 19 strict original cases, '
          'three EBP negatives and full original after-RET switch DATA '
          'rechecked in same fresh parent; whole giant still NONEXACT, '
          'no full authored exact credit or mass cold replay.')


if __name__=='__main__':
    main()
