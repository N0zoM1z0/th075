"""F906 pinpoint first original whole-fighter GPR allocation divergence at action59.

33 complete normal VC7.1 C++ real stage3 actor float/short,
getter, movement and 2x FTOL2 value-category alternatives.
Whole fighter original 46755B/13230x86 vs selected 46754B;
GPR roles match first 2103 whole native x86, then first wrong
register operand at physical game 0x59 0052327A. All 16
real original PE call/global fields independently checked.
No source reduces case native19 wrong GPR roles or whole2736,
and replacing genuinely used local reference adds real code,
so no separate case or whole native exact credit.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json,collections,re
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f906-fighter-first-gpr'
O.mkdir(parents=True,exist_ok=True)
prior=R/'.analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp'
receipt=R/'.analysis/f901-fighter-31b/verified-summary.json'
if not prior.exists() or not receipt.exists():
 cp=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-tail31b-31c-f901.py')],
       cwd=R,capture_output=True,text=True,timeout=1700)
 (O/'previous-f901-native.log').write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-720:]
j=json.loads(receipt.read_text())
assert j['current_entire_normal_compiler_CODE_B']==46754
assert j['entire_original_callable_giant_exact'] is False
base=prior.read_text()
fragment=(R/'probes/FighterScriptedBounce59F813.inc').read_text()
mark='#include "FighterScriptedBounce59F813.inc"'
assert base.count(mark)==1 and fragment.count('case 0x59:')==1
variants={'baseline':fragment}
patterns=[
('float30-plus-assign','F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;',
                       'F32(0x30)+=g_F728_RandomOffsetYAt00657858;'),
('float54-minus-assign','POS54=POS54-POS5C;','POS54-=POS5C;'),
('contact-order','POS54+POS48<=g_ThresholdAt0065782C','POS48+POS54<=g_ThresholdAt0065782C'),
('contact-strict-inverse','POS54+POS48<=g_ThresholdAt0065782C','!(POS54+POS48>g_ThresholdAt0065782C)'),
('contact-ge-comparison','POS54+POS48<=g_ThresholdAt0065782C','g_ThresholdAt0065782C>=POS54+POS48'),
('contact-typed-float','POS54+POS48<=g_ThresholdAt0065782C',
                       'F32(0x54)+F32(0x48)<=g_ThresholdAt0065782C'),
('contact-typed-double','POS54+POS48<=g_ThresholdAt0065782C',
                        'static_cast<double>(POS54+POS48)<=g_ThresholdAt0065782C'),
('stage3-left','S16(0x62)==3','3==S16(0x62)'),
('stage3-negative','S16(0x62)==3','!(S16(0x62)!=3)'),
('stage3-cast','S16(0x62)==3','static_cast<signed short>(S16(0x62))==3'),
('stage3-int','S16(0x62)==3','static_cast<int>(S16(0x62))==3'),
('stage3-direct','S16(0x62)==3','(*reinterpret_cast<signed short*>(RAW+0x62))==3'),
('native-getter-invert','GetNativeActionAt40FA30()==S16(0x70)',
                        'S16(0x70)==GetNativeActionAt40FA30()'),
('frame0-negate','S16(0x64)==0','!S16(0x64)'),
('frame0-left','S16(0x64)==0','0==S16(0x64)'),
('f00-int-cast','static_cast<float>(static_cast<int>(S16(0xF00)))','static_cast<float>(S16(0xF00))'),
('f02-int-cast','static_cast<float>(-static_cast<int>(S16(0xF02)))','-static_cast<float>(S16(0xF02))'),
('f02-plus-minus','-static_cast<int>(S16(0xF02))','0-static_cast<int>(S16(0xF02))'),
('float30-access','F32(0x30)','(*reinterpret_cast<float*>(RAW+0x30))'),
('float54-access','POS54','F32(0x54)'),
('float5c-access','POS5C','F32(0x5C)'),
('float48-access','POS48','F32(0x48)'),
('f00-signed-short','S16(0xF00)','(*reinterpret_cast<const signed short*>(RAW+0xF00))'),
('f02-signed-short','S16(0xF02)','(*reinterpret_cast<const signed short*>(RAW+0xF02))'),
('bounceX-float-lvalue','POS=static_cast<float>(static_cast<int>(S16(0xF00)))',
                       'F32(0x50)=static_cast<float>(static_cast<int>(S16(0xF00)))'),
('motion-state-float','SetMotionStateAt40FBB0(0,95.0f,0)','SetMotionStateAt40FBB0(0,float(95),0)')
]
for label,original,changed in patterns:
 assert original in fragment,(label,original)
 variants[label]=fragment.replace(original,changed,1)
# Only the REAL read values may be const. Do not make the
# original current actor short F00/F02 assignment itself const.
# The original short F00/F02 values are also WRITTEN by the
# stage3 source; these real const controls qualify only the
# READ operand, never the required actual C++ assignment.
variants['f00-signed-short']=fragment.replace(
 'static_cast<int>(S16(0xF00))',
 'static_cast<int>(*reinterpret_cast<const signed short*>(RAW+0xF00))',1)
variants['f02-signed-short']=fragment.replace(
 'static_cast<int>(S16(0xF02))',
 'static_cast<int>(*reinterpret_cast<const signed short*>(RAW+0xF02))',1)
# Two actual original game boolean paths both changed in a meaningful
# C++ expression; may rotate compiler register phase without extra locals.
for name,tags in (('both-float-plus-minus',('float30-plus-assign','float54-minus-assign')),
                  ('both-stage-frame','stage3-left frame0-left'.split()),
                  ('both-conversion','f00-int-cast f02-int-cast'.split()),
                  ('both-float-xaccess','float54-access float5c-access'.split()),
                  ('both-stage-and-sub','stage3-left float54-minus-assign'.split())):
 if isinstance(tags,str):tags=(tags,)
 candidate=fragment
 for t in tags:
  p=next((before,after) for label,before,after in patterns if label==t)
  candidate=candidate.replace(*p,1)
 variants[name]=candidate
# Reuse genuinely used float lvalue in real POS54 computation without
# fake allocation. Compiler may materialize an actual additional copy.
line='                POS54=POS54-POS5C;'
assert fragment.count(line)==1
variants['actual-live-pos54-ref']=fragment.replace(line,
  '                float& vertical=POS54;\n                vertical=vertical-POS5C;',1)
# Normal compiler args must be pinned as in original F901.
sp=importlib.util.spec_from_file_location('f906rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
pe=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
N=list(D.disasm(rd.pe_bytes_at(pe,0x5214b0,46755),0x5214b0))
native_59=list(D.disasm(rd.pe_bytes_at(pe,0x52327a,356),0x52327a))
assert len(N)==13230 and len(native_59)==95
idx=next(i for i,x in enumerate(N) if x.address==0x52327a)
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[];profiles=collections.Counter()
for tag,inc in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj')
 cpp.write_text(base.replace(mark,inc,1))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
     cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':tag,'compiler_failure':(cp.stdout+cp.stderr)[-330:]}
  rows.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 row={'variant':tag,'whole_source_CODE_B':ret,'whole_source_x86':len(I),
      'COFF_fields':len(refs),'afterRET_DATA_B':len(code)-ret}
 if len(I)==13230:
  cur=I[idx:idx+95];lo,hi=cur[0].address,cur[-1].address+cur[-1].size
  f=[r for r in refs if lo<=r['offset']<hi]
  badreg=sum(tuple(rx.findall(n.op_str))!=tuple(rx.findall(s.op_str)) for n,s in zip(native_59,cur))
  wrong_w=[j for j,(a,b) in enumerate(zip(native_59,cur)) if a.size!=b.size]
  wrong_m=[j for j,(a,b) in enumerate(zip(native_59,cur)) if a.mnemonic!=b.mnemonic]
  # Count GPR divergence in entire original 46755B parent,
  # not just the cropped 95-source-unit trial.
  whole_badreg=sum(tuple(rx.findall(n.op_str))!=tuple(rx.findall(s.op_str))
        for n,s in zip(N,I))
  row.update({'case_59_source_B':hi-lo,'native_case_59_B':356,
              'case_native_x86':95,'case_source_x86':len(cur),
              'case_59_actual_PE_fields':len(f),
              'case_59_native_GPR_operand_differences':badreg,
              'whole_parent_native_GPR_operand_differences':whole_badreg,
              'native_case_59_wrong_width_ordinals':wrong_w,
              'native_case_59_wrong_mnemonic_ordinals':wrong_m})
 profiles[(ret,len(I),hi-lo,badreg,whole_badreg,
           tuple(wrong_m[:8]),tuple(wrong_w[:8]))]+=1
 rows.append(row);print(json.dumps(row),flush=True)
(O/'research-summary.json').write_text(json.dumps(rows,indent=2)+'\n')
print('F906 first native GPR divergence mode59 original 356B/95x86/16 PE; full selected sources',len(rows),
      'quality profiles',dict((str(k),v) for k,v in profiles.items()))

assert len(rows)==len(variants)==33
assert all('compiler_failure' not in row for row in rows)
shapes=collections.Counter((row['whole_source_CODE_B'],row['whole_source_x86']) for row in rows)
assert shapes=={(46754,13230):29,(46756,13231):2,
                (46755,13232):1,(46767,13233):1}
assert all(row['COFF_fields']==1491 and row['afterRET_DATA_B']==901 for row in rows)
shape=[row for row in rows if row['whole_source_x86']==13230]
assert len(shape)==29 and all(row['case_59_source_B']==356
        and row['case_59_actual_PE_fields']==16 for row in shape)
assert min(row['case_59_native_GPR_operand_differences'] for row in shape)==19
assert min(row['whole_parent_native_GPR_operand_differences'] for row in shape)==2736
basecase=next(row for row in rows if row['variant']=='baseline')
assert basecase['case_59_native_GPR_operand_differences']==19
assert basecase['whole_parent_native_GPR_operand_differences']==2736
assert basecase['native_case_59_wrong_mnemonic_ordinals']==[]
assert basecase['native_case_59_wrong_width_ordinals']==[]
# Verify the FIRST GPR divergence belongs to the native physical
# action0x59 at ordinal2103: 2103 original register expressions
# preceding it are EXACT, independent of absolute native jump
# displacements or source-COFF relocation field encoding.
raw=rd.pe_bytes_at(pe,0x5214b0,46755)
Nwhole=list(D.disasm(raw,0x5214b0))
baseline_code,baseline_refs=rd.object_function(
     O/'baseline.obj','?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
source_ins=[]
for x in D.disasm(baseline_code,0):
    source_ins.append(x)
    if x.mnemonic=='ret':break
assert len(source_ins)==len(Nwhole)==13230
regwrong=[j for j,(a,b) in enumerate(zip(Nwhole,source_ins))
          if tuple(rx.findall(a.op_str))!=tuple(rx.findall(b.op_str))]
assert len(regwrong)==2736 and regwrong[0]==idx==2103
assert Nwhole[idx].address==0x52327a
# Native action0x59 physical PE reference field offsets and
# exact game call/global targets, including both original
# real x87 __ftol2 helper calls at native 006406AC.
native_case=rd.pe_bytes_at(pe,0x52327a,356)
sec=source_ins[idx:idx+95]
lo,hi=sec[0].address,sec[-1].address+sec[-1].size
assert hi-lo==356 and len(sec)==len(native_59)==95
native_fields=[r for r in baseline_refs if lo<=r['offset']<hi]
assert len(native_fields)==16
typed=[]
for r in native_fields:
    off=r['offset']-lo
    ordinal=next(j for j,x in enumerate(sec)
                 if x.address<=r['offset']<x.address+x.size)
    n=native_59[ordinal]
    native_off=n.address-0x52327a+n.size-4
    assert off==native_off and r['addend']==0
    assert r['local_symbol_offset'] is None
    assert r['type'] in ('DIR32','REL32')
    match=re.search(r'At([0-9a-fA-F]{6,8})',r['symbol'])
    expected=(int(match.group(1),16) if match else
              0x6406AC if r['symbol']=='__ftol2' else None)
    assert expected is not None
    op=int.from_bytes(native_case[native_off:native_off+4],
          'little',signed=r['type']=='REL32')
    real_target=n.address+n.size+op if r['type']=='REL32' else op
    assert real_target==expected,(ordinal,hex(real_target),hex(expected))
    typed.append({'native_x86_ordinal':ordinal,'original_PE_field_offset':off,
                  'original_actual_target':hex(real_target),
                  'source_COFF_symbol':r['symbol']})
assert len(typed)==16
(O/'verified-summary.json').write_text(json.dumps({
  'original_whole_fighter':'0x005214B0',
  'native_original_whole_callable_CODE_B':46755,
  'source_current_whole_CODE_B':46754,
  'native_and_generated_whole_x86':13230,
  'first_native_register_role_error_whole_x86_ordinal':2103,
  'first_native_register_role_error_physical_original_PE':'0x0052327A',
  'first_GPR_error_action':'0x59',
  'whole_native_GPR_register_role_wrong_instructions':2736,
  'native_0x59_entire_inner_original_CODE_B':356,
  'native_0x59_complete_x86':95,
  'native_0x59_real_original_PE_fields':16,
  'native_0x59_fully_physically_verified_PE_destinations':typed,
  'source_0x59_native_GPR_wrong_instructions':19,
  'original_mode59_all_opcode_mnemonic_widths_match_in_baseline':True,
  'normal_full_VC71_real_Cpp_source_variants':33,
  'full_source_count_at_original_13230_x86':29,
  'source_variants_that_improve_original_native_GPR_match':0,
  'original_last_46B_getter_native_exact_not_implied':True,
  'not_accepting_early_2103_opcode_roles_as_whole_function':True,
  'whole_original_callable_fighter_exact':False,
  'new_accepted_original_whole_callable_CODE_B':0,
  'mass_cold_replay':False,
  'real_complete_source_profiles':rows
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['whole_original_callable_fighter_exact'] is False
print('F906 first original whole fighter GPR divergence at 0x52327A action59 x86 ordinal2103; preceding 2103 register-operand roles match. Native 59 full 356B/95x86/16 original PE fields physically exact targets incl two __ftol2 calls. Thirty-three entire normal VC7.1 C++ float/status/motion source variants: best case 19 GPR wrong instructions, whole 2736 GPR wrong, none improved; four additional whole x86 not cropped. Giant original 46755B still NONEXACT, no mass replay.')
