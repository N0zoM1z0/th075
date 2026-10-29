#!/usr/bin/env python3
"""F645: real 60-x86 native motion restart B4/B5 in 11 giant fighters.

Rebuild ONLY selected affected whole VC7.1 fighter parent C++ source
TUs. Check each complete physically bounded original case, all GPR/
x87/CFG instruction roles and 8 physically typed PE-targeted COFF
fields; verify native B4->B5->C8 boundaries (B6..C7 share default,
not physical next CODE). Original two consecutive final JMPs require
actual natural C++ break *inside* and *after* the auxiliary branch.
Revalidate previous F642/F641/F639 and all earlier native source-backed
cases and the complete separately owned afterRET packed jump DATA.
Never accept case interiors as new whole authored function CODE.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f645-fighter-motion-restart-verified'
SOURCE=ROOT/'probes/FighterMotionRestartB4F645.inc'
ACTIONS=(0xB4,0xB5)
NEXT={0xB4:0xB5,0xB5:0xC8}
HEIGHT={0xB4:8.0,0xB5:-8.0}
# Independently checked original PE x86 ordinal55 auxiliary native
# action values. These are not globally 8/10: every actor may differ.
AUX={
  0x0045DD70:(7,5),
  0x00486550:(8,10),
  0x004AC040:(8,10),
  0x004D7E70:(7,7),
  0x004F7130:(8,10),
  0x005214B0:(8,10),
  0x00543210:(6,6),
  0x00564BE0:(7,7),
  0x0058AF60:(7,5),
  0x005AEEC0:(8,10),
  0x005D73C0:(7,6),
}
FIELDS={
   9:(0x00453E20,'call','ResetAt453E20'),
   19:(0x0040FC50,'call','ResetMotionAt40FC50'),
   22:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
   36:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
   42:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
   46:(0x00453E20,'call','ResetAt453E20'),
   49:(0x0040FA30,'call','GetNativeActionAt40FA30'),
   57:(0x0040FB40,'call','SetAuxActionAt40FB40'),
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,
         'actual original native PE source helper unavailable: '+str(path))
    module=importlib.util.module_from_spec(sp)
    sys.modules[name]=module
    sp.loader.exec_module(module)
    return module


def native_case(reader,pe,decoder,boss,by,action):
    addr=boss['address'];start=by[action];end=by[NEXT[action]]
    physical_next=min((x for x in set(by.values()) if x>start),default=None)
    size=275 if addr==0x00564BE0 else 215
    n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    need(addr<start<end<addr+boss['size']
         and end==physical_next
         and len(n)==60 and sum(x.size for x in n)==end-start==size,
         f'{addr:#x} action{action:#x}: real original full physical B4/B5 native 60 x86 size or boundary changed')
    height=struct.unpack('<f',struct.pack('<I',int(n[11].op_str.rsplit(', ',1)[-1],0)))[0]
    aux=int(n[55].op_str,0)
    need(len(AUX)==11 and aux==AUX[addr][ACTIONS.index(action)]
         and height==HEIGHT[action]
         and n[1].mnemonic=='movsx' and '+ 0x62]' in n[1].op_str
         and n[5].mnemonic=='movsx' and '+ 0x64]' in n[5].op_str
         and n[9].mnemonic=='call' and n[9].op_str=='0x453e20'
         and n[11].mnemonic=='mov' and n[11].op_str.endswith(
             ', 0x41000000' if action==0xB4 else ', 0xc1000000')
         and n[13].mnemonic=='mov' and n[13].op_str.endswith(', 0x41480000')
         and n[15].mnemonic=='mov' and n[15].op_str.endswith(', 0x3f400000')
         and n[17].mnemonic=='mov' and n[17].op_str.endswith(', 0')
         and n[19].mnemonic=='call' and n[19].op_str=='0x40fc50'
         and n[22].mnemonic=='fcomp' and n[22].op_str=='dword ptr [0x65782c]'
         and n[24].mnemonic=='test' and n[24].op_str=='ah, 0x41'
         and n[25].mnemonic=='jne'
         and n[29].mnemonic=='fsub' and '+ 0x5c]' in n[29].op_str
         and n[36].mnemonic=='fcomp' and n[36].op_str=='dword ptr [0x65782c]'
         and n[38].mnemonic=='test' and n[38].op_str=='ah, 0x41'
         and n[39].mnemonic=='jp'
         and n[40].mnemonic=='push' and n[40].op_str=='0xa'
         and n[42].mnemonic=='call' and n[42].op_str=='0x40fac0'
         and n[44].mnemonic=='mov' and n[44].op_str.endswith(', 0')
         and n[46].mnemonic=='call' and n[46].op_str=='0x453e20'
         and n[49].mnemonic=='call' and n[49].op_str=='0x40fa30'
         and n[55].mnemonic=='push' and n[57].mnemonic=='call'
         and n[57].op_str=='0x40fb40'
         and n[58].mnemonic==n[59].mnemonic=='jmp'
         and n[58].op_str==n[59].op_str,
         f'{addr:#x} action{action:#x}: actual original native x87 restart, split break/aux role semantics changed')
    for j,(target,mn,_) in FIELDS.items():
        instr=n[j]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(instr.mnemonic==mn and instr.op_str==want,
             f'{addr:#x} action{action:#x}: real original native typed target {target:#x} at ordinal{j} changed')
    return n,{'native_original_action':f'0x{action:02X}',
              'original_complete_case_start':f'0x{start:08X}',
              'physical_original_next_case':f'0x{end:08X}',
              'original_true_native_complete_CODE_bytes':size,
              'native_complete_x86_instruction_roles':60,
              'original_initial_float_height':height,
              'original_native_auxiliary_action':aux,
              'two_original_native_final_JMPs':True,
              'genuine_PE_COFF_targets':len(FIELDS),
              'enclosing_original_giant_whole_exact':False}


def source_with_restart(addr,boss,report,mapped,reader,pe,decoder,h,originals):
    by={x['action']:int(x['handler'],16) for x in mapped}
    earlier={a:h['f642'].native_case(reader,pe,decoder,boss,by,a)
             for a in h['f642'].ACTIONS}
    source=h['f642'].source_with_projectiles(addr,boss,report,mapped,
             reader,pe,decoder,h,earlier)
    for action in ACTIONS:
        _,meta=originals[action]
        defs={'F645_CASE':f'0x{action:X}',
              'F645_START_POS':repr(meta['original_initial_float_height'])+'f',
              'F645_AUX_ACTION':str(meta['original_native_auxiliary_action'])}
        mark=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(mark)==1,
             f'{addr:#x}: original full giant native restart case{action:X} source marker lost')
        replacement='\n'.join('#define '+k+' '+v for k,v in defs.items())
        replacement+='\n#include "FighterMotionRestartB4F645.inc"\n'
        replacement+='\n'.join('#undef '+k for k in defs)
        source=source.replace(mark,replacement)
    need(source.count('        case 0xC8: g_FighterProbeMarker = 201; break;')==1,
         f'{addr:#x}: actual next native action0xC8 marker lost; B6 is a default handler, not a real case boundary')
    return source


def verify_obj(reader,pe,decoder,boss,report,mapped,code,refs,originals,h):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: newly compiled whole fighter source final RET lost')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: actual original complete after-RET packed jump DATA extent changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    prior={a:h['f642'].native_case(reader,pe,decoder,boss,by,a)
           for a in h['f642'].ACTIONS}
    # The entire previous F642 sprite source, every older strictly
    # source-backed original case and entire separately owned jump
    # DATA is rechecked on THIS new C++ whole-giant OBJ.
    h['f642'].verify_fresh(reader,pe,decoder,boss,report,mapped,code,refs,
                             prior,h,extra_after_a8_x86=2*60)
    marker=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        x=next((i for i in ins if i.address<=f['offset']<i.address+i.size),None)
        if x is not None and x.mnemonic=='mov' and x.op_str.endswith(', 0xc9'):
            marker.append(x)
    need(len(marker)==1,
         f'{addr:#x}: genuine following native action0xC8 source marker not unique')
    end=ins.index(marker[0]);num=2*60
    need(end>=num,f'{addr:#x}: previous original 120 total x86 B4/B5 truncated')
    source=ins[end-num:end]
    need(source[-1].address+source[-1].size==marker[0].address,
         f'{addr:#x}: actual original B5 entire case must directly reach next real C8')
    results=[]
    for j,action in enumerate(ACTIONS):
        native,meta=originals[action]
        cand=source[j*60:(j+1)*60]
        need(len(cand)==len(native)==60 and cand[-1].mnemonic=='jmp'
             and cand[-2].mnemonic=='jmp',
             f'{addr:#x}: original complete native B4/B5 has 60 x86 including TWO final jumps')
        widths=[n.size-c.size for n,c in zip(native,cand)]
        if addr==0x00564BE0:
            need(widths.count(3)==20 and widths.count(0)==40
                 and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,w in enumerate(widths) if w==3),
                 f'{addr:#x}: true native 20 widened saved EBP−0x88 receiver MOVs per restart case differ')
        else:need(all(w==0 for w in widths),
                  f'{addr:#x}: original 60-x86 compact restart case instruction widths differ')
        low,high=cand[0].address,cand[-1].address+cand[-1].size
        need(high-low==215,
             f'{addr:#x} action{action:#x}: ordinary 60-instruction entire case source extent not 215 bytes')
        physical=[f for f in refs if low<=f['offset']<high]
        need(len(physical)==len(FIELDS)==8,
             f'{addr:#x} action{action:#x}: original 8 physical typed PE/COFF game calls/ground fields missing')
        for i,(target,mn,sym) in FIELDS.items():
            n,g=native[i],cand[i]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(n.mnemonic==g.mnemonic==mn and n.op_str==want,
                 f'{addr:#x} action{action:#x}: pinned original physical PE source typed target {target:#x} at {i} differs')
            match=[f for f in physical if g.address<=f['offset']<g.address+g.size]
            need(len(match)==1 and match[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and match[0]['addend']==0 and match[0]['local_symbol_offset'] is None
                 and sym in match[0]['symbol'],
                 f'{addr:#x} action{action:#x}: original PE/COFF typed game target {target:#x} at x86{i} wrong')
        actual,emitted=h['f598'].normalized(native),h['f598'].normalized(cand)
        bad=[(i,a,b) for i,(a,b) in enumerate(zip(actual,emitted)) if a!=b]
        need(not bad,
             f'{addr:#x} action{action:#x}: native original 60-x86 GPR/x87/CFG roles differ: {bad[:6]}')
        results.append({'original_action':meta['native_original_action'],
                        'original_whole_native_inner_CODE_bytes':meta['original_true_native_complete_CODE_bytes'],
                        'original_whole_native_x86_roles':60,
                        'original_real_PE_targeted_CO_FF_fields':8,
                        'native_original_two_final_JMPs':True,
                        'new_accepted_whole_game_CODE_bytes':0})
    return {'original_whole_giant':f'0x{addr:08X}',
            'original_entire_giant_CODE_still_NONEXACT':boss['size'],
            'actual_complete_separate_afterRET_jump_DATA':boss['postret_size'],
            'previous_F642_F641_F639_F637_mode63_30_cases_and_full_jump_DATA_rechecked':True,
            'two_native_full_original_restart_cases':results,
            'genuine_original_inner_CODE_bytes_strict_UNCREDITED':sum(x['original_whole_native_inner_CODE_bytes'] for x in results),
            'accepted_new_complete_whole_authored_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one actual original whole fighter C++ TU, default eleven affected giants')
    opt=p.parse_args()
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
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py',
    }
    h={name:load('f645_'+name,ROOT/path) for name,path in modules.items()}
    reader=load('f645_reader',ROOT/'scripts/compare-coff-function.py')
    acts=load('f645_acts',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    cohort=(*h['f628'].POSITIVE,0x004F7130,0x0045DD70,0x0058AF60)
    need(len(cohort)==len(set(cohort))==11,
         'pinned original native 11 fighter B4/B5 source cohort changed')
    selected=[int(opt.boss,0)] if opt.boss else list(cohort)
    need(all(a in cohort for a in selected),
         'selected original giant does not belong to actual native B4/B5 motion restart family')
    cpp=SOURCE.read_text()
    need(cpp.count('case F645_CASE:')==1
         and cpp.count('ResetAt453E20()')==2
         and cpp.count('break;')==3
         and 'if (POS48>g_ThresholdAt0065782C)' in cpp
         and 'if (POS48+POS54<=g_ThresholdAt0065782C)' in cpp
         and 'SetAuxActionAt40FB40(F645_AUX_ACTION);' in cpp,
         'actual original native doubled-break source restart C++ code changed')
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    receipts=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=acts.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        originals={action:native_case(reader,pe,decoder,boss,by,action)
                   for action in ACTIONS}
        cpp=OUT/f'Boss{addr:08X}-51-real-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-51-real-game-actions.obj'
        cpp.write_text(source_with_restart(addr,boss,report,mapped,reader,pe,decoder,h,originals))
        run=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                 cwd=ROOT,env=env,capture_output=True,text=True,timeout=190)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(run.stdout+run.stderr)
        need(run.returncode==0,
             f'{addr:#x}: whole original giant VC7.1 source failed: {run.stderr[-550:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        res=verify_obj(reader,pe,decoder,boss,report,mapped,code,refs,originals,h)
        receipts.append(res)
        print(f'F645 {addr:#010x}: original complete B4/B5 each 60/60 native '
              f'GPR/x87/CFG roles; {res["genuine_original_inner_CODE_bytes_strict_UNCREDITED"]} '
              'original inner CODE B, 16 physical typed COFF fields, '
              'previous F642 A7/A8/F641 counter-free landings and all older '
              'native game cases and packed DATA rechecked in SAME giant OBJ, '
              'enclosing original fighter still NONEXACT.',flush=True)
    output=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    output.write_text(json.dumps(receipts,indent=2)+'\n')
    print(f'F645 {len(receipts)} affected whole giant C++ builds, '
          f'{len(receipts)*2} true entire native INTERNAL cases, '
          f'{len(receipts)*120} x86 original roles / '
          f'{sum(r["genuine_original_inner_CODE_bytes_strict_UNCREDITED"] for r in receipts)} '
          f'UNcredited native inner CODE bytes / {len(receipts)*16} actual typed PE/COFF refs. '
          'ZERO accepted whole authored exact CODE, no full cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F645 pinned original TH075 native B4/B5 restart source proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
