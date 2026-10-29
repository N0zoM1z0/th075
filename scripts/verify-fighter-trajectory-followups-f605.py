#!/usr/bin/env python3
"""F605: true original action0x47/0x48 inside nine huge fighter functions.

For each selected original, regenerate genuine prior F598/F600/F602
case C++, cold-compile only the selected VC7.1 translation unit and
independently check two native complete case subranges, full prior case
roles, 26 genuine typed COFF targets, and all after-RET switch DATA.
No enclosing giant or case subrange is granted exact CODE credit.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
INC=ROOT/'probes/FighterTrajectoryFollowupsF605.inc'
OUT=ROOT/'.analysis/f605-trajectory-source'
ACTIONS=(0x47,0x48)
NATIVE_FIELDS={27:(0x00657480,'fcomp'),33:(0x0040FB40,'call'),
  45:(0x0065782C,'fcomp'),51:(0x00657888,'fmul'),52:(0x006406AC,'call'),
  57:(0x00657888,'fmul'),58:(0x006406AC,'call'),62:(0x00453E20,'call'),
  67:(0x0040FAC0,'call'),70:(0x00453E60,'call'),73:(0x00453D60,'call'),
  76:(0x0040FA30,'call'),84:(0x0040FB40,'call')}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name, path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None, 'missing pinned original PE reader: '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def original_action(reader,pe,decoder,boss,by,action):
    addr=boss['address']
    start,end=by[action],by[action+1]
    need(addr<=start<end<addr+boss['size'],
         f'{addr:#x}: original source code case0x{action:x} boundary is outside complete giant')
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=398 if addr==0x00564BE0 else 310
    need(end-start==size and len(native)==86
         and sum(x.size for x in native)==size and native[-1].mnemonic=='jmp',
         f'{addr:#x}: entire original native 0x{action:X} has different x86/size')
    need(native[9].mnemonic=='fld' and '+ 0x94]' in native[9].op_str
         and native[10].mnemonic=='fchs'
         and native[14].mnemonic=='mov' and native[15].mnemonic=='mov'
         and native[15].op_str.endswith(' + 0x98]')
         and native[16].mnemonic=='mov' and '+ 0x54]' in native[16].op_str
         and 'dword ptr' in native[16].op_str
         and native[18].mnemonic=='mov' and
            native[18].op_str.endswith(', '+('0x3f4ccccd' if action==0x47 else '0x3fa66666')),
         f'{addr:#x}: original 0x{action:X} direct DWORD velocity copy / drag literal changed')
    stage=int(native[23].op_str.rsplit(', ',1)[-1],0)
    early=int(native[31].op_str,0)
    late=int(native[82].op_str,0)
    need(native[23].mnemonic=='cmp' and (stage,early,late) in
         ((1,2,5),(1,2,6),(1,2,7),(2,3,5),(2,3,6),(2,3,8),
          (3,4,5),(3,4,7)),
         f'{addr:#x}: native stage/early/late action literals differ')
    shorts=[]
    for index in (54,60):
        x=native[index];m=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], ax',x.op_str)
        need(x.mnemonic=='mov' and m is not None,
             f'{addr:#x}: original native two signed-short trajectory stores changed at {index}')
        shorts.append(int(m.group(1),16))
    need(shorts[0] in (0xF00,0xEFC) and shorts[1]==shorts[0]+2,
         f'{addr:#x}: native adjacent signed-short source owner offsets changed')
    for index,(target,opcode) in NATIVE_FIELDS.items():
        ins=native[index]
        need(ins.mnemonic==opcode, f'{addr:#x}: native original typed instruction {index} drift')
        if opcode=='call':
            need(ins.op_str==f'0x{target:x}',
                 f'{addr:#x}: original true call dest {index} differs')
        else:
            need(ins.op_str==f'dword ptr [0x{target:x}]',
                 f'{addr:#x}: original real x87 float global {index} differs')
    return native,{
        'original_start':f'0x{start:08X}',
        'original_native_CODE_bytes':size,
        'original_x86_instructions':86,
        'native_stage':stage,'native_early_state':early,'native_late_state':late,
        'original_signed_short_velocity_offset':shorts[0],
        'native_float_copy_uses_dword_MOV_not_x87':True}


def reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,f602,f598,f567,info,attrs):
    src=f602.create_source(addr,boss,report,mapped,reader,pe,decoder,f598,f567,info)
    a='        case 0x47: g_FighterProbeMarker = 72; break;'
    b='        case 0x48: g_FighterProbeMarker = 73; break;'
    nextcase='        case 0x49: g_FighterProbeMarker = 74; break;'
    need(src.count(a)==src.count(b)==src.count(nextcase)==1,
         f'{addr:#x}: native next compressed switch cases are missing in source')
    start,end=src.index(a),src.index(nextcase)
    cfg=[]
    for action in ACTIONS:
        props=attrs[action]
        for key,value in [('STAGE',props['native_stage']),('EARLY',props['native_early_state']),
                          ('LATE',props['native_late_state'])]:
            cfg.append(f'#define F605_{key}{action:X} {value}')
    offset=attrs[0x47]['original_signed_short_velocity_offset']
    need(attrs[0x48]['original_signed_short_velocity_offset']==offset
         and offset==info['actual_native_counter_offset'],
         f'{addr:#x}: original 46/47/48 distinct case owner short offsets conflict')
    cfg.append(f'#define F605_COUNTER 0x{offset:X}')
    cfg.append('#include "FighterTrajectoryFollowupsF605.inc"')
    for key in ('F605_COUNTER',*[f'F605_{typ}{action:X}' for action in ACTIONS
             for typ in ('STAGE','EARLY','LATE')]):cfg.append(f'#undef {key}')
    return src[:start]+'\n'.join(cfg)+'\n'+src[end:]


def check_candidate(reader,pe,decoder,f598,f602,f600,core,zero,switch,
                    boss,report,mapped,source_code,refs,originals,info46):
    addr=boss['address'];inst=[]
    for x in decoder.disasm(source_code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',f'{addr:#x}: candidate giant has no final RET')
    ret=inst[-1].address+inst[-1].size
    # Recheck true original first 23 cases and entire after-RET DATA.
    prior=f600.compare_candidate(reader,pe,decoder,f598,core,zero,switch,
                                 boss,report,mapped,source_code,refs)
    by={r['action']:int(r['handler'],16) for r in mapped}
    orig46,meta46=f602.original_case(reader,pe,decoder,boss,by)
    f602.check_source_case(reader,pe,decoder,f598,orig46,source_code,refs,
                          inst,ret,boss,meta46)
    real_table=boss['tables'][1]
    native_index=reader.pe_bytes_at(pe,real_table['map_addr'],real_table['map_length'])
    need([native_index[action-0x33] for action in ACTIONS]==[12,13],
         f'{addr:#x}: actual native sparse indices do not point to 0x47/48')
    rows=[]
    for action in ACTIONS:
        original,attributes=originals[action]
        ordinal=12 if action==0x47 else 13
        n0=by[action];n1=by[action+1]
        native_slots=[int.from_bytes(reader.pe_bytes_at(pe,real_table['dense_addr']+4*j,4),'little')
                      for j in (ordinal,ordinal+1)]
        need(native_slots==[n0,n1],
             f'{addr:#x}: original real native dense jump boundaries drift at action {action:#x}')
        candidate_slots=[]
        for j in (ordinal,ordinal+1):
            physical=[r for r in refs if r['offset']==ret+44+4*j]
            need(len(physical)==1 and physical[0]['type']=='DIR32'
                 and physical[0]['addend']==0 and physical[0]['local_symbol_offset'] is not None,
                 f'{addr:#x}: actual candidate complete native second-switch COFF physical field missing')
            candidate_slots.append(physical[0]['local_symbol_offset'])
        c0,c1=candidate_slots
        compiled=list(decoder.disasm(source_code[c0:c1],c0))
        need(len(compiled)==len(original)==86 and c1-c0==310
             and sum(x.size for x in compiled)==310,
             f'{addr:#x}: candidate entire case{action:x} original x86 source count/length drift')
        ngram,cgram=f598.normalized(original),f598.normalized(compiled)
        difference=[(i,x,y) for i,(x,y) in enumerate(zip(ngram,cgram)) if x!=y]
        need(not difference,
             f'{addr:#x} case {action:x}: real GPR/x87/CFG role mismatch: {difference[:6]}')
        widths=[x.size-y.size for x,y in zip(original,compiled)]
        if addr==0x00564BE0:
            need(widths.count(3)==28 and widths.count(4)==1
                 and widths.count(0)==57
                 and [i for i,x in enumerate(widths) if x==4]==[48]
                 and all(original[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,x in enumerate(widths) if x==3
                         if original[i].mnemonic=='mov' and 'ebp -' in original[i].op_str),
                 f'{addr:#x}: actual wide stack 28 MOV/one JP near expansion changed')
        else:
            need(all(x==0 for x in widths),
                 f'{addr:#x}: original 86 native x86 byte widths not exactly reproduced')
        real_fields=[r for r in refs if c0<=r['offset']<c1]
        need(len(real_fields)==len(NATIVE_FIELDS)==13,
             f'{addr:#x}: original {action:#x} source physical genuine COFF fields differ')
        for i,(destination,mnemonic) in NATIVE_FIELDS.items():
            original_ins,source_ins=original[i],compiled[i]
            need(original_ins.mnemonic==source_ins.mnemonic==mnemonic,
                 f'{addr:#x}: true native typed PE operand shifted at ordinal {i}')
            candidates=[r for r in real_fields
                        if source_ins.address<=r['offset']<source_ins.address+source_ins.size]
            need(len(candidates)==1 and candidates[0]['type']==(
                 'REL32' if mnemonic=='call' else 'DIR32')
                 and candidates[0]['addend']==0
                 and candidates[0]['local_symbol_offset'] is None
                 and f602.ALL_SYMBOLS[destination] in candidates[0]['symbol'],
                 f'{addr:#x}: true original COFF call/global dest {destination:#x} differs at {i}: {candidates}')
        rows.append({'action':f'0x{action:02X}',
                     'original_native_complete_CASE_bytes':attributes['original_native_CODE_bytes'],
                     'original_complete_x86_instruction_roles':86,
                     'actual_new_generated_case_CODE_bytes':c1-c0,
                     'true_PE_COFF_relocation_fields':len(real_fields),
                     'native_velocity_copy_is_32bit_MOV':True,
                     'wide_native_EBP_receiver_loads':widths.count(3),
                     'wide_native_short_to_near_conditionals':widths.count(4),
                     'whole_original_fighter_exact':False})
    return {'original_whole_giant_boss':f'0x{addr:08X}',
            'original_enclosing_whole_CODE_bytes_still_nonexact':boss['size'],
            'original_afterRET_jump_DATA_bytes_separate':boss['postret_size'],
            'prior_23_original_source_cases_preserved':True,
            'prior_action46_roles_preserved':104,
            'two_new_original_complete_internal_cases':rows,
            'added_original_x86_roles':172,
            'added_original_inner_CODE_bytes_uncredited':sum(r['original_native_complete_CASE_bytes'] for r in rows),
            'added_true_original_typed_COFF_fields':26,
            'accepted_new_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original 86-instruction fighter; default nine affected fighter TUs')
    opts=parser.parse_args()
    f602=load('f605_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f605_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f605_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f605_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    reader=load('f605_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f605_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f605_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f605_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f605_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    selectable=[x for x in cohort if x not in (0x0045DD70,0x0058AF60)]
    selected=[int(opts.boss,0)] if opts.boss else selectable
    need(len(selectable)==9 and all(addr in selectable for addr in selected),
         'selected original giant has 113-instruction spawn variant; cannot use 86-instruction source')
    source=INC.read_text()
    need(all(source.count(f'case 0x{action:X}:')==1 for action in ACTIONS)
         and source.count('I32(0x54) = I32(0x98);')==2
         and source.count('F605_COUNTER')==4,
         'original native source bitwise 32-bit velocity copy or state declarations missing')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    results=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native46,info46=f602.original_case(reader,pe,decoder,boss,by)
        originals={action:original_action(reader,pe,decoder,boss,by,action)
                   for action in ACTIONS}
        cpp=OUT/f'Boss{addr:08X}-26-real-original-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-26-real-original-actions.obj'
        cpp.write_text(reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                    f602,f598,f567,info46,{x:pair[1] for x,pair in originals.items()}))
        p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              env=env,cwd=ROOT,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compile.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,f'{addr:#x}: real VC7.1 original source compile failed: {p.stderr[-550:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        result=check_candidate(reader,pe,decoder,f598,f602,f600,core,zero,switch,
                               boss,report,mapped,code,refs,originals,info46)
        results.append(result)
        print(f'F605 {addr:#010x}: full original action 0x47+0x48 '
              f'172/172 x86, {result["added_original_inner_CODE_bytes_uncredited"]} native inner '
              'CODE bytes, 26/26 genuine typed original PE/COFF fields; '
              'previous 24 real cases and entire switch DATA preserved, WHOLE giant NONEXACT',flush=True)
    output=OUT/('summary.json' if not opts.boss else f'summary-{selected[0]:08X}.json')
    output.write_text(json.dumps(results,indent=2)+'\n')
    print(f'F605 {len(results)} selected giant sources, {len(results)*2} original internal cases '
          f'{len(results)*172} genuine x86 roles, '
          f'{sum(x["added_original_inner_CODE_bytes_uncredited"] for x in results)} '
          f'original internal native CODE bytes and {len(results)*26} real typed COFF fields; '
          '0 new whole-exact game functions, NO full all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as error:
        print('F605 original native fighter followup source failed:',error,file=sys.stderr)
        raise SystemExit(1)
