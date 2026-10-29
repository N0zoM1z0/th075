#!/usr/bin/env python3
"""F604: two complete original 24B/31B unsigned-state leaf source controls.

Cold-compile one pinned natural C++ TU, check every whole original x86
byte (zero native relocations), and independently audit actual native
callers. These original unknown-origin functions are NOT awarded authored
CODE merely because a natural source can reproduce machine bytes.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/SceneFlagAndCounterLeavesF604.cpp'
OUT=ROOT/'.analysis/f604-game-leaves-source'
CASES=(('0x00454C00',24,9,'?ClearCounter@GameCounterOwnerF604@@QAEXXZ'),
       ('0x00454F70',31,15,'?HasFlagBit@GameStatusFlagOwnerF604@@QAEHXZ'))
EXPRESSION='& 0x20) > 0;'


def need(test,reason):
    if not test:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing native PE original source reader')
    reader=importlib.util.module_from_spec(spec)
    sys.modules[name]=reader
    spec.loader.exec_module(reader)
    return reader


def compile_source(name,content):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/(name+'.cpp');obj=OUT/(name+'.obj')
    cpp.write_text(content)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                   '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
                   env=env,cwd=ROOT,capture_output=True,text=True,timeout=160)
    (OUT/(name+'.log')).write_text(result.stdout+result.stderr)
    need(result.returncode==0,
         'original-profile VC7.1 C++ leaf source compilation failed: '+result.stderr[-600:])
    return obj


def check_case(reader,pe,decoder,obj,record):
    where,size,count,sym=record
    addr=int(where,16)
    original=reader.pe_bytes_at(pe,addr,size)
    code,refs=reader.object_function(obj,sym)
    native=list(decoder.disasm(original,addr));generated=list(decoder.disasm(code,addr))
    need(len(native)==len(generated)==count and len(code)==len(original)==size
         and sum(x.size for x in native)==sum(x.size for x in generated)==size
         and native[-1].mnemonic==generated[-1].mnemonic=='ret'
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(native,generated)),
         f'{where}: whole source/original PE function x86 extent, order, width differs')
    need(not refs and bytes(code)==original,
         f'{where}: complete original has unmatched bytes or unexpected physical COFF relocations')
    if size==24:
        need(native[5].mnemonic=='mov' and
             native[5].op_str=='dword ptr [eax + 0x47c], 0',
             'actual original +0x47C 32-bit counter clear no longer observed')
    else:
        expected=[('mov','edx, dword ptr [ecx + 0x3c]'),
                  ('and','edx, 0x20'),('xor','eax, eax'),
                  ('cmp','eax, edx'),('sbb','eax, eax'),('neg','eax')]
        need([(q.mnemonic,q.op_str) for q in native[6:12]]==expected,
             'real original is not unsigned >0 comparison via XOR/CMP/SBB/NEG')
    return {'original_PE_address':where,'whole_original_CODE_bytes':size,
            'whole_original_x86_instructions':count,
            'whole_linked_original_CODE_bytes_equal':size,
            'physically_owned_COFF_fields':0,
            'original_class_declaration_proven':False,
            'accepted_authored_CODE_bytes':0}


def caller_evidence(reader,pe,decoder):
    addresses={int(x[0],16):x[0] for x in CASES}
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        rows=list(csv.DictReader(stream))
    counts={f'0x{addr:08X}':[] for addr in addresses}
    for row in rows:
        base=int(row['address'],16)
        for ins in decoder.disasm(reader.pe_bytes_at(pe,base,int(row['size'])),base):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                dest=int(ins.op_str,16)
                if dest in addresses:
                    counts[f'0x{dest:08X}'].append({'caller':row['address'],
                        'native_CALL':f'0x{ins.address:08X}','current_origin':row['owner']})
    # No false claim of unreachable code: real indirect calls, unknown
    # extents and late linker metadata are not excluded by this scan.
    return {'native_function_boundaries_scanned':len(rows),
            'direct_CALL_from_registered_native_functions':counts,
            'literal_original_PE_DWORD_reference_counts':{
                f'0x{addr:08X}':pe.count(struct.pack('<I',addr)) for addr in addresses},
            'absence_of_discovered_direct_call_does_NOT_prove_unreachable':True}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--negative-predicate',action='store_true',
         help='compile one additional genuinely false 29-byte !=0 predicate source')
    args=parser.parse_args()
    src=SOURCE.read_text()
    need(src.count(EXPRESSION)==1 and src.count('GameCounterOwnerF604')>=2
         and src.count('GameStatusFlagOwnerF604')>=2,
         'native natural source lost genuine original unsigned predicate')
    reader=load('f604_native_reader',ROOT/'scripts/compare-coff-function.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origin={x['address']:x for x in csv.DictReader(stream)}
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        funcs={x['address']:x for x in csv.DictReader(stream)}
    need(all(origin[addr]['origin']=='unknown' and origin[addr]['disposition']=='review'
         and funcs[addr]['status']=='unclassified' and int(funcs[addr]['size'])==size
         for addr,size,_,_ in CASES),
         'unknown native original 24/31-byte original owner/extent changed')
    obj=compile_source('native-positive',src)
    positive=[check_case(reader,pe,decoder,obj,x) for x in CASES]
    negative=None
    if args.negative_predicate:
        neg=compile_source('negative-inequality',src.replace(EXPRESSION,'& 0x20) != 0;'))
        code,fields=reader.object_function(neg,CASES[1][3])
        ins=list(decoder.disasm(code,0))
        need(len(code)==29 and len(ins)==14 and not fields
             and bytes(code)!=reader.pe_bytes_at(pe,0x454F70,31)
             and [(q.mnemonic,q.op_str) for q in ins[8:11]]==[
                 ('neg','eax'),('sbb','eax, eax'),('neg','eax')],
             'simple nonzero expression no longer a distinct native-negative codegen control')
        negative={'literal_expression':'(flags & 0x20) != 0',
                  'VC71_x86_instructions':14,'whole_generated_CODE_bytes':29,
                  'original_whole_CODE_bytes':31,'native_original_comparison':'size-mismatch'}
        print('F604 negative: !=0 emits 29B/14 x86, not original 31B/15 x86',flush=True)
    result={'original_PE_sha256':hashlib.sha256(pe).hexdigest(),
            'source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            'positive_object_sha256':hashlib.sha256(obj.read_bytes()).hexdigest(),
            'source_profile':'/Od /Ob0 /Gy /GR- /GX- /GS /Zi',
            'original_complete_native_functions':positive,
            'native_original_caller_scan':caller_evidence(reader,pe,decoder),
            'optional_nonmatching_negative':negative,
            'original_member_owner':'unknown, independently recorded and not promoted',
            'accepted_new_whole_authored_functions':0,
            'accepted_new_authored_CODE_bytes':0,
            'all_unit_cold_replay':False}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(result,indent=2)+'\n')
    for row in positive:
        print(f'F604 {row["original_PE_address"]}: complete original '
              f'{row["whole_original_CODE_bytes"]}/'
              f'{row["whole_original_CODE_bytes"]} authentic native CODE bytes '
              f'and {row["whole_original_x86_instructions"]} x86, no COFF relocations',flush=True)
    print('F604: 55 authentic PE bytes reconstructed with ordinary C++; '
          'original class/source provenance remains unknown, zero authored '
          'CODE accepted, no 943-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F604 TH075 original two small native leaves verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
