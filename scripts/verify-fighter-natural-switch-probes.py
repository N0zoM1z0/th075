#!/usr/bin/env python3
"""Fresh VC7.1 source probe for two original giant fighter switch front-ends.

Construct one *natural C++* switch for each entire native action-ID topology,
using only actual explicitly branched or nondefault indexed case IDs. Case
bodies are distinct placeholder stores; **not reconstructed boss C++**. Check
all 66 original dispatch instructions and 325 bytes of dispatch geometry,
then verify entire original post-RET native sparse-index maps and candidate
COFF switch-table relocation partitions. No target bytes, object bytes or
assembly are copied into the generated sources; never credits any giant CODE.

This runs exactly two bounded standalone compiler probes (or --boss one).
It never runs the all-unit cold replay.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / '.analysis/f538-natural-fighter-switch-source'
BOSSES = {'Reimu':0x0045DD70,'CharacterMove':0x004AC040}
ORIG = ROOT / 'config/fighter-boss-dispatch-fingerprints.json'
MATCH = ROOT / 'scripts/compare-coff-function.py'
ACTION = ROOT / 'scripts/report-fighter-action-handlers.py'
CMP32 = re.compile(r'^dword ptr (\[ebp - (?:0x[0-9a-f]+|\d+)\]), 0x32$')
EBP = re.compile(r'\[ebp - (?:0x[0-9a-f]+|\d+)\]')
INDEXED = re.compile(r'^dword ptr \[([a-z]{3})\*4(?: \+ 0x[0-9a-f]+)?\]$')
SPARSE = re.compile(r'byte ptr \[([a-z]{3})(?: \+ 0x[0-9a-f]+)?\]')


def require(condition: bool, msg: str) -> None:
    if not condition:
        raise ValueError(msg)


def module(name: str, file: Path):
    spec=importlib.util.spec_from_file_location(name,file)
    require(spec is not None and spec.loader is not None, f'missing {file}')
    m=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=m
    spec.loader.exec_module(m)
    return m


def sha(raw:bytes)->str:
    return hashlib.sha256(raw).hexdigest()


def generate_probe(tag: str, mapped: list[dict], default: str)->tuple[str,int]:
    # Deliberately NO guessed case handlers, native-address fragments, fake
    # locals, asm, padding, stub classes standing in for full source, etc.
    # These independently observable case IDs force VC7.1 to retain distinct
    # switch targets and select its own jump-table/sparse-map strategy.
    ids=sorted(int(x['action']) for x in mapped
               if x['kind']=='singleton' or x['handler']!=default)
    require(len(ids)==len(set(ids)) and ids,'duplicate/nonexistent native cases')
    source=f'''// F538 natural switch *probe*, not original fighter source or CODE credit.
// This file is regenerable from the original PE under ignored .analysis.
class FighterSwitchF538_{tag} {{ public: void Advance(); }};
extern unsigned int g_FighterProbeMarker;
#define RAW reinterpret_cast<char*>(this)
#define I16(off) *reinterpret_cast<signed short*>(RAW+(off))
#define OWNER (*reinterpret_cast<char**>(RAW+0x2E8))
void FighterSwitchF538_{tag}::Advance() {{
    if (I16(0x82) != 0 || *reinterpret_cast<signed short*>(OWNER+0x3BA) != 0)
        return;
    switch (I16(0x60)) {{
'''
    for case in ids:
        source+=f'        case 0x{case:X}: g_FighterProbeMarker = {case+1}; break;\n'
    source+='''        default: g_FighterProbeMarker = 0;
    }
}
#undef OWNER
#undef I16
#undef RAW
'''
    return source,len(ids)


def source_object(tag:str,source:str)->Path:
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT / (tag+'-natural-switch.cpp')
    obj=OUT / (tag+'-natural-switch.obj')
    cpp.write_text(source)
    env=os.environ.copy()
    for name in ('DISPLAY','WAYLAND_DISPLAY'):
        env.pop(name,None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    completed=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                              '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                             env=env,cwd=ROOT,text=True,capture_output=True,
                             check=False,timeout=120)
    (OUT / (tag+'-compiler.log')).write_text(completed.stdout+completed.stderr)
    require(completed.returncode==0, f'{tag}: VC7.1 probe failed; inspect {cpp.with_suffix(".log")} or the generated compiler log')
    return obj


def dispatcher(ins, first_table: int, full_end: int):
    """From natural C++ input load through final indexed jump, excluding case bodies."""
    positions={i.address:j for j,i in enumerate(ins)}
    guard_cmp=[j for j,i in enumerate(ins)
               if i.mnemonic=='cmp' and CMP32.fullmatch(i.op_str)]
    require(len(guard_cmp)>=1, 'missing original switch upper-bound decision')
    start_index=guard_cmp[0]-3
    require(start_index>=0,'missing original action-state load')
    check_start=ins[start_index]
    require(check_start.mnemonic=='mov' and 'dword ptr [ebp - ' in check_start.op_str,
            'action-state load is not native receiver-relative')
    last=[x for x in ins if x.mnemonic=='jmp' and INDEXED.fullmatch(x.op_str)]
    require(len(last)==6,'original large boss should have six indirect dispatch tables')
    end=last[-1].address+last[-1].size
    subset=[i for i in ins if check_start.address<=i.address<end]
    require(sum(x.size for x in subset)==end-check_start.address,
            'native switch dispatch contains disassembly gaps')
    require(end<=full_end,'native dispatch crosses entire function bound')
    return subset,check_start.address,end


def grammar(ins,start,end):
    """No target branch addresses or stack offsets are assumed identical.

    But opcode, instruction sizes, input constants, register allocations,
    internal branch destinations, and ordering must ALL agree. Native
    relocations stay as distinct physical fields, never masked in a CODE
    exactness comparison. This is only a *switch topology* proof.
    """
    def normalized(i):
        op=EBP.sub('[EBP_SLOT]',i.op_str)
        op=INDEXED.sub(lambda m:'dword ptr ['+m.group(1)+'*4+ORIGINAL_TABLE]',op)
        if i.mnemonic=='movzx':
            op=SPARSE.sub(lambda m:'byte ptr ['+m.group(1)+'+ORIGINAL_INDEX]',op)
        if i.mnemonic in ('ja','je','jg','jne','jmp') and not op.startswith('dword ptr'):
            dest=int(op,16)
            op=f'LOCAL+{dest-start:03X}' if start<=dest<end else 'OUTSIDE_NATIVE_DISPATCH'
        return (i.mnemonic,i.size,op)
    return [normalized(i) for i in ins]


def canonical_partitions(locations):
    labels={};seq=[]
    for loc in locations:
        if loc not in labels: labels[loc]=len(labels)
        seq.append(labels[loc])
    return seq


def verify_one(tag:str, boss:dict, pe, reader, action, decoder)->dict:
    native_report, entries=action.report_boss(reader,pe,decoder,boss)
    cpp, concrete=generate_probe(tag,entries,native_report['default'])
    obj=source_object(tag,cpp)
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF538_{tag}@@QAEXXZ')
    orig_code=reader.pe_bytes_at(pe,boss['address'],boss['size'])
    original=list(decoder.disasm(orig_code,boss['address']))
    # Candidate contains genuine x86 CODE and its after-RET original-shaped
    # COFF DATA; disassemble only through the first complete original RET.
    fake=[]
    for i in decoder.disasm(code,0):
        fake.append(i)
        if i.mnemonic=='ret':break
    require(fake[-1].mnemonic=='ret','probe has no complete normal function RET')
    physical_data_start=fake[-1].address+fake[-1].size
    native_disp,native_start,native_end=dispatcher(original,boss['tables'][0]['jmp'],boss['address']+boss['size'])
    probe_disp,probe_start,probe_end=dispatcher(fake,0,physical_data_start)
    require((native_end-native_start)==(probe_end-probe_start)==325,
            f'{tag}: original full 325-byte switch dispatch geometry not retained')
    ng,cg=grammar(native_disp,native_start,native_end),grammar(probe_disp,probe_start,probe_end)
    require(len(ng)==len(cg)==66, f'{tag}: incomplete native instruction alignment')
    diffs=[(index,n,c) for index,(n,c) in enumerate(zip(ng,cg)) if n!=c]
    require(not diffs, f'{tag}: original 66 instruction grammar differs; first {diffs[:5]}')
    require(len(code)-physical_data_start==boss['postret_size'],
            f'{tag}: generated C++ has wrong COMPLETE post-RET switch table/data extent')
    native_default=int(native_report['default'],16)
    # First JA within physical indexed dispatch targets default; all six JA
    # targets are separately checked by F537 against original native CODE.
    ja=[int(i.op_str,16) for i in probe_disp if i.mnemonic=='ja']
    require(len(ja)==6 and len(set(ja))==1, f'{tag}: probe has inconsistent JA default')
    candidate_default=ja[0]
    physical=physical_data_start
    original_dense=[];candidate_dense=[]
    sparse_bytes=0; slots=0;maps=0
    for t in boss['tables']:
        n=t['slots'];bounds=4*n
        native=reader.pe_bytes_at(pe,t['dense_addr'],bounds)
        native_dest=[int.from_bytes(native[i:i+4],'little') for i in range(0,bounds,4)]
        reflist=sorted((r for r in refs if physical<=r['offset']<physical+bounds),key=lambda r:r['offset'])
        require(len(reflist)==n, f'{tag}: missing physical COFF DWORD destination refs')
        require(all(r['type']=='DIR32' and r['offset']==physical+4*j
                    and r['local_symbol_offset'] is not None for j,r in enumerate(reflist)),
                f'{tag}: invalid/fake original-style physical jump relocation')
        candidate_dest=[r['local_symbol_offset'] for r in reflist]
        require([x==native_default for x in native_dest]==[x==candidate_default for x in candidate_dest],
                f'{tag}: default-case slot topology differs from full original table')
        original_dense.extend(native_dest);candidate_dense.extend(candidate_dest)
        physical+=bounds;slots+=n
        if t['map_addr'] is not None:
            original_map=reader.pe_bytes_at(pe,t['map_addr'],t['map_length'])
            candidate_map=code[physical:physical+t['map_length']]
            require(bytes(candidate_map)==original_map,
                    f'{tag}: genuine original sparse byte index map mismatch (not just matching sizes)')
            require(sha(bytes(candidate_map))==t['map_sha'],
                    f'{tag}: original sparse-map witness SHA changed')
            physical+=len(candidate_map);sparse_bytes+=len(candidate_map);maps+=1
    require(physical==len(code) and slots==sum(t['slots'] for t in boss['tables']),
            f'{tag}: nonphysical trailing or missing table bytes')
    require(canonical_partitions(original_dense)==canonical_partitions(candidate_dense),
            f"{tag}: generated switch case partition is not original")
    return {'boss':f'0x{boss["address"]:08X}', 'original_full_CODE':boss['size'],
            'natural_cpp_cases':concrete,'dispatch_bytes':native_end-native_start,
            'native_instructions_aligned':len(ng),'dense_coff_refs':slots,
            'exact_sparse_index_bytes':sparse_bytes,'sparse_maps':maps,
            'full_postret_data_shape':len(code)-physical_data_start,
            'source':str((OUT / (tag+'-natural-switch.cpp')).relative_to(ROOT)),
            'object':str(obj.relative_to(ROOT))}


def main() -> None:
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--boss',choices=tuple(BOSSES),help='Rebuild/check only the named original giant fighter')
    a=ap.parse_args()
    reader=module('f538_comparison',MATCH)
    action=module('f538_physical_actions',ACTION)
    pe=reader.verified_target()
    all_bosses={x['address']:x for x in json.loads(ORIG.read_text())['bosses']}
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    outcomes=[]
    for tag,addr in BOSSES.items():
        if a.boss is not None and tag!=a.boss:continue
        outcome=verify_one(tag,all_bosses[addr],pe,reader,action,decoder)
        outcomes.append(outcome)
        print(f'{tag} original giant {outcome["original_full_CODE"]:,} native CODE: '
              f'one natural C++ switch with {outcome["natural_cpp_cases"]} explicit cases; '
              f'{outcome["native_instructions_aligned"]} original instruction grammars / '
              f'{outcome["dispatch_bytes"]} dispatch bytes aligned; '
              f'{outcome["dense_coff_refs"]} original-style DWORD table COFF refs, '
              f'{outcome["exact_sparse_index_bytes"]}/{outcome["exact_sparse_index_bytes"]} '
              f'original-index bytes identical; full {outcome["full_postret_data_shape"]} '
              'DATA shape and destination partition matched')
    print(f'Fresh standalone VC7.1 switch probes: {len(outcomes)}/{len(outcomes)} validated; '
          'NO full giant C++ code match, no accepted CODE/DATA, no all-unit replay')
    (OUT/'summary.json').write_text(json.dumps(outcomes,indent=2)+'\n')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('error: original fighter switch compiler probe:',exc,file=sys.stderr)
        raise SystemExit(1)
