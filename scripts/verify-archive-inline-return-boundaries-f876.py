"""F876: original Archive full171B destructor real returned-pointer helper boundaries.

Ten real C++ whole destructor source controls, normal pinned VC7.1
/Od /Ob0 /GX-, using forceinline/ordinary inline helper return
values and template dereference of the ACTUAL archive name/resource
pointers. Verify original whole 171B/51x86/14 physically solved PE
fields in baseline. Ordinary and forceinline helpers create separate
source callee calls (167B/50x86/13 fields, or 163B/49x86/12),
rather than preserving original At() calls; template wrappers add
178/185B and new call references. No split or falsely accepted exact
whole CODE. No mass cold replay.
"""
from pathlib import Path
import importlib.util,os,sys,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f876-archive-inline-return';O.mkdir(parents=True,exist_ok=True)
baseline=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
anchor='class ArchiveCatalogF343 {public: ~ArchiveCatalogF343();};'
assert baseline.count(anchor)==1
ptr='delete *g_ArchiveResourcesAt0068BE08.At(index);'
name='char* filename = *g_ArchiveNamesAt0068BE1C.At(index);'
assert baseline.count(ptr)==1 and baseline.count(name)==1
extra='''// Genuine helper return values from native list elements, no ignored locals.
static __forceinline ArchiveResourceF343* F876GetResource(unsigned int index) {
    return *g_ArchiveResourcesAt0068BE08.At(index);
}
static __forceinline char* F876GetName(unsigned int index) {
    return *g_ArchiveNamesAt0068BE1C.At(index);
}
template<class T> static __forceinline T* F876BorrowValue(T** observedSlot) {
    return *observedSlot;
}
static inline ArchiveResourceF343* F876InlineResource(unsigned int index) {
    return *g_ArchiveResourcesAt0068BE08.At(index);
}
static inline char* F876InlineName(unsigned int index) {
    return *g_ArchiveNamesAt0068BE1C.At(index);
}
'''
base=baseline.replace(anchor,extra+anchor,1)
cases={
 'baseline':baseline,
 'forced-resource':base.replace(ptr,'delete F876GetResource(index);'),
 'forced-name':base.replace(name,'char* filename = F876GetName(index);'),
 'forced-both':base.replace(ptr,'delete F876GetResource(index);').replace(name,'char* filename = F876GetName(index);'),
 'forced-template-resource':base.replace(ptr,'delete F876BorrowValue(g_ArchiveResourcesAt0068BE08.At(index));'),
 'forced-template-name':base.replace(name,'char* filename = F876BorrowValue(g_ArchiveNamesAt0068BE1C.At(index));'),
 'forced-template-both':base.replace(ptr,'delete F876BorrowValue(g_ArchiveResourcesAt0068BE08.At(index));').replace(name,'char* filename = F876BorrowValue(g_ArchiveNamesAt0068BE1C.At(index));'),
 'ordinary-inline-resource':base.replace(ptr,'delete F876InlineResource(index);'),
 'ordinary-inline-name':base.replace(name,'char* filename = F876InlineName(index);'),
 'ordinary-inline-both':base.replace(ptr,'delete F876InlineResource(index);').replace(name,'char* filename = F876InlineName(index);')
}
sp=importlib.util.spec_from_file_location('f876rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
pe=rd.verified_target();native=rd.pe_bytes_at(pe,0x41ce50,171);d=Cs(CS_ARCH_X86,CS_MODE_32);N=list(d.disasm(native,0x41ce50));assert(len(native),len(N))==(171,51)
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
obj_paths={}
for key,src in cases.items():
 cpp=O/(key+'.cpp');obj=O/(key+'.obj');cpp.write_text(src)
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=225)
 (O/(key+'.log')).write_text(p.stdout+p.stderr)
 if p.returncode:print(key,'COMPILE FAILURE',(p.stdout+p.stderr)[-520:],flush=True);continue
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ');I=list(d.disasm(code,0))
 obj_paths[key]=obj
 assert all(r['addend']==0 for r in refs)

 row={'variant':key,'code_B':len(code),'x86':len(I),'COFF_refs':len(refs),
       'native_function_relocation_callees':[r['symbol'] for r in refs]}
 if len(I)>38:
  row['stack_orig_roles']=[I[j].op_str for j in (3,8,22,24,30,38)]
 if len(code)==171 and len(I)==51 and len(refs)==14:
  from importlib.util import spec_from_file_location,module_from_spec
  mask={q for r in refs for q in range(r['offset'],r['offset']+4)}
  wrong=[i for i in range(171) if i not in mask and code[i]!=native[i]]
  row['native_nonfield_equal']=115-len(wrong)
  row['actual_wrong_offsets']=wrong
  row['native_mnemonics_and_widths_equal']=all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(N,I))
 rows.append(row)
 print(json.dumps(row),flush=True)
(O/'explore-summary.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==10
by={x['variant']:x for x in rows}
assert (by['baseline']['code_B'],by['baseline']['x86'],by['baseline']['COFF_refs'])==(171,51,14)
assert (by['baseline']['native_nonfield_equal'],by['baseline']['native_mnemonics_and_widths_equal'])==(108,True)
assert by['baseline']['actual_wrong_offsets']==[79,82,85,88,96,132,135]
original=rd.compare(obj_paths['baseline'],'??1ArchiveCatalogF343@@QAE@XZ',0x41ce50,171)
assert original['result']=='mismatch'
assert original['matched_comparable_bytes']==108 and original['comparable_bytes']==115
assert len(original['relocations'])==14
assert all(x['object_addend']=='0x00000000' for x in original['relocations'])
assert [x['offset'] for x in original['relocations']]==[
 '0xA','0x12','0x2F','0x34','0x42','0x47','0x62','0x77',
 '0x7C','0x8A','0x94','0x99','0x9E','0xA3']
assert [x['solved_destination'] for x in original['relocations']]==[
 '0x0068BE04','0x0068BE04','0x0068BE1C','0x0041DD50',
 '0x0068BE08','0x0041DB40','0x0041D8C0','0x0068BE1C',
 '0x0041DDC0','0x0064169D','0x0068BE08','0x0041DCD0',
 '0x0068BE1C','0x0041DF50']
assert all(x['solved_destination']==x['target_field'] for x in original['relocations']
           if x['type']=='DIR32')
for key in ('forced-resource','forced-name','ordinary-inline-resource','ordinary-inline-name'):
 r=by[key]
 assert (r['code_B'],r['x86'],r['COFF_refs'])==(167,50,13),(key,r)
 assert any('F876GetResource' in s or 'F876GetName' in s or 'F876InlineResource' in s or 'F876InlineName' in s
            for s in r['native_function_relocation_callees'])
for key in ('forced-both','ordinary-inline-both'):
 r=by[key]
 assert (r['code_B'],r['x86'],r['COFF_refs'])==(163,49,12),key
for key in ('forced-template-resource','forced-template-name'):
 r=by[key]
 assert (r['code_B'],r['x86'],r['COFF_refs'])==(178,53,15),key
 assert any('F876BorrowValue' in s for s in r['native_function_relocation_callees'])
assert (by['forced-template-both']['code_B'],by['forced-template-both']['x86'],
        by['forced-template-both']['COFF_refs'])==(185,55,16)
(O/'verified-summary.json').write_text(json.dumps({
 'original_nonvirtual_archive_destructor':'0x0041CE50',
 'original_complete_CODE_B':171,
 'original_full_x86_count':51,
 'original_physical_PE_field_count':14,
 'baseline_real_native_nonfield_equality':'108/115',
 'original_baseline_wrong_EBP_stack_operand_offsets':[79,82,85,88,96,132,135],
 'real_return_value_helper_variants_tested':10,
 'inline_and_forceinline_shift_native_list_call_boundary':True,
 'four_single_helpers_result_full_CODE_B':167,
 'two_double_helpers_result_full_CODE_B':163,
 'two_template_single_helpers_result_full_CODE_B':178,
 'template_double_helpers_result_full_CODE_B':185,
 'wrong_callee_relocations_independently_observed':True,
 'real_original_destructor_whole_CODE_exact':False,
 'newly_accepted_authored_whole_CODE_B':0,
 'all_existing_979_units_cold_replayed':False,
 'variant_original_full_COFFER_source':rows
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['real_original_destructor_whole_CODE_exact'] is False
print('F876 original whole 171B/51x86/14 genuine PE fields, 10 complete actual used pointer-return C++ variants. Native 108/115 nonrelocation baseline; four 167B helper, two 163B double helper, two 178B templates, one 185B template double all move/add real calls and NONNATIVE complete extents. Zero exact authored CODE, no mass cold replay.')
