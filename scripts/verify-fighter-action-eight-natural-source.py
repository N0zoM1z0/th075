#!/usr/bin/env python3
"""Native action eight in three complete original giant-fighter contexts.

Regenerate natural C++ with complete actual cases 6, 7 and 8. Native case
8 differs in three role-specific literals from case 6, and one fighter
also genuinely lacks a state-flag clear. Compare full native case bounds,
all original call/global COFF references and complete switch DATA.
This is NOT full giant-function CODE exactness or an all-unit cold replay.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f553-action-eight-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
SELECTED={0x0045DD70:'Reimu',0x0058AF60:'Boss0058AF60',0x005D73C0:'Boss005D73C0'}


def require(ok,explanation):
    if not ok:raise ValueError(explanation)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    require(spec is not None and spec.loader is not None,f'missing native verifier: {path}')
    result=importlib.util.module_from_spec(spec)
    sys.modules[name]=result
    spec.loader.exec_module(result)
    return result


def real_eight(reader,target,decoder,boss):
    tab=boss['tables'][0]
    require(tab['slots']==11 and tab['map_addr'] is None and boss['jump_count'] in (6,7),
            'original first action switch is not the native 11-slot direct table')
    fields=reader.pe_bytes_at(target,tab['dense_addr']+8*4,8)
    first,last=[int.from_bytes(fields[k:k+4],'little') for k in (0,4)]
    require(boss['address']<first<last<boss['address']+boss['size'],
            'entire original case8 lies outside verified whole original boss')
    ins=list(decoder.disasm(reader.pe_bytes_at(target,first,last-first),first))
    require(len(ins) in (102,104) and ins[0].address==first
            and ins[-1].address+ins[-1].size==last,
            'original case-eight native contiguous instructions/bounds changed')
    require(last-first==(352 if len(ins)==102 else 362),
            'original case-eight native CODE byte count/word size changed')
    require(ins[10].mnemonic=='cmp' and ins[10].op_str.endswith(', 4')
            and ins[16].mnemonic=='push' and ins[16].op_str=='0xce',
            'original native case-eight state trigger/transition argument changed')
    store=ins[81]
    require(store.mnemonic=='mov' and '+ 0x50]' in store.op_str,
            'native action-eight float position initializer missing')
    original=float(struct.unpack('<f',int(store.op_str.split(', ')[-1],16).to_bytes(4,'little'))[0])
    require(original==-4.0,'native action-eight original float store is not -4.0f')
    if len(ins)==102:
        require(boss['address']==0x0058AF60,
                'new original fighter unexpectedly omits action-eight flag-clear operation')
        require(ins[87].mnemonic=='movsx' and '+ 0x62' in ins[87].op_str,
                'native two-insn early flag-clear omission is not physically demonstrated')
    else:
        require(ins[87].mnemonic=='mov' and '+ 0x3ac]' in ins[87].op_str,
                'native full 104-insn action-eight flag clear changed')
    return ins,len(ins)==102


def create_source(tag,s7,original,eight_no_clear,six):
    old=f'FighterSwitchF551_{tag}'
    require(s7.count(old)>=2,'prior original-backed action-six/seven source changed')
    src=s7.replace(old,f'FighterSwitchF553_{tag}')
    marker='case 0x8: g_FighterProbeMarker = 9; break;'
    require(src.count(marker)==1 and src.count('case 0x6:')==1 and src.count('case 0x7:')==1,
            'original six/seven/eight switch case labels missing')
    body=src[src.index('case 0x6:'):src.index('case 0x7:')]
    require(body.count('U8(0x511) == 3')==1
            and body.count('SetNativeActionAt40FAC0(0xCC)')==1
            and body.count('POS = 0.0f;')==1,
            'native six source not valid for source-derived original action eight')
    body=(body.replace('case 0x6:','case 0x8:',1)
            .replace('U8(0x511) == 3','U8(0x511) == 4')
            .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCE)')
            .replace('POS = 0.0f;','POS = -4.0f;'))
    if eight_no_clear:
        require(body.count('FLAG = 0;')==1,'the expected optional flag-clear in native source is not unique')
        body=body.replace('                    FLAG = 0;\n','')
        require('FLAG = 0;' not in body,'incorrect extra action-eight flag-clear remains')
    return src.replace(marker,body.rstrip())


def compile_one(tag,src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}-action-eight.cpp';obj=OUT/f'{tag}-action-eight.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     env=env,cwd=ROOT,text=True,capture_output=True,timeout=120)
    (OUT/f'{tag}-compiler.log').write_text(p.stdout+p.stderr)
    require(p.returncode==0,f'{tag}: new source-specific VC7.1 compile failed: {p.stderr}')
    return obj


def candidate_three(reader,decoder,obj,tag,boss):
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF553_{tag}@@QAEXXZ')
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    require(ins and ins[-1].mnemonic=='ret','generated C++ full switch has no RET')
    ret=ins[-1].address+ins[-1].size
    require(len(code)-ret==boss['postret_size'],
            'original fighter post-RET switch DATA shape changed')
    fields=sorted((r for r in refs if ret+24<=r['offset']<ret+40),key=lambda r:r['offset'])
    require(len(fields)==4 and all(r['type']=='DIR32' and
            r['offset']==ret+24+4*k and r['local_symbol_offset'] is not None
            for k,r in enumerate(fields)),
            'generated case6..9 physical COFF targets not independently valid')
    offsets=[r['local_symbol_offset'] for r in fields]
    require(offsets==sorted(set(offsets)) and 0<=offsets[0]<offsets[-1]<=ret,
            'candidate action 6/7/8 source spans overlap or leave original CODE')
    result=[]
    for k in range(3):
        start,end=offsets[k:k+2]
        block=list(decoder.disasm(code[start:end],start))
        require(block and block[0].address==start and
                block[-1].address+block[-1].size==end,
                'candidate native case body not complete contiguous instructions')
        result.append(block)
    return code,refs,ins,ret,result


def six_real_fields(original,candidate,relocations,old):
    require(len(original)==len(candidate), 'native 102/104 action-eight length mismatch')
    for ordinal,(mnemonic,typ,target,source) in old.ORIGINAL_REFS.items():
        a,b=original[ordinal],candidate[ordinal]
        require(a.mnemonic==b.mnemonic==mnemonic,
                f'original action eight COFF instruction {ordinal} moved')
        require(a.op_str==(f'0x{target:x}' if typ=='REL32' else
                 f'dword ptr [0x{target:x}]'),
                 f'original action-eight physical PE callee/global mismatches {ordinal}')
        fields=[r for r in relocations if b.address<=r['offset']<b.address+b.size]
        require(len(fields)==1 and fields[0]['type']==typ and source in fields[0]['symbol'],
                f'candidate real COFF field differs at instruction {ordinal}')
    start,end=candidate[0].address,candidate[-1].address+candidate[-1].size
    require(len([r for r in relocations if start<=r['offset']<end])==6,
            'genuine action8 C++ has extra/missing native COFF fields')
    require(original[-2].mnemonic==candidate[-2].mnemonic=='call'
            and original[-2].op_str==candidate[-2].op_str
            and original[-2].op_str in ('dword ptr [edx]','dword ptr [eax]'),
            'candidate action-eight real virtual dispatch GPR or vtable call changed')
    return 6


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='Rebuild only one native PE address or Reimu; default three 104/102-insn fighters')
    args=parser.parse_args()
    reader=module('f553_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f553_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f553_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f553_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f553_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    six=module('f553_six',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    source6=module('f553_source6',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    source7=module('f553_source7',ROOT/'scripts/verify-fighter-action-seven-natural-source.py')
    target=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    manifest={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    selected=list(SELECTED)
    if args.boss:
        key=0x0045DD70 if args.boss.lower()=='reimu' else int(args.boss,0)
        require(key in SELECTED,'original native fighter is not one of the selected action-eight cohort')
        selected=[key]
    outcome=[]
    for addr in selected:
        boss=manifest[addr];tag=SELECTED[addr]
        # Attest complete original huge function and all native switch DATA.
        report,mapped=actions.report_boss(reader,target,decoder,boss)
        native6,stage,floats=source6.native_case(reader,target,decoder,boss)
        native7,position7=source7.native_seven(reader,target,decoder,boss,native6)
        native8,no_clear=real_eight(reader,target,decoder,boss)
        base6=source6.generate_source(tag,stage,floats,report,mapped,six,switch,zero,one,
                                      reader,target,decoder,boss)
        base7,_=source7.generate_source(tag,base6,native7,position7,source6)
        cpp=create_source(tag,base7,native8,no_clear,source6)
        obj=compile_one(tag,cpp)
        code,refs,whole,postret,candidates=candidate_three(reader,decoder,obj,tag,boss)
        for original,candidate in zip((native6,native7,native8),candidates):
            source6.compare_grammar(original,candidate)
            six_real_fields(original,candidate,refs,source6)
        slots,sparse,maps=zero.verify_physical_tables(boss,report,target,reader,switch,
                                                      whole,code,refs,postret)
        lengths=[sum(x.size for x in ins) for ins in candidates]
        require(lengths==[362,362,352 if no_clear else 362],
             'actual native 102-instruction action-eight variant was lost')
        row={'boss':f'0x{addr:08X}','whole_original_CODE':boss['size'],
             'native_case_six_and_seven_each':362,'native_case_eight_bytes':lengths[2],
             'native_case_eight_instructions':len(native8),
             'original_real_case_COFF_fields':18,'native_case_eight_flag_clear':not no_clear,
             'original_speed_initialization':'-4.0f',
             'original_virtual_call':native8[-2].op_str,
             'whole_original_DWORD_COFF_fields':slots,
             'identical_original_sparse_bytes':sparse,
             'full_native_postret_DATA_shape':len(code)-postret}
        outcome.append(row)
        print(f'{addr:#010x}: new original action8 {len(native8)}/{len(native8)} '
              f'GPR/x87/control instructions and {lengths[2]}/{lengths[2]} CODE length, '
              f'same real virtual {native8[-2].op_str}; flags clear={not no_clear}; '
              f'all three cases 18/18 authentic COFF fields, {slots} native table refs, '
              f'{sparse} original compressed bytes',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    file='summary.json' if args.boss is None else f'summary-{selected[0]:08X}.json'
    (OUT/file).write_text(json.dumps(outcome,indent=2)+'\n')
    print(f'{len(outcome)}/{len(selected)} entire original-fighter contexts locally VC7.1 compiled; '
          'NO accepted full-boss/split CODE or all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as err:
        print('TH075 original action-eight native C++ verification failed:',err,file=sys.stderr)
        raise SystemExit(1)
