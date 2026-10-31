#!/usr/bin/env python3
"""F917: restore 4 native FSUBR/positive-IMUL sequences in real 58KB fighter.

Regenerates two complete VC7.1 /Od whole-parent sources from F781's
tracked chain. Native opponent/case structure is not cropped; all 16471
instruction mnemonics/widths, typed COFF fields, and 943B afterRET
jump data are inspected. Four true x87 source sequences are corrected
using a borrowed observed +0x44 float actor member. NO exact CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,sys,subprocess,re
ROOT=Path(__file__).resolve().parents[1]
O=ROOT/'.analysis/f917-native-burst-x87-verified';O.mkdir(parents=True,exist_ok=True)
ADDR=0x00543210;ORIGINAL_SIZE=58294
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'
FOUR=(11765,11970,12328,12528)
IMMEDIATE=(20,46,20,46)

def load(name,path):
 s=importlib.util.spec_from_file_location(name,ROOT/path)
 m=importlib.util.module_from_spec(s);sys.modules[s.name]=m;s.loader.exec_module(m)
 return m

f781=load('f917_781','scripts/verify-fighter-shared-getter-f781.py')
f778=load('f917_778','scripts/verify-fighter-native-default-f778.py')
f759=load('f917_759','scripts/verify-fighter-four-directional-c8-f759.py')
f762=load('f917_762','scripts/verify-fighter-typed-returns-f762.py')
rd=load('f917_reader','scripts/compare-coff-function.py')
original,boss=f781.source_for_whole_parent(f778,f759,f762)
assert boss['size']==58294 and boss['postret_size']==943
# This is the real, accepted F781 entire original-shaped parent,
# not the previous F708 *different* compiler parent context.
for stem in ('FighterEarlyPairF722.inc','FighterFollowupBurstF724.inc'):
 marker='#include "'+stem+'"'
 assert original.count(marker)==1
 original=original.replace(marker,(ROOT/'probes'/stem).read_text(),1)
sign='*reinterpret_cast<signed char*>(RAW+0x66)'
base=lambda n:'float('+sign+'*-'+str(n)+')+F32(0x44)'
replacement=lambda n:'reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float('+sign+'*'+str(n)+')'
corrected=original
for n in (20,46):
 assert corrected.count(base(n))==2
 corrected=corrected.replace(base(n),replacement(n))
corrected='#include "FighterProjectileXViewF917.hpp"\n'+corrected
assert corrected.count('coordinateXAt44-float(')==4
D=Cs(CS_ARCH_X86,CS_MODE_32)
PE=rd.verified_target();N=list(D.disasm(rd.pe_bytes_at(PE,ADDR,ORIGINAL_SIZE),ADDR))
assert len(N)==16471 and N[-1].address+N[-1].size==ADDR+ORIGINAL_SIZE
for j,amount in zip(FOUR,IMMEDIATE):
 assert N[j].mnemonic=='fsubr' and N[j].op_str.endswith('0x44]')
 assert N[j-4].mnemonic=='imul' and int(N[j-4].op_str.rsplit(',',1)[-1],0)==amount
 assert N[j-2].mnemonic=='fild'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={};artifacts={}
for tag,source in [('F781-original-source-control',original),('F917-borrowed-real-X',corrected)]:
 cpp,obj=O/(tag+'.cpp'),O/(tag+'.obj')
 cpp.write_text(source)
 cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
      cwd=ROOT,env=E,capture_output=True,text=True,timeout=340)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-980:]
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert end==58293 and len(I)==16471 and len(refs)==1863 and len(code)-end==943
 mnemonic_wrong=[i for i,(n,s) in enumerate(zip(N,I)) if n.mnemonic!=s.mnemonic]
 widths_wrong=[i for i,(n,s) in enumerate(zip(N,I)) if n.size!=s.size]
 assert widths_wrong==[2934,2977,3000]
 four=[]
 for j,amount in zip(FOUR,IMMEDIATE):
  instructions=range(j-5,j+1)
  old_native=[N[k].bytes.hex() for k in instructions]
  source_bytes=[I[k].bytes.hex() for k in instructions]
  four.append({'native_last_x87_PE_address':f'0x{N[j].address:08X}',
               'whole_x86_ordinal':j,'native_imul_positive':amount,
               'whole_six_native_instructions_same_raw_bytes':old_native==source_bytes,
               'native_opcode':N[j].mnemonic,'source_opcode':I[j].mnemonic,
               'source_imul_int':I[j-4].op_str.rsplit(',',1)[-1].strip()})
 row={'original_callable_CODE_B':ORIGINAL_SIZE,'whole_source_CODE_B':end,
 'native_and_source_x86':16471,'source_COFF_fields':len(refs),
 'afterRET_DATA_B':len(code)-end,'whole_native_wrong_mnemonic_ordinals':mnemonic_wrong,
 'whole_native_wrong_width_ordinals':widths_wrong,
 'four_original_burst_x87_spots':four,
 'whole_game_exact':False}
 artifacts[tag]=(code,refs,I,end)
 rows[tag]=row
 print(tag,'source',end,'CODE; original',ORIGINAL_SIZE,'CODE; mnemonic wrong',
   mnemonic_wrong,'width wrong',widths_wrong,'six-native-byte-correct',
   [x['whole_six_native_instructions_same_raw_bytes'] for x in four],flush=True)
assert rows['F781-original-source-control']['whole_native_wrong_mnemonic_ordinals']==list(FOUR)
assert rows['F917-borrowed-real-X']['whole_native_wrong_mnemonic_ordinals']==[]
assert all(not x['whole_six_native_instructions_same_raw_bytes']
           for x in rows['F781-original-source-control']['four_original_burst_x87_spots'])
assert all(x['whole_six_native_instructions_same_raw_bytes']
           for x in rows['F917-borrowed-real-X']['four_original_burst_x87_spots'])
a,ra,ia,enda=artifacts['F781-original-source-control']
b,rb,ib,endb=artifacts['F917-borrowed-real-X']
assert enda==endb and a[enda:]==b[endb:]
diff=[j for j,(x,y) in enumerate(zip(a[:enda],b[:endb])) if x!=y]
assert len(diff)==8,diff
# Every changed generated CODE byte MUST belong to precisely the
# original four signed multiplier immediate bytes + FSUBR opcode bytes.
expected=set()
for j in FOUR:
 expected.add(ia[j-4].address+ia[j-4].size-1)
 expected.add(ia[j].address+1)
assert set(diff)==expected,(diff,sorted(expected))
# Non-local original COFF call/global fields and 156 local afterRET
# native switch-table COFF relocations must be untouched.
def record(r):
 return (r['offset'],r['type'],r['addend'],
        r['local_symbol_offset'],
        r['symbol'] if r['local_symbol_offset'] is None else None)
assert sorted(map(record,ra))==sorted(map(record,rb))
assert sum(r['offset']>=enda for r in rb)==156
# F781's original 943B table independently verifies source dense
# original PE actual handler ordinals, sparse map and all 156 fields.
f759.check_afterret(rd,PE,D,boss,b,rb,ib)
summary={'original_callable_fighter':'0x00543210',
 'original_complete_CODE_B':ORIGINAL_SIZE,'native_x86':len(N),
 'selected_complete_borrowed_Cpp_native_mnemonic_differences':0,
 'source_original_whole_CODE_byte_shortfall':1,
 'native_three_mode63_wrong_width_ordinals':[2934,2977,3000],
 'exact_source_code_bytes_changed_from_F781':8,
 'source_changed_eight_bytes_are_four_real_IMUL_signs_and_four_FSUBR_opcodes':True,
 'afterRET943_and_156_native_typed_COFF_fields_preserved':True,
 'native_whole_original_exact':False,'newly_accepted_original_CODE_B':0,
 'mass_cold_replay':False,'whole_source_profiles':rows}
(O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print('F917 00543210 full 16471-mnemonic match. Four original native POSX - positive-facing distance expressions are exactly six-x86-byte identical. 1 genuine CODE byte still short; remaining GPR and reloc fields unresolved; NO whole exact credit.')
