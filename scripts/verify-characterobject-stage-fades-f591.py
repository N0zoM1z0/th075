#!/usr/bin/env python3
"""F591: three native 0x385/0x386/0x387 complete 138/84/74 game actions.

One newly selected normal VC7.1 C++ translation unit containing all 49
original physical real actions in still-nonexact original 004EBDA0 giant.
Hash entire Japanese TH075 1.11 PE and check actual original sparse
switch 60-DWORD/198-index DATA. Freshly verify prior 46 original cases
through F590, then strict full native x86 GPR/x87/CFG/byte-width grammar,
all 24 zero-addend typed original PE COFF fields in 3 new real actions.
Important native original policy: 0x386 always fades even at stage0,
whereas 0x385/0x387 fade only after stage1. Do not fabricate stage guards.
No standalone split/whole CODE or all-unit cold replay.
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
SRC=ROOT/'probes/CharacterObjectActionsF572.cpp'
BASE=ROOT/'.analysis/f583-characterobject-state-leaves-source'
OBJ=BASE/'CharacterObjectF583.obj'
OUT=ROOT/'.analysis/f591-characterobject-stage-fades-source'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
STATES={0x385:(0x386,138,511,10),
        0x386:(0x387,84,330,7),
        0x387:(0x388,74,262,7)}
REAL_FIELDS={
  0x006590A0:('DIR32','gParentYAt006590A0'),
  0x0040FBB0:('REL32','ResetStateAt40FBB0'),
  0x006583FC:('DIR32','gAddAt006583FC'),
  0x00659090:('DIR32','gSubAt00659090'),
  0x0045B830:('REL32','ResetAt45B830'),
  0x0040FA30:('REL32','GetStateAt40FA30'),
  0x00659728:('DIR32','gSubtractAt00659728'),
  0x006590B4:('DIR32','gMulAt006590B4'),
  0x00658058:('DIR32','gDropAt00658058'),
  0x00657CC0:('DIR32','gLiftAt00657CC0'),
  0x0065782C:('DIR32','gCompareAt0065782C'),
  0x00453A70:('REL32','SpawnDirectedAt453A70'),
  0x00453D40:('REL32','ModifyAt453D40'),
  0x0040FAC0:('REL32','SetActionAt40FAC0'),
  0x006714D0:('DIR32','gGlobalActorCountAt006714D0'),
  0x0040FB40:('REL32','SetStateAt40FB40'),
  0x00453E60:('REL32','SetupAt453E60'),
  0x00659724:('DIR32','gAbsScaleAt00659724'),
  0x006583F8:('DIR32','gFadeAt006583F8'),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,path)
    need(sp is not None and sp.loader is not None,
         f'missing native original game PE COFF verifier: {path}')
    module=importlib.util.module_from_spec(sp)
    sys.modules[tag]=module
    sp.loader.exec_module(module)
    return module


def genuine_native_COFF(native,candidate,refs,case):
    start,end=candidate[0].address,candidate[-1].address+candidate[-1].size
    physical=[r for r in refs if start<=r['offset']<end]
    observed=[]
    for i,x in enumerate(native):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            addr=int(x.op_str,16);kind='REL32'
        elif 'ptr [0x' in x.op_str:
            addr=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
            kind='DIR32'
        else:continue
        need(addr in REAL_FIELDS,
             f'original Japanese action {case:#x} unknown real physical call/global {addr:#x} at {i}')
        typ,symbol=REAL_FIELDS[addr]
        need(typ==kind,
             f'original native physical field {case:#x}:{i} kind changed')
        if case==0x385 and addr==0x00453A70 and i in (66,136):
            symbol='SpawnDirectedAt453A70'
        y=candidate[i]
        need(x.mnemonic==y.mnemonic,
             f'new genuine game C++ original PE field moved instruction ordinal {i}')
        fields=[r for r in physical if y.address<=r['offset']<y.address+y.size]
        need(len(fields)==1 and fields[0]['type']==kind and
             fields[0]['addend']==0 and symbol in fields[0]['symbol'],
             f'original Japanese actor case {case:#x} physical field {i} not genuine typed COFF target: {fields}')
        observed.append((i,addr,kind))
    need(len(observed)==len(physical)==STATES[case][3],
         f'original native case {case:#x} real physical typed COFF field count mismatch')
    if case==0x384:
        need((102,0x006714D0,'DIR32') in observed,
             'true original global actor count MOVSX byte operand has no physical native COFF')
    return observed


def strict_original_policy(native,candidate,case,grammar):
    next_case,count,size,fields=STATES[case]
    need(len(native)==len(candidate)==count and
         sum(x.size for x in native)==sum(x.size for x in candidate)==size and
         all(x.size==y.size for x,y in zip(native,candidate)),
         f'original complete {case:#x} x86 count / whole CODE byte-width geometry differs')
    original=grammar.authentic_grammar(native,case)
    source=grammar.authentic_grammar(candidate,case)
    need(original==source,
         f'original whole native {case:#x} EAX/ECX/EDX/x87/CFG source mismatch: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(original,source)) if x!=y][:6]}')
    for code in (native,candidate):
        need(code[2].mnemonic=='movsx' and code[2].op_str.endswith('0x3a0]')
             and code[4].mnemonic=='jg' and code[6].mnemonic=='call'
             and code[6].size==5,
             f'original actor parent live short +0x3A0 guard missing in {case:#x}')
        if case==0x385:
            need(code[17].mnemonic=='mov' and code[17].op_str.endswith(', 0')
                 and code[32].op_str.endswith('0x3f400000')
                 and code[34].op_str.endswith('0x3f400000')
                 and code[49].mnemonic=='push' and code[49].op_str=='0x40a00000'
                 and code[52].mnemonic=='call'
                 and code[63].mnemonic=='push' and code[63].op_str=='0x387'
                 and code[66].mnemonic=='call'
                 and code[68].mnemonic=='cmp' and code[68].op_str.endswith(', 6')
                 and code[73].mnemonic=='mov' and code[73].op_str.endswith('0x80]')
                 and code[89].mnemonic=='cmp' and code[89].op_str.endswith(', 1')
                 and code[93].mnemonic=='cmp' and code[93].op_str.endswith(', 0x28')
                 and code[94].mnemonic=='jl'
                 and code[133].mnemonic=='push' and code[133].op_str=='0x386',
                 'original case385 5.0f parent setup, effects 387/386, signed stage>1 or color40 fade changed')
        elif case==0x386:
            need(code[17].mnemonic=='mov' and code[17].op_str.endswith(', 0')
                 and code[32].op_str.endswith('0x3f400000')
                 and code[34].op_str.endswith('0x3f400000')
                 and code[60].mnemonic=='movzx'
                 and code[61].mnemonic=='cmp' and code[61].op_str.endswith(', 0x14')
                 and code[62].mnemonic=='jl'
                 and code[70].mnemonic=='mov' and code[70].op_str.endswith(', 0')
                 and code[72].mnemonic=='call',
                 'native original case386 always fade by20, no stage>1 guard or invented effect')
        else:
            need(code[22].mnemonic=='mov' and code[22].op_str.endswith('0x3f400000')
                 and code[24].mnemonic=='mov' and code[24].op_str.endswith('0x3f400000')
                 and code[34].mnemonic=='mov' and code[34].op_str.endswith('0x4e2')
                 and code[36].mnemonic=='mov' and code[36].op_str.endswith('0xc2960000')
                 and code[39].mnemonic=='fadd' and code[44].mnemonic=='fadd'
                 and code[49].mnemonic=='cmp' and code[49].op_str.endswith(', 1')
                 and code[53].mnemonic=='cmp' and code[53].op_str.endswith(', 0x14')
                 and code[54].mnemonic=='jle' and code[62].mnemonic=='call',
                 'original case387 x87 global 006583F8, sprite0x4E2/-75f and strict >20 fade differ')
    return True

def main():
    reader=load('f591_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f591_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=load('f591_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    grammar=load('f591_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    prior=load('f591_previous',ROOT/'scripts/verify-characterobject-guarded-stages-f590.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need(boss['size']==33293 and boss['postret_size']==438 and boss['jump_count']==1,
         'original entire Japanese native giant CODE or afterRET physical DATA shape changed')
    original,rows=actions.report_boss(reader,pe,decoder,boss)
    byaction={r['action']:int(r['handler'],16) for r in rows}
    tab=boss['tables'][0]
    need(tab['slots']==60 and tab['map_length']==198,
         'original compressed physical first-switch target/index shape changed')
    nd=reader.pe_bytes_at(pe,tab['dense_addr'],tab['slots']*4)
    index=reader.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
    need(hashlib.sha256(nd).hexdigest()==tab['dense_sha'] and
         hashlib.sha256(index).hexdigest()==tab['map_sha'],
         'complete original Japanese physical dense/sparse index hashes differ')
    src=SRC.read_text()
    need('F588/F590/F591' in src and all(src.count(f'case 0x{x:X}:')==1 for x in STATES)
         and 'case 0x388: g_FighterProbeMarker = 905; break;' in src,
         'source must implement all three real native cases, leave 385 diagnostic')
    # Exactly one affected VC7.1 TU freshly compiled by original-PE
    # backed F588 check, also checking all 46 previous native actions.
    prior.main()
    old=json.loads((ROOT/'.analysis/f590-characterobject-guarded-source/summary.json').read_text())
    need(old['cumulative_real_original_game_action_cases']==46
         and old['cumulative_original_x86_instruction_roles']==6813
         and old['cumulative_original_inner_CODE_bytes_uncredited']==25588
         and old['cumulative_original_PE_typed_COFF_fields']==474,
         'original 43 prior whole source cases have changed physical PE/COFF counts')
    code,refs=reader.object_function(OBJ,SYMBOL)
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret','new VC7.1 original source lacks normal function RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'] and
         code[ret+4*tab['slots']:]==index,
         'new source physical original afterRET switch DATA not identical')
    jump=sorted((r for r in refs if ret<=r['offset']<ret+4*tab['slots']),key=lambda r:r['offset'])
    need(len(jump)==tab['slots'] and
         all(r['type']=='DIR32' and r['offset']==ret+4*i and
             r['addend']==0 and r['local_symbol_offset'] is not None
             for i,r in enumerate(jump)),
         'original game 60-slot jump label physical COFF fields no longer canonical')
    nslots=[int.from_bytes(nd[i*4:i*4+4],'little') for i in range(tab['slots'])]
    cslots=[r['local_symbol_offset'] for r in jump]
    need(switch.canonical_partitions(nslots)==switch.canonical_partitions(cslots),
         'genuine original first-switch default and repeated native handler partitions differ')
    ja=[int(x.op_str,16) for x in ins if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(original['default'],16) for x in nslots]==[x==ja[0] for x in cslots],
         'actual native default jump-handler slot targets changed')
    receipts=[];total_coff=0
    for case,(nxt,count,size,fields) in STATES.items():
        start,end=byaction[case],byaction[nxt]
        need(boss['address']<=start<end<boss['address']+boss['size'],
             f'original game case {case:#x} outside true complete 33293 CODE bytes')
        real=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
        ca,cb=cslots[index[case-0x320]],cslots[index[nxt-0x320]]
        need(0<=ca<cb<ret,'original complete native case source not inside normal C++ CODE')
        compiled=list(decoder.disasm(code[ca:cb],ca))
        need(real and compiled and real[0].address==start
             and real[-1].address+real[-1].size==end
             and compiled[0].address==ca
             and compiled[-1].address+compiled[-1].size==cb,
             f'original native physical 0x{case:X} entire action CODE range cropped or aliased')
        physical=genuine_native_COFF(real,compiled,refs,case)
        strict_original_policy(real,compiled,case,grammar)
        total_coff+=len(physical)
        receipts.append({'action':f'0x{case:X}',
                         'whole_original_native_x86_instructions':count,
                         'original_internal_CODE_bytes':size,
                         'true_PE_typed_COFF_fields':len(physical)})
        print(f'{case:#05x}: complete original {count}/{count} native GPR/x87/CFG instructions, '
              f'{size}/{size} actual inner CODE bytes and {len(physical)}/{fields} '
              'original PE typed zero-addend COFF fields',flush=True)
    need(len(receipts)==3 and total_coff==24 and
         sum(x['whole_original_native_x86_instructions'] for x in receipts)==296 and
         sum(x['original_internal_CODE_bytes'] for x in receipts)==1103,
         'three real original 385/386/387 game action totals differ')
    OUT.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(OBJ,OUT/'one-normal-Cpp-source.obj')
    if (BASE/'compiler.log').exists():shutil.copyfile(BASE/'compiler.log',OUT/'compiler.log')
    summary={'entire_native_giant':'0x004EBDA0',
             'complete_original_CODE_unaccepted':33293,
             'new_real_case_details':receipts,
             'new_actual_original_x86_instructions':296,
             'new_original_inner_CODE_bytes':1103,
             'new_typed_native_COFF_call_globals':24,
             'cumulative_real_original_game_action_cases':49,
             'cumulative_original_x86_instruction_roles':7109,
             'cumulative_original_inner_CODE_bytes_uncredited':26691,
             'cumulative_original_PE_typed_COFF_fields':498,
             'native_first_switch_DWORD_COFF_refs':60,
             'native_literal_sparse_index_bytes':198,
             'separate_afterret_DATA_shape':438}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F591 complete 49 real native game-action bodies, '
          '7109 original x86 instruction roles, 26691 original internal '
          'CODE bytes, 498 genuine typed original PE COFF fields; '
          'whole 33293-byte fighter giant STILL NONEXACT',flush=True)
    print('One affected VC7.1 original-shaped TU, no independent split '
          'or whole exact CODE/DATA and no all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('F591 original native game action 385/386/387 source verifier failed:',exc,file=sys.stderr)
        raise SystemExit(1)
