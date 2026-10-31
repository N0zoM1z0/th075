"""F905 54 real native 252/254 byte-dec sources in one complete fighter.

Original 252/253/254 native 260/260/224 B and 72/72/63 x86;
original actual SUB DL/CL/AL respectively. VC7.1 full natural
source still SUB AL/DL/CL, 259/260/225 B. All six original PE
call/data targets per original case are separately checked for
source-native physical offsets. Full-father incidental 46755B
length is not exact original source. No inert locals, no manual
registers and no corpus cold replay.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json,collections,re
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f905-fighter-byte-decrement'
O.mkdir(parents=True,exist_ok=True)
previous=R/'.analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp'
receipt=R/'.analysis/f901-fighter-31b/verified-summary.json'
if not previous.exists() or not receipt.exists():
 cp=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-tail31b-31c-f901.py')],
       cwd=R,capture_output=True,text=True,timeout=1600)
 (O/'previous-f901-whole.log').write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-720:]
prior=json.loads(receipt.read_text())
assert prior['current_entire_normal_compiler_CODE_B']==46754
assert prior['entire_original_callable_giant_exact'] is False
base=previous.read_text()
native_incs={a:(R/f'probes/FighterScriptedStage{a:X}F879.inc').read_text() for a in (0x252,0x253,0x254)}
marks={a:f'#include "FighterScriptedStage{a:X}F879.inc"' for a in native_incs}
assert all(base.count(marks[a])==1 for a in native_incs)
decs={
  'signed': '--*reinterpret_cast<signed char*>(RAW+0x366);',
  'postfix':'U8(0x366)--;',
  'signed-postfix': '(*reinterpret_cast<signed char*>(RAW+0x366))--;',
  'compound': 'U8(0x366)-=1;',
  'unsigned-index': '--reinterpret_cast<unsigned char*>(RAW)[0x366];',
  'typed-member': '--reinterpret_cast<FighterRealStageByteF905*>(this)->counterAt366;',
  'typed-member-postfix':'reinterpret_cast<FighterRealStageByteF905*>(this)->counterAt366--;',
  'signed-member':'--reinterpret_cast<FighterRealSignedByteF905*>(this)->counterAt366;',
  'byte-lvalue-ref':'{ unsigned char& usedByte=U8(0x366); --usedByte; }',
  'volatile-byte-ref':'{ volatile unsigned char& usedByte=U8(0x366); --usedByte; }',
  'borrowed-raw':'--*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this)+0x366);',
  'byte-zero-sub':'U8(0x366)=static_cast<unsigned char>(U8(0x366)-1);',
  'byte-address-indirect':'--*(&U8(0x366));'
}
predecl='''struct FighterRealStageByteF905 {
    unsigned char original_member_0_to_365[0x366];
    unsigned char counterAt366;
};
struct FighterRealSignedByteF905 {
    unsigned char original_member_0_to_365[0x366];
    signed char counterAt366;
};
'''
assert 'FighterRealStageByteF905' not in base
def patch(frag,tag):
 old='--U8(0x366);'
 assert frag.count(old)==1
 if tag in decs:return frag.replace(old,decs[tag],1)
 if tag=='stage0-negative':return frag.replace('S16(0x62)==0','!S16(0x62)',1)
 if tag=='frame0-negative':return frag.replace('S16(0x64)==0','!S16(0x64)',1)
 if tag=='stage0-constant-left':return frag.replace('S16(0x62)==0','0==S16(0x62)',1)
 if tag=='stage0-typed':return frag.replace('S16(0x62)==0','*reinterpret_cast<const signed short*>(RAW+0x62)==0',1)
 if tag=='action-comparison-reverse':return frag.replace('GetNativeActionAt40FA30()==S16(0x70)','S16(0x70)==GetNativeActionAt40FA30()',1)
 if tag=='stage5-reverse':return frag.replace('S16(0x62)==5','5==S16(0x62)',1)
 if tag=='frame5-reverse':return frag.replace('S16(0x64)==0','0==S16(0x64)',1)
 if tag=='member-efa-typed':
  return frag.replace('*reinterpret_cast<signed short*>(OWNER+0xEFA)=0;',
                      'reinterpret_cast<FighterRealStatusAtEFAF905*>(OWNER)->statusAtEFA=0;',1)
 raise ValueError(tag)
predecl+='''struct FighterRealStatusAtEFAF905 {
    char actual_preceding_fields[0xEFA];
    signed short statusAtEFA;
};
'''
variants={'baseline':{}}
for a in (0x252,0x254):
 for tag in tuple(decs)+('stage0-negative','frame0-negative','stage0-constant-left','stage0-typed',
                         'action-comparison-reverse','stage5-reverse','frame5-reverse','member-efa-typed'):
  variants[hex(a)[2:]+'-'+tag]={a:tag}
for tag in ('signed','postfix','signed-postfix','compound','unsigned-index',
            'typed-member','byte-lvalue-ref','borrowed-raw','stage0-negative',
            'action-comparison-reverse','stage5-reverse'):
 variants['both-'+tag]={0x252:tag,0x254:tag}
spec=importlib.util.spec_from_file_location('f905rd',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
n=list(d.disasm(rd.pe_bytes_at(pe,0x5214b0,46755),0x5214b0));assert len(n)==13230
original_idx={x.address:i for i,x in enumerate(n)}
start_ord={0x252:original_idx[0x5290d2],0x253:original_idx[0x5291d6],0x254:original_idx[0x5292da]}
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[];shapes=collections.Counter()
for tag,changed in variants.items():
 src=predecl+base
 for a,ch in changed.items():
  frag=patch(native_incs[a],ch)
  src=src.replace(marks[a],frag,1)
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj');cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=E,capture_output=True,text=True,timeout=360)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':tag,'compiler_failure':(cp.stdout+cp.stderr)[-540:]}
  rows.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 row={'variant':tag,'full_fighter_CODE_B':ret,'native_whole_CODE_B':46755,
      'full_source_x86':len(I),'real_COFF_fields':len(refs),
      'afterRET_DATA_B':len(code)-ret,'cases':[]}
 if len(I)==13230:
  for a in (0x252,0x253,0x254):
   pos=start_ord[a];count=(63 if a==0x254 else 72)
   sec=I[pos:pos+count];native=n[pos:pos+count]
   lo,hi=sec[0].address,sec[-1].address+sec[-1].size
   f=[r for r in refs if lo<=r['offset']<hi]
   row['cases'].append({'action':hex(a),'original_B':native[-1].address+native[-1].size-native[0].address,
                        'source_B':hi-lo,'x86':len(sec),'physical_PE_field_count':len(f),
                        'original_sub':native[10].op_str,'current_sub':sec[10].op_str,
                        'wrong_width_case_ordinals':[i for i,(x,y) in enumerate(zip(native,sec)) if x.size!=y.size],
                        'wrong_mnem_case_ordinals':[i for i,(x,y) in enumerate(zip(native,sec)) if x.mnemonic!=y.mnemonic][:12]})
 shapes[(ret,len(I),tuple((x['source_B'],x['current_sub']) for x in row['cases']))]+=1
 rows.append(row);print(json.dumps(row),flush=True)
(O/'research-summary.json').write_text(json.dumps(rows,indent=2)+'\n')
print('F905 complete original fighter 252/254 source grammar cases',len(rows),
      'original physical byte SUB 252 DL3B/253 CL3B/254 AL2B')
print('SIZES',dict((str(k),v) for k,v in shapes.items()))

# Every source model is a complete normal VC7.1 game parent;
# no physical native size mismatch may be hidden by summing
# 252 and 254 or masking shifted relocation field bytes.
assert len(rows)==len(variants)==54
assert all('compiler_failure' not in row for row in rows)
assert all(row['afterRET_DATA_B']==901 and row['real_COFF_fields']==1491
           for row in rows)
assert rows[0]['variant']=='baseline'
assert (rows[0]['full_fighter_CODE_B'],rows[0]['full_source_x86'])==(46754,13230)
shapes=collections.Counter((r['full_fighter_CODE_B'],r['full_source_x86']) for r in rows)
assert shapes=={
    (46754,13230):41,(46756,13230):2,(46764,13233):2,
    (46755,13232):2,(46755,13230):2,(46763,13233):2,
    (46756,13232):1,(46757,13230):1,(46773,13236):1}
normal=[r for r in rows if r['full_source_x86']==13230]
assert len(normal)==46
assert all(len(r['cases'])==3 for r in normal)
assert not any(r['cases'][0]['current_sub']==r['cases'][0]['original_sub'] or
               r['cases'][2]['current_sub']==r['cases'][2]['original_sub']
               for r in normal)
assert [len(r['cases']) for r in rows if r['full_source_x86']!=13230]==[0]*8
for r in normal:
    assert all(c['physical_PE_field_count']==6 for c in r['cases'])
# Native physical original each 6 PE field targets; source actual
# state 252/254 offsets shift even if their total 484B remains
# equal. A genuine byte-subs source is compared to ORIGINAL
# 260/260/224 B, never just the 744B aggregate.
tested=[]
for a,orig_size,src_size,nx in ((0x252,260,259,72),
                                (0x253,260,260,72),
                                (0x254,224,225,63)):
    code,refs=rd.object_function(O/'baseline.obj',
             '?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    at=start_ord[a]
    origseg=n[at:at+nx];srcseg=ins[at:at+nx]
    low=srcseg[0].address;hi=srcseg[-1].address+srcseg[-1].size
    nativebytes=rd.pe_bytes_at(pe,origseg[0].address,orig_size)
    f=[r for r in refs if low<=r['offset']<hi]
    assert len(f)==6 and hi-low==src_size
    offsets=[];dest=[]
    for field in f:
        ordinal=next(i for i,x in enumerate(srcseg)
            if x.address<=field['offset']<x.address+x.size)
        original_loc=origseg[ordinal].address-origseg[0].address+origseg[ordinal].size-4
        source_loc=field['offset']-low
        assert source_loc-original_loc==src_size-orig_size
        match=re.search(r'At([0-9a-fA-F]{6,8})',field['symbol'])
        assert match is not None and field['addend']==0 and field['local_symbol_offset'] is None
        expected=int(match.group(1),16)
        value=int.from_bytes(nativebytes[original_loc:original_loc+4],'little',
                        signed=field['type']=='REL32')
        actual=(origseg[0].address+original_loc+4+value
                if field['type']=='REL32' else value)
        assert actual==expected,(hex(a),ordinal,hex(actual),hex(expected))
        offsets.append((original_loc,source_loc));dest.append(hex(actual))
    tested.append({'case':hex(a),'native_B':orig_size,'source_B':src_size,
                   'source_actual_PE_field_locations_vs_native':offsets,
                   'original_6_PE_targets':dest})
assert [j['source_B'] for j in tested]==[259,260,225]
(O/'verified-summary.json').write_text(json.dumps({
  'native_original_callable_giant':'0x005214B0',
  'original_whole_CODE_B':46755,
  'original_whole_x86':13230,
  'real_three_native_case_CODE_B':[260,260,224],
  'normal_source_three_case_B':[259,260,225],
  'real_native_byte_SUB_registers':['dl','cl','al'],
  'normal_compiler_byte_SUB_registers':['al','dl','cl'],
  'real_54_selected_full_source_Cpp_variants':54,
  'full_compiler_x86_count_correct_models':46,
  'same_native_case_MNEMONIC_count_but_byte_width_wrong_models':43,
  'full_native_6_original_PE_fields_each_verified':tested,
  'native_252_original_six_PE_fields_shifted_by_minus_one':True,
  'native_254_original_six_PE_fields_shifted_by_plus_one':True,
  'nonnative_accidental_whole_byte_count_46755_B_models':4,
  'real_original_252_254_byte_counter_exact':False,
  'whole_original_callable_giant_exact':False,
  'new_adopted_whole_callable_CODE_B':0,
  'mass_cold_replay':False,
  'real_source_alternatives':rows
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['whole_original_callable_giant_exact'] is False
print('F905 54 complete original physical fighter VC7.1 sources: real 252/253/254 native SUB DL/CL/AL and cases260/260/224B, current AL/DL/CL and259/260/225B. Forty-six still13230 x86; none restores BOTH original register/widths, even four misleading 46755B whole-size models. Each case six real PE targets verified at original positions, 252/254 six original fields shifted -1/+1B. Zero whole exact callable CODE; no mass cold replay.')
