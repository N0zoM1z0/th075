#!/usr/bin/env python3
"""F947: source authentic 004AC040 original CF+D0 inside full partial 82KB father.

Build four complete normal-VC7.1 original-shaped C++ parents (old CF/D0
markers, CF only, D0 only, both real). Original PE is authoritative:
verify whole source/opcode stream, true original 114B/30-x86 CF and
195B/60-x86 D0, 4+6 original PE-targeted reloc fields, surrounding
native handler mapping, 151 actual DIR32 afterRET entries and 522
nonfield DATA bytes. Never claim a partial original case exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f947-third-giant-fall-reflect';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/FighterWhole004AC040F938.cpp').read_text()
pair=(R/'probes/FighterThirdBossPair5D5EF939.inc').read_text()
facing=(R/'probes/FighterThirdBossFacing5FF941.inc').read_text()
volley=(R/'probes/FighterThirdBossVolley6061F942.inc').read_text()
selector=(R/'probes/FighterThirdBossSelector62F943.inc').read_text()
src=base
for a,marker,frag in [
 (0x5D,'94',pair),(0x5E,'95',''),(0x5F,'96',facing),
 (0x60,'97',volley),(0x61,'98',''),(0x62,'99',selector)]:
 needle=f'        case 0x{a:X}: g_FighterProbeMarker = {marker}; break;'
 assert src.count(needle)==1
 src=src.replace(needle,frag,1)
assert src.count('extern float g_ThresholdAt0065782C;')==1
src=src.replace('extern float g_ThresholdAt0065782C;',
   'extern float g_ThresholdAt0065782C;\nextern float g_F748_SpeedScaleAt006590B8;',1)
CF=(R/'probes/FighterFallStateCFF647.inc').read_text()
D0=(R/'probes/FighterReflectLandingD0F646.inc').read_text()
assert CF.count('case 0xCF:')==D0.count('case 0xD0:')==1
oldcf='        case 0xCF: g_FighterProbeMarker = 208; break;'
oldd0='        case 0xD0: g_FighterProbeMarker = 209; break;'
assert src.count(oldcf)==src.count(oldd0)==1
variants={
 'F943-before-CF-D0':src,
 'F947-real-CF-only':src.replace(oldcf,CF,1),
 'F947-real-D0-only':src.replace(oldd0,D0,1),
 'F947-both-real-CF-D0':src.replace(oldcf,CF,1).replace(oldd0,D0,1)}
sp=importlib.util.spec_from_file_location('f947reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
base_addr=0x4AC040;whole=82796;whole_nx=22721;data_len=1126
original=list(D.disasm(rd.pe_bytes_at(PE,base_addr,whole),base_addr))
assert len(original)==whole_nx and original[-1].address+original[-1].size==base_addr+whole
native_table=rd.pe_bytes_at(PE,base_addr+whole,data_len)
native={
 '0xCF':(0x4B0D42,0x4B0DB4,114,30,4),
 '0xD0':(0x4B0DB4,0x4B0E77,195,60,6),
 '0xD1':(0x4B0E77,0x4B0F3E,199,59,8),
}
# Independently read source-owner boundaries and real native PE calls
# without assuming previous F652 claims are correct.
for name,(a,b,size,nx,rf) in native.items():
 assert b-a==size,(name,b-a,size)
 ins=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert len(ins)==nx and ins[-1].address+ins[-1].size==b,(name,len(ins))
 native[name]+=(ins,)
ncf=native['0xCF'][-1];nd0=native['0xD0'][-1]
assert ncf[4].mnemonic=='fsub' and ncf[4].op_str=='dword ptr [0x657478]'
assert nd0[19].mnemonic=='fld' and nd0[19].op_str=='dword ptr [0x65782c]'
assert nd0[43].mnemonic=='call' and nd0[43].op_str=='0x40fac0'
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
rows={}
for label,source in variants.items():
 cpp=O/(label+'.cpp');obj=O/(label+'.obj')
 cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=E,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1100:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for ins in D.disasm(code,0):
  I.append(ins)
  if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==data_len
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};data_mask=set()
 for r in table:
  offset=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(k not in data_mask for k in range(offset,offset+4))
  data_mask.update(range(offset,offset+4))
  native_addr=int.from_bytes(native_table[offset:offset+4],'little')
  assert base_addr<=native_addr<base_addr+whole
  labels.setdefault(native_addr,r['local_symbol_offset'])
 assert data_len-len(data_mask)==522
 assert all(code[end+i]==native_table[i] for i in range(data_len) if i not in data_mask)
 for name,(a,b,_,_,_,_) in native.items():
  assert a in labels and b in labels,(name,hex(a),hex(b))
 row={'variant':label,'whole_original_CODE_B':whole,'original_x86':whole_nx,
      'partial_compiled_father_CODE_B':end,'partial_father_x86':len(I),
      'compiled_COFF_fields':len(refs),'afterRET_original_DATA_B':data_len,
      'afterRET_native_DIR32_entries':151,'afterRET_native_nonfield_equal_B':522,
      'real_cases':{},'whole_original_exact':False}
 for name,(a,b,n,nx,nrefs,original_ins) in native.items():
  lo,hi=labels[a],labels[b]
  part=[ins for ins in I if lo<=ins.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  case={'native_B':n,'native_x86':nx,'source_B':hi-lo,'source_x86':len(part)}
  if hi-lo==n and len(part)==nx:
   badm=[i for i,(x,y) in enumerate(zip(original_ins,part)) if x.mnemonic!=y.mnemonic]
   badw=[i for i,(x,y) in enumerate(zip(original_ins,part)) if x.size!=y.size]
   badg=[i for i,(x,y) in enumerate(zip(original_ins,part)) if roles(x)!=roles(y)]
   case.update({'mnemonic_wrong':badm,'width_wrong':badw,'GPR_role_wrong':badg})
   if not badm and not badw:
    assert len(fields)==nrefs,(name,len(fields),nrefs)
    pebytes=rd.pe_bytes_at(PE,a,n)
    for r in fields:
     j=next(i for i,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
     disp=r['offset']-part[j].address
     native_field=original_ins[j].address-a+disp
     assert native_field==r['offset']-lo
     assert r['addend']==0 and r['local_symbol_offset'] is None
     assert r['type'] in ('DIR32','REL32')
     num=int.from_bytes(pebytes[native_field:native_field+4],
       'little',signed=r['type']=='REL32')
     real_target=(original_ins[j].address+disp+4+num if r['type']=='REL32' else num)
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert real_target==expected,(name,j,real_target,expected,r['symbol'])
    case['native_external_PE_targets_verified']=len(fields)
  row['real_cases'][name]=case
 rows[label]=row
 print(label,'whole emitted B',end,'x86',len(I),'CF',
   (row['real_cases']['0xCF']['source_B'],row['real_cases']['0xCF']['source_x86']),
   'D0',(row['real_cases']['0xD0']['source_B'],row['real_cases']['0xD0']['source_x86']),
   'CF/D0 GPR',[(k,len(row['real_cases'][k].get('GPR_role_wrong',[])))
        for k in ('0xCF','0xD0')],flush=True)
baseline=rows['F943-before-CF-D0'];both=rows['F947-both-real-CF-D0']
assert (baseline['partial_compiled_father_CODE_B'],baseline['partial_father_x86'])==(18234,4855)
assert (both['partial_compiled_father_CODE_B'],both['partial_father_x86'])==(18513,4941)
for name in ('0xCF','0xD0'):
 assert baseline['real_cases'][name]['source_B']==15
 assert both['real_cases'][name]['source_B']==native[name][2]
 assert both['real_cases'][name]['source_x86']==native[name][3]
 assert both['real_cases'][name]['mnemonic_wrong']==[]
 assert both['real_cases'][name]['width_wrong']==[]
 assert both['real_cases'][name]['native_external_PE_targets_verified']==native[name][4]
assert len(both['real_cases']['0xCF']['GPR_role_wrong'])==18
assert len(both['real_cases']['0xD0']['GPR_role_wrong'])==35
for name in ('0xD1',):
 # Already present real source. Original PE and physical next case
 # boundary are grounded, and this is never cropped for acceptance.
 assert both['real_cases'][name]['source_B']==native[name][2]
 assert both['real_cases'][name]['source_x86']==native[name][3]
assert rows['F947-real-CF-only']['real_cases']['0xCF']['source_B']==114
assert rows['F947-real-D0-only']['real_cases']['0xD0']['source_B']==195
(O/'verified-summary.json').write_text(json.dumps({
 'original_sha_pinned_Japanese_whole':'0x004AC040','original_entire_CODE_B':whole,
 'native_whole_x86':whole_nx,'original_CFFall_native_B_x86':[114,30],
 'original_D0Reflect_native_B_x86':[195,60],
 'new_CF_D0_native_PE_fields':10,'real_CF_D0_natural_full_Cpp_reconstruction':True,
 'saved_this_EBP_and_GPR_not_exact':True,
 'accepted_new_callable_CODE_B':0,'whole_original_exact':False,
 'mass_cold_replay':False,'whole_partial_father_cases':rows
},indent=2)+'\n')
print('F947 verified 82KB original CF 114B/30-x86 and D0 195B/60-x86 with 4+6 native PE fields; both x86 mnemonic and width geometry exact, but whole parent incomplete and NONEXACT.')
