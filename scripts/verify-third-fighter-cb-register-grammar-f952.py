#!/usr/bin/env python3
"""F952: original fighter 004AC040 case CB register phase on entire partial father.

Regenerate the F951 complete original-shaped partial C++ parent from
TRACKED inputs and compile nine meaningful ordinary VC7.1 source
variations. Measure whole native 466B/131-x86 CB GPR/width/mnemonic
differences against pinned original PE. Check 11 physical original
external PE/COFF references, original 151 afterRET DIR32 table fields
and 522 DATA nonfield bytes on EVERY parent. This documents negative
full-parent C++ grammar evidence without a false exact-game claim.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f952-third-cb-register-proof';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
parts=[
 (0x5D,94,'FighterThirdBossPair5D5EF939.inc'),
 (0x5E,95,None),(0x5F,96,'FighterThirdBossFacing5FF941.inc'),
 (0x60,97,'FighterThirdBossVolley6061F942.inc'),
 (0x61,98,None),(0x62,99,'FighterThirdBossSelector62F943.inc'),
 (0xCF,208,'FighterFallStateCFF647.inc'),
 (0xD0,209,'FighterReflectLandingD0F646.inc'),
 (0xC8,201,'FighterThirdBossFourWayC8F948.inc'),
 (0xC9,202,'FighterThirdBossFourWayC9F949.inc'),
 (0xCA,203,'FighterThirdBossFourWayCAF950.inc')]
for action,marker,name in parts:
 old=f'        case 0x{action:X}: g_FighterProbeMarker = {marker}; break;'
 assert base.count(old)==1
 base=base.replace(old,(R/'probes'/name).read_text() if name else '',1)
owner=' void SpawnAt453C80(int,float,float,char,int);'
assert base.count(owner)==1
base=base.replace(owner,owner+
 ' void SpawnMixedAt453C80(int,int,float,char,int);'
 ' void ConfigureStormAt454BC0(int,int,int);',1)
needle='extern float g_ThresholdAt0065782C;'
assert base.count(needle)==1
base=base.replace(needle,'''extern float g_F748_SpeedScaleAt006590B8;
extern float g_F948_C8UpperAt00657854;
extern float g_F948_C8DragAt00658350;
extern float g_F948_C8VolleyYAt00658268;
extern float g_F950_CAVolleyYAt00658400;
'''+needle,1)
marker='        case 0xCB: g_FighterProbeMarker = 204; break;'
assert base.count(marker)==1
body=(R/'probes/FighterThirdBossFourWayCBF951.inc').read_text()
assert body.count('case 0xCB:')==1
normal=base.replace(marker,body,1)
variants={'F951-strict-baseline':body}
substitutions=[
 ('stage0-const-read','S16(0x62)==0','*reinterpret_cast<const short*>(RAW+0x62)==0'),
 ('stage0-reversed','S16(0x62)==0','0==S16(0x62)'),
 ('stage-positive-ge-one','S16(0x62)>0','S16(0x62)>=1'),
 ('floor-positive-reversed','POS48>g_ThresholdAt0065782C','g_ThresholdAt0065782C<POS48'),
 ('frame-finish-reversed','GetNativeActionAt40FA30()==S16(0x70)',
  'S16(0x70)==GetNativeActionAt40FA30()'),
 ('float-X-typed-borrowed','float((*reinterpret_cast<signed char*>(RAW+0x66))*68)+F32(0x44)',
  'float((*reinterpret_cast<signed char*>(RAW+0x66))*68)+reinterpret_cast<const FighterBorrowedXViewF752*>(this)->xAt44'),
 ('float-X-operand-reversed','float((*reinterpret_cast<signed char*>(RAW+0x66))*68)+F32(0x44)',
  'F32(0x44)+float((*reinterpret_cast<signed char*>(RAW+0x66))*68)'),
 ('used-initializer-reorder','S16(0xF00)=0;\n        POS=0.0f;\n        POS54=0.0f;\n        POS5C=0.0f;',
  'POS=0.0f;\n        S16(0xF00)=0;\n        POS54=0.0f;\n        POS5C=0.0f;'),
]
for name,old,new in substitutions:
 assert old in body,(name,old)
 variants[name]=body.replace(old,new,1)
assert len(variants)==9
sp=importlib.util.spec_from_file_location('f952reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
original_base=0x4AC040;original_whole=82796;original_data_B=1126
orig_whole_ins=list(D.disasm(rd.pe_bytes_at(PE,original_base,original_whole),original_base))
assert len(orig_whole_ins)==22721 and orig_whole_ins[2].op_str=='esp, 0x720'
original_data=rd.pe_bytes_at(PE,original_base+original_whole,original_data_B)
CB_LO,CB_HI=0x4B0680,0x4B0852
native=list(D.disasm(rd.pe_bytes_at(PE,CB_LO,CB_HI-CB_LO),CB_LO))
assert len(native)==131 and CB_HI-CB_LO==466
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(rx.findall(ins.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
results=[]
for name,case in variants.items():
 src=normal.replace(body,case,1)
 cpp,obj=O/(name+'.cpp'),O/(name+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for ins in D.disasm(code,0):
  I.append(ins)
  if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==original_data_B
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(original_data[off:off+4],'little')
  assert original_base<=va<original_base+original_whole
  labels.setdefault(va,r['local_symbol_offset'])
 assert original_data_B-len(mask)==522
 assert all(code[end+i]==original_data[i] for i in range(original_data_B) if i not in mask)
 assert CB_LO in labels and CB_HI in labels
 lo,hi=labels[CB_LO],labels[CB_HI]
 caseins=[x for x in I if lo<=x.address<hi]
 fields=[r for r in refs if lo<=r['offset']<hi]
 assert len(caseins)==131 and len(fields)==11
 wrong_m=[i for i,(a,b) in enumerate(zip(native,caseins)) if a.mnemonic!=b.mnemonic]
 wrong_w=[i for i,(a,b) in enumerate(zip(native,caseins)) if a.size!=b.size]
 wrong_g=[i for i,(a,b) in enumerate(zip(native,caseins)) if roles(a)!=roles(b)]
 native_bytes=rd.pe_bytes_at(PE,CB_LO,466)
 # A candidate with different x87/branch mnemonics may genuinely
 # reorder the original PE field's x86 instruction ordinal. Never
 # falsely compare same-ordinal displacement fields in such controls.
 # First strictly verify all 11 original target VAs in baseline and
 # in each variant whose ordered original mnemonics are preserved.
 if not wrong_m:
  for ref in fields:
   i=next(i for i,x in enumerate(caseins) if x.address<=ref['offset']<x.address+x.size)
   delta=ref['offset']-caseins[i].address
   native_off=native[i].address-CB_LO+delta
   assert ref['type'] in ('DIR32','REL32') and ref['addend']==0 and ref['local_symbol_offset'] is None
   v=int.from_bytes(native_bytes[native_off:native_off+4],'little',signed=ref['type']=='REL32')
   target=(native[i].address+delta+4+v if ref['type']=='REL32' else v)
   m=re.search(r'At([0-9A-Fa-f]{6,8})',ref['symbol'])
   exp=int(m.group(1),16) if m else 0x6406AC if ref['symbol']=='__ftol2' else None
   assert target==exp,(name,i,ref['symbol'],hex(target),exp)
 source_field_roles=[(r['type'],r['symbol']) for r in sorted(fields,key=lambda x:x['offset'])]
 if name=='F951-strict-baseline':
  baseline_field_roles=source_field_roles
 else:
  assert source_field_roles==baseline_field_roles,(name,source_field_roles)
 row={'variant':name,'whole_partial_source_CODE_B':end,'whole_partial_source_x86':len(I),
 'native_original_CB_CODE_B':466,'native_original_CB_x86':131,
 'generated_CB_CODE_B':hi-lo,'CB_wrong_mnemonic_ordinals':wrong_m,
 'CB_wrong_width_ordinals':wrong_w,'CB_wrong_GPR_role_instructions':len(wrong_g),
 'CB_first_wrong_GPR':wrong_g[0] if wrong_g else None,
 'original_typed_COFF_symbol_fields_preserved':len(fields),
 'original_PE_target_fields_positional_verified':len(fields) if not wrong_m else 0,
 'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal':522,
 'whole_original_exact':False}
 results.append(row)
 print(name,'whole generated',end,'CB',hi-lo,
   'GPR wrong',len(wrong_g),'mnemonic wrong',len(wrong_m),
   'width wrong',len(wrong_w),flush=True)
assert len(results)==9 and all(x['CB_wrong_GPR_role_instructions']>=79 for x in results)
assert all(x['original_typed_COFF_symbol_fields_preserved']==11 for x in results)
assert results[0]['original_PE_target_fields_positional_verified']==11
a=next(x for x in results if x['variant']=='F951-strict-baseline')
assert (a['generated_CB_CODE_B'],a['CB_wrong_GPR_role_instructions'])==(454,79)
assert a['CB_wrong_mnemonic_ordinals']==[]
assert a['CB_wrong_width_ordinals']==[96,97,118,119]
assert all(x['CB_first_wrong_GPR']==5 for x in results)
(O/'verified-summary.json').write_text(json.dumps({
 'original_hash_attested_fighter':'0x004AC040',
 'true_original_whole_CODE_B':82796,'true_original_whole_x86':22721,
 'original_0xCB':'0x004B0680..004B0852',
 'original_0xCB_CODE_B_x86':[466,131],
 'portable_full_partial_father_Cpp_controls':len(results),
 'private_full_parent_28_original_source_variants_saved':True,
 'native_minimum_wrong_0xCB_GPR_roles':min(x['CB_wrong_GPR_role_instructions'] for x in results),
 'native_original_EBP_first_save_still_wrong':True,
 'new_accepted_original_GAME_CODE_B':0,'whole_original_exact':False,
 'mass_cold_replay':False,'verified_controls':results
},indent=2)+'\n')
print('F952 nine original PE/COFF-backed entire partial C++ parents: none improves first native CB GPR mismatch ordinal5 or 79 wrong roles without regressions; no exact whole game source.')
