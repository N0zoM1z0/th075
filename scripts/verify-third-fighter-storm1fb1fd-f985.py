#!/usr/bin/env python3
"""F985: true original 004AC040 1FB/1FC/1FD 346-x86 storm states.

Cold-compile two TRACKED complete original-shaped PARTIAL 82KB fighter
normal VC7.1 parents, F984 markers and F985 real source.
Independently check whole native original Japanese PE, real 1FB/1FC/
1FD case boundaries and all 28 typed zero-addend original call/global
PE fields each. Native CMP ordinal54 has one register-dependent x86
width mismatch for 1FB/1FC, none for 1FD. Verify 151 afterRET local
DIR32 and 522 original nonfield DATA bytes. Never credit inner cases.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f985-third-original-proof'
O.mkdir(parents=True,exist_ok=True)
sources={'F984-prior-markers':R/'probes/FighterWhole004AC040F984.cpp',
         'F985-real-storm':R/'probes/FighterWhole004AC040F985.cpp'}
inc=(R/'probes/FighterThirdBossStages1FB1FDF985.inc').read_text()
assert all(inc.count('case 0x'+k+':')==1 for k in ('1FB','1FC','1FD'))
assert inc.count('StartAnimationAt46D000(0xC8)')==3
assert inc.count('g_F983_BurstYAt00659490')==18
assert sources['F985-real-storm'].read_text().count('#include "FighterThirdBossStages1FB1FDF985.inc"')==1
sp=importlib.util.spec_from_file_location('f985reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;AFTER=1126
orig_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(orig_whole)==WHOLEX and orig_whole[2].op_str=='esp, 0x720'
native_after=rd.pe_bytes_at(PE,BASE+WHOLE,AFTER)
cases={'1FA':(0x4B6394,0x4B6824,1168,339,28),
       '1FB':(0x4B6824,0x4B6CCD,1193,346,28),
       '1FC':(0x4B6CCD,0x4B7175,1192,346,28),
       '1FD':(0x4B7175,0x4B761E,1193,346,28)}
native={}
for k,(lo,hi,size,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,lo,size),lo))
 assert hi-lo==size and len(n)==nx and n[-1].address+n[-1].size==hi
 native[k]=n
for key,px in [('1FB','0x42700000'),('1FC','0xc2700000'),('1FD','0x42f00000')]:
 n=native[key]
 assert n[11].op_str.startswith('dword ptr [') and n[11].op_str.endswith('+ 0x7c], 1')
 assert n[20].op_str.endswith(', 6')
 assert n[28].op_str.endswith(', 0x14')
 assert n[54].op_str.endswith(', 0xeb')
 assert n[76].op_str=='0xd'
 for off in [173,194,215,236,257,278]:
  assert n[off+3].mnemonic=='fild'
  assert n[off+5].mnemonic=='fsubr'
 assert n[291].op_str=='0x46d000'
 assert n[329].op_str.endswith(', '+px)
 assert n[-1].op_str=='0x4c03a7'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(rx.findall(i.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for key,cpp in sources.items():
 obj=O/(key+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=env,text=True,capture_output=True,timeout=345)
 (O/(key+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 ins=[]
 for i in D.disasm(code,0):
  ins.append(i)
  if i.mnemonic=='ret':break
 end=ins[-1].address+ins[-1].size
 assert len(code)-end==AFTER
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  pos=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(pos,pos+4))
  mask.update(range(pos,pos+4))
  va=int.from_bytes(native_after[pos:pos+4],'little')
  assert BASE<=va<BASE+WHOLE
  labels.setdefault(va,r['local_symbol_offset'])
 assert AFTER-len(mask)==522
 assert all(code[end+i]==native_after[i] for i in range(AFTER) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'native_original_callable_B':WHOLE,'original_x86':WHOLEX,
  'full_partial_CPP_CODE_B':end,'partial_CPP_x86':len(ins),
  'total_COFF_fields':len(refs),'original_afterRET_local_DIR32':151,
  'original_afterRET_nonfield_equal_B':522,
  'original_cases':{},'whole_original_exact':False}
 for name,(a,b,size,nx,nfields) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in ins if lo<=x.address<hi]
  refs_case=[r for r in refs if lo<=r['offset']<hi]
  out={'original_native_CODE_B':size,'original_x86':nx,
       'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[name],s)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[name],s)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[name],s)) if roles(n)!=roles(x)]
   out.update({'wrong_original_mnemonic_ordinals':mm,
               'wrong_original_width_ordinals':ww,'wrong_original_GPR_ordinals':gg})
   if not mm:
    assert len(refs_case)==nfields,(key,name,len(refs_case),nfields)
    pebytes=rd.pe_bytes_at(PE,a,size)
    for r in refs_case:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-s[j].address
     origoff=native[name][j].address-a+dt
     if not ww: assert origoff==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     num=int.from_bytes(pebytes[origoff:origoff+4],
                        'little',signed=r['type']=='REL32')
     dest=native[name][j].address+dt+4+num if r['type']=='REL32' else num
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert dest==expected,(key,name,j,r['symbol'],hex(dest),expected)
    out['native_PE_targets_verified']=nfields
  row['original_cases'][name]=out
 results[key]=row
 print(key,'whole partial source',end,len(ins),
   '1FB/C/D',[(k,row['original_cases'][k]['source_CODE_B'],
               row['original_cases'][k]['source_x86']) for k in ('1FB','1FC','1FD')],flush=True)
old=results['F984-prior-markers'];new=results['F985-real-storm']
assert (old['full_partial_CPP_CODE_B'],old['partial_CPP_x86'])==(43483,11990)
assert (new['full_partial_CPP_CODE_B'],new['partial_CPP_x86'])==(47016,13022)
for name,srcB,badwidth in [('1FB',1192,[54]),('1FC',1193,[54]),('1FD',1193,[])]:
 assert old['original_cases'][name]['source_CODE_B']==15
 case=new['original_cases'][name]
 assert (case['source_CODE_B'],case['source_x86'])==(srcB,346)
 assert case['wrong_original_mnemonic_ordinals']==[]
 assert case['wrong_original_width_ordinals']==badwidth
 assert len(case['wrong_original_GPR_ordinals'])==180
 assert case['native_PE_targets_verified']==28
assert new['original_cases']['1FA']['native_PE_targets_verified']==28
(O/'verified-summary.json').write_text(json.dumps({
 'native_SHA_pinned_Japanese_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':WHOLE,'original_x86':WHOLEX,
 'original_1FB_1FC_1FD_native_CODE_B_x86':[1193+1192+1193,346*3],
 'original_all_1038_mnemonic_ordinals_match':True,
 'original_1FB_1FC_1FD_true_PE_targets_verified':84,
 'native_wrong_CMP_width_ordinals':{'1FB':[54],'1FC':[54],'1FD':[]},
 'native_GPR_role_errors_each':[180,180,180],
 'whole_original_exact':False,'new_accepted_complete_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_parent_profiles':results
},indent=2)+'\n')
print('F985 original 1FB/C/D 3578B/1038 x86, 84 verified PE targets, zero wrong mnemonic; one CMP x86 width 1FB/FC, zero 1FD. 82KB giant NONEXACT.')
