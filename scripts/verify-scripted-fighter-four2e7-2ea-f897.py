#!/usr/bin/env python3
"""F897 four original 2E7..2EA 555B/167x86/15 PE fields each.

A normal VC7.1 C++ source actually generates the native four FILD
scratch slots -110/-114/-118/-11C, 2E7/8 sprite38B vs 2E9/A
sprite38C, two genuine __ftol2 at original 6406AC per case.
But the last 2EA near its current source father epilogue uses
a nonnative 2B short JMP instead of original 5B far JMP:
it is 552B/167x86 in current 4-case selected parent. Do NOT
claim exact native case width. Recheck 73 previous original cases
including physical PE relocations, five 901B packed afterRET
tables; no all-unit cold replay or whole callable case credit.
"""
from pathlib import Path
import json,os,subprocess,sys,importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f897-four-2e7-ea'
ACTIONS=(0x2e7,0x2e8,0x2e9,0x2ea)
WRONG_FULL=[268,269,551,552]
WRONG_LAST=[268,269,550,551]
def need(ok,msg):
    if not ok:raise ValueError(msg)
def load():
    s=importlib.util.spec_from_file_location('f897context',R/'scripts/verify-scripted-fighter-context-f895.py')
    m=importlib.util.module_from_spec(s);sys.modules[s.name]=m;s.loader.exec_module(m);return m

def source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f896-paired-2e5-2e6/Boss005214B0-F896-whole.cpp'
    rec=R/'.analysis/f896-paired-2e5-2e6/verified-summary.json'
    if not prev.is_file() or not rec.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-pair2e5-2e6-f896.py')],
              cwd=R,capture_output=True,text=True,timeout=1700)
        (O/'prior-f896-original.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'prior 2E5/2E6 physically verified original source missing '+(cp.stdout+cp.stderr)[-670:])
    old=json.loads(rec.read_text())
    need(old['new_generated_full_source_CODE_B']==42184
         and old['entire_native_whole_fighter_exact'] is False,
         'previous original PE 2E5/2E6 receipt changed')
    body=(R/'probes/FighterScriptedFourShots2E7F897.inc').read_text()
    need(body.count('case F897_CASE:')==1
         and body.count('return;')==2
         and 'S16(0x80)=0x63;' in body
         and '++S16(0xF02);' in body
         and 'if (S16(0xF02)>4)' in body
         and 'g_CloudOpponentAt006714D0' in body
         and 'static_cast<signed short>(F32(0x44))' in body
         and 'static_cast<signed short>(F32(0x48))' in body
         and 'SpawnExtraRawYAt453B50(F897_SECOND_SPRITE' in body,
         'native four real 555B stages missing true gameplay C++ source')
    cpp='extern signed char g_CloudOpponentAt006714D0;\n'+prev.read_text()
    for a in ACTIONS:
        mark=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        need(cpp.count(mark)==1,'original four physical case markers missing '+hex(a))
        sprite=0x38b if a in (0x2e7,0x2e8) else 0x38c
        replacement=(f'#define F897_CASE 0x{a:X}\n'
           f'#define F897_SECOND_SPRITE 0x{sprite:X}\n'
           '#include "FighterScriptedFourShots2E7F897.inc"\n'
           '#undef F897_CASE\n#undef F897_SECOND_SPRITE')
        cpp=cpp.replace(mark,replacement,1)
    return cpp

def compile_one(src,tag):
    cpp=O/('Boss005214B0-F897-'+tag+'.cpp')
    obj=O/('Boss005214B0-F897-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=e,text=True,capture_output=True,timeout=340)
    (O/('compiler-'+tag+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'native 2E7..2EA normal full VC7.1 '+tag+' failed '+(cp.stdout+cp.stderr)[-690:])
    return obj

def main():
    C=load();M=C.modules();rd=M['rd'];d=Cs(CS_ARCH_X86,CS_MODE_32)
    cpp=source();obj=compile_one(cpp,'whole')
    code,refs,I,ret,k=C.parse_coff(rd,d,obj,0x2f1,668)
    need((ret,len(I),len(refs),len(code)-ret)==(44353,12556,1433,901),
         'four actual source original 2E7..2EA complete whole parent changed')
    pe,d,by=C.native_environment(M,code,refs,I,ret)
    actual=[];src_starts={}
    for i,a in enumerate(ACTIONS):
        start=k-(4-i)*167
        sec=I[start:start+167];src_starts[a]=start
        lo,hi=sec[0].address,sec[-1].address+sec[-1].size
        native=rd.pe_bytes_at(pe,by[a],555)
        N=list(d.disasm(native,by[a]))
        need(len(N)==167 and min(v for v in by.values() if v>by[a])-by[a]==555
             and N[15].op_str=='0x453e20'
             and N[93].op_str==N[98].op_str=='0x6406ac'
             and N[166].mnemonic=='jmp' and N[166].op_str=='0x52cb4f'
             and N[136].op_str==hex(0x38b if a in (0x2e7,0x2e8) else 0x38c),
             'original 2E7..2EA native source/FILD/FTOL2 sprite/physical extent incorrect '+hex(a))
        expected_stack=f'dword ptr [ebp - 0x{0x110+4*i:x}], ecx'
        need(N[43].op_str==sec[43].op_str==expected_stack
             and N[44].mnemonic==sec[44].mnemonic=='fild',
             'real native distinct FILD local stack slots not restored '+hex(a))
        if a!=0x2ea:
            case,offs,targets=C.physical_case(M,pe,d,by,code,refs,sec,
                     a,a+1,555,167,15,WRONG_FULL)
            need(case['original_native_enclosing_parent_JMP_exit_ordinals']==[73,166],
                 'native 2E7..2E9 two far epilogue exits incorrect '+hex(a))
        else:
            # Honest parent END CASE: VC7.1 chooses 2B short instead of
            # original 5B JMP. All 15 physical PE fields before it align.
            need(hi-lo==552 and sec[-1].mnemonic=='jmp'
                 and sec[-1].size==2 and N[-1].size==5
                 and all(n.mnemonic==s.mnemonic and n.size==s.size
                          and n.address-by[a]==s.address-lo
                          for n,s in zip(N[:-1],sec[:-1])),
                 'last 2EA source must retain honest short-JMP width defect')
            fs=[r for r in refs if lo<=r['offset']<hi]
            mask=M['f820'].physical_fields(rd,native,by[a],fs,lo,15)
            need(len(mask)==60,'original 2EA fifteen actual physical PE fields missing')
            actualwrong=[j for j in range(552) if j not in mask and native[j]!=code[lo+j]]
            need(actualwrong==WRONG_LAST,'2EA real original short-JMP source byte negatives changed')
            offs=[r['offset']-lo for r in fs];targets=[]
            case={'case':hex(a),'native_whole_inner_B':555,
                  'native_complete_x86':167,'generated_source_B':552,
                  'original_typed_PE_fields':15,
                  'real_nonrelocation_wrong_offsets':actualwrong,
                  'genuine_enclosing_JMP_last_width_defect':'original 5B vs current 2B',
                  'original_complete_case_exact':False}
        actual.append({'action':hex(a),'native':case,'real_PE_offsets':offs,
                       'native_true_FILD_stack':expected_stack})
    # 73 preceding original game states; all are in current full C++.
    prev=C.verify_previous(M,pe,d,by,code,refs,I,k-668,
          extra=[(0x2e4,0x2e5,114,409,11,[182,183,405,406]),
                 (0x2e5,0x2e6,102,374,12,[193,194,226,227,259,260,277,278,370,371]),
                 (0x2e6,0x2e7,102,374,12,[193,194,226,227,259,260,277,278,370,371])])
    need(prev['previous_source_case_count']==73 and prev['physically_checked_cases']==70,
         'all 73 prior native original game inner states unverified')
    getter=C.native_getter_result(M,pe,code,refs,ret)
    # One true bad C++ test: 2E9/2EA sprite 38B instead of native 38C.
    wrong=cpp.replace('F897_SECOND_SPRITE 0x38C','F897_SECOND_SPRITE 0x38B')
    need(wrong!=cpp,'could not change both native 2E9/2EA sprite constants')
    obj2=compile_one(wrong,'wrong-sprite38b')
    bc,br,bI,bret,bk=C.parse_coff(rd,d,obj2,0x2f1,668)
    need((bret,len(bI),len(br),len(bc)-bret)==(44353,12556,1433,901),
         'false 2E9/2EA sprite source must emit deceptively same full-giant geometry')
    for a in (0x2e9,0x2ea):
        i=ACTIONS.index(a);sec=bI[bk-(4-i)*167:bk-(3-i)*167]
        lo,hi=sec[0].address,sec[-1].address+sec[-1].size
        f=[r for r in br if lo<=r['offset']<hi]
        raw=rd.pe_bytes_at(pe,by[a],555)
        m=M['f820'].physical_fields(rd,raw,by[a],f,lo,15)
        bad=[j for j in range(hi-lo) if j not in m and raw[j]!=bc[lo+j]]
        expected=sorted((WRONG_LAST if a==0x2ea else WRONG_FULL)+[459])
        need(bad==expected,'false original 2E9/2EA sprite38B must differ in true PE opcode byte '+str((a,bad)))
    out={'original_giant':'0x005214B0','original_whole_callable_CODE_B':46755,
       'new_generated_full_source_CODE_B':ret,
       'original_four_2E7_2EA_complete_game_cases':actual,
       'original_four_physically_typed_PE_fields':60,
       'genuine_four_FILD_EBP_slots':['-0x110','-0x114','-0x118','-0x11C'],
       '2E9_2EA_sprite38C_vs_2E7_2E8_sprite38B_physically_checked':True,
       'selected_last_2EA_source_short_JMP_not_native_width':True,
       'earlier_three_native_geometry_except_real_far_JMPs':True,
       'wrong_two_sprite_original_byte_controls_compiled':True,
       'previous_73_case_original_PE_result':prev,
       'shared_46B_getter_original_PE_result':getter,
       'original_901B_afterRET_tables_physically_verified':True,
       'whole_original_callable_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F897 2E7/2E8/2E9 full original 555B/167x86/15 real PE fields, two original giant JMP byte-pairs per case only; 2EA same native grammar /15 PE fields but selected last-C++ source 552B short JMP vs original 555B long JMP (NOT exact). FOUR distinct native FILD scratch -110/-114/-118/-11C. Full normal giant 44353B/12556x86; previous73 actual original cases and 901B tables checked. Entire 46755B parent NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F897 original four 2E7..2EA current source PE FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
