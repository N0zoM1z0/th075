#!/usr/bin/env python3
"""F828: 15 full VC7.1 original ArchiveCatalog destructor source storage controls.

Only actual used loop index & filename locals: register, volatile,
different original-compatible 32-bit types, pointer cv qualification
and postincrement/reversed unsigned comparison. Verify full native
171B/51 x86, 14 REAL original PE/COFF fields and all matching
nonrelocation bytes; no cropped deletes or filler locals.
C++ register/volatile/const and equivalent 32-bit index types all
emit identical 171B source; reversed source comparison emits 2
different machine bytes and is worse. No authored exact unit/cold replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f828-archive-storage-types'
SYM='??1ArchiveCatalogF343@@QAE@XZ'
ADDR=0x0041CE50
SIZE=171

def need(x,msg):
    if not x:raise ValueError(msg)

def load():
    sp=importlib.util.spec_from_file_location('archive_f828_rd',R/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'native PE/COFF reader missing')
    rd=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=rd
    sp.loader.exec_module(rd)
    return rd

def variants():
    base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
    index='for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index)'
    filename='char* filename = *g_ArchiveNamesAt0068BE1C.At(index);'
    need(base.count(index)==base.count(filename)==1 and
         base.count('delete *g_ArchiveResourcesAt0068BE08.At(index);')==1
         and base.count('free(filename);')==1,
         'real native Archive full source/lifetime changed')
    out={'baseline':base}
    for name,typ in (
        ('register-index','register unsigned int'),
        ('volatile-index','volatile unsigned int'),
        ('unsigned-long-index','unsigned long'),
        ('unsigned-int32-index','unsigned __int32')):
        out[name]=base.replace(index,index.replace('unsigned int index',typ+' index'),1)
    for name,decl,free in (
        ('register-filename','register char* filename','free(filename);'),
        ('volatile-filename','char* volatile filename','free(filename);'),
        ('const-pointer-filename','char* const filename','free(filename);'),
        ('const-pointee-filename','const char* filename','free(const_cast<char*>(filename));'),
        ('volatile-pointee-filename','volatile char* filename','free(const_cast<char*>(filename));')):
        src=base.replace(filename,decl+' = *g_ArchiveNamesAt0068BE1C.At(index);',1)
        if name in ('const-pointee-filename','volatile-pointee-filename'):
            src=src.replace('free(filename);',free,1)
        out[name]=src
    both=base.replace(index,index.replace('unsigned int index','register unsigned int index'),1)
    both=both.replace(filename,'register char* filename = *g_ArchiveNamesAt0068BE1C.At(index);',1)
    out['register-both']=both
    both=base.replace(index,index.replace('unsigned int index','volatile unsigned int index'),1)
    both=both.replace(filename,'char* volatile filename = *g_ArchiveNamesAt0068BE1C.At(index);',1)
    out['volatile-both']=both
    out['post-increment']=base.replace('++index)','index++)',1)
    out['reversed-unsigned-comparison']=base.replace(
        'index<g_ArchiveNamesAt0068BE1C.Size()',
        'g_ArchiveNamesAt0068BE1C.Size()>index',1)
    out['reversed-comparison-and-postincrement']=out['reversed-unsigned-comparison'].replace(
        '++index)','index++)',1)
    need(len(out)==15,'F828 full physical original used-local source variants missing')
    return out

def compile_full(label,src):
    O.mkdir(parents=True,exist_ok=True)
    cpp=O/(label+'.cpp')
    obj=O/(label+'.obj')
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
       cwd=R,env=env,text=True,capture_output=True,timeout=215)
    (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'F828 original complete ArchiveCatalog source failed '+label+' '+(cp.stdout+cp.stderr)[-700:])
    return obj

def main():
    rd=load()
    pe=rd.verified_target()
    native=rd.pe_bytes_at(pe,ADDR,SIZE)
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    n=list(d.disasm(native,ADDR))
    need(len(n)==51 and sum(x.size for x in n)==SIZE and n[-1].mnemonic=='ret'
         and [n[i].op_str for i in (2,3,8,22,24,38)]==[
          'esp, 0x18','dword ptr [ebp - 0x14], ecx',
          'dword ptr [ebp - 4], 0','dword ptr [ebp - 0xc], eax',
          'dword ptr [ebp - 8], ecx','dword ptr [ebp - 0x10], eax'],
         'original full native Archive stack/whole ABI changed')
    rows=[]
    original_symbols=None
    baseline_bytes=None
    baseline_fields=None
    for label,src in variants().items():
        obj=compile_full(label,src)
        code,refs=rd.object_function(obj,SYM)
        ins=list(d.disasm(code,0))
        need(len(code)==SIZE and len(ins)==51 and len(refs)==14
             and sum(x.size for x in ins)==SIZE and ins[-1].mnemonic=='ret',
             'candidate source no longer original-size whole destructor '+label)
        result=rd.compare(obj,SYM,ADDR,SIZE)
        expected=(106 if label.startswith('reversed') else 108)
        need(result['result']=='mismatch' and
             result['comparable_bytes']==115 and
             result['matched_comparable_bytes']==expected and
             len(result['relocations'])==14 and
             all(int(x['object_addend'],16)==0 for x in result['relocations']),
             'original real native PE COFF-target/data comparison differs '+label)
        fields=[(r['offset'],r['type'],r['symbol'],r['addend'],r['local_symbol_offset']) for r in refs]
        actual_symbols=[(x['offset'],x['type'],x['solved_destination']) for x in result['relocations']]
        if original_symbols is None:
            original_symbols=actual_symbols
            baseline_bytes=code
            baseline_fields=fields
        need(fields==baseline_fields and actual_symbols==original_symbols,
             'changed 32-bit local syntax moved an original physical PE/COFF field '+label)
        if not label.startswith('reversed'):
            need(code==baseline_bytes,'actual storage-class variant changes whole source machine CODE '+label)
        else:
            need(code!=baseline_bytes,'reversed source operand-order should emit genuine byte negatives')
        need([ins[i].op_str for i in (8,22,24,38)]==[
             'dword ptr [ebp - 4], 0',
             'dword ptr [ebp - 0x10], eax',
             'dword ptr [ebp - 0xc], ecx',
             'dword ptr [ebp - 8], eax'],
             'actual three stack temporary slots unintentionally moved '+label)
        rows.append({'variant':label,'full_original_native_B':171,
            'compiler_whole_CODE_B':171,'native_x86':51,'source_x86':51,
            'real_typed_physical_original_PE_fields':14,
            'native_nonrelocation_comparable_B':115,
            'native_nonrelocation_matching_B':expected,
            'entire_generated_CODE_equal_to_baseline':code==baseline_bytes,
            'source_register_resource_EBP':'-0x10',
            'source_scalar_delete_receiver_EBP':'-0x0C',
            'source_filename_EBP':'-0x08',
            'original_register_resource_EBP':'-0x0C',
            'original_delete_receiver_EBP':'-0x08',
            'original_filename_EBP':'-0x10',
            'whole_original_game_function_exact':False})
        print('F828',label,'whole 171/171B 51/51-x86, 14 real original PE fields, native nonfield',expected,'/115, still NONEXACT',flush=True)
    need(len(rows)==15 and sum(r['native_nonrelocation_matching_B']==108 for r in rows)==13,
         'F828 fifteen actual full original source controls incomplete')
    report={'original_complete_game_function':'0x0041CE50',
        'original_full_CODE_B':171,'native_original_x86':51,
        'native_real_PE_fields':14,
        'natural_source_variants':rows,
        'storage_cv_and_equivalent_32bit_local_types_same_entire_generated_CODE':True,
        'reversed_unsigned_comparison_changed_exactly_two_original_nonfield_bytes':True,
        'original_stack_owner_order_still_NONEXACT':True,
        'newly_accepted_authored_whole_CODE_B':0,
        'full_979_unit_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F828 15 complete native Archive destructor whole C++ source controls: 13 compiler-byte-identical 171B/51-x86/14-PE-field COFF, 108/115 native nonfield; reversed unsigned condition lowers to 106/115. True original resource/delete/filename EBP permutation remains wrong. NO formal exact.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F828 original whole archive storage control FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
