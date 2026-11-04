#!/usr/bin/env python3
"""F1057: five true 1,908B/402-x86 game action interiors of ONE 81KB Boss.

Pinned actual Japanese original PE and whole C++ parent are separately checked;
all 5*33 physical original external fields use original x86 ordinal and native
PE target bytes. True independent C++ per-action loop temporaries and next
sprite differ, never promote switch case interiors to exact callable code.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import collections,hashlib,importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1057-five-long-native';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f1057rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
B=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x0050A580)
assert (B['size'],B['instructions'],B['postret_size'],B['dense_entries'],B['sparse_bytes'])==(81539,17435,567,92,199)
whole=rd.pe_bytes_at(PE,B['address'],B['size']);assert hashlib.sha256(whole).hexdigest()==B['sha256']
NWHOLE=list(D.disasm(whole,B['address']));assert len(NWHOLE)==17435
assert NWHOLE[2].op_str=='esp, 0x3a0' and NWHOLE[3].op_str=='dword ptr [ebp - 0xac], ecx'
after=rd.pe_bytes_at(PE,B['address']+B['size'],567)
assert hashlib.sha256(after).hexdigest()==B['postret_sha']
original_dense=[int.from_bytes(after[i*4:i*4+4],'little') for i in range(92)]
original_map=after[368:];assert len(original_map)==199
assert hashlib.sha256(after[:368]).hexdigest()==B['tables'][0]['dense_sha']
assert hashlib.sha256(original_map).hexdigest()==B['tables'][0]['map_sha']
base=(R/'probes/CharacterObjectWhole0050A580F1044.cpp').read_text()
fragment=(R/'probes/CharacterObjectBossLongF1057.inc').read_text()
assert fragment.count('case F1057_CASE:')==1 and fragment.count('F1057_NEXT_CASE')==1
assert fragment.count('F1057_FloatAtan2At00483300')==1 and fragment.count('g_F1055_FadeScaleAt006598A4')==2
cases=[('33b',0x50f25a,0x50f9ce,0x33c,1547,282),('33d',0x50faca,0x51023e,0x33e,1547,282),
 ('33f',0x51033a,0x510aae,0x340,1547,282),('341',0x510baa,0x51131e,0x342,1547,282),
 ('343',0x51141a,0x511b8e,0x344,1547,282)]
for action,st,stop,next_action,expectlen,widths in cases:
 src=(f'#define F1057_CASE 0x{action.upper()}\n#define F1057_NEXT_CASE 0x{next_action:X}\n'
  '#include "CharacterObjectBossLongF1057.inc"\n#undef F1057_NEXT_CASE\n#undef F1057_CASE')
 assert base.count(src)==1,action
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'F1057-current-complete-parent-probe.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(R/'probes/CharacterObjectWhole0050A580F1044.cpp'),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,capture_output=True,text=True,env=E,timeout=375)
(O/'F1057-current-parent.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(29479,7928,567,763)
assert I[2].op_str=='esp, 0x194' and I[3].op_str=='dword ptr [ebp - 0x64], ecx'
T=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
assert len(T)==92 and all(r['type']=='DIR32' and r['offset']==end+4*j and r['addend']==0 and r['local_symbol_offset'] is not None for j,r in enumerate(T))
assert code[end+368:]==original_map
assert all((original_dense[i]==original_dense[j])==(T[i]['local_symbol_offset']==T[j]['local_symbol_offset']) for i in range(92) for j in range(92))
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
previous=None;rows=[]
for action,start,stop,next_action,expectlen,expected_width in cases:
 slot=original_map[int(action,16)-0x320]
 assert original_dense[slot]==start and original_dense[slot+1]==stop
 lo,hi=T[slot]['local_symbol_offset'],T[slot+1]['local_symbol_offset']
 orig=[x for x in NWHOLE if start<=x.address<stop]
 S=[x for x in I if lo<=x.address<hi]
 assert (len(orig),len(S),stop-start,hi-lo)==(402,402,1908,expectlen)
 badm=[j for j,(n,s) in enumerate(zip(orig,S)) if n.mnemonic!=s.mnemonic]
 badw=[j for j,(n,s) in enumerate(zip(orig,S)) if n.size!=s.size]
 badg=[j for j,(n,s) in enumerate(zip(orig,S)) if roles(n)!=roles(s)]
 assert not badm and not badg and 402-len(badw)==expected_width
 if previous is not None:
  baseins=previous
  assert all(n.mnemonic==x.mnemonic and n.size==x.size and roles(n)==roles(x) for n,x in zip(baseins,orig))
  uncommon=[j for j,(n,x) in enumerate(zip(baseins,orig)) if n.op_str!=x.op_str and n.mnemonic not in ('je','jne','jg','jge','jle','jl','jp','jnp','jmp','call')]
  assert len(uncommon)==15 and uncommon[10]==227
  assert orig[227].op_str==hex(next_action),(action,orig[227].op_str,hex(next_action))
 else:previous=orig
 actual=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
 assert len(actual)==33
 fields=[]
 for r in actual:
  assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
  j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
  delta=r['offset']-S[j].address;field=orig[j].address+delta
  assert delta+4<=orig[j].size,(action,j,delta,r,orig[j].mnemonic,orig[j].op_str,S[j].mnemonic,S[j].op_str)
  v=int.from_bytes(rd.pe_bytes_at(PE,field,4),'little',signed=r['type']=='REL32')
  native_target=field+4+v if r['type']=='REL32' else v
  match=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
  expected=int(match.group(1),16) if match else 0x6406ac if r['symbol']=='__ftol2' else None
  assert expected is not None and expected==native_target,(action,j,r['symbol'],hex(native_target))
  assert orig[j].mnemonic=='call' if r['type']=='REL32' else ('0x'+format(native_target,'x') in orig[j].op_str)
  fields.append({'ordinal':j,'physical_original_PE_va':hex(field),'original_target':hex(native_target),'kind':r['type'],'source_symbol':r['symbol']})
 assert sum(x['kind']=='REL32' for x in fields)==17 and sum(x['kind']=='DIR32' for x in fields)==16
 rows.append({'action':action,'original_native_interior_CODE_B':stop-start,'original_native_x86':402,
  'source_compiled_inner_CODE_B':hi-lo,'source_compiled_inner_x86':len(S),
  'native_mnemonics_equal':402,'native_widths_equal':expected_width,
  'native_GPR_roles_equal':402,'real_original_PE_external_fields':fields,
  'original_entire_whole_Boss_exact':False})
 print(action,'original 1908B/402 x86, source',hi-lo,'B/402 x86; native mnemonic 402/402, width',expected_width,'/402, GPR 402/402; true original external fields 33/33',flush=True)
assert sum(r['original_native_interior_CODE_B'] for r in rows)==9540
assert sum(len(r['real_original_PE_external_fields']) for r in rows)==165
(O/'verified-summary.json').write_text(json.dumps({'native_one_original_Boss':'0x0050A580',
 'whole_original_CODE_B':81539,'whole_original_x86':17435,'current_partial_source_CODE_B':end,'current_partial_source_x86':len(I),
 'actual_5_recovered_long_action_original_CODE_B':9540,'actual_5_recovered_long_action_original_x86':2010,
 'physical_actual_original_PE_call_global_fields_verified':165,
 'afterRET_original_92_DIR32_partition_preserved':True,'afterRET_original_199_literal_sparse_bytes_equal':True,
 'whole_original_GAME_function_exact':False,'new_accepted_exact_original_CODE_B':0,'mass_cold_replay':False,'cases':rows},indent=2)+'\n')
print('F1057 genuine native original five 1908B action cases: 2010/2010 mnemonic ordinals and 165/165 physical original typed PE fields verified. Full 81KB game callable remains NONEXACT.')
