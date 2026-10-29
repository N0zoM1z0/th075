#!/usr/bin/env python3
"""F575: recover actual CharacterObject fade actions 0x32D/0x32E; recheck 13.

Fresh compile of ONE selected normal VC7.1 source including all real actions
0x320..0x331 (except default 0x32F) in 33,293-byte 004EBDA0; all later action labels are
explicit diagnostic markers. SHA-verify complete original Japanese TH075 PE
and physical 60-slot COFF jump/data before checking entire native case bodies,
real x87 operand/calls and typed COFF. Allow ONLY two proven read-only MOV/FLD source order swaps in older cases,
and true 18-byte native EBP local-frame widening in EACH newly recovered
274-insn case. No fake frame or physical exact CODE credit.
Never credit giant whole/split CODE or run all-unit cold replay.
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
OUT=ROOT/'.analysis/f576-characterobject-fire-source'
MANIFEST=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
ADDR=0x004EBDA0
START=0x320
END=0x331
TYPED={
   0x0040FBB0:('REL32','ResetStateAt40FBB0'),
   0x00453E60:('REL32','SetupAt453E60'),
   0x0045B830:('REL32','ResetAt45B830'),
   0x0040FA30:('REL32','GetStateAt40FA30'),
   0x0040FB40:('REL32','SetStateAt40FB40'),
   0x00453A70:('REL32','SpawnAt453A70'),
   0x00453D40:('REL32','ModifyAt453D40'),
   0x0040FB70:('REL32','MotionRawAt40FB70'),
   0x0040FAC0:('REL32','SetActionAt40FAC0'),
   0x0065972C:('DIR32','gCurveAt0065972C'),
   0x00658044:('DIR32','gStepAt00658044'),
   0x00657CC0:('DIR32','gLiftAt00657CC0'),
   0x0065782C:('DIR32','gCompareAt0065782C'),
   0x006583F8:('DIR32','gFadeAt006583F8'),
   0x00659428:('DIR32','gFadeAt00659428'),
   0x00659738:('DIR32','gAddAt00659738'),
   0x006583FC:('DIR32','gAddAt006583FC'),
   0x00659730:('DIR32','gMulDoubleAt00659730'),
   0x00659090:('DIR32','gSubAt00659090'),
   0x00455580:('REL32','RandomAt455580'),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         f'missing tracked original-backed source verifier {path}')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def actual_typed_fields(native,candidate,relocations,action):
    first,last=candidate[0].address,candidate[-1].address+candidate[-1].size
    physical=[r for r in relocations if first<=r['offset']<last]
    observed=[]
    for ordinal,n in enumerate(native):
        if n.mnemonic=='call' and n.op_str.startswith('0x'):
            kind='REL32';address=int(n.op_str,16)
        elif n.mnemonic.startswith('f') and 'ptr [0x' in n.op_str:
            kind='DIR32';address=int(n.op_str.split('[0x',1)[1].split(']',1)[0],16)
        else:continue
        need(address in TYPED,
             f'original {action:#x} unexpected native call/global {address:#x}, instruction {ordinal}')
        expected_kind,expected_symbol=TYPED[address]
        need(kind==expected_kind,'native original float/call field type changed')
        if (action==0x32C and address==0x00453A70 and ordinal in (138,152)) or (action in (0x330,0x331) and address==0x00453A70 and ordinal==268):
            expected_symbol='SpawnMovedAt453A70' if action in (0x330,0x331) else 'SpawnDirectedAt453A70'
        generated=candidate[ordinal]
        need(n.mnemonic==generated.mnemonic,
             f'physical original COFF instruction moved at {action:#x} ordinal {ordinal}')
        refs=[r for r in physical if generated.address<=r['offset']<generated.address+generated.size]
        need(len(refs)==1 and refs[0]['type']==kind
             and refs[0]['addend']==0 and expected_symbol in refs[0]['symbol'],
             f'C++ COFF real original call/global field mismatch at {action:#x} ordinal {ordinal}: {refs}')
        observed.append((ordinal,kind,address))
    expected={0x32B:9,0x32C:13,0x32D:6,0x32E:5,0x330:16,0x331:16}[action]
    need(len(observed)==len(physical)==expected,
         f'original {action:#x} physical source COFF field count incorrect')
    if action==0x32B:
        need([k for k,x in enumerate(native) if x.mnemonic=='fimul']==[58,77]
             and [k for k,x in enumerate(candidate) if x.mnemonic=='fimul']==[58,77],
             'native 0x32B second integer-to-float multiply/update missing')
    return observed


def native_32c_read_swap(native,candidate,f572):
    """Only permitted exception: one adjacent, independent memory READ pair.

    Native: MOV EAX,[saved_this]; FLD [EDX+0x48]
    Source: FLD [EDX+0x48]; MOV EAX,[saved_this].
    No write, branch or external relocation separates the two; neither
    reads the register written by the other. This is semantic equivalence,
    NOT physical instruction-order exactness or CODE credit.
    """
    need(len(native)==len(candidate)==176,'original x86 case32C length drift')
    a=f572.authentic_grammar(native,0x32C)
    b=f572.authentic_grammar(candidate,0x32C)
    diffs=[k for k,(x,y) in enumerate(zip(a,b)) if x!=y]
    need(diffs==[114,115],
         f'case32C previously independently bounded adjacent MOV/FLD mismatch changed: {diffs[:9]}')
    need(native[114].mnemonic=='mov'
         and native[114].op_str.startswith('eax, dword ptr [ebp - ')
         and native[115].mnemonic=='fld'
         and native[115].op_str=='dword ptr [edx + 0x48]'
         and candidate[114].mnemonic=='fld'
         and candidate[114].op_str=='dword ptr [edx + 0x48]'
         and candidate[115].mnemonic=='mov'
         and candidate[115].op_str.startswith('eax, dword ptr [ebp - '),
         'one independent actual native MOV/FLD pair is not the original')
    b[114],b[115]=b[115],b[114]
    need(a==b,'extra original x87/branch/GPR difference after independently proven read swap')
    return diffs


def validate_native_wide_frame(native,candidate,f572,action):
    """No filler: actual giant spills three int-to-x87 temporaries deep in EBP.

    Each of three MOV temp stores and three FILD temp loads uses a real
    native disp32, whereas an isolated C++ source uses a disp8 operand.
    Their 3-byte size differences are not standalone CODE exactness.
    Keep every other native opcode, GPR, control destination and original
    x87 source operand identical; typed qword COFF fields were checked.
    """
    need(action in (0x330,0x331) and len(native)==len(candidate)==274,
         'not original 274-insn fire-state body')
    differences=[(i,x,y,x.size-y.size) for i,(x,y) in enumerate(zip(native,candidate))
                 if x.size!=y.size]
    ordinals=[97,98,244,245,259,260]
    need([i for i,*_ in differences]==ordinals
         and all(delta==3 for _,_,_,delta in differences),
         f'original fire-state EBP width is not precisely 6 true 3-byte excesses: {differences[:7]}')
    for i,x,y,delta in differences:
        need(x.mnemonic==y.mnemonic==('mov' if i in (97,244,259) else 'fild'),
             f'giant spill at {i} is not original native MOV/FILD')
        need('[ebp - 0x8' in x.op_str or '[ebp - 0x9' in x.op_str,
             f'original giant EBP disp32 spill at {i} missing')
        need('[ebp - ' in y.op_str and y.size+3==x.size,
             f'natural compact source EBP frame width at {i} invalid')
    orig_normal=[(mnemonic,operands) for mnemonic,size,operands
                 in f572.authentic_grammar(native,action)]
    source_normal=[(mnemonic,operands) for mnemonic,size,operands
                   in f572.authentic_grammar(candidate,action)]
    need(orig_normal==source_normal,
         f'whole action {action:#x} original GPR/x87/CFG instructions differ beyond genuine EBP widths: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(orig_normal,source_normal)) if x!=y][:5]}')
    need(sum(x.size for x in native)==1003 and
         sum(x.size for x in candidate)==985,
         'not original 1003 vs compact VC7.1 985-byte stage source')
    return len(differences),sum(delta for *_,delta in differences)


def build_one():
    OUT.mkdir(parents=True,exist_ok=True)
    src=SOURCE.read_text()
    need('F572/F573/F574/F575' in src and
         all(src.count(f'case 0x{k:X}:')==1 for k in range(START,END+1) if k!=0x32F)
         and 'case 0x340: g_FighterProbeMarker = 833; break;' in src,
         'actual F576 source must implement 17 real game cases and keep next case diagnostic')
    need(src.count('gCurveAt0065972C')>=3 and src.count('MotionRawAt40FB70')>=2,
         'real source must include native polynomial and raw-float input')
    obj=OUT/'CharacterObjectF576.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'fresh selected native profile VC7.1 compile failed: {proc.stderr}')
    return obj


def main():
    reader=module('f576_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f576_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f576_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    f572=module('f576_firstten',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    f573=module('f575_previous',ROOT/'scripts/verify-characterobject-extended-action-f573.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads(MANIFEST.read_text())['bosses'] if x['address']==ADDR)
    need(boss['size']==33293 and boss['postret_size']==438,
         'original complete giant function CODE or post-RET DATA drift')
    report,mapped=actions.report_boss(reader,pe,decoder,boss)
    allcases={r['action']:int(r['handler'],16) for r in mapped}
    tab=boss['tables'][0]
    need(tab['slots']==60 and tab['map_length']==198 and tab['map_addr'] is not None,
         'original native one-switch compressed table geometry changed')
    original_dense=reader.pe_bytes_at(pe,tab['dense_addr'],4*tab['slots'])
    original_map=reader.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
    need(hashlib.sha256(original_dense).hexdigest()==tab['dense_sha'] and
         hashlib.sha256(original_map).hexdigest()==tab['map_sha'],
         'actual original PE switch SHA controls do not match')
    obj=build_one()
    code,refs=reader.object_function(obj,'?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ')
    allins=[]
    for x in decoder.disasm(code,0):
        allins.append(x)
        if x.mnemonic=='ret':break
    need(allins and allins[-1].mnemonic=='ret','candidate whole fighter switch no normal RET')
    ret=allins[-1].address+allins[-1].size
    need(len(code)-ret==boss['postret_size'],
         'original candidate full after-RET jump DATA size differs')
    physical=sorted((r for r in refs if ret<=r['offset']<ret+4*tab['slots']),
                    key=lambda r:r['offset'])
    need(len(physical)==tab['slots'] and all(r['type']=='DIR32'
         and r['addend']==0 and r['offset']==ret+4*k
         and r['local_symbol_offset'] is not None for k,r in enumerate(physical)),
         'one-switch physical original direct handler COFF fields incorrect')
    nslots=[int.from_bytes(original_dense[4*k:4*k+4],'little')
            for k in range(tab['slots'])]
    cslots=[r['local_symbol_offset'] for r in physical]
    need(switch.canonical_partitions(nslots)==switch.canonical_partitions(cslots),
         'actual default/repeated switch handler partitions mismatch')
    need(code[ret+4*tab['slots']:]==original_map,'original literal sparse index bytes differ')
    ja=[int(x.op_str,16) for x in allins if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(report['default'],16) for x in nslots]==[x==ja[0] for x in cslots],
         'native shared default physical jump slots differ')
    rows=[];total_coff=0;native_frame_extra=0
    cases=[k for k in range(START,END+1) if k!=0x32F]
    need(len(cases)==17 and cases[-3:]==[0x32E,0x330,0x331],
         'original 0x32F default handler must never be counted as action body')
    for action in cases:
        first=allcases[action];last=allcases[0x330] if action==0x32E else allcases[action+1]
        need(boss['address']<=first<last<boss['address']+boss['size'],
             'actual original game case outside giant source range')
        orig=list(decoder.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        cfirst=cslots[original_map[action-START]]
        clast=cslots[original_map[(0x330 if action==0x32E else action+1)-START]]
        need(0<=cfirst<clast<ret,'candidate complete case source outside normal CODE')
        cand=list(decoder.disasm(code[cfirst:clast],cfirst))
        need(orig and orig[0].address==first and orig[-1].address+orig[-1].size==last
             and cand and cand[0].address==cfirst and cand[-1].address+cand[-1].size==clast,
             f'actual whole native actor case {action:#x} is truncated/discontinuous')
        need(len(orig)==len(cand) and (
             (last-first==clast-cfirst and all(x.size==y.size for x,y in zip(orig,cand)))
             if action<0x330 else (last-first-clast+cfirst==18)),
             f'whole native actor {action:#x} instruction/codebyte grammar differs')
        if action<=0x329:
            fields=f572.compare_actual_case(orig,cand,refs,action)
            changes=[]
        elif action==0x32A:
            fields=f573.actual_case32a_fields(orig,cand,refs)
            changes=f573.equivalent_independent_reads(orig,cand,f572)
        else:
            fields=actual_typed_fields(orig,cand,refs,action)
            if action in (0x32B,0x32D,0x32E):
                a=f572.authentic_grammar(orig,action)
                b=f572.authentic_grammar(cand,action)
                need(a==b,'full native stage/curve action32B has incorrect original register/x87/CFG roles')
                changes=[]
            elif action==0x32C:
                changes=native_32c_read_swap(orig,cand,f572)
            else:
                widened,excess=validate_native_wide_frame(orig,cand,f572,action)
                need(widened==6 and excess==18,'not genuine original deep-frame source x87 slots')
                native_frame_extra+=excess
                changes=[]
        total_coff+=len(fields)
        rows.append({'action':f'0x{action:X}', 'native_x86_instructions':len(orig),
                     'native_original_CODE_bytes':last-first,
                     'genuine_physical_COFF_fields':len(fields),
                     'explicit_nonidentical_read_only_swap_indices':changes,
                     'native_deep_frame_extra_bytes':18 if action in (0x330,0x331) else 0})
        print(f'{action:#05x}: whole original {len(orig)} x86 instructions / '
              f'{last-first} CODE bytes, {len(fields)} genuine COFF fields, '
              f'independent read-only source-order exceptions {changes}',flush=True)
    need(len(rows)==17 and sum(x['native_x86_instructions'] for x in rows)==2054
         and sum(x['native_original_CODE_bytes'] for x in rows)==7593
         and total_coff==145 and native_frame_extra==36
         and [rows[-2]['native_x86_instructions'],rows[-1]['native_x86_instructions']]==[274,274]
         and [rows[-2]['native_original_CODE_bytes'],rows[-1]['native_original_CODE_bytes']]==[1003,1003],
         'original case family 17 physical complete native actions/fields differs')
    OUT.mkdir(parents=True,exist_ok=True)
    summary={'original_giant':f'0x{ADDR:08X}','whole_original_CODE_unaccepted':boss['size'],
             'native_complete_real_action_count':len(rows),
             'case_details':rows,
             'original_native_x86_insns':2054,
             'original_inner_CODE_bytes':7593,
             'genuine_typed_COFF_fields':145,
             'genuine_original_deep_frame_extra_bytes':native_frame_extra,
             'original_dense_DWORD_COFF_slots':len(physical),
             'byte_identical_sparse_index_bytes':len(original_map),
             'complete_native_afterret_DATA_shape':len(code)-ret}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(f'F576 original 0x{ADDR:08X}: 17 complete action bodies, '
          f'2054 native x86 source roles, 7593 whole original inner CODE bytes, '
          f'{total_coff}/145 genuine typed COFF records, 60 native-style jump '
          f'DWORD fields, 198 byte-identical original sparse bytes; '
          f'two previously proven read-only swaps; two new case deep-frame source excess +18 bytes each, '
          f'whole 33293-byte giant still NONEXACT')
    print('Only one affected VC7.1 C++ TU freshly compiled; no full cold '
          'replay or accepted whole/partial CODE/DATA exactness credit')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original CharacterObject action330/331 source verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
