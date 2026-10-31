#!/usr/bin/env python3
"""F995 genuine 36-shot original game state25B, 3693B/957x86.

Fresh normal VC7.1 whole-PARTIAL 82KB parent builds from tracked
F994 old 25B marker and F995 real 36-shot state. Independently
read SHA-pinned original Japanese executable: all 36 true
angle0..350 stores, 36 original sprite0x327 calls, 77 actual typed
zero-addend PE external targets. Also audit previous four real
25F/260/261/262 source cases: GPR phase 0->73/73/65/65 wrong
after genuine source addition, but mnemonic/widths remain aligned.
Verify original afterRET 151 local DIR32 /522 nonfield DATA bytes.
Entire original 82KB callable still NONEXACT, no original CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,struct,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f995-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F994-old-25B-marker':R/'probes/FighterWhole004AC040F994.cpp',
         'F995-real-36-projectiles':R/'probes/FighterWhole004AC040F995.cpp'}
frag=(R/'probes/FighterThirdBossFullCircle25BF995.inc').read_text()
assert frag.count('case 0x25B:')==1
assert frag.count('SpawnFloatXYAt453A70(0x327,')==36
assert frag.count('g_F968_RoundY190At00659294')==36
assert sources['F995-real-36-projectiles'].read_text().count('#include "FighterThirdBossFullCircle25BF995.inc"')==1
sp=importlib.util.spec_from_file_location('f995reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;GAME=82796;GAME_X86=22721;DATA=1126
orig_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,GAME),BASE))
assert len(orig_whole)==GAME_X86 and orig_whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+GAME,DATA)
cases={
 '25A':(0x4B823F,0x4B84BA,635,166,15),
 '25B':(0x4B84BA,0x4B9327,3693,957,77),
 '25F':(0x4BA59B,0x4BA76D,466,114,9),
 '260':(0x4BA76D,0x4BA93F,466,114,9),
 '261':(0x4BA93F,0x4BAAA8,361,98,8),
 '262':(0x4BAAA8,0x4BAC11,361,98,8)}
native={}
for name,(a,b,sz,nx,nf) in cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(I)==nx and I[-1].address+I[-1].size==b
 native[name]=I
n=native['25B']
angles=[]
for j,i in enumerate(n):
 if i.mnemonic=='mov' and '+ 0x314]' in i.op_str:
  hit=re.search(r', (0x[0-9a-f]+|0)$',i.op_str)
  assert hit,(j,i.op_str)
  number=int(hit.group(1),16) if hit.group(1).startswith('0x') else 0
  angles.append((j,struct.unpack('<f',struct.pack('<I',number))[0]))
assert angles==[(40+25*k,float(10*k)) for k in range(36)]
assert [j for j,i in enumerate(n) if i.mnemonic=='call' and i.op_str=='0x453a70']==[63+25*k for k in range(36)]
assert all(n[61+25*k].op_str=='0x327' for k in range(36))
assert all(n[49+25*k].op_str=='dword ptr [0x659294]' for k in range(36))
assert all(n[54+25*k].mnemonic=='imul' and n[54+25*k].op_str.endswith(', 0x31') for k in range(36))
assert n[38].op_str=='0x46d000' and n[40].op_str=='dword ptr [ecx + 0x314], 0'
assert n[940].mnemonic=='mov' and n[940].op_str.endswith('+ 0xf00], 2')
assert n[955].op_str=='0x40fac0'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(RX.findall(i.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,text=True,capture_output=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for i in D.disasm(code,0):
  I.append(i)
  if i.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+GAME
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+j]==after[j] for j in range(DATA) if j not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_full_GAME_CODE_B':GAME,'original_full_GAME_x86':GAME_X86,
      'partial_generated_CODE_B':end,'partial_generated_x86':len(I),
      'source_partial_parent_frame':I[2].op_str,
      'original_afterRET_DIR32':151,'native_afterRET_nonfield_equal_B':522,
      'original_cases':{},'whole_original_exact':False}
 for key,(a,b,sz,nx,nfields) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  refs_case=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(x,y) in enumerate(zip(native[key],s)) if x.mnemonic!=y.mnemonic]
   ww=[j for j,(x,y) in enumerate(zip(native[key],s)) if x.size!=y.size]
   gg=[j for j,(x,y) in enumerate(zip(native[key],s)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnem_ordinals':mm,'wrong_native_width_ordinals':ww,
                'wrong_native_GPR_ordinals':gg})
   if not mm:
    assert len(refs_case)==nfields,(label,key,len(refs_case),nfields)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in refs_case:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     offset=r['offset']-s[j].address
     native_off=native[key][j].address-a+offset
     if not ww:assert native_off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[native_off:native_off+4],'little',signed=r['type']=='REL32')
     target=native[key][j].address+offset+4+value if r['type']=='REL32' else value
     match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(match.group(1),16) if match else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,key,j,r['symbol'],hex(target),expected)
    item['original_PE_external_targets_verified']=nfields
  row['original_cases'][key]=item
 rows[label]=row
 print(label,'complete partial fighter',end,len(I),'frame',I[2].op_str,
       '25B source B/x86',row['original_cases']['25B']['source_CODE_B'],
       row['original_cases']['25B']['source_x86'],flush=True)
old=rows['F994-old-25B-marker'];new=rows['F995-real-36-projectiles']
assert (old['partial_generated_CODE_B'],old['partial_generated_x86'])==(52238,14416)
assert (new['partial_generated_CODE_B'],new['partial_generated_x86'])==(55916,15371)
assert old['source_partial_parent_frame']=='esp, 0x380'
assert new['source_partial_parent_frame']=='esp, 0x410'
assert old['original_cases']['25B']['source_CODE_B']==15
real=new['original_cases']['25B']
assert (real['source_CODE_B'],real['source_x86'])==(3693,957)
assert real['wrong_native_mnem_ordinals']==real['wrong_native_width_ordinals']==[]
assert len(real['wrong_native_GPR_ordinals'])==577
assert real['original_PE_external_targets_verified']==77
for state,regression in [('25F',73),('260',73),('261',65),('262',65)]:
 prior=old['original_cases'][state]
 now=new['original_cases'][state]
 assert prior['wrong_native_mnem_ordinals']==prior['wrong_native_width_ordinals']==prior['wrong_native_GPR_ordinals']==[]
 assert now['wrong_native_mnem_ordinals']==now['wrong_native_width_ordinals']==[]
 assert len(now['wrong_native_GPR_ordinals'])==regression
 assert now['original_PE_external_targets_verified']==cases[state][4]
assert new['original_cases']['25A']['original_PE_external_targets_verified']==15
(O/'verified-summary.json').write_text(json.dumps({
 'native_Japanese_SHA_pinned_fighter':'0x004AC040',
 'original_complete_callable_GAME_CODE_B':GAME,'original_x86':GAME_X86,
 'native_true_25B_36_shot_CODE_B_x86':[3693,957],
 'original_true_angle_stores_0_to_350_every_10':True,
 'real_25B_original_PE_fields':77,
 'native_25B_wrong_mnemonics_widths':[0,0],
 'native_25B_wrong_GPR_roles':577,
 'genuine_parent_source_frame_before_after':['0x380','0x410'],
 'earlier_four_ten_shot_GPR_wrong_before_after':{'25F':[0,73],
   '260':[0,73],'261':[0,65],'262':[0,65]},
 'earlier_four_mnemonics_and_widths_still_match':True,
 'four_original_scope_grammar_controls_negative':True,
 'whole_original_exact':False,'accepted_new_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_father_profiles':rows
},indent=2)+'\n')
print('F995 true original 25B 3693B/957x86, 77 native PE fields. All native mnemonics/widths, 577 GPR errors; following 25F/260/261/262 GPR phase regresses 73/73/65/65. Still whole 82KB NONEXACT.')
