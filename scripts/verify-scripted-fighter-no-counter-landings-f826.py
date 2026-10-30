#!/usr/bin/env python3
"""F826: original native A3/A4/A5 *counter-free* states in 46KB fighter.

The actual PE has three complete 264B/71-x86/9-field states with
NO F00 short reset. Regenerate F825 prior whole source, recompile
entire affected normal VC7.1 parent and verify the three new cases,
nine previous original timed landings, 9E ground boost, full
original 901B afterRET DATA. Each new state differs only in 2
actual enclosing-giant final JMP operand bytes; not callable exact.
No accepted-unit mass cold replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f826-scripted-no-counter'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
NEW=(0xa3,0xa4,0xa5)
NEXT=(0xa4,0xa5,0xa7)
TIMER=(0x96,0x97,0x98,0x9a,0x9b,0x9c,0x9f,0xa0,0xa1)
TIMER_NEXT=(0x97,0x98,0x9a,0x9b,0x9c,0x9e,0xa0,0xa1,0xa3)

def need(v,msg):
    if not v:raise ValueError(msg)

def load(tag,file):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/file)
    need(sp is not None and sp.loader is not None,'native PE reader not available '+file)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def make_source(meta):
    O.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-last-timers-f825.py')],
       cwd=R,text=True,capture_output=True,timeout=1250)
    (O/'f825-prior-physical-source.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'previous whole native game source did not independently verify '+
         (run.stdout+run.stderr)[-850:])
    source=(R/'.analysis/f825-scripted-last-timers/Boss005214B0-F825-full.cpp').read_text()
    inc=(R/'probes/FighterScriptedNoCounterF826.inc').read_text()
    need(inc.count('case F641_CASE:')==1 and inc.count('return;')==1
         and 'I16(F641_COUNTER)' not in inc and 'I16(0xF00)=0' not in inc,
         'true original counter-free native case source grammar changed')
    for action in NEW:
        info=meta[action][1]
        need(info['original_native_height']=={0xa3:-9.,0xa4:-10.,0xa5:-13.}[action]
             and info['original_native_next_action']==2
             and not info['original_short_counter_reset'],
             'true original A3/A4/A5 native ground parameters or counter absent changed')
        mark=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(mark)==1,'next original state C++ marker absent '+hex(action))
        defs={'F641_CASE':f'0x{action:X}',
              'F641_START_HEIGHT':repr(info['original_native_height'])+'f',
              'F641_NEXT_ACTION':'2'}
        text='\n'.join('#define '+k+' '+v for k,v in defs.items())
        text+='\n#include "FighterScriptedNoCounterF826.inc"\n'
        text+='\n'.join('#undef '+k for k in defs)
        source=source.replace(mark,text,1)
    return source

def compile_source(src):
    cpp=O/'Boss005214B0-F826-full.cpp'
    obj=O/'Boss005214B0-F826-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv= d;winemenubuilder.exe=d'.replace('= d','=d')
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,text=True,capture_output=True,env=env,timeout=285)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'whole original counter-free case source VC7.1 compile failed '+
         (p.stdout+p.stderr)[-850:])
    return obj

def main():
    rd=load('f826_rd','compare-coff-function.py')
    ac=load('f826_ac','report-fighter-action-handlers.py')
    f641=load('f826_f641','verify-fighter-no-counter-landings-f641.py')
    f633=load('f826_f633','verify-fighter-landing-siblings-f633.py')
    f631=load('f826_f631','verify-fighter-landing-timer96-f631.py')
    f637=load('f826_f637','verify-fighter-ground-boost-f637.py')
    f820=load('f826_f820','verify-scripted-fighter-landing-trio-f820.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
         if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original target entire fighter/source DATA changed')
    _,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals={a:f641.native_case(rd,pe,d,boss,by,a) for a in NEW}
    obj=compile_source(make_source(originals))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(16606,4396,724,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'new whole source original C++ ABI, x86 or packed DATA geometry changed')
    marker=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0xa8')
        and any('g_FighterProbeMarker' in r['symbol']
           and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=3*71+3*73+66+6*73,
         'actual next native 0xA7 game case marker not uniquely found')
    end=marker[0]
    newins=ins[end-3*71:end]
    results=[]
    for j,a in enumerate(NEW):
        native,meta=originals[a]
        cur=newins[j*71:(j+1)*71]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[a],by[NEXT[j]]-by[a])
        need(hi-lo==len(raw)==264 and len(cur)==len(native)==71
             and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(native,cur)),
             'actual original complete native no-counter x86 roles/widths differ '+hex(a))
        fields=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,by[a],fields,lo,9)
        # The original no-counter source removes TWO x86 and field
        # ordinals compared to the 73-x86 F631 timer family.
        for ordinary,(target,mn,symbol) in f631.FIELDS.items():
            index=ordinary-2 if ordinary>=31 else ordinary
            x,y=native[index],cur[index]
            f=[r for r in fields if y.address<=r['offset']<y.address+y.size]
            need(x.mnemonic==y.mnemonic==mn and len(f)==1
                 and symbol in f[0]['symbol']
                 and f[0]['offset']-lo==x.address-by[a]+x.size-4,
                 'actual original no-counter PE field source ordinal shifted '+hex(a))
        wrong=[k for k in range(264) if k not in mask and raw[k]!=code[lo+k]]
        need(wrong==[260,261] and native[-1].op_str=='0x52cb4f'
             and cur[-1].op_str==hex(ret-4),
             'original no-counter case must differ ONLY in authentic enclosing-giant JMP operand bytes')
        results.append({'native_original_action':hex(a),
              'original_complete_inner_CODE_B':264,'native_x86':71,
              'physical_original_PE_fields':9,
              'real_external_epilogue_wrong_offsets':wrong})
    # Recheck 9F/A0/A1 actual full original timed cases in newly compiled
    # source; preserve the actor initial float and native PE calls.
    prior=ins[end-3*71-3*73:end-3*71]
    for j,a in enumerate((0x9f,0xa0,0xa1)):
        native,meta=f633.original_case(rd,pe,d,boss,by,a)
        cur=prior[j*73:(j+1)*73]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[a],by[(0xa0,0xa1,0xa3)[j]]-by[a])
        need(hi-lo==276 and len(cur)==len(native)==73
             and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(native,cur)),
             'preceding real timer whole x86 geometry changed')
        mask=f820.physical_fields(rd,raw,by[a],
              [r for r in refs if lo<=r['offset']<hi],lo,9)
        need([k for k in range(276) if k not in mask and raw[k]!=code[lo+k]]==[272,273],
             'previous 9F/A0/A1 original nonrelocation machine source changed')
    native9e,_=f637.original_case(rd,pe,d,boss,by)
    cur9e=ins[end-3*71-3*73-66:end-3*71-3*73]
    lo,hi=cur9e[0].address,cur9e[-1].address+cur9e[-1].size
    raw=rd.pe_bytes_at(pe,by[0x9e],243)
    need(hi-lo==243 and len(cur9e)==len(native9e)==66
         and all(x.mnemonic==y.mnemonic and x.size==y.size
                 for x,y in zip(native9e,cur9e)),
         'preceding real ground boost full source x86 changed')
    mask=f820.physical_fields(rd,raw,by[0x9e],
              [r for r in refs if lo<=r['offset']<hi],lo,8)
    need([k for k in range(243) if k not in mask and raw[k]!=code[lo+k]]==[202,203,239,240],
         'earlier native 9E source actual exterior JMP bytes changed')
    six=ins[end-3*71-3*73-66-6*73:end-3*71-3*73-66]
    for j,a in enumerate((0x96,0x97,0x98,0x9a,0x9b,0x9c)):
        native,_=(f631.original_case(rd,pe,d,boss,by) if a==0x96
                  else f633.original_case(rd,pe,d,boss,by,a))
        cur=six[j*73:(j+1)*73]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[a],by[(0x97,0x98,0x9a,0x9b,0x9c,0x9e)[j]]-by[a])
        need(hi-lo==276 and len(cur)==len(native)==73
             and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(native,cur)),
             'earlier six native timer case instruction geometry altered')
        mask=f820.physical_fields(rd,raw,by[a],
              [r for r in refs if lo<=r['offset']<hi],lo,9)
        need([k for k in range(276) if k not in mask and raw[k]!=code[lo+k]]==[272,273],
             'earlier original PE timer case nonrelocation byte drift')
    n_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,n_tail,0x52cb25,
         [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tailwrong=[k for k in range(46) if k not in mask and n_tail[k]!=code[ret-46+k]]
    need(tailwrong==[10,12,16,19],'current default original GPR byte differences changed')
    result={'original_giant':'0x005214B0','native_whole_CODE_B':46755,
       'current_whole_source_B':ret,
       'original_new_no_counter_cases':results,
       'new_source_backed_native_inner_B':792,
       'new_native_x86':213,'genuine_native_PE_fields':27,
       'original_previous_nine_timer_cases_physically_checked':True,
       'original_ground_boost_9E_physically_checked':True,
       'original_postRET_independent_DATA_B':901,
       'native_default_GPR_operand_wrong_bytes':tailwrong,
       'whole_native_game_exact':False,'accepted_new_whole_callable_CODE_B':0,
       'all_unit_mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F826 original A3/A4/A5 three 264B/71-x86/9-PE-field cases in new 16606B/4396-x86 whole parent; all native nonexternal GPR/x87/call bytes exact, 2 true final enclosing-giant JMP operand bytes per case. Nine preceding timer cases, 9E, 901B afterRET DATA checked. Giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F826 original no-counter whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
