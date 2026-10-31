"""F882: 17 whole native Scene destructor genuine texture owner source shapes.

The original 0043B0B0 is 248 callable B /75 x86/12 PE fields.
Normal VC7.1 /Od /GX real virtual destructor:
A 4-member actual cleanup aggregate with texture field as
second-last moves the first original deleting texture temp
to native EBP-0x14, but requires an extra true MOV/store of the
scalar-deleting receiver, producing 254B/77x86, not exact.
Ten complete real 254B/77x86 forms, three 251B/76x86,
two reference forms 256B/78x86 and two native-extent
248B/75x86 forms. Only baseline and true direct typed
texture-lvalue have all original 12 physical PE field
positions and 191/200 native nonrelocation bytes.
No cropped source, fake locals, ABI changes or mass replay.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f882-scene-texture-ownership';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
original_texture='''    if (FIELD(TextureManagerF200*,0x08))
        delete FIELD(TextureManagerF200*,0x08);'''
old_struct='''struct CleanupPointersF215 {
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
old_decl='    CleanupPointersF215 released;'
assert all(base.count(s)==1 for s in (original_texture,old_struct,old_decl))
variants={'baseline':base}
def var(name,texture,body=None,struct=None):
 x=base
 if struct is not None:x=x.replace(old_struct,struct,1)
 x=x.replace(original_texture,texture,1)
 if body is not None:x=x.replace(old_decl,body,1)
 variants[name]=x
var('scoped-texture-pointer','''    if (FIELD(TextureManagerF200*,0x08)) {
        TextureManagerF200* texture = FIELD(TextureManagerF200*,0x08);
        delete texture;
    }''')
var('scoped-const-texture-pointer','''    if (FIELD(TextureManagerF200*,0x08)) {
        TextureManagerF200* const texture = FIELD(TextureManagerF200*,0x08);
        delete texture;
    }''')
var('scoped-volatile-texture-pointer','''    if (FIELD(TextureManagerF200*,0x08)) {
        TextureManagerF200* volatile texture = FIELD(TextureManagerF200*,0x08);
        delete texture;
    }''')
var('scoped-reference-texture','''    if (FIELD(TextureManagerF200*,0x08)) {
        TextureManagerF200*& texture = FIELD(TextureManagerF200*,0x08);
        delete texture;
    }''')
var('early-named-texture','''    TextureManagerF200* texture = FIELD(TextureManagerF200*,0x08);
    if (texture)
        delete texture;''')
var('early-const-texture','''    TextureManagerF200* const texture = FIELD(TextureManagerF200*,0x08);
    if (texture)
        delete texture;''')
var('early-register-texture','''    register TextureManagerF200* texture = FIELD(TextureManagerF200*,0x08);
    if (texture)
        delete texture;''')
var('early-scoped-copied-texture','''    TextureManagerF200* texture;
    if (FIELD(TextureManagerF200*,0x08)) {
        texture = FIELD(TextureManagerF200*,0x08);
        delete texture;
    }''')
var('early-named-unused-check-no','''    TextureManagerF200* texture=FIELD(TextureManagerF200*,0x08);
    if (FIELD(TextureManagerF200*,0x08))
        delete texture;''')
var('typed-cast-lvalue-texture','''    if (FIELD(TextureManagerF200*,0x08))
        delete (*reinterpret_cast<TextureManagerF200**>(
            reinterpret_cast<unsigned char*>(this)+8));''')
var('scoped-typed-pointer-to-member','''    if (FIELD(TextureManagerF200*,0x08)) {
        TextureManagerF200** texturePtr = &FIELD(TextureManagerF200*,0x08);
        delete *texturePtr;
    }''')
# Single 4-field truly used aggregate including texture and all freed values
four='''struct CleanupPointersF215 {
    TextureManagerF200* texture;
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
var('aggregate-four-texture-first',
'''    if (FIELD(TextureManagerF200*,0x08)) {
        released.texture = FIELD(TextureManagerF200*,0x08);
        delete released.texture;
    }''',struct=four,
body='    CleanupPointersF215 released;')
# Above the declaration comes after first texture access: source should hoist
# actual aggregate declaration earlier, without changing actual free effects.
s=variants['aggregate-four-texture-first']
assert s.count(old_decl)==1
s=s.replace(old_decl,'')
s=s.replace('    if (g_FrameClockModeAt0066C238 == 2 || 4)','    CleanupPointersF215 released;\n    if (g_FrameClockModeAt0066C238 == 2 || 4)',1)
variants['aggregate-four-texture-first']=s
# The order of actual members can affect /Od local physical slot numbering
for key,struct_fields in {
 'four-texture-last':'    void* digitAtlas;\n    void* firstCombo;\n    void* secondCombo;\n    TextureManagerF200* texture;\n',
 'four-texture-middle':'    void* digitAtlas;\n    TextureManagerF200* texture;\n    void* firstCombo;\n    void* secondCombo;\n',
 'four-texture-second-last':'    void* digitAtlas;\n    void* firstCombo;\n    TextureManagerF200* texture;\n    void* secondCombo;\n'}.items():
 variants[key]=s.replace(four,
                 'struct CleanupPointersF215 {\n'+struct_fields+'};',1)
# Actual scoped cleanup aggregate, deleted value also an actual member
# with the correct native one conditional lookup
for key in ('aggregate-texture-only-and-frees',):
 fourtex='''struct CleanupPointersF215 {
    TextureManagerF200* texture;
    void* digitAtlas;
    void* firstCombo;
    void* secondCombo;
};'''
 x=base.replace(old_struct,fourtex,1)
 x=x.replace(original_texture,'''    CleanupPointersF215 released;
    if (FIELD(TextureManagerF200*,0x08)) {
        released.texture = FIELD(TextureManagerF200*,0x08);
        delete released.texture;
    }''',1)
 assert x.count(old_decl)==2
 x=x.rsplit(old_decl,1)[0]+x.rsplit(old_decl,1)[1]
 variants[key]=x
sp=importlib.util.spec_from_file_location('rd882',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
sp=importlib.util.spec_from_file_location('f589882',R/'scripts/verify-scene-texture-delete-f589.py');f589=importlib.util.module_from_spec(sp);sys.modules[sp.name]=f589;sp.loader.exec_module(f589)
pe=rd.verified_target();raw=rd.pe_bytes_at(pe,0x43b0b0,248);D=Cs(CS_ARCH_X86,CS_MODE_32);orig=list(D.disasm(raw,0x43b0b0));assert len(orig)==75
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None);E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
baseline_reloc_symbols=None
for key,source in variants.items():
 cpp=O/(key+'.cpp');obj=O/(key+'.obj');cpp.write_text(source)
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=E,capture_output=True,text=True,timeout=250)
 (O/(key+'.log')).write_text(p.stdout+p.stderr)
 if p.returncode:
  row={'variant':key,'compile_failed':(p.stdout+p.stderr)[-230:]}
  rows.append(row);print(json.dumps(row),flush=True);continue
 try:code,refs=rd.object_function(obj,'??1BattleSceneF200@@UAE@XZ')
 except ValueError as exc:print(key, 'SYMBOL FAIL',str(exc),flush=True);continue
 ins=list(D.disasm(code,0))
 assert len(refs)==12 and all(r['addend']==0 for r in refs)
 symbols=sorted((r['type'],r['symbol'],r['addend']) for r in refs)
 if key=='baseline':baseline_reloc_symbols=symbols
 assert symbols==baseline_reloc_symbols, 'different original native destructor calls produced '+key
 row={'variant':key,'whole_CODE_B':len(code),'whole_x86':len(ins),'COFF_fields':len(refs)}
 if len(ins)>62:
  row['native_role_ordinals_26_28_42_52_62']=[ins[i].op_str for i in (26,28,42,52,62)]
 if len(code)==248 and len(ins)==75 and len(refs)==12:
  result=rd.compare(obj,'??1BattleSceneF200@@UAE@XZ',0x43b0b0,248)
  row['genuine_native_nonfield_matching']=result['matched_comparable_bytes']
  row['true_native_comparable_B']=result['comparable_bytes']
  row['original_pe_12_physical_fields_all_equal']=all(
   int(f['offset'],16) in f589.ORIGINAL_COFF
   and f['type']==f589.ORIGINAL_COFF[int(f['offset'],16)][0]
   and int(f['solved_destination'],16)==f589.ORIGINAL_COFF[int(f['offset'],16)][1]
   and f['object_addend']=='0x00000000'
   for f in result['relocations'])
  row['actual_byte_offsets_wrong']=[i for i in range(248) if i not in {j for f in refs for j in range(f['offset'],f['offset']+4)} and code[i]!=raw[i]]
 rows.append(row);print(json.dumps(row),flush=True)
(O/'explore-summary.json').write_text(json.dumps(rows,indent=2)+'\n')

assert len(rows)==17
by={x['variant']:x for x in rows}
assert all('compile_failed' not in x for x in rows), 'one of the real C++ native source cases failed compiler'
assert sum(x.get('whole_CODE_B')==248 for x in rows)==2
assert sum(x.get('whole_CODE_B')==251 for x in rows)==3
assert sum(x.get('whole_CODE_B')==254 for x in rows)==10
assert sum(x.get('whole_CODE_B')==256 for x in rows)==2
for name in ('baseline','typed-cast-lvalue-texture'):
 r=by[name]
 assert (r['whole_CODE_B'],r['whole_x86'],r['COFF_fields'])==(248,75,12)
 assert r['genuine_native_nonfield_matching']==191
 assert r['true_native_comparable_B']==200
 assert r['original_pe_12_physical_fields_all_equal'] is True
 assert r['actual_byte_offsets_wrong']==[94,97,100,103,111,176,179,206,209]
for name in ('aggregate-four-texture-first','four-texture-middle',
             'four-texture-second-last','four-texture-last'):
 r=by[name]
 assert (r['whole_CODE_B'],r['whole_x86'],r['COFF_fields'])==(254,77,12)
assert by['four-texture-second-last']['native_role_ordinals_26_28_42_52_62'][0]=='dword ptr [ebp - 0x14], edx'
assert by['four-texture-second-last']['native_role_ordinals_26_28_42_52_62'][1]=='dword ptr [ebp - 0x24], eax'
assert [x['offset'] for x in rd.object_function(O/'four-texture-second-last.obj',
                      '??1BattleSceneF200@@UAE@XZ')[1]]==[
 6,12,20,35,49,70,119,158,188,218,236,246]
assert list(sorted(f589.ORIGINAL_COFF))==[
 6,12,20,35,49,70,113,152,182,212,230,240]
# First six physical PE fields are the same, later six move
# +6B: therefore never crop or treat the native first slot as
# whole original matching code.
(O/'verified-summary.json').write_text(json.dumps({
 'original_whole_scene_destructor':'0x0043B0B0',
 'real_native_whole_CODE_B':248,
 'real_native_full_x86_count':75,
 'real_physical_PE_relocation_fields':12,
 'genuine_texture_and_resource_owner_source_variants':len(rows),
 'native_original_texture_EBP_slot':'-0x14',
 'native_original_delete_receiver_EBP_slot':'-0x10',
 'source_four_field_second_last_texture_first_slot':'-0x14',
 'source_four_field_second_last_delete_receiver':'-0x24',
 'nonoriginal_four_field_member_actual_SOURCE_B':254,
 'nonoriginal_four_field_member_actual_source_x86':77,
 'four_field_original_later_six_PE_offsets':[113,152,182,212,230,240],
 'four_field_actual_later_six_PE_offsets':[119,158,188,218,236,246],
 'whole_sized_native_248B_source_count':2,
 'two_whole_sized_source_original_nonfield_match':'191/200',
 'two_whole_sized_source_actual_bad_stack_byte_offsets':[94,97,100,103,111,176,179,206,209],
 'original_whole_function_exact':False,
 'new_accepted_authored_whole_callable_CODE_B':0,
 'all_units_cold_replay':False,
 'all_complete_original_scene_Cpp_source_variants':rows
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['original_whole_function_exact'] is False
print('F882 real Scene original248B/75-x86/12 physical PE fields; 17 WHOLE genuine texture-local/cleanup-aggregate source controls. One 4-field actual resource owner yields true texture EBP-0x14 but introduces two real MOVs, 254B/77x86, and shifts 6 PE call fields +6. Two true 248B sources remain 191/200 nonfield, 9 real stack bytes wrong. No whole exact CODE, no mass replay.')
