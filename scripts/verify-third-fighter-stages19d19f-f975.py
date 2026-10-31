#!/usr/bin/env python3
"""F975 real Japanese 004AC040 19D/19E/19F natural source in ENTIRE father.

Fresh compile two tracked complete original-shaped normal VC7.1 PARTIAL
82KB fighter sources, F974 old three markers and F975 actual game-state
C++. Independently check pinned original 19D 400B/97x86,
19E 475B/128x86, 19F 478B/128x86, all 31 actual typed
i386 PE external target fields, original 19C predecessor and
151 afterRET DIR32/522 nonfield DATA B. No original whole CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f975-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F974-three-old-markers':R/'probes/FighterWhole004AC040F974.cpp',
         'F975-native-19d19f':R/'probes/FighterWhole004AC040F975.cpp'}
inc=(R/'probes/FighterThirdBossStages19D19FF975.inc').read_text()
assert all(inc.count('case 0x'+i+':')==1 for i in ('19D','19E','19F'))
assert sources['F975-native-19d19f'].read_text().count('#include "FighterThirdBossStages19D19FF975.inc"')==1
sp=importlib.util.spec_from_file_location('f975reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;DATA=1126
original_full=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original_full)==WHOLEX and original_full[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
physical={
 '19C':(0x4B39EB,0x4B3B4E,355,87,7),
 '19D':(0x4B3B4E,0x4B3CDE,400,97,7),
 '19E':(0x4B3CDE,0x4B3EB9,475,128,12),
 '19F':(0x4B3EB9,0x4B4097,478,128,12)}
native={}
for key,(a,b,size,nx,nf) in physical.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert len(n)==nx and b-a==size and n[-1].address+n[-1].size==b
 native[key]=n
d=native['19D']
assert d[36].mnemonic=='lea' and d[36].op_str.endswith('+ 0x37]')
assert d[54].mnemonic=='fiadd' and d[54].op_str=='dword ptr [ebp - 0x18c]'
assert d[66].mnemonic=='fild' and d[66].op_str=='dword ptr [ebp - 0x190]'
assert d[71].op_str=='0x326' and d[73].op_str=='0x453a70'
assert d[93].op_str=='2'
for key,delta in [('19E','0'),('19F','0xffffffd3')]:
 n=native[key]
 assert n[15].mnemonic=='fld' and n[15].op_str.endswith('+ 0x50]')
 assert n[16].op_str=='dword ptr [0x657f74]'
 assert n[20].mnemonic=='fld' and n[20].op_str.endswith('+ 0x54]')
 assert n[21].mnemonic=='fmul' and n[21].op_str=='dword ptr [0x657f74]'
 assert n[44].mnemonic=='shl' and n[44].op_str.endswith(', 2')
 if key=='19E':
  assert n[45].mnemonic=='xor' and n[46].mnemonic=='sub'
 else:
  assert n[45].mnemonic=='mov' and n[45].op_str.endswith(', 0xffffffd3')
  assert n[46].mnemonic=='sub'
 assert n[59].op_str=='dword ptr [0x6590ac]'
 assert n[65].op_str=='0x326' and n[67].op_str=='0x453a70'
 assert n[124].op_str=='0x335' and n[126].op_str=='0x453a70'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,capture_output=True,text=True,timeout=330)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 mask=set();labels={}
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  addr=int.from_bytes(after[off:off+4],'little')
  assert BASE<=addr<BASE+WHOLE
  labels.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+j]==after[j] for j in range(DATA) if j not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in physical.values())
 row={'pinned_original_whole_GAME_CODE_B':WHOLE,'original_whole_x86':WHOLEX,
      'compiled_entire_partial_father_CODE_B':ret,'partial_father_x86':len(I),
      'source_COFF_fields_total':len(refs),
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'real_cases':{},'original_whole_exact':False}
 for k,(a,b,size,nx,nf) in physical.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':size,'native_original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   m=[j for j,(v,w) in enumerate(zip(native[k],s)) if v.mnemonic!=w.mnemonic]
   w=[j for j,(v,w) in enumerate(zip(native[k],s)) if v.size!=w.size]
   g=[j for j,(v,w) in enumerate(zip(native[k],s)) if roles(v)!=roles(w)]
   item.update({'wrong_native_mnemonic_ordinals':m,
                'wrong_native_width_ordinals':w,'wrong_native_GPR_ordinals':g})
   if not m and not w:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,size)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-s[j].address
     physicaloff=native[k][j].address-a+delta
     assert physicaloff==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[physicaloff:physicaloff+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+delta+4+value if r['type']=='REL32' else value
     mm=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(mm.group(1),16) if mm else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_original_PE_targets_verified']=len(fields)
  row['real_cases'][k]=item
 rows[label]=row
 print(label,'whole partial',ret,len(I),'19D/19E/19F',
  [(k,row['real_cases'][k]['source_CODE_B'],row['real_cases'][k]['source_x86'])
   for k in ('19D','19E','19F')],flush=True)
old=rows['F974-three-old-markers'];new=rows['F975-native-19d19f']
assert (old['compiled_entire_partial_father_CODE_B'],old['partial_father_x86'])==(32180,8848)
assert (new['compiled_entire_partial_father_CODE_B'],new['partial_father_x86'])==(33488,9195)
for k in ('19D','19E','19F'):
 assert old['real_cases'][k]['source_CODE_B']==15
 n=new['real_cases'][k]
 assert (n['source_CODE_B'],n['source_x86'])==physical[k][2:4]
 assert n['wrong_native_mnemonic_ordinals']==n['wrong_native_width_ordinals']==[]
 assert n['native_original_PE_targets_verified']==physical[k][4]
assert [len(new['real_cases'][k]['wrong_native_GPR_ordinals']) for k in ('19D','19E','19F')]==[65,84,84]
assert new['real_cases']['19C']['native_original_PE_targets_verified']==7
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_original_game':'0x004AC040',
 'original_entire_callable_CODE_B':WHOLE,'original_entire_x86':WHOLEX,
 'native_19D_E_F_original_CODE_B_x86':[400+475+478,97+128+128],
 'native_19D_E_F_original_typed_PE_targets':31,
 'source_all_native_mnemonics_and_widths_equal':True,
 'source_true_x87_19D_integer_FIADD':True,
 'source_19E_19F_native_signed_shift_and_sub_expressions':True,
 'source_19D_E_F_original_wrong_GPR_roles':[65,84,84],
 'original_game_whole_exact':False,'new_accepted_exact_original_CODE_B':0,
 'mass_cold_replay':False,'whole_partial_source_profiles':rows
},indent=2)+'\n')
print('F975 native 19D 400B/97x86, 19E 475B/128x86, 19F 478B/128x86; 31 PE targets and all mnemonic/width roles match, GPR 65/84/84 wrong. Entire 82KB fighter still NONEXACT.')
