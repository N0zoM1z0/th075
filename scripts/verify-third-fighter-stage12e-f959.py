#!/usr/bin/env python3
"""F959: real third-fighter 12E (270B/82x86/7 fields) in a whole partial father.

Fresh-compile both tracked F958 and F959 selected normal VC7.1
whole-source partial parents. Compare all 12C/12D/12E original
internal states and earlier genuine D2 end. Source 12C has NO
physical original afterRET entry; do not invent one. All 19
genuine original external PE targets, 151 original afterRET
DIR32 label relocations and 522 original nonfield DATA bytes.
No independent case or incomplete whole-giant exact code credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import os,sys,re,json,subprocess,importlib.util
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f959-third-stage12e-proof';O.mkdir(parents=True,exist_ok=True)
sources={
 'F958-old-12E-marker':R/'probes/FighterWhole004AC040F958.cpp',
 'F959-real-12E':R/'probes/FighterWhole004AC040F959.cpp'}
assert sources['F958-old-12E-marker'].read_text().count('        case 0x12E: g_FighterProbeMarker = 303; break;')==1
assert sources['F959-real-12E'].read_text().count('#include "FighterThirdBossStage12EF959.inc"')==1
inc=(R/'probes/FighterThirdBossStage12EF959.inc').read_text()
assert inc.count('case 0x12E:')==1 and inc.count('SpawnSevenAt453B50')==1
sp=importlib.util.spec_from_file_location('f959reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
N=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(N)==NX and N[-1].address+N[-1].size==BASE+WHOLE
native_data=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
actual={
 'D2':(0x4B0F3E,0x4B1039,251,74,0),
 '12C':(0x4B1039,0x4B1108,207,59,6),
 '12D':(0x4B1108,0x4B11E3,219,61,6),
 '12E':(0x4B11E3,0x4B12F1,270,82,7)}
native={}
for k,(a,b,sz,nx,fields) in actual.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
assert not any(int.from_bytes(native_data[i:i+4],'little')==0x4B1039
               for i in range(DATA-3))
assert native['12E'][78].op_str=='0x333' and native['12E'][80].op_str=='0x453b50'
assert native['12E'][55].op_str=='0x1d'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
records={}
for name,cpp in sources.items():
 obj=O/(name+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
    cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  target=int.from_bytes(native_data[off:off+4],'little')
  assert BASE<=target<BASE+WHOLE
  labels.setdefault(target,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(DATA) if i not in mask)
 assert 0x4B1039 not in labels
 assert all(a in labels for a in (0x4B0F3E,0x4B1108,0x4B11E3,0x4B12F1))
 d2start=labels[0x4B0F3E]
 d2i=next(j for j,x in enumerate(I) if x.address==d2start)
 d2=I[d2i:d2i+74]
 boundary12c=d2[-1].address+d2[-1].size
 assert len(d2)==74 and boundary12c-d2start==251
 assert [x.mnemonic for x in d2]==[x.mnemonic for x in native['D2']]
 assert [x.size for x in d2]==[x.size for x in native['D2']]
 row={'original_whole_CODE_B':WHOLE,'original_whole_x86':NX,
      'source_partial_whole_CODE_B':end,'source_partial_whole_x86':len(I),
      'native_12C_has_no_afterRET_label':True,
      'native_D2_to_12C_physically_contiguous':True,
      'source_COFF_fields_total':len(refs),
      'original_afterRET_DIR32_labels':151,
      'original_afterRET_nonfield_bytes_equal':522,
      'original_states':{},'original_whole_exact':False}
 for state,(a,b,sz,nx,nf) in actual.items():
  if state=='D2':continue
  lo=boundary12c if state=='12C' else labels[a]
  hi=labels[b]
  src=[x for x in I if lo<=x.address<hi]
  f=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':sz,'original_native_x86':nx,
        'generated_B':hi-lo,'generated_x86':len(src),
        'native_original_PE_fields_checked':0}
  if len(src)==nx and hi-lo==sz:
   m=[j for j,(x,y) in enumerate(zip(native[state],src)) if x.mnemonic!=y.mnemonic]
   w=[j for j,(x,y) in enumerate(zip(native[state],src)) if x.size!=y.size]
   g=[j for j,(x,y) in enumerate(zip(native[state],src)) if roles(x)!=roles(y)]
   item.update({'wrong_mnemonics':m,'wrong_widths':w,'wrong_GPR_roles':g})
   if not m and not w:
    assert len(f)==nf
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in f:
     j=next(j for j,x in enumerate(src) if x.address<=r['offset']<x.address+x.size)
     disp=r['offset']-src[j].address
     off=native[state][j].address-a+disp
     assert off==r['offset']-lo
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[state][j].address+disp+4+val if r['type']=='REL32' else val
     mm=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(mm.group(1),16) if mm else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(state,j,r['symbol'],hex(target),expected)
    item['native_original_PE_fields_checked']=len(f)
  row['original_states'][state]=item
 records[name]=row
 print(name,'whole partial source',end,len(I),'native 12C/D/E source B',
       [row['original_states'][k]['generated_B'] for k in ('12C','12D','12E')],flush=True)
old=records['F958-old-12E-marker'];new=records['F959-real-12E']
assert (old['source_partial_whole_CODE_B'],old['source_partial_whole_x86'])==(22012,5975)
assert (new['source_partial_whole_CODE_B'],new['source_partial_whole_x86'])==(22267,6055)
assert old['original_states']['12E']['generated_B']==15
for k in ('12C','12D','12E'):
 e=new['original_states'][k]
 assert (e['generated_B'],e['generated_x86'])==actual[k][2:4]
 assert e['wrong_mnemonics']==e['wrong_widths']==e['wrong_GPR_roles']==[]
 assert e['native_original_PE_fields_checked']==actual[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':WHOLE,'original_whole_x86':NX,
 'native_12C_12D_12E_CODE_B':207+219+270,
 'native_12C_12D_12E_x86':59+61+82,
 'all_three_native_mnemonic_width_GPR_roles_match':True,
 'native_original_external_PE_targets_total':19,
 'original_12C_no_afterRET_table_entry':True,
 'whole_original_exact':False,'newly_accepted_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_source_profiles':records
},indent=2)+'\n')
print('F959: real 12E 270B/82 native x86 with 7 original PE targets; all three contiguous stage12C/D/E cases 696B/202x86/19 targets have zero wrong x86 roles in 22,267B partial father, but entire original 82KB game remains NONEXACT.')
