#!/usr/bin/env python3
"""F760: cold-compile one real 00543210 fighter parent with original CC/CD/CE.

Verify every complete 435/435/394-B original switch case, all native x86,
original PE-targeted COFF relocations, native source byte identity outside
explicit shared whole-parent JMPs, eight downstream game cases and afterRET
DATA. Internal cases are NOT independently callable whole-game CODE.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f760-fighter-cc-ce'
BASE=0x00543210
ORIG={0xCC:(0x00547A8B,0x00547C3E,435,128,11),
      0xCD:(0x00547C3E,0x00547DF1,435,128,11),
      0xCE:(0x00547DF1,0x00547F7B,394,115,9)}
DOWNSTREAM={0x18A:(0x005490FD,0x005491FD,256,71,6),
            0x18B:(0x005491FD,0x00549364,359,99,7),
            0x190:(0x00549364,0x00549478,276,75,7),
            0x191:(0x00549478,0x0054958C,276,75,7),
            0x192:(0x0054958C,0x0054967C,240,68,7),
            0x194:(0x0054967C,0x005497CB,335,92,7),
            0x195:(0x005497CB,0x0054991A,335,92,7),
            0x2D0:(0x0054E111,0x0054E2B1,416,120,15)}
SYM='?Advance@FighterSwitchF598_Boss00543210@@QAEXXZ'


def need(ok,msg):
    if not ok: raise ValueError(msg)


def load(tag,relative):
    sp=importlib.util.spec_from_file_location(tag,ROOT/relative)
    need(sp and sp.loader,'missing original PE/source helper '+relative)
    obj=importlib.util.module_from_spec(sp)
    sys.modules[tag]=obj
    sp.loader.exec_module(obj)
    return obj


def compile_parent(f759,reader,pe,decoder,boss,report,mapped):
    source=f759.full_source(reader,pe,decoder,boss,report,mapped)
    for action in ORIG:
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(source.count(marker)==1,f'actual original {action:#x} incomplete marker absent')
        source=source.replace(marker,
            '#include "FighterComplexStageCC_CE_F760.inc"' if action==0xCC else '')
    need(source.count('#include "FighterComplexStageCC_CE_F760.inc"')==1
         and source.count('#include "FighterFourDirectionalC8F759.inc"')==1,
         'must compose complete previous original four actions and new three actions')
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-F760-cold-whole.cpp'
    obj=OUT/'Boss00543210-F760-cold-whole.obj'
    cpp.write_text(source)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
            cwd=ROOT,env=env,capture_output=True,text=True,timeout=220)
    (OUT/'F760-cold-compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'real VC7.1 entire fighter compilation failed '+
         (cp.stdout+cp.stderr)[-900:])
    return obj


def code_instructions(d,code):
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret','complete native-shaped parent RET missing')
    return ins


def physical_case(reader,pe,d,code,refs,ins,mapper,case,original,*,check_targets):
    lo,hi,nb,nx,nfields=original
    need(hi-lo==nb and lo in mapper and hi in mapper,
         f'{case:#x}: entire original PE dispatch boundary not mapped')
    start,end=mapper[lo],mapper[hi]
    native=reader.pe_bytes_at(pe,lo,nb)
    a=list(d.disasm(native,lo))
    b=[i for i in ins if start<=i.address<end]
    need(len(a)==len(b)==nx and end-start==nb and
         all(x.size==y.size and x.mnemonic==y.mnemonic for x,y in zip(a,b)),
         f'{case:#x}: whole genuine native x86/size geometry not matched')
    owned=[r for r in refs if start<=r['offset']<end]
    need(len(owned)==nfields and all(r['addend']==0 for r in owned),
         f'{case:#x}: true native physical COFF field count/addend differs')
    fieldmask=set()
    for r in owned:
        off=r['offset']-start
        j=next((j for j,bi in enumerate(b) if bi.address<=r['offset']<bi.address+bi.size),None)
        need(j is not None and r['type'] in ('DIR32','REL32') and
             r['local_symbol_offset'] is None and
             all(0<=k<nb and k not in fieldmask for k in range(off,off+4)),
             f'{case:#x}: physical COFF owner/field overlap malformed')
        fieldmask.update(range(off,off+4))
        if check_targets:
            match=re.search(r'At([0-9a-fA-F]{6,8})(?=[^0-9a-fA-F]|$)',r['symbol'])
            need(match is not None,f'{case:#x}: unknown native original target {r["symbol"]}')
            field=native[off:off+4]
            word=int.from_bytes(field,'little')
            dest=word if r['type']=='DIR32' else (lo+off+4+(word if word<0x80000000 else word-0x100000000))
            need(dest==int(match.group(1),16),
                 f'{case:#x}: source COFF {r["symbol"]} not physical original PE destination {dest:#x}')
            need(a[j].mnemonic==b[j].mnemonic and
                 r['type']==('REL32' if a[j].mnemonic=='call' else 'DIR32'),
                 f'{case:#x}: genuine COFF relocation type or x86 instruction moved')
    tailmask=set();tailtarget=None;exits=0
    source_starts={x.address for x in ins}
    for j,(x,y) in enumerate(zip(a,b)):
        if x.mnemonic=='jmp' and x.op_str=='0x5515c2':
            need(x.size==y.size==5 and y.mnemonic=='jmp' and
                 int(y.op_str,16) in source_starts,
                 f'{case:#x}: real parent-tail x86 JMP not a genuine generated whole-parent target')
            tailtarget=y.op_str
            tailmask.update(range(y.address-start+1,y.address-start+5))
            exits+=1
    bad=[k for k in range(nb) if k not in fieldmask and k not in tailmask
         and native[k]!=code[start+k]]
    need(not bad,f'{case:#x}: genuine native other CODE bytes still differ {bad[:16]}')
    return {'case':f'0x{case:X}','native_original_CODE_bytes':nb,
            'original_and_source_x86':nx,'genuine_original_COFF_fields':len(owned),
            'nonfield_nontail_original_bytes_exact':nb-len(fieldmask)-len(tailmask),
            'external_parent_tail_JMP_count_NOT_EXACT':exits,
            'generated_full_parent_tail':tailtarget,
            'independently_exact_callable_game_CODE':False}


def main():
    rd=load('f760_reader','scripts/compare-coff-function.py')
    act=load('f760_actions','scripts/report-fighter-action-handlers.py')
    f734=load('f760_mapper','scripts/verify-fighter-eight-round-f734.py')
    f759=load('f760_F759','scripts/verify-fighter-four-directional-c8-f759.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if x['address']==BASE)
    need(boss['size']==58294 and boss['postret_size']==943,
         'original Japanese whole fighter target extent differs')
    report,mapped=act.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    for case,(lo,hi,nb,_,_) in ORIG.items():
        need(by[case]==lo and by[case+1]==hi and hi-lo==nb,
             f'original {case:#x} current whole boss case boundary changed')
    obj=compile_parent(f759,rd,pe,d,boss,report,mapped)
    code,refs=rd.object_function(obj,SYM)
    ins=code_instructions(d,code)
    ret=ins[-1].address+ins[-1].size
    need(ret==58173 and len(code)==ret+943 and boss['size']-ret==121,
         'new whole parent native original 58,294B still differs by 121 bytes, not exact')
    mapper=f734.source_map_from_original_afterRET(rd,pe,boss,code,ins,refs)
    older,oldtail=f759.check_native_cases(rd,pe,d,code,refs,ins,mapper,by)
    fresh=[physical_case(rd,pe,d,code,refs,ins,mapper,case,layout,check_targets=True)
           for case,layout in ORIG.items()]
    need(sum(q['native_original_CODE_bytes'] for q in fresh)==1264 and
         sum(q['original_and_source_x86'] for q in fresh)==371 and
         sum(q['genuine_original_COFF_fields'] for q in fresh)==31 and
         sum(q['nonfield_nontail_original_bytes_exact'] for q in fresh)==1116 and
         all(q['external_parent_tail_JMP_count_NOT_EXACT']==2 for q in fresh),
         'new original three whole case physical source proof incomplete')
    print('F760 three full original CC/CD/CE: 1,264 native CODE B /371 x86 /31 PE/COFF fields; '
          '1,116 genuine nonfield non-tail bytes exact; six legitimate shared-tail JMPs still NONEXACT',flush=True)
    recovered=[physical_case(rd,pe,d,code,refs,ins,mapper,case,layout,check_targets=False)
               for case,layout in DOWNSTREAM.items()]
    need(len(recovered)==8 and all(x['nonfield_nontail_original_bytes_exact']>0 for x in recovered),
         'downstream whole native 18A..2D0 actual CODE/COFF still not source-backed')
    print('F760 eight downstream complete native cases 18A/18B/190–195/2D0 have '
          'zero other PE nonfield differences; original 190 whole 276B x86/7 fields now natural',flush=True)
    later=physical_case(rd,pe,d,code,refs,ins,mapper,0x302,
                        (0x55101e,0x5513c5,935,261,28),check_targets=False) if False else None
    afterret=f759.check_afterret(rd,pe,d,boss,code,refs,ins)
    data={'original_full_game_function':'0x00543210',
          'native_entire_GAME_CODE_bytes':58294,
          'current_whole_Cpp_CODE_bytes':ret,
          'still_missing_original_GAME_CODE_bytes':121,
          'new_original_CCpp_case_evidence':fresh,
          'reverified_F759_original_cases':older,
          'eight_whole_downstream_original_source_cases':recovered,
          'authentic_original_afterRET_data':afterret,
          'entire_original_boss_byte_exact':False,
          'new_canonical_whole_game_CODE_credit':0,
          'full_970_unit_cold_replay_run':False}
    (OUT/'f760-complete-native-evidence.json').write_text(json.dumps(data,indent=2)+'\n')
    print('F760 whole 58KB giant source length',ret,'vs original 58294; 121B still missing; zero official game CODE credit',flush=True)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F760 ORIGINAL PE WHOLE FIGHTER SOURCE VERIFICATION FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
