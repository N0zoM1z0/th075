#!/usr/bin/env python3
"""F569: complete native-guard and one-sparse-switch C++ source across 11 giants.

Every entire original Japanese TH075 v1.11 fighter CODE SHA256 and its real
single jump table are verified first. Freshly compile only selected natural
VC7.1 diagnostic C++ TUs, reproducing original receiver/parent guard logic
and native cooldown plus the physical sparse single-switch topology.
All cases are intentionally marker stores, NOT reconstructed game-action
bodies. Never claim exact original huge CODE or run all-unit cold replay.
"""
import importlib.util,json,sys,re,collections,os,subprocess,argparse,hashlib
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
def load(tag,p):
 s=importlib.util.spec_from_file_location(tag,p);m=importlib.util.module_from_spec(s);sys.modules[tag]=m;s.loader.exec_module(m);return m
m=load('r569check','scripts/compare-coff-function.py')
act=load('a569check','scripts/report-fighter-action-handlers.py')
sw=load('sw569check','scripts/verify-fighter-natural-switch-probes.py')
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f569-characterobject-original-source'
OUT.mkdir(parents=True,exist_ok=True)
pe=m.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--boss',help='One whole original CharacterObject PE address, default all eleven')
args=parser.parse_args()
manifest=[b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if b['jump_count']==1]
assert len(manifest)==11 and sum(b['size'] for b in manifest)==488664
if args.boss:
 address=int(args.boss,0)
 manifest=[b for b in manifest if b['address']==address]
 assert len(manifest)==1,'not one of eleven registered original single-switch giants'

FRAME=re.compile(r'\[ebp - (0x[0-9a-f]+|\d+)\]')
result=[]
for boss in manifest:
 address=boss['address'];tag=f'Boss{address:08X}'
 report,mapped=act.report_boss(m,pe,d,boss)
 native=list(d.disasm(m.pe_bytes_at(pe,address,boss['size']),address))
 generated,case_count=sw.generate_probe(tag,mapped,report['default'])
 old='''    if (I16(0x82) != 0 || *reinterpret_cast<signed short*>(OWNER+0x3BA) != 0)
        return;
    switch (I16(0x60)) {'''
 new='''    if (*reinterpret_cast<signed short*>(
            *reinterpret_cast<char**>(
                *reinterpret_cast<char**>(RAW+0xE4)+0x2E8)+0x3BA) != 0)
        return;
    if (*reinterpret_cast<signed short*>(
            *reinterpret_cast<char**>(RAW+0xE4)+0x3BA) != 0 &&
            I16(0x8A) == 0)
        return;
    if (I16(0x82) != 0) {
        --I16(0x82);
        return;
    }
    switch (I16(0x60)) {'''
 assert generated.count(old)==1,'actual source guard does not match native pointer chain'
 generated=generated.replace(old,new).replace('FighterSwitchF539_','FighterSwitchF569_')
 cpp=OUT/f'{tag}-guard-switch.cpp';obj=OUT/f'{tag}-guard-switch.obj'
 cpp.write_text(generated)
 env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
 env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
 env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
      cwd=ROOT,env=env,text=True,capture_output=True,timeout=120)
 (OUT/f'{tag}-compile.log').write_text(proc.stdout+proc.stderr)
 assert proc.returncode==0,(tag,'original-profile VC7.1 source compile failed',proc.stderr)
 source,relocs=m.object_function(obj,f'?Advance@FighterSwitchF569_{tag}@@QAEXXZ')
 candidate=[]
 for x in d.disasm(source,0):
  candidate.append(x)
  if x.mnemonic=='ret':break
 ret=candidate[-1].address+candidate[-1].size
 # Actual two owner/controller guards are the 17 consecutive instructions
 # beginning with the first this-slot reload before parent+E4.
 s=next(i for i in range(3,12) if native[i].mnemonic=='mov' and i+1<len(native)
        and '+ 0xe4]' in native[i+1].op_str)
 t=next(i for i in range(3,10) if candidate[i].mnemonic=='mov'
        and '+ 0xe4]' in candidate[i+1].op_str)
 g0=native[s:s+17];g1=candidate[t:t+17]
 assert len(g0)==len(g1)==17
 def norm_ins(seq):
  addresses={x.address:k for k,x in enumerate(seq)}
  result=[]
  for x in seq:
   op=FRAME.sub('[SAVED_OWNER]',x.op_str)
   if x.mnemonic in ('ja','jg','je','jne','jle','jl','jp','jmp') and op.startswith('0x'):
    dest=int(op,16)
    op='TO_'+str(addresses[dest]) if dest in addresses else 'EXIT_OR_NEXT'
   result.append((x.mnemonic,op))
  return result
 prefix_match=norm_ins(g0)==norm_ins(g1)
 assert prefix_match, (tag,'original two-stage parent/owner-state guard differs')
 # Real native signed-short cooldown is the 10-instruction block
 # immediately preceding the 11-instruction original sparse dispatcher.
 native_jump=next(i for i,x in enumerate(native) if x.address==boss['tables'][0]['jmp'])
 cand_jump=next(i for i,x in enumerate(candidate)
                if x.mnemonic=='jmp' and x.op_str.startswith('dword ptr ['))
 orig_cool=native[native_jump-20:native_jump-10]
 cand_cool=candidate[cand_jump-20:cand_jump-10]
 assert len(orig_cool)==len(cand_cool)==10
 cool_gpr_exact=norm_ins(orig_cool)==norm_ins(cand_cool)
 assert cool_gpr_exact or address==0x00536400, (
     tag,'native 10-instruction cooldown register grammar changed unexpectedly')
 def physical_widths(real,compiled):
  assert len(real)==len(compiled)
  wide=0
  for x,y in zip(real,compiled):
   diff=x.size-y.size
   if diff:
    assert diff==3 and x.mnemonic in ('mov','cmp') and (
      '[ebp - 0xac]' in x.op_str or '[ebp - 0xb0]' in x.op_str), (
      tag,'unexplained source/native full-giant stack displacement width',x.op_str,y.op_str)
    wide+=1
  return wide
 prefix_wide=physical_widths(g0,g1)
 cooldown_wide=physical_widths(orig_cool,cand_cool)

 # Native physical jump entry has the same single indirect switch,
 # including direct case-ID lower bound and upper bound.
 native_jmp=next(i for i,x in enumerate(native) if x.address==boss['tables'][0]['jmp'])
 src_jmp=next(i for i,x in enumerate(candidate) if x.mnemonic=='jmp' and
              x.op_str.startswith('dword ptr ['))
 n=native[native_jmp-10:native_jmp+1]
 c=candidate[src_jmp-10:src_jmp+1]
 assert len(n)==len(c)==11
 dispatch_wide=physical_widths(n,c)
 ng=sw.grammar(n,n[0].address,n[-1].address+n[-1].size)
 cg=sw.grammar(c,c[0].address,c[-1].address+c[-1].size)
 strict=ng==cg
 # Free register normalization, but a physical 11-instruction switch
 # loader must preserve all native stack-dataflow roles, not just a
 # mnemonic bag. All individual operand relationships are checked here.
 def dataflow(ins):
  assert [x.mnemonic for x in ins]==['mov','movsx','mov','mov','sub','mov','cmp','ja','mov','movzx','jmp']
  first=ins[0].op_str.split(',',1)[0]
  assert ins[1].op_str.startswith(ins[1].op_str.split(',',1)[0]+', word ptr ['+first+' + 0x60]')
  state=ins[1].op_str.split(',',1)[0]
  stack=ins[2].op_str.split(', ',1)[0]
  assert FRAME.fullmatch(stack) is None # stack contains "dword ptr" prefix
  assert ins[2].op_str.endswith(', '+state)
  tmp=ins[3].op_str.split(',',1)[0]
  assert ins[3].op_str.endswith(', '+stack)
  assert ins[4].op_str==tmp+', 0x320'
  assert ins[5].op_str==stack+', '+tmp
  assert ins[6].op_str.startswith(stack+', ')
  assert ins[7].mnemonic=='ja'
  offset=ins[8].op_str.split(',',1)[0]
  assert ins[8].op_str.endswith(', '+stack)
  ix=ins[9].op_str.split(',',1)[0]
  assert 'byte ptr ['+offset in ins[9].op_str
  assert ins[10].op_str.startswith('dword ptr ['+ix+'*4')
  return int(ins[6].op_str.split(', ',1)[1],0)
 upper_native=dataflow(n)
 upper_candidate=dataflow(c)
 assert upper_native==upper_candidate
 assert strict or address in (0x0050A580,0x00536400),(
     tag,'unexpected new original free-register allocations')
 assert not strict or address not in (0x0050A580,0x00536400),(
     tag,'historical GPR-allocation mismatch apparently changed; re-review real native behavior')
 if address==0x0050A580:
  assert dispatch_wide==6 and prefix_wide>0 and cooldown_wide==3, (
      tag,'native EBP-0xAC/-0xB0 wide receiver stack widths changed')
 else:
  assert prefix_wide==cooldown_wide==dispatch_wide==0, (
      tag,'unexpected real original wide-stack form')

 # Complete native original switch DATA (not CODE)
 table=boss['tables'][0];data_start=ret;nslots=table['slots']
 fields=sorted((r for r in relocs if data_start<=r['offset']<data_start+4*nslots),key=lambda r:r['offset'])
 assert len(fields)==nslots and all(r['type']=='DIR32' and r['offset']==data_start+4*k and
                                    r['local_symbol_offset'] is not None and r['addend']==0
                                    for k,r in enumerate(fields))
 original_dense=[int.from_bytes(m.pe_bytes_at(pe,table['dense_addr']+4*k,4),'little') for k in range(nslots)]
 cand_dense=[r['local_symbol_offset'] for r in fields]
 assert sw.canonical_partitions(original_dense)==sw.canonical_partitions(cand_dense)
 native_default=int(report['default'],16)
 # One JA fallthrough points to original real shared default, candidate
 # source default. Compare which DWORD slots target that function.
 cdefault=int(c[7].op_str,16)
 assert [x==native_default for x in original_dense]==[x==cdefault for x in cand_dense]
 native_map=m.pe_bytes_at(pe,table['map_addr'],table['map_length'])
 candidate_map=source[data_start+4*nslots:data_start+4*nslots+table['map_length']]
 assert native_map==candidate_map and len(source)-ret==boss['postret_size']
 assert hashlib.sha256(native_map).hexdigest()==table['map_sha']
 assert hashlib.sha256(m.pe_bytes_at(pe,table['dense_addr'],4*nslots)).hexdigest()==table['dense_sha']

 assert data_start+4*nslots+table['map_length']==len(source)
 row={'boss':f'0x{address:08X}','whole_native_CODE':boss['size'],'native_dispatch_insns':11,
      'native_guard_insns':17,'original_guard_grammar_match':prefix_match,
      'original_signed_cooldown_insns':10,
      'native_cooldown_register_exact':cool_gpr_exact,
      'native_wide_stack_loads_prefix':prefix_wide,
      'native_wide_stack_loads_cooldown':cooldown_wide,
      'native_wide_stack_loads_dispatch':dispatch_wide,
      'native_dispatch_register_exact':strict,'physical_dense_COFF':nslots,
      'byte_identical_sparse_index':len(native_map),'full_afterret_DATA':boss['postret_size'],
      'natural_source_cases':case_count,
      'normal_switch_upper':upper_native}
 result.append(row)
 print(f'{address:08X} original {boss["size"]} CODE, guard {prefix_match} native GPR dispatch {strict} '
       f'upper {upper_native:#x} whole {nslots} dense COFF, {len(native_map)} literal index bytes '
       f'{boss["postret_size"]} postret DATA',flush=True)
assert len(result)==len(manifest)
if not args.boss:
 assert sum(x['whole_native_CODE'] for x in result)==488664
 assert sum(x['physical_dense_COFF'] for x in result)==752
 assert sum(x['byte_identical_sparse_index'] for x in result)==2185
 assert sum(x['full_afterret_DATA'] for x in result)==5193
 assert sum(x['native_dispatch_register_exact'] for x in result)==9
 assert sum(x['native_cooldown_register_exact'] for x in result)==10
name='summary.json' if not args.boss else f'summary-{manifest[0]["address"]:08X}.json'
(OUT/name).write_text(json.dumps(result,indent=2)+'\n')
print('SELECTED FINAL',len(result),'guard match',sum(x['original_guard_grammar_match'] for x in result),
      'strict dispatch',sum(x['native_dispatch_register_exact'] for x in result),
      'whole original CODE',sum(x['whole_native_CODE'] for x in result),'COFF',
      sum(x['physical_dense_COFF'] for x in result),'sparse',
      sum(x['byte_identical_sparse_index'] for x in result),'afterret',
      sum(x['full_afterret_DATA'] for x in result))
