#!/usr/bin/env python3
"""F671: 502-byte four-shot fighter 258 source, real EBP-lifetime negative.

Compile ONE newly selected 00543210 complete VC7.1 giant, recheck all
25 earlier context-strict native case bodies and complete after-RET DATA
in the same object, then verify 134 original 258 x86/12 physical COFF
fields and exactly 8 authentic EBP scratch width mismatches. Never
claim 258 strictly exact or accept any whole giant CODE from this.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f671-fighter-four-shot-barrage'
ACTOR=0x00543210
CASE=0x258
NEXT=0x259
ORIGINAL_X86=134
ORIGINAL_CASE_BYTES=502
SOURCE_CASE_BYTES=478
ORIGINAL_SLOTS={39:('0x114','0x2c'),40:('0x114','0x2c'),
                64:('0x118','0x30'),65:('0x118','0x30'),
                89:('0x11c','0x34'),90:('0x11c','0x34'),
               114:('0x120','0x38'),115:('0x120','0x38')}
FIELDS={11:(0x00453E20,'call','ResetAt453E20'),
        22:(0x0046D000,'call','StartAnimationAt46D000'),
        33:(0x006591EC,'fadd','g_BarrageY1At006591EC'),
        47:(0x00453A70,'call','SpawnFloatXYAt453A70'),
        58:(0x006581DC,'fadd','g_BarrageY2At006581DC'),
        72:(0x00453A70,'call','SpawnFloatXYAt453A70'),
        83:(0x0065908C,'fadd','g_BarrageY3At0065908C'),
        97:(0x00453A70,'call','SpawnFloatXYAt453A70'),
       108:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
       122:(0x00453A70,'call','SpawnFloatXYAt453A70'),
       124:(0x0040FA30,'call','GetNativeActionAt40FA30'),
       132:(0x0040FAC0,'call','SetNativeActionAt40FAC0')}


def need(ok,message):
    if not ok:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing genuine original source '+str(path))
    module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module
    spec.loader.exec_module(module)
    return module


def original_case(reader,pe,dec,boss,mapped):
    by={x['action']:int(x['handler'],16) for x in mapped}
    first,last=by[CASE],by[NEXT]
    original=list(dec.disasm(reader.pe_bytes_at(pe,first,last-first),first))
    need(boss['address']<first<last<boss['address']+boss['size']
         and last-first==ORIGINAL_CASE_BYTES
         and len(original)==ORIGINAL_X86
         and sum(x.size for x in original)==ORIGINAL_CASE_BYTES
         and original[0].mnemonic=='mov'
         and original[-1].mnemonic=='jmp' and original[-1].op_str=='0x5515c2',
         'true original 258 complete physical x86/exit changed')
    need(original[14].mnemonic=='cmp' and original[14].op_str.endswith(', 4')
         and original[20].mnemonic=='push' and original[20].op_str=='0x64'
         and all(original[i].mnemonic=='push' and original[i].op_str=='0x322'
                 for i in (45,70,95,120))
         and all(original[i].mnemonic=='call' and original[i].op_str=='0x453a70'
                 for i in (47,72,97,122)),
         'original real stage4 full four-shot resource order changed')
    for ordinal,(target,mn,_) in FIELDS.items():
        x=original[ordinal]
        expect=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(x.mnemonic==mn and x.op_str==expect,
             f'actual original PE-targeted x86 ordinal {ordinal} changed')
    return original,first,last


def source_with_barrage(source):
    decl='extern float g_YPlusAt00658400;'
    need(source.count(decl)==1,'genuine selected native source global declarations missing')
    extra='\nextern float g_BarrageY1At006591EC;\nextern float g_BarrageY2At006581DC;\nextern float g_BarrageY3At0065908C;'
    source=source.replace(decl,decl+extra)
    marker='        case 0x258: g_FighterProbeMarker = 601; break;'
    need(source.count(marker)==1,'real native action258 placeholder missing')
    source=source.replace(marker,'#include "FighterFourShotBarrageF671.inc"')
    need(source.count('        case 0x259: g_FighterProbeMarker = 602; break;')==1,
         'next true original physical action259 marker missing')
    return source


def verify_negative(reader,pe,dec,code,refs,native,start,shared_exit,h,following_native=None):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    original,lo,hi=native
    compiled=ins[start:start+ORIGINAL_X86]
    need(len(compiled)==ORIGINAL_X86 and compiled[-1].mnemonic=='jmp'
         and compiled[-1].op_str==shared_exit
         and sum(x.size for x in compiled)==SOURCE_CASE_BYTES,
         'native 258 entire original/compiled case x86 count or shared exit differs')
    physical=[f for f in refs
              if compiled[0].address<=f['offset']<compiled[-1].address+compiled[-1].size]
    need(len(physical)==len(FIELDS),
         'native 258 all twelve genuine source/PE physical typed fields differ')
    for ordinal,(target,mn,symbol) in FIELDS.items():
        a,b=original[ordinal],compiled[ordinal]
        expect=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(a.mnemonic==b.mnemonic==mn and a.op_str==expect,
             f'original native 258 PE x86{ordinal} destination {target:#x} changed')
        field=[f for f in physical if b.address<=f['offset']<b.address+b.size]
        need(len(field)==1
             and field[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and field[0]['addend']==0 and field[0]['local_symbol_offset'] is None
             and symbol in field[0]['symbol'],
             f'258 original native PE/COFF physical true symbol x86{ordinal} differs')
    widths=[(i,a.size,b.size) for i,(a,b) in enumerate(zip(original,compiled)) if a.size!=b.size]
    need(widths==[(i,6,3) for i in ORIGINAL_SLOTS],
         f'original native four wide scratch conversion pairs changed: {widths}')
    norm_orig,norm_comp=h['f598'].normalized(original),h['f598'].normalized(compiled)
    absolute={i for i,(target,mn,symbol) in FIELDS.items() if mn!='call'}
    wrong=[(i,a,b) for i,(a,b) in enumerate(zip(norm_orig,norm_comp))
           if a!=b and i not in absolute]
    need(not wrong,f'genuine original native GPR/x87/CFG roles differ beyond EBP offsets: {wrong[:8]}')
    # F598 normalized() intentionally ignores ALL stack offsets; never
    # accept 0x258 from that simplified comparator. Inspect raw EBP
    # operands independently and permit ONLY saved-this -0x44 -> -8.
    raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(original,compiled))
         if i not in absolute and a.mnemonic!='call'
         and not a.mnemonic.startswith('j')
         and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
    need([i for i,a,b in raw]==list(ORIGINAL_SLOTS)
         and all(f'[ebp - {old}]' in original[i].op_str
                 and f'[ebp - {new}]' in compiled[i].op_str
                 for i,(old,new) in ORIGINAL_SLOTS.items()),
         f'actual original native scratch EBP negative changed: {raw[:10]}')
    if following_native is None:
        need(ins[start+ORIGINAL_X86].mnemonic=='mov'
             and ins[start+ORIGINAL_X86].op_str.endswith(', 0x25a'),
             'native original 0x258 must end at next 0x259 source marker')
    else:
        need(following_native==0x259
             and ins[start+ORIGINAL_X86].mnemonic=='mov'
             and ins[start+ORIGINAL_X86].op_str=='eax, dword ptr [ebp - 8]'
             and ins[start+ORIGINAL_X86+1].mnemonic=='movsx'
             and ins[start+ORIGINAL_X86+1].op_str=='ecx, word ptr [eax + 0x62]',
             'actual native 259 body must immediately follow original 258')
    result={'real_original_native_action':'0x258',
            'entire_original_PE_native_start':f'0x{lo:08X}',
            'original_next_physical_native_handler':f'0x{hi:08X}',
            'original_whole_case_x86_instructions':len(original),
            'original_whole_native_inner_CODE_bytes':hi-lo,
            'generated_normal_CPP_case_bytes':SOURCE_CASE_BYTES,
            'true_original_typed_PE_COFF_fields':len(physical),
            'real_wrong_native_EBP_scratch_ordinals':list(ORIGINAL_SLOTS),
            'original_EBP_scratch':['-'+ORIGINAL_SLOTS[i][0] for i in (40,65,90,115)],
            'compiled_EBP_scratch':['-'+ORIGINAL_SLOTS[i][1] for i in (40,65,90,115)],
            'new_case_strict':False,'accepted_original_whole_authored_CODE_bytes':0}
    return result if following_native is None else (result,start+ORIGINAL_X86)


def main():
    f651=load('f671_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f671_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f671_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f671_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f671_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f671_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f671_f664','scripts/verify-fighter-special-stage-f664.py')
    f668=load('f671_f668','scripts/verify-fighter-counter-special-f668.py')
    f669=load('f671_f669','scripts/verify-fighter-post-counter-f669.py')
    h=f651.load_helpers()
    reader=load('f671_reader','scripts/compare-coff-function.py')
    acts=load('f671_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original=original_case(reader,pe,dec,boss,mapped)
    n651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    n653=f653.native_cases(reader,pe,dec,boss,mapped)
    n654=f654.original_native(reader,pe,dec,boss,mapped)
    n656=f656.native_cases(reader,pe,dec,boss,mapped)
    n657=f657.native_cases(reader,pe,dec,boss,mapped)
    n661=f661.true_native(reader,pe,dec,boss,mapped)
    n664=f664.original_cases(reader,pe,dec,boss,mapped)
    n668=f668.physical_original(reader,pe,dec,boss,mapped)
    n669=f669.original_native(reader,pe,dec,boss,mapped)
    source=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
    source=f653.replace_following_cases(source)
    source=f654.source_with_finish(source)
    source=f656.source_with_native_stages(source)
    source=f657.source_with_stage_186_189(source)
    source=f661.parent_source(source)
    source=f664.source_with_cases(source)
    source=f668.source_with_special(source)
    source=f669.add_native_cases(source)
    source=source_with_barrage(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-original-258-complex-source.cpp'
    obj=OUT/'Boss00543210-original-258-complex-source.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'native VC7.1 selected original full giant compile failed: '+cp.stderr[-500:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,n651,h,following_native=0x12C)
    a,idx=f653.verify_new(reader,pe,dec,code,refs,old,n653,h,following_native=0x12F)
    b,idx=f654.verify_new(reader,pe,dec,code,refs,n654,old,idx,h,following_native=0x131)
    c,idx=f656.verify_native(reader,pe,dec,code,refs,n656,old,idx,h,following_native=0x186)
    d,negative186,idx=f657.verify_new(reader,pe,dec,code,refs,n657,old,idx,h,following_native=0x18A)
    negative661=f661.verify_nonstrict(reader,pe,dec,code,refs,n661,old,idx,h)
    old664,idx=f664.verify_new_code(reader,pe,dec,code,refs,boss,mapped,n664,h,following_native=0x252)
    wholeins=[]
    for x in dec.disasm(code,0):
        wholeins.append(x)
        if x.mnemonic=='ret':break
    shared=wholeins[old['continuation_source_ordinal']-1].op_str
    old668,idx=f668.verify_inner(reader,pe,dec,code,refs,n668,idx,shared,h,following_native=0x255)
    old669,idx=f669.verify_native(reader,pe,dec,code,refs,n669,idx,shared,h,following_native=0x258)
    negative=verify_negative(reader,pe,dec,code,refs,original,idx,shared,h)
    receipt={'selected_original_00543210_entire_parent_still_NONEXACT':boss['size'],
             'original_after_RET_owned_switch_DATA_bytes':boss['postret_size'],
             'earlier_25_context_strict_native_cases_rechecked_same_compiled_parent':True,
             'all_original_186_18A_18B_EBP_negative_controls_preserved':True,
             'original_complete_943_byte_afterRET_switch_DATA_checked':True,
             'new_original_complete_native_action258_source_backed_but_NONSTRICT':negative,
             'new_strict_original_native_case_count':0,
             'new_accepted_authored_whole_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F671 selected whole original fighter 00543210: full 0x258 '
          '502 original CODE B /134 x86 /12 authentic PE/COFF fields '
          'source-backed, FOUR original integer-to-float EBP scratch '
          'pairs mismatched (-114/-118/-11C/-120 vs -2C/-30/-34/-38); '
          'source emits 478B and remains intentionally NONSTRICT. '
          'All preceding 25 strict native interiors, three original EBP '
          'negative cases and full after-RET DATA rechecked in SAME '
          'full-parent fresh VC7.1 C++ object. No new authored exact '
          'whole-function CODE or all-unit replay.')


if __name__=='__main__':
    main()
