#!/usr/bin/env python3
"""F737: both original complete native 194/195 ground eight-shot action bodies.

Build ONE entire original-shaped 58KB VC7.1 C++ parent using every
prior real 190/191/192, 1F4..1F8, 1FA..1FF and late fighter case.
Compare two original full 335-B/92-x86 native actions, every 14
physical PE typed field at exact x86 ordinal, and genuine 6B→3B
used stack scratch negatives. Independent same-parent original
1F5/1FA/1FB/1FE/1FF/200/201/2D0/2D1/2DD/2DE/2EF machine
geometry/COFF/GPR roles rechecked. Entire 943-B original afterRET
DATA incl 156 DIR32 native/source instruction labels + 319 sparse
bytes compared. No separate internal CODE accepted; no 955-unit replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f737-fighter-eight-ground'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
CASES={0x194:(0x0054967C,0x005497CB,5596,'0x9c','0x6c','0x1c','0x14'),
       0x195:(0x005497CB,0x0054991A,5688,'0xa0','0x70','0x20','0x18')}
SYMBOLS={
 0x0065782C:'g_ThresholdAt0065782C',
 0x00453D40:'PrepareActionAt453D40',
 0x0046D000:'StartAnimationAt46D000',
 0x00659A24:'g_F737_RoundY0At00659A24',
 0x00659A20:'g_F737_RoundY1At00659A20',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
}
SELECTED_ACTUAL_CONTEXT={
 0x1F4:(538,149,506,18,0),
 0x1F5:(538,149,538,18,0),
 0x1FA:(287,82,287,9,0),
 0x1FB:(603,174,603,15,0),
 0x1FE:(526,153,526,14,0),
 0x1FF:(526,153,526,14,0),
 0x200:(343,102,343,8,0),
 0x201:(436,126,436,9,0),
 0x2D0:(416,120,416,15,0),
 0x2D1:(416,120,416,15,0),
 0x2DD:(680,189,680,19,0),
 0x2DE:(660,189,660,18,0),
 0x2EF:(788,224,788,20,0),
}


def need(cond,msg):
    if not cond:raise ValueError(msg)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'original PE/source checker missing: '+path)
    mod=importlib.util.module_from_spec(sp)
    sys.modules[name]=mod
    sp.loader.exec_module(mod)
    return mod


def with_194_195(src):
    for action in CASES:
        placeholder=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(placeholder)==1,f'old original native case {action:#x} placeholder missing')
        src=src.replace(placeholder,
            '#include "FighterEightGroundF737.inc"' if action==0x194 else '')
    global_decl='extern float g_F734_RoundY2At00659A28;'
    need(src.count(global_decl)==1,'prior 192 native global declaration changed')
    src=src.replace(global_decl,global_decl+'\n'
        'extern float g_F737_RoundY0At00659A24;\n'
        'extern float g_F737_RoundY1At00659A20;')
    need(src.count('#include "FighterEightGroundF737.inc"')==1,
         'must insert both whole meaningful original actions at once')
    return src


def check_entire_cases(rd,pe,d,f676,f701,f598,by,ins,refs,*,following_native_196=False):
    result=[]
    for act,(lo,hi,start,orig_slot,src_slot,native_index,src_index) in CASES.items():
        next_action=0x195 if act==0x194 else 0x196
        need(by[act]==lo and by[next_action]==hi and hi-lo==335,
             'real original complete 194/195 PE case bounds changed')
        native=list(d.disasm(rd.pe_bytes_at(pe,lo,335),lo))
        generated=ins[start:start+92]
        need(len(native)==len(generated)==92
             and sum(x.size for x in native)==335
             and sum(x.size for x in generated)==329
             and all(a.mnemonic==b.mnemonic for a,b in zip(native,generated))
             and native[-1].mnemonic==generated[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'original complete {act:#x} 335B native, 329B source or 92 x86 mnemonics changed')
        fields=f676.original_fields(native)
        physical=f701.compare_typed_fields(fields,generated,refs,SYMBOLS,
                                           tuple(i for i,_,_ in fields))
        need(len(physical)==len(fields)==7,
             f'original {act:#x} all seven original typed physical PE fields missing')
        widths=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,generated))
                if a.size!=b.size]
        need(widths==[(71,6,3),(72,6,3)]
             and native[20].mnemonic==generated[20].mnemonic=='fcomp'
             and native[22].op_str==generated[22].op_str=='ah, 0x41'
             and native[23].mnemonic==generated[23].mnemonic=='jp',
             f'original {act:#x} physical native FCOMP/TEST AH41/JP and two x87 widths differ')
        for ix,mn in ((71,'mov'),(72,'fild')):
            need(native[ix].mnemonic==generated[ix].mnemonic==mn
                 and f'[ebp - {orig_slot}]' in native[ix].op_str
                 and f'[ebp - {src_slot}]' in generated[ix].op_str,
                 f'original {act:#x} real float scratch at x86 {ix} not honestly checked')
        need(f'[ebp - {native_index}]' in native[52].op_str
             and f'[ebp - {src_index}]' in generated[52].op_str
             and native[70].mnemonic==generated[70].mnemonic=='imul'
             and native[70].op_str==generated[70].op_str==
               ('ecx, ecx, 0x23' if act==0x194 else 'edx, edx, 0x1b')
             and native[77].op_str==generated[77].op_str=='0x324'
             and native[88].op_str==generated[88].op_str=='9',
             f'original {act:#x} real loop lifetime, signed facing / projectile and finish wrong')
        absolute={i for i,target,mn in fields if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(generated)))
               if a!=b and i not in absolute]
        need(not wrong,f'original {act:#x} GPR/CFG mismatches unexpectedly changed: {wrong[:6]}')
        result.append({'native_original_action':f'0x{act:X}',
             'original_physical_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
             'original_entire_CODE_bytes':335,
             'compiler_entire_CASE_CODE_bytes':329,
             'original_and_source_x86_mnemonics':92,
             'real_PE_COFF_fields_by_native_instruction_ordinal':len(physical),
             'x86_width_differences':widths,
             'original_real_EBP_float_temp':orig_slot,
             'source_real_EBP_float_temp':src_slot,
             'original_real_EBP_loop_index':native_index,
             'source_real_EBP_loop_index':src_index,
             'native_nonfield_GPR_CFG_discrepancies':0,
             'whole_original_game_function_exact':False})
    need(ins[5688].mnemonic=='mov' and ins[5780].mnemonic=='mov',
         'real 190/191/192->194->195->196 original physical source order missing')
    if following_native_196:
        need(ins[5780].op_str=='ecx, dword ptr [ebp - 0x3c]'
             and ins[5781].mnemonic=='movsx'
             and ins[5781].op_str=='edx, word ptr [ecx + 0x62]',
             'actual full 196 native source must begin immediately after full 195')
    else:
        need(ins[5780].op_str.endswith(', 0x197'),
             'historical earlier original-shaped parent must retain native 196 placeholder')
    return result


def check_selected_context(rd,pe,d,f676,f598,by,ins,refs,mapper,*,
                           source_1f4_start=5798,
                           source_expected_context=None,
                           source_receiver_slot='0x3c'):
    rows=[]
    expected_context=(SELECTED_ACTUAL_CONTEXT if source_expected_context is None
                      else source_expected_context)
    for act,(native_B,nx,source_B,field_count,gpr_count) in expected_context.items():
        lo=by[act];hi=min(k for k in by.values() if k>lo)
        original=list(d.disasm(rd.pe_bytes_at(pe,lo,hi-lo),lo))
        address=mapper.get(lo)
        start=(source_1f4_start if act==0x1F4 else
               next((i for i,x in enumerate(ins) if x.address==address),None))
        need(start is not None,'original active context source owner missing')
        generated=ins[start:start+nx]
        fields=f676.original_fields(original)
        ref=[r for r in refs if generated[0].address<=r['offset']<generated[-1].address+generated[-1].size]
        absolute={i for i,target,mnem in fields if mnem!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(original),
                                              f598.normalized(generated)))
               if a!=b and i not in absolute]
        need(hi-lo==native_B and len(original)==len(generated)==nx
             and sum(x.size for x in generated)==source_B
             and len(fields)==len(ref)==field_count
             and all(a.mnemonic==b.mnemonic for a,b in zip(original,generated))
             and len(wrong)==gpr_count,
             f'native case {act:#x} new actual compiler phase / whole original geometry wrong')
        if native_B==source_B:
            need(all(a.size==b.size for a,b in zip(original,generated)),
                 f'original {act:#x} native x86-width restored claim not true')
        else:
            need(act==0x1F4 and sum(a.size!=b.size for a,b in zip(original,generated))==10,
                 'older original 1F4 ten x86-width differences must remain honest')
        rows.append({'native_original_case':f'0x{act:X}',
            'original_entire_CODE_bytes':native_B,
            'compiled_entire_CODE_bytes':source_B,
            'native_and_source_x86':nx,
            'authentic_original_PE_COFF_field_count':field_count,
            'real_nonfield_GPR_CFG_differences':gpr_count,
            'not_entire_GAME_function_exact':True})
    # The 1F5 C++ source now emits all original widths due to actually
    # used preceding 194+195 stack temporaries, though deep EBP offsets
    # and preserved `this` frame still differ (native -0x44, source -0x3c).
    need(ins[3].op_str==f'dword ptr [ebp - {source_receiver_slot}], ecx',
         'natural source saved receiver EBP must remain physically proven for this parent')
    return rows


def main():
    rd=load('f737_rd','scripts/compare-coff-function.py')
    acts=load('f737_acts','scripts/report-fighter-action-handlers.py')
    f676=load('f737_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f701=load('f737_physical','scripts/verify-fighter-four-tier-volley-f701.py')
    f598=load('f737_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f728=load('f737_728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f737_729','scripts/verify-fighter-return-boundary-f729.py')
    f731=load('f737_731','scripts/verify-fighter-aim-return-f731.py')
    f732=load('f737_732','scripts/verify-fighter-following-native-f732.py')
    f734=load('f737_734','scripts/verify-fighter-eight-round-f734.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    source,compiler=f728.source_for_complete_parent(rd,pe,d,boss,report,mapped)
    source=f729.source_with_return_boundaries(source)
    source=f731.source_with_aim_return(source)
    source=f732.whole_source_with_following(source)
    source=f734.source_with_three(source)
    source=with_194_195(source)
    obj=compiler.compile_whole_parent(source)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-194-195.cpp').write_text(source)
    shutil.copyfile(obj,OUT/'Boss00543210-194-195.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=rd.object_function(obj,SYMBOL)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    first=f734.new_native_actions(rd,pe,d,f676,f701,f598,by,ins,refs,
                                  following_native_194=True,source_x87_slot_shift=8)
    newly=check_entire_cases(rd,pe,d,f676,f701,f598,by,ins,refs)
    mapper=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    later=check_selected_context(rd,pe,d,f676,f598,by,ins,refs,mapper)
    native_data=f728.complete_native_switch_DATA(rd,pe,d,boss,code,ins,refs,
                    source_1f5_start=5947,source_1f6_start=6096)
    need(len(first)==3 and len(newly)==2
         and sum(x['original_entire_CODE_bytes'] for x in newly)==670
         and all(x['real_nonfield_GPR_CFG_differences']==0 for x in later)
         and native_data['original_nonrelocation_afterRET_BYTES_equal']==319,
         'new complete source 194/195 original and native 943B afterRET data validation failed')
    summary={'entire_original_fighter':'0x00543210',
       'original_whole_giant_CODE_B_still_NONEXACT':boss['size'],
       'new_true_native_194_195_complete_action_Cpp':newly,
       'new_original_source_backed_internal_CODE_B_NOT_CREDITED':670,
       'original_typed_PE_COFF_field_count':14,
       'earlier_190_191_192_complete_source_reverified':first,
       '13_actual_cross_case_native_Cpp_GPR_phase_results':later,
       'entire_native_943B_original_afterRET_switch_DATA':native_data,
       'whole_original_GAME_function_byte_exact':False,
       'new_exact_whole_game_function_CODE_B':0}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F737 entire original 00543210 fighter two full 194/195 grounded '
          '8-shot actions each native 335B/92 x86/7 real COFF fields; '
          'natural VC7.1 source each 329B/92 original mnemonic positions '
          'and ALL 14 authentic PE typed fields at native ordinals. '
          'Original FCOMP [0065782C]; TEST AH,41; JP and signed 35/27 '
          'shot/angle; source only two real 6B->3B EBP scratch width '
          'differences each, GPR normalized 0. Source saved this '
          'naturally -0x3c vs original -0x44. Recheck previous 190-192 '
          'full native, and 13 complete previous cases: ORIGINAL 1F5 '
          'now matches all 538B native instruction WIDTHS and GPR 0; '
          '1FA/1FB/1FE/1FF, 200/201, 2D0/2D1, 2DD/2DE, 2EF '
          'all native GPR zero in SAME parent. All 943 original afterRET '
          'DATA, 156 x86-aligned native/source DIR32 and other 319 '
          'native bytes exact. Actual deep EBP slots / whole game '
          'NONEXACT, ZERO newly accepted standalone game CODE.')


if __name__=='__main__':
    main()
