#!/usr/bin/env python3
"""F963: real 004AC040 native 133/134 (282B/84x86, 516B/152x86).

Serially cold-compile the two TRACKED, entire original-shaped partial
82KB VC7.1 fathers (F962 old markers versus F963 real states).
Independently check pinned Japanese PE: 131/133/134 true x86,
7+12 real typed PE external targets for 133/134, genuine afterRET
151 physical DIR32 case labels and 522 nonfield DATA bytes.
The whole original is still incomplete, with nonnative GPR/EBP roles.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f963-third-original-stage-proof'
OUT.mkdir(parents=True,exist_ok=True)
sources={
 'F962-old-markers':ROOT/'probes/FighterWhole004AC040F962.cpp',
 'F963-real-133-134':ROOT/'probes/FighterWhole004AC040F963.cpp',
}
frag=(ROOT/'probes/FighterThirdBossStage133134F963.inc').read_text()
assert frag.count('case 0x133:')==1 and frag.count('case 0x134:')==1
assert sources['F962-old-markers'].read_text().count('case 0x133: g_FighterProbeMarker = 308; break;')==1
assert sources['F963-real-133-134'].read_text().count('#include "FighterThirdBossStage133134F963.inc"')==1

sp=importlib.util.spec_from_file_location('f963reader',ROOT/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
BASE=0x004AC040;ORIG_B=82796;ORIG_X86=22721;POSTRET_B=1126
native_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIG_B),BASE))
assert len(native_whole)==ORIG_X86 and native_whole[-1].address+native_whole[-1].size==BASE+ORIG_B
assert native_whole[2].op_str=='esp, 0x720'
native_data=rd.pe_bytes_at(PE,BASE+ORIG_B,POSTRET_B)
physical={
 '131':(0x004B14C9,0x004B1593,202,58,5),
 '133':(0x004B1593,0x004B16AD,282,84,7),
 '134':(0x004B16AD,0x004B18B1,516,152,12),
}
original={}
for k,(lo,hi,size,nx,nrefs) in physical.items():
 inst=list(D.disasm(rd.pe_bytes_at(PE,lo,size),lo))
 assert hi-lo==size and len(inst)==nx and inst[-1].address+inst[-1].size==hi
 original[k]=inst
# Independently observed, actor-specific native source original:
assert original['133'][51].mnemonic=='cmp' and original['133'][51].op_str=='edx, 4'
assert original['133'][57].op_str=='0x1c'
assert original['133'][80].op_str=='0x324' and original['133'][82].op_str=='0x453b50'
assert original['134'][51].op_str=='edx, 0xe'
assert original['134'][75].op_str=='0xe'
assert original['134'][123].op_str=='0x336'
assert original['134'][125].op_str=='0x453b50'
assert original['134'][134].op_str=='0x1d'
role_re=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(role_re.findall(ins.op_str))

env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,source_cpp in sources.items():
 obj=OUT/(label+'.obj')
 cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source_cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=ROOT,env=env,text=True,capture_output=True,timeout=340)
 (OUT/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 assert len(code)-ret==POSTRET_B
 jump=[r for r in refs if r['offset']>=ret]
 assert len(jump)==151
 labels={};mask=set()
 for r in jump:
  delta=r['offset']-ret
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(delta,delta+4))
  mask.update(range(delta,delta+4))
  target=int.from_bytes(native_data[delta:delta+4],'little')
  assert BASE<=target<BASE+ORIG_B
  labels.setdefault(target,r['local_symbol_offset'])
 assert POSTRET_B-len(mask)==522
 assert all(code[ret+i]==native_data[i] for i in range(POSTRET_B) if i not in mask)

 row={
  'whole_original_callable_CODE_B':ORIG_B,
  'whole_original_x86':ORIG_X86,
  'whole_partial_source_CODE_B':ret,
  'whole_partial_source_x86':len(I),
  'native_saved_this_EBP':'-0x64',
  'original_full_frame':'0x720',
  'afterRET_native_local_DIR32_fields':151,
  'afterRET_original_nonfield_equal_B':522,
  'source_COFF_record_count':len(refs),
  'original_cases':{},
  'original_whole_game_exact':False,
 }
 for action,(a,b,size,nx,nfields) in physical.items():
  assert a in labels and b in labels
  lo,hi=labels[a],labels[b]
  part=[x for x in I if lo<=x.address<hi]
  refs_local=[r for r in refs if lo<=r['offset']<hi]
  candidate={
    'original_CODE_B':size,'original_x86':nx,
    'source_CODE_B':hi-lo,'source_x86':len(part),
    'actual_native_PE_external_targets_verified':0,
  }
  if len(part)==nx and hi-lo==size:
   wrong_m=[i for i,(x,y) in enumerate(zip(original[action],part)) if x.mnemonic!=y.mnemonic]
   wrong_w=[i for i,(x,y) in enumerate(zip(original[action],part)) if x.size!=y.size]
   wrong_r=[i for i,(x,y) in enumerate(zip(original[action],part)) if roles(x)!=roles(y)]
   candidate.update({'wrong_original_mnemonic_ordinals':wrong_m,
                     'wrong_original_width_ordinals':wrong_w,
                     'wrong_original_GPR_ordinals':wrong_r})
   if not wrong_m and not wrong_w:
    assert len(refs_local)==nfields,(label,action,len(refs_local),nfields)
    source_bytes=rd.pe_bytes_at(PE,a,size)
    field_mask=set()
    for r in refs_local:
     ix=next(i for i,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     displacement=r['offset']-part[ix].address
     native_field=original[action][ix].address-a+displacement
     assert r['offset']-lo==native_field,(action,ix,native_field,r['offset']-lo)
     assert r['type'] in ('DIR32','REL32')
     assert r['addend']==0 and r['local_symbol_offset'] is None
     assert all(j not in field_mask for j in range(native_field,native_field+4))
     field_mask.update(range(native_field,native_field+4))
     raw=int.from_bytes(source_bytes[native_field:native_field+4],
                        'little',signed=r['type']=='REL32')
     native_target=(original[action][ix].address+displacement+4+raw
                    if r['type']=='REL32' else raw)
     symbol=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=(int(symbol.group(1),16) if symbol else
               0x6406AC if r['symbol']=='__ftol2' else None)
     assert native_target==expected,(label,action,ix,r['symbol'],hex(native_target),expected)
    candidate['actual_native_PE_external_targets_verified']=len(refs_local)
  row['original_cases'][action]=candidate
 rows[label]=row
 print(label,'partial-parent CODE',ret,'x86',len(I),
       'cases',[(act,row['original_cases'][act]['source_CODE_B'],
                row['original_cases'][act]['source_x86'],
                len(row['original_cases'][act].get('wrong_original_GPR_ordinals',[])))
                for act in physical],flush=True)
base=rows['F962-old-markers'];new=rows['F963-real-133-134']
assert (base['whole_partial_source_CODE_B'],base['whole_partial_source_x86'])==(22896,6247)
assert (new['whole_partial_source_CODE_B'],new['whole_partial_source_x86'])==(23664,6479)
for action in ('133','134'):
 old=base['original_cases'][action]
 assert old['source_CODE_B']==15 and old['source_x86']==2
 item=new['original_cases'][action]
 assert (item['source_CODE_B'],item['source_x86'])==physical[action][2:4]
 assert item['wrong_original_mnemonic_ordinals']==[]
 assert item['wrong_original_width_ordinals']==[]
 assert item['actual_native_PE_external_targets_verified']==physical[action][4]
assert len(new['original_cases']['133']['wrong_original_GPR_ordinals'])==53
assert len(new['original_cases']['134']['wrong_original_GPR_ordinals'])==98
assert len(new['original_cases']['131']['wrong_original_GPR_ordinals'])==36
assert new['original_cases']['131']['actual_native_PE_external_targets_verified']==5

(OUT/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_82KB_fighter':'0x004AC040',
 'original_complete_callable_CODE_B':ORIG_B,
 'original_complete_x86':ORIG_X86,
 'native_new_133_CODE_B_x86':[282,84],
 'native_new_134_CODE_B_x86':[516,152],
 'native_new_133_134_PE_targets':7+12,
 'native_new_133_134_wrong_GPR_roles':[53,98],
 'native_original_x86_mnemonics_and_widths_match':True,
 'native_original_stack_and_register_roles_incomplete':True,
 'whole_original_exact':False,
 'new_accepted_exact_whole_game_CODE_B':0,
 'mass_cold_replay':False,
 'whole_partial_source_profiles':rows,
},indent=2)+'\n')
print('F963 verified original native 133+134 798 internal B/236 x86, all mnemonic/width positions and 19 native PE call/global fields; GPR roles 53/98 wrong, 82KB game whole NONEXACT.')
