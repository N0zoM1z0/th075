#!/usr/bin/env python3
"""F646/F647: genuine native CF+D0 source grammar in selected giants.

Cold-build ONLY the three selected full huge fighter VC7.1 parent
C++ TUs. Original 00564BE0 and 005214B0 strict D0 (60 x86 each);
original 00543210 strict CF (30 x86) AND D0 (60 x86) in one
actual whole-parent object. Reverify earlier F645 22 B4/B5 cases,
F642 A7/A8, all older original game cases and afterRET jump DATA.
Unselected actor D0 originals remain genuine GPR register negatives;
these original interior cases are not accepted independent functions.
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
OUT=ROOT/'.analysis/f646-fall-reflect-verified'
POSITIVE={0x00564BE0,0x005214B0,0x00543210}
CF_OWNER=0x00543210
CF_SOURCE=ROOT/'probes/FighterFallStateCFF647.inc'
D0_SOURCE=ROOT/'probes/FighterReflectLandingD0F646.inc'
FIELDS={
  0xCF:{
       4:(0x00657478,'fsub','g_SubtractAt00657478'),
       9:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
       18:(0x0040FA30,'call','GetNativeActionAt40FA30'),
       26:(0x0040FAC0,'call','SetNativeActionAt40FAC0')},
  0xD0:{
       19:(0x0065782C,'fld','g_ThresholdAt0065782C'),
       37:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
       43:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
       47:(0x00453E20,'call','ResetAt453E20'),
       50:(0x0040FA30,'call','GetNativeActionAt40FA30'),
       58:(0x0040FB40,'call','SetAuxActionAt40FB40')},
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         'original native PE source helper absent '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def native_case(reader,pe,decoder,boss,by,action):
    addr=boss['address']
    start=by[action]
    next_action=0xD0 if action==0xCF else None
    end=(by[next_action] if next_action is not None else
         min((x for x in set(by.values()) if x>start),default=None))
    need(end is not None,f'{addr:#x}: pinned original native next handler missing')
    original=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    count=30 if action==0xCF else 60
    expected=114 if action==0xCF else 252 if addr==0x00564BE0 else 195
    need(addr<start<end<addr+boss['size']
         and len(original)==count
         and sum(x.size for x in original)==end-start==expected
         and original[-1].mnemonic=='jmp',
         f'{addr:#x} action{action:#x}: complete original physical case start/end/width differs')
    if action==0xCF:
        need(addr==CF_OWNER
             and original[1].mnemonic=='mov' and '+ 0x3ac]' in original[1].op_str
             and original[1].op_str.endswith(', 1')
             and original[4].mnemonic=='fsub' and original[4].op_str=='dword ptr [0x657478]'
             and original[9].mnemonic=='fcomp' and original[9].op_str=='dword ptr [0x65782c]'
             and original[11].mnemonic=='test' and original[11].op_str=='ah, 5'
             and original[12].mnemonic=='jp'
             and original[16].mnemonic=='mov' and original[16].op_str.endswith(', 0')
             and original[24].mnemonic=='push' and original[24].op_str=='0'
             and original[28].mnemonic=='mov' and original[28].op_str.endswith(', 0'),
             f'{addr:#x}: real original CF fade/ground/frame transition changed')
    else:
        need(original[1].mnemonic=='movsx' and '+ 0x62]' in original[1].op_str
             and original[5].mnemonic=='movsx' and '+ 0x64]' in original[5].op_str
             and original[9].mnemonic=='movsx' and '+ 0x66]' in original[9].op_str
             and original[10].mnemonic=='neg'
             and original[12].mnemonic=='mov' and '+ 0x66]' in original[12].op_str
             and original[15].mnemonic=='fchs'
             and original[19].mnemonic=='fld' and original[19].op_str=='dword ptr [0x65782c]'
             and original[20].mnemonic=='fld' and '+ 0x5c]' in original[20].op_str
             and original[21].mnemonic=='fucompp'
             and original[23].mnemonic=='test' and original[23].op_str=='ah, 0x44'
             and original[24].mnemonic=='jp'
             and original[26].mnemonic=='mov' and original[26].op_str.endswith(', 0x3f19999a')
             and original[30].mnemonic=='fsub' and '+ 0x5c]' in original[30].op_str
             and original[37].mnemonic=='fcomp' and original[37].op_str=='dword ptr [0x65782c]'
             and original[39].mnemonic=='test' and original[39].op_str=='ah, 0x41'
             and original[40].mnemonic=='jp'
             and original[41].mnemonic=='push' and original[41].op_str=='0xa'
             and original[56].mnemonic=='push' and original[56].op_str=='5',
             f'{addr:#x}: native original D0 signflip/FUCOMPP/ground/AUX semantics changed')
    for i,(target,mn,_) in FIELDS[action].items():
        ins=original[i]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(ins.mnemonic==mn and ins.op_str==want,
             f'{addr:#x} native action{action:#x}: real original PE target {target:#x} at x86{i} changed')
    return original,{'original_action':f'0x{action:02X}',
                     'actual_physical_original_handler':f'0x{start:08X}',
                     'actual_physical_original_next_handler':f'0x{end:08X}',
                     'original_complete_native_inner_CODE_bytes':expected,
                     'real_original_x86_roles':count,
                     'actual_physical_PE_COFF_fields':len(FIELDS[action]),
                     'whole_enclosing_fighter_exact':False}


def source_with_cases(addr,boss,report,mapped,reader,pe,decoder,h,originals):
    by={row['action']:int(row['handler'],16) for row in mapped}
    prior={act:h['f645'].native_case(reader,pe,decoder,boss,by,act)
           for act in h['f645'].ACTIONS}
    src=h['f645'].source_with_restart(addr,boss,report,mapped,reader,pe,decoder,h,prior)
    if addr==CF_OWNER:
        marker='        case 0xCF: g_FighterProbeMarker = 208; break;'
        need(src.count(marker)==1,f'{addr:#x}: actual original CF full source marker lost')
        src=src.replace(marker,'#include "FighterFallStateCFF647.inc"')
    marker='        case 0xD0: g_FighterProbeMarker = 209; break;'
    need(src.count(marker)==1,f'{addr:#x}: actual original D0 full source marker lost')
    return src.replace(marker,'#include "FighterReflectLandingD0F646.inc"')


def verify_fresh(reader,pe,decoder,boss,report,mapped,code,refs,originals,h):
    addr=boss['address'];inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',f'{addr:#x}: normal whole-parent fighter source final RET missing')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: entire separately owned original after-RET packed jump DATA changed')
    by={row['action']:int(row['handler'],16) for row in mapped}
    previous={action:h['f645'].native_case(reader,pe,decoder,boss,by,action)
              for action in h['f645'].ACTIONS}
    # Full pinned original B4/B5 and all predecessor PE/COFF source
    # cases, plus entire original jump DATA, are rechecked in this
    # SAME newly compiled whole C++ giant, not stale earlier output.
    h['f645'].verify_obj(reader,pe,decoder,boss,report,mapped,code,refs,previous,h)
    expected=(0xCF,0xD0) if addr==CF_OWNER else (0xD0,)
    num=sum(originals[action][1]['real_original_x86_roles'] for action in expected)
    unique={0xCF:0xCF,0xD0:0xD0}
    marker_value=(0xCF if addr==CF_OWNER else 0xD0)
    marks=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:continue
        idx=next((i for i,x in enumerate(inst)
                  if x.address<=field['offset']<x.address+x.size),None)
        if (idx is not None and inst[idx].mnemonic=='mov'
                and inst[idx].op_str.endswith(f', 0x{marker_value:x}')):
            marks.append(idx)
    need(len(marks)==1,
         f'{addr:#x}: preceding original CF or CE true source marker not uniquely typed')
    idx=marks[0]
    need(idx+2<len(inst) and inst[idx+1].mnemonic=='jmp',
         f'{addr:#x}: original previous case source marker does not directly exit via JMP')
    begin=idx+2
    produced=inst[begin:begin+num]
    need(len(produced)==num,f'{addr:#x}: whole original CF/D0 source physically truncated')
    need(produced[-1].mnemonic=='jmp',
         f'{addr:#x}: true final native D0 body must end with shared giant exit')
    results=[];offset=0
    for action in expected:
        original,meta=originals[action]
        count=meta['real_original_x86_roles']
        gen=produced[offset:offset+count];offset+=count
        need(len(gen)==len(original)==count and gen[-1].mnemonic=='jmp',
             f'{addr:#x}: native complete action{action:#x} source case x86 truncated')
        widths=[n.size-g.size for n,g in zip(original,gen)]
        if addr==0x00564BE0 and action==0xD0:
            need(widths.count(3)==19 and widths.count(0)==41
                 and all(original[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,v in enumerate(widths) if v==3),
                 f'{addr:#x}: original D0 true 19 wide EBP−0x88 saved-this MOVs missing')
        else:need(all(v==0 for v in widths),
                  f'{addr:#x} case{action:#x}: original compact x86 instruction widths differ')
        first,last=gen[0].address,gen[-1].address+gen[-1].size
        need(last-first==(114 if action==0xCF else 195),
             f'{addr:#x} case{action:#x}: normal source full native CODE is not 114/195B')
        fields=[f for f in refs if first<=f['offset']<last]
        need(len(fields)==len(FIELDS[action]),
             f'{addr:#x} action{action:#x}: native physical COFF source target count changed')
        for i,(target,mn,symbol) in FIELDS[action].items():
            n,g=original[i],gen[i]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(n.mnemonic==g.mnemonic==mn and n.op_str==want,
                 f'{addr:#x} action{action:#x}: original physical PE global/call {target:#x} at x86{i} changed')
            actual=[f for f in fields if g.address<=f['offset']<g.address+g.size]
            need(len(actual)==1
                 and actual[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and actual[0]['addend']==0
                 and actual[0]['local_symbol_offset'] is None
                 and symbol in actual[0]['symbol'],
                 f'{addr:#x} action{action:#x}: source field at x86{i} not true native PE target {target:#x}')
        # The x86 decoder sees 0 for an UNLINKED original COFF field;
        # only the exact original global float field ordinals may be
        # normalized to that physical target AFTER verifying each
        # native PE instruction and its typed COFF record above.
        normalized_o,normalized_g=h['f598'].normalized(original),h['f598'].normalized(gen)
        absfields={i for i,(target,mn,sym) in FIELDS[action].items() if mn!='call'}
        mismatch=[(i,x,y) for i,(x,y) in enumerate(zip(normalized_o,normalized_g))
                  if x!=y and i not in absfields]
        need(not mismatch,
             f'{addr:#x} action{action:#x}: real original GPR/x87/CFG role mismatch: {mismatch[:8]}')
        results.append({'original_action':meta['original_action'],
                        'strict_native_whole_inner_CODE_bytes':meta['original_complete_native_inner_CODE_bytes'],
                        'strict_real_original_x86_roles':count,
                        'genuine_original_typed_PE_COFF_fields':len(fields),
                        'new_accepted_whole_game_functions':0})
    return {'actual_original_parent_giant':f'0x{addr:08X}',
            'entire_native_parent_giant_CODE_still_NONEXACT':boss['size'],
            'entire_actual_afterRET_switch_DATA_bytes':boss['postret_size'],
            'previous_F645_F642_F641_F639_30_actions_and_DATA_reverified_on_new_OBJ':True,
            'actually_strict_original_CF_D0_case_bodies':results,
            'original_strict_internal_CODE_bytes_uncredited':sum(x['strict_native_whole_inner_CODE_bytes'] for x in results),
            'new_accepted_complete_authored_functions':0}


def main():
    cli=argparse.ArgumentParser(description=__doc__)
    cli.add_argument('--boss',help='one actual strict 00564BE0, 005214B0 or 00543210 whole fighter source')
    opt=cli.parse_args()
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
      'f639':'scripts/verify-fighter-last-landings-f639.py',
      'f641':'scripts/verify-fighter-no-counter-landings-f641.py',
      'f642':'scripts/verify-fighter-projectile-launch-f642.py',
      'f645':'scripts/verify-fighter-motion-restart-f645.py',
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py',
    }
    h={name:load('f646_'+name,ROOT/path) for name,path in modules.items()}
    reader=load('f646_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f646_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    selected=([int(opt.boss,0)] if opt.boss else sorted(POSITIVE))
    need(all(a in POSITIVE for a in selected),
         'nine OTHER actual originals retain native 35/36-GPR register-role differences in D0')
    need(CF_SOURCE.read_text().count('case 0xCF:')==1
         and D0_SOURCE.read_text().count('case 0xD0:')==1
         and 'if (*(&POS5C)==g_ThresholdAt0065782C)' in D0_SOURCE.read_text()
         and 'POS=-POS;' in D0_SOURCE.read_text(),
         'real original 30/60-x86 natural C++ source grammar changed')
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    receipts=[]
    for addr in selected:
        boss=bosses[addr];report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        needed=(0xCF,0xD0) if addr==CF_OWNER else (0xD0,)
        originals={a:native_case(reader,pe,decoder,boss,by,a) for a in needed}
        cpp=OUT/f'Boss{addr:08X}-true-original-CF-D0.cpp'
        obj=OUT/f'Boss{addr:08X}-true-original-CF-D0.obj'
        cpp.write_text(source_with_cases(addr,boss,report,mapped,reader,pe,decoder,h,originals))
        proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
               '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
               cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(proc.stdout+proc.stderr)
        need(proc.returncode==0,
             f'{addr:#x}: original pinned VC7.1 full fighter source compile error: {proc.stderr[-520:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        res=verify_fresh(reader,pe,decoder,boss,report,mapped,code,refs,originals,h)
        receipts.append(res)
        print(f'F646/F647 {addr:#010x}: original complete cases '
              f'{[x["original_action"] for x in res["actually_strict_original_CF_D0_case_bodies"]]} '
              f'strict {res["original_strict_internal_CODE_bytes_uncredited"]} '
              'authentic native inner CODE bytes; full original PE/COFF, '
              'previous B4/B5/A7/A8 and all earlier cases and afterRET jump DATA '
              'rechecked on same whole fighter C++ object. Parent still NONEXACT.',flush=True)
    file=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    file.write_text(json.dumps(receipts,indent=2)+'\n')
    print(f'F646/F647 {len(receipts)} selected entire fighter VC7.1 source TUs, '
          f'{sum(len(r["actually_strict_original_CF_D0_case_bodies"]) for r in receipts)} '
          'strict actual internal case bodies / '
          f'{sum(r["original_strict_internal_CODE_bytes_uncredited"] for r in receipts)} '
          'original inner CODE bytes / '
          f'{sum(x["strict_real_original_x86_roles"] for r in receipts for x in r["actually_strict_original_CF_D0_case_bodies"])} '
          'native x86 roles / '
          f'{sum(x["genuine_original_typed_PE_COFF_fields"] for r in receipts for x in r["actually_strict_original_CF_D0_case_bodies"])} '
          'original typed COFF; no whole-function acceptance or all-unit replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F646/F647 Japanese TH075 original native CF/D0 source proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
