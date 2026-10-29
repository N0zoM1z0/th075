#!/usr/bin/env python3
"""F606: complete original 0x47/0x48 trajectories in two special giants.

Freshly compile only either selected original fighter's whole C++ source,
retaining its real 131-instruction action0x46, prior 23 native source
cases, both complete native 0x47/0x48 variants and all after-RET switch
DATA. Validate all typed physical PE/COFF fields; never award a split
case or still-nonexact enclosing giant as a whole exact function.
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
OUT=ROOT/'.analysis/f606-trajectory-spawn-source'
SPAWN_BEFORE=ROOT/'probes/FighterTrajectoryFollowupSpawnF606.inc'
SPAWN_AFTER=ROOT/'probes/FighterTrajectoryFollowupLateSpawnF606.inc'
SIMPLE=ROOT/'probes/FighterTrajectoryFollowupsF605.inc'
BOSSES=(0x0045DD70,0x0058AF60)
ACTIONS=(0x47,0x48)


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    s=importlib.util.spec_from_file_location(name,path)
    need(s is not None and s.loader is not None, 'missing original PE verifier: '+str(path))
    mod=importlib.util.module_from_spec(s)
    sys.modules[name]=mod
    s.loader.exec_module(mod)
    return mod


def word_field(ins,ordinal):
    x=ins[ordinal]
    m=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], (?:1|ax)',x.op_str)
    need(x.mnemonic=='mov' and m is not None,
         f'original native signed-short/flag store at ordinal {ordinal} differs: {x.mnemonic} {x.op_str}')
    return int(m.group(1),16)


def read_native_case(reader,pe,decoder,boss,by,action,f605):
    address=boss['address'];start,end=by[action],by[action+1]
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    normal=(address==0x0045DD70 and action==0x48)
    # Actual original 0x0058AF60 action0x48 has stage-one spawn AFTER
    # the early stage check; every other spawn action puts it BEFORE.
    after=(address==0x0058AF60 and action==0x48)
    count=86 if normal else 113
    size=310 if normal else 395
    need(boss['address']<=start<end<boss['address']+boss['size']
         and end-start==size and len(native)==count
         and sum(x.size for x in native)==size
         and native[-1].mnemonic=='jmp',
         f'{address:#x}: original {action:#x} whole native original case boundary/code differs')
    need(native[9].mnemonic=='fld' and native[10].mnemonic=='fchs'
         and native[15].mnemonic=='mov' and native[15].op_str.endswith('+ 0x98]')
         and native[16].mnemonic=='mov' and '+ 0x54]' in native[16].op_str
         and 'dword ptr' in native[16].op_str
         and native[18].mnemonic=='mov'
         and native[18].op_str.endswith(', '+('0x3f4ccccd' if action==0x47 else '0x3fa66666')),
         f'{address:#x}: original 32-bit MOV trajectory initialization or 0.8/1.3f drag changed')
    delta=(27 if not(normal or after) else 0)
    stage=int(native[23+delta].op_str.rsplit(', ',1)[-1],0)
    early=int(native[31+delta].op_str,0)
    late=int(native[82+(27 if not normal else 0)].op_str,0)
    expected=(1,2,5) if address==0x0045DD70 else (2,3,5)
    need((stage,early,late)==expected
         and native[23+delta].mnemonic=='cmp'
         and native[31+delta].mnemonic=='push'
         and native[82+(27 if not normal else 0)].mnemonic=='push',
         f'{address:#x}: actual original staged movement action policy differs')
    field_offset=54+(27 if not normal else 0)
    need(word_field(native,field_offset)==0xF00
         and word_field(native,field_offset+6)==0xF02,
         f'{address:#x}: true original two adjacent signed-short trajectory members differ')
    spawn=None
    if not normal:
        # Real original register/ABI source places the spawn in different
        # lexical control-flow order in the unique late-spawn variant.
        flag_set=48 if after else 34
        projectile_index=59 if after else 45
        side_index=49 if after else 35
        call_index=61 if after else 47
        start_guard=35 if after else 21
        need(native[start_guard].mnemonic=='mov'
             and native[start_guard+2].mnemonic=='cmp'
             and native[start_guard+2].op_str.endswith(', 1')
             and word_field(native,flag_set)==0xF0C
             and native[call_index].mnemonic=='call'
             and native[call_index].op_str=='0x453a70',
             f'{address:#x}: original stage-one sprite spawn guarding/order changed')
        projectile=int(native[projectile_index].op_str,0)
        side=int(native[side_index].op_str,0)
        need((projectile,side)==((0x3B7,1) if address==0x0045DD70 else (0x3E7,0)),
             f'{address:#x}: actual original projectile identifier/side changed')
        spawn={'original_projectile_kind':projectile,'original_spawn_side':side,
               'original_flag_offset':0xF0C,'spawn_x86_ordinal':call_index,
               'spawn_order':'after-early-transition' if after else 'before-early-transition'}
    # Independently establish all actual native field targets and positions
    # from the complete original PE, with known x87/call roles and true
    # per-original spawn insertion location (never assume the positions are
    # those of a shorter original case).
    typed=dict(f605.NATIVE_FIELDS)
    if not normal:
        typed={i+(27 if (not after or i>=45) else 0):(target,mnemonic)
               for i,(target,mnemonic) in typed.items()}
        typed[61 if after else 47]=(0x00453A70,'call')
    for i,(target,mnemonic) in typed.items():
        item=native[i]
        need(item.mnemonic==mnemonic,
             f'{address:#x} action{action:x}: original PE physical typed reference moved at {i}')
        if mnemonic=='call':
            need(item.op_str==f'0x{target:x}',
                 f'{address:#x}: original game/CRT callee target incorrect at {i}')
        else:
            need(item.op_str==f'dword ptr [0x{target:x}]',
                 f'{address:#x}: native x87 true game global incorrect at {i}')
    need(len(typed)==(13 if normal else 14),
         f'{address:#x}: lost authentic typed original physical COFF field')
    return native,{'action':f'0x{action:X}',
                   'original_handler':f'0x{start:08X}',
                   'original_native_CODE_bytes':size,
                   'original_x86_instructions':count,
                   'native_stage':stage,'native_early':early,'native_late':late,
                   'original_trajectory_member_offset':0xF00,
                   'native_projectile_spawn':spawn,
                   'native_typed_field_ordinal_targets':typed,
                   'new_independent_exact_function':False}


def source_for(address,boss,report,mapped,reader,pe,decoder,
               f602,f603,f598,f567,info46,cases):
    src=f603.source_for(address,boss,report,mapped,reader,pe,decoder,
                        f602,f598,f567,info46)
    a='        case 0x47: g_FighterProbeMarker = 72; break;'
    b='        case 0x49: g_FighterProbeMarker = 74; break;'
    need(src.count(a)==src.count(b)==1,
         f'{address:#x}: actual original next action placeholder missing')
    original_simple=SIMPLE.read_text()
    need(original_simple.count('case 0x48: {')==1,
         'missing actual 86-instruction natural C++ case0x48 source')
    pieces=[]
    for action in ACTIONS:
        info=cases[action][1]
        spawn=info['native_projectile_spawn']
        if spawn is not None:
            spec={
              'F606_ACTION':f'0x{action:X}',
              'F606_DRAG':'0.8f' if action==0x47 else '1.3f',
              'F606_STAGE':str(info['native_stage']),
              'F606_EARLY':str(info['native_early']),
              'F606_LATE':str(info['native_late']),
              'F606_PROJECTILE':f'0x{spawn["original_projectile_kind"]:X}',
              'F606_SIDE':str(spawn['original_spawn_side']),
              'F606_COUNTER':f'0x{info["original_trajectory_member_offset"]:X}',
            }
            pieces.extend('#define '+k+' '+v for k,v in spec.items())
            pieces.append('#include "'+(
                SPAWN_AFTER.name if spawn['spawn_order']=='after-early-transition'
                else SPAWN_BEFORE.name)+'"')
            pieces.extend('#undef '+k for k in spec)
        else:
            need(action==0x48,'unexpected simple case0x47 among native special fighters')
            names={'F605_STAGE48':str(info['native_stage']),
                   'F605_EARLY48':str(info['native_early']),
                   'F605_LATE48':str(info['native_late']),
                   'F605_COUNTER':f'0x{info["original_trajectory_member_offset"]:X}'}
            pieces.extend('#define '+k+' '+v for k,v in names.items())
            pieces.append(original_simple[original_simple.index('case 0x48: {'):])
            pieces.extend('#undef '+k for k in names)
    begin,end=src.index(a),src.index(b)
    return src[:begin]+'\n'.join(pieces)+'\n'+src[end:]


def original_source_check(reader,pe,decoder,f600,f598,f603,f602,core,zero,
                          switch,boss,report,mapped,code,refs,original46,meta46,cases):
    address=boss['address'];inst=[]
    for item in decoder.disasm(code,0):
        inst.append(item)
        if item.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',
         f'{address:#x}: source whole-fighter RET no longer present')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{address:#x}: original full afterRET switch DATA geometry differs')
    # Full original prior 23 case roles + complete original action0x46.
    f600.compare_candidate(reader,pe,decoder,f598,core,zero,switch,
                           boss,report,mapped,code,refs)
    f603.compare_new_action(reader,pe,decoder,f598,f602,original46,
                            code,refs,boss,meta46)
    table=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need([sparse[action-0x33] for action in ACTIONS]==[12,13],
         f'{address:#x}: original complete compressed sparse index map changed')
    symbols={**f602.ALL_SYMBOLS,0x00453A70:'SpawnDirectedAt453A70'}
    rows=[]
    for action in ACTIONS:
        native,info=cases[action]
        n0=int(info['original_handler'],16);n1=n0+info['original_native_CODE_bytes']
        ordinal=12 if action==0x47 else 13
        dense=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
               for i in (ordinal,ordinal+1)]
        need(dense==[n0,n1],
             f'{address:#x}: original 0x{action:x} physical next indexed handlers differ')
        pos=[]
        for i in (ordinal,ordinal+1):
            fields=[r for r in refs if r['offset']==ret+44+4*i]
            need(len(fields)==1 and fields[0]['type']=='DIR32' and fields[0]['addend']==0
                 and fields[0]['local_symbol_offset'] is not None,
                 f'{address:#x}: actual source dense afterRET case-slot COFF field missing')
            pos.append(fields[0]['local_symbol_offset'])
        c0,c1=pos
        generated=list(decoder.disasm(code[c0:c1],c0))
        need(c1-c0==info['original_native_CODE_bytes']
             and len(generated)==len(native)==info['original_x86_instructions']
             and sum(x.size for x in generated)==c1-c0,
             f'{address:#x}: genuine whole original 0x{action:x} x86 boundary mismatch')
        left,right=f598.normalized(native),f598.normalized(generated)
        diff=[(i,x,y) for i,(x,y) in enumerate(zip(left,right)) if x!=y]
        need(not diff and all(x.size==y.size for x,y in zip(native,generated)),
             f'{address:#x}: genuine original source GPR/x87/CFG widths/roles differ: {diff[:6]}')
        physical=[r for r in refs if c0<=r['offset']<c1]
        targets=info['native_typed_field_ordinal_targets']
        need(len(physical)==len(targets),
             f'{address:#x}: actual original native typed relocation count differs')
        for i,(dest,mnemonic) in targets.items():
            a,b=native[i],generated[i]
            need(a.mnemonic==b.mnemonic==mnemonic,
                 f'{address:#x}: original source native typed instruction {i} shifted')
            found=[r for r in physical if b.address<=r['offset']<b.address+b.size]
            need(len(found)==1 and found[0]['type']==('REL32' if mnemonic=='call' else 'DIR32')
                 and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
                 and symbols[dest] in found[0]['symbol'],
                 f'{address:#x}: original PE/COFF actual callee/global {dest:#x} identity/type differs: {found}')
        rows.append({'action':info['action'],
                     'whole_original_inner_CODE_uncredited':info['original_native_CODE_bytes'],
                     'native_original_x86_GPR_x87_CFG_roles':len(native),
                     'original_typed_physical_COFF_fields':len(physical),
                     'native_stage_one_projectile':info['native_projectile_spawn'],
                     'enclosing_giant_function_exact':False})
    return {'original_whole_giant':f'0x{address:08X}',
            'entire_original_whole_CODE_still_nonexact':boss['size'],
            'original_afterRET_DATA_separately_owned':boss['postret_size'],
            'earlier_24_real_source_cases_retained':True,
            'two_true_next_original_case_bodies':rows,
            'new_original_native_x86_roles':sum(x['native_original_x86_GPR_x87_CFG_roles'] for x in rows),
            'new_original_internal_CODE_bytes_uncredited':sum(x['whole_original_inner_CODE_uncredited'] for x in rows),
            'new_native_typed_COFF_fields':sum(x['original_typed_physical_COFF_fields'] for x in rows),
            'accepted_exact_whole_game_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one original 113-instruction special fighter, default 2 affected TUs')
    opts=p.parse_args()
    selected=[int(opts.boss,0)] if opts.boss else list(BOSSES)
    need(all(x in BOSSES for x in selected),'selected original does not have genuine special spawn policy')
    for path in (SPAWN_BEFORE,SPAWN_AFTER):
        text=path.read_text()
        need(text.count('case F606_ACTION:')==1
             and text.count('SpawnDirectedAt453A70(')==1
             and text.count('I32(0x54) = I32(0x98);')==1,
             'genuine original before/after stage-one projectile C++ source absent')
    f602=load('f606_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f603=load('f606_f603',ROOT/'scripts/verify-fighter-trajectory-spawn-f603.py')
    f600=load('f606_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f606_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f606_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f606_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    reader=load('f606_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f606_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f606_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f606_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f606_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={r['address']:r for r in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for address in selected:
        boss=bosses[address];report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={r['action']:int(r['handler'],16) for r in mapped}
        original46,info46=f603.real_case(reader,pe,decoder,boss,by,f602)
        originals={action:read_native_case(reader,pe,decoder,boss,by,action,f605)
                   for action in ACTIONS}
        cpp=OUT/f'Boss{address:08X}-26-real-original-game-cases.cpp'
        obj=OUT/f'Boss{address:08X}-26-real-original-game-cases.obj'
        cpp.write_text(source_for(address,boss,report,mapped,reader,pe,decoder,
                                  f602,f603,f598,f567,info46,originals))
        proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              env=env,cwd=ROOT,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{address:08X}-compile.log').write_text(proc.stdout+proc.stderr)
        need(proc.returncode==0,f'{address:#x}: genuine selected VC7.1 source failed: {proc.stderr[-600:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{address:08X}@@QAEXXZ')
        row=original_source_check(reader,pe,decoder,f600,f598,f603,f602,core,zero,
                                  switch,boss,report,mapped,code,refs,original46,info46,originals)
        rows.append(row)
        print(f'F606 {address:#010x}: genuine two native whole case0x47/0x48 actions '
              f'{row["new_original_native_x86_roles"]} x86 roles '
              f'{row["new_original_internal_CODE_bytes_uncredited"]} original inner CODE B '
              f'{row["new_native_typed_COFF_fields"]} physical typed PE/COFF destinations; '
              'previous 24 actions & afterRET switch preserved, whole giant NONEXACT',flush=True)
    out=OUT/('summary.json' if not opts.boss else f'summary-{selected[0]:08X}.json')
    out.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F606 {len(rows)}/2 special original fighter sources: '
          f'{sum(x["new_original_native_x86_roles"] for x in rows)} authentic x86 roles '
          f'{sum(x["new_original_internal_CODE_bytes_uncredited"] for x in rows)} native '
          f'internal uncredited CODE bytes, {sum(x["new_native_typed_COFF_fields"] for x in rows)} '
          'typed original COFF fields; 0 accepted whole exact game functions or all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F606 true original Japanese TH075 special fighter cases failed:',exc,file=sys.stderr)
        raise SystemExit(1)
