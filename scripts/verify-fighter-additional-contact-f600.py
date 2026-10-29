#!/usr/bin/env python3
"""F600: reconstruct 11 additional complete second-switch cases in big fighters.

The original 11 game functions are still WHOLE nonexact: the case bodies
are genuine subranges, not independent accepted CODE. Independently read the
pinned Japanese PE, full boundaries, real after-RET tables, actual native
relocation destinations and cold-compile only the selected fighter's C++ TU.
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
INC=ROOT/'probes/FighterAdditionalContactF600.inc'
OUT=ROOT/'.analysis/f600-fighter-contact-source'
ADDITIONAL=(0x33,0x34,0x35,0x38,0x39,0x3A,0x3B,0x3E,0x3F,0x40,0x41)
WITH_STAGE={0x35,0x3B,0x41}
START={0x33:0xC1100000,0x34:0xC1400000,0x35:0xC1700000,
       0x38:0xC1000000,0x39:0xC1100000,0x3A:0xC1400000,
       0x3B:0xC1700000,0x3E:0xC1000000,0x3F:0xC1100000,
       0x40:0xC1400000,0x41:0xC1700000}
# Native physical COFF field positions in each *complete original case*.
# The extra initial stage-reset adds two instructions to stage counters.
DIRECT={16:('fcomp','DIR32',0x0065782C,'g_ThresholdAt0065782C'),
        22:('fadd','DIR32',0x00658058,'g_ApproachAt00658058'),
        27:('fcomp','DIR32',0x0065782C,'g_ThresholdAt0065782C'),
        34:('call','REL32',0x00454EE0,'ContactAt454EE0'),
        44:('fmul','DIR32',0x006583E8,'g_ContactScaleAt006583E8'),
        48:('call','REL32',0x0040FA30,'GetNativeActionAt40FA30'),
        56:('call','REL32',0x0040FAC0,'SetNativeActionAt40FAC0')}


def need(test, message):
    if not test: raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,f'missing native evidence helper: {path}')
    result=importlib.util.module_from_spec(spec)
    sys.modules[name]=result
    spec.loader.exec_module(result)
    return result


def whole_original_case(reader,pe,decoder,boss,byaction,case):
    start=byaction[case]
    later=sorted({address for address in byaction.values() if address>start})
    need(later and boss['address']<=start<later[0]<boss['address']+boss['size'],
         f'{boss["address"]:#x} action{case:x}: no verified physical original case extent')
    end=later[0]
    ins=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    size=367 if boss['address']==0x00564BE0 and case in WITH_STAGE else (
         256 if boss['address']==0x00564BE0 else (295 if case in WITH_STAGE else 205))
    num=79 if case in WITH_STAGE else 58
    need(end-start==size and len(ins)==num and sum(x.size for x in ins)==size
         and ins[-1].mnemonic=='jmp' and ins[0].mnemonic=='mov',
         f'{boss["address"]:#x}: original {case:#x} complete CODE boundary/size changed')
    pos=11 if case in WITH_STAGE else 9
    need(ins[pos].mnemonic=='mov' and ins[pos].op_str.endswith(f'0x{START[case]:x}')
         and '0x50]' in ins[pos].op_str,
         f'{boss["address"]:#x}: original {case:#x} initiation speed wrong')
    if case in WITH_STAGE:
        for idx in (9,60):
            need(ins[idx].mnemonic=='mov' and 'word ptr' in ins[idx].op_str
                 and ins[idx].op_str.endswith(', 0') and '+ 0x' in ins[idx].op_str,
                 f'{boss["address"]:#x}: native contact stage counter not written')
        offsets=[int(re.search(r'\+ (0x[0-9a-f]+)',ins[idx].op_str).group(1),16) for idx in (9,60,67,71,74)]
        need(all(x==offsets[0] for x in offsets) and offsets[0] in (0xF00,0xEFC)
             and ins[64].mnemonic=='cmp' and ins[64].op_str.endswith(', 7')
             and ins[68].mnemonic=='cmp' and ins[68].op_str.endswith(', 1')
             and ins[75].mnemonic=='push' and ins[75].op_str=='1'
             and ins[77].mnemonic=='call' and ins[77].op_str=='0x40fb40',
             f'{boss["address"]:#x}: original stage7 threshold/counter/native trigger changed: {offsets}')
        return start,end,ins,offsets[0]
    need(ins[54].mnemonic=='push' and
         ins[54].op_str==('2' if case>=0x3E else '0'),
         f'{boss["address"]:#x}: native contact next action not genuine')
    return start,end,ins,None


def correct_native_fields(inst,generated,refs,physical,case):
    fields=dict(DIRECT)
    if case in WITH_STAGE:
        fields={i+2:(m,t,a,s) for i,(m,t,a,s) in DIRECT.items()}
        fields[77]=('call','REL32',0x0040FB40,'SetAuxActionAt40FB40')
    sourcefields=[r for r in refs if generated[0].address<=r['offset']<generated[-1].address+generated[-1].size]
    need(len(sourcefields)==len(fields),
         f'case{case:x}: incorrect genuine source COFF field count: {len(sourcefields)}')
    verified=[]
    for ordinal,(mnemonic,typ,dest,symbol) in fields.items():
        native,cpp=inst[ordinal],generated[ordinal]
        need(native.mnemonic==cpp.mnemonic==mnemonic,
             f'{case:#x}: original PE COFF instruction ordinal {ordinal} differs')
        if typ=='REL32':
            need(native.op_str==f'0x{dest:x}',
                 f'{case:#x}: native original target call {ordinal} changed')
        else:
            need(native.op_str==f'{"qword" if mnemonic=="fmul" else "dword"} ptr [0x{dest:x}]',
                 f'{case:#x}: actual native double/float physical target changed at {ordinal}')
        found=[r for r in sourcefields if cpp.address<=r['offset']<cpp.address+cpp.size]
        need(len(found)==1 and found[0]['type']==typ and found[0]['addend']==0
             and symbol in found[0]['symbol'],
             f'{case:#x}: physical COFF source target identity/type/addend differs at {ordinal}')
        verified.append((ordinal,typ,dest))
    return len(verified)


def compare_candidate(reader,pe,decoder,f598,core,zero,switch,boss,report,mapped,code,refs):
    address=boss['address'];original={x['action']:int(x['handler'],16) for x in mapped}
    instructions=[]
    for x in decoder.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    need(instructions and instructions[-1].mnemonic=='ret',
         f'{address:#x}: source missing native fighter return')
    ret=instructions[-1].address+instructions[-1].size
    need(len(code)-ret==boss['postret_size'],f'{address:#x}: native afterRET switch table structure changed')
    # Re-check earlier true native standalone action50 and original 11 opening
    # case roles under THIS new one source compilation (no old object reuse).
    prior=f598.strict_singleton(reader,pe,decoder,50,boss,report,mapped,code,refs,instructions,ret)
    native_earlier=[int.from_bytes(reader.pe_bytes_at(pe,boss['tables'][0]['dense_addr']+4*i,4),'little') for i in range(11)]
    candidate_earlier=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+4*i) for i in range(11)]
    original50=int(next(x['handler'] for x in report['singleton_branches'] if x['action']==50),16)
    candidate50=int(next(int(instructions[i+1].op_str,16) for i in range(len(instructions)-1)
        if instructions[i].mnemonic=='cmp' and instructions[i].op_str.endswith(', 0x32')
        and instructions[i+1].mnemonic=='je'))
    norig=native_earlier+[original50];nsource=candidate_earlier+[candidate50]
    need(norig==sorted(set(norig)) and nsource==sorted(set(nsource)),
         'previous native first-switch source extent no longer ordered')
    old_roles=0
    for i in range(11):
        x,y=norig[i:i+2];u,v=nsource[i:i+2]
        native=list(decoder.disasm(reader.pe_bytes_at(pe,x,y-x),x))
        generated=list(decoder.disasm(code[u:v],u))
        need(len(native)==len(generated),f'{address:#x}: previous genuine case{i} changed count')
        core.compare_grammar(native,generated)
        if address!=0x00564BE0:
            need([z.size for z in native]==[z.size for z in generated],
                 f'{address:#x}: previous opening x86 physical instruction size changed')
        old_roles+=len(native)
    # The second dense table is *compressed*. Its 27 DWORDs are NOT
    # indexed by `case - 0x33`; the first 11 physical slots are the 11
    # distinct game states below, slot 11 is the next original case 0x46.
    native_dense=[int.from_bytes(reader.pe_bytes_at(pe,boss['tables'][1]['dense_addr']+4*i,4),'little') for i in range(12)]
    generated_dense=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*i) for i in range(12)]
    cases=[*ADDITIONAL,0x46]
    need(all(original[x]==n for x,n in zip(cases,native_dense))
         and native_dense==sorted(set(native_dense))
         and generated_dense==sorted(set(generated_dense)),
         f'{address:#x}: actual original packed second-switch labels changed')
    record=[];counter=None
    for i,case in enumerate(ADDITIONAL):
        start,end,native,original_counter=whole_original_case(reader,pe,decoder,boss,original,case)
        cstart,cend=generated_dense[i:i+2]
        generated=list(decoder.disasm(code[cstart:cend],cstart))
        need(len(generated)==len(native) and sum(x.size for x in generated)==cend-cstart,
             f'{address:#x}: actual original case{case:#x} candidate instruction count differs')
        lhs,rhs=f598.normalized(native),f598.normalized(generated)
        need(lhs==rhs,
             f'{address:#x}: original game case{case:#x} GPR/x87/CFG differs: '
             f'{[(k,l,r) for k,(l,r) in enumerate(zip(lhs,rhs)) if l!=r][:4]}')
        widths=[x.size-y.size for x,y in zip(native,generated)]
        if address==0x00564BE0:
            widened=24 if case in WITH_STAGE else 17
            need(widths.count(3)==widened and widths.count(0)==len(widths)-widened,
                 f'{address:#x}: original wide stack displacement instruction geometry differs {case:#x}')
        else:
            need(all(x==0 for x in widths) and cend-cstart==end-start,
                 f'{address:#x}: original compact case{case:#x} physical widths differ')
        real=correct_native_fields(native,generated,refs,original,case)
        if case in WITH_STAGE:
            need(original_counter== (0xEFC if address==0x005AEEC0 else 0xF00),
                 f'{address:#x}: counter ownership is not original')
            counter=original_counter
        record.append({'action':f'0x{case:02X}',
                       'native_original_start':f'0x{start:08X}',
                       'native_x86_roles':len(native),
                       'native_original_internal_CODE_bytes':end-start,
                       'source_inner_CODE_bytes':cend-cstart,
                       'true_original_physical_typed_COFF_fields':real,
                       'physical_original_wide_EBP_loads':sum(x==3 for x in widths),
                       'whole_giant_exact':False})
    dense,sparse,_=zero.verify_physical_tables(boss,report,pe,reader,switch,instructions,code,refs,ret)
    return {'boss':f'0x{address:08X}', 'original_whole_CODE_unmatched':boss['size'],
            'original_afterRET_DATA_separately_owned':boss['postret_size'],
            'native_second_switch_counter_offset':f'0x{counter:X}',
            'earlier_11_original_actions_retained_native_x86_roles':old_roles,
            'earlier_original_action_0x32_retained_native_x86_roles':prior['original_GPR_x87_CFG_instruction_roles'],
            'additional_11_original_cases':record,
            'additional_native_case_x86_roles':sum(x['native_x86_roles'] for x in record),
            'additional_native_case_internal_CODE_bytes_uncredited':sum(x['native_original_internal_CODE_bytes'] for x in record),
            'additional_physical_typed_COFF_refs':sum(x['true_original_physical_typed_COFF_fields'] for x in record),
            'full_original_postRET_typed_dense_DWORD_fields':dense,
            'full_original_postRET_literal_sparse_bytes':sparse,
            'accepted_exact_whole_functions':0,
            'all_unit_cold_replay':False}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='selected original giant, 0x prefix; default checks 11 affected TUs')
    args=parser.parse_args()
    f598=load('f600_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
    f567=load('f600_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
    reader=load('f600_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f600_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=load('f600_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    zero=load('f600_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    switch=load('f600_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    registered={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    need(len(cohort)==len(set(cohort))==11,'original eleven fighter cohort changed')
    selected=[int(args.boss,0)] if args.boss else list(cohort)
    need(all(addr in cohort for addr in selected),'non-member original giant selected')
    inc=INC.read_text()
    need(all(inc.count(f'case 0x{case:X}:')==1 for case in ADDITIONAL)
         and inc.count('CONTACT_STAGE_OFFSET')>=12
         and inc.count('SetAuxActionAt40FB40(1);')==3,
         'actual original C++ eleven nondefault fighter states missing')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for addr in selected:
        boss=registered[addr]
        report,mapped=actions.report_boss(reader,pe,dec,boss)
        source=f598.source_with_singleton(f598.original_source(addr,boss,report,mapped,reader,pe,dec,f567),addr)
        begin='        case 0x33: g_FighterProbeMarker = 52; break;'
        end='        case 0x46: g_FighterProbeMarker = 71; break;'
        need(source.count(begin)==source.count(end)==1,
             'original 11-case switch no longer carries next actual native branch placeholders')
        before,after=source.split(begin,1)
        need(end in after,'original next physical case0x46 is missing')
        nextcase=after.index(end)
        counter=0xEFC if addr==0x005AEEC0 else 0xF00
        replaced=(f'#define CONTACT_STAGE_OFFSET 0x{counter:X}\n'
                  '#include "FighterAdditionalContactF600.inc"\n'
                  '#undef CONTACT_STAGE_OFFSET\n')
        source=before+replaced+after[nextcase:]
        cpp=OUT/f'Boss{addr:08X}-23-real-original-cases.cpp'
        obj=OUT/f'Boss{addr:08X}-23-real-original-cases.obj'
        cpp.write_text(source)
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/f'Boss{addr:08X}-compile.log').write_text(result.stdout+result.stderr)
        need(result.returncode==0,f'{addr:#x}: original VC7.1 source fails selected compile: {result.stderr[-700:]}')
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        row=compare_candidate(reader,pe,dec,f598,core,zero,switch,boss,report,mapped,code,refs)
        rows.append(row)
        print(f'F600 {addr:#010x}: 11 full original action states, '
              f'{row["additional_native_case_x86_roles"]} native x86 roles, '
              f'{row["additional_native_case_internal_CODE_bytes_uncredited"]} original inner CODE bytes '
              f'and {row["additional_physical_typed_COFF_refs"]} physical original COFF refs '
              f'(counter {row["native_second_switch_counter_offset"]}); entire giant NONEXACT',flush=True)
    out=OUT/('summary.json' if not args.boss else f'summary-{selected[0]:08X}.json')
    out.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F600 {len(rows)}/{len(selected)} fighters: source reproduces all genuine 11 original '
          'inner cases, preserves prior 12 cases and original afterRET table layout, '
          'ZERO accepted whole game functions, no all-unit cold replay',flush=True)


if __name__=='__main__':
    try: main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F600 actual Japanese TH075 giant contact source failed:',exc,file=sys.stderr)
        raise SystemExit(1)
