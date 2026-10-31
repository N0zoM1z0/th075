#!/usr/bin/env python3
"""F939: two true 337B/101-x86 0x5D/0x5E game cases in 82KB 004AC040.

Regenerate from tracked F938 incomplete whole parent + native-original
F939 real C++ pair, then serially compile three WHOLE VC7.1 fathers.
Independent PE checks: 0x58/59/5D/5E physical original boundaries,
0x5D/5E original actor-specific thresholds/floats, all 32 original
typed PE/COFF external targets and the entire 1126B separate afterRET.
Never count a case interior or a partial parent as exact whole CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f939-verified-third-pair'
O.mkdir(parents=True,exist_ok=True)
BASE=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
INC=(R/'probes/FighterThirdBossPair5D5EF939.inc').read_text()
MARK1='        case 0x5D: g_FighterProbeMarker = 94; break;'
MARK2='        case 0x5E: g_FighterProbeMarker = 95; break;'
assert BASE.count(MARK1)==BASE.count(MARK2)==1
assert INC.count('case 0x5D:')==INC.count('case 0x5E:')==1
# The tracked original actor 004AC040 has genuine constants different
# from the F752 58KB actor. No blind reuse of old guesses.
assert 'S16(0x62)<12' in INC and 'S16(0x62)<9' in INC
assert 'POS=12.5f;' in INC and 'POS=-12.5f;' in INC
assert 'POS5C=0.7f;' in INC
recovered=BASE.replace(MARK1,INC,1).replace(MARK2,'',1)
loop=(R/'probes/FighterTrajectoryBurst58F614.inc').read_text()
old='for (int burst=0;burst<10;++burst)\n            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);'
alt='int burst=0;\n        while (burst++<10) {\n            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);\n        }'
assert loop.count(old)==1
while_src=recovered.replace('#include "FighterTrajectoryBurst58F614.inc"',
    loop.replace(old,alt,1),1)
assert while_src!=recovered
cases={
 'F938-prior-5D5E-markers':BASE,
 'F939-native-5D5E':recovered,
 'F939-while-postincrement-control':while_src,
}
spec=importlib.util.spec_from_file_location('f939reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
base=0x4AC040;size=82796;post=1126;whole_x86=22721
native_full=list(D.disasm(rd.pe_bytes_at(PE,base,size),base))
assert len(native_full)==whole_x86 and native_full[-1].address+native_full[-1].size==base+size
native_data=rd.pe_bytes_at(PE,base+size,post)
physical={
 '0x58':(0x4ADD25,0x4ADEFA,469,135,17),
 '0x59':(0x4ADEFA,0x4AE05E,356,95,16),
 '0x5D':(0x4AE05E,0x4AE1AF,337,101,8),
 '0x5E':(0x4AE1AF,0x4AE300,337,101,8),
}
native={}
for name,(lo,hi,length,nx,nrefs) in physical.items():
 ins=list(D.disasm(rd.pe_bytes_at(PE,lo,length),lo))
 assert hi-lo==length and len(ins)==nx and ins[-1].address+ins[-1].size==hi
 native[name]=ins
# Prove ACTOR-specific original semantics directly, not inferred from F752.
for name,expected in (
 ('0x5D',{2:'edx, 0xc',28:'0xc',77:'eax, 4',86:'dword ptr [ecx + 0x50], 0x41480000',
          88:'dword ptr [edx + 0x5c], 0x3f333333',91:'ecx, 0xc',97:'0xa'}),
 ('0x5E',{2:'eax, 9',28:'9',77:'ecx, 6',86:'dword ptr [edx + 0x50], 0xc1480000',
          88:'dword ptr [eax + 0x5c], 0x3f333333',91:'edx, 9',97:'8'})):
 for ordinal,op in expected.items():
  assert native[name][ordinal].op_str==op,(name,ordinal,native[name][ordinal].op_str)
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(rx.findall(ins.op_str))
results={}
for name,body in cases.items():
 cpp,obj=O/(name+'.cpp'),O/(name+'.obj')
 cpp.write_text(body)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==post
 after_refs=[r for r in refs if r['offset']>=end]
 assert len(after_refs)==151
 labelmap={};mask=set()
 for r in after_refs:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(k not in mask for k in range(off,off+4))
  mask.update(range(off,off+4))
  pe_va=int.from_bytes(native_data[off:off+4],'little')
  assert base<=pe_va<base+size
  labelmap.setdefault(pe_va,r['local_symbol_offset'])
 assert post-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(post) if i not in mask)
 row={'whole_original_GAME_CODE_B':size,'whole_original_GAME_x86':whole_x86,
      'whole_partial_Cpp_CODE_B':end,'whole_partial_Cpp_x86':len(I),
      'source_COFF_fields_total':len(refs),
      'whole_afterRET_DATA_B':post,'native_afterRET_DIR32_labels':151,
      'native_afterRET_nonfield_equal_B':522,'original_cases':{},
      'whole_original_GAME_exact':False}
 for action,(lo,hi,length,nx,nrefs) in physical.items():
  l,h=labelmap[lo],labelmap[hi]
  compiled=[x for x in I if l<=x.address<h]
  original=native[action]
  refs_case=[r for r in refs if l<=r['offset']<h]
  status={'native_original_CODE_B':length,'original_native_x86':nx,
     'generated_CODE_B':h-l,'source_x86':len(compiled),
     'original_external_PE_target_fields_verified':0}
  if len(compiled)==nx and h-l==length:
   mw=[i for i,(a,b) in enumerate(zip(original,compiled)) if a.mnemonic!=b.mnemonic]
   ww=[i for i,(a,b) in enumerate(zip(original,compiled)) if a.size!=b.size]
   rg=[i for i,(a,b) in enumerate(zip(original,compiled)) if roles(a)!=roles(b)]
   status.update({'wrong_original_mnemonic_ordinals':mw,
       'wrong_original_width_ordinals':ww,'wrong_original_GPR_roles':rg})
   if not mw and not ww:
    assert len(refs_case)==nrefs,(action,len(refs_case))
    byte_native=rd.pe_bytes_at(PE,lo,length)
    for r in refs_case:
     j=next(i for i,x in enumerate(compiled)
            if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-compiled[j].address
     original_field=original[j].address-lo+delta
     assert r['offset']-l==original_field
     assert r['addend']==0 and r['local_symbol_offset'] is None
     assert r['type'] in ('REL32','DIR32')
     v=int.from_bytes(byte_native[original_field:original_field+4],
       'little',signed=r['type']=='REL32')
     target=original[j].address+delta+4+v if r['type']=='REL32' else v
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=(int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None)
     assert target==expected,(action,j,r['symbol'],hex(target),expected)
    status['original_external_PE_target_fields_verified']=len(refs_case)
  row['original_cases'][action]=status
 results[name]=row
 print(name,'whole source',end,len(I),
   'native real 5D/5E',[(c,row['original_cases'][c]['generated_CODE_B'],
                        row['original_cases'][c]['source_x86'],
                        len(row['original_cases'][c].get('wrong_original_GPR_roles',[])))
                        for c in ('0x5D','0x5E')],flush=True)
control=results['F938-prior-5D5E-markers']
real=results['F939-native-5D5E']
whilecontrol=results['F939-while-postincrement-control']
assert (control['whole_partial_Cpp_CODE_B'],control['whole_partial_Cpp_x86'])==(16312,4280)
assert (real['whole_partial_Cpp_CODE_B'],real['whole_partial_Cpp_x86'])==(16956,4478)
assert (whilecontrol['whole_partial_Cpp_CODE_B'],whilecontrol['whole_partial_Cpp_x86'])==(16956,4478)
for actor in ('0x5D','0x5E'):
 assert control['original_cases'][actor]['generated_CODE_B']==15
 assert real['original_cases'][actor]['generated_CODE_B']==337
 assert real['original_cases'][actor]['source_x86']==101
 assert real['original_cases'][actor]['wrong_original_mnemonic_ordinals']==[]
 assert real['original_cases'][actor]['wrong_original_width_ordinals']==[]
 assert real['original_cases'][actor]['original_external_PE_target_fields_verified']==8
 assert len(real['original_cases'][actor]['wrong_original_GPR_roles'])==61
 assert len(whilecontrol['original_cases'][actor]['wrong_original_GPR_roles'])==61
for r in (real,whilecontrol):
 assert r['original_cases']['0x59']['generated_CODE_B']==356
 assert r['original_cases']['0x59']['original_external_PE_target_fields_verified']==16
assert real['original_cases']['0x58']['wrong_original_mnemonic_ordinals']==[]
assert real['original_cases']['0x58']['wrong_original_width_ordinals']==[]
assert real['original_cases']['0x58']['wrong_original_GPR_roles']==[]
assert whilecontrol['original_cases']['0x58']['wrong_original_mnemonic_ordinals']==[55]
assert whilecontrol['original_cases']['0x58']['wrong_original_width_ordinals']==[55,59]
assert len(whilecontrol['original_cases']['0x59']['wrong_original_GPR_roles'])==0
(O/'verified-summary.json').write_text(json.dumps({
 'native_original_SHA_pinned_giant':'0x004AC040',
 'native_entire_original_CODE_B':size,
 'original_new_case5D_physically_complete_B':337,
 'original_new_case5E_physically_complete_B':337,
 'new_native_5D_5E_typed_actual_PE_targets':16,
 'native_real_5D_5E_cumul_original_CODE_B':674,
 'source_original_total_NEW_cases_already_actor59':True,
 'source_incomplete_giant_nonexact':True,
 'new_exact_original_GAME_CODE_B':0,
 'complete_original_exact':False,
 'no_all_unit_cold_replay':True,
 'whole_parent_source_variants':results
},indent=2)+'\n')
print('F939 two native third-fighter 337B/101-x86 stage actions with native actor-specific floats/thresholds, 16 genuine PE fields; full source remains 16,956 B partial, nonexact. 1,126B DATA checked.')
