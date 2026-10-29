#!/usr/bin/env python3
"""Cold-compile real C++ case-zero logic inside two original giant switch shapes.

Then verify the *complete* 50-instruction original action-zero case, all nine
actual call/global COFF references, x87 ordering and conditional branch graph
against **all eleven** fully hash-verified multi-switch boss originals.
Only regenerable single-TU probes are compiled: no whole-boss exact claim,
no partial native CODE accepted, no all-unit replay.
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
BOI={'Reimu':0x0045DD70,'CharacterMove':0x004AC040}
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


def find_generated_case(code,decoder):
    instruction=[]
    for x in decoder.disasm(code,0):
        instruction.append(x)
        if x.mnemonic=='ret': break
    indexed=[j for j,x in enumerate(instruction) if x.mnemonic=='jmp' and INDEXED.fullmatch(x.op_str)]
    require(len(indexed)==6,'generated C++ switch lost original six-table lowering')
    start=indexed[-1]+1
    require(len(instruction)>start+50,'generated action-zero body unexpectedly truncated')
    result=instruction[start:start+50]
    require(sum(i.size for i in result)==180 and len(result)==50,
            'generated natural C++ action-zero case lost 180-byte x86 sequence')
    require(result[-1].mnemonic=='jmp','natural case is not connected to common return')
    assert_case_register_dataflow(result)
    return result


def main():
    arg=argparse.ArgumentParser(description=__doc__)
    arg.add_argument('--boss',choices=tuple(BOI),help='Compile only the named natural case-zero candidate')
    opts=arg.parse_args()
    reader=load_module('f540_reader',ROOT/'scripts/compare-coff-function.py')
    action=load_module('f540_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    natural=load_module('f540_switch_source',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    all_bosses=json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
    indexed={x['address']:x for x in all_bosses}
    originals=[]
    # Read *all eleven* original full giant native CODE SHA identities, then
    # extract exactly independently native-bounded complete 50-insn cases.
    for boss in all_bosses:
        if len(boss['tables'])<=1:continue
        zero,ins=action_zero_original(reader,pe,decoder,action,boss)
        original_refs=reference_sequence(ins)
        originals.append((boss,zero,ins,original_refs))
    require(len(originals)==11,'all eleven native action-zero originals are required')
    outcomes=[]
    for tag,addr in BOI.items():
        if opts.boss and opts.boss!=tag:continue
        # Reuses the verified *whole* native action-ID topology, not invented
        # case numbers, and preserves real F539 single-switch grouping.
        report,mapped=action.report_boss(reader,pe,decoder,indexed[addr])
        base,cases=natural.generate_probe(tag,mapped,report['default'])
        require(cases in (143,151),'incomplete original fighter case vocabulary')
        obj=compile_one(tag,generate(base,tag))
        raw,relocs=reader.object_function(obj,f'?Advance@FighterSwitchF540_{tag}@@QAEXXZ')
        generated=find_generated_case(raw,decoder)
        source_refs=reference_sequence(generated,relocs)
        source_grammar=case_grammar(generated)
        source_exact_registers=case_grammar(generated,register_sensitive=True)
        parity=[]
        for boss,zero,real,refs in originals:
            require(refs==source_refs,'native/compiled exact physical reference sequence differs')
            require(case_grammar(real)==source_grammar,
                    f'{boss["address"]:08X}: natural C++ action-zero x87/control-flow differs')
            if boss['address']==addr:
                require(case_grammar(real,register_sensitive=True)==source_exact_registers,
                        f'{tag}: natural C++ has unexpected receiver-register allocation')
            # A native receiver EBP slot beyond signed disp8 costs 3 bytes on
            # every one of its 14 real loads; absolutely no fake padding.
            slot=int(zero['this_slot'].split('0x')[1],16)
            normal_bytes=180 if slot<128 else 222
            require(zero['bytes']==normal_bytes,'original receiver relocation width differs')
            parity.append(zero['bytes'])
        outcomes.append({'tag':tag,'native_boss':f'0x{addr:08X}',
                        'whole_original_CODE':indexed[addr]['size'],
                        'cpp_cases':cases,'native_originals_compared':len(originals),
                        'matched_insns_per_case':50,
                        'physical_refs_per_case':len(source_refs),
                        'normal_native_case_bytes':sum(x==180 for x in parity),
                        'wide_native_case_bytes':sum(x==222 for x in parity)})
        print(f'{tag}: one natural C++ action-zero source, 50/50 x86 control/x87 '
              f'instructions and 9/9 true COFF call/global fields; native 180-byte '
              f'signed-byte guard/position policy covers ALL {len(originals)} complete '
              'fighter originals (10 normal 180-byte cases, one real 222-byte disp32 case)')
    require(outcomes,'no boss probes selected')
    (OUT/'summary.json').write_text(json.dumps(outcomes,indent=2)+'\n')
    print('Fresh original VC7.1 local-only probe '+str(len(outcomes))+'/'+str(len(outcomes))+
          ': no whole giant C++ exact code, no partial CODE credit and no full replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as error:
        print('fighter action-zero native C++ evidence failed:',error,file=sys.stderr)
        raise SystemExit(1)
