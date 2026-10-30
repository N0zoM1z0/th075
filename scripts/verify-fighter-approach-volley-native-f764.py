#!/usr/bin/env python3
"""F764: genuine 2FA 971B/279x86 full-action opcode grammar, still NONEXACT.

Freshly compile ONE entire 58KB VC7.1 fighter, verify 31 original physical
PE/COFF references, all native opcode starts/widths and explicitly report
156 genuine nonfield operand-byte negatives. No split-case game CODE credit.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f764-approach-volley-whole'
BASE=0x00543210
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
ORIG=(0x005509CC,0x00550D97,971,279,31)


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(tag,path):
    spec=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing whole-source verifier '+path)
    x=importlib.util.module_from_spec(spec)
    sys.modules[tag]=x
    spec.loader.exec_module(x)
    return x


def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F764-full.cpp';obj=OUT/'Boss00543210-F764-full.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'normal original entire VC7.1 source failed '+(cp.stdout+cp.stderr)[-950:])
    return obj


def whole_game_native_2fa(rd,pe,d,code,refs,ins,mapper):
    lo,hi,size,nx,nrefs=ORIG
    start,end=mapper[lo],mapper[hi]
    real=rd.pe_bytes_at(pe,lo,size)
    native=list(d.disasm(real,lo))
    generated=[x for x in ins if start<=x.address<end]
    need(hi-lo==size and end-start==size and len(native)==len(generated)==nx
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(native,generated)),
         'F764 2FA whole original 971 CODE B/279 exact opcode geometry missing')
    fields=[r for r in refs if start<=r['offset']<end]
    need(len(fields)==nrefs,'original 2FA 31 physically typed PE fields missing')
    fieldmask=set()
    for field in fields:
        off=field['offset']-start
        owner=next((j for j,x in enumerate(generated) if
                     x.address<=field['offset']<x.address+x.size),None)
        need(owner is not None and field['addend']==0 and field['local_symbol_offset'] is None
             and field['type'] in ('DIR32','REL32')
             and all(0<=k<size and k not in fieldmask for k in range(off,off+4)),
             '2FA genuine native PE/COFF owner malformed or overlapping')
        fieldmask.update(range(off,off+4))
        original_op=native[owner]
        need(original_op.mnemonic==generated[owner].mnemonic
             and field['type']==('REL32' if original_op.mnemonic=='call' else 'DIR32'),
             'native original 2FA COFF relocation type or x86 owner differs')
        raw=int.from_bytes(real[off:off+4],'little')
        dest=(raw if field['type']=='DIR32' else
              lo+off+4+(raw if raw<2**31 else raw-2**32))
        found=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',field['symbol'])
        expected=(int(found.group(1),16) if found else
                  0x006406AC if field['symbol']=='__ftol2' else None)
        need(expected is not None and expected==dest,
             f'2FA native original PE destination {dest:#x} contradicts source {field["symbol"]}')
    jmps=set();exits=0;parents={x.address for x in ins}
    for i,(a,b) in enumerate(zip(native,generated)):
        if a.mnemonic=='jmp' and a.op_str=='0x5515c2':
            need(a.size==b.size==5 and b.mnemonic=='jmp'
                 and int(b.op_str,16) in parents,
                 'native original 2FA external shared-tail jump not genuine')
            exits+=1
            jmps.update(range(b.address-start+1,b.address-start+5))
    wrong=[i for i in range(size) if i not in fieldmask and i not in jmps
           and real[i]!=code[start+i]]
    need(len(wrong)==156,
         f'original 2FA real GPR/operand mismatch count changed {len(wrong)}; do not promote')
    return {'real_original_case':'0x2FA',
            'complete_original_and_generated_CODE_B':size,
            'exact_original_x86_mnemonic_width_ordinals':nx,
            'original_physically_targeted_zero_addend_COFF_fields':nrefs,
            'real_other_nonfield_byte_mismatches_NOT_EXACT':len(wrong),
            'first_bad_original_CODE_offsets':wrong[:16],
            'real_unmatched_parent_exit_JMPs':exits,
            'native_original_case_byte_exact':False}


def main():
    f759=load('f764_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f760=load('f764_f760','scripts/verify-fighter-complex-stage-cc-ce-f760.py')
    f762=load('f764_f762','scripts/verify-fighter-typed-returns-f762.py')
    f734=load('f764_f734','scripts/verify-fighter-eight-round-f734.py')
    rd=load('f764_reader','scripts/compare-coff-function.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    source,boss=f762.make_parent(f759)
    old='#include "FighterApproachPhaseF715.inc"'
    need(source.count(old)==1,'native original 2DB physical source missing')
    source=source.replace(old,'#include "FighterApproachNativeF763.inc"')
    old='#include "FighterApproachVolleyF699.inc"'
    need(source.count(old)==1,'original 2FA source not inserted at genuine case')
    source=source.replace(old,'#include "FighterApproachVolleyNativeF764.inc"')
    obj=compile_one(source)
    code,refs=rd.object_function(obj,SYM)
    ins=f760.code_instructions(d,code)
    ret=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and ret==58261 and len(code)==ret+943,
         'real full giant original size deficit after actual 2FA float correction differs')
    mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    f2fa=whole_game_native_2fa(rd,pe,d,code,refs,ins,mapping)
    f2db=f762.original_case(rd,pe,d,code,refs,ins,mapping,0x2DB,
             (0x0054E451,0x0054E851,1024,290,34))
    earlier=[f762.original_case(rd,pe,d,code,refs,ins,mapping,c,r)
             for c,r in f762.ORIGINAL.items()]
    prev,tail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapping,
             {0xC8:0x0054737F,0xC9:0x0054756F,0xCA:0x00547717,
              0xCB:0x005478CE,0xCC:0x00547A8B})
    ccs=[f760.physical_case(rd,pe,d,code,refs,ins,mapping,c,r,check_targets=True)
         for c,r in f760.ORIG.items()]
    after=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    report={'original_authored_whole_function':'0x00543210',
            'real_whole_original_CODE_bytes':58294,
            'real_generated_whole_CODE_bytes':ret,
            'still_missing_whole_original_CODE_B':58294-ret,
            'F764_new_2FA_correct_mnemonic_widths_NONEXACT_156_GPR':f2fa,
            'prior_F763_2DB_original_strict':f2db,
            'previous_three_complete_1F6_1F7_1F8':earlier,
            'complete_original_C8_CB':prev,'complete_original_CC_CD_CE':ccs,
            'original_separate_jump_DATA':after,
            'original_whole_game_function_exact':False,
            'new_accepted_callable_game_CODE_B':0,
            'all_accepted_units_cold_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F764 2FA complete 971B/279 native x86/31 original PE-COFF refs; '
          'ALL native mnemonic/width positions, 156 genuine nonfield bytes STILL WRONG',flush=True)
    print('F764 entire boss source 58261/58294 original CODE B; '
          'whole authored game function NONEXACT, no all-unit cold replay',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F764 full original PE/COFF proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
