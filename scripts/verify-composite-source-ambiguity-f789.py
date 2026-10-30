"""Prove exact explicit AND implicit 116B composite copy-source ambiguity.

Two full pinned VC7.1 explicit C++ methods independently emit the
same physical original CODE as implicit F788. Therefore original
historical explicit/implicit authorship CANNOT be decided from bytes.
No formal authored credit or unknown-origin reclassification.
"""
from pathlib import Path
import importlib.util,subprocess,os,sys,json,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f789-composite-origin-equivalence';O.mkdir(exist_ok=True)
base=Path('probes/CompositeImplicitAssignmentF787.cpp').read_text()
needle='''    NestedSequenceF787 first, second;
};'''
assert base.count(needle)==1
fieldlist=['header','short10','dword14',*[f'short{x}' for x in ('18','1a','1c','1e','20','22','24','26','28','2a')],'dword2c','dword30','short34','short36','byte38','dword3c','dword40','tail44','first','second']
assign_stmt='\n'.join('    '+field+'=src.'+field+';' for field in fieldlist)
source_assign=base.replace(needle,'''    NestedSequenceF787 first, second;
    CompositeValueF787& operator=(const CompositeValueF787&);
};''')
source_assign=source_assign.replace('void ProbeCompositeCopyF787(', '''CompositeValueF787& CompositeValueF787::operator=(const CompositeValueF787& src) {
'''+assign_stmt+'''
    return *this;
}
void ProbeCompositeCopyF787(''')
initializer=',\n    '.join(field+'(src.'+field+')' for field in fieldlist)
source_ctor=base.replace(needle,'''    NestedSequenceF787 first, second;
    CompositeValueF787(const CompositeValueF787&);
};''')
source_ctor=source_ctor.replace('void ProbeCompositeCopyF787(','''CompositeValueF787::CompositeValueF787(const CompositeValueF787& src)
    : '''+initializer+''' {}
void ProbeCompositeCopyF787(''')
# Source experiments both force compilation through regular wrapper.
cases=[('explicit-assignment',source_assign,'??4CompositeValueF787@@QAEAAU0@ABU0@@Z',368,0x45aae0),
       ('explicit-constructor',source_ctor,'??0CompositeValueF787@@QAE@ABU0@@Z',417,0x4591e0)]
sp=importlib.util.spec_from_file_location('rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine');env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
f788spec=importlib.util.spec_from_file_location('f789_f788',R/'scripts/verify-composite-implicit-constructor-f788.py')
f788=importlib.util.module_from_spec(f788spec);sys.modules[f788spec.name]=f788;f788spec.loader.exec_module(f788)
d=Cs(CS_ARCH_X86,CS_MODE_32)
def confirm_whole_compiler_section(path,sym,size):
 data=path.read_bytes()
 machine,nsections,_,symbol_offset,count,optional,_=struct.unpack_from('<HHIIIHH',data,0)
 if machine!=0x14c or optional:raise ValueError('non-VC7 original COFF object')
 strings_at=symbol_offset+count*18
 stringsz=struct.unpack_from('<I',data,strings_at)[0]
 strings=data[strings_at:strings_at+stringsz]
 i=0; found=[]
 while i<count:
  pos=symbol_offset+i*18
  name,val,section,kind,storage,auxcount=struct.unpack_from('<8sIhHBB',data,pos)
  if rd.coff_name(name,strings)==sym and section>0:
   found.append((val,section,kind,auxcount,pos))
  i+=1+auxcount
 if len(found)!=1:raise ValueError('nonunique full explicit native method symbol')
 val,section,kind,auxcount,pos=found[0]
 sectionbytes=struct.unpack_from('<I',data,20+(section-1)*40+16)[0]
 if sectionbytes!=size or val!=0 or kind!=0x20:
  raise ValueError('explicit source COFF has a cropped function extent')
 if auxcount and struct.unpack_from('<I',data,pos+18+4)[0]!=size:
  raise ValueError('explicit function COFF length aux disagrees')

rows=[]
for tag,src,sym,orig_size,addr in cases:
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi'],cwd=R,env=env,capture_output=True,text=True,timeout=240)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:print(tag,'compile fail',cp.stderr[-600:],flush=True);continue
 confirm_whole_compiler_section(obj,sym,orig_size)
 try:
  code,refs=rd.object_function(obj,sym,orig_size)
 except Exception as ex:
  print(tag,'read/comparison failure',str(ex)[:400],flush=True);continue
 orig=rd.pe_bytes_at(rd.verified_target(),addr,orig_size)
 map_name='ctor' if tag=='explicit-constructor' else 'assignment'
 expected=f788.SYMS[map_name][4]
 if {r['offset'] for r in refs}!=set(expected):
  raise ValueError('wrong original physical typed relocation positions '+tag)
 mask=set()
 for r in refs:
  off=r['offset'];kind,target=expected[off]
  origfield=rd.pe_bytes_at(rd.verified_target(),addr,orig_size)[off:off+4]
  dest=(int.from_bytes(origfield,'little') if kind=='DIR32' else
   addr+off+4+int.from_bytes(origfield,'little',signed=True))
  if r['type']!=kind or r['addend']!=0 or r['local_symbol_offset'] is not None or dest!=target:
   raise ValueError('original PE native field mismatch '+tag+' '+str(r))
  mask.update(range(off,off+4))
 n=list(d.disasm(orig,addr));ss=list(d.disasm(code,0))
 row={'tag':tag,'source_COFF_len':len(code),'original_len':orig_size,
      'source_x86':len(ss),'native_x86':len(n),
      'nonfield_equal':sum(code[i]==orig[i] for i in range(orig_size) if i not in mask),
      'nonfield_total':orig_size-len(mask),'physical_reloc':len(refs)}
 if row['source_x86']!=row['native_x86'] or (
   row['nonfield_equal']!=row['nonfield_total']):
  raise ValueError('explicit whole source not native byte exact '+tag)
 rows.append(row);print(json.dumps(row),flush=True)
if len(rows)!=2:
 raise ValueError('not both original explicit copy methods reproduced')
(O/'verified-summary.json').write_text(json.dumps({
 'user_supplied_original_Japanese_PE_hash_checked':True,
 'physical_full_explicit_source_matches':rows,
 'implicit_source_comparisons':'F787/F788 separately verified exact',
 'historical_authoring_provenance':'unknown; distinct explicit and implicit C++ source policies emit same complete PE CODE',
 'authored_exact_ledger_delta':0,'entire_accepted_unit_cold_replay_run':False,
},indent=2)+'\n')
print('F789: BOTH explicit C++ 417B constructor and 368B assignment reproduce complete native bytes and all actual PE refs; equivalent implicit F788 code disproves uniqueness of historical provenance. ZERO official authored credit.')
