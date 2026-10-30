#!/usr/bin/env python3
"""F728: full 538B/149-x86 random-arc 1F4 and 1F5 in entire fighter.

Build one VC7.1 original-shaped 00543210 C++ parent from tracked
source. Read pinned original two *complete* gameplay cases, their
36 genuine typed PE/COFF fields and 8 used x87 scratch owner slots.
Compare ALL 943 native after-RET DATA, every one of 156 genuine
DIR32 switch entries to original AND source real instruction bounds,
and 319/319 sparse-map bytes. The newly added genuine source changes
previously strict original 200/201 GPR phases: count those errors,
never transplant old 27-strict-context claims or claim split-case CODE.
No full 943-unit cold replay or executable byte patches.
"""
from __future__ import annotations
import hashlib
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f728-fighter-random-arcs'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
# Original native physical PE CODE intervals; not independent functions.
CASES={0x1F4:(0x0054A6CC,0x0054A8E6,538,149,18,5406),
       0x1F5:(0x0054A8E6,0x0054AB00,538,149,18,5555)}
ORIGINAL_CACHED_NONFIELD_GPR={0x1F4:71,0x1F5:71}
# Original-used stage-4 and random float shot x87 stack storage.
X87_SLOTS={
 0x1F4:{37:('0xd8','0x4c'),42:('0xdc','0x50'),43:('0xdc','0x50'),
         44:('0xd8','0x4c'),50:('0xe0','0x54'),55:('0xe4','0x58'),
         56:('0xe4','0x58'),57:('0xe0','0x54')},
 0x1F5:{56:('0xe8','0x5c'),61:('0xec','0x60'),62:('0xec','0x60'),
         63:('0xe8','0x5c'),69:('0xf0','0x64'),74:('0xf4','0x68'),
         75:('0xf4','0x68'),76:('0xf0','0x64')},
}
SYMBOLS={
 0x00453E20:'ResetAt453E20',
 0x00455580:'RandomBoundaryAt455580',
 0x00657858:'g_F728_RandomOffsetYAt00657858',
 0x00657878:'g_F728_RandomOffsetXAt00657878',
 0x00453A70:'SpawnFloatXYAt453A70',
 0x0065782C:'g_ThresholdAt0065782C',
 0x006583FC:'g_F728_PositiveDragAt006583FC',
 0x00658058:'g_F728_PositiveDrag2At00658058',
 0x0040FB40:'SetAuxActionAt40FB40',
 0x0040FA30:'GetNativeActionAt40FA30',
 0x0040FAC0:'SetNativeActionAt40FAC0',
 0x00453D40:'PrepareActionAt453D40',
}
# Two previous source-STRICT original complete internal actions must
# now be explicitly marked NONSTRICT in this newly compiled context.
PREVIOUS_ACTION_GPR_REGRESSION={0x200:67,0x201:85}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,relative):
    sp=importlib.util.spec_from_file_location(name,ROOT/relative)
    need(sp is not None and sp.loader is not None,'original source helper absent: '+relative)
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def source_with_random_arcs(src):
    for action in CASES:
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(marker)==1,f'old original action {action:#x} placeholder absent')
        src=src.replace(marker,'#include "FighterRandomArcsF728.inc"' if action==0x1F4 else '')
    declaration='extern float g_F724_ShotYAt00659488;'
    need(src.count(declaration)==1,'native original 59488 float declaration changed')
    src=src.replace(declaration,declaration+'\n'
       'extern float g_F728_RandomOffsetXAt00657878;\n'
       'extern float g_F728_RandomOffsetYAt00657858;\n'
       'extern float g_F728_PositiveDragAt006583FC;\n'
       'extern float g_F728_PositiveDrag2At00658058;')
    need(src.count('#include "FighterRandomArcsF728.inc"')==1,
         'both native original 1F4/1F5 cases must be present only once')
    return src


def source_for_complete_parent(reader,pe,real,boss,report,mapped):
    f696=load('f728_f696','scripts/verify-fighter-grounded-volley-f696.py')
    f699=load('f728_f699','scripts/verify-fighter-approach-volley-f699.py')
    f701=load('f728_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    f706=load('f728_f706','scripts/verify-fighter-combined-native-storm-f706.py')
    f708=load('f728_f708','scripts/verify-fighter-twin-burst-f708.py')
    f711=load('f728_f711','scripts/verify-fighter-falling-radials-f711.py')
    f714=load('f728_f714','scripts/verify-fighter-complex-movement-f714-f715.py')
    f718=load('f728_f718','scripts/verify-fighter-double-volley-f718.py')
    f720=load('f728_f720','scripts/verify-fighter-late-storm-f720-f721.py')
    f722=load('f728_f722','scripts/verify-fighter-native-order-f722.py')
    f724=load('f728_f724','scripts/verify-fighter-followup-burst-f724.py')
    f672=load('f728_f672','scripts/verify-fighter-eight-shot-and-follow-f672.py')
    src,mods,helpers=f714.combine_source(f706,f708,f711,f696,f699,f701,f672,
                                           reader,pe,real,boss,report,mapped)
    src=f718.source_with_double_volley(src)
    src=f720.source_with_both(src)
    src=f722.native_order_source(src)
    src=f724.source_with_2c5(src)
    src=source_with_random_arcs(src)
    return src,f706


def case_evidence(reader,pe,real,f676,f598,f701,by,ins,refs,*,following_native_1f6=False):
    rows=[]
    for action,(start,end,original_size,nx,nfields,st) in CASES.items():
        need(by[action]==start and by[0x1F5 if action==0x1F4 else 0x1F6]==end
             and end-start==original_size,
             f'original entire native {action:#x} 538-byte physical PE interval changed')
        native=list(real.disasm(reader.pe_bytes_at(pe,start,original_size),start))
        generated=ins[st:st+nx]
        need(len(native)==len(generated)==nx
             and all(a.mnemonic==b.mnemonic for a,b in zip(native,generated))
             and sum(x.size for x in native)==original_size
             and sum(x.size for x in generated)==506
             and generated[-1].mnemonic==native[-1].mnemonic=='jmp'
             and native[-1].op_str=='0x5515c2',
             f'original full native {action:#x}: actual mnemonic / length / native exit changed')
        original_fields=f676.original_fields(native)
        relocs=f701.compare_typed_fields(original_fields,generated,refs,SYMBOLS,
                                          tuple(i for i,target,mn in original_fields))
        need(len(relocs)==nfields,
             f'original native {action:#x} all typed PE/COFF source fields drift')
        # The originally wrong DIR32 owner: after member-lvalue source,
        # native Y global is FADD immediately following actor FLD.
        yord=36 if action==0x1F4 else 55
        need(native[yord-1].mnemonic==generated[yord-1].mnemonic=='fld'
             and '[0x' not in generated[yord-1].op_str
             and native[yord].op_str=='dword ptr [0x657858]'
             and generated[yord].op_str=='dword ptr [0]'
             and generated[yord].mnemonic=='fadd',
             f'native {action:#x} original random Y-global DIR32 float order not corrected')
        for ordinal,(original_slot,source_slot) in X87_SLOTS[action].items():
            a,b=native[ordinal],generated[ordinal]
            need(a.mnemonic==b.mnemonic
                 and f'[ebp - {original_slot}]' in a.op_str
                 and f'[ebp - {source_slot}]' in b.op_str,
                 f'original {action:#x}: real x87 used temporary at x86{ordinal} is not measured')
        wide=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,generated))
              if a.size!=b.size]
        need(len(wide)==10 and sum(a-b for _,a,b in wide)==32,
             f'authentic 538B/506B native x87 scratch and branch-width gap changed {wide}')
        absolute={i for i,target,mn in original_fields if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(generated)))
               if a!=b and i not in absolute]
        need(len(wrong)==ORIGINAL_CACHED_NONFIELD_GPR[action],
             f'native source {action:#x} honest nonfield GPR/CFG roles changed: {wrong[:9]}')
        rows.append({'action':f'0x{action:X}',
             'original_physical_PE_interval':[f'0x{start:08X}',f'0x{end:08X}'],
             'original_entire_native_CODE_bytes':original_size,
             'new_source_entire_CODE_bytes':sum(x.size for x in generated),
             'original_and_compiler_x86_mnemonics':nx,
             'original_physical_zero_addend_PE_COFF_fields':len(relocs),
             'original_incorrect_frame_width_positions':wide,
             'native_real_EBP_x87_scratch_vs_source':X87_SLOTS[action],
             'actual_native_GPR_CFG_negative_ordinals':len(wrong),
             'native_case_byte_exact':False})
    need(ins[5406].mnemonic==ins[5555].mnemonic==ins[5704].mnemonic=='mov',
         'source must preserve full 1F4->1F5->1F6 physical action start order')
    if following_native_1f6:
        need(ins[5704].op_str=='eax, dword ptr [ebp - 0x28]'
             and ins[5705].op_str=='ecx, word ptr [eax + 0x62]',
             'source after native 1F5 must be independently proven real 1F6 full source')
    else:
        need(ins[5704].op_str.endswith(', 0x1f7'),
             'original 1F6 placeholder expected in F728 prior standalone source context')
    return rows


def complete_native_switch_DATA(reader,pe,real,boss,code,ins,refs,*,
                                source_1f5_start=5555,source_1f6_start=5704):
    ret=ins[-1].address+ins[-1].size
    n=reader.pe_bytes_at(pe,BOSS+boss['size'],boss['postret_size'])
    obj=code[ret:]
    need(len(n)==len(obj)==boss['postret_size']==943,
         'entire 943-byte independent original afterRET switch DATA absent')
    fields=sorted((x for x in refs if x['offset']>=ret),key=lambda x:x['offset'])
    need(len(fields)==sum(t['slots'] for t in boss['tables'])==156,
         'original 7 complete switch tables have wrong DIR32 entry count')
    original_ins=list(real.disasm(reader.pe_bytes_at(pe,BOSS,boss['size']),BOSS))
    original_starts={x.address for x in original_ins}
    source_starts={x.address for x in ins}
    field_bytes=set()
    target_pairs={}
    for item in fields:
        offset=item['offset']-ret
        need(0<=offset<=len(obj)-4
             and not (set(range(offset,offset+4)) & field_bytes),
             'native original afterRET DIR32 relocation overlap/out of table')
        field_bytes.update(range(offset,offset+4))
        original_target=int.from_bytes(n[offset:offset+4],'little')
        source_target=item['local_symbol_offset']
        need(item['type']=='DIR32' and item['addend']==0
             and source_target is not None
             and original_target in original_starts
             and source_target in source_starts,
             'original afterRET switch entry target not actual native/source x86 instruction')
        target_pairs.setdefault(original_target,[]).append(source_target)
    matching=sum(n[i]==obj[i] for i in range(len(n)) if i not in field_bytes)
    need(len(field_bytes)==624 and matching==943-624==319
         and all(n[i]==obj[i] for i in range(943) if i not in field_bytes),
         'independent native/source sparse switch dispatch DATA bytes are not identical')
    # Grounded original 1F5 / following 1F6 physical table targets,
    # not merely any target within either 58KB body.
    need(source_1f5_start<len(ins) and source_1f6_start<len(ins)
         and target_pairs.get(0x0054A8E6)==[ins[source_1f5_start].address]
         and target_pairs.get(0x0054AB00)==[ins[source_1f6_start].address],
         'original and newly recovered 1F5/1F6 dense switch target instruction identity changed')
    return {'original_entire_afterRET_bytes':len(n),
            'original_and_compiler_afterRET_typed_DIR32_fields':len(fields),
            'all_native_and_source_jump_labels_instruction_aligned':True,
            'original_nonrelocation_afterRET_BYTES_equal':matching,
            'original_afterRET_NONrelocation_total':319,
            'original_data_sha256':hashlib.sha256(n).hexdigest()}


def verify_prior_context_regression(reader,pe,real,f676,f598,by,ins,refs,boss,*,
                                    source_expected_gpr=None):
    # The literal source switch tables provide an independently physical
    # mapping from original instruction addresses to new source labels.
    ret=ins[-1].address+ins[-1].size
    original_data=reader.pe_bytes_at(pe,BOSS+boss['size'],boss['postret_size'])
    refsdata=[x for x in refs if x['offset']>=ret]
    mapping={}
    for x in refsdata:
        i=x['offset']-ret
        orig=int.from_bytes(original_data[i:i+4],'little')
        mapping.setdefault(orig,x['local_symbol_offset'])
    out=[]
    for action in (0x200,0x201,0x2EF):
        native_start=by[action]
        native_end=min(x for x in by.values() if x>native_start)
        native=list(real.disasm(reader.pe_bytes_at(pe,native_start,native_end-native_start),native_start))
        need(native_start in mapping,
             f'original case{action:#x} must have an actual original and source switch label')
        cstart=mapping[native_start]
        offset=next((j for j,x in enumerate(ins) if x.address==cstart),None)
        need(offset is not None,'original native action switch label missing in current source C++')
        compiled=ins[offset:offset+len(native)]
        orig_fields=f676.original_fields(native)
        emitted_fields=[r for r in refs if compiled[0].address<=r['offset']<compiled[-1].address+compiled[-1].size]
        absolute={i for i,t,mn in orig_fields if mn!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(compiled)))
               if a!=b and i not in absolute]
        expected=(source_expected_gpr if source_expected_gpr is not None
                  else PREVIOUS_ACTION_GPR_REGRESSION).get(action,0)
        need(len(wrong)==expected
             and len(orig_fields)==len(emitted_fields)
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(native,compiled))
             and sum(a.size for a in native)==sum(b.size for b in compiled),
             f'original case{action:#x} honest new-GPR-regression/physical geometry changed')
        out.append({'native_case':f'0x{action:X}',
            'original_full_internal_CASE_bytes':native_end-native_start,
            'native_x86_instructions':len(native),
            'original_actual_typed_PE_COFF_fields':len(orig_fields),
            'current_source_nonfield_GPR_CFG_differences':len(wrong),
            'current_context_strict_native_interior':len(wrong)==0})
    if source_expected_gpr is None:
        need(out[0]['current_source_nonfield_GPR_CFG_differences']>0
             and out[1]['current_source_nonfield_GPR_CFG_differences']>0
             and out[2]['current_context_strict_native_interior'],
             'real upstream source 200/201 regressions cannot be hidden as old strict')
    else:
        need(all(x['current_source_nonfield_GPR_CFG_differences']
                 ==source_expected_gpr.get(int(x['native_case'],16),0)
                 for x in out),
             'new actual original source case GPR phases must match this compiler parent')
    return out


def main():
    reader=load('f728_reader','scripts/compare-coff-function.py')
    acts=load('f728_acts','scripts/report-fighter-action-handlers.py')
    f676=load('f728_f676','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f728_f598','scripts/verify-fighter-singleton-contact-f598.py')
    f701=load('f728_f701','scripts/verify-fighter-four-tier-volley-f701.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    src,compiler=source_for_complete_parent(reader,pe,real,boss,report,mapped)
    obj=compiler.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-1F4-1F5.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-1F4-1F5.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,SYMBOL)
    ins=[]
    for x in real.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    new=case_evidence(reader,pe,real,f676,f598,f701,by,ins,refs)
    switch=complete_native_switch_DATA(reader,pe,real,boss,code,ins,refs)
    context=verify_prior_context_regression(reader,pe,real,f676,f598,by,ins,refs,boss)
    receipt={'original_whole_giant':'0x00543210',
       'original_entire_giant_CODE_bytes_still_NONEXACT':boss['size'],
       'new_original_whole_internal_action_sources':new,
       'new_original_physical_internal_CODE_not_credited_bytes':1076,
       'new_original_native_x86_mnemonic_positions':298,
       'new_original_physical_typed_fields':36,
       'real_source_context_strict_regression_not_hidden':context,
       'original_and_compiler_complete_943B_afterRET_DATA':switch,
       'new_exact_whole_game_function_bytes':0,
       'original_entire_function_byte_exact':False}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F728 two original complete random-arc game cases 1F4/1F5: '
          '538+538 native B, 149+149 original x86 mnemonics, '
          '18+18 genuine physically owned typed PE/COFF fields '
          'now restored (real member-FLD before DIR32 global-FADD), '
          'source each 506B/149 x86 with genuine 10 EBP width and '
          '4 x87 used source-temporary stack owner differences per case. '
          'No exact whole-game function. IMPORTANT new source breaks '
          'previous strict 200/201 source GPR phases: 67/85 honest '
          'nonfield mismatches in otherwise aligned 343B/436B native cases; '
          '2EF still strictly matching. Independently entire original '
          '943B afterRET physical DATA reverified: all 156 actual DIR32 '
          'native and source targets instruction-aligned and all '
          '319/319 original sparse nonrelocation bytes match. No inherited '
          'old 27-strict claim, fake locals or 943-unit full cold replay.')


if __name__=='__main__':
    main()
