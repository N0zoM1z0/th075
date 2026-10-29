#!/usr/bin/env python3
"""F664: strict 0x200/0x201 original native fighter action interiors.

Only the one selected complete original 00543210 fighter C++ parent is
freshly compiled under pinned VC7.1. Verify true original case bounds,
all typed genuine PE/COFF call/float fields, GPR/x87/CFG and exact widths,
plus the preceding 17 strict cases, actual 186/18A/18B nonstrict cases
and the complete separated after-RET native switch DATA. Never claim
an independently exact authored whole 58K giant from inner cases.
"""
from __future__ import annotations
import json
import os
from pathlib import Path
import subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f664-fighter-special-stage'
ACTOR=0x00543210
CASES=(0x200,0x201)
NEXT={0x200:0x201,0x201:0x252}
GEOMETRY={0x200:(102,343),0x201:(126,436)}
FIELDS={
    0x200:{9:(0x00453E20,'call','ResetAt453E20'),
           24:(0x00659240,'fsub','g_FallingLateDragAt00659240'),
           29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           44:(0x0040FB40,'call','SetAuxActionAt40FB40'),
           48:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           56:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           67:(0x00453D40,'call','PrepareActionAt453D40'),
           80:(0x00453C80,'call','SpawnRawXYAt453C80')},
    0x201:{9:(0x00453E20,'call','ResetAt453E20'),
           24:(0x00659240,'fsub','g_FallingLateDragAt00659240'),
           29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           44:(0x0040FB40,'call','SetAuxActionAt40FB40'),
           48:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           56:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           67:(0x00453D40,'call','PrepareActionAt453D40'),
           80:(0x00453C80,'call','SpawnRawXYAt453C80'),
          120:(0x0040FB40,'call','SetAuxActionAt40FB40')},
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def original_cases(reader,pe,dec,boss,mapped):
    by={m['action']:int(m['handler'],16) for m in mapped}
    result={}
    for action in CASES:
        lo,hi=by[action],by[NEXT[action]]
        ins=list(dec.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        want_count,want_size=GEOMETRY[action]
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and len(ins)==want_count and hi-lo==want_size
             and sum(x.size for x in ins)==want_size
             and ins[0].mnemonic=='mov' and ins[-1].mnemonic=='jmp'
             and ins[-1].op_str=='0x5515c2',
             f'{action:#x}: complete physical native fighter case extent changed')
        # Case action semantics come from fresh original x86, not inherited
        # from a previous report or from another fighter actor.
        need(ins[20].mnemonic=='cmp' and ins[20].op_str.endswith(', 7')
             and ins[31].mnemonic=='test' and ins[31].op_str=='ah, 5'
             and ins[42].mnemonic=='push' and ins[42].op_str=='8'
             and ins[65].mnemonic=='push' and ins[65].op_str=='7'
             and ins[78].mnemonic=='push' and ins[78].op_str=='0x3c'
             and ins[90].mnemonic=='mov' and '+ 0x50]' in ins[90].op_str,
             f'{action:#x}: authentic native x87 stage motion and raw sprite ABI changed')
        if action==0x201:
            need(ins[103].mnemonic=='cmp' and ins[103].op_str.endswith(', 0xb')
                 and ins[111].mnemonic=='test' and ins[111].op_str.endswith(', edx')
                 and ins[115].mnemonic=='add' and ins[115].op_str.endswith(', 1')
                 and ins[118].mnemonic=='push' and ins[118].op_str=='2',
                 '0x201 extra native stage11 one-shot counter/auxiliary action changed')
        for ordinal,(target,mn,_) in FIELDS[action].items():
            n=ins[ordinal]
            expected=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(n.mnemonic==mn and n.op_str==expected,
                 f'{action:#x}: physical true native PE x86{ordinal} target {target:#x} differs')
        result[action]=(ins,lo,hi)
    return result


def source_with_cases(source):
    decl='void SpawnFloatXYAt453A70(int,float,float,char,int);'
    need(source.count(decl)==1,'current whole parent provisional typed sprite declaration lost')
    source=source.replace(decl,decl+' void SpawnRawXYAt453C80(int,int,int,char,int); void PrepareActionAt453D40(int);')
    start='        case 0x200: g_FighterProbeMarker = 513; break;'
    next_='        case 0x201: g_FighterProbeMarker = 514; break;'
    need(source.count(start)==source.count(next_)==1,
         'original physical 200/201 source placeholders missing')
    source=source.replace(start,'#include "FighterSpecialStageF664.inc"').replace(next_,'')
    need(source.count('        case 0x252: g_FighterProbeMarker = 595; break;')==1,
         'original next distinct native 252 handler missing')
    return source


def verify_new_code(reader,pe,dec,code,refs,boss,mapped,orig,helper,following_native=None):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    # The previously verified 0x1FF original dispatch has a real g_Marker
    # physical source record; don't guess a function-relative ordinal.
    entries=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        i=next((j for j,x in enumerate(ins) if x.address<=f['offset']<x.address+x.size),None)
        if i is not None and ins[i].mnemonic=='mov' and ins[i].op_str.endswith(', 0x200'):
            entries.append(i)
    need(len(entries)==1 and ins[entries[0]+1].mnemonic=='jmp',
         'unique previous 0x1FF original native marker and jump not found')
    position=entries[0]+2
    accepted=[]
    for action in CASES:
        original,lo,hi=orig[action]
        gen=ins[position:position+len(original)]
        need(len(gen)==len(original) and gen[-1].mnemonic=='jmp'
             and gen[-1].op_str==ins[entries[0]+1].op_str
             and all(a.size==b.size for a,b in zip(original,gen))
             and gen[-1].address+gen[-1].size-gen[0].address==hi-lo,
             f'{action:#x}: original entire native CODE geometry / shared exit differs')
        physical=[r for r in refs if gen[0].address<=r['offset']<gen[-1].address+gen[-1].size]
        need(len(physical)==len(FIELDS[action]),
             f'{action:#x}: original real typed PE/COFF field count changed')
        for i,(target,mn,sym) in FIELDS[action].items():
            native,compiled=original[i],gen[i]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(native.mnemonic==compiled.mnemonic==mn and native.op_str==want,
                 f'{action:#x}: original PE-targeted x86 ordinal {i} differs')
            reloc=[f for f in physical if compiled.address<=f['offset']<compiled.address+compiled.size]
            need(len(reloc)==1 and reloc[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and reloc[0]['addend']==0 and reloc[0]['local_symbol_offset'] is None
                 and sym in reloc[0]['symbol'],
                 f'{action:#x}: original PE source target {target:#x} must have true typed COFF field at x86{i}')
        lhs,rhs=helper['f598'].normalized(original),helper['f598'].normalized(gen)
        absfield={i for i,(_,mn,_) in FIELDS[action].items() if mn!='call'}
        mism=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b and i not in absfield]
        need(not mism,f'{action:#x}: true native nonfield GPR/x87/CFG mismatch {mism[:8]}')
        # The previous F598 normalization masks EBP offsets broadly;
        # check every noncall, nonbranch original operand again and permit
        # only the actually known saved receiver slot -0x44 -> -8.
        raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(original,gen))
             if i not in absfield and a.mnemonic!='call'
             and not a.mnemonic.startswith('j')
             and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
        need(not raw,f'{action:#x}: genuine original physical EBP/local operand mismatch {raw[:8]}')
        accepted.append({'original_action':f'0x{action:03X}',
                         'original_entire_native_start':f'0x{lo:08X}',
                         'original_next_native_handler':f'0x{hi:08X}',
                         'entire_original_native_x86_instructions':len(original),
                         'strict_source_backed_entire_case_CODE_bytes':hi-lo,
                         'original_typed_PE_COFF_fields':len(physical),
                         'independent_whole_function_accepted_bytes':0})
        position+=len(original)
    if following_native is None:
        need(ins[position].mnemonic=='mov' and ins[position].op_str.endswith(', 0x253'),
             'new strict 0x201 must end at genuine following 0x252 marker')
    else:
        need(following_native==0x252
             and ins[position].mnemonic=='mov'
             and ins[position].op_str=='edx, dword ptr [ebp - 8]'
             and ins[position+1].mnemonic=='movsx'
             and ins[position+1].op_str=='eax, word ptr [edx + 0x62]',
             'native 0x252 C++ source must physically follow validated 0x201')
    return accepted,position


def main():
    import importlib.util,sys
    def load(name,path):
        spec=importlib.util.spec_from_file_location(name,ROOT/path)
        need(spec is not None and spec.loader is not None,'missing original native source '+str(path))
        mod=importlib.util.module_from_spec(spec);sys.modules[name]=mod;spec.loader.exec_module(mod)
        return mod
    f651=load('f664_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f664_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f664_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f664_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f664_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f664_f661','scripts/verify-fighter-motion-shots-f661.py')
    h=f651.load_helpers()
    reader=load('f664_reader','scripts/compare-coff-function.py')
    acts=load('f664_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={v['action']:int(v['handler'],16) for v in mapped}
    originals=original_cases(reader,pe,dec,boss,mapped)
    prior651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    prior653=f653.native_cases(reader,pe,dec,boss,mapped)
    prior654=f654.original_native(reader,pe,dec,boss,mapped)
    prior656=f656.native_cases(reader,pe,dec,boss,mapped)
    prior657=f657.native_cases(reader,pe,dec,boss,mapped)
    prior661=f661.true_native(reader,pe,dec,boss,mapped)
    source=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
    source=f653.replace_following_cases(source)
    source=f654.source_with_finish(source)
    source=f656.source_with_native_stages(source)
    source=f657.source_with_stage_186_189(source)
    source=f661.parent_source(source)
    source=source_with_cases(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-original-native-200-201.cpp'
    obj=OUT/'Boss00543210-original-native-200-201.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'original pinned VC7.1 whole selected parent compilation failed: '+proc.stderr[-450:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,prior651,h,following_native=0x12C)
    a,idx=f653.verify_new(reader,pe,dec,code,refs,old,prior653,h,following_native=0x12F)
    b,idx=f654.verify_new(reader,pe,dec,code,refs,prior654,old,idx,h,following_native=0x131)
    c,idx=f656.verify_native(reader,pe,dec,code,refs,prior656,old,idx,h,following_native=0x186)
    d,negative186,idx=f657.verify_new(reader,pe,dec,code,refs,prior657,old,idx,h,following_native=0x18A)
    negative661=f661.verify_nonstrict(reader,pe,dec,code,refs,prior661,old,idx,h)
    new,_=verify_new_code(reader,pe,dec,code,refs,boss,mapped,originals,h)
    receipt={'selected_true_giant':'0x00543210',
             'original_entire_parent_CODE_bytes_NONEXACT':boss['size'],
             'separate_after_RET_switch_DATA_bytes':boss['postret_size'],
             'previous_17_strict_native_case_interiors_reverified_in_same_cold_parent':True,
             'previous_186_18A_18B_negative_cases_reverified_in_same_cold_parent':True,
             'previous_18A_18B_negative_count':len(negative661),
             'new_strict_original_native_case_interiors':new,
             'new_strict_original_internal_native_CODE_bytes':sum(x['strict_source_backed_entire_case_CODE_bytes'] for x in new),
             'accepted_additional_whole_authored_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F664 original selected 0x00543210 58K giant: TWO newly strict real '
          f'0x200/0x201 whole native case interiors, {sum(x["entire_original_native_x86_instructions"] for x in new)} '
          f'authentic x86, {receipt["new_strict_original_internal_native_CODE_bytes"]} '
          f'original internal CODE bytes, {sum(x["original_typed_PE_COFF_fields"] for x in new)} '
          'actual PE/COFF source fields; all prior 17 strict inner cases, '
          'the genuine 186/18A/18B negative controls and full afterRET DATA '
          'rechecked in SAME new C++ parent. Whole function NONEXACT, '
          'no independent authored CODE/Oracle acceptance, no 943-unit replay.')


if __name__=='__main__':
    main()
