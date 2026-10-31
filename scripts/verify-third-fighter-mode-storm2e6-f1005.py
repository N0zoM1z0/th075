#!/usr/bin/env python3
"""F1005 original 2E6 590-x86 mode-dependent storm, 47 real PE targets.

Fresh-compile TWO TRACKED ENTIRE normal VC7.1 82KB original-shaped
PARTIAL parents, previous F1004 marker and F1005 genuine original
C++: 12/20/30/40 native 0x387 loops and six independent 0x338-33D
seven-arg sprites. The native 2058B/590x86 2E6 all mnemonics/GPR
roles match; only final shared-parent-tail JMP width differs 5 vs 2
because the 82KB father is incomplete. Check 47 original real PE
target fields and all 151 original afterRET DIR32 plus 522 nonfield
DATA B. Prior 2E5 and 2C0..2C3 source GPR phase stays native.
DO NOT accept internal case as independent complete GAME CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1005-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1004-prior-2E6-marker':R/'probes/FighterWhole004AC040F1004.cpp',
         'F1005-real-mode-storm':R/'probes/FighterWhole004AC040F1005.cpp'}
inc=(R/'probes/FighterThirdBossModeStorm2E6F1005.inc').read_text()
assert inc.count('case 0x2E6:')==1
assert inc.count('SpawnFloatXYAt453A70(0x387,')==4
assert inc.count('SpawnSevenFloatAt453B50(0x')==7
assert inc.count('reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44')==1
assert all(f'for (int shot=0;shot<{n};++shot)' in inc for n in (12,20,30,40))
assert sources['F1005-real-mode-storm'].read_text().count('#include "FighterThirdBossModeStorm2E6F1005.inc"')==1
sp=importlib.util.spec_from_file_location('f1005reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;ORIG_X86=22721;AFTER=1126
full=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(full)==ORIG_X86 and full[2].op_str=='esp, 0x720'
native_post=rd.pe_bytes_at(PE,BASE+WHOLE,AFTER)
cases={
 '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47)}
native={}
for key,(a,b,sz,nx,nf) in cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(I)==nx and I[-1].address+I[-1].size==b
 native[key]=I
n=native['2E6']
assert n[80].mnemonic=='fcomp' and n[80].op_str.endswith('+ 0x44]')
assert n[115].op_str=='dword ptr [0x65782c]'
assert n[157].op_str=='dword ptr [0x657cbc]'
assert n[176].op_str=='dword ptr [0x658264]'
assert n[199].op_str=='edx, byte ptr [0x6714d0]'
assert [n[x].op_str for x in (235,273,311,349)]==['0x453a70']*4
assert [n[x].op_str for x in (401,422,443,464,485,506)]==['0x453b50']*6
assert all(n[x].op_str=='dword ptr [0x659490]' for x in (387,408,429,450,471,492))
assert n[-1].mnemonic=='jmp' and n[-1].op_str=='0x4c03a7' and n[-1].size==5
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
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
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==AFTER
 tail=[r for r in refs if r['offset']>=end]
 assert len(tail)==151
 lab={};mask=set()
 for r in tail:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(native_post[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  lab.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+j]==native_post[j] for j in range(AFTER) if j not in mask)
 assert all(a in lab and b in lab for a,b,_,_,_ in cases.values())
 row={'native_original_whole_B':WHOLE,'native_original_x86':ORIG_X86,
      'source_whole_partial_B':end,'source_whole_partial_x86':len(I),
      'source_partial_frame':I[2].op_str,
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'original_whole_exact':False,'cases':{}}
 for key,(a,b,sz,nx,nf) in cases.items():
  lo,hi=lab[a],lab[b]
  S=[x for x in I if lo<=x.address<hi]
  phys=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':sz,'native_original_x86':nx,
        'source_B':hi-lo,'source_x86':len(S)}
  if len(S)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[key],S)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[key],S)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[key],S)) if roles(n)!=roles(x)]
   item.update({'wrong_original_mnemonic_ordinals':mm,'wrong_original_width_ordinals':ww,
                'wrong_original_GPR_ordinals':gg})
   if not mm:
    assert len(phys)==nf,(label,key,len(phys),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in phys:
     j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-S[j].address
     off=native[key][j].address-a+dt
     if not ww or key=='2E6': assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[key][j].address+dt+4+value if r['type']=='REL32' else value
     regex=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(regex.group(1),16) if regex else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,key,j,r['symbol'],hex(target),expected)
    item['native_original_PE_fields_verified']=nf
  row['cases'][key]=item
 rows[label]=row
 print(label,'whole PARTIAL source',end,len(I),
 'native2E6',row['cases']['2E6']['source_B'],row['cases']['2E6']['source_x86'],flush=True)
old=rows['F1004-prior-2E6-marker'];new=rows['F1005-real-mode-storm']
assert (old['source_whole_partial_B'],old['source_whole_partial_x86'])==(64810,17756)
assert (new['source_whole_partial_B'],new['source_whole_partial_x86'])==(66877,18344)
assert old['source_partial_frame']=='esp, 0x47c'
assert new['source_partial_frame']=='esp, 0x4d8'
assert old['cases']['2E6']['source_B']==12
r=new['cases']['2E6']
assert (r['source_B'],r['source_x86'])==(2055,590)
assert r['wrong_original_mnemonic_ordinals']==r['wrong_original_GPR_ordinals']==[]
assert r['wrong_original_width_ordinals']==[589]
assert r['native_original_PE_fields_verified']==47
for key in ('2C0','2C1','2C2','2C3','2E5'):
 r=new['cases'][key]
 assert r['wrong_original_mnemonic_ordinals']==r['wrong_original_width_ordinals']==r['wrong_original_GPR_ordinals']==[]
 assert r['native_original_PE_fields_verified']==cases[key][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_native_Japanese_82KB_fighter':'0x004AC040',
 'native_complete_original_CODE_B':WHOLE,'native_whole_x86':ORIG_X86,
 'native_real_2E6_B_x86':[2058,590],
 'source_2E6_B_x86':[2055,590],
 'all_590_original_mnemonics_and_GPR_roles_match':True,
 'single_original_width_difference':'last 2E6 shared-tail JMP 5B vs source 2B',
 'native_original_2E6_typed_PE_targets_verified':47,
 'all_prior_2C0_2C3_2E5_mnemonic_width_GPR_roles_preserved':True,
 'real_borrowed_opponent_X_restores_native_FCOMP_memory':True,
 'original_whole_callable_exact':False,'new_accepted_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'entire_original_shaped_partial_cpp_parent_profiles':rows
},indent=2)+'\n')
print('F1005 native2E6 2058B/590x86/47 real PE fields, all 590 mnemonic and GPR roles match; only final near-vs-short shared JMP width differs. Whole 82KB father NONEXACT.')
