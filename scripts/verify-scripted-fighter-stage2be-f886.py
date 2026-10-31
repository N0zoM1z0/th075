#!/usr/bin/env python3
"""F886: original native 2BE 461B/136x86/15 actual PE fields.

True stage2 F32->signed short conversion produces two
native __ftol2 calls at actual original 6406AC. Sprite33C
through actual 453B50 uses RAW int Y, unlike previous
2BD with floating Y. Declaring float Y causes an extra
FILD/FSTP pair and wrong complete original x86 size,
despite similar behavior. Stage10 animation1F4/Prepare6,
stage11 InitTrajectory5/raw sprite7F. Compile only
the current giant VC7.1 parent, compare full 461B and
all 15 real PE destinations and recheck earlier 61
original source-backed cases/five 901B packed DATA.
Full original giant NONEXACT; no inner case exact CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f886-scripted-stage2be'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,23,27,35,38,45,49,74,76,80,83,97,101,104,108,111,118,122,125,134,138,141,169,172,184,187,195,198,200,202,205,218,222,225,228,240,243,260,263,271,275,281,284,457,458]
FIELDS={
 15:(0x453e20,'ResetAt453E20'),
 17:(0x40fa30,'GetNativeActionAt40FA30'),
 25:(0x40fac0,'SetNativeActionAt40FAC0'),
 42:(0x453e80,'AnimatePushAt453E80'),
 45:(0x453d60,'PrepareActionAt453D60'),
 48:(0x657888,'g_ContactProjectionAt00657888'),
 57:(0x659470,'g_F884Stage5YAt00659470'),
 71:(0x453c80,'SpawnAt453C80'),
 74:(0x6406ac,'__ftol2'),
 79:(0x6406ac,'__ftol2'),
 96:(0x453b50,'SpawnExtraRawYAt453B50'),
 107:(0x46d000,'StartAnimationAt46D000'),
 110:(0x453d40,'PrepareActionAt453D40'),
 121:(0x453e60,'InitTrajectoryAt453E60'),
 134:(0x453c80,'SpawnRawAt453C80')}
OFFSETS=[60,68,92,154,164,179,209,255,266,287,337,373,383,419,452]

def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'original PE helper missing '+name)
    mod=importlib.util.module_from_spec(spec);sys.modules[tag]=mod;spec.loader.exec_module(mod);return mod

def source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f885-scripted-stage2bd/Boss005214B0-F885-whole.cpp'
    receipt=R/'.analysis/f885-scripted-stage2bd/verified-summary.json'
    if not prior.exists() or not receipt.exists():
        p=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-stage2bd-f885.py')],
              cwd=R,capture_output=True,text=True,timeout=1500)
        (O/'f885-original-fallback.log').write_text(p.stdout+p.stderr)
        need(p.returncode==0,'previous original 2BD whole source proof failed '+(p.stdout+p.stderr)[-740:])
    old=json.loads(receipt.read_text())
    need(old['generated_current_whole_source_CODE_B']==35615
         and old['entire_original_giant_exact'] is False,
         'prior F885 real whole PE receipt changed')
    src=prior.read_text()
    decl='void SpawnExtraAt453B50(int,int,float,char,int,int,int);'
    need(src.count(decl)==1,'prior 2BD real floatY sprite declaration moved')
    src=src.replace(decl,decl+' void SpawnExtraRawYAt453B50(int,int,int,char,int,int,int);',1)
    marker='        case 0x2BE: g_FighterProbeMarker = 703; break;'
    frag=(R/'probes/FighterScriptedStage2BEF886.inc').read_text()
    need(src.count(marker)==1 and frag.count('case 0x2BE:')==1
         and frag.count('return;')==1
         and frag.count('static_cast<signed short>(F32(')==2
         and 'S16(0xF00)=static_cast<signed short>(F32(0x44))' in frag
         and 'S16(0xF02)=static_cast<signed short>(F32(0x48))' in frag
         and 'SpawnExtraRawYAt453B50(0x33C,I32(0x44),I32(0x48)' in frag
         and 'SpawnAt453C80(0x73' in frag
         and 'StartAnimationAt46D000(0x1F4)' in frag
         and 'PrepareActionAt453D40(6)' in frag
         and 'InitTrajectoryAt453E60(5.0f)' in frag
         and 'SpawnRawAt453C80(0x7F' in frag,
         'real original 2BE native short conversion/raw int Y/stage game actions changed')
    return src.replace(marker,'#include "FighterScriptedStage2BEF886.inc"',1)

def compile_one(src,tag='whole'):
    cpp=O/('Boss005214B0-F886-'+tag+'.cpp')
    obj=O/('Boss005214B0-F886-'+tag+'.obj')
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=310)
    (O/('compiler-'+tag+'.log')).write_text(p.stdout+p.stderr)
    need(p.returncode==0,'native 2BE normal VC7.1 whole fighter '+tag+' compiler failed '+(p.stdout+p.stderr)[-790:])
    return obj

def parse(rd,d,obj):
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    m=[j for j,x in enumerate(I) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x2c0')
         and any('g_FighterProbeMarker' in r['symbol']
                 and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(m)==1 and m[0]>=136,'next native 2BF game case source marker missing')
    return code,refs,I,ret,m[0]

def main():
    rd=ld('f886rd','compare-coff-function.py')
    ac=ld('f886ac','report-fighter-action-handlers.py')
    f834=ld('f886f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f886f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f886f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f886f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f886f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f886f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f886f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f886f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f886f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f886f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f886f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f886f885','verify-scripted-fighter-stage2bd-f885.py')
    zero=ld('f886zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f886switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original fighter complete CODE/afterRET DATA identity drifted')
    report,mapping=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapping}
    native_raw=rd.pe_bytes_at(pe,by[0x2be],by[0x2bf]-by[0x2be])
    original=list(d.disasm(native_raw,by[0x2be]))
    need((by[0x2be],by[0x2bf],len(native_raw),len(original))==
         (0x529e8e,0x52a05b,461,136)
         and original[13].op_str.endswith(', 6')
         and original[74].mnemonic=='call' and original[74].op_str=='0x6406ac'
         and original[79].mnemonic=='call' and original[79].op_str=='0x6406ac'
         and original[89].mnemonic=='mov' and original[89].size==3
         and original[96].op_str=='0x453b50'
         and original[105].op_str=='0x1f4'
         and original[107].op_str=='0x46d000'
         and original[110].op_str=='0x453d40'
         and original[121].op_str=='0x453e60'
         and original[132].op_str=='0x7f'
         and original[134].op_str=='0x453c80'
         and original[-1].op_str=='0x52cb4f',
         'original native 2BE two F32 to signed-short helpers, real rawY or stages changed')
    src=source()
    obj=compile_one(src)
    code,refs,I,ret,k=parse(rd,d,obj)
    need((ret,len(I),len(refs),len(code)-ret)==(36061,10165,1218,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'F886 normal whole VC7.1 original source/CODE/COFF/ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all five native original 901B packed tables missing')
    sec=I[k-136:k]
    current=f834.physical_case(rd,pe,d,code,refs,sec,by,0x2be,461,15,BAD,0x2bf,f820)
    need(current['native_complete_x86']==136
         and current['original_native_enclosing_parent_JMP_exit_ordinals']==[135]
         and sec[-1].op_str==hex(ret-4)
         and sec[74].mnemonic==sec[79].mnemonic=='call'
         and sec[89].mnemonic=='mov' and sec[89].size==3
         and sec[96].mnemonic=='call',
         'original 2BE complete native float->short x86/one outer giant exit differs')
    lo=sec[0].address
    fields=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    masked=f820.physical_fields(rd,native_raw,by[0x2be],fields,lo,15)
    need(len(masked)==60,'fifteen real native PE fields not independently checked')
    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],sec[ordinal]
        fs=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(fs)==1 and fs[0]['addend']==0
             and fs[0]['local_symbol_offset'] is None
             and fs[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in fs[0]['symbol']
             and fs[0]['offset']-lo==a.address-by[0x2be]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                  else f'dword ptr [0x{target:x}]'),
             'native original 2BE actual PE target/offset or __ftol2 helper wrong '+str(ordinal))
        offsets.append(fs[0]['offset']-lo)
    need(offsets==OFFSETS and len(BAD)==50 and BAD[-2:]==[457,458],
         'original 2BE real native register/JMP differences changed')
    need(all(r['symbol']=='__ftol2'
             for r in fields if any(sec[j].address<=r['offset']<sec[j].address+sec[j].size for j in (74,79))),
         'both native physical 6406AC calls must come from real VC7.1 __ftol2 source')
    # NEGATIVE complete source: inherited 2BD float Y method changes
    # the real 2BE third argument to float and inserts FILD/FSTP,
    # giving one more instruction and 3 extra B, not an exact native
    # case. Reject despite the superficially same call target.
    inc=(R/'probes/FighterScriptedStage2BEF886.inc').read_text()
    actual='SpawnExtraRawYAt453B50(0x33C,I32(0x44),I32(0x48),'
    incorrect='SpawnExtraAt453B50(0x33C,I32(0x44),I32(0x48),'
    need(inc.count(actual)==1
         and src.count('#include "FighterScriptedStage2BEF886.inc"')==1,
         'native original 2BE rawY source insertion not unique')
    badsrc=src.replace('#include "FighterScriptedStage2BEF886.inc"',
                       inc.replace(actual,incorrect,1),1)
    badobj=compile_one(badsrc,tag='wrong-float-Y')
    badcode,badrefs,badI,badret,badk=parse(rd,d,badobj)
    badseg=badI[badk-137:badk]
    need((badret,len(badI),len(badrefs),len(badcode)-badret)==(36064,10166,1218,901)
         and (badseg[-1].address+badseg[-1].size-badseg[0].address,len(badseg))==(464,137)
         and original[89].mnemonic=='mov'
         and badseg[89].mnemonic=='fild'
         and badseg[91].mnemonic=='fstp',
         'wrong float Y must yield one added native-FILD/FSTP, 464B 137x86')
    # Recheck previous 61 original sourced state intervals in THIS
    # one newly compiled full parent, without mass replay.
    previous=json.loads((R/'.analysis/f885-scripted-stage2bd/verified-summary.json').read_text())
    old=previous['preceding_46_original_PE_game_cases_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous 46 source-backed original states lost')
    prevbd=I[k-136-239:k-136]
    prevbc=I[k-136-239-228:k-136-239]
    f834.physical_case(rd,pe,d,code,refs,prevbd,by,
                       0x2bd,855,24,f885.WRONG,0x2be,f820)
    f834.physical_case(rd,pe,d,code,refs,prevbc,by,
                       0x2bc,803,22,f884.BAD,0x2bd,f820)
    early_end=k-136-239-228-(107+107+149+177+80+207+205+60+60)
    beginning=I[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    pos=0;older=[]
    for j,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[j+1]['case'],16) if j+1<len(old) else 0x1fd
        st=beginning[pos:pos+x['native_complete_x86']]
        pos+=x['native_complete_x86']
        older.append(f834.physical_case(rd,pe,d,code,refs,st,by,
                     action,x['native_whole_inner_B'],x['original_typed_PE_fields'],
                     x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(st[3].op_str==st[7].op_str==hex(st[22].address),
                 'stage0 native 1A0 multiplier condition scope lost')
    need(pos==len(beginning),'46 preceding real native inner states not contiguous')
    misc=I[early_end:k-136-239-228-(207+205+60+60)]
    fd,fe,ff,st200,st201=misc[:107],misc[107:214],misc[214:363],misc[363:540],misc[540:]
    origfd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(fd[-1].address+fd[-1].size-fd[0].address==385
         and origfd[99].size==6 and fd[99].size==5
         and fd[100].op_str==hex(fd[104].address),
         'earlier 1FD real one-byte CMP and correct original CFG lost')
    for action,nxt,st,nb,nf,bad in [
       (0x1fe,0x1ff,fe,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,ff,533,9,f875.BAD),
       (0x200,0x201,st200,634,10,f877.BAD),
       (0x201,0x252,st201,267,8,f878.BAD)]:
        f834.physical_case(rd,pe,d,code,refs,st,by,action,nb,nf,bad,nxt,f820)
    triple=I[k-136-239-228-(207+205+60+60):k-136-239-228-(205+60+60)]
    pos=0;incorrect_slots=[]
    for action,nxt,nb,nx,sb,_ in f879.CASES:
        st=triple[pos:pos+nx];pos+=nx;low=st[0].address
        high=st[-1].address+st[-1].size
        ff=[r for r in refs if low<=r['offset']<high]
        need(high-low==sb and len(ff)==6,'old 252..254 byte register phase source changed')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,st,by,
                               action,260,6,f879.BAD_253,0x254,f820)
        else:
            native=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and native[10].mnemonic==st[10].mnemonic=='sub'
                 and all(r['offset']-low==
                   native[next(j for j,z in enumerate(st) if z.address<=r['offset']<z.address+z.size)].address-by[action]+
                   native[next(j for j,z in enumerate(st) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                   for r in ff),
                 'true original 252/254 PE relocation shifts still wrong, no exact credit')
            incorrect_slots.append({'case':hex(action),'original_B':nb,'source_B':sb,'not_exact':True})
    need(pos==len(triple),'previous 252..254 physical case x86 intervals overlap')
    prior_3=I[k-136-239-228-(205+60+60):k-136-239-228-(60+60)]
    pos=0;verified3=[]
    for a,nxt,nb,nx,nf in f880.CASES:
        st=prior_3[pos:pos+nx];pos+=nx
        verified3.append(f834.physical_case(rd,pe,d,code,refs,st,by,
                           a,nb,nf,f880.BAD[a],nxt,f820))
    need(pos==len(prior_3),'prior three sprite37 native cases missing')
    st258=I[k-136-239-228-120:k-136-239-228-60]
    st259=I[k-136-239-228-60:k-136-239-228]
    f834.physical_case(rd,pe,d,code,refs,st258,by,
                       0x258,206,6,f881.BAD,0x259,f820)
    f834.physical_case(rd,pe,d,code,refs,st259,by,
                       0x259,206,6,f883.BAD,0x2bc,f820)
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
                [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tail_wrong=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(tail_wrong==[10,12,16,19],
         'native real 46B getter GPR phase no longer as expected')
    output={'original_giant_fighter':'0x005214B0',
       'real_original_callable_CODE_B':46755,
       'generated_current_whole_source_CODE_B':ret,
       'new_native_2BE_complete_game_case':current,
       'real_native_2BE_typed_PE_offsets':offsets,
       'real_original_6406AC_two_Cpp_ftol2_calls':True,
       'native_true_sprite33C_method_has_raw_integer_Y':True,
       'false_float_Y_2BE_source_entire_case_CODE_B':464,
       'false_float_Y_2BE_source_entire_x86':137,
       'new_2BE_native_GPR_operand_wrong_B':48,
       'new_2BE_original_giant_JMP_operand_wrong_offsets':[457,458],
       'prior_2BD_and_2BC_original_full_cases_physically_checked':True,
       'prior_46_original_native_cases_physically_checked':older,
       'prior_1FD_one_byte_CMP_error_retained':True,
       'prior_1FE_1FF_200_201_source_native_verified':True,
       'prior_252_254_one_byte_original_PE_shifts':incorrect_slots,
       'prior_255_256_257_complete_cases_checked':verified3,
       'prior_258_259_real_native_bounds_checked':True,
       'common_original_46B_getter_genuine_GPR_errors':tail_wrong,
       'all_five_native_901B_afterRET_jump_tables_checked':True,
       'original_afterRET_separate_DATA_B':901,
       'original_entire_whole_giant_exact':False,
       'newly_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(output,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_whole_giant_exact'] is False
    print('F886 actual original 2BE full 461B/136x86/15 true PE fields; native two float->SHORT cast calls C++ __ftol2 -> original 6406AC, sprite33C requires integer Y else wrong complete 464B/137x86. Whole fighter source 36061B/10165x86; 48 genuine GPR +two giant JMP bytes still wrong; all 61 preceding native cases and five 901B packed tables checked. Entire original giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F886 native 2BE original whole game PE FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
