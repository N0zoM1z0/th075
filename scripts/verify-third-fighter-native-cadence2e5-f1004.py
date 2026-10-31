#!/usr/bin/env python3
"""F1004 real original fighter 2E5 199 x86, all GPR and 14 PE targets.

Fresh serial normal VC7.1 compile two TRACKED ENTIRE 82KB
original-shaped PARTIAL fighter fathers: F1003 with old 2E5
marker and F1004 with real signed-mode 2E5 gameplay C++.
Independently check original Japanese pinned PE, all 765B/
199 positional opcode mnemonics, widths, GPR roles, 14
typed zero-addend physical PE targets, preceding authentic
2C0..2C3 source cases, all original afterRET 151 DIR32 local
labels and 522 nonfield DATA B. Whole giant remains NONEXACT.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1004-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1003-prior-2E5-marker':R/'probes/FighterWhole004AC040F1003.cpp',
         'F1004-real-2E5':R/'probes/FighterWhole004AC040F1004.cpp'}
inc=(R/'probes/FighterThirdBossCadence2E5F1004.inc').read_text()
assert inc.count('case 0x2E5:')==1 and inc.count('SpawnFloatXYAt453A70(0x387,')==2
assert inc.count('g_F1004_ModeAt006714D0')==3
assert sources['F1004-real-2E5'].read_text().count('#include "FighterThirdBossCadence2E5F1004.inc"')==1
sp=importlib.util.spec_from_file_location('f1004rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;NATIVE_CODE=82796;NATIVE_X86=22721;AFTER=1126
origwhole=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE_CODE),BASE))
assert len(origwhole)==NATIVE_X86 and origwhole[2].op_str=='esp, 0x720'
post=rd.pe_bytes_at(PE,BASE+NATIVE_CODE,AFTER)
cases={'2C0':(0x4BC0A8,0x4BC29A,498,135,14),
       '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
       '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
       '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
       '2E5':(0x4BD017,0x4BD314,765,199,14)}
native={}
for k,(a,b,sz,nx,fields) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(n)==nx and n[-1].address+n[-1].size==b and b-a==sz
 native[k]=n
n=native['2E5']
assert n[9].op_str=='0x453e20'
assert n[18].op_str=='ecx, byte ptr [0x6714d0]'
assert n[41].op_str=='edx, byte ptr [0x6714d0]'
assert n[59].op_str=='dword ptr [0x65836c]' and n[88].op_str=='dword ptr [0x65836c]'
assert n[71].op_str=='0x387' and n[100].op_str=='0x387'
assert n[73].op_str=='0x453a70' and n[102].op_str=='0x453a70'
assert n[136].op_str=='0x455580'
assert n[137].op_str=='ecx, byte ptr [0x6714d0]'
assert n[141].op_str.endswith('+ 0x516], ax')
assert n[160].op_str=='5' and n[162].op_str=='0x453d40'
assert n[-1].op_str=='0x4c03a7'
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(REG.findall(i.op_str))
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
 end=I[-1].address+I[-1].size
 assert len(code)-end==AFTER
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(q not in mask for q in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(post[off:off+4],'little')
  assert BASE<=va<BASE+NATIVE_CODE
  labels.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+j]==post[j] for j in range(AFTER) if j not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_whole_GAME_CODE_B':NATIVE_CODE,'original_whole_x86':NATIVE_X86,
      'whole_partial_cpp_CODE_B':end,'whole_partial_cpp_x86':len(I),
      'compiler_partial_frame':I[2].op_str,
      'native_afterRET_DIR32':151,'native_nonfield_DATA_equal_B':522,
      'whole_original_exact':False,'states':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':sz,'native_original_x86':nx,'source_CODE_B':hi-lo,'source_x86':len(s)}
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
     delta=r['offset']-s[j].address
     origoff=native[k][j].address-a+delta
     if not ww:assert origoff==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[origoff:origoff+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+delta+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['genuine_original_PE_targets_verified']=nf
  row['states'][k]=item
 rows[label]=row
 print(label,'complete PARTIAL father',end,len(I),'frame',I[2].op_str,
       '2E5 source',row['states']['2E5']['source_CODE_B'],row['states']['2E5']['source_x86'],flush=True)
old=rows['F1003-prior-2E5-marker'];new=rows['F1004-real-2E5']
assert (old['whole_partial_cpp_CODE_B'],old['whole_partial_cpp_x86'])==(64060,17559)
assert (new['whole_partial_cpp_CODE_B'],new['whole_partial_cpp_x86'])==(64810,17756)
assert old['compiler_partial_frame']=='esp, 0x46c' and new['compiler_partial_frame']=='esp, 0x47c'
assert old['states']['2E5']['source_CODE_B']==15
r=new['states']['2E5']
assert (r['source_CODE_B'],r['source_x86'])==(765,199)
assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPR_roles']==[]
assert r['genuine_original_PE_targets_verified']==14
for k in ('2C0','2C1','2C2','2C3'):
 r=new['states'][k]
 assert (r['source_CODE_B'],r['source_x86'])==cases[k][2:4]
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_native_GPR_roles']==[]
 assert r['genuine_original_PE_targets_verified']==14
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_native_fighter':'0x004AC040',
 'native_entire_GAME_callable_CODE_B':NATIVE_CODE,'original_whole_x86':NATIVE_X86,
 'native_real_2E5_CODE_B_x86':[765,199],
 'native_all_199_mnemonic_width_GPR_roles_match':True,
 'native_2E5_typed_PE_external_targets':14,
 'previous_four_2C0_2C3_GPR_phase_and_PE_preserved':True,
 'native_saved_this_EBP_and_full_stack_still_wrong':True,
 'entire_original_exact':False,'new_credited_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_original_shaped_partial_source_profiles':rows
},indent=2)+'\n')
print('F1004 real original2E5 765B/199x86, ALL mnemonic/width/GPR roles +14 PE targets; prior 555 GPR roles remain native. Whole 82KB original NONEXACT.')
