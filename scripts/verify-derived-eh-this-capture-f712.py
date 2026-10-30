#!/usr/bin/env python3
"""F712: six complete 73-B original native EH derived-destructor C++ hypotheses.

Only a selected native 0061A453 whole small function is tested by
default; --all builds these six genuinely used cleanup/catch/this
capture alternatives. Original source provenance remains UNKNOWN.
No fake locals, native byte grafts, accepted whole CODE or all-unit replay.
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
OUT=ROOT/'.analysis/f712-derived-EH-this-capture-verified'
ADDRESS=0x0061A453
NATIVE_CODE=73
NATIVE_X86=23
SYMBOL='??1SDKDerivedOwnerF688@@UAE@XZ'
HEADER='''// Original native EH derived destructor, source owner still unknown.
#include <stdlib.h>
extern "C" void __cdecl AdditionalCleanupAt619172();
class SDKBaseOwnerF688 { public: virtual ~SDKBaseOwnerF688(); };
class SDKDerivedOwnerF688: public SDKBaseOwnerF688 {
public: virtual ~SDKDerivedOwnerF688();
};
'''
ORIGINAL_USED_FREE='''    void* resource=*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+0x106C);
    if(resource) ::free(resource);'''
CATCH_RELEASE='''if (*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+0x106C))
            ::free(*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+0x106C));'''


def need(ok,msg):
    if not ok:raise ValueError(msg)


def reader():
    spec=importlib.util.spec_from_file_location('f712_reader',
                                    ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'original PE reader absent')
    m=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=m
    spec.loader.exec_module(m)
    return m


def candidates():
    prefix='SDKDerivedOwnerF688::~SDKDerivedOwnerF688()'
    free=ORIGINAL_USED_FREE
    release=CATCH_RELEASE
    variants={
      'body-try-resource-catch-rethrow':(
           '{\n    try { AdditionalCleanupAt619172(); }\n'
           '    catch(...) { '+release+' throw; }\n'+free+'\n}',69,22,7),
      'body-try-resource-catch-swallow':(
           '{\n    try { AdditionalCleanupAt619172(); }\n'
           '    catch(...) { '+release+' }\n'+free+'\n}',39,13,4),
      'body-try-free-catch-resource':(
           '{\n    AdditionalCleanupAt619172();\n'
           '    void* resource=*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+0x106C);\n'
           '    try { if(resource) ::free(resource); }\n'
           '    catch(...) { '+release+' throw; }\n}',69,22,7),
      'function-try-this-release':(
           'try {\n    AdditionalCleanupAt619172();\n'+free+'\n}\n'
           'catch(...) { '+release+' throw; }',107,39,9),
      'function-try-this-assert':(
           'try {\n    AdditionalCleanupAt619172();\n'+free+'\n}\n'
           'catch(...) { if(*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+0x106C)) throw; }',91,35,8),
      'body-try-scope-this-through-release':(
           '{\n    try {\n      AdditionalCleanupAt619172();\n'
           '      void* resource=*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+0x106C);\n'
           '      if(resource) ::free(resource);\n'
           '    } catch(...) { '+release+' throw; }\n}',69,22,7)}
    return {name:(HEADER+prefix+' '+body+'\n',size,x86,fields)
            for name,(body,size,x86,fields) in variants.items()}


def main():
    all_cases=candidates()
    cli=argparse.ArgumentParser(description=__doc__)
    opts=cli.add_mutually_exclusive_group()
    opts.add_argument('--case',choices=sorted(all_cases),default=None,
                      help='compile one whole original-shaped 73-byte destructor')
    opts.add_argument('--all',action='store_true',
                      help='compile only the six complete source EH/catch hypotheses')
    args=cli.parse_args()
    select=all_cases if args.all else {args.case or 'body-try-resource-catch-rethrow':
                                      all_cases[args.case or 'body-try-resource-catch-rethrow']}
    rd=reader()
    pe=rd.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    original=list(dec.disasm(rd.pe_bytes_at(pe,ADDRESS,NATIVE_CODE),ADDRESS))
    need(len(original)==NATIVE_X86 and sum(x.size for x in original)==NATIVE_CODE
         and [(original[i].mnemonic,original[i].op_str) for i in (0,1,5,7,8,13,17,20,21,22)]
         ==[('mov','eax, 0x656b2c'),('call','0x6425a4'),
            ('mov','dword ptr [ebp - 0x10], esi'),('and','dword ptr [ebp - 4], 0'),
            ('call','0x619172'),('call','0x640f15'),('call','0x61535a'),
            ('mov','dword ptr fs:[0], ecx'),('leave',''),('ret','')],
         'original complete 73-B native EH frame and cleanup control drift')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for name,(source,expected_bytes,expected_ins,expected_refs) in select.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(source)
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/O1','/GX','/Ob0','/Gy','/GR-','/GS','/Zi'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=160)
        cpp.with_suffix('.log').write_text(result.stdout+result.stderr)
        need(result.returncode==0,
             f'{name}: pinned VC7.1 entire derived EH destructor compile failed: {result.stderr[-420:]}')
        code,refs=rd.object_function(obj,SYMBOL)
        ins=list(dec.disasm(code,0))
        need(len(code)==expected_bytes and len(ins)==expected_ins
             and len(refs)==expected_refs and len(code)!=NATIVE_CODE,
             f'{name}: actual source entire 73-B native EH source geometry differs from proof')
        row={'case':name,'original_whole_CODE_bytes':NATIVE_CODE,
             'original_native_x86':NATIVE_X86,
             'compiler_whole_CODE_bytes':len(code),
             'compiler_complete_x86':len(ins),
             'source_physical_typed_COFF_fields':len(refs),
             'source_real_EH_entry':[(x.mnemonic,x.op_str) for x in ins[:5]],
             'actual_original_EH_saved_this':'EBP-0x10',
             'whole_native_PE_exact':False,
             'original_provenance':'unknown',
             'new_accepted_authored_CODE_bytes':0}
        rows.append(row)
        print(f'F712 {name}: true original native 73 B/23 x86; '
              f'actual C++ {len(code)} B/{len(ins)} x86/{len(refs)} fields, '
              'original EH stack-lifetime still NONEXACT, unknown source owner.',flush=True)
    (OUT/('summary.json' if args.all else 'summary-'+next(iter(select))+'.json')).write_text(
        json.dumps(rows,indent=2)+'\n')
    print(f'F712 {len(rows)} whole original-derived destructor C++ contexts; '
          'no source-owned game acceptance and no full replay.')


if __name__=='__main__':
    main()
