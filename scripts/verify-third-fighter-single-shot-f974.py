#!/usr/bin/env python3
"""F974: real original 19B/19C single shots within 82KB whole partial C++.

Fresh compile tracked F972/F974 ENTIRE original-shaped normal VC7.1
partial fighter parents. Compare real Japanese PE original 19B/19C
355B/87x86 each, seven genuine zero-addend i386 PE external fields
each; true following 19D boundary and predecessor 19A native state.
Original 151 afterRET DIR32 entries and 522 nonfield DATA B verified.
No separate case or partial father exact original CODE acceptance.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f974-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F972-prior-markers':R/'probes/FighterWhole004AC040F972.cpp',
         'F974-real-single-shots':R/'probes/FighterWhole004AC040F974.cpp'}
inc=(R/'probes/FighterThirdBossSingleShot19B19CF974.inc').read_text()
assert inc.count('case 0x19B:')==inc.count('case 0x19C:')==1
assert sources['F974-real-single-shots'].read_text().count('#include "FighterThirdBossSingleShot19B19CF974.inc"')==1
sp=importlib.util.spec_from_file_location('f974reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;DATA=1126
origparent=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(origparent)==WHOLEX and origparent[2].op_str=='esp, 0x720'
native_after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'19A':(0x4B3637,0x4B3888,593,170,19),
       '19B':(0x4B3888,0x4B39EB,355,87,7),
       '19C':(0x4B39EB,0x4B3B4E,355,87,7)}
original={}
for k,(a,b,size,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(n)==nx and n[-1].address+n[-1].size==b
 original[k]=n
proofs={'19B':{'stage':5,'angle':-30,'mul':49,'y':0x659294},
        '19C':{'stage':4,'angle':30,'mul':97,'y':0x659498}}
for k,v in proofs.items():
 n=original[k]
 assert n[18].op_str.endswith(', '+str(v['stage']))
 assert n[36].mnemonic=='lea'
 assert n[36].op_str.endswith(', [ecx*4 - 0x1e]') if k=='19B' else n[36].op_str.endswith(', [edx*4 + 0x1e]')
 assert n[42].op_str.endswith(', 0x41700000')
 assert n[49].op_str==f'dword ptr [0x{v["y"]:x}]'
 assert int(n[54].op_str.split(', ')[-1],16)==v['mul']
 assert n[61].op_str=='0x326'
 assert n[63].op_str=='0x453a70'
 assert n[85].op_str=='0x40fac0'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,capture_output=True,text=True,timeout=335)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
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
  nva=int.from_bytes(native_after[off:off+4],'little')
  assert BASE<=nva<BASE+WHOLE
  labels.setdefault(nva,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+j]==native_after[j] for j in range(DATA) if j not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_whole_game_CODE_B':WHOLE,'original_whole_x86':WHOLEX,
      'source_partial_whole_CODE_B':ret,'source_whole_x86':len(I),
      'whole_source_COFF_records':len(refs),
      'native_afterRET_DIR32_entries':151,'native_afterRET_nonfield_equal_B':522,
      'original_cases':{},'whole_game_exact':False}
 for k,(a,b,size,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  refs_case=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':size,'native_x86':nx,
        'generated_CODE_B':hi-lo,'generated_x86':len(s)}
  if len(s)==nx:
   badm=[j for j,(n,c) in enumerate(zip(original[k],s)) if n.mnemonic!=c.mnemonic]
   badw=[j for j,(n,c) in enumerate(zip(original[k],s)) if n.size!=c.size]
   badg=[j for j,(n,c) in enumerate(zip(original[k],s)) if roles(n)!=roles(c)]
   item.update({'wrong_mnemonic_ordinals':badm,
                'wrong_width_ordinals':badw,
                'wrong_native_GPR_ordinals':badg})
   if not badm and not badw:
    assert len(refs_case)==nf,(label,k,len(refs_case),nf)
    raw=rd.pe_bytes_at(PE,a,size)
    for r in refs_case:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address
     native_off=original[k][j].address-a+dt
     assert native_off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(raw[native_off:native_off+4],'little',signed=r['type']=='REL32')
     target=original[k][j].address+dt+4+value if r['type']=='REL32' else value
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_original_PE_targets_checked']=len(refs_case)
  row['original_cases'][k]=item
 rows[label]=row
 print(label,'partial father',ret,len(I),'19B/19C',
  [(k,row['original_cases'][k]['generated_CODE_B'],row['original_cases'][k]['generated_x86'])
   for k in ('19B','19C')],flush=True)
old=rows['F972-prior-markers'];new=rows['F974-real-single-shots']
assert (old['source_partial_whole_CODE_B'],old['source_whole_x86'])==(31500,8678)
assert (new['source_partial_whole_CODE_B'],new['source_whole_x86'])==(32180,8848)
for k in ('19B','19C'):
 assert old['original_cases'][k]['generated_CODE_B']==15
 r=new['original_cases'][k]
 assert (r['generated_CODE_B'],r['generated_x86'])==(355,87)
 assert r['wrong_mnemonic_ordinals']==r['wrong_width_ordinals']==[]
 assert len(r['wrong_native_GPR_ordinals'])==56
 assert r['native_original_PE_targets_checked']==7
assert new['original_cases']['19A']['native_original_PE_targets_checked']==19
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x004AC040',
 'original_complete_callable_CODE_B':WHOLE,'original_whole_x86':WHOLEX,
 'real_19B_19C_native_CODE_B_x86':[710,174],
 'real_19B_19C_source_CODE_B_x86':[710,174],
 'original_native_PE_external_fields':14,
 'native_source_wrong_mnemonic_width_positions':0,
 'native_GPR_wrong_per_case':[56,56],
 'real_19B_multipliers_and_original_stage_verified':True,
 'real_19C_multipliers_and_original_stage_verified':True,
 'entire_original_exact':False,'new_accepted_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_original_shaped_fathers':rows
},indent=2)+'\n')
print('F974 original native 19B/19C 710B/174x86 and 14 real PE targets; all original mnemonic/width roles matched, but 56 real GPR roles wrong in each. Whole 82KB game remains NONEXACT.')
