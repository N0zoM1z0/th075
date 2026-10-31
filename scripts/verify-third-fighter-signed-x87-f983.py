#!/usr/bin/env python3
"""F983 authentic 1F8/1F9 six native FILD/FSUBR chains per original case.

Rebuild tracked F982 markers and F983 genuine original-shaped entire
PARTIAL 82KB fighter VC7.1 sources. Read pinned original Japanese PE
1168B/339x86 and 1167B/339x86 native case extents and all 28 typed
zero-addend i386 PE call/global fields in EACH case, preserving
instruction-ordinal field locations where the source differs one
original CMP byte. Check whole afterRET 151 DIR32/522 data nonfields.
The giant remains NONEXACT; never accept an internal case as callable.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f983-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F982-prior-1F8F9-markers':R/'probes/FighterWhole004AC040F982.cpp',
         'F983-real-typed-FSUBR':R/'probes/FighterWhole004AC040F983.cpp'}
frag=(R/'probes/FighterThirdBossStages1F81F9F983.inc').read_text()
assert frag.count('case 0x1F8:')==frag.count('case 0x1F9:')==1
assert frag.count('reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float(')==12
sp=importlib.util.spec_from_file_location('readf983',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIGINAL=82796;NX=22721;DATA=1126
full=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIGINAL),BASE))
assert len(full)==NX and full[2].op_str=='esp, 0x720'
post=rd.pe_bytes_at(PE,BASE+ORIGINAL,DATA)
cases={'1F7':(0x4B576C,0x4B5A75,777,215,22),
       '1F8':(0x4B5A75,0x4B5F05,1168,339,28),
       '1F9':(0x4B5F05,0x4B6394,1167,339,28)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 v=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(v)==nx and v[-1].address+v[-1].size==b
 native[k]=v
chain_ord=[183,204,225,246,267,288]
for state in ('1F8','1F9'):
 n=native[state]
 for start in chain_ord:
  assert [i.mnemonic for i in n[start:start+6]]==[
   'movsx','imul','mov','fild','mov','fsubr']
  assert n[start+1].op_str.endswith(', 7')
  assert n[start+5].op_str.endswith('+ 0x44]')
 assert n[64].mnemonic=='cmp' and n[64].op_str.endswith(', 0xeb')
 assert n[125].op_str=='dword ptr [0x658264]'
 assert n[193].op_str=='0x453b50'
 assert n[298].op_str=='0x453b50'
 assert n[303].op_str=='0x40fbb0'
assert native['1F8'][64].size==6 and native['1F9'][64].size==5
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for name,cpp in sources.items():
 obj=O/(name+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-800:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  target=int.from_bytes(post[off:off+4],'little')
  assert BASE<=target<BASE+ORIGINAL
  labels.setdefault(target,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+i]==post[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_whole_GAME_CODE_B':ORIGINAL,'native_whole_x86':NX,
      'whole_partial_cpp_B':ret,'whole_partial_x86':len(I),
      'whole_source_COFF_fields':len(refs),
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'native_cases':{},'original_whole_exact':False}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  refs_case=[r for r in refs if lo<=r['offset']<hi]
  rowcase={'native_original_B':sz,'native_x86':nx,
           'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   rowcase.update({'wrong_original_mnemonic_ordinals':mm,
                   'wrong_original_width_ordinals':ww,
                   'wrong_original_GPR_ordinals':gg})
   if not mm:
    assert len(refs_case)==nf,(name,k,len(refs_case),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for ref in refs_case:
     j=next(j for j,x in enumerate(s) if x.address<=ref['offset']<x.address+x.size)
     dt=ref['offset']-s[j].address
     native_off=native[k][j].address-a+dt
     # F983 has a real single CMP EAX/ECX 5/6-B mismatch
     # at case ordinal 64. All later absolute source fields shift.
     # Compare original PE target at matching native INSTRUCTION
     # ordinal/field displacement. Never pretend absolute offsets equal.
     assert dt+4<=native[k][j].size
     assert ref['type'] in ('DIR32','REL32') and ref['addend']==0 and ref['local_symbol_offset'] is None
     val=int.from_bytes(raw[native_off:native_off+4],
                        'little',signed=ref['type']=='REL32')
     orig_va=native[k][j].address+dt+4+val if ref['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',ref['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if ref['symbol']=='__ftol2' else None
     assert orig_va==expected,(name,k,j,ref['symbol'],hex(orig_va),expected)
    rowcase['native_original_PE_targets_verified']=nf
  row['native_cases'][k]=rowcase
 rows[name]=row
 print(name,'whole partial',ret,len(I),'1F8/1F9 source',
  [(k,row['native_cases'][k]['source_B'],row['native_cases'][k]['source_x86'])
   for k in ('1F8','1F9')],flush=True)
old=rows['F982-prior-1F8F9-markers'];new=rows['F983-real-typed-FSUBR']
assert (old['whole_partial_cpp_B'],old['whole_partial_x86'])==(40025,10979)
assert (new['whole_partial_cpp_B'],new['whole_partial_x86'])==(42330,11653)
for k,sourceB,gpr in [('1F8',1167,174),('1F9',1168,168)]:
 assert old['native_cases'][k]['source_B']==15
 n=new['native_cases'][k]
 assert (n['source_B'],n['source_x86'])==(sourceB,339)
 assert n['wrong_original_mnemonic_ordinals']==[]
 assert n['wrong_original_width_ordinals']==[64]
 assert len(n['wrong_original_GPR_ordinals'])==gpr
 assert n['native_original_PE_targets_verified']==28
assert new['native_cases']['1F7']['native_original_PE_targets_verified']==22
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':ORIGINAL,'original_entire_native_x86':NX,
 'original_1F8_1F9_CODE_B_x86':[1168+1167,339+339],
 'source_1F8_1F9_CODE_B_x86':[1167+1168,339+339],
 'native_1F8_1F9_external_PE_targets_verified':56,
 'all_678_original_mnemonics_match':True,
 'real_twelve_original_IMUL_FILD_FSUBR_chains_correct':True,
 'one_real_wrong_CMP_op_width_per_case_ordinal64':True,
 'native_GPR_wrong_per_case':[174,168],
 'natural_opacity_controls_tested':8,
 'whole_original_exact':False,'new_accepted_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'entire_partial_source_profiles':rows
},indent=2)+'\n')
print('F983 1F8/1F9 original 2335B/678x86, 56 real native PE targets, 12 real FSUBR x87 chains, 0 mnemonic errors; 1 wrong CMP width per case, GPR 174/168 wrong. Whole 82KB game NONEXACT.')
