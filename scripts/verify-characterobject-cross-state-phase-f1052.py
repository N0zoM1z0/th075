#!/usr/bin/env python3
"""F1052: native 81KB CharacterObject cross-state real-loop GPR controls.

Compile four entire normal C++ partial-parent variants with/without genuine
0x325 3-shot loop and 0x32F action. Counterfactual marker states stay NONNATIVE;
physical PE DATA, real current state code and native whole origins never split
into independent accepted functions. Compare GPR-role phases over actual x86
state ordinals, not isolated cropped obj or forced register tricks.
"""
from pathlib import Path
import hashlib,importlib.util,json,os,re,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1052-object-cross-phase';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/CharacterObjectWhole0050A580F1044.cpp').read_text()
A='#include "CharacterObjectBoss325F1052.inc"'
B='#include "CharacterObjectBoss32FF1052.inc"'
assert base.count(A)==base.count(B)==1
cases={
 'old-both-markers':base.replace(A,'case 0x325: g_FighterProbeMarker = 806; break;',1).replace(B,'case 0x32F: g_FighterProbeMarker = 816; break;',1),
 'only-325-real':base.replace(B,'case 0x32F: g_FighterProbeMarker = 816; break;',1),
 'only-32f-real':base.replace(A,'case 0x325: g_FighterProbeMarker = 806; break;',1),
 'both-original-states':base,
}
sp=importlib.util.spec_from_file_location('f1052reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
P=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x0050A580)
raw=rd.pe_bytes_at(P,boss['address'],boss['size'])
assert hashlib.sha256(raw).hexdigest()==boss['sha256']
assert (boss['instructions'],boss['postret_size'])==(17435,567)
base_native=list(D.disasm(raw,boss['address']))
assert len(base_native)==17435
orig_data=rd.pe_bytes_at(P,boss['address']+boss['size'],567)
assert hashlib.sha256(orig_data).hexdigest()==boss['postret_sha']
original_dense=[int.from_bytes(orig_data[i*4:i*4+4],'little') for i in range(92)]
original_sparse=orig_data[368:]
assert len(original_sparse)==199
labels={'320':(0,0x0050A658,0x0050A80F),
 '321':(1,0x0050A80F,0x0050AC27),
 '322':(2,0x0050AC27,0x0050AD46),
 '325':(5,0x0050B654,0x0050B821),
 '32b':(9,0x0050CCC3,0x0050CD7A),
 '32c':(10,0x0050CD7A,0x0050CE97),
 '32d':(11,0x0050CE97,0x0050CF7A),
 '32e':(12,0x0050CF7A,0x0050D097),
 '32f':(13,0x0050D097,0x0050D17A),
 '332':(16,0x0050D88E,0x0050D929)}
for name,(index,st,sp) in labels.items():
 assert original_dense[index]==st and original_dense[index+1]==sp
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for tag,cpp in cases.items():
 source=O/(tag+'.cpp');obj=O/(tag+'.obj');source.write_text(cpp)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(source),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=350)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(tag,(cp.stdout+cp.stderr)[-900:])
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 T=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
 assert len(code)-end==567 and len(T)==92 and code[end+368:]==original_sparse
 assert all(r['type']=='DIR32' and r['offset']==end+4*j and r['addend']==0 and r['local_symbol_offset'] is not None for j,r in enumerate(T))
 assert all((original_dense[j]==original_dense[k])==(T[j]['local_symbol_offset']==T[k]['local_symbol_offset']) for j in range(92) for k in range(92))
 row={'source_whole_partial_CODE_B':end,'source_whole_x86':len(I),'source_all_COFF_fields':len(refs),'preserved_original_92_DIR32':True,'preserved_original_199_sparse_BYTES':True,'GPR_matching_ordinal_counts':{},'x86_in_case':{},'new_original_whole_exact':False}
 for name,(ix,start,stop) in labels.items():
  native=[x for x in base_native if start<=x.address<stop]
  src=[x for x in I if T[ix]['local_symbol_offset']<=x.address<T[ix+1]['local_symbol_offset']]
  row['x86_in_case'][name]=len(src)
  if (name=='325' and tag in ('old-both-markers','only-32f-real')) or (name=='32f' and tag in ('old-both-markers','only-325-real')):
   continue
  assert len(native)==len(src),(tag,name,len(native),len(src))
  row['GPR_matching_ordinal_counts'][name]=sum(roles(n)==roles(s) for n,s in zip(native,src))
  assert all(n.mnemonic==s.mnemonic for n,s in zip(native,src)),(tag,name)
 rows[tag]=row
 print(tag,'whole partial CODE',end,'x86',len(I),'tracked actual GPR roles',row['GPR_matching_ordinal_counts'],flush=True)
(O/'verified-summary.json').write_text(json.dumps({'native_original_whole_CODE_B':81539,'native_original_whole_x86':17435,'native_afterRET_DIR32':92,'native_afterRET_sparse_B':199,
 'current_source_whole_function_exact':False,'new_exact_original_GAME_CODE_B':0,'all_unit_cold_replay':False,
 'full_current_partial_parent_4_variants':rows},indent=2)+'\n')
assert len(rows)==4 and rows['both-original-states']['GPR_matching_ordinal_counts']=={name:len([x for x in base_native if st<=x.address<stop]) for name,(index,st,stop) in labels.items()}
print('F1052 real 0x325 and 0x32F whole-source phase experiment complete; original 81KB still NONEXACT.')
