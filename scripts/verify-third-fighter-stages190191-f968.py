#!/usr/bin/env python3
"""F968: original fighter 190/191, 294 genuine x86 mnemonics in full father.

Cold-compile tracked F966 old markers vs F968 real action190/191 under
normal pinned VC7.1 full original-shaped PARTIAL 82KB parent. Original
190 and 191 each 597B/147x86/11 typed real PE external fields;
natural C++ generates 561B/147 due original 12 wide EBP x87 scratch
instr per case, preserving all 147 original ordered mnemonics.
True original afterRET 151 DIR32+522 nonfield DATA checked; whole
82KB game remains NONEXACT and internal cases never credited.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f968-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F966-prior-markers':R/'probes/FighterWhole004AC040F966.cpp',
         'F968-real-190191':R/'probes/FighterWhole004AC040F968.cpp'}
inc=(R/'probes/FighterThirdBossStages190191F968.inc').read_text()
assert inc.count('case 0x190:')==inc.count('case 0x191:')==1
assert sources['F968-real-190191'].read_text().count('#include "FighterThirdBossStages190191F968.inc"')==1
sp=importlib.util.spec_from_file_location('f968reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLE_X86=22721;DATA=1126
NW=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(NW)==WHOLE_X86 and NW[2].op_str=='esp, 0x720'
data=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
physical={'189':(0x4B2091,0x4B2167,214,61,6),
          '190':(0x4B2167,0x4B23BC,597,147,11),
          '191':(0x4B23BC,0x4B2611,597,147,11)}
native={}
for k,(a,b,sz,nx,nf) in physical.items():
 seq=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(seq)==nx and b-a==sz
 native[k]=seq
for name in ('190','191'):
 n=native[name]
 assert n[37].mnemonic=='mov' and n[38].mnemonic=='fild'
 assert n[55].mnemonic=='mov' and n[56].mnemonic=='fild'
 assert n[115].mnemonic=='mov' and n[116].mnemonic=='fild'
 assert all(n[j].size==6 for j in [37,38,55,56,67,68,85,86,97,98,115,116])
 assert n[61].op_str==n[91].op_str==n[121].op_str=='0x320'
 assert n[63].op_str==n[93].op_str==n[123].op_str=='0x453a70'
 assert n[28].op_str=='0'
assert native['190'][18].op_str=='edx, 5'
assert native['191'][18].op_str=='ecx, 4'
assert native['190'][54].op_str.endswith(', 0x31')
assert native['191'][54].op_str.endswith(', 0x61')
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for name,cpp in sources.items():
 obj=O/(name+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=env,capture_output=True,text=True,timeout=345)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 instructions=[]
 for x in D.disasm(code,0):
  instructions.append(x)
  if x.mnemonic=='ret':break
 end=instructions[-1].address+instructions[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 mp={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  addr=int.from_bytes(data[off:off+4],'little')
  assert BASE<=addr<BASE+WHOLE
  mp.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==data[i] for i in range(DATA) if i not in mask)
 assert all(p in mp for p in (0x4B2091,0x4B2167,0x4B23BC,0x4B2611))
 row={'native_complete_game_CODE_B':WHOLE,'native_complete_game_x86':WHOLE_X86,
      'partial_generated_CODE_B':end,'partial_source_x86':len(instructions),
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'source_total_COFF_fields':len(refs),'whole_native_game_exact':False,
      'original_handlers':{}}
 for case,(a,b,sz,nx,nf) in physical.items():
  lo,hi=mp[a],mp[b]
  src=[x for x in instructions if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  record={'native_original_B':sz,'native_x86':nx,
          'source_B':hi-lo,'source_x86':len(src)}
  if len(src)==nx:
   mm=[i for i,(x,y) in enumerate(zip(native[case],src)) if x.mnemonic!=y.mnemonic]
   ww=[i for i,(x,y) in enumerate(zip(native[case],src)) if x.size!=y.size]
   gg=[i for i,(x,y) in enumerate(zip(native[case],src)) if roles(x)!=roles(y)]
   record.update({'wrong_native_mnemonic_ordinals':mm,
                  'wrong_native_width_ordinals':ww,'wrong_native_GPR_role_ordinals':gg})
   if not mm:
    assert len(fields)==nf,(name,case,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(src) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-src[j].address
     origoff=native[case][j].address-a+d
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[origoff:origoff+4],'little',signed=r['type']=='REL32')
     target=native[case][j].address+d+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(name,case,j,r['symbol'],hex(target),expected)
    record['native_original_PE_targets_verified']=len(fields)
  row['original_handlers'][case]=record
 rows[name]=row
 print(name,'complete partial father',end,len(instructions),
  '190/191 sourceB',[row['original_handlers'][c]['source_B'] for c in ('190','191')],flush=True)
old=rows['F966-prior-markers'];new=rows['F968-real-190191']
assert (old['partial_generated_CODE_B'],old['partial_source_x86'])==(25798,7113)
assert (new['partial_generated_CODE_B'],new['partial_source_x86'])==(26893,7403)
for case in ('190','191'):
 assert old['original_handlers'][case]['source_B']==15
 r=new['original_handlers'][case]
 assert (r['source_B'],r['source_x86'])==(561,147)
 assert r['wrong_native_mnemonic_ordinals']==[]
 assert r['wrong_native_width_ordinals']==[37,38,55,56,67,68,85,86,97,98,115,116]
 assert len(r['wrong_native_GPR_role_ordinals'])==94
 assert r['native_original_PE_targets_verified']==11
assert new['original_handlers']['189']['native_original_PE_targets_verified']==6
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x004AC040',
 'native_full_callable_CODE_B':WHOLE,'native_full_x86':WHOLE_X86,
 'original_190_191_CODE_B_x86':[597*2,147*2],
 'compiled_source_190_191_B_x86':[561*2,147*2],
 'native_original_external_PE_targets_checked':22,
 'original_12_wide_EBP_float_temp_instructions_per_case':True,
 'generated_12_short_EBP_temp_instructions_per_case':True,
 'wrong_native_GPR_roles_each':[94,94],
 'all_294_original_native_mnemonics_match':True,
 'whole_original_exact':False,'new_accepted_game_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_original_shaped_Cpp_profiles':rows
},indent=2)+'\n')
print('F968 native 190/191: source 1122B/294x86 versus original 1194B/294; all original mnemonics and 22 actual typed PE targets verified. 24 genuine EBP temp widths and 94/94 GPR roles wrong; whole 82KB fighter NONEXACT.')
