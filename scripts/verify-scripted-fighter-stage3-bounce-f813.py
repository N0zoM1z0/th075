#!/usr/bin/env python3
"""F813: real native 0x59 stage-3 bounce in growing 46KB fighter parent.

Use F812's true previous 30 game-action parent source; add the
native 356B/95-x86 original 0x59 with independent 16 true PE/COFF
fields, explicit native stage equality 3 and aux 3 (not F752's
other fighter stage assumptions). All prior 30 original case roles,
901B source/native afterRET DATA, actual original F806 46B shared
tail and four early entry JMPs are freshly revalidated in the one
affected whole-parent compile. Source GPR and EBP nonfield negatives
remain; no whole 46755B native game exact credit or cold-all replay.
"""
from __future__ import annotations
from pathlib import Path
import importlib.util
import json
import os
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f813-scripted-59'
ADDR=0x005214B0
SUFFIX=0x0052CB25
CALLS={4:0x0040FA30,28:0x0040FAC0,38:0x0040FA30}
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'

def need(value,message):
    if not value:raise ValueError(message)

def load(tag,path):
    spec=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(spec is not None and spec.loader is not None,
         'missing original target-backed source helper '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[tag]=module
    spec.loader.exec_module(module)
    return module

def construct_source(f812):
    src=f812.native_source()  # Regenerates selected F614 original parent, not an old object.
    inc=(ROOT/'probes/FighterScriptedBounce59F813.inc').read_text()
    need('case 0x59:' in inc and 'S16(0x62)==3' in inc
         and 'SetAuxActionAt40FB40(3)' in inc
         and 'S16(0x62)>1' not in inc,
         'real original actor-specific action59 source stage and aux calls changed')
    mark='        case 0x59: g_FighterProbeMarker = 90; break;'
    need(src.count(mark)==1,'target parent does not contain one 0x59 placeholder')
    decl=('extern float g_F728_RandomOffsetYAt00657858;\n'
          'extern float g_F747_BounceXAt006590BC;\n'
          'extern float g_F747_BounceYAt00658044;\n')
    return decl+src.replace(mark,'#include "FighterScriptedBounce59F813.inc"',1)

def compile_source(text):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss005214B0-F813-stage3-bounce.cpp'
    obj=OUT/'Boss005214B0-F813-stage3-bounce.obj'
    cpp.write_text(text)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                 cwd=ROOT,env=env,text=True,capture_output=True,timeout=230)
    (OUT/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'F813 entire actual 46KB original source fails VC7.1 build '+(p.stdout+p.stderr)[-750:])
    return obj

def main():
    rd=load('f813_reader','scripts/compare-coff-function.py')
    f812=load('f813_f812','scripts/verify-scripted-fighter-ten-burst-shared-f812.py')
    f614=load('f813_f614','scripts/verify-fighter-trajectory-burst-f614.py')
    f613=load('f813_f613','scripts/verify-fighter-trajectory-recovery-f613.py')
    f610=load('f813_f610','scripts/verify-fighter-trajectory-bounce-f610.py')
    f607=load('f813_f607','scripts/verify-fighter-trajectory-landing-f607.py')
    f605=load('f813_f605','scripts/verify-fighter-trajectory-followups-f605.py')
    f602=load('f813_f602','scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f813_f600','scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f813_f598','scripts/verify-fighter-singleton-contact-f598.py')
    f603=load('f813_f603','scripts/verify-fighter-trajectory-spawn-f603.py')
    f606=load('f813_f606','scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f608=load('f813_f608','scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f611=load('f813_f611','scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    core=load('f813_core','scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f813_zero','scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f813_switch','scripts/verify-fighter-natural-switch-probes.py')
    actions=load('f813_actions','scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need(boss['size']==46755 and boss['postret_size']==901,
         'native original whole function or afterRET table size changed')
    report,mapped=actions.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    need(by[0x59]==0x0052327A and by[0x5D]==0x005233DE,
         'actual native action59/5D PE packed pointers changed')
    original=rd.pe_bytes_at(pe,by[0x59],by[0x5D]-by[0x59])
    native=list(d.disasm(original,by[0x59]))
    need(len(original)==356 and len(native)==95 and
         native[2].mnemonic=='cmp' and native[2].op_str.endswith(', 3')
         and native[3].mnemonic=='jne' and native[-1].mnemonic=='jmp',
         'actual original native case59 control/whole x86 bounds differ')
    cpp=construct_source(f812)
    obj=compile_source(cpp)
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need(ret==9636 and len(ins)==2432 and len(code)-ret==901,
         'real action59 whole C++ parent compiler CODE/DATA geometry changed')
    prior58,meta58=f614.native_case(rd,pe,d,boss,by)
    preserved=f614.compare_candidate(rd,pe,d,f598,f600,f602,f603,f605,f606,
                  f607,f608,f610,f611,f613,core,zero,switch,boss,report,mapped,
                  code,refs,prior58,meta58)
    need(preserved['previous_29_original_case_bodies_strict_in_same_OBJ']
         and preserved['new_original_native_x86_roles']==135
         and preserved['genuine_original_PE_COFF_fields']==17,
         'prior 30 original game cases and 901B packed DATA not all reverified')
    table=boss['tables'][1]
    slotstart,slotend=18,19
    native_ptr=[int.from_bytes(rd.pe_bytes_at(pe,table['dense_addr']+4*k,4),'little')
                for k in (slotstart,slotend)]
    need(native_ptr==[by[0x59],by[0x5D]]
         and rd.pe_bytes_at(pe,table['map_addr'],table['map_length'])[0x59-0x33]==18,
         'source action59 boundaries not genuine packed original targets')
    original_slots=[r['local_symbol_offset'] for k in (slotstart,slotend)
         for r in refs if r['offset']==ret+44+4*k]
    need(len(original_slots)==2,'source packed jump-table slot relocation missing')
    start,end=original_slots
    generated=list(d.disasm(code[start:end],start))
    need(end-start==356 and len(generated)==95
         and all(a.mnemonic==b.mnemonic and a.size==b.size
                 for a,b in zip(native,generated)),
         'source actual game case59 not original complete 356B/95-x86 opcode geometry')
    fields=[r for r in refs if start<=r['offset']<end]
    need(len(fields)==16,'true original action59 16 typed PE fields incomplete')
    mask=set()
    physical=[]
    for field in fields:
        k=field['offset']-start
        absolute=by[0x59]+k
        need(0<=k<=356-4 and
             field['type'] in ('DIR32','REL32') and
             field['addend']==0 and field['local_symbol_offset'] is None,
             'real original action59 relocation type/addend/lifetime invalid')
        native_dest=(int.from_bytes(original[k:k+4],'little')
            if field['type']=='DIR32' else
            absolute+4+int.from_bytes(original[k:k+4],'little',signed=True))
        hit=re.search(r'At([0-9A-Fa-f]{6,8})',field['symbol'])
        expected=(int(hit.group(1),16) if hit else
                  0x006406AC if field['symbol']=='__ftol2' else None)
        need(expected is not None and native_dest==expected,
             'original case59 native PE and compiler typed source field mismatch '+str(field))
        mask.update(range(k,k+4))
        physical.append((hex(k),field['type'],hex(native_dest)))
    nonfield=[k for k in range(356) if k not in mask and original[k]!=code[start+k]]
    # This source is a natural native-equivalent action, not an x86
    # register-forced fragment. The copied game semantics preserve
    # full original opcode/size, but real context register/EBP bytes
    # remain unmasked and are accurately reported, not accepted.
    need(len(nonfield)>0 and len(mask)==64,
         'unexpectedly original action59 strict byte exact; audit and consider formal whole review')
    tail=rd.pe_bytes_at(pe,SUFFIX,46)
    tailref=[r for r in refs if ret-46<=r['offset']<ret]
    need(len(tailref)==3 and
         {r['offset']-(ret-46) for r in tailref}==set(CALLS),
         'authentic 46B F806 shared default PE fields disappeared')
    tailmask=set()
    for r in tailref:
        off=r['offset']-(ret-46)
        dest=SUFFIX+off+4+int.from_bytes(tail[off:off+4],'little',signed=True)
        need(dest==CALLS[off] and r['type']=='REL32' and r['addend']==0
             and r['local_symbol_offset'] is None
             and f'At{dest:06X}' in r['symbol'],
             'real original default physical PE call identity wrong')
        tailmask.update(range(off,off+4))
    actual_wrong=[k for k in range(46) if k not in tailmask and
                  tail[k]!=code[ret-46+k]]
    need(len(actual_wrong) in (4,8) and
         all(k in (2,10,12,13,16,19,26,36) for k in actual_wrong),
         'full updated parent original default GPR/EBP phase drifted '+str(actual_wrong))
    native_tail=list(d.disasm(tail,SUFFIX))
    source_tail=[x for x in ins if x.address>=ret-46]
    need(len(native_tail)==len(source_tail)==16 and
         all(a.mnemonic==b.mnemonic and a.size==b.size and
             a.address-SUFFIX==b.address-(ret-46)
             for a,b in zip(native_tail,source_tail)),
         'F813 original shared default 46B/16-x86 control/width changed')
    real_native=list(d.disasm(rd.pe_bytes_at(pe,ADDR,boss['size']),ADDR))
    native_xrefs=[x for x in real_native
                  if x.mnemonic=='jmp' and x.op_str=='0x52cb47']
    need(tuple(x.address for x in native_xrefs)==(
         0x00521709,0x00521891,0x00521974,0x00521983),
         'genuine early four native shared getter xrefs changed')
    src_xrefs=[x for x in ins if x.mnemonic=='jmp' and x.op_str==hex(ret-12)]
    need(len(src_xrefs)==4 and all(x.size==5 for x in src_xrefs),
         'new 0x59 parent has wrong count of true native early getter jumps')
    first=boss['tables'][0]
    for action in (0,2,4,5):
        orig_st=int.from_bytes(rd.pe_bytes_at(pe,first['dense_addr']+4*action,4),'little')
        orig_end=int.from_bytes(rd.pe_bytes_at(pe,first['dense_addr']+4*(action+1),4),'little')
        source_st=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+4*action)
        source_end=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+4*(action+1))
        phys=[x for x in native_xrefs if orig_st<=x.address<orig_end]
        generated_jumps=[x for x in src_xrefs if source_st<=x.address<source_end]
        need(len(phys)==len(generated_jumps)==1 and
             phys[0].address-orig_st==generated_jumps[0].address-source_st,
             'F813 original early action relative native getter jump differs '+str(action))
    record={'original_game_whole':'0x005214B0',
        'true_original_whole_CODE_B':46755,
        'current_generated_whole_callable_CODE_B':ret,
        'new_original_full_action':'0x59',
        'original_action_native_complete_B':356,
        'original_action_native_x86':95,
        'original_and_source_action_mnemonics_and_widths_equal':True,
        'original_16_typed_PE_COFF_fields':physical,
        'real_original_nonrelocation_case59_byte_mismatches':len(nonfield),
        'real_original_nonrelocation_case59_wrong_offsets':nonfield[:30],
        'previous_30_real_action_bodies_verified':True,
        'authentic_complete_afterRET_DATA_B':901,
        'original_shared_tail_46B_real_PE_fields':3,
        'four_genuine_early_shared_getter_JMPs_physically_checked':True,
        'original_shared_tail_wrong_nonrelocation_offsets':actual_wrong,
        'full_original_46755B_game_function_exact':False,
        'new_accepted_whole_callable_CODE_B':0,
        'all_979_unit_cold_replay_run':False}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'verified-summary.json').write_text(json.dumps(record,indent=2)+chr(10))
    print('F813 original 005214B0 native 0x59: ordinary stage==3/action3 C++ complete 356B/95 x86, 16 original typed PE fields; all 30 previously reconstructed native actions and 901B switch DATA preserved in one new 9636B whole parent. Unmasked original GPR/EBP differences remain (case '+str(len(nonfield))+' bytes; tail '+str(actual_wrong)+'). Whole 46755B giant NONEXACT, no callable CODE credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F813 whole source native action59 verification FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
