#!/usr/bin/env python3
"""F1015 pinned original 248B Scene virtual destructor: true three-pointer
aggregate declaration site and member order controls.

Fresh original Japanese PE, all 75 real native x86, every physical
type/target for 12 true PE/COFF fields (including EH), actual CRT
three free pointers and virtual base destroy, 13 full natural
VC7.1 /GX builds. No false native full CODE acceptance or mass
979-unit replay. Preserve observed original EH stack slots.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1015-scene-slot-rotation'
base=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
DECL='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
LOC='    CleanupPointersF215 released;'
TEXTURE='    if (FIELD(TextureManagerF200*,0x08))'
CLOCK='    if (g_FrameClockModeAt0066C238 == 2 || 4)'
START='BattleSceneF200::~BattleSceneF200()\n{'
assert all(base.count(x)==1 for x in (DECL,LOC,TEXTURE,CLOCK,START))
perms=[
 ('natural','digitAtlas','firstCombo','secondCombo'),
 ('reversed','secondCombo','firstCombo','digitAtlas'),
 ('rotated-1','firstCombo','secondCombo','digitAtlas'),
 ('rotated-2','secondCombo','digitAtlas','firstCombo'),
]
cases={'baseline':base}
for tag,*fields in perms:
 d='struct CleanupPointersF215 {\n'+''.join('    void* '+f+';\n' for f in fields)+'};'
 s=base.replace(DECL,d,1).replace(LOC,'',1)
 for loc,target in [('function-start',START),('before-clock',CLOCK),('before-texture',TEXTURE)]:
  if loc=='function-start':
   t=s.replace(START,START+'\n'+LOC,1)
  else:t=s.replace(target,LOC+'\n'+target,1)
  cases[tag+'-'+loc]=t
sp=importlib.util.spec_from_file_location('rd_f1015',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f589_f1015',R/'scripts/verify-scene-texture-delete-f589.py')
f589=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f589;sp.loader.exec_module(f589)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
raw=rd.pe_bytes_at(PE,0x43b0b0,248)
N=list(D.disasm(raw,0x43b0b0))
assert len(N)==75
masked=set()
for pos,(kind,target) in f589.ORIGINAL_COFF.items():
 x=int.from_bytes(raw[pos:pos+4],'little',signed=kind=='REL32')
 true=0x43b0b0+pos+4+x if kind=='REL32' else x
 assert true==target
 masked.update(range(pos,pos+4))
assert len(masked)==48
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
ref_symbols=None
for tag,src in cases.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print('COMPILE FAILURE',tag,(cp.stdout+cp.stderr)[-450:],flush=True)
  rows.append({'variant':tag,'compiler_failure':(cp.stdout+cp.stderr)[-650:]});continue
 code,refs=rd.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
 S=list(D.disasm(code,0))
 row={'variant':tag,'compiled_CODE_B':len(code),'compiled_x86':len(S),
      'original_CODE_B':248,'original_x86':75,'original_exact':False}
 if len(code)==248 and len(S)==75 and len(refs)==12:
  assert sorted((r['offset'],r['type']) for r in refs)==sorted((off,k) for off,(k,t) in f589.ORIGINAL_COFF.items())
  assert all(r['addend']==0 and r['local_symbol_offset'] is None for r in refs)
  symbols=sorted((r['type'],r['symbol'],r['addend']) for r in refs)
  if ref_symbols is None:ref_symbols=symbols
  assert symbols==ref_symbols
  assert all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(N,S))
  diff=[i for i in range(248) if i not in masked and code[i]!=raw[i]]
  row.update({'nonfield_equal_B':200-len(diff),'nonfield_wrong_indices':diff,
   'native_mnemonic_count':sum(x.mnemonic==y.mnemonic for x,y in zip(N,S)),
   'native_width_count':sum(x.size==y.size for x,y in zip(N,S)),
   'observed_native_EBP_roles':{str(j):S[j].op_str for j in (26,28,42,52,62)},
   'original_exact':len(diff)==0})
 rows.append(row)
 print(tag,'CODE/x86',len(code),len(S),'nonfield equal',row.get('nonfield_equal_B'),
       'actual local EBP',row.get('observed_native_EBP_roles'),
       'original exact',row['original_exact'],flush=True)
(O/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
assert len(rows)==13 and all('compiler_failure' not in r for r in rows)
assert all((r['compiled_CODE_B'],r['compiled_x86'],r['native_mnemonic_count'],
            r['native_width_count'])==(248,75,75,75) for r in rows)
assert [r['nonfield_equal_B'] for r in rows]==[191]*4+[189]*9
assert all(r['observed_native_EBP_roles']['26']=='dword ptr [ebp - 0x20], edx'
           and r['observed_native_EBP_roles']['28']=='dword ptr [ebp - 0x1c], eax'
           and r['original_exact'] is False for r in rows)
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_game_Scene_destructor':'0x0043B0B0',
 'original_whole_callable_CODE_B':248,'original_x86':75,
 'original_typed_PE_fields':12,'genuine_full_Cpp_variants':13,
 'original_texture_EBP':['-0x14','-0x10'],
 'candidate_texture_EBP':['-0x20','-0x1C'],
 'real_grouped_three_free_pointer_declaration_sites':['function','before-clock','before-texture'],
 'real_used_member_order_variations':4,
 'native_nonfield_best':'191/200',
 'native_nonfield_reversed_or_rotated':'189/200',
 'new_exact_complete_original_GAME_CODE_B':0,
 'original_whole_exact':False,'mass_cold_replay':False,
 'whole_native_Cpp_profiles':rows
},indent=2)+'\n')
print('F1015 13 genuine complete normal VC7.1 248B/75-x86 Scene destructor sources, all 12 original PE fields, at most 191/200 native nonrelocation bytes. Original texture-delete EBP not repaired, ZERO new accepted GAME CODE.')
