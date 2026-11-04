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
 0x346:34,0x347:10,0x348:9,0x349:7,0x34a:7,0x34b:6,0x34c:18,0x34d:18,0x34e:18,0x34f:18,0x350:18,0x351:15,0x352:6,0x353:3,0x354:14,0x355:20,0x356:14,0x357:7,
}
assert len(required_fields)==54 and sum(required_fields.values())==771
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
assert (original_total,x86total,fields_total)==(46518,10086,771)
# Additional REAL original C++ interiors, deliberately kept separately
# PROVISIONAL: their native mnemonics, scalar immediates and physical PE
# destinations match, but whole-parent GPR phases are NOT native yet.
# Do not inflate the exact/recovered counts or mask GPR-role debt.
provisional_native_fields={0x358:11,0x359:2,0x35a:3,0x35b:13,0x35c:6}
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
assert len(provisional_rows)==5
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
 'provisional_CASES_NOT_counted_as_recovered_or_exact':len(provisional_rows)}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1098 LIVE 54 original game action interiors: original',original_total,'CODE B /',x86total,'x86, native mnemonic+GPR',x86total,'/',x86total,'and genuine PE nonlocal',fields_total,'/',fields_total,'. Current partial source',end,'B /',len(I),'x86, NOT exact whole 81KB; accepted new original bytes 0.')
