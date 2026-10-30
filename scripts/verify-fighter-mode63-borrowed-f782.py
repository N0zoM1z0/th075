"""F782: four complete 58KB parent builds disprove simple mode-63 casts.

Probes entire giant, not isolated interiors; no callable CODE credited.
"""
from pathlib import Path
import importlib.util,sys,subprocess,os,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f782-fighter-mode63';O.mkdir(parents=True,exist_ok=True)
def load(tag,file):
 sp=importlib.util.spec_from_file_location(tag,R/file);m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m
f781=load('f782_781','scripts/verify-fighter-shared-getter-f781.py')
f778=load('f782_778','scripts/verify-fighter-native-default-f778.py')
f759=load('f782_759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=load('f782_762','scripts/verify-fighter-typed-returns-f762.py')
f734=load('f782_734','scripts/verify-fighter-eight-round-f734.py')
rd=load('f782_reader','scripts/compare-coff-function.py')
native=rd.pe_bytes_at(rd.verified_target(),0x545ade,706)
source,boss=f781.source_for_whole_parent(f778,f759,f762)
frag=Path('probes/FighterMode63BasicF626.inc').read_text()
marker='#include "FighterMode63BasicF626.inc"'
assert source.count(marker)==1
old_owner='*reinterpret_cast<signed short*>(OWNER+0x60)'
old_actor='*reinterpret_cast<signed char*>(RAW+0x39D)'
assert frag.count(old_owner)==4 and frag.count(old_actor)>=4
decl='struct BorrowedOpponentStageF782 { char observedBeforeStage[0x60]; signed short stage; };\nstruct BorrowedActorStageF782 { char observedBeforeStage[0x39D]; signed char stage; };\n'
variants=[
 ('baseline',frag),
 ('owner-typed',frag.replace(old_owner,'reinterpret_cast<const BorrowedOpponentStageF782*>(OWNER)->stage')),
 ('actor-typed',frag.replace(old_actor,'reinterpret_cast<const BorrowedActorStageF782*>(this)->stage')),
 ('both-typed',frag.replace(old_owner,'reinterpret_cast<const BorrowedOpponentStageF782*>(OWNER)->stage').replace(old_actor,'reinterpret_cast<const BorrowedActorStageF782*>(this)->stage')),
]
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
d=Cs(CS_ARCH_X86,CS_MODE_32)
orig_inst=list(d.disasm(native,0x545ade))
reports=[]
baseline_bytes=None
baseline_rel=None
def normalized(refs):
 return [(r['offset'],r['type'],r['addend'],r['local_symbol_offset'],
          r['symbol'] if r['local_symbol_offset'] is None else '<local-label>')
         for r in refs]
for name,case in variants:
 src=decl+source.replace(marker,case)
 cpp=O/(name+'.cpp');obj=O/(name+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=env,capture_output=True,text=True,timeout=230)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print(name,'compile failure', (cp.stdout+cp.stderr)[-1000:],flush=True);continue
 code,refs=rd.object_function(obj,f781.SYM)
 if baseline_bytes is None:
  baseline_bytes=code
  baseline_rel=normalized(refs)
 else:
  assert code==baseline_bytes, name+' whole-parent generated machine bytes changed'
  assert normalized(refs)==baseline_rel, name+' physical relocation fields changed'
 assert len(code)==59236 and len(refs)==1863, name+' source/data extent drift'
 ins=[]
 for x in d.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 end=ins[-1].address+ins[-1].size
 try:
  mapping=f734.source_map_from_original_afterRET(rd,rd.verified_target(),boss,code,ins,refs)
  current=[i for i in ins if mapping[0x545ade]<=i.address<mapping[0x545da0]]
  cmps=[(j,orig_inst[j].op_str,current[j].op_str,orig_inst[j].size,current[j].size) for j in [18,61,84]] if len(current)>84 else []
  width_bad=[j for j,(a,b) in enumerate(zip(orig_inst,current)) if a.size!=b.size]
  mnemonic_bad=[j for j,(a,b) in enumerate(zip(orig_inst,current)) if a.mnemonic!=b.mnemonic]
  assert end==58293, name+' entire original parent CODE length drift'
  assert mapping[0x545da0]-mapping[0x545ade]==705 and len(current)==189
  assert width_bad==[18,61,84] and not mnemonic_bad, name+' actual original register-width pattern changed'
  result={'variant':name,'whole_code_B':end,'case63_B':mapping[0x545da0]-mapping[0x545ade],
          'case63_x86':len(current),'native_wide_cmp_roles':cmps,'width_bad_ordinals':width_bad[:35],
          'mnemonic_bad_ordinals':mnemonic_bad[:35],
          'first_original_case_vs_source':[(orig_inst[j].op_str,current[j].op_str) for j in range(min(4,len(current)))]}
 except Exception as exc:
  result={'variant':name,'whole_code_B':end,'map_error':str(exc)[:250]}
 reports.append(result)
 print(json.dumps(result,ensure_ascii=False),flush=True)
assert len(reports)==4, 'not all four original whole-parent controls verified'
(O/'verified-summary.json').write_text(json.dumps({
 'original_game_boss':'0x00543210',
 'original_callable_CODE_B':58294,
 'entire_Cpp_parent_CODE_B':58293,
 'native_and_source_x86':16471,
 'all_four_complete_COFF_functions_byte_identical':True,
 'all_four_COFF_relocation_fields_equivalent':True,
 'native_mode63_CODE_B':706,
 'emitted_mode63_CODE_B':705,
 'remaining_real_CMP_width_ordinals':[18,61,84],
 'variants':reports,'accepted_exact_callable_CODE_B':0
},indent=2)+'\n')
print('F782: four complete 58KB parent builds produce identical CODE/DATA and physical relocations; no native register width gain, zero exact credit.',flush=True)
