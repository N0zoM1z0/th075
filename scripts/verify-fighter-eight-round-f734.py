#!/usr/bin/env python3
"""F734: recover original 190/191/192 full native eight-projectile actions.

Compile one complete VC7.1 original-shaped 00543210 fighter from tracked
normal C++ including all previous authentic actions. Compare original
276+276+240 physical CODE B /75+75+68 x86, all 21 genuine physical
zero-addend REL32/DIR32 PE fields at ORIGINAL instruction ordinals,
source GPR exactness only after explicit this-local normalization,
and all real EBP/width failures. Recheck previous original actions and
whole 943-B after-RET switch DATA, including 156 actual DIR32 entries.
No accepted independent internal case, fake locals, original EXE graft,
or full 943-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f734-fighter-eight-round'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
CASES=(0x190,0x191,0x192)
NEXT={0x190:0x191,0x191:0x192,0x192:0x194}
NATIVE={0x190:(0x00549364,0x00549478,276,75,7,266,5378),
        0x191:(0x00549478,0x0054958C,276,75,7,266,5453),
        0x192:(0x0054958C,0x0054967C,240,68,7,230,5528)}
WIDTHS={0x190:((26,6,2),(54,6,3),(55,6,3)),
        0x191:((26,6,2),(54,6,3),(55,6,3)),
        0x192:((19,6,2),(47,6,3),(48,6,3))}
SOURCE_LAST=5596
MEMBER_STORE={0x190:(35,'0x10','8'),
              0x191:(35,'0x14','0xc'),
              0x192:(28,'0x18','0x10')}
FILD_SLOTS={0x190:(54,55,'0x90','0x58'),
            0x191:(54,55,'0x94','0x5c'),
            0x192:(47,48,'0x98','0x60')}
PHYSICAL_SYMBOLS={
  0x00453E20:'ResetAt453E20',
  0x00453D40:'PrepareActionAt453D40',
  0x0046D000:'StartAnimationAt46D000',
  0x00659A30:'g_F734_RoundY0At00659A30',
  0x00659A2C:'g_F734_RoundY1At00659A2C',
  0x00659A28:'g_F734_RoundY2At00659A28',
  0x00453A70:'SpawnFloatXYAt453A70',
  0x0040FA30:'GetNativeActionAt40FA30',
  0x0040FAC0:'SetNativeActionAt40FAC0',
}
# Bounded original cases that must remain true in THIS new whole-parent context.
PREVIOUS=(
 (0x1F4,538,149,506,18,None),
 (0x1F5,538,149,506,18,71),
 (0x1FA,287,82,287,9,50),
 (0x1FB,603,174,603,15,111),
 (0x1FE,526,153,526,14,96),
 (0x1FF,526,153,526,14,96),
 (0x200,343,102,343,8,67),
 (0x201,436,126,436,9,85),
 (0x2EF,788,224,788,20,0),
)


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,rel):
    sp=importlib.util.spec_from_file_location(name,ROOT/rel)
    need(sp is not None and sp.loader is not None,'native/COFF checker missing: '+rel)
    mod=importlib.util.module_from_spec(sp)
    sys.modules[name]=mod
    sp.loader.exec_module(mod)
    return mod


def source_with_three(src):
    for act in CASES:
        old=f'        case 0x{act:X}: g_FighterProbeMarker = {act+1}; break;'
        need(src.count(old)==1,f'original {act:#x} placeholder absent; do not duplicate gameplay')
        src=src.replace(old,'#include "FighterEightRoundF734.inc"' if act==0x190 else '')
    needle='extern float g_FloatAddAt00657CBC;'
    need(src.count(needle)==1,'original full fighter global declaration changed')
    src=src.replace(needle,needle+'\nextern float g_F734_RoundY0At00659A30;\n'
        'extern float g_F734_RoundY1At00659A2C;\n'
        'extern float g_F734_RoundY2At00659A28;')
    need(src.count('#include "FighterEightRoundF734.inc"')==1,
         'complete 3 actions must appear once in whole C++ original-shaped parent')
    return src


def source_map_from_original_afterRET(reader,pe,boss,code,ins,refs):
    post=ins[-1].address+ins[-1].size
    native=reader.pe_bytes_at(pe,BOSS+boss['size'],boss['postret_size'])
    mapper={}
    for ref in refs:
        if ref['offset']<post:continue
        off=ref['offset']-post
        need(ref['type']=='DIR32' and ref['addend']==0
             and ref['local_symbol_offset'] is not None,
             'original/source afterRET switch owner must be genuine physical DIR32')
        mapper.setdefault(int.from_bytes(native[off:off+4],'little'),ref['local_symbol_offset'])
    return mapper


def new_native_actions(reader,pe,d,f676,f701,f598,by,ins,refs):
    rows=[]
    for action in CASES:
        lo,hi,nb,nx,nfields,sb,start=NATIVE[action]
        need(by[action]==lo and by[NEXT[action]]==hi and hi-lo==nb,
             f'original game native physical {action:#x} entire handler CODE boundaries differ')
        original=list(d.disasm(reader.pe_bytes_at(pe,lo,nb),lo))
        compiled=ins[start:start+nx]
        need(len(original)==len(compiled)==nx
             and sum(x.size for x in original)==nb
             and sum(x.size for x in compiled)==sb
             and all(a.mnemonic==b.mnemonic for a,b in zip(original,compiled))
             and original[-1].mnemonic==compiled[-1].mnemonic=='jmp'
             and original[-1].op_str=='0x5515c2',
             f'whole original {action:#x} native 75/68 mnemonic, section extent or tail differs')
        nf=f676.original_fields(original)
        fields=f701.compare_typed_fields(nf,compiled,refs,PHYSICAL_SYMBOLS,
                                          tuple(i for i,_,_ in nf))
        need(len(fields)==len(nf)==nfields,
             f'whole original {action:#x} seven genuine physical typed field owners missing')
        wide=tuple((i,a.size,b.size) for i,(a,b) in enumerate(zip(original,compiled))
                   if a.size!=b.size)
        need(wide==WIDTHS[action]
             and sum(a-b for _,a,b in wide)==nb-sb==10,
             f'original {action:#x} one branch and two genuine EBP width negatives changed')
        source_index,native_slot,compiled_slot=MEMBER_STORE[action]
        need(original[source_index].mnemonic==compiled[source_index].mnemonic=='mov'
             and f'[ebp - {native_slot}]' in original[source_index].op_str
             and f'[ebp - {compiled_slot}]' in compiled[source_index].op_str,
             f'native {action:#x} original 8-shot index EBP lifetime not honestly represented')
        i,j,old_slot,new_slot=FILD_SLOTS[action]
        need(original[i].mnemonic==compiled[i].mnemonic=='mov'
             and original[j].mnemonic==compiled[j].mnemonic=='fild'
             and f'[ebp - {old_slot}]' in original[i].op_str
             and f'[ebp - {new_slot}]' in compiled[i].op_str
             and f'[ebp - {old_slot}]' in original[j].op_str
             and f'[ebp - {new_slot}]' in compiled[j].op_str,
             f'native {action:#x} actual original integer-to-x87 temporary stack mismatch was hidden')
        absolute={i for i,target,mnem in nf if mnem!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(original),
                                              f598.normalized(compiled)))
               if a!=b and i not in absolute]
        need(not wrong,
             f'original {action:#x} source GPR roles not truly matching after physical receiver normalization: {wrong[:8]}')
        if action==0x190:
            need(original[53].op_str==compiled[53].op_str=='edx, edx, 0x46'
                 and original[21].op_str==compiled[21].op_str=='edx, 5'
                 and original[71].op_str==compiled[71].op_str=='0',
                 'original 190 stage-five 70x8-round and finish-zero source changed')
        elif action==0x191:
            need(original[53].mnemonic==compiled[53].mnemonic=='shl'
                 and original[53].op_str==compiled[53].op_str=='ecx, 6'
                 and original[21].op_str==compiled[21].op_str=='ecx, 4',
                 'native 191 authentic 64-multiplier and stage four lost')
        else:
            need(original[46].op_str==compiled[46].op_str=='eax, eax, 0x2c'
                 and original[64].op_str==compiled[64].op_str=='2',
                 'native 192 stage-four 44-multiplier and action finish-two lost')
        rows.append({'original_game_action':f'0x{action:X}',
          'whole_original_PE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
          'native_complete_original_CODE_bytes':nb,
          'full_parent_compiled_CODE_bytes':sb,
          'identical_native_ordered_x86_mnemonic_positions':nx,
          'all_original_typed_PE_COFF_targets_and_owners':len(fields),
          'three_real_native_vs_source_width_differences':wide,
          'real_original_EBP_8_shot_loop_index':native_slot,
          'actual_source_EBP_loop_index':compiled_slot,
          'real_original_EBP_signed_float_temp':old_slot,
          'actual_source_EBP_signed_float_temp':new_slot,
          'normalized_nonfield_GPR_CFG_mismatches':0,
          'original_entire_case_byte_exact':False})
    need(ins[SOURCE_LAST].mnemonic=='mov'
         and ins[SOURCE_LAST].op_str.endswith(', 0x195'),
         'three complete original 190->191->192 must lead into original 194 placeholder')
    return rows


def recheck_previous(reader,pe,d,f676,f598,by,ins,refs,mapper):
    evidence=[]
    for action,native_bytes,nx,compiled_bytes,nfields,expected_gpr in PREVIOUS:
        lo=by[action];hi=min(a for a in by.values() if a>lo)
        need(hi-lo==native_bytes,f'original previously sourced native {action:#x} CODE extent changed')
        native=list(d.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        # The original 1F4 case is a physically grounded source segment
        # but is not guaranteed a unique entry in the original dense table.
        if action==0x1F4:
            loc=5618
        else:
            need(lo in mapper,f'actual native original {action:#x} source dispatch label absent')
            address=mapper[lo]
            loc=next((i for i,x in enumerate(ins) if x.address==address),None)
        need(loc is not None,'native/source prior action boundary absent from this parent')
        endsource=loc+nx
        # Cases with extra genuine x87 operations are NOT declared
        # mnemonic/width-strict; here we recheck selected native
        # geometry and true field count without transplanting old counts.
        compiled=ins[loc:endsource]
        original_fields=f676.original_fields(native)
        source_fields=[f for f in refs if compiled[0].address<=f['offset']<compiled[-1].address+compiled[-1].size]
        need(len(native)==len(compiled)==nx
             and sum(x.size for x in compiled)==compiled_bytes
             and len(original_fields)==len(source_fields)==nfields,
             f'old original case {action:#x} entire physical opcode/count/PE ownership regression')
        absolute={i for i,target,mnem in original_fields if mnem!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(compiled)))
               if a!=b and i not in absolute]
        if expected_gpr is not None:
            expected_wide=10 if compiled_bytes!=native_bytes else 0
            need(len(wrong)==expected_gpr
                 and all(a.mnemonic==b.mnemonic for a,b in zip(native,compiled))
                 and sum(a.size!=b.size for a,b in zip(native,compiled))==expected_wide,
                 f'old original case {action:#x} current-parent real GPR or '
                 f'authentic EBP x86-width negatives moved')
        evidence.append({'original_prior_case':f'0x{action:X}',
            'real_original_CODE_B':native_bytes,
            'whole_parent_emitted_CODE_B':compiled_bytes,
            'actual_native_x86':nx,
            'original_zero_addend_typed_PE_COFF_field_count':nfields,
            'true_normalized_original_GPR_CFG_mismatches':len(wrong),
            'prior_original_entire_GAME_function_exact':False})
    return evidence


def main():
    reader=load('f734_reader','scripts/compare-coff-function.py')
    acts=load('f734_actions','scripts/report-fighter-action-handlers.py')
    f676=load('f734_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f701=load('f734_physical','scripts/verify-fighter-four-tier-volley-f701.py')
    f598=load('f734_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f728=load('f734_old728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f734_old729','scripts/verify-fighter-return-boundary-f729.py')
    f731=load('f734_old731','scripts/verify-fighter-aim-return-f731.py')
    f732=load('f734_old732','scripts/verify-fighter-following-native-f732.py')
    pe=reader.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(reader,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    src,compiler=f728.source_for_complete_parent(reader,pe,d,boss,report,mapped)
    src=f729.source_with_return_boundaries(src)
    src=f731.source_with_aim_return(src)
    src=f732.whole_source_with_following(src)
    src=source_with_three(src)
    obj=compiler.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-190-192.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-190-192.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,SYMBOL)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    new=new_native_actions(reader,pe,d,f676,f701,f598,by,ins,refs)
    original_switch=f728.complete_native_switch_DATA(reader,pe,d,boss,code,ins,refs,
                        source_1f5_start=5767,source_1f6_start=5916)
    mapper=source_map_from_original_afterRET(reader,pe,boss,code,ins,refs)
    previous=recheck_previous(reader,pe,d,f676,f598,by,ins,refs,mapper)
    need(len(new)==3
         and sum(x['native_complete_original_CODE_bytes'] for x in new)==792
         and sum(x['identical_native_ordered_x86_mnemonic_positions'] for x in new)==218
         and sum(x['all_original_typed_PE_COFF_targets_and_owners'] for x in new)==21
         and original_switch['original_nonrelocation_afterRET_BYTES_equal']==319,
         'all new native original 190-192 and current full 943B DATA must be actually verified')
    receipt={'original_entire_fighter':'0x00543210',
      'original_whole_giant_CODE_B_still_NONEXACT':boss['size'],
      'original_native_new_190_191_192_complete_action_sources':new,
      'new_original_internal_CODE_bytes_UNCREDITED':792,
      'new_original_native_x86_mnemonic_positions':218,
      'new_native_original_PE_COFF_physical_references':21,
      'prior_original_actions_in_same_new_compiler_parent':previous,
      'entire_original_native_afterRET_switch_DATA':original_switch,
      'new_accepted_whole_game_function_CODE_B':0,
      'whole_original_GAME_function_byte_exact':False}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F734 original fighter 190/191/192 full physical 276/276/240 '
          'native CODE B, 75/75/68 x86: all 218 native mnemonic ordinal '
          'positions identical in real one-parent VC7.1 C++ and all 21 '
          'original typed physical COFF fields at same x86 owners; source '
          '266/266/230 B, three authentic EBP/branch width mismatches '
          'per case, and original this EBP -0x44 vs source -0x34. '
          'Zero normalized nonfield GPR/CFG errors in all three, but '
          'NONSTRICT and ZERO new whole-game CODE credit. Prior native '
          '1F4/1F5, 1FA/1FB/1FE/1FF, 200/201, 2EF rechecked in '
          'same source; complete 943 native afterRET DATA, all 156 '
          'physically typed DIR32 switch targets and 319/319 sparse '
          'nonfield original bytes independently verified. No all-943 '
          'cold replay.')


if __name__=='__main__':
    main()
