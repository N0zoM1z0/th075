"""F609: actual 171B/51-x86 ArchiveCatalog destructor VC7.1 negative controls.

Rebuild ONLY one selected small source TU (`--case`) or the 19 targeted
original-equivalent type/lexical forms. All 14 typed physical COFF fields
and complete original native CODE are compared without claiming exact.
No all-unit cold replay or authored CODE acceptance.
"""
from pathlib import Path
import argparse
import os,sys,json,subprocess,importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f609-archive-source-types';O.mkdir(parents=True,exist_ok=True);base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text();SP=R/'scripts/compare-coff-function.py';spec=importlib.util.spec_from_file_location('r609',SP);m=importlib.util.module_from_spec(spec);sys.modules[spec.name]=m;spec.loader.exec_module(m);pe=m.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
loop='for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index)';release='''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);''';assert base.count(loop)==base.count(release)==1
v={
 'signed-index':base.replace(loop,'for (int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index)'),
 'unsigned-long-index':base.replace(loop,'for (unsigned long index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index)'),
 'signed-long-index':base.replace(loop,'for (long index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index)'),
 'size_t-index':base.replace(loop,'for (size_t index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index)'),
 'signed-unsigned-compare':base.replace(loop,'for (int index=0; (unsigned int)index<g_ArchiveNamesAt0068BE1C.Size(); ++index)'),
 'loop-add-post':base.replace(loop,'for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); index+=1)'),
 'loop-prefix-sub-neg':base.replace(loop,'for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); index = index - (unsigned)-1)'),
 'loop-inequality':base.replace(loop,'for (unsigned int index=0; index!=g_ArchiveNamesAt0068BE1C.Size(); ++index)'),
 'release-scope-innermost':base.replace(release,'{\n'+release+'\n            }'),
 'release-scope-delete':base.replace(release,'''            { delete *g_ArchiveResourcesAt0068BE08.At(index); }
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''),
 'release-scope-name':base.replace(release,'''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            {char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename); }'''),
 'release-void-cast':base.replace('free(filename);','::free(reinterpret_cast<void*>(filename));'),
 'release-double-address':base.replace('free(filename);','::free(*(&filename));'),
 'release-c-style-shortcast':base.replace('char* filename = *g_ArchiveNamesAt0068BE1C.At(index);','char* filename = (char*)*g_ArchiveNamesAt0068BE1C.At(index);'),
 'delete-nested-cast':base.replace('delete *g_ArchiveResourcesAt0068BE08.At(index);','delete (ArchiveResourceF343*)(*g_ArchiveResourcesAt0068BE08.At(index));'),
 'delete-named-pointee-using-member':base.replace('delete *g_ArchiveResourcesAt0068BE08.At(index);','delete (*g_ArchiveResourcesAt0068BE08.At(index));'),
 'delete-const-pointer-cast':base.replace('delete *g_ArchiveResourcesAt0068BE08.At(index);','delete const_cast<ArchiveResourceF343*>(*g_ArchiveResourcesAt0068BE08.At(index));'),
 'char-pointer-constref-then-free':base.replace('char* filename = *g_ArchiveNamesAt0068BE1C.At(index);','char* const filename = *g_ArchiveNamesAt0068BE1C.At(index);'),
 'loop-condition-deref-ref':base.replace('index<g_ArchiveNamesAt0068BE1C.Size()','index<(g_ArchiveNamesAt0068BE1C.Size())'),
}
original=list(d.disasm(m.pe_bytes_at(pe,0x0041CE50,171),0x0041CE50))
assert len(original)==51 and sum(x.size for x in original)==171
assert [original[i].op_str for i in (22,24,38)]==[
  'dword ptr [ebp - 0xc], eax',
  'dword ptr [ebp - 8], ecx',
  'dword ptr [ebp - 0x10], eax']
cli=argparse.ArgumentParser(description=__doc__)
cli.add_argument('--case',choices=sorted(v),help='compile only this changed original 171-byte C++ source')
opt=cli.parse_args()
if opt.case:v={opt.case:v[opt.case]}
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for name,src in v.items():
    cpp=O/(name+'.cpp');obj=cpp.with_suffix('.obj');cpp.write_text(src)
    process=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
         cwd=R,env=env,capture_output=True,text=True,timeout=150)
    cpp.with_suffix('.log').write_text(process.stdout+process.stderr)
    if process.returncode:
        raise ValueError(f'{name}: real VC7.1 small source compiler failed: {process.stderr[-400:]}')
    code,refs=m.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ')
    inst=list(d.disasm(code,0))
    cmp=subprocess.run([str(R/'scripts/repo-python'),str(SP),str(obj),
         '??1ArchiveCatalogF343@@QAE@XZ','0x0041CE50','171','--json'],
         cwd=R,capture_output=True,text=True,timeout=120)
    if not cmp.stdout.strip():raise ValueError(name+': complete original PE/COFF comparison missing')
    j=json.loads(cmp.stdout);cpp.with_suffix('.json').write_text(cmp.stdout)
    if not (len(code)==171 and len(inst)==51 and len(refs)==14
         and j['result']=='mismatch' and j['comparable_bytes']==115
         and j['matched_comparable_bytes'] in (107,108)
         and len(j['relocations'])==14
         and [inst[i].op_str for i in (22,24,38)]==[
            'dword ptr [ebp - 0x10], eax',
            'dword ptr [ebp - 0xc], ecx',
            'dword ptr [ebp - 8], eax']):
        raise ValueError(name+': original native 171/51 x86, local owner, or typed COFF source comparison changed')
    row={'variant':name,'original_source_length':171,'x86_instructions':51,
         'actual_typed_COFF_relocations':14,'whole_original_PE_compared':'mismatch',
         'same_original_nonfield_bytes':j['matched_comparable_bytes'],
         'original_nonfield_comparable_bytes':115,
         'original_EBP_slots_native':['-0xC','-0x8','-0x10'],
         'generated_EBP_slots':['-0x10','-0xC','-0x8'],
         'accepted_original_exact_CODE_bytes':0}
    rows.append(row)
    print(f'F609 {name}: native 171B/51 x86, {j["matched_comparable_bytes"]}/115 '
          'nonfield bytes, 14 authentic COFF; NONEXACT EBP allocation',flush=True)
(O/('summary.json' if not opt.case else f'summary-{opt.case}.json')).write_text(json.dumps(rows,indent=2)+'\n')
print(f'F609 {len(rows)} selected native 171-byte original C++ controls: all nonexact, '
      'zero adopted original whole CODE, no all-unit cold replay.',flush=True)
