"""F802: audit stage-four GPR phase with 22 WHOLE original 33KB C++ TUs.

Whole original PE/native call relocation checker is mandatory:
five apparently near-sized source alternatives CHANGE actual original
PE/COFF field associations and cannot be accepted as 137/140/141B
near-matches by blindly masking candidate relocation locations.
No authored exact credit, no mass cold replay.
"""
from pathlib import Path
import importlib.util,os,sys,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f802-character-stage4-grammar';O.mkdir(parents=True,exist_ok=True)
sp=importlib.util.spec_from_file_location('f802rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f802f593',R/'scripts/verify-characterobject-whole-geometry-f593.py')
f593=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f593;sp.loader.exec_module(f593)
boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==0x004EBDA0)
tab=boss['tables'][0];pe=rd.verified_target()
dense=rd.pe_bytes_at(pe,tab['dense_addr'],tab['slots']*4)
sparse=rd.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
source=Path('probes/CharacterObjectActionsF572.cpp').read_text()
a=source.index('        case 0x38D: {');b=source.index('        case 0x38E: {',a);base=source[a:b]
variants={'baseline':base}
def modify(tag,old,new):
 assert base.count(old)==1,(tag,base.count(old))
 variants[tag]=base.replace(old,new)
modify('stage-lt-reverse','if (S16(0x62)<3) {','if (3>S16(0x62)) {')
modify('stage-lt-negated','if (S16(0x62)<3) {','if (!(S16(0x62)>=3)) {')
modify('stage-lt-two','if (S16(0x62)<3) {','if (S16(0x62)<=2) {')
modify('stage-eq-four-reverse','if (S16(0x62)==4) {','if (4==S16(0x62)) {')
modify('stage-eq-four-negated','if (S16(0x62)==4) {','if (!(S16(0x62)!=4)) {')
modify('left-fade-ref','F32(0x1C)=F32(0x1C)+gFadeAt00659428;','F32(0x1C)=F32(0x1C)+*(&gFadeAt00659428);')
modify('right-fade-ref','F32(0x20)=F32(0x20)+gFadeAt00659428;','F32(0x20)=F32(0x20)+*(&gFadeAt00659428);')
modify('left-fade-compound','F32(0x1C)=F32(0x1C)+gFadeAt00659428;','F32(0x1C)+=gFadeAt00659428;')
modify('right-fade-compound','F32(0x20)=F32(0x20)+gFadeAt00659428;','F32(0x20)+=gFadeAt00659428;')
modify('right-fade-leftvalue','F32(0x20)=F32(0x20)+gFadeAt00659428;','*(&F32(0x20))=F32(0x20)+gFadeAt00659428;')
modify('left-fade-leftvalue','F32(0x1C)=F32(0x1C)+gFadeAt00659428;','*(&F32(0x1C))=F32(0x1C)+gFadeAt00659428;')
modify('stage-eq-four-convert','if (S16(0x62)==4) {','if (static_cast<int>(S16(0x62))==4) {')
modify('fade-switch-order','F32(0x1C)=F32(0x1C)+gFadeAt00659428;\n        F32(0x20)=F32(0x20)+gFadeAt00659428;','F32(0x20)=F32(0x20)+gFadeAt00659428;\n        F32(0x1C)=F32(0x1C)+gFadeAt00659428;')
modify('stage4-multiply-compound','F32(0x1C)=F32(0x1C)*gSubAt00659090;','F32(0x1C)*=gSubAt00659090;')
modify('stage4-multiply-ref','F32(0x1C)=F32(0x1C)*gSubAt00659090;','F32(0x1C)=F32(0x1C)*(*(&gSubAt00659090));')
modify('stage4-multiply-leftval','F32(0x1C)=F32(0x1C)*gSubAt00659090;','*(&F32(0x1C))=F32(0x1C)*gSubAt00659090;')
modify('stage4-color-eq','if (U8(0x11)>=20) {','if (20<=U8(0x11)) {')
modify('stage4-color-negated','if (U8(0x11)>=20) {','if (!(U8(0x11)<20)) {')
modify('stage4-color-signed-int','if (U8(0x11)>=20) {','if (static_cast<int>(U8(0x11))>=20) {')
modify('stage4-combined-refs','F32(0x1C)=F32(0x1C)*gSubAt00659090;','F32(0x1C)=*(&F32(0x1C))*(*(&gSubAt00659090));')
modify('stage4-all-mix','F32(0x1C)=F32(0x1C)*gSubAt00659090;','F32(0x1C)*=(*(&gSubAt00659090));')
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
D=Cs(CS_ARCH_X86,CS_MODE_32);target=rd.pe_bytes_at(rd.verified_target(),0x4ebda0,33731)
n=list(D.disasm(target[:33293],0))
rows=[]
assert len(variants)==22
bad_coff={'left-fade-compound','right-fade-compound','stage4-multiply-compound',
          'stage4-combined-refs','stage4-all-mix'}
for tag,fragment in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(source[:a]+fragment+source[b:])
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],cwd=R,env=E,text=True,capture_output=True,timeout=210)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:print(tag,'ERROR',(cp.stdout+cp.stderr)[-350:],flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ')
 inst=[]
 for i in D.disasm(code,0):
  inst.append(i)
  if i.mnemonic=='ret':break
 ret=inst[-1].address+inst[-1].size
 assert len(code)==33731 and ret==33293 and len(inst)==8789 and len(refs)==682
 row={'variant':tag,'CODE_B':ret,'x86':len(inst),'COFF':len(refs),'DATA_B':len(code)-ret}
 try:
  fields,real_labels=f593.physical_all_COFF(rd,pe,code,refs,ret,dense,sparse)
  assert len(fields)==682 and len(real_labels)==60
  row['all_682_original_PE_COFF_field_targets_attested']=True
 except ValueError as ex:
  assert tag in bad_coff and 'original physical COFF target identity' in str(ex), tag+' real native target relocation failed: '+str(ex)
  row['all_682_original_PE_COFF_field_targets_attested']=False
  row['real_native_relocation_mismatch_reason']=str(ex)[:210]
 if tag in bad_coff:
  assert not row['all_682_original_PE_COFF_field_targets_attested']
 else:
  assert row['all_682_original_PE_COFF_field_targets_attested']
 if len(code)==len(target) and ret==33293 and len(refs)==682 and len(inst)==8789:
  mask={i for r in refs for i in range(r['offset'],r['offset']+4)}
  diff=[i for i in range(len(target)) if i not in mask and code[i]!=target[i]]
  row['wrong_nonfield_B']=len(diff);row['first_wrong']=hex(diff[0]) if diff else None
  row['wrong_mnemonic_ordinals']=[j for j,(a,b) in enumerate(zip(n,inst)) if a.mnemonic!=b.mnemonic][:10]
  row['wrong_width_ordinals']=[j for j,(a,b) in enumerate(zip(n,inst)) if a.size!=b.size][:10]
 if tag=='baseline':
  assert row['wrong_nonfield_B']==137 and row['wrong_mnemonic_ordinals']==[] and row['wrong_width_ordinals']==[]
 if row.get('all_682_original_PE_COFF_field_targets_attested'):
  assert row.get('wrong_nonfield_B',0)>=137, tag+' unexplained native byte reduction requires independent audit'
 else:
  # A matching whole size and 682 object relocations are NOT sufficient
  # if the 4-byte fields no longer occupy the true original PE roles.
  row['candidate_masked_byte_count_NOT_an_exactness_metric']=True
 rows.append(row);print(json.dumps(row),flush=True)
assert len(rows)==22 and sum(r['all_682_original_PE_COFF_field_targets_attested'] for r in rows)==17
(O/'verified-summary.json').write_text(json.dumps({
 'original_game_boss':'0x004EBDA0','original_full_CODE_B':33293,
 'original_x86_instructions':8789,'original_afterRET_DATA_B':438,
 'original_physical_PE_COFF_fields':682,
 'fresh_full_parent_VC71_compilations':22,
 'full_native_PE_relocation_checks_accepted':17,
 'source_variants_with_WRONG_native_PE_relocations':sorted(bad_coff),
 'true_original_nonrelocation_wrong_bytes_best':137,
 'whole_boss_function_exact':False,
 'new_authored_exact_CODE_bytes':0,
 'all_unit_cold_replay_run':False,
 'variants':rows},indent=2)+chr(10))
print('F802 22 whole 33KB VC7.1 game-giant source builds, 17/22 preserve ALL original 682 physical PE refs. Five change native relocation target alignment despite identical total size; best original nonfield mismatch 137B. No callable exact credit.',flush=True)
