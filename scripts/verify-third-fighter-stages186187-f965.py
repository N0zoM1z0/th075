#!/usr/bin/env python3
"""F965: genuine 004AC040 native 186/187 whole-parent C++ and PE evidence.

Fresh-compile TRACKED old F964 and new F965 complete normal pinned
VC7.1 original-shaped PARTIAL 82KB fathers; decode complete original
136/186/187 callable internal case extents, 7+11 native PE external
fields, authentic afterRET 151 DIR32 target labels and 522 nonfield DATA.
Native 186 has NO physical afterRET label: derive it from the real
136 134-x86 source end, followed by genuine 187 label.
Not independent callable original exact game CODE.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f965-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F964-prior-markers':R/'probes/FighterWhole004AC040F964.cpp',
         'F965-real-186-187':R/'probes/FighterWhole004AC040F965.cpp'}
p=(R/'probes/FighterThirdBossStages186187F965.inc').read_text()
assert p.count('case 0x186:')==p.count('case 0x187:')==1
assert sources['F965-real-186-187'].read_text().count('#include "FighterThirdBossStages186187F965.inc"')==1
sp=importlib.util.spec_from_file_location('f965reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIGINAL_B=82796;ORIGINAL_X86=22721;DATA=1126
original_parent=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIGINAL_B),BASE))
assert len(original_parent)==ORIGINAL_X86 and original_parent[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+ORIGINAL_B,DATA)
native_def={'136':(0x4B1A98,0x4B1C5B,451,134,11),
            '186':(0x4B1C5B,0x4B1D70,277,84,7),
            '187':(0x4B1D70,0x4B1F1D,429,124,11)}
native={}
for key,(a,b,n,nx,nf) in native_def.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,n),a))
 assert b-a==n and len(I)==nx and I[-1].address+I[-1].size==b
 native[key]=I
assert native['186'][19].op_str=='dword ptr [edx + 0x50], 0x41200000'
assert native['186'][80].op_str=='0x324' and native['186'][82].op_str=='0x453b50'
assert native['187'][15].op_str=='word ptr [eax + 0x80], 2'
assert native['187'][63].op_str=='0xe'
assert native['187'][86].op_str=='dword ptr [eax + 0x50], 0x41700000'
assert native['187'][120].op_str=='0xc'
assert not any(int.from_bytes(native_data[j:j+4],'little')==0x4B1C5B
               for j in range(DATA-3))
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
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
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
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
  va=int.from_bytes(native_data[off:off+4],'little')
  assert BASE<=va<BASE+ORIGINAL_B
  labels.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+i]==native_data[i] for i in range(DATA) if i not in mask)
 assert 0x4B1C5B not in labels
 assert all(a in labels for a in (0x4B1A98,0x4B1D70,0x4B1F1D))
 d136_start=labels[0x4B1A98]
 idx=next(j for j,x in enumerate(I) if x.address==d136_start)
 d136=I[idx:idx+134]
 boundary186=d136[-1].address+d136[-1].size
 assert len(d136)==134 and boundary186-d136_start==451
 assert [x.mnemonic for x in d136]==[x.mnemonic for x in native['136']]
 assert [x.size for x in d136]==[x.size for x in native['136']]
 row={'original_whole_game_CODE_B':ORIGINAL_B,
      'original_whole_x86':ORIGINAL_X86,
      'compiled_partial_father_CODE_B':ret,'compiled_partial_father_x86':len(I),
      'original_186_missing_afterRET_label':True,
      'original_136_source_end_is_186_start':True,
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_exact_B':522,
      'whole_source_COFF_fields_total':len(refs),'real_handlers':{},
      'whole_original_exact':False}
 for name,(a,b,n,nx,nfields) in native_def.items():
  source_start=boundary186 if name=='186' else labels[a]
  source_end=boundary186 if name=='136' else labels[b]
  s=[x for x in I if source_start<=x.address<source_end]
  fields=[r for r in refs if source_start<=r['offset']<source_end]
  v={'original_native_CODE_B':n,'original_x86':nx,
    'source_CODE_B':source_end-source_start,'source_x86':len(s)}
  if len(s)==nx and source_end-source_start==n:
   m=[j for j,(x,y) in enumerate(zip(native[name],s)) if x.mnemonic!=y.mnemonic]
   w=[j for j,(x,y) in enumerate(zip(native[name],s)) if x.size!=y.size]
   g=[j for j,(x,y) in enumerate(zip(native[name],s)) if roles(x)!=roles(y)]
   v.update({'bad_original_mnemonic_ordinals':m,
             'bad_original_width_ordinals':w,'bad_original_GPR_ordinals':g})
   if not m and not w:
    assert len(fields)==nfields,(name,len(fields),nfields)
    raw=rd.pe_bytes_at(PE,a,n)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     off=r['offset']-s[j].address
     physical_off=native[name][j].address-a+off
     assert physical_off==r['offset']-source_start
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[physical_off:physical_off+4],
                        'little',signed=r['type']=='REL32')
     target=native[name][j].address+off+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,name,j,r['symbol'],hex(target),expected)
    v['native_original_PE_targets_verified']=len(fields)
  row['real_handlers'][name]=v
 rows[label]=row
 print(label,'full source',ret,len(I),'186/187',
  [(k,row['real_handlers'][k]['source_CODE_B'],row['real_handlers'][k]['source_x86'])
   for k in ('186','187')],flush=True)
old=rows['F964-prior-markers'];new=rows['F965-real-186-187']
assert (old['compiled_partial_father_CODE_B'],old['compiled_partial_father_x86'])==(24566,6746)
assert (new['compiled_partial_father_CODE_B'],new['compiled_partial_father_x86'])==(25242,6950)
for name in ('186','187'):
 assert old['real_handlers'][name]['source_CODE_B']==15
 item=new['real_handlers'][name]
 assert (item['source_CODE_B'],item['source_x86'])==native_def[name][2:4]
 assert item['bad_original_mnemonic_ordinals']==item['bad_original_width_ordinals']==[]
 assert item['native_original_PE_targets_verified']==native_def[name][4]
assert len(new['real_handlers']['186']['bad_original_GPR_ordinals'])==53
assert len(new['real_handlers']['187']['bad_original_GPR_ordinals'])==78
assert len(new['real_handlers']['136']['bad_original_GPR_ordinals'])==84
assert new['real_handlers']['136']['native_original_PE_targets_verified']==11
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_82KB_fighter':'0x004AC040',
 'native_whole_callable_CODE_B':ORIGINAL_B,'native_whole_x86':ORIGINAL_X86,
 'genuine_186_original_CODE_B_x86':[277,84],
 'genuine_187_original_CODE_B_x86':[429,124],
 'native_186_187_external_PE_targets_verified':18,
 'source_186_187_mnemonic_width_errors':0,
 'native_186_187_remaining_GPR_errors':[53,78],
 'true_186_has_no_jump_table_label':True,
 'whole_original_exact':False,'new_accepted_exact_original_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_partial_Cpp_source_profiles':rows
},indent=2)+'\n')
print('F965 original 186/187 source 706 native inner B/208 x86, 18 genuine PE targets; zero positional mnemonic/width errors but 53/78 GPR errors. Original giant NONEXACT.')
