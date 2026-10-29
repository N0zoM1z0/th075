#!/usr/bin/env python3
"""F587: one actual 397-insn, four-state CharacterObject game action 0x34C.

Entire Japanese original TH075 v1.11 33,293-byte fighter CODE hash and
physical first-switch jump DATA must pass the registered original reader.
Compile ONE selected ordinary VC7.1 C++ switch, first verify previous
39 complete real cases using F586's source/PE/COFF proof, then verify the
*whole* native 0x34C original case (397 x86/1529 bytes, 25 genuine typed
COFF fields) with complete register/x87/CFG/branch and every physical
source relocation. It contains distinct original 0x198/19A/19C/19D
parent state effects 0x322..325; don't alias or fabricate game code.
The enriched single C++ body also moves old 0x331 temporary spans to
native **byte-width-identical** disp32 source locations, not byte-exact
original EBP offsets. No split/whole exact function credit and no
all-unit cold replay.
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
ADDRESS=0x004EBDA0
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
BASE=ROOT/'.analysis/f583-characterobject-state-leaves-source'
OBJ=BASE/'CharacterObjectF583.obj'
OUT=ROOT/'.analysis/f587-characterobject-four-way-source'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
CALLS={
    0x0045B830:('REL32','ResetAt45B830'),
    0x00453A70:('REL32','SpawnAt453A70'),
    0x006590A8:('DIR32','gParentYAt006590A8'),
    0x00658264:('DIR32','gParentYExtraAt00658264'),
    0x0040FB40:('REL32','SetStateAt40FB40'),
    0x0040FBB0:('REL32','ResetStateAt40FBB0'),
    0x00659730:('DIR32','gMulDoubleAt00659730'),
    0x006583FC:('DIR32','gAddAt006583FC'),
    0x0040FA30:('REL32','GetStateAt40FA30'),
    0x00455580:('REL32','RandomAt455580'),
    0x00453D40:('REL32','ModifyAt453D40'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(tag,p):
    spec=importlib.util.spec_from_file_location(tag,p)
    need(spec is not None and spec.loader is not None,f'missing original PE/COFF verifier {p}')
    module=importlib.util.module_from_spec(spec)
    sys.modules[tag]=module
    spec.loader.exec_module(module)
    return module


def physical_fields(original,compiled,refs):
    start,end=compiled[0].address,compiled[-1].address+compiled[-1].size
    actual=[r for r in refs if start<=r['offset']<end]
    observed=[]
    for i,x in enumerate(original):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            dtype='REL32';dest=int(x.op_str,16)
        elif x.mnemonic.startswith('f') and 'ptr [0x' in x.op_str:
            dtype='DIR32';dest=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
        else:continue
        need(dest in CALLS, f'original whole 0x34C new PE callee/float target {dest:#x} at ordinal {i}')
        expected_type,symbol=CALLS[dest]
        need(dtype==expected_type, f'original native source target kind changed at {i}')
        if dest==0x00453A70 and i in (264,306,348,391):
            symbol='SpawnMovedAt453A70'
        y=compiled[i]
        need(x.mnemonic==y.mnemonic, f'original 0x34C physical COFF ordinal moved: {i}')
        found=[r for r in actual if y.address<=r['offset']<y.address+y.size]
        need(len(found)==1 and found[0]['type']==dtype
             and found[0]['addend']==0 and symbol in found[0]['symbol'],
             f'not original source physical typed COFF PE target/callee at {i}: {found}')
        observed.append((i,dtype,dest,symbol))
    need(len(observed)==len(actual)==25,
         'original entire game action0x34C has not exactly 25 original typed COFF refs')
    return observed


def native_four_way_policy(native,candidate):
    need(len(native)==len(candidate)==397 and
         sum(x.size for x in native)==sum(x.size for x in candidate)==1529 and
         all(x.size==y.size for x,y in zip(native,candidate)),
         'entire original 397-instruction 1529-byte native source body geometry wrong')
    for ins in (native,candidate):
        # Original has exactly four state tests, with one intentionally
        # different stage threshold per state. The four effect IDs and
        # signed random offsets must keep their physical original order.
        for ordinal,imm in ((60,0x198),(70,0x19C),(80,0x19A),(90,0x19D),
                            (116,0x19A),(230,0x198),(272,0x19A),
                            (314,0x19C),(356,0x19D)):
            need(ins[ordinal].mnemonic=='cmp'
                 and int(ins[ordinal].op_str.rsplit(', ',1)[-1],0)==imm,
                 f'original actor 0x34C parent state at ordinal {ordinal} must be {imm:#x}')
        need(all(ins[ordinal].mnemonic=='push' and
                 int(ins[ordinal].op_str,0)==effect
                 for ordinal,effect in ((261,0x322),(303,0x323),(345,0x324),(388,0x325))),
             'native source four distinct x87 random effect IDs 0x322..0x325 changed')
        need(all(ins[ordinal].mnemonic=='call'
                 for ordinal in (238,264,280,306,322,348,364,391)),
             'native four independent random/spawn parent call pairs absent')
        need(all(ins[ordinal].mnemonic=='push' and
                 ins[ordinal].op_str=='6'
                 for ordinal in (265,307,349,392)),
             'native four parent effect-modification callbacks no longer six')
        need(ins[365].mnemonic=='neg' and ins[365].op_str=='eax'
             and ins[366].mnemonic=='sub' and ins[366].op_str=='eax, 0x1e',
             'native original state0x19D random sign and negative 30 offset differ')
        need(ins[101].mnemonic=='imul' and ins[101].op_str.endswith(', 0x3c')
             and ins[110].mnemonic=='fadd'
             and ins[121].mnemonic=='fadd',
             'original signed direction times60 and two parent y x87 globals absent')
    return True


def main():
    reader=load('f587_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f587_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=load('f587_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    grammar=load('f587_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    prior=load('f587_old39',ROOT/'scripts/verify-characterobject-late-stage-actions-f586.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ADDRESS)
    need(boss['size']==33293 and boss['postret_size']==438 and boss['jump_count']==1,
         'native Japanese whole fighter giant code/postRET data original shape changed')
    original,rows=actions.report_boss(reader,pe,decoder,boss)
    byaction={r['action']:int(r['handler'],16) for r in rows}
    table=boss['tables'][0]
    need(table['slots']==60 and table['map_length']==198,
         'original native compressed first-switch slot shape changed')
    ndense=reader.pe_bytes_at(pe,table['dense_addr'],table['slots']*4)
    idx=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(hashlib.sha256(ndense).hexdigest()==table['dense_sha'] and
         hashlib.sha256(idx).hexdigest()==table['map_sha'],
         'genuine original Japanese dense/sparse native table hashes differ')
    src=SOURCE.read_text()
    need('F586/F587' in src and src.count('case 0x34C: {')==1
         and 'case 0x388: g_FighterProbeMarker = 905; break;' in src,
         'C++ source must implement complete real 0x34C action and retain next unfinished case diagnostic')
    # F586 re-checks every previous full action and compiles ONE VC7.1 TU.
    prior.main()
    old=json.loads((ROOT/'.analysis/f586-characterobject-late-stage-source/summary.json').read_text())
    need(old['all_complete_original_cases']==39 and
         old['all_original_native_x86_instruction_roles']==5651 and
         old['all_original_inner_CODE_bytes_uncredited']==21245 and
         old['all_typed_original_PE_call_global_COFF_fields']==389 and
         old['new_original_frame_width_surplus_0x331']==0,
         'F586 previous entire 39 native games or real 0x331 new disp32 context changed')
    code,refs=reader.object_function(OBJ,SYMBOL)
    cins=[]
    for x in decoder.disasm(code,0):
        cins.append(x)
        if x.mnemonic=='ret':break
    need(cins and cins[-1].mnemonic=='ret', 'selected source has no normal RET')
    ret=cins[-1].address+cins[-1].size
    need(len(code)-ret==boss['postret_size'] and
         code[ret+4*table['slots']:]==idx,
         'complete physical native original after-RET compressed DATA mismatch')
    fields=sorted((r for r in refs if ret<=r['offset']<ret+4*table['slots']),
                  key=lambda r:r['offset'])
    need(len(fields)==table['slots'] and all(x['type']=='DIR32'
         and x['offset']==ret+4*i and x['addend']==0 and x['local_symbol_offset'] is not None
         for i,x in enumerate(fields)),
         'whole original native switch physical 60 DWORD zero-addend relocations differ')
    native_dense=[int.from_bytes(ndense[4*i:4*i+4],'little') for i in range(table['slots'])]
    candidate_dense=[r['local_symbol_offset'] for r in fields]
    need(switch.canonical_partitions(native_dense)==switch.canonical_partitions(candidate_dense),
         'original repeated/default dense native handler partitions changed')
    ja=[int(x.op_str,16) for x in cins if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(original['default'],16) for x in native_dense]==[x==ja[0] for x in candidate_dense],
         'original shared default switch physical targets changed')
    start,end=byaction[0x34C],byaction[0x34D]
    need(boss['address']<=start<end<boss['address']+boss['size'],
         'original whole native 0x34C CODE range escapes containing boss')
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    cs,ce=candidate_dense[idx[0x34C-0x320]],candidate_dense[idx[0x34D-0x320]]
    need(0<=cs<ce<ret,'candidate source real case cropped or leaks into postRET switch DATA')
    candidate=list(decoder.disasm(code[cs:ce],cs))
    need(native and candidate and native[0].address==start and
         native[-1].address+native[-1].size==end and
         candidate[0].address==cs and candidate[-1].address+candidate[-1].size==ce,
         'original/compiled game 0x34C whole CODE boundaries not contiguous')
    original_fields=physical_fields(native,candidate,refs)
    a,b=grammar.authentic_grammar(native,0x34C),grammar.authentic_grammar(candidate,0x34C)
    need(a==b,
         f'original 397 native x86 GPR/x87/branch source differs: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(a,b)) if x!=y][:6]}')
    native_four_way_policy(native,candidate)
    OUT.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(OBJ,OUT/'selected-real-source.obj')
    if (BASE/'compiler.log').exists():shutil.copyfile(BASE/'compiler.log',OUT/'compiler.log')
    summary={'entire_original_boss':'0x004EBDA0',
             'whole_original_CODE_unaccepted':33293,
             'new_complete_real_game_action':'0x34C',
             'new_actual_native_x86_instructions':397,
             'new_original_internal_CODE_bytes':1529,
             'new_typed_physical_COFF_fields':len(original_fields),
             'all_complete_original_game_actions':40,
             'all_original_x86_instruction_roles':6048,
             'all_original_internal_CODE_bytes_uncredited':22774,
             'all_authentic_typed_COFF_call_global_fields':414,
             'physical_native_jump_DWORD_COFF_fields':60,
             'literal_original_sparse_index_bytes':198,
             'distinct_afterret_DATA_shape_bytes':438,
             'original_0x331_now_byte_width_equal':True}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('0x34c: COMPLETE original 397-instruction/1529-byte native x86 '
          f'case source and {len(original_fields)}/25 actual typed COFF references '
          'with strict GPR/x87/CFG instruction order',flush=True)
    print('F587 40 real complete native game action bodies, 6048 original '
          'x86 instruction roles, 22774 internal original CODE bytes and '
          '414 true physical PE-grounded typed COFF fields; complete '
          '33293-byte giant still NONEXACT',flush=True)
    print('One selected original VC7.1 C++ TU, no whole/split exact '
          'CODE or DATA, no all-unit cold replay or Oracle receipt')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as exc:
        print('TH075 original native four-way game action F587 verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
