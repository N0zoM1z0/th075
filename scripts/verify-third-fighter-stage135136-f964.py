#!/usr/bin/env python3
"""F964: real original 82KB fighter cases 135/136 in full partial VC7.1 fathers.

Fresh-compile tracked F963 (old markers) and F964 (real cases) as
entire original-shaped partial 82KB fighter normal VC7.1 C++ sources.
Read pinned original 487B/137-x86 case 135 and 451B/134-x86 case136
directly from PE, validate all 12+11 actual original typed PE-target
COFF fields and the full afterRET 151 DIR32 local labels/522 DATA B.
Original physical 136->186 has no afterRET label: source ends by
exact instruction count before 186 marker; next 187 real DIR32 anchor.
Source case135 has two legitimate wrong EBP-0xA4 x87 widths; CB/135/136
native GPR roles remain nonmatching. No exact original CODE credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f964-third-native-stage-proof';O.mkdir(parents=True,exist_ok=True)
sources={
 'F963-prior-markers':R/'probes/FighterWhole004AC040F963.cpp',
 'F964-two-authentic-cases':R/'probes/FighterWhole004AC040F964.cpp',
}
included=(R/'probes/FighterThirdBossStage135136F964.inc').read_text()
assert included.count('case 0x135:')==included.count('case 0x136:')==1
assert included.count('POS48==g_ThresholdAt0065782C')==1
assert sources['F964-two-authentic-cases'].read_text().count('#include "FighterThirdBossStage135136F964.inc"')==1
reader=importlib.util.spec_from_file_location('f964reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(reader);sys.modules[reader.name]=rd;reader.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE_B=82796;WHOLE_X86=22721;POST_B=1126
whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE_B),BASE))
assert len(whole)==WHOLE_X86 and whole[-1].address+whole[-1].size==BASE+WHOLE_B
assert whole[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+WHOLE_B,POST_B)
physical={
 '133':(0x4B1593,0x4B16AD,282,84,7),
 '134':(0x4B16AD,0x4B18B1,516,152,12),
 '135':(0x4B18B1,0x4B1A98,487,137,12),
 '136':(0x4B1A98,0x4B1C5B,451,134,11),
}
original={}
for action,(lo,hi,size,nx,nfields) in physical.items():
 ins=list(D.disasm(rd.pe_bytes_at(PE,lo,size),lo))
 assert len(ins)==nx and hi-lo==size and ins[-1].address+ins[-1].size==hi
 original[action]=ins
# Native 136 has a real FUCOMPP float EQUALITY comparison on +0x48.
# Reject previously assumed ">" grammar. Native 135 has a true
# signed-facing*150 FILD temp at EBP-0xA4, not a filler local.
assert original['136'][23].mnemonic=='fld' and original['136'][23].op_str=='dword ptr [0x65782c]'
assert original['136'][24].mnemonic=='fld' and original['136'][24].op_str=='dword ptr [edx + 0x48]'
assert original['136'][25].mnemonic=='fucompp'
assert original['136'][27].mnemonic=='test' and original['136'][27].op_str=='ah, 0x44'
assert original['135'][75].op_str=='dword ptr [ebp - 0xa4], edx'
assert original['135'][76].op_str=='dword ptr [ebp - 0xa4]'
assert original['135'][81].op_str=='0x80'
assert original['136'][120].op_str=='0x337' and original['136'][122].op_str=='0x453b50'
# The actual native source afterRET contains labels for 135 and 136,
# NOT an independent switch label for next native 186 at 004B1C5B.
assert all(int.from_bytes(after[i:i+4],'little')!=0x4B1C5B
           for i in range(POST_B-3))
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(rx.findall(i.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
    cwd=R,env=env,text=True,capture_output=True,timeout=350)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==POST_B
 jump=[r for r in refs if r['offset']>=ret]
 assert len(jump)==151
 labels={};mask=set()
 for r in jump:
  off=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  original_addr=int.from_bytes(after[off:off+4],'little')
  assert BASE<=original_addr<BASE+WHOLE_B
  labels.setdefault(original_addr,r['local_symbol_offset'])
 assert POST_B-len(mask)==522
 assert all(code[ret+i]==after[i] for i in range(POST_B) if i not in mask)
 assert all(a in labels for k,(a,b,_,_,_) in physical.items())
 assert 0x4B1C5B not in labels and 0x4B1D70 in labels
 row={
 'original_whole_game_CODE_B':WHOLE_B,'original_whole_game_x86':WHOLE_X86,
 'compiled_partial_father_CODE_B':ret,'compiled_partial_father_x86':len(I),
 'source_COFF_fields_total':len(refs),
 'original_afterRET_native_DIR32_labels':151,
 'original_afterRET_nonfield_equal_B':522,
 'original_136_to_186_has_no_afterRET_label':True,
 'whole_game_exact':False,'original_case_profiles':{},
 }
 for state,(a,b,size,nx,nf) in physical.items():
  source_start=labels[a]
  start=next(i for i,x in enumerate(I) if x.address==source_start)
  if state=='136':
   # The source case boundary cannot be taken from a nonexistent
   # 186 original jump-table entry. Decode precisely the whole
   # original 136's actual 134 x86 instruction sequence.
   candidate_nx=nx if label=='F964-two-authentic-cases' else 2
   cand=I[start:start+candidate_nx]
   end=cand[-1].address+cand[-1].size
   # Immediately following 186 remains a genuine 15B/2-x86 source
   # marker, and next 187 is a real native table label in BOTH builds.
   assert labels[0x4B1D70]-end==15
  else:
   source_end=labels[b]
   cand=[x for x in I if source_start<=x.address<source_end]
   end=source_end
  fields=[r for r in refs if source_start<=r['offset']<end]
  status={'original_inner_CODE_B':size,'original_inner_x86':nx,
          'source_inner_CODE_B':end-source_start,
          'source_inner_x86':len(cand),
          'actual_original_PE_targets_verified':0}
  if len(cand)==nx:
   m=[i for i,(x,y) in enumerate(zip(original[state],cand)) if x.mnemonic!=y.mnemonic]
   w=[i for i,(x,y) in enumerate(zip(original[state],cand)) if x.size!=y.size]
   g=[i for i,(x,y) in enumerate(zip(original[state],cand)) if roles(x)!=roles(y)]
   status.update({'wrong_original_mnemonics':m,
                  'wrong_original_widths':w,'wrong_original_GPR_roles':g})
   if not m:
    assert len(fields)==nf,(label,state,len(fields),nf)
    native_bytes=rd.pe_bytes_at(PE,a,size)
    for r in fields:
     j=next(i for i,x in enumerate(cand) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-cand[j].address
     native_field=original[state][j].address-a+d
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     v=int.from_bytes(native_bytes[native_field:native_field+4],
                       'little',signed=r['type']=='REL32')
     dest=original[state][j].address+d+4+v if r['type']=='REL32' else v
     found=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(found.group(1),16) if found else 0x6406AC if r['symbol']=='__ftol2' else None
     assert dest==expected,(label,state,j,r['symbol'],hex(dest),expected)
    status['actual_original_PE_targets_verified']=len(fields)
  row['original_case_profiles'][state]=status
 results[label]=row
 print(label,'whole partial',ret,len(I),
   'real 135/136',[(k,row['original_case_profiles'][k]['source_inner_CODE_B'],
         row['original_case_profiles'][k]['source_inner_x86'],
         len(row['original_case_profiles'][k].get('wrong_original_GPR_roles',[])))
         for k in ('135','136')],flush=True)
old=results['F963-prior-markers'];new=results['F964-two-authentic-cases']
assert (old['compiled_partial_father_CODE_B'],old['compiled_partial_father_x86'])==(23664,6479)
assert (new['compiled_partial_father_CODE_B'],new['compiled_partial_father_x86'])==(24566,6746)
assert old['original_case_profiles']['135']['source_inner_CODE_B']==15
assert old['original_case_profiles']['136']['source_inner_CODE_B']==15
for state in ('133','134'):
 item=new['original_case_profiles'][state]
 assert item['source_inner_CODE_B']==physical[state][2]
 assert item['actual_original_PE_targets_verified']==physical[state][4]
assert (new['original_case_profiles']['135']['source_inner_CODE_B'],
        new['original_case_profiles']['135']['source_inner_x86'])==(481,137)
assert new['original_case_profiles']['135']['wrong_original_mnemonics']==[]
assert new['original_case_profiles']['135']['wrong_original_widths']==[75,76]
assert len(new['original_case_profiles']['135']['wrong_original_GPR_roles'])==89
assert new['original_case_profiles']['135']['actual_original_PE_targets_verified']==12
assert (new['original_case_profiles']['136']['source_inner_CODE_B'],
        new['original_case_profiles']['136']['source_inner_x86'])==(451,134)
assert new['original_case_profiles']['136']['wrong_original_mnemonics']==[]
assert new['original_case_profiles']['136']['wrong_original_widths']==[]
assert len(new['original_case_profiles']['136']['wrong_original_GPR_roles'])==84
assert new['original_case_profiles']['136']['actual_original_PE_targets_verified']==11
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_whole_game':'0x004AC040',
 'native_complete_callable_CODE_B':WHOLE_B,'native_complete_x86':WHOLE_X86,
 'native_135_original_CODE_B_x86':[487,137],
 'native_136_original_CODE_B_x86':[451,134],
 'native_135_136_actual_PE_targets':23,
 'native_135_width_ordinal_errors':[75,76],
 'native_135_136_GPR_errors':[89,84],
 'native_136_float_equality_versus_greater_than_corrected':True,
 'native_missing_136_successor_jump_label_respected':True,
 'original_entire_game_exact':False,'new_accepted_whole_game_CODE_B':0,
 'mass_cold_replay':False,'complete_partial_parent_profiles':results,
},indent=2)+'\n')
print('F964: native 135 487B/137 x86, source 481B with two long original x87 temp EBP widths; native136 451B/134 x86 source equal shape, 23 native PE targets verified; remaining 89/84 GPR roles wrong. Whole 82KB original NONEXACT.')
