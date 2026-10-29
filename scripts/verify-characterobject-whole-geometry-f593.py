#!/usr/bin/env python3
"""F593: 8,789-insn entire original CharacterObject CODE+DATA geometry.

Read Japanese TH075 v1.11 original PE (33,293 whole giant CODE bytes +
438 after-RET native switch DATA). Fresh compile ONLY the affected ordinary
VC7.1 C++ TU, with genuine gameplay source in all original cases and
native GetStateAt40FA30 default exit; revalidate the prior 54 strict
complete cases. The whole source has EXACT native CODE length, 8,789
native x86 instruction positions/widths and 682 true typed PE-targeted
zero-addend COFF fields. The original F593 source has 155/31,003
nonfield differences (3 read-read swaps plus case38D/38E/3E3 GPR).
F596 natural original leftvalue expressions make all three pairs byte
identical, leaving ONLY 137/31,003 nonfield bytes different in the
three remaining actual original GPR allocation cases.

New original complete case3E4 (261/1,126,19 true physical fields) and
case3E5 (96/396,5 fields) are strict; case3E3 is original-sized and has
17 physically typed fields but its first 31 source GPR assignments
are not byte-exact. No whole/split authored CODE or DATA exact credit.
DO NOT run a full all-unit cold replay or imply Oracle acceptance.
"""
from __future__ import annotations

from collections import Counter, defaultdict
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
ADDR=0x004EBDA0
CODE_BYTES=33293
DATA_BYTES=438
ORIGINAL_TOTAL=CODE_BYTES+DATA_BYTES
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
BASE=ROOT/'.analysis/f591-characterobject-stage-fades-source'
OBJ=BASE/'one-normal-Cpp-source.obj'
OUT=ROOT/'.analysis/f593-characterobject-whole-source'
SYMBOL='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
# Correct original PE-bounded actions, including the physically last case
# whose two short JMPs end before the original shared default handler.
CASES={
  0x38D:(0x38E,155,570,10),
  0x38E:(0x3E3,87,348,6),
  0x3E3:(0x3E4,200,812,17),
  0x3E4:(0x3E5,261,1126,19),
  0x3E5:(None,96,396,5),
}
GPR_NONEXACT={0x38D:45,0x38E:64,0x3E3:24}
READ_READ_SWAPS=((1062,1063),(1350,1351),(2521,2522))


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,path)
    need(sp is not None and sp.loader is not None,
         f'missing original PE/C++ verifier {path}')
    obj=importlib.util.module_from_spec(sp)
    sys.modules[tag]=obj
    sp.loader.exec_module(obj)
    return obj


def original_target(reader,pe,off,typ):
    need(0<=off and off+4<=ORIGINAL_TOTAL and typ in ('REL32','DIR32'),
         'relocation offset/kind outside entire original PE full CODE+DATA')
    raw=reader.pe_bytes_at(pe,ADDR+off,4)
    return (ADDR+off+4+int.from_bytes(raw,'little',signed=True)
            if typ=='REL32' else int.from_bytes(raw,'little'))


def physical_all_COFF(reader,pe,code,refs,ret,sw,index):
    fields=[r for r in refs if 0<=r['offset']<ORIGINAL_TOTAL]
    need(len(fields)==682 and len([r for r in fields if r['offset']<ret])==622,
         'entire original game function has expected 622 code + 60 data physical COFF fields')
    need(Counter(r['type'] for r in fields)=={'REL32':432,'DIR32':250},
         'genuine original full CODE and original dense jump DATA relocation types changed')
    need(all(r['addend']==0 for r in fields),
         'original native whole CODE/DATA has nonzero COFF relocation addend')
    observed=defaultdict(set)
    for r in fields:
        off=r['offset']
        native=original_target(reader,pe,off,r['type'])
        sym=r['symbol']
        observed[sym].add(native)
        if sym.startswith('$L'):
            need(r['local_symbol_offset'] is not None and
                 native==ADDR+r['local_symbol_offset'] and r['type']=='DIR32',
                 f'original compressed native local jump label PE identity differs at offset {off:#x}: {r}')
        else:
            match=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',sym)
            known=0x006406AC if sym=='__ftol2' else int(match.group(1),16) if match else None
            need(known is not None and native==known,
                 f'original physical COFF target identity (not borrowed symbol) incorrect: {sym} at {off:#x} native target {native:#x}')
    need(len(observed)==132 and all(len(dest)==1 for dest in observed.values()),
         'multiple real PE targets bound to same C++ original function symbol')
    dense=sorted([r for r in fields if ret<=r['offset']<ret+240],key=lambda x:x['offset'])
    need(len(dense)==60 and all(r['type']=='DIR32' and
         r['offset']==ret+4*i and r['local_symbol_offset'] is not None
         for i,r in enumerate(dense)),
         'original entire 60 physical compressed native action pointers changed')
    nslots=[int.from_bytes(sw[i*4:i*4+4],'little') for i in range(60)]
    cslots=[r['local_symbol_offset'] for r in dense]
    need(all(int.from_bytes(sw[i*4:i*4+4],'little')==ADDR+r['local_symbol_offset']
             for i,r in enumerate(dense)),
         'source original physical dense handler PE addresses are not byte-offset identical')
    need(code[ret+240:]==index,'198 genuine original sparse index bytes not byte-identical')
    return fields,cslots


def whole_native_byte_geometry(reader,pe,decoder,code,refs):
    original=reader.pe_bytes_at(pe,ADDR,CODE_BYTES)
    n=list(decoder.disasm(original,ADDR))
    c=[]
    for inst in decoder.disasm(code,0):
        c.append(inst)
        if inst.mnemonic=='ret':break
    ret=c[-1].address+c[-1].size
    need(len(n)==len(c)==8789 and ret==CODE_BYTES and
         len(code)==ORIGINAL_TOTAL and all(x.address-ADDR==y.address and
         x.size==y.size for x,y in zip(n,c)),
         'entire original/C++ 8789 instructions, every native CODE offset and size not identical')
    differing_mnemonics=[i for i,(x,y) in enumerate(zip(n,c))
                         if x.mnemonic!=y.mnemonic]
    historical=[i for pair in READ_READ_SWAPS for i in pair]
    need(differing_mnemonics in ([],historical),
         f'original giant x86 source differs by unproved opcode reorderings beyond the three physical native pairs: {differing_mnemonics[:22]}')
    for i,j in READ_READ_SWAPS:
        a,b=n[i],n[j];x,y=c[i],c[j]
        need(a.mnemonic=='mov' and b.mnemonic=='fld' and
             a.size==b.size==x.size==y.size==3,
             'original Japanese physical collision native MOV/FLD pair opcode widths changed')
        if differing_mnemonics:
            need(x.mnemonic=='fld' and y.mnemonic=='mov',
                 'historical F593 source read-read instruction pair no longer PE-attested')
        else:
            need(a.mnemonic==x.mnemonic and b.mnemonic==y.mnemonic
                 and a.bytes==x.bytes and b.bytes==y.bytes,
                 'F596 strict native collision preload before FLD is not exact machine bytes')
    masked=set()
    for r in refs:
        if 0<=r['offset']<CODE_BYTES:
            masked.update(range(r['offset'],r['offset']+4))
    changed={}
    for ordinal,(a,b) in enumerate(zip(n,c)):
        off=a.address-ADDR
        differences=[j for j in range(a.size) if off+j not in masked
                     and original[off+j]!=code[off+j]]
        if differences:changed[ordinal]=differences
    nonfield=sum(len(a) for a in changed.values())
    old_mode=bool(differing_mnemonics)
    expected_changed=139 if old_mode else 133
    expected_diff=155 if old_mode else 137
    expected_same=30650 if old_mode else 30668
    need(len(masked)==2488 and len(changed)==expected_changed and nonfield==expected_diff
         and CODE_BYTES-len(masked)-nonfield==expected_same,
         f'whole original native 33K code comparison has unexpected nonfield residuals: '
         f'{len(changed)} instr, {nonfield} bytes (old=155 / F596=137)')
    return n,c,ret,changed,differing_mnemonics


def case_grammar(reader,pe,decoder,gram,orig_ins,compiled_ins,
                 boss,table,cslots,index,refs):
    selected={}
    for case,(nextcase,count,size,fields) in CASES.items():
        start=table[case]
        end=table[nextcase] if nextcase is not None else ADDR+CODE_BYTES-12
        need(ADDR<=start<end<=ADDR+CODE_BYTES,
             f'original case {case:#x} real PE CODE boundary outside entire giant')
        n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
        begin=cslots[index[case-0x320]]
        cend=cslots[index[nextcase-0x320]] if nextcase is not None else begin+size
        need(0<=begin<cend<CODE_BYTES,
             f'normal source complete game case {case:#x} CODE interval wrongly intersects jump DATA')
        # The full candidate instructions have already been attested to
        # share every original instruction address offset. Therefore
        # original-CODE-aligned candidate offsets below are exact.
        obj=[x for x in compiled_ins if begin<=x.address<cend]
        need(len(n)==len(obj)==count and end-start==cend-begin==size
             and sum(x.size for x in n)==sum(y.size for y in obj)==size,
             f'complete native original case {case:#x} source opcode counts/whole bytes differ')
        native_roles=gram.authentic_grammar(n,case)
        compiled_roles=gram.authentic_grammar(obj,case)
        differences=[i for i,(a,b) in enumerate(zip(native_roles,compiled_roles)) if a!=b]
        if case in GPR_NONEXACT:
            need(len(differences)==GPR_NONEXACT[case],
                 f'original source {case:#x} register mismatch is not a bounded independently measured nonexact case: {differences[:15]}')
            if case==0x3E3:
                need(differences==[0,1,2,3,4,6,7,8,*range(15,31)],
                     'native 3E3 REAL GPR allocation differs outside its known first 31 instructions')
        else:
            need(not differences,
                 f'new last original case {case:#x} should be strict whole PE register/x87/CFG source: {differences[:15]}')
        concrete=[r for r in refs if begin<=r['offset']<cend]
        original_fields=[(i,x) for i,x in enumerate(n) if
                         (x.mnemonic=='call' and x.op_str.startswith('0x')) or 'ptr [0x' in x.op_str]
        need(len(concrete)==len(original_fields)==fields,
             f'actual native PE/candidate case {case:#x} physically typed COFF count differs')
        for i,x in original_fields:
            y=obj[i]
            found=[r for r in concrete if y.address<=r['offset']<y.address+y.size]
            need(len(found)==1 and found[0]['addend']==0 and
                 y.mnemonic==x.mnemonic,
                 f'original game source {case:#x} native COFF ordinal {i} moved/altered')
        selected[case]={'original_x86_instruction_roles':count,
                         'original_inner_CODE_bytes':size,
                         'typed_original_PE_COFF_fields':fields,
                         'source_register_mismatch_count':len(differences)}
        print(f'{case:#05x}: entire native original {count}/{count} x86 roles, '
              f'{size}/{size} CODE bytes, {fields}/{fields} PE-typed '
              f'physical source COFF fields, residual GPR differences {len(differences)}',flush=True)
    need(selected[0x3E4]['source_register_mismatch_count']==0
         and selected[0x3E5]['source_register_mismatch_count']==0,
         'original last two whole native game actions are no longer strict')
    return selected


def main():
    reader=load('f593_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f593_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    grammar=load('f593_grammar',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    prior=load('f593_prior',ROOT/'scripts/verify-characterobject-five-complex-actions-f592.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need(boss['size']==CODE_BYTES and boss['postret_size']==DATA_BYTES
         and boss['jump_count']==1,
         'actual pinned original Japanese complete CODE/after-RET DATA layout changed')
    tab=boss['tables'][0]
    need(tab['slots']==60 and tab['map_length']==198,
         'true original native compressed switch physical tables changed')
    src=SOURCE.read_text()
    need('F592/F593' in src and all(src.count(f'case 0x{k:X}:')==1 for k in CASES)
         and src.count('default: GetStateAt40FA30();')==1
         and 'case 0x3E5: g_FighterProbeMarker' not in src,
         'new whole fighter must use actual 3E3/3E4/3E5 C++ source and true 0040FA30 default')
    # Exactly ONE affected ordinary VC7.1 source TU, freshly built by
    # already independent original PE-backed F592 checker, also covering
    # all previous 54 exact-instruction-grammar whole source cases.
    prior.main()
    old=json.loads((ROOT/'.analysis/f592-characterobject-five-complex-source/summary.json').read_text())
    need(old['total_verified_original_native_game_action_bodies']==54
         and old['total_original_native_x86_instruction_roles']==7943
         and old['total_original_inner_CODE_bytes_uncredited']==29852
         and old['total_native_PE_typed_COFF_call_global_fields']==562,
         'previous 54 complete native case PE and typed COFF proof changed')
    need(OBJ.exists(),'missing newly compiled selected VC7.1 whole fighter source object')
    code,refs=reader.object_function(OBJ,SYMBOL)
    n,c,ret,byte_diff,mnemonic_differences=whole_native_byte_geometry(reader,pe,decoder,code,refs)
    dense=reader.pe_bytes_at(pe,tab['dense_addr'],tab['slots']*4)
    idx=reader.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
    need(hashlib.sha256(dense).hexdigest()==tab['dense_sha']
         and hashlib.sha256(idx).hexdigest()==tab['map_sha'],
         'pinned Japanese physical dense/sparse switch hashes mismatch')
    original_whole=reader.pe_bytes_at(pe,ADDR,ORIGINAL_TOTAL)
    need(len(original_whole)==ORIGINAL_TOTAL and
         original_whole[CODE_BYTES+240:]==idx,
         'complete original native original afterRET handler/sparse DATA mismatches')
    fields,cslots=physical_all_COFF(reader,pe,code,refs,ret,dense,idx)
    original_report,rows=actions.report_boss(reader,pe,decoder,boss)
    byaction={r['action']:int(r['handler'],16) for r in rows}
    source_cases=case_grammar(reader,pe,decoder,grammar,n,c,boss,byaction,cslots,idx,refs)
    need(source_cases[0x3E4]['original_x86_instruction_roles']==261
         and source_cases[0x3E5]['original_x86_instruction_roles']==96
         and source_cases[0x3E4]['typed_original_PE_COFF_fields']==19
         and source_cases[0x3E5]['typed_original_PE_COFF_fields']==5,
         'two new strictly original last true gameplay case source geometries differ')
    # Cross-check with the independently maintained whole-original
    # relocation-aware COFF matcher. Use *entire* 33,293 CODE + 438
    # afterRET DATA size, rather than falsely passing 33,293 to an object
    # whose real COFF section includes independent postRET DATA.
    result=subprocess.run([sys.executable,str(ROOT/'scripts/compare-coff-function.py'),
                           str(OBJ),SYMBOL,hex(ADDR),str(ORIGINAL_TOTAL),'--json'],
                          cwd=ROOT,text=True,capture_output=True,timeout=120)
    need(result.stdout.strip() and result.returncode in (0,1),
         f'original entire 33,731-byte CODE+DATA linker-aware compare failed: {result.stderr}')
    full=json.loads(result.stdout)
    expected_nonfield_same=30848 if mnemonic_differences else 30866
    need(full['result']=='mismatch' and full['size']==ORIGINAL_TOTAL
         and full['matched_comparable_bytes']==expected_nonfield_same
         and full['comparable_bytes']==31003
         and len(full['relocations'])==682,
         f'whole original PE CODE+DATA 30,848 historical or 30,866 F596 nonfield byte match changed: {full["matched_comparable_bytes"]}/31,003')
    need(all(int(r['object_addend'],16)==0 for r in full['relocations']),
         'whole original PE relocation field has nonzero source addend')
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'whole-original-comparison.json').write_text(result.stdout)
    shutil.copyfile(OBJ,OUT/'one-real-normal-VC71-source.obj')
    if (BASE/'compiler.log').exists():shutil.copyfile(BASE/'compiler.log',OUT/'compiler.log')
    summary={
      'whole_original_giant':'0x004EBDA0',
      'entire_original_CODE_bytes_nonexact':CODE_BYTES,
      'literal_original_afterret_DATA_bytes':DATA_BYTES,
      'native_whole_original_x86_instructions':8789,
      'source_whole_x86_instructions':8789,
      'native_whole_instruction_offsets_and_sizes_equal':True,
      'source_whole_instruction_mnemonics_same_position':8789-len(mnemonic_differences),
      'true_PE_COFF_CODE_fields':622,
      'true_PE_COFF_afterret_DATA_fields':60,
      'true_zero_addend_PE_COFF_total_fields':682,
      'whole_CODE_and_DATA_nonrelocation_comparable_bytes':31003,
      'whole_CODE_and_DATA_nonrelocation_identical_bytes':expected_nonfield_same,
      'whole_nonrelocation_differing_bytes':31003-expected_nonfield_same,
      'different_nonrelocation_original_instruction_entries':len(byte_diff),
      'native_original_three_sensitive_MOV_FLD_pairs':list(READ_READ_SWAPS),
      'remaining_swapped_Cpp_MOV_FLD_pair_indices':list(READ_READ_SWAPS) if mnemonic_differences else [],
      'new_strict_source_cases':{f'0x{k:X}':source_cases[k] for k in (0x3E4,0x3E5)},
      'nonexact_game_source_hypotheses':{f'0x{k:X}':source_cases[k] for k in (0x38D,0x38E,0x3E3)},
      'total_strict_original_game_action_bodies':56,
      'total_strict_original_game_action_x86_roles':8300,
      'total_strict_original_internal_CODE_bytes_uncredited':31374,
      'total_strict_original_physical_COFF_call_global_refs':586,
      'whole_function_byte_exact':False,
      'source_original_afterret_sparse_index_bytes_equal':198,
      'accepted_new_exact_whole_functions':0,
      'all_unit_cold_replay_run':False}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F593: WHOLE original 33,293 native CODE bytes, 8,789/8,789 x86 '
          'instructions, all individual offsets and byte widths identical; '
          '622 CODE + 60 afterRET true typed PE-targeted COFF fields',flush=True)
    print(f'F593/F596: source {expected_nonfield_same:,}/31,003 original nonrelocation CODE+DATA bytes identical; '
          f'{31_003-expected_nonfield_same} bytes/{len(byte_diff)} original instructions STILL DIFFER; '
          f'{len(mnemonic_differences)} residual opcode-order differences (F596 now ZERO)',flush=True)
    print('F593: 56 strict native original game source bodies, 8,300 original '
          'x86 case roles, 31,374 original inner CODE bytes, 586 true typed '
          'case COFF fields; 3 original cases 38D/38E/3E3 remain GPR nonexact. '
          'DO NOT count whole giant as exact.',flush=True)
    print('Only ONE affected normal VC7.1 source TU; no 943 exact ledger changes, '
          'no full all-unit cold replay or Oracle receipt.',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 F593 original whole giant PE/COFF source geometry proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
