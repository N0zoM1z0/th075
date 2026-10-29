#!/usr/bin/env python3
"""F607: full native 99-instruction 0x49 landings in nine giant fighters.

Only compile selected original-backed whole fighter source TUs, keep
strict previous 26 real action cases, all physical after-RET switch data,
read actual original PE 0x49/0x4A target boundaries and 15 COFF fields.
The original containing boss stays NONEXACT; NO split case CODE credit.
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
INC=ROOT/'probes/FighterTrajectoryLanding49F607.inc'
OUT=ROOT/'.analysis/f607-fighter-landing-source'
F607_FIELDS={25:(0x0065782C,'fcomp'),31:(0x00657888,'fmul'),
  32:(0x006406AC,'call'),37:(0x00657888,'fmul'),38:(0x006406AC,'call'),
  42:(0x00453E20,'call'),47:(0x0040FAC0,'call'),50:(0x00453E60,'call'),
  53:(0x00453D60,'call'),56:(0x0040FA30,'call'),67:(0x0040FB40,'call'),
  77:(0x0065782C,'fld'),84:(0x0065782C,'fld'),92:(0x0040FB40,'call'),
  96:(0x0040FB40,'call')}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing original PE reader '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def native_case(reader,pe,decoder,boss,by):
    addr=boss['address'];start,end=by[0x49],by[0x4A]
    orig=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=441 if addr==0x00564BE0 else 350
    need(addr<=start<end<addr+boss['size'] and end-start==size
         and len(orig)==99 and sum(x.size for x in orig)==size
         and orig[-1].mnemonic=='jmp',
         f'{addr:#x}: native complete action0x49 original size/role/boundary changed')
    # Ensure these are actual native PE observations, not decompiler guesses:
    # C++ deliberately uses the real raw DWORD copy in init, and the native
    # final equality test has two FLD/FUCOMPP pairs rather than FCOMP.
    need(orig[9].mnemonic=='fld' and orig[10].mnemonic=='fchs'
         and orig[15].mnemonic=='mov' and orig[15].op_str.endswith('+ 0x98]')
         and orig[16].mnemonic=='mov' and '+ 0x54]' in orig[16].op_str
         and 'dword ptr' in orig[16].op_str
         and orig[18].mnemonic=='mov' and orig[18].op_str.endswith(', 0x3f4ccccd')
         and [orig[i].mnemonic for i in (79,86)]==['fucompp','fucompp']
         and [orig[i].op_str for i in (81,88)]==['ah, 0x44','ah, 0x44']
         and orig[82].mnemonic=='jnp' and orig[89].mnemonic=='jp'
         and orig[70].mnemonic=='cmp' and orig[70].op_str.endswith(', 1')
         and [orig[i].op_str for i in (90,94)]==['3','2'],
         f'{addr:#x}: true original 0x49 stage-one equality/branch semantics differ')
    origshort=[]
    for index in (34,40):
        x=orig[index]
        m=re.fullmatch(r'word ptr \[[a-z]+ \+ (0x[0-9a-f]+)\], ax',x.op_str)
        need(x.mnemonic=='mov' and m is not None,
             f'{addr:#x}: native original float-to-short trajectory store {index} differs')
        origshort.append(int(m.group(1),16))
    need(origshort[0] in (0xF00,0xEFC) and origshort[1]==origshort[0]+2,
         f'{addr:#x}: native +0xF00 or +0xEFC trajectory slots changed')
    for idx,(target,mnemonic) in F607_FIELDS.items():
        x=orig[idx]
        need(x.mnemonic==mnemonic,
             f'{addr:#x}: native original typed source 0x49 ordinal{idx} changed')
        need(x.op_str==(f'0x{target:x}' if mnemonic=='call'
                        else f'dword ptr [0x{target:x}]'),
             f'{addr:#x}: original 0x49 real callee/float global differs at {idx}')
    return orig,{'original_native_handler':f'0x{start:08X}',
                 'original_complete_case_CODE_bytes':size,
                 'original_full_x86_instructions':99,
                 'native_trajectory_short_offset':origshort[0],
                 'real_native_typed_COFF_fields':15,
                 'native_closing_double_float_comparison':'two FLD/FUCOMPP status tests',
                 'whole_original_fighter_exact':False}


def preserve_case(reader,pe,decoder,f598,f602,f605,f600,core,zero,switch,
                 boss,report,mapped,code,refs,original49,info):
    addr=boss['address'];inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret',f'{addr:#x}: no genuine final giant source RET')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: original whole afterRET switch DATA owned physical extent changed')
    # All 23 earlier original game source cases plus the 104-action0x46
    # and both complete 86-x86 action0x47/0x48 cases are checked in THIS
    # fresh new object, not an earlier persisted result.
    by={q['action']:int(q['handler'],16) for q in mapped}
    orig46,info46=f602.original_case(reader,pe,decoder,boss,by)
    original47_48={action:f605.original_action(reader,pe,decoder,boss,by,action)
                   for action in (0x47,0x48)}
    f605.check_candidate(reader,pe,decoder,f598,f602,f600,core,zero,switch,
                         boss,report,mapped,code,refs,original47_48,info46)
    table=boss['tables'][1]
    native_map=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    need(native_map[0x49-0x33]==14 and native_map[0x4A-0x33]==15,
         f'{addr:#x}: true original compressed 0x49 and 0x4A sparse slots differ')
    native_bound=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*i,4),'little')
                  for i in (14,15)]
    need(native_bound==[by[0x49],by[0x4A]],
         f'{addr:#x}: native original physical 0x49 and 0x4A jump table boundaries differ')
    offsets=[]
    for slot in (14,15):
        field=[r for r in refs if r['offset']==ret+44+4*slot]
        need(len(field)==1 and field[0]['type']=='DIR32'
             and field[0]['addend']==0 and field[0]['local_symbol_offset'] is not None,
             f'{addr:#x}: original physical action49/4A afterRET COFF symbol missing')
        offsets.append(field[0]['local_symbol_offset'])
    start,end=offsets
    candidate=list(decoder.disasm(code[start:end],start))
    need(len(candidate)==len(original49)==99 and end-start==350
         and sum(x.size for x in candidate)==350,
         f'{addr:#x}: natural C++ source not full native 99-x86/350-byte action49')
    diffwidth=[x.size-y.size for x,y in zip(original49,candidate)]
    if addr==0x00564BE0:
        need(diffwidth.count(3)==29 and diffwidth.count(4)==1
             and diffwidth.count(0)==69,
             f'{addr:#x}: genuine native 0x49 wide-frame receiver/near-jump expansion differs')
    else:
        need(all(x==0 for x in diffwidth),
             f'{addr:#x}: compact native 0x49 original physical x86 widths differ')
    # The original special fld [real-target] and the source fld [0]
    # must be checked against original source COFF relocations BEFORE
    # normalizing their field encodings. No arbitrary masking of two
    # opcode/byte mismatches is permitted.
    actual_fields=[r for r in refs if start<=r['offset']<end]
    need(len(actual_fields)==15 and len(F607_FIELDS)==15,
         f'{addr:#x}: missing genuine original 0x49 physical typed COFF fields')
    symbols={**f602.ALL_SYMBOLS}
    for i,(target,mnemonic) in F607_FIELDS.items():
        original,compiled=original49[i],candidate[i]
        need(original.mnemonic==compiled.mnemonic==mnemonic,
             f'{addr:#x}: real original typed original C++ x86 ordinal {i} changed')
        match=[r for r in actual_fields
               if compiled.address<=r['offset']<compiled.address+compiled.size]
        need(len(match)==1 and match[0]['type']==(
             'REL32' if mnemonic=='call' else 'DIR32')
             and match[0]['addend']==0 and match[0]['local_symbol_offset'] is None
             and symbols[target] in match[0]['symbol'],
             f'{addr:#x}: native source typed original target {target:#x} at {i} differs: {match}')
    original_shape,compiler_shape=f598.normalized(original49),f598.normalized(candidate)
    # Two actual fld constants: having PROVEN their own precise typed
    # original PE destination, make their normalized roles comparable.
    for idx in (77,84):
        need(original_shape[idx]==('fld','dword ptr [0x65782c]')
             and compiler_shape[idx]==('fld','dword ptr [0]'),
             f'{addr:#x}: original 0x49 true typed fld operand moved')
        original_shape[idx]=compiler_shape[idx]=('fld','NATIVE_TYPED_FLOAT_GLOBAL_0065782C')
    mismatches=[(i,n,c) for i,(n,c) in enumerate(zip(original_shape,compiler_shape)) if n!=c]
    need(not mismatches,
         f'{addr:#x}: complete native 0x49 source GPR/x87/CFG comparison changed: {mismatches[:8]}')
    return {'original_whole_giant':f'0x{addr:08X}',
            'whole_original_CODE_still_NONEXACT':boss['size'],
            'entire_original_afterRET_switch_DATA_separately_owned':boss['postret_size'],
            'prior_26_original_source_cases_preserved':True,
            'source_complete_native_0x49':info,
            'source_new_case_CODE_bytes':350,
            'native_original_x86_roles':99,
            'native_typed_PE_COFF_fields':15,
            'exact_whole_game_functions_new':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one selected original nine regular giant fighters')
    opt=p.parse_args()
    f602=load('f607_f602',ROOT/'scripts/verify-fighter-trajectory46-f602.py')
    f600=load('f607_f600',ROOT/'scripts/verify-fighter-additional-contact-f600.py')
    f598=load('f607_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f607_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    f605=load('f607_f605',ROOT/'scripts/verify-fighter-trajectory-followups-f605.py')
    reader=load('f607_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f607_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f607_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f607_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f607_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses={r['address']:r for r in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    selected_cohort=[x for x in cohort if x not in (0x0045DD70,0x0058AF60)]
    chosen=[int(opt.boss,0)] if opt.boss else selected_cohort
    need(len(selected_cohort)==9 and all(addr in selected_cohort for addr in chosen),
         'selected giant has different native 118-instruction action0x49, must not use 99-insn source')
    source=INC.read_text()
    need(source.count('case 0x49:')==1 and 'I32(0x54) = I32(0x98)' in source
         and source.count('fucompp')==0 and '*(&POS) == g_ThresholdAt0065782C' in source,
         'genuine 0x49 natural native C++ source unexpectedly changed')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    results=[]
    for addr in chosen:
        boss=bosses[addr]
        report,mapped=actions.report_boss(reader,pe,dec,boss)
        by={r['action']:int(r['handler'],16) for r in mapped}
        orig46,info46=f602.original_case(reader,pe,dec,boss,by)
        attrs={action:f605.original_action(reader,pe,dec,boss,by,action)[1]
               for action in (0x47,0x48)}
        native49,info49=native_case(reader,pe,dec,boss,by)
        generated=f605.reconstruct_source(addr,boss,report,mapped,
                     reader,pe,dec,f602,f598,f567,info46,attrs)
        placeholder='        case 0x49: g_FighterProbeMarker = 74; break;'
        need(generated.count(placeholder)==1,
             f'{addr:#x}: genuine second-switch next source case placeholder moved')
        generated=generated.replace(placeholder,
                f'#define F607_COUNTER 0x{info49["native_trajectory_short_offset"]:X}\n'
                '#include "FighterTrajectoryLanding49F607.inc"\n'
                '#undef F607_COUNTER')
        cpp=OUT/f'Boss{addr:08X}-27-real-native-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-27-real-native-actions.obj'
        cpp.write_text(generated)
        p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
              env=env,cwd=ROOT,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compile.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,f'{addr:#x}: original pinned VC7.1 compiler failed: {p.stderr[-550:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        result=preserve_case(reader,pe,dec,f598,f602,f605,f600,core,zero,switch,
                             boss,report,mapped,code,refs,native49,info49)
        results.append(result)
        print(f'F607 {addr:#010x}: real native case0x49 99/99 x86 roles, '
              f'{info49["original_complete_case_CODE_bytes"]} native inner CODE bytes '
              'and 15/15 original PE/COFF fields, earlier 26 cases and '
              'entire afterRET switch DATA preserved; entire boss NONEXACT',flush=True)
    out=OUT/('summary.json' if not opt.boss else f'summary-{chosen[0]:08X}.json')
    out.write_text(json.dumps(results,indent=2)+'\n')
    print(f'F607 {len(results)} selected giant TUs / {len(results)*99} original x86 roles '
          f'/ {sum(r["source_complete_native_0x49"]["original_complete_case_CODE_bytes"] for r in results)} '
          f'original *uncredited* inner CODE bytes / {len(results)*15} actual typed COFF fields; '
          'zero whole exact function credit or all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F607 true original native fighter landing case failed:',e,file=sys.stderr)
        raise SystemExit(1)
