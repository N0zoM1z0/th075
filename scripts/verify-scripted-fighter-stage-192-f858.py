#!/usr/bin/env python3
"""F858: physical native 192 stage4 sprite, all six real PE calls in full fighter.

The current actor original state0x192 is 217B/64x86/6 call fields,
distinct from F856 sibling190 in action2, stage4 and float3.0.
Rebuild F857 before compiling ONE normal VC7.1 whole fighter.
All 29 preceding source-backed case interiors, five 901B original
packed afterRET tables, original 46B getter and honest true GPR
and enclosing-parent JMP mismatch bytes are independently rechecked.
No separate inner-case exact CODE adoption.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f858-scripted-stage192'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0

def need(x,msg):
    if not x:raise ValueError(msg)

def ld(tag,filename):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(spec is not None and spec.loader is not None,'missing original PE reader '+filename)
    module=importlib.util.module_from_spec(spec);sys.modules[tag]=module;spec.loader.exec_module(module)
    return module

def source(original,by):
    O.mkdir(parents=True,exist_ok=True)
    prior=subprocess.run([str(R/'scripts/repo-python'),
         str(R/'scripts/verify-scripted-fighter-floatshot-191-f857.py')],
         cwd=R,capture_output=True,text=True,timeout=1300)
    (O/'f857-prior-native.log').write_text(prior.stdout+prior.stderr)
    need(prior.returncode==0,'prior original F857 whole fighter PE failed '+(prior.stdout+prior.stderr)[-760:])
    native=list(original)
    need(len(native)==64
         and native[21].mnemonic=='push' and native[21].op_str=='2'
         and native[26].mnemonic=='cmp' and native[26].op_str.endswith(', 4')
         and native[33].op_str.endswith(', 0x40400000')
         and native[44].op_str=='0x320'
         and native[47].op_str=='0xfa'
         and native[49].op_str=='0x46d000'
         and native[52].op_str=='0x453d40'
         and native[55].op_str.endswith(', 5')
         and native[-1].op_str=='0x52cb4f',
         'genuine original actor192 stage4/stage5 and PE animation differs')
    s=(R/'.analysis/f857-scripted-191/Boss005214B0-F857-whole.cpp').read_text()
    marker='        case 0x192: g_FighterProbeMarker = 403; break;'
    frag=(R/'probes/FighterScriptedStage192F858.inc').read_text()
    need(s.count(marker)==1 and frag.count('case 0x192:')==1
         and frag.count('return;')==1
         and 'SetNativeActionAt40FAC0(2);' in frag
         and 'F32(0x314)=3.0f;' in frag
         and frag.count('S16(0x62)==4')==1
         and frag.count('S16(0x62)==5')==1,
         'normal current actor192 C++ game source changed')
    return s.replace(marker,'#include "FighterScriptedStage192F858.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F858-whole.cpp';obj=O/'Boss005214B0-F858-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=env,capture_output=True,text=True,timeout=280)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'original actor192 full VC7.1 compilation failed '+(run.stdout+run.stderr)[-750:])
    return obj

def main():
    rd=ld('f858rd','compare-coff-function.py')
    ac=ld('f858ac','report-fighter-action-handlers.py')
    f834=ld('f858f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f858f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f858f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f858f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f858f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f858f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f858f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f858f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f858f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f858f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f858f857','verify-scripted-fighter-floatshot-191-f857.py')
    zero=ld('f858zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f858switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original 46KB fighter/packed DATA identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mp}
    raw=rd.pe_bytes_at(pe,by[0x192],by[0x194]-by[0x192])
    original=list(d.disasm(raw,by[0x192]))
    need((len(raw),len(original))==(217,64),
         'selected original sparse next 194 physical boundary changed')
    obj=compile_one(source(original,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(25690,7100,959,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'entire selected native-shaped source/COFF/receiver frame changed')
    dens,spars,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dens>0 and spars>0 and maps>0,'all five genuine original packed switch tables not reverified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x195')
           and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1,'next native 194 source marker missing')
    k=marks[0]
    body=ins[k-64:k]
    result=f834.physical_case(rd,pe,d,code,refs,body,by,0x192,217,6,f856.BAD,0x194,f820)
    need(result['native_complete_x86']==64
         and result['original_native_enclosing_parent_JMP_exit_ordinals']==[63]
         and body[63].op_str==hex(ret-4)
         and body[21].op_str=='2'
         and body[26].op_str.endswith(', 4')
         and body[33].op_str.endswith(', 0x40400000')
         and body[55].op_str.endswith(', 5'),
         'physical original actor192 sprite/float/action and giant exit not preserved')
    for ordinal,(target,sym) in f856.FIELDS.items():
        a,b=original[ordinal],body[ordinal]
        field=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(field)==1 and field[0]['type']=='REL32'
             and field[0]['addend']==0 and field[0]['local_symbol_offset'] is None
             and sym in field[0]['symbol']
             and field[0]['offset']-body[0].address==a.address-by[0x192]+a.size-4
             and a.op_str==f'0x{target:x}',
             'selected native actor192 physical PE call target/ordinal wrong '+str(ordinal))
    # Recheck every previous whole native case, not just the last call shape.
    later=[
      (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
      (0x186,250,74,7,f850.BAD186,0x187),
      (0x187,214,61,6,f850.BAD187,0x188),
      (0x188,214,61,6,f851.WRONG188,0x189),
      (0x189,381,107,11,f852.BAD189,0x18a),
      (0x18a,250,71,6,f853.BAD,0x18b),
      (0x18b,353,99,7,f855.WRONG,0x190),
      (0x190,217,64,6,f856.BAD,0x191),
      (0x191,166,53,5,f857.BAD,0x192)]
    prev=ins[k-64-sum(x[2] for x in later):k-64]
    pos=0;late_results=[]
    for a,nb,nx,nf,bad,nxt in later:
        section=prev[pos:pos+nx];pos+=nx
        late_results.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(pos==len(prev),'nine prior real actor136-191 cases not contiguous')
    old_shapes=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
    left=k-64-sum(x[2] for x in later)
    earlier=ins[left-sum(x[2] for x in old_shapes):left]
    pos=0;early_results=[]
    for a,nb,nx,nf,bad,nxt in old_shapes:
        section=earlier[pos:pos+nx];pos+=nx
        early_results.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,nb,nf,bad,nxt,f820))
    need(pos==len(earlier),'20 original C8-D2 and 12C-135 cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,[r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[p for p in range(46) if p not in mask and tail[p]!=code[ret-46+p]]
    need(wrong_tail==[10,12,16,19],'original native getter register phase unexpectedly fixed or changed')
    out={'real_original_giant':'0x005214B0',
         'original_whole_callable_CODE_B':46755,
         'new_entire_source_callable_CODE_B':ret,
         'original_192_native_complete_case':result,
         'original_192_physical_PE_field_ordinals':list(f856.FIELDS),
         'actor192_true_action_stage_float':{'action':2,'spawn_stage':4,'float_at_314':3.0,'final_stage':5},
         'actor192_true_source_nonfield_GPR_wrong_B':39,
         'actor192_true_enclosing_giant_final_JMP_wrong_offsets':[213,214],
         'prior_nine_real_GPR_affected_original_cases_reverified':late_results,
         'earlier_twenty_original_PE_cases_reverified':early_results,
         'real_default_46B_GPR_wrong_offsets':wrong_tail,
         'original_five_afterRET_tables_reverified':True,
         'native_separate_packed_switch_DATA_B':901,
         'original_entire_46755B_exact':False,
         'accepted_new_whole_callable_CODE_B':0,
         'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_46755B_exact'] is False
    print('F858 native 192 217B/64x86/6 physical PE calls in entire 25690B/7100x86 fighter, original state2 stage4 float3.0 stage5. 39 real GPR and 2 whole-parent epilogue JMP bytes still NONEXACT, prior 29 original PE cases plus 5 packed 901B tables rechecked.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F858 selected original 192 whole fighter FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
