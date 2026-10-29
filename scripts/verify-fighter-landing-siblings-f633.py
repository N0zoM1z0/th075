#!/usr/bin/env python3
"""F633: three native entire landing cases 97/98/9A in all 11 giant fighters.

Freshly compile ONLY the affected whole fighter VC7.1 source TUs,
independently check 33 physical original PE case boundaries, native
73/75 x86 GPR/x87/CFG/width roles, nine real typed COFF targets each,
source action 0/0/2, true -10/-13/-9 initial float, the two opposite
+0xF0A field-reset orders and real wide EBP-0x88 owner.
Recheck complete F631 prior case96, F629/F630 91 (including genuine
native-register negatives), F628 3 landing cases, native mode63,
30 earlier cases and separately owned afterRET packed switch DATA.
No case interior is an accepted exact whole native game function.
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
SOURCE=ROOT/'probes/FighterLandingTimerSiblingsF633.inc'
OUT=ROOT/'.analysis/f633-fighter-landing-siblings-source'
ACTIONS=(0x97,0x98,0x9A)
NEXT_ACTION={0x97:0x98,0x98:0x9A,0x9A:0x9B,0x9B:0x9C,0x9C:0x9E}
INITIAL={0x97:-10.0,0x98:-13.0,0x9A:-9.0,0x9B:-10.0,0x9C:-13.0}
NEXT_MOVE={0x97:0,0x98:0,0x9A:2,0x9B:2,0x9C:2}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'native original source helper unavailable '+str(path))
    obj=importlib.util.module_from_spec(spec)
    sys.modules[name]=obj
    spec.loader.exec_module(obj)
    return obj


def original_case(reader,pe,decoder,boss,by,action):
    addr=boss['address']
    start,end=by[action],by[NEXT_ACTION[action]]
    next_pc=min((x for x in set(by.values()) if x>start),default=None)
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    count=75 if addr in (0x0058AF60,0x00543210) else 73
    size=342 if addr==0x00564BE0 else (288 if count==75 else 276)
    need(addr<start<end<addr+boss['size'] and end==next_pc
         and len(native)==count and sum(x.size for x in native)==end-start==size
         and native[-1].mnemonic=='jmp',
         f'{addr:#x} action{action:#x}: real native entire case extent/73-75 x86 differs')
    candidates=[(i,x) for i,x in enumerate(native)
         if x.mnemonic=='mov' and re.fullmatch(
             r'dword ptr \[[a-z]+ \+ 0x50\], 0xc[0-9a-f]+',x.op_str)]
    need(len(candidates)==1 and candidates[0][0] in (24,26),
         f'{addr:#x} action{action:#x}: native real float initial-height store changed')
    pos_index,move=candidates[0]
    bits=int(move.op_str.rsplit(', ',1)[-1],16)
    height=struct.unpack('<f',struct.pack('<I',bits))[0]
    need(height==INITIAL[action]
         and native[0].mnemonic=='mov'
         and native[1].mnemonic=='fld' and '+ 0x368]' in native[1].op_str
         and native[2].mnemonic=='fadd'
         and native[7].mnemonic=='fcomp'
         and native[9].mnemonic=='test' and native[9].op_str=='ah, 0x41'
         and native[10].mnemonic=='jne'
         and native[12].mnemonic=='mov' and native[12].op_str.endswith(', 0x447a0000')
         and native[14].mnemonic=='movsx' and '+ 0x62]' in native[14].op_str
         and native[18].mnemonic=='movsx' and '+ 0x64]' in native[18].op_str,
         f'{addr:#x} action{action:#x}: original animation/physics initial native x86 changed')
    counter=0xEFC if addr==0x005AEEC0 else 0xF00
    extra=count==75
    before=extra and '+ 0xf0a]' in native[22].op_str
    need(native[22].mnemonic=='mov'
         and f'+ 0x{0xF0A if before else counter:x}]' in native[22].op_str,
         f'{addr:#x}: original real 16-bit motion counter first assignment changed')
    if extra:
        flag_at=22 if before else 30
        need(native[flag_at].mnemonic=='mov' and '+ 0xf0a]' in native[flag_at].op_str
             and native[flag_at].op_str.endswith(', 0')
             and before==(addr==0x0058AF60),
             f'{addr:#x}: original actor-specific extra short reset BEFORE/AFTER differs')
    shift=2 if extra else 0
    need(native[31+shift].mnemonic=='fcomp'
         and native[33+shift].op_str=='ah, 5'
         and native[34+shift].mnemonic=='jp'
         and native[37+shift].mnemonic=='fadd'
         and native[42+shift].mnemonic=='fcomp'
         and native[44+shift].op_str=='ah, 0x41'
         and native[45+shift].mnemonic=='jne'
         and native[49+shift].mnemonic=='call'
         and native[54+shift].mnemonic=='movsx' and '+ 0x3be]' in native[54+shift].op_str
         and native[59+shift].mnemonic=='fmul' and native[59+shift].op_str=='qword ptr [0x6583e8]'
         and native[61+shift].mnemonic=='fstp' and '+ 0x490]' in native[61+shift].op_str
         and native[69+shift].mnemonic=='push'
         and native[69+shift].op_str==str(NEXT_MOVE[action]),
         f'{addr:#x} action{action:#x}: original native strict x87 ground or next action0/2 differs')
    return native,{'original_case':f'0x{action:02X}',
                   'original_full_native_start':f'0x{start:08X}',
                   'original_full_native_next_case':f'0x{end:08X}',
                   'original_complete_case_CODE_bytes':size,
                   'original_whole_case_x86_instructions':count,
                   'native_trajectory_counter_offset':counter,
                   'original_initial_float_height':height,
                   'original_followup_action_state':NEXT_MOVE[action],
                   'real_extra_short_0xF0A':extra,
                   'real_extra_short_before_trajectory_counter':before,
                   'original_real_typed_PE_COFF_fields':9,
                   'enclosing_original_fighter_whole_exact':False}


def natural_source(addr,boss,report,mapped,reader,pe,decoder,h,properties):
    by={x['action']:int(x['handler'],16) for x in mapped}
    earlier,info=h['f631'].original_case(reader,pe,decoder,boss,by)
    source=h['f631'].source_with_case(addr,boss,report,mapped,reader,pe,decoder,h,info)
    for action in ACTIONS:
        native,meta=properties[action]
        definition={
           'F633_CASE':f'0x{action:X}',
           'F633_COUNTER':f'0x{meta["native_trajectory_counter_offset"]:X}',
           'F633_START_HEIGHT':repr(meta['original_initial_float_height'])+'f',
           'F633_NEXT_ACTION':str(meta['original_followup_action_state']),
           'F633_EXTRA_FLAG':str(int(meta['real_extra_short_0xF0A'])),
           'F633_EXTRA_BEFORE':str(int(meta['real_extra_short_before_trajectory_counter']))}
        needle=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(needle)==1,
             f'{addr:#x}: prior whole-giant VC7.1 source actual action{action:#x} marker lost')
        inserted='\n'.join('#define '+k+' '+v for k,v in definition.items())
        inserted+='\n#include "FighterLandingTimerSiblingsF633.inc"\n'
        inserted+='\n'.join('#undef '+k for k in definition)
        source=source.replace(needle,inserted)
    need(source.count('        case 0x9B: g_FighterProbeMarker = 156; break;')==1,
         f'{addr:#x}: genuine following native indexed 0x9B source marker absent')
    return source


def verify_fresh_whole(reader,pe,decoder,boss,report,mapped,code,refs,properties,h,extra_followup_x86=0):
    addr=boss['address'];inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',f'{addr:#x}: whole-parent final RET absent')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original complete physically owned after-RET dense/sparse DATA differs')
    # Re-check prior 0x96 / 0x91 and strict earlier real game cases and
    # physical jump DATA on THIS newly extended source OBJ, not stale
    # individual compiler objects nor mere marker/subrange identity.
    by={x['action']:int(x['handler'],16) for x in mapped}
    earlier,prior_info=h['f631'].original_case(reader,pe,decoder,boss,by)
    counts=sum(properties[action][1]['original_whole_case_x86_instructions'] for action in ACTIONS)
    expected=3*prior_info['original_complete_x86_instructions']
    need(counts==expected and counts in (219,225)
         and extra_followup_x86 in (0,2*73,2*75)
         and (not extra_followup_x86 or extra_followup_x86==2*prior_info['original_complete_x86_instructions']),
         f'{addr:#x}: authentic 73/75-x86 native case count or followup differs')
    h['f631'].verify_new_obj(reader,pe,decoder,boss,report,mapped,code,refs,
        earlier,prior_info,h,extra_sibling_x86=counts+extra_followup_x86)
    wanted=0x9C if extra_followup_x86==0 else 0x9F
    markers=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:continue
        native_ins=next((x for x in inst if x.address<=field['offset']<x.address+x.size),None)
        if native_ins is not None and native_ins.mnemonic=='mov' and native_ins.op_str.endswith(f', 0x{wanted:x}'):
            markers.append(native_ins)
    need(len(markers)==1,
         f'{addr:#x}: actual next original source case0x9B must be unambiguously COFF-marked')
    endindex=inst.index(markers[0])
    need(endindex>=counts+extra_followup_x86,
         f'{addr:#x}: source last three original native case bodies truncated by followup')
    candidates=inst[endindex-counts-extra_followup_x86:endindex-extra_followup_x86]
    next_case_pc=(inst[endindex-extra_followup_x86].address if extra_followup_x86 else markers[0].address)
    need(candidates[-1].address+candidates[-1].size==next_case_pc,
         f'{addr:#x}: original source full case0x9A must end at case0x9B')
    result=[]
    offset=0
    for action in ACTIONS:
        native,meta=properties[action]
        num=meta['original_whole_case_x86_instructions']
        source=candidates[offset:offset+num];offset+=num
        need(len(source)==len(native)==num
             and source[-1].mnemonic=='jmp',
             f'{addr:#x}: original action{action:#x} entire x86 extent missing')
        widths=[n.size-c.size for n,c in zip(native,source)]
        if addr==0x00564BE0:
            need(widths.count(3)==22 and widths.count(0)==num-22
                 and all(native[j].op_str.endswith('dword ptr [ebp - 0x88]')
                     for j,w in enumerate(widths) if w==3),
                 f'{addr:#x}: real native 22 wides saved-this EBP receiver per sibling case differ')
        else:need(all(v==0 for v in widths),
             f'{addr:#x} case{action:#x}: source/PE native compact instruction widths differ')
        first=source[0].address;last=source[-1].address+source[-1].size
        need(last-first==(288 if num==75 else 276),
             f'{addr:#x} action{action:#x}: normal VC7.1 C++ not native 276/288 whole case grammar')
        refs_here=[x for x in refs if first<=x['offset']<last]
        need(len(refs_here)==9,
             f'{addr:#x} case{action:#x}: actual nine physical typed PE/COFF fields missing')
        for ordinal,(target,mn,symbol) in h['f631'].FIELDS.items():
            index=ordinal+(2 if num==75 and ordinal>=31 else 0)
            a,b=native[index],source[index]
            want=f'0x{target:x}' if mn=='call' else (
                 f'qword ptr [0x{target:x}]' if mn=='fmul' else f'dword ptr [0x{target:x}]')
            need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
                 f'{addr:#x} action{action:#x}: original x86 ordinal{index} PE target {target:#x} changed')
            fields=[x for x in refs_here if b.address<=x['offset']<b.address+b.size]
            need(len(fields)==1 and fields[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and fields[0]['addend']==0 and fields[0]['local_symbol_offset'] is None
                 and symbol in fields[0]['symbol'],
                 f'{addr:#x} action{action:#x}: genuine PE/COFF physical source field {target:#x} at{index} differs')
        na,ga=h['f598'].normalized(native),h['f598'].normalized(source)
        differences=[(i,n,g) for i,(n,g) in enumerate(zip(na,ga)) if n!=g]
        need(not differences,
             f'{addr:#x} action{action:#x}: original GPR/x87/CFG roles differ: {differences[:7]}')
        result.append({'original_complete_action':meta['original_case'],
                       'original_whole_native_case_CODE_bytes':meta['original_complete_case_CODE_bytes'],
                       'original_native_complete_x86_GPR_x87_CFG_roles':num,
                       'actual_native_PE_COFF_call_and_global_fields':len(refs_here),
                       'native_original_saved_this_wide_MOVis':22 if addr==0x00564BE0 else 0,
                       'new_whole_game_function_exact_credit':False})
    need(offset==len(candidates),f'{addr:#x}: source entire 97/98/9A original complete case span differs')
    return {'whole_original_fighter':f'0x{addr:08X}',
            'whole_original_entire_giant_CODE_still_NONEXACT':boss['size'],
            'separately_owned_original_after_RET_jump_DATA':boss['postret_size'],
            'previous_native_action96_arc91_F628_30_cases_and_jump_table_rechecked':True,
            'original_native_three_new_complete_case_bodies':result,
            'strict_original_inner_CODE_bytes_UNCREDITED':sum(x['original_whole_native_case_CODE_bytes'] for x in result),
            'new_accepted_whole_authored_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original fighter giant, default all eleven affected whole TUs')
    options=parser.parse_args()
    modules={
      'f602':'scripts/verify-fighter-trajectory46-f602.py',
      'f603':'scripts/verify-fighter-trajectory-spawn-f603.py',
      'f600':'scripts/verify-fighter-additional-contact-f600.py',
      'f598':'scripts/verify-fighter-singleton-contact-f598.py',
      'f567':'scripts/verify-fighter-all-multiswitch-opening-cases.py',
      'f605':'scripts/verify-fighter-trajectory-followups-f605.py',
      'f606':'scripts/verify-fighter-trajectory-followup-spawns-f606.py',
      'f607':'scripts/verify-fighter-trajectory-landing-f607.py',
      'f608':'scripts/verify-fighter-trajectory-landing-spawn-f608.py',
      'f610':'scripts/verify-fighter-trajectory-bounce-f610.py',
      'f611':'scripts/verify-fighter-trajectory-bounce-spawn-f611.py',
      'f613':'scripts/verify-fighter-trajectory-recovery-f613.py',
      'f614':'scripts/verify-fighter-trajectory-burst-f614.py',
      'f622':'scripts/verify-fighter-counter-dispatch-f622.py',
      'f624':'scripts/verify-fighter-mode63-f624.py',
      'f626':'scripts/verify-fighter-mode63-basic-f626.py',
      'f627_priority':'scripts/verify-fighter-mode63-priority-f627.py',
      'f628':'scripts/verify-fighter-jump-landings-f628.py',
      'f629':'scripts/verify-fighter-arc91-f629.py',
      'f631':'scripts/verify-fighter-landing-timer96-f631.py',
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    helpers={name:load('f633_'+name,ROOT/p) for name,p in modules.items()}
    reader=load('f633_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f633_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    cohort=(*helpers['f628'].POSITIVE,0x004F7130,0x0045DD70,0x0058AF60)
    need(len(set(cohort))==len(cohort)==11,'actual original whole fighter 0x97 case cohort changed')
    selected=[int(options.boss,0)] if options.boss else list(cohort)
    need(all(addr in cohort for addr in selected),
         'original actor not in the true native 11 fighter 97/98/9A source family')
    text=SOURCE.read_text()
    need(text.count('case F633_CASE:')==1
         and 'POS=F633_START_HEIGHT;' in text
         and 'F633_NEXT_ACTION' in text
         and 'F633_EXTRA_BEFORE' in text
         and 'g_JumpReflectionAt006583E8' in text,
         'real native 97/98/9A C++ physics/owner parameter source changed')
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    receipts=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        cases={ac:original_case(reader,pe,decoder,boss,by,ac) for ac in ACTIONS}
        source=natural_source(addr,boss,report,mapped,reader,pe,decoder,helpers,cases)
        cpp=OUT/f'Boss{addr:08X}-38-native-original-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-38-native-original-actions.obj'
        cpp.write_text(source)
        comp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=185)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(comp.stdout+comp.stderr)
        need(comp.returncode==0,
             f'{addr:#x}: real native VC7.1 whole fighter source compile failed: {comp.stderr[-500:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        verified=verify_fresh_whole(reader,pe,decoder,boss,report,mapped,code,refs,cases,helpers)
        receipts.append(verified)
        print(f'F633 {addr:#010x}: native complete 97/98/9A each '
              f'{cases[0x97][1]["original_whole_case_x86_instructions"]}/'
              f'{cases[0x97][1]["original_whole_case_x86_instructions"]} x86 roles, '
              f'{verified["strict_original_inner_CODE_bytes_UNCREDITED"]} original CODE B '
              'for three real inner cases, 27/27 actual typed COFF, '
              'previous 0x96/0x91/0x63 +30 true game cases and full afterRET DATA '
              'rechecked in one whole giant VC7.1 OBJ; giant NONEXACT',flush=True)
    path=OUT/('summary.json' if not options.boss else f'summary-{selected[0]:08X}.json')
    path.write_text(json.dumps(receipts,indent=2)+'\n')
    print(f'F633 {len(receipts)} whole giant source TUs, '
          f'{len(receipts)*3} strict true original complete *internal* cases, '
          f'{sum(c["original_native_complete_x86_GPR_x87_CFG_roles"] for r in receipts for c in r["original_native_three_new_complete_case_bodies"])} '
          'original x86 roles / '
          f'{sum(r["strict_original_inner_CODE_bytes_UNCREDITED"] for r in receipts)} '
          f'UNcredited inner native CODE bytes / {len(receipts)*27} original PE/COFF fields; '
          'ZERO new complete whole authored match units, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F633 original Japanese 97/98/9A complete native case proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
