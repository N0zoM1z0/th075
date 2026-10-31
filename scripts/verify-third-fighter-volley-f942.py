#!/usr/bin/env python3
"""F942: reconstruct two original 553B resource cases inside partial 82KB father.

Build F941 previously real partial giant, original F748 incorrect
actor parameters, and F942 actor-specific real source as THREE
complete naturally compiled VC7.1 partial father C++ sources.
Independently re-read original SHA-pinned Japanese executable;
validate original case boundaries and original opcodes, genuine
original 20 typed source PE targets, previous original actions,
151 real afterRET labels and 522 genuine nonfield DATA bytes.
No independent exact-code credit for internal 0x60/0x61.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f942-third-original-volley';O.mkdir(parents=True,exist_ok=True)
BASE=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
PAIR=(R/'probes/FighterThirdBossPair5D5EF939.inc').read_text()
FACE=(R/'probes/FighterThirdBossFacing5FF941.inc').read_text()
VOLLEY=(R/'probes/FighterThirdBossVolley6061F942.inc').read_text()
PRIOR=(R/'probes/FighterResourceTenVolleyF748.inc').read_text()
for c,mark in [(0x5D,'94'),(0x5E,'95'),(0x5F,'96'),(0x60,'97'),(0x61,'98')]:
 assert BASE.count(f'case 0x{c:X}: g_FighterProbeMarker = {mark}; break;')==1
assert VOLLEY.count('case 0x60:')==VOLLEY.count('case 0x61:')==1
assert VOLLEY.count('S16(0x62)>2 && S16(0x62)<6')==2
assert VOLLEY.count('SetAuxActionAt40FB40(6)')==2
assert VOLLEY.count('else if (S16(0x62)==3 && S16(0x64)==0)')==2
src=BASE.replace('        case 0x5D: g_FighterProbeMarker = 94; break;',PAIR,1)
src=src.replace('        case 0x5E: g_FighterProbeMarker = 95; break;','',1)
src=src.replace('        case 0x5F: g_FighterProbeMarker = 96; break;',FACE,1)
g='extern float g_F748_SpeedScaleAt006590B8;'
assert src.count('extern float g_ThresholdAt0065782C;')==1
src=src.replace('extern float g_ThresholdAt0065782C;',
                'extern float g_ThresholdAt0065782C;\n'+g,1)
C60='        case 0x60: g_FighterProbeMarker = 97; break;'
C61='        case 0x61: g_FighterProbeMarker = 98; break;'
assert src.count(C60)==src.count(C61)==1
variants={
 'F941-previous-markers':src,
 'F748-other-actor-parameters':src.replace(C60,PRIOR,1).replace(C61,'',1),
 'F942-original-actor-parameters':src.replace(C60,VOLLEY,1).replace(C61,'',1),
}
sp=importlib.util.spec_from_file_location('f942rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
base=0x004AC040;total=82796;native_x86=22721;data_b=1126
N=list(D.disasm(rd.pe_bytes_at(PE,base,total),base))
assert len(N)==native_x86 and N[-1].address+N[-1].size==base+total
native_data=rd.pe_bytes_at(PE,base+total,data_b)
physical={
 '0x58':(0x4ADD25,0x4ADEFA,469,135,17),
 '0x59':(0x4ADEFA,0x4AE05E,356,95,16),
 '0x5D':(0x4AE05E,0x4AE1AF,337,101,8),
 '0x5E':(0x4AE1AF,0x4AE300,337,101,8),
 '0x5F':(0x4AE300,0x4AE390,144,44,3),
 '0x60':(0x4AE390,0x4AE5B9,553,158,10),
 '0x61':(0x4AE5B9,0x4AE7E2,553,158,10),
}
native={}
for k,(lo,hi,bytes_,nx,external) in physical.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,lo,bytes_),lo))
 assert hi-lo==bytes_ and len(n)==nx
 native[k]=n
for k in ('0x60','0x61'):
 n=native[k]
 assert n[86].mnemonic=='cmp' and n[86].op_str.endswith(', 2')
 assert n[90].mnemonic=='cmp' and n[90].op_str.endswith(', 6')
 assert n[110].mnemonic=='push' and n[110].op_str=='6'
 assert n[134].mnemonic=='cmp' and n[134].op_str.endswith(', 3')
 assert n[144].mnemonic=='fmul' and n[144].op_str=='dword ptr [0x6590b8]'
 assert n[152].mnemonic=='fmul' and n[152].op_str=='dword ptr [0x6590b8]'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda ins:tuple(rx.findall(ins.op_str))
results={}
for label,source in variants.items():
 cpp=O/(label+'.cpp');obj=O/(label+'.obj');cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 instructions=[]
 for x in D.disasm(code,0):
  instructions.append(x)
  if x.mnemonic=='ret':break
 end=instructions[-1].address+instructions[-1].size
 assert len(code)-end==data_b
 table=sorted((r for r in refs if r['offset']>=end),key=lambda r:r['offset'])
 assert len(table)==151
 mask=set();labelmap={}
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(k not in mask for k in range(off,off+4))
  mask.update(range(off,off+4))
  target=int.from_bytes(native_data[off:off+4],'little')
  assert base<=target<base+total
  labelmap.setdefault(target,r['local_symbol_offset'])
 assert data_b-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(data_b) if i not in mask)
 row={'whole_partial_source_CODE_B':end,'whole_partial_source_x86':len(instructions),
   'original_whole_CODE_B':total,'original_whole_x86':native_x86,
   'source_COFF_records':len(refs),'original_afterRET_DATA_B':data_b,
   'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal':522,
   'original_cases':{},'whole_original_exact':False}
 for action,(lo,hi,bytes_,nx,nref) in physical.items():
  l,h=labelmap[lo],labelmap[hi]
  I=[x for x in instructions if l<=x.address<h]
  n=native[action]
  fields=[r for r in refs if l<=r['offset']<h]
  case={'original_CODE_B':bytes_,'original_x86':nx,
    'source_CODE_B':h-l,'source_x86':len(I)}
  if len(I)==nx and h-l==bytes_:
   badm=[i for i,(a,b) in enumerate(zip(n,I)) if a.mnemonic!=b.mnemonic]
   badw=[i for i,(a,b) in enumerate(zip(n,I)) if a.size!=b.size]
   badg=[i for i,(a,b) in enumerate(zip(n,I)) if role(a)!=role(b)]
   case.update({'wrong_native_mnemonics':badm,'wrong_native_widths':badw,'wrong_native_GPR_roles':badg})
   if not badm and not badw:
    assert len(fields)==nref,(action,len(fields),nref)
    original=rd.pe_bytes_at(PE,lo,bytes_)
    fieldmask=set()
    for r in fields:
     j=next(i for i,x in enumerate(I) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-I[j].address
     native_offset=n[j].address-lo+delta
     assert native_offset==r['offset']-l
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(original[native_offset:native_offset+4],
        'little',signed=r['type']=='REL32')
     dest=n[j].address+delta+4+value if r['type']=='REL32' else value
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert dest==expected,(action,j,r['symbol'],hex(dest),expected)
     fieldmask.update(range(native_offset,native_offset+4))
    case['native_PE_target_fields_verified']=len(fields)
    nonfield=[i for i in range(bytes_) if i not in fieldmask and original[i]!=code[l+i]]
    case['native_nonfield_wrong_bytes']=len(nonfield)
  row['original_cases'][action]=case
 results[label]=row
 print(label,'whole',end,len(instructions),'0x60',
   (row['original_cases']['0x60']['source_CODE_B'],row['original_cases']['0x60']['source_x86']),
   '0x61',(row['original_cases']['0x61']['source_CODE_B'],row['original_cases']['0x61']['source_x86']),
   'native GPR errors',[len(row['original_cases'][k].get('wrong_native_GPR_roles',[])) for k in ('0x60','0x61')],flush=True)
old=results['F941-previous-markers']
wrong=results['F748-other-actor-parameters']
new=results['F942-original-actor-parameters']
assert (old['whole_partial_source_CODE_B'],old['whole_partial_source_x86'])==(17086,4520)
assert (wrong['whole_partial_source_CODE_B'],wrong['whole_partial_source_x86'])==(18150,4828)
assert (new['whole_partial_source_CODE_B'],new['whole_partial_source_x86'])==(18161,4832)
for action in ('0x60','0x61'):
 assert old['original_cases'][action]['source_CODE_B']==15
 assert new['original_cases'][action]['source_CODE_B']==553
 assert new['original_cases'][action]['source_x86']==158
 assert new['original_cases'][action]['wrong_native_mnemonics']==[]
 assert new['original_cases'][action]['wrong_native_widths']==[]
 assert new['original_cases'][action]['wrong_native_GPR_roles']==[]
 assert new['original_cases'][action]['native_PE_target_fields_verified']==10
 assert new['original_cases'][action]['native_nonfield_wrong_bytes']>0
assert wrong['original_cases']['0x60']['source_CODE_B']==541
assert wrong['original_cases']['0x61']['source_CODE_B']==553
assert len(wrong['original_cases']['0x61']['wrong_native_GPR_roles'])>0
for action in ('0x58','0x59','0x5D','0x5E','0x5F'):
 assert new['original_cases'][action]['source_CODE_B']==physical[action][2]
 assert new['original_cases'][action]['native_PE_target_fields_verified']==physical[action][4]
assert new['original_cases']['0x58']['wrong_native_GPR_roles']==[]
assert new['original_cases']['0x5F']['wrong_native_GPR_roles']==[]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_82KB_fighter':'0x004AC040',
 'native_complete_CODE_B':total,'native_complete_x86':native_x86,
 'true_original_stage60_61_each_B':553,
 'true_original_stage60_61_each_x86':158,
 'true_original_stage60_61_original_typed_PE_targets':20,
 'natural_source_stage60_61_GPR_mnemonic_width_diffs':0,
 'native_real_original_actor_still_wrong_this_EBP':True,
 'new_exact_whole_original_GAME_CODE_B':0,'whole_original_exact':False,
 'mass_cold_replay':False,'compiled_complete_partial_father_profiles':results
},indent=2)+'\n')
print('F942 native original 004AC040 cases60/61: 553B/158x86 each, 20 original typed PE fields, all source GPR/mnemonic/width roles exact; still partial 18,161B vs original 82,796B, NO accepted game CODE.')
