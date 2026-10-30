"""F803: 15 full 58KB parents test real 32B native default getter grammar.

Original native default guard 00551598 is 32B/10 x86 and two
genuine PE-targeted calls. Nine parent source variants emit
identical complete current 59236B COFF CODE+DATA while retaining
four actual GPR byte negatives; six alternative normal C++ forms
change true machine code/ABI-like control geometry and are rejected.
No 979-unit cold replay, no whole boss exact credit.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f803-fighter-default-compare';O.mkdir(parents=True,exist_ok=True)
def ld(name,file):
 sp=importlib.util.spec_from_file_location(name,R/file);m=importlib.util.module_from_spec(sp);sys.modules[name]=m;sp.loader.exec_module(m);return m
f781=ld('f803_f781','scripts/verify-fighter-shared-getter-f781.py')
f778=ld('f803_f778','scripts/verify-fighter-native-default-f778.py')
f759=ld('f803_f759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=ld('f803_f762','scripts/verify-fighter-typed-returns-f762.py')
f734=ld('f803_f734','scripts/verify-fighter-eight-round-f734.py')
f777=ld('f803_f777','scripts/verify-fighter-current-register-phases-f777.py')
rd=ld('f803_rd','scripts/compare-coff-function.py')
base,boss=f781.source_for_whole_parent(f778,f759,f762)
marker='#include "FighterNativeDefaultF778.inc"'
assert base.count(marker)==1
original='''default:
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;'''
assert Path('probes/FighterNativeDefaultF778.inc').read_text().count(original)==1
needle='GetNativeActionAt40FA30()==S16(0x70)'
variants={
 'baseline':original,
 'stage-then-getter':original.replace(needle,'S16(0x70)==GetNativeActionAt40FA30()'),
 'compare-const-ref':original.replace(needle,'GetNativeActionAt40FA30()==*(&S16(0x70))'),
 'getter-explicit-short':original.replace(needle,'static_cast<short>(GetNativeActionAt40FA30())==S16(0x70)'),
 'both-cast-int':original.replace(needle,'static_cast<int>(GetNativeActionAt40FA30())==static_cast<int>(S16(0x70))'),
 'rhs-cast-int':original.replace(needle,'GetNativeActionAt40FA30()==static_cast<int>(S16(0x70))'),
 'reference-stage':original.replace(needle,'GetNativeActionAt40FA30()==reinterpret_cast<const BorrowedDefaultStageF803*>(this)->stageAt70'),
 'not-not-equal':original.replace(needle,'!(GetNativeActionAt40FA30()!=S16(0x70))'),
 'sub-zero':original.replace(needle,'GetNativeActionAt40FA30()-S16(0x70)==0'),
 'reverse-sub-zero':original.replace(needle,'S16(0x70)-GetNativeActionAt40FA30()==0'),
 'not-less-or-greater':original.replace(needle,'!(GetNativeActionAt40FA30()<S16(0x70) || GetNativeActionAt40FA30()>S16(0x70))'),
 'if-else-inverted':'''default:
    if (GetNativeActionAt40FA30()!=S16(0x70)) {
    } else {
        SetNativeActionAt40FAC0(0);
    }
    break;''',
 'conditional-statement':'''default:
    (GetNativeActionAt40FA30()==S16(0x70)) ? (SetNativeActionAt40FAC0(0),0) : 0;
    break;''',
 'if-with-scope':'''default: {
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}''',
 'stage-const-ref':original.replace(needle,'GetNativeActionAt40FA30()==static_cast<const signed short&>(S16(0x70))'),
}
declare='''struct BorrowedDefaultStageF803 { char observedBefore70[0x70]; signed short stageAt70; };\n'''
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
true=rd.pe_bytes_at(pe,0x551598,32)
original_inst=list(d.disasm(true,0x551598));assert len(original_inst)==10
rows=[]
baseline_bytes=None
baseline_relocations=None
def normalized(refs):
 return [(r['offset'],r['type'],r['addend'],r['local_symbol_offset'],
          r['symbol'] if r['local_symbol_offset'] is None else '<local-label>')
         for r in refs]
shape_equivalent={'baseline','compare-const-ref','getter-explicit-short',
    'both-cast-int','rhs-cast-int','reference-stage','not-not-equal',
    'if-with-scope','stage-const-ref'}
assert len(variants)==15 and len(shape_equivalent)==9
for name,source in variants.items():
 cpp=O/(name+'.cpp');obj=O/(name+'.obj');cpp.write_text(declare+base.replace(marker,source))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=240)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print(name,'COMPILER ERR',(cp.stdout+cp.stderr)[-600:],flush=True);continue
 code,refs=rd.object_function(obj,f781.SYM)
 if baseline_bytes is None:
  baseline_bytes=code
  baseline_relocations=normalized(refs)
 identical_whole=code==baseline_bytes
 identical_reloc=normalized(refs)==baseline_relocations
 assert identical_whole==identical_reloc if name in shape_equivalent else True
 if name in shape_equivalent:
  assert identical_whole and identical_reloc and len(code)==59236 and len(refs)==1863, name+' original whole native source geometry drift'
 else:
  assert not identical_whole, name+' unexpected original full CODE/DATA matching alternative: audit candidate'
 ins=[]
 for i in d.disasm(code,0):
  ins.append(i)
  if i.mnemonic=='ret':break
 end=ins[-1].address+ins[-1].size
 try:
  mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
  begin=mapping[0x551598]
  selected=[i for i in ins if begin<=i.address<begin+32]
  fields=[r for r in refs if begin<=r['offset']<begin+32]
  mask={j for r in fields for j in range(r['offset']-begin,r['offset']-begin+4)}
  diffs=[j for j in range(32) if j not in mask and true[j]!=code[begin+j]]
  if name in shape_equivalent:
   assert end==58293 and len(ins)==16471 and len(selected)==10 and len(fields)==2 and diffs==[10,12,16,19]
   guard=f781.verify_original_shared_getter(rd,pe,d,code,refs,ins,end)
   assert guard['genuine_native_shared_suffix_PE_calls']==['0x0040FA30','0x0040FAC0','0x0040FA30']
   if name=='baseline':
    for case in (0x58,0x59,0x60,0x61,0x63):
     f777.physical_whole_case(rd,pe,d,code,refs,ins,mapping,case,f777.ORIGINAL[case])
    f759.check_afterret(rd,pe,d,boss,code,refs,ins)
  row={'name':name,'whole_parent_B':end,'x86':len(ins),'relo':len(refs),
       'whole_byte_identical_current_boss':identical_whole,
       'whole_COFF_reloc_identical_current_boss':identical_reloc,
       'native_real_PE_calls_attested_for_current_source':name in shape_equivalent,
       'original_guard_emitted_FIRST_32_byte_mismatches':len(diffs),
       'guard_wrong_offsets':diffs,
       'original_guard_10_x86_equal':len(selected)==10 and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(original_inst,selected)),
       'original_guard_rel_fields':len(fields),
       'guard_first_opcodes':[(x.mnemonic,x.op_str) for x in selected[:8]]}
 except Exception as e:
  row={'name':name,'whole_parent_B':end,'x86':len(ins),'error':str(e)[:200]}
 assert 'error' not in row, name+' entire native mapping failed'
 rows.append(row)
 print(name,'CODE',end,'x86',len(ins),'GUARD_WRONG',row.get('original_guard_emitted_FIRST_32_byte_mismatches'), 'OFF',row.get('guard_wrong_offsets'), 'original_x86',row.get('original_guard_10_x86_equal'),flush=True)
assert len(rows)==15 and sum(r['whole_byte_identical_current_boss'] for r in rows)==9
(O/'verified-summary.json').write_text(json.dumps({
 'original_game_giant':'0x00543210','original_whole_CODE_B':58294,
 'source_whole_CODE_B_best':58293,'actual_native_original_x86':16471,
 'shared_default_original':'0x00551598','original_guard_CODE_B':32,
 'original_guard_native_x86':10,
 'native_original_guard_physically_attested_CALLS':['0x0040FA30','0x0040FAC0'],
 'full_source_compilations':15,
 'whole_source_identical_alternatives':9,
 'full_source_rejected_alternative_CFGs':6,
 'actual_remaining_original_default_GPR_wrong_offsets':[10,12,16,19],
 'original_943B_afterRET_DATA_reverified':True,
 'whole_boss_exact':False,'new_authored_exact_CODE':0,
 'all_cold_unit_replay_run':False,'variants':rows},indent=2)+chr(10))
print('F803 fifteen entire 58KB current boss builds: nine full COFF CODE+DATA identical and two default native PE calls exact, but original default GPR offsets [10,12,16,19] remain wrong. Six alternatives violate native control/length. Zero whole exact credit.',flush=True)
