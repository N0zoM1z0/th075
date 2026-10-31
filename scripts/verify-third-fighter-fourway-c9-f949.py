#!/usr/bin/env python3
"""F949: true native original 004AC040 C9: 531B/158x86, 13 PE fields.

Regenerate old C9 marker vs genuine C++ in two whole original-shaped
VC7.1 *partial* 82KB parent units. Compare true SHA-pinned PE physical
C9 target, original x86 mnemonic/width/GPR, 13 typed original
PE-target relocations, C8 earlier case, 151 true afterRET DIR32
local target labels and 522 nonfield DATA bytes. No whole exact credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f949-third-real-C9';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
parts=[
 (0x5D,94,'FighterThirdBossPair5D5EF939.inc'),
 (0x5E,95,None),
 (0x5F,96,'FighterThirdBossFacing5FF941.inc'),
 (0x60,97,'FighterThirdBossVolley6061F942.inc'),
 (0x61,98,None),
 (0x62,99,'FighterThirdBossSelector62F943.inc'),
 (0xCF,208,'FighterFallStateCFF647.inc'),
 (0xD0,209,'FighterReflectLandingD0F646.inc'),
 (0xC8,201,'FighterThirdBossFourWayC8F948.inc'),
]
source=base
for action,marker,file in parts:
 old=f'        case 0x{action:X}: g_FighterProbeMarker = {marker}; break;'
 assert source.count(old)==1
 source=source.replace(old,(R/'probes'/file).read_text() if file else '',1)
# Original ABI access remains provisional; exact call targets are
# verified against PE rather than guessed from method C++ names.
needle=' void SpawnAt453C80(int,float,float,char,int);'
assert source.count(needle)==1
source=source.replace(needle,needle+
 ' void SpawnMixedAt453C80(int,int,float,char,int);'
 ' void ConfigureStormAt454BC0(int,int,int);',1)
needle='extern float g_ThresholdAt0065782C;'
assert source.count(needle)==1
source=source.replace(needle,'''extern float g_F748_SpeedScaleAt006590B8;
extern float g_F948_C8UpperAt00657854;
extern float g_F948_C8DragAt00658350;
extern float g_F948_C8VolleyYAt00658268;
'''+needle,1)
old='        case 0xC9: g_FighterProbeMarker = 202; break;'
new=(R/'probes/FighterThirdBossFourWayC9F949.inc').read_text()
assert source.count(old)==1 and new.count('case 0xC9:')==1
variants={
 'F948-native-C9-marker':source,
 'F949-native-real-C9':source.replace(old,new,1)}
sp=importlib.util.spec_from_file_location('f949reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;TOTAL=82796;NX=22721;DATA=1126
native_full=list(D.disasm(rd.pe_bytes_at(PE,BASE,TOTAL),BASE))
assert len(native_full)==NX
native_data=rd.pe_bytes_at(PE,BASE+TOTAL,DATA)
original={
 'C8':(0x4B009E,0x4B02B9,539,149,15),
 'C9':(0x4B02B9,0x4B04CC,531,158,13)}
native={}
for case,(a,b,size,nx,ext) in original.items():
 instr=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(instr)==nx
 native[case]=instr
# Actual native stage/float and short-state values are independently
# decoded here; do not trust another original game's C9 profile.
C9=native['C9']
assert [C9[j].op_str for j in (17,27,43,47,73,89,99,148,154)]==[
  'ecx, 2','eax, 4','eax, 3','edx, 6','6','edx, 2','ecx, 4','eax, 6','5']
assert C9[110].op_str=='dword ptr [eax + 0x50], 0xc1f00000'
assert C9[118].op_str=='dword ptr [0x657888]'
assert C9[134].op_str=='dword ptr [0x657888]'
assert C9[126].mnemonic==C9[142].mnemonic=='call'
assert C9[126].op_str==C9[142].op_str=='0x453c80'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows={}
for tag,src in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for ins in D.disasm(code,0):
  I.append(ins)
  if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  native_addr=int.from_bytes(native_data[off:off+4],'little')
  assert BASE<=native_addr<BASE+TOTAL
  labels.setdefault(native_addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(DATA) if i not in mask)
 row={'original_whole_CODE_B':TOTAL,'original_whole_x86':NX,
      'source_partial_whole_CODE_B':end,'source_partial_whole_x86':len(I),
      'total_source_COFF_records':len(refs),'original_afterRET_DATA_B':DATA,
      'native_afterRET_DIR32':151,'native_afterRET_nonfield_equal_B':522,
      'original_C8_C9':{},'whole_original_exact':False}
 for case,(a,b,size,nx,expectfields) in original.items():
  assert a in labels and b in labels
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  record={'original_native_CODE_B':size,'original_x86':nx,
      'source_CODE_B':hi-lo,'source_x86':len(part),
      'native_original_PE_targets_verified':0}
  if len(part)==nx:
   wrongm=[i for i,(n,s) in enumerate(zip(native[case],part)) if n.mnemonic!=s.mnemonic]
   wrongw=[i for i,(n,s) in enumerate(zip(native[case],part)) if n.size!=s.size]
   wrongg=[i for i,(n,s) in enumerate(zip(native[case],part)) if roles(n)!=roles(s)]
   record.update({'wrong_original_mnemonics':wrongm,
       'wrong_original_widths':wrongw,'wrong_original_GPR_roles':wrongg})
   assert len(fields)==expectfields
   original_code=rd.pe_bytes_at(PE,a,size)
   for r in fields:
    j=next(i for i,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
    disp=r['offset']-part[j].address
    field=native[case][j].address-a+disp
    assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
    value=int.from_bytes(original_code[field:field+4],'little',signed=r['type']=='REL32')
    target=native[case][j].address+disp+4+value if r['type']=='REL32' else value
    found=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
    expect=int(found.group(1),16) if found else 0x6406AC if r['symbol']=='__ftol2' else None
    assert target==expect,(case,j,r['symbol'],hex(target),expect)
   record['native_original_PE_targets_verified']=len(fields)
  row['original_C8_C9'][case]=record
 rows[tag]=row
 print(tag,'whole partial B',end,'x86',len(I),
  'caseC8',row['original_C8_C9']['C8']['source_CODE_B'],
  'caseC9',row['original_C8_C9']['C9']['source_CODE_B'],
  'caseC9 fields',row['original_C8_C9']['C9']['native_original_PE_targets_verified'],flush=True)
old=rows['F948-native-C9-marker'];new=rows['F949-native-real-C9']
assert old['original_C8_C9']['C9']['source_CODE_B']==15
assert (new['source_partial_whole_CODE_B'],new['source_partial_whole_x86'])==(19543,5244)
assert (new['original_C8_C9']['C9']['source_CODE_B'],new['original_C8_C9']['C9']['source_x86'])==(531,158)
assert new['original_C8_C9']['C9']['wrong_original_mnemonics']==[]
assert new['original_C8_C9']['C9']['wrong_original_widths']==[]
assert new['original_C8_C9']['C9']['wrong_original_GPR_roles']==[]
assert new['original_C8_C9']['C9']['native_original_PE_targets_verified']==13
assert new['original_C8_C9']['C8']['wrong_original_widths']==[106,121,122]
assert new['original_C8_C9']['C8']['native_original_PE_targets_verified']==15
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_whole_game':'0x004AC040',
 'native_original_complete_CODE_B':TOTAL,'native_original_complete_x86':NX,
 'original_C9_native_handler':'0x004B02B9..004B04CC',
 'new_real_C9_natural_Cpp_native_B':531,'native_x86':158,
 'new_original_PE_typed_targets_verified':13,
 'C9_native_GPR_mnemonic_width_all_match':True,
 'whole_original_exact':False,'new_accepted_original_CODE_B':0,
 'mass_cold_replay':False,'source_control_profiles':rows
},indent=2)+'\n')
print('F949 original C9: 531B/158 x86 with all native mnemonics, widths and GPR roles, 13 true PE targets, inside 19,543B partial father. Whole game nonexact.')
