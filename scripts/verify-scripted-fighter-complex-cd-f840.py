#!/usr/bin/env python3
"""F840: genuine original 387B/113-x86/8-field CD in the selected fighter.

Recompile only actual affected 005214B0 whole giant after regenerating
F839 native CC and real preceding cases. Actor-specific CD stage3
position11, speed17.5, drag0.8, no earlier CC auxiliary branch;
x87 operand order and unconditional virtual vtable call matter.
All original native CD machine bytes match except two genuine
whole-giant epilogue JMP relative byte pairs. Recheck CC, C8-CB,
CF-D2, original F806 default and all five 901B packed tables.
No cropped case, accepted exact CODE or mass cold replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f840-scripted-complex-cd'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
CD_WRONG=[186,187,383,384]
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
def need(x,msg):
    if not x:raise ValueError(msg)
def ld(t,f):
    sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'missing native PE helper '+f)
    m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m)
    return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
      str(R/'scripts/verify-scripted-fighter-complex-cc-f839.py')],
      cwd=R,capture_output=True,text=True,timeout=1250)
    (O/'f839-prior-physical.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'F839 whole prior original source/PE proof failed '+(p.stdout+p.stderr)[-810:])
    src=(R/'.analysis/f839-scripted-stage-cc/Boss005214B0-F839-whole.cpp').read_text()
    old='        case 0xCD: g_FighterProbeMarker = 206; break;'
    fragment=(R/'probes/FighterScriptedComplexCDF840.inc').read_text()
    need(src.count(old)==1 and fragment.count('case 0xCD:')==1
         and fragment.count('NativeVirtualFrameAdvance();')==1
         and fragment.count('return;')==2 and
         fragment.count('++I16(0x64);')==1
         and fragment.count('++I16(0x62);')==1
         and 'POS48+POS54<=g_ThresholdAt0065782C' in fragment
         and 'POS54=17.5f' in fragment
         and 'POS5C=0.8f' in fragment,
         'real original CD game stage/virtual callback source changed')
    return src.replace(old,'#include "FighterScriptedComplexCDF840.inc"',1)
def compile_one(src):
    cpp=O/'Boss005214B0-F840-whole.cpp';obj=O/'Boss005214B0-F840-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=env,capture_output=True,text=True,timeout=290)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'original CD whole giant source compilation failed '+(p.stdout+p.stderr)[-750:])
    return obj
def main():
    rd=ld('f840rd','compare-coff-function.py')
    ac=ld('f840ac','report-fighter-action-handlers.py')
    f834=ld('f840f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f840f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=ld('f840zero','verify-fighter-actionzero-natural-source.py')
    switch=ld('f840switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
        if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'genuine original 46KB game identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={q['action']:int(q['handler'],16) for q in mp}
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(20950,5682,847,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'actual new whole VC7.1 CODE/x86/COFF/native receiver frame changed')
    dns,sps,mp0=zero.verify_physical_tables(boss,report,pe,rd,switch,ins,code,refs,ret)
    need(dns>0 and sps>0 and mp0>0,'original 5 afterRET packed tables not verified')
    mark=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0xcf')
          and any('g_FighterProbeMarker' in r['symbol']
                  and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(mark)==1 and mark[0]>=113+126,'original following CE marker not unique')
    k=mark[0]
    cd=ins[k-113:k]
    result=f834.physical_case(rd,pe,d,code,refs,cd,by,0xcd,387,8,CD_WRONG,0xce,f820)
    need(result['native_complete_x86']==113
         and result['original_native_enclosing_parent_JMP_exit_ordinals']==[55,112]
         and cd[55].op_str==cd[112].op_str==hex(ret-4)
         and cd[42].op_str=='dword ptr [ecx + 0x48]'
         and cd[43].op_str=='dword ptr [edx + 0x54]'
         and cd[102].mnemonic=='jl' and cd[102].op_str==hex(cd[108].address),
         'actual original CD float order/virtual dispatch stage CFG changed')
    cc=ins[k-113-126:k-113]
    orig_cc=f834.physical_case(rd,pe,d,code,refs,cc,by,0xcc,428,10,
                              [186,187,424,425],0xcd,f820)
    need(orig_cc['native_complete_x86']==126,'prior real CC source changed')
    first=k-113-126-sum(x[2] for x in FOUR)
    need(first>=0,'real old C8-CB original source truncated')
    prior=ins[first:k-113-126];old=[];cursor=0
    for a,size,nx,nf,bad,nxt in FOUR:
        section=prior[cursor:cursor+nx];cursor+=nx
        old.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,size,nf,bad,nxt,f820))
    need(cursor==len(prior),'original C8-CB full case source boundary mismatch')
    other=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x12d')
       and any('g_FighterProbeMarker' in r['symbol']
           and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(other)==1 and other[0]>=223,'original following 12C case marker not unique')
    preceding=ins[other[0]-223:other[0]]
    later=[];start=0
    for a,size,nx,nf,bad,nxt in LATER:
        section=preceding[start:start+nx];start+=nx
        later.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,size,nf,bad,nxt,f820))
    need(start==223,'original physical later CF/D0/D1/D2 cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,tail,0x52cb25,fields,ret-46,3)
    need(len(mask)==12 and
         all(tail[i]==code[ret-46+i] for i in range(46) if i not in mask)
         and len(list(d.disasm(tail,0x52cb25)))==16,
         'native original 46B shared default no longer 34/34 nonrelocation exact')
    out={'original_whole_game':'0x005214B0',
         'original_native_whole_CODE_B':46755,
         'current_whole_source_CODE_B':ret,
         'new_CD_true_complete_source':result,
         'prior_CC_original_real_PE_fields_reverified':orig_cc,
         'previous_four_original_C8_C9_CA_CB':old,
         'following_original_CF_D0_D1_D2_reverified':later,
         'native_CD_only_two_giant_JMP_operand_pairs_differ':CD_WRONG,
         'original_default_46B_nonrelocation':'34/34',
         'original_default_3_typed_PE_calls':3,
         'real_native_5_afterRET_tables_checked':True,
         'original_separate_afterRET_DATA_B':901,
         'original_entire_46755B_fighter_exact':False,
         'accepted_new_whole_callable_CODE_B':0,'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F840 selected original CD 387B/113x86/8 real PE fields in 20950B/5682x86 whole fighter, only 2 genuine enclosing epilogue JMP operand pairs differ. Actual CC and C8-CB, CF-D2, default 46B 34/34 and all five original afterRET packed tables physically checked. Whole giant NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F840 selected original CD whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
