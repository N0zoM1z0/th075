#!/usr/bin/env python3
"""F891: actual 2C3 69B/20x86/4 physical native PE calls in whole fighter.

Native Reset, getter match and truly used +4E0 status choose action0
or action1, with correctly nested JNE/JMP and final giant epilogue.
Wrong !zero and wrong member+4DC are full-source equal-length
but genuine nonrelocation byte mismatches.
ONE touched whole source parent rebuilt. Previous 2C2 2274B/
608x86/50 physical fields and original 65 preceding inner
states, common getter and five 901B afterRET tables checked.
Still NONEXACT entire 46755B father: never credit short inner case.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f891-scripted2c3'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
FIELD_ORDS=(1,3,14,18)
FIELD_OFFS=(4,12,48,60)
TARGETS=(0x453e20,0x40fa30,0x40fac0,0x40fac0)

def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(spec is not None and spec.loader is not None,'missing original PE helper '+name)
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m);return m
def native_source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f890-scripted-2c2/Boss005214B0-F890-whole.cpp'
    receipt=R/'.analysis/f890-scripted-2c2/verified-summary.json'
    if not prev.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-full2c2-f890.py')],
              cwd=R,capture_output=True,text=True,timeout=1650)
        (O/'f890-prior-original.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'preceding original 2C2 native source not verified '+(cp.stdout+cp.stderr)[-740:])
    old=json.loads(receipt.read_text())
    need(old['generated_new_whole_source_CODE_B']==39312
         and old['entire_original_callable_giant_exact'] is False
         and old['native_2C2_physically_typed_original_PE_field_count']==50,
         'previous 2C2 native entire original source receipt differs')
    cpp=prev.read_text()
    marker='        case 0x2C3: g_FighterProbeMarker = 708; break;'
    inc=(R/'probes/FighterScriptedTransition2C3F891.inc').read_text()
    need(cpp.count(marker)==1 and inc.count('case 0x2C3:')==1
         and inc.count('return;')==1
         and 'ResetAt453E20();' in inc
         and 'GetNativeActionAt40FA30()==S16(0x70)' in inc
         and 'if (I32(0x4E0)==0)' in inc
         and 'SetNativeActionAt40FAC0(0)' in inc
         and 'SetNativeActionAt40FAC0(1)' in inc,
         'original 2C3 true short transition/whole giant source changed')
    return cpp.replace(marker,'#include "FighterScriptedTransition2C3F891.inc"',1)
def compile_one(cpp,tag):
    cppfile=O/('Boss005214B0-F891-'+tag+'.cpp')
    obj=O/('Boss005214B0-F891-'+tag+'.obj')
    cppfile.write_text(cpp)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cppfile),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,capture_output=True,text=True,env=e,timeout=330)
    (O/('compiler-'+tag+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'original short case2C3 normal VC7.1 full '+tag+' failed '+(run.stdout+run.stderr)[-710:])
    return obj
def parsed(rd,d,obj):
    code,refs=rd.object_function(obj,SYM);I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    marks=[j for j,x in enumerate(I) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x2dc')
         and any('g_FighterProbeMarker' in r['symbol']
                 and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=20,
         'real next original 2DB marker not unique')
    return code,refs,I,ret,marks[0]

def main():
    rd=ld('f891rd','compare-coff-function.py')
    ac=ld('f891ac','report-fighter-action-handlers.py')
    f834=ld('f891f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f891f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f891f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f891f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f891f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f891f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f891f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f891f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f891f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f891f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f891f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f891f885','verify-scripted-fighter-stage2bd-f885.py')
    f886=ld('f891f886','verify-scripted-fighter-stage2be-f886.py')
    f888=ld('f891f888','verify-scripted-fighter-2c0-2c1-f888.py')
    f890=ld('f891f890','verify-scripted-fighter-full2c2-f890.py')
    zero=ld('f891zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f891switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original entire Japanese PE fighter/afterRET packed DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    raw=rd.pe_bytes_at(pe,by[0x2c3],by[0x2db]-by[0x2c3])
    native=list(d.disasm(raw,by[0x2c3]))
    need((len(raw),len(native),by[0x2c3],by[0x2db])==(69,20,0x52ad4a,0x52ad8f)
         and native[10].op_str=='dword ptr [edx + 0x4e0], 0'
         and native[14].op_str==native[18].op_str=='0x40fac0'
         and native[11].op_str==hex(native[16].address)
         and native[8].op_str==hex(native[19].address)
         and native[-1].op_str=='0x52cb4f',
         'original actual 2C3 true 4E0 native control-flow and two action values changed')
    cpp=native_source()
    obj=compile_one(cpp,'whole')
    code,refs,I,ret,k=parsed(rd,d,obj)
    need((ret,len(I),len(refs),len(code)-ret)==(39366,11087,1304,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current complete original 2C3 normal VC7.1 frame and COFF changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'native all five 901B packed afterRET tables unverified')
    sec=I[k-20:k]
    shape=f834.physical_case(rd,pe,d,code,refs,sec,by,
                        0x2c3,69,4,[65,66],0x2db,f820)
    need(shape['native_complete_x86']==20
         and shape['original_native_enclosing_parent_JMP_exit_ordinals']==[19]
         and sec[-1].op_str==hex(ret-4)
         and sec[8].op_str==hex(sec[19].address)
         and sec[11].op_str==hex(sec[16].address)
         and sec[15].op_str==hex(sec[19].address),
         'original 2C3 target branch CFG/early JMP changed')
    lo=sec[0].address
    fs=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x2c3],fs,lo,4)
    offsets=[]
    for j,target in zip(FIELD_ORDS,TARGETS):
        a,b=native[j],sec[j]
        f=[r for r in fs if b.address<=r['offset']<b.address+b.size]
        need(len(f)==1 and f[0]['type']=='REL32'
             and f[0]['addend']==0 and f[0]['local_symbol_offset'] is None
             and f[0]['offset']-lo==a.address-by[0x2c3]+a.size-4
             and a.op_str==f'0x{target:x}',
             'physical original 2C3 PE call target/symbol shifted '+str(j))
        offsets.append(f[0]['offset']-lo)
    need(offsets==list(FIELD_OFFS),'native four original PE fields have wrong source positions')
    # Equal-length incorrect native C++ sources: wrong action
    # branch polarity and wrong actually observed member 4E0.
    parent=cpp
    inc=(R/'probes/FighterScriptedTransition2C3F891.inc').read_text()
    include='#include "FighterScriptedTransition2C3F891.inc"'
    negative_controls={}
    for tag,src_bad,expected in (
       ('wrong-branch',inc.replace('I32(0x4E0)==0','I32(0x4E0)!=0'),[40,65,66]),
       ('wrong-member',inc.replace('I32(0x4E0)','I32(0x4DC)'),[35,65,66])):
        need(src_bad!=inc and parent.count(include)==1,
             'could not construct original negative source')
        badobj=compile_one(parent.replace(include,src_bad,1),tag)
        bc,br,bI,bret,bk=parsed(rd,d,badobj)
        bs=bI[bk-20:bk];blo=bs[0].address
        bf=[r for r in br if blo<=r['offset']<bs[-1].address+bs[-1].size]
        bmask=f820.physical_fields(rd,raw,by[0x2c3],bf,blo,4)
        bad=[j for j in range(69) if j not in bmask and raw[j]!=bc[blo+j]]
        need((bret,len(bI),len(br),len(bc)-bret)==(39366,11087,1304,901)
             and bad==expected,
             'false same-size original 2C3 logic must produce real nonfield byte error '+tag)
        negative_controls[tag]=bad
    # In this newly enlarged whole object recheck ALL 66 earlier
    # real native sourced original game cases (including F890
    # original 2274B and its 50 typed original PE references).
    previous=json.loads((R/'.analysis/f890-scripted-2c2/verified-summary.json').read_text())
    old=previous['previous_46_original_PE_case_sources_reverified']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous 46 genuine original source-backed case receipts missing')
    previous_late=(107+107+149+177+80+207+205+60+60+228+239+136+138+85+81+608)
    early_end=k-20-previous_late
    early=I[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    cursor=0;all_earlier=[]
    for idx,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[idx+1]['case'],16) if idx+1<len(old) else 0x1fd
        part=early[cursor:cursor+x['native_complete_x86']]
        cursor+=x['native_complete_x86']
        all_earlier.append(f834.physical_case(rd,pe,d,code,refs,part,by,
               action,x['native_whole_inner_B'],x['original_typed_PE_fields'],
               x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(part[3].op_str==part[7].op_str==hex(part[22].address),
                 'original stage0 1A0 multiplier scope drifted')
    need(cursor==len(early),'46 original early case x86 intervals not contiguous')
    prior=I[early_end:k-20]
    origfd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    fd=prior[:107]
    need(fd[-1].address+fd[-1].size-fd[0].address==385
         and origfd[99].size==6 and fd[99].size==5
         and fd[100].op_str==hex(fd[104].address),
         '1FD native one-byte original CMP defect or corrected owner CFG drifted')
    cursor=107
    for action,nxt,n,nb,nf,bad in (
       (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,149,533,9,f875.BAD),
       (0x200,0x201,177,634,10,f877.BAD),
       (0x201,0x252,80,267,8,f878.BAD)):
        part=prior[cursor:cursor+n];cursor+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,action,nb,nf,bad,nxt,f820)
    native_size_shifts=[]
    for action,nxt,nb,n,sb,_ in f879.CASES:
        part=prior[cursor:cursor+n];cursor+=n
        orig_2=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
        lo2=part[0].address;hi2=part[-1].address+part[-1].size
        ff=[r for r in refs if lo2<=r['offset']<hi2]
        need(hi2-lo2==sb and len(ff)==6,
             'original 252/254 byte register phase moved')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,part,by,
                      action,260,6,f879.BAD_253,0x254,f820)
        else:
            need(nb-sb==(1 if action==0x252 else -1)
                and all(r['offset']-lo2==
                  orig_2[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].address-by[action]+
                  orig_2[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                  for r in ff),
                  'original shifted 252/254 PE field positions must not claim exact')
            native_size_shifts.append(hex(action))
    for action,nxt,nb,n,nf in f880.CASES:
        part=prior[cursor:cursor+n];cursor+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,
                     action,nb,nf,f880.BAD[action],nxt,f820)
    later=[
       (0x258,0x259,60,206,6,f881.BAD),
       (0x259,0x2bc,60,206,6,f883.BAD),
       (0x2bc,0x2bd,228,803,22,f884.BAD),
       (0x2bd,0x2be,239,855,24,f885.WRONG),
       (0x2be,0x2bf,136,461,15,f886.BAD),
       (0x2bf,0x2c0,138,473,15,[469,470]),
       (0x2c0,0x2c1,85,288,11,f888.BAD[0x2c0]),
       (0x2c1,0x2c2,81,276,11,f888.BAD[0x2c1]),
       (0x2c2,0x2c3,608,2274,50,f890.EXPECTED_WRONG)]
    for action,nxt,n,nb,nf,bad in later:
        part=prior[cursor:cursor+n];cursor+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,action,nb,nf,bad,nxt,f820)
    need(cursor==len(prior),'all 66 original previous game states must be rechecked contiguously')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
              [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    # Adding one ACTUAL short game handler after F890 flips the
    # whole VC7.1 GPR allocator phase again. This is genuine source
    # nonrelocation mismatch, not a copied old F890 result.
    need(wrong_tail==[10,12,16,19] and len(tmask)==12,
         'native common getter real four register byte errors changed')
    out={'original_giant':'0x005214B0',
       'native_entire_callable_CODE_B':46755,
       'new_generated_full_source_CODE_B':ret,
       'native_2C3_complete_inner':shape,
       'original_2C3_PE_field_offsets':offsets,
       'native_real_2C3_owner_status':'this+0x4E0',
       'false_equal_size_Cpp_branch_and_owner_controls':negative_controls,
       'genuine_2C3_GPR_and_local_Jcc_wrong_B':0,
       'genuine_enclosing_giant_JMP_wrong_offsets':[65,66],
       'previous_46_original_case_sources_rechecked':all_earlier,
       'previous_1FD_original_CMP_one_byte_negative':True,
       'previous_252_254_native_PE_field_shifts':native_size_shifts,
       'all_previous_66_complete_game_cases_physically_rechecked':True,
       'native_original_2274B_2C2_reverified':True,
       'common_getter_46B_original_nonfield_match':'30/34',
       'common_getter_real_GPR_wrong_offsets':wrong_tail,
       'all_five_original_packed_901B_tables_physically_reverified':True,
       'original_separate_afterRET_DATA_B':901,
       'native_original_full_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['native_original_full_giant_exact'] is False
    print('F891 original 2C3 full 69B/20x86/4 physically typed PE calls, native Reset/getter and real +4E0 zero guard selects action0/1. GPR/branch identical; only two original giant JMP bytes different. Whole fighter 39366B/11087x86, all previous 66 original native cases incl full 2274B2C2, five 901B packed DATA and 46B getter genuine four GPR negative bytes rechecked. Original 46755B father NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F891 full native original 2C3 physical proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
