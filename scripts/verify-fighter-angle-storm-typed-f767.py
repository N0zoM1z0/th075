#!/usr/bin/env python3
"""F767: full-fighter 2F9 natural x87 angle source improvement, NOT exact.

Recompile precisely ONE full original 00543210 source-shaped VC7.1 parent,
then verify all 381 native 2F9 x86, 34 typed PE fields, 249 honest native
GPR/operand mismatches, downstream strict/nonexact cases and jump DATA.
"""
from pathlib import Path
import importlib.util
import json
import os
import re
import subprocess
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f767-fighter-angle-storm-whole'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
CASE=(0x00550475,0x005509CC,1367,381,34)


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(sp and sp.loader,'missing native original PE source verifier '+path)
    mod=importlib.util.module_from_spec(sp)
    sys.modules[tag]=mod;sp.loader.exec_module(mod)
    return mod


def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F767-full.cpp'
    obj=OUT/'Boss00543210-F767-full.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'selected whole giant source compile failed '+(cp.stdout+cp.stderr)[-1000:])
    return obj


def verify_native_2f9(rd,pe,d,code,refs,ins,mapper):
    lo,hi,size,nx,nrefs=CASE
    a,b=mapper[lo],mapper[hi]
    raw=rd.pe_bytes_at(pe,lo,size)
    orig=list(d.disasm(raw,lo))
    generated=[x for x in ins if a<=x.address<b]
    need(hi-lo==size and b-a==size and len(orig)==len(generated)==nx
         and all(x.mnemonic==y.mnemonic and x.size==y.size
                 for x,y in zip(orig,generated)),
         '2F9 original full 1367 CODE bytes/381 x86 opcode layout not restored')
    fields=[r for r in refs if a<=r['offset']<b]
    need(len(fields)==nrefs,'2F9 native original 34 true PE/COFF fields missing')
    mask=set()
    for r in fields:
        off=r['offset']-a
        instr=next((i for i,g in enumerate(generated)
                    if g.address<=r['offset']<g.address+g.size),None)
        need(instr is not None and r['addend']==0
             and r['local_symbol_offset'] is None and r['type'] in ('DIR32','REL32')
             and all(0<=k<size and k not in mask for k in range(off,off+4)),
             '2F9 genuine field position/owner/addend invalid')
        mask.update(range(off,off+4))
        original_owner=orig[instr]
        need(original_owner.mnemonic==generated[instr].mnemonic
             and r['type']==('REL32' if original_owner.mnemonic=='call' else 'DIR32'),
             '2F9 original PE/COFF owner or field kind changed')
        raw_value=int.from_bytes(raw[off:off+4],'little')
        target=raw_value if r['type']=='DIR32' else (
            lo+off+4+(raw_value if raw_value<2**31 else raw_value-2**32))
        found=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',r['symbol'])
        expected=int(found.group(1),16) if found else (
            0x006406AC if r['symbol']=='__ftol2' else None)
        need(expected is not None and expected==target,
             f'2F9 native original PE target {target:#x} differs {r["symbol"]}')
    jumpmask=set();exits=0;starts={x.address for x in ins}
    for j,(x,y) in enumerate(zip(orig,generated)):
        if x.mnemonic=='jmp' and x.op_str=='0x5515c2':
            need(x.size==y.size==5 and y.mnemonic=='jmp'
                 and int(y.op_str,16) in starts,
                 '2F9 genuine shared-parent tail reference differs')
            jumpmask.update(range(y.address-a+1,y.address-a+5));exits+=1
    bad=[i for i in range(size) if i not in mask and i not in jumpmask
         and raw[i]!=code[a+i]]
    need(len(bad)==249,
         f'2F9 exact original nonfield wrong-byte negative changed {len(bad)}')
    return {'native_action':'0x2F9','original_entire_case_CODE_B':size,
            'native_source_x86_mnemonic_and_size_positions':nx,
            'genuine_original_typed_PE_COFF_fields':nrefs,
            'real_original_nonfield_GPR_operand_wrong_bytes_NOT_EXACT':len(bad),
            'first_real_native_mismatching_offsets':bad[:20],
            'genuine_external_shared_tail_JMPs_NOT_EXACT':exits,
            'whole_case_nonfield_exact':False}


def main():
    f759=load('f767_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f760=load('f767_f760','scripts/verify-fighter-complex-stage-cc-ce-f760.py')
    f762=load('f767_f762','scripts/verify-fighter-typed-returns-f762.py')
    f764=load('f767_f764','scripts/verify-fighter-approach-volley-native-f764.py')
    f734=load('f767_f734','scripts/verify-fighter-eight-round-f734.py')
    rd=load('f767_reader','scripts/compare-coff-function.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    source,boss=f762.make_parent(f759)
    for old,new in [
        ('#include "FighterApproachPhaseF715.inc"','#include "FighterApproachNativeF763.inc"'),
        ('#include "FighterApproachVolleyF699.inc"','#include "FighterApproachVolleyNativeF764.inc"'),
        ('#include "FighterAngleStormF684.inc"','#include "FighterAngleStormTypedF767.inc"')]:
        need(source.count(old)==1,'missing actual original whole C++ case '+old)
        source=source.replace(old,new)
    obj=compile_one(source)
    code,refs=rd.object_function(obj,SYM)
    ins=f760.code_instructions(d,code)
    ret=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and boss['postret_size']==943 and ret==58261
         and len(code)==ret+943,
         'whole native fighter 33-B CODE deficit/data extent changed; not exact')
    mapper=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    f2f9=verify_native_2f9(rd,pe,d,code,refs,ins,mapper)
    f2fa=f764.whole_game_native_2fa(rd,pe,d,code,refs,ins,mapper)
    f2db=f762.original_case(rd,pe,d,code,refs,ins,mapper,0x2DB,
        (0x0054E451,0x0054E851,1024,290,34))
    earlier=[f762.original_case(rd,pe,d,code,refs,ins,mapper,act,record)
             for act,record in f762.ORIGINAL.items()]
    prev,tail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapper,
       {0xC8:0x0054737F,0xC9:0x0054756F,0xCA:0x00547717,
        0xCB:0x005478CE,0xCC:0x00547A8B})
    cc=[f760.physical_case(rd,pe,d,code,refs,ins,mapper,act,rec,check_targets=True)
        for act,rec in f760.ORIG.items()]
    after=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    report={'original_authored_whole_game_function':'0x00543210',
            'original_whole_CODE_B':58294,'current_one_full_parent_CODE_B':ret,
            'whole_native_GAME_CODE_deficit_B':58294-ret,
            'F767_original_2F9_complete_case_opcode_recovery':f2f9,
            'F764_rechecked_true_2FA_nonexact':f2fa,
            'F763_rechecked_strict_2DB':f2db,
            'F762_rechecked_native_1F6_1F7_1F8':earlier,
            'F759_rechecked_C8_CB':prev,'F760_rechecked_CC_CD_CE':cc,
            'original_afterRET_separate_DATA':after,
            'whole_game_function_byte_exact':False,
            'new_FORMAL_original_whole_function_CODE_credit':0,
            'all_accepted_units_cold_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F767 original 2F9 entire 1367B/381 native x86/34 genuine PE/COFF; '
          'ZERO opcode/width errors, 249 actual GPR/nonfield bytes STILL WRONG',flush=True)
    print('F767 original parent 58261/58294 native CODE B + 943B original DATA; '
          'whole fighter NONEXACT and zero new original callable CODE credit',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F767 complete original native source PE/COFF check FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
