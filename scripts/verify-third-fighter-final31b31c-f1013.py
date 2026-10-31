#!/usr/bin/env python3
"""F1013 native 31B/31C final fighter states and preceding 303 JMP repair.

Fresh serial VC7.1 whole original-shaped PARTIAL 82KB normal source
compiles from TWO tracked inputs F1012 with markers and F1013
genuine 31B/31C. Original native31B 257B/76 x86/9 PE fields;
31C 219B/63 x86/7 PE fields. Both all original mnemonic,
width, GPR roles and physical typed original PE target fields.
Genuine final game cases also make original303 shared JMP
near rather than short, restoring native 1014B/267 x86 geometry.
Check physical afterRET 151 DIR32 local labels and 522
nonreloc DATA bytes; never credit incomplete giant callable.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1013-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1012-final-two-markers':R/'probes/FighterWhole004AC040F1012.cpp',
         'F1013-real31B31C':R/'probes/FighterWhole004AC040F1013.cpp'}
inc=(R/'probes/FighterThirdBossFinal31B31CF1013.inc').read_text()
assert inc.count('case 0x31B:')==inc.count('case 0x31C:')==1
assert inc.count('BeginStateAt454A70(0)')==2
assert inc.count('RefreshStateAt452B30()')==2
assert inc.count('SpawnWithFloatAt453A70(0x3E5,')==1
assert inc.count('U8(0x3CF)=1;')==1
assert sources['F1013-real31B31C'].read_text().count('#include "FighterThirdBossFinal31B31CF1013.inc"')==1
sp=importlib.util.spec_from_file_location('f1013reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
native_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(native_whole)==NX and native_whole[2].op_str=='esp, 0x720'
native_after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={
 '302':(0x4BF9A2,0x4BFDAB,1033,279,25),
 '303':(0x4BFDAB,0x4C01A1,1014,267,29),
 '31B':(0x4C01A1,0x4C02A2,257,76,9),
 '31C':(0x4C02A2,0x4C037D,219,63,7)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
assert native['31B'][34].op_str=='0x454a70' and native['31B'][36].op_str=='0x452b30'
assert native['31B'][54].op_str=='0x453a70'
assert native['31C'][34].op_str=='0x454a70' and native['31C'][36].op_str=='0x452b30'
assert native['31C'][61].op_str.endswith('+ 0x3cf], 1')
assert native['31B'][-1].op_str==native['31C'][-1].op_str=='0x4c03a7'
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
   cwd=R,env=E,text=True,capture_output=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1100:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};masked=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in masked for j in range(off,off+4))
  masked.update(range(off,off+4))
  va=int.from_bytes(native_after[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(masked)==522
 assert all(code[end+j]==native_after[j] for j in range(DATA) if j not in masked)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_entire_callable_CODE_B':WHOLE,'original_x86':NX,
      'compiled_partial_CODE_B':end,'compiled_partial_x86':len(I),
      'partial_frame':I[2].op_str,
      'original_afterRET_DIR32':151,'native_nonfield_DATA_equal_B':522,
      'original_whole_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':sz,'native_original_x86':nx,
        'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   badm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   badw=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   badg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_original_mnemonics':badm,'wrong_original_widths':badw,
                'wrong_original_GPR_roles':badg})
   if not badm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    data=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-s[j].address; off=native[k][j].address-a+d
     assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     v=int.from_bytes(data[off:off+4],'little',signed=r['type']=='REL32')
     dest=native[k][j].address+d+4+v if r['type']=='REL32' else v
     mt=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     exp=int(mt.group(1),16) if mt else 0x6406AC if r['symbol']=='__ftol2' else None
     assert dest==exp,(label,k,j,r['symbol'],hex(dest),exp)
    item['original_PE_external_targets_verified']=nf
  row['cases'][k]=item
 rows[label]=row
 print(label,'full partial source',end,len(I),'frame',I[2].op_str,
       'true final cases',[(k,row['cases'][k]['source_B'],row['cases'][k]['source_x86']) for k in ('31B','31C')],flush=True)
old=rows['F1012-final-two-markers'];new=rows['F1013-real31B31C']
assert (old['compiled_partial_CODE_B'],old['compiled_partial_x86'])==(72252,19803)
assert (new['compiled_partial_CODE_B'],new['compiled_partial_x86'])==(72707,19938)
assert old['partial_frame']==new['partial_frame']=='esp, 0x584'
for k in ('31B','31C'):
 assert old['cases'][k]['source_B']==12
 r=new['cases'][k]
 assert (r['source_B'],r['source_x86'])==cases[k][2:4]
 assert r['wrong_original_mnemonics']==r['wrong_original_widths']==r['wrong_original_GPR_roles']==[]
 assert r['original_PE_external_targets_verified']==cases[k][4]
prev=old['cases']['303'];now=new['cases']['303']
assert (prev['source_B'],prev['source_x86'])==(1011,267) and prev['wrong_original_widths']==[266]
assert (now['source_B'],now['source_x86'])==(1014,267)
assert now['wrong_original_mnemonics']==now['wrong_original_widths']==now['wrong_original_GPR_roles']==[]
assert now['original_PE_external_targets_verified']==29
assert new['cases']['302']['wrong_original_mnemonics']==new['cases']['302']['wrong_original_widths']==new['cases']['302']['wrong_original_GPR_roles']==[]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_original_fighter':'0x004AC040',
 'original_whole_callable_CODE_B':WHOLE,'original_whole_x86':NX,
 'native_final_cases_GAME_CODE_B_x86':[257+219,76+63],
 'both_final_original_mnem_width_GPR_roles_match':True,
 'all_real_final_PE_external_fields_checked':16,
 'true_31B_projectile_sprite':'0x3E5',
 'true_31C_stage21_writes_actor_BYTE_3CF':True,
 'genuine_final_source_repairs_preceding_303_shared_JMP_width':{'before':[266],'after':[]},
 'native_original_303_mnemonic_width_GPR_all_match':True,
 'original_whole_exact':False,'new_original_accepted_whole_CODE_B':0,
 'mass_cold_replay':False,'full_partial_parent_profiles':rows
},indent=2)+'\n')
print('F1013 native 31B+31C 476B/139x86/16 PE, all mnemonic/width/GPR roles, original303 terminal near JMP naturally repaired. Whole 82KB NONEXACT.')
