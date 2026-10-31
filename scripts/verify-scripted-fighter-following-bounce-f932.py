#!/usr/bin/env python3
"""F932: source-loop register phase independently reproduces in 46KB giant.

Regenerate original F901 full-parent source, compile the original
native-shaped 32-bit for loop and genuine 32-bit postincrement-while
alternative. Check all 13230 whole x86, original 0x58/0x59 extents,
the 16 target-backed original native PE relocations, 0x59 GPR and
nonfield operands, two true shared-exit tail JMPs, and the unchanged
901B separate switch DATA. NONE is a whole callable exact match.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,os,sys,json,subprocess,re

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f932-scripted-next-bounce';O.mkdir(parents=True,exist_ok=True)
def load(tag,file):
 sp=importlib.util.spec_from_file_location(tag,R/file)
 m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m)
 return m
f901=load('f932source','scripts/verify-scripted-fighter-tail31b-31c-f901.py')
rd=load('f932rd','scripts/compare-coff-function.py')
full=f901.source()
mark='#include "FighterTrajectoryBurst58F614.inc"'
frag=(R/'probes/FighterTrajectoryBurst58F614.inc').read_text()
actual=('for (int burst=0;burst<10;++burst)\n'
       '            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);')
post=('int burst=0;\n'
      '        while (burst++<10) {\n'
      '            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);\n'
      '        }')
assert full.count(mark)==1 and frag.count(actual)==1
D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
N=list(D.disasm(rd.pe_bytes_at(pe,0x5214b0,46755),0x5214b0))
assert len(N)==13230 and N[-1].address+N[-1].size==0x52cb53
f58=next(i for i,x in enumerate(N) if x.address==0x5230a5)
f59=next(i for i,x in enumerate(N) if x.address==0x52327a)
assert (f58,f59)==(1968,2103)
assert N[f59].address-N[f58].address==469
actual59=list(D.disasm(rd.pe_bytes_at(pe,0x52327a,356),0x52327a))
assert len(actual59)==95 and actual59[-1].address+actual59[-1].size==0x5233de
assert sum(x.mnemonic=='jmp' and x.op_str=='0x52cb4f' for x in actual59)==2
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
summary={}
baseline=None
for label,fragment in [('original-for',frag),
                       ('postincrement-while',frag.replace(actual,post,1))]:
 cpp=O/(label+'.cpp');obj=O/(label+'.obj')
 cpp.write_text(full.replace(mark,fragment,1))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
     cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert (ret,len(I),len(refs),len(code)-ret)==(46754,13230,1491,901)
 assert I[f58].address==N[f58].address-0x5214b0
 assert I[f59].address==N[f59].address-0x5214b0
 assert I[f59].address-I[f58].address==469
 original58=N[f58:f59];source58=I[f58:f59]
 assert len(original58)==len(source58)==135
 bad58m=[j for j,(n,s) in enumerate(zip(original58,source58)) if n.mnemonic!=s.mnemonic]
 bad58w=[j for j,(n,s) in enumerate(zip(original58,source58)) if n.size!=s.size]
 current59=I[f59:f59+95]
 assert current59[-1].address+current59[-1].size-current59[0].address==356
 bad59r=[j for j,(n,s) in enumerate(zip(actual59,current59)) if role(n)!=role(s)]
 bad59m=[j for j,(n,s) in enumerate(zip(actual59,current59)) if n.mnemonic!=s.mnemonic]
 bad59w=[j for j,(n,s) in enumerate(zip(actual59,current59)) if n.size!=s.size]
 assert not bad59m and not bad59w
 source_fields=[r for r in refs if current59[0].address<=r['offset']<current59[-1].address+current59[-1].size]
 assert len(source_fields)==16
 mask=set()
 target_records=[]
 native_bytes=rd.pe_bytes_at(pe,0x52327a,356)
 for r in source_fields:
  owner=next(i for i,x in enumerate(current59) if x.address<=r['offset']<x.address+x.size)
  delta=r['offset']-current59[owner].address
  original_field_offset=actual59[owner].address-0x52327a+delta
  assert (r['addend'],r['local_symbol_offset'])==(0,None) and r['type'] in ('DIR32','REL32')
  assert original_field_offset==r['offset']-current59[0].address
  assert all(k not in mask for k in range(original_field_offset,original_field_offset+4))
  mask.update(range(original_field_offset,original_field_offset+4))
  val=int.from_bytes(native_bytes[original_field_offset:original_field_offset+4],
    'little',signed=r['type']=='REL32')
  target=(actual59[owner].address+delta+4+val if r['type']=='REL32' else val)
  m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
  expected=int(m.group(1),16) if m else 0x6406ac if r['symbol']=='__ftol2' else None
  assert target==expected,(label,owner,r['symbol'],target)
  target_records.append((owner,r['offset'],target))
 # Only two native original external direct jumps to common
 # epilogue 52CB4F are excluded from relative nonfield comparison.
 # The source reaches the same epilogue via the actual late
 # shared-exit JMP at compiled end-14, not an arbitrary destination.
 external=set();count=0
 for j,(n,s) in enumerate(zip(actual59,current59)):
  if n.mnemonic=='jmp' and n.op_str=='0x52cb4f':
   assert s.mnemonic=='jmp' and s.size==n.size==5
   address=int(s.op_str,16)
   entry=next((x for x in I if x.address==address),None)
   assert entry and entry.mnemonic=='jmp' and int(entry.op_str,16)==ret-4
   external.update(range(n.address-0x52327a+1,n.address-0x52327a+5))
   count+=1
 assert count==2
 wrong=[k for k in range(356) if k not in mask and k not in external and
        native_bytes[k]!=code[current59[0].address+k]]
 allwrong=[j for j,(n,s) in enumerate(zip(N,I)) if role(n)!=role(s)]
 widths=[j for j,(n,s) in enumerate(zip(N,I)) if n.size!=s.size]
 wrongm=[j for j,(n,s) in enumerate(zip(N,I)) if n.mnemonic!=s.mnemonic]
 if baseline is None:baseline=(code,refs,ret)
 else:
  prior,prior_ref,previous_end=baseline
  assert code[ret:]==prior[previous_end:]
  def key(r):
   return (r['offset'],r['type'],r['addend'],r['symbol'],
           r['local_symbol_offset'])
  assert sorted(map(key,refs))==sorted(map(key,prior_ref))
 row={'original_complete_CODE_B':46755,'whole_compiled_CODE_B':ret,
   'whole_native_and_compiler_x86':13230,'total_source_PE_COFF_fields':len(refs),
   'whole_wrong_native_mnemonic_count':len(wrongm),
   'whole_wrong_native_width_ordinals':widths,
   'whole_wrong_GPR_roles':len(allwrong),
   'first_wrong_GPR_ordinal':allwrong[0],
   'original_58_mnemonic_wrong_ordinals':bad58m,
   'original_58_width_wrong_ordinals':bad58w,
   'original_59_native_original_B':356,
   'original_59_x86':95,'original_59_GPR_role_wrong_ordinals':bad59r,
   'original_59_actual_PE_zero_addend_fields_verified':len(target_records),
   'original_59_nonfield_and_nonshared_JMP_byte_wrong_offsets':wrong,
   'original_59_real_shared_epilogue_JMPs_verified':count,
   'source_separate_afterRET_DATA_B':len(code)-ret,
   'full_game_exact':False}
 summary[label]=row
 print(label,'whole',ret,'original native 0x58 wrong mnemonics',bad58m,
    'widths',bad58w,'0x59 GPR differences',len(bad59r),
    '0x59 real other-byte differences',len(wrong),
    'source fields',len(target_records),flush=True)
old=summary['original-for'];new=summary['postincrement-while']
assert (len(old['original_59_GPR_role_wrong_ordinals']),
        len(old['original_59_nonfield_and_nonshared_JMP_byte_wrong_offsets']))==(19,19)
assert (len(new['original_59_GPR_role_wrong_ordinals']),
        len(new['original_59_nonfield_and_nonshared_JMP_byte_wrong_offsets']))==(0,0)
assert old['original_58_mnemonic_wrong_ordinals']==[]
assert old['original_58_width_wrong_ordinals']==[]
assert new['original_58_mnemonic_wrong_ordinals']==[55]
assert new['original_58_width_wrong_ordinals']==[55,59]
assert old['whole_wrong_native_width_ordinals']==[2885,2908,8455,8986,9130]
assert new['whole_wrong_native_width_ordinals']==[2023,2027,2885,2908,8455,8986,9130]
assert old['total_source_PE_COFF_fields']==new['total_source_PE_COFF_fields']==1491
(O/'verified-summary.json').write_text(json.dumps({
  'original_Japanese_fighter':'0x005214B0',
  'whole_original_CODE_B':46755,'full_native_x86':13230,
  'full_original_afterRET_DATA_B':901,
  'real_0x59_GPR_regression_resolved_by_preceding_postincrement':True,
  'real_original_previous_0x58_opcode_mnemonic_and_width_regressed':True,
  'native_full_code_exact':False,'new_accepted_original_CODE_bytes':0,
  'mass_cold_replay':False,'whole_parent_controls':summary,
 },indent=2)+'\n')
print('F932 cross-fighter full 46KB proof: 0x59 19-to-0 actual nonfield/GPR differences with verified 16 PE fields and 2 genuine shared epilogue exits. Source 0x58 regresses; no native entire exact credit.')
