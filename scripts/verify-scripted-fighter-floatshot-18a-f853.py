#!/usr/bin/env python3
"""F853: native 18A 250B/71 x86, six physical PE fields, in whole fighter.

Natural Y lvalue prevents reversed original FLD/FADD operand widths.
Compile only the affected normal VC7.1 parent and check each original
field, GPR negatives, prior states and separate 901B packed tables.
Original full 46755B giant remains nonexact, no accepted CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f853-scripted-float-shot18a'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,23,27,35,38,45,48,55,59,67,70,79,82,85,88,104,107,114,117,133,135,139,142,156,160,163,168,172,175,181,184,186,188,191,204,208,211,217,223,226,246,247]
PE_FIELDS={18:(0x658058,'g_JumpGroundCorrectionAt00658058'),
           23:(0x65782c,'g_ThresholdAt0065782C'),
           32:(0x40fa30,'GetNativeActionAt40FA30'),
           40:(0x40fac0,'SetNativeActionAt40FAC0'),
           55:(0x65929c,'g_F853OffsetYAt0065929C'),
           69:(0x453a70,'SpawnFloatXYAt453A70')}

def need(x,msg):
    if not x:raise ValueError(msg)

def load(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'original PE helper missing '+name)
    mod=importlib.util.module_from_spec(spec)
    sys.modules[tag]=mod;spec.loader.exec_module(mod)
    return mod

def build_source():
    O.mkdir(parents=True,exist_ok=True)
    old=subprocess.run([str(R/'scripts/repo-python'),
       str(R/'scripts/verify-scripted-fighter-bounce-189-f852.py')],
       cwd=R,capture_output=True,text=True,timeout=1300)
    (O/'f852-prior-proof.log').write_text(old.stdout+old.stderr)
    need(old.returncode==0,'prior native PE source check failed '+(old.stdout+old.stderr)[-650:])
    source=(R/'.analysis/f852-scripted-189/Boss005214B0-F852-whole.cpp').read_text()
    old='void SpawnDirectedAt453A70(int,int,int,char,int);'
    need(source.count(old)==1,'member declaration not unique')
    source=source.replace(old,old+' void SpawnFloatXYAt453A70(int,float,float,char,int);',1)
    source='extern float g_F853OffsetYAt0065929C;\n'+source
    old='        case 0x18A: g_FighterProbeMarker = 395; break;'
    inc=(R/'probes/FighterScriptedFloatShot18AF853.inc').read_text()
    need(source.count(old)==1 and inc.count('case 0x18A:')==1
         and inc.count('return;')==1
         and '(*(&POS48))+g_F853OffsetYAt0065929C' in inc
         and 'SpawnFloatXYAt453A70(0x327' in inc,
         'real native x87 float source changed')
    return source.replace(old,'#include "FighterScriptedFloatShot18AF853.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F853-whole.cpp'
    obj=O/'Boss005214B0-F853-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=env,capture_output=True,text=True,timeout=280)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'real 18A full C++ failed '+(run.stdout+run.stderr)[-800:])
    return obj

def main():
    rd=load('f853reader','compare-coff-function.py')
    ac=load('f853actions','report-fighter-action-handlers.py')
    f834=load('f853f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=load('f853f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=load('f853f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=load('f853f849','verify-scripted-fighter-physics-136-f849.py')
    f850=load('f853f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=load('f853f851','verify-scripted-fighter-ground-188-f851.py')
    f852=load('f853f852','verify-scripted-fighter-bounce-189-f852.py')
    zero=load('f853zero','verify-fighter-actionzero-natural-source.py')
    sw=load('f853switch','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original whole fighter identity changed')
    report,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    obj=compile_one(build_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(24797,6828,939,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'original selected giant whole CODE/ABI/packed DATA changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'five real original packed dispatch tables failed')
    markers=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x18c')
         and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1,'next original 18B source sentinel not unique')
    k=markers[0]
    section=ins[k-71:k]
    native=f834.physical_case(rd,pe,d,code,refs,section,by,0x18a,250,6,BAD,0x18b,f820)
    need(native['native_complete_x86']==71
         and native['original_native_enclosing_parent_JMP_exit_ordinals']==[70]
         and section[70].op_str==hex(ret-4)
         and section[54].mnemonic=='fld' and section[54].size==3
         and section[54].op_str.endswith('+ 0x48]')
         and section[55].mnemonic=='fadd' and section[55].size==6,
         'original 18A x87 source Y lvalue and direct exit wrong')
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x18a],250),by[0x18a]))
    for ordinal,(target,symbol) in PE_FIELDS.items():
        a,b=original[ordinal],section[ordinal]
        fields=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(fields)==1 and fields[0]['local_symbol_offset'] is None
             and fields[0]['addend']==0
             and fields[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and symbol in fields[0]['symbol']
             and fields[0]['offset']-section[0].address==a.address-by[0x18a]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                else f'dword ptr [0x{target:x}]'),
             'physical target native 18A field moved '+str(ordinal))
    # Every previously sourced case checked again against the
    # genuine original PE/COFF on this new full function.
    late=[
      (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
      (0x186,250,74,7,f850.BAD186,0x187),
      (0x187,214,61,6,f850.BAD187,0x188),
      (0x188,214,61,6,f851.WRONG188,0x189),
      (0x189,381,107,11,f852.BAD189,0x18a)]
    prev=ins[k-71-sum(x[2] for x in late):k-71]
    off=0;late_results=[]
    for a,nb,nx,nf,bad,nxt in late:
        sec=prev[off:off+nx];off+=nx
        late_results.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(off==len(prev),'five prior native ground cases truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),
                       (0x135,278,82,7,[274,275],0x136)]
    beginning=k-71-sum(x[2] for x in late)
    earlier=ins[beginning-sum(x[2] for x in early):beginning]
    off=0;previous=[]
    for a,nb,nx,nf,bad,nxt in early:
        sec=earlier[off:off+nx];off+=nx
        previous.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(off==len(earlier),'20 early original native cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
           [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong==[10,12,16,19],'actual common getter real GPR phase changed')
    report_data={
       'original_native_whole':'0x005214B0',
       'original_entire_callable_CODE_B':46755,
       'generated_whole_source_callable_CODE_B':ret,
       'new_actual_native_18A_complete_case':native,
       'original_18A_typed_PE_field_ordinals':list(PE_FIELDS),
       'real_nonparentJMP_GPR_mismatch_count':45,
       'original_giant_final_JMP_operand_wrong_offsets':[246,247],
       'five_late_original_native_cases_rechecked':late_results,
       'twenty_prior_original_native_cases_rechecked':previous,
       'native_common_getter_GPR_negative_offsets':wrong,
       'five_packed_901B_original_afterRET_tables_verified':True,
       'original_separate_afterRET_DATA_B':901,
       'whole_original_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(report_data,indent=2)+'\n')
    print('F853: selected original 18A 250B/71-x86/6 native PE fields. Real lvalue float Y fixes native FLD this+48/FADD global65929C. 45 honest native GPR operand negatives plus original final giant JMP two bytes. Entire current parent 24,797B/6,828-x86, 25 prior physical cases and five packed 901B DATA tables checked; giant still NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F853 original selected whole 18A FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
