#!/usr/bin/env python3
"""F894: physical 2DD original 535B/153x86, successor 2E4 not 2DE.

Original numeric 2DE jumps to common default 52CB25, giving
false 6358B extent; actual next physical handler is 2E4
52B466. Normal VC7.1 used int RandomBoundary455580(0,6)
returns EAX for original FILD EBP-10C, whereas short return
inserts nonnative MOVSX and generates 538B/154-x86.
Rebuild affected 46KB father only. Check full 535B physical
original, all 14 PE calls/globals, previous 69 complete game
state interiors/901B original packed tables and genuine
getter four GPR byte negative. No all-unit cold replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f894-scripted2dd'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[246,247,531,532]
FIELDS=(9,34,44,51,57,66,74,78,101,105,108,137,140,151)
OFFSETS=(26,139,170,194,211,254,278,290,356,368,386,483,493,526)
TARGETS=(0x453e20,0x65782c,0x659090,0x65782c,0x40fb40,
        0x40fa30,0x40fac0,0x455580,0x453c80,0x455580,
        0x6592a0,0x453a70,0x453d40,0x40fb40)
def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,filename):
    s=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(s is not None and s.loader is not None,'native original PE helper missing '+filename)
    m=importlib.util.module_from_spec(s);sys.modules[tag]=m;s.loader.exec_module(m);return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    p=R/'.analysis/f893-scripted2dc/Boss005214B0-F893-whole.cpp'
    receipt=R/'.analysis/f893-scripted2dc/verified-summary.json'
    if not p.exists() or not receipt.exists():
        cp=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-stage2dc-f893.py')],
              cwd=R,capture_output=True,text=True,timeout=1500)
        (O/'prior-f893-original.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'preceding original native 2DC PE source failed '+(cp.stdout+cp.stderr)[-690:])
    old=json.loads(receipt.read_text())
    need(old['generated_full_whole_source_CODE_B']==40552
         and old['original_complete_giant_exact'] is False,
         'prior original 2DC physical source receipt changed')
    cpp=p.read_text()
    method='short RandomBoundaryAt455580(int,int);'
    need(cpp.count(method)==1,'real native random helper source signature missing')
    cpp=cpp.replace(method,'int RandomBoundaryAt455580(int,int);',1)
    inc=(R/'probes/FighterScriptedStage2DDF894.inc').read_text()
    mark='        case 0x2DD: g_FighterProbeMarker = 734; break;'
    need(cpp.count(mark)==1 and inc.count('case 0x2DD:')==1
         and inc.count('return;')==2
         and 'RandomBoundaryAt455580(0,6)' in inc
         and 'float(RandomBoundaryAt455580(0,6))' in inc
         and 'S16(0x516)=RandomBoundaryAt455580(0,60)' in inc
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc
         and 'SpawnRawAt453C80(0x7F' in inc
         and 'SpawnDirectedAt453A70(0x335' in inc
         and 'SetAuxActionAt40FB40(24)' in inc,
         'original physical 2DD random float and native trajectory missing')
    prefix=('extern float g_F894VerticalStageAt00659090;\n'
            'extern float g_F894RandomHeightAt006592A0;\n')
    return prefix+cpp.replace(mark,'#include "FighterScriptedStage2DDF894.inc"',1)
def compile_one(src,tag):
    cpp=O/('Boss005214B0-F894-'+tag+'.cpp')
    obj=O/('Boss005214B0-F894-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=e,capture_output=True,text=True,timeout=330)
    (O/('compiler-'+tag+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'original game 2DD full normal VC7.1 '+tag+' failed '+(cp.stdout+cp.stderr)[-720:])
    return obj
def parse(rd,d,obj):
    code,refs=rd.object_function(obj,SYM);I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    marks=[j for j,x in enumerate(I) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x2e5')
           and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=153,
         'actual original physical 2E4 next source marker missing')
    return code,refs,I,ret,marks[0]

def main():
    rd=ld('f894rd','compare-coff-function.py')
    ac=ld('f894ac','report-fighter-action-handlers.py')
    f834=ld('f894f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f894f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f894f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f894f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f894f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f894f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f894f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f894f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f894f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f894f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f894f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f894f885','verify-scripted-fighter-stage2bd-f885.py')
    f886=ld('f894f886','verify-scripted-fighter-stage2be-f886.py')
    f888=ld('f894f888','verify-scripted-fighter-2c0-2c1-f888.py')
    f890=ld('f894f890','verify-scripted-fighter-full2c2-f890.py')
    f892=ld('f894f892','verify-scripted-fighter-stage2db-f892.py')
    f893=ld('f894f893','verify-scripted-fighter-stage2dc-f893.py')
    zero=ld('f894zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f894sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original Japanese whole fighter or afterRET data identity drifted')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    start=by[0x2dd]
    physical=min(v for v in by.values() if v>start)
    need(start==0x52b24f and physical==by[0x2e4]==0x52b466
         and by[0x2de]==0x52cb25
         and physical-start==535
         and by[0x2de]-start==6358,
         'original 2DD next PHYSICAL state2E4 vs numeric default2DE changed')
    raw=rd.pe_bytes_at(pe,start,physical-start)
    original=list(d.disasm(raw,start))
    need(len(raw)==535 and len(original)==153
         and original[105].op_str=='0x455580'
         and original[106].op_str.startswith('dword ptr [ebp - 0x10c],')
         and original[107].mnemonic=='fild'
         and original[108].op_str=='dword ptr [0x6592a0]'
         and original[137].op_str=='0x453a70'
         and original[140].op_str=='0x453d40'
         and original[64].op_str==original[152].op_str=='0x52cb4f',
         'original 2DD real FILD random int/EAX and native whole exits changed')
    obj=compile_one(source(),'whole')
    code,refs,I,ret,k=parse(rd,d,obj)
    need((ret,len(I),len(refs),len(code)-ret)==(41072,11584,1345,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'selected current original whole fighter VC7.1 source/PE/ABI changed')
    ds,ss,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(ds>0 and ss>0 and maps>0,'all five original packed 901B afterRET tables not validated')
    sec=I[k-153:k]
    result=f834.physical_case(rd,pe,d,code,refs,sec,by,0x2dd,535,14,BAD,0x2e4,f820)
    need(result['native_complete_x86']==153
         and result['original_native_enclosing_parent_JMP_exit_ordinals']==[64,152]
         and sec[64].op_str==sec[152].op_str==hex(ret-4)
         and sec[106].op_str.startswith('dword ptr [ebp - 0x10c],')
         and sec[107].mnemonic=='fild'
         and sec[105].mnemonic=='call'
         and sec[108].mnemonic=='fadd',
         'native original 2DD proper EAX/FILD or 2 whole giant exits mismatched')
    lo=sec[0].address;ff=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x2dd],ff,lo,14)
    need(len(mask)==56,'fourteen original physical native PE field positions not verified')
    offsets=[]
    for j,target in zip(FIELDS,TARGETS):
        a,b=original[j],sec[j]
        found=[r for r in ff if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and found[0]['offset']-lo==a.address-by[0x2dd]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                   else f'dword ptr [0x{target:x}]'),
             'native 2DD original physical PE field target/type differs '+str(j))
        offsets.append(found[0]['offset']-lo)
    need(offsets==list(OFFSETS),'actual fourteen original 2DD source COFF physical locations changed')
    # Real short-return false source generates an extra MOVSX and
    # changes complete original native case length 535->538B,
    # even though numeric successor is a distant default handler.
    cpp=source()
    good='int RandomBoundaryAt455580(int,int);'
    need(cpp.count(good)==1,'actual ABI int random return prototype missing')
    badobj=compile_one(cpp.replace(good,'short RandomBoundaryAt455580(int,int);',1),
                       'wrong-short-random-return')
    bc,br,bI,bret,bk=parse(rd,d,badobj)
    bs=bI[bk-154:bk]
    need((bret,len(bI),len(br),len(bc)-bret)==(41075,11585,1345,901)
         and bs[-1].address+bs[-1].size-bs[0].address==538
         and bs[106].mnemonic=='movsx'
         and original[106].mnemonic=='mov',
         'wrong short return must introduce nonnative MOVSX 538B/154x86')
    # The expanded real return type must not silently break
    # previous original 2DB and 2DC complete function codegen.
    prev=json.loads((R/'.analysis/f893-scripted2dc/verified-summary.json').read_text())
    old=prev['preceding_46_earlier_native_game_cases_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'original earlier 46 native game states missing')
    prev_count=(107+107+149+177+80+207+205+60+60+228+239+136+138+85+81+608+20+162+188)
    early_end=k-153-prev_count
    before=I[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    pos=0;early=[]
    for j,x in enumerate(old):
        a=int(x['case'],16)
        nxt=int(old[j+1]['case'],16) if j+1<len(old) else 0x1fd
        sg=before[pos:pos+x['native_complete_x86']];pos+=x['native_complete_x86']
        early.append(f834.physical_case(rd,pe,d,code,refs,sg,by,a,
                     x['native_whole_inner_B'],x['original_typed_PE_fields'],
                     x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if a==0x1a0:
            need(sg[3].op_str==sg[7].op_str==hex(sg[22].address),
                 'native 1A0 actual stage0 mul guard changed')
    need(pos==len(before),'46 early original physical case interiors truncated')
    late=I[early_end:k-153]
    one=late[:107]
    origfd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(one[-1].address+one[-1].size-one[0].address==385
         and origfd[99].size==6 and one[99].size==5
         and one[100].op_str==hex(one[104].address),
         '1FD original one-byte CMP negative/owner CFG changed')
    at=107
    for a,nxt,n,nb,nf,bad in (
       (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,149,533,9,f875.BAD),
       (0x200,0x201,177,634,10,f877.BAD),
       (0x201,0x252,80,267,8,f878.BAD)):
        sg=late[at:at+n];at+=n
        f834.physical_case(rd,pe,d,code,refs,sg,by,a,nb,nf,bad,nxt,f820)
    shifts=[]
    for a,nxt,nb,n,sb,_ in f879.CASES:
        sg=late[at:at+n];at+=n;low=sg[0].address;high=sg[-1].address+sg[-1].size
        arr=[r for r in refs if low<=r['offset']<high]
        need(high-low==sb and len(arr)==6,
             'previous 252/254 original one-byte compiler phase changed')
        if a==0x253:
            f834.physical_case(rd,pe,d,code,refs,sg,by,a,260,6,f879.BAD_253,0x254,f820)
        else:
            na=list(d.disasm(rd.pe_bytes_at(pe,by[a],nb),by[a]))
            need(nb-sb==(1 if a==0x252 else -1)
                 and all(r['offset']-low==
                   na[next(j for j,z in enumerate(sg) if z.address<=r['offset']<z.address+z.size)].address-by[a]+
                   na[next(j for j,z in enumerate(sg) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                   for r in arr),
                 'native original 252/254 physical PE shifts cannot be hidden')
            shifts.append({'case':hex(a),'native_B':nb,'source_B':sb})
    for a,nxt,nb,n,nf in f880.CASES:
        sg=late[at:at+n];at+=n
        f834.physical_case(rd,pe,d,code,refs,sg,by,a,nb,nf,f880.BAD[a],nxt,f820)
    later=[
       (0x258,0x259,60,206,6,f881.BAD),
       (0x259,0x2bc,60,206,6,f883.BAD),
       (0x2bc,0x2bd,228,803,22,f884.BAD),
       (0x2bd,0x2be,239,855,24,f885.WRONG),
       (0x2be,0x2bf,136,461,15,f886.BAD),
       (0x2bf,0x2c0,138,473,15,[469,470]),
       (0x2c0,0x2c1,85,288,11,f888.BAD[0x2c0]),
       (0x2c1,0x2c2,81,276,11,f888.BAD[0x2c1]),
       (0x2c2,0x2c3,608,2274,50,f890.EXPECTED_WRONG),
       (0x2c3,0x2db,20,69,4,[65,66]),
       (0x2db,0x2dc,162,556,13,f892.WRONG),
       (0x2dc,0x2dd,188,660,17,f893.BAD)]
    for a,nxt,n,nb,nf,bad in later:
        sg=late[at:at+n];at+=n
        f834.physical_case(rd,pe,d,code,refs,sg,by,a,nb,nf,bad,nxt,f820)
    need(at==len(late),'69 preceding original source-backed native states not contiguous')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
           [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tailwrong=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(tailwrong==[10,12,16,19],
         'new whole 2DD native getter actual GPR phase changed')
    out={'original_giant':'0x005214B0',
       'native_original_callable_CODE_B':46755,
       'generated_new_whole_source_CODE_B':ret,
       'original_numeric_2DE_handler':'0x0052CB25',
       'real_physical_next_after_2DD':'0x0052B466',
       'false_numeric_2DD_extent_B':6358,
       'true_native_original_2DD_complete_CODE_B':535,
       'true_original_2DD_native_complete_case':result,
       'real_original_2DD_physical_PE_field_offsets':offsets,
       'native_random_Boundary455580_int_return_full_EAX':True,
       'real_native_2DD_FILD_EBP_slot':'-0x10C',
       'false_short_random_return_nonnative_full_case_B':538,
       'false_short_random_return_nonnative_x86':154,
       'native_2DD_real_GPR_and_inner_branch_wrong_B':0,
       'native_2DD_actual_outer_giant_JMP_wrong_offsets':BAD,
       'previous_46_original_source_cases_physically_reverified':early,
       'previous_1FD_true_one_byte_CMP_negative':True,
       'previous_252_254_original_PE_offset_shifts':shifts,
       'all_previous_69_game_source_case_interiors_checked':True,
       'native_shared_getter_46B_four_GPR_wrong_offsets':tailwrong,
       'original_five_packed_901B_afterRET_tables_verified':True,
       'original_afterRET_separate_DATA_B':901,
       'native_whole_fighter_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['native_whole_fighter_exact'] is False
    print('F894 native 2DD original PHYSICAL 535B/153x86/14 PE calls, next original handler 2E4 at 52B466 (NOT numeric 2DE default at 52CB25 / false 6358B). Native int returning Random455580 EAX goes to FILD EBP-10C; wrong short return adds MOVSX 538B/154x86. Whole current fighter 41072B/11584x86, four enclosing giant JMP byte differences, 69 original earlier cases and 901B packed tables reverified. Full original 46755B fighter NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F894 original 2DD entire physical PE proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
