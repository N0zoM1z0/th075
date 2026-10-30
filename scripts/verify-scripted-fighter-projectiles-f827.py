#!/usr/bin/env python3
"""F827: original A7/A8 350B projectile cases recover native shared tail GPR phase.

Regenerate targeted F826 parent with complete earlier source cases;
add two actual 350B/97-x86/12-native-PE-field A7/A8 actions and compile
ONE entire affected 46KB fighter C++ parent. Real stage-zero sprite 38,
signed 30x direction, short F00 cooldown and real direct epilogue JMP.
After these actual original actions, the 46B default/getter once
again has ALL 34/34 original nonrelocation bytes equal plus three true
PE REL32 calls. Recheck A3/A4/A5, nine preceding timers, 9E and 901B
afterRET DATA. Whole original game still NONEXACT, no split-case credit.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f827-scripted-projectiles'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
NEW=(0xa7,0xa8)
NEXT=(0xa8,0xb4)
PRIOR=(0xa3,0xa4,0xa5)
PRIOR_NEXT=(0xa4,0xa5,0xa7)

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(tag,file):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/file)
    need(sp is not None and sp.loader is not None,'missing native original source helper '+file)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def natural_source(info):
    O.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-no-counter-landings-f826.py')],
       cwd=R,capture_output=True,text=True,timeout=1200)
    (O/'f826-prior-targeted-native.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'previous full fighter source and PE check failed '+
         (run.stdout+run.stderr)[-880:])
    src=(R/'.analysis/f826-scripted-no-counter/Boss005214B0-F826-full.cpp').read_text()
    member='void PrepareActionAt453D60(int);'
    glob='extern float g_ContactProjectionAt00657888;'
    need(src.count(member)==src.count(glob)==1,
         'real original sprite/cooldown declaration insertion point changed')
    src=src.replace(member,member+
         ' void StartAnimationAt46D000(int); void SpawnAt453C80(int,float,float,char,int);',1)
    src=src.replace(glob,glob+'\nextern float g_ProjectileFallAt006590B4;',1)
    inc=(R/'probes/FighterScriptedProjectileLaunchF827.inc').read_text()
    need(inc.count('case F642_CASE:')==inc.count('return;')==1
         and 'g_ProjectileFallAt006590B4' in inc
         and 'SpawnAt453C80(0x38' in inc,
         'real original A7/A8 natural projectile cooldown/source behavior changed')
    for action in NEW:
        meta=info[action][1]
        need(meta['native_original_complete_inner_CODE_bytes']==350
             and meta['original_complete_x86_instruction_roles']==97
             and meta['native_original_cooldown_short_offset']==0xf00
             and meta['native_original_sprite_kind']==0x38
             and meta['native_original_next_action']==(0 if action==0xa7 else 2),
             'real original stage0 sprite/trajectory source parameter differs')
        old=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(old)==1,'actual original case source placeholder missing '+hex(action))
        defs={'F642_CASE':f'0x{action:X}',
              'F642_COUNTER':'0xF00',
              'F642_NEXT_ACTION':str(meta['native_original_next_action'])}
        text='\n'.join('#define '+k+' '+v for k,v in defs.items())
        text+='\n#include "FighterScriptedProjectileLaunchF827.inc"\n'
        text+='\n'.join('#undef '+k for k in defs)
        src=src.replace(old,text,1)
    return src

def compile_one(src):
    cpp=O/'Boss005214B0-F827-full.cpp'
    obj=O/'Boss005214B0-F827-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,d;winemenubuilder.exe=d'.replace('winewayland.drv,d','winewayland.drv=d')
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=env,capture_output=True,text=True,timeout=290)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'whole fighter actual 0xA7/0xA8 C++ compile failed '+(run.stdout+run.stderr)[-850:])
    return obj

def main():
    rd=load('f827_reader','compare-coff-function.py')
    ac=load('f827_actions','report-fighter-action-handlers.py')
    f642=load('f827_f642','verify-fighter-projectile-launch-f642.py')
    f641=load('f827_f641','verify-fighter-no-counter-landings-f641.py')
    f633=load('f827_f633','verify-fighter-landing-siblings-f633.py')
    f631=load('f827_f631','verify-fighter-landing-timer96-f631.py')
    f637=load('f827_f637','verify-fighter-ground-boost-f637.py')
    f820=load('f827_f820','verify-scripted-fighter-landing-trio-f820.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
        if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original complete giant/native DATA geometry changed')
    _,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals={a:f642.native_case(rd,pe,d,boss,by,a) for a in NEW}
    obj=compile_one(natural_source(originals))
    code,refs=rd.object_function(obj,SYM)
    instructions=[]
    for x in d.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    ret=instructions[-1].address+instructions[-1].size
    need((ret,len(instructions),len(refs),len(code)-ret)==(17276,4586,746,901)
         and instructions[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'new full source native saved-this/COFF/901B DATA geometry changed')
    marker=[i for i,x in enumerate(instructions) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0xb5')
         and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=2*97+3*71+3*73+66+6*73,
         'native following 0xB4 source marker not physically bounded')
    end=marker[0]
    block=instructions[end-2*97:end]
    results=[]
    for j,action in enumerate(NEW):
        original,meta=originals[action]
        cur=block[j*97:(j+1)*97]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[NEXT[j]]-by[action])
        need(hi-lo==len(raw)==350 and len(original)==len(cur)==97
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(original,cur)),
             'real original projectile 350B/97-x86 source opcode/width differs')
        fields=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,by[action],fields,lo,12)
        for ordinal,(target,mn,symbol) in f642.FIELDS.items():
            a,b=original[ordinal],cur[ordinal]
            at=[r for r in fields if b.address<=r['offset']<b.address+b.size]
            need(a.mnemonic==b.mnemonic==mn and len(at)==1
                 and symbol in at[0]['symbol']
                 and at[0]['offset']-lo==a.address-by[action]+a.size-4,
                 'real native sprite/cooldown original PE field ordinal moved '+hex(action))
        bad=[k for k in range(350) if k not in mask and raw[k]!=code[lo+k]]
        need(bad==[346,347]
             and original[-1].mnemonic==cur[-1].mnemonic=='jmp'
             and original[-1].op_str=='0x52cb4f'
             and cur[-1].op_str==hex(ret-4),
             'only native whole enclosing function epilogue long JMP bytes may differ '+hex(action))
        results.append({'action':hex(action),'entire_native_inner_B':350,
            'native_x86':97,'true_PE_fields':12,
            'authentic_parent_external_JMP_wrong_bytes':bad})
    previous=instructions[end-2*97-3*71:end-2*97]
    for j,action in enumerate(PRIOR):
        original,meta=f641.native_case(rd,pe,d,boss,by,action)
        cur=previous[j*71:(j+1)*71]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[PRIOR_NEXT[j]]-by[action])
        need(hi-lo==264 and len(original)==len(cur)==71
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(original,cur)),
             'preceding original A3/A4/A5 source no longer full native width')
        mask=f820.physical_fields(rd,raw,by[action],
            [r for r in refs if lo<=r['offset']<hi],lo,9)
        need([k for k in range(264) if k not in mask and raw[k]!=code[lo+k]]==[260,261],
             'previous original no-counter real GPR/source byte phase shifted')
    # Before A3 the three 9F/A0/A1 timers and 9E source, then the
    # earlier six consecutive 96..9C original PE/source cases.
    before=instructions[end-2*97-3*71-3*73:end-2*97-3*71]
    for j,action in enumerate((0x9f,0xa0,0xa1)):
        orig,meta=f633.original_case(rd,pe,d,boss,by,action)
        cur=before[j*73:(j+1)*73]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[(0xa0,0xa1,0xa3)[j]]-by[action])
        need(hi-lo==276 and len(orig)==len(cur)==73
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(orig,cur)),
             'previous actual 9F/A0/A1 original source moved')
        mask=f820.physical_fields(rd,raw,by[action],
            [r for r in refs if lo<=r['offset']<hi],lo,9)
        need([k for k in range(276) if k not in mask and raw[k]!=code[lo+k]]==[272,273],
             'prior timer original native GPR/register phase changed')
    q=end-2*97-3*71-3*73
    native9e,_=f637.original_case(rd,pe,d,boss,by)
    cur=instructions[q-66:q]
    lo,hi=cur[0].address,cur[-1].address+cur[-1].size
    raw=rd.pe_bytes_at(pe,by[0x9e],243)
    need(hi-lo==243 and len(native9e)==len(cur)==66
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(native9e,cur)),
         'prior native 9E x86/source geometry changed')
    mask=f820.physical_fields(rd,raw,by[0x9e],
        [r for r in refs if lo<=r['offset']<hi],lo,8)
    need([k for k in range(243) if k not in mask and raw[k]!=code[lo+k]]==[202,203,239,240],
         'prior native 9E true two parent exits changed')
    six=instructions[q-66-6*73:q-66]
    for j,a in enumerate((0x96,0x97,0x98,0x9a,0x9b,0x9c)):
        original,_=(f631.original_case(rd,pe,d,boss,by) if a==0x96
                    else f633.original_case(rd,pe,d,boss,by,a))
        cur=six[j*73:(j+1)*73]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[a],by[(0x97,0x98,0x9a,0x9b,0x9c,0x9e)[j]]-by[a])
        need(hi-lo==276 and len(original)==len(cur)==73
             and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(original,cur)),
             'earlier native six timers x86 changed')
        mask=f820.physical_fields(rd,raw,by[a],
            [r for r in refs if lo<=r['offset']<hi],lo,9)
        need([k for k in range(276) if k not in mask and raw[k]!=code[lo+k]]==[272,273],
             'earlier native timer nonrelocated operand differs beyond giant final JMP')
    # Critical original native 46B fallback and shared getter suffix:
    # NO unrelocated machine-byte differences remain, including the
    # exact original EBP saved-this and original EDX/EAX/ECX phase.
    true_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,true_tail,0x52cb25,fields,ret-46,3)
    native_ins=list(d.disasm(true_tail,0x52cb25))
    generated_ins=list(d.disasm(code[ret-46:ret],ret-46))
    need(len(mask)==12 and len(native_ins)==len(generated_ins)==16
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(native_ins,generated_ins))
         and all(true_tail[k]==code[ret-46+k] for k in range(46) if k not in mask),
         'current original full 46B shared default must match all 34/34 native nonrelocation bytes')
    result={'original_whole_boss':'0x005214B0',
       'native_original_whole_callable_CODE_B':46755,
       'new_source_whole_callable_CODE_B':ret,
       'two_original_A7_A8_projectile_cases':results,
       'new_original_source_backed_inner_B':700,
       'new_original_x86':194,'new_original_PE_calls_globals':24,
       'previous_three_no_counter_landing_states_physically_checked':True,
       'previous_nine_timer_states_and_original_9E_physically_checked':True,
       'original_saved_this_EBP_0x10_still_correct':True,
       'native_46B_shared_default_getter_nonrelocation_match':'34/34',
       'native_46B_default_actual_original_PE_fields':3,
       'original_separate_afterRET_DATA_B':901,
       'whole_game_callable_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F827 original two A7/A8 350B/97-x86/12-PE-field projectile cases in entire 17,276B/4,586-x86 new parent. Original 46B/16-x86 default/getter now 34/34 native nonrelocation CODE bytes equal plus 3 physical PE fields, naturally restored by REAL preceding sprite behavior. Earlier A3-5/9 timers/9E verified, 901B DATA. Whole 46,755B giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F827 selected original projectile whole source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
