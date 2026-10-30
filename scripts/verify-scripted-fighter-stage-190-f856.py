#!/usr/bin/env python3
"""F856: original 190 217B/64x86/6 PE calls in the full selected fighter.

Regenerate F855 original target-backed native whole parent. Add
genuine stage3 sprite320, animationFA then prepare0, stage4 I32+7C=1,
and compile only the one affected normal VC7.1 giant C++ source.
Entire original 217B x86 grammar and all six physically original
PE call targets match, but 39 honest GPR operand bytes and two
enclosing-fighter final JMP operand bytes remain. Recheck all 27
earlier native source cases, original 46B getter now 34/34 equal
nonrelocation bytes and five packed 901B afterRET jump DATA tables.
Full original fighter still NONEXACT, no accepted standalone case CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f856-scripted-stage190'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,23,27,35,38,62,64,68,71,85,89,92,97,101,104,108,111,123,126,128,130,133,135,137,140,142,180,184,187,192,196,199,203,206,213,214]
FIELDS={
 13:(0x453e20,'ResetAt453E20'),
 15:(0x40fa30,'GetNativeActionAt40FA30'),
 23:(0x40fac0,'SetNativeActionAt40FAC0'),
 46:(0x453a70,'SpawnDirectedAt453A70'),
 49:(0x46d000,'StartAnimationAt46D000'),
 52:(0x453d40,'PrepareActionAt453D40'),
}
def need(v,msg):
 if not v:raise ValueError(msg)
def ld(t,f):
 sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
 need(sp is not None and sp.loader is not None,'native original verifier missing '+f)
 m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m);return m
def source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 cp=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-volley-18b-f855.py')],
     cwd=R,capture_output=True,text=True,timeout=1400)
 (O/'f855-prior-native.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'original previous 18B/whole native proof failed '+(cp.stdout+cp.stderr)[-780:])
 n=list(d.disasm(rd.pe_bytes_at(pe,by[0x190],by[0x191]-by[0x190]),by[0x190]))
 need(len(n)==64 and by[0x191]-by[0x190]==217
      and n[33].mnemonic=='mov' and n[33].op_str.endswith(', 0x3f800000')
      and n[44].op_str=='0x320'
      and n[46].mnemonic=='call' and n[46].op_str=='0x453a70'
      and n[47].op_str=='0xfa' and n[49].op_str=='0x46d000'
      and n[50].op_str=='0' and n[52].op_str=='0x453d40'
      and n[55].mnemonic=='cmp' and n[55].op_str.endswith(', 4')
      and n[62].op_str.endswith(', 1') and n[-1].op_str=='0x52cb4f',
      'selected original native 190 stage3/4 sprite/animation sequence changed')
 cpp=(R/'.analysis/f855-scripted-18b/Boss005214B0-F855-whole.cpp').read_text()
 old='        case 0x190: g_FighterProbeMarker = 401; break;'
 inc=(R/'probes/FighterScriptedStage190F856.inc').read_text()
 need(cpp.count(old)==1 and inc.count('case 0x190:')==1
      and inc.count('return;')==1
      and 'SpawnDirectedAt453A70(0x320' in inc
      and 'StartAnimationAt46D000(0xFA);' in inc
      and 'PrepareActionAt453D40(0);' in inc
      and 'I32(0x7C)=1;' in inc,
      'actual original 190 stage case C++ source altered')
 return cpp.replace(old,'#include "FighterScriptedStage190F856.inc"',1)
def compile_one(cpp):
 src=O/'Boss005214B0-F856-whole.cpp';obj=O/'Boss005214B0-F856-whole.obj'
 src.write_text(cpp)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 proc=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=E,capture_output=True,text=True,timeout=290)
 (O/'compiler.log').write_text(proc.stdout+proc.stderr)
 need(proc.returncode==0,'current selected 190 whole original fighter C++ failed '+(proc.stdout+proc.stderr)[-750:])
 return obj

def main():
 rd=ld('f856rd','compare-coff-function.py')
 ac=ld('f856ac','report-fighter-action-handlers.py')
 f834=ld('f856f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f856f820','verify-scripted-fighter-landing-trio-f820.py')
 f847=ld('f856f847','verify-scripted-fighter-projectile-134135-f847.py')
 f849=ld('f856f849','verify-scripted-fighter-physics-136-f849.py')
 f850=ld('f856f850','verify-scripted-fighter-ground-186187-f850.py')
 f851=ld('f856f851','verify-scripted-fighter-ground-188-f851.py')
 f852=ld('f856f852','verify-scripted-fighter-bounce-189-f852.py')
 f853=ld('f856f853','verify-scripted-fighter-floatshot-18a-f853.py')
 f855=ld('f856f855','verify-scripted-fighter-volley-18b-f855.py')
 zero=ld('f856zero','verify-fighter-actionzero-natural-source.py')
 sw=ld('f856sw','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
           if b['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'pinned original whole game function changed')
 report,mapped=ac.report_boss(rd,pe,d,boss)
 by={x['action']:int(x['handler'],16) for x in mapped}
 obj=compile_one(source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 need((ret,len(I),len(refs),len(code)-ret)==(25337,6987,950,901)
      and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'whole current fighter 190 source frame, x86 or COFF changed')
 ds,ss,ms=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
 need(ds>0 and ss>0 and ms>0,'five original packed afterRET tables not physically rechecked')
 mark=[j for j,x in enumerate(I) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x192')
       and any('g_FighterProbeMarker' in r['symbol']
               and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(mark)==1 and mark[0]>=64,'native following 191 source marker not unique')
 k=mark[0]
 sec=I[k-64:k]
 native=f834.physical_case(rd,pe,d,code,refs,sec,by,0x190,217,6,BAD,0x191,f820)
 need(native['native_complete_x86']==64
      and native['original_native_enclosing_parent_JMP_exit_ordinals']==[63]
      and sec[-1].op_str==hex(ret-4)
      and sec[44].op_str=='0x320'
      and sec[47].op_str=='0xfa'
      and sec[50].op_str=='0',
      'actual 190 native stage3 sprite/animation/callback or final JMP changed')
 original=list(d.disasm(rd.pe_bytes_at(pe,by[0x190],217),by[0x190]))
 for ordinal,(target,symbol) in FIELDS.items():
  a,b=original[ordinal],sec[ordinal]
  found=[r for r in refs if b.address<=r['offset']<b.address+b.size]
  need(len(found)==1 and found[0]['type']=='REL32'
       and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
       and symbol in found[0]['symbol']
       and found[0]['offset']-sec[0].address==a.address-by[0x190]+a.size-4
       and a.op_str==f'0x{target:x}',
       'native selected actor original 190 actual call field order/destination changed '+str(ordinal))
 need(len(BAD)==41 and BAD[-2:]==[213,214],
      'source must preserve 39 honest original GPR bytes plus two original external JMP bytes')
 late=[
  (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
  (0x186,250,74,7,f850.BAD186,0x187),
  (0x187,214,61,6,f850.BAD187,0x188),
  (0x188,214,61,6,f851.WRONG188,0x189),
  (0x189,381,107,11,f852.BAD189,0x18a),
  (0x18a,250,71,6,f853.BAD,0x18b),
  (0x18b,353,99,7,f855.WRONG,0x190)]
 old=I[k-64-sum(x[2] for x in late):k-64]
 cur=0;recent=[]
 for a,nb,nx,nf,bad,nxt in late:
  section=old[cur:cur+nx];cur+=nx
  recent.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
 need(cur==len(old),'previous seven selected original physical GPR cases missing')
 early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                     (0x135,278,82,7,[274,275],0x136)]
 boundary=k-64-sum(x[2] for x in late)
 before=I[boundary-sum(x[2] for x in early):boundary]
 cur=0;earlier=[]
 for a,nb,nx,nf,bad,nxt in early:
  sec0=before[cur:cur+nx];cur+=nx
  earlier.append(f834.physical_case(rd,pe,d,code,refs,sec0,by,a,nb,nf,bad,nxt,f820))
 need(cur==len(before),'previous 20 exact-geometry native cases truncated')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,tail,0x52cb25,
          [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 need(len(mask)==12 and all(tail[i]==code[ret-46+i] for i in range(46) if i not in mask),
      'real native default getter should have 34/34 nonrelocated bytes in new 190 parent')
 result={'original_whole_actor':'0x005214B0',
      'native_original_whole_game_CODE_B':46755,
      'new_source_whole_callable_CODE_B':ret,
      'new_native_original_190_entire_case':native,
      'original_190_real_PE_call_ordinals':list(FIELDS),
      'original_190_GPR_mismatching_B':39,
      'original_190_enclosing_giant_JMP_wrong_offsets':[213,214],
      'previous_seven_native_GPR_cases_rechecked':recent,
      'prior_twenty_original_native_case_sources_checked':earlier,
      'native_default_46B_nonrelocation_equal':'34/34',
      'native_default_original_PE_REL32_calls':3,
      'original_five_packed_afterRET_tables_verified':True,
      'native_separate_afterRET_DATA_B':901,
      'original_whole_46755B_exact':False,'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
 print('F856 original 190 native 217B/64-x86/6 physical PE calls in current whole 25337B/6987-x86 fighter. Full opcode/width and all call destinations match, but 39 genuine original GPR bytes plus two original giant epilogue JMP bytes nonexact. Prior 27 physical source cases, common getter native 34/34 nonrelocation and all five 901B switch tables verified; whole original giant NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F856 selected original whole fighter 190 FAILED:',e,file=sys.stderr);raise SystemExit(1)
