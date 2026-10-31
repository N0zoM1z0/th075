#!/usr/bin/env python3
"""F1009 native 2FB rebound restores preceding 2FA shared-tail width.

Freshly compile two TRACKED complete original-shaped PARTIAL 82KB
normal VC7.1 fighters, F1008 prior 2FB marker vs F1009 real C++.
Native original 2FB 1428B/411x86/33 true PE call/global targets.
All 411 positional mnemonic and GPR roles align, native wrong
width only last shared father tail JMP 5B versus short2B. Genuine
new 2FB restores prior original 2FA last JMP width [185] -> [].
Also verify 2F9 and 2E5/2E6 plus earlier real 2C0..2C3,
entire original 151 afterRET DIR32 and 522 nonfield data.
Never accept interior game cases as whole original callable CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1009-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1008-prior-2FB-marker':R/'probes/FighterWhole004AC040F1008.cpp',
         'F1009-real-rebound-2FB':R/'probes/FighterWhole004AC040F1009.cpp'}
inc=(R/'probes/FighterThirdBossRebound2FBF1009.inc').read_text()
assert inc.count('case 0x2FB:')==1
assert inc.count('SpawnSevenFloatAt453B50(0x')==7
assert inc.count('SpawnSevenFloatAt453B50(0x33E,')==1
assert inc.count('StartAnimationAt46D000(0xC8)')==1
assert inc.count('g_F983_BurstYAt00659490')==6
assert inc.count('reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44')==1
assert sources['F1009-real-rebound-2FB'].read_text().count('#include "FighterThirdBossRebound2FBF1009.inc"')==1
sp=importlib.util.spec_from_file_location('f1009reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;ORIG_X86=22721;AFTER=1126
original=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original)==ORIG_X86 and original[2].op_str=='esp, 0x720'
post=rd.pe_bytes_at(PE,BASE+WHOLE,AFTER)
cases={
 '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
 '2F9':(0x4BEC88,0x4BF16E,1254,326,33),
 '2FA':(0x4BF16E,0x4BF40E,672,186,18),
 '2FB':(0x4BF40E,0x4BF9A2,1428,411,33)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(I)==nx and I[-1].address+I[-1].size==b
 native[k]=I
n=native['2FB']
assert n[9].op_str=='0x453e20'
assert n[151].op_str=='0x40fac0' and n[149].op_str=='0x2f9'
assert n[120].op_str=='0x453b50' and n[118].op_str=='0x33e'
assert [n[j].op_str for j in (183,204,225,246,267,288)]==['0x453b50']*6
assert [n[j].op_str for j in (181,202,223,244,265,286)]==list(map(hex,range(0x338,0x33e)))
assert all(n[j].op_str=='dword ptr [0x659490]' for j in (169,190,211,232,253,274))
assert n[291].op_str=='0x46d000'
assert n[339].op_str=='dword ptr [0x65787c]'
assert n[357].op_str=='dword ptr [0x65920c]'
assert n[390].mnemonic=='fcomp' and n[390].op_str.endswith('+ 0x44]')
assert n[-1].mnemonic=='jmp' and n[-1].op_str=='0x4c03a7' and n[-1].size==5
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(REG.findall(x.op_str))
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
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==AFTER
 data_reloc=[r for r in refs if r['offset']>=end]
 assert len(data_reloc)==151
 labels={};mask=set()
 for r in data_reloc:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  a=int.from_bytes(post[off:off+4],'little')
  assert BASE<=a<BASE+WHOLE
  labels.setdefault(a,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+i]==post[i] for i in range(AFTER) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'native_entire_original_callable_CODE_B':WHOLE,'original_x86':ORIG_X86,
      'partial_SOURCE_CODE_B':end,'partial_source_x86':len(I),
      'partial_frame':I[2].op_str,'native_afterRET_DIR32':151,
      'native_afterRET_nonfield_equal_B':522,
      'native_entire_original_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  seq=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':sz,'native_x86':nx,'source_B':hi-lo,'source_x86':len(seq)}
  if len(seq)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],seq)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],seq)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],seq)) if roles(n)!=roles(x)]
   item.update({'wrong_original_mnemonics':mm,'wrong_original_widths':ww,'wrong_original_GPRs':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-seq[j].address
     off=native[k][j].address-a+dt
     # All original PE fields lie before any final shared-tail JMP width defect.
     assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+value if r['type']=='REL32' else value
     mt=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(mt.group(1),16) if mt else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_genuine_external_PE_targets']=nf
  row['cases'][k]=item
 rows[label]=row
 print(label,'complete original-shaped PARTIAL source',end,len(I),
 '2FA/2FB',[(k,row['cases'][k]['source_B'],row['cases'][k]['source_x86']) for k in ('2FA','2FB')],flush=True)
old=rows['F1008-prior-2FB-marker'];new=rows['F1009-real-rebound-2FB']
assert (old['partial_SOURCE_CODE_B'],old['partial_source_x86'])==(68785,18852)
assert (new['partial_SOURCE_CODE_B'],new['partial_source_x86'])==(70201,19261)
assert old['partial_frame']=='esp, 0x50c' and new['partial_frame']=='esp, 0x53c'
assert old['cases']['2FB']['source_B']==12
cur=new['cases']['2FB']
assert (cur['source_B'],cur['source_x86'])==(1425,411)
assert cur['wrong_original_mnemonics']==cur['wrong_original_GPRs']==[]
assert cur['wrong_original_widths']==[410]
assert cur['native_genuine_external_PE_targets']==33
prev=old['cases']['2FA'];now=new['cases']['2FA']
assert (prev['source_B'],prev['source_x86'])==(669,186)
assert prev['wrong_original_widths']==[185] and prev['wrong_original_GPRs']==[]
assert (now['source_B'],now['source_x86'])==(672,186)
assert now['wrong_original_mnemonics']==now['wrong_original_widths']==now['wrong_original_GPRs']==[]
assert now['native_genuine_external_PE_targets']==18
for k in ('2C0','2C1','2C2','2C3','2E5','2E6','2F9'):
 item=new['cases'][k]
 assert item['wrong_original_mnemonics']==item['wrong_original_widths']==item['wrong_original_GPRs']==[]
 assert item['native_genuine_external_PE_targets']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_native_fighter':'0x004AC040',
 'original_complete_callable_CODE_B':WHOLE,'native_whole_x86':ORIG_X86,
 'native_true_2FB_CODE_B_x86':[1428,411],
 'source_true_2FB_CODE_B_x86':[1425,411],
 'all_original_2FB_mnemonics_GPR_roles_match':True,
 'native_2FB_wrong_width_last_shared_JMP':[410],
 'real_original_2FB_typed_PE_targets_verified':33,
 'genuine_new_2FB_restores_previous_2FA_JMP_width':{'before':[185],'after':[]},
 'prior_2C0_2C3_2E5_2E6_2F9_all_GPR_and_PE_preserved':True,
 'entire_original_callable_exact':False,'newly_accepted_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'normal_complete_partial_parent_profiles':rows
},indent=2)+'\n')
print('F1009 native 2FB 1428B/411x86/33 real PE targets; source all mnemonic/GPR, one terminal JMP width; real 2FB restores original 2FA width and 186 native GPR roles. Whole 82KB NONEXACT.')
