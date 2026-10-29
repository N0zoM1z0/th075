#!/usr/bin/env python3
"""Fresh VC7.1 native action-seven C++ probes in three giant fighters.

Uses original whole-boss CODE SHA, physical native case 6/7/8 jump slots,
actual x87/flag/member and character-specific float constants. Rebuild only
three selected small source TUs; all other cases remain test-only markers.
Never credits subranges as standalone functions or runs an all-unit replay.
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
OUT=ROOT/'.analysis/f551-action-seven-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
SELECTED={0x0045DD70:'Reimu',0x0058AF60:'Boss0058AF60',0x005D73C0:'Boss005D73C0'}


def need(ok,why):
    if not ok: raise ValueError(why)


def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,f'missing source/PE reader {path}')
    m=importlib.util.module_from_spec(spec)
    sys.modules[tag]=m
    spec.loader.exec_module(m)
    return m


def native_seven(reader,target,decoder,boss,six_case):
    first=boss['tables'][0]
    need(first['slots']==11 and first['map_addr'] is None and boss['jump_count'] in (6,7),
         'not the original multi-table native fighter')
    actual=reader.pe_bytes_at(target,first['dense_addr']+28,8)
    start,end=[int.from_bytes(actual[k:k+4],'little') for k in (0,4)]
    need(boss['address']<start<end<boss['address']+boss['size'],
         'native action 7 case boundaries outside original complete giant')
    real=list(decoder.disasm(reader.pe_bytes_at(target,start,end-start),start))
    need(len(real)==len(six_case)==104 and end-start==362 and
         real[0].address==start and real[-1].address+real[-1].size==end,
         'not the independently original complete 362-byte action 7')
    # The original action 6 and 7 are genuinely the same 104-instruction
    # native policy with precisely three source-semantic differences. Do
    # not generalize this to eight other fighters whose policy differs.
    need(all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(six_case,real)),
         'original action six/seven instruction sequence or length differs')
    changed=[]
    for i,(a,b) in enumerate(zip(six_case,real)):
        if a.mnemonic.startswith('j') and a.op_str.startswith('0x'):
            src=int(a.op_str,16)
            dst=int(b.op_str,16)
            src_inside=(six_case[0].address<=src<=six_case[-1].address)
            dst_inside=(real[0].address<=dst<=real[-1].address)
            need(src_inside==dst_inside and
                 ((src-six_case[0].address)==(dst-real[0].address)
                  if src_inside else src==dst),
                 f'original action 7 branch target differs at instruction {i}')
            continue
        if a.op_str!=b.op_str:
            changed.append(i)
    need(changed==[10,16,81],f'native actions 6 and 7 differ outside three real semantic sites: {changed}')
    need(real[10].mnemonic=='cmp' and real[10].op_str.endswith(', 5')
         and six_case[10].op_str.endswith(', 3'),
         'wrong original action7 byte state threshold')
    need(real[16].mnemonic=='push' and real[16].op_str=='0xcd'
         and six_case[16].op_str=='0xcc',
         'wrong original action7 native state transition argument')
    need(real[81].mnemonic=='mov' and '+ 0x50]' in real[81].op_str
         and six_case[81].mnemonic=='mov' and six_case[81].op_str.endswith(', 0'),
         'wrong original action7 native float position initializer')
    return real,int(real[81].op_str.split(', ')[-1],16)


def generate_source(tag,source6,real7,position,six):
    old=f'FighterSwitchF548_{tag}'
    need(source6.count(old)>=2,'previous full native action6 owner model changed')
    result=source6.replace(old,f'FighterSwitchF551_{tag}')
    marker='case 0x7: g_FighterProbeMarker = 8; break;'
    start='case 0x6:'
    need(result.count(marker)==1 and result.count(start)==1,
         'unique original case six/seven source labels expected')
    action6=result[result.index(start):result.index(marker)]
    need(action6.count('U8(0x511) == 3')==1
         and action6.count('SetNativeActionAt40FAC0(0xCC)')==1
         and action6.count('POS = 0.0f;')==1,
         'genuine action-six source has changed, cannot clone with three verified differences')
    f=six.literal_float(position)
    action7=(action6.replace(start,'case 0x7:',1)
             .replace('U8(0x511) == 3','U8(0x511) == 5')
             .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCD)')
             .replace('POS = 0.0f;','POS = '+f+';'))
    need(action7.count('SetNativeActionAt40FAC0(0xCD)')==1,
         'candidate real case-seven source did not include original native transition')
    return result.replace(marker,action7.rstrip()),f


def compile_one(tag,src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}-action-seven.cpp';obj=OUT/f'{tag}-action-seven.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     text=True,capture_output=True,cwd=ROOT,env=env,timeout=120)
    (OUT/f'{tag}-compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,f'{tag}: native VC7.1 seven-action source failed: {p.stderr}')
    return obj


def compiled_six_and_seven(reader,decoder,obj,tag,boss):
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF551_{tag}@@QAEXXZ')
    inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret','candidate native function has no final RET')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size'],
         'native C++ source original full after-RET DATA layout changed')
    fields=sorted((r for r in refs if ret+24<=r['offset']<ret+36),key=lambda r:r['offset'])
    need(len(fields)==3 and all(r['type']=='DIR32' and r['offset']==ret+24+4*k
         and r['local_symbol_offset'] is not None for k,r in enumerate(fields)),
         'original case 6/7/8 physical COFF jump destinations missing')
    indexes=[r['local_symbol_offset'] for r in fields]
    need(indexes==sorted(set(indexes)) and 0<=indexes[0]<indexes[-1]<=ret,
         'original candidate action 6/7 case spans overlap or escape CODE')
    cases=[]
    for k in (0,1):
        s,e=indexes[k:k+2]
        block=list(decoder.disasm(code[s:e],s))
        need(len(block)==104 and sum(x.size for x in block)==362,
             'candidate action six/seven natural C++ not original complete 104 instructions/362 bytes')
        cases.append(block)
    return code,refs,inst,ret,cases


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='One original PE address, or Reimu; defaults to the three native 104-insn fighters')
    args=parser.parse_args()
    reader=module('f551_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f551_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f551_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f551_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f551_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    six=module('f551_six',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    action6=module('f551_action6',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    manifest={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    addresses=list(SELECTED)
    if args.boss:
        selected=0x0045DD70 if args.boss.lower()=='reimu' else int(args.boss,0)
        need(selected in SELECTED,'original fighter action7 is not in the physical 104-instruction cohort')
        addresses=[selected]
    rows=[]
    for addr in addresses:
        boss=manifest[addr];tag=SELECTED[addr]
        # Original full 43K-61K giant SHA and complete post-RET native DATA
        # verified independently, never copied into generated C++ source.
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        old,stage,floats=action6.native_case(reader,pe,decoder,boss)
        native,position=native_seven(reader,pe,decoder,boss,old)
        base=action6.generate_source(tag,stage,floats,report,mapped,six,switch,zero,one,
                                     reader,pe,decoder,boss)
        cpp,position_float=generate_source(tag,base,native,position,action6)
        obj=compile_one(tag,cpp)
        code,refs,whole_ins,ret,(c6,c7)=compiled_six_and_seven(reader,decoder,obj,tag,boss)
        action6.compare_grammar(old,c6)
        action6.compare_grammar(native,c7)
        ref6=action6.verify_fields(old,c6,refs)
        ref7=action6.verify_fields(native,c7,refs)
        need(len(ref6)==len(ref7)==6,'missing one genuine original native action-six/seven call/global field')
        slots,index,maps=zero.verify_physical_tables(boss,report,pe,reader,switch,
                                                     whole_ins,code,refs,ret)
        row={'boss':f'0x{addr:08X}','whole_original_CODE':boss['size'],
             'action6_native_CODE':362,'action7_native_CODE':362,
             'case_instructions_each':104,'genuine_COFF_call_data_fields':12,
             'state_check_value':5,'native_transition_argument':205,
             'native_action7_position':position_float,'original_action6_stage':stage,
             'original_virtual_call':native[102].op_str,
             'whole_table_DWORD_COFF_fields':slots,'literal_original_sparse_bytes':index,
             'complete_postret_DATA_shape':len(code)-ret}
        rows.append(row)
        print(f'{addr:#010x}: original native action7 362/362 CODE length, '
              f'104/104 GPR/x87/branch instructions, 6/6 authentic COFF fields, '
              f'virtual {native[102].op_str}; position={position_float}, '
              f'companion action6 104/104 still verified, {slots} native table refs, '
              f'{index} byte-identical sparse indexes',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    name=('summary.json' if args.boss is None else f'summary-{addresses[0]:08X}.json')
    (OUT/name).write_text(json.dumps(rows,indent=2)+'\n')
    print(f'{len(rows)}/{len(addresses)} original giant contexts freshly compiled; '
          'no independent case function exact credit, no all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original action seven native C++ verifier failed:',exc,file=sys.stderr)
        raise SystemExit(1)
