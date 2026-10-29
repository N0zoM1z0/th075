#!/usr/bin/env python3
"""F641: authentic 71-x86 native A3/A4/A5 in 11 giant fighter parents.

Compile only selected whole pinned VC7.1 fighter C++ source TUs.
Original 0xA3/A4/A5 omit the trajectory short reset unlike preceding
73/75-x86 landing cases. Verify 9 genuine PE-targeted zero-addend
COFF fields in each real whole case, GPR/x87/CFG/width, 21 native
wide saved EBP-0x88 loads, state2, and all earlier F639/F637/F636/
F633/F631 game cases/complete original afterRET switch DATA in the
SAME fresh whole parent source object. Giant remains NONEXACT.
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
SOURCE=ROOT/'probes/FighterLandingNoCounterF641.inc'
OUT=ROOT/'.analysis/f641-fighter-no-counter-landings-source'
ACTIONS=(0xA3,0xA4,0xA5)
NEXT={0xA3:0xA4,0xA4:0xA5,0xA5:0xA7}
HEIGHTS={0xA3:-9.0,0xA4:-10.0,0xA5:-13.0}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         'missing original native PE source helper '+str(path))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def native_case(reader,pe,decoder,boss,by,action):
    addr=boss['address'];start,end=by[action],by[NEXT[action]]
    next_physical=min((pc for pc in set(by.values()) if pc>start),default=None)
    orig=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=327 if addr==0x00564BE0 else 264
    need(addr<start<end<addr+boss['size'] and end==next_physical
         and len(orig)==71 and sum(x.size for x in orig)==end-start==size
         and orig[-1].mnemonic=='jmp',
         f'{addr:#x} case{action:#x}: real original entire 71-x86 physical case extent differs')
    pos=[(i,x) for i,x in enumerate(orig) if x.mnemonic=='mov' and re.fullmatch(
         r'dword ptr \[[a-z]+ \+ 0x50\], 0xc[0-9a-f]+',x.op_str)]
    need(len(pos)==1 and pos[0][0]==22,
         f'{addr:#x} case{action:#x}: original native 21/22 float initial member register role differs')
    height=struct.unpack('<f',struct.pack('<I',int(pos[0][1].op_str.rsplit(', ',1)[-1],0)))[0]
    need(height==HEIGHTS[action]
         and orig[0].mnemonic=='mov' and orig[1].mnemonic=='fld'
         and orig[2].mnemonic=='fadd' and orig[2].op_str=='dword ptr [0x65747c]'
         and orig[7].mnemonic=='fcomp' and orig[7].op_str=='dword ptr [0x6583b4]'
         and orig[9].mnemonic=='test' and orig[9].op_str=='ah, 0x41'
         and orig[10].mnemonic=='jne'
         and orig[14].mnemonic=='movsx' and '+ 0x62]' in orig[14].op_str
         and orig[18].mnemonic=='movsx' and '+ 0x64]' in orig[18].op_str
         and orig[24].mnemonic=='mov' and orig[24].op_str.endswith(', 0')
         and orig[26].mnemonic=='mov' and orig[26].op_str.endswith(', 0')
         and orig[29].mnemonic=='fcomp' and orig[31].op_str=='ah, 5'
         and orig[32].mnemonic=='jp'
         and orig[35].mnemonic=='fadd'
         and orig[40].mnemonic=='fcomp' and orig[42].op_str=='ah, 0x41'
         and orig[43].mnemonic=='jne'
         and orig[47].mnemonic=='call' and orig[47].op_str=='0x454ee0'
         and orig[52].mnemonic=='movsx' and '+ 0x3be]' in orig[52].op_str
         and orig[57].mnemonic=='fmul' and orig[57].op_str=='qword ptr [0x6583e8]'
         and orig[59].mnemonic=='fstp' and '+ 0x490]' in orig[59].op_str
         and orig[61].mnemonic=='call' and orig[61].op_str=='0x40fa30'
         and orig[67].mnemonic=='push' and orig[67].op_str=='2'
         and orig[69].mnemonic=='call' and orig[69].op_str=='0x40fac0',
         f'{addr:#x} action{action:#x}: native 71-x86 initial/count-free true timer, x87 and next-action2 differ')
    need(not any(x.mnemonic=='mov' and ('+ 0xf00]' in x.op_str or
             '+ 0xefc]' in x.op_str or '+ 0xf0a]' in x.op_str) for x in orig),
         f'{addr:#x} action{action:#x}: native still has short counter reset, not 71-x86 family')
    return orig,{'original_case':f'0x{action:02X}',
                 'native_original_complete_start':f'0x{start:08X}',
                 'native_original_complete_end':f'0x{end:08X}',
                 'native_original_complete_inner_CODE_bytes':size,
                 'original_complete_native_x86_roles':71,
                 'original_native_height':height,
                 'original_native_next_action':2,
                 'original_short_counter_reset':False,
                 'real_PE_COFF_fields':9,
                 'enclosing_original_giant_whole_exact':False}


def natural_source(addr,boss,report,mapped,reader,pe,decoder,h,originals):
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev={a:h['f633'].original_case(reader,pe,decoder,boss,by,a) for a in h['f639'].ACTIONS}
    src=h['f639'].actual_source(addr,boss,report,mapped,reader,pe,decoder,h,prev)
    for action in ACTIONS:
        _,info=originals[action]
        defs={'F641_CASE':f'0x{action:X}',
              'F641_START_HEIGHT':repr(info['original_native_height'])+'f',
              'F641_NEXT_ACTION':'2'}
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(marker)==1,
             f'{addr:#x}: genuine following original case{action:X} source placeholder absent')
        block='\n'.join('#define '+k+' '+v for k,v in defs.items())
        block+='\n#include "FighterLandingNoCounterF641.inc"\n'
        block+='\n'.join('#undef '+k for k in defs)
        src=src.replace(marker,block)
    need(src.count('        case 0xA7: g_FighterProbeMarker = 168; break;')==1,
         f'{addr:#x}: original next distinct native complex action0xA7 marker missing')
    return src


def check_source(reader,pe,decoder,boss,report,mapped,code,refs,originals,h,extra_after_a5_x86=0):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: actual whole giant source has no RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: separately owned original entire afterRET jump DATA changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    old={a:h['f633'].original_case(reader,pe,decoder,boss,by,a)
         for a in h['f639'].ACTIONS}
    need(extra_after_a5_x86 in (0,2*97),
         f'{addr:#x}: only two real complete 97-x86 A7/A8 cases may follow A5')
    h['f639'].check_fresh_whole(reader,pe,decoder,boss,report,mapped,code,refs,
                                 old,h,extra_after_last_x86=3*71+extra_after_a5_x86)
    wanted=0xA8 if extra_after_a5_x86==0 else 0xB5
    marks=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        instr=next((x for x in ins if x.address<=f['offset']<x.address+x.size),None)
        if instr is not None and instr.mnemonic=='mov' and instr.op_str.endswith(f', 0x{wanted:x}'):
            marks.append(instr)
    need(len(marks)==1,
         f'{addr:#x}: actual original next case0xA7 marker must be uniquely source-typed')
    end=ins.index(marks[0]);num=3*71
    need(end>=num+extra_after_a5_x86,
         f'{addr:#x}: three original 71-x86 source cases truncated by later source')
    source=ins[end-num-extra_after_a5_x86:end-extra_after_a5_x86]
    true_next=(ins[end-extra_after_a5_x86].address if extra_after_a5_x86
               else marks[0].address)
    need(source[-1].address+source[-1].size==true_next,
         f'{addr:#x}: genuine original final A5 physical x86 source end not adjacent A7')
    receipts=[]
    for ordinal,action in enumerate(ACTIONS):
        orig,meta=originals[action]
        produced=source[ordinal*71:(ordinal+1)*71]
        need(len(produced)==len(orig)==71 and produced[-1].mnemonic=='jmp',
             f'{addr:#x}: actual native whole case{action:#x} x86 cut short')
        widths=[x.size-y.size for x,y in zip(orig,produced)]
        if addr==0x00564BE0:
            need(widths.count(3)==21 and widths.count(0)==50
                 and all(orig[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,w in enumerate(widths) if w==3),
                 f'{addr:#x}: real native A3/A4/A5 original 21 EBP−0x88 receiver MOVs differ')
        else:need(all(w==0 for w in widths),
                  f'{addr:#x} action{action:#x}: original x86 compact opcode widths changed')
        low,high=produced[0].address,produced[-1].address+produced[-1].size
        need(high-low==264,
             f'{addr:#x} action{action:#x}: complete normal source not 264 original x86 bytes')
        fields=[f for f in refs if low<=f['offset']<high]
        need(len(fields)==9,f'{addr:#x} action{action:#x}: original 9 physically typed PE/COFF fields absent')
        for j,(target,mn,symbol) in h['f631'].FIELDS.items():
            i=j-2 if j>=31 else j
            a,b=orig[i],produced[i]
            expected=f'0x{target:x}' if mn=='call' else (
                f'qword ptr [0x{target:x}]' if mn=='fmul' else f'dword ptr [0x{target:x}]')
            need(a.mnemonic==b.mnemonic==mn and a.op_str==expected,
                 f'{addr:#x} action{action:#x}: actual original PE global/game x86{i} {target:#x} differs')
            matching=[f for f in fields if b.address<=f['offset']<b.address+b.size]
            need(len(matching)==1
                 and matching[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and matching[0]['addend']==0 and matching[0]['local_symbol_offset'] is None
                 and symbol in matching[0]['symbol'],
                 f'{addr:#x} action{action:#x}: actual original typed PE/COFF x86 ordinal{i} incorrect')
        lhs,rhs=h['f598'].normalized(orig),h['f598'].normalized(produced)
        diffs=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b]
        need(not diffs,
             f'{addr:#x} action{action:#x}: actual original native GPR/x87/CFG role errors {diffs[:5]}')
        receipts.append({'native_original_action':meta['original_case'],
                         'entire_original_native_case_CODE_bytes':meta['native_original_complete_inner_CODE_bytes'],
                         'original_complete_x86_GPR_x87_CFG_roles':71,
                         'true_native_PE_COFF_fields':9,
                         'accepted_authored_whole_function_bytes':0})
    return {'original_enclosing_giant':f'0x{addr:08X}',
            'enclosing_native_whole_CODE_still_NONEXACT':boss['size'],
            'separately_owned_afterRET_jump_DATA_original_bytes':boss['postret_size'],
            'preceding_F639_F637_F636_F633_F631_mode63_30_actions_reverified':True,
            'three_genuine_original_new_case_bodies':receipts,
            'native_original_inner_CODE_bytes_strict_UNCREDITED':sum(x['entire_original_native_case_CODE_bytes'] for x in receipts),
            'new_accepted_whole_authored_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one original giant source TU; omit for 11 affected parents')
    opt=p.parse_args()
    from pathlib import Path
    specs={
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
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    h={name:load('f641_'+name,ROOT/path) for name,path in specs.items()}
    reader=load('f641_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f641_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    cohort=(*h['f628'].POSITIVE,0x004F7130,0x0045DD70,0x0058AF60)
    need(len(cohort)==len(set(cohort))==11,
         'genuine original native eleven giant 0xA3/A4/A5 source owner cohort changed')
    selected=[int(opt.boss,0)] if opt.boss else list(cohort)
    need(all(a in cohort for a in selected),'original selected actor outside physical A3/4/5 71-x86 native cohort')
    source=SOURCE.read_text()
    need(source.count('case F641_CASE:')==1
         and 'F641_START_HEIGHT' in source and 'F641_NEXT_ACTION' in source
         and 'F633_COUNTER' not in source and '0xF0A' not in source,
         'original A3/A4/A5 genuinely counterless source grammar changed')
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=bosses[addr];report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        originals={a:native_case(reader,pe,decoder,boss,by,a) for a in ACTIONS}
        source=natural_source(addr,boss,report,mapped,reader,pe,decoder,h,originals)
        cpp=OUT/f'Boss{addr:08X}-47-original-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-47-original-game-actions.obj'
        cpp.write_text(source)
        comp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                 cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(comp.stdout+comp.stderr)
        need(comp.returncode==0,
             f'{addr:#x}: pinned original VC7.1 entire giant source build failed: {comp.stderr[-450:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        receipt=check_source(reader,pe,decoder,boss,report,mapped,code,refs,originals,h)
        rows.append(receipt)
        print(f'F641 {addr:#010x}: native A3/A4/A5 each 71/71 real x86 '
              f'GPR/x87/CFG roles; {receipt["native_original_inner_CODE_bytes_strict_UNCREDITED"]} '
              'genuine inner CODE bytes, 27/27 physical typed PE/COFF refs; '
              'all preceding real F639 9F/A0/A1, F637 9E and older native cases '
              'and entire afterRET table preserved in same new giant, NONEXACT.',flush=True)
    path=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    path.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F641 {len(rows)} freshly rebuilt entire fighter source parents; '
          f'{len(rows)*3} strict native original CASE INTERIORS, '
          f'{len(rows)*213} original x86 roles, '
          f'{sum(r["native_original_inner_CODE_bytes_strict_UNCREDITED"] for r in rows)} '
          f'uncredited inner CODE bytes, {len(rows)*27} real PE/COFF; '
          'ZERO new whole original authored exact functions, no full all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F641 original Japanese native A3/A4/A5 no-counter source proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
