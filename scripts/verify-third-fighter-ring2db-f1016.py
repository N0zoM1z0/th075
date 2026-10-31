#!/usr/bin/env python3
"""F1016 original Japanese 2DB: 1894B/548 x86 and 38 real PE targets.

Fresh normal VC7.1 build TWO tracked ENTIRE original-shaped PARTIAL
82KB fighter C++ sources: F1014 prior 2DB marker and F1016 real
randomized ring source. Original native stage11 two 36x 0x385
ring shot loops, true native007 float Y, original actor facing
memory FCOMP, six real 0x338..0x33D and random0x33E.
Every native positional mnemonic, x86 width AND GPR role
matches, and 38 independently typed original PE call/global
fields resolve correctly. Check earlier 2C0..2C3 and later
2E5/2E6/2F9..303, 151 true original afterRET DIR32
and 522 nonfield DATA B. Whole giant callable remains NONEXACT.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1016-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1014-prior-2DB-marker':R/'probes/FighterWhole004AC040F1014.cpp',
         'F1016-real-2DB':R/'probes/FighterWhole004AC040F1016.cpp'}
inc=(R/'probes/FighterThirdBossRing2DBF1016.inc').read_text()
assert inc.count('case 0x2DB:')==1
assert inc.count('SpawnFloatXYAt453A70(0x385,')==2
assert inc.count('g_F1016_RingYAt00659460')==2
assert inc.count('for (int shot=0;shot<360;shot+=10)')==2
assert inc.count('SpawnSevenFloatAt453B50(0x')==7
assert inc.count('reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44')==1
assert sources['F1016-real-2DB'].read_text().count('#include "FighterThirdBossRing2DBF1016.inc"')==1
sp=importlib.util.spec_from_file_location('reader1016',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
original_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original_whole)==NX and original_whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={
 '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2DB':(0x4BC8B1,0x4BD017,1894,548,38),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
 '2F9':(0x4BEC88,0x4BF16E,1254,326,33),
 '2FA':(0x4BF16E,0x4BF40E,672,186,18),
 '2FB':(0x4BF40E,0x4BF9A2,1428,411,33),
 '302':(0x4BF9A2,0x4BFDAB,1033,279,25),
 '303':(0x4BFDAB,0x4C01A1,1014,267,29)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(n)==nx and b-a==sz and n[-1].address+n[-1].size==b
 native[k]=n
n=native['2DB']
assert n[9].op_str=='0x453e20'
assert n[23].op_str.endswith('+ 0x5c], 0x3e4ccccd')
assert n[78].mnemonic=='fcomp' and n[78].op_str.endswith('+ 0x44]')
assert n[234].op_str=='0x453b50' and n[232].op_str=='0x33e'
assert [n[j].op_str for j in (276,297,318,339,360,381)]==['0x453b50']*6
assert [n[j].op_str for j in (274,295,316,337,358,379)]==list(map(hex,range(0x338,0x33e)))
assert n[444].mnemonic=='fild' and n[478].mnemonic=='fild'
assert n[469].op_str==n[503].op_str=='0x453a70'
assert n[455].op_str==n[489].op_str=='dword ptr [0x659460]'
assert n[-1].op_str=='0x4c03a7'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
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
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-970:]
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
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_whole_GAME_CODE_B':WHOLE,'native_whole_x86':NX,
  'partial_generated_CODE_B':end,'partial_generated_x86':len(I),
  'partial_compiler_frame':I[2].op_str,
  'original_afterRET_DIR32':151,'native_nonfield_DATA_equal_B':522,
  'whole_original_exact':False,'real_cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnem':mm,'wrong_native_width':ww,'wrong_native_GPR':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    physical=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     off=r['offset']-s[j].address;nativeoff=native[k][j].address-a+off
     if not ww:assert nativeoff==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     num=int.from_bytes(physical[nativeoff:nativeoff+4],'little',signed=r['type']=='REL32')
     dest=native[k][j].address+off+4+num if r['type']=='REL32' else num
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert dest==expected,(label,k,j,r['symbol'],hex(dest),expected)
    item['original_real_PE_targets_verified']=nf
  row['real_cases'][k]=item
 rows[label]=row
 print(label,'whole partial father',end,len(I),
 '2DB native',row['real_cases']['2DB']['source_CODE_B'],row['real_cases']['2DB']['source_x86'],flush=True)
old=rows['F1014-prior-2DB-marker'];new=rows['F1016-real-2DB']
assert (old['partial_generated_CODE_B'],old['partial_generated_x86'])==(72739,19950)
assert (new['partial_generated_CODE_B'],new['partial_generated_x86'])==(74630,20496)
assert old['partial_compiler_frame']=='esp, 0x584' and new['partial_compiler_frame']=='esp, 0x5c0'
assert old['real_cases']['2DB']['source_CODE_B']==15
r=new['real_cases']['2DB']
assert (r['source_CODE_B'],r['source_x86'])==(1894,548)
assert r['wrong_native_mnem']==r['wrong_native_width']==r['wrong_native_GPR']==[]
assert r['original_real_PE_targets_verified']==38
for k in cases:
 if k=='2DB':continue
 r=new['real_cases'][k]
 assert r['wrong_native_mnem']==r['wrong_native_width']==r['wrong_native_GPR']==[]
 assert r['original_real_PE_targets_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_original_fighter':'0x004AC040',
 'original_whole_callable_GAME_CODE_B':WHOLE,'original_x86':NX,
 'original_native_2DB_CODE_B_x86':[1894,548],
 'all_548_original_mnemonics_widths_GPR_roles_match':True,
 'native_2DB_original_typed_PE_targets_checked':38,
 'two_real_36_shot_0x385_ring_loops':True,
 'original_2DB_ring_speed_float_values':[5.0,10.0],
 'all_prior_and_later_2C0_2C3_2E5_2E6_2F9_303_native_roles_preserved':True,
 'whole_original_exact':False,'newly_credited_exact_GAME_CODE_B':0,
 'mass_cold_replay':False,'normal_whole_partial_parent_profiles':rows
},indent=2)+'\n')
print('F1016 true original 2DB 1894B/548x86/38 PE; all native opcode/width/GPR roles, before/after entire original-shaped partial father evidence; original game giant NONEXACT.')
