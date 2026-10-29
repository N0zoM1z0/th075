#!/usr/bin/env python3
"""Fresh-compile natural C++ case-zero logic inside all eleven multi-switch fighters.

Each original **whole** giant CODE SHA256/after-RET table is verified first.
The original character-specific entire C++ switch topology is recovered from
native action-to-handler evidence, and a genuine signed-byte/x87 action-zero
branch is substituted into each generated natural C++ prototype. Then verify
all 50 native case instructions including original register choices/branches,
all 9 typed x87/call relocations, exact original sparse byte-index tables,
all physical DWORD COFF relocations and original target equivalence classes.
No full boss source is claimed; no partial CODE accepted; no all-unit replay.
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

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f540-natural-actionzero-source'
NAMED={0x0045DD70:'Reimu',0x004AC040:'CharacterMove'}
RELOC_FIELDS={
  'call':('REL32',0x00453E20,'ResetAt453E20'),
  'fcomp':('DIR32',0x0065782C,'g_ThresholdAt0065782C'),
  'fsub':('DIR32',0x00657478,'g_SubtractAt00657478'),
  'fadd':('DIR32',0x00658050,'g_RiseAt00658050'),
}
FRAME = re.compile(r'\[ebp - (?:0x[0-9a-f]+|\d+)\]')
VOLATILE_REGISTER = re.compile(r'\b(?:eax|ecx|edx)\b')
ABS = re.compile(r'\[(?:0x[0-9a-f]+|0)\]')
INDEXED = re.compile(r'^dword ptr \[[a-z]{3}\*4(?: \+ 0x[0-9a-f]+)?\]$')


def require(ok,why):
    if not ok:raise ValueError(why)


def load_module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    require(spec is not None and spec.loader is not None,f'missing source helper {path}')
    m=importlib.util.module_from_spec(spec)
    sys.modules[tag]=m
    spec.loader.exec_module(m)
    return m


def generate(src: str, tag: str):
    """Keep F539's single-switch compiler topology; replace only action 0.

    This is an actual proposed game C++ case-logic expression, but not an
    assertion that all native source types, ownership or entire boss match.
    """
    src=src.replace('FighterSwitchF539_', 'FighterSwitchF540_')
    src=src.replace('public: void Advance();','public: void Advance(); void ResetAt453E20();')
    src=src.replace('extern unsigned int g_FighterProbeMarker;', '''extern unsigned int g_FighterProbeMarker;
extern float g_ThresholdAt0065782C;
extern float g_SubtractAt00657478;
extern double g_RiseAt00658050;''')
    src=src.replace('#define OWNER', '''#define POS (*reinterpret_cast<float*>(RAW+0x50))
#define FLAG (*reinterpret_cast<signed char*>(RAW+0x3AC))
#define OWNER''')
    before='        case 0x0: g_FighterProbeMarker = 1; break;'
    require(src.count(before)==1,'expected exactly one physical action-zero case label')
    # The sign-sensitive native FCOMP/JP is why <= or >= would be WRONG.
    after='''        case 0x0:
            if (FLAG == 0) {
                ResetAt453E20();
            } else {
                if (POS > g_ThresholdAt0065782C) {
                    POS -= g_SubtractAt00657478;
                    if (POS < g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
                if (POS < g_ThresholdAt0065782C) {
                    POS += g_RiseAt00658050;
                    if (POS > g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
            }
            break;'''
    return src.replace(before,after)


def compile_one(tag,code):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}-casezero.cpp';obj=OUT/f'{tag}-casezero.obj'
    cpp.write_text(code)
    env=os.environ.copy()
    for n in ('DISPLAY','WAYLAND_DISPLAY'):env.pop(n,None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    process=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                           text=True,capture_output=True,cwd=ROOT,env=env,timeout=120)
    (OUT/f'{tag}-compiler.log').write_text(process.stdout+process.stderr)
    require(process.returncode==0,f'{tag}: VC7.1 native probe did not compile')
    return obj


def reference_sequence(ins,relocs=None):
    """Compare nine physical original REL32/DIR32 references by ordinal.

    Native PE operands are verified target addresses; candidate fields must
    be actual COFF relocation entries in the correct x86 instruction.
    """
    result=[]
    for ordinal,inst in enumerate(ins):
        if inst.mnemonic not in RELOC_FIELDS:continue
        typ,target,source=RELOC_FIELDS[inst.mnemonic]
        if relocs is None:
            if inst.mnemonic=='call':
                require(inst.op_str==f'0x{target:x}','not the original native reset callee')
            else:
                require(inst.op_str.endswith(f'[0x{target:x}]'),
                        'not the original x87 global address')
        else:
            fields=[r for r in relocs if inst.address<=r['offset']<inst.address+inst.size]
            require(len(fields)==1 and fields[0]['type']==typ
                    and source in fields[0]['symbol'],
                    f'missing real typed COFF relocation at instruction {ordinal}')
        result.append((ordinal,inst.mnemonic,typ,target))
    require(len(result)==9,'native action-zero requires 3 REL32 calls and 6 DIR32 globals')
    require([x[1] for x in result]==['call','fcomp','fsub','fcomp','call','fcomp','fadd','fcomp','call'],
            'native x87/reset physical reference sequence changed')
    return result


def assert_case_register_dataflow(ins):
    """Allow compiler register rotations, never incorrect actual use/thiscall."""
    reloads=0
    for index,inst in enumerate(ins[:-1]):
        if inst.mnemonic=='movsx' and 'byte ptr [' in inst.op_str:
            match=re.fullmatch(r'(eax|ecx|edx), byte ptr \[[a-z]{3} \+ 0x3ac\]',inst.op_str)
            require(match is not None and ins[index+1].op_str==match.group(1)+', '+match.group(1)
                    and ins[index+1].mnemonic=='test', 'native signed flag does not drive next TEST')
        if inst.mnemonic!='mov':continue
        match=re.fullmatch(r'(eax|ecx|edx), dword ptr \[ebp - (?:0x[0-9a-f]+|\d+)\]',inst.op_str)
        if match is None:continue
        reloads+=1
        reg=match.group(1)
        next_ins=ins[index+1]
        if next_ins.mnemonic=='call':
            require(reg=='ecx','native reset call receiver is not thiscall ECX')
        else:
            require(f'[{reg} + ' in next_ins.op_str,
                    'native receiver reload is not consumed by the immediate property access')
    require(reloads==14,'native action-zero does not have exactly 14 real receiver reloads')


def case_grammar(ins,register_sensitive=False):
    address_to_ordinal={i.address:k for k,i in enumerate(ins)}
    observed=[]
    for x in ins:
        op=FRAME.sub('[SAVED_RECEIVER_SLOT]',x.op_str)
        op=ABS.sub('[PHYSICAL_GLOBAL_RELOC]',op)
        if x.mnemonic in ('je','jne','jp','jmp','jg','ja') and not op.startswith('dword ptr'):
            dest=int(op,16)
            op=('BRANCH_TO_INS_'+str(address_to_ordinal[dest]) if dest in address_to_ordinal
                else 'EXIT_WHOLE_CASE')
        if x.mnemonic=='call':op='ORIGINAL_RESET_METHOD'
        if not register_sensitive:
            op=VOLATILE_REGISTER.sub('VALIDATED_FREE_REGISTER',op)
        observed.append((x.mnemonic,op))
    return observed


def action_zero_original(reader,pe,decoder,actions,boss):
    report,_=actions.report_boss(reader,pe,decoder,boss)
    zero=report['case_zero']
    require(zero is not None,'not a full native multi-table action-zero original')
    start=int(zero['start'],16);end=int(zero['end_exclusive'],16)
    instr=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    require(len(instr)==50 and sum(i.size for i in instr)==end-start,
            'native action-zero case boundaries are not complete')
    assert_case_register_dataflow(instr)
    return zero,instr


def candidate_instructions(code, decoder):
    """Bound generated normal CODE at its own first complete RET."""
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    require(ins and ins[-1].mnemonic=='ret','no complete natural C++ normal RET')
    end=ins[-1].address+ins[-1].size
    require(end<len(code),'native C++ did not emit real after-RET table DATA')
    return ins,end


def generated_case(ins, expected_jumps):
    indexed=[j for j,x in enumerate(ins) if x.mnemonic=='jmp'
             and INDEXED.fullmatch(x.op_str)]
    require(len(indexed)==expected_jumps, 'generated switch lost original table count')
    start=indexed[-1]+1
    require(len(ins)>start+50,'generated original action-zero C++ body truncated')
    result=ins[start:start+50]
    require(len(result)==50 and sum(i.size for i in result)==180,
            'natural C++ action-zero must have original normal 180-byte code')
    require(result[-1].mnemonic=='jmp','case-zero must join common return')
    assert_case_register_dataflow(result)
    return result


def verify_physical_tables(boss, native_summary, pe, reader, natural, ins, code, refs, start):
    """All actual original and generated COFF jump-table DATA and partitions."""
    jumps=[x for x in ins if x.mnemonic=='jmp' and INDEXED.fullmatch(x.op_str)]
    require(len(jumps)==boss['jump_count'], 'not all native switch instructions re-emitted')
    guards=[x for x in ins if x.mnemonic=='ja']
    require(len(guards)==len(jumps) and len({i.op_str for i in guards})==1,
            'native-bound unsigned default guards differ in generated C++')
    probe_default=int(guards[0].op_str,16)
    native_default=int(native_summary['default'],16)
    physical=start;slots=0;bytes_index=0;origdest=[];canddest=[];maps=0
    for table in boss['tables']:
        n=table['slots'];raw=reader.pe_bytes_at(pe,table['dense_addr'],4*n)
        original=[int.from_bytes(raw[k:k+4],'little') for k in range(0,len(raw),4)]
        here=sorted((r for r in refs if physical<=r['offset']<physical+4*n),
                    key=lambda r:r['offset'])
        require(len(here)==n and all(r['type']=='DIR32' and
                r['offset']==physical+4*k and r['local_symbol_offset'] is not None
                for k,r in enumerate(here)), 'missing/extra physical COFF DWORD switch table relocations')
        actual=[r['local_symbol_offset'] for r in here]
        require([x==native_default for x in original]==[x==probe_default for x in actual],
                'candidate C++ default-slot placement differs from full native original')
        origdest+=original;canddest+=actual
        physical+=4*n;slots+=n
        if table['map_addr'] is not None:
            native=reader.pe_bytes_at(pe,table['map_addr'],table['map_length'])
            candidate=bytes(code[physical:physical+table['map_length']])
            require(candidate==native, 'candidate compiler emitted incorrect native sparse-index data')
            require(natural.sha(candidate)==table['map_sha'], 'original sparse-map SHA changed')
            physical+=len(native);bytes_index+=len(native);maps+=1
    require(physical==len(code) and len(code)-start==boss['postret_size'],
            'candidate switch DATA is not the full genuine original physical extent')
    require(slots==boss['dense_entries'] and bytes_index==boss['sparse_bytes'],
            'candidate post-RET DWORD or sparse-byte count drifted')
    require(natural.canonical_partitions(origdest)==natural.canonical_partitions(canddest),
            'same-source C++ did not reproduce cross-table original handler partition')
    return slots,bytes_index,maps


def main():
    arg=argparse.ArgumentParser(description=__doc__)
    arg.add_argument('--boss', help='Build one full original multi-switch boss by PE address; also Reimu or CharacterMove')
    opts=arg.parse_args()
    reader=load_module('f540_reader',ROOT/'scripts/compare-coff-function.py')
    action=load_module('f540_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    natural=load_module('f540_switch_source',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    bosses=json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
    candidates=[b for b in bosses if len(b['tables'])>1]
    require(len(candidates)==11,'full original 11-multi-switch fighter register has changed')
    if opts.boss:
        lookup=opts.boss.lower()
        byname={value.lower():key for key,value in NAMED.items()}
        selected=byname[lookup] if lookup in byname else int(opts.boss,0)
        candidates=[b for b in candidates if b['address']==selected]
        require(len(candidates)==1,'unregistered multi-switch original boss address')
    outcomes=[]
    for boss in candidates:
        addr=boss['address'];tag=NAMED.get(addr,f'Boss{addr:08X}')
        # Whole original source identity and full entire native switch DATA
        # are independently attested before any diagnostic recompilation.
        native,mapped=action.report_boss(reader,pe,decoder,boss)
        zero,original=action_zero_original(reader,pe,decoder,action,boss)
        original_refs=reference_sequence(original)
        base,number_cases=natural.generate_probe(tag,mapped,native['default'])
        cpp=generate(base,tag)
        obj=compile_one(tag,cpp)
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF540_{tag}@@QAEXXZ')
        ins,original_end=candidate_instructions(code,decoder)
        candidate=generated_case(ins,boss['jump_count'])
        compiled_refs=reference_sequence(candidate,refs)
        require(original_refs==compiled_refs,
                f'{addr:08X}: 9 physical original call and data COFF references changed')
        require(case_grammar(original,register_sensitive=True)==case_grammar(candidate,register_sensitive=True),
                f'{addr:08X}: natural C++ case-zero exact per-fighter GPR/x87/branch grammar differs')
        # Original has a true 222-byte body at EBP-0x88; no synthetic
        # padding/local is introduced into the C++ candidate's 180 bytes.
        slot=int(zero['this_slot'].split('0x')[1],16)
        require(zero['bytes']==(222 if slot>=128 else 180)
                and zero['this_slot_reads']==14,'native action-zero disp32 accounting changed')
        slots,idxbytes,maps=verify_physical_tables(boss,native,pe,reader,natural,
                                                   ins,code,refs,original_end)
        summary={'original_boss':f'0x{addr:08X}', 'whole_original_CODE':boss['size'],
                 'cpp_cases':number_cases, 'native_jumps':boss['jump_count'],
                 'original_case_zero_bytes':zero['bytes'], 'candidate_case_zero_bytes':180,
                 'matched_case_zero_instructions':len(candidate),
                 'genuine_typed_case_zero_relocations':len(compiled_refs),
                 'full_native_jumptable_COFF_fields':slots, 'exact_original_sparse_bytes':idxbytes,
                 'original_sparse_map_count':maps, 'full_original_postret_shape':len(code)-original_end}
        outcomes.append(summary)
        print(f'{addr:#010x}: 50/50 real native x87/branch/register instructions, '
              f'9/9 authentic COFF case references; {boss["jump_count"]} compiler jumps, '
              f'{slots}/{slots} original-style DWORD COFF refs, '
              f'{idxbytes}/{idxbytes} byte-identical sparse original indexes, '
              f'{len(code)-original_end} real original post-RET DATA layout; '
              f'case source {zero["bytes"]} native vs 180 generated',flush=True)
    (OUT/'summary.json').write_text(json.dumps(outcomes,indent=2)+'\n')
    print(f'Fresh bounded VC7.1 C++ action-zero+whole-dispatch probes: '
          f'{len(outcomes)}/{len(candidates)} validated. Only explicitly involved TUs compiled; '
          'NO whole giant C++ exact source, partial CODE credit or all-unit replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as error:
        print('fighter action-zero native C++ evidence failed:',error,file=sys.stderr)
        raise SystemExit(1)
