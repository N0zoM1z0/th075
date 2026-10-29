"""F612: native complete 248-byte SceneObject virtual destructor type controls.

Use original Japanese TH075 1.11 native PE, one fresh selected natural C++
source translation unit (--case), or 22 affected small variants; no full
943-unit cold replay. Assert source is nonexact: scene resource lifetime
and original five EBP temporary ownership are still unproven.
"""
from pathlib import Path
import argparse
import csv
import sys,os,json,importlib.util,subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f612-scene-types';O.mkdir(parents=True,exist_ok=True);base=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text();reader_path=R/'scripts/compare-coff-function.py';sp=importlib.util.spec_from_file_location('r612',reader_path);m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m);pe=m.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
old='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
assert base.count(old)==1
variants={}
for name,type_name,free_type in [
 ('voidptr','void*',''),
 ('charptr','char*',''),
 ('ucharptr','unsigned char*',''),
 ('signedcharptr','signed char*',''),
 ('wordptr','unsigned short*',''),
 ('int-pointer','int*',''),
 ('unsignedint','unsigned int','CAST'),
 ('ulong-value','unsigned long','CAST'),
 ('constvoid','const void*','CONST'),
 ('constchar','const char*','CONST'),
 ('constvolatilevoid','const volatile void*','CV'),
 ('constvolatilechar','const volatile char*','CV'),
 ('volatilevoid','volatile void*','VOL'),
 ('structsingle','void*',''),
]:
 src=base
 if name=='structsingle':
  src=src.replace(old,'''struct CleanupPointerF612 { void* pointer; };
struct CleanupPointersF215 {
 CleanupPointerF612 digitAtlas;
 CleanupPointerF612 firstCombo;
 CleanupPointerF612 secondCombo;
};''')
  for field in ('digitAtlas','firstCombo','secondCombo'):
   src=src.replace(f'released.{field}',f'released.{field}.pointer')
 else:
  src=src.replace(old,'struct CleanupPointersF215 {\n'+''.join(f'    {type_name} {field};\n' for field in ('digitAtlas','firstCombo','secondCombo'))+'};')
  if type_name != 'void*':
   for field,off in [('digitAtlas','0x4c'),('firstCombo','0x50'),('secondCombo','0x54')]:
    src=src.replace(f'released.{field} = FIELD(void*,{off});',f'released.{field} = reinterpret_cast<{type_name}>(FIELD(void*,{off}));')
    original=f'free(released.{field});'
    if free_type=='CAST':src=src.replace(original,f'free(reinterpret_cast<void*>(released.{field}));')
    elif free_type=='CONST':src=src.replace(original,f'free(const_cast<void*>(reinterpret_cast<const void*>(released.{field})));')
    elif free_type=='CV':src=src.replace(original,f'free(const_cast<void*>(reinterpret_cast<const volatile void*>(released.{field})));')
    elif free_type=='VOL':src=src.replace(original,f'free(const_cast<void*>(reinterpret_cast<const volatile void*>(released.{field})));')
 variants[name]=src
# Additional actual native source syntax controls, not invented unused locals.
array=base.replace(old,'struct CleanupPointersF215 { void* freed[3]; };')
for i,f in enumerate(('digitAtlas','firstCombo','secondCombo')):array=array.replace(f'released.{f}',f'released.freed[{i}]')
variants['array-three']=array
for order in ((0,2,1),(1,0,2),(1,2,0),(2,0,1),(2,1,0)):
 src=array
 for name,idx in zip(('digitAtlas','firstCombo','secondCombo'),order):
  src=src.replace(f'released.freed[{("digitAtlas","firstCombo","secondCombo").index(name)}]',f'released.X{idx}')
 for idx in range(3):src=src.replace(f'released.X{idx}',f'released.freed[{idx}]')
 variants['array-order-'+''.join(map(str,order))]=src
# Nontrivial meaningful C++ pointer alias types: pointer values still free via same CRT.
for name,decl in [('referenceptr','void*&'),('constreferenceptr','void* const&')]:
 src=base.replace(old,'')
 src=src.replace('    CleanupPointersF215 released;','')
 for field,off in [('digitAtlas','0x4c'),('firstCombo','0x50'),('secondCombo','0x54')]:
  src=src.replace(f'released.{field} = FIELD(void*,{off});',f'{decl} {field} = FIELD(void*,{off});')
  src=src.replace(f'free(released.{field});',f'free({field});')
 variants[name]=src
native=list(d.disasm(m.pe_bytes_at(pe,0x0043B0B0,248),0x0043B0B0))
assert len(native)==75 and sum(x.size for x in native)==248
assert [native[i].op_str for i in (26,28,42,52,62)]==[
    'dword ptr [ebp - 0x14], edx',
    'dword ptr [ebp - 0x10], eax',
    'dword ptr [ebp - 0x18], eax',
    'dword ptr [ebp - 0x1c], ecx',
    'dword ptr [ebp - 0x20], edx']
with (R/'config/function-origins.csv').open(newline='') as file:
    origin={line['address']:line for line in csv.DictReader(file)}
assert origin['0x0043B0B0']['origin']=='authored'
cli=argparse.ArgumentParser(description=__doc__)
cli.add_argument('--case',choices=sorted(variants),help='compile exactly one selected 248-byte source type/array control')
opt=cli.parse_args()
if opt.case:variants={opt.case:variants[opt.case]}
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for name,src in variants.items():
    cpp=O/(name+'.cpp');obj=cpp.with_suffix('.obj');cpp.write_text(src)
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=env,
        text=True,capture_output=True,timeout=160)
    cpp.with_suffix('.log').write_text(run.stdout+run.stderr)
    if run.returncode:raise ValueError(name+': original VC7.1 selected compilation failed: '+run.stderr[-400:])
    code,refs=m.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
    ins=list(d.disasm(code,0))
    proc=subprocess.run([str(R/'scripts/repo-python'),str(reader_path),str(obj),
        '??1BattleSceneF200@@UAE@XZ','0x0043B0B0','248','--json'],
        cwd=R,text=True,capture_output=True,timeout=120)
    if not proc.stdout.strip():raise ValueError(name+': original PE complete-function comparator returned no result')
    result=json.loads(proc.stdout)
    cpp.with_suffix('.json').write_text(proc.stdout)
    is_reference=name.endswith('referenceptr')
    expected_size=254 if is_reference else 248
    expected_x86=78 if is_reference else 75
    if not (len(code)==expected_size and len(ins)==expected_x86
            and len(refs)==12
            and (is_reference or len(result['relocations'])==12)
            and result['result']==('size-mismatch' if is_reference else 'mismatch')):
        raise ValueError(name+': full original 248B CODE/native x86/12 original COFF fields changed')
    if not is_reference:
        expected_match=189 if name in ('array-order-102','array-order-120',
                                      'array-order-201','array-order-210') else 191
        if not (result['matched_comparable_bytes']==expected_match
                and result['comparable_bytes']==200
                and [ins[i].op_str for i in (26,28)]==[
                    'dword ptr [ebp - 0x20], edx',
                    'dword ptr [ebp - 0x1c], eax']):
            raise ValueError(name+': actual scene EBP native texture/delete locals or original byte comparison changed')
    row={'variant':name,'native_full_CODE_bytes':248,
         'generated_full_CODE_bytes':len(code),'generated_full_x86':len(ins),
         'physical_typed_COFF_refs':len(refs),'original_PE_whole_comparison':result['result'],
         'original_nonfield_byte_match':result.get('matched_comparable_bytes'),
         'original_nonfield_byte_total':result.get('comparable_bytes'),
         'original_EBP_texture_delete_slots':['-0x14','-0x10'],
         'generated_EBP_texture_delete_slots':['-0x20','-0x1C'] if not is_reference else 'reference expression adds extra instructions',
         'accepted_whole_game_CODE_bytes':0}
    rows.append(row)
    print(f'F612 {name}: generated {len(code)} B/{len(ins)} x86, '
          f'{result["result"]} against original whole 248B/75 native x86; '
          f'{result.get("matched_comparable_bytes")}/200 CODE nonfields, 12 genuine COFF',flush=True)
(O/('summary.json' if not opt.case else f'summary-{opt.case}.json')).write_text(json.dumps(rows,indent=2)+'\n')
print(f'F612: {len(rows)} full selected original SceneObject destructor '
      'source controls; all nonexact, no new authored CODE, no all-unit cold replay.',flush=True)
