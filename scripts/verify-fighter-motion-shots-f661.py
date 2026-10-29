#!/usr/bin/env python3
"""F661: original giant 00543210 native shot 18A/18B, NONSTRICT EBP temps.

Compile ONE selected full normal VC7.1 fighter parent, check all 17
previous strict case interiors and after-RET DATA in the SAME object,
and independently prove the two genuine 18A/18B source-backed *negative*
whole case comparisons. No credit without the original EBP -88/-8C.
"""
from __future__ import annotations
import json
import os
from pathlib import Path
import subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f661-fighter-motion-shots'
ACTOR=0x00543210
ACTIONS=(0x18A,0x18B)
NEXT={0x18A:0x18B,0x18B:0x190}
SIZES={0x18A:(71,256,250,61,62,'0x88','0x24'),
       0x18B:(99,359,353,89,90,'0x8c','0x28')}
FIELDS={
    0x18A:{18:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
           23:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           32:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           40:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           55:(0x0065929C,'fadd','g_YPlusAt0065929C'),
           69:(0x00453A70,'call','SpawnFloatXYAt453A70')},
    0x18B:{22:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
           27:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           36:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           44:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
           64:(0x0040FB40,'call','SetAuxActionAt40FB40'),
           83:(0x00658400,'fadd','g_YPlusAt00658400'),
           97:(0x00453A70,'call','SpawnFloatXYAt453A70')},
}


def need(ok,why):
    if not ok:raise ValueError(why)


def true_native(reader,pe,decoder,boss,mapped):
    by={row['action']:int(row['handler'],16) for row in mapped}
    result={}
    for action in ACTIONS:
        lo,hi=by[action],by[NEXT[action]]
        n=list(decoder.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        count,size,_,scratch1,scratch2,origslot,_=SIZES[action]
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and hi-lo==size and len(n)==count and sum(x.size for x in n)==size
             and n[-1].mnemonic=='jmp' and n[-1].op_str=='0x5515c2',
             f'original {action:#x} complete physical native bounds/exit differ')
        need(n[scratch1].mnemonic=='mov' and f'[ebp - {origslot}]' in n[scratch1].op_str
             and n[scratch2].mnemonic=='fild' and f'[ebp - {origslot}]' in n[scratch2].op_str,
             f'original {action:#x} x87 integer scratch physical EBP source differs')
        if action==0x18A:
            need(n[13].op_str.endswith(', 0x41700000')
                 and n[60].mnemonic=='imul' and n[60].op_str.endswith(', 0x97')
                 and n[67].op_str=='0x327',
                 'original 18A native 15.0f, signed side*151 and 0x327 shot differs')
        else:
            need(n[13].op_str.endswith(', 0x41200000')
                 and n[55].op_str.endswith(', 2')
                 and n[59].mnemonic=='add' and n[59].op_str.endswith(', 1')
                 and n[88].mnemonic=='shl' and n[88].op_str.endswith(', 7')
                 and n[95].op_str=='0x328',
                 'original 18B native side*128, stage7 guarded shot/counter differs')
        for ordinal,(target,mn,_) in FIELDS[action].items():
            x=n[ordinal];want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(x.mnemonic==mn and x.op_str==want,
                 f'original {action:#x} PE-targeted physical x86{ordinal} differs')
        result[action]=(n,lo,hi)
    return result


def parent_source(source):
    decl='extern float g_SlowPositiveDragAt006578C0;'
    need(source.count(decl)==1,'native full parent original float source declaration lost')
    source=source.replace(decl,decl+'\nextern float g_YPlusAt0065929C;\nextern float g_YPlusAt00658400;')
    first='        case 0x18A: g_FighterProbeMarker = 395; break;'
    second='        case 0x18B: g_FighterProbeMarker = 396; break;'
    need(source.count(first)==source.count(second)==1,
         'actual original physical 18A and 18B source placeholders missing')
    source=source.replace(first,'#include "FighterMotionShotsF661.inc"').replace(second,'')
    need(source.count('        case 0x190: g_FighterProbeMarker = 401; break;')==1,
         'original following 190 true physical handler/source placeholder lost')
    return source


def verify_own_fields(refs,orig,gen,action):
    low,high=gen[0].address,gen[-1].address+gen[-1].size
    physical=[r for r in refs if low<=r['offset']<high]
    need(len(physical)==len(FIELDS[action]),
         f'{action:#x}: all real original 6/7 physical typed COFF fields are not present')
    for i,(target,mn,sym) in FIELDS[action].items():
        a,b=orig[i],gen[i]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
             f'{action:#x}: original physical PE native x86{i} source operation differs')
        linked=[f for f in physical if b.address<=f['offset']<b.address+b.size]
        need(len(linked)==1 and linked[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and linked[0]['addend']==0 and linked[0]['local_symbol_offset'] is None
             and sym in linked[0]['symbol'],
             f'{action:#x}: real original typed PE/COFF x86{i} target {target:#x} differs')
    return len(physical)


def verify_nonstrict(reader,pe,decoder,code,refs,originals,old,ordinal,h):
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    offset=ordinal
    receipts=[]
    for action in ACTIONS:
        n,lo,hi=originals[action]
        gen=ins[offset:offset+len(n)]
        count,size,gen_size,scratch1,scratch2,origslot,genslot=SIZES[action]
        need(len(gen)==count and gen[-1].mnemonic=='jmp'
             and gen[-1].op_str==ins[old['continuation_source_ordinal']-1].op_str
             and gen[-1].address+gen[-1].size-gen[0].address==gen_size,
             f'{action:#x}: real native source whole x86 instruction count/exit or compiled size differs')
        fields=verify_own_fields(refs,n,gen,action)
        widths=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(n,gen)) if a.size!=b.size]
        need(widths==[(scratch1,6,3),(scratch2,6,3)],
             f'{action:#x}: actual original 2 nonexact integer-to-float EBP widths changed: {widths}')
        lhs,rhs=h['f598'].normalized(n),h['f598'].normalized(gen)
        float_fields={i for i,(_,mn,_) in FIELDS[action].items() if mn!='call'}
        wrong=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs))
               if a!=b and i not in float_fields]
        need(not wrong,f'{action:#x}: real native GPR/x87/CFG differences besides EBP: {wrong[:8]}')
        # Old register-geometry helpers intentionally erase all EBP slots.
        # Here compare genuine physical EBP roles independently: only the
        # known saved receiver -0x44 -> -8 may be normalized.
        raw_wrong=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(n,gen))
                   if i not in float_fields and a.mnemonic!='call'
                   and not a.mnemonic.startswith('j')
                   and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
        need([i for i,_,_ in raw_wrong]==[scratch1,scratch2]
             and all(f'[ebp - {origslot}]' in n[i].op_str
                     and f'[ebp - {genslot}]' in gen[i].op_str for i in (scratch1,scratch2)),
             f'{action:#x}: native original EBP scratch really does not match only in two genuine operands: {raw_wrong[:6]}')
        receipts.append({'original_native_case':f'0x{action:03X}',
                         'original_whole_case_start':f'0x{lo:08X}',
                         'original_whole_case_next_handler':f'0x{hi:08X}',
                         'original_whole_native_x86_roles':count,
                         'original_whole_native_internal_CODE_bytes':size,
                         'actual_generated_cpp_case_bytes':gen_size,
                         'physical_original_typed_PE_COFF_fields':fields,
                         'genuine_remaining_wrong_EBP_x86_ordinals':[scratch1,scratch2],
                         'original_native_scratch_EBP':'-'+origslot,
                         'compiler_generated_scratch_EBP':'-'+genslot,
                         'complete_native_case_strict':False,
                         'new_accepted_whole_authored_bytes':0})
        offset+=count
    need(ins[offset].mnemonic=='mov' and ins[offset].op_str.endswith(', 0x191'),
         'source original 18B must immediately precede actual next 190 physical handler')
    return receipts


def main():
    from importlib.util import spec_from_file_location,module_from_spec
    import sys
    def load(name,path):
        sp=spec_from_file_location(name,ROOT/path)
        need(sp is not None and sp.loader is not None,'missing source '+str(path))
        module=module_from_spec(sp);sys.modules[name]=module;sp.loader.exec_module(module);return module
    f651=load('f661_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f661_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f661_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f661_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f661_f657','scripts/verify-fighter-motion-continuation-f657.py')
    h=f651.load_helpers()
    reader=load('f661_reader','scripts/compare-coff-function.py')
    acts=load('f661_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,decoder,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    originals=true_native(reader,pe,decoder,boss,mapped)
    old651={a:f651.true_native(reader,pe,decoder,boss,by,a) for a in (0xD1,0xD2)}
    old653=f653.native_cases(reader,pe,decoder,boss,mapped)
    old654=f654.original_native(reader,pe,decoder,boss,mapped)
    old656=f656.native_cases(reader,pe,decoder,boss,mapped)
    old657=f657.native_cases(reader,pe,decoder,boss,mapped)
    source=f651.source_with_d1_d2(reader,pe,decoder,boss,report,mapped,h)
    source=f653.replace_following_cases(source)
    source=f654.source_with_finish(source)
    source=f656.source_with_native_stages(source)
    source=f657.source_with_stage_186_189(source)
    source=parent_source(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-18A-18B-nonstrict-native-shots.cpp'
    obj=OUT/'Boss00543210-18A-18B-nonstrict-native-shots.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
           '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
           cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,'pinned VC7.1 whole parent compilation failed: '+result.stderr[-500:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,decoder,boss,report,mapped,code,refs,old651,h,following_native=0x12C)
    older653,ordinal=f653.verify_new(reader,pe,decoder,code,refs,old,old653,h,following_native=0x12F)
    older654,ordinal=f654.verify_new(reader,pe,decoder,code,refs,old654,old,ordinal,h,following_native=0x131)
    older656,ordinal=f656.verify_native(reader,pe,decoder,code,refs,old656,old,ordinal,h,following_native=0x186)
    older657,nonstrict186,ordinal=f657.verify_new(reader,pe,decoder,code,refs,old657,old,ordinal,h,following_native=0x18A)
    receipts=verify_nonstrict(reader,pe,decoder,code,refs,originals,old,ordinal,h)
    summary={'real_original_selected_whole_boss':'0x00543210',
             'entire_original_parent_NONEXACT_CODE_bytes':boss['size'],
             'separately_owned_after_RET_switch_DATA_bytes':boss['postret_size'],
             'previous_17_native_strict_cases_and_switch_DATA_verified_in_same_new_parent':True,
             'original_true_186_nonstrict_scratch_preserved':nonstrict186,
             'source_backed_original_18A_18B_but_NOT_STRICT':receipts,
             'new_original_inner_noncredited_native_source_backed_CODE_bytes':sum(q['original_whole_native_internal_CODE_bytes'] for q in receipts),
             'new_strict_native_cases':0,'new_whole_authored_exact_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F661 selected original full boss 00543210: two new original source-backed '
          'but NONSTRICT 18A/18B complete case bodies; 170 native x86, '
          '615 native original inner CODE B, 13 real typed PE/COFF fields. '
          'Four actual scratch EBP roles wrong across two cases, source bytes '
          '250/353 vs genuine 256/359, so zero new strict case/whole authored bytes. '
          'All 17 previous strict native case bodies and complete original '
          'afterRET jump DATA reverified in same fresh full parent COFF; '
          'no full 943-unit replay.')


if __name__=='__main__':
    main()
