#!/usr/bin/env python3
"""F883: correct original 259 PHYSICAL extent ends at 2BC, not numeric 25A.

The original fighter's packed switch has 259 at 00529746,
numeric 25A maps to default 0052CB25, BUT the next real
original CODE handler is 2BC at 00529814. Thus actual 259
bounded interior is 206B/60x86/6 PE calls, NOT a purported
13279-byte case from numeric successor. Its sprite34D
stage2 FILD EBP-B8, StartAnimation46D000(1F4), Prepare5
are native code. Recompile one affected whole VC7.1
parent; all six original physical PE calls, previous 58
game states incl 1FD and 252/254 negative field shifts,
five 901B packed afterRET tables. No independent
whole-callable exact CODE accepted.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f883-scripted-stage259'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,31,35,43,46,53,56,72,74,78,81,95,99,102,107,111,114,120,123,125,127,130,132,134,138,141,144,156,159,202,203]
FIELDS={9:(0x453e20,'ResetAt453E20'),
        17:(0x40fa30,'GetNativeActionAt40FA30'),
        25:(0x40fac0,'SetNativeActionAt40FAC0'),
        52:(0x453a70,'SpawnFloatXRawYAt453A70'),
        55:(0x46d000,'StartAnimationAt46D000'),
        58:(0x453d40,'PrepareActionAt453D40')}
OFFSETS=[26,66,90,174,187,197]
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'original PE helper missing '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m

def make_source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f881-scripted-stage258/Boss005214B0-F881-whole.cpp'
    receipt=R/'.analysis/f881-scripted-stage258/verified-summary.json'
    if not prev.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-floatx-258-f881.py')],
             cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'prior-f881-original.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous full native case258 physical proof failed '+(cp.stdout+cp.stderr)[-740:])
    old=json.loads(receipt.read_text())
    need(old['generated_current_whole_source_CODE_B']==33796
         and old['original_entire_game_giant_exact'] is False,
         'previous 258 native whole source receipt changed')
    src=prev.read_text()
    marker='        case 0x259: g_FighterProbeMarker = 602; break;'
    fragment=(R/'probes/FighterScriptedFloatX259F883.inc').read_text()
    need(src.count(marker)==1 and fragment.count('case 0x259:')==1
         and fragment.count('return;')==1
         and 'SpawnFloatXRawYAt453A70(0x34D' in fragment
         and 'StartAnimationAt46D000(0x1F4)' in fragment
         and 'PrepareActionAt453D40(5)' in fragment
         and 'I32(0x7C)=1;' in fragment,
         'original bounded native 259 source or actual stage2 actions changed')
    return src.replace(marker,'#include "FighterScriptedFloatX259F883.inc"',1)
def compile_one(src):
    cpp=O/'Boss005214B0-F883-whole.cpp'
    obj=O/'Boss005214B0-F883-whole.obj'
    cpp.write_text(src)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=310)
    (O/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'normal original physical 259 whole fighter compile failed '+(cp.stdout+cp.stderr)[-710:])
    return obj

def main():
    rd=ld('f883rd','compare-coff-function.py')
    ac=ld('f883ac','report-fighter-action-handlers.py')
    f834=ld('f883f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f883f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f883f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f883f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f883f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f883f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f883f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f883f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f883f881','verify-scripted-fighter-floatx-258-f881.py')
    zero=ld('f883zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f883switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original whole fighter or native afterRET jump tables changed')
    report,mp=ac.report_boss(rd,pe,d,boss);by={x['action']:int(x['handler'],16) for x in mp}
    # This proof uses the next ACTUAL PHYSICAL code handler,
    # not the next numeric action which points to fallback.
    native_start=by[0x259]
    physical_end=min(x for x in by.values() if x>native_start)
    need(native_start==0x529746 and by[0x25a]==0x52cb25
         and by[0x2bc]==physical_end==0x529814
         and physical_end-native_start==206
         and by[0x25a]-native_start==13279,
         'real physical native 259 boundary and sparse table changed')
    raw=rd.pe_bytes_at(pe,native_start,206)
    original=list(d.disasm(raw,native_start))
    need(len(original)==60 and original[44].op_str.startswith('dword ptr [ebp - 0xb8],')
         and original[45].mnemonic=='fild'
         and original[50].op_str=='0x34d'
         and original[52].op_str=='0x453a70'
         and original[53].op_str=='0x1f4'
         and original[55].op_str=='0x46d000'
         and original[58].op_str=='0x453d40'
         and original[59].op_str=='0x52cb4f',
         'original bounded 259 native float X game behavior changed')
    obj=compile_one(make_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(33987,9568,1160,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'one affected native whole parent CODE/x86/ABI/COFF geometry changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'five original 901B packed afterRET tables missing')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x2bd')
           and any('g_FighterProbeMarker' in r['symbol']
                  and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=60,
         'actual following native physical handler 2BC source marker missing')
    k=marks[0];sec=ins[k-60:k]
    # The source is 206B inner original code before 2BC.
    case=f834.physical_case(rd,pe,d,code,refs,sec,by,0x259,206,6,BAD,0x2bc,f820)
    need(case['native_complete_x86']==60
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[59]
         and sec[-1].op_str==hex(ret-4)
         and sec[44].op_str.startswith('dword ptr [ebp - 0xb8],')
         and sec[45].mnemonic=='fild',
         'native 259 floatX physical code or whole-giant tail differs')
    lo=sec[0].address
    ff=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,native_start,ff,lo,6)
    need(len(mask)==24,'six native original 259 PE call fields unverified')
    offsets=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=original[ordinal],sec[ordinal]
        found=[r for r in ff if b.address<=r['offset']<b.address+b.size]
        need(len(found)==1 and found[0]['type']=='REL32'
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and sym in found[0]['symbol']
             and found[0]['offset']-lo==a.address-native_start+a.size-4
             and a.op_str==f'0x{target:x}',
             'physical original 259 PE source/target incorrect at ordinal '+str(ordinal))
        offsets.append(found[0]['offset']-lo)
    need(offsets==OFFSETS and BAD==f881.BAD,
         'actual 259 original PE offsets/genuine register/JMP negative bytes changed')
    # Recheck all 58 previously source-backed physical native
    # case intervals in the SAME new full VC7.1 compiler parent.
    old=json.loads((R/'.analysis/f881-scripted-stage258/verified-summary.json').read_text())
    native_old=old['prior_46_native_game_cases_reverified']
    need(len(native_old)==46 and native_old[0]['case']=='0xc8' and native_old[-1]['case']=='0x1fc',
         'previous 46 physical native source game cases missing')
    first_end=k-60-(107+107+149+177+80+207+205+60)
    prefix=ins[first_end-sum(x['native_complete_x86'] for x in native_old):first_end]
    pos=0;checked=[]
    for j,x in enumerate(native_old):
        action=int(x['case'],16)
        nxt=int(native_old[j+1]['case'],16) if j+1<len(native_old) else 0x1fd
        s=prefix[pos:pos+x['native_complete_x86']];pos+=x['native_complete_x86']
        checked.append(f834.physical_case(rd,pe,d,code,refs,s,by,action,
                 x['native_whole_inner_B'],x['original_typed_PE_fields'],
                 x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(s[3].op_str==s[7].op_str==hex(s[22].address),
                 'native stage0 multiplier guard 1A0 false source returned')
    need(pos==len(prefix),'46 earlier native case intervals truncated')
    block=ins[first_end:k-60-207-205-60]
    fd,fe,ff,st200,st201=block[:107],block[107:214],block[214:363],block[363:540],block[540:]
    orig_fd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(fd[-1].address+fd[-1].size-fd[0].address==385
         and orig_fd[99].size==6 and fd[99].size==5
         and fd[100].op_str==hex(fd[104].address),
         'actual original 1FD one-byte CMP negative and status CFG changed')
    for action,nxt,s,nb,nf,bad in [
       (0x1fe,0x1ff,fe,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,ff,533,9,f875.BAD),
       (0x200,0x201,st200,634,10,f877.BAD),
       (0x201,0x252,st201,267,8,f878.BAD)]:
        f834.physical_case(rd,pe,d,code,refs,s,by,action,nb,nf,bad,nxt,f820)
    triple=ins[k-60-207-205-60:k-60-205-60]
    pos=0;bad_shifts=[]
    for action,nxt,nb,nx,sb,special in f879.CASES:
        s=triple[pos:pos+nx];pos+=nx;lo2=s[0].address
        hi2=s[-1].address+s[-1].size
        fields=[r for r in refs if lo2<=r['offset']<hi2]
        need(hi2-lo2==sb and len(fields)==6,'252-254 source native byte phase or fields moved')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,s,by,0x253,260,6,f879.BAD_253,0x254,f820)
        else:
            N=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and N[10].mnemonic==s[10].mnemonic=='sub'
                 and all(r['offset']-lo2==
                    N[next(i for i,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)].address-by[action]+
                    N[next(i for i,x in enumerate(s) if x.address<=r['offset']<x.address+x.size)].size-4+(sb-nb)
                    for r in fields),
                 'physical 252/254 original PE fields must remain shifted by one byte')
            bad_shifts.append({'case':hex(action),'native_B':nb,'source_B':sb,'original_not_exact':True})
    need(pos==len(triple),'previous three byte-phase case intervals overlap')
    recent=ins[k-60-205-60:k-60-60]
    pos=0;old_three=[]
    for action,nxt,nb,nx,nf in f880.CASES:
        s=recent[pos:pos+nx];pos+=nx
        old_three.append(f834.physical_case(rd,pe,d,code,refs,s,by,
                     action,nb,nf,f880.BAD[action],nxt,f820))
    need(pos==len(recent),'old sprite37 cases 255-257 truncated')
    last=ins[k-60-60:k-60]
    last_orig=f834.physical_case(rd,pe,d,code,refs,last,by,
                      0x258,206,6,f881.BAD,0x259,f820)
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tmask=f820.physical_fields(rd,tail,0x52cb25,
              [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    gpr=[j for j in range(46) if j not in tmask and tail[j]!=code[ret-46+j]]
    need(gpr==[10,12,16,19],
         'original common getter four true GPR wrong offsets changed')
    receipt={'real_original_whole_fighter':'0x005214B0',
      'original_whole_callable_CODE_B':46755,
      'new_generated_entire_source_CODE_B':ret,
      'original_numeric_25A_handler':'0x0052CB25',
      'original_physical_next_after_259_handler_2BC':'0x00529814',
      'false_numeric_case_259_extent_B':13279,
      'correct_original_physical_case_259_extent_B':206,
      'original_case_259_full_native':case,
      'physical_PE_CALL_offsets':offsets,
      'native_original_scratch_FILD_EBP_minus':'0xB8',
      'native_sprite_kind':0x34d,
      'native_animation_call_argument':0x1f4,
      'real_original_259_GPR_wrong_B':34,
      'giant_epilogue_JMP_wrong_offsets':[202,203],
      'old_46_original_PE_cases_verified':checked,
      'old_1FD_one_byte_CMP_negative_preserved':True,
      'old_1FE_1FF_200_201_checked':True,
      'old_252_254_physical_one_byte_offsets_wrong':bad_shifts,
      'old_255_256_257_unchanged':old_three,
      'old_258_unchanged':last_orig,
      'native_common_getter_GPR_wrong_offsets':gpr,
      'all_five_original_901B_afterRET_tables_verified':True,
      'native_separate_afterRET_DATA_B':901,
      'entire_original_whole_giant_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['entire_original_whole_giant_exact'] is False
    print('F883 corrected native original 259 PHYSICAL bound 529746..529814=206B/60x86/6 real PE calls, not numeric 259..25A default giant 13279B. Native sprite34D, FILD EBP-B8, 46D000(1F4), Prepare5 restored. Whole generated fighter 33987B/9568x86, 34 GPR and two original giant JMP bytes nonexact; all preceding 58 native cases and five 901B packed DATA tables verified. Whole original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F883 physical original 259 and whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
