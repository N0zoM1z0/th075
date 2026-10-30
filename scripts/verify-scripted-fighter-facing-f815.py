#!/usr/bin/env python3
"""F815: original scripted fighter entire native 0x5F in whole 46KB parent.

Full original 144B/44-x86 native facing action 0x5F has 3 genuine
physical PE calls; reconstruct with F620 normal C++ as part of
F814 original stage3/5D/5E parent and real F806 shared getter.
Strictly recheck 32 earlier original game cases, source DATA,
native 0x59, and PE-call identity. Thirteen original native receiver EBP bytes and two physical
parent-ending JMP displacement bytes still differ in this incomplete source.
Not exact independent CODE; no all-unit cold replay.
"""
from __future__ import annotations
from pathlib import Path
import importlib.util
import json
import os
import re
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f815-fighter-facing'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
PE_CASE=0x00523680
NATIVE_SIZE=144
NATIVE_CALLS={4:0x0040FA30,28:0x0040FAC0,50:0x0040FAC0}

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(tag,file):
    sp=importlib.util.spec_from_file_location(tag,ROOT/file)
    need(sp is not None and sp.loader is not None,'required PE reader missing '+str(file))
    mod=importlib.util.module_from_spec(sp)
    sys.modules[tag]=mod
    sp.loader.exec_module(mod)
    return mod

def generate_source():
    OUT.mkdir(parents=True,exist_ok=True)
    # Freshly rebuild and physically validate previous 32 original
    # actor action bodies before reading the newly emitted C++ source.
    proc=subprocess.run([str(ROOT/'scripts/repo-python'),
        str(ROOT/'scripts/verify-scripted-fighter-air-context-f814.py')],
        cwd=ROOT,text=True,capture_output=True,timeout=520)
    (OUT/'f814-prior-source.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'previous 32 original action source did not regenerate: '+
         (proc.stdout+proc.stderr)[-800:])
    base=(ROOT/'.analysis/f814-stage3-context/native-stage3.cpp').read_text()
    marker='        case 0x5F: g_FighterProbeMarker = 96; break;'
    need(base.count(marker)==1,'native 0x5F source placeholder changed')
    inc=(ROOT/'probes/FighterFacing5FF620.inc').read_text()
    need('case 0x5F:' in inc and 'F620_FIRST_ACTION' in inc
         and 'F620_SECOND_ACTION' in inc,
         'genuine native F620 facing source changed')
    replacement=('#define F620_FIRST_ACTION 0\n'
                 '#define F620_SECOND_ACTION 1\n'
                 '#include "FighterFacing5FF620.inc"\n'
                 '#undef F620_FIRST_ACTION\n'
                 '#undef F620_SECOND_ACTION')
    return base.replace(marker,replacement,1)

def compile_source(source):
    cpp=OUT/'Boss005214B0-native-facing.cpp'
    obj=OUT/'Boss005214B0-native-facing.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,text=True,capture_output=True,timeout=260)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'pinned normal VC7 source compilation failed: '+
         (proc.stdout+proc.stderr)[-850:])
    return obj

def main():
    rd=load('f815_reader','scripts/compare-coff-function.py')
    f617=load('f815_f617','scripts/verify-fighter-air-transition-f617.py')
    deps={name:load('f815_'+name,'scripts/'+path)
          for name,path in {
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
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'entire 46KB original identity changed')
    report,mapped=deps['actions'].report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    need(by[0x5F]==PE_CASE and by[0x60]==PE_CASE+NATIVE_SIZE,
         'original packed second-switch native 0x5F bounds changed')
    native=rd.pe_bytes_at(pe,PE_CASE,NATIVE_SIZE)
    ni=list(d.disasm(native,PE_CASE))
    need(len(ni)==44 and sum(x.size for x in ni)==144 and
         [x.mnemonic for x in ni[-3:]]==['mov','mov','jmp'],
         'whole original native facing x86/CFG changed')
    obj=compile_source(generate_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for i in d.disasm(code,0):
        ins.append(i)
        if i.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret,len(refs))==(10409,2672,901,560),
         'whole affected source 33-action VC7/CODE/COFF geometry changed')
    props={act:f617.native_case(rd,pe,d,boss,by,act) for act in (0x5D,0x5E)}
    prev=f617.verify_source(rd,pe,d,*(deps[k] for k in (
        'f598','f600','f602','f603','f605','f606','f607','f608',
        'f610','f611','f613','f614','core','zero','switch')),
        boss,report,mapped,code,refs,props,True)
    need(prev['all_previous_30_native_game_cases_source_retained']
         and prev['source_5D_native_GPR_CFG_role_mismatches']==61
         and prev['source_5E_native_GPR_CFG_role_mismatches']==61,
         'all previous current source 0x59/5D/5E native action contexts not preserved')
    orig59=rd.pe_bytes_at(pe,by[0x59],by[0x5D]-by[0x59])
    p59,p5d,p5e=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*slot)
                  for slot in (18,19,20)]
    source59=list(d.disasm(code[p59:p5d],p59))
    n59=list(d.disasm(orig59,by[0x59]))
    need(len(source59)==len(n59)==95 and p5d-p59==356
         and all(a.mnemonic==b.mnemonic and a.size==b.size
                 for a,b in zip(n59,source59))
         and sum(p59<=r['offset']<p5d for r in refs)==16,
         'real actor 0x59 original codegen/PE-field shape differs')
    tab=boss['tables'][1]
    native_slot=[int.from_bytes(rd.pe_bytes_at(pe,tab['dense_addr']+4*j,4),'little')
                 for j in (21,22)]
    need(native_slot==[PE_CASE,PE_CASE+NATIVE_SIZE]
         and rd.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])[0x5F-0x33]==21,
         'true PE sparse index or original native case bounds changed')
    fields=[next(r for r in refs if r['offset']==ret+44+4*j) for j in (21,22)]
    a,b=[r['local_symbol_offset'] for r in fields]
    si=list(d.disasm(code[a:b],a))
    need(b-a==NATIVE_SIZE and len(si)==len(ni)==44
         and all(n.mnemonic==g.mnemonic and n.size==g.size for n,g in zip(ni,si)),
         'new complete original action5F opcode/width/extent mismatch')
    reloc=[r for r in refs if a<=r['offset']<b]
    need(len(reloc)==3 and {r['offset']-a for r in reloc}==set(NATIVE_CALLS),
         'original 3 case5F game calls missing')
    mask=set()
    for f in reloc:
        off=f['offset']-a
        target=PE_CASE+off+4+int.from_bytes(native[off:off+4],'little',signed=True)
        need(f['type']=='REL32' and f['addend']==0 and
             f['local_symbol_offset'] is None and target==NATIVE_CALLS[off]
             and f'At{target:06X}' in f['symbol'],
             'true native case5F original PE call target wrong '+str(f))
        mask.update(range(off,off+4))
    wrong=[k for k in range(NATIVE_SIZE) if k not in mask and native[k]!=code[a+k]]
    saved_this_bad=[2,13,26,34,48,56,63,77,86,102,109,118,134]
    need(wrong==saved_this_bad+[140,141]
         and all(native[k]==0xF0 and code[a+k]==0xF8 for k in saved_this_bad)
         and ni[-1].mnemonic==si[-1].mnemonic=='jmp'
         and ni[-1].op_str=='0x52cb4f' and si[-1].size==ni[-1].size==5,
         'real native case5F saved receiver or whole-parent jump differs beyond expected incomplete frame')
    native_tail=rd.pe_bytes_at(pe,0x0052CB25,46)
    tailrels=[r for r in refs if ret-46<=r['offset']<ret]
    need(len(tailrels)==3,'original shared default true three PE calls lost')
    masks={j for r in tailrels for j in range(r['offset']-(ret-46),r['offset']-(ret-46)+4)}
    tail_wrong=[j for j in range(46) if j not in masks and
                native_tail[j]!=code[ret-46+j]]
    need(tail_wrong==[2,10,12,13,16,19,26,36],
         'old incomplete whole-parent default GPR/stack-phase honest differences changed')
    results={'native_original_whole_giant':'0x005214B0',
             'native_original_whole_CODE_B':46755,
             'new_whole_source_callable_CODE_B':ret,
             'source_x86':len(ins),
             'native_new_case5F':'0x00523680',
             'native_5F_entire_CODE_B':144,
             'native_5F_whole_x86':44,
             'native_5F_real_PE_call_relocations':3,
             'native_5F_original_EBP_receiver_nonfield_bytes_different':saved_this_bad,
             'native_5F_parent_external_JMP_bytes_different':[140,141],
             'real_parent_saved_this_stack_EBP':'-8',
             'previous_32_real_original_cases_verified':True,
             'original_901B_afterRET_packed_DATA_rechecked':True,
             'parent_native_default_tail_remaining_real_nonfield_diffs':tail_wrong,
             'entire_original_game_boss_exact':False,
             'accepted_new_whole_callable_CODE_B':0,
             'whole_979_accepted_unit_cold_replay':False}
    (OUT/'verified-summary.json').write_text(json.dumps(results,indent=2)+chr(10))
    print('F815 original 5F whole 144B/44 x86/3 real PE calls: compiler matches full original geometry; 13 genuine saved-this EBP-8 vs original EBP-0x10 bytes and two parent-final JMP bytes still differ in 10409B incomplete parent. Earlier 32 native cases/901B switch DATA verified. No callable exact credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F815 targeted native facing source FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
