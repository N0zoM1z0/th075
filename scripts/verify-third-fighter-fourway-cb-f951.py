#!/usr/bin/env python3
"""F951: original 82KB fighter's CΒ whole source geometry, 11 typed PE fields.

Generate two whole NORMAL VC7.1 original-shaped partial 82KB fighter
C++ source parents: old CB stub and genuine CB body. Original Japanese
TH075 PE authority, independently backed original 466B/131-x86
and 11 real PE field targets; preceding original C8/C9/CA cases
are also checked with their honest prior width deficits.
Actual 151 afterRET DIR32/522 nonfield DATA retained.
NEVER claim byte-exact partial case or a new whole function.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f951-third-native-CB';O.mkdir(parents=True,exist_ok=True)
source=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
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
for case,marker,file in parts:
 old=f'        case 0x{case:X}: g_FighterProbeMarker = {marker}; break;'
 assert source.count(old)==1
 source=source.replace(old,(R/'probes'/file).read_text() if file else '',1)
decl=' void SpawnAt453C80(int,float,float,char,int);'
assert source.count(decl)==1
source=source.replace(decl,decl+
 ' void SpawnMixedAt453C80(int,int,float,char,int);'
 ' void ConfigureStormAt454BC0(int,int,int);',1)
needle='extern float g_ThresholdAt0065782C;'
assert source.count(needle)==1
source=source.replace(needle,'''extern float g_F748_SpeedScaleAt006590B8;
extern float g_F948_C8UpperAt00657854;
extern float g_F948_C8DragAt00658350;
extern float g_F948_C8VolleyYAt00658268;
extern float g_F950_CAVolleyYAt00658400;
'''+needle,1)
old='        case 0xCB: g_FighterProbeMarker = 204; break;'
new=(R/'probes/FighterThirdBossFourWayCBF951.inc').read_text()
assert source.count(old)==1 and new.count('case 0xCB:')==1
variants={'F950-prior-CB-marker':source,
          'F951-authentic-CA-CB-pair':source.replace(old,new,1)}
sp=importlib.util.spec_from_file_location('f951reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;LENGTH=82796;WHOLEX=22721;DATA=1126
native_full=list(D.disasm(rd.pe_bytes_at(PE,BASE,LENGTH),BASE))
assert len(native_full)==WHOLEX and native_full[2].op_str=='esp, 0x720'
original_data=rd.pe_bytes_at(PE,BASE+LENGTH,DATA)
physical={
 'C8':(0x4B009E,0x4B02B9,539,149,15),
 'C9':(0x4B02B9,0x4B04CC,531,158,13),
 'CA':(0x4B04CC,0x4B0680,436,123,11),
 'CB':(0x4B0680,0x4B0852,466,131,11)}
original={}
for k,(a,b,n,nx,nf) in physical.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,n),a))
 assert len(I)==nx and b-a==n
 original[k]=I
assert original['CB'][96].op_str=='dword ptr [ebp - 0x9c], eax'
assert original['CB'][97].op_str=='dword ptr [ebp - 0x9c]'
assert original['CB'][118].op_str=='dword ptr [ebp - 0xa0], eax'
assert original['CB'][119].op_str=='dword ptr [ebp - 0xa0]'
assert original['CB'][95].mnemonic==original['CB'][117].mnemonic=='imul'
assert original['CB'][95].op_str.endswith(', 0x44')
assert original['CB'][117].op_str.endswith(', 0x44')
assert original['CB'][90].op_str==original['CB'][112].op_str=='dword ptr [0x658400]'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows={}
for tag,src in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
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
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  native_va=int.from_bytes(original_data[off:off+4],'little')
  assert BASE<=native_va<BASE+LENGTH
  labels.setdefault(native_va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+j]==original_data[j] for j in range(DATA) if j not in mask)
 row={'original_complete_game_CODE_B':LENGTH,'original_x86':WHOLEX,
      'partial_source_CODE_B':end,'partial_source_x86':len(I),
      'source_COFF_records':len(refs),'native_afterRET_DIR32':151,
      'native_afterRET_nonfield_DATA_equal':522,'native_actions':{},
      'whole_original_game_exact':False}
 for action,(a,b,n,nx,nf) in physical.items():
  assert a in labels and b in labels
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  rec={'native_original_CODE_B':n,'native_x86':nx,
       'source_CODE_B':hi-lo,'source_x86':len(part),'native_PE_fields_verified':0}
  if len(part)==nx:
   badm=[j for j,(x,y) in enumerate(zip(original[action],part)) if x.mnemonic!=y.mnemonic]
   badw=[j for j,(x,y) in enumerate(zip(original[action],part)) if x.size!=y.size]
   badg=[j for j,(x,y) in enumerate(zip(original[action],part)) if roles(x)!=roles(y)]
   rec.update({'wrong_native_mnemonic_ordinals':badm,
      'wrong_native_width_ordinals':badw,'wrong_native_GPR_roles':badg})
   assert len(fields)==nf
   nbytes=rd.pe_bytes_at(PE,a,n)
   for r in fields:
    j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
    disp=r['offset']-part[j].address
    native_offset=original[action][j].address-a+disp
    assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
    val=int.from_bytes(nbytes[native_offset:native_offset+4],'little',signed=r['type']=='REL32')
    target=original[action][j].address+disp+4+val if r['type']=='REL32' else val
    sym=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
    expect=int(sym.group(1),16) if sym else 0x6406AC if r['symbol']=='__ftol2' else None
    assert target==expect,(action,j,r['symbol'],hex(target),expect)
   rec['native_PE_fields_verified']=len(fields)
  row['native_actions'][action]=rec
 rows[tag]=row
 print(tag,'whole partial',end,len(I),'CB source B/x86',
       row['native_actions']['CB']['source_CODE_B'],row['native_actions']['CB']['source_x86'],
       'native fields',row['native_actions']['CB']['native_PE_fields_verified'],flush=True)
old=rows['F950-prior-CB-marker'];new=rows['F951-authentic-CA-CB-pair']
assert (old['partial_source_CODE_B'],old['partial_source_x86'])==(19958,5365)
assert (new['partial_source_CODE_B'],new['partial_source_x86'])==(20397,5494)
assert old['native_actions']['CB']['source_CODE_B']==15
assert (new['native_actions']['CB']['source_CODE_B'],new['native_actions']['CB']['source_x86'])==(454,131)
assert new['native_actions']['CB']['wrong_native_mnemonic_ordinals']==[]
assert new['native_actions']['CB']['wrong_native_width_ordinals']==[96,97,118,119]
assert len(new['native_actions']['CB']['wrong_native_GPR_roles'])==79
assert new['native_actions']['CB']['native_PE_fields_verified']==11
for k in ('C8','C9','CA'):
 assert new['native_actions'][k]['source_CODE_B']==old['native_actions'][k]['source_CODE_B']
 assert new['native_actions'][k]['native_PE_fields_verified']==physical[k][4]
assert new['native_actions']['C8']['wrong_native_width_ordinals']==[106,121,122]
assert new['native_actions']['C9']['wrong_native_width_ordinals']==[]
assert new['native_actions']['CA']['wrong_native_width_ordinals']==[47,48]
(O/'verified-summary.json').write_text(json.dumps({
 'native_Japanese_original_whole_fighter':'0x004AC040',
 'native_original_whole_CODE_B':LENGTH,'native_whole_x86':WHOLEX,
 'native_CB_handler':'0x004B0680..004B0852',
 'native_CB_full_CODE_B_x86':[466,131],
 'CB_generated_natural_Cpp_CODE_B_x86':[454,131],
 'CB_native_PE_targets_validated':11,
 'CB_wrong_mnemonic_positions':0,
 'CB_wrong_GPR_role_instructions':79,
 'CB_four_original_0x9C_0xA0_scratch_widths':[96,97,118,119],
 'whole_original_exact':False,'new_accepted_game_CODE_B':0,
 'mass_cold_replay':False,'whole_parent_source_profiles':rows
},indent=2)+'\n')
print('F951 original CB natural C++: 454B/131 x86 vs native 466B/131, 11 real native fields. GPR roles 79 wrong, 4 original long-stack widths short; no whole exact.')
