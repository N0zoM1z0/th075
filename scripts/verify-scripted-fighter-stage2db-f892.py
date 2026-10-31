#!/usr/bin/env python3
"""F892: full native 2DB 556B/162x86/13 PE fields in one affected fighter.

Native float ownerX-thisX game distance must use TWO true borrowed
X lvalues, giving original MOV owner, MOV this, FLD owner, FSUB this
sequence. Real RandomBoundary455580(30,60) and short+516 update
belong INSIDE GetNativeActionAt40FA30 match guard; false outside
placement keeps native size but changes JNE target one byte.
Original 412D90 helper verified as real original FloatAbs call.
Stage2, stage10 once-only short++/aux2, stage15 mixed floatX
sprite80 plus integer sprite336, stage16 height17.5.
All 67 preceding source-backed original states and five 901B
afterRET DATA tables rechecked in one new VC7.1 full father.
No whole exact CODE credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f892-scripted2db'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
WRONG=[166,167,552,553]
FIELD_ORDS=(19,35,37,43,51,56,63,71,75,107,134,147,150)
FIELD_OFFSETS=(84,135,144,161,190,208,233,257,269,384,468,504,514)
FIELD_TARGETS=(0x453e20,0x412d90,0x65787c,0x40fb40,
   0x657f74,0x65782c,0x40fa30,0x40fac0,0x455580,
   0x40fb40,0x453c80,0x453a70,0x453d40)

def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,filename):
    s=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(s is not None and s.loader is not None,'original PE helper missing '+filename)
    m=importlib.util.module_from_spec(s);sys.modules[tag]=m;s.loader.exec_module(m);return m
def make_source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f891-scripted2c3/Boss005214B0-F891-whole.cpp'
    rec=R/'.analysis/f891-scripted2c3/verified-summary.json'
    if not prev.exists() or not rec.exists():
        run=subprocess.run([str(R/'scripts/repo-python'),
           str(R/'scripts/verify-scripted-fighter-transition2c3-f891.py')],
           cwd=R,capture_output=True,text=True,timeout=1700)
        (O/'prior-f891-original.log').write_text(run.stdout+run.stderr)
        need(run.returncode==0,'previous 2C3 full native PE receipt failed '+(run.stdout+run.stderr)[-720:])
    old=json.loads(rec.read_text())
    need(old['new_generated_full_source_CODE_B']==39366
         and old['native_original_full_giant_exact'] is False,
         'previous current original PE 2C3 whole source receipt changed')
    cpp=prev.read_text()
    cl='void SetMotionStateAt40FBB0(int,float,int);'
    need(cpp.count(cl)==1,'original observed native game class declaration missing')
    cpp=cpp.replace(cl,cl+' short RandomBoundaryAt455580(int,int);',1)
    cpp='extern float g_F892DistAt0065787C;\nextern float F892AbsAt00412D90(float);\n'+cpp
    marker='        case 0x2DB: g_FighterProbeMarker = 732; break;'
    inc=(R/'probes/FighterScriptedStage2DBF892.inc').read_text()
    need(cpp.count(marker)==1 and inc.count('case 0x2DB:')==1
         and inc.count('return;')==2
         and inc.count('reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44')==1
         and inc.count('reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44')==1
         and inc.index('if (GetNativeActionAt40FA30()==S16(0x70)) {')<
             inc.index('S16(0x516)=RandomBoundaryAt455580(30,60);')<
             inc.index('    }\n    if (S16(0x62)==2')
         and 'F892AbsAt00412D90' in inc
         and 'SetAuxActionAt40FB40(10)' in inc
         and 'SetAuxActionAt40FB40(2)' in inc
         and 'SpawnFloatXRawYAt453C80(0x80' in inc
         and 'SpawnDirectedAt453A70(0x336' in inc,
         'actual native 2DB complete original game source misordered')
    return cpp.replace(marker,'#include "FighterScriptedStage2DBF892.inc"',1)

def compile_one(src,tag):
    cpp=O/('Boss005214B0-F892-'+tag+'.cpp')
    obj=O/('Boss005214B0-F892-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=e,capture_output=True,text=True,timeout=340)
    (O/('compiler-'+tag+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'normal original native 2DB full compiler '+tag+' failed '+(run.stdout+run.stderr)[-700:])
    return obj
def parse(rd,d,obj):
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    marker=[j for j,x in enumerate(I) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x2dd')
         and any('g_FighterProbeMarker' in r['symbol']
                 and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=162,
         'next native game 2DC source marker missing')
    return code,refs,I,ret,marker[0]

def main():
    rd=ld('f892rd','compare-coff-function.py')
    ac=ld('f892ac','report-fighter-action-handlers.py')
    f834=ld('f892f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f892f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f892f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f892f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f892f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f892f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f892f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f892f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f892f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f892f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f892f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f892f885','verify-scripted-fighter-stage2bd-f885.py')
    f886=ld('f892f886','verify-scripted-fighter-stage2be-f886.py')
    f888=ld('f892f888','verify-scripted-fighter-2c0-2c1-f888.py')
    f890=ld('f892f890','verify-scripted-fighter-full2c2-f890.py')
    f891=ld('f892f891','verify-scripted-fighter-transition2c3-f891.py')
    zero=ld('f892zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f892sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
             if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original fighter CODE/afterRET DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    raw=rd.pe_bytes_at(pe,by[0x2db],by[0x2dc]-by[0x2db])
    original=list(d.disasm(raw,by[0x2db]))
    need((len(raw),len(original),by[0x2db],by[0x2dc])==(556,162,0x52ad8f,0x52afbb)
         and original[35].op_str=='0x412d90'
         and original[37].op_str=='dword ptr [0x65787c]'
         and original[75].op_str=='0x455580'
         and original[107].op_str=='0x40fb40'
         and original[127].op_str=='dword ptr [ebp - 0x108]'
         and original[134].op_str=='0x453c80'
         and original[147].op_str=='0x453a70'
         and original[-1].op_str=='0x52cb4f',
         'native original 2DB real abs-distance/random/x87 sprite game evidence altered')
    source=make_source()
    obj=compile_one(source,'whole')
    code,refs,I,ret,k=parse(rd,d,obj)
    need((ret,len(I),len(refs),len(code)-ret)==(39907,11247,1316,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'F892 full native normal VC7.1 father CODE/x86/ABI geometry changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'five original 901B packed DATA tables absent')
    sec=I[k-162:k]
    check=f834.physical_case(rd,pe,d,code,refs,sec,by,0x2db,556,13,WRONG,0x2dc,f820)
    need(check['native_complete_x86']==162
         and check['original_native_enclosing_parent_JMP_exit_ordinals']==[44,161]
         and sec[44].op_str==sec[161].op_str==hex(ret-4)
         and all(a.mnemonic==b.mnemonic and a.op_str==b.op_str
                 for a,b in zip(original[28:33],sec[28:33]))
         and sec[68].op_str==hex(sec[78].address),
         '2DB original float ownerX-thisX order or conditionally protected random source differs')
    lo=sec[0].address
    ff=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x2db],ff,lo,13)
    need(len(mask)==52,'all thirteen native PE references not checked')
    offsets=[]
    for ordinal,target in zip(FIELD_ORDS,FIELD_TARGETS):
        a,b=original[ordinal],sec[ordinal]
        found=[r for r in ff if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['addend']==0
             and found[0]['local_symbol_offset'] is None
             and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and found[0]['offset']-lo==a.address-by[0x2db]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                      else f'dword ptr [0x{target:x}]'),
             'original 2DB original physical PE source symbol/callee differs '+str(ordinal))
        offsets.append(found[0]['offset']-lo)
    need(offsets==list(FIELD_OFFSETS),
         'original 2DB physically typed PE location geometry changed')
    # Two complete wrong source experiments with exact native 556B
    # geometry but real game logic/operand differences.
    include='#include "FighterScriptedStage2DBF892.inc"'
    frag=(R/'probes/FighterScriptedStage2DBF892.inc').read_text()
    incorrect_abs=frag.replace(
       'reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44',
       '(*reinterpret_cast<float*>(OWNER+0x44))-F32(0x44)')
    random_bad=frag.replace(
       '''    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(30,60);
    }''',
       '''    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    S16(0x516)=RandomBoundaryAt455580(30,60);''')
    need(incorrect_abs!=frag and random_bad!=frag and source.count(include)==1,
         'cannot build genuine native 2DB negative full source controls')
    negatives={}
    for tag,wrongsrc in [('wrong-owner-float-order',incorrect_abs),
                         ('wrong-random-guard',random_bad)]:
        badobj=compile_one(source.replace(include,wrongsrc,1),tag)
        bc,br,bI,bret,bk=parse(rd,d,badobj)
        bs=bI[bk-162:bk];blo=bs[0].address;end=bs[-1].address+bs[-1].size
        bf=[r for r in br if blo<=r['offset']<end]
        bmask=f820.physical_fields(rd,raw,by[0x2db],bf,blo,13)
        mismatch=[j for j in range(556) if j not in bmask and raw[j]!=bc[blo+j]]
        expected=([121,122,123,124,125,126,166,167,552,553]
                  if tag=='wrong-owner-float-order'
                  else [166,167,250,552,553])
        need((bret,len(bI),len(br),len(bc)-bret)==(39907,11247,1316,901)
             and mismatch==expected,
             'same-length false original 2DB game semantics must be rejected '+tag)
        negatives[tag]=mismatch
    # Previous 67 original game state sources verified again on
    # THIS new one-parent COFF. Never replay the whole corpus.
    previous=json.loads((R/'.analysis/f891-scripted2c3/verified-summary.json').read_text())
    old=previous['previous_46_original_case_sources_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'prior original 46 native case receipts absent')
    after_count=107+107+149+177+80+207+205+60+60+228+239+136+138+85+81+608+20
    early_end=k-162-after_count
    prefix=I[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    cursor=0;oldcases=[]
    for j,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[j+1]['case'],16) if j+1<len(old) else 0x1fd
        part=prefix[cursor:cursor+x['native_complete_x86']]
        cursor+=x['native_complete_x86']
        oldcases.append(f834.physical_case(rd,pe,d,code,refs,part,by,
                action,x['native_whole_inner_B'],x['original_typed_PE_fields'],
                x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(part[3].op_str==part[7].op_str==hex(part[22].address),
                 '1A0 native stage0 guarded multipliers regressed')
    need(cursor==len(prefix),'46 earlier original game cases truncated')
    previous_full=I[early_end:k-162]
    first=previous_full[:107]
    nativefd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(first[-1].address+first[-1].size-first[0].address==385
         and nativefd[99].size==6 and first[99].size==5
         and first[100].op_str==hex(first[104].address),
         '1FD native one-byte CMP defect and owner condition must stay nonexact')
    pos=107
    for action,nxt,n,nb,nf,bad in (
       (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,149,533,9,f875.BAD),
       (0x200,0x201,177,634,10,f877.BAD),
       (0x201,0x252,80,267,8,f878.BAD)):
        part=previous_full[pos:pos+n];pos+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,
                 action,nb,nf,bad,nxt,f820)
    shifted=[]
    for action,nxt,nb,n,sb,_ in f879.CASES:
        part=previous_full[pos:pos+n];pos+=n
        lo2=part[0].address;hi2=part[-1].address+part[-1].size
        ff2=[r for r in refs if lo2<=r['offset']<hi2]
        need(hi2-lo2==sb and len(ff2)==6,
             '252/254 original one-byte register phase has changed unexpectedly')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,part,by,action,260,6,f879.BAD_253,0x254,f820)
        else:
            original_2=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and all(r['offset']-lo2==
                    original_2[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].address-by[action]+
                    original_2[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                    for r in ff2),
                 'native 252/254 PE original field locations must stay incorrect')
            shifted.append({'case':hex(action),'native_B':nb,'source_B':sb})
    for action,nxt,nb,n,nf in f880.CASES:
        part=previous_full[pos:pos+n];pos+=n
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
       (0x2c2,0x2c3,608,2274,50,f890.EXPECTED_WRONG),
       (0x2c3,0x2db,20,69,4,[65,66])]
    for action,nxt,n,nb,nf,bad in later:
        part=previous_full[pos:pos+n];pos+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,
                   action,nb,nf,bad,nxt,f820)
    need(pos==len(previous_full),'all 67 prior original native state interiors not rechecked')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
                  [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_getter=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(wrong_getter==[] and len(tmask)==12,
         'native getter 34/34 comparison changed after actual 2DB owner phase')
    receipt={'original_whole_fighter':'0x005214B0',
       'original_native_whole_callable_CODE_B':46755,
       'generated_new_whole_source_CODE_B':ret,
       'new_original_2DB_complete_case':check,
       'native_original_2DB_physical_PE_field_offsets':offsets,
       'real_original_2DB_distance_helper':'0x00412D90',
       'real_original_2DB_random_helper':'0x00455580',
       'real_owner_and_actor_borrowed_X_lvalue_order':True,
       'real_random_update_inside_current_action_guard':True,
       'wrong_same_length_source_controls':negatives,
       'true_original_2DB_GPR_and_local_Jcc_wrong_B':0,
       'native_2DB_real_far_giant_epilogue_JMP_wrong_offsets':WRONG,
       'previous_46_original_native_cases_reverified':oldcases,
       'prior_1FD_one_byte_original_CMP_negative_preserved':True,
       'prior_252_254_one_byte_shifted_PE_fields':shifted,
       'all_previous_67_original_game_case_interiors_rechecked':True,
       'native_shared_getter_46B_nonrelocation_match':'34/34',
       'all_five_original_901B_afterRET_tables_rechecked':True,
       'original_separate_afterRET_DATA_B':901,
       'entire_original_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['entire_original_giant_exact'] is False
    print('F892 original 2DB full 556B/162x86/13 native PE fields, genuine borrowed ownerX-thisX FLOAT distance, abs helper412D90, random455580 guarded by current action, two stage15 sprites, FILD-108. Native internal exact except four original whole-parent far JMP bytes +166/167,+552/553. Full current fighter 39907B/11247x86; 67 earlier native cases, 901B tables and shared getter 34/34 checked; original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F892 original 2DB real whole PE proof FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
