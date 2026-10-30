#!/usr/bin/env python3
"""F830: real original D0 reflected landing inside the entire 005214B0 fighter.

Regenerate the F829 selected native-backed parent before adding real
195-B/60-x86/6-field D0 source. Verify physical original PE and
COFF field identity, retain B4/B5 complete native source, 901-B
separate afterRET jump DATA, original saved-this frame and the
current *nonexact* common default/getter register phase.
No cropped case credit, all-unit cold replay, or target binary patches.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f830-scripted-reflect'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0

def need(x,message):
    if not x:raise ValueError(message)

def ld(name,relative):
    spec=importlib.util.spec_from_file_location(name,R/'scripts'/relative)
    need(spec is not None and spec.loader is not None,'pinned helper missing '+relative)
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m

def native_source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
                      str(R/'scripts/verify-scripted-fighter-motion-restart-f829.py')],
           cwd=R,capture_output=True,text=True,timeout=1150)
    (O/'f829-prior-physical-targeted.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'prior whole original fighter target verification failed '+(p.stdout+p.stderr)[-850:])
    src=(R/'.analysis/f829-scripted-motion-restart/Boss005214B0-F829-full.cpp').read_text()
    marker='        case 0xD0: g_FighterProbeMarker = 209; break;'
    inc=(R/'probes/FighterScriptedReflectD0F830.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0xD0:')==1
         and inc.count('return;')==2
         and 'POS5C=0.6f' in inc
         and 'SetAuxActionAt40FB40(5)' in inc,
         'actual native mirrored-direction/ground source changed')
    return src.replace(marker,'#include "FighterScriptedReflectD0F830.inc"',1)

def compile_one(source):
    cpp=O/'Boss005214B0-F830-whole.cpp'
    obj=O/'Boss005214B0-F830-whole.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         env=env,cwd=R,capture_output=True,text=True,timeout=300)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'native original D0 whole-parent source build failed '+(p.stdout+p.stderr)[-850:])
    return obj

def main():
    rd=ld('f830_reader','compare-coff-function.py')
    ac=ld('f830_ac','report-fighter-action-handlers.py')
    f646=ld('f830_f646','verify-fighter-fall-reflect-f646.py')
    f645=ld('f830_f645','verify-fighter-motion-restart-f645.py')
    f820=ld('f830_f820','verify-scripted-fighter-landing-trio-f820.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'actual full native original giant or switch table changed')
    _,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original,info=f646.native_case(rd,pe,d,boss,by,0xD0)
    need((info['original_complete_native_inner_CODE_bytes'],info['real_original_x86_roles'],
          info['actual_physical_PE_COFF_fields'])==(195,60,6),
         'original PE physical D0 case extent or typed calls differ')
    obj=compile_one(native_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(17856,4760,765,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'new source entire CODE/x86/COFF or original saved-this slot changed')
    mark=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0xd2')
          and any('g_FighterProbeMarker' in r['symbol']
                 and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(mark)==1 and mark[0]>=60+2*60,
         'original next D1 source marker not unique')
    index=mark[0]
    source=ins[index-60:index]
    lo,hi=source[0].address,source[-1].address+source[-1].size
    native_bytes=rd.pe_bytes_at(pe,by[0xd0],by[0xd1]-by[0xd0])
    need(hi-lo==len(native_bytes)==195 and len(source)==len(original)==60
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(original,source)),
         'complete original D0 native x87/CFG instruction positions not reproduced')
    fields=[r for r in refs if lo<=r['offset']<hi]
    mask=f820.physical_fields(rd,native_bytes,by[0xd0],fields,lo,6)
    for ordinal,(target,mn,symbol) in f646.FIELDS[0xD0].items():
        original_inst,produced=original[ordinal],source[ordinal]
        real=[r for r in fields if produced.address<=r['offset']<produced.address+produced.size]
        need(original_inst.mnemonic==produced.mnemonic==mn and len(real)==1
             and symbol in real[0]['symbol']
             and real[0]['offset']-lo==original_inst.address-by[0xd0]+original_inst.size-4,
             'native D0 true PE global/call field position drifted')
    wrong=[j for j in range(195) if j not in mask and native_bytes[j]!=code[lo+j]]
    need(wrong==[154,155,191,192]
         and original[48].mnemonic==source[48].mnemonic=='jmp'
         and original[-1].mnemonic==source[-1].mnemonic=='jmp'
         and original[48].op_str==original[-1].op_str=='0x52cb4f'
         and source[48].op_str==source[-1].op_str==hex(ret-4),
         'D0 native case must differ only in actual two enclosing-function final JMPs')
    # Preserve earlier 2 full B4/B5 state boundaries, all 8 real
    # zero-addend PE calls per case, and three actual parent JMPs.
    c8markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
               and x.op_str.endswith(', 0xc9')
               and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(c8markers)==1 and c8markers[0]>=120 and c8markers[0]<index-60,
         'source original C8 placeholder/earlier B4 B5 boundary not unique')
    prior=ins[c8markers[0]-120:c8markers[0]]
    prev=[]
    for j,action in enumerate((0xb4,0xb5)):
        n,meta=f645.native_case(rd,pe,d,boss,by,action)
        current=prior[j*60:(j+1)*60]
        a,b=current[0].address,current[-1].address+current[-1].size
        raw=rd.pe_bytes_at(pe,by[action],215)
        need(b-a==215 and len(n)==len(current)==60
             and all(x.mnemonic==y.mnemonic and x.size==y.size for x,y in zip(n,current)),
             'earlier B4/B5 original native case geometry changed')
        owned=[r for r in refs if a<=r['offset']<b]
        masked=f820.physical_fields(rd,raw,by[action],owned,a,8)
        actual=[k for k in range(215) if k not in masked and raw[k]!=code[a+k]]
        need(actual==[169,170,206,207,211,212],
             'earlier B4/B5 real parent-external operand bytes changed')
        prev.append({'case':hex(action),'full_native_B':215,
                     'physical_original_PE_fields':8,
                     'real_parent_jmp_byte_differences':actual})
    # The default still has the original correct EBP-0x10, but new
    # actual D0 gameplay rotates four authentic GPR operand bytes.
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tr=[r for r in refs if ret-46<=r['offset']<ret]
    tailmask=f820.physical_fields(rd,tail,0x52cb25,tr,ret-46,3)
    tailbad=[k for k in range(46) if k not in tailmask and tail[k]!=code[ret-46+k]]
    need(tailbad==[10,12,16,19],
         'native original default new whole-parent GPR phase unexpected')
    true_tail=list(d.disasm(tail,0x52cb25))
    generated=list(d.disasm(code[ret-46:ret],ret-46))
    need(len(true_tail)==len(generated)==16 and
         all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(true_tail,generated)),
         'native 46B default/getter full geometry changed')
    out={'native_entire_original_game':'0x005214B0',
        'real_original_whole_CODE_B':46755,
        'new_whole_source_callable_CODE_B':ret,
        'original_real_D0_native_B':195,'native_full_x86':60,
        'original_typed_physical_PE_fields':6,
        'genuine_D0_parent_external_JMP_operand_differences':wrong,
        'previous_original_B4_B5_native_cases_reverified':prev,
        'actual_saved_receiver_EBP':'-0x10',
        'new_original_default_tail_GPR_nonfield_diffs':tailbad,
        'real_original_separate_afterRET_DATA_B':901,
        'whole_native_original_fighter_exact':False,
        'accepted_new_callable_whole_CODE_B':0,
        'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F830: real 0xD0 whole native 195B/60 x86/6 PE refs in ONE fresh 17,856B/4,760-x86 parent, 901B original DATA; only two physical final giant JMP operand pairs differ. Prior B4/B5 actual PE fields revalidated. Common 46B getter still native shape but 4 honest GPR bytes now wrong; giant 46,755B still NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F830 original whole fighter D0 verification FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
