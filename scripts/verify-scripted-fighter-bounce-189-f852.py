#!/usr/bin/env python3
"""F852: native original 189 bounce/state7 381B/107 x86/11 physical PE fields.

Regenerate previous F851 original whole parent; use real actor
FUCOMPP threshold equality, ground POS48+POS54 compare, bounce scalar
00657478, action7 and stage3 float initialization, all ordinary C++.
Compile ONE affected full fighter. The 189 original x86 widths,
mnemonics, eleven true PE field types/positions/targets match, but
68 real GPR operand byte differences and two final giant JMP operand
bytes remain. Prior 136/186/187/188 honest negatives, twenty
earlier PE-backed cases, five 901B tables and default 46B verified.
No whole-function exact credit; no accepted-corpus cold replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f852-scripted-189'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD189=[1,5,8,12,16,19,23,27,33,45,49,57,60,67,70,77,80,87,96,108,111,120,123,126,129,145,148,155,158,165,168,184,188,191,196,199,202,205,208,211,214,217,220,223,239,242,249,252,261,264,277,278,291,293,297,300,314,318,321,326,330,333,337,340,347,350,357,360,377,378]
PE_FIELDS={
 13:(0x00453E20,'ResetAt453E20'),
 23:(0x0065782C,'g_ThresholdAt0065782C'),
 31:(0x0065747C,'g_AnimationDeltaAt0065747C'),
 36:(0x0065782C,'g_ThresholdAt0065782C'),
 46:(0x0065782C,'g_ThresholdAt0065782C'),
 64:(0x0065782C,'g_ThresholdAt0065782C'),
 72:(0x00657478,'g_F852GroundBounceMultiplierAt00657478'),
 77:(0x0040FB40,'SetAuxActionAt40FB40'),
 80:(0x0040FA30,'GetNativeActionAt40FA30'),
 88:(0x0040FAC0,'SetNativeActionAt40FAC0'),
 105:(0x00453D60,'PrepareActionAt453D60'),
}
def need(b,m):
 if not b:raise ValueError(m)
def ld(tag,fn):
 s=importlib.util.spec_from_file_location(tag,R/'scripts'/fn)
 need(s is not None and s.loader is not None,'missing native original PE helper '+fn)
 m=importlib.util.module_from_spec(s);sys.modules[tag]=m;s.loader.exec_module(m);return m
def gen_source(rd,pe,d,by):
 O.mkdir(parents=True,exist_ok=True)
 cp=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-ground-188-f851.py')],
       cwd=R,text=True,capture_output=True,timeout=1500)
 (O/'f851-prior-native-original.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'previous selected original fighter 188 PE source proof failed '+(cp.stdout+cp.stderr)[-850:])
 original=list(d.disasm(rd.pe_bytes_at(pe,by[0x189],by[0x18a]-by[0x189]),by[0x189]))
 need(len(original)==107 and by[0x18a]-by[0x189]==381
      and original[25].mnemonic=='fucompp'
      and original[27].op_str=='ah, 0x44'
      and original[28].mnemonic=='jp'
      and original[49].mnemonic=='jne'
      and original[63].mnemonic=='fadd'
      and original[72].mnemonic=='fmul'
      and original[76].mnemonic=='mov'
      and original[77].op_str=='0x40fb40'
      and original[78].op_str=='0x52cb4f'
      and original[98].op_str.endswith(', 0x41700000')
      and original[100].op_str.endswith(', 0x41080000')
      and original[102].op_str.endswith(', 0x3f59999a')
      and original[103].op_str=='0x1d',
      'real native actor original 189 x87/bounce/stage3 physical instructions changed')
 src=(R/'.analysis/f851-scripted-188/Boss005214B0-F851-whole.cpp').read_text()
 mark='        case 0x189: g_FighterProbeMarker = 394; break;'
 frag=(R/'probes/FighterScriptedBounce189F852.inc').read_text()
 need(src.count(mark)==1 and frag.count('case 0x189:')==1
      and frag.count('return;')==2
      and 'if (*(&POS48)==g_ThresholdAt0065782C)' in frag
      and 'POS48+POS54<g_ThresholdAt0065782C' in frag
      and 'POS=POS*g_F852GroundBounceMultiplierAt00657478' in frag
      and 'SetAuxActionAt40FB40(7)' in frag
      and 'POS5C=0.85f' in frag,
      'original actor 189 native bounce source changed')
 declaration='extern float g_F852GroundBounceMultiplierAt00657478;\n'
 need(src.count(declaration)==0,'duplicate actual float bounce global')
 return declaration+src.replace(mark,'#include "FighterScriptedBounce189F852.inc"',1)
def compile_one(src):
 cpp=O/'Boss005214B0-F852-whole.cpp';obj=O/'Boss005214B0-F852-whole.obj'
 cpp.write_text(src)
 E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
 E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
 E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
     '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
     cwd=R,env=E,capture_output=True,text=True,timeout=310)
 (O/'compiler.log').write_text(p.stdout+p.stderr)
 need(p.returncode==0,'native original selected whole fighter189 build failed '+(p.stdout+p.stderr)[-760:])
 return obj
def main():
 rd=ld('f852rd','compare-coff-function.py')
 ac=ld('f852ac','report-fighter-action-handlers.py')
 f834=ld('f852f834','verify-scripted-fighter-fourway-c8-f834.py')
 f820=ld('f852f820','verify-scripted-fighter-landing-trio-f820.py')
 f847=ld('f852f847','verify-scripted-fighter-projectile-134135-f847.py')
 f849=ld('f852f849','verify-scripted-fighter-physics-136-f849.py')
 f850=ld('f852f850','verify-scripted-fighter-ground-186187-f850.py')
 f851=ld('f852f851','verify-scripted-fighter-ground-188-f851.py')
 zero=ld('f852zero','verify-fighter-actionzero-natural-source.py')
 sw=ld('f852sw','verify-fighter-natural-switch-probes.py')
 pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
 boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
 need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),'original native whole giant and afterRET extent changed')
 report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
 obj=compile_one(gen_source(rd,pe,d,by))
 code,refs=rd.object_function(obj,SYM)
 I=[]
 for x in d.disasm(code,0):
  I.append(x)
  if x.mnemonic=='ret':break
 ret=I[-1].address+I[-1].size
 need((ret,len(I),len(refs),len(code)-ret)==(24562,6759,934,901)
      and I[3].op_str=='dword ptr [ebp - 0x10], ecx','actual whole VC7.1 source x86/PE/ABI/901B table drifted')
 dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
 need(dense>0 and sparse>0 and maps>0,'all five real original packed jump tables not checked')
 markers=[j for j,x in enumerate(I) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0x18b')
          and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
 need(len(markers)==1 and markers[0]>=107+61+74+61+95,'following 18A source marker no longer unique')
 k=markers[0]
 section=I[k-107:k]
 new=f834.physical_case(rd,pe,d,code,refs,section,by,0x189,381,11,BAD189,0x18a,f820)
 need(new['native_complete_x86']==107
      and new['original_native_enclosing_parent_JMP_exit_ordinals']==[78,106]
      and all(section[j].op_str==hex(ret-4) for j in (78,106))
      and section[25].mnemonic=='fucompp'
      and section[63].mnemonic=='fadd',
      'native complete 189 original bounce x87/branch or PE fields changed')
 original=list(d.disasm(rd.pe_bytes_at(pe,by[0x189],381),by[0x189]))
 for ordinal,(dst,symbol) in PE_FIELDS.items():
  a,b=original[ordinal],section[ordinal]
  found=[r for r in refs if b.address<=r['offset']<b.address+b.size]
  need(len(found)==1 and found[0]['addend']==0
       and found[0]['local_symbol_offset'] is None
       and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
       and symbol in found[0]['symbol']
       and found[0]['offset']-section[0].address==a.address-by[0x189]+a.size-4
       and a.op_str==(f'0x{dst:x}' if a.mnemonic=='call' else f'dword ptr [0x{dst:x}]'),
       'original 189 physical typed PE field/target x86 ordinal differs '+str(ordinal))
 # Honest original GPR byte mismatches in real preceding 136+186-188.
 prior_shapes=[
   (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
   (0x186,250,74,7,f850.BAD186,0x187),
   (0x187,214,61,6,f850.BAD187,0x188),
   (0x188,214,61,6,f851.WRONG188,0x189),
 ]
 earlier=I[k-107-sum(x[2] for x in prior_shapes):k-107]
 cursor=0;prior=[]
 for a,nb,nx,nf,wrong,nxt in prior_shapes:
  part=earlier[cursor:cursor+nx];cursor+=nx
  prior.append(f834.physical_case(rd,pe,d,code,refs,part,by,a,nb,nf,wrong,nxt,f820))
 need(cursor==len(earlier),'four preceding original ground native cases truncated')
 old_shapes=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
 old=I[k-107-sum(x[2] for x in prior_shapes)-sum(x[2] for x in old_shapes):k-107-sum(x[2] for x in prior_shapes)]
 cursor=0;previous=[]
 for a,nb,nx,nf,wrong,nxt in old_shapes:
  seg=old[cursor:cursor+nx];cursor+=nx
  previous.append(f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,wrong,nxt,f820))
 need(cursor==len(old),'twenty other preceding native cases physically incomplete')
 tail=rd.pe_bytes_at(pe,0x52cb25,46)
 mask=f820.physical_fields(rd,tail,0x52cb25,
           [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
 need(len(mask)==12 and all(tail[j]==code[ret-46+j] for j in range(46) if j not in mask),
      'new 189 full parent expected 34/34 original default nonrelocation machine bytes')
 out={'original_entire_fighter':'0x005214B0',
      'original_native_entire_callable_CODE_B':46755,
      'generated_whole_source_callable_CODE_B':ret,
      'actual_original_189_complete_case':new,
      'original_189_real_PE_field_ordinals':list(PE_FIELDS),
      'native_189_nonrelocation_true_GPR_wrong_B':68,
      'native_189_two_enclosing_giant_JMP_operand_wrong_offsets':[377,378],
      'prior_136_186_187_188_honest_GPR_mismatches_reverified':prior,
      'preceding_20_original_PE_source_cases_rechecked':previous,
      'native_46B_shared_getter_equal_nonrelocation':'34/34',
      'shared_getter_3_actual_PE_calls':3,
      'native_five_packed_901B_afterRET_tables_verified':True,
      'native_original_separate_afterRET_DATA_B':901,
      'whole_original_function_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
 (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
 print('F852 genuine original 189 bounce 381B/107 x86/11 native physical PE fields, original FUCOMPP and bounce scalar, in one 24562B/6759x86 whole parent. 68 true source GPR operand differences plus two original enclosing-giant JMP bytes remain; earlier 136/186-188 PE field mismatches and 20 other cases rechecked, common 46B getter 34/34 plus 3 PE calls, all five 901B tables. Whole 46755B giant NONEXACT.')
if __name__=='__main__':
 try:main()
 except (ValueError,OSError,subprocess.TimeoutExpired) as e:
  print('F852 original bounce189 whole fighter FAILED:',e,file=sys.stderr);raise SystemExit(1)
