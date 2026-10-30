#!/usr/bin/env python3
"""F817: original 249B/65-x86/4-PE-field case0x62 integrated after real native frame.

Regenerate selected F816 whole 46KB parent from tracked prior game
source, recheck its first 35 complete original inner action bodies,
901B postRET DATA and 34/34 native default-tail nonfield positives,
then add authentic 0x62 resource selector and recompile entire affected
parent. 0x62 has 10 TRUE GPR operand byte differences and 2 parent
external-JMP differences, and rotates downstream original 46B
default's GPR phase back to four real nonfield negatives while
preserving native EBP-0x10. No whole-original or split-case exact
credit, no all accepted units cold replay.
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
OUT=ROOT/'.analysis/f817-scripted-selector'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
NATIVE_ORIGINAL=0x005214B0
SUFFIX=0x0052CB25
CASES={0x5F:(21,0x00523680,144,44,3,[140,141]),
       0x60:(22,0x00523710,586,169,11,[395,396,582,583]),
       0x61:(23,0x0052395A,586,169,11,[395,396,582,583]),
       0x62:(24,0x00523BA4,249,65,4,
              [172,174,178,181,195,199,205,220,224,230,245,246])}

def need(v,msg):
    if not v:raise ValueError(msg)

def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    need(spec is not None and spec.loader is not None,'required native PE reader missing '+str(path))
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m

def source_from_prior():
    OUT.mkdir(parents=True,exist_ok=True)
    proc=subprocess.run([str(ROOT/'scripts/repo-python'),
         str(ROOT/'scripts/verify-scripted-fighter-resource-volley-f816.py')],
         cwd=ROOT,capture_output=True,text=True,timeout=900)
    (OUT/'f816-native-prior-PE-evidence.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'F816 whole previous PE source failed target replay '+
         (proc.stdout+proc.stderr)[-920:])
    source=(ROOT/'.analysis/f816-scripted-resource/Boss005214B0-full-resource-volley.cpp').read_text()
    marker='        case 0x62: g_FighterProbeMarker = 99; break;'
    need(source.count(marker)==1,'native next 0x62 original source placeholder missing')
    inc=(ROOT/'probes/FighterScriptedResourceSelectorF817.inc').read_text()
    need(inc.count('case 0x62:')==1 and inc.count('return;')==1
         and inc.count('SetNativeActionAt40FAC0(0x5F)')==1
         and inc.count('SetNativeActionAt40FAC0(0x5D)')==1
         and inc.count('SetNativeActionAt40FAC0(0x5E)')==1,
         'true original 0x62 gameplay C++ source order/actions changed')
    return source.replace(marker,'#include "FighterScriptedResourceSelectorF817.inc"',1)

def compile_one(source):
    cpp=OUT/'Boss005214B0-case62-resource-selector.cpp'
    obj=OUT/'Boss005214B0-case62-resource-selector.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv= d;winemenubuilder.exe=d'.replace('= d','=d')
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=ROOT,env=env,capture_output=True,text=True,timeout=260)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,'F817 whole affected 46KB C++ source did not compile '+
         (proc.stdout+proc.stderr)[-800:])
    return obj

def main():
    rd=load('f817_reader','scripts/compare-coff-function.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==NATIVE_ORIGINAL)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original 46KB native function/afterRET ownership changed')
    obj=compile_one(source_from_prior())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret,len(refs))==(11785,3069,901,583)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'complete new source 0x62 natural EBP/COFF geometry drifted')
    second=boss['tables'][1]
    sparse=rd.pe_bytes_at(pe,second['map_addr'],second['map_length'])
    cases={}
    for action,(slot,start,size,nx,nref,expected_bad) in CASES.items():
        need(sparse[action-0x33]==slot,'original sparse action case index differs '+hex(action))
        pe_points=[int.from_bytes(rd.pe_bytes_at(pe,second['dense_addr']+4*k,4),'little')
                   for k in (slot,slot+1)]
        need(pe_points==[start,start+size],
             'original PE packed real handler pointer/whole case bounds changed '+hex(action))
        bounds=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*k)
                for k in (slot,slot+1)]
        lo,hi=bounds
        original=rd.pe_bytes_at(pe,start,size)
        emitted=code[lo:hi]
        n=list(d.disasm(original,start))
        s=list(d.disasm(emitted,lo))
        need(hi-lo==size and len(n)==len(s)==nx and
             all(a.mnemonic==b.mnemonic and a.size==b.size and
                 a.address-start==b.address-lo for a,b in zip(n,s)),
             'new complete original PE case has wrong x86 width or CFG '+hex(action))
        fields=[r for r in refs if lo<=r['offset']<hi]
        need(len(fields)==nref,'real physical PE native field count differs '+hex(action))
        mask=set()
        physical=[]
        for r in fields:
            off=r['offset']-lo
            need(r['type'] in ('DIR32','REL32') and r['local_symbol_offset'] is None
                 and r['addend']==0 and 0<=off<=size-4,
                 'false moved/typed source field for original target '+hex(action))
            dest=int.from_bytes(original[off:off+4],'little') if r['type']=='DIR32' else (
                start+off+4+int.from_bytes(original[off:off+4],'little',signed=True))
            m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
            symbol_dest=int(m.group(1),16) if m else (0x6406AC if r['symbol']=='__ftol2' else None)
            need(symbol_dest is not None and symbol_dest==dest,
                 'actual physical original PE call destination not the real source symbol '+str(r))
            mask.update(range(off,off+4))
            physical.append((hex(off),r['type'],hex(dest)))
        bad=[i for i in range(size) if i not in mask and original[i]!=emitted[i]]
        need(bad==expected_bad,
             'real 0x62/previous original case GPR/JMP machine byte differences changed '+str((action,bad)))
        for ordinal in (43,113,168,64):
            if ordinal>=len(n):continue
            x,y=n[ordinal],s[ordinal]
            if x.mnemonic=='jmp' and x.op_str=='0x52cb4f':
                need(y.mnemonic=='jmp' and y.size==x.size==5 and y.op_str==hex(ret-4),
                     'original case whole-parent end JMP must remain true direct epilogue')
        if action==0x62:
            need([n[j].op_str for j in (47,54,61)]==['0x5f','0x5d','0x5e'],
                 'true original 0x62 selector action IDs 5F/5D/5E changed')
            need([s[j].op_str for j in (47,54,61)]==['0x5f','0x5d','0x5e'],
                 'new source must preserve exact original action selection')
        cases[hex(action)]={'native_bytes':size,'native_x86':nx,
                           'physical_native_PE_fields':physical,
                           'real_unmasked_nonfield_difference_offsets':bad,
                           'formal_callable_exact_credit_B':0}
    native=rd.pe_bytes_at(pe,SUFFIX,46)
    output=code[ret-46:ret]
    native_ins=list(d.disasm(native,SUFFIX))
    source_ins=list(d.disasm(output,ret-46))
    need(len(native_ins)==len(source_ins)==16 and all(a.mnemonic==b.mnemonic and a.size==b.size
         for a,b in zip(native_ins,source_ins)),'default tail 46B/16-x86 native structure altered')
    fields=[r for r in refs if ret-46<=r['offset']<ret]
    need(len(fields)==3,'real original shared tail three PE calls lost')
    mask=set()
    for r in fields:
        off=r['offset']-(ret-46)
        real=SUFFIX+off+4+int.from_bytes(native[off:off+4],'little',signed=True)
        need(r['type']=='REL32' and r['addend']==0 and r['local_symbol_offset'] is None
             and real=={4:0x40FA30,28:0x40FAC0,38:0x40FA30}[off]
             and f'At{real:06X}' in r['symbol'],
             'tail actual native PE call field location/target changed')
        mask.update(range(off,off+4))
    wrong=[j for j in range(46) if j not in mask and native[j]!=output[j]]
    need(wrong==[10,12,16,19] and
         all(native[i]==output[i] for i in (2,13,26,36)),
         'adding real 0x62 source should shift four honest GPR operand bytes but retain original EBP-0x10')
    results={'physical_original_whole_game':'0x005214B0',
        'original_complete_native_callable_CODE_B':46755,
        'new_source_whole_callable_CODE_B':ret,
        'source_whole_x86':len(ins),
        'new_original_0x62_case_bytes_x86_refs':'249B/65 x86/4 true PE fields',
        'all_0x5F_0x60_0x61_0x62_complete_native_physical_cases':cases,
        'actual_original_afterRET_separate_DATA_B':901,
        'original_saved_this_EBP_0x10_preserved':True,
        'original_46B_shared_tail_x86':16,
        'original_46B_shared_tail_real_nonfield_GPR_diffs':wrong,
        'entire_game_boss_byte_exact':False,
        'new_authored_callable_exact_CODE_B':0,
        'no_all_units_cold_replay':True}
    (OUT/'verified-summary.json').write_text(json.dumps(results,indent=2)+chr(10))
    print('F817 native scripted 005214B0 case0x62 original 249B/65-x86/4 physical PE calls added in same 11785B whole source. Original saved this EBP-0x10 and previous 5F/60/61 PE-backed source retained, 901B switch DATA unchanged. Genuine case62 GPR phase rotates later 46B tail four nonrelocation register operand bytes; full 46755B giant still nonexact; no callable exact credit.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F817 original native whole parent 0x62 source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
