#!/usr/bin/env python3
"""F585: five complete original trajectory actions in CharacterObject 004EBDA0.

The original Japanese TH075 v1.11 giant has 33,293 complete CODE bytes;
none is yet an exact whole-function match. This checker freshly compiles
ONE *affected* ordinary VC7.1 C++ TU via the original-backed F583 source
verifier, rechecking all 32 previously restored game-action bodies, and
then independently verifies the physical original PE spans/entire x86
instruction roles and true typed COFF fields for native actions
0x345..0x349. No internal case is a standalone exact function. No
all-unit cold replay or externally accepted Factory/Oracle receipt.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f585-characterobject-five-native-source'
ADDRESS=0x004EBDA0
CASES=(0x345,0x346,0x347,0x348,0x349)
ENDS=(0x346,0x347,0x348,0x349,0x34A)
PREVIOUS=ROOT/'.analysis/f583-characterobject-state-leaves-source'
OBJECT=PREVIOUS/'CharacterObjectF583.obj'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
TYPED={
  0x0040FBB0:('REL32','ResetStateAt40FBB0'),
  0x0045B830:('REL32','ResetAt45B830'),
  0x0040FA30:('REL32','GetStateAt40FA30'),
  0x0040FB40:('REL32','SetStateAt40FB40'),
  0x0040FB70:('REL32','MotionAt40FB70'),
  0x006406AC:('REL32','__ftol2'),
  0x00659248:('DIR32','gBoundRightAt00659248'),
  0x0065930C:('DIR32','gBoundLowerAt0065930C'),
  0x00658E80:('DIR32','gBoundUpperAt00658E80'),
  0x00657CBC:('DIR32','gGrowAt00657CBC'),
  0x0065747C:('DIR32','gCompareAt0065747C'),
  0x0065782C:('DIR32','gCompareAt0065782C'),
}
GEOMETRY={
  0x345:(286,1144,19),0x346:(111,436,7),
  0x347:(286,1136,19),0x348:(289,1153,19),0x349:(111,436,7),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None, f'missing original PE source checker {path}')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def check_native_field(native,candidate,refs,case):
    first,end=candidate[0].address,candidate[-1].address+candidate[-1].size
    actual=[r for r in refs if first<=r['offset']<end]
    observed=[]
    for ordinal,x in enumerate(native):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            kind='REL32'
            destination=int(x.op_str,16)
        elif x.mnemonic.startswith('f') and 'ptr [0x' in x.op_str:
            kind='DIR32'
            destination=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
        else:continue
        need(destination in TYPED,
             f'original game action {case:#x} unknown callee/float address {destination:#x} at {ordinal}')
        dtype,symbol=TYPED[destination]
        need(kind==dtype,
             f'original game action {case:#x} physical native relocation type changed')
        generated=candidate[ordinal]
        need(x.mnemonic==generated.mnemonic,
             f'new normal C++ case {case:#x} original COFF instruction ordinal {ordinal} shifted')
        fields=[r for r in actual if generated.address<=r['offset']<generated.address+generated.size]
        need(len(fields)==1,
             f'physical native COFF field missing at {case:#x}: {ordinal} {fields}')
        r=fields[0]
        need(r['type']==kind and r['addend']==0 and symbol in r['symbol'],
             f'wrong true PE relocation/address/type/source symbol at {case:#x}:{ordinal}: {r}')
        observed.append((ordinal,kind,destination,symbol))
    count,byte_count,fields_expected=GEOMETRY[case]
    need(len(observed)==len(actual)==fields_expected,
         f'new real action {case:#x} has wrong number of physical COFF fields: {len(observed)}/{len(actual)} != {fields_expected}')
    return observed


def original_behavior(native,candidate,case):
    """Compare full source grammar, original native size, and meaningfully different states."""
    count,byte_count,_=GEOMETRY[case]
    need(len(native)==len(candidate)==count and
         sum(x.size for x in native)==sum(x.size for x in candidate)==byte_count and
         all(x.size==y.size for x,y in zip(native,candidate)),
         f'original full action {case:#x} instruction/byte width changed')
    if case in (0x345,0x347,0x348):
        # Three large physically different game trajectories; original
        # 0x348 reverses angle inputs to SetPolarVelocityAt40FB70.
        if case==0x348:
            need(native[144].mnemonic==candidate[144].mnemonic=='neg'
                 and native[145].mnemonic==candidate[145].mnemonic=='add'
                 and native[145].op_str==candidate[145].op_str=='eax, 0xb4'
                 and native[198].mnemonic==candidate[198].mnemonic=='neg'
                 and native[198].op_str==candidate[198].op_str=='eax',
                 'native original 0x348 sign/180-degree phase conversion wrong')
        cap,increase=(140,7) if case==0x345 else (120,6) if case==0x347 else (200,10)
        if case==0x348:
            ids=(236,240,245,248)
        else:
            ids=(233,237,242,245)
        ins=(native[ids[0]],native[ids[1]],native[ids[2]],native[ids[3]])
        assert all(x.mnemonic in ('cmp','add','mov') for x in ins)
        need(int(ins[0].op_str.rsplit(', ',1)[-1],0)==cap
             and int(ins[1].op_str.rsplit(', ',1)[-1],0)==increase
             and int(ins[2].op_str.rsplit(', ',1)[-1],0)==cap
             and int(ins[3].op_str.rsplit(', ',1)[-1],0)==cap,
             f'original actor {case:#x} phase increment/limit not {increase}/{cap}')
        need(sum(1 for x in native if x.mnemonic=='call' and x.op_str=='0x6406ac')==3,
             'native large trajectory must contain exactly three CRT float-to-long conversions')
    else:
        need(sum(1 for x in native if x.mnemonic=='call' and x.op_str=='0x6406ac')==2,
             'native 111-instruction parent coordinate sync must call two CRT __ftol2 helpers')
        need(native[27].mnemonic=='mov' and native[27].op_str.endswith(', 0')
             and native[29].mnemonic=='mov' and native[29].op_str.endswith(', 0x41c80000')
             and native[36].mnemonic=='movsx'
             and native[40].mnemonic=='mov'
             and native[46].mnemonic=='mov' and native[52].mnemonic=='mov',
             'native original two real parent shorts and 25.0f speed state changed')
    return True


def main():
    m=load('f585_reader',ROOT/'scripts/compare-coff-function.py')
    report=load('f585_report',ROOT/'scripts/report-fighter-action-handlers.py')
    sw=load('f585_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    grammar=load('f585_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    older=load('f585_previous',ROOT/'scripts/verify-characterobject-state-leaves-f583.py')
    pe=m.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDRESS)
    need(boss['size']==33293 and boss['postret_size']==438 and boss['jump_count']==1,
         'original entire giant CODE and complete physical switch DATA geometry changed')
    original,rows=report.report_boss(m,pe,decoder,boss)
    byaction={r['action']:int(r['handler'],16) for r in rows}
    tab=boss['tables'][0]
    need(tab['slots']==60 and tab['map_length']==198,
         'genuine native compressed switch geometry changed')
    original_dense=m.pe_bytes_at(pe,tab['dense_addr'],4*tab['slots'])
    original_sparse=m.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
    need(hashlib.sha256(original_dense).hexdigest()==tab['dense_sha'] and
         hashlib.sha256(original_sparse).hexdigest()==tab['map_sha'],
         'entire native original first compressed switch hash wrong')
    src=(ROOT/'probes/CharacterObjectActionsF572.cpp').read_text()
    need('F583/F585' in src and all(src.count(f'case 0x{case:X}:')==1 for case in CASES)
         and 'case 0x34A: g_FighterProbeMarker = 843; break;' in src,
         'actual new natural C++ must implement all five game cases, not diagnostic markers')
    # One fresh selected native-profile VC7.1 TU, including old 32 cases.
    # The previous original-native source checker independently checks all
    # 32, the full physical table and its native target PE before continuing.
    older.main()
    need(OBJECT.exists(),'missing fresh selected one-TU COFF result after prior 32-case source check')
    code,refs=m.object_function(OBJECT,SYMBOL)
    code_inst=[]
    for x in decoder.disasm(code,0):
        code_inst.append(x)
        if x.mnemonic=='ret':break
    need(code_inst and code_inst[-1].mnemonic=='ret','one-TU normal C++ switch lacks native RET')
    ret=code_inst[-1].address+code_inst[-1].size
    need(len(code)-ret==boss['postret_size'] and
         code[ret+4*tab['slots']:]==original_sparse,
         'candidate complete after-RET native index DATA no longer byte-identical')
    physical=sorted((r for r in refs if ret<=r['offset']<ret+4*tab['slots']),
                    key=lambda r:r['offset'])
    need(len(physical)==tab['slots'] and all(r['type']=='DIR32'
         and r['offset']==ret+4*k and r['addend']==0
         and r['local_symbol_offset'] is not None for k,r in enumerate(physical)),
         'new one-TU source full physical original jump-table fields invalid')
    od=[int.from_bytes(original_dense[k*4:k*4+4],'little') for k in range(tab['slots'])]
    cd=[r['local_symbol_offset'] for r in physical]
    need(sw.canonical_partitions(od)==sw.canonical_partitions(cd),
         'native original repeated/default handler shape differs')
    ja=[int(x.op_str,16) for x in code_inst if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(original['default'],16) for x in od]==[x==ja[0] for x in cd],
         'original shared default native handler slots changed')
    case_rows=[];total_fields=0
    for case,nxt in zip(CASES,ENDS):
        start,end=byaction[case],byaction[nxt]
        need(boss['address']<=start<end<boss['address']+boss['size'],
             f'original Japanese game-action case {case:#x} physical CODE extent invalid')
        native=list(decoder.disasm(m.pe_bytes_at(pe,start,end-start),start))
        cstart,cend=cd[original_sparse[case-0x320]],cd[original_sparse[nxt-0x320]]
        need(0<=cstart<cend<ret, 'candidate real case spills into after-RET DATA')
        candidate=list(decoder.disasm(code[cstart:cend],cstart))
        need(native and candidate and native[0].address==start
             and native[-1].address+native[-1].size==end
             and candidate[0].address==cstart
             and candidate[-1].address+candidate[-1].size==cend,
             f'original native entire game state {case:#x} CODE bounds are cropped/discontinuous')
        physical_refs=check_native_field(native,candidate,refs,case)
        a=grammar.authentic_grammar(native,case)
        b=grammar.authentic_grammar(candidate,case)
        need(a==b,
             f'original {case:#x} EAX/ECX/EDX/x87/control/source differs: '
             f'{[(i,x,y) for i,(x,y) in enumerate(zip(a,b)) if x!=y][:5]}')
        original_behavior(native,candidate,case)
        count,size,fields=GEOMETRY[case]
        case_rows.append({'action':f'0x{case:X}',
                          'native_complete_instructions':count,
                          'original_inner_CODE_bytes':size,
                          'real_PE_typed_COFF_fields':fields})
        total_fields+=len(physical_refs)
        print(f'{case:#05x}: complete native original {count} x86 GPR/x87/CFG '
              f'instructions / {size} original CODE bytes, '
              f'{fields} true typed native COFF fields; STRICT',flush=True)
    need(len(case_rows)==5 and total_fields==71 and
         sum(x['native_complete_instructions'] for x in case_rows)==1083 and
         sum(x['original_inner_CODE_bytes'] for x in case_rows)==4305,
         'original five real action source/PE/COFF aggregate count changed')
    previous_summary=json.loads((PREVIOUS/'summary.json').read_text())
    need(previous_summary['native_complete_real_action_count']==32 and
         previous_summary['original_native_x86_insns']==3995 and
         previous_summary['original_inner_CODE_bytes']==14835 and
         previous_summary['genuine_typed_COFF_fields']==283,
         'previous 32 real original case verifier report changed')
    OUT.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(OBJECT,OUT/'one-normal-Cpp-source.obj')
    src_log=PREVIOUS/'compiler.log'
    if src_log.exists():shutil.copyfile(src_log,OUT/'compiler.log')
    summary={'native_original_giant':'0x004EBDA0',
             'whole_original_CODE_unaccepted':33293,
             'new_complete_action_bodies':case_rows,
             'new_native_x86_instructions':1083,
             'new_original_internal_CODE_bytes':4305,
             'new_typed_native_COFF_fields':71,
             'all_complete_native_case_count':37,
             'all_original_game_action_x86_roles':5078,
             'all_original_internal_CODE_bytes_uncredited':19140,
             'all_real_typed_native_COFF_fields':354,
             'physical_native_jump_DWORD_COFF_fields':60,
             'exact_original_sparse_index_bytes':198,
             'separate_native_afterret_DATA_shape':438}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F585 37 original complete inner game cases, 5078 original x86 '
          'instruction roles, 19140 native original internal CODE bytes, '
          '354 authentic typed PE-targeted COFF call/global refs; '
          'whole giant 33293 CODE bytes STILL NONEXACT')
    print('ONE affected VC7.1 normal C++ object freshly compiled; '
          'NO accepted independent/whole CODE/DATA or full cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('TH075 original complete trajectory state source F585 check failed:',exc,file=sys.stderr)
        raise SystemExit(1)
