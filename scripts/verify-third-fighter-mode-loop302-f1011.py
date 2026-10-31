#!/usr/bin/env python3
"""F1011 genuine native mode-selected sprite 302 and previous 2FB JMP repair.

Fresh normal VC7.1 compile TWO complete tracked original-shaped
PARTIAL 82KB fighters, F1009 prior 302 marker and F1011 native
real mode 302. Native original 1033B/279x86, 25 typed PE
call/global fields. Source matches all native mnemonic/GPR
positions, final shared-tail JMP 5B native versus short2B.
Real addition of 302 recovers previous 2FB last near JMP
width, while all previous native 2FA,2F9,2E6,2E5,2C0..3
remain source mnemonic/width/GPR aligned. Also full original
151 afterRET DIR32 and 522 nonfield DATA B.
Never credit incomplete giant game father as exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1011-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1009-prior-302-marker':R/'probes/FighterWhole004AC040F1009.cpp',
         'F1011-real-mode302':R/'probes/FighterWhole004AC040F1011.cpp'}
inc=(R/'probes/FighterThirdBossModes302F1011.inc').read_text()
assert inc.count('case 0x302:')==1
assert inc.count('SpawnFloatXYAt453A70(0x389,')==4
assert inc.count('g_F1004_ModeAt006714D0')==6
assert all(f'for (int shot=0;shot<{n};++shot)' in inc for n in (10,12,15,20))
assert sources['F1011-real-mode302'].read_text().count('#include "FighterThirdBossModes302F1011.inc"')==1
sp=importlib.util.spec_from_file_location('f1011reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;NATIVE_CODE=82796;NATIVE_X86=22721;DATA=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE_CODE),BASE))
assert len(whole)==NATIVE_X86 and whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+NATIVE_CODE,DATA)
cases={
 '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
 '2F9':(0x4BEC88,0x4BF16E,1254,326,33),
 '2FA':(0x4BF16E,0x4BF40E,672,186,18),
 '2FB':(0x4BF40E,0x4BF9A2,1428,411,33),
 '302':(0x4BF9A2,0x4BFDAB,1033,279,25)}
native={}
for key,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[key]=n
n=native['302']
assert n[9].op_str=='0x453e20'
assert n[16].op_str=='ecx, byte ptr [0x6714d0]'
assert n[26].op_str=='dword ptr [0x65782c]' and n[38].op_str=='dword ptr [0x65747c]'
assert n[64].op_str=='dword ptr [0x65782c]'
assert n[88].op_str=='0x455580' and n[90].op_str=='edx, byte ptr [0x6714d0]'
assert n[115].op_str=='5' and n[117].op_str=='0x453d40'
assert n[156].op_str=='0x453a70' and n[196].op_str=='0x453a70'
assert n[236].op_str=='0x453a70' and n[276].op_str=='0x453a70'
assert all(n[j].op_str=='0x389' for j in (154,194,234,274))
assert all(n[j].op_str=='dword ptr [0x65836c]' for j in (142,182,222,262))
assert n[-1].mnemonic=='jmp' and n[-1].op_str=='0x4c03a7' and n[-1].size==5
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(REG.findall(i.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=env,capture_output=True,text=True,timeout=345)
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
 lab={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+NATIVE_CODE
  lab.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in lab and b in lab for a,b,_,_,_ in cases.values())
 row={'original_whole_GAME_CODE_B':NATIVE_CODE,'original_whole_x86':NATIVE_X86,
      'partial_SOURCE_CODE_B':end,'partial_source_x86':len(I),
      'source_partial_frame':I[2].op_str,
      'native_afterRET_DIR32':151,'original_nonfield_DATA_equal_B':522,
      'whole_original_exact':False,'cases':{}}
 for key,(a,b,sz,nx,nf) in cases.items():
  lo,hi=lab[a],lab[b]
  seq=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':sz,'native_x86':nx,'source_B':hi-lo,'source_x86':len(seq)}
  if len(seq)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[key],seq)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[key],seq)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[key],seq)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,
                'wrong_native_GPR_roles':gg})
   if not mm:
    assert len(fields)==nf,(label,key,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-seq[j].address
     off=native[key][j].address-a+dt
     assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     orig=native[key][j].address+dt+4+value if r['type']=='REL32' else value
     match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(match.group(1),16) if match else 0x6406AC if r['symbol']=='__ftol2' else None
     assert orig==expected,(label,key,j,r['symbol'],hex(orig),expected)
    item['original_typed_PE_fields_verified']=nf
  row['cases'][key]=item
 rows[label]=row
 print(label,'whole PARTIAL',end,len(I),
       '2FB/302',[(k,row['cases'][k]['source_B'],row['cases'][k]['source_x86']) for k in ('2FB','302')],flush=True)
old=rows['F1009-prior-302-marker'];new=rows['F1011-real-mode302']
assert (old['partial_SOURCE_CODE_B'],old['partial_source_x86'])==(70201,19261)
assert (new['partial_SOURCE_CODE_B'],new['partial_source_x86'])==(71250,19538)
assert old['source_partial_frame']=='esp, 0x53c' and new['source_partial_frame']=='esp, 0x56c'
assert old['cases']['302']['source_B']==12
r=new['cases']['302']
assert (r['source_B'],r['source_x86'])==(1030,279)
assert r['wrong_native_mnemonics']==r['wrong_native_GPR_roles']==[]
assert r['wrong_native_widths']==[278]
assert r['original_typed_PE_fields_verified']==25
prev=old['cases']['2FB'];now=new['cases']['2FB']
assert (prev['source_B'],prev['source_x86'])==(1425,411)
assert prev['wrong_native_widths']==[410] and prev['wrong_native_GPR_roles']==[]
assert (now['source_B'],now['source_x86'])==(1428,411)
assert now['wrong_native_mnemonics']==now['wrong_native_widths']==now['wrong_native_GPR_roles']==[]
assert now['original_typed_PE_fields_verified']==33
for k in ('2C0','2C1','2C2','2C3','2E5','2E6','2F9','2FA'):
 r=new['cases'][k]
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPR_roles']==[]
 assert r['original_typed_PE_fields_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x004AC040',
 'original_complete_callable_CODE_B':NATIVE_CODE,'original_x86':NATIVE_X86,
 'native_302_CODE_B_x86':[1033,279],
 'natural_302_source_B_x86':[1030,279],
 'all_279_native_302_mnemonic_GPR_positions_match':True,
 'wrong_native_302_width_positions':[278],
 'original_typed_PE_targets_302_verified':25,
 'genuine_302_repairs_previous_2FB_shared_JMP_width':{'before':[410],'after':[]},
 'earlier_2C0_2C3_2E5_2E6_2F9_2FA_native_ROLES_preserved':True,
 'entire_original_callable_exact':False,'credited_new_full_GAME_CODE_B':0,
 'mass_cold_replay':False,'original_complete_partial_CPP_father_profiles':rows
},indent=2)+'\n')
print('F1011 original 302 1033B/279x86/25 PE, all GPR/mnemonic; last JMP width 5->2; real later 302 repairs previous 2FB near JMP and 411 roles. Full original 82KB NONEXACT.')
