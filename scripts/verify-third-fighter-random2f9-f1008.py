#!/usr/bin/env python3
"""F1008 original 2F9 real random volleys and following 2FA GPR repair.

Fresh normal VC7.1 compile two TRACKED ENTIRE 82KB original-shaped
PARTIAL fighters, F1007 prior marker and F1008 real native 2F9.
Original 2F9 1254B/326x86/33 genuine typed PE fields, all
mnemonic/width/GPR roles match; its actual source restores
following 2FA GPR debt 113 ->0 while its last shared JMP
5B native vs2B incomplete parent remains mismatched.
Verify original 151 afterRET DIR32/522 DATA and all
genuine preceding 2C0..2C3/2E5/2E6 original PE/GPR.
Never accept cropped game cases as exact callable CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1008-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1007-old-2F9-marker':R/'probes/FighterWhole004AC040F1007.cpp',
 'F1008-real-2F9':R/'probes/FighterWhole004AC040F1008.cpp'}
inc=(R/'probes/FighterThirdBossRandom2F9F1008.inc').read_text()
assert inc.count('case 0x2F9:')==1
assert inc.count('SpawnFloatXYAt453A70(0x38B,')==2
assert inc.count('SpawnSevenFloatAt453B50(0x38A,')==2
assert inc.count('g_F1008_CenterXAt006593D0')==2
assert inc.count('g_F1008_AlternateXAt00658370')==2
assert sources['F1008-real-2F9'].read_text().count('#include "FighterThirdBossRandom2F9F1008.inc"')==1
sp=importlib.util.spec_from_file_location('f1008rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;CODE_B=82796;X86=22721;AFTER=1126
nativewhole=list(D.disasm(rd.pe_bytes_at(PE,BASE,CODE_B),BASE))
assert len(nativewhole)==X86 and nativewhole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+CODE_B,AFTER)
cases={'2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
 '2F9':(0x4BEC88,0x4BF16E,1254,326,33),
 '2FA':(0x4BF16E,0x4BF40E,672,186,18)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(n)==nx and b-a==sz and n[-1].address+n[-1].size==b
 native[k]=n
n=native['2F9']
assert n[15].op_str=='0x455580' and n[21].op_str=='0x455580'
assert n[63].op_str=='dword ptr [0x6593d0]' and n[101].op_str=='dword ptr [0x658370]'
assert n[76].op_str=='0x453a70' and n[114].op_str=='0x453a70'
assert n[162].op_str=='0x453b50' and n[210].op_str=='0x453b50'
assert n[222].op_str=='eax, eax, 0x14'
assert n[265].op_str=='0x453b50'
assert n[273].op_str=='0x40fbb0'
assert n[-1].op_str=='0x4c03a7'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(rx.findall(i.op_str))
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
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1050:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==AFTER
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 lab={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+CODE_B
  lab.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+j]==after[j] for j in range(AFTER) if j not in mask)
 assert all(a in lab and b in lab for a,b,_,_,_ in cases.values())
 row={'original_entire_GAME_CODE_B':CODE_B,'original_whole_x86':X86,
 'partial_CPP_CODE_B':end,'partial_CPP_x86':len(I),
 'source_partial_frame':I[2].op_str,
 'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
 'original_whole_exact':False,'original_cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=lab[a],lab[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':sz,'native_original_x86':nx,'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,
                'wrong_native_GPR_roles':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address
     off=native[k][j].address-a+dt
     if k not in ('2FA',):assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+value if r['type']=='REL32' else value
     mt=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(mt.group(1),16) if mt else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_real_PE_target_fields_verified']=nf
  row['original_cases'][k]=item
 rows[label]=row
 print(label,'entire PARTIAL fighter',end,len(I),
  '2F9',row['original_cases']['2F9']['source_B'],row['original_cases']['2F9']['source_x86'],
  '2FA GPR wrong',len(row['original_cases']['2FA'].get('wrong_native_GPR_roles',[])),flush=True)
old=rows['F1007-old-2F9-marker'];new=rows['F1008-real-2F9']
assert (old['partial_CPP_CODE_B'],old['partial_CPP_x86'])==(67546,18528)
assert (new['partial_CPP_CODE_B'],new['partial_CPP_x86'])==(68785,18852)
assert old['source_partial_frame']=='esp, 0x4dc' and new['source_partial_frame']=='esp, 0x50c'
assert old['original_cases']['2F9']['source_B']==15
r=new['original_cases']['2F9']
assert (r['source_B'],r['source_x86'])==(1254,326)
assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPR_roles']==[]
assert r['native_real_PE_target_fields_verified']==33
prev=old['original_cases']['2FA'];now=new['original_cases']['2FA']
assert len(prev['wrong_native_GPR_roles'])==113 and prev['wrong_native_widths']==[185]
assert now['wrong_native_mnemonics']==now['wrong_native_GPR_roles']==[]
assert now['wrong_native_widths']==[185] and now['native_real_PE_target_fields_verified']==18
for k in ('2C0','2C1','2C2','2C3','2E5','2E6'):
 r=new['original_cases'][k]
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPR_roles']==[]
 assert r['native_real_PE_target_fields_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_original_game_fighter':'0x004AC040',
 'original_whole_callable_CODE_B':CODE_B,'native_whole_x86':X86,
 'real_original_2F9_B_x86':[1254,326],
 'original_2F9_typed_PE_targets_verified':33,
 'all_original_2F9_mnemonics_widths_GPRs_match':True,
 'real_2F9_repairs_following_2FA_GPR_deficit':[113,0],
 '2FA_remaining_single_shared_tail_JMP_width':[185],
 'all_2C0_2C3_2E5_2E6_native_GPR_and_PE_preserved':True,
 'whole_original_exact':False,'new_exact_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_original_shaped_father_profiles':rows
},indent=2)+'\n')
print('F1008 genuine native2F9 1254B/326x86/33 original PE, all mnemonic/width/GPR roles; following 2FA GPR 113->0; whole original fighter NONEXACT.')
