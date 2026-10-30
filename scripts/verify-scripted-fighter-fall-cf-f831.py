#!/usr/bin/env python3
"""F831: actual original 0xCF falling state in the growing 46KB fighter.

Fresh selected F830 original parent verification, followed by one
whole native-shaped VC7.1 parent including 0xCF's genuine natural
C++ source from F647. Check 114B/30-x86/4 original PE fields,
recheck the preceding native B4/B5, original D0 and the 901B
separate packed afterRET DATA. Adding genuine CF rotates later
D0's current register phase (39 real source nonfield bytes now
wrong), but naturally restores 46B default/getter 34/34 nonfield
machine bytes and all three physical PE calls. No accepted
split-case CODE or all-units cold replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f831-scripted-cf'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
CF_WRONG=[1,4,11,14,23,26,29,32,48,51,58,61,77,79,83,86,100,103,110,111]
D0_WRONG=[1,5,8,12,16,19,23,27,30,32,35,38,41,46,49,52,61,73,
          76,83,86,89,92,95,98,101,104,107,110,136,139,154,155,
          168,170,174,177,191,192]

def need(x,msg):
    if not x:raise ValueError(msg)

def load(t,f):
    spec=importlib.util.spec_from_file_location(t,R/'scripts'/f)
    need(spec is not None and spec.loader is not None,'original target helper missing '+f)
    m=importlib.util.module_from_spec(spec)
    sys.modules[t]=m
    spec.loader.exec_module(m)
    return m

def whole_source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-reflect-d0-f830.py')],
       cwd=R,text=True,capture_output=True,timeout=1150)
    (O/'f830-prior-original-proof.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'F830 selected entire original source PE validation failed '+
         (p.stdout+p.stderr)[-850:])
    source=(R/'.analysis/f830-scripted-reflect/Boss005214B0-F830-whole.cpp').read_text()
    fragment=(R/'probes/FighterScriptedFallStateCFF831.inc').read_text()
    marker='        case 0xCF: g_FighterProbeMarker = 208; break;'
    need(source.count(marker)==1 and fragment.count('case 0xCF:')==1
         and fragment.count('return;')==1
         and 'g_SubtractAt00657478' in fragment,
         'actual original 0xCF source or real next case absent')
    declaration='extern float g_SubtractAt00657478;\n'
    need(source.count(declaration)==1,'real original global float declaration not unique')
    return source.replace(marker,'#include "FighterScriptedFallStateCFF831.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F831-whole.cpp'
    obj=O/'Boss005214B0-F831-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       env=env,cwd=R,text=True,capture_output=True,timeout=280)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'new original 0xCF normal VC7.1 whole-source compile failed '+
         (p.stdout+p.stderr)[-820:])
    return obj

def main():
    rd=load('f831_reader','compare-coff-function.py')
    ac=load('f831_actions','report-fighter-action-handlers.py')
    f646=load('f831_f646','verify-fighter-fall-reflect-f646.py')
    f645=load('f831_f645','verify-fighter-motion-restart-f645.py')
    f820=load('f831_f820','verify-scripted-fighter-landing-trio-f820.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    pe=rd.verified_target()
    boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original 46KB function and afterRET table identity changed')
    _,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    real_cf=rd.pe_bytes_at(pe,by[0xcf],by[0xd0]-by[0xcf])
    real_d0=rd.pe_bytes_at(pe,by[0xd0],by[0xd1]-by[0xd0])
    ncf=list(d.disasm(real_cf,by[0xcf]))
    nd0,_=f646.native_case(rd,pe,d,boss,by,0xd0)
    need(len(real_cf)==114 and len(ncf)==30
         and len(real_d0)==195 and len(nd0)==60,
         'original real CF/D0 physical native whole cases changed')
    obj=compile_one(whole_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(17955,4788,768,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'whole original game updated source native ABI or compact switch changed')
    markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
             and x.op_str.endswith(', 0xd2')
             and any('g_FighterProbeMarker' in r['symbol']
                     and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1 and markers[0]>=90,
         'original D1 next source case/CF D0 native boundaries not unique')
    idx=markers[0]
    old=[]
    for action,segment,original,fields_count,expect in (
        (0xcf,ins[idx-90:idx-60],real_cf,4,CF_WRONG),
        (0xd0,ins[idx-60:idx],real_d0,6,D0_WRONG)):
        a,b=segment[0].address,segment[-1].address+segment[-1].size
        n=list(d.disasm(original,by[action]))
        need(b-a==len(original) and len(n)==len(segment)
             and all(x.mnemonic==y.mnemonic and x.size==y.size
                  for x,y in zip(n,segment)),
             'complete PE CF/D0 original native x86 CFG/width changed')
        f=[r for r in refs if a<=r['offset']<b]
        mask=f820.physical_fields(rd,original,by[action],f,a,fields_count)
        if action==0xcf:
            for ordinal,(target,mn,sym) in f646.FIELDS[0xcf].items():
                x,y=n[ordinal],segment[ordinal]
                at=[r for r in f if y.address<=r['offset']<y.address+y.size]
                need(x.mnemonic==y.mnemonic==mn and len(at)==1
                     and sym in at[0]['symbol']
                     and at[0]['offset']-a==x.address-by[action]+x.size-4,
                     'native physical CF original PE global/call ordinal missing')
        wrong=[k for k in range(len(original)) if k not in mask
               and original[k]!=code[a+k]]
        need(wrong==expect,'actual native CF/D0 GPR/parent JMP differences changed '+str((action,wrong)))
        need(n[-1].mnemonic==segment[-1].mnemonic=='jmp'
             and n[-1].op_str=='0x52cb4f'
             and segment[-1].op_str==hex(ret-4),
             'original final CF/D0 exit must be a genuine enclosing fighter epilogue')
        old.append({'original_action':hex(action),
          'original_complete_CODE_B':len(original),
          'native_x86':len(n),'physical_original_PE_fields':fields_count,
          'actual_unmasked_original_PE_byte_differences':wrong})
    # Check earlier 2x215 B4/B5 source under newly compiled
    # whole C++ parent, not cached previous source.
    c8_marker=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
               and x.op_str.endswith(', 0xc9')
               and any('g_FighterProbeMarker' in r['symbol']
                  and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(c8_marker)==1 and c8_marker[0]>=120,
         'original native earlier C8 source marker absent')
    old_states=ins[c8_marker[0]-120:c8_marker[0]]
    for j,action in enumerate((0xb4,0xb5)):
        n,meta=f645.native_case(rd,pe,d,boss,by,action)
        seg=old_states[j*60:(j+1)*60]
        a,b=seg[0].address,seg[-1].address+seg[-1].size
        raw=rd.pe_bytes_at(pe,by[action],215)
        need(b-a==215 and all(x.mnemonic==y.mnemonic and x.size==y.size
              for x,y in zip(n,seg)),
             'earlier original motion restart source GPR widths changed')
        mask=f820.physical_fields(rd,raw,by[action],
             [r for r in refs if a<=r['offset']<b],a,8)
        bad=[k for k in range(215) if k not in mask and raw[k]!=code[a+k]]
        need(bad==[169,170,206,207,211,212],
             'earlier B4/B5 real parent epilogue JMP bytes changed')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,tail,0x52cb25,fields,ret-46,3)
    need(len(mask)==12 and
         all(tail[k]==code[ret-46+k] for k in range(46) if k not in mask),
         'the real original CF source must naturally restore native default GPR/EBP bytes')
    n=list(d.disasm(tail,0x52cb25));src=list(d.disasm(code[ret-46:ret],ret-46))
    need(len(n)==len(src)==16 and
         all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(n,src)),
         'native common default/getter 46B/16 x86 instruction geometry changed')
    out={'original_whole_giant':'0x005214B0',
        'native_original_complete_callable_CODE_B':46755,
        'current_whole_source_callable_CODE_B':ret,
        'original_CF_D0_native_PE_cases_checked':old,
        'original_CF_interior_B':114,'native_CF_x86':30,
        'original_CF_physically_typed_PE_fields':4,
        'CF_actual_nonrelocation_wrong_B':len(CF_WRONG),
        'prior_B4_B5_real_native_PE_fields_rechecked':True,
        'complete_native_default_tail_46B_nonrelocation_equal_B':'34/34',
        'original_default_three_true_PE_REL32_calls':3,
        'original_separate_afterRET_packed_DATA_B':901,
        'original_whole_function_exact':False,
        'new_accepted_callable_whole_CODE_B':0,
        'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F831 original native CF 114B/30 x86/4 genuine PE fields in 17,955B/4,788-x86 whole fighter. Genuine CF remains 20 nonfield GPR/parent-JMP byte mismatches and later D0 rotates to 39; actual original default/getter 46B now 34/34 unrelocated native bytes equal plus 3 typed PE calls. Old B4/B5, 901B switch DATA verified. Giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F831 original CF in whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
