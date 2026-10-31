#!/usr/bin/env python3
"""F976: true 004AC040 1A0 5/8 random loops and preceding 191 x87 phase.

Cold compile tracked F975 marker and tracked F976 real 1A0 in two
ENTIRE original-shaped normal VC7.1 PARTIAL 82KB fighter parents.
Independently compare SHA-pinned Japanese native 1A0 570B/148 x86,
12 original i386 PE-targeted fields, actual original Y float FIADD,
two RandAt455580 calls per loop iteration and source operand order,
151 original afterRET DIR32 and 522 nonfield DATA bytes. Also prove
the real source increases parent stack and repairs four original
191 x87 width errors, but 82KB whole remains NONEXACT.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f976-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F975-original-1A0-marker':R/'probes/FighterWhole004AC040F975.cpp',
         'F976-real-random-loop':R/'probes/FighterWhole004AC040F976.cpp'}
inc=(R/'probes/FighterThirdBossRandomLoop1A0F976.inc').read_text()
assert inc.count('case 0x1A0:')==1
assert inc.count('for (int shot=0;shot<5;++shot)')==1
assert inc.count('for (int shot=0;shot<8;++shot)')==1
assert inc.split('case 0x1A0:')[1].count('RandAt455580(0,20)')==2
assert sources['F976-real-random-loop'].read_text().count('#include "FighterThirdBossRandomLoop1A0F976.inc"')==1
sp=importlib.util.spec_from_file_location('reader976',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIG=82796;ORIG_X86=22721;DATA=1126
native_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIG),BASE))
assert len(native_whole)==ORIG_X86 and native_whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+ORIG,DATA)
cases={'191':(0x4B23BC,0x4B2611,597,147,11),
       '192':(0x4B2611,0x4B28ED,732,177,11),
       '1A0':(0x4B4097,0x4B42D1,570,148,12)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(n)==nx and b-a==sz and n[-1].address+n[-1].size==b
 native[k]=n
N=native['1A0']
assert N[40].op_str=='eax, 2'
assert N[42].op_str=='dword ptr [ebp - 0x10], 0'
assert N[47].op_str=='dword ptr [ebp - 0x10], 5'
assert N[65].mnemonic=='fiadd'
assert N[66].mnemonic=='fstp'
assert N[70].op_str=='0x455580'
assert N[72].mnemonic=='fild' and N[73].mnemonic=='fadd'
assert N[79].op_str=='0x455580'
assert N[92].op_str=='0x453b50'
assert N[95].op_str=='dword ptr [ebp - 0x14], 0'
assert N[100].op_str=='dword ptr [ebp - 0x14], 8'
assert N[118].mnemonic=='fiadd'
assert N[125].mnemonic=='fild'
assert N[145].op_str=='0x453b50'
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
  cwd=R,env=env,capture_output=True,text=True,timeout=335)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
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
 mp={};mask=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+ORIG
  mp.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+j]==after[j] for j in range(DATA) if j not in mask)
 assert all(a in mp and b in mp for a,b,_,_,_ in cases.values())
 row={'original_whole_CODE_B':ORIG,'original_whole_x86':ORIG_X86,
   'whole_partial_CPP_B':ret,'whole_partial_CPP_x86':len(I),
   'partial_CPP_stack_frame':I[2].op_str,
   'partial_saved_receiver_EBP':I[3].op_str,
   'afterRET_true_native_DIR32':151,'afterRET_native_nonfield_equal_B':522,
   'source_COFF_refs':len(refs),'real_states':{},'original_whole_exact':False}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=mp[a],mp[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_CODE_B':sz,'native_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnem_ordinals':mm,
    'wrong_native_width_ordinals':ww,'wrong_native_GPR_ordinals':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    nbytes=rd.pe_bytes_at(PE,a,sz)
    for f in fields:
     j=next(j for j,x in enumerate(s) if x.address<=f['offset']<x.address+x.size)
     dt=f['offset']-s[j].address
     noff=native[k][j].address-a+dt
     assert f['type'] in ('REL32','DIR32') and f['addend']==0 and f['local_symbol_offset'] is None
     value=int.from_bytes(nbytes[noff:noff+4],'little',signed=f['type']=='REL32')
     dest=native[k][j].address+dt+4+value if f['type']=='REL32' else value
     m=re.search(r'At([0-9A-Fa-f]{6,8})',f['symbol'])
     expect=int(m.group(1),16) if m else 0x6406AC if f['symbol']=='__ftol2' else None
     assert dest==expect,(label,k,j,f['symbol'],hex(dest),expect)
    item['original_typed_PE_targets_verified']=len(fields)
  row['real_states'][k]=item
 rows[label]=row
 print(label,'complete partial father',ret,len(I),'frame',I[2].op_str,
       'case1A0 B/x86',row['real_states']['1A0']['source_CODE_B'],
                         row['real_states']['1A0']['source_x86'],
       'prior191 sourceB',row['real_states']['191']['source_CODE_B'],flush=True)
old=rows['F975-original-1A0-marker'];new=rows['F976-real-random-loop']
assert (old['whole_partial_CPP_B'],old['whole_partial_CPP_x86'])==(33488,9195)
assert (new['whole_partial_CPP_B'],new['whole_partial_CPP_x86'])==(34055,9341)
assert old['partial_CPP_stack_frame']=='esp, 0x144'
assert new['partial_CPP_stack_frame']=='esp, 0x16c'
assert old['partial_saved_receiver_EBP']=='dword ptr [ebp - 0x10], ecx'
assert new['partial_saved_receiver_EBP']=='dword ptr [ebp - 0x18], ecx'
assert old['real_states']['1A0']['source_CODE_B']==15
true=new['real_states']['1A0']
assert (true['source_CODE_B'],true['source_x86'])==(570,148)
assert true['wrong_native_mnem_ordinals']==true['wrong_native_width_ordinals']==[]
assert len(true['wrong_native_GPR_ordinals'])==66
assert true['original_typed_PE_targets_verified']==12
assert old['real_states']['191']['source_CODE_B']==561
assert new['real_states']['191']['source_CODE_B']==573
assert len(old['real_states']['191']['wrong_native_width_ordinals'])==12
assert len(new['real_states']['191']['wrong_native_width_ordinals'])==8
assert new['real_states']['192']['original_typed_PE_targets_verified']==11
(O/'verified-summary.json').write_text(json.dumps({
 'original_SHA_pinned_Japanese_fighter':'0x004AC040',
 'native_original_whole_CODE_B':ORIG,'native_original_whole_x86':ORIG_X86,
 'original_native_1A0_B_x86':[570,148],
 'source_real_native_1A0_B_x86':[570,148],
 'original_1A0_native_PE_targets_verified':12,
 'native_1A0_mnemonics_and_widths_matched':True,
 'native_1A0_GPR_role_errors':66,
 'native_full_frame_still_not_recovered':True,
 'natural_loop_source_changes_parent_frame_from':'0x144',
 'natural_loop_source_changes_parent_frame_to':'0x16c',
 'native_prior_191_wrong_widths_before_after':[12,8],
 'original_whole_exact':False,'new_accepted_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'original_shaped_parent_profiles':rows
},indent=2)+'\n')
print('F976 genuine native 1A0 570B/148x86/12 PE fields, all mnemonic/width matches but 66 GPR roles wrong; real parent x87 scratch phase repairs four previous 191 width errors. Original 82KB whole NONEXACT.')
