#!/usr/bin/env python3
"""F962 authentic native 004AC040 case131 (202B/58x86) and its 36 GPR debt.

Build four entire original-shaped VC7.1 partial 82KB fighter sources
from TRACKED F961/F962 parents: marker, real ordinary C++, real
stage-const read, real void-return source. Compare genuine original
case131 202B/58x86/5 native external PE field targets and preceding
original 130 with 265B/81x86/6 actual PE refs, the authentic 151
afterRET DIR32 case labels and 522 DATA nonfields. Never credit an
inner case or incomplete full giant as original whole exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f962-third-stage131-proof';O.mkdir(parents=True,exist_ok=True)
prior=(R/'probes/FighterWhole004AC040F961.cpp').read_text()
latest=(R/'probes/FighterWhole004AC040F962.cpp').read_text()
inc=(R/'probes/FighterThirdBossStage131F962.inc').read_text()
marker='#include "FighterThirdBossStage131F962.inc"'
assert latest.count(marker)==1 and inc.count('case 0x131:')==1
assert prior.count('        case 0x131: g_FighterProbeMarker = 306; break;')==1
variations={
 'F961-prior-marker':prior,
 'F962-real-native-131':latest,
 'F962-const-signed-stage':latest.replace(marker,inc.replace(
        'S16(0x62)==5','*reinterpret_cast<const short*>(RAW+0x62)==5'),1),
 'F962-real-void-return':latest.replace(marker,inc.replace('break;','return;'),1),
}
sp=importlib.util.spec_from_file_location('f962reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
realwhole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(realwhole)==NX and realwhole[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
states={'130':(0x4B13C0,0x4B14C9,265,81,6),
        '131':(0x4B14C9,0x4B1593,202,58,5)}
native={}
for key,(lo,hi,n,nx,nf) in states.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,lo,n),lo))
 assert len(I)==nx and hi-lo==n and I[-1].address+I[-1].size==hi
 native[key]=I
assert native['131'][48].op_str=='eax, 5'
assert native['131'][54].op_str=='0x1d'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows={}
for tag,src in variations.items():
 cpp,obj=O/(tag+'.cpp'),O/(tag+'.obj')
 cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  addr=int.from_bytes(native_data[off:off+4],'little')
  assert BASE<=addr<BASE+WHOLE
  labels.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+j]==native_data[j] for j in range(DATA) if j not in mask)
 result={'whole_partial_source_CODE_B':ret,'whole_partial_source_x86':len(I),
         'original_complete_GAME_CODE_B':WHOLE,'original_whole_x86':NX,
         'native_afterRET_real_DIR32_labels':151,
         'native_afterRET_nonfield_bytes_equal':522,
         'source_COFF_total':len(refs),'whole_original_exact':False,'states':{}}
 for key,(a,b,sz,nx,nfields) in states.items():
  assert a in labels and b in labels
  lo,hi=labels[a],labels[b]
  source=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  row={'original_CASE_CODE_B':sz,'native_x86':nx,
       'source_CODE_B':hi-lo,'source_x86':len(source)}
  if len(source)==nx and hi-lo==sz:
   mm=[j for j,(x,y) in enumerate(zip(native[key],source)) if x.mnemonic!=y.mnemonic]
   ww=[j for j,(x,y) in enumerate(zip(native[key],source)) if x.size!=y.size]
   gg=[j for j,(x,y) in enumerate(zip(native[key],source)) if role(x)!=role(y)]
   row.update({'native_wrong_mnemonic_ordinals':mm,
               'native_wrong_width_ordinals':ww,
               'native_wrong_GPR_ordinals':gg})
   if not mm and not ww:
    assert len(fields)==nfields
    pebytes=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(source) if x.address<=r['offset']<x.address+x.size)
     offset=r['offset']-source[j].address
     origoffset=native[key][j].address-a+offset
     assert origoffset==r['offset']-lo
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(pebytes[origoffset:origoffset+4],'little',signed=r['type']=='REL32')
     target=native[key][j].address+offset+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     exp=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==exp,(key,j,r['symbol'],hex(target),exp)
    row['native_original_external_PE_targets_verified']=nfields
  result['states'][key]=row
 rows[tag]=result
 print(tag,'whole',ret,len(I),'131 source B/x86',
  result['states']['131']['source_CODE_B'],result['states']['131']['source_x86'],
  '131 wrong GPR',len(result['states']['131'].get('native_wrong_GPR_ordinals',[])),flush=True)
old=rows['F961-prior-marker'];latest=rows['F962-real-native-131']
assert (old['whole_partial_source_CODE_B'],old['whole_partial_source_x86'])==(22709,6191)
assert (latest['whole_partial_source_CODE_B'],latest['whole_partial_source_x86'])==(22896,6247)
assert old['states']['131']['source_CODE_B']==15
for key in ('F962-real-native-131','F962-const-signed-stage','F962-real-void-return'):
 rec=rows[key]['states']['131']
 assert (rec['source_CODE_B'],rec['source_x86'])==(202,58)
 assert rec['native_wrong_mnemonic_ordinals']==[]
 assert rec['native_wrong_width_ordinals']==[]
 assert len(rec['native_wrong_GPR_ordinals'])==36 and rec['native_wrong_GPR_ordinals'][0]==0
 assert rec['native_original_external_PE_targets_verified']==5
 assert rows[key]['states']['130']['native_wrong_GPR_ordinals']==[]
 assert rows[key]['states']['130']['native_original_external_PE_targets_verified']==6
(O/'verified-summary.json').write_text(json.dumps({
 'native_pinned_Japanese_fighter':'0x004AC040',
 'native_original_whole_CODE_B':WHOLE,'native_whole_x86':NX,
 'original_case131_CODE_B_x86':[202,58],
 'generated_partial_father_new_CASE_B_x86':[202,58],
 'real_native_case131_external_PE_targets':5,
 'native_case131_wrong_mnemonic_or_width':0,
 'native_case131_wrong_GPR':36,
 'real_previous_130_native_GPR_still_all_match':True,
 'private_28_full_source_Cpp_controls_all_fail_to_fix_GPR':True,
 'whole_original_game_exact':False,'accepted_new_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_fathers':rows
},indent=2)+'\n')
print('F962: natural 202B/58 native original case131 with 5 exact original PE targets. 36 native GPR roles (first ordinal0) remain wrong despite 28 whole-parent source alternatives; entire 82KB giant remains NONEXACT.')
