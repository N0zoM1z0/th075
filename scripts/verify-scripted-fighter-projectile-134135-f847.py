#!/usr/bin/env python3
"""F847: genuine 134/135 original sprite cases within whole 005214B0 fighter.

Rebuild F846 entire native-backed 133 current parent first, add real
134/135 game 0x334/0x339 projectiles at stage4/7 and native stage5/7
preparation animation1D. Compile only one selected entire VC7.1
whole parent. Each original 278B/82-x86/7 physical PE-field case
is native-equal except two authentic original encompassing parent
final-JMP bytes 274/275. Recheck all 18 prior native cases, five
complete original 901B afterRET jump tables and original 46B
default-getter 34/34 nonrelocation byte equality and three PE calls.
No standalone accepted inner-case CODE or all-unit cold replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f847-scripted-spawns134135'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BASE=0x005214B0
VALUES={0x134:(4,0x334,5),0x135:(7,0x339,7)}
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
 (0x133,270,78,6,[266,267],0x134),
]
def need(v,msg):
 if not v:raise ValueError(msg)
def ld(t,f):
 sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
 need(sp is not None and sp.loader is not None,'missing original PE helper '+f)
 m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m)
 return m
def generate_source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 cp=subprocess.run([str(R/'scripts/repo-python'),
          str(R/'scripts/verify-scripted-fighter-sidestep-133-f846.py')],
     cwd=R,capture_output=True,text=True,timeout=1320)
 (O/'f846-prior-original-evidence.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'prior native 133 and physical whole fighter failed '+(cp.stdout+cp.stderr)[-870:])
 source=(R/'.analysis/f846-scripted-133-launch/Boss005214B0-F846-whole.cpp').read_text()
 for action,(stage,kind,prep) in VALUES.items():
  native=list(d.disasm(rd.pe_bytes_at(pe,by[action],by[action+1]-by[action]),by[action]))
  need(len(native)==82 and by[action+1]-by[action]==278
       and native[51].mnemonic=='cmp' and native[51].op_str.endswith(', '+str(stage))
       and native[67].mnemonic=='push' and native[67].op_str==hex(kind)
       and native[69].mnemonic=='call' and native[69].op_str=='0x453a70'
       and native[72].mnemonic=='cmp' and native[72].op_str.endswith(', '+str(prep))
       and native[78].mnemonic=='push' and native[78].op_str=='0x1d',
       'selected actor true 134/135 native sprite/prepare parameters differ '+hex(action))
  marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
  fragment=(R/f'probes/FighterScriptedProjectile{action:X}F847.inc').read_text()
  need(source.count(marker)==1 and fragment.count(f'case 0x{action:X}:')==1
       and fragment.count('return;')==1
       and f'SpawnDirectedAt453A70(0x{kind:X}' in fragment
       and f'S16(0x62)=={stage}' in fragment
       and f'S16(0x62)=={prep}' in fragment
       and 'PrepareActionAt453D60(0x1D)' in fragment,
       'original selected actor projectile stage source altered '+hex(action))
  source=source.replace(marker,f'#include "FighterScriptedProjectile{action:X}F847.inc"',1)
 return source
def compile_one(src):
 cpp=O/'Boss005214B0-F847-whole.cpp';obj=O/'Boss005214B0-F847-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=E,capture_output=True,text=True,timeout=305)
 (O/'compiler.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'whole actual fighter 134/135 VC7.1 C++ build failed '+(cp.stdout+cp.stderr)[-820:])
 return obj
def main():
 rd=ld('f847rd','compare-coff-function.py')
 ac=ld('f847ac','report-fighter-action-handlers.py')
 f834=ld('f847f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f847f820','verify-scripted-fighter-landing-trio-f820.py')
 zero=ld('f847zero','verify-fighter-actionzero-natural-source.py')
 switch=ld('f847switch','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
           if x['address']==BASE)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
      'original Japanese fighter identity changed')
 report,mp=ac.report_boss(rd,pe,d,boss);by={r['action']:int(r['handler'],16) for r in mp}
 obj=compile_one(generate_source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 ins=[]
 for x in d.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 ret=ins[-1].address+ins[-1].size
 need((ret,len(ins),len(refs),len(code)-ret)==(23257,6371,899,901)
      and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
      'current selected whole fighter source ABI/COFF/x86 geometry changed')
 dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,switch,ins,code,refs,ret)
 need(dense>0 and sparse>0 and maps>0,'five physical original 901B afterRET tables missing')
 marker=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x137')
         and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(marker)==1 and marker[0]>=164+sum(s[2] for s in STATES),
      'native next 136 marker/whole case boundaries missing')
 end=marker[0]
 results=[]
 for j,action in enumerate((0x134,0x135)):
  seg=ins[end-164+j*82:end-164+(j+1)*82]
  phys=f834.physical_case(rd,pe,d,code,refs,seg,by,action,278,7,[274,275],action+1,f820)
  need(phys['native_complete_x86']==82
       and phys['original_native_enclosing_parent_JMP_exit_ordinals']==[81]
       and seg[-1].op_str==hex(ret-4),
       'original actor native sprite-case stage/direct exit source changed')
  results.append(phys)
 old=ins[end-164-sum(s[2] for s in STATES):end-164]
 cur=0;previous=[]
 for act,nb,nx,nf,wrong,nxt in STATES:
  seg=old[cur:cur+nx];cur+=nx
  previous.append(f834.physical_case(rd,pe,d,code,refs,seg,by,act,nb,nf,wrong,nxt,f820))
 need(cur==len(old),'original 18 preceding native gameplay cases not contiguous')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,tail,0x52cb25,
        [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 need(len(mask)==12 and all(tail[k]==code[ret-46+k] for k in range(46) if k not in mask),
      'actual original 46B common getter default must match all 34 native nonfield bytes')
 out={'original_giant':'0x005214B0',
      'original_entire_native_callable_CODE_B':46755,
      'new_generated_whole_callable_CODE_B':ret,
      'original_native_134_135_case_sources':results,
      'native_original_two_full_inner_CODE_B':556,
      'native_original_two_full_x86':164,
      'original_two_physical_PE_fields':14,
      'true_original_sprites':{'0x134':'0x334','0x135':'0x339'},
      'true_original_spawn_stage':{'0x134':4,'0x135':7},
      'true_original_prepare_stage':{'0x134':5,'0x135':7},
      'all_preceding_18_original_PE_cases_reverified':previous,
      'original_default_46B_nonrelocation_equal':'34/34',
      'default_three_original_PE_calls':3,
      'original_five_901B_afterRET_tables_checked':True,
      'original_separate_afterRET_DATA_B':901,
      'original_whole_function_exact':False,'new_accepted_whole_authored_CODE_B':0,
      'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
 print('F847 two authentic native 134/135 sprite states 2x278B/82 x86/7 PE fields in a fresh 23,257B/6,371-x86 full fighter. Both differ only in real original final whole-giant epilogue two-byte JMP operands. Prior 18 full cases, native shared getter 34/34 nonfield +3 PE calls, five 901B packed tables verified. Giant 46,755B NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F847 original whole fighter 134/135 FAILED:',e,file=sys.stderr);raise SystemExit(1)
