#!/usr/bin/env python3
"""F608: full original 118-instruction action0x49 in final two fighters.

Cold compile only chosen whole giant C++ TU with prior 26 original cases;
independently re-read actual native action 0x49, its 16 typed original
COFF fields, one-shot stage1 projectile, two x87 floating equality
checks and after-RET table. No inner case/full giant exact CODE credit.
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
INC=ROOT/'probes/FighterTrajectoryLandingSpawnF608.inc'
OUT=ROOT/'.analysis/f608-fighter-landing-source'
COHORT=(0x0045DD70,0x0058AF60)


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'missing pinned original reader '+str(path))
    module=importlib.util.module_from_spec(sp)
    sys.modules[name]=module
    sp.loader.exec_module(module)
    return module


def native_case(reader,pe,decoder,boss,by,f607):
    address=boss['address']
    start,end=by[0x49],by[0x4A]
    original=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    need(address<=start<end<address+boss['size']
         and end-start==420 and len(original)==118
         and sum(x.size for x in original)==420
         and original[-1].mnemonic=='jmp',
         f'{address:#x}: native original whole action49 size, complete boundary or roles differ')
    # Real original stage1/frame0 guard followed by one-shot short flag
    # and a genuine thiscall to spawn a projectile, before x87 tests.
    need(original[9].mnemonic=='fld' and original[10].mnemonic=='fchs'
         and original[15].mnemonic=='mov' and original[15].op_str.endswith('+ 0x98]')
         and original[16].mnemonic=='mov' and 'dword ptr' in original[16].op_str
         and '+ 0x54]' in original[16].op_str
         and original[18].mnemonic=='mov' and original[18].op_str.endswith(', 0x3f4ccccd')
         and original[70].mnemonic=='cmp' and original[70].op_str.endswith(', 1')
         and original[76].mnemonic=='mov' and original[77].mnemonic=='movsx'
         and '+ 0xf0c]' in original[77].op_str
         and original[78].mnemonic=='test' and original[79].mnemonic=='jne'
         and original[81].mnemonic=='mov' and '+ 0xf0c]' in original[81].op_str
         and original[81].op_str.endswith(', 1')
         and original[84].mnemonic=='mov' and 'byte ptr' in original[84].op_str
         and '+ 0x66]' in original[84].op_str
         and original[94].mnemonic=='call' and original[94].op_str=='0x453a70',
         f'{address:#x}: original 0x49 native stage1 shot / raw 32-bit movement ABI differs')
    kind=int(original[92].op_str,0)
    side=int(original[82].op_str,0)
    need((kind,side)==((0x3B7,1) if address==0x0045DD70 else (0x3E7,0)),
         f'{address:#x}: real original character-native projectile ID/direction differs')
    need([original[i].mnemonic for i in (98,105)]==['fucompp','fucompp']
         and [original[i].op_str for i in (100,107)]==['ah, 0x44','ah, 0x44']
         and original[101].mnemonic=='jnp' and original[108].mnemonic=='jp'
         and [original[i].op_str for i in (109,113)]==['3','2'],
         f'{address:#x}: actual original two x87 float equality branches changed')
    short_offsets=[]
    for i in (34,40):
        x=original[i]
        match=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], ax',x.op_str)
        need(x.mnemonic=='mov' and match is not None,
             f'{address:#x}: real native trajectory short store {i} differs')
        short_offsets.append(int(match.group(1),16))
    need(short_offsets==[0xF00,0xF02],
         f'{address:#x}: native stage-1 short trajectory owner changed')
    # Add exactly one real original spawn field; the first 11 original
    # fields stay at their old physical instruction ordinals, the last
    # two original FLD fields and two end calls shift 19 positions.
    typed={i+(19 if i>=77 else 0):t for i,t in f607.F607_FIELDS.items()}
    typed[94]=(0x00453A70,'call')
    need(len(typed)==16,f'{address:#x}: physical native 16-field table malformed')
    for i,(target,mn) in typed.items():
        x=original[i]
        need(x.mnemonic==mn and
             x.op_str==(f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'),
             f'{address:#x}: original PE typed field {i} real destination changed')
    return original,{'original_native_start':f'0x{start:08X}',
                     'original_complete_native_CASE_CODE_bytes':420,
                     'original_native_x86_instructions':118,
                     'actual_projectile_kind':kind,'actual_projectile_side':side,
                     'native_typed_fields':typed,
                     'native_original_trajectory_short_owner':0xF00,
                     'whole_giant_exact':False}


def check_candidate(reader,pe,decoder,f598,f602,f603,f606,f600,core,zero,switch,
                    boss,report,mapped,code,refs,original49,info):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: source whole giant RET missing')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: native complete afterRET jump table bytes lost')
    by={q['action']:int(q['handler'],16) for q in mapped}
    original46,info46=f603.real_case(reader,pe,decoder,boss,by,f602)
    earlier={action:f606.read_native_case(reader,pe,decoder,boss,by,action,
                                          load('f608_f605_inner',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py'))
             for action in (0x47,0x48)}
    # Repeat complete original 23-action x86/COFF + 131-instruction 0x46
    # and both native 86/113 action0x47/0x48 original tests against THIS
    # new COFF object; no stale object/proof substitute.
    f606.original_source_check(reader,pe,decoder,f600,f598,f603,f602,
                  core,zero,switch,boss,report,mapped,code,refs,original46,info46,earlier)
    table=boss['tables'][1]
    index=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(index[0x49-0x33]==14 and index[0x4A-0x33]==15,
         f'{addr:#x}: original sparse source action index 49/4A changed')
    native_ptrs=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
                 for i in (14,15)]
    need(native_ptrs==[by[0x49],by[0x4A]],
         f'{addr:#x}: original source physical native 49/4A CODE extents wrong')
    positions=[]
    for i in (14,15):
        data=[r for r in refs if r['offset']==ret+44+4*i]
        need(len(data)==1 and data[0]['type']=='DIR32' and data[0]['addend']==0
             and data[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: genuine native afterRET second-table case label {i} absent')
        positions.append(data[0]['local_symbol_offset'])
    c0,c1=positions
    generated=list(decoder.disasm(code[c0:c1],c0))
    need(c1-c0==420 and len(generated)==len(original49)==118
         and sum(x.size for x in generated)==420
         and all(x.size==y.size for x,y in zip(original49,generated)),
         f'{addr:#x}: original whole 118 x86/420 byte case49 source geometry mismatch')
    real_fields=[r for r in refs if c0<=r['offset']<c1]
    native_fields=info['native_typed_fields']
    need(len(real_fields)==len(native_fields)==16,
         f'{addr:#x}: original 16 genuine typed source COFF records missing')
    symbols={**f602.ALL_SYMBOLS,0x00453A70:'SpawnDirectedAt453A70'}
    for i,(target,mn) in native_fields.items():
        x,y=original49[i],generated[i]
        need(x.mnemonic==y.mnemonic==mn,
             f'{addr:#x}: real original typed x86 role {i} moved')
        physical=[r for r in real_fields if y.address<=r['offset']<y.address+y.size]
        need(len(physical)==1 and physical[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and physical[0]['addend']==0 and physical[0]['local_symbol_offset'] is None
             and symbols[target] in physical[0]['symbol'],
             f'{addr:#x}: original native typed PE target {target:#x} at {i} differs: {physical}')
    native_roles,source_roles=f598.normalized(original49),f598.normalized(generated)
    for index in (96,103):
        need(native_roles[index]==('fld','dword ptr [0x65782c]')
             and source_roles[index]==('fld','dword ptr [0]'),
             f'{addr:#x}: genuine PE-to-COFF source native fld float reference moved')
        # Match the exact physical typed original PE float global above,
        # so this is a proven relocation, not an ignored opcode error.
        native_roles[index]=source_roles[index]=('fld','NATIVE_TYPED_FLOAT_GLOBAL_0065782C')
    mismatch=[(i,x,y) for i,(x,y) in enumerate(zip(native_roles,source_roles)) if x!=y]
    need(not mismatch,
         f'{addr:#x}: actual native 118-instruction GPR/x87/CFG roles differ: {mismatch[:8]}')
    return {'whole_original_giant':f'0x{addr:08X}',
            'whole_original_CODE_still_nonexact':boss['size'],
            'source_prior_26_original_native_cases_retained':True,
            'original_afterRET_DATA_separately_owned':boss['postret_size'],
            'complete_new_original_case_0x49':info,
            'native_original_x86_roles':118,'native_original_interior_CODE_bytes_uncredited':420,
            'real_original_physical_COFF_fields':16,
            'accepted_new_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original special fighter giant, default two affected TUs')
    opts=parser.parse_args()
    selected=[int(opts.boss,0)] if opts.boss else list(COHORT)
    need(all(x in COHORT for x in selected),'selected original is not genuine 118-instruction landing owner')
    source=INC.read_text()
    need(source.count('case 0x49:')==1 and source.count('SpawnDirectedAt453A70(')==1
         and source.count('I16(0xF0C)')==2 and '*(&POS) == g_ThresholdAt0065782C' in source,
         'source no longer carries original genuine stage-one spawn or x87 source order')
    f602=load('f608_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f608_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f606=load('f608_f606',ROOT/'scripts/verify-fighter-trajectory-followup-spawns-f606.py')
    f607=load('f608_f607',ROOT/'scripts/verify-fighter-trajectory-landing-f607.py')
    f600=load('f608_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f608_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f608_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    reader=load('f608_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f608_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f608_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f608_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f608_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    originals={x['address']:x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    results=[]
    for addr in selected:
        boss=originals[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native46,info46=f603.real_case(reader,pe,decoder,boss,by,f602)
        old={action:f606.read_native_case(reader,pe,decoder,boss,by,action,
                load('f608_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py'))
             for action in (0x47,0x48)}
        real,info=native_case(reader,pe,decoder,boss,by,f607)
        base=f606.source_for(addr,boss,report,mapped,reader,pe,decoder,
                             f602,f603,f598,f567,info46,old)
        anchor='        case 0x49: g_FighterProbeMarker = 74; break;'
        need(base.count(anchor)==1,f'{addr:#x}: original next case49 switch placeholder moved')
        base=base.replace(anchor,
                f'#define F608_PROJECTILE 0x{info["actual_projectile_kind"]:X}\n'
                f'#define F608_SIDE {info["actual_projectile_side"]}\n'
                f'#define F608_COUNTER 0x{info["native_original_trajectory_short_owner"]:X}\n'
                '#include "FighterTrajectoryLandingSpawnF608.inc"\n'
                '#undef F608_PROJECTILE\n#undef F608_SIDE\n#undef F608_COUNTER')
        cpp=OUT/f'Boss{addr:08X}-27-real-native-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-27-real-native-actions.obj'
        cpp.write_text(base)
        p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              env=env,cwd=ROOT,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compile.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,f'{addr:#x}: real VC7.1 game source failed: {p.stderr[-600:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        rec=check_candidate(reader,pe,decoder,f598,f602,f603,f606,f600,core,zero,switch,
                            boss,report,mapped,code,refs,real,info)
        results.append(rec)
        print(f'F608 {addr:#010x}: genuine original 0x49 stage-one-spawn landing '
              f'118/118 x86 roles, 420 native inner CODE B, 16/16 actual original typed PE/COFF '
              f'fields; original projectile {info["actual_projectile_kind"]:#x} '
              f'side {info["actual_projectile_side"]}, previous 26 native game cases '
              'and after-RET tables preserved, whole giant NONEXACT',flush=True)
    out=OUT/('summary.json' if not opts.boss else f'summary-{selected[0]:08X}.json')
    out.write_text(json.dumps(results,indent=2)+'\n')
    print(f'F608 {len(results)} selected giant sources / {len(results)*118} original x86 roles '
          f'/ {len(results)*420} uncredited original internal CODE bytes / '
          f'{len(results)*16} original typed PE/COFF fields, no whole exact game CODE '
          'or all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F608 real original TH075 native fighter landing spawn failed:',exc,file=sys.stderr)
        raise SystemExit(1)
