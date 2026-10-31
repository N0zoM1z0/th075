#!/usr/bin/env python3
"""F996 true native 25C nine-shot spread, PE fields and adjacent GPR controls.

Compile two tracked ENTIRE original-shaped normal VC7.1 PARTIAL
82KB fighter parents, previous F995 with marker and F996 with
genuine 25C 1043B/271 native x86. Independently verify all
nine native angles, 23 actual original typed PE/COFF targets,
all native mnem/width positions, preceding real 25B and four
following genuine 25F/260/261/262 GPR controls, full native
151 afterRET DIR32 plus 522 exact DATA nonfields. Incomplete
whole game fighter is NONEXACT and earns NO whole-code credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,struct,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f996-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F995-25C-marker':R/'probes/FighterWhole004AC040F995.cpp',
         'F996-real-nine-shot':R/'probes/FighterWhole004AC040F996.cpp'}
inc=(R/'probes/FighterThirdBossNineShot25CF996.inc').read_text()
assert inc.count('case 0x25C:')==1
assert inc.count('SpawnFloatXYAt453A70(0x342,')==9
assert inc.count('g_F968_RoundY190At00659294')==9
assert sources['F996-real-nine-shot'].read_text().count('#include "FighterThirdBossNineShot25CF996.inc"')==1
sp=importlib.util.spec_from_file_location('read996',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;ORIG_NX=22721;AFTER=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(whole)==ORIG_NX and whole[2].op_str=='esp, 0x720'
original_data=rd.pe_bytes_at(PE,BASE+WHOLE,AFTER)
cases={
 '25B':(0x4B84BA,0x4B9327,3693,957,77),
 '25C':(0x4B9327,0x4B973A,1043,271,23),
 '25F':(0x4BA59B,0x4BA76D,466,114,9),
 '260':(0x4BA76D,0x4BA93F,466,114,9),
 '261':(0x4BA93F,0x4BAAA8,361,98,8),
 '262':(0x4BAAA8,0x4BAC11,361,98,8)}
native={}
for key,(a,b,size,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(n)==nx and n[-1].address+n[-1].size==b
 native[key]=n
n=native['25C']
angles=[]
for j,x in enumerate(n):
 if x.mnemonic=='mov' and '+ 0x314]' in x.op_str:
  m=re.search(r', (0x[0-9a-f]+|0)$',x.op_str)
  assert m,(j,x.op_str)
  value=int(m.group(1),16) if m.group(1).startswith('0x') else 0
  angles.append((j,struct.unpack('<f',struct.pack('<I',value))[0]))
assert angles==[(46+25*i,float(-28+7*i)) for i in range(9)]
assert [j for j,x in enumerate(n) if x.mnemonic=='call' and x.op_str=='0x453a70']==[69+25*i for i in range(9)]
assert all(n[67+25*i].op_str=='0x342' for i in range(9))
assert all(n[55+25*i].op_str=='dword ptr [0x659294]' for i in range(9))
assert all(n[60+25*i].mnemonic=='imul' and n[60+25*i].op_str.endswith(', 0x31') for i in range(9))
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(REG.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==AFTER
 post=[r for r in refs if r['offset']>=end]
 assert len(post)==151
 labels={};mask=set()
 for r in post:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(original_data[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+i]==original_data[i] for i in range(AFTER) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'native_complete_original_CODE_B':WHOLE,'native_complete_x86':ORIG_NX,
   'source_whole_partial_CODE_B':end,'source_whole_partial_x86':len(I),
   'compiler_frame':I[2].op_str,'original_afterRET_DIR32':151,
   'native_DATA_nonfield_exact_B':522,'whole_original_exact':False,
   'cases':{}}
 for key,(a,b,size,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  phys=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':size,'native_original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   badm=[j for j,(n,s) in enumerate(zip(native[key],part)) if n.mnemonic!=s.mnemonic]
   badw=[j for j,(n,s) in enumerate(zip(native[key],part)) if n.size!=s.size]
   badg=[j for j,(n,s) in enumerate(zip(native[key],part)) if roles(n)!=roles(s)]
   item.update({'wrong_native_mnemonics':badm,'wrong_native_widths':badw,
                'wrong_native_GPR_ordinals':badg})
   if not badm:
    assert len(phys)==nf,(label,key,len(phys),nf)
    raw=rd.pe_bytes_at(PE,a,size)
    for r in phys:
     j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-part[j].address
     off=native[key][j].address-a+delta
     if not badw: assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[key][j].address+delta+4+value if r['type']=='REL32' else value
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,key,j,r['symbol'],hex(target),expected)
    item['original_native_PE_targets_verified']=nf
  row['cases'][key]=item
 rows[label]=row
 print(label,'entire original-shaped PARTIAL father',end,len(I),
 'case25C',row['cases']['25C']['source_CODE_B'],row['cases']['25C']['source_x86'],flush=True)
old=rows['F995-25C-marker'];new=rows['F996-real-nine-shot']
assert (old['source_whole_partial_CODE_B'],old['source_whole_partial_x86'])==(55916,15371)
assert (new['source_whole_partial_CODE_B'],new['source_whole_partial_x86'])==(56944,15640)
assert old['compiler_frame']=='esp, 0x410'
assert new['compiler_frame']=='esp, 0x434'
assert old['cases']['25C']['source_CODE_B']==15
real=new['cases']['25C']
assert (real['source_CODE_B'],real['source_x86'])==(1043,271)
assert real['wrong_native_mnemonics']==real['wrong_native_widths']==[]
assert len(real['wrong_native_GPR_ordinals'])==162
assert real['original_native_PE_targets_verified']==23
for state,wrong in [('25B',577),('25F',73),('260',73),('261',65),('262',65)]:
 item=new['cases'][state]
 assert item['wrong_native_mnemonics']==item['wrong_native_widths']==[]
 assert len(item['wrong_native_GPR_ordinals'])==wrong
 assert item['original_native_PE_targets_verified']==cases[state][4]
(O/'verified-summary.json').write_text(json.dumps({
 'native_Japanese_original_fighter':'0x004AC040',
 'original_whole_game_CODE_B':WHOLE,'original_whole_x86':ORIG_NX,
 'native_real_25C_CODE_B_x86':[1043,271],
 'nine_original_angles_m28_to_28_by_seven':True,
 'true_25C_original_external_PE_targets_verified':23,
 'wrong_native_mnemonics_widths':[0,0],
 'wrong_native_25C_GPR_roles':162,
 'native_previous_and_following_case_roles_unchanged':True,
 'whole_parent_frame_before_after':['0x410','0x434'],
 'original_entire_callable_exact':False,'new_exact_original_CODE_B':0,
 'mass_cold_replay':False,'whole_original_shaped_partial_sources':rows
},indent=2)+'\n')
print('F996 original 25C 1043 CODE B/271 x86/23 real PE fields, native mnemonics/widths all match, 162 GPR wrong. Whole 82KB game NONEXACT.')
