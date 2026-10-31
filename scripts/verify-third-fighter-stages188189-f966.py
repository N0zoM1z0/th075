#!/usr/bin/env python3
"""F966: authentic 004AC040 native actions188/189 inside complete PARTIAL father.

Build two tracked complete original-shaped VC7.1 normal huge C++ sources.
Independently verify original 372B/106-x86/11 typed external fields
for state188 and 214B/61-x86/6 fields for 189, adjacent original
187/190 boundaries, 151 genuine DIR32 afterRET labels +522 native DATA B.
No inner-case CODE acceptance: original entire 82KB father remains NONEXACT.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f966-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F965-original-188189-markers':R/'probes/FighterWhole004AC040F965.cpp',
         'F966-real-original-188189':R/'probes/FighterWhole004AC040F966.cpp'}
srcinc=(R/'probes/FighterThirdBossStages188189F966.inc').read_text()
assert srcinc.count('case 0x188:')==srcinc.count('case 0x189:')==1
assert sources['F966-real-original-188189'].read_text().count('#include "FighterThirdBossStages188189F966.inc"')==1
sp=importlib.util.spec_from_file_location('f966reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIG_B=82796;ORIG_X86=22721;POSTRET=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIG_B),BASE))
assert len(whole)==ORIG_X86 and whole[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+ORIG_B,POSTRET)
original={
 '187':(0x4B1D70,0x4B1F1D,429,124,11),
 '188':(0x4B1F1D,0x4B2091,372,106,11),
 '189':(0x4B2091,0x4B2167,214,61,6)}
ins={}
for k,(a,b,sz,nx,fields) in original.items():
 v=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert len(v)==nx and b-a==sz and v[-1].address+v[-1].size==b
 ins[k]=v
assert ins['188'][23].mnemonic=='fucompp'
assert ins['188'][25].op_str=='ah, 0x44'
assert ins['188'][82].op_str=='eax, 6'
assert ins['188'][90].op_str=='ecx, 4'
assert ins['189'][46].op_str=='2'
assert ins['189'][57].op_str=='0x1c'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for v in D.disasm(code,0):
  I.append(v)
  if v.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==POSTRET
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 mask=set();labels={}
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(k not in mask for k in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(native_data[off:off+4],'little')
  assert BASE<=va<BASE+ORIG_B
  labels.setdefault(va,r['local_symbol_offset'])
 assert POSTRET-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(POSTRET) if i not in mask)
 assert all(v in labels for v in [0x4B1D70,0x4B1F1D,0x4B2091,0x4B2167])
 row={'original_whole_callable_CODE_B':ORIG_B,'original_whole_x86':ORIG_X86,
      'compiled_complete_partial_source_B':end,'partial_source_x86':len(I),
      'original_afterRET_local_DIR32':151,'original_afterRET_nonfield_bytes_equal':522,
      'real_cases':{},'whole_original_exact':False,'source_COFF_fields':len(refs)}
 for action,(a,b,sz,nx,nfields) in original.items():
  lo,hi=labels[a],labels[b]
  src=[v for v in I if lo<=v.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  r={'original_native_B':sz,'original_x86':nx,
     'source_Cpp_B':hi-lo,'source_x86':len(src)}
  if len(src)==nx and hi-lo==sz:
   mm=[i for i,(x,y) in enumerate(zip(ins[action],src)) if x.mnemonic!=y.mnemonic]
   ww=[i for i,(x,y) in enumerate(zip(ins[action],src)) if x.size!=y.size]
   gg=[i for i,(x,y) in enumerate(zip(ins[action],src)) if roles(x)!=roles(y)]
   r.update({'native_wrong_mnemonics':mm,'native_wrong_widths':ww,
             'native_wrong_GPR_roles':gg})
   if not mm and not ww:
    assert len(fields)==nfields
    native_bytes=rd.pe_bytes_at(PE,a,sz)
    for f in fields:
     j=next(j for j,v in enumerate(src) if v.address<=f['offset']<v.address+v.size)
     delta=f['offset']-src[j].address
     physical=ins[action][j].address-a+delta
     assert f['offset']-lo==physical
     assert f['type'] in ('DIR32','REL32') and f['addend']==0 and f['local_symbol_offset'] is None
     offset=int.from_bytes(native_bytes[physical:physical+4],'little',signed=f['type']=='REL32')
     dest=ins[action][j].address+delta+4+offset if f['type']=='REL32' else offset
     m=re.search(r'At([0-9A-Fa-f]{6,8})',f['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if f['symbol']=='__ftol2' else None
     assert dest==expected,(label,action,j,f['symbol'],hex(dest),expected)
    r['native_PE_external_targets_verified']=nfields
  row['real_cases'][action]=r
 rows[label]=row
 print(label,'complete partial father',end,len(I),'cases',
   [(a,row['real_cases'][a]['source_Cpp_B'],row['real_cases'][a]['source_x86'])
    for a in ('187','188','189')],flush=True)
old=rows['F965-original-188189-markers'];new=rows['F966-real-original-188189']
assert (old['compiled_complete_partial_source_B'],old['partial_source_x86'])==(25242,6950)
assert (new['compiled_complete_partial_source_B'],new['partial_source_x86'])==(25798,7113)
for a in ('188','189'):
 assert old['real_cases'][a]['source_Cpp_B']==15
 row=new['real_cases'][a]
 assert (row['source_Cpp_B'],row['source_x86'])==original[a][2:4]
 assert row['native_wrong_mnemonics']==row['native_wrong_widths']==[]
 assert row['native_PE_external_targets_verified']==original[a][4]
assert len(new['real_cases']['188']['native_wrong_GPR_roles'])==63
assert len(new['real_cases']['189']['native_wrong_GPR_roles'])==38
assert new['real_cases']['187']['native_PE_external_targets_verified']==11
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_82KB_fighter':'0x004AC040',
 'original_whole_callable_CODE_B':ORIG_B,'original_whole_x86':ORIG_X86,
 'native_original_188_B_x86':[372,106],'native_original_189_B_x86':[214,61],
 'native_original_188_189_external_PE_targets':17,
 'source_original_mnemonic_and_widths_all_match':True,
 'source_native_188_189_GPR_role_errors':[63,38],
 'original_188_has_equality_float_comparison':True,
 'original_188_stage6_nested_stage4_check_preserved':True,
 'whole_original_exact':False,'newly_accepted_native_game_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_father_profiles':rows
},indent=2)+'\n')
print('F966 real 188 372B/106-x86/11 PE and 189 214B/61-x86/6 PE source-backed in whole 25798B father, genuine GPR errors 63/38, no original exact whole callable CODE.')
