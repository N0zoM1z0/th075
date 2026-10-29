#!/usr/bin/env python3
"""F636: full original native 0x9B/0x9C landing cases across 11 giants.

Fresh VC7.1 compile ONLY the affected whole fighter C++ source TUs,
verify 22 real complete native case intervals and actual 73/75 native
GPR/x87/CFG register roles, physical 9 original typed PE/COFF fields
each; original true -10/-13 heights, action2, actor-specific +0xF0A
reset ordering, and saved wide EBP-0x88 receiver MOVs.
Reverify all prior F633 three cases, F631 0x96, F629/F630 0x91
(including remaining true register failures), F628 earlier actions,
prior 30 game-case grammars and separately owned afterRET DATA.
Do not adopt case interiors as independent whole native functions.
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
OUT=ROOT/'.analysis/f636-fighter-landing-pair-source'
ACTIONS=(0x9B,0x9C)


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'native original source helper unavailable '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def source_with_pair(addr,boss,report,mapped,reader,pe,decoder,h,properties):
    by={x['action']:int(x['handler'],16) for x in mapped}
    previous={ac:h['f633'].original_case(reader,pe,decoder,boss,by,ac)
              for ac in h['f633'].ACTIONS}
    source=h['f633'].natural_source(addr,boss,report,mapped,reader,pe,decoder,h,previous)
    for ac in ACTIONS:
        native,info=properties[ac]
        params={'F633_CASE':f'0x{ac:X}',
                'F633_COUNTER':f'0x{info["native_trajectory_counter_offset"]:X}',
                'F633_START_HEIGHT':repr(info['original_initial_float_height'])+'f',
                'F633_NEXT_ACTION':str(info['original_followup_action_state']),
                'F633_EXTRA_FLAG':str(int(info['real_extra_short_0xF0A'])),
                'F633_EXTRA_BEFORE':str(int(info['real_extra_short_before_trajectory_counter']))}
        placeholder=f'        case 0x{ac:X}: g_FighterProbeMarker = {ac+1}; break;'
        need(source.count(placeholder)==1,
             f'{addr:#x}: original next real action{ac:#x} C++ source marker missing')
        addition='\n'.join('#define '+k+' '+v for k,v in params.items())
        addition+='\n#include "FighterLandingTimerSiblingsF633.inc"\n'
        addition+='\n'.join('#undef '+k for k in params)
        source=source.replace(placeholder,addition)
    need(source.count('        case 0x9E: g_FighterProbeMarker = 159; break;')==1,
         f'{addr:#x}: next real action0x9E game source marker missing')
    return source


def strict_check(reader,pe,decoder,boss,report,mapped,code,refs,properties,h,extra_after_pair_x86=0):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: actual whole fighter source final RET missing')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original complete separately owned afterRET switch DATA lost')
    by={x['action']:int(x['handler'],16) for x in mapped}
    previous={ac:h['f633'].original_case(reader,pe,decoder,boss,by,ac)
              for ac in h['f633'].ACTIONS}
    count=sum(properties[ac][1]['original_whole_case_x86_instructions'] for ac in ACTIONS)
    expected=2*previous[0x97][1]['original_whole_case_x86_instructions']
    need(count==expected and count in (2*73,2*75)
         and extra_after_pair_x86 in (0,66,68,66+3*73,68+3*73)
         and (not extra_after_pair_x86 or
              extra_after_pair_x86 in (
                 (68 if count==2*75 else 66),
                 (68 if count==2*75 else 66)+3*73)),
         f'{addr:#x}: real native 9B/9C or next genuine 9E 66/68-x86 source extent changed')
    h['f633'].verify_fresh_whole(reader,pe,decoder,boss,report,mapped,code,refs,
                                 previous,h,extra_followup_x86=count+extra_after_pair_x86)
    following_marker=(0x9F if extra_after_pair_x86==0 else
                      0xA0 if extra_after_pair_x86 in (66,68) else 0xA4)
    markers=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:continue
        instruction=next((x for x in ins if x.address<=field['offset']<x.address+x.size),None)
        if instruction is not None and instruction.mnemonic=='mov' and instruction.op_str.endswith(f', 0x{following_marker:x}'):
            markers.append(instruction)
    need(len(markers)==1,
         f'{addr:#x}: actual next original action0x9E source marker not unique')
    end=ins.index(markers[0])
    need(end>=count+extra_after_pair_x86,
         f'{addr:#x}: original two complete 9B/9C cases truncated by next case9E')
    candidates=ins[end-count-extra_after_pair_x86:end-extra_after_pair_x86]
    actual_end=(ins[end-extra_after_pair_x86].address if extra_after_pair_x86 else markers[0].address)
    need(candidates[-1].address+candidates[-1].size==actual_end,
         f'{addr:#x}: actual complete native case0x9C must end at next original 0x9E')
    found=[];cur=0
    for ac in ACTIONS:
        native,meta=properties[ac]
        num=meta['original_whole_case_x86_instructions']
        source=candidates[cur:cur+num];cur+=num
        need(len(source)==len(native)==num and source[-1].mnemonic=='jmp',
             f'{addr:#x}: original native complete action{ac:#x} x86 source truncated')
        widths=[x.size-y.size for x,y in zip(native,source)]
        if addr==0x00564BE0:
            need(widths.count(3)==22 and widths.count(0)==num-22
                 and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,w in enumerate(widths) if w==3),
                 f'{addr:#x}: original wide EBP-0x88 22 receiver MOVs per 9B/9C case differ')
        else:need(all(w==0 for w in widths),
                  f'{addr:#x} action{ac:#x}: genuine original compact x86 opcode widths differ')
        low,high=source[0].address,source[-1].address+source[-1].size
        need(high-low==(288 if num==75 else 276),
             f'{addr:#x} action{ac:#x}: C++ source complete 73/75 native case geometry mismatch')
        physical=[f for f in refs if low<=f['offset']<high]
        need(len(physical)==9,
             f'{addr:#x} action{ac:#x}: original nine physical typed COFF target fields missing')
        for ordinal,(target,mn,symbol) in h['f631'].FIELDS.items():
            i=ordinal+(2 if num==75 and ordinal>=31 else 0)
            a,b=native[i],source[i]
            expected=f'0x{target:x}' if mn=='call' else (
                f'qword ptr [0x{target:x}]' if mn=='fmul' else f'dword ptr [0x{target:x}]')
            need(a.mnemonic==b.mnemonic==mn and a.op_str==expected,
                 f'{addr:#x} action{ac:#x}: native original PE x86 call/float ordinal{i} differs')
            refs_here=[f for f in physical if b.address<=f['offset']<b.address+b.size]
            need(len(refs_here)==1
                 and refs_here[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and refs_here[0]['addend']==0
                 and refs_here[0]['local_symbol_offset'] is None
                 and symbol in refs_here[0]['symbol'],
                 f'{addr:#x} action{ac:#x}: actual original target {target:#x} at ordinal{i} COFF differs')
        native_roles,src_roles=h['f598'].normalized(native),h['f598'].normalized(source)
        mismatch=[(i,n,s) for i,(n,s) in enumerate(zip(native_roles,src_roles)) if n!=s]
        need(not mismatch,
             f'{addr:#x} action{ac:#x}: complete original GPR/x87/CFG roles differ: {mismatch[:8]}')
        found.append({'original_native_action':meta['original_case'],
                      'original_entire_inner_CODE_bytes':meta['original_complete_case_CODE_bytes'],
                      'original_native_complete_x86_GPR_x87_CFG_roles':num,
                      'original_true_typed_PE_COFF_fields':9,
                      'new_accepted_exact_whole_functions':0})
    need(cur==len(candidates),f'{addr:#x}: real complete consecutive 9B/9C span source differs')
    return {'original_entire_boss':f'0x{addr:08X}',
            'original_whole_giant_CODE_still_NONEXACT':boss['size'],
            'separately_owned_original_afterRET_switch_DATA':boss['postret_size'],
            'prior_three_97_98_9A_case96_original_mode63_and_30_game_cases_rechecked':True,
            'two_true_original_case_bodies':found,
            'strict_native_inner_CODE_UNCREDITED_bytes':sum(x['original_entire_inner_CODE_bytes'] for x in found),
            'new_whole_exact_authored_functions':0}


def main():
    cli=argparse.ArgumentParser(description=__doc__)
    cli.add_argument('--boss',help='one of eleven whole original giant TUs, default just these 11 affected TUs')
    opt=cli.parse_args()
    loaders={
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
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    h={name:load('f636_'+name,ROOT/path) for name,path in loaders.items()}
    reader=load('f636_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f636_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    actors=(*h['f628'].POSITIVE,0x004F7130,0x0045DD70,0x0058AF60)
    need(len(actors)==len(set(actors))==11,'original native fighter pair actor cohort changed')
    selected=[int(opt.boss,0)] if opt.boss else list(actors)
    need(all(x in actors for x in selected),'not a member of eleven original 9B/9C native giants')
    source=(ROOT/'probes/FighterLandingTimerSiblingsF633.inc').read_text()
    need(source.count('case F633_CASE:')==1 and 'F633_START_HEIGHT' in source
         and 'F633_NEXT_ACTION' in source
         and 'F633_EXTRA_BEFORE' in source,
         'genuine normal C++ source cannot generate original 9B/9C physics')
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    receipts=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,dec,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        originals={a:h['f633'].original_case(reader,pe,dec,boss,by,a) for a in ACTIONS}
        source=source_with_pair(addr,boss,report,mapped,reader,pe,dec,h,originals)
        cpp=OUT/f'Boss{addr:08X}-40-native-original-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-40-native-original-actions.obj'
        cpp.write_text(source)
        cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                cwd=ROOT,env=env,capture_output=True,text=True,timeout=185)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,
             f'{addr:#x}: original pinned VC7.1 entire fighter source compilation failed: {cp.stderr[-500:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        result=strict_check(reader,pe,dec,boss,report,mapped,code,refs,originals,h)
        receipts.append(result)
        print(f'F636 {addr:#010x}: real original complete 9B/9C 2×'
              f'{originals[0x9B][1]["original_whole_case_x86_instructions"]} native x86, '
              f'{result["strict_native_inner_CODE_UNCREDITED_bytes"]} original inner CODE B, '
              '18/18 typed real PE/COFF, previous 97/98/9A, 96/91/63 and '
              '30 earlier game actions + afterRET DATA rechecked in same whole C++ source; '
              'giant still NONEXACT.',flush=True)
    file=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    file.write_text(json.dumps(receipts,indent=2)+'\n')
    print(f'F636 {len(receipts)} selected complete giant source TUs; '
          f'{len(receipts)*2} native strict original complete *internal* game cases, '
          f'{sum(x["original_native_complete_x86_GPR_x87_CFG_roles"] for r in receipts for x in r["two_true_original_case_bodies"])} '
          'real x86 roles / '
          f'{sum(r["strict_native_inner_CODE_UNCREDITED_bytes"] for r in receipts)} '
          f'UNcredited native interior CODE bytes / {len(receipts)*18} genuine typed COFF fields. '
          'No whole authored exact acceptance, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F636 original Japanese TH075 9B/9C fighter native proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
