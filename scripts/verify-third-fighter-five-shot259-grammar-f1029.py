#!/usr/bin/env python3
"""F1029: Eight legitimate original 259 angle-arithmetic owner grammars.

Fresh-build EIGHT ENTIRE 82KB original-shaped normal VC7.1
fighter parents from tracked F1020 with only actual signed
script F02/angle arithmetic value categories changed.
Validate native physical original 259 CODE 845B/212 x86,
all 15 PE call/global targets, 151 afterRET DIR32 original
case labels, 522 nonfield DATA B and all 22,721 original
whole mnemonics/widths/GPR roles. All eight remain nonexact:
three native 259 ADD widths and 137 wrong GPR roles. No
cropped case acceptance or corpus-wide 979-unit replay.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys,collections
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1029-original-five-shot-proof';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F1020.cpp').read_text()
frag=(R/'probes/FighterThirdBossFiveShot259F990.inc').read_text()
anchor='#include "FighterThirdBossFiveShot259F990.inc"'
assert base.count(anchor)==1
term='S16(0xF02)*3+'
assert frag.count(term)==5
cases={
 'original-strict':frag,
 'const-borrowed-F02':frag.replace(term,'(*reinterpret_cast<const signed short*>(RAW+0xF02))*3+'),
 'reversed-real-multiply':frag.replace(term,'3*S16(0xF02)+'),
 'explicit-int-read':frag.replace(term,'static_cast<int>(S16(0xF02))*3+'),
 'original-cast-syntax':frag.replace('float(S16(0xF02)*3+','static_cast<float>(S16(0xF02)*3+'),
 'const-short-reference':frag.replace(term,'static_cast<const signed short&>(S16(0xF02))*3+'),
 'typed-index-read':frag.replace(term,'reinterpret_cast<const signed short*>(RAW+0xF02)[0]*3+'),
 'literal-first-angle':frag
}
for amount in (145,140,135,130,125):
 x=f'float(S16(0xF02)*3+{amount})'
 assert cases['literal-first-angle'].count(x)==1
 cases['literal-first-angle']=cases['literal-first-angle'].replace(x,
  f'float({amount}+S16(0xF02)*3)',1)
spec=importlib.util.spec_from_file_location('f1029reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
native=list(D.disasm(rd.pe_bytes_at(PE,0x4ac040,82796),0x4ac040));assert len(native)==22721
original_inner=list(D.disasm(rd.pe_bytes_at(PE,0x4b7ef2,845),0x4b7ef2));assert len(original_inner)==212
original_after=rd.pe_bytes_at(PE,0x4ac040+82796,1126)
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(REG.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,fragment in cases.items():
 assert fragment.count('SpawnFloatXYAt453A70(0x325,')==5
 inc=O/(tag+'.inc');inc.write_text(fragment)
 src=base.replace(anchor,'#include "'+tag+'.inc"',1)
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,text=True,capture_output=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  rows.append({'variant':tag,'compile_error':(cp.stdout+cp.stderr)[-500:]})
  print(tag,'COMPILER FAIL',(cp.stdout+cp.stderr)[-230:],flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for i in D.disasm(code,0):
  I.append(i)
  if i.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 labels={}
 for r in refs:
  if r['offset']>=end:
   off=r['offset']-end;labels.setdefault(int.from_bytes(original_after[off:off+4],'little'),r['local_symbol_offset'])
 lo,hi=labels[0x4b7ef2],labels[0x4b823f]
 seq=[x for x in I if lo<=x.address<hi]
 mm=[j for j,(n,s) in enumerate(zip(original_inner,seq)) if n.mnemonic!=s.mnemonic]
 ww=[j for j,(n,s) in enumerate(zip(original_inner,seq)) if n.size!=s.size]
 gg=[j for j,(n,s) in enumerate(zip(original_inner,seq)) if roles(n)!=roles(s)]
 fullm=[j for j,(n,s) in enumerate(zip(native,I)) if n.mnemonic!=s.mnemonic]
 fullw=[j for j,(n,s) in enumerate(zip(native,I)) if n.size!=s.size]
 fullg=[j for j,(n,s) in enumerate(zip(native,I)) if roles(n)!=roles(s)]
 assert len(code)-end==1126
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 native_after=rd.pe_bytes_at(PE,0x4ac040+82796,1126)
 mask=set()
 for r in table:
  q=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(q,q+4))
  mask.update(range(q,q+4))
  addr=int.from_bytes(native_after[q:q+4],'little')
  assert 0x4ac040<=addr<0x4ac040+82796
 assert 1126-len(mask)==522
 assert all(code[end+j]==native_after[j] for j in range(1126) if j not in mask)
 fields=[r for r in refs if lo<=r['offset']<hi]
 assert len(fields)==15,(tag,len(fields))
 for r in fields:
  j=next(j for j,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
  d=r['offset']-seq[j].address
  o=original_inner[j].address-0x4b7ef2+d
  assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
  value=int.from_bytes(rd.pe_bytes_at(PE,0x4b7ef2+o,4),'little',signed=r['type']=='REL32')
  actual=original_inner[j].address+d+4+value if r['type']=='REL32' else value
  match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
  expected=int(match.group(1),16) if match else 0x6406AC if r['symbol']=='__ftol2' else None
  assert actual==expected,(tag,j,r['symbol'],hex(actual),expected)
 row={'variant':tag,'full_source_B':end,'full_x86':len(I),'source_frame':I[2].op_str,
 'full_mnemonic_diffs':len(fullm),'full_width_diffs':len(fullw),'full_GPR_diffs':len(fullg),
 'source_259_B':hi-lo,'source_259_x86':len(seq),
 'native_259_mnemonic_diff':mm,'native_259_width_diff':ww,
 'native_259_GPR_count':len(gg),
 'native_259_real_CORe_PE_fields':len([r for r in refs if lo<=r['offset']<hi])}
 rows.append(row)
 print(tag,'full',end,len(I),'M/W/G',len(fullm),len(fullw),len(fullg),
  '259 B/x86',hi-lo,len(seq),'wrong width',ww,'GPR',len(gg),flush=True)
(O/'results.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==8 and all('compile_error' not in row for row in rows)
assert all((r['full_source_B'],r['full_x86'],r['source_frame'])==(82796,22721,'esp, 0x720') for r in rows)
assert all((r['full_mnemonic_diffs'],r['full_width_diffs'],r['full_GPR_diffs'])==(0,12,6958) for r in rows)
assert all((r['source_259_B'],r['source_259_x86'],r['native_259_mnemonic_diff'],
            r['native_259_width_diff'],r['native_259_GPR_count'],
            r['native_259_real_CORe_PE_fields'])==(844,212,[],[34,96,127],137,15) for r in rows)
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_Japanese_original_82KB_fighter':'0x004AC040',
 'whole_original_GAME_CODE_B':82796,'whole_original_x86':22721,
 'real_native_259_845B_212x86':True,'actual_259_PE_targets_verified':15,
 'complete_normal_VC71_father_variants':len(rows),
 'all_original_259_mnemonics_match':True,
 'three_original_259_ADD_width_mismatches':[34,96,127],
 'original_259_wrong_GPR_roles':137,
 'whole_original_12_width_6958_GPR_debts_preserved':True,
 'all_151_original_afterRET_DIR32_and_522_nonfield_bytes_verified':True,
 'whole_original_exact':False,'new_accepted_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_source_proof':rows
},indent=2)+'\n')
print('F1029 eight genuine complete 82KB C++ angle expression controls; all 15 actual 259 PE call/global fields, 151 afterRET DIR32+522 DATA verified, no original width/GPR improvement. Whole giant NONEXACT.')
