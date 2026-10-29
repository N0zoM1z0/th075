#!/usr/bin/env python3
"""F588: three original whole action 0x34D/34E/34F source bodies in 004EBDA0.

Pin Japanese TH075 v1.11 original complete 33293-byte game giant CODE and
all physical after-RET sparse jump DATA. Build exactly ONE new natural VC7.1
C++ TU via F587's original-backed source proof, validate all previous
40 real original complete gameplay cases, then compare true 190/163/161
instruction full native case ranges, GPR/x87/CFG/instruction widths, and
35 actual original-PE typed zero-addend call/global COFF fields.

Original 0x34D uses *raw DWORD bit copies*, never x87 conversions.
Original 0x34E has no +0x7C/+0x80 stage0 stores; original 0x34F does.
Adding these authentic source cases makes original EBP int-to-FILD
saved locals in 0x330/331/332 byte-operand identical, NOT a complete
whole giant exact function. No fake locals or all-unit cold replay.
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
ADDR=0x004EBDA0
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
BASE=ROOT/'.analysis/f583-characterobject-state-leaves-source'
OBJ=BASE/'CharacterObjectF583.obj'
OUT=ROOT/'.analysis/f588-characterobject-three-source'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
STATES={0x34D:(0x34E,190,697,13),
        0x34E:(0x34F,163,603,11),
        0x34F:(0x370,161,599,11)}
TYPED={
  0x0045B830:('REL32','ResetAt45B830'),
  0x00453A70:('REL32','SpawnAt453A70'),
  0x0040FBB0:('REL32','ResetStateAt40FBB0'),
  0x00659090:('DIR32','gSubAt00659090'),
  0x00657CC0:('DIR32','gLiftAt00657CC0'),
  0x0065782C:('DIR32','gCompareAt0065782C'),
  0x00453D40:('REL32','ModifyAt453D40'),
  0x0040FAC0:('REL32','SetActionAt40FAC0'),
  0x0040FA30:('REL32','GetStateAt40FA30'),
  0x0040FB40:('REL32','SetStateAt40FB40'),
  0x00659730:('DIR32','gMulDoubleAt00659730'),
  0x006583FC:('DIR32','gAddAt006583FC'),
  0x0065747C:('DIR32','gCompareAt0065747C'),
  0x00657480:('DIR32','gMotionDecelAt00657480'),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,
         f'missing original verified helper {path}')
    module=importlib.util.module_from_spec(spec)
    sys.modules[tag]=module
    spec.loader.exec_module(module)
    return module


def genuine_COFF(native,candidate,refs,case):
    first,end=candidate[0].address,candidate[-1].address+candidate[-1].size
    physical=[r for r in refs if first<=r['offset']<end]
    observed=[]
    for ordinal,x in enumerate(native):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            kind='REL32';addr=int(x.op_str,16)
        elif x.mnemonic.startswith('f') and 'ptr [0x' in x.op_str:
            kind='DIR32';addr=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
        else:continue
        need(addr in TYPED,
             f'native original 0x{case:X} new call/global at ordinal {ordinal}: {addr:#x}')
        actual_kind,actual_symbol=TYPED[addr]
        need(actual_kind==kind,'original native call/global physical relocation type changed')
        if case==0x34D and addr==0x00453A70 and ordinal in (152,166):
            actual_symbol='SpawnDirectedAt453A70'
        y=candidate[ordinal]
        need(x.mnemonic==y.mnemonic,
             f'original 0x{case:X} typed call/global x86 instruction moved at ordinal {ordinal}')
        found=[r for r in physical if y.address<=r['offset']<y.address+y.size]
        need(len(found)==1 and found[0]['type']==kind and found[0]['addend']==0
             and actual_symbol in found[0]['symbol'],
             f'original game 0x{case:X} PE grounded physical COFF mismatch ordinal {ordinal}: {found}')
        observed.append((ordinal,kind,addr,actual_symbol))
    need(len(observed)==len(physical)==STATES[case][3],
         f'original full game-action 0x{case:X} real call/global COFF field count differs')
    return observed


def native_source_policy(native,candidate,case):
    nxt,inscount,codesize,fields=STATES[case]
    need(len(native)==len(candidate)==inscount and
         sum(x.size for x in native)==sum(x.size for x in candidate)==codesize and
         all(x.size==y.size for x,y in zip(native,candidate)),
         f'original entire native case 0x{case:X} x86 byte/inst geometry wrong')
    for ins in (native,candidate):
        need(ins[3].mnemonic=='cmp' and
             ins[3].op_str.endswith(', 0x31') and
             ins[8].mnemonic=='cmp' and
             ins[8].op_str.endswith(', 0x96') and
             ins[17].mnemonic=='cmp' and
             ins[17].op_str.endswith(', '+('5' if case==0x34D else '4')),
             'original parent state limits and genuine effect loop length differ')
        if case==0x34D:
            # Raw memory bit copy of source C8/CC into actor 50/54.
            need(ins[77].mnemonic==ins[78].mnemonic==ins[79].mnemonic==ins[80].mnemonic=='mov'
                 and ins[79].op_str.endswith('dword ptr [ecx + 0xc8]')
                 and ins[80].op_str.endswith('dword ptr [eax + 0x50], edx')
                 and ins[83].op_str.endswith('dword ptr [ecx + 0xcc]')
                 and ins[84].op_str.endswith('dword ptr [eax + 0x54], edx')
                 and all(x.mnemonic not in ('fld','fstp') for x in ins[77:85]),
                 'original 34D stage0 must use raw DWORD field-to-field copies, no artificial x87 conversions')
            need(ins[99].mnemonic=='fsub' and
                 ins[131].mnemonic=='fcomp' and
                 ins[133].op_str=='ah, 0x41' and
                 ins[134].mnemonic=='jp' and
                 ins[149].mnemonic=='push' and ins[149].op_str=='0x32b' and
                 ins[163].op_str=='0x32d' and
                 ins[167].op_str=='0x33b',
                 'original 34D x87 ground contact and distinct 0x32B/0x32D effects differ')
        elif case==0x34E:
            need(ins[62].mnemonic=='cmp' and ins[62].op_str.endswith(', 2')
                 and ins[101].mnemonic=='mov' and ins[101].op_str.endswith('0x41a00000')
                 and ins[103].op_str.endswith(', 0')
                 and ins[105].op_str.endswith(', 0')
                 and ins[120].mnemonic=='fsub' and
                 ins[125].mnemonic=='fcomp' and ins[127].op_str=='ah, 5'
                 and ins[128].mnemonic=='jp' and
                 ins[130].op_str.endswith('0x40000000') and
                 ins[154].mnemonic=='push' and ins[154].op_str=='1' and
                 ins[156].mnemonic=='call',
                 'original 34E native frame fade & stage threshold / 2.0f speed floor changed')
            need(not any(x.mnemonic=='mov' and ('+ 0x7c]' in x.op_str or '+ 0x80]' in x.op_str)
                         for x in ins[100:118]),
                 'original 34E stage0 does NOT contain extra 0x7C/+0x80 stores')
        else:
            need(ins[62].mnemonic=='cmp' and ins[62].op_str.endswith(', 1')
                 and ins[101].op_str.endswith('0x41a00000')
                 and ins[105].op_str.endswith(', 0')
                 and ins[107].op_str.endswith(', 0')
                 and ins[109].op_str.endswith(', 1')
                 and ins[124].mnemonic=='fsub'
                 and ins[129].mnemonic=='fcomp'
                 and ins[131].op_str=='ah, 5' and
                 ins[132].mnemonic=='jp' and
                 ins[134].op_str.endswith('0x40000000')
                 and ins[159].mnemonic=='call',
                 'original 34F counter/0x7C/0x80 stage0 stores, float speed floor or final RESET differs')
    return True


def main():
    reader=load('f588_reader',ROOT/'scripts/compare-coff-function.py')
    report=load('f588_report',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=load('f588_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    grammar=load('f588_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    prior=load('f588_prior40',ROOT/'scripts/verify-characterobject-four-way-event-f587.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need(boss['size']==33293 and boss['postret_size']==438 and boss['jump_count']==1,
         'original entire native 004EBDA0 boss CODE/postRET DATA geometry changed')
    original,rows=report.report_boss(reader,pe,decoder,boss)
    byaction={r['action']:int(r['handler'],16) for r in rows}
    table=boss['tables'][0]
    need(table['slots']==60 and table['map_length']==198,
         'real Japanese original compressed switch DWORD/index counts changed')
    orig_dense=reader.pe_bytes_at(pe,table['dense_addr'],table['slots']*4)
    orig_sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(hashlib.sha256(orig_dense).hexdigest()==table['dense_sha'] and
         hashlib.sha256(orig_sparse).hexdigest()==table['map_sha'],
         'original native Japanese whole sparse switch DATA hash changed')
    src=SOURCE.read_text()
    need('F587/F588' in src
         and all(src.count(f'case 0x{k:X}:')==1 for k in STATES)
         and 'case 0x370: g_FighterProbeMarker = 881; break;' in src,
         'new source must implement 34D/34E/34F and leave actual next 0x370 unfinished')
    # Only ONE selected native-profile VC7.1 TU built while rechecking
    # all 40 prior complete original cases and entire PE physical tables.
    prior.main()
    old=json.loads((ROOT/'.analysis/f587-characterobject-four-way-source/summary.json').read_text())
    need(old['all_complete_original_game_actions']==40 and
         old['all_original_x86_instruction_roles']==6048 and
         old['all_original_internal_CODE_bytes_uncredited']==22774 and
         old['all_authentic_typed_COFF_call_global_fields']==414,
         'original F587 40-case original PE/COFF source integrity changed')
    code,refs=reader.object_function(OBJ,SYMBOL)
    instructions=[]
    for x in decoder.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    need(instructions and instructions[-1].mnemonic=='ret',
         'new normal C++ whole original switch has no RET')
    ret=instructions[-1].address+instructions[-1].size
    need(len(code)-ret==boss['postret_size'] and
         code[ret+4*table['slots']:]==orig_sparse,
         'original afterRET physical sparse byte DATA not matched')
    jump=sorted((r for r in refs if ret<=r['offset']<ret+4*table['slots']),
                key=lambda r:r['offset'])
    need(len(jump)==table['slots'] and all(r['type']=='DIR32' and
         r['offset']==ret+4*i and r['addend']==0 and r['local_symbol_offset'] is not None
         for i,r in enumerate(jump)),
         'genuine complete 60 physical jump target COFF fields differ')
    nd=[int.from_bytes(orig_dense[4*i:4*i+4],'little') for i in range(table['slots'])]
    cd=[r['local_symbol_offset'] for r in jump]
    need(switch.canonical_partitions(nd)==switch.canonical_partitions(cd),
         'native first switch shared default/equal target partitions differ')
    ja=[int(x.op_str,16) for x in instructions if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(original['default'],16) for x in nd]==[x==ja[0] for x in cd],
         'actual original native shared default jump targets differ')
    case_receipts=[];typed=0
    for case,(nextcase,count,code_bytes,expected_fields) in STATES.items():
        first,last=byaction[case],byaction[nextcase]
        need(boss['address']<=first<last<boss['address']+boss['size'],
             'native real action CODE not inside whole original giant')
        native=list(decoder.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        cs,ce=cd[orig_sparse[case-0x320]],cd[orig_sparse[nextcase-0x320]]
        need(0<=cs<ce<ret,'new native actor source case incorrect CODE/DATA extent')
        candidate=list(decoder.disasm(code[cs:ce],cs))
        need(native and candidate and native[0].address==first
             and native[-1].address+native[-1].size==last
             and candidate[0].address==cs and candidate[-1].address+candidate[-1].size==ce,
             f'complete original native case {case:#x} CODE range cropped/invalid')
        fields=genuine_COFF(native,candidate,refs,case)
        a,b=grammar.authentic_grammar(native,case),grammar.authentic_grammar(candidate,case)
        need(a==b,
             f'original native 0x{case:X} GPR/x87/CFG field source mismatch: '
             f'{[(i,x,y) for i,(x,y) in enumerate(zip(a,b)) if x!=y][:7]}')
        native_source_policy(native,candidate,case)
        typed+=len(fields)
        case_receipts.append({'action':f'0x{case:X}',
                              'whole_original_x86_instruction_count':count,
                              'actual_original_inner_CODE_bytes':code_bytes,
                              'native_typed_zero_addend_COFF_fields':len(fields)})
        print(f'{case:#05x}: {count}/{count} strict x86 GPR/x87/CFG instructions, '
              f'{code_bytes}/{code_bytes} original entire internal CODE bytes, '
              f'{len(fields)}/{expected_fields} genuine typed original PE call/global COFF refs',flush=True)
    need(len(case_receipts)==3 and typed==35 and
         sum(x['whole_original_x86_instruction_count'] for x in case_receipts)==514 and
         sum(x['actual_original_inner_CODE_bytes'] for x in case_receipts)==1899,
         'native complete three new game-state original source/COFF totals differ')
    prev=json.loads((BASE/'summary.json').read_text())
    need(prev['native_complete_real_action_count']==32 and
         prev['genuine_original_deep_frame_extra_bytes']==0,
         'PE-tracked 330/331 real x87 FILD/EBP original operand widths no longer equal')
    # Must use EXACT EBP original addresses, not merely equal byte widths.
    need(all(next(x for x in prev['case_details'] if x['action']==action)['native_deep_frame_extra_bytes']==0
             for action in ('0x330','0x331','0x332')),
         'native original saved-EBP temp slots are not independently exactly tested')
    OUT.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(OBJ,OUT/'one-original-shaped-Cpp-source.obj')
    if (BASE/'compiler.log').exists():shutil.copyfile(BASE/'compiler.log',OUT/'compiler.log')
    summary={'native_original_giant':'0x004EBDA0',
             'complete_original_CODE_unaccepted':33293,
             'new_native_complete_case_details':case_receipts,
             'new_original_x86_instructions':514,
             'new_original_inner_CODE_bytes':1899,
             'new_true_typed_COFF':35,
             'total_physically_real_game_action_cases':43,
             'total_original_x86_instruction_roles':6562,
             'total_original_inner_CODE_bytes_uncredited':24673,
             'total_native_typed_COFF_call_global':449,
             'original_physical_dense_switch_DWORD_fields':60,
             'original_exact_sparse_index_bytes':198,
             'original_afterret_DATA_shape':438,
             'original_330_331_332_x87_EBP_operand_identical':True}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F588 whole original CharacterObject 43 real complete native actions, '
          '6562 native x86 roles, 24673 original inner CODE bytes, '
          '449 physical typed COFF refs; original giant 33293 bytes NONEXACT')
    print('Genuine native original 330/331/332 EBP FILD temp slots now '
          'source operand-identical; no independent/whole exact credit '
          'and NO all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('F588 original three real CharacterObject stages verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
