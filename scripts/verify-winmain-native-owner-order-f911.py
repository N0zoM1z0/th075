#!/usr/bin/env python3
"""F911: original WinMain whole native owner order at all 654 x86 positions.

Reproduce F910 full original WinMain and corrected main/scene/path
real source layout. Check entire normal VC7.1 emitted function, original
native mnemonic and instruction widths, phys original stack owner
roles, all 16 constructor sizes, and all 15 switch jump-table
index-to-ordinal DIR32 relocation targets. No exact claim.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import json,importlib.util,os,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f911-winmain-real-owner-order-replay'
O.mkdir(parents=True,exist_ok=True)
A=R/'probes/WinMainNativeSceneAllocationsF910.cpp'
B=R/'probes/WinMainNativeOwnerOrderF911.cpp'
assert A.is_file() and B.is_file()
assert 'HWND main; GameScenesF455* currentScene; char path[260];' in B.read_text()
s=importlib.util.spec_from_file_location('f911rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(s);sys.modules[s.name]=rd;s.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32); pe=rd.verified_target()
original=list(D.disasm(rd.pe_bytes_at(pe,0x602a60,2987),0x602a60))
assert len(original)==654 and original[-1].mnemonic=='ret'
original_data=rd.pe_bytes_at(pe,0x60360b,60)
native_cases=[int.from_bytes(original_data[i*4:i*4+4],'little') for i in range(15)]
original_case_ord=[next(j for j,n in enumerate(original) if n.address==t) for t in native_cases]
assert original_case_ord==[383,399,415,431,367]+[447+16*i for i in range(10)]
newcalls=[270]+[368+16*i for i in range(15)]
assert all(original[i].op_str=='0x64159d' and original[i].mnemonic=='call' for i in newcalls)
E=os.environ.copy(); E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in [('F910',A),('F911',B)]:
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
    cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
 code,refs=rd.object_function(obj,'?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z')
 I=[]
 for ins in D.disasm(code,0):
    I.append(ins)
    if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(I)==654 and len(refs)==173 and len(code)-end==60
 badwidth=[i for i,(a,b) in enumerate(zip(original,I)) if a.size!=b.size]
 badmnem=[i for i,(a,b) in enumerate(zip(original,I)) if a.mnemonic!=b.mnemonic]
 assert not badmnem
 casefields=[r for r in refs if r['offset']>=end]
 assert len(casefields)==15
 for i,r in enumerate(sorted(casefields,key=lambda r:r['offset'])):
    assert r['offset']==end+i*4 and r['type']=='DIR32' and r['addend']==0
    assert r['local_symbol_offset']==I[original_case_ord[i]].address
 ctorpairs=[]
 for idx in newcalls:
    assert original[idx-1].mnemonic=='push' and I[idx-1].mnemonic=='push'
    assert I[idx-1].op_str==original[idx-1].op_str
    ctorref=[r for r in refs if I[idx+6].address<=r['offset']<I[idx+6].address+I[idx+6].size]
    assert len(ctorref)==1 and ctorref[0]['type']=='REL32' and ctorref[0]['addend']==0
    native_ctor=int(original[idx+6].op_str,0)
    expected_class=(4 if idx in (270,368) else (idx-368)//16-1 if idx<448 else (idx-368)//16)
    assert ctorref[0]['symbol']==f'??0Scene{expected_class}F455@@QAE@XZ'
    ctorpairs.append({'original_CODE_ordinal':idx,
                      'physical_new_size':int(original[idx-1].op_str,0),
                      'source_new_size':int(I[idx-1].op_str,0),
                      'original_ctor':hex(native_ctor),
                      'source_ctor':ctorref[0]['symbol']})
 row={'source':str(cpp.relative_to(R)),'whole_CODE_B':end,
      'native_whole_CODE_B':2987,'x86':len(I),
      'native_matching_mnemonics':654,
      'native_matching_widths':654-len(badwidth),
      'native_wrong_width_ordinals':badwidth,
      'new_allocation_sizes_physically_correct':len(ctorpairs),
      'original_original_scene_jump_table_cases_with_matching_ordinal':len(casefields),
      'real_main_EBP':I[114].op_str,'original_main_EBP':original[114].op_str,
      'real_currentScene_EBP':I[9].op_str,'original_currentScene_EBP':original[9].op_str,
      'real_path_EBP':I[17].op_str,'original_path_EBP':original[17].op_str,
      'original_graphics_EBP':original[10].op_str,'source_graphics_EBP':I[10].op_str,
      'original_afterRET_DATA_B':len(original_data),
      'source_afterRET_DATA_B':len(code)-end,
      'real_physical_constructor_pairs':ctorpairs}
 rows[label]=row
 print(label,json.dumps({k:v for k,v in row.items()
             if k not in ('real_physical_constructor_pairs','source')},ensure_ascii=False),flush=True)
assert rows['F910']['whole_CODE_B']==2960
assert rows['F911']['whole_CODE_B']==2984
assert rows['F910']['native_matching_widths']==637
assert rows['F911']['native_matching_widths']==645
assert rows['F910']['real_main_EBP']=='dword ptr [ebp - 0x48], eax'
assert rows['F911']['real_main_EBP']=='dword ptr [ebp - 0x180], eax'
assert rows['F911']['native_wrong_width_ordinals']==[10,92,122,149,170,190,635,637,643]
assert rows['F911']['real_currentScene_EBP']!=rows['F911']['original_currentScene_EBP']
assert all(row['new_allocation_sizes_physically_correct']==16 and
           row['original_original_scene_jump_table_cases_with_matching_ordinal']==15
           for row in rows.values())
receipt={'original':'Japanese TH075 1.11 original SHA-pinned PE',
 'original_whole_WinMain':'0x00602A60','whole_original_CODE_B':2987,
 'original_x86':654,'native_afterRET_table':'0x0060360B',
 'F911_32_other_real_owner_layout_source_variants_saved_ignored':True,
 'whole_original_exact':False,'accepted_new_whole_game_CODE_B':0,
 'all_979_existing_units_cold_replayed':False,
 'profiles':rows}
(O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
print('F911 original whole WinMain: real main-before-scene owner improves source 2960->2984 CODE B and native widths 637->645/654; 16 original alloc+ctor sites and 15 native switch targets preserved. Still 9 wrong widths and nonexact whole 2987B.')
