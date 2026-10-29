"""F632: complete authored destructor source assignment-lifetime control.

Selected new whole-scene/whole-archive C++ source gets freshly compiled
with original VC7.1 /GX vs /GX- and compared to entire native PE
248-byte/171-byte functions. 15 genuine pointer-ownership AST source
alternatives all remain nonexact; all compiler-global/CRT COFF fields
stay real. No fake local, asm, byte graft, accepted new match unit or
943-unit all-unit cold replay.
"""
from pathlib import Path
import argparse
import os,sys,json,importlib.util,subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f632-real-free-assignment/verified';O.mkdir(parents=True,exist_ok=True)
source_archive=(R/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text();source_scene=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
old_archive='''            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);
            free(filename);'''
assert source_archive.count(old_archive)==1
original_expr='*g_ArchiveNamesAt0068BE1C.At(index)'
variants=[]
for tag,new in {
 'archive-ptr-in-free-arg':f'            char* filename;\n            free(filename = {original_expr});',
 'archive-ptr-arg-comma':f'            char* filename;\n            free((filename = {original_expr}, filename));',
 'archive-ptr-after-comma':f'            char* filename;\n            (filename = {original_expr}, free(filename));',
 'archive-ptr-discard-assign':f'            char* filename;\n            (void)(filename = {original_expr});\n            free(filename);',
 'archive-ptr-cast-assignment':f'            char* filename;\n            free(static_cast<void*>(filename = {original_expr}));',
 'archive-ptr-incremented-identity':f'            char* filename;\n            free(*(&(filename = {original_expr})));',
 'archive-void-in-free-arg':f'            void* filename;\n            free(filename = {original_expr});',
 'archive-const-ptr-assigned':f'            char* const filename = {original_expr};\n            free(filename);',
}.items():variants.append((tag,source_archive.replace(old_archive,new),0x0041CE50,171,'??1ArchiveCatalogF343@@QAE@XZ','/GX-'))
base_old='    CleanupPointersF215 released;'
need_fields=[('digitAtlas','0x4c'),('firstCombo','0x50'),('secondCombo','0x54')]
for tag,expression in {
 'scene-three-assignment-args':'free(released.{n} = FIELD(void*,{off}));',
 'scene-three-comma-args':'free((released.{n} = FIELD(void*,{off}), released.{n}));',
 'scene-three-cast-assignment':'free(static_cast<void*>(released.{n} = FIELD(void*,{off})));',
 'scene-three-identity-assignment':'free(*(&(released.{n} = FIELD(void*,{off}))));',
}.items():
 src=source_scene
 for name,offset in need_fields:
  old=f'''        released.{name} = FIELD(void*,{offset});
        free(released.{name});'''
  assert src.count(old)==1
  src=src.replace(old,'        '+expression.format(n=name,off=offset))
 variants.append((tag,src,0x0043B0B0,248,'??1BattleSceneF200@@UAE@XZ','/GX'))
for tag,expr in {
 'scene-three-local-free-assignment':'free({n} = FIELD(void*,{off}));',
 'scene-three-local-comma-assignment':'free(({n} = FIELD(void*,{off}),{n}));',
 'scene-three-local-cast-assignment':'free(static_cast<void*>({n} = FIELD(void*,{off})));',
}.items():
 src=source_scene.replace(base_old,'    void* digitAtlas; void* firstCombo; void* secondCombo;')
 for name,offset in need_fields:
  old=f'''        released.{name} = FIELD(void*,{offset});
        free(released.{name});'''
  assert src.count(old)==1
  src=src.replace(old,'        '+expr.format(n=name,off=offset))
 variants.append((tag,src,0x0043B0B0,248,'??1BattleSceneF200@@UAE@XZ','/GX'))
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--case',choices=sorted(x[0] for x in variants),
                    help='compile and compare ONLY this original complete destructor source alternative')
opts=parser.parse_args()
if opts.case:
    variants=[x for x in variants if x[0]==opts.case]
sp=importlib.util.spec_from_file_location('f632_reader',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd);pe=rd.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None);env['WINEPREFIX']=str(R/'.analysis/vc71-wine');env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,src,addr,size,symbol,gx in variants:
 cpp=O/(tag+'.cpp');obj=cpp.with_suffix('.obj');cpp.write_text(src)
 cp=subprocess.run(['scripts/compile-probe.sh',str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-',gx,'/GS','/Zi'],cwd=R,env=env,capture_output=True,text=True,timeout=180)
 cpp.with_suffix('.log').write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print('F632',tag,'compiler negative',cp.stderr[-200:],flush=True);continue
 code,refs=rd.object_function(obj,symbol)
 compare=subprocess.run(['scripts/repo-python','scripts/compare-coff-function.py',str(obj),symbol,hex(addr),str(size),'--json'],cwd=R,capture_output=True,text=True,timeout=160)
 if not compare.stdout.strip():print(tag,'COMPARATOR ERROR',compare.stderr[-200:]);continue
 data=json.loads(compare.stdout);cpp.with_suffix('.json').write_text(compare.stdout)
 native=list(decoder.disasm(rd.pe_bytes_at(pe,addr,size),addr));generated=list(decoder.disasm(code,0))
 expected_x86=51 if addr==0x0041CE50 else 75
 expected_COFF=14 if addr==0x0041CE50 else 12
 expected_matched=(108 if addr==0x0041CE50 else
                   189 if tag.startswith('scene-three-local-') else 191)
 expected_comparable=115 if addr==0x0041CE50 else 200
 if not (len(native)==len(generated)==expected_x86
         and len(code)==size
         and len(refs)==expected_COFF
         and data['result']=='mismatch'
         and data['matched_comparable_bytes']==expected_matched
         and data['comparable_bytes']==expected_comparable):
    raise ValueError(tag+': actual whole original PE/VC7.1 x86/COFF/stack-byte diagnosis changed; re-evaluate native proof')
 slots=[(i,generated[i].op_str if i<len(generated) else '?') for i in ((22,24,38) if addr==0x41ce50 else (26,28,42,52,62))]
 row={'variant':tag,'original_complete_native_CODE_bytes':size,'source_whole_CODE_bytes':len(code),'original_complete_x86_roles':len(native),'source_full_x86':len(generated),'genuine_source_COFF_fields':len(refs),'original_PE_whole_result':data['result'],'original_nonfield_equal':data.get('matched_comparable_bytes'),'original_nonfield_comparable':data.get('comparable_bytes'),'source_real_stack_owner_ordinals':slots,'accepted_exact':False};rows.append(row)
 print('F632',tag,'native',size,len(native),'source',len(code),len(generated),'COFF',len(refs),'result',data['result'],'nonfield',row['original_nonfield_equal'],'/',row['original_nonfield_comparable'],'slots',slots,flush=True)
receipt=(O/('summary.json' if not opts.case else f'summary-{opts.case}.json'))
receipt.write_text(json.dumps(rows,indent=2)+'\n')
print(f'F632 {len(rows)} whole original authored destructor source hypotheses, all definitively NONEXACT; '
      'zero new accepted whole CODE, no all-unit cold replay.',flush=True)
