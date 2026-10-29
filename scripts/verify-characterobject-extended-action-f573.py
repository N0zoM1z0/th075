#!/usr/bin/env python3
"""F573: add a complete 248-instruction x87 actor action 0x32A to F572.

Freshly compile only the affected natural VC7.1 C++ TU and read the
33,293-byte original Japanese TH075 v1.11 giant independently. Verify
each of 11 complete action code spans, their genuine native call/global
COFF fields and whole original 60-slot sparse jump DATA. For action 0x32A
one exact documented instruction-order nonidentity is permitted ONLY
between two independent read-only owner loads; no x86/code byte graft
is made or counted as exact. The full giant remains CODE nonexact.
No all-unit cold replay.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
OUT=ROOT/'.analysis/f573-characterobject-action32a'
ADDRESS=0x004EBDA0
FIRST=0x320
LAST=0x32A
TARGETS={
    0x0045B830:('REL32','ResetAt45B830'),
    0x00453A70:('REL32','SpawnAt453A70'),
    0x0040FBB0:('REL32','ResetStateAt40FBB0'),
    0x00453D40:('REL32','ModifyAt453D40'),
    0x0040FAC0:('REL32','SetActionAt40FAC0'),
    0x0040FA30:('REL32','GetStateAt40FA30'),
    0x0040FB40:('REL32','SetStateAt40FB40'),
    0x0065782C:('DIR32','gCompareAt0065782C'),
    0x0065747C:('DIR32','gCompareAt0065747C'),
    0x00657480:('DIR32','gCompareAt00657480'),
    0x00657CF8:('DIR32','gCompareAt00657CF8'),
    0x00657D14:('DIR32','gCompareAt00657D14'),
    0x00657874:('DIR32','gCompareAt00657874'),
    0x00658058:('DIR32','gDropAt00658058'),
    0x00657CC0:('DIR32','gLiftAt00657CC0'),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         f'missing original-backed verifier {path}')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def candidate_object():
    OUT.mkdir(parents=True,exist_ok=True)
    src=SOURCE.read_text()
    need('F572/F573' in src and src.count('case 0x32A: {')==1
         and 'case 0x370: g_FighterProbeMarker = 881; break;' in src,
         'must retain original source and diagnostic marker on unmodeled next action')
    need(src.count('if (*(&F32(0xC8)) == gCompareAt')==6,
         'six true independent x87 equality-condition source expressions changed')
    obj=OUT/'CharacterObjectActionsF573.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
                         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                        env=env,cwd=ROOT,text=True,capture_output=True,timeout=120)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'fresh original-profile VC7.1 source compile failed: {proc.stderr}')
    return obj


def actual_case32a_fields(native,compiled,relocs):
    need(len(native)==len(compiled)==248,'original game case32a whole instruction extent changed')
    start,end=compiled[0].address,compiled[-1].address+compiled[-1].size
    physical=[r for r in relocs if start<=r['offset']<end]
    observed=[]
    for ordinal,x in enumerate(native):
        if x.mnemonic=='call' and x.op_str.startswith('0x'):
            kind='REL32';target=int(x.op_str,16)
        elif x.mnemonic.startswith('f') and 'ptr [0x' in x.op_str:
            kind='DIR32';target=int(x.op_str.split('[0x',1)[1].split(']',1)[0],16)
        else:continue
        need(target in TARGETS,
             f'original native action32a direct call/x87 target unknown at instruction {ordinal}')
        expected_type, expected_symbol=TARGETS[target]
        need(kind==expected_type,'native opcode is not known physical COFF field type')
        if target==0x00453A70 and ordinal in (206,220):
            expected_symbol='SpawnDirectedAt453A70'
        y=compiled[ordinal]
        need(x.mnemonic==y.mnemonic,
             f'original case32a source COFF instruction moved at ordinal {ordinal}')
        record=[r for r in physical if y.address<=r['offset']<y.address+y.size]
        need(len(record)==1 and record[0]['type']==kind and record[0]['addend']==0
             and expected_symbol in record[0]['symbol'],
             f'original action32a native COFF field not reproduced at ordinal {ordinal}: {record}')
        observed.append((ordinal,kind,target))
    need(len(observed)==len(physical)==19,
         'actual complete native action32a must contain nineteen physical typed COFF fields')
    need([(k,x.mnemonic) for k,x in enumerate(native) if x.mnemonic=='fucompp']==
         [(k,x.mnemonic) for k,x in enumerate(compiled) if x.mnemonic=='fucompp']==
         [(80,'fucompp'),(91,'fucompp'),(102,'fucompp'),
          (113,'fucompp'),(124,'fucompp'),(135,'fucompp')],
         'genuine six independent native x87 FUCOMPP comparisons missing')
    return observed


def equivalent_independent_reads(native,compiled,f572):
    """Validate EXACTLY one authentic, harmless read-read instruction swap.

    Both memory instructions read immutable current owner/float state;
    MOV EDX only changes EDX, whereas FLD [ECX+0x48] uses ECX and x87.
    They have no register or memory dependency and never cross a branch
    or COFF field. This documents a real compiler-order mismatch, NOT
    true original machine-order/byte exactness.
    """
    first=f572.authentic_grammar(native,0x32A)
    second=f572.authentic_grammar(compiled,0x32A)
    diffs=[i for i,(x,y) in enumerate(zip(first,second)) if x!=y]
    need(diffs==[186,187],
         f'additional candidate-to-original instruction order mismatch: {diffs[:10]}')
    need(native[186].mnemonic=='mov' and
         native[186].op_str.startswith('edx, dword ptr [ebp - ') and
         native[187].mnemonic=='fld' and
         native[187].op_str=='dword ptr [ecx + 0x48]' and
         compiled[186].mnemonic=='fld' and
         compiled[186].op_str=='dword ptr [ecx + 0x48]' and
         compiled[187].mnemonic=='mov' and
         compiled[187].op_str.startswith('edx, dword ptr [ebp - '),
         'non-equivalent original/compiled operations at read-read swap')
    # The swapped two are identical in original and candidate, apart
    # from order: no other opcode/operand/GPR/CFG differences are allowed.
    second[186],second[187]=second[187],second[186]
    need(first==second,'unexpected original native control/operand difference after read-read swap')
    return diffs


def main():
    m=module('f573_reader',ROOT/'scripts/compare-coff-function.py')
    act=module('f573_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    sw=module('f573_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    f572=module('f573_firstten',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    target=m.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    manifest=json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())
    boss=next(b for b in manifest['bosses'] if b['address']==ADDRESS)
    need(boss['size']==33293 and boss['postret_size']==438,
         'whole original giant CODE or real after-RET physical DATA size changed')
    report,mapped=act.report_boss(m,target,decoder,boss)
    original_byaction={r['action']:int(r['handler'],16) for r in mapped}
    table=boss['tables'][0]
    need(table['slots']==60 and table['map_length']==198 and table['map_addr'] is not None,
         'original first native CharacterObject switch shape differs')
    dense_bytes=m.pe_bytes_at(target,table['dense_addr'],4*table['slots'])
    sparse=m.pe_bytes_at(target,table['map_addr'],table['map_length'])
    need(hashlib.sha256(dense_bytes).hexdigest()==table['dense_sha'] and
         hashlib.sha256(sparse).hexdigest()==table['map_sha'],
         'native pinned Japanese dense/sparse source hashes invalid')
    obj=candidate_object()
    code,relocs=m.object_function(obj,'?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ')
    body=[]
    for x in decoder.disasm(code,0):
        body.append(x)
        if x.mnemonic=='ret':break
    need(body and body[-1].mnemonic=='ret','normal C++ switch lacks final RET')
    ret=body[-1].address+body[-1].size
    need(len(code)-ret==438,'candidate physical original after-RET DATA extent differs')
    refs=sorted((r for r in relocs if ret<=r['offset']<ret+4*table['slots']),
                key=lambda r:r['offset'])
    need(len(refs)==table['slots'] and all(r['offset']==ret+4*k and
         r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
         for k,r in enumerate(refs)),
         'candidate native switch physical DWORD source COFF fields absent')
    original_dense=[int.from_bytes(dense_bytes[k*4:k*4+4],'little')
                    for k in range(table['slots'])]
    candidate_dense=[r['local_symbol_offset'] for r in refs]
    need(sw.canonical_partitions(original_dense)==sw.canonical_partitions(candidate_dense),
         'candidate original compressed native handler partition differs')
    need(code[ret+4*table['slots']:]==sparse,
         'native compressed switch index bytes not literal original DATA')
    ja=[int(x.op_str,16) for x in body if x.mnemonic=='ja' and
        x.op_str.startswith('0x')]
    need(len(ja)>=1 and
         [x==int(report['default'],16) for x in original_dense]==
         [x==ja[0] for x in candidate_dense],
         'original shared default case target partitions differ')
    results=[];relocation_count=0
    for action in range(FIRST,LAST+1):
        native_start=original_byaction[action]
        native_end=original_byaction[action+1]
        need(boss['address']<=native_start<native_end<boss['address']+boss['size'],
             'native action handler range escapes full original boss')
        native=list(decoder.disasm(m.pe_bytes_at(target,native_start,native_end-native_start),native_start))
        a,b=(candidate_dense[sparse[action-FIRST]],candidate_dense[sparse[action+1-FIRST]])
        need(0<=a<b<ret,'compiled physical source action exceeds switch CODE')
        generated=list(decoder.disasm(code[a:b],a))
        need(native and generated and native[0].address==native_start and
             native[-1].address+native[-1].size==native_end and
             generated[0].address==a and generated[-1].address+generated[-1].size==b,
             'candidate/original case has noncontiguous or truncated native CODE')
        if action<=0x329:
            fields=f572.compare_actual_case(native,generated,relocs,action)
            reordered=[]
        else:
            need(len(native)==len(generated)==248 and native_end-native_start==b-a==932,
                 'original action32A complete 248-insn x87 source geometry changed')
            fields=actual_case32a_fields(native,generated,relocs)
            reordered=equivalent_independent_reads(native,generated,f572)
        relocation_count+=len(fields)
        row={'action':f'0x{action:X}', 'original_x86_instructions':len(native),
             'native_original_CODE_bytes':native_end-native_start,
             'genuine_original_COFF_fields':len(fields),
             'independent_read_only_instruction_swaps':reordered}
        results.append(row)
        print(f'{action:#05x}: original {len(native)}/{len(generated)} x86 instructions, '
              f'{native_end-native_start} original CODE bytes, {len(fields)} real typed '
              f'COFF refs, read-only order differences {reordered}',flush=True)
    need(len(results)==11 and relocation_count==80 and
         sum(r['original_x86_instructions'] for r in results)==1082 and
         sum(r['native_original_CODE_bytes'] for r in results)==4019,
         'original ten older and one new case acceptance bounds changed')
    OUT.mkdir(parents=True,exist_ok=True)
    result={'boss':f'0x{ADDRESS:08X}','unaccepted_whole_original_CODE':boss['size'],
            'physically_full_real_action_cases':results,
            'all_original_x86_instructions':1082,
            'original_internal_CODE_bytes':4019,
            'authentic_typed_case_COFF_fields':80,
            'strict_case_native_order_count':10,
            'semantically_equivalent_read_only_swaps_case32a':2,
            'physical_switch_DWORD_COFF_fields':len(refs),
            'literal_original_sparse_index_bytes':len(sparse),
            'original_afterret_DATA_shape':len(code)-ret}
    (OUT/'summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print(f'F573 whole 004EBDA0 original: 11 authentic action bodies, 1082 native '
          f'instruction roles, 4019 native internal CODE bytes, {relocation_count}/80 '
          f'true COFF call/global fields, 60 zero-addend jump DWORD fields, '
          f'198 byte-identical sparse bytes; one documented read-only pair '
          f'commutes in action32A; original 33293-byte giant still NONEXACT')
    print('Only one affected natural VC7.1 C++ TU rebuilt; NO credited '
          'whole giant or independent split CODE/DATA, no all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('TH075 original CharacterObject action32A source verification failed:',e,file=sys.stderr)
        raise SystemExit(1)
