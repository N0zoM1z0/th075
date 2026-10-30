#!/usr/bin/env python3
"""F846: genuine actor original 0x133 270B/78 x86/6 PE fields.

Regenerate and physically verify affected F845 whole fighter
before introducing real selected 133 native side-step. Stage8
facing*70 converted using real FILD scratch and then ADDED
to existing xAt44, not reversed float evaluation order.
Compile one entire normal VC7.1 parent; physically recheck
all 17 preceding original 130/131/12C-12F/C8-D2 cases,
five 901B packed native switch DATA tables and the 46B
shared getter (34/34 original nonrelocation bytes now equal
again). Only authentic encompassing-giant epilogue JMP
operand differs; whole 46755B original still NONEXACT.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f846-scripted-133-launch'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
STATES=[
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
 (0x12c,207,59,6,[203,204],0x12d),
 (0x12d,219,61,6,[215,216],0x12e),
 (0x12e,207,59,6,[203,204],0x12f),
 (0x12f,207,59,6,[203,204],0x130),
 (0x130,202,58,5,[84,85,198,199],0x131),
 (0x131,202,58,5,[84,85,198,199],0x133),
]
def need(cond,reason):
 if not cond:raise ValueError(reason)
def ld(tag,filename):
 sp=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
 need(sp is not None and sp.loader is not None,'missing native physical helper '+filename)
 obj=importlib.util.module_from_spec(sp);sys.modules[tag]=obj;sp.loader.exec_module(obj)
 return obj
def new_source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 cp=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-grounded-131-f845.py')],
     cwd=R,capture_output=True,text=True,timeout=1400)
 (O/'f845-prior-whole-physical.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'prior F845 selected whole fighter failed physical verification '+(cp.stdout+cp.stderr)[-850:])
 raw=rd.pe_bytes_at(pe,by[0x133],by[0x134]-by[0x133])
 native=list(d.disasm(raw,by[0x133]))
 need(len(raw)==270 and len(native)==78
      and native[70].mnemonic=='imul' and native[70].op_str.endswith(', 0x46')
      and native[72].mnemonic=='fild'
      and native[74].mnemonic=='fadd' and native[74].op_str.endswith('+ 0x44]')
      and native[59].mnemonic=='call' and native[59].op_str=='0x453d60'
      and native[-1].op_str=='0x52cb4f',
      'original selected actor real 133 x87 stage8 direction*70 and CFG changed')
 src=(R/'.analysis/f845-scripted-stage131/Boss005214B0-F845-whole.cpp').read_text()
 mark='        case 0x133: g_FighterProbeMarker = 308; break;'
 include=(R/'probes/FighterScriptedSideStep133F846.inc').read_text()
 need(src.count(mark)==1 and include.count('case 0x133:')==1
      and include.count('return;')==1
      and 'S16(0x62)==8' in include
      and 'PrepareActionAt453D60(0x1D)' in include
      and '*70)+F32(0x44)' in include,
      'actual original actor 133 C++ stage/ground source changed')
 return src.replace(mark,'#include "FighterScriptedSideStep133F846.inc"',1)
def compile_one(src):
 cpp=O/'Boss005214B0-F846-whole.cpp';obj=O/'Boss005214B0-F846-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
    cwd=R,env=E,capture_output=True,text=True,timeout=310)
 (O/'compiler.log').write_text(run.stdout+run.stderr)
 need(run.returncode==0,'new original whole fighter with native 133 VC7.1 compile failed '+(run.stdout+run.stderr)[-650:])
 return obj
def main():
 rd=ld('f846rd','compare-coff-function.py')
 ac=ld('f846ac','report-fighter-action-handlers.py')
 f834=ld('f846f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f846f820','verify-scripted-fighter-landing-trio-f820.py')
 zero=ld('f846zero','verify-fighter-actionzero-natural-source.py')
 switch=ld('f846switch','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
           if x['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'pinned original Japanese whole fighter geometry changed')
 report,mp=ac.report_boss(rd,pe,d,boss);by={r['action']:int(r['handler'],16) for r in mp}
 obj=compile_one(new_source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 need((ret,len(I),len(refs),len(code)-ret)==(22731,6211,887,901)
      and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'F846 selected giant source CODE/COFF/x86 or original ABI changed')
 dfields,sfields,maps=zero.verify_physical_tables(boss,report,pe,rd,switch,I,code,refs,ret)
 need(dfields>0 and sfields>0 and maps>0,'real five 901B afterRET packed switch DATA not verified')
 marks=[j for j,x in enumerate(I) if x.mnemonic=='mov' and x.op_str.endswith(', 0x135')
      and any('g_FighterProbeMarker' in r['symbol']
               and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(marks)==1 and marks[0]>=78+sum(r[2] for r in STATES),
      'real following 0x134 source placeholder/whole prefix truncated')
 k=marks[0]
 state=I[k-78:k]
 actual=f834.physical_case(rd,pe,d,code,refs,state,by,0x133,270,6,[266,267],0x134,f820)
 need(actual['native_complete_x86']==78
      and actual['original_native_enclosing_parent_JMP_exit_ordinals']==[77]
      and state[77].op_str==hex(ret-4)
      and state[70].mnemonic=='imul' and state[70].op_str.endswith(', 0x46')
      and state[72].mnemonic=='fild' and state[74].mnemonic=='fadd',
      'genuine original 133 original side-step native FILD and long epilogue wrong')
 preceding=I[k-78-sum(r[2] for r in STATES):k-78]
 cursor=0;old=[]
 for a,nb,nx,nf,bad,nxt in STATES:
  section=preceding[cursor:cursor+nx];cursor+=nx
  old.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
 need(cursor==len(preceding),'all preceding 17 complete original cases not contiguous')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 f=[r for r in refs if ret-46<=r['offset']<ret]
 mask=f820.physical_fields(rd,tail,0x52cb25,f,ret-46,3)
 need(len(mask)==12 and all(tail[j]==code[ret-46+j] for j in range(46) if j not in mask),
      'real original 133 code must restore native default 46B 34/34 nonrelocation bytes')
 out={'original_native_whole_game':'0x005214B0',
      'real_original_callable_CODE_B':46755,
      'new_whole_generated_callable_CODE_B':ret,
      'new_original_game_133_case':actual,
      'actual_facing_multiplier':70,'actual_original_stage8_sidestep':True,
      'original_full_native_earlier_17_cases_rechecked':old,
      'native_common_getter_46B_nonrelocation':'34/34',
      'original_getter_PE_REL32_calls':3,
      'five_native_901B_afterRET_tables_checked':True,
      'original_separately_owned_afterRET_DATA_B':901,
      'original_whole_giant_exact':False,'accepted_new_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
 print('F846: original full 133 side-step 270B/78 x86/6 physical PE fields within 22,731B/6,211-x86 whole fighter. Native nonrelocation bytes identical except genuine final whole-giant long JMP offsets 266/267. Native 46B getter again 34/34 nonfield +3 real calls; all earlier 17 cases and five packed 901B tables verified. Whole original NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F846 selected original fighter 133 FAILED:',e,file=sys.stderr);raise SystemExit(1)
