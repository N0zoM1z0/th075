#!/usr/bin/env python3
"""F788: complete native composite implicit copy ctor and assignment.

One fresh compiler-generated 116B value COMDAT, two full function
boundaries and all original physical PE references validated, including
the EH handler field and actual staging for nontrivial 16B header.
Historical authored/implicit provenance remains unknown; no game
authored exact-unit adoption or mass replay.
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
OUT=ROOT/'.analysis/f788-composite-implicit-ctor'
SRC=ROOT/'probes/CompositeImplicitAssignmentF787.cpp'
SYMS={
    'ctor': ('??0CompositeValueF787@@QAE@ABU0@@Z',0x004591E0,417,128,{
        0x06:('DIR32',0x00656273),
        0x0C:('DIR32',0x00000000),
        0x14:('DIR32',0x00000000),
        0x16D:('REL32',0x00459390),
        0x183:('REL32',0x00459390),
        0x197:('DIR32',0x00000000)}),
    'assignment':('??4CompositeValueF787@@QAEAAU0@ABU0@@Z',0x0045AAE0,368,118,{
        0x151:('REL32',0x0045AC50),
        0x163:('REL32',0x0045AC50)}),
}

def load(tag,file):
    spec=importlib.util.spec_from_file_location(tag,ROOT/file)
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module
    spec.loader.exec_module(module)
    return module

def main():
    reader=load('f788_reader','scripts/compare-coff-function.py')
    f787=load('f788_f787','scripts/verify-composite-implicit-assignment-f787.py')
    target=reader.verified_target()
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/'CompositeImplicitCopyF788.obj'
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SRC),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=240)
    (OUT/'compile.log').write_text(cp.stdout+cp.stderr)
    if cp.returncode:
        raise ValueError('F788 full source failed pinned VC7.1 compilation '+(cp.stdout+cp.stderr)[-1000:])
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    result={}
    for typ,(symbol,addr,size,nx,fields) in SYMS.items():
        # Never compare an independently known SIZE by truncating a
        # generated constructor/assignment COMDAT: check full section.
        f787.require_untruncated_compiler_comdat(obj,reader,symbol,size)
        code,refs=reader.object_function(obj,symbol,size)
        raw=reader.pe_bytes_at(target,addr,size)
        native=list(d.disasm(raw,addr))
        generated=list(d.disasm(code,0))
        if not(len(code)==size and len(native)==len(generated)==nx
             and sum(x.size for x in generated)==size):
            raise ValueError('F788 full native constructor/assignment original extent mismatch '+typ)
        if len(refs)!=len(fields) or {r['offset'] for r in refs}!=set(fields):
            raise ValueError('original complete '+typ+' physical COFF fields missing')
        mask=set()
        for r in refs:
            off=r['offset']
            expected_type,dest=fields[off]
            if r['type']!=expected_type or r['addend']!=0 or r['local_symbol_offset'] is not None:
                raise ValueError('native '+typ+' has nonreal COFF field '+str(r))
            field=int.from_bytes(raw[off:off+4],'little')
            native_target=(field if expected_type=='DIR32' else
                      addr+off+4+int.from_bytes(raw[off:off+4],'little',signed=True))
            if native_target!=dest:
                raise ValueError('original '+typ+' physical PE relocated destination wrong at '+hex(off))
            if typ=='ctor' and off in (0x16D,0x183) and 'NestedSequenceF787' not in r['symbol']:
                raise ValueError('original nested-constructor source symbol missing')
            if typ=='assignment' and 'NestedSequenceF787' not in r['symbol']:
                raise ValueError('original nested-assignment source symbol missing')
            mask.update(range(off,off+4))
        wrong=[i for i in range(size) if i not in mask and raw[i]!=code[i]]
        if wrong:
            raise ValueError('F788 original source '+typ+' not physically exact at '+str(wrong[:12]))
        result[typ]={'original_address':f'0x{addr:08X}',
                     'complete_original_CODE_bytes':size,
                     'original_and_source_x86':nx,
                     'nonrelocation_bytes_identical':size-len(mask),
                     'physical_typed_original_rel_fields':len(refs),
                     'complete_function_source_matches_original':True,
                     'historical_function_provenance':'unknown'}
        if typ=='ctor':
            if (raw[0x38:0x3F]!=bytes.fromhex('c745fc00000000')
                or raw[0x171:0x175]!=bytes.fromhex('c645fc01')):
                raise ValueError('original EH state lifetime sequence does not match physical 16B header')
            # Original Ghidra EH handler is a real 10B VC7
            # _CxxFrameHandler thunk, not arbitrary game CODE.
            actual_handler=reader.pe_bytes_at(target,0x00656273,10)
            if not(actual_handler[0]==0xB8 and actual_handler[5]==0xE9):
                raise ValueError('native EH handler is not the verified VC7 shape')
            result[typ]['native_state_zero_after_header_offset']='0x38'
            result[typ]['native_state_one_after_first_nested_offset']='0x171'
            result[typ]['original_EH_handler']='0x00656273'
    (OUT/'verified-summary.json').write_text(json.dumps({
        'original_target_version':'Japanese TH075 v1.11 supplied archive',
        'provenance_determination':'unknown; implicit and explicit authored source may emit identical code',
        'reviewed_original_complete_functions':result,
        'original_total_source_equivalent_CODE_B':785,
        'official_accepted_authored_CODE_B':0,
        'all_exact_units_replayed':False,
    },indent=2)+'\n')
    print('F788 two native whole C++ function bodies: 417/417B constructor (128 x86, 393/393 nonfield, six PE fields with EH) + 368/368B assignment (118 x86, 360/360 nonfield, two PE fields). Source compiles once; historical provenance still unknown; no authored credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F788 full native composite source comparison FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
