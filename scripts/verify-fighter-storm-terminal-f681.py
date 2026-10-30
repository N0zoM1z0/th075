#!/usr/bin/env python3
"""F681: real storm 2F8 source reveals strict native 31B and 31C terminal.

Fresh-build ONE pinned VC7.1 complete selected original fighter giant.
Attest a second legitimate receiver local (-0xC instead of earlier -8)
from the actual complete compiled prologue and EVERY raw receiver access,
then normalize ONLY this saved-this role in comparisons. Reverify all
previous 28 context-strict cases, genuine 186/18A/18B/258 stack
negatives, 2F0/2F1 nonstrict source and 943 afterRET DATA. New actual
31B strict 74-x86/248B/8 authentic REL32; prior 31C stays strict.
The new original 2F8 (252 x86/928B/23 PE fields) stays NONSTRICT:
actual old scratch, loop local, evaluation order and GPR not exact.
Never accept entire 58KB giant or run all 943 cold units.
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
OUT=ROOT/'.analysis/f681-fighter-storm-terminal'
ACTOR=0x00543210
STORM=0x2F8
NEXT_STORM=0x2F9
TERMINAL=0x31B
NEXT_TERMINAL=0x31C
STORM_X86=252
STORM_ORIGINAL_CODE=928
STORM_COMPILED_CODE=904
TERMINAL_X86=74
TERMINAL_ORIGINAL_CODE=248
FIELD_SYMBOLS={
  0x00453E20:'ResetAt453E20',
  0x00453C80:'SpawnAt453C80',
  0x00453D40:'PrepareActionAt453D40',
  0x00455580:'RandomBoundaryAt455580',
  0x00453A70:'SpawnFloatXYAt453A70',
  0x0040FA30:'GetNativeActionAt40FA30',
  0x0040FAC0:'SetNativeActionAt40FAC0',
  0x0040FB40:'SetAuxActionAt40FB40',
  0x0065929C:'g_YPlusAt0065929C',
  0x0065948C:'g_StormYAt0065948C',
  0x006714D0:'g_CloudOpponentAt006714D0',
}
TERMINAL_FIELDS={
  13:(0x00453E20,'ResetAt453E20'),
  15:(0x0040FA30,'GetNativeActionAt40FA30'),
  23:(0x0040FAC0,'SetNativeActionAt40FAC0'),
  34:(0x00454A70,'SubactionAt454A70'),
  36:(0x00452B30,'SubactionAt452B30'),
  39:(0x00453D60,'PrepareActionAt453D60'),
  52:(0x00453A70,'SpawnDirectedAt453A70'),
  72:(0x0040FB40,'SetAuxActionAt40FB40'),
}
STORM_WIDE_DIFFERENCES={39:(4,3),41:(6,4),42:(6,3),
                        68:(6,3),69:(6,3),84:(6,3),85:(6,3),
                       114:(6,3),115:(6,3)}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    s=importlib.util.spec_from_file_location(name,ROOT/path)
    need(s is not None and s.loader is not None,'missing original native verification source '+str(path))
    m=importlib.util.module_from_spec(s);sys.modules[name]=m;s.loader.exec_module(m)
    return m


class _ReceiverRoleInsn:
    """Presentation-only view of one *attested* saved-this source role.

    Original bytes, physical width, COFF fields, and source compiler
    operands remain unchanged. A different original loop local at EBP-8
    is deliberately NOT normalized, nor are any other source EBP slots.
    """
    def __init__(self,actual):
        self.actual=actual

    def __getattr__(self,key):
        return getattr(self.actual,key)

    @property
    def op_str(self):
        actual=self.actual.op_str
        if actual=='dword ptr [ebp - 0xc], ecx':
            return 'dword ptr [ebp - 8], ecx'
        if re.fullmatch(r'(eax|ecx|edx), dword ptr \[ebp - 0xc\]',actual):
            return actual.replace('[ebp - 0xc]','[ebp - 8]')
        return actual


class _ReceiverRoleDecoder:
    def __init__(self,real):
        self.real=real

    def disasm(self,data,address):
        for ins in self.real.disasm(data,address):
            # Only freshly compiled COFF source has address-base zero.
            # Original PE native instructions always keep actual EBP roles.
            yield _ReceiverRoleInsn(ins) if address==0 else ins


def authenticate_real_saved_receiver(real,reader,pe,code):
    native=list(real.disasm(reader.pe_bytes_at(pe,ACTOR,115),ACTOR))
    source=[]
    for x in real.disasm(code,0):
        source.append(x)
        if x.mnemonic=='ret':break
    need(len(native)>5 and len(source)>5
         and native[0].mnemonic==source[0].mnemonic=='push'
         and native[1].mnemonic==source[1].mnemonic=='mov'
         and native[3].mnemonic==source[3].mnemonic=='mov'
         and native[3].op_str=='dword ptr [ebp - 0x44], ecx'
         and source[3].op_str=='dword ptr [ebp - 0xc], ecx',
         'original saved receiver EBP-44 and compiled genuine EBP-C prologue must be attested')
    uses=[x for x in source if '[ebp - 0xc]' in x.op_str]
    accepted={'dword ptr [ebp - 0xc], ecx',
              'eax, dword ptr [ebp - 0xc]',
              'ecx, dword ptr [ebp - 0xc]',
              'edx, dword ptr [ebp - 0xc]'}
    need(uses and {x.op_str for x in uses}==accepted
         and sum(x.op_str=='dword ptr [ebp - 0xc], ecx' for x in uses)==1
         and all(x.mnemonic=='mov' for x in uses),
         'entire compiled parent EBP-C must be exclusively a single real stored this pointer')
    actual_loop=[x for x in source if x.op_str=='dword ptr [ebp - 8], 0']
    need(len(actual_loop)==1,
         '2F8 must use a genuine separate int loop index at EBP-8, not a fake receiver')
    return {'original_real_PE_saved_this_EBP':'-0x44',
            'compiler_real_saved_this_EBP':'-0xC',
            'original_distinct_2F8_integer_loop_local_EBP':'-0x24',
            'compiler_distinct_2F8_integer_loop_local_EBP':'-8',
            'physical_real_this_store_count':1,
            'actual_compiler_this_reload_count':len(uses)-1,
            'presentation_normalization_only_saved_this':True,
            'machine_CODE_bits_changed_by_comparison':0}


def native_cases(reader,pe,real,boss,mapped,f676):
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals={}
    for action,next_,nx,code in ((STORM,NEXT_STORM,STORM_X86,STORM_ORIGINAL_CODE),
                                  (TERMINAL,NEXT_TERMINAL,TERMINAL_X86,TERMINAL_ORIGINAL_CODE)):
        lo,hi=by[action],by[next_]
        native=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        need(boss['address']<lo<hi<boss['address']+boss['size']
             and hi-lo==code and len(native)==nx and sum(x.size for x in native)==code
             and native[0].mnemonic=='mov'
             and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
             f'{action:#x}: original real PE whole native case boundaries/epilogue changed')
        fields=f676.original_fields(native)
        need(len(fields)==(23 if action==STORM else 8),
             f'{action:#x}: original real physical PE target field count changed')
        originals[action]=(native,lo,hi,fields)
    return originals


def add_source(source):
    decl='extern float g_CloudShotYAt006591E4;'
    need(source.count(decl)==1,'original complete selected giant global source lost')
    source=source.replace(decl,decl+'\nextern float g_StormYAt0065948C;')
    for action,path in ((STORM,'FighterStormVolleyF681.inc'),
                        (TERMINAL,'FighterTerminalShotF681.inc')):
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(marker)==1,f'original full selected fighter {action:#x} source marker absent')
        source=source.replace(marker,f'#include "{path}"')
    need(source.count('        case 0x2F9: g_FighterProbeMarker = 762; break;')==1,
         'true following storm native 2F9 original physical handler/source marker missing')
    return source


def check_real_fields(refs,native,gen,fields,symbols,action):
    physical=[f for f in refs if gen[0].address<=f['offset']<gen[-1].address+gen[-1].size]
    need(len(physical)==len(fields),
         f'{action:#x}: all original physical PE/COFF typed fields must be owned')
    for i,target,mn in fields:
        original,compiled=native[i],gen[i]
        if mn=='call':want=f'0x{target:x}'
        elif mn=='movsx':want=f'{original.op_str.split(", ")[0]}, byte ptr [0x{target:x}]'
        else:want=f'dword ptr [0x{target:x}]'
        need(original.mnemonic==compiled.mnemonic==mn and original.op_str==want,
             f'{action:#x} original native PE-targeted x86{i} operation changed')
        physical_field=[f for f in physical if compiled.address<=f['offset']<compiled.address+compiled.size]
        need(len(physical_field)==1 and physical_field[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and physical_field[0]['addend']==0
             and physical_field[0]['local_symbol_offset'] is None
             and symbols[target] in physical_field[0]['symbol'],
             f'{action:#x} real source PE/COFF symbol {target:#x} at x86{i} differs')
    return len(physical)


def verify_storm(source_decoder,code,refs,orig,pos,shared,h,following_native=None,*,
                 source_generated_bytes=STORM_COMPILED_CODE,
                 expected_width_differences=None):
    ins=[]
    for x in source_decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    native,lo,hi,fields=orig[STORM]
    gen=ins[pos:pos+len(native)]
    need(len(gen)==STORM_X86 and gen[-1].mnemonic=='jmp'
         and gen[-1].op_str==shared and sum(x.size for x in gen)==source_generated_bytes,
         'original 2F8 source must represent complete 252-x86 physical case with authenticated source extent')
    fcount=check_real_fields(refs,native,gen,fields,FIELD_SYMBOLS,STORM)
    expected_widths=[(i,*w) for i,w in (STORM_WIDE_DIFFERENCES if expected_width_differences is None
                                     else expected_width_differences).items()]
    widths=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(native,gen)) if a.size!=b.size]
    need(widths==expected_widths,
         f'actual original 2F8 x87 integer-to-float scratch/operand widths changed: {widths}')
    need(native[39].mnemonic=='movsx' and gen[39].mnemonic=='fld'
         and native[42].mnemonic=='fild' and gen[44].mnemonic=='fisub'
         and native[44].mnemonic=='fsubr'
         and native[93].op_str=='dword ptr [ebp - 0x24], 0'
         and gen[93].op_str=='dword ptr [ebp - 8], 0',
         'native 2F8 real nonexact x87 evaluation and loop-local EBP roles must remain negative')
    l,r=h['f598'].normalized(native),h['f598'].normalized(gen)
    absolute_fields={i for i,t,mn in fields if mn!='call'}
    nonfield=[(i,a,b) for i,(a,b) in enumerate(zip(l,r)) if a!=b and i not in absolute_fields]
    need(len(nonfield)>100 and nonfield[0][0]==0,
         'original 2F8 source nonfield GPR/x87 negative unexpectedly eliminated')
    if following_native is None:
        need(ins[pos+len(native)].mnemonic=='mov'
             and ins[pos+len(native)].op_str.endswith(', 0x2fa'),
             'native 2F8 complete source must end at true physical following 2F9 placeholder')
    else:
        need(following_native==0x2F9
             and ins[pos+len(native)].mnemonic=='push'
             and ins[pos+len(native)].op_str=='0xff0000'
             and ins[pos+len(native)+1].mnemonic=='push'
             and ins[pos+len(native)+1].op_str=='4'
             and ins[pos+len(native)+2].mnemonic=='push'
             and ins[pos+len(native)+2].op_str=='3',
             'original complete native 2F9 meaningful storm configuration must immediately follow 2F8')
    return {'real_original_native_action':'0x2F8',
            'original_full_native_start':f'0x{lo:08X}',
            'original_real_next_handler':f'0x{hi:08X}',
            'original_complete_x86_instructions':len(native),
            'original_full_native_inner_CODE_bytes':hi-lo,
            'normal_cpp_generated_inner_CODE_bytes':sum(x.size for x in gen),
            'real_typed_PE_COFF_fields':fcount,
            'actual_mismatching_nonfield_GPR_x87_roles':len(nonfield),
            'real_original_x87_scratch_or_operand_width_mismatches':widths,
            'genuine_original_loop_index_EBP':'-0x24',
            'real_compiler_loop_index_EBP':'-8',
            'strict_original_native_case':False,
            'accepted_new_whole_AUTHORED_function_CODE_bytes':0}


def verify_terminal_31B(source_decoder,code,refs,orig,shared,h,f674):
    ins=[]
    for x in source_decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    start=f674.locate_marker(refs,ins,0x303)
    native,lo,hi,fields=orig[TERMINAL]
    generated=ins[start:start+len(native)]
    need(len(generated)==TERMINAL_X86
         and all(a.size==b.size for a,b in zip(native,generated))
         and generated[-1].mnemonic=='jmp' and generated[-1].op_str==shared
         and generated[-1].address+generated[-1].size-generated[0].address==TERMINAL_ORIGINAL_CODE,
         'original native whole physical 31B 74-instruction/248B geometry or shared exit differs')
    need(native[50].op_str=='0x3e5'
         and native[63].op_str.endswith(', 8')
         and native[70].op_str=='9',
         'true original terminal 31B stage4 kind 3E5 and stage11 short-counter 9 transition changed')
    field_count=check_real_fields(refs,native,generated,fields,
       {target:sym for ordinal,(target,sym) in TERMINAL_FIELDS.items()},TERMINAL)
    need([(i,target) for i,target,mn in fields]==[(i,t) for i,(t,sym) in TERMINAL_FIELDS.items()],
         'real original terminal 31B target field ordinals or call ownership changed')
    lhs,rhs=h['f598'].normalized(native),h['f598'].normalized(generated)
    need(not [(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b],
         '31B original native complete GPR/x87/CFG roles differ in new C++ parent')
    raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(native,generated))
         if a.mnemonic!='call' and not a.mnemonic.startswith('j')
         and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
    need(not raw,
         f'31B original native register-independent saved-this/stack role mismatch {raw[:8]}')
    need(ins[start+len(native)].mnemonic=='mov' and ins[start+len(native)].op_str.endswith(', dword ptr [ebp - 8]'),
         'true physical next native 31C must follow entire original 31B 74-x86 body')
    return {'new_strict_native_case':'0x31B',
            'actual_original_native_physical_start':f'0x{lo:08X}',
            'actual_original_native_next_handler':f'0x{hi:08X}',
            'strict_original_entire_inner_CODE_bytes':hi-lo,
            'entire_original_native_x86':len(native),
            'genuine_zero_addend_original_PE_COFF_fields':field_count,
            'new_accepted_whole_game_FUNCTION_CODE_bytes':0}


def main():
    f651=load('f681_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f681_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f681_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f681_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f681_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f681_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f681_f664','scripts/verify-fighter-special-stage-f664.py')
    f668=load('f681_f668','scripts/verify-fighter-counter-special-f668.py')
    f669=load('f681_f669','scripts/verify-fighter-post-counter-f669.py')
    f671=load('f681_f671','scripts/verify-fighter-four-shot-barrage-f671.py')
    f673=load('f681_f673','scripts/verify-fighter-ground-wave-f673.py')
    f674=load('f681_f674','scripts/verify-fighter-cloud-rain-f674.py')
    f676=load('f681_f676','scripts/verify-fighter-cloud-burst-f676.py')
    h=f651.load_helpers()
    reader=load('f681_reader','scripts/compare-coff-function.py')
    acts=load('f681_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();real=Cs(CS_ARCH_X86,CS_MODE_32)
    decoder=_ReceiverRoleDecoder(real)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    native=native_cases(reader,pe,real,boss,mapped,f676)
    n651={a:f651.true_native(reader,pe,real,boss,by,a) for a in (0xD1,0xD2)}
    n653=f653.native_cases(reader,pe,real,boss,mapped)
    n654=f654.original_native(reader,pe,real,boss,mapped)
    n656=f656.native_cases(reader,pe,real,boss,mapped)
    n657=f657.native_cases(reader,pe,real,boss,mapped)
    n661=f661.true_native(reader,pe,real,boss,mapped)
    n664=f664.original_cases(reader,pe,real,boss,mapped)
    n668=f668.physical_original(reader,pe,real,boss,mapped)
    n669=f669.original_native(reader,pe,real,boss,mapped)
    n671=f671.original_case(reader,pe,real,boss,mapped)
    n673=f673.actual_native(reader,pe,real,boss,mapped)
    n674=f674.original_case(reader,pe,real,boss,mapped)
    terminal=f674.true_terminal(reader,pe,real,boss,mapped)
    n676=f676.original_cases(reader,pe,real,boss,mapped)
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
    source=add_source(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-storm-2F8-and-term-31B.cpp'
    obj=OUT/'Boss00543210-storm-2F8-and-term-31B.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=200)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'genuine pinned VC7.1 selected entire fighter compile failed: '+cp.stderr[-550:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    receiver=authenticate_real_saved_receiver(real,reader,pe,code)
    old=f651.verify_full(reader,pe,decoder,boss,report,mapped,code,refs,n651,h,following_native=0x12C)
    strict653,idx=f653.verify_new(reader,pe,decoder,code,refs,old,n653,h,following_native=0x12F)
    strict654,idx=f654.verify_new(reader,pe,decoder,code,refs,n654,old,idx,h,following_native=0x131)
    strict656,idx=f656.verify_native(reader,pe,decoder,code,refs,n656,old,idx,h,following_native=0x186)
    strict657,negative186,idx=f657.verify_new(reader,pe,decoder,code,refs,n657,old,idx,h,
                                                following_native=0x18A,source_scratch_slot='0x24')
    negative661=f661.verify_nonstrict(reader,pe,decoder,code,refs,n661,old,idx,h,source_scratch_shift=4)
    strict664,idx=f664.verify_new_code(reader,pe,decoder,code,refs,boss,mapped,n664,h,following_native=0x252)
    body=[]
    for x in decoder.disasm(code,0):
        body.append(x)
        if x.mnemonic=='ret':break
    shared=body[old['continuation_source_ordinal']-1].op_str
    strict668,idx=f668.verify_inner(reader,pe,decoder,code,refs,n668,idx,shared,h,following_native=0x255)
    strict669,idx=f669.verify_native(reader,pe,decoder,code,refs,n669,idx,shared,h,following_native=0x258)
    negative671=f671.verify_negative(reader,pe,decoder,code,refs,n671,idx,shared,h,source_scratch_shift=4)
    strict673=f673.verify_groundwave(reader,decoder,code,refs,n673,shared,h)
    strict674,strict31C,next_ordinal=f674.verify_native(reader,decoder,code,refs,n674,terminal,shared,h,
                following_native=0x2F0,terminal_expect_strict=True,terminal_preceding_native=0x31B)
    negative676,storm_ordinal=f676.verify_negative(reader,decoder,code,refs,n676,next_ordinal,shared,h,following_native=0x2F8)
    storm_negative=verify_storm(decoder,code,refs,native,storm_ordinal,shared,h)
    strict31B=verify_terminal_31B(decoder,code,refs,native,shared,h,f674)
    need(strict31C['strict_original_native_case']
         and (len(strict653),len(strict654),len(strict656),len(strict657),
              len(strict664),len(strict668),len(strict669))==(3,2,5,3,2,3,3),
         'all 27 preceding strict native cases and original 31C must remain valid')
    receipt={'original_whole_selected_fighter_parent':'0x00543210',
             'entire_original_parent_CODE_bytes_still_NONEXACT':boss['size'],
             'original_separately_owned_afterRET_switch_DATA_bytes':boss['postret_size'],
             'independent_native_prologue_receiver_role_and_distinct_true_loop_local':receiver,
             'all_previous_28_context_strict_original_cases_checked_same_parent':True,
             'original_186_18A_18B_258_negative_EBP_scratch_cases_reverified':True,
             'original_complete_after_RET_switch_DATA_reverified':True,
             'source_backed_but_NONSTRICT_full_2F8_storm_loop_case':storm_negative,
             'new_strict_actual_original_terminal_31B_case':strict31B,
             'previous_context_strict_terminal_31C_reverified':strict31C,
             'new_strict_original_inner_case_count':1,
             'new_strict_original_internal_CODE_bytes':TERMINAL_ORIGINAL_CODE,
             'accepted_new_whole_authored_game_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F681 selected complete original fighter 00543210: new strictly source-backed '
          'terminal 31B (74 real x86/248 original inner CODE B/8 genuine typed COFF fields), '
          'with previously strict 31C (63/219 B/7 fields) in the SAME whole parent. '
          'Actual 2F8 native storm (252 original x86/928 original B/23 PE/COFF fields) '
          'remains NONSTRICT (904 compiler B, real loop/scratch/x87/GPR mismatches). '
          'Original saved this at EBP-44 versus independently authenticated C++ '
          'saved this EBP-C is normalized by role alone; real index EBP-8 and '
          'all scratch locals are NOT masked. All previous 28 contextual strict '
          'native cases, old genuine EBP negatives and full independent '
          'afterRET switch DATA rechecked in SAME freshly compiled entire parent. '
          'No whole-giant authored credit or full 943-unit cold replay.')


if __name__=='__main__':
    main()
