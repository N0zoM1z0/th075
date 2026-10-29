#!/usr/bin/env python3
"""F627: one strict original 138-x86 priority-bonus mode action0x63.

Actual pinned Japanese TH075 PE, 005D73C0 strict source, and honest
0045DD70 138-x86 register-phase negative control. Only cold-compile
one original-shaped giant parent C++ translation unit at a time,
recheck 30 previous original native action cases and every original
afterRET sparse/dense switch-table COFF byte. Never credit an inner
case fragment as a whole native exact fighter function.
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
SOURCE=ROOT/'probes/FighterMode63PriorityF627.inc'
OUT=ROOT/'.analysis/f627-mode63-priority/verified'
STRICT=0x005D73C0
NEGATIVE=0x0045DD70
FIELDS={
    0:(0x006714B4,'movsx','g_ModeAt006714B4'),
    22:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    54:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    77:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    100:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    123:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    128:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    136:(0x0040FB40,'call','SetAuxActionAt40FB40'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'original native PE/source reader unavailable')
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address'];start,end=by[0x63],by[0x8C]
    true_next=min((p for p in set(by.values()) if p>start),default=None)
    size=533 if addr==NEGATIVE else 534
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    need(addr<=start<end<addr+boss['size'] and end==true_next
         and end-start==size and len(native)==138
         and sum(x.size for x in native)==size and native[-1].mnemonic=='jmp',
         f'{addr:#x}: real original priority0x63 x86 count/physical boundary changed')
    need(native[0].mnemonic=='movsx' and native[0].op_str.endswith('byte ptr [0x6714b4]')
         and native[1].mnemonic=='cmp' and native[1].op_str.endswith(', 3')
         and native[2].mnemonic=='jne' and native[2].op_str==f'0x{native[7].address:x}'
         and native[6].mnemonic=='jne' and native[6].op_str==f'0x{native[27].address:x}'
         and native[26].mnemonic=='jmp' and native[26].op_str==f'0x{native[127].address:x}'
         and native[43].mnemonic=='movsx' and '+ 0x370]' in native[43].op_str
         and native[44].mnemonic=='cmp' and native[44].op_str.endswith(', 5')
         and native[45].mnemonic=='jne' and native[45].op_str==f'0x{native[56].address:x}'
         and native[49].mnemonic=='movsx' and '+ 0x32a]' in native[49].op_str
         and native[50].mnemonic=='cmp' and native[50].op_str.endswith(', 2')
         and native[51].mnemonic=='jne' and native[51].op_str==f'0x{native[56].address:x}'
         and native[52].mnemonic=='push' and native[52].op_str=='0x303'
         and native[55].mnemonic=='jmp'
         and native[73].mnemonic=='cmp' and native[73].op_str.endswith(', 2')
         and native[75].mnemonic=='push' and native[75].op_str=='0x31c'
         and native[96].mnemonic=='cmp' and native[96].op_str.endswith(', 1')
         and native[119].mnemonic=='test' and native[120].mnemonic=='jne'
         and native[134].mnemonic=='push' and native[134].op_str=='2',
         f'{addr:#x}: original actual priority bonus byte/original case exit CFG differs')
    for i,(target,mn,_) in FIELDS.items():
        x=native[i]
        need(x.mnemonic==mn and (
              x.op_str.endswith('byte ptr [0x6714b4]') if i==0
              else x.op_str==f'0x{target:x}'),
             f'{addr:#x}: original native typed PE mode byte/callee {target:#x} at ordinal {i} wrong')
    return native,{'original_native_case_start':f'0x{start:08X}',
                   'original_next_physical_case0x8C':f'0x{end:08X}',
                   'original_full_internal_CODE_bytes':size,
                   'complete_original_x86_roles':138,
                   'original_first_priority_flag':5,
                   'original_first_priority_action':0x303,
                   'original_followup_action':0x31C,
                   'original_typed_PE_COFF_fields':8,
                   'original_entire_fighter_exact':False}


def build_source(addr,boss,report,mapped,reader,pe,decoder,
               f598,f567,f600,f602,f603,f605,f606,f607,f608,
               f610,f611,f613,f614):
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev,meta=f614.native_case(reader,pe,decoder,boss,by)
    source=f614.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                  f598,f567,f600,f602,f603,f605,f606,f607,f608,
                  f610,f611,f613,meta)
    marker='        case 0x63: g_FighterProbeMarker = 100; break;'
    decl='extern float g_ThresholdAt0065782C;'
    need(source.count(marker)==source.count(decl)==1,
         f'{addr:#x}: original giant source last packed action/global placeholder missing')
    return source.replace(decl,'extern signed char g_ModeAt006714B4;\n'+decl).replace(
                  marker,'#include "FighterMode63PriorityF627.inc"')


def compare_source(reader,pe,decoder,boss,report,mapped,code,refs,native,info,
                 negative,f598,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,f614,core,zero,switch):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: entire giant source RET absent')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original physical afterRET separately owned jump DATA lost')
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev,previnfo=f614.native_case(reader,pe,decoder,boss,by)
    f614.compare_candidate(reader,pe,decoder,f598,f600,f602,f603,
                f605,f606,f607,f608,f610,f611,f613,core,zero,switch,
                boss,report,mapped,code,refs,prev,previnfo)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(len(sparse)==49 and table['slots']==26 and sparse[0x63-0x33]==24,
         f'{addr:#x}: native compressed original case0x63 last actual index differs')
    ptr=int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+24*4,4),'little')
    need(ptr==by[0x63],f'{addr:#x}: original PE last real dense slot24 handler target changed')
    refs63=[x for x in refs if x['offset']==ret+44+24*4]
    need(len(refs63)==1 and refs63[0]['type']=='DIR32' and refs63[0]['addend']==0
         and refs63[0]['local_symbol_offset'] is not None,
         f'{addr:#x}: source actual packed case0x63 dense slot24 COFF label absent')
    low=refs63[0]['local_symbol_offset']
    # The real next original CODE case 0x8C is not dense slot26
    # (which is the shared default); locate the actual following source
    # marker physically to avoid truncating original 138 instructions.
    markers=[x for x in refs if x['offset']>low and 'g_FighterProbeMarker' in x['symbol']]
    need(markers,f'{addr:#x}: next actual case0x8C source marker missing')
    first=min(x['offset'] for x in markers)
    following=next((x for x in ins if x.address<=first<x.address+x.size),None)
    need(following is not None and following.mnemonic=='mov'
         and following.op_str.endswith(', 0x8d'),
         f'{addr:#x}: source next real native handler after case0x63 is not 0x8C')
    high=following.address
    generated=list(decoder.disasm(code[low:high],low))
    need(len(generated)==len(native)==138 and high-low==534
         and sum(x.size for x in generated)==534,
         f'{addr:#x}: generated C++ not full original 138-instruction 534B priority case')
    widths=[x.size-y.size for x,y in zip(native,generated)]
    if not negative:need(all(x==0 for x in widths),
                         f'{addr:#x}: original native priority owner instruction bytes lengths differ')
    else:need(any(x!=0 for x in widths),
              f'{addr:#x}: original negative 533-byte owner unexpectedly source-width exact')
    physical=[x for x in refs if low<=x['offset']<high]
    need(len(physical)==len(FIELDS)==8,
         f'{addr:#x}: missing original true 8 physical typed PE/COFF fields')
    for i,(target,mn,sym) in FIELDS.items():
        a,b=native[i],generated[i]
        need(a.mnemonic==b.mnemonic==mn,
             f'{addr:#x}: native priority typed x86 ordinal {i} changed')
        matches=[x for x in physical if b.address<=x['offset']<b.address+b.size]
        need(len(matches)==1 and matches[0]['type']==('DIR32' if i==0 else 'REL32')
             and matches[0]['addend']==0 and matches[0]['local_symbol_offset'] is None
             and sym in matches[0]['symbol'],
             f'{addr:#x}: source typed PE target {target:#x} at {i} wrong: {matches}')
    a,b=f598.normalized(native),f598.normalized(generated)
    need(a[0][1].endswith('byte ptr [0x6714b4]') and b[0][1].endswith('byte ptr [0]'),
         f'{addr:#x}: physically checked native global DIR32 at ordinal0 shifted')
    a[0]=b[0]=('movsx','NATIVE_TYPED_GLOBAL_006714B4')
    mismatch=[(i,x,y) for i,(x,y) in enumerate(zip(a,b)) if x!=y]
    need(len(mismatch)==(87 if negative else 0),
         f'{addr:#x}: native priority register/CFG mismatches {len(mismatch)}, '
         f'expected {(87 if negative else 0)}: {mismatch[:6]}')
    return {'original_entire_boss':f'0x{addr:08X}',
            'whole_original_giant_CODE_still_NONEXACT':boss['size'],
            'original_afterRET_DATA_separate_bytes':boss['postret_size'],
            'previous_30_real_original_case_bodies_preserved_on_same_OBJ':True,
            'original_priority_native_case0x63':info,
            'source_actual_PE_COFF_fields':8,
            'native_original_GPR_x87_CFG_role_mismatches':len(mismatch),
            'new_strict_native_inner_CODE_bytes_uncredited':0 if negative else 534,
            'new_accepted_whole_game_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--negative-actor',action='store_true',help='build genuine 0045DD70 533B/138-x86 register-phase negative')
    opts=p.parse_args()
    addr=NEGATIVE if opts.negative_actor else STRICT
    source=SOURCE.read_text()
    need(source.count('case 0x63:')==1
         and source.count('RAW+0x370+')==1
         and source.count('SetNativeActionAt40FAC0(0x303)')==1
         and source.count('SetNativeActionAt40FAC0(0x31C)')==2,
         'native priority bonus original C++ case grammar changed')
    f602=load('f627_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f627_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f627_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f627_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f627_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f627_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f627_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f627_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f627_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f627_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f627_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f613=load('f627_f613',ROOT/'scripts/verify-fighter-trajectory-recovery-f613.py')
    f614=load('f627_f614',ROOT/'scripts/verify-fighter-trajectory-burst-f614.py')
    rd=load('f627_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f627_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f627_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f627_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f627_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    b=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
           if x['address']==addr)
    report,mapped=actions.report_boss(rd,pe,dec,b)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original,info=original_case(rd,pe,dec,b,by)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'Boss{addr:08X}-31-real-original-actions.cpp'
    obj=OUT/f'Boss{addr:08X}-31-real-original-actions.obj'
    cpp.write_text(build_source(addr,b,report,mapped,rd,pe,dec,
              f598,f567,f600,f602,f603,f605,f606,f607,f608,
              f610,f611,f613,f614))
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=185)
    (OUT/f'Boss{addr:08X}-compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,
         f'{addr:#x}: pinned original whole-fighter VC7.1 source failed: {p.stderr[-450:]}')
    code,refs=rd.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
    result=compare_source(rd,pe,dec,b,report,mapped,code,refs,original,info,
             opts.negative_actor,f598,f600,f602,f603,f605,f606,f607,f608,
             f610,f611,f613,f614,core,zero,switch)
    out=OUT/('negative-summary.json' if opts.negative_actor else 'positive-summary.json')
    out.write_text(json.dumps(result,indent=2)+'\n')
    print(f'F627 {addr:#010x}: real entire original 0x63 '
          f'138/138 native x86, {info["original_full_internal_CODE_bytes"]} '
          f'original inner CODE bytes, 8/8 genuine typed PE/COFF fields; '
          f'{result["native_original_GPR_x87_CFG_role_mismatches"]} register/CFG source differences; '
          'all 30 original prior case roles and afterRET table preserved, '
          'whole giant NONEXACT.',flush=True)
    print(f'F627 strict native original priority source adds '
          f'{result["new_strict_native_inner_CODE_bytes_uncredited"]} original inner CODE bytes, '
          'ZERO accepted whole exact game functions, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F627 original TH075 bonus-priority game source proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
