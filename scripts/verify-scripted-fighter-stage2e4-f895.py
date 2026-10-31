#!/usr/bin/env python3
"""F895 original native 2E4 whole 409B/114x86/11 genuine PE fields.

Real borrowed ownerX-current X float Abs threshold6591F4;
strict < branches to original uniform Random455580(0,4)+0x2E4,
the native action group 2E4..2E7. Current action completion
guards random30..60 and short+516, stage2 height12.5,
stage10 true shortF00 increment only under <2.
Same-size false sources invert source predicate, move random
out of guard, or change action range; all rejected physically.
Rebuild only affected full fighter and verify prior 70 original
native cases, 901B afterRET tables and common getter GPR phase.
"""
from pathlib import Path
import json,os,subprocess,sys
import importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f895-native-2e4'
SOURCE='probes/FighterScriptedStage2E4F895.inc'
BAD=[182,183,405,406]
def need(ok,msg):
    if not ok:raise ValueError(msg)
def load():
    spec=importlib.util.spec_from_file_location('f895verify_context',R/'scripts/verify-scripted-fighter-context-f895.py')
    mod=importlib.util.module_from_spec(spec);sys.modules[spec.name]=mod;spec.loader.exec_module(mod)
    return mod

def selected_source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f894-scripted2dd/Boss005214B0-F894-whole.cpp'
    rec=R/'.analysis/f894-scripted2dd/verified-summary.json'
    if not prior.is_file() or not rec.is_file():
        run=subprocess.run([str(R/'scripts/repo-python'),
            str(R/'scripts/verify-scripted-fighter-physical2dd-f894.py')],
            cwd=R,capture_output=True,text=True,timeout=1700)
        (O/'f894-native-fallback.log').write_text(run.stdout+run.stderr)
        need(run.returncode==0,'real original F894 PE receipt missing '+(run.stdout+run.stderr)[-700:])
    old=json.loads(rec.read_text())
    need(old['generated_new_whole_source_CODE_B']==41072
         and old['native_whole_fighter_exact'] is False
         and old['true_native_original_2DD_complete_CODE_B']==535,
         'previous original 2DD PE evidence changed')
    cpp=prior.read_text()
    marker='        case 0x2E4: g_FighterProbeMarker = 741; break;'
    inc=(R/SOURCE).read_text()
    need(cpp.count(marker)==1 and inc.count('case 0x2E4:')==1
         and inc.count('return;')==2
         and 'F892AbsAt00412D90' in inc
         and 'reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-' in inc
         and 'RandomBoundaryAt455580(0,4)+0x2E4' in inc
         and 'RandomBoundaryAt455580(30,60)' in inc
         and 'if (S16(0xF00)<2)' not in inc
         and '++S16(0xF00);' in inc,
         'native 2E4 physical threshold/action source changed')
    prefix='extern float g_F895AbsThresholdAt006591F4;\n'
    return prefix+cpp.replace(marker,'#include "FighterScriptedStage2E4F895.inc"',1)
def compile_one(src,tag):
    cpp=O/('Boss005214B0-F895-'+tag+'.cpp')
    obj=O/('Boss005214B0-F895-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=e,capture_output=True,text=True,timeout=360)
    (O/('compiler-'+tag+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'native 2E4 full selected normal VC7.1 '+tag+' failed '+(run.stdout+run.stderr)[-740:])
    return obj

def main():
    C=load();M=C.modules();rd=M['rd'];pe=rd.verified_target()
    cpp=selected_source()
    obj=compile_one(cpp,'whole')
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    code,refs,ins,ret,k=C.parse_coff(rd,d,obj,0x2e6,114)
    need((ret,len(ins),len(refs),len(code)-ret)==(41466,11696,1355,901),
         'current selected native 2E4 real full C++ source geometry changed')
    pe,d,by=C.native_environment(M,code,refs,ins,ret)
    need((by[0x2e4],by[0x2e5])==(0x52b466,0x52b5ff)
         and by[0x2e5]-by[0x2e4]==409,
         'original 2E4 physical native state extent wrong')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x2e4],409),by[0x2e4]))
    need(len(original)==114
         and original[35].op_str=='0x412d90'
         and original[37].op_str=='dword ptr [0x6591f4]'
         and original[44].op_str=='0x455580'
         and original[45].op_str=='eax, 0x2e4'
         and original[48].op_str=='0x40fac0'
         and original[80].op_str=='0x455580'
         and original[49].op_str==original[113].op_str=='0x52cb4f',
         'original real native 2E4 0..4 action range float threshold or early exit changed')
    sec=ins[k-114:k]
    row,offsets,targets=C.physical_case(M,pe,d,by,code,refs,sec,0x2e4,0x2e5,409,114,11,BAD)
    need(row['native_complete_x86']==114
         and row['original_native_enclosing_parent_JMP_exit_ordinals']==[49,113]
         and sec[49].op_str==sec[113].op_str==hex(ret-4),
         'selected 2E4 original whole fighter two far epilogue exits incorrect')
    prior=C.verify_previous(M,pe,d,by,code,refs,ins,k-114)
    need(prior['previous_source_case_count']==70
         and prior['physically_checked_cases']==67
         and prior['original_1FD_CMP_width_negative_preserved']
         and prior['original_252_254_physically_shifted']==['0x252','0x254'],
         'original 70 prior real native case and honest nonexact PE evidence incomplete')
    getter=C.native_getter_result(M,pe,code,refs,ret)
    # Three real game-incorrect but same-size C++ candidates are
    # independently compiled with the SAME whole parent and rejected
    # via physically read original case bytes/PE fields.
    frag=(R/SOURCE).read_text()
    include='#include "FighterScriptedStage2E4F895.inc"'
    mutations={
      'wrong-unconditional-random':(
         frag.replace('''        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(30,60);
    }''',
         '''        SetNativeActionAt40FAC0(0);
    }
    S16(0x516)=RandomBoundaryAt455580(30,60);'''),
         [182,183,266,405,406]),
      'wrong-threshold-inclusive':(
         frag.replace('<g_F895AbsThresholdAt006591F4','<=g_F895AbsThresholdAt006591F4'),
         [152,182,183,405,406]),
      'wrong-random-range':(
         frag.replace('RandomBoundaryAt455580(0,4)+0x2E4',
                      'RandomBoundaryAt455580(0,3)+0x2E4'),
         [156,182,183,405,406])}
    badcases={}
    for tag,(wrong_src,expected) in mutations.items():
        need(wrong_src!=frag and cpp.count(include)==1,
             'native 2E4 false game source mutation missing '+tag)
        obj2=compile_one(cpp.replace(include,wrong_src,1),tag)
        bc,br,bins,bret,bk=C.parse_coff(rd,d,obj2,0x2e6,114)
        need((bret,len(bins),len(br),len(bc)-bret)==(41466,11696,1355,901),
             'false game source must remain same-size complete original father '+tag)
        lo=bins[bk-114].address;hi=bins[bk-1].address+bins[bk-1].size
        fields=[r for r in br if lo<=r['offset']<hi]
        raw=rd.pe_bytes_at(pe,by[0x2e4],409)
        mask=M['f820'].physical_fields(rd,raw,by[0x2e4],fields,lo,11)
        bad=[j for j in range(409) if j not in mask and raw[j]!=bc[lo+j]]
        need(bad==expected,'nonnative same-size 2E4 machine field/control source must be rejected '+tag+str(bad))
        badcases[tag]=bad
    out={'native_fighter':'0x005214B0',
         'original_whole_callable_CODE_B':46755,
         'new_entire_generated_fighter_CODE_B':ret,
         'new_original_native_2E4_complete_case':row,
         'native_2E4_true_PE_field_offsets':offsets,
         'native_2E4_verified_PE_targets':targets,
         'real_random_0to4_plus_action_2E4':True,
         'real_stage10_shortF00_strict_counter_lt2':True,
         'real_2E4_internal_GPR_or_branch_wrong_B':0,
         'real_original_2E4_far_giant_JMP_wrong_offsets':BAD,
         'false_same_size_full_Cpp_source_controls':badcases,
         'previous_70_game_state_native_PE_checks':prior,
         'real_native_46B_getter':getter,
         'all_five_packed_original_901B_tables_physically_reverified':True,
         'original_afterRET_separate_DATA_B':901,
         'original_giant_entire_callable_exact':False,
         'new_accepted_whole_callable_CODE_B':0,
         'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    need(json.loads((O/'verified-summary.json').read_text())['original_giant_entire_callable_exact'] is False,
         'must never accept internal switch fragment as whole function')
    print('F895 original 2E4 complete 409B/114x86/11 genuine typed PE fields; float abs owner distance selects native random0..4 +2E4 action, guarded random30..60; strict threshold and 16-bit F00. Only four far-giant epilogue JMP B differ, no local branch/GPR wrong. Whole source 41466B/11696x86, previous 70 originals and all five 901B afterRET tables reverified; 3 false equal-size source controls rejected. 46755B original giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as err:
        print('F895 original native whole 2E4 physical PE FAILED:',err,file=sys.stderr)
        raise SystemExit(1)
