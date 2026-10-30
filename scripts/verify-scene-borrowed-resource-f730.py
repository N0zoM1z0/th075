#!/usr/bin/env python3
"""F730: complete original 248B/75-x86 Scene EH destructor resource references.

Test genuine source aliasing of the three original Scene fields at
`this+0x4C/0x50/0x54`, with one used C++ resource-struct pointer or
reference, three real used member references, or per-guard borrows.
Each candidate actually frees all three resources and conditionally
deletes the native texture, with authentic VC7.1 /Od /GX.
Default cold-build one entire original-shaped 248-byte function;
--all builds ONLY these ten affected whole small C++ TUs.
No fake locals, byte grafts, original EXE edits or all-943 cold replay.
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
BASE=ROOT/'probes/BattleSceneTextureDeleteF589.cpp'
OUT=ROOT/'.analysis/f730-scene-borrowed-resource-verified'
ADDRESS=0x0043B0B0
BYTES=248
X86=75
NATIVE_FIELDS=12
SYMBOL='??1BattleSceneF200@@UAE@XZ'
SOURCE_REFS=(
 ('DIR32','__ehhandler$??1BattleSceneF200'),
 ('DIR32','__except_list'),
 ('DIR32','__except_list'),
 ('DIR32','??_7BattleSceneF200'),
 ('DIR32','?g_FrameClockModeAt0066C238'),
 ('REL32','?SetClampedGameValue@StateValueF200'),
 ('REL32','??_GTextureManagerF200'),
 ('REL32','_free'),('REL32','_free'),('REL32','_free'),
 ('REL32','??1SceneBaseF200'),
 ('DIR32','__except_list'))
FIELDS=(('digitAtlas','0x4c'),('firstCombo','0x50'),('secondCombo','0x54'))
ORIGINAL_ACTUAL_SCRATCH={26:'0x14',28:'0x10',42:'0x18',52:'0x1c',62:'0x20'}


def need(ok,explanation):
    if not ok:raise ValueError(explanation)


def load_reader():
    sp=importlib.util.spec_from_file_location('f730_native',
                                          ROOT/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'pinned original PE reader unavailable')
    obj=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=obj
    sp.loader.exec_module(obj)
    return obj


def variants():
    base=BASE.read_text()
    texture='''    if (FIELD(TextureManagerF200*,0x08))
        delete FIELD(TextureManagerF200*,0x08);'''
    scope={'early':'    if (g_FrameClockModeAt0066C238 == 2 || 4)',
           'late':'    CleanupPointersF215 released;'}
    need(base.count(texture)==1 and all(base.count(x)==1 for x in scope.values()),
         'original full Scene used resource pointers/conditional texture delete not unique')
    cases={}
    for type_ in ('struct-ref','struct-ptr','individual-refs','individual-const-refs'):
        for timing,point in scope.items():
            src=base
            if type_=='struct-ref':
                decl=('    CleanupPointersF215& borrowed = '
                      '*reinterpret_cast<CleanupPointersF215*>('
                      'reinterpret_cast<unsigned char*>(this)+0x4c);')
                for member,off in FIELDS:
                    src=src.replace(f'FIELD(void*,{off})',f'borrowed.{member}')
            elif type_=='struct-ptr':
                decl=('    CleanupPointersF215* borrowed = '
                      'reinterpret_cast<CleanupPointersF215*>('
                      'reinterpret_cast<unsigned char*>(this)+0x4c);')
                for member,off in FIELDS:
                    src=src.replace(f'FIELD(void*,{off})',f'borrowed->{member}')
            else:
                decl=''
                for member,off in FIELDS:
                    typ='void*&' if type_=='individual-refs' else 'void* const&'
                    decl+=f'    {typ} borrowed_{member} = FIELD(void*,{off});\n'
                    src=src.replace(f'FIELD(void*,{off})',f'borrowed_{member}')
            src=src.replace(point,decl+'\n'+point)
            cases[f'{type_}-{timing}']=(src,(255,78) if type_.startswith('struct') else (269,84))
    for typ,label in (('void*&','per-guard-ref'),
                      ('void* const&','per-guard-constref')):
        src=base
        for member,off in FIELDS:
            needle=f'        released.{member} = FIELD(void*,{off});'
            need(src.count(needle)==1,'native actual borrowed member assignment missing')
            src=src.replace(needle,
              f'        {typ} borrowed_{member} = FIELD(void*,{off});\n'
              f'        released.{member} = borrowed_{member};')
        cases[label]=(src,(272,84))
    need(len(cases)==10,'ten complete original Scene borrowed-field aliases not generated')
    for name,(src,_) in cases.items():
        actually_reads_resources=(
            (all(f'FIELD(void*,{offset})' in src for _,offset in FIELDS))
            or ('reinterpret_cast<CleanupPointersF215*>' in src
                and all(member in src for member,_ in FIELDS)
                and 'this)+0x4c' in src))
        need(src.count('free(')==3 and src.count('delete FIELD(')==1
             and actually_reads_resources,
             f'{name}: original actual 3 resource pointers/free/texture operations absent')
    return cases


def main():
    all_cases=variants()
    parser=argparse.ArgumentParser(description=__doc__)
    select=parser.add_mutually_exclusive_group()
    select.add_argument('--case',choices=sorted(all_cases),default=None,
                        help='compile just one entire nonexact Scene source')
    select.add_argument('--all',action='store_true',
                        help='only the ten directly affected complete small Scene objects')
    args=parser.parse_args()
    key=args.case or 'struct-ref-late'
    chosen=all_cases if args.all else {key:all_cases[key]}
    rd=load_reader()
    pe=rd.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(dec.disasm(rd.pe_bytes_at(pe,ADDRESS,BYTES),ADDRESS))
    need(len(native)==X86 and sum(x.size for x in native)==BYTES
         and native[-1].mnemonic=='ret'
         and all(native[i].mnemonic=='mov'
                 and f'[ebp - {slot}]' in native[i].op_str
                 for i,slot in ORIGINAL_ACTUAL_SCRATCH.items())
         and [native[i].op_str for i in (19,33,45,55,65,69)]
          ==[f'0x{x:x}' for x in (0x423c60,0x425460,0x640f15,
                                  0x640f15,0x640f15,0x431f40)],
         'real entire original Scene PE 248B/75-x86/EH/source owner changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for name,(src,expected) in chosen.items():
        cpp=OUT/(name+'.cpp')
        obj=cpp.with_suffix('.obj')
        cpp.write_text(src)
        cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
               '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],
               cwd=ROOT,env=env,capture_output=True,text=True,timeout=160)
        cpp.with_suffix('.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,
             f'{name}: native VC7.1 full Scene /GX compile failed: {cp.stderr[-400:]}')
        code,refs=rd.object_function(obj,SYMBOL)
        gen=list(dec.disasm(code,0))
        need((len(code),len(gen))==expected
             and len(refs)==NATIVE_FIELDS
             and len(code)>BYTES,
             f'{name}: original entire function geometry and nonexact source case changed')
        for i,(typ,symbol) in enumerate(SOURCE_REFS):
            ref=refs[i]
            need(ref['type']==typ and symbol in ref['symbol']
                 and ref['addend']==0 and ref['local_symbol_offset'] is None
                 and any(i2.address<=ref['offset']<i2.address+i2.size
                         for i2 in gen),
                 f'{name}: actual physically typed original source EH/vtable/free/base reference {i} missing')
        result={'case':name,'original_whole_CODE_B':BYTES,
                'native_full_x86':X86,
                'original_real_typed_PE_COFF_fields':NATIVE_FIELDS,
                'compiler_whole_CODE_B':len(code),
                'compiler_entire_x86':len(gen),
                'source_actual_physically_typed_fields':len(refs),
                'source_three_real_CRT_free_calls':sum('_free' in r['symbol'] for r in refs),
                'source_original_three_EH_setup_restore_field_roles':True,
                'original_used_EBP_scratch':ORIGINAL_ACTUAL_SCRATCH,
                'source_Cpp_operand_at_original_ordinals':{
                        str(i):gen[i].op_str for i in ORIGINAL_ACTUAL_SCRATCH},
                'native_whole_original_game_function_exact':False,
                'new_accepted_authored_GAME_CODE_bytes':0}
        rows.append(result)
        print(f'F730 {name}: actual original native 248B/75 x86, '
              f'full source {len(code)}B/{len(gen)} x86, '
              'same 12 typed EH/vtable/free/base source fields, '
              'NOT byte-exact.',flush=True)
    (OUT/('summary.json' if args.all else 'summary-'+key+'.json')).write_text(
        json.dumps(rows,indent=2)+'\n')
    print(f'F730 {len(rows)} whole original Scene borrowed-resource C++ cases; '
          'no new accepted native whole CODE or mass cold replay.')


if __name__=='__main__':
    main()
