#!/usr/bin/env python3
"""F634: three complete original game-facing 14/14/13-byte leaves.

Cold compile ONLY one ordinary VC7.1 C++ source TU, check all original
whole CODE bytes and x86 roles (zero actual PE/COFF relocations), then
independently scan actual direct CALLs across the 4351 registered
original native full function extents. Source provenance UNKNOWN:
never promote any to accepted authored exact match units merely
because original game functions call these leaves.
"""
from __future__ import annotations
import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/GameObjectThisAndNoopLeavesF634.cpp'
OUT=ROOT/'.analysis/f634-game-object-leaf-source'
CASES={
  0x0040D980:('14-byte sprite identity accessor',14,8,
              '?Self@SpriteSelfReferenceF634@@QAEPAV1@XZ',16,14),
  0x0040D9F0:('14-byte atlas identity accessor',14,8,
              '?Self@AtlasSelfReferenceF634@@QAEPAV1@XZ',3,3),
  0x0045B850:('13-byte action-parameter no-op',13,7,
              '?AcceptAction@CharacterNoopActionF634@@QAEXH@Z',14,14),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load_reader():
    spec=importlib.util.spec_from_file_location('f634_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'original native PE reader missing')
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module
    spec.loader.exec_module(module)
    return module


def main():
    reader=load_reader()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/functions.csv').open(newline='') as f:
        all_registered=list(csv.DictReader(f))
    with (ROOT/'config/function-origins.csv').open(newline='') as f:
        origins={x['address']:x for x in csv.DictReader(f)}
    need(len(all_registered)==4351,'original registered native full-function cohort unexpectedly changed')
    for addr in CASES:
        origin=origins[f'0x{addr:08X}']
        need(origin['origin']=='unknown' and origin['disposition']=='review',
             f'{addr:#x}: actual historical source ownership no longer unknown: investigate before any credit')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    obj=OUT/'original-three-whole-leaves.obj'
    build=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(build.stdout+build.stderr)
    need(build.returncode==0,
         f'normal original MSVC VC7.1 whole small-function source build failed: {build.stderr[-450:]}')
    result=[]
    for addr,(label,size,count,symbol,expected_calls,expected_authored) in CASES.items():
        original=reader.pe_bytes_at(pe,addr,size)
        generated,refs=reader.object_function(obj,symbol,expected_size=size)
        ni=list(decoder.disasm(original,addr))
        gi=list(decoder.disasm(generated,addr))
        need(len(original)==len(generated)==size
             and len(ni)==len(gi)==count
             and sum(x.size for x in ni)==sum(x.size for x in gi)==size
             and not refs
             and bytes(generated)==bytes(original)
             and all((x.address,x.mnemonic,x.size,x.op_str)==
                     (y.address,y.mnemonic,y.size,y.op_str)
                     for x,y in zip(ni,gi)),
             f'{addr:#x}: complete original native leaf real linked bytes, no-COFF, x86 roles differ')
        result.append({'native_original_address':f'0x{addr:08X}',
                       'provisional_source_meaning':label,
                       'original_whole_NATIVE_CODE_bytes':size,
                       'actual_complete_original_x86_instructions':count,
                       'physically_original_PE_COFF_fields':0,
                       'entire_original_native_CODE_bytes_identical':True,
                       'original_source_origin':'unknown',
                       'new_accepted_whole_authored_CODE_bytes':0})
        print(f'F634 original {addr:#010x}: entire {size}/{size} machine bytes, '
              f'{count}/{count} native x86, zero actual PE/COFF relocations; '
              'historical author-vs-generated origin UNKNOWN',flush=True)
    # Native direct calls as literal original PE CALL opcodes, not
    # source symbol guesses or decompiler XREFs. Count only registered
    # entire function extents to avoid attributing jump DATA as CODE.
    callers={addr:[] for addr in CASES}
    for row in all_registered:
        addr=int(row['address'],16)
        for ins in decoder.disasm(reader.pe_bytes_at(pe,addr,int(row['size'])),addr):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                dest=int(ins.op_str,16)
                if dest in callers:
                    callers[dest].append({'original_native_call_site':f'0x{ins.address:08X}',
                                          'original_whole_parent_function':row['address'],
                                          'current_parent_origin':row['owner'],
                                          'provisional_parent_name':row['proposed_name']})
    for addr,(_,_,_,_,total,authored) in CASES.items():
        observed=callers[addr]
        authored_count=sum(row['current_parent_origin']=='authored' for row in observed)
        need(len(observed)==total and authored_count==authored,
             f'{addr:#x}: original native game CALL provenance changed: {len(observed)}, {authored_count}')
    summary={'pinned_original_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'pinned_real_original_compiler_profile':'VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi',
             'native_source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'original_registered_native_whole_functions_scanned':len(all_registered),
             'three_complete_original_native_small_game_functions':result,
             'independently_observed_actual_PE_direct_CALLs':{
               f'0x{addr:08X}':observed for addr,observed in callers.items()},
             'accepted_new_authored_whole_functions':0,
             'accepted_new_authored_original_CODE_bytes':0,
             'all_unit_cold_replay_performed':False}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(f'F634 three entire native game-facing leaf source identities: '
          f'{sum(r["original_whole_NATIVE_CODE_bytes"] for r in result)} '
          f'whole original CODE bytes / '
          f'{sum(r["actual_complete_original_x86_instructions"] for r in result)} '
          f'full original x86, true game callers {[len(callers[a]) for a in CASES]}; '
          'historical source ownership still UNKNOWN and ZERO authored exact credit. '
          'No all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F634 complete original TH075 game-facing leaf verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
