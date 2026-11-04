#!/usr/bin/env python3
"""F1051: genuine original 0x321 state in the ONE 81KB CharacterObject.

Cold compile only the entire tracked C++ partial-switch parent. Independently
read SHA-pinned Japanese original whole 81KB and compare full 1,048B/229-x86
native state, all real external PE field targets, and following true 0x322
register allocation. Keep the rest-of-switch markers and nonexact full-boss
ownership unambiguously uncredited. No cropped callable or mass cold replay.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import hashlib,importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1051-object321-proof';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1051rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
P=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x0050A580)
assert (boss['size'],boss['instructions'],boss['postret_size'],boss['dense_entries'],boss['sparse_bytes'])==(81539,17435,567,92,199)
raw=rd.pe_bytes_at(P,boss['address'],boss['size'])
assert hashlib.sha256(raw).hexdigest()==boss['sha256']
whole=list(D.disasm(raw,boss['address']))
assert len(whole)==17435 and whole[-1].address+whole[-1].size==boss['address']+boss['size']
assert whole[2].op_str=='esp, 0x3a0' and whole[3].op_str=='dword ptr [ebp - 0xac], ecx'
a,b=0x0050A80F,0x0050AC27
native=[x for x in whole if a<=x.address<b]
assert len(native)==229 and native[0].address==a and native[-1].address+native[-1].size==b
original_dense=rd.pe_bytes_at(P,boss['tables'][0]['dense_addr'],368)
original_sparse=rd.pe_bytes_at(P,boss['tables'][0]['map_addr'],199)
assert hashlib.sha256(original_dense+original_sparse).hexdigest()==boss['postret_sha']
source=R/'probes/CharacterObjectWhole0050A580F1044.cpp'
assert source.read_text().count('#include "CharacterObjectBoss321F1051.inc"')==1
src=(R/'probes/CharacterObjectBoss321F1051.inc').read_text()
assert src.count('case 0x321:')==1 and src.count('g_FighterProbeMarker')==0
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'F1051-entire-partial-parent.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(source),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,text=True,capture_output=True,timeout=380)
(O/'F1051-entire-parent.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(13426,3491,567,433)
table=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
assert len(table)==92 and all(r['offset']==end+4*j and r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None for j,r in enumerate(table))
assert code[end+368:]==original_sparse
original_labels=[int.from_bytes(original_dense[j*4:j*4+4],'little') for j in range(92)]
assert original_labels[1]==a and original_labels[2]==b
assert all((original_labels[j]==original_labels[k])==(table[j]['local_symbol_offset']==table[k]['local_symbol_offset']) for j in range(92) for k in range(92))
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(rx.findall(x.op_str))
lo,hi=table[1]['local_symbol_offset'],table[2]['local_symbol_offset']
S=[x for x in I if lo<=x.address<hi]
assert (hi-lo,len(S))==(813,229)
wrong_m=[j for j,(n,s) in enumerate(zip(native,S)) if n.mnemonic!=s.mnemonic]
wrong_w=[j for j,(n,s) in enumerate(zip(native,S)) if n.size!=s.size]
wrong_g=[j for j,(n,s) in enumerate(zip(native,S)) if role(n)!=role(s)]
assert not wrong_m and not wrong_g
assert len(wrong_w)==77 and {native[j].size-S[j].size for j in wrong_w}=={3,4}
assert sum(native[j].size-S[j].size for j in wrong_w)==1048-813
nonlocal_relocs=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
assert len(nonlocal_relocs)==19
real=[]
for r in nonlocal_relocs:
 assert r['type'] in ('REL32','DIR32') and r['addend']==0
 j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
 d=r['offset']-S[j].address
 x=native[j]
 assert d+4<=x.size
 p=x.address+d
 value=int.from_bytes(rd.pe_bytes_at(P,p,4),'little',signed=r['type']=='REL32')
 target=p+4+value if r['type']=='REL32' else value
 if r['type']=='REL32':assert x.mnemonic=='call' and int(x.op_str,16)==target
 else:assert x.mnemonic in ('fadd','fcomp','fdiv') and f'0x{target:x}' in x.op_str
 match=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
 assert match is not None and int(match.group(1),16)==target,(j,hex(p),r['symbol'],hex(target))
 real.append({'native_original_x86_ordinal':j,'native_original_PE_field':hex(p),'native_original_target':hex(target),'kind':r['type'],'source_symbol':r['symbol']})
assert sum(x['kind']=='REL32' for x in real)==12
assert sum(x['kind']=='DIR32' for x in real)==7
next_N=[x for x in whole if b<=x.address<0x50ad46]
next_lo,next_hi=table[2]['local_symbol_offset'],table[3]['local_symbol_offset']
next_S=[x for x in I if next_lo<=x.address<next_hi]
assert len(next_N)==len(next_S)==56
assert all(x.mnemonic==y.mnemonic and role(x)==role(y) for x,y in zip(next_N,next_S))
summary={'real_original_whole_Boss':'0x0050A580','original_full_whole_CODE_B':81539,'original_whole_x86':17435,'real_321_original_start':'0x0050A80F','real_321_original_end':'0x0050AC27',
 'original_321_native_CODE_B':1048,'original_321_native_x86':229,'current_partial_source_321_CODE_B':813,
 'current_full_partial_parent_CODE_B':end,'current_full_partial_parent_x86':len(I),
 'native_321_mnemonics_equal':229,'native_321_GPR_roles_equal':229,
 'native_321_instruction_widths_equal':229-len(wrong_w),
 'native_321_wrong_width_positions':wrong_w,
 'true_321_original_physical_PE_fields_verified':real,
 'following_322_native_mnemonics_equal':56,'following_322_native_GPR_roles_equal':56,
 'native_92_afterRET_DIR32_equivalence_partition_preserved':True,'native_199_sparse_bytes_preserved':True,
 'whole_game_function_exact':False,'new_accepted_exact_whole_CODE_B':0,'mass_cold_replay':False}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F1051 native entire 0x321: 1048 original CODE B/229 x86; selected C++ 813B/229 x86; exact 229/229 mnemonics +229/229 GPR; 19/19 physical original external PE fields; source width 152/229. Following 0x322 now 56/56 GPR. Whole 81KB STILL NONEXACT.')
