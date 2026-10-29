#!/usr/bin/env python3
"""F638: four entire native game C++ constructors, dual sources, origin unknown.

Cold build just TWO selected genuine ordinary VC7.1 C++ translation
units: explicit empty default constructors and completely independent
implicit compiler-generated default constructors forced by placement
new. Compare full original 23/31/34/25-byte game CODE after verifying
six physical typed zero-addend PE/COFF vtable/constructor destinations
and original direct CALL sites in all registered original native CODE.
Original explicit-vs-generated source ownership is still UNKNOWN;
no new authored exact acceptance, no 943-unit cold replay.
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
EXPLICIT=ROOT/'probes/GameInheritanceAndMemberConstructorsF638.cpp'
IMPLICIT=ROOT/'probes/GameInheritanceAndMemberConstructorsImplicitF638.cpp'
OUT=ROOT/'.analysis/f638-game-inheritance-constructors-verified'
# Native original per-function physical CODE fields, not merely one
# symbol-name guess or an ignored COFF relocation patch.
CASES={
    0x00458670:{'symbol':'??0BaseF638@@QAE@XZ','bytes':23,'x86':10,
                'fields':{12:('DIR32',0x0065904C,'??_7BaseF638@@6B@')},
                'actual_calls':2,'authored_calls':1},
    0x00458650:{'symbol':'??0DerivedF638@@QAE@XZ','bytes':31,'x86':12,
                'fields':{11:('REL32',0x00458670,'??0BaseF638@@QAE@XZ'),
                          20:('DIR32',0x00659038,'??_7DerivedF638@@6B@')},
                'actual_calls':2,'authored_calls':2},
    0x004251C0:{'symbol':'??0SceneOwnerF638@@QAE@XZ','bytes':34,'x86':13,
                'fields':{12:('DIR32',0x00657B88,'??_7SceneOwnerF638@@6B@'),
                          23:('REL32',0x00417210,'??0TextureMemberF638@@QAE@XZ')},
                'actual_calls':15,'authored_calls':15},
    0x00411C10:{'symbol':'??0SpriteContainerF638@@QAE@XZ','bytes':25,'x86':11,
                'fields':{14:('REL32',0x0040D990,'??0SpriteMemberF638@@QAE@XZ')},
                'actual_calls':1,'authored_calls':1},
}


def need(ok,message):
    if not ok:raise ValueError(message)


def load_reader():
    path=ROOT/'scripts/compare-coff-function.py'
    spec=importlib.util.spec_from_file_location('f638_reader',path)
    need(spec is not None and spec.loader is not None,
         'pinned original physical PE/COFF reader unavailable')
    rd=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=rd
    spec.loader.exec_module(rd)
    return rd


def compile_one(label,source):
    OUT.mkdir(parents=True,exist_ok=True)
    obj=OUT/f'{label}-full-source.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source),str(obj),
                  '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
                  cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/f'{label}-compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,
         f'{label}: actual VC7.1 complete original constructor source failed: {p.stderr[-480:]}')
    return obj


def check_whole(reader,pe,decoder,obj,addr,info,mode):
    size=info['bytes']
    original=reader.pe_bytes_at(pe,addr,size)
    generated,fields=reader.object_function(obj,info['symbol'],expected_size=size)
    ni=list(decoder.disasm(original,addr))
    gi=list(decoder.disasm(generated,addr))
    need(len(original)==len(generated)==size
         and len(ni)==len(gi)==info['x86']
         and sum(x.size for x in ni)==sum(x.size for x in gi)==size
         and ni[-1].mnemonic==gi[-1].mnemonic=='ret'
         and all((x.address,x.size,x.mnemonic)==(y.address,y.size,y.mnemonic)
                 for x,y in zip(ni,gi)),
         f'{addr:#x} {mode}: original full native ctor length/x86 geometry changed')
    refs=info['fields']
    need(len(fields)==len(refs),
         f'{addr:#x} {mode}: missing genuine original physical PE/COFF fields')
    linked=bytearray(generated)
    receipts=[]
    for off,(kind,target,symbol) in refs.items():
        matching=[f for f in fields if f['offset']==off]
        need(len(matching)==1
             and matching[0]['type']==kind
             and matching[0]['addend']==0
             and matching[0]['symbol']==symbol
             and matching[0]['local_symbol_offset'] is None,
             f'{addr:#x} {mode}: native constructor source COFF field symbol/type at+{off:#x} differs')
        val=(target if kind=='DIR32' else (target-addr-off-4)&0xFFFFFFFF)
        actual=struct.unpack_from('<I',original,off)[0]
        need(actual==val and generated[off:off+4]==b'\x00'*4,
             f'{addr:#x} {mode}: actual original PE target {target:#x} at physical +{off:#x} differs')
        instr=next((x for x in ni if x.address<=addr+off<x.address+x.size),None)
        need(instr is not None and instr.mnemonic==('call' if kind=='REL32' else 'mov'),
             f'{addr:#x} {mode}: original physical typed field not actually a native call/vtable MOV')
        struct.pack_into('<I',linked,off,val)
        receipts.append({'true_original_byte_offset':off,
                         'actual_original_native_PE_target':f'0x{target:08X}',
                         'real_native_x86_relocation_type':kind,
                         'ordinary_VC71_COFF_symbol':symbol,
                         'unlinked_source_addend_zero':True})
    need(bytes(linked)==original,
         f'{addr:#x} {mode}: genuine whole native original CODE bytes differ after actual PE target resolution')
    nonfield=size-4*len(refs)
    need(sum(original[i]==generated[i] for i in range(size)
             if not any(off<=i<off+4 for off in refs))==nonfield,
         f'{addr:#x} {mode}: whole native source nonrelocation bytes not identical')
    return {'actual_original_complete_function':f'0x{addr:08X}',
            'independent_natural_source_hypothesis':mode,
            'original_complete_NATIVE_CODE_bytes_identical':size,
            'original_complete_native_x86_instructions':info['x86'],
            'original_true_CO_FF_fields':len(refs),
            'original_linked_complete_function_machine_bytes_equal':True,
            'physical_original_vtable_member_ctor_source_fields':receipts,
            'original_source_authorship':'unknown',
            'new_accepted_whole_authored_CODE_bytes':0}


def original_callers(reader,pe,decoder):
    with (ROOT/'config/functions.csv').open(newline='') as stream:
        functions=list(csv.DictReader(stream))
    with (ROOT/'config/function-origins.csv').open(newline='') as stream:
        origin={x['address']:x for x in csv.DictReader(stream)}
    need(len(functions)==4351,
         'pinned original registered whole function extent count changed')
    for addr in CASES:
        row=origin[f'0x{addr:08X}']
        need(row['origin']=='unknown' and row['disposition']=='review',
             f'{addr:#x}: original historical native ctor origin is no longer pending review')
    graph={addr:[] for addr in CASES}
    for row in functions:
        addr=int(row['address'],16)
        for ins in decoder.disasm(reader.pe_bytes_at(pe,addr,int(row['size'])),addr):
            if ins.mnemonic=='call' and ins.op_str.startswith('0x'):
                target=int(ins.op_str,16)
                if target in graph:
                    graph[target].append({'actual_original_native_CALL':f'0x{ins.address:08X}',
                                          'actual_original_entire_caller':row['address'],
                                          'current_caller_origin':row['owner'],
                                          'caller_provisional_name':row['proposed_name']})
    for addr,info in CASES.items():
        count=len(graph[addr])
        authors=sum(x['current_caller_origin']=='authored' for x in graph[addr])
        need(count==info['actual_calls'] and authors==info['authored_calls'],
             f'{addr:#x}: actual original native game call graph differs: {count}/{authors}')
    return graph


def main():
    reader=load_reader()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    explicit=compile_one('explicit',EXPLICIT)
    implicit=compile_one('implicit',IMPLICIT)
    results=[]
    for mode,obj in (('explicit',explicit),('compiler-implicit',implicit)):
        for addr,info in CASES.items():
            receipt=check_whole(reader,pe,decoder,obj,addr,info,mode)
            results.append(receipt)
            print(f'F638 {mode} original {addr:#010x}: entire {info["bytes"]}/'
                  f'{info["bytes"]} genuine native CODE bytes, '
                  f'{info["x86"]}/{info["x86"]} x86, '
                  f'{len(info["fields"])} physical true PE-targeted typed COFF fields. '
                  'Original explicit-vs-generated source origin UNKNOWN.',flush=True)
    graph=original_callers(reader,pe,decoder)
    summary={'original_pinned_PE_SHA256':hashlib.sha256(pe).hexdigest(),
             'original_vc71_compiler_profile':'/Od /Ob0 /Gy /GR- /GX- /GS /Zi',
             'original_explicit_source_SHA256':hashlib.sha256(EXPLICIT.read_bytes()).hexdigest(),
             'original_compiler_implicit_source_SHA256':hashlib.sha256(IMPLICIT.read_bytes()).hexdigest(),
             'each_original_native_function_verified_in_two_independent_source_hypotheses':results,
             'real_original_registered_native_function_extents_scanned':4351,
             'independently_actual_native_game_CALLs':{f'0x{a:08X}':rows for a,rows in graph.items()},
             'distinct_new_real_original_full_source_backed_native_functions':len(CASES),
             'distinct_native_complete_CODE_bytes_uncredited':sum(x['bytes'] for x in CASES.values()),
             'new_accepted_whole_authored_functions':0,
             'new_accepted_whole_authored_CODE_bytes':0,
             'full_all_unit_cold_replay':False}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F638: four distinct full original native game-facing constructors, '
          f'{summary["distinct_native_complete_CODE_bytes_uncredited"]} original whole CODE bytes, '
          f'{sum(x["x86"] for x in CASES.values())} native x86, '
          f'{sum(len(x["fields"]) for x in CASES.values())} physical typed original COFF; '
          'two independent explicit/implicit VC7.1 sources byte-match all. '
          'ZERO new accepted authored units, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F638 actual original TH075 game constructor PE/COFF source verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
