#!/usr/bin/env python3
"""F837: original selected actor 0xCB 496B/141x86/12 real PE fields in giant.

Rebuild the selected F836 original parent, add actual native CB C++
with signed-short increment, physically verify complete C8/C9/CA/CB
and following CF/D0/D1/D2 in the same newly compiled VC7.1 parent.
All 8 native cases now differ ONLY in genuine encompassing whole-giant
epilogue JMP relative operands; real default 46B getter is again
34/34 original nonrelocation bytes plus three original PE calls.
All five original 901B afterRET dispatch tables checked. Entire
46755B original fighter STILL NONEXACT, no independent case CODE credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f837-scripted-fourway-cb'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
FIRST=[
 (0xc8,657,190,17,[184,185,202,203,267,268,364,365,382,383,446,447,653,654],0xc9),
 (0xc9,279,86,11,[275,276],0xca),
 (0xca,418,121,11,[203,204,414,415],0xcb),
 (0xcb,496,141,12,[214,215,492,493],0xcc),
]
LATER=[
 (0xcf,114,30,4,[110,111],0xd0),
 (0xd0,195,60,6,[154,155,191,192],0xd1),
 (0xd1,199,59,8,[26,27,195,196],0xd2),
 (0xd2,251,74,10,[26,27,247,248],0x12c),
]
def need(x,msg):
    if not x:raise ValueError(msg)
def ld(t,name):
    sp=importlib.util.spec_from_file_location(t,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'native PE helper missing '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m)
    return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-fourway-ca-f836.py')],
       cwd=R,capture_output=True,text=True,timeout=1200)
    (O/'f836-prior-physical-source.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'prior whole C8/C9/CA original PE proof failed '+(p.stdout+p.stderr)[-700:])
    src=(R/'.analysis/f836-scripted-fourway-ca/Boss005214B0-F836-whole.cpp').read_text()
    old='        case 0xCB: g_FighterProbeMarker = 204; break;'
    inc=(R/'probes/FighterScriptedFourWayCBF837.inc').read_text()
    need(src.count(old)==1 and inc.count('case 0xCB:')==1
         and inc.count('return;')==2 and inc.count('++S16(0xF00);')==1
         and inc.count('SpawnAt453C80')==1
         and inc.count('SpawnMixedAt453C80')==1
         and 'S16(0x62)>0' in inc
         and 'S16(0xF00)=0;' in inc,
         'original actor CB source frame/exit/short grammar changed')
    return src.replace(old,'#include "FighterScriptedFourWayCBF837.inc"',1)
def compile_one(src):
    cpp=O/'Boss005214B0-F837-whole.cpp';obj=O/'Boss005214B0-F837-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy()
    E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=295)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'new original full C8-CB native-shaped source VC7.1 failed '+(p.stdout+p.stderr)[-650:])
    return obj
def main():
    rd=ld('f837rd','compare-coff-function.py')
    ac=ld('f837ac','report-fighter-action-handlers.py')
    f834=ld('f837f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f837f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=ld('f837zero','verify-fighter-actionzero-natural-source.py')
    switch=ld('f837switch','verify-fighter-natural-switch-probes.py')
    D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'actual original whole-game native PE identity changed')
    report,mp=ac.report_boss(rd,pe,D,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in D.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(20165,5447,831,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'full actual game fighter ABI/COFF size/x86/901B DATA differs')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,switch,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all five native dense/sparse packed switch tables not checked')
    starts=[i for i,x in enumerate(ins) if x.mnemonic=='push' and x.op_str=='0xff'
            and i+4<len(ins) and ins[i+1].op_str=='4'
            and ins[i+2].op_str=='3' and ins[i+4].mnemonic=='call']
    need(len(starts)>=4,'original consecutive C8/C9/CA/CB storm-entry source missing')
    k=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0xcd')
       and any('g_FighterProbeMarker' in r['symbol']
               and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(k)==1 and k[0]>starts[-1],'original following CC case marker missing')
    begin=starts[-4:];ends=[*begin[1:],k[0]]
    fours=[]
    for (act,nb,nx,nf,wrong,nextcase),a,b in zip(FIRST,begin,ends):
        gen=ins[a:b]
        result=f834.physical_case(rd,pe,D,code,refs,gen,by,act,nb,nf,wrong,nextcase,f820)
        need(len(gen)==nx,'true selected actor C8-CB x86 instruction count changed')
        for ordinal in result['original_native_enclosing_parent_JMP_exit_ordinals']:
            need(gen[ordinal].op_str==hex(ret-4),'real whole fighter direct exit JMP targets incorrect source tail')
        if act==0xcb:
            need(result['original_native_enclosing_parent_JMP_exit_ordinals']==[58,140]
                 and gen[133].mnemonic=='mov' and gen[133].op_str=='dx, word ptr [ecx + 0xf00]'
                 and gen[134].mnemonic=='add' and gen[134].op_str=='dx, 1',
                 'original CB authentic signed-short prefix increment/epilogue CFG changed')
        fours.append(result)
    later_marker=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x12d')
       and any('g_FighterProbeMarker' in r['symbol']
               and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(later_marker)==1 and later_marker[0]>=223,'native following 12C marker missing')
    old=ins[later_marker[0]-223:later_marker[0]]
    index=0;previous=[]
    for act,nb,nx,nf,wrong,nextcase in LATER:
        gen=old[index:index+nx];index+=nx
        result=f834.physical_case(rd,pe,D,code,refs,gen,by,act,nb,nf,wrong,nextcase,f820)
        for ordinal in result['original_native_enclosing_parent_JMP_exit_ordinals']:
            need(gen[ordinal].op_str==hex(ret-4),'original later full fighter parent epilogue exit wrong')
        previous.append(result)
    need(index==223,'native CF/D0/D1/D2 old case source truncated')
    native=rd.pe_bytes_at(pe,0x52cb25,46)
    f=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,native,0x52cb25,f,ret-46,3)
    real=list(D.disasm(native,0x52cb25))
    curr=list(D.disasm(code[ret-46:ret],ret-46))
    need(len(mask)==12 and len(real)==len(curr)==16
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(real,curr))
         and all(native[j]==code[ret-46+j] for j in range(46) if j not in mask),
         'new full C8-CB context must restore all 34/34 original default nonrelocation bytes')
    out={'original_giant':'0x005214B0','native_original_whole_CODE_B':46755,
         'whole_source_callable_CODE_B':ret,
         'four_true_native_C8_C9_CA_CB_cases':fours,
         'four_following_original_CF_D0_D1_D2_reverified':previous,
         'original_CB_real_complete_inner_CODE_B':496,
         'original_CB_native_x86':141,'actual_original_CB_PE_fields':12,
         'physical_CB_wrong_only_external_epilogue_offsets':[214,215,492,493],
         'native_original_default_tail_nonrelocation':'34/34',
         'real_original_default_tail_REL32_PE_fields':3,
         'five_original_native_afterRET_tables_reverified':True,
         'original_separate_afterRET_DATA_B':901,
         'entire_original_whole_function_exact':False,
         'new_accepted_whole_callable_CODE_B':0,'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F837 major: original native CB 496B/141x86/12 true PE fields, only 4 genuine whole-parent JMP operand bytes different; selected full parent 20165B/5447x86, C8/C9/CA/CB and CF/D0/D1/D2 now EACH only native parent-epilogue JMP-byte different. Native default 46B 34/34 nonrelocation +3 true PE calls, all five 901B packed tables verified. Whole 46755B giant NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F837 original native whole fighter CB FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
