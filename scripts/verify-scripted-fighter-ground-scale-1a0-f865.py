#!/usr/bin/env python3
"""F865 full original 1A0 235B/67x86/5 actual PE call/global fields.

Finish 5 original states 198/19A/19C/19E/1A0 occupying 980 real
native CODE bytes, but retain each actual switch entrypoint.
True POS54 left-lvalue multiply prevents reverse FLD/FMul width,
then original native ground zero, later stage>3 drag, state9 and
stage4 flag. Compile only ONE whole affected VC7.1 parent,
verify all five new separately addressed states and 36 earlier
native original case sources/5 packed 901B tables.
Actual 49 nonfield GPR bytes plus two original encompassing-giant
JMP bytes remain; no standalone case or full whole exact CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f865-scripted-1a0'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1, 5, 8, 12, 16, 19, 23, 27, 35, 38, 45, 48, 57, 60, 63, 66, 75, 78, 81, 84, 87, 90, 106, 109, 116, 119, 126, 129, 136, 140, 143, 148, 151, 154, 157, 160, 163, 175, 177, 181, 184, 198, 202, 205, 210, 214, 217, 221, 224, 231, 232]
FIELDS={
 14:(0x658348,'g_F865PhysicsMultiplierAt00658348'),
 19:(0x658348,'g_F865PhysicsMultiplierAt00658348'),
 26:(0x65782c,'g_ThresholdAt0065782C'),
 47:(0x40fa30,'GetNativeActionAt40FA30'),
 55:(0x40fac0,'SetNativeActionAt40FAC0')}
def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'native PE source helper missing '+name)
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m);return m
def selected_source(reader,pe,d,by):
    O.mkdir(parents=True,exist_ok=True)
    src=R/'.analysis/f863-scripted-19c19e/Boss005214B0-F863-whole.cpp'
    receipt=R/'.analysis/f863-scripted-19c19e/verified-summary.json'
    if not src.is_file() or not receipt.is_file():
        p=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-short-19c19e-f863.py')],
             cwd=R,capture_output=True,text=True,timeout=1600)
        (O/'f863-prior-fallback.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,'prior original 19C/19E whole physical PE check failed '+(p.stdout+p.stderr)[-700:])
    previous=json.loads(receipt.read_text())
    need(previous['new_generated_entire_source_CODE_B']==26841
         and previous['original_whole_giant_exact'] is False,
         'previous original 19C/19E native receipt inconsistent')
    n=list(d.disasm(reader.pe_bytes_at(pe,by[0x1a0],by[0x1f4]-by[0x1a0]),by[0x1a0]))
    need(len(n)==67 and by[0x1f4]-by[0x1a0]==235
         and n[13].mnemonic=='fld' and n[13].op_str.endswith('+ 0x50]')
         and n[14].op_str=='dword ptr [0x658348]'
         and n[18].mnemonic=='fld' and n[18].op_str.endswith('+ 0x54]')
         and n[19].op_str=='dword ptr [0x658348]'
         and n[26].op_str=='dword ptr [0x65782c]'
         and n[28].op_str=='ah, 0x41'
         and n[31].op_str.endswith(', 0')
         and n[33].op_str.endswith(', 0')
         and n[35].op_str.endswith(', 0')
         and n[38].op_str.endswith(', 3')
         and n[47].op_str=='0x40fa30'
         and n[55].op_str=='0x40fac0'
         and n[58].op_str.endswith(', 4')
         and n[-1].op_str=='0x52cb4f',
         'native original 1A0 physical x87 scale/motion controlflow changed')
    cpp=src.read_text()
    marker='        case 0x1A0: g_FighterProbeMarker = 417; break;'
    inc=(R/'probes/FighterScriptedGroundScale1A0F865.inc').read_text()
    need('I32(0x7C)=0;\n        POS=POS*g_F865PhysicsMultiplierAt00658348;\n        POS54=(*(&POS54))*g_F865PhysicsMultiplierAt00658348;\n    }' in inc,
         'original stage-zero multiplier lifetime moved OUTSIDE native branch')
    need(cpp.count(marker)==1 and inc.count('case 0x1A0:')==1
         and inc.count('return;')==1
         and inc.count('g_F865PhysicsMultiplierAt00658348')==2
         and 'POS54=(*(&POS54))*g_F865PhysicsMultiplierAt00658348;' in inc
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc
         and 'S16(0x62)>3' in inc
         and 'SetNativeActionAt40FAC0(9)' in inc,
         'real source 1A0 twice-typed x87/ground stage changed')
    return 'extern float g_F865PhysicsMultiplierAt00658348;\n'+cpp.replace(
        marker,'#include "FighterScriptedGroundScale1A0F865.inc"',1)
def compile_one(src,variant='whole'):
    cpp=O/('Boss005214B0-F865-'+variant+'.cpp');obj=O/('Boss005214B0-F865-'+variant+'.obj')
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=env,capture_output=True,text=True,timeout=310)
    (O/('compiler-'+variant+'.log')).write_text(p.stdout+p.stderr)
    need(p.returncode==0,'full selected 1A0 current VC7.1 source failed '+(p.stdout+p.stderr)[-820:])
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
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original selected whole fighter PE identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    need(by[0x1f4]-by[0x198]==980 and all(by[a]<by[nxt] for a,nxt in
         [(0x198,0x19a),(0x19a,0x19c),(0x19c,0x19e),(0x19e,0x1a0),(0x1a0,0x1f4)]),
         'five distinct native original switch handlers must span exactly 980B in PE')
    obj=compile_one(selected_source(rd,pe,d,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(27061,7515,992,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current full original game codegen/COFF/receiver ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all five real 901B afterRET packed switch tables not checked')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x1f5')
        and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=67,
         'next real original 1F4 marker missing')
    k=marks[0]
    sec=ins[k-67:k]
    actual=f834.physical_case(rd,pe,d,code,refs,sec,by,0x1a0,235,5,BAD,0x1f4,f820)
    need(actual['native_complete_x86']==67
         and actual['original_native_enclosing_parent_JMP_exit_ordinals']==[66]
         and sec[-1].op_str==hex(ret-4)
         and sec[13].mnemonic=='fld' and sec[13].size==3
         and sec[14].mnemonic=='fmul' and sec[14].size==6
         and sec[18].mnemonic=='fld' and sec[18].size==3
         and sec[19].mnemonic=='fmul' and sec[19].size==6
         and sec[28].op_str=='ah, 0x41'
         and sec[38].op_str.endswith(', 3'),
         'native 1A0 two original field-first FMUL or ground stage incorrect')
    orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x1a0],235),by[0x1a0]))
    need(orig[3].op_str==orig[7].op_str==hex(orig[22].address)
         and sec[3].op_str==sec[7].op_str==hex(sec[22].address)
         and sec[3].op_str!=hex(sec[12].address),
         'NATIVE guard branches must SKIP both scale operations; wrong scope is not original')

    # NEGATIVE CONTROL: a real but incorrect source spelling moves
    # both floating-point multiplications OUTSIDE the stage0 guard.
    # It retains all 235B/67 x86 and 5 PE fields, but changes the
    # actual game branch destinations at ordinal 3 and 7.
    actual_full_source=(O/'Boss005214B0-F865-whole.cpp').read_text()
    marker='#include "FighterScriptedGroundScale1A0F865.inc"'
    fragment=(R/'probes/FighterScriptedGroundScale1A0F865.inc').read_text()
    scoped=('        I32(0x7C)=0;\n'
            '        POS=POS*g_F865PhysicsMultiplierAt00658348;\n'
            '        POS54=(*(&POS54))*g_F865PhysicsMultiplierAt00658348;\n'
            '    }')
    unscoped=('        I32(0x7C)=0;\n'
              '    }\n'
              '    POS=POS*g_F865PhysicsMultiplierAt00658348;\n'
              '    POS54=(*(&POS54))*g_F865PhysicsMultiplierAt00658348;')
    need(fragment.count(scoped)==1 and actual_full_source.count(marker)==1,
         'original stage0 scope source cannot be checked against wrong AST')
    wrong_fragment=fragment.replace(scoped,unscoped,1)
    wrong_source=actual_full_source.replace(marker,wrong_fragment,1)
    wrong_obj=compile_one(wrong_source,variant='invalid-unconditional-scale')
    wrong_code,wrong_refs=rd.object_function(wrong_obj,SYM)
    wrong_ins=[]
    for x in d.disasm(wrong_code,0):
        wrong_ins.append(x)
        if x.mnemonic=='ret':break
    wrong_ret=wrong_ins[-1].address+wrong_ins[-1].size
    need((wrong_ret,len(wrong_ins),len(wrong_refs),len(wrong_code)-wrong_ret)==(27061,7515,992,901),
         'wrong multiplier scope must remain deceptively same full CODE/x86/COFF shape')
    wrong_mark=[j for j,x in enumerate(wrong_ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x1f5')
       and any('g_FighterProbeMarker' in r['symbol']
              and x.address<=r['offset']<x.address+x.size for r in wrong_refs)]
    need(len(wrong_mark)==1,'wrong scope whole case marker missing')
    wrong_sec=wrong_ins[wrong_mark[0]-67:wrong_mark[0]]
    wrong_bytes=sorted(set(BAD+[10,21]))
    wrong_result=f834.physical_case(rd,pe,d,wrong_code,wrong_refs,wrong_sec,by,
                                   0x1a0,235,5,wrong_bytes,0x1f4,f820)
    need(wrong_result['native_complete_x86']==67
         and wrong_sec[3].op_str==wrong_sec[7].op_str==hex(wrong_sec[12].address)
         and wrong_sec[3].op_str!=hex(wrong_sec[22].address)
         and 10 in wrong_bytes and 21 in wrong_bytes,
         'wrong scope must have two real additional native JNE operand mismatches')
    for ordinal,(target,sym) in FIELDS.items():
        a,b=orig[ordinal],sec[ordinal]
        found=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['local_symbol_offset'] is None
             and found[0]['addend']==0
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in found[0]['symbol']
             and found[0]['offset']-sec[0].address==a.address-by[0x1a0]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
             'original 1A0 PE call/global physical field wrong '+str(ordinal))
    # Independently verify every earlier whole original state on this
    # newly compiled C++ game function, including all four other
    # genuinely separate states in the 980B region.
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
    old=ins[k-67-sum(r[2] for r in late):k-67]
    cursor=0;previous=[]
    for a,nb,nx,nf,bad,nxt in late:
        section=old[cursor:cursor+nx];cursor+=nx
        previous.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(old),'sixteen preceding original source-backed case boundaries truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                       (0x135,278,82,7,[274,275],0x136)]
    left=k-67-sum(r[2] for r in late)
    earlier=ins[left-sum(r[2] for r in early):left]
    cursor=0;other=[]
    for a,nb,nx,nf,bad,nxt in early:
        section=earlier[cursor:cursor+nx];cursor+=nx
        other.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(earlier),'twenty native earlier game case sources truncated')
    # All five contiguous native states 198/19A/19C/19E/1A0 exactly
    # span original 980B original-code extent, never one merged state.
    region_cases=previous[-4:]+[actual]
    need([x['native_whole_inner_B'] for x in region_cases]==[199,302,122,122,235],
         'native original 980B region must contain 5 independent case boundaries')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,[r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'native common getter four true nonrelocation GPR byte differences changed')
    receipt={'original_whole_game':'0x005214B0',
         'original_whole_callable_CODE_B':46755,
         'new_source_whole_callable_CODE_B':ret,
         'new_complete_native_1A0':actual,
         'wrongly_unconditional_scale_negative_whole_source':wrong_result,
         'wrong_scope_extra_real_JNE_operand_offsets':[10,21],
         'native_correct_stage0_JNE_skips_both_float_scales':True,
         'native_1A0_true_original_PE_field_ordinals':list(FIELDS),
         'two_original_member_first_FMUL_groups_verified':True,
         'real_original_1A0_GPR_wrong_B':49,
         'real_original_1A0_giant_exit_JMP_wrong_offsets':[231,232],
         'five_distinct_original_980B_region_native_cases':region_cases,
         'previous_16_original_PE_cases_rechecked':previous,
         'earlier_20_original_PE_cases_rechecked':other,
         'real_46B_default_getter_GPR_wrong_offsets':wrong_tail,
         'all_five_original_901B_afterRET_tables_verified':True,
         'separate_original_switch_DATA_B':901,
         'original_whole_function_exact':False,'new_accepted_callable_whole_CODE_B':0,
         'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['two_original_member_first_FMUL_groups_verified']
    print('F865 extra strict negative control: incorrect stage0 multiplier scope preserves same 235B/67x86 and 5 PE fields but adds TWO genuine JNE byte errors +10/+21; original both guards skip multipliers.')
    print('F865 completes five separately bounded 980B native original game cases 198/19A/19C/19E/1A0. New 1A0 235B/67x86/5 actual PE fields, both native FLD member then FMUL global658348 x87 widths correct, 49 GPR bytes plus 2 true whole-giant JMP bytes still differ. Entire C++ parent 27061B/7515-x86; 36 earlier original cases, 901B packed tables and common getter verified. Whole fighter NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F865 original selected fighter 1A0 FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
