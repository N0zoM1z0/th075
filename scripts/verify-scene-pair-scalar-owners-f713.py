#!/usr/bin/env python3
"""F713: complete 248-byte native authored Scene destructor real-owned pair+scalar frees.

Build only ONE selected whole original Scene C++ TU by default, or
exactly twelve genuinely used member lifetime variants with --all.
Physical native 75 x86, 12 typed original PE/COFF fields, every
original stack scratch and full nonrelocation mismatch remain visible.
No filler, no original EXE byte patch or all-943-unit cold replay.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/BattleSceneTextureDeleteF589.cpp'
OUT=ROOT/'.analysis/f713-scene-pair-scalar-owner-verified'
SYMBOL='??1BattleSceneF200@@UAE@XZ'
ORIGINAL=0x0043B0B0
SIZE=248
NATIVE_X86=75
NATIVE_REFS=12
NAMES=(('digitAtlas','0x4c'),('firstCombo','0x50'),('secondCombo','0x54'))
ORIGINAL_SCRATCH={26:'dword ptr [ebp - 0x14], edx',
                  28:'dword ptr [ebp - 0x10], eax',
                  42:'dword ptr [ebp - 0x18], eax',
                  52:'dword ptr [ebp - 0x1c], ecx',
                  62:'dword ptr [ebp - 0x20], edx'}
TEXTURE_SOURCE={26:'dword ptr [ebp - 0x20], edx',
                28:'dword ptr [ebp - 0x1c], eax'}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load_reader():
    p=ROOT/'scripts/compare-coff-function.py'
    s=importlib.util.spec_from_file_location('f713_reader',p)
    need(s is not None and s.loader is not None,'native PE reader unavailable')
    m=importlib.util.module_from_spec(s)
    sys.modules[s.name]=m
    s.loader.exec_module(m)
    return m


def variants():
    base=SOURCE.read_text()
    definition='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
    head='''    if (FIELD(TextureManagerF200*,0x08))
        delete FIELD(TextureManagerF200*,0x08);
    CleanupPointersF215 released;'''
    need(base.count(definition)==base.count(head)==1,
         'complete actual Scene destructor baseline source/ABI drift')
    cases={}
    for standalone in range(3):
        original_pair=[i for i in range(3) if i!=standalone]
        for reverse in (False,True):
            pair=original_pair[::-1] if reverse else original_pair
            for early in (False,True):
                label=f'solo{standalone}-pairrev{int(reverse)}-early{int(early)}'
                structure='struct CleanupPairF713 { void* '+NAMES[pair[0]][0]+'; void* '+NAMES[pair[1]][0]+'; };'
                src=base.replace(definition,structure)
                declaration='    CleanupPairF713 owner;\n    void* standaloneResource;'
                src=src.replace(head,
                    (declaration+'\n' if early else '')+
                    head.replace('    CleanupPointersF215 released;',
                                 '' if early else declaration))
                for index,(name,offset) in enumerate(NAMES):
                    old=f'released.{name} = FIELD(void*,{offset});'
                    new=(f'standaloneResource = FIELD(void*,{offset});'
                         if index==standalone else f'owner.{name} = FIELD(void*,{offset});')
                    need(src.count(old)==1,f'{label}: real original free-resource assignment absent')
                    src=src.replace(old,new)
                    old=f'free(released.{name});'
                    new='free(standaloneResource);' if index==standalone else f'free(owner.{name});'
                    need(src.count(old)==1,f'{label}: actual CRT-free use absent')
                    src=src.replace(old,new)
                need(src.count('free(')==3 and src.count('delete FIELD(')==1,
                     f'{label}: C++ probe must perform all three frees and real texture delete')
                expected=191 if standalone in (1,2) and not reverse else 189
                cases[label]=(src,expected)
    need(len(cases)==12,'missing genuine original 2+1 used-resource ownership variants')
    return cases


def main():
    candidates=variants()
    arg=argparse.ArgumentParser(description=__doc__)
    opt=arg.add_mutually_exclusive_group()
    opt.add_argument('--case',choices=sorted(candidates),default=None,
                     help='build just one whole native 248-byte destructor')
    opt.add_argument('--all',action='store_true',help='build only these 12 complete Scene source hypotheses')
    args=arg.parse_args()
    chosen=candidates if args.all else {
        (args.case or 'solo1-pairrev0-early0'):candidates[args.case or 'solo1-pairrev0-early0']}
    reader=load_reader()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(decoder.disasm(reader.pe_bytes_at(pe,ORIGINAL,SIZE),ORIGINAL))
    need(len(native)==NATIVE_X86 and sum(x.size for x in native)==SIZE
         and all(native[i].op_str==want for i,want in ORIGINAL_SCRATCH.items())
         and native[-1].mnemonic=='ret',
         'original native whole destructor/EH frame and five real scratch owners changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for name,(source,expect) in chosen.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(source)
        cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=150)
        cpp.with_suffix('.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,f'{name} pinned VC7.1 whole destructor build failed: {cp.stderr[-450:]}')
        code,refs=reader.object_function(obj,SYMBOL)
        compiled=list(decoder.disasm(code,0))
        need(len(code)==SIZE and len(compiled)==len(native)==NATIVE_X86
             and len(refs)==NATIVE_REFS
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(native,compiled)),
             f'{name}: original complete 248B/75x86 native-style CODE or 12 physical fields changed')
        need(all(compiled[i].op_str==value for i,value in TEXTURE_SOURCE.items()),
             f'{name}: original texture delete source two EBP slots no longer attested')
        compare=subprocess.run([str(ROOT/'scripts/repo-python'),
           str(ROOT/'scripts/compare-coff-function.py'),str(obj),SYMBOL,
           hex(ORIGINAL),str(SIZE),'--json'],cwd=ROOT,capture_output=True,text=True,timeout=120)
        need(compare.stdout.strip() and compare.returncode in (0,1),
             f'{name}: original whole 248-byte PE/COFF comparison failed')
        result=json.loads(compare.stdout)
        need(result['result']=='mismatch' and result['comparable_bytes']==200
             and result['matched_comparable_bytes']==expect
             and len(result['relocations'])==NATIVE_REFS
             and all(int(r['object_addend'],16)==0 for r in result['relocations']),
             f'{name}: genuine full original 248B/75 x86/12-field source negative differs')
        row={'case':name,'actual_native_whole_CODE_bytes':SIZE,
             'actual_source_whole_CODE_bytes':len(code),
             'native_and_compiled_x86_mnemonics_and_widths':len(compiled),
             'original_PE_zero_addend_typed_fields':NATIVE_REFS,
             'native_nonfield_matched_bytes':expect,'native_nonfield_total':200,
             'original_five_real_EBP_owners':[native[i].op_str for i in (26,28,42,52,62)],
             'new_cpp_five_actual_EBP_owners':[compiled[i].op_str for i in (26,28,42,52,62)],
             'full_original_function_exact':False,'new_accepted_game_CODE_B':0}
        rows.append(row)
        (OUT/(name+'-comparison.json')).write_text(compare.stdout)
        print(f'F713 {name}: whole original 248 CODE B/75 x86/12 COFF fields; '
              f'{expect}/200 actual nonfield bytes equal. Genuine texture and three CRT-free '
              'EBP owners remain NONEXACT; no accepted whole-function CODE.',flush=True)
    destination=OUT/('summary.json' if args.all else 'summary-'+next(iter(chosen))+'.json')
    destination.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F713 {len(rows)} selected complete Scene C++ source objects verified; '
          'zero new exact originals, no all-943-unit replay.')


if __name__=='__main__':
    main()
