#!/usr/bin/env python3
"""F814: integrate real stage59 + 5D/5E in one 46KB fighter, observe GPR tradeoff.

Regenerate selected F617 original parent first. Add tracked genuine
stage-3 0x59 C++, F806 shared/default. Fresh whole VC7.1 compiles:
baseline preserves full native 356B/95 x86/16 PE fields in 0x59
and both 337B/101 x86/8 PE-field 0x5D/0x5E cases, but reg
phase 5E now has 61 true mismatches (not F617's old zero).
A semantically symmetric but nonnative swapped getter check
removes the 5E GPR problem only at cost of wrong 0x59 CFG opcodes
and 2 extra whole-code bytes/x86, proving no legitimate gain.
Never accept split game cases or full 46755B giant; no mass replay.
"""
from __future__ import annotations
import importlib.util
import json
import os
import re
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f814-stage3-context'
BOSS=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
REAL_CASES={0x59:(0x0052327A,0x005233DE,356,95,16),
            0x5D:(0x005233DE,0x0052352F,337,101,8),
            0x5E:(0x0052352F,0x00523680,337,101,8)}
AUX={0x0040FA30,0x0040FAC0,0x0040FB40}

def need(p,msg):
    if not p:raise ValueError(msg)

def load(tag,file):
    spec=importlib.util.spec_from_file_location(tag,ROOT/file)
    need(spec is not None and spec.loader is not None,'source reader missing '+str(file))
    m=importlib.util.module_from_spec(spec)
    sys.modules[tag]=m
    spec.loader.exec_module(m)
    return m

def source_from_selected_f617():
    # Physically prove old F617 30 prior and two next cases in its
    # shorter whole parent; this is prior evidence, NOT current exactness.
    OUT.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(ROOT/'scripts/repo-python'),
         str(ROOT/'scripts/verify-fighter-air-transition-f617.py'),
         '--boss','0x005214B0'],cwd=ROOT,capture_output=True,text=True,timeout=320)
    (OUT/'f617-prior-one-parent-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'selected F617 original first 30 plus 5D/5E failed '+(run.stdout+run.stderr)[-750:])
    src=(ROOT/'.analysis/f617-fighter-air-source/Boss005214B0-32-real-game-case-source.cpp').read_text()
    for a,b in ((0,1),(2,3)):
        first=f'        case 0x{a:X}:'
        last=f'        case 0x{b:X}:'
        begin=src.index(first)
        end=src.index(last,begin+len(first))
        part=src[begin:end]
        need(part.rstrip().endswith('break;'),'real original first 0/2 case terminal source moved')
        src=src[:begin]+part[:part.rindex('break;')]+(
             'goto native_script_shared_getter;\n')+src[end:]
    for a,val in ((4,'3.0f'),(5,'-3.0f')):
        old=f'case 0x{a:X}: POS = {val}; break;'
        need(src.count(old)==1,'native original earlier action 4/5 source changed')
        src=src.replace(old,f'case 0x{a:X}: POS = {val}; goto native_script_shared_getter;',1)
    mark='        default: g_FighterProbeMarker = 0;'
    need(src.count(mark)==1,'F806 native original shared default source marker changed')
    src=src.replace(mark,'#include "FighterScriptedNativeDefaultF806.inc"',1)
    old='    }\n}\n#undef OWNER'
    need(src.count(old)==1,'real full-parent compiler method closing changed')
    src=src.replace(old,'    }\n#include "FighterScriptedSharedGetterF806.inc"\n}\n#undef OWNER',1)
    marker='        case 0x59: g_FighterProbeMarker = 90; break;'
    need(src.count(marker)==1,'real next native 0x59 source placeholder disappeared')
    decl=('extern float g_F728_RandomOffsetYAt00657858;\n'
          'extern float g_F747_BounceXAt006590BC;\n'
          'extern float g_F747_BounceYAt00658044;\n')
    src=decl+src
    need(src.count('goto native_script_shared_getter;')==4,'native 4 early goto count changed')
    return src

def compile_one(name,src):
    cpp=OUT/(name+'.cpp')
    obj=OUT/(name+'.obj')
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv= d;winemenubuilder.exe=d'.replace('= d','=d')
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=230)
    (OUT/(name+'.log')).write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'F814 full native source compilation failed '+name+' '+(proc.stdout+proc.stderr)[-850:])
    return obj

def main():
    rd=load('f814_rd','scripts/compare-coff-function.py')
    f617=load('f814_f617','scripts/verify-fighter-air-transition-f617.py')
    f614=load('f814_f614','scripts/verify-fighter-trajectory-burst-f614.py')
    f613=load('f814_f613','scripts/verify-fighter-trajectory-recovery-f613.py')
    f610=load('f814_f610','scripts/verify-fighter-trajectory-bounce-f610.py')
    f607=load('f814_f607','scripts/verify-fighter-trajectory-landing-f607.py')
    f605=load('f814_f605','scripts/verify-fighter-trajectory-followups-f605.py')
    f602=load('f814_f602','scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f814_f600','scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f814_f598','scripts/verify-fighter-singleton-contact-f598.py')
    f603=load('f814_f603','scripts/verify-fighter-trajectory-spawn-f603.py')
    f606=load('f814_f606','scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f608=load('f814_f608','scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f611=load('f814_f611','scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    core=load('f814_core','scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f814_zero','scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f814_switch','scripts/verify-fighter-natural-switch-probes.py')
    actions=load('f814_actions','scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==BOSS)
    need(boss['size']==46755 and boss['postret_size']==901 and boss['instructions']==13230,
         'original whole 46KB native function changed')
    report,mapped=actions.report_boss(rd,pe,d,boss)
    addresses={x['action']:int(x['handler'],16) for x in mapped}
    for action,(a,b,byte_length,inscount,_) in REAL_CASES.items():
        need(addresses[action]==a and b-a==byte_length
             and len(list(d.disasm(rd.pe_bytes_at(pe,a,byte_length),a)))==inscount,
             'original native complete case %x PE extent unverified'%action)
    props={act:f617.native_case(rd,pe,d,boss,addresses,act)
           for act in (0x5D,0x5E)}
    original_59=rd.pe_bytes_at(pe,REAL_CASES[0x59][0],356)
    original_59_ins=list(d.disasm(original_59,REAL_CASES[0x59][0]))
    source=source_from_selected_f617()
    mark='#include "FighterScriptedBounce59F813.inc"'
    orig_inc=(ROOT/'probes/FighterScriptedBounce59F813.inc').read_text()
    need('S16(0x62)==3' in orig_inc
         and 'SetAuxActionAt40FB40(3)' in orig_inc
         and source.count('        case 0x59: g_FighterProbeMarker = 90; break;')==1,
         'real original stage3 action59 source changed')
    original_placeholder='        case 0x59: g_FighterProbeMarker = 90; break;'
    control=orig_inc.replace(
        'GetNativeActionAt40FA30()==S16(0x70)',
        'S16(0x70)==GetNativeActionAt40FA30()')
    need(control!=orig_inc,'genuine value-expression swap control absent')
    candidates={'native-stage3':source.replace(original_placeholder,mark,1),
        'wrong-getter-order':source.replace(original_placeholder,control,1)}
    result=[]
    for name,src in candidates.items():
        obj=compile_one(name,src)
        code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
        instructions=[]
        for ins in d.disasm(code,0):
            instructions.append(ins)
            if ins.mnemonic=='ret':break
        ret=instructions[-1].address+instructions[-1].size
        expected=(10280,2630,901,558) if name=='native-stage3' else (10282,2632,901,558)
        need((ret,len(instructions),len(code)-ret,len(refs))==expected,
             'native original source candidate wrong whole parent size/x86/data or COFF '+name)
        strict=f617.verify_source(rd,pe,d,f598,f600,f602,f603,f605,f606,
              f607,f608,f610,f611,f613,f614,core,zero,switch,boss,report,mapped,
              code,refs,props,name=='native-stage3')
        need(strict['all_previous_30_native_game_cases_source_retained']
             and strict['source_5D_native_GPR_CFG_role_mismatches']==61
             and strict['source_5E_native_GPR_CFG_role_mismatches']==(
                     61 if name=='native-stage3' else 0),
             'F814 native 5D/5E codegen GPR relative to actual original changed')
        second=boss['tables'][1]
        native_index=rd.pe_bytes_at(pe,second['map_addr'],second['map_length'])
        need([native_index[case-0x33] for case in (0x59,0x5D,0x5E,0x5F)]
             ==[18,19,20,21],'native packed true 59/5D/5E/5F case mapping changed')
        fields=[next((r for r in refs if r['offset']==ret+44+4*slot),None)
                for slot in (18,19,20,21)]
        need(all(f and f['type']=='DIR32' and f['local_symbol_offset'] is not None for f in fields),
             'whole original dense switch source case index fields absent')
        p0,p1=fields[0]['local_symbol_offset'],fields[1]['local_symbol_offset']
        generated=list(d.disasm(code[p0:p1],p0))
        wrong_mnemonic=[j for j,(n,cpp) in enumerate(zip(original_59_ins,generated))
                        if n.mnemonic!=cpp.mnemonic]
        wrong_width=[j for j,(n,cpp) in enumerate(zip(original_59_ins,generated))
                     if n.size!=cpp.size]
        if name=='native-stage3':
            need((p1-p0,len(generated),wrong_mnemonic,wrong_width)==(356,95,[],[]),
                 'native stage3 source does not preserve real complete original 0x59 x86 grammar')
        else:
            need((p1-p0,len(generated),wrong_mnemonic,wrong_width)==(
                 356,95,[54,55,56],[54,56,57]),
                 'wrong getter order could deceptively restore 5E without actual 0x59 corruption')
        physical=[r for r in refs if p0<=r['offset']<p1]
        need(len(physical)==16,'all original 0x59 physical fields must remain present')
        actual_relocations=0
        for r in physical:
            i=r['offset']-p0
            if name=='native-stage3':
                need(r['addend']==0 and r['local_symbol_offset'] is None and
                     r['type'] in ('REL32','DIR32') and i<=352,
                     'source native action59 true PE field not bound')
                real=(int.from_bytes(original_59[i:i+4],'little')
                      if r['type']=='DIR32' else
                      REAL_CASES[0x59][0]+i+4+int.from_bytes(original_59[i:i+4],'little',signed=True))
                sym=re.search(r'At([0-9a-fA-F]{6,8})',r['symbol'])
                want=(int(sym.group(1),16) if sym else
                      0x006406AC if r['symbol']=='__ftol2' else None)
                need(want is not None and real==want,'real actor59 source COFF target is not true original PE')
                actual_relocations+=1
        if name=='native-stage3':
            need(actual_relocations==16,'real original action59 16 typed PE fields not checked')
        suffix=rd.pe_bytes_at(pe,0x0052CB25,46)
        source_tail_length=46 if name=='native-stage3' else 47
        tail_start=ret-source_tail_length
        last=[r for r in refs if tail_start<=r['offset']<ret]
        need(len(last)==3 and
             {r['offset']-tail_start for r in last}=={4,28,38},
             'source new parent default three original call fields/offsets changed')
        tailmask=set()
        for ref in last:
            off=ref['offset']-tail_start
            native_target=0x0052CB25+off+4+int.from_bytes(suffix[off:off+4],'little',signed=True)
            need(ref['type']=='REL32' and ref['addend']==0
                 and ref['local_symbol_offset'] is None
                 and native_target=={4:0x0040FA30,28:0x0040FAC0,38:0x0040FA30}[off]
                 and f'At{native_target:06X}' in ref['symbol'],
                 'original physical PE default/getter call target differs from source')
            tailmask.update(range(off,off+4))
        source_tail=list(d.disasm(code[tail_start:ret],tail_start))
        native_tail=list(d.disasm(suffix,0x0052CB25))
        if name=='native-stage3':
            need(len(source_tail)==len(native_tail)==16
                 and all(a.mnemonic==b.mnemonic and a.size==b.size
                         for a,b in zip(native_tail,source_tail)),
                 'correct native stage3 parent must preserve original complete 46B/16-x86 suffix geometry')
            tailbad=[j for j in range(46) if j not in tailmask and suffix[j]!=code[tail_start+j]]
            need(tailbad==[2,10,12,13,16,19,26,36],
                 'native stage3 honest default 46B register/frame byte differences changed')
        else:
            need(len(source_tail)==17 and source_tail[-4].mnemonic=='pop'
                 and source_tail[-4].op_str=='esi'
                 and [x.mnemonic for x in source_tail[-3:]]==['mov','pop','ret']
                 and source_tail[-3].op_str=='esp, ebp',
                 'wrong-order source must disclose newly emitted NON-NATIVE POP ESI epilogue')
            need(all(native_tail[k].mnemonic==source_tail[k].mnemonic and
                     native_tail[k].op_str.replace('[ebp - 0x10]','[ebp - 8]')==source_tail[k].op_str
                     for k in (2,3,4,5)),
                 'wrong-order source recovered native GPR only by preserving real game comparison')
            tailbad=None # physically different entire function length/epilogue; never score by masking it
        result.append({'whole_source_variant':name,'source_callable_CODE_B':ret,
            'source_whole_x86':len(instructions),'postRET_unchanged_DATA_B':len(code)-ret,
            'native_0x59_full_CODE_B':356,'native_0x59_x86':95,
            'native_0x59_wrong_mnemonic_positions':wrong_mnemonic,
            'native_0x59_wrong_width_positions':wrong_width,
            'real_original_0x59_PE_fields_checked':actual_relocations,
            'native_0x5D_full_CODE_B':337,'native_0x5D_x86':101,
            'native_0x5D_original_GPR_CFG_role_mismatches':
                strict['source_5D_native_GPR_CFG_role_mismatches'],
            'native_0x5E_full_CODE_B':337,'native_0x5E_x86':101,
            'native_0x5E_original_GPR_CFG_role_mismatches':
                strict['source_5E_native_GPR_CFG_role_mismatches'],
            'native_5D_5E_true_original_PE_fields':16,
            'original_native_901B_jump_DATA_preserved':True,
            'real_original_tail_46B_current_source_tail_B':source_tail_length,
            'native_shared_46B_tail_wrong_nonfield_offsets':tailbad,
            'wrong_order_source_added_NONNATIVE_POP_ESI':name=='wrong-getter-order',
            'whole_game_exact':False})
        print('F814',name,'entire source',ret,'B',len(instructions),
              'x86; case 0x59 wrong op',wrong_mnemonic,'wrong sizes',wrong_width,
              '0x5D/5E real original normalized GPR-role negatives',
              strict['source_5D_native_GPR_CFG_role_mismatches'],
              strict['source_5E_native_GPR_CFG_role_mismatches'],flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'verified-summary.json').write_text(json.dumps({
        'original_giant':'0x005214B0','native_whole_CODE_B':46755,
        'genuine_complete_native_actions_in_this_parent':33,
        'new_original_game_case_bodies':['0x5D','0x5E'],
        'native_case5D_5E_original_B':337,
        'native_case5D_5E_original_x86':101,
        'native_case5D_5E_original_true_PE_fields_each':8,
        'real_actor59_source_context_changes_later_5E_original_GPR_cycle':True,
        'wrong_getter_order_reproduces_5E_but_breaks_real_59_opcodes':True,
        'two_selected_whole_parent_results':result,
        'accepted_new_game_exact_CODE_B':0,
        'all_979_unit_cold_replay':False},indent=2)+chr(10))
    print('F814: two full selected 46KB C++ variants: original stage3 case59 + native 337B/101-x86/8-PE 5D/5E in 10280-B whole parent. Real 0x59 makes BOTH 5D and 5E 61 native GPR mismatches; swapped getter restores 5E but corrupts 0x59 native opcode/width, so is INVALID source. No split/whole exact credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F814 whole native scripted 5D/5E original context failed:',exc,file=sys.stderr)
        raise SystemExit(1)
