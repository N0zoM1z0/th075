#!/usr/bin/env python3
"""F884: original giant fighter native 2BC 803B/228 x86/22 PE fields.

Real double-precision gravity, opposite stage7/9 flight motion,
once-only F00 counter and 453B50 sprite346 with seven real
arguments, true native current getter, stage5 motion and
sprite73 through FILD/FSUBR EBP-BC, stage7/8/10 movement
settings (40FBB0 true float,float,int), and stage8 FILD
EBP-C0 sprite80. Compile only affected full VC7.1
father, check every native 803B mnemonic/width and 22
physical PE destinations, wrong x87 / 16-bit ++ negative
full-source controls and previous 59 actual PE-backed cases
plus original five 901B packed afterRET tables.
No exact callable giant CODE until original 46755B matches.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f884-scripted-stage2bc'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,23,27,35,38,45,49,65,69,72,77,80,89,92,95,98,114,117,124,128,131,136,139,148,151,154,157,166,169,172,176,179,184,187,196,199,202,205,214,217,220,224,230,234,237,243,247,254,257,261,267,270,292,295,297,299,302,315,318,320,344,346,350,353,367,371,374,379,383,386,400,403,415,418,436,439,441,443,446,459,463,466,469,481,484,501,505,508,513,517,520,554,557,564,567,574,577,581,584,588,591,595,598,602,606,609,614,618,621,625,628,635,638,645,649,652,661,665,668,692,695,702,705,712,715,737,740,742,744,747,749,751,755,758,764,776,779,799,800]
FIELDS={
 15:(0x453e20,'ResetAt453E20'),
 22:(0x657d00,'g_F884DoubleDropAt00657D00'),
 27:(0x65782c,'g_ThresholdAt0065782C'),
 39:(0x658348,'g_F865SustainScaleAt00658348'),
 44:(0x6598b8,'g_F884PhaseYAt006598B8'),
 53:(0x658348,'g_F865SustainScaleAt00658348'),
 58:(0x6598b8,'g_F884PhaseYAt006598B8'),
 78:(0x453d40,'PrepareActionAt453D40'),
 87:(0x657888,'g_ContactProjectionAt00657888'),
 95:(0x453b50,'SpawnExtraAt453B50'),
 97:(0x40fa30,'GetNativeActionAt40FA30'),
 105:(0x40fac0,'SetNativeActionAt40FAC0'),
 116:(0x453e80,'AnimatePushAt453E80'),
 119:(0x657888,'g_ContactProjectionAt00657888'),
 124:(0x453d60,'PrepareActionAt453D60'),
 131:(0x659470,'g_F884Stage5YAt00659470'),
 145:(0x453c80,'SpawnAt453C80'),
 156:(0x453d40,'PrepareActionAt453D40'),
 161:(0x40fbb0,'SetFloatMotionAt40FBB0'),
 198:(0x40fbb0,'SetFloatMotionAt40FBB0'),
 207:(0x46d000,'StartAnimationAt46D000'),
 226:(0x453c80,'SpawnFloatXRawYAt453C80')}
OFFSETS=[60,84,102,143,161,191,209,281,306,330,338,362,395,410,429,450,496,529,549,687,730,794]
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'missing original PE helper '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f883-scripted-stage259/Boss005214B0-F883-whole.cpp'
    proof=R/'.analysis/f883-scripted-stage259/verified-summary.json'
    if not prev.is_file() or not proof.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-physical259-f883.py')],
             cwd=R,capture_output=True,text=True,timeout=1500)
        (O/'f883-original-fallback.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'prior original physical 259 source missing '+(cp.stdout+cp.stderr)[-770:])
    receipt=json.loads(proof.read_text())
    need(receipt['new_generated_entire_source_CODE_B']==33987
         and receipt['entire_original_whole_giant_exact'] is False,
         'prior physical 259 source receipt inconsistent')
    cpp=prev.read_text()
    marker='        case 0x2BC: g_FighterProbeMarker = 701; break;'
    original_class='void SetMotionStateAt40FBB0(int,float,int);'
    need(cpp.count(marker)==1 and cpp.count(original_class)==1,
         'native 2BC marker or borrowed real game method declaration moved')
    cpp=cpp.replace(original_class,
         original_class+' void SetFloatMotionAt40FBB0(float,float,int); void AnimatePushAt453E80(int); void SpawnExtraAt453B50(int,int,float,char,int,int,int);',1)
    prefix=('extern double g_F884DoubleDropAt00657D00;\n'
            'extern float g_F884PhaseYAt006598B8;\n'
            'extern float g_F884Stage5YAt00659470;\n')
    inc=(R/'probes/FighterScriptedStage2BCF884.inc').read_text()
    need(inc.count('case 0x2BC:')==1 and inc.count('return;')==1
         and 'POS=POS-g_F884DoubleDropAt00657D00;' in inc
         and '++S16(0xF00);' in inc
         and 'SpawnExtraAt453B50(0x346' in inc
         and 'SpawnAt453C80(0x73' in inc
         and 'SetFloatMotionAt40FBB0(-200.0f,60.0f,0);' in inc
         and 'SetFloatMotionAt40FBB0(100.0f,60.0f,0);' in inc
         and 'SpawnFloatXRawYAt453C80(0x80' in inc
         and 'reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-' in inc,
         'original whole 2BC double float flight source incomplete')
    return prefix+cpp.replace(marker,'#include "FighterScriptedStage2BCF884.inc"',1)

def compile_one(src,variant='whole'):
    cpp=O/('Boss005214B0-F884-'+variant+'.cpp')
    obj=O/('Boss005214B0-F884-'+variant+'.obj')
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=E,capture_output=True,text=True,timeout=325)
    (O/('compiler-'+variant+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'normal original native 2BC entire parent '+variant+' failed '+(cp.stdout+cp.stderr)[-710:])
    return obj

def parsed(rd,d,obj):
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    marks=[j for j,x in enumerate(I) if x.mnemonic=='mov'
          and x.op_str.endswith(', 0x2be')
          and any('g_FighterProbeMarker' in r['symbol']
                 and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=228,
         'physical 2BD following source marker not unique')
    return code,refs,I,ret,marks[0]

def main():
    rd=ld('f884rd','compare-coff-function.py')
    ac=ld('f884ac','report-fighter-action-handlers.py')
    f834=ld('f884f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f884f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f884f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f884f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f884f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f884f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f884f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f884f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f884f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f884f883','verify-scripted-fighter-physical259-f883.py')
    zero=ld('f884zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f884switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original Japanese fighter full physical CODE/afterRET identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mp}
    original_raw=rd.pe_bytes_at(pe,by[0x2bc],by[0x2bd]-by[0x2bc])
    original=list(d.disasm(original_raw,by[0x2bc]))
    need((len(original_raw),len(original),by[0x2bc],by[0x2bd])==
         (803,228,0x529814,0x529b37),
         'original 2BC actual physical bounded PE extent changed')
    need(original[22].mnemonic=='fsub' and original[22].size==6
         and original[22].op_str=='qword ptr [0x657d00]'
         and original[69].mnemonic=='mov' and original[70].mnemonic=='add'
         and original[95].op_str=='0x453b50'
         and original[137].op_str.startswith('dword ptr [ebp - 0xbc],')
         and original[138].mnemonic=='fild'
         and original[140].mnemonic=='fsubr' and original[140].size==3
         and original[161].op_str=='0x40fbb0'
         and original[198].op_str=='0x40fbb0'
         and original[218].op_str.startswith('dword ptr [ebp - 0xc0],')
         and original[219].mnemonic=='fild'
         and original[226].op_str=='0x453c80'
         and original[-1].op_str=='0x52cb4f',
         'original 2BC x87/once-only/real game method physical proof changed')
    src=source()
    obj=compile_one(src)
    code,refs,ins,ret,k=parsed(rd,d,obj)
    need((ret,len(ins),len(refs),len(code)-ret)==(34775,9794,1181,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'F884 one complete affected VC7.1 parent CODE/x86/COFF/ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all original five packed afterRET 901B tables not physically checked')
    now=ins[k-228:k]
    case=f834.physical_case(rd,pe,d,code,refs,now,by,0x2bc,803,22,BAD,0x2bd,f820)
    need(case['native_complete_x86']==228
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[227]
         and now[-1].op_str==hex(ret-4)
         and now[22].mnemonic=='fsub' and now[22].size==6
         and now[69].mnemonic=='mov' and now[70].mnemonic=='add'
         and now[138].mnemonic=='fild'
         and now[140].mnemonic=='fsubr'
         and now[219].mnemonic=='fild',
         'original 2BC exact geometry vs source inherited earlier x87 false grammar')
    lo=now[0].address
    fields=[r for r in refs if lo<=r['offset']<now[-1].address+now[-1].size]
    mask=f820.physical_fields(rd,original_raw,by[0x2bc],fields,lo,22)
    need(len(mask)==88,'all 22 native original PE call/global fields not verified')
    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],now[ordinal]
        found=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in found[0]['symbol']
             and found[0]['offset']-lo==a.address-by[0x2bc]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                  else f'qword ptr [0x{target:x}]' if ordinal==22
                                  else f'dword ptr [0x{target:x}]'),
             'native 2BC real physical PE destination or float width changed '+str(ordinal))
        offsets.append(found[0]['offset']-lo)
    need(offsets==OFFSETS and len(BAD)==144 and BAD[-2:]==[799,800],
         'F884 genuine original GPR and enclosing JMP operand differences drifted')
    # Verify BOTH used source float integer temporaries sit at
    # actual native original physical EBP slots.
    for ordinal,slot in ((137,0xbc),(218,0xc0)):
        need(original[ordinal].mnemonic==now[ordinal].mnemonic=='mov'
             and original[ordinal].size==now[ordinal].size==6
             and original[ordinal].op_str.startswith(f'dword ptr [ebp - 0x{slot:x}],')
             and now[ordinal].op_str.startswith(f'dword ptr [ebp - 0x{slot:x}],')
             and original[ordinal+1].mnemonic==now[ordinal+1].mnemonic=='fild',
             'actual original native FILD scratch EBP allocation changed '+hex(slot))
    # Two independently COMPILED wrong full fighter controls.
    fragment=(R/'probes/FighterScriptedStage2BCF884.inc').read_text()
    callsite='#include "FighterScriptedStage2BCF884.inc"'
    need(src.count(callsite)==1,'native original state2BC insertion not unique')
    correct='reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-'
    need(fragment.count(correct)==1,'source observed real actor X borrowed lvalue not present')
    wrong_x=src.replace(callsite,fragment.replace(correct,'F32(0x44)-',1),1)
    bad_obj=compile_one(wrong_x,variant='wrong-stage5-x87-fisub')
    bc,br,bI,bret,bk=parsed(rd,d,bad_obj)
    bx=bI[bk-228:bk]
    need((bret,len(bI),len(br),len(bc)-bret)==(34775,9794,1181,901)
         and bx[140].mnemonic=='fisub'
         and original[140].mnemonic=='fsubr',
         'wrong bare actor-X source must exhibit real FISUB rather than native FSUBR')
    correct_increment='++S16(0xF00);'
    need(fragment.count(correct_increment)==1,'real original once-only short counter source missing')
    wrong_inc=src.replace(callsite,
               fragment.replace(correct_increment,'S16(0xF00)=S16(0xF00)+1;',1),1)
    inc_obj=compile_one(wrong_inc,variant='wrong-32bit-counter')
    ic,ir,iI,iret,ik=parsed(rd,d,inc_obj)
    isec=iI[ik-228:ik]
    need((iret,len(iI),len(ir),len(ic)-iret)==(34774,9794,1181,901)
         and isec[-1].address+isec[-1].size-isec[0].address==802
         and original[69].mnemonic=='mov' and isec[69].mnemonic=='movsx'
         and isec[70].size==3 and original[70].size==4,
         'wrong 32-bit short counter must fail real original 803B/228x86 extent')
    # Recheck the previous real 59 native game intervals in
    # the SAME newly compiled object, not an independent exact
    # acceptance and not all-unit cold replay.
    previous=json.loads((R/'.analysis/f883-scripted-stage259/verified-summary.json').read_text())
    old=previous['old_46_original_PE_cases_verified']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous first 46 native game cases absent')
    prefix_end=k-228-(107+107+149+177+80+207+205+60+60)
    prefix=ins[prefix_end-sum(x['native_complete_x86'] for x in old):prefix_end]
    pos=0;older=[]
    for j,x in enumerate(old):
        a=int(x['case'],16)
        nxt=int(old[j+1]['case'],16) if j+1<len(old) else 0x1fd
        sec=prefix[pos:pos+x['native_complete_x86']]
        pos+=x['native_complete_x86']
        older.append(f834.physical_case(rd,pe,d,code,refs,sec,by,
                 a,x['native_whole_inner_B'],x['original_typed_PE_fields'],
                 x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if a==0x1a0:
            need(sec[3].op_str==sec[7].op_str==hex(sec[22].address),
                 'true original game 1A0 stage0 float multipliers incorrectly unguarded')
    need(pos==len(prefix),'prior 46 real original native PE intervals truncated')
    misc=ins[prefix_end:k-228-(207+205+60+60)]
    one,fe,ff,st200,st201=misc[:107],misc[107:214],misc[214:363],misc[363:540],misc[540:]
    one_orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(one[-1].address+one[-1].size-one[0].address==385
         and one_orig[99].size==6 and one[99].size==5
         and one[100].op_str==hex(one[104].address),
         'original 1FD real one-byte CMP negative or corrected game status CFG changed')
    for a,nxt,sec,nb,nf,bad in [
        (0x1fe,0x1ff,fe,392,9,f874.F874_1FE_BAD),
        (0x1ff,0x200,ff,533,9,f875.BAD),
        (0x200,0x201,st200,634,10,f877.BAD),
        (0x201,0x252,st201,267,8,f878.BAD)]:
        check=f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820)
        need(check['original_typed_PE_fields']==nf,'earlier original native case changed '+hex(a))
    trio=ins[k-228-(207+205+60+60):k-228-(205+60+60)]
    pos=0;bad_siblings=[]
    for action,nxt,nb,nx,sb,_ in f879.CASES:
        sec=trio[pos:pos+nx];pos+=nx;lo2=sec[0].address
        hi2=sec[-1].address+sec[-1].size
        fs=[r for r in refs if lo2<=r['offset']<hi2]
        need(hi2-lo2==sb and len(fs)==6,'original 252..254 full source byte phases altered')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,sec,by,
                       action,nb,6,f879.BAD_253,0x254,f820)
        else:
            native=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and native[10].mnemonic==sec[10].mnemonic=='sub'
                 and all(r['offset']-lo2==
                     native[next(j for j,z in enumerate(sec) if z.address<=r['offset']<z.address+z.size)].address-by[action]+
                     native[next(j for j,z in enumerate(sec) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                     for r in fs),
                 'original 252/254 PE field offsets no longer shifted, cannot guess exact')
            bad_siblings.append({'case':hex(action),'native_B':nb,'source_B':sb,'not_exact':True})
    need(pos==len(trio),'old physical 252-254 native case intervals overlap')
    stage=ins[k-228-(205+60+60):k-228-(60+60)]
    pos=0;older_sprites=[]
    for a,nxt,nb,nx,nf in f880.CASES:
        sec=stage[pos:pos+nx];pos+=nx
        older_sprites.append(f834.physical_case(rd,pe,d,code,refs,sec,by,
                            a,nb,nf,f880.BAD[a],nxt,f820))
    need(pos==len(stage),'preceding 255-257 native stage x86 intervals lost')
    last258=ins[k-228-120:k-228-60]
    last259=ins[k-228-60:k-228]
    check258=f834.physical_case(rd,pe,d,code,refs,last258,by,
                    0x258,206,6,f881.BAD,0x259,f820)
    check259=f834.physical_case(rd,pe,d,code,refs,last259,by,
                    0x259,206,6,f883.BAD,0x2bc,f820)
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
               [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'native current common getter four real GPR operand errors moved')
    output={'real_original_giant':'0x005214B0',
        'whole_native_callable_CODE_B':46755,
        'current_complete_generated_source_CODE_B':ret,
        'new_native_case_2BC_complete_803B':case,
        'real_original_2BC_physical_PE_field_offsets':offsets,
        'original_native_DOUBLE_gravity_DIR32':'0x00657D00',
        'real_x87_stage5_stage8_FILD_slots':['-0xBC','-0xC0'],
        'native_real_x87_stage5_expression':'FILD then FSUBR actor+44',
        'nonnative_float_expression_same_length_FISUB_rejected':True,
        'nonnative_dword_short_increment_full_case_802B_rejected':True,
        'native_2BC_real_register_operand_wrong_B':142,
        'native_giant_epilogue_JMP_wrong_byte_offsets':[799,800],
        'previous_46_original_PE_case_sources_rechecked':older,
        'previous_1FD_original_CMP_one_byte_negative':True,
        'previous_1FE_1FF_200_201_original_sources_rechecked':True,
        'previous_252_254_wrong_byte_register_PE_shifts':bad_siblings,
        'previous_255_256_257_native_case_sources_rechecked':older_sprites,
        'previous_258_complete_native_case_rechecked':check258,
        'previous_259_correct_sparse_physical_case_rechecked':check259,
        'original_common_46B_getter_GPR_error_offsets':wrong_tail,
        'all_five_original_901B_afterRET_packed_tables_reverified':True,
        'original_separate_switch_afterRET_DATA_B':901,
        'native_whole_giant_exact':False,
        'new_accepted_whole_callable_CODE_B':0,
        'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(output,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['native_whole_giant_exact'] is False
    print('F884 original 2BC huge game state 803B/228x86/22 real typed PE fields with DOUBLE gravity, native phase7/9, 453B50 sprite346, stage5 FILD/FSUBR -BC, stage8 FILD -C0 sprite80, true float,float,int motion. Bad equal-size FISUB and wrong short counter 802B full controls rejected. Complete fighter source 34775B/9794x86, 142 GPR+2 giant JMP bytes wrong, all 59 previous original PE game cases plus five 901B tables physically verified. Whole 46755B original NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F884 actual original 2BC whole-game PE proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
