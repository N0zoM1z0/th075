#!/usr/bin/env python3
"""F873: two whole original 1FB/1FC 253B/70x86, 6 PE fields each.

Both real sibling states BEGIN with original height-positive ground
damping global658350 (before stage0 initialization), then stage0
Reset/counters, stage6 counters reset, state0 action getter and
stage6 POS15f. Under VC7.1 one entire newly compiled fighter
has all native instruction mnemonics/widths/PE fields correct.
Each case remains 46 genuine GPR byte negatives and two whole-
giant final JMP bytes wrong. Recheck all 44 preceding game cases,
the native common getter and five original 901B packed tables.
Never merge the two true native original entrypoints or count
them as independent exact function CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f873-scripted-pair1fb-1fc'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
WRONG=[1,4,20,23,32,35,38,41,57,60,67,71,74,78,82,85,97,101,109,112,119,122,129,133,136,141,145,148,152,156,164,167,174,177,193,195,199,202,216,220,223,228,232,235,239,242,249,250]
FIELDS={2:(0x65782c,'g_ThresholdAt0065782C'),
        8:(0x658350,'g_F873GroundDropAt00658350'),
        13:(0x65782c,'g_ThresholdAt0065782C'),
        28:(0x453e20,'ResetAt453E20'),
        50:(0x40fa30,'GetNativeActionAt40FA30'),
        58:(0x40fac0,'SetNativeActionAt40FAC0')}
OFFSETS=[8,27,45,92,187,211]

def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,fn):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/fn)
    need(spec is not None and spec.loader is not None,'original PE helper missing '+fn)
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m);return m

def source():
    O.mkdir(parents=True,exist_ok=True)
    p=R/'.analysis/f872-scripted-pair1f9-1fa/Boss005214B0-F872-whole.cpp'
    receipt=R/'.analysis/f872-scripted-pair1f9-1fa/verified-summary.json'
    if not p.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-float-volley-pair-f872.py')],
             cwd=R,text=True,capture_output=True,timeout=1400)
        (O/'prior-f872-native.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'prior original 1F9/1FA native source proof failed '+(cp.stdout+cp.stderr)[-710:])
    old=json.loads(receipt.read_text())
    need(old['generated_full_source_callable_CODE_B']==29634
         and old['original_giant_entire_function_exact'] is False,
         'previous 1F9/1FA original whole-game physical receipt altered')
    src=p.read_text()
    for a in (0x1fb,0x1fc):
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        inc=(R/f'probes/FighterScriptedRecovery{a:X}F873.inc').read_text()
        need(src.count(marker)==1
             and inc.count(f'case 0x{a:X}:')==1 and inc.count('return;')==1
             and inc.index('POS=POS-g_F873GroundDropAt00658350;') <
                 inc.index('ResetAt453E20();')
             and inc.count('S16(0x62)==6 && S16(0x64)==0')==2
             and inc.count('I32(0x7C)=0')==2
             and inc.count('FLAG=0;')==2
             and 'SetNativeActionAt40FAC0(0);' in inc
             and 'POS=15.0f' in inc,
             'actual original 1FB/1FC physics-first/real owner stage C++ source wrong '+hex(a))
        src=src.replace(marker,f'#include "FighterScriptedRecovery{a:X}F873.inc"',1)
    return 'extern float g_F873GroundDropAt00658350;\n'+src

def compile_one(src):
    cpp=O/'Boss005214B0-F873-whole.cpp'
    obj=O/'Boss005214B0-F873-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=300)
    (O/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'whole VC7.1 original recovery-pair compile failed '+(cp.stdout+cp.stderr)[-680:])
    return obj

def main():
    rd=ld('f873rd','compare-coff-function.py')
    ac=ld('f873ac','report-fighter-action-handlers.py')
    f834=ld('f873f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f873f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f873f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f873f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f873f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f873f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f873f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f873f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f873f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f873f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f873f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f873f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f873f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f873f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f873f863','verify-scripted-fighter-short-19c19e-f863.py')
    f865=ld('f873f865','verify-scripted-fighter-sustain-1a0-f865.py')
    f866=ld('f873f866','verify-scripted-fighter-doubleprojectile-1f4-f866.py')
    f867=ld('f873f867','verify-scripted-fighter-staged-1f5-f867.py')
    f868=ld('f873f868','verify-scripted-fighter-conditional-1f6-f868.py')
    f869=ld('f873f869','verify-scripted-fighter-conditional-1f7-f869.py')
    f870=ld('f873f870','verify-scripted-fighter-bounce-1f8-f870.py')
    f872=ld('f873f872','verify-scripted-fighter-float-volley-pair-f872.py')
    zero=ld('f873zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f873sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original whole fighter executable/DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(30110,8442,1078,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'one selected full fighter parent VC7.1 CODE/x86/ABI shape changed')
    ds,ss,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(ds>0 and ss>0 and maps>0,'all five original packed afterRET tables not checked')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0x1fe')
          and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=140,'true next 1FD marker missing')
    k=marks[0]
    new=[]
    for a,nxt,back in ((0x1fb,0x1fc,140),(0x1fc,0x1fd,70)):
        src=ins[k-back:k-back+70]
        orig=list(d.disasm(rd.pe_bytes_at(pe,by[a],by[nxt]-by[a]),by[a]))
        need(len(orig)==70 and by[nxt]-by[a]==253
             and orig[0].mnemonic=='mov' and orig[1].mnemonic=='fld'
             and orig[2].op_str=='dword ptr [0x65782c]'
             and orig[8].op_str=='dword ptr [0x658350]'
             and orig[20].mnemonic=='movsx'
             and orig[28].mnemonic=='call'
             and orig[37].op_str.endswith(', 6')
             and orig[61].op_str.endswith(', 6')
             and orig[68].op_str.endswith(', 0x41700000')
             and orig[69].op_str=='0x52cb4f',
             'real original 1FB/1FC actor physics-before-init or stage6 changed '+hex(a))
        physical=f834.physical_case(rd,pe,d,code,refs,src,by,a,253,6,WRONG,nxt,f820)
        need(physical['native_complete_x86']==70
             and physical['original_native_enclosing_parent_JMP_exit_ordinals']==[69]
             and src[-1].op_str==hex(ret-4)
             and src[1].mnemonic=='fld'
             and src[2].mnemonic=='fcomp'
             and src[8].mnemonic=='fsub'
             and src[68].op_str.endswith(', 0x41700000'),
             'physical source did not preserve native 1FB/1FC motion branch and giant end')
        lo=src[0].address
        fields=[r for r in refs if lo<=r['offset']<src[-1].address+src[-1].size]
        mask=f820.physical_fields(rd,rd.pe_bytes_at(pe,by[a],253),by[a],fields,lo,6)
        need(len(mask)==24,'six original native PE fields not physically validated '+hex(a))
        offsets=[]
        for ord,(target,sym) in FIELDS.items():
            x,y=orig[ord],src[ord]
            ff=[r for r in fields if y.address<=r['offset']<y.address+y.size]
            need(len(ff)==1 and ff[0]['addend']==0
                 and ff[0]['local_symbol_offset'] is None
                 and ff[0]['type']==('REL32' if x.mnemonic=='call' else 'DIR32')
                 and sym in ff[0]['symbol']
                 and ff[0]['offset']-lo==x.address-by[a]+x.size-4
                 and x.op_str==(f'0x{target:x}' if x.mnemonic=='call'
                                   else f'dword ptr [0x{target:x}]'),
                 'original 1FB/1FC physical PE field incorrect '+hex(a)+' '+str(ord))
            offsets.append(ff[0]['offset']-lo)
        need(offsets==OFFSETS and len(WRONG)==48 and WRONG[-2:]==[249,250],
             'real original GPR/native epilogue error geometry changed')
        new.append({'case':hex(a),'native':physical,'original_field_offsets':offsets,
          'original_true_GPR_wrong_B':46,
          'original_giant_final_JMP_wrong_offsets':[249,250]})
    # Previous 44 source backed complete original switch actions in same
    # freshly compiled entire VC7.1 parent, not independent leaf code.
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
      (0x1f8,469,143,15,f870.BAD,0x1f9),
      (0x1f9,227,65,7,f872.BAD,0x1fa),
      (0x1fa,227,65,7,f872.BAD,0x1fb)]
    prior=ins[k-140-sum(x[2] for x in late):k-140]
    cursor=0;older=[]
    for a,nb,nx,nf,bad,nxt in late:
        seg=prior[cursor:cursor+nx];cursor+=nx
        checked=f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,bad,nxt,f820)
        if a==0x1a0:
            need(seg[3].op_str==seg[7].op_str==hex(seg[22].address),
                 'true original 1A0 native guarded scale source drift')
        older.append(checked)
    need(cursor==len(prior),'24 late original PE-backed game actions truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                       (0x135,278,82,7,[274,275],0x136)]
    left=k-140-sum(x[2] for x in late)
    beginning=ins[left-sum(x[2] for x in early):left]
    cursor=0;ancient=[]
    for a,nb,nx,nf,bad,nxt in early:
        seg=beginning[cursor:cursor+nx];cursor+=nx
        ancient.append(f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(beginning),'20 early original real PE case sources truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
              [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    need(len(mask)==12 and all(tail[j]==code[ret-46+j] for j in range(46) if j not in mask),
         'common native getter original 34/34 nonrelocation byte equality changed')
    output={'original_whole_fighter':'0x005214B0',
       'original_callable_native_CODE_B':46755,
       'new_generated_full_source_callable_CODE_B':ret,
       'two_native_original_1FB_1FC_complete_cases':new,
       'native_two_cases_actual_CODE_B_total':506,
       'native_two_cases_actual_x86_total':140,
       'native_two_cases_actual_PE_field_total':12,
       'actual_game_source_physics_before_stage0_reset':True,
       'previous_24_late_original_game_case_sources_rechecked':older,
       'previous_20_early_original_game_case_sources_rechecked':ancient,
       'original_shared_getter_46B_nonfield_equal':'34/34',
       'original_getter_physically_typed_PE_calls':3,
       'original_five_packed_901B_afterRET_tables_rechecked':True,
       'original_separate_afterRET_DATA_B':901,
       'original_entire_game_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(output,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_game_giant_exact'] is False
    print('F873 native 1FB/1FC each complete 253B/70-x86/6 real PE refs physics-first and stage6 POS15 in selected entire 30110B/8442-x86 fighter. Each 46 actual original GPR operand bytes +2 giant JMP bytes remain nonexact. Previous 44 physical original cases, 46B getter 34/34 and five 901B packed DATA tables verified. Whole original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F873 physical original 1FB/1FC whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
