#!/usr/bin/env python3
"""F857 original 191 complete native 166B/53x86/5 true PE fields.

Rebuild F856 selected whole 190 parent; add real original stage5
sprite321, float X facing*100 FILD then FADD member44, float Y
member48 before global 659298, and native action0 after source
callback0. Compile only affected full original-shaped VC7.1 giant.
All 53 native opcode/width and five true PE fields match but
29 honest GPR operand bytes and two original encompassing giant
final-JMP bytes differ; 28 earlier full cases/5 packed 901B
tables and original 46B getter 34/34 rechecked.
Original 46755B giant remains nonexact, no split-case CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f857-scripted-191'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BAD=[1,5,8,12,16,19,23,26,33,37,40,45,49,52,58,61,63,65,68,81,85,88,91,97,100,139,141,145,148,162,163]
FIELDS={24:(0x659298,'g_F857ShotYAt00659298'),
        38:(0x453a70,'SpawnFloatXYAt453A70'),
        41:(0x453d40,'PrepareActionAt453D40'),
        43:(0x40fa30,'GetNativeActionAt40FA30'),
        51:(0x40fac0,'SetNativeActionAt40FAC0')}
def need(v,msg):
 if not v:raise ValueError(msg)
def ld(tag,f):
 s=importlib.util.spec_from_file_location(tag,R/'scripts'/f)
 need(s is not None and s.loader is not None,'original native PE helper missing '+f)
 m=importlib.util.module_from_spec(s);sys.modules[tag]=m;s.loader.exec_module(m);return m
def source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 p=subprocess.run([str(R/'scripts/repo-python'),
      str(R/'scripts/verify-scripted-fighter-stage-190-f856.py')],
      cwd=R,capture_output=True,text=True,timeout=1380)
 (O/'f856-prior-whole-proof.log').write_text(p.stdout+p.stderr)
 need(p.returncode==0,'previous original 190 physical source proof failed '+(p.stdout+p.stderr)[-750:])
 orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x191],by[0x192]-by[0x191]),by[0x191]))
 need(len(orig)==53 and by[0x192]-by[0x191]==166
      and orig[24].mnemonic=='fadd' and orig[24].op_str=='dword ptr [0x659298]'
      and orig[29].mnemonic=='imul' and orig[29].op_str.endswith(', 0x64')
      and orig[31].mnemonic=='fild'
      and orig[33].mnemonic=='fadd' and orig[33].op_str.endswith('+ 0x44]')
      and orig[36].mnemonic=='push' and orig[36].op_str=='0x321'
      and orig[38].op_str=='0x453a70'
      and orig[41].op_str=='0x453d40'
      and orig[43].op_str=='0x40fa30'
      and orig[51].op_str=='0x40fac0'
      and orig[-1].op_str=='0x52cb4f',
      'actual original 191 actor native float/code owner source different')
 src=(R/'.analysis/f856-scripted-stage190/Boss005214B0-F856-whole.cpp').read_text()
 marker='        case 0x191: g_FighterProbeMarker = 402; break;'
 frag=(R/'probes/FighterScriptedFloatShot191F857.inc').read_text()
 need(src.count(marker)==1 and frag.count('case 0x191:')==1
      and frag.count('return;')==1
      and '(*(&POS48))+g_F857ShotYAt00659298' in frag
      and 'SpawnFloatXYAt453A70(0x321' in frag
      and 'PrepareActionAt453D40(0);' in frag,
      'real actor 191 normal source incomplete')
 return 'extern float g_F857ShotYAt00659298;\n'+src.replace(marker,'#include "FighterScriptedFloatShot191F857.inc"',1)
def compile_one(src):
 cpp=O/'Boss005214B0-F857-whole.cpp';obj=O/'Boss005214B0-F857-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=290)
 (O/'compiler.log').write_text(p.stdout+p.stderr)
 need(p.returncode==0,'entire original 191 giant VC7.1 compilation failed '+(p.stdout+p.stderr)[-800:])
 return obj

def main():
 rd=ld('f857rd','compare-coff-function.py')
 ac=ld('f857ac','report-fighter-action-handlers.py')
 f834=ld('f857f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f857f820','verify-scripted-fighter-landing-trio-f820.py')
 f847=ld('f857f847','verify-scripted-fighter-projectile-134135-f847.py')
 f849=ld('f857f849','verify-scripted-fighter-physics-136-f849.py')
 f850=ld('f857f850','verify-scripted-fighter-ground-186187-f850.py')
 f851=ld('f857f851','verify-scripted-fighter-ground-188-f851.py')
 f852=ld('f857f852','verify-scripted-fighter-bounce-189-f852.py')
 f853=ld('f857f853','verify-scripted-fighter-floatshot-18a-f853.py')
 f855=ld('f857f855','verify-scripted-fighter-volley-18b-f855.py')
 f856=ld('f857f856','verify-scripted-fighter-stage-190-f856.py')
 zero=ld('f857zero','verify-fighter-actionzero-natural-source.py')
 sw=ld('f857sw','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'real native original whole fighter and afterRET DATA changed')
 report,mapped=ac.report_boss(rd,pe,d,boss)
 by={x['action']:int(x['handler'],16) for x in mapped}
 obj=compile_one(source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 need((ret,len(I),len(refs),len(code)-ret)==(25488,7038,954,901)
      and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'current actor whole source CODE/COFF or ABI geometry drifted')
 dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
 need(dense>0 and sparse>0 and maps>0,'five original native jump DATA tables not verified')
 mark=[j for j,x in enumerate(I) if x.mnemonic=='mov'
      and x.op_str.endswith(', 0x193')
      and any('g_FighterProbeMarker' in r['symbol']
            and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(mark)==1 and mark[0]>=53,'next true original 192 source marker absent')
 k=mark[0];gen=I[k-53:k]
 case=f834.physical_case(rd,pe,d,code,refs,gen,by,0x191,166,5,BAD,0x192,f820)
 need(case['native_complete_x86']==53
      and case['original_native_enclosing_parent_JMP_exit_ordinals']==[52]
      and gen[52].op_str==hex(ret-4)
      and gen[23].mnemonic=='fld' and gen[23].size==3
      and gen[24].mnemonic=='fadd' and gen[24].size==6,
      'original game 191 Y lvalue width or final direct parent return wrong')
 orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x191],166),by[0x191]))
 for ordinal,(target,symbol) in FIELDS.items():
  a,b=orig[ordinal],gen[ordinal]
  ff=[r for r in refs if b.address<=r['offset']<b.address+b.size]
  need(len(ff)==1 and ff[0]['local_symbol_offset'] is None and ff[0]['addend']==0
       and ff[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
       and symbol in ff[0]['symbol']
       and ff[0]['offset']-gen[0].address==a.address-by[0x191]+a.size-4
       and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
       'real original 191 native PE call/global field wrong '+str(ordinal))
 need(len(BAD)==31 and BAD[-2:]==[162,163],
      'source must report 29 authentic GPR operand errors and 2 original giant JMP bytes')
 last=[
  (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
  (0x186,250,74,7,f850.BAD186,0x187),
  (0x187,214,61,6,f850.BAD187,0x188),
  (0x188,214,61,6,f851.WRONG188,0x189),
  (0x189,381,107,11,f852.BAD189,0x18a),
  (0x18a,250,71,6,f853.BAD,0x18b),
  (0x18b,353,99,7,f855.WRONG,0x190),
  (0x190,217,64,6,f856.BAD,0x191)]
 recent=I[k-53-sum(x[2] for x in last):k-53]
 off=0;prev=[]
 for a,nb,nx,nf,wrong,nxt in last:
  section=recent[off:off+nx];off+=nx
  prev.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,wrong,nxt,f820))
 need(off==len(recent),'prior eight original GPR phase source cases incomplete')
 early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                     (0x135,278,82,7,[274,275],0x136)]
 left=k-53-sum(x[2] for x in last)
 old=I[left-sum(x[2] for x in early):left]
 off=0;before=[]
 for a,nb,nx,nf,wrong,nxt in early:
  section=old[off:off+nx];off+=nx
  before.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,wrong,nxt,f820))
 need(off==len(old),'previous twenty source-backed native whole-case geometry changed')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,tail,0x52cb25,
        [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 need(len(mask)==12 and all(tail[i]==code[ret-46+i] for i in range(46) if i not in mask),
      'selected 191 original shared getter 34/34 nonrelocation should remain correct')
 result={'original_whole_actor':'0x005214B0',
       'original_complete_callable_CODE_B':46755,
       'generated_whole_source_callable_CODE_B':ret,
       'actual_original_191_complete_native_case':case,
       'real_191_native_PE_field_ordinals':list(FIELDS),
       'original_191_GPR_nonrelocation_wrong_B':29,
       'original_191_whole_function_JMP_wrong_offsets':[162,163],
       'eight_previous_original_GPR_source_cases_rechecked':prev,
       'twenty_earlier_original_PE_case_sources_rechecked':before,
       'shared_getter_native_46B_nonrelocation':'34/34',
       'shared_getter_three_actual_original_PE_calls':3,
       'native_five_packed_901B_afterRET_tables_rechecked':True,
       'native_separate_afterRET_jump_DATA_B':901,
       'original_whole_fighter_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
 print('F857 original 191 166B/53 native x86/5 true PE fields in selected 25488B/7038-x86 whole fighter, real Y lvalue width and native facing*100 FILD. 29 honest GPR bytes plus 2 original giant exit JMP bytes differ. Earlier 28 complete native case sources, common 46B getter 34/34 and all five packed 901B tables verified, whole original 46755B NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F857 original selected 191 FAILED:',e,file=sys.stderr);raise SystemExit(1)
