#!/usr/bin/env python3
"""F861: native 198 199B/60x86/7 real PE fields within one fighter.

The game original 198 stage4 state2 sprite351 uses facing*90
FILD and Y native global659460, not F860 196 parameters.
Rebuild only affected VC7.1 whole source from the previous verified
F860 parent. Recheck 32 earlier original game case interiors and
all 5 real packed 901B afterRET DATA tables. All native x86 geometry
and PE fields align; 31 authentic GPR +2 original giant epilogue
JMP bytes remain nonexact. Common getter recovers 34/34 nonfield.
No split-case or independent original CODE accepted.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f861-scripted-stage198'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'

def need(ok,msg):
    if not ok:raise ValueError(msg)

def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'missing original native helper '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def source(rd,pe,d,by):
    O.mkdir(parents=True,exist_ok=True)
    cpp=R/'.analysis/f860-scripted-stage196/Boss005214B0-F860-whole.cpp'
    receipt=R/'.analysis/f860-scripted-stage196/verified-summary.json'
    if not cpp.is_file() or not receipt.is_file():
        result=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-stage-196-f860.py')],
              cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'f860-prior-fallback-native.log').write_text(result.stdout+result.stderr)
        need(result.returncode==0,'previous F860 original PE source failed '+(result.stdout+result.stderr)[-710:])
    prior=json.loads(receipt.read_text())
    need(prior['generated_current_whole_source_CODE_B']==26156
         and prior['original_whole_giant_exact'] is False,
         'selected preceding whole fighter native receipt changed')
    native=list(d.disasm(rd.pe_bytes_at(pe,by[0x198],by[0x19a]-by[0x198]),by[0x198]))
    need(len(native)==60 and by[0x19a]-by[0x198]==199
         and native[21].mnemonic=='push' and native[21].op_str=='2'
         and native[26].op_str.endswith(', 4')
         and native[32].op_str=='3' and native[34].op_str=='0x453d40'
         and native[41].op_str=='dword ptr [0x659460]'
         and native[46].op_str.endswith(', 0x5a')
         and native[53].op_str=='0x351' and native[55].op_str=='0x453a70'
         and native[56].op_str=='0xc8' and native[58].op_str=='0x46d000'
         and native[-1].op_str=='0x52cb4f',
         'actual native selected fighter198 stage/sprite original PE shifted')
    src=cpp.read_text()
    marker='        case 0x198: g_FighterProbeMarker = 409; break;'
    inc=(R/'probes/FighterScriptedStage198F861.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x198:')==1
         and inc.count('return;')==1 and 'SetNativeActionAt40FAC0(2);' in inc
         and 'SpawnFloatXYAt453A70(0x351' in inc
         and '*90)+F32(0x44)' in inc
         and '(*(&POS48))+g_F861ShotYAt00659460' in inc,
         'source original selected stage198 game grammar changed')
    return 'extern float g_F861ShotYAt00659460;\n'+src.replace(marker,'#include "FighterScriptedStage198F861.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F861-whole.cpp'
    obj=O/'Boss005214B0-F861-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=E,text=True,capture_output=True,timeout=290)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'native source198 full VC7.1 compilation failed '+(run.stdout+run.stderr)[-740:])
    return obj

def main():
    rd=ld('f861rd','compare-coff-function.py')
    ac=ld('f861ac','report-fighter-action-handlers.py')
    f834=ld('f861f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f861f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f861f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f861f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f861f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f861f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f861f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f861f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f861f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f861f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f861f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f861f859','verify-scripted-fighter-ground-194-f859.py')
    f860=ld('f861f860','verify-scripted-fighter-stage-196-f860.py')
    zero=ld('f861zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f861switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
             if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original fighter/afterRET extent changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(source(rd,pe,d,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(26340,7300,977,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'original 198 new whole normal C++ source x86/ABI/COFF changed')
    dens,spars,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dens>0 and spars>0 and maps>0,'all original five 901B packed switch DATA tables missing')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x19b')
         and any('g_FighterProbeMarker' in r['symbol']
              and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1,'next original19A source marker missing')
    k=marks[0];gen=ins[k-60:k]
    case=f834.physical_case(rd,pe,d,code,refs,gen,by,0x198,199,7,f860.BAD,0x19a,f820)
    need(case['native_complete_x86']==60
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[59]
         and gen[59].op_str==hex(ret-4)
         and gen[21].op_str=='2' and gen[26].op_str.endswith(', 4')
         and gen[53].op_str=='0x351'
         and gen[40].mnemonic=='fld' and gen[40].size==3
         and gen[41].mnemonic=='fadd' and gen[41].size==6,
         'native selected original 198 stage/float/sprite/JMP source wrong')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x198],199),by[0x198]))
    for ordinal,(target,sym) in {**f860.FIELDS,41:(0x659460,'g_F861ShotYAt00659460')}.items():
        a,b=original[ordinal],gen[ordinal]
        found=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in found[0]['symbol']
             and found[0]['offset']-gen[0].address==a.address-by[0x198]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
             'actual original 198 physically typed PE field wrong at ordinal '+str(ordinal))
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
      (0x196,199,60,7,f860.BAD,0x198)]
    before=ins[k-60-sum(x[2] for x in late):k-60]
    cursor=0;recent=[]
    for a,nb,nx,nf,bad,nxt in late:
        section=before[cursor:cursor+nx];cursor+=nx
        recent.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(before),'previous twelve original game states truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
    left=k-60-sum(x[2] for x in late)
    prefix=ins[left-sum(x[2] for x in early):left]
    cursor=0;older=[]
    for a,nb,nx,nf,bad,nxt in early:
        section=prefix[cursor:cursor+nx];cursor+=nx
        older.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(prefix),'earlier twenty native PE-backed case sources truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
           [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    need(len(mask)==12 and all(tail[j]==code[ret-46+j] for j in range(46) if j not in mask),
         'current native original 46B default must be 34/34 nonfield equal')
    result={'original_whole_fighter':'0x005214B0',
          'native_entire_callable_CODE_B':46755,
          'generated_entire_source_callable_CODE_B':ret,
          'new_198_native_complete_original_case':case,
          'current_actor_198_params':{'action':2,'spawn_stage':4,'sprite':0x351,
                                     'facing_scale':90,'shot_Y_global':'0x00659460'},
          'actual_GPR_wrong_nonrelocation_byte_count':31,
          'original_198_parent_epilogue_JMP_wrong_offsets':[195,196],
          'preceding_twelve_GPR_affected_native_cases':recent,
          'preceding_twenty_other_original_native_case_sources':older,
          'native_common_getter_46B_nonrelocation_equal':'34/34',
          'native_common_getter_PE_fields':3,
          'all_five_original_afterRET_packed_tables_reverified':True,
          'separate_original_901B_afterRET_DATA':901,
          'whole_original_giant_exact':False,
          'new_accepted_whole_callable_CODE_B':0,
          'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['whole_original_giant_exact'] is False
    print('F861 selected original 198 199B/60x86/7 true PE fields in one 26340B/7300-x86 full fighter. Actor2/stage4 sprite351 facing*90 Y global659460 source x86 matches except 31 GPR plus two original giant JMP bytes. Previous 32 original source-backed cases, native 46B getter 34/34 and all five 901B packed tables verified, original whole 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as ex:
        print('F861 real selected original fighter 198 FAILED:',ex,file=sys.stderr)
        raise SystemExit(1)
