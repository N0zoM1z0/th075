#!/usr/bin/env python3
"""F572: authentic first ten action bodies of giant CharacterObject 004EBDA0.

One normal VC7.1 C++ source TU implements seven 3-insn native leaf cases
and three entire 271-insn native actor game cases (0x327..0x329). The
original whole 33,293-byte Japanese TH075 v1.11 function is SHA verified
before the probe compiles. Compare exact per-instruction grammar, original
case bounds, all physical call/global COFF references and original sparse
switch DATA. All OTHER cases remain diagnostic marker stores, NOT true
source. No complete giant/partial-function CODE exact credit and no all-unit
cold replay is performed.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
OUT=ROOT/'.analysis/f572-native-action-family'
MANIFEST=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
ADDRESS=0x004EBDA0
TAG='Boss004EBDA0'
FIRST=0x320
LAST=0x329
FRAME=re.compile(r'\[ebp - (?:0x[0-9a-f]+|\d+)\]')
ABS=re.compile(r'(dword|qword) ptr \[(?:0x[0-9a-f]+|0)\]')
BRANCH=re.compile(r'^0x[0-9a-f]+$')
SYMBOLS={
  0x004F4170:('REL32','ResetAt4F4170'),
  0x0045B830:('REL32','ResetAt45B830'),
  0x00453A70:('REL32','SpawnAt453A70'),
  0x0040FBB0:('REL32','ResetStateAt40FBB0'),
  0x00453D40:('REL32','ModifyAt453D40'),
  0x0040FB70:('REL32','MotionAt40FB70'),
  0x0040FB40:('REL32','SetStateAt40FB40'),
  0x0040FA30:('REL32','GetStateAt40FA30'),
  0x00657850:('DIR32','gFloatAt00657850'),
  0x006590B4:('DIR32','gMulAt006590B4'),
  0x00659738:('DIR32','gAddAt00659738'),
  0x00659730:('DIR32','gMulDoubleAt00659730'),
  0x006583FC:('DIR32','gAddAt006583FC'),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def module(name,p):
    spec=importlib.util.spec_from_file_location(name,p)
    need(spec is not None and spec.loader is not None,f'missing genuine source reader {p}')
    obj=importlib.util.module_from_spec(spec)
    sys.modules[name]=obj
    spec.loader.exec_module(obj)
    return obj


def typed_fields(original,compiled,relocations,case):
    start=compiled[0].address
    end=compiled[-1].address+compiled[-1].size
    source=[r for r in relocations if start<=r['offset']<end]
    actual=[]
    for ordinal,x in enumerate(original):
        if x.mnemonic=='call' and BRANCH.fullmatch(x.op_str):
            address=int(x.op_str,16)
            kind='REL32'
        elif x.mnemonic.startswith('f') and ABS.fullmatch(x.op_str):
            address=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
            kind='DIR32'
        else:
            continue
        need(address in SYMBOLS,
             f'original case {case:#x}, instruction {ordinal}: new unknown physical call/global {address:#x}')
        want_type, symbol=SYMBOLS[address]
        need(kind==want_type,f'original source target field type changed at {ordinal}')
        y=compiled[ordinal]
        need(x.mnemonic==y.mnemonic,
             f'VC7 case {case:#x} original call/global ordinal {ordinal} moved')
        matches=[r for r in source if y.address<=r['offset']<y.address+y.size]
        need(len(matches)==1,
             f'VC7 C++ source missing one genuine physical COFF field at {case:#x}:{ordinal}')
        r=matches[0]
        want_symbol=symbol
        if address==0x00453A70 and ordinal==122:
            want_symbol='SpawnComputedAt453A70'
        need(r['type']==kind and r['addend']==0 and want_symbol in r['symbol'],
             f'COFF source incorrect type/symbol/addend at {case:#x}:{ordinal}: {r}')
        actual.append((ordinal,kind,address,want_symbol))
    expected=1 if case<0x327 else 18
    need(len(source)==len(actual)==expected,
         f'case {case:#x} physical COFF fields not authentic ({len(actual)} vs {len(source)} vs {expected})')
    return actual


def authentic_grammar(instructions,case):
    ordinals={x.address:k for k,x in enumerate(instructions)}
    normalized=[]
    for x in instructions:
        op=FRAME.sub('[NATIVE_STACK_LOCAL]',x.op_str)
        if x.mnemonic.startswith('j') and BRANCH.fullmatch(op):
            target=int(op,16)
            op=('TO_INSTRUCTION_'+str(ordinals[target]) if target in ordinals
                else 'EXIT_WHOLE_FIGHTER')
        elif x.mnemonic=='call' and BRANCH.fullmatch(op):
            op='TRUE_TYPED_COFF_CALL'
        elif x.mnemonic.startswith('f') and ABS.fullmatch(op):
            # All these globals are independently verified by their
            # physical DIR32 relocation and actual original PE address.
            op=ABS.sub(lambda m:m.group(1)+' ptr [TRUE_TYPED_GLOBAL]',op)
        normalized.append((x.mnemonic,x.size,op))
    return normalized


def compare_actual_case(original,candidate,refs,case):
    need(len(original)==len(candidate) and
         sum(x.size for x in original)==sum(x.size for x in candidate),
         f'whole original {case:#x}: C++ case length/mnemonic number differs')
    fields=typed_fields(original,candidate,refs,case)
    na=authentic_grammar(original,case)
    ca=authentic_grammar(candidate,case)
    differences=[(k,x,y) for k,(x,y) in enumerate(zip(na,ca)) if x!=y]
    need(not differences,
         f'whole native case {case:#x} GPR/x87/branch/operand mismatch: {differences[:5]}')
    return fields


def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    need(source.exists() and source.stat().st_size>9000,
         'missing real 271-insn source for native giant actor')
    code=source.read_text()
    for action in range(FIRST,LAST+1):
        need(code.count(f'case 0x{action:X}:')==1,
             'missing/duplicated genuine original C++ action')
    need('DIAGNOSTIC marker stores' in code and
         'g_FighterProbeMarker' in code,
         'unfinished original action cases must remain transparently diagnostic')
    obj=OUT/'CharacterObjectActionsF572.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source),str(obj),
                         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                        cwd=ROOT,capture_output=True,text=True,env=env,timeout=120)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'new native C++ selected TU compile failed: {proc.stderr}')
    return obj


def main():
    m=module('f572_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f572_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    sw=module('f572_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    t=m.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads(MANIFEST.read_text())['bosses'] if x['address']==ADDRESS)
    need(boss['size']==33293 and boss['postret_size']==438 and
         boss['jump_count']==1,
         'entire original one-switch giant CODE or DATA extent changed')
    report,mapped=actions.report_boss(m,t,d,boss)
    original_byaction={x['action']:int(x['handler'],16) for x in mapped}
    original_default=int(report['default'],16)
    table=boss['tables'][0]
    need(table['slots']==60 and table['map_length']==198 and
         table['map_addr'] is not None,
         'original native dense/compressed handler topology changed')
    full_map=m.pe_bytes_at(t,table['map_addr'],table['map_length'])
    native_dense=m.pe_bytes_at(t,table['dense_addr'],4*table['slots'])
    need(hashlib.sha256(full_map).hexdigest()==table['map_sha'] and
         hashlib.sha256(native_dense).hexdigest()==table['dense_sha'],
         'original pinned native sparse/handler DWORD SHA changed')
    obj=compile_one(SOURCE)
    code,refs=m.object_function(obj,'?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ')
    instructions=[]
    for x in d.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    need(instructions and instructions[-1].mnemonic=='ret','generated C++ no normal RET')
    ret=instructions[-1].address+instructions[-1].size
    need(len(code)-ret==table['slots']*4+table['map_length']==boss['postret_size'],
         'whole physical original after-RET switch DATA shape differs')
    physical=sorted((r for r in refs if ret<=r['offset']<ret+table['slots']*4),
                    key=lambda r:r['offset'])
    need(len(physical)==table['slots'] and all(
         x['type']=='DIR32' and x['addend']==0 and
         x['offset']==ret+4*k and x['local_symbol_offset'] is not None
         for k,x in enumerate(physical)),
         'candidate physical complete dense COFF relocation slots differ')
    candidate_dense=[x['local_symbol_offset'] for x in physical]
    original_dense=[int.from_bytes(native_dense[4*k:4*k+4],'little')
                    for k in range(table['slots'])]
    need(sw.canonical_partitions(candidate_dense)==sw.canonical_partitions(original_dense),
         'original duplicated/default handler partitions not reproduced by source')
    candidate_map=code[ret+4*table['slots']:]
    need(candidate_map==full_map,'original real compressed byte-index map differs')
    ja=[int(x.op_str,16) for x in instructions if x.mnemonic=='ja' and BRANCH.fullmatch(x.op_str)]
    need(len(ja)>=1,'native C++ one-switch default guard JA missing')
    candidate_default=ja[0]
    need([x==original_default for x in original_dense]==
         [x==candidate_default for x in candidate_dense],
         'true native default dispatch slot flags differ')
    cases=[]
    source_fields=0
    for action in range(FIRST,LAST+1):
        real_start=original_byaction[action]
        real_end=original_byaction[action+1]
        need(boss['address']<=real_start<real_end<boss['address']+boss['size'],
             'original case boundary crosses complete original CODE')
        native=list(d.disasm(m.pe_bytes_at(t,real_start,real_end-real_start),real_start))
        idx=full_map[action-FIRST]
        next_idx=full_map[action+1-FIRST]
        physical_start=candidate_dense[idx]
        physical_end=candidate_dense[next_idx]
        need(0<=physical_start<physical_end<ret,
             f'case {action:#x}: candidate native generated code not physical')
        candidate=list(d.disasm(code[physical_start:physical_end],physical_start))
        need(native and native[0].address==real_start and
             native[-1].address+native[-1].size==real_end and
             candidate and candidate[0].address==physical_start and
             candidate[-1].address+candidate[-1].size==physical_end,
             f'original/candidate case {action:#x} not entirely contiguous x86')
        count_expected=3 if action<0x327 else 271
        bytes_expected=(13 if action<0x327 else
                        998 if action==0x327 else 999)
        need(len(native)==count_expected and real_end-real_start==bytes_expected,
             f'unknown real native action {action:#x} original footprint')
        fields=compare_actual_case(native,candidate,refs,action)
        source_fields+=len(fields)
        cases.append({'action':f'0x{action:X}','native_instructions':len(native),
                      'native_CODE_bytes':real_end-real_start,
                      'real_typed_COFF_fields':len(fields)})
        print(f'{action:#05x}: complete original {len(native)}/{len(candidate)} '
              f'GPR/x87/CFG/byte-width instructions, {bytes_expected} original '
              f'CODE bytes, {len(fields)} real COFF call/global references',flush=True)
    need(len(cases)==10 and source_fields==61,
         'seven real small and three 271-insn giant original cases do not yield 61 COFF fields')
    result={'boss':f'0x{ADDRESS:08X}','entire_original_CODE_unaccepted':boss['size'],
            'original_full_native_case_count':10,
            'original_case_details':cases,
            'all_cases_instructions':sum(x['native_instructions'] for x in cases),
            'original_inner_CODE_bytes':sum(x['native_CODE_bytes'] for x in cases),
            'genuine_physical_typed_case_COFF_fields':source_fields,
            'original_dense_DWORD_COFF_slots':len(physical),
            'exact_original_sparse_index_bytes':len(full_map),
            'separate_postret_native_DATA_shape':len(code)-ret}
    need(result['all_cases_instructions']==834 and result['original_inner_CODE_bytes']==3087,
         'native original first 10 game actions aggregate count changed')
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print(f'ORIGINAL 0x{ADDRESS:08X}: ten complete native game-action cases '
          f'{result["all_cases_instructions"]} actual x86 instructions / '
          f'{result["original_inner_CODE_bytes"]} original inner CODE bytes, '
          f'{source_fields}/61 real typed COFF fields, {len(physical)} physical '
          f'whole-switch COFF DWORD slots, {len(full_map)} exact compressed '
          f'bytes; full {boss["size"]} original giant CODE still NONEXACT')
    print('Only one affected natural VC7.1 C++ TU compiled; no whole/split '
          'native CODE exact credit, no full cold replay or Oracle receipt')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original 271-instruction CharacterObject source verifier failed:',exc,file=sys.stderr)
        raise SystemExit(1)
