#!/usr/bin/env python3
"""F590: three complete original 0x370/0x371/0x384 CharacterObject cases.

Pin genuine Japanese TH075 1.11 original entire 33293-byte giant CODE and
complete physical afterRET sparse jump DATA. Compile only ONE ordinary
VC7.1 C++ TU, independently verify all prior 43 real complete original
cases via F588, then check new 79/44/128 native x86 full case sources,
register/x87/CFG and 25 PE-grounded typed zero-addend COFF records.
The original 0x371 next physical real case is 0x384, not an invented
0x372; source0x384 has one genuine absolute byte MOVSX global
006714D0 and a verified DIR32 reference, never an ignored mismatch.
No standalone original case CODE credit or all-unit cold replay.
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
OUT=ROOT/'.analysis/f590-characterobject-guarded-source'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
STATES={0x370:(0x371,79,286,7),
        0x371:(0x384,44,156,4),
        0x384:(0x385,128,473,14)}
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
    nxt,count,size,fields=STATES[case]
    need(len(native)==len(candidate)==count and
         sum(x.size for x in native)==sum(x.size for x in candidate)==size
         and all(x.size==y.size for x,y in zip(native,candidate)),
         f'original full case {case:#x} physical x86 instruction/code size invalid')
    a=grammar.authentic_grammar(native,case)
    b=grammar.authentic_grammar(candidate,case)
    changes=[i for i,(x,y) in enumerate(zip(a,b)) if x!=y]
    if case==0x384:
        # The prior source grammar normalizes PE float DIR32 placeholders
        # but NOT this original MOVSX absolute BYTE global. Strictly
        # prove both the native operand and candidate zero/addend COFF
        # before allowing this sole expected source relocation placeholder.
        need(changes==[102] and native[102].mnemonic==candidate[102].mnemonic=='movsx'
             and native[102].op_str=='ecx, byte ptr [0x6714d0]'
             and candidate[102].op_str=='ecx, byte ptr [0]',
             f'original native case0x384 source must differ only in physically checked byte global 006714D0: {changes}')
        b[102]=a[102]
    else:
        need(not changes,
             f'full original native game source {case:#x} GPR/x87/CFG differs: {[(i,a[i],b[i]) for i in changes[:6]]}')
    need(a==b,
         'original source game case GPR/x87/branch grammar differs outside authentic native typed COFF fields')
    for ins in (native,candidate):
        if case==0x370:
            need(ins[3].mnemonic=='cmp' and ins[3].op_str.endswith(', 0x133')
                 and ins[9].mnemonic=='imul' and ins[9].op_str.endswith(', 0x104')
                 and ins[17].mnemonic=='fld' and
                 ins[53].mnemonic=='fmul'
                 and ins[58].mnemonic=='cmp' and ins[58].op_str.endswith(', 0x14')
                 and ins[59].mnemonic=='jle',
                 'original native 0x370 parent state/×260/float multiply/20-fade policy changed')
        elif case==0x371:
            need(ins[14].mnemonic=='mov' and ins[14].op_str.endswith('0x3f59999a')
                 and ins[16].mnemonic=='mov' and ins[16].op_str.endswith('0x3f59999a')
                 and ins[26].mnemonic=='mov' and ins[26].op_str.endswith('0x4e2')
                 and ins[28].mnemonic=='mov' and ins[28].op_str.endswith('0xc2820000')
                 and ins[31].mnemonic=='fsub',
                 'original 0x371 real .85f, 0x4E2 sprite, -65f and float subtraction changed')
        else:
            need(ins[2].mnemonic=='movsx' and ins[2].op_str.endswith('word ptr [eax + 0x3a0]')
                 and ins[4].mnemonic=='jg' and ins[35].mnemonic=='fmul'
                 and ins[40].mnemonic=='fmul'
                 and ins[45].mnemonic=='fsub'
                 and ins[77].mnemonic=='fcomp' and
                 ins[91].mnemonic=='push' and ins[91].op_str=='0x388'
                 and ins[95].mnemonic=='push' and ins[95].op_str=='8'
                 and ins[99].mnemonic=='push' and ins[99].op_str=='0x385'
                 and ins[105].mnemonic=='push' and ins[105].op_str=='0x38e',
                 'native actual parent guard 3A0, two float multipliers, effect 0x388, states 0x385/0x38E changed')
    return True


def main():
    reader=load('f590_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f590_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=load('f590_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    grammar=load('f590_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    prior=load('f590_previous',ROOT/'scripts/verify-characterobject-three-late-actions-f588.py')
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
    need('F588/F590' in src and all(src.count(f'case 0x{x:X}:')==1 for x in STATES)
         and 'case 0x3E3: {' in src,
         'source must implement all three real native cases, leave 385 diagnostic')
    # Exactly one affected VC7.1 TU freshly compiled by original-PE
    # backed F588 check, also checking all 43 previous native actions.
    prior.main()
    old=json.loads((ROOT/'.analysis/f588-characterobject-three-source/summary.json').read_text())
    need(old['total_physically_real_game_action_cases']==43
         and old['total_original_x86_instruction_roles']==6562
         and old['total_original_inner_CODE_bytes_uncredited']==24673
         and old['total_native_typed_COFF_call_global']==449,
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
    need(len(receipts)==3 and total_coff==25 and
         sum(x['whole_original_native_x86_instructions'] for x in receipts)==251 and
         sum(x['original_internal_CODE_bytes'] for x in receipts)==915,
         'three real original 370/371/384 game action totals differ')
    OUT.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(OBJ,OUT/'one-normal-Cpp-source.obj')
    if (BASE/'compiler.log').exists():shutil.copyfile(BASE/'compiler.log',OUT/'compiler.log')
    summary={'entire_native_giant':'0x004EBDA0',
             'complete_original_CODE_unaccepted':33293,
             'new_real_case_details':receipts,
             'new_actual_original_x86_instructions':251,
             'new_original_inner_CODE_bytes':915,
             'new_typed_native_COFF_call_globals':25,
             'cumulative_real_original_game_action_cases':46,
             'cumulative_original_x86_instruction_roles':6813,
             'cumulative_original_inner_CODE_bytes_uncredited':25588,
             'cumulative_original_PE_typed_COFF_fields':474,
             'native_first_switch_DWORD_COFF_refs':60,
             'native_literal_sparse_index_bytes':198,
             'separate_afterret_DATA_shape':438}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F590 complete 46 real native game-action bodies, '
          '6813 original x86 instruction roles, 25588 original internal '
          'CODE bytes, 474 genuine typed original PE COFF fields; '
          'whole 33293-byte fighter giant STILL NONEXACT',flush=True)
    print('One affected VC7.1 original-shaped TU, no independent split '
          'or whole exact CODE/DATA and no all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('F590 original native game action 370/371/384 source verifier failed:',exc,file=sys.stderr)
        raise SystemExit(1)
