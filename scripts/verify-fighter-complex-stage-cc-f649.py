#!/usr/bin/env python3
"""F649: two original complete CC grammar matches, true GPR-role NEGATIVES.

Freshly compile ONLY two entire giant VC7.1 C++ source TUs, check
original complete 128/126 x86 and physically 435/542 native CODE B,
all 11 actual typed PE/COFF fields at their original ordinal, saved
wide EBP-0x88 receiver widths and complete owned afterRET DATA.
Source emits 80/78 genuine non-COFF register-role mismatches. NEVER
promote these giant case interiors or the whole parent to exact CODE.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/FighterComplexStageCCF649.inc'
OUT=ROOT/'.analysis/f649-complex-stage-cc-verified'
COHORT=(0x005AEEC0,0x00564BE0)
FIELDS={
    1:(0x0065782C,'fld','g_ThresholdAt0065782C'),
    9:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
    17:(0x00454BC0,'call','SetupCollisionAt454BC0'),
    29:(0x00453E20,'call','ResetAt453E20'),
    32:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
    46:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
    52:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    56:(0x00453E20,'call','ResetAt453E20'),
    64:(0x00657D14,'fcomp','g_ExtraThresholdAt00657D14'),
    70:(0x0040FB40,'call','SetAuxActionAt40FB40'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'native pinned PE/source helper missing '+str(path))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def source_for(addr,boss,report,mapped,reader,pe,decoder,h):
    by={x['action']:int(x['handler'],16) for x in mapped}
    previous={a:h['f645'].native_case(reader,pe,decoder,boss,by,a)
              for a in h['f645'].ACTIONS}
    parent=h['f645'].source_with_restart(addr,boss,report,mapped,reader,pe,decoder,h,previous)
    classname=f'FighterSwitchF598_Boss{addr:08X}'
    declaration='virtual void NativeVirtualFrameAdvance();'
    need(parent.count(declaration)==1,
         f'{addr:#x}: original-shaped fighter actual virtual frame declaration missing')
    parent=parent.replace(declaration,declaration+
       ' void SetupCollisionAt454BC0(int,int,int);'
       ' void SpawnRawAt453C80(int,int,int,int,int);')
    source_cfg={
       0x005AEEC0:('4','4','0.0f','21.0f','0.75f','1','5'),
       0x00564BE0:('2','2','0.0f','18.5f','0.55f','0','3'),
    }
    labels=('F649_STAGE_LIMIT','F649_TRIGGER','F649_POS','F649_SPEED',
            'F649_DRAG','F649_CLEAR_FLAG','F649_AUX')
    params=dict(zip(labels,source_cfg[addr]))
    insertion='\n'.join('#define '+k+' '+v for k,v in params.items())
    insertion+='\n#include "FighterComplexStageCCF649.inc"\n'
    insertion+='\n'.join('#undef '+k for k in params)
    marker='        case 0xCC: g_FighterProbeMarker = 205; break;'
    need(parent.count(marker)==1,
         f'{addr:#x}: original complete indexed native CC case source marker missing')
    return parent.replace(marker,insertion)


def prove_shape(reader,pe,decoder,boss,mapped,code,refs,h):
    addr=boss['address'];by={x['action']:int(x['handler'],16) for x in mapped}
    start,end=by[0xCC],by[0xCD]
    n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    original_count=128 if addr==0x005AEEC0 else 126
    original_bytes=435 if addr==0x005AEEC0 else 542
    need(len(n)==original_count and end-start==original_bytes
         and sum(i.size for i in n)==original_bytes
         and n[-1].mnemonic=='jmp',
         f'{addr:#x}: true original CC complete physical x86 geometry changed')
    instructions=[]
    for x in decoder.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    need(instructions and instructions[-1].mnemonic=='ret',
         f'{addr:#x}: entire fighter source final RET absent')
    ret=instructions[-1].address+instructions[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original complete separately owned afterRET jump DATA changes')
    # Locate exact physical source case boundaries using the real
    # compiler COFF marker, not by taking a convenient 128-instruction
    # excerpt from the body or masking byte differences.
    def marker(value):
        found=[]
        for f in refs:
            if 'g_FighterProbeMarker' not in f['symbol']:continue
            i=next((i for i,x in enumerate(instructions)
                    if x.address<=f['offset']<x.address+x.size),None)
            if (i is not None and instructions[i].mnemonic=='mov'
                    and instructions[i].op_str.endswith(f', 0x{value:x}')):
                found.append(i)
        need(len(found)==1,
             f'{addr:#x}: actual source complete indexed switch case marker {value:#x} not unique')
        return found[0]
    a,b=marker(0xCC),marker(0xCE)
    need(instructions[a+1].mnemonic=='jmp',
         f'{addr:#x}: native previous original CB index marker not followed by actual jump')
    g=instructions[a+2:b]
    need(len(g)==len(n)==original_count
         and g[-1].address+g[-1].size==instructions[b].address
         and all(x.mnemonic==y.mnemonic for x,y in zip(n,g)),
         f'{addr:#x}: generated full CC not same original x86 count/mnemonic order/boundary')
    widths=[x.size-y.size for x,y in zip(n,g)]
    if addr==0x005AEEC0:
        need(all(w==0 for w in widths)
             and g[-1].address+g[-1].size-g[0].address==435,
             'real native compact original CC full 435-byte x86 layout changed')
    else:
        need(widths.count(3)==39 and widths.count(0)==87
             and all(n[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i,w in enumerate(widths) if w==3)
             and g[-1].address+g[-1].size-g[0].address==425,
             'real native wide original CC 39 saved receiver MOV +3B widths changed')
    real_fields=[f for f in refs if g[0].address<=f['offset']<g[-1].address+g[-1].size]
    need(len(real_fields)==11,
         f'{addr:#x}: native original CC 11 true physical COFF float/global fields missing')
    field_defs=dict(FIELDS)
    field_defs[111 if addr==0x005AEEC0 else 109]=(
        0x00453C80,'call','SpawnRawAt453C80')
    source_field_ordinals=[]
    for ordinal,(target,mn,symbol) in field_defs.items():
        ni,gi=n[ordinal],g[ordinal]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(ni.mnemonic==gi.mnemonic==mn and ni.op_str==want,
             f'{addr:#x}: native original PE CC x86{ordinal} real target {target:#x} changed')
        field=[f for f in real_fields
               if gi.address<=f['offset']<gi.address+gi.size]
        need(len(field)==1
             and field[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and field[0]['addend']==0 and field[0]['local_symbol_offset'] is None
             and symbol in field[0]['symbol'],
             f'{addr:#x}: authentic native PE/COFF global/callee {target:#x} at x86{ordinal} not proved')
        source_field_ordinals.append(ordinal)
    actual,source=h['f598'].normalized(n),h['f598'].normalized(g)
    # Unlinked absolute source field x86 #1 is the only normalizer
    # discrepancy not truly a GPR/CFG problem; all its original
    # PE-targeted typed fields were independently verified above.
    mismatches=[(i,x,y) for i,(x,y) in enumerate(zip(actual,source)) if x!=y]
    unlinked_only=[i for i,x,y in mismatches if i in source_field_ordinals]
    true_bad=[(i,x,y) for i,x,y in mismatches if i not in source_field_ordinals]
    expected_bad=80 if addr==0x005AEEC0 else 78
    need(len(true_bad)==expected_bad and unlinked_only==[1],
         f'{addr:#x}: true original native CC GPR/CFG role mismatch count changed: '
         f'{len(true_bad)} vs {expected_bad}, typed-field-only {unlinked_only}')
    return {'real_original_enclosing_giant':f'0x{addr:08X}',
            'real_original_complete_CC_case_x86':len(n),
            'real_original_complete_CC_CODE_bytes':original_bytes,
            'original_CC_ordinary_source_x86':len(g),
            'original_CC_ordinary_source_CODE_bytes':g[-1].address+g[-1].size-g[0].address,
            'real_original_true_PE_COFF_fields_at_exact_ordinals':len(real_fields),
            'native_original_widened_saved_this_receiver_MOVis':39 if addr==0x00564BE0 else 0,
            'real_native_nonfield_REGISTER_CFG_role_mismatches':len(true_bad),
            'only_extra_original_typed_absolute_unlinked_ref_ordinal':unlinked_only,
            'full_original_CC_case_strict_exact':False,
            'original_whole_giant_exact':False,
            'new_accepted_exact_whole_game_functions':0}


def main():
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
      'f642':'scripts/verify-fighter-projectile-launch-f642.py',
      'f645':'scripts/verify-fighter-motion-restart-f645.py',
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py',
    }
    h={name:load('f649_'+name,ROOT/path) for name,path in paths.items()}
    reader=load('f649_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f649_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    code=SOURCE.read_text()
    need(code.count('case 0xCC:')==1
         and 'SetupCollisionAt454BC0(3,4,0xFF)' in code
         and '++I16(0x64);' in code and '++I16(0x62);' in code
         and 'SpawnRawAt453C80(0x3C,I32(0x44),I32(0x48),1,1)' in code,
         'actual original native CC typed source grammar experiment changed')
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    results=[]
    for addr in COHORT:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        cpp=OUT/f'Boss{addr:08X}-original-nonstrict-CC.cpp'
        obj=OUT/f'Boss{addr:08X}-original-nonstrict-CC.obj'
        cpp.write_text(source_for(addr,boss,report,mapped,reader,pe,decoder,h))
        cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,
             f'{addr:#x}: actual normal VC7.1 whole fighter CC source failed: {cp.stderr[-450:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        receipt=prove_shape(reader,pe,decoder,boss,mapped,code,refs,h)
        results.append(receipt)
        print(f'F649 negative {addr:#010x}: exact original complete CC '
              f'{receipt["real_original_complete_CC_case_x86"]} x86 ordinal geometry, '
              f'{receipt["real_original_complete_CC_CODE_bytes"]} native original inner CODE B, '
              '11 true physical PE-targeted zero-addend typed COFF refs, '
              f'{receipt["real_native_nonfield_REGISTER_CFG_role_mismatches"]} '
              'unresolved genuine original GPR/CFG roles. '
              'Original whole giant STILL NONEXACT; no case CODE acceptance.',flush=True)
    (OUT/'summary.json').write_text(json.dumps(results,indent=2)+'\n')
    print('F649 two entire real giant caseCC native geometry/source studies, '
          'zero strictly accepted original case interiors or whole authored '
          'game functions, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F649 actual native original complex CC negative PE/C++ proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
