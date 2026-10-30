"""F723: full original authored ArchiveCatalog 171-B /51-x86 function loop CFG.

Test naturally equivalent `for`, `while`, explicit unsigned guard/break,
post/pre-increment, conditional order. Every source truly deletes the
resource then frees the borrowed filename, with original clear calls.
No inserted fake locals, native byte grafts, cropped loop/code or
943-unit cold replay.
"""
from pathlib import Path
import argparse,importlib.util,sys,os,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];P=R/'.analysis/f723-archive-loop-control/verified';P.mkdir(parents=True,exist_ok=True)
base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
original='''        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);
        }'''
assert base.count(original)==1
body='''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
size='g_ArchiveNamesAt0068BE1C.Size()'
variants={
 'for-postincrement':f'''        for (unsigned int index=0; index<{size}; index++) {{\n{body}\n        }}''',
 'for-add-equals':f'''        for (unsigned int index=0; index<{size}; index+=1) {{\n{body}\n        }}''',
 'for-index-plus-one':f'''        for (unsigned int index=0; index<{size}; index=index+1) {{\n{body}\n        }}''',
 'for-reverse-unsigned-order':f'''        for (unsigned int index=0; {size}>index; ++index) {{\n{body}\n        }}''',
 'for-explicit-no-condition':f'''        for (unsigned int index=0;;++index) {{\n            if (index >= {size}) break;\n{body}\n        }}''',
 'for-explicit-reverse-condition':f'''        for (unsigned int index=0;;++index) {{\n            if ({size} <= index) break;\n{body}\n        }}''',
 'while-counter':f'''        unsigned int index=0;\n        while (index<{size}) {{\n{body}\n            ++index;\n        }}''',
 'while-counter-postincrement':f'''        unsigned int index=0;\n        while (index<{size}) {{\n{body}\n            index++;\n        }}''',
 'while-reverse-guard':f'''        unsigned int index=0;\n        while ({size}>index) {{\n{body}\n            ++index;\n        }}''',
 'while-infinite-break':f'''        unsigned int index=0;\n        while (true) {{\n            if (index>={size}) break;\n{body}\n            ++index;\n        }}''',
 'do-infinite-break':f'''        unsigned int index=0;\n        do {{\n            if (index>={size}) break;\n{body}\n            ++index;\n        }} while (true);''',
 'for-guard-continue':f'''        for (unsigned int index=0;;) {{\n            if (index<{size}) {{\n{body}\n                index++;\n            }} else break;\n        }}''',
}
sp=importlib.util.spec_from_file_location('f723_rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd);pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32);native=list(d.disasm(rd.pe_bytes_at(pe,0x0041CE50,171),0x0041CE50))
assert len(native)==51 and sum(x.size for x in native)==171 and native[-1].mnemonic=='ret'
assert native[22].op_str=='dword ptr [ebp - 0xc], eax'
assert native[24].op_str=='dword ptr [ebp - 8], ecx'
assert native[38].op_str=='dword ptr [ebp - 0x10], eax'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
# One selected whole small original by default; `--all` builds ONLY
# these twelve affected native-source loops (never the 943 exact units).
parser=argparse.ArgumentParser(description=__doc__)
select=parser.add_mutually_exclusive_group()
select.add_argument('--case',choices=sorted(variants),default=None)
select.add_argument('--all',action='store_true')
args=parser.parse_args()
which=args.case or 'for-postincrement'
selected=variants if args.all else {which:variants[which]}
rows=[]
for name,loop in selected.items():
 source=base.replace(original,loop);cpp=P/(name+'.cpp');obj=cpp.with_suffix('.obj');cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=140)
 cpp.with_suffix('.log').write_text(cp.stdout+cp.stderr)
 row={'variant':name,'native_whole_original_CODE_B':171,'native_original_x86':51,'original_typed_fields':14,'compiled':cp.returncode==0}
 if cp.returncode:
  row['error']=(cp.stdout+cp.stderr)[-300:];rows.append(row);print(name,'FAILED',row['error'],flush=True);continue
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ');ins=list(d.disasm(code,0))
 assert len(refs)==14,(name,'source generated original-type COFF field count differs')
 row.update({'compiled_whole_CODE_B':len(code),'compiled_whole_x86':len(ins),'source_COFF_fields':len(refs),'same_native_mnemonic_width_positions':sum(a.size==b.size and a.mnemonic==b.mnemonic for a,b in zip(native,ins)),'native_first_18_mnemonics':[x.mnemonic for x in native[:18]],'compiled_first_18_mnemonics':[x.mnemonic for x in ins[:18]],'source_first_EBP_displacements':[ins[i].op_str if i<len(ins) else None for i in (22,24,38)],'native_whole_exact':False})
 if len(code)==171:
  cmp=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/compare-coff-function.py'),str(obj),'??1ArchiveCatalogF343@@QAE@XZ','0x0041CE50','171','--json'],cwd=R,capture_output=True,text=True,timeout=110)
  if cmp.stdout.strip():
   j=json.loads(cmp.stdout);row.update({'original_whole_result':j['result'],'matched_nonfield':j['matched_comparable_bytes'],'comparable_nonfield':j['comparable_bytes'],'native_physical_original_field_checks':len(j['relocations'])})
   expected=106 if name=='for-reverse-unsigned-order' else 108
   assert j['result']=='mismatch' and j['matched_comparable_bytes']==expected and j['comparable_bytes']==115 and len(j['relocations'])==14,(name,'authentic native whole PE/COFF mismatch profile unexpectedly changed')
 rows.append(row);print(name,'whole source',len(code),'bytes',len(ins),'x86',len(refs),'COFF','original matching',row.get('matched_nonfield'),'of',row.get('comparable_nonfield'),'same original mnemonic-width',row['same_native_mnemonic_width_positions'],flush=True)
(P/('summary.json' if args.all else 'summary-'+which+'.json')).write_text(json.dumps(rows,indent=2)+'\n')
print('F723',len(rows),'whole native 171-byte source loop CFG controls checked; no native-exact original whole function and no all-943 cold replay')
