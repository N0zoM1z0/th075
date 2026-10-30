#!/usr/bin/env python3
"""F843: native 0x12F complete 207B/59-x86/6 PE fields in giant 005214B0.

Rebuild F842 selected current actor 12C/12D/12E source first;
append original actor 12F with state2, prepare stage1, animation1B
and no short +0xF00 clear. Cold compile ONE entire affected VC7.1
father and compare 12C..12F physical original PE bytes, true calls,
and all previous real C8..D2 cases and five packed 901B tables.
All new native 12F bytes are equal except two genuine original
enclosing 46755B fighter epilogue long-JMP operand bytes.
Whole original giant NONEXACT, no split-case exact credit.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f843-scripted-stage12f'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BASE=0x005214B0
EARLIER={
 0x12c:(207,59,6,[203,204],0x12d),
 0x12d:(219,61,6,[215,216],0x12e),
 0x12e:(207,59,6,[203,204],0x12f),
 0x12f:(207,59,6,[203,204],0x130),
}
PREVIOUS=[
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

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(tag,name):
    s=importlib.util.spec_from_file_location(tag,ROOT/'scripts'/name)
    need(s is not None and s.loader is not None,'original PE helper missing '+name)
    m=importlib.util.module_from_spec(s)
    sys.modules[tag]=m
    s.loader.exec_module(m)
    return m

def generate_source(reader,pe,d,by):
    OUT.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(ROOT/'scripts/repo-python'),
      str(ROOT/'scripts/verify-scripted-fighter-falling-recovery-f842.py')],
      cwd=ROOT,text=True,capture_output=True,timeout=1250)
    (OUT/'f842-prior-original-proof.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'F842 previous selected 12CDE source PE proof failed '+(p.stdout+p.stderr)[-700:])
    original=list(d.disasm(reader.pe_bytes_at(pe,by[0x12f],by[0x130]-by[0x12f]),by[0x12f]))
    need(len(original)==59 and by[0x130]-by[0x12f]==207
         and original[44].mnemonic=='push' and original[44].op_str=='2'
         and original[49].mnemonic=='cmp' and original[49].op_str.endswith(', 1')
         and original[55].mnemonic=='push' and original[55].op_str=='0x1b'
         and original[47].mnemonic=='mov' and '+ 0xf00]' not in original[47].op_str,
         'actual native 12F stage1/action2/animation1B without F00 clear changed')
    src=(ROOT/'.analysis/f842-scripted-falling-recovery/Boss005214B0-F842-whole.cpp').read_text()
    marker='        case 0x12F: g_FighterProbeMarker = 304; break;'
    need(src.count(marker)==1,'original next 12F source placeholder not found')
    params={'F653_ACTION':'0x12F','F653_NEXT_ACTION':'2',
            'F653_PREPARE_FRAME':'1','F653_PREPARE_ANIM':'0x1B',
            'F653_CLEAR_F00':'0'}
    generated='\n'.join('#define '+k+' '+v for k,v in params.items())
    generated+='\n#include "FighterScriptedFallingRecoveryF842.inc"\n'
    generated+='\n'.join('#undef '+k for k in params)
    return src.replace(marker,generated,1)

def compile_one(src):
    cpp=OUT/'Boss005214B0-F843-whole.cpp';obj=OUT/'Boss005214B0-F843-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy()
    E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=ROOT,env=E,text=True,capture_output=True,timeout=285)
    (OUT/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'F843 entire fighter VC7.1 original C++ compile failed '+(p.stdout+p.stderr)[-750:])
    return obj

def main():
    rd=load('f843rd','compare-coff-function.py')
    ac=load('f843ac','report-fighter-action-handlers.py')
    f653=load('f843f653','verify-fighter-falling-recovery-f653.py')
    f834=load('f843f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=load('f843f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=load('f843zero','verify-fighter-actionzero-natural-source.py')
    sw=load('f843switch','verify-fighter-natural-switch-probes.py')
    D=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==BASE)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original selected whole fighter PE identity changed')
    report,mp=ac.report_boss(rd,pe,D,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(generate_source(rd,pe,D,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in D.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(22102,6023,874,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current whole VC7.1 father native ABI/COFF x86 geometry changed')
    ds,ss,ms=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(ds>0 and ss>0 and ms>0,'all five original packed afterRET tables not checked')
    m=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x131')
       and any('g_FighterProbeMarker' in q['symbol']
           and x.address<=q['offset']<x.address+x.size for q in refs)]
    need(len(m)==1 and m[0]>=238,'original following 130 marker not unique')
    end=m[0];seg=ins[end-238:end]
    off=0;cases=[]
    for a,(nb,nx,nf,bad,nxt) in EARLIER.items():
        part=seg[off:off+nx];off+=nx
        out=f834.physical_case(rd,pe,D,code,refs,part,by,a,nb,nf,bad,nxt,f820)
        need(out['native_complete_x86']==nx and
             out['original_native_enclosing_parent_JMP_exit_ordinals']==[nx-1]
             and part[-1].op_str==hex(ret-4),
             'original selected 12C/12D/12E/12F full native PE and epilogue changed')
        original=list(D.disasm(rd.pe_bytes_at(pe,by[a],nb),by[a]))
        fields=f653.FIELDS|{nx-2:(0x00453D60,'call','PrepareActionAt453D60')}
        for j,(target,mn,sym) in fields.items():
            x,y=original[j],part[j]
            found=[r for r in refs if y.address<=r['offset']<y.address+y.size]
            need(x.mnemonic==y.mnemonic==mn and len(found)==1
                 and sym in found[0]['symbol']
                 and found[0]['offset']-part[0].address==x.address-by[a]+x.size-4,
                 'true selected PE original physical field ordinal changed '+hex(a))
        cases.append(out)
    need(off==len(seg)==238,'genuine four original falling states truncated')
    previous=ins[end-238-sum(x[2] for x in PREVIOUS):end-238]
    off=0;prior=[]
    for a,nb,nx,nf,bad,nxt in PREVIOUS:
        part=previous[off:off+nx];off+=nx
        prior.append(f834.physical_case(rd,pe,D,code,refs,part,by,a,nb,nf,bad,nxt,f820))
    need(off==len(previous),'eleven original prior source states truncated')
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,native_tail,0x52cb25,
              [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    actual=[i for i in range(46) if i not in mask and native_tail[i]!=code[ret-46+i]]
    need(actual==[10,12,16,19],
         'native default current four PE-nonrelocation GPR operands changed')
    out={'original_fighter_whole':'0x005214B0',
       'native_original_entire_callable_CODE_B':46755,
       'current_entire_source_callable_CODE_B':ret,
       'four_true_native_falling_cases':cases,
       'new_original_12F_inner_CODE_B':207,
       'new_original_12F_x86':59,
       'original_12F_typed_PE_fields':6,
       'selected_original_12F_actor_parameters':{'next_action':2,'prepare_stage':1,'animation':27,'clear_F00':False},
       'previous_11_original_C8_to_D2_cases_physically_rechecked':prior,
       'native_default_nonfield_GPR_wrong_offsets':actual,
       'original_five_afterRET_packed_tables_verified':True,
       'separate_native_jump_DATA_B':901,
       'original_whole_giant_exact':False,'new_exact_accepted_whole_CODE_B':0,
       'mass_cold_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F843 original 12F 207B/59x86/6 original PE fields in one 22102B/6023x86 current whole fighter. All four real 12C-DE-12F original state cases and preceding 11 C8-D2 case PE refs, FIVE 901B packed tables and default actual GPR byte differences verified. 12F only two original whole-epilogue JMP bytes differ. Whole 46755B giant NONEXACT.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F843 native 12F current fighter source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
