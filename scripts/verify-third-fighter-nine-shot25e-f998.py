#!/usr/bin/env python3
"""F998 native 25E nine-shot spread, and four later GPR-phase regressions.

Rebuild tracked F997 prior 25E marker vs F998 native 25E real source,
TWO ENTIRE pinned normal VC7.1 PARTIAL original-shaped 82KB fathers.
Original 25E 882B/236x86/24 typed PE targets, real signed stage4
mixed raw-X/float-Y shots, original float global references.
Independently recheck native prior 25B/25C/25D and following real
25F/260/261/262. Genuine 25E changes downstream GPR error count
0/0/0/0 -> 73/73/65/65, without changing native mnemonic/width.
All original 151 afterRET DIR32 and 522 nonfield bytes checked.
Entire original game fighter remains NONEXACT; no exact CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,struct,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f998-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F997-prior-marker':R/'probes/FighterWhole004AC040F997.cpp',
 'F998-real-nine-shot':R/'probes/FighterWhole004AC040F998.cpp'}
inc=(R/'probes/FighterThirdBossNineShot25EF998.inc').read_text()
assert inc.count('case 0x25E:')==1
assert inc.count('SpawnWithFloatAt453A70(0x342,')==9
assert inc.count('g_F970_YAt006590AC')==9
assert sources['F998-real-nine-shot'].read_text().count('#include "FighterThirdBossNineShot25EF998.inc"')==1
sp=importlib.util.spec_from_file_location('f998reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;CODE_B=82796;ORIG_X86=22721;DATA=1126
original_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,CODE_B),BASE))
assert len(original_whole)==ORIG_X86 and original_whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+CODE_B,DATA)
cases={
 '25B':(0x4B84BA,0x4B9327,3693,957,77),
 '25C':(0x4B9327,0x4B973A,1043,271,23),
 '25D':(0x4B973A,0x4BA229,2799,749,78),
 '25E':(0x4BA229,0x4BA59B,882,236,24),
 '25F':(0x4BA59B,0x4BA76D,466,114,9),
 '260':(0x4BA76D,0x4BA93F,466,114,9),
 '261':(0x4BA93F,0x4BAAA8,361,98,8),
 '262':(0x4BAAA8,0x4BAC11,361,98,8)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
n=native['25E']
angles=[]
for j,x in enumerate(n):
 if x.mnemonic=='mov' and '+ 0x314]' in x.op_str:
  m=re.search(r', (0x[0-9a-f]+|0)$',x.op_str);assert m
  bits=int(m.group(1),16) if m.group(1).startswith('0x') else 0
  angles.append((j,struct.unpack('<f',struct.pack('<I',bits))[0]))
assert angles==[(65+19*i,float(-28+7*i)) for i in range(9)]
assert [j for j,x in enumerate(n) if x.mnemonic=='call' and x.op_str=='0x453a70']==[82+19*i for i in range(9)]
assert all(n[80+19*i].op_str=='0x342' for i in range(9))
assert all(n[74+19*i].op_str=='dword ptr [0x6590ac]' for i in range(9))
assert all(n[78+19*i].mnemonic=='mov' and n[78+19*i].op_str.endswith('+ 0x44]') for i in range(9))
assert n[16].op_str=='dword ptr [0x657f74]' and n[21].op_str=='dword ptr [0x657f74]'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
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
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+CODE_B
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'native_whole_CODE_B':CODE_B,'native_whole_x86':ORIG_X86,
  'whole_partial_CPP_B':end,'partial_CPP_x86':len(I),
  'partial_stack_frame':I[2].op_str,
  'native_afterRET_DIR32':151,'native_afterRET_nonfield_equal_B':522,
  'whole_original_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   mm=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.mnemonic!=y.mnemonic]
   ww=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.size!=y.size]
   gg=[j for j,(x,y) in enumerate(zip(native[k],part)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,
                'wrong_native_GPR_roles':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-part[j].address
     off=native[k][j].address-a+delta
     if not ww:assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+delta+4+value if r['type']=='REL32' else value
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['original_PE_fields_checked']=nf
  row['cases'][k]=item
 results[label]=row
 print(label,'whole partial',end,len(I),
  '25E source',row['cases']['25E']['source_CODE_B'],row['cases']['25E']['source_x86'],flush=True)
old=results['F997-prior-marker'];new=results['F998-real-nine-shot']
assert (old['whole_partial_CPP_B'],old['partial_CPP_x86'])==(59728,16387)
assert (new['whole_partial_CPP_B'],new['partial_CPP_x86'])==(60595,16621)
assert old['partial_stack_frame']==new['partial_stack_frame']=='esp, 0x434'
assert old['cases']['25E']['source_CODE_B']==15
r=new['cases']['25E']
assert (r['source_CODE_B'],r['source_x86'])==(882,236)
assert r['wrong_native_mnemonics']==r['wrong_native_widths']==[]
assert len(r['wrong_native_GPR_roles'])==153
assert r['original_PE_fields_checked']==24
for k,newwrong in [('25F',73),('260',73),('261',65),('262',65)]:
 prev=old['cases'][k];now=new['cases'][k]
 assert prev['wrong_native_mnemonics']==prev['wrong_native_widths']==prev['wrong_native_GPR_roles']==[]
 assert now['wrong_native_mnemonics']==now['wrong_native_widths']==[]
 assert len(now['wrong_native_GPR_roles'])==newwrong
 assert now['original_PE_fields_checked']==cases[k][4]
for k,wrong in [('25B',577),('25C',162),('25D',477)]:
 item=new['cases'][k]
 assert item['wrong_native_mnemonics']==item['wrong_native_widths']==[]
 assert len(item['wrong_native_GPR_roles'])==wrong
 assert item['original_PE_fields_checked']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x004AC040',
 'original_whole_callable_CODE_B':CODE_B,'original_whole_x86':ORIG_X86,
 'native_real_25E_CODE_B_x86':[882,236],
 'native_25E_nine_angles_-28_to_28':True,
 'original_PE_target_fields_verified':24,
 'native_25E_mnemonic_width_errors':[0,0],
 'native_25E_wrong_GPR_roles':153,
 'genuine_25E_downstream_GPR_regression':{
  '25F':[0,73],'260':[0,73],'261':[0,65],'262':[0,65]},
 'native_case_geometry_unchanged_and_source_frame_constant':True,
 'whole_original_exact':False,'new_credited_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_partial_cpp_profiles':results
},indent=2)+'\n')
print('F998 genuine original25E 882B/236x86/24 PE. All native mnem/width, 153 GPR wrong; 4 following ten-shot states regress GPR phase 0 ->73/73/65/65. Whole NONEXACT.')
