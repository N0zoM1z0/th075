#!/usr/bin/env python3
"""F727: original entire 248B Scene virtual/EH destructor real array owners.

The actual three CRT-freed resources are all written/read from a real
3-pointer local array, with six actual index permutations and early/late
array declaration. Cold compile ONE selected full original-shaped VC7.1
/GX C++ destructor by default or only 12 affected units with --all.
Compare the whole original 75 x86/248B, 12 typed PE/COFF fields and
five distinct real EBP scratch owners; no dummy locals or byte graft,
no accepted exact CODE or mass 943-unit cold replay.
"""
from __future__ import annotations
import argparse
import importlib.util
import itertools
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'probes/BattleSceneTextureDeleteF589.cpp'
OUT=ROOT/'.analysis/f727-scene-genuine-array-owner-verified'
ORIGINAL=0x0043B0B0
BYTES=248
X86=75
FIELDS=12
SYMBOL='??1BattleSceneF200@@UAE@XZ'
RESOURCES=(('digitAtlas','0x4c'),('firstCombo','0x50'),('secondCombo','0x54'))
NATIVE_USED_EBP={26:'0x14',28:'0x10',42:'0x18',52:'0x1c',62:'0x20'}
SOURCE_TEXTURE_EBP={26:'0x20',28:'0x1c'}


def need(ok,message):
    if not ok:raise ValueError(message)


def load_reader():
    sp=importlib.util.spec_from_file_location('f727_reader',
                                        ROOT/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'original native PE reader missing')
    mod=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=mod
    sp.loader.exec_module(mod)
    return mod


def variants():
    original=BASE.read_text()
    declaration='    CleanupPointersF215 released;'
    texture='''    if (FIELD(TextureManagerF200*,0x08))
        delete FIELD(TextureManagerF200*,0x08);'''
    need(original.count(declaration)==original.count(texture)==1,
         'full original-scene normal C++ owner source changed')
    all_cases={}
    for perm in itertools.permutations((0,1,2)):
        for when in ('after-texture','before-texture'):
            name='array-'+''.join(map(str,perm))+'-'+when
            src=original
            array='    void* released[3];'
            if when=='after-texture':src=src.replace(declaration,array)
            else:
                src=src.replace(declaration,'')
                src=src.replace(texture,array+'\n'+texture)
            for idx,(field,offset) in enumerate(RESOURCES):
                old=f'released.{field} = FIELD(void*,{offset});'
                new=f'released[{perm[idx]}] = FIELD(void*,{offset});'
                need(src.count(old)==1,f'{name} original real resource assignment absent')
                src=src.replace(old,new)
                old=f'free(released.{field});'
                new=f'free(released[{perm[idx]}]);'
                need(src.count(old)==1,f'{name} must actually CRT free original resource')
                src=src.replace(old,new)
            need(src.count('free(')==3 and src.count('delete FIELD(')==1,
                 f'{name}: all original three real frees and texture delete required')
            all_cases[name]=(src,191 if perm[0]==0 else 189)
    need(len(all_cases)==12,'all 6 used 3-resource array permutations and 2 scopes required')
    return all_cases


def main():
    all_cases=variants()
    arg=argparse.ArgumentParser(description=__doc__)
    selection=arg.add_mutually_exclusive_group()
    selection.add_argument('--case',choices=sorted(all_cases),default=None,
                           help='cold build one complete 248-byte original-shaped Scene source')
    selection.add_argument('--all',action='store_true',
                           help='only the twelve affected whole Scene source hypotheses')
    args=arg.parse_args()
    key=args.case or 'array-012-after-texture'
    chosen=all_cases if args.all else {key:all_cases[key]}
    reader=load_reader()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(decoder.disasm(reader.pe_bytes_at(pe,ORIGINAL,BYTES),ORIGINAL))
    need(len(native)==X86 and sum(x.size for x in native)==BYTES
         and native[-1].mnemonic=='ret'
         and all(native[i].mnemonic=='mov'
                 and f'[ebp - {slot}]' in native[i].op_str
                 for i,slot in NATIVE_USED_EBP.items()),
         'original full Scene native 248/75/5 actual stack owner evidence changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    results=[]
    for name,(src,expected) in chosen.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(src)
        compiler=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),
                  str(obj),'/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],
                  cwd=ROOT,env=env,capture_output=True,text=True,timeout=160)
        cpp.with_suffix('.log').write_text(compiler.stdout+compiler.stderr)
        need(compiler.returncode==0,
             f'{name}: original VC7.1 /GX whole scene compiler failed {compiler.stderr[-430:]}')
        code,refs=reader.object_function(obj,SYMBOL)
        gen=list(decoder.disasm(code,0))
        need(len(code)==BYTES and len(gen)==X86 and len(refs)==FIELDS
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(native,gen))
             and all(f'[ebp - {slot}]' in gen[i].op_str
                     for i,slot in SOURCE_TEXTURE_EBP.items()),
             f'{name}: authentic whole original 248B/75x86/12-field source negative changed')
        diff=subprocess.run([str(ROOT/'scripts/repo-python'),
            str(ROOT/'scripts/compare-coff-function.py'),str(obj),SYMBOL,
            hex(ORIGINAL),str(BYTES),'--json'],cwd=ROOT,
            text=True,capture_output=True,timeout=120)
        need(diff.stdout.strip() and diff.returncode in (0,1),
             f'{name}: original PE full typed reference/byte comparator failed')
        result=json.loads(diff.stdout)
        need(result['result']=='mismatch'
             and result['matched_comparable_bytes']==expected
             and result['comparable_bytes']==200
             and len(result['relocations'])==FIELDS
             and all(int(r['object_addend'],16)==0 for r in result['relocations']),
             f'{name}: real original native nonfield and 12 PE/COFF typed field count changed')
        row={'variant':name,
             'original_native_whole_CODE_B':BYTES,
             'source_whole_CODE_B':len(code),
             'native_and_source_ordered_x86_mnemonics_and_widths':len(gen),
             'original_typed_PE_COFF_fields':len(result['relocations']),
             'actual_original_nonfield_bytes_equal':expected,
             'original_comparable_nonfield_bytes':200,
             'native_original_five_EBP_slots':NATIVE_USED_EBP,
             'new_actual_cpp_five_used_EBP_stores':{
                  str(i):gen[i].op_str for i in NATIVE_USED_EBP},
             'full_original_scene_function_byte_exact':False,
             'new_accepted_GAME_CODE_bytes':0}
        results.append(row)
        (OUT/(name+'-original-PE-comparison.json')).write_text(diff.stdout)
        print(f'F727 {name}: whole original 248B/75-x86/12 physical PE refs; '
              f'{expected}/200 true original nonfield bytes equal. '
              'Native texture EBP slots −0x14/−0x10 still source '
              '−0x20/−0x1C. NONEXACT.',flush=True)
    (OUT/('summary.json' if args.all else 'summary-'+key+'.json')).write_text(
        json.dumps(results,indent=2)+'\n')
    print(f'F727 {len(results)} complete original Scene source cases compared; '
          'zero accepted authored exact CODE and no all-unit cold replay.')


if __name__=='__main__':
    main()
