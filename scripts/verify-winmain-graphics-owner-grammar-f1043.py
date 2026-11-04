#!/usr/bin/env python3
"""Whole 2,987-byte WinMain: test an actual graphics RAII subobject owner.

Each trial genuinely constructs/destroys graphics and initializes the live
scene pointer; no dummy stack slots, manual assembly, byte grafts or truncated
whole comparisons. All original PE/native and source origins are separate.
"""
from pathlib import Path
import importlib.util,json,os,re,subprocess,sys,collections
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1043-winmain-graphics-owner';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/WinMainNativeOwnerOrderF911.cpp').read_text()
struct='struct NativeStartupScenePathF500 {HWND main; GameScenesF455* currentScene; char path[260]; WNDCLASSEXA win; HANDLE readyEvent; char* directoryEnd; unsigned short sceneState; unsigned short previousState; };'
body='    NativeStartupScenePathF500 context;\n    context.currentScene = 0;\n    GraphicsClientF455 graphics;'
assert base.count(struct)==1 and base.count(body)==1
entries=['GraphicsClientF455 graphics','HWND main','GameScenesF455* currentScene','char path[260]','WNDCLASSEXA win', 'HANDLE readyEvent', 'char* directoryEnd','unsigned short sceneState','unsigned short previousState']
cases={'F911-baseline':base}
for placement in ('before-main','after-main','after-scene','after-path','after-win'):
 fields=entries[1:]
 pos={'before-main':0,'after-main':1,'after-scene':2,'after-path':3,'after-win':4}[placement]
 fields.insert(pos,entries[0])
 for init in ('member-init','body-init'):
  for mode in ('ordinary','forced-inline'):
   ctor=('__forceinline ' if mode=='forced-inline' else '')+'NativeStartupScenePathF500()'+(':currentScene(0)' if init=='member-init' else '')+' {'+('currentScene=0;' if init=='body-init' else '')+'}'
   newstruct='struct NativeStartupScenePathF500 {'+'; '.join(fields)+'; '+ctor+' };'
   source=base.replace(struct,newstruct,1).replace(body,'    NativeStartupScenePathF500 context;\n    InputClientF455 input;')
   # Remove the original repeated Input declaration (still one live input).
   source=source.replace('    InputClientF455 input;\n    InputClientF455 input;', '    InputClientF455 input;',1)
   assert source.count('InputClientF455 input;')==1 and source.count('SoundClientF455 sound;')==1
   assert source.count('GraphicsClientF455 graphics;')==1
   name=placement+'-'+init+'-'+mode
   cases[name]=source
sp=importlib.util.spec_from_file_location('f1043rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
N=list(D.disasm(rd.pe_bytes_at(PE,0x602a60,2987),0x602a60))
assert len(N)==654
T=rd.pe_bytes_at(PE,0x60360b,60)
case_ord=[next(i for i,x in enumerate(N) if x.address==int.from_bytes(T[4*j:4*j+4],'little')) for j in range(15)]
assert case_ord==[383,399,415,431,367]+[447+16*i for i in range(10)]
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
baseline_symbols=None
for tag,s in cases.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(s)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=300)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 row={'variant':tag,'original_whole_CODE_B':2987,'original_whole_x86':654,'original_afterRET_DATA_B':60,'native_exact':False}
 if cp.returncode:
  row['compiler_error']=(cp.stdout+cp.stderr)[-600:]
  print(tag,'COMPILE ERROR',row['compiler_error'][-150:],flush=True)
  rows.append(row);continue
 code,refs=rd.object_function(obj,'?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z')
 ins=[]
 for x in D.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 end=ins[-1].address+ins[-1].size
 relevant=collections.Counter((r['type'],r['symbol']) for r in refs if any(x in r['symbol'] for x in ('NativeStartupScenePathF500','GraphicsClientF455','InputClientF455','SoundClientF455')))
 if baseline_symbols is None:baseline_symbols=relevant
 row['original_graphics_ctor_dtor_symbol_multiset_retained']=(relevant==baseline_symbols)
 row['mismatched_real_RAII_symbols']=[{'type':k[0],'symbol':k[1],'source_occurrences':relevant[k],'baseline_occurrences':baseline_symbols[k]} for k in sorted(set(relevant)|set(baseline_symbols)) if relevant[k]!=baseline_symbols[k]]
 row.update({'whole_generated_CODE_B':end,'whole_source_x86':len(ins),'source_COFF_records':len(refs),'frame':ins[2].op_str,
  'source_first_20_mnemonics':[x.mnemonic for x in ins[:20]],
  'real_source_slots_at_9_10_17':[ins[k].op_str for k in (9,10,17)]})
 if len(ins)==654:
  badm=[i for i,(a,b) in enumerate(zip(N,ins)) if a.mnemonic!=b.mnemonic]
  badw=[i for i,(a,b) in enumerate(zip(N,ins)) if a.size!=b.size]
  row.update({'wrong_mnemonic_count':len(badm),'wrong_width_count':len(badw),'wrong_width_ordinals':badw,
    'native_matching_widths':654-len(badw),
    'source_original_stack_slots':{str(i):ins[i].op_str for i in (7,9,10,12,14,17,114,281,282,635,637,643)}})
  if len(code)-end==60:
   table=[r for r in refs if r['offset']>=end]
   row['native_afterRET_15_physical_ordinal_matches']=(len(table)==15 and all(r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset']==ins[case_ord[j]].address for j,r in enumerate(sorted(table,key=lambda t:t['offset']))))
   row['native_afterRET_60_B_original_nonfield']=len(code)-end
 rows.append(row)
 print(tag,'whole',end,'x86',len(ins),'M/W',row.get('wrong_mnemonic_count'),row.get('wrong_width_count'),'frame',row['frame'],'COFF',len(refs),'original ctor/dtor symbols',row['original_graphics_ctor_dtor_symbol_multiset_retained'],flush=True)
(O/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
assert len(rows)==21 and rows[0]['whole_generated_CODE_B']==2984 and rows[0]['whole_source_x86']==654
assert all(r['source_COFF_records']==173 and r['whole_source_x86']==653 and r['original_graphics_ctor_dtor_symbol_multiset_retained']==False for r in rows[1:])
assert rows[0]['wrong_mnemonic_count']==0 and rows[0]['wrong_width_count']==9
print('F1043 whole WinMain owner grammar compiled',len(rows),'real RAII source variants; no exact credit. Results under ignored analysis directory.')
