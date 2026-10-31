#!/usr/bin/env python3
"""F982 real 1F6/1F7 double-scaled native combat states in full original-shaped fighter.

Rebuild tracked F981 prior marker and F982 original-shaped natural
whole PARTIAL 82KB C++ parents with locked VC7.1. Compare pinned
Japanese original 777B/215 and 777B/215 x86 and 22 genuine PE
external targets in each case, native previous 1F5, all 151 genuine
afterRET DIR32 case labels +522 original nonfield DATA bytes.
Never count inner states or incomplete parent as whole exact CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f982-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F981-old-1F6F7-markers':R/'probes/FighterWhole004AC040F981.cpp',
         'F982-real-1F6F7':R/'probes/FighterWhole004AC040F982.cpp'}
frag=(R/'probes/FighterThirdBossStages1F61F7F982.inc').read_text()
assert frag.count('case 0x1F6:')==frag.count('case 0x1F7:')==1
assert sources['F982-real-1F6F7'].read_text().count('#include "FighterThirdBossStages1F61F7F982.inc"')==1
sp=importlib.util.spec_from_file_location('reader982',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;GAME=82796;GAME_NX=22721;DATA=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,GAME),BASE))
assert len(whole)==GAME_NX and whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+GAME,DATA)
cases={'1F5':(0x4B5125,0x4B5463,830,232,23),
       '1F6':(0x4B5463,0x4B576C,777,215,22),
       '1F7':(0x4B576C,0x4B5A75,777,215,22)}
native={}
for k,(a,b,size,nx,nf) in cases.items():
 ins=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(ins)==nx and ins[-1].address+ins[-1].size==b
 native[k]=ins
for state,global_va,stage4_max in [('1F6',0x6583e0,2),('1F7',0x6584c8,4)]:
 n=native[state]
 assert n[9].mnemonic=='fld' and n[9].op_str.endswith('+ 0x50]')
 assert n[10].mnemonic=='fmul' and n[10].op_str==f'qword ptr [0x{global_va:x}]'
 assert n[14].mnemonic=='fld' and n[14].op_str.endswith('+ 0x54]')
 assert n[15].mnemonic=='fmul' and n[15].op_str==f'qword ptr [0x{global_va:x}]'
 assert n[30].op_str.endswith(', 3') and n[34].op_str.endswith(', 6')
 assert n[86].op_str.endswith(', 2')
 assert n[116].op_str=='0x453b50'
 assert n[135].op_str=='0x453b50'
 assert n[160].op_str=='0x453b50'
 assert n[179].op_str=='0x453b50'
 assert n[193].op_str.endswith(', '+str(stage4_max))
 assert n[-1].mnemonic=='jmp' and n[-1].op_str=='0x4c03a7'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for name,cpp in sources.items():
 obj=O/(name+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=env,text=True,capture_output=True,timeout=340)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 mp={};mask=set()
 for r in table:
  d=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(d,d+4))
  mask.update(range(d,d+4))
  addr=int.from_bytes(after[d:d+4],'little')
  assert BASE<=addr<BASE+GAME
  mp.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in mp and b in mp for a,b,_,_,_ in cases.values())
 row={'original_game_entire_B':GAME,'original_game_x86':GAME_NX,
      'partial_cpp_B':end,'partial_cpp_x86':len(I),
      'partial_frame':I[2].op_str,'cpp_COFF_field_count':len(refs),
      'real_afterRET_DIR32':151,'real_afterRET_nonfield_equal_B':522,
      'original_whole_exact':False,'states':{}}
 for k,(a,b,size,nx,nf) in cases.items():
  lo,hi=mp[a],mp[b]
  part=[x for x in I if lo<=x.address<hi]
  refs_case=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':size,'original_x86':nx,
        'source_cpp_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   badm=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.mnemonic!=y.mnemonic]
   badw=[j for j,(x,y) in enumerate(zip(native[k],part)) if x.size!=y.size]
   badg=[j for j,(x,y) in enumerate(zip(native[k],part)) if roles(x)!=roles(y)]
   item.update({'wrong_mnemonics':badm,'wrong_widths':badw,'wrong_GPR_roles':badg})
   if not badm and not badw:
    assert len(refs_case)==nf,(name,k,len(refs_case),nf)
    raw=rd.pe_bytes_at(PE,a,size)
    for f in refs_case:
     j=next(j for j,x in enumerate(part) if x.address<=f['offset']<x.address+x.size)
     delta=f['offset']-part[j].address
     orig_off=native[k][j].address-a+delta
     assert orig_off==f['offset']-lo
     assert f['type'] in ('REL32','DIR32') and f['addend']==0 and f['local_symbol_offset'] is None
     num=int.from_bytes(raw[orig_off:orig_off+4],'little',signed=f['type']=='REL32')
     origdest=native[k][j].address+delta+4+num if f['type']=='REL32' else num
     m=re.search(r'At([0-9A-Fa-f]{6,8})',f['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if f['symbol']=='__ftol2' else None
     assert origdest==expected,(name,k,j,f['symbol'],hex(origdest),expected)
    item['native_PE_targets_verified']=nf
  row['states'][k]=item
 rows[name]=row
 print(name,'whole partial source',end,len(I),'1F6/1F7',
       [(k,row['states'][k]['source_cpp_B'],row['states'][k]['source_x86']) for k in ('1F6','1F7')],flush=True)
old=rows['F981-old-1F6F7-markers'];new=rows['F982-real-1F6F7']
assert (old['partial_cpp_B'],old['partial_cpp_x86'])==(38501,10553)
assert (new['partial_cpp_B'],new['partial_cpp_x86'])==(40025,10979)
for k,gpr in [('1F6',126),('1F7',126)]:
 assert old['states'][k]['source_cpp_B']==15
 n=new['states'][k]
 assert (n['source_cpp_B'],n['source_x86'])==cases[k][2:4]
 assert n['wrong_mnemonics']==n['wrong_widths']==[]
 assert len(n['wrong_GPR_roles'])==gpr
 assert n['native_PE_targets_verified']==22
assert new['states']['1F5']['native_PE_targets_verified']==23
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_native_game_fighter':'0x004AC040',
 'original_complete_callable_B':GAME,'original_entire_x86':GAME_NX,
 'native_1F6_1F7_original_B_x86':[777+777,215+215],
 'native_1F6_1F7_external_PE_targets':44,
 'native_source_all_mnemonic_and_width_roles_match':True,
 'native_source_GPR_mismatches':[126,126],
 'native_true_1F6_1F7_initial_DOUBLE_motion_scale':True,
 'original_entire_game_exact':False,'new_accepted_original_GAME_B':0,
 'mass_cold_replay':False,'entire_partial_source_profiles':rows
},indent=2)+'\n')
print('F982 original 1F6/1F7 native 1554B/430 x86, 44 original PE targets, zero mnemonic/width errors, 126/126 GPR errors; original giant NONEXACT.')
