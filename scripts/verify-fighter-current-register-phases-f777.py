#!/usr/bin/env python3
"""F777: independently remeasure latest whole 00543210 case58/59/60/61/63.

Never import a historical 'strict' classification into current whole-parent
compiler context. Cold compile exactly ONE affected 58KB original-shaped TU;
compare entire native PE action extents and actual typed PE/COFF destinations.
This is negative research, not newly exact callable game CODE.
"""
from __future__ import annotations
import importlib.util
import json
from pathlib import Path
import re
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f777-fighter-register-audit'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
ORIGINAL={
  0x58:(0x00544F34,0x00545109,469,135,17,0),
  0x59:(0x00545109,0x0054526D,356,95,16,19),
  0x60:(0x0054559F,0x005457BC,541,154,10,98),
  0x61:(0x005457BC,0x005459E5,553,158,10,101),
  0x63:(0x00545ADE,0x00545DA0,706,189,15,None),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(tag,path):
    spec=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing pinned original parser '+path)
    m=importlib.util.module_from_spec(spec)
    sys.modules[tag]=m
    spec.loader.exec_module(m)
    return m


def native_reloc_dest(raw,funcaddr,off,kind):
    value=int.from_bytes(raw[off:off+4],'little')
    if kind=='DIR32':return value
    need(kind=='REL32','unexpected PE relative field kind '+kind)
    return funcaddr+off+4+(value if value<2**31 else value-2**32)


def physical_whole_case(reader,pe,d,code,refs,inst,mapping,case,layout):
    lo,hi,size,nx,nref,expected_bad=layout
    need(lo in mapping and hi in mapping and hi-lo==size,
         f'{case:02x}: native actual complete action boundaries missing')
    source_start,source_end=mapping[lo],mapping[hi]
    original=reader.pe_bytes_at(pe,lo,size)
    n=list(d.disasm(original,lo))
    s=[x for x in inst if source_start<=x.address<source_end]
    need(len(n)==len(s)==nx,f'{case:02x}: physical original x86 count differs')
    bad_op=[j for j,(a,b) in enumerate(zip(n,s)) if a.mnemonic!=b.mnemonic]
    widths=[j for j,(a,b) in enumerate(zip(n,s)) if a.size!=b.size]
    need(not bad_op,f'{case:02x}: other source opcode-mnemonic errors: {bad_op[:12]}')
    if case==0x63:
        need(source_end-source_start==705 and widths==[18,61,84],
             'current 063 wrong CMP operand-width ordinals or source total unexpectedly changed')
        expected_cmp=[('edx','eax'),('eax','ecx'),('edx','eax')]
        cmp_roles=[]
        for j,(native_reg,source_reg) in zip(widths,expected_cmp):
            need(n[j].mnemonic==s[j].mnemonic=='cmp'
                 and n[j].op_str==f'{native_reg}, 0x96'
                 and s[j].op_str==f'{source_reg}, 0x96',
                 f'original 063 physical CMP x86 operand role mismatch at ordinal {j}')
            cmp_roles.append({'native_x86_ordinal':j,'original_operand':n[j].op_str,
                              'new_Cpp_operand':s[j].op_str,
                              'original_instruction_bytes':n[j].size,
                              'new_instruction_bytes':s[j].size})
    else:
        need(source_end-source_start==size and not widths,
             f'{case:02x}: true native instruction widths no longer line up: {widths[:8]}')
        cmp_roles=[]
    fields=[x for x in refs if source_start<=x['offset']<source_end]
    need(len(fields)==nref and all(x['addend']==0 and x['local_symbol_offset'] is None
                                  and x['type'] in ('DIR32','REL32') for x in fields),
         f'{case:02x}: original typed physical field count/zero addend changed')
    native_mask=set()
    for ref in fields:
        owner=next((j for j,x in enumerate(s)
                    if x.address<=ref['offset']<x.address+x.size),None)
        need(owner is not None,f'{case:02x}: COFF reference has no real native instruction owner')
        delta=ref['offset']-s[owner].address
        origfield=n[owner].address-lo+delta
        need(0<=origfield<=size-4,
             f'{case:02x}: mapped original physical relocation field outside action')
        need(all(z not in native_mask for z in range(origfield,origfield+4)),
             f'{case:02x}: overlapping mapped original PE/COFF fields')
        native_mask.update(range(origfield,origfield+4))
        # COFF rel32 must originate from the real game or CRT CALL at the
        # identical original instruction ordinal; DIR32 must originate in
        # the original mem/global absolute field. Neither is inferred from
        # a decompiler-displayed internal case label.
        if ref['type']=='REL32':
            need(n[owner].mnemonic=='call' and s[owner].mnemonic=='call',
                 f'{case:02x}: REL32 not the genuine native game call')
        target=native_reloc_dest(original,lo,origfield,ref['type'])
        m=re.search(r'At([0-9A-Fa-f]{6,8})(?=[^0-9a-fA-F]|$)',ref['symbol'])
        expected=(int(m.group(1),16) if m else
                  0x006406AC if ref['symbol']=='__ftol2' else None)
        need(expected is not None and target==expected,
             f'{case:02x}: original PE target {target:#x} contradicts {ref["symbol"]}')
    tail_mask=set()
    external_jumps=0
    valid_source={x.address for x in inst}
    for i,(a,b) in enumerate(zip(n,s)):
        if a.mnemonic=='jmp' and a.op_str=='0x5515c2':
            need(a.size==b.size==5 and b.mnemonic=='jmp'
                 and int(b.op_str,16) in valid_source,
                 f'{case:02x}: authentic native external giant-tail jump missing')
            tail_mask.update(range(a.address-lo+1,a.address-lo+5))
            external_jumps+=1
    wrong_bytes=None
    if case!=0x63:
        bad=[j for j in range(size)
             if j not in native_mask and j not in tail_mask
             and original[j]!=code[source_start+j]]
        wrong_bytes=len(bad)
        need(wrong_bytes==expected_bad,
             f'{case:02x}: physical nonfield operand difference changed '
             f'{wrong_bytes}, historical whole-parent evidence may be stale')
    return {'case':f'0x{case:X}',
            'actual_original_native_extent':f'{lo:08X}..{hi:08X}',
            'native_original_CODE_B':size,
            'actual_source_parent_case_CODE_B':source_end-source_start,
            'original_and_generated_x86_mnemonic_positions':nx,
            'native_zero_addend_typed_PE_COFF_fields_checked':nref,
            'actual_original_nonfield_operand_byte_mismatches':wrong_bytes,
            'genuine_shared_parent_JMPs_excluded_only_for_diagnosis':external_jumps,
            'nonmatching_actual_CMP_register_widths':cmp_roles,
            'entire_parent_byte_exact':False}


def main():
    f771=load('f777_current_f771','scripts/verify-fighter-grounded-volley-typed-f771.py')
    mf=load('f777_mapper','scripts/verify-fighter-eight-round-f734.py')
    rd=load('f777_reader','scripts/compare-coff-function.py')
    # This compiles only the ONE complete affected original-shaped parent,
    # and independently checks the previous strict cases and full 943-B
    # after-RET DATA. It does NOT replay any of 977 accepted exact units.
    f771.main()
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==0x00543210)
    obj=ROOT/'.analysis/f771-fighter-grounded-volley-whole/Boss00543210-F771-whole.obj'
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and boss['postret_size']==943
         and ret==58261 and len(code)==ret+943,
         'latest giant CODE/after-RET extent does not match independently pinned original')
    mapping=mf.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    results=[physical_whole_case(rd,pe,d,code,refs,ins,mapping,c,layout)
             for c,layout in ORIGINAL.items()]
    need(sum(q['native_zero_addend_typed_PE_COFF_fields_checked'] for q in results)==68,
         'full five case original physical relocation inventory changed')
    OUT.mkdir(parents=True,exist_ok=True)
    report={'native_original_entire_fighter':'0x00543210',
            'original_entire_callable_CODE_B':58294,
            'current_generated_full_parent_CODE_B':ret,
            'original_separate_afterRET_DATA_B':boss['postret_size'],
            'original_native_5_action_physical_cases':results,
            'stale_historical_0x63_strictness_must_NOT_be_reused':True,
            'official_whole_game_function_exact':False,
            'new_FORMAL_callable_game_CODE_credit':0,
            'all_977_existing_units_cold_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F777 full original 00543210: 58 469B strict; 59 19 wrong bytes; '
          '60 98; 61 101; 63 original 706B vs source 705B, '
          'native CMP register widths [18,61,84] wrong',flush=True)
    print('F777 68 true original PE-targeted COFF fields across five game states; '
          'native 943B afterRET DATA independently verified; '
          'NO new game CODE credit or full exact-unit replay',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError) as e:
        print('F777 original giant current-register audit FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
