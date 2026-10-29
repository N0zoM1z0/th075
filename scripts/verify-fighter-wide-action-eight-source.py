#!/usr/bin/env python3
"""F559: genuine complete action8 inside wide-EBP giant fighter 00564BE0.

Rebuild one natural VC7.1 fighter-source diagnostic TU, rechecking actions
6/7/8 against the original whole SHA-verified boss and complete native
switch DATA. No source padding, original CODE grafting, partial exact
credit or all-unit cold replay.
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
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
OUT=ROOT/'.analysis/f559-wide-action8-source'
ADDRESS=0x00564BE0
TAG='Boss00564BE0'
ORIGINAL_SHA='bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98'


def need(ok,why):
    if not ok:raise ValueError(why)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,f'missing original native source evidence reader {path}')
    mod=importlib.util.module_from_spec(spec);sys.modules[name]=mod;spec.loader.exec_module(mod)
    return mod


def original_eight(reader,pe,decoder,boss,old):
    table=boss['tables'][0]
    need(table['slots']==11 and table['map_addr'] is None and boss['jump_count']==7,
         'not original seven-table fighter')
    data=reader.pe_bytes_at(pe,table['dense_addr']+32,8)
    start,end=[int.from_bytes(data[i:i+4],'little') for i in (0,4)]
    need(boss['address']<start<end<boss['address']+boss['size'],
         'original action8 physical bounds outside full giant')
    ins=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    need(len(ins)==102 and end-start==458 and ins[0].address==start
         and ins[-1].address+ins[-1].size==end,
         'not native complete 458-byte 102-insn actor action8')
    need(ins[10].mnemonic=='cmp' and ins[10].op_str.endswith(', 4')
         and ins[16].mnemonic=='push' and ins[16].op_str=='0xce',
         'native action8 state trigger/argument changed')
    need(ins[78].mnemonic=='cmp' and ins[78].op_str.endswith(', 2'),
         'native action8 stage-two gate no longer matches original')
    need(ins[81].mnemonic=='mov' and ins[81].op_str.endswith(', 0xc0800000'),
         'original action8 float position -4.0f no longer observed')
    values=[old.literal_float(int(ins[k].op_str.rsplit(', ',1)[-1],16)) for k in (83,85)]
    need(values==['12.0f','0.4f'], 'native 0x54/0x5C original float initializers changed')
    need(ins[86].mnemonic=='mov' and ins[87].mnemonic=='movsx'
         and '+ 0x62' in ins[87].op_str,
         'original action8 contains a real flag clear or unexpected extra instruction')
    need(ins[-2].mnemonic=='call' and ins[-2].op_str=='dword ptr [edx]',
         'native action8 original virtual call dispatch changed')
    return ins


def source_for(orig6,orig7,report,mapped,reader,pe,decoder,boss,
               stage_source,core,opening,switch,zero,one):
    full=stage_source.generate(TAG,orig6,orig7,report,mapped,reader,pe,decoder,boss,
                               core,opening,switch,zero,one)
    normal=core.generate_source(TAG,orig6[1]['stage'],orig6[1]['floats'],
                                report,mapped,opening,switch,zero,one,reader,pe,decoder,boss)
    begin='case 0x6:';end='case 0x7: g_FighterProbeMarker = 8; break;'
    need(normal.count(begin)==1 and normal.count(end)==1,
         'prior natural original action6 core not available for no-flag action8')
    cloned=normal[normal.index(begin):normal.index(end)]
    need(cloned.count('U8(0x511) == 3')==1
         and cloned.count('SetNativeActionAt40FAC0(0xCC)')==1
         and cloned.count('POS = 0.0f;')==1
         and cloned.count('                    FLAG = 0;')==1,
         'native original 104-insn core source expression order changed')
    cloned=(cloned.replace(begin,'case 0x8:',1)
            .replace('U8(0x511) == 3','U8(0x511) == 4')
            .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCE)')
            .replace('POS = 0.0f;','POS = -4.0f;')
            .replace('                    FLAG = 0;\n',''))
    need('FLAG = 0;' not in cloned,'source still includes nonexistent native action8 flag clear')
    label='case 0x8: g_FighterProbeMarker = 9; break;'
    need(full.count(label)==1,'native whole fighter no longer has unique case8')
    full=full.replace(label,cloned.rstrip())
    old_name=f'FighterSwitchF557_{TAG}'
    need(full.count(old_name)>=2,'borrowed original-backed stage source name changed')
    return full.replace(old_name,f'FighterSwitchF559_{TAG}')


def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00564BE0-wide-action8.cpp'
    obj=OUT/'Boss00564BE0-wide-action8.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     cwd=ROOT,env=env,text=True,capture_output=True,timeout=120)
    (OUT/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,f'original VC7.1 selected-only compile failed: {p.stderr}')
    return obj


def candidate(reader,decoder,obj,boss):
    code,refs=reader.object_function(obj,
                   '?Advance@FighterSwitchF559_Boss00564BE0@@QAEXXZ')
    allins=[]
    for x in decoder.disasm(code,0):
        allins.append(x)
        if x.mnemonic=='ret':break
    need(allins and allins[-1].mnemonic=='ret','no generated native switch normal RET')
    ret=allins[-1].address+allins[-1].size
    need(len(code)-ret==boss['postret_size'],
         'native original entire after-RET physical DATA shape changed')
    refs4=sorted((r for r in refs if ret+24<=r['offset']<ret+40),key=lambda r:r['offset'])
    need(len(refs4)==4 and all(r['type']=='DIR32' and r['offset']==ret+24+4*i
         and r['local_symbol_offset'] is not None for i,r in enumerate(refs4)),
         'missing original source physical switch DWORD case6/7/8/9 refs')
    points=[r['local_symbol_offset'] for r in refs4]
    need(points==sorted(set(points)) and 0<=points[0]<points[-1]<ret,
         'candidate original action8 cases overlap or leave normal CODE')
    result=[]
    for k,expected in enumerate((115,115,102)):
        a,e=points[k:k+2]
        ins=list(decoder.disasm(code[a:e],a))
        length=(393,393,352)[k]
        need(len(ins)==expected and sum(i.size for i in ins)==length,
             'candidate complete normal native C++ case instruction/length differs')
        result.append(ins)
    return code,refs,allins,ret,result


def verify_original_case8_refs(native,candidate,refs,core):
    # F548's six actual COFF refs appear at the same physical instruction
    # ordinals in the 102-insn source case; only its tail vtable ordinal is
    # 100 rather than the 104-insn parent's 102.
    need(len(native)==len(candidate)==102,
         'new C++ case does not match full native action8 instruction count')
    for ordinal,(mnemonic,typ,target,symbol) in core.ORIGINAL_REFS.items():
        n,c=native[ordinal],candidate[ordinal]
        need(n.mnemonic==c.mnemonic==mnemonic,
             f'original case8 real relocation instruction {ordinal} moved')
        want=(f'0x{target:x}' if typ=='REL32' else f'dword ptr [0x{target:x}]')
        need(n.op_str==want,'native original call/float target identity changed')
        found=[r for r in refs if c.address<=r['offset']<c.address+c.size]
        need(len(found)==1 and found[0]['type']==typ and symbol in found[0]['symbol'],
             'candidate COFF physical typed source symbol differs at original native ordinal')
    a,e=candidate[0].address,candidate[-1].address+candidate[-1].size
    need(len([r for r in refs if a<=r['offset']<e])==6,
         'new native 102-insn case has extra or missing original COFF relocations')
    need(native[-2].mnemonic==candidate[-2].mnemonic=='call'
         and native[-2].op_str==candidate[-2].op_str=='dword ptr [edx]',
         'native physical virtual indirect method call not compiled from real C++')
    return 6


def main():
    reader=module('f559_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f559_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f559_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f559_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f559_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    opening=module('f559_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    core=module('f559_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    stage=module('f559_stage',ROOT/'scripts/verify-fighter-stage-no-flag-source.py')
    extra=module('f559_extra',ROOT/'scripts/verify-fighter-extra-stage-action-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads(PINNED.read_text())['bosses'] if x['address']==ADDRESS)
    need(boss['size']==61872 and boss['postret_size']==874,
         'original giant function CODE or owned switch DATA extent changed')
    report,mapped=actions.report_boss(reader,pe,decoder,boss)
    original6=stage.original_case(reader,pe,decoder,boss,6,core)
    original7=stage.original_case(reader,pe,decoder,boss,7,core)
    original8=original_eight(reader,pe,decoder,boss,core)
    source=source_for(original6,original7,report,mapped,reader,pe,decoder,boss,
                      stage,core,opening,switch,zero,one)
    obj=compile_one(source)
    code,refs,inst,ret,candidates=candidate(reader,decoder,obj,boss)
    nrefs=0;wide=0;longjls=0
    for (native,policy),cand in zip((original6,original7),candidates[:2]):
        core.compare_grammar(native,cand)
        w,j=stage.verify_wide_encodings(native,cand,boss)
        wide+=w;longjls+=j
        nrefs+=extra.verify_physical_fields(native,cand,refs)
    core.compare_grammar(original8,candidates[2])
    diffs=[(k,a,b,a.size-b.size) for k,(a,b) in enumerate(zip(original8,candidates[2]))
           if a.size!=b.size]
    wide8=[q for q in diffs if q[3]==3 and q[1].mnemonic=='mov'
           and '[ebp - 0x88]' in q[1].op_str]
    branch8=[q for q in diffs if q[3]==4 and q[1].mnemonic=='jl'
             and q[2].mnemonic=='jl']
    need(len(wide8)==34 and len(branch8)==1 and len(diffs)==35
         and sum(q[3] for q in diffs)==106,
         'original 458-vs-352 case width not exactly 34 wide saved-owner loads + one JL')
    nrefs+=verify_original_case8_refs(original8,candidates[2],refs,core)
    need(nrefs==22,'full 115/115/102 native cases require 22 physical COFF fields')
    slots,indexbytes,maps=zero.verify_physical_tables(boss,report,pe,reader,
                                                       switch,inst,code,refs,ret)
    output={'boss':f'0x{ADDRESS:08X}','whole_original_CODE':boss['size'],
            'original_case_bytes':[508,508,458],
            'candidate_case_bytes':[393,393,352],
            'native_instruction_count':[115,115,102],
            'real_native_case_COFF_fields':nrefs,
            'wide_owner_loads_in_original':wide+len(wide8),
            'long_JL_expansions':longjls+len(branch8),
            'physical_original_switch_DWORD_COFF_fields':slots,
            'exact_original_sparse_bytes':indexbytes,
            'entire_original_postret_DATA_shape':len(code)-ret}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(output,indent=2)+'\n')
    print(f'{ADDRESS:#010x}: one complete 61,872-byte original fighter context; '
          '115+115+102 real native GPR/x87/branch instruction roles; '
          f'22/22 physical COFF fields, real original 508+508+458 bytes; '
          f'wide EBP-0x88 loads {output["wide_owner_loads_in_original"]} and '
          f'long JL expansions {output["long_JL_expansions"]}; '
          f'{slots} native switch DWORD slots and {indexbytes} exact sparse bytes')
    print('Fresh one-TU VC7.1 probe matched native structural geometry; '
          'NO full giant CODE/DATA exact credit or all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 wide action8 original C++ validation failed:',exc,file=sys.stderr)
        raise SystemExit(1)
