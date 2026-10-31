#!/usr/bin/env python3
"""F978 pinned original complete-partial-father 1A2 dual native 5-shot proof.

Fresh compile TRACKED F977 markers and F978 real original-shaped whole
82KB fighter parents, compare original game PE 1A2 1142B/309 x86 and
all 24 source PE/COFF physical typed destinations. Check 1A1 preceding
native geometry, complete 151 afterRET local DIR32 +522 DATA nonfields.
NO inner-case or partial whole source exact acceptance.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f978-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F977-marker':R/'probes/FighterWhole004AC040F977.cpp',
         'F978-real':R/'probes/FighterWhole004AC040F978.cpp'}
inc=(R/'probes/FighterThirdBossDualFiveShot1A2F978.inc').read_text()
assert inc.count('case 0x1A2:')==1 and inc.count('SpawnSevenFloatAt453B50(')==10
assert inc.count('if (*reinterpret_cast<signed char*>(RAW+0x39D)==2)')==1
sp=importlib.util.spec_from_file_location('readf978',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
BASE=0x4AC040;NATIVE_LEN=82796;NATIVE_INS=22721;AFTER=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE_LEN),BASE))
assert len(whole)==NATIVE_INS and whole[2].op_str=='esp, 0x720'
post=rd.pe_bytes_at(PE,BASE+NATIVE_LEN,AFTER)
cases={'1A1':(0x4B42D1,0x4B450B,570,151,12),
       '1A2':(0x4B450B,0x4B4981,1142,309,24)}
native={}
for case,(a,b,size,nx,fields) in cases.items():
 v=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert len(v)==nx and b-a==size and v[-1].address+v[-1].size==b
 native[case]=v
n=native['1A2']
assert n[35].op_str.endswith(', 2')
assert [n[j].op_str for j in (61,88,115,142,169,197,224,251,278,305)]==['0x344']*10
assert [n[j].op_str for j in (63,90,117,144,171,199,226,253,280,307)]==['0x453b50']*10
assert [n[j].op_str for j in (38,65,92,119,146,174,201,228,255,282)]==[
    'dword ptr [eax + 0x314], 0x42820000',
    'dword ptr [edx + 0x314], 0x425c0000',
    'dword ptr [ecx + 0x314], 0x42340000',
    'dword ptr [eax + 0x314], 0x420c0000',
    'dword ptr [edx + 0x314], 0x41c80000',
    'dword ptr [ecx + 0x314], 0x42820000',
    'dword ptr [eax + 0x314], 0x425c0000',
    'dword ptr [edx + 0x314], 0x42340000',
    'dword ptr [ecx + 0x314], 0x420c0000',
    'dword ptr [eax + 0x314], 0x41c80000']
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for name,cpp in sources.items():
 obj=O/(name+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==AFTER
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  target=int.from_bytes(post[off:off+4],'little')
  assert BASE<=target<BASE+NATIVE_LEN
  labels.setdefault(target,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[ret+i]==post[i] for i in range(AFTER) if i not in mask)
 row={'original_whole_GAME_CODE_B':NATIVE_LEN,'original_x86':NATIVE_INS,
      'source_whole_partial_B':ret,'source_partial_x86':len(I),
      'source_COFF_relocs':len(refs),'original_afterRET_DIR32':151,
      'original_afterRET_nonfield_B_exact':522,
      'source_cases':{},'entire_original_exact':False}
 for key,(a,b,size,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':size,'original_x86':nx,
        'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   badm=[j for j,(x,y) in enumerate(zip(native[key],s)) if x.mnemonic!=y.mnemonic]
   badw=[j for j,(x,y) in enumerate(zip(native[key],s)) if x.size!=y.size]
   badg=[j for j,(x,y) in enumerate(zip(native[key],s)) if roles(x)!=roles(y)]
   item.update({'wrong_mnemonic_ordinals':badm,'wrong_width_ordinals':badw,
                'wrong_GPR_ordinals':badg})
   if not badm:
    assert len(fields)==nf,(name,key,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,size)
    for field in fields:
     j=next(j for j,x in enumerate(s) if x.address<=field['offset']<x.address+x.size)
     d=field['offset']-s[j].address
     native_off=native[key][j].address-a+d
     assert field['type'] in ('REL32','DIR32') and field['addend']==0 and field['local_symbol_offset'] is None
     v=int.from_bytes(raw[native_off:native_off+4],'little',signed=field['type']=='REL32')
     addr=native[key][j].address+d+4+v if field['type']=='REL32' else v
     m=re.search(r'At([0-9A-Fa-f]{6,8})',field['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if field['symbol']=='__ftol2' else None
     assert addr==expected,(name,key,j,field['symbol'],hex(addr),expected)
    item['original_PE_targets_verified']=nf
  row['source_cases'][key]=item
 results[name]=row
 print(name,'whole source',ret,len(I),'1A2 B/x86',
   row['source_cases']['1A2']['source_B'],row['source_cases']['1A2']['source_x86'],flush=True)
old=results['F977-marker'];new=results['F978-real']
assert (old['source_whole_partial_B'],old['source_partial_x86'])==(34624,9492)
assert (new['source_whole_partial_B'],new['source_partial_x86'])==(35751,9799)
assert old['source_cases']['1A2']['source_B']==15
s=new['source_cases']['1A2']
assert (s['source_B'],s['source_x86'])==(1142,309)
assert s['wrong_mnemonic_ordinals']==s['wrong_width_ordinals']==[]
assert len(s['wrong_GPR_ordinals'])==171
assert s['original_PE_targets_verified']==24
assert new['source_cases']['1A1']['original_PE_targets_verified']==12
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_82KB_fighter':'0x004AC040',
 'native_complete_callable_B':NATIVE_LEN,'native_complete_x86':NATIVE_INS,
 'native_1A2_original_CODE_B_x86':[1142,309],
 'native_1A2_real_external_PE_targets':24,
 'native_source_1A2_mnemonic_width_match':True,
 'native_1A2_wrong_GPR_roles':171,
 'original_two_real_distinct_five_shot_branches':True,
 'original_whole_exact':False,'new_accepted_native_GAME_CODE_B':0,
 'mass_cold_replay':False,'full_original_shaped_CPP_profiles':results
},indent=2)+'\n')
print('F978 original1A2 1142B/309x86/24 physical PE fields, all mnemonic/width positions match; 171 GPR roles wrong. 82KB parent NONEXACT.')
