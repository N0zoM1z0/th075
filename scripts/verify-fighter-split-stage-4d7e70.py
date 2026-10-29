#!/usr/bin/env python3
"""F562: recover all 102/115/102-insn action6/7/8 cases in 004D7E70.

Verify complete original giant CODE SHA/physical post-RET DATA from the
Japanese target before building exactly one new VC7.1 natural C++ switch
probe. Distinguish extra-stage callback only in action7, native actor
virtual-call register roles and character-specific float policy. Other
case labels remain diagnostic stores, not reconstructed game behavior.
NO cropped subfunction exact credit and NO full all-unit cold replay.
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
OUT=ROOT/'.analysis/f562-split-stage-source'
ADDR=0x004D7E70
TAG='Boss004D7E70'


def need(ok,message):
    if not ok:raise ValueError(message)


def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,
         f'missing independently original-backed source helper: {path}')
    obj=importlib.util.module_from_spec(spec)
    sys.modules[tag]=obj
    spec.loader.exec_module(obj)
    return obj


def native_cases(reader,original,decoder,boss,core):
    table=boss['tables'][0]
    need(boss['address']==ADDR and boss['size']==43601 and boss['postret_size']==969
         and boss['jump_count']==7 and table['slots']==11 and table['map_addr'] is None,
         'the complete original 43K native fighter/switch extent drifted')
    physical=reader.pe_bytes_at(original,table['dense_addr']+24,16)
    entry=[int.from_bytes(physical[i:i+4],'little') for i in (0,4,8,12)]
    need(entry==sorted(set(entry)) and all(boss['address']<x<boss['address']+boss['size'] for x in entry),
         'native original first-switch 6/7/8/9 boundaries invalid')
    bodies=[]
    for k,want in enumerate((102,115,102)):
        start,end=entry[k:k+2]
        code=reader.pe_bytes_at(original,start,end-start)
        ins=list(decoder.disasm(code,start))
        need(len(ins)==want and end-start==(393 if k==1 else 352)
             and ins[0].address==start and ins[-1].address+ins[-1].size==end,
             'original whole action 6/7/8 case not contiguous complete x86 CODE')
        need(ins[10].mnemonic=='cmp' and
             ins[10].op_str.endswith(', '+str((3,5,4)[k]))
             and ins[16].mnemonic=='push' and
             ins[16].op_str==('0xcc','0xcd','0xce')[k],
             'native per-action byte guard or original callback argument differs')
        need(not any(x.mnemonic=='mov' and 'byte ptr [' in x.op_str
             and '+ 0x3ac]' in x.op_str for x in ins),
             'native fighter case unexpectedly writes FLAG during stage initialization')
        need(ins[-2].mnemonic=='call' and
             ins[-2].op_str==('dword ptr [edx]' if k else 'dword ptr [eax]'),
             'original virtual actor vtable call/register not reproduced')
        calls=[(i,x.op_str) for i,x in enumerate(ins) if x.mnemonic=='call' and x.op_str.startswith('0x')]
        expected=[(18,'0x40fac0'),(29,'0x453e20'),(52,'0x40fac0'),(56,'0x453e20')]
        if k==1:expected.append((70,'0x40fb40'))
        need(calls==expected,'original actual call ordinal/target sequence differs')
        if k==1:
            need(ins[60].mnemonic=='cmp' and ins[60].op_str.endswith(', 4')
                 and ins[64].mnemonic=='fcomp' and ins[64].op_str=='dword ptr [0x657d14]'
                 and ins[68].mnemonic=='push' and ins[68].op_str=='5',
                 'original action7 alone must perform true staged x87 auxiliary call')
            stage_ordinal=91;data_ord=(94,96,98)
        else:
            stage_ordinal=78;data_ord=(81,83,85)
        need(ins[stage_ordinal].mnemonic=='cmp'
             and ins[stage_ordinal].op_str.endswith(', 2'),
             'native stage-two motion transition unexpectedly changed')
        positions=[]
        for idx,field in zip(data_ord,('0x50','0x54','0x5c')):
            x=ins[idx]
            need(x.mnemonic=='mov' and '+ '+field+']' in x.op_str,
                 f'original native motion store at instruction {idx} differs')
            positions.append(int(x.op_str.rsplit(', ',1)[-1],0))
        expected_pos=(0x00000000,0x40A00000,0xC0A00000)[k]
        need(positions[0]==expected_pos and positions[1:]==[0x41700000,0x3F266666],
             'original native position / per-character motion floats changed')
        bodies.append(ins)
    return bodies


def source_for(core,opening,switch,zero,one,
               reader,target,decoder,boss,report,mapped,bodies):
    actual_velocity=core.literal_float(0x41700000)
    actual_speed=core.literal_float(0x3F266666)
    need((actual_velocity,actual_speed)==('15.0f','0.65f'),
         'native source float literal cannot be faithfully represented')
    base=core.generate_source(TAG,2,[actual_velocity,actual_speed],report,mapped,
                              opening,switch,zero,one,reader,target,decoder,boss)
    first='case 0x6:';after='case 0x7: g_FighterProbeMarker = 8; break;'
    last='case 0x8: g_FighterProbeMarker = 9; break;'
    need(base.count(first)==base.count(after)==base.count(last)==1,
         'native-backed source generator no longer has original first cases')
    case6=base[base.index(first):base.index(after)]
    need(case6.count('U8(0x511) == 3')==1 and
         case6.count('SetNativeActionAt40FAC0(0xCC)')==1 and
         case6.count('                    FLAG = 0;')==1,
         'earlier native source contains unexpected flag/byte state')
    case6=case6.replace('                    FLAG = 0;\n','')
    need('FLAG = 0;' not in case6,'new source would incorrectly write native-absent flag')
    case7=(case6.replace('case 0x6:','case 0x7:',1)
           .replace('U8(0x511) == 3','U8(0x511) == 5')
           .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCD)')
           .replace('POS = 0.0f;','POS = 5.0f;'))
    extra='''            if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(5);
'''
    increase='            ++S16(0x64);'
    need(case7.count(increase)==1,
         'real frame counter increment not unique in original source')
    case7=case7.replace(increase,extra+increase)
    case8=(case6.replace('case 0x6:','case 0x8:',1)
           .replace('U8(0x511) == 3','U8(0x511) == 4')
           .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCE)')
           .replace('POS = 0.0f;','POS = -5.0f;'))
    need('FLAG = 0;' not in case6+case7+case8
         and case7.count('SetAuxActionAt40FB40(5)')==1
         and 'SetAuxActionAt40FB40' not in case6+case8,
         'source incorrectly duplicates native flag/auxiliary original operations')
    start=base.index(first)
    end=base.index(after)+len(after)
    src=base[:start]+case6+case7.rstrip()+'\n'+case8.rstrip()+base[end:]
    need(src.count(last)==1,'original action-eight diagnostic marker unexpectedly absent')
    src=src.replace(last,'')
    need(src.count('case 0x6:')==src.count('case 0x7:')==src.count('case 0x8:')==1,
         'native compiler would generate incorrect number of action labels')
    decl='void SetNativeActionAt40FAC0(int);'
    need(src.count(decl)==1,'original actor method declarations missing')
    src=src.replace(decl,decl+' void SetAuxActionAt40FB40(int);')
    glob='extern float g_ThresholdAt0065782C;'
    need(src.count(glob)==1,'native x87 original threshold missing')
    src=src.replace(glob,glob+'\nextern float g_ExtraThresholdAt00657D14;')
    old=f'FighterSwitchF548_{TAG}'
    need(src.count(old)>=2,'native source class ABI unexpectedly changed')
    return src.replace(old,f'FighterSwitchF562_{TAG}')


def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss004D7E70-split-stage.cpp'
    obj=OUT/'Boss004D7E70-split-stage.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                           '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                          cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,f'original profile VC7.1 selected-only source failed: {result.stderr}')
    return obj


def candidate_three(reader,decoder,obj,boss):
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF562_{TAG}@@QAEXXZ')
    allins=[]
    for ins in decoder.disasm(code,0):
        allins.append(ins)
        if ins.mnemonic=='ret':break
    need(allins and allins[-1].mnemonic=='ret','generated entire switch source normal RET absent')
    end=allins[-1].address+allins[-1].size
    need(len(code)-end==boss['postret_size']==969,
         'native whole after-RET physical switch DATA extent differs')
    rows=sorted((r for r in refs if end+24<=r['offset']<end+40),key=lambda r:r['offset'])
    need(len(rows)==4 and all(r['offset']==end+i*4+24 and r['type']=='DIR32'
         and r['local_symbol_offset'] is not None for i,r in enumerate(rows)),
         'native original first switch 6/7/8/9 physical COFF slots absent')
    positions=[r['local_symbol_offset'] for r in rows]
    need(positions==sorted(set(positions)) and 0<=positions[0]<positions[-1]<end,
         'candidate native first-switch case offsets overlap')
    bodies=[]
    for k,size in enumerate((102,115,102)):
        start,finish=positions[k:k+2]
        ins=list(decoder.disasm(code[start:finish],start))
        need(len(ins)==size and sum(i.size for i in ins)==(393 if k==1 else 352),
             f'compiled C++ did not emit the entire original case {6+k} size/insns')
        bodies.append(ins)
    return code,refs,allins,end,bodies


def verify_short_core_refs(original,candidate,refs,core,case):
    """Six real native call/global COFF fields; dynamic 102-insn virtual call."""
    need(len(original)==len(candidate)==102,
         'native action6/8 no-FLAG case is not 102 whole instructions')
    for idx,(mnemonic,kind,address,symbol) in core.ORIGINAL_REFS.items():
        a,b=original[idx],candidate[idx]
        need(a.mnemonic==b.mnemonic==mnemonic,
             f'actual native call/global ordinal {idx} changed')
        expected=f'0x{address:x}' if kind=='REL32' else f'dword ptr [0x{address:x}]'
        need(a.op_str==expected,'original whole-PE call or float constant changed')
        physical=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(physical)==1 and physical[0]['type']==kind
             and symbol in physical[0]['symbol'],
             f'candidate has no genuine original COFF typed field at {idx}')
    start,end=candidate[0].address,candidate[-1].address+candidate[-1].size
    need(len([r for r in refs if start<=r['offset']<end])==6,
         'extra/absent COFF relocation in native 102-insn core case')
    expected_call='dword ptr [eax]' if case==6 else 'dword ptr [edx]'
    need(original[-2].mnemonic==candidate[-2].mnemonic=='call'
         and original[-2].op_str==candidate[-2].op_str==expected_call,
         'per-fighter native actual virtual method dispatch uses wrong register')
    return 6


def main():
    reader=module('f562_reader',ROOT/'scripts/compare-coff-function.py')
    action=module('f562_action',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f562_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f562_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f562_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    opening=module('f562_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    core=module('f562_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    extra=module('f562_extra',ROOT/'scripts/verify-fighter-extra-stage-action-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads(PINNED.read_text())['bosses'] if b['address']==ADDR)
    report,mapped=action.report_boss(reader,pe,decoder,boss)
    originals=native_cases(reader,pe,decoder,boss,core)
    src=source_for(core,opening,switch,zero,one,reader,pe,decoder,boss,report,mapped,originals)
    obj=compile_one(src)
    code,refs,allins,postret,bodies=candidate_three(reader,decoder,obj,boss)
    fields=0
    for k,(native,candidate) in enumerate(zip(originals,bodies)):
        core.compare_grammar(native,candidate)
        need(all(x.size==y.size for x,y in zip(native,candidate)),
             f'native case {6+k} physical instruction widths changed')
        if k==1:
            fields+=extra.verify_physical_fields(native,candidate,refs)
        else:
            fields+=verify_short_core_refs(native,candidate,refs,core,6+k)
    need(fields==20,'native 102+115+102 fighter policy requires 6+8+6 real COFF fields')
    slots,spbytes,maps=zero.verify_physical_tables(boss,report,pe,reader,switch,
                                                  allins,code,refs,postret)
    outcome={'boss':f'0x{ADDR:08X}','whole_original_CODE':boss['size'],
             'native_case_bytes':[352,393,352],
             'native_case_instructions':[102,115,102],
             'full_real_call_and_float_COFF_fields':fields,
             'per_character_stage':2,'velocity':'15.0f','speed':'0.65f',
             'original_position_values':['0.0f','5.0f','-5.0f'],
             'extra_stage_callback_only_in_action7':True,
             'original_virtual_call_registers':['eax','edx','edx'],
             'native_switch_DWORD_COFF_fields':slots,
             'literal_native_sparse_bytes':spbytes,
             'native_postret_DATA_shape':len(code)-postret}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(outcome,indent=2)+'\n')
    print(f'{ADDR:#010x}: complete original {boss["size"]} CODE bytes; '
          f'action 6/7/8 = 102+115+102 native instructions, '
          f'352+393+352 full original CODE bytes, {fields}/20 actual COFF fields, '
          f'aux stage `0040FB40(5)` ONLY in action7, vtable calling forms eax/edx/edx; '
          f'{slots} native-style switch DWORD refs, {spbytes} byte-identical sparse bytes')
    print('One new VC7.1 C++ probe freshly compiled; whole giant NOT exact, '
          'no source subfunction credit or all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original 004D7E70 actor source original-check failed:',exc,file=sys.stderr)
        raise SystemExit(1)
