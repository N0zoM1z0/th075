#!/usr/bin/env python3
"""F926: bounded full-parent checks of genuinely used actor/opponent read grammars.

F923: native first bad GPR at physical 00545109 action0x59;
F924: native three CMP width differences in action0x63.
Compile full 58KB F917 parent for representative native-valid actor
stage/float and opponent stage value-category hypotheses, checking
original PE whole x86, fields and 943B afterRET shape. Negative
whole-function source study; never credit independent case CODE.
"""
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import importlib.util, json, os, re, subprocess, sys

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f926-fighter-register-owners'
O.mkdir(parents=True,exist_ok=True)
prior=R/'.analysis/f917-native-burst-x87-verified/F917-borrowed-real-X.cpp'
receipt=R/'.analysis/f917-native-burst-x87-verified/verified-summary.json'
if not prior.exists() or not receipt.exists():
 p=subprocess.run([str(R/'scripts/repo-python'),
                   str(R/'scripts/verify-fighter-native-burst-x87-f917.py')],
                  cwd=R,capture_output=True,text=True,timeout=950)
 (O/'f917-prior.log').write_text(p.stdout+p.stderr)
 assert p.returncode==0,(p.stdout+p.stderr)[-900:]
assert json.loads(receipt.read_text())['native_whole_original_exact'] is False
base=prior.read_text()
a59='#include "FighterEarlyBounceTypedF752.inc"'
a63='#include "FighterMode63BasicF626.inc"'
assert base.count(a59)==base.count(a63)==1
fragment59=(R/'probes/FighterEarlyBounceTypedF752.inc').read_text()
fragment63=(R/'probes/FighterMode63BasicF626.inc').read_text()
stage59='if (S16(0x62)>1)'
opponent63='*reinterpret_cast<signed short*>(OWNER+0x60)'
assert fragment59.count(stage59)==1 and fragment63.count(opponent63)==4
member_stage='reinterpret_cast<F926OpponentStage*>(OWNER)->stageAt60'
header='''// Borrowed original owner+0x60 signed stage, not a complete object.
struct F926OpponentStage {
    unsigned char unknownEarlierBytes[0x60];
    signed short stageAt60;
};
typedef char F926StageSize[(sizeof(F926OpponentStage)==0x62)?1:-1];
'''
candidates={
 'baseline':base,
 'actor-reversed-stage':base.replace(a59,fragment59.replace(stage59,'if (1<S16(0x62))'),1),
 'actor-ge-stage':base.replace(a59,fragment59.replace(stage59,'if (S16(0x62)>=2)'),1),
 'actor-real-const-stage':base.replace(a59,fragment59.replace(stage59,
     'if (*reinterpret_cast<const signed short*>(RAW+0x62)>1)'),1),
 'actor-float-sub-assign':base.replace(a59,fragment59.replace(
     'POS54=POS54-POS5C;','POS54-=POS5C;'),1),
 'actor-float-plus-assign':base.replace(a59,fragment59.replace(
     'F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;',
     'F32(0x30)+=g_F728_RandomOffsetYAt00657858;'),1),
 'actor-signed-conversion':base.replace(a59,fragment59.replace(
     '(*(&POS54))*g_ContactProjectionAt00657888',
     'POS54*g_ContactProjectionAt00657888'),1),
 'owner-const-short':base.replace(a63,fragment63.replace(
     opponent63,'*reinterpret_cast<const signed short*>(OWNER+0x60)'),1),
 'owner-volatile-short':base.replace(a63,fragment63.replace(
     opponent63,'*reinterpret_cast<volatile signed short*>(OWNER+0x60)'),1),
 'owner-typed-member':header+base.replace(a63,fragment63.replace(
     opponent63,member_stage),1),
}
spec=importlib.util.spec_from_file_location('f926reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32)
PE=rd.verified_target()
N=list(D.disasm(rd.pe_bytes_at(PE,0x543210,58294),0x543210))
assert len(N)==16471 and N[-1].address+N[-1].size==0x5515c6
first=next(i for i,x in enumerate(N) if x.address==0x545109)
mode=next(i for i,x in enumerate(N) if x.address==0x545ade)
assert first==2198 and (N[first+94].address+N[first+94].size)==0x54526d
assert [N[mode+j].op_str for j in (18,61,84)]==[
    'edx, 0x96','eax, 0x96','edx, 0x96']
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda ins:tuple(rx.findall(ins.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
results=[]
for name,src in candidates.items():
 cpp=O/(name+'.cpp');obj=O/(name+'.obj')
 cpp.write_text(src)
 cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
  '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
  cwd=R,env=E,capture_output=True,text=True,timeout=345)
 (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
 assert cp.returncode==0,(cp.stdout+cp.stderr)[-850:]
 code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ')
 I=[]
 for x in D.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 end=I[-1].address+I[-1].size
 assert len(I)==16471 and len(refs)==1863 and len(code)-end==943
 wrong=[i for i,(n,s) in enumerate(zip(N,I)) if roles(n)!=roles(s)]
 width=[i for i,(n,s) in enumerate(zip(N,I)) if n.size!=s.size]
 mnemonics=[i for i,(n,s) in enumerate(zip(N,I)) if n.mnemonic!=s.mnemonic]
 r={'variant':name,'whole_source_CODE_B':end,'whole_x86':len(I),
   'source_PE_COFF_fields_total':len(refs),'afterRET_DATA_B':len(code)-end,
   'first_original_GPR_wrong_ordinal':wrong[0] if wrong else None,
   'native_action59_wrong_GPR_instr':sum(roles(n)!=roles(s)
             for n,s in zip(N[first:first+95],I[first:first+95])),
   'whole_wrong_GPR_instr':len(wrong),
   'original_three_mode63_CMP_source_roles':[I[mode+j].op_str for j in (18,61,84)],
   'whole_width_wrong_ordinals':width[:20],
   'whole_mnemonic_wrong_ordinals':mnemonics[:20]}
 results.append(r);print(name,'source',end,'GPR',r['first_original_GPR_wrong_ordinal'],
  r['native_action59_wrong_GPR_instr'],'mode63',r['original_three_mode63_CMP_source_roles'],
  'widths',width[:12],flush=True)
assert len(results)==10
normal=[r for r in results if r['whole_source_CODE_B']==58293]
assert len(normal)==10
assert all(r['first_original_GPR_wrong_ordinal']==2198 for r in normal)
assert min(r['native_action59_wrong_GPR_instr'] for r in normal)==19
assert all(r['original_three_mode63_CMP_source_roles']
        ==['eax, 0x96','ecx, 0x96','eax, 0x96'] for r in normal)
assert all(r['whole_wrong_GPR_instr']>=1741 for r in normal)
assert all(r['whole_width_wrong_ordinals']==[2934,2977,3000]
           for r in normal if r['variant'] not in (
              'actor-float-plus-assign','actor-signed-conversion'))
assert results[0]['whole_mnemonic_wrong_ordinals']==[]
# Semantically valid source alternatives can change x86 conditional
# mnemonics. Record these physical negatives; never require all
# controls to reproduce the baseline's exact instruction identity.
assert all(not r['whole_mnemonic_wrong_ordinals'] for r in normal
           if r['variant'] in ('baseline','actor-reversed-stage',
              'actor-real-const-stage','actor-float-sub-assign',
              'actor-float-plus-assign','actor-signed-conversion',
              'owner-const-short','owner-volatile-short','owner-typed-member'))
(O/'verified-summary.json').write_text(json.dumps({
 'original_Japanese_SHA_pinned_fighter':'0x00543210',
 'native_complete_CODE_B':58294,'native_complete_x86':16471,
 'real_initial_GPR_divergence':'0x00545109','native_initial_GPR_whole_ordinal':2198,
 'real_first_case_complete_CODE_B':356,'real_first_case_x86':95,
 'real_mode63_three_CMP_width_ordinals':[2934,2977,3000],
 'complete_source_grammar_controls':len(results),'original_whole_exact':False,
 'all_unit_cold_replay':False,'new_exact_whole_original_bytes':0,
 'actual_complete_source_results':results},indent=2)+'\n')
print('F926 complete fighter semantic read controls: 10 whole 16471-x86 original sources; first GPR role and 3 CMP original roles unaffected. No new exact callable CODE.')
