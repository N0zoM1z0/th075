#!/usr/bin/env python3
"""F872: two original 227B/65-x86/7 PE-field float volleys 1F9/1FA.

Each actor's original stage2 owner-state3 fires float sprite32,
facing*50 versus*36 with distinct Y globals 6598BC/659310,
prepares animation20, updates real owner+0x82 then moves to
1FB vs1FC. Genuine whole-giant source naturally allocates
two distinct FILD x87 scratch EBP-0x70 vs -0x74. Compile ONLY
the current affected normal VC7.1 giant. Original native 65-x86
mnemonics/sizes and seven source PE call/global fields align,
but 35 real register bytes and two giant epilogue JMP byte pairs
PER case remain wrong. All 42 earlier source-backed original
cases, original packed 901B afterRET DATA and shared getter
rechecked. Full original giant NONEXACT, no separate leaf credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f872-scripted-pair1f9-1fa'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,63,67,70,75,78,86,89,91,93,96,109,113,116,119,125,128,155,158,165,186,187,200,202,206,209,223,224]
SHAPES={
 0x1f9:(0x1fa,50,0x6598bc,0x1fb,0x70,'g_F872Volley1F9YAt006598BC'),
 0x1fa:(0x1fb,36,0x659310,0x1fc,0x74,'g_F872Volley1FAYAt00659310'),
}
FIELD_OFFSETS=[26,100,140,150,181,194,218]
FIELD_ORDINALS={
 9:(0x453e20,'ResetAt453E20'),
 29:(None,None),
 43:(0x453c80,'SpawnAt453C80'),
 46:(0x453d60,'PrepareActionAt453D60'),
 52:(0x40fac0,'SetNativeActionAt40FAC0'),
 55:(0x40fa30,'GetNativeActionAt40FA30'),
 63:(0x40fac0,'SetNativeActionAt40FAC0')
}
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,filename):
    s=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(s is not None and s.loader is not None,'missing original PE helper '+filename)
    mod=importlib.util.module_from_spec(s);sys.modules[tag]=mod;s.loader.exec_module(mod);return mod

def current_source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f870-scripted-state1f8/Boss005214B0-F870-whole.cpp'
    proof=R/'.analysis/f870-scripted-state1f8/verified-summary.json'
    if not prev.exists() or not proof.exists():
        run=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-bounce-1f8-f870.py')],
             cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'f870-prior-proof.log').write_text(run.stdout+run.stderr)
        need(run.returncode==0,'prior original 1F8 selected source PE failed '+(run.stdout+run.stderr)[-800:])
    old=json.loads(proof.read_text())
    need(old['new_generated_entire_source_callable_CODE_B']==29210
         and old['original_entire_giant_exact'] is False,
         'prior whole F870 native source receipt inconsistent')
    src=prev.read_text()
    need('SpawnAt453C80(int,float,float,char,int)' in src,'actual native float-shot method signature missing')
    prefix=('extern float g_F872Volley1F9YAt006598BC;\n'
            'extern float g_F872Volley1FAYAt00659310;\n')
    for a,(nxt,mult,yg,target,scratch,name) in SHAPES.items():
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        inc=(R/f'probes/FighterScriptedVolley{a:X}F872.inc').read_text()
        need(src.count(marker)==1 and inc.count(f'case 0x{a:X}:')==1
             and inc.count('return;')==2
             and f'*{mult})+F32(0x44)' in inc
             and name in inc and 'SpawnAt453C80(0x32' in inc
             and 'S16(0x62)==2 && I32(0x7C)==3' in inc
             and '*reinterpret_cast<signed short*>(OWNER+0x82)=0x1E;' in inc
             and f'SetNativeActionAt40FAC0(0x{target:X})' in inc,
             'actual original stage2 owner/volley C++ source changed '+hex(a))
        src=src.replace(marker,f'#include "FighterScriptedVolley{a:X}F872.inc"',1)
    return prefix+src

def compile_one(src):
    cpp=O/'Boss005214B0-F872-whole.cpp';obj=O/'Boss005214B0-F872-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=env,capture_output=True,text=True,timeout=330)
    (O/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'full original stage2 pair whole normal C++ compile failed '+(cp.stdout+cp.stderr)[-710:])
    return obj

def main():
    rd=ld('f872rd','compare-coff-function.py')
    ac=ld('f872ac','report-fighter-action-handlers.py')
    f834=ld('f872f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f872f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f872f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f872f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f872f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f872f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f872f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f872f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f872f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f872f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f872f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f872f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f872f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f872f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f872f863','verify-scripted-fighter-short-19c19e-f863.py')
    f865=ld('f872f865','verify-scripted-fighter-sustain-1a0-f865.py')
    f866=ld('f872f866','verify-scripted-fighter-doubleprojectile-1f4-f866.py')
    f867=ld('f872f867','verify-scripted-fighter-staged-1f5-f867.py')
    f868=ld('f872f868','verify-scripted-fighter-conditional-1f6-f868.py')
    f869=ld('f872f869','verify-scripted-fighter-conditional-1f7-f869.py')
    f870=ld('f872f870','verify-scripted-fighter-bounce-1f8-f870.py')
    zero=ld('f872zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f872sw','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original Japanese fighter PE whole CODE/afterRET identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(current_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(29634,8306,1068,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'one selected whole C++ parent/COFF/x86/ABI changed')
    ds,ss,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(ds>0 and ss>0 and maps>0,'all five original packed 901B tables not verified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0x1fc')
          and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=130,'next original 1FB state sentinel missing')
    k=marks[0]
    new=[]
    for a,back in ((0x1f9,130),(0x1fa,65)):
        nxt,mult,yg,target,scratch,symbol=SHAPES[a]
        src=ins[k-back:k-back+65]
        physical=f834.physical_case(rd,pe,d,code,refs,src,by,a,227,7,BAD,nxt,f820)
        orig=list(d.disasm(rd.pe_bytes_at(pe,by[a],227),by[a]))
        need(len(orig)==65
             and physical['original_native_enclosing_parent_JMP_exit_ordinals']==[53,64]
             and src[53].op_str==src[64].op_str==hex(ret-4)
             and orig[34].op_str.endswith(', '+hex(mult))
             and orig[35].op_str.startswith('dword ptr [ebp - 0x'+hex(scratch)[2:]+']')
             and src[35].op_str.startswith('dword ptr [ebp - 0x'+hex(scratch)[2:]+']')
             and src[36].mnemonic=='fild'
             and src[49].mnemonic=='mov' and src[49].op_str.endswith(', 0x1e')
             and orig[50].op_str==hex(target)
             and src[50].op_str==hex(target),
             'native original staged owner/float scratch B' +hex(a))
        lo=src[0].address
        field=[r for r in refs if lo<=r['offset']<src[-1].address+src[-1].size]
        mask=f820.physical_fields(rd,rd.pe_bytes_at(pe,by[a],227),by[a],field,lo,7)
        need(len(mask)==28,'seven original physical PE fields not checked '+hex(a))
        offsets=[]
        for ord,(dst,sym) in FIELD_ORDINALS.items():
            if ord==29:dst,sym=yg,symbol
            x,y=orig[ord],src[ord]
            hits=[r for r in field if y.address<=r['offset']<y.address+y.size]
            need(len(hits)==1 and hits[0]['addend']==0
                 and hits[0]['local_symbol_offset'] is None
                 and hits[0]['type']==('REL32' if x.mnemonic=='call' else 'DIR32')
                 and sym in hits[0]['symbol']
                 and hits[0]['offset']-lo==x.address-by[a]+x.size-4
                 and x.op_str==(f'0x{dst:x}' if x.mnemonic=='call' else f'dword ptr [0x{dst:x}]'),
                 'physical native PE field target differs at '+hex(a)+' ordinal '+str(ord))
            offsets.append(hits[0]['offset']-lo)
        need(offsets==FIELD_OFFSETS and len(BAD)==39
             and all(z in BAD for z in (186,187,223,224)),
             'original staged volley two-parent-JMP or typed PE differences changed')
        new.append({'case':hex(a),'native':physical,'field_offsets':offsets,
                    'native_float_FILD_scratch_EBP_minus':hex(scratch),
                    'real_face_scale':mult,'actual_Y_global':hex(yg),
                    'true_next_action':hex(target),
                    'genuine_GPR_wrong_B':35,
                    'giant_final_JMP_wrong_offsets':[186,187,223,224]})
    # One whole C++ compiler output also rechecks all previously
    # sourced full 43? (22 late + 20 early =42) native case interiors.
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
      (0x1f7,307,90,11,f869.WRONG,0x1f8),
      (0x1f8,469,143,15,f870.BAD,0x1f9)]
    before=ins[k-130-sum(x[2] for x in late):k-130]
    cursor=0;old=[]
    for a,nb,nx,nf,bad,nxt in late:
        section=before[cursor:cursor+nx];cursor+=nx
        checked=f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820)
        if a==0x1a0:
            need(section[3].op_str==section[7].op_str==hex(section[22].address),
                 'native stage-zero mul-lifetime 1A0 changed')
        old.append(checked)
    need(cursor==len(before),'22 preceding late original cases truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                       (0x135,278,82,7,[274,275],0x136)]
    left=k-130-sum(x[2] for x in late)
    before2=ins[left-sum(x[2] for x in early):left]
    cursor=0;old2=[]
    for a,nb,nx,nf,bad,nxt in early:
        section=before2[cursor:cursor+nx];cursor+=nx
        old2.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(before2),'20 older source-backed original PE cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
           [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[],'shared native getter 46B expected 34/34 nonfield matches')
    out={'original_whole_fighter':'0x005214B0',
        'original_native_whole_callable_CODE_B':46755,
        'generated_full_source_callable_CODE_B':ret,
        'two_original_1F9_1FA_complete_cases':new,
        'native_original_two_stage2_volley_CODE_B_total':454,
        'native_original_both_stage2_x86_total':130,
        'real_original_two_PE_field_total':14,
        'prior_22_late_original_native_case_sources_checked':old,
        'prior_20_early_original_native_case_sources_checked':old2,
        'original_getter_46B_nonfield_equal':'34/34',
        'original_getter_real_PE_call_fields':3,
        'five_original_901B_packed_afterRET_tables_verified':True,
        'native_afterRET_separate_DATA_B':901,
        'original_giant_entire_function_exact':False,
        'new_accepted_whole_callable_CODE_B':0,
        'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_giant_entire_function_exact'] is False
    print('F872 original 1F9/1FA each 227B/65x86/7 true PE refs. Actual FILD EBP-0x70 and -0x74 native scratch, Y globals6598BC/659310, facing*50/*36, next1FB/1FC in whole 29634B/8306-x86 parent. Each 35 register +4 giant-JMP byte negatives. 42 preceding native cases, 901B packed tables and 46B getter 34/34 physically reverified. Whole original giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F872 selected original whole fighter volley pair FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
