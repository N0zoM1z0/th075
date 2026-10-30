#!/usr/bin/env python3
"""F865 original 1A0 235B/67x86/5 PE fields, real float lvalue source.

Standalone original action1A0 begins with state0/frame0,
scales POS and POS54 via native global00658348 and x87,
ground POS48+POS54 threshold and clears actual movement,
native stage>3 damping and stage4 state-bit update.
Real C++ lvalue read of POS54 times global keeps 3B FLD this+54
then 6B FMUL native global, unlike bare macro's reversed widths
and invalid PE field offset (dangerous masked-byte false positive).
Build only the affected whole fighter, verify all five real PE
field offsets/types/destinations and 36 preceding native cases,
all 901B packed afterRET DATA, shared getter true GPR phase.
Original giant NONEXACT, no case-only CODE acceptance.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f865-scripted-stage1a0'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
WRONG=[1,5,8,12,16,19,23,27,35,38,45,48,57,60,63,66,75,78,81,84,87,90,106,109,116,119,126,129,136,140,143,148,151,154,157,160,163,175,177,181,184,198,202,205,210,214,217,221,224,231,232]
FIELDS={
 14:(0x658348,'g_F865SustainScaleAt00658348'),
 19:(0x658348,'g_F865SustainScaleAt00658348'),
 26:(0x65782c,'g_ThresholdAt0065782C'),
 47:(0x40fa30,'GetNativeActionAt40FA30'),
 55:(0x40fac0,'SetNativeActionAt40FAC0'),
}

def need(x,msg):
    if not x:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'missing original PE helper '+name)
    mod=importlib.util.module_from_spec(sp);sys.modules[tag]=mod;sp.loader.exec_module(mod)
    return mod

def current_source(rd,pe,d,by):
    O.mkdir(parents=True,exist_ok=True)
    prior_src=R/'.analysis/f863-scripted-19c19e/Boss005214B0-F863-whole.cpp'
    prior_proof=R/'.analysis/f863-scripted-19c19e/verified-summary.json'
    if not prior_src.is_file() or not prior_proof.is_file():
        p=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-short-19c19e-f863.py')],
              cwd=R,capture_output=True,text=True,timeout=1300)
        (O/'f863-source-fallback.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,'prior F863 original game PE verification failed '+(p.stdout+p.stderr)[-670:])
    old=json.loads(prior_proof.read_text())
    need(old['new_generated_entire_source_CODE_B']==26841
         and old['original_whole_giant_exact'] is False,
         'prior original 19C/19E source receipt invalid')
    native=list(d.disasm(rd.pe_bytes_at(pe,by[0x1a0],by[0x1f4]-by[0x1a0]),by[0x1a0]))
    need(len(native)==67 and by[0x1f4]-by[0x1a0]==235
         and native[13].mnemonic=='fld' and native[13].size==3
         and native[14].mnemonic=='fmul' and native[14].op_str=='dword ptr [0x658348]'
         and native[18].mnemonic=='fld' and native[18].size==3
         and native[19].mnemonic=='fmul' and native[19].size==6
         and native[19].op_str=='dword ptr [0x658348]'
         and native[26].op_str=='dword ptr [0x65782c]'
         and native[28].op_str=='ah, 0x41'
         and native[38].op_str.endswith(', 3')
         and native[47].op_str=='0x40fa30'
         and native[55].op_str=='0x40fac0'
         and native[58].op_str.endswith(', 4')
         and native[-1].op_str=='0x52cb4f',
         'actual original 1A0 native instruction/global/width changed')
    src=prior_src.read_text()
    marker='        case 0x1A0: g_FighterProbeMarker = 417; break;'
    inc=(R/'probes/FighterScriptedSustain1A0F865.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x1A0:')==1
         and inc.count('return;')==1
         and 'POS54=(*(&POS54))*g_F865SustainScaleAt00658348;' in inc
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc
         and 'S16(0x62)>3' in inc
         and 'SetNativeActionAt40FAC0(9)' in inc,
         'authentic 1A0 source float lvalue, native state/threshold changed')
    return 'extern float g_F865SustainScaleAt00658348;\n'+src.replace(marker,'#include "FighterScriptedSustain1A0F865.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F865-whole.cpp';obj=O/'Boss005214B0-F865-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=env,capture_output=True,text=True,timeout=290)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'whole fighter 1A0 VC7.1 original source failed '+(run.stdout+run.stderr)[-730:])
    return obj

def main():
    rd=ld('f865rd','compare-coff-function.py')
    ac=ld('f865ac','report-fighter-action-handlers.py')
    f834=ld('f865f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f865f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f865f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f865f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f865f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f865f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f865f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f865f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f865f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f865f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f865f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f865f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f865f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f865f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f865f863','verify-scripted-fighter-short-19c19e-f863.py')
    zero=ld('f865zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f865sw','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original whole fighter / DATA identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(current_source(rd,pe,d,by))
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    need((ret,len(I),len(refs),len(code)-ret)==(27061,7515,992,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'new selected 1A0 entire VC7.1 parent CODE/x86/COFF/ABI changed')
    dens,spars,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(dens>0 and spars>0 and maps>0,
         'original five packed 901B switch DATA tables not independently verified')
    marker=[j for j,x in enumerate(I) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x1f5')
           and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=67,'following original 1F4 source sentinel missing')
    k=marker[0];gen=I[k-67:k]
    case=f834.physical_case(rd,pe,d,code,refs,gen,by,0x1a0,235,5,WRONG,0x1f4,f820)
    need(case['native_complete_x86']==67
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[66]
         and gen[66].op_str==hex(ret-4)
         and gen[18].mnemonic=='fld' and gen[18].size==3
         and gen[18].op_str.endswith('+ 0x54]')
         and gen[19].mnemonic=='fmul' and gen[19].size==6
         and gen[26].mnemonic=='fcomp'
         and gen[38].op_str.endswith(', 3'),
         'real original 1A0 x87 float scale/threshold codegen wrong')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x1a0],235),by[0x1a0]))
    need(original[3].op_str==original[7].op_str==hex(original[22].address)
         and gen[3].op_str==gen[7].op_str==hex(gen[22].address)
         and gen[3].op_str!=hex(gen[12].address),
         'stage0 native actor JNE must SKIP BOTH real x87 multiplier groups')

    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],gen[ordinal]
        found=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['local_symbol_offset'] is None
             and found[0]['addend']==0
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in found[0]['symbol']
             and found[0]['offset']-gen[0].address==a.address-by[0x1a0]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                  else f'dword ptr [0x{target:x}]'),
             'original 1A0 physical PE global/float/call field wrong at x86 '+str(ordinal))
        offsets.append(found[0]['offset']-gen[0].address)
    need(offsets==[52,70,94,169,193],
         'real original float multiplicand fields shifted; do not mask invalid PE bytes')
    # False original codegen input: plain POS54 macro reverses real
    # global/member x87 field widths. It has an invalid 2nd original
    # physical DIR32 field at +0x43 rather than native +0x46.
    false_obj=O/'native.obj'
    if not false_obj.is_file():
        assert False,'F865 plain-macro control evidence missing'
    false_code,false_refs=rd.object_function(false_obj,SYM)
    false_I=[]
    for x in d.disasm(false_code,0):
        false_I.append(x)
        if x.mnemonic=='ret':break
    false_k=next(j for j,x in enumerate(false_I) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0x1f5')
          and any('g_FighterProbeMarker' in r['symbol']
                  and x.address<=r['offset']<x.address+x.size for r in false_refs))
    false_gen=false_I[false_k-67:false_k]
    fbase=false_gen[0].address
    false_fields=[r['offset']-fbase for r in false_refs if fbase<=r['offset']<false_gen[-1].address+false_gen[-1].size]
    need((false_gen[18].size,false_gen[19].size)==(6,3)
         and false_fields==[52,67,94,169,193],
         'invalid plain macro should reverse original x87 width/physical field')
    # Recheck all 36 independently physical native switch state
    # interiors in THIS one new father (not separate exact units).
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
      (0x19e,122,35,3,f863.WRONG,0x1a0)]
    old=I[k-67-sum(x[2] for x in late):k-67]
    pos=0;recent=[]
    for a,nb,nx,nf,bad,nxt in late:
        sec=old[pos:pos+nx];pos+=nx
        recent.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(pos==len(old),'preceding 16 real original cases truncated')
    earlier=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
    left=k-67-sum(x[2] for x in late)
    prefix=I[left-sum(x[2] for x in earlier):left]
    pos=0;past=[]
    for a,nb,nx,nf,bad,nxt in earlier:
        sec=prefix[pos:pos+nx];pos+=nx
        past.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(pos==len(prefix),'previous twenty original case sources truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
             [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'current original shared getter four honest GPR byte negatives changed')
    out={'real_original_whole_fighter':'0x005214B0',
         'native_original_callable_CODE_B':46755,
         'generated_entire_source_callable_CODE_B':ret,
         'new_original_1A0_native_case':case,
         'original_1A0_actual_physical_PE_field_offsets':offsets,
         'native_float_54_member_then_global_widths':'3B+6B',
         'false_plain_POS54_multiplies_global_then_member_widths':'6B+3B',
         'false_source_original_PE_field_offsets':false_fields,
         'current_1A0_true_GPR_wrong_B':49,
         'original_whole_final_JMP_wrong_offsets':[231,232],
         'previous_sixteen_GPR_affected_native_cases_rechecked':recent,
         'previous_twenty_original_source_game_cases_rechecked':past,
         'native_default_46B_original_GPR_wrong_offsets':wrong_tail,
         'real_five_packed_901B_afterRET_tables_verified':True,
         'separate_original_afterRET_DATA_B':901,
         'original_whole_giant_exact':False,
         'new_accepted_whole_callable_CODE_B':0,
         'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_whole_giant_exact'] is False
    print('F865 native original 1A0 235B/67-x86/5 real PE fields recovered via genuine float54 lvalue; plain source reverses FLD/FMUL widths and moves physical field. Full selected fighter 27061B/7515 x86, 49 real GPR and 2 giant epilogue JMP bytes differ, preceding 36 game cases and FIVE packed 901B switch tables physical PE verified. Whole original NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F865 original physical 1A0 whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
