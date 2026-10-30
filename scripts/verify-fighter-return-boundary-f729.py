#!/usr/bin/env python3
"""F729: two original complete 1181B/348-x86 fighter 1F6/1F7 cases.

Cold-compile one full original-shaped 58KB fighter using actual game
C++ stage, contact, 7D/7E recoil and random sides. Verify both
bounded original native game interiors, all 70 original physically
typed PE/COFF fields (including shifted owned ordinals after real
x87 `FCOMP` vs source `FLD/FCOMPP`), the first corrected strict
`TEST AH,5; JP`, genuine EBP scratch and 1F4/1F5 original fields.
Native 200/201 remain 67/85 GPR-NONSTRICT; 2EF remains strict.
All 943 original afterRET bytes and 156 native DIR32 labels checked.
No clipped original code, inner-case credit or 943-unit cold replay.
"""
from __future__ import annotations
import difflib
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f729-fighter-return-boundary'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
NATIVE={0x1F6:(0x0054AB00,0x0054AF9D,1181,348,35,5704),
        0x1F7:(0x0054AF9D,0x0054B43A,1181,348,35,6054)}
# Extra real FLD/FCOMPP at original native x86 127 and 139.
GPR_DIFF={0x1F6:286,0x1F7:285}
SLOTS={0x1F6:('0xf8','0x6c'),0x1F7:('0xfc','0x70')}
# Every native symbol is a genuine PE-typed operand.
DESTINATIONS={
  0x00453E20:'ResetAt453E20',
  0x0065782C:'g_ThresholdAt0065782C',
  0x00658058:'g_ApproachAt00658058',
  0x0040FB40:'SetAuxActionAt40FB40',
  0x00454EE0:'ContactAt454EE0',
  0x00657874:'g_F699_SideOffsetAt00657874',
  0x00657884:'g_F699_SideEdgeAt00657884',
  0x0040FAC0:'SetNativeActionAt40FAC0',
  0x006583FC:'g_F728_PositiveDragAt006583FC',
  0x006581E0:'g_NewDragAt006581E0',
  0x0040FA30:'GetNativeActionAt40FA30',
  0x00453D40:'PrepareActionAt453D40',
  0x00657888:'g_ContactProjectionAt00657888',
  0x00453C80:'Spawn',
  0x00453A70:'SpawnDirectedAt453A70',
}
EXPECTED_EDITS=(('replace',127,128,127,129),
                ('replace',130,131,131,132),
                ('replace',139,140,140,142),
                ('replace',142,143,144,145))


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,relative):
    sp=importlib.util.spec_from_file_location(name,ROOT/relative)
    need(sp is not None and sp.loader is not None,'actual native verifier not installed: '+relative)
    mod=importlib.util.module_from_spec(sp)
    sys.modules[name]=mod
    sp.loader.exec_module(mod)
    return mod


def source_with_return_boundaries(src):
    for action in NATIVE:
        mark=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(mark)==1,
             f'old native 1F6/1F7 source placeholder absent for {action:#x}')
        macro=(f'#define F729_CASE 0x{action:X}\n'
             f'#define F729_STAGE14_X {"40.0f" if action==0x1F6 else "30.0f"}\n'
             f'#define F729_STAGE14_Y {"-20.0f" if action==0x1F6 else "-30.0f"}\n'
             f'#define F729_STAGE15_SHOT 0x{0x336 if action==0x1F6 else 0x337:X}\n'
             '#include "FighterBoundaryReturnF729.inc"\n'
             '#undef F729_CASE\n#undef F729_STAGE14_X\n'
             '#undef F729_STAGE14_Y\n#undef F729_STAGE15_SHOT')
        src=src.replace(mark,macro)
    need(src.count('#include "FighterBoundaryReturnF729.inc"')==2,
         'two genuine distinct original complete return-boundary actions missing')
    return src


def real_native_cases(reader,pe,real,f676,f598,by,ins,refs):
    rows=[]
    for action,(lo,hi,bytes_native,x86_native,count,source_ordinal) in NATIVE.items():
        next_action=0x1F7 if action==0x1F6 else 0x1F8
        need(by[action]==lo and by[next_action]==hi and hi-lo==bytes_native,
             'original complete 1F6/1F7 physical original PE bounds changed')
        native=list(real.disasm(reader.pe_bytes_at(pe,lo,bytes_native),lo))
        source=ins[source_ordinal:source_ordinal+350]
        need(len(native)==x86_native and len(source)==350
             and sum(x.size for x in native)==bytes_native
             and sum(x.size for x in source)==1183
             and native[-1].mnemonic==source[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'original whole physical {action:#x} source/nativex86 extent incorrect')
        expected_placements=f676.original_fields(native)
        actual=[r for r in refs if source[0].address<=r['offset']<source[-1].address+source[-1].size]
        need(len(expected_placements)==len(actual)==count,
             f'native {action:#x} all 35 original source fields missing')
        actual_fields=[]
        for (ordinal,target,mnemonic),reloc in zip(expected_placements,actual):
            owner=next((k for k,x in enumerate(source)
                        if x.address<=reloc['offset']<x.address+x.size),None)
            expected_owner=ordinal+int(ordinal>=127)+int(ordinal>=139)
            want=DESTINATIONS.get(target)
            if target==0x00453C80:
                want='SpawnAt453C80' if ordinal==254 else 'SpawnMixedAt453C80'
            need(want is not None
                 and reloc['type']==('REL32' if mnemonic=='call' else 'DIR32')
                 and reloc['addend']==0 and reloc['local_symbol_offset'] is None
                 and want in reloc['symbol']
                 and owner==expected_owner
                 and source[owner].mnemonic==mnemonic,
                 f'original {action:#x} native x86{ordinal} target {target:#x} actual source PE/COFF physical owner incorrect: {owner}')
            actual_fields.append({'original_instruction':ordinal,
                'compiler_instruction':owner,'original_target':f'0x{target:08X}',
                'physical_source_symbol':reloc['symbol']})
        changes=tuple((tag,a,b,c,e) for tag,a,b,c,e
                      in difflib.SequenceMatcher(a=[x.mnemonic for x in native],
                          b=[x.mnemonic for x in source],autojunk=False).get_opcodes()
                      if tag!='equal')
        need(changes==EXPECTED_EDITS
             and native[107].op_str==source[107].op_str=='ah, 5'
             and native[108].mnemonic==source[108].mnemonic=='jp'
             and native[127].mnemonic==native[139].mnemonic=='fcomp'
             and [x.mnemonic for x in source[127:129]]==['fld','fcompp']
             and [x.mnemonic for x in source[140:142]]==['fld','fcompp'],
             'original 1F6/1F7 strict threshold fix and real x87 two-FLD/FCOMPP negatives changed')
        source_slot,native_slot=SLOTS[action][1],SLOTS[action][0]
        for ni,ci in ((246,248),(247,249)):
            need(native[ni].mnemonic==source[ci].mnemonic
                 and f'[ebp - {native_slot}]' in native[ni].op_str
                 and f'[ebp - {source_slot}]' in source[ci].op_str,
                 f'original {action:#x} real integer-to-x87 scratch slot at native{ni} is incorrect')
        absolute={i for i,target,mn in expected_placements if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(source)))
               if a!=b and i not in absolute]
        need(len(wrong)==GPR_DIFF[action],
             f'original {action:#x} real GPR/x87 source operand negative changed')
        rows.append({'native_original_action':f'0x{action:X}',
             'original_entire_PE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
             'original_entire_native_CODE_B':bytes_native,
             'current_generated_entire_CODE_B':sum(x.size for x in source),
             'native_original_x86':x86_native,
             'current_source_x86':len(source),
             'all_original_physical_PE_COFF_fields':len(actual_fields),
             'actual_original_source_field_owners':actual_fields,
             'native_x87_and_branch_opcode_edit_blocks':changes,
             'normalized_original_GPR_negative_count':len(wrong),
             'original_real_scratch_EBP':native_slot,
             'current_source_real_scratch_EBP':source_slot,
             'original_case_byte_exact':False})
    need(ins[5704].mnemonic==ins[6054].mnemonic=='mov'
         and ins[6404].mnemonic=='mov'
         and ins[6404].op_str.endswith(', 0x1f9'),
         'native original 1F4->1F5->1F6->1F7->1F8 source order/boundary changed')
    return rows


def main():
    reader=load('f729_reader','scripts/compare-coff-function.py')
    acts=load('f729_actions','scripts/report-fighter-action-handlers.py')
    f676=load('f729_original_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f729_original_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f701=load('f729_physical_fields','scripts/verify-fighter-four-tier-volley-f701.py')
    f728=load('f729_f728','scripts/verify-fighter-random-arcs-f728.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    src,compiler=f728.source_for_complete_parent(reader,pe,real,boss,report,mapped)
    src=source_with_return_boundaries(src)
    obj=compiler.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-1F6-1F7.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-1F6-1F7.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,SYMBOL)
    emitted=[]
    for x in real.disasm(code,0):
        emitted.append(x)
        if x.mnemonic=='ret':break
    restored=real_native_cases(reader,pe,real,f676,f598,by,emitted,refs)
    previous=f728.case_evidence(reader,pe,real,f676,f598,f701,by,
                                 emitted,refs,following_native_1f6=True)
    after_ret=f728.complete_native_switch_DATA(reader,pe,real,boss,code,emitted,refs)
    upstream=f728.verify_prior_context_regression(reader,pe,real,f676,f598,
                                                   by,emitted,refs,boss)
    need([x['current_source_nonfield_GPR_CFG_differences'] for x in upstream]==[67,85,0]
         and after_ret['original_nonrelocation_afterRET_BYTES_equal']==319,
         'current source must NOT silently inherit old strict 200/201 or lose original 943B afterRET')
    receipt={'whole_original_fighter':'0x00543210',
         'entire_original_58KB_CODE_still_NONEXACT':boss['size'],
         'new_physically_verified_entire_game_actions':restored,
         'original_new_source_backed_internal_CODE_B_NOT_CREDITED':2362,
         'new_original_real_x86_instructions':696,
         'all_new_original_typed_PE_COFF_fields':70,
         'previous_1F4_1F5_complete_source_reverified':previous,
         'known_200_201_original_GPR_regression_and_strict_2EF':upstream,
         'entire_943B_original_native_afterRET_DATA_reverified':after_ret,
         'whole_original_game_function_byte_exact':False,
         'new_accepted_game_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F729 whole original fighter 1F6/1F7: 2x1181 native CODE B, '
          '2x348 native x86, 70 authentic physical typed source COFF fields '
          'verified in full parent; normal C++ emits 2x1183B/350 x86, '
          'first strict side-edge `<` restores original TEST AH,5/JP. '
          'Two authentic FCOMP memory operations per case remain extra '
          'FLD/FCOMPP, real x87 EBP -0xF8/-0xFC vs source '
          '-0x6C/-0x70 and 286/285 GPR-role mismatches: NONEXACT. '
          'Prior 1F4/1F5 original physical fields, true 200/201 67/85 '
          'GPR regressions, strict native 2EF, and all 156 DIR32 targets '
          'plus all 319 original sparse bytes of 943-byte afterRET DATA '
          'rechecked in SAME full C++ parent. No independent CODE credit '
          'and no 943-unit mass replay.')


if __name__=='__main__':
    main()
