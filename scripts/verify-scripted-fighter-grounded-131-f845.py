#!/usr/bin/env python3
"""F845: selected original 131 native 202B/58 x86/5 true PE fields.

Rebuild the affected F844 whole parent and use real actor native
stage3 animation 1D, not previous 130 animation1C. Compare entire
generated 131 case, five original PE field positions/types/targets,
prior true 130, 12C-12F and C8-D2 plus the FIVE 901B native
afterRET packed tables. Only genuine encompassing parent epilogue
JMP operands differ per case, while shared getter still has
4 honest GPR nonfield byte differences. Whole original NONEXACT.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f845-scripted-stage131'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
FALL=[(0x12c,207,59,6,[203,204],0x12d),
      (0x12d,219,61,6,[215,216],0x12e),
      (0x12e,207,59,6,[203,204],0x12f),
      (0x12f,207,59,6,[203,204],0x130)]
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
def need(p,msg):
 if not p:raise ValueError(msg)
def ld(tag,name):
 sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
 need(sp and sp.loader,'missing native reader '+name)
 m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
 return m
def new_source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 run=subprocess.run([str(R/'scripts/repo-python'),
    str(R/'scripts/verify-scripted-fighter-grounded-130-f844.py')],
    cwd=R,capture_output=True,text=True,timeout=1250)
 (O/'f844-prior-whole-original.log').write_text(run.stdout+run.stderr)
 need(run.returncode==0,'prior F844 original parent PE verification failed '+(run.stdout+run.stderr)[-780:])
 original=list(d.disasm(rd.pe_bytes_at(pe,by[0x131],by[0x133]-by[0x131]),by[0x131]))
 need(len(original)==58 and by[0x133]-by[0x131]==202
      and original[48].mnemonic=='cmp' and original[48].op_str.endswith(', 3')
      and original[54].mnemonic=='push' and original[54].op_str=='0x1d'
      and original[-1].op_str=='0x52cb4f',
      'actual original actor 0x131 PE stage3 animation parameter different')
 source=(R/'.analysis/f844-scripted-stage130/Boss005214B0-F844-whole.cpp').read_text()
 marker='        case 0x131: g_FighterProbeMarker = 306; break;'
 fragment=(R/'probes/FighterScriptedGrounded131F845.inc').read_text()
 need(source.count(marker)==1 and fragment.count('case 0x131:')==1
      and fragment.count('return;')==2
      and fragment.count('PrepareActionAt453D60(0x1D)')==1
      and 'POS48+POS54<=g_ThresholdAt0065782C' in fragment,
      'source 131 original stage/ground behavior changed')
 return source.replace(marker,'#include "FighterScriptedGrounded131F845.inc"',1)
def compile_parent(src):
 cpp=O/'Boss005214B0-F845-whole.cpp';obj=O/'Boss005214B0-F845-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=E,capture_output=True,text=True,timeout=280)
 (O/'compiler.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'current whole fighter source failed '+(cp.stdout+cp.stderr)[-850:])
 return obj
def main():
 rd=ld('f845rd','compare-coff-function.py')
 ac=ld('f845ac','report-fighter-action-handlers.py')
 f834=ld('f845f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f845f820','verify-scripted-fighter-landing-trio-f820.py')
 zero=ld('f845zero','verify-fighter-actionzero-natural-source.py')
 switch=ld('f845switch','verify-fighter-natural-switch-probes.py')
 d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
 boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'original fighter target changed')
 report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
 obj=compile_parent(new_source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 ins=[]
 for x in d.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 ret=ins[-1].address+ins[-1].size
 need((ret,len(ins),len(refs),len(code)-ret)==(22476,6135,882,901) and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'new whole fighter source x86, COFF or original ABI changed')
 dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,switch,ins,code,refs,ret)
 need(dense>0 and sparse>0 and maps>0,'five original switch tables not checked')
 sentinel=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
    and x.op_str.endswith(', 0x134')
    and any('g_FighterProbeMarker' in r['symbol']
             and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(sentinel)==1 and sentinel[0]>=58*2+238,'next true original 133 source marker lost')
 k=sentinel[0];seg=ins[k-58:k]
 native=f834.physical_case(rd,pe,d,code,refs,seg,by,0x131,202,5,[84,85,198,199],0x133,f820)
 need(native['native_complete_x86']==58
      and native['original_native_enclosing_parent_JMP_exit_ordinals']==[23,57]
      and seg[54].op_str=='0x1d'
      and seg[23].op_str==seg[57].op_str==hex(ret-4),
      'real selected actor 131 native grounded CFG/animation different')
 previous130=f834.physical_case(rd,pe,d,code,refs,ins[k-116:k-58],by,0x130,202,5,[84,85,198,199],0x131,f820)
 prev=ins[k-116-238:k-116];cur=0;fall=[]
 for a,nb,nx,nf,bad,nxt in FALL:
  fall.append(f834.physical_case(rd,pe,d,code,refs,prev[cur:cur+nx],by,a,nb,nf,bad,nxt,f820));cur+=nx
 need(cur==len(prev),'previous original falling frames incomplete')
 earlier=ins[k-116-238-sum(v[2] for v in PRIOR):k-116-238]
 j=0;prior=[]
 for a,nb,nx,nf,bad,nxt in PRIOR:
  prior.append(f834.physical_case(rd,pe,d,code,refs,earlier[j:j+nx],by,a,nb,nf,bad,nxt,f820));j+=nx
 need(j==len(earlier),'original C8-D2 source truncated')
 t=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,t,0x52cb25,[r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 wrong=[i for i in range(46) if i not in mask and t[i]!=code[ret-46+i]]
 need(wrong==[10,12,16,19],'current common default true GPR-negative byte offsets moved')
 out={'original_whole_fighter':'0x005214B0','original_whole_callable_CODE_B':46755,
      'source_entire_current_callable_CODE_B':ret,
      'new_actual_original_131':native,'actual_original_animation':29,'true_original_native_prepare_stage':3,
      'prior_130_physically_rechecked':previous130,
      'prior_four_12C_to_12F_real_PE_cases':fall,
      'previous_eleven_C8_to_D2_real_PE_cases':prior,
      'native_original_46B_default_GPR_negative_offsets':wrong,
      'five_real_afterRET_packed_tables_verified':True,
      'native_original_separate_jump_DATA_B':901,
      'original_whole_giant_exact':False,'new_accepted_authored_whole_CODE_B':0,'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
 print('F845 real original 131 202B/58x86/5 PE fields, stage3 animation1D, in whole 22476B/6135x86 parent. Native fields and all non-epilogue bytes equal; prior 130, four 12C-12F, eleven C8-D2, 5 native 901B tables reverified. Whole fighter NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F845 genuine whole actor 131 FAILED:',e,file=sys.stderr);raise SystemExit(1)
