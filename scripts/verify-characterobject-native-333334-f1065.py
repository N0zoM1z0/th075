#!/usr/bin/env python3
"""F1065/F1066: three original 249-x86 game action interiors, ONE nonexact 81KB Boss.

Cold-compile the entire current original-shaped 0050A580 C++ partial parent.
Read original SHA-pinned Japanese whole 81KB PE, check genuine 92 original
DIR32 jump fields/199 sparse bytes and check all original physical call/global
PE destinations by actual x86 ordinal/field. Never claim cropped original case
exactness or count cases as independent original callables.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import hashlib,importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1065-original-333334-proof';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1065rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x50a580)
assert (boss['size'],boss['instructions'],boss['postret_size'],boss['dense_entries'],boss['sparse_bytes'])==(81539,17435,567,92,199)
original=rd.pe_bytes_at(PE,boss['address'],boss['size'])
assert hashlib.sha256(original).hexdigest()==boss['sha256']
Nwhole=list(D.disasm(original,boss['address']))
assert len(Nwhole)==17435 and Nwhole[2].op_str=='esp, 0x3a0' and Nwhole[3].op_str=='dword ptr [ebp - 0xac], ecx'
data=rd.pe_bytes_at(PE,boss['address']+boss['size'],567)
assert hashlib.sha256(data).hexdigest()==boss['postret_sha']
native_labels=[int.from_bytes(data[i*4:i*4+4],'little') for i in range(92)]
native_index=data[368:]
assert len(native_index)==199 and hashlib.sha256(data[:368]).hexdigest()==boss['tables'][0]['dense_sha'] and hashlib.sha256(native_index).hexdigest()==boss['tables'][0]['map_sha']
SRC=R/'probes/CharacterObjectWhole0050A580F1044.cpp'
s=SRC.read_text();frag=(R/'probes/CharacterObjectBoss333334F1065.inc').read_text()
assert frag.count('case F1065_ACTION:')==1 and frag.count('shot<8')==1 and 'g_FighterProbeMarker' not in frag
for st,value in [('333','30.0f'),('334','0.0f'),('336','-30.0f')]:
 assert s.count(f'#define F1065_ACTION 0x{st}\n#define F1066_INITIAL_ANGLE {value}\n#include "CharacterObjectBoss333334F1065.inc"\n#undef F1066_INITIAL_ANGLE\n#undef F1065_ACTION')==1
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'full-current-partial-parent.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(SRC),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=385)
(O/'full-current-partial-parent.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-1200:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(31430,8440,567,797)
assert I[2].op_str=='esp, 0x1b4' and I[3].op_str=='dword ptr [ebp - 0x6c], ecx'
T=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
assert len(T)==92 and all(r['offset']==end+4*i and r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None for i,r in enumerate(T))
assert code[end+368:]==native_index
assert all((native_labels[i]==native_labels[j])==(T[i]['local_symbol_offset']==T[j]['local_symbol_offset']) for i in range(92) for j in range(92))
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(RX.findall(x.op_str))
statuses=[('333',0x50d929,0x50ddcf,1190,955,171),('334',0x50ddcf,0x50e274,1189,954,171),('336',0x50e518,0x50e9c0,1192,957,171)]
rows=[]
for state,a,b,nativesize,sourcesize,expect_widths in statuses:
 slot=native_index[int(state,16)-0x320]
 assert native_labels[slot]==a and native_labels[slot+1]==b
 N=[x for x in Nwhole if a<=x.address<b]
 lo,hi=T[slot]['local_symbol_offset'],T[slot+1]['local_symbol_offset']
 S=[x for x in I if lo<=x.address<hi]
 assert (len(N),len(S),b-a,hi-lo)==(249,249,nativesize,sourcesize)
 assert all(n.mnemonic==s.mnemonic and role(n)==role(s) for n,s in zip(N,S))
 wrong_w=[i for i,(n,s) in enumerate(zip(N,S)) if n.size!=s.size]
 assert len(wrong_w)==249-expect_widths and sum(N[i].size-S[i].size for i in wrong_w)==nativesize-sourcesize
 actual=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
 assert len(actual)==14
 fields=[]
 for r in actual:
  assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
  i=next(i for i,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
  delta=r['offset']-S[i].address
  assert delta+4<=N[i].size
  native_field=N[i].address+delta
  v=int.from_bytes(rd.pe_bytes_at(PE,native_field,4),'little',signed=r['type']=='REL32')
  dest=native_field+4+v if r['type']=='REL32' else v
  alias=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
  assert alias and int(alias.group(1),16)==dest,(state,i,r['symbol'],hex(dest))
  assert N[i].mnemonic=='call' if r['type']=='REL32' else ('0x'+format(dest,'x') in N[i].op_str)
  fields.append({'original_ordinal':i,'original_PE_field':hex(native_field),'kind':r['type'],'PE_destination':hex(dest),'source_symbol':r['symbol']})
 assert sum(f['kind']=='REL32' for f in fields)==10 and sum(f['kind']=='DIR32' for f in fields)==4
 # The ORIGINAL three native motion float immediates are NOT synonyms:
 # 333=+30, 334=0, 336=-30. An earlier source treated 334 as +30,
 # which matched mnemonics/PE field targets but was semantically WRONG.
 expected_imm={'333':'0x41f00000','334':'0','336':'0xc1f00000'}[state]
 assert N[105].mnemonic=='push' and N[105].op_str==expected_imm
 assert S[105].mnemonic=='push' and S[105].op_str==expected_imm,(state,S[105].op_str,expected_imm)
 rows.append({'action':state,'original_native_CODE_B':nativesize,'original_native_x86':249,
              'natural_partial_source_CODE_B':sourcesize,'natural_source_x86':249,
              'original_matching_mnemonics':249,'original_matching_GPR':249,
              'original_matching_instruction_widths':expect_widths,
              'true_original_physical_PE_nonlocal_fields':fields,'one_original_whole_exact':False})
 print(state,'original',nativesize,'B/249 x86 source',sourcesize,'B/249; native mnemonic 249/249, GPR 249/249, width',expect_widths,'/249; physical PE fields 14/14',flush=True)
# Preserve truth about following state and current incomplete compiler phase.
for st,a,b,role_expected in [('335',0x50e274,0x50e518,149),('337',0x50e9c0,0x50ea5b,35),('338',0x50ea5b,0x50ed70,175)]:
 ix=native_index[int(st,16)-0x320]
 N=[x for x in Nwhole if a<=x.address<b]
 S=[x for x in I if T[ix]['local_symbol_offset']<=x.address<T[ix+1]['local_symbol_offset']]
 assert len(N)==len(S)
 assert all(n.mnemonic==s.mnemonic for n,s in zip(N,S))
 assert sum(role(n)==role(s) for n,s in zip(N,S))==role_expected,(st,role_expected)
summary={'original_one_81KB_boss':'0x0050A580','original_whole_CODE_B':81539,'original_whole_x86':17435,
 'source_current_partial_parent_CODE_B':end,'source_partial_parent_x86':len(I),
 'three_real_original_native_game_state_CODE_B':3571,'three_real_original_native_x86':747,
 'three_correct_original_external_PE_target_count':42,
 'following_335_original_GPR_matching':149,
 'following_337_original_GPR_matching':35,
 'following_338_original_GPR_matching':175,
 'original_92_DIR32_jump_partitions_preserved':True,'original_199_sparse_bytes_preserved':True,
 'whole_original_callable_exact':False,'newly_accepted_exact_original_GAME_CODE_B':0,
 'full_979_unit_cold_replay':False,'cases':rows}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1066: authentic 333/334/336 3,571 native original game CODE B/747 original x86; +30/0/-30 physical instruction immediates, all native mnemonics/GPR and 42 physical PE targets verified. Full 81KB original still NONEXACT.')
