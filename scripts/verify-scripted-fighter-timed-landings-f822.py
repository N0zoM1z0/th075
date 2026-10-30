#!/usr/bin/env python3
"""F822: four original 276B/73-x86 native timed landings in whole 46KB fighter.

Regenerate the selected prior F821 original source, then independently
add real 0x96/97/98/9A from the pinned target's actual parameters.
Compile one complete affected VC7.1 parent and check 4x9 true original
PE call/global fields. Every new native case has only TWO authentic
unrelocated parent-final JMP displacement bytes different. Recheck
the current parent earlier 0x91, three 8C/8F/90, genuine shifted 0x63
COFF relocation, native saved-this frame and original 901B afterRET
packed switch DATA. No independent case/giant exact credit, no all-unit
cold replay.
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
OUT=ROOT/'.analysis/f822-scripted-timed'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
NEW=(0x96,0x97,0x98,0x9a)
TRIO=(0x8c,0x8f,0x90)

def need(p,msg):
    if not p:raise ValueError(msg)

def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/'scripts'/path)
    need(sp is not None and sp.loader is not None,'missing native physical PE helper '+path)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def native_source(facts):
    OUT.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(ROOT/'scripts/repo-python'),
      str(ROOT/'scripts/verify-scripted-fighter-arc91-context-f821.py')],
      cwd=ROOT,text=True,capture_output=True,timeout=1200)
    (OUT/'f821-prior-whole-native-source.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'targeted earlier full original game source invalid '+
         (run.stdout+run.stderr)[-870:])
    source=(ROOT/'.analysis/f821-scripted-arc/Boss005214B0-F821-whole.cpp').read_text()
    source=('extern float g_AnimationDeltaAt0065747C;\n'
            'extern float g_AnimationMaximumAt006583B4;\n'+source)
    a=(ROOT/'probes/FighterScriptedLanding96F822.inc').read_text()
    b=(ROOT/'probes/FighterScriptedLandingSiblingsF822.inc').read_text()
    need(a.count('case 0x96:')==1 and a.count('return;')==1
         and b.count('case F633_CASE:')==1 and b.count('return;')==1,
         'genuine direct native epilogue source incorrectly rewritten')
    for action in NEW:
        mark=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(mark)==1,'physical original timer case marker missing '+hex(action))
        info=facts[action][1]
        if action==0x96:
            need(info['original_counter_short_owner']==0xf00
                 and not info['original_extra_short_0xF0A_present'],
                 'original actor96 motion short and extra-native flags drifted')
            defs={'F631_COUNTER':'0xF00',
                  'F631_EXTRA_FLAG':'0',
                  'F631_EXTRA_BEFORE':'0'}
            inc='FighterScriptedLanding96F822.inc'
        else:
            need(info['native_trajectory_counter_offset']==0xf00
                 and not info['real_extra_short_0xF0A'],
                 'actor landing sibling native counter or real F0A extra flag changed')
            defs={'F633_CASE':hex(action).upper().replace('0X','0x'),
                  'F633_COUNTER':'0xF00',
                  'F633_START_HEIGHT':repr(info['original_initial_float_height'])+'f',
                  'F633_NEXT_ACTION':str(info['original_followup_action_state']),
                  'F633_EXTRA_FLAG':'0','F633_EXTRA_BEFORE':'0'}
            inc='FighterScriptedLandingSiblingsF822.inc'
        text='\n'.join('#define '+k+' '+v for k,v in defs.items())
        text+='\n#include "'+inc+'"\n'
        text+='\n'.join('#undef '+k for k in defs)
        source=source.replace(mark,text,1)
    need(source.count('#include "FighterScriptedLanding96F822.inc"')==1
         and source.count('#include "FighterScriptedLandingSiblingsF822.inc"')==3,
         'all four original timed native C++ actions not assembled')
    return source

def compile_one(src):
    cpp=OUT/'Boss005214B0-F822-all.cpp'
    obj=OUT/'Boss005214B0-F822-all.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=310)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'original selected whole timed C++ parent build failed '+(cp.stdout+cp.stderr)[-850:])
    return obj

def main():
    rd=load('f822_rd','compare-coff-function.py')
    f631=load('f822_f631','verify-fighter-landing-timer96-f631.py')
    f633=load('f822_f633','verify-fighter-landing-siblings-f633.py')
    f629=load('f822_f629','verify-fighter-arc91-f629.py')
    f628=load('f822_f628','verify-fighter-jump-landings-f628.py')
    f626=load('f822_f626','verify-fighter-mode63-basic-f626.py')
    f820=load('f822_f820','verify-scripted-fighter-landing-trio-f820.py')
    actions=load('f822_actions','report-fighter-action-handlers.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'genuine original game target identity changed')
    report,mapped=actions.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    facts={action:(f631.original_case(rd,pe,d,boss,by) if action==0x96
        else f633.original_case(rd,pe,d,boss,by,action)) for action in NEW}
    obj=compile_one(native_source(facts))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret,len(refs))==(14326,3770,901,653)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'source entire fighter native EBP frame/real switch COFF shape changed')
    # The next genuine original case is 0x9B, its unique g_marker
    # is 0x9C. Exactly 4x73 complete source instructions precede it.
    markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0x9c')
       and any('g_FighterProbeMarker' in r['symbol']
          and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1 and markers[0]>=292,
         'actual following original 0x9B case marker not uniquely located')
    boundary=markers[0]
    group=ins[boundary-4*73:boundary]
    summaries=[]
    for idx,action in enumerate(NEW):
        original,meta=facts[action]
        generated=group[idx*73:(idx+1)*73]
        lo,hi=generated[0].address,generated[-1].address+generated[-1].size
        native_raw=rd.pe_bytes_at(pe,by[action],276)
        need(hi-lo==276 and len(generated)==len(original)==73
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(original,generated)),
             'original complete timed landing x86 geometry differs '+hex(action))
        fields=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,native_raw,by[action],fields,lo,9)
        for ordinal,(dest,mn,symbol) in f631.FIELDS.items():
            a,b=original[ordinal],generated[ordinal]
            inside=[r for r in fields if b.address<=r['offset']<b.address+b.size]
            need(a.mnemonic==b.mnemonic==mn and len(inside)==1
                 and symbol in inside[0]['symbol']
                 and inside[0]['offset']-lo==a.address-by[action]+a.size-4,
                 'native original real timer field not at exact PE source x86 ordinal '+hex(action))
        wrong=[j for j in range(276) if j not in mask and native_raw[j]!=code[lo+j]]
        need(wrong==[272,273],
             'native timer case must differ ONLY in physical encompassing-giant final JMP '+str((action,wrong)))
        need(original[-1].mnemonic==generated[-1].mnemonic=='jmp'
             and original[-1].op_str=='0x52cb4f' and generated[-1].op_str==hex(ret-4),
             'source actual timed case must return to original void fighter epilogue')
        summaries.append({'native_action':hex(action),'original_full_CODE_B':276,
                'native_full_x86':73,'actual_original_PE_COFF_fields':9,
                'original_true_nonrel_wrong_offsets':wrong,
                'all_native_nonexternal_source_bytes_equal':True,
                'whole_function_accepted_CODE_B':0})
    # Recheck original 0x91 and the preceding 8C/8F/90 in the
    # SAME newly compiled entire source, not from an old object.
    n91,meta91=f629.real_original(rd,pe,d,boss,by)
    source91=ins[boundary-292-78:boundary-292]
    need(len(source91)==78 and source91[-1].address+source91[-1].size==group[0].address
         and source91[-1].address-source91[0].address+source91[-1].size==288
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(n91,source91)),
         'prior native original 91 whole arc case no longer valid')
    j91=source91[0].address
    old91=rd.pe_bytes_at(pe,by[0x91],288)
    fields91=[r for r in refs if j91<=r['offset']<group[0].address]
    mask91=f820.physical_fields(rd,old91,by[0x91],fields91,j91,12)
    wrong91=[j for j in range(288) if j not in mask91 and old91[j]!=code[j91+j]]
    need(len(wrong91)==37,'previous original 91 GPR/PE case context changed')
    nland={a:f628.native_case(rd,pe,d,boss,by,a) for a in TRIO}
    before=ins[boundary-292-78-240:boundary-292-78]
    need(len(before)==240 and before[-1].address+before[-1].size==source91[0].address,
         'three earlier original landing cases no longer contiguous')
    for idx,a in enumerate(TRIO):
        original,info=nland[a]
        own=before[idx*80:(idx+1)*80]
        lo,hi=own[0].address,own[-1].address+own[-1].size
        need(hi-lo==289 and all(x.mnemonic==y.mnemonic and x.size==y.size
             for x,y in zip(original,own)),
             'earlier original 8C/8F/90 machine source altered')
        raw=rd.pe_bytes_at(pe,by[a],289)
        fields=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,by[a],fields,lo,8)
        wrong=[j for j in range(289) if j not in mask and raw[j]!=code[lo+j]]
        need(len(wrong)==55,'real earlier landing case PE frame register phase changed')
    # The current 0x63 source is still physically shifted one COFF
    # field by -1; never mask its candidate COFF as original PE.
    n63,info63=f626.original_case(rd,pe,d,boss,by)
    srclo=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+25*4)
    srchi=before[0].address
    c63=list(d.disasm(code[srclo:srchi],srclo))
    need(srchi-srclo==417 and len(c63)==len(n63)==109
         and [j for j,(a,b) in enumerate(zip(n63,c63)) if a.size!=b.size]==[38,61]
         and all(a.mnemonic==b.mnemonic for a,b in zip(n63,c63)),
         'previous actual mode63 source/PE x86 shift did not persist')
    offsets={}
    for ordinal,(dest,mn,symbol) in f626.FIELDS.items():
        a,b=n63[ordinal],c63[ordinal]
        match=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(match)==1 and match[0]['addend']==0
             and match[0]['local_symbol_offset'] is None
             and symbol in match[0]['symbol'],
             'mode63 true typed call/global field missing')
        offsets[str(ordinal)]=match[0]['offset']-srclo-(a.address-by[0x63]+a.size-4)
    need(offsets=={'0':0,'22':0,'48':-1,'71':0,'94':0,'99':0,'107':0},
         'original mode63 moved COFF field not physically rechecked')
    t=rd.pe_bytes_at(pe,0x52CB25,46)
    tfields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,t,0x52CB25,tfields,ret-46,3)
    twrong=[j for j in range(46) if j not in mask and t[j]!=code[ret-46+j]]
    need(twrong==[10,12,16,19],
         'shared default original physical GPR register phase unexpectedly changed')
    result={'original_fighter_whole':'0x005214B0',
         'original_native_callable_CODE_B':46755,
         'generated_complete_parent_callable_CODE_B':ret,
         'four_new_timed_native_cases':summaries,
         'new_original_complete_internal_CODE_B_total':1104,
         'new_original_physical_PE_COFF_fields_total':36,
         'previous_arc91_native_x86_and_PE_rechecked':True,
         'previous_three_landing_native_x86_and_PE_rechecked':True,
         'original_mode63_one_shifted_COFF_field_unmasked':True,
         'native_shared_default_nonrelocation_wrong_offsets':twrong,
         'native_separate_packed_afterRET_DATA_B':901,
         'native_saved_this_EBP_0x10_persists':True,
         'original_whole_function_exact':False,
         'new_accepted_authored_whole_CODE_B':0,
         'mass_979_unit_cold_replay_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(result,indent=2)+chr(10))
    print('F822: true native 96/97/98/9A four 276B/73-x86/9-original-PE-field game states (1104B/292 x86/36 fields) newly integrated in 14326-B/3770-x86 whole fighter. ONLY 2 genuine encompassing-parent final JMP bytes per case differ; all native register/float/CFG bytes and 36 field positions match. Earlier 91, 8C-90, 63, 901B DATA rechecked. Giant 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F822 original timed-landing whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
