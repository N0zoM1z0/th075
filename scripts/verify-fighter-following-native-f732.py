#!/usr/bin/env python3
"""F732: original 1FA/1FB/1FE/1FF actual full source in latest fighter.

Rebuild ONLY one original-shaped 58KB VC7.1 giant. All 4 entire
physical native case bounds, 1942 original CODE B/562 original x86,
52 real typed PE/COFF fields, 1FA genuinely widened EBP->x87
MOV/FILD (actual original -0x110 vs source -0x84) and strict
1FE/1FF float clamp (native TEST AH,5; JP) are verified.
Old F666 diagnostic source is preserved separately, not rewritten.
Original 200/201 nonfield GPR source regresses from 0 to 67/85
in this whole parent; never inherit previous strict case credit.
All prior 1F4..1F8 actual native contexts, all 943 original
DATA and 156 physical jump targets checked in SAME new parent.
No independent internal-case game FUNCTION exact credit or full
943-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f732-fighter-four-following'
ACTOR=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ'
CASES=(0x1FA,0x1FB,0x1FE,0x1FF)
NEXT={0x1FA:0x1FB,0x1FB:0x1FE,0x1FE:0x1FF,0x1FF:0x200}
NATIVE={0x1FA:(0x0054B9F9,0x0054BB18,287,82,9,6828,50),
        0x1FB:(0x0054BB18,0x0054BD73,603,174,15,6910,111),
        0x1FE:(0x0054BD73,0x0054BF81,526,153,14,7084,96),
        0x1FF:(0x0054BF81,0x0054C18F,526,153,14,7237,96)}
SOURCE_NEXT_200_START=7390
GPR_CURRENT_CONTEXT={0x200:67,0x201:85,0x2EF:0}


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,relative):
    sp=importlib.util.spec_from_file_location(name,ROOT/relative)
    need(sp is not None and sp.loader is not None,
         'original PE or VC7.1 source checker not installed: '+relative)
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def whole_source_with_following(src):
    # Historical F666 source was a real diagnostic alternative, but it
    # used the incorrect >= comparator and a shallow x87 scratch slot
    # in its older compiler parent. F732 leaves it unchanged.
    anchor='extern float g_SlowPositiveDragAt006578C0;'
    need(src.count(anchor)==1,'native 6578C0 original source global declaration changed')
    declarations=('extern float g_ShotPositiveDragAt00659A10;\n'
       'extern float g_SpeedClampAt00657CF8;\n'
       'extern float g_RisingGravityAt0065747C;\n'
       'extern float g_RisingDragAt006581E0;\n'
       'extern float g_BounceScaleAt006583FC;\n'
       'extern float g_FloatMulAt00657874;\n'
       'extern float g_FloatAddAt00657CBC;')
    src=src.replace(anchor,anchor+'\n'+declarations)
    for action in CASES:
        mark=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(mark)==1,
             f'native original action {action:#x} placeholder missing in complete C++ source')
        src=src.replace(mark,
            '#include "FighterFollowingNativeF732.inc"' if action==0x1FA else '')
    need(src.count('#include "FighterFollowingNativeF732.inc"')==1,
         'four complete original actions must be loaded exactly once')
    return src


def verify_physical_actions(reader,pe,dec,f676,f701,f598,f666,by,ins,refs):
    results=[]
    for action in CASES:
        start,end,native_bytes,nx,nfields,source_start,expected_gpr=NATIVE[action]
        need(by[action]==start and by[NEXT[action]]==end
             and end-start==native_bytes,
             f'original complete action {action:#x} genuine physical 1FA..200 extent changed')
        original=list(dec.disasm(reader.pe_bytes_at(pe,start,native_bytes),start))
        generated=ins[source_start:source_start+nx]
        need(len(original)==len(generated)==nx
             and sum(x.size for x in original)==sum(x.size for x in generated)==native_bytes
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(original,generated))
             and original[-1].mnemonic==generated[-1].mnemonic=='jmp'
             and original[-1].op_str=='0x5515c2',
             f'whole original {action:#x} source native 287/603/526 mnemonic, length or tail wrong')
        physical=f676.original_fields(original)
        fields=f701.compare_typed_fields(physical,generated,refs,f666.SYMBOLS,
                                         tuple(i for i,_,_ in physical))
        need(len(physical)==len(fields)==nfields,
             f'original {action:#x} {nfields} authentic source owned PE field targets missing')
        absolute={i for i,target,mnemonic in physical if mnemonic!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(original),
                                              f598.normalized(generated)))
               if a!=b and i not in absolute]
        need(len(wrong)==expected_gpr and wrong[:2]==[0,1],
             f'original {action:#x} actual GPR/CFG differences changed: {wrong[:9]}')
        if action==0x1FA:
            # Native −0x110 and source −0x84 are SIX-BYTE operands,
            # unlike F666's old native 6B vs generated 3B. Source width
            # recovery is real but still wrong physical EBP content.
            for ordinal,mnemonic in ((16,'mov'),(17,'fild')):
                native,generated_ins=original[ordinal],generated[ordinal]
                need(native.size==generated_ins.size==6
                     and native.mnemonic==generated_ins.mnemonic==mnemonic
                     and '[ebp - 0x110]' in native.op_str
                     and '[ebp - 0x84]' in generated_ins.op_str,
                     f'original 1FA x86{ordinal} real native 6B C++ stack width recovery lost')
        if action in (0x1FE,0x1FF):
            need(original[47].mnemonic==generated[47].mnemonic=='test'
                 and original[47].op_str==generated[47].op_str=='ah, 5'
                 and original[48].mnemonic==generated[48].mnemonic=='jp'
                 and original[45].mnemonic==generated[45].mnemonic=='fcomp',
                 f'original {action:#x}: strict native POS < 00657CF8 not restored')
        results.append({'original_physical_game_action':f'0x{action:X}',
         'original_PE_interval':[f'0x{start:08X}',f'0x{end:08X}'],
         'original_entire_CODE_B':native_bytes,
         'generated_entire_CODE_B':sum(x.size for x in generated),
         'original_and_source_full_ordered_x86_mnemonic_widths':nx,
         'original_physical_zero_addend_typed_PE_COFF_fields':len(fields),
         'native_normalized_nonfield_GPR_CFG_positively_unresolved':len(wrong),
         'current_compiler_case_byte_exact':False})
    end= NATIVE[0x1FF][5]+NATIVE[0x1FF][3]
    need(end==SOURCE_NEXT_200_START and ins[end].mnemonic=='mov'
         and '[ebp - 0x28]' in ins[end].op_str,
         'original real 1FA->1FB->1FE->1FF->200 C++ physical source order changed')
    return results


def verify_context_gpr(reader,pe,dec,f676,f598,by,ins,refs,boss):
    ret=ins[-1].address+ins[-1].size
    native_data=reader.pe_bytes_at(pe,ACTOR+boss['size'],boss['postret_size'])
    byswitch={}
    for r in refs:
        if r['offset']<ret:continue
        off=r['offset']-ret
        native_target=int.from_bytes(native_data[off:off+4],'little')
        byswitch.setdefault(native_target,r['local_symbol_offset'])
    results=[]
    for action,expected in GPR_CURRENT_CONTEXT.items():
        start=by[action]
        end=min(i for i in by.values() if i>start)
        native=list(dec.disasm(reader.pe_bytes_at(pe,start,end-start),start))
        need(start in byswitch,'original native context action missing in afterRET jump table')
        index=next((i for i,x in enumerate(ins) if x.address==byswitch[start]),None)
        need(index is not None,'actual C++ context source jump label must align to original x86')
        source=ins[index:index+len(native)]
        fields=f676.original_fields(native)
        newrefs=[r for r in refs if source[0].address<=r['offset']<source[-1].address+source[-1].size]
        absfields={i for i,target,mnemonic in fields if mnemonic!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(source)))
               if a!=b and i not in absfields]
        need(len(wrong)==expected and len(fields)==len(newrefs)
             and len(native)==len(source)
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(native,source)),
             f'original case {action:#x} current C++ GPR regression is not historically transferrable')
        results.append({'original_game_internal_case':f'0x{action:X}',
             'original_entire_physical_CODE_B':end-start,
             'original_x86_positions':len(native),
             'native_PE_COFF_real_field_count':len(fields),
             'this_parent_real_GPR_CFG_differences':len(wrong),
             'source_context_strict_nonfield_GPR':not wrong})
    return results


def main():
    reader=load('f732_reader','scripts/compare-coff-function.py')
    acts=load('f732_actions','scripts/report-fighter-action-handlers.py')
    f676=load('f732_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f701=load('f732_typed','scripts/verify-fighter-four-tier-volley-f701.py')
    f598=load('f732_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f666=load('f732_old','scripts/verify-fighter-preceding-stage-controls-f666.py')
    f728=load('f732_728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f732_729','scripts/verify-fighter-return-boundary-f729.py')
    f731=load('f732_731','scripts/verify-fighter-aim-return-f731.py')
    pe=reader.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    source,compiler=f728.source_for_complete_parent(reader,pe,dec,boss,report,mapped)
    source=f729.source_with_return_boundaries(source)
    source=f731.source_with_aim_return(source)
    source=whole_source_with_following(source)
    obj=compiler.compile_whole_parent(source)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-1FA-1FF.cpp').write_text(source)
    shutil.copyfile(obj,OUT/'Boss00543210-1FA-1FF.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,SYMBOL)
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    restored=verify_physical_actions(reader,pe,dec,f676,f701,f598,f666,by,ins,refs)
    before=f731.verify_complete_native_1f8(reader,pe,dec,f676,f729,by,ins,refs,
                                           following_native_1fa=True)
    prior729=f729.real_native_cases(reader,pe,dec,f676,f598,by,ins,refs,
                                      following_native_1f8=True)
    prior728=f728.case_evidence(reader,pe,dec,f676,f598,f701,by,ins,refs,
                               following_native_1f6=True)
    current=verify_context_gpr(reader,pe,dec,f676,f598,by,ins,refs,boss)
    full_data=f728.complete_native_switch_DATA(reader,pe,dec,boss,code,ins,refs)
    need(len(restored)==4
         and sum(x['original_entire_CODE_B'] for x in restored)==1942
         and sum(x['original_physical_zero_addend_typed_PE_COFF_fields'] for x in restored)==52
         and [x['this_parent_real_GPR_CFG_differences'] for x in current]==[67,85,0]
         and full_data['original_nonrelocation_afterRET_BYTES_equal']==319,
         'all four genuine 1FA/1FB/1FE/1FF and current 200/201 true regressions not attested')
    receipt={'entire_original_boss':'0x00543210',
      'original_whole_game_function_CODE_BYTES_still_NONEXACT':boss['size'],
      'original_complete_physical_actions':restored,
      'original_internal_source_backed_CODE_B_NOT_CREDITED':1942,
      'original_native_x86_mnemonics_and_widths_all_equal':562,
      'original_52_physically_typed_source_fields':52,
      'old_1F8_original_case_and_remaining_x87_negatives':before,
      'old_1F6_1F7_original_case_context':prior729,
      'old_1F4_1F5_original_context':prior728,
      'new_Cpp_parent_register_phase_negative':current,
      'independent_original_943B_afterRET_DATA':full_data,
      'whole_original_GAME_function_byte_exact':False,
      'new_accepted_authored_GAME_function_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F732 new real native original 00543210 source-context 1FA/1FB/1FE/1FF: '
          '287/603/526/526 native original CODE B, 82/174/153/153 x86 '
          'identical real mnemonic and width positions, all 52 authentic '
          'typed PE/COFF fields at original ordinal. Original `1FA` scratch '
          'now naturally 6B native width in full original-shaped VC7.1 giant '
          '(-0x110 native vs -0x84 actual compiler), and both 1FE/1FF '
          'corrected real strict `<` produce TEST AH,5/JP, not old >=/AH1. '
          'Genuine GPR role errors 50/111/96/96: NONSTRICT. Previous '
          'original 1F4-1F8 cases physically rechecked, 200/201 GPR '
          'regress 0->67/85 and 2EF remains GPR strict. Entire original '
          '943B afterRET DATA with all 156 instruction-aligned native/source '
          'DIR32 and 319 sparse bytes verified; no complete original game '
          'CODE accepted or 943-unit cold replay.')


if __name__=='__main__':
    main()
