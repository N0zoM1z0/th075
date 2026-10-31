#!/usr/bin/env python3
"""F997 real native 25D 36-shot circle repairs four later GPR phases.

Compile tracked F996 marker and F997 real 25D as two ENTIRE normal
VC7.1 82KB original-shaped PARTIAL C++ fighter parents.
Original Japanese 25D is 2799B/749 x86 with 36 authentic
0x327 shots, original X passes RAW 32-bit bits and Y is floating
actor + original global006590AC, and 78 real typed PE fields.
Verify real PE original, all 151 afterRET DIR32/522 nonfield B,
previous 25B/25C and later 25F/260/261/262. Genuine preceding
25D repair makes following GPR role deficits 73/73/65/65 -> ZERO.
No complete 82KB original GAME callable exact credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,struct,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f997-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F996-prior-25D-marker':R/'probes/FighterWhole004AC040F996.cpp',
         'F997-real-36-shots':R/'probes/FighterWhole004AC040F997.cpp'}
frag=(R/'probes/FighterThirdBossFullCircle25DF997.inc').read_text()
assert frag.count('case 0x25D:')==1
assert frag.count('SpawnWithFloatAt453A70(0x327,')==36
assert frag.count('g_F970_YAt006590AC')==36
assert sources['F997-real-36-shots'].read_text().count('#include "FighterThirdBossFullCircle25DF997.inc"')==1
sp=importlib.util.spec_from_file_location('f997reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;GAME=82796;GAME_NX=22721;DATA=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,GAME),BASE))
assert len(whole)==GAME_NX and whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+GAME,DATA)
cases={
 '25B':(0x4B84BA,0x4B9327,3693,957,77),
 '25C':(0x4B9327,0x4B973A,1043,271,23),
 '25D':(0x4B973A,0x4BA229,2799,749,78),
 '25F':(0x4BA59B,0x4BA76D,466,114,9),
 '260':(0x4BA76D,0x4BA93F,466,114,9),
 '261':(0x4BA93F,0x4BAAA8,361,98,8),
 '262':(0x4BAAA8,0x4BAC11,361,98,8)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(I)==nx and I[-1].address+I[-1].size==b
 native[k]=I
n=native['25D']
angles=[]
for j,x in enumerate(n):
 if x.mnemonic=='mov' and '+ 0x314]' in x.op_str:
  m=re.search(r', (0x[0-9a-f]+|0)$',x.op_str);assert m
  bits=int(m.group(1),16) if m.group(1).startswith('0x') else 0
  angles.append((j,struct.unpack('<f',struct.pack('<I',bits))[0]))
assert angles==[(65+19*i,float(i*10)) for i in range(36)]
assert [j for j,x in enumerate(n) if x.mnemonic=='call' and x.op_str=='0x453a70']==[82+19*i for i in range(36)]
assert all(n[80+19*i].op_str=='0x327' for i in range(36))
assert all(n[74+19*i].op_str=='dword ptr [0x6590ac]' for i in range(36))
assert all(n[78+19*i].mnemonic=='mov' and n[78+19*i].op_str.endswith('+ 0x44]') for i in range(36))
assert n[16].op_str=='dword ptr [0x657f74]' and n[21].op_str=='dword ptr [0x657f74]'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-980:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 tail=[r for r in refs if r['offset']>=end]
 assert len(tail)==151
 labels={};mask=set()
 for r in tail:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(z not in mask for z in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+GAME
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'native_original_complete_GAME_CODE_B':GAME,
      'native_original_whole_x86':GAME_NX,
      'source_partial_CODE_B':end,'source_partial_x86':len(I),
      'partial_stack_frame':I[2].op_str,
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'whole_original_exact':False,'states':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':sz,'native_original_x86':nx,
        'source_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   mm=[j for j,(n,s) in enumerate(zip(native[k],part)) if n.mnemonic!=s.mnemonic]
   ww=[j for j,(n,s) in enumerate(zip(native[k],part)) if n.size!=s.size]
   gg=[j for j,(n,s) in enumerate(zip(native[k],part)) if role(n)!=role(s)]
   item.update({'wrong_native_mnemonic_ordinals':mm,'wrong_native_width_ordinals':ww,
                'wrong_native_GPR_ordinals':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-part[j].address
     off=native[k][j].address-a+dt
     if not ww:assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+value if r['type']=='REL32' else value
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_PE_target_fields_verified']=nf
  row['states'][k]=item
 results[label]=row
 print(label,'COMPLETE partial original-shaped C++',end,len(I),
       'native case25D',row['states']['25D']['source_B'],row['states']['25D']['source_x86'],flush=True)
old=results['F996-prior-25D-marker'];new=results['F997-real-36-shots']
assert (old['source_partial_CODE_B'],old['source_partial_x86'])==(56944,15640)
assert (new['source_partial_CODE_B'],new['source_partial_x86'])==(59728,16387)
assert old['partial_stack_frame']==new['partial_stack_frame']=='esp, 0x434'
assert old['states']['25D']['source_B']==15
r=new['states']['25D']
assert (r['source_B'],r['source_x86'])==(2799,749)
assert r['wrong_native_mnemonic_ordinals']==r['wrong_native_width_ordinals']==[]
assert len(r['wrong_native_GPR_ordinals'])==477
assert r['native_PE_target_fields_verified']==78
for k,oldwrong in [('25F',73),('260',73),('261',65),('262',65)]:
 prev=old['states'][k];now=new['states'][k]
 assert prev['wrong_native_mnemonic_ordinals']==prev['wrong_native_width_ordinals']==[]
 assert len(prev['wrong_native_GPR_ordinals'])==oldwrong
 assert now['wrong_native_mnemonic_ordinals']==now['wrong_native_width_ordinals']==now['wrong_native_GPR_ordinals']==[]
 assert now['native_PE_target_fields_verified']==cases[k][4]
for k,bad in [('25B',577),('25C',162)]:
 it=new['states'][k]
 assert it['wrong_native_mnemonic_ordinals']==it['wrong_native_width_ordinals']==[]
 assert len(it['wrong_native_GPR_ordinals'])==bad
 assert it['native_PE_target_fields_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'native_Japanese_SHA_pinned_fighter':'0x004AC040',
 'original_whole_callable_CODE_B':GAME,'native_whole_x86':GAME_NX,
 'original_25D_36_shot_CODE_B_x86':[2799,749],
 'original_25D_36_angles_0_to_350_by_ten':True,
 'original_25D_typed_PE_targets_checked':78,
 '25D_wrong_mnemonics_widths':[0,0],
 '25D_wrong_GPR_roles':477,
 'genuine_25D_repairs_four_following_case_GPR_debts':{
  '25F':[73,0],'260':[73,0],'261':[65,0],'262':[65,0]},
 'preceding_25B_25C_original_GPR_and_x86_geometry_unchanged':True,
 'source_frame_before_after':['0x434','0x434'],
 'entire_original_exact':False,'new_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'full_original_shaped_CPP_parent_profiles':results
},indent=2)+'\n')
print('F997 original 25D 2799B/749x86, all mnemonics/widths, 78 genuine PE fields. Real preceding 25D fixes following GPR debts 73/73/65/65 ->0. Whole 82KB NONEXACT.')
