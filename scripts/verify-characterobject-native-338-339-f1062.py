#!/usr/bin/env python3
"""F1061/F1062: native real 13-projectile 0x338 and procedural 0x339.

Only full selected original-shaped C++ partial one-switch parent is compiled;
real original whole 81KB/code/afterRET table are read independently. Every
original physical REL32 call and DIR32 global field of both real states
must match the original PE instruction ordinal and physical byte position.
Neither state is a separate exact callable; full 81KB still NONEXACT.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import hashlib,importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1062-native-338-339-proof';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1062rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
P=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==0x0050A580)
assert (boss['size'],boss['instructions'],boss['postret_size'],boss['dense_entries'],boss['sparse_bytes'])==(81539,17435,567,92,199)
whole=rd.pe_bytes_at(P,boss['address'],boss['size']);assert hashlib.sha256(whole).hexdigest()==boss['sha256']
Nwhole=list(D.disasm(whole,boss['address']));assert len(Nwhole)==17435
assert Nwhole[2].op_str=='esp, 0x3a0' and Nwhole[3].op_str=='dword ptr [ebp - 0xac], ecx'
data=rd.pe_bytes_at(P,boss['address']+boss['size'],567)
assert hashlib.sha256(data).hexdigest()==boss['postret_sha']
original_dense=[int.from_bytes(data[i*4:i*4+4],'little') for i in range(92)]
original_sparse=data[368:];assert len(original_sparse)==199
assert hashlib.sha256(data[:368]).hexdigest()==boss['tables'][0]['dense_sha'] and hashlib.sha256(original_sparse).hexdigest()==boss['tables'][0]['map_sha']
src=R/'probes/CharacterObjectWhole0050A580F1044.cpp'
assert src.read_text().count('#include "CharacterObjectBoss338F1062.inc"')==1
assert src.read_text().count('#include "CharacterObjectBoss339F1061.inc"')==1
assert (R/'probes/CharacterObjectBoss338F1062.inc').read_text().count('shot<13')==1
assert (R/'probes/CharacterObjectBoss339F1061.inc').read_text().count('case 0x339:')==1
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'complete-current-one-switch-source.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,text=True,capture_output=True,timeout=385)
(O/'complete-source-VC71.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(38034,10206,567,903)
assert I[2].op_str=='esp, 0x1f8' and I[3].op_str=='dword ptr [ebp - 0x80], ecx'
T=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
assert len(T)==92 and all(r['offset']==end+4*i and r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None for i,r in enumerate(T))
assert code[end+368:]==original_sparse
assert all((original_dense[i]==original_dense[j])==(T[i]['local_symbol_offset']==T[j]['local_symbol_offset']) for i in range(92) for j in range(92))
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(RX.findall(x.op_str))
cases=[('338',0x50ea5b,0x50ed70,789,175,638,12,125,10),
       ('339',0x50ed70,0x50ef5f,495,101,401,10,70,4)]
rows=[]
for label,start,stop,size,count,source_size,physical_fields,source_correct_widths,real_calls in cases:
 ix=original_sparse[int(label,16)-0x320]
 assert original_dense[ix]==start and original_dense[ix+1]==stop
 lo,hi=T[ix]['local_symbol_offset'],T[ix+1]['local_symbol_offset']
 N=[x for x in Nwhole if start<=x.address<stop]
 S=[x for x in I if lo<=x.address<hi]
 assert (len(N),len(S),stop-start,hi-lo)==(count,count,size,source_size)
 assert all(x.mnemonic==y.mnemonic and role(x)==role(y) for x,y in zip(N,S))
 badw=[j for j,(x,y) in enumerate(zip(N,S)) if x.size!=y.size]
 assert count-len(badw)==source_correct_widths and sum(N[j].size-S[j].size for j in badw)==size-source_size
 actual=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
 assert len(actual)==physical_fields
 checked=[]
 for r in actual:
  assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
  j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
  delta=r['offset']-S[j].address;assert delta+4<=N[j].size
  p=N[j].address+delta
  v=int.from_bytes(rd.pe_bytes_at(P,p,4),'little',signed=r['type']=='REL32')
  native_target=p+4+v if r['type']=='REL32' else v
  alias=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
  assert alias and int(alias.group(1),16)==native_target,(label,j,r['symbol'],hex(native_target))
  assert N[j].mnemonic=='call' if r['type']=='REL32' else '0x'+format(native_target,'x') in N[j].op_str
  checked.append({'x86_ordinal':j,'original_PE_field':hex(p),'kind':r['type'],'native_original_target':hex(native_target),'source_symbol':r['symbol']})
 assert sum(x['kind']=='REL32' for x in checked)==real_calls
 assert sum(x['kind']=='DIR32' for x in checked)==physical_fields-real_calls
 rows.append({'action':label,'original_native_CODE_B':size,'source_inner_CODE_B':source_size,
  'original_and_source_x86':count,'original_matching_mnemonics':count,
  'original_matching_GPR_roles':count,'original_matching_widths':source_correct_widths,
  'physical_original_PE_targets_verified':checked,'original_whole_exact':False})
 print(label,'original',size,'B/',count,'x86 source',source_size,'B/',count,'x86; native mnemonic and GPR',count,'/',count,'native width',source_correct_widths,'/',count,'PE fields',len(checked),'/',physical_fields,flush=True)
# These adjacent original state boundaries all remain in the ONE source,
# without splitting original CODE into independent accepted callables.
near=[('33a',0x50ef5f,0x50f25a,168),('33b',0x50f25a,0x50f9ce,402),('33c',0x50f9ce,0x50faca,57),
 ('33d',0x50faca,0x51023e,402),('33e',0x51023e,0x51033a,57),('33f',0x51033a,0x510aae,402),
 ('340',0x510aae,0x510baa,57),('341',0x510baa,0x51131e,402),('342',0x51131e,0x51141a,57),
 ('343',0x51141a,0x511b8e,402),('344',0x511b8e,0x511c8a,57),('345',0x511c8a,0x511d25,35)]
for state,a,b,ns in near:
 ix=original_sparse[int(state,16)-0x320]
 assert original_dense[ix]==a and original_dense[ix+1]==b
 n=[x for x in Nwhole if a<=x.address<b]
 s=[x for x in I if T[ix]['local_symbol_offset']<=x.address<T[ix+1]['local_symbol_offset']]
 assert len(n)==len(s)==ns and all(x.mnemonic==y.mnemonic and role(x)==role(y) for x,y in zip(n,s)),state
summary={'real_whole_original_Boss':'0x0050A580','original_whole_CODE_B':81539,'original_whole_x86':17435,
 'selected_partial_source_whole_CODE_B':end,'selected_partial_source_whole_x86':len(I),
 'original_338_339_combined_native_CODE_B':sum(x['original_native_CODE_B'] for x in rows),
 'original_338_339_combined_native_x86':sum(x['original_and_source_x86'] for x in rows),
 'original_338_339_nonlocal_PE_fields':sum(len(x['physical_original_PE_targets_verified']) for x in rows),
 'native_12_following_states_all_matching_GPR':True,
 'original_afterRET_92_DIR32_equivalence_preserved':True,'original_199_sparse_bytes_equal':True,
 'full_81KB_whole_function_exact':False,'newly_accepted_original_CODE_B':0,'mass_cold_replay':False,
 'cases':rows}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1062: TWO authentic game states 338/339, 1284 original inner CODE B, 276 original x86 mnemonics/GPR and 22 physically correct original PE fields. Following 12 state GPR phases restored. ONE original 81KB whole remains NONEXACT.')
