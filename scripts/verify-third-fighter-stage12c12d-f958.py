#!/usr/bin/env python3
"""F958 original 82KB giant, native 12C+12D with no fabricated 12C DIR32.

Compile two complete original-shaped normal VC7.1 partial giant fathers
from newly TRACKED master: old 12C/12D markers versus their genuine
source. Independently read SHA-pinned original 82KB PE native 12C:
207B/59x86 and 12D:219B/61x86; both with six actual PE external
targets. Original 12C has NO afterRET jump label; derive its physical
source boundary from prior native D2 ending exactly where 12C starts
and next genuine 12D afterRET label. Never invent a label or claim
inner-case/full partial father byte exact.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f958-third-source-proof';O.mkdir(parents=True,exist_ok=True)
master=(R/'probes/FighterWhole004AC040F958.cpp').read_text()
pair=(R/'probes/FighterThirdBossStage12C12DF958.inc').read_text()
mark='#include "FighterThirdBossStage12C12DF958.inc"'
assert master.count(mark)==1 and pair.count('case 0x12C:')==pair.count('case 0x12D:')==1
prior=(master.replace(mark,
    'case 0x12C: g_FighterProbeMarker = 301; break;\n'
    'case 0x12D: g_FighterProbeMarker = 302; break;',1))
versions={'F955-original-stubs':prior,'F958-both-real':master}
sp=importlib.util.spec_from_file_location('f958reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;ORIG=82796;ORIG_X86=22721;POSTRET=1126
N=list(D.disasm(rd.pe_bytes_at(PE,BASE,ORIG),BASE))
assert len(N)==ORIG_X86 and N[-1].address+N[-1].size==BASE+ORIG
original_after=rd.pe_bytes_at(PE,BASE+ORIG,POSTRET)
facts={
 'D2':(0x4B0F3E,0x4B1039,251,74,None),
 '12C':(0x4B1039,0x4B1108,207,59,6),
 '12D':(0x4B1108,0x4B11E3,219,61,6),
}
native={}
for name,(a,b,nb,nx,nr) in facts.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,nb),a))
 assert len(n)==nx and b-a==nb and n[-1].address+n[-1].size==b
 native[name]=n
# Original physical afterRET DATA has NO 12C label; do not manufacture one.
assert all(int.from_bytes(original_after[i:i+4],'little')!=0x4B1039
           for i in range(POSTRET-3))
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(rx.findall(ins.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winewayland.drv=d;winemenubuilder.exe=d'
results={}
for name,source in versions.items():
 cpp=O/(name+'.cpp');obj=O/(name+'.obj');cpp.write_text(source)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
   cwd=R,env=env,capture_output=True,text=True,timeout=330)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1000:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==POSTRET
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  orig_va=int.from_bytes(original_after[off:off+4],'little')
  assert BASE<=orig_va<BASE+ORIG
  labels.setdefault(orig_va,r['local_symbol_offset'])
 assert POSTRET-len(mask)==522
 assert all(code[end+i]==original_after[i] for i in range(POSTRET) if i not in mask)
 assert 0x4B1039 not in labels
 assert 0x4B0F3E in labels and 0x4B1108 in labels and 0x4B11E3 in labels
 d2start=labels[0x4B0F3E]
 d2n=facts['D2'][3]
 startidx=next(i for i,x in enumerate(I) if x.address==d2start)
 emittedD2=I[startidx:startidx+d2n]
 d2end=emittedD2[-1].address+emittedD2[-1].size
 assert len(emittedD2)==74 and d2end-d2start==251
 assert [n.mnemonic for n in emittedD2]==[n.mnemonic for n in native['D2']]
 assert [n.size for n in emittedD2]==[n.size for n in native['D2']]
 first12c=d2end
 next12d=labels[0x4B1108];next12e=labels[0x4B11E3]
 assert d2start<first12c<next12d<next12e
 row={'whole_original_CODE_B':ORIG,'whole_original_x86':ORIG_X86,
      'partial_compiled_source_CODE_B':end,'partial_source_x86':len(I),
      'real_original_D2_to_12C_contiguous':True,
      'real_12C_has_no_independent_afterRET_label':True,
      'afterRET_native_DIR32':151,'afterRET_original_nonfield_equal_B':522,
      'source_COFF_fields_total':len(refs),
      'real_states':{},'whole_original_exact':False}
 for label,lo,hi in [('12C',first12c,next12d),('12D',next12d,next12e)]:
  a,b,sz,nx,nrefs=facts[label]
  source_ins=[x for x in I if lo<=x.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  entry={'native_original_CODE_B':sz,'native_original_x86':nx,
         'source_CODE_B':hi-lo,'source_x86':len(source_ins),
         'original_PE_external_targets_verified':0}
  if hi-lo==sz and len(source_ins)==nx:
   m=[i for i,(x,y) in enumerate(zip(native[label],source_ins)) if x.mnemonic!=y.mnemonic]
   w=[i for i,(x,y) in enumerate(zip(native[label],source_ins)) if x.size!=y.size]
   g=[i for i,(x,y) in enumerate(zip(native[label],source_ins)) if roles(x)!=roles(y)]
   entry.update({'wrong_native_mnemonics':m,'wrong_native_widths':w,'wrong_native_GPR_roles':g})
   if not m and not w:
    assert len(fields)==nrefs
    pebytes=rd.pe_bytes_at(PE,a,sz)
    for r in fields:
     j=next(j for j,x in enumerate(source_ins) if x.address<=r['offset']<x.address+x.size)
     dt=r['offset']-source_ins[j].address
     originalfield=native[label][j].address-a+dt
     assert originalfield==r['offset']-lo
     assert r['type'] in ('DIR32','REL32') and r['addend']==0 and r['local_symbol_offset'] is None
     v=int.from_bytes(pebytes[originalfield:originalfield+4],'little',signed=r['type']=='REL32')
     addr=native[label][j].address+dt+4+v if r['type']=='REL32' else v
     mm=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(mm.group(1),16) if mm else 0x6406AC if r['symbol']=='__ftol2' else None
     assert addr==expected,(label,j,hex(addr),expected,r['symbol'])
    entry['original_PE_external_targets_verified']=len(fields)
  row['real_states'][label]=entry
 results[name]=row
 print(name,'whole C++',end,'x86',len(I),
   '12C source B/x86',row['real_states']['12C']['source_CODE_B'],row['real_states']['12C']['source_x86'],
   '12D source B/x86',row['real_states']['12D']['source_CODE_B'],row['real_states']['12D']['source_x86'],flush=True)
old=results['F955-original-stubs'];new=results['F958-both-real']
assert (old['partial_compiled_source_CODE_B'],old['partial_source_x86'])==(21616,5859)
assert (new['partial_compiled_source_CODE_B'],new['partial_source_x86'])==(22012,5975)
for label in ('12C','12D'):
 e=new['real_states'][label]
 assert (e['source_CODE_B'],e['source_x86'])==(facts[label][2],facts[label][3])
 assert e['wrong_native_mnemonics']==e['wrong_native_widths']==e['wrong_native_GPR_roles']==[]
 assert e['original_PE_external_targets_verified']==6
 assert old['real_states'][label]['source_CODE_B']==15
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x004AC040',
 'original_entire_callable_CODE_B':ORIG,'original_whole_x86':ORIG_X86,
 'native_12C_no_afterRET_table_entry':True,
 'original_12C_B_x86':[207,59],'original_12D_B_x86':[219,61],
 'native_original_12C_and_12D_PE_targets_verified':12,
 'both_original_12C_12D_GPR_mnemonic_width_roles_exact':True,
 'source_generated_from_tracked_selected_whole_parent':True,
 'whole_original_exact':False,'newly_accepted_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,'compiled_complete_partial_fathers':results
},indent=2)+'\n')
print('F958 complete: 426 original internal CODE B/120 x86 and 12 actual original external PE targets from two native C++ actions in selected whole 22,012-B parent. NO exact giant credit.')
