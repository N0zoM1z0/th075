#!/usr/bin/env python3
"""F781: recover the true four-entry native shared getter in 00543210 boss.

One complete /Od VC7.1 parent, no all-unit cold replay. Check four
original explicit jumps, their generated shared call target, 46B native
suffix, genuine relocation targets, original 943B after-RET jump data,
and retained large early-case native physical comparisons. Whole boss
is still NOT byte exact; original 0x63 has 1B register-width deficit.
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
OUT=ROOT/'.analysis/f781-fighter-tail'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
NATIVE_BEGIN=0x00543210
NATIVE_SUFFIX=0x00551598
NATIVE_GETTER=0x005515BA
NATIVE_EPILOGUE=0x005515C2
NATIVE_EARLY_XREFS=(0x00543462,0x005435EA,0x005436CD,0x005436DC)


def need(ok,why):
    if not ok: raise ValueError(why)


def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing source '+str(path))
    module=importlib.util.module_from_spec(sp)
    sys.modules[tag]=module
    sp.loader.exec_module(module)
    return module


def source_for_whole_parent(f778,f759,f762):
    source,boss=f778.source_for_one_full_parent(f759,f762)
    # Only original 0/2 and 4/5 terminate at native 005515BA. Four
    # PE JMPs are independently verified below; other cases must keep
    # their own shared epilogue, not acquire a synthetic extra getter.
    for begin,end in [('0x0','0x1'),('0x2','0x3')]:
        pre,body=source.split('        case '+begin+':',1)
        middle,post=body.split('        case '+end+':',1)
        old='            break;\n'
        need(middle.endswith(old) and middle.count(old)==1,
             'non-unique early case full-source break '+begin)
        middle=middle.replace(old,'            goto native_shared_getter;\n')
        source=pre+'        case '+begin+':'+middle+'        case '+end+':'+post
    for begin,value in [('0x4','6.5f'),('0x5','-6.5f')]:
        old='case '+begin+': POS = '+value+'; break;'
        need(source.count(old)==1,'non-unique native early case '+begin)
        source=source.replace(old,'case '+begin+': POS = '+value+'; goto native_shared_getter;',1)
    old='#include "FighterNativeDefaultF778.inc"\n    }\n}'
    new='#include "FighterNativeDefaultF778.inc"\n    }\n#include "FighterEarlySharedGetterTailF781.inc"\n}'
    need(source.count(old)==1,'whole 58KB default/epilogue anchor missing')
    source=source.replace(old,new,1)
    need(source.count('goto native_shared_getter;')==4,
         'only four native early original action exits can own shared getter')
    return source,boss


def compile_one_parent(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F781-full.cpp'
    obj=OUT/'Boss00543210-F781-full.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=260)
    (OUT/'compiler-F781.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,
         'F781 affected whole parent failed VC7.1 compilation '+(result.stdout+result.stderr)[-1000:])
    return obj


def verify_original_shared_getter(rd,pe,d,source,refs,ins,code_end):
    original=rd.pe_bytes_at(pe,NATIVE_BEGIN,58294)
    native=list(d.disasm(original,NATIVE_BEGIN))
    need(len(native)==16471 and native[-1].address+native[-1].size==0x005515C6,
         'original complete 58,294B/16,471 x86 PE not independently decoded')
    native_early=[x for x in native if x.mnemonic=='jmp' and x.op_str==hex(NATIVE_GETTER)]
    need(tuple(x.address for x in native_early)==NATIVE_EARLY_XREFS,
         'native shared getter is NOT reached by exactly four 0/2/4/5 true code paths')
    # Getter ends 12 B before the end of CODE: an eight-byte call
    # sequence followed by the four-byte MSVC epilogue.
    generated_getter=code_end-12
    generated_xrefs=[x for x in ins if x.mnemonic=='jmp' and x.op_str==hex(generated_getter)]
    expected_source_offsets=tuple(x-NATIVE_BEGIN for x in NATIVE_EARLY_XREFS)
    need(tuple(x.address for x in generated_xrefs)==expected_source_offsets,
         'source four original branches did not converge at real shared getter')
    need(all(ins[i].size==5 for i in range(len(ins)) if ins[i].address in expected_source_offsets),
         'original four native branches must remain 5B normal jumps')
    suffix_len=0x005515C6-NATIVE_SUFFIX
    need(suffix_len==46 and code_end-suffix_len>=0,'native entire shared suffix boundary missing')
    native_tail=[x for x in native if x.address>=NATIVE_SUFFIX]
    source_tail=[x for x in ins if x.address>=code_end-suffix_len]
    need(len(native_tail)==len(source_tail)==16,
         'full original 46B suffix should contain 16 native and generated x86 instructions')
    need(all(a.mnemonic==b.mnemonic and a.size==b.size
                 and a.address-NATIVE_SUFFIX==b.address-(code_end-suffix_len)
             for a,b in zip(native_tail,source_tail)),
         'true F781 native shared suffix opcode/width geometry differs')
    fields=[r for r in refs if code_end-suffix_len<=r['offset']<code_end]
    need(len(fields)==3 and all(r['type']=='REL32' and r['addend']==0
                                 and r['local_symbol_offset'] is None for r in fields),
         'real original shared suffix three PE call relocations missing')
    targets=[]
    mask=set()
    orig_tail=rd.pe_bytes_at(pe,NATIVE_SUFFIX,suffix_len)
    for ref in fields:
        offset=ref['offset']-(code_end-suffix_len)
        for k in range(offset,offset+4):mask.add(k)
        native_disp=int.from_bytes(orig_tail[offset:offset+4],'little',signed=True)
        target=NATIVE_SUFFIX+offset+4+native_disp
        m=re.search(r'At([0-9A-Fa-f]{6,8})(?=[^0-9A-Fa-f]|$)',ref['symbol'])
        need(m is not None and int(m.group(1),16)==target,
             'F781 PE native relocation target not verified against real source symbol')
        targets.append(target)
    need(targets==[0x0040FA30,0x0040FAC0,0x0040FA30],
         'source extra getter must be original 0040FA30, not an unrelated call')
    bad=[j for j in range(suffix_len)
         if j not in mask and orig_tail[j]!=source[code_end-suffix_len+j]]
    need(bad==[10,12,16,19],
         'F781 real default still has EXACTLY four honest GPR byte negatives '+str(bad))
    return {'original_shared_getter_address':f'0x{NATIVE_GETTER:08X}',
            'original_native_entry_xrefs':[f'0x{x:08X}' for x in NATIVE_EARLY_XREFS],
            'exact_same_four_source_xref_positions':True,
            'original_46B_suffix_and_source_46B_suffix_x86':16,
            'genuine_native_shared_suffix_PE_calls':[f'0x{x:08X}' for x in targets],
            'actual_source_function_relative_getter_address':generated_getter,
            'still_wrong_default_GPR_operand_bytes':bad,
            'accepted_entire_giant':False}


def main():
    f778=load('f781_778','scripts/verify-fighter-native-default-f778.py')
    f759=load('f781_759','scripts/verify-fighter-four-directional-c8-f759.py')
    f762=load('f781_762','scripts/verify-fighter-typed-returns-f762.py')
    f734=load('f781_734','scripts/verify-fighter-eight-round-f734.py')
    f777=load('f781_777','scripts/verify-fighter-current-register-phases-f777.py')
    rd=load('f781_reader','scripts/compare-coff-function.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    source,boss=source_for_whole_parent(f778,f759,f762)
    obj=compile_one_parent(source)
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    end=ins[-1].address+ins[-1].size
    need(boss['size']==58294 and boss['postret_size']==943
         and end==58293 and len(ins)==16471 and len(code)==end+943,
         'whole F781 parent not original near-exact native geometry; still 1 real byte short')
    mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    shared=verify_original_shared_getter(rd,pe,d,code,refs,ins,end)
    five=[f777.physical_whole_case(rd,pe,d,code,refs,ins,mapping,c,f777.ORIGINAL[c])
          for c in sorted(f777.ORIGINAL)]
    after=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    report={'original_complete_fighter':'0x00543210',
            'original_whole_code_bytes':58294,
            'generated_whole_code_bytes':end,
            'one_honest_remaining_063_REGISTER_WIDTH_byte':True,
            'whole_original_and_compiled_x86_instructions':16471,
            'native_four_entry_shared_getter':shared,
            'fresh_early_large_case_physical_coverage':five,
            'complete_943B_afterRET_jump_DATA_rechecked':after,
            'full_979_unit_cold_replay_run':False,
            'formal_accepted_game_CODE_credit':0,
            'giant_whole_byte_exact':False}
    OUT.mkdir(parents=True,exist_ok=True)
    OUT.joinpath('verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F781 physical native 005515BA recovered as one 8B getter, reachable from EXACT four native action 0/2/4/5 JMPs. 46B/16 x86 original suffix reproduced in complete source.',flush=True)
    print('F781 whole original fighter 58,293/58,294 CODE B, 16,471/16,471 x86; 0x63 still 1B wrong + authentic GPR differences; 943B afterRET DATA verified. NO whole exact credit.',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F781 native PE giant proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
