#!/usr/bin/env python3
"""F955: original 82KB Fighter's authentic CE state and CC/CD preceding GPR phase.

Four complete normal VC7.1 source parents (old CE marker, CE alone,
CC/CD real with CE marker, CC/CD/CE all real). Verify 394B/115-x86
original CE, real nine original typed PE targets, 435B/128-x86
original CC/CD where source-backed, and original 1,126B afterRET
151 DIR32 physical labels/522 nonfield bytes. No whole-function
original exactness or clipped case credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f955-third-ce-phase-proof';O.mkdir(parents=True,exist_ok=True)
source=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
predecessors=[
 (0x5D,94,'FighterThirdBossPair5D5EF939.inc'),
 (0x5E,95,None),(0x5F,96,'FighterThirdBossFacing5FF941.inc'),
 (0x60,97,'FighterThirdBossVolley6061F942.inc'),
 (0x61,98,None),(0x62,99,'FighterThirdBossSelector62F943.inc'),
 (0xC8,201,'FighterThirdBossFourWayC8F948.inc'),
 (0xC9,202,'FighterThirdBossFourWayC9F949.inc'),
 (0xCA,203,'FighterThirdBossFourWayCAF950.inc'),
 (0xCB,204,'FighterThirdBossFourWayCBF951.inc'),
 (0xCF,208,'FighterFallStateCFF647.inc'),
 (0xD0,209,'FighterReflectLandingD0F646.inc')]
for action,marker,name in predecessors:
 old=f'        case 0x{action:X}: g_FighterProbeMarker = {marker}; break;'
 assert source.count(old)==1
 source=source.replace(old,(R/'probes'/name).read_text() if name else '',1)
needle=' void SpawnAt453C80(int,float,float,char,int);'
assert source.count(needle)==1
source=source.replace(needle,needle+
 ' void SpawnMixedAt453C80(int,int,float,char,int);'
 ' void ConfigureStormAt454BC0(int,int,int);'
 ' void SpawnRawAt453C80(int,int,int,char,int);',1)
needle='extern float g_ThresholdAt0065782C;'
assert source.count(needle)==1
source=source.replace(needle,'''extern float g_F748_SpeedScaleAt006590B8;
extern float g_F948_C8UpperAt00657854;
extern float g_F948_C8DragAt00658350;
extern float g_F948_C8VolleyYAt00658268;
extern float g_F950_CAVolleyYAt00658400;
'''+needle,1)
cc=(R/'probes/FighterThirdBossCCF953.inc').read_text()
cd=(R/'probes/FighterThirdBossCDF953.inc').read_text()
ce=(R/'probes/FighterThirdBossCEF955.inc').read_text()
marks={'CC':'        case 0xCC: g_FighterProbeMarker = 205; break;',
       'CD':'        case 0xCD: g_FighterProbeMarker = 206; break;',
       'CE':'        case 0xCE: g_FighterProbeMarker = 207; break;'}
assert all(source.count(x)==1 for x in marks.values())
variants={
 'prior-CC-CD-CE-markers':source,
 'CE-alone':source.replace(marks['CE'],ce,1),
 'CC-CD-with-CE-marker':source.replace(marks['CC'],cc,1).replace(marks['CD'],cd,1),
 'CC-CD-and-CE':source.replace(marks['CC'],cc,1).replace(marks['CD'],cd,1).replace(marks['CE'],ce,1)
}
sp=importlib.util.spec_from_file_location('readerF955',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
original_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original_whole)==NX and original_whole[2].op_str=='esp, 0x720'
original_data=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={
 'CC':(0x4B0852,0x4B0A05,435,128,11),
 'CD':(0x4B0A05,0x4B0BB8,435,128,11),
 'CE':(0x4B0BB8,0x4B0D42,394,115,9),
 'CF':(0x4B0D42,0x4B0DB4,114,30,4),
 'D0':(0x4B0DB4,0x4B0E77,195,60,6),
}
native={}
for key,(lo,hi,n,nx,fields) in cases.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,lo,n),lo))
 assert hi-lo==n and len(I)==nx and I[-1].address+I[-1].size==hi
 native[key]=I
# Genuine actor-specific CE differs from CC/CD:
assert native['CE'][78].op_str=='edx, 3'
assert native['CE'][92].op_str=='dword ptr [ecx + 0x50], 0xc1200000'
assert native['CE'][94].op_str=='dword ptr [edx + 0x54], 0x41700000'
assert native['CE'][96].op_str=='dword ptr [eax + 0x5c], 0x3f333333'
assert native['CE'][90].op_str=='0x453c80'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
records={}
for label,src in variants.items():
 cpp=O/(label+'.cpp');obj=O/(label+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=350)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for i in D.disasm(code,0):
  I.append(i)
  if i.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 source_table=[r for r in refs if r['offset']>=end]
 assert len(source_table)==151
 labels={};mask=set()
 for r in source_table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(k not in mask for k in range(off,off+4))
  mask.update(range(off,off+4))
  orig_va=int.from_bytes(original_data[off:off+4],'little')
  assert BASE<=orig_va<BASE+WHOLE
  labels.setdefault(orig_va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+k]==original_data[k] for k in range(DATA) if k not in mask)
 row={'partial_whole_compiled_CODE_B':end,'partial_whole_x86':len(I),
      'original_whole_CODE_B':WHOLE,'original_whole_x86':NX,
      'whole_source_COFF_field_count':len(refs),
      'separate_afterRET_native_DIR32':151,
      'separate_afterRET_nonfield_native_bytes_equal':522,
      'real_cases':{},'native_whole_game_exact':False}
 for action,(a,b,sz,nx,nrefs) in cases.items():
  assert a in labels and b in labels
  lo,hi=labels[a],labels[b]
  ins=[x for x in I if lo<=x.address<hi]
  owned=[r for r in refs if lo<=r['offset']<hi]
  entry={'native_original_B':sz,'native_original_x86':nx,
         'compiled_source_B':hi-lo,'compiled_source_x86':len(ins)}
  if len(ins)==nx and hi-lo==sz:
   mm=[j for j,(n,s) in enumerate(zip(native[action],ins)) if n.mnemonic!=s.mnemonic]
   ww=[j for j,(n,s) in enumerate(zip(native[action],ins)) if n.size!=s.size]
   gg=[j for j,(n,s) in enumerate(zip(native[action],ins)) if roles(n)!=roles(s)]
   entry.update({'wrong_mnemonic_ordinals':mm,'wrong_width_ordinals':ww,
                 'wrong_GPR_role_ordinals':gg})
   if not mm and not ww:
    assert len(owned)==nrefs
    pe_bytes=rd.pe_bytes_at(PE,a,sz)
    for r in owned:
     j=next(j for j,x in enumerate(ins) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-ins[j].address
     origoff=native[action][j].address-a+dt
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(pe_bytes[origoff:origoff+4],'little',signed=r['type']=='REL32')
     target=native[action][j].address+dt+4+value if r['type']=='REL32' else value
     match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(match.group(1),16) if match else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(action,j,r['symbol'],hex(target),expected)
    entry['actual_original_PE_targets_validated']=nrefs
  row['real_cases'][action]=entry
 records[label]=row
 print(label,'whole',end,len(I),
       'CE B/x86',row['real_cases']['CE']['compiled_source_B'],
       row['real_cases']['CE']['compiled_source_x86'],
       'GPR wrong',len(row['real_cases']['CE'].get('wrong_GPR_role_ordinals',[])),flush=True)
prior=records['prior-CC-CD-CE-markers']
alone=records['CE-alone']
before=records['CC-CD-with-CE-marker']
allreal=records['CC-CD-and-CE']
assert (prior['partial_whole_compiled_CODE_B'],prior['partial_whole_x86'])==(20397,5494)
assert (before['partial_whole_compiled_CODE_B'],before['partial_whole_x86'])==(21237,5746)
assert (allreal['partial_whole_compiled_CODE_B'],allreal['partial_whole_x86'])==(21616,5859)
assert (alone['partial_whole_compiled_CODE_B'],alone['partial_whole_x86'])==(20776,5607)
assert prior['real_cases']['CE']['compiled_source_B']==15
for name in ('CE-alone','CC-CD-and-CE'):
 e=records[name]['real_cases']['CE']
 assert (e['compiled_source_B'],e['compiled_source_x86'])==(394,115)
 assert e['wrong_mnemonic_ordinals']==e['wrong_width_ordinals']==[]
 assert e['actual_original_PE_targets_validated']==9
assert len(alone['real_cases']['CE']['wrong_GPR_role_ordinals'])==72
assert allreal['real_cases']['CE']['wrong_GPR_role_ordinals']==[]
for name in ('CC','CD','CF','D0'):
 assert allreal['real_cases'][name]['actual_original_PE_targets_validated']==cases[name][4]
assert len(prior['real_cases']['CF']['wrong_GPR_role_ordinals'])==18
assert len(prior['real_cases']['D0']['wrong_GPR_role_ordinals'])==35
for enabled in (alone,before,allreal):
 for action in ('CF','D0'):
  assert enabled['real_cases'][action]['wrong_mnemonic_ordinals']==[]
  assert enabled['real_cases'][action]['wrong_width_ordinals']==[]
  assert enabled['real_cases'][action]['wrong_GPR_role_ordinals']==[]
assert len(allreal['real_cases']['CC']['wrong_GPR_role_ordinals'])==77
assert allreal['real_cases']['CD']['wrong_GPR_role_ordinals']==[]
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_whole_fighter':'0x004AC040',
 'complete_original_callable_CODE_B':WHOLE,'original_whole_x86':NX,
 'real_CE_original_B_x86':[394,115],'real_CE_external_PE_targets':9,
 'CD_CE_following_register_phase_from_true_CC_CD':True,
 'native_CE_GPR_errors_if_previous_CC_CD_markers':72,
 'native_CE_GPR_errors_if_predecessors_real':0,
 'native_CF_previous_GPR_errors':18,
 'native_D0_previous_GPR_errors':35,
 'native_CF_D0_roles_restored_if_CE_alone_or_CC_CD_real':True,
 'complete_original_game_exact':False,'new_accepted_whole_game_CODE_B':0,
 'mass_cold_replay':False,'whole_partial_parent_profiles':records
},indent=2)+'\n')
print('F955: source-authored original CE 394B/115x86/9 typed PE fields. Native CE GPR phase 72 wrong when alone but all 115 correct when preceded by genuine CC+CD. Entire fighter nonexact.')
