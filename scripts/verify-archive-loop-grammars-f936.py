#!/usr/bin/env python3
"""F936 actual original 171B ArchiveCatalog nonvirtual destructor loop controls.

Compile only seven whole C++ original-shaped functions from tracked
probe; pin every original 14 physical PE relocation fields and the
three real saved-local ownership slots. Negative research, no exact
acceptance or 979-unit cold replay.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,subprocess,sys
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f936-archive-loop-grammars';OUT.mkdir(parents=True,exist_ok=True)
src=(ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
original_for='for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {'
assert src.count(original_for)==1
cases={
 'baseline':src,
 'postfix-for':src.replace(original_for,
    'for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); index++) {'),
 'reversed-comparison':src.replace(original_for,
    'for (unsigned int index=0; g_ArchiveNamesAt0068BE1C.Size()>index; ++index) {'),
 'signed-index':src.replace(original_for,
    'for (int index=0; index<static_cast<int>(g_ArchiveNamesAt0068BE1C.Size()); ++index) {'),
 'unsigned-while':src.replace(original_for,
    'unsigned int index=0; while (index<g_ArchiveNamesAt0068BE1C.Size()) {').replace(
      '            free(filename);','            free(filename);\n            ++index;',1),
 'filename-const-reference':src.replace('char* filename =',
    'char* const& filename ='),
 'resource-const-delete':src.replace(
    'delete *g_ArchiveResourcesAt0068BE08.At(index)',
    'delete static_cast<ArchiveResourceF343* const&>(*g_ArchiveResourcesAt0068BE08.At(index))'),
}
sp=importlib.util.spec_from_file_location('f936reader',ROOT/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
lo=0x41ce50;original=rd.pe_bytes_at(pe,lo,171)
N=list(D.disasm(original,lo));assert len(N)==51 and N[-1].address+N[-1].size==lo+171
assert N[22].op_str=='dword ptr [ebp - 0xc], eax'
assert N[24].op_str=='dword ptr [ebp - 8], ecx'
assert N[38].op_str=='dword ptr [ebp - 0x10], eax'
# Independent original instruction/field targets; not source-NAME inference.
pe_fields=(
 (10,'DIR32',0x68BE04),(18,'DIR32',0x68BE04),
 (47,'DIR32',0x68BE1C),(52,'REL32',0x41DD50),
 (66,'DIR32',0x68BE08),(71,'REL32',0x41DB40),
 (98,'REL32',0x41D8C0),(119,'DIR32',0x68BE1C),
 (124,'REL32',0x41DDC0),(138,'REL32',0x64169D),
 (148,'DIR32',0x68BE08),(153,'REL32',0x41DCD0),
 (158,'DIR32',0x68BE1C),(163,'REL32',0x41DF50))
for offset,kind,target in pe_fields:
 v=int.from_bytes(original[offset:offset+4],'little',signed=kind=='REL32')
 actual=lo+offset+4+v if kind=='REL32' else v
 assert actual==target,(hex(offset),hex(actual),hex(target))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,source in cases.items():
 cpp,obj=OUT/(tag+'.cpp'),OUT/(tag+'.obj');cpp.write_text(source)
 cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
     cwd=ROOT,env=E,capture_output=True,text=True,timeout=280)
 (OUT/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-800:]
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ')
 I=list(D.disasm(code,0))
 row={'variant':tag,'original_whole_CODE_B':171,
   'compiled_whole_CODE_B':len(code),'whole_original_x86':51,
   'compiled_whole_x86':len(I),'compiled_COFF_fields':len(refs),
   'whole_native_exact':False}
 if len(code)==171 and len(I)==51:
  # Actual source refs must occur at every physical original field.
  fields=sorted((x['offset'],x['type']) for x in refs)
  assert fields==sorted((off,kind) for off,kind,target in pe_fields)
  assert all(r['addend']==0 and r['local_symbol_offset'] is None for r in refs)
  masked={i for r in refs for i in range(r['offset'],r['offset']+4)}
  nonfield=[i for i in range(171) if i not in masked and original[i]!=code[i]]
  assert len(masked)==56 and (171-len(masked))==115
  row.update({'native_real_PE_field_offsets_and_kinds_all_correct':True,
    'source_nonfield_original_bytes_equal':115-len(nonfield),
    'nonfield_wrong_offsets':nonfield,
    'source_local_resource':I[22].op_str,
    'source_local_delete_receiver':I[24].op_str,
    'source_local_filename':I[38].op_str,
    'native_mnemonic_ordinals_correct':sum(a.mnemonic==b.mnemonic for a,b in zip(N,I))})
  # Same original positions, zero addends, known symbol bindings
  # from original constructors, and source external field symbol list.
  symbols=[r['symbol'] for r in sorted(refs,key=lambda r:r['offset'])]
  assert 'g_ArchiveUseCountAt0068BE04' in symbols[0]
  assert 'g_ArchiveUseCountAt0068BE04' in symbols[1]
  assert '_free' in symbols[9]
  assert 'ArchiveNamesF343' in symbols[-1]
 rows.append(row)
 print(tag,'CODE',row['compiled_whole_CODE_B'],'x86',len(I),
   'matching native comparable',row.get('source_nonfield_original_bytes_equal'),
   'native original field positions correct',
   row.get('native_real_PE_field_offsets_and_kinds_all_correct',False),flush=True)
assert len(rows)==7
by={x['variant']:x for x in rows}
for name in ('baseline','postfix-for','resource-const-delete'):
 assert by[name]['source_nonfield_original_bytes_equal']==108
 assert by[name]['native_mnemonic_ordinals_correct']==51
 assert by[name]['source_local_resource']=='dword ptr [ebp - 0x10], eax'
 assert by[name]['source_local_delete_receiver']=='dword ptr [ebp - 0xc], ecx'
 assert by[name]['source_local_filename']=='dword ptr [ebp - 8], eax'
assert by['reversed-comparison']['source_nonfield_original_bytes_equal']==106
assert by['signed-index']['source_nonfield_original_bytes_equal']==107
assert by['filename-const-reference']['source_nonfield_original_bytes_equal']==102
assert by['unsigned-while']['compiled_whole_CODE_B']==169
assert all(x.get('source_nonfield_original_bytes_equal',0)<115 for x in rows)
(OUT/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_ArchiveCatalog':'0x0041CE50',
 'original_whole_CODE_B':171,'original_whole_x86':51,
 'original_fields':[
   {'offset':off,'kind':kind,'original_target':hex(target)}
   for off,kind,target in pe_fields],
 'real_original_saved_resource':'EBP-0x0C',
 'real_original_delete_receiver':'EBP-0x08',
 'real_original_filename':'EBP-0x10',
 'complete_source_variants_tested':len(rows),
 'previous_full_32_source_matrix_saved_local':True,
 'original_whole_exact':False,'new_accepted_original_CODE_B':0,
 'mass_cold_replay':False,'whole_source_results':rows
},indent=2)+'\n')
print('F936 7 native-target-backed entire Archive destructor controls: none correct original 0xC/8/10 real stack permutation, zero whole-function exact credit.')
