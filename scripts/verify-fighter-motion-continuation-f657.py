#!/usr/bin/env python3
"""F657: strict original fighter 187/188/189 while isolating 186 EBP negative.

Cold-compile only one genuine entire original 00543210 C++ parent. Strictly
recheck 14 older case interiors, the full after-RET switch DATA and all
physical original COFF fields. Do NOT credit nonstrict native case 186:
its two real original EBP-0x84 scratch references compile at EBP-0x20.
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
OUT=ROOT/'.analysis/f657-fighter-motion-continuation'
ACTOR=0x00543210
ACTIONS=(0x186,0x187,0x188,0x189)
NEXT={0x186:0x187,0x187:0x188,0x188:0x189,0x189:0x18A}
SIZES={0x186:(82,290),0x187:(50,181),0x188:(50,181),0x189:(112,405)}
BASE={13:(0x00453E20,'call','ResetAt453E20'),
      26:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
      31:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
      40:(0x0040FA30,'call','GetNativeActionAt40FA30'),
      48:(0x0040FAC0,'call','SetNativeActionAt40FAC0')}
FIELDS={
    0x186:BASE|{59:(0x00453E60,'call','InitTrajectoryAt453E60'),
               66:(0x00658290,'fsub','g_ApproachLowerAt00658290'),
               80:(0x00453A70,'call','SpawnFloatXYAt453A70')},
    0x187:BASE,
    0x188:BASE,
    0x189:{22:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           28:(0x006578C0,'fsub','g_SlowPositiveDragAt006578C0'),
           33:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           55:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
           71:(0x0040FB40,'call','SetAuxActionAt40FB40'),
           74:(0x0040FA30,'call','GetNativeActionAt40FA30'),
           82:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
          101:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
          110:(0x0040FB40,'call','SetAuxActionAt40FB40')},
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'original source missing '+str(path))
    m=importlib.util.module_from_spec(spec);sys.modules[name]=m;spec.loader.exec_module(m)
    return m


def native_cases(reader,pe,decoder,boss,mapped):
    by={x['action']:int(x['handler'],16) for x in mapped}
    cases={}
    for act in ACTIONS:
        lo,hi=by[act],by[NEXT[act]]
        n=list(decoder.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        want_count,want_size=SIZES[act]
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and len(n)==want_count and hi-lo==want_size
             and sum(x.size for x in n)==want_size
             and n[0].mnemonic=='mov' and n[-1].mnemonic=='jmp'
             and n[-1].op_str=='0x5515c2',
             f'{act:#x}: actual original native physical whole case wrong')
        if act==0x186:
            need(n[19].op_str.endswith(', 0x41200000')
                 and n[57].op_str=='0x40000000'
                 and n[71].op_str=='edx, edx, 0xaa'
                 and n[72].op_str=='dword ptr [ebp - 0x84], edx'
                 and n[73].op_str=='dword ptr [ebp - 0x84]'
                 and n[78].op_str=='0x325',
                 'original 186 true native scratch/side arithmetic and projectile changed')
        elif act in (0x187,0x188):
            need(n[19].op_str.endswith(', '+('0x41200000' if act==0x187 else '0x41700000'))
                 and n[22].mnemonic=='test' and n[23].mnemonic=='jle'
                 and n[46].op_str==('0' if act==0x187 else '2'),
                 f'original {act:#x}: signed-stage velocity initialisation or action target changed')
        else:
            need(n[9].op_str.endswith(', 0') and n[19].op_str.endswith(', 0x41700000')
                 and n[24].op_str=='ah, 0x41' and n[36].mnemonic=='jne'
                 and n[58].mnemonic=='jp' and n[69].op_str=='9'
                 and n[92].op_str.endswith(', 0x41100000')
                 and n[94].op_str.endswith(', 0x3f666666')
                 and n[108].mnemonic=='push',
                 'original 189 genuine gravity/collision, stage7 9.0/0.9 or aux stage9 behavior changed')
        for i,(target,mn,_) in FIELDS[act].items():
            x=n[i];want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(x.mnemonic==mn and x.op_str==want,
                 f'{act:#x}: original real PE field at x86{i} target {target:#x} changed')
        cases[act]=(n,lo,hi)
    return cases


def source_with_stage_186_189(src):
    decl='void SpawnWithFloatAt453A70(int,int,float,char,int);'
    need(src.count(decl)==1,'original selected complete parent directed source declaration missing')
    src=src.replace(decl,decl+' void SpawnFloatXYAt453A70(int,float,float,char,int);')
    old='extern float g_NewDragAt006581E0;'
    need(src.count(old)==1,'original selected complete parent native float declaration missing')
    src=src.replace(old,old+'\nextern float g_SlowPositiveDragAt006578C0;')
    marker='        case 0x186: g_FighterProbeMarker = 391; break;'
    need(src.count(marker)==1,'original native 186 source case marker missing')
    src=src.replace(marker,'#include "FighterMotionContinuationF657.inc"')
    for act in (0x187,0x188,0x189):
        mark=f'        case 0x{act:X}: g_FighterProbeMarker = {act+1}; break;'
        need(src.count(mark)==1,f'original native following {act:#x} source marker missing')
        src=src.replace(mark,'')
    need(src.count('        case 0x18A: g_FighterProbeMarker = 395; break;')==1,
         'original next physical handler 18A source marker missing')
    return src


def verify_physical_fields(refs,n,gen,fields,act):
    low,high=gen[0].address,gen[-1].address+gen[-1].size
    actual=[x for x in refs if low<=x['offset']<high]
    need(len(actual)==len(fields),
         f'{act:#x}: complete original physical typed PE/COFF field count differs')
    for ordinal,(target,mn,symbol) in fields.items():
        original,compiled=n[ordinal],gen[ordinal]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(original.mnemonic==compiled.mnemonic==mn and original.op_str==want,
             f'{act:#x}: original native physical x86{ordinal} instruction/target wrong')
        found=[x for x in actual if compiled.address<=x['offset']<compiled.address+compiled.size]
        need(len(found)==1 and found[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and symbol in found[0]['symbol'],
             f'{act:#x}: actual original native x86{ordinal} field source COFF role wrong')
    return len(actual)


def verify_new(reader,pe,decoder,code,refs,orig,older,start,h,following_native=None):
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    offset=start
    proven=[];negative={}
    for act in ACTIONS:
        n,lo,hi=orig[act]
        gen=ins[offset:offset+len(n)]
        need(len(gen)==len(n) and gen[-1].mnemonic=='jmp'
             and gen[-1].op_str==ins[older['continuation_source_ordinal']-1].op_str,
             f'{act:#x}: generated native function case truncated/noncanonical exit')
        count=verify_physical_fields(refs,n,gen,FIELDS[act],act)
        source_bytes=gen[-1].address+gen[-1].size-gen[0].address
        lhs,rhs=h['f598'].normalized(n),h['f598'].normalized(gen)
        abs_indices={i for i,(_,mn,_) in FIELDS[act].items() if mn!='call'}
        mismatches=[(i,x,y) for i,(x,y) in enumerate(zip(lhs,rhs))
                    if x!=y and i not in abs_indices]
        # The historical F598 normalizer deliberately erases ALL EBP
        # offsets, including real scratch slots. Do NOT use it to claim
        # that native 186's physical -0x84 and compiler -0x20 agree.
        # Independently allow ONLY the proven original receiver save
        # -0x44 -> -8, never another stack slot or machine-code field.
        scratch_mismatch=[(i,x.op_str,y.op_str)
                          for i,(x,y) in enumerate(zip(n,gen))
                          if x.mnemonic not in ('call',)
                          and not x.mnemonic.startswith('j')
                          and i not in abs_indices
                          and x.op_str.replace('[ebp - 0x44]', '[ebp - 8]')!=y.op_str]
        if act==0x186:
            widths=[(i,x.size,y.size) for i,(x,y) in enumerate(zip(n,gen)) if x.size!=y.size]
            need(len(n)==82 and source_bytes==284 and hi-lo==290
                 and widths==[(72,6,3),(73,6,3)]
                 and not mismatches
                 and [i for i,_,_ in scratch_mismatch]==[72,73]
                 and '[ebp - 0x84]' in n[72].op_str
                 and '[ebp - 0x84]' in n[73].op_str
                 and '[ebp - 0x20]' in gen[72].op_str
                 and '[ebp - 0x20]' in gen[73].op_str,
                 f'native 186 original scratch ownership NEGATIVE changed: normalized={mismatches[:5]}, raw_scratch={scratch_mismatch[:5]}, widths={widths}')
            negative={'original_action':'0x186',
                      'original_entire_physical_CODE_bytes':290,
                      'original_complete_native_x86':82,
                      'compiled_normal_CPP_CODE_bytes':284,
                      'real_original_typed_PE_COFF_fields':count,
                      'genuine_nonfield_mismatching_operand_ordinals':[72,73],
                      'actual_original_EBP_scratch':'-0x84',
                      'current_compiler_EBP_scratch':'-0x20',
                      'strict_native_case':False,
                      'new_authored_whole_function_credit':0}
        else:
            need(source_bytes==hi-lo and all(x.size==y.size for x,y in zip(n,gen))
                 and not mismatches and not scratch_mismatch,
                 f'{act:#x} true native GPR/x87/CFG/stack-role mismatch: normalized={mismatches[:10]}, raw_scratch={scratch_mismatch[:10]}')
            proven.append({'native_action':f'0x{act:03X}',
                           'original_native_physical_start':f'0x{lo:08X}',
                           'original_native_physical_next':f'0x{hi:08X}',
                           'strict_original_x86_instructions':len(n),
                           'strict_original_internal_CODE_bytes':hi-lo,
                           'actual_original_typed_COFF_fields':count,
                           'credited_new_authored_whole_function_bytes':0})
        offset+=len(n)
    if following_native is None:
        need(ins[offset].mnemonic=='mov' and ins[offset].op_str.endswith(', 0x18b'),
             'native 189 complete case must end directly at original 18A source marker')
    else:
        need(following_native==0x18A and ins[offset].mnemonic=='mov'
             and ins[offset].op_str=='eax, dword ptr [ebp - 8]'
             and ins[offset+1].mnemonic=='movsx'
             and ins[offset+1].op_str=='ecx, word ptr [eax + 0x62]',
             'native 0x18A must genuinely follow original 0x189, no marker')
    return proven,negative,offset


def main():
    f651=load('f657_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f657_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f657_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f657_f656','scripts/verify-fighter-late-stages-f656.py')
    h=f651.load_helpers()
    reader=load('f657_reader','scripts/compare-coff-function.py')
    acts=load('f657_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,decoder,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    orig=native_cases(reader,pe,decoder,boss,mapped)
    orig651={a:f651.true_native(reader,pe,decoder,boss,by,a) for a in (0xD1,0xD2)}
    orig653=f653.native_cases(reader,pe,decoder,boss,mapped)
    orig654=f654.original_native(reader,pe,decoder,boss,mapped)
    orig656=f656.native_cases(reader,pe,decoder,boss,mapped)
    src=f651.source_with_d1_d2(reader,pe,decoder,boss,report,mapped,h)
    src=f653.replace_following_cases(src)
    src=f654.source_with_finish(src)
    src=f656.source_with_native_stages(src)
    src=source_with_stage_186_189(src)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-strict187-188-189-and-negative186.cpp'
    obj=OUT/'Boss00543210-strict187-188-189-and-negative186.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'new full selected normal VC7.1 source parent failed: '+proc.stderr[-600:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,decoder,boss,report,mapped,code,refs,orig651,h,following_native=0x12C)
    prev653,start654=f653.verify_new(reader,pe,decoder,code,refs,old,orig653,h,following_native=0x12F)
    prev654,start656=f654.verify_new(reader,pe,decoder,code,refs,orig654,old,start654,h,following_native=0x131)
    prev656,start657=f656.verify_native(reader,pe,decoder,code,refs,orig656,old,start656,h,following_native=0x186)
    proven,negative,_=verify_new(reader,pe,decoder,code,refs,orig,old,start657,h)
    result={'original_parent':'0x00543210',
            'whole_parent_original_CODE_bytes_still_NONEXACT':boss['size'],
            'separate_original_after_RET_compressed_DATA_bytes':boss['postret_size'],
            'same_new_full_parent_all_prior_14_native_case_interiors_strict':True,
            'same_full_parent_all_prior_original_switch_afterRET_DATA_strict':True,
            'prior_strict_f653_f654_f656':(len(prev653),len(prev654),len(prev656)),
            'new_original_strict_native_case_interiors':proven,
            'new_strict_original_native_inner_CODE_bytes':sum(q['strict_original_internal_CODE_bytes'] for q in proven),
            'new_original_native_NONEXACT_case_186':negative,
            'new_accepted_entire_authored_function_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F657 one original whole fighter 00543210 cold parent: three new strictly '
          f'native 0x187/0x188/0x189 cases, {sum(q["strict_original_x86_instructions"] for q in proven)} '
          f'x86, {result["new_strict_original_native_inner_CODE_bytes"]} native internal CODE B, '
          f'{sum(q["actual_original_typed_COFF_fields"] for q in proven)} genuine typed PE/COFF fields. '
          'Original 186 is deliberate NONEXACT: 82 original x86, 8 real PE fields '
          'but two actual -0x84 EBP scratch slots compile -0x20, 284 vs original 290 B. '
          'All 14 older strict cases and complete afterRET native switch DATA were '
          'rechecked in SAME new parent. Zero independent whole function credit, '
          'no all-unit replay.')


if __name__=='__main__':
    main()
