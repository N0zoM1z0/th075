#!/usr/bin/env python3
"""F953: original 004AC040 CC and CD with true 435B/128x86 and 11 PE fields each.

Rebuild four COMPLETE original-shaped partial 82KB fighter C++ fathers
under pinned VC7.1. Original Japanese target dictates complete case
boundaries, x86 mnemonics/width/GPR, every physical i386 PE external
target and whole 1,126B afterRET table (151 DIR32 + 522 nonfield B).
Never label internal switch case or partial father exact.
"""
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import os, re, sys, json, subprocess, importlib.util
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f953-third-cc-cd-proof'; O.mkdir(parents=True,exist_ok=True)
source=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
before=[
 (0x5D,94,'FighterThirdBossPair5D5EF939.inc'),
 (0x5E,95,None),(0x5F,96,'FighterThirdBossFacing5FF941.inc'),
 (0x60,97,'FighterThirdBossVolley6061F942.inc'),
 (0x61,98,None),(0x62,99,'FighterThirdBossSelector62F943.inc'),
 (0xC8,201,'FighterThirdBossFourWayC8F948.inc'),
 (0xC9,202,'FighterThirdBossFourWayC9F949.inc'),
 (0xCA,203,'FighterThirdBossFourWayCAF950.inc'),
 (0xCB,204,'FighterThirdBossFourWayCBF951.inc'),
 (0xCF,208,'FighterFallStateCFF647.inc'),
 (0xD0,209,'FighterReflectLandingD0F646.inc'),
]
for action,marker,file in before:
 old=f'        case 0x{action:X}: g_FighterProbeMarker = {marker}; break;'
 assert source.count(old)==1,(action,marker)
 source=source.replace(old,(R/'probes'/file).read_text() if file else '',1)
method=' void SpawnAt453C80(int,float,float,char,int);'
assert source.count(method)==1
source=source.replace(method,method+
 ' void SpawnMixedAt453C80(int,int,float,char,int);'
 ' void ConfigureStormAt454BC0(int,int,int);'
 ' void SpawnRawAt453C80(int,int,int,char,int);',1)
marker='extern float g_ThresholdAt0065782C;'
assert source.count(marker)==1
source=source.replace(marker,'''extern float g_F748_SpeedScaleAt006590B8;
extern float g_F948_C8UpperAt00657854;
extern float g_F948_C8DragAt00658350;
extern float g_F948_C8VolleyYAt00658268;
extern float g_F950_CAVolleyYAt00658400;
'''+marker,1)
cc=(R/'probes/FighterThirdBossCCF953.inc').read_text()
cd=(R/'probes/FighterThirdBossCDF953.inc').read_text()
oldcc='        case 0xCC: g_FighterProbeMarker = 205; break;'
oldcd='        case 0xCD: g_FighterProbeMarker = 206; break;'
assert source.count(oldcc)==source.count(oldcd)==1
versions={
 'prior-markers':source,
 'CC-only':source.replace(oldcc,cc,1),
 'CD-only':source.replace(oldcd,cd,1),
 'CC-and-CD':source.replace(oldcc,cc,1).replace(oldcd,cd,1)
}
sp=importlib.util.spec_from_file_location('f953reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
BASE=0x4AC040; CODE=82796; NX=22721; DATA=1126
native_full=list(D.disasm(rd.pe_bytes_at(PE,BASE,CODE),BASE))
assert len(native_full)==NX and native_full[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+CODE,DATA)
physical={'CC':(0x4B0852,0x4B0A05,435,128,11),
          'CD':(0x4B0A05,0x4B0BB8,435,128,11),
          'CF':(0x4B0D42,0x4B0DB4,114,30,4),
          'D0':(0x4B0DB4,0x4B0E77,195,60,6)}
orig={}
for name,(a,b,sz,nx,_) in physical.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(n)==nx and b-a==sz
 orig[name]=n
# Source/PE semantics at original action transition, not historical F649.
assert orig['CC'][91].op_str=='edx, 3'
assert orig['CD'][91].op_str=='edx, 2'
assert orig['CC'][103].op_str==orig['CD'][103].op_str=='0x453c80'
assert orig['CC'][107].op_str=='dword ptr [edx + 0x54], 0x41a00000'
assert orig['CD'][107].op_str=='dword ptr [edx + 0x54], 0x41700000'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for name,src in versions.items():
 cpp,obj=O/(name+'.cpp'),O/(name+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
    cwd=R,env=env,text=True,capture_output=True,timeout=350)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 instructions=[]
 for x in D.disasm(code,0):
  instructions.append(x)
  if x.mnemonic=='ret':break
 ret=instructions[-1].address+instructions[-1].size
 assert len(code)-ret==DATA
 jump=[r for r in refs if r['offset']>=ret]
 assert len(jump)==151
 physicalmap={}; mask=set()
 for r in jump:
  o=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(o,o+4))
  mask.update(range(o,o+4))
  native_va=int.from_bytes(after[o:o+4],'little')
  assert BASE<=native_va<BASE+CODE
  physicalmap.setdefault(native_va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+i]==after[i] for i in range(DATA) if i not in mask)
 row={'partial_whole_source_B':ret,'partial_whole_source_x86':len(instructions),
      'original_whole_B':CODE,'original_whole_x86':NX,
      'all_source_COFF_fields':len(refs),'afterRET_DATA_B':DATA,
      'native_afterRET_DIR32_fields':151,
      'native_afterRET_nonfield_equal_B':522,
      'cases':{},'original_whole_exact':False}
 for case,(a,b,sz,nx,nfields) in physical.items():
  assert a in physicalmap and b in physicalmap
  lo,hi=physicalmap[a],physicalmap[b]
  s=[x for x in instructions if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  record={'native_B':sz,'native_x86':nx,'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx and hi-lo==sz:
   m=[i for i,(x,y) in enumerate(zip(orig[case],s)) if x.mnemonic!=y.mnemonic]
   w=[i for i,(x,y) in enumerate(zip(orig[case],s)) if x.size!=y.size]
   g=[i for i,(x,y) in enumerate(zip(orig[case],s)) if roles(x)!=roles(y)]
   record.update({'wrong_native_mnemonic_ordinals':m,'wrong_native_width_ordinals':w,
                  'wrong_native_GPR_ordinals':g})
   if not m and not w:
    assert len(fields)==nfields
    pe_raw=rd.pe_bytes_at(PE,a,sz)
    for ref in fields:
     i=next(i for i,x in enumerate(s) if x.address<=ref['offset']<x.address+x.size)
     delta=ref['offset']-s[i].address
     origoff=orig[case][i].address-a+delta
     assert ref['type'] in ('REL32','DIR32') and ref['addend']==0 and ref['local_symbol_offset'] is None
     v=int.from_bytes(pe_raw[origoff:origoff+4],'little',signed=ref['type']=='REL32')
     target=orig[case][i].address+delta+4+v if ref['type']=='REL32' else v
     f=re.search(r'At([0-9A-Fa-f]{6,8})',ref['symbol'])
     expected=int(f.group(1),16) if f else 0x6406AC if ref['symbol']=='__ftol2' else None
     assert target==expected,(case,i,ref['symbol'],hex(target),expected)
    record['actual_original_PE_targets_verified']=nfields
  row['cases'][case]=record
 results[name]=row
 print(name,'whole source',ret,len(instructions),
 'CC',row['cases']['CC']['source_B'],row['cases']['CC']['source_x86'],
 'CD',row['cases']['CD']['source_B'],row['cases']['CD']['source_x86'],
 'GPR mismatch',[(c,len(row['cases'][c].get('wrong_native_GPR_ordinals',[]))) for c in ('CC','CD')],flush=True)
o=results['prior-markers'];both=results['CC-and-CD']
assert (o['partial_whole_source_B'],o['partial_whole_source_x86'])==(20397,5494)
assert (both['partial_whole_source_B'],both['partial_whole_source_x86'])==(21237,5746)
for case in ('CC','CD'):
 assert o['cases'][case]['source_B']==15
 assert (both['cases'][case]['source_B'],both['cases'][case]['source_x86'])==(435,128)
 assert both['cases'][case]['wrong_native_mnemonic_ordinals']==[]
 assert both['cases'][case]['wrong_native_width_ordinals']==[]
 assert both['cases'][case]['actual_original_PE_targets_verified']==11
assert len(both['cases']['CC']['wrong_native_GPR_ordinals'])==77
assert both['cases']['CD']['wrong_native_GPR_ordinals']==[]
for case in ('CF','D0'):
 assert both['cases'][case]['actual_original_PE_targets_verified']==physical[case][4]
assert results['CC-only']['cases']['CC']['source_B']==435
assert results['CD-only']['cases']['CD']['source_B']==435
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x004AC040','complete_original_GAME_B':CODE,
 'original_GAME_x86':NX,'new_original_CC_native_B_x86':[435,128],
 'new_original_CD_native_B_x86':[435,128],
 'original_CC_CD_PE_targets_checked':22,
 'CD_all_128_native_GPR_mnemonic_width_roles_match':True,
 'CC_wrong_native_GPR_instr':77,'whole_original_exact':False,
 'newly_accepted_whole_game_CODE_B':0,'mass_cold_replay':False,
 'full_parent_partial_source_profiles':results
},indent=2)+'\n')
print('F953 native original CC+CD complete natural states: each 435B/128x86/11 true PE targets, native mnemonic/width exact; CD ALL 128 GPR roles align, CC 77 do not. 82KB whole game remains NONEXACT.')
