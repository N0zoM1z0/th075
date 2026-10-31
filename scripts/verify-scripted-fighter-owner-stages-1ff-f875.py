#!/usr/bin/env python3
"""F875: original 1FF full native 533B/149x86/9 PE fields in entire fighter.

Stages1..5 trigger real borrowed owner 0040FAC0 action0x64,
and facing*74/40/36/33/32 FILD float X copied into real
owner+0x44, with FIVE genuine EBP scratch locations
-88/-8C/-90/-94/-98. Stage6 owner action0x35.
Compile ONE affected whole VC7.1 parent; check full native
opcode/width, nine original PE call targets, all earlier 48
native cases and five 901B packed switch DATA tables. The
existing 1FD CMP EAX 5B vs original ECX 6B remains NONEXACT.
No split-case callable source exact CODE or mass cold replay.
"""
from pathlib import Path
import importlib,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f875-scripted-owner-stages'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,72,74,78,81,95,99,102,107,111,114,120,123,134,138,141,144,156,159,162,165,171,174,178,181,186,190,193,199,202,213,217,220,223,235,238,241,244,250,253,257,260,265,269,272,278,281,292,296,299,302,314,317,320,323,329,332,336,339,344,348,351,357,360,371,375,378,381,393,396,399,402,408,411,415,418,423,427,430,436,439,450,454,457,460,472,475,478,481,487,490,494,497,502,506,509,515,518,529,530]
FIELD_ORDINALS=(9,17,25,37,59,81,103,125,147)
FIELD_OFFSETS=[26,66,90,129,208,287,366,445,524]
SCRATCH_ORDINALS=(41,63,85,107,129)
SCRATCH_MINUS=(0x88,0x8c,0x90,0x94,0x98)
STAGE_FACTORS=(74,40,36,33,32)

def need(ok,msg):
    if not ok:raise ValueError(msg)

def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'missing original PE helper '+name)
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m)
    return m

def make_source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f874-scripted-owner-dual/Boss005214B0-F874-whole.cpp'
    receipt=R/'.analysis/f874-scripted-owner-dual/verified-summary.json'
    if not prior.is_file() or not receipt.is_file():
        p=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-owner-dual-f874.py')],
             cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'previous-f874-fallback.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,'previous original 1FD/1FE PE verification failed '+(p.stdout+p.stderr)[-740:])
    proof=json.loads(receipt.read_text())
    need(proof['current_new_generated_whole_source_CODE_B']==30860
         and proof['whole_original_giant_exact'] is False
         and proof['1FD_incomplete_real_register_size_error'] is True,
         'prior 1FD real one-byte negative receipt altered')
    src=prior.read_text()
    marker='        case 0x1FF: g_FighterProbeMarker = 512; break;'
    inc=(R/'probes/FighterScriptedOwnerStages1FFF875.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x1FF:')==1
         and inc.count('return;')==1
         and inc.count('SetNativeActionAt40FAC0(0x64);')==5
         and inc.count('SetNativeActionAt40FAC0(0x35);')==1
         and inc.count('OWNER+0x44')==5
         and all(f'*{m})+F32(0x44)' in inc for m in STAGE_FACTORS)
         and inc.count('S16(0x62)==6')==1,
         'actual native original 1FF six stage owner C++ operations changed')
    return src.replace(marker,'#include "FighterScriptedOwnerStages1FFF875.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F875-whole.cpp'
    obj=O/'Boss005214B0-F875-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=env,capture_output=True,text=True,timeout=305)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'normal VC7.1 original 1FF full fighter source failed '+(p.stdout+p.stderr)[-770:])
    return obj

def main():
    rd=ld('f875rd','compare-coff-function.py')
    ac=ld('f875ac','report-fighter-action-handlers.py')
    f834=ld('f875f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f875f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f875f874','verify-scripted-fighter-owner-dual-f874.py')
    zero=ld('f875zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f875switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original 005214B0 entire fighter/afterRET DATA identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={r['action']:int(r['handler'],16) for r in mp}
    obj=compile_one(make_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(31378,8799,1102,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current complete fighter VC7.1 source x86/PE ABI or packed DATA changed')
    ds,ss,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(ds>0 and ss>0 and maps>0,'five separate original 901B packed switch DATA tables not rechecked')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x201')
        and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=363,'following native original case 200 marker missing')
    k=marks[0]
    now=ins[k-149:k]
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x1ff],by[0x200]-by[0x1ff]),by[0x1ff]))
    need(len(original)==149 and by[0x200]-by[0x1ff]==533,
         'original native 1FF full stage state extent changed')
    native=f834.physical_case(rd,pe,d,code,refs,now,by,0x1ff,533,9,BAD,0x200,f820)
    need(native['native_complete_x86']==149
         and native['original_native_enclosing_parent_JMP_exit_ordinals']==[148]
         and now[-1].op_str==hex(ret-4)
         and len(BAD)==111 and BAD[-2:]==[529,530],
         '1FF full original x86 and 109 genuine GPR plus two giant JMP mismatch offsets changed')
    native_raw=rd.pe_bytes_at(pe,by[0x1ff],533)
    lo=now[0].address
    fields=[r for r in refs if lo<=r['offset']<now[-1].address+now[-1].size]
    mask=f820.physical_fields(rd,native_raw,by[0x1ff],fields,lo,9)
    need(len(mask)==36,'all NINE original PE fields in current 1FF not verified')
    offsets=[]
    for ordinal in FIELD_ORDINALS:
        a,b=original[ordinal],now[ordinal]
        dst=0x453e20 if ordinal==9 else (0x40fa30 if ordinal==17 else 0x40fac0)
        symbol=('ResetAt453E20' if ordinal==9 else
                'GetNativeActionAt40FA30' if ordinal==17 else
                'SetNativeActionAt40FAC0')
        found=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['type']=='REL32'
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and symbol in found[0]['symbol']
             and found[0]['offset']-lo==a.address-by[0x1ff]+a.size-4
             and a.op_str==f'0x{dst:x}',
             'true original 1FF stage PE call target/source incorrect at ordinal '+str(ordinal))
        offsets.append(found[0]['offset']-lo)
    need(offsets==FIELD_OFFSETS,'original 1FF real physical PE field offset list moved')
    scratches=[]
    for ordinal,offset in zip(SCRATCH_ORDINALS,SCRATCH_MINUS):
        orig,src=original[ordinal],now[ordinal]
        need(orig.mnemonic==src.mnemonic=='mov'
             and orig.size==src.size
             and orig.op_str.startswith(f'dword ptr [ebp - 0x{offset:x}],')
             and src.op_str.startswith(f'dword ptr [ebp - 0x{offset:x}],')
             and original[ordinal+1].mnemonic==now[ordinal+1].mnemonic=='fild',
             'native real 1FF FILD scratch slot not naturally restored EBP-'+hex(offset))
        scratches.append(f'-0x{offset:x}')
    need(original[128].mnemonic==now[128].mnemonic=='shl',
         'native stage5 facing*32 must shift, not multiply through nonnative grammar')
    # Before new 1FF state, check previously sourced 46+2
    # complete original inner cases. The 1FD interval stays 385B:
    # explicitly reject the 386B original full-code claim.
    prior=json.loads((R/'.analysis/f874-scripted-owner-dual/verified-summary.json').read_text())
    prev=prior['previous_46_real_original_PE_cases_rechecked']
    need(len(prev)==46 and prev[0]['case']=='0xc8' and prev[-1]['case']=='0x1fc',
         'previous 46 actual native source cases missing')
    previous=ins[k-149-(107+107)-sum(x['native_complete_x86'] for x in prev):k-149-(107+107)]
    cursor=0;old=[]
    for j,x in enumerate(prev):
        a=int(x['case'],16)
        nxt=int(prev[j+1]['case'],16) if j+1<len(prev) else 0x1fd
        sec=previous[cursor:cursor+x['native_complete_x86']];cursor+=x['native_complete_x86']
        old.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,
          x['native_whole_inner_B'],x['original_typed_PE_fields'],
          x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if a==0x1a0:
            need(sec[3].op_str==sec[7].op_str==hex(sec[22].address),
                 'previous original game 1A0 guarded multipliers still wrong')
    need(cursor==len(previous),'46 earlier PE source states not contiguous')
    last=ins[k-149-214:k-149]
    one=last[:107];two=last[107:]
    need((one[-1].address+one[-1].size-one[0].address,
          two[-1].address+two[-1].size-two[0].address)==(385,392),
         'prior real owner 1FD CMP length gap or complete 1FE grammar drifted')
    orig1=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    for part in (orig1,one):
        need(part[100].op_str==hex(part[104].address),
             '1FD native stage false path must actually write status zero')
    need(orig1[99].size==6 and one[99].size==5 and
         one[99].op_str=='eax, 0x95',
         '1FD real original one byte invalid accumulator CMP drifted')
    f874_case=f834.physical_case(rd,pe,d,code,refs,two,by,0x1fe,392,9,
                                  f874.F874_1FE_BAD,0x1ff,f820)
    need(f874_case['native_complete_x86']==107,
         'previous original 1FE complete case recheck failed')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tailmask=f820.physical_fields(rd,tail,0x52cb25,
       [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in tailmask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'native shared getter four honest GPR negatives in full F875 changed')
    output={'real_original_whole_game':'0x005214B0',
      'native_original_callable_CODE_B':46755,
      'new_generated_whole_source_CODE_B':ret,
      'new_original_1FF_complete_case':native,
      'original_1FF_physical_PE_field_offsets':offsets,
      'five_actual_native_1FF_integer_FILD_scratch_EBP_slots':scratches,
      'actual_stages1to5_facing_multipliers':list(STAGE_FACTORS),
      'real_stage6_owner_action':0x35,
      'real_GPR_nonnative_machine_B':109,
      'real_giant_final_JMP_different_offsets':[529,530],
      'previous_46_other_native_cases_reverified':old,
      'previous_1FD_still_missing_original_CMP_encoding_byte':True,
      'previous_1FE_native_complete_case_reverified':f874_case,
      'native_getter_46B_GPR_wrong_offsets':wrong_tail,
      'all_original_five_901B_afterRET_packed_tables_rechecked':True,
      'original_separate_afterRET_DATA_B':901,
      'whole_original_game_exact':False,'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(output,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['whole_original_game_exact'] is False
    print('F875 real native 1FF 533B/149x86/nine original physical PE calls; five native FILD EBP -88/-8C/-90/-94/-98 naturally reproduced, six original stage effects. Whole parent 31378B/8799x86, 109 actual GPR plus two giant JMP bytes differ; previous 48 original actions incl 1FD one-byte CMP negative and five packed 901B DATA verified. Entire original fighter NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F875 selected original 1FF native PE proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
