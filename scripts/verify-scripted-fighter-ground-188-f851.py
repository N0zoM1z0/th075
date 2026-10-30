#!/usr/bin/env python3
"""F851 selected original 0x188 214B/61 native x86/6 true PE fields.

Build only selected entire affected VC7.1 fighter from native F850,
adding actual 0x188 stage2 / action2 / animation1D with real 00659090
gravity. Recheck all previous source-backed original C8..187
native full cases, each actual PE fields, exact original nonfield
mismatches, the 5 packed 901B afterRET tables and 46B shared getter.
Native x86 mnemonics and widths exact, but 38 true GPR operand bytes
and two encompassing original fighter return JMP bytes remain wrong.
Original complete fighter still NONEXACT, no split-case/whole CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f851-scripted-188'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
WRONG188=[1,5,8,12,16,19,23,27,33,45,49,57,60,67,70,77,81,84,88,91,100,103,106,109,125,128,135,138,154,156,160,163,177,181,184,189,193,196,210,211]
def need(v,msg):
 if not v:raise ValueError(msg)
def ld(t,f):
 s=importlib.util.spec_from_file_location(t,R/'scripts'/f)
 need(s is not None and s.loader is not None,'native helper missing '+f)
 m=importlib.util.module_from_spec(s);sys.modules[t]=m;s.loader.exec_module(m);return m
def native_source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 p=subprocess.run([str(R/'scripts/repo-python'),
     str(R/'scripts/verify-scripted-fighter-ground-186187-f850.py')],
     cwd=R,capture_output=True,text=True,timeout=1500)
 (O/'f850-physical-prior.log').write_text(p.stdout+p.stderr)
 need(p.returncode==0,'F850 original 186/187 native case/PE evidence failed '+(p.stdout+p.stderr)[-820:])
 n=list(d.disasm(rd.pe_bytes_at(pe,by[0x188],by[0x189]-by[0x188]),by[0x188]))
 need(len(n)==61 and by[0x189]-by[0x188]==214
      and n[19].mnemonic=='mov' and n[19].op_str.endswith(', 0x41480000')
      and n[26].mnemonic=='fsub' and n[26].op_str=='dword ptr [0x659090]'
      and n[46].mnemonic=='push' and n[46].op_str=='2'
      and n[51].mnemonic=='cmp' and n[51].op_str.endswith(', 2')
      and n[57].mnemonic=='push' and n[57].op_str=='0x1d'
      and n[-1].op_str=='0x52cb4f',
      'real original actor188 native gravity, state2, stage2 animation1D changed')
 src=(R/'.analysis/f850-scripted-186187/Boss005214B0-F850-whole.cpp').read_text()
 marker='        case 0x188: g_FighterProbeMarker = 393; break;'
 frag=(R/'probes/FighterScriptedGround188F851.inc').read_text()
 need(src.count(marker)==1 and frag.count('case 0x188:')==1
      and frag.count('return;')==1 and 'SetNativeActionAt40FAC0(2)' in frag
      and 'S16(0x62)==2' in frag
      and 'PrepareActionAt453D60(0x1D)' in frag
      and 'g_AdditionalGravityAt00659090' in frag,
      'selected fighter 188 genuine game C++ source changed')
 return src.replace(marker,'#include "FighterScriptedGround188F851.inc"',1)
def compile_one(src):
 cpp=O/'Boss005214B0-F851-whole.cpp';obj=O/'Boss005214B0-F851-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=285)
 (O/'compiler.log').write_text(p.stdout+p.stderr)
 need(p.returncode==0,'F851 original fighter entire source VC7.1 build failed '+(p.stdout+p.stderr)[-700:])
 return obj
def main():
 rd=ld('f851rd','compare-coff-function.py')
 ac=ld('f851ac','report-fighter-action-handlers.py')
 f834=ld('f851f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f851f820','verify-scripted-fighter-landing-trio-f820.py')
 f847=ld('f851f847','verify-scripted-fighter-projectile-134135-f847.py')
 f849=ld('f851f849','verify-scripted-fighter-physics-136-f849.py')
 f850=ld('f851f850','verify-scripted-fighter-ground-186187-f850.py')
 zero=ld('f851zero','verify-fighter-actionzero-natural-source.py')
 sw=ld('f851sw','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'pinned original fighter whole/native table identity changed')
 report,mp=ac.report_boss(rd,pe,d,boss)
 by={x['action']:int(x['handler'],16) for x in mp}
 obj=compile_one(native_source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 need((ret,len(I),len(refs),len(code)-ret)==(24196,6654,924,901)
      and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'new whole parent CODE/COFF/x86/saved this frame changed')
 dfields,sfields,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
 need(dfields>0 and sfields>0 and maps>0,'all original five afterRET tables not checked')
 marker=[i for i,x in enumerate(I) if x.mnemonic=='mov'
    and x.op_str.endswith(', 0x18a')
    and any('g_FighterProbeMarker' in r['symbol']
            and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(marker)==1 and marker[0]>=61+135+95,'following original 189 case marker not unique')
 k=marker[0]
 section=I[k-61:k]
 actual=f834.physical_case(rd,pe,d,code,refs,section,by,0x188,214,6,WRONG188,0x189,f820)
 need(actual['native_complete_x86']==61
      and actual['original_native_enclosing_parent_JMP_exit_ordinals']==[60]
      and section[60].op_str==hex(ret-4),
      'real 188 original whole direct enclosing parent JMP wrong')
 # Previous F850 186/187 retain full native instruction and
 # genuine GPR mismatch byte sets rather than fake exact status.
 earlier=I[k-61-135:k-61];pos=0;prior=[]
 for a in (0x186,0x187):
  nb,nx,nf,bad,nxt,anim,gravity=f850.ORIGINALS[a]
  seg=earlier[pos:pos+nx];pos+=nx
  prior.append(f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,bad,nxt,f820))
 need(pos==135,'native 186/187 prefix truncated')
 old136=I[k-61-135-95:k-61-135]
 prev136=f834.physical_case(rd,pe,d,code,refs,old136,by,0x136,321,10,f849.ORIGINAL_BAD,0x186,f820)
 originals=f847.STATES+[
   (0x134,278,82,7,[274,275],0x135),
   (0x135,278,82,7,[274,275],0x136)]
 old=I[k-61-135-95-sum(v[2] for v in originals):k-61-135-95]
 off=0;previous=[]
 for a,nb,nx,nf,wrong,nxt in originals:
  seg=old[off:off+nx];off+=nx
  previous.append(f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,wrong,nxt,f820))
 need(off==len(old),'20 original preceding fighter case sources incomplete')
 native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,native_tail,0x52cb25,
          [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 diff=[i for i in range(46) if i not in mask and native_tail[i]!=code[ret-46+i]]
 need(diff==[10,12,16,19],'actual 188 whole-fighter source native getter GPR phase changed')
 out={'native_original_whole_function':'0x005214B0',
      'original_entire_callable_CODE_B':46755,
      'generated_entire_current_source_CODE_B':ret,
      'original_188_full_native_case':actual,
      'original_188_total_nonrelocation_wrong_B':40,
      'original_188_nonparentJMP_GPR_wrong_B':38,
      'original_real_188_animated_stage':2,
      'original_188_animation':29,
      'prior_186_187_genuine_nonfield_mismatches_retained':prior,
      'prior_136_real_register_mismatch_retained':prev136,
      'earlier_20_native_C8_to_135_original_PE_cases_rechecked':previous,
      'original_native_46B_default_wrong_GPR_offsets':diff,
      'five_real_901B_afterRET_tables_rechecked':True,
      'original_separate_afterRET_DATA_B':901,
      'whole_original_function_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
 print('F851 native original 188 214B/61 x86/6 genuine PE fields in 24196B/6654x86 one whole fighter; 38 real original GPR operand bytes and 2 whole-giant return JMP bytes differ. Prior 136/186/187 honest register errors +20 prior original physical cases, five 901B packed tables, native default four GPR negatives rechecked. Whole original NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F851 original selected fighter 188 FAILED:',e,file=sys.stderr);raise SystemExit(1)
