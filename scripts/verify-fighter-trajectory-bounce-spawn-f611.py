#!/usr/bin/env python3
"""F611: full original 165-x86 action0x4A in the two spawn giant fighters.

Cold-build only the selected whole giant C++ source under pinned VC7.1.
Check all 21 actual typed PE/COFF targets, complete original 589B/165
x86 GPR/x87/CFG/widths, two real guarded projectile spawns, the prior
27 source cases and original afterRET separate jump DATA. No split CODE
or incomplete whole function is accepted as an exact authored function.
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
INC=ROOT/'probes/FighterTrajectoryBounceSpawn4AF611.inc'
OUT=ROOT/'.analysis/f611-fighter-bounce-source'
COHORT=(0x0045DD70,0x0058AF60)


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing PE or source verifier '+str(path))
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def field_offset(ins,i,kind):
    x=ins[i]
    match=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], (?:0|1|ax)',x.op_str)
    need(x.mnemonic=='mov' and match is not None,
         f'original 0x4A native {kind} 16-bit field at x86 ordinal {i} moved: {x.mnemonic} {x.op_str}')
    return int(match.group(1),16)


def native_case(reader,pe,decoder,boss,by,f610):
    addr=boss['address'];start,end=by[0x4A],by[0x4C]
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    need(addr<=start<end<addr+boss['size'] and end-start==589
         and len(native)==165 and sum(x.size for x in native)==589
         and native[-1].mnemonic=='jmp',
         f'{addr:#x}: genuine original special 0x4A native whole CASE x86/size boundary changed')
    need(native[9].mnemonic=='fld' and native[10].mnemonic=='fchs'
         and native[15].mnemonic=='mov' and native[15].op_str.endswith('+ 0x98]')
         and native[16].mnemonic=='mov' and 'dword ptr' in native[16].op_str
         and '+ 0x54]' in native[16].op_str
         and native[18].mnemonic=='mov' and native[18].op_str.endswith(', 0x3f4ccccd')
         and native[23].mnemonic=='cmp' and native[23].op_str.endswith(', 1')
         and native[25].mnemonic=='mov' and native[26].mnemonic=='movsx'
         and native[30].mnemonic=='movsx' and '+ 0xf0c]' in native[30].op_str
         and native[34].mnemonic=='mov' and native[34].op_str.endswith(', 1')
         and native[47].mnemonic=='call' and native[47].op_str=='0x453a70'
         and native[50].mnemonic=='cmp' and native[58].mnemonic=='push'
         and native[63].mnemonic=='call' and native[63].op_str=='0x454ee0'
         and native[69].mnemonic=='fcomp' and native[69].op_str=='dword ptr [0x6590c0]'
         and native[74].mnemonic=='movsx' and '+ 0xf0c]' in native[74].op_str
         and native[78].mnemonic=='mov' and native[78].op_str.endswith(', 1')
         and native[91].mnemonic=='call' and native[91].op_str=='0x453a70'
         and native[94].mnemonic=='call' and native[94].op_str=='0x40fac0'
         and native[102].mnemonic=='mov' and native[102].op_str.endswith(', 0x41700000')
         and native[104].mnemonic=='mov' and native[104].op_str.endswith(', 0x3f000000')
         and native[112].mnemonic=='mov' and native[112].op_str.endswith(', 0'),
         f'{addr:#x}: real original double one-shot native projectile and bounce-stage control changed')
    need(field_offset(native,34,'initial shot flag')==0xF0C
         and field_offset(native,78,'contact shot flag')==0xF0C
         and field_offset(native,112,'bounce trajectory reset')==0xF00
         and field_offset(native,133,'ground trajectory horizontal')==0xF00
         and field_offset(native,139,'ground trajectory vertical')==0xF02,
         f'{addr:#x}: original native two projectile flags/trajectory owner locations differ')
    kind=int(native[45].op_str,0)
    side=int(native[35].op_str,0)
    stage=int(native[50].op_str.rsplit(', ',1)[-1],0)
    early=int(native[58].op_str,0)
    late=int(native[161].op_str,0)
    need((kind,side,stage,early,late)==((0x3B7,1,1,2,5)
         if addr==0x0045DD70 else (0x3E7,0,2,3,5))
         and [native[i].op_str for i in (79,89)]==[
             str(side),f'0x{kind:x}'],
         f'{addr:#x}: second stage-one native spawn kind/side/late action mismatch')
    fields={i+(27 if i<46 else 46):val
            for i,val in f610.TARGETS_AFTER.items()}
    fields[47]=(0x00453A70,'call')
    fields[91]=(0x00453A70,'call')
    need(len(fields)==21,'genuine native original 21 typed COFF field map incomplete')
    for i,(target,mnemonic) in fields.items():
        x=native[i]
        need(x.mnemonic==mnemonic and x.op_str==(
             f'0x{target:x}' if mnemonic=='call' else f'dword ptr [0x{target:x}]'),
             f'{addr:#x}: original native PE actual typed game/CRT target at ordinal {i} differs')
    return native,{'original_native_case_start':f'0x{start:08X}',
                   'real_native_complete_CODE_bytes':589,
                   'native_x86_instruction_roles':165,
                   'native_real_projectile_kind':kind,'native_real_projectile_side':side,
                   'native_stage':stage,'native_early_aux':early,'native_late_aux':late,
                   'original_guarded_projectile_calls':2,
                   'original_trajectory_short_offset':0xF00,
                   'original_typed_COFF_fields':fields,
                   'whole_original_giant_exact':False}


def source_with_prior(addr,boss,report,mapped,reader,pe,decoder,
                      f602,f603,f606,f608,f598,f567,original46,info46,prior,info49):
    src=f606.source_for(addr,boss,report,mapped,reader,pe,decoder,
                        f602,f603,f598,f567,info46,prior)
    anchor='        case 0x49: g_FighterProbeMarker = 74; break;'
    need(src.count(anchor)==1,
         f'{addr:#x}: real previous 118-insn action0x49 placement unexpectedly changed')
    src=src.replace(anchor,
         f'#define F608_PROJECTILE 0x{info49["actual_projectile_kind"]:X}\n'
         f'#define F608_SIDE {info49["actual_projectile_side"]}\n'
         f'#define F608_COUNTER 0x{info49["native_original_trajectory_short_owner"]:X}\n'
         '#include "FighterTrajectoryLandingSpawnF608.inc"\n'
         '#undef F608_PROJECTILE\n#undef F608_SIDE\n#undef F608_COUNTER')
    return src


def check_case(reader,pe,decoder,f598,f602,f603,f606,f608,f600,core,zero,
               switch,boss,report,mapped,code,refs,native,info):
    addr=boss['address'];instructions=[]
    for x in decoder.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    need(instructions and instructions[-1].mnemonic=='ret',
         f'{addr:#x}: new whole-giant source has no original frame RET')
    ret=instructions[-1].address+instructions[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original separately-owned afterRET jump DATA extent differs')
    by={x['action']:int(x['handler'],16) for x in mapped}
    native49,info49=f608.native_case(reader,pe,decoder,boss,by,
                                     load('f611_f607_inner',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py'))
    f608.check_candidate(reader,pe,decoder,f598,f602,f603,f606,f600,
                         core,zero,switch,boss,report,mapped,code,refs,native49,info49)
    second=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,second['map_addr'],second['map_length'])
    need(sparse[0x4A-0x33]==15 and sparse[0x4C-0x33]==16,
         f'{addr:#x}: native original packed sparse 4A/4C handler positions differ')
    actual_handlers=[int.from_bytes(reader.pe_bytes_at(pe,second['dense_addr']+i*4,4),'little')
                     for i in (15,16)]
    need(actual_handlers==[by[0x4A],by[0x4C]],
         f'{addr:#x}: actual original native packed afterRET 4A/4C destinations differ')
    bounds=[]
    for slot in (15,16):
        matches=[x for x in refs if x['offset']==ret+44+4*slot]
        need(len(matches)==1 and matches[0]['type']=='DIR32' and matches[0]['addend']==0
             and matches[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: natural C++ missing original physical 4A/4C case COFF pointer')
        bounds.append(matches[0]['local_symbol_offset'])
    a,b=bounds
    compiled=list(decoder.disasm(code[a:b],a))
    need(len(native)==len(compiled)==165 and b-a==589
         and sum(x.size for x in compiled)==589
         and all(x.size==y.size for x,y in zip(native,compiled)),
         f'{addr:#x}: candidate special 4A not whole original 165-x86/589-byte geometry')
    fields=[x for x in refs if a<=x['offset']<b]
    targets=info['original_typed_COFF_fields']
    need(len(fields)==len(targets)==21,
         f'{addr:#x}: native 21 authentic PE and source COFF physical fields differ')
    symbols={**f602.ALL_SYMBOLS,
             0x006590C0:'g_BounceThresholdAt006590C0',
             0x00657F74:'g_BounceScaleAt00657F74',
             0x00454EE0:'ContactAt454EE0',
             0x00453A70:'SpawnDirectedAt453A70'}
    for i,(target,mn) in targets.items():
        source_inst=compiled[i]
        need(native[i].mnemonic==source_inst.mnemonic==mn,
             f'{addr:#x}: actual original typed COFF x86 mnemonic shifted at {i}')
        physical=[x for x in fields if source_inst.address<=x['offset']<source_inst.address+source_inst.size]
        need(len(physical)==1 and physical[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and physical[0]['addend']==0 and physical[0]['local_symbol_offset'] is None
             and symbols[target] in physical[0]['symbol'],
             f'{addr:#x}: actual native PE target {target:#x} and source symbol differ at {i}: {physical}')
    original_roles,generated_roles=f598.normalized(native),f598.normalized(compiled)
    bad=[(i,x,y) for i,(x,y) in enumerate(zip(original_roles,generated_roles)) if x!=y]
    need(not bad,
         f'{addr:#x}: real native whole 165-x86 GPR/x87/CFG role mismatch: {bad[:8]}')
    return {'whole_original_fighter':f'0x{addr:08X}',
            'whole_original_CODE_NONEXACT':boss['size'],
            'original_afterRET_jump_DATA_separate_bytes':boss['postret_size'],
            'previous_27_original_game_cases_preserved_on_same_OBJ':True,
            'original_native_case_0x4A':info,
            'original_internal_CODE_bytes_uncredited':589,
            'native_original_x86_roles':165,
            'real_original_typed_COFF_fields':21,
            'new_accepted_exact_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one special giant with real 165-x86 original action0x4A')
    opt=parser.parse_args()
    selected=[int(opt.boss,0)] if opt.boss else list(COHORT)
    need(all(addr in COHORT for addr in selected),
         'selected original fighter does not own 165-insn double-spawn action 0x4A')
    src=INC.read_text()
    need(src.count('case 0x4A:')==1 and src.count('SpawnDirectedAt453A70(')==2
         and src.count('I16(0xF0C)==0')==2
         and 'I32(0x54) = I32(0x98);' in src,
         'real original guarded double-spawn C++ source or raw movement lost')
    f602=load('f611_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f611_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f606=load('f611_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f608=load('f611_f608',ROOT/'scripts/verify-fighter-trajectory-landing-spawn-f608.py')
    f610=load('f611_f610',ROOT/'scripts/verify-fighter-trajectory-bounce-f610.py')
    f600=load('f611_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f611_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f611_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    reader=load('f611_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f611_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f611_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f611_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f611_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    registered={r['address']:r for r in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=registered[addr];report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native,info=native_case(reader,pe,decoder,boss,by,f610)
        orig46,info46=f603.real_case(reader,pe,decoder,boss,by,f602)
        old={action:f606.read_native_case(reader,pe,decoder,boss,by,action,
                  load('f611_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py'))
             for action in (0x47,0x48)}
        orig49,info49=f608.native_case(reader,pe,decoder,boss,by,
                                      load('f611_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py'))
        text=source_with_prior(addr,boss,report,mapped,reader,pe,decoder,
                               f602,f603,f606,f608,f598,f567,orig46,info46,old,info49)
        global_decl='extern float g_ContactProjectionAt00657888;'
        need(text.count(global_decl)==1,
             f'{addr:#x}: missing true bounce scalar float declaration context')
        text=text.replace(global_decl,global_decl+'\nextern float g_BounceThresholdAt006590C0;'
                          '\nextern float g_BounceScaleAt00657F74;')
        placeholder='        case 0x4A: g_FighterProbeMarker = 75; break;'
        need(text.count(placeholder)==1,f'{addr:#x}: actual original next indexed C++ case4A absent')
        pre=(f'#define F611_PROJECTILE 0x{info["native_real_projectile_kind"]:X}\n'
             f'#define F611_SIDE {info["native_real_projectile_side"]}\n'
             f'#define F610_STAGE {info["native_stage"]}\n'
             f'#define F610_EARLY {info["native_early_aux"]}\n'
             f'#define F610_LATE {info["native_late_aux"]}\n'
             '#define F610_COUNTER 0xF00\n'
             '#define F610_PREPARE_BEFORE 0\n'
             '#include "FighterTrajectoryBounceSpawn4AF611.inc"\n'
             '#undef F611_PROJECTILE\n#undef F611_SIDE\n'
             '#undef F610_STAGE\n#undef F610_EARLY\n#undef F610_LATE\n'
             '#undef F610_COUNTER\n#undef F610_PREPARE_BEFORE')
        cpp=OUT/f'Boss{addr:08X}-28-real-native-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-28-real-native-game-actions.obj'
        cpp.write_text(text.replace(placeholder,pre))
        comp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(comp.stdout+comp.stderr)
        need(comp.returncode==0,f'{addr:#x}: original VC7.1 natural giant source compile failed: {comp.stderr[-600:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        found=check_case(reader,pe,decoder,f598,f602,f603,f606,f608,f600,
                         core,zero,switch,boss,report,mapped,code,refs,native,info)
        rows.append(found)
        print(f'F611 {addr:#010x}: 165/165 native x86 roles, 589 original interior '
              f'CODE bytes, 21/21 native typed PE/COFF targets; two actual guarded '
              f'projectile spawns {info["native_real_projectile_kind"]:#x}, '
              'previous 27 native cases and full original afterRET jump DATA preserved; '
              'whole giant NONEXACT',flush=True)
    receipt=OUT/('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json')
    receipt.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F611 {len(rows)} special source TUs / {len(rows)*165} native x86 roles '
          f'/ {len(rows)*589} original uncredited interior CODE bytes '
          f'/ {len(rows)*21} typed PE/COFF fields, ZERO whole exact native game '
          'functions or all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F611 original Japanese TH075 double-spawn bounce proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
