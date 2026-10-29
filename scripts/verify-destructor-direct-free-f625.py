#!/usr/bin/env python3
"""F625: actual native small authored destructor local-lifetime controls.

Freshly compile ONLY one selected whole ArchiveCatalog or SceneObject
C++ destructor translation unit; original registered native whole
functions 171B/51-x86, 248B/75-x86 remain NONEXACT. Direct freeing
from genuine game source avoids preallocating named CRT pointer locals
and recovers genuine deletion EBP stack slots, but drops exactly 2 or
6 original x86 pointer save/reload instructions. No artificial padding,
manual native byte graft, partial whole exact credit or 943-unit replay.
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
OUT=ROOT/'.analysis/f625-destructor-direct-free'
CASES={
 'archive':{'source':ROOT/'probes/ArchiveCatalogDirectFreeF625.cpp',
            'target':0x0041CE50,'original_bytes':171,'original_x86':51,
            'expected_source_bytes':165,'expected_source_x86':49,
            'symbol':'??1ArchiveCatalogF343@@QAE@XZ','flags':'/GX-',
            'native_slots':{22:'dword ptr [ebp - 0xc], eax',
                            24:'dword ptr [ebp - 8], ecx'},
            'physical_COFF_fields':14},
 'scene':{'source':ROOT/'probes/BattleSceneDirectFreeF625.cpp',
          'target':0x0043B0B0,'original_bytes':248,'original_x86':75,
          'expected_source_bytes':230,'expected_source_x86':69,
          'symbol':'??1BattleSceneF200@@UAE@XZ','flags':'/GX',
          'native_slots':{26:'dword ptr [ebp - 0x14], edx',
                          28:'dword ptr [ebp - 0x10], eax'},
          'physical_COFF_fields':12},
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load_reader():
    path=ROOT/'scripts/compare-coff-function.py'
    spec=importlib.util.spec_from_file_location('f625_reader',path)
    need(spec is not None and spec.loader is not None,'missing pinned original PE comparator')
    m=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=m
    spec.loader.exec_module(m)
    return m


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--which',choices=sorted(CASES),
                        help='cold compile only this affected authored whole destructor')
    opt=parser.parse_args()
    chosen={opt.which:CASES[opt.which]} if opt.which else CASES
    reader=load_reader()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    results=[]
    for name,case in chosen.items():
        target,size=case['target'],case['original_bytes']
        native=list(decoder.disasm(reader.pe_bytes_at(pe,target,size),target))
        need(len(native)==case['original_x86']
             and sum(x.size for x in native)==size,
             f'{name}: pinned original full native destructor physical code extent changed')
        # The original native is authoritative; source is a fully
        # recompiled alternative with fewer instructions, NOT exact.
        cpp=case['source'];obj=OUT/f'{name}-whole-original-shape-negative.obj'
        need(cpp.is_file(),f'{name}: actual plain C++ source missing')
        p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                          '/Od','/Ob0','/Gy','/GR-',case['flags'],'/GS','/Zi'],
                         cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'{name}-compiler.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,
             f'{name}: selected real VC7.1 native-profile C++ compiler failed: {p.stderr[-470:]}')
        code,refs=reader.object_function(obj,case['symbol'])
        generated=list(decoder.disasm(code,0))
        need(len(code)==case['expected_source_bytes']
             and len(generated)==case['expected_source_x86']
             and len(refs)==case['physical_COFF_fields']
             and sum(x.size for x in generated)==len(code),
             f'{name}: natural native direct-free code geometry/physical COFF fields changed')
        for i,operand in case['native_slots'].items():
            need(native[i].mnemonic==generated[i].mnemonic=='mov'
                 and native[i].op_str==generated[i].op_str==operand,
                 f'{name}: original physical texture/resource delete EBP owner at x86{i} not recovered')
        cmd=[str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/compare-coff-function.py'),
             str(obj),case['symbol'],f'0x{target:08X}',str(size),'--json']
        compare=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,timeout=130)
        need(compare.stdout.strip(),f'{name}: original complete function PE comparator returned no JSON')
        full=json.loads(compare.stdout)
        (OUT/f'{name}-original-whole-comparison.json').write_text(compare.stdout)
        need(full['result']=='size-mismatch',
             f'{name}: actual full native destructor mismatch result changed; reevaluate acceptance')
        row={'original_whole_function':f'0x{target:08X}',
             'authored_native_complete_CODE_bytes':size,
             'authored_native_complete_x86':len(native),
             'new_natural_CXX_complete_CODE_bytes':len(code),
             'new_natural_CXX_complete_x86':len(generated),
             'true_source_COFF_reloc_fields':len(refs),
             'two_original_physically_owned_delete_temp_slots_reproduced':True,
             'actual_original_whole_function_comparison':'size-mismatch',
             'original_x86_instructions_missing_in_natural_direct_free':
                 len(native)-len(generated),
             'new_accepted_exact_whole_game_functions':0}
        results.append(row)
        print(f'F625 {name} original {size}B/{len(native)} x86; '
              f'natural direct-free {len(code)}B/{len(generated)} x86, '
              f'{len(refs)} true COFF fields, first two native delete '
              'EBP locals match exactly but WHOLE original NONEXACT.',flush=True)
    out=OUT/('summary.json' if not opt.which else f'summary-{opt.which}.json')
    out.write_text(json.dumps(results,indent=2)+'\n')
    print('F625 native complete authored destructor geometry control: '
          f'{len(results)} affected original source TUs only, zero newly accepted '
          'authored whole CODE bytes, NO all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F625 original native two complete destructor lifetimes failed:',exc,file=sys.stderr)
        raise SystemExit(1)
