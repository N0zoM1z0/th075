#!/usr/bin/env python3
"""F943: recover original action0x62 in partial 82KB fighter as C++.

Compare fresh complete natural VC7.1 parents (F942 marker and F943
real 0x62) against original SHA-pinned PE. Verify original 87B/25 x86,
four genuine PE/COFF game call targets, neighboring 7 real cases,
151 original afterRET local jump labels and 522 nonfield DATA bytes.
No separate case accepted as independently callable original CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,os,json,sys,re,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f943-third-original-selector';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
pair=(R/'probes/FighterThirdBossPair5D5EF939.inc').read_text()
facing=(R/'probes/FighterThirdBossFacing5FF941.inc').read_text()
volley=(R/'probes/FighterThirdBossVolley6061F942.inc').read_text()
selector=(R/'probes/FighterThirdBossSelector62F943.inc').read_text()
for action,code in ((0x5D,94),(0x5E,95),(0x5F,96),(0x60,97),(0x61,98),(0x62,99)):
 assert base.count(f'        case 0x{action:X}: g_FighterProbeMarker = {code}; break;')==1
original=base.replace('        case 0x5D: g_FighterProbeMarker = 94; break;',pair,1)
original=original.replace('        case 0x5E: g_FighterProbeMarker = 95; break;','',1)
original=original.replace('        case 0x5F: g_FighterProbeMarker = 96; break;',facing,1)
original=original.replace('        case 0x60: g_FighterProbeMarker = 97; break;',volley,1)
original=original.replace('        case 0x61: g_FighterProbeMarker = 98; break;','',1)
assert original.count('extern float g_ThresholdAt0065782C;')==1
original=original.replace('extern float g_ThresholdAt0065782C;',
 'extern float g_ThresholdAt0065782C;\nextern float g_F748_SpeedScaleAt006590B8;',1)
nextsource=original.replace('        case 0x62: g_FighterProbeMarker = 99; break;',selector,1)
assert nextsource!=original
sp=importlib.util.spec_from_file_location('reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
start=0x4AC040;total=82796;nx=22721;DATA=1126
N=list(D.disasm(rd.pe_bytes_at(PE,start,total),start))
assert len(N)==nx
physical={
'0x58':(0x4ADD25,0x4ADEFA,469,135,17),
'0x59':(0x4ADEFA,0x4AE05E,356,95,16),
'0x5D':(0x4AE05E,0x4AE1AF,337,101,8),
'0x5E':(0x4AE1AF,0x4AE300,337,101,8),
'0x5F':(0x4AE300,0x4AE390,144,44,3),
'0x60':(0x4AE390,0x4AE5B9,553,158,10),
'0x61':(0x4AE5B9,0x4AE7E2,553,158,10),
'0x62':(0x4AE7E2,0x4AE839,87,25,4),
}
native={}
for key,(lo,hi,n,nx_,r) in physical.items():
 v=list(D.disasm(rd.pe_bytes_at(PE,lo,n),lo))
 assert len(v)==nx_ and hi-lo==n
 native[key]=v
# Original GAME action62 is NOT the longer resource test 62 of 58KB
# original 00543210. Verify its actual source semantic constants.
x=native['0x62']
assert [(x[i].mnemonic,x[i].op_str) for i in (7,14,21)]==[
 ('push','0x5f'),('push','0x5d'),('push','0x5e')]
assert x[12].op_str=='edx, 1' and x[19].op_str=='ecx, 2'
assert [x[i].op_str for i in (1,9,16,23)]==[
 '0x40fa30','0x40fac0','0x40fac0','0x40fac0']
original_data=rd.pe_bytes_at(PE,start+total,DATA)
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda i:tuple(rx.findall(i.op_str))
rows={}
for name,source in [('F942-original-62-marker',original),('F943-real-62-selector',nextsource)]:
 cpp=O/(name+'.cpp');obj=O/(name+'.obj')
 cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
    cwd=R,env=E,capture_output=True,text=True,timeout=330)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 length=I[-1].address+I[-1].size
 assert len(code)-length==DATA
 table=[r for r in refs if r['offset']>=length]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-length
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  target=int.from_bytes(original_data[off:off+4],'little')
  assert start<=target<start+total
  labels.setdefault(target,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[length+j]==original_data[j] for j in range(DATA) if j not in mask)
 row={'whole_partial_source_CODE_B':length,'whole_partial_source_x86':len(I),
      'source_COFF_fields':len(refs),'original_whole_CODE_B':total,
      'original_whole_x86':nx,'original_afterRET_DATA_B':DATA,
      'original_afterRET_DIR32_labels':151,
      'original_afterRET_nonfield_equal_B':522,'real_cases':{},
      'whole_original_exact':False}
 for action,(lo,hi,n,nx_,nrefs) in physical.items():
  a,b=labels[lo],labels[hi]
  s=[i for i in I if a<=i.address<b]
  o=native[action];refs_part=[r for r in refs if a<=r['offset']<b]
  record={'native_CODE_B':n,'native_x86':nx_,
          'source_CODE_B':b-a,'source_x86':len(s)}
  if b-a==n and len(s)==nx_:
   m=[i for i,(x,y) in enumerate(zip(o,s)) if x.mnemonic!=y.mnemonic]
   w=[i for i,(x,y) in enumerate(zip(o,s)) if x.size!=y.size]
   g=[i for i,(x,y) in enumerate(zip(o,s)) if role(x)!=role(y)]
   record.update({'wrong_mnemonic_ordinals':m,
                  'wrong_width_ordinals':w,
                  'wrong_GPR_ordinals':g})
   if not m and not w:
    assert len(refs_part)==nrefs,(action,len(refs_part),nrefs)
    pebytes=rd.pe_bytes_at(PE,lo,n)
    for r in refs_part:
     j=next(k for k,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-s[j].address
     off=o[j].address-lo+delta
     assert off==r['offset']-a
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     v=int.from_bytes(pebytes[off:off+4],'little',signed=r['type']=='REL32')
     target=(o[j].address+delta+4+v if r['type']=='REL32' else v)
     expected_match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=(int(expected_match.group(1),16) if expected_match else
                 0x6406AC if r['symbol']=='__ftol2' else None)
     assert target==expected,(action,j,r['symbol'],hex(target),expected)
    record['native_external_PE_fields_verified']=len(refs_part)
  row['real_cases'][action]=record
 rows[name]=row
 print(name,'whole',length,len(I),'0x62 B/x86',
    row['real_cases']['0x62']['source_CODE_B'],row['real_cases']['0x62']['source_x86'],
    'PE fields',row['real_cases']['0x62'].get('native_external_PE_fields_verified',0),flush=True)
old=rows['F942-original-62-marker'];new=rows['F943-real-62-selector']
assert (old['whole_partial_source_CODE_B'],old['whole_partial_source_x86'])==(18161,4832)
assert (new['whole_partial_source_CODE_B'],new['whole_partial_source_x86'])==(18234,4855)
assert (old['real_cases']['0x62']['source_CODE_B'],old['real_cases']['0x62']['source_x86'])==(15,2)
assert (new['real_cases']['0x62']['source_CODE_B'],new['real_cases']['0x62']['source_x86'])==(87,25)
assert new['real_cases']['0x62']['wrong_mnemonic_ordinals']==[]
assert new['real_cases']['0x62']['wrong_width_ordinals']==[]
assert new['real_cases']['0x62']['native_external_PE_fields_verified']==4
assert len(new['real_cases']['0x62']['wrong_GPR_ordinals'])>0
for action in physical:
 if action=='0x62':continue
 assert new['real_cases'][action]['source_CODE_B']==physical[action][2]
 assert new['real_cases'][action]['native_external_PE_fields_verified']==physical[action][4]
assert new['real_cases']['0x60']['wrong_GPR_ordinals']==[]
assert new['real_cases']['0x61']['wrong_GPR_ordinals']==[]
(O/'verified-summary.json').write_text(json.dumps({
 'original_whole_Japanese_game_fighter':'0x004AC040','original_whole_CODE_B':total,
 'original_whole_x86':nx,'actual_native_state62':'0x004AE7E2..004AE839',
 'original_state62_B':87,'original_state62_x86':25,
 'original_state62_PE_fields':4,'tracked_original_state62_Cpp_recovered':True,
 'source_partial_whole_original_exact':False,'new_accepted_whole_original_CODE_B':0,
 'mass_cold_replay':False,'partial_whole_source_profiles':rows,
},indent=2)+'\n')
print('F943 original 004AC040 0x62 real action/selector 87B/25-x86/4 true original PE targets in whole 18,234B partial C++; native mnemonics and widths align, GPR/this EBP still nonexact.')
