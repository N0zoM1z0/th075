#!/usr/bin/env python3
"""F584: actual original backed 171-byte ArchiveCatalog delete expression controls.

Recompile only selected ordinary C++ source TUs with pinned VC7.1 /GX-
(non-EH), independently compare EACH WHOLE original Japanese TH075 v1.11
0041CE50 destructor (171 CODE bytes, 51 x86 instructions). Twelve real
C++ delete-expression type/ref/alias variants are negative checks:
10 produce 171 bytes and 108/115 original nonfield bytes but keep wrong
resource/filename EBP locals; the two constant ternaries inflate CODE.
No original byte patches, machine ASM, false exact credit or all-unit replay.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from collections import Counter

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp'
OUT=ROOT/'.analysis/f584-archive-delete-source'
ORIGINAL=0x0041CE50
ORIG_SIZE=171
SYMBOL='??1ArchiveCatalogF343@@QAE@XZ'
EXPR='delete *g_ArchiveResourcesAt0068BE08.At(index);'
VALUE='*g_ArchiveResourcesAt0068BE08.At(index)'
VARIANTS={
 'paren':f'delete ({VALUE});',
 'static-cast':f'delete static_cast<ArchiveResourceF343*>({VALUE});',
 'reinterpret-cast':f'delete reinterpret_cast<ArchiveResourceF343*>({VALUE});',
 'cstyle-cast':f'delete (ArchiveResourceF343*)({VALUE});',
 'const-cast':f'delete const_cast<ArchiveResourceF343*>({VALUE});',
 'double-pointer-cast':'delete *((ArchiveResourceF343**)g_ArchiveResourcesAt0068BE08.At(index));',
 'address-deref':'delete *(&*g_ArchiveResourcesAt0068BE08.At(index));',
 'conditional-true':f'delete (true ? {VALUE} : (ArchiveResourceF343*)0);',
 'conditional-false':f'delete (false ? (ArchiveResourceF343*)0 : {VALUE});',
 'static-lvalue-ref':'delete static_cast<ArchiveResourceF343*&>(*g_ArchiveResourcesAt0068BE08.At(index));',
 'cstyle-lvalue-ref':'delete (ArchiveResourceF343*&)(*g_ArchiveResourcesAt0068BE08.At(index));',
 'pointer-alias':f'delete (static_cast<ArchiveResourceF343* const&>({VALUE}));',
}


def need(ok,message):
    if not ok:
        raise ValueError(message)


def original():
    spec=importlib.util.spec_from_file_location('f584_pe_reader',ROOT/'scripts/compare-coff-function.py')
    need(spec is not None and spec.loader is not None,
         'missing original PE native COFF verifier')
    reader=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=reader
    spec.loader.exec_module(reader)
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(decoder.disasm(reader.pe_bytes_at(pe,ORIGINAL,ORIG_SIZE),ORIGINAL))
    need(len(native)==51 and sum(x.size for x in native)==ORIG_SIZE,
         'original native entire 171-byte ArchiveCatalog boundary changed')
    need(native[22].mnemonic=='mov' and native[22].op_str=='dword ptr [ebp - 0xc], eax'
         and native[24].mnemonic=='mov' and native[24].op_str=='dword ptr [ebp - 8], ecx'
         and native[38].mnemonic=='mov' and native[38].op_str=='dword ptr [ebp - 0x10], eax'
         and native[-1].mnemonic=='ret',
         'actual original PE independent resource-delete/filename local slots differ')
    return reader,decoder


def compile_probe(kind,expr,reader,decoder):
    OUT.mkdir(parents=True,exist_ok=True)
    source=SOURCE.read_text()
    need(source.count(EXPR)==1 and 'NONEXACT C++ PROBE' in source,
         'native type/source input must have exactly one real delete expression')
    cpp=OUT/f'{kind}.cpp';obj=OUT/f'{kind}.obj'
    cpp.write_text(source.replace(EXPR,expr))
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
                        cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/f'{kind}-compile.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0, f'fresh VC7.1 archive natural C++ compile failed for {kind}: {proc.stderr}')
    code,refs=reader.object_function(obj,SYMBOL)
    inst=list(decoder.disasm(code,0))
    result=subprocess.run([sys.executable,str(ROOT/'scripts/compare-coff-function.py'),
         str(obj),SYMBOL,hex(ORIGINAL),str(ORIG_SIZE),'--json'],
         cwd=ROOT,text=True,capture_output=True,timeout=120)
    need(result.stdout.strip() and result.returncode in (0,1),
         f'original whole-function COFF compare failed for {kind}: {result.stderr}')
    (OUT/f'{kind}-compare.json').write_text(result.stdout)
    comparison=json.loads(result.stdout)
    row={'case':kind,'whole_source_CODE_bytes':len(code),
         'candidate_x86_instructions':len(inst),
         'native_comparison':comparison['result'],
         'matched_nonfield_bytes':comparison.get('matched_comparable_bytes'),
         'comparable_nonfield_bytes':comparison.get('comparable_bytes')}
    if kind.startswith('conditional-'):
        need(comparison['result']=='size-mismatch' and
             len(code)==(198 if kind=='conditional-true' else 193),
             f'original 171-byte destructor must NOT accept conditional extra-code {kind}')
    else:
        need(comparison['result']=='mismatch' and len(code)==171 and len(inst)==51
             and comparison['matched_comparable_bytes']==108
             and comparison['comparable_bytes']==115,
             f'original native small destructor actually changed under selected C++ source {kind}')
        need(inst[22].op_str=='dword ptr [ebp - 0x10], eax'
             and inst[24].op_str=='dword ptr [ebp - 0xc], ecx'
             and inst[38].op_str=='dword ptr [ebp - 8], eax',
             f'nonexact candidate EBP ownership changed for {kind}; inspect original anew')
        row['source_local_slots']={'resource_temp':'EBP-0x10',
                                   'delete_receiver':'EBP-0xC',
                                   'filename':'EBP-0x8'}
    return row


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--case',choices=list(VARIANTS),
                        help='Only one selected original-backed C++ variant; default all twelve')
    opts=parser.parse_args()
    reader,decoder=original()
    selected=[opts.case] if opts.case else list(VARIANTS)
    rows=[]
    for name in selected:
        row=compile_probe(name,VARIANTS[name],reader,decoder)
        rows.append(row)
        print(f'{name}: C++ {row["whole_source_CODE_bytes"]} bytes / '
              f'{row["candidate_x86_instructions"]} instructions, '
              f'original whole function {row["native_comparison"]}, '
              f'nonfield byte overlap {row["matched_nonfield_bytes"]}/'
              f'{row["comparable_nonfield_bytes"]}',flush=True)
    if not opts.case:
        counts=Counter(r['native_comparison'] for r in rows)
        need(len(rows)==12 and counts=={'mismatch':10,'size-mismatch':2},
             'expected negative source-control matrix changed; re-inspect original rather than assert exact')
    OUT.mkdir(parents=True,exist_ok=True)
    target='summary.json' if not opts.case else f'summary-{opts.case}.json'
    (OUT/target).write_text(json.dumps(rows,indent=2)+'\n')
    print(f'{len(rows)} fresh original complete 171-byte native archive destructor '
          f'source controls studied; ZERO accepted whole function matches, no '
          'all-unit cold replay and no external Oracle receipt')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as error:
        print('TH075 original ArchiveCatalog source-only control failed:',error,file=sys.stderr)
        raise SystemExit(1)
