#!/usr/bin/env python3
"""F937: strict native 0x58 x86 and next 0x59 GPR tradeoff in whole 58KB fathers.

Seven genuine normal VC7.1 whole-parent source controls. Recheck
original 469B native predecessor and 356B native follower,
typed PE target fields and the separate full 943B jump data.
Negative source analysis, not independent internal case acceptance.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,sys,subprocess,re,hashlib
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f937-strict-predecessor-controls';OUT.mkdir(parents=True,exist_ok=True)
SYMBOL='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
def load(name,file):
 sp=importlib.util.spec_from_file_location(name,ROOT/file)
 m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m)
 return m
f781=load('f937781','scripts/verify-fighter-shared-getter-f781.py')
f778=load('f937778','scripts/verify-fighter-native-default-f778.py')
f759=load('f937759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=load('f937762','scripts/verify-fighter-typed-returns-f762.py')
f734=load('f937734','scripts/verify-fighter-eight-round-f734.py')
f777=load('f937777','scripts/verify-fighter-current-register-phases-f777.py')
rd=load('f937reader','scripts/compare-coff-function.py')
source,boss=f781.source_for_whole_parent(f778,f759,f762)
for name in ('FighterEarlyPairF722.inc','FighterFollowupBurstF724.inc'):
 needle='#include "'+name+'"'
 assert source.count(needle)==1
 source=source.replace(needle,(ROOT/'probes'/name).read_text(),1)
for distance in (20,46):
 needle=f'float(*reinterpret_cast<signed char*>(RAW+0x66)*-{distance})+F32(0x44)'
 replacement=(f'reinterpret_cast<FighterProjectileXViewF917*>(this)->'
    f'coordinateXAt44-float(*reinterpret_cast<signed char*>(RAW+0x66)*{distance})')
 assert source.count(needle)==2
 source=source.replace(needle,replacement)
source='#include "FighterProjectileXViewF917.hpp"\n'+source
mark='#include "FighterTrajectoryBurst58F614.inc"'
fragment=(ROOT/'probes/FighterTrajectoryBurst58F614.inc').read_text()
assert source.count(mark)==1
loop='for (int burst=0;burst<10;++burst)\n            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'
assert fragment.count(loop)==1
call='SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'
variants={
 'native-strict-baseline':loop,
 'native-strict-add-one':loop.replace('++burst','burst+=1'),
 'native-strict-reverse-test':loop.replace('burst<10','10>burst'),
 'native-strict-X-const':loop.replace(call,call.replace('I32(0x44)',
          '*reinterpret_cast<const int*>(RAW+0x44)'),1),
 'native-strict-Y-const':loop.replace(call,call.replace('I32(0x48)',
          '*reinterpret_cast<const int*>(RAW+0x48)'),1),
 'native-strict-void-call':loop.replace(call,'(void)'+call),
 'native-different-le-nine':loop.replace('burst<10','burst<=9'),
}
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
native=list(D.disasm(rd.pe_bytes_at(PE,0x543210,58294),0x543210))
assert len(native)==16471
start58=next(i for i,x in enumerate(native) if x.address==0x544f34)
start59=next(i for i,x in enumerate(native) if x.address==0x545109)
assert (start58,start59)==(2063,2198)
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results=[];ref_base=None
for name,case in variants.items():
 cpp,obj=OUT/(name+'.cpp'),OUT/(name+'.obj')
 cpp.write_text(source.replace(mark,fragment.replace(loop,case,1),1))
 cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
    cwd=ROOT,env=E,capture_output=True,text=True,timeout=325)
 (OUT/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,SYMBOL)
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 length=I[-1].address+I[-1].size
 assert (length,len(I),len(refs),len(code)-length)==(58293,16471,1863,943)
 mapping=f734.source_map_from_original_afterRET(rd,PE,boss,code,I,refs)
 first,last=mapping[0x544f34],mapping[0x545109]
 assert (first,last-first)==(I[start58].address,469)
 assert len([x for x in I if first<=x.address<last])==135
 native58=native[start58:start59];source58=I[start58:start59]
 bad_mn=[j for j,(a,b) in enumerate(zip(native58,source58)) if a.mnemonic!=b.mnemonic]
 bad_w=[j for j,(a,b) in enumerate(zip(native58,source58)) if a.size!=b.size]
 bad_gpr=[j for j,(a,b) in enumerate(zip(native58,source58)) if roles(a)!=roles(b)]
 source59=I[start59:start59+95]
 bad59=[j for j,(a,b) in enumerate(zip(native[start59:start59+95],source59)) if roles(a)!=roles(b)]
 assert len(source59)==95 and len(bad59)==19
 record59=f777.physical_whole_case(rd,PE,D,code,refs,I,mapping,0x59,f777.ORIGINAL[0x59])
 assert record59['actual_original_nonfield_operand_byte_mismatches']==19
 if not bad_mn and not bad_w and not bad_gpr:
  case58=f777.physical_whole_case(rd,PE,D,code,refs,I,mapping,0x58,f777.ORIGINAL[0x58])
  assert case58['native_zero_addend_typed_PE_COFF_fields_checked']==17
  assert case58['actual_original_nonfield_operand_byte_mismatches']==0
 else:
  assert name=='native-different-le-nine' and bad_mn==[60] and not bad_w and not bad_gpr
 f759.check_afterret(rd,PE,D,boss,code,refs,I)
 # Source symbols may have differing temporary local names; physical
 # external COFF site count and afterRET bytes are stable.
 assert len([r for r in refs if first<=r['offset']<last])==17
 result={'variant':name,'whole_source_CODE_B':length,'whole_source_x86':len(I),
   'native_0x58_mnemonic_wrong_ordinals':bad_mn,
   'native_0x58_width_wrong_ordinals':bad_w,
   'native_0x58_GPR_wrong_ordinals':bad_gpr,
   'native_0x59_GPR_wrong_ordinals':bad59,
   'native_0x59_physically_verified_PE_COFF_fields':16,
   'native_0x59_other_nonfield_byte_differences':19,
   'complete_afterRET_DATA_B':943,'whole_GAME_exact':False}
 results.append(result)
 print(name,'0x58 wrong mnemonic',len(bad_mn),'width',len(bad_w),'GPR',len(bad_gpr),
       '0x59 GPR wrong',len(bad59),flush=True)
strict=[x for x in results if not x['native_0x58_mnemonic_wrong_ordinals']
       and not x['native_0x58_width_wrong_ordinals']
       and not x['native_0x58_GPR_wrong_ordinals']]
assert len(strict)==6 and all(len(x['native_0x59_GPR_wrong_ordinals'])==19 for x in strict)
assert len(results)==7
(OUT/'verified-summary.json').write_text(json.dumps({
  'original_Japanese_fighter':'0x00543210','original_callable_CODE_B':58294,
  'original_native_x86':16471,'original_afterRET_DATA_B':943,
  'complete_source_Cpp_controls':len(results),
  'true_native_0x58_MNEM_WIDTH_GPR_strict_controls':len(strict),
  'recovered_0x59_GPR_with_both_0x58_strict':0,
  'prior_49_entire_source_variants_saved_ignored':True,
  'new_accepted_original_CODE_B':0,'whole_game_exact':False,
  'mass_cold_replay':False,'native_original_control_rows':results
},indent=2)+'\n')
print('F937: six full 58KB VC7.1 native-strict 0x58 controls all retain 19 wrong 0x59 register roles; 17+16 physical fields, 943B original afterRET verified. No whole exact credit.')
