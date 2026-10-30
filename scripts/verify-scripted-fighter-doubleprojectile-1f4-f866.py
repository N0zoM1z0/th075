#!/usr/bin/env python3
"""F866: native real original 1F4 complete 448B/136 x86/14 PE fields.

Original current actor source includes native start Reset/FLAG zero,
ground x87 damping/early auxD path, TWO separate stage4 sprite
calls (338 then 7F), stage4 motion 8/9.5/0.65 and stage13 auxB.
A genuinely narrow fourth argument of SpawnRawAt453C80 emits
native 3B MOV r8 rather than widened int 4B MOVSX r32.
Compile ONE affected entire VC7.1 giant, physically compare all
14 original PE destinations, all opcode/width/positions and 82
honest register-operand bytes plus 4 enclosing giant JMP bytes.
Recheck previous 37 original whole case interiors and all five
separate native 901B afterRET switch DATA tables. The original
46755B full function NONEXACT, no split-case exact CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f866-scripted-state1f4'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,63,66,82,85,94,97,100,103,119,122,129,132,148,151,154,157,160,163,166,169,172,175,209,212,219,220,233,235,239,242,256,260,263,268,272,275,281,284,286,288,291,293,295,298,300,315,319,322,327,331,334,348,351,358,361,368,371,380,383,385,387,390,392,394,397,399,411,415,418,423,427,430,444,445]
FIELDS={
 9:(0x453e20,'ResetAt453E20'),
 18:(0x65782c,'g_ThresholdAt0065782C'),
 24:(0x6583fc,'g_F866DropAt006583FC'),
 29:(0x65782c,'g_ThresholdAt0065782C'),
 37:(0x65782c,'g_ThresholdAt0065782C'),
 51:(0x65782c,'g_ThresholdAt0065782C'),
 56:(0x453e20,'ResetAt453E20'),
 59:(0x40fb40,'SetAuxActionAt40FB40'),
 64:(0x40fa30,'GetNativeActionAt40FA30'),
 72:(0x40fac0,'SetNativeActionAt40FAC0'),
 93:(0x453a70,'SpawnDirectedAt453A70'),
 104:(0x453d40,'PrepareActionAt453D40'),
 123:(0x453c80,'SpawnRawAt453C80'),
 134:(0x40fb40,'SetAuxActionAt40FB40')
}
def need(cond,msg):
    if not cond:raise ValueError(msg)
def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'missing original PE helper '+name)
    mod=importlib.util.module_from_spec(spec);sys.modules[tag]=mod;spec.loader.exec_module(mod)
    return mod
def source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f865-scripted-stage1a0/Boss005214B0-F865-whole.cpp'
    receipt=R/'.analysis/f865-scripted-stage1a0/verified-summary.json'
    if not prior.is_file() or not receipt.is_file():
        run=subprocess.run([str(R/'scripts/repo-python'),
                   str(R/'scripts/verify-scripted-fighter-sustain-1a0-f865.py')],
                    cwd=R,text=True,capture_output=True,timeout=1300)
        (O/'f865-fallback-native.log').write_text(run.stdout+run.stderr)
        need(run.returncode==0,'preceding original F865 physical native parent missing '+(run.stdout+run.stderr)[-750:])
    old=json.loads(receipt.read_text())
    need(old['generated_entire_source_callable_CODE_B']==27061
         and old['original_whole_giant_exact'] is False,
         'previous native correct 1A0 full source receipt changed')
    s=prior.read_text()
    decl='SpawnRawAt453C80(int,int,int,int,int)'
    need(s.count(decl)==1,'original native SpawnRawAt453C80 method declaration not unique')
    s=s.replace(decl,'SpawnRawAt453C80(int,int,int,char,int)',1)
    mark='        case 0x1F4: g_FighterProbeMarker = 501; break;'
    fragment=(R/'probes/FighterScriptedDoubleProjectile1F4F866.inc').read_text()
    need(s.count(mark)==1 and fragment.count('case 0x1F4:')==1
         and fragment.count('return;')==2
         and fragment.count('SpawnDirectedAt453A70(0x338')==1
         and fragment.count('SpawnRawAt453C80(0x7F')==1
         and fragment.count('ResetAt453E20();')==2
         and 'POS48+POS54<=g_ThresholdAt0065782C' in fragment,
         'current original native 1F4 C++ stage and two projectile operations changed')
    return 'extern float g_F866DropAt006583FC;\n'+s.replace(
        mark,'#include "FighterScriptedDoubleProjectile1F4F866.inc"',1)
def compile_one(src):
    cpp=O/'Boss005214B0-F866-whole.cpp';obj=O/'Boss005214B0-F866-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=E,capture_output=True,text=True,timeout=300)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'whole native original fighter 1F4 VC7.1 build failed '+(run.stdout+run.stderr)[-700:])
    return obj

def main():
    rd=ld('f866rd','compare-coff-function.py')
    ac=ld('f866ac','report-fighter-action-handlers.py')
    f834=ld('f866f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f866f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f866f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f866f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f866f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f866f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f866f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f866f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f866f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f866f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f866f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f866f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f866f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f866f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f866f863','verify-scripted-fighter-short-19c19e-f863.py')
    f865=ld('f866f865','verify-scripted-fighter-sustain-1a0-f865.py')
    zero=ld('f866zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f866sw','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original whole fighter and five switch DATA region changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x1f4],by[0x1f5]-by[0x1f4]),by[0x1f4]))
    need(len(original)==136 and by[0x1f5]-by[0x1f4]==448
         and original[3].op_str==original[7].op_str==hex(original[16].address)
         and original[62].op_str=='0x52cb4f'
         and original[113].mnemonic=='mov' and original[113].size==3
         and original[113].op_str.startswith('dl, byte ptr')
         and original[123].op_str=='0x453c80'
         and original[135].op_str=='0x52cb4f',
         'real original 1F4 binary type/branch geometry changed')
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(27494,7649,1005,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'selected F866 whole source x86/COFF/901B afterRET table geometry changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all five native original packed afterRET DATA tables unverified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x1f6')
           and any('g_FighterProbeMarker' in r['symbol']
                  and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=136,'original next 1F5 case marker missing')
    k=marks[0];gen=ins[k-136:k]
    actual=f834.physical_case(rd,pe,d,code,refs,gen,by,0x1f4,448,14,BAD,0x1f5,f820)
    need(actual['native_complete_x86']==136
         and actual['original_native_enclosing_parent_JMP_exit_ordinals']==[62,135]
         and gen[62].op_str==gen[135].op_str==hex(ret-4)
         and gen[3].op_str==gen[7].op_str==hex(gen[16].address)
         and gen[113].mnemonic=='mov' and gen[113].size==3
         and 'byte ptr' in gen[113].op_str
         and gen[123].mnemonic=='call',
         'actual original 1F4 native stage0 guard, narrow char or two direct giant exits wrong')
    lo=gen[0].address
    orig_raw=rd.pe_bytes_at(pe,by[0x1f4],448)
    fields=[r for r in refs if lo<=r['offset']<gen[-1].address+gen[-1].size]
    physical_mask=f820.physical_fields(rd,orig_raw,by[0x1f4],fields,lo,14)
    need(len(physical_mask)==56,'all fourteen native PE fields must be physically validated')
    field_offsets=[]
    for ordinal,(target,symbol) in FIELDS.items():
        a,b=original[ordinal],gen[ordinal]
        ff=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(ff)==1 and ff[0]['addend']==0
             and ff[0]['local_symbol_offset'] is None
             and ff[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and symbol in ff[0]['symbol']
             and ff[0]['offset']-lo==a.address-by[0x1f4]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                               else f'dword ptr [0x{target:x}]'),
             'native original 1F4 typed PE symbol or target wrong at x86 '+str(ordinal))
        field_offsets.append(ff[0]['offset']-lo)
    need(field_offsets==[26,70,89,107,136,179,194,204,227,251,310,343,406,439],
         'source original 1F4 physical PE field geometry drifted')
    need(len(BAD)==86 and all(j in BAD for j in (219,220,444,445)),
         '1F4 exactness must retain two original giant epilogue JMP pairs and all GPR negatives')
    # All 37 previously source-backed real whole-case interiors,
    # including the two authentic original 1A0 stage-zero JNE guard targets.
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
      (0x1a0,235,67,5,f865.WRONG,0x1f4)]
    prior=ins[k-136-sum(x[2] for x in late):k-136]
    cursor=0;recent=[]
    for a,nb,nx,nf,bad,nxt in late:
        seg=prior[cursor:cursor+nx];cursor+=nx
        result=f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,bad,nxt,f820)
        if a==0x1a0:
            need(seg[3].op_str==seg[7].op_str==hex(seg[22].address),
                 'earlier native original stage-zero multipliers have incorrect conditional scope')
        recent.append(result)
    need(cursor==len(prior),'seventeen later original game cases truncated')
    earlier=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                          (0x135,278,82,7,[274,275],0x136)]
    left=k-136-sum(x[2] for x in late)
    old=ins[left-sum(x[2] for x in earlier):left]
    cursor=0;past=[]
    for a,nb,nx,nf,bad,nxt in earlier:
        seg=old[cursor:cursor+nx];cursor+=nx
        past.append(f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(old),'twenty earlier original physical case sources truncated')
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,native_tail,0x52cb25,
       [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    getter_wrong=[j for j in range(46) if j not in mask and native_tail[j]!=code[ret-46+j]]
    need(getter_wrong==[10,12,16,19],
         'original 46B common getter true GPR byte errors changed')
    report_out={'original_whole_fighter':'0x005214B0',
       'native_original_whole_callable_CODE_B':46755,
       'new_generated_whole_callable_CODE_B':ret,
       'actual_1F4_complete_native_case':actual,
       'original_1F4_typed_PE_field_offsets':field_offsets,
       'genuine_narrow_facing_parameter_at_453C80':True,
       'native_original_113_MOV_byte_width':3,
       'incorrect_int_fourth_parameter_MOVSX_width':4,
       'real_1F4_GPR_nonrelocation_wrong_B':82,
       'real_1F4_external_giant_JMP_wrong_offsets':[219,220,444,445],
       'previous_seventeen_GPR_affected_original_cases_rechecked':recent,
       'earlier_twenty_original_PE_game_cases_rechecked':past,
       'native_original_default_46B_GPR_wrong_offsets':getter_wrong,
       'all_five_original_packed_901B_afterRET_tables_rechecked':True,
       'original_separate_afterRET_DATA_B':901,
       'native_original_whole_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(report_out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['native_original_whole_giant_exact'] is False
    print('F866 original native 1F4 full 448B/136-x86/14 genuine PE fields, real narrow fourth facing byte MOV not MOVSX. Current entire fighter 27494B/7649-x86, 82 GPR and 4 honest full-giant JMP bytes wrong; all prior 37 original cases, five native 901B packed tables and common getter PE/GPR checked. Whole original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F866 original selected 1F4 whole fighter FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
