#!/usr/bin/env python3
"""F898 physical original 2F0 828B/229x86/19 PE fields in full father.

Rebuild with original native 2F0 source AFTER four real 2E7..2EA:
normal VC7.1 code naturally converts previous 2EA short final JMP
back into original five-byte near JMP, restoring all four 555B
action extents. 2F0 itself becomes current LAST source case and
its final JMP is 2B vs original 5B (825B source vs 828B native).
Never mask missing three original bytes nor credit inner case.
Native 2F0 double gravity, stage7/9 float motion,
two genuinely live FILD temps EBP-120/124 and original
special CloudOpponent actor offset. Validate 19 typed PE
refs, all previous 77 original game case sources and 901B tables.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f898-native-2f0'
ADDR=0x005214B0
NEW=0x2f0
WRONG_F898=[823,824]
WRONG_PREVIOUS=[268,269,551,552]
ACTIONS=(0x2e7,0x2e8,0x2e9,0x2ea)
def need(ok,msg):
    if not ok:raise ValueError(msg)
def load():
    spec=importlib.util.spec_from_file_location('f898context',R/'scripts/verify-scripted-fighter-context-f895.py')
    m=importlib.util.module_from_spec(spec);sys.modules[spec.name]=m;spec.loader.exec_module(m);return m

def source():
    O.mkdir(parents=True,exist_ok=True)
    parent=R/'.analysis/f897-four-2e7-ea/Boss005214B0-F897-whole.cpp'
    rec=R/'.analysis/f897-four-2e7-ea/verified-summary.json'
    if not parent.is_file() or not rec.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-four2e7-2ea-f897.py')],
              cwd=R,capture_output=True,text=True,timeout=1500)
        (O/'previous-f897-native.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous real four-shot original PE evidence failed '+(cp.stdout+cp.stderr)[-740:])
    r=json.loads(rec.read_text())
    need(r['new_generated_full_source_CODE_B']==44353
         and r['selected_last_2EA_source_short_JMP_not_native_width']
         and r['whole_original_callable_giant_exact'] is False,
         'prior F897 fourth case honest short JMP receipt changed')
    src=parent.read_text()
    marker='        case 0x2F0: g_FighterProbeMarker = 753; break;'
    inc=(R/'probes/FighterScriptedStage2F0F898.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x2F0:')==1
         and inc.count('return;')==1
         and 'POS=POS-g_F884DoubleDropAt00657D00;' in inc
         and 'S16(0x62)<6' in inc
         and '++S16(0xF02);' in inc
         and 'SpawnAt453C80(0x3E' in inc
         and 'SetFloatMotionAt40FBB0(-200.0f,60.0f,0)' in inc
         and 'SetFloatMotionAt40FBB0(100.0f,60.0f,0)' in inc
         and 'SpawnWithFloatAt453A70(0x38D' in inc
         and 'g_CloudOpponentAt006714D0' in inc
         and 'SpawnFloatXRawYAt453C80(0x80' in inc
         and 'POS=15.0f;' in inc,
         '2F0 original game source incomplete')
    return 'extern float g_F898ShotYAt0065839C;\n'+src.replace(
           marker,'#include "FighterScriptedStage2F0F898.inc"',1)

def compile_one(src,tag):
    cpp=O/('Boss005214B0-F898-'+tag+'.cpp')
    obj=O/('Boss005214B0-F898-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=e,text=True,capture_output=True,timeout=355)
    (O/('compiler-'+tag+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'native 2F0 whole VC7.1 '+tag+' failed '+(cp.stdout+cp.stderr)[-740:])
    return obj

def main():
    C=load();M=C.modules();rd=M['rd'];d=Cs(CS_ARCH_X86,CS_MODE_32)
    cpp=source()
    obj=compile_one(cpp,'whole')
    code,refs,I,ret,k=C.parse_coff(rd,d,obj,0x2f9,229)
    need((ret,len(I),len(refs),len(code)-ret)==(45169,12783,1451,901),
         'F898 full current natural C++ fighter/COFF geometry changed')
    pe,d,by=C.native_environment(M,code,refs,I,ret)
    # Natural increase in actual source content after 2EA
    # makes its final JMP long again. All four original PE
    # states are now 555B, not three plus a 552B truncation.
    four=[]
    for i,a in enumerate(ACTIONS):
        sec=I[k-229-(4-i)*167:k-229-(3-i)*167]
        need(sec[-1].size==5,'2EA original natural final JMP width not restored '+hex(a))
        row,offs,dests=C.physical_case(M,pe,d,by,code,refs,sec,a,
              a+1 if a!=0x2ea else 0x2f0,555,167,15,WRONG_PREVIOUS)
        need(row['original_native_enclosing_parent_JMP_exit_ordinals']==[73,166]
             and sec[43].op_str.startswith('dword ptr [ebp - 0x'),
             'four original physical 555B states not all naturally restored')
        four.append({'action':hex(a),'original_native_555B':row,
                     'true_PE_field_offsets':offs})
    # The last new 2F0 case naturally has a TWO-BYTE short exit
    # until original future 2F8 is also restored. Mask nothing
    # around it; explicitly prove absent three original bytes.
    start=by[NEW];end=by[0x2f8]
    raw=rd.pe_bytes_at(pe,start,end-start)
    native=list(d.disasm(raw,start))
    need((start,end,len(raw),len(native))==(0x52c197,0x52c4d3,828,229)
         and native[58].op_str=='qword ptr [0x657d00]'
         and native[42].op_str=='dword ptr [ebp - 0x120]'
         and native[210].op_str=='dword ptr [ebp - 0x124]'
         and native[217].op_str=='0x453c80'
         and native[-1].mnemonic=='jmp' and native[-1].size==5
         and native[-1].op_str=='0x52cb4f',
         'true original 2F0 whole native extent /x87 DOUBLE gravity changed')
    sec=I[k-229:k];lo,hi=sec[0].address,sec[-1].address+sec[-1].size
    need((hi-lo,len(sec),sec[-1].size)==(825,229,2),
         'honest last 2F0 short whole parent JMP real defect not recorded')
    need(all(a.mnemonic==b.mnemonic and a.size==b.size
             and a.address-start==b.address-lo
             for a,b in zip(native[:-1],sec[:-1]))
         and sec[-1].mnemonic=='jmp' and native[-1].size==5,
         'all preceding native 2F0 original instruction mnemonics/width must match')
    origfields=[r for r in refs if lo<=r['offset']<hi]
    mask=M['f820'].physical_fields(rd,raw,start,origfields,lo,19)
    need(len(mask)==76,'nineteen original 2F0 PE fields physically missing')
    wrong=[j for j in range(825) if j not in mask and raw[j]!=code[lo+j]]
    need(wrong==WRONG_F898,'2F0 has additional real source errors outside final short JMP '+str(wrong))
    offsets=[]
    for f in origfields:
        off=f['offset']-lo
        index=next(i for i,x in enumerate(sec) if x.address<=f['offset']<x.address+x.size)
        need(off==native[index].address-start+native[index].size-4
             and f['addend']==0 and f['local_symbol_offset'] is None,
             '2F0 original relocation operand field displaced in normal C++ source')
        offsets.append(off)
    # Earlier 73 native PE states were revalidated in SAME parent.
    extra=[
       (0x2e4,0x2e5,114,409,11,[182,183,405,406]),
       (0x2e5,0x2e6,102,374,12,[193,194,226,227,259,260,277,278,370,371]),
       (0x2e6,0x2e7,102,374,12,[193,194,226,227,259,260,277,278,370,371])]
    prior=C.verify_previous(M,pe,d,by,code,refs,I,k-229-4*167,extra)
    need(prior['previous_source_case_count']==73
         and prior['physically_checked_cases']==70,
         '73 preceding original physical cases not checked in same source parent')
    getter=C.native_getter_result(M,pe,code,refs,ret)
    # Two full otherwise same-geometry native-source controls
    # must be rejected at real physical original machine bytes.
    frag=(R/'probes/FighterScriptedStage2F0F898.inc').read_text()
    include='#include "FighterScriptedStage2F0F898.inc"'
    controls={
      'wrong-facing40-to41':(
         frag.replace('float((*reinterpret_cast<signed char*>(RAW+0x66))*40)',
                      'float((*reinterpret_cast<signed char*>(RAW+0x66))*41)'),[156,823,824]),
      'wrong-stage8-sprite38E':(
         frag.replace('SpawnWithFloatAt453A70(0x38D',
                      'SpawnWithFloatAt453A70(0x38E'),[432,823,824])}
    rejected={}
    for name,(badsrc,expected) in controls.items():
        need(badsrc!=frag and cpp.count(include)==1,
             'native wrong 2F0 source cannot be generated '+name)
        fobj=compile_one(cpp.replace(include,badsrc,1),name)
        bc,br,bI,bret,bk=C.parse_coff(rd,d,fobj,0x2f9,229)
        need((bret,len(bI),len(br),len(bc)-bret)==(45169,12783,1451,901),
             'false 2F0 source should match whole length but genuine bytes differ')
        bs=bI[bk-229:bk];blo=bs[0].address;high=bs[-1].address+bs[-1].size
        fs=[r for r in br if blo<=r['offset']<high]
        bmask=M['f820'].physical_fields(rd,raw,start,fs,blo,19)
        bad=[i for i in range(825) if i not in bmask and raw[i]!=bc[blo+i]]
        need(bad==expected,'false 2F0 stage/float native content not rejected '+name+str(bad))
        rejected[name]=bad
    receipt={'original_whole_fighter':'0x005214B0',
      'original_native_callable_CODE_B':46755,
      'new_generated_full_parent_CODE_B':ret,
      'native_previous_four_2E7_2EA_now_all_555B':four,
      'new_native_2F0_actual_original_CODE_B':828,
      'new_native_2F0_source_current_CODE_B':825,
      'new_native_2F0_original_x86':229,
      'new_native_2F0_PE_fields_count':19,
      'new_native_2F0_PE_field_offsets':offsets,
      'actual_x87_2F0_int_FILD_slots':['-0x120','-0x124'],
      'actual_original_2F0_double_gravity_global':'0x00657D00',
      'new_native_2F0_short_parent_JMP_real_wrong_offsets':wrong,
      'native_2F0_final_JMP_width_defect':'original 5B versus current 2B',
      'two_false_source_negative_controls':rejected,
      'prior_73_original_native_game_cases_current_full_COFT_checked':prior,
      'native_shared_46B_getter_result':getter,
      'all_five_901B_original_packed_afterRET_tables_verified':True,
      'original_whole_callable_giant_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F898 original 2F0 828B/229x86/19 real PE fields source 825B only final nonnative short JMP (missing THREE native B), two live FILD slots -120/-124. Adding actual physical 2F0 naturally restores ALL FOUR original 2E7..2EA to 555B/167x86/15 PE each and only true far giant-JMP byte differences. Full current father45169B/12783x86, 73 previous source case PE checks and all 901B afterRET tables. Entire 46755B fighter STILL NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F898 original physical 2F0 whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
