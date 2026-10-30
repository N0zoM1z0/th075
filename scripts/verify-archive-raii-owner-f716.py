#!/usr/bin/env python3
"""F716: selected entire 171-byte original archive destructor semantic RAII C++ tests.

One whole native-profile original 0041CE50 source object by default;
--all builds just seven real filename/resource-owner plus forced-inline
compiler controls. All native 51 x86 and 14 original PE fields are read
from original target; generated helper CALL is NOT the original _free.
No native bytes altered, no fake locals, no entire 943-unit replay.
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
SRC=ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp'
OUT=ROOT/'.analysis/f716-archive-semantic-release-verified'
SYMBOL='??1ArchiveCatalogF343@@QAE@XZ'
NATIVE_ADDR=0x0041CE50
NATIVE_BYTES=171
NATIVE_X86=51
NATIVE_TYPED_FIELDS=14


def need(ok,message):
    if not ok:raise ValueError(message)


def load_reader():
    sp=importlib.util.spec_from_file_location('f716_reader',ROOT/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'verified original PE tool absent')
    m=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=m
    sp.loader.exec_module(m)
    return m


def candidates():
    base=SRC.read_text()
    marker='class ArchiveCatalogF343 {public: ~ArchiveCatalogF343();};'
    release='''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
    need(base.count(marker)==base.count(release)==1,
         'original 171-byte nonexact release/delete source no longer present')
    versions={}
    nametype='struct F716NameRelease {char* value; __forceinline ~F716NameRelease() {::free(value);} };'
    namebody='''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            F716NameRelease filename;
            filename.value=*g_ArchiveNamesAt0068BE1C.At(index);'''
    namesource=base.replace(marker,nametype+'\n'+marker).replace(release,namebody)
    versions['name-dtor-Ob0']=(namesource,('/Od','/Ob0','/GX-'),167,49,14,'??1F716NameRelease')
    versions['name-dtor-GX']=(namesource,('/Od','/Ob0','/GX'),212,58,18,'??1F716NameRelease')
    versions['name-dtor-Ob1']=(namesource,('/Od','/Ob1','/GX-'),197,58,15,'??1F716NameRelease')
    typename='struct F716NameRelease {char* value; __forceinline void Release() {::free(value);} };'
    methodbody=namebody+'\n            filename.Release();'
    method=base.replace(marker,typename+'\n'+marker).replace(release,methodbody)
    versions['name-method-Ob0']=(method,('/Od','/Ob0','/GX-'),167,49,14,'?Release@F716NameRelease')
    for kind,ending in [('dtor','~F716ResourceOwner() { delete value; }'),
                        ('method','void Release() { delete value; }')]:
        typ='struct F716ResourceOwner {ArchiveResourceF343* value; __forceinline '+ending+' };'
        body='''            { F716ResourceOwner owner;
                owner.value = *g_ArchiveResourcesAt0068BE08.At(index);'''
        if kind=='method':body+='\n                owner.Release();'
        body+='''
            }
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
        source=base.replace(marker,typ+'\n'+marker).replace(release,body)
        expected='??1F716ResourceOwner' if kind=='dtor' else '?Release@F716ResourceOwner'
        versions['resource-'+kind+'-Ob0']=(source,('/Od','/Ob0','/GX-'),141,43,14,expected)
        if kind=='dtor':
            versions['resource-dtor-Ob1']=(source,('/Od','/Ob1','/GX-'),203,60,15,expected)
    need(len(versions)==7,'expected seven complete original real-release semantic/source controls')
    return versions


def main():
    trials=candidates()
    p=argparse.ArgumentParser(description=__doc__)
    opts=p.add_mutually_exclusive_group()
    opts.add_argument('--case',choices=sorted(trials),default=None,
                      help='compile and inspect one entire 171B source only')
    opts.add_argument('--all',action='store_true',
                      help='compile only the seven relevant complete archive owner C++ controls')
    args=p.parse_args()
    key=args.case or 'name-dtor-Ob0'
    wanted=trials if args.all else {key:trials[key]}
    reader=load_reader()
    pe=reader.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    n=list(dec.disasm(reader.pe_bytes_at(pe,NATIVE_ADDR,NATIVE_BYTES),NATIVE_ADDR))
    need(len(n)==NATIVE_X86 and sum(x.size for x in n)==NATIVE_BYTES
         and n[22].op_str=='dword ptr [ebp - 0xc], eax'
         and n[24].op_str=='dword ptr [ebp - 8], ecx'
         and n[38].op_str=='dword ptr [ebp - 0x10], eax'
         and n[41].mnemonic=='call' and n[41].op_str=='0x64169d'
         and n[-1].mnemonic=='ret',
         'genuine original entire 171-byte destructor and CRT-free owner provenance changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for name,(src,profile,want_bytes,want_ins,want_refs,helper) in wanted.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(src)
        cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              *profile,'/Gy','/GR-','/GS','/Zi'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=150)
        cpp.with_suffix('.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,f'{name}: original-profile whole archive C++ compiler failed: {cp.stderr[-480:]}')
        code,refs=reader.object_function(obj,SYMBOL)
        gen=list(dec.disasm(code,0))
        original_direct_free=any(x['symbol']=='_free' for x in refs)
        real_helper=any(helper in x['symbol'] for x in refs)
        should_inline='/Ob1' in profile
        need((len(code),len(gen),len(refs))==(want_bytes,want_ins,want_refs)
             and len(code)!=NATIVE_BYTES
             and real_helper==(not should_inline)
             and original_direct_free==(should_inline or name.startswith('resource-')),
             f'{name}: actual ABI __forceinline helper inlining/CRT free changed')
        result={'name':name,'native_complete_PE_bytes':NATIVE_BYTES,
             'native_original_x86':NATIVE_X86,
             'original_native_direct_CRT_free_call_address':'0x0064169D',
             'source_real_compiler_flags':list(profile),
             'source_complete_CODE_bytes':len(code),
             'source_complete_x86':len(gen),
             'source_typed_COFF_fields':len(refs),
             'source_RAII_helper_member':helper,
             'source_actual_RAII_helper_call_emitted':real_helper,
             'source_ob1_helper_inlining_diagnostic_not_pinned_native_profile':should_inline,
             'source_direct_CRT_free_still_in_original_function':original_direct_free,
             'original_three_real_EBP_stores':[n[i].op_str for i in (22,24,38)],
             'source_x86_opcodes_with_matching_native_mnemonic_and_width':sum(
                       a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(n,gen)),
             'original_full_function_exact':False,'new_accepted_game_CODE_bytes':0}
        rows.append(result)
        print(f'F716 {name}: original native 171B/51-x86/direct-free, '
              f'whole VC7.1 source {len(code)}B/{len(gen)}-x86/{len(refs)}-fields; '
              f'{helper} call emitted={real_helper}; never exact.',flush=True)
    output=OUT/('summary.json' if args.all else 'summary-'+key+'.json')
    output.write_text(json.dumps(rows,indent=2)+'\n')
    print('F716: '+str(len(rows))+' whole native-shaped game archive RAII source controls; '
          'original complete author function remains NONEXACT. No 943-unit replay.')


if __name__=='__main__':
    main()
