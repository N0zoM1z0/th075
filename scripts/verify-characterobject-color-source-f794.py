"""F794: genuine typed color owner and stage source in complete 33KB game boss.

All ten generated original-shaped full VC7.1 TUs are compared
against independent original PE CODE/DATA, all 8,789 x86 and
682 authentic physical PE/COFF fields. No split-case CODE credit.
"""
from pathlib import Path
import importlib.util,os,sys,json,subprocess
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f794-character-color-owner';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f794_rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
spec=importlib.util.spec_from_file_location('f794_f593',R/'scripts/verify-characterobject-whole-geometry-f593.py')
f593=importlib.util.module_from_spec(spec);sys.modules[spec.name]=f593;spec.loader.exec_module(f593)
boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x004EBDA0)
tab=boss['tables'][0]
pe=rd.verified_target()
sw=rd.pe_bytes_at(pe,tab['dense_addr'],tab['slots']*4)
idx=rd.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
s=(R/'probes/CharacterObjectActionsF572.cpp').read_text()
start=s.index('        case 0x38D: {');stop=s.index('        case 0x38E: {',start)
case=s[start:stop]
assert case.count('U8(0x11)')==4 and case.count('U8(0x12)')==2
struct='''struct BorrowedCharacterColorF794 {
    unsigned char observedTo11[0x11];
    unsigned char redAt11;
    unsigned char greenAt12;
    unsigned char blueAt13;
    unsigned char alphaAt14;
};
'''
c=case
for raw,member in [('U8(0x11)','redAt11'),('U8(0x12)','greenAt12'),('U8(0x13)','blueAt13'),('U8(0x14)','alphaAt14')]:
 c=c.replace(raw,'reinterpret_cast<BorrowedCharacterColorF794*>(this)->'+member)
variants={
 'baseline':case,
 'typed-four-color':c,
 'typed-four-color-const-lvalue':c.replace('reinterpret_cast<BorrowedCharacterColorF794*>(this)->redAt11>=20','(*(&reinterpret_cast<BorrowedCharacterColorF794*>(this)->redAt11))>=20'),
 'reverse-color-limit':case.replace('U8(0x11)>=20','20<=U8(0x11)'),
 'post-increment-stage':case.replace('++S16(0x80)','S16(0x80)++'),
 'reverse-stage-six':case.replace('I32(0x7C)==6','6==I32(0x7C)'),
 'explicit-color-subtract':case.replace('U8(0x11)-=20','U8(0x11)=static_cast<unsigned char>(U8(0x11)-20)').replace('U8(0x12)-=20','U8(0x12)=static_cast<unsigned char>(U8(0x12)-20)').replace('U8(0x13)-=20','U8(0x13)=static_cast<unsigned char>(U8(0x13)-20)'),
 'zero-state-readonly':case.replace('S16(0xD8)=0;','*(&S16(0xD8))=0;').replace('I32(0x7C)=0;','*(&I32(0x7C))=0;'),
 'stage-condition-reorder':case.replace('S16(0x62)==3 && S16(0x64)==0','S16(0x64)==0 && S16(0x62)==3'),
 'typed-one-alpha':case.replace('U8(0x11)=0xFF;','reinterpret_cast<BorrowedCharacterColorF794*>(this)->redAt11=0xFF;'),
}
native=rd.pe_bytes_at(pe,0x004ebda0,33731)
d=Cs(CS_ARCH_X86,CS_MODE_32)
orig_inst=list(d.disasm(native[:33293],0));assert len(orig_inst)==8789
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
assert boss['size']==33293 and boss['postret_size']==438 and len(variants)==10
rows=[]
for name,v in variants.items():
 src=struct+s[:start]+v+s[stop:]
 cpp=O/(name+'.cpp');obj=O/(name+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],cwd=R,env=E,capture_output=True,text=True,timeout=240)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  print(name,'COMPILE FAIL',(cp.stdout+cp.stderr)[-400:],flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ')
 inst=[]
 for a in d.disasm(code,0):
  inst.append(a)
  if a.mnemonic=='ret':break
 ret=inst[-1].address+inst[-1].size
 row={'variant':name,'whole_source_CODE_B':ret,'orig_CODE_B':33293,
      'source_x86':len(inst),'orig_x86':8789,'source_COFF':len(refs)}
 if not (len(code)==33731 and ret==33293 and len(inst)==8789 and len(refs)==682):
  raise ValueError('F794 whole native 33KB original CODE/DATA/x86/COFF extent drift '+name)
 fields,slots=f593.physical_all_COFF(rd,pe,code,refs,ret,sw,idx)
 assert len(fields)==682 and len(slots)==60, name+' original PE/COFF field/handler problem'
 if len(code)==33731 and ret==33293 and len(inst)==8789 and len(refs)==682:
  masks={x for r in refs for x in range(r['offset'],r['offset']+4)}
  wrong=[i for i in range(33731) if i not in masks and code[i]!=native[i]]
  row['wrong_total_nonfield_B']=len(wrong)
  row['wrong_first_machine_offsets']=[hex(i) for i in wrong[:20]]
  row['source_native_mnemonic_ordinals_bad']=[j for j,(a,b) in enumerate(zip(orig_inst,inst)) if a.mnemonic!=b.mnemonic][:20]
  row['source_native_instr_width_bad']=[j for j,(a,b) in enumerate(zip(orig_inst,inst)) if a.size!=b.size][:20]
 if name=='stage-condition-reorder':
  assert row['wrong_total_nonfield_B']==152 and row['source_native_instr_width_bad']==[8042,8046] and row['source_native_mnemonic_ordinals_bad']==[8042,8046]
 else:
  assert row['wrong_total_nonfield_B']==137 and row['source_native_instr_width_bad']==[] and row['source_native_mnemonic_ordinals_bad']==[]
 row['genuine_original_COFF_fields_independently_verified']=682
 row['complete_original_afterRET_jump_DATA_checked']=438
 rows.append(row);print(json.dumps(row),flush=True)
assert len(rows)==10
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_PE_target':'0x004EBDA0',
 'original_entire_CODE_B':33293,
 'original_and_source_x86':8789,
 'original_independent_afterRET_DATA_B':438,
 'original_genuine_COFF_fields':682,
 'original_real_switch_targets':60,
 'original_native_nonrelocated_bytes':31003,
 'native_nonrelocation_byte_difference_minimum':137,
 'all_10_whole_parent_variants':rows,
 'official_accepted_callable_CODE_delta':0,
 'full_accepted_unit_cold_replay':False,
},indent=2)+'\n')
print('F794: ten complete 33KB CharacterObject VC7.1 parents verified against 682 genuine physical original PE fields; 137 wrong GPR bytes remain or worse 152 for re-ordered branch. All 438B afterRET table verified; no exact game credit.',flush=True)
