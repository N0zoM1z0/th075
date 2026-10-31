#!/usr/bin/env python3
"""F1026: original 46KB Boss 005214B0 all 1341 nonlocal PE targets.

Freshly build ONLY the tracked complete original-shaped F901
normal VC7.1 fighter source. Independently map every non-local
source COFF REL32/DIR32 field to original Japanese PE native
x86 ordinal/physical field offset; compare source AtHEX target
to the actual original address, including 30 __ftol2. Also
verify original 139 afterRET DIR32, 345 nonfield DATA,
10 code-local COFF fields, all 13230 mnemonic slots,
5 wrong original widths and full-source CODE B shortfall.
NEVER count internal states or partial giant as exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import bisect,importlib.util,json,os,re,subprocess,sys,collections
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f1026-whole-46kb-original-PE';O.mkdir(parents=True,exist_ok=True)
cpp=R/'.analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp'
assert cpp.is_file(),'first regenerate only the F901 affected whole father using verify-scripted-fighter-tail31b-31c-f901.py'
obj=O/'native-F901-recompiled.obj'
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
 '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
 cwd=R,env=E,capture_output=True,text=True,timeout=350)
(O/'original-whole-VC71-build.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
sp=importlib.util.spec_from_file_location('f1026rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x5214B0;NATIVE=46755;X86=13230;AFTER=901
n=list(D.disasm(rd.pe_bytes_at(PE,BASE,NATIVE),BASE))
assert len(n)==X86 and n[-1].address+n[-1].size==BASE+NATIVE
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
i=[]
for x in D.disasm(code,0):
 i.append(x)
 if x.mnemonic=='ret':break
end=i[-1].address+i[-1].size
assert end==46754 and len(i)==X86 and len(code)-end==AFTER and len(refs)==1491
badm=[j for j,(x,y) in enumerate(zip(n,i)) if x.mnemonic!=y.mnemonic]
badw=[j for j,(x,y) in enumerate(zip(n,i)) if x.size!=y.size]
assert badm==[]
assert badw==[2885,2908,8455,8986,9130]
external=[r for r in refs if r['offset']<end and r['local_symbol_offset'] is None]
localcode=[r for r in refs if r['offset']<end and r['local_symbol_offset'] is not None]
table=[r for r in refs if r['offset']>=end]
assert (len(external),len(localcode),len(table))==(1341,11,139),(len(external),len(localcode),len(table))
starts=[x.address for x in i];types=collections.Counter();targets=[]
for r in external:
 assert r['type'] in ('REL32','DIR32') and r['addend']==0
 j=bisect.bisect_right(starts,r['offset'])-1
 assert 0<=j<X86 and i[j].address<=r['offset']<=i[j].address+i[j].size-4
 d=r['offset']-i[j].address
 assert d+4<=n[j].size
 orig=n[j].address+d
 value=int.from_bytes(rd.pe_bytes_at(PE,orig,4),'little',signed=r['type']=='REL32')
 target=orig+4+value if r['type']=='REL32' else value
 match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
 if match:expected=int(match.group(1),16);t='AtHEX'
 else:
  assert r['symbol']=='__ftol2',r['symbol']
  expected=0x6406AC;t='ftol2'
 assert target==expected,(j,r['symbol'],hex(target),hex(expected))
 types[t]+=1
 targets.append({'native_x86_ordinal':j,'native_original_field_va':f'0x{orig:08X}',
  'real_native_target':f'0x{target:08X}','kind':r['type'],'symbol':r['symbol']})
assert types=={'AtHEX':1311,'ftol2':30}
# The native afterRET payload is not CODE. Original tables are
# independently checked against sparse switch ordinals and real
# physical local target partitioning, not merely source labels.
manifest=json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())
boss=next(b for b in manifest['bosses'] if b['address']==BASE)
assert boss['postret_size']==AFTER and boss['dense_entries']==139 and boss['sparse_bytes']==345
after=rd.pe_bytes_at(PE,BASE+NATIVE,AFTER)
orig_map={}
masked=set()
for r in table:
 q=r['offset']-end
 assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
 assert all(x not in masked for x in range(q,q+4))
 masked.update(range(q,q+4))
 assert BASE<=int.from_bytes(after[q:q+4],'little')<BASE+NATIVE
 orig_map[q]=int.from_bytes(after[q:q+4],'little')
assert AFTER-len(masked)==345 and len(orig_map)==139
assert all(code[end+j]==after[j] for j in range(AFTER) if j not in masked)
# Compare native jump-target equality partitions for each original
# physical jump table, not the source absolute machine positions.
for tab in boss['tables']:
 t=tab['dense_addr'];q=None
 for offset in sorted(orig_map):
  expected=[int.from_bytes(rd.pe_bytes_at(PE,t+4*k,4),'little') for k in range(tab['slots'])]
  # Values in each physical table are contiguous in afterRET slots.
  if [orig_map.get(offset+4*k) for k in range(tab['slots'])]==expected:
   q=offset;break
 assert q is not None,(hex(t),tab['slots'])
 src_labels=[next(r['local_symbol_offset'] for r in table if r['offset']==end+q+4*k)
             for k in range(tab['slots'])]
 assert [expected[k]==expected[m] for k in range(tab['slots']) for m in range(tab['slots'])]==[
  src_labels[k]==src_labels[m] for k in range(tab['slots']) for m in range(tab['slots'])]
 (O/f'original-switch-{t:08X}.json').write_text(json.dumps(
  {'native_original_PE_table':hex(t),'native_case_count':tab['slots'],
   'native_actual_original_DATA_start_offset':q},indent=2)+'\n')
(O/'all-real-native-PE-targets.json').write_text(json.dumps(targets,indent=2)+'\n')
(O/'verified-summary.json').write_text(json.dumps({
 'pinned_original_Japanese_fighter':'0x005214B0',
 'native_whole_CODE_B':NATIVE,'native_whole_x86':X86,
 'source_whole_CODE_B':end,'source_whole_x86':len(i),
 'native_1341_nonlocal_PE_destinations_all_match':True,
 'original_named_PE_targets':1311,'real_ftol2_targets':30,
 'native_code_local_label_fields':len(localcode),
 'native_afterRET_DIR32_fields':len(table),
 'native_afterRET_nonfield_DATA_equal_B':345,
 'original_actual_jump_tables':len(boss['tables']),
 'whole_original_wrong_mnemonics':badm,
 'whole_original_wrong_widths':badw,
 'whole_original_exact':False,'new_accepted_whole_GAME_CODE_B':0,
 'mass_cold_replay':False
},indent=2)+'\n')
print('F1026 original 46KB whole: 1,341/1,341 genuine nonlocal PE targets, 11 local CODE fields, 139 native DIR32, 345 literal DATA B; source 46,754B/13,230 x86, 5 wrong widths, NONEXACT.')
