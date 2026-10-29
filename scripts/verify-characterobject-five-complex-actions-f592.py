#!/usr/bin/env python3
"""F592: five complete original 388/389/38A/38B/38C game-action bodies.

Entire Japanese TH075 v1.11 33293-byte CharacterObject boss original CODE
and 60-slot/198-index authentic compressed dispatch independently checked.
Fresh one normal VC7.1 switch C++ compile; prior F591 checker first proves all
49 previously reconstructed whole case bodies. F592 checks 834 additional
native x86 instruction roles, 3161 original inner CODE bytes, 64 physical
typed zero-addend PE/COFF source fields. No standalone game-case exact CODE
credit: the entire giant remains nonexact, and 38D/38E C++ source cases
remain explicitly register-nonexact hypotheses that help restore the native
38C jump width. No all-unit cold replay or external Oracle receipt.
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
ADDR=0x004EBDA0
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
BASE=ROOT/'.analysis/f591-characterobject-stage-fades-source'
OBJECT=BASE/'one-normal-Cpp-source.obj'
OUT=ROOT/'.analysis/f592-characterobject-five-complex-source'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
STATES={
 0x388:(0x389,92,334,12),
 0x389:(0x38A,174,627,12),
 0x38A:(0x38B,234,971,12),
 0x38B:(0x38C,260,953,18),
 0x38C:(0x38D,74,276,10),
}
TYPED={
  0x0045B830:('REL32','ResetAt45B830'),
  0x0040FBB0:('REL32','ResetStateAt40FBB0'),
  0x00455580:('REL32','RandomAt455580'),
  0x00659728:('DIR32','gSubtractAt00659728'),
  0x006581DC:('DIR32','gOffsetAt006581DC'),
  0x0040FB70:('REL32','MotionAt40FB70'),
  0x00659454:('DIR32','gVelocityDragAt00659454'),
  0x00657CBC:('DIR32','gGrowAt00657CBC'),
  0x0065912C:('DIR32','gMaxPositionAt0065912C'),
  0x0040FA30:('REL32','GetStateAt40FA30'),
  0x00657850:('DIR32','gFloatAt00657850'),
  0x00453A70:('REL32','SpawnDirectedAt453A70'),
  0x00453D40:('REL32','ModifyAt453D40'),
  0x0040FB40:('REL32','SetStateAt40FB40'),
  0x00659730:('DIR32','gMulDoubleAt00659730'),
  0x006583FC:('DIR32','gAddAt006583FC'),
  0x00657888:('DIR32','gCollisionAt00657888'),
  0x00483300:('REL32','AngleAt00483300'),
  0x00657828:('DIR32','gAngleUnitAt00657828'),
  0x006406AC:('REL32','__ftol2'),
  0x006714D0:('DIR32','gGlobalActorCountAt006714D0'),
  0x006590B4:('DIR32','gMulAt006590B4'),
  0x00659738:('DIR32','gAddAt00659738'),
  0x00658058:('DIR32','gDropAt00658058'),
  0x0040FAC0:('REL32','SetActionAt40FAC0'),
  0x00428D20:('REL32','MagnitudeAt00428D20'),
  0x006583A0:('DIR32','gLengthDivisorAt006583A0'),
  0x00659720:('DIR32','gLengthFactorAt00659720'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,path)
    need(sp is not None and sp.loader is not None,
         f'missing original PE/COFF reference helper: {path}')
    m=importlib.util.module_from_spec(sp)
    sys.modules[tag]=m
    sp.loader.exec_module(m)
    return m


def typed_original_COFF(native,compiled,refs,case):
    start,end=compiled[0].address,compiled[-1].address+compiled[-1].size
    rows=[r for r in refs if start<=r['offset']<end]
    observed=[]
    for ordinal,x in enumerate(native):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            dest=int(x.op_str,16);kind='REL32'
        elif 'ptr [0x' in x.op_str:
            dest=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
            kind='DIR32'
        else:continue
        need(dest in TYPED,
             f'new original game source case {case:#x} unknown PE target {dest:#x} at {ordinal}')
        realkind,realname=TYPED[dest]
        need(kind==realkind,
             f'original x86 PE field type differs in case {case:#x} ordinal {ordinal}')
        if dest==0x00453A70:
            if case==0x389: realname='SpawnComputedAt453A70'
            if case==0x38B and ordinal==254: realname='SpawnMovedAt453A70'
        if dest==0x00483300 and case==0x38C:
            # Actual 38C original CALL passes raw member DWORDs,
            # unlike original 38A's x87-computed float stack args.
            # Both physical callee addresses are the SAME 00483300;
            # symbol names are provisional compilation signatures.
            realname='AngleRawAt00483300'
        y=compiled[ordinal]
        need(x.mnemonic==y.mnemonic,
             f'original physical typed COFF instruction relocated within case {case:#x}:{ordinal}')
        fields=[r for r in rows if y.address<=r['offset']<y.address+y.size]
        need(len(fields)==1 and fields[0]['type']==kind
             and fields[0]['addend']==0 and realname in fields[0]['symbol'],
             f'case {case:#x} original PE target/type/zero-addend mismatch at ordinal {ordinal}: {fields}')
        observed.append((ordinal,kind,dest,realname))
    need(len(observed)==len(rows)==STATES[case][3],
         f'original whole game case {case:#x} genuine typed COFF count is not {STATES[case][3]}')
    if case==0x38A:
        need((216,'DIR32',0x006714D0,'gGlobalActorCountAt006714D0') in observed,
             'actual original BYTE global MOVSX opcode 0x6714d0 must be PE-relocated, not simply waived')
        need((95,'REL32',0x006406AC,'__ftol2') in observed,
             'original 38A float-to-int original CRT __ftol2 call not physically attested')
    if case==0x38C:
        need((54,'REL32',0x00483300,'AngleRawAt00483300') in observed
             and (32,'REL32',0x00428D20,'MagnitudeAt00428D20') in observed,
             'original 38C raw atan2/float magnitude ABI is not separately native-PE verified')
    return observed


def source_policy(native,compiled,case,grammar):
    nxt,count,size,fields=STATES[case]
    need(len(native)==len(compiled)==count and
         sum(x.size for x in native)==sum(x.size for x in compiled)==size
         and all(x.size==y.size for x,y in zip(native,compiled)),
         f'original case {case:#x} whole x86 instruction length/byte widths not recovered')
    a,b=grammar.authentic_grammar(native,case),grammar.authentic_grammar(compiled,case)
    differences=[i for i,(x,y) in enumerate(zip(a,b)) if x!=y]
    if case==0x38A:
        need(differences==[216]
             and native[216].mnemonic==compiled[216].mnemonic=='movsx'
             and native[216].op_str=='eax, byte ptr [0x6714d0]'
             and compiled[216].op_str=='eax, byte ptr [0]',
             f'original 38A native register/angle branches differ outside actual DIR32 at ordinal 216: {differences}')
        b[216]=a[216]
    else:
        need(not differences,
             f'original native source game case {case:#x} actual GPR/x87/CFG differs: '
             f'{[(i,a[i],b[i]) for i in differences[:6]]}')
    need(a==b, 'native original source machine grammar differs outside genuinely typed PE COFF field')
    for code in (native,compiled):
        if case==0x388:
            need(code[34].mnemonic=='push' and code[34].op_str=='0x2d'
                 and code[37].mnemonic=='call' and code[46].mnemonic=='call'
                 and code[75].mnemonic=='fcomp' and code[77].op_str=='ah, 5'
                 and code[78].mnemonic=='jp',
                 'real 388 parent guard and 45-range x87 random motion/float contact changed')
        elif case==0x389:
            need(code[24].mnemonic=='mov' and code[24].op_str.endswith('0xffe2')
                 and code[26].mnemonic=='mov' and code[26].op_str.endswith('0x96')
                 and code[70].mnemonic=='push' and code[70].op_str=='0x371'
                 and code[74].mnemonic=='push' and code[74].op_str=='2'
                 and code[105].mnemonic=='push'
                 and code[105].op_str.endswith('edx')
                 and code[143].op_str=='8'
                 and code[165].op_str=='4',
                 'native original 389 -30/150 initialization, original 0x371 spawn and separate stage8 conditional callbacks differ')
        elif case==0x38A:
            need(code[80].mnemonic=='fimul' and code[92].mnemonic=='call'
                 and code[94].mnemonic=='fdiv'
                 and code[95].mnemonic=='call'
                 and code[102].mnemonic=='cmp'
                 and code[103].mnemonic=='jle'
                 and code[144].mnemonic=='cmp'
                 and code[145].mnemonic=='jg'
                 and code[233].mnemonic=='jmp' and code[233].size==5,
                 'native 38A two separately rechecked angle-tracking states, real FIMUL/CRT or whole long EXIT changed')
        elif case==0x38B:
            need(code[46].mnemonic=='push' and code[46].op_str=='0xfffffe20'
                 and code[45].op_str=='0x3c0'
                 and code[178].mnemonic=='fstp'
                 and code[183].mnemonic=='mov' and code[183].op_str.endswith('dword ptr [ecx + 0x318], eax')
                 and code[188].mnemonic=='mov' and code[188].op_str.endswith('dword ptr [edx + 0x31c], ecx')
                 and code[199].mnemonic=='push' and code[199].op_str=='0x38c'
                 and code[251].mnemonic=='push' and code[251].op_str=='0x38d',
                 'original 38B native parent position raw-bit copies or distinct stage8/11 effects lost')
        else:
            need(code[23].mnemonic=='fld' and code[24].mnemonic=='fmul'
                 and code[27].mnemonic=='fld' and code[28].mnemonic=='fmul'
                 and code[29].mnemonic=='faddp' and code[32].mnemonic=='call'
                 and code[34].mnemonic=='fdiv' and code[35].mnemonic=='fmul'
                 and all(code[i].mnemonic in ('mov','push') for i in (49,50,52,53))
                 and code[54].mnemonic=='call' and code[56].mnemonic=='fdiv',
                 'native 38C two squared real actor velocities, magnitude, raw float-bit angle ABI not reproduced')
    return True


def main():
    reader=load('f592_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f592_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=load('f592_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    grammar=load('f592_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    old=load('f592_previous',ROOT/'scripts/verify-characterobject-stage-fades-f591.py')
    pe=reader.verified_target(); decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need(boss['size']==33293 and boss['postret_size']==438 and boss['jump_count']==1,
         'original entire pinned Japanese fighter CODE/postRET DATA extent changed')
    original,rows=actions.report_boss(reader,pe,decoder,boss)
    byaction={r['action']:int(r['handler'],16) for r in rows}
    tab=boss['tables'][0]
    need(tab['slots']==60 and tab['map_length']==198,
         'original physical compressed native first switch slot counts changed')
    nd=reader.pe_bytes_at(pe,tab['dense_addr'],tab['slots']*4)
    idx=reader.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
    need(hashlib.sha256(nd).hexdigest()==tab['dense_sha'] and
         hashlib.sha256(idx).hexdigest()==tab['map_sha'],
         'original physical Japanese native dense/sparse hash changed')
    src=SOURCE.read_text()
    need('F591/F592' in src and all(src.count(f'case 0x{k:X}:')==1 for k in STATES)
         and 'case 0x3E3: g_FighterProbeMarker = 996; break;' in src
         and src.count('case 0x38D: {')==src.count('case 0x38E: {')==1,
         'C++ source must include 5 genuine game bodies, source-only register-nonexact 38D/E and next actual diagnostic 3E3')
    # Fresh compile ONE affected VC7.1 C++ source TU while original F591
    # first rechecks all 49 previously strict complete native cases.
    old.main()
    prev=json.loads((ROOT/'.analysis/f591-characterobject-stage-fades-source/summary.json').read_text())
    need(prev['cumulative_real_original_game_action_cases']==49 and
         prev['cumulative_original_x86_instruction_roles']==7109 and
         prev['cumulative_original_inner_CODE_bytes_uncredited']==26691 and
         prev['cumulative_original_PE_typed_COFF_fields']==498,
         'previous 49 original case source/COFF evidence changed')
    need(OBJECT.exists(),'one normal C++ object missing after targeted source compile')
    code,refs=reader.object_function(OBJECT,SYMBOL)
    instructions=[]
    for x in decoder.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    need(instructions and instructions[-1].mnemonic=='ret','no normal VC7.1 enclosing source RET')
    ret=instructions[-1].address+instructions[-1].size
    need(len(code)-ret==boss['postret_size'] and code[ret+4*tab['slots']:]==idx,
         'candidate full native postRET original literal sparse DATA differs')
    jump=sorted((r for r in refs if ret<=r['offset']<ret+4*tab['slots']),key=lambda r:r['offset'])
    need(len(jump)==tab['slots'] and all(r['type']=='DIR32' and
         r['offset']==ret+4*i and r['addend']==0 and
         r['local_symbol_offset'] is not None for i,r in enumerate(jump)),
         '60 whole native physical jump-table COFF fields wrong')
    native_entries=[int.from_bytes(nd[i*4:i*4+4],'little') for i in range(tab['slots'])]
    compile_entries=[r['local_symbol_offset'] for r in jump]
    need(switch.canonical_partitions(native_entries)==switch.canonical_partitions(compile_entries),
         'native original default/repeated game dispatch equivalence groups changed')
    ja=[int(x.op_str,16) for x in instructions if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(original['default'],16) for x in native_entries]==[x==ja[0] for x in compile_entries],
         'Japanese original native true first-switch default handler changed')
    receipts=[];total_fields=0
    for case,(nxt,count,length,fields) in STATES.items():
        first,last=byaction[case],byaction[nxt]
        need(boss['address']<=first<last<boss['address']+boss['size'],
             'native case outside entire 33293-byte original giant')
        real=list(decoder.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        ca,cb=compile_entries[idx[case-0x320]],compile_entries[idx[nxt-0x320]]
        need(0<=ca<cb<ret, f'new game source {case:#x} selected CODE overlaps after-RET native DATA')
        compiled=list(decoder.disasm(code[ca:cb],ca))
        need(real and compiled and real[0].address==first and real[-1].address+real[-1].size==last
             and compiled[0].address==ca and compiled[-1].address+compiled[-1].size==cb,
             f'original game-action case {case:#x} entire contiguous native CODE not reconstructed')
        field_rows=typed_original_COFF(real,compiled,refs,case)
        source_policy(real,compiled,case,grammar)
        total_fields+=len(field_rows)
        receipts.append({'action':f'0x{case:X}',
                         'complete_original_native_x86_instructions':count,
                         'original_internal_CODE_bytes':length,
                         'genuine_PE_typed_COFF_fields':len(field_rows)})
        print(f'{case:#05x}: {count}/{count} true native x86 GPR/x87/CFG roles; '
              f'{length}/{length} original whole inner CODE bytes; '
              f'{len(field_rows)}/{fields} genuine zero-addend PE COFF references',flush=True)
    need(len(receipts)==5 and total_fields==64 and
         sum(r['complete_original_native_x86_instructions'] for r in receipts)==834 and
         sum(r['original_internal_CODE_bytes'] for r in receipts)==3161,
         'F592 five full source cases native original/PE/COFF totals changed')
    OUT.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(OBJECT,OUT/'one-selected-source.obj')
    if (BASE/'compiler.log').exists():shutil.copyfile(BASE/'compiler.log',OUT/'compiler.log')
    summary={'whole_original_giant':'0x004EBDA0','original_whole_CODE_nonexact':33293,
             'new_original_case_details':receipts,
             'new_original_native_x86_instruction_roles':834,
             'new_original_internal_CODE_bytes':3161,
             'new_real_typed_PE_COFF_fields':64,
             'total_verified_original_native_game_action_bodies':54,
             'total_original_native_x86_instruction_roles':7943,
             'total_original_inner_CODE_bytes_uncredited':29852,
             'total_native_PE_typed_COFF_call_global_fields':562,
             'original_physical_dense_DWORD_COFF':60,
             'byte_identical_native_sparse_index_bytes':198,
             'separate_native_postret_DATA_shape':438,
             'authentic_byte_global_relocation_38a':0x6714D0,
             'original_38d_38e_source_hypotheses_currently_strict_nonexact':True}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F592 54 complete native original whole game action bodies, '
          '7943 original x86 instruction roles, 29852 original inner CODE '
          'bytes, 562 genuine PE-typed COFF fields; WHOLE 33293 CODE NONEXACT',flush=True)
    print('ONE fresh selected normal VC7.1 TU. Two later source 38D/38E cases '
          'remain native-register-nonexact; no standalone inner CODE/whole giant '
          'exact credit, no full cold replay, no Oracle',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('F592 original native five complex actor cases source proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
