#!/usr/bin/env python3
"""F613: one full native 74-x86 action0x4C in each of eleven fighters.

Regenerate + cold compile ONLY each selected giant original source TU,
retain the previous 28 PE-backed case subranges, independent original
packed after-RET DATA, all 14 genuine PE/COFF targets, native complete
x86 GPR/x87/CFG roles/widths, and real owner counter. No partial case
or unfinished enclosing giant is granted exact-function credit.
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
SOURCE=ROOT/'probes/FighterTrajectoryRecovery4CF613.inc'
OUT=ROOT/'.analysis/f613-fighter-recovery-source'
SPECIAL=(0x0045DD70,0x0058AF60)
TARGETS={
    13:(0x0040FBB0,'call'),16:(0x00657878,'fadd'),
    29:(0x0065782C,'fcomp'),35:(0x00453D60,'call'),
    38:(0x00657888,'fmul'),39:(0x006406AC,'call'),
    44:(0x00657888,'fmul'),45:(0x006406AC,'call'),
    49:(0x00453E20,'call'),54:(0x0040FAC0,'call'),
    59:(0x00453E60,'call'),61:(0x0040FC50,'call'),
    64:(0x0040FA30,'call'),72:(0x0040FB40,'call')}


def need(test,message):
    if not test:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing original source helper '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def short_offset(native,i):
    x=native[i]
    match=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], (?:ax|0)',x.op_str)
    need(x.mnemonic=='mov' and match is not None,
         f'original 0x4C original trajectory short member ordinal {i} changed')
    return int(match.group(1),16)


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address']
    start,end=by[0x4C],by[0x58]
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    original_size=360 if addr==0x00564BE0 else 285
    need(addr<=start<end<addr+boss['size'] and end-start==original_size
         and len(native)==74 and sum(i.size for i in native)==original_size
         and native[-1].mnemonic=='jmp',
         f'{addr:#x}: original physical native complete 0x4C/0x58 case extent changed')
    offsets=[short_offset(native,i) for i in (8,41,47)]
    need(offsets[0] in (0xF00,0xEFC) and offsets[1]==offsets[0]
         and offsets[2]==offsets[0]+2
         and offsets[0]==(0xEFC if addr==0x005AEEC0 else 0xF00),
         f'{addr:#x}: real original two signed-short owner trajectory fields conflict')
    need(native[1].mnemonic=='movsx' and native[1].op_str.endswith(f'+ 0x{offsets[0]:x}]')
         and native[3].mnemonic=='jne' and native[3].op_str==f'0x{native[14].address:x}'
         and native[6].mnemonic=='add' and native[6].op_str=='ax, 1'
         and [native[j].op_str for j in (9,10,11)]==['0','0x42be0000','0']
         and native[13].mnemonic=='call' and native[13].op_str=='0x40fbb0'
         and native[14].mnemonic=='mov' and native[15].mnemonic=='fld'
         and native[16].mnemonic=='fadd' and native[16].op_str=='dword ptr [0x657878]'
         and native[22].mnemonic=='fsub' and native[28].mnemonic=='fadd'
         and native[33].mnemonic=='push' and native[33].op_str=='0x16'
         and native[55].mnemonic=='mov' and native[55].op_str.endswith('+ 0x30]') is False
         and native[56].mnemonic=='mov' and '+ 0x30]' in native[56].op_str
         and native[57].mnemonic=='push' and native[57].op_str=='0x40000000'
         and native[61].mnemonic=='call' and native[61].op_str=='0x40fc50'
         and native[63].mnemonic=='mov' and native[64].mnemonic=='call'
         and native[70].mnemonic=='push' and native[70].op_str=='0',
         f'{addr:#x}: genuine once-only initialization, EVERY-frame angle or original 0x4C recovery changed')
    for i,(dest,mnemonic) in TARGETS.items():
        x=native[i]
        need(x.mnemonic==mnemonic and x.op_str==(
             f'0x{dest:x}' if mnemonic=='call' else f'dword ptr [0x{dest:x}]'),
             f'{addr:#x}: original PE call/x87 target {dest:#x} at ordinal {i} differs')
    return native,{'original_handler':f'0x{start:08X}',
                   'original_native_complete_CASE_bytes':original_size,
                   'original_complete_x86_instructions':74,
                   'original_owner_counter_offset':offsets[0],
                   'native_original_typed_COFF_fields':14,
                   'real_native_unconditional_angle_advance':True,
                   'complete_giant_function_exact':False}


def reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                       f598,f567,f600,f602,f603,f605,f606,f607,f608,f610,f611):
    by={x['action']:int(x['handler'],16) for x in mapped}
    original49=meta49=None
    if addr in SPECIAL:
        orig46,meta46=f603.real_case(reader,pe,decoder,boss,by,f602)
        prev={a:f606.read_native_case(reader,pe,decoder,boss,by,a,f605)
              for a in (0x47,0x48)}
        orig49,meta49=f608.native_case(reader,pe,decoder,boss,by,f607)
        raw=f611.source_with_prior(addr,boss,report,mapped,reader,pe,decoder,
                         f602,f603,f606,f608,f598,f567,orig46,meta46,prev,meta49)
        # The original 589-byte double-shot bounce, not the regular
        # 434-byte owner; its real native stage/side are independent.
        original4a,meta4a=f611.native_case(reader,pe,decoder,boss,by,f610)
        marker='        case 0x4A: g_FighterProbeMarker = 75; break;'
        need(raw.count(marker)==1,f'{addr:#x}: original double-shot 4A placeholder moved')
        defs={
         'F611_PROJECTILE':f'0x{meta4a["native_real_projectile_kind"]:X}',
         'F611_SIDE':str(meta4a['native_real_projectile_side']),
         'F610_STAGE':str(meta4a['native_stage']),
         'F610_EARLY':str(meta4a['native_early_aux']),
         'F610_LATE':str(meta4a['native_late_aux']),
         'F610_COUNTER':f'0x{meta4a["original_trajectory_short_offset"]:X}',
         'F610_PREPARE_BEFORE':'0'}
        insert='\n'.join('#define '+k+' '+v for k,v in defs.items())
        insert+='\n#include "FighterTrajectoryBounceSpawn4AF611.inc"\n'
        insert+='\n'.join('#undef '+k for k in defs)
        raw=raw.replace(marker,insert)
    else:
        orig46,meta46=f602.original_case(reader,pe,decoder,boss,by)
        earlier={a:f605.original_action(reader,pe,decoder,boss,by,a)[1]
                 for a in (0x47,0x48)}
        orig49,meta49=f607.native_case(reader,pe,decoder,boss,by)
        raw=f605.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                                     f602,f598,f567,meta46,earlier)
        placeholder='        case 0x49: g_FighterProbeMarker = 74; break;'
        need(raw.count(placeholder)==1,f'{addr:#x}: original regular game action49 source placeholder moved')
        raw=raw.replace(placeholder,
           f'#define F607_COUNTER 0x{meta49["native_trajectory_short_offset"]:X}\n'
           '#include "FighterTrajectoryLanding49F607.inc"\n'
           '#undef F607_COUNTER')
        original4a,meta4a=f610.original_case(reader,pe,decoder,boss,by)
        marker='        case 0x4A: g_FighterProbeMarker = 75; break;'
        need(raw.count(marker)==1,f'{addr:#x}: original regular 0x4A source placeholder moved')
        defs={'F610_STAGE':str(meta4a['native_stage']),
              'F610_EARLY':str(meta4a['native_early_aux']),
              'F610_LATE':str(meta4a['native_late_aux']),
              'F610_COUNTER':f'0x{meta4a["native_counter_offset"]:X}',
              'F610_PREPARE_BEFORE':str(int(meta4a['original_pre_contact_prepare']))}
        insert='\n'.join('#define '+k+' '+v for k,v in defs.items())
        insert+='\n#include "FighterTrajectoryBounce4AF610.inc"\n'
        insert+='\n'.join('#undef '+k for k in defs)
        raw=raw.replace(marker,insert)
    # The two true original PE bounce globals are used in BOTH the
    # regular 4A and special 4A natural game source.
    decl='extern float g_ContactProjectionAt00657888;'
    need(raw.count(decl)==1,f'{addr:#x}: original game source global declarations lost')
    raw=raw.replace(decl,decl+'\nextern float g_BounceThresholdAt006590C0;'
                     '\nextern float g_BounceScaleAt00657F74;'
                     '\nextern float g_AngleShiftAt00657878;')
    cls=f'class FighterSwitchF598_Boss{addr:08X} {{ public:'
    need(raw.count(cls)==1,f'{addr:#x}: original game scene class declaration changed')
    raw=raw.replace(cls,cls+' void SetMotionStateAt40FBB0(int,float,int);'
                ' void ResetMotionAt40FC50();')
    marker='        case 0x4C: g_FighterProbeMarker = 77; break;'
    need(raw.count(marker)==1,f'{addr:#x}: original next second-switch 0x4C case missing')
    offset=0xEFC if addr==0x005AEEC0 else 0xF00
    raw=raw.replace(marker,
         f'#define F613_COUNTER 0x{offset:X}\n'
         '#include "FighterTrajectoryRecovery4CF613.inc"\n'
         '#undef F613_COUNTER')
    return raw


def compare_candidate(reader,pe,decoder,f598,f600,f602,f603,f605,f606,
                 f607,f608,f610,f611,core,zero,switch,
                 boss,report,mapped,code,refs,native,info):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: no whole-giant source RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: separately owned complete afterRET switch DATA changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    if addr in SPECIAL:
        prev,meta=f611.native_case(reader,pe,decoder,boss,by,f610)
        f611.check_case(reader,pe,decoder,f598,f602,f603,f606,f608,f600,
             core,zero,switch,boss,report,mapped,code,refs,prev,meta)
    else:
        prev,meta=f610.original_case(reader,pe,decoder,boss,by)
        f610.case_in_giant(reader,pe,decoder,f598,f602,f605,f607,f600,
             core,zero,switch,boss,report,mapped,code,refs,prev,meta)
    # Original packed afterRET index has a gap from 0x4A to 0x4C:
    # there is no invented independent action0x4B body.
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(sparse[0x4C-0x33]==16 and sparse[0x58-0x33]==17,
         f'{addr:#x}: original packed physical 0x4C/0x58 sparse slots changed')
    native_pointers=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+i*4,4),'little')
                     for i in (16,17)]
    need(native_pointers==[by[0x4C],by[0x58]],
         f'{addr:#x}: native physical afterRET indexed 0x4C/0x58 jump destinations changed')
    bounds=[]
    for i in (16,17):
        physical=[r for r in refs if r['offset']==ret+44+4*i]
        need(len(physical)==1 and physical[0]['type']=='DIR32'
             and physical[0]['addend']==0 and physical[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: generated COFF lost real afterRET packed 0x4C/0x58 branch')
        bounds.append(physical[0]['local_symbol_offset'])
    start,end=bounds
    compiled=list(decoder.disasm(code[start:end],start))
    need(len(compiled)==len(native)==74 and end-start==285
         and sum(x.size for x in compiled)==285,
         f'{addr:#x}: natural C++ is not complete 74-insn/285-byte native case 0x4C')
    width=[x.size-y.size for x,y in zip(native,compiled)]
    if addr==0x00564BE0:
        need(width.count(3)==25 and width.count(0)==49
             and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i in range(74) if width[i]==3),
             f'{addr:#x}: original 25 true native wide-frame EBP-0x88 receiver loads differ')
    else:need(all(delta==0 for delta in width),
              f'{addr:#x}: compact original case0x4C physical code width changed')
    symbols={**f602.ALL_SYMBOLS,
             0x0040FBB0:'SetMotionStateAt40FBB0',
             0x0040FC50:'ResetMotionAt40FC50',
             0x00657878:'g_AngleShiftAt00657878'}
    fields=[r for r in refs if start<=r['offset']<end]
    need(len(fields)==len(TARGETS)==14,
         f'{addr:#x}: native original 0x4C 14 physical typed PE/COFF references differ')
    for i,(target,mn) in TARGETS.items():
        a,b=native[i],compiled[i]
        need(a.mnemonic==b.mnemonic==mn,
             f'{addr:#x}: real original COFF instruction ordinal {i} moved')
        match=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(match)==1 and match[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and match[0]['addend']==0 and match[0]['local_symbol_offset'] is None
             and symbols[target] in match[0]['symbol'],
             f'{addr:#x}: native original PE call/float {target:#x} at {i} vs true COFF differs: {match}')
    na,ca=f598.normalized(native),f598.normalized(compiled)
    mismatch=[(i,x,y) for i,(x,y) in enumerate(zip(na,ca)) if x!=y]
    need(not mismatch,
         f'{addr:#x}: full original 0x4C GPR/x87/CFG role or branch differs: {mismatch[:6]}')
    need(na[3]==('jne','CASE_ORDINAL_14') and ca[3]==na[3],
         f'{addr:#x}: original angle advances every frame even on initialized recovery')
    return {'original_whole_fighter':f'0x{addr:08X}',
            'original_whole_giant_CODE_NONEXACT':boss['size'],
            'original_afterRET_packed_DATA_separate_bytes':boss['postret_size'],
            'previous_28_real_game_case_bodies_retained_in_same_OBJ':True,
            'original_full_native_0x4C':info,
            'new_original_inner_CODE_uncredited':info['original_native_complete_CASE_bytes'],
            'original_complete_x86_GPR_x87_CFG_roles':74,
            'true_physical_original_PE_COFF_fields':14,
            'accepted_whole_native_game_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one specific original fighter giant, default 11 affected TUs')
    opt=p.parse_args()
    f602=load('f613_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f613_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f613_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f613_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f613_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f613_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f613_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f613_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f613_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f613_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f613_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    reader=load('f613_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f613_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f613_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f613_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f613_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    need(len(cohort)==11 and len(set(cohort))==11,
         'actual eleven original second-switch whole boss cohort differs')
    selected=[int(opt.boss,0)] if opt.boss else list(cohort)
    need(all(addr in cohort for addr in selected),
         'selected native whole boss does not own this real indexed 0x4C case')
    text=SOURCE.read_text()
    need(text.count('case 0x4C:')==1
         and text.count('SetMotionStateAt40FBB0(0,95.0f,0)')==1
         and text.count('F32(0x30) = F32(0x30) + g_AngleShiftAt00657878;')==1
         and text.count('ResetMotionAt40FC50();')==1,
         'natural source no longer reproduces original unconditional angle advance')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,dec,boss)
        by={q['action']:int(q['handler'],16) for q in mapped}
        original,info=original_case(reader,pe,dec,boss,by)
        source=reconstruct_source(addr,boss,report,mapped,reader,pe,dec,
                 f598,f567,f600,f602,f603,f605,f606,f607,f608,f610,f611)
        cpp=OUT/f'Boss{addr:08X}-29-native-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-29-native-game-actions.obj'
        cpp.write_text(source)
        compile=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(compile.stdout+compile.stderr)
        need(compile.returncode==0,f'{addr:#x}: genuine original VC7.1 giant source fails: {compile.stderr[-600:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        found=compare_candidate(reader,pe,dec,f598,f600,f602,f603,f605,f606,
                    f607,f608,f610,f611,core,zero,switch,boss,report,mapped,
                    code,refs,original,info)
        rows.append(found)
        print(f'F613 {addr:#010x}: original 0x4C real 74/74 x86 roles, '
              f'{info["original_native_complete_CASE_bytes"]} native internal CODE bytes, '
              '14/14 genuine typed PE/COFF destinations; previous 28 native cases '
              'and original full afterRET table retained, whole boss NONEXACT',flush=True)
    file=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    file.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F613 {len(rows)} affected giant sources, {len(rows)*74} authentic original x86 '
          f'roles / {sum(x["new_original_inner_CODE_uncredited"] for x in rows)} '
          f'original *internal* CODE bytes / {len(rows)*14} physical typed native COFF targets; '
          'ZERO new exact whole functions; no 943-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F613 original TH075 native recovery case verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
