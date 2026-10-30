#!/usr/bin/env python3
"""F850: actual native 186/187 grounded transitions inside whole 005214B0.

Regenerate/verify selected previous F849 entire original fighter first,
then add native ground cases 186 (250B/74-x86/7 typed original PE
fields) and 187 (214B/61-x86/6 fields). Full source uses genuine
stage0 POS12.5, stage>0 decrement, native different float globals
658058/659090 and stage3 Prepare/Spawn original game callbacks.
One entire pinned VC7.1 father emits 23997B/6595 x86 with 901B
original switch DATA. Original case opcode-width/PE targets match,
but 47 and 38 genuine GPR bytes, plus 2 external final-JMP bytes,
remain nonexact per case. Recheck original preceding 136 register
negative, twenty earlier whole case physical PE fields and actual
native shared getter 34/34 original nonrelocation bytes.
No mass cold replay or original whole-game exact credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f850-scripted-186187'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BAD186=[1,5,8,12,16,19,23,27,33,45,49,57,60,67,70,77,81,84,88,91,100,103,106,109,125,128,135,138,154,156,160,163,177,181,184,189,193,196,212,215,217,219,222,224,226,229,231,246,247]
BAD187=[1,5,8,12,16,19,23,27,33,45,49,57,60,67,70,77,81,84,88,91,100,103,106,109,125,128,135,138,154,156,160,163,177,181,184,189,193,196,210,211]
ORIGINALS={
 0x186:(250,74,7,BAD186,0x187,0x1d,0x00658058),
 0x187:(214,61,6,BAD187,0x188,0x1c,0x00659090),
}
FIELDS={
 13:(0x00453E20,'ResetAt453E20'),
 26:(None,None),
 31:(0x0065782C,'g_ThresholdAt0065782C'),
 40:(0x0040FA30,'GetNativeActionAt40FA30'),
 48:(0x0040FAC0,'SetNativeActionAt40FAC0'),
 59:(0x00453D60,'PrepareActionAt453D60'),
}
def need(v,msg):
 if not v:raise ValueError(msg)
def ld(t,f):
 sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
 need(sp is not None and sp.loader is not None,'native reader missing '+f)
 mod=importlib.util.module_from_spec(sp);sys.modules[t]=mod;sp.loader.exec_module(mod)
 return mod
def source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 cp=subprocess.run([str(R/'scripts/repo-python'),
         str(R/'scripts/verify-scripted-fighter-physics-136-f849.py')],
         cwd=R,capture_output=True,text=True,timeout=1550)
 (O/'f849-prior-selected-original.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'F849 whole original fighter PE verification failed '+(cp.stdout+cp.stderr)[-800:])
 src=(R/'.analysis/f849-scripted-ground-136/Boss005214B0-F849-whole.cpp').read_text()
 src='extern float g_AdditionalGravityAt00659090;\n'+src
 for action,(nb,nx,nf,wrong,nxt,anim,gravity) in ORIGINALS.items():
  original=list(d.disasm(rd.pe_bytes_at(pe,by[action],by[nxt]-by[action]),by[action]))
  need(len(original)==nx and by[nxt]-by[action]==nb
       and original[19].mnemonic=='mov' and original[19].op_str.endswith(', 0x41480000')
       and original[23].mnemonic=='jle'
       and original[26].mnemonic=='fsub' and original[26].op_str==f'dword ptr [0x{gravity:x}]'
       and original[57].mnemonic=='push' and original[57].op_str==f'0x{anim:x}'
       and original[-1].op_str=='0x52cb4f',
       'physical original actor 186/187 stage3 and fall globals changed')
  if action==0x186:
   need(original[70].op_str=='0x341' and original[72].mnemonic=='call'
        and original[72].op_str=='0x453a70',
        'genuine native original 186 spawn kind 341 changed')
  marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
  frag=(R/f'probes/FighterScriptedGround{action:X}F850.inc').read_text()
  need(src.count(marker)==1 and frag.count(f'case 0x{action:X}:')==1
       and frag.count('return;')==1 and 'POS=12.5f;' in frag
       and f'PrepareActionAt453D60(0x{anim:X})' in frag
       and 'S16(0x62)>0' in frag,
       'real actor original normal 186/187 source incomplete')
  src=src.replace(marker,f'#include "FighterScriptedGround{action:X}F850.inc"',1)
 return src
def compile_one(src):
 cpp=O/'Boss005214B0-F850-whole.cpp';obj=O/'Boss005214B0-F850-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
     cwd=R,env=E,capture_output=True,text=True,timeout=305)
 (O/'compiler.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'full original 186/187 fighter compilation failed '+(cp.stdout+cp.stderr)[-780:])
 return obj
def main():
 rd=ld('f850rd','compare-coff-function.py')
 ac=ld('f850ac','report-fighter-action-handlers.py')
 f834=ld('f850f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f850f820','verify-scripted-fighter-landing-trio-f820.py')
 f847=ld('f850f847','verify-scripted-fighter-projectile-134135-f847.py')
 f849=ld('f850f849','verify-scripted-fighter-physics-136-f849.py')
 zero=ld('f850zero','verify-fighter-actionzero-natural-source.py')
 sw=ld('f850sw','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
           if b['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'target original native whole fighter identity changed')
 report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
 obj=compile_one(source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 ins=[]
 for x in d.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 ret=ins[-1].address+ins[-1].size
 need((ret,len(ins),len(refs),len(code)-ret)==(23997,6595,919,901)
      and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'current entire fighter ABI/COFF shape or 901B DATA changed')
 dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
 need(dense>0 and sparse>0 and maps>0,'five real afterRET native tables not physical')
 mark=[i for i,x in enumerate(ins) if x.mnemonic=='mov' and x.op_str.endswith(', 0x189')
       and any('g_FighterProbeMarker' in r['symbol']
              and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(mark)==1 and mark[0]>=135+95,'real next actor188 source sentinel not unique')
 k=mark[0]
 cases=[]
 for action,(nb,nx,nf,wrong,nxt,anim,gravity),lo in (
      (0x186,ORIGINALS[0x186],k-135),(0x187,ORIGINALS[0x187],k-61)):
  section=ins[lo:lo+nx]
  case=f834.physical_case(rd,pe,d,code,refs,section,by,action,nb,nf,wrong,nxt,f820)
  need(case['native_complete_x86']==nx
       and case['original_native_enclosing_parent_JMP_exit_ordinals']==[nx-1]
       and section[-1].op_str==hex(ret-4),
       'actual native actor186/187 full original body/exit source altered')
  original=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
  fields=dict(FIELDS)
  fields[26]=(gravity,('g_JumpGroundCorrectionAt00658058' if action==0x186 else 'g_AdditionalGravityAt00659090'))
  if action==0x186:fields[72]=(0x00453A70,'SpawnDirectedAt453A70')
  for ordinal,(target,symbol) in fields.items():
   o,s=original[ordinal],section[ordinal]
   physical=[r for r in refs if s.address<=r['offset']<s.address+s.size]
   need(len(physical)==1 and symbol in physical[0]['symbol']
        and physical[0]['addend']==0
        and physical[0]['type']==('REL32' if o.mnemonic=='call' else 'DIR32')
        and physical[0]['local_symbol_offset'] is None
        and physical[0]['offset']-section[0].address==o.address-by[action]+o.size-4
        and o.op_str==(f'0x{target:x}' if o.mnemonic=='call'
                         else f'dword ptr [0x{target:x}]'),
        'actual original 186/187 native PE target/COFF ordinal incorrect '+hex(action))
  need(len(wrong)-2==(47 if action==0x186 else 38)
       and wrong[-2:]==([246,247] if action==0x186 else [210,211]),
       'native original GPR mismatch and outer JMP negative should remain')
  cases.append(case)
 # Earlier 136 GPR mismatches are physically rechecked, NOT declared exact.
 start=k-135-95
 source136=ins[start:start+95]
 previous136=f834.physical_case(rd,pe,d,code,refs,source136,by,0x136,321,10,
                                f849.ORIGINAL_BAD,0x186,f820)
 previous=f847.STATES+[
      (0x134,278,82,7,[274,275],0x135),
      (0x135,278,82,7,[274,275],0x136)]
 old=ins[start-sum(s[2] for s in previous):start]
 cur=0;rows=[]
 for action,nb,nx,nf,bad,nxt in previous:
  part=old[cur:cur+nx];cur+=nx
  rows.append(f834.physical_case(rd,pe,d,code,refs,part,by,action,nb,nf,bad,nxt,f820))
 need(cur==len(old),'20 preceding actual whole source cases truncated')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,tail,0x52cb25,
           [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 need(len(mask)==12 and all(tail[i]==code[ret-46+i] for i in range(46) if i not in mask),
      'original 46B shared default should have 34/34 genuine native nonfield bytes')
 out={'original_whole_native_fighter':'0x005214B0',
      'native_entire_original_callable_CODE_B':46755,
      'generated_source_entire_callable_CODE_B':ret,
      'new_original_186_187_complete_cases':cases,
      'original_186_187_native_CODE_B_total':464,
      'original_186_187_x86_total':135,'original_186_187_physical_PE_fields':13,
      'true_nonrelocation_GPR_wrong_B_186_187':[47,38],
      'prior_native_136_register_mismatch_retained':previous136,
      'prior_20_original_PE_source_cases_reverified':rows,
      'native_46B_shared_default_nonrelocation_equal':'34/34',
      'native_default_three_PE_REL32_calls':3,
      'original_five_afterRET_901B_jump_tables_verified':True,
      'native_afterRET_separately_owned_DATA_B':901,
      'native_original_whole_giant_exact':False,
      'newly_accepted_authored_whole_CODE_B':0,'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
 print('F850 original 186 250B/74x86/7 PE fields + 187 214B/61x86/6 fields in selected whole 23997B/6595-x86 fighter. Genuine 47/38 source GPR bytes plus 2 actual giant JMP bytes remain wrong per case. Original 136 late GPR wrong retained; earlier 20 native cases, default 46B 34/34 and all five 901B tables PE-verified. Full original 46755B NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F850 selected whole original 186/187 FAILED:',e,file=sys.stderr);raise SystemExit(1)
