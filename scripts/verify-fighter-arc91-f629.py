#!/usr/bin/env python3
"""F629: full original action0x91 78-x86 arc landing in eight giants.

Compile ONLY selected whole fighter C++ source TUs; verify actual
native PE complete case0x91->0x96 x86 GPR/x87/CFG, typed physical
COFF fields, real 25 widened EBP-0x88 receiver MOVs, and independently
revalidate F628 previous three cases, previous native mode63 in same
whole TU, all earlier 30 case grammars and full afterRET switch DATA.
One original GPR-cycle negative (004F7130) is explicitly retained.
No case fragment or unfinished giant is accepted as an exact function.
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
SOURCE=ROOT/'probes/FighterArcTrajectory91F629.inc'
OUT=ROOT/'.analysis/f629-fighter-arc-source'
NEGATIVE=0x004F7130
FIELDS={
    22:(0x00657480,'fcomp','g_StopThresholdAt00657480'),
    28:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    40:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
    46:(0x00657888,'fmul','g_ContactProjectionAt00657888'),
    47:(0x006406AC,'call','__ftol2'),
    52:(0x00657888,'fmul','g_ContactProjectionAt00657888'),
    53:(0x006406AC,'call','__ftol2'),
    57:(0x00453E20,'call','ResetAt453E20'),
    62:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    65:(0x00453E60,'call','InitTrajectoryAt453E60'),
    68:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    76:(0x0040FB40,'call','SetAuxActionAt40FB40'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'native original source helper missing '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def real_original(reader,pe,decoder,boss,by):
    addr=boss['address'];start=by[0x91];end=by[0x96]
    actual_next=min((x for x in set(by.values()) if x>start),default=None)
    n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=363 if addr==0x00564BE0 else 288
    need(addr<=start<end<addr+boss['size'] and end==actual_next
         and len(n)==78 and end-start==size and sum(x.size for x in n)==size
         and n[-1].mnemonic=='jmp',
         f'{addr:#x}: real native original whole 0x91->0x96 physical boundary or x86 count differs')
    stage=int(n[18].op_str.rsplit(', ',1)[-1],0)
    early=int(n[26].op_str,0)
    late=int(n[74].op_str,0)
    counter=0xEFC if addr==0x005AEEC0 else 0xF00
    need(n[9].mnemonic=='mov' and n[9].op_str.endswith(', 0xc1200000')
         and n[11].mnemonic=='mov' and n[11].op_str.endswith(', 0x41600000')
         and n[13].mnemonic=='mov' and n[13].op_str.endswith(', 0x3f000000')
         and n[15].mnemonic=='mov' and n[15].op_str.endswith(', 0')
         and n[18].mnemonic=='cmp' and stage in (1,2,3)
         and n[24].mnemonic=='test' and n[24].op_str=='ah, 5'
         and n[25].mnemonic=='jp'
         and n[33].mnemonic=='fsub' and '+ 0x5c]' in n[33].op_str
         and n[39].mnemonic=='fadd' and '+ 0x48]' in n[39].op_str
         and n[42].mnemonic=='test' and n[42].op_str=='ah, 0x41'
         and n[43].mnemonic=='jp'
         and n[49].mnemonic=='mov' and f'+ 0x{counter:x}]' in n[49].op_str
         and n[55].mnemonic=='mov' and f'+ 0x{counter+2:x}]' in n[55].op_str
         and n[60].mnemonic=='push' and n[60].op_str=='0x61'
         and n[63].mnemonic=='push' and n[63].op_str=='0x40000000'
         and n[73].mnemonic=='jne' and n[74].mnemonic=='push'
         and (stage,early,late) in ((1,2,5),(1,2,6),(1,2,7),(2,3,6),
              (2,3,7),(2,3,8),(3,4,7)),
         f'{addr:#x}: original 0x91 real arc motion, float compare, stage/aux semantics differ')
    for i,(target,mn,sym) in FIELDS.items():
        x=n[i]
        need(x.mnemonic==mn and x.op_str==(
             f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'),
             f'{addr:#x}: actual original native PE typed target {target:#x} at x86 ordinal {i} differs')
    return n,{'actual_original_handler':f'0x{start:08X}',
              'actual_original_next_handler':f'0x{end:08X}',
              'original_complete_internal_CODE_bytes':size,
              'native_original_complete_x86':78,
              'native_stage':stage,'native_early_aux':early,'native_late_aux':late,
              'native_trajectory_short_owner':counter,
              'native_physical_PE_COFF_fields':len(FIELDS),
              'enclosing_giant_exact':False}


def source_with_action(addr,boss,report,mapped,reader,pe,decoder,h,native,info):
    source=h['f628'].source_with_landing(addr,boss,report,mapped,reader,pe,decoder,h,native)
    marker='        case 0x91: g_FighterProbeMarker = 146; break;'
    need(source.count(marker)==1,f'{addr:#x}: original next 0x91 action marker lost')
    defs={'F629_STAGE':str(info['native_stage']),
          'F629_EARLY':str(info['native_early_aux']),
          'F629_LATE':str(info['native_late_aux']),
          'F629_COUNTER':f'0x{info["native_trajectory_short_owner"]:X}'}
    insert='\n'.join('#define '+k+' '+v for k,v in defs.items())
    insert+='\n#include "FighterArcTrajectory91F629.inc"\n'
    insert+='\n'.join('#undef '+k for k in defs)
    result=source.replace(marker,insert)
    need(result.count('        case 0x96: g_FighterProbeMarker = 151; break;')==1,
         f'{addr:#x}: actual original following 0x96 marker unavailable')
    return result


def verify_case(reader,pe,decoder,boss,report,mapped,code,refs,n,info,helpers,negative,extra_after_0x91=0):
    addr=boss['address'];h=helpers
    by={x['action']:int(x['handler'],16) for x in mapped}
    earlier={action:h['f628'].native_case(reader,pe,decoder,boss,by,action)
             for action in h['f628'].ACTIONS}
    # Verify the actual earlier F628 THREE original x87 cases, real
    # strict mode63 predecessor, 30 earlier real game actions and
    # entire afterRET physical jump DATA in this NEW extended OBJ.
    need(extra_after_0x91 in (0,73,75,292,300,438,450,504,518,723,737,936,950,1130,1144,1250,1264),
         f'{addr:#x}: only actual original 73/75-x86 case96 may extend 0x91')
    h['f628'].verify_obj(reader,pe,decoder,boss,report,mapped,code,refs,
         earlier,helpers,negative,extra_followup_x86=78+extra_after_0x91)
    inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',f'{addr:#x}: whole fighter source RET absent')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original real separately owned afterRET DATA length differs')
    refs96=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:continue
        target=next((x for x in inst if x.address<=field['offset']<x.address+x.size),None)
        wanted=(0x97 if extra_after_0x91==0 else
                0x98 if extra_after_0x91 in (73,75) else
                0x9C if extra_after_0x91 in (292,300) else
                0x9F if extra_after_0x91 in (438,450) else
                0xA0 if extra_after_0x91 in (504,518) else
                0xA4 if extra_after_0x91 in (723,737) else
                0xA8 if extra_after_0x91 in (936,950) else
                0xB5 if extra_after_0x91 in (1130,1144) else 0xC9)
        if target is not None and target.mnemonic=='mov' and target.op_str.endswith(f', 0x{wanted:x}'):
            refs96.append(target)
    need(len(refs96)==1,f'{addr:#x}: original next case0x96 marker source not uniquely typed')
    idx=inst.index(refs96[0]);need(idx>=78+extra_after_0x91,
                                    'original 0x91 native entire source case truncated')
    gen=inst[idx-78-extra_after_0x91:idx-extra_after_0x91]
    actual_end=(inst[idx-extra_after_0x91].address if extra_after_0x91 else refs96[0].address)
    need(len(gen)==len(n)==78 and gen[-1].address+gen[-1].size==actual_end
         and gen[-1].mnemonic=='jmp',
         f'{addr:#x}: actual native source 0x91 does not join next source case0x96')
    width=[x.size-y.size for x,y in zip(n,gen)]
    if addr==0x00564BE0:
        need(width.count(3)==25 and width.count(0)==53
             and all(n[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i,diff in enumerate(width) if diff==3),
             f'{addr:#x}: original case91 25 real saved-this EBP-0x88 MOV widenings missing')
    else:need(all(w==0 for w in width),f'{addr:#x}: original compact case91 source x86 width mismatch')
    low,high=gen[0].address,gen[-1].address+gen[-1].size
    need(high-low==288,f'{addr:#x}: original 91 normal C++ 288-byte full case grammar changed')
    original_fields=[x for x in refs if low<=x['offset']<high]
    need(len(original_fields)==len(FIELDS)==12,
         f'{addr:#x}: twelve physical original game/CRT/float PE/COFF fields missing')
    for i,(target,mn,sym) in FIELDS.items():
        a,b=n[i],gen[i]
        need(a.mnemonic==b.mnemonic==mn,
             f'{addr:#x}: original typed PE game/CRT x86 instruction ordinal {i} changed')
        actual=[x for x in original_fields if b.address<=x['offset']<b.address+b.size]
        need(len(actual)==1 and actual[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and actual[0]['addend']==0 and actual[0]['local_symbol_offset'] is None
             and sym in actual[0]['symbol'],
             f'{addr:#x}: original game target {target:#x} source COFF x86{i} differs: {actual}')
    origshape,genshape=h['f598'].normalized(n),h['f598'].normalized(gen)
    diffs=[(i,a,b) for i,(a,b) in enumerate(zip(origshape,genshape)) if a!=b]
    need(len(diffs)==(35 if negative else 0),
         f'{addr:#x}: original case0x91 native GPR/x87/CFG role mismatches {len(diffs)} vs expected {35 if negative else 0}: {diffs[:6]}')
    return {'original_enclosing_giant':f'0x{addr:08X}',
            'entire_original_giant_CODE_still_NONEXACT':boss['size'],
            'original_separately_owned_afterRET_DATA':boss['postret_size'],
            'previous_8C_8F_90_and_original_mode63_30_cases_strict_in_new_OBJ':not negative,
            'native_original_0x91_full_case':info,
            'original_typed_native_PE_COFF_refs':12,
            'original_GPR_x87_CFG_role_differences':len(diffs),
            'new_original_inner_CODE_bytes_strict_uncredited':0 if negative else info['original_complete_internal_CODE_bytes'],
            'new_accepted_whole_exact_authored_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one strict original 78-x86 arc fighter; default eight F628 strict actors')
    p.add_argument('--negative-actor',action='store_true',
                   help='whole original 004F7130: 51 role errors in earlier 8C/8F/90, 35 in real 0x91')
    opt=p.parse_args()
    need(not(opt.boss and opt.negative_actor),'choose either strict or the GPR-phase negative')
    helperspec={
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
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    helpers={name:load('f629_'+name,ROOT/spec) for name,spec in helperspec.items()}
    reader=load('f629_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f629_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    selected=([NEGATIVE] if opt.negative_actor else
         ([int(opt.boss,0)] if opt.boss else list(helpers['f628'].POSITIVE)))
    need(all(addr in ((NEGATIVE,) if opt.negative_actor else helpers['f628'].POSITIVE)
             for addr in selected),
         'other fighter originals have an additional real projectile 105-x86 action0x91 source')
    text=SOURCE.read_text()
    need(text.count('case 0x91:')==1 and 'POS=-10.0f' in text
         and 'POS54=14.0f' in text and 'POS5C=0.5f' in text
         and 'POS54<g_StopThresholdAt00657480' in text
         and text.count('static_cast<short>')==2,
         'native real trajectory phase/threshold two original CRT conversions changed')
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    records=[]
    for addr in selected:
        boss=bosses[addr];rep,rows=actions.report_boss(reader,pe,dec,boss)
        by={x['action']:int(x['handler'],16) for x in rows}
        original,info=real_original(reader,pe,dec,boss,by)
        before={action:helpers['f628'].native_case(reader,pe,dec,boss,by,action)
                for action in helpers['f628'].ACTIONS}
        cpp=OUT/f'Boss{addr:08X}-34-real-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-34-real-game-actions.obj'
        cpp.write_text(source_with_action(addr,boss,rep,rows,reader,pe,dec,helpers,before,info))
        compile=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=190)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(compile.stdout+compile.stderr)
        need(compile.returncode==0,
             f'{addr:#x}: pinned VC7.1 whole original-shaped giant source fails: {compile.stderr[-500:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        found=verify_case(reader,pe,dec,boss,rep,rows,code,refs,original,info,helpers,opt.negative_actor)
        records.append(found)
        print(f'F629 {addr:#010x}: original complete 0x91 native 78/78 x86 roles, '
              f'{info["original_complete_internal_CODE_bytes"]} original inner CODE bytes, '
              '12/12 real PE/COFF CRT/game/float targets, '
              f'{found["original_GPR_x87_CFG_role_differences"]} GPR role differences; '
              'previous 3 landing cases, native 0x63, earlier 30 cases and '
              'original afterRET table rechecked; giant NONEXACT',flush=True)
    out=OUT/('negative-summary.json' if opt.negative_actor else
             ('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json'))
    out.write_text(json.dumps(records,indent=2)+'\n')
    print(f'F629 {len(records)} original whole source TUs; '
          f'{sum(r["new_original_inner_CODE_bytes_strict_uncredited"] for r in records)} '
          'source-backed internal original CODE bytes, zero whole-function accepted authored '
          'bytes and no full all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F629 real Japanese TH075 0x91 trajectory role verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
