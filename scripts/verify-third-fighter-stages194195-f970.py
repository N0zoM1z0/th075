#!/usr/bin/env python3
"""F970: original third-fighter 194+195 each 644B/168x86, 11 native PE fields.

Fresh-build two tracked entire original-shaped normal VC7.1 PARTIAL
82KB fighter parents, F969 old markers and F970 real cases. Check
the SHA-pinned Japanese original whole PE for 192/194/195 real source
geometry, 33 true i386 PE/COFF field targets, all 151 original afterRET
DIR32 entries and 522 nonfield DATA B. A 644-byte internal case
matching instruction widths is NOT whole original game exactness.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f970-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F969-old-194195-markers':R/'probes/FighterWhole004AC040F969.cpp',
         'F970-real-194195':R/'probes/FighterWhole004AC040F970.cpp'}
frag=(R/'probes/FighterThirdBossStages194195F970.inc').read_text()
assert frag.count('case 0x194:')==frag.count('case 0x195:')==1
assert sources['F970-real-194195'].read_text().count('#include "FighterThirdBossStages194195F970.inc"')==1
sp=importlib.util.spec_from_file_location('f970reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLE_X86=22721;DATA=1126
whole_original=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(whole_original)==WHOLE_X86 and whole_original[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
actual={
 '192':(0x4B2611,0x4B28ED,732,177,11),
 '194':(0x4B28ED,0x4B2B71,644,168,11),
 '195':(0x4B2B71,0x4B2DF5,644,168,11)}
orig={}
for k,(a,b,sz,nx,nr) in actual.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(n)==nx and b-a==sz and n[-1].address+n[-1].size==b
 orig[k]=n
for state in ('194','195'):
 n=orig[state]
 assert [n[j].mnemonic for j in (35,36,59,60,83,84)]==['mov','fild','mov','fild','mov','fild']
 assert [n[j].op_str for j in (53,77,101)]==['0x320']*3
 assert [n[j].op_str for j in (55,79,103)]==['0x453a70']*3
 assert [n[j].op_str for j in (150,152)]==['0x335','0x453a70']
 assert n[162].op_str=='dword ptr [ecx + 0x50], 0xc0c00000' if state=='194' else n[162].op_str=='dword ptr [edx + 0x50], 0xc0c00000'
 assert n[164].op_str.endswith(', 0x41100000')
assert orig['194'][34].op_str=='eax, [edx*4 - 8]'
assert orig['195'][34].op_str=='ecx, [eax*4 - 0x2d]'
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
   cwd=R,env=env,capture_output=True,text=True,timeout=340)
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
  d=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(d,d+4))
  mask.update(range(d,d+4))
  va=int.from_bytes(after[d:d+4],'little')
  assert BASE<=va<BASE+WHOLE
  mp.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in mp and b in mp for a,b,_,_,_ in actual.values())
 row={'original_whole_callable_CODE_B':WHOLE,'original_whole_x86':WHOLE_X86,
      'partial_source_CODE_B':ret,'partial_source_x86':len(I),
      'whole_source_COFF_refs':len(refs),
      'afterRET_native_DIR32':151,'afterRET_original_nonfield_equal':522,
      'native_cases':{},'whole_original_exact':False}
 for state,(a,b,sz,nx,nr) in actual.items():
  lo,hi=mp[a],mp[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[i for i,(x,y) in enumerate(zip(orig[state],s)) if x.mnemonic!=y.mnemonic]
   ww=[i for i,(x,y) in enumerate(zip(orig[state],s)) if x.size!=y.size]
   gg=[i for i,(x,y) in enumerate(zip(orig[state],s)) if roles(x)!=roles(y)]
   item.update({'wrong_mnemonic_ordinals':mm,
               'wrong_width_ordinals':ww,'wrong_GPR_ordinals':gg})
   if not mm:
    assert len(fields)==nr,(label,state,len(fields),nr)
    native_bytes=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(i for i,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address
     original_offset=orig[state][j].address-a+dt
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     num=int.from_bytes(native_bytes[original_offset:original_offset+4],
                       'little',signed=r['type']=='REL32')
     target=orig[state][j].address+dt+4+num if r['type']=='REL32' else num
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     exp=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==exp,(label,state,j,r['symbol'],hex(target),exp)
    item['native_PE_targets_verified']=len(fields)
  row['native_cases'][state]=item
 rows[label]=row
 print(label,'complete original-shaped father',ret,len(I),'194/195 source',
      [(k,row['native_cases'][k]['source_CODE_B'],row['native_cases'][k]['source_x86']) for k in ('194','195')],flush=True)
old=rows['F969-old-194195-markers'];new=rows['F970-real-194195']
assert (old['partial_source_CODE_B'],old['partial_source_x86'])==(27610,7578)
assert (new['partial_source_CODE_B'],new['partial_source_x86'])==(28868,7910)
for case in ('194','195'):
 assert old['native_cases'][case]['source_CODE_B']==15
 r=new['native_cases'][case]
 assert (r['source_CODE_B'],r['source_x86'])==(644,168)
 assert r['wrong_mnemonic_ordinals']==r['wrong_width_ordinals']==[]
 assert len(r['wrong_GPR_ordinals'])==118
 assert r['native_PE_targets_verified']==11
assert new['native_cases']['192']['native_PE_targets_verified']==11
assert new['native_cases']['192']['wrong_width_ordinals']==[]
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_game_fighter':'0x004AC040',
 'complete_original_callable_CODE_B':WHOLE,
 'complete_original_native_x86':WHOLE_X86,
 'native_two_original_194195_CODE_B_x86':[1288,336],
 'source_two_native_194195_CODE_B_x86':[1288,336],
 'original_native_194195_PE_targets_verified':22,
 'original_194195_mnemonic_width_diffs':0,
 'original_194195_GPR_wrong_roles':[118,118],
 'original_native_EBP_register_and_stack_owner_missing':True,
 'original_whole_exact':False,'new_accepted_original_CODE_B':0,
 'mass_cold_replay':False,'full_partial_source_profiles':rows,
},indent=2)+'\n')
print('F970 native 194+195 1288 original interior CODE B/336 x86 with all native mnemonic/width positions and 22 real PE targets; 118/118 GPR roles wrong, native original whole 82KB still NONEXACT.')
