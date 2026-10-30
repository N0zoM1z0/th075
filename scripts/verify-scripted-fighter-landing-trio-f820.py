#!/usr/bin/env python3
"""F820: genuine 8C/8F/90 original landings in WHOLE scripted 46KB fighter.

Selected F628 native source: three full 289B/80-x86 cases, 8 real
PE/COFF fields each. Rebuild F819 first, keep the genuine 0x63
source and all earlier selected cases, and compile the whole updated
parent. F628 shorter-parent 0 GPR mismatch label is NOT valid here:
55 native nonrelocation bytes differ per landing in this larger source.
No whole-game or case-fragment exact CODE, no accepted-unit cold replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import re
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f820-scripted-landings'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ACTIONS=(0x8c,0x8f,0x90)
OLD={0x5f:(21,0x523680,144,44,3,[140,141]),
     0x60:(22,0x523710,586,169,11,[395,396,582,583]),
     0x61:(23,0x52395a,586,169,11,[395,396,582,583]),
     0x62:(24,0x523ba4,249,65,4,
           [172,174,178,181,195,199,205,220,224,230,245,246])}

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(tag,file):
    spec=importlib.util.spec_from_file_location(tag,ROOT/'scripts'/file)
    need(spec is not None and spec.loader is not None,'native PE helper missing '+file)
    mod=importlib.util.module_from_spec(spec)
    sys.modules[tag]=mod;spec.loader.exec_module(mod)
    return mod

def selected_source(meta):
    OUT.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(ROOT/'scripts/repo-python'),
       str(ROOT/'scripts/verify-scripted-fighter-mode63-context-f819.py')],
       cwd=ROOT,capture_output=True,text=True,timeout=800)
    (OUT/'f819-prior-source-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'previous 36-case original source failed physical PE check '+
         (run.stdout+run.stderr)[-850:])
    src=(ROOT/'.analysis/f819-scripted-mode63/Boss005214B0-F819-whole.cpp').read_text()
    inc=(ROOT/'probes/FighterScriptedJumpLandingF820.inc').read_text()
    need('case F628_CASE:' in inc and 'return;' in inc
         and 'g_JumpGroundCorrectionAt00658058' in inc
         and 'g_JumpReflectionAt006583E8' in inc,
         'original source normal C++ landing direct exit changed')
    src=('extern float g_JumpGroundCorrectionAt00658058;\n'
         'extern double g_JumpReflectionAt006583E8;\n'+src)
    for action in ACTIONS:
        old=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(old)==1,'selected next source action marker missing '+hex(action))
        info=meta[action][1]
        value=struct.unpack('<f',struct.pack('<I',info['original_start_float_bits']))[0]
        need(value in (-11.0,-12.0) and info['original_counter_offset']==0xf00,
             'actual original F628 owner ground start or counter differs')
        defs={'F628_CASE':f'0x{action:X}',
              'F628_COUNTER':'0xF00',
              'F628_START_POS':repr(value)+'f',
              'F628_LIMIT':str(info['original_native_stage_counter_limit'])}
        text='\n'.join('#define '+k+' '+v for k,v in defs.items())
        text+='\n#include "FighterScriptedJumpLandingF820.inc"\n'
        text+='\n'.join('#undef '+k for k in defs)
        src=src.replace(old,text,1)
    need(src.count('#include "FighterScriptedJumpLandingF820.inc"')==3,
         'must add all three original native 80-x86 action sources')
    return src

def compile_source(src):
    cpp=OUT/'Boss005214B0-F820-whole.cpp'
    obj=OUT/'Boss005214B0-F820-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=ROOT,env=env,text=True,capture_output=True,timeout=275)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'fresh F820 complete selected source fails '+(cp.stdout+cp.stderr)[-800:])
    return obj

def physical_fields(rd,original,start,relocs,source_lo,expected):
    need(len(relocs)==expected,'typed PE original field count wrong')
    mask=set()
    for r in relocs:
        offset=r['offset']-source_lo
        need(r['type'] in ('DIR32','REL32') and r['local_symbol_offset'] is None
             and r['addend']==0 and 0<=offset<=len(original)-4,
             'invalid original zero-addend COFF reference '+str(r))
        actual=(int.from_bytes(original[offset:offset+4],'little')
                if r['type']=='DIR32' else
                start+offset+4+int.from_bytes(original[offset:offset+4],'little',signed=True))
        m=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
        expect=(int(m.group(1),16) if m else
                0x006406AC if r['symbol']=='__ftol2' else None)
        need(expect is not None and actual==expect,'original PE destination does not equal source symbol '+str(r))
        mask.update(range(offset,offset+4))
    return mask

def main():
    f={k:load('f820_'+k,v) for k,v in {
      'reader':'compare-coff-function.py',
      'f628':'verify-fighter-jump-landings-f628.py',
      'f626':'verify-fighter-mode63-basic-f626.py',
      'f617':'verify-fighter-air-transition-f617.py',
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
    rd=f['reader'];pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original entire giant/source DATA identity changed')
    report,mapped=f['actions'].report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    cases={action:f['f628'].native_case(rd,pe,d,boss,by,action) for action in ACTIONS}
    obj=compile_source(selected_source(cases))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret,len(refs))==(13009,3410,901,610)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'three new original game cases unexpected normal compiler source geometry')
    props={a:f['f617'].native_case(rd,pe,d,boss,by,a) for a in (0x5d,0x5e)}
    prior=f['f617'].verify_source(rd,pe,d,*(f[k] for k in (
       'f598','f600','f602','f603','f605','f606','f607','f608','f610',
       'f611','f613','f614','core','zero','switch')),
       boss,report,mapped,code,refs,props,True)
    need(prior['all_previous_30_native_game_cases_source_retained']
         and prior['source_5D_native_GPR_CFG_role_mismatches']==61
         and prior['source_5E_native_GPR_CFG_role_mismatches']==61,
         'F820 new whole source lost previous real cases or original 901B DATA')
    tab=boss['tables'][1]
    for action,(slot,start,size,nx,nfields,wrongexpected) in OLD.items():
        lo,hi=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*j)
               for j in (slot,slot+1)]
        original=rd.pe_bytes_at(pe,start,size)
        own=code[lo:hi]
        real=list(d.disasm(original,start))
        source=list(d.disasm(own,lo))
        need(hi-lo==size and len(real)==len(source)==nx
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(real,source)),
             'preceding native 5F-62 complete game case geometry shifted '+hex(action))
        physical=[r for r in refs if lo<=r['offset']<hi]
        mask=physical_fields(rd,original,start,physical,lo,nfields)
        actualwrong=[j for j in range(size) if j not in mask and original[j]!=own[j]]
        need(actualwrong==wrongexpected,'previous PE-backed 5F-62 original bytes newly shifted '+str(actualwrong))
    native63,info63=f['f626'].original_case(rd,pe,d,boss,by)
    src63=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+25*4)
    # Following game case0x91 has a unique original diagnostic marker;
    # original 8C/8F/90 are exactly the 240 x86 instructions before it.
    markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov' and
             x.op_str.endswith(', 0x92') and
             any('g_FighterProbeMarker' in r['symbol'] and
                 x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1 and markers[0]>=240,'actual next source 0x91 case marker not unique')
    triple=ins[markers[0]-240:markers[0]]
    need(len(triple)==240 and triple[0].address>src63,
         'actual original 8C/8F/90 contiguous complete C++ group missing')
    preceding=code[src63:triple[0].address]
    generated63=list(d.disasm(preceding,src63))
    need(len(preceding)==417 and len(generated63)==109 and
         len(native63)==109 and all(a.mnemonic==b.mnemonic
             for a,b in zip(native63,generated63))
         and [j for j,(a,b) in enumerate(zip(native63,generated63)) if a.size!=b.size]==[38,61],
         'earlier original real 0x63 context/width negative changed')
    rel63=[r for r in refs if src63<=r['offset']<triple[0].address]
    need(len(rel63)==7,'previous whole original mode0x63 typed PE fields lost')
    physical63=rd.pe_bytes_at(pe,by[0x63],417)
    native_mask=set()
    source_mask=set()
    field_shifts={}
    # TWO distinct native/source register-width positions make one
    # source relocation MOVE by -1. The original PE target must be
    # independently verified at the ORIGINAL field position, not
    # reconstructed by masking the shifted compiler source field.
    for ordinal,(target,mn,symbol) in f['f626'].FIELDS.items():
        native,source=native63[ordinal],generated63[ordinal]
        need(native.mnemonic==source.mnemonic==mn,
             'native original mode63 source call/global ordinal changed')
        source_ref=[r for r in rel63
                    if source.address<=r['offset']<source.address+source.size]
        need(len(source_ref)==1,'genuine mode63 source relocation missing at original x86 ordinal')
        r=source_ref[0]
        native_byte=native.address-by[0x63]+native.size-4
        source_byte=r['offset']-src63
        actual=(int.from_bytes(physical63[native_byte:native_byte+4],'little')
                if ordinal==0 else
                by[0x63]+native_byte+4+
                int.from_bytes(physical63[native_byte:native_byte+4],'little',signed=True))
        need(actual==target and
             r['type']==('DIR32' if ordinal==0 else 'REL32')
             and r['addend']==0 and r['local_symbol_offset'] is None
             and symbol in r['symbol'],
             'true ORIGINAL mode63 native PE relocation and source symbol disagree')
        field_shifts[str(ordinal)]=source_byte-native_byte
        native_mask.update(range(native_byte,native_byte+4))
        source_mask.update(range(source_byte,source_byte+4))
    need(field_shifts=={'0':0,'22':0,'48':-1,'71':0,'94':0,'99':0,'107':0},
         'source mode63 physical relocation shift drifted')
    diagnostic_wrong=[j for j in range(417) if j not in source_mask
                      and physical63[j]!=preceding[j]]
    safe_union=native_mask|source_mask
    conservative_wrong=[j for j in range(417) if j not in safe_union
                        and physical63[j]!=preceding[j]]
    need(len(diagnostic_wrong)==143
         and len(safe_union)==29 and len(conservative_wrong)>0,
         'F819 source-COFF-only masked 143-byte negative or field shift changed')
    results=[]
    for idx,action in enumerate(ACTIONS):
        real,meta=cases[action]
        gen=triple[idx*80:(idx+1)*80]
        lo,hi=gen[0].address,gen[-1].address+gen[-1].size
        need(len(gen)==len(real)==80 and hi-lo==meta['original_complete_case_CODE_bytes']==289
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(real,gen)),
             'new action native x87/GPR opcode geometry differs '+hex(action))
        original=rd.pe_bytes_at(pe,by[action],289)
        fields=[r for r in refs if lo<=r['offset']<hi]
        mask=physical_fields(rd,original,by[action],fields,lo,8)
        for ordinal,(want,mn,symbol) in f['f628'].FIELDS.items():
            a,b=real[ordinal],gen[ordinal]
            matching=[r for r in fields if b.address<=r['offset']<b.address+b.size]
            need(a.mnemonic==b.mnemonic==mn and len(matching)==1
                 and symbol in matching[0]['symbol'],
                 'original 8C-90 typed physical PE instruction position changed '+hex(action))
        bad=[j for j in range(289) if j not in mask and original[j]!=code[lo+j]]
        need(len(bad)==55,'older F628 strict register agreement does NOT hold in current whole parent '+str((action,len(bad))))
        need(real[-1].mnemonic==gen[-1].mnemonic=='jmp'
             and real[-1].op_str=='0x52cb4f' and gen[-1].op_str==hex(ret-4),
             'original face landing exits must go directly to game epilogue')
        results.append({'native_original_action':hex(action),
            'native_complete_inner_CODE_B':289,'source_inner_CODE_B':289,
            'original_x86':80,'physically_attested_native_PE_fields':8,
            'true_nonrelocation_wrong_B':55,
            'native_source_instruction_mnemonics_widths_equal':True,
            'independently_accepted_callable_CODE_B':0})
    n_tail=rd.pe_bytes_at(pe,0x52CB25,46)
    srctail=code[ret-46:ret]
    tfields=[r for r in refs if ret-46<=r['offset']<ret]
    mask=physical_fields(rd,n_tail,0x52CB25,tfields,ret-46,3)
    need(len(mask)==12 and [j for j in range(46) if j not in mask and n_tail[j]!=srctail[j]]==[10,12,16,19],
         'selected updated whole native default register phase physically changed')
    summary={'original_whole_giant':'0x005214B0',
        'native_whole_callable_CODE_B':46755,
        'new_source_callable_CODE_B':ret,
        'original_new_landing_cases':results,
        'native_real_new_case_PE_fields_total':24,
        'original_mode63_native_vs_compiler_COFF_field_offset_shifts_by_ordinal':field_shifts,
        'prior_mode63_diagnostic_compiler_mask_wrong_B':len(diagnostic_wrong),
        'prior_mode63_safe_union_mask_comparable_B':417-len(safe_union),
        'prior_mode63_safe_union_mask_wrong_B':len(conservative_wrong),
        'native_case63_previous_two_widths_still_wrong':[38,61],
        'all_selected_earlier_cases_and_afterRET_DATA_rechecked':True,
        'native_afterRET_dispatch_DATA_B':901,
        'native_default_actual_GPR_nonfield_wrong_offsets':[10,12,16,19],
        'whole_native_game_boss_exact':False,'new_accepted_whole_callable_CODE_B':0,
        'all_accepted_units_cold_replay_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(summary,indent=2)+chr(10))
    print('F820 original 005214B0 landing trio 8C/8F/90: 3 complete 289B/80-x86/8-native-PE-field game actions in a NEW 13009B/3410-x86 whole source, 901B original DATA and preceding 0x63/5F-62 checked. All 24 original PE destinations real, but current parent has 55 genuine nonrelocation byte negatives PER case, unlike earlier shorter F628. Full 46755B giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as ex:
        print('F820 true original 46KB landed fighter whole source FAILED:',ex,file=sys.stderr)
        raise SystemExit(1)
