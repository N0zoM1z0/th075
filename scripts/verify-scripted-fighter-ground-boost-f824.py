#!/usr/bin/env python3
"""F824: original 0x9E ground-boost case in whole 46KB scripted fighter.

Rebuild F823 full native-backed 9B/9C source first. One new entire
VC7.1 fighter parent adds the real 243B/66-x86/8 original PE field
0x9E case and preserves all six earlier true timer states, original
0x91/8C/8F/90, native mode63 displaced COFF field, 901B afterRET DATA.
Only four real enclosing-giant epilogue jump bytes differ in 0x9E.
No split-case or whole giant authored exact credit, no mass cold replay.
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
O=R/'.analysis/f824-scripted-9e'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
TIMERS=(0x96,0x97,0x98,0x9a,0x9b,0x9c)
NEXT=(0x97,0x98,0x9a,0x9b,0x9c,0x9e)

def need(test,msg):
    if not test:raise ValueError(msg)

def load(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'missing native original physical helper '+name)
    m=importlib.util.module_from_spec(sp)
    sys.modules[tag]=m
    sp.loader.exec_module(m)
    return m

def make_source(meta):
    O.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-landing-pair-f823.py')],
       cwd=R,capture_output=True,text=True,timeout=1250)
    (O/'f823-prior-physical-native.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'prior 6 timer cases not physically revalidated '+
         (run.stdout+run.stderr)[-800:])
    text=(R/'.analysis/f823-scripted-9b9c/Boss005214B0-F823-full.cpp').read_text()
    inc=(R/'probes/FighterScriptedGroundBoostF824.inc').read_text()
    need(inc.count('case 0x9E:')==1 and inc.count('return;')==2
         and 'POS48>=g_ThresholdAt0065782C' in inc,
         'original C++ 9E non-strict above-ground/native direct return changed')
    need(not meta['original_extra_short_0xF0A_reset']
         and not meta['strict_native_initial_ground_above_not_equal'],
         'original selected 9E actor has unexpected F0A or STRICT comparison')
    mark='        case 0x9E: g_FighterProbeMarker = 159; break;'
    need(text.count(mark)==1,'next selected original case 9E placeholder not found')
    parameters={'F637_EXTRA_FLAG':'0','F637_EXTRA_BEFORE':'0','F637_STRICT_ABOVE':'0'}
    code='\n'.join('#define '+k+' '+v for k,v in parameters.items())
    code+='\n#include "FighterScriptedGroundBoostF824.inc"\n'
    code+='\n'.join('#undef '+k for k in parameters)
    return text.replace(mark,code,1)

def compile_source(source):
    cpp=O/'Boss005214B0-F824-full.cpp'
    obj=O/'Boss005214B0-F824-full.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv= d;winemenubuilder.exe=d'.replace('= d','=d')
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,capture_output=True,text=True,env=env,timeout=280)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'new full original fighter source did not compile '+(run.stdout+run.stderr)[-850:])
    return obj

def main():
    rd=load('f824_rd','compare-coff-function.py')
    actions=load('f824_actions','report-fighter-action-handlers.py')
    f637=load('f824_f637','verify-fighter-ground-boost-f637.py')
    f633=load('f824_f633','verify-fighter-landing-siblings-f633.py')
    f631=load('f824_f631','verify-fighter-landing-timer96-f631.py')
    f629=load('f824_f629','verify-fighter-arc91-f629.py')
    f628=load('f824_f628','verify-fighter-jump-landings-f628.py')
    f626=load('f824_f626','verify-fighter-mode63-basic-f626.py')
    f820=load('f824_f820','verify-scripted-fighter-landing-trio-f820.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original fighter whole extent/source DATA changed')
    _,mapped=actions.report_boss(rd,pe,d,boss)
    by={row['action']:int(row['handler'],16) for row in mapped}
    native9e,meta=f637.original_case(rd,pe,d,boss,by)
    need((len(native9e),meta['native_complete_original_inner_CODE_bytes'],
          meta['original_real_PE_COFF_typed_fields'])==(66,243,8),
         'original selected actor true 9E PE bounds or typed fields changed')
    obj=compile_source(make_source(meta))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret,len(refs))==(15076,3976,901,676)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'whole source CODE/x86/PE/ABI geometry changed')
    markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0xa0')
       and any('g_FighterProbeMarker' in r['symbol']
           and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1 and markers[0]>=66+6*73,
         'true following 9F case marker not unique')
    idx=markers[0]
    state=ins[idx-66:idx]
    lo,hi=state[0].address,state[-1].address+state[-1].size
    native=rd.pe_bytes_at(pe,by[0x9e],by[0x9f]-by[0x9e])
    need(hi-lo==len(native)==243 and len(state)==len(native9e)==66
         and all(a.mnemonic==b.mnemonic and a.size==b.size
                  for a,b in zip(native9e,state)),
         'original 9E full x86 width/geometry changed')
    fields=[r for r in refs if lo<=r['offset']<hi]
    mask=f820.physical_fields(rd,native,by[0x9e],fields,lo,8)
    for ordinal,(target,mn,symbol) in f637.FIELDS.items():
        a,b=native9e[ordinal],state[ordinal]
        found=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(a.mnemonic==b.mnemonic==mn and len(found)==1
             and symbol in found[0]['symbol']
             and found[0]['offset']-lo==a.address-by[0x9e]+a.size-4,
             'original 9E typed global/call PE field is not at real native ordinal')
    wrong=[j for j in range(243) if j not in mask and native[j]!=code[lo+j]]
    need(wrong==[202,203,239,240]
         and native9e[54].mnemonic==state[54].mnemonic=='jmp'
         and native9e[-1].mnemonic==state[-1].mnemonic=='jmp'
         and native9e[54].op_str==native9e[-1].op_str=='0x52cb4f'
         and state[54].op_str==state[-1].op_str==hex(ret-4),
         'original 9E must differ only in two true complete-parent-exit JMP displacement pairs')
    # All six prior source-backed original timers rechecked in THIS
    # full newly built parent, with every actual physical PE field.
    timers=ins[idx-66-6*73:idx-66]
    need(len(timers)==6*73,'six previous real timers truncated')
    six=[]
    for index,action in enumerate(TIMERS):
        source=timers[index*73:(index+1)*73]
        a,b=source[0].address,source[-1].address+source[-1].size
        native,info=(f631.original_case(rd,pe,d,boss,by) if action==0x96
             else f633.original_case(rd,pe,d,boss,by,action))
        end=by[(0x97,0x98,0x9a,0x9b,0x9c,0x9e)[index]]
        raw=rd.pe_bytes_at(pe,by[action],end-by[action])
        need(b-a==len(raw)==276 and len(source)==len(native)==73
             and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(native,source)),
             'earlier original timer full x86 grammar changed '+hex(action))
        rs=[r for r in refs if a<=r['offset']<b]
        mask=f820.physical_fields(rd,raw,by[action],rs,a,9)
        bad=[j for j in range(276) if j not in mask and raw[j]!=code[a+j]]
        need(bad==[272,273],'earlier six timed cases no longer source-native register equal '+hex(action))
        six.append({'action':hex(action),'native_whole_CASE_B':276,
                    'real_PE_fields_checked':9,'actual_external_jump_mismatch_bytes':bad})
    # The previous original 91 and three 8C/8F/90 are also still
    # verified by true native PE fields in the newly built source.
    old91=ins[idx-66-6*73-78:idx-66-6*73]
    n91,info=f629.real_original(rd,pe,d,boss,by)
    a,b=old91[0].address,old91[-1].address+old91[-1].size
    need(b-a==288 and len(old91)==78 and
         all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(n91,old91)),
         'actual earlier 0x91 native opcode/x87 grammar changed')
    raw=rd.pe_bytes_at(pe,by[0x91],288)
    rf=[r for r in refs if a<=r['offset']<b]
    mask=f820.physical_fields(rd,raw,by[0x91],rf,a,12)
    need(sum(raw[j]!=code[a+j] for j in range(288) if j not in mask)==37,
         'native previous 0x91 GPR phase changed in extended parent')
    trio=ins[idx-66-6*73-78-240:idx-66-6*73-78]
    need(len(trio)==240,'original three landing x86 sequence truncated')
    for j,action in enumerate((0x8c,0x8f,0x90)):
        now=trio[j*80:(j+1)*80];lo,hi=now[0].address,now[-1].address+now[-1].size
        native,info=f628.native_case(rd,pe,d,boss,by,action)
        need(hi-lo==289 and len(now)==len(native)==80
             and all(x.mnemonic==y.mnemonic and x.size==y.size
                     for x,y in zip(native,now)),'older 8C-90 original opcode changed')
        raw=rd.pe_bytes_at(pe,by[action],289)
        mask=f820.physical_fields(rd,raw,by[action],
                [r for r in refs if lo<=r['offset']<hi],lo,8)
        need(sum(raw[k]!=code[lo+k] for k in range(289) if k not in mask)==55,
             'older landing case GPR cycle changed unexpectedly')
    # Verify original 0x63 source shifted field is not promoted.
    n63,_=f626.original_case(rd,pe,d,boss,by)
    lo=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+25*4)
    hi=trio[0].address
    src63=list(d.disasm(code[lo:hi],lo))
    need(hi-lo==417 and len(src63)==len(n63)==109
         and [i for i,(x,y) in enumerate(zip(n63,src63)) if x.size!=y.size]==[38,61],
         'native full mode63 source wrong x86 width sequence changed')
    shifts={}
    for ordinal,(target,mn,symbol) in f626.FIELDS.items():
        a,b=n63[ordinal],src63[ordinal]
        field=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(field)==1 and symbol in field[0]['symbol'] and field[0]['addend']==0,
             'mode63 real original PE call source missing')
        shifts[str(ordinal)]=field[0]['offset']-lo-(a.address-by[0x63]+a.size-4)
    need(shifts=={'0':0,'22':0,'48':-1,'71':0,'94':0,'99':0,'107':0},
         'actual original/source 0x63 PE field shift not rechecked')
    ntail=rd.pe_bytes_at(pe,0x52cb25,46)
    rs=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,ntail,0x52cb25,rs,ret-46,3)
    tailbad=[j for j in range(46) if j not in mask and ntail[j]!=code[ret-46+j]]
    need(tailbad==[10,12,16,19],'default shared tail current native GPR phase changed')
    result={'original_giant':'0x005214B0','original_whole_native_B':46755,
       'new_source_whole_callable_CODE_B':ret,
       'new_real_0x9E_inner_CODE_B':243,'original_case9E_x86':66,
       'physically_attested_native_9E_PE_fields':8,
       'native_case9E_only_enclosing_epilogue_relative_wrong_bytes':wrong,
       'all_six_earlier_original_timers_rechecked':six,
       'native_91_and_8C_8F_90_rechecked':True,
       'mode63_native_source_physically_shifted_field_retained':shifts,
       'native_original_separate_afterRET_DATA_B':901,
       'default_46B_native_GPR_byte_negatives':tailbad,
       'whole_giant_exact':False,'new_accepted_callable_CODE_B':0,
       'all_unit_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print('F824: actual native 0x9E ground boost 243B/66-x86/8 physical PE fields integrated in 15076B/3976-x86 complete C++ parent; only 4 real enclosing epilogue-JMP displacement bytes differ in 9E. All six timer cases, 91, 8C/8F/90, shifted 63 field and 901B DATA rechecked. 46755B giant still NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F824 original whole 9E native source verification FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
