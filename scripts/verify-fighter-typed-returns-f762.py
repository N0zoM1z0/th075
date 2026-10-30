#!/usr/bin/env python3
"""F762: physical original PE proof for real 05F/1F6/1F7/1F8 in one fighter.

Fresh VC7.1 compile of one full 58KB native-shaped parent. Verify 3,833
noncallable action CODE bytes /1,118 x86 /115 PE targets; do NOT grant
whole-function CODE credit while the enclosing giant remains nonexact.
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
OUT=ROOT/'.analysis/f762-typed-returns-whole'
BASE=0x00543210
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
ORIGINAL={0x1F6:(0x0054AB00,0x0054AF9D,1181,348,35),
          0x1F7:(0x0054AF9D,0x0054B43A,1181,348,35),
          0x1F8:(0x0054B43A,0x0054B9F9,1471,422,45)}
FACING=(0x0054550F,0x0054559F,144,44,3)


def need(ok,message):
    if not ok:raise ValueError(message)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing full native verification helper '+path)
    mod=importlib.util.module_from_spec(sp)
    sys.modules[tag]=mod
    sp.loader.exec_module(mod)
    return mod


def make_parent(f759):
    # The 4 earlier C8–CB and 3 CC–CE actual gameplay cases always remain
    # part of the ONE entire function. The real script F759 generator
    # carries all other previously reconstructed original states.
    r=load('f762_rd_for_src','scripts/compare-coff-function.py')
    acts=load('f762_act_for_src','scripts/report-fighter-action-handlers.py')
    from capstone import Cs,CS_ARCH_X86,CS_MODE_32
    pe=r.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==BASE)
    report,mapped=acts.report_boss(r,pe,d,boss)
    src=f759.full_source(r,pe,d,boss,report,mapped)
    for action in (0xCC,0xCD,0xCE):
        old=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(old)==1,'native original CC/CD/CE marker missing '+hex(action))
        src=src.replace(old,'#include "FighterComplexStageCC_CE_F760.inc"' if action==0xCC else '')
    old='        case 0x5F: g_FighterProbeMarker = 96; break;'
    need(src.count(old)==1,'original 05F game source marker missing')
    src=src.replace(old,'#include "FighterFacing05FF762.inc"')
    old='#include "FighterBoundaryReturnF729.inc"'
    need(src.count(old)==2,'original 1F6/1F7 direct physical C++ state pair absent')
    src=src.replace(old,'#include "FighterBoundaryReturnTypedF762.inc"')
    old='#include "FighterAimReturnF731.inc"'
    need(src.count(old)==1,'original 1F8 true source fragment absent')
    src=src.replace(old,'#include "FighterAimReturnTypedF762.inc"')
    need(src.count('#include "FighterFourDirectionalC8F759.inc"')==1
         and src.count('#include "FighterComplexStageCC_CE_F760.inc"')==1,
         'earlier 7 native whole game actions must be in full original giant')
    return src,boss


def compile_one(src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F762-full.cpp'
    obj=OUT/'Boss00543210-F762-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,'one whole parent VC7.1 build failed: '+(result.stdout+result.stderr)[-900:])
    return obj


def original_case(rd,pe,d,code,refs,ins,mapper,case,record):
    lo,hi,size,original_x86,nfields=record
    need(lo in mapper and hi in mapper and hi-lo==size,
         f'{case:#x}: complete source/PE original bounds not mapped')
    b0,b1=mapper[lo],mapper[hi]
    raw=rd.pe_bytes_at(pe,lo,size)
    orig=list(d.disasm(raw,lo))
    generated=[x for x in ins if b0<=x.address<b1]
    need(b1-b0==size and len(orig)==len(generated)==original_x86
         and all(x.mnemonic==y.mnemonic and x.size==y.size
                 for x,y in zip(orig,generated)),
         f'{case:#x}: complete original opcode/width/size not matched')
    fields=[ref for ref in refs if b0<=ref['offset']<b1]
    need(len(fields)==nfields,f'{case:#x}: PE/COFF true field count differs')
    mask=set()
    for ref in fields:
        off=ref['offset']-b0
        owner=next((i for i,x in enumerate(generated)
                    if x.address<=ref['offset']<x.address+x.size),None)
        need(owner is not None and ref['local_symbol_offset'] is None
             and ref['addend']==0 and ref['type'] in ('DIR32','REL32')
             and all(0<=k<size and k not in mask for k in range(off,off+4)),
             f'{case:#x}: invalid original relative field owner/overlap')
        mask.update(range(off,off+4))
        own=orig[owner]
        need(own.mnemonic==generated[owner].mnemonic
             and ref['type']==('REL32' if own.mnemonic=='call' else 'DIR32'),
             f'{case:#x}: physical original x86/COFF type not identical')
        word=int.from_bytes(raw[off:off+4],'little')
        dest=(word if ref['type']=='DIR32' else
              lo+off+4+(word if word<2**31 else word-2**32))
        m=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',ref['symbol'])
        expected=int(m.group(1),16) if m else (0x006406AC if ref['symbol']=='__ftol2' else None)
        need(expected is not None and dest==expected,
             f'{case:#x}: actual original PE relocation {dest:#x} mismatches {ref["symbol"]}')
    parent_starts={x.address for x in ins}
    tailmask=set();exits=0
    for i,(a,b) in enumerate(zip(orig,generated)):
        if a.mnemonic=='jmp' and a.op_str=='0x5515c2':
            need(a.size==b.size==5 and b.mnemonic=='jmp'
                 and int(b.op_str,16) in parent_starts,
                 f'{case:#x}: genuine external parent-tail branch missing')
            tailmask.update(range(b.address-b0+1,b.address-b0+5))
            exits+=1
    other=[i for i in range(size) if i not in mask and i not in tailmask
           and raw[i]!=code[b0+i]]
    need(not other,f'{case:#x}: nonfield native machine bytes mismatch: {other[:10]}')
    return {'original_case':f'0x{case:X}','entire_original_native_CODE_B':size,
            'original_x86_identical':original_x86,'authentic_original_PE_COFF_fields':nfields,
            'native_nonfield_nontail_bytes_identical':size-len(mask)-len(tailmask),
            'real_nonexact_external_shared_tail_JMPs':exits,
            'whole_original_game_function_exact':False}


def verify_facing(rd,pe,d,code,refs,ins,mapper):
    lo,hi,size,nx,nrefs=FACING
    orig=list(d.disasm(rd.pe_bytes_at(pe,lo,size),lo))
    s,e=mapper[lo],mapper[hi]
    gen=[x for x in ins if s<=x.address<e]
    fields=[x for x in refs if s<=x['offset']<e]
    need(len(gen)==len(orig)==nx and e-s==size and len(fields)==nrefs
         and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(orig,gen)),
         'original 05F 144B/44 x86 physical source grammar regressed')
    return {'case':'0x5F','native_and_source_CODE_B':size,'native_and_source_x86':nx,
            'physically_typed_refs':nrefs,
            'register_phase_still_NOT_EXACT':True}


def main():
    f759=load('f762_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f760=load('f762_f760','scripts/verify-fighter-complex-stage-cc-ce-f760.py')
    f734=load('f762_f734','scripts/verify-fighter-eight-round-f734.py')
    rd=load('f762_compare','scripts/compare-coff-function.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    src,boss=make_parent(f759)
    obj=compile_one(src)
    code,refs=rd.object_function(obj,SYM)
    ins=f760.code_instructions(d,code)
    ret=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and boss['postret_size']==943
         and ret==58277 and len(code)==ret+943,
         'original full source still 17 CODE bytes short, not whole exact')
    mapper=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    source=src
    facing=verify_facing(rd,pe,d,code,refs,ins,mapper)
    cases=[original_case(rd,pe,d,code,refs,ins,mapper,c,r) for c,r in ORIGINAL.items()]
    need(sum(x['entire_original_native_CODE_B'] for x in cases)==3833
         and sum(x['authentic_original_PE_COFF_fields'] for x in cases)==115
         and sum(x['original_x86_identical'] for x in cases)==1118,
         'original THREE complete game cases not fully recovered')
    native_c8,tail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapper,
                {0xC8:0x0054737F,0xC9:0x0054756F,0xCA:0x00547717,
                 0xCB:0x005478CE,0xCC:0x00547A8B})
    native_cc=[f760.physical_case(rd,pe,d,code,refs,ins,mapper,c,r,check_targets=True)
               for c,r in f760.ORIG.items()]
    afterret=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    proof={'native_game_whole_parent':'0x00543210',
           'native_original_CALLABLE_CODE_B':58294,
           'new_full_parent_compiled_CODE_B':ret,
           'remaining_full_GAME_CODE_deficit_B':boss['size']-ret,
           'new_authentic_complete_case_05F':facing,
           'three_genuine_native_1F6_1F7_1F8_CASES':cases,
           'prior_original_C8_CB_cases':native_c8,
           'prior_original_CC_CD_CE_cases':native_cc,
           'original_afterRET_jump_DATA':afterret,
           'entire_game_whole_function_exact':False,
           'new_FORMAL_authored_CODE_credit':0,
           'run_full_accepted_cold_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(proof,indent=2)+'\n')
    print('F762 real complete 1F6/1F7/1F8 3833 native CODE B /1118 x86 /115 typed fields; '
          'ZERO other CODE mismatches outside original shared-parent JMP and real PE COFF',flush=True)
    print('F762 whole fighter compiled 58277/58294 native CODE B, parent remains NONEXACT; '
          'no 971-unit cold replay or duplicate internal-case game CODE credit',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F762 entire original PE/COFF verification FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
