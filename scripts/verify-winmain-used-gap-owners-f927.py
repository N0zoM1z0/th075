#!/usr/bin/env python3
"""F927 bounded entire-WinMain tests of real used firstScene/HWND gap fields.

No fake padding: move real HANDLE, char* directory end and computed
window metrics with the real first scene pointer in the same source
aggregate before HWND/currentScene/path. Full original PE and all 654
native x86, 16 physical scene allocations and 15 afterRET dispatch
relocations are checked. No original whole exact acceptance.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,os,sys,subprocess,re,json

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f927-winmain-used-gap-proof';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/WinMainNativeOwnerOrderF911.cpp').read_text()
head='struct NativeStartupScenePathF500 {HWND main; GameScenesF455* currentScene; char path[260]; WNDCLASSEXA win; HANDLE readyEvent; char* directoryEnd; unsigned short sceneState; unsigned short previousState; };'
assert base.count(head)==1
loc='Scene4F455* firstConstructedScene = new Scene4F455;'
assert base.count(loc)==1 and base.count('context.currentScene = firstConstructedScene;')==1
fields={'r':'HANDLE readyEvent;','d':'char* directoryEnd;',
        'w':'int windowWidth;','h':'int windowHeight;'}
def make(order):
 src=base
 if order is None:return src
 members=('GameScenesF455* firstConstructedScene; '+
      ' '.join(fields[key] for key in order)+
      (' ' if order else '')+'HWND main; GameScenesF455* currentScene; '+
      'char path[260]; WNDCLASSEXA win; '+
      ' '.join(fields[key] for key in 'rd' if key not in order)+
      ' unsigned short sceneState; unsigned short previousState;')
 src=src.replace(head,'struct NativeStartupScenePathF500 {'+members+' };',1)
 src=src.replace(loc,'context.firstConstructedScene = new Scene4F455;',1).replace(
       'context.currentScene = firstConstructedScene;',
       'context.currentScene = context.firstConstructedScene;',1)
 for var in ('windowWidth','windowHeight'):
  key='w' if var=='windowWidth' else 'h'
  if key not in order:continue
  src=src.replace('int '+var+'=GetSystemMetrics(',
      'context.'+var+'=GetSystemMetrics(',1)
  top,body=src.split('int WINAPI GameApplicationRunF455(',1)
  body=re.sub(r'(?<![\w.])'+var+r'\b','context.'+var,body)
  src=top+'int WINAPI GameApplicationRunF455('+body
 return src

spec=importlib.util.spec_from_file_location('f927reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32)
N=list(D.disasm(rd.pe_bytes_at(rd.verified_target(),0x602a60,2987),0x602a60))
assert len(N)==654 and N[-1].mnemonic=='ret'
native_table=rd.pe_bytes_at(rd.verified_target(),0x60360b,60)
case_ord=[next(i for i,x in enumerate(N)
 if x.address==int.from_bytes(native_table[j*4:j*4+4],'little')) for j in range(15)]
assert case_ord==[383,399,415,431,367]+[447+16*i for i in range(10)]
assert N[281].op_str=='dword ptr [ebp - 0x19c], ecx'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,order in [('F911-baseline',None),('actual-initial-owner',''),
                  ('event-directory-gap','rd'),('all-four-used-gap','rdwh')]:
 src=make(order)
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
    cwd=R,env=E,capture_output=True,text=True,timeout=320)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-870:]
 code,refs=rd.object_function(obj,'?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 size=I[-1].address+I[-1].size
 assert len(I)==654 and len(refs)==173 and len(code)-size==60
 assert all(a.mnemonic==b.mnemonic for a,b in zip(N,I))
 table=sorted((r for r in refs if r['offset']>=size),key=lambda r:r['offset'])
 assert len(table)==15
 for i,r in enumerate(table):
  assert r['type']=='DIR32' and r['addend']==0 and r['offset']==size+4*i
  assert r['local_symbol_offset']==I[case_ord[i]].address
 for idx in [270]+[368+16*i for i in range(15)]:
  assert N[idx].mnemonic=='call' and I[idx].mnemonic=='call'
  assert N[idx-1].op_str==I[idx-1].op_str
  ctor=[r for r in refs if I[idx+6].address<=r['offset']<I[idx+6].address+I[idx+6].size]
  assert len(ctor)==1 and ctor[0]['type']=='REL32' and ctor[0]['addend']==0
  cls=4 if idx in (270,368) else (idx-368)//16-1 if idx<448 else (idx-368)//16
  assert ctor[0]['symbol']==f'??0Scene{cls}F455@@QAE@XZ'
 row={'variant':tag,'whole_source_CODE_B':size,
  'native_x86':len(I),'native_matching_x86_widths':sum(a.size==b.size for a,b in zip(N,I)),
  'source_frame':I[2].op_str,'orig_source_EBP_by_ordinal':{
     str(i):I[i].op_str for i in (281,114,9,17)},
  'original_actual_EBP_by_ordinal':{
     str(i):N[i].op_str for i in (281,114,9,17)},
  'original_4_meaningful_EBP_roles_recovered':sum(I[i].op_str==N[i].op_str for i in (281,114,9,17)),
  'native_16_ctor_size_pairs_correct':True,
  'native_15_afterRET_case_target_ordinals_correct':True,
  'source_COFF_fields':len(refs),'source_afterRET_DATA_B':len(code)-size}
 rows.append(row)
 print(tag,'whole',size,'native width',row['native_matching_x86_widths'],
   'actual four slots',row['original_4_meaningful_EBP_roles_recovered'],flush=True)
assert [r['whole_source_CODE_B'] for r in rows]==[2984,2984,3005,3017]
assert [r['native_matching_x86_widths'] for r in rows]==[645,645,638,634]
assert all(r['original_4_meaningful_EBP_roles_recovered']==0 for r in rows)
assert all(not r['whole_source_CODE_B']==2987 for r in rows)
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_WinMain':'0x00602A60','native_whole_CODE_B':2987,
 'native_complete_x86':654,'real_original_first_scene_EBP':'-0x19C',
 'real_original_HWND_EBP':'-0x188','original_scene_EBP':'-0x184',
 'original_module_path_EBP':'-0x180',
 'real_used_member_representative_full_cpp_compiles':4,
 'previous_full_66_used_gap_source_control_matrix':True,
 'whole_game_exact':False,'accepted_new_whole_original_CODE_B':0,
 'mass_cold_replay':False,'verified_complete_source_profiles':rows
},indent=2)+'\n')
print('F927 checked native all 654 whole x86, 16 scene new/ctors, 15 native switch cases. Real firstScene+used member gap does not restore four slots; WinMain remains NONEXACT.')
