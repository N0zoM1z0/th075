#!/usr/bin/env python3
"""F818: true Scene texture+3 free-field owner view, normal original VC7.1 codegen.

Independently verify original 0043B0B0 full 248B/75-x86/12 PE refs,
then compile seven real whole C++ destructor alternatives. Typed
borrowed view of actual original texture+free offsets emits the SAME
whole 248B/75-x86 COFF as raw FIELD, still 191/200 nonrel bytes;
naming the actual borrowed view pointer/ref emits extra 6B/2 x86
and changes native EH saved-this geometry. No artificial
padding/local instantiation, no exact authored CODE or mass cold replay.
"""
from __future__ import annotations
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f818-scene-borrowed-owner'
SOURCE=ROOT/'probes/BattleSceneTextureDeleteF589.cpp'
SYM='??1BattleSceneF200@@UAE@XZ'
ORIGINAL=0x0043B0B0

def need(test,msg):
    if not test:raise ValueError(msg)

def load(tag,path):
    spec=importlib.util.spec_from_file_location(tag,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing original PE verifier')
    m=importlib.util.module_from_spec(spec)
    sys.modules[tag]=m
    spec.loader.exec_module(m)
    return m

def source_variants():
    base=SOURCE.read_text()
    need('NONEXACT' in base and base.count('free(')==3,
         'true whole Scene destructor actual 3 real free calls changed')
    # Borrowed view only: NEVER declared as the actual complete historical
    # C++ class, constructed or embedded. It describes ONLY observed offsets.
    view='''// F818 borrowed physical observation, NOT an instantiated class owner.
struct BorrowedSceneResourcesF818 {
    unsigned char observedNativeBaseBefore8[8];
    TextureManagerF200* textureAt08;
    unsigned char unknownNativeFieldsBetween0CAnd4C[0x40];
    void* firstFreeAt4C;
    void* secondFreeAt50;
    void* thirdFreeAt54;
};
'''
    need('struct CleanupPointersF215 {' in base,'source borrowed location changed')
    original=[
        ('FIELD(TextureManagerF200*,0x08)','textureAt08'),
        ('FIELD(void*,0x4c)','firstFreeAt4C'),
        ('FIELD(void*,0x50)','secondFreeAt50'),
        ('FIELD(void*,0x54)','thirdFreeAt54')]
    variants={'baseline':base}
    for name,texture,free,local in (
          ('typed-texture',True,False,None),
          ('typed-three-frees',False,True,None),
          ('typed-all',True,True,None),
          ('used-borrowed-reference',True,True,'reference'),
          ('used-borrowed-pointer',True,True,'pointer'),
          ('used-borrowed-constpointer',True,True,'constpointer')):
        source=base
        prefix=('reinterpret_cast<BorrowedSceneResourcesF818*>(this)->'
                if local is None else
                'borrowed.' if local=='reference' else 'borrowed->')
        if texture:
            source=source.replace(original[0][0],prefix+original[0][1])
        if free:
            for old,field in original[1:]:
                source=source.replace(old,prefix+field)
        if local is not None:
            if local=='reference':
                declaration=('    BorrowedSceneResourcesF818& borrowed = '
                    '*reinterpret_cast<BorrowedSceneResourcesF818*>(this);\n')
            elif local=='pointer':
                declaration=('    BorrowedSceneResourcesF818* borrowed = '
                    'reinterpret_cast<BorrowedSceneResourcesF818*>(this);\n')
            else:
                declaration=('    const BorrowedSceneResourcesF818* borrowed = '
                    'reinterpret_cast<const BorrowedSceneResourcesF818*>(this);\n')
            marker='    if (g_FrameClockModeAt0066C238 == 2 || 4)'
            need(source.count(marker)==1,'scene state-before-texture declaration moved')
            source=source.replace(marker,declaration+marker,1)
        source=source.replace('struct CleanupPointersF215 {',view+'\nstruct CleanupPointersF215 {',1)
        need(source.count('free(')==3
             and source.count('delete ')>=1
             and source.count('struct BorrowedSceneResourcesF818')==1,
             'whole source resource lifetime or borrowed field evidence lost')
        variants[name]=source
    need(len(variants)==7,'expected seven meaningful complete Scene variants')
    return variants

def compiler(name,src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/(name+'.cpp')
    obj=OUT/(name+'.obj')
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,d;winemenubuilder.exe=d'.replace('winewayland.drv,d','winewayland.drv=d')
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=230)
    (OUT/(name+'.log')).write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'F818 complete Scene original VC7.1 compile failed '+name+' '+
         (proc.stdout+proc.stderr)[-700:])
    return obj

def main():
    rd=load('f818_rd','scripts/compare-coff-function.py')
    f589=load('f818_f589','scripts/verify-scene-texture-delete-f589.py')
    pe=rd.verified_target()
    native=rd.pe_bytes_at(pe,ORIGINAL,248)
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    n=list(d.disasm(native,ORIGINAL))
    need(len(n)==75 and n[-1].mnemonic=='ret' and
         [n[i].op_str for i in (26,28,42,52,62)]==[
           'dword ptr [ebp - 0x14], edx',
           'dword ptr [ebp - 0x10], eax',
           'dword ptr [ebp - 0x18], eax',
           'dword ptr [ebp - 0x1c], ecx',
           'dword ptr [ebp - 0x20], edx'],
         'native Scene original 248B/75-x86 five real pointer slots changed')
    original_fields=f589.ORIGINAL_COFF
    need(len(original_fields)==12,'real Scene original PE fields missing')
    rows=[]
    base_code=None
    base_reloc=None
    for name,src in source_variants().items():
        obj=compiler(name,src)
        code,refs=rd.object_function(obj,SYM)
        ins=list(d.disasm(code,0))
        need(sum(x.size for x in ins)==len(code) and len(refs)==12,
             'entire untruncated C++ source/real COFF field count wrong '+name)
        row={'variant':name,'original_whole_B':248,
             'source_whole_B':len(code),'original_x86':75,
             'source_x86':len(ins),'compiler_COFF_records':len(refs),
             'source_actual_texture_delete_temp_slots':[
                 ins[k].op_str for k in (26,28) if k<len(ins)]}
        if name=='baseline':
            base_code=code
            base_reloc=[(r['offset'],r['type'],r['addend'],r['local_symbol_offset'],r['symbol']) for r in refs]
        if name in ('baseline','typed-texture','typed-three-frees','typed-all'):
            need(len(code)==248 and len(ins)==75 and code==base_code,
                 'typed original borrowed field access changes actual machine CODE '+name)
            current=[(r['offset'],r['type'],r['addend'],r['local_symbol_offset'],r['symbol']) for r in refs]
            need(current==base_reloc,'typed field access alters compiler PE/COFF field binding '+name)
            need(set(r['offset'] for r in refs)==set(original_fields),
                 'true Scene native original physical 12 field offsets shifted '+name)
            mask=set()
            for r in refs:
                off=r['offset']
                typ,target=original_fields[off]
                real=int.from_bytes(native[off:off+4],'little') if typ=='DIR32' else (
                    ORIGINAL+off+4+int.from_bytes(native[off:off+4],'little',signed=True))
                need(r['type']==typ and r['addend']==0 and
                     r['local_symbol_offset'] is None and real==target,
                     'new typed native Scene source would falsely mask a moved PE field')
                mask.update(range(off,off+4))
            bad=[i for i in range(248) if i not in mask and code[i]!=native[i]]
            need(len(bad)==9 and len(mask)==48,'real original Scene stack mismatch count changed')
            row['physically_attested_original_PE_fields']=12
            row['true_original_nonfield_matching_B']='191/200'
            row['all_compiler_function_bytes_equal_to_baseline']=True
            row['native_nonfield_wrong_offsets']=bad
        else:
            need(len(code)==254 and len(ins)==77 and
                 ins[8].op_str=='dword ptr [ebp - 0x28], ecx',
                 'named real borrowed access expected two genuine new x86 and saved-this -0x28')
            row['original_entire_function_size_mismatch']=True
            row['original_PE_field_offsets_not_independently_comparable']=True
        rows.append(row)
        print('F818',name,'full native C++ CODE',len(code),
              'x86',len(ins),'physical nonrel',row.get('true_original_nonfield_matching_B','wrong native CODE extent'),flush=True)
    need(len(rows)==7,'F818 seven original full function variants incomplete')
    (OUT/'verified-summary.json').write_text(json.dumps({
        'original_Japanese_PE_Scene_destructor':'0x0043B0B0',
        'native_original_entire_callable_CODE_B':248,
        'native_original_75_x86':True,
        'true_native_PE_COFF_fields':12,
        'three_typed_borrowed_views_generate_identical_entire_CODE':True,
        'native_original_nonrelocation_byte_match_best':'191/200',
        'borrowed_pointer_or_reference_changes_real_CODE_to_254B_77x86':True,
        'native_original_five_real_texture_free_slots_unrecovered':True,
        'variants':rows,'accepted_new_authored_exact_CODE_B':0,
        'all_979_unit_cold_replay_run':False
    },indent=2)+chr(10))
    print('F818 seven complete 248B authored Scene source probes: all uninstantiated typed owner views produce identical real 248B/75-x86/12 native-PE-field COFF and 191/200 nonrel bytes, while used named borrowed pointer/ref emits nonnative 254B/77-x86. No exact whole game credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F818 original full Scene borrowed owner proof FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
