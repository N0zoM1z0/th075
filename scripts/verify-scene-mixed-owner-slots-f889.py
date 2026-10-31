"""F889: independent original Scene 248B native mixed 1+2 free-owner test.

Normal pinned VC7.1 /Od /GX full original authored virtual
destructor, three actually released CRT pointer source values.
Test 28 complete mixed 1/2-field aggregates + named locals,
every real free/texture/base/clock effect preserved, with
4 real declaration positions and true register/volatile
pointer-qualified variants. 248B/75x86/12 authentic physically
typed PE fields all 29 sources, but baseline 191/200
native nonfield bytes vs all mixed variants 189/200.
No inert locals or source registers forced. No full-unit
cold replay and no accepted whole callable CODE.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json,itertools,collections
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f889-scene-mixed-free-owners';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
decl='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
loc='    CleanupPointersF215 released;'
tex='    if (FIELD(TextureManagerF200*,0x08))'
clock='    if (g_FrameClockModeAt0066C238 == 2 || 4)'
assert all(base.count(n)==1 for n in (decl,loc,tex,clock))
fields=('digitAtlas','firstCombo','secondCombo')
cases={'baseline':base}
for count in (1,2):
 for grouped in itertools.combinations(fields,count):
  named=tuple(f for f in fields if f not in grouped)
  replacement='struct CleanupPointersF215 {\n'+''.join('    void* '+f+';\n' for f in grouped)+'};'
  actual=base.replace(decl,replacement,1)
  for n in named:actual=actual.replace('released.'+n,n)
  for place in ('after','before','before-texture','before-clock'):
   s=actual.replace(loc,'',1)
   namelines=''.join('    void* '+n+';\n' for n in named)
   if place=='after':
    insert=loc+'\n'+namelines
    s=s.replace(tex,insert+tex,1)
   elif place=='before':
    insert=namelines+loc+'\n'
    s=s.replace(tex,insert+tex,1)
   elif place=='before-texture':
    s=s.replace(tex,loc+'\n'+namelines+tex,1)
   elif place=='before-clock':
    s=s.replace(clock,loc+'\n'+namelines+clock,1)
   tag='mixed-'+''.join(f[0] for f in grouped)+'-'+place
   cases[tag]=s
# Distinct real aggregate freeing objects with genuine named live
# local type controls rather than padding variables.
for count in (1,2):
 grouped=fields[:count];named=fields[count:]
 original=base.replace(decl,
    'struct CleanupPointersF215 {\n'+''.join('    void* '+f+';\n' for f in grouped)+'};',1)
 for n in named:original=original.replace('released.'+n,n)
 for qualifier in ('register','volatile'):
  header=loc+'\n'+''.join(('    void* volatile '+n+';\n') if qualifier=='volatile' else ('    register void* '+n+';\n') for n in named)
  src=original.replace(loc,header,1)
  cases['named-'+qualifier+'-group'+str(count)]=src
sp=importlib.util.spec_from_file_location('f889rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f889native','scripts/verify-scene-texture-delete-f589.py');f589=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f589;sp.loader.exec_module(f589)
pe=rd.verified_target();raw=rd.pe_bytes_at(pe,0x43b0b0,248);D=Cs(CS_ARCH_X86,CS_MODE_32);N=list(D.disasm(raw,0x43b0b0));assert len(N)==75 and len(f589.ORIGINAL_COFF)==12
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
res=[];symbol_template=None
for tag,src in cases.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=env,capture_output=True,text=True,timeout=240)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':tag,'compile_error':(cp.stdout+cp.stderr)[-390:]};res.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
 ins=list(D.disasm(code,0))
 row={'variant':tag,'whole_CODE_B':len(code),'x86':len(ins),'COFF_fields':len(refs)}
 if len(ins)>62:row['EBP_roles_26_28_42_52_62']=[ins[j].op_str for j in (26,28,42,52,62)]
 symbols=sorted((r['type'],r['symbol'],r['addend']) for r in refs)
 if tag=='baseline':symbol_template=symbols
 row['original_callee_symbol_multiset_correct']=symbols==symbol_template
 if len(code)==248 and len(ins)==75 and len(refs)==12:
  physical_fields=all(
       r['offset'] in f589.ORIGINAL_COFF
       and r['addend']==0
       and r['type']==f589.ORIGINAL_COFF[r['offset']][0]
       and (int.from_bytes(raw[r['offset']:r['offset']+4],'little')
            if r['type']=='DIR32' else
            0x43b0b0+r['offset']+4+int.from_bytes(raw[r['offset']:r['offset']+4],'little',signed=True))
         ==f589.ORIGINAL_COFF[r['offset']][1]
       for r in refs)
  row['real_original_all_twelve_PE_fields_correct']=physical_fields
  if physical_fields:
   mask={j for r in refs for j in range(r['offset'],r['offset']+4)}
   wrong=[j for j in range(248) if j not in mask and raw[j]!=code[j]]
   row['real_original_nonrelocation_equal_B']=200-len(wrong)
   row['real_wrong_offsets']=wrong
   row['true_opcode_width_order_all_match']=all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(N,ins))
 res.append(row)
 print(json.dumps(row),flush=True)
(O/'explore-summary.json').write_text(json.dumps(res,indent=2)+'\n')
print('CANDIDATES',len(cases),'EQUALITY SUMMARY',dict(collections.Counter((x.get('whole_CODE_B'),x.get('x86'),x.get('real_original_nonrelocation_equal_B')) for x in res)),flush=True)

assert len(res)==29
assert all('compile_error' not in r for r in res)
assert all((r['whole_CODE_B'],r['x86'],r['COFF_fields'])==(248,75,12)
           and r['original_callee_symbol_multiset_correct']
           and r['real_original_all_twelve_PE_fields_correct']
           and r['true_opcode_width_order_all_match'] for r in res)
assert res[0]['variant']=='baseline'
assert res[0]['real_original_nonrelocation_equal_B']==191
assert res[0]['real_wrong_offsets']==[94,97,100,103,111,176,179,206,209]
for r in res[1:]:
 assert r['real_original_nonrelocation_equal_B']==189
 assert r['real_wrong_offsets']==[94,97,100,103,111,146,149,176,179,206,209]
assert all(r['EBP_roles_26_28_42_52_62'][0]=='dword ptr [ebp - 0x20], edx'
           and r['EBP_roles_26_28_42_52_62'][1]=='dword ptr [ebp - 0x1c], eax'
           for r in res)
# Original Scene actually requires texture pointer EBP-0x14,
# scalar delete receiver EBP-0x10, and frees EBP-18/1C/20.
# Every mixed case keeps the wrong original two delete slots
# despite changing actual resource free group and declaration time.
(O/'verified-summary.json').write_text(json.dumps({
 'original_whole_virtual_destructor':'0x0043B0B0',
 'original_complete_native_CODE_B':248,
 'original_complete_native_x86':75,
 'original_typed_physically_resolved_PE_fields':12,
 'selected_complete_native_Cpp_source_variants':len(res),
 'full_source_baseline_nonrelocation_native_matches':'191/200',
 '28_mixed_actual_free_owner_sources_native_matches':'189/200',
 'original_texture_EBP_slot':'-0x14',
 'original_scalar_delete_receiver_EBP_slot':'-0x10',
 'all_source_texture_EBP_slot':'-0x20',
 'all_source_delete_receiver_EBP_slot':'-0x1C',
 'original_CRT_free_EBP_slots':['-0x18','-0x1C','-0x20'],
 'all_Cpp_sources_exact_native_PE_field_positions_targets':True,
 'genuine_1plus2_and_2plus1_cleanup_pointer_ownership_tried':True,
 'mixed_actual_pointer_owners_do_not_solve_original_lifetime':True,
 'newly_accepted_whole_callable_CODE_B':0,
 'original_whole_destructor_exact':False,
 'mass_cold_replay':False,
 'all_29_complete_analyses':res
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['original_whole_destructor_exact'] is False
print('F889 actual original Scene whole 248B/75x86/12 native PE fields: 29 complete VC7.1 sources, including 28 genuinely used 1+2/2+1 pointer cleanup aggregates across source lifetime/qualifiers. All 28 mixed sources 189/200 native nonfield vs baseline 191/200; native texture/deleter slots still WRONG -20/-1C instead of original -14/-10. No exact whole CODE, no cold replay.')
