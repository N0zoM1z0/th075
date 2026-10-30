#!/usr/bin/env python3
"""F819: complete genuine native mode0x63 in selected 46KB fighter parent.

Rebuild F817 affected parent first, then reconstruct original 417B/109-x86
case0x63 via tracked F626 source in the same full C++ function. Strictly
recheck previous 30 actions + 901B DATA using F617, and actual 5F-62
with their authentic native PE fields. The F626 earlier short-parent
zero GPR-mismatch result is NOT transferable to this longer parent:
2 real instruction-width differences and 143 unmasked bytes in 0x63.
Whole game giant not exact; no independent case credit or mass cold replay.
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
OUT=ROOT/'.analysis/f819-scripted-mode63'
TARGET=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
OLD_CASES={
  0x5f:(21,0x00523680,144,44,3,[140,141]),
  0x60:(22,0x00523710,586,169,11,[395,396,582,583]),
  0x61:(23,0x0052395A,586,169,11,[395,396,582,583]),
  0x62:(24,0x00523BA4,249,65,4,
        [172,174,178,181,195,199,205,220,224,230,245,246]),
}

def need(ok,msg):
    if not ok:raise ValueError(msg)

def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/'scripts'/path)
    need(sp is not None and sp.loader is not None,'missing pinned original PE checker '+path)
    mod=importlib.util.module_from_spec(sp)
    sys.modules[tag]=mod
    sp.loader.exec_module(mod)
    return mod

def reconstruct_source():
    OUT.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(ROOT/'scripts/repo-python'),
       str(ROOT/'scripts/verify-scripted-fighter-resource-selector-f817.py')],
       cwd=ROOT,capture_output=True,text=True,timeout=750)
    (OUT/'f817-prior-targeted-whole.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,
         'previous live selected original 5F-62 parent did not verify '+
         (run.stdout+run.stderr)[-800:])
    s=(ROOT/'.analysis/f817-scripted-selector/Boss005214B0-case62-resource-selector.cpp').read_text()
    mark='        case 0x63: g_FighterProbeMarker = 100; break;'
    decl='extern float g_ThresholdAt0065782C;'
    inc=(ROOT/'probes/FighterMode63BasicF626.inc').read_text()
    need(s.count(mark)==s.count(decl)==1 and inc.count('case 0x63:')==1
         and inc.count('SetNativeActionAt40FAC0(0x31C)')==2,
         'real actor-specific mode63 source/original source marker changed')
    return s.replace(decl,'extern signed char g_ModeAt006714B4;\n'+decl,1).replace(
        mark,'#include "FighterMode63BasicF626.inc"',1)

def build(src):
    cpp=OUT/'Boss005214B0-F819-whole.cpp'
    obj=OUT/'Boss005214B0-F819-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=ROOT,env=env,capture_output=True,text=True,timeout=260)
    (OUT/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'entire F819 original-shaped source failed '+(run.stdout+run.stderr)[-850:])
    return obj

def main():
    f={k:load('f819_'+k,v) for k,v in {
      'reader':'compare-coff-function.py',
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
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==TARGET)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'genuine original fighter whole target changed')
    report,mapped=f['actions'].report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapped}
    native63,meta=f['f626'].original_case(rd,pe,d,boss,by)
    need(meta['native_whole_inner_CODE_bytes']==417 and
         meta['native_complete_x86_instructions']==109 and
         meta['real_original_typed_fields']==7,
         'native complete last indexed action changed')
    obj=build(reconstruct_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(code)-ret,len(refs))==(12187,3176,901,589)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'original-mode parent native source assembly/EBP frame changed')
    props={a:f['f617'].native_case(rd,pe,d,boss,by,a) for a in (0x5d,0x5e)}
    early=f['f617'].verify_source(rd,pe,d,*(f[k] for k in (
        'f598','f600','f602','f603','f605','f606','f607',
        'f608','f610','f611','f613','f614','core','zero','switch')),
        boss,report,mapped,code,refs,props,True)
    need(early['all_previous_30_native_game_cases_source_retained']
         and early['source_5D_native_GPR_CFG_role_mismatches']==61
         and early['source_5E_native_GPR_CFG_role_mismatches']==61,
         'genuine previous 30 game cases or 901B packed table unverified')
    table=boss['tables'][1]
    sparse=rd.pe_bytes_at(pe,table['map_addr'],table['map_length'])
    old={}
    for act,(slot,addr,size,nx,nfields,expected_wrong) in OLD_CASES.items():
        need(sparse[act-0x33]==slot,'native packed action slot shifted '+hex(act))
        lo,hi=[next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+4*k)
               for k in (slot,slot+1)]
        actual=rd.pe_bytes_at(pe,addr,size);source=code[lo:hi]
        na=list(d.disasm(actual,addr));sa=list(d.disasm(source,lo))
        need(hi-lo==size and len(na)==len(sa)==nx and
             all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(na,sa)),
             'prior 5F-62 complete original opcode geometry changed '+hex(act))
        fields=[r for r in refs if lo<=r['offset']<hi]
        need(len(fields)==nfields,'previous actual native PE fields lost '+hex(act))
        mask=set()
        for r in fields:
            k=r['offset']-lo
            x=int.from_bytes(actual[k:k+4],'little') if r['type']=='DIR32' else (
                addr+k+4+int.from_bytes(actual[k:k+4],'little',signed=True))
            hit=re.search(r'At([0-9a-fA-F]{6,8})',r['symbol'])
            wanted=int(hit.group(1),16) if hit else None
            need(wanted is not None and x==wanted and r['addend']==0
                 and r['local_symbol_offset'] is None and r['type'] in ('REL32','DIR32'),
                 'prior original physical PE destination not preserved')
            mask.update(range(k,k+4))
        bad=[j for j in range(size) if j not in mask and actual[j]!=source[j]]
        need(bad==expected_wrong,
             'real earlier 5F-62 nonrelocation machine source changed '+hex(act))
        old[hex(act)]={'native_whole_case_CODE_B':size,
                      'native_x86':nx,'verified_original_COFF_fields':nfields,
                      'true_nonrelocation_wrong_bytes':bad}
    # Native last packed index 25, source next literal action 8C has
    # a genuine COFF reference to its diagnostic marker, not a
    # source-generated case 0x63 sample code truncation.
    need(sparse[0x63-0x33]==25 and by[0x63]==0x00523C9D
         and by[0x8c]==0x00523E3E,
         'physical last indexed source case0x63/8C original boundary shifted')
    srclo=next(r['local_symbol_offset'] for r in refs if r['offset']==ret+44+25*4)
    after=[r for r in refs if r['offset']>srclo and 'g_FighterProbeMarker' in r['symbol']]
    need(after,'actual following source case 0x8C COFF marker missing')
    first=min(after,key=lambda r:r['offset'])
    marker=next(x for x in ins if x.address<=first['offset']<x.address+x.size)
    need(marker.mnemonic=='mov' and marker.op_str.endswith(', 0x8d'),
         'physical source next case 0x8C literal not identifiable')
    srchi=marker.address
    source_ins=list(d.disasm(code[srclo:srchi],srclo))
    need(srchi-srclo==417 and len(source_ins)==len(native63)==109
         and all(a.mnemonic==b.mnemonic for a,b in zip(native63,source_ins)),
         'new 0x63 source entire real native x86 structure lost')
    widths=[j for j,(a,b) in enumerate(zip(native63,source_ins)) if a.size!=b.size]
    need(widths==[38,61],'real VC7.1 longer-parent 0x63 register-width negatives changed')
    real_pe=rd.pe_bytes_at(pe,by[0x63],417)
    fields=[r for r in refs if srclo<=r['offset']<srchi]
    need(len(fields)==7,'native original seven mode63 typed fields missing')
    mask=set()
    for ordinal,(target,mn,source_symbol) in f['f626'].FIELDS.items():
        orig,gen=native63[ordinal],source_ins[ordinal]
        need(orig.mnemonic==gen.mnemonic==mn and
             (orig.op_str.endswith('byte ptr [0x6714b4]') if ordinal==0
              else orig.op_str=='0x'+format(target,'x')),
             'original independently observed native mode63 target/call ordinal changed')
        inside=[r for r in fields if gen.address<=r['offset']<gen.address+gen.size]
        need(len(inside)==1,'source relocation left actual original native instruction '+str(ordinal))
        r=inside[0]
        need(r['type']==('DIR32' if ordinal==0 else 'REL32')
             and r['addend']==0 and r['local_symbol_offset'] is None
             and source_symbol in r['symbol'],
             'true original typed PE/COFF symbol mismatch '+str(r))
        k=r['offset']-srclo
        mask.update(range(k,k+4))
    wrong=[j for j in range(417) if j not in mask and real_pe[j]!=code[srclo+j]]
    need(len(wrong)==143,
         'actual 0x63 source mismatch count changed; re-audit full native PE '+str(len(wrong)))
    original_tail=rd.pe_bytes_at(pe,0x52CB25,46)
    tailmask={j for r in refs if ret-46<=r['offset']<ret
              for j in range(r['offset']-(ret-46),r['offset']-(ret-46)+4)}
    tailbad=[j for j in range(46) if j not in tailmask
             and original_tail[j]!=code[ret-46+j]]
    need(tailbad==[10,12,16,19],'real original 46B default GPR role negative changed')
    summary={'original_whole_fighter':'0x005214B0',
       'real_original_complete_callable_CODE_B':46755,
       'new_generated_parent_callable_CODE_B':ret,
       'new_original_action':'0x63',
       'new_native_complete_inner_CODE_B':417,'new_native_complete_x86':109,
       'original_typed_COFF_fields_in_new_case':7,
       'native_complete_source_opcode_width_differences':widths,
       'real_unmasked_original_0x63_wrong_byte_count':len(wrong),
       'real_unmasked_original_0x63_wrong_byte_offsets_first':wrong[:24],
       'earlier_original_5F_60_61_62_source_persist':old,
       'original_901B_packed_switch_DATA_reverified':True,
       'original_saved_this_EBP_0x10_persist':True,
       'default_46B_native_real_GPR_wrong_byte_positions':tailbad,
       'original_whole_game_exact':False,
       'new_whole_authored_exact_CODE_B':0,'mass_cold_replay_run':False}
    (OUT/'verified-summary.json').write_text(json.dumps(summary,indent=2)+chr(10))
    print('F819 selected original 46KB fighter: new mode0x63 native 417B/109-x86/7 original PE fields integrated in 12187B whole parent. Earlier game cases and 901B jump DATA verified. Real 0x63 context has 2 native width and 143 unmasked byte negatives; no false inherited F626 short-parent exactness, default four GPR bytes still wrong. Whole boss NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as exc:
        print('F819 selected whole native 0x63 fighter FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
