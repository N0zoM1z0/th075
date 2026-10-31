#!/usr/bin/env python3
"""F893: original 2DC entire 660B/188x86/17 PE fields in full fighter.

Native stage2 sprite33B, stage13 sprite338,
two authentic independent POS/POS48 ground tests
and actual <= compare after short falling vertical impulse.
Native auxiliary24 ground landing is early entire parent exit;
random range0..30 is GUARDED by current-action match,
stage13 short F00<1/aux2, stage15 height12.5 and speed15,
stage24 aux22. The false < vs <=, unguarded random and
wrong sprite preserve same 660B/188x86 but change true
original machine operand bytes. Rebuild ONLY touched full
VC7.1 giant, verify 17 original PE fields and all previous
68 native source game cases, five packed 901B afterRET tables.
Never claim separate case or whole original exact CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f893-scripted2dc'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[427,428,656,657]
FIELD_ORDS=(9,44,47,68,71,74,80,85,93,103,110,116,125,133,137,159,186)
FIELD_OFFS=(26,163,173,232,242,254,273,291,320,351,375,392,435,459,471,553,651)
FIELD_DEST=(0x453e20,0x453a70,0x453d40,0x453a70,0x453d40,
 0x65782c,0x657478,0x65782c,0x65782c,0x6598b0,0x65782c,
 0x40fb40,0x40fa30,0x40fac0,0x455580,0x40fb40,0x40fb40)

def need(v,msg):
    if not v:raise ValueError(msg)
def ld(k,name):
    s=importlib.util.spec_from_file_location(k,R/'scripts'/name)
    need(s is not None and s.loader is not None,'missing native PE helper '+name)
    m=importlib.util.module_from_spec(s);sys.modules[k]=m;s.loader.exec_module(m);return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    p=R/'.analysis/f892-scripted2db/Boss005214B0-F892-whole.cpp'
    receipt=R/'.analysis/f892-scripted2db/verified-summary.json'
    if not p.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
              str(R/'scripts/verify-scripted-fighter-stage2db-f892.py')],
              cwd=R,capture_output=True,text=True,timeout=1750)
        (O/'prior-f892-native.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'preceding 2DB true original whole source unavailable '+(cp.stdout+cp.stderr)[-690:])
    old=json.loads(receipt.read_text())
    need(old['generated_new_whole_source_CODE_B']==39907
         and old['entire_original_giant_exact'] is False,
         'previous 2DB full native C++ receipt changed')
    parent=p.read_text()
    mark='        case 0x2DC: g_FighterProbeMarker = 733; break;'
    inc=(R/'probes/FighterScriptedStage2DCF893.inc').read_text()
    need(parent.count(mark)==1 and inc.count('case 0x2DC:')==1
         and inc.count('return;')==2
         and 'SpawnDirectedAt453A70(0x33B' in inc
         and 'SpawnDirectedAt453A70(0x338' in inc
         and 'if (POS>g_ThresholdAt0065782C)' in inc
         and 'POS=POS-g_F893FloatFallAt00657478' in inc
         and 'POS48+POS54<=g_ThresholdAt0065782C' in inc
         and 'SetAuxActionAt40FB40(24)' in inc
         and 'S16(0x516)=RandomBoundaryAt455580(0,30)' in inc
         and '++S16(0xF00);' in inc
         and 'POS54=15.0f;' in inc
         and 'SetAuxActionAt40FB40(22)' in inc,
         'real native 2DC game stage/ground/random source changed')
    prefix=('extern float g_F893FloatFallAt00657478;\n'
            'extern float g_F893VerticalStageAt006598B0;\n')
    return prefix+parent.replace(mark,'#include "FighterScriptedStage2DCF893.inc"',1)
def compile_one(src,tag):
    cpp=O/('Boss005214B0-F893-'+tag+'.cpp')
    obj=O/('Boss005214B0-F893-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=e,capture_output=True,text=True,timeout=325)
    (O/('compiler-'+tag+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'current native 2DC full VC7.1 '+tag+' failed '+(run.stdout+run.stderr)[-700:])
    return obj
def parse(rd,d,obj):
    code,refs=rd.object_function(obj,SYM);I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    marks=[j for j,x in enumerate(I) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x2de')
         and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=188,
         'next physical 2DD state source marker missing')
    return code,refs,I,ret,marks[0]

def main():
    rd=ld('f893rd','compare-coff-function.py')
    ac=ld('f893ac','report-fighter-action-handlers.py')
    f834=ld('f893f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f893f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f893f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f893f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f893f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f893f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f893f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f893f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f893f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f893f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f893f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f893f885','verify-scripted-fighter-stage2bd-f885.py')
    f886=ld('f893f886','verify-scripted-fighter-stage2be-f886.py')
    f888=ld('f893f888','verify-scripted-fighter-2c0-2c1-f888.py')
    f890=ld('f893f890','verify-scripted-fighter-full2c2-f890.py')
    f892=ld('f893f892','verify-scripted-fighter-stage2db-f892.py')
    zero=ld('f893zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f893sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
          if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'real original fighter whole native CODE/901B afterRET identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    raw=rd.pe_bytes_at(pe,by[0x2dc],by[0x2dd]-by[0x2dc])
    native=list(d.disasm(raw,by[0x2dc]))
    need((len(raw),len(native),by[0x2dc],by[0x2dd])==
         (660,188,0x52afbb,0x52b24f)
         and native[42].op_str=='0x33b'
         and native[66].op_str=='0x338'
         and native[74].op_str=='dword ptr [0x65782c]'
         and native[80].op_str=='dword ptr [0x657478]'
         and native[103].op_str=='dword ptr [0x6598b0]'
         and native[116].op_str=='0x40fb40'
         and native[137].op_str=='0x455580'
         and native[186].op_str=='0x40fb40'
         and native[123].op_str==native[187].op_str=='0x52cb4f',
         'native 2DC actual double sprite/float ground physics stages changed')
    cpp=source()
    obj=compile_one(cpp,'whole')
    code,refs,I,ret,k=parse(rd,d,obj)
    need((ret,len(I),len(refs),len(code)-ret)==(40552,11433,1332,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'native 2DC entire compiled father PE/ABI/COFF changed')
    ds,ss,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(ds>0 and ss>0 and maps>0,
         'five separate original 901B packed afterRET DATA tables not verified')
    sec=I[k-188:k]
    checked=f834.physical_case(rd,pe,d,code,refs,sec,by,
                          0x2dc,660,17,BAD,0x2dd,f820)
    need(checked['native_complete_x86']==188
         and checked['original_native_enclosing_parent_JMP_exit_ordinals']==[123,187]
         and sec[123].op_str==sec[187].op_str==hex(ret-4)
         and native[110].mnemonic==sec[110].mnemonic=='fcomp'
         and sec[107].mnemonic=='mov'
         and sec[108].mnemonic=='fld'
         and sec[109].mnemonic=='fadd',
         'native 2DC original ground contact CFG or two giant exits differs')
    lo=sec[0].address
    f=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x2dc],f,lo,17)
    need(len(mask)==68,'native 2DC all 17 original physical field operand bytes not verified')
    offsets=[]
    for j,target in zip(FIELD_ORDS,FIELD_DEST):
        a,b=native[j],sec[j]
        found=[r for r in f if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and found[0]['offset']-lo==a.address-by[0x2dc]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                    else f'dword ptr [0x{target:x}]'),
             'native 2DC real Japanese PE call/global target or type changed '+str(j))
        offsets.append(found[0]['offset']-lo)
    need(offsets==list(FIELD_OFFS),
         'real original 2DC seventeen native physical PE operand offsets changed')
    # Three full normal VC7.1 negative controls with misleadingly
    # equal 660B/188-x86/17 fields but wrong game operands.
    inc=(R/'probes/FighterScriptedStage2DCF893.inc').read_text()
    include='#include "FighterScriptedStage2DCF893.inc"'
    bad_models={
       'wrong-ground-less':(inc.replace(
            'POS48+POS54<=g_ThresholdAt0065782C',
            'POS48+POS54<g_ThresholdAt0065782C'),[383,427,428,656,657]),
       'wrong-random-outside':(inc.replace(
            '''    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(0,30);
    }''',
            '''    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    S16(0x516)=RandomBoundaryAt455580(0,30);'''),
            [427,428,452,656,657]),
       'wrong-sprite33b':(inc.replace(
           'SpawnDirectedAt453A70(0x33B',
           'SpawnDirectedAt453A70(0x33A'),[155,427,428,656,657])}
    negative={}
    for tag,(altered,expected) in bad_models.items():
        need(altered!=inc and cpp.count(include)==1,'failed to create original wrong game source '+tag)
        c=compile_one(cpp.replace(include,altered,1),tag)
        bc,br,bI,bret,bk=parse(rd,d,c)
        bs=bI[bk-188:bk];blo=bs[0].address
        bf=[r for r in br if blo<=r['offset']<bs[-1].address+bs[-1].size]
        bmask=f820.physical_fields(rd,raw,by[0x2dc],bf,blo,17)
        wrong=[j for j in range(660) if j not in bmask and raw[j]!=bc[blo+j]]
        need((bret,len(bI),len(br),len(bc)-bret)==(40552,11433,1332,901)
             and wrong==expected,'false equal-length native 2DC game source must be rejected '+tag)
        negative[tag]=wrong
    # The same freshly compiled whole parent physically rechecks
    # all 68 preceding original native game case interiors.
    previous=json.loads((R/'.analysis/f892-scripted2db/verified-summary.json').read_text())
    old=previous['previous_46_original_native_cases_reverified']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous 46 original native case receipts missing')
    late_count=(107+107+149+177+80+207+205+60+60+228+239+136+138+85+81+608+20+162)
    early_end=k-188-late_count
    original_prefix=I[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    pos=0;oldchecks=[]
    for idx,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[idx+1]['case'],16) if idx+1<len(old) else 0x1fd
        s=original_prefix[pos:pos+x['native_complete_x86']]
        pos+=x['native_complete_x86']
        oldchecks.append(f834.physical_case(rd,pe,d,code,refs,s,by,
              action,x['native_whole_inner_B'],x['original_typed_PE_fields'],
              x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(s[3].op_str==s[7].op_str==hex(s[22].address),
                 'original stage0 1A0 guarded scale changed')
    need(pos==len(original_prefix),'earlier 46 genuine original case intervals not contiguous')
    late=I[early_end:k-188]
    fd=late[:107]
    original_fd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(fd[-1].address+fd[-1].size-fd[0].address==385
         and original_fd[99].size==6 and fd[99].size==5
         and fd[100].op_str==hex(fd[104].address),
         'native original 1FD true one-byte CMP and owner-status negative lost')
    at=107
    for a,nxt,n,nb,nf,bad in (
       (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,149,533,9,f875.BAD),
       (0x200,0x201,177,634,10,f877.BAD),
       (0x201,0x252,80,267,8,f878.BAD)):
        s=late[at:at+n];at+=n
        f834.physical_case(rd,pe,d,code,refs,s,by,a,nb,nf,bad,nxt,f820)
    shifts=[]
    for a,nxt,nb,n,sb,_ in f879.CASES:
        s=late[at:at+n];at+=n;low=s[0].address;hi=s[-1].address+s[-1].size
        ff=[r for r in refs if low<=r['offset']<hi]
        need(hi-low==sb and len(ff)==6,'native byte phase 252/254 changed')
        if a==0x253:
            f834.physical_case(rd,pe,d,code,refs,s,by,a,260,6,f879.BAD_253,0x254,f820)
        else:
            na=list(d.disasm(rd.pe_bytes_at(pe,by[a],nb),by[a]))
            need(nb-sb==(1 if a==0x252 else -1)
                 and all(r['offset']-low==
                    na[next(j for j,z in enumerate(s) if z.address<=r['offset']<z.address+z.size)].address-by[a]+
                    na[next(j for j,z in enumerate(s) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                    for r in ff),'original 252/254 physical PE field positions must stay shifted')
            shifts.append({'case':hex(a),'native_B':nb,'source_B':sb,'not_exact':True})
    for a,nxt,nb,n,nf in f880.CASES:
        s=late[at:at+n];at+=n
        f834.physical_case(rd,pe,d,code,refs,s,by,a,nb,nf,f880.BAD[a],nxt,f820)
    cases=[
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
       (0x2db,0x2dc,162,556,13,f892.WRONG)]
    for a,nxt,n,nb,nf,bad in cases:
        s=late[at:at+n];at+=n
        f834.physical_case(rd,pe,d,code,refs,s,by,a,nb,nf,bad,nxt,f820)
    need(at==len(late),'all previous 68 original game cases truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
         [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    bad_tail=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(bad_tail==[] and len(tmask)==12,
         'original shared 46B getter full 34/34 nonfield byte recovery altered')
    out={'original_whole_game':'0x005214B0',
       'native_original_entire_callable_CODE_B':46755,
       'generated_full_whole_source_CODE_B':ret,
       'new_original_2DC_complete_case':checked,
       'native_real_2DC_typed_physical_PE_fields':list(offsets),
       'genuine_original_game_stage2_sprite':0x33b,
       'genuine_original_game_stage13_sprite':0x338,
       'true_original_ground_contact_leq_semantics':True,
       'true_action_guarded_random_boundary_short516':True,
       'three_equal_length_wrong_game_source_controls':negative,
       'actual_2DC_internal_GPR_and_branch_wrong_B':0,
       'actual_2DC_original_far_giant_JMP_wrong_offsets':BAD,
       'preceding_46_earlier_native_game_cases_rechecked':oldchecks,
       'previous_1FD_one_byte_CMP_defect_preserved':True,
       'previous_252_254_native_PE_offset_shifts_retained':shifts,
       'all_68_previous_native_game_cases_rechecked':True,
       'native_common_getter_46B_nonfield_equal':'34/34',
       'native_five_original_901B_afterRET_packed_tables_verified':True,
       'original_separate_afterRET_DATA_B':901,
       'original_complete_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_complete_giant_exact'] is False
    print('F893 original 2DC 660B/188x86/17 real PE fields complete source, stage2/13 native sprites and ground-contact <=, random0..30 under current action match. ONLY four enclosing giant JMP bytes +427/428,+656/657 different. Full father40552B/11433x86, prior68 original states/five 901B tables and common getter 34/34 rechecked. Whole original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as err:
        print('F893 full native 2DC physical original PE FAILED:',err,file=sys.stderr)
        raise SystemExit(1)
