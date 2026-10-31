#!/usr/bin/env python3
"""F941: exact native case0x5F 144B/44 x86/GPR in the partial 82KB fighter.

Cold-build two complete original-shaped C++ father sources under VC7.1.
Reconstruct tracked F938+F939 cases, replace authentic 0x5F placeholder.
Compare original PE physical boundaries and targets (not case-only fake
functions), all prior real 0x58/59/5D/5E, afterRET labels/nonfields and
new 0x5F external sources. Whole 82KB giant is still NONEXACT.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import json,os,re,subprocess,importlib.util,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f941-third-original-facing';O.mkdir(parents=True,exist_ok=True)
BASE=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
PAIR=(R/'probes/FighterThirdBossPair5D5EF939.inc').read_text()
FACE=(R/'probes/FighterThirdBossFacing5FF941.inc').read_text()
A='        case 0x5D: g_FighterProbeMarker = 94; break;'
B='        case 0x5E: g_FighterProbeMarker = 95; break;'
C='        case 0x5F: g_FighterProbeMarker = 96; break;'
assert all(BASE.count(m)==1 for m in (A,B,C))
assert PAIR.count('case 0x5D:')==PAIR.count('case 0x5E:')==1
assert FACE.count('case 0x5F:')==1
prior=BASE.replace(A,PAIR,1).replace(B,'',1)
full=prior.replace(C,FACE,1)
s=importlib.util.spec_from_file_location('f941reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(s);sys.modules[s.name]=rd;s.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
native_base=0x4AC040;native_size=82796;native_x86=22721;data_size=1126
native_whole=list(D.disasm(rd.pe_bytes_at(PE,native_base,native_size),native_base))
assert len(native_whole)==native_x86
original_data=rd.pe_bytes_at(PE,native_base+native_size,data_size)
physical={
 '0x58':(0x4ADD25,0x4ADEFA,469,135,17),
 '0x59':(0x4ADEFA,0x4AE05E,356,95,16),
 '0x5D':(0x4AE05E,0x4AE1AF,337,101,8),
 '0x5E':(0x4AE1AF,0x4AE300,337,101,8),
 '0x5F':(0x4AE300,0x4AE390,144,44,3),
}
native_cases={}
for case,(a,b,n,nx,nf) in physical.items():
 instructions=list(D.disasm(rd.pe_bytes_at(PE,a,n),a))
 assert b-a==n and len(instructions)==nx
 native_cases[case]=instructions
assert [native_cases['0x5F'][i].op_str for i in (1,9,15)]==['0x40fa30','0x40fac0','0x40fac0']
assert native_cases['0x5F'][43].op_str=='0x4c03a7'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(rx.findall(ins.op_str))
profiles={}
for label,source in [('F939-original-5F-marker',prior),('F941-natural-5F-source',full)]:
 cpp=O/(label+'.cpp');obj=O/(label+'.obj');cpp.write_text(source)
 run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=350)
 (O/(label+'.log')).write_text(run.stdout+run.stderr)
 assert run.returncode==0,(run.stdout+run.stderr)[-1100:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for ins in D.disasm(code,0):
  I.append(ins)
  if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==data_size
 table=sorted((r for r in refs if r['offset']>=end),key=lambda r:r['offset'])
 assert len(table)==151
 mask=set();label_map={}
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  native_target=int.from_bytes(original_data[off:off+4],'little')
  assert native_base<=native_target<native_base+native_size
  label_map.setdefault(native_target,r['local_symbol_offset'])
 assert data_size-len(mask)==522
 assert all(code[end+j]==original_data[j] for j in range(data_size) if j not in mask)
 row={'whole_source_CODE_B':end,'whole_source_x86':len(I),
      'original_whole_CODE_B':native_size,'original_whole_x86':native_x86,
      'source_typed_COFF_fields_total':len(refs),'original_afterRET_DATA_B':data_size,
      'original_afterRET_DIR32_count':len(table),
      'original_afterRET_nonfield_bytes_equal':522,'original_cases':{},
      'whole_original_exact':False}
 for case,(a,b,n,nx,nf) in physical.items():
  lo,hi=label_map[a],label_map[b]
  native=native_cases[case];source_cases=[ins for ins in I if lo<=ins.address<hi]
  case_refs=[r for r in refs if lo<=r['offset']<hi]
  record={'native_whole_actor_original_case_CODE_B':n,'native_original_case_x86':nx,
          'source_case_CODE_B':hi-lo,'source_case_x86':len(source_cases)}
  if len(source_cases)==nx and hi-lo==n:
   m=[i for i,(x,y) in enumerate(zip(native,source_cases)) if x.mnemonic!=y.mnemonic]
   w=[i for i,(x,y) in enumerate(zip(native,source_cases)) if x.size!=y.size]
   g=[i for i,(x,y) in enumerate(zip(native,source_cases)) if roles(x)!=roles(y)]
   record.update({'wrong_mnemonics':m,'wrong_widths':w,'wrong_GPR_roles':g})
   if not m and not w:
    assert len(case_refs)==nf,(case,len(case_refs),nf)
    native_b=rd.pe_bytes_at(PE,a,n)
    for r in case_refs:
     ordinal=next(i for i,x in enumerate(source_cases)
                  if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-source_cases[ordinal].address
     native_field=native[ordinal].address-a+delta
     assert native_field==r['offset']-lo
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(native_b[native_field:native_field+4],'little',
                           signed=r['type']=='REL32')
     resolved=(native[ordinal].address+delta+4+value if r['type']=='REL32' else value)
     found=re.search(r'At([0-9a-fA-F]{6,8})',r['symbol'])
     expected=int(found.group(1),16) if found else 0x6406AC if r['symbol']=='__ftol2' else None
     assert resolved==expected,(case,ordinal,r['symbol'],hex(resolved),expected)
    record['native_PE_target_fields_verified']=nf
  row['original_cases'][case]=record
 profiles[label]=row
 print(label,'partial father B',end,'x86',len(I),
   '0x5F B/x86',record['source_case_CODE_B'],record['source_case_x86'],
   '0x5F wrong mnem/width/GPR',len(record.get('wrong_mnemonics',[])),
   len(record.get('wrong_widths',[])),len(record.get('wrong_GPR_roles',[])),flush=True)
old=profiles['F939-original-5F-marker'];new=profiles['F941-natural-5F-source']
assert (old['whole_source_CODE_B'],old['whole_source_x86'])==(16956,4478)
assert (new['whole_source_CODE_B'],new['whole_source_x86'])==(17086,4520)
assert (old['original_cases']['0x5F']['source_case_CODE_B'],old['original_cases']['0x5F']['source_case_x86'])==(15,2)
face=new['original_cases']['0x5F']
assert face['source_case_CODE_B']==144 and face['source_case_x86']==44
assert face['wrong_mnemonics']==face['wrong_widths']==face['wrong_GPR_roles']==[]
assert face['native_PE_target_fields_verified']==3
assert all(new['original_cases'][k]['source_case_CODE_B']==v for k,v in
           [('0x58',469),('0x59',356),('0x5D',337),('0x5E',337)])
assert new['original_cases']['0x58']['wrong_mnemonics']==[]
assert new['original_cases']['0x58']['wrong_widths']==[]
assert new['original_cases']['0x58']['wrong_GPR_roles']==[]
assert new['original_cases']['0x59']['native_PE_target_fields_verified']==16
assert new['original_cases']['0x5D']['native_PE_target_fields_verified']==8
assert new['original_cases']['0x5E']['native_PE_target_fields_verified']==8
# New source still uses EBP-8 receiver rather than native EBP-0x64;
# raw case bytes are NOT exact despite intra-case GPR role equality.
assert native_cases['0x5F'][0].op_str=='ecx, dword ptr [ebp - 0x64]'
( O/'verified-summary.json').write_text(json.dumps({
 'original_native_whole':'0x004AC040','original_native_CODE_B':82796,
 'original_native_whole_x86':22721,'original_native_0x5F':'0x004AE300..004AE390',
 'original_native_0x5F_x86':44,'original_native_0x5F_B':144,
 'genuine_original_0x5F_COFF_external_fields':3,
 'native_0x5F_GPR_mnemonic_and_width_roles_all_match':True,
 'source_native_this_EBP_still_wrong':True,
 'whole_82KB_original_exact':False,'new_original_exact_callable_CODE_B':0,
 'mass_cold_replay':False,'source_profiles':profiles
},indent=2)+'\n')
print('F941 complete: original 0x5F facing source matches all 44 native GPR/mnemonic/width positions, 144B/3 typed PE fields in whole 17,086B/4,520-x86 partial source. Not whole exact.')
