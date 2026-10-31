#!/usr/bin/env python3
"""F981 real 1F4/1F5 native ground/combat states in full original-shaped fighter.

Rebuild tracked F979 prior marker and F981 original-shaped natural
whole PARTIAL 82KB C++ parents with locked VC7.1. Compare pinned
Japanese original 830B/232 and 830B/232 x86 and 23 genuine PE
external targets in each case, native previous 1A4, all 151 genuine
afterRET DIR32 case labels +522 original nonfield DATA bytes.
Never count inner states or incomplete parent as whole exact CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f981-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F979-old-1F4F5-markers':R/'probes/FighterWhole004AC040F979.cpp',
         'F981-real-1F4F5':R/'probes/FighterWhole004AC040F981.cpp'}
frag=(R/'probes/FighterThirdBossStages1F41F5F981.inc').read_text()
assert frag.count('case 0x1F4:')==frag.count('case 0x1F5:')==1
assert sources['F981-real-1F4F5'].read_text().count('#include "FighterThirdBossStages1F41F5F981.inc"')==1
sp=importlib.util.spec_from_file_location('reader981',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;GAME=82796;GAME_NX=22721;DATA=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,GAME),BASE))
assert len(whole)==GAME_NX and whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+GAME,DATA)
cases={'1A4':(0x4B4BAD,0x4B4DE7,570,151,11),
       '1F4':(0x4B4DE7,0x4B5125,830,232,23),
       '1F5':(0x4B5125,0x4B5463,830,232,23)}
native={}
for k,(a,b,size,nx,nf) in cases.items():
 ins=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(ins)==nx and ins[-1].address+ins[-1].size==b
 native[k]=ins
for state in ('1F4','1F5'):
 n=native[state]
 assert n[8].mnemonic=='mov' and n[9].mnemonic=='call' and n[9].op_str=='0x453e20'
 assert n[22].op_str=='dword ptr [0x65782c]'
 assert n[83].op_str.endswith(', 0x40000000') if state=='1F4' else n[83].op_str.endswith(', 0x41000000')
 assert n[100].op_str=='0x453c80' if state=='1F4' else n[98].op_str=='0x453c80'
 assert [n[j].op_str for j in (134,153,178,197) if j<len(n)].count('0x32a')<=2
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
 print(name,'whole partial source',end,len(I),'1F4/1F5',
       [(k,row['states'][k]['source_cpp_B'],row['states'][k]['source_x86']) for k in ('1F4','1F5')],flush=True)
old=rows['F979-old-1F4F5-markers'];new=rows['F981-real-1F4F5']
assert (old['partial_cpp_B'],old['partial_cpp_x86'])==(36871,10093)
assert (new['partial_cpp_B'],new['partial_cpp_x86'])==(38501,10553)
for k,gpr in [('1F4',135),('1F5',135)]:
 assert old['states'][k]['source_cpp_B']==15
 n=new['states'][k]
 assert (n['source_cpp_B'],n['source_x86'])==cases[k][2:4]
 assert n['wrong_mnemonics']==n['wrong_widths']==[]
 assert len(n['wrong_GPR_roles'])==gpr
 assert n['native_PE_targets_verified']==23
assert new['states']['1A4']['native_PE_targets_verified']==11
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_native_game_fighter':'0x004AC040',
 'original_complete_callable_B':GAME,'original_entire_x86':GAME_NX,
 'native_1F4_1F5_original_B_x86':[830+830,232+232],
 'native_1F4_1F5_external_PE_targets':46,
 'native_source_all_mnemonic_and_width_roles_match':True,
 'native_source_GPR_mismatches':[135,135],
 'native_true_1F5_stage7_drag_store_after_projectile':True,
 'original_entire_game_exact':False,'new_accepted_original_GAME_B':0,
 'mass_cold_replay':False,'entire_partial_source_profiles':rows
},indent=2)+'\n')
print('F981 original 1F4/1F5 native 1660B/464 x86, 46 original PE targets, zero mnemonic/width errors, 135/135 GPR errors; original giant NONEXACT.')
