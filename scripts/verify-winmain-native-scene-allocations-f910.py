#!/usr/bin/env python3
"""F910: recover original case4-first WinMain switch physical source order.

Read original Japanese PE every run. Compile TWO complete source TUs
serially, the prior numeric-order /GX- F904 best and corrected tracked F910
case4-first whole source. Verify all native operator-new sizes, sixteen
constructors, the physical order and relocations of all fifteen afterRET
switch destinations, and whole x86 geometry. No exact acceptance.
"""
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import importlib.util, json, os, re, subprocess, sys

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f910-winmain-native-scenes'
O.mkdir(parents=True,exist_ok=True)
SOURCE=R/'probes/WinMainNativeSceneAllocationsF910.cpp'
BASELINE=R/'.analysis/f904-winmain-staged-owners/group-sceneState-previousState.cpp'
assert SOURCE.is_file() and BASELINE.is_file()
spec=importlib.util.spec_from_file_location('f910rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
pe=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
N=list(D.disasm(rd.pe_bytes_at(pe,0x602a60,2987),0x602a60))
assert len(N)==654 and N[-1].mnemonic=='ret' and N[-1].op_str=='0x10'
orig_table=rd.pe_bytes_at(pe,0x60360b,60)
assert len(orig_table)==60
original_cases=[int.from_bytes(orig_table[i*4:i*4+4],'little') for i in range(15)]
# Verify the ORIGINAL afterRET jump table's case handler indices;
# never infer which scene constructor is called from source labels.
original_case_ordinals=[next(i for i,n in enumerate(N)
                             if n.address==physical) for physical in original_cases]
assert original_case_ordinals==[383,399,415,431,367]+[447+16*i for i in range(10)]
native_allocations=[i for i,n in enumerate(N) if n.mnemonic=='call' and n.op_str=='0x64159d' and i>210]
assert native_allocations==[270]+[368+16*i for i in range(15)]
# First scene (logo) and physically FIRST case are both state 4.
# Original table maps numeric states 0-3 to the NEXT four physical
# blocks and maps state 4 back to the first. Then cases 5-14 follow.
expected_source_scene_indices=[4,4,0,1,2,3]+list(range(5,15))
# Original pairs are defined by actual PE new/call/whole table,
# not by the older prose or mistaken source class-size map.
native_pairs=[]
for ordinal,scene in zip(native_allocations,expected_source_scene_indices):
    before,ctor=N[ordinal-1],N[ordinal+6]
    assert before.mnemonic=='push' and ctor.mnemonic=='call'
    size=int(before.op_str,0);target=int(ctor.op_str,0)
    assert 0x420000<=target<0x450000
    native_pairs.append({'ordinal':ordinal,
      'scene_index':scene, 'original_PE_new_size':size,
      'original_PE_ctor_target':f'0x{target:08X}',
      'initial_scene_before_switch':ordinal==270})
assert native_pairs[0]['original_PE_new_size']==native_pairs[1]['original_PE_new_size']==16
assert native_pairs[0]['original_PE_ctor_target']==native_pairs[1]['original_PE_ctor_target']
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
def compile_source(name,src):
    obj=O/(name+'.obj')
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
      cwd=R,env=E,capture_output=True,text=True,timeout=340)
    (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
    assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
    code,refs=rd.object_function(obj,'?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z')
    I=[]
    for x in D.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    size=I[-1].address+I[-1].size
    assert len(I)==654 and len(refs)==173 and len(code)-size==60
    return I,refs,size
rows={}
for name,src in [('older-F904',BASELINE),('corrected-F910',SOURCE)]:
    I,refs,size=compile_source(name,src)
    table_refs=sorted((r for r in refs if r['offset']>=size),key=lambda r:r['offset'])
    assert len(table_refs)==15
    # Check actual source jump-table target ordinal and compare the
    # mapped case-index-to-physical-order permutation with the native PE.
    physical_source_order=(original_case_ordinals if name=='corrected-F910'
                           else [367+16*i for i in range(15)])
    table_equal=0
    for i,r in enumerate(table_refs):
        assert r['offset']==size+i*4 and r['type']=='DIR32' and r['addend']==0
        assert r['local_symbol_offset']==I[physical_source_order[i]].address
        table_equal+=physical_source_order[i]==original_case_ordinals[i]
    seen=[]
    for native in native_pairs:
        idx=native['ordinal'];scene=native['scene_index']
        assert I[idx-1].mnemonic=='push' and I[idx+6].mnemonic=='call'
        refs_for_call=[r for r in refs if I[idx+6].address<=r['offset']<I[idx+6].address+I[idx+6].size]
        assert len(refs_for_call)==1
        ref=refs_for_call[0]
        assert ref['type']=='REL32' and ref['addend']==0 and ref['local_symbol_offset'] is None
        symbol=ref['symbol']
        oldscene=4 if idx==270 else (idx-368)//16
        expected_class=scene if name=='corrected-F910' else oldscene
        assert symbol==f'??0Scene{expected_class}F455@@QAE@XZ', (name,idx,symbol,expected_class)
        seen.append({'scene_index':scene,
          'initial_scene':idx==270,'original_new_size':native['original_PE_new_size'],
          'source_new_size':int(I[idx-1].op_str,0),
          'same_native_allocation_size':int(I[idx-1].op_str,0)==native['original_PE_new_size'],
          'same_original_constructor_index':expected_class==scene,
          'source_constructor':symbol,
          'original_ctor_target':native['original_PE_ctor_target']})
    rows[name]={'whole_source_CODE_B':size,'whole_x86':len(I),
      'native_mnemonic_matches':sum(x.mnemonic==y.mnemonic for x,y in zip(N,I)),
      'native_x86_width_matches':sum(x.size==y.size for x,y in zip(N,I)),
      'whole_coff_records':len(refs),'original_afterRET_scene_table_B':len(orig_table),
      'source_afterRET_scene_table_B':60,'original_15_table_destinations_match_source_case_ordinals':table_equal,
      'correct_native_new_size_count':sum(x['same_native_allocation_size'] for x in seen),
      'correct_native_constructor_index_count':sum(x['same_original_constructor_index'] for x in seen),
      'initial_original_logo_scene_constructor_correct':
             seen[0]['source_constructor']=='??0Scene4F455@@QAE@XZ',
      'native_pairs':seen}
    print(name,'whole CODE',size,'x86',len(I),'original width matches',
          rows[name]['native_x86_width_matches'],'original real allocation sizes',
          rows[name]['correct_native_new_size_count'],'of 16',flush=True)
old,new=rows['older-F904'],rows['corrected-F910']
assert old['whole_source_CODE_B']==new['whole_source_CODE_B']==2960
assert old['native_x86_width_matches']==633
assert new['native_x86_width_matches']==637
assert old['correct_native_new_size_count']==11
assert new['correct_native_new_size_count']==16
assert old['native_mnemonic_matches']==new['native_mnemonic_matches']==654
assert old['initial_original_logo_scene_constructor_correct']
assert new['initial_original_logo_scene_constructor_correct']
assert old['correct_native_constructor_index_count']==11
assert new['correct_native_constructor_index_count']==16
assert old['original_15_table_destinations_match_source_case_ordinals']==10
assert new['original_15_table_destinations_match_source_case_ordinals']==15
assert all(x['same_native_allocation_size'] for x in new['native_pairs'])
# Both correct source and old are still whole NONEXACT:
# original source is 2987 CODE B, compiler emits 2960.
receipt={'original_source':'Japanese TH075 v1.11 SHA-pinned PE',
 'native_original_WinMain':'0x00602A60',
 'native_original_whole_callable_CODE_B':2987,'native_original_whole_x86':654,
 'native_original_afterRET_dispatch_table':'0x0060360B',
 'real_original_initial_and_15_scene_new_call_pairs':native_pairs,
 'real_original_15_scene_afterRET_targets':[f'0x{x:08X}' for x in original_cases],
 'whole_original_exact':False,'new_accepted_callable_CODE_B':0,
 'whole_979_unit_cold_replay':False,'complete_source_profiles':rows}
(O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
print('F910 verified native switch index 4 maps to first physical case; relocated case4 first in ordinary whole C++. All 16 native constructor/size pairs and 15 PE-vs-COFF table destinations now align; 633 -> 637 native x86 widths, 2960B source != native 2987B, NONEXACT.')
