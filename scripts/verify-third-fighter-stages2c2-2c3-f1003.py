#!/usr/bin/env python3
"""F1003 actual Japanese original 2C2/2C3 cases: all 279 native GPRs align.

Fresh normal VC7.1 compile two TRACKED ENTIRE 82KB original-shaped
PARTIAL fighter fathers, prior F1002 2C2/2C3 markers versus F1003
real source. Original 2C2 515B/138 x86, 2C3 522B/141 x86,
14 PE fields each. Independently check native control-flow branch
to shared tail after 2C2 completion shot, original 2C3 F0C=300,
genuine PE/COFF symbols, previous F1002 2C0/2C1 case geometry,
all 151 afterRET DIR32 and 522 native DATA nonfield bytes.
This is NOT an entire original game function exact acceptance.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1003-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1002-prior-markers':R/'probes/FighterWhole004AC040F1002.cpp',
 'F1003-real-2C2-2C3':R/'probes/FighterWhole004AC040F1003.cpp'}
inc=(R/'probes/FighterThirdBossStages2C22C3F1003.inc').read_text()
assert inc.count('case 0x2C2:')==inc.count('case 0x2C3:')==1
assert inc.count('SpawnSevenRawXFloatYAt453B50(')==2
assert inc.count('SpawnSevenFloatAt453B50(')==2
assert inc.count('ApplyAt453E80(')==2
assert inc.count('S16(0xF0C)=300;')==1
assert sources['F1003-real-2C2-2C3'].read_text().count('#include "FighterThirdBossStages2C22C3F1003.inc"')==1
sp=importlib.util.spec_from_file_location('f1003reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIG=82796;ORIG_NX=22721;DATA=1126
full=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIG),BASE))
assert len(full)==ORIG_NX and full[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+ORIG,DATA)
cases={'2C0':(0x4BC0A8,0x4BC29A,498,135,14),
       '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
       '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
       '2C3':(0x4BC6A7,0x4BC8B1,522,141,14)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(I)==nx and I[-1].address+I[-1].size==b
 native[k]=I
n=native['2C2']
assert n[27].op_str=='0x40fac0'
assert n[29].op_str.endswith('+ 0xf12], 1')
assert n[42].op_str=='0x332' and n[44].op_str=='0x453b50'
assert n[45].mnemonic=='jmp' and n[45].op_str=='0x4c03a7'
assert n[69].op_str=='0x453e80' and n[72].op_str=='0x453d60' and n[75].op_str=='0x453d40'
assert n[87].op_str=='dword ptr [0x659284]'
assert n[99].op_str=='0x74' and n[101].op_str=='0x453c80'
assert n[108].op_str=='0x330' and n[110].op_str=='0x453b50'
assert n[116].op_str.endswith('+ 0xf12], 1')
n=native['2C3']
assert n[20].op_str.endswith(', 5') and n[21].mnemonic=='jle'
assert n[23].op_str.endswith('+ 0xf0c], 0x12c')
assert n[46].op_str=='0x32f' and n[48].op_str=='0x453b50'
assert n[59].op_str.endswith(', 4')
assert n[72].op_str=='0x453e80' and n[75].op_str=='0x453d60' and n[78].op_str=='0x453d40'
assert n[90].op_str=='dword ptr [0x659284]'
assert n[102].op_str=='0x74' and n[104].op_str=='0x453c80'
assert n[111].op_str=='0x32e' and n[113].op_str=='0x453b50'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for label,src in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=env,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(native_data[off:off+4],'little')
  assert BASE<=va<BASE+ORIG
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_entire_GAME_CODE_B':ORIG,'original_whole_x86':ORIG_NX,
  'partial_compiled_CODE_B':end,'partial_compiled_x86':len(I),
  'partial_stack_frame':I[2].op_str,
  'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
  'whole_original_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_CODE_B':sz,'native_original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   badm=[j for j,(n,s) in enumerate(zip(native[k],part)) if n.mnemonic!=s.mnemonic]
   badw=[j for j,(n,s) in enumerate(zip(native[k],part)) if n.size!=s.size]
   badg=[j for j,(n,s) in enumerate(zip(native[k],part)) if roles(n)!=roles(s)]
   item.update({'wrong_native_mnemonics':badm,
                'wrong_native_widths':badw,'wrong_native_GPRs':badg})
   if not badm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-part[j].address
     off=native[k][j].address-a+dt
     if not badw:assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['original_PE_external_targets_verified']=nf
  row['cases'][k]=item
 results[label]=row
 print(label,'complete partial father',end,len(I),
 '2C2/2C3',[(k,row['cases'][k]['source_CODE_B'],row['cases'][k]['source_x86']) for k in ('2C2','2C3')],flush=True)
old=results['F1002-prior-markers'];new=results['F1003-real-2C2-2C3']
assert (old['partial_compiled_CODE_B'],old['partial_compiled_x86'])==(63053,17284)
assert (new['partial_compiled_CODE_B'],new['partial_compiled_x86'])==(64060,17559)
assert old['partial_stack_frame']=='esp, 0x464'
assert new['partial_stack_frame']=='esp, 0x46c'
for k in ('2C2','2C3'):
 assert old['cases'][k]['source_CODE_B']==15
 r=new['cases'][k]
 assert (r['source_CODE_B'],r['source_x86'])==cases[k][2:4]
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPRs']==[]
 assert r['original_PE_external_targets_verified']==14
for k in ('2C0','2C1'):
 r=new['cases'][k]
 assert (r['source_CODE_B'],r['source_x86'])==cases[k][2:4]
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPRs']==[]
 assert r['original_PE_external_targets_verified']==14
(O/'verified-summary.json').write_text(json.dumps({
 'original_SHA_pinned_Japanese_fighter':'0x004AC040',
 'original_complete_GAME_CODE_B':ORIG,'original_whole_x86':ORIG_NX,
 'native_2C2_2C3_CODE_B_x86':[515+522,138+141],
 'all_279_original_mnemonic_width_GPR_roles_match':True,
 'real_2C2_2C3_original_typed_PE_targets_verified':28,
 'previous_2C0_2C1_native_GPR_and_PE_unchanged':True,
 'all_four_original_2C0_to_2C3_GPR_roles_match':True,
 'original_2C2_completion_has_real_shared_tail_JMP':True,
 'whole_original_exact':False,'newly_credited_game_CODE_B':0,
 'mass_cold_replay':False,'full_original_shaped_partial_parent_profiles':results
},indent=2)+'\n')
print('F1003 native2C2+2C3 1037B/279x86, all original mnem/width/GPR roles, 28 true PE fields, prior 2C0/2C1 remain GPR-aligned. Entire 82KB NONEXACT.')
