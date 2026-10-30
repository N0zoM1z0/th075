#!/usr/bin/env python3
"""Reproduce entire 0045AAE0 source match with honest unknown provenance.

Generated implicit VC7.1 record assignment: independently checked 116B
layout, 368 native CODE B / 118 x86 / 2 real calls, complete nonfield
machine bytes, both typed PE relocations. Its manual/implicit provenance
is NOT decided. No ledger adoption or authored-byte credit.
"""
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SRC=ROOT/'probes/CompositeImplicitAssignmentF787.cpp'
OBJ=ROOT/'.analysis/f787-composite-copy-attribution/F787-accepted-shape-only.obj'
OUT=ROOT/'.analysis/f787-composite-copy-attribution/F787-verified-assignment.json'
SYM='??4CompositeValueF787@@QAEAAU0@ABU0@@Z'
ADDR=0x0045AAE0
NATIVE_SIZE=368
CALLS={0x151:0x0045AC50,0x163:0x0045AC50}

def load():
    spec=importlib.util.spec_from_file_location('f787_reader',ROOT/'scripts/compare-coff-function.py')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=mod
    spec.loader.exec_module(mod)
    return mod

def require_untruncated_compiler_comdat(obj,reader,symbol,required_size):
    # An aux-less compiler-synthesized COMDAT must not silently be
    # truncated by the comparison helper's explicit expected_size.
    data=obj.read_bytes()
    machine,n_sections,_,symoff,nsyms,opt,_=struct.unpack_from('<HHIIIHH',data,0)
    if machine!=0x14c or opt!=0:
        raise ValueError('not the native i386 object format')
    strstart=symoff+nsyms*18
    strsize=struct.unpack_from('<I',data,strstart)[0]
    strings=data[strstart:strstart+strsize]
    i=0;matches=[]
    while i<nsyms:
        loc=symoff+i*18
        name,value,sect,kind,storage,naux=struct.unpack_from('<8sIhHBB',data,loc)
        if reader.coff_name(name,strings)==symbol and sect>0:
            matches.append((value,sect,kind,storage,naux))
        i+=1+naux
    if len(matches)!=1:
        raise ValueError('non-unique real implicit compiler method definition')
    offset,section,kind,storage,naux=matches[0]
    size=struct.unpack_from('<I',data,20+(section-1)*40+16)[0]
    if size!=required_size or offset!=0 or kind!=0x20 or naux!=0:
        raise ValueError('compiler COMDAT full physical section extent differs: '+str((size,offset,kind,naux)))


def main():
    rd=load()
    pe=rd.verified_target()
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    obj=OBJ
    obj.parent.mkdir(parents=True,exist_ok=True)
    command=[str(ROOT/'scripts/compile-probe.sh'),str(SRC),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi']
    cp=subprocess.run(command,cwd=ROOT,env=env,capture_output=True,text=True,timeout=240)
    (obj.parent/'f787-compile.log').write_text(cp.stdout+cp.stderr)
    if cp.returncode:
        raise ValueError('pinned VC7.1 source build failed '+(cp.stdout+cp.stderr)[-750:])
    # Compiler-generated COMDAT methods lack definition auxiliary records.
    # Size is independently bounded from the original 368B native PE,
    # and must not be used to crop nonmatching COFF instructions.
    require_untruncated_compiler_comdat(obj,rd,SYM,NATIVE_SIZE)
    code,refs=rd.object_function(obj,SYM,NATIVE_SIZE)
    native=rd.pe_bytes_at(pe,ADDR,NATIVE_SIZE)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    n=list(decoder.disasm(native,ADDR))
    s=list(decoder.disasm(code,0))
    if not (len(code)==NATIVE_SIZE and len(n)==len(s)==118
            and sum(x.size for x in s)==NATIVE_SIZE):
        raise ValueError('entire original native function extent/instructions changed')
    if len(refs)!=2 or {int(x['offset']) for x in refs} != set(CALLS):
        raise ValueError('actual native COFF field count/offsets wrong')
    masks=set()
    for r in refs:
        off=int(r['offset'])
        if r['type']!='REL32' or r['addend']!=0 or r['local_symbol_offset'] is not None or (
                'NestedSequenceF787' not in r['symbol']):
            raise ValueError('not the real whole nested STL assignment references '+str(r))
        target=ADDR+off+4+int.from_bytes(native[off:off+4],'little',signed=True)
        if target!=CALLS[off]:
            raise ValueError('true original PE nested assignment destination wrong')
        masks.update(range(off,off+4))
    mismatches=[i for i in range(NATIVE_SIZE) if i not in masks and native[i]!=code[i]]
    if mismatches:
        raise ValueError('original complete native CODE bytes nonfield mismatch '+str(mismatches[:24]))
    result={'original_function':'0x0045AAE0','original_game_candidate_origin':'unknown',
            'entire_native_CODE_B':NATIVE_SIZE,'native_and_source_x86':118,
            'nonfield_identical_B':360,'real_native_COFF_fields':2,
            'physical_calls':{'0x151':'0x0045AC50','0x163':'0x0045AC50'},
            'source_method':'compiler-synthesized implicit operator= of provisional 116B physical composite',
            'historical_source_identity':'unproved',
            'authored_exact_credit':0,'source_evidence_kind':'full-COFF-comparison-only'}
    OUT.write_text(json.dumps(result,indent=2)+'\n')
    print('F787: entire original 0045AAE0 368B/118-x86, 360/360 nonfield original bytes, two verified PE/COFF nested assignment calls. Origin remains unknown; 0 formal authored credit.')

if __name__=='__main__':
    try: main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F787 source verification FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
