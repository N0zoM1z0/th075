#!/usr/bin/env python3
"""F836: actual 418B/121-x86/11-field original CA in complete growing fighter.

Rebuild the F834 entire C8 source and original physical five jump tables,
then add the genuinely different selected-actor original CA (NOT F759
other-actor 439B case). Recompile ONE affected full VC7.1 parent, check
C8,C9,CA and true COFF fields, the complete 901B after-RET tables
and original default 46B. New CA matches all non-PE original CODE
apart from two real enclosing-parent JMP operand pairs. It is not
an independent original function; whole 46,755-B giant NONEXACT.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f836-scripted-fourway-ca'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BASE=0x005214B0
EXPECTED={0xc8:(657,190,17,[184,185,202,203,267,268,364,365,382,383,446,447,653,654]),
          0xc9:(279,86,11,[275,276]),
          0xca:(418,121,11,[203,204,414,415])}
def need(p,msg):
    if not p:raise ValueError(msg)
def load(t,n):
    sp=importlib.util.spec_from_file_location(t,R/'scripts'/n)
    need(sp and sp.loader,'missing original PE helper '+n)
    m=importlib.util.module_from_spec(sp);sys.modules[t]=m;sp.loader.exec_module(m)
    return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-fourway-c8-f834.py')],
       cwd=R,capture_output=True,text=True,timeout=1200)
    (O/'f834-prior-target-proof.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'previous full C8 physical original proof failed '+(p.stdout+p.stderr)[-700:])
    cpp=(R/'.analysis/f834-scripted-fourway-c8/Boss005214B0-F834-whole.cpp').read_text()
    old='        case 0xCA: g_FighterProbeMarker = 203; break;'
    inc=(R/'probes/FighterScriptedFourWayCAF836.inc').read_text()
    need(cpp.count(old)==1 and inc.count('case 0xCA:')==1
         and inc.count('return;')==2
         and inc.count('SpawnAt453C80')==1
         and inc.count('SpawnMixedAt453C80')==1
         and 'POS54=POS54-POS5C' in inc
         and 'S16(0x62)>1' in inc,
         'actual native CA source/macro behavior changed')
    return cpp.replace(old,'#include "FighterScriptedFourWayCAF836.inc"',1)
def compile_one(src):
    cpp=O/'Boss005214B0-F836-whole.cpp';obj=O/'Boss005214B0-F836-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,env=env,capture_output=True,text=True,timeout=280)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'full VC7.1 CA codegen failed '+(run.stdout+run.stderr)[-650:])
    return obj
def main():
    rd=load('f836rd','compare-coff-function.py')
    ac=load('f836ac','report-fighter-action-handlers.py')
    f834=load('f836f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=load('f836f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=load('f836zero','verify-fighter-actionzero-natural-source.py')
    switch=load('f836switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BASE)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original whole fighter/afterRET DATA geometry changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={row['action']:int(row['handler'],16) for row in mp}
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(19684,5308,820,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current entire natural C++ ABI/COFF geometry shifted')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,switch,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'original 5 whole packed tables not checked')
    # C8/C9/CA all begin physically with genuine ConfigureStorm
    # push FF; push 4; push 3; MOV ECX; CALL.
    starts=[i for i,x in enumerate(ins) if x.mnemonic=='push' and x.op_str=='0xff'
       and i+4<len(ins) and ins[i+1].op_str=='4' and ins[i+2].op_str=='3'
       and ins[i+4].mnemonic=='call']
    need(len(starts)>=3,'three true C8/C9/CA source entries not found')
    at=starts[-3:]
    after=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0xcc')
        and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(after)==1 and after[0]>at[-1],'next CB source sentinel moved')
    physical=[]
    for action,start,end,next_action in zip((0xc8,0xc9,0xca),at,
                                             [at[1],at[2],after[0]],(0xc9,0xca,0xcb)):
        nb,nx,nfields,bad=EXPECTED[action]
        src=ins[start:end]
        result=f834.physical_case(rd,pe,d,code,refs,src,by,action,nb,nfields,bad,next_action,f820)
        need(result['native_complete_x86']==nx,'original case x86 count wrong')
        for j in result['original_native_enclosing_parent_JMP_exit_ordinals']:
            need(src[j].op_str==hex(ret-4),
                 'original case long return not source parent epilogue')
        if action==0xca:
            need(result['original_native_enclosing_parent_JMP_exit_ordinals']==[56,120],
                 'real CA original two direct exit ordinals changed')
        physical.append(result)
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,native_tail,0x52cb25,fields,ret-46,3)
    tail_wrong=[j for j in range(46) if j not in mask
                and native_tail[j]!=code[ret-46+j]]
    need(tail_wrong==[10,12,16,19],
         'new original CA should rotate four true common getter GPR operand bytes')
    out={'original_whole_boss':'0x005214B0',
      'native_whole_callable_CODE_B':46755,
      'current_source_entire_callable_CODE_B':ret,
      'real_native_C8_C9_CA_complete_cases':physical,
      'new_real_CA_inner_CODE_B':418,
      'new_real_CA_x86':121,
      'new_real_CA_PE_fields':11,
      'true_CA_nonrelocation_wrong_offsets':[203,204,414,415],
      'native_five_complete_afterRET_tables_rechecked':True,
      'real_packed_afterRET_DATA_B':901,
      'new_46B_native_default_GPR_wrong_offsets':tail_wrong,
      'native_whole_original_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F836 original CA whole 418B/121 x86/11 original PE fields restored in 19684B/5308x86 whole 005214B0 fighter, only native enclosing epilogue JMP offsets 203/204 414/415 remain. Native prior C8/C9, all five 901B packed tables checked; default suffix four GPR bytes differ. Enclosing original giant NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as ex:
        print('F836 original CA whole parent FAILED:',ex,file=sys.stderr)
        raise SystemExit(1)
