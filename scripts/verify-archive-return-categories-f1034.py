#!/usr/bin/env python3
"""F1034: entire native Archive destructor, genuine indexed-list At return ABI.

Contrasts pointer-to-element with reference-to-element return declarations,
including real used delete and filename expressions. All 14 native PE fields
are independently audited before any same-length comparison. No exact credit
is inferred from matching case instructions or a truncated machine function.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,itertools,json,os,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1034-archive-return-categories';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
spec=importlib.util.spec_from_file_location('f1034reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);P=rd.verified_target();ORIGIN=0x41ce50
native_bytes=rd.pe_bytes_at(P,ORIGIN,171);native=list(D.disasm(native_bytes,ORIGIN));assert len(native)==51
fields=((10,'DIR32',0x68be04),(18,'DIR32',0x68be04),(47,'DIR32',0x68be1c),(52,'REL32',0x41dd50),(66,'DIR32',0x68be08),(71,'REL32',0x41db40),(98,'REL32',0x41d8c0),(119,'DIR32',0x68be1c),(124,'REL32',0x41ddc0),(138,'REL32',0x64169d),(148,'DIR32',0x68be08),(153,'REL32',0x41dcd0),(158,'DIR32',0x68be1c),(163,'REL32',0x41df50))
for off,kind,dest in fields:
 v=int.from_bytes(native_bytes[off:off+4],'little',signed=kind=='REL32')
 assert (ORIGIN+off+4+v if kind=='REL32' else v)==dest
MASK={i for off,_,_ in fields for i in range(off,off+4)}
assert len(MASK)==56
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
cases={}
for rp,np in itertools.product(('pointer','reference','const-pointer'),repeat=2):
 s=base
 if rp=='reference':
  s=s.replace('ArchiveResourceF343** At(unsigned int index);','ArchiveResourceF343*& At(unsigned int index);').replace('delete *g_ArchiveResourcesAt0068BE08.At(index);','delete g_ArchiveResourcesAt0068BE08.At(index);')
 if rp=='const-pointer':
  s=s.replace('ArchiveResourceF343** At(unsigned int index);','ArchiveResourceF343* const* At(unsigned int index);')
 if np=='reference':
  s=s.replace('char** At(unsigned int index);','char*& At(unsigned int index);').replace('char* filename = *g_ArchiveNamesAt0068BE1C.At(index);','char* filename = g_ArchiveNamesAt0068BE1C.At(index);')
 if np=='const-pointer':s=s.replace('char** At(unsigned int index);','char* const* At(unsigned int index);')
 cases[rp+'--'+np]=s
# A true no-named-local free() call is additional natural source lifetime.
for np in ('pointer','reference'):
 s=cases['pointer--'+np]
 if np=='pointer':s=s.replace('char* filename = *g_ArchiveNamesAt0068BE1C.At(index);\n            free(filename);','free(*g_ArchiveNamesAt0068BE1C.At(index));')
 else:s=s.replace('char* filename = g_ArchiveNamesAt0068BE1C.At(index);\n            free(filename);','free(g_ArchiveNamesAt0068BE1C.At(index));')
 cases['direct-free-'+np]=s
rows=[]
for tag,source in cases.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,text=True,capture_output=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  rows.append({'variant':tag,'compiler_error':(cp.stdout+cp.stderr)[-600:]});print(tag,'failed',flush=True);continue
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ');I=list(D.disasm(code,0))
 row={'variant':tag,'whole_source_B':len(code),'whole_x86':len(I),'original_whole_B':171,'original_x86':51,'physical_source_COFF_fields':len(refs),'whole_exact':False}
 if len(code)==171 and len(I)==51 and len(refs)==14:
  row['physical_original_PE_fields_align']=(sorted((r['offset'],r['type']) for r in refs)==sorted((off,k) for off,k,t in fields) and all(r['addend']==0 and r['local_symbol_offset'] is None for r in refs))
  if row['physical_original_PE_fields_align']:
   differences=[j for j in range(171) if j not in MASK and code[j]!=native_bytes[j]]
   row.update({'native_nonfield_equal_B':115-len(differences),
      'native_nonfield_wrong_offsets':differences,'same_native_mnemonics':sum(n.mnemonic==s.mnemonic for n,s in zip(native,I)),
      'same_native_widths':sum(n.size==s.size for n,s in zip(native,I)),
      'real_resource_slot':I[22].op_str,'real_delete_slot':I[24].op_str,'real_filename_slot':I[38].op_str,
      'whole_exact':len(differences)==0})
 rows.append(row)
 print(tag,len(code),len(I),'native_equal',row.get('native_nonfield_equal_B'),
       'all_fields',row.get('physical_original_PE_fields_align'),
       'native_slots',row.get('real_resource_slot'),row.get('real_delete_slot'),row.get('real_filename_slot'),flush=True)
(O/'verified-summary.json').write_text(json.dumps({'original_Japanese_ArchiveCatalog':'0x0041CE50',
 'original_whole_B':171,'original_x86':51,'native_original_PE_fields':len(fields),
 'new_accepted_original_CODE_B':0,'whole_original_exact':False,
 'normal_whole_Cpp_trials':rows},indent=2)+'\n')
assert len(rows)==11
assert rows[0]['whole_source_B']==171 and rows[0]['native_nonfield_equal_B']==108
print('F1034',len(rows),'whole Archive genuine return value controls complete; exact flag per candidate in ignored verified-summary.json.')
