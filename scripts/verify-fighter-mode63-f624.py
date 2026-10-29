#!/usr/bin/env python3
"""F624: original 118-x86 native action0x63 in two huge fighter parents.

Actual Japanese TH075 source-backed whole native case CODE grammar:
mode-global short circuit, owner-state gating, three action branches,
independent bonus action and physical real PE+COFF game-call targets.
Only cold-compile selected giant C++ translation units, independently
recheck F622 case0x62, previous F614 30 original case role proofs, and
all complete original separately owned after-RET jump DATA.
Never count any case interior or incomplete fighter as an exact full
native game function; pending original source provenance unchanged.
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
SOURCE=ROOT/'probes/FighterMode63F624.inc'
OUT=ROOT/'.analysis/f624-mode63-verified'
ACTORS=(0x00564BE0,0x005AEEC0)
REAL_FIELDS={
    0:(0x006714B4,'movsx','g_ModeAt006714B4'),
    22:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    48:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    57:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    80:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    103:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    108:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    116:(0x0040FB40,'call','SetAuxActionAt40FB40'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'missing pinned original PE source helper '+str(path))
    module=importlib.util.module_from_spec(sp)
    sys.modules[name]=module
    sp.loader.exec_module(module)
    return module


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address'];s=by[0x63];t=by[0x8C]
    following=min((v for v in set(by.values()) if v>s),default=None)
    n=list(decoder.disasm(reader.pe_bytes_at(pe,s,t-s),s))
    length=552 if addr==0x00564BE0 else 455
    need(addr<=s<t<addr+boss['size'] and t==following
         and t-s==length and len(n)==118 and sum(x.size for x in n)==length
         and n[-1].mnemonic=='jmp',
         f'{addr:#x}: full original native 0x63 to 0x8C boundary, x86 count or size changed')
    need(n[0].mnemonic=='movsx' and n[0].op_str=='ecx, byte ptr [0x6714b4]'
         and n[1].mnemonic=='cmp' and n[1].op_str=='ecx, 3'
         and n[2].mnemonic=='jne' and n[2].op_str==f'0x{n[7].address:x}'
         and n[6].mnemonic=='jne' and n[6].op_str==f'0x{n[27].address:x}'
         and n[26].mnemonic=='jmp' and n[26].op_str==f'0x{n[107].address:x}'
         and n[54].mnemonic=='jne' and n[54].op_str==f'0x{n[58].address:x}'
         and n[43].mnemonic=='movsx' and '+ 0x32a]' in n[43].op_str
         and n[52].mnemonic=='movsx' and '+ 0x370]' in n[52].op_str
         and n[44].mnemonic=='cmp' and n[44].op_str.endswith(', 2')
         and n[76].mnemonic=='cmp' and n[76].op_str.endswith(', 1')
         and n[99].mnemonic=='test' and n[100].mnemonic=='jne'
         and n[107].mnemonic=='mov' and n[108].mnemonic=='call'
         and n[114].mnemonic=='push' and n[114].op_str=='2',
         f'{addr:#x}: original PE real mode-3 gating or extra action-stage CFG differs')
    bonus_flag=int(n[53].op_str.rsplit(', ',1)[-1],0)
    bonus_action=int(n[55].op_str,0)
    need((bonus_flag,bonus_action)==((4,0x302) if addr==0x00564BE0 else (5,0x31D)),
         f'{addr:#x}: native unique secondary action/bonus condition differs')
    for i,(target,mn,symbol) in REAL_FIELDS.items():
        x=n[i]
        if i==0:
            need(x.mnemonic==mn and x.op_str=='ecx, byte ptr [0x6714b4]',
                 f'{addr:#x}: original game mode global byte ref at x860 changed')
        else:
            need(x.mnemonic==mn and x.op_str==f'0x{target:x}',
                 f'{addr:#x}: native original call/aux global {target:#x} at x86{i} changed')
    return n,{'original_native_case0x63_start':f'0x{s:08X}',
              'original_native_next_case0x8C_start':f'0x{t:08X}',
              'original_whole_internal_CODE_bytes':length,
              'complete_native_x86_instructions':118,
              'native_extra_bonus_flag':bonus_flag,
              'native_extra_bonus_action':bonus_action,
              'original_native_PE_COFF_fields':len(REAL_FIELDS),
              'original_entire_giant_exact':False}


def natural_source(addr,boss,report,mapped,reader,pe,decoder,
                   f598,f567,f600,f602,f603,f605,f606,f607,f608,
                   f610,f611,f613,f614,f622,info):
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev,previnfo=f622.native_case(reader,pe,decoder,boss,by)
    raw=f622.with_source(addr,boss,report,mapped,reader,pe,decoder,
           f598,f567,f600,f602,f603,f605,f606,f607,f608,
           f610,f611,f613,f614,previnfo)
    needle='        case 0x63: g_FighterProbeMarker = 100; break;'
    need(raw.count(needle)==1,f'{addr:#x}: next natural original 0x63 placeholder moved')
    decl='extern float g_ThresholdAt0065782C;'
    need(raw.count(decl)==1,f'{addr:#x}: original giant global declaration missing')
    raw=raw.replace(decl,'extern signed char g_ModeAt006714B4;\n'+decl)
    added=(f'#define F624_BONUS_FLAG {info["native_extra_bonus_flag"]}\n'
           f'#define F624_BONUS_ACTION 0x{info["native_extra_bonus_action"]:X}\n'
           '#include "FighterMode63F624.inc"\n'
           '#undef F624_BONUS_FLAG\n#undef F624_BONUS_ACTION')
    return raw.replace(needle,added)


def check_source(reader,pe,decoder,boss,report,mapped,code,refs,
                 original,info,f598,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,f614,f622,core,zero,switch):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: whole giant source no final RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: native original separately owned packed after-RET DATA extent changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev,previnfo=f622.native_case(reader,pe,decoder,boss,by)
    f622.check_obj(reader,pe,decoder,boss,report,mapped,code,refs,prev,previnfo,
              f598,f600,f602,f603,f605,f606,f607,f608,f610,f611,f613,f614,
              core,zero,switch,False)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(sparse[0x63-0x33]==25 and len(sparse)==49 and table['slots']==27,
         f'{addr:#x}: original last packed 0x63 action physical table mapping differs')
    pointer=int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*25,4),'little')
    need(pointer==by[0x63],
         f'{addr:#x}: real native compressed case0x63 dense pointer target incorrect')
    physical=[r for r in refs if r['offset']==ret+44+4*25]
    need(len(physical)==1 and physical[0]['type']=='DIR32'
         and physical[0]['addend']==0 and physical[0]['local_symbol_offset'] is not None,
         f'{addr:#x}: new source missing real packed dense original case0x63 label')
    low=physical[0]['local_symbol_offset']
    # Original case0x8C is the NEXT PHYSICAL CODE handler, not a member
    # of this compressed sparse map. The probe retains a distinct
    # case0x8C marker 141 (=0x8D) at the real source code boundary;
    # never substitute packed slot26's common-default handler as a
    # convenient fake/truncated end to case0x63.
    markers=[r for r in refs if r['offset']>low and 'g_FighterProbeMarker' in r['symbol']]
    need(markers,f'{addr:#x}: actual next named C++ case0x8C marker missing')
    first=min(r['offset'] for r in markers)
    next_case=next((x for x in ins if x.address<=first<x.address+x.size),None)
    need(next_case is not None and next_case.mnemonic=='mov'
         and next_case.op_str.endswith(', 0x8d'),
         f'{addr:#x}: source 0x8C must be the first successor of full 0x63 case')
    high=next_case.address
    source=list(decoder.disasm(code[low:high],low))
    need(len(source)==len(original)==118 and high-low==455
         and sum(x.size for x in source)==455,
         f'{addr:#x}: natural VC7.1 source 0x63 no longer whole 118-x86/455-byte case')
    widths=[x.size-y.size for x,y in zip(original,source)]
    if addr==0x00564BE0:
        need(widths.count(3)==31 and widths.count(4)==1
             and widths.count(0)==86
             and [i for i,w in enumerate(widths) if w==4]==[30]
             and all(original[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i,w in enumerate(widths) if w==3),
             f'{addr:#x}: genuine 31 native wide EBP loads + one conditional branch expansion changed')
    else:
        need(all(x==0 for x in widths),
             f'{addr:#x}: original 455-byte native compact 0x63 x86 widths differ')
    found=[x for x in refs if low<=x['offset']<high]
    need(len(found)==len(REAL_FIELDS)==8,
         f'{addr:#x}: original case0x63 missing real 8 physical call/global PE/COFF fields')
    for i,(dest,mn,symbol) in REAL_FIELDS.items():
        native,compiled=original[i],source[i]
        need(native.mnemonic==compiled.mnemonic==mn,
             f'{addr:#x}: real native 0x63 codegen typed instruction {i} shifted')
        real=[x for x in found if compiled.address<=x['offset']<compiled.address+compiled.size]
        need(len(real)==1 and real[0]['type']==('DIR32' if i==0 else 'REL32')
             and real[0]['addend']==0 and real[0]['local_symbol_offset'] is None
             and symbol in real[0]['symbol'],
             f'{addr:#x}: actual original typed PE target {dest:#x} at {i} COFF symbol differs: {real}')
    original_roles,source_roles=f598.normalized(original),f598.normalized(source)
    need(original_roles[0]==('movsx','ecx, byte ptr [0x6714b4]')
         and source_roles[0]==('movsx','ecx, byte ptr [0]'),
         f'{addr:#x}: original real mode byte field operand changed')
    # Only the physically checked DIR32 PE global may be normalized.
    original_roles[0]=source_roles[0]=('movsx','ecx, byte ptr [NATIVE_REAL_MODE_006714B4]')
    differences=[(i,x,y) for i,(x,y) in enumerate(zip(original_roles,source_roles)) if x!=y]
    need(not differences,
         f'{addr:#x}: original complete native 118-x86 GPR/x87/CFG roles differ: {differences[:8]}')
    return {'original_entire_giant_boss':f'0x{addr:08X}',
            'original_entire_giant_CODE_still_NONEXACT':boss['size'],
            'original_afterRET_jump_DATA_separately_owned':boss['postret_size'],
            'earlier_31_actual_original_game_case_source_proofs_retained':True,
            'complete_original_native_action0x63':info,
            'new_original_internal_CODE_bytes_uncredited':info['original_whole_internal_CODE_bytes'],
            'new_real_native_x86_GPR_x87_CFG_roles':118,
            'new_original_PE_COFF_zero_addend_fields':8,
            'new_authored_exact_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one native whole 118-instruction case0x63 owner; default two affected sources')
    opt=parser.parse_args()
    selected=[int(opt.boss,0)] if opt.boss else list(ACTORS)
    need(all(addr in ACTORS for addr in selected),
         'native original other fighters have 109/138 variants; cannot claim 118-x86 source')
    source=SOURCE.read_text()
    need(source.count('case 0x63:')==1 and source.count('g_ModeAt006714B4 != 3')==1
         and source.count('RAW+0x2CD)==0')==1
         and source.count('SetNativeActionAt40FAC0(0x31C)')==2
         and source.count('break;')==5,
         'genuine source mode3 short circuit/bonus stage branch changed')
    f602=load('f624_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f624_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f624_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f624_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f624_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f624_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f624_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f624_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f624_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f624_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f624_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f613=load('f624_f613',ROOT/'scripts/verify-fighter-trajectory-recovery-f613.py')
    f614=load('f624_f614',ROOT/'scripts/verify-fighter-trajectory-burst-f614.py')
    f622=load('f624_f622',ROOT/'scripts/verify-fighter-counter-dispatch-f622.py')
    reader=load('f624_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f624_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f624_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f624_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f624_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native,info=original_case(reader,pe,decoder,boss,by)
        generated=natural_source(addr,boss,report,mapped,reader,pe,decoder,
                    f598,f567,f600,f602,f603,f605,f606,f607,f608,
                    f610,f611,f613,f614,f622,info)
        cpp=OUT/f'Boss{addr:08X}-32-original-native-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-32-original-native-actions.obj'
        cpp.write_text(generated)
        comp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(comp.stdout+comp.stderr)
        need(comp.returncode==0,
             f'{addr:#x}: original VC7.1 whole fighter native source build failed: {comp.stderr[-470:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        result=check_source(reader,pe,decoder,boss,report,mapped,code,refs,
                 native,info,f598,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,f614,f622,core,zero,switch)
        rows.append(result)
        print(f'F624 {addr:#010x}: complete native original action0x63 '
              f'118/118 x86 GPR/x87/CFG roles, {info["original_whole_internal_CODE_bytes"]} '
              'original inner CODE bytes, 8/8 genuine typed PE/COFF '
              'call/global fields; earlier 31 original game cases and '
              'entire afterRET switch DATA preserved; whole giant NONEXACT',flush=True)
    out=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    out.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F624 {len(rows)} selected whole giant source TUs: '
          f'{len(rows)*118} original native x86 roles / '
          f'{sum(r["new_original_internal_CODE_bytes_uncredited"] for r in rows)} '
          f'original uncredited interior CODE bytes / {len(rows)*8} typed original COFF; '
          'no new whole exact native function, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F624 original Japanese TH075 event/state action63 failed:',e,file=sys.stderr)
        raise SystemExit(1)
