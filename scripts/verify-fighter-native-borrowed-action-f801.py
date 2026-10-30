"""F801: native actor-history/opponent field access in whole 58KB fighter.

Eight FULL current F781 source parents: observed real 0x32A action
history, 0x39D index, 0x2E8 owner pointer and 0x60 stage. Verify
entire generated CODE+943B switch DATA bit-identical, all 1863 COFF
relocation shapes plus independent physical original 0x63 PE calls.
These are observed borrowed views, not historical owner layouts.
Zero whole giant exact credit, no all-unit cold replay.
"""
from pathlib import Path
import importlib.util,sys,os,json,subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];P=R/'.analysis/f801-fighter-borrowed-action';P.mkdir(parents=True,exist_ok=True)
def load(tag,path):
 sp=importlib.util.spec_from_file_location(tag,R/path);m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m
f781=load('f801_781','scripts/verify-fighter-shared-getter-f781.py')
f778=load('f801_778','scripts/verify-fighter-native-default-f778.py')
f759=load('f801_759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=load('f801_762','scripts/verify-fighter-typed-returns-f762.py')
f734=load('f801_734','scripts/verify-fighter-eight-round-f734.py')
f777=load('f801_777','scripts/verify-fighter-current-register-phases-f777.py')
rd=load('f801_rd','scripts/compare-coff-function.py')
pe=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
source,boss=f781.source_for_whole_parent(f778,f759,f762)
frag=Path('probes/FighterMode63BasicF626.inc').read_text()
marker='#include "FighterMode63BasicF626.inc"';assert source.count(marker)==1
views='''struct BorrowedStageF801 { unsigned char unknownBefore60[0x60]; signed short stageAt60; };
struct BorrowedActorStatusF801 { unsigned char unknownBefore39D[0x39D]; signed char indexAt39D; };
struct BorrowedActorHistoryF801 { unsigned char unknownBefore32A[0x32A]; signed char valuesAt32A[8]; };
struct BorrowedOwnerPointerF801 { unsigned char unknownBefore2E8[0x2E8]; BorrowedStageF801* opponentAt2E8; };
'''
raw_stage='*reinterpret_cast<signed short*>(OWNER+0x60)'
raw_array='*reinterpret_cast<signed char*>(RAW+0x32A+\n                *reinterpret_cast<signed char*>(RAW+0x39D))'
raw_flag='*reinterpret_cast<signed char*>(RAW+0x39D)'
assert frag.count(raw_stage)==4 and frag.count(raw_array)==3 and frag.count(raw_flag)==7,(frag.count(raw_array),frag.count(raw_flag))
typed_flag='reinterpret_cast<const BorrowedActorStatusF801*>(this)->indexAt39D'
typed_array='reinterpret_cast<const BorrowedActorHistoryF801*>(this)->valuesAt32A[\n                '+typed_flag+']'
typed_stage='reinterpret_cast<const BorrowedOwnerPointerF801*>(this)->opponentAt2E8->stageAt60'
vars={
 'baseline':frag,
 'history-typed':frag.replace(raw_array,typed_array),
 'flag-typed':frag.replace(raw_flag,typed_flag),
 'history-and-flag':frag.replace(raw_array,typed_array).replace(raw_flag,typed_flag),
 'owner-pointer-typed':frag.replace(raw_stage,typed_stage),
 'owner-and-history':frag.replace(raw_stage,typed_stage).replace(raw_array,typed_array),
 'all-real-borrowed':frag.replace(raw_stage,typed_stage).replace(raw_array,typed_array).replace(raw_flag,typed_flag),
 'history-ref':frag.replace(raw_array,'*(&'+typed_array+')'),
}
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
native=list(D.disasm(rd.pe_bytes_at(pe,0x545ade,706),0x545ade))
rows=[]
baseline_bytes=None
baseline_relocs=None
def normalized(refs):
 return [(r['offset'],r['type'],r['addend'],r['local_symbol_offset'],
          r['symbol'] if r['local_symbol_offset'] is None else '<local-label>')
         for r in refs]
assert len(native)==189 and len(vars)==8
for tag,body in vars.items():
 cpp=P/(tag+'.cpp');obj=P/(tag+'.obj');cpp.write_text(views+source.replace(marker,body))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=260)
 (P/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print(tag,'COMPILE ERROR',(cp.stdout+cp.stderr)[-750:],flush=True);continue
 code,refs=rd.object_function(obj,f781.SYM)
 assert len(code)==59236 and len(refs)==1863, tag+' original full source CODE/DATA or COFF shape drift'
 if baseline_bytes is None:
  baseline_bytes=code
  baseline_relocs=normalized(refs)
 else:
  assert code==baseline_bytes, tag+' has new complete source machine-code differences'
  assert normalized(refs)==baseline_relocs, tag+' changed native physical COFF relocation identity'
 ins=[]
 for i in D.disasm(code,0):
  ins.append(i)
  if i.mnemonic=='ret':break
 ret=ins[-1].address+ins[-1].size
 try:
  mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
  start,end=mapping[0x545ade],mapping[0x545da0]
  local=[i for i in ins if start<=i.address<end]
  width=[j for j,(a,b) in enumerate(zip(native,local)) if a.size!=b.size]
  mnemonic=[j for j,(a,b) in enumerate(zip(native,local)) if a.mnemonic!=b.mnemonic]
  phases=[(j,native[j].op_str,local[j].op_str,native[j].size,local[j].size) for j in (18,38,61,84)]
  assert ret==58293 and len(ins)==16471 and end-start==705 and len(local)==189
  assert width==[18,61,84] and not mnemonic, tag+' real native original 0x63 GPR width controls not preserved'
  verified=f777.physical_whole_case(rd,pe,D,code,refs,ins,mapping,0x63,f777.ORIGINAL[0x63])
  assert verified['native_zero_addend_typed_PE_COFF_fields_checked']==15
  if tag=='baseline':
   f781.verify_original_shared_getter(rd,pe,D,code,refs,ins,ret)
   f759.check_afterret(rd,pe,D,boss,code,refs,ins)
   for case in (0x58,0x59,0x60,0x61):
    f777.physical_whole_case(rd,pe,D,code,refs,ins,mapping,case,f777.ORIGINAL[case])
  row={'variant':tag,'whole_CODE_B':ret,'whole_x86':len(ins),'COFF_fields':len(refs),
       'mode63_CODE_B':end-start,'mode63_x86':len(local),
       'actual_original_CMP_phases':phases,'width_mismatch_ordinals':width[:25],
       'mnemonic_mismatch_ordinals':mnemonic[:25]}
  if (end-start)==706 and len(local)==189 and not mnemonic and not width:
   field=[r for r in refs if start<=r['offset']<end]
   mask={z for r in field for z in range(r['offset']-start,r['offset']-start+4)}
   target=rd.pe_bytes_at(pe,0x545ade,706)
   wrong=[k for k in range(706) if k not in mask and target[k]!=code[start+k]]
   row['physical_nonrelocation_wrong_B']=len(wrong)
 except Exception as exc:row={'variant':tag,'whole_CODE_B':ret,'map_error':str(exc)[:300]}
 assert 'map_error' not in row
 row['original_15_mode63_PE_COFF_fields_verified']=True
 row['entire_native_shaped_59236B_COFF_identical_to_baseline']=True
 rows.append(row);print(json.dumps(row),flush=True)
assert len(rows)==8
(P/'verified-summary.json').write_text(json.dumps({
 'physical_original_pe_start':'0x00543210',
 'entire_original_native_CODE_B':58294,
 'current_generated_parent_CODE_B':58293,
 'original_and_compiled_x86':16471,
 'actual_original_mode63_CODE_B':706,
 'compiled_mode63_CODE_B':705,
 'real_original_wrong_CMP_width_ordinals':[18,61,84],
 'original_target_PE_fields_mode63':15,
 'complete_generated_COFF_records':1863,
 'real_original_afterRET_switch_DATA_B':943,
 'all_eight_entire_59236B_COFF_functions_byte_identical':True,
 'all_eight_COFF_relocation_shapes_identical':True,
 'all_typed_original_mode63_native_PE_fields_rechecked':True,
 'affected_whole_parent_variants':rows,
 'native_giant_entire_byte_exact':False,
 'new_callable_exact_CODE_B':0,
 'all_unit_cold_replay_run':False,
},indent=2)+chr(10))
print('F801 eight COMPLETE fighter parents: all 59236 generated CODE+DATA bytes and 1863 COFF relocation shapes identical; original mode63 15 physical PE calls reviewed, still original 706 vs source 705B and wrong GPR widths 18/61/84. NO accepted giant CODE.',flush=True)
