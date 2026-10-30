#!/usr/bin/env python3
"""F816: TWO entire original 586B resource-volley actions make 46B tail nonfield exact.

Freshly regenerate and PE-verify the F815 source for selected 005214B0
(original first 33 source-backed actions) before adding 0x60/0x61 normal
actual game C++. Both original native full cases 586B/169 x86 have
eleven zero-addend physically mapped PE/COFF call/global fields, and
complete literal x86 source differs ONLY at two genuine external
giant-epilogue JMP rel32 displacements per case. The two real 10-shot
loop counters move saved this to the original EBP-0x10 and the original
46B/16-x86 shared default/getter becomes *all 34/34 nonrelocation
bytes equal* with three real PE calls. No whole original 46755B exact,
no independent split-case CODE credit or all accepted-unit cold replay.
"""
from __future__ import annotations
import importlib.util
import json
import os
import re
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f816-scripted-resource'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
WHOLE=0x005214B0
CASES={
   0x5F:(21,0x00523680,0x00523710,144,44,3,[140,141]),
   0x60:(22,0x00523710,0x0052395A,586,169,11,[395,396,582,583]),
   0x61:(23,0x0052395A,0x00523BA4,586,169,11,[395,396,582,583]),
}
TAIL=0x0052CB25
SUFFIX_LEN=46
CALLS={4:0x0040FA30,28:0x0040FAC0,38:0x0040FA30}

def need(value,msg):
    if not value:raise ValueError(msg)

def load(tag,relpath):
    sp=importlib.util.spec_from_file_location(tag,ROOT/relpath)
    need(sp is not None and sp.loader is not None,'missing genuine native source verifier '+str(relpath))
    mod=importlib.util.module_from_spec(sp)
    sys.modules[tag]=mod
    sp.loader.exec_module(mod)
    return mod

def assemble_source():
    # The immediate previous full source object is regenerated and
    # independently verified, not read as a stale historical guess.
    OUT.mkdir(parents=True,exist_ok=True)
    proc=subprocess.run([str(ROOT/'scripts/repo-python'),
        str(ROOT/'scripts/verify-scripted-fighter-facing-f815.py')],
        cwd=ROOT,capture_output=True,text=True,timeout=500)
    (OUT/'f815-prior-native-evidence.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'prior whole original game 33-case source did not re-verify '+
         (proc.stdout+proc.stderr)[-750:])
    base=(ROOT/'.analysis/f815-fighter-facing/Boss005214B0-native-facing.cpp').read_text()
    inc=(ROOT/'probes/FighterScriptedResourceVolleysF816.inc').read_text()
    need(inc.count('case 0x60:')==inc.count('case 0x61:')==1
         and inc.count('for (int shot=0;shot<10;++shot)')==2
         and inc.count('SetAuxActionAt40FB40(4)')==2
         and inc.count('SetAuxActionAt40FB40(3)')==2
         and inc.count('POS54+POS48<g_ThresholdAt0065782C')==2
         and inc.count('return;')==4 and 'break;' not in inc,
         'genuine stage 2/3 native signed strict contact and both used ten-shot loops changed')
    first='        case 0x60: g_FighterProbeMarker = 97; break;'
    last='        case 0x61: g_FighterProbeMarker = 98; break;'
    need(base.count(first)==base.count(last)==1,'old current partial game source no longer has 0x60/61 markers')
    # Both original native 0x5F and real native 0x60/61 exit DIRECTLY
    # to the native whole game function epilogue. Using ordinary C++
    # return; in the void method preserves the real CFG; the generic
    # F620 switch-case break folded to an extra default JMP instead.
    original_face='#include "FighterFacing5FF620.inc"'
    need(base.count(original_face)==1,'current prior 0x5F source include changed')
    face=(ROOT/'probes/FighterScriptedFacingF816.inc').read_text()
    need(face.count('case 0x5F:')==1 and face.count('return;')==1,
         'original 0x5F direct epilogue C++ source missing')
    base=base.replace(original_face,
       '#include "FighterScriptedFacingF816.inc"',1)
    # Distinct original 0x60/0x61 PE-backed source is compiled with a
    # real typed global. This is not a generated x86 fragment.
    source='extern float g_F748_SpeedScaleAt006590B8;\n'+base
    source=source.replace(first,'#include "FighterScriptedResourceVolleysF816.inc"',1)
    source=source.replace(last,'',1)
    return source

def compile_one(source):
    cpp=OUT/'Boss005214B0-full-resource-volley.cpp'
    obj=OUT/'Boss005214B0-full-resource-volley.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv= d;winemenubuilder.exe=d'.replace('= d','=d')
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
         cwd=ROOT,env=env,text=True,capture_output=True,timeout=280)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'current original whole 0x60/61 normal VC7.1 source failed '+
         (proc.stdout+proc.stderr)[-950:])
    return obj

def true_PE_fields(original,origin,lo,refs,expected_count):
    need(len(refs)==expected_count,'actual original source PE field count changed')
    masked=set()
    result=[]
    for r in refs:
        k=r['offset']-lo
        need(0<=k<=len(original)-4 and
             r['type'] in ('DIR32','REL32') and r['addend']==0 and
             r['local_symbol_offset'] is None,'original typed native field shape unproved '+str(r))
        target=(int.from_bytes(original[k:k+4],'little') if r['type']=='DIR32' else
                origin+k+4+int.from_bytes(original[k:k+4],'little',signed=True))
        match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
        expected=(int(match.group(1),16) if match else
                  0x006406AC if r['symbol']=='__ftol2' else None)
        need(expected is not None and target==expected,
             'original independent PE call/global destination not the actual compiler symbol '+str(r))
        need(all(k+i not in masked for i in range(4)),
             'overlapping false source PE fields')
        masked.update(range(k,k+4))
        result.append({'offset':hex(k),'native_kind':r['type'],'native_target':hex(target)})
    return result,masked

def main():
    rd=load('f816_reader','scripts/compare-coff-function.py')
    f617=load('f816_f617','scripts/verify-fighter-air-transition-f617.py')
    deps={name:load('f816_'+name,'scripts/'+file)
          for name,file in {
            'f598':'verify-fighter-singleton-contact-f598.py',
            'f600':'verify-fighter-additional-contact-f600.py',
            'f602':'verify-fighter-trajectory46-f602.py',
            'f603':'verify-fighter-trajectory-spawn-f603.py',
            'f605':'verify-fighter-trajectory-followups-f605.py',
            'f606':'verify-fighter-trajectory-followup-spawns-f606.py',
            'f607':'verify-fighter-trajectory-landing-f607.py',
            'f608':'verify-fighter-trajectory-landing-spawn-f608.py',
            'f610':'verify-fighter-trajectory-bounce-f610.py',
            'f611':'verify-fighter-trajectory-bounce-spawn-f611.py',
            'f613':'verify-fighter-trajectory-recovery-f613.py',
            'f614':'verify-fighter-trajectory-burst-f614.py',
            'core':'verify-fighter-action-six-natural-source.py',
            'zero':'verify-fighter-actionzero-natural-source.py',
            'switch':'verify-fighter-natural-switch-probes.py',
            'actions':'report-fighter-action-handlers.py',
          }.items()}
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==WHOLE)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'actual source-backed original whole fighter changed')
    report,mapped=deps['actions'].report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    source=assemble_source()
    obj=compile_one(source)
    code,refs=rd.object_function(obj,SYM)
    instructions=[]
    for x in d.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    ret=instructions[-1].address+instructions[-1].size
    need((ret,len(instructions),len(code)-ret,len(refs))==(11551,3006,901,580),
         'real original loop source whole CODE/COFF and afterRET DATA geometry changed')
    need(instructions[3].mnemonic=='mov'
         and instructions[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'actual two used ten-shot loop vars no longer restore native EBP-0x10 saved-this')
    props={act:f617.native_case(rd,pe,d,boss,by,act) for act in (0x5D,0x5E)}
    prior=f617.verify_source(rd,pe,d,*(deps[k] for k in (
         'f598','f600','f602','f603','f605','f606','f607','f608','f610',
         'f611','f613','f614','core','zero','switch')),
         boss,report,mapped,code,refs,props,True)
    need(prior['all_previous_30_native_game_cases_source_retained']
         and prior['source_5D_native_GPR_CFG_role_mismatches']==61
         and prior['source_5E_native_GPR_CFG_role_mismatches']==61,
         'previous 32 real PE-backed original action sources/901B DATA not preserved')
    case_summaries={}
    table=boss['tables'][1]
    pe_index=rd.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    for action,(slot,st,en,size,nx,nref,expected_wrong) in CASES.items():
        need(by[action]==st and pe_index[action-0x33]==slot,
             'native PE packed case-handler index changed '+hex(action))
        pe_slots=[int.from_bytes(rd.pe_bytes_at(pe,table['dense_addr']+4*j,4),'little')
                  for j in (slot,slot+1)]
        need(pe_slots==[st,en] and en-st==size,
             'actual original PE dense two handler boundary fields wrong')
        original=rd.pe_bytes_at(pe,st,size)
        original_x86=list(d.disasm(original,st))
        need(len(original_x86)==nx and sum(x.size for x in original_x86)==size,
             'original complete native case instructions differ')
        field_start=[next(r for r in refs if r['offset']==ret+44+4*j)
                     for j in (slot,slot+1)]
        need(all(r['type']=='DIR32' and r['local_symbol_offset'] is not None
                 and r['addend']==0 for r in field_start),
             'current source packed original case-pointer source field missing')
        a,b=[r['local_symbol_offset'] for r in field_start]
        need(b-a==size,'entire original game case source length is not native '+hex(action))
        current=list(d.disasm(code[a:b],a))
        need(len(current)==nx and all(u.mnemonic==v.mnemonic and u.size==v.size
             and u.address-st==v.address-a for u,v in zip(original_x86,current)),
             'original complete x86 opcode/control/position changed '+hex(action))
        fields=[r for r in refs if a<=r['offset']<b]
        targets,mask=true_PE_fields(original,st,a,fields,nref)
        bad=[j for j in range(size) if j not in mask and original[j]!=code[a+j]]
        need(bad==expected_wrong,
             'unexpected original unrelocated case machine bytes '+hex(action)+': '+str(bad))
        for j in bad:
            ordinal=next(k for k,x in enumerate(original_x86)
                         if x.address-st<=j<x.address-st+x.size)
            n,s=original_x86[ordinal],current[ordinal]
            need(n.mnemonic==s.mnemonic=='jmp'
                 and n.op_str=='0x52cb4f'
                 and n.size==s.size==5 and s.op_str==hex(ret-4),
                 'remaining case 5F/60/61 difference is not a TRUE enclosing whole parent epilogue JMP')
        if action in (0x60,0x61):
            need(original_x86[48].mnemonic==current[48].mnemonic=='mov'
                 and original_x86[48].op_str==current[48].op_str
                 and original_x86[48].op_str==
                    ('dword ptr [ebp - 8], 0' if action==0x60 else 'dword ptr [ebp - 0xc], 0')
                 and original_x86[104].op_str==current[104].op_str=='ah, 5'
                 and original_x86[110].op_str==current[110].op_str=='4'
                 and original_x86[131].bytes==current[131].bytes,
                 'original 2 used native ten-burst indices/strict contact/aux4/else CFG not matched')
        case_summaries[hex(action)]={'native_full_case_B':size,
                 'native_full_x86':nx,
                 'authentic_target_PE_calls_and_globals':targets,
                 'native_unmasked_byte_comparison_B':size-len(mask),
                 'original_nonfield_byte_mismatches':bad,
                 'only_external_whole_giant_JMP_displacements_differ':True}
    # Actual 0x59 stage3 case original literal full COFF must stay in
    # current 0x60/61 parent and not be treated as exact by accident.
    src59a=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*18)
    src59b=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*19)
    orig59=rd.pe_bytes_at(pe,by[0x59],by[0x5D]-by[0x59])
    n59=list(d.disasm(orig59,by[0x59]))
    s59=list(d.disasm(code[src59a:src59b],src59a))
    need(src59b-src59a==356 and len(n59)==len(s59)==95
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(n59,s59))
         and sum(src59a<=r['offset']<src59b for r in refs)==16,
         'original stage-three 0x59 action source lost in new whole native parent')
    # Crucial positive: 46B physical native fallback is now all
    # nonrelocated MACHINE BYTES exactly equal, including saved this,
    # GPR-role bytes, branch targets and original F806 sharing.
    n_tail=rd.pe_bytes_at(pe,TAIL,SUFFIX_LEN)
    src_tail=code[ret-SUFFIX_LEN:ret]
    rel=[r for r in refs if ret-SUFFIX_LEN<=r['offset']<ret]
    truecalls,mask=true_PE_fields(n_tail,TAIL,ret-SUFFIX_LEN,rel,3)
    need({int(r['offset'],16) for r in truecalls}==set(CALLS)
         and {int(r['offset'],16):int(r['native_target'],16) for r in truecalls}==CALLS,
         'three native original default/getter true REL32 calls changed')
    need(all(r['native_kind']=='REL32' for r in truecalls),
         'default physical PE call relocation type lost')
    original_tail=list(d.disasm(n_tail,TAIL))
    generated_tail=list(d.disasm(src_tail,ret-SUFFIX_LEN))
    need(len(original_tail)==len(generated_tail)==16
         and all(n.mnemonic==c.mnemonic and n.size==c.size
                 and n.address-TAIL==c.address-(ret-SUFFIX_LEN)
                 for n,c in zip(original_tail,generated_tail))
         and all(n_tail[j]==src_tail[j] for j in range(SUFFIX_LEN) if j not in mask)
         and len(mask)==12,
         'native 46B fallback must have every one of 34 real nonrelocation bytes EXACT in whole updated parent')
    native_full=list(d.disasm(rd.pe_bytes_at(pe,WHOLE,boss['size']),WHOLE))
    actual_jump=[x for x in native_full if x.mnemonic=='jmp' and x.op_str=='0x52cb47']
    source_jump=[x for x in instructions if x.mnemonic=='jmp' and x.op_str==hex(ret-12)]
    need(tuple(x.address for x in actual_jump)==(
             0x00521709,0x00521891,0x00521974,0x00521983)
         and len(source_jump)==4,'real original action0/2/4/5 shared tail entries wrong')
    first=boss['tables'][0]
    for action in (0,2,4,5):
        nstart,nstop=[int.from_bytes(rd.pe_bytes_at(pe,first['dense_addr']+4*k,4),'little')
                      for k in (action,action+1)]
        sc0,sc1=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+4*k)
                 for k in (action,action+1)]
        phys=[x for x in actual_jump if nstart<=x.address<nstop]
        generated=[x for x in source_jump if sc0<=x.address<sc1]
        need(len(phys)==len(generated)==1 and
             phys[0].address-nstart==generated[0].address-sc0,
             'real original early shared-getter branch location changed '+str(action))
    result={'original_complete_giant':'0x005214B0',
          'native_whole_original_callable_CODE_B':46755,
          'generated_whole_parent_callable_CODE_B':ret,
          'new_real_source_actions':['0x60','0x61'],
          'original_native_action_60_61_original_B_each':586,
          'original_native_action_60_61_x86_each':169,
          'original_native_60_61_fields_each':11,
          'original_action_5F_and_new_60_61':case_summaries,
          'whole_parent_natural_saved_this_EBP':'-0x10 (native original)',
          'original_native_two_real_burst_loop_counter_EBP':['-8','-0xC'],
          'source_original_default_fallback_tail_full_B':46,
          'real_original_default_tail_nonrelocation_bytes_exact':'34/34',
          'three_actual_original_tail_PE_REL32_calls':truecalls,
          'four_original_early_shared_getter_jumps_verified':True,
          'all_33_previous_original_source_cases_verified':True,
          'entire_original_postRET_packed_DATA_B':901,
          'full_original_game_function_exact':False,
          'new_accepted_whole_callable_CODE_B':0,
          'all_accepted_units_mass_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(result,indent=2)+chr(10))
    print('F816 breakthrough: real 0x60/0x61 source each 586B/169x86/11 original PE fields, only two parent-external JMP displacement bytes each remain; used 10-shot loop indices at EBP-8 and EBP-0xC NATURALLY recover original saved this EBP-0x10. Entire original 46B shared default/getter now 34/34 actual nonrelocation bytes EXACT plus 3 true native PE REL32 calls; all 33 previous cases, 901B switch DATA and 4 original entry JMPs checked. Giant 46755B still NONEXACT: zero whole game credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as ex:
        print('F816 native original complete case/whole-parent verification FAILED:',ex,file=sys.stderr)
        raise SystemExit(1)
