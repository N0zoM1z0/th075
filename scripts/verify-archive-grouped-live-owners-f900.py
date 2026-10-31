"""F900 full original Archive destructor, true used resource/filename grouped locals.

Twenty-five entire pinned VC7.1 /Od /GX- authored destructor
source variants: real resource+filename pair, three-field loop
index/resource/filename aggregate order, one-element owner,
union reusing sequentially deleted resource/free filename,
pointer-to-pointer list entry and true two-value expression forms.
All perform real list At, delete, filename CRT free and both Clears.
Twenty-three truly owned real source variants generate 177B/53x86;
baseline 171B/51x86/14 PE fields matches 108/115 original
nonrelocation bytes, filename-only matches 102/115.
No compiled 177B function is cropped to claim exact native CODE.
"""
from pathlib import Path
import itertools,importlib.util,sys,os,json,subprocess,collections
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f900-archive-grouped-locals';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
old='''        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            delete *g_ArchiveResourcesAt0068BE08.At(index);
            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);
        }'''
assert base.count(old)==1
anchor='extern unsigned int g_ArchiveUseCountAt0068BE04;'
assert base.count(anchor)==1
cases={'baseline':base}
fields={'r':'ArchiveResourceF343* resource;', 'f':'char* filename;', 'i':'unsigned int index;', 'e':'ArchiveResourceF343** entry;'}
def source(tag,types,body,placement='before-loop',kind='struct'):
    header=kind+' ArchiveLiveF900 {'+' '.join(fields[t] for t in types)+'};\n'
    src=base.replace(anchor,header+anchor,1)
    if placement=='before-loop':
        body='        ArchiveLiveF900 state;\n'+body
    elif placement=='before-guard':
        assert src.count('    if (--g_ArchiveUseCountAt0068BE04 == 0) {')==1
        src=src.replace('    if (--g_ArchiveUseCountAt0068BE04 == 0) {',
           '    ArchiveLiveF900 state;\n    if (--g_ArchiveUseCountAt0068BE04 == 0) {',1)
    else:raise ValueError(placement)
    assert src.count(old)==1
    cases[tag]=src.replace(old,body,1)
def loopbody(index,first,second):
    return (f'''        for ({'state.index=0' if index=='state.index' else 'unsigned int index=0'};
             {index}<g_ArchiveNamesAt0068BE1C.Size(); ++{index}) {{
            {first}
            {second}
        }}''')
# One real struct field only, actual used as actual delete or CRT free parameter.
source('resource-only','r',loopbody('index',
     'state.resource=*g_ArchiveResourcesAt0068BE08.At(index);\n            delete state.resource;',
     'char* filename=*g_ArchiveNamesAt0068BE1C.At(index);\n            free(filename);'))
source('filename-only','f',loopbody('index',
     'delete *g_ArchiveResourcesAt0068BE08.At(index);',
     'state.filename=*g_ArchiveNamesAt0068BE1C.At(index);\n            free(state.filename);'))
# Two real live resource/name pointers within the SAME aggregate; no dummy fields.
for order in ('rf','fr'):
 for place in ('before-loop','before-guard'):
    body=loopbody('index',
        'state.resource=*g_ArchiveResourcesAt0068BE08.At(index);\n            delete state.resource;',
        'state.filename=*g_ArchiveNamesAt0068BE1C.At(index);\n            free(state.filename);')
    source('pair-'+order+'-'+place,order,body,place)
 for mode in ('assign-delete','delete-lvalue','delete-cast'):
    rfirst=('delete (state.resource=*g_ArchiveResourcesAt0068BE08.At(index));'
             if mode=='assign-delete' else
             'state.resource=*g_ArchiveResourcesAt0068BE08.At(index);\n            delete (state.resource);' if mode=='delete-lvalue' else
             'state.resource=*g_ArchiveResourcesAt0068BE08.At(index);\n            delete static_cast<ArchiveResourceF343*&>(state.resource);')
    body=loopbody('index',rfirst,
           'state.filename=*g_ArchiveNamesAt0068BE1C.At(index);\n            free(state.filename);')
    source('pair-'+order+'-'+mode,order,body)
# All THREE actually-used index/resource/name fields, reorders in six source layouts.
for order in ('rfi','rif','fri','fir','irf','ifr'):
    body=loopbody('state.index',
        'state.resource=*g_ArchiveResourcesAt0068BE08.At(state.index);\n            delete state.resource;',
        'state.filename=*g_ArchiveNamesAt0068BE1C.At(state.index);\n            free(state.filename);')
    source('triple-'+order,order,body)
# A real char* name and resource* only occupy the same source lifetime sequentially.
# A C++ union may be reused because resource is already deleted before filename is read.
for order in ('rf','fr'):
 body=loopbody('index',
     'state.resource=*g_ArchiveResourcesAt0068BE08.At(index);\n            delete state.resource;',
     'state.filename=*g_ArchiveNamesAt0068BE1C.At(index);\n            free(state.filename);')
 source('union-'+order,order,body,kind='union')
# Group real first list-entry (pointer-to-pointer) and filename in struct or union.
for order in ('ef','fe'):
 body=loopbody('index',
     'state.entry=g_ArchiveResourcesAt0068BE08.At(index);\n            delete *state.entry;',
     'state.filename=*g_ArchiveNamesAt0068BE1C.At(index);\n            free(state.filename);')
 source('entry-'+order,order,body)
# A two-member actually-used aggregate for filename & saved loop index with real resource
# as named local; creates a genuinely changed lifetime from F798.
for order in ('fi','if'):
 body=loopbody('state.index',
       'ArchiveResourceF343* resource=*g_ArchiveResourcesAt0068BE08.At(state.index);\n            delete resource;',
       'state.filename=*g_ArchiveNamesAt0068BE1C.At(state.index);\n            free(state.filename);')
 source('filename-index-named-resource-'+order,order,body)
sp=importlib.util.spec_from_file_location('f900rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
pe=rd.verified_target();raw=rd.pe_bytes_at(pe,0x41ce50,171);d=Cs(CS_ARCH_X86,CS_MODE_32);native=list(d.disasm(raw,0x41ce50))
assert len(native)==51 and len(raw)==171
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[];counters=collections.Counter();symbols=None
for tag,src in cases.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
       cwd=R,env=E,capture_output=True,text=True,timeout=210)
 (O/(tag+'.log')).write_text(p.stdout+p.stderr)
 if p.returncode:
    row={'variant':tag,'compile_failed':(p.stdout+p.stderr)[-390:]}
    rows.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'??1ArchiveCatalogF343@@QAE@XZ')
 ins=list(d.disasm(code,0))
 current_symbols=sorted((r['type'],r['symbol'],r['addend']) for r in refs)
 if symbols is None:symbols=current_symbols
 assert current_symbols==symbols and len(refs)==14 and all(r['addend']==0 for r in refs), (
    'original archive native list/delete/free/clear API call identities changed',tag)
 row={'variant':tag,'whole_source_CODE_B':len(code),'native_CODE_B':171,
      'whole_source_x86':len(ins),'native_x86':51,'source_PE_fields':len(refs),
      'source_stack_22_24_38':[ins[i].op_str for i in (22,24,38)] if len(ins)>38 else []}
 if len(code)==171 and len(ins)==51 and len(refs)==14:
    result=rd.compare(obj,'??1ArchiveCatalogF343@@QAE@XZ',0x41ce50,171)
    row['native_nonrelocation_equal_B']=result['matched_comparable_bytes']
    row['original_nonrelocation_comparable_B']=result['comparable_bytes']
    row['all_original_14_physical_PE_fields_aligned']=len(result['relocations'])==14 and all(
       int(r['object_addend'],16)==0 for r in result['relocations'])
    row['mnemonics_and_width_original']=all(a.mnemonic==b.mnemonic and a.size==b.size
                                           for a,b in zip(native,ins))
 else:
    row['size_not_original_native']=True
 rows.append(row)
 counters[(len(code),len(ins),len(refs),row.get('native_nonrelocation_equal_B'))]+=1
 print(json.dumps(row),flush=True)
(O/'research-summary.json').write_text(json.dumps(rows,indent=2)+'\n')
print('F900 REAL source variants',len(rows),'complete sizes',dict((str(k),v) for k,v in counters.items()))

assert len(rows)==25
assert all('compile_failed' not in x for x in rows)
assert rows[0]['variant']=='baseline'
assert rows[0]['whole_source_CODE_B']==171
assert rows[0]['whole_source_x86']==51
assert rows[0]['native_nonrelocation_equal_B']==108
assert len([r for r in rows if r['whole_source_CODE_B']==171])==2
assert len([r for r in rows if r['whole_source_CODE_B']==177])==23
assert len([r for r in rows if r['whole_source_x86']==53])==23
assert all(r['source_PE_fields']==14 for r in rows)
same={r['variant']:r for r in rows if r['whole_source_CODE_B']==171}
assert set(same)=={'baseline','filename-only'}
assert same['filename-only']['native_nonrelocation_equal_B']==102
assert all(r['all_original_14_physical_PE_fields_aligned'] and
           r['mnemonics_and_width_original'] and
           r['original_nonrelocation_comparable_B']==115
           for r in same.values())
# Original code actually stores resource -C / delete receiver -8 /
# filename -10; the same-size C++ source still stores resource -10 /
# receiver -C and filename -8 (baseline) or index -4 (one-field source).
assert rows[0]['source_stack_22_24_38']==[
 'dword ptr [ebp - 0x10], eax','dword ptr [ebp - 0xc], ecx','dword ptr [ebp - 8], eax']
assert same['filename-only']['source_stack_22_24_38']==[
 'dword ptr [ebp - 0x10], eax','dword ptr [ebp - 0xc], ecx','dword ptr [ebp - 4], eax']
(O/'verified-summary.json').write_text(json.dumps({
 'real_original_whole_callable_function':'0x0041CE50',
 'original_native_complete_CODE_B':171,
 'original_native_complete_x86':51,
 'original_actual_physically_typed_PE_fields':14,
 'actual_complete_real_live_source_variants':len(rows),
 'real_grouped_resource_filename_owner_variants':23,
 'wrong_size_grouped_entire_source_CODE_B':177,
 'wrong_size_grouped_entire_source_x86':53,
 'real_natively_sized_but_nonexact_source_models':2,
 'native_baseline_nonrelocation_equality':'108/115',
 'native_one_actual_filename_aggregate_equality':'102/115',
 'all_original_real_list_delete_free_clear_call_symbols_unchanged':True,
 'original_real_resource_EBP':'-0xC',
 'original_real_delete_receiver_EBP':'-0x8',
 'original_real_filename_EBP':'-0x10',
 'native_171B_resource_and_deleter_still_different':True,
 'whole_original_game_function_exact':False,
 'accepted_new_authored_whole_callable_CODE_B':0,
 'mass_cold_replay':False,
 'whole_generated_source_variants':rows
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['whole_original_game_function_exact'] is False
print('F900 Archive original authored whole 171B/51x86/14 real PE fields; 25 normal full VC7.1 source variants, 23 actually used grouped resource/filename/index/union/entry owners emit WRONG complete 177B/53x86. Baseline 108/115 native nonfield, single filename context 102/115, neither exact. No truncated CODE or mass cold replay.')
