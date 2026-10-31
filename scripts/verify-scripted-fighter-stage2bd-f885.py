#!/usr/bin/env python3
"""F885: real 2BD native 855B/239x86/24 typed original PE fields.

Real 2BC does NOT serve as source for 2BD without game changes:
2BD stage1 one-shot uses sprite346 BEFORE PrepareD, changes action2C2,
Reset, copies observed borrowed owner's X, then early whole-gigant
exit; stage5 Prepare17 BEFORE 36C correction and sprite74,
stage7 PrepareB; stage8 height30; genuine FILD slots C4/C8.
Whole pinned VC7.1 fighter codegen compared to actual original PE
every x86 opcode/width/physical PE field, previous 60 game cases,
5 packed 901B afterRET DATA. Residual native GPR/JMP errors remain.
Never accept inner state as original whole callable CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f885-scripted-stage2bd'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
WRONG=[1,5,8,12,16,19,23,27,35,38,45,49,65,69,72,77,80,89,92,95,98,114,117,124,128,131,136,139,148,151,154,157,166,169,172,176,179,184,187,196,199,202,205,214,217,220,224,230,238,241,251,255,261,262,263,265,269,275,278,290,293,295,297,300,313,316,318,364,367,373,376,379,382,383,396,398,402,405,419,423,426,431,435,438,462,465,477,480,488,491,493,495,498,511,515,518,521,533,536,553,557,560,565,569,572,606,609,616,619,626,629,633,636,640,643,647,650,654,658,661,666,670,673,677,680,687,690,697,701,704,713,717,720,744,747,754,757,764,767,789,792,794,796,799,801,803,807,810,816,828,831,851,852]
FIELDS={
 15:(0x453e20,'ResetAt453E20'),
 22:(0x657d00,'g_F884DoubleDropAt00657D00'),
 27:(0x65782c,'g_ThresholdAt0065782C'),
 39:(0x658348,'g_F865SustainScaleAt00658348'),
 44:(0x6598b8,'g_F884PhaseYAt006598B8'),
 53:(0x658348,'g_F865SustainScaleAt00658348'),
 58:(0x6598b8,'g_F884PhaseYAt006598B8'),
 84:(0x657888,'g_ContactProjectionAt00657888'),
 92:(0x453b50,'SpawnExtraAt453B50'),
 95:(0x453d40,'PrepareActionAt453D40'),
 98:(0x40fac0,'SetNativeActionAt40FAC0'),
 100:(0x453e20,'ResetAt453E20'),
 108:(0x40fa30,'GetNativeActionAt40FA30'),
 116:(0x40fac0,'SetNativeActionAt40FAC0'),
 127:(0x453e80,'AnimatePushAt453E80'),
 130:(0x453d60,'PrepareActionAt453D60'),
 133:(0x657888,'g_ContactProjectionAt00657888'),
 142:(0x659470,'g_F884Stage5YAt00659470'),
 156:(0x453c80,'SpawnAt453C80'),
 167:(0x453d40,'PrepareActionAt453D40'),
 172:(0x40fbb0,'SetFloatMotionAt40FBB0'),
 209:(0x40fbb0,'SetFloatMotionAt40FBB0'),
 218:(0x46d000,'StartAnimationAt46D000'),
 237:(0x453c80,'SpawnFloatXRawYAt453C80')
}
PE_OFFSETS=[60,84,102,143,161,191,209,304,328,338,351,359,390,414,447,457,472,502,548,581,601,739,782,846]

def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'native PE helper missing '+name)
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m)
    return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    p=R/'.analysis/f884-scripted-stage2bc/Boss005214B0-F884-whole.cpp'
    receipt=R/'.analysis/f884-scripted-stage2bc/verified-summary.json'
    if not p.exists() or not receipt.exists():
        result=subprocess.run([str(R/'scripts/repo-python'),
                str(R/'scripts/verify-scripted-fighter-stage2bc-f884.py')],
                cwd=R,text=True,capture_output=True,timeout=1550)
        (O/'f884-fallback-original.log').write_text(result.stdout+result.stderr)
        need(result.returncode==0,'previous original 803B 2BC PE proof failed '+(result.stdout+result.stderr)[-760:])
    old=json.loads(receipt.read_text())
    need(old['current_complete_generated_source_CODE_B']==34775
         and old['native_whole_giant_exact'] is False,
         'prior original 2BC game source receipt altered')
    text=p.read_text()
    marker='        case 0x2BD: g_FighterProbeMarker = 702; break;'
    inc=(R/'probes/FighterScriptedStage2BDF885.inc').read_text()
    need(text.count(marker)==1 and inc.count('case 0x2BD:')==1
         and inc.count('return;')==2
         and 'SpawnExtraAt453B50(0x346' in inc
         and inc.index('SpawnExtraAt453B50(0x346')<inc.index('PrepareActionAt453D40(0xD)')
         and inc.index('SetNativeActionAt40FAC0(0x2C2)')<inc.index('ResetAt453E20();',inc.index('SetNativeActionAt40FAC0(0x2C2)'))
         and 'I32(0x44)=*reinterpret_cast<int*>(OWNER+0x44)' in inc
         and inc.index('PrepareActionAt453D60(0x17)')<inc.index('F32(0x36C)=')
         and 'SpawnAt453C80(0x74' in inc
         and 'PrepareActionAt453D40(0xB)' in inc
         and 'POS=30.0f;' in inc
         and 'SpawnFloatXRawYAt453C80(0x80' in inc,
         'real 2BD owner copy/early whole exit or stage changes missing')
    return text.replace(marker,'#include "FighterScriptedStage2BDF885.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F885-whole.cpp'
    obj=O/'Boss005214B0-F885-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
            cwd=R,env=E,capture_output=True,text=True,timeout=325)
    (O/'compiler.log').write_text(result.stdout+result.stderr)
    need(result.returncode==0,'native 2BD complete VC7.1 fighter source compile failed '+(result.stdout+result.stderr)[-760:])
    return obj

def main():
    rd=ld('f885rd','compare-coff-function.py')
    ac=ld('f885ac','report-fighter-action-handlers.py')
    f834=ld('f885f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f885f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f885f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f885f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f885f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f885f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f885f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f885f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f885f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f885f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f885f884','verify-scripted-fighter-stage2bc-f884.py')
    zero=ld('f885zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f885switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==0x5214b0)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original whole fighter or five packed afterRET native tables changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mp}
    raw=rd.pe_bytes_at(pe,by[0x2bd],by[0x2be]-by[0x2bd])
    orig=list(d.disasm(raw,by[0x2bd]))
    need((by[0x2bd],by[0x2be],len(raw),len(orig))==
         (0x529b37,0x529e8e,855,239)
         and orig[22].mnemonic=='fsub' and orig[22].op_str=='qword ptr [0x657d00]'
         and orig[69].mnemonic=='mov' and orig[70].mnemonic=='add'
         and orig[92].op_str=='0x453b50'
         and orig[95].op_str=='0x453d40'
         and orig[98].op_str=='0x40fac0'
         and orig[100].op_str=='0x453e20'
         and orig[106].op_str=='0x52cb4f'
         and orig[127].op_str=='0x453e80'
         and orig[130].op_str=='0x453d60'
         and orig[154].op_str=='0x74'
         and orig[148].op_str.startswith('dword ptr [ebp - 0xc4],')
         and orig[149].mnemonic=='fild'
         and orig[151].mnemonic=='fsubr'
         and orig[167].op_str=='0x453d40'
         and orig[218].op_str=='0x46d000'
         and orig[229].op_str.startswith('dword ptr [ebp - 0xc8],')
         and orig[230].mnemonic=='fild'
         and orig[-1].op_str=='0x52cb4f',
         'original 2BD real stage sprite/owner/float PE geometry changed')
    obj=compile_one(source())
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    need((ret,len(I),len(refs),len(code)-ret)==(35615,10031,1204,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'original 2BD whole VC7.1 source/x86/PE COFF ABI drifted')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'native five packed 901B afterRET jump tables unverified')
    marker=[j for j,x in enumerate(I) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x2bf')
        and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=239,'next actual 2BE source marker missing')
    k=marker[0];sec=I[k-239:k]
    now=f834.physical_case(rd,pe,d,code,refs,sec,by,0x2bd,855,24,WRONG,0x2be,f820)
    need(now['native_complete_x86']==239
         and now['original_native_enclosing_parent_JMP_exit_ordinals']==[106,238]
         and sec[106].op_str==sec[238].op_str==hex(ret-4)
         and sec[92].mnemonic=='call'
         and sec[95].mnemonic=='call'
         and sec[98].mnemonic=='call'
         and sec[100].mnemonic=='call'
         and sec[130].mnemonic=='call'
         and sec[151].mnemonic=='fsubr'
         and sec[230].mnemonic=='fild',
         'native 2BD whole-giant early return/owner change/FSUBR geometry changed')
    lo=sec[0].address
    ff=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x2bd],ff,lo,24)
    need(len(mask)==96,'original 2BD all 24 physically typed PE fields missing')
    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=orig[ordinal],sec[ordinal]
        found=[r for r in ff if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in found[0]['symbol']
             and found[0]['offset']-lo==a.address-by[0x2bd]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                               else f'qword ptr [0x{target:x}]' if ordinal==22
                               else f'dword ptr [0x{target:x}]'),
             'native 2BD original PE source/call/float target changed '+str(ordinal))
        offsets.append(found[0]['offset']-lo)
    need(offsets==PE_OFFSETS and len(WRONG)==153
         and all(i in WRONG for i in (382,383,851,852)),
         'real original 2BD register and two giant epilogue-JMP negatives changed')
    scratches=[]
    for ordinal,offset in ((148,0xc4),(229,0xc8)):
        a,b=orig[ordinal],sec[ordinal]
        need(a.mnemonic==b.mnemonic=='mov' and a.size==b.size==6
             and a.op_str.startswith(f'dword ptr [ebp - 0x{offset:x}],')
             and b.op_str.startswith(f'dword ptr [ebp - 0x{offset:x}],')
             and orig[ordinal+1].mnemonic==sec[ordinal+1].mnemonic=='fild',
             'native 2BD original real FILD scratch slot incorrect '+hex(offset))
        scratches.append(f'-0x{offset:x}')
    # Physically verify all 60 previous original switch-case
    # intervals using THIS newly compiled whole father object.
    previous=json.loads((R/'.analysis/f884-scripted-stage2bc/verified-summary.json').read_text())
    old=previous['previous_46_original_PE_case_sources_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous original 46 source-backed case physical receipts missing')
    prior_bc=I[k-239-228:k-239]
    f834.physical_case(rd,pe,d,code,refs,prior_bc,by,
                      0x2bc,803,22,f884.BAD,0x2bd,f820)
    earlier_end=k-239-228-(107+107+149+177+80+207+205+60+60)
    start=earlier_end-sum(x['native_complete_x86'] for x in old)
    prefix=I[start:earlier_end]
    pos=0;older=[]
    for j,x in enumerate(old):
        a=int(x['case'],16)
        next_action=int(old[j+1]['case'],16) if j+1<len(old) else 0x1fd
        sg=prefix[pos:pos+x['native_complete_x86']]
        pos+=x['native_complete_x86']
        older.append(f834.physical_case(rd,pe,d,code,refs,sg,by,
                    a,x['native_whole_inner_B'],x['original_typed_PE_fields'],
                    x['real_nonrelocation_wrong_offsets'],next_action,f820))
        if a==0x1a0:
            need(sg[3].op_str==sg[7].op_str==hex(sg[22].address),
                 'previous stage0 1A0 multiplier guards changed')
    need(pos==len(prefix),'46 previous original native state source intervals truncated')
    other=I[earlier_end:k-239-228-(207+205+60+60)]
    one,fe,ff,st200,st201=other[:107],other[107:214],other[214:363],other[363:540],other[540:]
    nativefd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(one[-1].address+one[-1].size-one[0].address==385
         and nativefd[99].size==6 and one[99].size==5
         and one[100].op_str==hex(one[104].address),
         '1FD original real one-byte CMP deficit/owner stage CFG changed')
    for a,nxt,sg,nb,nf,bad in [
       (0x1fe,0x1ff,fe,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,ff,533,9,f875.BAD),
       (0x200,0x201,st200,634,10,f877.BAD),
       (0x201,0x252,st201,267,8,f878.BAD)]:
        f834.physical_case(rd,pe,d,code,refs,sg,by,a,nb,nf,bad,nxt,f820)
    tr=I[k-239-228-(207+205+60+60):k-239-228-(205+60+60)]
    pos=0;two_bad=[]
    for a,nxt,nb,nx,sb,_ in f879.CASES:
        sg=tr[pos:pos+nx];pos+=nx;low=sg[0].address
        high=sg[-1].address+sg[-1].size
        f=[r for r in refs if low<=r['offset']<high]
        need(high-low==sb and len(f)==6,'252/253/254 physical codegen phase changed')
        if a==0x253:
            f834.physical_case(rd,pe,d,code,refs,sg,by,a,260,6,f879.BAD_253,0x254,f820)
        else:
            native=list(d.disasm(rd.pe_bytes_at(pe,by[a],nb),by[a]))
            need(nb-sb==(1 if a==0x252 else -1) and
                 native[10].mnemonic==sg[10].mnemonic=='sub'
                 and all(r['offset']-low==
                   native[next(j for j,z in enumerate(sg) if z.address<=r['offset']<z.address+z.size)].address-by[a]+
                   native[next(j for j,z in enumerate(sg) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                   for r in f),
                 '252/254 one-byte source PE fields MUST still be shifted')
            two_bad.append({'case':hex(a),'native_B':nb,'source_B':sb,'original_not_exact':True})
    need(pos==len(tr),'earlier 252/253/254 native source subregions truncated')
    reg=I[k-239-228-(205+60+60):k-239-228-(60+60)]
    pos=0;checks=[]
    for a,nxt,nb,nx,nf in f880.CASES:
        sg=reg[pos:pos+nx];pos+=nx
        checks.append(f834.physical_case(rd,pe,d,code,refs,sg,by,
                              a,nb,nf,f880.BAD[a],nxt,f820))
    need(pos==len(reg),'previous 255-257 actual native state intervals truncated')
    last258=I[k-239-228-120:k-239-228-60]
    last259=I[k-239-228-60:k-239-228]
    f834.physical_case(rd,pe,d,code,refs,last258,by,
                       0x258,206,6,f881.BAD,0x259,f820)
    f834.physical_case(rd,pe,d,code,refs,last259,by,
                       0x259,206,6,f883.BAD,0x2bc,f820)
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
              [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tail_wrong=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(tail_wrong==[10,12,16,19],
         'native common getter four true GPR errors shifted')
    out={'original_giant':'0x005214B0',
         'native_whole_callable_CODE_B':46755,
         'generated_current_whole_source_CODE_B':ret,
         'native_new_real_2BD_complete_case':now,
         'real_original_native_2BD_PE_field_offsets':offsets,
         'real_native_2BD_double_gravity_global':'0x00657D00',
         'real_native_two_FILD_scratch_EBP_slots':scratches,
         '2BD_first_original_early_game_action':'0x2C2',
         'native_real_2BD_two_enclosing_whole_JMP_ordinals':[106,238],
         '2BD_real_register_operand_wrong_B':149,
         '2BD_original_whole_giant_JMP_wrong_byte_offsets':[382,383,851,852],
         'previous_original_2BC_803B_completely_rechecked':True,
         'preceding_46_original_PE_game_cases_rechecked':older,
         'previous_1FD_real_one_byte_CMP_deficit_kept':True,
         'previous_1FE_1FF_200_201_native_sources_checked':True,
         'previous_252_254_nonexact_pe_shift_retained':two_bad,
         'previous_255_256_257_original_cases_checked':checks,
         'previous_258_259_original_cases_checked':True,
         'original_common_46B_getter_genuine_GPR_wrong_offsets':tail_wrong,
         'all_five_original_901B_afterRET_packed_tables_checked':True,
         'separate_original_afterRET_DATA_B':901,
         'entire_original_giant_exact':False,
         'new_accepted_whole_callable_CODE_B':0,
         'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['entire_original_giant_exact'] is False
    print('F885 real original 2BD full 855B/239 x86/24 physically typed PE fields. Native first sprite346 THEN PrepareD, SetAction2C2/Reset/OwnerX copy/early parent exit, stage5 Prepare17 before correction and sprite74, stage7 PrepareB, FILD scratch C4/C8. Selected entire fighter 35615B/10031x86: 149 genuine GPR and 4 giant-JMP bytes wrong. All 60 preceding original native cases and 5 packed 901B tables verified; full original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F885 real physical original 2BD PE FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
