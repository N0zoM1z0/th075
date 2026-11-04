#!/usr/bin/env python3
"""F1058: full-original-shaped Boss: parent-Y + original 657888 source grammar.

Compile true entire 81KB partial C++ parent, not cropped 33B cases. Compare
all 5 genuinely native 1908B/402-x86 game states and real original physical
external Y-offset PE fields by native instruction ordinal. Never consider a
source symbol name sufficient without real original field byte locations.
"""
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import importlib.util,json,os,re,subprocess,sys
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1058-long-y-grammar';O.mkdir(parents=True,exist_ok=True)
base=(R/'probes/CharacterObjectWhole0050A580F1044.cpp').read_text()
fragment=(R/'probes/CharacterObjectBossLongF1057.inc').read_text()
anchor='#include "CharacterObjectBossLongF1057.inc"';assert base.count(anchor)==5
expr='(*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1057_YOffsetAt00657888'
old='F1037_POSITION(PARENT_GRANDPARENT).yPosition+g_F1057_YOffsetAt00657888'
assert fragment.count(expr)==2
Y='F1037_POSITION(PARENT_GRANDPARENT).yPosition'
G='g_F1057_YOffsetAt00657888'
variants={
 'selected-current':expr,
 'previous-bad-physical-fields':old,
 'ptr-unparenthesized':'(*reinterpret_cast<float*>(PARENT_GRANDPARENT+0x48))+'+G,
 'ptr-const':'(*reinterpret_cast<const float*>(PARENT_GRANDPARENT+0x48))+'+G,
 'typed-member-deref':'(*reinterpret_cast<FrameActorPositionPairF1037*>(PARENT_GRANDPARENT+0x44)).yPosition+'+G,
 'lvalue-static-const':'static_cast<const float&>('+Y+')+'+G,
 'explicit-float':'float('+Y+')+'+G,
 'const-global-lvalue':Y+'+(*(&'+G+'))',
 'reverse-order':G+'+'+Y,
 'reverse-ptr':G+'+(*reinterpret_cast<float*>(PARENT_GRANDPARENT+0x48))',
 'dereference-pointer':'*(&'+Y+'+0)+'+G,
 'typed-direct-ref':Y+'+static_cast<const float&>('+G+')',
}
sp=importlib.util.spec_from_file_location('f1058rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
P=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==0x0050A580)
original_all=rd.pe_bytes_at(P,boss['address'],boss['size']);assert boss['size']==81539
assert boss['sha256']==__import__('hashlib').sha256(original_all).hexdigest()
origins=[('33b',0x50f25a,0x50f9ce),('33d',0x50faca,0x51023e),('33f',0x51033a,0x510aae),('341',0x510baa,0x51131e),('343',0x51141a,0x511b8e)]
orig={label:list(D.disasm(rd.pe_bytes_at(P,a,b-a),a)) for label,a,b in origins}
assert all(len(x)==402 for x in orig.values())
mp=rd.pe_bytes_at(P,boss['tables'][0]['map_addr'],199)
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for label,alternate in variants.items():
 inc=fragment.replace(expr,alternate)
 assert inc.count(alternate)==2,(label,inc.count(alternate))
 (O/(label+'.inc')).write_text(inc)
 src=base.replace(anchor,'#include "'+label+'.inc"')
 (O/(label+'.cpp')).write_text(src)
 obj=O/(label+'.obj')
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(O/(label+'.cpp')),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,text=True,capture_output=True,timeout=350)
 (O/(label+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  rows.append({'variant':label,'compiler_error':(cp.stdout+cp.stderr)[-450:]})
  print(label,'COMPILER FAIL',flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 T=sorted([r for r in refs if r['offset']>=end],key=lambda r:r['offset'])
 assert len(T)==92 and len(code)-end==567
 row={'variant':label,'whole_partial_source_CODE_B':end,'whole_partial_source_x86':len(I),'five_original_state_field_status':{},'original_whole_game_exact':False}
 for key,a,b in origins:
  slot=mp[int(key,16)-0x320];lo,hi=T[slot]['local_symbol_offset'],T[slot+1]['local_symbol_offset']
  S=[x for x in I if lo<=x.address<hi];N=orig[key]
  site={'source_inner_CODE_B':hi-lo,'source_x86':len(S),'native_x86':402}
  if len(S)==len(N):
   site['matching_native_mnemonics']=sum(n.mnemonic==s.mnemonic for n,s in zip(N,S))
   refs_in=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
   match=0;mismatches=[]
   for r in refs_in:
    j=next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size)
    d=r['offset']-S[j].address
    if d+4>N[j].size:
     mismatches.append({'ordinal':j,'symbol':r['symbol'],'reason':'wrong-native-instruction-field-kind'});continue
    p=N[j].address+d
    disp=int.from_bytes(rd.pe_bytes_at(P,p,4),'little',signed=r['type']=='REL32')
    native_target=p+4+disp if r['type']=='REL32' else disp
    v=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
    expect=int(v.group(1),16) if v else 0x6406ac if r['symbol']=='__ftol2' else None
    if native_target==expect:match+=1
    else:mismatches.append({'ordinal':j,'symbol':r['symbol'],'original_target':hex(native_target),'expected':hex(expect or 0)})
   site.update({'actual_source_external_COFF_fields':len(refs_in),'correct_original_physically_positioned_PE_targets':match,'wrong_original_physical_targets':mismatches,
    'source_natively_ordered_Y_global_add_ordinal':[next(j for j,x in enumerate(S) if x.address<=r['offset']<x.address+x.size) for r in refs_in if 'At00657888' in r['symbol']]})
  row['five_original_state_field_status'][key]=site
 rows.append(row)
 one=row['five_original_state_field_status']['33b']
 print(label,'whole',end,len(I),'33B native M',one.get('matching_native_mnemonics'),'real PE fields',one.get('correct_original_physically_positioned_PE_targets'), '/',one.get('actual_source_external_COFF_fields'),'Y indices',one.get('source_natively_ordered_Y_global_add_ordinal'),flush=True)
(O/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
assert len(rows)==len(variants)==12
assert all('compiler_error' not in r for r in rows)
assert all(r['whole_partial_source_CODE_B']==25234 and r['whole_partial_source_x86']==6790 for r in rows)
assert all(x['matching_native_mnemonics']==402 and x['actual_source_external_COFF_fields']==33
           for r in rows for x in r['five_original_state_field_status'].values())
physically_complete=[r for r in rows if all(x['correct_original_physically_positioned_PE_targets']==33
             for x in r['five_original_state_field_status'].values())]
physically_short=[r for r in rows if all(x['correct_original_physically_positioned_PE_targets']==31
             for x in r['five_original_state_field_status'].values())]
assert len(physically_complete)==4 and len(physically_short)==8
assert all(x['source_natively_ordered_Y_global_add_ordinal']==[152,263,278]
           for r in physically_complete for x in r['five_original_state_field_status'].values())
assert all(x['source_natively_ordered_Y_global_add_ordinal']==[152,262,277]
           for r in physically_short for x in r['five_original_state_field_status'].values())
assert rows[0]['five_original_state_field_status']['33b']['correct_original_physically_positioned_PE_targets']==33
assert rows[1]['five_original_state_field_status']['33b']['correct_original_physically_positioned_PE_targets']==31
assert all(x['correct_original_physically_positioned_PE_targets']==33 for x in rows[0]['five_original_state_field_status'].values())
print('F1058: 12 distinct whole normal C++ parent variants: four source grammars restore 33/33 physical PE fields across all five cases, eight emit 31/33, while every case retains the same 402 original native mnemonic ordinals. Original 81KB remains NONEXACT.')
