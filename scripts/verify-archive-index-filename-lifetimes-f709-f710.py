#!/usr/bin/env python3
"""F709/F710 whole original 171B ArchiveCatalog destructor used-local controls.

Freshly compile just one selected whole C++ original-shaped destructor by
DEFAULT, or the 12 actually affected meaningful source alternatives with
--all. Verify original Japanese TH075 1.11 PE, all 14 native typed PE/COFF
fields and 51 native x86. A real 108/115 or 102/115 nonfield byte match
is a negative, not exact function acceptance. Never replay all 943 units.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f709-f710-archive-full-negative'
SOURCE=ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp'
SYMBOL='??1ArchiveCatalogF343@@QAE@XZ'
ADDRESS=0x0041CE50
NATIVE_BYTES=171
NATIVE_X86=51
NATIVE_FIELDS=14
ORIGINAL_RAW_EBP={22:'dword ptr [ebp - 0xc], eax',
                  24:'dword ptr [ebp - 8], ecx',
                  38:'dword ptr [ebp - 0x10], eax'}


def need(ok,why):
    if not ok:raise ValueError(why)


def load_reader():
    path=ROOT/'scripts/compare-coff-function.py'
    spec=importlib.util.spec_from_file_location('f709_f710_reader',path)
    need(spec is not None and spec.loader is not None,'original PE reader unavailable')
    m=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=m
    spec.loader.exec_module(m)
    return m


def candidates():
    base=SOURCE.read_text()
    original='''        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
    guard='    if (--g_ArchiveUseCountAt0068BE04 == 0) {'
    need(base.count(original)==base.count(guard)==1,
         'actual original game list destructor source/declaration context changed')
    cases={}
    for where in ('inside-guard','before-guard'):
        for order in ('name-index','index-name','name-only','index-only'):
            fname='char* filename; ' if 'name' in order else ''
            idx='unsigned int index; ' if 'index' in order else ''
            decl=(idx+fname) if order=='index-name' else fname+idx
            need(bool(decl),'real local source declaration absent')
            loop='for (index=0;' if idx else 'for (unsigned int index=0;'
            body=original.replace('for (unsigned int index=0;',loop)
            body=body.replace('char* filename = *g_ArchiveNamesAt0068BE1C.At(index);',
                 ('filename = ' if fname else 'char* filename = ')+'*g_ArchiveNamesAt0068BE1C.At(index);')
            src=base.replace(original,body)
            src=src.replace(guard,
                (guard+'\n        '+decl if where=='inside-guard'
                 else '    '+decl+'\n'+guard))
            name='F709-'+where+'-'+order
            cases[name]=(src,102 if fname and not idx else 108)
    structanchor='class ArchiveCatalogF343 {public: ~ArchiveCatalogF343();};'
    need(base.count(structanchor)==1,'original class destructor declaration missing')
    for order in ('index-filename','filename-index'):
        record=('unsigned int index; char* filename;' if order=='index-filename'
                else 'char* filename; unsigned int index;')
        decl='struct F710ArchiveCleanupState { '+record+' };'
        src=base.replace(structanchor,decl+'\n'+structanchor)
        body='''        for (state.index=0; state.index<g_ArchiveNamesAt0068BE1C.Size(); ++state.index) {
            delete *g_ArchiveResourcesAt0068BE08.At(state.index);
            state.filename = *g_ArchiveNamesAt0068BE1C.At(state.index);
            free(state.filename);'''
        src=src.replace(original,body)
        for where in ('inside-guard','before-guard'):
            scoped=src.replace(guard,(guard+'\n        F710ArchiveCleanupState state;'
                                           if where=='inside-guard'
                                           else '    F710ArchiveCleanupState state;\n'+guard))
            cases['F710-'+order+'-'+where]=(scoped,102 if order=='index-filename' else 108)
    need(len(cases)==12 and all('free(' in src and 'delete *' in src for src,_ in cases.values()),
         'twelve true original used-local controls required')
    return cases


def main():
    all_cases=candidates()
    cli=argparse.ArgumentParser(description=__doc__)
    selection=cli.add_mutually_exclusive_group()
    selection.add_argument('--case',choices=sorted(all_cases),default=None,
                           help='compile one whole original 171-byte destructor source')
    selection.add_argument('--all',action='store_true',
                           help='compile only the 12 original F709/F710 used-local controls')
    args=cli.parse_args()
    if args.all:chosen=all_cases
    else:
        key=args.case or 'F709-inside-guard-name-index'
        chosen={key:all_cases[key]}
    reader=load_reader()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(decoder.disasm(reader.pe_bytes_at(pe,ADDRESS,NATIVE_BYTES),ADDRESS))
    need(len(native)==NATIVE_X86 and sum(x.size for x in native)==NATIVE_BYTES
         and all(native[i].mnemonic=='mov' and native[i].op_str==operand
                 for i,operand in ORIGINAL_RAW_EBP.items())
         and native[-1].mnemonic=='ret',
         'native whole original 171-byte ArchiveCatalog extent/real EBP owner changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    # The real serial VC7.1 workflow uses no graphics drivers.
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    results=[]
    for name,(source,expected) in chosen.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(source)
        compiler=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                                 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
                                 cwd=ROOT,env=env,capture_output=True,text=True,timeout=160)
        cpp.with_suffix('.log').write_text(compiler.stdout+compiler.stderr)
        need(compiler.returncode==0,
             f'{name}: selected whole native destructor compiler failed: {compiler.stderr[-400:]}')
        code,refs=reader.object_function(obj,SYMBOL)
        generated=list(decoder.disasm(code,0))
        need(len(code)==NATIVE_BYTES and len(generated)==NATIVE_X86
             and all(a.size==b.size and a.mnemonic==b.mnemonic for a,b in zip(native,generated))
             and len(refs)==NATIVE_FIELDS,
             f'{name}: source no longer has authentic whole original 171/51/14 geometry')
        comparison=subprocess.run([str(ROOT/'scripts/repo-python'),
                                   str(ROOT/'scripts/compare-coff-function.py'),
                                   str(obj),SYMBOL,hex(ADDRESS),str(NATIVE_BYTES),'--json'],
                                  cwd=ROOT,text=True,capture_output=True,timeout=120)
        need(comparison.stdout.strip() and comparison.returncode in (0,1),
             f'{name}: original PE native whole relocation-aware byte comparison failed')
        full=json.loads(comparison.stdout)
        need(full['result']=='mismatch'
             and full['matched_comparable_bytes']==expected
             and full['comparable_bytes']==115
             and len(full['relocations'])==NATIVE_FIELDS
             and len(full['first_differences'])==115-expected
             and all(int(f['object_addend'],16)==0 for f in full['relocations']),
             f'{name}: original whole PE native typed fields or raw EBP negatives changed')
        if expected==108:
            need([int(f['offset'],16) for f in full['first_differences']]
                 ==[0x4F,0x52,0x55,0x58,0x60,0x84,0x87],
                 f'{name}: actual seven native EBP stack-byte positions differ from known originals')
        result={'case':name,'original_whole_CODE_bytes':NATIVE_BYTES,
                'source_whole_CODE_bytes':len(code),'native_and_compiled_x86':NATIVE_X86,
                'all_original_real_PE_COFF_fields':NATIVE_FIELDS,
                'original_nonrelocation_bytes_equal':expected,
                'original_comparable_nonrelocation_bytes':115,
                'source_original_three_EBP_store_operands':[generated[i].op_str for i in (22,24,38)],
                'original_whole_function_exact':False,'accepted_new_game_CODE_bytes':0}
        results.append(result)
        (OUT/(name+'-comparison.json')).write_text(comparison.stdout)
        print(f'{name}: original full 171B/51-x86/14 typed PE fields; '
              f'{expected}/115 original nonfield bytes equal, native three EBP slots '
              'still NONEXACT; no complete game function credit.',flush=True)
    (OUT/('summary.json' if args.all else 'summary-'+next(iter(chosen))+'.json')).write_text(
        json.dumps(results,indent=2)+'\n')
    print(f'F709/F710 {len(results)} selected whole 171-byte native C++ controls; '
          'no original byte-exact accepted function and no all-943-unit replay.')


if __name__=='__main__':
    main()
