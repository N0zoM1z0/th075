#!/usr/bin/env python3
"""F1019 original 2EF/2F0, both 2229B/573 x86/80 PE; whole 22721 x86.

Fresh normal VC7.1 compile TWO TRACKED ENTIRE original-shaped fighter
PARTIAL C++ fathers: F1018 marker versus F1019 native 2EF+2F0.
Independently read pinned original Japanese PE, all original
typed zero-addend physical PE destinations, all 151 genuine
afterRET DIR32 case labels and all 522 nonfield DATA bytes.
F1019 naturally produces the original complete 22721 x86
instruction COUNT, but 82802B/0x724 frame vs original
82796B/0x720 frame; 2BE source still has 125 wrong GPR
roles. No full original whole callable CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1019-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1018-prior-two-markers':R/'probes/FighterWhole004AC040F1018.cpp',
         'F1019-both-real-arc-states':R/'probes/FighterWhole004AC040F1019.cpp'}
inc=(R/'probes/FighterThirdBossPairedArc2EF2F0F1019.inc').read_text()
assert inc.count('case 0x2EF:')==inc.count('case 0x2F0:')==1
assert inc.count('SetAngleBitsAt40FB70(I32(0x314),100.0f);')==10
assert inc.count('*reinterpret_cast<const float*>(RAW+0x50)')==10
assert inc.count('if (S16(0xF04)<g_F1004_ModeAt006714D0*2+8)')==2
assert inc.count('SpawnFloatXYAt453A70(0x38F,')==10
assert sources['F1019-both-real-arc-states'].read_text().count('#include "FighterThirdBossPairedArc2EF2F0F1019.inc"')==1
sp=importlib.util.spec_from_file_location('f1019reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;NATIVE=82796;NX=22721;DATA=1126
nativewhole=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE),BASE))
assert len(nativewhole)==NX and nativewhole[2].op_str=='esp, 0x720'
original_data=rd.pe_bytes_at(PE,BASE+NATIVE,DATA)
cases={
 '2BE':(0x4BB1EA,0x4BB831,1607,471,50),
 '2BF':(0x4BB831,0x4BC0A8,2167,616,65),
 '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2DB':(0x4BC8B1,0x4BD017,1894,548,38),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
 '2EF':(0x4BDB1E,0x4BE3D3,2229,573,80),
 '2F0':(0x4BE3D3,0x4BEC88,2229,573,80),
 '2F9':(0x4BEC88,0x4BF16E,1254,326,33),
 '2FA':(0x4BF16E,0x4BF40E,672,186,18),
 '2FB':(0x4BF40E,0x4BF9A2,1428,411,33),
 '302':(0x4BF9A2,0x4BFDAB,1033,279,25),
 '303':(0x4BFDAB,0x4C01A1,1014,267,29),
 '31B':(0x4C01A1,0x4C02A2,257,76,9),
 '31C':(0x4C02A2,0x4C037D,219,63,7),
 'default':(0x4C037D,0x4C03A7,42,13,3)}
native={}
for key,(a,b,size,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(n)==nx and n[-1].address+n[-1].size==b
 native[key]=n
n1,n2=native['2EF'],native['2F0']
assert n1[32].op_str=='dword ptr [0x658044]'
assert n2[32].op_str=='dword ptr [0x658354]'
assert n1[114].op_str.endswith(', 0x3fc00000')
assert n2[114].op_str.endswith(', 0x40600000')
for j in (227,313,399,485):
 assert n1[j].op_str.endswith(', 0x32') and n2[j].op_str.endswith(', 0x46')
for n in (n1,n2):
 assert [j for j,x in enumerate(n) if x.mnemonic=='call' and x.op_str=='0x453a70']==[185,271,357,443,529]
 assert all(n[j].op_str=='0x40fb70' for j in (160,246,332,418,504))
 assert all(n[j].op_str=='0x6406ac' for j in (128,134,214,220,300,306,386,392,472,478))
 assert n[-1].op_str=='0x4c03a7'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(RX.findall(i.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1100:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==DATA
 tables=[r for r in refs if r['offset']>=ret]
 assert len(tables)==151
 labels={};mask=set()
 for r in tables:
  offset=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(q not in mask for q in range(offset,offset+4))
  mask.update(range(offset,offset+4))
  va=int.from_bytes(original_data[offset:offset+4],'little')
  assert BASE<=va<BASE+NATIVE
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+j]==original_data[j] for j in range(DATA) if j not in mask)
 assert all(a in labels for k,(a,b,_,_,_) in cases.items())
 assert all(b in labels if k!='default' else b==0x4C03A7 for k,(a,b,_,_,_) in cases.items())
 epilogue=list(D.disasm(rd.pe_bytes_at(PE,0x4C03A7,5),0x4C03A7))
 assert [(x.mnemonic,x.size) for x in I[-4:]]==[(x.mnemonic,x.size) for x in epilogue]
 assert I[-4].address==ret-5
 row={'native_whole_GAME_CODE_B':NATIVE,'native_whole_x86':NX,
  'compiled_PARTIAL_CODE_B':ret,'compiled_PARTIAL_x86':len(I),
  'partial_compiler_frame':I[2].op_str,
  'original_afterRET_DIR32':151,'native_original_nonfield_DATA_equal_B':522,
  'original_whole_callable_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo=labels[a]
  hi=I[-4].address if k=='default' else labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_x86':nx,
    'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   m=[j for j,(x,y) in enumerate(zip(native[k],s)) if x.mnemonic!=y.mnemonic]
   w=[j for j,(x,y) in enumerate(zip(native[k],s)) if x.size!=y.size]
   g=[j for j,(x,y) in enumerate(zip(native[k],s)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnemonic_ordinals':m,'wrong_native_width_ordinals':w,
      'wrong_native_GPR_ordinals':g})
   if not m:
    assert len(fields)==nf,(label,k,len(fields),nf)
    orig=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address;phys=native[k][j].address-a+dt
     if not w:assert phys==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(orig[phys:phys+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+val if r['type']=='REL32' else val
     match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(match.group(1),16) if match else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_real_typed_PE_targets_verified']=nf
  row['cases'][k]=item
 rows[label]=row
 print(label,'whole original-shaped source',ret,len(I),I[2].op_str,
  '2EF/2F0 sources',[(k,row['cases'][k]['source_CODE_B'],row['cases'][k]['source_x86']) for k in ('2EF','2F0')],flush=True)
old=rows['F1018-prior-two-markers'];new=rows['F1019-both-real-arc-states']
assert (old['compiled_PARTIAL_CODE_B'],old['compiled_PARTIAL_x86'])==(78374,21579)
assert (new['compiled_PARTIAL_CODE_B'],new['compiled_PARTIAL_x86'])==(82802,NX)
assert old['partial_compiler_frame']=='esp, 0x654' and new['partial_compiler_frame']=='esp, 0x724'
for k in ('2EF','2F0'):
 assert old['cases'][k]['source_CODE_B']==15
 obj=new['cases'][k]
 assert (obj['source_CODE_B'],obj['source_x86'])==(2229,573)
 assert obj['wrong_native_mnemonic_ordinals']==obj['wrong_native_width_ordinals']==obj['wrong_native_GPR_ordinals']==[]
 assert obj['native_real_typed_PE_targets_verified']==80
for k in cases:
 if k in ('2EF','2F0'):continue
 obj=new['cases'][k]
 assert (obj['source_CODE_B'],obj['source_x86'])==cases[k][2:4]
 assert obj['wrong_native_mnemonic_ordinals']==obj['wrong_native_width_ordinals']==[]
 assert len(obj['wrong_native_GPR_ordinals'])==(125 if k=='2BE' else 0),(k,len(obj['wrong_native_GPR_ordinals']))
 assert obj['native_real_typed_PE_targets_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':NATIVE,'original_entire_x86':NX,
 'compiled_whole_PARTIAL_CODE_B':82802,'compiled_whole_PARTIAL_x86':NX,
 'original_and_source_instruction_COUNTS_identical':True,
 'original_and_source_CODE_B_difference':6,
 'original_native_stack_frame':'0x720','source_stack_frame':'0x724',
 'native_2EF_2F0_code_B_x86':[4458,1146],
 'all_1146_native_mnemonics_widths_GPR_roles_match':True,
 'both_true_native_2EF_2F0_PE_targets_verified':160,
 'remaining_real_2BE_GPR_role_defects':125,
 'all_other_tested_native_case_roles_and_151_DIR32_522_nonfield_DATA_valid':True,
 'original_whole_exact':False,'new_accepted_whole_game_CODE_B':0,
 'mass_cold_replay':False,'native_entire_original_shaped_partial_Cpp_profiles':rows
},indent=2)+'\n')
print('F1019 true original2EF+2F0 4458B/1146 native x86/160 PE fields, all mnemonic/width/GPR correct; WHOLE parent now matches original 22721 x86 instruction COUNT but is 82802 vs82796 native and frame0x724 vs0x720, 2BE 125 GPR errors. NONEXACT.')
