#!/usr/bin/env python3
"""F855: original 18B 353B/99x86, 7 actual native PE fields, in whole giant.

Regenerate F853 native parent, compile only current affected VC7.1
fighter with original stage7 short prefix++ and auxiliary action6,
stage6 float X facing*128 FILD then add member44; Y left lvalue
loaded before original global00658400 FADD. All native instructions
and PE fields match, but 71 true GPR operand bytes and 2 original
giant epilogue long-JMP bytes remain wrong. Prior 26 native source
cases and 5 true packed 901B switch DATA tables rechecked.
Whole native 46755B NONEXACT, no accepted COD E/cold replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f855-scripted-18b'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
WRONG=[1,5,8,12,16,19,23,27,35,38,45,48,55,59,67,71,74,79,82,91,94,97,100,116,119,126,129,145,147,151,154,168,172,175,178,180,184,187,189,191,195,201,204,206,210,216,217,218,220,224,240,244,252,255,262,266,269,274,278,281,287,290,292,294,297,310,314,317,320,326,329,349,350]
FIELDS={
 22:(0x658058,'g_JumpGroundCorrectionAt00658058'),
 27:(0x65782c,'g_ThresholdAt0065782C'),
 36:(0x40fa30,'GetNativeActionAt40FA30'),
 44:(0x40fac0,'SetNativeActionAt40FAC0'),
 64:(0x40fb40,'SetAuxActionAt40FB40'),
 83:(0x658400,'g_F855ShotYAt00658400'),
 97:(0x453a70,'SpawnFloatXYAt453A70'),
}
def need(v,msg):
 if not v:raise ValueError(msg)
def ld(t,f):
 s=importlib.util.spec_from_file_location(t,R/'scripts'/f)
 need(s is not None and s.loader is not None,'native helper missing '+f)
 m=importlib.util.module_from_spec(s);sys.modules[t]=m;s.loader.exec_module(m);return m
def native_source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 cp=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-floatshot-18a-f853.py')],
  cwd=R,capture_output=True,text=True,timeout=1350)
 (O/'f853-prior-original.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'prior complete native original fighter 18A proof failed '+(cp.stdout+cp.stderr)[-650:])
 orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x18b],by[0x190]-by[0x18b]),by[0x18b]))
 need(len(orig)==99 and by[0x190]-by[0x18b]==353
      and orig[13].mnemonic=='mov' and orig[13].op_str.endswith(', 0x41200000')
      and orig[19].mnemonic=='jle'
      and orig[58].op_str.startswith('ax, word ptr [')
      and orig[59].mnemonic=='add' and orig[59].op_str=='ax, 1'
      and orig[64].op_str=='0x40fb40'
      and orig[83].mnemonic=='fadd' and orig[83].op_str=='dword ptr [0x658400]'
      and orig[88].mnemonic=='shl' and orig[88].op_str=='eax, 7'
      and orig[95].op_str=='0x328'
      and orig[97].op_str=='0x453a70'
      and orig[-1].op_str=='0x52cb4f',
      'selected original physical 18B 16-bit short, float source/stage changed')
 src=(R/'.analysis/f853-scripted-float-shot18a/Boss005214B0-F853-whole.cpp').read_text()
 marker='        case 0x18B: g_FighterProbeMarker = 396; break;'
 inc=(R/'probes/FighterScriptedVolley18BF855.inc').read_text()
 need(src.count(marker)==1 and inc.count('case 0x18B:')==1
      and inc.count('return;')==1
      and inc.count('++S16(0xF00);')==1
      and '(*(&POS48))+g_F855ShotYAt00658400' in inc
      and 'SpawnFloatXYAt453A70(0x328' in inc,
      'native original source C++ 18B semantic AST changed')
 return 'extern float g_F855ShotYAt00658400;\n'+src.replace(marker,'#include "FighterScriptedVolley18BF855.inc"',1)
def compile_one(src):
 cpp=O/'Boss005214B0-F855-whole.cpp';obj=O/'Boss005214B0-F855-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=285)
 (O/'compiler.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'current whole original fighter18B VC7.1 failed '+(cp.stdout+cp.stderr)[-700:])
 return obj

def main():
 rd=ld('f855reader','compare-coff-function.py')
 ac=ld('f855actions','report-fighter-action-handlers.py')
 f834=ld('f855f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f855f820','verify-scripted-fighter-landing-trio-f820.py')
 f847=ld('f855f847','verify-scripted-fighter-projectile-134135-f847.py')
 f849=ld('f855f849','verify-scripted-fighter-physics-136-f849.py')
 f850=ld('f855f850','verify-scripted-fighter-ground-186187-f850.py')
 f851=ld('f855f851','verify-scripted-fighter-ground-188-f851.py')
 f852=ld('f855f852','verify-scripted-fighter-bounce-189-f852.py')
 f853=ld('f855f853','verify-scripted-fighter-floatshot-18a-f853.py')
 zero=ld('f855zero','verify-fighter-actionzero-natural-source.py')
 sw=ld('f855sw','verify-fighter-natural-switch-probes.py')
 d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
 boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if x['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'pinned original fighter or switch DATA identity changed')
 report,mp=ac.report_boss(rd,pe,d,boss)
 by={x['action']:int(x['handler'],16) for x in mp}
 obj=compile_one(native_source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 need((ret,len(I),len(refs),len(code)-ret)==(25135,6925,945,901)
      and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'selected entire game fighter source CODE/ABI/native DATA changed')
 dens,spars,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
 need(dens>0 and spars>0 and maps>0,'all five true packed native afterRET jump tables absent')
 mark=[j for j,x in enumerate(I) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x191')
       and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(mark)==1 and mark[0]>=99,'original following 190 source marker absent')
 k=mark[0]
 sec=I[k-99:k]
 case=f834.physical_case(rd,pe,d,code,refs,sec,by,0x18b,353,7,WRONG,0x190,f820)
 need(case['native_complete_x86']==99
      and case['original_native_enclosing_parent_JMP_exit_ordinals']==[98]
      and sec[98].op_str==hex(ret-4)
      and sec[58].mnemonic=='mov' and sec[58].op_str.startswith('dx, word ptr [')
      and sec[59].op_str=='dx, 1'
      and sec[83].mnemonic=='fadd' and sec[83].size==6
      and sec[88].op_str=='edx, 7',
      'native selected 18B short++, float Y and signed facing shl changed')
 orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x18b],353),by[0x18b]))
 for ordinal,(target,sym) in FIELDS.items():
  a,b=orig[ordinal],sec[ordinal]
  fields=[r for r in refs if b.address<=r['offset']<b.address+b.size]
  need(len(fields)==1 and fields[0]['local_symbol_offset'] is None
       and fields[0]['addend']==0
       and fields[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
       and sym in fields[0]['symbol']
       and fields[0]['offset']-sec[0].address==a.address-by[0x18b]+a.size-4
       and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
       'actual original 18B physical PE field wrong '+str(ordinal))
 # Current source remains 71 native GPR operand byte negatives,
 # plus original complete-fighter external JMP two-byte difference.
 need(len(WRONG)==73 and WRONG[-2:]==[349,350],
      'real 18B negative bytes must not be silently hidden')
 prior=[
  (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
  (0x186,250,74,7,f850.BAD186,0x187),
  (0x187,214,61,6,f850.BAD187,0x188),
  (0x188,214,61,6,f851.WRONG188,0x189),
  (0x189,381,107,11,f852.BAD189,0x18a),
  (0x18a,250,71,6,f853.BAD,0x18b)]
 prev=I[k-99-sum(s[2] for s in prior):k-99]
 cur=0;old=[]
 for a,nb,nx,nf,bad,nxt in prior:
  section=prev[cur:cur+nx];cur+=nx
  old.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
 need(cur==len(prev),'previous 136 through 18A native original states truncated')
 earlier=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                       (0x135,278,82,7,[274,275],0x136)]
 left=k-99-sum(s[2] for s in prior)
 whole=I[left-sum(s[2] for s in earlier):left]
 cur=0;ancient=[]
 for a,nb,nx,nf,bad,nxt in earlier:
  section=whole[cur:cur+nx];cur+=nx
  ancient.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
 need(cur==len(whole),'twenty earlier original case source boundaries changed')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,tail,0x52cb25,
       [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 differences=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
 need(differences==[10,12,16,19],'original 46B getter source current GPR phase changed')
 summary={'original_complete_fighter':'0x005214B0',
      'original_native_entire_CODE_B':46755,
      'current_generated_whole_source_CODE_B':ret,
      'actual_original_18B_native_complete_case':case,
      'original_18B_typed_PE_field_ordinals':list(FIELDS),
      'actual_18B_source_GPR_wrong_B':71,
      'original_final_whole_giant_JMP_wrong_offsets':[349,350],
      'previous_six_136_through_18A_original_PE_cases_reverified':old,
      'twenty_earlier_original_PE_case_sources_rechecked':ancient,
      'real_default_46B_nonrelocation_wrong_positions':differences,
      'all_five_901B_afterRET_packed_tables_reverified':True,
      'original_separate_switch_DATA_B':901,
      'whole_original_46755B_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
 print('F855 original 18B 353B/99 native x86/7 physical PE fields inside entire 25135B/6925-x86 VC7.1 fighter. All opcode/widths/fields correct, 71 real GPR operand bytes plus 2 whole-giant final JMP bytes nonnative. Prior 26 case original PE and five packed 901B switch tables checked. Native fighter NONEXACT, no split-case credit.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F855 original selected fighter 18B FAILED:',e,file=sys.stderr);raise SystemExit(1)
