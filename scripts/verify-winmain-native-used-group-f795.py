"""F795: entire native 2,987B/654-x86 WinMain used-window/scene context.

Only genuine used HWND, MSG, WNDCLASSEXA, HANDLE and metrics
are grouped/permuted; test complete pinned original native
startup, not partial 15-scene switch cases or fake frame padding.
The real physical graphics/main/scene/path adjacency is PE-read
independently. No authored whole exact CODE is credited.
"""
from pathlib import Path
import importlib.util,sys,os,re,json,subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f795-winmain-grouped-runtime';O.mkdir(parents=True,exist_ok=True)
def load(tag,file):
 spec=importlib.util.spec_from_file_location(tag,R/file);m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m);return m
f615=load('f795_f615','scripts/verify-winmain-local-layout-f615.py')
rd=load('f795_rd','scripts/compare-coff-function.py')
pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
n=list(d.disasm(rd.pe_bytes_at(pe,0x00602A60,2987),0x00602A60));assert len(n)==654
native_real={7:'ecx, [ebp - 0x3d]',9:'dword ptr [ebp - 0x184], 0',10:'ecx, [ebp - 0x189]',
             12:'ecx, [ebp - 0x62]',14:'ecx, [ebp - 0x61]',17:'eax, [ebp - 0x180]',
             55:'dword ptr [ebp - 0x30], 0x30',114:'dword ptr [ebp - 0x188], eax'}
for j,role in native_real.items():
 assert n[j].op_str==role, 'actual original PE startup stack role differs at '+str(j)
assert sum(x.mnemonic=='call' for x in n)==123
assert n[-1].mnemonic=='ret' and n[-1].op_str=='0x10'
native_after=rd.pe_bytes_at(pe,0x0060360B,60)
assert len(native_after)==60
actual_jump_targets=[int.from_bytes(native_after[i:i+4],'little') for i in range(0,60,4)]
assert len(actual_jump_targets)==15 and all(0x602a60<=x<0x60360b for x in actual_jump_targets)
base=f615.create_sources()['scene-path-plus-msg-plus-event']
header='struct NativeStartupScenePathF500 {GameScenesF455* currentScene; char path[260];};'
assert base.count(header)==1
flags={'main':'HWND','readyEvent':'HANDLE','msg':'MSG','win':'WNDCLASSEXA','directoryEnd':'char*',
       'windowWidth':'int','windowHeight':'int'}
variants={
 'window-main-dir':['win','main','directoryEnd'],
 'window-main-msg':['win','main','msg'],
 'window-msg-main':['win','msg','main'],
 'message-window-main':['msg','win','main'],
 'window-main-ready-directory':['win','main','readyEvent','directoryEnd'],
 'window-main-width':['win','main','windowWidth'],
 'window-main-height':['win','main','windowHeight'],
 'window-main-width-height':['win','main','windowWidth','windowHeight'],
 'window-main-msg-ready':['win','main','msg','readyEvent'],
 'message-main-window-directory':['msg','main','win','directoryEnd'],
 'main-event-dir-window':['main','readyEvent','directoryEnd','win'],
 'main-event-dir-window-msg':['main','readyEvent','directoryEnd','win','msg'],
}
start='int WINAPI GameApplicationRunF455('
def make(fields):
 src=base.replace(header,'struct NativeStartupScenePathF500 {GameScenesF455* currentScene; char path[260]; '+''.join(flags[f]+' '+f+'; ' for f in fields)+'};')
 pref,body=src.split(start,1);body=start+body
 for f in fields:
  body=re.sub(r'\b'+f+r'\b','context.'+f,body)
  if f=='main':
   assert body.count('HWND context.main=CreateWindowExA(')==1
   body=body.replace('HWND context.main=CreateWindowExA(','context.main=CreateWindowExA(')
  elif f=='readyEvent':
   assert body.count('    HANDLE context.readyEvent;')==1
   body=body.replace('    HANDLE context.readyEvent;\n','',1)
  elif f=='msg':
   assert body.count('          MSG context.msg;')==1
   body=body.replace('          MSG context.msg;\n','',1)
  elif f=='win':
   assert body.count('    WNDCLASSEXA context.win;')==1
   body=body.replace('    WNDCLASSEXA context.win;\n','',1)
  elif f=='directoryEnd':
   assert body.count('char* context.directoryEnd=strrchr(')==1
   body=body.replace('char* context.directoryEnd=strrchr(','context.directoryEnd=strrchr(')
  elif f in ('windowWidth','windowHeight'):
   assert body.count('int context.'+f+'=GetSystemMetrics(')==1
   body=body.replace('int context.'+f+'=GetSystemMetrics(','context.'+f+'=GetSystemMetrics(')
  assert body.count('context.'+f)>=2
 return pref+body
# Actual original HWND/main, Scene, path can be observed at adjacent
# EBP-188/-184/-180. Reordering ONLY genuine used context fields is
# a natural source hypothesis, not arbitrary gap bytes.
fields={'s':'GameScenesF455* currentScene;','p':'char path[260];',
        'w':'WNDCLASSEXA win;','m':'HWND main;'}
best_base=make(['win','main'])
old_head='struct NativeStartupScenePathF500 {GameScenesF455* currentScene; char path[260]; WNDCLASSEXA win; HWND main; };'
assert best_base.count(old_head)==1
for order in ['spwm','mspw','mwsp','wmsp','smpw','spmw','swmp','mswp','wsmp','wspm','smwp','wmps']:
 names=' '.join(fields[c] for c in order)
 variants['order-'+order]=best_base.replace(old_head,'struct NativeStartupScenePathF500 {'+names+' };')
# Disproven pack1 changes source syntax without recovering the original
# layout. Keep just two diagnostic controls instead of 12 duplicates.
for order in ('spwm','wmps'):
 source=variants['order-'+order]
 old_head='struct NativeStartupScenePathF500 {'+' '.join(fields[c] for c in order)+' };'
 assert source.count(old_head)==1
 variants['packed-'+order]=source.replace(old_head,
     '#pragma pack(push, 1)\n'+old_head+'\n#pragma pack(pop)')
assert len(variants)==26
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,fields in variants.items():
 source=fields if isinstance(fields,str) else make(fields);cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=220)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:print(tag,'COMPILE ERROR',(cp.stdout+cp.stderr)[-450:],flush=True);continue
 code,refs=rd.object_function(obj,f615.SYMBOL)
 ins=[]
 for i in d.disasm(code,0):
  ins.append(i)
  if i.mnemonic=='ret':break
 ret=ins[-1].address+ins[-1].size
 role=[7,9,10,12,14,17,26,54,60,75]
 assert len(ins)==654 and len(refs)==173 and len(code)-ret==60, tag+' whole WinMain CALL/scene table/ABI drift'
 row={'variant':tag,'source_CODE_B':ret,'original_CODE_B':2987,'source_x86':len(ins),
      'original_x86':654,'ref_fields':len(refs),'afterRET_data_B':len(code)-ret,
      'matching_mnemonics':sum(a.mnemonic==b.mnemonic for a,b in zip(n,ins)),
      'matching_x86_widths':sum(a.size==b.size for a,b in zip(n,ins)),
      'native_source_EBP_at_ordinals':[(j,ins[j].op_str) for j in (*role,55,114)],
      'real_native_scene_path_locations':ins[9].op_str=='dword ptr [ebp - 0x184], 0' and ins[17].op_str=='eax, [ebp - 0x180]'}
 assert row['matching_mnemonics']==654 and row['matching_x86_widths'] in (590,606,614,619,627), tag+' original x86 source geometry no longer bounded'
 if tag=='packed-spwm':
  old=next(r for r in rows if r['variant']=='order-spwm')
  assert all(row[k]==old[k] for k in ('source_CODE_B','matching_mnemonics','matching_x86_widths','native_source_EBP_at_ordinals'))
 if tag=='packed-wmps':
  old=next(r for r in rows if r['variant']=='order-wmps')
  assert all(row[k]==old[k] for k in ('source_CODE_B','matching_mnemonics','matching_x86_widths','native_source_EBP_at_ordinals'))
 rows.append(row)
 print(tag,'B',ret,'x86',len(ins),'widths',row['matching_x86_widths'],'scene',ins[9].op_str,'path',ins[17].op_str,'call_fields',len(refs),'postRET',len(code)-ret,flush=True)
assert len(rows)==26
assert not any(x['real_native_scene_path_locations'] for x in rows)
byname={r['variant']:r for r in rows}
assert byname['window-main-ready-directory']['native_source_EBP_at_ordinals'][1][1]=='dword ptr [ebp - 0x180], 0'
assert byname['order-wmps']['source_CODE_B']==2993 and byname['order-wmps']['matching_x86_widths']==590
(O/'verified-summary.json').write_text(json.dumps({
 'native_Japanese_original_address':'0x00602A60',
 'original_whole_CODE_B':2987,'original_whole_x86':654,
 'original_native_actual_CALL_instructions':123,
 'original_native_afterRET_scene_jump_DATA_B':60,
 'original_real_stack_graphics':'EBP-0x189','original_real_stack_main_HWND':'EBP-0x188',
 'original_real_stack_scene':'EBP-0x184','original_real_stack_path':'EBP-0x180',
 'original_real_stack_WindowClass':'EBP-0x30',
 'tested_complete_source_variants':len(rows),
 'all_original_654_Cpp_mnemonics_per_variant':True,
 'all_variants_have_173_source_only_COFF_fields':True,
 'no_original_full_2987B_exact_source_found':True,
 'no_source_matches_native_scene_and_path_EBP':True,
 'original_native_function_origin':'authored',
 'actual_source_results':rows,
 'official_game_exact_CODE_credit':0,
 'all_unit_cold_replay_run':False,
},indent=2)+'\n')
print('F795: 26 whole authored WinMain startup VC7.1 sources (genuine used window/scene/msg/handle field groupings); physically confirmed native graphics/main/scene/path 0x189/0x188/0x184/0x180, but none matches original full 2987B/654-x86 with correct EBP. No accepted CODE.',flush=True)
