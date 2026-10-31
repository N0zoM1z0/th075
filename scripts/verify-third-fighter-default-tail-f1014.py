#!/usr/bin/env python3
"""F1014 native switch default 42B/13x86 and actual shared RET boundary.

Independently read pinned Japanese complete native 82KB fighter
and freshly compile two tracked normal VC7.1 ENTIRE original-shaped
PARTIAL sources: F1013 old marker and F1014 true default getter/
conditional setter/else getter. Verify native default at physical
004C037D..004C03A7 (42B/13x86, 3 PE targets), distinct
shared 004C03A7..004C03AC epilogue (5B/4x86), original
31B/31C/303 prior genuine source case PE/width/GPR roles,
151 genuine afterRET DIR32 local case labels/522 native DATA
nonfields. Do NOT crop away the real shared tail or award
whole native original exact CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1014-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1013-default-marker':R/'probes/FighterWhole004AC040F1013.cpp',
         'F1014-real-default':R/'probes/FighterWhole004AC040F1014.cpp'}
assert sources['F1013-default-marker'].read_text().count('default: g_FighterProbeMarker = 0;')==1
assert sources['F1014-real-default'].read_text().count('default: g_FighterProbeMarker = 0;')==0
assert sources['F1014-real-default'].read_text().count('else\n                GetNativeActionAt40FA30();')==1
sp=importlib.util.spec_from_file_location('f1014reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;NX=22721;DATA=1126
origwhole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(origwhole)==NX and origwhole[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'303':(0x4BFDAB,0x4C01A1,1014,267,29),
       '31B':(0x4C01A1,0x4C02A2,257,76,9),
       '31C':(0x4C02A2,0x4C037D,219,63,7),
       'default':(0x4C037D,0x4C03A7,42,13,3)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
ep=list(D.disasm(rd.pe_bytes_at(PE,0x4C03A7,5),0x4C03A7))
assert [(i.mnemonic,i.size) for i in ep]==[('pop',1),('mov',2),('pop',1),('ret',1)]
assert [i.op_str for i in native['default'] if i.mnemonic=='call']==['0x40fa30','0x40fac0','0x40fa30']
assert native['default'][10].op_str=='0x4c03a7'
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
 cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 assert [(i.mnemonic,i.size) for i in I[-4:]]==[(i.mnemonic,i.size) for i in ep]
 epstart=I[-4].address
 assert epstart==end-5
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  offset=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(offset,offset+4))
  mask.update(range(offset,offset+4))
  a=int.from_bytes(native_data[offset:offset+4],'little')
  assert BASE<=a<BASE+WHOLE
  labels.setdefault(a,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==native_data[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and (b in labels if k!='default' else b==0x4C03A7)
            for k,(a,b,_,_,_) in cases.items())
 row={'native_entire_GAME_CODE_B':WHOLE,'native_original_x86':NX,
      'source_whole_partial_CODE_B':end,'source_partial_x86':len(I),
      'partial_stack_frame':I[2].op_str,
      'native_shared_epilogue_B':5,'native_shared_epilogue_x86':4,
      'native_afterRET_DIR32':151,'native_nonfield_DATA_equal_B':522,
      'original_whole_exact':False,'native_states':{}}
 for key,(a,b,sz,nx,nf) in cases.items():
  lo=labels[a]
  hi=epstart if key=='default' else labels[b]
  seq=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':sz,'original_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(seq)}
  if len(seq)==nx:
   mm=[j for j,(n,x) in enumerate(zip(native[key],seq)) if n.mnemonic!=x.mnemonic]
   ww=[j for j,(n,x) in enumerate(zip(native[key],seq)) if n.size!=x.size]
   gg=[j for j,(n,x) in enumerate(zip(native[key],seq)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnem_ordinals':mm,'wrong_native_width_ordinals':ww,
                'wrong_native_GPR_ordinals':gg})
   if not mm:
    assert len(fields)==nf,(label,key,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-seq[j].address;off=native[key][j].address-a+d
     if not ww:assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     v=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     orig=native[key][j].address+d+4+v if r['type']=='REL32' else v
     mt=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(mt.group(1),16) if mt else 0x6406AC if r['symbol']=='__ftol2' else None
     assert orig==expected,(label,key,j,r['symbol'],hex(orig),expected)
    item['original_PE_fields_verified']=nf
  row['native_states'][key]=item
 rows[label]=row
 print(label,'whole PARTIAL parent',end,len(I),
       'default original-shaped',row['native_states']['default']['source_CODE_B'],
       row['native_states']['default']['source_x86'],flush=True)
old=rows['F1013-default-marker'];new=rows['F1014-real-default']
assert (old['source_whole_partial_CODE_B'],old['source_partial_x86'])==(72707,19938)
assert (new['source_whole_partial_CODE_B'],new['source_partial_x86'])==(72739,19950)
assert old['partial_stack_frame']==new['partial_stack_frame']=='esp, 0x584'
assert old['native_states']['default']['source_CODE_B']!=42
cur=new['native_states']['default']
assert (cur['source_CODE_B'],cur['source_x86'])==(42,13)
assert cur['wrong_native_mnem_ordinals']==cur['wrong_native_width_ordinals']==cur['wrong_native_GPR_ordinals']==[]
assert cur['original_PE_fields_verified']==3
for k in ('303','31B','31C'):
 r=new['native_states'][k]
 assert (r['source_CODE_B'],r['source_x86'])==cases[k][2:4]
 assert r['wrong_native_mnem_ordinals']==r['wrong_native_width_ordinals']==r['wrong_native_GPR_ordinals']==[]
 assert r['original_PE_fields_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'native_SHA_pinned_original_fighter':'0x004AC040',
 'original_complete_callable_GAME_CODE_B':WHOLE,'native_original_x86':NX,
 'native_actual_default_B_x86':[42,13],
 'all_default_mnem_width_GPR_roles_match':True,
 'native_default_genuine_PE_targets':3,
 'actual_shared_epilogue_B_x86':[5,4],
 'real_final_303_31B_31C_case_geometry_preserved':True,
 'all_original_afterRET_151_labels_522_nonfield_B_equal':True,
 'original_whole_exact':False,'new_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'full_partial_parent_profiles':rows
},indent=2)+'\n')
print('F1014 native switch default 42B/13 x86/3 PE fields and distinct original shared 5B/4x86 epilogue match; previous 303/31B/31C all exact native positional roles, giant still NONEXACT.')
