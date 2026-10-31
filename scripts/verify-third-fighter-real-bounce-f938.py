#!/usr/bin/env python3
"""F938: replace a 15-B placeholder with ORIGINAL 356-B case0x59 in 82KB giant.

Three complete original-shaped VC7.1 parents, including the tracked
natural source, the old marker, and a diagnostic preceding-loop alternative.
Pin original Japanese PE, physical afterRET jump table, 0x58 and 0x59
complete original opcode/widths, and all real PE/COFF external targets.
Never claim case-only or truncated whole-game exact acceptance.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f938-third-original-bounce-proof';O.mkdir(parents=True,exist_ok=True)
SYM='?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ'
SRC=R/'probes/FighterWhole004AC040F938.cpp'
source=SRC.read_text()
assert source.count('#include "FighterScriptedBounce59F813.inc"')==1
loop_inc=(R/'probes/FighterTrajectoryBurst58F614.inc').read_text()
real_loop='for (int burst=0;burst<10;++burst)\n            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'
alternate='int burst=0;\n        while (burst++<10) {\n            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);\n        }'
assert loop_inc.count(real_loop)==1
variants={
 'F652-previous-marker':source.replace(
   '#include "FighterScriptedBounce59F813.inc"',
   '        case 0x59: g_FighterProbeMarker = 90; break;',1),
 'F938-new-real-bounce':source,
 'F938-postincrement-predecessor-control':source.replace(
   '#include "FighterTrajectoryBurst58F614.inc"',
   loop_inc.replace(real_loop,alternate,1),1)
}
spec=importlib.util.spec_from_file_location('f938reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
original_start=0x004AC040;whole=82796;original_x86=22721;after=1126
N=list(D.disasm(rd.pe_bytes_at(pe,original_start,whole),original_start))
assert len(N)==original_x86 and N[-1].address+N[-1].size==original_start+whole
original_data=rd.pe_bytes_at(pe,original_start+whole,after)
native58_lo,native58_hi=0x004ADD25,0x004ADEFA
native59_lo,native59_hi=0x004ADEFA,0x004AE05E
native58=list(D.disasm(rd.pe_bytes_at(pe,native58_lo,native58_hi-native58_lo),native58_lo))
native59=list(D.disasm(rd.pe_bytes_at(pe,native59_lo,native59_hi-native59_lo),native59_lo))
assert len(native58)==135 and native58_hi-native58_lo==469
assert len(native59)==95 and native59_hi-native59_lo==356
assert [x.mnemonic for x in native59[:4]]==['mov','movsx','cmp','jne']
assert native59[2].op_str=='ecx, 3' and native59[0].op_str=='eax, dword ptr [ebp - 0x64]'
assert native59[-1].mnemonic=='jmp'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
rows={};saved={}
for tag,body in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(body)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
     cwd=R,env=E,capture_output=True,text=True,timeout=325)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1100:]
 code,refs=rd.object_function(obj,SYM)
 ins=[]
 for x in D.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 ret=ins[-1].address+ins[-1].size
 assert len(code)-ret==after
 # Original native DATA contains actual physical VA of every
 # native switch label. Pair to the same source's actual DIR32
 # relocated local label, not guessed ordinal or external RVA.
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151 and all(r['type']=='DIR32' and
     r['addend']==0 and r['local_symbol_offset'] is not None
     and r['offset']+4<=len(code) for r in table)
 labelmap={}
 field_mask=set()
 for r in table:
  off=r['offset']-ret
  assert all(k not in field_mask for k in range(off,off+4))
  field_mask.update(range(off,off+4))
  native_va=int.from_bytes(original_data[off:off+4],'little')
  assert original_start<=native_va<original_start+whole
  labelmap.setdefault(native_va,r['local_symbol_offset'])
 wrong_data=[i for i in range(after) if i not in field_mask and
    code[ret+i]!=original_data[i]]
 assert len(wrong_data)==0 and len(field_mask)==151*4
 assert after-len(field_mask)==522
 for key in (native58_lo,native59_lo,native59_hi):
  assert key in labelmap
 l58,h58=labelmap[native58_lo],labelmap[native58_hi]
 l59,h59=labelmap[native59_lo],labelmap[native59_hi]
 assert l58<h58==l59<h59
 s58=[x for x in ins if l58<=x.address<h58]
 s59=[x for x in ins if l59<=x.address<h59]
 assert len(s58)==135 and h58-l58==469
 wrong58m=[i for i,(a,b) in enumerate(zip(native58,s58)) if a.mnemonic!=b.mnemonic]
 wrong58w=[i for i,(a,b) in enumerate(zip(native58,s58)) if a.size!=b.size]
 wrong58g=[i for i,(a,b) in enumerate(zip(native58,s58)) if roles(a)!=roles(b)]
 row={'actual_whole_source_CODE_B':ret,'native_whole_CODE_B':whole,
  'whole_source_x86':len(ins),'whole_original_x86':original_x86,
  'complete_source_COFF_fields':len(refs),
  'separate_original_and_source_afterRET_DATA_B':after,
  'separate_original_and_source_DIR32_table_fields':151,
  'separate_original_and_source_nonfield_DATA_equal_B':522,
  'actual_0x58_original_CODE_B':469,'source_0x58_CODE_B':h58-l58,
  'actual_0x58_original_x86':135,'source_0x58_x86':len(s58),
  '0x58_wrong_native_mnemonics':wrong58m,
  '0x58_wrong_native_instruction_widths':wrong58w,
  '0x58_wrong_native_GPR_roles':wrong58g,
  'actual_0x59_original_CODE_B':356,'source_0x59_CODE_B':h59-l59,
  'actual_0x59_original_x86':95,'source_0x59_x86':len(s59),
  '0x59_wrong_native_GPR_roles':[],
  '0x59_wrong_native_mnemonics':[],
  '0x59_wrong_native_widths':[],
  '0x59_actual_typed_PE_external_fields':0,
  'entire_original_game_function_exact':False}
 if tag=='F652-previous-marker':
  assert h59-l59==15
  assert len([r for r in refs if l59<=r['offset']<h59])==1
 else:
  assert h59-l59==356 and len(s59)==95
  row['0x59_wrong_native_GPR_roles']=[i for i,(a,b) in enumerate(zip(native59,s59)) if roles(a)!=roles(b)]
  row['0x59_wrong_native_mnemonics']=[i for i,(a,b) in enumerate(zip(native59,s59)) if a.mnemonic!=b.mnemonic]
  row['0x59_wrong_native_widths']=[i for i,(a,b) in enumerate(zip(native59,s59)) if a.size!=b.size]
  assert not row['0x59_wrong_native_mnemonics'] and not row['0x59_wrong_native_widths']
  physical=rd.pe_bytes_at(pe,native59_lo,356)
  native_fields=[r for r in refs if l59<=r['offset']<h59]
  assert len(native_fields)==16
  for r in native_fields:
   j=next(i for i,x in enumerate(s59) if x.address<=r['offset']<x.address+x.size)
   offset=r['offset']-s59[j].address
   assert r['addend']==0 and r['local_symbol_offset'] is None
   assert r['type'] in ('DIR32','REL32')
   original_field=native59[j].address-native59_lo+offset
   assert original_field==r['offset']-l59
   value=int.from_bytes(physical[original_field:original_field+4],
       'little',signed=r['type']=='REL32')
   actual=(native59[j].address+offset+4+value if r['type']=='REL32' else value)
   match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
   expected=(int(match.group(1),16) if match else
            0x6406AC if r['symbol']=='__ftol2' else None)
   assert actual==expected,(tag,j,r['symbol'],hex(actual),expected)
  row['0x59_actual_typed_PE_external_fields']=len(native_fields)
  # The real receiver saved-this EBP slot itself remains wrong:
  # the selected partial parent stores this at -8 rather than
  # original -0x64. Count GPR-only changes separately.
  assert s59[0].op_str.endswith('dword ptr [ebp - 8]')
  row['0x59_original_receiver_EBP']='-0x64'
  row['0x59_compiler_receiver_EBP']='-0x8'
 rows[tag]=row
 saved[tag]=(code,refs,ins,ret)
 print(tag,'whole',ret,'x86',len(ins),'0x58 mnemonic/width/GPR',
      len(wrong58m),len(wrong58w),len(wrong58g),
      '0x59 code/x86',h59-l59,len(s59),'wrongGPR',
      len(row['0x59_wrong_native_GPR_roles']),'fields',
      row['0x59_actual_typed_PE_external_fields'],flush=True)
old=rows['F652-previous-marker'];new=rows['F938-new-real-bounce'];alt=rows['F938-postincrement-predecessor-control']
assert (old['actual_whole_source_CODE_B'],old['whole_source_x86'])==(15972,4187)
assert (new['actual_whole_source_CODE_B'],new['whole_source_x86'])==(16312,4280)
assert (alt['actual_whole_source_CODE_B'],alt['whole_source_x86'])==(16312,4280)
assert old['source_0x59_CODE_B']==15
assert new['0x59_actual_typed_PE_external_fields']==alt['0x59_actual_typed_PE_external_fields']==16
assert (len(new['0x59_wrong_native_GPR_roles']),len(alt['0x59_wrong_native_GPR_roles']))==(19,0)
assert (new['0x58_wrong_native_mnemonics'],new['0x58_wrong_native_instruction_widths'],new['0x58_wrong_native_GPR_roles'])==([],[],[])
assert (alt['0x58_wrong_native_mnemonics'],alt['0x58_wrong_native_instruction_widths'])==([55],[55,59])
assert len(alt['0x58_wrong_native_GPR_roles'])>0
# The 151 real postret source records and the entire 1126B data
# still preserve source label shape, but source whole CODE is
# structurally partial and may have differing absolute relocs.
for other in ('F938-new-real-bounce','F938-postincrement-predecessor-control'):
 assert saved[other][0][saved[other][3]:] == saved['F652-previous-marker'][0][saved['F652-previous-marker'][3]:]
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_whole_fighter':'0x004AC040',
 'native_whole_original_CODE_B':82796,'native_whole_x86':22721,
 'native_case59_start':'0x004ADEFA','native_case59_end':'0x004AE05E',
 'original_case59_Cpp_reconstructed_from_placeholder':True,
 'original_case59_PE_targets_verified':16,
 'original_case59_relative_mnemonic_and_width_exact_in_whole_partial_parent':True,
 'native_original_receiver_EBP_still_wrong_in_partial_parent':True,
 'source_postincrement_while_recovers_case59_GPR_but_regresses_0x58':True,
 'whole_original_exact':False,'new_accepted_original_CODE_B':0,
 'mass_cold_replay':False,'compiled_whole_parent_sources':rows
},indent=2)+'\n')
print('F938 third 82KB original: 0x59 placeholder 15B -> actual 356B/95 original-x86 /16 true typed PE targets, 151 original DATA labels 522 exact nonfield bytes. Still incomplete and NONEXACT.')
