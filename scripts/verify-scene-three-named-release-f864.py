"""F864: twelve COMPLETE original Scene destructor real named free-pointer sources.

Normal pinned VC7.1 /Od /GX virtual destructor 248B/75-x86/12
physical PE fields. Use actual freed pointer values from +4C,+50,+54,
with true independent named locals instead of earlier aggregate.
Test declaration order/time, register/volatile and actual in-branch
references. All 10 original-sized whole variants still mismatch
native temp stack slots, named ones 189/200 nonfield vs baseline
191/200; two real pointer/reference variants produce 254B/78x86.
No padding locals or false whole CODE exact credit.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f864-scene-named-release-slots';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
old='    CleanupPointersF215 released;\n'
assert base.count(old)==1
names={'released.digitAtlas':'digitAtlas','released.firstCombo':'firstCombo','released.secondCombo':'secondCombo'}
def named(s,declare='    void* digitAtlas;\n    void* firstCombo;\n    void* secondCombo;\n',anchor='    if (FIELD(void*,0x4c)) {'):
 assert s.count(old)==1 and s.count(anchor)==1
 s=s.replace(old,'',1)
 for a,b in names.items():s=s.replace(a,b)
 return s.replace(anchor,declare+anchor,1)
variants={'baseline':base}
decl='    void* digitAtlas;\n    void* firstCombo;\n    void* secondCombo;\n'
variants['three-named-after-texture']=named(base)
variants['three-named-before-texture']=named(base,anchor='    if (FIELD(TextureManagerF200*,0x08))')
variants['three-named-before-clock']=named(base,anchor='    if (g_FrameClockModeAt0066C238 == 2 || 4)')
variants['three-named-reversed']=named(base,declare='    void* secondCombo;\n    void* firstCombo;\n    void* digitAtlas;\n')
variants['three-named-rotate']=named(base,declare='    void* firstCombo;\n    void* secondCombo;\n    void* digitAtlas;\n')
variants['three-register']=named(base,declare='    register void* digitAtlas;\n    register void* firstCombo;\n    register void* secondCombo;\n')
variants['three-volatile']=named(base,declare='    void* volatile digitAtlas;\n    void* volatile firstCombo;\n    void* volatile secondCombo;\n')
variants['three-named-top-reversed']=named(base,declare='    void* secondCombo;\n    void* firstCombo;\n    void* digitAtlas;\n',anchor='    if (g_FrameClockModeAt0066C238 == 2 || 4)')
# Source branch scoped pointers initialized from their actual real
# memory owners before free, no inert variables.
s=base.replace(old,'')
for a,b in names.items():s=s.replace(f'        {a} = FIELD(void*,0x',f'        void* {b} = FIELD(void*,0x')
for a,b in names.items():s=s.replace(a,b)
variants['three-branch-named-inits']=s
# Each resource is an actually used reference to native pointer member.
s=base.replace(old,'')
for a,b in names.items():
 s=s.replace(f'        {a} = FIELD(void*,0x',f'        void*& {b} = FIELD(void*,0x')
for a,b in names.items():s=s.replace(a,b)
variants['three-branch-references']=s
# Each resource is a real pointer into the actually freed resource
# member; use it at free, no fake locals or dummy members.
s=base.replace(old,'')
for i,(a,b) in enumerate(names.items()):
 s=s.replace(f'        {a} = FIELD(void*,0x{0x4c+i*4:x});',
             f'        void** {b} = &FIELD(void*,0x{0x4c+i*4:x});')
 s=s.replace(f'free({a});',f'free(*{b});')
variants['three-branch-member-pointers']=s
sp=importlib.util.spec_from_file_location('rd864',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f589_864',R/'scripts/verify-scene-texture-delete-f589.py');f589=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f589;sp.loader.exec_module(f589)
pe=rd.verified_target();raw=rd.pe_bytes_at(pe,0x43b0b0,248);d=Cs(CS_ARCH_X86,CS_MODE_32);orig=list(d.disasm(raw,0x43b0b0));assert len(orig)==75 and len(raw)==248
assert [orig[j].op_str for j in (26,28,42,52,62)]==[
 'dword ptr [ebp - 0x14], edx',
 'dword ptr [ebp - 0x10], eax',
 'dword ptr [ebp - 0x18], eax',
 'dword ptr [ebp - 0x1c], ecx',
 'dword ptr [ebp - 0x20], edx']
assert len(f589.ORIGINAL_COFF)==12

E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
baseline_semantics=None
for tag,s in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(s)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=250)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':tag,'compiler_failure':(cp.stdout+cp.stderr)[-490:]}
  rows.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
 ins=list(d.disasm(code,0))
 assert len(refs)==12 and all(r['addend']==0 for r in refs)
 symbols=sorted((r['type'],r['symbol'],r['addend']) for r in refs)
 if tag=='baseline':baseline_semantics=symbols
 assert symbols==baseline_semantics, 'actual game native Delete/Free/base dtor call category changed '+tag
 row={'variant':tag,'whole_source_CODE_B':len(code),'x86':len(ins),'COFF_fields':len(refs)}
 if len(ins)>62:
  row['observed_five_source_EBP_roles']=[ins[j].op_str for j in (26,28,42,52,62)]
 if len(code)==248 and len(ins)==75 and len(refs)==12:
  mask=set();PE_equal=True
  for r in refs:
   off=r['offset'];dest=f589.ORIGINAL_COFF.get(off)
   if dest is None:PE_equal=False;continue
   typ,target=dest
   physical=int.from_bytes(raw[off:off+4],'little') if typ=='DIR32' else 0x43b0b0+off+4+int.from_bytes(raw[off:off+4],'little',signed=True)
   if r['type']!=typ or r['addend']!=0 or physical!=target:PE_equal=False
   mask.update(range(off,off+4))
  row['genuine_12_PE_fields_correct']=PE_equal
  if PE_equal:
   assert len(mask)==48 and all(orig[j].mnemonic==ins[j].mnemonic
         and orig[j].size==ins[j].size for j in range(75)), 'physical 248B/75 x86 Scene geometry altered'
   wrong=[j for j in range(248) if j not in mask and code[j]!=raw[j]]
   row['original_native_nonfield_matching']=200-len(wrong)
   row['native_nonfield_wrong_offsets']=wrong
 rows.append(row);print(json.dumps(row),flush=True)
(O/'explore-summary.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==12
assert sum(r.get('original_native_nonfield_matching')==191 for r in rows)==1
assert sum(r.get('original_native_nonfield_matching')==189 for r in rows)==9
assert sum(r.get('whole_source_CODE_B')==254 for r in rows)==2
assert all(r['COFF_fields']==12 for r in rows)
assert all(r.get('genuine_12_PE_fields_correct') for r in rows if r['whole_source_CODE_B']==248)
(O/'verified-summary.json').write_text(json.dumps({
 'original_whole_virtual_destructor':'0x0043B0B0',
 'real_original_entire_CODE_B':248,
 'real_original_x86_count':75,
 'real_original_typed_physical_PE_fields':12,
 'genuine_named_actual_free_pointer_source_variants':12,
 'baseline_source_native_nonrelocation_match':'191/200',
 'nine_named_source_real_native_nonfield_match':'189/200',
 'nine_named_source_complete_CODE_B':248,
 'nine_named_source_complete_x86':75,
 'two_true_branch_reference_or_member_pointer_source_B':254,
 'two_real_branch_reference_source_x86':78,
 'true_original_texture_and_deleting_receiver_EBP_slots':['-0x14','-0x10'],
 'newly_accepted_whole_callable_CODE_B':0,
 'original_whole_function_exact':False,
 'all_979_accepted_exact_units_cold_replayed':False,
 'source_variants':rows
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['original_whole_function_exact'] is False
print('F864 real Scene whole 248B destructor: 12 complete native VC7.1 source controls, 10 original-size 75x86/12 PE-field sources; baseline 191/200, nine independent named real frees 189/200. Two genuine member pointer/ref source variants 254B/78x86 nonnative. No original whole exact CODE, no cold replay.')
