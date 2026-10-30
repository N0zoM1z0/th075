"""F838: eight complete real Scene destructor declaration/member-order controls.

Compile only original 248B/75-x86 Scene virtual destructor using actual
cleanup pointer object declaration at meaningful source lifetime sites,
or three original released-pointer field orders. Check real original
12 PE fields/types/targets and exact nonrelocation bytes, not just
source object extent. No fake padding or accepted exact unit credit.
"""
from pathlib import Path
import importlib.util,os,json,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f838-scene-declaration-placement';O.mkdir(parents=True,exist_ok=True)
baseline=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
alloc='    CleanupPointersF215 released;'
clock='    if (g_FrameClockModeAt0066C238 == 2 || 4)'
texture='    if (FIELD(TextureManagerF200*,0x08))'
freeguard='    if (FIELD(void*,0x4c)) {'
assert all(baseline.count(t)==1 for t in (alloc,clock,texture,freeguard))
cases={'baseline':baseline}
for name,loc in [('declaration-before-clock',clock),('declaration-before-texture',texture)]:
 x=baseline.replace(alloc+'\n','',1)
 x=x.replace(loc,alloc+'\n'+loc,1)
 cases[name]=x
# Assignment to the three actually freed resource pointers using a real
# aggregate can use declaration at function-entry and the same original three frees.
x=baseline.replace(alloc+'\n','',1)
x=x.replace('BattleSceneF200::~BattleSceneF200()\n{','BattleSceneF200::~BattleSceneF200()\n{\n'+alloc,1)
cases['declaration-function-top']=x
# One meaningfully used three-pointer aggregate introduced into an explicit
# conditional cleanup block; no extra null-condition or dummy local.
x=baseline.replace(alloc, '    {\n'+alloc,1)
x=x.replace('    }\n}\n#undef FIELD','    }\n    }\n}\n#undef FIELD',1)
cases['owned-release-inner-scope']=x
# Real original assignment order remains 4C/50/54, but the semantic
# aggregate member declaration order can differ.
decl='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
assert baseline.count(decl)==1
variants={'reverse-fields':'''struct CleanupPointersF215 {
    void* secondCombo;
    void* firstCombo;
    void* digitAtlas;
};''','rotate-fields':'''struct CleanupPointersF215 {
    void* firstCombo;
    void* secondCombo;
    void* digitAtlas;
};''',
 'rotate-last':'''struct CleanupPointersF215 {
    void* secondCombo;
    void* digitAtlas;
    void* firstCombo;
};'''}
for k,v in variants.items():cases[k]=baseline.replace(decl,v,1)
sp=importlib.util.spec_from_file_location('f838rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f838f589',R/'scripts/verify-scene-texture-delete-f589.py');f589=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f589;sp.loader.exec_module(f589)
native=rd.pe_bytes_at(rd.verified_target(),0x43b0b0,248);D=Cs(CS_ARCH_X86,CS_MODE_32);real=list(D.disasm(native,0x43b0b0))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for k,s in cases.items():
 cpp=O/(k+'.cpp');obj=O/(k+'.obj');cpp.write_text(s)
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=170)
 (O/(k+'.log')).write_text(p.stdout+p.stderr)
 if p.returncode:print(k,'COMPILER ERR',(p.stdout+p.stderr)[-300:],flush=True);continue
 code,refs=rd.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
 curr=list(D.disasm(code,0))
 row={'variant':k,'source_B':len(code),'x86':len(curr),'PE_fields':len(refs),'slots':[curr[i].op_str for i in (26,28,42,52,62)] if len(curr)>62 else []}
 if len(code)==248 and len(curr)==75 and len(refs)==12:
  mask=set();verified=True
  for ref in refs:
   off=ref['offset']
   if off not in f589.ORIGINAL_COFF:verified=False;continue
   typ,dst=f589.ORIGINAL_COFF[off]
   realdst=int.from_bytes(native[off:off+4],'little') if typ=='DIR32' else 0x43b0b0+off+4+int.from_bytes(native[off:off+4],'little',signed=True)
   if typ!=ref['type'] or dst!=realdst or ref['addend']!=0:verified=False
   mask.update(range(off,off+4))
  wrong=[i for i in range(248) if i not in mask and code[i]!=native[i]]
  row['native_nonfield_matching']=248-len(mask)-len(wrong)
  row['native_comparable']=248-len(mask)
  row['original_PE_fields_verified']=verified
  row['wrong_offsets']=wrong
  assert verified and len(mask)==48 and len(wrong)==(11 if k in variants else 9), (
      'physical original Scene native COFF or five stack temp offsets changed',k,wrong)
  assert all(real[j].mnemonic==curr[j].mnemonic and real[j].size==curr[j].size
             for j in range(75)), 'original Scene 75-x86 mnemonic/width geometry changed'
 rows.append(row);print(json.dumps(row),flush=True)
(O/'exploration-summary.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==8
assert sum(x.get('native_nonfield_matching')==191 for x in rows)==5
assert sum(x.get('native_nonfield_matching')==189 for x in rows)==3
assert all(x['source_B']==248 and x['x86']==75 and x['PE_fields']==12
           and x.get('original_PE_fields_verified') for x in rows)
(O/'verified-summary.json').write_text(json.dumps({
 'real_original_whole_virtual_destructor':'0x0043B0B0',
 'native_complete_CODE_B':248,
 'native_original_x86':75,
 'actual_original_typed_PE_fields':12,
 'complete_source_variants':rows,
 'actual_texture_and_delete_native_EBP_slots':['-0x14','-0x10'],
 'newly_accepted_authored_callable_CODE_B':0,
 'mass_cold_replay_run':False,
},indent=2)+'\n')
print('F838 original Scene: eight complete VC7.1 248B/75-x86 /GX candidates with all 12 genuine original PE fields; moving three real released-pointer declarations before texture/clock/function has zero CODE effect, 191/200 native nonfield. Permuting actual released fields worsens to 189/200; original texture/delete EBP slots remain wrong. No full exact credit.')
