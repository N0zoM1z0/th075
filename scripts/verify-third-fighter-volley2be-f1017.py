#!/usr/bin/env python3
"""F1017 real original 2BE, 1607B/471 native x86/50 actual PE fields.

Fresh-build TWO tracked ENTIRE original-shaped PARTIAL 82KB normal
VC7.1 fighter parents: F1016 prior marker and F1017 true
five 0x321+boolean &0x33F volley C++ source. Verify all native
mnemonic and widths, 50 physical PE targets, document 125
remaining original GPR-role instructions (not exact). Check
preceding/following native 2C0..2C3,2DB,2E5/2E6,303
and afterRET 151 DIR32 local cases/522 nonfield DATA B.
Do NOT credit inner case as exact original callable.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1017-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1016-prior-2BE-marker':R/'probes/FighterWhole004AC040F1016.cpp',
 'F1017-real-2BE':R/'probes/FighterWhole004AC040F1017.cpp'}
inc=(R/'probes/FighterThirdBossVolley2BEF1017.inc').read_text()
assert inc.count('case 0x2BE:')==1
assert inc.count('SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),')==5
assert inc.count('SpawnFloatXYAt453A70(0x33F,')==5
assert inc.count('g_F1017_VolleyYAt0065908C')==10
assert inc.count('SpawnAt453C80(0x73,')==1
assert sources['F1017-real-2BE'].read_text().count('#include "FighterThirdBossVolley2BEF1017.inc"')==1
sp=importlib.util.spec_from_file_location('rd1017',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
native_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(native_whole)==NX and native_whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={
 '2BE':(0x4BB1EA,0x4BB831,1607,471,50),
 '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2DB':(0x4BC8B1,0x4BD017,1894,548,38),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
 '303':(0x4BFDAB,0x4C01A1,1014,267,29)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 seq=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(seq)==nx and seq[-1].address+seq[-1].size==b
 native[k]=seq
n=native['2BE']
assert n[13].op_str=='0x453e20'
assert n[84].op_str=='dword ptr [0x657888]'
assert n[93].op_str=='dword ptr [0x658268]'
assert n[107].op_str=='0x453c80'
assert n[118].op_str=='0x453d40'
assert n[137].op_str=='0x46d000'
assert n[159].op_str=='0x455580'
assert all(n[j].op_str=='0x453a70' for j in (166,187,230,251,294,315,358,379,422,443))
assert n[-1].op_str=='0x4c03a7'
reg=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(reg.findall(i.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_whole_game_CODE_B':WHOLE,'original_whole_x86':NX,
  'whole_partial_CODE_B':ret,'whole_partial_x86':len(I),
  'partial_frame':I[2].op_str,'original_afterRET_DIR32':151,
  'native_nonfield_DATA_equal_B':522,'whole_original_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':sz,'native_original_x86':nx,
   'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnemonic_positions':mm,
    'wrong_native_width_positions':ww,'wrong_native_GPR_positions':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address;off=native[k][j].address-a+dt
     if not ww:assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     dest=native[k][j].address+dt+4+val if r['type']=='REL32' else val
     match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(match.group(1),16) if match else 0x6406AC if r['symbol']=='__ftol2' else None
     assert dest==expected,(label,k,j,r['symbol'],hex(dest),expected)
    item['native_original_PE_fields_verified']=nf
  row['cases'][k]=item
 rows[label]=row
 print(label,'whole original-shaped partial C++',ret,len(I),
       'native 2BE',row['cases']['2BE']['source_CODE_B'],row['cases']['2BE']['source_x86'],flush=True)
old=rows['F1016-prior-2BE-marker'];new=rows['F1017-real-2BE']
assert (old['whole_partial_CODE_B'],old['whole_partial_x86'])==(74630,20496)
assert (new['whole_partial_CODE_B'],new['whole_partial_x86'])==(76222,20965)
assert old['partial_frame']=='esp, 0x5c0' and new['partial_frame']=='esp, 0x5ec'
assert old['cases']['2BE']['source_CODE_B']==15
it=new['cases']['2BE']
assert (it['source_CODE_B'],it['source_x86'])==(1607,471)
assert it['wrong_native_mnemonic_positions']==it['wrong_native_width_positions']==[]
assert len(it['wrong_native_GPR_positions'])==125
assert it['native_original_PE_fields_verified']==50
for k in cases:
 if k=='2BE':continue
 it=new['cases'][k]
 assert it['wrong_native_mnemonic_positions']==it['wrong_native_width_positions']==it['wrong_native_GPR_positions']==[]
 assert it['native_original_PE_fields_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_original_fighter':'0x004AC040',
 'original_whole_callable_CODE_B':WHOLE,'native_whole_x86':NX,
 'genuine_native_2BE_CODE_B_x86':[1607,471],
 'all_original_2BE_mnemonics_widths_match':True,
 'native_2BE_remaining_wrong_GPR_instructions':125,
 'native_2BE_real_typed_PE_targets_verified':50,
 'previous_and_later_real_cases_GPR_roles_unchanged':True,
 'whole_original_exact':False,'new_original_accepted_exact_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_CPP_parent_profiles':rows
},indent=2)+'\n')
print('F1017 original 2BE native1607B/471x86/50 PE fields, all mnemonic/width, 125 GPR wrong, previous and later native game cases unchanged; whole 82KB NONEXACT.')
