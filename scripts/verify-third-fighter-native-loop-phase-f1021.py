#!/usr/bin/env python3
"""F1021: 10 original-shaped whole fighter C++ loop/register-phase controls.

Unlike earlier 58KB or incomplete 82KB controls, the genuine
F1020 entire source now has original 82796 CODE B /22721 x86,
native saved this EBP-0x64 and 0x720 frame. Fresh normal
VC7.1 compile of 10 whole variant fathers, varying ONLY
actual native 0x58 ten-shot loop spelling/scope and true
borrowed operand value category. Check pinned original
0x58 469B/135x86 and 0x59 356B/95x86, full native
mnemonic/width/GPR role changes, original afterRET table
151 DIR32+522 nonfield bytes. This is negative experimental
research: selected strict 0x58 source remains unmodified,
and no partial case earns whole original exact CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1021-third-native-loop-proof';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F1020.cpp').read_text()
frag=(R/'probes/FighterTrajectoryBurst58F614.inc').read_text()
anchor='#include "FighterTrajectoryBurst58F614.inc"'
assert base.count(anchor)==1
original_for='''        for (int burst=0;burst<10;++burst)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'''
assert frag.count(original_for)==1
variants={
 'original-strict-for':frag,
 'postinc-while':frag.replace(original_for,'''        int burst=0;
        while (burst++<10)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'''),
 'postinc-for':frag.replace(original_for,'''        int burst=0;
        for (;burst++<10;)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'''),
 'preinc-while':frag.replace(original_for,'''        int burst=0;
        while (++burst<=10)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'''),
 'hoisted-local-for':frag.replace(original_for,'''        int burst;
        for (burst=0;burst<10;++burst)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'''),
 'postfix-iteration-for':frag.replace(original_for,'''        for (int burst=0;burst<10;burst++)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'''),
 'reversed-comparison-for':frag.replace(original_for,'''        for (int burst=0;10>burst;++burst)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'''),
 'scoped-real-for':frag.replace(original_for,'''        {
        for (int burst=0;burst<10;++burst)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
        }'''),
 'readonly-XY-shot-arguments':frag.replace(
   'SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);',
   'SpawnDirectedAt453A70(0x3E4,*reinterpret_cast<const int*>(RAW+0x44),*reinterpret_cast<const int*>(RAW+0x48),1,1);'),
 'typed-real-stage1-POS54':frag.replace('if (POS54 != g_ThresholdAt0065782C)',
                                       'if (F32(0x54) != g_ThresholdAt0065782C)'),
}
assert len(variants)==10
sp=importlib.util.spec_from_file_location('f1021reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIG_B=82796;ORIG_X86=22721;AFTER=1126
original=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIG_B),BASE))
assert len(original)==ORIG_X86 and original[2].op_str=='esp, 0x720'
assert original[4].op_str=='dword ptr [ebp - 0x64], ecx'
assert original[2180].address==0x4ADEFA
original_after=rd.pe_bytes_at(PE,BASE+ORIG_B,AFTER)
states={'58':(0x4ADD25,0x4ADEFA,469,135,17),
        '59':(0x4ADEFA,0x4AE05E,356,95,16)}
native={}
for k,(a,b,sz,nx,nf) in states.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for tag,body in variants.items():
 assert body.count('SpawnDirectedAt453A70(0x3E4,')==1
 suffix='native-58-'+tag
 (O/(suffix+'.inc')).write_text(body)
 cpp=O/(suffix+'.cpp');obj=O/(suffix+'.obj')
 cpp.write_text(base.replace(anchor,'#include "'+suffix+'.inc"',1))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(suffix+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(tag,(cp.stdout+cp.stderr)[-1100:])
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==AFTER
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(q not in mask for q in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(original_after[off:off+4],'little')
  assert BASE<=va<BASE+ORIG_B
  labels.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+j]==original_after[j] for j in range(AFTER) if j not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in states.values())
 mm=[j for j,(n,s) in enumerate(zip(original,I)) if n.mnemonic!=s.mnemonic]
 ww=[j for j,(n,s) in enumerate(zip(original,I)) if n.size!=s.size]
 gg=[j for j,(n,s) in enumerate(zip(original,I)) if roles(n)!=roles(s)]
 row={'variant':tag,'native_whole_GAME_CODE_B':ORIG_B,'native_whole_x86':ORIG_X86,
      'full_source_CODE_B':end,'full_source_x86':len(I),
      'source_frame':I[2].op_str,'source_saved_receiver':I[4].op_str,
      'whole_original_wrong_mnemonics':len(mm),
      'whole_original_wrong_widths':len(ww),
      'whole_original_wrong_GPR_roles':len(gg),
      'original_afterRET_DIR32':151,'original_nonfield_DATA_equal_B':522,
      'original_whole_exact':False,'two_native_cases':{}}
 for k,(a,b,sz,nx,nf) in states.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  n=native[k]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CASE_B':sz,'native_x86':nx,
    'source_B':hi-lo,'source_x86':len(s),
    'wrong_mnemonic_ordinals':[j for j,(x,y) in enumerate(zip(n,s)) if x.mnemonic!=y.mnemonic],
    'wrong_width_ordinals':[j for j,(x,y) in enumerate(zip(n,s)) if x.size!=y.size],
    'wrong_GPR_ordinals':[j for j,(x,y) in enumerate(zip(n,s)) if roles(x)!=roles(y)],
    'compiled_true_PE_field_count':len(fields)}
  assert len(fields)==nf,(tag,k,len(fields),nf)
  row['two_native_cases'][k]=item
 rows[tag]=row
 print(tag,'whole CODE/x86',end,len(I),'wrong mnem/width/GPR',len(mm),len(ww),len(gg),
 'native58 deficits',tuple(len(row['two_native_cases']['58'][z]) for z in ('wrong_mnemonic_ordinals','wrong_width_ordinals','wrong_GPR_ordinals')),
 'native59 GPR errors',len(row['two_native_cases']['59']['wrong_GPR_ordinals']),flush=True)
old=rows['original-strict-for']
assert (old['full_source_CODE_B'],old['full_source_x86'],old['whole_original_wrong_mnemonics'],
        old['whole_original_wrong_widths'],old['whole_original_wrong_GPR_roles'])==(ORIG_B,ORIG_X86,0,12,6958)
assert all(old['two_native_cases']['58'][k]==[] for k in ('wrong_mnemonic_ordinals','wrong_width_ordinals','wrong_GPR_ordinals'))
assert len(old['two_native_cases']['59']['wrong_GPR_ordinals'])==19
for k in ('postinc-while','postinc-for'):
 r=rows[k]
 assert (r['full_source_CODE_B'],r['full_source_x86'],
         r['whole_original_wrong_mnemonics'],r['whole_original_wrong_widths'],
         r['whole_original_wrong_GPR_roles'])==(ORIG_B,ORIG_X86,1,14,6979)
 assert tuple(len(r['two_native_cases']['58'][z]) for z in ('wrong_mnemonic_ordinals','wrong_width_ordinals','wrong_GPR_ordinals'))==(1,2,40)
 assert r['two_native_cases']['59']['wrong_GPR_ordinals']==[]
for k in ('hoisted-local-for','postfix-iteration-for','reversed-comparison-for',
          'scoped-real-for','readonly-XY-shot-arguments'):
 r=rows[k]
 assert (r['full_source_CODE_B'],r['full_source_x86'],r['whole_original_wrong_mnemonics'],
         r['whole_original_wrong_widths'],r['whole_original_wrong_GPR_roles'])==(ORIG_B,ORIG_X86,0,12,6958)
 assert r['two_native_cases']['58']['wrong_mnemonic_ordinals']==r['two_native_cases']['58']['wrong_width_ordinals']==r['two_native_cases']['58']['wrong_GPR_ordinals']==[]
 assert len(r['two_native_cases']['59']['wrong_GPR_ordinals'])==19
q=rows['typed-real-stage1-POS54']
assert (q['full_source_CODE_B'],q['full_source_x86'],q['whole_original_wrong_mnemonics'],
        q['whole_original_wrong_widths'],q['whole_original_wrong_GPR_roles'])==(ORIG_B,ORIG_X86,0,14,6960)
assert len(q['two_native_cases']['58']['wrong_width_ordinals'])==2
assert len(q['two_native_cases']['59']['wrong_GPR_ordinals'])==19
r=rows['preinc-while']
assert (r['full_source_CODE_B'],r['full_source_x86'])==(82794,22720)
assert (r['two_native_cases']['58']['source_B'],r['two_native_cases']['58']['source_x86'])==(467,134)
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_82KB_fighter':'0x004AC040',
 'whole_original_CODE_B':ORIG_B,'whole_original_x86':ORIG_X86,
 'original_frame':'0x720','source_frame':'0x720',
 'native_first_whole_GPR_divergence_address':'0x004ADEFA',
 'strict_0x58_native_B_x86':[469,135],
 'strict_0x59_native_B_x86':[356,95],
 'complete_full_82KB_source_controls_tested':len(rows),
 'strict_58_original_mnemonic_width_GPR_errors':[0,0,0],
 'strict_next_59_original_GPR_errors':19,
 'postincrement_while_58_errors_mnem_width_GPR':[1,2,40],
 'postincrement_while_next_59_GPR_errors':0,
 'whole_wrong_GPR_selected_vs_postincrement':[6958,6979],
 'other_real_scope_borrowed_controls_do_not_repair_phase':True,
 'original_whole_exact':False,'new_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_source_results':rows
},indent=2)+'\n')
print('F1021 10 whole original-shaped 82KB normal VC7.1 controls: no natural grammar aligns native 58 and 59 simultaneously. Strict original 58 remains best; whole giant NONEXACT.')
