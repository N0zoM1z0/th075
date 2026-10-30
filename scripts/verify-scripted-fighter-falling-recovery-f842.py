#!/usr/bin/env python3
"""F842: native 12C/12D/12E original falling recovery in current whole fighter.

Reverify selected F841 whole original C8-CE/CF-D2 source, then
compile ONE new entire VC7.1 parent with three genuine 12C/12D/12E
cases. Physically read actor's stage preparation 1/3/2 and real
animations 1B/1C/1C (different from other-actor F653). Original
207/219/207B, 59/61/59 x86, six true PE/COFF fields per case.
All nonrelocation bytes match except one authentic final parent
JMP two-byte pair per case; recheck previous eleven cases and
all five separate original 901B packed switch tables.
Whole original 46,755B remains NONEXACT; no split-case credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f842-scripted-falling-recovery'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
PARAM={
 0x12c:(0,1,0x1b,0,207,59,[203,204],0x12d),
 0x12d:(0,3,0x1c,1,219,61,[215,216],0x12e),
 0x12e:(2,2,0x1c,0,207,59,[203,204],0x12f),
}
PRIOR=[
 (0xc8,657,190,17,[184,185,202,203,267,268,364,365,382,383,446,447,653,654],0xc9),
 (0xc9,279,86,11,[275,276],0xca),
 (0xca,418,121,11,[203,204,414,415],0xcb),
 (0xcb,496,141,12,[214,215,492,493],0xcc),
 (0xcc,428,126,10,[186,187,424,425],0xcd),
 (0xcd,387,113,8,[186,187,383,384],0xce),
 (0xce,387,113,8,[186,187,383,384],0xcf),
 (0xcf,114,30,4,[110,111],0xd0),
 (0xd0,195,60,6,[154,155,191,192],0xd1),
 (0xd1,199,59,8,[26,27,195,196],0xd2),
 (0xd2,251,74,10,[26,27,247,248],0x12c),
]
def need(v,msg):
    if not v:raise ValueError(msg)
def ld(t,f):
    sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'original PE helper missing '+f)
    m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m)
    return m
def full_source(by,rd,pe,d):
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-complex-ce-f841.py')],
       cwd=R,capture_output=True,text=True,timeout=1200)
    (O/'f841-prior-native-proof.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'prior original 46KB fighter CE/CC-D2 PE validation failed '+(p.stdout+p.stderr)[-770:])
    src=(R/'.analysis/f841-scripted-complex-ce/Boss005214B0-F841-whole.cpp').read_text()
    fragment=(R/'probes/FighterScriptedFallingRecoveryF842.inc').read_text()
    need(fragment.count('case F653_ACTION:')==1
         and fragment.count('return;')==1 and
         'g_JumpGroundCorrectionAt00658058' in fragment,
         'real actor falling state native movement source changed')
    for act,(next_state,frame,anim,clear,size,nx,wrong,nxt) in PARAM.items():
        original=list(d.disasm(rd.pe_bytes_at(pe,by[act],by[nxt]-by[act]),by[act]))
        need(len(original)==nx and by[nxt]-by[act]==size
             and original[44].mnemonic=='push'
             and original[44].op_str==str(next_state)
             and original[51 if act==0x12d else 49].mnemonic=='cmp'
             and original[51 if act==0x12d else 49].op_str.endswith(', '+str(frame))
             and original[57 if act==0x12d else 55].mnemonic=='push'
             and original[57 if act==0x12d else 55].op_str==hex(anim)
             and (original[48].mnemonic=='mov' and '+ 0xf00]' in original[48].op_str)==bool(clear),
             'current actor original PE native prep/action/frame differs '+hex(act))
        old=f'        case 0x{act:X}: g_FighterProbeMarker = {act+1}; break;'
        need(src.count(old)==1,'real original full source state placeholder missing '+hex(act))
        defs={'F653_ACTION':f'0x{act:X}', 'F653_NEXT_ACTION':str(next_state),
              'F653_PREPARE_FRAME':str(frame), 'F653_PREPARE_ANIM':f'0x{anim:X}',
              'F653_CLEAR_F00':str(clear)}
        block='\n'.join('#define '+k+' '+v for k,v in defs.items())
        block+='\n#include "FighterScriptedFallingRecoveryF842.inc"\n'
        block+='\n'.join('#undef '+k for k in defs)
        src=src.replace(old,block,1)
    need(src.count('        case 0x12F: g_FighterProbeMarker = 304; break;')==1,
         'real next 12F source original marker missing')
    return src
def compile_one(src):
    cpp=O/'Boss005214B0-F842-whole.cpp';obj=O/'Boss005214B0-F842-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=E,capture_output=True,text=True,timeout=280)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'current original 12C/12D/12E entire VC7.1 source failed '+(p.stdout+p.stderr)[-850:])
    return obj
def main():
    rd=ld('f842rd','compare-coff-function.py')
    ac=ld('f842ac','report-fighter-action-handlers.py')
    f834=ld('f842f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f842f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=ld('f842zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f842switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original physical fighter or switch DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(full_source(by,rd,pe,d))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(21910,5966,869,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current whole actor ABI, native source size or switch DATA changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'five true original packed switch tables not verified')
    marker=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x130')
        and any('g_FighterProbeMarker' in r['symbol']
             and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=179,'next original 12F source marker not unique')
    k=marker[0]
    current=ins[k-179:k];off=0;new=[]
    for act,(next_state,frame,anim,clear,size,nx,wrong,nxt) in PARAM.items():
        seg=current[off:off+nx];off+=nx
        row=f834.physical_case(rd,pe,d,code,refs,seg,by,act,size,6,wrong,nxt,f820)
        need(row['native_complete_x86']==nx
             and row['original_native_enclosing_parent_JMP_exit_ordinals']==[nx-1]
             and seg[-1].op_str==hex(ret-4),
             'original falling source actor x86/parent-epilogue branch not exact')
        new.append(row)
    need(off==179,'three authentic original falling case x86 lengths changed')
    # Every source-backed previous C8..D2 case must be compared again
    # against its native true PE fields in the NEW whole object.
    start=k-179-sum(x[2] for x in PRIOR)
    need(start>=0,'preceding genuine original storm/complex/reflect cases truncated')
    old=ins[start:k-179];j=0;prior=[]
    for act,size,nx,nf,bad,nxt in PRIOR:
        seg=old[j:j+nx];j+=nx
        result=f834.physical_case(rd,pe,d,code,refs,seg,by,act,size,nf,bad,nxt,f820)
        prior.append(result)
    need(j==len(old),'previous eleven original whole interior cases no longer contiguous')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
          [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong==[10,12,16,19],
         'actual new whole actor 46B common getter GPR phase changed')
    out={'real_original_actor':'0x005214B0',
        'original_entire_whole_CODE_B':46755,
        'current_whole_Cpp_CODE_B':ret,
        'three_original_falling_cases_reconstructed':new,
        'new_source_backed_native_inner_CODE_B':633,
        'new_original_x86':179,'original_typed_PE_fields':18,
        'actual_actor_prepare_frame_12C_12D_12E':[1,3,2],
        'actual_actor_prepare_animation_12C_12D_12E':['0x1B','0x1C','0x1C'],
        'previous_native_C8_to_D2_cases_physically_rechecked':prior,
        'real_native_default_46B_GPR_wrong_offsets':wrong,
        'original_five_901B_afterRET_tables_rechecked':True,
        'real_separate_afterRET_DATA_B':901,
        'whole_native_original_exact':False,'accepted_whole_callable_CODE_delta':0,
        'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F842 three original 12C/12D/12E native recovery cases 207/219/207B, 179x86, 18 typed PE refs in ONE 21910B/5966-x86 whole fighter; only 2 real enclosing giant epilogue JMP operand bytes differ per case. Earlier eleven complete C8..D2 original state sources, 901B five switch tables and 46B default physical fields rechecked. Giant still NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F842 real actor 12C/12D/12E source verification FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
