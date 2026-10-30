#!/usr/bin/env python3
"""F733: full original 171-B ArchiveCatalog resource/name/index used owners.

Rebuild ONE complete VC7.1 original-shaped small C++ destructor by
default, or the 22 directly affected full source variants with --all.
All 2/3-field aggregates and lifetime-overlapping union/void*
objects are truly used for native delete/free/unsigned iteration,
never artificial padding. Check authentic original 51 x86/14 real
PE/COFF fields, actual source two extra MOV and resulting 8 fields
shifted by SIX bytes. No cropped comparisons or 943-unit cold replay.
"""
from __future__ import annotations
import argparse
import difflib
import importlib.util
import itertools
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp'
OUT=ROOT/'.analysis/f733-archive-shared-state-verified'
ADDRESS=0x0041CE50
NATIVE_BYTES=171
NATIVE_X86=51
NATIVE_FIELDS=14
SYMBOL='??1ArchiveCatalogF343@@QAE@XZ'
EXPECTED_NATIVE_FIELD_OFFSETS=(10,18,47,52,66,71,98,119,124,138,148,153,158,163)
EXPECTED_SOURCE_FIELD_OFFSETS=(10,18,47,52,66,71,104,125,130,144,154,159,164,169)
EXPECTED_SOURCE_FIELDS=(
 ('DIR32','?g_ArchiveUseCountAt0068BE04'),
 ('DIR32','?g_ArchiveUseCountAt0068BE04'),
 ('DIR32','?g_ArchiveNamesAt0068BE1C'),
 ('REL32','?Size@ArchiveNamesF343'),
 ('DIR32','?g_ArchiveResourcesAt0068BE08'),
 ('REL32','?At@ArchiveResourcesF343'),
 ('REL32','??_GArchiveResourceF343'),
 ('DIR32','?g_ArchiveNamesAt0068BE1C'),
 ('REL32','?At@ArchiveNamesF343'),
 ('REL32','_free'),
 ('DIR32','?g_ArchiveResourcesAt0068BE08'),
 ('REL32','?Clear@ArchiveResourcesF343'),
 ('DIR32','?g_ArchiveNamesAt0068BE1C'),
 ('REL32','?Clear@ArchiveNamesF343'))


def need(ok,message):
    if not ok:raise ValueError(message)


def load_reader():
    sp=importlib.util.spec_from_file_location('f733_reader',
                                            ROOT/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'pinned native PE reader missing')
    m=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=m
    sp.loader.exec_module(m)
    return m


def real_used_source_variants():
    base=BASE.read_text()
    original='''        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);
        }'''
    old_release='''            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
    guard='    if (--g_ArchiveUseCountAt0068BE04 == 0) {'
    klass='class ArchiveCatalogF343 {public: ~ArchiveCatalogF343();};'
    need(base.count(original)==base.count(old_release)==base.count(guard)==base.count(klass)==1,
         'pinned original whole 171B archive C++ resource/delete/free source changed')
    variants={}
    fields={'index':'unsigned int index;',
            'resource':'ArchiveResourceF343* resource;',
            'filename':'char* filename;'}
    for kind in ('pair','triple'):
        names=('resource','filename') if kind=='pair' else ('index','resource','filename')
        for order in itertools.permutations(names):
            typ='struct F733UsedState { '+' '.join(fields[n] for n in order)+' };'
            for scope in (('loop','guard') if kind=='pair' else ('guard','pre-guard')):
                src=base.replace(klass,typ+'\n'+klass)
                if kind=='pair':
                    body=('''        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            state.resource = *g_ArchiveResourcesAt0068BE08.At(index);
            delete state.resource;
            state.filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(state.filename);
        }''')
                    if scope=='loop':
                        body=body.replace('            state.resource',
                                          '            F733UsedState state;\n            state.resource',1)
                    else:src=src.replace(guard,guard+'\n        F733UsedState state;')
                else:
                    body=('''        for (state.index=0; state.index<g_ArchiveNamesAt0068BE1C.Size(); ++state.index) {
            state.resource = *g_ArchiveResourcesAt0068BE08.At(state.index);
            delete state.resource;
            state.filename = *g_ArchiveNamesAt0068BE1C.At(state.index);
            free(state.filename);
        }''')
                    src=src.replace(guard,('        F733UsedState state;\n'+guard)
                          if scope=='pre-guard' else (guard+'\n        F733UsedState state;'))
                src=src.replace(original,body)
                name=f'{kind}-{"-".join(order)}-{scope}'
                need(src.count('state.resource')==src.count('state.filename')==2
                     and src.count('delete state.resource;')==1
                     and src.count('free(state.filename);')==1,
                     f'{name}: both actual native resource and filename owner fields MUST be used')
                variants[name]=src
    for order in ('res-first','name-first'):
        body=('ArchiveResourceF343* resource; char* filename;' if order=='res-first'
              else 'char* filename; ArchiveResourceF343* resource;')
        union='union F733SequentialBorrowed { '+body+' };'
        for scope in ('loop','guard'):
            src=base.replace(klass,union+'\n'+klass)
            code=('''            owner.resource=*g_ArchiveResourcesAt0068BE08.At(index);
            delete owner.resource;
            owner.filename=*g_ArchiveNamesAt0068BE1C.At(index);
            free(owner.filename);''')
            if scope=='loop':code='            F733SequentialBorrowed owner;\n'+code
            else:src=src.replace(guard,guard+'\n        F733SequentialBorrowed owner;')
            src=src.replace(old_release,code)
            variants[f'union-{order}-{scope}']=src
    for scope in ('loop','guard'):
        src=base
        code=('''            owner=*g_ArchiveResourcesAt0068BE08.At(index);
            delete static_cast<ArchiveResourceF343*>(owner);
            owner=*g_ArchiveNamesAt0068BE1C.At(index);
            free(owner);''')
        if scope=='loop':code='            void* owner;\n'+code
        else:src=src.replace(guard,guard+'\n        void* owner;')
        variants[f'typed-void-owner-{scope}']=src.replace(old_release,code)
    need(len(variants)==22,'all 22 real used resource/filename/index state C++ source models required')
    return variants


def main():
    all_cases=real_used_source_variants()
    parser=argparse.ArgumentParser(description=__doc__)
    choose=parser.add_mutually_exclusive_group()
    choose.add_argument('--case',choices=sorted(all_cases),default=None,
                        help='one entire original-shaped 171B archive destructor source')
    choose.add_argument('--all',action='store_true',
                        help='only the 22 directly affected whole small source variants')
    args=parser.parse_args()
    key=args.case or 'pair-resource-filename-loop'
    cases=all_cases if args.all else {key:all_cases[key]}
    rd=load_reader()
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(d.disasm(rd.pe_bytes_at(pe,ADDRESS,NATIVE_BYTES),ADDRESS))
    need(len(native)==NATIVE_X86 and sum(x.size for x in native)==NATIVE_BYTES
         and native[-1].mnemonic=='ret'
         and native[22].op_str=='dword ptr [ebp - 0xc], eax'
         and native[24].op_str=='dword ptr [ebp - 8], ecx'
         and native[38].op_str=='dword ptr [ebp - 0x10], eax'
         and native[29].mnemonic==native[41].mnemonic=='call'
         and native[29].op_str=='0x41d8c0'
         and native[41].op_str=='0x64169d',
         'actual original native 171B/51x86 and three used temporary EBP slots changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    results=[]
    for name,src in cases.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(src)
        cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
                cwd=ROOT,env=env,capture_output=True,text=True,timeout=160)
        cpp.with_suffix('.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,
             f'{name}: pinned VC7.1 complete original destructor compile failed {cp.stderr[-400:]}')
        code,refs=rd.object_function(obj,SYMBOL)
        gen=list(d.disasm(code,0))
        need(len(code)==177 and len(gen)==53 and len(refs)==NATIVE_FIELDS,
             f'{name}: actual compiler full 177B/53x86/14 PE source owner negative changed')
        off=tuple(x['offset'] for x in refs)
        need(off==EXPECTED_SOURCE_FIELD_OFFSETS
             and all(r['type']==typ and sym in r['symbol']
                     and r['addend']==0 and r['local_symbol_offset'] is None
                     for r,(typ,sym) in zip(refs,EXPECTED_SOURCE_FIELDS)),
             f'{name}: all native original target/source PE reference types and full positions changed')
        edits=tuple((tag,a,b,c,e) for tag,a,b,c,e
                  in difflib.SequenceMatcher(a=[x.mnemonic for x in native],
                       b=[x.mnemonic for x in gen],autojunk=False).get_opcodes()
                  if tag!='equal')
        need(edits==(('insert',21,21,21,23),)
             and gen[21].mnemonic==gen[22].mnemonic=='mov'
             and all(gen[i+2].mnemonic==native[i].mnemonic for i in range(21,51)),
             f'{name}: original scalar delete now has a different real two-extra-MOV compiler source expansion')
        # Native 14 entries at 10/18/.../163; generated fields 7-14
        # move +6 bytes. Matching counts and types never establish exactness.
        for i,(native_offset,compiled_offset) in enumerate(zip(
                EXPECTED_NATIVE_FIELD_OFFSETS,EXPECTED_SOURCE_FIELD_OFFSETS)):
            need(compiled_offset-native_offset==(0 if i<6 else 6),
                 f'{name}: real original COFF field shift no longer +6 after scalar delete')
        result={'model':name,
          'original_whole_authored_CODE_B':NATIVE_BYTES,
          'original_full_native_x86':NATIVE_X86,
          'original_typed_PE_COFF_fields':NATIVE_FIELDS,
          'source_complete_CODE_B':len(code),
          'source_complete_x86':len(gen),
          'source_typed_PE_COFF_fields':len(refs),
          'actual_compiler_extra_two_MOV_instructions':list(edits),
          'native_full_original_PE_field_offsets':EXPECTED_NATIVE_FIELD_OFFSETS,
          'compiler_full_COFF_field_offsets':EXPECTED_SOURCE_FIELD_OFFSETS,
          'exact_same_source_target_and_type_identities_not_offsets':True,
          'original_real_EBP_slot_stores':{str(i):native[i].op_str for i in (22,24,38)},
          'current_source_machine_stores_at_native_ordinals':{
                      str(i):gen[i].op_str for i in (22,24,38)},
          'original_whole_GAME_function_byte_exact':False,
          'new_accepted_GAME_FUNCTION_CODE_B':0}
        results.append(result)
        print(f'F733 {name}: native entire 171B/51 x86/14 fields; '
              'C++ 177B/53 x86/14 fields, TWO real extra MOV, '
              'last 8 native field offsets shift +6. NONEXACT.',flush=True)
    (OUT/('summary.json' if args.all else 'summary-'+key+'.json')).write_text(
          json.dumps(results,indent=2)+'\n')
    print(f'F733 {len(results)} real used small original 171B owner state variants; '
          'zero complete native byte-exact CODE, no all-unit cold replay.')


if __name__=='__main__':
    main()
