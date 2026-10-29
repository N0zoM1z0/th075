#!/usr/bin/env python3
"""F614: complete native action0x58 in eleven giant fighter controllers.

Cold-compile only each chosen original giant C++ source and independently
check whole original 0x58/0x59 packed handler bounds, 135/154 original
GPR/x87/CFG instructions, 469/539/wide580 bytes, 17/18 authentic
PE/COFF call/float fields and native ten-projectile loop. Re-verify
all 29 earlier original game action subranges in the same new object.
No case fragment or enclosing unfinished giant receives exact credit.
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
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
INC=ROOT/'probes/FighterTrajectoryBurst58F614.inc'
OUT=ROOT/'.analysis/f614-fighter-burst-source'
SPECIAL=(0x0045DD70,0x0058AF60)
FIELDS={25:(0x0065782C,'fcomp'),
 31:(0x00657888,'fmul'),32:(0x006406AC,'call'),
 37:(0x00657888,'fmul'),38:(0x006406AC,'call'),
 42:(0x00453E20,'call'),47:(0x0040FAC0,'call'),
 50:(0x00453E60,'call'),53:(0x00453D60,'call'),
 71:(0x00453A70,'call'),89:(0x00453A70,'call'),
 92:(0x0040FA30,'call'),103:(0x0040FB40,'call'),
 113:(0x0065782C,'fld'),120:(0x0065782C,'fld'),
 128:(0x0040FB40,'call'),132:(0x0040FB40,'call')}


def need(value,why):
    if not value:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing original PE helper '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def native_case(reader,pe,decoder,boss,by):
    addr=boss['address'];start,end=by[0x58],by[0x59]
    special=addr in SPECIAL
    length=539 if special else (580 if addr==0x00564BE0 else 469)
    count=154 if special else 135
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    need(addr<=start<end<addr+boss['size']
         and end-start==length and len(native)==count
         and sum(i.size for i in native)==length
         and native[-1].mnemonic=='jmp',
         f'{addr:#x}: actual original complete native 0x58/0x59 physical x86 extent changed')
    short=(0xEFC if addr==0x005AEEC0 else 0xF00)
    need(native[15].mnemonic=='mov' and native[15].op_str.endswith('+ 0x98]')
         and native[16].mnemonic=='mov' and 'dword ptr' in native[16].op_str
         and '+ 0x54]' in native[16].op_str
         and native[18].mnemonic=='mov' and native[18].op_str.endswith(', 0x3f4ccccd')
         and native[25].mnemonic=='fcomp'
         and native[34].mnemonic=='mov' and f'+ 0x{short:x}]' in native[34].op_str
         and native[40].mnemonic=='mov' and f'+ 0x{short+2:x}]' in native[40].op_str
         and native[45].mnemonic=='push' and native[45].op_str=='0x59'
         and native[48].mnemonic=='push' and native[48].op_str=='0x40400000'
         and native[54].mnemonic=='mov' and native[54].op_str=='dword ptr [ebp - 4], 0'
         and native[59].mnemonic=='cmp' and native[59].op_str=='dword ptr [ebp - 4], 0xa'
         and native[69].mnemonic=='push' and native[69].op_str=='0x3e4'
         and native[71].mnemonic=='call' and native[71].op_str=='0x453a70'
         and native[74].mnemonic=='movsx' and '+ 0xefa]' in native[74].op_str
         and native[75].mnemonic=='cmp' and native[75].op_str.endswith(', 0x19')
         and native[78].mnemonic=='mov' and '+ 0xefa]' in native[78].op_str
         and native[87].mnemonic=='push' and native[87].op_str=='0x3e3'
         and native[89].mnemonic=='call' and native[89].op_str=='0x453a70'
         and native[106].mnemonic=='cmp' and native[106].op_str.endswith(', 1'),
         f'{addr:#x}: original 10-projectile loop, threshold and main action movement differ')
    # Real original two physical FLD/FUCOMPP status comparisons, with
    # one additional independently guarded stage-one sprite only in
    # the two authentic player-owner fighters.
    bias=19 if special else 0
    need([native[j+bias].mnemonic for j in (115,122)]==['fucompp','fucompp']
         and [native[j+bias].op_str for j in (117,124)]==['ah, 0x44','ah, 0x44']
         and [native[j+bias].op_str for j in (126,130)]==['3','2'],
         f'{addr:#x}: original native 0x58 two late x87 float equality comparisons changed')
    typed={i+(bias if i>=113 else 0):val for i,val in FIELDS.items()}
    sprite=None
    if special:
        kind=int(native[128].op_str,0)
        side=int(native[118].op_str,0)
        need((kind,side)==((0x3B7,1) if addr==0x0045DD70 else (0x3E7,0))
             and native[113].mnemonic=='movsx' and '+ 0xf0c]' in native[113].op_str
             and native[117].mnemonic=='mov' and native[117].op_str.endswith(', 1')
             and native[130].mnemonic=='call' and native[130].op_str=='0x453a70',
             f'{addr:#x}: real native stage1 projectile type/side and one-shot flag changed')
        typed[130]=(0x00453A70,'call')
        sprite={'native_projectile_kind':kind,'native_projectile_side':side,
                'real_short_one_shot_counter':0xF0C}
    need(len(typed)==(18 if special else 17),
         f'{addr:#x}: original real source distinct COFF field count malformed')
    for index,(dest,mn) in typed.items():
        x=native[index]
        need(x.mnemonic==mn and x.op_str==(
             f'0x{dest:x}' if mn=='call' else f'dword ptr [0x{dest:x}]'),
             f'{addr:#x}: true native original PE call/global target changed at {index}')
    return native,{'native_actual_original_start':f'0x{start:08X}',
                   'native_original_complete_CASE_CODE_bytes':length,
                   'original_complete_x86_roles':count,
                   'native_trajectory_counter_offset':short,
                   'original_10_burst_sprite':0x3E4,
                   'native_bonus_sprite':0x3E3,
                   'native_bonus_counter':0xEFA,
                   'original_stage_one_projectile':sprite,
                   'real_original_typed_PE_COFF_fields':typed,
                   'entire_enclosing_original_boss_exact':False}


def reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                      f598,f567,f600,f602,f603,f605,f606,f607,f608,
                      f610,f611,f613,info):
    raw=f613.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
          f598,f567,f600,f602,f603,f605,f606,f607,f608,f610,f611)
    cls=f'class FighterSwitchF598_Boss{addr:08X} {{ public:'
    need(raw.count(cls)==1,f'{addr:#x}: whole original game actor declaration missing')
    if 'void SpawnDirectedAt453A70(int,int,int,char,int);' not in raw:
        raw=raw.replace(cls,cls+' void SpawnDirectedAt453A70(int,int,int,char,int);')
    marker='        case 0x58: g_FighterProbeMarker = 89; break;'
    need(raw.count(marker)==1,f'{addr:#x}: indexed next true original action0x58 placeholder missing')
    spawn=info['original_stage_one_projectile']
    defs={'F614_COUNTER':f'0x{info["native_trajectory_counter_offset"]:X}',
          'F614_STAGE1_SPAWN':str(int(spawn is not None)),
          'F614_PROJECTILE':f'0x{spawn["native_projectile_kind"]:X}' if spawn else '0x3E7',
          'F614_SIDE':str(spawn['native_projectile_side']) if spawn else '0'}
    added='\n'.join('#define '+k+' '+v for k,v in defs.items())
    added+='\n#include "FighterTrajectoryBurst58F614.inc"\n'
    added+='\n'.join('#undef '+k for k in defs)
    return raw.replace(marker,added)


def compare_candidate(reader,pe,decoder,f598,f600,f602,f603,f605,f606,
                   f607,f608,f610,f611,f613,core,zero,switch,
                   boss,report,mapped,code,refs,native,info):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: source giant final RET missing')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original afterRET separately-owned DATA length changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    orig4c,info4c=f613.original_case(reader,pe,decoder,boss,by)
    f613.compare_candidate(reader,pe,decoder,f598,f600,f602,f603,f605,f606,
                  f607,f608,f610,f611,core,zero,switch,
                  boss,report,mapped,code,refs,orig4c,info4c)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(sparse[0x58-0x33]==17 and sparse[0x59-0x33]==18,
         f'{addr:#x}: original packed second-switch 0x58/0x59 physical sparse slots changed')
    actual_handlers=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
                     for i in (17,18)]
    need(actual_handlers==[by[0x58],by[0x59]],
         f'{addr:#x}: original PE actual 0x58/0x59 dense handler targets differ')
    bounds=[]
    for i in (17,18):
        fields=[x for x in refs if x['offset']==ret+44+4*i]
        need(len(fields)==1 and fields[0]['type']=='DIR32' and fields[0]['addend']==0
             and fields[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: real original afterRET dense source COFF index {i} missing')
        bounds.append(fields[0]['local_symbol_offset'])
    start,end=bounds
    generated=list(decoder.disasm(code[start:end],start))
    expected_count=info['original_complete_x86_roles']
    expected_source=469 if expected_count==135 else 539
    need(len(native)==len(generated)==expected_count
         and end-start==expected_source
         and sum(x.size for x in generated)==expected_source,
         f'{addr:#x}: source is not entire genuine original 0x58 135/154 native instructions')
    widths=[x.size-y.size for x,y in zip(native,generated)]
    if addr==0x00564BE0:
        need(widths.count(3)==37 and widths.count(0)==98
             and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i,k in enumerate(widths) if k==3),
             f'{addr:#x}: original native wide receiver 37 x86 displacement fields differ')
    else:need(all(x==0 for x in widths),
              f'{addr:#x}: original native source 0x58 135/154 width mismatch')
    fields=[x for x in refs if start<=x['offset']<end]
    targets=info['real_original_typed_PE_COFF_fields']
    need(len(fields)==len(targets),
         f'{addr:#x}: 17/18 native typed original physical source COFF fields missing')
    symbols={**f602.ALL_SYMBOLS,0x00453A70:'SpawnDirectedAt453A70'}
    for i,(dest,mn) in targets.items():
        a,b=native[i],generated[i]
        need(a.mnemonic==b.mnemonic==mn,
             f'{addr:#x}: original native PE typed x86 ordinal {i} moved')
        found=[x for x in fields if b.address<=x['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and symbols[dest] in found[0]['symbol'],
             f'{addr:#x}: original PE physical call/float target {dest:#x} at {i} differs: {found}')
    original_roles,generated_roles=f598.normalized(native),f598.normalized(generated)
    # Unlinked compiler fld [0] is only normalized AFTER exact original
    # native DIR32 target and compiler COFF field symbol/ordinal check.
    bias=19 if expected_count==154 else 0
    for i in (113+bias,120+bias):
        need(original_roles[i]==('fld','dword ptr [0x65782c]')
             and generated_roles[i]==('fld','dword ptr [0]'),
             f'{addr:#x}: genuine source/original x87 two FLD+FUCOMPP operands changed')
        original_roles[i]=generated_roles[i]=('fld','NATIVE_REAL_TYPED_FLOAT_GLOBAL_0065782C')
    mistakes=[(i,x,y) for i,(x,y) in enumerate(zip(original_roles,generated_roles)) if x!=y]
    need(not mistakes,
         f'{addr:#x}: complete native 0x58 GPR/x87/CFG role mismatch: {mistakes[:6]}')
    return {'original_whole_fighter':f'0x{addr:08X}',
            'original_entire_giant_CODE_still_NONEXACT':boss['size'],
            'original_afterRET_DATA_separately_owned':boss['postret_size'],
            'previous_29_original_case_bodies_strict_in_same_OBJ':True,
            'original_complete_0x58_case':info,
            'new_original_native_x86_roles':expected_count,
            'new_original_native_internal_CODE_bytes_uncredited':info['native_original_complete_CASE_CODE_bytes'],
            'genuine_original_PE_COFF_fields':len(fields),
            'accepted_new_whole_exact_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one selected giant original fighter; default eleven affected C++ TUs')
    options=parser.parse_args()
    f602=load('f614_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f614_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f614_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f614_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f614_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f614_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f614_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f614_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f614_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f614_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f614_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f613=load('f614_f613',ROOT/'scripts/verify-fighter-trajectory-recovery-f613.py')
    reader=load('f614_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f614_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f614_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f614_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f614_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    need(len(cohort)==len(set(cohort))==11,
         'actual 11 fighter original second-switch native owners changed')
    selected=[int(options.boss,0)] if options.boss else list(cohort)
    need(all(addr in cohort for addr in selected),
         'selected whole original boss not one of 11 native burst cases')
    text=INC.read_text()
    need(text.count('case 0x58:')==1
         and text.count('SpawnDirectedAt453A70(0x3E4')==1
         and text.count('SpawnDirectedAt453A70(0x3E3')==1
         and text.count('for (int burst=0;burst<10;++burst)')==1
         and text.count('I16(0xEFA)')==2
         and '*(&POS)==g_ThresholdAt0065782C' in text,
         'original 0x58 ten-projectile burst and genuine float equality source changed')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={q['action']:int(q['handler'],16) for q in mapped}
        original,info=native_case(reader,pe,decoder,boss,by)
        source=reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                     f598,f567,f600,f602,f603,f605,f606,f607,f608,
                     f610,f611,f613,info)
        cpp=OUT/f'Boss{addr:08X}-30-real-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-30-real-game-actions.obj'
        cpp.write_text(source)
        compile=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(compile.stdout+compile.stderr)
        need(compile.returncode==0,
             f'{addr:#x}: original pinned VC7.1 whole fighter source fails: {compile.stderr[-550:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        found=compare_candidate(reader,pe,decoder,f598,f600,f602,f603,f605,f606,
                 f607,f608,f610,f611,f613,core,zero,switch,
                 boss,report,mapped,code,refs,original,info)
        rows.append(found)
        print(f'F614 {addr:#010x}: real native full 0x58 case '
              f'{info["original_complete_x86_roles"]}/{info["original_complete_x86_roles"]} '
              f'x86 GPR/x87/CFG roles, {info["native_original_complete_CASE_CODE_bytes"]} '
              f'original internal CODE bytes, {len(info["real_original_typed_PE_COFF_fields"])} '
              'true original typed COFF fields, previous 29 actions and afterRET packed DATA '
              'retained. Whole giant NONEXACT',flush=True)
    out=OUT/('summary.json' if not options.boss else f'summary-{selected[0]:08X}.json')
    out.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F614 {len(rows)} selected giant source TUs, '
          f'{sum(x["new_original_native_x86_roles"] for x in rows)} original x86 roles / '
          f'{sum(x["new_original_native_internal_CODE_bytes_uncredited"] for x in rows)} '
          f'original uncredited CODE bytes / '
          f'{sum(x["genuine_original_PE_COFF_fields"] for x in rows)} genuine typed COFF; '
          'ZERO new whole native exact function credit and no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F614 original TH075 native fighter ten-burst verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
