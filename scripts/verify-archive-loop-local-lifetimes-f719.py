#!/usr/bin/env python3
"""F719: whole original 171-byte ArchiveCatalog destructor used-loop local grammar.

Cold-compile ONLY a selected entire original small C++ function by default,
or the 12 directly affected used-loop/source hypotheses with --all. Never
interpret a nonnative-size source or changed COM field owner as exact.
Original target PE, all 51 authentic x86 and all 14 real typed fields
are checked; no fake padding locals, EXE patches or 943-unit replay.
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
SOURCE=ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp'
OUT=ROOT/'.analysis/f719-archive-early-loop-verified'
SYMBOL='??1ArchiveCatalogF343@@QAE@XZ'
ADDRESS=0x0041CE50
SIZE=171
NATIVE_X86=51
NATIVE_FIELDS=14
ORIGINAL_SLOTS={22:'dword ptr [ebp - 0xc], eax',
                24:'dword ptr [ebp - 8], ecx',
                38:'dword ptr [ebp - 0x10], eax'}


def need(ok,why):
    if not ok:raise ValueError(why)


def load_reader():
    spec=importlib.util.spec_from_file_location('f719_reader',
                                 ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'pinned PE/COFF reader missing')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=mod
    spec.loader.exec_module(mod)
    return mod


def actual_used_source_cases():
    base=SOURCE.read_text()
    original='''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
    need(base.count(original)==1,'original whole ArchiveCatalog release/delete source changed')
    resource='*g_ArchiveResourcesAt0068BE08.At(index)'
    filename='*g_ArchiveNamesAt0068BE1C.At(index)'
    variants={}
    def insert(name,body,expected_bytes,expected_x86,expected_fields,matching=None,
               behaviorally_equivalent=True):
        need('delete ' in body and 'free(filename)' in body
             and 'g_ArchiveResourcesAt0068BE08.At(index)' in body
             and 'g_ArchiveNamesAt0068BE1C.At(index)' in body,
             f'{name}: actual native borrowed resource and name values must be used')
        variants[name]={'cpp':base.replace(original,body),
          'code_bytes':expected_bytes,'x86':expected_x86,'fields':expected_fields,
          'nonfield_equal':matching,
          'behaviorally_equivalent_candidate':behaviorally_equivalent}
    early='''            char* filename;
            delete '''+resource+''';
            filename = '''+filename+''';
            free(filename);'''
    insert('name-declared-before-delete',early,171,51,14,108)
    insert('name-before-delete-nested',
           '            {\n'+early+'\n            }',171,51,14,108)
    insert('name-declared-before-delete-volatile',early.replace('char* filename;','char* volatile filename;'),171,51,14,108)
    insert('name-declared-before-delete-const-pointer',early.replace('char* filename;','char* filename = 0;'),178,52,14)
    insert('name-declared-inside-resource-block',early.replace('delete '+resource+';','{ delete '+resource+'; }'),171,51,14,108)
    # This is a genuine, executed extra null check; it changes original
    # native control flow and relocation count, so NEGATIVE only.
    insert('name-declared-before-resource-conditional',early.replace('delete '+resource+';',
           'if (g_ArchiveResourcesAt0068BE08.At(index))\n                delete '+resource+';'),
           189,57,16,behaviorally_equivalent=False)
    pointer='''            ArchiveResourceF343* resource = '''+resource+''';
            delete resource;
            char* filename = '''+filename+''';
            free(filename);'''
    insert('resource-named-after-acquire',pointer,177,53,14)
    insert('resource-named-before-acquire',pointer.replace('ArchiveResourceF343* resource = '+resource+';',
           'ArchiveResourceF343* resource;\n            resource = '+resource+';'),177,53,14)
    earlyresource='''            char* filename;
            ArchiveResourceF343* resource;
            resource = '''+resource+''';
            delete resource;
            filename = '''+filename+''';
            free(filename);'''
    insert('name-and-resource-declare-before-delete',earlyresource,177,53,14)
    insert('resource-then-name-declare-before-delete',earlyresource.replace(
           'char* filename;\n            ArchiveResourceF343* resource;',
           'ArchiveResourceF343* resource;\n            char* filename;'),177,53,14)
    entry='''            ArchiveResourceF343** entry = g_ArchiveResourcesAt0068BE08.At(index);
            delete *entry;
            char* filename = '''+filename+''';
            free(filename);'''
    insert('real-resource-entry-pointer',entry,177,53,14)
    insert('real-resource-entry-pointer-name-early',entry.replace(
           '            ArchiveResourceF343** entry',
           '            char* filename;\n            ArchiveResourceF343** entry').replace(
           'char* filename = '+filename+';', 'filename = '+filename+';'),177,53,14)
    need(len(variants)==12,'twelve actual used-native-source lifetime candidates missing')
    return variants


def main():
    all_cases=actual_used_source_cases()
    parser=argparse.ArgumentParser(description=__doc__)
    options=parser.add_mutually_exclusive_group()
    options.add_argument('--case',choices=sorted(all_cases),default=None,
                          help='compile one selected whole 171-byte destructor')
    options.add_argument('--all',action='store_true',
                          help='build only twelve affected complete source hypotheses')
    args=parser.parse_args()
    key=args.case or 'name-declared-before-delete'
    cases=all_cases if args.all else {key:all_cases[key]}
    reader=load_reader()
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(real.disasm(reader.pe_bytes_at(pe,ADDRESS,SIZE),ADDRESS))
    need(len(native)==NATIVE_X86 and sum(x.size for x in native)==SIZE
         and native[-1].mnemonic=='ret'
         and all(native[i].mnemonic=='mov' and native[i].op_str==slot
                 for i,slot in ORIGINAL_SLOTS.items()),
         'real complete original 171-B ArchiveCatalog saved owner locations changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    results=[]
    for name,variant in cases.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(variant['cpp'])
        compiled=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),
             str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=150)
        cpp.with_suffix('.log').write_text(compiled.stdout+compiled.stderr)
        need(compiled.returncode==0,
             f'{name}: native VC7.1 whole destructor source compilation failed: '+compiled.stderr[-350:])
        code,refs=reader.object_function(obj,SYMBOL)
        generated=list(real.disasm(code,0))
        need((len(code),len(generated),len(refs))==(
             variant['code_bytes'],variant['x86'],variant['fields'])
             and len(code)!=0,
             f'{name}: actual full native/source byte/x86/field evidence changed')
        row={'variant':name,'original_entire_CODE_bytes':SIZE,
             'original_authentic_x86_instructions':NATIVE_X86,
             'original_physical_typed_PE_COFF_fields':NATIVE_FIELDS,
             'source_entire_CODE_bytes':len(code),
             'source_entire_x86_instructions':len(generated),
             'source_physical_COFF_fields':len(refs),
             'real_original_semantics_preserved':variant['behaviorally_equivalent_candidate'],
             'original_raw_EBP_owner_roles':ORIGINAL_SLOTS,
             'actual_source_at_original_owner_instructions':{
                  str(i):generated[i].op_str for i in ORIGINAL_SLOTS if i<len(generated)},
             'source_complete_original_function_exact':False,
             'new_accepted_authored_GAME_CODE_bytes':0}
        if len(code)==SIZE:
            need(len(generated)==NATIVE_X86 and len(refs)==NATIVE_FIELDS
                 and all(a.mnemonic==b.mnemonic and a.size==b.size
                         for a,b in zip(native,generated)),
                 f'{name}: source no longer reconstructs authentic complete 51-x86 original shape')
            diff=subprocess.run([str(ROOT/'scripts/repo-python'),
                   str(ROOT/'scripts/compare-coff-function.py'),str(obj),SYMBOL,
                   hex(ADDRESS),str(SIZE),'--json'],
                   cwd=ROOT,text=True,capture_output=True,timeout=115)
            need(diff.stdout.strip() and diff.returncode in (0,1),
                 f'{name}: canonical PE whole typed relocation comparison missing')
            match=json.loads(diff.stdout)
            need(match['result']=='mismatch'
                 and match['matched_comparable_bytes']==variant['nonfield_equal']==108
                 and match['comparable_bytes']==115
                 and len(match['relocations'])==NATIVE_FIELDS
                 and [int(q['offset'],16) for q in match['first_differences']]
                 ==[0x4F,0x52,0x55,0x58,0x60,0x84,0x87],
                 f'{name}: true PE EBP bytes or physical relocations changed')
            row['original_nonrelocation_matched_bytes']=match['matched_comparable_bytes']
            row['original_nonrelocation_comparable_bytes']=115
            (OUT/(name+'-comparison.json')).write_text(diff.stdout)
        results.append(row)
        print(f'F719 {name}: complete native 171B/51 x86/14 fields; '
              f'actual source {len(code)}B/{len(generated)} x86/{len(refs)} fields '
              f'and original {row.get("original_nonrelocation_matched_bytes", "size-mismatch")} '
              'non-COFF bytes matched; NONEXACT.',flush=True)
    (OUT/('summary.json' if args.all else 'summary-'+key+'.json')).write_text(
        json.dumps(results,indent=2)+'\n')
    print('F719: '+str(len(results))+' selected original whole 171-B destructor source trials; '
          'zero accepted exact authored CODE and no all-943-unit replay.')


if __name__=='__main__':
    main()
