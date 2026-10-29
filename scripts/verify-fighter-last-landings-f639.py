#!/usr/bin/env python3
"""F639: true native 9F/A0/A1 landing actions in 11 still-nonexact fighters.

Freshly compile only selected whole VC7.1 fighter Advance() C++ parent
source TUs. Recheck three complete actual 73-x86 physical case bodies,
actual 0/0/0 action targets, native -9/-10/-13 float initializers,
9 real PE-typed zero-addend COFF fields per case, and 22 real wide
EBP-0x88 receiver MOVs in the unique wide owner. Recursively check
F637 action9E, F636 pair, F633 trio, F631 action96, earlier 91,
original 30 game cases and complete separately owned jump DATA in
this SAME newly built object. This is not whole-fighter acceptance.
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
OUT=ROOT/'.analysis/f639-fighter-last-landings-source'
ACTIONS=(0x9F,0xA0,0xA1)


def need(condition,message):
    if not condition:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing original PE source helper '+str(path))
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def actual_source(addr,boss,report,mapped,reader,pe,decoder,h,originals):
    by={x['action']:int(x['handler'],16) for x in mapped}
    earlier,earlier_info=h['f637'].original_case(reader,pe,decoder,boss,by)
    source=h['f637'].source_with_ground_boost(addr,boss,report,mapped,reader,pe,decoder,h,earlier_info)
    for action in ACTIONS:
        native,info=originals[action]
        need(info['original_whole_case_x86_instructions']==73
             and info['original_followup_action_state']==0
             and not info['real_extra_short_0xF0A'],
             f'{addr:#x}: original actual 9F/A0/A1 normal landing family differs')
        params={'F633_CASE':f'0x{action:X}',
                'F633_COUNTER':f'0x{info["native_trajectory_counter_offset"]:X}',
                'F633_START_HEIGHT':repr(info['original_initial_float_height'])+'f',
                'F633_NEXT_ACTION':str(info['original_followup_action_state']),
                'F633_EXTRA_FLAG':'0',
                'F633_EXTRA_BEFORE':'0'}
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(marker)==1,
             f'{addr:#x}: preceding original giant C++ source 0x{action:X} marker lost')
        addition='\n'.join('#define '+k+' '+v for k,v in params.items())
        addition+='\n#include "FighterLandingTimerSiblingsF633.inc"\n'
        addition+='\n'.join('#undef '+k for k in params)
        source=source.replace(marker,addition)
    need(source.count('        case 0xA3: g_FighterProbeMarker = 164; break;')==1,
         f'{addr:#x}: true following original action0xA3 source marker missing')
    return source


def check_fresh_whole(reader,pe,decoder,boss,report,mapped,code,refs,originals,h):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',
         f'{addr:#x}: giant C++ parent lacks true native final RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original entire separate afterRET dense/sparse jump DATA extent changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    earlier,meta=h['f637'].original_case(reader,pe,decoder,boss,by)
    # The full true predecessor original grammar/PE fields and all
    # its older actual source-backed cases + DATA must remain exact
    # on THIS new C++ parent object, not an earlier compiled one.
    h['f637'].verify_source(reader,pe,decoder,boss,report,mapped,code,refs,
                             earlier,meta,h,extra_after_9e_x86=3*73)
    markers=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:continue
        n=next((x for x in ins if x.address<=field['offset']<x.address+x.size),None)
        if n is not None and n.mnemonic=='mov' and n.op_str.endswith(', 0xa4'):
            markers.append(n)
    need(len(markers)==1,
         f'{addr:#x}: actual next native action0xA3 full-C++ boundary is not unique')
    end=ins.index(markers[0])
    count=3*73
    need(end>=count,f'{addr:#x}: source original 3×73 x86 cut off before next action')
    instructions=ins[end-count:end]
    need(instructions[-1].address+instructions[-1].size==markers[0].address,
         f'{addr:#x}: true native complete case0xA1 must end at next action0xA3 marker')
    receipts=[]
    for ordinal,action in enumerate(ACTIONS):
        original,info=originals[action]
        src=instructions[ordinal*73:(ordinal+1)*73]
        need(len(src)==len(original)==73 and src[-1].mnemonic=='jmp',
             f'{addr:#x}: complete original action0x{action:X} whole x86 body truncated')
        widths=[n.size-c.size for n,c in zip(original,src)]
        if addr==0x00564BE0:
            need(widths.count(3)==22 and widths.count(0)==51
                 and all(original[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,v in enumerate(widths) if v==3),
                 f'{addr:#x}: real native original 22 EBP-0x88 saved-this MOV widenings differ')
        else:need(all(v==0 for v in widths),
                  f'{addr:#x}: source compact original case0x{action:X} opcode widths changed')
        low,high=src[0].address,src[-1].address+src[-1].size
        need(high-low==276,
             f'{addr:#x}: actual natural VC7.1 case0x{action:X} not complete 276-byte source')
        real_fields=[f for f in refs if low<=f['offset']<high]
        need(len(real_fields)==9,
             f'{addr:#x}: source case0x{action:X} has wrong original physical PE/COFF target count')
        for index,(target,mn,symbol) in h['f631'].FIELDS.items():
            orig,gen=original[index],src[index]
            expected=f'0x{target:x}' if mn=='call' else (
                     f'qword ptr [0x{target:x}]' if mn=='fmul'
                     else f'dword ptr [0x{target:x}]')
            need(orig.mnemonic==gen.mnemonic==mn and orig.op_str==expected,
                 f'{addr:#x}: true original case0x{action:X} native typed PE x86 ordinal{index} differs')
            matched=[f for f in real_fields if gen.address<=f['offset']<gen.address+gen.size]
            need(len(matched)==1
                 and matched[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and matched[0]['addend']==0 and matched[0]['local_symbol_offset'] is None
                 and symbol in matched[0]['symbol'],
                 f'{addr:#x}: original case0x{action:X} typed native PE destination {target:#x} at {index} differs')
        lhs,rhs=h['f598'].normalized(original),h['f598'].normalized(src)
        bad=[(i,n,c) for i,(n,c) in enumerate(zip(lhs,rhs)) if n!=c]
        need(not bad,f'{addr:#x} case0x{action:X}: actual original GPR/x87/CFG source roles differ: {bad[:5]}')
        receipts.append({'native_original_action':info['original_case'],
                         'real_original_complete_inner_CODE_bytes':info['original_complete_case_CODE_bytes'],
                         'original_x86_instruction_roles':73,
                         'real_native_pe_typed_coff_fields':9,
                         'original_initial_signed_float':info['original_initial_float_height'],
                         'new_whole_game_function_credit':0})
    return {'original_parent_giant':f'0x{addr:08X}',
            'whole_original_giant_CODE_still_NONEXACT':boss['size'],
            'full_original_separate_afterRET_jump_DATA_bytes':boss['postret_size'],
            'old_9E_9B_9C_97_98_9A_96_91_mode63_30_cases_rechecked_on_new_OBJ':True,
            'three_new_native_complete_inner_cases':receipts,
            'original_strict_uncredited_inner_CODE_bytes':sum(x['real_original_complete_inner_CODE_bytes'] for x in receipts),
            'new_accepted_exact_whole_authored_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one original giant fighter, default 11 newly affected full source TUs')
    args=p.parse_args()
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
      'f633':'scripts/verify-fighter-landing-siblings-f633.py',
      'f636':'scripts/verify-fighter-landing-pair-f636.py',
      'f637':'scripts/verify-fighter-ground-boost-f637.py',
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    h={name:load('f639_'+name,ROOT/path) for name,path in modules.items()}
    rd=load('f639_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f639_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    cohort=(*h['f628'].POSITIVE,0x004F7130,0x0045DD70,0x0058AF60)
    need(len(set(cohort))==len(cohort)==11,'actual original 11 fighter native action9F family changed')
    selected=[int(args.boss,0)] if args.boss else list(cohort)
    need(all(a in cohort for a in selected),'selected original giant lacks this true 9F/A0/A1 native case family')
    cpp=(ROOT/'probes/FighterLandingTimerSiblingsF633.inc').read_text()
    need(cpp.count('case F633_CASE:')==1 and 'F633_START_HEIGHT' in cpp
         and 'F633_NEXT_ACTION' in cpp and 'g_JumpReflectionAt006583E8' in cpp,
         'ordinary original per-actor landing C++ source changed')
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    results=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(rd,pe,decoder,boss)
        by={q['action']:int(q['handler'],16) for q in mapped}
        original={action:h['f633'].original_case(rd,pe,decoder,boss,by,action)
                  for action in ACTIONS}
        source=actual_source(addr,boss,report,mapped,rd,pe,decoder,h,original)
        cpp=OUT/f'Boss{addr:08X}-44-original-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-44-original-game-actions.obj'
        cpp.write_text(source)
        comp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(comp.stdout+comp.stderr)
        need(comp.returncode==0,
             f'{addr:#x}: normal pinned VC7.1 entire fighter source build failed: {comp.stderr[-460:]}')
        code,refs=rd.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        receipt=check_fresh_whole(rd,pe,decoder,boss,report,mapped,code,refs,original,h)
        results.append(receipt)
        print(f'F639 {addr:#010x}: original actual action9F/A0/A1 three full '
              '73/73 x86 native GPR/x87/CFG case roles, '
              f'{receipt["original_strict_uncredited_inner_CODE_bytes"]} '
              'original inner CODE bytes, 27 true typed PE/COFF fields; '
              'previous 9E, prior 9B/9C/97/98/9A/96/91/63, '
              '30 early game actions and all original afterRET jump DATA '
              'preserved on same newly built whole fighter; giant NONEXACT.',flush=True)
    output=OUT/('summary.json' if not args.boss else f'summary-{selected[0]:08X}.json')
    output.write_text(json.dumps(results,indent=2)+'\n')
    print(f'F639 {len(results)} selected giant whole-source TUs, '
          f'{sum(len(r["three_new_native_complete_inner_cases"]) for r in results)} '
          f'complete original internal cases, '
          f'{len(results)*219} native x86 roles, '
          f'{sum(r["original_strict_uncredited_inner_CODE_bytes"] for r in results)} '
          f'uncredited original inner CODE bytes, {len(results)*27} '
          'physical typed PE/COFF. Zero new accepted whole authored '
          'functions, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as err:
        print('F639 original Japanese TH075 last landing source proof failed:',err,file=sys.stderr)
        raise SystemExit(1)
