#!/usr/bin/env python3
"""F880: 255/256/257 three complete native sprite37 game states.

Original 258/186/258 B, 75/55/75 x86, 7/6/7 real PE fields.
State0 reset and F00=0, action-completion->9, stage5 sprite37
float Y+657888, Prepare21. Two case75 versions additionally
stage8/frame0, short F00<1, byte-authentic 16-bit ++F00
and aux action6. Compile one affected parent, check all original
physical PE field offset/type/target, old 252/254 byte register
phase mismatch, all other prior game cases and afterRET 901B DATA.
No accepted separate case or whole 46755B CODE credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f880-scripted-255-257'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
CASES=[(0x255,0x256,258,75,7),(0x256,0x257,186,55,6),(0x257,0x258,258,75,7)]
BAD={
 0x255:[1,5,8,12,16,19,31,35,43,46,53,56,63,67,84,86,90,93,107,111,114,119,123,126,132,135,137,139,142,155,158,160,182,186,189,194,198,201,205,209,215,220,224,230,231,232,234,238,254,255],
 0x256:[1,5,8,12,16,19,31,35,43,46,53,56,63,67,84,86,90,93,107,111,114,119,123,126,132,135,137,139,142,155,158,160,182,183],
 0x257:[1,5,8,12,16,19,31,35,43,46,53,56,63,67,84,86,90,93,107,111,114,119,123,126,132,135,137,139,142,155,158,160,182,186,189,194,198,201,205,209,215,220,224,230,231,232,234,238,254,255]}
OFFSETS={0x255:[26,78,102,146,167,177,249],
         0x256:[26,78,102,146,167,177],
         0x257:[26,78,102,146,167,177,249]}
CALLS={9:(0x453e20,'ResetAt453E20'),19:(0x40fa30,'GetNativeActionAt40FA30'),
       27:(0x40fac0,'SetNativeActionAt40FAC0'),42:(0x657888,'g_ContactProjectionAt00657888'),
       50:(0x453c80,'SpawnMixedAt453C80'),53:(0x453d60,'PrepareActionAt453D60'),
       73:(0x40fb40,'SetAuxActionAt40FB40')}

def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,filename):
    spec=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(spec is not None and spec.loader is not None,'original PE helper missing '+filename)
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m);return m
def native_source():
    O.mkdir(parents=True,exist_ok=True)
    previous=R/'.analysis/f879-scripted-triple252/Boss005214B0-F879-whole.cpp'
    receipt=R/'.analysis/f879-scripted-triple252/verified-summary.json'
    if not previous.is_file() or not receipt.is_file():
        run=subprocess.run([str(R/'scripts/repo-python'),
          str(R/'scripts/verify-scripted-fighter-stage-252-254-f879.py')],
          cwd=R,capture_output=True,text=True,timeout=1500)
        (O/'previous-original-f879.log').write_text(run.stdout+run.stderr)
        need(run.returncode==0,'previous genuine 252/253/254 PE source failed '+(run.stdout+run.stderr)[-780:])
    old=json.loads(receipt.read_text())
    need(old['current_generated_entire_source_CODE_B']==32948
         and old['original_entire_whole_fighter_exact'] is False,
         'previous original 252-254 whole PE evidence changed')
    src=previous.read_text()
    for a,nxt,nb,nx,nf in CASES:
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        fragment=(R/f'probes/FighterScriptedStage{a:X}F880.inc').read_text()
        need(src.count(marker)==1 and fragment.count(f'case 0x{a:X}:')==1
             and fragment.count('return;')==1
             and fragment.count('SetNativeActionAt40FAC0(9);')==1
             and fragment.count('SpawnMixedAt453C80(0x37')==1
             and fragment.count('PrepareActionAt453D60(0x21)')==1
             and fragment.count('S16(0xF00)=0;')==1,
             'genuine game action9 or sprite37 source changed '+hex(a))
        if a==0x256:need('SetAuxActionAt40FB40(6)' not in fragment,
                         'original 256 has no stage8 aux6')
        else:
            need('++S16(0xF00);' in fragment
                 and 'SetAuxActionAt40FB40(6);' in fragment,
                 'native stage8 16-bit increment and aux6 missing '+hex(a))
        src=src.replace(marker,f'#include "FighterScriptedStage{a:X}F880.inc"',1)
    return src
def compile_one(src):
    cpp=O/'Boss005214B0-F880-whole.cpp'
    obj=O/'Boss005214B0-F880-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    run=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,capture_output=True,text=True,env=env,timeout=310)
    (O/'compiler.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'normal full native staged255-257 VC7.1 source failed '+(run.stdout+run.stderr)[-700:])
    return obj

def main():
    rd=ld('f880rd','compare-coff-function.py')
    ac=ld('f880ac','report-fighter-action-handlers.py')
    f834=ld('f880f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f880f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f880f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f880f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f880f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f880f878','verify-scripted-fighter-stage-201-f878.py')
    f879=ld('f880f879','verify-scripted-fighter-stage-252-254-f879.py')
    zero=ld('f880zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f880switch','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'original Japanese fighter whole code/afterRET packed DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mp}
    obj=compile_one(native_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(33605,9452,1150,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'native 255-257 selected whole VC7.1 CODE/x86/COFF/ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'all five original separately owned packed 901B afterRET tables unverified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
           and x.op_str.endswith(', 0x259')
           and any('g_FighterProbeMarker' in r['symbol']
                   and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=205,'next real native 258 marker missing')
    k=marks[0];offset=205;new=[]
    for action,nxt,nb,nx,nf in CASES:
        sec=ins[k-offset:k-offset+nx];offset-=nx
        original=list(d.disasm(rd.pe_bytes_at(pe,by[action],by[nxt]-by[action]),by[action]))
        need(len(original)==nx and by[nxt]-by[action]==nb
             and original[25].op_str=='9'
             and original[48].op_str=='0x37'
             and original[50].op_str=='0x453c80'
             and original[53].op_str=='0x453d60',
             'real original 255/256/257 initial action/sprite PE identity wrong '+hex(action))
        physical=f834.physical_case(rd,pe,d,code,refs,sec,by,
                     action,nb,nf,BAD[action],nxt,f820)
        need(physical['native_complete_x86']==nx
             and physical['original_native_enclosing_parent_JMP_exit_ordinals']==[nx-1]
             and sec[-1].op_str==hex(ret-4),
             'real original game 255-257 whole interior native epilogue wrong '+hex(action))
        if action!=0x256:
            need(original[56].op_str.endswith(', 8')
                 and original[64].op_str.endswith(', 1')
                 and original[67].mnemonic==sec[67].mnemonic=='mov'
                 and original[68].mnemonic==sec[68].mnemonic=='add'
                 and original[67].size==sec[67].size==7
                 and original[68].size==sec[68].size==4
                 and original[73].op_str=='0x40fb40',
                 'native 16-bit increment +F00 and original aux6 missing '+hex(action))
        else:need(all(x.mnemonic!='call' or x.op_str!='0x40fb40' for x in original),
                  'original 256 does NOT call auxiliary action6')
        lo=sec[0].address;fs=[r for r in refs if lo<=r['offset']<sec[-1].address+sec[-1].size]
        mask=f820.physical_fields(rd,rd.pe_bytes_at(pe,by[action],nb),by[action],fs,lo,nf)
        need(len(mask)==4*nf,'real native PE fields count/physical destinations missing '+hex(action))
        offsets=[]
        for ordinal in (9,19,27,42,50,53)+( (73,) if action!=0x256 else ()):
            target,sym=CALLS[ordinal]
            a,b=original[ordinal],sec[ordinal]
            f=[r for r in fs if b.address<=r['offset']<b.address+b.size]
            need(len(f)==1 and f[0]['addend']==0
                 and f[0]['local_symbol_offset'] is None
                 and f[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
                 and sym in f[0]['symbol']
                 and f[0]['offset']-lo==a.address-by[action]+a.size-4
                 and a.op_str==(f'0x{target:x}' if a.mnemonic=='call'
                                   else f'dword ptr [0x{target:x}]'),
                 'native original 255-257 PE field source/target drift '+hex(action)+' '+str(ordinal))
            offsets.append(f[0]['offset']-lo)
        need(offsets==OFFSETS[action] and len(BAD[action])==(34 if action==0x256 else 50),
             'real original PE offsets/true GPR negatives moved '+hex(action))
        new.append({'case':hex(action),'original_native':physical,
            'real_original_PE_field_offsets':offsets,
            'actual_native_genuine_register_operand_wrong_B':32 if action==0x256 else 48,
            'native_enclosing_giant_final_JMP_wrong_offsets':[nb-4,nb-3]})
    need(offset==0,'three real previous original game state intervals overlapped')
    # RECHECK 54 previously original-backed states in the same new
    # whole source. Crucial original 252/254 remain wrong by one
    # physical byte each, not erased by total 744B equality.
    prior=json.loads((R/'.analysis/f879-scripted-triple252/verified-summary.json').read_text())
    old=prior['preceding_46_game_cases_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         '46 earlier verified PE case receipts missing')
    stem=ins[k-205-(107+107+149+177+80+207)-sum(x['native_complete_x86'] for x in old):
             k-205-(107+107+149+177+80+207)]
    pos=0;older=[]
    for i,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[i+1]['case'],16) if i+1<len(old) else 0x1fd
        seg=stem[pos:pos+x['native_complete_x86']];pos+=x['native_complete_x86']
        older.append(f834.physical_case(rd,pe,d,code,refs,seg,by,action,
             x['native_whole_inner_B'],x['original_typed_PE_fields'],
             x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(seg[3].op_str==seg[7].op_str==hex(seg[22].address),
                 'native 1A0 stage0 multiplier scope wrong')
    need(pos==len(stem),'previous 46 complete PE-sourced game actions truncated')
    other=ins[k-205-(107+107+149+177+80+207):k-205-207]
    first,fe,ff,act200,act201=other[:107],other[107:214],other[214:363],other[363:540],other[540:]
    orig_fd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(first[-1].address+first[-1].size-first[0].address==385
         and orig_fd[99].size==6 and first[99].size==5
         and first[100].op_str==hex(first[104].address),
         '1FD one-byte original CMP defect or corrected owner stage CFG disappeared')
    for action,nxt,seg,nb,nf,bad in [
       (0x1fe,0x1ff,fe,392,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,ff,533,9,f875.BAD),
       (0x200,0x201,act200,634,10,f877.BAD),
       (0x201,0x252,act201,267,8,f878.BAD)]:
        check=f834.physical_case(rd,pe,d,code,refs,seg,by,
                                 action,nb,nf,bad,nxt,f820)
        need(check['original_typed_PE_fields']==nf,
             'older original native complete case source incorrectly changed '+hex(action))
    # Explicitly preserve 252 and 254 false exact offset shifts.
    portion=ins[k-205-207:k-205]
    p=0;old_three=[]
    for x in prior['native_three_252_253_254_bounded_cases']:
        action=int(x['native_original_action'],16)
        nx=x['original_complete_x86'];seg=portion[p:p+nx];p+=nx
        lo,hi=seg[0].address,seg[-1].address+seg[-1].size
        nb=x['original_entire_game_case_B'];sb=x['current_entire_case_source_B']
        ff=[r for r in refs if lo<=r['offset']<hi]
        need(hi-lo==sb and len(ff)==6 and len(seg)==nx,
             'native original 252-254 BYTE GPR phase changed '+hex(action))
        if action==0x253:
            recheck=f834.physical_case(rd,pe,d,code,refs,seg,by,
                    action,nb,6,f879.BAD_253,0x254,f820)
            old_three.append(recheck)
        else:
            native=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(nb-sb==(1 if action==0x252 else -1)
                 and native[10].mnemonic==seg[10].mnemonic=='sub'
                 and len(ff)==6
                 and all(r['offset']-lo==
                        native[next(j for j,op in enumerate(seg)
                                   if op.address<=r['offset']<op.address+op.size)].address-by[action]+
                        native[next(j for j,op in enumerate(seg)
                                   if op.address<=r['offset']<op.address+op.size)].size-4+(sb-nb)
                        for r in ff),
                 'original 252/254 PE fields still misplaced, never claim exact')
            old_three.append({'case':hex(action),
                   'native_whole_inner_B':nb,
                   'source_whole_inner_B':sb,'original_typed_PE_fields':6,
                   'native_size_mismatch_B':nb-sb,'original_exact':False})
    need(p==len(portion),'previous 252-254 current source intervals not contiguous')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
                [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],
         'native common 46B getter 4 real GPR errors changed')
    out={'original_whole_fighter':'0x005214B0',
       'original_native_whole_callable_CODE_B':46755,
       'generated_full_fighter_callable_CODE_B':ret,
       'three_new_255_256_257_original_complete_cases':new,
       'new_original_full_case_CODE_B_total':702,
       'new_original_full_case_x86_total':205,
       'new_real_original_PE_field_total':20,
       'previous_46_original_game_cases_reverified':older,
       'previous_1FD_one_byte_CMP_source_negative':True,
       'previous_1FE_1FF_200_201_physically_reverified':True,
       'previous_252_253_254_rechecked_with_false_size_proof':old_three,
       'native_default_46B_GPR_wrong_offsets':wrong_tail,
       'all_five_original_packed_901B_afterRET_tables_reverified':True,
       'original_separate_afterRET_DATA_B':901,
       'original_complete_giant_exact':False,
       'new_accepted_whole_callable_CODE_B':0,
       'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_complete_giant_exact'] is False
    print('F880 native 255/256/257 complete 258/186/258B, 75/55/75 x86, 7/6/7 real original PE fields, action9 and real 16-bit stage8 ++F00 aux6. Whole fighter 33605B/9452x86, 48/32/48 genuine GPR plus whole-giant JMP errors; previous 54 originals including 252/254 one-byte phase negatives, 901B tables and native getter four real GPR errors reverified. Original whole 46755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F880 original 255-257 whole fighter FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
