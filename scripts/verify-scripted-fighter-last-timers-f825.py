#!/usr/bin/env python3
"""F825: original 9F/A0/A1 276B/73-x86 timer states in whole fighter.

Regenerate pinned prior F824 native PE/source proof. Add three real
normal VC7.1 C++ timed-landing states with true -9/-10/-13 heights,
action0 transitions, +0xF00 counter; independently verify 9 original
PE fields each in a newly compiled 15,859B whole parent.
Recheck previous 9E, all six earlier timer states, 901B switch
DATA and authentic default PE fields. Only native enclosing-parent
long-JMP operand bytes (272,273 per timer) differ; no exact credit.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f825-scripted-last-timers'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
FRESH=(0x9f,0xa0,0xa1)
FOLLOW=(0xa0,0xa1,0xa3)
OLD=(0x96,0x97,0x98,0x9a,0x9b,0x9c)
NEXT=(0x97,0x98,0x9a,0x9b,0x9c,0x9e)

def need(test,msg):
    if not test:raise ValueError(msg)

def load(tag,file):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/file)
    need(sp is not None and sp.loader is not None,'native original PE helper missing '+file)
    m=importlib.util.module_from_spec(sp)
    sys.modules[tag]=m
    sp.loader.exec_module(m)
    return m

def make_source(info):
    O.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(R/'scripts/repo-python'),
         str(R/'scripts/verify-scripted-fighter-ground-boost-f824.py')],
         cwd=R,capture_output=True,text=True,timeout=1300)
    (O/'prior-f824-original-pe.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'prior whole-source native 9E PE proof failed '+(run.stdout+run.stderr)[-840:])
    text=(R/'.analysis/f824-scripted-9e/Boss005214B0-F824-full.cpp').read_text()
    inc=(R/'probes/FighterScriptedLandingSiblingsF822.inc').read_text()
    need(inc.count('case F633_CASE:')==inc.count('return;')==1,
         'genuine original landing C++ direct function exit changed')
    for action in FRESH:
        entry=info[action][1]
        need(entry['original_followup_action_state']==0 and not entry['real_extra_short_0xF0A']
             and entry['native_trajectory_counter_offset']==0xf00
             and entry['original_initial_float_height']=={0x9f:-9.,0xa0:-10.,0xa1:-13.}[action],
             'native original actor last landing parameter changed '+hex(action))
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(text.count(marker)==1,'original 9F/A0/A1 source marker missing '+hex(action))
        defs={'F633_CASE':f'0x{action:X}','F633_COUNTER':'0xF00',
              'F633_START_HEIGHT':repr(entry['original_initial_float_height'])+'f',
              'F633_NEXT_ACTION':'0','F633_EXTRA_FLAG':'0','F633_EXTRA_BEFORE':'0'}
        replacement='\n'.join('#define '+k+' '+v for k,v in defs.items())
        replacement+='\n#include "FighterScriptedLandingSiblingsF822.inc"\n'
        replacement+='\n'.join('#undef '+k for k in defs)
        text=text.replace(marker,replacement,1)
    return text

def compile_source(src):
    cpp=O/'Boss005214B0-F825-full.cpp'
    obj=O/'Boss005214B0-F825-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=env,capture_output=True,text=True,timeout=270)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'affected whole original 46KB C++ compilation failed '+(run.stdout+run.stderr)[-850:])
    return obj

def main():
    rd=load('f825_reader','compare-coff-function.py')
    ac=load('f825_actions','report-fighter-action-handlers.py')
    f633=load('f825_f633','verify-fighter-landing-siblings-f633.py')
    f631=load('f825_f631','verify-fighter-landing-timer96-f631.py')
    f637=load('f825_f637','verify-fighter-ground-boost-f637.py')
    f820=load('f825_f820','verify-scripted-fighter-landing-trio-f820.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original 46KB function/afterRET ownership changed')
    _,mapped=ac.report_boss(rd,pe,d,boss)
    by={m['action']:int(m['handler'],16) for m in mapped}
    physical={a:f633.original_case(rd,pe,d,boss,by,a) for a in FRESH}
    obj=compile_source(make_source(physical))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(15859,4189,700,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'original frame or entire compiled source geometry drifted')
    marker=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0xa4')
          and any('g_FighterProbeMarker' in r['symbol']
             and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=219+66+438,
         'actual source next native 0xA3 handler marker not unique')
    p=marker[0]
    current=ins[p-219:p]
    results=[]
    for j,action in enumerate(FRESH):
        original,meta=physical[action]
        source=current[j*73:(j+1)*73]
        a,b=source[0].address,source[-1].address+source[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[FOLLOW[j]]-by[action])
        need(b-a==len(raw)==276 and len(original)==len(source)==73
             and all(x.mnemonic==y.mnemonic and x.size==y.size
                     for x,y in zip(original,source)),
             'source original 9F/A0/A1 whole native x86 grammar changed')
        fields=[r for r in refs if a<=r['offset']<b]
        mask=f820.physical_fields(rd,raw,by[action],fields,a,9)
        for ordinal,(target,mn,sym) in f631.FIELDS.items():
            x,y=original[ordinal],source[ordinal]
            f=[r for r in fields if y.address<=r['offset']<y.address+y.size]
            need(x.mnemonic==y.mnemonic==mn and len(f)==1 and sym in f[0]['symbol']
                 and f[0]['offset']-a==x.address-by[action]+x.size-4,
                 'native 9F/A0/A1 physically typed PE call target ordinal shifted')
        diff=[k for k in range(276) if k not in mask and raw[k]!=code[a+k]]
        need(diff==[272,273] and original[-1].op_str=='0x52cb4f'
             and source[-1].op_str==hex(ret-4),
             'native complete timer nonfield bytes must differ only in original enclosing function JMP')
        results.append({'action':hex(action),'native_original_whole_inner_B':276,
                        'native_x86':73,'physically_attested_PE_fields':9,
                        'remaining_external_parent_JMP_byte_offsets':diff})
    # Check 9E whole native physical x86 and all eight original typed
    # call/global references in the *new* parent.
    true9e,meta=f637.original_case(rd,pe,d,boss,by)
    src9e=ins[p-219-66:p-219]
    a,b=src9e[0].address,src9e[-1].address+src9e[-1].size
    raw=rd.pe_bytes_at(pe,by[0x9e],243)
    need(b-a==243 and len(src9e)==len(true9e)==66
         and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(true9e,src9e)),
         'native 9E source changed by following three timer cases')
    mask=f820.physical_fields(rd,raw,by[0x9e],
             [r for r in refs if a<=r['offset']<b],a,8)
    need([k for k in range(243) if k not in mask and raw[k]!=code[a+k]]==[202,203,239,240],
         'original 9E two enclosing-function JMP bytes changed')
    # Every one of prior six timers remains physically equal modulo
    # its honest 2B external final-JMP difference.
    six=ins[p-219-66-6*73:p-219-66]
    for j,action in enumerate(OLD):
        old,info=(f631.original_case(rd,pe,d,boss,by) if action==0x96 else
                  f633.original_case(rd,pe,d,boss,by,action))
        section=six[j*73:(j+1)*73]
        lo,hi=section[0].address,section[-1].address+section[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[NEXT[j]]-by[action])
        need(hi-lo==276 and len(section)==len(old)==73
             and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(old,section)),
             'one previous original 96..9C native source invalid')
        mask=f820.physical_fields(rd,raw,by[action],
              [r for r in refs if lo<=r['offset']<hi],lo,9)
        need([i for i in range(276) if i not in mask and raw[i]!=code[lo+i]]==[272,273],
             'previous original timer GPR/whole case changed in new parent')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    refs_tail=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,tail,0x52cb25,refs_tail,ret-46,3)
    tail_wrong=[i for i in range(46) if i not in mask and tail[i]!=code[ret-46+i]]
    need(tail_wrong==[10,12,16,19],
         'original default GPR phase changed after timer source')
    summary={'original_giant':'0x005214B0','real_whole_game_CODE_B':46755,
       'new_whole_source_CODE_B':ret,'source_full_x86':len(ins),
       'three_new_9F_A0_A1_native_states':results,
       'new_native_complete_inner_B':828,
       'new_actual_PE_fields':27,
       'native_previous_9E_and_six_timers_physically_checked':True,
       'native_901B_afterRET_DATA':901,
       'native_current_original_default_GPR_wrong_offsets':tail_wrong,
       'enclosing_original_function_exact':False,
       'accepted_new_whole_callable_CODE_B':0,
       'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F825 original 005214B0: 9F/A0/A1 three real 276B/73-x86/9-field timer actions in 15,859B/4,189-x86 whole source. All nine consecutive prior/current timers and 9E preserve true native PE fields, only two actual final parent-exit JMP bytes per timer. Giant NONEXACT, no accepted callable CODE.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F825 original 9F/A0/A1 whole source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
