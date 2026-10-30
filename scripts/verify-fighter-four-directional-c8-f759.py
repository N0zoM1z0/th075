#!/usr/bin/env python3
"""F759: four original entire C8..CB game-state interiors in one VC7.1 giant.

Use independently pinned Japanese PE, actual full source dispatch and COFF,
not a standalone fake switch-case function or masked 'exact' original CODE.
The still-unmatched 00543210 parent and its separately owned 943-B afterRET
DATA are examined together. Only THIS affected giant source TU is compiled.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f759-fighter-c8-cb-original'
SYMBOL='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
BASE=0x00543210
ORIGINAL={
  0xC8:(0x0054737F,0x0054756F,496,145,16,5,0x74),
  0xC9:(0x0054756F,0x00547717,424,127,14,3,0x78),
  0xCA:(0x00547717,0x005478CE,439,129,12,2,0x7C),
  0xCB:(0x005478CE,0x00547A8B,445,131,12,2,0x80),
}
# Match physical original x87 scratch *after* adding the four missing
# authentic native cases; no claim for remaining register/CFG differences.
DOWNSTREAM={
  0x18A:(0x005490FD,0x005491FD,62,0x88),
  0x18B:(0x005491FD,0x00549364,90,0x8C),
  0x190:(0x00549364,0x00549478,55,0x90),
  0x191:(0x00549478,0x0054958C,55,0x94),
  0x192:(0x0054958C,0x0054967C,48,0x98),
  0x194:(0x0054967C,0x005497CB,72,0x9C),
  0x195:(0x005497CB,0x0054991A,72,0xA0),
  0x2D0:(0x0054E111,0x0054E2B1,72,0x184),
  0x302:(0x0055101E,0x005513C5,77,0x208),
}


def require(ok, message):
    if not ok: raise ValueError(message)


def module(tag,relative):
    sp=importlib.util.spec_from_file_location(tag,ROOT/relative)
    require(sp is not None and sp.loader is not None,
            'missing tracked original-target C++ generator: '+relative)
    m=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=m
    sp.loader.exec_module(m)
    return m


def full_source(reader,pe,decoder,boss,report,mapped):
    """Rebuild all earlier tracked genuine parent C++ fragments, not cached OBJ."""
    f728=module('f759_f728','scripts/verify-fighter-random-arcs-f728.py')
    f729=module('f759_f729','scripts/verify-fighter-return-boundary-f729.py')
    f731=module('f759_f731','scripts/verify-fighter-aim-return-f731.py')
    f732=module('f759_f732','scripts/verify-fighter-following-native-f732.py')
    f734=module('f759_f734','scripts/verify-fighter-eight-round-f734.py')
    f737=module('f759_f737','scripts/verify-fighter-eight-ground-f737.py')
    f740=module('f759_f740','scripts/verify-fighter-repeat-shot-f740.py')
    f743=module('f759_f743','scripts/verify-fighter-later-early-f743.py')
    f744=module('f759_f744','scripts/verify-fighter-double-repeat-f744.py')
    f749=module('f759_f749','scripts/verify-fighter-early-resource-f749.py')
    f752=module('f759_f752','scripts/verify-fighter-borrowed-position-f752.py')
    src,_=f728.source_for_complete_parent(reader,pe,decoder,boss,report,mapped)
    src=f729.source_with_return_boundaries(src)
    src=f731.source_with_aim_return(src)
    src=f732.whole_source_with_following(src)
    src=f734.source_with_three(src)
    src=f737.with_194_195(src)
    src=f740.source_with_repeat_shots(src)
    src=f743.source_with_four(src)
    src=f744.source_with_19a_19b(src)
    src=f752.source_with_typed_borrowed_faces(src,f749)
    for case,index in zip(ORIGINAL,(201,202,203,204)):
        old=f'        case 0x{case:X}: g_FighterProbeMarker = {index}; break;'
        require(src.count(old)==1,f'original action 0x{case:X} placeholder missing')
        src=src.replace(old,'#include "FighterFourDirectionalC8F759.inc"' if case==0xC8 else '')
    needle='extern float g_ThresholdAt0065782C;'
    require(src.count(needle)==1,'native original fighter threshold declaration not uniquely present')
    src=src.replace(needle,needle+'\nextern float g_F759_C8DecelAt006593E8;\n'
                    'extern float g_F759_C9DecelAt00658290;')
    require(src.count('#include "FighterFourDirectionalC8F759.inc"')==1
            and 'FighterEarlyBounceTypedF752.inc' in src,
            'all original C8..CB and real 0x44 typed borrowed position source not retained')
    return src


def compile_one(src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F759-whole.cpp'
    obj=OUT/'Boss00543210-F759-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         env=env,cwd=ROOT,text=True,capture_output=True,timeout=220)
    (OUT/'F759-compiler.log').write_text(cp.stdout+cp.stderr)
    require(cp.returncode==0,'entire original giant normal VC7.1 C++ compiler error: '
            +(cp.stdout+cp.stderr)[-1500:])
    return obj


def program_instructions(decoder,code):
    inst=[]
    for x in decoder.disasm(code,0):
        inst.append(x)
        if x.mnemonic=='ret': break
    require(inst and inst[-1].mnemonic=='ret','compiled giant complete callable RET missing')
    return inst


def original_relocation_target(reader,pe,instruction,source_instruction,ref):
    delta=ref['offset']-source_instruction.address
    require(0<=delta and delta+4<=instruction.size,
            f'original x86 physical relocation is not owned by same instruction {instruction.address:#x}')
    raw=int.from_bytes(reader.pe_bytes_at(pe,instruction.address+delta,4),'little')
    return raw if ref['type']=='DIR32' else (instruction.address+delta+4
            + (raw if raw<0x80000000 else raw-0x100000000))


def check_native_cases(reader,pe,decoder,code,refs,ins,map_table,by):
    original_bytes=real_ins=real_fields=physical_bytes=shared_jump_fields=0
    source_starts={x.address for x in ins}
    records=[]
    common_source_tail=None
    for case,(start,end,expected_size,nx,nfields,njumps,slot) in ORIGINAL.items():
        require(by[case]==start and by[case+1]==end and end-start==expected_size,
                f'original game case {case:#x} physically bounded and independent')
        native=list(decoder.disasm(reader.pe_bytes_at(pe,start,expected_size),start))
        low,high=map_table[start],map_table[end]
        generated=[x for x in ins if low<=x.address<high]
        require(len(native)==len(generated)==nx and high-low==expected_size
                and all(start<=a.address and a.address+a.size<=end and a.mnemonic==b.mnemonic and a.size==b.size
                        for a,b in zip(native,generated)),
                f'original complete {case:#x} native C++ x86 mnemonic/width/extent diverges')
        # Full genuine nonrelocated operand machine bytes must match, except
        # two known kinds of original code field: source COFF relocations and
        # legitimate JMP displacement to external *parent* continuation.
        owned=[r for r in refs if low<=r['offset']<high]
        require(len(owned)==nfields and all(r['addend']==0 for r in owned),
                f'original {case:#x} genuine physical COFF field count/addend differs')
        fmask=set()
        for ref in owned:
            j=next((i for i,x in enumerate(generated)
                    if x.address<=ref['offset']<x.address+x.size),None)
            require(j is not None and ref['local_symbol_offset'] is None
                    and ref['type'] in ('REL32','DIR32'),
                    f'original {case:#x} source field not owned by original real x86')
            observed=original_relocation_target(reader,pe,native[j],generated[j],ref)
            symbol=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',ref['symbol'])
            require(symbol is not None and observed==int(symbol.group(1),16),
                    f'original {case:#x} physical PE target is not the emitted C++ COFF owner: '
                    f'{ref["symbol"]} -> {observed:#x}')
            offset=ref['offset']-low
            require(all(0<=k<expected_size and k not in fmask for k in range(offset,offset+4)),
                    'native and COFF fields overlap or leave original complete CODE')
            fmask.update(range(offset,offset+4))
        jmask=set();exits=[]
        for i,(a,b) in enumerate(zip(native,generated)):
            if a.mnemonic=='jmp' and a.op_str=='0x5515c2':
                require(a.size==b.size==5 and b.mnemonic=='jmp'
                        and int(b.op_str,16) in source_starts,
                        'original C++ full parent shared continuation not a real instruction')
                if common_source_tail is None:common_source_tail=b.op_str
                require(b.op_str==common_source_tail,
                        'four actual original actions must share only one compiled parent continuation')
                jmask.update(range(b.address-low+1,b.address-low+5))
                exits.append(i)
        require(len(exits)==njumps,
                f'original {case:#x} has wrong native shared parent JMP count')
        native_raw=reader.pe_bytes_at(pe,start,expected_size)
        source_raw=code[low:high]
        other_diff=[k for k in range(expected_size) if k not in fmask
                    and k not in jmask and native_raw[k]!=source_raw[k]]
        require(not other_diff,
                f'original {case:#x} real native nonfield bytes differ outside legitimate parent-tail '
                f'JMP and typed COFF fields at offsets: {other_diff[:30]}')
        fild=[(i,x) for i,x in enumerate(native) if x.mnemonic=='fild'
              and f'[ebp - 0x{slot:x}]' in x.op_str]
        require(len(fild)==1 and generated[fild[0][0]].bytes==fild[0][1].bytes,
                f'original {case:#x} actually used integer-to-x87 scratch EBP {slot:#x} missing')
        print(f'F759 native 0x{case:X}: {expected_size} original CODE B/{nx} authentic '
              f'x86, all {nfields} real typed PE/COFF fields, {njumps} legitimate '
              f'external parent-tail JMPs, ZERO other nonfield differences',flush=True)
        records.append({'action':f'0x{case:X}','entire_original_CODE_B':expected_size,
               'native_x86_instructions':nx,'physical_original_COFF_fields':nfields,
               'actual_original_stack_FILD':f'EBP-0x{slot:X}',
               'real_shared_tail_jump_ordinals':exits,
               'original_other_nonfield_mismatching_bytes':0,
               'original_whole_game_function_exact':False})
        original_bytes+=expected_size;real_ins+=nx;real_fields+=nfields
        physical_bytes+=expected_size-len(fmask)-len(jmask)
        shared_jump_fields+=len(exits)
    require((original_bytes,real_ins,real_fields,physical_bytes,shared_jump_fields)
            ==(1804,532,54,1540,12),
            'F759 original full four-action C++ physical evidence totals changed')
    return records,common_source_tail


def check_downstream_scratch(reader,pe,decoder,ins,mapper):
    # Verify the real regression too: restoring native FILD slots does NOT
    # imply that later eight-shot register phases are byte-exact.
    f598=module('f759_downstream_normalizer',
                'scripts/verify-fighter-singleton-contact-f598.py')
    native_register_residuals={0x190:40,0x191:40,0x192:34}
    checked=[]
    for case,(start,end,ordinal,slot) in DOWNSTREAM.items():
        original=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
        a,b=mapper[start],mapper[end]
        source=[x for x in ins if a<=x.address<b]
        require(len(source)==len(original) and ordinal<len(source)
                and original[ordinal].mnemonic==source[ordinal].mnemonic=='fild'
                and source[ordinal].op_str==original[ordinal].op_str
                and f'[ebp - 0x{slot:x}]' in original[ordinal].op_str,
                f'original downstream {case:#x} entire native context scratch slot mismatch')
        # Real integer-to-FPU input actually written to SAME original slot
        # by preceding native MOV, not a merely similar FILD text.
        require(original[ordinal-1].mnemonic==source[ordinal-1].mnemonic=='mov'
                and original[ordinal-1].op_str.startswith(f'dword ptr [ebp - 0x{slot:x}], ')
                and source[ordinal-1].op_str.startswith(f'dword ptr [ebp - 0x{slot:x}], '),
                f'original {case:#x} signed integer scratch backing store slot not recovered')
        # Only the *physical EBP role* is claimed: some later source
        # registers still differ from the native owner, and that remains
        # an honest unaccepted whole-boss mismatch.
        gpr_wrong=[i for i,(a,b) in enumerate(zip(
                   f598.normalized(original),f598.normalized(source)))
                   if a!=b and original[i].mnemonic not in ('call','jmp')]
        if case in native_register_residuals:
            require(len(gpr_wrong)==native_register_residuals[case],
                    f'current F759 source {case:#x} original GPR regression changed; '
                    're-audit native source, do not transplant F752 zero-GPR claim')
        checked.append({'native_case':f'0x{case:X}',
                        'original_and_source_EBP_FILD':f'-0x{slot:X}',
                        'native_case_CODE_B':end-start,
                        'native_x86_instructions':len(original),
                        'source_nonfield_GPR_residuals':len(gpr_wrong)})
    print('F759 downstream: all 9 original/CPP real MOV/FILD stack roles restored '
          '(18A/18B,190/191/192,194/195,2D0,302); whole 58KB NOT exact',flush=True)
    return checked


def check_afterret(reader,pe,decoder,boss,code,refs,ins):
    ret=ins[-1].address+ins[-1].size
    native=reader.pe_bytes_at(pe,BASE+boss['size'],boss['postret_size'])
    emitted=code[ret:]
    require(len(native)==len(emitted)==boss['postret_size']==943,
            'whole original and source separate afterRET DATA extent must equal 943')
    src_fields=sorted([r for r in refs if r['offset']>=ret],key=lambda x:x['offset'])
    require(len(src_fields)==156,'whole fighter seven original compressed switch tables lost')
    nstarts={x.address for x in decoder.disasm(reader.pe_bytes_at(pe,BASE,boss['size']),BASE)}
    cstarts={x.address for x in ins}
    masked=set()
    for ref in src_fields:
        off=ref['offset']-ret
        require(0<=off<=939 and ref['type']=='DIR32' and ref['addend']==0
                and ref['local_symbol_offset'] in cstarts,
                'original afterRET actual COFF field kind/addend/compiled native target changed')
        ptr=int.from_bytes(native[off:off+4],'little')
        require(ptr in nstarts and all(j not in masked for j in range(off,off+4)),
                'original native physical switch table points outside real instructions')
        masked.update(range(off,off+4))
    equal=sum(native[i]==emitted[i] for i in range(943) if i not in masked)
    require(len(masked)==624 and equal==319,
            'original physically separate afterRET DATA 319 native sparse index bytes differ')
    print('F759 complete original post-RET switch DATA: 943B, 156 genuine DIR32, '
          '319/319 native nonfield bytes equal; zero data CODE credit',flush=True)
    return {'total_bytes':943,'physical_native_and_Cpp_DIR32_fields':156,
            'native_nonfield_sparse_bytes_identical':319}


def main():
    reader=module('f759_rd','scripts/compare-coff-function.py')
    acts=module('f759_acts','scripts/report-fighter-action-handlers.py')
    f734=module('f759_f734_mapping','scripts/verify-fighter-eight-round-f734.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==BASE)
    require(boss['size']==58294 and boss['postret_size']==943,
            'whole original fighter independent pinned original native CODE or DATA changed')
    report,mapped=acts.report_boss(reader,pe,decoder,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    source=full_source(reader,pe,decoder,boss,report,mapped)
    obj=compile_one(source)
    code,refs=reader.object_function(obj,SYMBOL)
    ins=program_instructions(decoder,code)
    ret=ins[-1].address+ins[-1].size
    require(0<ret<boss['size'] and len(code)==ret+943,
            'whole original fighter remains NONEXACT: do not promote one case as full function')
    mapper=f734.source_map_from_original_afterRET(reader,pe,boss,code,ins,refs)
    cases,tail=check_native_cases(reader,pe,decoder,code,refs,ins,mapper,by)
    downstream=check_downstream_scratch(reader,pe,decoder,ins,mapper)
    data=check_afterret(reader,pe,decoder,boss,code,refs,ins)
    OUT.mkdir(parents=True,exist_ok=True)
    proof={'original_entire_game_function':'0x00543210',
           'complete_native_original_CODE_bytes':58294,
           'current_Cpp_entire_CODE_bytes':ret,
           'remaining_CODE_size_deficit_NOT_MATCHED':boss['size']-ret,
           'four_new_real_original_full_case_interiors':cases,
           'original_internal_case_CODE_B_NOT_CREDITED':1804,
           'four_original_native_x86_instructions':532,
           'original_COFF_fields_proven':54,
           'original_other_nonrelocation_CASE_bytes_equal':1540,
           'true_nonidentical_external_parent_jump_displacement_fields':12,
           'source_giant_shared_tail_target':tail,
           'downstream_real_EBP_MOV_FILD_restorations':downstream,
           'F759_actual_190_191_192_register_regressions_NOT_EXACT':
             {x['native_case']:x['source_nonfield_GPR_residuals'] for x in downstream
              if x['native_case'] in ('0x190','0x191','0x192')},
           'genuine_afterRET_DISPATCH_DATA':data,
           'new_whole_original_game_FUNCTION_exact':False,
           'new_canonical_game_function_CODE_credit':0,
           'all_existing_match_units_replayed':False}
    (OUT/'f759-verified-summary.json').write_text(json.dumps(proof,indent=2)+'\n')
    print('F759 complete 58KB boss: four real native whole-case interiors '
          '1804 CODE B/532 x86/54 typed physical fields verified in ONE '
          'whole VC7.1 C++ parent; parent itself NONEXACT and uncredited',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F759 true whole original fighter C8..CB evidence FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
