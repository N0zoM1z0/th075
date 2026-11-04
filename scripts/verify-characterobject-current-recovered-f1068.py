#!/usr/bin/env python3
"""Live PE/native proof for every recovered state in ONE nonexact 81KB Boss.

Cold-compile only the current natural complete partial-switch C++ parent under
original pinned VC7.1. Independently read Japanese original full 81539B CODE,
567B afterRET, every real native case interval and physical original PE call
and global field. Reject inaccurate game instruction mnemonics, GPR roles,
missing physical calls, wrong float immediate and source jump-table aliases.
Never count case-local agreement as independent byte-exact original callable.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import hashlib,importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1068-boss-live-all-native';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1068reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
P=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
B=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x50a580)
assert (B['size'],B['instructions'],B['postret_size'],B['dense_entries'],B['sparse_bytes'])==(81539,17435,567,92,199)
raw=rd.pe_bytes_at(P,B['address'],B['size'])
assert hashlib.sha256(raw).hexdigest()==B['sha256']
NWHOLE=list(D.disasm(raw,B['address']))
assert len(NWHOLE)==17435 and NWHOLE[-1].address+NWHOLE[-1].size==B['address']+B['size']
assert NWHOLE[2].op_str=='esp, 0x3a0' and NWHOLE[3].op_str=='dword ptr [ebp - 0xac], ecx'
after=rd.pe_bytes_at(P,B['address']+B['size'],B['postret_size'])
assert hashlib.sha256(after).hexdigest()==B['postret_sha']
orig_dense=[int.from_bytes(after[4*i:4*i+4],'little') for i in range(92)]
orig_sparse=after[368:];assert len(orig_sparse)==199
assert hashlib.sha256(after[:368]).hexdigest()==B['tables'][0]['dense_sha']
assert hashlib.sha256(orig_sparse).hexdigest()==B['tables'][0]['map_sha']
# Every listed game case has genuine original behavior in the tracked C++.
# Counts prevent a missing original external call from becoming a false pass.
required_fields={
 0x320:6,0x321:19,0x322:4,0x323:24,0x324:27,0x325:7,
 0x328:37,0x329:35,0x32a:35,
 0x32b:3,0x32c:4,0x32d:3,0x32e:4,0x32f:3,
 0x330:16,0x331:9,0x332:3,0x333:14,0x334:14,0x335:12,0x336:14,
 0x337:3,0x338:12,0x339:10,0x33a:18,
 0x33b:33,0x33c:5,0x33d:33,0x33e:5,0x33f:33,
 0x340:5,0x341:33,0x342:5,0x343:33,0x344:5,0x345:3,
}
assert len(required_fields)==36 and sum(required_fields.values())==529
src=R/'probes/CharacterObjectWhole0050A580F1044.cpp'
source=src.read_text()
# Native state imports, not fake marker labels, must actually be represented.
for act in required_fields:
 assert not re.search(r'case\s+0x'+format(act,'X')+r'\s*:\s*g_FighterProbeMarker',source,re.I),hex(act)
for token in ('#include "CharacterObjectBoss330F1068.inc"',
 '#include "CharacterObjectBoss331F1069.inc"',
 '#include "CharacterObjectBoss323F1070.inc"',
 '#include "CharacterObjectBoss324F1071.inc"',
 '#include "CharacterObjectBoss328F1073.inc"',
 '#include "CharacterObjectBoss32932AF1074.inc"',
 '#include "CharacterObjectBoss335F1064.inc"',
 '#include "CharacterObjectBoss333334F1065.inc"',
 '#include "CharacterObjectBoss338F1062.inc"',
 '#include "CharacterObjectBoss339F1061.inc"'):
 assert token in source,token
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'all-recovered-current-full-parent.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=380)
(O/'all-recovered-current-full-parent.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert len(code)-end==567 and end<81539
T=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
assert len(T)==92 and all(r['type']=='DIR32' and r['offset']==end+4*j and r['addend']==0 and r['local_symbol_offset'] is not None for j,r in enumerate(T))
assert code[end+368:]==orig_sparse
assert all((orig_dense[i]==orig_dense[j])==(T[i]['local_symbol_offset']==T[j]['local_symbol_offset']) for i in range(92) for j in range(92))
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
known=[];rows=[]
for action,expected_count in required_fields.items():
 ix=orig_sparse[action-0x320]
 lo_orig,hi_orig=orig_dense[ix],orig_dense[ix+1]
 assert B['address']<=lo_orig<hi_orig<=B['address']+B['size']
 N=[x for x in NWHOLE if lo_orig<=x.address<hi_orig]
 assert N and N[0].address==lo_orig and N[-1].address+N[-1].size==hi_orig
 lo,hi=T[ix]['local_symbol_offset'],T[ix+1]['local_symbol_offset']
 assert 0<=lo<hi<=end
 S=[x for x in I if lo<=x.address<hi]
 assert len(N)==len(S),(hex(action),len(N),len(S))
 badm=[j for j,(a,b) in enumerate(zip(N,S)) if a.mnemonic!=b.mnemonic]
 badg=[j for j,(a,b) in enumerate(zip(N,S)) if roles(a)!=roles(b)]
 assert not badm and not badg,(hex(action),'mnemonic',badm[:15],'gpr',badg[:15])
 fields=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
 assert len(fields)==expected_count,(hex(action),len(fields),expected_count)
 pe=[]
 for r in fields:
  assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
  j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
  delta=r['offset']-S[j].address
  assert delta+4<=N[j].size,(hex(action),j,'COFF instruction kind mismatch')
  p=N[j].address+delta
  v=int.from_bytes(rd.pe_bytes_at(P,p,4),'little',signed=r['type']=='REL32')
  actual=p+4+v if r['type']=='REL32' else v
  m=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
  expected=int(m.group(1),16) if m else 0x6406ac if r['symbol']=='__ftol2' else None
  assert expected==actual,(hex(action),j,r['symbol'],hex(actual),hex(expected or 0))
  assert N[j].mnemonic=='call' if r['type']=='REL32' else ('0x'+format(actual,'x') in N[j].op_str)
  pe.append({'x86_ordinal':j,'original_PE_field':hex(p),'kind':r['type'],
             'original_native_PE_target':hex(actual),'source_symbol':r['symbol']})
 if action in (0x333,0x334,0x336):
  immediate={0x333:'0x41f00000',0x334:'0',0x336:'0xc1f00000'}[action]
  assert N[105].mnemonic==S[105].mnemonic=='push' and N[105].op_str==S[105].op_str==immediate
 if action==0x323:
  # Actual original +0xC8 native *raw-bit* angle is directly forwarded
  # in a DWORD MOV/PUSH rather than reloaded/stored through x87.
  for mov_at,push_at in ((34,35),(79,80)):
   assert N[mov_at].mnemonic==S[mov_at].mnemonic=='mov'
   assert '+ 0xc8' in N[mov_at].op_str and '+ 0xc8' in S[mov_at].op_str
   assert N[push_at].mnemonic==S[push_at].mnemonic=='push'
 if action==0x324:
  # Real stage-0 15.0f float bit-pattern, original +C8 MOV/PUSH and
  # native unordered-ground comparison TEST AH,41 ; JP skip transition.
  assert N[82].mnemonic==S[82].mnemonic=='push'
  assert N[82].op_str==S[82].op_str=='0x41700000'
  assert N[84].mnemonic==S[84].mnemonic=='mov'
  assert N[85].mnemonic==S[85].mnemonic=='push'
  assert N[174].mnemonic==S[174].mnemonic=='test'
  assert N[174].op_str==S[174].op_str=='ah, 0x41'
  assert N[175].mnemonic==S[175].mnemonic=='jp'
 if action in (0x328,0x329,0x32a):
  # Original 328 has raw angle DWORD+0xC8 passed without x87
  # conversion; original 329/32A start with genuinely distinct X speed.
  # All three original original-native handlers have EXACTLY 16
  # separate 0x33A projectile calls, not a generated counter loop.
  if action==0x328:
   assert N[105].mnemonic==S[105].mnemonic=='push'
   assert N[105].op_str==S[105].op_str=='0x41500000'
   assert N[107].mnemonic==S[107].mnemonic=='mov'
   assert '+ 0xc8' in N[107].op_str and '+ 0xc8' in S[107].op_str
   assert N[114].mnemonic==S[114].mnemonic=='mov'
   assert '+ 0x30' in N[114].op_str and '+ 0x30' in S[114].op_str
   spawn_ordinals=list(range(212,423,14))
   assert len(spawn_ordinals)==16
  else:
   speed='0x41a00000' if action==0x329 else '0x41200000'
   assert N[106].mnemonic==S[106].mnemonic=='mov'
   assert N[106].op_str==S[106].op_str and speed in N[106].op_str
   spawn_ordinals=list(range(190,401,14))
   assert len(spawn_ordinals)==16
  assert all(N[i].mnemonic==S[i].mnemonic=='call' for i in spawn_ordinals)
  assert all(any(field['x86_ordinal']==i and field['original_native_PE_target']=='0x453a70'
                 for field in pe) for i in spawn_ordinals)
  # Always spawned random 0x32B before the original status/landing
  # condition; two native 0x455580 calls compute its true X/Y.
  rng=(154,165) if action==0x328 else (140,151)
  assert all(any(field['x86_ordinal']==i and field['original_native_PE_target']=='0x455580'
                 for field in pe) for i in rng)
 if action==0x331:
  # Original actual 50.0f +0x2C initialization and the three separate
  # parent Y displacements are immediate/physical-value native evidence.
  assert N[140].mnemonic==S[140].mnemonic=='mov'
  assert N[140].op_str.split(', ')[-1]==S[140].op_str.split(', ')[-1]=='0x42480000'
  target_at={32:'0x659138',62:'0x658264',87:'0x657888'}
  for index,target in target_at.items():
   assert N[index].mnemonic==S[index].mnemonic=='fadd'
   assert target in N[index].op_str
 if action==0x330:
  # Floats and x87 unordered branch in the real original state.
  assert N[76].mnemonic==S[76].mnemonic=='push' and N[76].op_str==S[76].op_str=='0x42700000'
  assert [(x.mnemonic,x.op_str.split(',')[0]) for x in N[165:167]]==[('test','ah'),('jnp','0x50d492')]
  assert S[165].mnemonic=='test' and S[165].op_str=='ah, 0x41' and S[166].mnemonic=='jnp'
 known.append(lo_orig)
 rows.append({'action':hex(action),'original_native_PE_interval':[hex(lo_orig),hex(hi_orig)],
  'original_interior_CODE_B':hi_orig-lo_orig,'current_source_interior_CODE_B':hi-lo,
  'original_native_x86':len(N),'source_x86':len(S),
  'matching_mnemonics':len(N),'matching_GPR_roles':len(N),
  'matching_x86_widths':sum(a.size==b.size for a,b in zip(N,S)),
  'native_physically_correct_PE_call_global_fields':pe,
  'one_original_whole_function_exact':False})
 print(hex(action),'native',hi_orig-lo_orig,'B/',len(N),'x86; selected source',hi-lo,'B;',len(pe),'real PE fields',flush=True)
assert len(set(known))==len(required_fields)
original_total=sum(row['original_interior_CODE_B'] for row in rows)
x86total=sum(row['original_native_x86'] for row in rows)
src_total=sum(row['current_source_interior_CODE_B'] for row in rows)
fields_total=sum(len(row['native_physically_correct_PE_call_global_fields']) for row in rows)
assert (original_total,x86total,fields_total)==(30413,6634,529)
summary={'original_Boss':'0x0050A580','original_whole_CODE_B':81539,
 'original_whole_x86':17435,'selected_partial_source_CODE_B':end,'selected_partial_source_x86':len(I),
 'source_partial_afterRET_DATA_B':567,'original_recovered_independent_case_interior_count':len(rows),
 'total_recovered_native_original_state_CODE_B':original_total,
 'total_recovered_native_original_x86':x86total,
 'total_native_mnemonics_and_GPR_roles_matching':x86total,
 'total_original_PE_nonlocal_fields_physically_verified':fields_total,
 'total_generated_inner_case_source_CODE_B':src_total,
 'original_92_DIR32_native_jump_partitions_equal':True,'original_199_sparse_bytes_equal':True,
 'original_81KB_whole_function_exact':False,'new_exact_original_whole_CODE_B':0,
 'all_979_cold_replay':False,'native_states':rows}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1074 LIVE 36 original game action interiors: original',original_total,'CODE B /',x86total,'x86, native mnemonic+GPR',x86total,'/',x86total,'and genuine PE nonlocal',fields_total,'/',fields_total,'. Current partial source',end,'B /',len(I),'x86, NOT exact whole 81KB; accepted new original bytes 0.')
