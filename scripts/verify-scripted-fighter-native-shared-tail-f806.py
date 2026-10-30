#!/usr/bin/env python3
"""F806: recover 46B original shared tail in WHOLE 005214B0 46KB boss.

Regenerate the *tracked* F600 original first 23 cases for THIS
specific original target and verify them before extending. Four real
early case 0/2/4/5 JMPs now enter real 8-B getter at 0052CB47.
Full native fallback 0052CB25 has 32B/10 x86 and two authentic
PE calls; complete 46B/16 original x86 suffix matches current
generated source modulo *only* source's missing deep saved-ECX
lifetime (EBP-4 vs native EBP-0x10). Three real COFF fields
and original-afterRET switch DATA physical bindings are proved.
The enclosing 46755B giant is NOT exact, never credit 46B
as separate callable CODE. No all-unit cold replay.
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
OUT=ROOT/'.analysis/f806-scripted-default'
ADDR=0x005214B0
SUFFIX=0x0052CB25
GETTER=0x0052CB47
EPILOGUE=0x0052CB4F
TAIL_LENGTH=46
EARLY=(0,2,4,5)
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
XREF=(0x00521709,0x00521891,0x00521974,0x00521983)
CALLS={4:0x0040FA30,28:0x0040FAC0,38:0x0040FA30}

def need(p,s):
    if not p:raise ValueError(s)

def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing source verifier '+str(path))
    obj=importlib.util.module_from_spec(sp)
    sys.modules[tag]=obj
    sp.loader.exec_module(obj)
    return obj

def reconstruct_source():
    # This cold targeted run uses only original selected boss plus
    # the prior tracked generator: no unknown stale .analysis file.
    run=subprocess.run([str(ROOT/'scripts/repo-python'),
        str(ROOT/'scripts/verify-fighter-additional-contact-f600.py'),
        '--boss','0x005214B0'],cwd=ROOT,capture_output=True,text=True,
        timeout=300)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'f600-prior-boss-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'F600 selected previous 23-case complete native source failed '+(run.stdout+run.stderr)[-700:])
    path=ROOT/'.analysis/f600-fighter-contact-source/Boss005214B0-23-real-original-cases.cpp'
    src=path.read_text()
    for i,j in ((0,1),(2,3)):
        begin=f'        case 0x{i:X}:'
        later=f'        case 0x{j:X}:'
        a=src.index(begin);b=src.index(later,a+len(begin))
        fragment=src[a:b]
        need(fragment.rstrip().endswith('break;'),
             'original early native case no longer ends in correct normal goto site')
        src=src[:a]+fragment[:fragment.rindex('break;')]+ 'goto native_script_shared_getter;\n'+src[b:]
    for i,value in ((4,'3.0f'),(5,'-3.0f')):
        old=f'case 0x{i:X}: POS = {value}; break;'
        need(src.count(old)==1,'native early C++ position case changed '+str(i))
        src=src.replace(old,f'case 0x{i:X}: POS = {value}; goto native_script_shared_getter;',1)
    fallback='        default: g_FighterProbeMarker = 0;'
    need(src.count(fallback)==1,'native previous artificial default not visible')
    src=src.replace(fallback,'#include "FighterScriptedNativeDefaultF806.inc"',1)
    anchor='    }\n}\n#undef OWNER'
    need(src.count(anchor)==1,'whole original C++ switch/epilogue changed')
    src=src.replace(anchor,'    }\n#include "FighterScriptedSharedGetterF806.inc"\n}\n#undef OWNER',1)
    need(src.count('goto native_script_shared_getter;')==4,'real four early source transfers missing')
    return src

def compile_one(src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss005214B0-F806-full.cpp'
    obj=OUT/'Boss005214B0-F806-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,capture_output=True,text=True,env=env,timeout=260)
    (OUT/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'original entire scripted parent did not compile '+(run.stdout+run.stderr)[-700:])
    return obj

def main():
    rd=load('f806_rd','scripts/compare-coff-function.py')
    actions=load('f806_actions','scripts/report-fighter-action-handlers.py')
    f600=load('f806_f600','scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f806_f598','scripts/verify-fighter-singleton-contact-f598.py')
    core=load('f806_core','scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f806_zero','scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f806_switch','scripts/verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need(boss['size']==46755 and boss['postret_size']==901,'original complete scripted fighter code/table bounds changed')
    native=rd.pe_bytes_at(pe,ADDR,boss['size'])
    original=list(d.disasm(native,ADDR))
    report,mapped=actions.report_boss(rd,pe,d,boss)
    need(int(report['default'],16)==SUFFIX,'original real native 005214B0 default handler changed')
    native_jumps=[i for i in original if i.mnemonic=='jmp' and i.op_str==hex(GETTER)]
    need(tuple(i.address for i in native_jumps)==XREF,'native original shared getter is not reached from exact four early actions')
    src=reconstruct_source()
    obj=compile_one(src)
    code,refs=rd.object_function(obj,SYM)
    instructions=[]
    for i in d.disasm(code,0):
        instructions.append(i)
        if i.mnemonic=='ret':break
    ret=instructions[-1].address+instructions[-1].size
    need((ret,len(instructions),len(code)-ret)==(6868,1650,901),
         'new whole 46KB source intermediate CODE geometry drifted (still not full native function)')
    earlier=f600.compare_candidate(rd,pe,d,f598,core,zero,switch,boss,report,mapped,code,refs)
    need(earlier['additional_native_case_x86_roles']==701
         and earlier['additional_physical_typed_COFF_refs']==80
         and earlier['full_original_postRET_literal_sparse_bytes']==345
         and earlier['full_original_postRET_typed_dense_DWORD_fields']==139,
         'previous 23 original entire action cases or original packed switch DATA changed')
    n_tail=[i for i in original if i.address>=SUFFIX]
    s_tail=[i for i in instructions if i.address>=ret-TAIL_LENGTH]
    need(len(n_tail)==len(s_tail)==16 and n_tail[0].address==SUFFIX
         and n_tail[-1].address+n_tail[-1].size==ADDR+boss['size'],
         'native complete original 46B shared tail not bounded correctly')
    need(all(a.size==b.size and a.mnemonic==b.mnemonic
             and a.address-SUFFIX==b.address-(ret-TAIL_LENGTH)
             for a,b in zip(n_tail,s_tail)),
         'VC7.1 source does not recreate full real 46B/16 x86 tail offsets/opcodes')
    native_bytes=rd.pe_bytes_at(pe,SUFFIX,TAIL_LENGTH)
    generated_bytes=code[ret-TAIL_LENGTH:ret]
    fields=[r for r in refs if ret-TAIL_LENGTH<=r['offset']<ret]
    need(len(fields)==3 and {r['offset']-(ret-TAIL_LENGTH) for r in fields}==set(CALLS),
         'missing one of the three actual native 46B original PE calls')
    mask=set()
    for r in fields:
        k=r['offset']-(ret-TAIL_LENGTH)
        actual=SUFFIX+k+4+int.from_bytes(native_bytes[k:k+4],'little',signed=True)
        need(r['type']=='REL32' and r['local_symbol_offset'] is None
             and r['addend']==0 and actual==CALLS[k]
             and f'At{actual:06X}' in r['symbol'],
             'real PE/COFF source tail call identity or addend mismatch '+str(r))
        mask.update(range(k,k+4))
    bad=[k for k in range(TAIL_LENGTH) if k not in mask
         and native_bytes[k]!=generated_bytes[k]]
    need(bad==[2,13,26,36],
         'native complete 46B original tail has unexpected unmasked differences '+str(bad))
    need(all(native_bytes[k]==0xF0 and generated_bytes[k]==0xFC for k in bad),
         'only allowed negative is original genuine EBP-0x10 vs source EBP-4 saved receiver displacement')
    getter_src=ret-12
    early_source=[i for i in instructions if i.mnemonic=='jmp'
                  and i.op_str==hex(getter_src)]
    need(len(early_source)==4 and len(set(i.address for i in early_source))==4
         and all(i.size==5 for i in early_source),
         'source shared getter reached by more or fewer than genuine early action paths')
    table=boss['tables'][0]
    ncases=[int.from_bytes(rd.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
            for i in range(11)]
    scases=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+4*i)
            for i in range(11)]
    for case,jump in zip(EARLY,early_source):
        nlo,nhi=ncases[case:case+2]
        slo,shi=scases[case:case+2]
        original_inside=[x for x in native_jumps if nlo<=x.address<nhi]
        source_inside=[x for x in early_source if slo<=x.address<shi]
        need(len(original_inside)==len(source_inside)==1 and
             original_inside[0].address-nlo==source_inside[0].address-slo,
             f'0x{case:x} original game case exit does not land at real shared getter at the same case offset')
    out={'original_giant':'0x005214B0',
         'original_whole_callable_CODE_B':46755,
         'source_whole_callable_CODE_B':ret,
         'original_separate_afterRET_jump_DATA_B':901,
         'genuine_first_23_native_actions_reverified':True,
         'genuine_physical_case_COFF_fields_in_11_followups':80,
         'genuine_packed_original_tables_dense_DWORD':139,
         'genuine_packed_original_tables_sparse_bytes':345,
         'native_shared_default':'0x0052CB25',
         'native_exact_tail_extent_B':46,
         'native_and_compiled_tail_x86':16,
         'original_tail_getter':'0x0052CB47',
         'original_four_early_entry_jumps':[hex(x) for x in XREF],
         'compiled_four_source_relative_jumps':[hex(x.address) for x in early_source],
         'source_branch_offsets_match_all_native_four_early_case_boundaries':True,
         'tail_three_true_physically_attested_relocations':[hex(CALLS[k]) for k in sorted(CALLS)],
         'tail_only_four_remaining_original_saved_this_EBP_byte_differences':bad,
         'source_original_EBP_receiver_slot_gap':'native EBP-0x10 vs intermediate source EBP-4',
         'whole_giant_exact':False,'accepted_game_callable_exact_CODE':0,
         'all_unit_cold_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(out,indent=2)+chr(10))
    print('F806 native 005214B0: full 46B/16-x86 default+shared getter restored; original four 0/2/4/5 JMP positions, three PE call fields true; ONLY four saved-this EBP displacement negatives in tail. Previous 23 entire native actions and 901B DATA verified. Whole 46755B boss still NONEXACT; no credited CODE.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F806 original 46KB scripted giant full-source validation FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
