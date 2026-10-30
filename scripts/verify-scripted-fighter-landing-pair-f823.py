#!/usr/bin/env python3
"""F823: original 9B/9C timer landings in *whole* growing 005214B0 fighter.

Rebuild and verify selected F822's four real native cases first.
Then add genuine 9B and 9C source using original F633 parameters,
and freshly compile the one affected full VC7.1 fighter parent.
All SIX timer cases are 276B/73-x86/9 physical typed PE fields,
and all original register/float bytes match except 2 real enclosing
function-epilogue JMP displacement bytes per case. Recheck native
arc91, three earlier landings, 0x63 shifted PE field and 901B
separate switch DATA. No accepted callable case/giant CODE.
"""
from pathlib import Path
import importlib.util
import json
import os
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f823-scripted-9b9c'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ACTIONS=(0x96,0x97,0x98,0x9a,0x9b,0x9c)
NEXT=(0x97,0x98,0x9a,0x9b,0x9c,0x9e)

def need(p,msg):
    if not p:raise ValueError(msg)

def load(tag,name):
    s=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(s is not None and s.loader is not None,'missing native original verifier '+name)
    m=importlib.util.module_from_spec(s)
    sys.modules[tag]=m
    s.loader.exec_module(m)
    return m

def source(originals):
    O.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(R/'scripts/repo-python'),str(R/'scripts/verify-scripted-fighter-timed-landings-f822.py')],
      cwd=R,capture_output=True,text=True,timeout=1200)
    (O/'f822-native-prior-check.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'previous original F822 complete C++ and native PE checks failed '+
         (run.stdout+run.stderr)[-850:])
    text=(R/'.analysis/f822-scripted-timed/Boss005214B0-F822-all.cpp').read_text()
    inc=(R/'probes/FighterScriptedLandingPairF823.inc').read_text()
    need(inc.count('case F633_CASE:')==inc.count('return;')==1,
         'real native landing source should exit directly to giant epilogue')
    for action in (0x9b,0x9c):
        record=originals[action][1]
        need(record['native_trajectory_counter_offset']==0xf00
             and not record['real_extra_short_0xF0A']
             and record['original_followup_action_state']==2
             and record['original_initial_float_height']==(-10.0 if action==0x9b else -13.0),
             'actual actor-specific native 9B/9C original values changed')
        mark=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(text.count(mark)==1,'original next source case marker missing '+hex(action))
        fields={'F633_CASE':f'0x{action:X}','F633_COUNTER':'0xF00',
           'F633_START_HEIGHT':repr(record['original_initial_float_height'])+'f',
           'F633_NEXT_ACTION':'2','F633_EXTRA_FLAG':'0','F633_EXTRA_BEFORE':'0'}
        insert='\n'.join(f'#define {k} {v}' for k,v in fields.items())
        insert+='\n#include "FighterScriptedLandingPairF823.inc"\n'
        insert+='\n'.join('#undef '+k for k in fields)
        text=text.replace(mark,insert,1)
    need(text.count('#include "FighterScriptedLandingPairF823.inc"')==2,
         'both complete original source states required')
    return text

def compile_source(src):
    cpp=O/'Boss005214B0-F823-full.cpp'
    obj=O/'Boss005214B0-F823-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
      cwd=R,capture_output=True,text=True,env=env,timeout=265)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'F823 entire selected original-shaped VC7.1 compile failed '+
         (run.stdout+run.stderr)[-800:])
    return obj

def main():
    rd=load('f823_rd','compare-coff-function.py')
    ac=load('f823_actions','report-fighter-action-handlers.py')
    f633=load('f823_f633','verify-fighter-landing-siblings-f633.py')
    f631=load('f823_f631','verify-fighter-landing-timer96-f631.py')
    f629=load('f823_f629','verify-fighter-arc91-f629.py')
    f628=load('f823_f628','verify-fighter-jump-landings-f628.py')
    f626=load('f823_f626','verify-fighter-mode63-basic-f626.py')
    f820=load('f823_f820','verify-scripted-fighter-landing-trio-f820.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original whole game function/afterRET DATA physical identity changed')
    _,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals={a:(f631.original_case(rd,pe,d,boss,by) if a==0x96
                   else f633.original_case(rd,pe,d,boss,by,a)) for a in ACTIONS}
    obj=compile_source(source(originals))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(14848,3912,669,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'full selected source emitted wrong current owner frame or original 901B switch DATA')
    markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x9f')
       and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size
               for r in refs)]
    need(len(markers)==1 and markers[0]>=len(ACTIONS)*73,
         'real 9E next original source action marker not unique')
    k=markers[0]
    cases=ins[k-6*73:k]
    results=[]
    for j,action in enumerate(ACTIONS):
        native,meta=originals[action]
        current=cases[j*73:(j+1)*73]
        lo,hi=current[0].address,current[-1].address+current[-1].size
        original=rd.pe_bytes_at(pe,by[action],by[NEXT[j]]-by[action])
        need(len(original)==hi-lo==276 and len(current)==len(native)==73
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(native,current)),
             'whole physical original source 96-9C x86 sequence differs '+hex(action))
        physical=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,original,by[action],physical,lo,9)
        for ordinal,(target,mn,symbol) in f631.FIELDS.items():
            a,b=native[ordinal],current[ordinal]
            x=[r for r in physical if b.address<=r['offset']<b.address+b.size]
            need(a.mnemonic==b.mnemonic==mn and len(x)==1
                 and symbol in x[0]['symbol']
                 and x[0]['offset']-lo==a.address-by[action]+a.size-4,
                 'real original 96-9C PE call/global field position moved '+hex(action))
        wrong=[p for p in range(276) if p not in mask and original[p]!=code[lo+p]]
        need(wrong==[272,273] and current[-1].mnemonic==native[-1].mnemonic=='jmp'
             and current[-1].op_str==hex(ret-4) and native[-1].op_str=='0x52cb4f',
             'original full landing case must differ only in genuine external epilogue rel32 bytes '+hex(action))
        results.append({'action':hex(action),'original_entire_CASE_CODE_B':276,
            'physical_native_x86':73,'original_true_PE_fields':9,
            'original_unmasked_wrong_bytes':wrong,
            'original_ENCLOSING_FUNCTION_exact':False})
    # Bound preceding 0x91 and earlier 8C/8F/90 by full native
    # instruction counts; all per-ordinal physically typed PE fields
    # checked against ORIGINAL locations (never source-only masks).
    n91,meta=f629.real_original(rd,pe,d,boss,by)
    i91=ins[k-6*73-78:k-6*73]
    lo,hi=i91[0].address,i91[-1].address+i91[-1].size
    need(len(i91)==len(n91)==78 and hi-lo==288
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(n91,i91)),
         'original prior 91 entire native action source changed')
    raw=rd.pe_bytes_at(pe,by[0x91],288)
    physical=[r for r in refs if lo<=r['offset']<hi]
    mask=f820.physical_fields(rd,raw,by[0x91],physical,lo,12)
    need(sum(raw[p]!=code[lo+p] for p in range(288) if p not in mask)==37,
         'previous complete native 91 nonrelocation role differences changed')
    three=ins[k-6*73-78-3*80:k-6*73-78]
    need(len(three)==240,'earlier 8C/8F/90 original x86 sequence missing')
    for j,action in enumerate((0x8c,0x8f,0x90)):
        native,meta=f628.native_case(rd,pe,d,boss,by,action)
        cur=three[j*80:(j+1)*80]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        need(hi-lo==289 and all(a.mnemonic==b.mnemonic and a.size==b.size
                 for a,b in zip(native,cur)),
             'old 8C/8F/90 source no longer native x86 grammar')
        raw=rd.pe_bytes_at(pe,by[action],289)
        physical=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,by[action],physical,lo,8)
        need(sum(raw[p]!=code[lo+p] for p in range(289) if p not in mask)==55,
             'old source native landing has different actual GPR allocation')
    native63,meta=f626.original_case(rd,pe,d,boss,by)
    lo=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*25)
    hi=three[0].address
    cur=list(d.disasm(code[lo:hi],lo))
    need(hi-lo==417 and len(cur)==len(native63)==109
         and all(a.mnemonic==b.mnemonic for a,b in zip(native63,cur))
         and [i for i,(a,b) in enumerate(zip(native63,cur)) if a.size!=b.size]==[38,61],
         'physical previous mode63 native width negative changed')
    field_shifts={}
    for ordinal,(target,mn,symbol) in f626.FIELDS.items():
        n,s=native63[ordinal],cur[ordinal]
        field=[r for r in refs if s.address<=r['offset']<s.address+s.size]
        need(len(field)==1 and symbol in field[0]['symbol'] and field[0]['addend']==0,
             'native previous mode63 typed field altered')
        field_shifts[str(ordinal)]=field[0]['offset']-lo-(n.address-by[0x63]+n.size-4)
    need(field_shifts=={'0':0,'22':0,'48':-1,'71':0,'94':0,'99':0,'107':0},
         'one true PE original mode63 source relocation no longer shifted -1')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tfields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,tail,0x52cb25,tfields,ret-46,3)
    need([p for p in range(46) if p not in mask and tail[p]!=code[ret-46+p]]==[10,12,16,19],
         'original default tail current four GPR operand differences shifted')
    report={'original_game_function':'0x005214B0',
      'native_original_whole_CODE_B':46755,
      'complete_current_source_parent_B':ret,
      'new_9B_9C_original_inner_CODE_B':552,
      'new_9B_9C_original_x86':146,
      'new_real_typed_PE_fields':18,
      'all_six_96_97_98_9A_9B_9C_complete_native_states':results,
      'source_native_shifted_mode63_PE_field':field_shifts,
      'earlier_original_91_and_three_landings_physically_rechecked':True,
      'original_separate_afterRET_DATA_B':901,
      'original_whole_game_CODE_exact':False,
      'new_accepted_authored_whole_CODE_B':0,
      'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F823: 9B/9C each original 276B/73-x86/9 genuine PE fields integrated in entire 14848B/3912-x86 parent; all SIX consecutive original timers match all nonrelocation bytes except two physical enclosing parent-jump bytes per case. Prior arc91/3 landings/mode63 shift and 901B DATA rechecked. Giant NONEXACT, no callable exact credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as exc:
        print('F823 original whole 9B/9C source proof FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
