#!/usr/bin/env python3
"""F991 original native 25A fixed-angle five shots.

Fresh-build tracked F990 original-shaped marker and F991 five-shot
ENTIRE normal VC7.1 PARTIAL 82KB parent source C++, verify all native
25A 635B/166x86 source opcode widths, fifteen PE targets, previous
259 845B/212x86 fifteen true native PE targets, entire 151 afterRET original
DIR32 and 522 original DATA nonfields. The original 82KB whole game
callable is still NONEXACT and earns zero accepted exact CODE bytes.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f991-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F990-prior-marker':R/'probes/FighterWhole004AC040F990.cpp',
 'F991-real-five-shot':R/'probes/FighterWhole004AC040F991.cpp'}
frag=(R/'probes/FighterThirdBossFiveShot25AF991.inc').read_text()
assert frag.count('case 0x25A:')==1
assert frag.count('SpawnFloatXYAt453A70(0x325,')==5
assert sources['F991-real-five-shot'].read_text().count('#include "FighterThirdBossFiveShot25AF991.inc"')==1
sp=importlib.util.spec_from_file_location('f991reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;DATA=1126
origparent=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(origparent)==WHOLEX and origparent[2].op_str=='esp, 0x720'
orig_after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'259':(0x4B7EF2,0x4B823F,845,212,15),
       '25A':(0x4B823F,0x4B84BA,635,166,15)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
n=native['25A']
for j in (59,84,109,134,159): assert n[j].op_str=='0x325'
for j in (61,86,111,136,161): assert n[j].op_str=='0x453a70'
assert n[164].op_str=='0x46d000'
assert n[38].op_str.endswith(', 0x41200000')
assert n[162].op_str=='0xfa'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(RX.findall(i.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,src in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=env,text=True,capture_output=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 lab={};masked=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in masked for i in range(off,off+4))
  masked.update(range(off,off+4))
  addr=int.from_bytes(orig_after[off:off+4],'little')
  assert BASE<=addr<BASE+WHOLE
  lab.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(masked)==522
 assert all(code[ret+i]==orig_after[i] for i in range(DATA) if i not in masked)
 assert all(a in lab and b in lab for a,b,_,_,_ in cases.values())
 row={'native_complete_GAME_CODE_B':WHOLE,'native_original_whole_x86':WHOLEX,
      'partial_source_CODE_B':ret,'partial_source_x86':len(I),
      'parent_source_frame':I[2].op_str,
      'native_afterRET_DIR32':151,'native_DATA_nonfield_exact_B':522,
      'original_states':{},'whole_original_exact':False}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=lab[a],lab[b];part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  it={'original_native_B':sz,'original_x86':nx,
      'source_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   badm=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.mnemonic!=y.mnemonic]
   badw=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.size!=y.size]
   badg=[j for j,(x,y) in enumerate(zip(native[k],part)) if roles(x)!=roles(y)]
   it.update({'wrong_mnemonics':badm,'wrong_widths':badw,'wrong_GPR_roles':badg})
   if not badm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-part[j].address;off=native[k][j].address-a+delta
     if not badw: assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     number=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+delta+4+number if r['type']=='REL32' else number
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    it['native_PE_targets_verified']=nf
  row['original_states'][k]=it
 rows[label]=row
 print(label,'whole partial source',ret,len(I),'frame',I[2].op_str,
  'case25A',row['original_states']['25A']['source_B'],row['original_states']['25A']['source_x86'],flush=True)
old=rows['F990-prior-marker'];new=rows['F991-real-five-shot']
assert (old['partial_source_CODE_B'],old['partial_source_x86'])==(50000,13836)
assert (new['partial_source_CODE_B'],new['partial_source_x86'])==(50620,14000)
assert old['original_states']['25A']['source_B']==15
assert old['parent_source_frame']=='esp, 0x334'
assert new['parent_source_frame']=='esp, 0x348'
n=new['original_states']['25A']
assert (n['source_B'],n['source_x86'])==(635,166)
assert n['wrong_mnemonics']==n['wrong_widths']==[]
assert len(n['wrong_GPR_roles'])==97
assert n['native_PE_targets_verified']==15
assert new['original_states']['259']['native_PE_targets_verified']==15
(O/'verified-summary.json').write_text(json.dumps({
 'original_82KB_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':WHOLE,'original_whole_x86':WHOLEX,
 'native_25A_CODE_B_x86':[635,166],
 'native_25A_zero_mnemonic_width_diffs':True,
 'native_25A_true_original_external_PE_targets':15,
 'native_25A_GPR_role_errors':97,
 'real_parent_frame_changes':['0x334','0x348'],
 'whole_original_exact':False,'new_accepted_game_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_parent_profiles':rows
},indent=2)+'\n')
print('F991 original 25A 635B/166x86, 15 true native PE targets; source mnemonic/width align, 97 wrong GPR roles; whole 82KB father NONEXACT.')
