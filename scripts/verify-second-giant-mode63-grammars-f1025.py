#!/usr/bin/env python3
"""F1025: 10 real 58KB whole fighter mode63 branch-grammar controls.

Fresh normal VC7.1 compile of TEN complete original-shaped
00543210 C++ parent sources, pinned Japanese v1.11 native
58294B/16471x86, physical mode63 417B/109x86/7
typed original PE fields and all 943 afterRET DATA B
(156 DIR32 local labels, 319 nonfields). Genuine
else-if/de Morgan/read-only native short owner controls
do not repair three original CMP register-width debts.
Real 0x720 shared slot repair from 82KB is NOT relevant
to this original 58KB actor: original 0x218 frame and
EBP−0x44 receiver already match. Whole game exact=NO.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1025-native-58kb-proof';O.mkdir(parents=True,exist_ok=True)
base=(R/'.analysis/f917-native-burst-x87-verified/F917-borrowed-real-X.cpp').read_text()
inc=(R/'probes/FighterMode63BasicF626.inc').read_text()
marker='#include "FighterMode63BasicF626.inc"'
assert base.count(marker)==1 and inc.count('case 0x63:')==1
first='''    if (g_ModeAt006714B4 != 3 ||
        *reinterpret_cast<signed char*>(RAW+0x2CD)==0)'''
assert inc.count(first)==1
key='*reinterpret_cast<signed char*>(RAW+0x39D)'
own='*reinterpret_cast<signed short*>(OWNER+0x60)'
assert inc.count(own)==4 and inc.count(key)==7
def ifelse(s,second=False,third=False):
 if second:
  a='        if (I16(0x62)>0 &&'
  assert s.count(a)==1
  s=s.replace(a,'        else if (I16(0x62)>0 &&',1)
 if third:
  a='        if (I16(0x62)>1 &&'
  assert s.count(a)==2
  pos=s.rfind(a)
  s=s[:pos]+s[pos:].replace(a,'        else if (I16(0x62)>1 &&',1)
 return s
variants={
 'strict-native':inc,
 'else-if-second':ifelse(inc,True,False),
 'else-if-third':ifelse(inc,False,True),
 'else-if-both':ifelse(inc,True,True),
 'de-morgan-outer':inc.replace(first,'''    if (!(g_ModeAt006714B4 == 3 &&
        *reinterpret_cast<signed char*>(RAW+0x2CD)!=0))'''),
 'reversed-pure-outer':inc.replace(first,'''    if (*reinterpret_cast<signed char*>(RAW+0x2CD)==0 ||
        g_ModeAt006714B4 != 3)'''),
 'real-owner-const-borrow':inc.replace(own,'*reinterpret_cast<const signed short*>(OWNER+0x60)'),
 'real-key-const-borrow':inc.replace(key,'*reinterpret_cast<const signed char*>(RAW+0x39D)'),
 'signed-stage-const-borrow':inc.replace('I16(0x62)','*reinterpret_cast<const signed short*>(RAW+0x62)'),
 'stage-guard-nested':inc.replace('''if (I16(0x62)==2 &&
            *reinterpret_cast<signed char*>(RAW+0x39D)>0 &&''',
 '''if (I16(0x62)==2 &&
            *reinterpret_cast<signed char*>(RAW+0x39D)>0 &&'''),
}
# Replace duplicate no-op variant with a genuine used status source change:
assert variants['stage-guard-nested']==inc
variants['stage-guard-nested']=inc.replace('''I16(0x62)>1 &&''','''(I16(0x62)>1) &&''')
sp=importlib.util.spec_from_file_location('rd1025',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);P=rd.verified_target()
N=list(D.disasm(rd.pe_bytes_at(P,0x543210,58294),0x543210));assert len(N)==16471
assert N[2].op_str=='esp, 0x218'
original_post=rd.pe_bytes_at(P,0x543210+58294,943)
start=next(j for j,x in enumerate(N) if x.address==0x545ade)
n=N[start:start+109];assert len(n)==109 and sum(x.size for x in n)==417
post=rd.pe_bytes_at(P,0x543210+58294,943)
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for tag,frag in variants.items():
 (O/(tag+'.inc')).write_text(frag)
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj')
 cpp.write_text(base.replace(marker,'#include "'+tag+'.inc"',1))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  rows.append({'variant':tag,'compiler_error':(cp.stdout+cp.stderr)[-450:]})
  print(tag,'COMPILE FAIL',(cp.stdout+cp.stderr)[-150:],flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==943
 tail=[r for r in refs if r['offset']>=end]
 assert len(tail)==156
 lab={};mask=set()
 for r in tail:
  o=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(o,o+4))
  mask.update(range(o,o+4))
  addr=int.from_bytes(original_post[o:o+4],'little')
  assert 0x543210<=addr<0x543210+58294
  lab.setdefault(addr,r['local_symbol_offset'])
 assert 943-len(mask)==319
 assert all(code[end+j]==original_post[j] for j in range(943) if j not in mask)
 a=lab[0x545ade]
 z=next(j for j,x in enumerate(I) if x.address==a)
 seq=I[z:z+109]
 ww=[j for j,(x,y) in enumerate(zip(N,I)) if x.size!=y.size]
 mm=[j for j,(x,y) in enumerate(zip(N,I)) if x.mnemonic!=y.mnemonic]
 gg=[j for j,(x,y) in enumerate(zip(N,I)) if roles(x)!=roles(y)]
 fields=[r for r in refs if a<=r['offset']<seq[-1].address+seq[-1].size]
 assert len(fields)==7,(tag,len(fields))
 if all(x.mnemonic==y.mnemonic for x,y in zip(n,seq)):
  nativebytes=rd.pe_bytes_at(P,0x545ade,417)
  for r in fields:
   j=next(j for j,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
   dt=r['offset']-seq[j].address
   off=n[j].address-0x545ade+dt
   assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
   value=int.from_bytes(nativebytes[off:off+4],'little',signed=r['type']=='REL32')
   dest=n[j].address+dt+4+value if r['type']=='REL32' else value
   m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
   expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
   assert dest==expected,(tag,j,r['symbol'],hex(dest),expected)
 row={'variant':tag,'compiled_full_CODE_B':end,'full_x86':len(I),
 'source_frame':I[2].op_str,'wrong_whole_mnemonics':len(mm),
 'wrong_whole_widths':ww[:25],'wrong_whole_GPR_count':len(gg),
 'native_63_source_B':sum(x.size for x in seq),'native_63_source_x86':len(seq),
 'native_63_wrong_mnemonic':[j for j,(x,y) in enumerate(zip(n,seq)) if x.mnemonic!=y.mnemonic],
 'native_63_wrong_width':[j for j,(x,y) in enumerate(zip(n,seq)) if x.size!=y.size],
 'native_63_wrong_GPR':sum(roles(x)!=roles(y) for x,y in zip(n,seq)),
 'original_afterRET_fields':sum(r['offset']>=end for r in refs)}
 rows.append(row)
 print(tag,'whole B/x86',end,len(I),'mnemonic,width,GPR wrong',len(mm),len(ww),len(gg),
 'native63',row['native_63_source_B'],len(seq),'m/w/g',len(row['native_63_wrong_mnemonic']),
 len(row['native_63_wrong_width']),row['native_63_wrong_GPR'],flush=True)
(O/'results.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==10 and all('compiler_error' not in r for r in rows)
native_summary={
 'pinned_Japanese_original_58KB_fighter':'0x00543210',
 'native_original_whole_CODE_B':58294,'native_whole_x86':16471,
 'original_native_mode63_B_x86':[417,109],
 'actual_native_mode63_original_PE_fields':7,
 'original_afterRET_DIR32_and_nonfield_B':[156,319],
 'source_stack_frame':'0x218','original_saved_this_EBP':'-0x44',
 'new_full_parent_compiler_sources':len(rows),
 'all_ten_compiled_source_CODE_B':58293,
 'all_ten_compiled_source_x86':16471,
 'best_original_full_mnemonic_width_GPR_defects':[0,3,1741],
 'actual_mode63_wrong_CMP_widths_persist':True,
 'reversed_outer_condition_has_six_extra_mnemonic_defects':True,
 'whole_original_exact':False,'new_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,
 'whole_source_profiles':rows
}
assert all((r['compiled_full_CODE_B'],r['full_x86'],
            r['original_afterRET_fields'])==(58293,16471,156) for r in rows)
for r in rows:
 if r['variant']=='reversed-pure-outer':
  assert (r['wrong_whole_mnemonics'],len(r['wrong_whole_widths']),
          r['wrong_whole_GPR_count'])==(6,7,1742)
 else:
  assert (r['wrong_whole_mnemonics'],len(r['wrong_whole_widths']),
          r['wrong_whole_GPR_count'])==(0,3,1741)
(O/'verified-summary.json').write_text(json.dumps(native_summary,indent=2)+'\n')
print('F1025 10 entire normal VC7.1 58KB original-shaped parents verified; native 0x63 true PE targets/afterRET DATA, no source fixes native CMP widths, original frame already correct. NO exact credit.')
