#!/usr/bin/env python3
"""F994 native 261/262 true ten-shot states: 196 GPR roles all aligned.

Fresh-build tracked F993 marker father and F994 real 261/262 as TWO
complete original-shaped normal VC7.1 PARTIAL 82KB fighter sources.
Independently check pinned Japanese native 261/262 each 361B/98 x86
and eight real typed PE call/global fields, preceding 25F/260
two 466B/114-x86/9 PE units, all 151 native afterRET DIR32
and 522 nonfield DATA B. Never credit incomplete 82KB father.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f994-third-native-proof'
O.mkdir(parents=True,exist_ok=True)
sources={'F993-prior-markers':R/'probes/FighterWhole004AC040F993.cpp',
 'F994-real-261262':R/'probes/FighterWhole004AC040F994.cpp'}
inc=(R/'probes/FighterThirdBossTenShot261262F994.inc').read_text()
assert inc.count('case 0x261:')==inc.count('case 0x262:')==1
assert inc.count('for (int shot=0;shot<10;++shot)')==2
assert inc.count('SpawnWithFloatAt453A70(0x346,')==1
assert inc.count('SpawnWithFloatAt453A70(0x347,')==1
assert inc.count('g_F972_GravityAt00657F74')==4
assert sources['F994-real-261262'].read_text().count('#include "FighterThirdBossTenShot261262F994.inc"')==1
sp=importlib.util.spec_from_file_location('f994reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;ORIG_X86=22721;AFTER=1126
origfull=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(origfull)==ORIG_X86 and origfull[2].op_str=='esp, 0x720'
data=rd.pe_bytes_at(PE,BASE+WHOLE,AFTER)
cases={
 '25F':(0x4BA59B,0x4BA76D,466,114,9),
 '260':(0x4BA76D,0x4BA93F,466,114,9),
 '261':(0x4BA93F,0x4BAAA8,361,98,8),
 '262':(0x4BAAA8,0x4BAC11,361,98,8)}
native={}
for k,(lo,hi,sz,nx,nf) in cases.items():
 v=list(D.disasm(rd.pe_bytes_at(PE,lo,sz),lo))
 assert len(v)==nx and hi-lo==sz and v[-1].address+v[-1].size==hi
 native[k]=v
for k,kind in [('261',0x346),('262',0x347)]:
 n=native[k]
 assert n[9].op_str.endswith('+ 0x7c], 1')
 assert n[11].op_str.endswith('+ 0xf00], 0')
 assert n[13].op_str.endswith('+ 0xf02], 0')
 assert n[16].op_str=='dword ptr [0x657f74]'
 assert n[21].op_str=='dword ptr [0x657f74]'
 assert n[53].op_str.endswith('+ 0x50], 0xc0400000')
 assert n[55].op_str.endswith('+ 0x54], 0x41100000')
 assert n[57].op_str.endswith('+ 0x5c], 0x3f333333')
 assert n[60].op_str=='0x453d40' and n[63].op_str=='0x46d000'
 assert n[69].op_str.endswith(', 0xa')
 assert n[87].op_str=='dword ptr [0x6590ac]'
 assert n[93].op_str==hex(kind) and n[95].op_str=='0x453a70'
 assert n[96].mnemonic=='jmp' and n[-1].op_str=='0x4c03a7'
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
  cwd=R,env=env,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1100:]
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
  va=int.from_bytes(data[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[ret+i]==data[i] for i in range(AFTER) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'native_original_whole_CODE_B':WHOLE,'native_original_whole_x86':ORIG_X86,
  'full_partial_CPP_B':ret,'full_partial_x86':len(I),'source_frame':I[2].op_str,
  'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
  'whole_original_exact':False,'real_cases':{}}
 for name,(a,b,sz,nx,nfields) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  reloc=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':sz,'original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(x,y) in enumerate(zip(native[name],s)) if x.mnemonic!=y.mnemonic]
   ww=[j for j,(x,y) in enumerate(zip(native[name],s)) if x.size!=y.size]
   gg=[j for j,(x,y) in enumerate(zip(native[name],s)) if roles(x)!=roles(y)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,
                'wrong_original_GPR_roles':gg})
   if not mm:
    assert len(reloc)==nfields,(label,name,len(reloc),nfields)
    original=rd.pe_bytes_at(PE,a,sz)
    for r in reloc:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address
     native_off=native[name][j].address-a+dt
     if not ww:assert native_off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     value=int.from_bytes(original[native_off:native_off+4],'little',signed=r['type']=='REL32')
     target=native[name][j].address+dt+4+value if r['type']=='REL32' else value
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,name,j,r['symbol'],hex(target),expected)
    item['native_original_PE_fields_verified']=nfields
  row['real_cases'][name]=item
 rows[label]=row
 print(label,'complete original-shaped PARTIAL father',ret,len(I),
  '261/262 B/x86',[(k,row['real_cases'][k]['source_CODE_B'],row['real_cases'][k]['source_x86']) for k in ('261','262')],flush=True)
old=rows['F993-prior-markers'];new=rows['F994-real-261262']
assert (old['full_partial_CPP_B'],old['full_partial_x86'])==(51534,14224)
assert (new['full_partial_CPP_B'],new['full_partial_x86'])==(52238,14416)
assert old['source_frame']=='esp, 0x370' and new['source_frame']=='esp, 0x380'
for k in ('261','262'):
 assert old['real_cases'][k]['source_CODE_B']==15
 r=new['real_cases'][k]
 assert (r['source_CODE_B'],r['source_x86'])==(361,98)
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_original_GPR_roles']==[]
 assert r['native_original_PE_fields_verified']==8
for k in ('25F','260'):
 r=new['real_cases'][k]
 assert (r['source_CODE_B'],r['source_x86'])==(466,114)
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==r['wrong_original_GPR_roles']==[]
 assert r['native_original_PE_fields_verified']==9
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_native_original_fighter':'0x004AC040',
 'original_entire_callable_GAME_CODE_B':WHOLE,'original_whole_x86':ORIG_X86,
 'native_261_262_CODE_B_x86':[361*2,98*2],
 'all_native_196_x86_mnemonics_widths_GPRs_match':True,
 'verified_original_261_262_typed_PE_targets':16,
 'previous_25F_260_full_gpr_and_PE_unchanged':True,
 'native_actor_full_frame_still_unrecovered':True,
 'whole_original_exact':False,'new_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,
 'entire_original_shaped_partial_father_profiles':rows
},indent=2)+'\n')
print('F994 two true native 261/262 722B/196 x86, all original mnemonic/width/GPR roles and 16 PE targets verified; preceding 25F/260 unaffected. Whole giant NONEXACT.')
