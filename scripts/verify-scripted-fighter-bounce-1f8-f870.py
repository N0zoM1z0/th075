#!/usr/bin/env python3
"""F870 original 1F8 full 469B/143x86/15 physically typed PE fields.

Stage0 Reset; genuine positive POS and POS48==threshold FUCOMPP
that must FLD global before FLD member; native POS gravity658058,
ground landing auxF; stage3 raw sprite7F with POS8/velocity12/drag.8,
stage7 sprite335 Prepare4, stage15 auxE. Exactly one entire affected
normal VC7.1 fighter compiled. Native opcode/width/PE relocation
positions & destinations all match; 84 real GPR byte negatives
plus two whole-giant epilogue JMP relative pairs remain. Recheck
41 preceding native PE-source cases, all 901B afterRET DATA and
current native 46B getter, no separate case/whole exact credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f870-scripted-state1f8'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,63,66,82,91,103,106,115,118,121,124,140,143,150,153,169,172,175,178,181,184,187,190,193,196,230,233,240,241,254,256,260,263,277,281,284,289,293,296,300,303,310,313,320,323,332,335,337,339,342,344,346,349,351,363,367,370,375,379,382,388,391,393,395,398,400,402,405,407,432,436,439,444,448,451,465,466]
FIELDS={
 9:(0x453e20,'ResetAt453E20'),
 18:(0x65782c,'g_ThresholdAt0065782C'),
 23:(0x65782c,'g_ThresholdAt0065782C'),
 31:(0x658058,'g_JumpGroundCorrectionAt00658058'),
 36:(0x65782c,'g_ThresholdAt0065782C'),
 44:(0x65782c,'g_ThresholdAt0065782C'),
 58:(0x65782c,'g_ThresholdAt0065782C'),
 63:(0x453e20,'ResetAt453E20'),
 66:(0x40fb40,'SetAuxActionAt40FB40'),
 71:(0x40fa30,'GetNativeActionAt40FA30'),
 79:(0x40fac0,'SetNativeActionAt40FAC0'),
 106:(0x453c80,'SpawnRawAt453C80'),
 127:(0x453a70,'SpawnDirectedAt453A70'),
 130:(0x453d40,'PrepareActionAt453D40'),
 141:(0x40fb40,'SetAuxActionAt40FB40')
}
OFFSETS=[26,70,86,110,128,157,200,215,225,248,272,358,417,427,460]

def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'missing original PE helper '+name)
    mod=importlib.util.module_from_spec(spec);sys.modules[tag]=mod;spec.loader.exec_module(mod);return mod

def create_source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f869-scripted-state1f7/Boss005214B0-F869-whole.cpp'
    proof=R/'.analysis/f869-scripted-state1f7/verified-summary.json'
    if not prior.exists() or not proof.exists():
        cp=subprocess.run([str(R/'scripts/repo-python'),
            str(R/'scripts/verify-scripted-fighter-conditional-1f7-f869.py')],
            cwd=R,capture_output=True,text=True,timeout=1350)
        (O/'f869-prior-source.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'prior F869 original PE source not verified '+(cp.stdout+cp.stderr)[-760:])
    j=json.loads(proof.read_text())
    need(j['current_generated_source_callable_CODE_B']==28756
         and j['whole_original_fighter_exact'] is False,
         'F869 whole original physical evidence receipt altered')
    src=prior.read_text()
    marker='        case 0x1F8: g_FighterProbeMarker = 505; break;'
    inc=(R/'probes/FighterScriptedGroundBounce1F8F870.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x1F8:')==1
         and inc.count('return;')==2
         and 'if (POS48==g_ThresholdAt0065782C)' in inc
         and 'POS=POS-g_JumpGroundCorrectionAt00658058;' in inc
         and 'SetAuxActionAt40FB40(0xF)' in inc
         and 'SpawnRawAt453C80(0x7F' in inc
         and 'SpawnDirectedAt453A70(0x335' in inc
         and 'PrepareActionAt453D40(4)' in inc
         and 'SetAuxActionAt40FB40(0xE)' in inc,
         'real original 1F8 FUCOMPP/landing/stage game source altered')
    return src.replace(marker,'#include "FighterScriptedGroundBounce1F8F870.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F870-whole.cpp';obj=O/'Boss005214B0-F870-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=env,capture_output=True,text=True,timeout=300)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'whole selected fighter 1F8 normal VC7.1 compile failed '+(run.stdout+run.stderr)[-740:])
    return obj

def main():
    rd=ld('f870rd','compare-coff-function.py')
    ac=ld('f870ac','report-fighter-action-handlers.py')
    f834=ld('f870f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f870f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f870f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f870f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f870f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f870f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f870f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f870f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f870f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f870f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f870f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f870f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f870f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f870f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f870f863','verify-scripted-fighter-short-19c19e-f863.py')
    f865=ld('f870f865','verify-scripted-fighter-sustain-1a0-f865.py')
    f866=ld('f870f866','verify-scripted-fighter-doubleprojectile-1f4-f866.py')
    f867=ld('f870f867','verify-scripted-fighter-staged-1f5-f867.py')
    f868=ld('f870f868','verify-scripted-fighter-conditional-1f6-f868.py')
    f869=ld('f870f869','verify-scripted-fighter-conditional-1f7-f869.py')
    zero=ld('f870zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f870sw','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original whole fighter/afterRET DATA identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x1f8],by[0x1f9]-by[0x1f8]),by[0x1f8]))
    need(len(original)==143 and by[0x1f9]-by[0x1f8]==469
         and original[23].mnemonic=='fld' and original[23].size==6
         and original[23].op_str=='dword ptr [0x65782c]'
         and original[24].mnemonic=='fld' and original[24].size==3
         and original[24].op_str.endswith('+ 0x48]')
         and original[25].mnemonic=='fucompp'
         and original[27].op_str=='ah, 0x44'
         and original[31].op_str=='dword ptr [0x658058]'
         and original[66].op_str=='0x40fb40'
         and original[69].op_str=='0x52cb4f'
         and original[89].op_str.endswith(', 0x41000000')
         and original[91].op_str.endswith(', 0x41400000')
         and original[93].op_str.endswith(', 0x3f4ccccd')
         and original[104].op_str=='0x7f'
         and original[106].op_str=='0x453c80'
         and original[125].op_str=='0x335'
         and original[127].op_str=='0x453a70'
         and original[130].op_str=='0x453d40'
         and original[141].op_str=='0x40fb40'
         and original[142].op_str=='0x52cb4f',
         'real original 1F8 game x87/branch/sprite physical source changed')
    obj=compile_one(create_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(29210,8180,1056,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current selected F870 whole VC7.1 source/PE/ABI geometry changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all original five 901B packed afterRET tables unverified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x1fa')
           and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=143,'following true original 1F9 marker missing')
    k=marks[0];case=ins[k-143:k]
    physical=f834.physical_case(rd,pe,d,code,refs,case,by,0x1f8,469,15,BAD,0x1f9,f820)
    need(physical['native_complete_x86']==143
         and physical['original_native_enclosing_parent_JMP_exit_ordinals']==[69,142]
         and case[69].op_str==case[142].op_str==hex(ret-4)
         and case[23].mnemonic=='fld' and case[23].size==6
         and case[24].mnemonic=='fld' and case[24].size==3
         and case[25].mnemonic=='fucompp'
         and case[27].op_str=='ah, 0x44'
         and case[104].op_str=='0x7f'
         and case[125].op_str=='0x335',
         'original 1F8 nested FUCOMPP widths, stage sprites or giant exits differ')
    lo=case[0].address
    fields=[r for r in refs if lo<=r['offset']<case[-1].address+case[-1].size]
    raw=rd.pe_bytes_at(pe,by[0x1f8],469)
    mask=f820.physical_fields(rd,raw,by[0x1f8],fields,lo,15)
    need(len(mask)==60,'all fifteen original native PE fields not independently checked')
    field_offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],case[ordinal]
        f=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(f)==1 and f[0]['local_symbol_offset'] is None
             and f[0]['addend']==0
             and f[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in f[0]['symbol']
             and f[0]['offset']-lo==a.address-by[0x1f8]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
             'real original 1F8 physical PE field address/target moved at '+str(ordinal))
        field_offsets.append(f[0]['offset']-lo)
    need(field_offsets==OFFSETS and len(BAD)==88
         and all(j in BAD for j in (240,241,465,466)),
         'original 1F8 PE field/JMP negatives unexpectedly reclassified')
    # Recheck all 41 earlier original switch case interiors in
    # newly compiled whole parent. No independent inner-function credit.
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
      (0x1f4,448,136,14,f866.BAD,0x1f5),
      (0x1f5,628,195,17,f867.BAD,0x1f6),
      (0x1f6,372,111,12,f868.BAD,0x1f7),
      (0x1f7,307,90,11,f869.WRONG,0x1f8)]
    previous=ins[k-143-sum(x[2] for x in late):k-143]
    cursor=0;late_cases=[]
    for a,nb,nx,nf,bad,nxt in late:
        section=previous[cursor:cursor+nx];cursor+=nx
        p=f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820)
        if a==0x1a0:
            need(section[3].op_str==section[7].op_str==hex(section[22].address),
                 'actual original 1A0 multiply scope violated')
        late_cases.append(p)
    need(cursor==len(previous),'21 preceding real GPR game cases truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
    left=k-143-sum(x[2] for x in late)
    prefix=ins[left-sum(x[2] for x in early):left]
    cursor=0;early_cases=[]
    for a,nb,nx,nf,bad,nxt in early:
        section=prefix[cursor:cursor+nx];cursor+=nx
        early_cases.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(prefix),'20 old native original state cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tailmask=f820.physical_fields(rd,tail,0x52cb25,
             [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[i for i in range(46) if i not in tailmask and tail[i]!=code[ret-46+i]]
    need(wrong_tail==[],'native 46B common getter expected 34/34 real nonfield equality')
    out={
      'original_giant_fighter':'0x005214B0','original_whole_callable_CODE_B':46755,
      'new_generated_entire_source_callable_CODE_B':ret,
      'actual_original_1F8_whole_native_case':physical,
      'original_1F8_field_offsets':field_offsets,
      'original_equality_x87_load_order':'FLD global65782C 6B, FLD member48 3B, FUCOMPP',
      'original_1F8_wrong_native_GPR_nonfield_B':84,
      'two_original_giant_final_JMP_wrong_pairs':[240,241,465,466],
      'twentyone_late_original_case_sources_rechecked':late_cases,
      'twenty_early_original_case_sources_rechecked':early_cases,
      'original_getter_46B_native_nonrelocation_equal':'34/34',
      'original_native_getter_PE_REL32_fields':3,
      'all_five_original_packed_901B_afterRET_tables_rechecked':True,
      'original_switch_afterRET_DATA_B':901,'original_entire_giant_exact':False,
      'new_accepted_whole_callable_CODE_B':0,'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_giant_exact'] is False
    print('F870 original 1F8 469B/143x86/15 original physical PE fields with nested global-first FUCOMPP, stage3 raw7F/stage7 sprite335, stage15 auxE. Whole source 29210B/8180x86; 84 genuine register and four enclosing-original-giant JMP bytes wrong. All 41 previous real source cases, common 46B getter 34/34 and five packed 901B DATA tables verified; whole native fighter NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F870 whole original fighter 1F8 FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
