#!/usr/bin/env python3
"""F626: strict 109-x86 original native action0x63 in five giant fighters.

Selected ORIGINAL Japanese TH075 PE case boundaries (real last packed
second-switch slot25 to actual next native 0x8C handler) and 7 actual
typed physical PE/COFF global/call fields. Cold-compile only selected
whole giant C++ source TU, revalidate all prior 30 F614 original
case grammars and full separate after-RET DATA, and explicitly preserve
nonmatching 67-role variants (after the proven DIR32 global) in two other original 109-x86 actors.
NO split-case exact credit, NO whole giant exact, NO all-unit cold replay.
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
SOURCE=ROOT/'probes/FighterMode63BasicF626.inc'
OUT=ROOT/'.analysis/f626-mode63-regular/verified'
GOOD=(0x004AC040,0x00486550,0x00543210,0x004D7E70,0x005214B0)
NEG=(0x004F7130,0x0058AF60)
FIELDS={0:(0x006714B4,'movsx','g_ModeAt006714B4'),
        22:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
        48:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
        71:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
        94:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
        99:(0x0040FA30,'call','GetNativeActionAt40FA30'),
        107:(0x0040FB40,'call','SetAuxActionAt40FB40')}


def need(value,message):
    if not value:raise ValueError(message)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'original PE/whole source verifier unavailable')
    module=importlib.util.module_from_spec(sp)
    sys.modules[name]=module
    sp.loader.exec_module(module)
    return module


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address'];start,end=by[0x63],by[0x8C if addr!=0x0058AF60 else 0x89]
    true_next=min((p for p in set(by.values()) if p>start),default=None)
    n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=416 if addr==0x004F7130 else 417
    need(addr<=start<end<addr+boss['size'] and end==true_next
         and len(n)==109 and end-start==size
         and sum(x.size for x in n)==size and n[-1].mnemonic=='jmp',
         f'{addr:#x}: complete original native action0x63 109-instruction bounds/code drift')
    need(n[0].mnemonic=='movsx' and n[0].op_str.endswith('byte ptr [0x6714b4]')
         and n[1].mnemonic=='cmp' and n[1].op_str.endswith(', 3')
         and n[2].mnemonic=='jne' and n[2].op_str==f'0x{n[7].address:x}'
         and n[6].mnemonic=='jne' and n[6].op_str==f'0x{n[27].address:x}'
         and n[26].mnemonic=='jmp' and n[26].op_str==f'0x{n[98].address:x}'
         and n[45].mnemonic=='jne' and n[45].op_str==f'0x{n[50].address:x}'
         and n[22].mnemonic=='call' and n[22].op_str=='0x40fac0'
         and n[44].mnemonic=='cmp' and n[44].op_str.endswith(', 2')
         and n[67].mnemonic=='cmp' and n[67].op_str.endswith(', 1')
         and n[90].mnemonic=='test' and n[91].mnemonic=='jne'
         and n[105].mnemonic=='push' and n[105].op_str=='2',
         f'{addr:#x}: original real mode3 short circuit or bonus-absent native CFG changed')
    for i,(target,mn,_) in FIELDS.items():
        x=n[i]
        need(x.mnemonic==mn and
             (x.op_str.endswith('byte ptr [0x6714b4]') if i==0
              else x.op_str==f'0x{target:x}'),
             f'{addr:#x}: genuine native typed mode/global target {target:#x} at {i} wrong')
    return n,{'native_original_code_handler':f'0x{start:08X}',
              'native_original_next_code_handler':f'0x{end:08X}',
              'native_whole_inner_CODE_bytes':size,
              'native_complete_x86_instructions':109,
              'real_original_typed_fields':len(FIELDS),
              'native_bonus_state_0x370_path_present':False,
              'original_entire_fighter_exact':False}


def build_source(addr,boss,report,mapped,reader,pe,decoder,
          f598,f567,f600,f602,f603,f605,f606,f607,f608,
          f610,f611,f613,f614):
    by={x['action']:int(x['handler'],16) for x in mapped}
    old,meta=f614.native_case(reader,pe,decoder,boss,by)
    source=f614.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
               f598,f567,f600,f602,f603,f605,f606,f607,f608,
               f610,f611,f613,meta)
    anchor='        case 0x63: g_FighterProbeMarker = 100; break;'
    need(source.count(anchor)==1,f'{addr:#x}: natural second-switch 0x63 placeholder missing')
    decl='extern float g_ThresholdAt0065782C;'
    need(source.count(decl)==1,f'{addr:#x}: original owner global declarations lost')
    return source.replace(decl,'extern signed char g_ModeAt006714B4;\n'+decl).replace(
           anchor,'#include "FighterMode63BasicF626.inc"')


def verify_source(reader,pe,decoder,boss,report,mapped,code,refs,
                  native,info,negative,f598,f600,f602,f603,f605,f606,
                  f607,f608,f610,f611,f613,f614,core,zero,switch):
    addr=boss['address'];instr=[]
    for x in decoder.disasm(code,0):
        instr.append(x)
        if x.mnemonic=='ret':break
    need(instr and instr[-1].mnemonic=='ret',f'{addr:#x}: whole original source RET missing')
    ret=instr[-1].address+instr[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original entire after-RET switch DATA physical size changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    prev,previnfo=f614.native_case(reader,pe,decoder,boss,by)
    f614.compare_candidate(reader,pe,decoder,f598,f600,f602,f603,
                f605,f606,f607,f608,f610,f611,f613,core,zero,switch,
                boss,report,mapped,code,refs,prev,previnfo)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    expected_slot=24 if addr==0x0058AF60 else 25
    need(sparse[0x63-0x33]==expected_slot and len(sparse)==49
         and table['slots']==expected_slot+2,
         f'{addr:#x}: original packed 0x63 native sparse lookup changed')
    native_ptr=int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+expected_slot*4,4),'little')
    need(native_ptr==by[0x63],f'{addr:#x}: original dense slot25 handler changed')
    typed_label=[r for r in refs if r['offset']==ret+44+expected_slot*4]
    need(len(typed_label)==1 and typed_label[0]['type']=='DIR32'
         and typed_label[0]['addend']==0 and typed_label[0]['local_symbol_offset'] is not None,
         f'{addr:#x}: generated C++ lacks original last real dense 0x63 source label')
    start=typed_label[0]['local_symbol_offset']
    # The next real native action may be 0x89 or 0x8C; it is NOT the
    # packed table's shared default slot26. Locate the next actual
    # source case marker with a genuine COFF relocation, and verify
    # its source literal against the independent original PE bound.
    next_action=0x89 if addr==0x0058AF60 else 0x8C
    next_address=by[next_action]
    need(int(info['native_original_next_code_handler'],16)==next_address,
         f'{addr:#x}: original next actual native action differs')
    markers=[r for r in refs if r['offset']>start and 'g_FighterProbeMarker' in r['symbol']]
    need(markers,f'{addr:#x}: actual following case marker COFF field missing')
    first=min(r['offset'] for r in markers)
    following=next((x for x in instr if x.address<=first<x.address+x.size),None)
    need(following is not None and following.mnemonic=='mov'
         and following.op_str.endswith(', '+hex(next_action+1)),
         f'{addr:#x}: first following source case not genuine next original code label')
    end=following.address
    candidate=list(decoder.disasm(code[start:end],start))
    need(len(candidate)==109 and end-start==417
         and sum(x.size for x in candidate)==417,
         f'{addr:#x}: not true entire source 109-instruction action0x63')
    width=[x.size-y.size for x,y in zip(native,candidate)]
    if not negative:need(all(x==0 for x in width),f'{addr:#x}: native original 109-x86 physical sizes differ')
    else:need(sum(1 for x in width if x)!=0,
              f'{addr:#x}: original negative actor unexpectedly became width-exact')
    ref_fields=[r for r in refs if start<=r['offset']<end]
    need(len(ref_fields)==7,
         f'{addr:#x}: original case0x63 has 7 physical typed PE/COFF fields')
    for i,(dest,mn,symbol) in FIELDS.items():
        original,compiled=native[i],candidate[i]
        need(original.mnemonic==compiled.mnemonic==mn,
             f'{addr:#x}: native original typed x86 ordinal {i} shifted')
        target=[r for r in ref_fields if compiled.address<=r['offset']<compiled.address+compiled.size]
        need(len(target)==1 and target[0]['type']==('DIR32' if i==0 else 'REL32')
             and target[0]['addend']==0 and target[0]['local_symbol_offset'] is None
             and symbol in target[0]['symbol'],
             f'{addr:#x}: real native PE COFF typed global/call {dest:#x} differs at {i}: {target}')
    original_gram,compiled_gram=f598.normalized(native),f598.normalized(candidate)
    original_gram[0]=compiled_gram[0]=('movsx','NATIVE_TYPED_GLOBAL_006714B4')
    differences=[(i,a,b) for i,(a,b) in enumerate(zip(original_gram,compiled_gram)) if a!=b]
    need(len(differences)==(67 if negative else 0),
         f'{addr:#x}: actual 0x63 register-phase mismatch count {len(differences)}, '
         f'expected {(67 if negative else 0)}: {differences[:6]}')
    return {'original_entire_giant':f'0x{addr:08X}',
            'original_whole_giant_CODE_still_NONEXACT':boss['size'],
            'real_original_afterRET_jump_DATA_owned_separately':boss['postret_size'],
            'all_30_prior_original_native_action_bodies_verified_in_same_OBJ':True,
            'original_complete_action0x63':info,
            'native_original_x86_roles':109,
            'original_pe_typed_COFF_fields':7,
            'original_native_GPR_CFG_roles_not_matched':len(differences),
            'new_source_matched_native_inner_CODE_uncredited':0 if negative else 417,
            'new_accepted_exact_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original 109-x86 strict actor; default five affected giant sources')
    parser.add_argument('--negative-actor',choices=['0x004F7130','0x0058AF60'],
                        help='one actual 67 native GPR mismatches actor after typed global; never counted as exact')
    opts=parser.parse_args()
    need(not(opts.boss and opts.negative_actor),'choose one source verification mode')
    negative=bool(opts.negative_actor)
    selected=[int(opts.negative_actor,0)] if negative else ([int(opts.boss,0)] if opts.boss else list(GOOD))
    need(all(a in (NEG if negative else GOOD) for a in selected),
         'selected original fighter owns different 109/118/138 source grammar')
    s=SOURCE.read_text()
    need(s.count('case 0x63:')==1 and 'g_ModeAt006714B4 != 3' in s
         and s.count('SetNativeActionAt40FAC0(0x31C)')==2
         and 'F624_BONUS_' not in s and 'RAW+0x370' not in s
         and s.count('RAW+0x2CD')==1,
         'basic original 109-instruction source no-bonus CFG changed')
    f602=load('f626_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f626_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f626_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f626_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f626_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f626_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f606=load('f626_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f626_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f608=load('f626_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f626_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f611=load('f626_f611',ROOT/'scripts/verify-fighter-trajectory-bounce-spawn-f611.py')
    f613=load('f626_f613',ROOT/'scripts/verify-fighter-trajectory-recovery-f613.py')
    f614=load('f626_f614',ROOT/'scripts/verify-fighter-trajectory-burst-f614.py')
    reader=load('f626_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f626_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f626_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f626_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f626_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=bosses[addr];report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        original,info=original_case(reader,pe,decoder,boss,by)
        cpp=OUT/f'Boss{addr:08X}-31-native-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-31-native-game-actions.obj'
        cpp.write_text(build_source(addr,boss,report,mapped,reader,pe,decoder,
              f598,f567,f600,f602,f603,f605,f606,f607,f608,
              f610,f611,f613,f614))
        p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,
             f'{addr:#x}: real VC7.1 original giant source did not compile: {p.stderr[-450:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        rec=verify_source(reader,pe,decoder,boss,report,mapped,code,refs,
                 original,info,negative,f598,f600,f602,f603,f605,f606,
                 f607,f608,f610,f611,f613,f614,core,zero,switch)
        rows.append(rec)
        print(f'F626 {addr:#010x}: entire original case0x63 109/109 x86; '
              f'{info["native_whole_inner_CODE_bytes"]} original inner CODE bytes, '
              '7 physically typed PE/COFF call/global fields; '
              f'{rec["original_native_GPR_CFG_roles_not_matched"]} native register mismatches; '
              '30 prior strict game cases, whole original afterRET DATA preserved; '
              'entire giant NONEXACT',flush=True)
    name='summary-negative.json' if negative else ('summary.json' if not opts.boss else f'summary-{selected[0]:08X}.json')
    (OUT/name).write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F626 {len(rows)} selected giant full-source C++ TUs, '
          f'{sum(x["new_source_matched_native_inner_CODE_uncredited"] for x in rows)} '
          'original native source-backed inner CODE bytes UNcredited. '
          'No entire giant exact or all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F626 original TH075 109-x86 mode63 source verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
