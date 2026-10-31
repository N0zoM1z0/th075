#!/usr/bin/env python3
"""F993 genuine original 25F/260 ten-shot loops: zero GPR-role errors.

Freshly compile two TRACKED entire original-shaped PARTIAL 82KB
normal VC7.1 fighter C++ parents, F991 old markers and F993 real
ten-shot C++. Independently verify the pinned Japanese original
25F/260 each 466B/114x86/9 typed zero-addend PE fields,
native actual loop backedges, all native GPR operands and widths,
preceding native 25A and original 151 afterRET DIR32/522
nonfield data. Original full 82KB is NOT accepted exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f993-third-native-proof'
O.mkdir(parents=True,exist_ok=True)
sources={'F991-old-two-markers':R/'probes/FighterWhole004AC040F991.cpp',
 'F993-two-real-ten-shot-loops':R/'probes/FighterWhole004AC040F993.cpp'}
inc=(R/'probes/FighterThirdBossTenShot25F260F993.inc').read_text()
assert inc.count('case 0x25F:')==inc.count('case 0x260:')==1
assert inc.count('for (int shot=0;shot<10;++shot)')==2
assert inc.count('SpawnFloatXYAt453A70(0x346,')==1
assert inc.count('SpawnFloatXYAt453A70(0x347,')==1
assert sources['F993-two-real-ten-shot-loops'].read_text().count('#include "FighterThirdBossTenShot25F260F993.inc"')==1
sp=importlib.util.spec_from_file_location('f993reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
nativewhole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(nativewhole)==NX and nativewhole[2].op_str=='esp, 0x720'
post=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'25A':(0x4B823F,0x4B84BA,635,166,15),
 '25F':(0x4BA59B,0x4BA76D,466,114,9),
 '260':(0x4BA76D,0x4BA93F,466,114,9)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(I)==nx and I[-1].address+I[-1].size==b
 native[k]=I
for key,kind in (('25F',0x346),('260',0x347)):
 n=native[key]
 assert n[8].mnemonic=='mov' and n[9].op_str.endswith('+ 0x7c], 1')
 assert n[53].op_str==('dword ptr [ebp - 0x30], 0' if key=='25F' else 'dword ptr [ebp - 0x34], 0')
 assert n[54].mnemonic=='jmp'
 assert n[58].op_str==('dword ptr [ebp - 0x30], 0xa' if key=='25F' else 'dword ptr [ebp - 0x34], 0xa')
 assert n[59].mnemonic=='jge'
 assert n[61].mnemonic=='imul' and n[61].op_str.endswith(', 6')
 assert n[63].mnemonic=='sub'
 assert n[88].op_str==hex(kind) and n[90].op_str=='0x453a70'
 assert n[91].mnemonic=='jmp'
 assert n[96].op_str=='dword ptr [0x658044]'
 assert n[103].op_str=='dword ptr [0x658044]'
 assert n[107].op_str.endswith('+ 0xf00], 2')
 assert n[-1].op_str=='0x4c03a7'
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
 source=[]
 for x in D.disasm(code,0):
  source.append(x)
  if x.mnemonic=='ret':break
 ret=source[-1].address+source[-1].size
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  offset=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(offset,offset+4))
  mask.update(range(offset,offset+4))
  va=int.from_bytes(post[offset:offset+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+i]==post[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'native_entire_callable_CODE_B':WHOLE,'original_whole_x86':NX,
  'partial_cpp_CODE_B':ret,'partial_cpp_x86':len(source),
  'partial_source_frame':source[2].op_str,'native_afterRET_DIR32':151,
  'native_nonfield_DATA_equal_B':522,'original_whole_exact':False,
  'original_cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  part=[x for x in source if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':sz,'original_x86':nx,
   'source_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   badm=[i for i,(x,y) in enumerate(zip(native[k],part)) if x.mnemonic!=y.mnemonic]
   badw=[i for i,(x,y) in enumerate(zip(native[k],part)) if x.size!=y.size]
   badg=[i for i,(x,y) in enumerate(zip(native[k],part)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnemonics':badm,'wrong_native_widths':badw,
      'wrong_original_GPR_roles':badg})
   if not badm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for f in fields:
     j=next(i for i,x in enumerate(part) if x.address<=f['offset']<x.address+x.size)
     d=f['offset']-part[j].address
     native_off=native[k][j].address-a+d
     if not badw:assert native_off==f['offset']-lo
     assert f['type'] in ('REL32','DIR32') and f['addend']==0 and f['local_symbol_offset'] is None
     val=int.from_bytes(raw[native_off:native_off+4],'little',signed=f['type']=='REL32')
     target=native[k][j].address+d+4+val if f['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',f['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if f['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,f['symbol'],hex(target),expected)
    item['native_external_PE_targets_verified']=nf
  row['original_cases'][k]=item
 rows[label]=row
 print(label,'complete PARTIAL parent',ret,len(source),
 '25F/260 sourceB',row['original_cases']['25F']['source_B'],
 row['original_cases']['260']['source_B'],flush=True)
old=rows['F991-old-two-markers'];new=rows['F993-two-real-ten-shot-loops']
assert (old['partial_cpp_CODE_B'],old['partial_cpp_x86'])==(50620,14000)
assert (new['partial_cpp_CODE_B'],new['partial_cpp_x86'])==(51534,14224)
assert old['partial_source_frame']=='esp, 0x348'
assert new['partial_source_frame']=='esp, 0x370'
for k in ('25F','260'):
 assert old['original_cases'][k]['source_B']==15
 n=new['original_cases'][k]
 assert (n['source_B'],n['source_x86'])==(466,114)
 assert n['wrong_native_mnemonics']==n['wrong_native_widths']==n['wrong_original_GPR_roles']==[]
 assert n['native_external_PE_targets_verified']==9
assert new['original_cases']['25A']['native_external_PE_targets_verified']==15
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x004AC040',
 'native_entire_callable_GAME_CODE_B':WHOLE,'native_original_x86':NX,
 'true_native_25F_260_CODE_B_x86':[466*2,114*2],
 'all_228_original_mnemonics_widths_GPR_roles_match':True,
 'real_native_PE_targets_verified':18,
 'native_actual_two_ten_shot_loops':True,
 'source_partial_frame_change':['0x348','0x370'],
 'whole_original_exact':False,'new_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'entire_original_shaped_partial_father_profiles':rows
},indent=2)+'\n')
print('F993 two native true 10-shot cases, 932B/228 x86, all mnemonic/width/GPR roles, 18 actual PE targets. Whole 82KB game NONEXACT.')
