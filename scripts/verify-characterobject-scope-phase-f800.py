"""F800: prove lexical switch-case braces cannot fix 33KB boss GPR phase.

Eleven full-parent MSVC7.1 builds retain identical *complete*
33731 CODE+DATA compiler output and typed native target relocations,
while original 0x38D/0x38E/0x3E3 still differ in 137 nonfield bytes.
No giant CODE credited, no all-unit cold replay.
"""
from pathlib import Path
import os,sys,subprocess,json,importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];P=R/'.analysis/f800-character-scope';P.mkdir(parents=True,exist_ok=True)
base=(R/'probes/CharacterObjectActionsF572.cpp').read_text()
targets=(0x38B,0x38C,0x38D,0x38E,0x3E3,0x3E4)
def unbrace(s,action):
 start=f'        case 0x{action:X}: {{'
 a=s.index(start)
 b=s.index('        case 0x',a+len(start))
 part=s[a:b]
 if not part.endswith('}\n'):raise ValueError('case does not end brace '+hex(action))
 return s[:a]+part.replace(start,f'        case 0x{action:X}:',1)[:-2]+s[b:]
cases={
 'baseline':(),
 'scope-38C':(0x38C,),
 'scope-38D':(0x38D,),
 'scope-38E':(0x38E,),
 'scope-3E3':(0x3E3,),
 'scope-38B-38C':(0x38B,0x38C),
 'scope-38C-38D':(0x38C,0x38D),
 'scope-38D-38E':(0x38D,0x38E),
 'scope-38C-38D-38E':(0x38C,0x38D,0x38E),
 'scope-38B-38C-38D-38E':(0x38B,0x38C,0x38D,0x38E),
 'scope-3E3-3E4':(0x3E3,0x3E4)
}
sp=importlib.util.spec_from_file_location('f800_rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f800_f593',R/'scripts/verify-characterobject-whole-geometry-f593.py')
f593=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f593;sp.loader.exec_module(f593)
boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x004EBDA0)
tab=boss['tables'][0]
pe=rd.verified_target()
sw=rd.pe_bytes_at(pe,tab['dense_addr'],tab['slots']*4)
idx=rd.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
D=Cs(CS_ARCH_X86,CS_MODE_32);target=rd.pe_bytes_at(rd.verified_target(),0x4ebda0,33731)
N=list(D.disasm(target[:33293],0));assert len(N)==8789
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
baseline_bytes=None
baseline_relocations=None
def normalized(refs):
 return [(r['offset'],r['type'],r['addend'],r['local_symbol_offset'],
          r['symbol'] if r['local_symbol_offset'] is None else '<local-label>')
         for r in refs]
assert len(cases)==11
for name,areas in cases.items():
 s=base
 for a in areas:s=unbrace(s,a)
 cpp=P/(name+'.cpp');obj=P/(name+'.obj');cpp.write_text(s)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],cwd=R,env=E,capture_output=True,text=True,timeout=230)
 (P/(name+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:print(name,'COMPILE_ERR',(cp.stdout+cp.stderr)[-250:],flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ')
 assert len(code)==33731 and len(refs)==682, 'full parent/native relocated DATA size changed'
 fields,source_labels=f593.physical_all_COFF(rd,pe,code,refs,33293,sw,idx)
 assert len(fields)==682 and len(source_labels)==60
 if baseline_bytes is None:
  baseline_bytes=code
  baseline_relocations=normalized(refs)
 else:
  assert code==baseline_bytes, name+' changed entire native-shaped CODE+DATA bytes'
  assert normalized(refs)==baseline_relocations, name+' changed full original COFF relocation identities'
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 row={'case':name,'code':ret,'x86':len(I),'refs':len(refs),'data':len(code)-ret}
 if len(code)==33731 and ret==33293 and len(I)==8789 and len(refs)==682:
  mask={i for r in refs for i in range(r['offset'],r['offset']+4)}
  mismatch=[i for i in range(33731) if i not in mask and target[i]!=code[i]]
  row['wrong_bytes']=len(mismatch)
  row['first_wrong_offset']=hex(mismatch[0]) if mismatch else None
  row['mnemonic_wrong']=[i for i,(a,b) in enumerate(zip(N,I)) if a.mnemonic!=b.mnemonic][:15]
  row['width_wrong']=[i for i,(a,b) in enumerate(zip(N,I)) if a.size!=b.size][:15]
 assert ret==33293 and len(I)==8789 and row['wrong_bytes']==137
 assert row['mnemonic_wrong']==[] and row['width_wrong']==[]
 row['full_33731B_identical_compiler_output_to_baseline']=True
 row['all_682_original_PE_COFF_relocations_attested']=True
 rows.append(row);print(json.dumps(row),flush=True)
assert len(rows)==11
(P/'verified-summary.json').write_text(json.dumps({
 'target':'0x004EBDA0',
 'native_original_callable_CODE_B':33293,
 'native_original_x86':8789,
 'native_original_afterRET_DATA_B':438,
 'whole_original_PE_COFF_fields':682,
 'source_whole_variants_built':len(rows),
 'all_compiled_COFF_sections_byte_identical':True,
 'all_genuine_physical_original_reloc_shapes_identical':True,
 'remaining_nonfield_wrong_bytes_each':137,
 'candidate_results':rows,
 'whole_original_game_function_exact':False,
 'new_accepted_game_CODE_credit':0,
 'all_unit_cold_replay_run':False,
},indent=2)+'\n')
print('F800 eleven 33KB whole-parent VC7.1 compilations are byte-identical across full CODE and 438B afterRET DATA; all 682 genuine PE relocation fields verified. Native 137 GPR bytes remain nonexact; zero credit.',flush=True)
