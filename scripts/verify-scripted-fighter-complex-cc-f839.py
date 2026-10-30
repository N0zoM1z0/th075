#!/usr/bin/env python3
"""F839: true original 428B/126-x86/10-PE-field CC in selected giant.

Regenerate prior F837 complete C8-CB normal C++ source and physical
five native jump tables; introduce real actor-specific 0xCC: genuine
x87 POS48+POS54 operand order, stage3 conditional frame/flag,
and native virtual vtable call OUTSIDE the stage>=max decrement.
Recompile ONLY selected entire original-shaped VC7.1 parent.
Original CC and all eight source-backed C8-CB/CF-D2 cases now
differ only by physical enclosing whole-fighter epilogue long-JMP
operands, while original 46B default/getter remains 34/34 correct
nonrelocation bytes and 3 true native PE calls. Full 46755B nonexact.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f839-scripted-stage-cc'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
CC_WRONG=[186,187,424,425]
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
def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'native PE helper missing '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m
def current_source():
    O.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-fourway-cb-f837.py')],
       cwd=R,capture_output=True,text=True,timeout=1300)
    (O/'f837-prior-physical-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'F837 preceding whole original fighter source not reverified '+
         (run.stdout+run.stderr)[-800:])
    src=(R/'.analysis/f837-scripted-fourway-cb/Boss005214B0-F837-whole.cpp').read_text()
    fragment=(R/'probes/FighterScriptedComplexCCF839.inc').read_text()
    marker='        case 0xCC: g_FighterProbeMarker = 205; break;'
    anchor='void PrepareActionAt453D60(int);'
    need(src.count(marker)==src.count(anchor)==1 and
         fragment.count('case 0xCC:')==1
         and fragment.count('return;')==2
         and fragment.count('NativeVirtualFrameAdvance();')==1
         and 'POS48+POS54<=g_ThresholdAt0065782C' in fragment
         and '++I16(0x64);' in fragment and '++I16(0x62);' in fragment,
         'actual original 0xCC source and physical stage expressions changed')
    src=src.replace(anchor,anchor+' void SetupCollisionAt454BC0(int,int,int);'
         ' void SpawnRawAt453C80(int,int,int,int,int);'
         ' virtual void NativeVirtualFrameAdvance();',1)
    return src.replace(marker,'#include "FighterScriptedComplexCCF839.inc"',1)
def compile_one(source):
    cpp=O/'Boss005214B0-F839-whole.cpp';obj=O/'Boss005214B0-F839-whole.obj'
    cpp.write_text(source)
    E=os.environ.copy()
    E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=300)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'real selected CC normal VC7.1 whole fighter compile failed '+(p.stdout+p.stderr)[-700:])
    return obj
def main():
    rd=ld('f839rd','compare-coff-function.py')
    ac=ld('f839ac','report-fighter-action-handlers.py')
    f834=ld('f839f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f839f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=ld('f839zero','verify-fighter-actionzero-natural-source.py')
    switch=ld('f839switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
         if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'real original 46KB giant identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(current_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(20578,5571,840,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'real current whole source CODE/x86/COFF/frame/table geometry changed')
    ds,sp,mp=zero.verify_physical_tables(boss,report,pe,rd,switch,ins,code,refs,ret)
    need(ds>0 and sp>0 and mp>0,'all five original packed jump DATA tables not reverified')
    marker=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0xce')
       and any('g_FighterProbeMarker' in r['symbol']
           and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=126,'original next CD source marker missing')
    k=marker[0]
    cc=ins[k-126:k]
    result=f834.physical_case(rd,pe,d,code,refs,cc,by,0xcc,428,10,CC_WRONG,0xcd,f820)
    need(result['native_complete_x86']==126
         and result['original_native_enclosing_parent_JMP_exit_ordinals']==[55,125]
         and cc[55].op_str==cc[125].op_str==hex(ret-4)
         and cc[42].op_str=='dword ptr [ecx + 0x48]'
         and cc[43].op_str=='dword ptr [edx + 0x54]'
         and cc[115].mnemonic=='jl'
         and cc[115].op_str==hex(cc[121].address),
         'real selected CC float evaluation order/unconditional native vtable callback incorrect')
    # Recheck prior four full storm C8..CB cases. Each original PE
    # typed symbol and authentic external giant JMP is checked.
    start=k-126-sum(x[2] for x in FOUR)
    need(start>=0,'preceding true four native C8-CB actions truncated')
    seq=ins[start:k-126];cursor=0;previous=[]
    for action,nb,nx,nf,wrong,nextact in FOUR:
        part=seq[cursor:cursor+nx];cursor+=nx
        result4=f834.physical_case(rd,pe,d,code,refs,part,by,action,nb,nf,wrong,nextact,f820)
        need(result4['native_complete_x86']==nx,'earlier fourway opcode count changed')
        previous.append(result4)
    need(cursor==len(seq),'previous four source case extents changed')
    # CF/D0/D1/D2 native GPR role comparison in THIS new source.
    last_marker=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x12d')
       and any('g_FighterProbeMarker' in r['symbol']
           and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(last_marker)==1,'original following 12C case marker missing')
    last=ins[last_marker[0]-223:last_marker[0]]
    cursor=0;later=[]
    for action,nb,nx,nf,wrong,nextact in LATER:
        part=last[cursor:cursor+nx];cursor+=nx
        later.append(f834.physical_case(rd,pe,d,code,refs,part,by,action,nb,nf,wrong,nextact,f820))
    need(cursor==223,'four genuine later native original cases truncated')
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,native_tail,0x52cb25,fields,ret-46,3)
    need(len(mask)==12 and
         all(native_tail[i]==code[ret-46+i] for i in range(46) if i not in mask)
         and len(list(d.disasm(native_tail,0x52cb25)))==16,
         'full original common getter must be 34/34 native nonrelocation bytes and 3 PE refs')
    out={'original_whole_actor':'0x005214B0',
      'native_entire_callable_CODE_B':46755,'current_whole_Cpp_CODE_B':ret,
      'new_original_CC_native_full_case':result,
      'prior_C8_C9_CA_CB_case_original_physically_rechecked':previous,
      'following_CF_D0_D1_D2_case_original_physically_rechecked':later,
      'actual_CC_original_float_and_unconditional_virtual_call_recovered':True,
      'original_CC_nonrelocation_wrong_only_external_JMP_offsets':CC_WRONG,
      'native_real_default_46B_nonrelocation_bytes':'34/34',
      'original_default_three_PE_calls':3,
      'original_five_packed_afterRET_jump_tables_checked':True,
      'separate_native_afterRET_DATA_B':901,
      'original_whole_function_exact':False,'new_accepted_callable_CODE_B':0,
      'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F839 full original CC 428B/126x86/10 physical native PE fields within new 20578B/5571x86 entire giant, only 2 original encompassing final JMP operand pairs wrong. Restored native x87 POS48+POS54 order, genuine unconditional vtable frame call. C8-CB plus CF-D2 native physical sources and FIVE packed 901B tables rechecked, native default 34/34. Whole original giant NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as ex:
        print('F839 original selected CC whole fighter FAILED:',ex,file=sys.stderr)
        raise SystemExit(1)
