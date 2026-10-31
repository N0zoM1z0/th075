#!/usr/bin/env python3
"""F878: original 201 267B/80-x86/8 true physically typed PE fields.

Native state201 at 00528FC7 has state-zero Reset/flags,
POS height decrement via ORIGINAL 00658350, getter state0,
TWO separate stage5/frame0 guards for sprite336/Prepare2
and POS=30.0f. The false 00657478 global has identical
COFF relocation field geometry and nonrelocation bytes,
but a WRONG native original PE target, so physical
destination verification is essential. Compile one selected
and one wrong-global whole VC7.1 fighter, check 50 preceding
real source-backed native cases (including 1FD one-byte
CMP negative), five 901B packed afterRET tables, and
native common getter. No all-unit cold replay or inner
case exact credit: original 46,755B giant remains nonexact.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f878-scripted-state201'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,63,66,82,85,94,97,100,103,119,122,138,140,144,147,161,165,168,173,177,180,186,189,191,193,196,198,200,203,205,230,234,237,242,246,249,253,256,263,264]
FIELDS={
 9:(0x453e20,'ResetAt453E20'),
 18:(0x65782c,'g_ThresholdAt0065782C'),
 24:(0x658350,'g_F873GroundDropAt00658350'),
 29:(0x65782c,'g_ThresholdAt0065782C'),
 36:(0x40fa30,'GetNativeActionAt40FA30'),
 44:(0x40fac0,'SetNativeActionAt40FAC0'),
 65:(0x453a70,'SpawnDirectedAt453A70'),
 68:(0x453d40,'PrepareActionAt453D40')
}
OFFSETS=[26,70,89,107,132,156,215,225]

def need(cond,msg):
    if not cond: raise ValueError(msg)

def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'original native PE helper missing '+name)
    mod=importlib.util.module_from_spec(spec);sys.modules[tag]=mod;spec.loader.exec_module(mod)
    return mod

def new_source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f877-scripted-owner-wave200/Boss005214B0-F877-whole.cpp'
    receipt=R/'.analysis/f877-scripted-owner-wave200/verified-summary.json'
    if not prev.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-owner-wave-200-f877.py')],
             cwd=R,capture_output=True,text=True,timeout=1450)
        (O/'f877-original-fallback.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'preceding 200 physical original PE proof failed '+(cp.stdout+cp.stderr)[-750:])
    proof=json.loads(receipt.read_text())
    need(proof['new_current_generated_source_CODE_B']==31997
         and proof['original_whole_fighter_exact'] is False,
         'preceding native source 200 PE receipt inconsistent')
    old=prev.read_text()
    marker='        case 0x201: g_FighterProbeMarker = 514; break;'
    inc=(R/'probes/FighterScriptedStage201F878.inc').read_text()
    need(old.count(marker)==1 and inc.count('case 0x201:')==1
         and inc.count('return;')==1
         and inc.count('S16(0x62)==5 && S16(0x64)==0')==2
         and inc.count('POS=30.0f;')==1
         and inc.count('SpawnDirectedAt453A70(0x336')==1
         and inc.count('PrepareActionAt453D40(2)')==1
         and inc.count('POS=POS-g_F873GroundDropAt00658350')==1,
         'native selected actor201 separate guards or real original float source changed')
    return old.replace(marker,'#include "FighterScriptedStage201F878.inc"',1)

def compile_one(src,tag='whole'):
    cpp=O/('Boss005214B0-F878-'+tag+'.cpp')
    obj=O/('Boss005214B0-F878-'+tag+'.obj')
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=env,capture_output=True,text=True,timeout=310)
    (O/('compiler-'+tag+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'normal VC7.1 actor201 entire parent '+tag+' failed '+(run.stdout+run.stderr)[-700:])
    return obj

def whole(rd,d,obj):
    code,refs=rd.object_function(obj,SYM)
    instructions=[]
    for x in d.disasm(code,0):
        instructions.append(x)
        if x.mnemonic=='ret':break
    ret=instructions[-1].address+instructions[-1].size
    marks=[j for j,x in enumerate(instructions) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x253')
         and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=80,'next real 252 source sentinel missing')
    return code,refs,instructions,ret,marks[0]

def main():
    rd=ld('f878rd','compare-coff-function.py')
    ac=ld('f878ac','report-fighter-action-handlers.py')
    f834=ld('f878f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f878f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f878f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f878f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f878f877','verify-scripted-fighter-owner-wave-200-f877.py')
    zero=ld('f878zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f878sw','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original complete fighter CODE/afterRET DATA identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    raw=rd.pe_bytes_at(pe,by[0x201],by[0x252]-by[0x201])
    orig=list(d.disasm(raw,by[0x201]))
    need((len(raw),len(orig))==(267,80)
         and orig[9].op_str=='0x453e20'
         and orig[18].op_str=='dword ptr [0x65782c]'
         and orig[24].op_str=='dword ptr [0x658350]'
         and orig[36].op_str=='0x40fa30'
         and orig[47].op_str.endswith(', 5')
         and orig[63].op_str=='0x336'
         and orig[65].op_str=='0x453a70'
         and orig[68].op_str=='0x453d40'
         and orig[71].op_str.endswith(', 5')
         and orig[78].op_str.endswith(', 0x41f00000')
         and orig[79].op_str=='0x52cb4f',
         'physical original 201 native actor stage5/game global/sprite/flags changed')
    src=new_source()
    obj=compile_one(src)
    code,refs,ins,ret,k=whole(rd,d,obj)
    need((ret,len(ins),len(refs),len(code)-ret)==(32249,9052,1118,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'native current 201 complete VC7.1 source/PE/COFF/ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all original five packed 901B switch tables failed')
    sec=ins[k-80:k]
    case=f834.physical_case(rd,pe,d,code,refs,sec,by,0x201,267,8,BAD,0x252,f820)
    need(case['native_complete_x86']==80
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[79]
         and sec[-1].op_str==hex(ret-4)
         and sec[63].op_str=='0x336'
         and sec[66].op_str=='2'
         and sec[78].op_str.endswith(', 0x41f00000'),
         'real original 201 native complete stage5+native epilogue changed')
    lo=sec[0].address
    ff=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x201],ff,lo,8)
    need(len(mask)==32,'all eight original PE fields not physically verified')
    offsets=[]
    for ordinal,(target,symbol) in FIELDS.items():
        x,y=orig[ordinal],sec[ordinal]
        found=[r for r in ff if y.address<=r['offset']<y.address+y.size]
        need(len(found)==1 and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if x.mnemonic=='call' else 'DIR32')
             and symbol in found[0]['symbol']
             and found[0]['offset']-lo==x.address-by[0x201]+x.size-4
             and x.op_str==(f'0x{target:x}' if x.mnemonic=='call'
                                else f'dword ptr [0x{target:x}]'),
             'real original 201 physical PE target changed at x86 '+str(ordinal))
        offsets.append(found[0]['offset']-lo)
    need(offsets==OFFSETS and len(BAD)==51 and BAD[-2:]==[263,264],
         'native 201 original real register/JMP differences changed')
    # Negative original source with the WRONG but physically relocatable
    # global at 657478. Identical nonrelocation code does NOT
    # mean the actual original global/callee is correctly recovered.
    inc=(R/'probes/FighterScriptedStage201F878.inc').read_text()
    actual='POS=POS-g_F873GroundDropAt00658350'
    wrong='POS=POS-g_SubtractAt00657478'
    need(inc.count(actual)==1
         and src.count('#include "FighterScriptedStage201F878.inc"')==1,
         'real native global source replacement control not unique')
    neg_src=src.replace('#include "FighterScriptedStage201F878.inc"',
                        inc.replace(actual,wrong,1),1)
    neg_obj=compile_one(neg_src,tag='wrong-physical-global')
    neg_code,neg_refs,neg_I,neg_ret,neg_k=whole(rd,d,neg_obj)
    need((neg_ret,len(neg_I),len(neg_refs),len(neg_code)-neg_ret)==(32249,9052,1118,901),
         'false-global control must preserve misleading whole geometry')
    ns=neg_I[neg_k-80:neg_k]
    need((ns[-1].address+ns[-1].size-ns[0].address,len(ns))==(267,80),
         'wrong global should preserve misleading 267B/80-x86 source body')
    typed=[r for r in neg_refs if ns[24].address<=r['offset']<ns[24].address+ns[24].size]
    need(len(typed)==1 and typed[0]['type']=='DIR32'
         and 'g_SubtractAt00657478' in typed[0]['symbol']
         and 'g_F873GroundDropAt00658350' not in typed[0]['symbol']
         and orig[24].op_str=='dword ptr [0x658350]',
         'false global must be rejected by real native 658350 PE destination')
    # The other incorrect source merges TWO separate stage5 guards,
    # shortening the entire actual case. Never compare a cropped
    # 267B prefix against the original as whole code.
    before='''    }
    if (S16(0x62)==5 && S16(0x64)==0)
        POS=30.0f;'''
    after='''        POS=30.0f;
    }'''
    need(inc.count(before)==1,'native two separate stage5 guards not present')
    merge_src=src.replace('#include "FighterScriptedStage201F878.inc"',inc.replace(before,after,1),1)
    merged_obj=compile_one(merge_src,tag='wrong-merged-stage5')
    merged_code,merged_refs,merged_I,merged_ret,merged_k=whole(rd,d,merged_obj)
    need((merged_ret,len(merged_I),len(merged_refs),len(merged_code)-merged_ret)==(32226,9044,1118,901),
         'incorrect merged-stage5 control should have nonnative whole code extent')
    # Recheck the previous native-backed game states from the newly
    # compiled FULL parent; including the nonexact one-byte 1FD CMP.
    previous=json.loads((R/'.analysis/f877-scripted-owner-wave200/verified-summary.json').read_text())
    old=previous['previous_46_PE_cases_reverified']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous 46 source-backed original PE case receipts missing')
    begin=ins[k-80-(107+107+149+177)-sum(x['native_complete_x86'] for x in old):
             k-80-(107+107+149+177)]
    cursor=0;old_checked=[]
    for index,x in enumerate(old):
        a=int(x['case'],16)
        nxt=int(old[index+1]['case'],16) if index+1<len(old) else 0x1fd
        n=x['native_complete_x86']
        section=begin[cursor:cursor+n];cursor+=n
        old_checked.append(f834.physical_case(rd,pe,d,code,refs,section,by,a,
          x['native_whole_inner_B'],x['original_typed_PE_fields'],
          x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if a==0x1a0:
            need(section[3].op_str==section[7].op_str==hex(section[22].address),
                 'original game stage0 1A0 floating multipliers moved outside guard')
    need(cursor==len(begin),'46 prior real original PE case interiors truncated')
    other=ins[k-80-(107+107+149+177):k-80]
    sf,sg,sh,si=other[:107],other[107:214],other[214:363],other[363:]
    original1=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(sf[-1].address+sf[-1].size-sf[0].address==385
         and original1[99].size==6 and sf[99].size==5
         and original1[100].op_str==hex(original1[104].address)
         and sf[100].op_str==hex(sf[104].address),
         'genuine original 1FD one-byte CMP and correct owner CFG must remain nonexact')
    prev_fe=f834.physical_case(rd,pe,d,code,refs,sg,by,0x1fe,392,9,
                               f874.F874_1FE_BAD,0x1ff,f820)
    prev_ff=f834.physical_case(rd,pe,d,code,refs,sh,by,0x1ff,533,9,
                               f875.BAD,0x200,f820)
    prev_200=f834.physical_case(rd,pe,d,code,refs,si,by,0x200,634,10,
                               f877.BAD,0x201,f820)
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
         [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tail_wrong=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(tail_wrong==[10,12,16,19],
         'native shared getter real GPR byte phase changed')
    receipt={'original_whole_fighter':'0x005214B0',
      'native_whole_game_callable_CODE_B':46755,
      'generated_entire_current_source_CODE_B':ret,
      'original_native_201_complete_case':case,
      'real_original_201_physical_PE_field_offsets':offsets,
      'original_201_true_gravity_global':'0x00658350',
      'false_global_same_nonfield_wrong_physical_destination':'0x00657478',
      'original_stage5_two_independent_game_guards_verified':True,
      'false_combined_stage5_whole_source_CODE_B':merged_ret,
      'actual_201_GPR_operand_wrong_B':49,
      'actual_enclosing_giant_final_JMP_wrong_offsets':[263,264],
      'original_46_early_original_case_sources_rechecked':old_checked,
      'original_1FD_one_native_CMP_byte_still_wrong':True,
      'original_1FE_complete_source_rechecked':prev_fe,
      'original_1FF_complete_source_rechecked':prev_ff,
      'original_200_complete_source_rechecked':prev_200,
      'real_common_getter_46B_GPR_byte_errors':tail_wrong,
      'all_five_original_901B_packed_afterRET_tables_reverified':True,
      'original_separate_afterRET_DATA_B':901,
      'original_entire_fighter_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_fighter_exact'] is False
    print('F878 true original 201 267B/80x86/8 physical PE fields, two real stage5 guards sprite336/Prepare2 then POS30. Wrong equal-length 657478 instead of real 658350 global PHYSICALLY rejected, merged guard whole extent wrong. Whole fighter 32249B/9052x86, 49 GPR+two giant-JMP bytes nonexact; all 50 prior original PE cases, five 901B packed tables rechecked.')

if __name__=='__main__':
    try: main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as err:
        print('F878 selected original fighter 201 FAILED:',err,file=sys.stderr)
        raise SystemExit(1)
