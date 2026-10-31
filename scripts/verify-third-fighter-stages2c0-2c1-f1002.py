#!/usr/bin/env python3
"""F1002: true native 2C0/2C1 276-x86, all mnemonic/width/GPR roles align.

Fresh normal VC7.1 rebuild two TRACKED ENTIRE original-shaped PARTIAL
82KB fighter sources, old F1001 markers and F1002 real mixed RAW-X,
float-Y seven-parameter effects. Check original Japanese PE 2C0
498B/135x86, 2C1 522B/141x86, 14 typed PE fields each, full
151 original afterRET DIR32 and 522 nonfield DATA bytes.
Also verify previous two genuine 2BC/2BD PE and native geometry.
Do not credit original whole fighter (0x720 native frame remains).
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1002-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1001-prior-2C0-2C1-markers':R/'probes/FighterWhole004AC040F1001.cpp',
 'F1002-real-2C0-2C1':R/'probes/FighterWhole004AC040F1002.cpp'}
inc=(R/'probes/FighterThirdBossStages2C02C1F1002.inc').read_text()
assert inc.count('case 0x2C0:')==inc.count('case 0x2C1:')==1
assert inc.count('SpawnSevenRawXFloatYAt453B50(')==2
assert inc.count('SpawnSevenFloatAt453B50(')==2
assert inc.count('ApplyAt453E80(')==2
assert sources['F1002-real-2C0-2C1'].read_text().count('#include "FighterThirdBossStages2C02C1F1002.inc"')==1
sp=importlib.util.spec_from_file_location('f1002reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;AFTER=1126
orig_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(orig_whole)==WHOLEX and orig_whole[2].op_str=='esp, 0x720'
original_after=rd.pe_bytes_at(PE,BASE+WHOLE,AFTER)
cases={'2BC':(0x4BAC11,0x4BAF04,755,199,15),
       '2BD':(0x4BAF04,0x4BB1EA,742,196,15),
       '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
       '2C1':(0x4BC29A,0x4BC4A4,522,141,14)}
native={}
for k,(a,b,size,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
n=native['2C0']
assert n[15].op_str=='0x453e20'
assert n[42].op_str=='0x453b50'
assert n[40].op_str=='0x332'
assert n[34].op_str=='dword ptr [0x657888]'
assert n[66].op_str=='0x453e80' and n[69].op_str=='0x453d60' and n[72].op_str=='0x453d40'
assert n[84].op_str=='dword ptr [0x659284]'
assert n[96].op_str=='0x73' and n[98].op_str=='0x453c80'
assert n[105].op_str=='0x330' and n[107].op_str=='0x453b50'
assert n[111].op_str.endswith('+ 0xf10], dx') and n[113].op_str.endswith('+ 0xf12], 1')
n=native['2C1']
assert n[23].op_str.endswith('+ 0xf0c], 0xb4')
assert n[46].op_str=='0x32f' and n[48].op_str=='0x453b50'
assert n[59].op_str.endswith(', 4')
assert n[72].op_str=='0x453e80' and n[75].op_str=='0x453d40' and n[78].op_str=='0x453d60'
assert n[111].op_str=='0x32e' and n[113].op_str=='0x453b50'
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
 cwd=R,env=env,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==AFTER
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};masked=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in masked for i in range(off,off+4))
  masked.update(range(off,off+4))
  addr=int.from_bytes(original_after[off:off+4],'little')
  assert BASE<=addr<BASE+WHOLE
  labels.setdefault(addr,r['local_symbol_offset'])
 assert AFTER-len(masked)==522
 assert all(code[ret+j]==original_after[j] for j in range(AFTER) if j not in masked)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'whole_original_GAME_CODE_B':WHOLE,'native_whole_x86':WHOLEX,
  'whole_partial_CPP_CODE_B':ret,'whole_partial_x86':len(I),
  'source_partial_frame':I[2].op_str,
  'afterRET_native_DIR32':151,'afterRET_native_nonfield_DATA_equal_B':522,
  'whole_original_exact':False,'cases':{}}
 for k,(a,b,size,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':size,'native_original_x86':nx,
        'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   m=[j for j,(x,y) in enumerate(zip(native[k],s)) if x.mnemonic!=y.mnemonic]
   w=[j for j,(x,y) in enumerate(zip(native[k],s)) if x.size!=y.size]
   g=[j for j,(x,y) in enumerate(zip(native[k],s)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnemonics':m,'wrong_native_widths':w,
                'wrong_native_GPR_roles':g})
   if not m:
    assert len(fields)==nf,(label,k,len(fields),nf)
    original=rd.pe_bytes_at(PE,a,size)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address
     phys=native[k][j].address-a+dt
     if not w:assert phys==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     number=int.from_bytes(original[phys:phys+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+number if r['type']=='REL32' else number
     regex=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(regex.group(1),16) if regex else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_PE_external_targets_verified']=nf
  row['cases'][k]=item
 rows[label]=row
 print(label,'whole partial',ret,len(I),
 '2C0/2C1',[(k,row['cases'][k]['source_B'],row['cases'][k]['source_x86']) for k in ('2C0','2C1')],flush=True)
old=rows['F1001-prior-2C0-2C1-markers'];new=rows['F1002-real-2C0-2C1']
assert (old['whole_partial_CPP_CODE_B'],old['whole_partial_x86'])==(62063,17012)
assert (new['whole_partial_CPP_CODE_B'],new['whole_partial_x86'])==(63053,17284)
assert old['source_partial_frame']=='esp, 0x45c'
assert new['source_partial_frame']=='esp, 0x464'
for k in ('2C0','2C1'):
 assert old['cases'][k]['source_B']==15
 s=new['cases'][k]
 assert (s['source_B'],s['source_x86'])==cases[k][2:4]
 assert s['wrong_native_mnemonics']==s['wrong_native_widths']==s['wrong_native_GPR_roles']==[]
 assert s['native_PE_external_targets_verified']==14
for k,widths,roleswrong in [('2BC',[],128),('2BD',[133],125)]:
 s=new['cases'][k]
 assert s['wrong_native_mnemonics']==[] and s['wrong_native_widths']==widths
 assert len(s['wrong_native_GPR_roles'])==roleswrong
 assert s['native_PE_external_targets_verified']==15
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_original_fighter':'0x004AC040',
 'native_original_full_callable_CODE_B':WHOLE,'native_whole_x86':WHOLEX,
 'native_original_2C0_2C1_CODE_B_x86':[498+522,135+141],
 'native_source_all_276_mnemonics_widths_GPR_roles_match':True,
 'real_original_2C0_2C1_external_PE_targets':28,
 'native_previous_2BC_2BD_PE_and_GPR_roles_unchanged':True,
 'original_father_whole_exact':False,'new_exact_whole_original_GAME_CODE_B':0,
 'mass_cold_replay':False,
 'complete_original_shaped_partial_fathers':rows
},indent=2)+'\n')
print('F1002 original 2C0+2C1 1020B/276x86, ALL native mnemonic/width/GPR roles and 28 physical PE targets, previous 2BC/2BD unchanged. Full giant NONEXACT.')
