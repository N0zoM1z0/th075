"""F848: actual 248B Scene destructor real pointer member access source profiles.

Complete pinned VC7.1 normal /GX original game destructor, ten real
source forms: aggregate getters/setters, volatile/register, pointer-to-
member and pointer access. Check all physically typed original 12 PE
calls/globals on ALL five complete 248B/75 x86 variants. Under /Ob0,
__forceinline source member helpers still emit additional real code,
253..281B /76..84x86, never cropped or counted exact.
No accepted-unit mass cold replay.
"""
from pathlib import Path
import os,subprocess,sys,importlib.util,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f848-scene-real-owner-access';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
definition='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
assert base.count(definition)==1
names=('digitAtlas','firstCombo','secondCombo')
cases={'baseline':base}
def with_methods(setters=False,getters=False,all_three=True):
 s=base
 members=list(names if all_three else names[:1])
 fun=[]
 for i,name in enumerate(members):
  if setters:fun.append(f'    __forceinline void set{i}(void* value) {{ {name}=value; }}')
  if getters:fun.append(f'    __forceinline void* get{i}() {{ return {name}; }}')
 if fun:
  s=s.replace(definition,definition.replace('};','\n'.join(fun)+'\n};'),1)
 for i,name in enumerate(members):
  if setters:s=s.replace(f'released.{name} = FIELD(void*,0x{(0x4c+4*i):x});',f'released.set{i}(FIELD(void*,0x{(0x4c+4*i):x}));',1)
  if getters:s=s.replace(f'free(released.{name});',f'free(released.get{i}());',1)
 return s
cases['setter-only-first']=with_methods(setters=True,all_three=False)
cases['getter-only-first']=with_methods(getters=True,all_three=False)
cases['all-setters']=with_methods(setters=True)
cases['all-getters']=with_methods(getters=True)
cases['both-setters-getters']=with_methods(setters=True,getters=True)
cases['volatile-aggregate']=base.replace('    CleanupPointersF215 released;','    volatile CleanupPointersF215 released;',1)
cases['register-aggregate']=base.replace('    CleanupPointersF215 released;','    register CleanupPointersF215 released;',1)
cases['address-of-aggregate']=base
for name in names:
 cases['address-of-aggregate']=cases['address-of-aggregate'].replace(f'released.{name}',f'(&released)->{name}')
cases['pointer-to-member']=base
for name in names:
 cases['pointer-to-member']=cases['pointer-to-member'].replace(f'released.{name}',f'(released.*(&CleanupPointersF215::{name}))')
sp=importlib.util.spec_from_file_location('f848rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f848f589',R/'scripts/verify-scene-texture-delete-f589.py');f589=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f589;sp.loader.exec_module(f589)
n=rd.pe_bytes_at(rd.verified_target(),0x43b0b0,248);D=Cs(CS_ARCH_X86,CS_MODE_32);orig=list(D.disasm(n,0x43b0b0))
assert len(orig)==75 and sum(x.size for x in orig)==248 and orig[-1].mnemonic=='ret'
assert tuple(orig[j].op_str for j in (26,28,42,52,62))==(
 'dword ptr [ebp - 0x14], edx',
 'dword ptr [ebp - 0x10], eax',
 'dword ptr [ebp - 0x18], eax',
 'dword ptr [ebp - 0x1c], ecx',
 'dword ptr [ebp - 0x20], edx')
assert len(f589.ORIGINAL_COFF)==12

E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results=[]
for label,src in cases.items():
 cpp=O/(label+'.cpp');obj=O/(label+'.obj');cpp.write_text(src)
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=215)
 (O/(label+'.log')).write_text(p.stdout+p.stderr)
 if p.returncode:
  print(label,'COMPILE FAILED',(p.stdout+p.stderr)[-420:].replace('\n',' '),flush=True)
  results.append({'source':label,'compile_failed':True});continue
 code,refs=rd.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
 ins=list(D.disasm(code,0))
 row={'source':label,'full_CODE_B':len(code),'whole_x86':len(ins),'COFF_fields':len(refs)}
 if len(code)==248 and len(ins)==75 and len(refs)==12:
  mask=set()
  check=True
  for r in refs:
   off=r['offset'];wanted=f589.ORIGINAL_COFF.get(off)
   if not wanted:check=False;continue
   typ,dest=wanted
   current=int.from_bytes(n[off:off+4],'little') if typ=='DIR32' else 0x43b0b0+off+4+int.from_bytes(n[off:off+4],'little',signed=True)
   if r['type']!=typ or r['addend']!=0 or current!=dest:check=False
   mask.update(range(off,off+4))
  wrong=[j for j in range(248) if j not in mask and n[j]!=code[j]]
  assert check and len(mask)==48 and len(wrong)==9, 'physical native 12 fields or 9 EBP operand bytes changed '+label
  assert all(orig[j].mnemonic==ins[j].mnemonic and orig[j].size==ins[j].size for j in range(75))
  row['original_all_12_PE_fields_correct']=check
  row['native_nonfield_matched']=248-len(mask)-len(wrong)
  row['native_nonfield_total']=248-len(mask)
  row['wrong_byte_offsets']=wrong
  row['source_five_temp_slots']=[ins[j].op_str for j in (26,28,42,52,62)]
 results.append(row)
 print(json.dumps(row),flush=True)
(O/'explore-summary.json').write_text(json.dumps(results,indent=2)+'\n')

assert len(results)==10, 'all ten genuine original destructor source profiles required'
same=[r for r in results if r.get('full_CODE_B')==248]
extended=[r for r in results if r.get('full_CODE_B')!=248]
assert len(same)==5 and len(extended)==5
assert all(r['whole_x86']==75 and r['COFF_fields']==12
           and r['native_nonfield_matched']==191 for r in same)
assert sorted(r['full_CODE_B'] for r in extended)==[253,254,263,266,281]
assert sorted(r['whole_x86'] for r in extended)==[76,77,78,81,84]
assert sorted(r['COFF_fields'] for r in extended)==[13,13,15,15,18]
(O/'verified-summary.json').write_text(json.dumps({
 'original_whole_function':'0x0043B0B0',
 'native_original_entire_CODE_B':248,
 'native_original_entire_x86':75,
 'native_original_physical_typed_PE_fields':12,
 'actual_meaningful_source_profiles':10,
 'whole_native_248B_variant_count':5,
 'unchanged_native_nonrelocation_matching_bytes':'191/200',
 'true_original_texture_delete_slots':['-0x14','-0x10'],
 'source_texture_delete_slots':['-0x20','-0x1C'],
 'actual_resource_owner_member_helpers_emit_additional_CODE_under_Ob0':True,
 'source_non_native_entire_CODE_lengths':[253,254,263,266,281],
 'whole_original_function_exact':False,
 'new_accepted_authored_whole_CODE_B':0,
 'all_unit_cold_replay':False,
 'variants':results,
},indent=2)+'\n')
print('F848 original Scene: 10 complete meaningful VC7.1 /GX resource-owner access sources. Five whole 248B/75-x86/12-physical-original-field sources only 191/200 nonrelocation bytes; five actual __forceinline getter/setter sources emit nonnative 253/254/263/266/281B. Native five temp-slot allocation remains NONEXACT.')
