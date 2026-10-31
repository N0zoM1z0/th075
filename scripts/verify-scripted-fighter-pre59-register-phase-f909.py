#!/usr/bin/env python3
"""F909: full original fighter register-phase experiment in REAL preceding action 0x58.

F906 established that 0052327A is the first GPR-role disagreement of
the full 13230-instruction father. Test whether ordinary, semantically
equivalent action-0x58 source grammars perturb the next action's initial
register allocator state. Every candidate compiles a WHOLE original
fighter-shaped normal VC7.1 function. Never claim isolated-case exactness.
"""
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import collections, hashlib, importlib.util, json, os, re, subprocess, sys

R = Path(__file__).resolve().parents[1]
O = R / '.analysis/f909-pre59-register-phase'
O.mkdir(parents=True, exist_ok=True)
BASE = R / '.analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp'
FRAGMENT = R / 'probes/FighterTrajectoryBurst58F614.inc'
RECEIPT = R / '.analysis/f901-fighter-31b/verified-summary.json'
assert BASE.is_file() and FRAGMENT.is_file() and RECEIPT.is_file()
assert json.loads(RECEIPT.read_text())['entire_original_callable_giant_exact'] is False
base, frag = BASE.read_text(), FRAGMENT.read_text()
mark = '#include "FighterTrajectoryBurst58F614.inc"'
assert base.count(mark) == 1 and frag.count('case 0x58:') == 1
variants = {'baseline':frag}
patterns = [
 ('stage0-zero-left','I16(0x62)==0','0==I16(0x62)'),
 ('stage0-zero-negated','I16(0x62)==0','!I16(0x62)'),
 ('stage0-frame-left','I16(0x64)==0','0==I16(0x64)'),
 ('stage0-frame-negated','I16(0x64)==0','!I16(0x64)'),
 ('initial-lvalue','POS = -F32(0x94);','F32(0x50) = -F32(0x94);'),
 ('initial-y-lvalue','I32(0x54) = I32(0x98);','*reinterpret_cast<int*>(RAW+0x54) = I32(0x98);'),
 ('contact-summands','POS54 + POS48 <= g_ThresholdAt0065782C','POS48 + POS54 <= g_ThresholdAt0065782C'),
 ('contact-reverse','POS54 + POS48 <= g_ThresholdAt0065782C','g_ThresholdAt0065782C >= POS54 + POS48'),
 ('contact-negation','POS54 + POS48 <= g_ThresholdAt0065782C','!(POS54 + POS48 > g_ThresholdAt0065782C)'),
 ('counter1-direct','I16(F614_COUNTER)=static_cast<short>(POS*g_ContactProjectionAt00657888);',
     'S16(F614_COUNTER)=static_cast<short>(POS*g_ContactProjectionAt00657888);'),
 ('counter2-direct','I16(F614_COUNTER+2)=static_cast<short>((POS54)*g_ContactProjectionAt00657888);',
     'S16(F614_COUNTER+2)=static_cast<short>((POS54)*g_ContactProjectionAt00657888);'),
 ('counter2-parentheses','((POS54)*g_ContactProjectionAt00657888)',
     '(POS54*g_ContactProjectionAt00657888)'),
 ('burst-postfix','++burst','burst++'),
 ('burst-unsigned','for (int burst=0;','for (unsigned int burst=0;'),
 ('burst-condition','burst<10','10>burst'),
 ('guard-count-left','I16(0xEFA)>25','25<I16(0xEFA)'),
 ('guard-count-negative','I16(0xEFA)>25','!(I16(0xEFA)<=25)'),
 ('get-action-reverse','GetNativeActionAt40FA30()==I16(0x70)',
    'I16(0x70)==GetNativeActionAt40FA30()'),
 ('stage1-left','I16(0x62)==1','1==I16(0x62)'),
 ('stage1-frame-negated','I16(0x64)==0','!I16(0x64)'),
 ('final-test-reversed','POS54 != g_ThresholdAt0065782C','g_ThresholdAt0065782C != POS54'),
 ('final-pos-expression','*(&POS)==g_ThresholdAt0065782C',
    'POS==g_ThresholdAt0065782C'),
]
for name, old, new in patterns:
    assert old in frag, (name,old)
    variants[name] = frag.replace(old,new,1)
# Real coordinated boolean/source alternatives, not dummy reg-phase padding.
for name, labels in (
  ('both-initial-conditions',('stage0-zero-left','stage0-frame-left')),
  ('both-loop-grammar',('burst-unsigned','burst-condition')),
  ('both-counter-lvalue',('counter1-direct','counter2-direct')),
  ('both-final-conditions',('stage1-left','final-test-reversed')),
):
    inc=frag
    for label in labels:
        old,new=next((a,b) for t,a,b in patterns if t==label)
        assert old in inc
        inc=inc.replace(old,new,1)
    variants[name]=inc
spec=importlib.util.spec_from_file_location('f909rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec)
sys.modules[spec.name]=rd
spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32)
native=list(D.disasm(rd.pe_bytes_at(rd.verified_target(),0x5214b0,46755),0x5214b0))
assert len(native)==13230
start=next(i for i,x in enumerate(native) if x.address==0x52327a)
assert start==2103
native59=native[start:start+95]
assert native59[0].address==0x52327a and native59[-1].address+native59[-1].size==0x5233de
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x: tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,inc in variants.items():
    cpp,obj=O/(tag+'.cpp'),O/(tag+'.obj')
    cpp.write_text(base.replace(mark,inc,1))
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=E,capture_output=True,text=True,timeout=345)
    (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
    if cp.returncode:
        row={'variant':tag,'compile_failure':(cp.stdout+cp.stderr)[-400:]}
        rows.append(row);print(json.dumps(row),flush=True);continue
    code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
    instructions=[]
    for x in D.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    end=instructions[-1].address+instructions[-1].size
    row={'variant':tag,'whole_emitted_CODE_B':end,'x86':len(instructions),
         'coff_fields':len(refs),'afterRET_DATA_B':len(code)-end,
         'whole_CODE_SHA256':hashlib.sha256(code[:end]).hexdigest()}
    if len(instructions)==len(native):
        source59=instructions[start:start+95]
        badregs=[i for i,(n,s) in enumerate(zip(native,instructions))
                  if roles(n)!=roles(s)]
        badwidth=[i for i,(n,s) in enumerate(zip(native,instructions))
                  if n.size!=s.size]
        badmnemonics=[i for i,(n,s) in enumerate(zip(native,instructions))
                  if n.mnemonic!=s.mnemonic]
        row.update(first_GPR_difference=badregs[0] if badregs else None,
          total_GPR_differences=len(badregs),
          action59_GPR_differences=sum(roles(n)!=roles(s) for n,s in zip(native59,source59)),
          action59_initial_registers=[roles(x) for x in source59[:3]],
          action59_source_width=sum(x.size for x in source59),
          width_differences=badwidth[:24],width_differences_count=len(badwidth),
          mnemonic_differences=badmnemonics[:12],mnemonic_differences_count=len(badmnemonics),
          true_prefix_same_GPR=sum(roles(n)==roles(s) for n,s in zip(native[:start],instructions[:start])))
    rows.append(row)
    print(json.dumps({k:v for k,v in row.items() if k!='whole_CODE_SHA256'}),flush=True)
assert len(rows)==len(variants)
assert all('compile_failure' not in r for r in rows)
baseline=rows[0]
assert baseline['whole_emitted_CODE_B']==46754 and baseline['x86']==13230
assert baseline['first_GPR_difference']==2103 and baseline['total_GPR_differences']==2736
assert baseline['action59_GPR_differences']==19 and baseline['coff_fields']==1491
assert baseline['afterRET_DATA_B']==901
assert baseline['mnemonic_differences_count']==0 and baseline['width_differences_count']==5
summary={'original_whole_start':'0x005214B0',
 'original_CODE_B':46755,'original_x86':13230,'original_59_start':'0x0052327A',
 'compiler_normal':'VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi',
 'full_source_variants':len(rows),
 'native_59_initial_registers':[roles(x) for x in native59[:3]],
 'same_shape_count':sum(r['x86']==13230 for r in rows),
 'improved_first_GPR_count':sum(r.get('first_GPR_difference',0)>2103 for r in rows if r['x86']==13230),
 'best_father_GPR_count':min(r.get('total_GPR_differences',99999) for r in rows if r['x86']==13230),
 'no_exactness_credit':True,'mass_cold_replay':False,'rows':rows}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F909 complete; variants',len(rows),'phase improvement count',summary['improved_first_GPR_count'],
      'best whole wrong GPR instructions',summary['best_father_GPR_count'])
