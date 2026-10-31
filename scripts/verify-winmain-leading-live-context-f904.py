"""F904 leading actual firstScene, unsigned short state/message real owners.

Thirteen fully used original C++ owner-field permutations in
complete source WinMain, pinned VC7.1 /GX-. No fake members.
None reproduces both original Scene EBP-0x184 and module
path EBP-0x180. Keep all whole original x86 and afterRET scene
data; dependent on only affected F904 stage proof.
"""
from pathlib import Path
import json,importlib.util,sys,os,subprocess,collections,itertools
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f904-winmain-staged-owners'
stage=O/'verified-stage-source.json'
if not stage.exists():
 cp=subprocess.run([str(R/'scripts/repo-python'),
      str(R/'scripts/verify-winmain-stage-live-context-f904.py')],
      cwd=R,capture_output=True,text=True,timeout=1650)
 (O/'prior-f904-stage-source.log').write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-820:]
previous=json.loads(stage.read_text())
assert previous['complete_genuine_live_state_source_variants']==30
assert previous['whole_game_original_exact'] is False
prefix=R/'.analysis/f795-winmain-grouped-runtime/window-main-ready-directory.cpp'
assert prefix.exists()
base=prefix.read_text()
hdr='struct NativeStartupScenePathF500 {GameScenesF455* currentScene; char path[260]; WNDCLASSEXA win; HWND main; HANDLE readyEvent; char* directoryEnd; };'
assert base.count(hdr)==1
# Reuse actual compiled current author lifetime variants from phase1:
# each has all real field owner accesses.
typed={'f':'GameScenesF455* firstConstructedScene;',
       's':'unsigned short sceneState;',
       'p':'unsigned short previousState;',
       'm':'MSG msg;',
       'w':'int windowWidth;',
       'h':'int windowHeight;'}
files={'f':'group-firstConstructedScene.cpp',
       's':'group-sceneState.cpp','p':'group-previousState.cpp',
       'm':'group-msg.cpp','w':'group-windowWidth.cpp',
       'h':'group-windowHeight.cpp',
       'fs':'group-sceneState-firstConstructedScene.cpp',
       'sp':'group-sceneState-previousState.cpp',
       'fm':'group-firstConstructedScene-msg.cpp',
       'sm':'group-sceneState-msg.cpp',
       'fsh':'group-sceneState-firstConstructedScene-windowWidth-windowHeight.cpp'}
def srcfile(key):
 if key in files:
  p=O/files[key]
  if p.exists():return p.read_text()
 return None
variants={}
# Field reorder of genuinely used real owner values without fake
# padding. Reorder full struct member declarations only, keep real
# game behavior, calls and lifetimes physically the same.
for letters in ('f','s','p','fs','sf','sp','ps','fm','mf','sm','ms','sfm','fsm',
                'msf','fms','spf','fps','fsh','fsw','wsf','hsf','sfw'):
 unique=''.join(dict.fromkeys(letters))
 parts=tuple(typed[c] for c in unique)
 base_key=''.join(sorted(unique))
 candidates=[p for p in O.glob('group-*.cpp')]
 found=None
 for p in candidates:
  txt=p.read_text()
  head=txt.split('struct NativeStartupScenePathF500 {',1)[1].split('};',1)[0]
  if all(part in head for part in parts):
   # Strict same field count: check relevant known additions
   owned=set()
   for c,decl in typed.items():
    if decl in head:owned.add(c)
   if owned==set(unique):
    found=txt;break
 if not found:continue
 ahead=' '.join(typed[c] for c in unique)
 orig_header=found.split('struct NativeStartupScenePathF500 {',1)[1].split('};',1)[0]
 tail='GameScenesF455* currentScene; char path[260]; WNDCLASSEXA win; HWND main; HANDLE readyEvent; char* directoryEnd;'
 assert all(item in orig_header for item in (tail,'currentScene','path'))
 replace='struct NativeStartupScenePathF500 {'+orig_header+'};'
 newhead='struct NativeStartupScenePathF500 {'+ahead+' '+tail+'};'
 assert found.count(replace)==1
 variants['front-'+unique]=found.replace(replace,newhead,1)
# Other used, non-aggregate, local positions cannot be repositioned
# inside struct without real read/write. No inert members allowed.
D=Cs(CS_ARCH_X86,CS_MODE_32)
sp=importlib.util.spec_from_file_location('f904rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
pe=rd.verified_target()
N=list(D.disasm(rd.pe_bytes_at(pe,0x602a60,2987),0x602a60));assert len(N)==654
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[];stats=collections.Counter()
for tag,src in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
     cwd=R,env=E,capture_output=True,text=True,timeout=310)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':tag,'compiler_failure':(cp.stdout+cp.stderr)[-300:]}
  rows.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 row={'variant':tag,'whole_CODE_B':ret,'x86':len(I),'COFF_fields':len(refs),
      'afterRET_DATA_B':len(code)-ret,
      'full_native_x86_mnemonic_match':sum(a.mnemonic==b.mnemonic for a,b in zip(N,I)),
      'full_native_x86_width_match':sum(a.size==b.size for a,b in zip(N,I)),
      'currentScene_stack':I[9].op_str,
      'path_stack':I[17].op_str,
      'both_actual_original_scene_path_stack_slots_match':I[9].op_str==N[9].op_str and I[17].op_str==N[17].op_str}
 stats[(ret,len(I),row['full_native_x86_width_match'],row['currentScene_stack'],row['path_stack'])]+=1
 rows.append(row);print(json.dumps(row),flush=True)
(O/'leading-owner-summary.json').write_text(json.dumps(rows,indent=2)+'\n')
print('F904 real leading-owner variants',len(rows),
      'original both scene/path match',sum(r.get('both_actual_original_scene_path_stack_slots_match',False) for r in rows))
print('SHAPES',dict((str(k),v) for k,v in stats.items()))

assert len(variants)==len(rows)==13
assert all('compiler_failure' not in row for row in rows)
assert all(row['x86']==654 and row['COFF_fields']==173
           and row['afterRET_DATA_B']==60
           and row['full_native_x86_mnemonic_match']==654
           and not row['both_actual_original_scene_path_stack_slots_match']
           for row in rows)
assert sorted(set(row['full_native_x86_width_match'] for row in rows))==[615,619]
assert set(row['whole_CODE_B'] for row in rows)=={3002,3014}
(O/'verified-leading-summary.json').write_text(json.dumps({
  'native_original_author_game_function':'0x00602A60',
  'native_whole_CODE_B':2987,
  'native_whole_x86':654,
  'normal_VC71_exception_flag':'/GX-',
  'genuine_live_leading_Cpp_source_permutations':len(rows),
  'all_original_winmain_173_source_COFF_field_count':True,
  'native_original_scene_path_physical_EBP_both_restored':False,
  'original_scene_EBP':'-0x184',
  'original_path_EBP':'-0x180',
  'all_original_15_scene_afterRET_DATA_B_verified':60,
  'whole_native_exact':False,
  'new_adopted_whole_callable_CODE_B':0,
  'mass_cold_replay':False,
  'source_profiles':rows
},indent=2)+'\n')
print('F904 lead: 13 original WinMain complete /GX- 654-x86 173-field source permutations of REAL scene-state / firstScene / msg members, all whole original scene and path EBP still wrong. Combined F904 43 complete actual C++ source variants, best 633/654 native width matches, but entire 2987B still NONEXACT.')
