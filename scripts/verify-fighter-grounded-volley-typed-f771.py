#!/usr/bin/env python3
"""F771: one whole TH075 00543210 native fighter build for real 2FB X/Y.

Native complete 2FB 647B/181 x86/17 original PE/COFF fields, all natural
mnemonics and widths, but 111 real GPR/operand byte differences remain.
This is not separately callable exact game CODE; no 975-unit replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f771-fighter-grounded-volley-whole'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
CASE=(0x00550D97,0x0055101E,647,181,17)


def need(ok,message):
    if not ok:raise ValueError(message)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing independent source/PE reader '+path)
    obj=importlib.util.module_from_spec(sp);sys.modules[tag]=obj;sp.loader.exec_module(obj)
    return obj


def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F771-whole.cpp'
    obj=OUT/'Boss00543210-F771-whole.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'original whole fighter VC7.1 source compile failed '+(cp.stdout+cp.stderr)[-950:])
    return obj


def check_original_complete_case(rd,pe,d,code,fields,ins,mapper):
    lo,hi,size,nx,nref=CASE
    src0,src1=mapper[lo],mapper[hi]
    raw=rd.pe_bytes_at(pe,lo,size)
    original=list(d.disasm(raw,lo))
    new=[x for x in ins if src0<=x.address<src1]
    need(hi-lo==size and src1-src0==size and len(original)==len(new)==nx
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(original,new)),
         'original entire 2FB 647-B/181 native x86 geometry not restored')
    refs=[x for x in fields if src0<=x['offset']<src1]
    need(len(refs)==nref,'2FB physical 17 native PE fields missing')
    mask=set()
    for ref in refs:
        pos=ref['offset']-src0
        ordinal=next((j for j,x in enumerate(new)
                      if x.address<=ref['offset']<x.address+x.size),None)
        need(ordinal is not None and ref['addend']==0
             and ref['local_symbol_offset'] is None
             and ref['type'] in ('DIR32','REL32')
             and all(0<=k<size and k not in mask for k in range(pos,pos+4)),
             '2FB genuine original typed PE/COFF field offset/addend/owner invalid')
        mask.update(range(pos,pos+4))
        original_op=original[ordinal]
        need(original_op.mnemonic==new[ordinal].mnemonic
             and ref['type']==('REL32' if original_op.mnemonic=='call' else 'DIR32'),
             '2FB original PE/COFF owner mnemonic or type mismatch')
        word=int.from_bytes(raw[pos:pos+4],'little')
        dst=word if ref['type']=='DIR32' else lo+pos+4+(word if word<2**31 else word-2**32)
        m=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',ref['symbol'])
        expected=int(m.group(1),16) if m else (0x006406AC if ref['symbol']=='__ftol2' else None)
        need(expected is not None and expected==dst,
             f'2FB original PE destination {dst:#x} differs source symbol {ref["symbol"]}')
    jumps=set();count=0;valid={x.address for x in ins}
    for a,b in zip(original,new):
        if a.mnemonic=='jmp' and a.op_str=='0x5515c2':
            need(a.size==b.size==5 and b.mnemonic=='jmp' and int(b.op_str,16) in valid,
                 '2FB actual native parent tail exit not preserved')
            jumps.update(range(b.address-src0+1,b.address-src0+5));count+=1
    bad=[i for i in range(size) if i not in mask and i not in jumps and raw[i]!=code[src0+i]]
    need(len(bad)==111,'2FB genuine remaining wrong register byte count changed '+str(len(bad)))
    for idx in (64,65,75,76):
        need(original[idx].mnemonic==new[idx].mnemonic,
             'actual native MOV-before-FLD argument evaluation incorrect')
    return {'native_game_case':'0x2FB','native_and_source_complete_CODE_B':size,
            'original_and_source_x86_opcode_width_positions':nx,
            'genuine_zero_addend_native_PE_COFF_references':nref,
            'native_mnemonic_errors':0,'native_x87_MOV_before_FLD_restored':True,
            'genuine_nonfield_operand_bad_bytes_NOT_EXACT':len(bad),
            'first_native_bad_byte_offsets':bad[:18],
            'parent_shared_tail_JMPs_nonmatching':count,
            'whole_original_game_function_exact':False}


def main():
    f759=load('f771_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f760=load('f771_f760','scripts/verify-fighter-complex-stage-cc-ce-f760.py')
    f762=load('f771_f762','scripts/verify-fighter-typed-returns-f762.py')
    f764=load('f771_f764','scripts/verify-fighter-approach-volley-native-f764.py')
    f767=load('f771_f767','scripts/verify-fighter-angle-storm-typed-f767.py')
    f768=load('f771_f768','scripts/verify-fighter-storm-volley-typed-f768.py')
    f734=load('f771_f734','scripts/verify-fighter-eight-round-f734.py')
    rd=load('f771_reader','scripts/compare-coff-function.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    src,boss=f762.make_parent(f759)
    for old,new in [
        ('#include "FighterApproachPhaseF715.inc"','#include "FighterApproachNativeF763.inc"'),
        ('#include "FighterApproachVolleyF699.inc"','#include "FighterApproachVolleyNativeF764.inc"'),
        ('#include "FighterAngleStormF684.inc"','#include "FighterAngleStormTypedF767.inc"'),
        ('#include "FighterStormVolleyF681.inc"','#include "FighterStormVolleyTypedF768.inc"'),
        ('#include "FighterGroundedVolleyF696.inc"','#include "FighterGroundedVolleyTypedF771.inc"')]:
        need(src.count(old)==1,'original whole fighter source include not in true parent '+old)
        src=src.replace(old,new)
    anchor='void FighterSwitchF598_Boss00543210::Advance() {'
    need(src.count(anchor)==1,'actual whole native member definition missing')
    src=src.replace(anchor,'#include "FighterBorrowedXYViewF771.hpp"\n'+anchor)
    obj=compile_one(src)
    code,refs=rd.object_function(obj,SYM)
    ins=f760.code_instructions(d,code)
    end=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and boss['postret_size']==943 and end==58261
         and len(code)==end+943,'whole source still nonexact and switch DATA extent changed')
    mapper=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    new=check_original_complete_case(rd,pe,d,code,refs,ins,mapper)
    f2f8=f768.verify_original_2f8(rd,pe,d,code,refs,ins,mapper)
    f2f9=f767.verify_native_2f9(rd,pe,d,code,refs,ins,mapper)
    f2fa=f764.whole_game_native_2fa(rd,pe,d,code,refs,ins,mapper)
    f2db=f762.original_case(rd,pe,d,code,refs,ins,mapper,0x2DB,
             (0x0054E451,0x0054E851,1024,290,34))
    previous=[f762.original_case(rd,pe,d,code,refs,ins,mapper,k,rec)
              for k,rec in f762.ORIGINAL.items()]
    c8,tail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapper,
             {0xC8:0x0054737F,0xC9:0x0054756F,0xCA:0x00547717,
              0xCB:0x005478CE,0xCC:0x00547A8B})
    cc=[f760.physical_case(rd,pe,d,code,refs,ins,mapper,k,rec,check_targets=True)
        for k,rec in f760.ORIG.items()]
    after=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    result={'original_entire_game_function':'0x00543210',
            'original_whole_CODE_B':58294,'new_whole_compiled_CODE_B':end,
            'original_whole_CODE_deficit_B':58294-end,
            'new_original_2FB_full_case_nonexact_source':new,
            'reverified_original_2F8':f2f8,'reverified_original_2F9':f2f9,
            'reverified_original_2FA':f2fa,'reverified_original_2DB':f2db,
            'reverified_original_1F6_1F7_1F8':previous,
            'reverified_original_C8_CB':c8,'reverified_original_CC_CD_CE':cc,
            'reverified_original_afterRET_DATA':after,
            'whole_original_game_byte_exact':False,
            'new_formal_callable_CODE_credit':0,'all_units_cold_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F771 original full 2FB: 647B /181 native x86/17 genuine PE fields; '
          'four wrong MOV/FLD opcodes restored; 111 true operand bytes STILL WRONG',flush=True)
    print('F771 whole original 00543210 58261/58294 CODE B and 943-B separate DATA; '
          'NOT whole exact, no split-case credit or all-unit replay',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F771 original 58KB game source/PE verification FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
