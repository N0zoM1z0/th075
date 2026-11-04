#!/usr/bin/env python3
"""F1055: five ORIGINAL 252B fade game-state interiors, one 81KB Boss.

Cold build only the complete tracked partial 0050A580 source parent; audit
pinned original full 81KB SHA, genuine original five separate handler starts,
original 92 afterRET labels/199 sparse indices and each original physical PE
call/global target. Matching instructions are not new independent callables,
and this function is NOT byte exact or original-whole complete.
"""
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import hashlib, importlib.util, json, os, re, subprocess, sys, collections
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1055-five-fade-native'; O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1055rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
P=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
B=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x0050A580)
assert (B['size'],B['instructions'],B['postret_size'],B['dense_entries'],B['sparse_bytes'])==(81539,17435,567,92,199)
original_whole=rd.pe_bytes_at(P,B['address'],B['size']);assert hashlib.sha256(original_whole).hexdigest()==B['sha256']
original_ins=list(D.disasm(original_whole,B['address']));assert len(original_ins)==17435
assert original_ins[2].op_str=='esp, 0x3a0' and original_ins[3].op_str=='dword ptr [ebp - 0xac], ecx'
original_after=rd.pe_bytes_at(P,B['address']+B['size'],B['postret_size'])
assert hashlib.sha256(original_after).hexdigest()==B['postret_sha']
dense=[int.from_bytes(original_after[i*4:i*4+4],'little') for i in range(92)]
mapbytes=original_after[368:];assert len(mapbytes)==199
assert hashlib.sha256(original_after[:368]).hexdigest()==B['tables'][0]['dense_sha']
assert hashlib.sha256(mapbytes).hexdigest()==B['tables'][0]['map_sha']
frag=(R/'probes/CharacterObjectBossFadeF1055.inc').read_text()
assert 'case F1055_CASE:' in frag and frag.count('g_F1055_FadeScaleAt006598A4')==2
assert ' *= ' not in frag and frag.count('SELF_FIELD(float,0x1C) * g_F1055_FadeScaleAt006598A4')==1
assert frag.count('SELF_FIELD(float,0x20) * g_F1055_FadeScaleAt006598A4')==1
src=R/'probes/CharacterObjectWhole0050A580F1044.cpp'
for action in ('33C','33E','340','342','344'):
 s=src.read_text();needle=f'#define F1055_CASE 0x{action}\n#include "CharacterObjectBossFadeF1055.inc"\n#undef F1055_CASE'
 assert s.count(needle)==1,action
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'current-five-native-fades-whole-parent.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=375)
(O/'whole-native-VC71.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(5258,1325,567,256)
T=sorted([r for r in refs if r['offset']>=end],key=lambda x:x['offset'])
assert len(T)==92 and all(r['type']=='DIR32' and r['offset']==end+4*i and r['addend']==0 and r['local_symbol_offset'] is not None for i,r in enumerate(T))
assert code[end+368:]==mapbytes
assert all((dense[i]==dense[j])==(T[i]['local_symbol_offset']==T[j]['local_symbol_offset']) for i in range(92) for j in range(92))
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(RX.findall(x.op_str))
cases=[('33c',0x50f9ce,0x50faca,17),('33e',0x51023e,0x51033a,57),
 ('340',0x510aae,0x510baa,17),('342',0x51131e,0x51141a,17),('344',0x511b8e,0x511c8a,57)]
rows=[]
for action,start,stop,expected_gpr in cases:
 slot=mapbytes[int(action,16)-0x320]
 assert dense[slot]==start and dense[slot+1]==stop
 lo,hi=T[slot]['local_symbol_offset'],T[slot+1]['local_symbol_offset']
 N=[x for x in original_ins if start<=x.address<stop]
 S=[x for x in I if lo<=x.address<hi]
 assert len(N)==len(S)==57 and stop-start==252 and hi-lo==192
 wrong_m=[i for i,(a,b) in enumerate(zip(N,S)) if a.mnemonic!=b.mnemonic]
 wrong_w=[i for i,(a,b) in enumerate(zip(N,S)) if a.size!=b.size]
 wrong_g=[i for i,(a,b) in enumerate(zip(N,S)) if role(a)!=role(b)]
 assert not wrong_m and len(wrong_w)==20 and len(wrong_g)==57-expected_gpr,(action,wrong_m,wrong_w,wrong_g)
 # All 20 width mismatches are the same real wide saved-this stack
 # operand, not a forbidden trick or an ignored unknown byte.
 assert all(a.size-b.size==3 and '[ebp - 0xac]' in a.op_str and '[ebp - 0xc]' in b.op_str
  for j in wrong_w for a,b in [(N[j],S[j])])
 actual=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
 assert len(actual)==5
 verified=[]
 for r in actual:
  assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
  j=next(i for i,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
  d=r['offset']-S[j].address; field=N[j].address+d
  assert d+4<=N[j].size
  value=int.from_bytes(rd.pe_bytes_at(P,field,4),'little',signed=r['type']=='REL32')
  original_target=field+4+value if r['type']=='REL32' else value
  alias=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
  assert alias is not None and int(alias.group(1),16)==original_target
  assert N[j].mnemonic=='call' if r['type']=='REL32' else N[j].mnemonic=='fmul'
  verified.append({'native_x86_ordinal':j,'original_PE_field':hex(field),'kind':r['type'],
   'original_PE_target':hex(original_target),'actual_source_symbol':r['symbol']})
 assert [x['original_PE_target'] for x in verified].count('0x6598a4')==2
 assert sum(x['kind']=='REL32' for x in verified)==3
 rows.append({'action':action,'native_CODE_B':252,'native_x86':57,'generated_CASE_CODE_B':192,'source_case_x86':57,
  'native_mnemonics_equal':57,'native_widths_equal':37,'native_GPR_roles_equal':expected_gpr,
  'real_PE_fields':verified,'whole_original_callable_exact':False})
 print(action,'native 252B/57 x86 source 192B/57, mnemonics 57/57, width 37/57, GPR',expected_gpr,'/57, actual physical external fields 5/5',flush=True)
# Original immediately following 0x345 is its own 155B/35-x86 handler.
lo,hi=T[35]['local_symbol_offset'],T[36]['local_symbol_offset']
N=[x for x in original_ins if 0x511c8a<=x.address<0x511d25]
S=[x for x in I if lo<=x.address<hi]
assert len(N)==len(S)==35 and all(a.mnemonic==b.mnemonic and role(a)==role(b) for a,b in zip(N,S))
summary={'original_single_whole_boss':'0x0050A580','real_original_whole_CODE_B':81539,'real_original_whole_x86':17435,
 'current_source_partial_whole_CODE_B':end,'current_source_partial_whole_x86':len(I),
 'new_actual_original_fade_cases':len(rows),'new_real_original_state_CODE_B':sum(r['native_CODE_B'] for r in rows),
 'new_real_original_state_x86':sum(r['native_x86'] for r in rows),'original_external_PE_fields_verified':25,
 'original_all_92_jump_DIR32_partition_match':True,'original_all_199_sparse_BYTES_equal':True,
 'following_345_original_x86_GPR_match':35,'not_yet_exact_original_whole':True,
 'new_accepted_exact_whole_CODE_B':0,'mass_cold_replay':False,'cases':rows}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1055 five authentic state interiors, real 1,260 original native CODE B, 285 native x86 and 25 real PE fields recovered as C++; trailing original 0x345 GPR 35/35. The one 81KB whole remains NONEXACT.')
