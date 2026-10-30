#!/usr/bin/env python3
"""F798: native whole ArchiveCatalog loop resource/receiver/filename owners.

Only genuinely used local members (index, filename, resource and actual
delete receiver), never a fake stack filler. Fresh pinned VC7.1 C++
complete 171B function alternatives; physical original PE/COFF fields
fully checked for same-size variants. Intentional 183B source negatives
checked as whole source rather than cropped byte-exact comparisons.
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
OUT=ROOT/'.analysis/f798-archive-teardown-scratch'
ADDRESS=0x0041CE50
SIZE=171
SYM='??1ArchiveCatalogF343@@QAE@XZ'
BODY='''        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);
        }'''

def need(ok,why):
    if not ok:raise ValueError(why)

def load_reader():
    sp=importlib.util.spec_from_file_location('f798_reader',ROOT/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'missing physical original PE reader')
    reader=importlib.util.module_from_spec(sp)
    sys.modules[sp.name]=reader
    sp.loader.exec_module(reader)
    return reader

def make_sources():
    base=(ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
    need(base.count(BODY)==1,'original source-only archive destructor changed')
    variants={'baseline':base}
    for name,fields in [('index-first','unsigned int index;char* filename;'),
                        ('filename-first','char* filename;unsigned int index;')]:
        declaration='struct ArchiveLoopF798 { '+fields+' };\n'
        body=('''        ArchiveLoopF798 state;
        for (state.index=0; state.index<g_ArchiveNamesAt0068BE1C.Size(); ++state.index) {
            delete *g_ArchiveResourcesAt0068BE08.At(state.index);
            state.filename=*g_ArchiveNamesAt0068BE1C.At(state.index);
            free(state.filename);
        }''')
        variants[name]=base.replace('extern unsigned int g_ArchiveUseCountAt0068BE04;',
             declaration+'extern unsigned int g_ArchiveUseCountAt0068BE04;').replace(BODY,body)
    fields={'f':'char* filename;','r':'ArchiveResourceF343* resource;',
            'd':'ArchiveResourceF343* deleteReceiver;','i':'unsigned int index;'}
    for order in ('frdi','fdri','rfdi'):
        declaration='struct ArchiveScratchF798 {'+' '.join(fields[c] for c in order)+'};\n'
        for mode in ('assign-then-delete','inline-assign-delete'):
            delete=('''            state.resource=*g_ArchiveResourcesAt0068BE08.At(state.index);
            state.deleteReceiver=state.resource;
            delete state.deleteReceiver;''' if mode=='assign-then-delete' else
             '''            state.resource=*g_ArchiveResourcesAt0068BE08.At(state.index);
            delete (state.deleteReceiver=state.resource);''')
            body=('''        ArchiveScratchF798 state;
        for (state.index=0; state.index<g_ArchiveNamesAt0068BE1C.Size(); ++state.index) {
'''+delete+'''
            state.filename=*g_ArchiveNamesAt0068BE1C.At(state.index);
            free(state.filename);
        }''')
            variants[order+'-'+mode]=base.replace(
                'extern unsigned int g_ArchiveUseCountAt0068BE04;',
                declaration+'extern unsigned int g_ArchiveUseCountAt0068BE04;').replace(BODY,body)
    need(len(variants)==9,'expected nine natural original archive whole function sources')
    return variants

def main():
    rd=load_reader()
    pe=rd.verified_target()
    original=rd.pe_bytes_at(pe,ADDRESS,SIZE)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    native=list(decoder.disasm(original,ADDRESS))
    need(len(native)==51 and sum(i.size for i in native)==SIZE
         and native[-1].mnemonic=='ret'
         and [native[j].op_str for j in (2,3,8,22,24,38)]==
         ['esp, 0x18','dword ptr [ebp - 0x14], ecx','dword ptr [ebp - 4], 0',
          'dword ptr [ebp - 0xc], eax','dword ptr [ebp - 8], ecx',
          'dword ptr [ebp - 0x10], eax'],
         'original physical ArchiveCatalog whole native frame/slots differ')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    baseline_fields=None
    for name,source in make_sources().items():
        cpp=OUT/(name+'.cpp')
        obj=OUT/(name+'.obj')
        cpp.write_text(source)
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        (OUT/(name+'.log')).write_text(result.stdout+result.stderr)
        need(result.returncode==0,
             'original archive native compiler failed '+name+': '+(result.stdout+result.stderr)[-500:])
        code,refs=rd.object_function(obj,SYM)
        inst=list(decoder.disasm(code,0))
        need(sum(i.size for i in inst)==len(code) and len(refs)==14,
             'native original archive full CODE/COFF reference extent changed '+name)
        current_symbols=[(r['type'],r['symbol'],r['addend'],r['local_symbol_offset']) for r in refs]
        if baseline_fields is None:
            baseline_fields=current_symbols
        need(current_symbols==baseline_fields,'archive full source real native API call sequence changed '+name)
        row={'variant':name,'original_entire_CODE_B':SIZE,
             'source_entire_CODE_B':len(code),
             'original_x86':51,'source_x86':len(inst),
             'actual_compiler_COFF_references':len(refs),
             'real_native_index_slot':'EBP-4',
             'source_native_slot_ordinals':{str(k):inst[k].op_str for k in (2,3,8,22,24,38)}}
        if len(code)==SIZE:
            need(len(inst)==51,'same-length source changed instruction count unexpectedly')
            comparison=rd.compare(obj,SYM,ADDRESS,SIZE)
            expected=102 if name=='index-first' else 108
            need(comparison['result']=='mismatch'
                 and comparison['matched_comparable_bytes']==expected
                 and comparison['comparable_bytes']==115
                 and len(comparison['relocations'])==14
                 and all(int(r['object_addend'],16)==0 for r in comparison['relocations']),
                 'native original full same-length archive PE/COFF evidence changed '+name)
            row['actual_original_nonrelocated_matching_B']=expected
            row['actual_original_nonrelocated_total_B']=115
            row['all_14_original_PE_call_destinations_verified']=True
        else:
            need(len(code)==183 and len(inst)==55 and inst[2].op_str=='esp, 0x20'
                 and inst[3].op_str=='dword ptr [ebp - 0x1c], ecx',
                 'complete used 4-value candidate did not generate honest extra original stack operations '+name)
            row['original_native_length_mismatch_B']=12
            row['not_exact_due_to_four_additional_copy_instructions']=True
            if name.startswith('frdi'):
                need(inst[8].op_str=='dword ptr [ebp - 4], 0'
                     and inst[22].op_str=='dword ptr [ebp - 0xc], eax'
                     and inst[24].op_str=='dword ptr [ebp - 8], ecx'
                     and inst[42].op_str=='dword ptr [ebp - 0x10], edx',
                     'actual native four-slot loop context source not physically verified')
                row['first_four_original_index_resource_receiver_filename_EBP_slots_matching']=True
                row['extra_four_original_position_COPY_instructions']=[25,26,27,28]
        rows.append(row)
        print('F798 '+name+': whole C++ '+str(len(code))+'/'+str(SIZE)+'B, '
              +str(len(inst))+' x86, native 14 original-shaped fields'
              +(f', nonfield {row["actual_original_nonrelocated_matching_B"]}/115' if len(code)==SIZE else
                ', native stack-slot prefix restored but 12 extra original CODE bytes'),
              flush=True)
    need(len(rows)==9 and sum('actual_original_nonrelocated_matching_B' in r for r in rows)==3,
         'nine real source controls not all independently audited')
    report={'original_target_address':'0x0041CE50',
            'original_native_complete_CODE_B':171,
            'original_native_x86':51,
            'original_native_physical_PEs':14,
            'native_original_resource_slot':'EBP-0xC',
            'native_original_delete_slot':'EBP-0x8',
            'native_original_filename_slot':'EBP-0x10',
            'native_original_index_slot':'EBP-0x4',
            'four_used_local_context_can_recover_all_four_original_slots':True,
            'but_real_four_copy_extra_instructions_make_it_nonexact':True,
            'complete_source_variants':rows,
            'new_formal_authored_exact_CODE_B':0,
            'full_unit_cold_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F798 original complete 171B/51-x86 ArchiveCatalog: 4-live-value natural C++ grouping restores four EBP member slots but emits 183B/55-x86 and changes actual frame. No fake exact/game credit or global replay.',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F798 true ArchiveCatalog physical-PE research FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
