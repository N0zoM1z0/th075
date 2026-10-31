#!/usr/bin/env python3
"""F901 original late native 31B/31C complete and whole opcode-width audit.

Selected whole fighter is now 46754B/13230-x86 vs original
46755B/13230-x86. All 13230 native x86 MNEMONICS match but
five genuine WIDTH mismatches remain, specifically action63
(2), action1FD(1), 252(1),254(1). Never claim whole exact:
443 source COFF fields are physically shifted; 16K+ raw
unaligned original byte mismatches remain if compared literally.
Original 2F8 full 1151B and both 31B 248B/74x86/8fields
and 31C 219B/63x86/7fields now match ALL original
nonrelocation bytes, including original enclosing JMP fields,
in the SAME whole selected VC7.1 codegen context.
Three whole equal-sized bad stage/threshold/sprite controls
are compiled and rejected. Verify previous 79 cases +901B DATA.
"""
from pathlib import Path
import re,collections
import json,os,subprocess,sys,importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f901-fighter-31b'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
CASES=((0x31b,0x31c,248,74,8),(0x31c,0x36,219,63,7))
WIDTH=(2885,2908,8455,8986,9130)
def need(v,msg):
    if not v:raise ValueError(msg)
def load():
    s=importlib.util.spec_from_file_location('f901context',R/'scripts/verify-scripted-fighter-context-f895.py')
    m=importlib.util.module_from_spec(s);sys.modules[s.name]=m;s.loader.exec_module(m);return m

def source():
    O.mkdir(parents=True,exist_ok=True)
    prior=R/'.analysis/f899-native-2f8/Boss005214B0-F899-whole.cpp'
    rec=R/'.analysis/f899-native-2f8/verified-summary.json'
    if not prior.is_file() or not rec.is_file():
        cp=subprocess.run([str(R/'scripts/repo-python'),
            str(R/'scripts/verify-scripted-fighter-stage2f8-f899.py')],
            cwd=R,capture_output=True,text=True,timeout=1630)
        (O/'prior-f899-original.log').write_text(cp.stdout+cp.stderr)
        need(cp.returncode==0,'prior original complete 2F8 source PE receipt not available '+(cp.stdout+cp.stderr)[-780:])
    j=json.loads(rec.read_text())
    need(j['new_complete_generated_whole_source_CODE_B']==46308
         and j['new_2F8_actual_generated_source_CODE_B']==1148
         and j['original_entire_callable_giant_exact'] is False,
         'previous F899 original game PE receipt changed')
    cpp=prior.read_text()
    cl='void ResetMotionAt40FC50();'
    need(cpp.count(cl)==1,'original game class native methods declaration moved')
    cpp=cpp.replace(cl,cl+' void ApplyStateAt454A70(int); void EmitStateAt452B30();',1)
    for a,nxt,nb,nx,nf in CASES:
        marker=f'        case 0x{a:X}: g_FighterProbeMarker = {a+1}; break;'
        inc=(R/f'probes/FighterScriptedTail{a:X}F901.inc').read_text()
        need(cpp.count(marker)==1 and inc.count(f'case 0x{a:X}:')==1
             and inc.count('return;')==1
             and 'ApplyStateAt454A70(0);' in inc
             and 'EmitStateAt452B30();' in inc
             and 'PrepareActionAt453D60(0x17);' in inc
             and 'S16(0xF00)<8' in inc,
             'original native tail source complete stage/actions missing '+hex(a))
        if a==0x31b:
            need('SpawnDirectedAt453A70(0x3E5' in inc
                 and 'S16(0x62)==4' in inc
                 and 'S16(0x62)==8' in inc
                 and 'SetAuxActionAt40FB40(6)' in inc,
                 'original native 31B stage4 sprite/stage8 aux missing')
        else:
            need('S16(0x62)==12' in inc and 'S16(0x62)==15' in inc
                 and 'U8(0x3CF)=1;' in inc
                 and 'SetAuxActionAt40FB40(0xD)' in inc,
                 'original native 31C stage12/15 once-only status missing')
        cpp=cpp.replace(marker,f'#include "FighterScriptedTail{a:X}F901.inc"',1)
    return cpp

def compile_one(src,tag):
    cpp=O/('Boss005214B0-F901-'+tag+'.cpp')
    obj=O/('Boss005214B0-F901-'+tag+'.obj')
    cpp.write_text(src)
    e=os.environ.copy();e.pop('DISPLAY',None);e.pop('WAYLAND_DISPLAY',None)
    e['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    e['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=e,capture_output=True,text=True,timeout=340)
    (O/('compiler-'+tag+'.log')).write_text(p.stdout+p.stderr)
    need(p.returncode==0,'native 31B/31C complete VC7.1 '+tag+' compile failed '+(p.stdout+p.stderr)[-800:])
    return obj

def parse(rd,d,obj):
    code,refs=rd.object_function(obj,SYM)
    I=[]
    for x in d.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    ret=I[-1].address+I[-1].size
    need(I[-1].mnemonic=='ret' and len(code)-ret==901,
         'original current whole callable fighter RET/data not exact shaped')
    tail=[i for i,x in enumerate(I) if x.address==ret-46]
    need(len(tail)==1 and tail[0]>=74+63+316,
         'true native 46B shared getter before 901B afterRET not found')
    return code,refs,I,ret,tail[0]

def audit_prior_native_current_phase(rd,pe,d,by,refs,N,I):
    """Physical original PE evidence, not stale historical GPR mismatch lists.

    In the complete 46754B normal VC7.1 context, all thirteen thousand
    x86 mnemonics align. Native source register allocation changes from
    an earlier 46754B parent when we append actual original tail states.
    Recompute each of 79 PREVIOUS source-backed original case intervals
    by its ORIGINAL PE physical handler entry. Independently resolve ALL
    actual 797 original COFF data/call targets from real PE operand bytes.
    Report (never mask) 12 original relative site shifts from 252/254
    and 424 absolute phase-shifted physical field offsets.
    """
    original_start=0x005214B0
    old=json.loads((R/'.analysis/f894-scripted2dd/verified-summary.json').read_text())
    early=[int(x['case'],16) for x in old['previous_46_original_source_cases_physically_reverified']]
    later=[0x1fd,0x1fe,0x1ff,0x200,0x201,0x252,0x253,0x254,
           0x255,0x256,0x257,0x258,0x259,0x2bc,0x2bd,0x2be,
           0x2bf,0x2c0,0x2c1,0x2c2,0x2c3,0x2db,0x2dc,0x2dd,
           0x2e4,0x2e5,0x2e6,0x2e7,0x2e8,0x2e9,0x2ea,0x2f0,0x2f8]
    actions=early+later
    need(len(early)==46 and len(later)==33
         and len(actions)==len(set(actions))==79,
         'expected 79 original source-backed native switch case identities changed')
    physical_starts=sorted(set(v for v in by.values()
                             if original_start<=v<=0x52cb25))
    original_inst_index={inst.address:j for j,inst in enumerate(N)}
    C=collections.Counter();details=[];shifted=[]
    for action in actions:
        start=by[action]
        successor=min(v for v in physical_starts if v>start)
        beg=original_inst_index[start]
        end=original_inst_index[successor]
        original=N[beg:end];src=I[beg:end]
        need(original and len(original)==len(src)
             and all(a.mnemonic==b.mnemonic for a,b in zip(original,src)),
             'current full original game action opcode grammar changed '+hex(action))
        lo=src[0].address;hi=src[-1].address+src[-1].size
        source_fields=[r for r in refs if lo<=r['offset']<hi]
        diffs=collections.Counter();count=0
        for field in source_fields:
            j=next(i for i,x in enumerate(src)
                   if x.address<=field['offset']<x.address+x.size)
            n=original[j]
            natural_original_location=n.address-original_start+n.size-4
            current_location=field['offset']
            original_case_off=n.address-start+n.size-4
            source_case_off=current_location-lo
            need(field['addend']==0
                 and field['local_symbol_offset'] is None
                 and field['type'] in ('DIR32','REL32'),
                 'original source case physical PE field not real zero-addend')
            match=re.search(r'At([0-9A-Fa-f]{6,8})',field['symbol'])
            expected=(int(match.group(1),16) if match else
                      0x6406AC if field['symbol']=='__ftol2' else None)
            need(expected is not None,
                 'source external original PE field lacks native target attribution '+hex(action))
            native_field=rd.pe_bytes_at(pe,n.address+n.size-4,4)
            val=int.from_bytes(native_field,'little',
                               signed=field['type']=='REL32')
            actual=(n.address+n.size+val if field['type']=='REL32' else val)
            need(actual==expected,
                 'real native original PE field target changed '+str((hex(action),j,hex(actual),hex(expected))))
            C['real_source_game_PE_targets_physically_verified']+=1
            count+=1
            if natural_original_location!=current_location:
                C['native_absolute_PE_fields_shifted']+=1
                diffs['global_shift']+=1
            if original_case_off!=source_case_off:
                C['native_case_relative_PE_fields_shifted']+=1
                diffs['local_shift']+=1
        b_original=original[-1].address+original[-1].size-start
        b_source=src[-1].address+src[-1].size-lo
        widths=[i for i,(x,y) in enumerate(zip(original,src)) if x.size!=y.size]
        if widths or b_original!=b_source or diffs['local_shift']:
            shifted.append({'case':hex(action),
               'original_B':b_original,'source_B':b_source,
               'native_x86':len(original),
               'original_source_width_wrong_ordinals_in_case':widths,
               'original_PE_case_relative_shifts':diffs['local_shift']})
        details.append({'case':hex(action),'native_x86':len(original),
                        'original_B':b_original,'source_B':b_source,
                        'real_typed_PE_target_fields_checked':count,
                        'physical_absolute_PE_shifted':diffs['global_shift'],
                        'physical_case_relative_PE_shifted':diffs['local_shift']})
    need(C['real_source_game_PE_targets_physically_verified']==797
         and C['native_absolute_PE_fields_shifted']==424
         and C['native_case_relative_PE_fields_shifted']==12,
         'previous 79 original native case source PE target/phase profile changed')
    need({x['case'] for x in shifted}=={'0x1fd','0x252','0x254'}
         and next(x for x in shifted if x['case']=='0x252')['original_B']==260
         and next(x for x in shifted if x['case']=='0x252')['source_B']==259
         and next(x for x in shifted if x['case']=='0x254')['original_B']==224
         and next(x for x in shifted if x['case']=='0x254')['source_B']==225,
         'original native byte width negatives must remain source phase mismatches')
    return {'previous_case_count':len(details),
            'native_original_game_PE_destinations_all_verified':C['real_source_game_PE_targets_physically_verified'],
            'original_native_absolute_COFF_positions_shifted':C['native_absolute_PE_fields_shifted'],
            'original_native_case_relative_PE_positions_shifted':C['native_case_relative_PE_fields_shifted'],
            'original_sized_or_width_defective_cases':shifted,
            'previous_original_native_case_profiles':details}

def main():
    C=load();M=C.modules();rd=M['rd'];d=Cs(CS_ARCH_X86,CS_MODE_32)
    cpp=source()
    obj=compile_one(cpp,'whole')
    code,refs,I,ret,k=parse(rd,d,obj)
    need((ret,len(I),len(refs),len(code)-ret)==(46754,13230,1491,901),
         'actual whole original fighter 1B geometry/COFF/wave changed')
    pe,d,by=C.native_environment(M,code,refs,I,ret)
    raw=rd.pe_bytes_at(pe,0x005214B0,46755)
    N=list(d.disasm(raw,0x005214B0))
    need(len(N)==len(I)==13230
         and all(n.mnemonic==s.mnemonic for n,s in zip(N,I)),
         'whole game 13230 actual native opcode mnemonic order not all recovered')
    widths=[j for j,(a,b) in enumerate(zip(N,I)) if a.size!=b.size]
    need(widths==list(WIDTH) and sum(x.size for x in N)-sum(x.size for x in I)==1,
         'whole original native five true opcode-width defects changed')
    originals={}
    for ordinal,action,original_b,source_b in (
       (2885,0x63,6,5),(2908,0x63,5,6),
       (8455,0x1fd,6,5),(8986,0x252,3,2),
       (9130,0x254,2,3)):
        a,b=N[ordinal],I[ordinal]
        need((a.size,b.size)==(original_b,source_b),
             'original native width/register phase per difficult case changed '+hex(action))
        originals.setdefault(hex(action),[]).append({
             'native_whole_x86_ordinal':ordinal,
             'native_va':hex(a.address),
             'native_instruction':a.mnemonic+' '+a.op_str,
             'source_instruction':b.mnemonic+' '+b.op_str,
             'native_opcode_B':a.size,'source_opcode_B':b.size})
    tail1=I[k-63-74:k-63];tail2=I[k-63:k]
    exact=[]
    for a,nxt,nb,nx,nf in CASES:
        part=tail1 if a==0x31b else tail2
        # The actual original physical successor 31C is 52CA4A.
        # 31C's next physical entry is shared default at 52CB25
        # (not numeric 31D).
        start=by[a]
        original_next=(by[0x31c] if a==0x31b else 0x52cb25)
        native_bytes=rd.pe_bytes_at(pe,start,original_next-start)
        source_first=part[0].address
        if a==0x31b:
            # Original 31B ends in a genuinely 5-byte near JMP;
            # C.physical_case requires original far JMPs to be 5B.
            row,offsets,targets=C.physical_case(
                M,pe,d,by,code,refs,part,a,nxt,nb,nx,nf,[])
            need(row['original_native_enclosing_parent_JMP_exit_ordinals']==[nx-1]
                 and part[-1].size==5,
                 'original 31B long enclosing near JMP not reproduced')
        else:
            # ORIGINAL 31C genuinely ends in a TWO-byte SHORT JMP
            # (original 52CB23: EB 2A to 52CB4F). Old f834
            # helper applies only to original 5-byte JMP cases.
            # Verify this case directly from actual pinned PE
            # without forcing long JMP/cropping any original byte.
            original=list(d.disasm(native_bytes,start))
            need(len(original)==len(part)==nx
                 and all(x.mnemonic==y.mnemonic and x.size==y.size
                         and x.address-start==y.address-source_first
                         for x,y in zip(original,part))
                 and original[-1].bytes==bytes.fromhex('eb2a')
                 and part[-1].bytes==bytes.fromhex('eb2a'),
                 'original 31C real 2-byte short branch and exact native geometry differ')
            fs=[r for r in refs if source_first<=r['offset']<part[-1].address+part[-1].size]
            mask=M['f820'].physical_fields(rd,native_bytes,start,fs,source_first,nf)
            offsets=[];targets=[]
            for r in fs:
                off=r['offset']-source_first
                idx=next(i for i,x in enumerate(part) if x.address<=r['offset']<x.address+x.size)
                inst=original[idx]
                need(off==inst.address-start+inst.size-4
                     and r['addend']==0 and r['local_symbol_offset'] is None,
                     '31C original physical PE call field shifted')
                target=start+off+4+int.from_bytes(native_bytes[off:off+4],'little',signed=True)
                offsets.append(off);targets.append(hex(target))
            need(len(mask)==nf*4 and
                 [i for i in range(nb) if i not in mask and native_bytes[i]!=code[source_first+i]]==[],
                 'original 31C complete native SHORT JMP or nonfield bytes differ')
            row={'case':hex(a),'native_whole_inner_B':nb,
                 'native_complete_x86':nx,'original_typed_PE_fields':nf,
                 'original_native_enclosing_parent_JMP_exit_ordinals':[nx-1],
                 'original_last_JMP_is_actual_TWO_BYTE_short':True,
                 'real_nonrelocation_wrong_offsets':[]}
        need(row['native_complete_x86']==nx
             and start in (0x52c952,0x52ca4a),
             'complete original 31B/31C native CODE/PE evidence changed')
        # A complete inner case is identical modulo true original PE
        # field bytes, but NOT an independent whole callable function.
        exact.append({'action':hex(a),
              'original_complete_inner_CODE_B':nb,'native_x86':nx,
              'physically_typed_PE_fields':nf,
              'all_nonfield_native_bytes_equal':True,
              'native_field_offsets':offsets,'actual_original_PE_destinations':targets,
              'is_independent_original_callable_function':False})
    # Physical 2F8 now naturally has the authentic full 5B last JMP
    # and zero original nonfield byte mismatches; F899 short deficit
    # disappears without forced register/no-op/padding.
    prior2f8=I[k-63-74-316:k-63-74]
    original2f8=C.physical_case(M,pe,d,by,code,refs,prior2f8,
               0x2f8,0x31b,1151,316,28,[])
    need(original2f8[0]['original_native_enclosing_parent_JMP_exit_ordinals']==[315]
         and prior2f8[-1].size==5,
         '2F8 original 1151B near-JMP not naturally restored')
    # The prior 79 source-backed original native game cases all
    # retain real original PE call/global targets, but their C++
    # register assignment changes as additional true game source
    # is compiled. Do NOT freeze old per-case GPR wrong offsets.
    checked=audit_prior_native_current_phase(rd,pe,d,by,refs,N,I)
    need(checked['previous_case_count']==79
         and checked['native_original_game_PE_destinations_all_verified']==797
         and checked['original_native_absolute_COFF_positions_shifted']==424
         and checked['original_native_case_relative_PE_positions_shifted']==12,
         'all 79 prior game case PE original targets and real width deficits must be audited')
    getter=C.native_getter_result(M,pe,code,refs,ret)
    need(getter['matching_original_nonfield_B']==34
         and getter['physical_original_PE_call_fields']==3,
         'original 46B shared getter must match all 34 native nonfield bytes')
    # The same physical PE/COFF references across the whole
    # selected parent do NOT all occupy the original physical
    # offsets because real source instruction width defects
    # shift the following machine-code phase. Never mask a
    # moved relocation at a source-only address as original.
    fieldlist=sorted((r for r in refs if r['offset']<ret),key=lambda r:r['offset'])
    pos=0;same=0;shifted=0;reloc_fail=[]
    for j,(original,generated) in enumerate(zip(N,I)):
        while pos<len(fieldlist) and fieldlist[pos]['offset']<generated.address:
            pos+=1
        idx=pos
        while idx<len(fieldlist) and fieldlist[idx]['offset']<generated.address+generated.size:
            r=fieldlist[idx]
            offset_original=original.address-0x005214B0+(r['offset']-generated.address)
            if offset_original==r['offset']:same+=1
            else:
                shifted+=1
                if len(reloc_fail)<8:
                    reloc_fail.append({
                      'original_x86_ordinal':j,
                      'source_COFF_field_offset':r['offset'],
                      'original_instruction_field_offset':offset_original})
            idx+=1
    need((len(fieldlist),same,shifted)==(1352,909,443),
         'native full-fighter physically shifted real source COFF fields have changed')
    # ORIGINAL function is NOT exact: five genuine native
    # instruction widths and 443 physically shifted
    # relocations defeat complete callable function acceptance,
    # regardless of all-mnemonic and 46754/46755 near sizes.
    negative_results={}
    incpaths={
      'wrong-31b-sprite':('31B','0x3E5','0x3E4',159),
      'wrong-31b-stage':('31B','S16(0x62)==4','S16(0x62)==5',93),
      'wrong-31c-limit':('31C','S16(0xF00)<8','S16(0xF00)<=8',171)}
    for tag,(which,good,bad,expected_offset) in incpaths.items():
        include=f'#include "FighterScriptedTail{which}F901.inc"'
        frag=(R/f'probes/FighterScriptedTail{which}F901.inc').read_text()
        need(frag.count(good)==1 and cpp.count(include)==1,
             'one original false source control must alter a real live operand '+tag)
        altered=cpp.replace(include,frag.replace(good,bad,1),1)
        wrongobj=compile_one(altered,tag)
        wc,wr,wI,wret,wk=parse(rd,d,wrongobj)
        need((wret,len(wI),len(wr),len(wc)-wret)==(46754,13230,1491,901),
             'false original tail source must keep misleading identical whole geometry '+tag)
        wrongcase=0x31c if which=='31C' else 0x31b
        source_part=(wI[wk-63:wk] if wrongcase==0x31c
                     else wI[wk-63-74:wk-63])
        lo=source_part[0].address;hi=source_part[-1].address+source_part[-1].size
        nativebytes=rd.pe_bytes_at(pe,by[wrongcase],219 if wrongcase==0x31c else 248)
        fs=[r for r in wr if lo<=r['offset']<hi]
        wm=M['f820'].physical_fields(rd,nativebytes,by[wrongcase],fs,lo,
                                       7 if wrongcase==0x31c else 8)
        wrongpositions=[i for i in range(len(nativebytes))
                        if i not in wm and nativebytes[i]!=wc[lo+i]]
        need(wrongpositions==[expected_offset],
             'wrong whole-source game C++ operand must be physically rejected '+tag+str(wrongpositions))
        negative_results[tag]=wrongpositions
    output={
        'original_sha_pinned_giant':'0x005214B0',
        'original_callable_whole_CODE_B':46755,
        'current_entire_normal_compiler_CODE_B':ret,
        'original_whole_native_x86_count':13230,
        'new_entire_normal_cpp_x86_count':len(I),
        'entire_13230_original_x86_mnemonics_match':True,
        'full_father_original_width_wrong_ordinals':list(WIDTH),
        'real_original_width_differences_by_game_action':originals,
        'native_total_original_SOURCE_COFF_fields_in_CODE':len(fieldlist),
        'native_original_physical_source_COFF_field_offsets_same':same,
        'native_original_physically_shifted_source_COFF_field_offsets':shifted,
        'first_source_relocation_physical_shift_evidence':reloc_fail,
        'new_31B_31C_complete_original_cases':exact,
        'previous_original_2F8_now_full_1151B_and_nonfield_equal':True,
        'new_two_native_original_tail_case_PE_fields_total':15,
        'native_tail_no_unmasked_original_byte_mismatches':True,
        'native_shared_getter_46B_34of34_original_nonfield_equal':getter,
        'three_false_full_tail_game_source_controls':negative_results,
        'previous_79_original_game_case_interiors_reverified':checked,
        'all_five_original_901B_afterRET_tables_verified':True,
        'original_separate_afterRET_DATA_B':901,
        'entire_original_callable_giant_exact':False,
        'newly_accepted_independent_whole_callable_CODE_B':0,
        'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(output,indent=2)+'\n')
    need(json.loads((O/'verified-summary.json').read_text())['entire_original_callable_giant_exact'] is False,
         'never claim whole function exact until every original byte and PE offset matches')
    print('F901 original native fighter whole 46755B/13230x86 vs actual complete generated VC7.1 parent 46754B/13230x86; ALL 13230 mnemonics align, but FIVE true opcode WIDTH positions original actions63 twice/1FD/252/254 and 443 physically shifted original COFF fields remain. Native 2F8 1151B/316x86/28 PE, 31B 248B/74x86/8 PE, 31C 219B/63x86/7 PE now match ALL original nonfield bytes incl giant far-JMP operands. 79 preceding cases, five 901B DATA, getter34/34 verified. Whole father NONEXACT, zero new adopted CODE.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F901 original entire fighter native 31B/31C PE FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
