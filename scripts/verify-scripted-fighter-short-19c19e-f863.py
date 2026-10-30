#!/usr/bin/env python3
"""F863: two real original 122B/35-x86/3-PE field cases in whole fighter.

Genuine separately addressed 19C and 19E state0 initialization,
Reset, getter/action0 and stage4 state flag. Compile ONE affected
full normal VC7.1 parent; check all original PE calls and GPR
mismatches. Preserve prior 34 source-backed original game states,
all five 901B packed afterRET tables and default 46B nonfield.
Neither inner case is independently callable exact CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f863-scripted-19c19e'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
WRONG=[1,5,8,12,16,19,23,27,35,38,62,64,68,71,85,89,92,97,101,104,108,111,118,119]
FIELDS={13:(0x453e20,'ResetAt453E20'),
        15:(0x40fa30,'GetNativeActionAt40FA30'),
        23:(0x40fac0,'SetNativeActionAt40FAC0')}
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,fn):
    s=importlib.util.spec_from_file_location(tag,R/'scripts'/fn)
    need(s is not None and s.loader is not None,'missing pinned original PE helper '+fn)
    m=importlib.util.module_from_spec(s);sys.modules[tag]=m;s.loader.exec_module(m)
    return m
def current_source(rd,pe,d,by):
    O.mkdir(parents=True,exist_ok=True)
    source=R/'.analysis/f862-scripted-stage19a/Boss005214B0-F862-whole.cpp'
    receipt=R/'.analysis/f862-scripted-stage19a/verified-summary.json'
    if not source.is_file() or not receipt.is_file():
        p=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-stage-19a-f862.py')],
             cwd=R,capture_output=True,text=True,timeout=1300)
        (O/'f862-prior-fallback.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,'prior original 19A whole-source PE proof failed '+(p.stdout+p.stderr)[-700:])
    old=json.loads(receipt.read_text())
    need(old['current_selected_full_source_CODE_B']==26627
         and old['entire_original_46755B_exact'] is False,
         'previous original whole game 19A evidence receipt changed')
    src=source.read_text()
    for a,nxt in ((0x19c,0x19e),(0x19e,0x1a0)):
        original=list(d.disasm(rd.pe_bytes_at(pe,by[a],by[nxt]-by[a]),by[a]))
        need(len(original)==35 and by[nxt]-by[a]==122
             and original[13].op_str=='0x453e20'
             and original[15].op_str=='0x40fa30'
             and original[21].op_str=='0'
             and original[23].op_str=='0x40fac0'
             and original[26].mnemonic=='cmp' and original[26].op_str.endswith(', 4')
             and original[-1].op_str=='0x52cb4f',
             'real original 19C/19E native separate game case identity changed '+hex(a))
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        inc=(R/f'probes/FighterScriptedShort{a:X}F863.inc').read_text()
        need(src.count(marker)==1 and inc.count(f'case 0x{a:X}:')==1
             and inc.count('return;')==1
             and 'ResetAt453E20();' in inc
             and 'SetNativeActionAt40FAC0(0);' in inc
             and 'S16(0x62)==4' in inc,
             'real source normal C++ for selected native short action incomplete '+hex(a))
        src=src.replace(marker,f'#include "FighterScriptedShort{a:X}F863.inc"',1)
    return src
def compile_one(src):
    cpp=O/'Boss005214B0-F863-whole.cpp';obj=O/'Boss005214B0-F863-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=E,capture_output=True,text=True,timeout=300)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'F863 whole fighter short native cases compiler failed '+(p.stdout+p.stderr)[-770:])
    return obj
def main():
    rd=ld('f863rd','compare-coff-function.py')
    ac=ld('f863ac','report-fighter-action-handlers.py')
    f834=ld('f863f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f863f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f863f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f863f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f863f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f863f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f863f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f863f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f863f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f863f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f863f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f863f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f863f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f863f862','verify-scripted-fighter-stage-19a-f862.py')
    zero=ld('f863zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f863sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original giant PE/packed switch geometry changed')
    report,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    obj=compile_one(current_source(rd,pe,d,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(26841,7450,988,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'F863 current fighter native CODE/x86/COFF/ABI changed')
    dens,spars,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dens>0 and spars>0 and maps>0,
         'five original 901B native packed afterRET tables missing')
    marker=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x1a1')
        and any('g_FighterProbeMarker' in r['symbol']
               and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=70,'next real original 1A0 marker not unique')
    k=marker[0]
    new=[]
    for action,off,nxt in ((0x19c,70,0x19e),(0x19e,35,0x1a0)):
        section=ins[k-off:k-off+35]
        result=f834.physical_case(rd,pe,d,code,refs,section,by,action,122,3,WRONG,nxt,f820)
        need(result['native_complete_x86']==35
             and result['original_native_enclosing_parent_JMP_exit_ordinals']==[34]
             and section[-1].op_str==hex(ret-4)
             and section[26].op_str.endswith(', 4'),
             'original native 19C/19E whole source/giant-epilogue differs '+hex(action))
        orig=list(d.disasm(rd.pe_bytes_at(pe,by[action],122),by[action]))
        for ordinal,(target,sym) in FIELDS.items():
            a,b=orig[ordinal],section[ordinal]
            f=[r for r in refs if b.address<=r['offset']<b.address+b.size]
            need(len(f)==1 and f[0]['type']=='REL32'
                 and f[0]['addend']==0 and f[0]['local_symbol_offset'] is None
                 and sym in f[0]['symbol']
                 and f[0]['offset']-section[0].address==a.address-by[action]+a.size-4
                 and a.op_str==f'0x{target:x}',
                 'native original PE call field for selected short action wrong '+hex(action))
        new.append(result)
    # Fourteen late original full cases 136..19A (not fake split
    # units) and twenty earlier C8..135, PE-checked in the SAME object.
    late=[
       (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
       (0x186,250,74,7,f850.BAD186,0x187),
       (0x187,214,61,6,f850.BAD187,0x188),
       (0x188,214,61,6,f851.WRONG188,0x189),
       (0x189,381,107,11,f852.BAD189,0x18a),
       (0x18a,250,71,6,f853.BAD,0x18b),
       (0x18b,353,99,7,f855.WRONG,0x190),
       (0x190,217,64,6,f856.BAD,0x191),
       (0x191,166,53,5,f857.BAD,0x192),
       (0x192,217,64,6,f856.BAD,0x194),
       (0x194,297,86,7,f859.WRONG,0x196),
       (0x196,199,60,7,f860.BAD,0x198),
       (0x198,199,60,7,f860.BAD,0x19a),
       (0x19a,302,86,8,f862.BAD,0x19c)]
    before=ins[k-70-sum(x[2] for x in late):k-70]
    cursor=0;recent=[]
    for action,nb,nx,nf,bad,nxt in late:
        section=before[cursor:cursor+nx];cursor+=nx
        recent.append(f834.physical_case(rd,pe,d,code,refs,section,by,action,nb,nf,bad,nxt,f820))
    need(cursor==len(before),'14 preceding native physical game cases truncated')
    earlier=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
    left=k-70-sum(x[2] for x in late)
    prev=ins[left-sum(x[2] for x in earlier):left]
    cursor=0;older=[]
    for action,nb,nx,nf,bad,nxt in earlier:
        section=prev[cursor:cursor+nx];cursor+=nx
        older.append(f834.physical_case(rd,pe,d,code,refs,section,by,action,nb,nf,bad,nxt,f820))
    need(cursor==len(prev),'twenty earlier original PE source cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
              [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    need(len(mask)==12 and all(tail[i]==code[ret-46+i] for i in range(46) if i not in mask),
         'native 46B shared getter must be 34/34 nonrelocation equal in F863')
    out={'real_original_whole_fighter':'0x005214B0',
       'original_whole_callable_CODE_B':46755,
       'new_generated_entire_source_CODE_B':ret,
       'actual_native_19C_19E_complete_cases':new,
       'new_two_real_native_interior_CODE_B':244,
       'new_two_original_native_x86':70,
       'new_typed_original_PE_call_fields':6,
       'actual_genuine_GPR_byte_negatives_per_case':22,
       'original_giant_epilogue_JMP_negative_offsets_per_case':[118,119],
       'previous_fourteen_GPR_affected_case_sources_reverified':recent,
       'twenty_prior_PE_backed_original_game_cases_rechecked':older,
       'original_46B_getter_nonrelocation_equal':'34/34',
       'original_getter_typed_PE_calls':3,
       'all_five_original_901B_packed_afterRET_tables_reverified':True,
       'native_separate_switch_DATA_B':901,
       'original_whole_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_whole_giant_exact'] is False
    print('F863 original 19C and19E each 122B/35 x86/3 genuine PE calls in one 26841B/7450-x86 whole fighter. 22 true original GPR bytes plus 2 original giant-final JMP bytes each remain. Previous 34 complete native game cases, default 46B 34/34 and all five 901B packed tables rechecked, full original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F863 original selected 19C/19E native PE FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
