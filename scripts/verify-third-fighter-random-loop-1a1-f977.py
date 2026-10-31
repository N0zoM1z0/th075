#!/usr/bin/env python3
"""F977: true original 1A1 random 5/8 loops and native ESI owner lifetime.

Cold compile two tracked ENTIRE normal VC7.1 original-shaped PARTIAL
004AC040 fighter parents (F976 1A1 marker, F977 real source).
Independently read pinned Japanese native PE: original 1A0 570B/148,
1A1 570B/151, 12 true typed PE fields each; 1A1 has genuine ESI
live across 455580 calls and source now saves ESI in parent prologue.
Check 151 original afterRET local DIR32 and 522 nonfield DATA bytes.
Also verify 191 x87 width debt changes 8->4 from parent native-shaped
source stack growth, not from fake locals. No original whole exact credit.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f977-third-original-proof';O.mkdir(parents=True,exist_ok=True)
sources={'F976-prior-1A1-marker':R/'probes/FighterWhole004AC040F976.cpp',
         'F977-real-1A1-ESI':R/'probes/FighterWhole004AC040F977.cpp'}
inc=(R/'probes/FighterThirdBossRandomLoop1A1F977.inc').read_text()
assert inc.count('case 0x1A1:')==1
assert inc.split('case 0x1A1:')[1].count('RandAt455580(0,20)')==2
assert inc.count('for (int shot=0;shot<5;++shot)')==1
assert inc.count('for (int shot=0;shot<8;++shot)')==1
sp=importlib.util.spec_from_file_location('f977reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32);PE=rd.verified_target()
BASE=0x4AC040;WHOLE=82796;WHOLEX=22721;DATA=1126
original_whole=list(D.disasm(rd.pe_bytes_at(PE,BASE,WHOLE),BASE))
assert len(original_whole)==WHOLEX and original_whole[2].op_str=='esp, 0x720'
assert any(x.mnemonic=='push' and x.op_str=='esi' for x in original_whole[:8])
after=rd.pe_bytes_at(PE,BASE+WHOLE,DATA)
cases={'191':(0x4B23BC,0x4B2611,597,147,11),
       '1A0':(0x4B4097,0x4B42D1,570,148,12),
       '1A1':(0x4B42D1,0x4B450B,570,151,12)}
native={}
for k,(a,b,size,nx,nf) in cases.items():
 n=list(D.disasm(rd.pe_bytes_at(PE,a,size),a))
 assert b-a==size and len(n)==nx and n[-1].address+n[-1].size==b
 native[k]=n
n=native['1A1']
assert n[35].op_str.endswith(', 2')
assert n[37].op_str=='dword ptr [ebp - 0x18], 0'
assert n[42].op_str=='dword ptr [ebp - 0x18], 5'
assert n[73].op_str=='esi, 0x1e' and n[74].mnemonic=='sub' and n[74].op_str.startswith('esi, ')
assert n[78].op_str=='0x455580' and n[79].op_str=='esi, eax'
assert n[82].mnemonic=='imul' and n[82].op_str.startswith('esi, ')
assert n[91].op_str=='0x453b50'
assert n[130].op_str=='esi, 0x14' and n[131].op_str.startswith('esi, ')
assert n[135].op_str=='0x455580'
assert n[139].op_str.startswith('esi, ')
assert n[148].op_str=='0x453b50'
RX=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(RX.findall(x.op_str))
env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows={}
for label,cpp in sources.items():
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=env,capture_output=True,text=True,timeout=340)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-950:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(code)-end==DATA
 table=[r for r in refs if r['offset']>=end]
 assert len(table)==151
 mp={};mask=set()
 for r in table:
  off=r['offset']-end
  assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
  assert all(j not in mask for j in range(off,off+4))
  mask.update(range(off,off+4))
  va=int.from_bytes(after[off:off+4],'little')
  assert BASE<=va<BASE+WHOLE
  mp.setdefault(va,r['local_symbol_offset'])
 assert DATA-len(mask)==522
 assert all(code[end+j]==after[j] for j in range(DATA) if j not in mask)
 assert all(a in mp and b in mp for a,b,_,_,_ in cases.values())
 row={'native_original_whole_CODE_B':WHOLE,'native_whole_x86':WHOLEX,
      'whole_partial_CPP_B':end,'partial_source_x86':len(I),
      'partial_CPP_stack_frame':I[2].op_str,
      'source_saves_ESI':any(x.mnemonic=='push' and x.op_str=='esi' for x in I[:7]),
      'partial_source_saved_this':next((x.op_str for x in I[3:8] if x.mnemonic=='mov' and x.op_str.endswith(', ecx')),None),
      'source_COFF_fields':len(refs),
      'original_afterRET_DIR32':151,'original_afterRET_nonfield_equal_B':522,
      'original_cases':{},'whole_original_exact':False}
 for k,(a,b,sz,nx,nf) in cases.items():
  lo,hi=mp[a],mp[b]
  s=[x for x in I if lo<=x.address<hi]
  owned=[r for r in refs if lo<=r['offset']<hi]
  item={'original_native_CODE_B':sz,'native_x86':nx,
        'source_CODE_B':hi-lo,'source_x86':len(s)}
  if len(s)==nx:
   mm=[j for j,(v,w) in enumerate(zip(native[k],s)) if v.mnemonic!=w.mnemonic]
   ww=[j for j,(v,w) in enumerate(zip(native[k],s)) if v.size!=w.size]
   gg=[j for j,(v,w) in enumerate(zip(native[k],s)) if roles(v)!=roles(w)]
   item.update({'wrong_native_mnemonics':mm,'wrong_native_widths':ww,'wrong_native_GPRs':gg})
   if not mm:
    assert len(owned)==nf
    raw=rd.pe_bytes_at(PE,a,sz)
    for r in owned:
     j=next(j for j,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)
     d=r['offset']-s[j].address
     n_off=native[k][j].address-a+d
     assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
     val=int.from_bytes(raw[n_off:n_off+4],'little',signed=r['type']=='REL32')
     target=native[k][j].address+d+4+val if r['type']=='REL32' else val
     m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
     expected=int(m.group(1),16) if m else 0x6406AC if r['symbol']=='__ftol2' else None
     assert target==expected,(label,k,j,r['symbol'],hex(target),expected)
    item['original_PE_external_fields_checked']=len(owned)
  row['original_cases'][k]=item
 rows[label]=row
 print(label,'whole partial',end,len(I),'ESI saved?',row['source_saves_ESI'],
       'frame',I[2].op_str,'1A1 source CODE B',
       row['original_cases']['1A1']['source_CODE_B'],
       '191 wrong widths',len(row['original_cases']['191'].get('wrong_native_widths',[])),flush=True)
old=rows['F976-prior-1A1-marker'];new=rows['F977-real-1A1-ESI']
assert (old['whole_partial_CPP_B'],old['partial_source_x86'])==(34055,9341)
assert (new['whole_partial_CPP_B'],new['partial_source_x86'])==(34624,9492)
assert old['source_saves_ESI']==False and new['source_saves_ESI']==True
assert old['partial_CPP_stack_frame']=='esp, 0x16c'
assert new['partial_CPP_stack_frame']=='esp, 0x194'
assert new['partial_source_saved_this']=='dword ptr [ebp - 0x20], ecx'
assert old['original_cases']['1A1']['source_CODE_B']==15
item=new['original_cases']['1A1']
assert (item['source_CODE_B'],item['source_x86'])==(570,151)
assert item['wrong_native_mnemonics']==item['wrong_native_widths']==[]
assert len(item['wrong_native_GPRs'])==67
assert item['original_PE_external_fields_checked']==12
assert new['original_cases']['1A0']['original_PE_external_fields_checked']==12
assert len(old['original_cases']['191']['wrong_native_widths'])==8
assert len(new['original_cases']['191']['wrong_native_widths'])==4
(O/'verified-summary.json').write_text(json.dumps({
 'original_hash_pinned_Japanese_fighter':'0x004AC040',
 'original_entire_callable_GAME_CODE_B':WHOLE,'native_whole_x86':WHOLEX,
 'original_1A1_native_CODE_B_x86':[570,151],
 'source_1A1_native_mnemonic_width_roles_match':True,
 'original_1A1_typed_PE_fields_checked':12,
 'original_1A1_GPR_wrong_instr':67,
 'new_true_ESI_save_across_native_rand_calls':True,
 'natural_partial_Cpp_frame_before_after':['0x16C','0x194'],
 'original_prior_191_wrong_widths_before_after':[8,4],
 'whole_original_game_exact':False,'new_accepted_GAME_CODE_B':0,
 'mass_cold_replay':False,'complete_original_shaped_parent_profiles':rows
},indent=2)+'\n')
print('F977 true 1A1 original 570B/151x86/12 PE targets, all positional native mnemonics and widths; 67 wrong GPR roles, but native ESI save recovered and preceding 191 width deficits improve 8->4. Whole 82KB remains NONEXACT.')
