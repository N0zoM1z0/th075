#!/usr/bin/env python3
"""F987 original third-fighter 252/253/254: real native byte-decrement and PE.

Freshly compile tracked F985 old markers and F987 full PARTIAL
original-shaped normal VC7.1 82KB fighter parents, comparing pinned
Japanese original 260/259/225 CODE B original 72/72/63 x86 and
six actual typed zero-addend PE external fields each.
Original 254 has NO afterRET jump table entry: derive its boundary
from preceding 253's complete source instruction terminus. Compare
all 151 native original DIR32 afterRET labels plus 522 nonfield data.
Never accept an internal state or incomplete whole parent as exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f987-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F985-original-stubs':R/'probes/FighterWhole004AC040F985.cpp',
         'F987-real-252-254':R/'probes/FighterWhole004AC040F987.cpp'}
inc=(R/'probes/FighterThirdBossStages252254F987.inc').read_text()
assert all(inc.count('case 0x'+k+':')==1 for k in ('252','253','254'))
assert inc.count('--U8(0x366);')==3
assert inc.count('S16(0x3B0)=1000;')==2
assert inc.count('g_ContactProjectionAt00657888')==3
assert sources['F987-real-252-254'].read_text().count('#include "FighterThirdBossStages252254F987.inc"')==1
sp=importlib.util.spec_from_file_location('f987reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;DATA=1126
original_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original_whole)==WHOLEX and original_whole[2].op_str=='esp, 0x720'
original_after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'1FD':(0x4B7175,0x4B761E,1193,346,28),
       '252':(0x4B761E,0x4B7722,260,72,6),
       '253':(0x4B7722,0x4B7825,259,72,6),
       '254':(0x4B7825,0x4B7906,225,63,6)}
native={}
for key,(lo,hi,sz,nx,nfields) in cases.items():
 ins=list(D.disasm(rd.pe_bytes_at(PE,lo,sz),lo))
 assert hi-lo==sz and len(ins)==nx and ins[-1].address+ins[-1].size==hi
 native[key]=ins
for k in ('252','253','254'):
 n=native[k]
 assert [i.mnemonic for i in n[9:13]]==['mov','sub','mov','mov']
 assert n[10].op_str.endswith(', 1')
 assert n[14].op_str=='0x453e20'
 assert n[16].mnemonic=='mov' and n[16].op_str.endswith('+ 0x80], 1')
 assert n[-2].mnemonic=='mov' and n[-2].op_str.endswith('+ 0xefa], 0')
 assert n[-1].op_str=='0x4c03a7'
assert native['252'][24].op_str.endswith('+ 0x3b6]')
assert native['253'][24].op_str.endswith('+ 0x3b6]')
assert native['254'][23].mnemonic=='mov' and native['254'][24].mnemonic=='call'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(RX.findall(i.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,text=True,capture_output=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-980:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for ins in D.disasm(code,0):
  I.append(ins)
  if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(original_after[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==original_after[i] for i in range(DATA) if i not in mask)
 assert 0x4B7825 not in labels
 assert all(addr in labels for addr in (0x4B7175,0x4B761E,0x4B7722,0x4B7906))
 start253=labels[0x4B7722]
 idx=next(i for i,x in enumerate(I) if x.address==start253)
 # Previous complete marker 253 has 2 x86, new real 253 has all 72.
 source_253_x86=72 if label=='F987-real-252-254' else 2
 full_prev253=I[idx:idx+source_253_x86]
 source_254_start=full_prev253[-1].address+full_prev253[-1].size
 assert len(full_prev253)==source_253_x86
 boundaries={
 '1FD':(labels[0x4B7175],labels[0x4B761E]),
 '252':(labels[0x4B761E],labels[0x4B7722]),
 '253':(labels[0x4B7722],source_254_start),
 '254':(source_254_start,labels[0x4B7906])}
 row={'whole_original_callable_CODE_B':WHOLE,'whole_original_x86':WHOLEX,
      'source_partial_CODE_B':end,'source_partial_x86':len(I),
      'original_254_lacks_native_afterRET_label':True,
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'source_total_COFF_relocations':len(refs),'whole_original_exact':False,'cases':{}}
 for key,(a,b,nbytes,nx,nfields) in cases.items():
  lo,hi=boundaries[key]
  part=[i for i in I if lo<=i.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_B':nbytes,'original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   mm=[j for j,(x,y) in enumerate(zip(native[key],part)) if x.mnemonic!=y.mnemonic]
   ww=[j for j,(x,y) in enumerate(zip(native[key],part)) if x.size!=y.size]
   gg=[j for j,(x,y) in enumerate(zip(native[key],part)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,
                'wrong_native_GPR_roles':gg})
   if not mm:
    assert len(fields)==nfields,(label,key,len(fields),nfields)
    raw=rd.pe_bytes_at(PE,a,nbytes)
    for f in fields:
     j=next(j for j,x in enumerate(part) if x.address<=f['offset']<x.address+x.size)
     dt=f['offset']-part[j].address
     native_off=native[key][j].address-a+dt
     if not ww: assert native_off==f['offset']-lo
     assert f['type'] in ('REL32','DIR32') and f['addend']==0 and f['local_symbol_offset'] is None
     num=int.from_bytes(raw[native_off:native_off+4],'little',signed=f['type']=='REL32')
     target=native[key][j].address+dt+4+num if f['type']=='REL32' else num
     m=re.search(r'At([0-9A-Fa-f]{6,8})',f['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if f['symbol']=='__ftol2' else None
     assert target==expected,(label,key,j,f['symbol'],hex(target),expected)
    item['original_PE_targets_verified']=nfields
  row['cases'][key]=item
 rows[label]=row
 print(label,'whole partial',end,len(I),'state252/253/254',
   [(k,row['cases'][k]['source_CODE_B'],row['cases'][k]['source_x86']) for k in ('252','253','254')],flush=True)
old=rows['F985-original-stubs'];new=rows['F987-real-252-254']
assert (old['source_partial_CODE_B'],old['source_partial_x86'])==(47016,13022)
assert (new['source_partial_CODE_B'],new['source_partial_x86'])==(47715,13223)
for key,sourceB,gpr,width in [('252',259,47,[10]),('253',260,47,[10]),('254',225,40,[])]:
 assert old['cases'][key]['source_CODE_B']==15
 n=new['cases'][key]
 assert (n['source_CODE_B'],n['source_x86'])==(sourceB,cases[key][3])
 assert n['wrong_native_mnemonics']==[]
 assert n['wrong_native_widths']==width
 assert len(n['wrong_native_GPR_roles'])==gpr
 assert n['original_PE_targets_verified']==6
assert new['cases']['1FD']['original_PE_targets_verified']==28
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_fighter':'0x004AC040',
 'original_complete_callable_CODE_B':WHOLE,'original_whole_x86':WHOLEX,
 'original_native_252_253_254_CODE_B_x86':[260+259+225,72+72+63],
 'native_original_PE_targets_checked':18,
 'native_correct_8bit_decrement_MOV_SUB_MOV':True,
 'real_254_missing_native_afterRET_table_label':True,
 'all_207_native_mnemonics_match':True,
 'wrong_original_width_ordinals':{'252':[10],'253':[10],'254':[]},
 'wrong_original_GPR_instr':[47,47,40],
 'entire_original_game_exact':False,'new_accepted_exact_original_B':0,
 'mass_cold_replay':False,'full_original_shaped_parent_profiles':rows
},indent=2)+'\n')
print('F987 native 252/253/254 744B/207 x86, 18 real PE targets; all mnemonics, 1/1/0 widths wrong due actual 8-bit register phase. Whole 82KB fighter NONEXACT.')
