#!/usr/bin/env python3
"""F644: six entire original 28-byte float-to-double math adapters.

Cold compile only ONE affected normal VC7.1 C++ TU; check complete
original native x86 and linked 28-byte function CODE, original PE
call target and typed zero-addend COFF field for each of the six,
plus real native CALLs within the registered original function CODE.
Historical source author-vs-generated ownership is still unknown.
Never run the 943-unit all-accepted cold replay or grant match credit.
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
SOURCE=ROOT/'probes/GameFloatMathAdaptersF644.cpp'
OUT=ROOT/'.analysis/f644-math-source/verified'
CALLEES={
  0x0040D920:0x00641754,
  0x0040D960:0x00641804,
  0x00412DB0:0x006418CD,
  0x00428D40:0x00641E54,
  0x00442040:0x00641FD0,
  0x00449A80:0x00642120,
}


def need(ok,why):
    if not ok:raise ValueError(why)


def reader_module():
    name='f644_reader'
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,'missing pinned original PE/COFF reader')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def build_source():
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'six-full-original-float-adapters.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
                  '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],cwd=ROOT,
                  env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,
         'actual VC7.1 original math-adapter source failed: '+run.stderr[-450:])
    return obj


def compare_native(reader,pe,decoder,obj,addr,target):
    expected=28
    native=reader.pe_bytes_at(pe,addr,expected)
    symbol=f'?FloatAdapterAt{addr:06X}@@YAMM@Z'
    source,refs=reader.object_function(obj,symbol,expected_size=expected)
    ni=list(decoder.disasm(native,addr))
    gi=list(decoder.disasm(source,addr))
    need(len(native)==len(source)==expected
         and len(ni)==len(gi)==12
         and sum(x.size for x in ni)==sum(x.size for x in gi)==expected
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(ni,gi))
         and ni[3].mnemonic=='fld' and ni[3].op_str=='dword ptr [ebp + 8]'
         and ni[4].mnemonic=='sub' and ni[4].op_str=='esp, 8'
         and ni[5].mnemonic=='fstp' and ni[5].op_str=='qword ptr [esp]'
         and ni[8].mnemonic=='fst' and ni[8].op_str=='dword ptr [ebp - 4]'
         and ni[-1].mnemonic==gi[-1].mnemonic=='ret',
         f'{addr:#x}: original complete 28-byte float-to-double x87 call grammar differs')
    need(len(refs)==1 and refs[0]['offset']==14
         and refs[0]['type']=='REL32'
         and refs[0]['addend']==0 and refs[0]['local_symbol_offset'] is None
         and refs[0]['symbol']==f'?NativeDoubleAt{target:06X}@@YANN@Z',
         f'{addr:#x}: real 14-offset original native PE callee COFF target differs')
    n=ni[6]
    need(n.mnemonic=='call' and n.op_str==f'0x{target:x}',
         f'{addr:#x}: original native physical x86 CALL destination {target:#x} differs')
    displacement=(target-(addr+14+4))&0xFFFFFFFF
    need(struct.unpack_from('<I',native,14)[0]==displacement
         and source[14:18]==b'\0'*4,
         f'{addr:#x}: true original native PE REL32 field is not physically correct')
    linked=bytearray(source)
    struct.pack_into('<I',linked,14,displacement)
    need(bytes(linked)==native,
         f'{addr:#x}: complete ORIGINAL 28-byte native function differs after true field resolution')
    return {'original_registered_native_function':f'0x{addr:08X}',
            'genuine_original_native_math_callee':f'0x{target:08X}',
            'original_complete_CODE_bytes':expected,
            'original_whole_native_x86':len(ni),
            'actual_physical_original_PE_COFF_fields':1,
            'original_native_x87_float_to_double_argument_promotion':True,
            'complete_original_native_machine_BYTES_IDENTICAL':True,
            'actual_original_source_origin':'unknown',
            'new_accepted_authored_whole_CODE_bytes':0}


def get_callers(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as f:
        functions=list(csv.DictReader(f))
    with (ROOT/'config/function-origins.csv').open(newline='') as f:
        origins={x['address']:x for x in csv.DictReader(f)}
    need(len(functions)==4351,'original function registered CODE extents changed')
    for addr in CALLEES:
        cls=origins[f'0x{addr:08X}']
        need(cls['origin']=='unknown' and cls['disposition']=='review',
             f'{addr:#x}: original historical source provenance needs independent review')
    uses={a:[] for a in CALLEES}
    for row in functions:
        begin=int(row['address'],16)
        for ins in decoder.disasm(reader.pe_bytes_at(pe,begin,int(row['size'])),begin):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                dest=int(ins.op_str,16)
                if dest in uses:
                    uses[dest].append({'real_native_original_CALL_site':f'0x{ins.address:08X}',
                                       'registered_original_caller':row['address'],
                                       'current_caller_origin':row['owner'],
                                       'provisional_caller_name':row['proposed_name']})
    need(all(len(xs)==1 for xs in uses.values()),
         'native original float adapter real source call topology changed')
    return uses


def main():
    rd=reader_module()
    pe=rd.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    obj=build_source()
    receipts=[]
    for addr,target in CALLEES.items():
        res=compare_native(rd,pe,decoder,obj,addr,target)
        receipts.append(res)
        print(f'F644 {addr:#010x}: original complete 28/28 whole machine CODE bytes, '
              f'12/12 x86 including real x87 float→double; genuine '
              f'PE-targeted COFF CALL {target:#010x} physically linked, '
              'historical origin UNKNOWN',flush=True)
    calls=get_callers(rd,pe,decoder)
    total=(len(receipts),sum(x['original_complete_CODE_bytes'] for x in receipts),
           sum(x['original_whole_native_x86'] for x in receipts),
           sum(x['actual_physical_original_PE_COFF_fields'] for x in receipts))
    need(total==(6,168,72,6),
         f'original 28-byte native game math source original physical accounting changed: {total}')
    artifact={'pinned_original_PE_SHA256':hashlib.sha256(pe).hexdigest(),
              'source_SHA256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
              'genuine_source_compiler_profile':'MSVC VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi',
              'six_complete_original_native_PE_math_functions':receipts,
              'all_registered_original_CODE_extents_scanned':4351,
              'independent_native_CALL_graph':{f'0x{a:08X}':xs for a,xs in calls.items()},
              'six_original_whole_CODE_bytes_source_backed_UNCREDITED':168,
              'accepted_new_whole_authored_exact_functions':0,
              'all_unit_cold_replay_performed':False}
    (OUT/'summary.json').write_text(json.dumps(artifact,indent=2)+'\n')
    print('F644 six genuine complete 28-byte original native x87 adapters, '
          '168/168 whole original CODE bytes, 72/72 physical x86, '
          '6 real linked PE/COFF fields, six native original game CALLs, '
          'ORIGIN UNKNOWN, ZERO accepted authored whole CODE; no 943-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F644 complete original native TH075 float adapter PE-source proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
