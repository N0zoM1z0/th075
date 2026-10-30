#!/usr/bin/env python3
"""F676: two entire original native 2F0/2F1 source grammars, GPR-negative.

Genuine pinned VC7.1 cold-build of ONE complete selected 00543210 parent.
Verify actual native 342/274 whole x86, 1,169/977 original full case
CODE bytes and 42/23 zero-addend PE/COFF fields. Deliberately reject
147/170 real nonfield original GPR register-role differences.
Revalidate 27 prior strictly source-backed fighter case interiors, four
EBP scratch negatives, 31C real nonstrict terminal, and all original
after-RET switch DATA in the SAME new parent; no entire-giant credit.
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
OUT=ROOT/'.analysis/f676-fighter-cloud-burst'
ACTOR=0x00543210
ACTIONS=(0x2F0,0x2F1)
NEXT={0x2F0:0x2F1,0x2F1:0x2F8}
GEOMETRY={0x2F0:(342,1169,42,147,39),0x2F1:(274,977,23,170,0)}
SYMBOLS={
 0x00453E20:'ResetAt453E20',0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',0x0040FB40:'SetAuxActionAt40FB40',
 0x00455580:'RandomBoundaryAt455580',0x00453D40:'PrepareActionAt453D40',
 0x00453E60:'InitTrajectoryAt453E60',0x00453C80:'SpawnMixedAt453C80',
 0x0065785C:'g_CloudGravityAt0065785C',
 0x0065782C:'g_ThresholdAt0065782C',
 0x006714D0:'g_CloudOpponentAt006714D0',
 0x00657888:'g_ContactProjectionAt00657888',
 0x00659238:'g_BurstXAt00659238',
 0x00658400:'g_BurstXAt00658400',
 0x00659420:'g_BurstXAt00659420',
 0x00658370:'g_BurstXAt00658370',
 0x006590A8:'g_BurstXAt006590A8',
 0x006591E4:'g_CloudShotYAt006591E4',
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing original reconstruction source '+str(path))
    mod=importlib.util.module_from_spec(sp)
    sys.modules[name]=mod;sp.loader.exec_module(mod)
    return mod


def original_fields(ins):
    fields=[]
    for i,x in enumerate(ins):
        if x.mnemonic=='call' and re.fullmatch(r'0x[0-9a-f]+',x.op_str):
            fields.append((i,int(x.op_str,16),'call'))
        elif x.mnemonic.startswith('f') and re.fullmatch(r'dword ptr \[0x[0-9a-f]+\]',x.op_str):
            fields.append((i,int(x.op_str.split('[0x')[1][:-1],16),x.mnemonic))
        elif x.mnemonic=='movsx' and re.fullmatch(r'(eax|ecx|edx), byte ptr \[0x[0-9a-f]+\]',x.op_str):
            fields.append((i,int(x.op_str.split('[0x')[1][:-1],16),'movsx'))
    return fields


def original_cases(reader,pe,dec,boss,mapped):
    by={x['action']:int(x['handler'],16) for x in mapped}
    result={}
    for action in ACTIONS:
        first,last=by[action],by[NEXT[action]]
        native=list(dec.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        nx,code,fields,wrong,first_wrong=GEOMETRY[action]
        need(boss['address']<first<last<boss['address']+boss['size']
             and last-first==code and len(native)==nx
             and sum(x.size for x in native)==code
             and native[0].mnemonic=='mov'
             and native[-1].mnemonic=='jmp' and native[-1].size==5
             and native[-1].op_str=='0x5515c2',
             f'{action:#x}: actual original PE physical whole case or shared exit changed')
        truefields=original_fields(native)
        need(len(truefields)==fields and all(t in SYMBOLS or t==0x00453A70
                                             for i,t,m in truefields),
             f'{action:#x}: native original physical PE field targets/count changed')
        if action==0x2F0:
            need(native[112].op_str=='0x38c' and native[123].op_str=='0x38f'
                 and all(native[i].op_str=='0x38d'
                         for i in (166,179,192,205,218,231,247,260,273,286,299,312))
                 and native[317].op_str=='0x453e60'
                 and native[320].op_str=='0x453d40',
                 'genuine original stage8 twelve-shot 2F0 resource and trajectory grammar changed')
        else:
            need(native[70].op_str=='0x40'
                 and native[126].op_str=='0x390'
                 and native[140].op_str=='0x390'
                 and native[220].op_str=='0x38b'
                 and native[252].op_str=='0x453d40',
                 'original native 2F1 conditional random-shot/counter stage grammar changed')
        result[action]=(native,first,last,truefields)
    return result


def source_with_burst(source):
    decl='void SpawnWithFloatAt453A70(int,int,float,char,int);'
    need(source.count(decl)==1,'original whole giant source directed shot declaration missing')
    source=source.replace(decl,decl+' void SpawnFloatXRawYAt453A70(int,float,int,char,int);')
    start='extern float g_CloudShotYAt006591E4;'
    need(source.count(start)==1,'original complete fighter native float declarations missing')
    extra=('\nextern float g_BurstXAt00659238;'
           '\nextern float g_BurstXAt00658400;'
           '\nextern float g_BurstXAt00659420;'
           '\nextern float g_BurstXAt00658370;'
           '\nextern float g_BurstXAt006590A8;')
    source=source.replace(start,start+extra)
    marker='        case 0x2F0: g_FighterProbeMarker = 753; break;'
    need(source.count(marker)==1,'original physical 2F0 native source marker missing')
    source=source.replace(marker,'#include "FighterCloudBurstF676.inc"')
    marker='        case 0x2F1: g_FighterProbeMarker = 754; break;'
    need(source.count(marker)==1,'original physical 2F1 native source marker missing')
    source=source.replace(marker,'')
    need(source.count('        case 0x2F8: g_FighterProbeMarker = 761; break;')==1,
         'real original following physical 2F8 source marker missing')
    return source


def expected_symbol(action,ordinal,target):
    if target==0x00453A70:
        if action==0x2F1:return 'SpawnWithFloatAt453A70'
        return 'SpawnDirectedAt453A70' if ordinal in (114,125) else 'SpawnFloatXRawYAt453A70'
    need(target in SYMBOLS,f'original unknown native physical PE source destination {target:#x}')
    return SYMBOLS[target]


def verify_negative(reader,dec,code,refs,originals,first_ordinal,shared_exit,h,following_native=None,*,
                    source_native_GPR_counts=None):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    receipts=[]
    pos=first_ordinal
    for action in ACTIONS:
        native,lo,hi,true_fields=originals[action]
        generated=ins[pos:pos+len(native)]
        expected_len,expected_bytes,expected_fields,want_wrong,want_first=GEOMETRY[action]
        need(len(generated)==len(native)==expected_len
             and all(a.size==b.size for a,b in zip(native,generated))
             and generated[-1].mnemonic=='jmp'
             and generated[-1].size==5
             and generated[-1].op_str==shared_exit
             and generated[-1].address+generated[-1].size-generated[0].address==hi-lo,
             f'{action:#x}: original entire source native CODE/x86/CFG geometry changed')
        physical=[f for f in refs if generated[0].address<=f['offset']<generated[-1].address+generated[-1].size]
        need(len(physical)==len(true_fields)==expected_fields,
             f'{action:#x}: original genuine physical typed PE/COFF fields differ')
        for ordinal,target,mn in true_fields:
            a,b=native[ordinal],generated[ordinal]
            if mn=='call':operand=f'0x{target:x}'
            elif mn=='movsx':operand=f'{a.op_str.split(", ")[0]}, byte ptr [0x{target:x}]'
            else:operand=f'dword ptr [0x{target:x}]'
            need(a.mnemonic==b.mnemonic==mn and a.op_str==operand,
                 f'{action:#x}: original physical PE x86{ordinal} destination changed')
            fields=[f for f in physical if b.address<=f['offset']<b.address+b.size]
            need(len(fields)==1 and fields[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and fields[0]['addend']==0 and fields[0]['local_symbol_offset'] is None
                 and expected_symbol(action,ordinal,target) in fields[0]['symbol'],
                 f'{action:#x}: source typed PE/COFF symbol field at native x86{ordinal} differs')
        l,r=h['f598'].normalized(native),h['f598'].normalized(generated)
        excluded={i for i,t,m in true_fields if m!='call'}
        bad=[(i,a,b) for i,(a,b) in enumerate(zip(l,r)) if a!=b and i not in excluded]
        # Later independently reconstructed original game cases may
        # naturally alter VC7.1 register phases even for this already
        # recovered complete 342/274-x86 native-shaped source. Those are
        # real nonexact source differences; never turn them into strict.
        if source_native_GPR_counts is not None:
            need(action in source_native_GPR_counts,
                 f'original {action:#x} GPR regression does not have an independent count')
            want_wrong,want_first=source_native_GPR_counts[action]
        need(len(bad)==want_wrong and bad[0][0]==want_first,
             f'{action:#x}: independently observed original GPR phase negative pattern changed: {bad[:7]} count={len(bad)}')
        # This selected original native case has NO additional stack locals.
        # Do not use F598's broad stack-slot normalization as false proof
        # if a future compiler variant creates a fake local.
        ebp_orig=[(i,a.op_str) for i,a in enumerate(native) if '[ebp' in a.op_str]
        ebp_gen=[(i,b.op_str) for i,b in enumerate(generated) if '[ebp' in b.op_str]
        need([i for i,_ in ebp_orig]==[i for i,_ in ebp_gen]
             and all('[ebp - 0x44]' in a and '[ebp - 8]' in b
                     for (i,a),(j,b) in zip(ebp_orig,ebp_gen)),
             f'{action:#x}: unexpected original or source EBP local or frame offset')
        receipts.append({'original_native_action':f'0x{action:03X}',
                         'original_real_physical_start':f'0x{lo:08X}',
                         'next_actual_original_native_handler':f'0x{hi:08X}',
                         'original_complete_x86_instructions':len(native),
                         'original_entire_native_internal_CODE_bytes':hi-lo,
                         'new_normal_CPP_internal_CODE_bytes':hi-lo,
                         'genuine_typed_PE_COFF_fields':len(physical),
                         'actual_nonfield_GPR_role_mismatches':len(bad),
                         'strict_original_native_case':False,
                         'new_accepted_whole_authored_CODE_bytes':0})
        pos+=len(native)
    if following_native is None:
        need(ins[pos].mnemonic=='mov' and ins[pos].op_str.endswith(', 0x2f9'),
             'real original physical following native 2F8 marker missing after 2F1')
    else:
        need(following_native==0x2F8
             and ins[pos].mnemonic=='mov'
             and ins[pos].op_str.endswith(', dword ptr [ebp - 8]')
             and ins[pos+1].mnemonic=='movsx'
             and ins[pos+1].op_str.endswith('+ 0x62]'),
             'original native 2F8 must genuinely follow whole 2F1 source body')
    return receipts if following_native is None else (receipts,pos)


def main():
    f651=load('f676_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f676_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f676_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f676_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f676_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f676_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f676_f664','scripts/verify-fighter-special-stage-f664.py')
    f668=load('f676_f668','scripts/verify-fighter-counter-special-f668.py')
    f669=load('f676_f669','scripts/verify-fighter-post-counter-f669.py')
    f671=load('f676_f671','scripts/verify-fighter-four-shot-barrage-f671.py')
    f673=load('f676_f673','scripts/verify-fighter-ground-wave-f673.py')
    f674=load('f676_f674','scripts/verify-fighter-cloud-rain-f674.py')
    h=f651.load_helpers()
    reader=load('f676_reader','scripts/compare-coff-function.py')
    acts=load('f676_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original=original_cases(reader,pe,dec,boss,mapped)
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
    old673=f673.actual_native(reader,pe,dec,boss,mapped)
    old674=f674.original_case(reader,pe,dec,boss,mapped)
    terminal=f674.true_terminal(reader,pe,dec,boss,mapped)
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
    source=f674.source_with_rain_and_terminal(source)
    source=source_with_burst(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-original-2F0-2F1-cloud-burst.cpp'
    obj=OUT/'Boss00543210-original-2F0-2F1-cloud-burst.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'pinned VC7.1 original complete selected giant compile failed: '+cp.stderr[-500:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,old651,h,following_native=0x12C)
    _,idx=f653.verify_new(reader,pe,dec,code,refs,old,old653,h,following_native=0x12F)
    _,idx=f654.verify_new(reader,pe,dec,code,refs,old654,old,idx,h,following_native=0x131)
    _,idx=f656.verify_native(reader,pe,dec,code,refs,old656,old,idx,h,following_native=0x186)
    _,neg186,idx=f657.verify_new(reader,pe,dec,code,refs,old657,old,idx,h,following_native=0x18A)
    neg661=f661.verify_nonstrict(reader,pe,dec,code,refs,old661,old,idx,h)
    _,idx=f664.verify_new_code(reader,pe,dec,code,refs,boss,mapped,old664,h,following_native=0x252)
    full=[]
    for x in dec.disasm(code,0):
        full.append(x)
        if x.mnemonic=='ret':break
    shared=full[old['continuation_source_ordinal']-1].op_str
    _,idx=f668.verify_inner(reader,pe,dec,code,refs,old668,idx,shared,h,following_native=0x255)
    _,idx=f669.verify_native(reader,pe,dec,code,refs,old669,idx,shared,h,following_native=0x258)
    neg671=f671.verify_negative(reader,pe,dec,code,refs,old671,idx,shared,h)
    strict673=f673.verify_groundwave(reader,dec,code,refs,old673,shared,h)
    strict674,strict_terminal,ordinal=f674.verify_native(reader,dec,code,refs,old674,terminal,shared,h,following_native=0x2F0,terminal_expect_strict=True)
    negative=verify_negative(reader,dec,code,refs,original,ordinal,shared,h)
    receipt={'original_selected_whole_giant':'0x00543210',
             'entire_original_parent_CODE_bytes_still_NONEXACT':boss['size'],
             'original_separately_owned_after_RET_switch_DATA_bytes':boss['postret_size'],
             'all_previous_27_strict_original_native_case_interiors_rechecked_same_parent':True,
             'original_186_18A_18B_258_EBP_negative_controls_preserved':True,
             'original_terminal_31C_newly_STRICT_due_to_recovered_2F0_2F1_context':True,
             'complete_original_afterRET_switch_DATA_reverified':True,
             'new_source_backed_NONSTRICT_complete_native_2F0_2F1_cases':negative,
             'original_source_backed_but_nonexact_total_native_CODE_bytes':sum(x['original_entire_native_internal_CODE_bytes'] for x in negative),
             'new_strict_complete_original_terminal_case':strict_terminal,
             'new_strict_native_original_case_count':1,
             'new_strict_original_internal_CODE_bytes':219,
             'new_accepted_entire_GAME_AUTHORED_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F676 selected full original giant 00543210: two complete real native '
          '2F0/2F1 source cases, 616 full original x86 /2,146 complete original '
          'case CODE B /65 physical zero-addend original PE/COFF fields. '
          'All native instruction widths/CFG grammar align, but 147/170 '
          'real original GPR register-phase differences remain: NONSTRICT. '
          'All previously 27 context-strict original native cases, four EBP '
          'scratch negatives, newly STRICT 31C terminal and full afterRET '
          'switch DATA rechecked in SAME new VC7.1 parent; original '
          'terminal 31C (63 x86/219 B/7 fields) and zero whole authored '
          'function credit and no 943-unit mass replay.')


if __name__=='__main__':
    main()
