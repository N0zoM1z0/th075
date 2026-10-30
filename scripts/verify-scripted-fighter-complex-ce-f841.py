#!/usr/bin/env python3
"""F841: original selected actor CE 387B/113 x86/8 genuine PE fields.

Regenerate whole F840 actor CC/CD and previous original sources from
physical target, then compile one growing VC7.1 fighter including true
CE, with original stage3 POS -11.0f, speed17.5f, drag0.8f,
unconditional virtual vtable callback outside stage decrement and
original float operand order. Verify actual CE 387B/113-x86 and all
eight original typed fields; only two genuine whole-giant long JMP
operand pairs differ. Earlier CC/CD, all C8-CB, CF-D2, common getter
46B and FIVE real 901B packed tables rechecked. Original whole
46755B remains nonexact, no independent case CODE or mass cold replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f841-scripted-complex-ce'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
JMP_BAD=[186,187,383,384]
FOUR=[
 (0xc8,657,190,17,[184,185,202,203,267,268,364,365,382,383,446,447,653,654],0xc9),
 (0xc9,279,86,11,[275,276],0xca),
 (0xca,418,121,11,[203,204,414,415],0xcb),
 (0xcb,496,141,12,[214,215,492,493],0xcc),
]
LATER=[
 (0xcf,114,30,4,[110,111],0xd0),
 (0xd0,195,60,6,[154,155,191,192],0xd1),
 (0xd1,199,59,8,[26,27,195,196],0xd2),
 (0xd2,251,74,10,[26,27,247,248],0x12c),
]
def need(v,m):
    if not v:raise ValueError(m)
def ld(t,f):
    sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'native PE helper not found '+f)
    m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m)
    return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-complex-cd-f840.py')],
       cwd=R,capture_output=True,text=True,timeout=1250)
    (O/'f840-prior-original-proof.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'prior whole selected CD native PE proof failed '+(p.stdout+p.stderr)[-650:])
    src=(R/'.analysis/f840-scripted-complex-cd/Boss005214B0-F840-whole.cpp').read_text()
    old='        case 0xCE: g_FighterProbeMarker = 207; break;'
    inc=(R/'probes/FighterScriptedComplexCEF841.inc').read_text()
    need(src.count(old)==1 and inc.count('case 0xCE:')==1
         and inc.count('return;')==2
         and inc.count('NativeVirtualFrameAdvance();')==1
         and 'POS=-11.0f;' in inc
         and 'POS54=17.5f;' in inc
         and 'POS5C=0.8f;' in inc
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc,
         'physical original CE stage3/x87/virtual method source changed')
    return src.replace(old,'#include "FighterScriptedComplexCEF841.inc"',1)
def compile_one(src):
    cpp=O/'Boss005214B0-F841-whole.cpp';obj=O/'Boss005214B0-F841-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=290)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'full selected original CE C++ codegen failed '+(p.stdout+p.stderr)[-750:])
    return obj
def main():
    rd=ld('f841rd','compare-coff-function.py')
    ac=ld('f841ac','report-fighter-action-handlers.py')
    f834=ld('f841f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f841f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=ld('f841zero','verify-fighter-actionzero-natural-source.py')
    switch=ld('f841switch','verify-fighter-natural-switch-probes.py')
    D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original complete fighter identity changed')
    report,mp=ac.report_boss(rd,pe,D,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in D.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(21322,5793,854,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'source original frame/switch ABI or full x86 geometry wrong')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,switch,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all five afterRET native tables not checked')
    m=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x12d')
       and any('g_FighterProbeMarker' in r['symbol']
            and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(m)==1 and m[0]>=223+113*2+126,'real following 12C marker not unique')
    follow=m[0]
    cf_start=follow-223
    ce=ins[cf_start-113:cf_start]
    result=f834.physical_case(rd,pe,D,code,refs,ce,by,0xce,387,8,JMP_BAD,0xcf,f820)
    need(result['native_complete_x86']==113
         and result['original_native_enclosing_parent_JMP_exit_ordinals']==[55,112]
         and ce[55].op_str==ce[112].op_str==hex(ret-4)
         and ce[79].op_str=='dword ptr [edx + 0x50], 0xc1300000'
         and ce[102].mnemonic=='jl' and ce[102].op_str==hex(ce[108].address),
         'native CE actual stage3 -11.0f or unconditional virtual call differs')
    prior=[]
    prev_end=cf_start-113
    for action,nx,size,nf,next_action in ((0xcd,113,387,8,0xce),(0xcc,126,428,10,0xcd)):
        seg=ins[prev_end-nx:prev_end]
        result0=f834.physical_case(rd,pe,D,code,refs,seg,by,action,size,nf,
                       [186,187,383,384] if action==0xcd else [186,187,424,425],
                       next_action,f820)
        prior.append(result0);prev_end-=nx
    initial=ins[prev_end-sum(x[2] for x in FOUR):prev_end]
    cursor=0;storm=[]
    for action,size,nx,nf,wrong,nextact in FOUR:
        seg=initial[cursor:cursor+nx];cursor+=nx
        storm.append(f834.physical_case(rd,pe,D,code,refs,seg,by,action,size,nf,wrong,nextact,f820))
    need(cursor==len(initial),'four original storm source cases truncated')
    later=ins[cf_start:follow];pos=0;last=[]
    for action,size,nx,nf,wrong,nextact in LATER:
        seg=later[pos:pos+nx];pos+=nx
        last.append(f834.physical_case(rd,pe,D,code,refs,seg,by,action,size,nf,wrong,nextact,f820))
    need(pos==223,'original genuine CF/D0/D1/D2 source truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
            [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    need(len(mask)==12 and
         all(tail[i]==code[ret-46+i] for i in range(46) if i not in mask)
         and len(list(D.disasm(tail,0x52cb25)))==16,
         'original whole shared getter native nonrelocation 34/34 changed')
    out={'native_original_giant':'0x005214B0',
         'native_complete_whole_CODE_B':46755,
         'new_current_entire_source_CODE_B':ret,
         'original_CE_full_native_case':result,
         'original_CC_CD_native_cases_rechecked':prior,
         'earlier_C8_C9_CA_CB_native_source_rechecked':storm,
         'later_CF_D0_D1_D2_native_source_rechecked':last,
         'true_original_CE_float_initial_position':-11.0,
         'original_CE_only_giant_exit_JMP_byte_negatives':JMP_BAD,
         'real_default_46B_nonrelocation':'34/34',
         'native_default_three_real_PE_calls':3,
         'native_original_five_packed_switch_tables_rechecked':True,
         'separate_original_afterRET_DATA_B':901,
         'original_whole_giant_exact':False,'accepted_new_whole_callable_CODE_B':0,
         'all_corpus_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F841 original CE 387B/113-x86/8 true PE fields native except two parent-epilogue JMP pairs, in 21322B/5793-x86 whole fighter. CC/CD, C8-CB, CF-D2, five packed 901B tables and default 46B native 34/34 source rechecked. Whole 46755B NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F841 original CE selected whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
