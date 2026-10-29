#!/usr/bin/env python3
"""F631: all eleven original 73/75-x86 native action0x96 landing timers.

Cold compile only the eleven affected whole fighter C++ parent TUs,
validate every native complete case0x96->0x97 x86 GPR/x87/CFG role,
real 9 physical typed PE/COFF fields and original 22 wide receiver
MOVs. Recheck F629 prior strict 0x91 in eight actors and the real
105-instruction F630 projectile-spawn source *negative* in two more,
plus F628 3 landings, F627/F626/F624 mode63, earlier 30 original
case bodies and actual entire separately owned afterRET jump DATA.
Never count incomplete original giant functions as exact CODE.
"""
from __future__ import annotations
import argparse
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/FighterLandingTimer96F631.inc'
OUT=ROOT/'.analysis/f631-fighter-landing-timer-source'
SPECIAL=(0x0045DD70,0x0058AF60)
NEG_ARC=0x004F7130
FIELDS={
  2:(0x0065747C,'fadd','g_AnimationDeltaAt0065747C'),
  7:(0x006583B4,'fcomp','g_AnimationMaximumAt006583B4'),
  31:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
  37:(0x00658058,'fadd','g_JumpGroundCorrectionAt00658058'),
  42:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
  49:(0x00454EE0,'call','ContactAt454EE0'),
  59:(0x006583E8,'fmul','g_JumpReflectionAt006583E8'),
  63:(0x0040FA30,'call','GetNativeActionAt40FA30'),
  71:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
}


def need(test,message):
    if not test:raise ValueError(message)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'missing original native source helper '+str(path))
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def original_case(reader,pe,decoder,boss,by):
    addr=boss['address'];start=by[0x96];end=by[0x97]
    next_handler=min((x for x in set(by.values()) if x>start),default=None)
    n=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    extra=len(n)==75
    count=75 if addr in (0x00543210,0x0058AF60) else 73
    size=342 if addr==0x00564BE0 else (288 if extra else 276)
    counter=0xEFC if addr==0x005AEEC0 else 0xF00
    need(addr<=start<end<addr+boss['size'] and end==next_handler
         and len(n)==count and sum(x.size for x in n)==end-start==size
         and n[-1].mnemonic=='jmp',
         f'{addr:#x}: actual original entire native 0x96->0x97 CODE/x86 geometry changed')
    before=extra and '+ 0xf0a]' in n[22].op_str
    need(n[0].mnemonic=='mov' and n[1].mnemonic=='fld'
         and '+ 0x368]' in n[1].op_str
         and n[2].mnemonic=='fadd' and n[2].op_str=='dword ptr [0x65747c]'
         and n[7].mnemonic=='fcomp' and n[7].op_str=='dword ptr [0x6583b4]'
         and n[9].mnemonic=='test' and n[9].op_str=='ah, 0x41'
         and n[10].mnemonic=='jne'
         and n[12].mnemonic=='mov' and n[12].op_str.endswith(', 0x447a0000')
         and n[22].mnemonic=='mov' and f'+ 0x{(0xF0A if before else counter):x}]' in n[22].op_str
         and n[24+(2 if before else 0)].mnemonic=='mov'
         and n[24+(2 if before else 0)].op_str.endswith(', 0xc1100000')
         and n[26+(2 if before else 0)].op_str.endswith(', 0')
         and n[28+(2 if before else 0)].op_str.endswith(', 0'),
         f'{addr:#x}: real native action96 animation increment/extra short flag/init changed')
    if extra:
        flag_at=22 if before else 30
        need(n[flag_at].mnemonic=='mov' and '+ 0xf0a]' in n[flag_at].op_str
             and n[flag_at].op_str.endswith(', 0')
             and (addr==0x0058AF60)==bool(before),
             f'{addr:#x}: native extra short flag +0xF0A must retain original BEFORE/AFTER order')
    shift=2 if extra else 0
    need(n[31+shift].mnemonic=='fcomp'
         and n[33+shift].op_str=='ah, 5'
         and n[34+shift].mnemonic=='jp'
         and n[37+shift].mnemonic=='fadd'
         and n[42+shift].mnemonic=='fcomp'
         and n[44+shift].op_str=='ah, 0x41'
         and n[45+shift].mnemonic=='jne'
         and n[49+shift].mnemonic=='call' and n[49+shift].op_str=='0x454ee0'
         and n[54+shift].mnemonic=='movsx' and '+ 0x3be]' in n[54+shift].op_str
         and n[59+shift].mnemonic=='fmul' and n[59+shift].op_str=='qword ptr [0x6583e8]'
         and n[61+shift].mnemonic=='fstp' and '+ 0x490]' in n[61+shift].op_str
         and n[69+shift].mnemonic=='push' and n[69+shift].op_str=='0',
         f'{addr:#x}: original native 0x96 strict x87 contact/reflection and action transition differ')
    for original_i,(dest,mn,_) in FIELDS.items():
        i=original_i+(2 if extra and original_i>=31 else 0)
        orig=n[i]
        want=f'0x{dest:x}' if mn=='call' else (
             f'qword ptr [0x{dest:x}]' if mn=='fmul' else f'dword ptr [0x{dest:x}]')
        need(orig.mnemonic==mn and orig.op_str==want,
             f'{addr:#x}: actual native original typed game/float target {dest:#x} at ordinal{i} changed')
    return n,{'original_native_complete_case_start':f'0x{start:08X}',
              'original_next_handler0x97':f'0x{end:08X}',
              'original_whole_case_CODE_bytes':size,
              'original_complete_x86_instructions':count,
              'original_counter_short_owner':counter,
              'original_extra_short_0xF0A_present':extra,
              'original_extra_short_0xF0A_before_counter':before,
              'original_real_typed_PE_COFF_fields':9,
              'entire_enclosing_original_boss_exact':False}


def source_with_case(addr,boss,report,mapped,reader,pe,decoder,helpers,info):
    h=helpers
    by={x['action']:int(x['handler'],16) for x in mapped}
    if addr not in SPECIAL:
        orig,earlier=h['f629'].real_original(reader,pe,decoder,boss,by)
        before={a:h['f628'].native_case(reader,pe,decoder,boss,by,a)
                for a in h['f628'].ACTIONS}
        source=h['f629'].source_with_action(addr,boss,report,mapped,reader,pe,decoder,h,before,earlier)
    else:
        earlier={a:h['f628'].native_case(reader,pe,decoder,boss,by,a)
                 for a in h['f628'].ACTIONS}
        source=h['f628'].source_with_landing(addr,boss,report,mapped,reader,pe,decoder,h,earlier)
        orig91=list(decoder.disasm(reader.pe_bytes_at(pe,by[0x91],by[0x96]-by[0x91]),by[0x91]))
        need(len(orig91)==105,f'{addr:#x}: original special sprite spawn not 105 x86')
        params={'F630_STAGE':orig91[45].op_str.rsplit(', ',1)[-1],
                'F630_EARLY':orig91[53].op_str,
                'F630_LATE':orig91[101].op_str,
                'F630_COUNTER':'0xF00',
                'F630_PROJECTILE':orig91[40].op_str,
                'F630_SIDE':orig91[30].op_str}
        marker='        case 0x91: g_FighterProbeMarker = 146; break;'
        need(source.count(marker)==1,
             f'{addr:#x}: actual special original sprite 0x91 source insertion lost')
        inserted='\n'.join('#define '+k+' '+v for k,v in params.items())
        inserted+='\n#include "FighterArcSpawn91F630.inc"\n'
        inserted+='\n'.join('#undef '+k for k in params)
        source=source.replace(marker,inserted)
    marker='        case 0x96: g_FighterProbeMarker = 151; break;'
    need(source.count(marker)==1,f'{addr:#x}: next real original timed landing 0x96 marker missing')
    names={'F631_COUNTER':f'0x{info["original_counter_short_owner"]:X}',
           'F631_EXTRA_FLAG':str(int(info['original_extra_short_0xF0A_present'])),
           'F631_EXTRA_BEFORE':str(int(info['original_extra_short_0xF0A_before_counter']))}
    inserted='\n'.join('#define '+k+' '+v for k,v in names.items())
    inserted+='\n#include "FighterLandingTimer96F631.inc"\n'
    inserted+='\n'.join('#undef '+k for k in names)
    decl='extern float g_ThresholdAt0065782C;'
    need(source.count(decl)==1,f'{addr:#x}: original global trajectory float declaration missing')
    source=source.replace(decl,decl+'\nextern float g_AnimationDeltaAt0065747C;'
              '\nextern float g_AnimationMaximumAt006583B4;')
    return source.replace(marker,inserted)


def verify_special_previous_91(reader,pe,decoder,boss,mapped,code,refs,inst,case_start,h,extra):
    addr=boss['address'];by={x['action']:int(x['handler'],16) for x in mapped}
    native=list(decoder.disasm(reader.pe_bytes_at(pe,by[0x91],by[0x96]-by[0x91]),by[0x91]))
    need(len(native)==105 and sum(x.size for x in native)==373,
         f'{addr:#x}: native special original projectile 0x91 not full 105/373')
    start_index=next(i for i,x in enumerate(inst) if x.address==case_start)
    need(start_index>=105,f'{addr:#x}: source prior sprite action0x91 incomplete')
    gen=inst[start_index-105:start_index]
    need(len(gen)==105 and gen[-1].address+gen[-1].size==case_start
         and case_start-gen[0].address==373
         and all(x.size==y.size for x,y in zip(native,gen)),
         f'{addr:#x}: original native sprite 0x91 geometry not 105 x86/373B')
    kind=int(native[40].op_str,0)
    side=int(native[30].op_str,0)
    need((kind,side)==((0x3B7,1) if addr==0x0045DD70 else (0x3E7,1))
         and native[25].mnemonic=='movsx' and '+ 0xf0c]' in native[25].op_str
         and native[29].mnemonic=='mov' and '+ 0xf0c]' in native[29].op_str
         and native[42].mnemonic=='call' and native[42].op_str=='0x453a70',
         f'{addr:#x}: real stage-one original 0xF0C one-shot spawn sprite ABI differs')
    fields={42:(0x00453A70,'call','SpawnDirectedAt453A70')}
    fields.update({i+27:(dest,mn,sym) for i,(dest,mn,sym) in h['f629'].FIELDS.items()})
    need(len(fields)==13,'original 13 typed sprite/CRT PE fields missing')
    lo,hi=gen[0].address,gen[-1].address+gen[-1].size
    physical=[x for x in refs if lo<=x['offset']<hi]
    need(len(physical)==13,f'{addr:#x}: source sprite 0x91 physical 13 real COFF refs missing')
    for i,(target,mn,sym) in fields.items():
        n,g=native[i],gen[i]
        want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
        need(n.mnemonic==g.mnemonic==mn and n.op_str==want,
             f'{addr:#x}: actual original sprite source typed x86 ordinal{i} target differs')
        found=[x for x in physical if g.address<=x['offset']<g.address+g.size]
        need(len(found)==1 and found[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and found[0]['addend']==0 and found[0]['local_symbol_offset'] is None
             and sym in found[0]['symbol'],
             f'{addr:#x}: original sprite x86{i} PE target {target:#x} COFF differs: {found}')
    na,ga=h['f598'].normalized(native),h['f598'].normalized(gen)
    errors=[(i,x,y) for i,(x,y) in enumerate(zip(na,ga)) if x!=y]
    need(len(errors)==55,
         f'{addr:#x}: genuine original special sprite register phase changed: {len(errors)} !=55')
    return {'previous_special_original_0x91_x86':105,
            'previous_special_original_0x91_CODE_bytes':373,
            'previous_special_sprite_kind':kind,
            'previous_special_sprite_side':side,
            'previous_special_native_COFF_field_targets':13,
            'previous_special_native_REGISTER_mismatches':len(errors),
            'previous_special_case_NOT_source_strict':True}


def verify_new_obj(reader,pe,decoder,boss,report,mapped,code,refs,real,info,h,extra_sibling_x86=0):
    addr=boss['address'];ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret',f'{addr:#x}: original whole fighter source final RET missing')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         f'{addr:#x}: separately owned original full afterRET switch DATA changed')
    by={x['action']:int(x['handler'],16) for x in mapped}
    count=info['original_complete_x86_instructions']
    need(extra_sibling_x86 in (0,3*73,3*75,5*73,5*75),
         f'{addr:#x}: only actual complete three 73/75-x86 97/98/9A siblings may follow 0x96')
    wanted=(0x98 if extra_sibling_x86==0 else
            0x9C if extra_sibling_x86 in (3*73,3*75) else 0x9F)
    marker=[]
    for field in refs:
        if 'g_FighterProbeMarker' not in field['symbol']:continue
        x=next((i for i in ins if i.address<=field['offset']<i.address+i.size),None)
        if x is not None and x.mnemonic=='mov' and x.op_str.endswith(f', 0x{wanted:x}'):
            marker.append(x)
    need(len(marker)==1,f'{addr:#x}: original next source case0x97 marker not unique')
    idx=ins.index(marker[0]);need(idx>=count+extra_sibling_x86,
                                 'original 96 source truncated by following sibling cases')
    source=ins[idx-count-extra_sibling_x86:idx-extra_sibling_x86]
    actual_next=(ins[idx-extra_sibling_x86].address if extra_sibling_x86
                 else marker[0].address)
    need(len(source)==len(real)==count
         and source[-1].address+source[-1].size==actual_next
         and source[-1].mnemonic=='jmp',
         f'{addr:#x}: complete native source 0x96→0x97 physical CFG boundary shifted')
    widths=[x.size-y.size for x,y in zip(real,source)]
    if addr==0x00564BE0:
        need(widths.count(3)==22 and widths.count(0)==51
             and all(real[i].op_str.endswith('dword ptr [ebp - 0x88]')
                     for i,diff in enumerate(widths) if diff==3),
             f'{addr:#x}: native 0x96 actual 22 wide EBP-0x88 receiver MOV widths differ')
    else:need(all(x==0 for x in widths),
              f'{addr:#x}: native compact action0x96 source instruction widths differ')
    lo,hi=source[0].address,source[-1].address+source[-1].size
    need(hi-lo==(288 if count==75 else 276),
         f'{addr:#x}: complete 0x96 natural source x86 size incorrect')
    physical=[x for x in refs if lo<=x['offset']<hi]
    need(len(physical)==9,f'{addr:#x}: nine actual native PE/COFF typed fields missing')
    for ord,(dest,mn,symbol) in FIELDS.items():
        j=ord+(2 if count==75 and ord>=31 else 0)
        original,generated=real[j],source[j]
        want=f'0x{dest:x}' if mn=='call' else (
             f'qword ptr [0x{dest:x}]' if mn=='fmul' else f'dword ptr [0x{dest:x}]')
        need(original.mnemonic==generated.mnemonic==mn and original.op_str==want,
             f'{addr:#x}: original x86 {j} typed float/game call target {dest:#x} changed')
        field=[x for x in physical if generated.address<=x['offset']<generated.address+generated.size]
        need(len(field)==1 and field[0]['type']==('REL32' if mn=='call' else 'DIR32')
             and field[0]['addend']==0 and field[0]['local_symbol_offset'] is None
             and symbol in field[0]['symbol'],
             f'{addr:#x}: real original target {dest:#x} at 0x96 ordinal{j} vs source COFF differs: {field}')
    nshape,sshape=h['f598'].normalized(real),h['f598'].normalized(source)
    differences=[(i,n,s) for i,(n,s) in enumerate(zip(nshape,sshape)) if n!=s]
    need(not differences,
         f'{addr:#x}: original case0x96 complete x86 GPR/x87/CFG source role mismatch: {differences[:7]}')
    # Full ancestor case proof, always on the SAME extended whole source
    # object. The original extra 0x96 x86 count is explicitly passed
    # through F629's backward-compatible F628 check.
    before=[]
    if addr not in SPECIAL:
        earlier,meta=h['f629'].real_original(reader,pe,decoder,boss,by)
        h['f629'].verify_case(reader,pe,decoder,boss,report,mapped,code,refs,
            earlier,meta,h,addr==NEG_ARC,extra_after_0x91=count+extra_sibling_x86)
        prior_status={'previous_0x91_strict':addr!=NEG_ARC,
                      'original_prior_0x91_GPR_role_mismatches':35 if addr==NEG_ARC else 0}
    else:
        prior={a:h['f628'].native_case(reader,pe,decoder,boss,by,a)
               for a in h['f628'].ACTIONS}
        h['f628'].verify_obj(reader,pe,decoder,boss,report,mapped,code,refs,
            prior,h,True,extra_followup_x86=105+count+extra_sibling_x86)
        prior_status=verify_special_previous_91(reader,pe,decoder,boss,mapped,
                code,refs,ins,lo,h,count)
    return {'original_whole_boss':f'0x{addr:08X}',
            'original_whole_boss_CODE_still_NONEXACT':boss['size'],
            'original_separate_afterRET_DATA_bytes':boss['postret_size'],
            'prior_F628_30_cases_and_full_jump_tables_preserved_on_new_OBJ':True,
            'previous_original_action0x91_context':prior_status,
            'original_complete_action0x96':info,
            'native_original_case0x96_GPR_x87_CFG_roles_strict':True,
            'actual_native_typed_PE_COFF_fields':len(physical),
            'new_strict_original_inner_CODE_bytes_uncredited':info['original_whole_case_CODE_bytes'],
            'new_authored_whole_exact_functions':0}


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--boss',help='one of 11 actual native 0x96 fighter source TUs; omit for all affected giants')
    opt=p.parse_args()
    modules={
      'f602':'scripts/verify-fighter-trajectory46-f602.py',
      'f603':'scripts/verify-fighter-trajectory-spawn-f603.py',
      'f600':'scripts/verify-fighter-additional-contact-f600.py',
      'f598':'scripts/verify-fighter-singleton-contact-f598.py',
      'f567':'scripts/verify-fighter-all-multiswitch-opening-cases.py',
      'f605':'scripts/verify-fighter-trajectory-followups-f605.py',
      'f606':'scripts/verify-fighter-trajectory-followup-spawns-f606.py',
      'f607':'scripts/verify-fighter-trajectory-landing-f607.py',
      'f608':'scripts/verify-fighter-trajectory-landing-spawn-f608.py',
      'f610':'scripts/verify-fighter-trajectory-bounce-f610.py',
      'f611':'scripts/verify-fighter-trajectory-bounce-spawn-f611.py',
      'f613':'scripts/verify-fighter-trajectory-recovery-f613.py',
      'f614':'scripts/verify-fighter-trajectory-burst-f614.py',
      'f622':'scripts/verify-fighter-counter-dispatch-f622.py',
      'f624':'scripts/verify-fighter-mode63-f624.py',
      'f626':'scripts/verify-fighter-mode63-basic-f626.py',
      'f627_priority':'scripts/verify-fighter-mode63-priority-f627.py',
      'f628':'scripts/verify-fighter-jump-landings-f628.py',
      'f629':'scripts/verify-fighter-arc91-f629.py',
      'core':'scripts/verify-fighter-action-six-natural-source.py',
      'zero':'scripts/verify-fighter-actionzero-natural-source.py',
      'switch':'scripts/verify-fighter-natural-switch-probes.py'}
    h={name:load('f631_'+name,ROOT/path) for name,path in modules.items()}
    rd=load('f631_reader',ROOT/'scripts/compare-coff-function.py')
    actions=load('f631_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=rd.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    cohort=(*h['f628'].POSITIVE,NEG_ARC,*SPECIAL)
    need(len(cohort)==len(set(cohort))==11,'original entire second-switch giant cohort changed')
    chosen=[int(opt.boss,0)] if opt.boss else list(cohort)
    need(all(a in cohort for a in chosen),'selected original actor not in actual 0x96 native complete action cohort')
    text=SOURCE.read_text()
    sprite=(ROOT/'probes/FighterArcSpawn91F630.inc').read_text()
    need(text.count('case 0x96:')==1 and 'F631_EXTRA_BEFORE' in text
         and 'I16(F631_COUNTER)=0;' in text
         and 'F32(0x490)=POS*g_JumpReflectionAt006583E8;' in text
         and sprite.count('SpawnDirectedAt453A70(')==1
         and sprite.count('I16(0xF0C)==0')==1,
         'original normal 0x96 or genuine special 0x91 native C++ source unexpectedly changed')
    bs={b['address']:b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']}
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    results=[]
    for addr in chosen:
        boss=bs[addr];report,mapped=actions.report_boss(rd,pe,decoder,boss)
        by={x['action']:int(x['handler'],16) for x in mapped}
        native,info=original_case(rd,pe,decoder,boss,by)
        cpp=OUT/f'Boss{addr:08X}-35-real-game-actions.cpp'
        obj=OUT/f'Boss{addr:08X}-35-real-game-actions.obj'
        cpp.write_text(source_with_case(addr,boss,report,mapped,rd,pe,decoder,h,info))
        compile=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=190)
        (OUT/f'Boss{addr:08X}-compiler.log').write_text(compile.stdout+compile.stderr)
        need(compile.returncode==0,f'{addr:#x}: original pinned VC7.1 whole parent C++ compile failed: {compile.stderr[-550:]}')
        code,refs=rd.object_function(obj,f'?Advance@FighterSwitchF598_Boss{addr:08X}@@QAEXXZ')
        receipt=verify_new_obj(rd,pe,decoder,boss,report,mapped,code,refs,native,info,h)
        results.append(receipt)
        prev=receipt['previous_original_action0x91_context']
        print(f'F631 {addr:#010x}: original complete 0x96 '
              f'{info["original_complete_x86_instructions"]}/'
              f'{info["original_complete_x86_instructions"]} x86 GPR/x87/CFG roles, '
              f'{info["original_whole_case_CODE_bytes"]} authentic inner CODE B, '
              f'9/9 PE/COFF targets; previous 0x91 context {prev}, '
              'preceding 8C/8F/90, real 0x63, prior 30 game cases and entire '
              'afterRET table rechecked. Whole giant NONEXACT.',flush=True)
    summary=OUT/('summary.json' if not opt.boss else f'summary-{chosen[0]:08X}.json')
    summary.write_text(json.dumps(results,indent=2)+'\n')
    print(f'F631: {len(results)} fresh giant source TU builds, '
          f'{sum(x["original_complete_action0x96"]["original_complete_x86_instructions"] for x in results)} '
          'authentic native x86 roles / '
          f'{sum(x["new_strict_original_inner_CODE_bytes_uncredited"] for x in results)} '
          f'uncredited original interior native CODE bytes / {9*len(results)} physical typed fields; '
          'ZERO new whole exact authored functions, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F631 original Japanese fighter landing timer source proof failed:',e,file=sys.stderr)
        raise SystemExit(1)
