#!/usr/bin/env python3
"""F589: original 248-byte SceneObject destructor pointer-delete controls.

Pin the genuine Japanese TH075 1.11 entire native 248-byte/75-insn
virtual-EH destructor and physically verify all 12 native PE/COFF
call/global fields, even in 11 source-only nonexact variants. Build
only selected ordinary VC7.1 C++ TUs with genuine `/GX` (not `/GX-`)
and compare the ENTIRE original function. A matrix of 14 natural
texture-pointer cast/ref/conditional expression variants is explicitly
negative, not an original exact-credit claim. No all-unit cold replay.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from collections import Counter

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/BattleSceneTextureDeleteF589.cpp'
OUT=ROOT/'.analysis/f589-scene-texture-source'
ORIGINAL=0x0043B0B0
SIZE=248
SYMBOL='??1BattleSceneF200@@UAE@XZ'
EXPR='delete FIELD(TextureManagerF200*,0x08);'
VALUE='FIELD(TextureManagerF200*,0x08)'
VARIANTS={
 'paren':f'delete ({VALUE});',
 'static_cast':f'delete static_cast<TextureManagerF200*>({VALUE});',
 'reinterpret_cast':f'delete reinterpret_cast<TextureManagerF200*>({VALUE});',
 'cstyle_cast':f'delete (TextureManagerF200*)({VALUE});',
 'const_cast':f'delete const_cast<TextureManagerF200*>({VALUE});',
 'double_pointer':'delete *((TextureManagerF200**)(reinterpret_cast<unsigned char*>(this)+0x08));',
 'lvalue_ref':f'delete static_cast<TextureManagerF200*&>({VALUE});',
 'const_ref':f'delete static_cast<TextureManagerF200* const&>({VALUE});',
 'address_deref':f'delete *(&{VALUE});',
 'const_pointer':'delete (static_cast<TextureManagerF200* const&>(FIELD(TextureManagerF200*,0x08)));',
 'conditional_true':f'delete (true ? {VALUE} : (TextureManagerF200*)0);',
 'conditional_false':f'delete (false ? (TextureManagerF200*)0 : {VALUE});',
 'sizeof_precondition':f'delete ((sizeof(TextureManagerF200*)==4) ? {VALUE} : (TextureManagerF200*)0);',
 'member_pointer':'delete *reinterpret_cast<TextureManagerF200**>(reinterpret_cast<unsigned char*>(this)+8);',
}

# The twelve actual TARGET PE COFF fields are not substituted for CODE.
# Each accepted C++ field must resolve to this independently verified PE
# destination, including EH handler (two FS exception-list bindings),
# 3 native CRT frees and the true base virtual destructor.
ORIGINAL_COFF={
  0x06:('DIR32',0x00655B86),
  0x0C:('DIR32',0),
  0x14:('DIR32',0),
  0x23:('DIR32',0x00658334),
  0x31:('DIR32',0x0066C238),
  0x46:('REL32',0x00423C60),
  0x71:('REL32',0x00425460),
  0x98:('REL32',0x00640F15),
  0xB6:('REL32',0x00640F15),
  0xD4:('REL32',0x00640F15),
  0xE6:('REL32',0x00431F40),
  0xF0:('DIR32',0),
}


def need(ok,why):
    if not ok:raise ValueError(why)


def load(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,
         f'missing original scene PE/COFF reader {path}')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[tag]=mod
    spec.loader.exec_module(mod)
    return mod


def read_original():
    reader=load('f589_original_reader',ROOT/'scripts/compare-coff-function.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(decoder.disasm(reader.pe_bytes_at(pe,ORIGINAL,SIZE),ORIGINAL))
    need(len(native)==75 and sum(i.size for i in native)==SIZE and
         native[-1].mnemonic=='ret' and
         native[7].mnemonic=='sub' and native[7].op_str=='esp, 0x1c',
         'original whole native 248-byte scene destructor geometry/EA frame changed')
    real={26:'dword ptr [ebp - 0x14], edx',
          28:'dword ptr [ebp - 0x10], eax',
          42:'dword ptr [ebp - 0x18], eax',
          52:'dword ptr [ebp - 0x1c], ecx',
          62:'dword ptr [ebp - 0x20], edx'}
    need(all(native[i].mnemonic=='mov' and native[i].op_str==value
             for i,value in real.items()),
         'original native deleted texture/resource free temp locations were guessed wrong')
    need(native[33].mnemonic=='call' and native[33].op_str=='0x425460'
         and [native[k].op_str for k in (45,55,65)]==['0x640f15']*3
         and native[69].op_str=='0x431f40',
         'original complete scene destructor real scalar-delete/free/base calls changed')
    return reader,decoder


def compile_one(reader,decoder,tag,expression):
    source=SOURCE.read_text()
    need(source.count(EXPR)==1 and 'NONEXACT' in source,
         'original source-only native scene destructor input drift')
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}.cpp';obj=OUT/f'{tag}.obj'
    cpp.write_text(source.replace(EXPR,expression))
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],
                     cwd=ROOT,env=env,text=True,capture_output=True,timeout=120)
    (OUT/f'{tag}-compile.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,
         f'fresh pinned real EH-profile VC7.1 compiler failed source variant {tag}: {p.stderr}')
    code,refs=reader.object_function(obj,SYMBOL)
    actual=list(decoder.disasm(code,0))
    res=subprocess.run([sys.executable,str(ROOT/'scripts/compare-coff-function.py'),
                        str(obj),SYMBOL,hex(ORIGINAL),str(SIZE),'--json'],
                       cwd=ROOT,capture_output=True,text=True,timeout=120)
    need(res.stdout.strip() and res.returncode in (0,1),
         f'failed whole native original scene PE/COFF source compare {tag}: {res.stderr}')
    (OUT/f'{tag}-comparison.json').write_text(res.stdout)
    data=json.loads(res.stdout)
    result={'variant':tag,'compiler_x86_instructions':len(actual),
            'compiler_CODE_bytes':len(code),'whole_original_comparison':data['result'],
            'same_nonfield_bytes':data.get('matched_comparable_bytes'),
            'total_nonfield_bytes':data.get('comparable_bytes')}
    expected_sizes={'conditional_true':272,'conditional_false':267,'sizeof_precondition':272}
    if tag in expected_sizes:
        need(data['result']=='size-mismatch' and len(code)==expected_sizes[tag],
             f'non-original conditional texture expression accidentally matched 248 original bytes: {tag}')
    else:
        need(data['result']=='mismatch' and len(code)==SIZE and len(actual)==75
             and data['matched_comparable_bytes']==191 and
             data['comparable_bytes']==200,
             f'actual original scene destructor 248/75 exact comparison changed for source variant {tag}')
        need(all(actual[i].mnemonic=='mov' and actual[i].op_str==x
                 for i,x in {26:'dword ptr [ebp - 0x20], edx',
                             28:'dword ptr [ebp - 0x1c], eax',
                             42:'dword ptr [ebp - 0x18], eax',
                             52:'dword ptr [ebp - 0x14], ecx',
                             62:'dword ptr [ebp - 0x10], edx'}.items()),
             'candidate source scene texture/three resource temporary EBP allocation actually changed; inspect before claiming nonexact')
        reloc=data['relocations']
        need(len(reloc)==len(ORIGINAL_COFF)==12,
             'original scene virtual destructor physically has 12 relocation records, not guessed 8')
        for field in reloc:
            off=int(field['offset'],16)
            need(off in ORIGINAL_COFF and
                 (field['type'],int(field['solved_destination'],16))==ORIGINAL_COFF[off]
                 and int(field['object_addend'],16)==0,
                 f'original scene full virtual EH+scalar delete+3 frees+base COFF was not zero-addend at {off:#x}')
        result['actual_original_typed_COFF_fields']=len(reloc)
    return result


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--case',choices=list(VARIANTS),
                   help='Only one affected original 248-byte source control; default all 14 (not cold replay)')
    opts=p.parse_args()
    reader,decoder=read_original()
    selection=[opts.case] if opts.case else list(VARIANTS)
    results=[]
    for tag in selection:
        r=compile_one(reader,decoder,tag,VARIANTS[tag])
        results.append(r)
        print(f'{tag}: {r["compiler_x86_instructions"]} x86, {r["compiler_CODE_bytes"]} '
              f'CODE bytes, {r["whole_original_comparison"]}; original nonfield '
              f'{r["same_nonfield_bytes"]}/{r["total_nonfield_bytes"]}',flush=True)
    if not opts.case:
        need(len(results)==14 and
             Counter(x['whole_original_comparison'] for x in results)=={'mismatch':11,'size-mismatch':3},
             'expected native scene original negative control matrix changed; re-review ownership')
    (OUT/('summary.json' if not opts.case else f'summary-{opts.case}.json')).write_text(json.dumps(results,indent=2)+'\n')
    print(f'F589 original 248-byte scene virtual destructor: {len(results)} new actual '
          'VC7.1 C++ delete-expression controls, all NONEXACT; no accepted original '
          'CODE/DATA, no all-unit cold replay, no external Oracle')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F589 original whole scene texture-delete verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
