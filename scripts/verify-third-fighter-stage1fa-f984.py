#!/usr/bin/env python3
"""F984 original 1FA: native 1168B/339x86, 28 original PE targets.

Fresh compile two TRACKED ENTIRE 82KB PARTIAL original-shaped VC7.1
father C++ sources. Original 1FA source has exact native lengths,
mnemonics and x86 widths with only six wrong GPR roles at 327-333;
the real original saved-this EBP is still wrong, so NO callable exact
GAME credit. Check complete original PE and all afterRET DIR32 data.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f984-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F983-old-1FA-marker':R/'probes/FighterWhole004AC040F983.cpp',
         'F984-real-1FA':R/'probes/FighterWhole004AC040F984.cpp'}
src=(R/'probes/FighterThirdBossStage1FAF984.inc').read_text()
assert src.count('case 0x1FA:')==1 and src.count('POS=120.0f;')==1
assert src.count('g_F983_BurstYAt00659490')==6
assert sources['F984-real-1FA'].read_text().count('#include "FighterThirdBossStage1FAF984.inc"')==1
sp=importlib.util.spec_from_file_location('f984reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;GAME=82796;GAME_X86=22721;POST=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,GAME),BASE))
assert len(whole)==GAME_X86 and whole[2].op_str=='esp, 0x720'
original_data=rd.pe_bytes_at(PE,BASE+GAME,POST)
cases={
 '1F8':(0x4B5A75,0x4B5F05,1168,339,28),
 '1F9':(0x4B5F05,0x4B6394,1167,339,28),
 '1FA':(0x4B6394,0x4B6824,1168,339,28)}
native={}
for k,(a,b,size,nx,nrefs) in cases.items():
 seq=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(seq)==nx and seq[-1].address+seq[-1].size==b
 native[k]=seq
assert native['1FA'][42].op_str.endswith(', 0x42f00000')
assert native['1FA'][64].mnemonic=='cmp'
assert native['1FA'][64].size==6
for j in (183,204,225,246,267,288):
 assert [x.mnemonic for x in native['1FA'][j:j+6]]==[
  'movsx','imul','mov','fild','mov','fsubr']
 assert native['1FA'][j+1].op_str.endswith(', 7')
 assert native['1FA'][j+5].op_str.endswith('+ 0x44]')
reg=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(reg.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,text=True,capture_output=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1100:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==POST
 fields=[r for r in refs if r['offset']>=ret]
 assert len(fields)==151
 labels={};mask=set()
 for r in fields:
  offset=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(offset,offset+4))
  mask.update(range(offset,offset+4))
  dest=int.from_bytes(original_data[offset:offset+4],'little')
  assert BASE<=dest<BASE+GAME
  labels.setdefault(dest,r['local_symbol_offset'])
 assert POST-len(mask)==522
 assert all(code[ret+j]==original_data[j] for j in range(POST) if j not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_whole_CODE_B':GAME,'original_whole_x86':GAME_X86,
   'partial_parent_CPP_CODE_B':ret,'partial_parent_x86':len(I),
   'native_afterRET_DIR32':151,'native_afterRET_nonfield_exact_B':522,
   'CPP_source_COFF_records':len(refs),'original_cases':{},
   'original_whole_exact':False}
 for k,(a,b,size,nx,nrefs) in cases.items():
  lo,hi=labels[a],labels[b]
  src_inst=[x for x in I if lo<=x.address<hi]
  refs_local=[r for r in refs if lo<=r['offset']<hi]
  item={'original_CODE_B':size,'original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(src_inst)}
  if len(src_inst)==nx:
   badm=[j for j,(x,y) in enumerate(zip(native[k],src_inst)) if x.mnemonic!=y.mnemonic]
   badw=[j for j,(x,y) in enumerate(zip(native[k],src_inst)) if x.size!=y.size]
   badr=[j for j,(x,y) in enumerate(zip(native[k],src_inst)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnemonic_ordinals':badm,
                'wrong_native_width_ordinals':badw,
                'wrong_native_GPR_ordinals':badr})
   if not badm:
    assert len(refs_local)==nrefs,(label,k,len(refs_local),nrefs)
    raw=rd.pe_bytes_at(PE,a,size)
    for r in refs_local:
     j=next(j for j,x in enumerate(src_inst) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-src_inst[j].address
     physical=native[k][j].address-a+d
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     if not badw: assert physical==r['offset']-lo
     val=int.from_bytes(raw[physical:physical+4],'little',
                        signed=r['type']=='REL32')
     origdest=native[k][j].address+d+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert origdest==expected,(label,k,j,r['symbol'],hex(origdest),expected)
    item['original_PE_external_fields_verified']=nrefs
  row['original_cases'][k]=item
 results[label]=row
 print(label,'whole original-shaped partial',ret,len(I),
 '1FA C++',row['original_cases']['1FA']['source_CODE_B'],
 row['original_cases']['1FA']['source_x86'],flush=True)
old=results['F983-old-1FA-marker'];new=results['F984-real-1FA']
assert (old['partial_parent_CPP_CODE_B'],old['partial_parent_x86'])==(42330,11653)
assert (new['partial_parent_CPP_CODE_B'],new['partial_parent_x86'])==(43483,11990)
assert old['original_cases']['1FA']['source_CODE_B']==15
rec=new['original_cases']['1FA']
assert (rec['source_CODE_B'],rec['source_x86'])==(1168,339)
assert rec['wrong_native_mnemonic_ordinals']==rec['wrong_native_width_ordinals']==[]
assert rec['wrong_native_GPR_ordinals']==[327,328,329,331,332,333]
assert rec['original_PE_external_fields_verified']==28
assert new['original_cases']['1F8']['original_PE_external_fields_verified']==28
assert new['original_cases']['1F9']['original_PE_external_fields_verified']==28
(O/'verified-summary.json').write_text(json.dumps({
 'original_SHA_pinned_game_fighter':'0x004AC040',
 'native_entire_callable_CODE_B':GAME,'native_whole_x86':GAME_X86,
 'true_original_1FA_B_x86':[1168,339],
 'source_natural_1FA_B_x86':[1168,339],
 'native_1FA_original_external_PE_fields_verified':28,
 'all_native_1FA_mnemonics_widths_and_333_GPR_roles_match':True,
 'six_wrong_native_GPR_ordinals':[327,328,329,331,332,333],
 'native_saved_this_EBP_still_wrong':True,
 'original_whole_exact':False,'accepted_new_whole_CODE_B':0,
 'mass_cold_replay':False,'whole_original_shaped_source_profiles':results
},indent=2)+'\n')
print('F984 native 1FA 1168B/339x86/28 verified PE fields, only 6 GPR differences; source giant NONEXACT.')
