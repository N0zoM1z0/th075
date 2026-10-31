"""F903 native mode63 29 complete parent typed status/short-circuit sources.

Actual original 417B/109x86/7 physically grounded PE fields.
Twenty-nine whole VC7.1 owner short+60, stage+62, signed key/flag
source alternatives, all using meaningful original game operands.
Twenty-seven preserve original-sized 417B/109x86 but two wrong
CMP register and widths at original case ordinals38/61.
One source makes the entire generated father 46755B, but changes
the real mode63 interior to nonnative 418B instead.
No whole exact original CODE or mass cold replay.
"""
from pathlib import Path
import importlib.util,sys,os,subprocess,json,collections,re
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f903-fighter-63-typed-conditions'
O.mkdir(parents=True,exist_ok=True)
prior=R/'.analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp'
receipt=R/'.analysis/f901-fighter-31b/verified-summary.json'
if not prior.exists() or not receipt.exists():
    cp=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-tail31b-31c-f901.py')],
       cwd=R,capture_output=True,text=True,timeout=1600)
    (O/'prior-f901-native.log').write_text(cp.stdout+cp.stderr)
    assert cp.returncode==0,(cp.stdout+cp.stderr)[-700:]
rec=json.loads(receipt.read_text())
assert rec['current_entire_normal_compiler_CODE_B']==46754
assert rec['entire_original_callable_giant_exact'] is False
parent=prior.read_text()
inc=(R/'probes/FighterMode63BasicF626.inc').read_text()
include='#include "FighterMode63BasicF626.inc"'
assert parent.count(include)==1 and inc.count('case 0x63:')==1
raw_owner='*reinterpret_cast<signed short*>(OWNER+0x60)'
raw_stage='I16(0x62)'
raw_key='*reinterpret_cast<signed char*>(RAW+0x39D)'
raw_flag='*reinterpret_cast<signed char*>(RAW+0x2CD)'
assert inc.count(raw_owner)==4 and inc.count(raw_stage)==4 and inc.count(raw_key)==7
predecl=('''struct FighterOwnerStageF903 {
    char preceding[0x60];
    signed short stageAt60;
};
struct FighterActorModeF903 {
    char beforeStage[0x62];
    signed short stageAt62;
};
''')
assert 'FighterOwnerStageF903' not in parent
typed_owner='reinterpret_cast<FighterOwnerStageF903*>(OWNER)->stageAt60'
typed_stage='reinterpret_cast<FighterActorModeF903*>(this)->stageAt62'
variants={'baseline':(inc,'')}
for tag,typ in (
 ('typed-owner',typed_owner),
 ('typed-owner-const','static_cast<const signed short&>('+typed_owner+')'),
 ('owner-direct-pointer',
  '*reinterpret_cast<const signed short*>(*reinterpret_cast<char**>(RAW+0x2E8)+0x60)'),
 ('owner-charcast','*reinterpret_cast<const signed short*>(reinterpret_cast<const char*>(OWNER)+0x60)'),
 ('owner-array-indirect',
  'reinterpret_cast<const signed short*>(OWNER+0x60)[0]'),
 ('owner-rvalue-const','static_cast<const signed short>('+raw_owner+')'),
 ('owner-shortpluszero','static_cast<int>('+raw_owner+')+0'),
 ('owner-ref-lvalue','static_cast<const signed short&>('+raw_owner+')'),
 ('owner-value-pluszero','0+('+raw_owner+')')):
 variants[tag]=(inc.replace(raw_owner,typ),predecl)
for tag,typ in (
 ('typed-stage',typed_stage),
 ('stage-original-short','S16(0x62)'),
 ('stage-const','*reinterpret_cast<const signed short*>(RAW+0x62)'),
 ('stage-char-mem','reinterpret_cast<const signed short*>(RAW+0x62)[0]'),
 ('stage-rvalueconst','static_cast<const signed short>(I16(0x62))')):
 variants[tag]=(inc.replace(raw_stage,typ),predecl)
for tag,typ in (
 ('key-const','*reinterpret_cast<const signed char*>(RAW+0x39D)'),
 ('key-staticcast','static_cast<signed char>('+raw_key+')'),
 ('key-readindex','reinterpret_cast<const signed char*>(RAW)[0x39D]')):
 variants[tag]=(inc.replace(raw_key,typ),predecl)
for tag,typ in (
 ('flag-const','*reinterpret_cast<const signed char*>(RAW+0x2CD)'),
 ('flag-array','reinterpret_cast<const signed char*>(RAW)[0x2CD]')):
 variants[tag]=(inc.replace(raw_flag,typ),predecl)
# Boolean-preserving spelling variants. Strict signed stage <150 is
# equivalent to <=149 or not >=150 for every possible value.
for tag,old,new in [
 ('owner-limit-149',raw_owner+'<150',raw_owner+'<=149'),
 ('owner-limit-negated',raw_owner+'<150','!('+raw_owner+'>=150)'),
 ('stage-two-equality','I16(0x62)==2','2==I16(0x62)'),
 ('stage-greater-one','I16(0x62)>1','I16(0x62)>=2'),
 ('stage-greater-zero','I16(0x62)>0','I16(0x62)>=1'),
 ('key-greater-zero',raw_key+'>0',raw_key+'>=1'),
 ('mode-const-source','g_ModeAt006714B4 != 3','3 != g_ModeAt006714B4'),
 ('flag-zero-source',raw_flag+'==0','0=='+raw_flag),
]:
 assert old in inc
 variants[tag]=(inc.replace(old,new),predecl)
# Also test separately truly used owner status value alias via C++ block
# in real branch: this yields different number of x86, NEVER crop.
frag=inc.replace('''            *reinterpret_cast<signed short*>(OWNER+0x60)<150 &&''',
 '''            reinterpret_cast<FighterOwnerStageF903*>(OWNER)->stageAt60<150 &&''')
variants['owner-typed-precondition']=(frag,predecl)
spec=importlib.util.spec_from_file_location('r903',R/'scripts/compare-coff-function.py');rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
native=list(d.disasm(rd.pe_bytes_at(pe,0x523c9d,417),0x523c9d));assert len(native)==109
wholeoriginal=list(d.disasm(rd.pe_bytes_at(pe,0x5214b0,46755),0x5214b0))
start=next(i for i,x in enumerate(wholeoriginal) if x.address==0x523c9d)
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results=[];cnt=collections.Counter()
for tag,(frag,decl) in variants.items():
 cpp=O/(tag+'.cpp');obj=O/(tag+'.obj')
 cpp.write_text(decl+parent.replace(include,frag,1))
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
   '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,
   capture_output=True,text=True,timeout=360)
 (O/(tag+'.log')).write_text(cp.stdout+cp.stderr)
 if cp.returncode:
  row={'variant':tag,'compile_failure':(cp.stdout+cp.stderr)[-480:]}
  results.append(row);print(json.dumps(row),flush=True);continue
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 row={'variant':tag,'whole_SOURCE_B':ret,'whole_x86':len(I),
       'whole_COFF_fields':len(refs),'whole_afterRET_DATA_B':len(code)-ret}
 if len(I)>=start+109:
  seg=I[start:start+109];lo,hi=seg[0].address,seg[-1].address+seg[-1].size
  field=[r for r in refs if lo<=r['offset']<hi]
  row.update({'native_63_B':417,'source_first_109_instructions_B':hi-lo,
              'original_native_63_x86':109,'source_63_first_109_x86':len(seg),
              'source_PE_fields_in_first109':len(field),
              'source_ordinal38_CMP':seg[38].op_str if len(seg)>38 else '',
              'source_ordinal61_CMP':seg[61].op_str if len(seg)>61 else '',
              'native_original_63_width_wrong_ordinals':[i for i,(a,b) in enumerate(zip(native,seg)) if a.size!=b.size],
              'native_original_63_mnemonic_wrong_ordinals':[i for i,(a,b) in enumerate(zip(native,seg)) if a.mnemonic!=b.mnemonic][:12]})
 cnt[(ret,len(I),row.get('source_first_109_instructions_B'),
      tuple(row.get('native_original_63_width_wrong_ordinals',[])))]+=1
 results.append(row);print(json.dumps(row),flush=True)
(O/'research-summary.json').write_text(json.dumps(results,indent=2)+'\n')
print('F903 real original 63 typed C++ experiment variants',len(results),
      'shapes',dict((str(k),v) for k,v in cnt.items()))

# Strict whole-father PE negatives, no fake local byte masking.
assert len(variants)==len(results)==29
assert all('compile_failure' not in r for r in results)
shapes=collections.Counter((r['whole_SOURCE_B'],r['whole_x86'],
                 r['source_first_109_instructions_B']) for r in results)
assert shapes=={(46754,13230,417):27,(46755,13230,418):1,
                (46758,13230,421):1}
for row in results:
    assert row['whole_COFF_fields']==1491 and row['whole_afterRET_DATA_B']==901
    assert row['source_PE_fields_in_first109']==7
    assert row['original_native_63_x86']==row['source_63_first_109_x86']==109
for row in results:
    if row['source_first_109_instructions_B']==417:
        assert row['native_original_63_width_wrong_ordinals']==[38,61]
        assert row['source_ordinal38_CMP'] in ('eax, 0x96','eax, 0x95')
        assert row['source_ordinal61_CMP'] in ('edx, 0x96','edx, 0x95')
assert next(row for row in results if row['whole_SOURCE_B']==46755)['variant']=='stage-greater-zero'
assert next(row for row in results if row['whole_SOURCE_B']==46758)['variant']=='key-greater-zero'
proven=[]
origraw=rd.pe_bytes_at(pe,0x523c9d,417)
for label in ('baseline','typed-owner','typed-stage','owner-limit-negated'):
    code,refs=rd.object_function(O/(label+'.obj'),
               '?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ')
    ins=[]
    for item in d.disasm(code,0):
        ins.append(item)
        if item.mnemonic=='ret':break
    region=ins[start:start+109]
    lo=region[0].address;hi=region[-1].address+region[-1].size
    assert hi-lo==417
    fs=[f for f in refs if lo<=f['offset']<hi]
    assert len(fs)==7
    moved=[]
    for field in fs:
        index=next(j for j,x in enumerate(region)
                   if x.address<=field['offset']<x.address+x.size)
        native_inst=native[index]
        original_offset=native_inst.address-0x523c9d+native_inst.size-4
        source_offset=field['offset']-lo
        if original_offset!=source_offset:
            moved.append((index,original_offset,source_offset))
        assert field['addend']==0 and field['local_symbol_offset'] is None
        assert field['type'] in ('REL32','DIR32')
        match=re.search(r'At([0-9a-fA-F]{6,8})',field['symbol'])
        assert match is not None
        expected=int(match.group(1),16)
        value=int.from_bytes(origraw[original_offset:original_offset+4],
                             'little',signed=field['type']=='REL32')
        target=(0x523c9d+original_offset+4+value
                if field['type']=='REL32' else value)
        assert target==expected,(label,index,hex(target),hex(expected))
    assert moved==[(48,185,184)]
    proven.append({'variant':label,'all_original_7_PE_destinations_verified':True,
          'original_physically_shifted_COFFER_operand_ordinal48':moved})
(O/'verified-summary.json').write_text(json.dumps({
    'original_callable_giant':'0x005214B0',
    'native_original_whole_CODE_B':46755,
    'native_original_whole_x86':13230,
    'native_mode63_entire_inner_CODE_B':417,
    'native_mode63_original_x86':109,
    'native_mode63_original_real_PE_fields':7,
    'normal_full_VC71_actual_source_variants':29,
    'original_case_sized_417B_but_two_width_errors_variants':27,
    'native_mode63_original_width_wrong_case_ordinals':[38,61],
    'four_independent_original_7_PE_targets_and_shift_proofs':proven,
    'actual_ordinal48_real_original_PE_field_offset':185,
    'normal_source_ordinal48_shifted_PE_field_offset':184,
    'misleading_whole_exact_length_from_wrong_63_case':46755,
    'misleading_whole_equal_length_native_63_wrong_B':418,
    'all_29_genuine_full_compiler_source_variants_proven':True,
    'original_whole_callable_giant_exact':False,
    'new_accepted_whole_callable_CODE_B':0,
    'mass_cold_replay':False,
    'full_original_source_variants':results
},indent=2)+'\n')
assert json.loads((O/'verified-summary.json').read_text())['original_whole_callable_giant_exact'] is False
print('F903 real mode63 417 native B/109x86/7 original PE fields: 29 full VC7.1 sources, 27 unchanged 417B with two actual CMP GPR/width errors ord38/61 and source COFF field moved -1B at native original ordinal48. One semantically rewritten source generates WHOLE 46755B but wrong inner 418B: never fake whole exact CODE. All four selected physical PE target audits pass; no mass replay.')
