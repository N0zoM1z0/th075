#!/usr/bin/env python3
"""F859 current fighter 194 297B/86x86/7 original PE typed fields.

Falsify inherited 192 ResetAt453E20: original 194 stage-zero lacks
that helper; retaining it emits 298B/88x86 source and 8 rather than
7 real fields. Genuine source has native vertical drag, ground early
stateA exit, state9, stage5 sprite320 with owner float2 and stage6
flag. Build ONE entire affected normal VC7.1 parent, compare complete
native x86/physical call fields, 55 genuine GPR and four real
external epilogue JMP operand byte negatives, all 30 earlier case
sources, original common getter and five packed 901B DATA tables.
Original whole game giant NONEXACT, zero split-case callable CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f859-scripted-ground-194'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
WRONG=[1,5,8,12,16,19,23,27,35,38,45,48,51,54,57,60,63,66,69,72,98,101,108,111,118,121,128,129,142,144,148,151,165,169,172,177,181,184,188,191,203,206,208,210,213,215,217,220,222,260,264,267,272,276,279,283,286,293,294]
ORIGINAL_FIELDS={
 22:(0x65782c,'g_ThresholdAt0065782C'),
 28:(0x40fac0,'SetNativeActionAt40FAC0'),
 37:(0x40fa30,'GetNativeActionAt40FA30'),
 45:(0x40fac0,'SetNativeActionAt40FAC0'),
 68:(0x453a70,'SpawnDirectedAt453A70'),
 71:(0x46d000,'StartAnimationAt46D000'),
 74:(0x453d40,'PrepareActionAt453D40')}
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'native PE script missing '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m
def current_source(rd,pe,d,by):
    O.mkdir(parents=True,exist_ok=True)
    prev=subprocess.run([str(R/'scripts/repo-python'),
         str(R/'scripts/verify-scripted-fighter-stage-192-f858.py')],
         cwd=R,text=True,capture_output=True,timeout=1350)
    (O/'f858-prior-native.log').write_text(prev.stdout+prev.stderr)
    need(prev.returncode==0,'previous original 192 parent PE comparison failed '+(prev.stdout+prev.stderr)[-690:])
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x194],by[0x196]-by[0x194]),by[0x194]))
    need(len(original)==86 and by[0x196]-by[0x194]==297
         and original[13].mnemonic=='mov' and original[14].mnemonic=='fld'
         and original[15].mnemonic=='fsub'
         and original[22].mnemonic=='fcomp'
         and original[24].op_str=='ah, 0x41'
         and original[28].mnemonic=='call' and original[28].op_str=='0x40fac0'
         and original[35].op_str=='0x52cb4f'
         and original[55].op_str.endswith(', 0x40000000')
         and original[68].op_str=='0x453a70'
         and original[85].op_str=='0x52cb4f',
         'real native actor194 ground/float/call source identity changed')
    source=(R/'.analysis/f858-scripted-stage192/Boss005214B0-F858-whole.cpp').read_text()
    mark='        case 0x194: g_FighterProbeMarker = 405; break;'
    inc=(R/'probes/FighterScriptedGround194F859.inc').read_text()
    need(source.count(mark)==1 and inc.count('case 0x194:')==1
         and inc.count('return;')==2 and 'ResetAt453E20()' not in inc
         and 'POS54=POS54-POS5C;' in inc
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc
         and 'SetNativeActionAt40FAC0(0xA)' in inc
         and 'SetNativeActionAt40FAC0(9)' in inc
         and 'F32(0x314)=2.0f;' in inc
         and 'S16(0x62)==5' in inc
         and 'S16(0x62)==6' in inc,
         '194 genuine native source stage0 without Reset and x87 ground missing')
    return source.replace(mark,'#include "FighterScriptedGround194F859.inc"',1)
def compile_one(s):
    cpp=O/'Boss005214B0-F859-whole.cpp';obj=O/'Boss005214B0-F859-whole.obj'
    cpp.write_text(s)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=env,capture_output=True,text=True,timeout=290)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'normal source 194 entire fighter failed '+(p.stdout+p.stderr)[-720:])
    return obj
def main():
    rd=ld('f859rd','compare-coff-function.py')
    ac=ld('f859ac','report-fighter-action-handlers.py')
    f834=ld('f859f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f859f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f859f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f859f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f859f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f859f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f859f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f859f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f859f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f859f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f859f857','verify-scripted-fighter-floatshot-191-f857.py')
    zero=ld('f859zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f859switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original fighter 005214B0 PE identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(current_source(rd,pe,d,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(25972,7184,965,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current 194 whole source ABI/COFF/x86 geometry changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all five real original 901B packed switch tables failed')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x197')
           and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=86,'following 196 source marker missing')
    k=marks[0];gen=ins[k-86:k]
    native=f834.physical_case(rd,pe,d,code,refs,gen,by,0x194,297,7,WRONG,0x196,f820)
    need(native['native_complete_x86']==86
         and native['original_native_enclosing_parent_JMP_exit_ordinals']==[35,85]
         and gen[35].op_str==gen[85].op_str==hex(ret-4)
         and gen[24].op_str=='ah, 0x41'
         and gen[55].op_str.endswith(', 0x40000000'),
         'real original 194 ground branch/full fighter epilogue/float2 incorrect')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x194],297),by[0x194]))
    for ordinal,(dest,sym) in ORIGINAL_FIELDS.items():
        a,b=original[ordinal],gen[ordinal]
        fields=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(fields)==1 and fields[0]['addend']==0 and fields[0]['local_symbol_offset'] is None
             and fields[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in fields[0]['symbol']
             and fields[0]['offset']-gen[0].address==a.address-by[0x194]+a.size-4
             and a.op_str==(f'0x{dest:x}' if a.mnemonic=='call' else f'dword ptr [0x{dest:x}]'),
             'physical real original 194 PE/COFF field wrong at ordinal '+str(ordinal))
    # 10 earlier GPR-phase cases (136/186-192) and 20
    # previously sourced full game actions in the same new parent.
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
      (0x192,217,64,6,f856.BAD,0x194)]
    previous=ins[k-86-sum(x[2] for x in late):k-86]
    cursor=0;prior=[]
    for act,nb,nx,nf,bad,nxt in late:
        section=previous[cursor:cursor+nx];cursor+=nx
        prior.append(f834.physical_case(rd,pe,d,code,refs,section,by,act,nb,nf,bad,nxt,f820))
    need(cursor==len(previous),'ten original GPR case sources truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
    left=k-86-sum(x[2] for x in late)
    old=ins[left-sum(x[2] for x in early):left]
    cursor=0;older=[]
    for act,nb,nx,nf,bad,nxt in early:
        sec=old[cursor:cursor+nx];cursor+=nx
        older.append(f834.physical_case(rd,pe,d,code,refs,sec,by,act,nb,nf,bad,nxt,f820))
    need(cursor==len(old),'twenty previous original PE case sources truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
                  [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'genuine new whole parent getter has four original GPR operand negatives')
    result={'original_whole_fighter':'0x005214B0',
        'native_original_whole_callable_CODE_B':46755,
        'new_current_whole_source_callable_CODE_B':ret,
        'new_actor194_original_complete_native_case':native,
        'original194_native_fields_at_ordinals':list(ORIGINAL_FIELDS),
        'actual_original194_stagezero_ResetAt453E20_absent':True,
        'source_only_55_GPR_and_four_final_JMP_wrong_bytes':len(WRONG),
        'actual_parent_JMP_wrong_offsets':[128,129,293,294],
        'prior_ten_GPR_affected_case_original_PE_checked':prior,
        'twenty_earlier_original_case_sources_checked':older,
        'original_46B_getter_GPR_wrong_offsets':wrong_tail,
        'five_native_packed_afterRET_tables_rechecked':True,
        'original_separate_switch_DATA_B':901,
        'whole_original_game_exact':False,
        'new_whole_callable_CODE_accepted_B':0,
        'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['whole_original_game_exact'] is False
    print('F859 genuine original 194 297B/86-x86/7 original PE fields in full new 25972B/7184-x86 VC7.1 fighter; original 192 ResetAt453E20 was invalid here. 55 true GPR plus four whole game epilogue JMP bytes remain nonexact. Prior 30 physical cases and all five 901B packed switch tables verified; whole 46755B giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F859 real original whole fighter 194 FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
