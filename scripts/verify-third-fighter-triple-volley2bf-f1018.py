#!/usr/bin/env python3
"""F1018 real native 2BF 2167B/616 x86/65 genuine original PE targets.

Fresh-build two tracked ENTIRE original-shaped 82KB PARTIAL fighter
normal VC7.1 parents, F1017 with 2BF marker and F1018 with
genuine 5 triple-volley stages. All original native 616 mnemonic,
width AND GPR positions match, all 65 physical PE call/global
fields resolve. Preceding2BE keeps its original 125 GPR role
errors, no native opcode/width/PE regression. Verify all
later2C0..2C3/2DB/2E5/2E6/303 original x86, afterRET
151 DIR32 local cases and 522 nonfield DATA B.
No original whole callable exact GAME CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1018-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1017-prior-2BF-marker':R/'probes/FighterWhole004AC040F1017.cpp',
         'F1018-real-2BF':R/'probes/FighterWhole004AC040F1018.cpp'}
inc=(R/'probes/FighterThirdBossTripleVolley2BFF1018.inc').read_text()
assert inc.count('case 0x2BF:')==1
assert inc.count('SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),')==5
assert inc.count('SpawnFloatXYAt453A70(0x340,')==5
assert inc.count('SpawnFloatXYAt453A70(0x341,')==5
assert inc.count('g_F1018_ThirdYAt0065784C')==5
assert inc.count('StartAnimationAt46D000(0xC)')==5
assert sources['F1018-real-2BF'].read_text().count('#include "FighterThirdBossTripleVolley2BFF1018.inc"')==1
sp=importlib.util.spec_from_file_location('reader1018',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
full=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(full)==NX and full[2].op_str=='esp, 0x720'
post=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={
 '2BE':(0x4BB1EA,0x4BB831,1607,471,50),
 '2BF':(0x4BB831,0x4BC0A8,2167,616,65),
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
n=native['2BF']
assert n[13].op_str=='0x453e20'
assert n[93].op_str=='dword ptr [0x658268]'
assert n[107].op_str=='0x453c80' and n[105].op_str=='0x74'
assert n[122].op_str.endswith('+ 0x54], 0x3f666666')
assert n[163].op_str=='0x453a70' and n[184].op_str=='0x453a70' and n[213].op_str=='0x453a70'
assert n[191].op_str=='dword ptr [0x65784c]'
assert n[196].op_str=='0x455580'
assert all(n[j].op_str=='0x453a70' for j in (256,277,306,349,370,399,442,463,492,535,556,585))
assert n[-1].op_str=='0x4c03a7'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(RX.findall(i.op_str))
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
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 lab={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(post[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  lab.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==post[i] for i in range(DATA) if i not in mask)
 assert all(a in lab and b in lab for a,b,_,_,_ in cases.values())
 row={'original_complete_GAME_CODE_B':WHOLE,'original_whole_x86':NX,
      'partial_generated_CODE_B':end,'partial_x86':len(I),
      'partial_source_frame':I[2].op_str,
      'native_afterRET_DIR32':151,'native_afterRET_nonfield_equal_B':522,
      'original_whole_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=lab[a],lab[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_x86':nx,'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,'wrong_native_GPRs':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address;off=native[k][j].address-a+dt
     if not ww:assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     v=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     dest=native[k][j].address+dt+4+v if r['type']=='REL32' else v
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     exp=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert dest==exp,(label,k,j,r['symbol'],hex(dest),exp)
    item['original_real_PE_targets_verified']=nf
  row['cases'][k]=item
 rows[label]=row
 print(label,'whole PARTIAL C++',end,len(I),'2BF',row['cases']['2BF']['source_B'],
       row['cases']['2BF']['source_x86'],flush=True)
old=rows['F1017-prior-2BF-marker'];new=rows['F1018-real-2BF']
assert (old['partial_generated_CODE_B'],old['partial_x86'])==(76222,20965)
assert (new['partial_generated_CODE_B'],new['partial_x86'])==(78374,21579)
assert old['partial_source_frame']=='esp, 0x5ec' and new['partial_source_frame']=='esp, 0x654'
assert old['cases']['2BF']['source_B']==15
it=new['cases']['2BF']
assert (it['source_B'],it['source_x86'])==(2167,616)
assert it['wrong_native_mnemonics']==it['wrong_native_widths']==it['wrong_native_GPRs']==[]
assert it['original_real_PE_targets_verified']==65
prior=new['cases']['2BE']
assert prior['wrong_native_mnemonics']==prior['wrong_native_widths']==[]
assert len(prior['wrong_native_GPRs'])==125
assert prior['original_real_PE_targets_verified']==50
for k in cases:
 if k in ('2BE','2BF'):continue
 it=new['cases'][k]
 assert it['wrong_native_mnemonics']==it['wrong_native_widths']==it['wrong_native_GPRs']==[]
 assert it['original_real_PE_targets_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_SHA_pinned_fighter':'0x004AC040',
 'original_entire_callable_GAME_CODE_B':WHOLE,'native_whole_x86':NX,
 'native_original_2BF_CODE_B_x86':[2167,616],
 'original_2BF_65_typed_PE_targets_checked':True,
 'all_616_native_original_mnemonics_widths_GPR_roles_match':True,
 'preceding_real_2BE_GPR_role_deficit_persists':125,
 'all_later_2C0_2C3_2DB_2E5_2E6_303_native_GPR_roles_preserved':True,
 'native_actual_five_triple_volley_stages':True,
 'original_whole_exact':False,'new_credited_exact_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_partial_parent_profiles':rows
},indent=2)+'\n')
print('F1018 real2BF 2167B/616x86 all mnemonic/width/GPR roles and 65 original PE targets; prior2BE retains 125 GPR debt, all later native cases unchanged. Whole 82KB NONEXACT.')
