#!/usr/bin/env python3
"""F899: entire original 2F8 native 1151B/316x86/28 PE fields.

In 005214B0 whole parent, state2F8 contains real stage6..12
random-position sprite392 with intermediate float scratch
FSTP EBP-12C, int Random455580(0,200) -> FILD EBP-130
then FSUBR. Stage8 random0..60 -> FILD EBP-134
height, signed-facing*150 FILD EBP-138 shot80, and
CloudOpponent signed-byte stage dynamic 13-Cloud
with F04<Cloud+1, aux7/turn-around.
Adding true native 2F8 naturally expands prior 2F0
short source JMP back to native 5B near JMP and original
828B/229x86. Last source2F8 still 1148B due its own
short JMP vs original native 1151B, with missing three B.
All 78 previous source-backed native cases and 901B
afterRET original tables checked in one whole COFF.
"""
from pathlib import Path
import json,os,subprocess,sys,importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f899-native-2f8'
BAD=[1146,1147]
LAST=0x2f8
def need(v,msg):
    if not v:raise ValueError(msg)
def load():
    sp=importlib.util.spec_from_file_location('f899context',R/'scripts/verify-scripted-fighter-context-f895.py')
    m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m);return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f898-native-2f0/Boss005214B0-F898-whole.cpp'
    rec=R/'.analysis/f898-native-2f0/verified-summary.json'
    if not prior.exists() or not rec.exists():
        cp=subprocess.run([str(R/'scripts/repo-python'),
           str(R/'scripts/verify-scripted-fighter-stage2f0-f898.py')],
           cwd=R,capture_output=True,text=True,timeout=1660)
        (O/'prior-f898-native.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'prior 2F0 original physical evidence missing '+(cp.stdout+cp.stderr)[-710:])
    old=json.loads(rec.read_text())
    need(old['new_generated_full_parent_CODE_B']==45169
         and old['new_native_2F0_source_current_CODE_B']==825
         and old['original_whole_callable_giant_exact'] is False,
         'previous 2F0 honest short-JMP receipt changed')
    cpp=prior.read_text()
    marker='        case 0x2F8: g_FighterProbeMarker = 761; break;'
    inc=(R/'probes/FighterScriptedStage2F8F899.inc').read_text()
    need(cpp.count(marker)==1 and inc.count('case 0x2F8:')==1
         and inc.count('return;')==1
         and 'S16(0xF04)=0;' in inc
         and 'S16(0x62)<6 && S16(0x64)<10' in inc
         and 'POS=POS-g_F884DoubleDropAt00657D00;' in inc
         and 'SpawnDirectedAt453A70(0x393' in inc
         and 'SpawnFloatXYAt453A70(0x392' in inc
         and 'RandomBoundaryAt455580(0,200)' in inc
         and 'RandomBoundaryAt455580(0,60)' in inc
         and 'SpawnFloatXRawYAt453C80(0x80' in inc
         and 'S16(0x62)==13-static_cast<int>(g_CloudOpponentAt006714D0)' in inc
         and 'S16(0xF04)<static_cast<int>(g_CloudOpponentAt006714D0)+1' in inc
         and 'SetAuxActionAt40FB40(7)' in inc
         and 'POS=15.0f;' in inc,
         'native original 2F8 complex stage/random/Cloud CPP source incomplete')
    return cpp.replace(marker,'#include "FighterScriptedStage2F8F899.inc"',1)

def compile_one(src,tag):
    cpp=O/('Boss005214B0-F899-'+tag+'.cpp')
    obj=O/('Boss005214B0-F899-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=e,capture_output=True,text=True,timeout=370)
    (O/('compiler-'+tag+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'native physical 2F8 whole VC7.1 '+tag+' failed '+(cp.stdout+cp.stderr)[-720:])
    return obj
def main():
    C=load();M=C.modules();rd=M['rd'];d=Cs(CS_ARCH_X86,CS_MODE_32)
    cpp=source()
    obj=compile_one(cpp,'whole')
    code,refs,I,ret,k=C.parse_coff(rd,d,obj,0x31c,316)
    need((ret,len(I),len(refs),len(code)-ret)==(46308,13097,1478,901),
         'selected whole fighter 2F8 native C++/COFF/afterRET changed')
    pe,d,by=C.native_environment(M,code,refs,I,ret)
    # Previous action2F0 828-B near-JMP restored without any fake
    # original bytes, inline ASM, linker patch or dummy locals.
    prior=I[k-316-229:k-316]
    row,prev_off,prev_targets=C.physical_case(
         M,pe,d,by,code,refs,prior,0x2f0,0x2f8,828,229,19,[824,825])
    need(row['original_native_enclosing_parent_JMP_exit_ordinals']==[228]
         and prior[-1].mnemonic=='jmp' and prior[-1].size==5,
         'true original 2F0 prior short-JMP compiler source not repaired')
    native_start=by[LAST];native_end=min(v for v in by.values() if v>native_start)
    raw=rd.pe_bytes_at(pe,native_start,native_end-native_start)
    N=list(d.disasm(raw,native_start))
    need((native_start,native_end,len(raw),len(N))==(0x52c4d3,0x52c952,1151,316)
         and N[64].op_str=='qword ptr [0x657d00]'
         and N[47].op_str=='dword ptr [ebp - 0x128], ecx'
         and N[147].op_str=='dword ptr [ebp - 0x12c]'
         and N[152].op_str=='dword ptr [ebp - 0x130], eax'
         and N[231].op_str=='dword ptr [ebp - 0x134], eax'
         and N[246].op_str=='dword ptr [ebp - 0x138], ecx'
         and N[151].op_str==N[230].op_str=='0x455580'
         and N[315].op_str=='0x52cb4f'
         and N[315].size==5,
         'real original 2F8 dynamic stage/double gravity/five FILD slots PE changed')
    sec=I[k-316:k];lo,hi=sec[0].address,sec[-1].address+sec[-1].size
    need((hi-lo,len(sec),sec[-1].size)==(1148,316,2)
         and all(a.mnemonic==b.mnemonic and a.size==b.size
                 and a.address-native_start==b.address-lo
                 for a,b in zip(N[:-1],sec[:-1]))
         and sec[-1].mnemonic=='jmp',
         'last native 2F8 true short source vs original five-byte JMP incorrectly hidden')
    f=[r for r in refs if lo<=r['offset']<hi]
    mask=M['f820'].physical_fields(rd,raw,native_start,f,lo,28)
    need(len(mask)==112,'all 28 real original 2F8 PE call/global operands missing')
    wrong=[j for j in range(1148) if j not in mask and raw[j]!=code[lo+j]]
    need(wrong==BAD,'unexpected true native 2F8 GPR/x87/branch source operand differences '+str(wrong))
    offsets=[]
    for r in f:
        off=r['offset']-lo
        ix=next(i for i,x in enumerate(sec) if x.address<=r['offset']<x.address+x.size)
        need(off==N[ix].address-native_start+N[ix].size-4
             and r['addend']==0 and r['local_symbol_offset'] is None,
             'native original 2F8 PE field physical instruction operand incorrectly relocated')
        offsets.append(off)
    # Original cloud dynamic stage and short F04 counter:
    # original GNU-like / VC7.1 different register phases in
    # short expressions must remain genuinely source-generated.
    need(sec[257].mnemonic==N[257].mnemonic=='movsx'
         and sec[260].mnemonic==N[260].mnemonic=='cmp'
         and sec[268].mnemonic==N[268].mnemonic=='movsx'
         and sec[270].mnemonic==N[270].mnemonic=='cmp'
         and sec[274].mnemonic==N[274].mnemonic=='add'
         and sec[304].mnemonic==N[304].mnemonic=='mov',
         'native 2F8 original CloudOpponent condition/face flip changed')
    # Strict current full-father prior 78 physical original
    # game-state intervals. In particular 2E7..2EA,2F0 now
    # ALL native 555/828-B original width geometry.
    extra=[
      (0x2e4,0x2e5,114,409,11,[182,183,405,406]),
      (0x2e5,0x2e6,102,374,12,[193,194,226,227,259,260,277,278,370,371]),
      (0x2e6,0x2e7,102,374,12,[193,194,226,227,259,260,277,278,370,371])]
    for a,nxt in ((0x2e7,0x2e8),(0x2e8,0x2e9),(0x2e9,0x2ea),(0x2ea,0x2f0)):
        extra.append((a,nxt,167,555,15,[268,269,551,552]))
    extra.append((0x2f0,0x2f8,229,828,19,[824,825]))
    prev=C.verify_previous(M,pe,d,by,code,refs,I,k-316,extra)
    need(prev['previous_source_case_count']==78
         and prev['physically_checked_cases']==75
         and prev['original_1FD_CMP_width_negative_preserved'],
         'previous 78 native real source cases not all originally PE checked')
    getter=C.native_getter_result(M,pe,code,refs,ret)
    need(getter['matching_original_nonfield_B']==34,
         'F899 current whole native getter must truly match 34/34 original nonfield bytes')
    frag=(R/'probes/FighterScriptedStage2F8F899.inc').read_text()
    include='#include "FighterScriptedStage2F8F899.inc"'
    wrong_sources={
       'wrong-cloud-limit':(frag.replace(
           'S16(0xF04)<static_cast<int>(g_CloudOpponentAt006714D0)+1',
           'S16(0xF04)<=static_cast<int>(g_CloudOpponentAt006714D0)+1'),
           [984,1146,1147]),
       'wrong-random200':(frag.replace(
           'RandomBoundaryAt455580(0,200)',
           'RandomBoundaryAt455580(0,199)'),
           [522,1146,1147])}
    negatives={}
    for tag,(incorrect,expected) in wrong_sources.items():
        need(incorrect!=frag and cpp.count(include)==1,
             '2F8 false whole C++ source not changed '+tag)
        obj2=compile_one(cpp.replace(include,incorrect,1),tag)
        bc,br,bI,bret,bk=C.parse_coff(rd,d,obj2,0x31c,316)
        need((bret,len(bI),len(br),len(bc)-bret)==(46308,13097,1478,901),
             '2F8 false game source must have deceptively identical whole geometry')
        bs=bI[bk-316:bk];blo=bs[0].address
        fs=[r for r in br if blo<=r['offset']<bs[-1].address+bs[-1].size]
        bm=M['f820'].physical_fields(rd,raw,native_start,fs,blo,28)
        bad=[j for j in range(1148) if j not in bm and raw[j]!=bc[blo+j]]
        need(bad==expected,'2F8 false equal-sized game C++ source must be rejected '+tag+str(bad))
        negatives[tag]=bad
    receipt={'native_original_whole_fighter':'0x005214B0',
       'native_original_entire_callable_CODE_B':46755,
       'new_complete_generated_whole_source_CODE_B':ret,
       'previous_2F0_now_correct_native_828B':row,
       'previous_2F0_true_PE_offsets':prev_off,
       'new_2F8_original_entire_inner_CODE_B':1151,
       'new_2F8_actual_generated_source_CODE_B':1148,
       'new_2F8_native_complete_x86':316,
       'new_2F8_original_typed_PE_field_count':28,
       'new_2F8_actual_PE_offsets':offsets,
       'new_native_2F8_FILD_temporary_stack_slots':['-0x128','-0x130','-0x134','-0x138'],
       '2F8_actual_native_float_intermediate_FSTP_EBP':'-0x12C',
       'native_2F8_double_gravity_original':'0x00657D00',
       'native_2F8_last_source_short_JMP_original_width_defect':True,
       'native_2F8_actual_short_JMP_wrong_bytes':wrong,
       'real_native_CloudOpponent_dynamic_stage_predicate':True,
       'false_same_size_game_source_controls':negatives,
       'all_78_previous_native_case_source_pe_checks':prev,
       'original_common_getter_34_of_34_native_nonfield_bytes':getter,
       'all_five_901B_original_packed_afterRET_tables_verified':True,
       'original_entire_callable_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F899 original 2F8 full 1151B/316x86/28 native physical PE fields (current source1148B due last 2B short JMP, no hidden bytes); random0..200 shot392 and dynamic CloudOpponent F04 bound restored, five natural source x87 scratch values. Adding real 2F8 restores previous 2F0 ORIGINAL 828B/229x86/19 PE fields near-JMP! Whole father 46308B/13097x86, all prior 78 native source cases, 901B packed tables and common getter34/34 checked; original 46755B giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as err:
        print('F899 original 2F8 selected whole parent physical PE FAILED:',err,file=sys.stderr)
        raise SystemExit(1)
