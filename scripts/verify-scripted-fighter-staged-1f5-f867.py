#!/usr/bin/env python3
"""F867: original 1F5 628B/195x86/17 real typed PE fields in whole fighter.

Physically real native source: state-zero reset and flag, height
damping using global6583FC then floor bound657480 (NOT 65782C),
ground early aux18, state1/stage2/stage13/stage14/stage15/stage24
motion/projectile events. Stage1+15 raw sprites 7F use true
narrow byte fourth parameter, stage2 projectile33B and stage13
sprite338 use genuine source methods. Compile only the ONE affected
whole normal VC7.1 fighter. All 195 original mnemonic/width and
17 actual original PE types/offsets/destinations match; still
124 genuine native GPR operand byte negatives and 4 enclosing
whole-parent final JMP operands. Prior 38 whole source-backed real
game cases and 5 separate 901B packed afterRET tables checked.
Original giant NONEXACT, no independently callable case credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f867-scripted-state1f5'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,63,66,82,85,94,97,100,103,119,122,129,132,148,151,154,157,160,163,166,169,172,175,209,212,219,220,233,235,239,242,256,260,263,268,272,275,279,282,291,294,296,298,301,303,305,308,310,322,326,329,334,338,341,347,350,352,354,357,359,361,364,366,391,395,398,403,407,410,416,419,421,423,426,428,430,433,435,460,464,467,472,476,479,483,487,495,498,505,509,512,517,521,524,528,531,538,541,548,551,560,563,565,567,570,572,574,577,579,591,595,598,603,607,610,624,625]
FIELDS={
 9:(0x453e20,'ResetAt453E20'),
 18:(0x65782c,'g_ThresholdAt0065782C'),
 24:(0x6583fc,'g_F866DropAt006583FC'),
 29:(0x657480,'g_StopThresholdAt00657480'),
 37:(0x65782c,'g_ThresholdAt0065782C'),
 51:(0x65782c,'g_ThresholdAt0065782C'),
 56:(0x453e20,'ResetAt453E20'),
 59:(0x40fb40,'SetAuxActionAt40FB40'),
 64:(0x40fa30,'GetNativeActionAt40FA30'),
 72:(0x40fac0,'SetNativeActionAt40FAC0'),
 95:(0x453c80,'SpawnRawAt453C80'),
 116:(0x453a70,'SpawnDirectedAt453A70'),
 119:(0x453d40,'PrepareActionAt453D40'),
 140:(0x453a70,'SpawnDirectedAt453A70'),
 143:(0x453d40,'PrepareActionAt453D40'),
 182:(0x453c80,'SpawnRawAt453C80'),
 193:(0x40fb40,'SetAuxActionAt40FB40')
}
FIELD_OFFSETS=[26,70,89,107,136,179,194,204,227,251,317,376,386,445,455,586,619]
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,f):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/f)
    need(spec is not None and spec.loader is not None,'original PE helper missing '+f)
    mod=importlib.util.module_from_spec(spec);sys.modules[tag]=mod;spec.loader.exec_module(mod)
    return mod
def source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f866-scripted-state1f4/Boss005214B0-F866-whole.cpp'
    receipt=R/'.analysis/f866-scripted-state1f4/verified-summary.json'
    if not prior.is_file() or not receipt.is_file():
        previous=subprocess.run([str(R/'scripts/repo-python'),
          str(R/'scripts/verify-scripted-fighter-doubleprojectile-1f4-f866.py')],
          cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'f866-prior-fallback.log').write_text(previous.stdout+previous.stderr)
        need(previous.returncode==0,'previous native1F4 PE source failed '+(previous.stdout+previous.stderr)[-780:])
    evidence=json.loads(receipt.read_text())
    need(evidence['new_generated_whole_callable_CODE_B']==27494
         and evidence['native_original_whole_giant_exact'] is False,
         'previous 1F4 physical source receipt incorrect')
    cpp=prior.read_text()
    mark='        case 0x1F5: g_FighterProbeMarker = 502; break;'
    inc=(R/'probes/FighterScriptedStaged1F5F867.inc').read_text()
    need(cpp.count(mark)==1 and inc.count('case 0x1F5:')==1
         and inc.count('return;')==2 and inc.count('SpawnRawAt453C80(0x7F')==2
         and inc.count('SpawnDirectedAt453A70(')==2
         and 'POS<g_StopThresholdAt00657480' in inc
         and 'SetAuxActionAt40FB40(0x18)' in inc
         and 'SetAuxActionAt40FB40(0x16)' in inc
         and 'S16(0x62)==0x18' in inc
         and 'SpawnDirectedAt453A70(0x33B' in inc
         and 'SpawnDirectedAt453A70(0x338' in inc
         and 'SpawnRawAt453C80(int,int,int,char,int)' in cpp,
         'actual original 1F5 native C++ stage/events or typed fourth arg changed')
    return cpp.replace(mark,'#include "FighterScriptedStaged1F5F867.inc"',1)
def compile_one(src):
    cpp=O/'Boss005214B0-F867-whole.cpp';obj=O/'Boss005214B0-F867-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=E,capture_output=True,text=True,timeout=300)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'normal selected fighter 1F5 whole source build failed '+(run.stdout+run.stderr)[-770:])
    return obj
def main():
    rd=ld('f867rd','compare-coff-function.py')
    ac=ld('f867ac','report-fighter-action-handlers.py')
    f834=ld('f867f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f867f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f867f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f867f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f867f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f867f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f867f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f867f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f867f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f867f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f867f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f867f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f867f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f867f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f867f863','verify-scripted-fighter-short-19c19e-f863.py')
    f865=ld('f867f865','verify-scripted-fighter-sustain-1a0-f865.py')
    f866=ld('f867f866','verify-scripted-fighter-doubleprojectile-1f4-f866.py')
    zero=ld('f867zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f867sw','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==0x5214b0)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original fighter native code/afterRET DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x1f5],by[0x1f6]-by[0x1f5]),by[0x1f5]))
    need(len(original)==195 and by[0x1f6]-by[0x1f5]==628
         and original[3].op_str==original[7].op_str==hex(original[16].address)
         and original[29].op_str=='dword ptr [0x657480]'
         and original[34].op_str.endswith(', 0x40000000')
         and original[62].op_str=='0x52cb4f'
         and original[95].op_str=='0x453c80'
         and original[116].op_str=='0x453a70'
         and original[140].op_str=='0x453a70'
         and original[182].op_str=='0x453c80'
         and original[193].op_str=='0x40fb40'
         and original[194].op_str=='0x52cb4f',
         'actual original 1F5 native controlflow/calls/float bound shifted')
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(28107,7842,1021,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current selected whole fighter native VC7.1 source/COFF geometry changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all five separately owned original packed 901B tables not verified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0x1f7')
          and any('g_FighterProbeMarker' in r['symbol']
                  and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=195,
         'following true original case 1F6 source marker missing')
    k=marks[0];gen=ins[k-195:k]
    case=f834.physical_case(rd,pe,d,code,refs,gen,by,0x1f5,628,17,BAD,0x1f6,f820)
    need(case['native_complete_x86']==195
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[62,194]
         and gen[62].op_str==gen[194].op_str==hex(ret-4)
         and gen[29].mnemonic=='fcomp'
         and gen[34].op_str.endswith(', 0x40000000')
         and gen[95].mnemonic=='call' and gen[182].mnemonic=='call'
         and gen[130].mnemonic=='mov' and gen[130].size==3
         and gen[172].mnemonic=='mov' and gen[172].size==3,
         'actual original 1F5 stage1/15 narrow facing or floor/jumps wrong')
    lo=gen[0].address
    original_data=rd.pe_bytes_at(pe,by[0x1f5],628)
    ff=[r for r in refs if lo<=r['offset']<gen[-1].address+gen[-1].size]
    physical_mask=f820.physical_fields(rd,original_data,by[0x1f5],ff,lo,17)
    need(len(physical_mask)==68,'all 17 true PE native call/global fields must be checked')
    off=[]
    for ordinal,(target,symbol) in FIELDS.items():
        a,b=original[ordinal],gen[ordinal]
        found=[r for r in ff if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and symbol in found[0]['symbol']
             and found[0]['offset']-lo==a.address-by[0x1f5]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                               else f'dword ptr [0x{target:x}]'),
             'native 1F5 original physical field/target mismatch at x86 '+str(ordinal))
        off.append(found[0]['offset']-lo)
    need(off==FIELD_OFFSETS,'original game 1F5 physical PE field geometry shifted')
    need(len(BAD)==128 and all(j in BAD for j in (219,220,624,625)),
         'original 1F5 124 source register negatives plus 4 giant JMP bytes must remain honest')
    # Test that target actually uses the DISTINCT original floor
    # global 657480, not the common original 65782C threshold.
    need(original[29].op_str=='dword ptr [0x657480]'
         and original[18].op_str=='dword ptr [0x65782c]'
         and original[29].op_str!=original[18].op_str,
         'native 1F5 two different original float threshold globals conflated')
    # Recheck previous 38 fully source-backed actual native interior states.
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
      (0x19a,302,86,8,f862.BAD,0x19c),
      (0x19c,122,35,3,f863.WRONG,0x19e),
      (0x19e,122,35,3,f863.WRONG,0x1a0),
      (0x1a0,235,67,5,f865.WRONG,0x1f4),
      (0x1f4,448,136,14,f866.BAD,0x1f5)]
    prior=ins[k-195-sum(x[2] for x in late):k-195]
    cursor=0;recent=[]
    for a,nb,nx,nf,bad,nxt in late:
        sec=prior[cursor:cursor+nx];cursor+=nx
        result=f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820)
        if a==0x1a0:
            need(sec[3].op_str==sec[7].op_str==hex(sec[22].address),
                 'previous 1A0 real original two scaled variables unguarded')
        recent.append(result)
    need(cursor==len(prior),'18 preceding true GPR cases original PE source truncated')
    earlier=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                          (0x135,278,82,7,[274,275],0x136)]
    left=k-195-sum(x[2] for x in late)
    old=ins[left-sum(x[2] for x in earlier):left]
    cursor=0;past=[]
    for a,nb,nx,nf,bad,nxt in earlier:
        sec=old[cursor:cursor+nx];cursor+=nx
        past.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(old),'twenty older source-backed game cases truncated')
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,native_tail,0x52cb25,
        [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and native_tail[j]!=code[ret-46+j]]
    need(wrong_tail==[],'new 1F5 correct compiler context should give 34/34 original native default nonfield equality')
    receipt={'original_entire_giant':'0x005214B0',
       'native_original_whole_game_callable_CODE_B':46755,
       'current_generated_full_source_CODE_B':ret,
       'new_full_original_1F5_native':case,
       'actual_original_1F5_typed_PE_field_offsets':off,
       'genuine_original_1F5_distinct_floor_global':'0x657480',
       'common_original_ground_global':'0x65782C',
       'native_1F5_wrong_GPR_operand_B':124,
       'native_1F5_two_enclosing_giant_JMP_negative_pairs':[219,220,624,625],
       'prior_eighteen_original_native_full_cases_checked':recent,
       'earlier_twenty_original_game_native_cases_checked':past,
       'native_common_getter_46B_nonrelocation_equal':'34/34',
       'original_getter_typed_PE_calls':3,
       'original_five_901B_packed_afterRET_tables_verified':True,
       'separate_original_901B_afterRET_DATA_B':901,
       'original_whole_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_whole_giant_exact'] is False
    print('F867 original 1F5 628B/195-x86/17 physically true PE fields, six staged actions with distinct native floor657480 and 8-bit-facing sprite calls; full C++ fighter 28107B/7842-x86. 124 real GPR bytes and four original giant-epilogue JMP bytes still wrong. Previous 38 native case sources, common getter 34/34 and 5 original 901B afterRET tables rechecked; original whole giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F867 real original 1F5 giant source FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
