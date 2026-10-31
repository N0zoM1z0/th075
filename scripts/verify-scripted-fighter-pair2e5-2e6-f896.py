#!/usr/bin/env python3
"""F896 native original 2E5/2E6 sibling 374B/102x86/12 PE fields EACH.

Original action split: low random stage0..100 and active actor
sends 2E5->2E6 or 2E6->2E5, next split to 2E7, else 2E8.
At empty +7C, set action0, random60..120 short+516 then
direct enclosing giant exit. Stage2 vs stage3 float Y sprite38E.
Ten original whole-parent far JMP operand bytes per case
remain wrong. Recompile only latest whole VC7.1 game giant,
physically verify prior71 cases and all 901B afterRET tables.
"""
from pathlib import Path
import json,os,subprocess,sys,importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f896-paired-2e5-2e6'
MARKER=0x2e8
WRONG=[193,194,226,227,259,260,277,278,370,371]
CASES=((0x2e5,0x2e6,2),(0x2e6,0x2e5,3))
FALSE={
 'wrong-first-action':(213,),
 'wrong-first-guard':(210,),
 'wrong-stage-trigger':(290,)}
def need(ok,msg):
    if not ok:raise ValueError(msg)
def load():
    s=importlib.util.spec_from_file_location('f896context',R/'scripts/verify-scripted-fighter-context-f895.py')
    m=importlib.util.module_from_spec(s);sys.modules[s.name]=m;s.loader.exec_module(m);return m

def source():
    O.mkdir(parents=True,exist_ok=True)
    p=R/'.analysis/f895-native-2e4/Boss005214B0-F895-whole.cpp'
    rec=R/'.analysis/f895-native-2e4/verified-summary.json'
    if not p.is_file() or not rec.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
          str(R/'scripts/verify-scripted-fighter-stage2e4-f895.py')],
          cwd=R,capture_output=True,text=True,timeout=1500)
        (O/'f895-fallback.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous real native 2E4 physical proof unavailable '+(cp.stdout+cp.stderr)[-680:])
    old=json.loads(rec.read_text())
    need(old['new_entire_generated_fighter_CODE_B']==41466
         and old['original_giant_entire_callable_exact'] is False,
         'F895 physically verified parent changed')
    src=p.read_text()
    for a,next_,stage in CASES:
        mark=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        frag=(R/f'probes/FighterScriptedRandomPair{a:X}F896.inc').read_text()
        need(src.count(mark)==1 and frag.count(f'case 0x{a:X}:')==1
             and frag.count('return;')==5
             and f'SetNativeActionAt40FAC0(0x{next_:X})' in frag
             and f'if (S16(0x62)=={stage} && S16(0x64)==0)' in frag
             and 'S16(0xF00)=RandomBoundaryAt455580(0,100)' in frag
             and 'S16(0x516)=RandomBoundaryAt455580(60,120)' in frag
             and 'SpawnWithFloatAt453A70(0x38E' in frag,
             'native original 2E5/2E6 random/action/sprite source incomplete '+hex(a))
        src=src.replace(mark,f'#include "FighterScriptedRandomPair{a:X}F896.inc"',1)
    return src
def compile_one(src,tag):
    cpp=O/('Boss005214B0-F896-'+tag+'.cpp')
    obj=O/('Boss005214B0-F896-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=e,capture_output=True,text=True,timeout=335)
    (O/('compiler-'+tag+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'complete native 2E5/2E6 VC7.1 '+tag+' failed '+(cp.stdout+cp.stderr)[-680:])
    return obj

def main():
    C=load();M=C.modules();rd=M['rd'];d=Cs(CS_ARCH_X86,CS_MODE_32)
    src=source()
    obj=compile_one(src,'whole')
    code,refs,I,ret,k=C.parse_coff(rd,d,obj,MARKER,204)
    need((ret,len(I),len(refs),len(code)-ret)==(42184,11896,1377,901),
         'normal whole-fighter 2E5/2E6 native output geometry changed')
    pe,d,by=C.native_environment(M,code,refs,I,ret)
    received=[]
    for a,nxt,stage in CASES:
        need(by[nxt]-by[a] in (374,-374) and
             (by[a],by[a+1]-by[a]) in
             ((0x52b5ff,374),(0x52b775,374)),
             'original 2E5 or 2E6 physical next handler not 374B')
        raw=rd.pe_bytes_at(pe,by[a],374)
        N=list(d.disasm(raw,by[a]))
        need(len(N)==102 and N[55].op_str=='eax, 0x1e'
             and N[63].op_str=='edx, 0x3c'
             and N[100].op_str=='0x453a70'
             and N[75].op_str=='ecx, '+str(stage),
             'physical original 2E5/2E6 action dispatch/trigger changed')
        back=204 if a==0x2e5 else 102
        part=I[k-back:k-back+102]
        row,offs,targets=C.physical_case(
              M,pe,d,by,code,refs,part,a,a+1,374,102,12,WRONG)
        need(row['native_complete_x86']==102 and
             row['original_native_enclosing_parent_JMP_exit_ordinals']==[52,60,68,72,101],
             'original game 2E5/2E6 five far epilogue exits not exact-shaped')
        received.append({'action':hex(a),'native':row,'source_PE_offsets':offs,'original_PE_targets':targets,
          'true_gpr_wrong':0,'five_giant_exits_wrong_B':WRONG})
    prior=C.verify_previous(M,pe,d,by,code,refs,I,k-204,
        extra=[(0x2e4,0x2e5,114,409,11,[182,183,405,406])])
    need(prior['previous_source_case_count']==71 and prior['physically_checked_cases']==68,
         '71 earlier actual original source-backed states not physically checked')
    getter=C.native_getter_result(M,pe,code,refs,ret)
    # Three false whole VC7.1 sources: incorrect low action,
    # inclusive threshold and incorrect sprite trigger stage.
    mutations={}
    for tag,extra_wrong in FALSE.items():
        source_wrong=src
        for a,nxt,stage in CASES:
            inc=(R/f'probes/FighterScriptedRandomPair{a:X}F896.inc').read_text()
            if tag=='wrong-first-action':
                wrong=inc.replace(f'SetNativeActionAt40FAC0(0x{nxt:X})',
                                  'SetNativeActionAt40FAC0(0x2E7)')
            elif tag=='wrong-first-guard':
                wrong=inc.replace('S16(0xF00)<30','S16(0xF00)<=30')
            else:
                wrong=inc.replace(f'S16(0x62)=={stage}','S16(0x62)==1')
            need(wrong!=inc and source_wrong.count(
                 f'#include "FighterScriptedRandomPair{a:X}F896.inc"')==1,
                 'false whole original game source control unchanged '+tag)
            source_wrong=source_wrong.replace(
                 f'#include "FighterScriptedRandomPair{a:X}F896.inc"',wrong,1)
        bad_obj=compile_one(source_wrong,tag)
        bc,br,bins,bret,bk=C.parse_coff(rd,d,bad_obj,MARKER,204)
        need((bret,len(bins),len(br),len(bc)-bret)==(42184,11896,1377,901),
             'false game source should have same complete 374B/102x86 geometry '+tag)
        for a,nxt,stage in CASES:
            part=bins[bk-(204 if a==0x2e5 else 102):bk-(204 if a==0x2e5 else 102)+102]
            lo,hi=part[0].address,part[-1].address+part[-1].size
            fs=[r for r in br if lo<=r['offset']<hi]
            raw=rd.pe_bytes_at(pe,by[a],374)
            mask=M['f820'].physical_fields(rd,raw,by[a],fs,lo,12)
            bad=[i for i in range(374) if i not in mask and raw[i]!=bc[lo+i]]
            expected=sorted(WRONG+list(extra_wrong))
            need(bad==expected,'false same-size native 2E5/2E6 source must be rejected '+str((tag,a,bad)))
            mutations.setdefault(tag,{})[hex(a)]=bad
    receipt={'original_whole_fighter':'0x005214B0',
       'original_native_callable_CODE_B':46755,
       'new_generated_full_source_CODE_B':ret,
       'actual_original_2E5_2E6_complete_cases':received,
       'native_two_original_case_CODE_B':748,
       'native_two_original_case_x86':204,
       'native_two_original_PE_field_count':24,
       'actual_original_2E5_low_F00_action':'0x2E6',
       'actual_original_2E6_low_F00_action':'0x2E5',
       'false_equal_size_full_sources':mutations,
       'previous_71_original_game_states_physically_checked':prior,
       'native_shared_getter_current_phase':getter,
       'five_original_afterRET_packed_901B_tables_checked':True,
       'entire_native_whole_fighter_exact':False,
       'newly_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F896 original 2E5/2E6 each 374B/102x86/12 physical PE fields, real stage2 vs3 action random-cascade (2E6 vs 2E5) and sprite38E. Each only ten genuine far giant-JMP operand bytes wrong; all 71 prior PE native states and five packed 901B tables checked in whole VC7.1 42184B/11896x86. False full sources rejected; entire original 46755B fighter NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F896 native original paired 2E5/2E6 PE FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
