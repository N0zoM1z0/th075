#!/usr/bin/env python3
"""F651/F652: strict original D1/D2 resource-shot cases in giant 00543210.

Only cold-compile the selected original whole fighter C++ parent under
pinned VC7.1. Real native CF/D0 must also remain strict on this SAME
new object, plus all earlier game cases and separately owned afterRET
jump DATA. Original other eight D1/D2 fighter owners retain 28+ true
GPR role mismatches and are NOT accepted. No 943-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f651-f652-giant-resource-shots-verified'
ACTOR=0x00543210
ACTIONS=(0xD1,0xD2)
NEXT={0xD1:0xD2,0xD2:0x12C}
FIELDS={
  0xD1:{
    6:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    22:(0x00453E20,'call','ResetAt453E20'),
    25:(0x00453D60,'call','PrepareActionAt453D60'),
    32:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
    40:(0x00453A70,'call','SpawnWithFloatAt453A70'),
    42:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    53:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    57:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
  },
  0xD2:{
    6:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    27:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
    35:(0x00453A70,'call','SpawnWithFloatAt453A70'),
    38:(0x00657F74,'fmul','g_BounceScaleAt00657F74'),
    43:(0x00657F74,'fmul','g_BounceScaleAt00657F74'),
    48:(0x00453D60,'call','PrepareActionAt453D60'),
    51:(0x00657F74,'fmul','g_BounceScaleAt00657F74'),
    57:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    68:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    72:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
  }
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'original native PE source helper absent '+str(path))
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def true_native(reader,pe,decoder,boss,by,action):
    start,end=by[action],by[NEXT[action]]
    n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    count=59 if action==0xD1 else 74
    size=199 if action==0xD1 else 251
    need(boss['address']<start<end<boss['address']+boss['size']
         and len(n)==count and sum(x.size for x in n)==end-start==size
         and n[-1].mnemonic=='jmp',
         f'actual whole original {action:#x} native case interval or 59/74 x86 differs')
    need(n[1].mnemonic=='movsx' and '+ 0x3b0]' in n[1].op_str
         and n[2].mnemonic=='cmp' and n[2].op_str.endswith(', 2')
         and n[3].mnemonic=='jge'
         and n[4].mnemonic=='push' and n[4].op_str==str(0 if action==0xD1 else 9)
         and n[10].mnemonic=='sub' and n[10].op_str.endswith(', 3')
         and n[14].mnemonic=='movsx' and '+ 0x62]' in n[14].op_str
         and n[18].mnemonic=='movsx' and '+ 0x64]' in n[18].op_str
         and n[66 if action==0xD2 else 51].mnemonic=='push'
         and n[66 if action==0xD2 else 51].op_str=='2',
         f'original real signed short resources, guarded timer, native early-state or aux-state changed {action:#x}')
    if action==0xD1:
        need(n[21].mnemonic=='mov' and n[22].mnemonic=='call'
             and n[23].mnemonic=='push' and n[23].op_str=='0x2c'
             and n[38].mnemonic=='push' and n[38].op_str=='0x3e6'
             and n[31].mnemonic=='fld' and '+ 0x48]' in n[31].op_str
             and n[32].mnemonic=='fadd' and n[32].op_str=='dword ptr [0x657888]'
             and n[49].mnemonic=='cmp' and '+ 0x4f4]' in n[49].op_str,
             'native original D1 prepare/spawn float/member resource gate changed')
    else:
        need(n[21].mnemonic=='push' and n[21].op_str=='1'
             and n[27].mnemonic=='fadd' and n[27].op_str=='dword ptr [0x657888]'
             and n[33].mnemonic=='push' and n[33].op_str=='0x3e6'
             and n[37].mnemonic=='fld' and '+ 0x50]' in n[37].op_str
             and n[38].mnemonic=='fmul' and n[38].op_str=='dword ptr [0x657f74]'
             and n[42].mnemonic=='fld' and '+ 0x54]' in n[42].op_str
             and n[43].mnemonic=='fmul' and n[43].op_str=='dword ptr [0x657f74]'
             and n[46].mnemonic=='push' and n[46].op_str=='0x2c'
             and n[50].mnemonic=='fld' and '+ 0x5c]' in n[50].op_str
             and n[51].mnemonic=='fmul' and n[51].op_str=='dword ptr [0x657f74]'
             and n[53].mnemonic=='fsubr' and '+ 0x54]' in n[53].op_str
             and n[64].mnemonic=='cmp' and '+ 0x4f4]' in n[64].op_str,
             'native original D2 member-first float scaling, outside-stage drag or true native frame transition differs')
    for i,(target,mn,_) in FIELDS[action].items():
        instr=n[i]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(instr.mnemonic==mn and instr.op_str==want,
             f'original physical D1/D2 PE field target {target:#x} at x86{i} changed')
    return n,{'original_action':f'0x{action:02X}',
              'original_native_full_case_start':f'0x{start:08X}',
              'original_native_full_case_next_handler':f'0x{end:08X}',
              'original_whole_internal_CODE_bytes':size,
              'original_x86_GPR_x87_CFG_roles':count,
              'true_PE_targeted_COFF_fields':len(FIELDS[action]),
              'whole_fighter_parent_exact':False}


def source_with_d1_d2(reader,pe,decoder,boss,report,mapped,h):
    by={x['action']:int(x['handler'],16) for x in mapped}
    previous={a:h['f646'].native_case(reader,pe,decoder,boss,by,a)
              for a in (0xCF,0xD0)}
    src=h['f646'].source_with_cases(ACTOR,boss,report,mapped,reader,pe,decoder,h,previous)
    decl='void SpawnDirectedAt453A70(int,int,int,char,int);'
    need(src.count(decl)==1,'source source class original directed sprite method declaration missing')
    src=src.replace(decl,decl+' void SpawnWithFloatAt453A70(int,int,float,char,int);')
    for action,inc,macro in ((0xD1,'FighterResourceShotD1F651.inc',
                  {'F651_DECAY':'3','F651_SPRITE':'0x3E6'}),
                 (0xD2,'FighterResourceShotD2F652.inc',
                  {'F652_DECAY':'3','F652_SPRITE':'0x3E6','F652_SCALE_BEFORE':'0'})):
        placeholder=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(placeholder)==1,
             f'original game D1/D2 real source marker absent case{action:#x}')
        replace='\n'.join('#define '+k+' '+v for k,v in macro.items())
        replace+=f'\n#include "{inc}"\n'
        replace+='\n'.join('#undef '+k for k in macro)
        src=src.replace(placeholder,replace)
    need(src.count('        case 0x12C: g_FighterProbeMarker = 301; break;')==1,
         'next physical original native handler is action0x12C, not nonexistent D3')
    return src


def verify_full(reader,pe,decoder,boss,report,mapped,code,refs,originals,h):
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret','entire original giant source final return missing')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         'original complete after-RET compressed switch DATA ownership changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev={a:h['f646'].native_case(reader,pe,decoder,boss,by,a)
          for a in (0xCF,0xD0)}
    h['f646'].verify_fresh(reader,pe,decoder,boss,report,mapped,code,refs,prev,h)
    prior_mark=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        i=next((j for j,x in enumerate(ins) if x.address<=f['offset']<x.address+x.size),None)
        if i is not None and ins[i].mnemonic=='mov' and ins[i].op_str.endswith(', 0xcf'):
            prior_mark.append(i)
    need(len(prior_mark)==1 and ins[prior_mark[0]+1].mnemonic=='jmp',
         'previous CF original source boundary marker not unique')
    offset=prior_mark[0]+2+30+60
    results=[]
    for action in ACTIONS:
        original,meta=originals[action]
        gen=ins[offset:offset+len(original)];offset+=len(original)
        need(len(gen)==len(original) and gen[-1].mnemonic=='jmp'
             and all(x.size==y.size for x,y in zip(original,gen)),
             f'case{action:#x}: original complete native 59/74-x86 source role widths changed')
        low,high=gen[0].address,gen[-1].address+gen[-1].size
        need(high-low==meta['original_whole_internal_CODE_bytes'],
             f'case{action:#x}: entire source native 199/251B geometry shifted')
        physical=[f for f in refs if low<=f['offset']<high]
        need(len(physical)==len(FIELDS[action]),
             f'case{action:#x}: original physical 8/10 typed PE/COFF fields missing')
        for i,(target,mn,symbol) in FIELDS[action].items():
            a,b=original[i],gen[i]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
                 f'case{action:#x}: real original PE symbol {target:#x} at x86{i} changed')
            found=[f for f in physical if b.address<=f['offset']<b.address+b.size]
            need(len(found)==1
                 and found[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
                 and symbol in found[0]['symbol'],
                 f'case{action:#x}: native x86{i} true target {target:#x} original typed COFF wrong')
        lhs,rhs=h['f598'].normalized(original),h['f598'].normalized(gen)
        # Actual original absolute PE x87 globals appear as dword [0];
        # normalize ONLY proven genuine typed DIR32 global field x86.
        global_idxs={i for i,(target,mn,sym) in FIELDS[action].items() if mn!='call'}
        mismatched=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs))
                    if a!=b and i not in global_idxs]
        need(not mismatched,
             f'case{action:#x}: real original GPR/x87/CFG register roles differ: {mismatched[:5]}')
        results.append({'original_native_case':meta['original_action'],
                        'original_complete_internal_CODE_bytes':meta['original_whole_internal_CODE_bytes'],
                        'original_complete_native_x86_roles':len(original),
                        'real_original_typed_PE_COFF_fields':len(physical),
                        'new_accepted_whole_authored_function_bytes':0})
    need(ins[offset].mnemonic=='mov' and ins[offset].op_str.endswith(', 0x12d'),
         'source D2 whole case must terminate at real following action0x12C marker')
    return {'original_entire_parent_giant':f'0x{ACTOR:08X}',
            'entire_original_parent_CODE_still_NONEXACT':boss['size'],
            'separately_owned_original_afterRET_switch_DATA_bytes':boss['postret_size'],
            'preceding_original_CF_D0_F645_F642_30_source_cases_and_jump_DATA_rechecked':True,
            'two_new_strict_native_resource_cases':results,
            'original_inner_CODE_UNCREDITED_bytes':sum(x['original_complete_internal_CODE_bytes'] for x in results),
            'new_whole_authored_exact_functions':0}


def main():
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
      'f636':'scripts/verify-fighter-landing-pair-f636.py',
      'f637':'scripts/verify-fighter-ground-boost-f637.py',
      'f639':'scripts/verify-fighter-last-landings-f639.py',
      'f641':'scripts/verify-fighter-no-counter-landings-f641.py',
      'f642':'scripts/verify-fighter-projectile-launch-f642.py',
      'f645':'scripts/verify-fighter-motion-restart-f645.py',
      'f646':'scripts/verify-fighter-fall-reflect-f646.py',
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py',
    }
    h={name:load('f651_'+name,ROOT/path) for name,path in loaders.items()}
    reader=load('f651_reader',ROOT/'scripts/compare-coff-function.py')
    acts=load('f651_acts',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,decoder,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    orig={a:true_native(reader,pe,decoder,boss,by,a) for a in ACTIONS}
    first=(ROOT/'probes/FighterResourceShotD1F651.inc').read_text()
    second=(ROOT/'probes/FighterResourceShotD2F652.inc').read_text()
    need(first.count('case 0xD1:')==1 and second.count('case 0xD2:')==1
         and 'F32(0x48)+g_ContactProjectionAt00657888' in first
         and 'F32(0x48)+g_ContactProjectionAt00657888' in second
         and 'POS54=POS54-F32(0x5C)*g_BounceScaleAt00657F74;' in second,
         'genuine original native D1/D2 59/74-x86 C++ grammar changed')
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-four-real-CF-D0-D1-D2.cpp'
    obj=OUT/'Boss00543210-four-real-CF-D0-D1-D2.obj'
    cpp.write_text(source_with_d1_d2(reader,pe,decoder,boss,report,mapped,h))
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,
         'actual original VC7.1 entire giant fighter C++ source failed: '+cp.stderr[-480:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    result=verify_full(reader,pe,decoder,boss,report,mapped,code,refs,orig,h)
    (OUT/'summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F651/F652 pinned original giant 0x00543210 D1+D2: '
          '59/59 +74/74 strict authentic native GPR/x87/CFG roles, '
          f'{result["original_inner_CODE_UNCREDITED_bytes"]} original CODE bytes, '
          f'{sum(x["real_original_typed_PE_COFF_fields"] for x in result["two_new_strict_native_resource_cases"])} '
          'actual PE/COFF. Prior CF+D0 strict in SAME whole giant C++ OBJ; '
          'F645/F642 and all older game cases and afterRET table preserved. '
          'Original parent still NONEXACT; no authored whole-function credit '
          'and no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F651/F652 original Japanese TH075 resource shot source proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
