#!/usr/bin/env python3
"""F979 native 1A3/1A4 real random loops in complete original-shaped 82KB father.

Rebuild tracked F978 prior marker and F979 original-shaped natural
whole PARTIAL 82KB C++ parents with locked VC7.1. Compare pinned
Japanese original 556B/147 and 570B/151 x86 and 11 genuine PE
external targets in each case, native previous 1A2, all 151 genuine
afterRET DIR32 case labels +522 original nonfield DATA bytes.
Never count inner states or incomplete parent as whole exact CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f979-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F978-old-1A3A4-markers':R/'probes/FighterWhole004AC040F978.cpp',
         'F979-genuine-random-1A3A4':R/'probes/FighterWhole004AC040F979.cpp'}
frag=(R/'probes/FighterThirdBossRandomLoops1A31A4F979.inc').read_text()
assert frag.count('case 0x1A3:')==frag.count('case 0x1A4:')==1
assert sources['F979-genuine-random-1A3A4'].read_text().count('#include "FighterThirdBossRandomLoops1A31A4F979.inc"')==1
sp=importlib.util.spec_from_file_location('reader979',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;GAME=82796;GAME_NX=22721;DATA=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,GAME),BASE))
assert len(whole)==GAME_NX and whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+GAME,DATA)
cases={'1A2':(0x4B450B,0x4B4981,1142,309,24),
       '1A3':(0x4B4981,0x4B4BAD,556,147,11),
       '1A4':(0x4B4BAD,0x4B4DE7,570,151,11)}
native={}
for k,(a,b,size,nx,nf) in cases.items():
 ins=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(ins)==nx and ins[-1].address+ins[-1].size==b
 native[k]=ins
assert native['1A3'][12].mnemonic=='fld' and native['1A3'][13].mnemonic=='fsub'
assert native['1A3'][64].mnemonic=='fiadd' and native['1A3'][71].mnemonic=='fild'
assert native['1A3'][91].op_str=='0x453b50'
assert native['1A4'][12].mnemonic=='fld' and native['1A4'][13].mnemonic=='fsub'
assert native['1A4'][75].op_str.startswith('esi, ') and native['1A4'][80].op_str=='0x455580'
assert native['1A4'][81].mnemonic=='lea' and native['1A4'][84].mnemonic=='imul'
assert native['1A4'][93].op_str=='0x453b50'
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
 print(name,'whole partial source',end,len(I),'1A3/1A4',
       [(k,row['states'][k]['source_cpp_B'],row['states'][k]['source_x86']) for k in ('1A3','1A4')],flush=True)
old=rows['F978-old-1A3A4-markers'];new=rows['F979-genuine-random-1A3A4']
assert (old['partial_cpp_B'],old['partial_cpp_x86'])==(35751,9799)
assert (new['partial_cpp_B'],new['partial_cpp_x86'])==(36871,10093)
for k,gpr in [('1A3',67),('1A4',71)]:
 assert old['states'][k]['source_cpp_B']==15
 n=new['states'][k]
 assert (n['source_cpp_B'],n['source_x86'])==cases[k][2:4]
 assert n['wrong_mnemonics']==n['wrong_widths']==[]
 assert len(n['wrong_GPR_roles'])==gpr
 assert n['native_PE_targets_verified']==11
assert new['states']['1A2']['native_PE_targets_verified']==24
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_native_game_fighter':'0x004AC040',
 'original_complete_callable_B':GAME,'original_entire_x86':GAME_NX,
 'native_1A3_1A4_original_B_x86':[556+570,147+151],
 'native_1A3_1A4_external_PE_targets':22,
 'native_source_all_mnemonic_and_width_roles_match':True,
 'native_source_GPR_mismatches':[67,71],
 'native_original_1A3_1A4_lack_initial_reset':True,
 'original_entire_game_exact':False,'new_accepted_original_GAME_B':0,
 'mass_cold_replay':False,'entire_partial_source_profiles':rows
},indent=2)+'\n')
print('F979 authentic original 1A3/1A4 native 1126B/298 x86, 22 actual original PE fields, zero mnemonic/width errors, 67/71 GPR errors; original giant NONEXACT.')
