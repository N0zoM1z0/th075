#!/usr/bin/env python3
"""F1028: pin all 2191 original typed nonlocal PE destinations in 82KB giant.

Fresh-build ONLY the tracked original-shaped whole 82796B/22721
x86 normal VC7.1 F1020 fighter and independently decode the
pinned Japanese native PE, all genuine physical nonlocal REL32/
DIR32 targets (2150 address-named and 41 __ftol2), 10 original
CODE-local fields and 151 afterRET DIR32 labels plus 522 real
nonfield DATA bytes. Count all 12 wrong native instruction widths
and 6958 wrong native GPR roles. Whole still NONEXACT; do not
credit interior switch cases as separate original game functions.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import bisect,importlib.util,json,os,re,subprocess,sys,collections
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1028-original-82kb-whole-PE';O.mkdir(parents=True,exist_ok=True)
cpp=R/'probes/FighterWhole004AC040F1020.cpp'
assert cpp.exists()
obj=O/'F1020-fresh-original-shaped.obj'
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=env,capture_output=True,text=True,timeout=370)
(O/'whole-original-shaped-VC71.log').write_text(p.stdout+p.stderr)
assert p.returncode==0,(p.stdout+p.stderr)[-850:]
sp=importlib.util.spec_from_file_location('f1028reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;NATIVE=82796;X86=22721;DATA=1126
original=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE),BASE))
assert len(original)==X86 and original[-1].address+original[-1].size==BASE+NATIVE
assert original[2].op_str=='esp, 0x720'
assert original[4].op_str=='dword ptr [ebp - 0x64], ecx'
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
I=[]
for ins in D.disasm(code,0):
 I.append(ins)
 if ins.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert end==NATIVE and len(I)==X86 and len(code)-end==DATA and len(refs)==2352
assert I[2].op_str==original[2].op_str and I[4].op_str==original[4].op_str
wrong_m=[j for j,(x,y) in enumerate(zip(original,I)) if x.mnemonic!=y.mnemonic]
wrong_w=[j for j,(x,y) in enumerate(zip(original,I)) if x.size!=y.size]
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
wrong_g=[j for j,(x,y) in enumerate(zip(original,I))
         if rx.findall(x.op_str)!=rx.findall(y.op_str)]
assert not wrong_m
assert len(wrong_w)==12 and len(wrong_g)==6958
assert sum(I[j].size-original[j].size for j in wrong_w)==0
external=[r for r in refs if r['offset']<end and r['local_symbol_offset'] is None]
local=[r for r in refs if r['offset']<end and r['local_symbol_offset'] is not None]
table=[r for r in refs if r['offset']>=end]
assert (len(external),len(local),len(table))==(2191,10,151)
starts=[x.address for x in I]
real_targets=[];classes=collections.Counter()
for r in external:
 assert r['type'] in ('REL32','DIR32') and r['addend']==0
 j=bisect.bisect_right(starts,r['offset'])-1
 assert 0<=j<X86 and I[j].address<=r['offset']<=I[j].address+I[j].size-4
 d=r['offset']-I[j].address
 assert d+4<=original[j].size
 orig_field=original[j].address+d
 v=int.from_bytes(rd.pe_bytes_at(PE,orig_field,4),'little',signed=r['type']=='REL32')
 native_target=orig_field+4+v if r['type']=='REL32' else v
 match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
 if match:
  expected=int(match.group(1),16);kind='address-named'
 else:
  assert r['symbol']=='__ftol2',r['symbol']
  expected=0x6406AC;kind='ftol2'
 assert native_target==expected,(j,r['symbol'],hex(native_target),hex(expected))
 classes[kind]+=1
 real_targets.append({'native_original_x86_ordinal':j,
  'native_original_PE_field':f'0x{orig_field:08X}',
  'actual_native_original_target':f'0x{native_target:08X}',
  'typed_zero_addend_reloc':r['type'],'natural_source_symbol':r['symbol']})
assert classes=={'address-named':2150,'ftol2':41}
native_after=rd.pe_bytes_at(PE,BASE+NATIVE,DATA)
masked=set();mapping=[]
for r in table:
 q=r['offset']-end
 assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
 assert all(j not in masked for j in range(q,q+4))
 masked.update(range(q,q+4))
 target=int.from_bytes(native_after[q:q+4],'little')
 assert BASE<=target<BASE+NATIVE
 mapping.append((q,target,r['local_symbol_offset']))
assert len(mapping)==151 and DATA-len(masked)==522
assert all(code[end+j]==native_after[j] for j in range(DATA) if j not in masked)
# The real afterRET native source jump table entries are each equal
# iff the original physical PE game target entries are equal.
assert all((x[1]==y[1])==(x[2]==y[2]) for x in mapping for y in mapping)
(O/'actual-original-2191-PE-targets.json').write_text(json.dumps(real_targets,indent=2)+'\n')
(O/'verified-summary.json').write_text(json.dumps({
 'SHA_pinned_Japanese_original_fighter':'0x004AC040',
 'real_entire_original_CODE_B':NATIVE,'real_original_x86':X86,
 'source_entire_CODE_B':end,'source_x86':len(I),
 'native_frame_and_saved_this_restored':['0x720','EBP-0x64'],
 'all_2191_external_original_PE_targets_correct':True,
 'address_named_actual_native_global_call_targets':2150,
 'native_ftol2_external_targets':41,
 'real_code_local_COFF_fields':10,
 'original_afterRET_DIR32_fields':151,
 'actual_native_afterRET_nonfield_DATA_B':522,
 'native_wrong_mnemonic_ordinals':wrong_m,
 'native_wrong_width_ordinals':wrong_w,
 'original_wrong_GPR_role_count':len(wrong_g),
 'native_whole_exact':False,'new_exact_original_GAME_CODE_B':0,
 'mass_cold_replay':False
},indent=2)+'\n')
print('F1028 whole 82KB original 82796B/22721 x86, 2191/2191 real nonlocal PE destinations, 10 original code labels, 151 afterRET DIR32, 522 original nonfield DATA. All opcode mnemonics, frame0x720/this EBP-0x64 but 12 widths/6958 GPR roles wrong; WHOLE NONEXACT.')
