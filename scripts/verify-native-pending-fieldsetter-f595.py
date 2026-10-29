#!/usr/bin/env python3
"""F595: exact 40-byte *source-code shape* of an origin-UNKNOWN leaf.

Original Japanese TH075 1.11 004135F0 is 40 bytes/16 x86 instructions
with no COFF relocations, a thiscall 3-field write + RET 0xC.
One freshly compiled ordinary VC7.1 C++ TU is all 40/40 bytes exact.
However absence of registered native direct-call/dword references and
lack of original independent class/owner identity means the function is
NOT classified as authored and earns 0 official exact function/CODE
credit. Also independently reread true 36 exact game-callers to a
separate 45-byte R108-unknown constructor 00449DE0, and six mixed
library/game callers of 004588B0, without laundering provenance.
No all-unit cold replay or Factory/Oracle acceptance.
"""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from collections import Counter, defaultdict

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/NativeFieldSetterOriginPendingF595.cpp'
OUT=ROOT/'.analysis/f595-small-origin-source'
ADDR=0x004135F0
SIZE=40
SYMBOL='?WriteFields@NativeFieldSetterF595@@QAEXEII@Z'
CASES={0x004135F0:0,0x00449DE0:36,0x004588B0:6}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def import_source(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None, f'missing original-PE checker {path}')
    module=importlib.util.module_from_spec(spec)
    sys.modules[tag]=module
    spec.loader.exec_module(module)
    return module


def compile_original_source():
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=SOURCE
    need(cpp.read_text().count('class NativeFieldSetterF595')==1
         and cpp.read_text().count('WriteFields(unsigned char flag')==2,
         'genuine original pending owner-unknown source must be typed ordinary C++')
    obj=OUT/'one-normal-Cpp-probe.obj'
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    command=[str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src']
    result=subprocess.run(command,cwd=ROOT,text=True,capture_output=True,env=env,timeout=120)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,f'pinned original VC7.1 C++ build failed: {result.stderr}')
    return obj


def native_callers(pe,reader,decoder):
    rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    callers=defaultdict(list)
    for row in rows:
        try:
            addr=int(row['address'],16);size=int(row['size'])
        except (ValueError,KeyError):continue
        for inst in decoder.disasm(reader.pe_bytes_at(pe,addr,size),addr):
            if inst.mnemonic!='call' or not inst.op_str.startswith('0x'):continue
            dest=int(inst.op_str,16)
            if dest in CASES:
                callers[dest].append({'address':f'0x{addr:08X}',
                                      'site':f'0x{inst.address:08X}',
                                      'caller':row['proposed_name'],
                                      'status':row['status'],
                                      'source':row['source_file']})
    need(all(len(callers[k])==v for k,v in CASES.items()),
         f'native original complete function-inventory CALL graph changed: '
         f'{[(hex(k),len(callers[k])) for k in CASES]}')
    bg=callers[0x449DE0]
    need(all(r['status']=='matching' and 'BackgroundLoad' in r['source']
             for r in bg) and len({x['address'] for x in bg})==36,
         'original pure-virtual BackgroundStage base is not physically linked to 36 independently exact authored load constructors')
    mix=Counter(x['status'] for x in callers[0x4588B0])
    need(mix.get('matching')==1 and mix.get('excluded')==4
         and mix.get('unclassified')==1,
         'original resource-element destructor owner is still mixed game/STL and cannot be automatically attributed')
    return callers, len(rows)


def main():
    reader=import_source('f595_reader',ROOT/'scripts/compare-coff-function.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    native=reader.pe_bytes_at(pe,ADDR,SIZE)
    native_ins=list(decoder.disasm(native,ADDR))
    need(len(native)==SIZE and len(native_ins)==16 and
         sum(i.size for i in native_ins)==SIZE and
         native_ins[-1].mnemonic=='ret' and native_ins[-1].op_str=='0xc'
         and native_ins[6].mnemonic=='mov' and native_ins[6].op_str=='byte ptr [eax + 0x24], cl'
         and native_ins[9].op_str=='dword ptr [edx + 0x1c], eax'
         and native_ins[12].op_str=='dword ptr [ecx + 0x20], edx',
         'entire original 40-byte leaf and typed 3-arg thiscall source materially differs')
    source_obj=compile_original_source()
    code,refs=reader.object_function(source_obj,SYMBOL)
    source_ins=list(decoder.disasm(code,0))
    need(len(code)==SIZE and code==native and len(source_ins)==16
         and not refs and all(x.bytes==y.bytes for x,y in zip(native_ins,source_ins)),
         'origin-unknown 004135F0 whole original 40-byte machine code is not truly exact')
    run=subprocess.run([sys.executable,str(ROOT/'scripts/compare-coff-function.py'),
                        str(source_obj),SYMBOL,hex(ADDR),str(SIZE),'--json'],
                       cwd=ROOT,text=True,capture_output=True,timeout=120)
    need(run.returncode==0 and run.stdout.strip(),
         f'original-PE full-source COFF matcher failed: {run.stderr}')
    full=json.loads(run.stdout)
    need(full['result']=='structural-exact' and full['matched_comparable_bytes']==40
         and full['comparable_bytes']==40 and len(full['relocations'])==0,
         'whole original 004135F0 byte count or relocation source evidence is not 40/40 exact')
    (OUT/'whole-original-comparison.json').write_text(run.stdout)
    origin={int(r['address'],16):r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for addr in CASES:
        need(origin[addr]['origin']=='unknown' and origin[addr]['disposition']=='review',
             f'original {addr:#x} origin was independently classified already: check before using pending-source probe')
    callers,functions_checked=native_callers(pe,reader,decoder)
    original_file=(ROOT/'resources/th075.exe').read_bytes()
    byte_refs=original_file.count(ADDR.to_bytes(4,'little'))
    need(byte_refs==0,'native pending leaf now has at least one raw direct pointer DATA/imm site; re-evaluate ownership')
    vtbl=reader.pe_bytes_at(pe,0x0065844C,24)
    words=[int.from_bytes(vtbl[i:i+4],'little') for i in range(0,24,4)]
    need(words==[0x00449D60,*([0x00641E19]*5)],
         f'original BackgroundStage pure virtual base vtable is not attested: {list(map(hex,words))}')
    summary={
      'native_original_function':'0x004135F0',
      'native_original_whole_CODE_bytes':40,
      'native_original_complete_x86_instructions':16,
      'original_native_return_stack_bytes':12,
      'normal_VC71_source_whole_exact_bytes':40,
      'normal_source_real_critical_machine_byte_equal':True,
      'real_original_COFF_fields':0,
      'native_original_SHA256':hashlib.sha256(native).hexdigest(),
      'accepted_new_authored_exact_functions':0,
      'accepted_new_authored_CODE_bytes':0,
      'origin':'unknown',
      'registered_native_function_boundaries_scanned':functions_checked,
      'registered_direct_CALL_004135F0':len(callers[ADDR]),
      'raw_absolute_POINTER_004135F0_refs':byte_refs,
      'registered_direct_CALL_00449DE0':len(callers[0x449DE0]),
      'registered_direct_CALL_004588B0':len(callers[0x4588B0]),
      'vtable_0065844C_words':[f'0x{v:08X}' for v in words],
      'still_unknown_00449DE0_and_004588B0':True,
      'all_unit_cold_replay_run':False}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    (OUT/'native-original-callers.json').write_text(json.dumps({f'0x{k:08X}':v for k,v in callers.items()},indent=2)+'\n')
    print(f'F595 original 004135F0 40/40 native CODE bytes, 16/16 x86, original zero-COFF full exact C++; origin still UNKNOWN, ZERO official game exact credit',flush=True)
    print(f'F595 source CALL-site audit {functions_checked} original function boundaries: no 004135F0 registered direct call nor raw 4-byte PE reference',flush=True)
    print('F595 independent original peer evidence: 00449DE0 has 36 previously exact game BackgroundStage constructor callers and 5 purecall vtable slots; 004588B0 has 6 mixed game/STL callers. Both still origin UNKNOWN.',flush=True)
    print('One original-pinned VC7.1 C++ TU; no all-unit cold replay, no official authored count change or external Oracle')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F595 native origin-pending small complete leaf proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
