#!/usr/bin/env python3
"""F832: genuine original D1/D2 resource shots in selected 46KB fighter.

Rebuild selected F831 whole original-shaped VC7.1 source; add both
genuine normal C++ source cases with actor-specific signed short
resource DECAY 6 and PRE-spawn scaling in D2 (not another actor's
historical decay 3 / post-spawn order). Verify 199B/59-x86/8-field
D1 and 251B/74-x86/10-field D2 with original physical PE targets.
Recheck full preceding CF/D0, 901B afterRET table and 46B common
tail. Actual GPR source differences are not masked, no split-case
or complete original function exact credit, no mass cold replay.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f832-scripted-resource-shots'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ACTIONS=(0xd1,0xd2)
# The F651 source owner is a DIFFERENT fighter. Its D2 original
# x86 ordinals for spawn/preparation and scaling are not applicable
# here, despite equal complete 251B/74-x86 case geometry. These
# actor-specific physical original D2 ordinals are independently
# verified against the pinned target PE and real COFF field symbols.
D2_PHYSICAL_FIELDS={
    6:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
    23:(0x00657F74,'fmul','g_BounceScaleAt00657F74'),
    28:(0x00657F74,'fmul','g_BounceScaleAt00657F74'),
    33:(0x00453D60,'call','PrepareActionAt453D60'),
    40:(0x00657888,'fadd','g_ContactProjectionAt00657888'),
    48:(0x00453A70,'call','SpawnWithFloatAt453A70'),
    51:(0x00657F74,'fmul','g_BounceScaleAt00657F74'),
    57:(0x0040FA30,'call','GetNativeActionAt40FA30'),
    68:(0x0040FB40,'call','SetAuxActionAt40FB40'),
    72:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
}
OLD={0xcf:(30,114,4,20),0xd0:(60,195,6,39)}

def need(x,msg):
    if not x:raise ValueError(msg)

def load(tag,f):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'true original PE/source reader missing '+f)
    m=importlib.util.module_from_spec(sp)
    sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def make_source():
    O.mkdir(parents=True,exist_ok=True)
    p=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-fall-cf-f831.py')],
             cwd=R,capture_output=True,text=True,timeout=1250)
    (O/'f831-prior-physical-original.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'selected prior CF/D0 original source/PE not reverified '+
         (p.stdout+p.stderr)[-840:])
    src=(R/'.analysis/f831-scripted-cf/Boss005214B0-F831-whole.cpp').read_text()
    old='void SpawnDirectedAt453A70(int,int,int,char,int);'
    need(src.count(old)==1,'actual original native sprite method declaration changed')
    src=src.replace(old,old+' void SpawnWithFloatAt453A70(int,int,float,char,int);',1)
    for action,frag,params in (
        (0xd1,'FighterScriptedResourceShotD1F832.inc',
            {'F651_DECAY':'6','F651_SPRITE':'0x3E6'}),
        (0xd2,'FighterScriptedResourceShotD2F832.inc',
            {'F652_DECAY':'6','F652_SPRITE':'0x3E6','F652_SCALE_BEFORE':'1'})):
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        inc=(R/'probes'/frag).read_text()
        need(src.count(marker)==1 and inc.count(f'case 0x{action:X}:')==1
             and inc.count('return;')==2 and inc.count('SpawnWithFloatAt453A70')==1,
             'actor native 0xD1/0xD2 authentic game/source changed')
        block='\n'.join('#define '+k+' '+v for k,v in params.items())
        block+='\n#include "'+frag+'"\n'
        block+='\n'.join('#undef '+k for k in params)
        src=src.replace(marker,block,1)
    return src

def build(src):
    cpp=O/'Boss005214B0-F832-whole.cpp'
    obj=O/'Boss005214B0-F832-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=env,capture_output=True,text=True,timeout=280)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'full original-shaped D1/D2 VC7.1 compiler failed '+(p.stdout+p.stderr)[-820:])
    return obj

def main():
    rd=load('f832_reader','compare-coff-function.py')
    ac=load('f832_actions','report-fighter-action-handlers.py')
    f651=load('f832_f651','verify-fighter-resource-shots-f651.py')
    f646=load('f832_f646','verify-fighter-fall-reflect-f646.py')
    f820=load('f832_f820','verify-scripted-fighter-landing-trio-f820.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original 46KB fighter or separately owned table changed')
    _,mp=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mp}
    obj=build(make_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(18375,4917,784,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'real new source full native CODE/x86/COFF/EBP frame geometry changed')
    marks=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0x12d')
          and any('g_FighterProbeMarker' in r['symbol']
                    and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=133+90,
         'original following 0x12C physical marker not unique')
    index=marks[0]
    candidates=ins[index-133:index]
    rows=[]
    for action,start,end,offset,count,nfields,wrong in (
       (0xd1,by[0xd1],by[0xd2],0,59,8,32),
       (0xd2,by[0xd2],by[0x12c],59,74,10,46)):
        raw=rd.pe_bytes_at(pe,start,end-start)
        orig=list(d.disasm(raw,start))
        src=candidates[offset:offset+count]
        lo,hi=src[0].address,src[-1].address+src[-1].size
        need(hi-lo==len(raw)==(199 if action==0xd1 else 251)
             and len(orig)==len(src)==count
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(orig,src)),
             'actor original resource D1/D2 complete x86 instruction sequence incorrect')
        physical=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,start,physical,lo,nfields)
        expected_fields=(f651.FIELDS[0xd1] if action==0xd1
                         else D2_PHYSICAL_FIELDS)
        need(len(expected_fields)==nfields,
             'actor-specific physical original native fields count differs')
        for ordinal,(target,mn,sym) in expected_fields.items():
            a,b=orig[ordinal],src[ordinal]
            field=[r for r in physical if b.address<=r['offset']<b.address+b.size]
            need(a.mnemonic==b.mnemonic==mn and len(field)==1
                 and sym in field[0]['symbol']
                 and field[0]['offset']-lo==a.address-start+a.size-4
                 and a.op_str==(f'0x{target:x}' if mn=='call'
                                   else f'dword ptr [0x{target:x}]'),
                 'selected actor D1/D2 original native PE field ordinal/target differs')
        bad=[j for j in range(len(raw)) if j not in mask and raw[j]!=code[lo+j]]
        need(len(bad)==wrong and bad[-2:]==[
               (195 if action==0xd1 else 247),
               (196 if action==0xd1 else 248)],
             'native D1/D2 genuine GPR and original long-parent JMP byte negatives differ '+str((action,bad)))
        need(orig[-1].mnemonic==src[-1].mnemonic=='jmp'
             and orig[-1].op_str=='0x52cb4f'
             and src[-1].op_str==hex(ret-4),
             'D1/D2 natural return does not target enclosing original function epilogue')
        # Real resource decay 6 and native original D2 float order:
        # F651 historical other actor uses 3 and D2 scale-after.
        need(orig[10].mnemonic==src[10].mnemonic=='sub'
             and orig[10].op_str.endswith(', 6') and src[10].op_str.endswith(', 6'),
             'actual original signed resource decrement is not 6')
        if action==0xd2:
            need(orig[22].mnemonic==src[22].mnemonic=='fld'
                 and orig[23].mnemonic==src[23].mnemonic=='fmul'
                 and orig[27].mnemonic==src[27].mnemonic=='fld'
                 and orig[28].mnemonic==src[28].mnemonic=='fmul'
                 and orig[31].mnemonic==src[31].mnemonic=='push'
                 and orig[33].mnemonic==src[33].mnemonic=='call'
                 and orig[40].mnemonic==src[40].mnemonic=='fadd'
                 and orig[48].mnemonic==src[48].mnemonic=='call',
                 'native D2 original MUST scale position before sprite emission')
        rows.append({'action':hex(action),'native_original_complete_inner_B':len(raw),
             'original_x86':count,'original_physical_typed_PE_fields':nfields,
             'real_original_nonrelocation_wrong_byte_count':len(bad),
             'real_wrong_offsets':bad,
             'complete_original_native_case_exact':False})
    # Physically reverify preceding original CF and D0 source in
    # THIS newly generated whole fighter parent. Their natural
    # register phase is non-native and not masked.
    source_old=ins[index-133-90:index-133]
    rows_old=[]
    for action,ordinal,(nx,nb,nfields,nwrong) in (
        (0xcf,0,OLD[0xcf]),(0xd0,30,OLD[0xd0])):
        real=f646.native_case(rd,pe,d,boss,by,action)[0] if action==0xd0 else list(
            d.disasm(rd.pe_bytes_at(pe,by[action],by[action+1]-by[action]),by[action]))
        src=source_old[ordinal:ordinal+nx]
        lo,hi=src[0].address,src[-1].address+src[-1].size
        raw=rd.pe_bytes_at(pe,by[action],nb)
        need(hi-lo==nb and len(real)==len(src)==nx
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(real,src)),
             'prior original CF/D0 whole source x86 opcode/width changed')
        f=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,by[action],f,lo,nfields)
        diff=[j for j in range(nb) if j not in mask and raw[j]!=code[lo+j]]
        need(len(diff)==nwrong,'genuine earlier CF/D0 original nonrelocation bytes changed')
        rows_old.append({'action':hex(action),'original_B':nb,'native_x86':nx,
                         'PE_fields':nfields,'real_nonfield_wrong_B':len(diff)})
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    f=[r for r in refs if ret-46<=r['offset']<ret]
    mask=f820.physical_fields(rd,tail,0x52cb25,f,ret-46,3)
    wrong=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong==[10,12,16,19],
         'whole source new original default GPR phase differs from real native evidence')
    out={'original_whole_game_function':'0x005214B0',
        'native_whole_original_callable_CODE_B':46755,
        'current_source_whole_callable_CODE_B':ret,
        'real_original_D1_D2_full_cases':rows,
        'physically_rechecked_previous_CF_D0_cases':rows_old,
        'new_original_inner_CODE_B':450,
        'new_original_x86':133,'new_real_PE_fields':18,
        'actor_specific_original_resource_decay':6,
        'actor_specific_D2_native_scale_before_sprite':True,
        'native_46B_default_actual_GPR_wrong_offsets':wrong,
        'native_separate_afterRET_packed_DATA_B':901,
        'original_whole_game_function_exact':False,
        'new_accepted_callable_whole_CODE_B':0,
        'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F832 selected original D1/D2 199B/59x86/8PE +251B/74x86/10PE in one fresh 18,375B/4,917-x86 whole source. Native signed decay 6 and D2 pre-spawn scale proven, 18 physical PE fields. CF and D0 PE source rechecked; source GPR negatives 32/46 bytes plus 4 common fallback GPR wrong. Giant 46,755B remains NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F832 original 005214B0 resource-shot PE/source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
