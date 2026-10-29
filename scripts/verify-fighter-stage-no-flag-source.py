#!/usr/bin/env python3
"""F557: natural C++ action6/7 in two original 115-insn fighter giants.

Both original native cases have stage-dependent x87/helper behavior but
NO state FLAG clear; one has a genuine EBP-0x88 wide frame and long JL.
Check complete original huge CODE SHA and physical post-RET data, then
cold-compile only these new small source-probe TUs. Never count interior
cases or diagnostic marker actions as complete original exact CODE.
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
OUT=ROOT/'.analysis/f557-no-flag-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
BOSSES={0x00543210:'Boss00543210',0x00564BE0:'Boss00564BE0'}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def module(tag,p):
    spec=importlib.util.spec_from_file_location(tag,p)
    need(spec is not None and spec.loader is not None,f'missing independent original verifier: {p}')
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m)
    return m


def original_case(reader,pe,decoder,boss,number,old):
    table=boss['tables'][0]
    need(table['slots']==11 and table['map_addr'] is None and boss['jump_count']==7,
         'not original seven-way multi-switch boss')
    raw=reader.pe_bytes_at(pe,table['dense_addr']+4*number,8)
    a,b=(int.from_bytes(raw[i:i+4],'little') for i in (0,4))
    need(boss['address']<a<b<boss['address']+boss['size'],
         'original inner case outside full native function')
    native=list(decoder.disasm(reader.pe_bytes_at(pe,a,b-a),a))
    expected=508 if boss['address']==0x00564BE0 else 393
    need(len(native)==115 and b-a==expected and native[0].address==a
         and native[-1].address+native[-1].size==b,
         'original action six/seven whole case not 115 native x86 instructions')
    need(native[10].mnemonic=='cmp' and native[10].op_str.endswith(', '+str(3 if number==6 else 5))
         and native[16].mnemonic=='push' and native[16].op_str==('0xcc' if number==6 else '0xcd'),
         'native per-action unsigned state threshold/argument changed')
    need(native[60].mnemonic=='cmp' and native[64].mnemonic=='fcomp'
         and native[64].op_str=='dword ptr [0x657d14]'
         and native[68].mnemonic=='push' and native[70].mnemonic=='call'
         and native[70].op_str=='0x40fb40',
         'extra-stage original physical float compare/callback not preserved')
    guard=int(native[60].op_str.split(', ')[-1],0)
    aux=int(native[68].op_str,0)
    need((guard,aux) in ((3,4),(4,5),(2,3)),
         'native fighter-specific extra-stage and auxiliary argument unknown')
    need(native[91].mnemonic=='cmp','native postcounter stage threshold not found')
    stage=int(native[91].op_str.split(', ')[-1],0)
    need(stage in (2,3),'original native stage count changed')
    need(all(native[i].mnemonic=='mov' for i in (94,96,98)),
         'native no-flag C++ original float stores missing')
    for i,offset in ((94,'0x50'),(96,'0x54'),(98,'0x5c')):
        need(f' + {offset}]' in native[i].op_str,
             f'native action {number} writes unexpected field at physical instruction {i}')
    pos=old.literal_float(int(native[94].op_str.rsplit(', ',1)[-1],16)) if native[94].op_str.rsplit(', ',1)[-1]!='0' else '0.0f'
    floats=[old.literal_float(int(native[i].op_str.rsplit(', ',1)[-1],16)) for i in (96,98)]
    need(native[99].mnemonic=='mov' and native[100].mnemonic=='movsx'
         and '+ 0x62' in native[100].op_str,
         'native no-flag case contains unexpected flag assignment')
    need(native[-2].mnemonic=='call' and native[-2].op_str=='dword ptr [edx]',
         'actual original vtable indirect source call changed')
    return native,dict(guard=guard,aux=aux,stage=stage,pos=pos,floats=floats)


def generate(tag,first,second,report,mapped,reader,pe,decoder,boss,
             old,opening,switch,zero,one):
    n0,v0=first;n1,v1=second
    need(v0['stage']==v1['stage'], 'original native two actions have different stage gate')
    original=old.generate_source(tag,v0['stage'],v0['floats'],report,mapped,
                                 opening,switch,zero,one,reader,pe,decoder,boss)
    mark='case 0x7: g_FighterProbeMarker = 8; break;'
    firstmarker='case 0x6:'
    need(original.count(firstmarker)==1 and original.count(mark)==1,
         'the previous original-backed six source no longer has correct action labels')
    prefix=original[:original.index(firstmarker)]
    source6=original[original.index(firstmarker):original.index(mark)]
    suffix=original[original.index(mark)+len(mark):]
    need(source6.count('                    FLAG = 0;')==1,
         'one real original flag-clear negative control was not found')
    source6=source6.replace('                    FLAG = 0;\n','')
    need('FLAG = 0;' not in source6,'the source still performs a nonoriginal flag-clear')
    needle='            ++S16(0x64);'
    need(source6.count(needle)==1,'native source frame increment boundary lost')
    extra=f'''            if (S16(0x62) == {v0['guard']} && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40({v0['aux']});
'''
    source6=source6.replace(needle,extra+needle)
    source7=(source6.replace(firstmarker,'case 0x7:',1)
       .replace('U8(0x511) == 3','U8(0x511) == 5')
       .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCD)')
       .replace(f'S16(0x62) == {v0["guard"]} && POS54 < g_ExtraThresholdAt00657D14',
                f'S16(0x62) == {v1["guard"]} && POS54 < g_ExtraThresholdAt00657D14')
       .replace(f'SetAuxActionAt40FB40({v0["aux"]})',f'SetAuxActionAt40FB40({v1["aux"]})')
       .replace('POS = 0.0f;',f'POS = {v1["pos"]};')
       .replace(f'POS54 = {v0["floats"][0]};',f'POS54 = {v1["floats"][0]};')
       .replace(f'POS5C = {v0["floats"][1]};',f'POS5C = {v1["floats"][1]};'))
    need('FLAG = 0' not in source7,'action7 has false native flag-clear')
    compiled=prefix+source6+source7.rstrip()+suffix
    declaration='void SetNativeActionAt40FAC0(int);'
    need(compiled.count(declaration)==1,'native actor method prototype changed')
    compiled=compiled.replace(declaration,declaration+' void SetAuxActionAt40FB40(int);')
    ext='extern float g_ThresholdAt0065782C;'
    need(compiled.count(ext)==1,'native original x87 threshold declaration missing')
    compiled=compiled.replace(ext,ext+'\nextern float g_ExtraThresholdAt00657D14;')
    previous=f'FighterSwitchF548_{tag}'
    need(compiled.count(previous)>=2,'old source class unexpectedly changed')
    return compiled.replace(previous,f'FighterSwitchF557_{tag}')


def compile_one(tag,source):
    OUT.mkdir(parents=True,exist_ok=True)
    path=OUT/f'{tag}-no-flag.cpp';obj=OUT/f'{tag}-no-flag.obj'
    path.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(path),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/f'{tag}-compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,f'{tag}: selected VC7.1 native source did not compile: {p.stderr}')
    return obj


def candidate(reader,decoder,obj,tag,boss):
    raw,relocs=reader.object_function(obj,f'?Advance@FighterSwitchF557_{tag}@@QAEXXZ')
    ins=[]
    for x in decoder.disasm(raw,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret','generated native C++ has no normal RET')
    end=ins[-1].address+ins[-1].size
    need(len(raw)-end==boss['postret_size'],'native post-RET CODE/DATA boundary lost')
    slots=sorted((r for r in relocs if end+24<=r['offset']<end+36),key=lambda r:r['offset'])
    need(len(slots)==3 and all(r['type']=='DIR32' and r['offset']==end+24+i*4
             and r['local_symbol_offset'] is not None for i,r in enumerate(slots)),
         'original native case6/7/8 physical COFF slots missing')
    addr=[r['local_symbol_offset'] for r in slots]
    need(addr==sorted(set(addr)) and 0<=addr[0]<addr[-1]<end,
         'native original candidate case addresses overlap')
    cases=[]
    for i in (0,1):
        start,finish=addr[i:i+2]
        body=list(decoder.disasm(raw[start:finish],start))
        need(len(body)==115 and sum(z.size for z in body)==393,
             'generated original-style source case not complete 393-byte/115-insn body')
        cases.append(body)
    return raw,relocs,ins,end,cases


def verify_wide_encodings(native,probe,boss):
    need(len(native)==len(probe)==115,'native/compiled complete case length not 115')
    if boss['address']==0x00543210:
        need(all(x.size==y.size for x,y in zip(native,probe)),
             'normal EBP disp8 case source instruction lengths changed')
        return 0,0
    differences=[(i,x,y,x.size-y.size) for i,(x,y) in enumerate(zip(native,probe))
                 if x.size!=y.size]
    wide=[x for x in differences if x[3]==3 and x[1].mnemonic=='mov'
          and '[ebp - 0x88]' in x[1].op_str]
    branches=[x for x in differences if x[3]==4 and x[1].mnemonic=='jl'
              and x[2].mnemonic=='jl']
    need(len(wide)==37 and len(branches)==1 and len(differences)==38
         and sum(x[3] for x in differences)==115,
         'native 508-byte case not precisely 37 wide EBP loads + one long JL')
    return len(wide),len(branches)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='One original PE 0x00543210/0x00564BE0 giant; default both')
    args=parser.parse_args()
    reader=module('f557_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f557_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f557_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f557_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f557_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    opening=module('f557_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    source6=module('f557_six',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    extra=module('f557_extra',ROOT/'scripts/verify-fighter-extra-stage-action-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    originals={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    need(sum(originals[a]['size'] for a in BOSSES)==120166,
         'native original 58K/62K fighter CODE SHA cohort changed')
    selected=list(BOSSES)
    if args.boss:
        addr=int(args.boss,0)
        need(addr in BOSSES,'original fighter not one of the 115-insn no-flag cohort')
        selected=[addr]
    results=[]
    for addr in selected:
        boss=originals[addr];tag=BOSSES[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        cases=[original_case(reader,pe,decoder,boss,k,source6) for k in (6,7)]
        cpp=generate(tag,cases[0],cases[1],report,mapped,reader,pe,decoder,boss,
                     source6,opening,switch,zero,one)
        obj=compile_one(tag,cpp)
        raw,relocs,all_ins,ret,compiled=candidate(reader,decoder,obj,tag,boss)
        native_fields=0;wide_reads=0;long_jumps=0
        for (native,policy),code in zip(cases,compiled):
            source6.compare_grammar(native,code)
            wide,long=verify_wide_encodings(native,code,boss)
            wide_reads+=wide;long_jumps+=long
            native_fields+=extra.verify_physical_fields(native,code,relocs)
        need(native_fields==16,'two real 115-insn cases require exactly 16 typed original COFF fields')
        dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,reader,
                                                      switch,all_ins,raw,relocs,ret)
        x={'boss':f'0x{addr:08X}','whole_original_CODE':boss['size'],
           'native_case6_and_case7_bytes':(508 if addr==0x00564BE0 else 393),
           'candidate_case_bytes_each':393,'native_case_instructions_each':115,
           'actual_case_COFF_fields':native_fields,
           'original_source_case6':cases[0][1], 'original_source_case7':cases[1][1],
           'native_wide_EBP_loads_total':wide_reads,'native_extra_long_JLs_total':long_jumps,
           'physical_switch_DWORD_COFF_refs':dense,'original_sparse_bytes':sparse,
           'full_original_postret_DATA_shape':len(raw)-ret}
        results.append(x)
        print(f'{addr:#010x}: complete original 115/115 actions 6 and 7, '
              f'{x["native_case6_and_case7_bytes"]} native bytes each vs 393 natural source; '
              f'16/16 genuine typed COFF fields; native stages {cases[0][1]["stage"]}/'
              f'{cases[1][1]["stage"]}, extra-state thresholds '
              f'{cases[0][1]["guard"]}/{cases[1][1]["guard"]}; '
              f'original wide owner reads {wide_reads} and extra long JL {long_jumps}; '
              f'{dense} table DWORD refs and {sparse} native sparse bytes',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    output='summary.json' if args.boss is None else f'summary-{selected[0]:08X}.json'
    (OUT/output).write_text(json.dumps(results,indent=2)+'\n')
    print(f'{len(results)}/{len(selected)} whole original fighter contexts validated with new VC7.1 '
          'natural source; NO cropped/whole CODE or all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('TH075 native 115-insn fighter source check failed:',e,file=sys.stderr)
        raise SystemExit(1)
