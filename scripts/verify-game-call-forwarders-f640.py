#!/usr/bin/env python3
"""F640: 12 complete original C++ forwarding/receiver tiny game leaves.

Build only one ordinary pinned VC7.1 source TU; check full native
203 whole CODE bytes/99 x86 and ten physically original typed
zero-addend PE/COFF call targets. Independently scan original PE
CALL instructions in all 4351 registered actual native CODE extents.
Original function authorship and guessed float-vs-int parameter types
remain UNKNOWN: no authored exact credit or full all-unit cold replay.
"""
from __future__ import annotations
import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/GameCallForwardersF640.cpp'
OUT=ROOT/'.analysis/f640-game-call-forwarders-verified'
# The actual *whole* original PE case and its genuine one-arg/thiscall
# adapter real CALL is independent of provisional C++ type naming.
CASES={
  0x0040D900:(17,8,'?ForwardFloatAt40D900@@YAMM@Z',8,0x0040D920,7,5),
  0x0040D940:(17,8,'?ForwardFloatAt40D940@@YAMM@Z',8,0x0040D960,14,12),
  0x00412D90:(17,8,'?ForwardFloatAt412D90@@YAMM@Z',8,0x00412DB0,68,68),
  0x00428D20:(17,8,'?ForwardFloatAt428D20@@YAMM@Z',8,0x00428D40,6,6),
  0x00449A60:(17,8,'?ForwardFloatAt449A60@@YAMM@Z',8,0x00449A80,6,6),
  0x00438A60:(17,8,'?ForwardFloatAt438A60@@YAMM@Z',8,0x00641FB8,14,14),
  0x004073A0:(11,7,'?Noop@NoopAt4073A0F640@@QAEXXZ',None,None,1,1),
  0x00438CF0:(11,7,'?Noop@NoopAt438CF0F640@@QAEXXZ',None,None,1,1),
  0x0040DE30:(19,9,'?Forward@ForwardObjectAt40DE30F640@@QAEXXZ',11,0x0040E150,3,2),
  0x0040DF40:(19,9,'?Forward@ForwardObjectAt40DF40F640@@QAEXXZ',11,0x0040E2F0,5,4),
  0x0040D8E0:(19,9,'?Forward@ForwardObjectAt40D8E0F640@@QAEXXZ',11,0x0041A380,7,1),
  0x0040D8C0:(22,10,'??0GameNativeContainerF640@@QAE@XZ',11,0x0041A2D0,3,1),
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def reader_module():
    spec=importlib.util.spec_from_file_location('f640_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'missing original physical PE reader')
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module
    spec.loader.exec_module(module)
    return module


def compile_source():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'twelve-whole-original-game-leaves.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,
         'pinned original VC7.1 normal C++ source compile failed: '+p.stderr[-480:])
    return obj


def whole_original(reader,pe,decoder,obj,addr,info):
    size,count,symbol,off,target,total,authored=info
    real=reader.pe_bytes_at(pe,addr,size)
    code,fields=reader.object_function(obj,symbol,expected_size=size)
    native=list(decoder.disasm(real,addr))
    source=list(decoder.disasm(code,addr))
    need(len(real)==len(code)==size
         and len(native)==len(source)==count
         and sum(x.size for x in native)==sum(x.size for x in source)==size
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(native,source))
         and native[-1].mnemonic==source[-1].mnemonic=='ret',
         f'{addr:#x}: whole native original 11/17/19/22-byte x86 geometry does not match')
    need(len(fields)==(1 if off is not None else 0),
         f'{addr:#x}: actual physical original one/zero COFF fields differ')
    linked=bytearray(code)
    if off is not None:
        f=fields[0]
        need(f['offset']==off and f['type']=='REL32'
             and f['addend']==0 and f['local_symbol_offset'] is None,
             f'{addr:#x}: real original native REL32 call physical source field+{off:#x} wrong')
        instruction=next((x for x in native if x.address<=addr+off<x.address+x.size),None)
        need(instruction is not None and instruction.mnemonic=='call'
             and instruction.op_str==f'0x{target:x}',
             f'{addr:#x}: actual original x86 CALL destination {target:#x} differs')
        reloc=(target-(addr+off+4))&0xFFFFFFFF
        need(struct.unpack_from('<I',real,off)[0]==reloc
             and bytes(code[off:off+4])==b'\0'*4,
             f'{addr:#x}: physically owned original PE relative call operand not consistent')
        struct.pack_into('<I',linked,off,reloc)
        need(f['symbol'] and f['symbol'].startswith('?'),
             f'{addr:#x}: source unlinked original callee missing valid compiler symbol')
    need(bytes(linked)==real,
         f'{addr:#x}: entire original native CODE bytes do not match normal source after genuine target resolution')
    nonfield=size-(4 if off is not None else 0)
    return {'original_complete_native_function':f'0x{addr:08X}',
            'actual_original_whole_CODE_bytes':size,
            'complete_original_native_x86':count,
            'full_original_linked_CODE_bytes_equal':True,
            'native_true_physical_COFF_fields':len(fields),
            'original_native_PE_callee':None if target is None else f'0x{target:08X}',
            'actual_original_nonrelocation_bytes_equal':nonfield,
            'ordinary_source_COFF_symbol':None if not fields else fields[0]['symbol'],
            'original_source_provenance':'unknown',
            'accepted_new_whole_authored_CODE_bytes':0}


def source_callers(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        originals=list(csv.DictReader(stream))
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        classifications={x['address']:x for x in csv.DictReader(stream)}
    need(len(originals)==4351,'original native whole registered function extents changed')
    for addr in CASES:
        classification=classifications[f'0x{addr:08X}']
        need(classification['origin']=='unknown' and classification['disposition']=='review',
             f'{addr:#x}: original compiler-vs-authored source provenance changed')
    calls={addr:[] for addr in CASES}
    for row in originals:
        start=int(row['address'],16)
        for ins in decoder.disasm(reader.pe_bytes_at(pe,start,int(row['size'])),start):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                dest=int(ins.op_str,16)
                if dest in calls:
                    calls[dest].append({
                        'real_original_native_CALL_site':f'0x{ins.address:08X}',
                        'original_entire_registered_caller':row['address'],
                        'current_caller_origin':row['owner'],
                        'caller_provisional_name':row['proposed_name']})
    for addr,info in CASES.items():
        count=len(calls[addr])
        authored=sum(x['current_caller_origin']=='authored' for x in calls[addr])
        need((count,authored)==info[5:7],
             f'{addr:#x}: real original PE direct game caller count {count}/{authored} changed')
    return calls


def main():
    reader=reader_module()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    obj=compile_source()
    receipts=[]
    for addr,info in CASES.items():
        row=whole_original(reader,pe,decoder,obj,addr,info)
        receipts.append(row)
        print(f'F640 {addr:#010x}: original full native whole CODE '
              f'{row["actual_original_whole_CODE_bytes"]}/'
              f'{row["actual_original_whole_CODE_bytes"]} linked bytes, '
              f'{row["complete_original_native_x86"]} actual x86, '
              f'{row["native_true_physical_COFF_fields"]} true typed PE/COFF call; '
              'historical origin UNKNOWN',flush=True)
    calls=source_callers(reader,pe,decoder)
    totals=(len(receipts),sum(r['actual_original_whole_CODE_bytes'] for r in receipts),
            sum(r['complete_original_native_x86'] for r in receipts),
            sum(r['native_true_physical_COFF_fields'] for r in receipts))
    need(totals==(12,203,99,10),
         f'original small full-code source/field accounting changed: {totals}')
    summary={'original_pinned_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'true_original_compiler_profile':'MSVC VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi',
             'source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'all_original_function_extents_scanned_for_true_DIRECT_CALL':4351,
             'twelve_distinct_whole_original_game_source_reproductions':receipts,
             'actual_original_native_DIRECT_CALL_sites':{f'0x{a:08X}':v for a,v in calls.items()},
             'original_whole_native_CODE_bytes_source_backed_uncredited':totals[1],
             'total_original_native_x86':totals[2],
             'total_original_PE_targeted_COFF_fields':totals[3],
             'new_accepted_authored_whole_functions':0,
             'new_accepted_authored_whole_CODE_bytes':0,
             'full_cold_all_unit_replay':False}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F640 12 full original native game-facing small functions, '
          '203/203 exact whole linked CODE bytes, 99 original x86, '
          '10 true physically typed original PE/COFF calls, '
          'source provenance UNKNOWN; ZERO new authored exact credit. '
          'No all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F640 original Japanese TH075 whole small C++ forwarding source verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
