#!/usr/bin/env python3
"""F1023 independent original PE: 20 complete 82KB C++ sources around
2BC/2BD/2BE/2BF, including genuinely used stage/frame guards,
native boolean grammars, readonly/volatile signed shorts and
the original-borrowed F1022 adjacent script counter view.

Genuine native 82KB 22,721 instruction geometry, frame0x720,
physical 151 DIR32 switch fields +522 afterRET nonreloc bytes.
All 20 regular VC7.1 whole-father candidates are fully compiled
and compared. Local 2BC/2BD/2BE register roles remain wrong
128/125/125; native 2BD's lone source width mismatch remains,
real 2BF stays correct. No whole original game CODE credit
and no all-979-unit cold replay.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1023-third-native-proof';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F1020.cpp').read_text()
frag=(R/'probes/FighterThirdBossStages2BC2BDF1001.inc').read_text()
anchor='#include "FighterThirdBossStages2BC2BDF1001.inc"'
assert base.count(anchor)==1
start='if (S16(0x62)==0 && S16(0x64)==0)'
assert frag.count(start)==2
cases={'strict-original':(frag,False)}
variants={
 'nested-if':'if (S16(0x62)==0) if (S16(0x64)==0)',
 'de-morgan':'if (!(S16(0x62)!=0 || S16(0x64)!=0))',
 'zero-first':'if (0==S16(0x62) && 0==S16(0x64))',
 'not-short':'if (!S16(0x62) && !S16(0x64))',
 'redundant-casts':'if (static_cast<int>(S16(0x62))==0 && static_cast<int>(S16(0x64))==0)',
 'read-only-short':'if (*reinterpret_cast<const signed short*>(RAW+0x62)==0 && *reinterpret_cast<const signed short*>(RAW+0x64)==0)',
 'volatile-short':'if (*reinterpret_cast<volatile signed short*>(RAW+0x62)==0 && *reinterpret_cast<volatile signed short*>(RAW+0x64)==0)',
 'swapped-guards':'if (S16(0x64)==0 && S16(0x62)==0)',
}
for tag,repl in variants.items():
 cases[tag+'-both']=(frag.replace(start,repl),False)
 cases[tag+'-only-2BC']=(frag.replace(start,repl,1),False)
# Three meaningfully different original stores/borrowed owner variants.
cases['borrowed-unsigned-script-word']=(frag.replace('S16(0xF00)=0;','F1022_SCRIPT(this).counterAtF00=0;').replace('S16(0xF02)=0;','F1022_SCRIPT(this).counterAtF02=0;'),True)
cases['reordered-initial-f00']=(frag.replace('''        S16(0xF00)=0;
        I32(0x7C)=1;
        ResetAt453E20();''','''        I32(0x7C)=1;
        S16(0xF00)=0;
        ResetAt453E20();'''),False)
cases['explicit-stage0-scope']=(frag.replace('''    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;''','''    if (S16(0x62)==0 && S16(0x64)==0) {{
        S16(0xF00)=0;''').replace('''        S16(0xF06)=0;
    }
    if (GetNativeActionAt40FA30()''','''        S16(0xF06)=0;
    }}
    if (GetNativeActionAt40FA30()'''),False)
# Fix inserted extra braces only for opening stage0 blocks above:
if 'explicit-stage0-scope' in cases:
 f,_=cases['explicit-stage0-scope']
 assert f.count('{{')==2 and f.count('}}')==2
 cases['explicit-stage0-scope']=(f.replace('{{','{').replace('}}','}'),False)
sp=importlib.util.spec_from_file_location('rd1023',R/'scripts/compare-coff-function.py')
m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m)
D=Cs(CS_ARCH_X86,CS_MODE_32);P=m.verified_target()
N=list(D.disasm(m.pe_bytes_at(P,0x4ac040,82796),0x4ac040))
assert len(N)==22721 and N[2].op_str=='esp, 0x720'
ORIGINAL_AFTER=m.pe_bytes_at(P,0x4ac040+82796,1126)
STATE_FIELDS={'2BC':15,'2BD':15,'2BE':50,'2BF':65}
post=m.pe_bytes_at(P,0x4ac040+82796,1126)
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(rx.findall(i.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,(f,needsheader) in cases.items():
 path=O/(tag+'.inc');path.write_text(f)
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj')
 src=base.replace(anchor,'#include "'+tag+'.inc"',1)
 if needsheader:src='#include "FighterScriptCounterWindowF1022.hpp"\n'+src
 cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=350)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  rows.append({'variant':tag,'compile_error':(cp.stdout+cp.stderr)[-550:]})
  print(tag,'COMPILE ERROR',(cp.stdout+cp.stderr)[-200:],flush=True);continue
 code,refs=m.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 lab={};masked=set()
 tail=[r for r in refs if r['offset']>=end]
 assert len(code)-end==1126 and len(tail)==151
 for r in tail:
  q=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in masked for j in range(q,q+4))
  masked.update(range(q,q+4))
  addr=int.from_bytes(ORIGINAL_AFTER[q:q+4],'little')
  assert 0x4ac040<=addr<0x4ac040+82796
  lab.setdefault(addr,r['local_symbol_offset'])
 assert 1126-len(masked)==522
 assert all(code[end+j]==ORIGINAL_AFTER[j] for j in range(1126) if j not in masked)
 mm=[j for j,(a,b) in enumerate(zip(N,I)) if a.mnemonic!=b.mnemonic]
 ww=[j for j,(a,b) in enumerate(zip(N,I)) if a.size!=b.size]
 gg=[j for j,(a,b) in enumerate(zip(N,I)) if roles(a)!=roles(b)]
 row={'variant':tag,'source_whole_B':end,'source_x86':len(I),'frame':I[2].op_str,
 'whole_wrong_mnem':len(mm),'whole_wrong_width':len(ww),'whole_wrong_GPR':len(gg),
 'cases':{}}
 for key,a,b in [('2BC',0x4bac11,0x4baf04),('2BD',0x4baf04,0x4bb1ea),('2BE',0x4bb1ea,0x4bb831),('2BF',0x4bb831,0x4bc0a8)]:
  S=[x for x in I if lab[a]<=x.address<lab[b]]
  nat=list(D.disasm(m.pe_bytes_at(P,a,b-a),a))
  fields=[r for r in refs if lab[a]<=r['offset']<lab[b]]
  assert len(fields)==STATE_FIELDS[key],(tag,key,len(fields))
  # Compare true PE relocation destination against native ordinal,
  # not shifted/nonexistent source-only relocation locations.
  for r in fields:
   assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
   j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
   delta=r['offset']-S[j].address
   off=nat[j].address-a+delta
   value=int.from_bytes(m.pe_bytes_at(P,a+off,4),'little',signed=r['type']=='REL32')
   actual=nat[j].address+delta+4+value if r['type']=='REL32' else value
   symbol=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
   expected=int(symbol.group(1),16) if symbol else 0x6406ac if r['symbol']=='__ftol2' else None
   assert actual==expected,(tag,key,j,r['symbol'],hex(actual),expected)
  row['cases'][key]={'source_B':sum(x.size for x in S),'source_x86':len(S),
   'bad_mnem':sum(x.mnemonic!=y.mnemonic for x,y in zip(nat,S)),
   'bad_width':sum(x.size!=y.size for x,y in zip(nat,S)),
   'bad_GPR':sum(roles(x)!=roles(y) for x,y in zip(nat,S)),
   'true_original_PE_fields':len(fields)}
 rows.append(row)
 print(tag,'FULL',end,len(I),'wrong M/W/G',len(mm),len(ww),len(gg),
   'native case 2BC/2BD/2BE/2BF',[(k,row['cases'][k]['bad_GPR']) for k in ('2BC','2BD','2BE','2BF')],flush=True)
(O/'results.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==20 and all('compile_error' not in r for r in rows)
assert all(r['source_whole_B']==82796 and r['source_x86']==22721
           and r['frame']=='esp, 0x720' and r['whole_wrong_mnem']==0
           and r['whole_wrong_GPR']==6958 for r in rows)
assert all([r['cases'][k]['bad_GPR'] for k in ('2BC','2BD','2BE','2BF')]
           ==[128,125,125,0] for r in rows)
assert all([r['cases'][k]['true_original_PE_fields'] for k in
            ('2BC','2BD','2BE','2BF')]==[15,15,50,65] for r in rows)
assert sum(r['whole_wrong_width']!=12 for r in rows)==1
assert next(r for r in rows if r['variant']=='reordered-initial-f00')['whole_wrong_width']==16
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_native_fighter':'0x004AC040',
 'original_full_callable_CODE_B':82796,
 'original_full_x86':22721,
 'whole_fathers_freshly_compiled':len(rows),
 'actual_original_2BC_2BD_2BE_2BF_GPR_differences':[128,125,125,0],
 'all_verified_original_PE_fields_per_state':[15,15,50,65],
 'original_2BD_real_wrong_ADD_width_remains':True,
 'original_whole_wrong_widths_best':12,
 'original_whole_wrong_GPR_best':6958,
 'native_151_DIR32_and_522_afterRET_nonfields_checked':True,
 'all_natural_grammar_controls_failed_to_fix_original_GPR_phase':True,
 'whole_original_exact':False,'new_exact_original_CODE_B':0,
 'mass_cold_replay':False,'complete_father_results':rows
},indent=2)+'\n')
print('F1023 twenty actual whole original-shaped normal VC7.1 82KB sources: native 2BC/BD/BE GPR roles 128/125/125 wrong, native2BD ADD width remains; 145 true PE fields per parent verified. All afterRET fields preserved. NO whole original exact.')
