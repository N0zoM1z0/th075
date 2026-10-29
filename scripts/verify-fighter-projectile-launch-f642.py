#!/usr/bin/env python3
"""F642: two full 97-x86 A7/A8 projectile cases in 11 giant fighters.

Ordinary pinned VC7.1 C++ whole-parent TUs with genuine member/float
expression order, 12 physically typed original PE-targeted COFF
fields per case and authentic 004AC040 4 near-stack scratch and
00564BE0 31 wide receiver/one near-branch original widths.
Reverify previous F641 A3/A4/A5, F639 final landings, F637 9E,
F636 pair, earlier game cases and complete separate afterRET DATA in
same new parent. Case fragments still never earn whole CODE credit.
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
SOURCE=ROOT/'probes/FighterProjectileLaunchF642.inc'
OUT=ROOT/'.analysis/f642-projectile-launch-verified'
ACTIONS=(0xA7,0xA8)
NEXT={0xA7:0xA8,0xA8:0xB4}
FIELDS={
  2:(0x0065747C,'fadd','g_AnimationDeltaAt0065747C'),
  7:(0x006583B4,'fcomp','g_AnimationMaximumAt006583B4'),
  23:(0x0046D000,'call','StartAnimationAt46D000'),
  26:(0x00453D60,'call','PrepareActionAt453D60'),
  35:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
  49:(0x00453C80,'call','SpawnAt453C80'),
  52:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
  58:(0x00658058,'fadd','g_JumpGroundCorrectionAt00658058'),
  63:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
  74:(0x006590B4,'fmul','g_ProjectileFallAt006590B4'),
  87:(0x0040FA30,'call','GetNativeActionAt40FA30'),
  95:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'original native PE helper missing: '+str(path))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def native_case(reader,pe,decoder,boss,by,action):
    addr=boss['address'];start,end=by[action],by[NEXT[action]]
    following=min((p for p in set(by.values()) if p>start),default=None)
    n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=(447 if addr==0x00564BE0 else 362 if addr==0x004AC040 else 350)
    counter=0xEFC if addr==0x005AEEC0 else 0xF00
    next_move=0 if action==0xA7 else 2
    need(addr<start<end<addr+boss['size'] and end==following
         and sum(i.size for i in n)==end-start==size
         and len(n)==97 and n[-1].mnemonic=='jmp',
         f'{addr:#x} action{action:#x}: original full native A7/A8 97-x86 case geometry changed')
    need(n[14].mnemonic=='movsx' and '+ 0x62]' in n[14].op_str
         and n[18].mnemonic=='movsx' and '+ 0x64]' in n[18].op_str
         and n[21].mnemonic=='push' and n[21].op_str=='0xfa'
         and n[24].mnemonic=='push' and n[24].op_str=='0x2c'
         and n[28].mnemonic=='mov' and f'+ 0x{counter:x}]' in n[28].op_str
         and n[28].op_str.endswith(', 0xb4')
         and n[29].mnemonic=='push' and n[29].op_str=='1'
         and n[29].op_str=='1',
         f'{addr:#x} action{action:#x}: actual game sprite one-shot original native stage start differs')
    need(n[34].mnemonic=='fld' and '+ 0x48]' in n[34].op_str
         and n[35].mnemonic=='fadd' and n[35].op_str=='dword ptr [0x657888]'
         and n[40].mnemonic=='imul' and n[40].op_str.endswith(', 0x1e')
         and n[41].mnemonic=='mov' and n[42].mnemonic=='fild'
         and n[47].mnemonic=='push' and n[47].op_str=='0x38'
         and n[47].op_str=='0x38',
         f'{addr:#x} action{action:#x}: native 30x direction, original FILD and sprite 0x38 differ')
    need(n[52].mnemonic=='fcomp' and n[52].op_str=='dword ptr [0x65782c]'
         and n[54].mnemonic=='test' and n[54].op_str=='ah, 5'
         and n[55].mnemonic=='jp'
         and n[63].mnemonic=='fcomp' and n[63].op_str=='dword ptr [0x65782c]'
         and n[65].mnemonic=='test' and n[65].op_str=='ah, 0x41'
         and n[66].mnemonic=='jne'
         and n[70].mnemonic=='movsx' and f'+ 0x{counter:x}]' in n[70].op_str
         and n[71].mnemonic=='neg' and n[72].mnemonic=='mov'
         and n[73].mnemonic=='fild' and n[74].mnemonic=='fmul'
         and n[74].op_str=='dword ptr [0x6590b4]'
         and n[78].mnemonic=='movsx' and f'+ 0x{counter:x}]' in n[78].op_str
         and n[83].mnemonic=='sub' and n[83].op_str.endswith(', 0xa')
         and n[85].mnemonic=='mov' and f'+ 0x{counter:x}]' in n[85].op_str
         and n[93].mnemonic=='push' and n[93].op_str==str(next_move),
         f'{addr:#x} action{action:#x}: original signed short cooldown, x87 bounce or next state differ')
    for i,(target,mn,sym) in FIELDS.items():
        x=n[i]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(x.mnemonic==mn and x.op_str==want,
             f'{addr:#x} action{action:#x}: real native PE field target {target:#x} at ordinal{i} differs')
    return n,{'native_original_action':f'0x{action:02X}',
              'true_original_case_start':f'0x{start:08X}',
              'true_original_next_handler':f'0x{end:08X}',
              'native_original_complete_inner_CODE_bytes':size,
              'original_complete_x86_instruction_roles':97,
              'native_original_cooldown_short_offset':counter,
              'native_original_sprite_kind':0x38,
              'native_original_side':1,
              'native_original_next_action':next_move,
              'native_actual_PE_COFF_target_fields':12,
              'whole_enclosing_giant_exact':False}


def source_with_projectiles(addr,boss,report,mapped,reader,pe,decoder,h,originals):
    by={r['action']:int(r['handler'],16) for r in mapped}
    prior={a:h['f641'].native_case(reader,pe,decoder,boss,by,a)
           for a in h['f641'].ACTIONS}
    src=h['f641'].natural_source(addr,boss,report,mapped,reader,pe,decoder,h,prior)
    decl='void PrepareActionAt453D60(int);'
    need(src.count(decl)==1,f'{addr:#x}: real fighter game method class source declaration missing')
    src=src.replace(decl,decl+' void StartAnimationAt46D000(int);'
                    ' void SpawnAt453C80(int,float,float,char,int);')
    glob='extern float g_ContactProjectionAt00657888;'
    need(src.count(glob)==1,f'{addr:#x}: actual source game float global declaration missing')
    src=src.replace(glob,glob+'\nextern float g_ProjectileFallAt006590B4;')
    for action in ACTIONS:
        _,info=originals[action]
        definitions={'F642_CASE':f'0x{action:X}',
                     'F642_COUNTER':f'0x{info["native_original_cooldown_short_offset"]:X}',
                     'F642_NEXT_ACTION':str(info['native_original_next_action'])}
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(marker)==1,f'{addr:#x}: original next action{action:#x} source marker missing')
        block='\n'.join('#define '+k+' '+v for k,v in definitions.items())
        block+='\n#include "FighterProjectileLaunchF642.inc"\n'
        block+='\n'.join('#undef '+k for k in definitions)
        src=src.replace(marker,block)
    need(src.count('        case 0xB4: g_FighterProbeMarker = 181; break;')==1,
         f'{addr:#x}: original following distinct native 0xB4 source marker missing')
    return src


def verify_fresh(reader,pe,decoder,boss,report,mapped,code,refs,originals,h):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: source whole giant final native RET missing')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original entire separate afterRET jump DATA length changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    old={a:h['f641'].native_case(reader,pe,decoder,boss,by,a)
         for a in h['f641'].ACTIONS}
    h['f641'].check_source(reader,pe,decoder,boss,report,mapped,code,refs,
                          old,h,extra_after_a5_x86=2*97)
    marker=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        x=next((i for i in ins if i.address<=f['offset']<i.address+i.size),None)
        if x is not None and x.mnemonic=='mov' and x.op_str.endswith(', 0xb5'):
            marker.append(x)
    need(len(marker)==1,f'{addr:#x}: real next native case0xB4 source marker not unique')
    end=ins.index(marker[0]);count=2*97
    need(end>=count,f'{addr:#x}: original entire consecutive A7/A8 cases truncated')
    cases=ins[end-count:end]
    need(cases[-1].address+cases[-1].size==marker[0].address,
         f'{addr:#x}: source case0xA8 must end at real next case0xB4 boundary')
    found=[]
    for pos,action in enumerate(ACTIONS):
        real,info=originals[action]
        src=cases[pos*97:(pos+1)*97]
        need(len(src)==len(real)==97 and src[-1].mnemonic=='jmp',
             f'{addr:#x}: true original A7/A8 entire native x86 source interval differs')
        widths=[x.size-y.size for x,y in zip(real,src)]
        if addr==0x00564BE0:
            # The native 31 widened +3 fields are NOT all receiver
            # loads: 27 are genuine EBP−0x88 saved-this MOVs and FOUR
            # are real signed-int scratch stores/FILD loads at native
            # ordinal41/42/72/73 (EBP−0xA8/AC or −0xB0/B4 per case).
            # Plus one original near 6-byte JNE at ordinal16 (+4).
            wide_scratch={41,42,72,73}
            need(widths.count(3)==31 and widths.count(4)==1
                 and widths.count(0)==65
                 and [i for i,v in enumerate(widths) if v==4]==[16]
                 and all(real[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,v in enumerate(widths) if v==3 and i not in wide_scratch)
                 and [i for i,v in enumerate(widths) if v==3 and i in wide_scratch]==[41,42,72,73]
                 and real[41].mnemonic==real[72].mnemonic=='mov'
                 and real[42].mnemonic==real[73].mnemonic=='fild'
                 and all('[ebp - 0x' in real[i].op_str for i in wide_scratch),
                 f'{addr:#x}: native 27 wide saved-this MOV, 4 true wide FILD scratch fields + one near JNE differ')
        elif addr==0x004AC040:
            need([i for i,v in enumerate(widths) if v==3]==[41,42,72,73]
                 and all(v in (0,3) for v in widths)
                 and real[42].mnemonic==real[73].mnemonic=='fild',
                 f'{addr:#x}: original actual four widened signed integer-to-float scratch stack operands differ')
        else:need(all(v==0 for v in widths),
                  f'{addr:#x}: original compact 350-byte A7/A8 native x86 widths differ')
        low,high=src[0].address,src[-1].address+src[-1].size
        need(high-low==350,
             f'{addr:#x}: real natural x86 97-instruction case source must be 350 bytes')
        physical=[f for f in refs if low<=f['offset']<high]
        need(len(physical)==len(FIELDS)==12,
             f'{addr:#x}: native original A7/A8 12 physical game/float COFF fields missing')
        for ordinal,(target,mn,sym) in FIELDS.items():
            a,b=real[ordinal],src[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
                 f'{addr:#x}: original A7/A8 x86{ordinal} true PE target {target:#x} differs')
            refs_here=[f for f in physical if b.address<=f['offset']<b.address+b.size]
            need(len(refs_here)==1
                 and refs_here[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and refs_here[0]['addend']==0 and refs_here[0]['local_symbol_offset'] is None
                 and sym in refs_here[0]['symbol'],
                 f'{addr:#x}: original A7/A8 x86{ordinal} real C++ COFF target {target:#x} wrong')
        a,b=h['f598'].normalized(real),h['f598'].normalized(src)
        differences=[(i,n,s) for i,(n,s) in enumerate(zip(a,b)) if n!=s]
        need(not differences,
             f'{addr:#x}: original entire A7/A8 native GPR/x87/CFG roles differ: {differences[:5]}')
        found.append({'actual_original_native_action':info['native_original_action'],
                      'original_complete_inner_CODE_bytes':info['native_original_complete_inner_CODE_bytes'],
                      'original_complete_x86_roles':97,
                      'true_physical_native_PE_COFF_fields':12,
                      'new_accepted_whole_game_function_bytes':0})
    return {'real_original_giant':f'0x{addr:08X}',
            'whole_native_giant_CODE_still_NONEXACT':boss['size'],
            'separate_real_original_afterRET_jump_DATA':boss['postret_size'],
            'prior_F641_A3_A4_A5_F639_F637_F636_mode63_30_cases_rechecked':True,
            'two_native_complete_original_projectile_cases':found,
            'new_strict_original_internal_CODE_bytes_UNCREDITED':sum(x['original_complete_inner_CODE_bytes'] for x in found),
            'accepted_new_exact_whole_authored_functions':0}


def main():
    cli=argparse.ArgumentParser(description=__doc__)
    cli.add_argument('--boss',help='one original fighter whole source TU; omit for 11 affected TUs')
    opt=cli.parse_args()
    paths={
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
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    h={name:load('f642_'+name,ROOT/path) for name,path in paths.items()}
    reader=load('f642_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f642_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    cohort=(*h['f628'].POSITIVE,0x004F7130,0x0045DD70,0x0058AF60)
    need(len(set(cohort))==len(cohort)==11,'genuine original eleven A7/A8 giant fighter cohort changed')
    selected=[int(opt.boss,0)] if opt.boss else list(cohort)
    need(all(x in cohort for x in selected),'selected fighter is not original A7/A8 registered cohort')
    code=SOURCE.read_text()
    need(code.count('case F642_CASE:')==1
         and 'F32(0x48)+g_ContactProjectionAt00657888' in code
         and 'SpawnAt453C80' in code
         and 'I16(F642_COUNTER)=0xB4' in code
         and 'F32(0x490)=(-I16(F642_COUNTER))*g_ProjectileFallAt006590B4' in code,
         'native original actual float 30x sprite source expression/trajectory changed')
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    receipts=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        orig={a:native_case(reader,pe,decoder,boss,by,a) for a in ACTIONS}
        cpp=OUT/f'Boss{addr:08X}-49-real-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-49-real-game-actions.obj'
        cpp.write_text(source_with_projectiles(addr,boss,report,mapped,reader,pe,decoder,h,orig))
        proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                 cwd=ROOT,env=env,capture_output=True,text=True,timeout=190)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(proc.stdout+proc.stderr)
        need(proc.returncode==0,
             f'{addr:#x}: actual original normal VC7.1 whole giant C++ source build failed: {proc.stderr[-550:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        verified=verify_fresh(reader,pe,decoder,boss,report,mapped,code,refs,orig,h)
        receipts.append(verified)
        print(f'F642 {addr:#010x}: real original A7/A8 two complete 97/97 native '
              f'GPR/x87/CFG roles; {verified["new_strict_original_internal_CODE_bytes_UNCREDITED"]} '
              'real original inner CODE B, 24 actual typed PE/COFF fields; '
              'prior A3/A4/A5/9F/A0/A1/9E and all earlier native game cases '
              'and entire afterRET DATA rechecked in same giant C++ OBJ, '
              'whole original fighter NONEXACT.',flush=True)
    summary=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    summary.write_text(json.dumps(receipts,indent=2)+'\n')
    print(f'F642 {len(receipts)} newly compiled whole giant C++ source TUs: '
          f'{len(receipts)*2} genuinely original complete internal cases, '
          f'{len(receipts)*194} original native x86 roles / '
          f'{sum(x["new_strict_original_internal_CODE_bytes_UNCREDITED"] for x in receipts)} '
          f'UNcredited original inner CODE bytes / {len(receipts)*24} actual typed COFF; '
          'zero accepted original whole-function authored exact CODE and no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F642 original Japanese native A7/A8 sprite launch source verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
