#!/usr/bin/env python3
"""F862: real entire original 19A 302B/86x86/8 original PE fields.

The actor 19A begins immediately with POS54-=POS5C, no stage-zero
Reset. One false source inserts stage-zero Reset into 19A: it emits
332B/96x86/9 fields, but its LAST 302B/86x86 matches all GPRs!
Physically reject that cropped false positive; preserve genuine
302B/86x86 55 unmasked nonfield byte negatives, including two
original whole-giant JMP pairs. Verify all preceding 33 original
case PE fields and five 901B packed native afterRET tables in the
one freshly built affected parent. No original case-only CODE credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f862-scripted-stage19a'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BAD=[1,4,7,10,13,16,19,22,25,28,54,57,64,67,74,77,84,85,98,100,104,107,121,125,128,137,141,144,150,153,155,157,160,173,177,180,183,189,192,235,238,245,248,255,258,265,269,272,277,281,284,288,291,298,299]
FIELDS={
 10:(0x65782c,'g_ThresholdAt0065782C'),
 16:(0x40fac0,'SetNativeActionAt40FAC0'),
 25:(0x40fa30,'GetNativeActionAt40FA30'),
 33:(0x40fac0,'SetNativeActionAt40FAC0'),
 48:(0x658268,'g_F701_VolleyYAt00658268'),
 62:(0x453a70,'SpawnFloatXYAt453A70'),
 65:(0x46d000,'StartAnimationAt46D000'),
 68:(0x453d40,'PrepareActionAt453D40'),
}
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,fn):
    s=importlib.util.spec_from_file_location(tag,R/'scripts'/fn)
    need(s is not None and s.loader is not None,'missing pinned original PE helper '+fn)
    m=importlib.util.module_from_spec(s);sys.modules[tag]=m;s.loader.exec_module(m);return m

def native_source(rd,pe,d,by):
    O.mkdir(parents=True,exist_ok=True)
    p=R/'.analysis/f861-scripted-stage198/Boss005214B0-F861-whole.cpp'
    receipt=R/'.analysis/f861-scripted-stage198/verified-summary.json'
    if not p.is_file() or not receipt.is_file():
        previous=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-stage-198-f861.py')],
              cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'f861-prior-fallback.log').write_text(previous.stdout+previous.stderr)
        need(previous.returncode==0,'preceding F861 physical original case failed '+(previous.stdout+previous.stderr)[-650:])
    proof=json.loads(receipt.read_text())
    need(proof['generated_entire_source_callable_CODE_B']==26340
         and proof['whole_original_giant_exact'] is False,
         'previous whole native 198 receipt inconsistent')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x19a],by[0x19c]-by[0x19a]),by[0x19a]))
    need(len(original)==86 and by[0x19c]-by[0x19a]==302
         and original[0].mnemonic=='mov' and original[2].mnemonic=='fld'
         and original[3].mnemonic=='fsub'
         and original[10].op_str=='dword ptr [0x65782c]'
         and original[12].op_str=='ah, 0x41'
         and original[23].op_str=='0x52cb4f'
         and original[36].op_str.endswith(', 5')
         and original[48].op_str=='dword ptr [0x658268]'
         and original[53].op_str.endswith(', 0x3c')
         and original[60].op_str=='0x352'
         and original[62].op_str=='0x453a70'
         and original[65].op_str=='0x46d000'
         and original[68].op_str=='0x453d40'
         and original[70].op_str.endswith(', 0xc0a00000')
         and original[72].op_str.endswith(', 0x41400000')
         and original[74].op_str.endswith(', 0x3f266666')
         and original[85].op_str=='0x52cb4f',
         'actual original 19A PE-ground/float/stage native source changed')
    src=p.read_text()
    marker='        case 0x19A: g_FighterProbeMarker = 411; break;'
    inc=(R/'probes/FighterScriptedStage19AF862.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x19A:')==1
         and inc.count('return;')==2
         and 'ResetAt453E20()' not in inc
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc
         and 'SpawnFloatXYAt453A70(0x352' in inc
         and '(*(&POS48))+g_F701_VolleyYAt00658268' in inc
         and inc.index('StartAnimationAt46D000(0xC8)')<inc.index('PrepareActionAt453D40(3)'),
         'physical actor 19A source incorrectly inherited stage-zero Reset')
    return src.replace(marker,'#include "FighterScriptedStage19AF862.inc"',1)

def compile_one(src,name):
    cpp=O/(name+'.cpp');obj=O/(name+'.obj')
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=env,capture_output=True,text=True,timeout=300)
    (O/(name+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'whole actor 19A VC7.1 candidate build failed '+(run.stdout+run.stderr)[-760:])
    return obj

def main():
    rd=ld('f862rd','compare-coff-function.py')
    ac=ld('f862ac','report-fighter-action-handlers.py')
    f834=ld('f862f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f862f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f862f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f862f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f862f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f862f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f862f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f862f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f862f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f862f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f862f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f862f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f862f860','verify-scripted-fighter-stage-196-f860.py')
    f861=ld('f862f861','verify-scripted-fighter-stage-198-f861.py')
    zero=ld('f862zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f862switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
             if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original giant target native CODE or packed switch DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    source=native_source(rd,pe,d,by)
    obj=compile_one(source,'Boss005214B0-F862-whole')
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(26627,7384,984,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'selected entire 19A original native grammar/ABI/COFF changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all five true native packed afterRET switch tables not verified')
    markers=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x19d')
       and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1,'following original 19C source marker missing')
    k=markers[0]
    gen=ins[k-86:k]
    current=f834.physical_case(rd,pe,d,code,refs,gen,by,0x19a,302,8,BAD,0x19c,f820)
    need(current['native_complete_x86']==86
         and current['original_native_enclosing_parent_JMP_exit_ordinals']==[23,85]
         and gen[23].op_str==gen[85].op_str==hex(ret-4)
         and gen[70].op_str.endswith(', 0xc0a00000')
         and gen[72].op_str.endswith(', 0x41400000')
         and gen[74].op_str.endswith(', 0x3f266666'),
         'original physical actor19A stage5 shot or early ground exit wrong')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x19a],302),by[0x19a]))
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],gen[ordinal]
        ff=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(ff)==1 and ff[0]['local_symbol_offset'] is None
             and ff[0]['addend']==0
             and ff[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in ff[0]['symbol']
             and ff[0]['offset']-gen[0].address==a.address-by[0x19a]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
             'physical original 19A PE field/target moved at '+str(ordinal))
    # Deliberate false positive: the invalid invented stage-zero
    # Reset prefix changes the COMPLETE source extent to 332B/96-x86
    # but slicing LAST 302B/86-x86 misleadingly gives GPR agreement.
    inc=(R/'probes/FighterScriptedStage19AF862.inc').read_text()
    raw_case=inc[inc.index('case 0x19A:'):].strip()
    bad_case=raw_case.replace('case 0x19A: {',
         'case 0x19A: {\n    if (S16(0x62)==0 && S16(0x64)==0) ResetAt453E20();',1)
    need(bad_case.count('ResetAt453E20();')==1,'invalid prefix control not unique')
    false_cpp=source.replace('#include "FighterScriptedStage19AF862.inc"',bad_case,1)
    false_obj=compile_one(false_cpp,'false-stagezero-reset-F862')
    false_code,false_refs=rd.object_function(false_obj,SYM)
    false_ins=[]
    for x in d.disasm(false_code,0):
        false_ins.append(x)
        if x.mnemonic=='ret':break
    false_ret=false_ins[-1].address+false_ins[-1].size
    need((false_ret,len(false_ins),len(false_refs),len(false_code)-false_ret)==(26657,7394,985,901),
         'actual invalid stage-zero prefix compiler full giant output changed')
    false_marks=[j for j,x in enumerate(false_ins) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x19d')
         and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in false_refs)]
    need(len(false_marks)==1,'false prefix target next case shifted')
    fk=false_marks[0]
    false_full=false_ins[fk-96:fk]
    fstart,fend=false_full[0].address,false_full[-1].address+false_full[-1].size
    false_fields=[r for r in false_refs if fstart<=r['offset']<fend]
    cropped=false_ins[fk-86:fk]
    cstart,cend=cropped[0].address,cropped[-1].address+cropped[-1].size
    need(fend-fstart==332 and len(false_full)==96
         and len(false_fields)==9
         and cstart-fstart==30 and cend-cstart==302
         and len(cropped)==86,
         'false positive MUST remain whole 332B/96x86 with one genuine extra call')
    raw=rd.pe_bytes_at(pe,by[0x19a],302)
    mask={j for r in false_refs if cstart<=r['offset']<cend
          for j in range(r['offset']-cstart,r['offset']-cstart+4)}
    cropped_wrong=[j for j in range(302) if j not in mask and raw[j]!=false_code[cstart+j]]
    need(cropped_wrong==[84,85,298,299],
         'invalid prefix cropped source should misleadingly show only whole-giant JMP negatives')
    # 13 preceding full cases re-PE-verified in same selected
    # (non-invalid) normal C++ whole object.
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
       (0x198,199,60,7,f860.BAD,0x19a)]
    prev=ins[k-86-sum(x[2] for x in late):k-86]
    cur=0;recent=[]
    for a,nb,nx,nf,bad,nxt in late:
        section=prev[cur:cur+nx];cur+=nx
        recent.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cur==len(prev),'13 genuine previous states missing original source')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                       (0x135,278,82,7,[274,275],0x136)]
    left=k-86-sum(x[2] for x in late)
    beginning=ins[left-sum(x[2] for x in early):left]
    cur=0;older=[]
    for a,nb,nx,nf,bad,nxt in early:
        section=beginning[cur:cur+nx];cur+=nx
        older.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cur==len(beginning),'20 older native source cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
             [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'native current 19A whole getter 4 honest GPR bytes changed')
    out={'original_whole_fighter':'0x005214B0',
         'native_whole_game_callable_CODE_B':46755,
         'current_selected_full_source_CODE_B':ret,
         'original_19A_whole_interior':current,
         'original_19A_native_PE_field_ordinals':list(FIELDS),
         'real_original_19A_GPR_wrong_B':51,
         'two_original_giant_epilogue_JMP_pairs_wrong_offsets':[84,85,298,299],
         'false_reset_prefix_whole_source_B':fend-fstart,
         'false_reset_prefix_whole_source_x86':len(false_full),
         'false_reset_prefix_physical_source_fields':len(false_fields),
         'false_reset_prefix_misleading_cropped_native_wrong_offsets':cropped_wrong,
         'invalid_false_prefix_is_not_original_whole_source':True,
         'preceding_13_real_original_native_cases_reverified':recent,
         'earlier_20_native_source_cases_physically_checked':older,
         'current_46B_getter_GPR_wrong_offsets':wrong_tail,
         'real_original_five_901B_afterRET_tables_checked':True,
         'native_separate_original_afterRET_DATA_B':901,
         'entire_original_46755B_exact':False,'new_accepted_whole_callable_CODE_B':0,
         'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['invalid_false_prefix_is_not_original_whole_source']
    print('F862 native 19A full 302B/86x86/8 PE fields in whole 26627B/7384-x86, 51 genuine GPR and 4 original giant JMP bytes wrong. False stage-zero Reset creates 332B/96x86/9-call whole source yet cropped final302B falsely looks native apart from JMP; formally REFUSED. Previous 33 real original cases and five 901B packed tables rechecked. Whole giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F862 original 19A whole-parent proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
