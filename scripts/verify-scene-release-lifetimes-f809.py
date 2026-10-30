#!/usr/bin/env python3
"""F809: 248B native Scene destructor texture/delete and three free lifetimes.

Whole original authored Scene, never cropped. Fresh pinned VC7.1 /GX
source profiles: three real pointer values in an aggregate versus
individual used locals, direct passing to CRT free, small lexical
scopes, a borrowed union wrapper and a true alignment control.
All 12 original PE fields are fully verified only for candidates
with complete original 248B instruction geometry; changed-size
sources are negative and explicitly never treated as matching.
No all-unit replay or accepted exact code delta.
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
SRC=ROOT/'probes/BattleSceneTextureDeleteF589.cpp'
OUT=ROOT/'.analysis/f809-scene-released-lifetimes'
ORIGINAL=0x0043B0B0
SIZE=248
SYMBOL='??1BattleSceneF200@@UAE@XZ'
SLOTS=(26,28,42,52,62)
NATIVE_SLOTS=(
 'dword ptr [ebp - 0x14], edx',
 'dword ptr [ebp - 0x10], eax',
 'dword ptr [ebp - 0x18], eax',
 'dword ptr [ebp - 0x1c], ecx',
 'dword ptr [ebp - 0x20], edx'
)

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(tag,rel):
    spec=importlib.util.spec_from_file_location(tag,ROOT/rel)
    need(spec is not None and spec.loader is not None,'missing true original source checker '+str(rel))
    mod=importlib.util.module_from_spec(spec)
    sys.modules[tag]=mod
    spec.loader.exec_module(mod)
    return mod

def source_variants():
    base=SRC.read_text()
    need('NONEXACT' in base,'must not promote source-only destructor to canonical exact')
    group='    CleanupPointersF215 released;'
    texture=('    if (FIELD(TextureManagerF200*,0x08))\n'
             '        delete FIELD(TextureManagerF200*,0x08);')
    begin=base.index(group)
    end=base.index('}\n#undef FIELD',begin)
    original=base[begin:end]
    need(original.count('free(')==3 and base.count(texture)==1,
         'original three actual free calls and real texture deletion lost')
    variants={'aggregate-baseline':base}
    variants['aggregate-nested-texture']=base.replace(texture,'    {\n'+texture+'\n    }',1)
    cases={}
    names=('digitAtlas','firstCombo','secondCombo')
    offsets=('0x4c','0x50','0x54')
    for kind in ('scoped-local','volatile-local','union-storage','direct-crt-free'):
        parts=[]
        for name,off in zip(names,offsets):
            if kind=='direct-crt-free':
                release=f'free(FIELD(void*,{off}));'
            elif kind=='scoped-local':
                release=f'void* {name} = FIELD(void*,{off});\n        free({name});'
            elif kind=='volatile-local':
                release=f'void* volatile {name} = FIELD(void*,{off});\n        free({name});'
            else:
                release=f'ReleaseViewF809 {name};\n        {name}.pointer = FIELD(void*,{off});\n        free({name}.pointer);'
            parts.append(f'    if (FIELD(void*,{off})) {{\n        '+release+'\n    }')
        compiled=base[:begin]+'\n'.join(parts)+'\n'+base[end:]
        if kind=='union-storage':
            compiled=compiled.replace('struct CleanupPointersF215 {',
               'union ReleaseViewF809 { void* pointer; unsigned int sameBits; };\n'
               'struct CleanupPointersF215 {',1)
        cases[kind]=compiled
    variants.update(cases)
    # This C++ source has three real used local pointer values. Its
    # declaration order is deliberately reversed, but all free() calls
    # remain in the physical native game order.
    declared=('    void* secondCombo;\n'
              '    void* firstCombo;\n'
              '    void* digitAtlas;\n')
    inner=''.join(f'    if (FIELD(void*,{off})) {{\n'
                  f'        {name} = FIELD(void*,{off});\n'
                  f'        free({name});\n'
                  '    }\n'
                  for name,off in zip(names,offsets))
    vars_used=base[:begin]+declared+inner+base[end:]
    variants['three-used-locals-reverse-declared']=vars_used
    # Grouping cleanup parameters into an actual 3-element array
    # is source-compatible with the observed three independent values.
    array_source=base.replace('struct CleanupPointersF215 {\n    void* digitAtlas;\n    void* firstCombo;\n    void* secondCombo;\n};',
                               'struct CleanupPointersF215 { void* active[3]; };')
    for j,name in enumerate(names):
        array_source=array_source.replace('released.'+name,f'released.active[{j}]')
    variants['real-pointer-array']=array_source
    # Alignment changes real ABI prologue; this is an explicitly
    # rejected alternative if the original normal EH frame changes.
    variants['aligned-pointer-owner']=base.replace(
        'struct CleanupPointersF215 {',
        '__declspec(align(8)) struct CleanupPointersF215 {',1)
    need(len(variants)==9 and all(t.count('free(')==3 and
             t.count('delete FIELD(TextureManagerF200*,0x08)')==1
             for t in variants.values()),
         'all nine must actually free original resources and delete original texture')
    return variants

def compile_one(name,source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/(name+'.cpp')
    obj=OUT/(name+'.obj')
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    cmd=[str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi']
    run=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True,timeout=210)
    (OUT/(name+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'native original Scene C++ failed '+name+' '+(run.stdout+run.stderr)[-650:])
    return obj

def main():
    rd=load('f809_reader','scripts/compare-coff-function.py')
    f589=load('f809_f589','scripts/verify-scene-texture-delete-f589.py')
    pe=rd.verified_target()
    native=rd.pe_bytes_at(pe,ORIGINAL,SIZE)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    real=list(decoder.disasm(native,ORIGINAL))
    need(len(real)==75 and sum(x.size for x in real)==SIZE
         and real[-1].mnemonic=='ret'
         and tuple(real[k].op_str for k in SLOTS)==NATIVE_SLOTS,
         'original complete Scene 248B/75-x86 EH owner stack slots unverified')
    need(len(f589.ORIGINAL_COFF)==12,'original original 12 actual PE fields lost')
    result=[]
    for name,text in source_variants().items():
        obj=compile_one(name,text)
        code,refs=rd.object_function(obj,SYMBOL)
        instructions=list(decoder.disasm(code,0))
        need(sum(x.size for x in instructions)==len(code) and len(refs)==12,
             'entire source Scene CODE/PE record size drifted '+name)
        record={'source_variant':name,'original_whole_CODE_B':SIZE,
                'source_whole_CODE_B':len(code),'original_x86':75,
                'source_whole_x86':len(instructions),
                'compiler_physical_COFF_fields':len(refs),
                'source_first_two_texture_delete_temp_slots':[
                     instructions[k].op_str if k<len(instructions) else None for k in (26,28)],
                'formally_accepted_exact':False}
        if len(code)==SIZE:
            need(len(instructions)==75,
                 'equal 248B original source with wrong instruction count '+name)
            # This compares every actual target original field at its
            # *physical original offset*. Field count alone does NOT
            # prove original relocation identity.
            need(set(r['offset'] for r in refs)==set(f589.ORIGINAL_COFF),
                 'same-size Scene original native PE offsets no longer corresponding '+name)
            mask=set()
            for r in refs:
                off=r['offset']
                want_type,want_dest=f589.ORIGINAL_COFF[off]
                field=native[off:off+4]
                actual=(int.from_bytes(field,'little') if want_type=='DIR32' else
                        ORIGINAL+off+4+int.from_bytes(field,'little',signed=True))
                need(r['type']==want_type and r['addend']==0
                     and r['local_symbol_offset'] is None and actual==want_dest,
                     'source original real physical PE relocation/target invalid '+name+' '+str(r))
                mask.update(range(off,off+4))
            bad=[k for k in range(SIZE) if k not in mask and code[k]!=native[k]]
            record['independently_verified_original_12_PE_fields']=True
            record['original_nonrelocation_byte_matches']=SIZE-len(mask)-len(bad)
            record['original_nonrelocation_byte_total']=SIZE-len(mask)
            record['unmasked_original_byte_differences']=bad
            need(len(mask)==48 and len(bad)==(9 if name in
                     ('aggregate-baseline','aggregate-nested-texture','real-pointer-array')
                     else 11),
                 'selected source-native original stack role mismatch changed '+name)
            record['source_original_five_stack_roles']={
                    str(k):instructions[k].op_str for k in SLOTS}
        else:
            need((name=='direct-crt-free' and
                       len(code)==230 and len(instructions)==69) or
                 (name=='aligned-pointer-owner' and
                       len(code)==271 and len(instructions)==85),
                 'candidate changed full native Scene extent unexpectedly '+name)
            record['original_PE_relocation_offsets_not_comparable']=True
            record['nonexact_reason']='missing three real source free temp stores' if name=='direct-crt-free' else 'non-native aligned stack/EH prologue'
            if name=='direct-crt-free':
                need([instructions[k].op_str for k in (26,28)]==
                     list(NATIVE_SLOTS[:2]),
                     'full original direct free source did not recover native texture+delete receiver slots')
        result.append(record)
        print('F809',name,'whole',len(code),'/248 CODE B, x86',len(instructions),
              'physically comparable',record.get('original_nonrelocation_byte_matches','wrong original length'),
              'texture slots',record['source_first_two_texture_delete_temp_slots'],flush=True)
    need(len(result)==9,'must test all 9 original real Scene lifetime variants')
    report={'original_function':'0x0043B0B0',
            'reviewed_authored_origin':True,'original_full_CODE_B':248,
            'original_full_x86':75,'original_physical_PE_fields':12,
            'native_original_texture_delete_EBP':['-0x14','-0x10'],
            'native_original_three_freed_pointer_EBP':['-0x18','-0x1C','-0x20'],
            'natural_inlining_free_recovers_two_real_texture_slots':True,
            'but_direct_free_omits_six_native_original_pointer_store_instructions':True,
            'no_candidate_reproduces_entire_original_native_248B':True,
            'source_variants':result,
            'formal_new_game_callable_exact_CODE':0,'all_accepted_units_cold_replayed':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+chr(10))
    print('F809 nine complete original Scene authored C++ function compiler variants: aggregate best 191/200 genuine nonfield PE bytes; direct free source 230B/69x86 gets texture EBP -14/-10 but loses 18B/6 actually used free-pointer stores. Full original 248B/75x86 remains nonexact; no false credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F809 original Scene whole PE/COFF physical result FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
