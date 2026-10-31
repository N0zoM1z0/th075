#!/usr/bin/env python3
"""F957: natural real preceding CA source and following CB GPR-phase controls.

Build nine complete original-shaped partial fighter parents, generated
entirely from tracked F938–F955 natural source, under normal pinned
VC7.1. Read native Japanese 004AC040 original PE to check full
CA 123 and CB 131 instruction roles, real original PE source symbol
targets for ordinal-aligned variants and 151 actual afterRET DIR32
case-label relocations /522 DATA nonfield bytes. Negative evidence,
never accept inner cases or the incomplete 82KB parent as whole exact.
"""
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import importlib.util, json, os, re, sys, subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f957-ca-before-cb';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
members=[
 (0x5D,94,'FighterThirdBossPair5D5EF939.inc'),(0x5E,95,None),
 (0x5F,96,'FighterThirdBossFacing5FF941.inc'),
 (0x60,97,'FighterThirdBossVolley6061F942.inc'),(0x61,98,None),
 (0x62,99,'FighterThirdBossSelector62F943.inc'),
 (0xC8,201,'FighterThirdBossFourWayC8F948.inc'),
 (0xC9,202,'FighterThirdBossFourWayC9F949.inc'),
 (0xCA,203,'FighterThirdBossFourWayCAF950.inc'),
 (0xCB,204,'FighterThirdBossFourWayCBF951.inc'),
 (0xCC,205,'FighterThirdBossCCF953.inc'),
 (0xCD,206,'FighterThirdBossCDF953.inc'),
 (0xCE,207,'FighterThirdBossCEF955.inc'),
 (0xCF,208,'FighterFallStateCFF647.inc'),
 (0xD0,209,'FighterReflectLandingD0F646.inc')]
for action,marker,filename in members:
 old=f'        case 0x{action:X}: g_FighterProbeMarker = {marker}; break;'
 assert base.count(old)==1,(action,filename)
 base=base.replace(old,(R/'probes'/filename).read_text() if filename else '',1)
decl=' void SpawnAt453C80(int,float,float,char,int);'
assert base.count(decl)==1
base=base.replace(decl,decl+
  ' void SpawnMixedAt453C80(int,int,float,char,int);'
  ' void ConfigureStormAt454BC0(int,int,int);'
  ' void SpawnRawAt453C80(int,int,int,char,int);',1)
ext='extern float g_ThresholdAt0065782C;'
assert base.count(ext)==1
base=base.replace(ext,'''extern float g_F748_SpeedScaleAt006590B8;
extern float g_F948_C8UpperAt00657854;
extern float g_F948_C8DragAt00658350;
extern float g_F948_C8VolleyYAt00658268;
extern float g_F950_CAVolleyYAt00658400;
'''+ext,1)
CA=(R/'probes/FighterThirdBossFourWayCAF950.inc').read_text()
assert base.count(CA)==1
changes=[
 ('stage0-reversed','S16(0x62)==0','0==S16(0x62)'),
 ('stage2-const','S16(0x62)==2','*reinterpret_cast<const short*>(RAW+0x62)==2'),
 ('stage-gt-one-reversed','S16(0x62)>1','1<S16(0x62)'),
 ('ground-gt-reversed','POS48>g_ThresholdAt0065782C','g_ThresholdAt0065782C<POS48'),
 ('contact-summand-reverse','POS54+POS48<=g_ThresholdAt0065782C','POS48+POS54<=g_ThresholdAt0065782C'),
 ('bullet-X-borrowed','float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44)',
 'float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+reinterpret_cast<const FighterBorrowedXViewF752*>(this)->xAt44'),
 ('bullet-X-summand-reverse','float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44)',
 'F32(0x44)+float((*reinterpret_cast<signed char*>(RAW+0x66))*80)'),
 ('frame-finish-reversed','GetNativeActionAt40FA30()==S16(0x70)',
 'S16(0x70)==GetNativeActionAt40FA30()'),
]
variants={'native-strict-CA':CA}
for label,old,new in changes:
 assert old in CA
 variants[label]=CA.replace(old,new,1)
assert len(variants)==9
sp=importlib.util.spec_from_file_location('f957reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;LENGTH=82796;WHOLEX=22721;DATA=1126
full_native=list(D.disasm(rd.pe_bytes_at(PE,BASE,LENGTH),BASE))
assert len(full_native)==WHOLEX and full_native[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+LENGTH,DATA)
orig={'CA':(0x4B04CC,0x4B0680,436,123,11),
      'CB':(0x4B0680,0x4B0852,466,131,11)}
native={}
for case,(lo,hi,size,nx,_) in orig.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,lo,size),lo))
 assert hi-lo==size and len(n)==nx
 native[case]=n
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda n:tuple(rx.findall(n.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,case_source in variants.items():
 src=base.replace(CA,case_source,1)
 cpp,obj=O/(label+'.cpp'),O/(label+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=env,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  o=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(k not in mask for k in range(o,o+4))
  mask.update(range(o,o+4))
  addr=int.from_bytes(native_data[o:o+4],'little')
  assert BASE<=addr<BASE+LENGTH
  labels.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+k]==native_data[k] for k in range(DATA) if k not in mask)
 results={'whole_partial_CODE_B':end,'whole_partial_x86':len(I),
  'original_complete_GAME_CODE_B':LENGTH,'original_complete_GAME_x86':WHOLEX,
  'source_COFF_fields_total':len(refs),
  'original_afterRET_DIR32_fields':151,'original_afterRET_nonfield_exact_B':522,
  'real_cases':{},'whole_game_exact':False}
 for case,(a,b,sz,nx,nrefs) in orig.items():
  assert a in labels and b in labels
  lo,hi=labels[a],labels[b]
  ins=[x for x in I if lo<=x.address<hi]
  refs_case=[r for r in refs if lo<=r['offset']<hi]
  assert len(ins)==nx and len(refs_case)==nrefs
  mm=[i for i,(x,y) in enumerate(zip(native[case],ins)) if x.mnemonic!=y.mnemonic]
  ww=[i for i,(x,y) in enumerate(zip(native[case],ins)) if x.size!=y.size]
  gg=[i for i,(x,y) in enumerate(zip(native[case],ins)) if role(x)!=role(y)]
  record={'native_original_B':sz,'native_original_x86':nx,
    'source_B':hi-lo,'source_x86':len(ins),
    'native_wrong_mnemonic_ordinals':mm,'native_wrong_width_ordinals':ww,
    'native_wrong_GPR_ordinals':gg,
    'original_typed_COFF_symbol_fields':len(refs_case),
    'real_native_PE_targets_physically_checked':0}
  if not mm:
   raw=rd.pe_bytes_at(PE,a,sz)
   for r in refs_case:
    i=next(i for i,x in enumerate(ins) if x.address<=r['offset']<x.address+x.size)
    delta=r['offset']-ins[i].address
    o=native[case][i].address-a+delta
    assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
    value=int.from_bytes(raw[o:o+4],'little',signed=r['type']=='REL32')
    target=(native[case][i].address+delta+4+value if r['type']=='REL32' else value)
    f=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
    exp=int(f.group(1),16) if f else 0x6406AC if r['symbol']=='__ftol2' else None
    assert target==exp,(label,case,i,r['symbol'],hex(target),exp)
   record['real_native_PE_targets_physically_checked']=len(refs_case)
  results['real_cases'][case]=record
 rows[label]=results
 print(label,'partial whole',end,len(I),
   'CA wrong mnemonic/GPR',len(results['real_cases']['CA']['native_wrong_mnemonic_ordinals']),
   len(results['real_cases']['CA']['native_wrong_GPR_ordinals']),
   'CB wrong GPR',len(results['real_cases']['CB']['native_wrong_GPR_ordinals']),flush=True)
basecase=rows['native-strict-CA']
assert (basecase['whole_partial_CODE_B'],basecase['whole_partial_x86'])==(21616,5859)
assert len(basecase['real_cases']['CA']['native_wrong_GPR_ordinals'])==0
assert basecase['real_cases']['CA']['native_wrong_width_ordinals']==[47,48]
assert basecase['real_cases']['CA']['native_wrong_mnemonic_ordinals']==[]
assert (basecase['real_cases']['CB']['source_B'],basecase['real_cases']['CB']['source_x86'])==(454,131)
assert len(basecase['real_cases']['CB']['native_wrong_GPR_ordinals'])==79
assert basecase['real_cases']['CB']['native_wrong_width_ordinals']==[96,97,118,119]
assert all(len(x['real_cases']['CB']['native_wrong_GPR_ordinals'])==79 for x in rows.values())
assert all(x['real_cases']['CB']['real_native_PE_targets_physically_checked']==11 for x in rows.values())
assert all(x['real_cases']['CA']['original_typed_COFF_symbol_fields']==11 for x in rows.values())
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_native_Japanese_whole_game':'0x004AC040',
 'original_whole_native_B':LENGTH,'original_whole_native_x86':WHOLEX,
 'native_original_CA_B_x86':[436,123],'native_original_CB_B_x86':[466,131],
 'natural_predecessor_CA_source_variants':len(rows),
 'private_30_complete_Cpp_compiles_saved':True,
 'one_invalid_const_write_candidate_rejected':True,
 'CB_original_minimum_wrong_GPR':79,'CB_original_first_wrong_GPR_ordinal':5,
 'original_whole_exact':False,'new_original_accepted_GAME_B':0,
 'no_mass_cold_replay':True,'native_whole_source_control_rows':rows
},indent=2)+'\n')
print('F957 complete: 9 PE-backed whole natural C++ parent controls of real preceding CA; all keep 79 native next CB GPR differences, no whole original exactness.')
