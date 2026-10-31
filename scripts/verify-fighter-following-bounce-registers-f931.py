#!/usr/bin/env python3
"""F931: independently confirm native actor register phase recovered in 0x59.

Build two ENTIRE original 58KB VC7.1 game-fighter parent sources serially;
read the SHA-pinned original PE and verify 0x58/0x59 real extents, all
actual target-backed COFF fields, native 0x59 GPR/x87/branch operands,
four-entry shared getter and entire 943B afterRET jump DATA. The short
preceding loop grammar is still WRONG and never earns exact CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,sys,subprocess,os,json,re,hashlib

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f931-following-bounce-registers';O.mkdir(parents=True,exist_ok=True)
SYMBOL='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
SOURCE_MARKER='#include "FighterTrajectoryBurst58F614.inc"'
REAL_LOOP=('for (int burst=0;burst<10;++burst)\n'
           '            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);')
CONTROL_LOOP=('int burst=0;\n'
              '        while (burst++<10) {\n'
              '            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);\n'
              '        }')
def load(tag,relative):
 sp=importlib.util.spec_from_file_location(tag,R/relative)
 m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m)
 return m

f781=load('f931_781','scripts/verify-fighter-shared-getter-f781.py')
f778=load('f931_778','scripts/verify-fighter-native-default-f778.py')
f759=load('f931_759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=load('f931_762','scripts/verify-fighter-typed-returns-f762.py')
f734=load('f931_734','scripts/verify-fighter-eight-round-f734.py')
f777=load('f931_777','scripts/verify-fighter-current-register-phases-f777.py')
rd=load('f931_reader','scripts/compare-coff-function.py')
pe=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
full,boss=f781.source_for_whole_parent(f778,f759,f762)
for name in ('FighterEarlyPairF722.inc','FighterFollowupBurstF724.inc'):
 old='#include "'+name+'"'
 assert full.count(old)==1
 full=full.replace(old,(R/'probes'/name).read_text(),1)
for n in (20,46):
 old=f'float(*reinterpret_cast<signed char*>(RAW+0x66)*-{n})+F32(0x44)'
 new=(f'reinterpret_cast<FighterProjectileXViewF917*>(this)->'
      f'coordinateXAt44-float(*reinterpret_cast<signed char*>(RAW+0x66)*{n})')
 assert full.count(old)==2
 full=full.replace(old,new)
full='#include "FighterProjectileXViewF917.hpp"\n'+full
fragment=(R/'probes/FighterTrajectoryBurst58F614.inc').read_text()
assert full.count(SOURCE_MARKER)==1 and fragment.count(REAL_LOOP)==1
assert boss['size']==58294 and boss['postret_size']==943
original=list(D.disasm(rd.pe_bytes_at(pe,0x543210,58294),0x543210))
assert len(original)==16471 and original[-1].address+original[-1].size==0x5515c6
lo,hi,native58_size,native58_x86,refs58,_=f777.ORIGINAL[0x58]
al,ah,native59_size,native59_x86,refs59,_=f777.ORIGINAL[0x59]
assert hi==al and hi-lo==469 and ah-al==356
first58=next(i for i,x in enumerate(original) if x.address==lo)
first59=next(i for i,x in enumerate(original) if x.address==al)
assert (first58,first59)==(2063,2198)
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
results={}; compiled={}
for tag,frag in [('F917-strict-preceding',fragment),
                 ('F931-postincrement-while',fragment.replace(REAL_LOOP,CONTROL_LOOP,1))]:
 source=full.replace(SOURCE_MARKER,frag,1)
 cpp,obj=O/(tag+'.cpp'),O/(tag+'.obj');cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
                     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
                   cwd=R,env=E,capture_output=True,text=True,timeout=350)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,SYMBOL)
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert end==58293 and len(I)==16471 and len(refs)==1863 and len(code)-end==943
 mapping=f734.source_map_from_original_afterRET(rd,pe,boss,code,I,refs)
 start58,stop58=mapping[lo],mapping[hi]
 start59,stop59=mapping[al],mapping[ah]
 assert start58==original[first58].address-0x543210 and stop58-start58==469
 assert start59==original[first59].address-0x543210 and stop59-start59==356
 assert len([x for x in I if start58<=x.address<stop58])==135
 assert len([x for x in I if start59<=x.address<stop59])==95
 native58=list(D.disasm(rd.pe_bytes_at(pe,lo,469),lo))
 source58=[x for x in I if start58<=x.address<stop58]
 dif_m=[j for j,(a,b) in enumerate(zip(native58,source58)) if a.mnemonic!=b.mnemonic]
 dif_w=[j for j,(a,b) in enumerate(zip(native58,source58)) if a.size!=b.size]
 native59=list(D.disasm(rd.pe_bytes_at(pe,al,356),al))
 source59=[x for x in I if start59<=x.address<stop59]
 dif_regs=[j for j,(a,b) in enumerate(zip(native59,source59)) if roles(a)!=roles(b)]
 dif59_m=[j for j,(a,b) in enumerate(zip(native59,source59)) if a.mnemonic!=b.mnemonic]
 dif59_w=[j for j,(a,b) in enumerate(zip(native59,source59)) if a.size!=b.size]
 assert not dif59_m and not dif59_w
 # Case 0x59 physical source fields and non-branch bytes are rechecked
 # by the original PE-based typed relocation/actual target matcher.
 expected_bad=19 if tag.startswith('F917') else 0
 record59=f777.physical_whole_case(rd,pe,D,code,refs,I,mapping,0x59,
    (al,ah,native59_size,native59_x86,refs59,expected_bad))
 assert record59['native_zero_addend_typed_PE_COFF_fields_checked']==16
 # Case 0x58 real PE fields are unchanged even in the loop grammar control.
 fields58=[r for r in refs if start58<=r['offset']<stop58]
 assert len(fields58)==17
 for r in fields58:
  idx=next(i for i,x in enumerate(source58) if x.address<=r['offset']<x.address+x.size)
  assert r['addend']==0 and r['local_symbol_offset'] is None
  delta=r['offset']-source58[idx].address
  native_field_offset=native58[idx].address-lo+delta
  resolved=f777.native_reloc_dest(rd.pe_bytes_at(pe,lo,469),lo,native_field_offset,r['type'])
  lookup=re.search(r'At([0-9A-Fa-f]{6,8})(?=[^0-9a-fA-F]|$)',r['symbol'])
  expected=(int(lookup.group(1),16) if lookup else
    0x006406AC if r['symbol']=='__ftol2' else None)
  assert expected==resolved,(tag,r['offset'],r['symbol'],hex(resolved))
 # Assert external whole-father shared tail and 943-byte afterRET
 # actually exist and resolve (not just same length or field count).
 suffix=f781.verify_original_shared_getter(rd,pe,D,code,refs,I,end)
 after=f759.check_afterret(rd,pe,D,boss,code,refs,I)
 assert suffix['original_46B_suffix_and_source_46B_suffix_x86']==16
 whole_regs=[j for j,(a,b) in enumerate(zip(original,I)) if roles(a)!=roles(b)]
 row={'generated_complete_callable_CODE_B':end,
      'original_complete_callable_CODE_B':58294,
      'whole_x86':len(I),'COFF_fields':len(refs),'afterRET_DATA_B':len(code)-end,
      'original_58_native_and_source_B':469,
      'original_58_native_and_source_x86':135,
      'original_58_mnemonic_wrong_ordinals':dif_m,
      'original_58_width_wrong_ordinals':dif_w,
      'original_58_real_native_PE_target_fields_verified':len(fields58),
      'original_59_native_and_source_B':356,
      'original_59_native_and_source_x86':95,
      'original_59_wrong_mnemonic_ordinals':dif59_m,
      'original_59_wrong_width_ordinals':dif59_w,
      'original_59_wrong_GPR_ordinals':dif_regs,
      'original_59_native_PE_target_fields_verified':record59['native_zero_addend_typed_PE_COFF_fields_checked'],
      'original_59_physical_nonrelocation_nonshared_jump_byte_mismatches':
         record59['actual_original_nonfield_operand_byte_mismatches'],
      'original_59_true_external_shared_tail_JMP_fields':record59['genuine_shared_parent_JMPs_excluded_only_for_diagnosis'],
      'original_whole_first_GPR_wrong_ordinal':whole_regs[0],
      'original_whole_GPR_wrong_instruction_count':len(whole_regs),
      'original_real_fighter_four_shared_getter_edges_rechecked':True,
      'complete_afterRET_943B_and_156_DIR32_rechecked':True,
      'whole_game_exact':False}
 results[tag]=row;compiled[tag]=(code,refs,I,end)
 print(tag,'whole',end,'native0x58 mnemonic bad',dif_m,'width bad',dif_w,
     'case0x59 GPR wrong',len(dif_regs),'original other bytes wrong',
     row['original_59_physical_nonrelocation_nonshared_jump_byte_mismatches'],flush=True)
b=results['F917-strict-preceding'];c=results['F931-postincrement-while']
assert b['original_58_mnemonic_wrong_ordinals']==[] and b['original_58_width_wrong_ordinals']==[]
assert b['original_59_wrong_GPR_ordinals'] and len(b['original_59_wrong_GPR_ordinals'])==19
assert b['original_59_physical_nonrelocation_nonshared_jump_byte_mismatches']==19
assert c['original_58_mnemonic_wrong_ordinals']==[55]
assert c['original_58_width_wrong_ordinals']==[55,59]
assert c['original_59_wrong_GPR_ordinals']==[] and c['original_59_physical_nonrelocation_nonshared_jump_byte_mismatches']==0
assert c['original_whole_first_GPR_wrong_ordinal']<first59
# Not exact: no reduction of overall whole function original CODE count,
# only a strong previous-case x86 role/next-case compatibility tradeoff.
(O/'verified-summary.json').write_text(json.dumps({
 'original_native_fighter':'0x00543210',
 'native_complete_CODE_B':58294,'native_x86':16471,
 'real_first_source_register_case':'0x59',
 'true_original_0x59_relative_native_nonfield_byte_improvement':19,
 'original_0x59_register_ordinal_improvement':19,
 'candidate_0x58_is_wrong_and_not_accepted':True,
 'native_0x59_two_parent_shared_tail_jumps_not_counted_as_exact_bytes':True,
 'whole_original_exact':False,'new_accepted_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_compiled_parent_results':results,
},indent=2)+'\n')
print('F931: 58KB whole native: 469B preceding case0x58 loses 1 opcode /2 widths, but real 356B/95x86 next case0x59 has 0 wrong nonfield and 0 wrong GPR roles, 16 native PE-targeted COFF fields. No whole exact.')
