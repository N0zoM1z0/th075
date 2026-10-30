#!/usr/bin/env python3
"""F829: two authentic B4/B5 restart states in whole 46KB fighter source.

Rebuild F827 source first, then compile one full VC7.1 affected parent
with original 215B/60-x86/8-PE-field B4/B5 action source. Original two
back-to-back final JMPs plus earlier ground-reset exit go directly
to actual enclosing-giant epilogue. All original x86 and physical
PE fields match except 6 honest original parent-exit JMP bytes
per case. Previously sourced A7/A8 and full 46B default/getter
34/34 native nonrelocation CODE bytes remain correct. No whole exact.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f829-scripted-motion-restart'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
NEW=(0xb4,0xb5)
NEXT=(0xb5,0xc8)
ACTUAL_JMP_DIFFS=[169,170,206,207,211,212]

def need(p,msg):
    if not p:raise ValueError(msg)

def load(tag,file):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/file)
    need(sp is not None and sp.loader is not None,'missing original PE reader '+file)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def source(originals):
    O.mkdir(parents=True,exist_ok=True)
    proc=subprocess.run([str(R/'scripts/repo-python'),
         str(R/'scripts/verify-scripted-fighter-projectiles-f827.py')],
         cwd=R,capture_output=True,text=True,timeout=1400)
    (O/'f827-native-prior.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'previous original whole fighter PE proof failed '+
         (proc.stdout+proc.stderr)[-850:])
    code=(R/'.analysis/f827-scripted-projectiles/Boss005214B0-F827-full.cpp').read_text()
    include=(R/'probes/FighterScriptedMotionRestartF829.inc').read_text()
    need(include.count('case F645_CASE:')==1 and include.count('return;')==3
         and include.count('ResetAt453E20()')==2,
         'real native B4/B5 two ground and aux exits/source grammar changed')
    for action in NEW:
        meta=originals[action][1]
        need(meta['original_true_native_complete_CODE_bytes']==215
             and meta['native_complete_x86_instruction_roles']==60
             and meta['genuine_PE_COFF_targets']==8
             and meta['original_initial_float_height']==(8.0 if action==0xb4 else -8.0),
             'real original B4/B5 motion restart original PE parameters changed')
        needle=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(code.count(needle)==1,'current source original B4/B5 marker missing')
        defs={'F645_CASE':f'0x{action:X}',
              'F645_START_POS':repr(meta['original_initial_float_height'])+'f',
              'F645_AUX_ACTION':str(meta['original_native_auxiliary_action'])}
        src='\n'.join('#define '+k+' '+v for k,v in defs.items())
        src+='\n#include "FighterScriptedMotionRestartF829.inc"\n'
        src+='\n'.join('#undef '+k for k in defs)
        code=code.replace(needle,src,1)
    return code

def compile_one(src):
    cpp=O/'Boss005214B0-F829-full.cpp'
    obj=O/'Boss005214B0-F829-full.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv= d;winemenubuilder.exe=d'.replace('= d','=d')
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,capture_output=True,text=True,env=env,timeout=290)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'full original game source VC7.1 compile failed '+(p.stdout+p.stderr)[-950:])
    return obj

def main():
    rd=load('f829_rd','compare-coff-function.py')
    ac=load('f829_ac','report-fighter-action-handlers.py')
    f645=load('f829_f645','verify-fighter-motion-restart-f645.py')
    f642=load('f829_f642','verify-fighter-projectile-launch-f642.py')
    f641=load('f829_f641','verify-fighter-no-counter-landings-f641.py')
    f820=load('f829_f820','verify-scripted-fighter-landing-trio-f820.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
         if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original fighter complete game function identity changed')
    _,mp=ac.report_boss(rd,pe,d,boss)
    by={m['action']:int(m['handler'],16) for m in mp}
    originals={action:f645.native_case(rd,pe,d,boss,by,action) for action in NEW}
    obj=compile_one(source(originals))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(17676,4702,760,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'new full fighter source native saved-this frame/switch fields changed')
    marker=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0xc9')
        and any('g_FighterProbeMarker' in r['symbol']
           and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=2*60+2*97,
         'native following 0xC8 source marker not unique')
    k=marker[0]
    group=ins[k-120:k]
    cases=[]
    for j,action in enumerate(NEW):
        native,meta=originals[action]
        cur=group[j*60:(j+1)*60]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[NEXT[j]]-by[action])
        need(hi-lo==len(raw)==215 and len(native)==len(cur)==60
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                 for a,b in zip(native,cur)),
             'actual original B4/B5 complete x86 instruction geometry changed')
        fields=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,by[action],fields,lo,8)
        for index,(target,mn,symbol) in f645.FIELDS.items():
            a,b=native[index],cur[index]
            found=[r for r in fields if b.address<=r['offset']<b.address+b.size]
            need(a.mnemonic==b.mnemonic==mn and len(found)==1
                 and symbol in found[0]['symbol']
                 and found[0]['offset']-lo==a.address-by[action]+a.size-4,
                 'physical original PE target for B4/B5 moved '+str((action,index)))
        bad=[i for i in range(215) if i not in mask and raw[i]!=code[lo+i]]
        need(bad==ACTUAL_JMP_DIFFS
             and all(native[ordinal].mnemonic==cur[ordinal].mnemonic=='jmp'
                 and native[ordinal].op_str=='0x52cb4f'
                 and cur[ordinal].op_str==hex(ret-4)
                 for ordinal in (47,58,59)),
             'new B4/B5 may differ ONLY in three actual encompassing giant return JMP operands')
        cases.append({'native_action':hex(action),'complete_original_inner_CODE_B':215,
              'native_x86':60,'true_original_PE_fields':8,
              'genuine_external_epilogue_byte_differences':bad})
    # A7/A8 original projectile source must remain native-shaped in
    # the *new* parent including all 12 physical typed PE call fields.
    old=ins[k-120-194:k-120]
    for j,action in enumerate((0xa7,0xa8)):
        native,meta=f642.native_case(rd,pe,d,boss,by,action)
        cur=old[j*97:(j+1)*97]
        lo,hi=cur[0].address,cur[-1].address+cur[-1].size
        raw=rd.pe_bytes_at(pe,by[action],350)
        need(hi-lo==350 and len(cur)==len(native)==97
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(native,cur)),
             'earlier original A7/A8 sprite x86 width/roles differ in new parent')
        mask=f820.physical_fields(rd,raw,by[action],
             [r for r in refs if lo<=r['offset']<hi],lo,12)
        need([i for i in range(350) if i not in mask and raw[i]!=code[lo+i]]==[346,347],
             'earlier A7/A8 original physical sprite source changed')
    # The complete original 46B default/getter is STILL 34/34
    # unrelocated native bytes equal, with three real PE calls.
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,native_tail,0x52cb25,fields,ret-46,3)
    true=list(d.disasm(native_tail,0x52cb25))
    current=list(d.disasm(code[ret-46:ret],ret-46))
    need(len(true)==len(current)==16
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(true,current))
         and len(mask)==12
         and all(native_tail[i]==code[ret-46+i] for i in range(46) if i not in mask),
         'shared getter 46B original nonrelocation should remain entirely correct after true B4/B5')
    report={'original_game_giant':'0x005214B0',
       'real_native_entire_callable_CODE_B':46755,
       'current_whole_source_callable_CODE_B':ret,
       'two_original_B4_B5_game_case_sources':cases,
       'original_source_backed_inner_CODE_B':430,
       'original_full_native_x86':120,'true_original_typed_PE_fields':16,
       'previous_real_A7_A8_projectiles_physically_rechecked':True,
       'native_default_getter_46B_nonrelocation_byte_match':'34/34',
       'real_native_default_typed_PE_fields':3,
       'native_separate_afterRET_DATA_B':901,
       'whole_original_giant_exact':False,
       'new_accepted_authored_whole_CODE_B':0,
       'all_979_unit_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print('F829 two real B4/B5 original 215B/60-x86/8-PE-field restart cases added to 17676B/4702-x86 whole fighter; all native register/float opcode bytes correct except three genuine enclosing-parent JMP two-byte pairs per case. A7/A8 24 PE refs and original shared 46B default 34/34 native nonrelocation bytes remain correct. Original game giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F829 original B4/B5 source whole-parent FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
