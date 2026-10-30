#!/usr/bin/env python3
"""F868: real original 1F6 372B/111 x86/12 original physical PE fields.

Stage0 original Reset/counters, ground drop native global657478,
special stage8..10 when unsigned byte+511==0x14 switches to
action1F7, resets and calls original 455B30 before early direct
return. Stage5 sprite80 with facing*100 FILD float X, raw Y bits
and second sprite336 plus Prepare2, real original call order.
Normal real mixed float/int coordinate method source emits the
native push/FILD ordering; all native x86 mnemonic/width and
12 original PE fields/targets match but 64 genuine GPR operand
bytes plus 4 actual enclosing-giant epilogue JMP bytes differ.
Compile ONE affected entire fighter and recheck prior 39 complete
original game source cases and 901B packed native afterRET DATA.
No standalone accepted exact CODE; no all-unit cold replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f868-scripted-state1f6'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,63,66,82,85,94,97,100,103,119,122,129,133,136,141,145,148,153,157,163,197,198,211,213,217,220,234,238,241,246,250,253,257,260,269,272,274,276,279,281,283,287,290,293,299,302,324,327,329,331,334,336,338,341,343,368,369]
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
 93:(0x453c80,'SpawnFloatXRawYAt453C80'),
 106:(0x453a70,'SpawnDirectedAt453A70'),
 109:(0x453d40,'PrepareActionAt453D40'),
}
EXPECTED_OFFSETS=[26,70,89,107,176,184,192,205,229,317,353,363]
def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,f):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'original PE helper missing '+f)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f867-scripted-state1f5/Boss005214B0-F867-whole.cpp'
    receipt=R/'.analysis/f867-scripted-state1f5/verified-summary.json'
    if not prior.is_file() or not receipt.is_file():
        p=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-staged-1f5-f867.py')],
           cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'f867-native-fallback.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,'previous native 1F5 whole source verification failed '+(p.stdout+p.stderr)[-680:])
    previous=json.loads(receipt.read_text())
    need(previous['current_generated_full_source_CODE_B']==28107
         and previous['original_whole_giant_exact'] is False,
         'previous 1F5 physical full-source receipt inconsistent')
    src=prior.read_text()
    prototype='SpawnRawAt453C80(int,int,int,char,int);'
    need(src.count(prototype)==1,'native narrow facing source signature missing')
    src=src.replace(prototype,prototype+' void SpawnFloatXRawYAt453C80(int,float,int,char,int); void NativeGameEffectAt455B30();',1)
    marker='        case 0x1F6: g_FighterProbeMarker = 503; break;'
    inc=(R/'probes/FighterScriptedConditional1F6F868.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x1F6:')==1
         and inc.count('return;')==2
         and 'U8(0x511)==0x14' in inc
         and 'S16(0x62)>7' in inc and 'S16(0x62)<0xB' in inc
         and 'SetNativeActionAt40FAC0(0x1F7)' in inc
         and 'NativeGameEffectAt455B30()' in inc
         and 'SpawnFloatXRawYAt453C80(0x80' in inc
         and 'SpawnDirectedAt453A70(0x336' in inc
         and 'PrepareActionAt453D40(2)' in inc,
         'actual game original stage1F6 conditional branch/projectiles source changed')
    return src.replace(marker,'#include "FighterScriptedConditional1F6F868.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F868-whole.cpp';obj=O/'Boss005214B0-F868-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=env,capture_output=True,text=True,timeout=305)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'real selected fighter 1F6 full VC7.1 compile failed '+(p.stdout+p.stderr)[-730:])
    return obj

def main():
    rd=ld('f868rd','compare-coff-function.py')
    ac=ld('f868ac','report-fighter-action-handlers.py')
    f834=ld('f868f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f868f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f868f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f868f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f868f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f868f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f868f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f868f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f868f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f868f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f868f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f868f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f868f860','verify-scripted-fighter-stage-196-f860.py')
    f862=ld('f868f862','verify-scripted-fighter-stage-19a-f862.py')
    f863=ld('f868f863','verify-scripted-fighter-short-19c19e-f863.py')
    f865=ld('f868f865','verify-scripted-fighter-sustain-1a0-f865.py')
    f866=ld('f868f866','verify-scripted-fighter-doubleprojectile-1f4-f866.py')
    f867=ld('f868f867','verify-scripted-fighter-staged-1f5-f867.py')
    zero=ld('f868zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f868sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'real native fighter original whole or packed table identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x1f6],by[0x1f7]-by[0x1f6]),by[0x1f6]))
    need(len(original)==111 and by[0x1f7]-by[0x1f6]==372
         and original[24].op_str=='dword ptr [0x657478]'
         and original[37].op_str.endswith(', 7')
         and original[41].op_str.endswith(', 0xb')
         and original[45].op_str.endswith(', 0x14')
         and original[49].op_str=='0x40fac0'
         and original[53].op_str=='0x455b30'
         and original[54].op_str=='0x52cb4f'
         and original[74].op_str.endswith(', 0x41600000')
         and original[84].op_str.endswith(', 0x64')
         and original[91].op_str=='0x80'
         and original[93].op_str=='0x453c80'
         and original[104].op_str=='0x336'
         and original[106].op_str=='0x453a70'
         and original[109].op_str=='0x453d40'
         and original[110].op_str=='0x52cb4f',
         'original 1F6 native special stage/sprite/physical call identity changed')
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(28464,7951,1032,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'actual new complete VC7.1 giant 1F6 CODE/x86/COFF/ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all five original native packed 901B switch DATA tables missing')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x1f8')
       and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=111,'following original 1F7 marker missing')
    k=marks[0];gen=ins[k-111:k]
    actual=f834.physical_case(rd,pe,d,code,refs,gen,by,0x1f6,372,12,BAD,0x1f7,f820)
    need(actual['native_complete_x86']==111
         and actual['original_native_enclosing_parent_JMP_exit_ordinals']==[54,110]
         and gen[54].op_str==gen[110].op_str==hex(ret-4)
         and original[3].op_str==original[7].op_str==hex(original[16].address)
         and gen[3].op_str==gen[7].op_str==hex(gen[16].address)
         and original[38].op_str==original[42].op_str==original[46].op_str==hex(original[55].address)
         and gen[38].op_str==gen[42].op_str==gen[46].op_str==hex(gen[55].address)
         and gen[44].mnemonic=='movzx'
         and gen[86].mnemonic=='fild'
         and gen[88].mnemonic=='fadd'
         and gen[93].mnemonic=='call'
         and gen[106].mnemonic=='call',
         'original 1F6 stage8..10 conditional/float projectile or direct giant returns wrong')
    lo=gen[0].address
    raw=rd.pe_bytes_at(pe,by[0x1f6],372)
    ff=[r for r in refs if lo<=r['offset']<gen[-1].address+gen[-1].size]
    masked=f820.physical_fields(rd,raw,by[0x1f6],ff,lo,12)
    need(len(masked)==48,'12 original PE fields not physically verified')
    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],gen[ordinal]
        field=[r for r in ff if b.address<=r['offset']<b.address+b.size]
        need(len(field)==1 and field[0]['addend']==0
             and field[0]['local_symbol_offset'] is None
             and field[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in field[0]['symbol']
             and field[0]['offset']-lo==a.address-by[0x1f6]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                   else f'dword ptr [0x{target:x}]'),
             'native 1F6 physical PE call/global target at x86 ordinal '+str(ordinal))
        offsets.append(field[0]['offset']-lo)
    need(offsets==EXPECTED_OFFSETS,'native 1F6 physical PE field positions changed')
    need(len(BAD)==68 and all(j in BAD for j in (197,198,368,369)),
         'original 1F6 real GPR and enclosing giant JMP bytes must remain nonexact')
    # Recheck previous 39 complete native case sources on SAME current
    # compiled original-shaped giant, including guarded original 1A0.
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
      (0x1f5,628,195,17,f867.BAD,0x1f6)]
    prior=ins[k-111-sum(x[2] for x in late):k-111]
    cursor=0;recent=[]
    for a,nb,nx,nf,bad,nxt in late:
        sec=prior[cursor:cursor+nx];cursor+=nx
        result=f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820)
        if a==0x1a0:
            need(sec[3].op_str==sec[7].op_str==hex(sec[22].address),
                 'prior native 1A0 multipliers incorrectly moved outside stage0')
        recent.append(result)
    need(cursor==len(prior),'nineteen preceding real original game cases truncated')
    earlier=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                          (0x135,278,82,7,[274,275],0x136)]
    left=k-111-sum(x[2] for x in late)
    old=ins[left-sum(x[2] for x in earlier):left]
    cursor=0;past=[]
    for a,nb,nx,nf,bad,nxt in earlier:
        sec=old[cursor:cursor+nx];cursor+=nx
        past.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(old),'twenty earlier original source-backed cases truncated')
    original_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tailmask=f820.physical_fields(rd,original_tail,0x52cb25,
            [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    need(len(tailmask)==12 and all(original_tail[j]==code[ret-46+j] for j in range(46) if j not in tailmask),
         'native 46B common getter 34/34 original nonfield equality changed')
    receipt={'original_whole_fighter':'0x005214B0',
       'original_native_whole_callable_CODE_B':46755,
       'new_generated_entire_source_callable_CODE_B':ret,
       'new_1F6_complete_native_case':actual,
       'actual_native_original_1F6_PE_field_offsets':offsets,
       'native_special_stage_range':{'lower_exclusive':7,'upper_exclusive':11,'unsigned_byte_511':20,'new_action':503},
       'native_new_game_effect_call':'0x00455B30',
       'native_float_X_raw_Y_sprite':0x80,
       'second_integer_coordinate_sprite':0x336,
       'genuine_1F6_source_GPR_wrong_B':64,
       'native_1F6_two_giant_JMP_wrong_pairs':[197,198,368,369],
       'previous_nineteen_original_native_PE_cases_rechecked':recent,
       'earlier_twenty_original_source_PE_cases_rechecked':past,
       'native_getter_46B_nonrelocation':'34/34',
       'all_five_original_packed_901B_afterRET_tables_verified':True,
       'separate_original_native_afterRET_DATA_B':901,
       'original_entire_giant_exact':False,'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_giant_exact'] is False
    print('F868 native original1F6 372B/111x86/12 actual PE fields with stage8..10 unsigned-byte+511 game effect455B30 and stage5 float-X sprite80 plus integer sprite336. Entire current fighter 28464B/7951x86; 64 GPR/4 original whole-giant JMP bytes remain nonexact. Prior39 original cases, 901B five packed tables and native getter 34/34 verified.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F868 original fighter 1F6 native verification FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
