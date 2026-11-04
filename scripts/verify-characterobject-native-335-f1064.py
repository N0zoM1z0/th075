#!/usr/bin/env python3
"""F1064: real 676B/149-x86 action 335 in ONE nonexact 81KB game Boss.

Cold compile the entire current original-shaped partial C++ parent; re-read
pinned Japanese full 81KB game PE and all genuine 92+199 afterRET DATA.
Audit native mnemonic/width/GPR plus 12 real physically located external PE
fields with actual ordinal and native target; following GPR phase is audited.
No independent case callable or new exact GAME byte credit is claimed.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import hashlib,importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1064-original-335-proof';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1064read',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x50a580)
assert (boss['size'],boss['instructions'],boss['postret_size'],boss['dense_entries'],boss['sparse_bytes'])==(81539,17435,567,92,199)
original=rd.pe_bytes_at(PE,boss['address'],boss['size']);assert hashlib.sha256(original).hexdigest()==boss['sha256']
original_x86=list(D.disasm(original,boss['address']));assert len(original_x86)==17435
assert original_x86[2].op_str=='esp, 0x3a0' and original_x86[3].op_str=='dword ptr [ebp - 0xac], ecx'
original_data=rd.pe_bytes_at(PE,boss['address']+boss['size'],567)
assert hashlib.sha256(original_data).hexdigest()==boss['postret_sha']
native_label=[int.from_bytes(original_data[j*4:j*4+4],'little') for j in range(92)]
native_sparse=original_data[368:]
assert len(native_sparse)==199 and hashlib.sha256(original_data[:368]).hexdigest()==boss['tables'][0]['dense_sha'] and hashlib.sha256(native_sparse).hexdigest()==boss['tables'][0]['map_sha']
src=R/'probes/CharacterObjectWhole0050A580F1044.cpp'
assert src.read_text().count('#include "CharacterObjectBoss335F1064.inc"')==1
frag=(R/'probes/CharacterObjectBoss335F1064.inc').read_text()
assert frag.count('case 0x335:')==1 and frag.count('shot<4')==1 and frag.count('g_FighterProbeMarker')==0
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'current-whole-partial-Cpp.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,text=True,capture_output=True,timeout=360)
(O/'current-whole-partial-Cpp.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(29479,7928,567,763)
assert I[2].op_str=='esp, 0x194' and I[3].op_str=='dword ptr [ebp - 0x64], ecx'
T=sorted((r for r in refs if r['offset']>=end),key=lambda r:r['offset'])
assert len(T)==92 and all(r['type']=='DIR32' and r['offset']==end+4*j and r['addend']==0 and r['local_symbol_offset'] is not None for j,r in enumerate(T))
assert code[end+368:]==native_sparse
assert all((native_label[i]==native_label[j])==(T[i]['local_symbol_offset']==T[j]['local_symbol_offset']) for i in range(92) for j in range(92))
start,stop=0x50e274,0x50e518
slot=native_sparse[0x335-0x320];assert native_label[slot]==start and native_label[slot+1]==stop
N=[x for x in original_x86 if start<=x.address<stop]
lo,hi=T[slot]['local_symbol_offset'],T[slot+1]['local_symbol_offset']
S=[x for x in I if lo<=x.address<hi]
assert (len(N),len(S),stop-start,hi-lo)==(149,149,676,542)
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
assert all(x.mnemonic==y.mnemonic for x,y in zip(N,S))
wrong_w=[j for j,(x,y) in enumerate(zip(N,S)) if x.size!=y.size]
wrong_g=[j for j,(x,y) in enumerate(zip(N,S)) if roles(x)!=roles(y)]
assert len(wrong_w)==44 and len(wrong_g)==0
assert sum(N[j].size-S[j].size for j in wrong_w)==676-542
real=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
assert len(real)==12
proof=[]
for r in real:
 assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
 j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
 d=r['offset']-S[j].address
 assert d+4<=N[j].size
 field=N[j].address+d
 v=int.from_bytes(rd.pe_bytes_at(PE,field,4),'little',signed=r['type']=='REL32')
 native_target=field+4+v if r['type']=='REL32' else v
 m=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
 assert m and int(m.group(1),16)==native_target,(j,r['symbol'],hex(native_target))
 assert N[j].mnemonic=='call' if r['type']=='REL32' else ('0x'+format(native_target,'x') in N[j].op_str)
 proof.append({'original_native_x86_ordinal':j,'original_PE_field_va':hex(field),'original_PE_target':hex(native_target),'native_field_kind':r['type'],'real_COFF_source_symbol':r['symbol']})
assert sum(x['native_field_kind']=='REL32' for x in proof)==8
assert sum(x['native_field_kind']=='DIR32' for x in proof)==4
# No faked good source phase: check genuinely recovered following originals.
following=[('337',0x50e9c0,0x50ea5b,35),('338',0x50ea5b,0x50ed70,175),
 ('339',0x50ed70,0x50ef5f,101),('33a',0x50ef5f,0x50f25a,168),
 ('33b',0x50f25a,0x50f9ce,402),('345',0x511c8a,0x511d25,35)]
for name,a,b,count in following:
 ix=native_sparse[int(name,16)-0x320];assert native_label[ix]==a and native_label[ix+1]==b
 na=[x for x in original_x86 if a<=x.address<b]
 so=[x for x in I if T[ix]['local_symbol_offset']<=x.address<T[ix+1]['local_symbol_offset']]
 assert len(na)==len(so)==count
 assert all(x.mnemonic==y.mnemonic and roles(x)==roles(y) for x,y in zip(na,so)),name
summary={'original_whole_game':'0x0050A580','original_whole_CODE_B':81539,'original_whole_x86':17435,
 'original_335_native_interval':['0x0050E274','0x0050E518'],'original_335_native_CODE_B':676,'native_335_x86':149,
 'current_partial_source_case_CODE_B':542,'source_335_x86':149,'original_matching_mnemonics':149,
 'original_matching_widths':149-len(wrong_w),'original_matching_GPR_roles':149-len(wrong_g),
 'original_physical_PE_fields_verified':proof,'original_92_DIR32_switch_partitions_identical':True,
 'original_199_sparse_map_bytes_identical':True,'selected_partial_parent_CODE_B':end,
 'selected_partial_parent_x86':len(I),'following_real_six_states_all_GPR_equal':True,
 'whole_original_GAME_callable_exact':False,'new_accepted_original_CODE_B':0,'mass_cold_replay':False}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1064 real native 0x335: original 676B/149 x86, selected inner source 542B/149 x86; native 149/149 mnemonic+GPR, 105/149 width; 12/12 true original PE external fields. Following six real state GPR phases all preserved. Whole 81KB still NONEXACT.')
