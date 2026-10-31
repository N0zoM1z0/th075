#!/usr/bin/env python3
"""F1025: verify EVERY typed nonlocal original 58KB giant PE target.

Fresh-build the two original-shaped F781/F917 58KB VC7.1
normal sources using the canonical F917 original-float-X native
verifier. Independently check the WHOLE physical Japanese
00543210 original PE, all 16471 ordered x86, all physical
genuine typed zero-addend 1697/1697 nonlocal original
COFF call/global relocation targets, 10 code local refs,
156 independently original afterRET switch DIR32 targets and
319 nonfield DATA bytes. Original entire giant still NONEXACT:
three genuine width mismatches, 1741 original GPR differences,
absolute COFF positions shifted, source 58293 rather than
native 58294 CODE B. Never award internal states/whole CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import bisect,importlib.util,json,os,re,subprocess,sys,collections
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1025-original-58kb-pe';O.mkdir(parents=True,exist_ok=True)
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
cp=subprocess.run([str(R/'scripts/repo-python'),
 str(R/'scripts/verify-fighter-native-burst-x87-f917.py')],
 cwd=R,env=E,capture_output=True,text=True,timeout=1150)
(O/'F917-fresh-complete-parents.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
sp=importlib.util.spec_from_file_location('f1025read',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x543210;CODE=58294;X86=16471;AFTER=943
raw=rd.pe_bytes_at(PE,BASE,CODE)
native=list(D.disasm(raw,BASE))
assert len(native)==X86 and native[-1].address+native[-1].size==BASE+CODE
sources={
 'F781-before-native-x87':R/'.analysis/f917-native-burst-x87-verified/F781-original-source-control.obj',
 'F917-native-positive-x87':R/'.analysis/f917-native-burst-x87-verified/F917-borrowed-real-X.obj'}
rgs=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(rgs.findall(i.op_str))
f759sp=importlib.util.spec_from_file_location('f1025f759',R/'scripts/verify-fighter-four-directional-c8-f759.py')
f759=importlib.util.module_from_spec(f759sp);sys.modules[f759sp.name]=f759;f759sp.loader.exec_module(f759)
f781sp=importlib.util.spec_from_file_location('f1025f781',R/'scripts/verify-fighter-shared-getter-f781.py')
f781=importlib.util.module_from_spec(f781sp);sys.modules[f781sp.name]=f781;f781sp.loader.exec_module(f781)
manifest=__import__('json').loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())
boss=next(b for b in manifest['bosses'] if b['address']==BASE)
assert boss['size']==CODE and boss['postret_size']==AFTER
assert boss['dense_entries']==156 and boss['sparse_bytes']==319
import bisect
rows={}
for label,obj in sources.items():
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ')
 ins=[]
 for x in D.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 end=ins[-1].address+ins[-1].size
 assert end==CODE-1 and len(ins)==X86 and len(code)-end==AFTER and len(refs)==1863
 first=[x.address for x in ins]
 external=[r for r in refs if r['offset']<end and r['local_symbol_offset'] is None]
 localcode=[r for r in refs if r['offset']<end and r['local_symbol_offset'] is not None]
 table=[r for r in refs if r['offset']>=end]
 assert len(external)==1697 and len(localcode)==10 and len(table)==156
 matched=collections.Counter();orig_targets=[];errors=[]
 for r in external:
  assert r['type'] in ('DIR32','REL32') and r['addend']==0
  assert r['local_symbol_offset'] is None
  j=bisect.bisect_right(first,r['offset'])-1
  assert 0<=j<X86 and ins[j].address<=r['offset']<=ins[j].address+ins[j].size-4
  delta=r['offset']-ins[j].address
  assert delta+4<=native[j].size
  orig_phys=native[j].address+delta
  val=int.from_bytes(rd.pe_bytes_at(PE,orig_phys,4),'little',signed=r['type']=='REL32')
  dest=orig_phys+4+val if r['type']=='REL32' else val
  match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
  if match:
   expected=int(match.group(1),16);cls='address-named'
  else:
   assert r['symbol']=='__ftol2',r['symbol']
   expected=0x6406AC;cls='ftol2'
  if dest!=expected:errors.append((j,r['symbol'],hex(dest),hex(expected)))
  matched[cls]+=1
  orig_targets.append({'native_x86_ordinal':j,'original_field_va':f'0x{orig_phys:08X}',
    'original_real_destination':f'0x{dest:08X}',
    'original_type':r['type'],'source_symbol':r['symbol']})
 assert not errors,errors[:10]
 assert matched=={'address-named':1676,'ftol2':21},matched
 # Every afterRET local DIR32 is a genuine source CASE label. Original
 # game target mapping, constant sparse-map bytes and all real table
 # relocation values are checked independently by the F759 owner.
 f759.check_afterret(rd,PE,D,boss,code,refs,ins)
 badm=[j for j,(n,x) in enumerate(zip(native,ins)) if n.mnemonic!=x.mnemonic]
 badw=[j for j,(n,x) in enumerate(zip(native,ins)) if n.size!=x.size]
 badg=[j for j,(n,x) in enumerate(zip(native,ins)) if roles(n)!=roles(x)]
 row={'native_complete_CODE_B':CODE,'source_CODE_B':end,
 'native_and_source_x86':X86,'whole_source_COFF_fields':len(refs),
 'native_pe_field_counts':{'typed_nonlocal_external':1697,
  'address_named_original_targets':1676,'original_ftol2_targets':21,
  'actual_original_code_local_labels':10,
  'original_afterRET_DIR32_labels':156,
  'original_afterRET_nonfield_bytes':319},
 'wrong_native_mnemonic_ordinals':badm,
 'wrong_native_width_ordinals':badw,
 'wrong_native_GPR_roles_count':len(badg),
 'all_1697_original_PE_external_targets_verified':True,
 'whole_original_exact':False}
 rows[label]=row
 print(label,'CODE',end,'native',CODE,'x86',X86,
   'all typed original external PE',len(orig_targets),
   'wrong native mnemonic',len(badm),'width',len(badw),
   'GPR',len(badg),flush=True)
 if label=='F917-native-positive-x87':
  (O/'real-original-PE-fields.json').write_text(json.dumps(orig_targets,indent=2)+'\n')
assert rows['F781-before-native-x87']['wrong_native_mnemonic_ordinals']==[11765,11970,12328,12528]
best=rows['F917-native-positive-x87']
assert best['wrong_native_mnemonic_ordinals']==[]
assert best['wrong_native_width_ordinals']==[2934,2977,3000]
assert best['wrong_native_GPR_roles_count']==1741
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x00543210',
 'whole_original_CODE_B':CODE,'whole_original_x86':X86,
 'all_original_1697_external_PE_call_global_destinations_match':True,
 '1697_source_named_original_PE_dests':{'AtHEX':1676,'__ftol2':21},
 'all_10_native_code_local_case_refs_and_156_afterRET_labels_verified':True,
 'native_319_nonfield_afterRET_bytes_match':True,
 'remaining_native_width_defects':[2934,2977,3000],
 'remaining_native_GPR_role_defects':1741,
 'native_whole_exact':False,'new_accepted_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_original_source_profiles':rows
},indent=2)+'\n')
print('F1025 pinned original58KB: all 1,697 real external PE targets, 10 code-local labels, 156 afterRET DIR32 and 319 native DATA nonfields verified. Zero wrong native mnemonics, 3 widths and 1,741 GPR roles remain. Entire callable NONEXACT.')
