#!/usr/bin/env python3
"""F558: complete 117/117/104-insn action 6/7/8 in two giant fighters.

Original entire 50K/82K native CODE SHA, whole physical switch DATA and
actual C++ field assignment order are verified before compiling selected
small VC7.1 C++ prototypes. Cases remain part of *unmatched giant* CODE;
never credit partial inner functions or run all-unit cold replay.
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
OUT=ROOT/'.analysis/f558-extra-stage-eight'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
FIGHTERS={0x00486550:'Boss00486550',0x004AC040:'CharacterMove'}


def need(ok,message):
    if not ok:raise ValueError(message)


def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,f'missing original native validator {path}')
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m)
    return m


def original_eight(reader,pe,decoder,boss,source6,old6):
    table=boss['tables'][0]
    need(table['slots']==11 and table['map_addr'] is None,
         'not original first 11-way native jump table')
    raw=reader.pe_bytes_at(pe,table['dense_addr']+8*4,8)
    start,end=[int.from_bytes(raw[i:i+4],'little') for i in (0,4)]
    need(boss['address']<start<end<boss['address']+boss['size'],
         'original 8-action native CODE not physically contained in whole fighter')
    block=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    need(len(block)==104 and end-start==362 and
         block[0].address==start and block[-1].address+block[-1].size==end,
         'complete native original action8 is not 104 instructions and 362 bytes')
    need(block[10].mnemonic=='cmp' and block[10].op_str.endswith(', 4')
         and block[16].mnemonic=='push' and block[16].op_str=='0xce',
         'original action8 unsigned state trigger / aux callback changed')
    need(block[78].mnemonic=='cmp' and
         int(block[78].op_str.split(', ')[-1],0)==old6[1],
         'per-role native action8 stage differs from original action6')
    real_values=[]
    for k in (81,83,85,87):
        ins=block[k]
        need(ins.mnemonic=='mov' and ins.op_str.startswith(('byte ptr [','dword ptr [')),
             'actual action8 float/flag original store not at native ordinal')
        real_values.append(ins.op_str)
    suffixes=['0x50','0x54','0x5c','0x3ac']
    kinds=[next((field for field in suffixes if '+ '+field+']' in op),None)
           for op in real_values]
    need(set(kinds)==set(suffixes),'original action8 not exactly one position, speed and flag store')
    order=kinds.index('0x3ac')
    need(order in (0,1),'original action8 native FLAG clear placement unexpected')
    need(real_values[order].endswith(', 0'),'original action8 flag store not zero')
    pos=real_values[kinds.index('0x50')]
    need(pos.endswith(', 0xc0800000'),'native action8 position immediate is not -4.0f')
    floats=[]
    for field in ('0x54','0x5c'):
        literal=int(real_values[kinds.index(field)].split(', ')[-1],16)
        floats.append(source6.literal_float(literal))
    need(floats==old6[2], 'original action8 signed float initializers differ from case6')
    need(block[-2].mnemonic=='call' and block[-2].op_str=='dword ptr [edx]',
         'native complete action8 ends in different genuine virtual call')
    return block,order,floats


def generate_source(tag,report,mapped,originals,real8,order,
                    reader,pe,decoder,boss,extra,old,opening,switch,zero,one):
    two=extra.source_for(tag,originals,report,mapped,reader,pe,decoder,boss,
                         old,opening,switch,zero,one)
    sixbase=old.generate_source(tag,originals[0][1],originals[0][2],
                                report,mapped,opening,switch,zero,one,
                                reader,pe,decoder,boss)
    marker='case 0x7: g_FighterProbeMarker = 8; break;'
    need(sixbase.count('case 0x6:')==1 and sixbase.count(marker)==1,
         'old 104-instruction original source case not available')
    orig=sixbase[sixbase.index('case 0x6:'):sixbase.index(marker)]
    need(orig.count('U8(0x511) == 3')==1
         and orig.count('SetNativeActionAt40FAC0(0xCC)')==1
         and orig.count('POS = 0.0f;')==1,
         'native 104-instruction source base unexpectedly changed')
    extra8=(orig.replace('case 0x6:','case 0x8:',1)
                .replace('U8(0x511) == 3','U8(0x511) == 4')
                .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCE)')
                .replace('POS = 0.0f;','POS = -4.0f;'))
    one,two_float=originals[0][2]
    current=f'''                    POS = -4.0f;
                    POS54 = {one};
                    POS5C = {two_float};
                    FLAG = 0;'''
    need(extra8.count(current)==1,'native source has unexpected float initializer order')
    desired=([f'                    FLAG = 0;',
              f'                    POS = -4.0f;',
              f'                    POS54 = {one};',
              f'                    POS5C = {two_float};'] if order==0 else
             [f'                    POS = -4.0f;',
              f'                    FLAG = 0;',
              f'                    POS54 = {one};',
              f'                    POS5C = {two_float};'])
    extra8=extra8.replace(current,'\n'.join(desired))
    label='case 0x8: g_FighterProbeMarker = 9; break;'
    need(two.count(label)==1,'previous true 117-instruction source action case not preserved')
    result=two.replace(label,extra8.rstrip())
    old_name=f'FighterSwitchF556_{tag}'
    need(result.count(old_name)>=2,'original F556 fighter source owner replaced')
    return result.replace(old_name,f'FighterSwitchF558_{tag}')


def compile_one(tag,source):
    OUT.mkdir(parents=True,exist_ok=True)
    path=OUT/f'{tag}-case6-7-8.cpp';obj=OUT/f'{tag}-case6-7-8.obj'
    path.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(path),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     cwd=ROOT,env=env,text=True,capture_output=True,timeout=120)
    (OUT/f'{tag}-compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,f'{tag}: selected VC7.1 native source compile failed: {p.stderr}')
    return obj


def candidate_three(reader,decoder,obj,tag,boss):
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF558_{tag}@@QAEXXZ')
    inst=[]
    for i in decoder.disasm(code,0):
        inst.append(i)
        if i.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret','full source-derived fighter switch missing normal RET')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],'native post-RET original dense/sparse DATA extent changed')
    items=sorted((r for r in refs if ret+24<=r['offset']<ret+40),key=lambda r:r['offset'])
    need(len(items)==4 and all(r['type']=='DIR32' and r['offset']==ret+24+4*k
         and r['local_symbol_offset'] is not None for k,r in enumerate(items)),
         'original case6/7/8/9 physical COFF DWORD destinations missing')
    positions=[r['local_symbol_offset'] for r in items]
    need(positions==sorted(set(positions)) and 0<=positions[0]<positions[-1]<ret,
         'native compiler repeated/overlapping action6/7/8 labels')
    cases=[]
    for k,expected in enumerate((117,117,104)):
        start,end=positions[k:k+2]
        decoded=list(decoder.disasm(code[start:end],start))
        need(len(decoded)==expected and sum(i.size for i in decoded)==(403 if k<2 else 362),
             'source C++ did not reproduce complete original whole action-case body')
        cases.append(decoded)
    return code,refs,inst,ret,cases


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='One original 0x00486550/0x004AC040 or CharacterMove; default both')
    args=parser.parse_args()
    reader=module('f558_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f558_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f558_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f558_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f558_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    opening=module('f558_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    old=module('f558_old',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    extra=module('f558_extra',ROOT/'scripts/verify-fighter-extra-stage-action-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    originals={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    need(sum(originals[a]['size'] for a in FIGHTERS)==133531,
         'whole original fighter CODE cohort changed')
    selected=list(FIGHTERS)
    if args.boss:
        token=args.boss.lower()
        addr=0x004AC040 if token=='charactermove' else int(args.boss,0)
        need(addr in FIGHTERS,'not a registered native 117/104 action family original')
        selected=[addr]
    results=[]
    for addr in selected:
        boss=originals[addr];tag=FIGHTERS[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        prev=[extra.native_case(reader,pe,decoder,boss,k,old) for k in (6,7)]
        real,order,floats=original_eight(reader,pe,decoder,boss,old,prev[0])
        source=generate_source(tag,report,mapped,prev,real,order,
                               reader,pe,decoder,boss,extra,old,opening,switch,zero,one)
        obj=compile_one(tag,source)
        code,refs,ins,ret,cases=candidate_three(reader,decoder,obj,tag,boss)
        actual=0
        for k,(original,candidate) in enumerate(zip((prev[0][0],prev[1][0],real),cases)):
            old.compare_grammar(original,candidate)
            need(all(u.size==v.size for u,v in zip(original,candidate)),
                 f'{addr:08X} case {6+k}: actual native original operand widths differ')
            actual+=(extra.verify_physical_fields(original,candidate,refs) if k<2
                     else old.verify_fields(original,candidate,refs).__len__())
        need(actual==22,'three full original cases require exactly 8+8+6 authentic COFF fields')
        dense,indexbytes,maps=zero.verify_physical_tables(boss,report,pe,reader,switch,ins,code,refs,ret)
        row={'boss':f'0x{addr:08X}','whole_original_CODE':boss['size'],
             'native_action6_7_bytes_each':403,'native_action8_bytes':362,
             'case_instructions':[117,117,104],
             'actual_case_call_and_float_COFF_fields':actual,
             'native_action8_stage':prev[0][1],
             'native_action8_float_initializers':floats,
             'native_action8_flag_store_order':('before position' if order==0 else 'between position and velocity'),
             'original_switch_DWORD_COFF_fields':dense,'native_sparse_index_bytes':indexbytes,
             'native_postret_DATA_shape':len(code)-ret}
        results.append(row)
        print(f'{addr:#010x}: 117/117,117/117,104/104 actual x86 GPR/x87/branch instructions; '
              f'403+403+362 original CODE bytes matched in natural C++ geometry, '
              f'{actual}/22 physical typed COFF fields, native action8 FLAG order={row["native_action8_flag_store_order"]}; '
              f'{dense} native switch DWORD refs, {indexbytes} literal original sparse bytes',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    file='summary.json' if args.boss is None else f'summary-{selected[0]:08X}.json'
    (OUT/file).write_text(json.dumps(results,indent=2)+'\n')
    print(f'{len(results)}/{len(selected)} complete original giant contexts recompiled; '
          'NO accepted original whole/split CODE, no all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('TH075 original extended action8 source validation failed:',e,file=sys.stderr)
        raise SystemExit(1)
