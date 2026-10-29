#!/usr/bin/env python3
"""F610: full 119-x86 native action0x4A in nine non-spawn giant fighters.

Each selected original giant is freshly compiled under pinned VC7.1.
Verify the real physical sparse+packed native 0x4A/0x4C bounds, complete
119-instruction GPR/x87/CFG and byte geometry, 19 typed PE-targeted
COFF fields, all 27 prior action source bodies and afterRET jump DATA.
No truncated case credited as an independent or whole exact function.
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
INC=ROOT/'probes/FighterTrajectoryBounce4AF610.inc'
OUT=ROOT/'.analysis/f610-fighter-bounce-source'
SPECIAL={0x006590C0:'g_BounceThresholdAt006590C0',0x00657F74:'g_BounceScaleAt00657F74',0x00454EE0:'ContactAt454EE0'}
TARGETS_BEFORE={
 27:(0x00657480,'fcomp'),33:(0x0040FB40,'call'),
 36:(0x00454EE0,'call'),42:(0x006590C0,'fcomp'),
 48:(0x0040FAC0,'call'),52:(0x00657F74,'fmul'),
 61:(0x00453E60,'call'),64:(0x00453D60,'call'),
 78:(0x0065782C,'fcomp'),84:(0x00453D60,'call'),
 87:(0x00657888,'fmul'),88:(0x006406AC,'call'),
 93:(0x00657888,'fmul'),94:(0x006406AC,'call'),
 98:(0x00453E20,'call'),103:(0x0040FAC0,'call'),
 106:(0x00453E60,'call'),109:(0x0040FA30,'call'),
 117:(0x0040FB40,'call')}
TARGETS_AFTER={
 27:(0x00657480,'fcomp'),33:(0x0040FB40,'call'),
 36:(0x00454EE0,'call'),42:(0x006590C0,'fcomp'),
 48:(0x0040FAC0,'call'),52:(0x00657F74,'fmul'),
 61:(0x00453E60,'call'),64:(0x00453D60,'call'),
 78:(0x0065782C,'fcomp'),84:(0x00657888,'fmul'),
 85:(0x006406AC,'call'),90:(0x00657888,'fmul'),
 91:(0x006406AC,'call'),95:(0x00453E20,'call'),
 100:(0x0040FAC0,'call'),103:(0x00453E60,'call'),
 106:(0x00453D60,'call'),109:(0x0040FA30,'call'),
 117:(0x0040FB40,'call')}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing PE verifier '+str(path))
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def field_offset(ins,index):
    x=ins[index]
    match=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], (?:0|ax)',x.op_str)
    need(x.mnemonic=='mov' and match is not None,
         f'original native case4A 16-bit member at ordinal {index} differs')
    return int(match.group(1),16)


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address'];start,end=by[0x4A],by[0x4C]
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=556 if addr==0x00564BE0 else 434
    need(addr<=start<end<addr+boss['size'] and end-start==size
         and len(native)==119 and sum(x.size for x in native)==size
         and native[-1].mnemonic=='jmp',
         f'{addr:#x}: original native entire 0x4A case boundary/x86/length differs')
    need(native[15].mnemonic=='mov' and native[15].op_str.endswith('+ 0x98]')
         and native[16].mnemonic=='mov' and 'dword ptr' in native[16].op_str
         and '+ 0x54]' in native[16].op_str
         and native[18].mnemonic=='mov' and native[18].op_str.endswith(', 0x3f4ccccd')
         and native[23].mnemonic=='cmp' and native[31].mnemonic=='push'
         and native[36].mnemonic=='call' and native[36].op_str=='0x454ee0'
         and native[46].mnemonic=='push' and native[46].op_str=='0x4c'
         and native[56].mnemonic=='mov' and native[56].op_str.endswith(', 0x41700000')
         and native[58].mnemonic=='mov' and native[58].op_str.endswith(', 0x3f000000')
         and native[59].mnemonic=='push' and native[59].op_str=='0x40000000'
         and native[65].mnemonic=='mov',
         f'{addr:#x}: native real 0x4A initialization, contact, bounce or member changed')
    stage=int(native[23].op_str.rsplit(', ',1)[-1],0)
    early=int(native[31].op_str,0)
    late=int(native[115].op_str,0)
    need((stage,early,late) in ((1,2,5),(1,2,6),(1,2,7),
              (2,3,5),(2,3,6),(2,3,8),(3,4,5),(3,4,7)),
         f'{addr:#x}: actual original actor-specific stage/aux values differ')
    prepare_before=native[82].mnemonic=='push'
    need((native[82].mnemonic,native[106].mnemonic)==(
         ('push','call') if prepare_before else ('mov','call')),
         f'{addr:#x}: genuine native 0x4A ground-contact PrepareCall ordering changed')
    fields=TARGETS_BEFORE if prepare_before else TARGETS_AFTER
    original_stores={65:field_offset(native,66),
                     (90 if prepare_before else 87):field_offset(native,90 if prepare_before else 87),
                     (96 if prepare_before else 93):field_offset(native,96 if prepare_before else 93)}
    counter=original_stores[65]
    need(counter in (0xF00,0xEFC)
         and original_stores[90 if prepare_before else 87]==counter
         and original_stores[96 if prepare_before else 93]==counter+2,
         f'{addr:#x}: real native bounce trajectory short fields disagree')
    for i,(target,mn) in fields.items():
        x=native[i]
        need(x.mnemonic==mn and x.op_str==(
             f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'),
             f'{addr:#x}: true original typed bounce x87 or game target changed at ordinal {i}')
    need(len(fields)==19,'genuine native 19 original physical typed fields incomplete')
    return native,{'original_native_case_start':f'0x{start:08X}',
                   'native_original_CODE_bytes':size,
                   'native_original_x86_instructions':119,
                   'native_stage':stage,'native_early_aux':early,'native_late_aux':late,
                   'original_pre_contact_prepare':prepare_before,
                   'native_counter_offset':counter,
                   'native_typed_COFF_targets':fields,
                   'whole_giant_exact':False}


def case_in_giant(reader,pe,decoder,f598,f602,f605,f607,f600,core,zero,
                  switch,boss,report,mapped,code,refs,native,info):
    addr=boss['address'];inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',f'{addr:#x}: whole C++ giant RET missing')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: complete original separately-owned afterRET switch DATA size changed')
    by={r['action']:int(r['handler'],16) for r in mapped}
    orig49,info49=f607.native_case(reader,pe,decoder,boss,by)
    f607.preserve_case(reader,pe,decoder,f598,f602,f605,f600,core,zero,switch,
                       boss,report,mapped,code,refs,orig49,info49)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(sparse[0x4a-0x33]==15 and sparse[0x4c-0x33]==16,
         f'{addr:#x}: original native 0x4A/0x4C physical sparse map changed')
    real_dense=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
                for i in (15,16)]
    need(real_dense==[by[0x4A],by[0x4C]],
         f'{addr:#x}: original native 0x4A/0x4C physical packed pointer targets differ')
    positions=[]
    for slot in (15,16):
        fields=[r for r in refs if r['offset']==ret+44+4*slot]
        need(len(fields)==1 and fields[0]['type']=='DIR32'
             and fields[0]['addend']==0 and fields[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: whole C++ original afterRET 0x4A case COFF label missing')
        positions.append(fields[0]['local_symbol_offset'])
    a,b=positions
    generated=list(decoder.disasm(code[a:b],a))
    need(len(native)==len(generated)==119 and b-a==434
         and sum(x.size for x in generated)==434,
         f'{addr:#x}: source not full original 119-x86 434B natural case 4A')
    wide=[x.size-y.size for x,y in zip(native,generated)]
    if addr==0x00564BE0:
        need(wide.count(3)==38 and wide.count(4)==2
             and wide.count(0)==79
             and [i for i,sz in enumerate(wide) if sz==4]==[39,81],
             f'{addr:#x}: 38 true native EBP-0x88 receiver and two widened branch positions differ')
    else:need(all(sz==0 for sz in wide),f'{addr:#x}: native compact case4A opcode widths changed')
    fields=[r for r in refs if a<=r['offset']<b]
    needed=info['native_typed_COFF_targets']
    need(len(fields)==len(needed)==19,f'{addr:#x}: native exact 19 physical COFF field count differs')
    symbols={**f602.ALL_SYMBOLS,**SPECIAL}
    for i,(target,mn) in needed.items():
        original,compiled=native[i],generated[i]
        need(original.mnemonic==compiled.mnemonic==mn,
             f'{addr:#x}: native game source COFF x86 instruction shifted at {i}')
        actual=[x for x in fields if compiled.address<=x['offset']<compiled.address+compiled.size]
        need(len(actual)==1 and actual[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and actual[0]['addend']==0 and actual[0]['local_symbol_offset'] is None
             and symbols[target] in actual[0]['symbol'],
             f'{addr:#x}: original PE target {target:#x} vs source COFF field at {i} differ: {actual}')
    shape_n,shape_c=f598.normalized(native),f598.normalized(generated)
    wrong=[(i,x,y) for i,(x,y) in enumerate(zip(shape_n,shape_c)) if x!=y]
    need(not wrong,f'{addr:#x}: actual complete 0x4A GPR/x87/CFG source operands differ: {wrong[:8]}')
    return {'original_whole_giant':f'0x{addr:08X}',
            'original_whole_giant_CODE_still_NONEXACT':boss['size'],
            'original_afterRET_DATA_separately_owned':boss['postret_size'],
            'prior_27_real_original_cases_retained':True,
            'native_original_stage_trajectory':info,
            'new_original_internal_CODE_bytes_uncredited':info['native_original_CODE_bytes'],
            'complete_new_original_x86_roles':119,
            'native_typed_COFF_fields_exact_positions_and_destinations':19,
            'accepted_new_whole_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one original regular 119-x86 fighter; default nine affected C++ TUs')
    opt=p.parse_args()
    f602=load('f610_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f610_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f610_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f610_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f610_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    f607=load('f610_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    reader=load('f610_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f610_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f610_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f610_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f610_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    registered={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    regular=[x for x in cohort if x not in (0x0045DD70,0x0058AF60)]
    selected=[int(opt.boss,0)] if opt.boss else regular
    need(len(regular)==9 and all(addr in regular for addr in selected),
         'original 165-instruction projectile-spawn variant cannot use 119-instruction case')
    src=INC.read_text()
    need(src.count('case 0x4A:')==1 and 'I32(0x54) = I32(0x98);' in src
         and src.count('ContactAt454EE0()')==1
         and src.count('I16(F610_COUNTER)')==2
         and 'POS = -POS * g_BounceScaleAt00657F74;' in src,
         'F610 original real bounce source/no fake ABI unexpectedly changed')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    results=[]
    for addr in selected:
        boss=registered[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        n,info=original_case(reader,pe,decoder,boss,by)
        orig46,info46=f602.original_case(reader,pe,decoder,boss,by)
        followups={i:f605.original_action(reader,pe,decoder,boss,by,i)[1]
                   for i in (0x47,0x48)}
        original49,meta49=f607.native_case(reader,pe,decoder,boss,by)
        src=f605.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                                    f602,f598,f567,info46,followups)
        marker='        case 0x49: g_FighterProbeMarker = 74; break;'
        need(src.count(marker)==1,f'{addr:#x}: missing source previous true action49')
        src=src.replace(marker,
                f'#define F607_COUNTER 0x{meta49["native_trajectory_short_offset"]:X}\n'
                '#include "FighterTrajectoryLanding49F607.inc"\n'
                '#undef F607_COUNTER')
        decl='extern float g_ContactProjectionAt00657888;'
        need(src.count(decl)==1,f'{addr:#x}: genuine original trajectory globals declaration changed')
        src=src.replace(decl,decl+'\nextern float g_BounceThresholdAt006590C0;'
                '\nextern float g_BounceScaleAt00657F74;')
        old='        case 0x4A: g_FighterProbeMarker = 75; break;'
        need(src.count(old)==1,f'{addr:#x}: next original second-switch case4A placeholder missing')
        pre=(f'#define F610_STAGE {info["native_stage"]}\n'
             f'#define F610_EARLY {info["native_early_aux"]}\n'
             f'#define F610_LATE {info["native_late_aux"]}\n'
             f'#define F610_COUNTER 0x{info["native_counter_offset"]:X}\n'
             f'#define F610_PREPARE_BEFORE {int(info["original_pre_contact_prepare"])}\n'
             '#include "FighterTrajectoryBounce4AF610.inc"\n'
             '#undef F610_STAGE\n#undef F610_EARLY\n#undef F610_LATE\n'
             '#undef F610_COUNTER\n#undef F610_PREPARE_BEFORE')
        src=src.replace(old,pre)
        cpp=OUT/f'Boss{addr:08X}-28-real-native-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-28-real-native-game-actions.obj'
        cpp.write_text(src)
        comp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              env=env,cwd=ROOT,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(comp.stdout+comp.stderr)
        need(comp.returncode==0,f'{addr:#x}: real native-profile VC7.1 giant source fails: {comp.stderr[-600:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        found=case_in_giant(reader,pe,decoder,f598,f602,f605,f607,f600,
                            core,zero,switch,boss,report,mapped,code,refs,n,info)
        results.append(found)
        print(f'F610 {addr:#010x}: 119/119 original x86 source roles, '
              f'{info["native_original_CODE_bytes"]} original internal CODE bytes, '
              '19/19 native typed PE/COFF fields; all 27 earlier cases and '
              'original afterRET jump DATA preserved. Whole giant NONEXACT',flush=True)
    receipt=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    receipt.write_text(json.dumps(results,indent=2)+'\n')
    print(f'F610 {len(results)} selected giant sources / {len(results)*119} authentic native '
          f'x86 roles / {sum(x["new_original_internal_CODE_bytes_uncredited"] for x in results)} '
          f'original uncredited interior CODE bytes / {len(results)*19} real PE/COFF refs; '
          'no new whole function exactness or all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F610 native TH075 fighter full action 4A verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
