#!/usr/bin/env python3
"""F1048 whole 248B scene destructor: genuine sequential texture/free lifetimes.

Try a real C++ union reusing the texture receiver storage after delete
for one of three actually freed scene resource pointers, with varied true
member declaration and nested lifetime. Cold-build the complete destructor,
never crop CODE, force registers, add dummy locals or count near matches.
"""
from pathlib import Path
import importlib.util,itertools,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1048-scene-reused-owner';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
STRUCT='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
TEX='''    if (FIELD(TextureManagerF200*,0x08))
        delete FIELD(TextureManagerF200*,0x08);'''
DECL='    CleanupPointersF215 released;'
assert all(base.count(k)==1 for k in (STRUCT,TEX,DECL))
FIELDS=['digitAtlas','firstCombo','secondCombo']
sp=importlib.util.spec_from_file_location('f1048rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f1048f589',R/'scripts/verify-scene-texture-delete-f589.py')
f589=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f589;sp.loader.exec_module(f589)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32);original=rd.pe_bytes_at(PE,0x43b0b0,248)
N=list(D.disasm(original,0x43b0b0));assert len(N)==75
assert [N[i].op_str for i in (26,28,42,52,62)]==[
'dword ptr [ebp - 0x14], edx','dword ptr [ebp - 0x10], eax','dword ptr [ebp - 0x18], eax','dword ptr [ebp - 0x1c], ecx','dword ptr [ebp - 0x20], edx']
MASK=set()
for off,(kind,target) in f589.ORIGINAL_COFF.items():
 val=int.from_bytes(original[off:off+4],'little',signed=kind=='REL32')
 assert (0x43b0b0+off+4+val if kind=='REL32' else val)==target
 MASK.update(range(off,off+4))
assert len(MASK)==48
cases={'original-natural-baseline':base}
for shared in FIELDS:
 for position in ('first','middle','last'):
  for scope in ('function-entry','before-clock','before-texture'):
   remaining=[s for s in FIELDS if s!=shared]
   fields=['union { TextureManagerF200* texture; void* '+shared+'; } sharedValue;']
   members=['void* '+i+';' for i in remaining]
   if position=='first':fields+=members
   elif position=='middle':fields=[members[0],fields[0],members[1]]
   else:fields=members+fields
   SRC='struct CleanupReuseF1048 {\n'+''.join('    '+x+'\n' for x in fields)+'};'
   src=base.replace(STRUCT,SRC,1).replace(DECL,'',1)
   # Real C++ auto lifetime; the shared union is overwritten only after
   # the texture has already been deleted (no simultaneous active use).
   NEWTEX='''    if (FIELD(TextureManagerF200*,0x08)) {
        released.sharedValue.texture = FIELD(TextureManagerF200*,0x08);
        delete released.sharedValue.texture;
    }'''
   assert src.count(TEX)==1
   src=src.replace(TEX,NEWTEX,1)
   for field in FIELDS:
    old='released.'+field
    assert src.count(old)==2,old
    src=src.replace(old,'released.sharedValue.'+shared if field==shared else 'released.'+field)
   anchor={'function-entry':'BattleSceneF200::~BattleSceneF200()\n{',
           'before-clock':'    if (g_FrameClockModeAt0066C238 == 2 || 4)',
           'before-texture':NEWTEX}[scope]
   assert src.count(anchor)==1
   if scope=='function-entry':src=src.replace(anchor,anchor+'\n    CleanupReuseF1048 released;',1)
   else:src=src.replace(anchor,'    CleanupReuseF1048 released;\n'+anchor,1)
   assert src.count('free(')==3 and src.count('delete released.sharedValue.texture')==1
   cases[shared+'-'+position+'-'+scope]=src
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[];base_symbols=None
for name,src in cases.items():
 cpp=O/(name+'.cpp');obj=O/(name+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=E,text=True,capture_output=True,timeout=345)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  rows.append({'variant':name,'compile_error':(cp.stdout+cp.stderr)[-750:]})
  print(name,'compiler failure',(cp.stdout+cp.stderr)[-250:],flush=True)
  continue
 code,refs=rd.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
 ins=list(D.disasm(code,0))
 symbols=sorted((r['type'],r['symbol'],r['addend']) for r in refs)
 if base_symbols is None:base_symbols=symbols
 row={'variant':name,'source_whole_CODE_B':len(code),'source_whole_x86':len(ins),
      'original_whole_CODE_B':248,'original_whole_x86':75,
      'source_real_COFF_fields':len(refs),'same_original_calls_global_EH_symbols':base_symbols==symbols,
      'exact_original_whole':False}
 if len(ins)>62:row['real_used_source_EBP_roles_at_original_ordinals']=[ins[i].op_str for i in (26,28,42,52,62)]
 if len(code)==248 and len(ins)==75 and len(refs)==12:
  aligned=sorted((r['offset'],r['type']) for r in refs)==sorted((off,k) for off,(k,target) in f589.ORIGINAL_COFF.items())
  row['all_12_original_physical_PE_fields']=(aligned and all(r['addend']==0 and r['local_symbol_offset'] is None for r in refs if r['type']=='REL32'))
  if row['all_12_original_physical_PE_fields']:
   assert all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(N,ins))
   wrong=[j for j in range(248) if j not in MASK and code[j]!=original[j]]
   row['real_original_nonfield_equal_B']=200-len(wrong)
   row['real_nonfield_wrong_offsets']=wrong
   row['exact_original_whole']=len(wrong)==0
 rows.append(row)
 print(name,'whole',len(code),len(ins),'native original comparable',row.get('real_original_nonfield_equal_B'),
       'original calls',row['same_original_calls_global_EH_symbols'],flush=True)
(O/'verified-summary.json').write_text(json.dumps({
 'original_248B_authored_scene_virtual_destructor':'0x0043B0B0',
 'original_whole_CODE_B':248,'original_x86':75,
 'original_12_physical_PE_fields_checked':True,'full_natural_source_variants':len(cases),
 'new_exact_original_GAME_CODE_B':0,'mass_cold_replay':False,
 'trial_results':rows},indent=2)+'\n')
assert len(rows)==28 and all('compile_error' not in row for row in rows)
assert rows[0]['real_original_nonfield_equal_B']==191
print('F1048 tested',len(rows),'complete original-shaped Scene destructor VC7.1 sources; no acceptance assumed. Inspect source/native stack results.')
