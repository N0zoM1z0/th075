#!/usr/bin/env python3
"""F879: native 252/253/254 real BYTE counter and three whole case limits.

Original game inner states 252/253/254 have full native 260/260/224 B,
72/72/63 x86, SIX physical original PE call/global fields EACH.
Native decrements BYTE this+0x366 in r8 with SUB byte 1, NOT
MOVZX r32 and subtract. Under current incomplete source register
phase VC7.1 chooses AL 2B for 252 (native DL 3B), DL 3B for 253
(native CL 3B), CL 3B for 254 (native AL 2B). So complete
C++ inner extents are 259/260/225 B. Their SUM is deceptively
the same 744B as original: NEVER claim 252/254 exact or mask their
physically shifted PE relocation positions (-1/+1).
252 and 253 have real +3B6/+7C conditional +3B0=1000,
254 lacks that check, all share stage5 sprite37 with genuine
float Y global657888 and native owner+EFA reset.
Rebuild only this entire affected fighter, verify each native
PE destination/symbol and 253 physically byte/width-checked;
recheck previous 51 true native actions, original five packed
901B afterRET tables and shared getter current GPR negatives.
No full 979-unit cold replay, no inner-case credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f879-scripted-triple252'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
CASES=[
 (0x252,0x253,260,72,259,0x3e8),
 (0x253,0x254,260,72,260,0x3e8),
 (0x254,0x255,224,63,225,None)]
BAD_253=[1,5,8,12,16,19,23,26,32,35,38,52,56,64,67,74,77,84,88,96,100,106,110,113,119,123,140,142,146,149,163,167,170,175,179,182,188,191,193,195,198,211,214,216,238,241,248,256,257]
ORIGINAL_TARGETS={
 14:(0x453e20,'ResetAt453E20'),
 56:(0x657888,'g_ContactProjectionAt00657888'),
 64:(0x453c80,'SpawnMixedAt453C80'),
 67:(0x453d60,'PrepareActionAt453D60')}

def need(ok,msg):
    if not ok:raise ValueError(msg)
def ld(tag,filename):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(sp is not None and sp.loader is not None,'pinned original PE helper missing '+filename)
    mod=importlib.util.module_from_spec(sp);sys.modules[tag]=mod;sp.loader.exec_module(mod);return mod

def make_source():
    O.mkdir(parents=True,exist_ok=True)
    oldpath=R/'.analysis/f878-scripted-state201/Boss005214B0-F878-whole.cpp'
    receipt=R/'.analysis/f878-scripted-state201/verified-summary.json'
    if not oldpath.is_file() or not receipt.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-stage-201-f878.py')],
             cwd=R,capture_output=True,text=True,timeout=1500)
        (O/'f878-previous-native-proof.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'previous real native 201 verification failed '+(cp.stdout+cp.stderr)[-720:])
    prior=json.loads(receipt.read_text())
    need(prior['generated_entire_current_source_CODE_B']==32249
         and prior['original_entire_fighter_exact'] is False,
         'previous current native 201 source receipt changed')
    source=oldpath.read_text()
    for action,nxt,nb,nx,sb,special in CASES:
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        fragment=(R/f'probes/FighterScriptedStage{action:X}F879.inc').read_text()
        need(source.count(marker)==1 and fragment.count(f'case 0x{action:X}:')==1
             and fragment.count('return;')==1
             and fragment.count('--U8(0x366);')==1
             and fragment.count('SpawnMixedAt453C80(0x37')==1
             and fragment.count('(*(&POS48))+g_ContactProjectionAt00657888')==1
             and 'PrepareActionAt453D60(0x21)' in fragment
             and 'OWNER+0xEFA' in fragment,
             'selected actor original stage0 BYTE and stage5 float Y source altered '+hex(action))
        if special is None:
            need('S16(0x3B6)' not in fragment,
                 'original actor254 MUST NOT have historical 252/253 special stage')
        else:
            need('S16(0x3B6)==0 && I32(0x7C)==1' in fragment
                 and 'S16(0x3B0)=1000' in fragment,
                 'real original 252/253 conditional motion timer missing')
        source=source.replace(marker,f'#include "FighterScriptedStage{action:X}F879.inc"',1)
    return source

def compile_one(source):
    cpp=O/'Boss005214B0-F879-whole.cpp'
    obj=O/'Boss005214B0-F879-whole.obj'
    cpp.write_text(source)
    E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
    E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=E,capture_output=True,text=True,timeout=320)
    (O/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'native original staged 252/253/254 full VC7.1 compile failed '+(cp.stdout+cp.stderr)[-740:])
    return obj

def main():
    rd=ld('f879rd','compare-coff-function.py')
    ac=ld('f879ac','report-fighter-action-handlers.py')
    f834=ld('f879f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f879f820','verify-scripted-fighter-landing-trio-f820.py')
    f874=ld('f879f874','verify-scripted-fighter-owner-dual-f874.py')
    f875=ld('f879f875','verify-scripted-fighter-owner-stages-1ff-f875.py')
    f877=ld('f879f877','verify-scripted-fighter-owner-wave-200-f877.py')
    f878=ld('f879f878','verify-scripted-fighter-stage-201-f878.py')
    zero=ld('f879zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f879sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original whole giant or afterRET DATA changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={r['action']:int(r['handler'],16) for r in mp}
    obj=compile_one(make_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(32948,9253,1133,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'one current whole fighter x86/PE fields and ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'five native original packed 901B afterRET tables unverified')
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
         and x.op_str.endswith(', 0x256')
         and any('g_FighterProbeMarker' in r['symbol'] and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=207,'original subsequent 255 source marker missing')
    k=marks[0]
    results=[]
    for action,nxt,nb,nx,sb,special in CASES:
        back=sum(x[3] for x in CASES if x[0]>=action)
        section=ins[k-back:k-back+nx]
        lo,hi=section[0].address,section[-1].address+section[-1].size
        raw=rd.pe_bytes_at(pe,by[action],by[nxt]-by[action])
        original=list(d.disasm(raw,by[action]))
        need((len(raw),len(original),hi-lo,len(section))==(nb,nx,sb,nx),
             'real original full game case boundary/length differs '+hex(action))
        need(all(a.mnemonic==b.mnemonic and a.address-by[action] -
                 (b.address-lo)==(0 if a.address<=original[10].address else nb-sb)
                 for a,b in zip(original,section)),
             'native source opcode or instruction-address geometry incorrectly cropped '+hex(action))
        width_wrong=[i for i,(a,b) in enumerate(zip(original,section)) if a.size!=b.size]
        need(width_wrong==([] if action==0x253 else [10]),
             'native BYTE accumulator vs non-accumulator SUB width mismatch changed '+hex(action))
        need(original[9].mnemonic==section[9].mnemonic=='mov'
             and original[10].mnemonic==section[10].mnemonic=='sub'
             and original[10].op_str.endswith(', 1')
             and section[10].op_str.endswith(', 1')
             and original[10].size==(2 if action==0x254 else 3)
             and section[10].size==(2 if action==0x252 else 3),
             'native 252-254 real byte counter register-phase discrepancy changed '+hex(action))
        fields=[r for r in refs if lo<=r['offset']<hi]
        need(len(fields)==6,'six physically typed original PE fields absent '+hex(action))
        physical_offsets=[]
        source_offsets=[]
        for r in fields:
            ordinal=next(i for i,x in enumerate(section)
                         if x.address<=r['offset']<x.address+x.size)
            x,y=original[ordinal],section[ordinal]
            original_offset=x.address-by[action]+x.size-4
            source_offset=r['offset']-lo
            target=(int.from_bytes(raw[original_offset:original_offset+4],'little')
                if r['type']=='DIR32' else
                by[action]+original_offset+4+int.from_bytes(raw[original_offset:original_offset+4],'little',signed=True))
            expected_dest=(0x657888 if ordinal==(56 if action!=0x254 else 47) else
                     0x453e20 if ordinal==14 else
                     0x40fa30 if ordinal==(33 if action!=0x254 else 24) else
                     0x40fac0 if ordinal==(41 if action!=0x254 else 32) else
                     0x453c80 if ordinal==(64 if action!=0x254 else 55) else
                     0x453d60 if ordinal==(67 if action!=0x254 else 58) else None)
            need(expected_dest is not None
                 and target==expected_dest
                 and r['type']==('DIR32' if target==0x657888 else 'REL32')
                 and r['addend']==0 and r['local_symbol_offset'] is None
                 and (('g_ContactProjectionAt00657888' in r['symbol']) if target==0x657888 else True),
                 'native actual source PE operand differs at original '+hex(action)+' ordinal '+str(ordinal))
            need(source_offset-original_offset==(sb-nb),
                 'true nonnative one-byte source PE relocation shift hidden '+hex(action))
            physical_offsets.append(original_offset)
            source_offsets.append(source_offset)
        if action==0x253:
            actual=f834.physical_case(rd,pe,d,code,refs,section,by,
                     action,260,6,BAD_253,nxt,f820)
            need(actual['native_complete_x86']==72
                 and actual['original_native_enclosing_parent_JMP_exit_ordinals']==[71]
                 and section[-1].op_str==hex(ret-4),
                 '253 original case exact-x86 grammar or genuine JMP negative changed')
            errors=BAD_253
        else:
            # Never mask the wrong physical COFF field offsets. Keep
            # complete original size mismatch as a formal negative.
            need(sb!=nb and physical_offsets!=source_offsets
                 and section[-1].op_str==hex(ret-4),
                 '252/254 cannot be declared full original native exact')
            errors=None
        results.append({'native_original_action':hex(action),
          'original_entire_game_case_B':nb,'current_entire_case_source_B':sb,
          'original_complete_x86':nx,
          'original_physical_PE_field_offsets':physical_offsets,
          'source_actual_PE_field_offsets':source_offsets,
          'physical_PE_field_count':len(fields),
          'real_original_byte_SUB_operand':original[10].op_str,
          'current_incomplete_source_SUB_operand':section[10].op_str,
          'nonrelocation_wrong_byte_offsets_if_equal_length':errors,
          'complete_native_case_exact':False})
    need([x['original_entire_game_case_B'] for x in results]==[260,260,224]
         and [x['current_entire_case_source_B'] for x in results]==[259,260,225],
         'source register-phase case lengths unexpectedly silently accepted')
    # Recheck 51 already sourced whole game-state interiors on THIS
    # NEW compiled parent, never mass replay of 979 exact units.
    previous=json.loads((R/'.analysis/f878-scripted-state201/verified-summary.json').read_text())
    old=previous['original_46_early_original_case_sources_rechecked']
    need(len(old)==46 and old[0]['case']=='0xc8' and old[-1]['case']=='0x1fc',
         'prior reviewed 46 original game case sources missing')
    early_end=k-207-(107+107+149+177+80)
    before=ins[early_end-sum(x['native_complete_x86'] for x in old):early_end]
    cursor=0;checked=[]
    for i,x in enumerate(old):
        action=int(x['case'],16)
        nxt=int(old[i+1]['case'],16) if i+1<len(old) else 0x1fd
        seg=before[cursor:cursor+x['native_complete_x86']]
        cursor+=x['native_complete_x86']
        checked.append(f834.physical_case(rd,pe,d,code,refs,seg,by,action,
          x['native_whole_inner_B'],x['original_typed_PE_fields'],
          x['real_nonrelocation_wrong_offsets'],nxt,f820))
        if action==0x1a0:
            need(seg[3].op_str==seg[7].op_str==hex(seg[22].address),
                 'actual original game 1A0 conditional multiply scope changed')
    need(cursor==len(before),'prior46 original native case source regions truncated')
    other=ins[early_end:k-207]
    one,two,three,four,five=other[:107],other[107:214],other[214:363],other[363:540],other[540:]
    native_one=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    need(one[-1].address+one[-1].size-one[0].address==385
         and native_one[99].size==6 and one[99].size==5
         and one[100].op_str==hex(one[104].address),
         '1FD real one byte CMP defect or actual owner-status path changed')
    for a,nxt,segment,nbytes,nx,npe,bad in [
       (0x1fe,0x1ff,two,392,107,9,f874.F874_1FE_BAD),
       (0x1ff,0x200,three,533,149,9,f875.BAD),
       (0x200,0x201,four,634,177,10,f877.BAD),
       (0x201,0x252,five,267,80,8,f878.BAD)]:
        verify=f834.physical_case(rd,pe,d,code,refs,segment,by,a,nbytes,npe,bad,nxt,f820)
        need(verify['native_complete_x86']==nx,
             'previous original sourced case wrong in current giant '+hex(a))
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
             [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    tail_wrong=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(tail_wrong==[10,12,16,19],
         'true original common getter GPR phase changed')
    receipt={'original_whole_fighter':'0x005214B0',
      'original_native_whole_callable_CODE_B':46755,
      'current_generated_entire_source_CODE_B':ret,
      'native_three_252_253_254_bounded_cases':results,
      'original_three_case_CODE_B_total':744,
      'incomplete_generated_three_case_B_total':744,
      'original_three_case_full_x86_total':207,
      'two_nonexact_case_size_errors_not_creditable':[0x252,0x254],
      'source_byte_vs_native_byte_SUB_register_phase_unresolved':True,
      'original_three_case_PE_field_count_total':18,
      'preceding_46_game_cases_rechecked':checked,
      'preceding_1FD_one_byte_native_CMP_error_retained':True,
      'preceding_1FE_1FF_200_201_rechecked':True,
      'native_common_getter_real_GPR_wrong_offsets':tail_wrong,
      'all_five_original_901B_afterRET_tables_reverified':True,
      'original_separate_afterRET_DATA_B':901,
      'original_entire_whole_fighter_exact':False,
      'new_accepted_whole_callable_CODE_B':0,
      'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_entire_whole_fighter_exact'] is False
    print('F879 physical 252/253/254 original 260/260/224B 72/72/63-x86 with eighteen original PE field destination checks. Correct actual BYTE predecrement: current incomplete whole case 259/260/225B (native DL/CL/AL vs compiler AL/DL/CL), source total 744B only misleadingly equals original. 253 full 260B grammar with honest register/JMP negatives; 252/254 PHYSICAL RELOC OFFSETS WRONG by -1/+1. Prior51 cases, five 901B tables and getter 4 real GPR negatives reverified. Whole giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F879 original 252-254 native whole fighter FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
