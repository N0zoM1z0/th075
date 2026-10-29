#!/usr/bin/env python3
"""F600: original action51/0x33 complete source codegen in 11 native giants.

Generate original-backed F598 real 12-case switch source from the pinned PE,
add the separate actual second-table indexed case 0x33, then compile ONLY
selected VC7.1 natural C++ translation units. Verify whole original case
51 via original table DWORD and sparse byte-index, all 58 native x86 roles,
7 physical original typed COFF refs, exact 205/256 widths, and preservation
of all eleven previous cases PLUS original singleton case50 and complete
native switch DATA. These are case subranges, never standalone functions.
"""
from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f600-fighter-indexed-contact51'
SOURCE=ROOT/'probes/FighterIndexedContact51F600.inc'
# Shared strict original PE-backed helper; do not fork its native controls.
sys.path.insert(0,str(ROOT/'scripts'))
import importlib.util


def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    if spec is None or spec.loader is None:
        raise ValueError(f'original source generator missing: {path}')
    result=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=result
    spec.loader.exec_module(result)
    return result


f598=module('f600_f598',ROOT/'scripts/verify-fighter-singleton-contact-f598.py')
f567=module('f600_f567',ROOT/'scripts/verify-fighter-all-multiswitch-opening-cases.py')
reader=module('f600_reader',ROOT/'scripts/compare-coff-function.py')
actions=module('f600_actions',ROOT/'scripts/report-fighter-action-handlers.py')
zero=module('f600_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
switch=module('f600_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
core=module('f600_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
need=f598.need


def composed_source(address,boss,report,mapped,pe,dec):
    old=f598.original_source(address,boss,report,mapped,reader,pe,dec,f567)
    original=f598.source_with_singleton(old,address)
    witness=SOURCE.read_text()
    need(witness.count('case 0x33:')==1 and 'POS = -9.0f;' in witness
         and witness.count('POS < g_ThresholdAt0065782C')==1,
         'real native second indexed actor 0x33 source changed unexpectedly')
    marker='case 0x33: g_FighterProbeMarker = 52; break;'
    need(original.count(marker)==1,'source original indexed case51 marker absent')
    original=original.replace(marker,'#include "FighterIndexedContact51F600.inc"')
    before=f'FighterSwitchF598_Boss{address:08X}'
    need(original.count(before)>=2,'F598 original frame actor name not found')
    original=original.replace(before,f'FighterSwitchF600_Boss{address:08X}')
    need('case 0x34: g_FighterProbeMarker = 53; break;' in original,
         'the next action remains a diagnostic marker, not false whole source')
    return original


def compile_one(address,src):
    p=OUT/f'Boss{address:08X}-thirteen-cases.cpp'
    obj=OUT/f'Boss{address:08X}-thirteen-cases.obj'
    p.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cmd=[str(ROOT/'scripts/compile-probe.sh'),str(p),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes']
    result=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True,timeout=150)
    (OUT/f'Boss{address:08X}-compile.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0, f'VC7.1 C++ original indexed action51 compile failure {result.stderr[-600:]}')
    return obj


def strict_indexed_51(pe,dec,boss,report,mapped,code,refs,ret):
    address=boss['address'];table=boss['tables'][1]
    need(table['map_addr'] is not None and table['slots']>=3,
         'original native second action switch must be sparse with 3 physical slots')
    idx=reader.pe_bytes_at(pe,table['map_addr'],3)
    need(idx==b'\x00\x01\x02',
         'original physical sparse byte map for indexed actions 51,52,53 changed')
    native_ptrs=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*k,4),'little')
                 for k in (0,1)]
    original51,original52=native_ptrs
    mapped51=[r for r in mapped if r['action'] in (51,52)]
    need(len(mapped51)==2 and [int(r['handler'],16) for r in mapped51]==native_ptrs,
         'native indexed action 0x33..0x34 physical table DWORD mapping differs')
    source_ptrs=[]
    for k in (0,1):
        r=[x for x in refs if x['offset']==ret+44+4*k]
        need(len(r)==1 and r[0]['type']=='DIR32' and
             r[0]['addend']==0 and r[0]['local_symbol_offset'] is not None,
             f'original second switch physical COFF source label at {k} not reproduced')
        source_ptrs.append(r[0]['local_symbol_offset'])
    ca,cb=source_ptrs;need(0<=ca<cb<ret,'compiled indexed case 51 source bounds invalid')
    original=list(dec.disasm(reader.pe_bytes_at(pe,original51,original52-original51),original51))
    compiled=list(dec.disasm(code[ca:cb],ca))
    wide=address==0x00564BE0
    native_size=256 if wide else 205
    need(original52-original51==native_size and cb-ca==205 and
         len(original)==len(compiled)==58,
         f'original second indexed action51 native 58-instruction boundary changed {address:08X}')
    need(original[9].mnemonic==compiled[9].mnemonic=='mov' and
         original[9].op_str.endswith('0xc1100000') and
         compiled[9].op_str.endswith('0xc1100000') and
         original[18].op_str=='ah, 5' and original[19].mnemonic=='jp' and
         original[29].op_str=='ah, 0x41' and original[30].mnemonic=='jne',
         '0x33 original -9.0f initializer and strict x87 signs not reproduced')
    mismatches=[(i,a,b) for i,(a,b) in enumerate(zip(f598.normalized(original),f598.normalized(compiled))) if a!=b]
    need(not mismatches,f'original indexed action51 real GPR/x87/CFG mismatch {mismatches[:8]}')
    sizes=[x.size-y.size for x,y in zip(original,compiled)]
    nloads=[x for x in original if x.mnemonic=='mov' and 'dword ptr [ebp - ' in x.op_str]
    cloads=[x for x in compiled if x.mnemonic=='mov' and 'dword ptr [ebp - ' in x.op_str]
    need(len(nloads)==len(cloads)==17 and
         (sizes.count(3)==17 and sizes.count(0)==41 if wide else all(x==0 for x in sizes)),
         'actual second indexed case51 special wide saved-receiver displacement has unexplained bytes')
    need(all('[ebp - 0x88]' in x.op_str for x in nloads)==wide,
         'actual original indexed case51 wide saved receiver not original EBP-0x88')
    physical=[r for r in refs if ca<=r['offset']<cb]
    need(len(physical)==7,'original indexed action51 must preserve exactly 7 typed physical source COFF fields')
    for ordinal,(mnemonic,typ,target,symbol) in f598.DIRECT.items():
        old,now=original[ordinal],compiled[ordinal]
        expected=(f'0x{target:x}' if typ=='REL32' else
                  f'{"qword" if ordinal==44 else "dword"} ptr [0x{target:x}]')
        need(old.mnemonic==now.mnemonic==mnemonic and old.op_str==expected,
             f'native original action51 typed PE target changed at ordinal {ordinal}')
        placed=[r for r in physical if now.address<=r['offset']<now.address+now.size]
        need(len(placed)==1 and placed[0]['type']==typ and placed[0]['addend']==0
             and symbol in placed[0]['symbol'],
             f'candidate action51 actual COFF field {ordinal} wrong symbol/kind/addend')
    return {'native_CASE_51_start':f'0x{original51:08X}',
            'native_CASE_51_CODE_bytes':native_size,
            'source_CASE_51_CODE_bytes':cb-ca,
            'native_CASE_51_instructions':58,
            'genuine_native_CASE_51_typed_fields':7,
            'wide_saved_receiver_3byte_encoding_delta':51 if wide else 0}


def main():
    cli=argparse.ArgumentParser(description=__doc__)
    cli.add_argument('--boss',help='Only one original eleven-switch giant; default eleven affected source builds')
    options=cli.parse_args()
    cohort=(*f567.BOSSES,*f598.F564,f598.F566)
    selected=[int(options.boss,0)] if options.boss else list(cohort)
    need(all(x in cohort for x in selected),'selected fighter is not part of original native eleven-giant cohort')
    originals={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for addr in selected:
        boss=originals[addr]
        report,mapped=actions.report_boss(reader,pe,decoder,boss)
        src=composed_source(addr,boss,report,mapped,pe,decoder)
        obj=compile_one(addr,src)
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF600_Boss{addr:08X}@@QAEXXZ')
        inst=[]
        for x in decoder.disasm(code,0):
            inst.append(x)
            if x.mnemonic=='ret':break
        need(inst and inst[-1].mnemonic=='ret','candidate fighter lost whole native RET')
        ret=inst[-1].address+inst[-1].size
        need(len(code)-ret==boss['postret_size'],
             f'{addr:#x}: original seven jump table/sparse DATA shape changed')
        # Revalidate F598 singleton from the freshly compiled F600 object.
        prior=f598.strict_singleton(reader,pe,decoder,50,boss,report,mapped,code,refs,inst,ret)
        row=strict_indexed_51(pe,decoder,boss,report,mapped,code,refs,ret)
        cfirst=[r['local_symbol_offset'] for r in refs if ret<=r['offset']<ret+44]
        nfirst=[int.from_bytes(reader.pe_bytes_at(pe,boss['tables'][0]['dense_addr']+4*k,4),'little') for k in range(11)]
        singleton=[int(x['handler'],16) for x in report['singleton_branches'] if x['action']==50]
        source_singletons=[int(inst[k+1].op_str,16) for k in range(len(inst)-1)
             if inst[k].mnemonic=='cmp' and inst[k].op_str.endswith(', 0x32')
             and inst[k+1].mnemonic=='je']
        need(len(cfirst)==11 and len(singleton)==len(source_singletons)==1,
             'old original 11 case physical source labels no longer present')
        nfirst+=singleton;cfirst+=source_singletons
        need(nfirst==sorted(set(nfirst)) and cfirst==sorted(set(cfirst)),
             'original earlier case0..10 boundaries changed')
        prior_instructions=0
        for k in range(11):
            a,b=nfirst[k:k+2];c,d=cfirst[k:k+2]
            ns=list(decoder.disasm(reader.pe_bytes_at(pe,a,b-a),a))
            cs=list(decoder.disasm(code[c:d],c))
            need(len(ns)==len(cs),f'earlier native fighter case{k} number of instructions changed')
            core.compare_grammar(ns,cs)
            if addr!=0x00564BE0:
                need([x.size for x in ns]==[x.size for x in cs],
                     f'previous original native fighter case{k} changed instruction length')
            else:
                f567.native_size_encoding(ns,cs,True)
            prior_instructions+=len(ns)
        fields,sparse,maps=zero.verify_physical_tables(boss,report,pe,reader,switch,inst,code,refs,ret)
        row.update({'boss':f'0x{addr:08X}','original_whole_giant_CODE_unaccepted':boss['size'],
                    'preserved_11_original_prior_cases_x86':prior_instructions,
                    'preserved_original_singleton_50_x86':prior['native_x86_instructions'],
                    'native_all_switch_DWORD_COFF_fields':fields,
                    'literal_native_sparse_index_bytes':sparse,
                    'original_afterRET_switch_DATA_bytes':boss['postret_size'],
                    'fully_source_reconstructed_giant':False})
        rows.append(row)
        print(f'F600 {addr:#010x}: new original indexed action0x33 '
              f'{row["native_CASE_51_CODE_bytes"]} native/205 source bytes, '
              f'58/58 genuine x86 roles, 7/7 typed COFF; '
              f'old 11 real cases {prior_instructions} original x86 + '
              f'F598 action50 58 original x86 still pass, '
              f'full {fields} switch DWORD/ {sparse} sparse bytes preserved',flush=True)
    out=OUT/('summary.json' if not options.boss else f'summary-{selected[0]:08X}.json')
    out.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F600 {len(rows)}/{len(selected)} complete native indexed game subranges; '
          '0 new whole exact functions/0 credited source CODE; no full cold replay',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F600 original fighter indexed contact source verifier failed:',e,file=sys.stderr)
        raise SystemExit(1)
