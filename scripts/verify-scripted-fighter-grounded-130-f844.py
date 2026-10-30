#!/usr/bin/env python3
"""F844: real original 0x130 202B/58-x86/5 PE fields in full 005214B0.

Regenerate F843 source with actor-specific 12F and 12C-12E and
all earlier C8-D2 cases; add true 130 x87 ground drag and staged
animation, then compile ONLY the one affected whole VC7.1 parent.
Check complete 202B/58 native geometry, actual physical PE fields,
both genuine encompassing-giant JMPs, four prior falling states,
eleven previous C8-D2 cases, and five real 901B afterRET tables.
No inner-case accepted CODE or full 979-unit cold replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f844-scripted-stage130'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
FALL={
 0x12c:(207,59,6,[203,204],0x12d),
 0x12d:(219,61,6,[215,216],0x12e),
 0x12e:(207,59,6,[203,204],0x12f),
 0x12f:(207,59,6,[203,204],0x130),
}
PRIOR=[
 (0xc8,657,190,17,[184,185,202,203,267,268,364,365,382,383,446,447,653,654],0xc9),
 (0xc9,279,86,11,[275,276],0xca),
 (0xca,418,121,11,[203,204,414,415],0xcb),
 (0xcb,496,141,12,[214,215,492,493],0xcc),
 (0xcc,428,126,10,[186,187,424,425],0xcd),
 (0xcd,387,113,8,[186,187,383,384],0xce),
 (0xce,387,113,8,[186,187,383,384],0xcf),
 (0xcf,114,30,4,[110,111],0xd0),
 (0xd0,195,60,6,[154,155,191,192],0xd1),
 (0xd1,199,59,8,[26,27,195,196],0xd2),
 (0xd2,251,74,10,[26,27,247,248],0x12c),
]
FIELDS130={
 10:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
 16:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
 37:(0x0040FA30,'call','GetNativeActionAt40FA30'),
 45:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
 56:(0x00453D60,'call','PrepareActionAt453D60'),
}
def need(p,msg):
    if not p:raise ValueError(msg)

def load(t,filename):
    sp=importlib.util.spec_from_file_location(t,ROOT/'scripts'/filename)
    need(sp is not None and sp.loader is not None,
         'missing original native PE helper '+filename)
    m=importlib.util.module_from_spec(sp)
    sys.modules[t]=m
    sp.loader.exec_module(m)
    return m

def current_source(rd,pe,d,by):
    OUT.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(ROOT/'scripts/repo-python'),
         str(ROOT/'scripts/verify-scripted-fighter-falling-12f-f843.py')],
         cwd=ROOT,capture_output=True,text=True,timeout=1300)
    (OUT/'f843-prior-original-physical-proof.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'earlier original selected 12F PE evidence did not verify '+
         (p.stdout+p.stderr)[-900:])
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x130],by[0x131]-by[0x130]),by[0x130]))
    need(len(original)==58 and by[0x131]-by[0x130]==202
         and original[0].mnemonic=='mov'
         and original[2].mnemonic=='fld' and original[3].mnemonic=='fsub'
         and original[8].mnemonic=='fld' and '+ 0x48]' in original[8].op_str
         and original[9].mnemonic=='fadd' and '+ 0x54]' in original[9].op_str
         and original[18].mnemonic=='mov' and '+ 0x48]' in original[18].op_str
         and original[20].mnemonic=='mov' and '+ 0x5c]' in original[20].op_str
         and original[22].mnemonic=='mov' and '+ 0x54]' in original[22].op_str
         and original[43].op_str=='9'
         and original[48].mnemonic=='cmp' and original[48].op_str.endswith(', 3')
         and original[54].op_str=='0x1c',
         'original 130 physical native x87 operand/zero order/stage 3 parameters changed')
    src=(ROOT/'.analysis/f843-scripted-stage12f/Boss005214B0-F843-whole.cpp').read_text()
    marker='        case 0x130: g_FighterProbeMarker = 305; break;'
    inc=(ROOT/'probes/FighterScriptedGrounded130F844.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x130:')==1
         and inc.count('return;')==2
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc
         and 'S16(0x62)==3' in inc
         and inc.count('PrepareActionAt453D60(0x1C)')==1,
         'actual original game 130 native source grammar modified')
    return src.replace(marker,'#include "FighterScriptedGrounded130F844.inc"',1)

def compile_source(src):
    cpp=OUT/'Boss005214B0-F844-whole.cpp'
    obj=OUT/'Boss005214B0-F844-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=ROOT,env=env,capture_output=True,text=True,timeout=300)
    (OUT/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'entire selected original 130 VC7.1 C++ compilation failed '+
         (p.stdout+p.stderr)[-780:])
    return obj

def main():
    rd=load('f844reader','compare-coff-function.py')
    ac=load('f844actions','report-fighter-action-handlers.py')
    f834=load('f844f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=load('f844f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=load('f844zero','verify-fighter-actionzero-natural-source.py')
    sw=load('f844switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    pe=rd.verified_target()
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original whole game executable identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={q['action']:int(q['handler'],16) for q in mp}
    obj=compile_source(current_source(rd,pe,d,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(22289,6079,878,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'normal entire fighter original case130 codegen or packed DATA changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all five genuine original afterRET packed dispatch tables not checked')
    follow=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x132')
       and any('g_FighterProbeMarker' in r['symbol']
             and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(follow)==1 and follow[0]>=58+238,
         'actual original following 131 source marker not unique')
    k=follow[0]
    current=ins[k-58:k]
    result=f834.physical_case(rd,pe,d,code,refs,current,by,0x130,202,5,
                              [84,85,198,199],0x131,f820)
    need(result['native_complete_x86']==58
         and result['original_native_enclosing_parent_JMP_exit_ordinals']==[23,57]
         and all(current[j].op_str==hex(ret-4) for j in (23,57))
         and current[8].op_str=='dword ptr [ecx + 0x48]'
         and current[9].op_str=='dword ptr [edx + 0x54]'
         and current[48].op_str.endswith(', 3'),
         'true original source130 x87/CFG/parent epilogue exits shifted')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x130],202),by[0x130]))
    for ordinal,(target,mn,symbol) in FIELDS130.items():
        a,b=original[ordinal],current[ordinal]
        owned=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(a.mnemonic==b.mnemonic==mn and len(owned)==1
             and owned[0]['local_symbol_offset'] is None
             and owned[0]['addend']==0
             and owned[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and symbol in owned[0]['symbol']
             and owned[0]['offset']-current[0].address==a.address-by[0x130]+a.size-4,
             'physical original 130 native PE target field moved at x86 '+str(ordinal))
    # Four earlier 12C..12F now all remain correct source in the NEW
    # original whole-object, not only a cached earlier F843 build.
    prior=ins[k-58-238:k-58]
    offset=0;falling=[]
    for action,(size,nx,nf,wrong,nextact) in FALL.items():
        segment=prior[offset:offset+nx];offset+=nx
        falling.append(f834.physical_case(rd,pe,d,code,refs,segment,by,
                                           action,size,nf,wrong,nextact,f820))
    need(offset==238,'actual original prior four falling states truncated')
    old=ins[k-58-238-sum(q[2] for q in PRIOR):k-58-238]
    off=0;previous=[]
    for action,size,nx,nf,wrong,nextact in PRIOR:
        seg=old[off:off+nx];off+=nx
        previous.append(f834.physical_case(rd,pe,d,code,refs,seg,by,
                                              action,size,nf,wrong,nextact,f820))
    need(off==len(old),'genuine original previous eleven C8-D2 states truncated')
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,native_tail,0x52cb25,
        [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    bad=[j for j in range(46) if j not in mask
         and native_tail[j]!=code[ret-46+j]]
    need(bad==[10,12,16,19],
         'original fallback true current nonrelocated GPR operand differences changed')
    summary={'original_whole_native_fighter':'0x005214B0',
        'original_complete_whole_callable_CODE_B':46755,
        'current_generated_entire_source_callable_CODE_B':ret,
        'real_original_case130_complete':result,
        'native_130_original_PE_fields_at_x86_ordinals':list(FIELDS130),
        'prior_falling_cases_12C_12D_12E_12F_reverified':falling,
        'earlier_C8_to_D2_original_PE_cases_reverified':previous,
        'real_selected_130_ground_native_order_preserved':True,
        'original_default_46B_real_GPR_byte_negatives':bad,
        'original_five_901B_packed_afterRET_tables_checked':True,
        'separate_native_afterRET_DATA_B':901,
        'whole_native_function_exact':False,'new_whole_authored_CODE_accepted_B':0,
        'all_unit_cold_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F844 original 0x130 202B/58 x86/5 actual native PE fields in 22289B/6079-x86 entire fighter source; only two true whole original parent-epilogue JMP operand pairs differ. Prior four 12C-12F, original eleven C8-D2 cases, five real 901B switch tables and fallback GPR nonfield negatives verified. Original 46755B giant NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F844 original native 130 whole fighter source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
