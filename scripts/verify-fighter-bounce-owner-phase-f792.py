"""F792: 8 whole-fighter VC7.1 actor/source phase probes for action 0x59.

Original native 356B/95 x86/16 typed PE fields. Test meaningful
borrowed actor stage/velocity and native x87 evaluation grammar in
ONE complete 58KB C++ parent per variant; never crop a switch case.
No authored whole CODE credited until independently exact.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f792-fighter59';O.mkdir(parents=True,exist_ok=True)
def load(tag,part):
 spec=importlib.util.spec_from_file_location(tag,R/part);m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m);return m
f781=load('f792_781','scripts/verify-fighter-shared-getter-f781.py')
f778=load('f792_778','scripts/verify-fighter-native-default-f778.py')
f759=load('f792_759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=load('f792_762','scripts/verify-fighter-typed-returns-f762.py')
f734=load('f792_734','scripts/verify-fighter-eight-round-f734.py')
f777=load('f792_777','scripts/verify-fighter-current-register-phases-f777.py')
rd=load('f792_rd','scripts/compare-coff-function.py')
pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
source,boss=f781.source_for_whole_parent(f778,f759,f762)
frag=Path('probes/FighterEarlyBounceTypedF752.inc').read_text()
marker='#include "FighterEarlyBounceTypedF752.inc"'
assert source.count(marker)==1
case='        case 0x59: {'
boundary='        case 0x5D: {'
a=frag.index(case);b=frag.index(boundary)
old=frag[a:b]
assert old.count('S16(0x62)>1')==1
assert old.count('POS54+POS48<=g_ThresholdAt0065782C')==1
assert old.count('F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;')==1
assert old.count('POS54=POS54-POS5C;')==1
variants={
  'baseline':old,
  'stage-leftcompare':old.replace('S16(0x62)>1','1<S16(0x62)'),
  'float-compare-reversed':old.replace('POS54+POS48<=g_ThresholdAt0065782C','g_ThresholdAt0065782C>=POS54+POS48'),
  'float-sum-reorder':old.replace('POS54+POS48<=g_ThresholdAt0065782C','POS48+POS54<=g_ThresholdAt0065782C'),
  'stage-view':old.replace('S16(0x62)>1','reinterpret_cast<const ActorStageBorrowedF792*>(this)->stage>1'),
  'typed-drag':old.replace('POS54=POS54-POS5C;','reinterpret_cast<ActorVelocityBorrowedF792*>(this)->velocity -= reinterpret_cast<const ActorVelocityBorrowedF792*>(this)->drag;'),
  'pre-float-readonly':old.replace('F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;','*(&F32(0x30))=F32(0x30)+g_F728_RandomOffsetYAt00657858;'),
  'short-guard-native':old.replace('S16(0x62)>1','static_cast<int>(S16(0x62))>1'),
}
declare='''struct ActorStageBorrowedF792 { char observed[0x62]; signed short stage; };
struct ActorVelocityBorrowedF792 { char observed[0x54]; float velocity; char actual54To5C[4]; float drag; };
'''
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine');env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
native=list(d.disasm(rd.pe_bytes_at(pe,0x00545109,356),0x00545109))
rows=[]
assert len(native)==95 and sum(i.size for i in native)==356
for tag,casebody in variants.items():
 tu=source.replace(marker,declare+frag[:a]+casebody+frag[b:])
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(tu)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=env,capture_output=True,text=True,timeout=220)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print(tag,'compile FAIL',(cp.stdout+cp.stderr)[-450:],flush=True);continue
 code,refs=rd.object_function(obj,f781.SYM)
 inst=[]
 for i in d.disasm(code,0):
  inst.append(i)
  if i.mnemonic=='ret':break
 ret=inst[-1].address+inst[-1].size
 try:
  mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,inst,refs)
  start,stop=mapping[0x00545109],mapping[0x0054526d]
  now=[x for x in inst if start<=x.address<stop]
  native_case=rd.pe_bytes_at(pe,0x00545109,356)
  fields=[x for x in refs if start<=x['offset']<stop]
  mask={z for f in fields for z in range(f['offset']-start,f['offset']-start+4)}
  tails=set()
  for n,i in zip(native,now):
   if n.mnemonic=='jmp' and n.op_str=='0x5515c2' and n.size==i.size==5 and i.mnemonic=='jmp':
    tails.update(range(n.address-0x00545109+1,n.address-0x00545109+5))
  wrong=[i for i in range(356) if i not in mask and i not in tails and i<stop-start and native_case[i]!=code[start+i]]
  expected=21 if tag=='float-sum-reorder' else 19
  assert ret==58293 and len(inst)==16471 and len(code)==ret+943
  assert stop-start==356 and len(now)==95 and len(fields)==16
  assert len(wrong)==expected and not [i for i,(a,b) in enumerate(zip(native,now)) if a.mnemonic!=b.mnemonic or a.size!=b.size], tag+' original whole action x86 geometry drift'
  layout=(*f777.ORIGINAL[0x59][:5],expected)
  checked=f777.physical_whole_case(rd,pe,d,code,refs,inst,mapping,0x59,layout)
  assert checked['native_zero_addend_typed_PE_COFF_fields_checked']==16
  if tag=='baseline':
   for case in (0x58,0x60,0x61):
    f777.physical_whole_case(rd,pe,d,code,refs,inst,mapping,case,f777.ORIGINAL[case])
   f759.check_afterret(rd,pe,d,boss,code,refs,inst)
   f781.verify_original_shared_getter(rd,pe,d,code,refs,inst,ret)
  row={'variant':tag,'whole_original_source_CODE_B':ret,'case59_B':stop-start,'x86':len(now),
       'real_59_relocs':len(fields),'wrong_nonfield_other_bytes':len(wrong),'wrong_offsets':wrong[:20],
       'opcodes_bad':[i for i,(a,b) in enumerate(zip(native,now)) if a.mnemonic!=b.mnemonic][:20],
       'width_bad':[i for i,(a,b) in enumerate(zip(native,now)) if a.size!=b.size][:20]}
 except Exception as ex:
  expected=21 if tag=='float-sum-reorder' else 19
  assert ret==58293 and len(inst)==16471 and len(code)==ret+943
  assert stop-start==356 and len(now)==95 and len(fields)==16
  assert len(wrong)==expected and not [i for i,(a,b) in enumerate(zip(native,now)) if a.mnemonic!=b.mnemonic or a.size!=b.size], tag+' original whole action x86 geometry drift'
  layout=(*f777.ORIGINAL[0x59][:5],expected)
  checked=f777.physical_whole_case(rd,pe,d,code,refs,inst,mapping,0x59,layout)
  assert checked['native_zero_addend_typed_PE_COFF_fields_checked']==16
  if tag=='baseline':
   for case in (0x58,0x60,0x61):
    f777.physical_whole_case(rd,pe,d,code,refs,inst,mapping,case,f777.ORIGINAL[case])
   f759.check_afterret(rd,pe,d,boss,code,refs,inst)
   f781.verify_original_shared_getter(rd,pe,d,code,refs,inst,ret)
  row={'variant':tag,'whole_original_source_CODE_B':ret,'error':str(ex)[:300]}
 assert 'error' not in row
 rows.append(row);print(json.dumps(row),flush=True)
assert len(rows)==8 and [r['wrong_nonfield_other_bytes'] for r in rows]==[19,19,19,21,19,19,19,19]
(O/'verified-summary.json').write_text(json.dumps({
 'native_complete_game_function':'0x00543210',
 'native_entire_original_CODE_B':58294,
 'generated_best_complete_CODE_B':58293,
 'native_59_original_B':356,
 'native_59_original_instructions':95,
 'true_PE_COFF_original_fields_each_variant':16,
 'all_eight_whole_source_builds_replay_only_affected_parent':True,
 'actual_native_59_register_phase_wrong_bytes':19,
 'variants':rows,
 'whole_game_exact':False,
 'formal_native_authored_CODE_credit':0,
 'full_cold_replay':False,
},indent=2)+'\n')
print('F792: eight full-original-parent 0x59 sourced C++ VC7.1 compiles; baseline 19 wrong genuine GPR bytes, typed/grammar controls retain 19 or regress to 21. All 16 native PE fields checked per case, 943B DATA validated; no game CODE credit.')
