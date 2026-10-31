#!/usr/bin/env python3
"""F1007: native 2FA trajectory and repair of preceding 2E6 shared-tail JMP.

Fresh normal VC7.1 cold compile TWO ENTIRE tracked original-shaped
PARTIAL 82KB fighter C++ parents, F1005 with old 2FA marker and
F1007 with true native 2FA. Original2FA 672B/186x86 and 18
physical typed PE global/call fields, all opcode mnemonics,
one last shared-parent JMP width 5B vs source 2B and 113
GPR-role differences. Genuine 2FA source repair changes prior
original 2E6 width [589] from wrong to native, preserving all
590 GPR roles and 47 original PE fields. Also check 2E5 and
all 2C0..2C3, original 151 afterRET DIR32 and 522 nonfield.
No whole 82KB callable exact credit from internal cases.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1007-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1005-prior-2FA-marker':R/'probes/FighterWhole004AC040F1005.cpp',
         'F1007-real-2FA':R/'probes/FighterWhole004AC040F1007.cpp'}
inc=(R/'probes/FighterThirdBossTrajectory2FAF1007.inc').read_text()
assert inc.count('case 0x2FA:')==1
assert inc.count('SpawnWithFloatAt453A70(0x38E,')==1
assert inc.count('g_F1007_RightBoundAt0065945C')==1
assert sources['F1007-real-2FA'].read_text().count('#include "FighterThirdBossTrajectory2FAF1007.inc"')==1
sp=importlib.util.spec_from_file_location('f1007rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;NATIVE=82796;NATIVE_X86=22721;AFTER=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE),BASE))
assert len(whole)==NATIVE_X86 and whole[2].op_str=='esp, 0x720'
post=rd.pe_bytes_at(PE,BASE+NATIVE,AFTER)
cases={'2C0':(0x4BC0A8,0x4BC29A,498,135,14),
       '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
       '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
       '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
       '2E5':(0x4BD017,0x4BD314,765,199,14),
       '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
       '2FA':(0x4BF16E,0x4BF40E,672,186,18)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
n=native['2FA']
assert n[9].op_str=='0x453e20'
assert n[18].op_str=='ecx, byte ptr [0x6714d0]'
assert n[24].op_str=='dword ptr [0x65782c]' and n[38].op_str=='dword ptr [0x65782c]'
assert n[42].op_str=='0xf' and n[44].op_str=='0x40fb40'
assert n[77].op_str=='dword ptr [0x657888]' and n[85].op_str=='0x453a70'
assert n[102].op_str=='0x455580'
assert n[103].op_str=='edx, byte ptr [0x6714d0]'
assert n[135].op_str=='dword ptr [0x65945c]'
assert n[145].op_str=='dword ptr [0x657888]'
assert n[-1].mnemonic=='jmp' and n[-1].op_str=='0x4c03a7' and n[-1].size==5
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(REG.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==AFTER
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 lab={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(post[off:off+4],'little')
  assert BASE<=va<BASE+NATIVE
  lab.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+j]==post[j] for j in range(AFTER) if j not in mask)
 assert all(a in lab and b in lab for a,b,_,_,_ in cases.values())
 row={'original_entire_callable_CODE_B':NATIVE,'native_whole_x86':NATIVE_X86,
  'compiled_partial_CODE_B':end,'compiled_partial_x86':len(I),
  'partial_frame':I[2].op_str,'original_afterRET_DIR32':151,
  'native_afterRET_nonfield_equal_B':522,'original_whole_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=lab[a],lab[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':sz,'native_x86':nx,
   'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,
                'wrong_native_GPR_roles':gg})
   if not mm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address;off=native[k][j].address-a+dt
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     if k not in ('2FA',):assert off==r['offset']-lo
     val=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+dt+4+val if r['type']=='REL32' else val
     regex=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(regex.group(1),16) if regex else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_PE_targets_verified']=nf
  row['cases'][k]=item
 results[label]=row
 print(label,'complete PARTIAL source',end,len(I),
 '2E6/2FA',[(k,row['cases'][k]['source_CODE_B'],row['cases'][k]['source_x86']) for k in ('2E6','2FA')],flush=True)
old=results['F1005-prior-2FA-marker'];new=results['F1007-real-2FA']
assert (old['compiled_partial_CODE_B'],old['compiled_partial_x86'])==(66877,18344)
assert (new['compiled_partial_CODE_B'],new['compiled_partial_x86'])==(67546,18528)
assert old['partial_frame']=='esp, 0x4d8' and new['partial_frame']=='esp, 0x4dc'
assert old['cases']['2FA']['source_CODE_B']==12
r=new['cases']['2FA']
assert (r['source_CODE_B'],r['source_x86'])==(669,186)
assert r['wrong_native_mnemonics']==[] and r['wrong_native_widths']==[185]
assert len(r['wrong_native_GPR_roles'])==113
assert r['native_PE_targets_verified']==18
prior=old['cases']['2E6'];current=new['cases']['2E6']
assert (prior['source_CODE_B'],prior['source_x86'])==(2055,590)
assert prior['wrong_native_widths']==[589]
assert prior['wrong_native_mnemonics']==prior['wrong_native_GPR_roles']==[]
assert (current['source_CODE_B'],current['source_x86'])==(2058,590)
assert current['wrong_native_mnemonics']==current['wrong_native_widths']==current['wrong_native_GPR_roles']==[]
assert current['native_PE_targets_verified']==47
for k in ('2C0','2C1','2C2','2C3','2E5'):
 r=new['cases'][k]
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPR_roles']==[]
 assert r['native_PE_targets_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x004AC040',
 'original_complete_GAME_CODE_B':NATIVE,'original_x86':NATIVE_X86,
 'native_2FA_B_x86':[672,186],'natural_2FA_source_B_x86':[669,186],
 'native_2FA_genuine_typed_PE_targets_checked':18,
 'native_2FA_wrong_mnemonics':0,
 'native_2FA_wrong_widths':[185],
 'native_2FA_wrong_GPR_roles':113,
 'previous_2E6_terminal_shared_JMP_native_width_repaired':True,
 'previous_2E6_all_590_native_mnem_width_GPR_roles_match':True,
 'whole_original_exact':False,'accepted_new_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_original_shaped_partial_parent_profiles':results
},indent=2)+'\n')
print('F1007 original 2FA 672B/186x86/18 PE; original 2E6 2058B/590x86 now ALL native mnem/width/GPR roles due later real game source. Giant NONEXACT.')
