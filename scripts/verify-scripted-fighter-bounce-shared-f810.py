#!/usr/bin/env python3
"""F810: actual 434B/119-x86 native bounce action0x4A in WHOLE scripted 46KB fighter.

Regenerate F610 selected original 28-action source, revalidate native 0x4A
and all previous 27 real cases, real 901B afterRET packed switch DATA.
Then one whole VC7.1 parent rebuild restores F806 four true early
shared getter jumps and original 46B shared-default. This actual 0x4A
source rotates later native default GPR phase: four GPR and four honest
saved-this EBP bytes remain wrong. No truncated case exact credit.
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
OUT=ROOT/'.analysis/f810-scripted-bounce'
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
             str(ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py'),
             '--boss','0x005214B0']
    OUT.mkdir(parents=True,exist_ok=True)
    run=subprocess.run(command,cwd=ROOT,capture_output=True,text=True,timeout=380)
    (OUT/'f607-prior-original-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'selected original 0x4A native PE proof failed '+(run.stdout+run.stderr)[-800:])
    src=(ROOT/'.analysis/f610-fighter-bounce-source/Boss005214B0-28-real-native-game-actions.cpp').read_text()
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
    cpp=OUT/'Boss005214B0-31real-default.cpp'
    obj=OUT/'Boss005214B0-31real-default.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    cmd=[str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes']
    proc=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True,timeout=260)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'natural 27 action+shared tail entire VC7.1 source failed '+(proc.stdout+proc.stderr)[-700:])
    return obj

def main():
    rd=load('f810_reader','scripts/compare-coff-function.py')
    f610=load('f810_f610','scripts/verify-fighter-trajectory-bounce-f610.py')
    f607=load('f810_f607','scripts/verify-fighter-trajectory-landing-f607.py')
    f605=load('f810_f605','scripts/verify-fighter-trajectory-followups-f605.py')
    f602=load('f810_f602','scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f810_f600','scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f810_f598','scripts/verify-fighter-singleton-contact-f598.py')
    core=load('f810_core','scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f810_zero','scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f810_switch','scripts/verify-fighter-natural-switch-probes.py')
    actions=load('f810_actions','scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ADDR)
    need(boss['size']==46755 and boss['postret_size']==901
         and boss['instructions']==13230,'whole original game target changed')
    report,mapped=actions.report_boss(rd,pe,d,boss)
    indexed={x['action']:int(x['handler'],16) for x in mapped}
    original4a,meta4a=f610.original_case(rd,pe,d,boss,indexed)
    src=native_source()
    obj=compile_full(src)
    code,refs=rd.object_function(obj,SYM)
    instructions=[]
    for i in d.disasm(code,0):
        instructions.append(i)
        if i.mnemonic=='ret':break
    ret=instructions[-1].address+instructions[-1].size
    need((ret,len(instructions),len(code)-ret)==(8571,2134,901),
         'selected full source 28 actions+real default native geometry drifted')
    earlier=f610.case_in_giant(rd,pe,d,f598,f602,f605,f607,f600,core,zero,switch,
                    boss,report,mapped,code,refs,original4a,meta4a)
    need(earlier['prior_27_real_original_cases_retained']
         and earlier['complete_new_original_x86_roles']==119
         and earlier['new_original_internal_CODE_bytes_uncredited']==434
         and earlier['native_typed_COFF_fields_exact_positions_and_destinations']==19,
         'original game 28th action 0x4A/19 physical fields not reproduced')
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
    current_gpr=[10,12,16,19]
    need(differences==[2,10,12,13,16,19,26,36]
         and all(authentic[x]==0xF0 and emitted[x]==0xFC for x in honest_ebp),
         'integrated 0x4A source did not reproduce genuine default GPR and EBP negatives '+str(differences))
    phase=[
      ('movsx','edx, ax','eax, ax'),
      ('mov','eax, dword ptr [ebp - 0x10]','ecx, dword ptr [ebp - 4]'),
      ('movsx','ecx, word ptr [eax + 0x70]','edx, word ptr [ecx + 0x70]'),
      ('cmp','edx, ecx','eax, edx')]
    need([(native_tail[k].mnemonic,native_tail[k].op_str,source_tail[k].op_str)
          for k in (2,3,4,5)]==phase,
         'native full 0x4A registers/operands drifted unexpectedly')
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
         'F808_prior_source_callable_CODE_B':8152,
         'F810_new_source_callable_CODE_B':ret,
         'original_case0x4A_bounded_CODE_B':434,
         'native_4A_original_x86':119,
         'native_case4A_real_PE_fields_verified':19,
         'all_27_previous_original_cases_rechecked':True,
         'true_original_full_source_afterRET_DATA_B':901,
         'true_original_dense_jumps_and_sparse_map_rechecked':True,
         'original_complete_shared_getter_native_tail_B':46,
         'original_and_source_shared_tail_x86':16,
         'source_native_tail_fields':targets,
         'native_early_shared_getter_xrefs':[hex(x) for x in XREF],
         'native_and_source_early_case_jump_offsets_equal':True,
         'new_real_0x4A_game_source_changes_default_register_phase':True,
         'four_native_GPR_wrong_offsets':current_gpr,
         'four_native_saved_this_EBP_wrong_offsets':honest_ebp,
         'whole_original_giant_exact':False,
         'authored_callable_exact_CODE_B_delta':0,
         'full_cold_unit_replay_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(out,indent=2)+chr(10))
    print('F810 original 005214B0 action 0x4A full 434B/119-x86/19 native-PE-field bounce in one 28-action C++ parent. Source CODE 8152->8571 B, x86 2017->2134; all 27 earlier native cases, 901B switch DATA, 46B shared suffix and four genuine xrefs reverified. Actual preceding 0x4A rotates default GPR phase again (4 GPR +4 EBP bytes wrong). Giant 46755B remains nonexact; zero accepted game CODE.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as ex:
        print('F810 whole original scripted fighter PE/source comparison FAILED:',ex,file=sys.stderr)
        raise SystemExit(1)
