#!/usr/bin/env python3
"""F890: original 2C2 COMPLETE 2274B/608x86/50 PE fields.

Original sparse giant stage2C2 0052A468..0052AD49,
eight genuinely unrolled F00=0..7 projectile stages,
x87 natural 15 real integer temporaries, owner X
borrowed true lvalue BEFORE signed facing conversions.
Native stage8 one-shot logic MUST be INSIDE the
stage<9/frame0 guard. Otherwise the 2274B/608x86
C++ source still has four wrong original long Jcc
operand bytes, changing native CFG destinations.
Selected original source has only FOUR enclosing
parent far epilogue JMP bytes different. All 50
original actual PE refs/targets and previous 65
original inner game states, five 901B DATA tables
physically checked in ONE affected VC7.1 full parent.
Original whole 46755B still NONEXACT; no split-case credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f890-scripted-2c2'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
EXPECTED_WRONG=[175,176,2270,2271]
GLOBAL_NAMES={
 'g_F890GravityAt006581E0':'0x006581E0',
 'g_F890Phase0YAt0065835C':'0x0065835C',
 'g_F890Phase0AltYAt006591E4':'0x006591E4',
 'g_F890Phase1LowYAt0065788C':'0x0065788C',
 'g_F890Phase4HiYAt00659420':'0x00659420',
 'g_F890Phase4OtherYAt006598B4':'0x006598B4',
 'g_F890Phase5YAt0065786C':'0x0065786C'}
def need(cond,msg):
    if not cond:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'missing original PE helper '+name)
    mod=importlib.util.module_from_spec(sp);sys.modules[tag]=mod;sp.loader.exec_module(mod)
    return mod

def source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f888-scripted-2c0-2c1/Boss005214B0-F888-whole.cpp'
    receipt=R/'.analysis/f888-scripted-2c0-2c1/verified-summary.json'
    if not prior.exists() or not receipt.exists():
        cp=subprocess.run([str(R/'scripts/repo-python'),
                str(R/'scripts/verify-scripted-fighter-2c0-2c1-f888.py')],
                cwd=R,text=True,capture_output=True,timeout=1500)
        (O/'f888-original-fallback.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous 2C0/2C1 full native proof failed '+(cp.stdout+cp.stderr)[-720:])
    old=json.loads(receipt.read_text())
    need(old['new_whole_source_callable_CODE_B']==37053
         and old['original_entire_giant_exact'] is False
         and old['native_getter_34_of_34_original_nonfield_bytes_equal'],
         'previous 2C0/2C1 current PE whole parent receipt changed')
    cpp=prior.read_text()
    marker='        case 0x2C2: g_FighterProbeMarker = 707; break;'
    inc=(R/'probes/FighterScriptedFull2C2F890.inc').read_text()
    need(cpp.count(marker)==1 and inc.count('case 0x2C2:')==1
         and inc.count('return;')==2
         and inc.count('if (S16(0xF00)==')==8
         and inc.count('++S16(0xF00);')==1
         and inc.count('++S16(0xF02);')==1
         and inc.count('++S16(0xF04);')==1
         and inc.count('Spawn')>=20
         and 'POS54=POS54-g_F890GravityAt006581E0;' in inc
         and inc.count('F32(0x314)=0.0f;')==3
         and inc.count('reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44')>=12,
         'original whole 2274B game 2C2 multiple true projectile phases missing')
    phase='    if (S16(0x62)<9 && S16(0x64)==0) {'
    stage8='        if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF04)==0) {'
    stage9='    if (S16(0x62)==9 && S16(0x64)==0) {'
    need(inc.count(phase)==inc.count(stage8)==inc.count(stage9)==1
         and inc.index(phase)<inc.index(stage8)<inc.index(stage9)
         and inc.rindex('    }\n    if (S16(0x62)==9')>inc.index(stage8),
         'native stage8 must be nested in stage<9 frame0 C++ guard')
    prefix=''.join('extern float '+key+';\n'
                   for key in GLOBAL_NAMES)
    return prefix+cpp.replace(marker,'#include "FighterScriptedFull2C2F890.inc"',1)

def compile_one(cpp,tag):
    cpp_path=O/('Boss005214B0-F890-'+tag+'.cpp')
    obj=O/('Boss005214B0-F890-'+tag+'.obj')
    cpp_path.write_text(cpp)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp_path),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=R,env=env,capture_output=True,text=True,timeout=350)
    (O/('compiler-'+tag+'.log')).write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'original 2C2 entire VC7.1 '+tag+' source compile failed '+(cp.stdout+cp.stderr)[-700:])
    return obj
def parsed(rd,d,obj):
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    marks=[j for j,x in enumerate(I) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x2c4')
           and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=608,
         'next original native 2C3 state marker missing')
    return code,refs,I,ret,marks[0]

def main():
    rd=ld('f890rd','compare-coff-function.py')
    ac=ld('f890ac','report-fighter-action-handlers.py')
    f834=ld('f890f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f890f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f890f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f890f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f890f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f890f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f890f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f890f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f890f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f890f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f890f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f890f885','verify-scripted-fighter-stage2bd-f885.py')
    f886=ld('f890f886','verify-scripted-fighter-stage2be-f886.py')
    f888=ld('f890f888','verify-scripted-fighter-2c0-2c1-f888.py')
    zero=ld('f890zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f890switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads(
       (R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
       if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned Japanese original whole 46755B fighter and 901B DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    raw=rd.pe_bytes_at(pe,by[0x2c2],by[0x2c3]-by[0x2c2])
    orig=list(d.disasm(raw,by[0x2c2]))
    need((by[0x2c2],by[0x2c3],len(raw),len(orig))==
          (0x52a468,0x52ad4a,2274,608),
          'original action 2C2 actual physical handler extent changed')
    need(orig[26].mnemonic=='fsub'
         and orig[26].op_str=='dword ptr [0x6581e0]'
         and orig[44].mnemonic=='jmp' and orig[44].op_str=='0x52cb4f'
         and orig[55].mnemonic=='add' and orig[55].op_str.endswith(', 1')
         and orig[140].op_str=='0x453a70'
         and orig[180].mnemonic=='fild'
         and orig[279].mnemonic=='fsubr'
         and orig[539].op_str=='0x40fb40'
         and orig[607].mnemonic=='jmp' and orig[607].op_str=='0x52cb4f',
         'native original 2C2 projectile stages or shared giant exit changed')
    obj=compile_one(source(),'whole')
    code,refs,ins,ret,k=parsed(rd,d,obj)
    need((ret,len(ins),len(refs),len(code)-ret)==(39312,11069,1301,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'complete full native VC7.1 source frame/CODE/COFF changed')
    dense,sparse,maps=zero.verify_physical_tables(
          boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all native five packed 901B afterRET switch DATA tables not verified')
    sec=ins[k-608:k]
    original_case=f834.physical_case(
          rd,pe,d,code,refs,sec,by,0x2c2,2274,50,
          EXPECTED_WRONG,0x2c3,f820)
    need(original_case['native_complete_x86']==608
         and original_case['original_native_enclosing_parent_JMP_exit_ordinals']==[44,607]
         and sec[44].op_str==sec[607].op_str==hex(ret-4),
         'real original 2C2 complete x86 geometry or two giant JMP exits changed')
    lo=sec[0].address
    fields=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x2c2],fields,lo,50)
    need(len(mask)==200,'fifty original native PE operands must be independently verified')
    offsets=[];targets=[];real_sym_ids=[]
    for r in fields:
        offset=r['offset']-lo
        ordinal=next(i for i,x in enumerate(sec) if x.address<=r['offset']<x.address+x.size)
        real=orig[ordinal];src=sec[ordinal]
        need(offset==real.address-by[0x2c2]+real.size-4
             and src.mnemonic==real.mnemonic and src.size==real.size
             and r['addend']==0 and r['local_symbol_offset'] is None,
             'native 2C2 genuinely physical COFF operand shifted '+str(ordinal))
        native_target=(int.from_bytes(raw[offset:offset+4],'little')
               if r['type']=='DIR32' else by[0x2c2]+offset+4+
                     int.from_bytes(raw[offset:offset+4],'little',signed=True))
        actual_desc=r['symbol']
        if r['type']=='DIR32':
            import re
            match=re.search(r'At([0-9A-Fa-f]{8})',actual_desc)
            need(match is not None and native_target==int(match.group(1),16),
                 'original 2C2 PE global address/type inconsistent with actual C++ variable '+str(ordinal))
        else:
            need(real.mnemonic=='call'
                 and 0x400000<=native_target<=0x6406ac,
                 'original 2C2 PE relocation function call target invalid '+str(ordinal))
        offsets.append(offset)
        targets.append(hex(native_target))
        real_sym_ids.append(actual_desc)
    need(len(offsets)==50 and len(set(offsets))==50
         and offsets[0]==84 and offsets[-1]==2217,
         'original 2C2 50 physical fields unexpectedly different')
    for j,expected_native in ((90,583),(94,583)):
        need(orig[j].op_str==hex(orig[expected_native].address)
             and sec[j].op_str==hex(sec[expected_native].address),
             'native 2C2 stage<9 must skip ALL stage8 one-shot logic, not only phases')
    # These are real integer->float scratch stack stores, not
    # padding locals or inline assembler.
    temp_indexes=(133,179,226,250,277,301,350,399,429,452,481,505,557)
    native_temps=[]
    for i in temp_indexes:
        a,b=orig[i],sec[i]
        need(a.mnemonic==b.mnemonic=='mov'
             and a.op_str.startswith('dword ptr [ebp - ')
             and b.op_str.split(',')[0]==a.op_str.split(',')[0]
             and orig[i+1].mnemonic==sec[i+1].mnemonic=='fild',
             'native 2C2 real live float scratch slot changed '+str(i))
        native_temps.append(a.op_str.split(',')[0])
    need(len(native_temps)==13 and native_temps[0]=='dword ptr [ebp - 0xd4]'
         and native_temps[-1]=='dword ptr [ebp - 0x104]',
         'native integer FILD scratch allocation evidence missing')
    # FALSE full original source: emit stage8 outside stage<9 guard.
    # Despite all 608 opcode/size slots and 50 original PE fields
    # this changes original real Jcc destinations.
    cpp=source()
    include='#include "FighterScriptedFull2C2F890.inc"'
    frag=(R/'probes/FighterScriptedFull2C2F890.inc').read_text()
    wrong1='''        ++S16(0xF00);
        if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF04)==0) {'''
    revert1='''        ++S16(0xF00);
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF04)==0) {'''
    wrong2='''        }
    }
    if (S16(0x62)==9 && S16(0x64)==0) {'''
    revert2='''        }
    if (S16(0x62)==9 && S16(0x64)==0) {'''
    need(frag.count(wrong1)==frag.count(wrong2)==1,
         'native 2C2 nesting source control not at expected original locations')
    outside=frag.replace(wrong1,revert1,1)
    outside=outside.replace(wrong2,revert2,1)
    # The preceding revert had a body closing brace for stage8,
    # so remove the original nested last brace only, retaining
    # exactly one brace closing original stage8.
    exterior_obj=compile_one(cpp.replace(include,outside,1),'bad-stage8-unnested')
    bc,br,bI,bret,bk=parsed(rd,d,exterior_obj)
    bs=bI[bk-608:bk]
    need((bret,len(bI),len(br),len(bc)-bret)==(39312,11069,1301,901)
         and bs[-1].address+bs[-1].size-bs[0].address==2274,
         'wrong stage8 guard source should be deceptively same whole x86 size')
    blo=bs[0].address
    bfields=[r for r in br if blo<=r['offset']<bs[-1].address+bs[-1].size]
    bmask=f820.physical_fields(rd,raw,by[0x2c2],bfields,blo,50)
    mismatch=[j for j in range(2274) if j not in bmask and raw[j]!=bc[blo+j]]
    need(mismatch==[175,176,334,335,349,350,2270,2271],
         'wrong stage8 guard must generate genuine native Jcc target byte errors')
    # FALSE whole parent: compute signed facing first then fetch
    # borrowed actor ownerX for a real projectile. Native source
    # demands owner pointer loaded BEFORE integer-to-float stage.
    good='reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44+float(((*reinterpret_cast<signed char*>(RAW+0x66)))*100)'
    bad='float(((*reinterpret_cast<signed char*>(RAW+0x66)))*100)+(*reinterpret_cast<float*>(OWNER+0x44))'
    need(frag.count(good)==2,'F890 2C2 two actual facing100 positive owner X shots absent')
    float_control=frag.replace(good,bad,1)
    altobj=compile_one(cpp.replace(include,float_control,1),'bad-owner-x-order')
    dc,dr,dI,dret,dk=parsed(rd,d,altobj)
    ds=dI[dk-608:dk]
    need((dret,len(dI),len(dr),len(dc)-dret)==(39312,11069,1301,901)
         and any(a.mnemonic!=b.mnemonic for a,b in zip(orig,ds))
         and any(a.size!=b.size for a,b in zip(orig,ds)),
         'wrong owner X float operand evaluation order must break original x87 grammar')
    # The current same whole object must reverify the 65 previously
    # recovered native interior cases; 1FD and 252/254 negative
    # source size/PE displacement mismatches remain uncredited.
    prior=json.loads((R/'.analysis/f888-scripted-2c0-2c1/verified-summary.json').read_text())
    old=prior['previous_46_native_game_cases_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'native prior 46 source-backed action evidence missing')
    recent_count=(107+107+149+177+80+207+205+60+60+228+239+136+138+85+81)
    early_end=k-608-recent_count
    prefix=ins[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    cursor=0;oldchecked=[]
    for i,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[i+1]['case'],16) if i+1<len(old) else 0x1fd
        part=prefix[cursor:cursor+x['native_complete_x86']]
        cursor+=x['native_complete_x86']
        oldchecked.append(f834.physical_case(rd,pe,d,code,refs,part,by,
           action,x['native_whole_inner_B'],x['original_typed_PE_fields'],
           x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(part[3].op_str==part[7].op_str==hex(part[22].address),
                 'true prior 1A0 conditional multiplier scope differs')
    need(cursor==len(prefix),'46 early original PE source case intervals truncated')
    prior_cases=ins[early_end:k-608]
    first=prior_cases[:107]
    origfd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(first[-1].address+first[-1].size-first[0].address==385
         and origfd[99].size==6 and first[99].size==5
         and first[100].op_str==hex(first[104].address),
         '1FD original CMP-ECX width negative or owner-status true CFG changed')
    curr=107
    for action,nxt,n,nb,nf,bad in (
        (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
        (0x1ff,0x200,149,533,9,f875.BAD),
        (0x200,0x201,177,634,10,f877.BAD),
        (0x201,0x252,80,267,8,f878.BAD)):
        part=prior_cases[curr:curr+n];curr+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,
              action,nb,nf,bad,nxt,f820)
    shifted=[]
    for action,nxt,nb,n,sb,_ in f879.CASES:
        part=prior_cases[curr:curr+n];curr+=n
        lo2=part[0].address;hi2=part[-1].address+part[-1].size
        ff=[r for r in refs if lo2<=r['offset']<hi2]
        need(hi2-lo2==sb and len(ff)==6,
             'native 252-254 original byte phase shifted in full fighter')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,part,by,
                               action,260,6,f879.BAD_253,0x254,f820)
        else:
            original_offset=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and all(r['offset']-lo2==
                    original_offset[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].address-by[action]+
                    original_offset[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                    for r in ff),
                 '252/254 native original full physical PE reloc shifts must stay NONEXACT')
            shifted.append({'case':hex(action),'native_B':nb,'source_B':sb,'original_exact':False})
    for action,nxt,nb,n,nf in f880.CASES:
        part=prior_cases[curr:curr+n];curr+=n
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
       (0x2c1,0x2c2,81,276,11,f888.BAD[0x2c1])]
    for action,nxt,n,nb,nf,bad in later:
        part=prior_cases[curr:curr+n];curr+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,
             action,nb,nf,bad,nxt,f820)
    need(curr==len(prior_cases),'all prior 65 actual original game case interiors must be contiguous')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
              [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tailwrong=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(tailwrong==[] and len(mask)==12,
         'common original 46B getter must match 34/34 original non-PE bytes')
    receipt={'original_giant':'0x005214B0',
       'native_entire_callable_CODE_B':46755,
       'generated_new_whole_source_CODE_B':ret,
       'new_native_complete_original_2C2':original_case,
       'native_original_2C2_full_CODE_B':2274,
       'native_original_2C2_full_x86':608,
       'native_2C2_physically_typed_original_PE_field_count':50,
       'real_2C2_native_PE_field_offsets':offsets,
       'native_2C2_original_PE_targets':targets,
       'native_2C2_source_COFFER_sym_roles':real_sym_ids,
       'native_2C2_real_integer_FILD_temp_operands':native_temps,
       'real_native_stage8_within_stage_lt9_frame0':True,
       'false_unnested_stage8_equal_size_original_wrong_offsets':mismatch,
       'false_owner_x_evaluation_order_breaks_original_opcode_width':True,
       'native_2C2_original_register_and_CJMP_wrong_B':0,
       'native_2C2_real_whole_giant_JMP_wrong_offsets':EXPECTED_WRONG,
       'previous_46_original_PE_case_sources_reverified':oldchecked,
       'previous_1FD_native_one_byte_CMP_negative_retained':True,
       'previous_252_254_one_byte_physical_PE_field_shifts':shifted,
       'all_previous_65_native_case_interiors_checked':True,
       'common_native_getter_46B_nonrelocation_equal':'34/34',
       'all_five_original_901B_packed_afterRET_tables_verified':True,
       'native_separate_afterRET_DATA_B':901,
       'entire_original_callable_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['entire_original_callable_giant_exact'] is False
    print('F890 actual giant 2C2 entire 2274B/608x86/50 physical PE fields naturally restored (13 real FILD temps). Stage8 nested original CFG; all nonfield bytes exact except FOUR original far giant epilogue JMP bytes +175/176,+2270/2271. Whole source 39312B/11069x86, previous 65 game cases, five 901B tables and common native getter 34/34 checked. Whole original 46755B still NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F890 complete original 2C2 physical PE proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
