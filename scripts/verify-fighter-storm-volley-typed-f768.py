#!/usr/bin/env python3
"""F768 one whole fighter source PE proof: native 2F8 FILD/FSUBR recovery.

Freshly compile ONLY one affected real 00543210-shaped giant; 2F8 retains
166 real nonfield GPR differences and whole original fighter is NONEXACT.
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
OUT=ROOT/'.analysis/f768-fighter-storm-whole'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
CASE=(0x005500D5,0x00550475,928,252,23)


def need(ok,why):
    if not ok:raise ValueError(why)


def load(tag,relative):
    spec=importlib.util.spec_from_file_location(tag,ROOT/relative)
    need(spec and spec.loader,'missing original full-owner PE helper '+relative)
    mod=importlib.util.module_from_spec(spec)
    sys.modules[tag]=mod;spec.loader.exec_module(mod)
    return mod


def cold_one(src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F768-full.cpp';obj=OUT/'Boss00543210-F768-full.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'actual VC7.1 whole fighter build failed '+(cp.stdout+cp.stderr)[-850:])
    return obj


def verify_original_2f8(rd,pe,d,code,refs,ins,mapping):
    lo,hi,size,nx,nref=CASE
    a,b=mapping[lo],mapping[hi]
    original_code=rd.pe_bytes_at(pe,lo,size)
    orig=list(d.disasm(original_code,lo))
    gen=[x for x in ins if a<=x.address<b]
    need(hi-lo==size and b-a==size and len(orig)==len(gen)==nx
         and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(orig,gen)),
         'original 2F8 928 native CODE B/252 exact opcode geometry not recovered')
    fields=[x for x in refs if a<=x['offset']<b]
    need(len(fields)==nref,'real 2F8 23 actual PE relocations missing')
    mask=set()
    for ref in fields:
        off=ref['offset']-a
        owner=next((j for j,x in enumerate(gen)
                    if x.address<=ref['offset']<x.address+x.size),None)
        need(owner is not None and ref['addend']==0 and ref['local_symbol_offset'] is None
             and ref['type'] in ('DIR32','REL32')
             and all(0<=k<size and k not in mask for k in range(off,off+4)),
             'original 2F8 original PE/COFF owner/field/addend not authentic')
        mask.update(range(off,off+4))
        original_owner=orig[owner]
        need(original_owner.mnemonic==gen[owner].mnemonic
             and ref['type']==('REL32' if original_owner.mnemonic=='call' else 'DIR32'),
             'original 2F8 COFF owner mnemonic/type differs')
        word=int.from_bytes(original_code[off:off+4],'little')
        linked=(word if ref['type']=='DIR32' else
                lo+off+4+(word if word<2**31 else word-2**32))
        m=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',ref['symbol'])
        need(m is not None and linked==int(m.group(1),16),
             f'2F8 physical native target {linked:#x} contradicts COFF symbol {ref["symbol"]}')
    tails=set();count=0;native_starts={x.address for x in ins}
    for j,(original,source) in enumerate(zip(orig,gen)):
        if original.mnemonic=='jmp' and original.op_str=='0x5515c2':
            need(original.size==source.size==5 and source.mnemonic=='jmp'
                 and int(source.op_str,16) in native_starts,
                 'native 2F8 original parent shared-tail call/branch not preserved')
            count+=1;tails.update(range(source.address-a+1,source.address-a+5))
    wrong=[i for i in range(size) if i not in mask and i not in tails
           and original_code[i]!=code[a+i]]
    need(len(wrong)==166,
         f'2F8 actual wrong original operand bytes {len(wrong)} differ from measured 166; NOT exact')
    need(orig[39].mnemonic=='movsx' and orig[42].mnemonic=='fild'
         and orig[44].mnemonic=='fsubr'
         and all(orig[i].mnemonic==gen[i].mnemonic for i in range(39,45)),
         'real original 2F8 integer-first FILD/FSUBR ordering not recovered')
    return {'native_2F8_entire_action_CODE_B':size,
            'source_and_native_x86_mnemonic_width_positions':nx,
            'physical_original_PE_COFF_relocations':nref,
            'native_integer_FILD_reverse_subtract_grammar':True,
            'actual_original_nonfield_GPR_byte_differences_NOT_EXACT':len(wrong),
            'first_original_wrong_byte_offsets':wrong[:20],
            'original_external_shared_tail_JMPs_still_NONEXACT':count,
            'entire_original_game_function_exact':False}


def main():
    f759=load('f768_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f760=load('f768_f760','scripts/verify-fighter-complex-stage-cc-ce-f760.py')
    f762=load('f768_f762','scripts/verify-fighter-typed-returns-f762.py')
    f764=load('f768_f764','scripts/verify-fighter-approach-volley-native-f764.py')
    f767=load('f768_f767','scripts/verify-fighter-angle-storm-typed-f767.py')
    f734=load('f768_f734','scripts/verify-fighter-eight-round-f734.py')
    rd=load('f768_rd','scripts/compare-coff-function.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    source,boss=f762.make_parent(f759)
    for old,new in [
       ('#include "FighterApproachPhaseF715.inc"','#include "FighterApproachNativeF763.inc"'),
       ('#include "FighterApproachVolleyF699.inc"','#include "FighterApproachVolleyNativeF764.inc"'),
       ('#include "FighterAngleStormF684.inc"','#include "FighterAngleStormTypedF767.inc"'),
       ('#include "FighterStormVolleyF681.inc"','#include "FighterStormVolleyTypedF768.inc"')]:
        need(source.count(old)==1,'missing original full giant game source '+old)
        source=source.replace(old,new)
    obj=cold_one(source)
    code,refs=rd.object_function(obj,SYM)
    ins=f760.code_instructions(d,code)
    ret=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and boss['postret_size']==943 and ret==58261
         and len(code)==ret+943,
         'whole original fighter still not exact; original source extent changed')
    mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    original_2f8=verify_original_2f8(rd,pe,d,code,refs,ins,mapping)
    original_2f9=f767.verify_native_2f9(rd,pe,d,code,refs,ins,mapping)
    original_2fa=f764.whole_game_native_2fa(rd,pe,d,code,refs,ins,mapping)
    earlier=[f762.original_case(rd,pe,d,code,refs,ins,mapping,act,record)
             for act,record in f762.ORIGINAL.items()]
    original_2db=f762.original_case(rd,pe,d,code,refs,ins,mapping,0x2DB,
       (0x0054E451,0x0054E851,1024,290,34))
    c8,tail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapping,
       {0xC8:0x0054737F,0xC9:0x0054756F,0xCA:0x00547717,
        0xCB:0x005478CE,0xCC:0x00547A8B})
    cc=[f760.physical_case(rd,pe,d,code,refs,ins,mapping,act,rec,check_targets=True)
        for act,rec in f760.ORIG.items()]
    after=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    proof={'whole_original_game_boss':'0x00543210','original_game_CODE_B':58294,
           'source_game_CODE_B':ret,'remaining_CODE_B_shortfall':58294-ret,
           'F768_original_2F8_x87_correct_but_registers_nonexact':original_2f8,
           'F767_2F9_249_wrong_real_bytes':original_2f9,
           'F764_2FA_156_wrong_real_bytes':original_2fa,
           'F763_2DB_strict_native':original_2db,
           'F762_three_strict_real_1F6_1F7_1F8':earlier,
           'F759_four_C8_CB':c8,'F760_three_CC_CD_CE':cc,
           'original_separate_943B_jump_DATA':after,
           'whole_original_callable_function_byte_exact':False,
           'new_formal_authored_game_CODE_byte_credit':0,
           'all_existing_cold_units_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(proof,indent=2)+'\n')
    print('F768 original complete 2F8: 928 native CODE B/252 x86/23 typed'
          ' PE fields, ZERO opcode/size wrong; genuine 166 GPR operand bytes NONEXACT',flush=True)
    print('F768 original 00543210 parent: 58261/58294 CODE B; original'
          ' 2F9 GPR 249 and 2FA GPR 156 still wrong, not whole exact',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F768 complete original fighter PE/COFF FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
