#!/usr/bin/env python3
"""F1059 genuine real native 33A action in ONE 81KB original Game Boss.

Build entire current natural C++ partial parent; inspect original pinned whole
81KB PE and 567 afterRET bytes, all authentic switch partition labels and
original 33A physical nonlocal call/global sites. 763B is an INNER state,
never a separate accepted callable; source frame and widths remain NONEXACT.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import hashlib,importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1059-33a-native-original-proof';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1059reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
P=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
manifest=json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
boss=next(x for x in manifest if x['address']==0x50a580)
assert (boss['size'],boss['instructions'],boss['postret_size'],boss['dense_entries'],boss['sparse_bytes'])==(81539,17435,567,92,199)
native_code=rd.pe_bytes_at(P,boss['address'],boss['size']);assert hashlib.sha256(native_code).hexdigest()==boss['sha256']
native_whole=list(D.disasm(native_code,boss['address']));assert len(native_whole)==17435
assert native_whole[2].op_str=='esp, 0x3a0' and native_whole[3].op_str=='dword ptr [ebp - 0xac], ecx'
DATA=rd.pe_bytes_at(P,boss['address']+boss['size'],567)
assert hashlib.sha256(DATA).hexdigest()==boss['postret_sha']
original_dense=[int.from_bytes(DATA[k*4:k*4+4],'little') for k in range(92)]
original_index=DATA[368:]
assert len(original_index)==199 and hashlib.sha256(DATA[:368]).hexdigest()==boss['tables'][0]['dense_sha'] and hashlib.sha256(original_index).hexdigest()==boss['tables'][0]['map_sha']
a,b=0x50ef5f,0x50f25a
native=[x for x in native_whole if a<=x.address<b]
assert len(native)==168 and native[0].address==a and native[-1].address+native[-1].size==b
src=R/'probes/CharacterObjectWhole0050A580F1044.cpp'
assert src.read_text().count('#include "CharacterObjectBoss33AF1059.inc"')==1
source_case=(R/'probes/CharacterObjectBoss33AF1059.inc').read_text()
assert source_case.count('case 0x33A:')==1 and source_case.count('RandomBoundaryAt00455580')==3
assert source_case.count('F1057_FloatAtan2At00483300')==1 and 'g_FighterProbeMarker' not in source_case
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'current-partial-81KB-game.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=380)
(O/'current-partial-game.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(34615,9311,567,852)
assert I[2].op_str=='esp, 0x1dc' and I[3].op_str=='dword ptr [ebp - 0x74], ecx'
table=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
assert len(table)==92 and all(r['offset']==end+4*k and r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None for k,r in enumerate(table))
assert code[end+368:end+567]==original_index
assert all((original_dense[i]==original_dense[j])==(table[i]['local_symbol_offset']==table[j]['local_symbol_offset']) for i in range(92) for j in range(92))
slot=original_index[0x33a-0x320]
assert original_dense[slot]==a and original_dense[slot+1]==b
lo,hi=table[slot]['local_symbol_offset'],table[slot+1]['local_symbol_offset']
S=[x for x in I if lo<=x.address<hi]
assert (hi-lo,len(S))==(610,168)
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(RX.findall(x.op_str))
assert all(x.mnemonic==y.mnemonic and role(x)==role(y) for x,y in zip(native,S))
wd=[i for i,(x,y) in enumerate(zip(native,S)) if x.size!=y.size]
assert len(wd)==51 and sum(native[i].size-S[i].size for i in wd)==763-610
refs_in=sorted((r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None),key=lambda r:r['offset'])
assert len(refs_in)==18
fields=[]
for r in refs_in:
 assert r['type'] in ('REL32','DIR32') and r['addend']==0
 j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
 delta=r['offset']-S[j].address
 assert delta+4<=native[j].size
 p=native[j].address+delta
 v=int.from_bytes(rd.pe_bytes_at(P,p,4),'little',signed=r['type']=='REL32')
 orig_target=p+4+v if r['type']=='REL32' else v
 match=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
 assert match and int(match.group(1),16)==orig_target,(j,r['symbol'],hex(orig_target))
 assert native[j].mnemonic=='call' if r['type']=='REL32' else '0x'+format(orig_target,'x') in native[j].op_str
 fields.append({'original_ordinal':j,'physical_original_PE_field':hex(p),'original_PE_target':hex(orig_target),'original_field_kind':r['type'],'actual_source_COFF_symbol':r['symbol']})
assert sum(x['original_field_kind']=='REL32' for x in fields)==9
assert sum(x['original_field_kind']=='DIR32' for x in fields)==9
# Natural source states immediately following real 33A in same WHOLE
# original compiler GPR cycle. Do NOT credit them as independent functions.
neighbor_cases=[('33b',0x50f25a,0x50f9ce,402),('33c',0x50f9ce,0x50faca,57),
 ('33d',0x50faca,0x51023e,402),('33e',0x51023e,0x51033a,57),
 ('33f',0x51033a,0x510aae,402),('340',0x510aae,0x510baa,57),
 ('341',0x510baa,0x51131e,402),('342',0x51131e,0x51141a,57),
 ('343',0x51141a,0x511b8e,402),('344',0x511b8e,0x511c8a,57),
 ('345',0x511c8a,0x511d25,35)]
following=[]
for state,na,nb,expected in neighbor_cases:
 slot=original_index[int(state,16)-0x320]
 assert original_dense[slot]==na and original_dense[slot+1]==nb
 orig=[x for x in native_whole if na<=x.address<nb]
 src=[x for x in I if table[slot]['local_symbol_offset']<=x.address<table[slot+1]['local_symbol_offset']]
 assert len(orig)==len(src)==expected
 assert all(x.mnemonic==y.mnemonic and role(x)==role(y) for x,y in zip(orig,src)),state
 following.append({'action':state,'native_x86':expected,'original_mnemonics_matching':expected,'original_GPR_roles_matching':expected})
summary={'original_parent':'0x0050A580','original_whole_CODE_B':81539,'native_whole_x86':17435,
 'original_33a_start':'0x0050EF5F','original_33a_end':'0x0050F25A',
 'original_33a_native_CODE_B':763,'native_original_33a_x86':168,
 'source_natural_33a_CODE_B':610,'source_33a_x86':168,
 'original_x86_mnemonics_matching':168,'original_x86_GPR_matching':168,
 'original_x86_widths_matching':168-len(wd),'original_true_external_PE_fields_verified':fields,
 'following_real_case_GPR_phase':following,
 'current_partial_source_CODE_B':end,'current_partial_source_x86':len(I),
 'original_92_afterRET_label_equivalence_preserved':True,'original_199_sparse_map_bytes_preserved':True,
 'original_whole_GAME_callable_exact':False,'newly_accepted_whole_CODE_B':0,'mass_cold_replay':False}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1059: genuine native 33A 763B/168 x86; selected partial C++ 610B/168 x86; 168/168 original mnemonics+GPR, 18/18 physical original PE fields; 11 following real states now 100% original GPR. Whole 81KB remains NONEXACT.')
