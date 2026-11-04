#!/usr/bin/env python3
"""F1044 original native 81KB CharacterObject 0x320 source-recovery research.

Compile full authored one-switch C++ prototype with real native 0x320 logic
and 91 still-unimplemented source marker cases. Never equate the prototype or
the 0x320 switch interior with an exact independent original callable.
Check actual whole original PE boundaries, all original switch DATA and six
physical native original call/global targets before comparing case ordinals.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1044-object320-grammars';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/CharacterObjectWhole0050A580F1044.cpp').read_text()
frag=(R/'probes/CharacterObjectBoss320F1044.inc').read_text()
anchor='#include "CharacterObjectBoss320NativeF1045.inc"';assert base.count(anchor)==1
# Keep both real float motion source expressions, the parent gate, all real
# native external API calls, and every original switch handler route.
parent='''    SELF_FIELD(float,0x44) =
        float(SELF_FIELD(signed char,0x66) * 66) +
        PARENT_FIELD(float,0x44);'''
move='    SELF_FIELD(float,0x48) = SELF_FIELD(float,0x48) + SELF_FIELD(float,0x54);'
assert frag.count(parent)==frag.count(move)==1
cases={'baseline-actual-native-320':frag}
variants={
 'commuted-parent':'    SELF_FIELD(float,0x44) = PARENT_FIELD(float,0x44) +\n        float(SELF_FIELD(signed char,0x66) * 66);',
 'borrowed-parent-first':'    float* parentX = &PARENT_FIELD(float,0x44);\n    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) + *parentX;',
 'typed-parent-reference':'    const float& parentX = PARENT_FIELD(float,0x44);\n    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) + parentX;',
 'parent-indexed-float':'    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) +\n        reinterpret_cast<float*>(PARENT)[0x11];',
 'parent-readonly-view':'    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) +\n        *reinterpret_cast<const float*>(PARENT+0x44);',
 'typed-parent-struct':'    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) +\n        reinterpret_cast<const F1044ParentXView*>(PARENT)->xAt44;',
 'typed-parent-struct-commuted':'    SELF_FIELD(float,0x44) = reinterpret_cast<const F1044ParentXView*>(PARENT)->xAt44 +\n        float(SELF_FIELD(signed char,0x66) * 66);',
 'actual-parent-assignment':'    float parentX = PARENT_FIELD(float,0x44);\n    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) + parentX;',
 'explicit-cast-int':'    SELF_FIELD(float,0x44) = float(int(SELF_FIELD(signed char,0x66)) * 66) +\n        PARENT_FIELD(float,0x44);',
 'facing-reversed-multiply':'    SELF_FIELD(float,0x44) = float(66 * SELF_FIELD(signed char,0x66)) +\n        PARENT_FIELD(float,0x44);',
 'no-parent-temporary':'    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) +\n        *reinterpret_cast<float*>(reinterpret_cast<char*>(*reinterpret_cast<char**>(RAW+0xe4))+0x44);',
}
for tag,repl in variants.items():
 x=frag.replace(parent,repl,1)
 if 'typed-parent-struct' in tag:
  x='struct F1044ParentXView { unsigned char observedUnknown[0x44]; float xAt44; };\n'+x
 cases[tag]=x
# Real borrowed parent/actor coordinate forms from F1037 already preserve
# complete original actor frame functions. Test their semantic expression
# effect in the full original-shaped one-switch parent, not an isolated case.
basegood=cases['typed-parent-struct-commuted']
for tag,repl in {
 'good-move-typed-both':'    F1037_POSITION(this).yPosition = F1037_POSITION(this).yPosition + F1037_MOTION(this).yMotion;',
 'good-move-typed-right':'    SELF_FIELD(float,0x48) = SELF_FIELD(float,0x48) + F1037_MOTION(this).yMotion;',
 'good-move-typed-left':'    F1037_POSITION(this).yPosition = F1037_POSITION(this).yPosition + SELF_FIELD(float,0x54);',
 'good-move-pointer-refs':'    SELF_FIELD(float,0x48) = *(&SELF_FIELD(float,0x48)) + *(&SELF_FIELD(float,0x54));',
 'good-move-right-reference':'    SELF_FIELD(float,0x48) = SELF_FIELD(float,0x48) + (*(&SELF_FIELD(float,0x54)));',
 'good-move-left-reference':'    SELF_FIELD(float,0x48) = (*(&SELF_FIELD(float,0x48))) + SELF_FIELD(float,0x54);',
 'good-move-right-const':'    SELF_FIELD(float,0x48) = SELF_FIELD(float,0x48) + static_cast<const float&>(SELF_FIELD(float,0x54));',
 'good-move-left-const':'    SELF_FIELD(float,0x48) = static_cast<const float&>(SELF_FIELD(float,0x48)) + SELF_FIELD(float,0x54);',
 'good-move-typed-macro':'    SELF_FIELD(float,0x48) = F1037_POSITION(this).yPosition + F1037_MOTION(this).yMotion;',
 'good-move-both-reverse':'    F1037_POSITION(this).yPosition = F1037_MOTION(this).yMotion + F1037_POSITION(this).yPosition;',
 'good-move-explicit-float':'    SELF_FIELD(float,0x48) = float(SELF_FIELD(float,0x48) + SELF_FIELD(float,0x54));',
 'good-move-raw-double':'    SELF_FIELD(float,0x48) = (*reinterpret_cast<float*>(RAW+0x48)) + (*reinterpret_cast<float*>(RAW+0x54));',
}.items():cases[tag]=basegood.replace(move,repl,1)
for tag,repl in {
 'good-parent-borrowed-commuted':'    SELF_FIELD(float,0x44) = F1037_POSITION(PARENT).xPosition + float(SELF_FIELD(signed char,0x66) * 66);',
 'good-parent-borrowed-normal':'    SELF_FIELD(float,0x44) = float(SELF_FIELD(signed char,0x66) * 66) + F1037_POSITION(PARENT).xPosition;',
}.items():cases[tag]=frag.replace(parent,repl,1)
cases['native-borrowed-coordinate-both']=(
    frag.replace(parent,
      '    SELF_FIELD(float,0x44) = F1037_POSITION(PARENT).xPosition + float(SELF_FIELD(signed char,0x66) * 66);',1)
    .replace(move,
      '    F1037_POSITION(this).yPosition = F1037_POSITION(this).yPosition + F1037_MOTION(this).yMotion;',1))
for tag,repl in {
 'move-plus-equals':'    SELF_FIELD(float,0x48) += SELF_FIELD(float,0x54);',
 'move-reversed-add':'    SELF_FIELD(float,0x48) = SELF_FIELD(float,0x54) + SELF_FIELD(float,0x48);',
 'move-identity-lvalue':'    SELF_FIELD(float,0x48) = *(&SELF_FIELD(float,0x48)) + SELF_FIELD(float,0x54);',
 'move-readonly-right':'    SELF_FIELD(float,0x48) = SELF_FIELD(float,0x48) + *reinterpret_cast<const float*>(RAW+0x54);',
 'move-typed-macro':'    F1044_Y = F1044_Y + SELF_FIELD(float,0x54);',
 'move-bracket-add':'    SELF_FIELD(float,0x48) = (SELF_FIELD(float,0x48) + SELF_FIELD(float,0x54));',
}.items():cases[tag]=frag.replace(move,repl,1)
sp=importlib.util.spec_from_file_location('f1044reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32);BASE=0x50a580;CODE=81539;AFTER=567
manifest=json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())
boss=next(z for z in manifest['bosses'] if z['address']==BASE)
assert boss['size']==CODE and boss['postret_size']==AFTER and boss['instructions']==17435
original=rd.pe_bytes_at(PE,BASE,CODE)
import hashlib
assert hashlib.sha256(original).hexdigest()==boss['sha256']
N=list(D.disasm(rd.pe_bytes_at(PE,0x50a658,439),0x50a658))
assert len(N)==91 and N[0].address==0x50a658 and N[-1].address+N[-1].size==0x50a80f
native_fields=[]
for j in (16,40,69,74,81,89):
 x=N[j]
 typ='REL32' if x.mnemonic=='call' else 'DIR32'
 if typ=='REL32':
  origfield=x.address+1
  target=int(x.op_str,16)
 else:
  import re
  found=re.search(r'\[0x([0-9a-f]+)\]',x.op_str)
  assert found,(j,x.op_str)
  origfield=x.address+x.size-4
  target=int(found.group(1),16)
 assert int.from_bytes(rd.pe_bytes_at(PE,origfield,4),'little') == ((target-origfield-4)&0xffffffff if typ=='REL32' else target)
 native_fields.append({'ordinal':j,'original_PE_field':origfield,'kind':typ,'native_target':target})
assert [f['native_target'] for f in native_fields]==[0x45b830,0x40fbb0,0x65747c,0x65782c,0x40fa30,0x40fb40]
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(rx.findall(ins.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,inc in cases.items():
 assert inc.count('NativeParentExpiredAt0045B830();')==1
 assert inc.count('SetNativeMotionAt0040FBB0(0,0,0);')==1
 assert inc.count('GetNativeActionAt0040FA30()')==1
 assert inc.count('SetAuxActionAt0040FB40(1)')==1
 (O/(tag+'.inc')).write_text(inc)
 src=base.replace(anchor,'#include "'+tag+'.inc"',1)
 if tag=='move-typed-macro':src=src.replace('#define SELF_FIELD(type,off)', '#define F1044_Y SELF_FIELD(float,0x48)\n#define SELF_FIELD(type,off)',1)
 (O/(tag+'.cpp')).write_text(src)
 obj=O/(tag+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(O/(tag+'.cpp')),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=350)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 row={'variant':tag,'native_81KB_whole_original_CODE_B':CODE,'native_whole_x86':boss['instructions'],'original_whole_exact':False}
 if cp.returncode:
  row['compiler_error']=(cp.stdout+cp.stderr)[-1000:]
  rows.append(row);print(tag,'compile failed',row['compiler_error'][-170:],flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 table=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
 assert len(table)==92 and len(code)-end==AFTER
 assert all(r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None and r['offset']==end+4*j for j,r in enumerate(table))
 native_table=[int.from_bytes(rd.pe_bytes_at(PE,boss['tables'][0]['dense_addr']+4*j,4),'little') for j in range(92)]
 for a in range(92):
  for b in range(92):
   assert (native_table[a]==native_table[b])==(table[a]['local_symbol_offset']==table[b]['local_symbol_offset'])
 original_map=rd.pe_bytes_at(PE,boss['tables'][0]['map_addr'],199)
 assert code[end+368:end+567]==original_map
 lo,hi=table[0]['local_symbol_offset'],table[1]['local_symbol_offset']
 S=[x for x in I if lo<=x.address<hi]
 row.update({'whole_source_CODE_B':end,'source_x86':len(I),'source_afterRET_DIR32':len(table),
  'native_sparse_index_BYTES_equal':199,'source_320_CODE_B':hi-lo,'source_320_x86':len(S),
  'native_320_CODE_B':439,'native_320_x86':91,
  'source_320_external_PE_COFF_fields':len([r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]),
  'native_320_original_PE_fields':6})
 if len(S)==91:
  row.update({'native_320_mnemonic_equal':sum(n.mnemonic==x.mnemonic for n,x in zip(N,S)),
   'native_320_width_equal':sum(n.size==x.size for n,x in zip(N,S)),
   'native_320_GPR_equal':sum(roles(n)==roles(x) for n,x in zip(N,S)),
   'wrong_mnemonic_ordinals':[j for j,(n,x) in enumerate(zip(N,S)) if n.mnemonic!=x.mnemonic],
   'wrong_width_ordinals':[j for j,(n,x) in enumerate(zip(N,S)) if n.size!=x.size]})
 real={r['symbol']:r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None}
 assert len(real)==6,(tag,len(real))
 fields=[]
 for original_field in native_fields:
  addr=original_field['native_target']
  match=[r for r in real.values() if f'At{addr:08X}' in r['symbol'] or (r['symbol']=='__ftol2' and addr==0x6406ac)]
  assert len(match)==1,(tag,hex(addr),list(real))
  r=match[0]
  assert r['type']==original_field['kind'] and r['addend']==0 and r['local_symbol_offset'] is None
  j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
  # This is only an original-ordinal field proof if all previous ordinal
  # boundaries have been recovered. Otherwise report actual debt honestly.
  fields.append({'native_ordinal':original_field['ordinal'], 'source_ordinal':j,
                 'native_original_target':hex(addr),'real_source_symbol':r['symbol'],
                 'original_physical_PE_field':hex(original_field['original_PE_field']),
                 'source_COFF_offset':r['offset'], 'same_real_instruction_ordinal':original_field['ordinal']==j})
 row['native_PE_target_semantics_all_verified']=len(fields)==6
 row['native_320_PE_fields_by_actual_instruction_ordinal']=fields
 rows.append(row)
 print(tag,'prototype whole',end,'source 320',hi-lo,len(S),'native 320 matched',row.get('native_320_mnemonic_equal'),'out of 91','width',row.get('native_320_width_equal'),'fields',len(fields),flush=True)
(O/'verified-summary.json').write_text(json.dumps({'original_CharacterObject_Boss':'0x0050A580','whole_original_CODE_B':CODE,'whole_original_x86':17435,'native_320_actual_PE_start':'0x0050A658','native_320_original_CODE_B':439,'native_320_original_x86':91,'native_original_320_external_targets':native_fields,'all_92_original_switch_label_equivalence_partitions_reverified':True,'all_199_original_index_map_bytes_reverified':True,'whole_original_exact':False,'new_accepted_original_GAME_CODE_B':0,'source_has_non-native_marker_cases':True,'mass_cold_replay':False,'trials':rows},indent=2)+'\n')
assert len(rows)==len(cases) and all('compiler_error' not in x for x in rows)
best=next(x for x in rows if x['variant']=='native-borrowed-coordinate-both')
assert (best['source_320_x86'],best['source_320_CODE_B'],best['native_320_mnemonic_equal'],best['native_320_GPR_equal'],best['native_320_width_equal'])==(91,335,91,91,57)
assert best['source_320_external_PE_COFF_fields']==6
assert all(x['same_real_instruction_ordinal'] for x in best['native_320_PE_fields_by_actual_instruction_ordinal'])
assert (R/'probes/CharacterObjectBoss320NativeF1045.inc').read_text()==cases['native-borrowed-coordinate-both']
selected_cpp=base.replace(anchor,'#include "native-borrowed-coordinate-both.inc"',1)
assert (O/'native-borrowed-coordinate-both.cpp').read_text()==selected_cpp
selected_obj=O/'native-borrowed-coordinate-both.obj'
selected_code,selected_refs=rd.object_function(selected_obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
assert len(selected_code)==35569+567 and len(selected_refs)==865

print('F1044 native CharacterObject 81KB one-switch source expanded with genuine complete 0x320 case, original whole remains mostly placeholder and nonexact.')
