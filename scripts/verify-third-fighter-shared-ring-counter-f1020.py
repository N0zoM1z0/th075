#!/usr/bin/env python3
"""F1020: ORIGINAL whole 82796B/22721 x86, native 0x720 frame, saved this.

Fresh VC7.1 compile TWO tracked ENTIRE original-shaped 82KB
PARTIAL fighter sources, prior F1019 with two separate genuine
2DB ring counters vs F1020 with a shared genuine stage11
int counter. Independently read SHA-pinned Japanese original
PE, compare *every* whole x86 mnemonic, width, GPR operand
role, native saved receiver/stack, two real ring-loop local
owners, all 151 physical afterRET DIR32 labels/522 DATA
nonfields and 2DB/2EF/2F0 real PE target fields. Do not
claim complete original byte equality: 12 true width defects,
6958 original GPR-role differences, COFF and game code still
nonexact despite exact original CODE B and x86 count.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1020-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1019-two-separate-native-ring-counters':R/'probes/FighterWhole004AC040F1019.cpp',
         'F1020-genuine-shared-ring-counter':R/'probes/FighterWhole004AC040F1020.cpp'}
oldinc=(R/'probes/FighterThirdBossRing2DBF1016.inc').read_text()
newinc=(R/'probes/FighterThirdBossRingSharedCounter2DBF1020.inc').read_text()
assert oldinc.count('for (int shot=0;shot<360;shot+=10)')==2
assert newinc.count('int shot;')==1
assert newinc.count('for (shot=0;shot<360;shot+=10)')==2
assert newinc.count('for (int shot=0;shot<360;shot+=10)')==0
assert newinc.count('SpawnFloatXYAt453A70(0x385,')==2
assert newinc.count('g_F1016_RingYAt00659460')==2
assert sources['F1020-genuine-shared-ring-counter'].read_text().count('#include "FighterThirdBossRingSharedCounter2DBF1020.inc"')==1
sp=importlib.util.spec_from_file_location('f1020reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
rawwhole=rd.pe_bytes_at(PE,BASE,WHOLE)
native=list(D.disasm(rawwhole,BASE))
assert len(native)==NX and native[2].op_str=='esp, 0x720'
assert native[4].op_str=='dword ptr [ebp - 0x64], ecx'
assert native[19050].op_str=='dword ptr [ebp - 0x40], 0'
assert native[19084].op_str=='dword ptr [ebp - 0x40], 0'
assert native[2829].op_str=='dword ptr [ebp - 0x80], eax'
assert native[2830].op_str=='dword ptr [ebp - 0x80]'
post=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={
 '2BE':(0x4BB1EA,0x4BB831,1607,471,50),
 '2BF':(0x4BB831,0x4BC0A8,2167,616,65),
 '2DB':(0x4BC8B1,0x4BD017,1894,548,38),
 '2EF':(0x4BDB1E,0x4BE3D3,2229,573,80),
 '2F0':(0x4BE3D3,0x4BEC88,2229,573,80),
 '2F9':(0x4BEC88,0x4BF16E,1254,326,33),
 '303':(0x4BFDAB,0x4C01A1,1014,267,29)}
subnative={}
for key,(a,b,size,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(n)==nx and n[-1].address+n[-1].size==b
 subnative[key]=n
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(REG.findall(x.op_str))
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
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1050:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(I)==NX and len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(post[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==post[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 mm=[j for j,(n,s) in enumerate(zip(native,I)) if n.mnemonic!=s.mnemonic]
 ww=[j for j,(n,s) in enumerate(zip(native,I)) if n.size!=s.size]
 gg=[j for j,(n,s) in enumerate(zip(native,I)) if roles(n)!=roles(s)]
 row={'native_whole_GAME_CODE_B':WHOLE,'native_whole_x86':NX,
   'whole_partial_source_CODE_B':end,'whole_partial_x86':len(I),
   'source_frame':I[2].op_str,'source_saved_this':I[4].op_str,
   'source_first_ring_counter':I[19050].op_str,
   'source_second_ring_counter':I[19084].op_str,
   'source_x87_scratch_mov':I[2829].op_str,
   'source_x87_scratch_fild':I[2830].op_str,
   'wrong_original_whole_mnemonic_ordinals':mm,
   'wrong_original_whole_width_ordinals':ww,
   'wrong_original_GPR_role_count':len(gg),
   'signed_width_delta_bytes':sum(I[j].size-native[j].size for j in ww),
   'native_afterRET_DIR32':151,'native_nonfield_afterRET_B_equal':522,
   'whole_original_exact':False,'native_cases':{}}
 for key,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  seq=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_CASE_CODE_B':sz,'original_x86':nx,
    'source_CASE_CODE_B':hi-lo,'source_x86':len(seq)}
  if len(seq)==nx:
   m=[j for j,(n,s) in enumerate(zip(subnative[key],seq)) if n.mnemonic!=s.mnemonic]
   w=[j for j,(n,s) in enumerate(zip(subnative[key],seq)) if n.size!=s.size]
   g=[j for j,(n,s) in enumerate(zip(subnative[key],seq)) if roles(n)!=roles(s)]
   item.update({'wrong_original_mnemonic_ordinals':m,
                'wrong_original_width_ordinals':w,'wrong_original_GPR_ordinals':g})
   if not m:
    assert len(fields)==nf,(label,key,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-seq[j].address
     off=subnative[key][j].address-a+delta
     if not w:assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=subnative[key][j].address+delta+4+val if r['type']=='REL32' else val
     match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(match.group(1),16) if match else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,key,j,r['symbol'],hex(target),expected)
    item['real_original_PE_targets_verified']=nf
  row['native_cases'][key]=item
 rows[label]=row
 print(label,'WHOLE CODE/x86',end,len(I),'frame',I[2].op_str,
  'saved this',I[4].op_str,'width defects',len(ww),
  'GPR mismatches',len(gg),flush=True)
old=rows['F1019-two-separate-native-ring-counters']
new=rows['F1020-genuine-shared-ring-counter']
assert (old['whole_partial_source_CODE_B'],old['whole_partial_x86'])==(82802,NX)
assert (new['whole_partial_source_CODE_B'],new['whole_partial_x86'])==(WHOLE,NX)
assert old['source_frame']=='esp, 0x724' and new['source_frame']=='esp, 0x720'
assert old['source_saved_this']=='dword ptr [ebp - 0x68], ecx'
assert new['source_saved_this']==native[4].op_str
assert old['source_first_ring_counter']=='dword ptr [ebp - 0x40], 0'
assert old['source_second_ring_counter']=='dword ptr [ebp - 0x44], 0'
assert new['source_first_ring_counter']==new['source_second_ring_counter']=='dword ptr [ebp - 0x40], 0'
assert old['source_x87_scratch_mov']=='dword ptr [ebp - 0x84], eax'
assert old['source_x87_scratch_fild']=='dword ptr [ebp - 0x84]'
assert new['source_x87_scratch_mov']==native[2829].op_str
assert new['source_x87_scratch_fild']==native[2830].op_str
assert old['wrong_original_whole_mnemonic_ordinals']==new['wrong_original_whole_mnemonic_ordinals']==[]
assert old['wrong_original_whole_width_ordinals']==[2829,2830,2900,2923,10952,11291,11959,12305,12953,13025,13595,13657,13688,16908]
assert new['wrong_original_whole_width_ordinals']==[2900,2923,10952,11291,11959,12305,12953,13025,13595,13657,13688,16908]
assert old['signed_width_delta_bytes']==6 and new['signed_width_delta_bytes']==0
assert old['wrong_original_GPR_role_count']==new['wrong_original_GPR_role_count']==6958
for k in cases:
 r=new['native_cases'][k]
 assert (r['source_CASE_CODE_B'],r['source_x86'])==cases[k][2:4]
 assert r['wrong_original_mnemonic_ordinals']==r['wrong_original_width_ordinals']==[]
 assert len(r['wrong_original_GPR_ordinals'])==(125 if k=='2BE' else 0)
 assert r['real_original_PE_targets_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x004AC040',
 'native_whole_GAME_CODE_B':WHOLE,'native_whole_x86':NX,
 'source_entire_partial_CODE_B_x86':[WHOLE,NX],
 'native_and_source_complete_CODE_B_and_x86_counts_equal':True,
 'original_whole_mnemonic_errors':0,'original_whole_width_errors':12,
 'original_whole_GPR_role_errors':6958,
 'real_2DB_two_loops_share_native_EBP_minus_40':True,
 'source_compiler_stack_frame_restored_to_native':'0x720',
 'source_saved_this_restored_to_native':'EBP-0x64',
 'native_original_2EF_2F0_2DB_real_PE_fields_still_verified':True,
 'whole_original_exact':False,'newly_credited_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_original_shaped_partial_parent_profiles':rows
},indent=2)+'\n')
print('F1020 NATIVE 82KB entire CODE B/22,721 x86 length+mnemonics, 0x720 frame, saved this EBP-0x64 restored by shared REAL 2DB shot counter. Twelve genuine widths, 6958 GPR wrong. Whole GAME still NONEXACT.')
