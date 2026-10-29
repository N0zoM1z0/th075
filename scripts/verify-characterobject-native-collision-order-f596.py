#!/usr/bin/env python3
"""F596: recover three exact original MOV-before-FLD collision read orders.

Check entire pinned Japanese TH075 1.11 original PE giant 004EBDA0,
all 8,789 machine instruction addresses/widths, 622 CODE plus 60
DATA authentic zero-addend typed COFF fields, and 198 original sparse
index bytes. Fresh-compile ONE affected ordinary VC7.1 C++ TU through
F593 original-backed verifier, then *independently* verify byte-identical
three native full GPR/x87/CFG actions 0x32A,0x32C,0x335 and their original
six formerly swapped read-only x86 instructions. F596 source-only
lvalue evaluation removes all 6 opcode-order errors, improves non-COFF
native 30,848 -> 30,866 /31,003 and residual 155 -> 137 bytes.
The three unaccepted whole 0x38D/38E/3E3 source cases still have
unmatched original register allocation. NO split-case or whole giant
exact CODE/DATA acceptance; no full cold replay or Oracle.
"""
from __future__ import annotations

import importlib.util
import json
from pathlib import Path
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
OBJ=ROOT/'.analysis/f593-characterobject-whole-source/one-real-normal-VC71-source.obj'
OUT=ROOT/'.analysis/f596-characterobject-native-collision-source'
SYM='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
PAIRS={0x32A:(0x32B,186,187,1062,1063,248,932),
       0x32C:(0x32D,114,115,1350,1351,176,635),
       0x335:(0x338,146,147,2521,2522,269,1022)}


def need(ok,message):
    if not ok:raise ValueError(message)


def module(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,f'missing original reader/checker {path}')
    obj=importlib.util.module_from_spec(sp)
    sys.modules[name]=obj
    sp.loader.exec_module(obj)
    return obj


def main():
    reader=module('f596_reader',ROOT/'scripts/compare-coff-function.py')
    gram=module('f596_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    prior=module('f596_f593',ROOT/'scripts/verify-characterobject-whole-geometry-f593.py')
    pe=reader.verified_target()
    original=reader.pe_bytes_at(pe,0x004EBDA0,33293)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    src=SOURCE.read_text()
    need('F596' in src.splitlines()[0] and
         all(src.count(f'case 0x{k:X}:')==1 for k in PAIRS),
         'real F596 edited original C++ source is missing or no longer includes three genuine game states')
    for action,(nextcase,localfirst,localsecond,_,_,_,_) in PAIRS.items():
        start=src.index(f'case 0x{action:X}: {{')
        end=src.index(f'case 0x{nextcase:X}: {{',start)
        inner=src[start:end]
        if action in (0x32A,0x32C):
            need(inner.count('*(&F32(0x48)) + *(&F32(0x54)) <= gCompareAt0065782C')==1,
                 f'F596 0x{action:X} must use true two-owner native collision lvalues')
        else:
            need(inner.count('*(&F32(0x48)) - *(&F32(0x54)) <= gCollisionAt00657888')==1,
                 'F596 native action0x335 stage10 collision must use actual signed two-operand source')
    # Native original geometry and all earlier PE-backed whole cases,
    # including genuine 682 typed original COFF fields, are strictly
    # checked and ONE affected normal VC7.1 source TU is freshly compiled.
    prior.main()
    summary=json.loads((ROOT/'.analysis/f593-characterobject-whole-source/summary.json').read_text())
    need(summary['entire_original_CODE_bytes_nonexact']==33293
         and summary['literal_original_afterret_DATA_bytes']==438
         and summary['native_whole_original_x86_instructions']==8789
         and summary['source_whole_x86_instructions']==8789
         and summary['native_whole_instruction_offsets_and_sizes_equal']
         and summary['source_whole_instruction_mnemonics_same_position']==8789
         and summary['whole_CODE_and_DATA_nonrelocation_comparable_bytes']==31003
         and summary['whole_CODE_and_DATA_nonrelocation_identical_bytes']==30866
         and summary['whole_nonrelocation_differing_bytes']==137
         and summary['different_nonrelocation_original_instruction_entries']==133
         and summary['remaining_swapped_Cpp_MOV_FLD_pair_indices']==[]
         and summary['true_zero_addend_PE_COFF_total_fields']==682
         and summary['total_strict_original_game_action_bodies']==56
         and summary['whole_function_byte_exact'] is False
         and summary['accepted_new_exact_whole_functions']==0,
         'new original 33K game function must have exact all-opcode order and only 137 PE-grounded nonfield byte mismatches')
    code,refs=reader.object_function(OBJ,SYM)
    n=list(decoder.disasm(original,0x004EBDA0));c=[]
    for x in decoder.disasm(code,0):
        c.append(x)
        if x.mnemonic=='ret':break
    need(len(n)==len(c)==8789 and c[-1].address+c[-1].size==33293,
         'entire original actor whole CODE instruction boundaries wrong')
    matches={}
    for action,(nextcase,localfirst,localsecond,idx1,idx2,expected_ins,expected_len) in PAIRS.items():
        for ordinal,kind,reg in ((idx1,'mov',None),(idx2,'fld',None)):
            original_inst,compiled_inst=n[ordinal],c[ordinal]
            need(original_inst.mnemonic==compiled_inst.mnemonic==kind
                 and original_inst.bytes==compiled_inst.bytes
                 and original_inst.size==compiled_inst.size==3
                 and original_inst.address-0x004EBDA0==compiled_inst.address,
                 f'original game action0x{action:X} F596 actual x86 machine opcode {ordinal} not byte exact')
        need(n[idx1].op_str.startswith('edx,') if action!=0x32C
             else n[idx1].op_str.startswith('eax,'),
             'actual native original recipient register of MOV read changed')
        code_start=n[idx1-localfirst].address
        code_end=n[idx1-localfirst+expected_ins-1].address+n[idx1-localfirst+expected_ins-1].size
        true_start=code_start-0x004EBDA0
        machine_start=code_start-0x004EBDA0
        need(code_end-code_start==expected_len,
             f'complete original action {action:#x} native physical whole CODE length changed')
        original_case=n[idx1-localfirst:idx1-localfirst+expected_ins]
        source_case=c[idx1-localfirst:idx1-localfirst+expected_ins]
        need(gram.authentic_grammar(original_case,action)==gram.authentic_grammar(source_case,action),
             f'original {action:#x} entire original x86 GPR/x87/CFG grammar changed')
        typed=[r for r in refs if machine_start<=r['offset']<machine_start+expected_len]
        need(all(r['type'] in ('REL32','DIR32') and r['addend']==0 for r in typed),
             f'original action {action:#x} source does not have genuine zero-addend COFF records')
        field_mask={off for r in typed for off in range(r['offset'],r['offset']+4)}
        byte_positions=[(x.address+j,x.bytes[j],y.bytes[j])
                        for x,y in zip(original_case,source_case) for j in range(x.size)
                        if x.address-0x004EBDA0+j not in field_mask]
        need(all(original_byte==compiled_byte for _,original_byte,compiled_byte in byte_positions),
             f'whole native {action:#x} source still differs in non-COFF bytes even after F596 real collision lvalue correction')
        matches[f'0x{action:X}']={
            'whole_native_original_instructions':expected_ins,
            'whole_native_original_CODE_bytes':expected_len,
            'original_native_MOV_FLD_ordinals':[localfirst,localsecond],
            'original_entire_giant_MOV_FLD_ordinals':[idx1,idx2],
            'byte_identical_machine_instructions':2,
        }
        print(f'0x{action:X}: {expected_ins} original complete x86 instructions/{expected_len} CODE bytes, '
              f'native MOV/FLD ordinals {localfirst}/{localsecond} now byte-identical in normal C++',flush=True)
    need(sum(x['byte_identical_machine_instructions'] for x in matches.values())==6,
         'three genuine original read-only two-register MOV/FLD pairs not all exact')
    OUT.mkdir(parents=True,exist_ok=True)
    report={'native_original_giant':'0x004EBDA0',
            'native_whole_original_CODE_bytes':33293,
            'native_whole_original_x86_instructions':8789,
            'exact_original_x86_mnemonic_ordinals':8789,
            'whole_CODE_and_DATA_total':33731,
            'real_typed_zero_addend_original_PE_COFF_fields':682,
            'whole_natives_nonrelocation_comparable_bytes':31003,
            'whole_natives_nonrelocation_matching_bytes':30866,
            'previous_matching_bytes_before_three_read_fixes':30848,
            'previous_nonfield_different_bytes':155,
            'new_nonfield_different_bytes':137,
            'new_nonfield_different_instruction_ordinals':133,
            'actual_native_MOV_FLD_instruction_pairs_byte_identical':matches,
            'remaining_whole_native_GPR_wrong_cases':['0x38D','0x38E','0x3E3'],
            'complete_giant_byte_exact':False,
            'accepted_new_whole_or_independent_CODE':0,
            'full_all_unit_cold_replay_run':False}
    (OUT/'summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F596 entire Japanese TH075 original giant 33,293 CODE /8,789 x86: '
          'ALL mnemonic orders, instruction offsets and sizes match; '
          '30,866/31,003 non-COFF CODE+DATA bytes, only 137 remain differing',flush=True)
    print('F596 682 whole true original physical PE COFF refs; real source '
          'exact 6 formerly swapped MOV/FLD instruction machine bytes; '
          'whole giant NOT byte-exact, 0 official new source CODE credit, '
          'one affected VC7.1 TU and no all-unit replay',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('F596 true Japanese native CharacterObject collision source check failed:',exc,file=sys.stderr)
        raise SystemExit(1)
