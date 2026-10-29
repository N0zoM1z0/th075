#!/usr/bin/env python3
"""F602: genuine action 0x46 original x87/float→integer trajectory in fighters.

Native 104-instruction action 0x46 is a subrange inside a whole STILL
NONEXACT fighter boss. Regenerate PE-backed prior 23 actions, compile
ONLY the selected VC7.1 C++ translation unit; verify native register
roles, all real typed COFF call/global fields, and full original
physical after-RET jump geometry. No partial/whole exact CODE credit.
"""
from __future__ import annotations

import argparse
from collections import Counter
import importlib.util
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f602-fighter-trajectory-source'
CASE=ROOT/'probes/FighterTrajectoryContact46F602.inc'
SIMPLE=0x46
NEXT=0x47
TARGETS={21:0x00658290,31:0x006592A4,45:0x00657480,51:0x0040FB40,
         63:0x0065782C,69:0x00657888,70:0x006406AC,
         75:0x00657888,76:0x006406AC,80:0x00453E20,
         85:0x0040FAC0,88:0x00453E60,91:0x00453D60,
         94:0x0040FA30,102:0x0040FB40}
LOWER={0x00658290:'g_ApproachLowerAt00658290',
       0x00657480:'g_StopThresholdAt00657480'}
UPPER={0x006592A4:'g_ApproachUpperAt006592A4',
       0x006590C4:'g_TrajectoryUpperAt006590C4'}
ALL_SYMBOLS={0x00657480:'g_StopThresholdAt00657480',
 0x0065782C:'g_ThresholdAt0065782C',
 0x00657888:'g_ContactProjectionAt00657888',
 0x0040FB40:'SetAuxActionAt40FB40',
 0x006406AC:'__ftol2',
 0x00453E20:'ResetAt453E20',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00453E60:'InitTrajectoryAt453E60',
 0x00453D60:'PrepareActionAt453D60',
 0x0040FA30:'GetNativeActionAt40FA30',**LOWER,**UPPER}


def need(ok,detail):
    if not ok:raise ValueError(detail)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing original-PE native verifier: '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def intop(op):
    return int(op.rsplit(', ',1)[-1],0)


def x87global(ins,at,opcode):
    x=ins[at]
    match=re.fullmatch(r'dword ptr \[(0x[0-9a-f]+)\]',x.op_str)
    need(x.mnemonic==opcode and match is not None,
         f'original native x87 global operand {at} differs: {x.mnemonic} {x.op_str}')
    return int(match.group(1),16)


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address'];a,b=by[SIMPLE],by[NEXT]
    size=b-a
    inst=list(decoder.disasm(reader.pe_bytes_at(pe,a,size),a))
    need(size==(485 if addr==0x00564BE0 else 374)
         and len(inst)==104 and sum(x.size for x in inst)==size
         and inst[10].mnemonic=='fchs' and inst[103].mnemonic=='jmp'
         and len([x for x in inst if x.mnemonic=='call'])==9,
         f'{addr:#x}: original native 0x46 complete boundaries, full x86 geometry or calls differ')
    lower=x87global(inst,21,'fcomp')
    upper=x87global(inst,31,'fcomp')
    need(lower in LOWER and upper in UPPER and
         x87global(inst,45,'fcomp')==0x00657480
         and x87global(inst,63,'fcomp')==0x0065782C
         and x87global(inst,69,'fmul')==x87global(inst,75,'fmul')==0x00657888,
         f'{addr:#x}: original full stage trajectory true physical float globals changed')
    minimum,maxspeed=(intop(inst[26].op_str),intop(inst[36].op_str))
    short_stage=intop(inst[41].op_str)
    early=int(inst[49].op_str,0)
    late=int(inst[100].op_str,0)
    need(all(inst[x].mnemonic=='push' for x in (49,83,86,89,100))
         and [int(inst[x].op_str,0) for x in (83,86,89)]==[0x61,0x40000000,0x16]
         and minimum in (0x40000000,0x40C00000)
         and maxspeed in (0x41400000,0x41C80000)
         and short_stage in (1,2,3) and early in (2,3,4)
         and late in (5,6,7,8),
         f'{addr:#x}: original physical game speed/frame/action literals changed')
    # Both x87-to-short results are signed, and each must write to the
    # same real native owner's two adjacent 16-bit trajectory slots.
    offsets=[]
    for index in (72,78):
        x=inst[index]
        match=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], ax',x.op_str)
        need(x.mnemonic=='mov' and match is not None,
             f'{addr:#x}: original x87 __ftol2 word-store source offset {index} differs')
        offsets.append(int(match.group(1),16))
    need(offsets[0] in (0xF00,0xEFC) and offsets[1]==offsets[0]+2,
         f'{addr:#x}: original native adjacent trajectory owner slots changed: {offsets}')
    targets=dict(TARGETS);targets[21]=lower;targets[31]=upper
    for i,expected in targets.items():
        x=inst[i]
        if x.mnemonic=='call':
            need(x.op_str==f'0x{expected:x}',
                 f'{addr:#x}: original native callee physical target at {i} changed')
        else:
            need(x87global(inst,i,x.mnemonic)==expected,
                 f'{addr:#x}: genuine original native float COFF physical target at {i} changed')
    return inst,{
        'original_handler':f'0x{a:08X}',
        'original_native_CODE_bytes':size,
        'native_x86_instructions':len(inst),
        'native_initial_speed_minimum':hex(minimum),
        'native_initial_speed_maximum':hex(maxspeed),
        'native_original_lower_global':hex(lower),
        'native_original_upper_global':hex(upper),
        'native_stage_comparison':short_stage,
        'native_early_aux_state':early,
        'native_late_aux_state':late,
        'actual_native_counter_offset':offsets[0],
        'native_original_COFF_targets':targets,
        'all_unit_replay':False}


def create_source(addr,boss,report,mapped,reader,pe,dec,f598,f567,orig):
    raw=f598.source_with_singleton(f598.original_source(addr,boss,report,mapped,reader,pe,dec,f567),addr)
    first='        case 0x33: g_FighterProbeMarker = 52; break;'
    final='        case 0x46: g_FighterProbeMarker = 71; break;'
    need(raw.count(first)==1 and raw.count(final)==1 and
         'case 0x47: g_FighterProbeMarker' in raw,
         'original fighter second switch source structure changed')
    before,rest=raw.split(first,1)
    after=rest[rest.index(final):]
    counter=orig['actual_native_counter_offset']
    raw=before+(f'#define CONTACT_STAGE_OFFSET 0x{counter:X}\n'
                '#include "FighterAdditionalContactF600.inc"\n'
                '#undef CONTACT_STAGE_OFFSET\n')+after
    marker='class FighterSwitchF598_Boss%08X { public:'%addr
    need(raw.count(marker)==1,'actual original C++ actor declaration changed')
    raw=raw.replace(marker,marker+' void InitTrajectoryAt453E60(float);')
    decl='extern float g_ThresholdAt0065782C;'
    need(raw.count(decl)==1,'fighter physical float global declarations changed')
    raw=raw.replace(decl,decl+'\n'+ '\n'.join('extern float '+v+';' for v in (
      'g_ApproachLowerAt00658290', 'g_ApproachUpperAt006592A4',
      'g_StopThresholdAt00657480','g_TrajectoryUpperAt006590C4',
      'g_ContactProjectionAt00657888')))
    macro='#define POS54'
    need(raw.count(macro)==1,'F32 ordinary native view must be declared once')
    raw=raw.replace(macro,'#define F32(off) (*reinterpret_cast<float*>(RAW+(off)))\n'+macro)
    minfloat=struct.unpack('<f',struct.pack('<I',int(orig['native_initial_speed_minimum'],16)))[0]
    maxfloat=struct.unpack('<f',struct.pack('<I',int(orig['native_initial_speed_maximum'],16)))[0]
    meta={
      'TRAJECTORY_LOWER_THRESHOLD':LOWER[int(orig['native_original_lower_global'],16)],
      'TRAJECTORY_UPPER_THRESHOLD':UPPER[int(orig['native_original_upper_global'],16)],
      'TRAJECTORY_MINIMUM_SPEED':f'{minfloat:.1f}f',
      'TRAJECTORY_MAXIMUM_SPEED':f'{maxfloat:.1f}f',
      'TRAJECTORY_STAGE_THRESHOLD':str(orig['native_stage_comparison']),
      'TRAJECTORY_EARLY_STATE':str(orig['native_early_aux_state']),
      'TRAJECTORY_LATE_STATE':str(orig['native_late_aux_state']),
      'CONTACT_STAGE_OFFSET':f'0x{counter:X}',
    }
    replacement='\n'.join(f'#define {k} {v}' for k,v in meta.items())
    replacement+='\n#include "FighterTrajectoryContact46F602.inc"\n'
    replacement+='\n'.join(f'#undef {k}' for k in meta)+'\n'
    raw=raw.replace(final,replacement)
    return raw


def check_source_case(reader,pe,decoder,f598,actual,code,refs,inst,ret,boss,info):
    addr=boss['address']
    # First 11 entries are the F600 contact bodies. Native true physical
    # second compressed jump table indices 11 and 12 delimit action0x46.
    table=boss['tables'][1]
    need(table['slots']>=13,'original second switch missing native 0x46/0x47')
    dense=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
           for i in range(13)]
    original_start=int(info['original_handler'],16)
    need(dense[11]==original_start and dense[12]==original_start+info['original_native_CODE_bytes'],
         f'{addr:#x}: native original case46/47 owned table boundaries are not true')
    produced=[]
    for i in (11,12):
        off=ret+44+4*i
        match=[r for r in refs if r['offset']==off]
        need(len(match)==1 and match[0]['type']=='DIR32' and
             match[0]['local_symbol_offset'] is not None and match[0]['addend']==0,
             'native source physical COFF case 0x46/0x47 labels lost')
        produced.append(match[0]['local_symbol_offset'])
    start,end=produced
    generated=list(decoder.disasm(code[start:end],start))
    need(len(generated)==len(actual)==104 and end-start==374,
         f'{addr:#x}: full original action46 selected C++ case geometry differs')
    grammar1,grammar2=f598.normalized(actual),f598.normalized(generated)
    bad=[(i,x,y) for i,(x,y) in enumerate(zip(grammar1,grammar2)) if x!=y]
    need(not bad,f'{addr:#x}: original 0x46 full native GPR/x87/CFG differs: {bad[:8]}')
    width=[x.size-y.size for x,y in zip(actual,generated)]
    if addr==0x00564BE0:
        # The original EBP-0x88 frame widens 33 MOV receiver loads by
        # three bytes; three true local conditionals also grow from short
        # Jcc (2 B) to near Jcc (6 B) because the larger original body
        # crosses the x86 signed-rel8 displacement boundary. These are
        # *physical original branch bytes*, not hypothetical padding.
        near_jumps={3,7,66}
        need(width.count(3)==33 and width.count(4)==3 and width.count(0)==68
             and {i for i,x in enumerate(width) if x==4}==near_jumps
             and all(actual[i].mnemonic==generated[i].mnemonic in ('jne','jp') for i in near_jumps),
             'wide native 0x46 original 33 EBP-0x88 receiver loads + 3 real near Jcc differ')
    else:
        need(all(w==0 for w in width),
             f'{addr:#x}: compact original x86 opcode widths wrong for action0x46')
    physical=[r for r in refs if start<=r['offset']<end]
    need(len(physical)==len(info['native_original_COFF_targets'])==15,
         f'{addr:#x}: real source whole native 0x46 COFF field count mismatch')
    true=[]
    for i,expected in info['native_original_COFF_targets'].items():
        x,y=actual[i],generated[i]
        need(x.mnemonic==y.mnemonic,
             f'{addr:#x}: native typed ref instruction ordinal {i} changed')
        found=[r for r in physical if y.address<=r['offset']<y.address+y.size]
        need(len(found)==1 and found[0]['type']==('REL32' if y.mnemonic=='call' else 'DIR32')
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None,
             f'{addr:#x}: genuine original typed native PE/COFF field {i} shifted')
        sym=ALL_SYMBOLS[expected]
        need(sym in found[0]['symbol'],
             f'{addr:#x}: native original x87/CRT/game call {expected:#x} symbol differs at {i}: {found}')
        true.append({'ordinal':i,'type':found[0]['type'],
                     'target':f'0x{expected:08X}','symbol':found[0]['symbol']})
    return {'whole_native_game_action':SIMPLE,'original_104_instruction_roles_equal':True,
            'original_inner_native_CODE_bytes_uncredited':info['original_native_CODE_bytes'],
            'source_inner_CODE_bytes':end-start,
            'real_native_physical_COFF_fields':true,
            'native_wide_saved_this_instructions':width.count(3),
            'native_wide_branch_rel32_expansions':width.count(4),
            'whole_original_fighter_exact':False}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one selected 104-instruction original 0x46 fighter')
    options=parser.parse_args()
    f600=load('f602_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f602_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f602_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    reader=load('f602_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f602_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f602_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f602_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f602_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    need(len(cohort)==len(set(cohort))==11,'native source fighter cohort identity changed')
    # Two fighters have 131 native x86 and extra real spawn policy;
    # never silently substitute the compact 104-insn source there.
    selectable=[a for a in cohort if a not in (0x0045DD70,0x0058AF60)]
    selected=[int(options.boss,0)] if options.boss else selectable
    need(all(a in selectable for a in selected),
         'selected giant has a different original action46: use dedicated spawn-source audit')
    source=CASE.read_text()
    need(source.count('case 0x46:')==1 and
         'POS54 = *(&POS54) + *(&F32(0x98));' in source and
         'static_cast<short>((POS54) * g_ContactProjectionAt00657888)' in source,
         'original natural x87 evaluation order of 104-instruction action changed')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        original,info=original_case(reader,pe,decoder,boss,by)
        source=create_source(addr,boss,report,mapped,reader,pe,decoder,f598,f567,info)
        cpp=OUT/f'Boss{addr:08X}-24-real-game-cases.cpp'
        obj=OUT/f'Boss{addr:08X}-24-real-game-cases.obj'
        cpp.write_text(source)
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,capture_output=True,text=True,env=env,timeout=180)
        (OUT/f'Boss{addr:08X}-compile.log').write_text(result.stdout+result.stderr)
        need(result.returncode==0,
             f'{addr:#x}: original selected actual VC7.1 source failed: {result.stderr[-650:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        previously=f600.compare_candidate(reader,pe,decoder,f598,core,zero,switch,
                                           boss,report,mapped,code,refs)
        inst=[]
        for x in decoder.disasm(code,0):
            inst.append(x)
            if x.mnemonic=='ret':break
        ret=inst[-1].address+inst[-1].size
        record=check_source_case(reader,pe,decoder,f598,original,code,refs,inst,ret,boss,info)
        rows.append({'original_boss':f'0x{addr:08X}',
                     'previous_23_real_action_cases_preserved':True,
                     'whole_original_CODE_bytes_still_nonexact':boss['size'],
                     'original_afterRET_DATA_verified':boss['postret_size'],
                     'native_source_trajectory_parameters':info,
                     'native_0x46_source':record,
                     'new_independent_exact_functions':0})
        print(f'F602 {addr:#010x}: full original action0x46 104/104 x86, '
              f'{info["original_native_CODE_bytes"]} native /374 source inner CODE B, '
              '15/15 physical original COFF fields, previous 23 native actions preserved; '
              'WHOLE giant still nonexact',flush=True)
    outfile=OUT/('summary.json' if not options.boss else f'summary-{selected[0]:08X}.json')
    outfile.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F602 {len(rows)} original giant-fighter action46 C++ cases: '
          f'{len(rows)*104} native x86 roles, '
          f'{sum(r["native_source_trajectory_parameters"]["original_native_CODE_bytes"] for r in rows)} '
          f'original internal CODE bytes uncredited, {len(rows)*15} authentic COFF fields; '
          '0 newly accepted original whole functions and no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F602 original native fighter trajectory case source failed:',exc,file=sys.stderr)
        raise SystemExit(1)
