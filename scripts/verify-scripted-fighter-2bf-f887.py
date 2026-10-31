#!/usr/bin/env python3
"""F887 original 2BF: 473B/138 x86/15 fields, only 2 final JMP mismatches.

Pin native 2BF real stage0 redundant short +80=0x63 then +80=1,
sprites74/33D, actual two C++ __ftol2 conversions to original
6406AC. Verify a freshly compiled *whole* VC7.1 giant's native PE
field destinations and all preceding 62 game interiors, five packed
901B afterRET tables. Do not infer complete fighter exactness from
a byte-perfect interior except external enclosing epilogue JMP.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f887-scripted-followups'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
FIELDS={17:(0x453e20,'ResetAt453E20'),
 19:(0x40fa30,'GetNativeActionAt40FA30'),
 27:(0x40fac0,'SetNativeActionAt40FAC0'),
 44:(0x453e80,'AnimatePushAt453E80'),
 47:(0x453d60,'PrepareActionAt453D60'),
 50:(0x657888,'g_ContactProjectionAt00657888'),
 59:(0x659470,'g_F884Stage5YAt00659470'),
 73:(0x453c80,'SpawnAt453C80'),76:(0x6406ac,'__ftol2'),
 81:(0x6406ac,'__ftol2'),
 98:(0x453b50,'SpawnExtraRawYAt453B50'),
 109:(0x46d000,'StartAnimationAt46D000'),
 112:(0x453d40,'PrepareActionAt453D40'),
 123:(0x453e60,'InitTrajectoryAt453E60'),
 136:(0x453c80,'SpawnRawAt453C80')}
OFFSETS=[72,80,104,166,176,191,221,267,278,299,349,385,395,431,464]
def need(v,msg):
    if not v:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp and sp.loader,'missing native PE helper '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m
def native_source():
    O.mkdir(parents=True,exist_ok=True)
    oldp=R/'.analysis/f886-scripted-stage2be/Boss005214B0-F886-whole.cpp'
    receipt=R/'.analysis/f886-scripted-stage2be/verified-summary.json'
    if not oldp.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
            str(R/'scripts/verify-scripted-fighter-stage2be-f886.py')],
            cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'prior-f886.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous native original 2BE proof failed '+(cp.stdout+cp.stderr)[-690:])
    r=json.loads(receipt.read_text())
    need(r['generated_current_whole_source_CODE_B']==36061
         and r['original_entire_whole_giant_exact'] is False,
         'original previous 2BE PE receipt changed')
    src=oldp.read_text()
    marker='        case 0x2BF: g_FighterProbeMarker = 704; break;'
    frag=(R/'probes/FighterScriptedStage2BFF887.inc').read_text()
    need(src.count(marker)==1 and frag.count('case 0x2BF:')==1
         and frag.count('return;')==1
         and 'S16(0x80)=0x63;' in frag
         and 'S16(0x80)=1;' in frag
         and frag.index('S16(0x80)=0x63;')<frag.index('S16(0x80)=1;')
         and 'SpawnAt453C80(0x74' in frag
         and 'SpawnExtraRawYAt453B50(0x33D' in frag
         and 'PrepareActionAt453D40(7)' in frag
         and 'InitTrajectoryAt453E60(10.0f)' in frag
         and frag.count('static_cast<signed short>(F32(')==2,
         'genuine original 2BF stage0/register/float conversions incomplete')
    return src.replace(marker,'#include "FighterScriptedStage2BFF887.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F887-whole.cpp';obj=O/'Boss005214B0-F887-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=env,capture_output=True,text=True,timeout=330)
    (O/'compiler-f887.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'full 2BF native VC7.1 C++ compiler failed '+(cp.stdout+cp.stderr)[-690:])
    return obj

def main():
    rd=ld('f887rd','compare-coff-function.py')
    ac=ld('f887ac','report-fighter-action-handlers.py')
    f834=ld('f887f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f887f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f887f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f887f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f887f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f887f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f887f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f887f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f887f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f887f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f887f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f887f885','verify-scripted-fighter-stage2bd-f885.py')
    f886=ld('f887f886','verify-scripted-fighter-stage2be-f886.py')
    zero=ld('f887zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f887sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned whole native fighter or jump DATA changed')
    report,mapping=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mapping}
    raw=rd.pe_bytes_at(pe,by[0x2bf],by[0x2c0]-by[0x2bf]);orig=list(d.disasm(raw,by[0x2bf]))
    need((by[0x2bf],by[0x2c0],len(raw),len(orig))==(0x52a05b,0x52a234,473,138)
         and orig[13].op_str.endswith(', 0x63') and orig[15].op_str.endswith(', 1')
         and orig[71].op_str=='0x74' and orig[96].op_str=='0x33d'
         and orig[76].op_str==orig[81].op_str=='0x6406ac'
         and orig[110].op_str=='7' and orig[121].op_str=='0x41200000'
         and orig[-1].op_str=='0x52cb4f',
         'original native 2BF control flow and double short+80 assignment changed')
    obj=compile_one(native_source())
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for inst in d.disasm(code,0):
        I.append(inst)
        if inst.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    need((ret,len(I),len(refs),len(code)-ret)==(36519,10301,1232,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'one affected whole VC7.1 parent output changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'five physical original 901B packed switch tables missing')
    marks=[j for j,x in enumerate(I) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x2c1')
           and any('g_FighterProbeMarker' in r['symbol']
                  and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=138,'following native 2C0 state marker missing')
    k=marks[0];sec=I[k-138:k]
    native=f834.physical_case(rd,pe,d,code,refs,sec,by,
            0x2bf,473,15,[469,470],0x2c0,f820)
    need(native['native_complete_x86']==138
         and native['original_native_enclosing_parent_JMP_exit_ordinals']==[137]
         and sec[-1].op_str==hex(ret-4)
         and len([j for j in range(473) if j in [469,470]])==2,
         'true native 2BF otherwise exact interior physical bytes changed')
    lo=sec[0].address
    fs=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
    mask=f820.physical_fields(rd,raw,by[0x2bf],fs,lo,15)
    need(len(mask)==60,'all 15 original PE field locations not checked')
    offs=[]
    for ordinal,(target,sym) in FIELDS.items():
        a,b=orig[ordinal],sec[ordinal]
        f=[r for r in fs if b.address<=r['offset']<b.address+b.size]
        need(len(f)==1 and f[0]['addend']==0 and f[0]['local_symbol_offset'] is None
             and f[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and sym in f[0]['symbol']
             and f[0]['offset']-lo==a.address-by[0x2bf]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                               else f'dword ptr [0x{target:x}]'),
             'real native 2BF source/callee/original PE field incorrect '+str(ordinal))
        offs.append(f[0]['offset']-lo)
    need(offs==OFFSETS,'native 2BF real original call positions drifted')
    # 62 previous physical game cases in this same new parent.
    previous=json.loads((R/'.analysis/f886-scripted-stage2be/verified-summary.json').read_text())
    old=previous['prior_46_original_native_cases_physically_checked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous original 46 source-backed cases missing')
    previous_recent_count=(107+107+149+177+80+207+205+60+60+228+239+136)
    end=k-138-previous_recent_count
    before=I[end-sum(x['native_complete_x86'] for x in old):end]
    at=0;checked=[]
    for j,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[j+1]['case'],16) if j+1<len(old) else 0x1fd
        piece=before[at:at+x['native_complete_x86']];at+=x['native_complete_x86']
        checked.append(f834.physical_case(rd,pe,d,code,refs,piece,by,action,
                      x['native_whole_inner_B'],x['original_typed_PE_fields'],
                      x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(piece[3].op_str==piece[7].op_str==hex(piece[22].address),
                 'original 1A0 real multiplier guard changed')
    need(at==len(before),'original early case source intervals not contiguous')
    recent=I[end:k-138]
    one=recent[:107]
    origfd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(one[-1].address+one[-1].size-one[0].address==385
         and origfd[99].size==6 and one[99].size==5
         and one[100].op_str==hex(one[104].address),
         'real original 1FD one-byte CMP/owner status negative changed')
    cursor=107
    shapes=[
      (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
      (0x1ff,0x200,149,533,9,f875.BAD),
      (0x200,0x201,177,634,10,f877.BAD),
      (0x201,0x252,80,267,8,f878.BAD)]
    for action,nxt,n,nb,nf,bad in shapes:
        part=recent[cursor:cursor+n];cursor+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,action,nb,nf,bad,nxt,f820)
    shifted=[]
    for action,nxt,nb,n,sb,_ in f879.CASES:
        part=recent[cursor:cursor+n];cursor+=n
        start=part[0].address;stop=part[-1].address+part[-1].size
        ff=[r for r in refs if start<=r['offset']<stop]
        need(stop-start==sb and len(ff)==6,
             '252-254 original wrong register-phase case sizes changed')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,part,by,action,260,6,f879.BAD_253,0x254,f820)
        else:
            native_ins=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and all(r['offset']-start==
                   native_ins[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].address-by[action]+
                   native_ins[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].size-4+(sb-nb)
                   for r in ff),
                 'original 252/254 PE field displacements falsely accepted')
            shifted.append({'case':hex(action),'native_B':nb,'source_B':sb,'not_exact':True})
    for action,nxt,nb,n,nf in f880.CASES:
        part=recent[cursor:cursor+n];cursor+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,
             action,nb,nf,f880.BAD[action],nxt,f820)
    more=[(0x258,0x259,60,206,6,f881.BAD),
          (0x259,0x2bc,60,206,6,f883.BAD),
          (0x2bc,0x2bd,228,803,22,f884.BAD),
          (0x2bd,0x2be,239,855,24,f885.WRONG),
          (0x2be,0x2bf,136,461,15,f886.BAD)]
    for action,nxt,n,nb,nf,bad in more:
        part=recent[cursor:cursor+n];cursor+=n
        f834.physical_case(rd,pe,d,code,refs,part,by,
             action,nb,nf,bad,nxt,f820)
    need(cursor==len(recent),'all previous 62 actual source game cases not contiguous')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    tm=f820.physical_fields(rd,tail,0x52cb25,
             [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    badtail=[j for j in range(46) if j not in tm and tail[j]!=code[ret-46+j]]
    need(badtail==[10,12,16,19],
         'native shared getter four real GPR byte errors changed')
    out={'original_giant':'0x005214B0',
         'original_entire_callable_CODE_B':46755,
         'generated_new_full_source_CODE_B':ret,
         'new_original_2BF_full_native':native,
         'original_2BF_actual_PE_field_offsets':offs,
         'original_2BF_real_short80_stage0_writes':[0x63,1],
         'source_2BF_real_interior_GPR_wrong_B':0,
         'source_2BF_real_outer_giant_JMP_wrong_bytes':[469,470],
         'prior_46_physical_cases_rechecked':checked,
         'prior_1FD_original_CMP_one_byte_negative':True,
         'prior_252_254_one_byte_PE_field_shifts':shifted,
         'all_prior_original_states_through_2BE_physically_rechecked':True,
         'original_common_getter_GPR_negative_offsets':badtail,
         'all_five_901B_original_afterRET_tables_reverified':True,
         'original_independent_afterRET_DATA_B':901,
         'original_complete_fighter_exact':False,
         'new_accepted_whole_callable_CODE_B':0,
         'mass_cold_replay':False}
    (O/'verified-summary2bf.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary2bf.json').read_text())['original_complete_fighter_exact'] is False
    print('F887 original 2BF complete 473B/138x86/15 real PE fields in whole VC7.1 fighter 36519B/10301x86. All original inner nonfield bytes identical EXCEPT enclosing giant JMP +469/+470: ZERO GPR errors! Early native short80=0x63 then =1. Prior 62 original case sources and all five 901B packed DATA tables rechecked. Original 46755B callable fighter NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F887 original 2BF whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
