#!/usr/bin/env python3
"""F601: two original 21+37-byte atan2 adapters with real native CALL fields.

Cold compile ONE ordinary VC7.1 C++ TU, compare both complete original
Japanese TH075 PE functions and resolve all physical actual COFF fields.
Original authored-vendor ownership is left explicitly unresolved.
"""
from __future__ import annotations

from collections import Counter,defaultdict
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
SOURCE=ROOT/'probes/FloatAtan2AdaptersF601.cpp'
OUT=ROOT/'.analysis/f601-atan2-natural-source'
CASES=(
 ('0x00483300',21,10,'?FloatAtan2ForwardF601@@YAMMM@Z',0x0C,0x00483320,
  '?FloatAtan2ThroughDoubleF601@@YAMMM@Z'),
 ('0x00483320',37,15,'?FloatAtan2ThroughDoubleF601@@YAMMM@Z',0x17,0x00642240,'_atan2'),
)


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None, 'missing original PE code reader')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def original_and_generated(reader,pe,decoder,obj,item):
    addrstr,size,instructions,symbol,offset,callee,calledsymbol=item
    address=int(addrstr,16)
    native=reader.pe_bytes_at(pe,address,size)
    source,refs=reader.object_function(obj,symbol)
    a=list(decoder.disasm(native,address));b=list(decoder.disasm(source,address))
    need(len(source)==len(native)==size and len(a)==len(b)==instructions
         and sum(x.size for x in a)==sum(x.size for x in b)==size
         and a[-1].mnemonic==b[-1].mnemonic=='ret'
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(a,b)),
         f'{addrstr}: actual complete source/original x86 boundary/geometry/mnemonics differ')
    need(len(refs)==1 and refs[0]['offset']==offset
         and refs[0]['type']=='REL32' and refs[0]['symbol']==calledsymbol
         and refs[0]['addend']==0 and refs[0]['local_symbol_offset'] is None,
         f'{addrstr}: original real external cdecl CALL COFF field wrong: {refs}')
    target_field=struct.unpack_from('<i',native,offset)[0]
    native_target=(address+offset+4+target_field)&0xFFFFFFFF
    need(native_target==callee and
         a[6 if size==21 else 9].mnemonic==b[6 if size==21 else 9].mnemonic=='call'
         and a[6 if size==21 else 9].op_str==f'0x{callee:x}'
         and source[offset:offset+4]==b'\x00'*4,
         f'{addrstr}: original external true _atan2/forwarder callee changed')
    linked=bytearray(source)
    struct.pack_into('<I',linked,offset,(callee-address-offset-4)&0xFFFFFFFF)
    mask=set(range(offset,offset+4))
    identical=sum(source[i]==native[i] for i in range(size) if i not in mask)
    need(identical==size-4 and linked==native,
         f'{addrstr}: full original linked CODE bytes not equal')
    if size==37:
        need(a[3].mnemonic=='fld' and a[5].mnemonic=='fstp'
             and a[6].mnemonic=='fld' and a[8].mnemonic=='fstp'
             and a[11].mnemonic=='fst' and a[11].op_str=='dword ptr [ebp - 4]',
             'original CRT double stack arguments and float return differ')
    return {'original':addrstr,'whole_CODE_bytes':size,'complete_x86_instructions':instructions,
            'nonfield_bytes_equal':identical,'nonfield_bytes_total':size-4,
            'original_true_external_COFF_fields':[{'offset':f'0x{offset:X}','type':'REL32',
                'source_symbol':calledsymbol,'actual_original_PE_target':f'0x{callee:08X}',
                'actual_addend':0}],
            'linked_whole_original_CODE_byte_exact':True,
            'independent_authored_origin_proven':False,'accepted_new_authored_bytes':0}


def caller_audit(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as file:
        rows=list(csv.DictReader(file))
    functions={row['address']:row for row in rows}
    hits=defaultdict(list)
    for row in rows:
        addr=int(row['address'],16)
        for x in decoder.disasm(reader.pe_bytes_at(pe,addr,int(row['size'])),addr):
            if x.mnemonic=='call' and x.op_str.startswith('0x'):
                dest=int(x.op_str,16)
                if dest in (0x00483300,0x00483320):
                    hits[f'0x{dest:08X}'].append({'caller':row['address'],
                        'instruction':f'0x{x.address:08X}',
                        'current_caller_owner':row['owner'],
                        'current_caller_status':row['status']})
    helper=hits['0x00483320']
    need(len(helper)==1 and helper[0]['caller']=='0x00483300',
         'original leaf atan2 double adapter has different direct callers')
    forward=hits['0x00483300']
    need(forward and all(functions[x['caller']]['owner']=='authored' for x in forward),
         'original game caller ownership changed; reassess actual library-vs-author status')
    return {'registered_original_function_boundaries_examined':len(rows),
            'direct_callers_of_forwarder':len(forward),
            'distinct_direct_caller_functions':len({r['caller'] for r in forward}),
            'author_origin_is_only_the_callER_not_the_library_adapter':True,
            'original_registered_direct_callers':dict(hits)}


def main():
    reader=load('f601_reader',ROOT/'scripts/compare-coff-function.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origin={x['address']:x for x in csv.DictReader(stream)}
    need(all(origin[x[0]]['origin']=='unknown' and origin[x[0]]['disposition']=='review'
             for x in CASES),
         'original atan2 wrappers provenance changed; do not claim authored source')
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        need(any(x['address']=='0x00642240' and x['origin']=='library' for x in csv.DictReader(stream)),
             'original external _atan2 CRT callee is no longer library-classified')
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'one-ordinary-VC71-angle-source.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    compile=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
                   '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=ROOT,
                   env=env,capture_output=True,text=True,timeout=150)
    (OUT/'compiler.log').write_text(compile.stdout+compile.stderr)
    need(compile.returncode==0,f'original-profile VC7.1 compiler failed: {compile.stderr}')
    results=[original_and_generated(reader,pe,decoder,obj,case) for case in CASES]
    callers=caller_audit(reader,pe,decoder)
    summary={'original_PE_sha256':hashlib.sha256(pe).hexdigest(),
             'source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
             'new_object_sha256':hashlib.sha256(obj.read_bytes()).hexdigest(),
             'whole_original_code_reconstruction':results,'original_call_graph':callers,
             'candidate_member_provenance':'UNKNOWN: authored vs ordinary/SDK atan2 overload',
             'accepted_whole_game_functions':0,
             'accepted_new_authored_CODE_bytes':0,
             'all_unit_cold_replay':False}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    for result in results:
        print(f"F601: {result['original']} original whole "
              f"{result['whole_CODE_bytes']}/{result['whole_CODE_bytes']} linked CODE bytes, "
              f"{result['complete_x86_instructions']} x86 and 1 real original _atan2/forwarder COFF field",flush=True)
    print(f'F601: {callers["direct_callers_of_forwarder"]} native direct calls from '
          f'{callers["distinct_direct_caller_functions"]} registered authored parents, '
          'plus one leaf wrapper caller. Original adapter ownership UNKNOWN; '
          '0 new accepted CODE bytes or whole functions, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as exc:
        print('F601 original Japanese atan2 adapter source failed:',exc,file=sys.stderr)
        raise SystemExit(1)
