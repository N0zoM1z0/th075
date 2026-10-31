#!/usr/bin/env python3
"""F961 real original 82KB fighter 12F and 130, plus original 12C/D/E.

Build TRACKED F959 and F961 cumulative partial whole original-shaped
fighters under pinned native VC7.1. Source 12F:207B/59 x86/6 native
PE fields, 130:265B/81x86/6 fields. Verify true original PE case
boundaries, x86 mnemonic/width/GPR roles, all 31 source fields from
12C through 130, the 12C (unlabeled) previous D2 terminus, and
all 151 original afterRET DIR32 and 522 native DATA bytes.
No whole or internal exact CODE acceptance.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f961-original-stage-proof';O.mkdir(parents=True,exist_ok=True)
src={
 'F959-old-12F130-markers':R/'probes/FighterWhole004AC040F959.cpp',
 'F961-real-12F130':R/'probes/FighterWhole004AC040F961.cpp'}
inc=(R/'probes/FighterThirdBossStage12F130F961.inc').read_text()
assert inc.count('case 0x12F:')==inc.count('case 0x130:')==1
assert src['F961-real-12F130'].read_text().count('#include "FighterThirdBossStage12F130F961.inc"')==1
sp=importlib.util.spec_from_file_location('f961reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;FULL_X86=22721;DATA=1126
N=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(N)==FULL_X86 and N[-1].address+N[-1].size==BASE+WHOLE
after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
physical={
 'D2':(0x4B0F3E,0x4B1039,251,74,0),
 '12C':(0x4B1039,0x4B1108,207,59,6),
 '12D':(0x4B1108,0x4B11E3,219,61,6),
 '12E':(0x4B11E3,0x4B12F1,270,82,7),
 '12F':(0x4B12F1,0x4B13C0,207,59,6),
 '130':(0x4B13C0,0x4B14C9,265,81,6),
 '131':(0x4B14C9,0x4B1593,202,58,5),
}
native={}
for key,(a,b,n,nx,fields) in physical.items():
 v=list(D.disasm(rd.pe_bytes_at(PE,a,n),a))
 assert b-a==n and len(v)==nx and v[-1].address+v[-1].size==b
 native[key]=v
assert native['12F'][55].op_str=='0x1c'
assert native['130'][54].op_str=='0x1c'
assert native['130'][77].op_str=='0x334'
assert native['130'][79].op_str=='0x453b50'
assert not any(int.from_bytes(after[i:i+4],'little')==0x4B1039
               for i in range(DATA-3))
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows={}
for name,cpp in src.items():
 obj=O/(name+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 records=[r for r in refs if r['offset']>=end]
 assert len(records)==151
 labels={};mask=set()
 for r in records:
  k=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(k,k+4))
  mask.update(range(k,k+4))
  native_va=int.from_bytes(after[k:k+4],'little')
  assert BASE<=native_va<BASE+WHOLE
  labels.setdefault(native_va,r['local_symbol_offset'])
 assert len(mask)==151*4 and DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert 0x4B1039 not in labels
 assert all(a in labels for k,(a,b,_,_,_) in physical.items() if k not in ('12C','131'))
 assert 0x4B14C9 in labels
 d2start=labels[0x4B0F3E]
 index=next(i for i,x in enumerate(I) if x.address==d2start)
 d2=I[index:index+74]
 d2end=d2[-1].address+d2[-1].size
 assert len(d2)==74 and d2end-d2start==251
 assert [x.mnemonic for x in d2]==[x.mnemonic for x in native['D2']]
 assert [x.size for x in d2]==[x.size for x in native['D2']]
 row={'whole_native_GAME_CODE_B':WHOLE,'whole_native_GAME_x86':FULL_X86,
  'whole_partial_CPP_B':end,'whole_partial_CPP_x86':len(I),
  'original_D2_real_251B_terminus':True,'native_12C_without_afterRET_label':True,
  'original_afterRET_DIR32_labels':151,'original_afterRET_nonfield_exact_B':522,
  'whole_CPP_COFF_relocation_count':len(refs),'states':{},
  'whole_original_exact':False}
 for k in ('12C','12D','12E','12F','130'):
  a,b,size,nx,nfields=physical[k]
  lo=d2end if k=='12C' else labels[a]
  hi=labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  record={'native_GAME_CODE_B':size,'native_x86':nx,
          'source_CPP_CODE_B':hi-lo,'source_x86':len(s),
          'native_PE_target_fields_verified':0}
  if len(s)==nx and hi-lo==size:
   m=[j for j,(x,y) in enumerate(zip(native[k],s)) if x.mnemonic!=y.mnemonic]
   w=[j for j,(x,y) in enumerate(zip(native[k],s)) if x.size!=y.size]
   g=[j for j,(x,y) in enumerate(zip(native[k],s)) if roles(x)!=roles(y)]
   record.update({'bad_original_mnemonic_ordinals':m,'bad_original_width_ordinals':w,
                  'bad_original_GPR_ordinals':g})
   if not m and not w:
    assert len(fields)==nfields
    raw=rd.pe_bytes_at(PE,a,size)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address;orig_off=native[k][j].address-a+dt
     assert orig_off==r['offset']-lo
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[orig_off:orig_off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+value if r['type']=='REL32' else value
     ss=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(ss.group(1),16) if ss else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(k,j,r['symbol'],hex(target),expected)
    record['native_PE_target_fields_verified']=len(fields)
  row['states'][k]=record
 rows[name]=row
 print(name,'whole',end,len(I),'12F/130 C++',
   [(k,row['states'][k]['source_CPP_CODE_B'],row['states'][k]['source_x86'])
    for k in ('12F','130')],flush=True)
old=rows['F959-old-12F130-markers'];new=rows['F961-real-12F130']
assert (old['whole_partial_CPP_B'],old['whole_partial_CPP_x86'])==(22267,6055)
assert (new['whole_partial_CPP_B'],new['whole_partial_CPP_x86'])==(22709,6191)
for k in ('12C','12D','12E','12F','130'):
 n=new['states'][k]
 assert (n['source_CPP_CODE_B'],n['source_x86'])==physical[k][2:4]
 assert n['bad_original_mnemonic_ordinals']==n['bad_original_width_ordinals']==n['bad_original_GPR_ordinals']==[]
 assert n['native_PE_target_fields_verified']==physical[k][4]
assert old['states']['12F']['source_CPP_CODE_B']==old['states']['130']['source_CPP_CODE_B']==15
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_game_fighter':'0x004AC040','original_whole_CODE_B':WHOLE,
 'original_whole_x86':FULL_X86,'new_real_12F_B_x86':[207,59],
 'new_real_130_B_x86':[265,81],'new_12F_130_typed_PE_fields':12,
 'consecutive_real_12C_D_E_F_130_B_x86':[207+219+270+207+265,59+61+82+59+81],
 'five_real_states_original_native_PE_targets':31,
 'all_five_original_mnemonic_width_GPR_roles_match':True,
 'native_12C_missing_jump_table_entry_preserved':True,
 'whole_original_game_exact':False,'new_accepted_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_source_profiles':rows
},indent=2)+'\n')
print('F961 original 004AC040: real 12F 207B/59 and 130 265B/81 with 12 typed PE targets; 12C-D-E-F-130 combined 1168B/342 x86/31 PE targets all positional native roles aligned in whole 22,709B partial source. Giant NONEXACT.')
