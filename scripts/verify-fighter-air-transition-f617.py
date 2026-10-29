#!/usr/bin/env python3
"""F617: six real 101-x86 original action0x5E cases inside big fighters.

Original 0x5D has the same native x86 geometry and typed COFF targets
but still mismatches 61 GPR/CFG source roles (native register cycle).
Original 0x5E is fully source-grammar-equal in SIX selected fighters;
other original 0x5E actors include one independently negative GPR
phase and four different 64/94/96/106-x86 grammars. Never credit
misproven 0x5D, 0x5E fragments or entire nonexact fighter as an
accepted exact whole native game function. Rebuild affected TUs only.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
INC=ROOT/'probes/FighterAirTransitionCaseF617.inc'
OUT=ROOT/'.analysis/f617-fighter-air-source'
COHORT=(0x0045DD70,0x005D73C0,0x00486550,0x004AC040,
        0x00564BE0,0x005214B0)
NEGATIVE=0x00543210
FIELDS={6:(0x0065782C,'fcomp'),20:(0x0065782C,'fcomp'),
        27:(0x00453E20,'call'),30:(0x0040FB40,'call'),
        33:(0x0040FA30,'call'),41:(0x0040FAC0,'call'),
        47:(0x0040FAC0,'call'),99:(0x0040FB40,'call')}


def need(value, reason):
    if not value:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing true original/native source reader '+str(path))
    obj=importlib.util.module_from_spec(spec)
    sys.modules[name]=obj
    spec.loader.exec_module(obj)
    return obj


def numeric_last(text):
    return int(text.rsplit(', ',1)[-1],0)


def native_case(reader,pe,decoder,boss,by,action):
    addr=boss['address']
    start,end=by[action],by[action+1]
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=430 if addr==0x00564BE0 else 337
    need(addr<=start<end<addr+boss['size'] and end-start==size
         and len(native)==101 and sum(x.size for x in native)==size
         and native[-1].mnemonic=='jmp',
         f'{addr:#x} original action0x{action:X}: physical 101-instruction extent/boundaries differ')
    threshold=numeric_last(native[2].op_str)
    beginning=numeric_last(native[77].op_str)
    finish=int(native[97].op_str,0)
    speed=numeric_last(native[84].op_str)
    position=numeric_last(native[86].op_str)
    friction=numeric_last(native[88].op_str)
    need(native[2].mnemonic=='cmp' and native[28].mnemonic=='push'
         and int(native[28].op_str,0)==threshold
         and native[91].mnemonic=='cmp' and numeric_last(native[91].op_str)==threshold
         and native[77].mnemonic=='cmp'
         and native[84].mnemonic==native[86].mnemonic==native[88].mnemonic=='mov'
         and [native[j].mnemonic for j in (58,59,68,69)]==['fld','fcomp','fld','fcomp']
         and native[61].mnemonic=='test' and native[61].op_str=='ah, 0x41'
         and native[62].mnemonic=='jne' and native[62].op_str==f'0x{native[65].address:x}'
         and native[71].mnemonic=='test' and native[71].op_str=='ah, 5'
         and native[72].mnemonic=='jp'
         and native[73].mnemonic=='mov'
         and native[97].mnemonic=='push',
         f'{addr:#x} {action:#x}: original actual facing/independent comparators/stage grammar differs')
    need(speed in (0x40900000,0x41000000)
         and position in (0x41480000,0x41A00000,0x41580000,0x41780000,
                           0xC1480000,0xC1A00000,0xC1580000,0xC1780000,0xC1380000)
         and friction in (0x3EB33333,0x3F000000,0x3F19999A,0x3F333333,0x3F400000)
         and threshold in (6,7,8,9,11,12,18,19),
         f'{addr:#x} {action:#x}: genuine native actor-specific initial motion no longer expected')
    for i,(target,mn) in FIELDS.items():
        x=native[i]
        need(x.mnemonic==mn and x.op_str==(
             f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'),
             f'{addr:#x} {action:#x}: true native PE typed float/game target {target:#x} at ordinal{i} differs')
    return native,{'action':f'0x{action:02X}',
                   'native_actual_PE_start':f'0x{start:08X}',
                   'native_original_complete_inner_CODE_bytes':size,
                   'native_complete_x86_roles':101,
                   'native_threshold':threshold,'native_initial_stage':beginning,
                   'native_finish_state':finish,
                   'native_start_speed_bits':speed,
                   'native_start_position_bits':position,
                   'native_friction_bits':friction,
                   'original_typed_COFF_field_targets':FIELDS,
                   'whole_giant_exact':False}


def float_literal(bits):
    value=struct.unpack('<f',struct.pack('<I',bits))[0]
    need(value==value and abs(value)<10000,'invalid original finite native movement literal')
    return repr(value)+'f'


def with_native_cases(addr,boss,report,mapped,reader,pe,decoder,
                      f598,f567,f600,f602,f603,f605,f606,f607,f608,
                      f610,f611,f613,f614,properties):
    native58,info58=f614.native_case(reader,pe,decoder,boss,
                          {r['action']:int(r['handler'],16) for r in mapped})
    source=f614.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
             f598,f567,f600,f602,f603,f605,f606,f607,f608,
             f610,f611,f613,info58)
    a='        case 0x5D: g_FighterProbeMarker = 94; break;'
    b='        case 0x5E: g_FighterProbeMarker = 95; break;'
    next_case='        case 0x5F: g_FighterProbeMarker = 96; break;'
    need(source.count(a)==source.count(b)==source.count(next_case)==1,
         f'{addr:#x}: real original two packed indexed case placeholders no longer consecutive')
    defs=[]
    for action in (0x5D,0x5E):
        info=properties[action][1]
        values={
          'F617_CASE':f'0x{action:X}',
          'F617_THRESHOLD':str(info['native_threshold']),
          'F617_BEGIN_STAGE':str(info['native_initial_stage']),
          'F617_FINISH_STATE':str(info['native_finish_state']),
          'F617_START_SPEED':float_literal(info['native_start_speed_bits']),
          'F617_START_POS':float_literal(info['native_start_position_bits']),
          'F617_FRICTION':float_literal(info['native_friction_bits'])}
        defs.extend('#define '+k+' '+v for k,v in values.items())
        defs.append('#include "FighterAirTransitionCaseF617.inc"')
        defs.extend('#undef '+k for k in values)
    first,last=source.index(a),source.index(next_case)
    return source[:first]+'\n'.join(defs)+'\n'+source[last:]


def verify_source(reader,pe,decoder,f598,f600,f602,f603,f605,f606,
                  f607,f608,f610,f611,f613,f614,core,zero,switch,
                  boss,report,mapped,code,refs,properties,negative):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: whole C++ fighter source has no final native RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: source no longer preserves original complete afterRET jump table ownership')
    by={q['action']:int(q['handler'],16) for q in mapped}
    previous,prior_info=f614.native_case(reader,pe,decoder,boss,by)
    # Re-validate the actual original 30 previously reconstructed game
    # inner cases, including 0x58 x86/COFF, in the SAME new C++ object.
    f614.compare_candidate(reader,pe,decoder,f598,f600,f602,f603,
         f605,f606,f607,f608,f610,f611,f613,core,zero,switch,
         boss,report,mapped,code,refs,previous,prior_info)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need([sparse[a-0x33] for a in (0x5D,0x5E,0x5F)]==[19,20,21],
         f'{addr:#x}: original real packed sparse 5D/5E/5F owner indices differ')
    originals=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
               for i in (19,20,21)]
    need(originals==[by[x] for x in (0x5D,0x5E,0x5F)],
         f'{addr:#x}: native genuine original dense action5D/5E/5F boundaries differ')
    offsets=[]
    for slot in (19,20,21):
        physical=[r for r in refs if r['offset']==ret+44+slot*4]
        need(len(physical)==1 and physical[0]['type']=='DIR32'
             and physical[0]['addend']==0 and physical[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: source missing original exact afterRET native dense slot {slot}')
        offsets.append(physical[0]['local_symbol_offset'])
    symbolic={**f602.ALL_SYMBOLS}
    rows=[]
    for act,source_start,source_end in zip((0x5D,0x5E),offsets,offsets[1:]):
        native,info=properties[act]
        source=list(decoder.disasm(code[source_start:source_end],source_start))
        need(len(source)==len(native)==101
             and source_end-source_start==337
             and sum(x.size for x in source)==337,
             f'{addr:#x}: candidate 5D/5E native action frame not correct original 101-x86 source')
        widths=[x.size-y.size for x,y in zip(native,source)]
        if addr==0x00564BE0:
            need(widths.count(3)==31 and widths.count(0)==70
                 and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,n in enumerate(widths) if n==3),
                 f'{addr:#x}: exact original 31 native wide EBP saved-this loads differ')
        else:
            need(all(x==0 for x in widths),
                 f'{addr:#x}: compact native original 337-byte action CODE widths changed')
        typed=[r for r in refs if source_start<=r['offset']<source_end]
        need(len(typed)==len(FIELDS)==8,
             f'{addr:#x}: genuine action{act:x} 8 physical typed native COFF fields missing')
        for i,(target,mn) in FIELDS.items():
            a,b=native[i],source[i]
            need(a.mnemonic==b.mnemonic==mn,
                 f'{addr:#x}: real original typed x86 role moved at ordinal{i}')
            fields=[r for r in typed if b.address<=r['offset']<b.address+b.size]
            need(len(fields)==1 and fields[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and fields[0]['addend']==0 and fields[0]['local_symbol_offset'] is None
                 and symbolic[target] in fields[0]['symbol'],
                 f'{addr:#x}: actual original PE {target:#x} source typed COFF ordinal{i} differs: {fields}')
        lhs,rhs=f598.normalized(native),f598.normalized(source)
        errors=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b]
        expected=61 if (act==0x5D or negative) else 0
        need(len(errors)==expected,
             f'{addr:#x}: natural source case{act:x} original GPR/CFG mismatch count {len(errors)}, expected {expected}, first {errors[:5]}')
        if act==0x5E and not negative:
            need(not errors, f'{addr:#x}: original 5E not role-exact; no local case credit')
        rows.append({'original_case':f'0x{act:02X}',
                     'native_complete_original_CODE_bytes':info['native_original_complete_inner_CODE_bytes'],
                     'source_x86_instruction_count':101,
                     'native_actual_typed_PE_COFF_fields':8,
                     'source_physical_GPR_CFG_role_mismatches':len(errors),
                     'source_fully_native_grammatical':not errors,
                     'source_widths_exact_or_real_wide_ebp':True,
                     'original_native_whole_function_exact':False})
    return {'whole_original_giant':f'0x{addr:08X}',
            'whole_original_giant_CODE_still_nonexact':boss['size'],
            'separate_original_afterRET_jump_DATA_bytes':boss['postret_size'],
            'all_previous_30_native_game_cases_source_retained':True,
            'two_true_original_followup_5D_5E':rows,
            'source_5D_native_GPR_CFG_role_mismatches':rows[0]['source_physical_GPR_CFG_role_mismatches'],
            'source_5E_native_GPR_CFG_role_mismatches':rows[1]['source_physical_GPR_CFG_role_mismatches'],
            'source_5E_original_inner_bytes_strict_uncredited':
                 rows[1]['native_complete_original_CODE_bytes'] if not negative else 0,
            'source_5E_original_typed_fields_strict_uncredited':8 if not negative else 0,
            'accepted_new_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original 5E strict-grammar fighter (six actor owners), default six')
    parser.add_argument('--negative-actor',action='store_true',
        help='independently rebuild excluded 00543210 5D/5E: 61 wrong roles in both original cases')
    opt=parser.parse_args()
    need(not(opt.boss and opt.negative_actor), 'choose either one strict owner or the excluded negative control')
    selected=[NEGATIVE] if opt.negative_actor else ([int(opt.boss,0)] if opt.boss else list(COHORT))
    need(all(x==NEGATIVE for x in selected) if opt.negative_actor
         else all(x in COHORT for x in selected),
         'selected original 5D/5E native case family not 101-instruction source')
    source=INC.read_text()
    need(source.count('case F617_CASE:')==1
         and source.count('if (*(&F32(0x44))>')==1
         and source.count('if (*(&F32(0x44))<')==1
         and 'I16(0x62)==I16(0x70)-1' in source,
         'genuine two independent source-facing comparisons or stage actor members missing')
    f602=load('f617_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f617_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f617_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f617_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f617_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f617_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f617_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f617_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f617_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f617_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f617_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f613=load('f617_f613',ROOT/'scripts/verify-fighter-trajectory-recovery-f613.py')
    f614=load('f617_f614',ROOT/'scripts/verify-fighter-trajectory-burst-f614.py')
    reader=load('f617_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f617_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f617_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f617_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f617_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,dec,boss)
        by={q['action']:int(q['handler'],16) for q in mapped}
        original={x:native_case(reader,pe,dec,boss,by,x) for x in (0x5D,0x5E)}
        cpp=OUT/f'Boss{addr:08X}-32-real-game-case-source.cpp'
        obj=OUT/f'Boss{addr:08X}-32-real-game-case-source.obj'
        cpp.write_text(with_native_cases(addr,boss,report,mapped,reader,pe,dec,
              f598,f567,f600,f602,f603,f605,f606,f607,f608,
              f610,f611,f613,f614,original))
        compile=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(compile.stdout+compile.stderr)
        need(compile.returncode==0,
             f'{addr:#x}: original native VC7.1 giant source compile failed: {compile.stderr[-600:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        row=verify_source(reader,pe,dec,f598,f600,f602,f603,f605,f606,
              f607,f608,f610,f611,f613,f614,core,zero,switch,
              boss,report,mapped,code,refs,original,opt.negative_actor)
        rows.append(row)
        print(f'F617 {addr:#010x}: prior 30 real original cases preserved; '
              f'0x5D native 101/101 x86 geometry /8 true COFF but '
              f'{row["source_5D_native_GPR_CFG_role_mismatches"]} source GPR roles NONEXACT; '
              f'0x5E native 101/101 x86 /8 genuine typed COFF, '
              f'{row["source_5E_native_GPR_CFG_role_mismatches"]} GPR/CFG role diffs; '
              'whole original giant NONEXACT',flush=True)
    output=OUT/('summary-negative.json' if opt.negative_actor else
                ('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json'))
    output.write_text(json.dumps(rows,indent=2)+'\n')
    credited=sum(r['source_5E_original_inner_bytes_strict_uncredited'] for r in rows)
    print(f'F617 {len(rows)} selected giant source TUs: {credited} original 5E '
          f'inner PE bytes strictly role-matched (NOT authored exact credit), '
          'all 5D still native GPR-cycle NONEXACT, no all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F617 genuine TH075 original 5D/5E source grammar failed:',exc,file=sys.stderr)
        raise SystemExit(1)
