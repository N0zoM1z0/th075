#!/usr/bin/env python3
"""Compare full original 654 x86 WinMain with F911 and F914 owners, no exact adoption."""
from pathlib import Path
import importlib.util,json,os,sys,subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]; O=R/'.analysis/f914-winmain-first-scene-proof';O.mkdir(parents=True,exist_ok=True)
spec=importlib.util.spec_from_file_location('rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
N=list(D.disasm(rd.pe_bytes_at(pe,0x602a60,2987),0x602a60))
assert len(N)==654 and N[2].op_str=='esp, 0x278'
original_stack={9:'dword ptr [ebp - 0x184], 0',17:'eax, [ebp - 0x180]',114:'dword ptr [ebp - 0x188], eax',281:'dword ptr [ebp - 0x19c], ecx'}
assert all(N[i].op_str==x for i,x in original_stack.items())
table=rd.pe_bytes_at(pe,0x60360b,60)
case_ord=[next(i for i,x in enumerate(N) if x.address==int.from_bytes(table[k*4:k*4+4],'little')) for k in range(15)]
assert case_ord==[383,399,415,431,367]+[447+16*i for i in range(10)]
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for tag,src in [('F911',R/'probes/WinMainNativeOwnerOrderF911.cpp'),('F914',R/'probes/WinMainNativeFirstSceneOwnerF914.cpp')]:
 obj=O/(tag+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,text=True,capture_output=True,timeout=300)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(I)==654 and len(refs)==173 and len(code)-end==60
 for k,r in enumerate(sorted((x for x in refs if x['offset']>=end),key=lambda x:x['offset'])):
  assert r['offset']==end+k*4 and r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset']==I[case_ord[k]].address
 for idx in [270]+[368+16*i for i in range(15)]:
  assert I[idx-1].op_str==N[idx-1].op_str
  cr=[x for x in refs if I[idx+6].address<=x['offset']<I[idx+6].address+I[idx+6].size]
  expected=4 if idx in (270,368) else ((idx-368)//16-1 if idx<448 else (idx-368)//16)
  assert len(cr)==1 and cr[0]['type']=='REL32' and cr[0]['addend']==0 and cr[0]['symbol']==f'??0Scene{expected}F455@@QAE@XZ'
 w=[i for i,(a,b) in enumerate(zip(N,I)) if a.size!=b.size]
 assert all(a.mnemonic==b.mnemonic for a,b in zip(N,I))
 rows[tag]={'generated_CODE_B':end,'native_matching_widths':654-len(w),'wrong_width_ordinals':w,
            'frame_matches_original':I[2].op_str==N[2].op_str,
            'actual_EBP_at_ordinals':{str(i):I[i].op_str for i in original_stack},
            'matched_native_hwnd_scene_path':sum(I[i].op_str==N[i].op_str for i in (9,17,114)),
            'native_15_afterRET_case_ordinal_refs_correct':True,
            'native_16_new_ctor_pairs_correct':True}
 print(tag,rows[tag],flush=True)
assert rows['F911']['generated_CODE_B']==2984 and rows['F911']['native_matching_widths']==645
assert rows['F914']['generated_CODE_B']==2978 and rows['F914']['native_matching_widths']==643
assert rows['F914']['frame_matches_original'] and rows['F914']['matched_native_hwnd_scene_path']==3
assert rows['F914']['wrong_width_ordinals']==[10,92,122,149,170,190,281,282,635,637,643]
assert rows['F914']['actual_EBP_at_ordinals']['281']=='dword ptr [ebp - 0x7c], ecx'
(O/'verified-summary.json').write_text(json.dumps({'original_WinMain':'0x00602A60','original_CODE_B':2987,
  'original_x86':654,'original_postRET_DATA_B':60,'whole_original_exact':False,
  'new_accepted_whole_CODE_B':0,'all_unit_cold_replay':False,'rows':rows},indent=2)+'\n')
print('F914 REAL whole WinMain native frame + main/scene/path slots found, but pointer temp still wrong. No exact whole credit.')
