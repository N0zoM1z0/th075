#!/usr/bin/env python3
"""F799: two whole original unknown-origin native leaves (40B + 31B).

Entire original PE, original source COFF section sizes, ABI/RET,
x86 bytes and zero physical relocations attested by one affected
VC7.1 compile. Contrast valid normal '!=0' syntax, whose different
29B compilation proves that a source-level equivalent expression
does not establish byte-exactness. No canonical authored credit.
"""
from __future__ import annotations
import csv
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/UnknownOwnerFieldLeavesF799.cpp'
OUT=ROOT/'.analysis/f799-native-owner-leaves'
ROWS={
    'setter':('0x004135F0',40,16,'?Configure@NativeOwnerSetterF799@@QAEXEHH@Z','0xc'),
    'flag':('0x00454F70',31,15,'?HasActiveFlag@NativeOwnerFlagF799@@QAE_NXZ',''),
}

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load():
    spec=importlib.util.spec_from_file_location('f799_reader',ROOT/'scripts/compare-coff-function.py')
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module
    spec.loader.exec_module(module)
    return module

def compile_one(tag,source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/(tag+'.cpp')
    obj=OUT/(tag+'.obj')
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cmd=[str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi']
    run=subprocess.run(cmd,cwd=ROOT,env=env,text=True,capture_output=True,timeout=200)
    (OUT/(tag+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'full original source compiler failed '+tag+': '+(run.stdout+run.stderr)[-550:])
    return obj

def main():
    rd=load()
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    source=SOURCE.read_text()
    need('NOT accepted historical authored' in source,
         'source must keep truthful unknown historical provenance')
    origin={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    functions={r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    for addr,size,nx,_,_ in ROWS.values():
        need(origin[addr]['origin']=='unknown' and origin[addr]['disposition']=='review'
             and functions[addr]['status']=='unclassified'
             and int(functions[addr]['size'])==size,
             'F799 original candidate provenance/whole interval was silently changed '+addr)
    obj=compile_one('native',source)
    records=[]
    for typ,(address,size,x86,symbol,retstr) in ROWS.items():
        code,refs=rd.object_function(obj,symbol)
        target=rd.pe_bytes_at(pe,int(address,16),size)
        native=list(d.disasm(target,int(address,16)))
        generated=list(d.disasm(code,0))
        need(len(code)==size and len(refs)==0 and code==target
             and len(native)==len(generated)==x86 and
             sum(i.size for i in native)==size
             and sum(i.size for i in generated)==size,
             'F799 complete original machine-code identity wrong '+typ)
        need(native[-1].mnemonic=='ret' and
             (not retstr or native[-1].op_str==retstr),
             'F799 physical thiscall ABI stack-return changed '+typ)
        need(all(a.bytes==b.bytes for a,b in zip(native,generated)),
             'F799 actual physical original x86 machine instruction differs '+typ)
        records.append({'candidate':typ,'native_original_start':address,
                        'original_complete_CODE_B':size,'native_original_x86':x86,
                        'full_native_PE_nonfield_bytes_equal':size,
                        'real_PE_COFF_relocation_fields':0,
                        'source_form':'normal VC7.1 C++ borrowed member method',
                        'historical_function_origin':'unknown',
                        'accepted_new_authored_whole_CODE_B':0})
    # Independent semantic-equivalent source contrast: no masking or
    # trimming of nonnative C++ to fabricate a 31B function.
    exact='return 0 < (statusAt74->flagsAt3C & 0x20);'
    alternative='return (statusAt74->flagsAt3C & 0x20) != 0;'
    need(source.count(exact)==1,'original native bool expression missing')
    other=compile_one('not-equal-negative',source.replace(exact,alternative))
    sym=ROWS['flag'][3]
    obj_bad,ref_bad=rd.object_function(other,sym)
    bad_instructions=list(d.disasm(obj_bad,0))
    need(len(obj_bad)==29 and len(bad_instructions)==14 and len(ref_bad)==0
         and obj_bad!=rd.pe_bytes_at(pe,0x00454F70,31),
         'ordinary nonnative !=0 control unexpectedly matches real 31B original')
    record={'original_target':'user supplied Japanese th075.exe',
            'two_complete_original_functions':records,
            'normal_explicit_minus_zero_source_incorrect_B':29,
            'original_unsigned_ordered_compare_native_B':31,
            'both_original_source_equivalents_machine_code_exact':True,
            'attribution_inference':'unknown; no reliable independent game ownership',
            'formal_authored_exact_functions_delta':0,
            'cold_all_accepted_units_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(record,indent=2)+chr(10))
    print('F799: two entire PE originals now C++ codegen exact: setter 004135F0 40/40B 16 x86, flag 00454F70 31/31B 15 x86, zero COFF fields. Equivalent !=0 emits incorrect 29/31B. Both remain unknown origin; ZERO formal authored exact credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F799 original whole unknown owner leaves FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
