#!/usr/bin/env python3
"""F620: true full 44-x86 native action0x5F in giant actor005AEEC0.

The real original 0x5D/0x5E predecessor cases are still source-register-
nonexact; their natural 64-x86/210B source candidates shift the register
phase of 0x5F too. Explicit negative-context control proves this.
Positive source retains the diagnostic 5D/5E placeholders and all 30
prior genuine game case subranges, and verifies actual native whole
0x5F bytes/3 PE-targeted COFF fields without crediting incomplete
giants or source case fragments as accepted original functions.
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
SOURCE=ROOT/'probes/FighterFacing5FF620.inc'
NEG_SOURCE=ROOT/'probes/FighterSimpleAirTransitionF619.inc'
OUT=ROOT/'.analysis/f620-fighter-facing-source'
ADDR=0x005AEEC0
FIELDS={1:(0x0040FA30,'call'),9:(0x0040FAC0,'call'),15:(0x0040FAC0,'call')}


def need(test,message):
    if not test:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing original PE source helper '+str(path))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def real_case(reader,pe,decoder,boss,by,action):
    start=by[action]
    remaining=sorted({x for x in by.values() if x>start})
    need(remaining,'original native next-case physical handler missing')
    end=remaining[0]
    ins=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    count,size=(44,144) if action==0x5F else (64,210)
    need(ADDR<=start<end<ADDR+boss['size']
         and len(ins)==count and end-start==size
         and sum(x.size for x in ins)==size
         and ins[-1].mnemonic=='jmp',
         f'original 0x{action:X} complete native handler x86/size changed')
    if action==0x5F:
        need(ins[0].mnemonic=='mov' and ins[1].mnemonic=='call'
             and ins[1].op_str=='0x40fa30'
             and ins[7].op_str=='0' and ins[13].op_str=='1'
             and ins[12].mnemonic=='jle' and ins[11].op_str.endswith(', 0')
             and ins[19].mnemonic=='movsx' and ins[20].mnemonic=='sub'
             and ins[22].mnemonic=='jne' and ins[23].mnemonic=='mov'
             and ins[24].mnemonic=='mov' and '+ 0x2e8]' in ins[24].op_str
             and ins[26].mnemonic=='fld' and ins[27].mnemonic=='fcomp'
             and ins[29].op_str=='ah, 0x41'
             and ins[30].mnemonic=='jne' and ins[30].op_str==f'0x{ins[33].address:x}'
             and ins[38].mnemonic=='fnstsw' and ins[39].op_str=='ah, 5'
             and ins[40].mnemonic=='jp',
             'native 5F actor-facing two independent original x87 tests differ')
        for i,(target,mn) in FIELDS.items():
            need(ins[i].mnemonic==mn and ins[i].op_str==f'0x{target:x}',
                 f'original 5F native PE true game call {target:#x} differs at x86 ordinal{i}')
    else:
        need(ins[9].mnemonic=='mov'
             and ins[9].op_str.endswith(', '+('0x41300000' if action==0x5D else '0xc1300000'))
             and ins[55].mnemonic=='cmp' and ins[55].op_str.endswith(', 0xe')
             and all(ins[i].op_str==f'0x{target:x}' for i,target in
                     ((11,0x40fa30),(19,0x40fac0),(25,0x40fac0))),
             f'original 0x{action:X} 64-instruction PE action control changed')
    return ins,{'action':f'0x{action:02X}',
                'real_native_original_handler':f'0x{start:08X}',
                'native_original_whole_inner_CODE_bytes':size,
                'complete_original_x86_instructions':count,
                'real_physical_original_typed_COFF_fields':3,
                'original_enclosing_whole_boss_exact':False}


def build_source(reader,pe,decoder,boss,report,mapped,
                 f598,f567,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,f614,negative):
    by={x['action']:int(x['handler'],16) for x in mapped}
    original58,info58=f614.native_case(reader,pe,decoder,boss,by)
    source=f614.reconstruct_source(ADDR,boss,report,mapped,reader,pe,decoder,
              f598,f567,f600,f602,f603,f605,f606,f607,f608,
              f610,f611,f613,info58)
    marker='        case 0x5F: g_FighterProbeMarker = 96; break;'
    need(source.count(marker)==1,'original 5F next physical source placeholder missing')
    source=source.replace(marker,
            '#define F620_FIRST_ACTION 0\n#define F620_SECOND_ACTION 1\n'
            '#include "FighterFacing5FF620.inc"\n'
            '#undef F620_FIRST_ACTION\n#undef F620_SECOND_ACTION')
    if negative:
        a='        case 0x5D: g_FighterProbeMarker = 94; break;'
        b='        case 0x5E: g_FighterProbeMarker = 95; break;'
        end='#define F620_FIRST_ACTION 0'
        need(source.count(a)==source.count(b)==source.count(end)==1,
             'native original 5D/5E diagnostic placeholders changed')
        block=[]
        for action,initial in ((0x5D,'11.0f'),(0x5E,'-11.0f')):
            values={'F619_CASE':f'0x{action:X}', 'F619_START_POS':initial}
            block.extend('#define '+k+' '+v for k,v in values.items())
            block.append('#include "FighterSimpleAirTransitionF619.inc"')
            block.extend('#undef '+k for k in values)
        start=source.index(a)
        finish=source.index(end,start)
        source=source[:start]+'\n'.join(block)+'\n'+source[finish:]
    return source


def check_candidate(reader,pe,decoder,boss,code,refs,origins,f598,f614,
                    f600,f602,f603,f605,f606,f607,f608,f610,f611,f613,
                    core,zero,switch,report,mapped,negative):
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',
         'selected new whole fighter source lacks actual return')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         'original complete afterRET indexed DATA ownership changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    earlier,info=f614.native_case(reader,pe,decoder,boss,by)
    f614.compare_candidate(reader,pe,decoder,f598,f600,f602,f603,
                   f605,f606,f607,f608,f610,f611,f613,core,zero,switch,
                   boss,report,mapped,code,refs,earlier,info)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need([sparse[x-0x33] for x in (0x5D,0x5E,0x5F,0x60)]==[19,20,21,22],
         'actual original 5D/5E/5F/60 compressed physical slot indices changed')
    native_ptrs=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+i*4,4),'little')
                 for i in (19,20,21,22)]
    need(native_ptrs==[by[x] for x in (0x5D,0x5E,0x5F,0x60)],
         'actual original sparse/dense game CODE boundaries differ')
    offsets=[]
    for i in (19,20,21,22):
        rows=[x for x in refs if x['offset']==ret+44+4*i]
        need(len(rows)==1 and rows[0]['type']=='DIR32' and rows[0]['addend']==0
             and rows[0]['local_symbol_offset'] is not None,
             f'original afterRET table C++ source actual original DWORD slot {i} absent')
        offsets.append(rows[0]['local_symbol_offset'])
    results=[]
    for action,start,end in zip((0x5D,0x5E,0x5F),offsets,offsets[1:]):
        orig,info=origins[action]
        if action!=0x5F and not negative:continue
        generated=list(decoder.disasm(code[start:end],start))
        need(len(generated)==len(orig)==info['complete_original_x86_instructions']
             and end-start==info['native_original_whole_inner_CODE_bytes']
             and sum(x.size for x in generated)==end-start,
             f'action0x{action:X}: generated natural entire native case length/roles changed')
        physical=[x for x in refs if start<=x['offset']<end]
        need(len(physical)==3,
             f'original action0x{action:X}: generated physical three true COFF fields missing')
        expected=FIELDS if action==0x5F else {
            11:(0x0040FA30,'call'),19:(0x0040FAC0,'call'),25:(0x0040FAC0,'call')}
        names={0x0040FA30:'GetNativeActionAt40FA30',0x0040FAC0:'SetNativeActionAt40FAC0'}
        for i,(dest,mn) in expected.items():
            a,b=orig[i],generated[i]
            need(a.mnemonic==b.mnemonic==mn and a.op_str==f'0x{dest:x}',
                 f'action0x{action:X}: original native call x86 ordinal {i} changed')
            rows=[x for x in physical if b.address<=x['offset']<b.address+b.size]
            need(len(rows)==1 and rows[0]['type']=='REL32' and rows[0]['addend']==0
                 and rows[0]['local_symbol_offset'] is None
                 and names[dest] in rows[0]['symbol'],
                 f'action0x{action:X}: original actual native PE/COFF call target {dest:#x} differs')
        lhs,rhs=f598.normalized(orig),f598.normalized(generated)
        mismatches=[(i,x,y) for i,(x,y) in enumerate(zip(lhs,rhs)) if x!=y]
        expected_wrong=42 if action!=0x5F else (26 if negative else 0)
        need(len(mismatches)==expected_wrong,
             f'original native action0x{action:X}: register/CFG source mismatch '
             f'{len(mismatches)} vs expected {expected_wrong}: {mismatches[:5]}')
        results.append({'original_native_action':info['action'],
                        'original_complete_native_internal_CODE_bytes':info['native_original_whole_inner_CODE_bytes'],
                        'original_x86_instructions':info['complete_original_x86_instructions'],
                        'physical_typed_original_PE_COFF_fields':3,
                        'nonmatching_native_GPR_CFG_roles':len(mismatches),
                        'strict_original_native_case_role_match':not mismatches,
                        'original_enclosing_giant_whole_exact':False})
    return {'whole_original_fighter':'0x005AEEC0',
            'whole_original_CODE_still_NONEXACT':boss['size'],
            'real_original_afterRET_data_separately_owned':boss['postret_size'],
            'prior_30_original_case_roles_retained_in_fresh_OBJ':True,
            'actual_5D_5E_5F_native_cases':results,
            'positive_5F_strict_original_bytes_uncredited':0 if negative else 144,
            'new_accepted_whole_original_game_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--negative-context',action='store_true',
                   help='compile actual 64-x86 source for preceding 5D+5E and verify 42/42/26 role mismatches')
    options=p.parse_args()
    source=SOURCE.read_text()
    need(source.count('case 0x5F:')==1
         and source.count('if (*(&F32(0x44))>')==1
         and source.count('if (*(&F32(0x44))<')==1,
         'original 5F source no longer has two independent x87-facing comparisons')
    if options.negative_context:
        negative=NEG_SOURCE.read_text()
        need(negative.count('case F619_CASE:')==1 and 'I16(0x62)==14' in negative,
             'genuine original 64-x86 stage2/stage14 negative source missing')
    f602=load('f620_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f620_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f620_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f620_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f620_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f620_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f620_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f620_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f620_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f620_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f620_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f613=load('f620_f613',ROOT/'scripts/verify-fighter-trajectory-recovery-f613.py')
    f614=load('f620_f614',ROOT/'scripts/verify-fighter-trajectory-burst-f614.py')
    reader=load('f620_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f620_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f620_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f620_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f620_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDR)
    report,mapped=actions.report_boss(reader,pe,decoder,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals={a:real_case(reader,pe,decoder,boss,by,a) for a in (0x5D,0x5E,0x5F)}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cpp=OUT/('negative-real-predecessor-context.cpp' if options.negative_context else
             'strict-native-5F-context.cpp')
    obj=cpp.with_suffix('.obj')
    cpp.write_text(build_source(reader,pe,decoder,boss,report,mapped,
                f598,f567,f600,f602,f603,f605,f606,f607,f608,
                f610,f611,f613,f614,options.negative_context))
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    cpp.with_suffix('.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,
         f'original native VC7.1 natural C++ source compile failed: {p.stderr[-600:]}')
    code,refs=reader.object_function(obj,'?Advance@FighterSwitchF598_Boss005AEEC0@@QAEXXZ')
    result=check_candidate(reader,pe,decoder,boss,code,refs,originals,f598,f614,
                 f600,f602,f603,f605,f606,f607,f608,f610,f611,f613,
                 core,zero,switch,report,mapped,options.negative_context)
    receipt=OUT/('negative-summary.json' if options.negative_context else 'positive-summary.json')
    receipt.write_text(json.dumps(result,indent=2)+'\n')
    for row in result['actual_5D_5E_5F_native_cases']:
        print(f'F620 {row["original_native_action"]}: real original complete '
              f'{row["original_complete_native_internal_CODE_bytes"]}B/'
              f'{row["original_x86_instructions"]} x86, 3 original typed PE/COFF calls, '
              f'{row["nonmatching_native_GPR_CFG_roles"]} GPR/CFG source mismatches',flush=True)
    print('F620: prior 30 real original game cases and full afterRET switch DATA retained; '
          f'original strict 0x5F inner CODE {result["positive_5F_strict_original_bytes_uncredited"]}B '
          '(NEVER whole-function credit); context-sensitive GPR phase independently '
          'documented, original giant NONEXACT, no full all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F620 original Japanese native 0x5D/5E/5F source context verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
