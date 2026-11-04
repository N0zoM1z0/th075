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
from bisect import bisect_right
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
 0x346:34,0x347:10,0x348:9,0x349:7,0x34a:7,0x34b:6,0x34c:18,0x34d:18,0x34e:18,0x34f:18,0x350:18,0x351:15,0x352:6,0x353:3,0x354:14,0x355:20,0x356:14,0x357:7,0x35f:2,0x360:15,0x361:15,0x362:15,0x363:15,0x364:15,0x365:32,0x366:32,0x367:32,0x368:32,0x369:32,0x384:24,0x385:10,0x386:22,0x387:17,0x388:14,0x389:24,0x38a:18,0x38b:16,0x38c:4,0x38e:8,0x38f:3,0x390:24,0x392:4,0x393:9,0x3e3:17,0x3e4:19,0x3e5:5,
}
assert len(required_fields)==82 and sum(required_fields.values())==1246
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
 '#include "CharacterObjectBoss346F1076.inc"',
 '#include "CharacterObjectBoss347F1075.inc"',
 '#include "CharacterObjectBoss348F1080.inc"',
 '#include "CharacterObjectBoss349F1081.inc"',
 '#include "CharacterObjectBoss34AF1082.inc"',
 '#include "CharacterObjectBoss34BF1083.inc"',
 '#include "CharacterObjectBoss34CF1085.inc"',
 '#include "CharacterObjectBoss34DF1086.inc"',
 '#include "CharacterObjectBoss34EF1087.inc"',
 '#include "CharacterObjectBoss34FF1088.inc"',
 '#include "CharacterObjectBoss350F1089.inc"',
 '#include "CharacterObjectBoss351F1090.inc"',
 '#include "CharacterObjectBoss352F1091.inc"',
 '#include "CharacterObjectBoss353F1092.inc"',
 '#include "CharacterObjectBoss354F1093.inc"',
 '#include "CharacterObjectBoss355F1095.inc"',
 '#include "CharacterObjectBoss356F1097.inc"',
 '#include "CharacterObjectBoss357F1098.inc"',
 '#include "CharacterObjectBoss35FF1105.inc"',
 '#include "CharacterObjectBoss360361F1108.inc"',
 '#include "CharacterObjectBoss365F1110.inc"',
 '#include "CharacterObjectBoss366369F1111.inc"',
 '#include "CharacterObjectBoss384F1113.inc"',
 '#include "CharacterObjectBoss385F1114.inc"',
 '#include "CharacterObjectBoss386F1115.inc"',
 '#include "CharacterObjectBoss387F1116.inc"',
 '#include "CharacterObjectBoss388F1117.inc"',
 '#include "CharacterObjectBoss389F1118.inc"',
 '#include "CharacterObjectBoss38AF1119.inc"',
 '#include "CharacterObjectBoss38BF1120.inc"',
 '#include "CharacterObjectBoss38CF1121.inc"',
 '#include "CharacterObjectBoss38EF1122.inc"',
 '#include "CharacterObjectBoss38FF1123.inc"',
 '#include "CharacterObjectBoss390F1125.inc"',
 '#include "CharacterObjectBoss392F1127.inc"',
 '#include "CharacterObjectBoss393F1128.inc"',
 '#include "CharacterObjectBoss3E3F1131.inc"',
 '#include "CharacterObjectBoss3E4F1132.inc"',
 '#include "CharacterObjectBoss3E5F1130.inc"',
 '#include "CharacterObjectBoss3E6F1129.inc"',
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
assert len(code)-end==567 and end>0  # One NORMAL partial C++ parent; may exceed original CODE before exactness.
T=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
assert len(T)==92 and all(r['type']=='DIR32' and r['offset']==end+4*j and r['addend']==0 and r['local_symbol_offset'] is not None for j,r in enumerate(T))
assert code[end+368:]==orig_sparse
# F1140: Physical original PE control flow is not proven by identical
# x86 mnemonic/GPR/width sequences. Compare each actual direct jump
# destination to the corresponding GLOBAL x86 ordinal in the entire
# original callable. The candidate and original must have the same
# complete 17,435 instruction count, not a conveniently cropped case.
assert len(I)==len(NWHOLE)==17435
assert [n.mnemonic for n in I]==[n.mnemonic for n in NWHOLE]
native_instruction_by_address={n.address:k for k,n in enumerate(NWHOLE)}
source_instruction_by_address={n.address:k for k,n in enumerate(I)}
physical_original_branch_positions=0
native_branch_target_debt=[]
for k,(native,emitted) in enumerate(zip(NWHOLE,I)):
 if not native.mnemonic.startswith('j'):
  continue
 if not (re.fullmatch(r'0x[0-9a-f]+',native.op_str) and
         re.fullmatch(r'0x[0-9a-f]+',emitted.op_str)):
  continue
 orig_target=native_instruction_by_address.get(int(native.op_str,16))
 src_target=source_instruction_by_address.get(int(emitted.op_str,16))
 assert orig_target is not None and src_target is not None,(k,native.op_str,emitted.op_str)
 physical_original_branch_positions+=1
 if orig_target!=src_target:
  slot=bisect_right(orig_dense,native.address)-1
  assert 0<=slot<=91
  case_ordinal=k-native_instruction_by_address[orig_dense[slot]]
  native_branch_target_debt.append({'jump_global_ordinal':k,
      'physical_switch_slot':slot,'case_ordinal':case_ordinal,
      'original_target_global_ordinal':orig_target,
      'source_target_global_ordinal':src_target})
assert physical_original_branch_positions==1834,physical_original_branch_positions
# These are not waived as exact or correctness: all 14 remain true
# unresolved source CFG target differences. Explicitly enumerate
# them to reject any *additional* source control-flow regression.
remaining_native_branch_keys={(0x346,271),
 (0x35d,13),(0x35d,17),(0x35e,155),(0x389,101),
 (0x391,124),(0x391,130),(0x3e3,43),(0x3e3,163),
 (0x3e4,43),(0x3e4,179),(0x3e4,204),(0x3e4,214),(0x3e4,232)}
actual_debt_keys={(row['physical_switch_slot'],row['case_ordinal'])
                  for row in native_branch_target_debt}
expected_debt_keys={(orig_sparse[action-0x320],ordinal)
                    for action,ordinal in remaining_native_branch_keys}
assert actual_debt_keys==expected_debt_keys,(
   'original PE control-flow target debt changed',actual_debt_keys^expected_debt_keys)
# Genuine recovered branch targets in original 0x387 must now bypass
# only the initialization, not its later every-frame gravity/angle.
original_387_index=native_instruction_by_address[orig_dense[orig_sparse[0x387-0x320]]]
for local in (38,42):
 n=NWHOLE[original_387_index+local];q=I[original_387_index+local]
 assert n.mnemonic==q.mnemonic=='jne'
 assert native_instruction_by_address[int(n.op_str,16)]-original_387_index==92
 assert source_instruction_by_address[int(q.op_str,16)]-original_387_index==92
# F1142: Original 330 has the SAME true native OR policy:
# its FPU JNP lands at impact body ordinal 173, while status==0/6
# jump past the body to ordinal 183. Prior C++ used the wrong AND.
original_330_index=native_instruction_by_address[orig_dense[orig_sparse[0x330-0x320]]]
for ord,expected in ((166,173),(169,183),(172,183)):
 n=NWHOLE[original_330_index+ord];q=I[original_330_index+ord]
 assert n.mnemonic==q.mnemonic and n.mnemonic in ('jnp','je')
 assert native_instruction_by_address[int(n.op_str,16)]-original_330_index==expected
 assert source_instruction_by_address[int(q.op_str,16)]-original_330_index==expected
# F1141: original 388 signed stage-2 landing FPU JNP must ENTER the
# body at ordinal 124, while status 0 or 6 skip to ordinal 134.
original_388_index=native_instruction_by_address[orig_dense[orig_sparse[0x388-0x320]]]
for ord,expected in ((117,124),(120,134),(123,134)):
 n=NWHOLE[original_388_index+ord];q=I[original_388_index+ord]
 assert n.mnemonic==q.mnemonic and n.mnemonic in ('jnp','je')
 assert native_instruction_by_address[int(n.op_str,16)]-original_388_index==expected
 assert source_instruction_by_address[int(q.op_str,16)]-original_388_index==expected
print('F1140 WHOLE native control-flow audit:',physical_original_branch_positions,
      'real direct PE-local jumps, original 0x387 stage/velocity guards corrected;',
      len(native_branch_target_debt),'other native branch target debts remain',flush=True)
assert all((orig_dense[i]==orig_dense[j])==(T[i]['local_symbol_offset']==T[j]['local_symbol_offset']) for i in range(92) for j in range(92))
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
# The original default case is not inert. It ACTUALLY calls the native
# 0040FA30 action getter and shares the original post-switch epilogue.
# Previous source used a synthetic g_FighterProbeMarker=0 instead and
# omitted one genuine x86 instruction. Validate the whole native
# physical common-tail and REL32 call, not just sparse-table labels.
orig_default=[n for n in NWHOLE if n.address>=orig_dense[91]]
src_default=[n for n in I if n.address>=T[91]['local_symbol_offset']]
assert [n.mnemonic for n in orig_default]==['mov','call','mov','pop','ret']
assert [n.mnemonic for n in src_default]==[n.mnemonic for n in orig_default]
assert [roles(n) for n in orig_default]==[roles(n) for n in src_default]
assert orig_default[1].address==orig_default[0].address+orig_default[0].size
orig_rel=orig_default[1].address+1
orig_disp=int.from_bytes(rd.pe_bytes_at(P,orig_rel,4),'little',signed=True)
assert orig_rel+4+orig_disp==0x40fa30
src_tail_pe=[r for r in refs if T[91]['local_symbol_offset']<=r['offset']<end and r['local_symbol_offset'] is None]
assert len(src_tail_pe)==1
assert src_tail_pe[0]['type']=='REL32' and src_tail_pe[0]['addend']==0
assert src_tail_pe[0]['offset']==src_default[1].address+1
assert 'GetNativeActionAt0040FA30' in src_tail_pe[0]['symbol']
assert not re.search(r'default\s*:\s*g_FighterProbeMarker',source)
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
 # Compare non-relocation native literal *values* in every real case.
 # Correct mnemonic/GPR/PE targets alone previously allowed a mistaken
 # +30.0f in the actual 0x334 source (original 0.0f).
 # Exclude branch displacements and the PE field ordinals already audited.
 scalar=re.compile(r'(?:,\s*|^)(0x[0-9a-f]+|-?\d+)$')
 field_ordinals={f['x86_ordinal'] for f in pe}
 original_scalar_imm_count=0
 for k,(n,emitted) in enumerate(zip(N,S)):
  if k in field_ordinals or n.mnemonic=='call' or n.mnemonic.startswith('j'):
   continue
  ni=scalar.search(n.op_str)
  si=scalar.search(emitted.op_str)
  if ni or si:
   assert ni is not None and si is not None and ni.group(1)==si.group(1),(
      hex(action),k,n.mnemonic,n.op_str,emitted.mnemonic,emitted.op_str)
   original_scalar_imm_count+=1
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
  # Native actor type for the FIRST unrolled projectile is 0x339,
  # followed by exactly fifteen 0x33A calls. Older source incorrectly
  # used 0x33A all sixteen times while matching 100% x86 mnemonic/GPR
  # and all physical PE relocation fields.
  spawn_ids=[209+14*k for k in range(16)] if action==0x328 else [187+14*k for k in range(16)]
  expected_ids=['0x339']+['0x33a']*15
  assert [N[i].mnemonic for i in spawn_ids]==['push']*16
  assert [S[i].mnemonic for i in spawn_ids]==['push']*16
  assert [N[i].op_str for i in spawn_ids]==expected_ids
  assert [S[i].op_str for i in spawn_ids]==expected_ids,(hex(action),'original projectile IDs regressed')
  assert all(N[i].mnemonic==S[i].mnemonic=='call' for i in spawn_ordinals)
  assert all(any(field['x86_ordinal']==i and field['original_native_PE_target']=='0x453a70'
                 for field in pe) for i in spawn_ordinals)
  # Earlier source had all sixteen correct physical CALL sites, but used
  # the WRONG initial action ID. Pinned PE requires 0x339 first,
  # followed by precisely fifteen 0x33A literal IDs, in EVERY state.
  assert all(N[i-3].mnemonic==S[i-3].mnemonic=='push' and
             N[i-3].op_str==S[i-3].op_str==('0x339' if j==0 else '0x33a')
             for j,i in enumerate(spawn_ordinals))
  # Always spawned random 0x32B before the original status/landing
  # condition; two native 0x455580 calls compute its true X/Y.
  rng=(154,165) if action==0x328 else (140,151)
  assert all(any(field['x86_ordinal']==i and field['original_native_PE_target']=='0x455580'
                 for field in pe) for i in rng)
 if action==0x346:
  # Original raw native +0xC8 angle DWORD is passed twice using MOV/PUSH,
  # then original x87 FILD/FADD and native CRT float-to-long route are
  # reproduced as genuine source gameplay, never patched instructions.
  for mov,push in ((105,106),(136,137)):
   assert N[mov].mnemonic==S[mov].mnemonic=='mov'
   assert '+ 0xc8' in N[mov].op_str and '+ 0xc8' in S[mov].op_str
   assert N[push].mnemonic==S[push].mnemonic=='push'
  assert N[351].mnemonic==S[351].mnemonic=='call'
  assert any(f['x86_ordinal']==351 and f['original_native_PE_target']=='0x6406ac' for f in pe)
  assert N[343].mnemonic==S[343].mnemonic=='fadd'
  assert '0x658398' in N[343].op_str
 if action==0x348:
  # Original PE x87 stack: signed parent F0E and own D8 FILD, then
  # FLD actual global 6590A8 and FMUL [actor+C8]. Other natural
  # C++ grammars reverse physical PE global relocation location.
  assert N[41].mnemonic==S[41].mnemonic=='fld'
  assert N[42].mnemonic==S[42].mnemonic=='fmul'
  assert any(f['x86_ordinal']==41 and f['original_native_PE_target']=='0x6590a8' for f in pe)
  assert '+ 0xc8' in N[42].op_str and '+ 0xc8' in S[42].op_str
  assert N[43].mnemonic==S[43].mnemonic=='faddp'
  assert N[104].mnemonic==S[104].mnemonic=='call'
 if action==0x349:
  # Native 349 uses a bit-exact DWORD copy of parent X, then original
  # FLD real parent Y ; FADD original 00658268. Typed member source
  # can incorrectly FLD the global first, despite identical mnemonics.
  assert N[33].mnemonic==S[33].mnemonic=='mov'
  assert '+ 0x44' in N[33].op_str and '+ 0x44' in S[33].op_str
  assert N[36].mnemonic==S[36].mnemonic=='fld'
  assert '+ 0x48' in N[36].op_str and '+ 0x48' in S[36].op_str
  assert N[37].mnemonic==S[37].mnemonic=='fadd'
  assert any(f['x86_ordinal']==37 and f['original_native_PE_target']=='0x658268' for f in pe)
  assert any(f['x86_ordinal']==42 and f['original_native_PE_target']=='0x657874' for f in pe)
 if action==0x34a:
  # Original bit-preserving parent X DWORD and zero Y are native,
  # as are original distinct parent+60/+62 checks against 0x2C0.
  assert N[4].mnemonic==S[4].mnemonic=='mov'
  assert N[6].mnemonic==S[6].mnemonic=='mov'
  assert N[41].op_str==S[41].op_str and '0xc2a00000' in N[41].op_str
  for ordinal in (53,58):
   assert N[ordinal].mnemonic==S[ordinal].mnemonic=='cmp'
   assert N[ordinal].op_str==S[ordinal].op_str and '0x2c0' in N[ordinal].op_str
  # Two genuine direct returns after final action completion, not a
  # synthetic compiler fallthrough that omits the original last JMP.
  assert N[100].mnemonic==S[100].mnemonic=='jmp'
  assert N[101].mnemonic==S[101].mnemonic=='jmp'
 if action==0x34b:
  # True 34B stage-zero timer is 99, real x87 actor-Y boundary
  # `TEST AH,0x41; JNE` and stage 15 frame-zero Y=-40.0f.
  assert N[14].mnemonic==S[14].mnemonic=='mov'
  assert '0x63' in N[14].op_str and N[14].op_str==S[14].op_str
  assert N[44].mnemonic==S[44].mnemonic=='test'
  assert N[44].op_str==S[44].op_str=='ah, 0x41'
  assert N[45].mnemonic==S[45].mnemonic=='jne'
  assert N[83].mnemonic==S[83].mnemonic=='mov'
  assert N[83].op_str==S[83].op_str and '0xc2200000' in N[83].op_str
  assert any(f['x86_ordinal']==42 and f['original_native_PE_target']=='0x658e80' for f in pe)
 if action==0x3e3:
  # The native 200-x86 state keeps +0x66 facing=1,
  # real 00483300 atan2/grandparent thresholds, original
  # +0x366 byte and +0x2D0 score, 45B860 hit action 0x2E.
  # Original one JNE at ordinal 43 is LONG; current partial
  # C++ emits short. Do not call this byte-exact.
  assert len(N)==200 and sum(n.size==q.size for n,q in zip(N,S))==199
  assert N[43].mnemonic==S[43].mnemonic=='jne'
  assert N[43].size==6 and S[43].size==2
  for k,target in ((34,'0x455580'),(69,'0x40fb70'),(91,'0x483300'),
                   (94,'0x6406ac'),(147,'0x45b830'),(175,'0x45b860')):
   assert any(f['x86_ordinal']==k and f['original_native_PE_target']==target for f in pe)
  assert N[173].mnemonic==S[173].mnemonic=='push'
  assert N[173].op_str==S[173].op_str=='0x2e'
 if action==0x3e4:
  # The actual original meter-and-hit state is NOT an exclusive
  # `if(3B6>0) else {meter3B0}`: after 3B6>5 decrement it
  # CONTINUES through the real 3B0 policy. This fixes a true
  # gameplay source bug and an extra generated terminal JMP.
  assert len(N)==261 and sum(n.size==q.size for n,q in zip(N,S))==260
  assert N[43].mnemonic==S[43].mnemonic=='jne'
  assert N[43].size==6 and S[43].size==2
  assert N[179].mnemonic==S[179].mnemonic=='jmp'
  assert N[187].mnemonic==S[187].mnemonic=='mov'
  assert N[188].mnemonic==S[188].mnemonic=='jmp'
  assert N[189].mnemonic==S[189].mnemonic=='mov'
  for k,target in ((34,'0x455580'),(69,'0x40fb70'),(91,'0x483300'),
                   (94,'0x6406ac'),(155,'0x45b860'),(157,'0x45b830'),
                   (219,'0x659228'),(227,'0x657478')):
   assert any(f['x86_ordinal']==k and f['original_native_PE_target']==target for f in pe)
 if action==0x3e5:
  # Extra shared-tail JMP is intentional and present in the native
  # 96-x86 source, recovered from two real returns around stage end.
  assert len(N)==96 and all(n.size==q.size for n,q in zip(N,S))
  assert N[95].mnemonic==S[95].mnemonic=='jmp'
  assert N[95].size==S[95].size==5
  assert N[35].mnemonic==S[35].mnemonic=='mov'
  assert N[35].op_str==S[35].op_str and '0x4e2' in N[35].op_str
 if action==0x392:
  # Genuine 0x392 full native 222B/47x86 reset/expiry, one
  # independent original switch entry and 4 physical PE calls.
  assert len(N)==47 and all(a.size==b.size for a,b in zip(N,S))
  assert N[22].mnemonic==S[22].mnemonic=='mov'
  assert N[22].op_str==S[22].op_str and '0x3f800000' in N[22].op_str
  assert any(f['x86_ordinal']==20 and f['original_native_PE_target']=='0x40fbb0' for f in pe)
  assert any(f['x86_ordinal']==38 and f['original_native_PE_target']=='0x40fa30' for f in pe)
 if action==0x393:
  # Original retry gate is 2 - signed difficulty; the original
  # two mutually exclusive 0x391 spawn sites have actual X=0
  # or X=1280, distinct random Y ranges 0..60/0..120.
  assert len(N)==110 and all(a.size==b.size for a,b in zip(N,S))
  assert N[109].mnemonic==S[109].mnemonic=='jmp'
  assert N[109].size==S[109].size==5
  for k,imm in ((67,'0x3c'),(77,'0x391'),(88,'0x78'),(97,'0x44a00000'),(98,'0x391')):
   assert N[k].mnemonic==S[k].mnemonic=='push'
   assert N[k].op_str==S[k].op_str==imm
  assert N[51].mnemonic==S[51].mnemonic=='mov'
  assert N[51].op_str==S[51].op_str=='eax, 2'
  assert any(f['x86_ordinal']==50 and f['original_native_PE_target']=='0x6714d0' for f in pe)
  assert any(f['x86_ordinal']==70 and f['original_native_PE_target']=='0x455580' for f in pe)
  assert any(f['x86_ordinal']==91 and f['original_native_PE_target']=='0x455580' for f in pe)
 if action==0x390:
  # Original 390 always loads raw angle +0xC8 as a DWORD for
  # the real two polar velocity calls, computes native atan2 and
  # uses real upper Y 00657884/lower Y 0065924C boundaries.
  assert len(N)==212 and all(n.size==q.size for n,q in zip(N,S))
  assert N[211].mnemonic==S[211].mnemonic=='jmp'
  assert N[211].size==S[211].size==5
  for k,t in ((31,'0x6590b4'),(32,'0x6592a4'),(39,'0x40fb70'),
              (58,'0x483300'),(60,'0x657828'),(77,'0x6592a4'),
              (84,'0x40fb70'),(150,'0x657884'),(156,'0x65924c'),
              (188,'0x659454'),(193,'0x659454')):
   assert any(f['x86_ordinal']==k and f['original_native_PE_target']==t for f in pe),(k,t)
  assert N[172].mnemonic==S[172].mnemonic=='movzx'
  assert N[173].mnemonic==S[173].mnemonic=='sub'
  assert N[173].op_str.endswith(', 0x19') and S[173].op_str.endswith(', 0x19')
 if action==0x38c:
  # Actual 38C must FLD native actor+0x50 before FADD global
  # 00659090; the first source had the global/actor roles reversed.
  assert len(N)==52 and all(n.size==q.size for n,q in zip(N,S))
  assert N[28].mnemonic==S[28].mnemonic=='fld'
  assert '+ 0x50' in N[28].op_str and '+ 0x50' in S[28].op_str
  assert N[29].mnemonic==S[29].mnemonic=='fadd'
  assert any(f['x86_ordinal']==29 and f['original_native_PE_target']=='0x659090' for f in pe)
 if action==0x38e:
  # Native 38E copies own DWORD +0xC8 into x-motion +0x50,
  # then physically spawns 38F and bounds actor X with two
  # original globals. End uses ONE common return.
  assert len(N)==91 and all(n.size==q.size for n,q in zip(N,S))
  assert N[40].mnemonic==S[40].mnemonic=='push'
  assert N[40].op_str==S[40].op_str=='0x38f'
  assert N[79].mnemonic==S[79].mnemonic=='lea'
  assert N[79].op_str==S[79].op_str
  for k,dest in ((46,'0x659424'),(52,'0x65924c'),(78,'0x6714d0')):
   assert any(f['x86_ordinal']==k and f['original_native_PE_target']==dest for f in pe)
 if action==0x38f:
  # Restoring true following 390 expands original shared-tail
  # distance; the original 38F final JMP now naturally emits
  # 5 bytes instead of the historically premature 2-byte short.
  assert len(N)==32 and all(a.size==b.size for a,b in zip(N,S))
  assert N[31].mnemonic==S[31].mnemonic=='jmp'
  assert N[31].size==S[31].size==5
  assert any(f['x86_ordinal']==23 and f['original_native_PE_target']=='0x40fa30' for f in pe)
 if action==0x38b:
  # Actual original speed step uses actor+0x50 first, then
  # 00657478 global (x87 FLD followed by FADD, ordinal 101/102).
  # The original signed +0xDC phase raises 0..30, true +0xD8
  # collision cooldown, and stage 23 redirect have real dimensions.
  assert len(N)==226 and all(n.size==q.size for n,q in zip(N,S))
  assert N[101].mnemonic==S[101].mnemonic=='fld'
  assert '+ 0x50' in N[101].op_str and '+ 0x50' in S[101].op_str
  assert N[102].mnemonic==S[102].mnemonic=='fadd'
  assert any(f['x86_ordinal']==102 and f['original_native_PE_target']=='0x657478' for f in pe)
  assert N[89].mnemonic==S[89].mnemonic=='cmp'
  assert N[89].op_str.endswith(', 0x1e') and S[89].op_str.endswith(', 0x1e')
  assert N[98].mnemonic==S[98].mnemonic=='cmp'
  assert N[98].op_str.endswith(', 0x1d') and S[98].op_str.endswith(', 0x1d')
  assert N[200].mnemonic==S[200].mnemonic=='push'
  assert N[200].op_str==S[200].op_str=='0x17'
 if action==0x38a:
  # Original 0x38A versus 0x384 has TWO genuinely distinct 15-shot
  # loops, 33A and 389; original scale comparison uses actual
  # global 0065747C, not 384's 00657480.
  assert len(N)==226 and all(n.size==q.size for n,q in zip(N,S))
  for k,imm in ((95,'0x385'),(108,'0x347'),(129,'0x33a'),
                (151,'0x389'),(176,'0x1e')):
   assert N[k].mnemonic==S[k].mnemonic=='push'
   assert N[k].op_str==S[k].op_str==imm
  assert all(any(f['x86_ordinal']==k and f['original_native_PE_target']=='0x65747c' for f in pe)
             for k in (59,67))
  assert any(f['x86_ordinal']==179 and f['original_native_PE_target']=='0x455580' for f in pe)
  assert N[117].mnemonic==S[117].mnemonic=='cmp'
  assert N[117].op_str.endswith(', 0xf') and S[117].op_str.endswith(', 0xf')
  assert N[139].mnemonic==S[139].mnemonic=='cmp'
  assert N[139].op_str.endswith(', 0xf') and S[139].op_str.endswith(', 0xf')
 if action==0x389:
  # Actual signed-short randomized timer/direction/limit and
  # double-precision randomized scale, native 0x33C projectile.
  # Both original 0040FB70 calls and native FILD/FADD/FMULT
  # in their original codegen order; final source return shared.
  assert len(N)==238 and all(n.size==q.size for n,q in zip(N,S))
  for k,imm in ((62,'0x12c'),(69,'0x32'),(76,'0xf'),(127,'0x33c')):
   assert N[k].mnemonic==S[k].mnemonic=='push'
   assert N[k].op_str==S[k].op_str==imm
  for k,imm in ((66,'0xc8'),(73,'0x2d'),(80,'5'),(148,'0xf')):
   assert N[k].mnemonic==S[k].mnemonic in ('add','sub')
   assert N[k].op_str.endswith(', '+imm) and S[k].op_str.endswith(', '+imm)
  assert all(any(f['x86_ordinal']==k and f['original_native_PE_target']=='0x455580' for f in pe)
             for k in (65,72,79,134))
  assert all(any(f['x86_ordinal']==k and f['original_native_PE_target']=='0x40fb70' for f in pe)
             for k in (97,116))
  assert any(f['x86_ordinal']==138 and f['original_native_PE_target']=='0x658a20' for f in pe)
  assert any(f['x86_ordinal']==139 and f['original_native_PE_target']=='0x657d00' for f in pe)
 if action==0x388:
  # Original game action 388 has an UNORDERED-aware JNP after
  # TEST AH,0x41. C++ ordinary '>' emits JNE and is not equivalent
  # on unordered FPU input. Native grammar is !(Y+Vy <= ground).
  assert len(N)==160 and all(n.size==q.size for n,q in zip(N,S))
  assert N[27].mnemonic==S[27].mnemonic=='push'
  assert N[27].op_str==S[27].op_str=='0x42700000'
  assert N[48].mnemonic==S[48].mnemonic=='mov'
  assert N[48].op_str==S[48].op_str and '0x41b40000' in N[48].op_str
  assert N[63].mnemonic==S[63].mnemonic=='push'
  assert N[63].op_str==S[63].op_str=='0x345'
  assert N[116].mnemonic==S[116].mnemonic=='test'
  assert N[116].op_str==S[116].op_str=='ah, 0x41'
  assert N[117].mnemonic==S[117].mnemonic=='jnp'
  assert N[159].mnemonic==S[159].mnemonic=='jmp'
  assert all(any(f['x86_ordinal']==k and f['original_native_PE_target']=='0x65782c' for f in pe)
             for k in (89,114))
 if action==0x387:
  # Actual original 0x387 performs 3 native random calls for
  # angle, X and Y speeds; stage 1 landing uses real x87
  # TEST AH,0x41;JP and original FCHS velocity reversal.
  assert len(N)==167 and all(n.size==q.size for n,q in zip(N,S))
  for ord,imm in ((66,'0x167'),(74,'0x10'),(83,'6')):
   assert N[ord].mnemonic==S[ord].mnemonic=='push'
   assert N[ord].op_str==S[ord].op_str==imm
  for ord in (69,77,86):
   assert any(f['x86_ordinal']==ord and f['original_native_PE_target']=='0x455580' for f in pe)
  assert any(f['x86_ordinal']==94 and f['original_native_PE_target']=='0x659888' for f in pe)
  assert N[128].mnemonic==S[128].mnemonic=='test'
  assert N[128].op_str==S[128].op_str=='ah, 0x41'
  assert N[129].mnemonic==S[129].mnemonic=='jp'
  assert N[135].mnemonic==S[135].mnemonic=='fchs'
 if action==0x386:
  # Native stage 1 uses FILD random(0,4), float 6590B4 and
  # DOUBLE 6583B8, then genuine 412D90 absolute distance.
  # Completion calls 453E60(10) and spawns 12 real 0x387
  # projectiles with independent random Y and X offsets.
  assert len(N)==195 and all(n.size==q.size for n,q in zip(N,S))
  assert any(f['x86_ordinal']==81 and f['original_native_PE_target']=='0x6583b8' for f in pe)
  assert any(f['x86_ordinal']==96 and f['original_native_PE_target']=='0x412d90' for f in pe)
  assert any(f['x86_ordinal']==164 and f['original_native_PE_target']=='0x658264' for f in pe)
  assert N[163].mnemonic==S[163].mnemonic=='fld'
  assert '+ 0x44' in N[163].op_str and '+ 0x44' in S[163].op_str
  assert N[164].mnemonic==S[164].mnemonic=='fadd'
  assert N[148].mnemonic==S[148].mnemonic=='cmp'
  assert N[148].op_str.endswith(', 0xc') and S[148].op_str.endswith(', 0xc')
  for k,imm in ((154,'0x140'),(166,'0x50'),(175,'0x387')):
   assert N[k].mnemonic==S[k].mnemonic=='push'
   assert N[k].op_str==S[k].op_str==imm
  assert all(any(f['x86_ordinal']==k and f['original_native_PE_target']=='0x455580' for f in pe)
             for k in (77,157,169))
 if action==0x385:
  # Genuine 385 used scale X 1.0/Y 2.0, degree 15.0,
  # stage 2 random x87 with real additive 00659094 and
  # stage>2 independent fade at 00659240.
  assert len(N)==114 and all(n.size==q.size for n,q in zip(N,S))
  assert N[40].mnemonic==S[40].mnemonic=='mov'
  assert N[40].op_str==S[40].op_str and '0x40000000' in N[40].op_str
  assert N[50].mnemonic==S[50].mnemonic=='mov'
  assert N[50].op_str==S[50].op_str and '0x41700000' in N[50].op_str
  assert any(f['x86_ordinal']==58 and f['original_native_PE_target']=='0x455580' for f in pe)
  assert any(f['x86_ordinal']==62 and f['original_native_PE_target']=='0x659094' for f in pe)
  assert any(f['x86_ordinal']==76 and f['original_native_PE_target']=='0x659240' for f in pe)
  assert N[98].mnemonic==S[98].mnemonic=='cmp'
  assert N[98].op_str==S[98].op_str and ', 9' in N[98].op_str
 if action==0x384:
  # Original game difficulty tests are TWO independent branches,
  # not one nested branch. The source initially matched all 277
  # mnemonics/GPR/24 real PE fields but 277 instruction widths
  # failed at the first long JLE, and low difficulty behavior was
  # wrong. The physically native independent branches restore all.
  assert len(N)==277 and all(n.size==q.size for n,q in zip(N,S))
  assert N[100].mnemonic==S[100].mnemonic=='jle' and N[100].size==S[100].size==2
  assert N[130].mnemonic==S[130].mnemonic=='jle'
  assert N[95].mnemonic==S[95].mnemonic=='push'
  assert N[95].op_str==S[95].op_str=='0x385'
  for k,imm in ((112,'0x38e'),(124,'0x38e'),(142,'0x38e'),(154,'0x38e'),
                (168,'0x347'),(189,'0x33a')):
   assert N[k].mnemonic==S[k].mnemonic=='push'
   assert N[k].op_str==S[k].op_str==imm,(k,imm)
  assert N[177].mnemonic==S[177].mnemonic=='cmp'
  assert N[177].op_str.endswith(', 0xf') and S[177].op_str.endswith(', 0xf')
  assert any(f['x86_ordinal']==98 and f['original_native_PE_target']=='0x6714d0' for f in pe)
  assert any(f['x86_ordinal']==128 and f['original_native_PE_target']=='0x6714d0' for f in pe)
  assert any(f['x86_ordinal']==225 and f['original_native_PE_target']=='0x65988c' for f in pe)
 if action in (0x365,0x366,0x367,0x368,0x369):
  # Real original 2,214B case has 452 native x86 and retains
  # every original width/GPR role, including parent-facing
  # homing angle and its *independent* second angle comparison.
  assert all(n.size==q.size for n,q in zip(N,S)),(hex(action),'native width regression')
  assert N[277].mnemonic==S[277].mnemonic=='push'
  assert N[277].op_str==S[277].op_str==hex(0x33c+2*(action-0x365))
  assert any(f['x86_ordinal']==280 and f['original_native_PE_target']=='0x453a70' for f in pe)
  assert any(f['x86_ordinal']==288 and f['original_native_PE_target']=='0x658a20' for f in pe)
  assert any(f['x86_ordinal']==289 and f['original_native_PE_target']=='0x657d00' for f in pe)
  assert any(f['x86_ordinal']==255 and f['original_native_PE_target']=='0x6578c0' for f in pe)
  assert any(f['x86_ordinal']==256 and f['original_native_PE_target']=='0x657cf8' for f in pe)
 if action in (0x360,0x361,0x362,0x363,0x364):
  # Both actual original PE handlers are separately physical, each
  # 206 x86. Their final spawned object is 0x365 and 0x366,
  # respectively; the source must keep distinct switch labels.
  assert N[199].mnemonic==S[199].mnemonic=='push'
  expected_id=hex(action+5)
  assert N[199].op_str==S[199].op_str==expected_id
  assert any(f['x86_ordinal']==202 and f['original_native_PE_target']=='0x453a70' for f in pe)
  assert N[205].mnemonic==S[205].mnemonic=='jmp'
  assert N[91].mnemonic==S[91].mnemonic=='mov'
  assert N[91].op_str==S[91].op_str and '0xf' in N[91].op_str
  # The native original uses the same 0x595EC physically defined
  # float global for its lower X and Y border checks.
  assert all(any(f['original_native_PE_target']=='0x6595ec' and f['x86_ordinal']==i for f in pe)
             for i in (158,170))
 if action==0x357:
  # Original parent state 0x189 follows parent X plus native
  # signed facing*120 and Y=120.0f, then native x87 TEST AH5;JP
  # scale fade and actual parent +0x82 completion gate.
  assert N[21].mnemonic==S[21].mnemonic=='cmp'
  assert N[21].op_str==S[21].op_str and '0x189' in N[21].op_str
  assert N[31].mnemonic==S[31].mnemonic=='imul'
  assert N[31].op_str==S[31].op_str and '0x78' in N[31].op_str
  assert N[38].mnemonic==S[38].mnemonic=='mov'
  assert N[38].op_str==S[38].op_str and '0x42f00000' in N[38].op_str
  assert N[76].mnemonic==S[76].mnemonic=='test'
  assert N[76].op_str==S[76].op_str=='ah, 5'
  assert N[77].mnemonic==S[77].mnemonic=='jp'
  assert any(f['x86_ordinal']==74 and f['original_native_PE_target']=='0x65747c' for f in pe)
 if action==0x356:
  # Original 356 is NOT an alias for 354: original initial native
  # Y velocity = -7.5f and real native Y additive global 00657F74.
  assert N[85].mnemonic==S[85].mnemonic=='mov'
  assert N[85].op_str==S[85].op_str and '0xc0f00000' in N[85].op_str
  assert N[100].mnemonic==S[100].mnemonic=='fld'
  assert '+ 0x54' in N[100].op_str and '+ 0x54' in S[100].op_str
  assert any(f['x86_ordinal']==101 and f['original_native_PE_target']=='0x657f74' for f in pe)
  for test,jump in ((108,109),(120,121)):
   assert N[test].mnemonic==S[test].mnemonic=='test'
   assert N[test].op_str==S[test].op_str=='ah, 5'
   assert N[jump].mnemonic==S[jump].mnemonic=='jp'
 if action==0x355:
  # Original parent 0x45..0x96 triggers ten 0x3E4 shots plus
  # extra 0x3E3, true dual motion bounds, 31-stage winding and
  # actual original Y lvalue FLD before 006583F8 global FADD.
  assert N[3].mnemonic==S[3].mnemonic=='cmp' and '0x45' in N[3].op_str
  assert N[17].mnemonic==S[17].mnemonic=='cmp' and ', 0xa' in N[17].op_str
  assert N[27].mnemonic==S[27].mnemonic=='push'
  assert N[27].op_str==S[27].op_str=='0x3e4'
  assert N[48].mnemonic==S[48].mnemonic=='push'
  assert N[48].op_str==S[48].op_str=='0x3e3'
  assert any(f['x86_ordinal']==94 and f['original_native_PE_target']=='0x659898' for f in pe)
  for test,jump,mask,branch in ((96,97,'ah, 5','jp'),(124,125,'ah, 0x41','jne'),
                                (135,136,'ah, 5','jp'),(152,153,'ah, 5','jp'),
                                (169,170,'ah, 0x41','jne')):
   assert N[test].mnemonic==S[test].mnemonic=='test'
   assert N[test].op_str==S[test].op_str==mask
   assert N[jump].mnemonic==S[jump].mnemonic==branch
  assert N[161].mnemonic==S[161].mnemonic=='fld'
  assert '+ 0x54' in N[161].op_str and '+ 0x54' in S[161].op_str
  assert any(f['x86_ordinal']==162 and f['original_native_PE_target']=='0x6583f8' for f in pe)
  assert N[187].mnemonic==S[187].mnemonic=='cmp'
  assert ', 0x1f' in N[187].op_str and ', 0x1f' in S[187].op_str
 if action==0x354:
  # Original eight real 0x3E4 shots under native parent bounds,
  # independent extra 0x3E3, native actor Y x87 borrow before
  # global+006583F8 and the TWO real parity-aware x87 comparisons.
  assert N[21].mnemonic==S[21].mnemonic=='cmp'
  assert N[21].op_str.endswith(', 8') and S[21].op_str.endswith(', 8')
  assert N[31].mnemonic==S[31].mnemonic=='push'
  assert N[31].op_str==S[31].op_str=='0x3e4'
  assert N[52].mnemonic==S[52].mnemonic=='push'
  assert N[52].op_str==S[52].op_str=='0x3e3'
  assert N[100].mnemonic==S[100].mnemonic=='fld'
  assert '+ 0x54' in N[100].op_str and '+ 0x54' in S[100].op_str
  assert N[101].mnemonic==S[101].mnemonic=='fadd'
  assert any(f['x86_ordinal']==101 and f['original_native_PE_target']=='0x6583f8' for f in pe)
  for test,jump in ((108,109),(120,121)):
   assert N[test].mnemonic==S[test].mnemonic=='test'
   assert N[test].op_str==S[test].op_str=='ah, 5'
   assert N[jump].mnemonic==S[jump].mnemonic=='jp'
 if action==0x352:
  # Original initial scale 0.5f, actual step global 0065747C
  # on BOTH axes, and stage >1 alpha subtraction exactly 20.
  assert N[14].mnemonic==S[14].mnemonic=='mov'
  assert N[14].op_str==S[14].op_str and '0x3f000000' in N[14].op_str
  assert N[29].mnemonic==S[29].mnemonic=='fadd'
  assert N[34].mnemonic==S[34].mnemonic=='fadd'
  assert all(any(f['x86_ordinal']==i and f['original_native_PE_target']=='0x65747c' for f in pe) for i in (29,34))
  assert N[43].mnemonic==S[43].mnemonic=='cmp'
  assert N[43].op_str==S[43].op_str and '0x14' in N[43].op_str
 if action==0x353:
  # Entire native 155B original animation reset + original frame
  # getter and expiry, with no extra symbol or physical owner.
  assert N[14].mnemonic==S[14].mnemonic=='mov'
  assert '0x3f800000' in N[14].op_str and N[14].op_str==S[14].op_str
  assert N[26].mnemonic==S[26].mnemonic=='call'
  assert any(f['x86_ordinal']==26 and f['original_native_PE_target']=='0x40fa30' for f in pe)
 if action==0x351:
  # First actual parent-facing x87 int*20 addition, native 6..11
  # scale behavior, physical seven-argument projectile 0x352 and
  # actual original stage 16 parent 0x2BF gate, not guessed phase.
  assert N[5].mnemonic==S[5].mnemonic=='imul'
  assert N[5].op_str==S[5].op_str and '0x14' in N[5].op_str
  assert N[86].op_str==S[86].op_str=='ah, 1'
  assert N[123].mnemonic==S[123].mnemonic=='push'
  assert N[123].op_str==S[123].op_str=='0x33a'
  assert N[146].mnemonic==S[146].mnemonic=='cmp'
  assert N[146].op_str==S[146].op_str and '0x23' in N[146].op_str
  assert N[160].mnemonic==S[160].mnemonic=='push'
  assert N[160].op_str==S[160].op_str=='0x352'
  assert any(f['x86_ordinal']==163 and f['original_native_PE_target']=='0x453b50' for f in pe)
  assert N[230].mnemonic==S[230].mnemonic=='cmp'
  assert N[230].op_str==S[230].op_str and '0x2bf' in N[230].op_str
 if action==0x350:
  # The genuinely distinct original 0x350 combines four native
  # parent triggers, including 0x192/4 and 0x260/4 through 0x262/4.
  # Eight 45-degree shots of native projectile 0x364.
  for i,imm in ((127,'0x192'),(137,'0x260'),(147,'0x261'),(157,'0x262')):
   assert N[i].mnemonic==S[i].mnemonic=='cmp'
   assert N[i].op_str==S[i].op_str and imm in N[i].op_str
  assert N[172].mnemonic==S[172].mnemonic=='imul'
  assert N[172].op_str==S[172].op_str and '0x2d' in N[172].op_str
  assert N[189].mnemonic==S[189].mnemonic=='push'
  assert N[189].op_str==S[189].op_str=='0x364'
  assert any(f['x86_ordinal']==192 and f['original_native_PE_target']=='0x453a70' for f in pe)
 if action==0x34f:
  # Original parent combinations 194/4, 263/5, 264/5,
  # eight real 45-degree 0x363 projectile shots, and exact native
  # parent-owned angle float writeback.
  assert N[127].mnemonic==S[127].mnemonic=='cmp' and '0x194' in N[127].op_str
  assert N[137].mnemonic==S[137].mnemonic=='cmp' and '0x263' in N[137].op_str
  assert N[147].mnemonic==S[147].mnemonic=='cmp' and '0x264' in N[147].op_str
  assert N[162].mnemonic==S[162].mnemonic=='imul'
  assert N[162].op_str==S[162].op_str and '0x2d' in N[162].op_str
  assert N[179].mnemonic==S[179].mnemonic=='push'
  assert N[179].op_str==S[179].op_str=='0x363'
  assert any(f['x86_ordinal']==182 and f['original_native_PE_target']=='0x453a70' for f in pe)
 if action==0x34e:
  # Genuine original 0x34E parent cases 195/4, 1F4/14, 1F5/14,
  # eight native 45-degree trajectory shots of object ID 0x362.
  assert N[127].mnemonic==S[127].mnemonic=='cmp' and '0x195' in N[127].op_str
  assert N[137].mnemonic==S[137].mnemonic=='cmp' and '0x1f4' in N[137].op_str
  assert N[147].mnemonic==S[147].mnemonic=='cmp' and '0x1f5' in N[147].op_str
  assert N[162].mnemonic==S[162].mnemonic=='imul'
  assert N[162].op_str==S[162].op_str and '0x2d' in N[162].op_str
  assert N[179].mnemonic==S[179].mnemonic=='push'
  assert N[179].op_str==S[179].op_str=='0x362'
  assert any(f['x86_ordinal']==182 and f['original_native_PE_target']=='0x453a70' for f in pe)
 if action==0x34d:
  # Real 34D parent actions 191/4 OR 25C/6, original loop 8
  # times with literal 0x361 (not 34C 0x360). Real native
  # frame-2 transition occurs after actual alpha fade branch.
  assert N[127].mnemonic==S[127].mnemonic=='cmp'
  assert N[127].op_str==S[127].op_str and '0x191' in N[127].op_str
  assert N[137].mnemonic==S[137].mnemonic=='cmp'
  assert N[137].op_str==S[137].op_str and '0x25c' in N[137].op_str
  assert N[149].mnemonic==S[149].mnemonic=='cmp'
  assert N[152].mnemonic==S[152].mnemonic=='imul'
  assert N[152].op_str==S[152].op_str and '0x2d' in N[152].op_str
  assert N[169].mnemonic==S[169].mnemonic=='push'
  assert N[169].op_str==S[169].op_str=='0x361'
  assert any(f['x86_ordinal']==172 and f['original_native_PE_target']=='0x453a70' for f in pe)
 if action==0x34c:
  # Native real x87 field/velocity order, 8-shot loop of 0x360
  # and the actual original parent-owned trajectory float +0x314.
  assert N[45].mnemonic==S[45].mnemonic=='fld'
  assert any(f['x86_ordinal']==45 and f['original_native_PE_target']=='0x65989c' for f in pe)
  assert N[60].mnemonic==S[60].mnemonic=='fld'
  assert '+ 0x54' in N[60].op_str and '+ 0x54' in S[60].op_str
  assert N[61].mnemonic==S[61].mnemonic=='fmul'
  assert any(f['x86_ordinal']==61 and f['original_native_PE_target']=='0x657f74' for f in pe)
  assert N[169].mnemonic==S[169].mnemonic=='cmp'
  assert N[172].mnemonic==S[172].mnemonic=='imul'
  assert N[172].op_str==S[172].op_str and '0x2d' in N[172].op_str
  assert N[192].mnemonic==S[192].mnemonic=='call'
  assert any(f['x86_ordinal']==192 and f['original_native_PE_target']=='0x453a70' for f in pe)
  assert N[189].mnemonic==S[189].mnemonic=='push'
  assert N[189].op_str==S[189].op_str=='0x360'
 if action==0x347:
  # Actual signed facing*25 and two original x87 FMUL/FSUBR/FADD
  # independent fade tracks, distinct from the similar 0x339 source.
  assert N[31].mnemonic==S[31].mnemonic=='imul'
  assert '0x19' in N[31].op_str and '0x19' in S[31].op_str
  assert [N[i].mnemonic for i in (42,50,51,60,68,69)]==['fmul','fsubr','fadd','fmul','fsubr','fadd']
  assert all(N[i].mnemonic==S[i].mnemonic for i in (42,50,51,60,68,69))
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
  'native_scalar_immediate_ordinals_verified':original_scalar_imm_count,
  'native_physically_correct_PE_call_global_fields':pe,
  'one_original_whole_function_exact':False})
 print(hex(action),'native',hi_orig-lo_orig,'B/',len(N),'x86; selected source',hi-lo,'B;',len(pe),'real PE fields',flush=True)
assert len(set(known))==len(required_fields)
original_total=sum(row['original_interior_CODE_B'] for row in rows)
x86total=sum(row['original_native_x86'] for row in rows)
src_total=sum(row['current_source_interior_CODE_B'] for row in rows)
fields_total=sum(len(row['native_physically_correct_PE_call_global_fields']) for row in rows)
assert (original_total,x86total,fields_total)==(75260,16090,1246)
# Additional REAL original C++ interiors, deliberately kept separately
# PROVISIONAL: their native mnemonics, scalar immediates and physical PE
# destinations match, but whole-parent GPR phases are NOT native yet.
# Do not inflate the exact/recovered counts or mask GPR-role debt.
provisional_native_fields={0x358:11,0x359:2,0x35a:3,0x35b:13,0x35c:6,0x35d:7,0x35e:28,0x3e6:9}
provisional_rows=[]
for act,expected_field_count in provisional_native_fields.items():
 ix=orig_sparse[act-0x320]
 start,stop=orig_dense[ix],orig_dense[ix+1]
 N=[x for x in NWHOLE if start<=x.address<stop]
 lo,hi=T[ix]['local_symbol_offset'],T[ix+1]['local_symbol_offset']
 S=[x for x in I if lo<=x.address<hi]
 assert N and S and len(N)==len(S) and N[0].address==start
 assert all(a.mnemonic==b.mnemonic for a,b in zip(N,S)),hex(act)
 fs=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
 assert len(fs)==expected_field_count,(hex(act),len(fs),expected_field_count)
 ordinals=set()
 for r in fs:
  assert r['type'] in ('REL32','DIR32') and r['addend']==0
  j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
  d=r['offset']-S[j].address
  assert d+4<=N[j].size,(hex(act),j,'source relocation not original instruction')
  p=N[j].address+d
  v=int.from_bytes(rd.pe_bytes_at(P,p,4),'little',signed=r['type']=='REL32')
  target=p+4+v if r['type']=='REL32' else v
  m=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
  expected=int(m.group(1),16) if m else 0x6406ac if r['symbol']=='__ftol2' else None
  assert expected==target,(hex(act),j,r['symbol'],hex(target),hex(expected or 0))
  ordinals.add(j)
 scalars=0
 for j,(n,q) in enumerate(zip(N,S)):
  if j in ordinals or n.mnemonic=='call' or n.mnemonic.startswith('j'):
   continue
  a,b=scalar.search(n.op_str),scalar.search(q.op_str)
  if a or b:
   assert a is not None and b is not None and a.group(1)==b.group(1),(
       hex(act),j,'native scalar differs',n.op_str,q.op_str)
   scalars+=1
 gpr_match=sum(roles(a)==roles(b) for a,b in zip(N,S))
 assert gpr_match<len(N),(hex(act),'not eligible as provisional if GPR exact')
 row={'action':hex(act),'original_inner_CODE_B':stop-start,
      'native_x86':len(N),'source_inner_CODE_B':hi-lo,
      'matching_mnemonics':len(N),'matching_instruction_widths':sum(a.size==b.size for a,b in zip(N,S)),
      'matching_GPR_roles':gpr_match,'physically_correct_PE_external_fields':len(fs),
      'matching_original_native_nonrelocated_scalars':scalars,
      'original_entire_81KB_callable_exact':False,'interior_phase_verified':False}
 provisional_rows.append(row)
 print(hex(act),'PROVISIONAL original',stop-start,'B/',len(N),'x86:',
       'MN',len(N),'GPR',gpr_match,'PE',len(fs),'scalar',scalars,flush=True)
assert len(provisional_rows)==8
summary={'original_Boss':'0x0050A580','original_whole_CODE_B':81539,
 'original_whole_x86':17435,'selected_partial_source_CODE_B':end,'selected_partial_source_x86':len(I),
 'source_partial_afterRET_DATA_B':567,'original_recovered_independent_case_interior_count':len(rows),
 'total_recovered_native_original_state_CODE_B':original_total,
 'total_recovered_native_original_x86':x86total,
 'total_native_mnemonics_and_GPR_roles_matching':x86total,
 'total_original_PE_nonlocal_fields_physically_verified':fields_total,
 'total_native_nonrelocated_scalar_immediates_verified':sum(r['native_scalar_immediate_ordinals_verified'] for r in rows),
 'total_generated_inner_case_source_CODE_B':src_total,
 'original_92_DIR32_native_jump_partitions_equal':True,'original_199_sparse_bytes_equal':True,
 'original_81KB_whole_function_exact':False,'new_exact_original_whole_CODE_B':0,
 'all_979_cold_replay':False,'native_states':rows,
 'additional_original_native_provisional_interiors':provisional_rows,
 'provisional_CASES_NOT_counted_as_recovered_or_exact':len(provisional_rows),
 'whole_native_original_direct_jumps_audited':physical_original_branch_positions,
 'remaining_nonexact_native_branch_target_mismatches':native_branch_target_debt}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1132 LIVE 82 original game action interiors: original',original_total,'CODE B /',x86total,'x86, native mnemonic+GPR',x86total,'/',x86total,'and genuine PE nonlocal',fields_total,'/',fields_total,'. Current partial source',end,'B /',len(I),'x86, NOT exact whole 81KB; accepted new original bytes 0.')
