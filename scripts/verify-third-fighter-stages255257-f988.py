#!/usr/bin/env python3
"""F988: original Japanese 004AC040 255/256/257 whole-parent source.

Rebuild tracked F987 old markers and F988 genuine game states as
two complete normal VC7.1 original-shaped PARTIAL 82KB fighter
sources. Verify native PE 258B/75,176B/52,248B/72 x86 and real
7+5+6 typed original i386 PE fields, preceding native 254
without its own afterRET label (boundary from authentic 253),
all 151 original afterRET DIR32 and 522 native DATA nonfields.
No whole game exact CODE acceptance from internal states.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f988-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F987-prior-markers':R/'probes/FighterWhole004AC040F987.cpp',
         'F988-real-255257':R/'probes/FighterWhole004AC040F988.cpp'}
inc=(R/'probes/FighterThirdBossStages255257F988.inc').read_text()
assert all(inc.count('case 0x'+k+':')==1 for k in ('255','256','257'))
assert inc.count('SpawnMixedAt453C80(0x37')==3
assert inc.count('PrepareActionAt453D60(0x21)')==1
assert inc.count('SetAuxActionAt40FB40(6)')==2
assert sources['F988-real-255257'].read_text().count('#include "FighterThirdBossStages255257F988.inc"')==1
sp=importlib.util.spec_from_file_location('f988reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;DATA=1126
original_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original_whole)==WHOLEX and original_whole[2].op_str=='esp, 0x720'
original_after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'254':(0x4B7825,0x4B7906,225,63,6),
       '255':(0x4B7906,0x4B7A08,258,75,7),
       '256':(0x4B7A08,0x4B7AB8,176,52,5),
       '257':(0x4B7AB8,0x4B7BB0,248,72,6)}
native={}
for k,(a,b,sz,nx,nfields) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(n)==nx and b-a==sz and n[-1].address+n[-1].size==b
 native[k]=n
for name in ('255','256','257'):
 n=native[name]
 assert n[9].op_str=='0x453e20'
 assert n[25].op_str=='9' and n[27].op_str=='0x40fac0'
 assert n[30].op_str.endswith(', 5')
 assert n[48 if name=='256' else 48].op_str=='0x37'
 assert n[50].op_str=='0x453c80'
 assert n[-1].op_str=='0x4c03a7'
assert native['255'][53].op_str=='0x453d60'
assert native['255'][73].op_str=='0x40fb40'
assert native['257'][70].op_str=='0x40fb40'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,text=True,capture_output=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for i in D.disasm(code,0):
  I.append(i)
  if i.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(z not in mask for z in range(off,off+4))
  mask.update(range(off,off+4))
  addr=int.from_bytes(original_after[off:off+4],'little')
  assert BASE<=addr<BASE+WHOLE
  labels.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+j]==original_after[j] for j in range(DATA) if j not in mask)
 assert 0x4B7825 not in labels
 assert all(addr in labels for addr in (0x4B7722,0x4B7906,0x4B7A08,0x4B7AB8,0x4B7BB0))
 # Actual original 254 lacks jump-table label; source 253 has 72
 # complete x86, whose terminus establishes original 254 start.
 prev_idx=next(j for j,x in enumerate(I) if x.address==labels[0x4B7722])
 complete_253=I[prev_idx:prev_idx+72]
 original254_src_start=complete_253[-1].address+complete_253[-1].size
 assert len(complete_253)==72
 bounds={
 '254':(original254_src_start,labels[0x4B7906]),
 '255':(labels[0x4B7906],labels[0x4B7A08]),
 '256':(labels[0x4B7A08],labels[0x4B7AB8]),
 '257':(labels[0x4B7AB8],labels[0x4B7BB0])}
 row={'original_whole_game_CODE_B':WHOLE,'original_whole_x86':WHOLEX,
      'whole_partial_SOURCE_CODE_B':ret,'source_x86':len(I),
      'original_254_has_no_afterRET_label':True,
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'total_source_COFF_fields':len(refs),
      'original_whole_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nfields) in cases.items():
  lo,hi=bounds[k]
  part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   badm=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.mnemonic!=y.mnemonic]
   badw=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.size!=y.size]
   badr=[j for j,(x,y) in enumerate(zip(native[k],part)) if roles(x)!=roles(y)]
   item.update({'wrong_original_mnemonic_ordinals':badm,
                'wrong_original_width_ordinals':badw,
                'wrong_original_GPR_ordinals':badr})
   if not badm:
    assert len(fields)==nfields,(label,k,len(fields),nfields)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-part[j].address
     phys=native[k][j].address-a+d
     if not badw: assert phys==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[phys:phys+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+d+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['original_PE_fields_verified']=nfields
  row['cases'][k]=item
 rows[label]=row
 print(label,'whole partial',ret,len(I),'255/256/257',
  [(k,row['cases'][k]['source_CODE_B'],row['cases'][k]['source_x86']) for k in ('255','256','257')],flush=True)
old=rows['F987-prior-markers'];new=rows['F988-real-255257']
assert (old['whole_partial_SOURCE_CODE_B'],old['source_x86'])==(47715,13223)
assert (new['whole_partial_SOURCE_CODE_B'],new['source_x86'])==(48352,13416)
for k,gpr in [('255',46),('256',32),('257',46)]:
 assert old['cases'][k]['source_CODE_B']==15
 n=new['cases'][k]
 assert (n['source_CODE_B'],n['source_x86'])==cases[k][2:4]
 assert n['wrong_original_mnemonic_ordinals']==n['wrong_original_width_ordinals']==[]
 assert len(n['wrong_original_GPR_ordinals'])==gpr
 assert n['original_PE_fields_verified']==cases[k][4]
assert new['cases']['254']['original_PE_fields_verified']==6
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':WHOLE,'original_x86':WHOLEX,
 'native_255_256_257_B_x86':[258+176+248,75+52+72],
 'all_native_mnemonic_widths_match':True,
 'real_original_native_PE_targets_verified':7+5+6,
 'original_254_missing_native_afterRET_label':True,
 'wrong_native_GPR_roles':[46,32,46],
 'entire_original_game_exact':False,'new_accepted_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_PARTIAL_original_shaped_father_profiles':rows
},indent=2)+'\n')
print('F988 authentic original 255/256/257 682B/199 native x86, 18 original PE targets, zero mnemonic/width errors, 46/32/46 wrong GPR. Full 82KB giant NONEXACT.')
