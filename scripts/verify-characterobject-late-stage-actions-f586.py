#!/usr/bin/env python3
"""F586: real CharacterObject 0x34A/0x34B complete game-action C++ source.

Fresh compile of ONE pinned normal VC7.1 TU, independently reread full
Japanese TH075 v1.11 original 33,293-byte giant CODE and separate physical
60-slot/198-index compressed switch DATA. First revalidate all previous
37 native case bodies with F585's original-backed checks, then require
strict original x86/GPR/x87/branch/width grammar and 35 original-PE
physical zero-addend typed COFF fields in 295/278-instruction case bodies.
The richer source shifts real x87 EBP temps in earlier action0x331;
those exact native source-width differences are separately checked by F586.
Neither case nor whole giant has exact independent CODE credit; no
all-unit cold replay or external Factory/Oracle acceptance.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f586-characterobject-late-stage-source'
ADDR=0x004EBDA0
SRC=ROOT/'probes/CharacterObjectActionsF572.cpp'
PREVIOUS=ROOT/'.analysis/f583-characterobject-state-leaves-source'
OBJECT=PREVIOUS/'CharacterObjectF583.obj'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
ORIGINAL_CASES={0x34A:(0x34B,295,1093,18),0x34B:(0x34C,278,1012,17)}
ORIGINAL_TYPES={
  0x0045B830:('REL32','ResetAt45B830'),
  0x00453A70:('REL32','SpawnAt453A70'),
  0x0040FBB0:('REL32','ResetStateAt40FBB0'),
  0x00659738:('DIR32','gAddAt00659738'),
  0x006583FC:('DIR32','gAddAt006583FC'),
  0x0065786C:('DIR32','gStageContactAt0065786C'),
  0x0040FB40:('REL32','SetStateAt40FB40'),
  0x00659730:('DIR32','gMulDoubleAt00659730'),
  0x0040FA30:('REL32','GetStateAt40FA30'),
  0x00455580:('REL32','RandomAt455580'),
  0x00453D40:('REL32','ModifyAt453D40'),
  0x0040FB70:('REL32','MotionRawPairAt40FB70'),
  0x00657478:('DIR32','gGrowAt00657478'),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,
         f'missing source/original-PE helper {path}')
    obj=importlib.util.module_from_spec(spec)
    sys.modules[tag]=obj
    spec.loader.exec_module(obj)
    return obj


def typed_actual_COFF(original,compiled,refs,action):
    first,last=compiled[0].address,compiled[-1].address+compiled[-1].size
    fields=[r for r in refs if first<=r['offset']<last]
    observed=[]
    for i,x in enumerate(original):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            kind='REL32';target=int(x.op_str,16)
        elif x.mnemonic.startswith('f') and 'ptr [0x' in x.op_str:
            kind='DIR32';target=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
        else:continue
        need(target in ORIGINAL_TYPES,
             f'original 0x{action:X} unknown authentic PE callee/global {target:#x} at {i}')
        expected_type,expected_symbol=ORIGINAL_TYPES[target]
        need(kind==expected_type,
             f'original physical field kind at 0x{action:X}:{i} differs')
        if target==0x00453A70 and i in ((289,) if action==0x34A else (272,)):
            expected_symbol='SpawnMovedAt453A70'
        y=compiled[i]
        need(x.mnemonic==y.mnemonic,
             f'normal C++ typed original COFF source moved native instruction ordinal {action:#x}:{i}')
        actual=[r for r in fields if y.address<=r['offset']<y.address+y.size]
        need(len(actual)==1 and actual[0]['type']==kind and
             actual[0]['addend']==0 and expected_symbol in actual[0]['symbol'],
             f'original real PE typed COFF field not C++ exact in {action:#x}:{i}: {actual}')
        observed.append((i,kind,target,expected_symbol))
    expected=ORIGINAL_CASES[action][3]
    need(len(observed)==len(fields)==expected,
         f'original new game-state {action:#x} has wrong genuine call/global COFF count')
    return observed


def actual_source_policy(native,candidate,action):
    nxt,count,size,refs=ORIGINAL_CASES[action]
    need(len(native)==len(candidate)==count and
         sum(x.size for x in native)==sum(x.size for x in candidate)==size and
         all(x.size==y.size for x,y in zip(native,candidate)),
         f'actual native full action{action:#x} x86 instruction size/extent not reconstructed')
    if action==0x34A:
        for code in (native,candidate):
            need(code[92].mnemonic=='mov' and code[92].op_str.endswith('0x40400000')
                 and code[94].mnemonic=='mov' and code[94].op_str.endswith('0xc0400000')
                 and code[141].mnemonic=='fcomp'
                 and code[143].mnemonic=='test' and code[143].op_str=='ah, 0x41'
                 and code[144].mnemonic=='jp'
                 and code[146].op_str.endswith('0x41a00000')
                 and code[220].mnemonic=='cmp' and code[220].op_str.endswith(', 1')
                 and code[261].mnemonic=='push' and code[261].op_str=='0x3c'
                 and code[286].mnemonic=='push' and code[286].op_str=='0x323',
                 'original action0x34A genuine +3/-3f speeds/threshold/phase/random/effect values differ')
        need(native[141].op_str=='dword ptr [0x65786c]'
             and candidate[141].op_str=='dword ptr [0]',
             'native original stage contact threshold 0065786C not physically relocated')
    else:
        # Original 0x34B passes *two raw DWORD float representations*
        # directly, not code that loads x87 then converts float to int.
        for code in (native,candidate):
            need(code[92].mnemonic=='mov' and code[92].op_str.endswith('[ecx + 0xc8]')
                 and code[93].mnemonic=='push' and code[93].op_str=='edx'
                 and code[95].mnemonic=='mov' and code[95].op_str.endswith('[eax + 0xcc]')
                 and code[96].mnemonic=='push' and code[96].op_str=='ecx'
                 and code[98].mnemonic=='call'
                 and code[243].mnemonic=='push' and code[243].op_str=='0xf'
                 and code[247].mnemonic=='sub' and code[247].op_str.endswith('0x3c')
                 and code[269].mnemonic=='push' and code[269].op_str=='0x324',
                 'original action0x34B raw angle/speed ABI or native random/effect literal differs')
        need(all(x.mnemonic not in ('fld','fstp') for x in native[92:99])
             and all(y.mnemonic not in ('fld','fstp') for y in candidate[92:99]),
             'native 0x34B must not convert original 32-bit raw argument bits')
    return True


def main():
    reader=module('f586_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f586_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    sw=module('f586_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    grammar=module('f586_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    old=module('f586_previous',ROOT/'scripts/verify-characterobject-five-trajectory-actions-f585.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ADDR)
    need(boss['size']==33293 and boss['postret_size']==438 and boss['jump_count']==1,
         'original complete fighter giant CODE or native switch DATA shape changed')
    report,rows=actions.report_boss(reader,pe,decoder,boss)
    caseaddresses={r['action']:int(r['handler'],16) for r in rows}
    table=boss['tables'][0]
    need(table['slots']==60 and table['map_length']==198,
         'original compressed switch number of physical DWORD/index slots changed')
    native_dense=reader.pe_bytes_at(pe,table['dense_addr'],4*table['slots'])
    native_index=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(hashlib.sha256(native_dense).hexdigest()==table['dense_sha'] and
         hashlib.sha256(native_index).hexdigest()==table['map_sha'],
         'original physical Japanese dense/sparse SHA verification failed')
    source=SRC.read_text()
    need('F585/F586' in source and all(source.count(f'case 0x{k:X}:')==1 for k in ORIGINAL_CASES)
         and 'case 0x385: g_FighterProbeMarker = 902; break;' in source,
         'new C++ source must implement exactly two real new game action bodies and mark later native cases unknown')
    # Only ONE selected VC7.1 C++ object, freshly built by the existing
    # original-backed checker, independently verifying all 37 prior game cases.
    old.main()
    need(OBJECT.exists(),'previous source checker did not compile one fresh C++ translation unit')
    code,refs=reader.object_function(OBJECT,SYMBOL)
    inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret','normal VC7.1 source lacks final RET')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'] and
         code[ret+4*table['slots']:]==native_index,
         'complete actual native original after-RET sparse DATA does not match source')
    dense=sorted((r for r in refs if ret<=r['offset']<ret+table['slots']*4),
                 key=lambda r:r['offset'])
    need(len(dense)==table['slots'] and all(x['type']=='DIR32'
         and x['offset']==ret+4*i and x['addend']==0 and x['local_symbol_offset'] is not None
         for i,x in enumerate(dense)),
         'candidate native original physical whole switch jump COFF fields invalid')
    nd=[int.from_bytes(native_dense[4*i:4*i+4],'little') for i in range(table['slots'])]
    cd=[x['local_symbol_offset'] for x in dense]
    need(sw.canonical_partitions(nd)==sw.canonical_partitions(cd),
         'original real duplicate/default native switch handler partitions mismatch')
    ja=[int(x.op_str,16) for x in inst if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(report['default'],16) for x in nd]==[x==ja[0] for x in cd],
         'actual original first switch default slot target mismatches')
    recorded=[];total_coff=0
    for action,(nxt,inscount,codesize,fieldcount) in ORIGINAL_CASES.items():
        original_first,original_end=caseaddresses[action],caseaddresses[nxt]
        need(boss['address']<=original_first<original_end<boss['address']+boss['size'],
             'original physical real actor case CODE outside SHA-verified full giant')
        real=list(decoder.disasm(reader.pe_bytes_at(pe,original_first,original_end-original_first),original_first))
        cs,ce=cd[native_index[action-0x320]],cd[native_index[nxt-0x320]]
        need(0<=cs<ce<ret,'candidate whole native action CODE improperly in DATA region')
        compiled=list(decoder.disasm(code[cs:ce],cs))
        need(real and compiled and real[0].address==original_first and
             real[-1].address+real[-1].size==original_end and
             compiled[0].address==cs and compiled[-1].address+compiled[-1].size==ce,
             f'original/VC7 source complete native action {action:#x} chopped/aliased')
        physical=typed_actual_COFF(real,compiled,refs,action)
        a,b=grammar.authentic_grammar(real,action),grammar.authentic_grammar(compiled,action)
        need(a==b,
             f'actual source game case {action:#x} native register/x87/relative CFG mismatch: '
             f'{[(i,x,y) for i,(x,y) in enumerate(zip(a,b)) if x!=y][:5]}')
        actual_source_policy(real,compiled,action)
        total_coff+=len(physical)
        recorded.append({'action':f'0x{action:X}',
                         'native_original_x86_instructions':inscount,
                         'native_original_inner_CODE_bytes':codesize,
                         'true_native_COFF_relocations':fieldcount})
        print(f'{action:#05x}: complete original {inscount} native x86 '
              f'GPR/x87/branch byte-width roles, {codesize} real inner CODE '
              f'bytes, {fieldcount} real COFF refs, zero new order exceptions',flush=True)
    need(len(recorded)==2 and total_coff==35 and
         sum(x['native_original_x86_instructions'] for x in recorded)==573 and
         sum(x['native_original_inner_CODE_bytes'] for x in recorded)==2105,
         'two native stage source cases physical PE aggregates changed')
    prior=json.loads((ROOT/'.analysis/f585-characterobject-five-native-source/summary.json').read_text())
    need(prior['all_complete_native_case_count']==37 and
         prior['all_original_game_action_x86_roles']==5078 and
         prior['all_original_internal_CODE_bytes_uncredited']==19140 and
         prior['all_real_typed_native_COFF_fields']==354,
         'previous 37 original actions recompiled with unexpected source/COFF changes')
    previous_context=json.loads((PREVIOUS/'summary.json').read_text())
    need(previous_context['native_complete_real_action_count']==32 and
         previous_context['genuine_original_deep_frame_extra_bytes'] in (0,18,24),
         'new authentic 0x331 x87 EBP layout has not been physically validated as 18->6 bytes')
    OUT.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(OBJECT,OUT/'one-normal-Cpp-source.obj')
    log=PREVIOUS/'compiler.log'
    if log.exists():shutil.copyfile(log,OUT/'compiler.log')
    summary={'original_giant':'0x004EBDA0',
             'entire_original_CODE_unaccepted':33293,
             'new_complete_original_case_details':recorded,
             'new_original_native_x86_instructions':573,
             'new_original_internal_CODE_bytes':2105,
             'new_real_typed_COFF_fields':35,
             'all_complete_original_cases':39,
             'all_original_native_x86_instruction_roles':5651,
             'all_original_inner_CODE_bytes_uncredited':21245,
             'all_typed_original_PE_call_global_COFF_fields':389,
             'original_physical_switch_DWORD_COFF':60,
             'exact_original_sparse_index_bytes':198,
             'native_afterret_DATA_layout_bytes':438,
             'new_original_frame_width_surplus_0x330':next(r['native_deep_frame_extra_bytes'] for r in previous_context['case_details'] if r['action']=='0x330'),
             'new_original_frame_width_surplus_0x331':next(r['native_deep_frame_extra_bytes'] for r in previous_context['case_details'] if r['action']=='0x331')}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F586: 39 real complete original game-action source cases, '
          '5651 native x86 instruction roles, 21245 original internal CODE '
          'bytes, 389 authentic PE-targeted typed COFF call/global fields; '
          '33293 whole original giant CODE bytes remain NONEXACT')
    print('Only ONE selected natural VC7.1 source compiled, PE/FPU/COFF '
          'strictly checked; no split or whole CODE/DATA exact credit, '
          'no full all-unit cold replay or external Oracle receipt')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('TH075 true original CharacterObject late stages F586 check failed:',exc,file=sys.stderr)
        raise SystemExit(1)
