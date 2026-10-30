#!/usr/bin/env python3
"""F869 original game fighter action 1F7 307B/90-x86/11 native PE fields.

Full parent with actual 4..6 stage transition to 1F8, U8+511==20
and game effect 455B30; stage3 sprite337 and Prepare3. One normal
VC7.1 affected fighter compilation, true original PE field positions/
types/destinations, earlier forty sourced full case interiors and five
901B original afterRET packed DATA tables. Native GPR and enclosing
giant JMP differences are explicitly nonexact, never split-credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f869-scripted-state1f7'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
WRONG=[1,5,8,12,16,19,31,35,43,46,53,56,63,66,82,85,94,97,100,103,119,122,129,133,136,141,145,148,153,157,163,197,198,211,213,217,220,234,238,241,246,250,253,259,262,264,266,269,271,273,276,278,303,304]
FIELDS={
 9:(0x453e20,'ResetAt453E20'),
 18:(0x65782c,'g_ThresholdAt0065782C'),
 24:(0x657478,'g_SubtractAt00657478'),
 29:(0x65782c,'g_ThresholdAt0065782C'),
 49:(0x40fac0,'SetNativeActionAt40FAC0'),
 51:(0x453e20,'ResetAt453E20'),
 53:(0x455b30,'NativeGameEffectAt455B30'),
 56:(0x40fa30,'GetNativeActionAt40FA30'),
 64:(0x40fac0,'SetNativeActionAt40FAC0'),
 85:(0x453a70,'SpawnDirectedAt453A70'),
 88:(0x453d40,'PrepareActionAt453D40')
}
OFFSETS=[26,70,89,107,176,184,192,205,229,288,298]

def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,f):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'original PE helper missing '+f)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m

def generate_source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f868-scripted-state1f6/Boss005214B0-F868-whole.cpp'
    receipt=R/'.analysis/f868-scripted-state1f6/verified-summary.json'
    if not prev.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-conditional-1f6-f868.py')],
             cwd=R,text=True,capture_output=True,timeout=1400)
        (O/'previous-f868-original-PE.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous native F868 source missing '+(cp.stdout+cp.stderr)[-780:])
    old=json.loads(receipt.read_text())
    need(old['new_generated_entire_source_callable_CODE_B']==28464
         and old['original_entire_giant_exact'] is False,
         'prior original 1F6 PE receipt inconsistent')
    src=prev.read_text()
    marker='        case 0x1F7: g_FighterProbeMarker = 504; break;'
    inc=(R/'probes/FighterScriptedConditional1F7F869.inc').read_text()
    need(src.count(marker)==1
         and inc.count('case 0x1F7:')==1
         and inc.count('return;')==2
         and 'S16(0x62)>3 && S16(0x62)<7' in inc
         and 'U8(0x511)==0x14' in inc
         and 'SetNativeActionAt40FAC0(0x1F8)' in inc
         and 'NativeGameEffectAt455B30()' in inc
         and 'S16(0x62)==3 && S16(0x64)==0' in inc
         and 'SpawnDirectedAt453A70(0x337' in inc
         and 'PrepareActionAt453D40(3)' in inc,
         'native source staged 1F7 game action/source grammar changed')
    return src.replace(marker,'#include "FighterScriptedConditional1F7F869.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F869-whole.cpp'
    obj=O/'Boss005214B0-F869-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=R,env=env,text=True,capture_output=True,timeout=290)
    (O/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'VC7.1 original actor 1F7 whole source failed '+(cp.stdout+cp.stderr)[-760:])
    return obj

def main():
    rd=ld('f869rd','compare-coff-function.py')
    ac=ld('f869ac','report-fighter-action-handlers.py')
    f834=ld('f869f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f869f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f869f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f869f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f869f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f869f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f869f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f869f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f869f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f869f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f869f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f869f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f869f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f869f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f869f863','verify-scripted-fighter-short-19c19e-f863.py')
    f865=ld('f869f865','verify-scripted-fighter-sustain-1a0-f865.py')
    f866=ld('f869f866','verify-scripted-fighter-doubleprojectile-1f4-f866.py')
    f867=ld('f869f867','verify-scripted-fighter-staged-1f5-f867.py')
    f868=ld('f869f868','verify-scripted-fighter-conditional-1f6-f868.py')
    zero=ld('f869zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f869sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original 005214B0 whole fighter/packed DATA native changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x1f7],by[0x1f8]-by[0x1f7]),by[0x1f7]))
    need(len(orig)==90 and by[0x1f8]-by[0x1f7]==307
         and orig[3].op_str==orig[7].op_str==hex(orig[16].address)
         and orig[37].op_str.endswith(', 3')
         and orig[41].op_str.endswith(', 7')
         and orig[45].op_str.endswith(', 0x14')
         and orig[47].op_str=='0x1f8'
         and orig[53].op_str=='0x455b30'
         and orig[54].op_str=='0x52cb4f'
         and orig[67].op_str.endswith(', 3')
         and orig[83].op_str=='0x337'
         and orig[85].op_str=='0x453a70'
         and orig[86].op_str=='3'
         and orig[88].op_str=='0x453d40'
         and orig[89].op_str=='0x52cb4f',
         'real original 1F7 native boundaries, staged action or call targets differ')
    obj=compile_one(generate_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(28756,8039,1042,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'new whole actor source ABI, x86 geometry or COFF field drifted')
    dens,spars,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dens>0 and spars>0 and maps>0,'five original 901B packed afterRET tables not proven')
    markers=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
             and x.op_str.endswith(', 0x1f9')
             and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1 and markers[0]>=90,'following native 1F8 source marker missing')
    k=markers[0];gen=ins[k-90:k]
    result=f834.physical_case(rd,pe,d,code,refs,gen,by,0x1f7,307,11,WRONG,0x1f8,f820)
    need(result['native_complete_x86']==90
         and result['original_native_enclosing_parent_JMP_exit_ordinals']==[54,89]
         and gen[54].op_str==gen[89].op_str==hex(ret-4)
         and gen[3].op_str==gen[7].op_str==hex(gen[16].address)
         and gen[38].op_str==gen[42].op_str==gen[46].op_str==hex(gen[55].address)
         and gen[83].op_str=='0x337',
         'original staged native 1F7 guard/facing or enclosing return changed')
    lo=gen[0].address
    fields=[r for r in refs if lo<=r['offset']<gen[-1].address+gen[-1].size]
    native_raw=rd.pe_bytes_at(pe,by[0x1f7],307)
    mask=f820.physical_fields(rd,native_raw,by[0x1f7],fields,lo,11)
    need(len(mask)==44,'eleven original real typed PE fields not validated')
    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=orig[ordinal],gen[ordinal]
        fs=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(fs)==1 and fs[0]['addend']==0
             and fs[0]['local_symbol_offset'] is None
             and fs[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in fs[0]['symbol']
             and fs[0]['offset']-lo==a.address-by[0x1f7]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                  else f'dword ptr [0x{target:x}]'),
             'native original 1F7 physical typed PE call/global field wrong '+str(ordinal))
        offsets.append(fs[0]['offset']-lo)
    need(offsets==OFFSETS and len(WRONG)==54 and all(i in WRONG for i in (197,198,303,304)),
         'original 1F7 exactness guard unexpectedly changed')
    # All 40 preceding real source-backed game action intervals checked
    # in the SAME updated parent, not accepted as standalone functions.
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
      (0x1f6,372,111,12,f868.BAD,0x1f7)]
    old=ins[k-90-sum(r[2] for r in late):k-90]
    pos=0;previous=[]
    for a,nb,nx,nf,bad,nxt in late:
        seg=old[pos:pos+nx];pos+=nx
        physical=f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,bad,nxt,f820)
        if a==0x1a0:
            need(seg[3].op_str==seg[7].op_str==hex(seg[22].address),
                 'guarded original 1A0 multipliers moved outside original stage-zero branch')
        previous.append(physical)
    need(pos==len(old),'twenty later original source cases truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                       (0x135,278,82,7,[274,275],0x136)]
    left=k-90-sum(r[2] for r in late)
    prefix=ins[left-sum(r[2] for r in early):left]
    pos=0;prior=[]
    for a,nb,nx,nf,bad,nxt in early:
        seg=prefix[pos:pos+nx];pos+=nx
        prior.append(f834.physical_case(rd,pe,d,code,refs,seg,by,a,nb,nf,bad,nxt,f820))
    need(pos==len(prefix),'twenty earlier original native PE-backed case sources truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tailmask=f820.physical_fields(rd,tail,0x52cb25,
         [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    bad_tail=[i for i in range(46) if i not in tailmask and tail[i]!=code[ret-46+i]]
    need(bad_tail==[10,12,16,19],'native original common getter GPR phase changed')
    receipt={'original_whole_game':'0x005214B0','native_original_whole_callable_CODE_B':46755,
      'current_generated_source_callable_CODE_B':ret,'native_original_new_1F7_complete_case':result,
      'native_1F7_physical_PE_field_offsets':offsets,
      'original_special_range':{'stage_gt':3,'stage_lt':7,'unsigned_byte_at_511':20,'action':0x1f8},
      'true_native_1F7_GPR_nonfield_wrong_B':50,
      'true_native_original_giant_JMP_wrong_offsets':[197,198,303,304],
      'twenty_late_original_case_sources_rechecked':previous,
      'twenty_early_original_case_sources_rechecked':prior,
      'native_common_getter_46B_GPR_wrong_offsets':bad_tail,
      'original_five_901B_afterRET_packed_tables_rechecked':True,
      'original_separate_afterRET_DATA_B':901,'whole_original_fighter_exact':False,
      'new_accepted_whole_callable_CODE_B':0,'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['whole_original_fighter_exact'] is False
    print('F869 native original1F7 307B/90 x86/11 real PE fields stage4..6 U8+511 game effect action1F8 and stage3 sprite337/Prepare3. Whole generated source 28756B/8039x86; 50 real GPR and four giant final JMP bytes remain wrong. Previous 40 native PE-backed cases, native getter four GPR negatives and all five 901B tables verified. Whole original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F869 real original whole 1F7 native PE proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
