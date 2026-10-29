#!/usr/bin/env python3
"""F628: original 8C/8F/90 native landing x87 cases in 11 fighter giants.

Eight fighter parents have all three cases strictly matching real native
80-x86 GPR/x87/CFG roles, 8 physical typed PE/COFF fields each; the
other three actors' full-size candidate source retains 51 register
mismatches per case. Build ONLY selected affected whole giant C++ TU,
check all 30 previous original native cases, all physical afterRET
DATA, and previously reconstructed 0x63 on seven positive owners.
Whole giants and case fragments remain unaccepted NONEXACT CODE.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
INC=ROOT/'probes/FighterJumpLandingF628.inc'
OUT=ROOT/'.analysis/f628-fighter-landings-source'
SPECIAL=(0x005AEEC0,0x00564BE0)
REGULAR=(0x004AC040,0x00486550,0x00543210,0x004D7E70,0x005214B0)
PRIORITY=(0x005D73C0,)
NEGATIVE=(0x0045DD70,0x0058AF60,0x004F7130)
POSITIVE=(*SPECIAL,*REGULAR,*PRIORITY)
ACTIONS=(0x8C,0x8F,0x90)
FIELDS={18:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
        24:(0x00658058,'fadd','g_JumpGroundCorrectionAt00658058'),
        29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
        36:(0x00454EE0,'call','ContactAt454EE0'),
        46:(0x006583E8,'fmul','g_JumpReflectionAt006583E8'),
        50:(0x0040FA30,'call','GetNativeActionAt40FA30'),
        58:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
        78:(0x0040FB40,'call','SetAuxActionAt40FB40')}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         'missing real original target/native source helper '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def native_case(reader,pe,decoder,boss,by,action):
    addr=boss['address']
    start=by[action]
    end=min((v for v in set(by.values()) if v>start),default=None)
    size=361 if addr==0x00564BE0 else 289
    need(end is not None and start<end<addr+boss['size'] and end-start==size,
         f'{addr:#x}: real native whole action{action:#x} boundary/size differs')
    native=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    count=len(native)
    counter=0xEFC if addr==0x005AEEC0 else 0xF00
    need(count==80 and sum(x.size for x in native)==size
         and native[-1].mnemonic=='jmp'
         and native[1].mnemonic=='movsx' and '+ 0x62]' in native[1].op_str
         and native[5].mnemonic=='movsx' and '+ 0x64]' in native[5].op_str
         and native[9].mnemonic=='mov' and native[9].op_str.endswith(
             ', 0xc1300000' if action==0x8C else ', 0xc1400000')
         and native[15].mnemonic=='mov' and f'+ 0x{counter:x}]' in native[15].op_str
         and native[15].op_str.endswith(', 0')
         and native[20].mnemonic=='test' and native[20].op_str=='ah, 5'
         and native[21].mnemonic=='jp' and native[21].op_str==f'0x{native[35].address:x}'
         and native[31].mnemonic=='test' and native[31].op_str=='ah, 0x41'
         and native[32].mnemonic=='jne' and native[32].op_str==f'0x{native[35].address:x}'
         and native[41].mnemonic=='movsx' and '+ 0x3be]' in native[41].op_str
         and native[46].mnemonic=='fmul' and native[46].op_str=='qword ptr [0x6583e8]'
         and native[48].mnemonic=='fstp' and '+ 0x490]' in native[48].op_str
         and native[56].mnemonic=='push' and native[56].op_str=='0'
         and native[61].mnemonic=='cmp' and native[61].op_str.endswith(', 3')
         and native[68].mnemonic=='movsx' and f'+ 0x{counter:x}]' in native[68].op_str
         and native[76].mnemonic=='push' and native[76].op_str=='1',
         f'{addr:#x}: native original x87 landing/feedback frame semantics changed')
    limit=int(native[69].op_str.rsplit(', ',1)[-1],0)
    need(native[69].mnemonic=='cmp' and limit in (5,7)
         and native[72].mnemonic=='mov' and f'+ 0x{counter:x}]' in native[72].op_str
         and native[75].mnemonic=='mov' and f'+ 0x{counter:x}]' in native[75].op_str,
         f'{addr:#x}: native original per-actor motion counter or stage limit changed')
    for i,(dest,mn,symbol) in FIELDS.items():
        x=native[i]
        want=f'0x{dest:x}' if mn=='call' else (
             f'qword ptr [0x{dest:x}]' if mn=='fmul' else f'dword ptr [0x{dest:x}]')
        need(x.mnemonic==mn and x.op_str==want,
             f'{addr:#x}: original PE native typed game/CRT float target {dest:#x} at ordinal{i} differs')
    return native,{'original_full_case_start':f'0x{start:08X}',
                   'original_full_case_end':f'0x{end:08X}',
                   'original_complete_case_CODE_bytes':size,
                   'original_x86_instructions':80,
                   'original_counter_offset':counter,
                   'original_start_float_bits':int(native[9].op_str.rsplit(', ',1)[-1],0),
                   'original_native_stage_counter_limit':limit,
                   'real_original_PE_COFF_fields':8,
                   'whole_enclosing_fighter_exact':False}


def source_with_landing(addr,boss,report,mapped,reader,pe,decoder,helpers,caseinfo):
    h=helpers
    names=('f598','f567','f600','f602','f603','f605','f606','f607','f608',
           'f610','f611','f613','f614')
    (f598,f567,f600,f602,f603,f605,f606,f607,f608,
     f610,f611,f613,f614)=(h[n] for n in names)
    by={x['action']:int(x['handler'],16) for x in mapped}
    if addr in SPECIAL:
        f622=h['f622'];f624=h['f624']
        old,info=f624.original_case(reader,pe,decoder,boss,by)
        source=f624.natural_source(addr,boss,report,mapped,reader,pe,decoder,
                 f598,f567,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,f614,f622,info)
    elif addr in REGULAR:
        f626=h['f626']
        source=f626.build_source(addr,boss,report,mapped,reader,pe,decoder,
                 f598,f567,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,f614)
    elif addr in PRIORITY:
        f627=h['f627_priority']
        source=f627.build_source(addr,boss,report,mapped,reader,pe,decoder,
                 f598,f567,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,f614)
    else:
        old,info=f614.native_case(reader,pe,decoder,boss,by)
        source=f614.reconstruct_source(addr,boss,report,mapped,reader,pe,decoder,
                 f598,f567,f600,f602,f603,f605,f606,f607,f608,
                 f610,f611,f613,info)
    decl='extern float g_ThresholdAt0065782C;'
    need(source.count(decl)==1,
         f'{addr:#x}: missing real original owner/global float declaration')
    source=source.replace(decl,decl+'\nextern float g_JumpGroundCorrectionAt00658058;'
               '\nextern double g_JumpReflectionAt006583E8;')
    for action in ACTIONS:
        info=caseinfo[action][1]
        bits=info['original_start_float_bits']
        value=struct.unpack('<f',struct.pack('<I',bits))[0]
        need(value in (-11.,-12.),
             f'{addr:#x}: original actual negative startup float differs')
        params={'F628_CASE':f'0x{action:X}',
                'F628_COUNTER':f'0x{info["original_counter_offset"]:X}',
                'F628_START_POS':repr(value)+'f',
                'F628_LIMIT':str(info['original_native_stage_counter_limit'])}
        placeholder=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(placeholder)==1,
             f'{addr:#x}: original source action{action:#x} independent case marker absent')
        insert='\n'.join('#define '+k+' '+v for k,v in params.items())
        insert+='\n#include "FighterJumpLandingF628.inc"\n'
        insert+='\n'.join('#undef '+k for k in params)
        source=source.replace(placeholder,insert)
    need(source.count('        case 0x91: g_FighterProbeMarker = 146; break;')==1,
         f'{addr:#x}: actual next complete game action0x91 source marker lost')
    return source


def verify_obj(reader,pe,decoder,boss,report,mapped,code,refs,caseinfo,helpers,negative,extra_followup_x86=0):
    addr=boss['address'];h=helpers
    f598,f614=(h[n] for n in ('f598','f614'))
    inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',f'{addr:#x}: no real giant source RET')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original entire afterRET packed jump DATA ownership changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    # Entire previous 30 actual original game-case grammar + all native
    # afterRET dense COFF and sparse literal bytes must be re-verified
    # in the SAME fresh 8C/8F/90 whole-parent source C++ object.
    o58,i58=f614.native_case(reader,pe,decoder,boss,by)
    f614.compare_candidate(reader,pe,decoder,h['f598'],h['f600'],
           h['f602'],h['f603'],h['f605'],h['f606'],h['f607'],h['f608'],
           h['f610'],h['f611'],h['f613'],h['core'],h['zero'],h['switch'],
           boss,report,mapped,code,refs,o58,i58)
    # For the F628 baseline, next original 0x91 is still a source
    # marker. Later F629/F630 can pass the REAL newly reconstructed
    # 78/105 native 0x91 x86 extent, bounded instead by the actual
    # next case0x96 marker. The prior three 80-x86 8C/8F/90 cases
    # must then be rechecked in the SAME newly compiled full giant.
    need(extra_followup_x86 in (0,78,105,151,153,178,180,370,378,397,405,
                                 516,528,543,555,582,596,609,623,
                                 801,815,828,842,1014,1028,1041,1055),
         f'{addr:#x}: only genuine 78/105-x86 action91 and 73/75-x86 action96 extensions permitted')
    next_marker_value=(0x92 if extra_followup_x86==0 else
                       0x97 if extra_followup_x86 in (78,105) else
                       0x98 if extra_followup_x86 in (151,153,178,180) else
                       0x9C if extra_followup_x86 in (370,378,397,405) else
                       0x9F if extra_followup_x86 in (516,528,543,555) else
                       0xA0 if extra_followup_x86 in (582,596,609,623) else
                       0xA4 if extra_followup_x86 in (801,815,828,842) else 0xA8)
    refs91=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:continue
        target=next((x for x in inst if x.address<=field['offset']<x.address+x.size),None)
        if target is not None and target.mnemonic=='mov' and target.op_str.endswith(f', 0x{next_marker_value:x}'):
            refs91.append(target)
    need(len(refs91)==1,
         f'{addr:#x}: actual next original indexed action source marker not unambiguous')
    marker_end=refs91[0].address
    index=inst.index(refs91[0])
    need(index>=3*80+extra_followup_x86,
         f'{addr:#x}: candidate does not own three complete 80-x86 cases plus real followup')
    case_source=inst[index-3*80-extra_followup_x86:index-extra_followup_x86]
    case_start=case_source[0].address
    end=(inst[index-extra_followup_x86].address if extra_followup_x86
         else marker_end)
    need(case_source[-1].address+case_source[-1].size==end,
         f'{addr:#x}: actual source case0x90 does not join true original next action boundary')
    # Prior native 0x63 source ends EXACTLY at the first 0x8C case;
    # on seven original actors this case was already strict. Its
    # original native GPR/typed symbols are independently rechecked
    # here after adding all three new C++ cases (register phase can
    # change with different enclosing source, as F620 proved).
    dense=boss['tables'][1]
    sparse=reader.pe_bytes_at(pe,dense['map_addr'],dense['map_length'])
    # Native physical second-switch size is 26 slots for some actors,
    # 27 for others. Always use the real PE compressed map rather than
    # importing another fighter's last slot number.
    slot=sparse[0x63-0x33]
    need(len(sparse)==49 and slot==dense['slots']-2
         and int.from_bytes(reader.pe_bytes_at(pe,dense['dense_addr']+4*slot,4),'little')==by[0x63],
         f'{addr:#x}: actual original 0x63 packed case versus default slot differs')
    label=[x for x in refs if x['offset']==ret+44+4*slot]
    need(len(label)==1 and label[0]['type']=='DIR32'
         and label[0]['addend']==0 and label[0]['local_symbol_offset'] is not None,
         f'{addr:#x}: actual native 0x63 preceding C++ case label missing')
    prev_lo=label[0]['local_symbol_offset']
    prev_source=list(decoder.disasm(code[prev_lo:case_start],prev_lo))
    if addr in (*SPECIAL,*REGULAR,*PRIORITY):
        prev_case=by[0x63]
        next_case=by[0x8C]
        prev_native=list(decoder.disasm(reader.pe_bytes_at(pe,prev_case,next_case-prev_case),prev_case))
        expected_count=118 if addr in SPECIAL else (138 if addr in PRIORITY else 109)
        need(len(prev_source)==len(prev_native)==expected_count,
             f'{addr:#x}: prior source-backed native action0x63 count shifted after new cases')
        original_roles,compiled_roles=f598.normalized(prev_native),f598.normalized(prev_source)
        need(original_roles[0][1].endswith('byte ptr [0x6714b4]')
             and compiled_roles[0][1].endswith('byte ptr [0]'),
             f'{addr:#x}: native original previous mode PE/COFF global changed')
        original_roles[0]=compiled_roles[0]=('movsx','NATIVE_TYPED_GLOBAL_006714B4')
        errors=[(i,x,y) for i,(x,y) in enumerate(zip(original_roles,compiled_roles)) if x!=y]
        need(not errors,f'{addr:#x}: previously strict 0x63 GPR/CFG source shifted: {errors[:4]}')
        prev_fields=(h['f624'].REAL_FIELDS if addr in SPECIAL else
                     h['f627_priority'].FIELDS if addr in PRIORITY else h['f626'].FIELDS)
        expected_fields=len(prev_fields)
        physical=[x for x in refs if prev_lo<=x['offset']<case_start]
        need(len(physical)==expected_fields,
             f'{addr:#x}: original mode63 previous actual typed PE/COFF refs missing')
        for i,(dest,mn,symbol) in prev_fields.items():
            a,b=prev_native[i],prev_source[i]
            need(a.mnemonic==b.mnemonic==mn,
                 f'{addr:#x}: original previous mode63 PE x86 typed ordinal{i} changed')
            found=[x for x in physical if b.address<=x['offset']<b.address+b.size]
            need(len(found)==1 and found[0]['type']==('DIR32' if i==0 else 'REL32')
                 and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
                 and symbol in found[0]['symbol'],
                 f'{addr:#x}: original 0x63 global/game target {dest:#x} at{i} altered')
        # Width checks include native 118-case wide stack this on
        # original 0x00564BE0, already proven separately in F624.
    else:
        # This selected owner has an honestly unfinished mode63 case;
        # no claim it remains strict against the original native 138
        # or 109 instruction source, even if 8C..90 do match.
        need(len(prev_source) in (2,8),
             f'{addr:#x}: earlier unresolved 0x63/0x89 placeholder geometry unexpectedly changed')
    results=[]
    for action,offset in zip(ACTIONS,(0,80,160)):
        native,info=caseinfo[action]
        source=case_source[offset:offset+80]
        need(len(source)==len(native)==80,
             f'{addr:#x}: original complete native case{action:x} 80 x86 source was truncated')
        sizes=[x.size-y.size for x,y in zip(native,source)]
        if addr==0x00564BE0:
            need(sizes.count(3)==24 and sizes.count(0)==56
                 and all(native[i].op_str.endswith('dword ptr [ebp - 0x88]')
                         for i,w in enumerate(sizes) if w==3),
                 'original 8C/8F/90 wide actor 24 real EBP-0x88 receiver MOVs not reproduced')
        else:need(all(x==0 for x in sizes),
                  f'{addr:#x}: original compact case{action:#x} instruction width differences')
        lo=source[0].address;hi=source[-1].address+source[-1].size
        need(hi-lo==289,
             f'{addr:#x}: case{action:#x} source is not full 80-instruction/289-byte native grammar')
        actual_fields=[x for x in refs if lo<=x['offset']<hi]
        need(len(actual_fields)==len(FIELDS)==8,
             f'{addr:#x}: original case{action:#x} typed zero-addend COFF field count changed')
        for i,(dest,mn,symbol) in FIELDS.items():
            original,generated=native[i],source[i]
            need(original.mnemonic==generated.mnemonic==mn,
                 f'{addr:#x}: original 8C/8F/90 physical instruction ordinal{i} moved')
            field=[x for x in actual_fields if generated.address<=x['offset']<generated.address+generated.size]
            need(len(field)==1 and field[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and field[0]['addend']==0 and field[0]['local_symbol_offset'] is None
                 and symbol in field[0]['symbol'],
                 f'{addr:#x}: original PE real target {dest:#x} at {i} vs source COFF differs: {field}')
        lhs,rhs=f598.normalized(native),f598.normalized(source)
        mistakes=[(i,n,c) for i,(n,c) in enumerate(zip(lhs,rhs)) if n!=c]
        need(len(mistakes)==(51 if negative else 0),
             f'{addr:#x}: original case{action:#x} GPR/x87/CFG role mismatch {len(mistakes)} expected {51 if negative else 0}, first {mistakes[:5]}')
        results.append({'original_native_action':f'0x{action:02X}',
                        'complete_original_native_inner_CODE_bytes':info['original_complete_case_CODE_bytes'],
                        'full_native_x86_roles':80,'real_native_typed_PE_COFF_fields':8,
                        'native_role_mismatches':len(mistakes),
                        'independently_strict_source_original_grammar':not mistakes,
                        'new_accepted_full_game_function_CODE':0})
    return {'whole_original_giant':f'0x{addr:08X}',
            'whole_original_native_CODE_still_NONEXACT':boss['size'],
            'complete_original_afterRET_jump_DATA_separately_owned':boss['postret_size'],
            'previous_30_real_game_case_grammar_preserved_on_new_OBJ':True,
            'original_mode63_previous_strict_role_preserved':addr in (*SPECIAL,*REGULAR,*PRIORITY),
            'three_native_complete_cases':results,
            'strict_original_interior_CODE_bytes_uncredited':0 if negative else sum(x[1]['original_complete_case_CODE_bytes'] for x in caseinfo.values()),
            'new_accepted_exact_whole_game_functions':0}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='one original strict 8C/8F/90 parent, default eight affected giant sources')
    parser.add_argument('--negative-actor',choices=[f'0x{x:08X}' for x in NEGATIVE],
                        help='independent original 51-roles-mismatching register-phase negative')
    opt=parser.parse_args()
    need(not(opt.boss and opt.negative_actor),'choose strict or a genuine negative context')
    negative=bool(opt.negative_actor)
    selected=[int(opt.negative_actor,0)] if negative else ([int(opt.boss,0)] if opt.boss else list(POSITIVE))
    need(all(addr in (NEGATIVE if negative else POSITIVE) for addr in selected),
         'selected original register allocation family is not strict 8C/8F/90 source')
    source=INC.read_text()
    need(source.count('case F628_CASE:')==1
         and source.count('ContactAt454EE0()')==1
         and source.count('g_JumpGroundCorrectionAt00658058')==1
         and source.count('g_JumpReflectionAt006583E8')==1
         and 'I16(F628_COUNTER)<F628_LIMIT' in source,
         'original x87 landing/bounce/stage-counter C++ source unexpectedly changed')
    loaders={
      'f602':'scripts/verify-fighter-trajectory46-f602.py',
      'f603':'scripts/verify-fighter-trajectory-spawn-f603.py',
      'f600':'scripts/verify-fighter-additional-contact-f600.py',
      'f598':'scripts/verify-fighter-singleton-contact-f598.py',
      'f567':'scripts/verify-fighter-all-multiswitch-opening-cases.py',
      'f605':'scripts/verify-fighter-trajectory-followups-f605.py',
      'f606':'scripts/verify-fighter-trajectory-followup-spawns-f606.py',
      'f607':'scripts/verify-fighter-trajectory-landing-f607.py',
      'f608':'scripts/verify-fighter-trajectory-landing-spawn-f608.py',
      'f610':'scripts/verify-fighter-trajectory-bounce-f610.py',
      'f611':'scripts/verify-fighter-trajectory-bounce-spawn-f611.py',
      'f613':'scripts/verify-fighter-trajectory-recovery-f613.py',
      'f614':'scripts/verify-fighter-trajectory-burst-f614.py',
      'f622':'scripts/verify-fighter-counter-dispatch-f622.py',
      'f624':'scripts/verify-fighter-mode63-f624.py',
      'f626':'scripts/verify-fighter-mode63-basic-f626.py',
      'f627_priority':'scripts/verify-fighter-mode63-priority-f627.py',
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    helpers={name:load('f628_'+name,ROOT/path) for name,path in loaders.items()}
    reader=load('f628_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f628_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    records=[]
    for addr in selected:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native={action:native_case(reader,pe,decoder,boss,by,action) for action in ACTIONS}
        source=source_with_landing(addr,boss,report,mapped,reader,pe,decoder,helpers,native)
        cpp=OUT/f'Boss{addr:08X}-33-real-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-33-real-game-actions.obj'
        cpp.write_text(source)
        comp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=185)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(comp.stdout+comp.stderr)
        need(comp.returncode==0,
             f'{addr:#x}: original VC7.1 whole-fighter source compile failed: {comp.stderr[-500:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        result=verify_obj(reader,pe,decoder,boss,report,mapped,code,refs,native,helpers,negative)
        records.append(result)
        print(f'F628 {addr:#010x}: original real three 8C/8F/90 action cases '
              f'3×80 native x86 roles, {sum(x[1]["original_complete_case_CODE_bytes"] for x in native.values())} '
              f'original inner CODE B, 24 actual PE/COFF typed fields; '
              f'{[x["native_role_mismatches"] for x in result["three_native_complete_cases"]]} GPR/CFG mismatches; '
              'earlier original case source and entire afterRET DATA preserved, '
              'whole enclosing giant NONEXACT',flush=True)
    out=OUT/('negative-summary.json' if negative else ('summary.json' if not opt.boss else f'summary-{selected[0]:08X}.json'))
    out.write_text(json.dumps(records,indent=2)+'\n')
    print(f'F628 {len(records)} selected entire giant source TUs, '
          f'{sum(x["strict_original_interior_CODE_bytes_uncredited"] for x in records)} '
          'new original native strict **interior** CODE bytes UNcredited, '
          'no new whole exact authored function and no all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F628 original Japanese native 8C/8F/90 strict-source proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
