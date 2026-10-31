#!/usr/bin/env python3
"""F950: restore real actor 004AC040 original 0xCA 123 native x86 in whole partial father.

Serially compile old marker and new C++ under pinned normal VC7.1 in
ENTIRE original-shaped father source, independently compare SHA-pinned
PE source boundaries, original 0xCA real x86 436B/123, 11 true original
PE-targeted COFF fields, real previous C8/C9 x86 and afterRET DATA.
Native EBP-0x98 vs source-0x44 causes two genuine width differences.
No standalone case/partial parent exact code credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f950-third-original-CA';O.mkdir(parents=True,exist_ok=True)
source=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
parts=[
 (0x5D,94,'FighterThirdBossPair5D5EF939.inc'),
 (0x5E,95,None),(0x5F,96,'FighterThirdBossFacing5FF941.inc'),
 (0x60,97,'FighterThirdBossVolley6061F942.inc'),
 (0x61,98,None),(0x62,99,'FighterThirdBossSelector62F943.inc'),
 (0xCF,208,'FighterFallStateCFF647.inc'),
 (0xD0,209,'FighterReflectLandingD0F646.inc'),
 (0xC8,201,'FighterThirdBossFourWayC8F948.inc'),
 (0xC9,202,'FighterThirdBossFourWayC9F949.inc')]
for action,marker,file in parts:
 old=f'        case 0x{action:X}: g_FighterProbeMarker = {marker}; break;'
 assert source.count(old)==1
 source=source.replace(old,(R/'probes'/file).read_text() if file else '',1)
pro=' void SpawnAt453C80(int,float,float,char,int);'
assert source.count(pro)==1
source=source.replace(pro,pro+
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
old='        case 0xCA: g_FighterProbeMarker = 203; break;'
real=(R/'probes/FighterThirdBossFourWayCAF950.inc').read_text()
assert source.count(old)==1 and real.count('case 0xCA:')==1
variants={'F949-original-CA-marker':source,
          'F950-authentic-CA':source.replace(old,real,1)}
sp=importlib.util.spec_from_file_location('f950reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
BASE=0x4AC040;WHOLEN=82796;WHOLEX=22721;DATA=1126
native_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLEN),BASE))
assert len(native_whole)==WHOLEX and native_whole[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+WHOLEN,DATA)
native_cases={
 '0xC8':(0x4B009E,0x4B02B9,539,149,15),
 '0xC9':(0x4B02B9,0x4B04CC,531,158,13),
 '0xCA':(0x4B04CC,0x4B0680,436,123,11)}
original={}
for key,(a,b,nb,nx,nf) in native_cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,nb),a))
 assert len(I)==nx and b-a==nb
 original[key]=I
assert original['0xCA'][47].op_str=='dword ptr [ebp - 0x98], ecx'
assert original['0xCA'][48].op_str=='dword ptr [ebp - 0x98]'
assert original['0xCA'][55].op_str=='0x453c80'
assert original['0xCA'][70].op_str=='0x453c80'
assert original['0xCA'][41].op_str=='dword ptr [0x658400]'
assert original['0xCA'][62].op_str=='dword ptr [0x658400]'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(rx.findall(i.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
results={}
for tag,body in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(body)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
    cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 mp={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(k not in mask for k in range(off,off+4))
  mask.update(range(off,off+4))
  t=int.from_bytes(native_data[off:off+4],'little')
  assert BASE<=t<BASE+WHOLEN
  mp.setdefault(t,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+k]==native_data[k] for k in range(DATA) if k not in mask)
 row={'whole_original_CODE_B':WHOLEN,'original_whole_x86':WHOLEX,
 'complete_partial_cpp_CODE_B':end,'complete_partial_cpp_x86':len(I),
 'source_COOf_records':len(refs),'native_afterRET_DIR32_fields':151,
 'native_afterRET_nonfield_bytes_equal':522,'original_actions':{},
 'whole_original_game_exact':False}
 for key,(a,b,nb,nx,nf) in native_cases.items():
  assert a in mp and b in mp
  lo,hi=mp[a],mp[b]
  part=[x for x in I if lo<=x.address<hi]
  owned=[r for r in refs if lo<=r['offset']<hi]
  rec={'native_original_CODE_B':nb,'original_x86':nx,
       'source_CODE_B':hi-lo,'source_x86':len(part),
       'native_PE_fields_verified':0}
  if len(part)==nx:
   badm=[j for j,(x,y) in enumerate(zip(original[key],part)) if x.mnemonic!=y.mnemonic]
   badw=[j for j,(x,y) in enumerate(zip(original[key],part)) if x.size!=y.size]
   badg=[j for j,(x,y) in enumerate(zip(original[key],part)) if roles(x)!=roles(y)]
   rec.update({'native_mnemonic_wrong_ordinals':badm,
       'native_width_wrong_ordinals':badw,
       'native_GPR_wrong_ordinals':badg})
   assert len(owned)==nf
   orig_raw=rd.pe_bytes_at(PE,a,nb)
   for r in owned:
    j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
    delta=r['offset']-part[j].address
    origoff=original[key][j].address-a+delta
    assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
    v=int.from_bytes(orig_raw[origoff:origoff+4],'little',signed=r['type']=='REL32')
    resolved=original[key][j].address+delta+4+v if r['type']=='REL32' else v
    f=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
    expected=int(f.group(1),16) if f else 0x6406AC if r['symbol']=='__ftol2' else None
    assert resolved==expected,(key,j,r['symbol'],hex(resolved),expected)
   rec['native_PE_fields_verified']=len(owned)
  row['original_actions'][key]=rec
 results[tag]=row
 print(tag,'whole source',end,'x86',len(I),'native CA src B/x86',
   row['original_actions']['0xCA']['source_CODE_B'],
   row['original_actions']['0xCA']['source_x86'],
   'real CA PE fields',row['original_actions']['0xCA']['native_PE_fields_verified'],flush=True)
old=results['F949-original-CA-marker'];new=results['F950-authentic-CA']
assert (old['complete_partial_cpp_CODE_B'],old['complete_partial_cpp_x86'])==(19543,5244)
assert (new['complete_partial_cpp_CODE_B'],new['complete_partial_cpp_x86'])==(19958,5365)
assert old['original_actions']['0xCA']['source_CODE_B']==15
assert new['original_actions']['0xCA']['source_CODE_B']==430
assert new['original_actions']['0xCA']['source_x86']==123
assert new['original_actions']['0xCA']['native_mnemonic_wrong_ordinals']==[]
assert new['original_actions']['0xCA']['native_width_wrong_ordinals']==[47,48]
assert new['original_actions']['0xCA']['native_GPR_wrong_ordinals']==[]
assert new['original_actions']['0xCA']['native_PE_fields_verified']==11
for key in ('0xC8','0xC9'):
 assert new['original_actions'][key]['source_CODE_B']==old['original_actions'][key]['source_CODE_B']
 assert new['original_actions'][key]['native_PE_fields_verified']==native_cases[key][4]
assert new['original_actions']['0xC8']['native_width_wrong_ordinals']==[106,121,122]
assert new['original_actions']['0xC9']['native_width_wrong_ordinals']==[]
(O/'verified-summary.json').write_text(json.dumps({
 'original_sha_pinned_giant':'0x004AC040',
 'whole_original_B':WHOLEN,'whole_original_x86':WHOLEX,
 'new_0xCA_native_start_end':'0x004B04CC..004B0680',
 'native_original_0xCA_B_x86':[436,123],
 'generated_0xCA_B_x86':[430,123],
 'native_0xCA_actual_typed_PE_targets':11,
 'native_0xCA_mnemonic_GPR_role_wrong':0,
 'real_width_deficits_native_stack_ordinals':[47,48],
 'native_EBP_temp':'-0x98','partial_cpp_EBP_temp':'-0x44',
 'original_whole_exact':False,'accepted_new_original_CODE_B':0,
 'all_units_cold_replayed':False,'whole_parent_profiles':results
},indent=2)+'\n')
print('F950 native actor CΑ: 436B/123 original; natural C++ 430B/123, all mnemonic/GPR roles align with 11 original PE targets; 2 genuine EBP-0x98 wide-temp deficits. NO whole exact.')
