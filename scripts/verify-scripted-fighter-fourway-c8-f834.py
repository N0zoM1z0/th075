#!/usr/bin/env python3
"""F834: native 657B/190-x86 C8 source in one complete current 46KB fighter.

Regenerate selected F833 C9 and preceding CF/D0/D1/D2 source from
pinned original PE. Add genuine C8 storm, directional contact and
seven direct parent exits in a newly compiled whole VC7.1 source.
Natural prefix ++ on REAL +0xF00 short emits the exact original
MOV CX/ADD CX,1 grammar, not assignment/add that widens ECX.
All 17 PE call/global fields, all 190 x86/657 bytes aside from
14 true encompassing parent JMP displacement bytes, and all five
native packed afterRET tables are physically checked. Critically
C9 and CF/D0/D1/D2 now also differ ONLY in parent-external JMP
bytes, and shared default/getter has 34/34 native nonfield bytes
plus 3 actual original PE REL32 calls. Whole 46755B still NONEXACT.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f834-scripted-fourway-c8'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
C8_JMP_ORDINALS=(50,54,72,98,102,120,189)
C8_WRONG=[184,185,202,203,267,268,364,365,382,383,446,447,653,654]
PRIOR=[
 (0xc9,86,279,11,[275,276],0xca),
 (0xcf,30,114,4,[110,111],0xd0),
 (0xd0,60,195,6,[154,155,191,192],0xd1),
 (0xd1,59,199,8,[26,27,195,196],0xd2),
 (0xd2,74,251,10,[26,27,247,248],0x12c),
]

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(t,f):
    sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'native original PE helper missing '+f)
    m=importlib.util.module_from_spec(sp)
    sys.modules[t]=m;sp.loader.exec_module(m)
    return m

def make_source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
         str(R/'scripts/verify-scripted-fighter-fourway-c9-f833.py')],
         cwd=R,text=True,capture_output=True,timeout=1250)
    (O/'f833-physical-original-proof.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'prior original C9 CF/D0/D1/D2 real PE proof failed '+(p.stdout+p.stderr)[-850:])
    src=(R/'.analysis/f833-scripted-fourway-c9/Boss005214B0-F833-whole.cpp').read_text()
    marker='        case 0xC8: g_FighterProbeMarker = 201; break;'
    need(src.count(marker)==1,'original next C8 marker is not unique')
    inc=(R/'probes/FighterScriptedFourWayC8F834.inc').read_text()
    need(inc.count('case 0xC8:')==1 and inc.count('return;')==7
         and inc.count('++S16(0xF00);')==1
         and 'ConfigureStormAt454BC0(3,4,0xFF)' in inc
         and inc.count('SpawnAt453C80')==1
         and inc.count('SpawnMixedAt453C80')==1,
         'actual game C8 physical 7 exits, typed short ++ or sprite behavior moved')
    method='void PrepareActionAt453D60(int);'
    need(src.count(method)==1,'original borrowed method declaration changed')
    src=src.replace(method,method+' void PrepareActionAt453D40(int);',1)
    src=('extern float g_F834_UpperAt00657CBC;\n'
         'extern float g_F834_LowerAt006590B0;\n'+src)
    return src.replace(marker,'#include "FighterScriptedFourWayC8F834.inc"',1)

def compile_whole(src):
    cpp=O/'Boss005214B0-F834-whole.cpp'
    obj=O/'Boss005214B0-F834-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=env,capture_output=True,text=True,timeout=290)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'real C8 whole-giant normal C++ source VC7.1 failed '+(p.stdout+p.stderr)[-880:])
    return obj

def physical_case(rd,pe,d,code,refs,source,by,action,expected_size,
                  nfields,wrong_expected,next_action,f820):
    lo,hi=source[0].address,source[-1].address+source[-1].size
    raw=rd.pe_bytes_at(pe,by[action],by[next_action]-by[action])
    original=list(d.disasm(raw,by[action]))
    need(len(raw)==hi-lo==expected_size and
         len(original)==len(source) and
         all(a.mnemonic==b.mnemonic and a.size==b.size
              and a.address-by[action]==b.address-lo
              for a,b in zip(original,source)),
         'actual original C8/C9/CF/D0/D1/D2 native opcode-width/position differs '+hex(action))
    fields=[r for r in refs if lo<=r['offset']<hi]
    mask=f820.physical_fields(rd,raw,by[action],fields,lo,nfields)
    for r in fields:
        off=r['offset']-lo
        src_inst=next(x for x in source if x.address<=r['offset']<x.address+x.size)
        j=source.index(src_inst)
        orig=original[j]
        need(off==orig.address-by[action]+orig.size-4,
             'original game actual PE call/global operand shifted versus compiler source '+str((action,j)))
    wrong=[k for k in range(expected_size) if k not in mask and raw[k]!=code[lo+k]]
    need(wrong==wrong_expected,
         'original game case machine bytes differ beyond genuine enclosing parent-JMP '+str((action,wrong)))
    native_exits=[k for k,x in enumerate(original)
                  if x.mnemonic=='jmp' and x.op_str=='0x52cb4f']
    for ordinal in native_exits:
        a,b=original[ordinal],source[ordinal]
        need(a.size==b.size==5 and b.mnemonic=='jmp',
             'real parent exit JMP geometry incorrect')
    return {'case':hex(action),'native_whole_inner_B':expected_size,
            'native_complete_x86':len(original),
            'original_typed_PE_fields':nfields,
            'original_native_enclosing_parent_JMP_exit_ordinals':native_exits,
            'real_nonrelocation_wrong_offsets':wrong}

def main():
    rd=load('f834_reader','compare-coff-function.py')
    ac=load('f834_actions','report-fighter-action-handlers.py')
    f820=load('f834_f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=load('f834_zero','verify-fighter-actionzero-natural-source.py')
    switch=load('f834_switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'actual original entire fighter function and switch DATA changed')
    report,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    obj=compile_whole(make_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(19281,5189,810,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'new whole fighter original PE/COFF full output or ABI geometry changed')
    # Independently recheck every original dense/sparse table from the
    # current new *whole* COFF object, not only 901B length.
    dense,sparse,maps=zero.verify_physical_tables(
          boss,report,pe,rd,switch,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all five true original postRET native jump tables not reverified')
    # Original C8 and C9 begin with the identical genuine
    # ConfigureStorm(3,4,0xFF) triple push + native call.
    starts=[i for i,x in enumerate(ins) if x.mnemonic=='push'
        and x.op_str=='0xff' and i+4<len(ins)
        and ins[i+1].mnemonic=='push' and ins[i+1].op_str=='4'
        and ins[i+2].mnemonic=='push' and ins[i+2].op_str=='3'
        and ins[i+4].mnemonic=='call']
    need(len(starts)>=2,'both original C8/C9 source ConfigureStorm entries missing')
    first,second=starts[-2:]
    c8=ins[first:second]
    need(len(c8)==190,'physical original 190-instruction 657B C8 source incomplete')
    case8=physical_case(rd,pe,d,code,refs,c8,by,0xc8,657,17,C8_WRONG,0xc9,f820)
    need(case8['original_native_enclosing_parent_JMP_exit_ordinals']==list(C8_JMP_ORDINALS)
         and c8[94].mnemonic=='mov' and c8[94].op_str=='cx, word ptr [eax + 0xf00]'
         and c8[95].mnemonic=='add' and c8[95].op_str=='cx, 1',
         'actual original native C8 16-bit ++ register/7 exits not reproduced')
    for j in C8_JMP_ORDINALS:
        need(c8[j].op_str==hex(ret-4),
             'C8 actual original seven native direct jumps must target one source epilogue')
    c9=ins[second:second+86]
    case9=physical_case(rd,pe,d,code,refs,c9,by,0xc9,279,11,[275,276],0xca,f820)
    need(case9['original_native_enclosing_parent_JMP_exit_ordinals']==[85]
         and c9[-1].op_str==hex(ret-4),
         'original C9 once-only direct whole-giant exit source differs')
    # After 0xC8/C9, every previously physical CF/D0/D1/D2 now
    # follows the same native EDX/EAX/ECX GPR phase. Only true
    # parent-external original JMP relative bytes are different.
    marks=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x12d')
        and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=223,'following native 0x12C source marker not unique')
    k=marks[0];last=ins[k-223:k];prev=[]
    start=0
    for act,nx,nb,nf,wrong,nxt in PRIOR[1:]:
        section=last[start:start+nx];start+=nx
        result=physical_case(rd,pe,d,code,refs,section,by,act,nb,nf,wrong,nxt,f820)
        for j in result['original_native_enclosing_parent_JMP_exit_ordinals']:
            need(section[j].op_str==hex(ret-4),
                 'CF/D0/D1/D2 true native direct epilogue JMP differs')
        prev.append(result)
    need(start==223,'four previous contiguous native cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    f=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,tail,0x52cb25,f,ret-46,3)
    actual=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    orig=list(d.disasm(tail,0x52cb25));generated=list(d.disasm(code[ret-46:ret],ret-46))
    need(not actual and len(mask)==12 and len(orig)==len(generated)==16
         and all(a.mnemonic==b.mnemonic and a.size==b.size
                 for a,b in zip(orig,generated)),
         'C8 REAL 190-x86 source must restore common native default/getter 34/34 nonfield bytes')
    summary={'native_original_whole_game':'0x005214B0',
         'original_complete_callable_CODE_B':46755,
         'new_generated_whole_parent_callable_CODE_B':ret,
         'new_original_C8_case':case8,
         'original_C9_case_freshly_rechecked':case9,
         'previous_CF_D0_D1_D2_original_cases_rechecked':prev,
         'native_true_full_afterRET_table_dense_fields':dense,
         'native_true_full_afterRET_table_sparse_bytes':sparse,
         'native_true_full_afterRET_table_maps':maps,
         'real_afterRET_DATA_B':901,
         'native_original_common_default_getter_46B_nonrelocation':'34/34',
         'original_common_default_three_real_PE_REL32_calls':3,
         'original_whole_function_exact':False,
         'new_accepted_authored_whole_CODE_B':0,
         'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F834 BREAKTHROUGH: original C8 657B/190 x86/17 actual PE fields now all NON-parent-JMP machine bytes native-identical, 7 authentic whole-giant JMP pairs differ. The genuine ++short restores MOV CX/ADD CX1, C9 279B and CF/D0/D1/D2 now ALSO only native whole-parent JMP bytes different; 46B default/getter 34/34 native nonfield +3 true REL32, ALL five original 901B switch DATA tables verified. Entire new source 19,281B/5,189 x86, full 46,755B original still NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F834 original C8 current 46KB whole-parent PE proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
