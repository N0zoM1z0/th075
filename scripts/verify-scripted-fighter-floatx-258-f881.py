#!/usr/bin/env python3
"""F881: real 258 float-X/raw-Y original 206B/60x86/6 PE fields.

Original stage0 Reset and state+7C=1, current action -> zero;
stage2 sprite340 float X = signed facing*80 FILD + actorX,
integer raw owner Y+48, true char facing, StartAnimation
46D000(0xFA) and Prepare5. The actual correct borrowed
method signature narrow char makes 206B; false 4-byte int
signature emits MOVSX 207B. Recheck original full PE calls,
preceding 57 native games including 252/254 byte phase and
original 1FD CMP negative, original five packed 901B
afterRET DATA tables. Giant original 46755B NONEXACT,
no new accepted complete whole callable CODE.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f881-scripted-stage258'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,72,74,78,81,95,99,102,107,111,114,120,123,125,127,130,132,134,138,141,144,156,159,202,203]
FIELDS={
 9:(0x453e20,'ResetAt453E20'),
 17:(0x40fa30,'GetNativeActionAt40FA30'),
 25:(0x40fac0,'SetNativeActionAt40FAC0'),
 52:(0x453a70,'SpawnFloatXRawYAt453A70'),
 55:(0x46d000,'StartAnimationAt46D000'),
 58:(0x453d40,'PrepareActionAt453D40')}
OFFSETS=[26,66,90,174,187,197]

def need(v,msg):
    if not v:raise ValueError(msg)
def ld(k,filename):
    sp=importlib.util.spec_from_file_location(k,R/'scripts'/filename)
    need(sp is not None and sp.loader is not None,'native PE helper missing '+filename)
    m=importlib.util.module_from_spec(sp);sys.modules[k]=m;sp.loader.exec_module(m)
    return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f880-scripted-255-257/Boss005214B0-F880-whole.cpp'
    proof=R/'.analysis/f880-scripted-255-257/verified-summary.json'
    if not prev.exists() or not proof.exists():
        run=subprocess.run([str(R/'scripts/repo-python'),
          str(R/'scripts/verify-scripted-fighter-stage255-257-f880.py')],
          cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'f880-native-prior.log').write_text(run.stdout+run.stderr)
        need(run.returncode==0,'preceding 255-257 real native PE source failed '+(run.stdout+run.stderr)[-680:])
    prior=json.loads(proof.read_text())
    need(prior['generated_full_fighter_callable_CODE_B']==33605
         and prior['original_complete_giant_exact'] is False,
         'preceding original 255-257 source receipt changed')
    cpp=prev.read_text()
    signature='void SpawnDirectedAt453A70(int,int,int,char,int);'
    need(cpp.count(signature)==1,'borrowed original sprite method declaration missing')
    cpp=cpp.replace(signature,signature+' void SpawnFloatXRawYAt453A70(int,float,int,char,int);',1)
    marker='        case 0x258: g_FighterProbeMarker = 601; break;'
    inc=(R/'probes/FighterScriptedFloatX258F881.inc').read_text()
    need(cpp.count(marker)==1 and inc.count('case 0x258:')==1
         and inc.count('return;')==1
         and inc.count('SpawnFloatXRawYAt453A70(0x340')==1
         and 'float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44)' in inc
         and 'StartAnimationAt46D000(0xFA)' in inc
         and 'PrepareActionAt453D40(5)' in inc
         and 'I32(0x7C)=1;' in inc,
         'genuine 258 native mixed coordinate source changed')
    return cpp.replace(marker,'#include "FighterScriptedFloatX258F881.inc"',1)
def compile_one(src,tag='whole'):
    cpp=O/('Boss005214B0-F881-'+tag+'.cpp')
    obj=O/('Boss005214B0-F881-'+tag+'.obj')
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=E,capture_output=True,text=True,timeout=310)
    (O/('compiler-'+tag+'.log')).write_text(run.stdout+run.stderr)
    need(run.returncode==0,'original 258 full normal VC7.1 build failed '+(run.stdout+run.stderr)[-700:])
    return obj
def parsed(rd,d,obj):
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    marker=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
      and x.op_str.endswith(', 0x25a')
      and any('g_FighterProbeMarker' in r['symbol']
              and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1 and marker[0]>=60,'next native 259 block source sentinel missing')
    return code,refs,ins,ret,marker[0]

def main():
    rd=ld('f881rd','compare-coff-function.py')
    ac=ld('f881ac','report-fighter-action-handlers.py')
    f834=ld('f881f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f881f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f881f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f881f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f881f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f881f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f881f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f881f880','verify-scripted-fighter-stage255-257-f880.py')
    zero=ld('f881zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f881switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original 005214B0 whole PE CODE or afterRET packed tables changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    original=list(d.disasm(rd.pe_bytes_at(pe,by[0x258],by[0x259]-by[0x258]),by[0x258]))
    need(len(original)==60 and by[0x259]-by[0x258]==206
         and original[13].op_str.endswith(', 1')
         and original[28].op_str.endswith(', 2')
         and original[44].mnemonic=='mov'
         and original[44].op_str.startswith('dword ptr [ebp - 0xb4],')
         and original[45].mnemonic=='fild'
         and original[50].op_str=='0x340'
         and original[52].op_str=='0x453a70'
         and original[55].op_str=='0x46d000'
         and original[58].op_str=='0x453d40'
         and original[59].op_str=='0x52cb4f',
         'native original stage258 floatX projectile/real PE call grammar changed')
    src=source()
    obj=compile_one(src)
    code,refs,ins,ret,k=parsed(rd,d,obj)
    need((ret,len(ins),len(refs),len(code)-ret)==(33796,9510,1155,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'selected whole fighter normal VC7.1 PE/COFF/x86/ABI changed')
    ds,ss,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(ds>0 and ss>0 and maps>0,'five real 901B original switch tables missing')
    now=ins[k-60:k]
    case=f834.physical_case(rd,pe,d,code,refs,now,by,
                            0x258,206,6,BAD,0x259,f820)
    need(case['native_complete_x86']==60
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[59]
         and now[-1].op_str==hex(ret-4)
         and now[44].op_str.startswith('dword ptr [ebp - 0xb4],')
         and now[45].mnemonic=='fild'
         and now[36].mnemonic=='mov' and now[36].size==3,
         'native original sprite 258 and narrow facing/FILD source differs')
    lo=now[0].address
    fields=[r for r in refs if lo<=r['offset']<now[-1].address+now[-1].size]
    mask=f820.physical_fields(rd,rd.pe_bytes_at(pe,by[0x258],206),
                  by[0x258],fields,lo,6)
    need(len(mask)==24,'all six genuine original PE fields missing')
    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],now[ordinal]
        found=[r for r in fields if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['type']=='REL32'
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and sym in found[0]['symbol']
             and found[0]['offset']-lo==a.address-by[0x258]+a.size-4
             and a.op_str==f'0x{target:x}',
             'real original 258 physical call destination/offset differs '+str(ordinal))
        offsets.append(found[0]['offset']-lo)
    need(offsets==OFFSETS and len(BAD)==36 and BAD[-2:]==[202,203],
         'real original 258 native GPR/GIANT JMP byte negatives changed')
    # Wrong C++ 4th formal int changes native 3B MOV r8 to 4B MOVSX.
    method='void SpawnFloatXRawYAt453A70(int,float,int,char,int);'
    need(src.count(method)==1,'native 258 narrow method declaration moved')
    badsrc=src.replace(method,'void SpawnFloatXRawYAt453A70(int,float,int,int,int);',1)
    badobj=compile_one(badsrc,tag='nonnative-wide-facing')
    badcode,badrefs,badI,badret,badk=parsed(rd,d,badobj)
    wide=badI[badk-60:badk]
    need((badret,len(badI),len(badrefs),len(badcode)-badret)==(33797,9510,1155,901)
         and wide[-1].address+wide[-1].size-wide[0].address==207
         and wide[36].mnemonic=='movsx' and wide[36].size==4
         and original[36].mnemonic=='mov' and original[36].size==3,
         'wrong 32bit-facing argument must be rejected by complete native machine extent')
    # Prior 57 physical source cases (46 exact instruction
    # geometries, 1FD one-byte negative, four following normal
    # shape, three shifted 252..254, three complete 255..257).
    prior=json.loads((R/'.analysis/f880-scripted-255-257/verified-summary.json').read_text())
    old=prior['previous_46_original_game_cases_reverified']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         '46 previously complete original source-backed actions lost')
    prefix_end=k-60-205-207-(107+107+149+177+80)
    prefix=ins[prefix_end-sum(x['native_complete_x86'] for x in old):prefix_end]
    pos=0;older=[]
    for j,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[j+1]['case'],16) if j+1<len(old) else 0x1fd
        sec=prefix[pos:pos+x['native_complete_x86']]
        pos+=x['native_complete_x86']
        older.append(f834.physical_case(rd,pe,d,code,refs,sec,by,action,
                 x['native_whole_inner_B'],x['original_typed_PE_fields'],
                 x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(sec[3].op_str==sec[7].op_str==hex(sec[22].address),
                 'original native 1A0 both mul operations must be guarded')
    need(pos==len(prefix),'prior 46 original game code intervals truncated')
    block=ins[prefix_end:k-60-205-207]
    one,fe,ff,act200,act201=block[:107],block[107:214],block[214:363],block[363:540],block[540:]
    orig1=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(one[-1].address+one[-1].size-one[0].address==385
         and orig1[99].size==6 and one[99].size==5
         and one[100].op_str==hex(one[104].address),
         'original 1FD real one-byte accumulator-CMP defect must remain nonexact')
    for action,nxt,sec,nb,nf,bad in [
       (0x1fe,0x1ff,fe,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,ff,533,9,f875.BAD),
       (0x200,0x201,act200,634,10,f877.BAD),
       (0x201,0x252,act201,267,8,f878.BAD)]:
        verified=f834.physical_case(rd,pe,d,code,refs,sec,by,
                                  action,nb,nf,bad,nxt,f820)
        need(verified['original_typed_PE_fields']==nf,'previous full game case incorrect '+hex(action))
    triple=ins[k-60-205-207:k-60-205]
    pos=0;oldshifts=[]
    prev879=prior['previous_252_253_254_rechecked_with_false_size_proof']
    need(len(prev879)==3,'previous actual 252..254 byte phase receipts missing')
    for record in prev879:
        action=int(record['case'],16)
        nx=72 if action!=0x254 else 63
        sec=triple[pos:pos+nx];pos+=nx
        lo2,hi2=sec[0].address,sec[-1].address+sec[-1].size
        nb=260 if action!=0x254 else 224
        sb=259 if action==0x252 else 225 if action==0x254 else 260
        ff=[r for r in refs if lo2<=r['offset']<hi2]
        need(hi2-lo2==sb and len(ff)==6,
             'real PE call count or incorrect native byte length in 252/254 drifted')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,sec,by,
                            action,nb,6,f879.BAD_253,0x254,f820)
        else:
            origp=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and origp[10].mnemonic==sec[10].mnemonic=='sub'
                 and all(r['offset']-lo2==
                         origp[next(j for j,op in enumerate(sec)
                                    if op.address<=r['offset']<op.address+op.size)].address-by[action]+
                         origp[next(j for j,op in enumerate(sec)
                                    if op.address<=r['offset']<op.address+op.size)].size-4+(sb-nb)
                         for r in ff),
                 'real original 252/254 one-byte PE positions cannot be called exact')
            oldshifts.append({'case':hex(action),'native_B':nb,'source_B':sb,'wrong_entire_PE_offsets':True})
    need(pos==len(triple),'prior 252-254 physical interiors overlapped')
    recent=ins[k-60-205:k-60]
    pos=0;newer=[]
    for a,nxt,nb,nx,nf in f880.CASES:
        sec=recent[pos:pos+nx];pos+=nx
        newer.append(f834.physical_case(rd,pe,d,code,refs,sec,by,
                                       a,nb,nf,f880.BAD[a],nxt,f820))
    need(pos==len(recent),'prior 255-257 physical case intervals truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
                [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    bad_tail=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(bad_tail==[10,12,16,19],
         'native common 46B shared getter real GPR phase changed')
    out={'native_original_fighter':'0x005214B0',
       'original_whole_callable_CODE_B':46755,
       'generated_current_whole_source_CODE_B':ret,
       'new_real_original_258_complete_case':case,
       'physical_258_PE_CALL_offsets':offsets,
       'native_real_258_float_X_FILD_EBP_minus':'0xB4',
       'native_true_facing_argument_formal':'char',
       'wrong_int_facing_generated_complete_258_CODE_B':207,
       'original_258_true_register_byte_mismatches':34,
       'original_258_giant_epilogue_JMP_wrong_bytes':[202,203],
       'prior_46_native_game_cases_reverified':older,
       'prior_1FD_original_cmp_1B_negative_preserved':True,
       'prior_1FE_1FF_200_201_rechecked':True,
       'prior_252_254_byte_phase_wrong_fields_rechecked':oldshifts,
       'prior_255_256_257_rechecked':newer,
       'native_46B_getter_GPR_wrong_offsets':bad_tail,
       'five_original_901B_afterRET_tables_reverified':True,
       'original_switch_afterRET_DATA_B':901,
       'original_entire_game_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_game_giant_exact'] is False
    print('F881 original258 206B/60x86/6 authentic physical PE calls mixed float X from native FILD EBP-B4 and raw integer Y; actual sprite340, 46D000 FA and Prepare5. Wrong int facing produces 207B MOVSX not native 3B MOV. Whole fighter 33796B/9510x86, 34 GPR plus two original giant JMP bytes wrong; preceding 57 original native cases and five packed 901B tables checked. Whole 46755B giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as err:
        print('F881 original game 258 full PE proof FAILED:',err,file=sys.stderr)
        raise SystemExit(1)
