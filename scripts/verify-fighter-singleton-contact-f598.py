#!/usr/bin/env python3
"""F598: original singleton action 0x32 in all ELEVEN huge multi-switch fighters.

Re-read entire pinned original giant CODE and every after-RET jump table,
regenerate eleven real opening cases from existing original-backed F564,
F566, or F567 sources, insert natural C++ singleton 50, and compile ONLY
requested affected VC7.1 translation units. Compare all 58 original case
instructions, GPR/x87/CFG roles, original native case lengths, 7 real typed
COFF fields/targets and the entire seven-switch DATA geometry. The one
wide EBP-0x88 original is 256 bytes (17 x 3-byte wider MOVs), not the
205-byte compact source. No original function is split/adopted, no ASM,
manual patches, synthetic frame locals or complete cold replay.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f598-fighter-singleton'
CASE_SOURCE=ROOT/'probes/FighterSingletonContactF598.inc'
F564=(0x004F7130,0x005AEEC0)
F566=0x005214B0
DIRECT={
 16:('fcomp','DIR32',0x0065782C,'g_ThresholdAt0065782C'),
 22:('fadd', 'DIR32',0x00658058,'g_ApproachAt00658058'),
 27:('fcomp','DIR32',0x0065782C,'g_ThresholdAt0065782C'),
 34:('call', 'REL32',0x00454EE0,'ContactAt454EE0'),
 44:('fmul', 'DIR32',0x006583E8,'g_ContactScaleAt006583E8'),
 48:('call', 'REL32',0x0040FA30,'GetNativeActionAt40FA30'),
 56:('call', 'REL32',0x0040FAC0,'SetNativeActionAt40FAC0'),
}
SLOT=re.compile(r'\[ebp - (?:0x[0-9a-f]+|\d+)\]')
GLOBAL=re.compile(r'(?<=\[)(?:0x[0-9a-f]+|0)(?=\])')


def need(ok,detail):
    if not ok:
        raise ValueError(detail)


def load(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,f'missing original C++ generator {path}')
    result=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=result
    spec.loader.exec_module(result)
    return result


def original_source(address,boss,report,mapped,reader,pe,dec,f567):
    """Never trust an ignored old C++ artifact as our source-of-truth."""
    if address in f567.BOSSES:
        h=f567.helpers()
        return f567.compose_source(address,boss,report,mapped,reader,pe,dec,h)
    if address==F566:
        s=load('f598_f566',ROOT/'scripts/verify-fighter-integrated-scripted-switch.py')
        files={tag:load('f598_f566_'+tag,ROOT/'scripts'/filename) for tag,filename in {
            'opening':'verify-fighter-opening-actions-natural-source.py',
            'switch':'verify-fighter-natural-switch-probes.py',
            'zero':'verify-fighter-actionzero-natural-source.py',
            'one':'verify-fighter-actionone-natural-source.py',
            'script':'verify-fighter-scripted-stage-actions.py',
            'nine':'verify-fighter-actionnine-natural-source.py',
            'ten':'verify-fighter-actionten-natural-source.py',
        }.items()}
        result,original=s.make_source(reader,pe,dec,boss,report,mapped,
               *(files[x] for x in ('opening','switch','zero','one','script','nine','ten')))
        need(len(original)==11,'scripted fighter original action0-10 generation changed')
        return result
    need(address in F564,'unregistered 11-case fighter giant')
    # F564 is a historical top-level script rather than an importable
    # generator. Rebuild JUST the selected original-backed source TU;
    # read the newly regenerated C++ only on full successful verification.
    output=subprocess.run([str(ROOT/'scripts/repo-python'),
             str(ROOT/'scripts/verify-fighter-integrated-opening-switch.py'),
             '--boss',f'0x{address:08X}'],cwd=ROOT,
             capture_output=True,text=True,timeout=180)
    (OUT/f'F564-{address:08X}-baseline.log').write_text(output.stdout+output.stderr)
    need(output.returncode==0,'selected F564 original-backed opening source validation failed: '+output.stderr[-500:])
    src=ROOT/f'.analysis/f564-integrated-opening-switch/Boss{address:08X}-all11.cpp'
    need(src.is_file(),'fresh verified F564 natural source not generated')
    return src.read_text()


def source_with_singleton(source,address):
    inc=CASE_SOURCE.read_text()
    need(inc.count('case 0x32:')==1 and
         'POS < g_ThresholdAt0065782C' in inc and
         'POS > g_ThresholdAt0065782C' in inc and
         'POS * g_ContactScaleAt006583E8' in inc,
         'the genuine C++ contact-stage case source is absent')
    marker='case 0x32: g_FighterProbeMarker = 51; break;'
    need(source.count(marker)==1 and 'case 0x33:' in source,
         'the physical original 0x32 singleton or next group 0x33 is not separately represented')
    original_name=re.search(r'class (FighterSwitchF\d+_[a-zA-Z0-9_]+)\s*\{',source)
    need(original_name is not None,'no real original-backed C++ actor type')
    name=original_name.group(1)
    need(source.count(name)>=2,'missing actual C++ method definition')
    source=source.replace(name,f'FighterSwitchF598_Boss{address:08X}')
    existing='void SetNativeActionAt40FAC0(int);'
    need(source.count(existing)==1,'native state callback declaration changed')
    source=source.replace(existing,existing+' signed char ContactAt454EE0();')
    globaldecl='extern float g_ThresholdAt0065782C;'
    need(source.count(globaldecl)==1,'native physical signed float threshold unavailable')
    source=source.replace(globaldecl,globaldecl+'''\nextern float g_ApproachAt00658058;
extern double g_ContactScaleAt006583E8;''')
    source=source.replace(marker,'#include "FighterSingletonContactF598.inc"')
    need(source.count('case 0xA:')==1 and source.count('g_FighterProbeMarker')>1,
         'remaining incomplete giant source must retain diagnostic action placeholders')
    return source


def compile_one(address,source):
    cpp=OUT/f'Boss{address:08X}-twelve-original-cases.cpp'
    obj=OUT/f'Boss{address:08X}-twelve-original-cases.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cmd=[str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes']
    proc=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True,timeout=150)
    (OUT/f'Boss{address:08X}-compile.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'pinned VC7.1 compilation failed: '+proc.stderr[-600:])
    return obj


def normalized(ins):
    addresses={x.address:k for k,x in enumerate(ins)}
    shape=[]
    for ordinal,x in enumerate(ins):
        op=SLOT.sub('[NATIVE_RECEIVER_SLOT]',x.op_str)
        if x.mnemonic.startswith('j') and re.fullmatch(r'0x[0-9a-f]+',op):
            target=int(op,16)
            op=('CASE_ORDINAL_'+str(addresses[target]) if target in addresses
                else 'EN closing shared fighter exit')
        elif x.mnemonic=='call' and re.fullmatch(r'0x[0-9a-f]+',op):
            op='NATIVE_TYPED_CALLEE'
        elif x.mnemonic in ('fcomp','fadd','fmul'):
            op=GLOBAL.sub('NATIVE_TYPED_FLOAT_GLOBAL',op)
        shape.append((x.mnemonic,op))
    return shape


def strict_singleton(reader,pe,dec,action,boss,report,mapped,code,refs,inst,ret):
    addr=boss['address']
    singles=[int(q['handler'],16) for q in report['singleton_branches'] if q['action']==50]
    need(len(singles)==1,'missing genuine original separate action50 equality branch')
    start=singles[0]
    nextcases=[int(q['handler'],16) for q in mapped if int(q['handler'],16)>start]
    need(nextcases,'missing original second switch physical case51')
    end=min(nextcases)
    need(end==boss['tables'][1]['firsttarget'],
         'original next indexed table begins somewhere other than after action50')
    native=list(dec.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    width=256 if addr==0x00564BE0 else 205
    need(end-start==width and len(native)==58 and
         native[0].mnemonic=='mov' and native[-1].mnemonic=='jmp',
         f'whole original singleton action0x32 physical native extent changed {addr:#x}')
    need(native[9].mnemonic=='mov' and native[9].op_str.endswith(', 0xc1000000')
         and native[18].op_str=='ah, 5' and native[19].mnemonic=='jp'
         and native[29].op_str=='ah, 0x41' and native[30].mnemonic=='jne',
         'actual original -8.0f initialization and distinct < versus > contact comparisons changed')
    cases=[int(inst[i+1].op_str,16) for i in range(len(inst)-1)
        if inst[i].mnemonic=='cmp' and inst[i].op_str.endswith(', 0x32')
        and inst[i+1].mnemonic=='je']
    need(len(cases)==1,'fresh VC7.1 source missing true separate 0x32 action dispatch')
    candidates=[r for r in refs if r['offset']==ret+44]
    need(len(candidates)==1 and candidates[0]['type']=='DIR32'
         and candidates[0]['addend']==0
         and candidates[0]['local_symbol_offset'] is not None,
         'case51 native next dense table slot missing physical zero-addend pointer')
    ca,cb=cases[0],candidates[0]['local_symbol_offset']
    need(0<=ca<cb<ret,'candidate action50/51 shared code boundary invalid')
    generated=list(dec.disasm(code[ca:cb],ca))
    need(len(generated)==len(native)==58 and cb-ca==205,
         'natural source singleton does not preserve full 58-instruction 205-byte candidate')
    native_loads=[x for x in native if x.mnemonic=='mov' and 'dword ptr [ebp - ' in x.op_str]
    generated_loads=[x for x in generated if x.mnemonic=='mov' and 'dword ptr [ebp - ' in x.op_str]
    need(len(native_loads)==len(generated_loads)==17,
         'original singleton saved-this stack loads changed: expected exactly 17')
    need(all('[ebp - 0x88]' in x.op_str for x in native_loads)==(width==256),
         'wide-native receiver must be the real EBP-0x88 exception only')
    dwidth=[x.size-y.size for x,y in zip(native,generated)]
    need(sum(dwidth)==width-205 and
         (dwidth.count(3)==17 and dwidth.count(0)==41 if width==256
          else all(k==0 for k in dwidth)),
         'original full-case instruction widths not explained by exactly 17 true wide EBP loads')
    left,right=normalized(native),normalized(generated)
    issues=[(i,a,b) for i,(a,b) in enumerate(zip(left,right)) if a!=b]
    need(not issues,f'original full singleton action50 native GPR/x87/branch grammar differs: {issues[:8]}')
    physical=[r for r in refs if ca<=r['offset']<cb]
    need(len(physical)==len(DIRECT)==7,'singleton has missing/extra COFF references')
    for i,(mnemonic,typ,target,symbol) in DIRECT.items():
        original,source=native[i],generated[i]
        need(original.mnemonic==source.mnemonic==mnemonic,
             f'original genuine physical typed singleton COFF instruction {i} moved')
        want=(f'0x{target:x}' if typ=='REL32' else
              f'{"qword" if i==44 else "dword"} ptr [0x{target:x}]')
        need(original.op_str==want,
             f'original PE singleton call/float target {i} changed: {original.op_str}')
        found=[r for r in physical if source.address<=r['offset']<source.address+source.size]
        need(len(found)==1 and found[0]['type']==typ and
             found[0]['addend']==0 and symbol in found[0]['symbol'],
             f'physical compiler COFF field target/kind/addend does not prove original opcode {i}: {found}')
    return {'start':f'0x{start:08X}','native_CODE_bytes':width,
            'source_CODE_bytes':cb-ca,'native_x86_instructions':58,
            'original_GPR_x87_CFG_instruction_roles':58,
            'original_physical_COFF_fields':7,
            'wide_native_EBP_receiver_reads':17 if width==256 else 0,
            'source_is_complete_boss':False}


def main():
    opts=argparse.ArgumentParser(description=__doc__)
    opts.add_argument('--boss',help='One 0x-prefixed registered giant; default all 11 original bosses')
    opts=opts.parse_args()
    f567=load('f598_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    reader=load('f598_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f598_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    zero=load('f598_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f598_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    core=load('f598_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    registered={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*F564,F566)
    need(len(cohort)==len(set(cohort))==11,'native multi-switch fighter source cohort changed')
    selected=[int(opts.boss,0)] if opts.boss else list(cohort)
    need(all(x in cohort for x in selected),'selected fighter is not part of eleven original full-sized switch bosses')
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for address in selected:
        boss=registered[address]
        report,mapped=actions.report_boss(reader,pe,dec,boss)
        src=source_with_singleton(original_source(address,boss,report,mapped,reader,pe,dec,f567),address)
        obj=compile_one(address,src)
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{address:08X}@@QAEXXZ')
        instructions=[]
        for x in dec.disasm(code,0):
            instructions.append(x)
            if x.mnemonic=='ret':break
        need(instructions and instructions[-1].mnemonic=='ret',f'{address:#x}: C++ whole code has no normal return')
        ret=instructions[-1].address+instructions[-1].size
        need(len(code)-ret==boss['postret_size'],f'{address:#x}: original complete jump-table DATA layout changed')
        row=strict_singleton(reader,pe,dec,50,boss,report,mapped,code,refs,instructions,ret)
        # Ensure the newly added case has not silently changed any existing
        # eleven genuine case0..10 codegen grammars or parent switch DATA.
        cfirst=[r['local_symbol_offset'] for r in refs if ret<=r['offset']<ret+44]
        nfirst=[int.from_bytes(reader.pe_bytes_at(pe,boss['tables'][0]['dense_addr']+4*k,4),'little')
                for k in range(11)]
        need(len(cfirst)==11 and all(x is not None for x in cfirst),
             'first original eleven DWORD jump-table fields disappeared')
        n0=int(next(x['handler'] for x in report['singleton_branches'] if x['action']==50),16)
        c0=int(next(int(instructions[i+1].op_str,16) for i in range(len(instructions)-1)
             if instructions[i].mnemonic=='cmp' and instructions[i].op_str.endswith(', 0x32')
             and instructions[i+1].mnemonic=='je'))
        origbounds=nfirst+[n0];cppbounds=cfirst+[c0]
        need(origbounds==sorted(set(origbounds)) and cppbounds==sorted(set(cppbounds)),
             'original first eleven action-code boundaries no longer ordered')
        count=0
        for k in range(11):
            a,b=origbounds[k:k+2];c,d=cppbounds[k:k+2]
            native=list(dec.disasm(reader.pe_bytes_at(pe,a,b-a),a))
            generated=list(dec.disasm(code[c:d],c))
            need(len(native)==len(generated),f'{address:#x}: prior original case{k} now has wrong instruction count')
            core.compare_grammar(native,generated)
            if address!=0x00564BE0:
                need([x.size for x in native]==[x.size for x in generated],
                     f'{address:#x}: previously reconstructed action{k} instruction width drift')
            else:
                f567.native_size_encoding(native,generated,True)
            count+=len(native)
        dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,reader,switch,
                instructions,code,refs,ret)
        row.update({'boss':f'0x{address:08X}','original_whole_giant_CODE_unaccepted':boss['size'],
                    'retained_other_original_action_cases':11,
                    'retained_other_original_action_x86_roles':count,
                    'real_whole_switch_DWORD_COFF_fields':dense,
                    'literal_original_sparse_switch_bytes':sparse,
                    'original_afterret_DATA_layout_bytes':boss['postret_size']})
        rows.append(row)
        print(f'F598 {address:#010x}: original complete singleton case0x32 '
              f'{row["native_CODE_bytes"]} native /205 source CODE bytes, 58/58 GPR/x87/CFG '
              f'instructions, 7/7 physical COFF call/global target fields, '
              f'{count} earlier native case0..10 x86 roles unchanged, '
              f'{dense} native full-table refs, {sparse} sparse indices',flush=True)
    path=OUT/('summary.json' if not opts.boss else f'summary-{selected[0]:08X}.json')
    path.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F598 {len(rows)}/{len(selected)} native action50 fighters: original whole giants NOT exact; '
          '0 independent exact functions, zero new CODE/DATA acceptance, no all-unit cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as error:
        print('F598 original native singleton contact C++ verifier failed:',error,file=sys.stderr)
        raise SystemExit(1)
