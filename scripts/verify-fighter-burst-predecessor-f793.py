"""F793: ten full 58KB parents test real action 0x58 -> 0x59 register allocation.

Original 0x58 469 B/135 x86/17 PE fields; original adjacent 0x59
356 B/95 x86/16 PE fields. Whole actual original PE boundaries,
switch DATA and affected source code are compared, not split-case credit.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f793-fighter58-predecessor';O.mkdir(parents=True,exist_ok=True)
def L(tag,f):
 sp=importlib.util.spec_from_file_location(tag,R/f);m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m
f781=L('f793_781','scripts/verify-fighter-shared-getter-f781.py')
f778=L('f793_778','scripts/verify-fighter-native-default-f778.py')
f759=L('f793_759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=L('f793_762','scripts/verify-fighter-typed-returns-f762.py')
f734=L('f793_734','scripts/verify-fighter-eight-round-f734.py')
f777=L('f793_777','scripts/verify-fighter-current-register-phases-f777.py')
rd=L('f793_rd','scripts/compare-coff-function.py')
pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
source,boss=f781.source_for_whole_parent(f778,f759,f762)
frag=Path('probes/FighterTrajectoryBurst58F614.inc').read_text()
assert source.count('#include "FighterTrajectoryBurst58F614.inc"')==1
names={
 'baseline':frag,
 'loop-postincrement':frag.replace('for (int burst=0;burst<10;++burst)','for (int burst=0;burst<10;burst++)'),
 'typed-loop-counter':frag.replace('for (int burst=0;burst<10;++burst)','for (unsigned int burst=0;burst<10;++burst)'),
 'reverse-25-compare':frag.replace('I16(0xEFA)>25','25<I16(0xEFA)'),
 'reverse-position-compare':frag.replace('POS54 + POS48 <= g_ThresholdAt0065782C','g_ThresholdAt0065782C >= POS54 + POS48'),
 'reverse-add-operands':frag.replace('POS54 + POS48 <= g_ThresholdAt0065782C','POS48 + POS54 <= g_ThresholdAt0065782C'),
 'true-bitcopy-used':frag.replace('I32(0x54) = I32(0x98);','*reinterpret_cast<unsigned int*>(RAW+0x54) = *reinterpret_cast<const unsigned int*>(RAW+0x98);'),
 'same-constant-source':frag.replace('POS5C = 0.8f;','*(&POS5C) = 0.8f;'),
 'loop-count-reversed':frag.replace('burst<10','10>burst'),
 'stage-guard-negated':frag.replace('I16(0x62)==0 && I16(0x64)==0','!(I16(0x62)!=0 || I16(0x64)!=0)'),
}
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None);env['WINEPREFIX']=str(R/'.analysis/vc71-wine');env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
N={a:list(d.disasm(rd.pe_bytes_at(pe,a,b-a),a)) for a,b in [(0x544f34,0x545109),(0x545109,0x54526d)]}
rows=[]
assert len(N[0x544f34])==135 and len(N[0x545109])==95
assert len(names)==10
for tag,frag in names.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj')
 cpp.write_text(source.replace('#include "FighterTrajectoryBurst58F614.inc"',frag))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=env,capture_output=True,text=True,timeout=240)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print(tag,'COMPILER FAIL',(cp.stdout+cp.stderr)[-350:],flush=True);continue
 code,refs=rd.object_function(obj,f781.SYM)
 ins=[]
 for x in d.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 end=ins[-1].address+ins[-1].size
 try:
  mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
  assert end==58293 and len(ins)==16471 and len(code)==end+943 and len(refs)==1863
  out={'variant':tag,'entire_SOURCE_CODE_bytes':end,'source_x86':len(ins),'source_COFF_fields':len(refs)}
  for case,lo,hi in [(0x58,0x544f34,0x545109),(0x59,0x545109,0x54526d)]:
   nat=N[lo];src=[x for x in ins if mapping[lo]<=x.address<mapping[hi]]
   field=[r for r in refs if mapping[lo]<=r['offset']<mapping[hi]]
   mask={p for r in field for p in range(r['offset']-mapping[lo],r['offset']-mapping[lo]+4)}
   tails=set()
   for a,b in zip(nat,src):
    if a.mnemonic=='jmp' and a.op_str=='0x5515c2' and a.size==b.size==5 and b.mnemonic=='jmp':
     tails.update(range(a.address-lo+1,a.address-lo+5))
   nbytes=rd.pe_bytes_at(pe,lo,hi-lo)
   wrong=[i for i in range(min(len(nbytes),mapping[hi]-mapping[lo])) if i not in mask and i not in tails and nbytes[i]!=code[mapping[lo]+i]]
   out[f'{case:02x}_CODE']=mapping[hi]-mapping[lo]
   out[f'{case:02x}_x86']=len(src)
   out[f'{case:02x}_relocs']=len(field)
   out[f'{case:02x}_nonfield_other_bad']=len(wrong)
   out[f'{case:02x}_mnemonic_bad']=[j for j,(a,b) in enumerate(zip(nat,src)) if a.mnemonic!=b.mnemonic][:18]
   out[f'{case:02x}_width_bad']=[j for j,(a,b) in enumerate(zip(nat,src)) if a.size!=b.size][:18]
  expected58=2 if tag=='reverse-add-operands' else 1 if tag=='typed-loop-counter' else 0
  assert out['58_CODE']==469 and out['58_x86']==135 and out['58_relocs']==17
  assert out['59_CODE']==356 and out['59_x86']==95 and out['59_relocs']==16
  assert out['58_nonfield_other_bad']==expected58 and out['59_nonfield_other_bad']==19
  assert not out['59_mnemonic_bad'] and not out['59_width_bad']
  # Real signed-to-unsigned loop branch changes one original Jcc;
  # reject that variant without pretending it is native exact.
  if tag=='typed-loop-counter':
   assert out['58_mnemonic_bad']==[60] and out['58_width_bad']==[]
  else:
   expected=(*f777.ORIGINAL[0x58][:5],expected58)
   checked=f777.physical_whole_case(rd,pe,d,code,refs,ins,mapping,0x58,expected)
   assert checked['native_zero_addend_typed_PE_COFF_fields_checked']==17
  checked59=f777.physical_whole_case(rd,pe,d,code,refs,ins,mapping,0x59,f777.ORIGINAL[0x59])
  assert checked59['native_zero_addend_typed_PE_COFF_fields_checked']==16
  if tag=='baseline':
   f781.verify_original_shared_getter(rd,pe,d,code,refs,ins,end)
   for case in (0x60,0x61,0x63):
    f777.physical_whole_case(rd,pe,d,code,refs,ins,mapping,case,f777.ORIGINAL[case])
   f759.check_afterret(rd,pe,d,boss,code,refs,ins)
 except Exception as ex:
  raise ValueError('F793 original whole-parent verification failed for '+tag+': '+str(ex))
 rows.append(out);print(json.dumps(out),flush=True)
assert len(rows)==10
(O/'verified-summary.json').write_text(json.dumps({
 'native_original_fighter_00543210_CODE_B':58294,
 'source_entire_parent_CODE_B':58293,
 'whole_original_and_source_x86':16471,
 'original_058_native_CODE_B':469,
 'original_058_native_x86':135,
 'original_058_real_PE_fields':17,
 'original_059_native_CODE_B':356,
 'original_059_native_x86':95,
 'original_059_real_PE_fields':16,
 'cases':[r for r in rows],
 'remaining_actual_059_GPR_operand_bytes':19,
 'original_and_compiled_943B_afterRET_DATA_independently_rechecked':True,
 'full_giant_byte_exact':False,
 'accepted_callable_CODE_bytes':0,
 'full_cold_unit_replay':False,
},indent=2)+'\n')
print('F793: ten complete affected 58KB parents; original 058 strict except unsigned-loop Jcc/operand-order controls; original 059 remains 19 wrong GPR bytes with all 16 native physical refs. No callable exact credit.',flush=True)
