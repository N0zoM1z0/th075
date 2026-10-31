#!/usr/bin/env python3
"""F972: verify 82KB original 199/19A five-shot and real x87 motion ordering.

Cold compile TWO tracked complete original-shaped normal VC7.1 PARTIAL
004AC040 fighters: F971 markers and new F972 real 199/19A sources.
Compare pinned Japanese original x86/PE 593B/170 each, 19 physical
typed zero-addend PE fields per case, real global float-motion
FLD/[member], FMUL/[global] order, original 151 afterRET DIR32
and 522 nonfield DATA bytes. No whole native GAME exact credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib,json,os,re,sys,subprocess
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f972-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F971-prior-markers':R/'probes/FighterWhole004AC040F971.cpp',
         'F972-real-motion-five-shot':R/'probes/FighterWhole004AC040F972.cpp'}
inc=(R/'probes/FighterThirdBossFiveShot19919AF972.inc').read_text()
assert inc.count('case 0x199:')==inc.count('case 0x19A:')==1
assert inc.count('F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;')==2
sp=importlib.util.spec_from_file_location('readerF972',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
BASE=0x4AC040;CODE_B=82796;NX=22721;DATA=1126
full=list(D.disasm(rd.pe_bytes_at(PE,BASE,CODE_B),BASE))
assert len(full)==NX and full[2].op_str=='esp, 0x720'
after=rd.pe_bytes_at(PE,BASE+CODE_B,DATA)
physical={
 '198':(0x4B31EB,0x4B33E6,507,146,15),
 '199':(0x4B33E6,0x4B3637,593,170,19),
 '19A':(0x4B3637,0x4B3888,593,170,19),
}
natives={}
for k,(a,b,size,nx,nf) in physical.items():
 I=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert len(I)==nx and b-a==size and I[-1].address+I[-1].size==b
 natives[k]=I
expect={
 '199':{'angle':0,'mult':[76,81,86,91,96],
        'y':[0x65836c,0x659474,0x657860,0x659284,0x659470]},
 '19A':{'angle':0xc1a00000,'mult':[98,92,86,80,74],
        'y':[0x659470,0x658364,0x65946c,0x659468,0x659464]},
}
for k,v in expect.items():
 n=natives[k]
 assert n[9].mnemonic=='fld' and n[9].op_str.endswith('+ 0x50]')
 assert n[10].op_str=='dword ptr [0x657f74]'
 assert n[14].mnemonic=='fld' and n[14].op_str.endswith('+ 0x54]')
 assert n[15].mnemonic=='fmul' and n[15].op_str=='dword ptr [0x657f74]'
 assert n[48].op_str.endswith(', 5')
 assert n[58].op_str.endswith(', '+hex(v['angle']) if v['angle'] else ', 0')
 assert [n[j].op_str for j in (67,88,109,130,151)]==[f'dword ptr [0x{x:x}]' for x in v['y']]
 assert [int(n[j].op_str.split(', ')[-1],16) for j in (72,93,114,135,156)]==v['mult']
 assert [n[j].op_str for j in (79,100,121,142,163)]==['0x328']*5
 assert [n[j].op_str for j in (81,102,123,144,165)]==['0x453a70']*5
 assert n[168].op_str=='0x46d000'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda i:tuple(RX.findall(i.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results={}
for key,src in sources.items():
 obj=O/(key+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(src),str(obj),
    '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
    cwd=R,env=env,capture_output=True,text=True,timeout=340)
 (O/(key+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-1100:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for ins in D.disasm(code,0):
  I.append(ins)
  if ins.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 labels={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(i not in mask for i in range(off,off+4))
  mask.update(range(off,off+4))
  target=int.from_bytes(after[off:off+4],'little')
  assert BASE<=target<BASE+CODE_B
  labels.setdefault(target,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+i]==after[i] for i in range(DATA) if i not in mask)
 assert all(a in labels and b in labels for a,b,_,_,_ in physical.values())
 entry={'native_original_full_GAME_CODE_B':CODE_B,'native_original_full_x86':NX,
    'whole_partial_CPP_B':end,'whole_partial_CPP_x86':len(I),
    'source_COFF_relocs':len(refs),
    'native_afterRET_DIR32_count':151,'native_afterRET_nonfield_equal_B':522,
    'states':{},'whole_original_game_exact':False}
 for name,(a,b,size,nx,nfields) in physical.items():
  lo,hi=labels[a],labels[b]
  source_ins=[i for i in I if lo<=i.address<hi]
  fields=[r for r in refs if lo<=r['offset']<hi]
  status={'native_original_CODE_B':size,'native_original_x86':nx,
          'source_CODE_B':hi-lo,'source_x86':len(source_ins)}
  if len(source_ins)==nx:
   mm=[j for j,(n,s) in enumerate(zip(natives[name],source_ins)) if n.mnemonic!=s.mnemonic]
   ww=[j for j,(n,s) in enumerate(zip(natives[name],source_ins)) if n.size!=s.size]
   gg=[j for j,(n,s) in enumerate(zip(natives[name],source_ins)) if roles(n)!=roles(s)]
   status.update({'native_wrong_mnem_ordinals':mm,'native_wrong_width_ordinals':ww,
                  'native_wrong_GPR_ordinals':gg})
   if not mm and not ww:
    assert len(fields)==nfields,(key,name,len(fields),nfields)
    raw=rd.pe_bytes_at(PE,a,size)
    for ref in fields:
     j=next(j for j,i in enumerate(source_ins) if i.address<=ref['offset']<i.address+i.size)
     d=ref['offset']-source_ins[j].address
     original_offset=natives[name][j].address-a+d
     assert original_offset==ref['offset']-lo,(key,name,j,original_offset,ref['offset']-lo)
     assert ref['type'] in ('REL32','DIR32') and ref['addend']==0 and ref['local_symbol_offset'] is None
     val=int.from_bytes(raw[original_offset:original_offset+4],
                        'little',signed=ref['type']=='REL32')
     orig_va=natives[name][j].address+d+4+val if ref['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',ref['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if ref['symbol']=='__ftol2' else None
     assert orig_va==expected,(key,name,j,ref['symbol'],hex(orig_va),expected)
    status['native_original_PE_targets_checked']=len(fields)
  entry['states'][name]=status
 results[key]=entry
 print(key,'whole partial',end,len(I),'199/19A source',
   [(name,entry['states'][name]['source_CODE_B'],entry['states'][name]['source_x86'])
    for name in ('199','19A')],flush=True)
old=results['F971-prior-markers'];new=results['F972-real-motion-five-shot']
assert (old['whole_partial_CPP_B'],old['whole_partial_CPP_x86'])==(30344,8342)
assert (new['whole_partial_CPP_B'],new['whole_partial_CPP_x86'])==(31500,8678)
for name in ('199','19A'):
 assert old['states'][name]['source_CODE_B']==15
 n=new['states'][name]
 assert (n['source_CODE_B'],n['source_x86'])==(593,170)
 assert n['native_wrong_mnem_ordinals']==n['native_wrong_width_ordinals']==[]
 assert len(n['native_wrong_GPR_ordinals'])==91
 assert n['native_original_PE_targets_checked']==19
assert new['states']['198']['native_original_PE_targets_checked']==15
(O/'verified-summary.json').write_text(json.dumps({
 'original_pinned_Japanese_fighter':'0x004AC040',
 'original_whole_callable_CODE_B':CODE_B,'original_whole_x86':NX,
 'native_real_199_19A_B_x86':[593*2,170*2],
 'native_two_cases_original_PE_targets':38,
 'natural_source_real_x87_member_then_global_FMUL':True,
 'original_all_mnemonics_and_widths_match':True,
 'native_wrong_GPR_roles_per_case':[91,91],
 'original_whole_game_exact':False,'new_accepted_whole_GAME_CODE_B':0,
 'mass_cold_replay':False,
 'complete_original_shaped_partial_fathers':results
},indent=2)+'\n')
print('F972 original 199/19A 1186B/340x86, 38 actual PE target fields, native FLD member/FMUL global source recovered with 0 mnemonic/width errors but 91 GPR roles wrong each. Whole giant NONEXACT.')
