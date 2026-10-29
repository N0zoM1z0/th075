#!/usr/bin/env python3
"""Fresh VC7.1 C++ probes for first SIX native actions of 11 giant fighters.

Every original 28K-82K CODE function SHA and its full physical post-RET
switch tables are checked first. Each separate natural C++ prototype models
six complete gameplay cases (0..5); other cases remain diagnostic marker
stores. Compiler results are case/source-codegen evidence, NEVER credited
as exact independent functions or partial main-boss CODE. Compile only
these selected new units, never all 942 accepted cold-replay units.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import math
import os
from pathlib import Path
import re
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / '.analysis/f545-opening-six-actions'
PINNED = ROOT / 'config/fighter-boss-dispatch-fingerprints.json'
NAMES = {0x0045DD70: 'Reimu', 0x004AC040: 'CharacterMove'}


def require(condition, detail):
    if not condition:
        raise ValueError(detail)


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    require(spec is not None and spec.loader is not None, f'missing helper {path}')
    loaded = importlib.util.module_from_spec(spec)
    sys.modules[name] = loaded
    spec.loader.exec_module(loaded)
    return loaded


def native_six(reader, target, decoder, boss):
    """Read complete physical cases 0..5, bounded by 7 actual DWORD slots."""
    require(boss['jump_count'] in (6, 7) and boss['tables'][0]['slots'] == 11
            and boss['tables'][0]['map_addr'] is None,
            'not an original 11-way direct first action switch')
    dense = reader.pe_bytes_at(target, boss['tables'][0]['dense_addr'], 7*4)
    addresses = [int.from_bytes(dense[4*k:4*k+4], 'little') for k in range(7)]
    require(addresses == sorted(set(addresses)), 'native action-zero through six address layout changed')
    check = []
    for index in range(6):
        start, end = addresses[index:index+2]
        require(boss['address'] <= start < end <= boss['address']+boss['size'],
                'original action case physical CODE outside whole boss')
        code = reader.pe_bytes_at(target, start, end-start)
        ins = list(decoder.disasm(code, start))
        require(ins and ins[0].address==start and ins[-1].address+ins[-1].size==end,
                f'original action {index} CODE instruction bounds incomplete')
        check.append(ins)
    require([len(x) for x in check]==[50,60,50,60,3,3],
            'original first six action-case complete native instruction counts changed')
    return check


def original_float(ins, index):
    """Native physical case 4/5 are one owner load, one float store, JMP."""
    require(len(ins) == 3 and [x.mnemonic for x in ins]==['mov','mov','jmp'],
            f'original action {index}: no genuine 3-instruction constant store')
    dest = re.fullmatch(r'dword ptr \[([a-z]{3}) \+ 0x50\], (0x[0-9a-f]+)', ins[1].op_str)
    require(dest is not None and re.fullmatch(r'([a-z]{3}), dword ptr \[ebp - 0x[0-9a-f]+\]', ins[0].op_str),
            'original action 4/5 not a float position member assignment')
    require(ins[0].op_str.split(',', 1)[0]==dest.group(1),
            'original action 4/5 owner receiver register mismatch')
    raw = int(dest.group(2),16).to_bytes(4,'little')
    value = struct.unpack('<f',raw)[0]
    require(math.isfinite(value) and value != 0.0, 'nonfinite/zero original float constant')
    return value


def as_float_literal(value):
    # Meaningful native float value, never an x86 DWORD or byte-array literal.
    s = repr(value)
    if '.' not in s and 'e' not in s.lower(): s += '.0'
    return s+'f'


def source_for(switch, casezero, actionone, native, mapped, tag, originals):
    generic,case_count=switch.generate_probe(tag,mapped,native['default'])
    complete_first_two=actionone.case_source(generic,casezero,tag)
    original_type=f'FighterSwitchF542_{tag}'
    new_type=f'FighterSwitchF545_{tag}'
    require(complete_first_two.count(original_type)>=2, 'action-one hypothesis owner changed')
    src=complete_first_two.replace(original_type,new_type)
    marker=lambda k:f'        case 0x{k:X}:'
    first=src[src.index(marker(0))+len(marker(0)):src.index(marker(1))]
    second=src[src.index(marker(1))+len(marker(1)):src.index(marker(2))]
    require(first.rstrip().endswith('break;') and second.rstrip().endswith('break;'),
            'real action-zero or action-one source lost complete case return')
    require('SetNativeActionAt40FAC0(2)' in second, 'native action-one state setter changed')
    for case, body in ((2,first),(3,second.replace('SetNativeActionAt40FAC0(2)',
                                                   'SetNativeActionAt40FAC0(0)'))):
        previous=marker(case)+f' g_FighterProbeMarker = {case+1}; break;'
        require(src.count(previous)==1, f'original case {case} not represented as a unique source label')
        src=src.replace(previous, marker(case)+body.rstrip())
    constants=[]
    for case in (4,5):
        number=original_float(originals[case],case)
        constants.append(number)
        previous=marker(case)+f' g_FighterProbeMarker = {case+1}; break;'
        require(src.count(previous)==1, 'missing original case 4/5 source label')
        src=src.replace(previous, marker(case)+f' POS = {as_float_literal(number)}; break;')
    return src,case_count,constants


def compile_one(tag, source):
    OUT.mkdir(parents=True, exist_ok=True)
    cpp=OUT/f'{tag}-opening-six.cpp'
    obj=OUT/f'{tag}-opening-six.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None)
    env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     env=env,cwd=ROOT,text=True,capture_output=True,timeout=120)
    (OUT/f'{tag}-compile.log').write_text(p.stdout+p.stderr)
    require(p.returncode==0, f'{tag}: pinned VC7.1 compilation failed: {p.stderr}')
    return obj


def generated_six(reader, decoder, obj, tag, post_ret_bytes):
    code,relocs=reader.object_function(obj,f'?Advance@FighterSwitchF545_{tag}@@QAEXXZ')
    instructions=[]
    for i in decoder.disasm(code,0):
        instructions.append(i)
        if i.mnemonic=='ret':break
    require(instructions and instructions[-1].mnemonic=='ret', 'no complete candidate normal RET')
    start=instructions[-1].address+instructions[-1].size
    require(start < len(code) and len(code)-start==post_ret_bytes,
            'generated C++ full post-RET table DATA shape differs from original')
    first=sorted((r for r in relocs if start<=r['offset']<start+28),key=lambda r:r['offset'])
    require(len(first)==7 and all(r['type']=='DIR32' and
            r['offset']==start+4*k and r['local_symbol_offset'] is not None for k,r in enumerate(first)),
            'candidate first 7 original table slots not real COFF DIR32')
    addr=[r['local_symbol_offset'] for r in first]
    require(addr==sorted(set(addr)) and 0<=addr[0]<addr[-1]<start,
            'candidate first six original action handlers overlap or exceed CODE')
    result=[]
    for k in range(6):
        a,b=addr[k:k+2]
        ins=list(decoder.disasm(code[a:b],a))
        require(ins and ins[0].address==a and ins[-1].address+ins[-1].size==b,
                'candidate first-six CASE CODE is not contiguous')
        result.append(ins)
    return code,relocs,instructions,start,result


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='One original PE address, Reimu or CharacterMove; otherwise all 11')
    args=parser.parse_args()
    reader=module('f545_coff',ROOT/'scripts/compare-coff-function.py')
    actions=module('f545_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f545_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f545_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f545_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses=[b for b in json.loads(PINNED.read_text())['bosses'] if b['jump_count']>1]
    require(len(bosses)==11 and sum(b['size'] for b in bosses)==613391,
            'whole original multi-switch fighter register changed')
    if args.boss:
        names={tag.lower():addr for addr,tag in NAMES.items()}
        key=args.boss.lower()
        selected=names[key] if key in names else int(args.boss,0)
        bosses=[b for b in bosses if b['address']==selected]
        require(len(bosses)==1,'unregistered original giant boss address')
    outcomes=[]
    for b in bosses:
        addr=b['address'];tag=NAMES.get(addr,f'Boss{addr:08X}')
        report,mapped=actions.report_boss(reader,pe,decoder,b)
        original=native_six(reader,pe,decoder,b)
        source,number,values=source_for(switch,zero,one,report,mapped,tag,original)
        obj=compile_one(tag,source)
        code,relocs,all_ins,postret,probes=generated_six(reader,decoder,obj,tag,b['postret_size'])
        expected_counts=[50,60,50,60,3,3]
        refs_count=0
        wide=int(report['case_zero']['this_slot'].split('0x')[1],16)>=128
        for k,(real,candidate) in enumerate(zip(original,probes)):
            require(len(real)==len(candidate)==expected_counts[k],
                    f'{addr:08X}: original action {k} complete instruction count differs')
            require(zero.case_grammar(real, register_sensitive=True)==
                    zero.case_grammar(candidate, register_sensitive=True),
                    f'{addr:08X}: action {k} original real register/branch/x87 operands mismatch')
            natural_bytes=sum(i.size for i in candidate)
            real_bytes=sum(i.size for i in real)
            extra=(42,51,42,51,3,3)[k] if wide else 0
            require(real_bytes==natural_bytes+extra,
                    f'{addr:08X}: native action {k} has unexplained stack displacement width difference')
            if k in (0,2):
                zero.assert_case_register_dataflow(real)
                zero.assert_case_register_dataflow(candidate)
                require(zero.reference_sequence(real)==zero.reference_sequence(candidate,relocs),
                        f'{addr:08X}: action {k} nine physical original COFF fields differ')
                refs_count+=9
            elif k in (1,3):
                one.check_receiver_dataflow(real)
                one.check_receiver_dataflow(candidate)
                require(one.inspect_field_grammar(real)==one.inspect_field_grammar(candidate,relocs),
                        f'{addr:08X}: action {k} eleven physical original COFF fields differ')
                refs_count+=11
            else:
                require(not [r for r in relocs if candidate[0].address<=r['offset']<
                             candidate[-1].address+candidate[-1].size],
                        'action 4/5 must be genuinely relocation-free immediate float stores')
                require(original_float(real,k)==values[k-4],
                        'per-character action float constant inferred from wrong original member')
        require(refs_count==40,'not all 40 authentic original calls/float references verified')
        slots,indices,maps=zero.verify_physical_tables(b,report,pe,reader,switch,all_ins,code,relocs,postret)
        row={'boss':f'0x{addr:08X}', 'whole_original_CODE':b['size'],
             'native_full_six_instructions':sum(len(x) for x in original),
             'original_six_CODE_bytes':sum(sum(i.size for i in x) for x in original),
             'new_cpp_six_CODE_bytes':sum(sum(i.size for i in x) for x in probes),
             'native_x87_call_COFF_roles':refs_count, 'native_switches':b['jump_count'],
             'dense_COFF_refs':slots,'sparse_original_bytes':indices,
             'full_postret_data_shape':len(code)-postret,'explicit_source_cases':number,
             'action_four_float':values[0],'action_five_float':values[1]}
        outcomes.append(row)
        print(f'{addr:#010x}: 226/226 actual first-six native instructions, '
              f'{refs_count}/40 genuine call/constant fields, '
              f'{slots}/{slots} physical switch-table COFF fields, '
              f'{indices}/{indices} original sparse bytes; '
              f'action4/5 floats = {values[0]:g}/{values[1]:g}; '
              f'native six-case CODE {row["original_six_CODE_bytes"]} '
              f'vs probe {row["new_cpp_six_CODE_bytes"]} bytes',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(outcomes,indent=2)+'\n')
    print(f'New natural opening-action C++ probes: {len(outcomes)}/{len(bosses)} '
          'whole-original contexts checked, zero giant accepted exact CODE/DATA, '
          'no full-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('TH075 original first-six fighter action C++ research failed:',e,file=sys.stderr)
        raise SystemExit(1)
