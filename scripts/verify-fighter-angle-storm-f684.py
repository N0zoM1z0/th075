#!/usr/bin/env python3
"""F684: full 381-x86 native 2F9 angle/volley source is genuinely NONSTRICT.

Cold-compile just ONE selected whole 00543210 original-shaped giant.
Recheck 27 preceding contextual strict inner cases, original real
186/18A/18B/258/2F8 EBP negatives, full afterRET switch DATA,
all actual original native 2F9 381 x86 /1367 CODE B /34 typed fields.
Source emits 1319B, with 16 original 6-byte x87 scratch instructions
at different EBP positions and real GPR/evaluation order differences.
Actual terminal 31B/31C GPR roles regress when true 2F9 source is
inserted; never merge strict results across distinct parent contexts.
No whole fighter function acceptance or 943-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f684-fighter-angle-storm'
ACTOR=0x00543210
ACTION=0x2F9
NEXT=0x2FA
ORIGINAL_X86=381
ORIGINAL_CODE=1367
GENERATED_CODE=1319
ORIGINAL_FIELDS=34
SLOTS={
    78:('0x1d8','0x58'),79:('0x1d8','0x58'),
    94:('0x1dc','0x5c'),95:('0x1dc','0x5c'),
   124:('0x1e0','0x60'),125:('0x1e0','0x60'),
   151:('0x1e4','0x64'),152:('0x1e4','0x64'),
   167:('0x1e8','0x68'),168:('0x1e8','0x68'),
   197:('0x1ec','0x6c'),198:('0x1ec','0x6c'),
   273:('0x1f0','0x70'),274:('0x1f0','0x70'),
   330:('0x1f4','0x74'),331:('0x1f4','0x74'),
}
REORDERED_FLOAT_EVALUATIONS=(268,269,279,280,325,326,336,337)
PE_TARGETS={
    0x00454BC0:'ConfigureStormAt454BC0',
    0x00453E20:'ResetAt453E20',
    0x0040FB40:'SetAuxActionAt40FB40',
    0x00453D40:'PrepareActionAt453D40',
    0x00453A70:'SpawnFloatXYAt453A70',
    0x0040FA30:'GetNativeActionAt40FA30',
    0x0040FAC0:'SetNativeActionAt40FAC0',
    0x00455580:'RandomBoundaryAt455580',
    0x00483300:'CalculateAngleAt483300',
    0x006406AC:'__ftol2',
    0x0065782C:'g_ThresholdAt0065782C',
    0x00659A18:'g_StormAngleShotYAt00659A18',
    0x006714D0:'g_CloudOpponentAt006714D0',
    0x00658348:'g_StormMotionAt00658348',
    0x00657828:'g_StormAngleDenominatorAt00657828',
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing original source '+str(path))
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod;spec.loader.exec_module(mod)
    return mod


class _OriginalThisRoleInsn:
    """ONLY authenticated source EBP-14 saved-this MOV, no instruction patch."""
    def __init__(self,x):self.real=x
    def __getattr__(self,name):return getattr(self.real,name)
    @property
    def op_str(self):
        s=self.real.op_str
        if s=='dword ptr [ebp - 0x14], ecx':return 'dword ptr [ebp - 8], ecx'
        if re.fullmatch(r'(eax|ecx|edx), dword ptr \[ebp - 0x14\]',s):
            return s.replace('[ebp - 0x14]','[ebp - 8]')
        return s


class _SourceRoleDecoder:
    def __init__(self,real):self.real=real
    def disasm(self,code,address):
        for ins in self.real.disasm(code,address):
            yield _OriginalThisRoleInsn(ins) if address==0 else ins


def original_2f9(reader,pe,real,boss,mapped,f676):
    by={m['action']:int(m['handler'],16) for m in mapped}
    lo,hi=by[ACTION],by[NEXT]
    native=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
    need(boss['address']<lo<hi<boss['address']+boss['size']
         and hi-lo==ORIGINAL_CODE and len(native)==ORIGINAL_X86
         and sum(x.size for x in native)==ORIGINAL_CODE
         and native[0].op_str=='0xff0000'
         and native[1].op_str=='4' and native[2].op_str=='3'
         and native[4].mnemonic=='call' and native[4].op_str=='0x454bc0'
         and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
         'genuine entire original native 2F9 1367-byte PE bounds/storm/exit changed')
    need(native[103].op_str=='dword ptr [ebp - 0x28], 0'
         and native[176].op_str=='dword ptr [ebp - 0x2c], 0'
         and native[284].op_str==native[341].op_str=='0x483300'
         and native[287].op_str==native[344].op_str=='0x6406ac'
         and native[286].op_str==native[343].op_str=='dword ptr [0x657828]'
         and native[100].op_str==native[173].op_str=='0x391'
         and native[130].op_str==native[203].op_str=='0x392',
         'genuine original 2F9 two-loop shots, native x87 angle/float conversion and physical loop indices changed')
    fields=f676.original_fields(native)
    need(len(fields)==ORIGINAL_FIELDS and all(target in PE_TARGETS for i,target,mn in fields),
         'actual original whole native 2F9 PE/COFF relocation count/targets changed')
    return native,lo,hi,fields


def add_2f9_source(source):
    decl='void SubactionAt454A70(int);'
    need(source.count(decl)==1,'genuine original selected parent subaction method declaration missing')
    source=source.replace(decl,decl+' void ConfigureStormAt454BC0(int,int,int);')
    decl='extern float g_CloudShotYAt006591E4;'
    need(source.count(decl)==1,'native selected full parent original global declaration missing')
    source=source.replace(decl,decl+('\nextern float g_StormAngleShotYAt00659A18;'
                                     '\nextern float g_StormMotionAt00658348;'
                                     '\nextern float g_StormAngleDenominatorAt00657828;'
                                     '\nextern "C" float __cdecl CalculateAngleAt483300(float,float);'))
    marker='        case 0x2F9: g_FighterProbeMarker = 762; break;'
    need(source.count(marker)==1,'authentic physical action2F9 source marker missing')
    source=source.replace(marker,'#include "FighterAngleStormF684.inc"')
    need(source.count('        case 0x2FA: g_FighterProbeMarker = 763; break;')==1,
         'genuine next physical native action2FA original marker missing')
    return source


def authenticate_saved_this(real,reader,pe,code):
    orig=list(real.disasm(reader.pe_bytes_at(pe,ACTOR,100),ACTOR))
    ins=[]
    for x in real.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(len(ins)>5 and len(orig)>5
         and orig[3].op_str=='dword ptr [ebp - 0x44], ecx'
         and ins[3].op_str=='dword ptr [ebp - 0x14], ecx'
         and ins[3].mnemonic=='mov',
         'actual entire original/source saved receiver role not validated')
    uses=[x for x in ins if '[ebp - 0x14]' in x.op_str]
    allowed={'dword ptr [ebp - 0x14], ecx',
             'eax, dword ptr [ebp - 0x14]',
             'ecx, dword ptr [ebp - 0x14]',
             'edx, dword ptr [ebp - 0x14]'}
    need(uses and {x.op_str for x in uses}==allowed
         and sum(x.op_str=='dword ptr [ebp - 0x14], ecx' for x in uses)==1
         and all(x.mnemonic=='mov' for x in uses),
         'original compiler source EBP-14 used for nonreceiver local; cannot normalize')
    return {'original_real_PE_saved_receiver':'EBP-0x44',
            'compiler_real_full_parent_saved_receiver':'EBP-0x14',
            'genuine_authentic_saved_this_store_count':1,
            'compiled_saved_this_reload_count':len(uses)-1,
            'real_2F8_integer_loop_source_EBP':'-8',
            'real_2F9_two_integer_loops_source_EBP':['-0xC','-0x10'],
            'source_receiver_role_only_presentation':True,
            'machine_code_bytes_patched':0}


def verify_negative(source_decoder,original,code,refs,start,shared,h,*,
                    following_native_2fa=False, expected_compiled_size=GENERATED_CODE,
                    expected_wide_ordinals=None):
    ins=[]
    for x in source_decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    native,lo,hi,fields=original
    gen=ins[start:start+len(native)]
    need(len(gen)==ORIGINAL_X86 and sum(x.size for x in gen)==expected_compiled_size
         and gen[0].mnemonic=='push' and gen[0].op_str=='0xff0000'
         and gen[-1].mnemonic=='jmp' and gen[-1].op_str==shared,
         'actual full 2F9 381 native x86 source structure or shared original exit changed')
    physical=[f for f in refs if gen[0].address<=f['offset']<gen[-1].address+gen[-1].size]
    need(len(physical)==len(fields)==ORIGINAL_FIELDS,
         'actual all 34 true PE/COFF fields must be physically owned inside 2F9')
    for ordinal,target,mn in fields:
        native_i,generated_i=native[ordinal],gen[ordinal]
        if mn=='call':want=f'0x{target:x}'
        elif mn=='movsx':want=f'{native_i.op_str.split(", ")[0]}, byte ptr [0x{target:x}]'
        else:want=f'dword ptr [0x{target:x}]'
        need(native_i.mnemonic==generated_i.mnemonic==mn and native_i.op_str==want,
             f'2F9 native x86{ordinal}: original PE-targeted instruction/target changed')
        actual=[f for f in physical if generated_i.address<=f['offset']<generated_i.address+generated_i.size]
        need(len(actual)==1 and actual[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and actual[0]['addend']==0 and actual[0]['local_symbol_offset'] is None
             and PE_TARGETS[target] in actual[0]['symbol'],
             f'2F9 original PE/COFF authentic zero-addend typed field missing at x86{ordinal}')
    wide=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,gen)) if a.size!=b.size]
    need(wide==[(i,6,3) for i in (SLOTS if expected_wide_ordinals is None else expected_wide_ordinals)],
         f'actual native 2F9 sixteen original EBP scratch width mismatches changed: {wide}')
    raw=[]
    for i,(a,b) in enumerate(zip(native,gen)):
        if i in SLOTS:
            old,new=SLOTS[i]
            need(f'[ebp - {old}]' in a.op_str
                 and f'[ebp - {new}]' in b.op_str,
                 f'2F9 original x87 floating integer conversion local at x86{i} no longer accurately tracked')
            raw.append(i)
    need(raw==list(SLOTS), '2F9 native EBP scratch negative ordinals changed')
    need(native[103].op_str=='dword ptr [ebp - 0x28], 0'
         and native[176].op_str=='dword ptr [ebp - 0x2c], 0'
         and gen[103].op_str=='dword ptr [ebp - 0xc], 0'
         and gen[176].op_str=='dword ptr [ebp - 0x10], 0',
         'real original/source two meaningful storm loop-index locals were masked or displaced')
    wrong_mn=[i for i,(a,b) in enumerate(zip(native,gen)) if a.mnemonic!=b.mnemonic]
    need(wrong_mn==list(REORDERED_FLOAT_EVALUATIONS),
         f'actual four native angle x87 operand expression reorder patterns changed {wrong_mn}')
    lhs,rhs=h['f598'].normalized(native),h['f598'].normalized(gen)
    absolute_fields={i for i,target,mn in fields if mn!='call'}
    wrong=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b and i not in absolute_fields]
    need(len(wrong)==236 and wrong[0][0]==5,
         f'2F9 has genuine nonfield GPR/x87 phase differences; never promote to strict: {len(wrong)} {wrong[:5]}')
    if following_native_2fa:
        # Real F699 source now follows 2F9, rather than a placeholder.
        # The entire native 2FA begins with a genuine saved-this reload.
        need(ins[start+ORIGINAL_X86].mnemonic=='mov'
             and ins[start+ORIGINAL_X86].op_str=='edx, dword ptr [ebp - 8]',
             'whole original native 2F9 must lead directly into the real source-backed 2FA handler')
    else:
        need(ins[start+ORIGINAL_X86].mnemonic=='mov'
             and ins[start+ORIGINAL_X86].op_str.endswith(', 0x2fb'),
             'whole original native 2F9 must end at genuine following 2FA source marker')
    return {'actual_original_native_action':'0x2F9',
            'original_entire_PE_case_start':f'0x{lo:08X}',
            'original_physical_next_native_handler':f'0x{hi:08X}',
            'entire_original_native_x86':len(native),
            'original_full_native_inner_CODE_bytes':hi-lo,
            'compiler_generated_real_CPP_inner_CODE_bytes':expected_compiled_size,
            'all_physical_original_typed_PE_COFF_fields':len(physical),
            'native_original_wrong_wide_EBP_scratch_ordinals':list(SLOTS),
            'actual_native_four_float_order_mismatch_ordinals':wrong_mn,
            'actual_nonfield_native_register_x87_differences':len(wrong),
            'two_original_real_native_loop_locals':['EBP-0x28','EBP-0x2C'],
            'source_real_compiled_loop_locals':['EBP-0xC','EBP-0x10'],
            'strict_original_native_inner_case':False,
            'accepted_game_authored_whole_FUNCTION_CODE_bytes':0}


def verify_terminal_negative(source_decoder,code,refs,originals,shared,h,f681,f674,*,
                             source_native_302_end_ordinal=None):
 ins=[]
 for x in source_decoder.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 first=(f674.locate_marker(refs,ins,0x303)
        if source_native_302_end_ordinal is None
        else source_native_302_end_ordinal)
 if source_native_302_end_ordinal is not None:
  need(0<first<len(ins)-74 and ins[first].mnemonic=='mov'
       and ins[first].op_str.endswith(', dword ptr [ebp - 8]'),
       'genuine newly restored 302 source does not lead to native 31B')
 native,lo,hi,fields=originals[0x31B]
 gen=ins[first:first+len(native)]
 need(len(gen)==74 and all(a.size==b.size for a,b in zip(native,gen))
      and gen[-1].mnemonic=='jmp' and gen[-1].op_str==shared,
      'original complete native terminal 31B source still physically whole')
 count=f681.check_real_fields(refs,native,gen,fields,
     {target:sym for i,(target,sym) in f681.TERMINAL_FIELDS.items()},0x31B)
 lhs,rhs=h['f598'].normalized(native),h['f598'].normalized(gen)
 wrong=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b]
 need(len(wrong)==43 and wrong[0][0]==0,
      f'original 31B phase regression from true upstream 2F9 source was not exactly observed: {len(wrong)}')
 return {'original_native_action':'0x31B',
         'full_original_native_x86':len(native),
         'original_true_inner_CODE_bytes':hi-lo,
         'genuine_PE_COFF_typed_fields':count,
         'source_context_genuine_GPR_mismatch_count':len(wrong),
         'strict_original_case_in_this_parent':False}


def main():
 f651=load('f684_f651','scripts/verify-fighter-resource-shots-f651.py')
 f653=load('f684_f653','scripts/verify-fighter-falling-recovery-f653.py')
 f654=load('f684_f654','scripts/verify-fighter-falling-finish-f654.py')
 f656=load('f684_f656','scripts/verify-fighter-late-stages-f656.py')
 f657=load('f684_f657','scripts/verify-fighter-motion-continuation-f657.py')
 f661=load('f684_f661','scripts/verify-fighter-motion-shots-f661.py')
 f664=load('f684_f664','scripts/verify-fighter-special-stage-f664.py')
 f668=load('f684_f668','scripts/verify-fighter-counter-special-f668.py')
 f669=load('f684_f669','scripts/verify-fighter-post-counter-f669.py')
 f671=load('f684_f671','scripts/verify-fighter-four-shot-barrage-f671.py')
 f673=load('f684_f673','scripts/verify-fighter-ground-wave-f673.py')
 f674=load('f684_f674','scripts/verify-fighter-cloud-rain-f674.py')
 f676=load('f684_f676','scripts/verify-fighter-cloud-burst-f676.py')
 f681=load('f684_f681','scripts/verify-fighter-storm-terminal-f681.py')
 h=f651.load_helpers();reader=load('f684_reader','scripts/compare-coff-function.py')
 acts=load('f684_acts','scripts/report-fighter-action-handlers.py')
 pe=reader.verified_target();real=Cs(CS_ARCH_X86,CS_MODE_32);decoder=_SourceRoleDecoder(real)
 boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
 report,mapped=acts.report_boss(reader,pe,real,boss)
 by={x['action']:int(x['handler'],16) for x in mapped}
 target=original_2f9(reader,pe,real,boss,mapped,f676)
 native31B=f681.native_cases(reader,pe,real,boss,mapped,f676)
 native651={a:f651.true_native(reader,pe,real,boss,by,a) for a in (0xD1,0xD2)}
 native653=f653.native_cases(reader,pe,real,boss,mapped)
 native654=f654.original_native(reader,pe,real,boss,mapped)
 native656=f656.native_cases(reader,pe,real,boss,mapped)
 native657=f657.native_cases(reader,pe,real,boss,mapped)
 native661=f661.true_native(reader,pe,real,boss,mapped)
 native664=f664.original_cases(reader,pe,real,boss,mapped)
 native668=f668.physical_original(reader,pe,real,boss,mapped)
 native669=f669.original_native(reader,pe,real,boss,mapped)
 native671=f671.original_case(reader,pe,real,boss,mapped)
 native673=f673.actual_native(reader,pe,real,boss,mapped)
 native674=f674.original_case(reader,pe,real,boss,mapped)
 nativeTerminal=f674.true_terminal(reader,pe,real,boss,mapped)
 native676=f676.original_cases(reader,pe,real,boss,mapped)
 source=f651.source_with_d1_d2(reader,pe,real,boss,report,mapped,h)
 source=f653.replace_following_cases(source)
 source=f654.source_with_finish(source)
 source=f656.source_with_native_stages(source)
 source=f657.source_with_stage_186_189(source)
 source=f661.parent_source(source)
 source=f664.source_with_cases(source)
 source=f668.source_with_special(source)
 source=f669.add_native_cases(source)
 source=f671.source_with_barrage(source)
 source=f673.source_with_groundwave(source)
 source=f674.source_with_rain_and_terminal(source)
 source=f676.source_with_burst(source)
 source=f681.add_source(source)
 source=add_2f9_source(source)
 OUT.mkdir(parents=True,exist_ok=True)
 cpp=OUT/'Boss00543210-entire-2F9-angle-source.cpp'
 obj=OUT/'Boss00543210-entire-2F9-angle-source.obj'
 cpp.write_text(source)
 env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
 env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
 env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
 cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=ROOT,env=env,capture_output=True,text=True,timeout=200)
 (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
 need(cp.returncode==0,'selected original complete giant VC7.1 native C++ compile failed: '+cp.stderr[-550:])
 code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
 receiver=authenticate_saved_this(real,reader,pe,code)
 old=f651.verify_full(reader,pe,decoder,boss,report,mapped,code,refs,native651,h,following_native=0x12C)
 proof653,idx=f653.verify_new(reader,pe,decoder,code,refs,old,native653,h,following_native=0x12F)
 proof654,idx=f654.verify_new(reader,pe,decoder,code,refs,native654,old,idx,h,following_native=0x131)
 proof656,idx=f656.verify_native(reader,pe,decoder,code,refs,native656,old,idx,h,following_native=0x186)
 proof657,neg186,idx=f657.verify_new(reader,pe,decoder,code,refs,native657,old,idx,h,
                                    following_native=0x18A,source_scratch_slot='0x2c')
 neg661=f661.verify_nonstrict(reader,pe,decoder,code,refs,native661,old,idx,h,source_scratch_shift=12)
 proof664,idx=f664.verify_new_code(reader,pe,decoder,code,refs,boss,mapped,native664,h,following_native=0x252)
 ins=[]
 for x in decoder.disasm(code,0):
  ins.append(x)
  if x.mnemonic=='ret':break
 shared=ins[old['continuation_source_ordinal']-1].op_str
 proof668,idx=f668.verify_inner(reader,pe,decoder,code,refs,native668,idx,shared,h,following_native=0x255)
 proof669,idx=f669.verify_native(reader,pe,decoder,code,refs,native669,idx,shared,h,following_native=0x258)
 neg671=f671.verify_negative(reader,pe,decoder,code,refs,native671,idx,shared,h,source_scratch_shift=12)
 proof673=f673.verify_groundwave(reader,decoder,code,refs,native673,shared,h)
 strict2EF,negativeTerminal,idx=f674.verify_native(reader,decoder,code,refs,native674,nativeTerminal,shared,h,
                 following_native=0x2F0,terminal_expect_strict=False,terminal_preceding_native=0x31B)
 neg676,idx=f676.verify_negative(reader,decoder,code,refs,native676,idx,shared,h,following_native=0x2F8)
 neg2F8=f681.verify_storm(decoder,code,refs,native31B,idx,shared,h,following_native=0x2F9)
 proof=verify_negative(decoder,target,code,refs,idx+252,shared,h)
 neg31B=verify_terminal_negative(decoder,code,refs,native31B,shared,h,f681,f674)
 need((len(proof653),len(proof654),len(proof656),len(proof657),
       len(proof664),len(proof668),len(proof669))==(3,2,5,3,2,3,3),
       'all previous 27 native strict original cases before terminal not preserved')
 receipt={'selected_original_whole_fighter':'0x00543210',
          'original_entire_parent_CODE_bytes_still_NONEXACT':boss['size'],
          'original_separate_owned_afterRET_switch_DATA_bytes':boss['postret_size'],
          'physically_authenticated_original_and_compiler_saved_this':receiver,
          'original_prior_27_nonterminal_context_strict_case_bodies_reverified':True,
          'authentic_prior_original_186_18A_18B_258_2F8_nonexact_controls_reverified':True,
          'complete_original_943_byte_afterRET_switch_DATA_verified_in_same_parent':True,
          'new_source_backed_but_NONSTRICT_entire_native_2F9_case':proof,
          'formerly_strict_terminal_31B_now_real_nonfield_GPR_negative':neg31B,
          'formerly_strict_terminal_31C_now_real_nonfield_GPR_negative':negativeTerminal,
          'new_context_strict_native_case_count':0,
          'new_accepted_whole_authored_game_FUNCTION_CODE_bytes':0}
 (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
 print('F684 complete selected giant 00543210: original entire action 2F9 '
       '381 authentic x86, 1367 full native CODE B, 34 true PE/COFF typed source fields; '
       'natural VC7.1 C++ emits 381 x86/1319B. Original 16 real wide EBP '
       'scratch instructions differ, 8 original float load/mov ordering phases '
       'remain, and 236 genuine nonfield GPR/x87 roles mismatch: NONSTRICT. '
       'All 27 earlier nonterminal contextual strict native cases, real EBP '
       'negatives and entire afterRET original switch DATA rechecked in SAME '
       'new compiled parent; terminal 31B/31C now both genuine GPR negative '
       '(43/36) due to true upstream source/context. No false exact whole function '
       'credit or 943-unit full replay.')


if __name__=='__main__':
 main()
