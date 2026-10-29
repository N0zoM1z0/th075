#!/usr/bin/env python3
"""F603: entire original 131-instruction action46 in two extra giant fighters.

Cold-rebuild only the selected fighter's ordinary C++ TU, retain prior 23
real game-case grammars and actual complete afterRET switch DATA shape.
Independently read the real original PE, all native action boundaries,
real stage-one projectile policy, 16 typed COFF references and GPR/x87.
The still-nonexact entire giant is never granted split-case CODE credit.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
CASE = ROOT / 'probes/FighterTrajectorySpawn46F603.inc'
OUT = ROOT / '.analysis/f603-fighter-spawn-source'
COHORT = (0x0045DD70, 0x0058AF60)


def need(test, detail):
    if not test:
        raise ValueError(detail)


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    need(spec is not None and spec.loader is not None, f'missing original PE source helper: {path}')
    m = importlib.util.module_from_spec(spec)
    sys.modules[name] = m
    spec.loader.exec_module(m)
    return m


def parse_offset(source):
    match = re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], ax', source)
    need(match is not None, f'original signed-short trajectory store changed: {source}')
    return int(match.group(1), 16)


def real_case(reader, pe, decoder, boss, by, f602):
    address = boss['address']
    first, last = by[0x46], by[0x47]
    need(boss['address'] <= first < last < boss['address'] + boss['size'],
         f'{address:#x}: original native 0x46,0x47 complete fighter boundaries changed')
    native = list(decoder.disasm(reader.pe_bytes_at(pe, first, last-first), first))
    need(last-first == 459 and len(native) == 131 and sum(x.size for x in native) == 459
         and native[10].mnemonic == 'fchs' and native[-1].mnemonic == 'jmp'
         and len([x for x in native if x.mnemonic == 'call']) == 10,
         f'{address:#x}: actual original full 131-instruction action body changed')
    need(native[41].mnemonic == 'cmp' and native[41].op_str.endswith(', 1')
         and native[48].mnemonic == 'movsx' and '+ 0xf0c' in native[48].op_str
         and native[52].mnemonic == 'mov' and '+ 0xf0c' in native[52].op_str
         and native[52].op_str.endswith(', 1')
         and native[55].mnemonic == 'mov' and native[55].op_str.endswith('byte ptr [edx + 0x66]')
         and native[65].mnemonic == 'call' and native[65].op_str == '0x453a70',
         f'{address:#x}: real stage-one signed-char projectile/one-shot flag/source ABI changed')
    kind = int(native[63].op_str, 0)
    side = int(native[53].op_str, 0)
    stage = int(native[68].op_str.rsplit(', ', 1)[-1], 0)
    early = int(native[76].op_str, 0)
    late = int(native[127].op_str, 0)
    need(all(native[i].mnemonic == 'push' for i in (53,56,59,62,63,76,110,113,116,127))
         and (kind,side,stage,early,late) in ((0x3B7,1,3,4,5), (0x3E7,0,2,3,5))
         and all(native[i].op_str == expected for i,expected in
                 ((110,'0x61'),(113,'0x40000000'),(116,'0x16'))),
         f'{address:#x}: native original projectile ID, direction, stage or action-state changed')
    need(native[9].mnemonic == 'fld' and native[15].mnemonic == 'fld'
         and native[69].mnemonic == 'jne' and native[80].mnemonic == 'mov'
         and native[90].mnemonic == 'fcomp' and native[119].mnemonic == 'jmp',
         f'{address:#x}: original stage/motion/return instruction sequence changed')
    lower = f602.x87global(native,21,'fcomp')
    upper = f602.x87global(native,31,'fcomp')
    need((lower, upper) == (0x00657480,0x006590C4)
         and f602.x87global(native,72,'fcomp') == 0x00657480
         and f602.x87global(native,90,'fcomp') == 0x0065782C
         and f602.x87global(native,96,'fmul') == 0x00657888
         and f602.x87global(native,102,'fmul') == 0x00657888,
         f'{address:#x}: actual native original 131-case x87 call/global constants changed')
    minimum = f602.intop(native[26].op_str)
    maximum = f602.intop(native[36].op_str)
    need((minimum, maximum) == (0x40000000,0x41400000),
         f'{address:#x}: native 2f..12f original projectile speed clamps changed')
    first_short = parse_offset(native[99].op_str)
    last_short = parse_offset(native[105].op_str)
    need(first_short==0xF00 and last_short == 0xF02,
         f'{address:#x}: native original 16-bit two-word trajectory member positions differ')
    destinations = {
         (index + (27 if index>=39 else 0)): value
         for index,value in f602.TARGETS.items()
    }
    destinations[21]=lower
    destinations[31]=upper
    destinations[65]=0x00453A70
    need(len(destinations)==16, 'native F602 authentic fields lost one original spawn call')
    for index, dest in destinations.items():
        ins=native[index]
        if ins.mnemonic=='call':
            need(ins.op_str == f'0x{dest:x}',
                 f'{address:#x}: native original game/CRT callback destination incorrect at {index}')
        else:
            need(f602.x87global(native,index,ins.mnemonic)==dest,
                 f'{address:#x}: actual native physical global destination incorrect at {index}')
    return native, {
        'original_handler':f'0x{first:08X}',
        'native_original_CODE_bytes':459,
        'native_x86_instructions':131,
        'native_initial_speed_minimum':hex(minimum),
        'native_initial_speed_maximum':hex(maximum),
        'native_original_lower_global':hex(lower),
        'native_original_upper_global':hex(upper),
        'native_stage_comparison':stage,
        'native_early_aux_state':early,
        'native_late_aux_state':late,
        'actual_native_counter_offset':first_short,
        'projectile_id':kind,
        'projectile_side':side,
        'original_one_shot_flag':0xF0C,
        'native_original_COFF_targets':destinations,
    }


def source_for(address,boss,report,mapped,reader,pe,decoder,f602,f598,f567,info):
    raw=f602.create_source(address,boss,report,mapped,reader,pe,decoder,f598,f567,info)
    decl=f'class FighterSwitchF598_Boss{address:08X} {{ public:'
    need(raw.count(decl)==1,
         f'{address:#x}: source native fighter declaration no longer matches')
    raw=raw.replace(decl,decl+' void SpawnDirectedAt453A70(int,int,int,char,int);')
    marker='#include "FighterTrajectoryContact46F602.inc"'
    need(raw.count(marker)==1, f'{address:#x}: original 104-insn source marker unexpectedly missing')
    replacement=(f'#define TRAJECTORY_SPAWN_KIND 0x{info["projectile_id"]:X}\n'
                 f'#define TRAJECTORY_SPAWN_SIDE {info["projectile_side"]}\n'
                 '#include "FighterTrajectorySpawn46F603.inc"\n'
                 '#undef TRAJECTORY_SPAWN_KIND\n'
                 '#undef TRAJECTORY_SPAWN_SIDE')
    raw=raw.replace(marker,replacement)
    return raw


def compare_new_action(reader,pe,decoder,f598,f602,actual,code,refs,boss,info):
    addr=boss['address']
    instructions=[]
    for x in decoder.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    need(instructions and instructions[-1].mnemonic=='ret',f'{addr:#x}: no genuine final giant-source RET')
    ret=instructions[-1].address+instructions[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original complete afterRET DATA physical extent changed')
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(sparse[0x46-0x33]==11 and sparse[0x47-0x33]==12,
         f'{addr:#x}: physical original second-sparse-case mapping changed')
    native_dense=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
                  for i in (11,12)]
    need(native_dense==[int(info['original_handler'],16),int(info['original_handler'],16)+459],
         f'{addr:#x}: native real case0x46/47 handler bounds did not match source')
    locations=[]
    for slot in (11,12):
        offset=ret+44+4*slot
        matched=[r for r in refs if r['offset']==offset]
        need(len(matched)==1 and matched[0]['type']=='DIR32'
             and matched[0]['addend']==0 and matched[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: actual afterRET case{slot} COFF target no longer physically present')
        locations.append(matched[0]['local_symbol_offset'])
    start,end=locations
    generated=list(decoder.disasm(code[start:end],start))
    need(len(actual)==len(generated)==131 and end-start==459
         and sum(x.size for x in generated)==459,
         f'{addr:#x}: candidate natural 131-instruction entire action case size changed')
    lhs,rhs=f598.normalized(actual),f598.normalized(generated)
    bad=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b]
    need(not bad and all(x.size==y.size for x,y in zip(actual,generated)),
         f'{addr:#x}: real source 131 x86 GPR/x87/CFG roles/widths differ: {bad[:5]}')
    fields=[r for r in refs if start<=r['offset']<end]
    targets=info['native_original_COFF_targets']
    need(len(fields)==len(targets)==16,
         f'{addr:#x}: missing physical 131-case target/call relocation fields')
    symbol_targets={
      0x00453A70:'SpawnDirectedAt453A70',
      0x00657480:'g_StopThresholdAt00657480',
      0x006590C4:'g_TrajectoryUpperAt006590C4',
      **f602.ALL_SYMBOLS,
    }
    for index,dest in targets.items():
        a,b=actual[index],generated[index]
        need(a.mnemonic==b.mnemonic,f'{addr:#x}: native call/float ordinal{index} moved')
        row=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(row)==1 and row[0]['type']==('REL32' if b.mnemonic=='call' else 'DIR32')
             and row[0]['addend']==0 and row[0]['local_symbol_offset'] is None
             and symbol_targets[dest] in row[0]['symbol'],
             f'{addr:#x}: wrong source original native 16-byte physical PE/COFF target {index}: {row}')
    return {'native_original_CODE_bytes':459, 'complete_native_x86_GPR_x87_CFG_roles':131,
            'native_typed_real_COFF_fields':16,
            'actual_native_spawn_callee': '0x00453A70',
            'actual_native_one_shot_flag':'+0xF0C',
            'whole_fighter_exact':False}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original 131-instruction fighter; default 2 selected original giants')
    opts=parser.parse_args()
    f602=load('f603_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f603_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f603_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f603_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    reader=load('f603_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f603_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f603_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f603_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f603_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    registered={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    selected=[int(opts.boss,0)] if opts.boss else list(COHORT)
    need(all(x in COHORT for x in selected),'selected boss does not have native 131-instruction trajectory policy')
    source=CASE.read_text()
    need(source.count('case 0x46:')==1 and source.count('SpawnDirectedAt453A70(')==1
         and source.count('I16(0xF0C)')==2
         and 'POS54 = *(&POS54) + *(&F32(0x98));' in source
         and 'static_cast<short>((POS54) * g_ContactProjectionAt00657888)' in source,
         'original native positive spawn source/lvalue ordering unexpectedly changed')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=registered[addr]
        report,mapped=actions.report_boss(reader,pe,dec,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native,info=real_case(reader,pe,dec,boss,by,f602)
        src=source_for(addr,boss,report,mapped,reader,pe,dec,f602,f598,f567,info)
        cpp=OUT/f'Boss{addr:08X}-24-game-cases-with-native-spawn.cpp'
        obj=OUT/f'Boss{addr:08X}-24-game-cases-with-native-spawn.obj'
        cpp.write_text(src)
        compile=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compile.log').write_text(compile.stdout+compile.stderr)
        need(compile.returncode==0,f'{addr:#x}: original native VC7.1 compile failed: {compile.stderr[-650:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        previous=f600.compare_candidate(reader,pe,dec,f598,core,zero,switch,boss,report,mapped,code,refs)
        found=compare_new_action(reader,pe,dec,f598,f602,native,code,refs,boss,info)
        rows.append({'whole_original_fighter':f'0x{addr:08X}',
                     'whole_native_CODE_still_nonexact':boss['size'],
                     'source_prior_23_cases_retained':previous['additional_native_case_x86_roles']==701,
                     'real_afterRET_owner_DATA_bytes':boss['postret_size'],
                     'original_native_trajectory_and_spawn':info,
                     'complete_original_new_internal_case':found,
                     'accepted_whole_native_functions':0})
        print(f'F603 {addr:#010x}: real original 459/459-byte 131/131-role stage1 spawn '
              f'(type 0x{info["projectile_id"]:X}, side {info["projectile_side"]}), '
              '16/16 genuine physical PE/COFF targets, previous 23 cases retained; '
              'WHOLE original giant NONEXACT',flush=True)
    outfile=OUT/('summary.json' if not opts.boss else f'summary-{selected[0]:08X}.json')
    outfile.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F603 {len(rows)} original 131-instruction giant cases: '
          f'{len(rows)*131} native x86 roles /{len(rows)*459} uncredited internal CODE bytes /'
          f'{len(rows)*16} genuine PE-targeted COFF fields; '
          'zero additional whole exact game functions and no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F603 true TH075 native projectile case failed:',exc,file=sys.stderr)
        raise SystemExit(1)
