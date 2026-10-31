"""F904 original authored 2987B WinMain: 30 full source lifetime models.

Normal pinned VC7.1 /Od /GX- and real 654 x86/173 PE
refs/60 postRET scene table. Genuinely used sceneState,
previousState, first Scene4 owner, WNDCLASSEXA/MSG,
windowWidth and windowHeight, never fake padding.
Native original currentScene EBP-0x184, path EBP-0x180.
No whole exact adopted function or mass cold replay.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json,collections,re,itertools
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f904-winmain-staged-owners';O.mkdir(parents=True,exist_ok=True)
pref=R/'.analysis/f795-winmain-grouped-runtime/window-main-ready-directory.cpp'
if not pref.exists():
 cp=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-winmain-native-used-group-f795.py')],
       cwd=R,capture_output=True,text=True,timeout=1550)
 (O/'prior-f795-source.log').write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-670:]
base=pref.read_text()
header=('struct NativeStartupScenePathF500 {GameScenesF455* currentScene; char path[260]; '
        'WNDCLASSEXA win; HWND main; HANDLE readyEvent; char* directoryEnd; };')
assert base.count(header)==1
start='int WINAPI GameApplicationRunF455('
assert base.count(start)==1
before,body=base.split(start,1);body=start+body
choices={'sceneState':('unsigned short sceneState;','unsigned short sceneState=0x2004;'),
         'previousState':('unsigned short previousState;','unsigned short previousState=sceneState;'),
         'firstConstructedScene':('GameScenesF455* firstConstructedScene;','Scene4F455* firstConstructedScene = new Scene4F455;'),
         'msg':('MSG msg;','MSG msg;'),
         'windowWidth':('int windowWidth;','int windowWidth=GetSystemMetrics(45)'),
         'windowHeight':('int windowHeight;','int windowHeight=GetSystemMetrics(46)')}
def grouped(names):
 src=base
 head=header.replace(' };',' '+ ' '.join(choices[k][0] for k in names)+' };')
 src=src.replace(header,head,1)
 top,body=src.split(start,1);body=start+body
 for key in names:
  # Replace exact used variable occurrences inside function only.
  body=re.sub(r'\b'+key+r'\b', 'context.'+key,body)
  if key=='sceneState':
   assert body.count('unsigned short context.sceneState=0x2004;')==1
   body=body.replace('unsigned short context.sceneState=0x2004;',
                     'context.sceneState=0x2004;',1)
  elif key=='previousState':
   old=('unsigned short context.previousState=context.sceneState;'
        if 'sceneState' in names and names.index('sceneState')<names.index('previousState') else
        'unsigned short context.previousState=sceneState;')
   assert body.count(old)==1
   body=body.replace(old,old[len('unsigned short '):],1)
  elif key=='firstConstructedScene':
   assert body.count('Scene4F455* context.firstConstructedScene = new Scene4F455;')==1
   body=body.replace('Scene4F455* context.firstConstructedScene = new Scene4F455;',
                     'context.firstConstructedScene = new Scene4F455;',1)
  elif key=='msg':
   assert body.count('MSG context.msg;')==1
   body=body.replace('MSG context.msg;','',1)
  elif key=='windowWidth':
   assert body.count('int context.windowWidth=GetSystemMetrics(45)')==1
   body=body.replace('int context.windowWidth=GetSystemMetrics(45)',
                     'context.windowWidth=GetSystemMetrics(45)',1)
  elif key=='windowHeight':
   assert body.count('int context.windowHeight=GetSystemMetrics(46)')==1
   body=body.replace('int context.windowHeight=GetSystemMetrics(46)',
                     'context.windowHeight=GetSystemMetrics(46)',1)
 return top+body
combo=[(),
 ('sceneState',),('previousState',),('sceneState','previousState'),
 ('firstConstructedScene',),('sceneState','firstConstructedScene'),
 ('previousState','firstConstructedScene'),
 ('sceneState','previousState','firstConstructedScene'),
 ('msg',),('sceneState','msg'),('previousState','msg'),
 ('sceneState','previousState','msg'),
 ('firstConstructedScene','msg'),
 ('sceneState','previousState','firstConstructedScene','msg'),
 ('windowWidth',),('windowHeight',),
 ('windowWidth','windowHeight'),
 ('sceneState','windowWidth'),
 ('sceneState','windowHeight'),
 ('sceneState','previousState','windowWidth','windowHeight'),
 ('sceneState','firstConstructedScene','windowWidth','windowHeight'),
 ('msg','windowWidth','windowHeight'),
 ('sceneState','msg','windowWidth','windowHeight'),
 ('sceneState','previousState','msg','windowWidth','windowHeight')]
cases={'baseline':base}
for a in combo[1:]:
 tag='group-'+'-'.join(a);cases[tag]=grouped(a)
# True members with alternative order; all assigned/used.
for order in (('sceneState','previousState'),('previousState','sceneState'),
              ('msg','sceneState'),('sceneState','msg'),
              ('firstConstructedScene','sceneState'),
              ('sceneState','firstConstructedScene')):
 tag='order-'+ '-'.join(order)
 if tag not in cases:cases[tag]=grouped(order)
sp=importlib.util.spec_from_file_location('f904rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
raw=rd.pe_bytes_at(pe,0x602a60,2987);N=list(D.disasm(raw,0x602a60))
assert len(N)==654 and N[9].op_str=='dword ptr [ebp - 0x184], 0' and N[17].op_str=='eax, [ebp - 0x180]'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[];cnt=collections.Counter()
for tag,src in cases.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,
     capture_output=True,text=True,timeout=290)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':tag,'compile_failure':(cp.stdout+cp.stderr)[-420:]}
  rows.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 size=I[-1].address+I[-1].size
 row={'variant':tag,'full_source_CODE_B':size,'native_complete_CODE_B':2987,
      'source_x86':len(I),'real_COFF_fields':len(refs),
      'afterRET_scene_jump_DATA_B':len(code)-size,
      'native_original_x86_mnemonics_equal':sum(a.mnemonic==b.mnemonic for a,b in zip(N,I)),
      'native_original_x86_width_equal':sum(a.size==b.size for a,b in zip(N,I)),
      'real_scene_slot_ord9':I[9].op_str,
      'real_path_slot_ord17':I[17].op_str,
      'real_this_scene_and_path_offsets_both_match':I[9].op_str==N[9].op_str and I[17].op_str==N[17].op_str}
 cnt[(size,len(I),row['native_original_x86_width_equal'],
      row['real_scene_slot_ord9'],row['real_path_slot_ord17'])]+=1
 rows.append(row);print(json.dumps(row),flush=True)
(O/'research-summary.json').write_text(json.dumps(rows,indent=2)+'\n')
print('F904 WINMAIN total',len(rows),'genuine lifetime variants; matched original scene+path',sum(x.get('real_this_scene_and_path_offsets_both_match') for x in rows))
print('SHAPES',dict((str(k),v) for k,v in cnt.items()))

assert len(cases)==len(rows)==30
assert all('compile_failure' not in r for r in rows)
assert all(r['source_x86']==654 and r['real_COFF_fields']==173
           and r['afterRET_scene_jump_DATA_B']==60
           and r['native_original_x86_mnemonics_equal']==654
           for r in rows)
assert all(not r['real_this_scene_and_path_offsets_both_match'] for r in rows)
assert max(r['native_original_x86_width_equal'] for r in rows)==633
assert rows[0]['variant']=='baseline'
assert (rows[0]['full_source_CODE_B'],
        rows[0]['native_original_x86_width_equal'])==(3002,619)
improved=[r for r in rows if r['native_original_x86_width_equal']==633]
assert len(improved)>=3 and all(
   r['full_source_CODE_B']==2960 for r in improved)
(O/'verified-stage-source.json').write_text(json.dumps({
  'native_original_author_game_function':'0x00602A60',
  'native_entire_callable_CODE_B':2987,'native_x86':654,
  'original_real_physically_resolved_afterRET_15_scene_DATA_B':60,
  'normal_VC71_exception_flag':'/GX-',
  'complete_genuine_live_state_source_variants':len(rows),
  'normal_original_source_COFF_field_count':173,
  'all_source_654_native_ordered_mnemonics_equal':True,
  'baseline_equal_x86_widths':'619/654',
  'best_two_real_short_scene_state_equal_widths':'633/654',
  'source_original_scene_path_EBP_both_restored':False,
  'native_real_scene_EBP':'-0x184',
  'native_real_path_EBP':'-0x180',
  'whole_game_original_exact':False,
  'new_adopted_whole_callable_CODE_B':0,
  'mass_cold_replay':False,
  'actual_complete_source_profiles':rows
},indent=2)+'\n')
print('F904 stage group: 30 full /GX- WinMain 2987B/654x86 original, 173 original-shaped PE refs, 60B DATA. Real scenario two short states increase 619->633 original-width matches but path/scene EBP remain wrong; no native whole exact.')
