#!/usr/bin/env python3
"""F812: native original 0x58 ten-projectile burst in WHOLE 46KB scripted giant.

Regenerate selected 30-game-action F614 parent, physically verify previous
29 original cases and new 469B/135-x86 native action0x58 with 17 real
PE/COFF fields. One full pinned VC7.1 parent then includes F806 four
original shared-getter early exit JMPs and 46B native fallback,
rechecking 901B afterRET DATA. True ten-shot loop introduces genuine
EBP-8 loop counter and changes saved-this frame from EBP-4 to EBP-8;
default GPRs naturally align with original again. Four honest saved
receiver EBP bytes remain unequal to actual native EBP-0x10.
Whole 46,755B original is still nonexact, no subcase CODE credit.
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
OUT=ROOT/'.analysis/f812-scripted-burst'
ADDR=0x005214B0
ORIGINAL_TAIL=0x0052CB25
ORIGINAL_GETTER=0x0052CB47
SUFFIX_SIZE=46
XREF=(0x00521709,0x00521891,0x00521974,0x00521983)
TARGET_CALLS={4:0x0040FA30,28:0x0040FAC0,38:0x0040FA30}
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'

def need(v,message):
    if not v:raise ValueError(message)

def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,
         'native original PE-backed source tool missing: '+str(path))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m

def native_source():
    # Rebuild and PHYSICALLY VERIFY the selected prior 27-action whole
    # parent before deriving anything from its ignored generated file.
    command=[str(ROOT/'scripts/repo-python'),
             str(ROOT/'scripts/verify-fighter-trajectory-burst-f614.py'),
             '--boss','0x005214B0']
    OUT.mkdir(parents=True,exist_ok=True)
    run=subprocess.run(command,cwd=ROOT,capture_output=True,text=True,timeout=380)
    (OUT/'f614-prior-original-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'selected original 0x58 native PE proof failed '+(run.stdout+run.stderr)[-800:])
    src=(ROOT/'.analysis/f614-fighter-burst-source/Boss005214B0-30-real-game-actions.cpp').read_text()
    for a,b in ((0,1),(2,3)):
        begin=f'        case 0x{a:X}:'
        nextcase=f'        case 0x{b:X}:'
        first=src.index(begin)
        last=src.index(nextcase,first+len(begin))
        body=src[first:last]
        need(body.rstrip().endswith('break;'),
             'original early native case no longer ends in ordinary C++ break')
        src=src[:first]+body[:body.rindex('break;')]+(
                'goto native_script_shared_getter;\n')+src[last:]
    for a,pos in ((4,'3.0f'),(5,'-3.0f')):
        expr=f'case 0x{a:X}: POS = {pos}; break;'
        need(src.count(expr)==1,'native original early 4/5 action changed')
        src=src.replace(expr,f'case 0x{a:X}: POS = {pos}; goto native_script_shared_getter;',1)
    marker='        default: g_FighterProbeMarker = 0;'
    need(src.count(marker)==1,'expected old diagnostic default absent')
    src=src.replace(marker,'#include "FighterScriptedNativeDefaultF806.inc"',1)
    tail='    }\n}\n#undef OWNER'
    need(src.count(tail)==1,'complete script switch source tail moved')
    src=src.replace(tail,'    }\n#include "FighterScriptedSharedGetterF806.inc"\n}\n#undef OWNER',1)
    need(src.count('goto native_script_shared_getter;')==4,
         'native shared tail must have precisely four early natural JMP sources')
    return src

def compile_full(src):
    cpp=OUT/'Boss005214B0-33real-default.cpp'
    obj=OUT/'Boss005214B0-33real-default.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    cmd=[str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes']
    proc=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True,timeout=260)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'natural 30 action+shared tail entire VC7.1 source failed '+(proc.stdout+proc.stderr)[-700:])
    return obj

def main():
    rd=load('f812_reader','scripts/compare-coff-function.py')
    f614=load('f812_f614','scripts/verify-fighter-trajectory-burst-f614.py')
    f613=load('f812_f613','scripts/verify-fighter-trajectory-recovery-f613.py')
    f610=load('f812_f610','scripts/verify-fighter-trajectory-bounce-f610.py')
    f607=load('f812_f607','scripts/verify-fighter-trajectory-landing-f607.py')
    f605=load('f812_f605','scripts/verify-fighter-trajectory-followups-f605.py')
    f602=load('f812_f602','scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f812_f603','scripts/verify-fighter-trajectory-spawn-f603.py')
    f606=load('f812_f606','scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f608=load('f812_f608','scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f611=load('f812_f611','scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f600=load('f812_f600','scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f812_f598','scripts/verify-fighter-singleton-contact-f598.py')
    core=load('f812_core','scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f812_zero','scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f812_switch','scripts/verify-fighter-natural-switch-probes.py')
    actions=load('f812_actions','scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ADDR)
    need(boss['size']==46755 and boss['postret_size']==901
         and boss['instructions']==13230,'whole original game target changed')
    report,mapped=actions.report_boss(rd,pe,d,boss)
    indexed={x['action']:int(x['handler'],16) for x in mapped}
    original58,meta58=f614.native_case(rd,pe,d,boss,indexed)
    src=native_source()
    obj=compile_full(src)
    code,refs=rd.object_function(obj,SYM)
    instructions=[]
    for i in d.disasm(code,0):
        instructions.append(i)
        if i.mnemonic=='ret':break
    ret=instructions[-1].address+instructions[-1].size
    need((ret,len(instructions),len(code)-ret)==(9295,2339,901),
         'selected full source 30 native actions+F806 real shared default geometry drifted')
    earlier=f614.compare_candidate(rd,pe,d,f598,f600,f602,f603,f605,f606,
                    f607,f608,f610,f611,f613,core,zero,switch,boss,report,mapped,code,refs,original58,meta58)
    need(earlier['previous_29_original_case_bodies_strict_in_same_OBJ']
         and earlier['new_original_native_x86_roles']==135
         and earlier['new_original_native_internal_CODE_bytes_uncredited']==469
         and earlier['genuine_original_PE_COFF_fields']==17,
         'original game 30th action 0x58/17 physical fields not reproduced')
    source_tail=[x for x in instructions if x.address>=ret-SUFFIX_SIZE]
    native_full=list(d.disasm(rd.pe_bytes_at(pe,ADDR,boss['size']),ADDR))
    native_tail=[x for x in native_full if x.address>=ORIGINAL_TAIL]
    need(len(source_tail)==len(native_tail)==16 and
         all(a.mnemonic==b.mnemonic and a.size==b.size and
             a.address-ORIGINAL_TAIL==b.address-(ret-SUFFIX_SIZE)
             for a,b in zip(native_tail,source_tail)),
         'entire native real 46-B shared tail opcode geometry or offset differs')
    authentic=rd.pe_bytes_at(pe,ORIGINAL_TAIL,SUFFIX_SIZE)
    emitted=code[ret-SUFFIX_SIZE:ret]
    rel=[r for r in refs if ret-SUFFIX_SIZE<=r['offset']<ret]
    need(len(rel)==3 and {r['offset']-(ret-SUFFIX_SIZE) for r in rel}==set(TARGET_CALLS),
         'original native shared getter three physical PE call offsets changed')
    masks=set()
    targets=[]
    for r in rel:
        at=r['offset']-(ret-SUFFIX_SIZE)
        original_target=ORIGINAL_TAIL+at+4+int.from_bytes(authentic[at:at+4],'little',signed=True)
        need(r['type']=='REL32' and r['addend']==0
             and r['local_symbol_offset'] is None
             and original_target==TARGET_CALLS[at]
             and f'At{original_target:06X}' in r['symbol'],
             'original independent source PE call destination differs '+str(r))
        masks.update(range(at,at+4))
        targets.append(original_target)
    differences=[j for j in range(SUFFIX_SIZE) if j not in masks and authentic[j]!=emitted[j]]
    honest_ebp=[2,13,26,36]
    current_gpr=[]
    need(differences==honest_ebp
         and all(authentic[x]==0xF0 and emitted[x]==0xF8 for x in honest_ebp),
         'true 0x58 ten-burst source did not restore native default GPR and EBP-8 source frame '+str(differences))
    # The native original default registers are now *all* exact
    # under the new real burst game source, with only the physical
    # full-parent frame-size difference accounted for. Never
    # normalize GPRs or invent fake source locals.
    for j in (2,3,4,5):
        target,source=native_tail[j],source_tail[j]
        operand=target.op_str.replace('[ebp - 0x10]','[ebp - 8]')
        need(target.mnemonic==source.mnemonic and operand==source.op_str,
             'new native source ten-burst loop did not restore original default GPR phases')
    jumps=[x for x in native_full if x.mnemonic=='jmp' and x.op_str=='0x52cb47']
    need(tuple(x.address for x in jumps)==XREF,'physical original shared getter xref set is not real')
    source_jump=[x for x in instructions if x.mnemonic=='jmp' and x.op_str==hex(ret-12)]
    need(len(source_jump)==4 and all(x.size==5 for x in source_jump),
         'new source shared getter has additional or missing early entry paths')
    table=boss['tables'][0]
    ncase=[int.from_bytes(rd.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
           for i in range(11)]
    scase=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+4*i)
           for i in range(11)]
    for case in (0,2,4,5):
        a,b=ncase[case:case+2]
        u,v=scase[case:case+2]
        nj=[x for x in jumps if a<=x.address<b]
        sj=[x for x in source_jump if u<=x.address<v]
        need(len(nj)==len(sj)==1 and nj[0].address-a==sj[0].address-u,
             'real early action branch differs from original physical case position '+str(case))
    out={'original_game_boss':'0x005214B0',
         'actual_original_callable_CODE_B':46755,
         'F811_prior_source_callable_CODE_B':8841,
         'F812_new_source_callable_CODE_B':ret,
         'original_case0x58_bounded_CODE_B':469,
         'native_58_original_x86':135,
         'native_case58_real_PE_fields_verified':17,
         'all_29_previous_original_cases_rechecked':True,
         'true_original_full_source_afterRET_DATA_B':901,
         'true_original_dense_jumps_and_sparse_map_rechecked':True,
         'original_complete_shared_getter_native_tail_B':46,
         'original_and_source_shared_tail_x86':16,
         'source_native_tail_fields':targets,
         'native_early_shared_getter_xrefs':[hex(x) for x in XREF],
         'native_and_source_early_case_jump_offsets_equal':True,
         'new_real_0x58_ten_projectile_loop_restores_default_GPR_phase':True,
         'remaining_original_default_tail_GPR_wrong_offsets':current_gpr,
         'remaining_native_saved_this_EBP8_vs_EBP10_wrong_offsets':honest_ebp,
         'whole_original_giant_exact':False,
         'authored_callable_exact_CODE_B_delta':0,
         'full_cold_unit_replay_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(out,indent=2)+chr(10))
    print('F812 whole 005214B0 native 0x58 ten-burst game case: 469B/135-x86/17 authentic original PE fields, previous 29 native cases and 901B jump table checked. Source CODE 8841->9295 B, x86 2206->2339. Real ten-shot loop introduces native-sized EBP-8 frame, naturally restores ALL original default GPRs; only four honest EBP-8 vs native EBP-0x10 nonfield bytes remain in 46B tail. Original 46755B entire boss NONEXACT; no accepted callable CODE.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as ex:
        print('F812 whole original scripted fighter PE/source comparison FAILED:',ex,file=sys.stderr)
        raise SystemExit(1)
