#!/usr/bin/env python3
"""F971: natural 196/197/198 five-shot x86 backed by original full 82KB fighter.

Compile two TRACKED entire normal VC7.1 original-shaped PARTIAL
004AC040 father C++ sources: F970 prior markers, F971 all three real
five-shot actions. Independently validate original PE 507B/146-x86
case interiors, 15 true original typed i386 PE field destinations
per case, distinct multipliers/global float Y sources, original
151 afterRET DIR32 and 522 nonfield DATA bytes. Not whole CODE exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f971-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F970-old-196198-markers':R/'probes/FighterWhole004AC040F970.cpp',
         'F971-real-five-shot':R/'probes/FighterWhole004AC040F971.cpp'}
inc=(R/'probes/FighterThirdBossFiveShot196198F971.inc').read_text()
assert all(inc.count('case 0x'+n+':')==1 for n in ('196','197','198'))
assert sources['F971-real-five-shot'].read_text().count('#include "FighterThirdBossFiveShot196198F971.inc"')==1
sp=importlib.util.spec_from_file_location('f971reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;DATA=1126
origfull=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(origfull)==WHOLEX and origfull[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'195':(0x4B2B71,0x4B2DF5,644,168,11),
       '196':(0x4B2DF5,0x4B2FF0,507,146,15),
       '197':(0x4B2FF0,0x4B31EB,507,146,15),
       '198':(0x4B31EB,0x4B33E6,507,146,15)}
original={}
for k,(a,b,size,nx,nf) in cases.items():
 v=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(v)==nx and v[-1].address+v[-1].size==b
 original[k]=v
native_values={
 '196':{'stage':6,'end':0,'angle':0,'xs':[39,44,49,54,59],
        'ys':[0x659494,0x659490,0x659294,0x65948c,0x659488]},
 '197':{'stage':5,'end':0,'angle':25,'xs':[85,91,97,103,109],
        'ys':[0x659484,0x659480,0x659498,0x65947c,0x659478]},
 '198':{'stage':6,'end':2,'angle':0,'xs':[92,98,104,110,116],
        'ys':[0x65826c,0x658264,0x658294,0x657878,0x657cbc]}}
for k,c in native_values.items():
 n=original[k]
 assert n[24].op_str.split(', ')[1]==str(c['stage'])
 assert n[19].op_str==str(c['end'])
 assert n[34].op_str.endswith(', '+('0' if c['angle']==0 else '0x41c80000'))
 assert [n[j].op_str for j in (43,64,85,106,127)]==[f'dword ptr [0x{x:x}]' for x in c['ys']]
 assert [int(n[j].op_str.split(', ')[-1],16) for j in (48,69,90,111,132)]==c['xs']
 assert all(n[j].op_str=='0x328' for j in (55,76,97,118,139))
 assert all(n[j].op_str=='0x453a70' for j in (57,78,99,120,141))
 assert n[144].op_str=='0x46d000'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(rx.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,capture_output=True,text=True,timeout=350)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 jump=[r for r in refs if r['offset']>=end]
 assert len(jump)==151
 mp={};mask=set()
 for r in jump:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(z not in mask for z in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  mp.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in mp and b in mp for a,b,_,_,_ in cases.values())
 row={'original_entire_callable_GAME_CODE_B':WHOLE,
      'original_entire_GAME_x86':WHOLEX,
      'partial_full_CPP_CODE_B':end,'partial_full_CPP_x86':len(I),
      'native_afterRET_DIR32':151,'native_afterRET_nonfield_bytes':522,
      'source_COFF_field_count':len(refs),'native_source_cases':{},
      'entire_original_GAME_exact':False}
 for action,(a,b,size,nx,nf) in cases.items():
  lo,hi=mp[a],mp[b]
  s=[x for x in I if lo<=x.address<hi]
  refs_local=[r for r in refs if lo<=r['offset']<hi]
  status={'native_original_CODE_B':size,'native_original_x86':nx,
          'CPP_source_CODE_B':hi-lo,'CPP_source_x86':len(s)}
  if len(s)==nx:
   m=[j for j,(v,w) in enumerate(zip(original[action],s)) if v.mnemonic!=w.mnemonic]
   w=[j for j,(v,w) in enumerate(zip(original[action],s)) if v.size!=w.size]
   g=[j for j,(v,w) in enumerate(zip(original[action],s)) if role(v)!=role(w)]
   status.update({'native_mnemonic_wrong_ordinals':m,
                  'native_width_wrong_ordinals':w,
                  'native_GPR_wrong_ordinals':g})
   if not m:
    assert len(refs_local)==nf,(label,action,len(refs_local),nf)
    actualbytes=rd.pe_bytes_at(PE,a,size)
    for r in refs_local:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-s[j].address
     origoff=original[action][j].address-a+delta
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     num=int.from_bytes(actualbytes[origoff:origoff+4],
                        'little',signed=r['type']=='REL32')
     target=original[action][j].address+delta+4+num if r['type']=='REL32' else num
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,action,j,r['symbol'],hex(target),expected)
    status['original_PE_targets_checked']=len(refs_local)
  row['native_source_cases'][action]=status
 rows[label]=row
 print(label,'whole partial source',end,len(I),'native 196/197/198',
       [(c,row['native_source_cases'][c]['CPP_source_CODE_B'],row['native_source_cases'][c]['CPP_source_x86'])
       for c in ('196','197','198')],flush=True)
old=rows['F970-old-196198-markers'];new=rows['F971-real-five-shot']
assert (old['partial_full_CPP_CODE_B'],old['partial_full_CPP_x86'])==(28868,7910)
assert (new['partial_full_CPP_CODE_B'],new['partial_full_CPP_x86'])==(30344,8342)
for case in ('196','197','198'):
 assert old['native_source_cases'][case]['CPP_source_CODE_B']==15
 n=new['native_source_cases'][case]
 assert (n['CPP_source_CODE_B'],n['CPP_source_x86'])==(507,146)
 assert n['native_mnemonic_wrong_ordinals']==n['native_width_wrong_ordinals']==[]
 assert len(n['native_GPR_wrong_ordinals'])==77
 assert n['original_PE_targets_checked']==15
assert new['native_source_cases']['195']['original_PE_targets_checked']==11
(O/'verified-summary.json').write_text(json.dumps({
 'native_Japanese_original_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':WHOLE,'original_entire_x86':WHOLEX,
 'original_three_five_shot_CASE_CODE_B_x86':[507*3,146*3],
 'generated_three_five_shot_CPP_B_x86':[507*3,146*3],
 'all_three_native_mnemonic_and_width_roles_match':True,
 'all_fifteen_true_PE_external_targets_each':True,
 'native_all_external_PE_targets_checked':45,
 'original_GPR_wrong_per_CASE':[77,77,77],
 'complete_original_exact':False,'newly_accepted_original_callable_GAME_CODE_B':0,
 'mass_cold_replay':False,
 'complete_partial_father_profiles':rows,
},indent=2)+'\n')
print('F971 three original five-shot cases 1521 native CODE B/438x86, all original mnemonics and widths, 45 true PE fields; GPR 77 per case. Entire 82KB father NONEXACT.')
