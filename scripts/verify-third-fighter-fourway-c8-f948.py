#!/usr/bin/env python3
"""F948: entire partial 82KB original father with true native C8 149-x86 source.

Regenerate from tracked F938/939/941/942/943 plus F947 CF/D0.
Compare previous C8 marker with real actor-specific native
source in TWO whole compiled VC7.1 partial father C++ units. Original
PE handler C8 539B/149 x86, 15 typed original external fields;
three honest source width mismatches due incomplete actual frame.
Check all 151 original afterRET case DIR32 refs and 522 DATA bytes.
Never claim a truncated partial father or inner case as original exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f948-third-native-C8';O.mkdir(parents=True,exist_ok=True)
BASE=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
PARTS=[
 (0x5D,94,'FighterThirdBossPair5D5EF939.inc'),
 (0x5E,95,None),
 (0x5F,96,'FighterThirdBossFacing5FF941.inc'),
 (0x60,97,'FighterThirdBossVolley6061F942.inc'),
 (0x61,98,None),
 (0x62,99,'FighterThirdBossSelector62F943.inc'),
 (0xCF,208,'FighterFallStateCFF647.inc'),
 (0xD0,209,'FighterReflectLandingD0F646.inc'),
]
source=BASE
for case,marker,filename in PARTS:
 old=f'        case 0x{case:X}: g_FighterProbeMarker = {marker}; break;'
 assert source.count(old)==1
 source=source.replace(old,(R/'probes'/filename).read_text() if filename else '',1)
assert source.count('extern float g_ThresholdAt0065782C;')==1
source=source.replace('extern float g_ThresholdAt0065782C;',
 'extern float g_ThresholdAt0065782C;\nextern float g_F748_SpeedScaleAt006590B8;\n'
 'extern float g_F948_C8UpperAt00657854;\nextern float g_F948_C8DragAt00658350;\n'
 'extern float g_F948_C8VolleyYAt00658268;',1)
needle=' void SpawnAt453C80(int,float,float,char,int);'
assert source.count(needle)==1
source=source.replace(needle,needle+
  ' void SpawnMixedAt453C80(int,int,float,char,int);'
  ' void ConfigureStormAt454BC0(int,int,int);',1)
old='        case 0xC8: g_FighterProbeMarker = 201; break;'
real=(R/'probes/FighterThirdBossFourWayC8F948.inc').read_text()
assert source.count(old)==1 and real.count('case 0xC8:')==1
variants={'F947-C8-original-placeholder':source,
          'F948-original-C8-Cpp':source.replace(old,real,1)}
sp=importlib.util.spec_from_file_location('f948reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
BASEADDR=0x4AC040;ORIGLEN=82796;ORIGX86=22721;DATA=1126
nativewhole=list(D.disasm(rd.pe_bytes_at(PE,BASEADDR,ORIGLEN),BASEADDR))
assert len(nativewhole)==ORIGX86 and nativewhole[2].op_str=='esp, 0x720'
assert nativewhole[3].mnemonic=='push' and nativewhole[3].op_str=='esi'
native_data=rd.pe_bytes_at(PE,BASEADDR+ORIGLEN,DATA)
lo,hi=0x4B009E,0x4B02B9
native=list(D.disasm(rd.pe_bytes_at(PE,lo,hi-lo),lo))
assert len(native)==149 and hi-lo==539
assert native[121].op_str=='dword ptr [ebp - 0x94], ecx'
assert native[122].op_str=='dword ptr [ebp - 0x94]'
assert native[106].mnemonic=='jne' and native[106].size==6
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(rx.findall(ins.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows={}
for tag,body in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(body)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for ins in D.disasm(code,0):
  I.append(ins)
  if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 mask=set();labels={}
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(x not in mask for x in range(off,off+4))
  mask.update(range(off,off+4))
  original_addr=int.from_bytes(native_data[off:off+4],'little')
  assert BASEADDR<=original_addr<BASEADDR+ORIGLEN
  labels.setdefault(original_addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(DATA) if i not in mask)
 assert lo in labels and hi in labels
 a,b=labels[lo],labels[hi]
 source_part=[x for x in I if a<=x.address<b]
 fields=[r for r in refs if a<=r['offset']<b]
 row={'whole_original_callable_CODE_B':ORIGLEN,'whole_original_x86':ORIGX86,
    'whole_source_partial_CODE_B':end,'whole_source_x86':len(I),
    'whole_source_stack_frame':I[2].op_str,
    'original_stack_frame':nativewhole[2].op_str,
    'original_0xC8_B':539,'original_0xC8_x86':149,
    'source_0xC8_B':b-a,'source_0xC8_x86':len(source_part),
    'source_0xC8_original_PE_target_fields_checked':0,
    'original_afterRET_DIR32_fields':151,'original_afterRET_nonfield_equal_B':522,
    'whole_original_exact':False}
 if len(source_part)==149:
  wrong_m=[i for i,(n,s) in enumerate(zip(native,source_part)) if n.mnemonic!=s.mnemonic]
  wrong_w=[i for i,(n,s) in enumerate(zip(native,source_part)) if n.size!=s.size]
  wrong_g=[i for i,(n,s) in enumerate(zip(native,source_part)) if roles(n)!=roles(s)]
  row.update({'native_wrong_mnemonic_ordinals':wrong_m,
    'native_wrong_width_ordinals':wrong_w,'native_wrong_GPR_roles':wrong_g})
  assert len(fields)==15
  nativebytes=rd.pe_bytes_at(PE,lo,539)
  original_fields=set()
  for ref in fields:
   j=next(i for i,x in enumerate(source_part) if x.address<=ref['offset']<x.address+x.size)
   delta=ref['offset']-source_part[j].address
   nativeoff=native[j].address-lo+delta
   assert ref['type'] in ('DIR32','REL32') and ref['addend']==0 and ref['local_symbol_offset'] is None
   assert all(k not in original_fields for k in range(nativeoff,nativeoff+4))
   original_fields.update(range(nativeoff,nativeoff+4))
   value=int.from_bytes(nativebytes[nativeoff:nativeoff+4],'little',signed=ref['type']=='REL32')
   dest=native[j].address+delta+4+value if ref['type']=='REL32' else value
   found=re.search('At([0-9a-fA-F]{6,8})',ref['symbol'])
   expected=int(found.group(1),16) if found else 0x6406AC if ref['symbol']=='__ftol2' else None
   assert dest==expected,(tag,j,ref['symbol'],hex(dest),expected)
  row['source_0xC8_original_PE_target_fields_checked']=len(fields)
  wrong_nonfield=[k for k in range(539) if k not in original_fields and
     # Native fields after offset shift cannot compare absolute bytes
     # directly unless source/native ordinal position is identical.
     k<(b-a) and nativebytes[k]!=code[a+k]]
  row['source_0xC8_original_remaining_nonfield_wrong_or_shifted']=len(wrong_nonfield)
 rows[tag]=row
 print(tag,'compiled full-partial CODE',end,'x86',len(I),
    'actual original C8',b-a,'B',len(source_part),'x86',
    'native role/width errors',len(row.get('native_wrong_GPR_roles',[])),
    row.get('native_wrong_width_ordinals'),'PE target fields',
    row['source_0xC8_original_PE_target_fields_checked'],flush=True)
old=rows['F947-C8-original-placeholder'];new=rows['F948-original-C8-Cpp']
assert (old['whole_source_partial_CODE_B'],old['source_0xC8_B'],old['source_0xC8_x86'])==(18513,15,2)
assert (new['whole_source_partial_CODE_B'],new['source_0xC8_B'],new['source_0xC8_x86'])==(19027,529,149)
assert new['native_wrong_mnemonic_ordinals']==[]
assert new['native_wrong_width_ordinals']==[106,121,122]
assert new['native_wrong_GPR_roles']==[]
assert new['source_0xC8_original_PE_target_fields_checked']==15
assert new['source_0xC8_B']+10==539
assert new['whole_source_stack_frame']=='esp, 0x40'
(O/'verified-summary.json').write_text(json.dumps({
 'original_native_whole_fighter':'0x004AC040',
 'original_native_82KB_function_CODE_B':ORIGLEN,
 'original_native_whole_x86':ORIGX86,
 'true_C8_original_start_end':['0x004B009E','0x004B02B9'],
 'source_has_actual_C8_cpp_instead_of_marker':True,
 'native_case_C8_total_GPR_mnemonic_mismatches':0,
 'native_C8_three_width_ordinal_diffs':[106,121,122],
 'true_original_native_call_global_PE_fields':15,
 'physical_0x94_native_integer_x87_temp_not_recovered':True,
 'whole_original_exact':False,'accepted_new_game_CODE_B':0,
 'mass_cold_replay':False,'compiled_complete_partial_sources':rows
},indent=2)+'\n')
print('F948: new original C8 149 ordered native x86 mnemonic and GPR roles, 15 actual original PE targets; current source 529B vs original 539B, because 0x720 frame, genuine -0x94 scratch and branch still nonnative. No accepted exact whole CODE.')
