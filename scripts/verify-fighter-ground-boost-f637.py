#!/usr/bin/env python3
"""F637: complete original action0x9E ground boost in eleven fighter giants.

Compile only affected whole VC7.1 fighter Advance() source TUs. Verify
original complete 66/68 x86 role/CFG/width, 8 genuinely typed PE/COFF
global and call fields, real 005D73C0 strict-above vs other actors'
greater-or-equal ground test, original 21 wide EBP-0x88 saved-this MOVs,
and two opposing extra short 0xF0A initialization orders.
Recheck preceding F636 pair, F633 trio, F631 action96, F629/630
real action91 (including negative GPR register cycles), prior 30 real
original game actions and separately owned complete afterRET jump DATA.
Case body is NOT an accepted complete original game function.
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
OUT=ROOT/'.analysis/f637-fighter-ground-boost-source'
SOURCE=ROOT/'probes/FighterGroundBoost9EF637.inc'
SPECIAL_STRICT_ABOVE=0x005D73C0
TWO_EXTRA=(0x00543210,0x0058AF60)
FIELDS={
    2:(0x0065747C,'fadd','g_AnimationDeltaAt0065747C'),
    7:(0x006583B4,'fcomp','g_AnimationMaximumAt006583B4'),
    29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
    43:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
    49:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    53:(0x00453E20,'call','ResetAt453E20'),
    56:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    64:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
}


def need(ok,msg):
    if not ok:
        raise ValueError(msg)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         'pinned original PE source helper unavailable '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address']
    start,end=by[0x9E],by[0x9F]
    next_handler=min((x for x in set(by.values()) if x>start),default=None)
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    count=68 if addr in TWO_EXTRA else 66
    size=306 if addr==0x00564BE0 else (255 if count==68 else 243)
    need(addr<start<end<addr+boss['size'] and end==next_handler
         and len(native)==count and end-start==size
         and sum(x.size for x in native)==size and native[-1].mnemonic=='jmp',
         f'{addr:#x}: actual entire native case0x9E->0x9F x86/physical extent differs')
    extra=count==68
    strict=addr==SPECIAL_STRICT_ABOVE
    count_offset=2 if extra else 0
    first_test=31+count_offset
    need(native[1].mnemonic=='fld' and '+ 0x368]' in native[1].op_str
         and native[2].mnemonic=='fadd' and native[2].op_str=='dword ptr [0x65747c]'
         and native[7].mnemonic=='fcomp' and native[7].op_str=='dword ptr [0x6583b4]'
         and native[9].mnemonic=='test' and native[9].op_str=='ah, 0x41'
         and native[12].mnemonic=='mov' and native[12].op_str.endswith(', 0x447a0000')
         and native[22 if not(extra and addr==0x0058AF60) else 24].mnemonic=='mov'
         and native[24 if not(extra and addr==0x0058AF60) else 26].op_str.endswith(', 0x41000000')
         and native[26 if not(extra and addr==0x0058AF60) else 28].op_str.endswith(', 0x3f400000')
         and native[first_test-2].mnemonic=='fcomp'
         and native[first_test].mnemonic=='test'
         and native[first_test].op_str==('ah, 0x41' if strict else 'ah, 1')
         and native[first_test+1].mnemonic=='jne'
         and native[45+count_offset].op_str=='ah, 0x41'
         and native[46+count_offset].mnemonic=='jp'
         and native[47+count_offset].mnemonic=='push'
         and native[47+count_offset].op_str=='0xa'
         and native[62+count_offset].mnemonic=='push'
         and native[62+count_offset].op_str=='9',
         f'{addr:#x}: original native x87 ground comparison/boost state or initial floats differ')
    need(native[22 if not(extra and addr==0x0058AF60) else 24].op_str.endswith(', 0xc0c00000'),
         f'{addr:#x}: original signed −6f initial displacement changed')
    if extra:
        flag_index=22 if addr==0x0058AF60 else 28
        need(native[flag_index].mnemonic=='mov'
             and '+ 0xf0a]' in native[flag_index].op_str
             and native[flag_index].op_str.endswith(', 0'),
             f'{addr:#x}: genuine native actor-specific extra short F0A initialization order changed')
    for ordinary,(target,mn,symbol) in FIELDS.items():
        ordinal=ordinary+(2 if extra and ordinary>=29 else 0)
        x=native[ordinal]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(x.mnemonic==mn and x.op_str==want,
             f'{addr:#x}: actual original PE typed global/call target {target:#x} at {ordinal} changed')
    return native,{'actual_original_native_start':f'0x{start:08X}',
                   'actual_next_original_handler_0x9F':f'0x{end:08X}',
                   'native_complete_original_inner_CODE_bytes':size,
                   'native_original_full_x86_instructions':count,
                   'strict_native_initial_ground_above_not_equal':strict,
                   'original_extra_short_0xF0A_reset':extra,
                   'original_extra_short_before_velocity':addr==0x0058AF60,
                   'original_real_PE_COFF_typed_fields':len(FIELDS),
                   'original_enclosing_giant_whole_exact':False}


def source_with_ground_boost(addr,boss,report,mapped,reader,pe,decoder,h,meta):
    by={x['action']:int(x['handler'],16) for x in mapped}
    previous={a:h['f633'].original_case(reader,pe,decoder,boss,by,a)
              for a in h['f636'].ACTIONS}
    cpp=h['f636'].source_with_pair(addr,boss,report,mapped,reader,pe,decoder,h,previous)
    needle='        case 0x9E: g_FighterProbeMarker = 159; break;'
    need(cpp.count(needle)==1,f'{addr:#x}: original source action0x9E marker absent')
    mapping={'F637_EXTRA_FLAG':str(int(meta['original_extra_short_0xF0A_reset'])),
             'F637_EXTRA_BEFORE':str(int(meta['original_extra_short_before_velocity'])),
             'F637_STRICT_ABOVE':str(int(meta['strict_native_initial_ground_above_not_equal']))}
    replacement='\n'.join('#define '+k+' '+v for k,v in mapping.items())
    replacement+='\n#include "FighterGroundBoost9EF637.inc"\n'
    replacement+='\n'.join('#undef '+k for k in mapping)
    result=cpp.replace(needle,replacement)
    need(result.count('        case 0x9F: g_FighterProbeMarker = 160; break;')==1,
         f'{addr:#x}: genuine next original action0x9F case marker missing')
    return result


def verify_source(reader,pe,decoder,boss,report,mapped,code,refs,native,meta,h,extra_after_9e_x86=0):
    addr=boss['address']
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':
            break
    need(ins and ins[-1].mnemonic=='ret',
         f'{addr:#x}: enclosing original giant source lacks final RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original separate afterRET packed jump DATA extent differs')
    by={x['action']:int(x['handler'],16) for x in mapped}
    previous={a:h['f633'].original_case(reader,pe,decoder,boss,by,a)
              for a in h['f636'].ACTIONS}
    need(extra_after_9e_x86 in (0,3*73),
         f'{addr:#x}: only genuine three 73-x86 original 9F/A0/A1 cases may follow 9E')
    h['f636'].strict_check(reader,pe,decoder,boss,report,mapped,code,refs,
                           previous,h,extra_after_pair_x86=len(native)+extra_after_9e_x86)
    wanted=0xA0 if extra_after_9e_x86==0 else 0xA4
    markers=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:
            continue
        x=next((i for i in ins if i.address<=field['offset']<i.address+i.size),None)
        if x is not None and x.mnemonic=='mov' and x.op_str.endswith(f', 0x{wanted:x}'):
            markers.append(x)
    need(len(markers)==1,
         f'{addr:#x}: genuine following original action0x9F source marker not uniquely COFF-typed')
    end=ins.index(markers[0]);num=meta['native_original_full_x86_instructions']
    need(end>=num+extra_after_9e_x86,
         f'{addr:#x}: actual source action0x9E native source truncated by newly reconstructed cases')
    cand=ins[end-num-extra_after_9e_x86:end-extra_after_9e_x86]
    true_next_pc=(ins[end-extra_after_9e_x86].address if extra_after_9e_x86
                  else markers[0].address)
    need(len(cand)==len(native)==num and cand[-1].mnemonic=='jmp'
         and cand[-1].address+cand[-1].size==true_next_pc,
         f'{addr:#x}: actual 9E→9F complete source physical case boundary lost')
    widths=[n.size-c.size for n,c in zip(native,cand)]
    if addr==0x00564BE0:
        need(widths.count(3)==21 and widths.count(0)==num-21
             and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i,diff in enumerate(widths) if diff==3),
             f'{addr:#x}: real original 21 EBP−0x88 receiver MOV width enlargements differ')
    else:
        need(all(w==0 for w in widths),
             f'{addr:#x}: actual normal native source 0x9E x86 opcode width differs')
    low,high=cand[0].address,cand[-1].address+cand[-1].size
    need(high-low==(255 if num==68 else 243),
         f'{addr:#x}: emitted source complete native case0x9E is not 243/255 bytes')
    fields=[f for f in refs if low<=f['offset']<high]
    need(len(fields)==8,
         f'{addr:#x}: 8 genuine typed physical PE-target COFF fields absent')
    for ordinal,(target,mn,symbol) in FIELDS.items():
        i=ordinal+(2 if num==68 and ordinal>=29 else 0)
        a,b=native[i],cand[i]
        expected=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(a.mnemonic==b.mnemonic==mn and a.op_str==expected,
             f'{addr:#x}: real original typed PE target {target:#x} at 9E x86{i} differs')
        matching=[f for f in fields if b.address<=f['offset']<b.address+b.size]
        need(len(matching)==1
             and matching[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and matching[0]['addend']==0
             and matching[0]['local_symbol_offset'] is None
             and symbol in matching[0]['symbol'],
             f'{addr:#x}: original source C++ game/global PE target {target:#x} at {i} incorrect')
    orig_roles,gen_roles=h['f598'].normalized(native),h['f598'].normalized(cand)
    bad=[(i,n,s) for i,(n,s) in enumerate(zip(orig_roles,gen_roles)) if n!=s]
    need(not bad,f'{addr:#x}: native complete 0x9E original GPR/x87/CFG role mismatches {bad[:6]}')
    return {'whole_original_fighter':f'0x{addr:08X}',
            'enclosing_original_giant_CODE_still_NONEXACT':boss['size'],
            'separate_afterRET_native_switch_DATA':boss['postret_size'],
            'earlier_F636_F633_F631_F628_mode63_30_cases_and_afterRET_all_checked':True,
            'new_strict_native_action_0x9E_complete_case':meta,
            'original_native_true_PE_COFF_fields':len(fields),
            'new_source_backed_original_inner_CODE_bytes_UNCREDITED':meta['native_complete_original_inner_CODE_bytes'],
            'new_accepted_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original entire giant fighter, otherwise just 11 affected fighter TUs')
    opt=parser.parse_args()
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
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py',
    }
    h={name:load('f637_'+name,ROOT/path) for name,path in modules.items()}
    reader=load('f637_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f637_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    cohort=(*h['f628'].POSITIVE,0x004F7130,0x0045DD70,0x0058AF60)
    need(len(cohort)==len(set(cohort))==11,
         'genuine original 11 fighter boss 9E candidate boundaries changed')
    selected=[int(opt.boss,0)] if opt.boss else list(cohort)
    need(all(x in cohort for x in selected),'only actual original 11 fighter 9E case TUs are supported')
    original_source=SOURCE.read_text()
    need(original_source.count('case 0x9E:')==1
         and 'F637_STRICT_ABOVE' in original_source
         and 'POS48>g_ThresholdAt0065782C' in original_source
         and 'POS48>=g_ThresholdAt0065782C' in original_source
         and 'POS54=POS54-POS5C' in original_source
         and 'SetNativeActionAt40FAC0(0xA)' in original_source
         and 'SetNativeActionAt40FAC0(9)' in original_source,
         'native original strict-vs-nonstrict x87 motion source changed')
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
        native,meta=original_case(reader,pe,decoder,boss,by)
        cpp=OUT/f'Boss{addr:08X}-41-original-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-41-original-game-actions.obj'
        cpp.write_text(source_with_ground_boost(addr,boss,report,mapped,reader,pe,decoder,h,meta))
        build=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=190)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(build.stdout+build.stderr)
        need(build.returncode==0,
             f'{addr:#x}: pinned VC7.1 whole-fighter normal C++ compilation failed: {build.stderr[-480:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        receipt=verify_source(reader,pe,decoder,boss,report,mapped,code,refs,native,meta,h)
        receipts.append(receipt)
        print(f'F637 {addr:#010x}: native whole original 0x9E '
              f'{meta["native_original_full_x86_instructions"]} native x86 GPR/x87/CFG '
              f'roles strictly matching, {meta["native_complete_original_inner_CODE_bytes"]} '
              'original inner CODE bytes, 8 real original typed PE/COFF refs; '
              'previous 9B/9C/97/98/9A/96, earlier 0x91 and 30 game actions '
              'and afterRET switch DATA rechecked in same new whole fighter; '
              'giant still NONEXACT.',flush=True)
    path=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    path.write_text(json.dumps(receipts,indent=2)+'\n')
    print(f'F637 {len(receipts)} whole giant source TU compiles: '
          f'{sum(x["new_strict_native_action_0x9E_complete_case"]["native_original_full_x86_instructions"] for x in receipts)} '
          'real native x86 roles / '
          f'{sum(x["new_source_backed_original_inner_CODE_bytes_UNCREDITED"] for x in receipts)} '
          'original native inner CODE bytes / '
          f'{len(receipts)*8} genuine typed COFF fields. '
          'ZERO accepted whole authored exact functions, NO all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F637 actual original TH075 whole fighter native 0x9E verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
