#!/usr/bin/env python3
"""F564: VC7.1 build of all eleven real action cases 0..10 inside each giant.

Whole-original Japanese TH075 v1.11 CODE and all after-RET DATA are checked
first. Each genuine original case is independently compared for whole
instruction/branch/typed-COFF geometry in one newly compiled C++ switch TU.
Remaining other cases are diagnostic markers; source is NOT complete exact
whole-boss C++ and inner cases are NOT standalone original functions.
Build only selected new TUs, NEVER a full cold replay.
"""
from pathlib import Path
import importlib.util,sys,json,re,subprocess,os,argparse
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

def load(t,p):
 spec=importlib.util.spec_from_file_location(t,p);m=importlib.util.module_from_spec(spec);sys.modules[t]=m;spec.loader.exec_module(m);return m
m=load('r564','scripts/compare-coff-function.py')
a=load('a564','scripts/report-fighter-action-handlers.py')
core=load('core564','scripts/verify-fighter-action-six-natural-source.py')
opening=load('open564','scripts/verify-fighter-opening-actions-natural-source.py')
switch=load('sw564','scripts/verify-fighter-natural-switch-probes.py')
zero=load('z564','scripts/verify-fighter-actionzero-natural-source.py')
one=load('one564','scripts/verify-fighter-actionone-natural-source.py')
f563=load('f563','scripts/verify-fighter-conditional-override-actions.py')
f547=load('f547','scripts/verify-fighter-actionnine-natural-source.py')
f549=load('f549','scripts/verify-fighter-actionten-natural-source.py')
f540=load('f540','scripts/verify-fighter-actionzero-natural-source.py')
extra=load('extra','scripts/verify-fighter-extra-stage-action-source.py')
t=m.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--boss',help='Only a selected original 0x004F7130 / 0x005AEEC0 (default both)')
options=parser.parse_args()
all_bosses=(0x4F7130,0x5AEEC0)
selected=[int(options.boss,0)] if options.boss else list(all_bosses)
assert all(x in all_bosses for x in selected), 'not one of the two SHA-verified native giants'
rows=[]
for address in selected:
 tag=f'Boss{address:08X}'
 boss=next(b for b in json.load(open('config/fighter-boss-dispatch-fingerprints.json'))['bosses'] if b['address']==address)
 summary,mapped=a.report_boss(m,t,dec,boss)
 original56,params=f563.native_three(m,t,dec,boss,core)
 base=f563.source_for(tag,params,summary,mapped,boss,m,t,dec,core,opening,switch,zero,one)
 original9=f547.native_case(m,t,dec,boss)
 native10,low,high,prepare=f549.native_ten(m,t,dec,boss,summary)
 later,ncases,aux=f549.source_ten(f547,tag,summary,mapped,original9,m,t,dec,boss,opening,switch,zero,one,low,high,prepare)
 begin9=later.index('case 0x9:');begin10=later.index('case 0xA:');begin32=later.index('case 0x32:')
 nine=later[begin9:begin10].rstrip();ten=later[begin10:begin32].rstrip()
 marker9='case 0x9: g_FighterProbeMarker = 10; break;'
 marker10='case 0xA: g_FighterProbeMarker = 11; break;'
 assert base.count(marker9)==base.count(marker10)==1
 base=base.replace(marker9,nine).replace(marker10,ten)
 olddecl='void ResetAt453E20();'
 assert base.count(olddecl)==1
 base=base.replace(olddecl,olddecl+' void PrepareActionAt453D60(int);')
 macro='#define I16(off)'
 assert base.count(macro)==1
 base=base.replace(macro,'#define I32(off) *reinterpret_cast<int*>(RAW+(off))\n'+macro)
 oldowner=f'FighterSwitchF563_{tag}'
 assert base.count(oldowner)>=2
 base=base.replace(oldowner,f'FighterSwitchF564_{tag}')
 assert all(base.count(f'case 0x{i:X}:')==1 for i in range(11))
 src=Path(f'.analysis/f564-integrated-opening-switch/{tag}-all11.cpp');src.write_text(base)
 obj=Path(f'build/probes/F564-{tag}.obj')
 env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
 env['WINEPREFIX']=str(Path('.analysis/vc71-wine').resolve())
 env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 p=subprocess.run(['scripts/compile-probe.sh',str(src),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],env=env,capture_output=True,text=True,timeout=120)
 Path(f'.analysis/f564-integrated-opening-switch/{tag}-compile.log').write_text(p.stdout+p.stderr)
 assert p.returncode==0,(tag,p.stdout,p.stderr)
 code,relocs=m.object_function(obj,f'?Advance@FighterSwitchF564_{tag}@@QAEXXZ')
 inst=[]
 for x in dec.disasm(code,0):
  inst.append(x)
  if x.mnemonic=='ret':break
 ret=inst[-1].address+inst[-1].size
 assert len(code)-ret==boss['postret_size'],(tag,'DATA length',len(code)-ret,boss['postret_size'])
 heads=sorted((r for r in relocs if ret<=r['offset']<ret+44),key=lambda r:r['offset'])
 assert len(heads)==11
 candheads=[r['local_symbol_offset'] for r in heads]
 originalheads=[int.from_bytes(m.pe_bytes_at(t,boss['tables'][0]['dense_addr']+4*i,4),'little') for i in range(11)]
 action10target=next(x['handler'] for x in summary['singleton_branches'] if x['action']==0x32)
 end10=int(action10target,16)
 originalheads.append(end10)
 # A direct singleton action 0x32 jump target is seen earlier in normal
 # compiler dispatch. The same real singleton gives candidate action10 end.
 js=[int(inst[i+1].op_str,16) for i in range(len(inst)-1)
     if inst[i].mnemonic=='cmp' and inst[i].op_str.endswith(', 0x32')
     and inst[i+1].mnemonic=='je' and inst[i+1].op_str.startswith('0x')]
 assert len(js)==1,('singleton',tag,js)
 candheads.append(js[0]);assert candheads==sorted(set(candheads))
 source_instrs=0
 source_bytes=0
 physical_count=0
 original_counts=[]
 original_sizes=[]
 for action in range(11):
  a0,a1=originalheads[action:action+2]
  assert boss['address']<=a0<a1<boss['address']+boss['size'], ('native original case invalid',address,action)
  native=list(dec.disasm(m.pe_bytes_at(t,a0,a1-a0),a0))
  c0,c1=candheads[action:action+2]
  cand=list(dec.disasm(code[c0:c1],c0))
  assert native and cand and len(native)==len(cand), (tag,action,'real instructions differ')
  assert sum(x.size for x in native)==sum(x.size for x in cand)==a1-a0==c1-c0, (tag,action,'whole case byte length differs')
  assert all(x.size==y.size for x,y in zip(native,cand)), (tag,action,'native x86 instruction-length mismatch')
  # Physically real EAX/ECX/EDX, x87 and native relative branch positions,
  # allowing only the different containing function's EBP/absolute addresses.
  core.compare_grammar(native,cand)
  physical=[r for r in relocs if c0<=r['offset']<c1]
  if action in (0,2):
   assert f540.reference_sequence(native)==f540.reference_sequence(cand,relocs)
  elif action in (1,3):
   assert one.inspect_field_grammar(native)==one.inspect_field_grammar(cand,relocs)
  elif action in (4,5):
   assert len(native)==3 and len(physical)==0
   assert native[1].mnemonic==cand[1].mnemonic=='mov'
   assert native[1].op_str==cand[1].op_str
  elif action in (6,7,8):
   assert f563.verify_typed_fields(native,cand,relocs,action,core,extra)==(8 if action<8 else 6)
  elif action==9:
   assert f547.typed_references(native)==f547.typed_references(cand,relocs)
  elif action==10:
   assert f549.physical_calls(native,cand,relocs)==5
  expected_fields=(9,11,9,11,0,0,8,8,6,6,5)[action]
  assert len(physical)==expected_fields, (tag,action,'real COFF field count',len(physical))
  physical_count+=len(physical)
  source_instrs+=len(native)
  source_bytes+=a1-a0
  original_counts.append(len(native))
  original_sizes.append(a1-a0)
  print('  original whole case',action,'complete native',len(native),'instructions /',a1-a0,
        'CODE bytes, actual typed COFF fields',len(physical),'PASS',flush=True)
  Path(f'.analysis/f564-integrated-opening-switch/{tag}-case{action}-alignment.txt').write_text(
   ''.join(f'{i:03d} N {x.address:08X} {x.mnemonic:<8} {x.op_str:<44} | C {y.address:06X} {y.mnemonic:<8} {y.op_str}\n'
           for i,(x,y) in enumerate(zip(native,cand))))
 assert physical_count==73, (tag,'all eleven original source COFF cases need 73 real fields',physical_count)
 count,sparse,maps=zero.verify_physical_tables(boss,summary,t,m,switch,inst,code,relocs,ret)
 row={'boss':f'0x{address:08X}','entire_original_CODE_unaccepted':boss['size'],
      'original_action_cases':list(range(11)),
      'original_case_instructions':original_counts,
      'original_case_CODE_bytes':original_sizes,
      'real_case_COFF_relocations':physical_count,
      'physical_original_switch_DWORD_fields':count,
      'literal_native_sparse_index_bytes':sparse,
      'original_afterret_DATA_shape':len(code)-ret,
      'candidate_partial_CXX_CODE_bytes':ret}
 rows.append(row)
 print(f'INTEGRATED {address:#010x}: {source_instrs} original native instructions, '
       f'{source_bytes} complete inner CODE bytes, {physical_count}/73 authentic '
       f'case COFF refs, {count} whole native switch DWORD fields, '
       f'{sparse} exact sparse bytes, original whole {boss["size"]} CODE still NONEXACT',flush=True)
out=Path('.analysis/f564-integrated-opening-switch')
out.mkdir(parents=True,exist_ok=True)
label='summary.json' if not options.boss else f'summary-{selected[0]:08X}.json'
(out/label).write_text(json.dumps(rows,indent=2)+'\n')
print(f'{len(rows)}/{len(selected)} new integrated natural C++ source TUs passed; '
      'no completed giant or split-function CODE/DATA credit, no all-unit replay.')
