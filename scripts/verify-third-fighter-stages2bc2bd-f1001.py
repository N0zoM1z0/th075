#!/usr/bin/env python3
"""F1001: true original Japanese 2BC/2BD fighter stages, 30 PE targets.

Fresh compile two tracked original-shaped ENTIRE 82KB PARTIAL normal
VC7.1 parent source objects, F998 old 2BC/BD markers vs F1001
actual 2BC/BD source. Original native PE cases755B/199x86 and
742B/196x86, 15 typed original call/global PE fields each.
Check actual 2BD distinct limit72,F14 and 0x74/0x32B effects
vs 2BC limit36,0x73/0x323 & F04 increment. Original 2BD
native ADD width ordinal133 is one byte smaller than source.
Verify original 151 afterRET DIR32+522 nonfield DATA bytes,
and preceding native 25D/25E/25F/260/261/262 source cases.
Entire original whole callable still NONEXACT, zero credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1001-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F998-prior-markers':R/'probes/FighterWhole004AC040F998.cpp',
 'F1001-real-2BC2BD':R/'probes/FighterWhole004AC040F1001.cpp'}
inc=(R/'probes/FighterThirdBossStages2BC2BDF1001.inc').read_text()
assert inc.count('case 0x2BC:')==inc.count('case 0x2BD:')==1
assert inc.count('ApplyAt453E80(0x28)')==2
assert inc.count('SpawnAt453C80(0x73,')==inc.count('SpawnAt453C80(0x74,')==1
assert inc.count('SpawnFloatXYAt453A70(0x323,')==2
assert inc.count('SpawnFloatXYAt453A70(0x32B,')==2
assert inc.count('S16(0xF14)=1;')==1
assert sources['F1001-real-2BC2BD'].read_text().count('#include "FighterThirdBossStages2BC2BDF1001.inc"')==1
sp=importlib.util.spec_from_file_location('f1001reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;GAME_X86=22721;AFTER=1126
original_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original_whole)==GAME_X86 and original_whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+WHOLE,AFTER)
cases={
 '25D':(0x4B973A,0x4BA229,2799,749,78),
 '25E':(0x4BA229,0x4BA59B,882,236,24),
 '25F':(0x4BA59B,0x4BA76D,466,114,9),
 '260':(0x4BA76D,0x4BA93F,466,114,9),
 '261':(0x4BA93F,0x4BAAA8,361,98,8),
 '262':(0x4BAAA8,0x4BAC11,361,98,8),
 '2BC':(0x4BAC11,0x4BAF04,755,199,15),
 '2BD':(0x4BAF04,0x4BB1EA,742,196,15)}
native={}
for key,(a,b,size,nx,nf) in cases.items():
 seq=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(seq)==nx and seq[-1].address+seq[-1].size==b
 native[key]=seq
for k,projectile,shots,limit in [('2BC',0x73,0x323,36),('2BD',0x74,0x32B,72)]:
 n=native[k]
 assert n[9].op_str.endswith('+ 0xf00], 0')
 assert n[13].op_str=='0x453e20'
 assert n[42].op_str=='0x453e80'
 assert n[45].op_str=='0x453d60'
 assert n[48].op_str=='dword ptr [0x657888]'
 assert n[57].op_str=='dword ptr [0x659284]'
 assert n[69].op_str==hex(projectile)
 assert n[71].op_str=='0x453c80'
 assert n[95].op_str.endswith(', '+hex(limit) if limit==72 else ', 0x24')
 assert n[-1].op_str=='0x4c03a7'
 assert len([x for x in n if x.mnemonic=='call' and x.op_str=='0x453a70'])==2
 assert len([x for x in n if x.mnemonic=='call' and x.op_str=='0x40fb40'])==1
 assert len([x for x in n if x.mnemonic=='call' and x.op_str=='0x46d000'])==1
 assert any(x.op_str==hex(shots) and x.mnemonic=='push' for x in n)
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for label,src in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
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
  addr=int.from_bytes(after[off:off+4],'little')
  assert BASE<=addr<BASE+WHOLE
  labels.setdefault(addr,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[ret+i]==after[i] for i in range(AFTER) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_entire_callable_GAME_B':WHOLE,'original_whole_x86':GAME_X86,
   'compiled_whole_partial_CODE_B':ret,'partial_cpp_x86':len(I),
   'partial_frame':I[2].op_str,'original_afterRET_DIR32':151,
   'original_afterRET_nonfield_equal_B':522,
   'original_whole_exact':False,'real_cases':{}}
 for k,(a,b,size,nx,nfields) in cases.items():
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'native_original_CODE_B':size,'native_x86':nx,
   'source_CODE_B':hi-lo,'source_x86':len(part)}
  if len(part)==nx:
   mm=[j for j,(n,s) in enumerate(zip(native[k],part)) if n.mnemonic!=s.mnemonic]
   ww=[j for j,(n,s) in enumerate(zip(native[k],part)) if n.size!=s.size]
   gg=[j for j,(n,s) in enumerate(zip(native[k],part)) if roles(n)!=roles(s)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,
                'wrong_native_GPR_roles':gg})
   if not mm:
    assert len(fields)==nfields,(label,k,len(fields),nfields)
    raw=rd.pe_bytes_at(PE,a,size)
    for r in fields:
     j=next(j for j,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-part[j].address
     off=native[k][j].address-a+d
     if not ww: assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+d+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['native_original_PE_targets_verified']=nfields
  row['real_cases'][k]=item
 results[label]=row
 print(label,'whole-partial father',ret,len(I),
  '2BC/2BD',[(k,row['real_cases'][k]['source_CODE_B'],row['real_cases'][k]['source_x86']) for k in ('2BC','2BD')],flush=True)
old=results['F998-prior-markers'];new=results['F1001-real-2BC2BD']
assert (old['compiled_whole_partial_CODE_B'],old['partial_cpp_x86'])==(60595,16621)
assert (new['compiled_whole_partial_CODE_B'],new['partial_cpp_x86'])==(62063,17012)
assert old['partial_frame']=='esp, 0x434'
assert new['partial_frame']=='esp, 0x45c'
for k,sz,nx,g,w in [('2BC',755,199,128,[]),('2BD',743,196,125,[133])]:
 assert old['real_cases'][k]['source_CODE_B']==15
 r=new['real_cases'][k]
 assert (r['source_CODE_B'],r['source_x86'])==(sz,nx)
 assert r['wrong_native_mnemonics']==[] and r['wrong_native_widths']==w
 assert len(r['wrong_native_GPR_roles'])==g
 assert r['native_original_PE_targets_verified']==15
for k,wrong in [('25D',477),('25E',153),('25F',73),('260',73),('261',65),('262',65)]:
 r=new['real_cases'][k]
 assert r['wrong_native_mnemonics']==r['wrong_native_widths']==[]
 assert len(r['wrong_native_GPR_roles'])==wrong
 assert r['native_original_PE_targets_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'original_SHA_pinned_Japanese_fighter':'0x004AC040',
 'original_entire_callable_GAME_CODE_B':WHOLE,'native_whole_x86':GAME_X86,
 'original_2BC_2BD_B_x86':[755+742,199+196],
 'native_original_PE_fields_checked':30,
 'source_native_mnemonics_all_395_match':True,
 'wrong_native_widths':{'2BC':[],'2BD':[133]},
 'source_2BC_2BD_wrong_GPR_roles':[128,125],
 'eight_natural_2BD_integer_value_category_trials_no_improvement':True,
 'native_prior_game_cases_unchanged':True,
 'whole_original_exact':False,'new_accepted_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_original_shaped_cpp_parent_profiles':results
},indent=2)+'\n')
print('F1001 original 2BC/2BD 1497 B/395 x86/30 PE targets; all native mnemonics, widths 2BC zero and 2BD ordinal133 one. Giant whole NONEXACT.')
