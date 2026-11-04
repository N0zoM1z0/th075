#!/usr/bin/env python3
"""F1078 native full ArchiveCatalog destructor: real indexed element lvalue ownership.

Freshly compile ordinary VC7.1 complete original-shaped 171B destructor
sources. Contrast true mutable/const/volatile element references and
pointer-to-element lifetimes, plus semantically real resource-delete value
categories. Independently compare the COMPLETE pinned PE function and all
14 actual physical external target fields. Never crop generated CODE or
count local/near match as an independently exact original game callable.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import hashlib,importlib.util,json,os,re,subprocess,sys,collections
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1078-archive-element-lifetimes';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
name='''            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
dele='            delete *g_ArchiveResourcesAt0068BE08.At(index);'
assert base.count(name)==base.count(dele)==1
candidates={'baseline':base}
names={
 'name-mutable-reference':'''            char*& filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);''',
 'name-const-reference':'''            char* const& filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);''',
 'name-volatile-reference':'''            char* volatile& filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);''',
 'name-element-address':'''            char** filenameEntry = g_ArchiveNamesAt0068BE1C.At(index);
            free(*filenameEntry);''',
 'name-const-element-address':'''            char* const* filenameEntry = g_ArchiveNamesAt0068BE1C.At(index);
            free(*filenameEntry);''',
 'name-pointer-to-element-const-ref':'''            char** const& filenameEntry = g_ArchiveNamesAt0068BE1C.At(index);
            free(*filenameEntry);''',
 'name-direct-const-ref':'''            free(static_cast<char* const&>(*g_ArchiveNamesAt0068BE1C.At(index)));''',
 'name-direct-volatile-ref':'''            free(static_cast<char* volatile&>(*g_ArchiveNamesAt0068BE1C.At(index)));''',
 'name-direct-const-pointer':'''            free(static_cast<char* const>(*g_ArchiveNamesAt0068BE1C.At(index)));''',
 'name-direct-double-deref':'''            free(*g_ArchiveNamesAt0068BE1C.At(index));''',
 'name-direct-reference-identity':'''            free(*(&(*g_ArchiveNamesAt0068BE1C.At(index))));''',
 'name-original-reinterpret':'''            char* filename = *reinterpret_cast<char**>(g_ArchiveNamesAt0068BE1C.At(index));
            free(filename);''',
}
for tag,text in names.items():candidates[tag]=base.replace(name,text,1)
deletes={
 'delete-static-pointer':'''            delete static_cast<ArchiveResourceF343*>(*g_ArchiveResourcesAt0068BE08.At(index));''',
 'delete-const-pointer-value':'''            delete static_cast<ArchiveResourceF343* const>(*g_ArchiveResourcesAt0068BE08.At(index));''',
 'delete-element-address':'''            ArchiveResourceF343** resourceEntry = g_ArchiveResourcesAt0068BE08.At(index);
            delete *resourceEntry;''',
 'delete-pointer-const-reference':'''            ArchiveResourceF343** const& resourceEntry = g_ArchiveResourcesAt0068BE08.At(index);
            delete *resourceEntry;''',
 'delete-original-reinterpret':'''            delete *reinterpret_cast<ArchiveResourceF343**>(g_ArchiveResourcesAt0068BE08.At(index));''',
 'delete-reference-identity':'''            delete *(&(*g_ArchiveResourcesAt0068BE08.At(index)));''',
}
for tag,text in deletes.items():candidates[tag]=base.replace(dele,text,1)
candidates['both-real-element-references']=base.replace(dele,deletes['delete-pointer-const-reference'],1).replace(name,names['name-mutable-reference'],1)
assert len(candidates)==1+len(names)+len(deletes)+1==20
sp=importlib.util.spec_from_file_location('f1078reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();ORIGINAL=rd.pe_bytes_at(PE,0x0041CE50,171)
D=Cs(CS_ARCH_X86,CS_MODE_32);native=list(D.disasm(ORIGINAL,0x0041CE50))
assert len(native)==51 and native[2].op_str=='esp, 0x18' and native[22].op_str=='dword ptr [ebp - 0xc], eax' and native[24].op_str=='dword ptr [ebp - 8], ecx' and native[38].op_str=='dword ptr [ebp - 0x10], eax'
fields=((10,'DIR32',0x68BE04),(18,'DIR32',0x68BE04),(47,'DIR32',0x68BE1C),(52,'REL32',0x41DD50),
 (66,'DIR32',0x68BE08),(71,'REL32',0x41DB40),(98,'REL32',0x41D8C0),(119,'DIR32',0x68BE1C),
 (124,'REL32',0x41DDC0),(138,'REL32',0x64169D),(148,'DIR32',0x68BE08),(153,'REL32',0x41DCD0),
 (158,'DIR32',0x68BE1C),(163,'REL32',0x41DF50))
for off,typ,target in fields:
 val=int.from_bytes(ORIGINAL[off:off+4],'little',signed=typ=='REL32')
 assert (0x41CE50+off+4+val if typ=='REL32' else val)==target
MASK={k for off,_,_ in fields for k in range(off,off+4)}
assert len(MASK)==56
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[];counts=collections.Counter()
for tag,src in candidates.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,text=True,capture_output=True,timeout=290)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 row={'variant':tag,'native_whole_original_CODE_B':171,'native_whole_x86':51,'native_original_nonreloc_comparable_B':115,'original_whole_callable_exact':False}
 if cp.returncode:
  row['compiler_error']=(cp.stdout+cp.stderr)[-700:]
  print(tag,'compiler failure',row['compiler_error'][-160:],flush=True)
  rows.append(row);continue
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ');I=list(D.disasm(code,0))
 row.update({'source_whole_CODE_B':len(code),'source_whole_x86':len(I),'source_original_nonlocal_fields':len(refs),
  'original_mnemonics_matching':sum(a.mnemonic==b.mnemonic for a,b in zip(native,I)),
  'original_x86_widths_matching':sum(a.size==b.size for a,b in zip(native,I))})
 # Check actual original physical targets; reject any nonnative extra
 # instruction, truncated CODE or extra wrong game function call.
 if len(code)==171 and len(I)==51 and len(refs)==14:
  phys=(sorted((r['offset'],r['type']) for r in refs)==sorted((off,t) for off,t,_ in fields)
        and all(r['addend']==0 and r['local_symbol_offset'] is None for r in refs))
  row['original_14_physical_fields_aligned']=phys
  if phys:
   # Compare actual source COFF physical destinations to the actual pinned
   # native PE, not just kind/offset. A matching COFF field *count*
   # proves nothing about its physical original target.
   report=rd.compare(obj,'??1ArchiveCatalogF343@@QAE@XZ',0x0041CE50,171)
   assert len(report['relocations'])==14 and report['comparable_bytes']==115
   for got,(off,t,target) in zip(report['relocations'],fields):
    assert int(got['offset'],16)==off and got['type']==t
    assert int(got['object_addend'],16)==0
    assert int(got['solved_destination'],16)==target,(tag,got,target)
   mismatches=[k for k in range(171) if k not in MASK and ORIGINAL[k]!=code[k]]
   assert report['matched_comparable_bytes']==115-len(mismatches)
   row.update({'all_14_actual_original_PE_field_destinations_verified':True,'original_nonfield_matching_B':115-len(mismatches),'wrong_nonfield_original_offsets':mismatches,
    'actual_resource_slot':I[22].op_str,'actual_scalar_delete_receiver_slot':I[24].op_str,
    'actual_filename_slot':I[38].op_str,
    'original_whole_callable_exact':len(mismatches)==0})
   assert all((r['offset'],r['type'])==(off,t) and r['addend']==0
              for r,(off,t,_) in zip(sorted(refs,key=lambda x:x['offset']),fields))
 counts[(len(code),len(I),len(refs),row.get('original_nonfield_matching_B',-1))]+=1
 rows.append(row)
 print(tag,'complete',len(code),'B /',len(I),'x86; native 14 fields',row.get('original_14_physical_fields_aligned'),
       'matching original nonfield',row.get('original_nonfield_matching_B'),'/115',flush=True)
(O/'verified-summary.json').write_text(json.dumps({'original_complete_game_callable':'0x0041CE50',
 'original_native_whole_CODE_B':171,'original_native_whole_x86':51,
 'original_actual_physical_PE_fields':14,'original_nonreloc_comparable_B':115,
 'original_three_used_EBP_slots':{'resource':'-0xC','delete':'-0x8','filename':'-0x10'},
 'full_original_Cpp_variants':len(rows),'all_979_cold_replay':False,
 'any_new_accepted_original_whole_CODE_B':0,'selected_original_exact':False,
 'results':rows,'distribution':{str(k):v for k,v in counts.items()}},indent=2)+'\n')
assert len(rows)==20 and all('source_whole_CODE_B' in x for x in rows)
assert rows[0]['source_whole_CODE_B']==171 and rows[0]['original_nonfield_matching_B']==108
assert all(r.get('all_14_actual_original_PE_field_destinations_verified') is True for r in rows if r.get('original_14_physical_fields_aligned'))
assert all(r.get('original_nonfield_matching_B',0)<115 for r in rows)
if any(r['original_whole_callable_exact'] for r in rows):
 print('IMPORTANT: ORIGINAL 171B WHOLE SOURCE EXACT CANDIDATE; separately verify canonical acceptance before claiming exact!')
else:print('F1078 20 genuine native whole Archive destructor C++ value/lifetime variants built, no original entire 171B exact; receipts and actual PE physical evidence saved.')
