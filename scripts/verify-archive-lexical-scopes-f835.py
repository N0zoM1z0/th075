"""F835: genuine 171B Archive destructor lexical scopes, full original VC7.1 PE/COFF proof; no exact credit."""
from pathlib import Path
import importlib.util,sys,os,json,subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f835-archive-lexical-scope';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
old='''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
assert base.count(old)==1
delete='delete *g_ArchiveResourcesAt0068BE08.At(index);'
read='char* filename = *g_ArchiveNamesAt0068BE1C.At(index);'
free='free(filename);'
parts=[delete,read,free]
def arrange(*pieces):
 return '\n'.join('            '+piece.replace('\n','\n            ') for piece in pieces)
def block(text):
 return '{\n    '+text.replace('\n','\n    ')+'\n}'
D=delete;Rr=read;F=free
variants={
 'baseline':base,
 'delete-scoped':base.replace(old,arrange(block(D),Rr,F)),
 'filename-free-scoped':base.replace(old,arrange(D,block(arrange(Rr,F)))),
 'two-distinct-scopes':base.replace(old,arrange(block(D),block(arrange(Rr,F)))),
 'whole-loop-body-extra-scope':base.replace(old,block(arrange(D,Rr,F))),
 'nested-delete':base.replace(old,arrange(block(block(D)),Rr,F)),
 'nested-filename-free':base.replace(old,arrange(D,block(block(arrange(Rr,F))))),
 'nested-both':base.replace(old,arrange(block(block(D)),block(block(arrange(Rr,F))))),
 'whole-body-nested-two':base.replace(old,block(arrange(block(D),block(arrange(Rr,F))))),
 'delete-scoped-free-scoped':base.replace(old,arrange(block(D),Rr,block(F))),
 'delete-scoped-name-free':base.replace(old,arrange(block(D),Rr,block(F))),
 'filename-declared-before-delete-block':base.replace(old,arrange('char* filename;',block(D),'filename = *g_ArchiveNamesAt0068BE1C.At(index);',F)),
 'filename-declared-before-delete-two-scopes':base.replace(old,arrange('char* filename;',block(D),block(arrange('filename = *g_ArchiveNamesAt0068BE1C.At(index);',F)))),
 'filename-outer-loop-before':base.replace(old,arrange(block(D),'filename = *g_ArchiveNamesAt0068BE1C.At(index);',F)).replace(
   '        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {',
   '        char* filename;\n        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {'),
 'used-file-reference-scoped':base.replace(old,arrange(block(D),block(arrange('char* filename = *g_ArchiveNamesAt0068BE1C.At(index);','char* const& fileReference = filename;','free(fileReference);')))),
 'delete-outer-block-with-file-inner':base.replace(old,block(arrange(D,block(arrange(Rr,F))))),
}
# Deduplicate accidental duplicate spelling.
unique={}
for name,text in variants.items():
 if text in unique.values():continue
 unique[name]=text
variants=unique
print('lexically distinct real source variants',len(variants),flush=True)
sp=importlib.util.spec_from_file_location('f835rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
pe=rd.verified_target();raw=rd.pe_bytes_at(pe,0x41ce50,171);D=Cs(CS_ARCH_X86,CS_MODE_32)
orig=list(D.disasm(raw,0x41ce50))
assert len(orig)==51 and sum(x.size for x in orig)==171 and orig[-1].mnemonic=='ret'
assert [orig[j].op_str for j in (2,3,8,22,24,38)]==['esp, 0x18','dword ptr [ebp - 0x14], ecx','dword ptr [ebp - 4], 0','dword ptr [ebp - 0xc], eax','dword ptr [ebp - 8], ecx','dword ptr [ebp - 0x10], eax']
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
baseline_code=None
baseline_fields=None
for name,src in variants.items():
 cpp=O/(name+'.cpp');obj=O/(name+'.obj');cpp.write_text(src)
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
   cwd=R,env=E,capture_output=True,text=True,timeout=200)
 (O/(name+'.log')).write_text(p.stdout+p.stderr)
 if p.returncode:
  rows.append({'variant':name,'compiler_failed':True,'error':(p.stdout+p.stderr)[-160:]})
  print(name,'COMPILE FAIL',(p.stdout+p.stderr)[-180:],flush=True);continue
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ')
 current=list(D.disasm(code,0))
 row={'variant':name,'source_B':len(code),'x86':len(current),'fields':len(refs),
   'actual_index_slot':current[8].op_str if len(current)>8 else None,
   'resource_slot':current[22].op_str if len(current)>22 else None,
   'delete_receiver_slot':current[24].op_str if len(current)>24 else None,
   'filename_slot':current[38].op_str if len(current)>38 else None}
 if len(code)==171 and len(current)==51 and len(refs)==14:
  c=rd.compare(obj,'??1ArchiveCatalogF343@@QAE@XZ',0x41ce50,171)
  assert c['result']=='mismatch' and c['comparable_bytes']==115
  assert c['matched_comparable_bytes']==(102 if name=='filename-outer-loop-before' else 108)
  assert len(c['relocations'])==14 and all(int(r['object_addend'],16)==0 for r in c['relocations'])
  row.update({'native_PE_comparable_B':c['comparable_bytes'],
              'original_comparable_equal_B':c['matched_comparable_bytes'],
              'result':c['result'],
              'all_original_14_relocations':[r['solved_destination'] for r in c['relocations']],
              'source_same_original_instr_mnemonics':all(a.mnemonic==b.mnemonic for a,b in zip(orig,current))})
 if name=='baseline':
  baseline_code=code
  baseline_fields=refs
 elif name not in ('filename-outer-loop-before','used-file-reference-scoped'):
  assert code==baseline_code and refs==baseline_fields, 'lexical source changed baseline whole CODE/COFF'
 if name=='used-file-reference-scoped':
  assert len(code)==179 and len(current)==54 and len(refs)==14
 elif name=='filename-outer-loop-before':
  assert (len(code),len(current),row['original_comparable_equal_B'])==(171,51,102)
 else:
  assert (len(code),len(current),row['original_comparable_equal_B'])==(171,51,108)
 rows.append(row)
 print(name,'B',len(code),'x86',len(current),'native_equal',row.get('original_comparable_equal_B'),'index',row['actual_index_slot'],'resource',row['resource_slot'],'delete',row['delete_receiver_slot'],'filename',row['filename_slot'],flush=True)
(O/'summary.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==15
assert sum(x.get('original_comparable_equal_B')==108 for x in rows)==13
assert sum(x.get('original_comparable_equal_B')==102 for x in rows)==1
assert sum(x.get('source_B')==179 for x in rows)==1
(O/'verified-summary.json').write_text(json.dumps({
 'real_original_complete_function':'0x0041CE50',
 'original_native_whole_CODE_B':171,'native_whole_x86':51,
 'native_original_PE_fields':14,
 'natural_whole_source_variants':len(rows),
 'whole_original_nonrelocation_best_matching_B':'108/115',
 'lexical_braces_source_byte_identical_source_variants':13,
 'filename_before_loop_native_matching_B':'102/115',
 'actually_used_const_reference_adds_real_non_native_CODE':'179B/54x86',
 'native_resource_delete_filename_EBP_slots_still_nonexact':True,
 'new_accepted_whole_authored_CODE_B':0,
 'full_979_exact_unit_cold_replay_run':False,
 'real_source_profiles':rows,
},indent=2)+'\n')
print('F835: 15 complete VC7.1 original Archive destructor lexical source controls, 13 unchanged 171B/51x86 and 108/115 native nonfield, filename before loop 102/115, genuine used reference 179B/54x86. All 14 physical native PE fields checked on equal-size candidates; original EBP locals NONEXACT.')
