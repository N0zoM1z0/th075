#!/usr/bin/env python3
"""F821: actual complete native fighter action0x91 in full growing 46KB parent.

Regenerate selected F820 whole source with previous real 8C/8F/90
and mode63, add F629 natural 0x91 arc/ground logic, recompile ONE
affected parent. Verify entire original action0x91 as 288B/78 x86,
12 true original PE/COFF fields, previous 3 landings plus shifted
original mode63 PE field and full 901B afterRET DATA.
Shorter-parent native register matches do NOT transfer: 37 true
nonrelocated source bytes differ in the enlarged current parent.
No whole-game exactness claim or accepted-corpus cold replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f821-scripted-arc'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
NATIVE=0x005214B0
TRIO=(0x8c,0x8f,0x90)

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(tag,filename):
    sp=importlib.util.spec_from_file_location(tag,ROOT/'scripts'/filename)
    need(sp is not None and sp.loader is not None,'missing pinned native PE helper '+filename)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def original_source(info):
    OUT.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(ROOT/'scripts/repo-python'),
         str(ROOT/'scripts/verify-scripted-fighter-landing-trio-f820.py')],
         cwd=ROOT,capture_output=True,text=True,timeout=1100)
    (OUT/'f820-prior-selected-source-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'prior selected F820 whole 8C/8F/90 source failed '+
         (run.stdout+run.stderr)[-750:])
    source=(ROOT/'.analysis/f820-scripted-landings/Boss005214B0-F820-whole.cpp').read_text()
    marker='        case 0x91: g_FighterProbeMarker = 146; break;'
    need(source.count(marker)==1,'original next case0x91 source placeholder missing')
    inc=(ROOT/'probes/FighterScriptedArc91F821.inc').read_text()
    need(inc.count('case 0x91:')==1 and inc.count('return;')==3,
         'native original arc/ground return-source shape changed')
    need(info['native_stage']==3 and info['native_early_aux']==4
         and info['native_late_aux']==7 and info['native_trajectory_short_owner']==0xf00,
         'actual actor native arc action stage/aux/state differs')
    defs={'F629_STAGE':str(info['native_stage']),
          'F629_EARLY':str(info['native_early_aux']),
          'F629_LATE':str(info['native_late_aux']),
          'F629_COUNTER':'0xF00'}
    replacement='\n'.join('#define '+k+' '+v for k,v in defs.items())
    replacement+='\n#include "FighterScriptedArc91F821.inc"\n'
    replacement+='\n'.join('#undef '+k for k in defs)
    return source.replace(marker,replacement,1)

def build(src):
    cpp=OUT/'Boss005214B0-F821-whole.cpp'
    obj=OUT/'Boss005214B0-F821-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=290)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'selected whole original action91 VC7.1 build failed '+
         (proc.stdout+proc.stderr)[-860:])
    return obj

def main():
    rd=load('f821_rd','compare-coff-function.py')
    f629=load('f821_f629','verify-fighter-arc91-f629.py')
    f628=load('f821_f628','verify-fighter-jump-landings-f628.py')
    f626=load('f821_f626','verify-fighter-mode63-basic-f626.py')
    f820=load('f821_f820','verify-scripted-fighter-landing-trio-f820.py')
    actions=load('f821_actions','report-fighter-action-handlers.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==NATIVE)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'actual whole native target function or afterRET DATA ownership changed')
    report,mapped=actions.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    native91,info=f629.real_original(rd,pe,d,boss,by)
    need(info['original_complete_internal_CODE_bytes']==288
         and info['native_original_complete_x86']==78
         and info['native_physical_PE_COFF_fields']==12,
         'genuine original target case0x91 physical GPR/PE extent changed')
    obj=build(original_source(info))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret,len(refs))==(13282,3486,901,621)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'whole affected native fighter COFF/EBP/switch geometry changed')
    markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
             and x.op_str.endswith(', 0x97') and
             any('g_FighterProbeMarker' in r['symbol'] and
                 x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1 and markers[0]>=318,
         'genuine following 0x96 source marker not unique')
    point=markers[0]
    s91=ins[point-78:point]
    need(len(s91)==len(native91)==78 and
         s91[-1].address+s91[-1].size==ins[point].address,
         'original 91 source entire native case not bounded by next case96')
    lo,hi=s91[0].address,s91[-1].address+s91[-1].size
    original=rd.pe_bytes_at(pe,by[0x91],288)
    need(hi-lo==288 and
         all(a.mnemonic==b.mnemonic and a.size==b.size
             for a,b in zip(native91,s91)),
         'selected 91 x87/GPR/CFG codegen mnemonic or width mismatch')
    fields=[r for r in refs if lo<=r['offset']<hi]
    original_mask=f820.physical_fields(rd,original,by[0x91],fields,lo,12)
    for ordinal,(target,mn,symbol) in f629.FIELDS.items():
        a,b=native91[ordinal],s91[ordinal]
        x=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(a.mnemonic==b.mnemonic==mn and len(x)==1
             and symbol in x[0]['symbol'],
             'native original game F629 call/float x86 field ordinal differs')
        orig_byte=a.address-by[0x91]+a.size-4
        need(x[0]['offset']-lo==orig_byte,
             'original 0x91 source PE field shifted despite matching instruction widths')
    wrong=[j for j in range(288) if j not in original_mask and
           original[j]!=code[lo+j]]
    need(len(wrong)==37,'new source 0x91 native unrelocation role difference count changed')
    native_trio={a:f628.native_case(rd,pe,d,boss,by,a) for a in TRIO}
    prior=ins[point-78-240:point-78]
    need(len(prior)==240,'all three earlier landing game case x86 boundaries lost')
    summaries=[]
    for i,action in enumerate(TRIO):
        real,meta=native_trio[action]
        current=prior[i*80:(i+1)*80]
        start,end=current[0].address,current[-1].address+current[-1].size
        need(len(current)==len(real)==80 and end-start==289 and
             all(a.mnemonic==b.mnemonic and a.size==b.size
                 for a,b in zip(real,current)),
             'prior 8C/8F/90 complete original x86 geometry altered')
        raw=rd.pe_bytes_at(pe,by[action],289)
        fields=[r for r in refs if start<=r['offset']<end]
        mask=f820.physical_fields(rd,raw,by[action],fields,start,8)
        diff=[j for j in range(289) if j not in mask and raw[j]!=code[start+j]]
        need(len(diff)==55,'previous original landing role-differences not preserved in newer parent')
        summaries.append({'action':hex(action),'complete_native_B':289,
                          'native_x86':80,'original_pe_fields':8,
                          'real_nonrelocation_wrong_B':len(diff)})
    native63,meta63=f626.original_case(rd,pe,d,boss,by)
    src63=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+25*4)
    end63=prior[0].address
    source63=list(d.disasm(code[src63:end63],src63))
    need(end63-src63==417 and len(source63)==len(native63)==109
         and all(a.mnemonic==b.mnemonic for a,b in zip(native63,source63))
         and [j for j,(a,b) in enumerate(zip(native63,source63)) if a.size!=b.size]==[38,61],
         'earlier current parent mode63 physical width negative changed')
    fields63=[r for r in refs if src63<=r['offset']<end63]
    need(len(fields63)==7,'previous original mode63 true PE fields no longer present')
    offsets={}
    for ord,(target,mn,symbol) in f626.FIELDS.items():
        na,sa=native63[ord],source63[ord]
        matching=[r for r in fields63 if sa.address<=r['offset']<sa.address+sa.size]
        need(len(matching)==1 and matching[0]['type']==('DIR32' if ord==0 else 'REL32')
             and matching[0]['addend']==0 and matching[0]['local_symbol_offset'] is None
             and symbol in matching[0]['symbol'],
             'original 0x63 typed PE/global source symbol changed')
        offsets[str(ord)]=(matching[0]['offset']-src63)-(
             na.address-by[0x63]+na.size-4)
    need(offsets=={'0':0,'22':0,'48':-1,'71':0,'94':0,'99':0,'107':0},
         'previous original mode63 shifted PE field -1 not retained')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,tail,0x52cb25,fields,ret-46,3)
    tail_wrong=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(tail_wrong==[10,12,16,19],
         'current original default getter genuine GPR four byte negatives altered')
    result={'original_whole_giant':'0x005214B0',
       'native_original_callable_CODE_B':46755,
       'new_whole_source_callable_CODE_B':ret,
       'original_case91_complete_CODE_B':288,'native_case91_full_x86':78,
       'original_case91_physically_valid_native_PE_fields':12,
       'new_case91_source_native_mnemonics_widths_equal':True,
       'native_case91_original_unrelocated_wrong_B':len(wrong),
       'previous_three_native_landing_cases_physically_rechecked':summaries,
       'original_mode63_ordinal48_PEmask_field_displacement_persisted':offsets,
       'entire_original_afterRET_packed_jump_DATA_B':901,
       'native_saved_this_EBP_0x10_still_original':True,
       'current_native_default_shared_tail_GPR_wrong_bytes':tail_wrong,
       'original_giant_function_exact':False,
       'new_accepted_whole_authored_CODE_B':0,
       'full_accepted_units_cold_replay_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(result,indent=2)+chr(10))
    print('F821 original 005214B0 case0x91 added 288B/78x86/12 genuine native PE call/float fields, 13282B/3486-x86 affected whole C++ source; previous 8C/8F/90, physical mode63 -1 COFF field and 901B DATA checked. 37 true 0x91 nonfield bytes and four default GPR bytes remain wrong; full 46755B giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F821 actual original arc91 full source/PE verification FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
