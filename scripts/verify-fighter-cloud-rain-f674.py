#!/usr/bin/env python3
"""F674: native 0x2EF 788B strict case with true terminal 0x31C context.

Compile ONE selected complete giant VC7.1 C++ parent; validate all
physical original 2EF PE fields, entire 224-instruction x86/CFG/GPR and
real 5-byte shared-exit JMP. The real following original 31C source
is independently NONSTRICT (register phase, not fabricated padding).
Recheck all earlier 26 strict cases, original 258/186/18A/18B EBP
negative cases and complete independently owned after-RET switch DATA.
No whole 58K giant CODE acceptance or full 943-unit cold replay.
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
OUT=ROOT/'.analysis/f674-fighter-cloud-rain'
ACTOR=0x00543210
ACTION=0x2EF
NEXT=0x2F0
ORIGINAL_X86=224
ORIGINAL_BYTES=788
FIELDS={
     17:(0x00453E20,'call','ResetAt453E20'),
     28:(0x0065785C,'fsub','g_CloudGravityAt0065785C'),
     33:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
     59:(0x006714D0,'movsx','g_CloudOpponentAt006714D0'),
     69:(0x00453D40,'call','PrepareActionAt453D40'),
     76:(0x006591E4,'fadd','g_CloudShotYAt006591E4'),
     84:(0x00453A70,'call','SpawnWithFloatAt453A70'),
     91:(0x006591E4,'fadd','g_CloudShotYAt006591E4'),
     99:(0x00453A70,'call','SpawnWithFloatAt453A70'),
    118:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
    124:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    127:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    135:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    139:(0x00455580,'call','RandomBoundaryAt455580'),
    140:(0x006714D0,'movsx','g_CloudOpponentAt006714D0'),
    159:(0x00453D40,'call','PrepareActionAt453D40'),
    174:(0x006591E4,'fadd','g_CloudShotYAt006591E4'),
    182:(0x00453A70,'call','SpawnWithFloatAt453A70'),
    197:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    217:(0x0040FB40,'call','SetAuxActionAt40FB40'),
}
TERMINAL_CALLS={
    13:(0x00453E20,'ResetAt453E20'),
    15:(0x0040FA30,'GetNativeActionAt40FA30'),
    23:(0x0040FAC0,'SetNativeActionAt40FAC0'),
    34:(0x00454A70,'SubactionAt454A70'),
    36:(0x00452B30,'SubactionAt452B30'),
    39:(0x00453D60,'PrepareActionAt453D60'),
    59:(0x0040FB40,'SetAuxActionAt40FB40'),
}


def need(ok,msg):
    if not ok:raise ValueError(msg)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'missing native source '+str(path))
    mod=importlib.util.module_from_spec(spec);sys.modules[name]=mod;spec.loader.exec_module(mod)
    return mod


def original_case(reader,pe,dec,boss,mapped):
    by={m['action']:int(m['handler'],16) for m in mapped}
    lo,hi=by[ACTION],by[NEXT]
    native=list(dec.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
    need(boss['address']<lo<hi<boss['address']+boss['size']
         and hi-lo==ORIGINAL_BYTES and len(native)==ORIGINAL_X86
         and sum(x.size for x in native)==ORIGINAL_BYTES
         and native[0].mnemonic=='mov'
         and native[-1].mnemonic=='jmp'
         and native[-1].op_str=='0x5515c2'
         and native[-1].size==5,
         'real original native entire 2EF PE x86 bounds/5-byte shared exit changed')
    need(native[9].op_str.endswith(', 0')
         and native[11].op_str.endswith(', 0')
         and native[13].op_str.endswith(', 0')
         and native[20].op_str.endswith(', 3')
         and native[24].op_str.endswith(', 0xb')
         and native[41].op_str.endswith(', 4')
         and native[45].op_str.endswith(', 8')
         and native[59].op_str=='eax, byte ptr [0x6714d0]'
         and native[82].op_str=='0x389'
         and native[97].op_str=='0x38a'
         and native[140].op_str=='ecx, byte ptr [0x6714d0]'
         and native[154].op_str.endswith(', 0x41840000')
         and native[180].op_str=='0x38b'
         and native[193].op_str.endswith(', 0x19')
         and native[213].op_str.endswith(', 0x19'),
         'original native 2EF initial multi-short state, ranked source shot or stage semantics changed')
    for ordinal,(dest,mn,_) in FIELDS.items():
        x=native[ordinal]
        if mn=='call':expect=f'0x{dest:x}'
        elif mn=='movsx':expect=f'{"eax" if ordinal==59 else "ecx"}, byte ptr [0x{dest:x}]'
        else:expect=f'dword ptr [0x{dest:x}]'
        need(x.mnemonic==mn and x.op_str==expect,
             f'original physical 2EF x86{ordinal} native target {dest:#x} differs')
    return native,lo,hi


def true_terminal(reader,pe,dec,boss,mapped):
    by={m['action']:int(m['handler'],16) for m in mapped}
    lo,hi=by[0x31C],0x00551598
    native=list(dec.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
    need(boss['address']<lo<hi<boss['address']+boss['size']
         and hi-lo==219 and len(native)==63
         and sum(x.size for x in native)==219
         and native[-1].mnemonic=='jmp' and native[-1].op_str=='0x5515c2',
         'original true physical terminal stage 31C shape changed')
    for ordinal,(dest,_) in TERMINAL_CALLS.items():
        x=native[ordinal]
        need(x.mnemonic=='call' and x.op_str==f'0x{dest:x}',
             f'original physical stage31C native x86{ordinal} call changed')
    return native,lo,hi


def source_with_rain_and_terminal(source):
    decl='void InitTrajectoryAt453E60(float);'
    need(source.count(decl)==1,'genuine native full parent trajectory declaration missing')
    source=source.replace(decl,decl+' int RandomBoundaryAt455580(int,int);')
    decl='extern float g_FallDecelerationAt00659888;'
    need(source.count(decl)==1,'genuine F673 parent native global declaration missing')
    source=source.replace(decl,decl+('\\nextern float g_CloudGravityAt0065785C;\\n'
                                     'extern float g_CloudShotYAt006591E4;\\n'
                                     'extern signed char g_CloudOpponentAt006714D0;').replace('\\n','\n'))
    first='        case 0x2EF: g_FighterProbeMarker = 752; break;'
    terminal='        case 0x31C: g_FighterProbeMarker = 797; break;'
    need(source.count(first)==source.count(terminal)==1,
         'original giant true physical 2EF/31C source markers absent')
    source=source.replace(first,'#include "FighterCloudRainF674.inc"')
    source=source.replace(terminal,'#include "FighterTerminalCounterF674.inc"')
    decl='void PrepareActionAt453D60(int);'
    need(source.count(decl)==1,'whole fighter normal action method declarations changed')
    source=source.replace(decl,decl+' void SubactionAt454A70(int); void SubactionAt452B30();')
    need(source.count('        case 0x2F0: g_FighterProbeMarker = 753; break;')==1,
         'true original physical next 2F0 handler source marker missing')
    return source


def field_match(native,compiled,ordinal,target,mn,symbol,physical,case):
    a,b=native[ordinal],compiled[ordinal]
    if mn=='call':want=f'0x{target:x}'
    elif mn=='movsx':want=f'{"eax" if ordinal==59 else "ecx"}, byte ptr [0x{target:x}]'
    else:want=f'dword ptr [0x{target:x}]'
    need(a.mnemonic==b.mnemonic==mn and a.op_str==want,
         f'{case} original physical PE target at x86{ordinal} differs')
    reloc=[f for f in physical if b.address<=f['offset']<b.address+b.size]
    need(len(reloc)==1
         and reloc[0]['type']==('REL32' if mn=='call' else 'DIR32')
         and reloc[0]['addend']==0 and reloc[0]['local_symbol_offset'] is None
         and symbol in reloc[0]['symbol'],
         f'{case} original COFF source field at x86{ordinal} missing genuine original {target:#x}')


def locate_marker(refs,ins,operand):
    found=[]
    for f in refs:
        if 'g_FighterProbeMarker' not in f['symbol']:continue
        i=next((j for j,x in enumerate(ins) if x.address<=f['offset']<x.address+x.size),None)
        if i is not None and ins[i].mnemonic=='mov' and ins[i].op_str.endswith(f', {hex(operand)}'):
            found.append(i)
    need(len(found)==1 and ins[found[0]+1].mnemonic=='jmp',
         f'previous true original native marker {operand:#x} not unique')
    return found[0]+2


def verify_native(reader,dec,code,refs,original,terminal,shared_exit,h,following_native=None, terminal_expect_strict=False, terminal_preceding_native=None):
    ins=[]
    for x in dec.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ordinal=locate_marker(refs,ins,0x2E6)
    original_ins,lo,hi=original
    compiled=ins[ordinal:ordinal+len(original_ins)]
    need(len(compiled)==ORIGINAL_X86
         and all(a.size==b.size for a,b in zip(original_ins,compiled))
         and compiled[-1].size==5 and compiled[-1].mnemonic=='jmp'
         and compiled[-1].op_str==shared_exit
         and compiled[-1].address+compiled[-1].size-compiled[0].address==ORIGINAL_BYTES,
         'genuine original physical full 2EF 788-byte CODE, 224 roles and 5-byte exit changed')
    physical=[f for f in refs if compiled[0].address<=f['offset']<compiled[-1].address+compiled[-1].size]
    need(len(physical)==len(FIELDS)==20,'all 20 original physical native PE/COFF fields required')
    for i,(target,mn,symbol) in FIELDS.items():
        field_match(original_ins,compiled,i,target,mn,symbol,physical,'2EF')
    lhs,rhs=h['f598'].normalized(original_ins),h['f598'].normalized(compiled)
    absolute={i for i,(target,mn,_) in FIELDS.items() if mn!='call'}
    wrong=[(i,a,b) for i,(a,b) in enumerate(zip(lhs,rhs)) if a!=b and i not in absolute]
    need(not wrong,f'2EF non-PE-field original GPR/x87/CFG roles differ {wrong[:8]}')
    raw=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(original_ins,compiled))
         if i not in absolute and a.mnemonic!='call'
         and not a.mnemonic.startswith('j')
         and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
    need(not raw,f'2EF original raw EBP/local argument operand roles differ {raw[:8]}')
    if following_native is None:
        need(ins[ordinal+ORIGINAL_X86].mnemonic=='mov'
             and ins[ordinal+ORIGINAL_X86].op_str.endswith(', 0x2f1'),
             'original next physical 2F0 source marker must directly follow 2EF')
    else:
        need(following_native==0x2F0
             and ins[ordinal+ORIGINAL_X86].mnemonic=='mov'
             and ins[ordinal+ORIGINAL_X86].op_str=='eax, dword ptr [ebp - 8]'
             and ins[ordinal+ORIGINAL_X86+1].mnemonic=='movsx'
             and ins[ordinal+ORIGINAL_X86+1].op_str=='ecx, word ptr [eax + 0x62]',
             'native C++ physical 2F0 must immediately follow strict 2EF')
    if terminal_preceding_native is None:
        terminal_start=locate_marker(refs,ins,0x31C)
    else:
        need(terminal_preceding_native==0x31B,
             'only original independently bounded 31B may precede this native terminal')
        terminal_start=locate_marker(refs,ins,0x303)+74
        need(ins[terminal_start].mnemonic=='mov'
             and ins[terminal_start].op_str.endswith(', dword ptr [ebp - 8]'),
             'native stage 31C must physically follow original full 74-x86 31B body')
    term,term_lo,term_hi=terminal
    generated_terminal=ins[terminal_start:terminal_start+len(term)]
    need(len(generated_terminal)==len(term)==63
         and sum(x.size for x in generated_terminal)==219
         and all(a.size==b.size for a,b in zip(term,generated_terminal))
         and generated_terminal[-1].mnemonic=='jmp'
         and generated_terminal[-1].op_str==shared_exit,
         'real source terminal native stage31C entire geometry or shared original exit changed')
    term_fields=[f for f in refs if generated_terminal[0].address<=f['offset']<generated_terminal[-1].address+generated_terminal[-1].size]
    need(len(term_fields)==len(TERMINAL_CALLS)==7,
         'true original terminal stage31C physical PE/COFF source fields changed')
    for i,(target,symbol) in TERMINAL_CALLS.items():
        field_match(term,generated_terminal,i,target,'call',symbol,term_fields,'31C')
    term_a,term_b=h['f598'].normalized(term),h['f598'].normalized(generated_terminal)
    wrong_term=[(i,a,b) for i,(a,b) in enumerate(zip(term_a,term_b)) if a!=b]
    if terminal_expect_strict:
        need(following_native==0x2F0 and not wrong_term,
             f'original terminal 31C genuine native nonfield GPR role mismatch: {wrong_term[:8]}')
        raw_term=[(i,a.op_str,b.op_str) for i,(a,b) in enumerate(zip(term,generated_terminal))
                  if a.mnemonic!='call' and not a.mnemonic.startswith('j')
                  and a.op_str.replace('[ebp - 0x44]','[ebp - 8]')!=b.op_str]
        need(not raw_term,
             f'original terminal 31C raw EBP/nonfield operand mismatch: {raw_term[:8]}')
    else:
        need(len(wrong_term)>=25 and wrong_term[0][0]==0,
             'original terminal native 31C register-phase NEGATIVE was unexpectedly removed')
    strict_case={'new_original_strict_native_action':'0x2EF',
                 'original_native_physical_start':f'0x{lo:08X}',
                 'original_next_native_physical_handler':f'0x{hi:08X}',
                 'entire_strict_original_x86_instructions':ORIGINAL_X86,
                 'strict_original_internal_CODE_bytes':ORIGINAL_BYTES,
                 'original_real_typed_PE_COFF_fields':len(physical),
                 'real_original_physical_exit_JMP_bytes':5,
                 'new_accepted_whole_GAME_FUNCTION_CODE_bytes':0}
    terminal_case={'original_native_terminal_action':'0x31C',
                   'actual_original_terminal_PE_start':f'0x{term_lo:08X}',
                   'original_terminal_source_x86_instructions':len(term),
                   'original_terminal_native_CODE_bytes':term_hi-term_lo,
                   'generated_terminal_native_CODE_bytes':sum(x.size for x in generated_terminal),
                   'genuine_typed_PE_COFF_calls':len(term_fields),
                   'real_nonfield_GPR_mismatch_count':len(wrong_term),
                   'strict_original_native_case':terminal_expect_strict}
    if following_native is None:
        return strict_case,terminal_case
    return strict_case,terminal_case,ordinal+ORIGINAL_X86



def main():
    f651=load('f674_f651','scripts/verify-fighter-resource-shots-f651.py')
    f653=load('f674_f653','scripts/verify-fighter-falling-recovery-f653.py')
    f654=load('f674_f654','scripts/verify-fighter-falling-finish-f654.py')
    f656=load('f674_f656','scripts/verify-fighter-late-stages-f656.py')
    f657=load('f674_f657','scripts/verify-fighter-motion-continuation-f657.py')
    f661=load('f674_f661','scripts/verify-fighter-motion-shots-f661.py')
    f664=load('f674_f664','scripts/verify-fighter-special-stage-f664.py')
    f668=load('f674_f668','scripts/verify-fighter-counter-special-f668.py')
    f669=load('f674_f669','scripts/verify-fighter-post-counter-f669.py')
    f671=load('f674_f671','scripts/verify-fighter-four-shot-barrage-f671.py')
    f673=load('f674_f673','scripts/verify-fighter-ground-wave-f673.py')
    h=f651.load_helpers()
    reader=load('f674_reader','scripts/compare-coff-function.py')
    acts=load('f674_acts','scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();dec=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,dec,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original=original_case(reader,pe,dec,boss,mapped)
    terminal=true_terminal(reader,pe,dec,boss,mapped)
    n651={a:f651.true_native(reader,pe,dec,boss,by,a) for a in (0xD1,0xD2)}
    n653=f653.native_cases(reader,pe,dec,boss,mapped)
    n654=f654.original_native(reader,pe,dec,boss,mapped)
    n656=f656.native_cases(reader,pe,dec,boss,mapped)
    n657=f657.native_cases(reader,pe,dec,boss,mapped)
    n661=f661.true_native(reader,pe,dec,boss,mapped)
    n664=f664.original_cases(reader,pe,dec,boss,mapped)
    n668=f668.physical_original(reader,pe,dec,boss,mapped)
    n669=f669.original_native(reader,pe,dec,boss,mapped)
    n671=f671.original_case(reader,pe,dec,boss,mapped)
    n673=f673.actual_native(reader,pe,dec,boss,mapped)
    source=f651.source_with_d1_d2(reader,pe,dec,boss,report,mapped,h)
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
    source=source_with_rain_and_terminal(source)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-2EF-31C-full-original-parent.cpp'
    obj=OUT/'Boss00543210-2EF-31C-full-original-parent.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'real pinned VC7.1 complete fighter giant source compile failed: '+cp.stderr[-550:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,dec,boss,report,mapped,code,refs,n651,h,following_native=0x12C)
    _,idx=f653.verify_new(reader,pe,dec,code,refs,old,n653,h,following_native=0x12F)
    _,idx=f654.verify_new(reader,pe,dec,code,refs,n654,old,idx,h,following_native=0x131)
    _,idx=f656.verify_native(reader,pe,dec,code,refs,n656,old,idx,h,following_native=0x186)
    _,neg186,idx=f657.verify_new(reader,pe,dec,code,refs,n657,old,idx,h,following_native=0x18A)
    neg661=f661.verify_nonstrict(reader,pe,dec,code,refs,n661,old,idx,h)
    _,idx=f664.verify_new_code(reader,pe,dec,code,refs,boss,mapped,n664,h,following_native=0x252)
    full=[]
    for x in dec.disasm(code,0):
        full.append(x)
        if x.mnemonic=='ret':break
    shared=full[old['continuation_source_ordinal']-1].op_str
    _,idx=f668.verify_inner(reader,pe,dec,code,refs,n668,idx,shared,h,following_native=0x255)
    _,idx=f669.verify_native(reader,pe,dec,code,refs,n669,idx,shared,h,following_native=0x258)
    neg671=f671.verify_negative(reader,pe,dec,code,refs,n671,idx,shared,h)
    prior673=f673.verify_groundwave(reader,dec,code,refs,n673,shared,h)
    new,negative_terminal=verify_native(reader,dec,code,refs,original,terminal,shared,h)
    receipt={'original_selected_whole_giant':'0x00543210',
             'whole_original_parent_CODE_bytes_still_NONEXACT':boss['size'],
             'entire_separate_after_RET_switch_DATA_bytes':boss['postret_size'],
             'previous_26_strict_native_original_case_interiors_verified_same_parent':True,
             'original_186_18A_18B_258_EBP_negative_cases_still_nonexact':True,
             'entire_original_afterRET_native_switch_DATA_reverified':True,
             'new_strict_original_complete_case':new,
             'actual_original_terminal_31C_source_backed_but_NONSTRICT':negative_terminal,
             'new_strict_internal_original_CODE_bytes':new['strict_original_internal_CODE_bytes'],
             'new_accepted_whole_authored_GAME_FUNCTION_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F674 original selected giant 00543210: new strictly matched entire '
          'native 2EF (224 original x86/788 genuine CODE B/20 original true '
          'typed PE/COFF fields). Original real terminal 31C normal C++ '
          'source restores the required five-byte shared JMP naturally '
          '(63 x86/219 B/7 fields, but 36 native nonfield GPR mismatches, '
          'therefore terminal remains NONSTRICT). Same fresh complete '
          'parent preserves all previous 26 context-strict original cases, '
          'four EBP negative cases, and full afterRET DATA. Giant still '
          'NONEXACT, zero entire authored function credit; no full replay.')


if __name__=='__main__':
    main()
