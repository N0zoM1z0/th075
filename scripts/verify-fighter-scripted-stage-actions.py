#!/usr/bin/env python3
"""F565: native action6/7/8 in original 46,755-byte fighter 005214B0.

This fighter does NOT implement regular C++ actor frame advancement.
Recover the genuine three complete original states from the SHA-verified
Japanese PE and compile one VC7.1 natural switch source (other actions
remain diagnostic marker stores). Check original native case x86 grammar,
all real physical COFF fields and whole original jump DATA; no partial/
whole exact CODE acceptance and no full all-unit cold replay.
"""
from __future__ import annotations

import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
OUT=ROOT/'.analysis/f565-scripted-stage-source'
ADDR=0x005214B0
TAG='Boss005214B0'
TYPED={
    0x0040FAC0:('REL32','SetNativeActionAt40FAC0'),
    0x00453E20:('REL32','ResetAt453E20'),
    0x0040FB40:('REL32','SetAuxActionAt40FB40'),
    0x0040FA30:('REL32','GetNativeActionAt40FA30'),
    0x0065782C:('DIR32','g_ThresholdAt0065782C'),
    0x00657D14:('DIR32','g_ExtraThresholdAt00657D14'),
}

def need(ok,message):
    if not ok:raise ValueError(message)

def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         f'missing native-source helper {path}')
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m

def whole_original_cases(reader,pe,decoder,boss,core):
    table=boss['tables'][0]
    need(boss['address']==ADDR and boss['size']==46755
         and boss['postret_size']==901 and boss['jump_count']==7
         and table['map_addr'] is None and table['slots']==11,
         'original complete scripted fighter CODE/switch DATA drift')
    data=reader.pe_bytes_at(pe,table['dense_addr']+24,16)
    points=[int.from_bytes(data[k:k+4],'little') for k in (0,4,8,12)]
    need(points==sorted(set(points)) and
         all(ADDR<=x<ADDR+boss['size'] for x in points),
         'physical original actor 6/7/8/9 case boundaries changed')
    cases=[]
    for idx in range(3):
        start,end=points[idx:idx+2]
        block=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
        n,size=(96,331) if idx==0 else (83,290)
        need(len(block)==n and end-start==size and
             block[0].address==start and block[-1].address+block[-1].size==end,
             'original scripted action body is not complete contiguous native x86')
        need(block[10].mnemonic=='cmp' and
             block[10].op_str.endswith(', '+str((3,5,4)[idx]))
             and block[16].mnemonic=='push' and
             block[16].op_str==('0xcc','0xcd','0xce')[idx],
             'native scripted initial frame-state/argument different')
        need(block[32].mnemonic=='cmp' and block[32].op_str.endswith(', 2')
             and block[33].mnemonic=='jle',
             'native original signed-stage>2 guard absent: not a float position precondition')
        need(block[44].mnemonic=='fcomp'
             and block[44].op_str=='dword ptr [0x65782c]',
             'native original x87 contact did not use pinned threshold')
        need(block[-1].mnemonic=='jmp'
             and not any(x.mnemonic=='call' and x.op_str.startswith('dword ptr [')
                         for x in block),
             'native scripted action unexpectedly has frame-advance vtable call')
        points_for_float=(88,90,92) if idx==0 else (75,77,79)
        expected_bits=((0x00000000,0x41800000,0x3F4CCCCD),
                       (0x40B00000,0x41800000,0x3F4CCCCD),
                       (0xC0B00000,0x41800000,0x3F4CCCCD))[idx]
        for ordinal,offset,bits in zip(points_for_float,('0x50','0x54','0x5c'),expected_bits):
            ins=block[ordinal]
            need(ins.mnemonic=='mov' and '+ '+offset+']' in ins.op_str
                 and int(ins.op_str.rsplit(', ',1)[-1],0)==bits,
                 f'original script motion field/float changed at case {idx+6}')
        flag=block[94 if idx==0 else 81]
        need(flag.mnemonic=='mov' and '+ 0x3ac]' in flag.op_str
             and flag.op_str.endswith(', 0'),
             'original script case clears flag after all three motion fields')
        calls=[(j,x.op_str) for j,x in enumerate(block)
               if x.mnemonic=='call' and x.op_str.startswith('0x')]
        wanted=([(18,'0x40fac0'),(29,'0x453e20'),
                 (50,'0x40fac0'),(54,'0x453e20'),
                 (68,'0x40fb40'),(70,'0x40fa30'),(78,'0x40fb40')]
                if idx==0 else
                [(18,'0x40fac0'),(29,'0x453e20'),
                 (50,'0x40fac0'),(54,'0x453e20'),
                 (57,'0x40fa30'),(65, '0x40fac0' if idx==1 else '0x40fb40')])
        need(calls==wanted,'native real script-state call sequence changed')
        if idx==0:
            need(block[58].mnemonic=='cmp' and block[58].op_str.endswith(', 4')
                 and block[62].mnemonic=='fcomp'
                 and block[62].op_str=='dword ptr [0x657d14]'
                 and block[66].mnemonic=='push' and block[66].op_str=='5'
                 and block[76].mnemonic=='push' and block[76].op_str=='0xb',
                 'two original auxiliary-state calls missing in native case 6')
        else:
            value=9 if idx==1 else 13
            need(block[63].mnemonic=='push'
                 and int(block[63].op_str,0)==value,
                 'native script case 7/8 state transition argument differs')
        cases.append(block)
    return cases

def source_for(reader,pe,decoder,boss,report,mapped,opening,switch,zero,one):
    originals=opening.native_six(reader,pe,decoder,boss)
    base,ncases,floats=opening.source_for(switch,zero,one,report,mapped,TAG,originals)
    existing=f'FighterSwitchF545_{TAG}'
    need(base.count(existing)>=2,'previous original opening source class changed')
    base=base.replace(existing,f'FighterSwitchF565_{TAG}')
    declaration='void SetNativeActionAt40FAC0(int);'
    need(base.count(declaration)==1,'real actor state setter declaration missing')
    base=base.replace(declaration,declaration+' void SetAuxActionAt40FB40(int);')
    global_decl='extern float g_ThresholdAt0065782C;'
    need(base.count(global_decl)==1,'actual game x87 state source global missing')
    base=base.replace(global_decl,global_decl+
                      '\nextern float g_ExtraThresholdAt00657D14;')
    macro='#define FLAG'
    need(base.count(macro)==1,'native member source macro missing')
    base=base.replace(macro,'''#define POS48 *reinterpret_cast<float*>(RAW+0x48)
#define POS54 *reinterpret_cast<float*>(RAW+0x54)
#define POS5C *reinterpret_cast<float*>(RAW+0x5C)
#define S16(off) (*reinterpret_cast<signed short*>(RAW+(off)))
#define U8(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))
'''+macro)
    def start(action):
        initial,callback=(3,0xCC) if action==6 else (
                          (5,0xCD) if action==7 else (4,0xCE))
        return f'''case 0x{action:X}:
            if (S16(0x62) == 0 && S16(0x64) == 0 &&
                    (U8(0x511) == {initial} || FLAG > 0)) {{
                SetNativeActionAt40FAC0(0x{callback:X});
                return;
            }}
            if (S16(0x62) == 0 && FLAG == 0)
                ResetAt453E20();
            if (S16(0x62) > 2) {{
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {{
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }}
            }}
'''
    block6=start(6)+'''            if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(5);
            if (GetNativeActionAt40FA30() == I16(0x70))
                SetAuxActionAt40FB40(11);
            if (S16(0x62) == 3 && S16(0x64) == 0) {
                POS = 0.0f;
                POS54 = 16.0f;
                POS5C = 0.8f;
                FLAG = 0;
            }
            break;'''
    blocks={6:block6}
    for action,value,method in ((7,9,'SetNativeActionAt40FAC0'),
                                (8,13,'SetAuxActionAt40FB40')):
        blocks[action]=start(action)+f'''            if (GetNativeActionAt40FA30() == I16(0x70))
                {method}({value});
            if (S16(0x62) == 3 && S16(0x64) == 0) {{
                POS = {'5.5f' if action==7 else '-5.5f'};
                POS54 = 16.0f;
                POS5C = 0.8f;
                FLAG = 0;
            }}
            break;'''
    for action,body in blocks.items():
        previous=f'case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(base.count(previous)==1,f'native script diagnostic action {action} not unique')
        base=base.replace(previous,body)
    need(all(base.count(f'case 0x{x:X}:')==1 for x in (6,7,8)),
         'game script original source labels duplicated/missing')
    return base

def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss005214B0-script-stages.cpp'
    obj=OUT/'Boss005214B0-script-stages.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                        text=True,capture_output=True,cwd=ROOT,env=env,timeout=120)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'native-profile source C++ compile failed: {proc.stderr}')
    return obj

def candidate_three(reader,decoder,obj,boss,real):
    code,refs=reader.object_function(obj,
              f'?Advance@FighterSwitchF565_{TAG}@@QAEXXZ')
    allins=[]
    for x in decoder.disasm(code,0):
        allins.append(x)
        if x.mnemonic=='ret':break
    need(allins and allins[-1].mnemonic=='ret','source whole actor switch missing RET')
    ret=allins[-1].address+allins[-1].size
    need(len(code)-ret==boss['postret_size'],
         'whole original after-RET native switch DATA shape differs')
    records=sorted((r for r in refs if ret+24<=r['offset']<ret+40),
                   key=lambda r:r['offset'])
    need(len(records)==4 and all(r['offset']==ret+24+4*i
            and r['type']=='DIR32' and r['local_symbol_offset'] is not None
            for i,r in enumerate(records)),
         'candidate native first table 6/7/8/9 original physical COFF references absent')
    places=[r['local_symbol_offset'] for r in records]
    need(places==sorted(set(places)) and 0<=places[0]<places[-1]<ret,
         'native C++ script-state case boundaries invalid')
    result=[]
    for index,original in enumerate(real):
        start,end=places[index:index+2]
        cand=list(decoder.disasm(code[start:end],start))
        need(len(cand)==len(original) and
             sum(i.size for i in cand)==sum(i.size for i in original),
             'candidate case original byte/insn entire extent differs')
        result.append(cand)
    return code,refs,allins,ret,result

def verify_typed_fields(native,candidate,refs,case):
    a,b=candidate[0].address,candidate[-1].address+candidate[-1].size
    physical=[r for r in refs if a<=r['offset']<b]
    result=[]
    for ordinal,x in enumerate(native):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            key=int(x.op_str,16)
        elif x.mnemonic=='fcomp' and x.op_str.startswith('dword ptr [0x'):
            key=int(x.op_str.split('[',1)[1].split(']',1)[0],16)
        else:continue
        need(key in TYPED,'unknown original state COFF call/global address')
        kind,source=TYPED[key]
        probe=candidate[ordinal]
        need(x.mnemonic==probe.mnemonic,'original call/global instruction ordinal changed')
        reloc=[r for r in physical if probe.address<=r['offset']<probe.address+probe.size]
        need(len(reloc)==1 and reloc[0]['type']==kind
             and source in reloc[0]['symbol'],
             f'original scripted case {case} COFF ref mismatch at instruction {ordinal}')
        result.append((ordinal,kind,key))
    expected=9 if case==6 else 7
    need(len(result)==len(physical)==expected,
         'real native scripted case COFF field count changed')
    return len(result)

def main():
    reader=module('f565_reader',ROOT/'scripts/compare-coff-function.py')
    action=module('f565_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    opening=module('f565_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    switch=module('f565_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f565_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f565_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    core=module('f565_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads(PINNED.read_text())['bosses'] if b['address']==ADDR)
    report,mapped=action.report_boss(reader,pe,decoder,boss)
    real=whole_original_cases(reader,pe,decoder,boss,core)
    source=source_for(reader,pe,decoder,boss,report,mapped,opening,switch,zero,one)
    obj=compile_one(source)
    code,refs,allins,ret,candidates=candidate_three(reader,decoder,obj,boss,real)
    total=0
    for case,(native,candidate) in enumerate(zip(real,candidates),start=6):
        core.compare_grammar(native,candidate)
        need(all(x.size==y.size for x,y in zip(native,candidate)),
             f'original scripted case {case} native instruction lengths differ')
        total+=verify_typed_fields(native,candidate,refs,case)
    need(total==23,'three real native script-state cases require 9+7+7 COFF fields')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,reader,
                                                   switch,allins,code,refs,ret)
    summary={'boss':f'0x{ADDR:08X}','original_whole_CODE_unaccepted':boss['size'],
             'native_case_instructions':[len(x) for x in real],
             'native_case_CODE_bytes':[sum(i.size for i in x) for x in real],
             'authentic_native_COFF_case_fields':total,
             'case6_original_extra_action':[5,11],
             'case7_native_action':9,'case8_native_action':13,
             'stage_motion_positions':['0.0f','5.5f','-5.5f'],
             'original_stage_velocity':'16.0f',
             'original_stage_speed':'0.8f',
             'whole_original_switch_DWORD_COFF_fields':dense,
             'original_sparse_index_bytes':sparse,
             'original_postret_DATA_shape':len(code)-ret}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(f'{ADDR:#010x}: complete original {boss["size"]} CODE, scripted action6/7/8 '
          f'96+83+83 original native x86 GPR/x87/branch instructions; '
          f'331+290+290 actual native internal CODE bytes; '
          f'{total}/23 true physical call/global COFF refs, '
          f'{dense} native switch DWORD fields, {sparse} original sparse bytes')
    print('Only one affected normal VC7.1 C++ source compiled; no giant whole/split '
          'CODE/DATA exact credit, no all-unit replay')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original scripted fighter source verifier failed:',exc,file=sys.stderr)
        raise SystemExit(1)
