"""F854: full 171B Archive destructor real resource/delete value categories.

Sixteen genuinely used C++ resource owner/ref/pointer categories, with
the actual original resource delete, filename free, and both native
Clear calls. Compile ALL complete normal pinned VC7.1 /GX- functions,
then prove 4 exact-source-geometry candidates are STILL 108/115
nonrelocation native bytes with all 14 real PE fields correct.
Other genuine used values grow to 177/183/185 complete CODE B.
Never truncate larger CODE, fake EBP locals or claim whole exact.
No mass cold replay.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f854-archive-real-delete-values';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
needle='delete *g_ArchiveResourcesAt0068BE08.At(index);'
assert base.count(needle)==1
values={
 'baseline':needle,
 'owned-value':'''ArchiveResourceF343* resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete resource;''',
 'const-owned-value':'''ArchiveResourceF343* const resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete resource;''',
 'register-owned-value':'''register ArchiveResourceF343* resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete resource;''',
 'volatile-pointer-value':'''ArchiveResourceF343* volatile resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete resource;''',
 'owned-value-parentheses':'''ArchiveResourceF343* resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete (resource);''',
 'lvalue-ref-entry':'''ArchiveResourceF343*& resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete resource;''',
 'const-ref-entry':'''ArchiveResourceF343* const& resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete resource;''',
 'pointer-to-pointer':'''ArchiveResourceF343** entry=g_ArchiveResourcesAt0068BE08.At(index);
            delete *entry;''',
 'const-pointer-to-pointer':'''ArchiveResourceF343** const entry=g_ArchiveResourcesAt0068BE08.At(index);
            delete *entry;''',
 'register-pointer-to-pointer':'''register ArchiveResourceF343** entry=g_ArchiveResourcesAt0068BE08.At(index);
            delete *entry;''',
 'two-used-values':'''ArchiveResourceF343** entry=g_ArchiveResourcesAt0068BE08.At(index);
            ArchiveResourceF343* resource=*entry;
            delete resource;''',
 'owned-value-used-ref':'''ArchiveResourceF343* resource=*g_ArchiveResourcesAt0068BE08.At(index);
            ArchiveResourceF343* const& receiver=resource;
            delete receiver;''',
 'delete-lvalue-ref-expression':'''delete static_cast<ArchiveResourceF343*&>(*g_ArchiveResourcesAt0068BE08.At(index));''',
 'delete-const-ref-expression':'''delete static_cast<ArchiveResourceF343* const&>(*g_ArchiveResourcesAt0068BE08.At(index));''',
 'delete-pointer-deref-expression':'''delete (*g_ArchiveResourcesAt0068BE08.At(index));''',
}
print('real source value-category candidates',len(values),flush=True)
sp=importlib.util.spec_from_file_location('rd854',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
pe=rd.verified_target();raw=rd.pe_bytes_at(pe,0x41ce50,171);d=Cs(CS_ARCH_X86,CS_MODE_32);native=list(d.disasm(raw,0x41ce50))
assert (len(raw),len(native))==(171,51) and native[-1].mnemonic=='ret'
assert [native[i].op_str for i in (2,3,8,22,24,38)]==[
 'esp, 0x18','dword ptr [ebp - 0x14], ecx',
 'dword ptr [ebp - 4], 0','dword ptr [ebp - 0xc], eax',
 'dword ptr [ebp - 8], ecx','dword ptr [ebp - 0x10], eax']

E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results=[]
baseline_code=None
baseline_fields=None
baseline_semantic_calls=None
for label,value in values.items():
 cpp=O/(label+'.cpp');obj=O/(label+'.obj');cpp.write_text(base.replace(needle,value,1))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=190)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':label,'compile_error':(cp.stdout+cp.stderr)[-230:]}
  print(label,'COMPILE FAILED',row['compile_error'].replace('\n',' '),flush=True)
  results.append(row);continue
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ')
 current=list(d.disasm(code,0))
 assert len(refs)==14 and all(r['addend']==0 for r in refs)
 semantic_calls=sorted((r['type'],r['symbol'],r['addend']) for r in refs)
 if label=='baseline':
  baseline_code=code
  baseline_fields=refs
  baseline_semantic_calls=semantic_calls
 assert semantic_calls==baseline_semantic_calls, 'actual game resource/delete/filename call identities changed '+label
 row={'variant':label,'full_CODE_B':len(code),'whole_x86':len(current),
      'COFF_fields':len(refs)}
 if len(current)>38:
  row['slot_resource_ordinal22']=current[22].op_str
  row['slot_receiver_ordinal24']=current[24].op_str
  row['slot_filename_ordinal38']=current[38].op_str
 if len(code)==171 and len(current)==51 and len(refs)==14:
  original=rd.compare(obj,'??1ArchiveCatalogF343@@QAE@XZ',0x41ce50,171)
  assert original['result']=='mismatch'
  assert original['comparable_bytes']==115
  assert original['matched_comparable_bytes']==108
  assert len(original['relocations'])==14
  assert all(int(r['object_addend'],16)==0 for r in original['relocations'])
  assert code==baseline_code and refs==baseline_fields, 'original-sized source generated different actual native CODE or PE fields'
  assert all(native[j].mnemonic==current[j].mnemonic
             and native[j].size==current[j].size for j in range(51))
  row['original_matching_nonfield']=original['matched_comparable_bytes']
  row['original_comparable_nonfield']=original['comparable_bytes']
  row['original_compare_result']=original['result']
  row['actual_all_14_PE_fields']=[(x['offset'],x['type'],x['solved_destination']) for x in original['relocations']]
 results.append(row)
 print(json.dumps({k:v for k,v in row.items() if k!='actual_all_14_PE_fields'}),flush=True)
(O/'exploration-summary.json').write_text(json.dumps(results,indent=2)+'\n')

assert len(results)==16
assert sorted(r['full_CODE_B'] for r in results)==[171]*4+[177]*10+[183]+[185]
assert sorted(r['whole_x86'] for r in results)==[51]*4+[53]*10+[55]+[56]
assert sum(r.get('original_matching_nonfield')==108 for r in results)==4
(O/'verified-summary.json').write_text(json.dumps({
 'actual_native_original_game_function':'0x0041CE50',
 'real_original_entire_CODE_B':171,
 'real_original_x86':51,
 'real_original_physical_PE_fields':14,
 'real_compiled_source_value_category_variants':len(results),
 'original_size_source_variants_that_remain_nonexact':4,
 'native_original_size_candidate_nonfield_equal':'108/115',
 'genuine_named_pointer_or_reference_variants_emit_non_native_code_B':[177,183,185],
 'all_variants_original_resource_delete_free_clear_call_symbols_unchanged':True,
 'native_original_resource_receiver_filename_EBP_slots_recovered':False,
 'whole_original_authored_function_exact':False,
 'new_accepted_original_callable_CODE_B':0,
 'mass_979_unit_cold_replay':False,
 'variants':results
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['real_compiled_source_value_category_variants']==16, 'target receipt must be strict JSON'
print('F854 real original Archive 171B: 16 complete pinned VC7.1 resource pointer, reference, value category expressions; four 171B/51x86 original-sized sources byte-identical and 14/14 physical original PE fields, STILL 108/115 nonrelocation bytes. All real named-value candidates 177/183/185B whole nonnative. Archive NONEXACT, zero accepted whole CODE.')
