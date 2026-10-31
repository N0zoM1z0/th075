#!/usr/bin/env python3
"""F1012 real native 303 angle geometry, and preceding 302 JMP recovery.

Fresh normal VC7.1 compile TWO tracked entire original-shaped PARTIAL
82KB fathers, prior F1011 303 marker vs F1012 actual 303 source.
Native original303 1014B/267x86, 29 real typed PE fields, correct
external math call00483300 and __ftol2, signed F04+=F06,
true borrowed opponent-X FIMUL memory, and native
FLD member/FMUL global for both real float velocity casts.
The generated source has all mnemonic/GPR roles and all but the
final near-vs-short shared JMP width. Genuine later 303 source
repairs preceding302 last shared JMP width to native near form.
Verify original 151 afterRET DIR32 and 522 true nonfield DATA B,
and six earlier independently restored 2C0..2C3/2E5/2E6
plus 2F9/2FA/2FB. The incomplete 82KB father is NEVER exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1012-third-native-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F1011-prior-303-marker':R/'probes/FighterWhole004AC040F1011.cpp',
 'F1012-real-angle303':R/'probes/FighterWhole004AC040F1012.cpp'}
inc=(R/'probes/FighterThirdBossArc303F1012.inc').read_text()
assert inc.count('case 0x303:')==1
assert inc.count('F1012_AngleAt00483300(')==1
assert inc.count('S16(0xF04)+=S16(0xF06);')==1
assert inc.count('reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44')==1
assert inc.count('S16(0xF08)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);')==1
assert sources['F1012-real-angle303'].read_text().count('#include "FighterThirdBossArc303F1012.inc"')==1
sp=importlib.util.spec_from_file_location('f1012reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;NATIVE_CODE=82796;NATIVE_X86=22721;DATA=1126
native_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE_CODE),BASE))
assert len(native_whole)==NATIVE_X86 and native_whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+NATIVE_CODE,DATA)
cases={
 '2C0':(0x4BC0A8,0x4BC29A,498,135,14),
 '2C1':(0x4BC29A,0x4BC4A4,522,141,14),
 '2C2':(0x4BC4A4,0x4BC6A7,515,138,14),
 '2C3':(0x4BC6A7,0x4BC8B1,522,141,14),
 '2E5':(0x4BD017,0x4BD314,765,199,14),
 '2E6':(0x4BD314,0x4BDB1E,2058,590,47),
 '2F9':(0x4BEC88,0x4BF16E,1254,326,33),
 '2FA':(0x4BF16E,0x4BF40E,672,186,18),
 '2FB':(0x4BF40E,0x4BF9A2,1428,411,33),
 '302':(0x4BF9A2,0x4BFDAB,1033,279,25),
 '303':(0x4BFDAB,0x4C01A1,1014,267,29)}
native={}
for k,(a,b,sz,nx,nf) in cases.items():
 ins=list(D.disasm(rd.pe_bytes_at(PE,a,sz),a))
 assert b-a==sz and len(ins)==nx and ins[-1].address+ins[-1].size==b
 native[k]=ins
n=native['303']
assert n[9].op_str=='0x453e20'
assert n[19].op_str=='0x455580'
assert n[33].op_str=='dword ptr [0x65782c]'
assert n[45].op_str=='dword ptr [0x65747c]'
assert n[111].op_str=='dword ptr [0x657888]'
assert n[112].op_str=='0x6406ac' and n[118].op_str=='0x6406ac'
assert n[116].op_str.endswith('+ 0x54]') and n[117].op_str=='dword ptr [0x657888]'
assert n[137].op_str=='0x40fb70'
assert n[144].op_str=='dword ptr [0x6591ec]' and n[159].op_str=='0x388'
assert n[161].op_str=='0x453a70'
assert n[166].op_str=='dword ptr [0x658044]' and n[173].op_str=='dword ptr [0x658044]'
assert n[226].mnemonic=='mov' and n[227].mnemonic=='fld'
assert n[232].mnemonic=='fimul'
assert n[245].op_str=='0x483300' and n[248].op_str=='0x6406ac'
assert n[-1].mnemonic=='jmp' and n[-1].op_str=='0x4c03a7' and n[-1].size==5
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
 assert len(code)-ret==DATA
 table=[r for r in refs if r['offset']>=ret]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  offset=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(offset,offset+4))
  mask.update(range(offset,offset+4))
  addr=int.from_bytes(after[offset:offset+4],'little')
  assert BASE<=addr<BASE+NATIVE_CODE
  labels.setdefault(addr,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[ret+j]==after[j] for j in range(DATA) if j not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in cases.values())
 row={'original_entire_callable_CODE_B':NATIVE_CODE,'original_whole_x86':NATIVE_X86,
      'partial_SOURCE_CODE_B':ret,'partial_SOURCE_x86':len(I),
      'source_partial_frame':I[2].op_str,
      'native_afterRET_DIR32':151,'native_afterRET_nonfield_equal_B':522,
      'whole_original_exact':False,'cases':{}}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=labels[a],labels[b]
  s=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_B':sz,'native_x86':nx,'source_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   badm=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.mnemonic!=x.mnemonic]
   badw=[j for j,(n,x) in enumerate(zip(native[k],s)) if n.size!=x.size]
   badg=[j for j,(n,x) in enumerate(zip(native[k],s)) if roles(n)!=roles(x)]
   item.update({'wrong_native_mnemonics':badm,'wrong_native_widths':badw,
                'wrong_native_GPR_roles':badg})
   if not badm:
    assert len(fields)==nf,(label,k,len(fields),nf)
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     delta=r['offset']-s[j].address;off=native[k][j].address-a+delta
     assert off==r['offset']-lo
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+delta+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['original_PE_target_fields_verified']=nf
  row['cases'][k]=item
 rows[label]=row
 print(label,'full original-shaped PARTIAL',ret,len(I),
  '302/303',[(k,row['cases'][k]['source_B'],row['cases'][k]['source_x86']) for k in ('302','303')],flush=True)
old=rows['F1011-prior-303-marker'];new=rows['F1012-real-angle303']
assert (old['partial_SOURCE_CODE_B'],old['partial_SOURCE_x86'])==(71250,19538)
assert (new['partial_SOURCE_CODE_B'],new['partial_SOURCE_x86'])==(72252,19803)
assert old['source_partial_frame']=='esp, 0x56c' and new['source_partial_frame']=='esp, 0x584'
assert old['cases']['303']['source_B']==12
cur=new['cases']['303']
assert (cur['source_B'],cur['source_x86'])==(1011,267)
assert cur['wrong_native_mnemonics']==cur['wrong_native_GPR_roles']==[]
assert cur['wrong_native_widths']==[266]
assert cur['original_PE_target_fields_verified']==29
prev=old['cases']['302'];corrected=new['cases']['302']
assert (prev['source_B'],prev['source_x86'])==(1030,279)
assert prev['wrong_native_mnemonics']==prev['wrong_native_GPR_roles']==[]
assert prev['wrong_native_widths']==[278]
assert (corrected['source_B'],corrected['source_x86'])==(1033,279)
assert corrected['wrong_native_mnemonics']==corrected['wrong_native_widths']==corrected['wrong_native_GPR_roles']==[]
assert corrected['original_PE_target_fields_verified']==25
for k in ('2C0','2C1','2C2','2C3','2E5','2E6','2F9','2FA','2FB'):
 obj=new['cases'][k]
 assert obj['wrong_native_mnemonics']==obj['wrong_native_widths']==obj['wrong_native_GPR_roles']==[]
 assert obj['original_PE_target_fields_verified']==cases[k][4]
(O/'verified-summary.json').write_text(json.dumps({
 'original_SHA_pinned_Japanese_fighter':'0x004AC040',
 'native_entire_callable_GAME_CODE_B':NATIVE_CODE,'native_whole_x86':NATIVE_X86,
 'native_original_303_CODE_B_x86':[1014,267],
 'compiled_303_SOURCE_B_x86':[1011,267],
 'native_303_all_mnemonic_GPR_roles_match':True,
 'native_303_only_wrong_width_last_shared_JMP':[266],
 'native_303_original_typed_PE_fields_verified':29,
 'native_303_external_math_00483300_and_ftol2_verified':True,
 'real_303_source_repairs_previous_302_shared_JMP_width':{'before':[278],'after':[]},
 'native_prior_2C0_2C3_2E5_2E6_2F9_2FA_2FB_GPR_PE_preserved':True,
 'whole_original_callable_exact':False,'new_exact_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'whole_original_shaped_partial_parent_profiles':rows
},indent=2)+'\n')
print('F1012 real original303 1014B/267x86/29 PE, all mnemonic/GPR, one terminal shared JMP width; genuine 303 restores preceding302 near JMP width. Whole fighter NONEXACT.')
