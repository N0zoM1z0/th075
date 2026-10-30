#!/usr/bin/env python3
"""F849: original actor 0x136 whole native 321B/95-x86/10-PE-field source.

Rebuild F847 native original 134/135 source and previous 18 cases,
then integrate actual original stage>2 and x87 extra ground correction,
stage5 sprite0x33A, natural void-fighter exit. Compile ONE entire
normal VC7.1 whole source. The entire 321B native instruction
mnemonic/width sequence and ten genuine original PE fields match,
but 15 authentic stage5 register operand bytes and two original
enclosing fighter final JMP operand bytes remain wrong. Ten real
source AST alternatives failed to fix the GPR phase.
Recheck all earlier original game case PE fields, five 901B
packed afterRET tables and current 46B default GPR phase.
Original whole 46755B remains NONEXACT, no whole CODE adoption.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f849-scripted-ground-136'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
ORIGINAL_BAD=[248,252,255,260,264,267,273,276,278,280,283,285,287,290,292,317,318]
TYPED_FIELDS={
 13:(0x00453E20,'ResetAt453E20'),
 24:(0x00658058,'g_JumpGroundCorrectionAt00658058'),
 29:(0x0065782C,'g_ThresholdAt0065782C'),
 43:(0x0065782C,'g_ThresholdAt0065782C'),
 49:(0x0065747C,'g_AnimationDeltaAt0065747C'),
 54:(0x0065782C,'g_ThresholdAt0065782C'),
 61:(0x0040FA30,'GetNativeActionAt40FA30'),
 69:(0x0040FAC0,'SetNativeActionAt40FAC0'),
 90:(0x00453A70,'SpawnDirectedAt453A70'),
 93:(0x00453D60,'PrepareActionAt453D60'),
}
def need(v,msg):
 if not v:raise ValueError(msg)
def ld(t,name):
 sp=importlib.util.spec_from_file_location(t,R/'scripts'/name)
 need(sp and sp.loader,'missing original game helper '+name)
 m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m)
 return m
def create_source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 cp=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-projectile-134135-f847.py')],
   cwd=R,capture_output=True,text=True,timeout=1400)
 (O/'f847-prior-original-proof.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'previous full fighter source/PE mismatched '+(cp.stdout+cp.stderr)[-800:])
 raw=rd.pe_bytes_at(pe,by[0x136],by[0x186]-by[0x136])
 native=list(d.disasm(raw,by[0x136]))
 need(len(raw)==321 and len(native)==95
   and native[39].mnemonic=='cmp' and native[39].op_str.endswith(', 2')
   and native[49].mnemonic=='fsub' and native[49].op_str=='dword ptr [0x65747c]'
   and native[72].op_str.endswith(', 5')
   and native[88].mnemonic=='push' and native[88].op_str=='0x33a'
   and native[93].mnemonic=='call' and native[93].op_str=='0x453d60'
   and native[-1].op_str=='0x52cb4f',
   'original full actor stage136 extra-ground/sprite physics changed')
 source=(R/'.analysis/f847-scripted-spawns134135/Boss005214B0-F847-whole.cpp').read_text()
 marker='        case 0x136: g_FighterProbeMarker = 311; break;'
 frag=(R/'probes/FighterScriptedGroundPhysics136F849.inc').read_text()
 need(source.count(marker)==1 and frag.count('case 0x136:')==1
      and frag.count('return;')==1 and 'S16(0x62)>2 && POS>g_ThresholdAt0065782C' in frag
      and frag.count('SpawnDirectedAt453A70(0x33A')==1
      and frag.count('PrepareActionAt453D60(0x1D)')==1,
      'original actor 136 genuine source conditions/calls missing')
 return source.replace(marker,'#include "FighterScriptedGroundPhysics136F849.inc"',1)
def compile_one(src):
 cpp=O/'Boss005214B0-F849-whole.cpp';obj=O/'Boss005214B0-F849-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
     cwd=R,env=E,capture_output=True,text=True,timeout=300)
 (O/'compiler.log').write_text(p.stdout+p.stderr)
 need(p.returncode==0,'full native original 136 C++ compile failed '+(p.stdout+p.stderr)[-720:])
 return obj
def main():
 rd=ld('f849rd','compare-coff-function.py')
 ac=ld('f849ac','report-fighter-action-handlers.py')
 f834=ld('f849f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f849f820','verify-scripted-fighter-landing-trio-f820.py')
 f847=ld('f849f847','verify-scripted-fighter-projectile-134135-f847.py')
 zero=ld('f849zero','verify-fighter-actionzero-natural-source.py')
 sw=ld('f849sw','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if b['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'original whole fighter identity/dense DATA changed')
 report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
 obj=compile_one(create_source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 need((ret,len(I),len(refs),len(code)-ret)==(23563,6464,908,901)
      and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'whole actor current original C++ ABI/COFF/x86 geometry changed')
 dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
 need(dense>0 and sparse>0 and maps>0,'five real native packed 901B jump tables missing')
 marker=[j for j,x in enumerate(I) if x.mnemonic=='mov'
    and x.op_str.endswith(', 0x187')
    and any('g_FighterProbeMarker' in r['symbol']
          and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(marker)==1 and marker[0]>=95,'next original 186 placeholder missing')
 k=marker[0]
 gen=I[k-95:k];lo,hi=gen[0].address,gen[-1].address+gen[-1].size
 case=f834.physical_case(rd,pe,d,code,refs,gen,by,0x136,321,10,ORIGINAL_BAD,0x186,f820)
 need(case['native_complete_x86']==95
      and case['original_native_enclosing_parent_JMP_exit_ordinals']==[94]
      and gen[94].op_str==hex(ret-4),
      'original full 136 x86/parent-exit geometry unexpectedly changed')
 real=list(d.disasm(rd.pe_bytes_at(pe,by[0x136],321),by[0x136]))
 for ordinal,(target,symbol) in TYPED_FIELDS.items():
  a,b=real[ordinal],gen[ordinal]
  hits=[r for r in refs if b.address<=r['offset']<b.address+b.size]
  need(len(hits)==1 and hits[0]['addend']==0
       and hits[0]['local_symbol_offset'] is None and symbol in hits[0]['symbol']
       and hits[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
       and hits[0]['offset']-lo==a.address-by[0x136]+a.size-4
       and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
       'native source136 true PE field destination/ordinal changed '+str(ordinal))
 # Source GPR phase after the action0 branch differs on 15 actual
 # operand bytes; verify those negatives remain unmasked.
 badregister=[j for j in ORIGINAL_BAD if j not in (317,318)]
 need(len(badregister)==15 and all(j>=248 for j in badregister)
      and gen[70].op_str=='eax, dword ptr [ebp - 0x10]'
      and real[70].op_str=='ecx, dword ptr [ebp - 0x10]',
      'original/source 136 late-frame register phase mismatch not independently checked')
 previous=f847.STATES+[
      (0x134,278,82,7,[274,275],0x135),
      (0x135,278,82,7,[274,275],0x136)]
 earlier=I[k-95-sum(s[2] for s in previous):k-95]
 cursor=0;rows=[]
 for action,nb,nx,nf,wrong,nxt in previous:
  seg=earlier[cursor:cursor+nx];cursor+=nx
  rows.append(f834.physical_case(rd,pe,d,code,refs,seg,by,action,nb,nf,wrong,nxt,f820))
 need(cursor==len(earlier),'original 20 earlier whole-case source boundaries changed')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,tail,0x52cb25,[r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
 need(wrong_tail==[10,12,16,19],
      'actual GPR phase of 46B shared getter changed; cannot falsely claim 34/34')
 out={'original_actor_whole':'0x005214B0','original_callable_CODE_B':46755,
      'generated_source_current_whole_B':ret,
      'true_original_136_complete_native':case,
      'original_136_real_field_ordinals':list(TYPED_FIELDS),
      'original_136_GPR_wrong_offsets':badregister,
      'real_136_final_giant_JMP_wrong_offsets':[317,318],
      'prior_20_original_cases_full_physically_verified':rows,
      'original_46B_default_real_GPR_byte_differences':wrong_tail,
      'five_original_packed_afterRET_tables_rechecked':True,
      'original_afterRET_DATA_B':901,
      'whole_original_46755B_exact':False,
      'new_accepted_whole_authored_CODE_B':0,
      'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
 print('F849 original 136 complete 321B/95x86/10 true PE fields integrated in whole 23563B/6464-x86 fighter; 15 honest late-stage GPR operand bytes plus two real entire-parent JMP bytes remain wrong, NONEXACT. Earlier 20 PE-backed native cases and five 901B packed DATA tables verified, 46B default 4 honest GPR operand negatives.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F849 actual original giant 136 FAILED:',e,file=sys.stderr);raise SystemExit(1)
