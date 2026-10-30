#!/usr/bin/env python3
"""F740 native fighter complete original 196/197/198 native 0x330/0x347.

Rebuild ONE original-shaped 58KB VC7.1 giant with all tracked 190..195,
1F4..1F8, 1FA..1FF and late original actions. 196+197 original 436 B
and 118 x86 each; 198 218 B/62 x86. Check every physical original
31 typed REL32/DIR32 field at original x86 owner, all original 298
mnemonics, real signed facing x87 scratch EBP and exact width negatives,
all prior 190-195 original source, 13 later original native contexts,
and the entire original 943-B after-RET DATA / 156 DIR32 labels.
No fake locals, original executable edits, truncated case credit or
full 961-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f740-fighter-repeating-shot'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
CASES=(0x196,0x197,0x198)
NEXT={0x196:0x197,0x197:0x198,0x198:0x19A}
NATIVE={
 0x196:(0x0054991A,0x00549ACE,436,118,12,424,5780,((49,'0xa4','0x74'),(50,'0xa4','0x74'),(97,'0xa8','0x78'),(98,'0xa8','0x78'))),
 0x197:(0x00549ACE,0x00549C82,436,118,12,424,5898,((49,'0xac','0x7c'),(50,'0xac','0x7c'),(97,'0xb0','0x80'),(98,'0xb0','0x80'))),
 0x198:(0x00549C82,0x00549D5C,218,62,7,218,6016,((42,'0xb4','0x84'),(43,'0xb4','0x84'))),
}
SYMBOLS={
 0x00453E20:'ResetAt453E20',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00453D40:'PrepareActionAt453D40',
 0x00659A1C:'g_F740_ShotY0At00659A1C',
 0x0065928C:'g_F740_ShotY1At0065928C',
 0x00659A18:'g_F740_ShotY2At00659A18',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0046D000:'StartAnimationAt46D000',
 0x0040FB40:'SetAuxActionAt40FB40',
}


def need(ok,what):
    if not ok:raise ValueError(what)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'native original checker missing: '+path)
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def source_with_repeat_shots(source):
    for action in CASES:
        old=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(old)==1,f'original action{action:#x} source placeholder missing')
        source=source.replace(old,
                 '#include "FighterRepeatShotF740.inc"' if action==0x196 else '')
    before='extern float g_F737_RoundY1At00659A20;'
    need(source.count(before)==1,'earlier whole original physics global declaration changed')
    source=source.replace(before,before+'\n'
        'extern float g_F740_ShotY0At00659A1C;\n'
        'extern float g_F740_ShotY1At0065928C;\n'
        'extern float g_F740_ShotY2At00659A18;')
    need(source.count('#include "FighterRepeatShotF740.inc"')==1,
         'all three real original source cases must compile in one giant parent')
    return source


def verify_all_three_native(rd,pe,d,f676,f701,f598,by,ins,refs,*,
                            following_complete_19A=False):
    rows=[]
    for action in CASES:
        lo,hi,size,nx,nfields,source_size,start,scratch=NATIVE[action]
        need(by[action]==lo and by[NEXT[action]]==hi and hi-lo==size,
             f'original complete native 196/197/198 target physical bound changed: {action:#x}')
        native=list(d.disasm(rd.pe_bytes_at(pe,lo,size),lo))
        generated=ins[start:start+nx]
        need(len(native)==len(generated)==nx
             and sum(x.size for x in native)==size
             and sum(x.size for x in generated)==source_size
             and all(a.mnemonic==b.mnemonic for a,b in zip(native,generated))
             and native[-1].mnemonic==generated[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'original entire native {action:#x} x86 mnemonic, sizes and common tail differ')
        physical=f676.original_fields(native)
        fields=f701.compare_typed_fields(physical,generated,refs,SYMBOLS,
                                          tuple(i for i,_,_ in physical))
        need(len(fields)==len(physical)==nfields,
             f'native original {action:#x} all {nfields} fields not physically owned by correct x86')
        width=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,generated))
               if a.size!=b.size]
        expect_width=([(i,6,3) for i,_,_ in scratch] if action!=0x198 else [])
        need(width==expect_width,
             f'original {action:#x} true 6B->3B stack operand widths not preserved: {width}')
        for ordinal,old,new in scratch:
            a,b=native[ordinal],generated[ordinal]
            need(a.mnemonic==b.mnemonic
                 and a.mnemonic==('fild' if ordinal in (50,98,43) else 'mov')
                 and f'[ebp - {old}]' in a.op_str
                 and f'[ebp - {new}]' in b.op_str,
                 f'original {action:#x} real native x87 scratch owner {ordinal} changed')
        absolute={i for i,_,mn in physical if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                               f598.normalized(generated)))
               if a!=b and i not in absolute]
        need(not wrong,f'original {action:#x} native GPR/CFG owner phase wrong: {wrong[:7]}')
        if action==0x196:
            need(native[48].op_str==generated[48].op_str=='ecx, ecx, 0x3c'
                 and native[96].op_str==generated[96].op_str=='edx, edx, 0x3c'
                 and native[55].op_str==generated[55].op_str=='0x330'
                 and native[103].op_str==generated[103].op_str=='0x330'
                 and native[109].op_str==generated[109].op_str=='6',
                 'real original 196 0x330 twin 60-direction and six repeat state lost')
        elif action==0x197:
            need(native[48].op_str==generated[48].op_str=='ecx, ecx, 0x44'
                 and native[96].op_str==generated[96].op_str=='edx, edx, 0x44'
                 and native[84].op_str==generated[84].op_str=='dword ptr [eax + 0x314], 0x41a00000',
                 'real native 197 68-direction and distinct stage-seven 20.0f angle lost')
        else:
            need(native[41].op_str==generated[41].op_str=='ecx, ecx, 0x1c'
                 and native[26].op_str==generated[26].op_str=='dword ptr [edx + 0x314], 0x42700000'
                 and native[27].op_str==generated[27].op_str=='0xfa'
                 and native[48].op_str==generated[48].op_str=='0x347'
                 and native[58].op_str==generated[58].op_str=='2',
                 'original complete 198 stage4 angle60, 250 animation and 347 shot wrong')
        rows.append({'native_action':f'0x{action:X}',
           'original_entire_PE_CODE_interval':[f'0x{lo:08X}',f'0x{hi:08X}'],
           'original_entire_CODE_bytes':size,
           'emitted_entire_CODE_bytes':source_size,
           'original_and_source_ordered_x86_mnemonics':nx,
           'original_physical_typed_PE_COFF_fields':len(fields),
           'real_width_operand_differences':width,
           'actual_original_vs_source_EBP_scratch':[
                {'x86_ordinal':ix,'original_native_EBP':old,'source_real_EBP':new}
                for ix,old,new in scratch],
           'normalized_nonfield_native_GPR_CFG_errors':0,
           'original_whole_game_function_byte_exact':False})
    need(all(ins[i].mnemonic=='mov' for i in (5780,5898,6016,6078)),
         'original 196/197/198/19A source action start ordering changed')
    if following_complete_19A:
        need(ins[6078].op_str=='eax, dword ptr [ebp - 0x3c]'
             and ins[6079].mnemonic=='movsx'
             and ins[6079].op_str=='ecx, word ptr [eax + 0x62]',
             'actual newly complete 19A source must directly follow original 198')
    else:
        need(ins[6078].op_str.endswith(', 0x19b'),
             'old F740 whole parent must retain original 19A placeholder')
    return rows


def main():
    rd=load('f740_rd','scripts/compare-coff-function.py')
    acts=load('f740_acts','scripts/report-fighter-action-handlers.py')
    f676=load('f740_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f701=load('f740_typed','scripts/verify-fighter-four-tier-volley-f701.py')
    f598=load('f740_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f728=load('f740_728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f740_729','scripts/verify-fighter-return-boundary-f729.py')
    f731=load('f740_731','scripts/verify-fighter-aim-return-f731.py')
    f732=load('f740_732','scripts/verify-fighter-following-native-f732.py')
    f734=load('f740_734','scripts/verify-fighter-eight-round-f734.py')
    f737=load('f740_737','scripts/verify-fighter-eight-ground-f737.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    src,compiler=f728.source_for_complete_parent(rd,pe,d,boss,report,mapped)
    src=f729.source_with_return_boundaries(src)
    src=f731.source_with_aim_return(src)
    src=f732.whole_source_with_following(src)
    src=f734.source_with_three(src)
    src=f737.with_194_195(src)
    src=source_with_repeat_shots(src)
    obj=compiler.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-196-197-198.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-196-197-198.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=rd.object_function(obj,SYMBOL)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    new=verify_all_three_native(rd,pe,d,f676,f701,f598,by,ins,refs)
    prev194=f737.check_entire_cases(rd,pe,d,f676,f701,f598,by,ins,refs,
                                     following_native_196=True)
    prev190=f734.new_native_actions(rd,pe,d,f676,f701,f598,by,ins,refs,
                         following_native_194=True,source_x87_slot_shift=8)
    mapper=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    source_context={
        0x1F4:(538,149,538,18,71),
        0x1F5:(538,149,538,18,71),
        0x1FA:(287,82,287,9,50),
        0x1FB:(603,174,603,15,111),
        0x1FE:(526,153,526,14,96),
        0x1FF:(526,153,526,14,96),
        0x200:(343,102,343,8,67),
        0x201:(436,126,436,9,85),
        0x2D0:(416,120,416,15,60),
        0x2D1:(416,120,416,15,60),
        0x2DD:(680,189,680,19,80),
        0x2DE:(660,189,660,18,0),
        0x2EF:(788,224,788,20,0),
    }
    previous=f737.check_selected_context(rd,pe,d,f676,f598,by,ins,refs,
               mapper,source_1f4_start=6090,source_expected_context=source_context)
    native_data=f728.complete_native_switch_DATA(rd,pe,d,boss,code,ins,refs,
                            source_1f5_start=6239,source_1f6_start=6388)
    need(len(new)==3 and sum(x['original_entire_CODE_bytes'] for x in new)==1090
         and sum(x['original_physical_typed_PE_COFF_fields'] for x in new)==31
         and [x['real_nonfield_GPR_CFG_differences'] for x in previous]
             ==[r[-1] for r in source_context.values()]
         and native_data['original_nonrelocation_afterRET_BYTES_equal']==319,
         'actual native PE 196-198 source, native previous contexts or full afterRET DATA differs')
    receipt={'original_whole_fighter':'0x00543210',
       'original_full_58KB_game_FUNCTION_CODE_still_NONEXACT':boss['size'],
       'original_three_complete_physically_bounded_sources':new,
       'new_native_original_internal_CODE_B_NOT_CREDITED':1090,
       'new_original_native_x86_opcode_positions':298,
       'new_physical_source_31_original_PE_COFF_fields':31,
       'prior_original_194_195_same_compiler_parent':prev194,
       'prior_original_190_191_192_same_parent':prev190,
       'prior_13_original_source_contexts_including_real_GPR_REGRESSIONS':previous,
       'entire_original_943B_native_switch_DATA':native_data,
       'new_authored_whole_GAME_function_exact_CODE_B':0,
       'entire_original_GAME_function_byte_exact':False}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F740 full original 00543210 cases 196/197/198: native '
          '436/436/218 B, 118/118/62 x86 original mnemonics, '
          '12/12/7 physical typed native PE/COFF fields, correct '
          'stage6/7 330 60/68 facing twin shots, 198 stage4 347 '
          'shot and true 250-frame animation. Whole VC7.1 source '
          '424/424/218 B, all 31 field owner ordinals and ALL 298 '
          'original mnemonic positions identical, 0 normalized '
          'nonfield GPR errors. Real deep native -0xa4..-0xb4 '
          'vs source -0x74..-0x84 used EBP scratch, native saved '
          'this -0x44 vs source -0x3c, giant NONEXACT. Previous '
          '194/195 and 190-192 verified, 13 old original physical '
          'contexts independently checked, including real GPR-phase '
          'regressions; full 943B original '
          'afterRET switch DATA 156 original/source DIR32 x86 starts '
          'and 319/319 sparse bytes checked. Older 1F4 now native 538B '
          'x86-width geometry yet 71 real GPR owner errors; other '
          'previous full cases likewise show genuine new source '
          'register-phase regressions, not inherited strict. '
          'NO whole game CODE '
          'credit, no 961-unit cold replay.')


if __name__=='__main__':
    main()
