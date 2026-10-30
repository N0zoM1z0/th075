#!/usr/bin/env python3
"""F807: 46KB native scripted fighter 26 complete cases PLUS real F806 tail.

Targeted F605 rebuild of original selected 005214B0, preserving
all 23 real prior cases, 104 native x86/complete original 0x46,
two 86-x86 original 0x47/48 native cases with all 26 typed PE
fields, and entire 901B postRET packed switch DATA. Then
add F806 four early JMPs, true 46B fallback/getter suffix in
same WHOLE source parent. Verify genuine original PE targets
and real context-induced GPR plus EBP displacement negatives. Still not whole
46755B exact, no case-level exact credit and no cold replay
of unchanged 979 accepted functions.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f807-scripted-extended'
ADDR=0x005214B0
TAIL=0x0052CB25
SUFFIX_BYTES=46
GETTER=0x0052CB47
REAL_XREF=(0x00521709,0x00521891,0x00521974,0x00521983)
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
CALLS={4:0x0040FA30,28:0x0040FAC0,38:0x0040FA30}

def need(p,s):
    if not p:raise ValueError(s)

def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing physical original source helper '+str(path))
    mod=importlib.util.module_from_spec(sp)
    sys.modules[tag]=mod
    sp.loader.exec_module(mod)
    return mod

def generated_prior_source():
    # F605 uses all earlier original-backed tracked generators,
    # and verifies all 26 native action extents/calls itself. This
    # explicitly regenerates and does not trust stale .analysis files.
    cmd=[str(ROOT/'scripts/repo-python'),
         str(ROOT/'scripts/verify-fighter-trajectory-followups-f605.py'),
         '--boss','0x005214B0']
    run=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,timeout=360)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'f605-targeted-prior-whole-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'selected 26 original native action generator failed '+(run.stdout+run.stderr)[-850:])
    path=ROOT/'.analysis/f605-trajectory-source/Boss005214B0-26-real-original-actions.cpp'
    src=path.read_text()
    for case in (0,2):
        start=f'        case 0x{case:X}:'
        after=f'        case 0x{case+1:X}:'
        a=src.index(start);b=src.index(after,a+len(start))
        original_case=src[a:b]
        need(original_case.rstrip().endswith('break;'),
             'real early shared source action no longer has one outer case break')
        src=src[:a]+original_case[:original_case.rindex('break;')]+(
            'goto native_script_shared_getter;\n')+src[b:]
    for case,value in ((4,'3.0f'),(5,'-3.0f')):
        old=f'case 0x{case:X}: POS = {value}; break;'
        need(src.count(old)==1,'real native early one-statement action changed')
        src=src.replace(old,f'case 0x{case:X}: POS = {value}; goto native_script_shared_getter;',1)
    old='        default: g_FighterProbeMarker = 0;'
    need(src.count(old)==1,'previous whole source fallback is no longer the tested marker')
    src=src.replace(old,'#include "FighterScriptedNativeDefaultF806.inc"',1)
    old='    }\n}\n#undef OWNER'
    need(src.count(old)==1,'whole original switch/parent end changed')
    src=src.replace(old,'    }\n#include "FighterScriptedSharedGetterF806.inc"\n}\n#undef OWNER',1)
    need(src.count('goto native_script_shared_getter;')==4,
         'only four native early actions may enter real shared getter')
    return src

def compile_one(src):
    cpp=OUT/'Boss005214B0-29real-default.cpp'
    obj=OUT/'Boss005214B0-29real-default.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv= d;winemenubuilder.exe=d'.replace('= d','=d')
    run=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=260)
    (OUT/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'whole new 46KB source build failed '+(run.stdout+run.stderr)[-900:])
    return obj

def main():
    rd=load('f807_reader','scripts/compare-coff-function.py')
    f605=load('f807_f605','scripts/verify-fighter-trajectory-followups-f605.py')
    f602=load('f807_f602','scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f807_f600','scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f807_f598','scripts/verify-fighter-singleton-contact-f598.py')
    core=load('f807_core','scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f807_zero','scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f807_switch','scripts/verify-fighter-natural-switch-probes.py')
    actions=load('f807_actions','scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need(boss['size']==46755 and boss['postret_size']==901 and boss['instructions']==13230,
         'original real 46KB original fighter boundaries changed')
    report,mapped=actions.report_boss(rd,pe,decoder,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    native46,meta46=f602.original_case(rd,pe,decoder,boss,by)
    native_followups={act:f605.original_action(rd,pe,decoder,boss,by,act)
                      for act in (0x47,0x48)}
    source=generated_prior_source()
    obj=compile_one(source)
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for i in decoder.disasm(code,0):
        ins.append(i)
        if i.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret)==(7817,1920,901),
         'new 26-case + native-shared-tail full-parent source geometry drifted')
    previous=f605.check_candidate(rd,pe,decoder,f598,f602,f600,core,zero,switch,
             boss,report,mapped,code,refs,native_followups,meta46)
    need(previous['prior_23_original_source_cases_preserved']
         and previous['prior_action46_roles_preserved']==104
         and previous['added_original_x86_roles']==172
         and previous['added_true_original_typed_COFF_fields']==26,
         'existing real 26 authored native subcases not verified inside new parent')
    # Independent original 46-byte tail relative to *last generated RET*.
    original=rd.pe_bytes_at(pe,TAIL,SUFFIX_BYTES)
    natives=list(decoder.disasm(original,TAIL))
    produced=[x for x in ins if x.address>=ret-SUFFIX_BYTES]
    need(len(natives)==len(produced)==16
         and all(x.mnemonic==y.mnemonic and x.size==y.size and
             x.address-TAIL==y.address-(ret-SUFFIX_BYTES)
             for x,y in zip(natives,produced)),
         'expanded source parent lost original full native 46B/16-x86 default/getter')
    fields=[r for r in refs if ret-SUFFIX_BYTES<=r['offset']<ret]
    need(len(fields)==3 and {r['offset']-(ret-SUFFIX_BYTES) for r in fields}==set(CALLS),
         'three native real PE fallback/getter call relocations disappeared')
    mask=set()
    for ref in fields:
        off=ref['offset']-(ret-SUFFIX_BYTES)
        real=TAIL+off+4+int.from_bytes(original[off:off+4],'little',signed=True)
        need(ref['type']=='REL32' and ref['local_symbol_offset'] is None
             and ref['addend']==0 and real==CALLS[off]
             and f'At{real:06X}' in ref['symbol'],
             'original fallback PE call target or source relocation semantics incorrect')
        mask.update(range(off,off+4))
    diffs=[j for j in range(SUFFIX_BYTES) if j not in mask
           and original[j]!=code[ret-SUFFIX_BYTES+j]]
    expected_ebp=[2,13,26,36]
    expected_gpr=[10,12,16,19]
    need(diffs==[2,10,12,13,16,19,26,36]
         and all(original[x]==0xF0 and code[ret-SUFFIX_BYTES+x]==0xFC
                 for x in expected_ebp),
         'expanded parent has unexpected native EBP/GPR negatives '+str(diffs))
    need([(natives[j].mnemonic,natives[j].op_str,
           produced[j].op_str) for j in (2,3,4,5)]==[
       ('movsx','edx, ax','eax, ax'),
       ('mov','eax, dword ptr [ebp - 0x10]','ecx, dword ptr [ebp - 4]'),
       ('movsx','ecx, word ptr [eax + 0x70]','edx, word ptr [ecx + 0x70]'),
       ('cmp','edx, ecx','eax, edx')],
       'restoring real 0x46/47/48 changed original default GPR cycle unexpectedly')
    native_full=list(decoder.disasm(rd.pe_bytes_at(pe,ADDR,boss['size']),ADDR))
    xref=[x for x in native_full if x.mnemonic=='jmp' and x.op_str=='0x52cb47']
    need(tuple(x.address for x in xref)==REAL_XREF,
         'four genuine native early original branch addresses changed')
    getter=ret-12
    sj=[x for x in ins if x.mnemonic=='jmp' and x.op_str==hex(getter)]
    need(len(sj)==4 and all(x.size==5 for x in sj),
         'expanded source shared getter is not reached via exactly four jumps')
    table=boss['tables'][0]
    origcases=[int.from_bytes(rd.pe_bytes_at(pe,table['dense_addr']+4*j,4),'little') for j in range(11)]
    srccases=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+4*j) for j in range(11)]
    for case in (0,2,4,5):
        nstart,nstop=origcases[case:case+2]
        sstart,sstop=srccases[case:case+2]
        a=[x for x in xref if nstart<=x.address<nstop]
        b=[x for x in sj if sstart<=x.address<sstop]
        need(len(a)==len(b)==1
             and a[0].address-nstart==b[0].address-sstart,
             'source original action %d JMP position differs from real native case'%case)
    result={
        'original_native_46KB_giant':'0x005214B0',
        'original_whole_callable_CODE_B':46755,
        'current_generated_callable_CODE_B':ret,
        'prior_F806_source_callable_CODE_B':6868,
        'original_giant_whole_exact':False,
        'real_original_0x46_x86':104,
        'original_0x47_and_0x48_x86':172,
        'new_source_three_actions_bytes_inside_original':[meta46['original_native_CODE_bytes'],310,310],
        'native_0x47_and_0x48_real_typed_fields':26,
        'first_23_original_native_actions_still_revalidated':True,
        'new_native_46B_suffix_source_complete_except_real_register_and_EBP_negatives':True,
        'native_tail_x86':16,'native_tail_real_PE_relocations':3,
        'four_original_sharing_early_case_entries':[hex(x) for x in REAL_XREF],
        'tail_four_saved_receiver_EBP_byte_negatives':expected_ebp,
        'tail_four_real_native_GPR_byte_negatives':expected_gpr,
        'new_fighter_controlflow_affects_default_GPR_phase':True,
        'real_original_afterRET_switch_DATA_B':901,
        'full_source_postRET_table_revalidated':True,
        'whole_compiled_parent_x86':len(ins),
        'new_accepted_game_whole_CODE_B':0,
        'all_accepted_units_cold_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(result,indent=2)+chr(10))
    print('F807 full 005214B0 source grows F806 6868 -> 7817 callable B, +3 native motion cases 0x46/47/48 (276 real x86 / 3 complete original extents / 26 original PE fields), all 23 previous cases, 46B native shared tail, 901B native jump DATA revalidated. Whole 46755B giant still nonexact; zero split-case credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F807 selected original 46KB scripted giant FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
