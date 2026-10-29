#!/usr/bin/env python3
"""F622: original packed action0x62 four-way unsigned collision OR.

Source-backed exact native GPR/x87/CFG inner-case grammar for TWO
selected giant fighter owners, with original wide EBP receiver and
+0xEFC peculiarities. Rebuild only selected whole giant C++ source TUs,
recheck prior 30 native action case subranges and separately owned
original packed after-RET DATA, 4 real typed COFF game-call targets.
Optional full-geometry native source negatives show register-phase
mismatch in 0045DD70 (40) and native 004AC040 short case (10).
NEVER count case fragments as accepted exact whole fighter functions.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/FighterCounterDispatch62F622.inc'
OUT=ROOT/'.analysis/f622-counter-dispatch/verified'
GOOD=(0x00564BE0,0x005AEEC0)
NEGATIVE=(0x0045DD70,0x004AC040)
ACTIONS={41:(0x0040FA30,'GetNativeActionAt40FA30'),
         49:(0x0040FAC0,'SetNativeActionAt40FAC0'),
         56:(0x0040FAC0,'SetNativeActionAt40FAC0'),
         63:(0x0040FAC0,'SetNativeActionAt40FAC0')}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'missing pinned native original source verifier: '+str(path))
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def native_case(reader,pe,decoder,boss,by):
    addr=boss['address'];s,t=by[0x62],by[0x63]
    n=list(decoder.disasm(reader.pe_bytes_at(pe,s,t-s),s))
    count=25 if addr==0x004AC040 else 65
    size=87 if addr==0x004AC040 else (312 if addr==0x00564BE0 else 249)
    need(addr<=s<t<addr+boss['size'] and len(n)==count
         and t-s==size and sum(x.size for x in n)==size
         and n[-1].mnemonic=='jmp',
         f'{addr:#x}: real original complete native 0x62 action extent/count/size changed')
    counter=0xEFC if addr==0x005AEEC0 else 0xF00
    if count==65:
        need(n[1].mnemonic=='movsx' and '+ 0x66]' in n[1].op_str,
             f'{addr:#x}: invalid original collision source byte direction operand')
        need(n[3].mnemonic=='imul' and '+ 0x4dc]' in n[3].op_str
             and n[4].mnemonic=='test' and n[5].mnemonic=='jle'
             and n[23].mnemonic=='imul' and n[24].mnemonic=='test'
             and n[25].mnemonic=='jge',
             f'{addr:#x}: real native signed direction multiplied by collision velocity differs')
        # This is the crucial original conditional semantic discovery:
        # THREE unsigned JA branches jump *into* the assignment; the
        # fourth unsigned JBE skips it. Logical four-way OR, NOT AND.
        for indexes,hit,skip in (((8,11,14,17),18,20),((28,31,34,37),38,40)):
            for j in indexes[:3]:
                need(n[j].mnemonic=='ja' and n[j].op_str==f'0x{n[hit].address:x}',
                     f'{addr:#x}: unsigned original native field OR early-hit jcc at {j} changed')
            last=indexes[-1]
            need(n[last].mnemonic=='jbe' and n[last].op_str==f'0x{n[skip].address:x}',
                 f'{addr:#x}: original unsigned fourth field no-hit jcc at {last} changed')
        need(n[19].mnemonic=='mov' and f'+ 0x{counter:x}]' in n[19].op_str
             and n[19].op_str.endswith(', 1')
             and n[39].mnemonic=='mov' and f'+ 0x{counter:x}]' in n[39].op_str
             and n[39].op_str.endswith(', 2'),
             f'{addr:#x}: original signed-short native collision owner counter incorrect')
    else:
        need(n[0].mnemonic=='mov' and n[1].mnemonic=='call'
             and n[1].op_str=='0x40fa30'
             and n[7].op_str=='0x5f' and n[14].op_str=='0x5d'
             and n[21].op_str=='0x5e'
             and n[11].mnemonic=='movsx' and f'+ 0x{counter:x}]' in n[11].op_str,
             f'{addr:#x}: original actor-specific no-collision 25-x86 owner differs')
    fields={i-(40 if count==25 else 0):(target,sym) for i,(target,sym) in ACTIONS.items()}
    need(len(fields)==4,'actual 4 real game calls lost')
    for i,(target,sym) in fields.items():
        need(n[i].mnemonic=='call' and n[i].op_str==f'0x{target:x}',
             f'{addr:#x}: genuine native direct call target {target:#x} at {i} differs')
    return n,{'real_native_complete_start':f'0x{s:08X}',
              'original_whole_case_CODE_bytes':size,
              'original_x86_instructions':count,
              'actual_short_motion_counter_offset':counter,
              'native_is_unsigned_four_field_collision_OR':count==65,
              'native_typed_call_fields':fields,
              'enclosing_giant_whole_exact':False}


def with_source(addr,boss,report,mapped,reader,pe,decoder,
                f598,f567,f600,f602,f603,f605,f606,f607,f608,
                f610,f611,f613,f614,info):
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev,meta=f614.native_case(reader,pe,decoder,boss,by)
    src=f614.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
           f598,f567,f600,f602,f603,f605,f606,f607,f608,
           f610,f611,f613,meta)
    needle='        case 0x62: g_FighterProbeMarker = 99; break;'
    need(src.count(needle)==1,f'{addr:#x}: original next second-switch source case0x62 placeholder moved')
    additions=(f'#define F622_COUNTER 0x{info["actual_short_motion_counter_offset"]:X}\n'
               f'#define F622_CHECK_DIRECTION {int(info["native_is_unsigned_four_field_collision_OR"])}\n'
               '#include "FighterCounterDispatch62F622.inc"\n'
               '#undef F622_COUNTER\n#undef F622_CHECK_DIRECTION')
    return src.replace(needle,additions)


def check_obj(reader,pe,decoder,boss,report,mapped,code,refs,native,info,
              f598,f600,f602,f603,f605,f606,f607,f608,f610,f611,f613,f614,
              core,zero,switch,negative):
    addr=boss['address'];original_count=info['original_x86_instructions']
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: whole giant C++ source RET missing')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original physical complete afterRET packed DATA changed')
    by={r['action']:int(r['handler'],16) for r in mapped}
    prev,previnfo=f614.native_case(reader,pe,decoder,boss,by)
    f614.compare_candidate(reader,pe,decoder,f598,f600,f602,f603,
            f605,f606,f607,f608,f610,f611,f613,core,zero,switch,
            boss,report,mapped,code,refs,prev,previnfo)
    table=boss['tables'][1]
    mapx=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    s,e=[mapx[i-0x33] for i in (0x62,0x63)]
    need(e==s+1 and s in (23,24),f'{addr:#x}: native real original packed index 0x62/0x63 moved')
    pointers=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little') for i in (s,e)]
    need(pointers==[by[0x62],by[0x63]],
         f'{addr:#x}: actual original indexed physical native case0x62/0x63 handlers differ')
    positions=[]
    for j in (s,e):
        physical=[x for x in refs if x['offset']==ret+44+j*4]
        need(len(physical)==1 and physical[0]['type']=='DIR32' and physical[0]['addend']==0
             and physical[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: real packed physical case0x62/0x63 source label COFF field missing')
        positions.append(physical[0]['local_symbol_offset'])
    low,high=positions
    actual=list(decoder.disasm(code[low:high],low))
    expected_source_bytes=87 if original_count==25 else 249
    need(len(actual)==len(native)==original_count
         and high-low==expected_source_bytes
         and sum(x.size for x in actual)==expected_source_bytes,
         f'{addr:#x}: source complete original action0x62 count/bytes differ')
    widths=[x.size-y.size for x,y in zip(native,actual)]
    if addr==0x00564BE0:
        need(widths.count(3)==21 and widths.count(0)==44
             and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i,v in enumerate(widths) if v==3),
             'wide original 0x62 owner requires exactly 21 widened native MOV receivers')
    else:need(all(x==0 for x in widths),
              f'{addr:#x}: original compact case0x62 native physical instruction widths changed')
    typed=[r for r in refs if low<=r['offset']<high]
    fields=info['native_typed_call_fields']
    need(len(typed)==len(fields)==4,
         f'{addr:#x}: actual four physical typed original native/COFF fields missing')
    for i,(dest,symbol) in fields.items():
        x=actual[i]
        need(x.mnemonic==native[i].mnemonic=='call'
             and native[i].op_str==f'0x{dest:x}',
             f'{addr:#x}: actual original game C++ source call moved at native ordinal{i}')
        match=[r for r in typed if x.address<=r['offset']<x.address+x.size]
        need(len(match)==1 and match[0]['type']=='REL32'
             and match[0]['addend']==0 and match[0]['local_symbol_offset'] is None
             and symbol in match[0]['symbol'],
             f'{addr:#x}: PE-target source COFF call {dest:#x} at {i} differs: {match}')
    lhs,rhs=f598.normalized(native),f598.normalized(actual)
    mismatches=[(i,n,c) for i,(n,c) in enumerate(zip(lhs,rhs)) if n!=c]
    expected_error=(10 if original_count==25 else 40) if negative else 0
    need(len(mismatches)==expected_error,
         f'{addr:#x}: genuine original case0x62 GPR/CFG roles {len(mismatches)} mismatches, '
         f'expected {expected_error}: {mismatches[:7]}')
    return {'original_entire_boss':f'0x{addr:08X}',
            'original_complete_whole_CODE_still_NONEXACT':boss['size'],
            'native_afterRET_packed_DATA_separate':boss['postret_size'],
            'all_30_previous_giant_case_bodies_source_preserved':True,
            'original_complete_case0x62':info,
            'physical_case0x62_native_COFF_targets':len(typed),
            'real_original_full_case_native_GPR_CFG_role_mismatches':len(mismatches),
            'new_strict_inner_original_CODE_bytes_uncredited':0 if negative else info['original_whole_case_CODE_bytes'],
            'accepted_new_whole_function_CODE_bytes':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original 65-x86 strict owner; default both 00564BE0/005AEEC0')
    parser.add_argument('--negative-actor',choices=['0x0045DD70','0x004AC040'],
                        help='one original 40- or 10-role mismatch control')
    opt=parser.parse_args()
    need(not(opt.boss and opt.negative_actor),'choose one original actor testing mode')
    if opt.negative_actor:selected=[int(opt.negative_actor,0)]
    else:selected=[int(opt.boss,0)] if opt.boss else list(GOOD)
    negative=bool(opt.negative_actor)
    need(all(x in (NEGATIVE if negative else GOOD) for x in selected),
         'cannot treat a different original GPR-phase actor as strict role match')
    source=SOURCE.read_text()
    need(source.count('case 0x62:')==1 and source.count('F622_CHECK_DIRECTION')==1
         and source.count('unsigned int*')==8 and source.count('||')==6
         and source.count('I16(F622_COUNTER)=1;')==1
         and source.count('I16(F622_COUNTER)=2;')==1,
         'genuine PE four unsigned collision fields OR source has changed')
    f602=load('f622_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f622_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f622_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f622_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f622_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f622_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f622_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f622_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f622_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f622_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f622_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f613=load('f622_f613',ROOT/'scripts/verify-fighter-trajectory-recovery-f613.py')
    f614=load('f622_f614',ROOT/'scripts/verify-fighter-trajectory-burst-f614.py')
    rd=load('f622_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f622_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f622_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f622_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f622_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    receipts=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(rd,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native,info=native_case(rd,pe,decoder,boss,by)
        src=with_source(addr,boss,report,mapped,rd,pe,decoder,
              f598,f567,f600,f602,f603,f605,f606,f607,f608,
              f610,f611,f613,f614,info)
        cpp=OUT/f'Boss{addr:08X}-31-original-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-31-original-actions.obj'
        cpp.write_text(src)
        p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,
             f'{addr:#x}: pinned VC7.1 whole giant natural source fails: {p.stderr[-470:]}')
        code,refs=rd.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        result=check_obj(rd,pe,decoder,boss,report,mapped,code,refs,native,info,
              f598,f600,f602,f603,f605,f606,f607,f608,f610,f611,f613,f614,
              core,zero,switch,negative)
        receipts.append(result)
        print(f'F622 {addr:#010x}: original action62 {info["original_x86_instructions"]}/'
              f'{info["original_x86_instructions"]} x86, '
              f'{info["original_whole_case_CODE_bytes"]} native interior CODE B, '
              '4 genuine typed original PE/COFF game calls, '
              f'{result["real_original_full_case_native_GPR_CFG_role_mismatches"]} GPR/CFG '
              'role mismatches; previous 30 cases and afterRET DATA preserved, '
              'whole boss NONEXACT',flush=True)
    out=OUT/('summary-negative.json' if negative else ('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json'))
    out.write_text(json.dumps(receipts,indent=2)+'\n')
    print(f'F622 {len(receipts)} selected giant whole-source TU compilations; '
          f'{sum(x["new_strict_inner_original_CODE_bytes_uncredited"] for x in receipts)} '
          'original inner native CODE bytes strictly source-backed and UNcredited; '
          'ZERO new complete authored exact function, NO all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F622 original TH075 unsigned collision OR verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
