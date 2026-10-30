#!/usr/bin/env python3
"""F790: verify real-mode63 stage and outer-control hypotheses in one full giant per variant.

All comparison evidence comes from the original 58,294B Japanese PE,
not historical strict case labels. Test original-shaped normal C++ in
six independent whole-parent VC7.1 builds, never a cropped case.
Reject semantically dubious alternatives despite near-native lengths.
No credited authored CODE and no all-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f790-fighter-mode63-controls'
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
ORIGINAL_CASE=(0x00545ADE,0x00545DA0,706,189)
EXPECTED_WIDTHS=[18,61,84]

def load(tag,file):
    sp=importlib.util.spec_from_file_location(tag,ROOT/file)
    if sp is None or sp.loader is None:raise ValueError('missing original source '+str(file))
    mod=importlib.util.module_from_spec(sp)
    sys.modules[tag]=mod
    sp.loader.exec_module(mod)
    return mod

def require(ok,msg):
    if not ok:raise ValueError(msg)

def main():
    f781=load('f790_f781','scripts/verify-fighter-shared-getter-f781.py')
    f778=load('f790_f778','scripts/verify-fighter-native-default-f778.py')
    f759=load('f790_f759','scripts/verify-fighter-four-directional-c8-f759.py')
    f762=load('f790_f762','scripts/verify-fighter-typed-returns-f762.py')
    f734=load('f790_f734','scripts/verify-fighter-eight-round-f734.py')
    f777=load('f790_f777','scripts/verify-fighter-current-register-phases-f777.py')
    rd=load('f790_reader','scripts/compare-coff-function.py')
    source,boss=f781.source_for_whole_parent(f778,f759,f762)
    marker='#include "FighterMode63BasicF626.inc"'
    require(source.count(marker)==1,'natural full parent missing true mode63 source')
    base=(ROOT/'probes/FighterMode63BasicF626.inc').read_text()
    stage='*reinterpret_cast<signed short*>(OWNER+0x60)<150'
    condition=('    if (g_ModeAt006714B4 != 3 ||\n'
               '        *reinterpret_cast<signed char*>(RAW+0x2CD)==0) {')
    require(base.count(stage)==4 and base.count(condition)==1,
            'F790 entire stage or outer case source changed')
    variants={
        'baseline':base,
        'reversed-constant':base.replace(stage,'150>*reinterpret_cast<signed short*>(OWNER+0x60)'),
        'explicit-signed-int':base.replace(stage,'static_cast<int>(*reinterpret_cast<signed short*>(OWNER+0x60))<150'),
        'negated-greater-equal':base.replace(stage,'!(*reinterpret_cast<signed short*>(OWNER+0x60)>=150)'),
        'off-by-one-less-equal':base.replace(stage,'*reinterpret_cast<signed short*>(OWNER+0x60)<=149'),
        'swapped-shortcircuit':base.replace(condition,
              '    if (*reinterpret_cast<signed char*>(RAW+0x2CD)==0 ||\n'
              '        g_ModeAt006714B4 != 3) {'),
        'bool-flag':base.replace(condition,
              '    if (g_ModeAt006714B4 != 3 ||\n'
              '        !static_cast<bool>(*reinterpret_cast<signed char*>(RAW+0x2CD))) {'),
    }
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    pe=rd.verified_target()
    lo,hi,nlen,nx=ORIGINAL_CASE
    target=rd.pe_bytes_at(pe,lo,nlen)
    native=list(decoder.disasm(target,lo))
    require(len(native)==nx and native[-1].address+native[-1].size==hi,
            'native original entire mode63 706B/189-x86 extent is unverified')
    require([(native[j].op_str,native[j].size) for j in EXPECTED_WIDTHS]
            == [('edx, 0x96',6),('eax, 0x96',5),('edx, 0x96',6)],
            'actual native target stage operand and CMP width evidence changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for name,variant in variants.items():
        cpp=OUT/(name+'.cpp')
        obj=OUT/(name+'.obj')
        cpp.write_text(source.replace(marker,variant,1))
        command=[str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes']
        cp=subprocess.run(command,cwd=ROOT,env=env,capture_output=True,text=True,timeout=240)
        (OUT/(name+'.log')).write_text(cp.stdout+cp.stderr)
        require(cp.returncode==0,'VC7.1 whole original parent did not compile for '+name+
                (cp.stdout+cp.stderr)[-650:])
        code,refs=rd.object_function(obj,SYM)
        instructions=[]
        for i in decoder.disasm(code,0):
            instructions.append(i)
            if i.mnemonic=='ret':break
        ret=instructions[-1].address+instructions[-1].size
        require(len(refs)==1863 and len(code)==ret+943,
                'original whole source switch DATA or physical COFF references drifted '+name)
        mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,instructions,refs)
        start,stop=mapping[lo],mapping[hi]
        current=[i for i in instructions if start<=i.address<stop]
        widths=[j for j,(a,b) in enumerate(zip(native,current)) if a.size!=b.size]
        mnemonic_bad=[j for j,(a,b) in enumerate(zip(native,current)) if a.mnemonic!=b.mnemonic]
        record={'variant':name,'entire_compiled_CODE_B':ret,
                'original_entire_CODE_B':58294,
                'source_x86':len(instructions),
                'original_full_x86':16471,
                'mode63_compiled_CODE_B':stop-start,
                'original_mode63_CODE_B':nlen,
                'mode63_compiled_x86':len(current),
                'real_CMP_width_wrong_ordinals':widths,
                'whole_case_wrong_mnemonic_ordinals':mnemonic_bad,
                'actual_original_CMP':[native[j].op_str for j in EXPECTED_WIDTHS],
                'VC71_generated_CMP':[current[j].op_str for j in EXPECTED_WIDTHS],
                'actual_COFF_fields':len(refs),
                'whole_game_exact':False}
        if name in ('baseline','reversed-constant','explicit-signed-int','negated-greater-equal'):
            require(ret==58293 and len(instructions)==16471
                    and stop-start==705 and len(current)==189
                    and widths==EXPECTED_WIDTHS and not mnemonic_bad,
                    'non-improving meaningful original stage comparison no longer matches known real x86 geometry')
            # This verifies all 15 *physical original* case PE/COFF
            # targets and each native instruction position in this
            # newly built full parent, not merely matching register descriptions.
            case=f777.physical_whole_case(rd,pe,decoder,code,refs,instructions,mapping,0x63,f777.ORIGINAL[0x63])
            require(case['native_zero_addend_typed_PE_COFF_fields_checked']==15,
                    'actual full 0x63 original typed PE fields changed')
            record['independently_verified_native_mode63_PE_fields']=15
        if name=='baseline':
            shared=f781.verify_original_shared_getter(rd,pe,decoder,code,refs,instructions,ret)
            require(shared['original_46B_suffix_and_source_46B_suffix_x86']==16,
                    'true original 46B shared getter suffix no longer preserved')
            prior=[f777.physical_whole_case(rd,pe,decoder,code,refs,instructions,mapping,c,f777.ORIGINAL[c])
                   for c in (0x58,0x59,0x60,0x61)]
            require([x['actual_original_nonfield_operand_byte_mismatches'] for x in prior]==[0,19,98,101],
                    'fresh native original early case register comparison changed')
            f759.check_afterret(rd,pe,decoder,boss,code,refs,instructions)
            record['true_early_original_case_GPR_byte_differences']=[0,19,98,101]
            record['native_shared_getter_46B_and_943B_switch_DATA_rechecked']=True
        rows.append(record)
        print(f'F790 {name}: whole source {ret}/58294 CODE B; 0x63 {stop-start}/706 B; '
              f'wrong width ordinals {widths[:12]}; mnemonic differences {mnemonic_bad[:8]}; '
              f'{len(refs)} COFF fields; not exact.',flush=True)
    names={x['variant']:x for x in rows}
    require(len(rows)==7 and names['off-by-one-less-equal']['whole_case_wrong_mnemonic_ordinals']
             ==[19,39,62,85] and names['swapped-shortcircuit']['whole_case_wrong_mnemonic_ordinals']
             ==[0,1,2,3,5,6] and
             names['bool-flag']['entire_compiled_CODE_B']==58300,
             'native negative branch grammar controls changed; audit before recording')
    report={'original_Japanese_PE_version':'TH075 v1.11',
            'original_callable_fighter':'0x00543210',
            'native_full_CODE_B':58294,
            'best_full_source_CODE_B':58293,
            'best_source_instruction_count':16471,
            'mode63_original_706B_CMP_register_width_problem':[18,61,84],
            'independent_whole_parent_source_compilations':len(rows),
            'all_variants':rows,
            'full_game_function_exact':False,
            'new_canonical_authored_exact_CODE':0,
            'all_unit_cold_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F790 verified seven complete affected 58KB VC7.1 parents; native 0x63 CMP 18/61/84 and 059/060/061 native GPR differences unresolved. 943B separate native table verified; no whole game exact credit.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F790 giant physical research FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
