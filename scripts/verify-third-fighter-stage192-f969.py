#!/usr/bin/env python3
"""F969 real 004AC040 native 192: 732B/177x86, original FIADD and PE targets.

Fresh-build two TRACKED normal VC7.1 entire original-shaped PARTIAL 82KB
father sources, old F968 192 marker versus natural F969 192. Compare
pinned Japanese original game 190/191/192 physical x86 and 33 genuine
PE external target fields; 192 complete byte widths and mnemonics align,
but original -0xD8..-0xF8 x87 temporary positions/GPRs do NOT.
All 151 original afterRET DIR32 labels, 522 DATA nonfields verified.
No inner case is independently callable exact original CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f969-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F968-prior-192-marker':R/'probes/FighterWhole004AC040F968.cpp',
         'F969-real-192':R/'probes/FighterWhole004AC040F969.cpp'}
frag=(R/'probes/FighterThirdBossStage192F969.inc').read_text()
assert frag.count('case 0x192:')==1 and frag.count('SpawnFloatXYAt453A70(')==3
assert sources['F969-real-192'].read_text().count('#include "FighterThirdBossStage192F969.inc"')==1
sp=importlib.util.spec_from_file_location('f969reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIG_B=82796;ORIG_X86=22721;DATA_B=1126
N=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIG_B),BASE))
assert len(N)==ORIG_X86 and N[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+ORIG_B,DATA_B)
facts={
 '190':(0x4B2167,0x4B23BC,597,147,11),
 '191':(0x4B23BC,0x4B2611,597,147,11),
 '192':(0x4B2611,0x4B28ED,732,177,11),
}
native={}
for name,(a,b,n,nx,nr) in facts.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,n),a))
 assert len(I)==nx and b-a==n and I[-1].address+I[-1].size==b
 native[name]=I
x=native['192']
assert [x[j].mnemonic for j in (38,54,66,78,94,106,118,134,146)]==[
 'fild','fiadd','fild','fild','fiadd','fild','fild','fiadd','fild']
assert all(x[i].size==6 for i in
  (37,38,53,54,65,66,77,78,93,94,105,106,117,118,133,134,145,146))
assert x[71].op_str==x[111].op_str==x[151].op_str=='0x320'
assert x[73].op_str==x[113].op_str==x[153].op_str=='0x453a70'
assert x[173].op_str=='2'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(RX.findall(ins.op_str))
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
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 instructions=[]
 for xx in D.disasm(code,0):
  instructions.append(xx)
  if xx.mnemonic=='ret':break
 end=instructions[-1].address+instructions[-1].size
 assert len(code)-end==DATA_B
 jump=[r for r in refs if r['offset']>=end]
 assert len(jump)==151
 mask=set();labels={}
 for r in jump:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  original_addr=int.from_bytes(after[off:off+4],'little')
  assert BASE<=original_addr<BASE+ORIG_B
  labels.setdefault(original_addr,r['local_symbol_offset'])
 assert DATA_B-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA_B) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in facts.values())
 row={'original_whole_CODE_B':ORIG_B,'original_whole_x86':ORIG_X86,
  'whole_partial_source_B':end,'whole_partial_x86':len(instructions),
  'original_afterRET_DIR32_fields':151,'original_afterRET_nonfield_exact_B':522,
  'source_COFF_fields':len(refs),'native_case_source':{},
  'whole_game_exact':False}
 for name,(a,b,sz,nx,nf) in facts.items():
  lo,hi=labels[a],labels[b]
  part=[v for v in instructions if lo<=v.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':sz,'native_x86':nx,
        'source_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   mm=[i for i,(v,w) in enumerate(zip(native[name],part)) if v.mnemonic!=w.mnemonic]
   ww=[i for i,(v,w) in enumerate(zip(native[name],part)) if v.size!=w.size]
   gg=[i for i,(v,w) in enumerate(zip(native[name],part)) if roles(v)!=roles(w)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_width_ordinals':ww,
                'wrong_native_GPR_roles':gg})
   if not mm:
    assert len(fields)==nf,(label,name,len(fields),nf)
    physical_bytes=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,v in enumerate(part) if v.address<=r['offset']<v.address+v.size)
     disp=r['offset']-part[j].address
     native_off=native[name][j].address-a+disp
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     v=int.from_bytes(physical_bytes[native_off:native_off+4],
                      'little',signed=r['type']=='REL32')
     target=native[name][j].address+disp+4+v if r['type']=='REL32' else v
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,name,j,r['symbol'],hex(target),expected)
    item['native_original_PE_targets_checked']=len(fields)
  row['native_case_source'][name]=item
 rows[label]=row
 print(label,'whole source',end,'x86',len(instructions),
       '192 original sourceB',row['native_case_source']['192']['source_B'],flush=True)
old=rows['F968-prior-192-marker'];new=rows['F969-real-192']
assert (old['whole_partial_source_B'],old['whole_partial_x86'])==(26893,7403)
assert (new['whole_partial_source_B'],new['whole_partial_x86'])==(27610,7578)
assert old['native_case_source']['192']['source_B']==15
c=new['native_case_source']['192']
assert (c['source_B'],c['source_x86'])==(732,177)
assert c['wrong_native_mnemonics']==c['wrong_native_width_ordinals']==[]
assert len(c['wrong_native_GPR_roles'])==121
assert c['native_original_PE_targets_checked']==11
assert all(new['native_case_source'][case]['native_original_PE_targets_checked']==11
           for case in ('190','191'))
assert all(new['native_case_source'][case]['wrong_native_mnemonics']==[]
           for case in ('190','191'))
assert all(len(new['native_case_source'][case]['wrong_native_width_ordinals'])==12
           for case in ('190','191'))
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_82KB_fighter':'0x004AC040',
 'whole_original_callable_CODE_B':ORIG_B,'whole_original_x86':ORIG_X86,
 'native_192_original_CODE_B_x86':[732,177],
 'generated_192_same_CODE_B_x86':[732,177],
 'original_192_native_PE_targets_verified':11,
 'source_192_FIADD_x87_integer_semantics_verified':True,
 'source_192_all_mnemonic_and_width_roles_match':True,
 'original_192_GPR_role_errors':121,
 'original_192_stack_spill_EBP_d8_to_f8_not_recovered':True,
 'original_entire_game_exact':False,'new_exact_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_source_profiles':rows,
},indent=2)+'\n')
print('F969 original 192 732 B/177 native x86, three FIADD and six FILD slots, 11 true original external PE targets; all source widths/mnemonics but 121 native GPR roles wrong. 82KB original whole nonexact.')
