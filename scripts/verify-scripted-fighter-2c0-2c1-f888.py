#!/usr/bin/env python3
"""F888: two 2C0/2C1 original 288/276B PE-backed game states.

Unlike initial plausible source, original sprite345 is INSIDE
the current-action matching conditional: JNE must jump
directly to this case's whole-fighter epilogue JMP, not
skip only SetAction and fire unconditionally.
Compile complete normal VC7.1 parent, inspect every
physical PE field and all earlier 63 game-state interiors.
Both cases then have only two original giant-epilogue
JMP bytes different; no GPR or branch error. Recheck all
901B separately owned packed jump DATA. No cold mass replay.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f888-scripted-2c0-2c1'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
CASES=((0x2c0,0x2c1,288,85,8,0x73),
       (0x2c1,0x2c2,276,81,9,0x74))
BAD={0x2c0:[284,285],0x2c1:[272,273]}
FIELD_ORDS={0x2c0:[15,26,29,32,35,44,52,60,68,75,83],
            0x2c1:[15,26,29,32,35,44,52,54,64,71,79]}
FIELD_OFFS={0x2c0:[60,93,103,113,128,158,179,211,235,255,279],
            0x2c1:[60,93,103,113,128,158,179,187,223,243,267]}
DEST={15:(0x453e20,'ResetAt453E20'),
      26:(0x453e80,'AnimatePushAt453E80'),
      29:(0x453d60,'PrepareActionAt453D60'),
      32:(0x453d40,'PrepareActionAt453D40'),
      35:(0x657888,'g_ContactProjectionAt00657888'),
      44:(0x657888,'g_ContactProjectionAt00657888'),
      52:(0x453c80,'SpawnMixedAt453C80'),
      60:(0x40fa30,'GetNativeActionAt40FA30'),
      68:(0x40fac0,'SetNativeActionAt40FAC0'),
      75:(0x657888,'g_ContactProjectionAt00657888'),
      83:(0x453b50,'SpawnExtraAt453B50'),
      54:(0x40fa30,'GetNativeActionAt40FA30'),
      64:(0x40fac0,'SetNativeActionAt40FAC0'),
      71:(0x657888,'g_ContactProjectionAt00657888'),
      79:(0x453b50,'SpawnExtraAt453B50')}
def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,name):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/name)
    need(sp is not None and sp.loader is not None,'missing original PE helper '+name)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m);return m
def source():
    O.mkdir(parents=True,exist_ok=True)
    prev=R/'.analysis/f887-scripted-followups/Boss005214B0-F887-whole.cpp'
    rec=R/'.analysis/f887-scripted-followups/verified-summary2bf.json'
    if not prev.is_file() or not rec.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
                str(R/'scripts/verify-scripted-fighter-2bf-f887.py')],
                cwd=R,capture_output=True,text=True,timeout=1400)
        (O/'prior-original-f887.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous physical original 2BF proof failed '+(cp.stdout+cp.stderr)[-680:])
    old=json.loads(rec.read_text())
    need(old['generated_new_full_source_CODE_B']==36519
         and old['original_complete_fighter_exact'] is False,
         'previous 2BF current whole PE evidence changed')
    cpp=prev.read_text()
    for a,nxt,nb,nx,pre,sp in CASES:
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        frag=(R/f'probes/FighterScriptedStage{a:X}F888.inc').read_text()
        need(cpp.count(marker)==1 and frag.count(f'case 0x{a:X}:')==1
             and frag.count('return;')==1
             and 'SpawnMixedAt453C80(0x' in frag
             and f'PrepareActionAt453D40({pre})' in frag
             and f'SpawnMixedAt453C80(0x{sp:X}' in frag
             and frag.index('if (GetNativeActionAt40FA30()==S16(0x70))') <
                 frag.index('SpawnExtraAt453B50(0x345') <
                 frag.rindex('    }') ,
             'true original sprite345 is NOT within action completion condition '+hex(a))
        if a==0x2c0:
            need('if (S16(0x62)>10)' in frag
                 and frag.index('S16(0xF10)=0x1A4;') <
                     frag.index('if (GetNativeActionAt40FA30()'),
                 '2C0 original thresholdF10 outside action match changed')
        else:
            need('if (S16(0x62)>10)' not in frag
                 and frag.index('S16(0xF10)=0x1A4;') >
                     frag.index('if (GetNativeActionAt40FA30()'),
                 '2C1 original F10 assignment must be inside action guard')
        cpp=cpp.replace(marker,f'#include "FighterScriptedStage{a:X}F888.inc"',1)
    return cpp
def compile_one(cpp,tag):
    p=O/('Boss005214B0-F888-'+tag+'.cpp');obj=O/('Boss005214B0-F888-'+tag+'.obj')
    p.write_text(cpp)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(R/'scripts/compile-probe.sh'),str(p),str(obj),
          '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
          cwd=R,env=env,capture_output=True,text=True,timeout=330)
    (O/('compiler-'+tag+'.log')).write_text(result.stdout+result.stderr)
    need(result.returncode==0,'full native 2C0/2C1 '+tag+' VC7.1 failed '+(result.stdout+result.stderr)[-680:])
    return obj
def parse(rd,d,obj):
    code,refs=rd.object_function(obj,SYM);I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    marks=[j for j,x in enumerate(I) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x2c3')
           and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=166,'original physical 2C2 next handler marker missing')
    return code,refs,I,ret,marks[0]

def main():
    rd=ld('f888rd','compare-coff-function.py')
    ac=ld('f888ac','report-fighter-action-handlers.py')
    f834=ld('f888f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f888f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f888f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f888f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f888f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f888f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f888f879','verify-scripted-fighter-stage-252-254-f879.py')
    f880=ld('f888f880','verify-scripted-fighter-stage255-257-f880.py')
    f881=ld('f888f881','verify-scripted-fighter-floatx-258-f881.py')
    f883=ld('f888f883','verify-scripted-fighter-physical259-f883.py')
    f884=ld('f888f884','verify-scripted-fighter-stage2bc-f884.py')
    f885=ld('f888f885','verify-scripted-fighter-stage2bd-f885.py')
    f886=ld('f888f886','verify-scripted-fighter-stage2be-f886.py')
    f887=ld('f888f887','verify-scripted-fighter-2bf-f887.py')
    zero=ld('f888zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f888sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original giant complete native CODE or packed DATA identity changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(source(),'whole')
    code,refs,I,ret,k=parse(rd,d,obj)
    need((ret,len(I),len(refs),len(code)-ret)==(37053,10463,1252,901)
         and I[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'complete 2C0/2C1 VC7.1 source COFF/ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,I,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'five original packed 901B afterRET tables not verified')
    new=[]
    for action,nxt,nb,nx,prep,sprite in CASES:
        back=166 if action==0x2c0 else 81
        seg=I[k-back:k-back+nx]
        lo,hi=seg[0].address,seg[-1].address+seg[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[nxt]-by[action])
        native=list(d.disasm(raw,by[action]))
        need((len(raw),len(native),hi-lo,len(seg))==(nb,nx,nb,nx)
             and native[30].op_str==str(prep)
             and native[50].op_str==hex(sprite)
             and native[-1].op_str=='0x52cb4f',
             'original native 2C0/2C1 real initial/sprite/whole source changed '+hex(action))
        row=f834.physical_case(rd,pe,d,code,refs,seg,by,
                    action,nb,11,BAD[action],nxt,f820)
        need(row['native_complete_x86']==nx
             and row['original_native_enclosing_parent_JMP_exit_ordinals']==[nx-1]
             and seg[-1].op_str==hex(ret-4),
             'native 2C0/2C1 entire code/parent exit mismatches '+hex(action))
        jne_ord=65 if action==0x2c0 else 59
        need(native[jne_ord].mnemonic==seg[jne_ord].mnemonic=='jne'
             and native[jne_ord].op_str==hex(native[-1].address)
             and seg[jne_ord].op_str==hex(seg[-1].address),
             'genuine sprite345 must run ONLY on real action match '+hex(action))
        field=[r for r in refs if lo<=r['offset']<hi]
        mask=f820.physical_fields(rd,raw,by[action],field,lo,11)
        need(len(mask)==44,'eleven original PE fields unverified '+hex(action))
        offsets=[]
        for ordinal in FIELD_ORDS[action]:
            dst,sym=DEST[ordinal]
            a,b=native[ordinal],seg[ordinal]
            found=[r for r in field if b.address<=r['offset']<b.address+b.size]
            need(len(found)==1 and found[0]['addend']==0
                 and found[0]['local_symbol_offset'] is None
                 and found[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
                 and sym in found[0]['symbol']
                 and found[0]['offset']-lo==a.address-by[action]+a.size-4
                 and a.op_str==(f'0x{dst:x}' if a.mnemonic=='call'
                                       else f'dword ptr [0x{dst:x}]'),
                 'original 2C0/2C1 actual PE symbol/operand target differs '+hex(action)+' '+str(ordinal))
            offsets.append(found[0]['offset']-lo)
        need(offsets==FIELD_OFFS[action],'native 2C0/2C1 source PE operand offsets moved '+hex(action))
        new.append({'case':hex(action),'original_complete_native':row,
                    'true_PE_field_offsets':offsets,
                    'real_genuine_GPR_and_branch_wrong_B':0,
                    'real_enclosing_giant_epilogue_wrong_offsets':BAD[action]})
    # One source-equivalent (equal size!) but functionally WRONG
    # negative: fire sprite345 outside matching condition.
    src=source()
    for action,nxt,nb,nx,prep,sprite in CASES:
        marker=f'#include "FighterScriptedStage{action:X}F888.inc"'
        frag=(R/f'probes/FighterScriptedStage{action:X}F888.inc').read_text()
        incorrect=frag.replace(
            '        SetNativeActionAt40FAC0(0);\n        SpawnExtraAt453B50',
            '        SetNativeActionAt40FAC0(0);\n    }\n    SpawnExtraAt453B50',1)
        incorrect=incorrect.replace(
            'g_ContactProjectionAt00657888,1,1,0,1);\n    }\n    return;',
            'g_ContactProjectionAt00657888,1,1,0,1);\n    return;',1)
        need(incorrect!=frag and marker in src,
             'cannot construct authentic false unconditional sprite branch')
        src=src.replace(marker,incorrect,1)
    falseobj=compile_one(src,'bad-unguarded-sprite')
    wrongcode,wrongrefs,wrongI,wrongret,wrongk=parse(rd,d,falseobj)
    need((wrongret,len(wrongI),len(wrongrefs),len(wrongcode)-wrongret)==(37053,10463,1252,901),
         'false guard control should be deceptively equal-sized whole parent')
    for action,nxt,nb,nx,prep,sprite in CASES:
        back=166 if action==0x2c0 else 81
        sec=wrongI[wrongk-back:wrongk-back+nx]
        lo=sec[0].address;high=sec[-1].address+sec[-1].size
        raw=rd.pe_bytes_at(pe,by[action],nb)
        f=[r for r in wrongrefs if lo<=r['offset']<high]
        mask={j for r in f for j in range(r['offset']-lo,r['offset']-lo+4)}
        wrong=[j for j in range(nb) if j not in mask and raw[j]!=wrongcode[lo+j]]
        expected=[228,284,285] if action==0x2c0 else [204,272,273]
        need(wrong==expected,'actual false source must differ by real game JNE target '+hex(action))
    # Full parent: physically verify 63 preceding original game
    # case sources, including negative 1FD and shifted 252/254.
    previous=json.loads((R/'.analysis/f887-scripted-followups/verified-summary2bf.json').read_text())
    old=previous['prior_46_physical_cases_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'previous 46 physical original cases not available')
    recent_count=107+107+149+177+80+207+205+60+60+228+239+136+138
    tail_end=k-166
    early_end=tail_end-recent_count
    prefix=I[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    pos=0;older=[]
    for idx,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[idx+1]['case'],16) if idx+1<len(old) else 0x1fd
        part=prefix[pos:pos+x['native_complete_x86']];pos+=x['native_complete_x86']
        older.append(f834.physical_case(rd,pe,d,code,refs,part,by,
             action,x['native_whole_inner_B'],x['original_typed_PE_fields'],
             x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(part[3].op_str==part[7].op_str==hex(part[22].address),
                 'original 1A0 one-shot multiplier guard drifted')
    need(pos==len(prefix),'46 prior native game cases truncated')
    recent=I[early_end:tail_end]
    origfd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    fd=recent[:107]
    need(fd[-1].address+fd[-1].size-fd[0].address==385
         and origfd[99].size==6 and fd[99].size==5
         and fd[100].op_str==hex(fd[104].address),
         'genuine native 1FD CMP and owner condition negative changed')
    cur=107
    for action,nxt,n,nb,nf,bad in (
       (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,149,533,9,f875.BAD),
       (0x200,0x201,177,634,10,f877.BAD),
       (0x201,0x252,80,267,8,f878.BAD)):
        sec=recent[cur:cur+n];cur+=n
        f834.physical_case(rd,pe,d,code,refs,sec,by,action,nb,nf,bad,nxt,f820)
    shifts=[]
    for action,nxt,nb,nx,sb,_ in f879.CASES:
        sec=recent[cur:cur+nx];cur+=nx
        lo=sec[0].address;hi=sec[-1].address+sec[-1].size
        ff=[r for r in refs if lo<=r['offset']<hi]
        need(hi-lo==sb and len(ff)==6,'252/254 native 1-byte PE register phase changed')
        if action==0x253:
            f834.physical_case(rd,pe,d,code,refs,sec,by,action,260,6,f879.BAD_253,0x254,f820)
        else:
            n=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                and all(r['offset']-lo==
                 n[next(i for i,x in enumerate(sec) if x.address<=r['offset']<x.address+x.size)].address-by[action]+
                 n[next(i for i,x in enumerate(sec) if x.address<=r['offset']<x.address+x.size)].size-4+(sb-nb)
                 for r in ff),
                 'original 252/254 physically shifted PE references must stay NONEXACT')
            shifts.append(hex(action))
    for action,nxt,nb,n,nf in f880.CASES:
        sec=recent[cur:cur+n];cur+=n
        f834.physical_case(rd,pe,d,code,refs,sec,by,action,nb,nf,f880.BAD[action],nxt,f820)
    for action,nxt,n,nb,nf,bad in (
       (0x258,0x259,60,206,6,f881.BAD),
       (0x259,0x2bc,60,206,6,f883.BAD),
       (0x2bc,0x2bd,228,803,22,f884.BAD),
       (0x2bd,0x2be,239,855,24,f885.WRONG),
       (0x2be,0x2bf,136,461,15,f886.BAD),
       (0x2bf,0x2c0,138,473,15,[469,470])):
        sec=recent[cur:cur+n];cur+=n
        f834.physical_case(rd,pe,d,code,refs,sec,by,action,nb,nf,bad,nxt,f820)
    need(cur==len(recent),'all 63 earlier original native case interiors not rechecked')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
                  [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tailwrong=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    # This newly expanded real VC7.1 whole switch changes the
    # compiler's GPR allocation phase: native common getter is NOW
    # 34/34 byte-identical outside its three original PE call fields.
    # Previous F887 inherited four genuine old-parent mismatches;
    # never assert them as immutable facts about new compiled parents.
    need(tailwrong==[] and len(mask)==12,
         'native common getter should now match all 34 nonfield bytes')
    result={'original_giant':'0x005214B0',
       'original_complete_callable_CODE_B':46755,
       'new_whole_source_callable_CODE_B':ret,
       'two_real_original_2C0_2C1_cases':new,
       'original_combined_case_CODE_B':564,
       'original_total_true_PE_fields':22,
       'native_real_sprite345_inside_action_guard':True,
       'nonnative_same_sized_wrong_guard_JNE_rejected':True,
       'real_GPR_wrong_B_both_cases':0,
       'real_giant_epilogue_JMP_wrong_bytes':[284,285,272,273],
       'previous_46_native_game_cases_rechecked':older,
       'previous_1FD_native_CMP_byte_negative_retained':True,
       'previous_252_254_actual_shifted_PE_fields':shifts,
       'all_63_preceding_physical_original_cases_rechecked':True,
       'original_getter_46B_nonrelocation_wrong_offsets':tailwrong,
       'native_getter_34_of_34_original_nonfield_bytes_equal':True,
       'original_five_901B_afterRET_packed_tables_reverified':True,
       'original_separate_afterRET_DATA_B':901,
       'original_entire_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_giant_exact'] is False
    print('F888 real 2C0 288B/85x86/11 PE fields and 2C1 276B/81x86/11 fields now match all original nonrelocation bytes except two external giant JMP bytes each, and original sprite345 JNE guard target restored. Equal-length WRONG unguarded sprite controls rejected. Full fighter 37053B/10463 x86, prior63 native game cases and five packed 901B tables checked; whole original 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F888 original 2C0/2C1 whole native proof FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
