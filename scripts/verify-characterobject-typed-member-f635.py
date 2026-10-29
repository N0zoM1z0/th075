"""F635: native whole 33,293-byte authored giant float-member type negatives.

Only cold compile selected 004EBDA0 whole C++ TU (--case) or the 25
actual affected C++ type/ownership variants (--all). Original 8,789
CODE x86, 438 separately owned afterRET DATA bytes and 682 truly
typed PE/COFF fields are always compared. The original 137 non-COFF
byte register cycle is nonexact in all variants (two worsen to 140).
Do not invent local padding, asm, synthetic source or whole-function
exact credit; never run the full 943 accepted-unit cold replay.
"""
from pathlib import Path
import argparse
import importlib.util,sys,os,subprocess,json,collections
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];OUT=R/'.analysis/f635-main-giant-type-ownership/verified';base=(R/'probes/CharacterObjectActionsF572.cpp').read_text()
sp=importlib.util.spec_from_file_location('r635',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd);pe=rd.verified_target();native=rd.pe_bytes_at(pe,0x004EBDA0,33731);decoder=Cs(CS_ARCH_X86,CS_MODE_32)
symbol='?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ'
startcase={a:base.index(f'case 0x{a:X}: {{') for a in (0x38D,0x38E,0x3E3,0x3E4)}
def change(which,old,new):
 a=startcase[which];nextcase={0x38D:0x38E,0x38E:0x3E3,0x3E3:0x3E4}[which];z=startcase[nextcase]
 scope=base[a:z];assert scope.count(old)==1,(which,old,scope.count(old))
 return base[:a]+scope.replace(old,new)+base[z:]
variants={'baseline':base}
for name,case,orig,repl in [
 ('38d-zero-velocity-as-bits',0x38D,'F32(0x54)=0.0f;','I32(0x54)=0;'),
 ('38d-zero-pos-as-bits',0x38D,'F32(0x50)=0.0f;','I32(0x50)=0;'),
 ('38d-alpha-quarter-as-bits',0x38D,'F32(0x1C)=0.25f;','I32(0x1C)=0x3E800000;'),
 ('38d-alpha-one-as-bits',0x38D,'F32(0x20)=1.0f;','I32(0x20)=0x3F800000;'),
 ('38d-stage4-assign-op',0x38D,'F32(0x1C)=F32(0x1C)*gSubAt00659090;','F32(0x1C)*=gSubAt00659090;'),
 ('38d-stage4-integer-lvalue',0x38D,'F32(0x1C)=F32(0x1C)*gSubAt00659090;','*reinterpret_cast<float*>(RAW+0x1C)=F32(0x1C)*gSubAt00659090;'),
 ('38d-stage4-true-ref-global',0x38D,'F32(0x1C)=F32(0x1C)*gSubAt00659090;','F32(0x1C)=F32(0x1C)* *(&gSubAt00659090);'),
 ('38d-stage4-member-lvalue',0x38D,'F32(0x1C)=F32(0x1C)*gSubAt00659090;','F32(0x1C)=*(&F32(0x1C))*gSubAt00659090;'),
 ('38d-alpha-byte-sign-lvalue',0x38D,'U8(0x11)=0xFF;','S8(0x11)=static_cast<signed char>(-1);'),
 ('38d-stage4-test-unsigned-cast',0x38D,'if (U8(0x11)>=20) {','if (static_cast<unsigned char>(U8(0x11))>=20) {'),
 ('38d-stage4-test-unary-ref',0x38D,'if (U8(0x11)>=20) {','if (*(&U8(0x11))>=20) {'),
 ('38d-stage4-sub-operator',0x38D,'U8(0x11)-=20;','U8(0x11)=static_cast<unsigned char>(U8(0x11)-20);'),
 ('38e-zero-velocity-as-bits',0x38E,'F32(0x54)=0.0f;','I32(0x54)=0;'),
 ('38e-zero-pos-as-bits',0x38E,'F32(0x50)=0.0f;','I32(0x50)=0;'),
 ('38e-alpha-threequarters-as-bits',0x38E,'F32(0x1C)=0.75f;','I32(0x1C)=0x3F400000;'),
 ('38e-alpha-one-as-bits',0x38E,'F32(0x20)=1.0f;','I32(0x20)=0x3F800000;'),
 ('3e3-zero-pos-as-bits',0x3E3,'F32(0x50)=0.0f;','I32(0x50)=0;'),
 ('3e3-minus-one-velocity-as-bits',0x3E3,'F32(0x54)=-1.0f;','I32(0x54)=0xBF800000;'),
 ('3e3-alpha-one-as-bits',0x3E3,'F32(0x1C)=1.0f;','I32(0x1C)=0x3F800000;'),
 ('3e3-second-alpha-one-as-bits',0x3E3,'F32(0x20)=1.0f;','I32(0x20)=0x3F800000;'),
 ('3e3-direction-write-cast',0x3E3,'S8(0x66)=1;','U8(0x66)=1;'),
 ('3e3-float-position-lvalue',0x3E3,'F32(0x50)=0.0f;','*(&F32(0x50))=0.0f;'),
]: variants[name]=change(case,orig,repl)
# Two real simultaneous source-grammar hypotheses, still no fake source state.
s=change(0x38D,'F32(0x54)=0.0f;','I32(0x54)=0;');a=s.index('case 0x38E: {');z=s.index('case 0x3E3: {',a);v=s[a:z];assert v.count('F32(0x54)=0.0f;')==1
variants['both-zero-velocity-bits']=s[:a]+v.replace('F32(0x54)=0.0f;','I32(0x54)=0;')+s[z:]
s=change(0x38D,'F32(0x1C)=0.25f;','I32(0x1C)=0x3E800000;');a=s.index('case 0x38E: {');z=s.index('case 0x3E3: {',a);v=s[a:z];assert v.count('F32(0x1C)=0.75f;')==1
variants['both-alpha-initializers-bits']=s[:a]+v.replace('F32(0x1C)=0.75f;','I32(0x1C)=0x3F400000;')+s[z:]
parser=argparse.ArgumentParser(description=__doc__)
selection=parser.add_mutually_exclusive_group()
selection.add_argument('--case',choices=sorted(variants),default=None,
                       help='compile ONLY one chosen entire original giant C++ source TU')
selection.add_argument('--all',action='store_true',
                       help='compile just these 25 original giant typed-member source experiments')
options=parser.parse_args()
chosen=variants if options.all else {
    (options.case or 'baseline'):variants[(options.case or 'baseline')]}
original_ins=list(decoder.disasm(native[:33293],0))
if len(original_ins)!=8789 or sum(x.size for x in original_ins)!=33293:
    raise ValueError('actual pinned original giant complete 8,789 x86 instructions differ')
OUT.mkdir(parents=True,exist_ok=True)
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None);env['WINEPREFIX']=str(R/'.analysis/vc71-wine');env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows=[]
for name,source in chosen.items():
 cpp=OUT/(name+'.cpp');obj=cpp.with_suffix('.obj');cpp.write_text(source)
 comp=subprocess.run(['scripts/compile-probe.sh',str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=env,capture_output=True,text=True,timeout=180)
 cpp.with_suffix('.log').write_text(comp.stdout+comp.stderr)
 if comp.returncode:raise ValueError(f'{name}: original VC7.1 complete source build failed: {comp.stderr[-350:]}')
 try:code,fields=rd.object_function(obj,symbol)
 except Exception as e:raise ValueError(f'{name}: original whole native source COFF symbol missing: {e}') from e
 orig_ins=[]
 for inst in decoder.disasm(code,0):
  orig_ins.append(inst)
  if inst.mnemonic=='ret':break
 rowslot= {'name':name,'original_total_33731_bytes':33731,'generated_total_bytes':len(code),'generated_whole_CODE_insns':len(orig_ins),'source_COFF_fields':len(fields),'original_whole_author_exact':False}
 if len(code)!=33731 or len(fields)!=682 or len(orig_ins)!=8789:
  raise ValueError(f'{name}: original source actual whole 33,293 CODE +438 DATA, 8,789 x86/682 typed fields changed')
 geometry_errors=[i for i,(a,b) in enumerate(zip(original_ins,orig_ins))
                  if (a.address,a.size)!=(b.address,b.size)]
 mnemonic_errors=[i for i,(a,b) in enumerate(zip(original_ins,orig_ins))
                  if a.mnemonic!=b.mnemonic]
 expected_x86_geometry_errors=([8081,8082]
     if name in ('38d-stage4-assign-op','38d-stage4-member-lvalue') else [])
 if geometry_errors!=expected_x86_geometry_errors:
  raise ValueError(f'{name}: entire original physical x86 geometry differs at {geometry_errors[:6]} vs expected {expected_x86_geometry_errors}')
 rowslot['native_x86_start_width_mismatch_ordinals']=geometry_errors
 rowslot['changed_native_x86_mnemonic_ordinals']=mnemonic_errors
 if name not in ('38d-stage4-assign-op','38d-stage4-member-lvalue') and mnemonic_errors:
  raise ValueError(f'{name}: ordinary equivalent source changed original mnemonics at {mnemonic_errors[:6]}')
 if not all(f['type'] in ('DIR32','REL32') and f['addend']==0 for f in fields):
  raise ValueError(f'{name}: original giant physical COFF source fields are not typed zero addend')
 if not (len([f for f in fields if f['offset']<33293])==622
         and len([f for f in fields if f['offset']>=33293])==60):
  raise ValueError(f'{name}: original separate afterRET dense DATA physical field ownership changed')
 mask={i for f in fields for i in range(f['offset'],f['offset']+4)}
 differences=[i for i in range(33731) if i not in mask and native[i]!=code[i]]
 rowslot.update({'real_nonfield_comparable':33731-len(mask),'real_native_nonfield_difference_bytes':len(differences),'first_original_difference_offsets':differences[:8],'original_8789_x86_source_count_preserved':len(orig_ins)==8789,
                 'original_full_byte_exact':not differences})
 expected=140 if name in ('38d-stage4-assign-op','38d-stage4-member-lvalue') else 137
 if len(differences)!=expected or len(mask)!=2728 or 30381 not in differences:
  raise ValueError(f'{name}: actual original typed whole 33K source mismatch changed: {len(differences)} vs {expected}')
 rows.append(rowslot)
 print('F635',name,'whole original 33,293 CODE +438 afterRET DATA bytes, '
       '8,789/8,789 x86, 682 physical typed zero-addend COFF; '
       f'{len(differences)} original nonrelocation bytes STILL wrong, '
       'whole giant NONEXACT',flush=True)
report=OUT/('summary.json' if options.all else f'summary-{next(iter(chosen))}.json')
report.write_text(json.dumps(rows,indent=2)+'\n')
print(f'F635 {len(rows)} selected whole original 004EBDA0 giant C++ source TUs, '
      'zero new accepted original whole authored functions, NO 943-unit cold replay.',flush=True)
