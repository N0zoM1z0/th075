#!/usr/bin/env python3
"""F666: four natural preceding giant native stages, strict-regression control.

Rebuild exactly ONE selected full original 00543210 parent under VC7.1.
Prove 1FA/1FB/1FE/1FF real original x86 extent and all PE/COFF
fields, and the genuine register/EBP mismatches when restoring them.
Their insertion shifts formerly strict 200/201 GPR roles; do NOT
replace the stable F664 strict parent or grant false exact case credit.
No 943-unit cold replay, target patch, ASM, or fake local padding.
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
OUT=ROOT/'.analysis/f666-fighter-preceding-controls'
ACTOR=0x00543210
CASES=(0x1FA,0x1FB,0x1FE,0x1FF,0x200,0x201)
NEXT={0x1FA:0x1FB,0x1FB:0x1FE,0x1FE:0x1FF,0x1FF:0x200,0x200:0x201,0x201:0x252}
SIZES={0x1FA:(82,287,281),0x1FB:(174,603,603),0x1FE:(153,526,526),
       0x1FF:(153,526,526),0x200:(102,343,343),0x201:(126,436,436)}
EXPECTED_FIELDS={0x1FA:9,0x1FB:15,0x1FE:14,0x1FF:14,0x200:8,0x201:9}
# Actual PE-address-to-typed-source-symbol relationship is separately
# verified per physical original x86 field; names are inferred C++ grammar,
# *not* claims about historical declaration or object owner.
SYMBOLS={
  0x00453E20:'ResetAt453E20',0x0040FB40:'SetAuxActionAt40FB40',
  0x0040FA30:'GetNativeActionAt40FA30',0x0040FAC0:'SetNativeActionAt40FAC0',
  0x00453C80:'SpawnRawXYAt453C80',0x00453A70:'SpawnDirectedAt453A70',
  0x00453D40:'PrepareActionAt453D40',
  0x00657874:'g_FloatMulAt00657874',0x00657CBC:'g_FloatAddAt00657CBC',
  0x0065782C:'g_ThresholdAt0065782C',0x0065747C:'g_RisingGravityAt0065747C',
  0x006583FC:'g_BounceScaleAt006583FC',0x006581E0:'g_RisingDragAt006581E0',
  0x00659A10:'g_ShotPositiveDragAt00659A10',0x00657CF8:'g_SpeedClampAt00657CF8',
  0x00659240:'g_FallingLateDragAt00659240',
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing original native C++ source '+str(path))
    m=importlib.util.module_from_spec(sp);sys.modules[name]=m;sp.loader.exec_module(m)
    return m


def source_with_preceding_cases(source):
    decl='extern float g_SlowPositiveDragAt006578C0;'
    need(source.count(decl)==1,'original giant current native float declaration missing')
    additions=('extern float g_ShotPositiveDragAt00659A10;\n'
               'extern float g_SpeedClampAt00657CF8;\n'
               'extern float g_RisingGravityAt0065747C;\n'
               'extern float g_RisingDragAt006581E0;\n'
               'extern float g_BounceScaleAt006583FC;\n'
               'extern float g_FloatMulAt00657874;\n'
               'extern float g_FloatAddAt00657CBC;')
    source=source.replace(decl,decl+'\n'+additions)
    for action in (0x1FA,0x1FB,0x1FE,0x1FF):
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(marker)==1,f'genuine physical original native source marker {action:#x} missing')
        source=source.replace(marker,
             '#include "FighterPrecedingStageGrammarF666.inc"' if action==0x1FA else '')
    need(source.count('#include "FighterSpecialStageF664.inc"')==1,
         'two F664 200/201 accepted standalone case sources missing')
    return source


def actual_pe_fields(original):
    fields=[]
    for i,x in enumerate(original):
        if x.mnemonic=='call' and re.fullmatch(r'0x[0-9a-f]+',x.op_str):
            fields.append((i,int(x.op_str,16),x.mnemonic))
        elif x.mnemonic.startswith('f') and re.fullmatch(r'dword ptr \[0x[0-9a-f]+\]',x.op_str):
            fields.append((i,int(x.op_str.split('[0x',1)[1][:-1],16),x.mnemonic))
    return fields


def verify_phase_negative(reader,pe,decoder,code,refs,orig,helper):
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    # Original preceding 1F8 case is intentionally still a separately
    # compiled original-jump marker, not a guessed ordinal or code patch.
    entry=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        i=next((k for k,x in enumerate(ins) if x.address<=f['offset']<x.address+x.size),None)
        if i is not None and ins[i].mnemonic=='mov' and ins[i].op_str.endswith(', 0x1f9'):
            entry.append(i)
    need(len(entry)==1 and ins[entry[0]+1].mnemonic=='jmp',
         'original prior 1F8 source marker not physically unique')
    pos=entry[0]+2
    result=[]
    for action in CASES:
        native,lo,hi=orig[action]
        gen=ins[pos:pos+len(native)]
        n_count,n_width,g_width=SIZES[action]
        need(len(gen)==len(native)==n_count and gen[-1].mnemonic=='jmp'
             and sum(x.size for x in native)==n_width
             and gen[-1].address+gen[-1].size-gen[0].address==g_width,
             f'{action:#x}: actual native generated physical case x86/size changed')
        if action==0x1FA:
            widths=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,gen))
                    if a.size!=b.size]
            need(widths==[(16,6,3),(17,6,3)],
                 f'1FA original two genuine wide EBP integer-to-x87 scratch slots changed {widths}')
        else:
            need(all(a.size==b.size for a,b in zip(native,gen)),
                 f'{action:#x}: full original x86 geometry/width changed')
        original_fields=actual_pe_fields(native)
        physical=[f for f in refs if gen[0].address<=f['offset']<gen[-1].address+gen[-1].size]
        need(len(original_fields)==len(physical)==EXPECTED_FIELDS[action],
             f'{action:#x}: genuine source/PE full typed COFF field ownership changed')
        for ordinal,target,mn in original_fields:
            a,b=native[ordinal],gen[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
                 f'{action:#x}: actual original native instruction or real PE target changed at {ordinal}')
            reloc=[f for f in physical if b.address<=f['offset']<b.address+b.size]
            need(len(reloc)==1 and reloc[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and reloc[0]['addend']==0 and reloc[0]['local_symbol_offset'] is None
                 and SYMBOLS[target] in reloc[0]['symbol'],
                 f'{action:#x}: genuine typed original PE/COFF source x86{ordinal} is wrong')
        l,r=helper['f598'].normalized(native),helper['f598'].normalized(gen)
        absolute={i for i,t,m in original_fields if m!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(l,r)) if a!=b and i not in absolute]
        need(len(wrong)>15 and 0 in wrong,
             f'{action:#x}: expected original compiler register-phase difference disappeared, re-evaluate acceptance')
        result.append({'native_action':f'0x{action:03X}',
                       'real_native_original_start':f'0x{lo:08X}',
                       'real_native_original_next':f'0x{hi:08X}',
                       'original_native_complete_x86_instructions':len(native),
                       'real_original_native_internal_CODE_bytes':n_width,
                       'emitted_normal_CPP_inner_CODE_bytes':g_width,
                       'true_zero_addend_PE_COFF_fields':len(physical),
                       'nonfield_original_register_role_mismatch_count':len(wrong),
                       'native_new_strict_in_this_source_context':False})
        pos+=len(native)
    need(ins[pos].mnemonic=='mov' and ins[pos].op_str.endswith(', 0x253'),
         'following true native 252 source marker physically missing')
    return result


def main():
    f651=load('f666_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f666_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f666_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f666_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f666_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f666_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f666_f664','scripts/verify-fighter-special-stage-f664.py')
    h=f651.load_helpers()
    reader=load('f666_reader','scripts/compare-coff-function.py')
    acts=load('f666_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,decoder,boss)
    by={row['action']:int(row['handler'],16) for row in mapped}
    original={}
    for action in CASES:
        first,last=by[action],by[NEXT[action]]
        native=list(decoder.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        need(len(native)==SIZES[action][0] and last-first==SIZES[action][1]
             and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
             f'{action:#x}: original real PE physical case/epilogue changed')
        original[action]=(native,first,last)
    source=f651.source_with_d1_d2(reader,pe,decoder,boss,report,mapped,h)
    source=f653.replace_following_cases(source)
    source=f654.source_with_finish(source)
    source=f656.source_with_native_stages(source)
    source=f657.source_with_stage_186_189(source)
    source=f661.parent_source(source)
    source=f664.source_with_cases(source)
    source=source_with_preceding_cases(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-original-stage-phase-negative.cpp'
    obj=OUT/'Boss00543210-original-stage-phase-negative.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned VC7.1 selected negative full-giant C++ compile failed: '+cp.stderr[-500:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old_native={a:f651.true_native(reader,pe,decoder,boss,by,a) for a in (0xD1,0xD2)}
    old=f651.verify_full(reader,pe,decoder,boss,report,mapped,code,refs,old_native,h,following_native=0x12C)
    prior653=f653.native_cases(reader,pe,decoder,boss,mapped)
    prior654=f654.original_native(reader,pe,decoder,boss,mapped)
    prior656=f656.native_cases(reader,pe,decoder,boss,mapped)
    prior657=f657.native_cases(reader,pe,decoder,boss,mapped)
    prior661=f661.true_native(reader,pe,decoder,boss,mapped)
    accepted653,ordinal=f653.verify_new(reader,pe,decoder,code,refs,old,prior653,h,following_native=0x12F)
    accepted654,ordinal=f654.verify_new(reader,pe,decoder,code,refs,prior654,old,ordinal,h,following_native=0x131)
    accepted656,ordinal=f656.verify_native(reader,pe,decoder,code,refs,prior656,old,ordinal,h,following_native=0x186)
    accepted657,nonstrict186,ordinal=f657.verify_new(reader,pe,decoder,code,refs,prior657,old,ordinal,h,following_native=0x18A)
    nonstrict_shots=f661.verify_nonstrict(reader,pe,decoder,code,refs,prior661,old,ordinal,h)
    need((len(accepted653),len(accepted654),len(accepted656),len(accepted657),len(nonstrict_shots))==(3,2,5,3,2),
         'earlier 17 exact inner native source cases or three real negative controls changed')
    actual=verify_phase_negative(reader,pe,decoder,code,refs,original,h)
    # F664's separate stable strict verifier starts from the *prior*
    # 0x1FF physical placeholder marker. That marker is correctly absent
    # in THIS variant because real 1FF is now a natural C++ case; do not
    # interpret loss of that sentinel as evidence of a strict mismatch.
    # Instead compare the actual newly compiled complete 200/201 native
    # instructions and all physical fields above, independently and without
    # the older marker assumption. Both now have genuine nonfield GPR
    # mismatches (beginning at x86 ordinal zero), so no F664 adoption here.
    last_two=[x for x in actual if x['native_action'] in ('0x200','0x201')]
    need(len(last_two)==2 and all(x['nonfield_original_register_role_mismatch_count']>15
                                  for x in last_two),
         'new preceding-stage source must have genuinely changed both 200/201 native register phases')
    receipt={'original_selected_parent':'0x00543210',
             'original_parent_whole_nonexact':True,
             'selected_whole_parent_original_CODE_bytes':boss['size'],
             'prior_native_dispatch_and_original_afterRET_DATA_preserved':True,
             'all_17_earlier_strict_original_case_interiors_reverified_in_same_parent':True,
             'prior_186_18A_18B_real_EBP_nonexact_controls_reverified':True,
             'new_source_grammar_1FA_1FB_1FE_1FF_control_negative':actual,
             'restoring_native_predecessor_source_changes_200_201_GPR_phase':True,
             'F664_strict_200_201_must_not_be_claimed_in_this_alternative_context':True,
             'new_accepted_whole_authored_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F666 complete selected original giant negative control: four genuine '
          '1FA/1FB/1FE/1FF native source grammars reproduce 562 original x86 '
          'and 1,942 original CODE B with full true typed PE/COFF fields '
          '(but REAL GPR phase mismatches; 1FA original 287 B emits 281 B). '
          'Restoring these prior source cases also causes verified F664 '
          '200/201 strict source context to FAIL on actual native register roles. '
          'Entire original afterRET DATA remains checked, no new strict cases, '
          'no accepted authored CODE and no 943-unit cold replay.')


if __name__=='__main__':
    main()
