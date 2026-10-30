#!/usr/bin/env python3
"""F696: prove the real 2FB native action in a freshly built *whole* boss TU.

The authored 00543210 parent and its 647-byte internal action remain
NONEXACT. Reconstruct and validate the complete 181-instruction action,
all 17 original physical PE/COFF fields and honest stack/GPR negatives.
Never accept the action as an independent function or mask EBP differences.
This compiles exactly one selected giant, not the 943-unit registry.
"""
from __future__ import annotations
import importlib.util
import json
import os
import re
from pathlib import Path
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / '.analysis/f696-fighter-grounded-volley'
ACTOR = 0x00543210
START = 0x2FB
NEXT = 0x302
ORIGINAL_SIZE = 647
ORIGINAL_X86 = 181
GENERATED_SIZE = 635
ORIGINAL_FIELD_ORDINALS = (4, 39, 45, 49, 61, 80, 82, 91, 105,
                           111, 121, 135, 138, 146, 157, 163, 179)
WIDTH_NEGATIVES = {69:(6,3,'0x1fc','0x7c'), 70:(6,3,'0x1fc','0x7c'),
                   97:(6,3,'0x200','0x80'), 98:(6,3,'0x200','0x80')}
OPCODE_REORDERS = {64:('mov','fld'),65:('fld','mov'),
                   75:('mov','fld'),76:('fld','mov')}
EXPECTED_SYMBOLS = {
    0x00454BC0:'ConfigureStormAt454BC0',
    0x00453D40:'PrepareActionAt453D40',
    0x00453E20:'ResetAt453E20',
    0x0040FB40:'SetAuxActionAt40FB40',
    0x00483300:'CalculateAngleAt483300',
    0x00453A70:'SpawnFloatXYAt453A70',
    0x0040FA30:'GetNativeActionAt40FA30',
    0x0040FAC0:'SetNativeActionAt40FAC0',
    0x0065782C:'g_ThresholdAt0065782C',
    0x00657828:'g_StormAngleDenominatorAt00657828',
    0x00659A18:'g_StormAngleShotYAt00659A18',
    0x0065948C:'g_StormYAt0065948C',
    0x006714D0:'g_CloudOpponentAt006714D0',
}


def need(ok, message):
    if not ok:
        raise ValueError(message)


def load(name, relative):
    spec = importlib.util.spec_from_file_location(name, ROOT / relative)
    need(spec is not None and spec.loader is not None, str(relative))
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def source_for_entire_parent(reader, pe, decoder, boss, report, mapped):
    """Rebuild the full selected source context from tracked F651–F684 inputs."""
    deps = [(n, f'scripts/verify-fighter-{slug}.py') for n,slug in [
        ('f651','resource-shots-f651'), ('f653','falling-recovery-f653'),
        ('f654','falling-finish-f654'),('f656','late-stages-f656'),
        ('f657','motion-continuation-f657'),('f661','motion-shots-f661'),
        ('f664','special-stage-f664'),('f668','counter-special-f668'),
        ('f669','post-counter-f669'),('f671','four-shot-barrage-f671'),
        ('f673','ground-wave-f673'),('f674','cloud-rain-f674'),
        ('f676','cloud-burst-f676'),('f681','storm-terminal-f681')]]
    m={n:load('f696_'+n,p) for n,p in deps}
    prior=m['f651'].load_helpers()
    src=m['f651'].source_with_d1_d2(reader,pe,decoder,boss,report,mapped,prior)
    for name,method in [('f653','replace_following_cases'),
                        ('f654','source_with_finish'),
                        ('f656','source_with_native_stages'),
                        ('f657','source_with_stage_186_189'),
                        ('f661','parent_source'),
                        ('f664','source_with_cases'),
                        ('f668','source_with_special'),
                        ('f669','add_native_cases'),
                        ('f671','source_with_barrage'),
                        ('f673','source_with_groundwave'),
                        ('f674','source_with_rain_and_terminal'),
                        ('f676','source_with_burst'),
                        ('f681','add_source')]:
        src=getattr(m[name],method)(src)
    f684=load('f696_f684','scripts/verify-fighter-angle-storm-f684.py')
    src=f684.add_2f9_source(src)
    marker='        case 0x2FB: g_FighterProbeMarker = 764; break;'
    need(src.count(marker)==1, 'native physical 2FB case absent from full switch TU')
    src=src.replace(marker,'#include "FighterGroundedVolleyF696.inc"')
    need(src.count('        case 0x302: g_FighterProbeMarker = 771; break;')==1,
         'next true 302 physical original case/placeholder absent')
    return src,m,prior



class _SavedReceiverInsn:
    """Comparison view of the independently attested compiler *this* slot.

    No native bytes or other EBP locals are changed; this is not a claim
    of original stack layout equivalence.
    """
    def __init__(self, original, source_receiver_slot):
        self.original=original
        self.source_receiver_slot=source_receiver_slot

    def __getattr__(self, key):
        return getattr(self.original,key)

    @property
    def op_str(self):
        raw=self.original.op_str
        if self.original.mnemonic!='mov':return raw
        slot=f'[ebp - {self.source_receiver_slot}]'
        if raw==f'dword ptr {slot}, ecx':return 'dword ptr [ebp - 8], ecx'
        if re.fullmatch(rf'(eax|ecx|edx), dword ptr \[ebp - {self.source_receiver_slot}\]',raw):
            return raw.replace(slot,'[ebp - 8]')
        return raw


class _SavedReceiverDecoder:
    def __init__(self, decoder, source_receiver_slot):
        self.decoder=decoder
        self.source_receiver_slot=source_receiver_slot

    def disasm(self, code, address):
        for insn in self.decoder.disasm(code,address):
            yield _SavedReceiverInsn(insn,self.source_receiver_slot) if address==0 else insn


def verify_prior_parent_context(reader,pe,real,boss,report,mapped,code,refs,m,h,*,
                                expected_receiver_uses=2393, following_native_2fa=False,
                                source_receiver_slot='0x18', source_scratch_slot='0x30',
                                source_scratch_shift=16, source_f684_slot_shift=4,
                                source_native_302_end_ordinal=None,
                                source_2f9_expected_size=1319,
                                source_2f9_wide_ordinals=None):
    """Recheck the *same* newly compiled complete parent and after-RET DATA.

    The authentic native frame slot is EBP-44. Only source `this` MOVs
    proven by the actual whole-parent prologue can be presented as the
    older verifiers' saved receiver; real scratch locals are untouched.
    """
    ins=[]
    for x in real.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    original_prologue=list(real.disasm(reader.pe_bytes_at(pe,ACTOR,32),ACTOR))
    slot=f'[ebp - {source_receiver_slot}]'
    uses=[x for x in ins if slot in x.op_str]
    allowed={f'dword ptr {slot}, ecx',
             f'eax, dword ptr {slot}',
             f'ecx, dword ptr {slot}',
             f'edx, dword ptr {slot}'}
    need(len(uses)==expected_receiver_uses and {x.op_str for x in uses}==allowed
         and sum(x.op_str==f'dword ptr {slot}, ecx' for x in uses)==1
         and all(x.mnemonic=='mov' for x in uses)
         and ins[3].op_str==f'dword ptr {slot}, ecx'
         and original_prologue[3].op_str=='dword ptr [ebp - 0x44], ecx',
         'actual original and new compiled whole-parent `this` owner not independently attested')
    decoder=_SavedReceiverDecoder(real,source_receiver_slot)
    by={x['action']:int(x['handler'],16) for x in mapped}
    n651={a:m['f651'].true_native(reader,pe,real,boss,by,a) for a in (0xD1,0xD2)}
    old=m['f651'].verify_full(reader,pe,decoder,boss,report,mapped,code,refs,n651,h,
                               following_native=0x12C)
    n653=m['f653'].native_cases(reader,pe,real,boss,mapped)
    p653,idx=m['f653'].verify_new(reader,pe,decoder,code,refs,old,n653,h,following_native=0x12F)
    n654=m['f654'].original_native(reader,pe,real,boss,mapped)
    p654,idx=m['f654'].verify_new(reader,pe,decoder,code,refs,n654,old,idx,h,following_native=0x131)
    n656=m['f656'].native_cases(reader,pe,real,boss,mapped)
    p656,idx=m['f656'].verify_native(reader,pe,decoder,code,refs,n656,old,idx,h,following_native=0x186)
    n657=m['f657'].native_cases(reader,pe,real,boss,mapped)
    p657,negative186,idx=m['f657'].verify_new(reader,pe,decoder,code,refs,n657,old,idx,h,
                                    following_native=0x18A,source_scratch_slot=source_scratch_slot)
    n661=m['f661'].true_native(reader,pe,real,boss,mapped)
    m['f661'].verify_nonstrict(reader,pe,decoder,code,refs,n661,old,idx,h,source_scratch_shift=source_scratch_shift)
    n664=m['f664'].original_cases(reader,pe,real,boss,mapped)
    p664,idx=m['f664'].verify_new_code(reader,pe,decoder,code,refs,boss,mapped,n664,h,following_native=0x252)
    shared=ins[old['continuation_source_ordinal']-1].op_str
    n668=m['f668'].physical_original(reader,pe,real,boss,mapped)
    p668,idx=m['f668'].verify_inner(reader,pe,decoder,code,refs,n668,idx,shared,h,following_native=0x255)
    n669=m['f669'].original_native(reader,pe,real,boss,mapped)
    p669,idx=m['f669'].verify_native(reader,pe,decoder,code,refs,n669,idx,shared,h,following_native=0x258)
    n671=m['f671'].original_case(reader,pe,real,boss,mapped)
    m['f671'].verify_negative(reader,pe,decoder,code,refs,n671,idx,shared,h,source_scratch_shift=source_scratch_shift)
    n673=m['f673'].actual_native(reader,pe,real,boss,mapped)
    m['f673'].verify_groundwave(reader,decoder,code,refs,n673,shared,h)
    n674=m['f674'].original_case(reader,pe,real,boss,mapped)
    terminal=m['f674'].true_terminal(reader,pe,real,boss,mapped)
    strict2ef,negative31c,idx=m['f674'].verify_native(reader,decoder,code,refs,n674,
            terminal,shared,h,following_native=0x2F0,terminal_expect_strict=False,
            terminal_preceding_native=0x31B,
            source_native_302_end_ordinal=source_native_302_end_ordinal)
    n676=m['f676'].original_cases(reader,pe,real,boss,mapped)
    negative676,idx=m['f676'].verify_negative(reader,decoder,code,refs,n676,idx,shared,h,
                                              following_native=0x2F8)
    n31b=m['f681'].native_cases(reader,pe,real,boss,mapped,m['f676'])
    negative2f8=m['f681'].verify_storm(decoder,code,refs,n31b,idx,shared,h,following_native=0x2F9)
    f684=load('f696_context_2f9','scripts/verify-fighter-angle-storm-f684.py')
    native2f9=f684.original_2f9(reader,pe,real,boss,mapped,m['f676'])
    # Real 2FB's second source index moves the *actual* F684 compiler
    # scratch slots by four bytes; check each original operand unchanged.
    f684.SLOTS={i:(native, f'0x{int(source,16)+source_f684_slot_shift:x}')
                for i,(native,source) in f684.SLOTS.items()}
    negative2f9=f684.verify_negative(decoder,native2f9,code,refs,idx+252,shared,h,
                                        following_native_2fa=following_native_2fa,
                                        expected_compiled_size=source_2f9_expected_size,
                                        expected_wide_ordinals=source_2f9_wide_ordinals)
    negative31b=f684.verify_terminal_negative(decoder,code,refs,n31b,shared,h,
                                                m['f681'],m['f674'],
                                                source_native_302_end_ordinal=source_native_302_end_ordinal)
    need((len(p653),len(p654),len(p656),len(p657),len(p664),len(p668),len(p669))
         ==(3,2,5,3,2,3,3),
         'earlier 27 source-context strict original inner bodies regressed in new parent')
    return {
        'native_original_saved_this_EBP':'-0x44',
        'new_compiler_actual_saved_this_EBP':'-'+source_receiver_slot,
        'physically_attested_compiled_saved_this_mov_uses':len(uses),
        'previous_27_nonterminal_context_strict_original_cases_rechecked':True,
        'genuine_previous_nonstrict_case_controls_rechecked':True,
        'prior_2f9_nonfield_GPR_mismatches':negative2f9['actual_nonfield_native_register_x87_differences'],
        'prior_terminal_31b_real_gpr_negative':negative31b['source_context_genuine_GPR_mismatch_count'],
        'prior_terminal_31c_remains_nonstrict':True,
        'original_after_RET_switch_DATA_rechecked_on_this_source':True,
        'original_whole_parent_code_exact':False,
    }


def main():
    reader=load('f696_reader','scripts/compare-coff-function.py')
    acts=load('f696_acts','scripts/report-fighter-action-handlers.py')
    f676=load('f696_fields','scripts/verify-fighter-cloud-burst-f676.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    lo,hi=by[START],by[NEXT]
    native=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
    need(lo==0x00550D97 and hi==0x0055101E and hi-lo==ORIGINAL_SIZE
         and len(native)==ORIGINAL_X86 and sum(x.size for x in native)==ORIGINAL_SIZE
         and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
         'original whole physical 2FB case CODE interval not attested')
    native_fields=f676.original_fields(native)
    need(len(native_fields)==len(ORIGINAL_FIELD_ORDINALS)
         and tuple(i for i,_,_ in native_fields)==ORIGINAL_FIELD_ORDINALS
         and all(target in EXPECTED_SYMBOLS for _,target,_ in native_fields),
         'original 17 typed native call/global PE fields are not as observed')
    source,mods,prior=source_for_entire_parent(reader,pe,real,boss,report,mapped)
    OUT.mkdir(parents=True, exist_ok=True)
    cpp=OUT/'Boss00543210-2FB.cpp'
    obj=OUT/'Boss00543210-2FB.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'VC7.1 failed: '+proc.stderr[-700:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    generated=[]
    for inst in real.disasm(code,0):
        generated.append(inst)
        if inst.mnemonic=='ret':break
    starts=[i for i,x in enumerate(generated)
            if [y.op_str for y in generated[i:i+3]]==['0xff0000','4','3']
            and [y.mnemonic for y in generated[i:i+3]]==['push','push','push']]
    need(len(starts)==2, 'full parent must contain both native 2F9 and 2FB configuration prologues')
    index=starts[-1]
    end=next(i for i,x in enumerate(generated[index:],index)
             if x.mnemonic=='mov' and x.op_str.endswith(', 0x303'))
    current=generated[index:end]
    need(len(current)==ORIGINAL_X86 and sum(x.size for x in current)==GENERATED_SIZE
         and current[-1].mnemonic=='jmp' and current[-1].op_str==generated[starts[0]-1].op_str,
         'generated complete original 2FB action 181-x86, 635-byte geometry changed')
    # The actual previous 2FA marker is NOT the real native case. It must
    # remain a placeholder, so 2FB is not misidentified as another action.
    need(generated[index-2].mnemonic=='mov'
         and generated[index-2].op_str.endswith(', 0x2fb'),
         'the complete emitted case 2FB does not follow its real 2FA marker')
    mismatches={i:(a.mnemonic,b.mnemonic) for i,(a,b) in enumerate(zip(native,current))
                if a.mnemonic!=b.mnemonic}
    need(mismatches==OPCODE_REORDERS,
         f'four genuine native 2FB angle-operand move/FLD orders changed: {mismatches}')
    sizes={i:(a.size,b.size) for i,(a,b) in enumerate(zip(native,current)) if a.size!=b.size}
    need(sizes=={i:t[:2] for i,t in WIDTH_NEGATIVES.items()},
         f'authentic wide native EBP x87 operand displacements changed: {sizes}')
    for i,(_,_,original_slot,source_slot) in WIDTH_NEGATIVES.items():
        need(f'[ebp - {original_slot}]' in native[i].op_str
             and f'[ebp - {source_slot}]' in current[i].op_str,
             f'original {i} native EBP scratch and compiler local must both be examined')
    fields=[r for r in refs if current[0].address<=r['offset']<current[-1].address+current[-1].size]
    need(len(fields)==len(native_fields),'17 actual complete original PE/COFF source fields missing')
    for i,target,mn in native_fields:
        own=[r for r in fields if current[i].address<=r['offset']<current[i].address+current[i].size]
        need(len(own)==1 and own[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and own[0]['addend']==0 and own[0]['local_symbol_offset'] is None
             and EXPECTED_SYMBOLS[target] in own[0]['symbol']
             and native[i].mnemonic==current[i].mnemonic,
             f'native original COFF typed field/owner mismatch at whole-case x86 ordinal {i}')
    # The original full parent has far larger EBP scratch slots than the
    # reconstructed TU. Save the actual source receiver, never treat every
    # frame-slot displacement as cosmetic or exact.
    need(generated[3].op_str=='dword ptr [ebp - 0x18], ecx'
         and current[69].op_str=='dword ptr [ebp - 0x7c], ecx'
         and current[97].op_str=='dword ptr [ebp - 0x80], ecx',
         'real new parent saved receiver/scratch stack ownership changed')
    normalized=prior['f598'].normalized
    wrong=[i for i,(a,b) in enumerate(zip(normalized(native),normalized(current))) if a!=b]
    need(len(wrong)==109 and wrong[0]==5,
         'actual 2FB native GPR/source register phase changed; do not promote case as strict')
    parent_context=verify_prior_parent_context(reader,pe,real,boss,report,mapped,code,refs,mods,prior)
    outcome={
        'original_target':'pinned PE verified via original reader',
        'giant_original_entry':f'0x{ACTOR:08X}',
        'whole_parent_original_CODE_bytes_NONEXACT':boss['size'],
        'native_action':'0x2FB','native_start':f'0x{lo:08X}','native_end_exclusive':f'0x{hi:08X}',
        'original_native_complete_CODE_bytes':ORIGINAL_SIZE,
        'real_native_x86_instructions':ORIGINAL_X86,
        'compiled_case_x86_instructions':len(current),
        'generated_case_CODE_bytes':sum(x.size for x in current),
        'genuine_original_physically_mapped_PE_COFF_fields':len(fields),
        'actual_native_opcode_reorders':list(OPCODE_REORDERS),
        'actual_native_scratch_operand_width_differences':list(WIDTH_NEGATIVES),
        'real_native_GPR_operand_mismatch_positions':len(wrong),
        'source_saved_receiver_EBP':'-0x18',
        'original_saved_receiver_EBP':'-0x44',
        'whole_parent_original_dispatch_and_prior_case_context':parent_context,
        'whole_parent_exact':False,'new_accepted_whole_game_CODE_bytes':0,
    }
    (OUT/'summary.json').write_text(json.dumps(outcome,indent=2)+'\n')
    print('F696 verified full selected original boss 00543210 source: real action 2FB '
          '181/181 machine x86 positions, 647 native/635 generated CODE bytes, '
          'all 17 original typed PE/COFF fields. Four authentic angle MOV/FLD '
          'order differences, four genuine EBP operand-width differences and '
          '109 actual mismatched normalized GPR/CFG roles: NONSTRICT. '
          'Earlier 27 strict contextual cases and actual after-RET DATA rechecked. '
          'Whole 58KB boss still NONEXACT; no function credit or full replay.')


if __name__=='__main__':
    main()
