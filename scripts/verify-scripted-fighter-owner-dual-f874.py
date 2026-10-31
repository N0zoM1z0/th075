#!/usr/bin/env python3
"""F874: real native 1FD/1FE owner-pointer control flow and PE fields.

Original 1FD has 386B/107-x86 and original 1FE 392B/107-x86
with NINE physical PE fields each, real borrowed owner at+0x2E8
and owner Y float equality against native global, then owner
stage<50 || >149. Crucial true CFG: float equality AND
stage out-of-range yields flag+0x80=1, all other paths SET zero;
wrong nested else silently skips that zero on in-range stage.
One normal full VC7.1 parent emits 1FD 385B (one real CMP99
register/length discrepancy), 1FE 392B (70 native nonfield
wrong including original giant exits). Never crop/claim exact
1FD; validate all PE field types/targets and 46 earlier game
states plus five original 901B packed switch tables.
"""
from pathlib import Path
import importlib,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f874-scripted-owner-dual'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
F874_1FE_BAD=[1,5,8,12,16,19,31,35,43,46,53,56,63,67,70,79,82,94,97,99,101,104,117,121,124,127,133,136,153,156,169,172,183,187,190,193,205,208,211,214,220,236,237,250,252,256,259,273,277,280,285,289,292,296,299,311,323,326,333,336,341,344,351,354,362,366,376,380,388,389]
ORIGINAL_FIELDS={
 0x1fd:{9:(0x453e20,'ResetAt453E20'),29:(0x659310,'g_F872Volley1FAYAt00659310'),
    43:(0x453c80,'SpawnAt453C80'),47:(0x40fac0,'SetNativeActionAt40FAC0'),
    50:(0x453e20,'ResetAt453E20'),63:(0x40fac0,'SetNativeActionAt40FAC0'),
    66:(0x40fa30,'GetNativeActionAt40FA30'),74:(0x40fac0,'SetNativeActionAt40FAC0'),
    85:(0x65782c,'g_ThresholdAt0065782C')},
 0x1fe:{9:(0x453e20,'ResetAt453E20'),29:(0x659310,'g_F872Volley1FAYAt00659310'),
    43:(0x453c80,'SpawnAt453C80'),46:(0x453e20,'ResetAt453E20'),
    50:(0x40fac0,'SetNativeActionAt40FAC0'),63:(0x40fac0,'SetNativeActionAt40FAC0'),
    66:(0x40fa30,'GetNativeActionAt40FA30'),74:(0x40fac0,'SetNativeActionAt40FAC0'),
    85:(0x65782c,'g_ThresholdAt0065782C')}}
OFFSETS={
 0x1fd:[26,108,148,164,178,225,238,262,300],
 0x1fe:[26,108,148,162,178,231,244,268,306]
}
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'native PE helper missing '+name)
    mod=importlib.util.module_from_spec(spec);sys.modules[tag]=mod;spec.loader.exec_module(mod);return mod
def source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f873-scripted-pair1fb-1fc/Boss005214B0-F873-whole.cpp'
    receipt=R/'.analysis/f873-scripted-pair1fb-1fc/verified-summary.json'
    if not prev.exists() or not receipt.exists():
        cp=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-recovery-pair-f873.py')],
             cwd=R,capture_output=True,text=True,timeout=1300)
        (O/'f873-prior-fallback-original.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'preceding native original 1FB/1FC source failed '+(cp.stdout+cp.stderr)[-720:])
    prior=json.loads(receipt.read_text())
    need(prior['new_generated_full_source_callable_CODE_B']==30110
         and prior['original_entire_game_giant_exact'] is False,
         'prior full native F873 evidence receipt changed')
    cpp=prev.read_text()
    anchor='// F539 natural switch *probe*, not original fighter source or CODE credit.'
    need(cpp.count(anchor)==1,'borrowing real owner declaration insertion site moved')
    cpp=cpp.replace(anchor,'''// F874: only the real native caller methods of actor+0x2E8 are borrowed.
class FighterBorrowedOwnerF874 {
public:
    void SetNativeActionAt40FAC0(int action);
    void ResetAt453E20();
};
'''+anchor,1)
    for a in (0x1fd,0x1fe):
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        fragment=(R/f'probes/FighterScriptedBorrowedOwner{a:X}F874.inc').read_text()
        need(cpp.count(marker)==1 and fragment.count(f'case 0x{a:X}:')==1
             and fragment.count('return;')==2
             and 'if (*reinterpret_cast<float*>(OWNER+0x48)==g_ThresholdAt0065782C &&' in fragment
             and 'S16(0x80)=1;' in fragment and 'S16(0x80)=0;' in fragment
             and '*reinterpret_cast<float*>(OWNER+0x44)=' in fragment
             and 'float followedX' not in fragment
             and 'SpawnAt453C80(0x50' in fragment,
             'original native owner 1FD/1FE condition or real floating source moved '+hex(a))
        cpp=cpp.replace(marker,f'#include "FighterScriptedBorrowedOwner{a:X}F874.inc"',1)
    return cpp

def compile_one(src):
    cpp=O/'Boss005214B0-F874-whole.cpp';obj=O/'Boss005214B0-F874-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=320)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'normal original-shaped owner states 1FD/1FE VC7.1 compile failed '+(run.stdout+run.stderr)[-800:])
    return obj

def main():
    rd=ld('f874rd','compare-coff-function.py')
    ac=ld('f874ac','report-fighter-action-handlers.py')
    f834=ld('f874f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f874f820','verify-scripted-fighter-landing-trio-f820.py')
    zero=ld('f874zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f874sw','verify-fighter-natural-switch-probes.py')
    d=Cs(CS_ARCH_X86,CS_MODE_32);pe=rd.verified_target()
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original whole fighter native CODE or packed afterRET DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(30860,8652,1094,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'F874 selected full VC7.1 source ABI/PE/COFF and DATA geometry changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all original 901B five packed afterRET tables unverified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x200')
           and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=214,'next genuine 1FF state marker missing')
    k=marks[0]
    present=[]
    for action,nxt,back,original_size,source_size in (
       (0x1fd,0x1fe,214,386,385),
       (0x1fe,0x1ff,107,392,392)):
        current=ins[k-back:k-back+107]
        lo,hi=current[0].address,current[-1].address+current[-1].size
        actual=rd.pe_bytes_at(pe,by[action],by[nxt]-by[action])
        original=list(d.disasm(actual,by[action]))
        need((len(actual),len(original),hi-lo,len(current))==(original_size,107,source_size,107),
             'full native 1FD/1FE current game actor extent changed '+hex(action))
        fields=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,actual,by[action],fields,lo,9)
        need(len(mask)==36,'all nine original 1FD/1FE physically typed fields not checked '+hex(action))
        offsets=[]
        for ordinal,(target,symbol) in ORIGINAL_FIELDS[action].items():
            a,b=original[ordinal],current[ordinal]
            hits=[r for r in fields if b.address<=r['offset']<b.address+b.size]
            need(len(hits)==1 and hits[0]['addend']==0
                 and hits[0]['local_symbol_offset'] is None
                 and hits[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
                 and symbol in hits[0]['symbol']
                 and hits[0]['offset']-lo==a.address-by[action]+a.size-4
                 and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                   else f'dword ptr [0x{target:x}]'),
                 'original 1FD/1FE PE field original position, source callee or destination differs '+hex(action)+' at '+str(ordinal))
            offsets.append(hits[0]['offset']-lo)
        need(offsets==OFFSETS[action],
             'actual original PE field positions wrong '+hex(action))
        need(all(a.mnemonic==b.mnemonic for a,b in zip(original,current)),
             'normal original 1FD/1FE x86 mnemonics differ '+hex(action))
        # Native original: owner Y FUCOMPP global-first, then
        # ALL in-range owner stage and Y-unequal paths WRITE status 0.
        # Old nested else wrongly jumped from JLE to JMP ord103,
        # silently skipping status reset. Recovered C++ must
        # jump from original ord100 directly to zero-store ord104.
        for part in (original,current):
            need(part[85].mnemonic=='fld'
                 and part[86].mnemonic=='fld'
                 and part[85].size==6 and part[86].size==3
                 and part[87].mnemonic=='fucompp'
                 and part[100].mnemonic=='jle'
                 and part[100].op_str==hex(part[104].address)
                 and part[95].mnemonic=='jl'
                 and part[95].op_str==hex(part[101].address),
                 'real original owner condition MUST zero in-range stage too '+hex(action))
        need(original[64].op_str==original[106].op_str=='0x52cb4f'
             and current[64].op_str==current[106].op_str==hex(ret-4),
             'two original direct enclosing fighter exits changed '+hex(action))
        if action==0x1fd:
            # This is a WHOLE source-negative, not a cropped byte match:
            # original CMP ECX,149=6 B; our compiler naturally
            # chose accumulator EAX CMP EAX,149=5 B at ord99.
            # The 385-byte source cannot earn exact or be masked.
            need(all(a.size==b.size and a.address-by[action]==b.address-lo
                     for a,b in zip(original[:99],current[:99]))
                 and all(a.size==b.size for a,b in zip(original[100:],current[100:]))
                 and original[99].mnemonic==current[99].mnemonic=='cmp'
                 and original[99].size==6 and original[99].op_str=='ecx, 0x95'
                 and current[99].size==5 and current[99].op_str=='eax, 0x95',
                 'original 1FD one genuine native CMP register/length error changed')
            case_result={'case':hex(action),
              'native_original_inner_CODE_B':386,
              'original_native_x86':107,
              'normal_source_complete_inner_CODE_B':385,
              'compiler_complete_x86':107,
              'physical_typed_PE_fields':9,
              'original_PE_field_offsets':offsets,
              'native_width_error_ordinal':99,
              'real_native_CMP':'CMP ECX,0x95 6B',
              'source_nonnative_CMP':'CMP EAX,0x95 5B',
              'whole_native_Case_exact':False}
        else:
            physical=f834.physical_case(rd,pe,d,code,refs,current,by,
                 action,392,9,F874_1FE_BAD,nxt,f820)
            need(physical['native_complete_x86']==107
                 and physical['original_native_enclosing_parent_JMP_exit_ordinals']==[64,106]
                 and len(F874_1FE_BAD)==70,
                 'true 1FE original source negative operands drifted')
            case_result={'case':hex(action),'native':physical,
                 'original_PE_field_offsets':offsets,
                 'true_native_GPR_bytes_different':66,
                 'true_enclosing_parent_JMP_wrong_offsets':[236,237,388,389],
                 'whole_native_Case_exact':False}
        present.append(case_result)
    # Recheck all previously native-verified full source case intervals
    # against ACTUAL original PE and this NEW full compiler object.
    prior_receipt=json.loads((R/'.analysis/f873-scripted-pair1fb-1fc/verified-summary.json').read_text())
    previous=(prior_receipt['previous_20_early_original_game_case_sources_rechecked']
        +prior_receipt['previous_24_late_original_game_case_sources_rechecked']
        +[x['native'] for x in prior_receipt['two_native_original_1FB_1FC_complete_cases']])
    need(len(previous)==46 and previous[0]['case']=='0xc8'
         and previous[-1]['case']=='0x1fc',
         'prior 46 physical native original game cases missing')
    earlier=ins[k-214-sum(x['native_complete_x86'] for x in previous):k-214]
    cursor=0;checked=[]
    for index,old in enumerate(previous):
        a=int(old['case'],16)
        nxt=int(previous[index+1]['case'],16) if index+1<len(previous) else 0x1fd
        n=old['native_complete_x86']
        section=earlier[cursor:cursor+n];cursor+=n
        row=f834.physical_case(rd,pe,d,code,refs,section,by,a,
             old['native_whole_inner_B'],old['original_typed_PE_fields'],
             old['real_nonrelocation_wrong_offsets'],nxt,f820)
        if a==0x1a0:
            need(section[3].op_str==section[7].op_str==hex(section[22].address),
                 'prior native1A0 stage-zero guarded multipliers broken')
        checked.append(row)
    need(cursor==len(earlier),'all 46 genuine original case source intervals not contiguous')
    native_tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,native_tail,0x52cb25,
             [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and native_tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'native common 46B getter true original GPR phase changed')
    out={'original_whole_fighter':'0x005214B0',
      'native_entire_original_game_callable_CODE_B':46755,
      'current_new_generated_whole_source_CODE_B':ret,
      'two_actual_original_owner_game_cases':present,
      '1FD_incomplete_real_register_size_error':True,
      '1FE_original_392B_107x86_full_geometry':True,
      'original_1FD_1FE_union_PE_field_total':18,
      'combined_outer_equality_and_stage_range_native_branch_to_real_zero_store':True,
      'previous_46_real_original_PE_cases_rechecked':checked,
      'original_default_46B_GPR_wrong_offsets':wrong_tail,
      'original_five_packed_901B_afterRET_tables_verified':True,
      'native_separate_switch_afterRET_DATA_B':901,
      'whole_original_giant_exact':False,
      'new_accepted_callable_whole_CODE_B':0,
      'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['whole_original_giant_exact'] is False
    print('F874 real owner 1FD 386 original vs385 source 107x86 one CMP EAX5B/ECX6B negative; 1FE original 392B/107x86 full grammar 9 PE fields and 70 honest nonfield wrong. Crucial JLE from stage<=149 to real zero-status instruction104 corrected. Entire source 30860B/8652x86, all prior 46 native cases/901B tables rechecked. Whole fighter NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F874 original 1FD/1FE whole PE source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
