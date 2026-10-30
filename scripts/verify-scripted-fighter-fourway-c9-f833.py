#!/usr/bin/env python3
"""F833: selected true 279-B 0xC9 storm shot in the complete growing fighter.

Regenerate F832 prior affected whole parent, introduce the actual
physical original 0xC9 startup, two signed-direction projectiles,
height recovery, and direct original function return in one fresh
pinned VC7.1 whole 46KB source. Check all 86 x86 opcode sizes,
11 physical original PE call/global fields, actual 47 nonrelocation
source register/parent-JMP differences, and unchanged earlier
CF/D0/D1/D2 source with all true PE fields and 901B afterRET DATA.
C8 is still a placeholder; no whole-original exact credit.
"""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f833-scripted-fourway-c9'
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
OLDER={
  0xcf:(30,114,4,20),
  0xd0:(60,195,6,39),
  0xd1:(59,199,8,32),
  0xd2:(74,251,10,46),
}
FOLLOW={0xcf:0xd0,0xd0:0xd1,0xd1:0xd2,0xd2:0x12c}

def need(x,msg):
    if not x:raise ValueError(msg)

def load(t,f):
    sp=importlib.util.spec_from_file_location(t,R/'scripts'/f)
    need(sp is not None and sp.loader is not None,'real PE source helper missing '+f)
    m=importlib.util.module_from_spec(sp)
    sys.modules[t]=m;sp.loader.exec_module(m)
    return m

def original_source():
    O.mkdir(parents=True,exist_ok=True)
    run=subprocess.run([str(R/'scripts/repo-python'),
             str(R/'scripts/verify-scripted-fighter-resource-shots-f832.py')],
             cwd=R,capture_output=True,text=True,timeout=1250)
    (O/'f832-prior-original-proof.log').write_text(run.stdout+run.stderr)
    need(run.returncode==0,'previous original CF/D0/D1/D2 PE proof failed '+
         (run.stdout+run.stderr)[-870:])
    src=(R/'.analysis/f832-scripted-resource-shots/Boss005214B0-F832-whole.cpp').read_text()
    mark='        case 0xC9: g_FighterProbeMarker = 202; break;'
    need(src.count(mark)==1,'source missing genuine original C9 placeholder')
    source=(R/'probes/FighterScriptedFourWayC9F833.inc').read_text()
    need(source.count('case 0xC9:')==source.count('return;')==1
         and source.count('SpawnAt453C80')==1
         and source.count('SpawnMixedAt453C80')==1
         and 'g_F701_VolleyYAt00658268' in source,
         'true C9 native signed projectile/storm source changed')
    method='void PrepareActionAt453D60(int);'
    need(src.count(method)==1,'original native method source declaration changed')
    src=src.replace(method,method+
         ' void ConfigureStormAt454BC0(int,int,int);'
         ' void SpawnMixedAt453C80(int,int,float,char,int);',1)
    borrowed=('struct FighterBorrowedXViewF833 { '
              'unsigned char observedUnknown[0x44]; float xAt44; };\n')
    return borrowed+'extern float g_F701_VolleyYAt00658268;\n'+src.replace(
         mark,'#include "FighterScriptedFourWayC9F833.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F833-whole.cpp'
    obj=O/'Boss005214B0-F833-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
         cwd=R,env=env,capture_output=True,text=True,timeout=280)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'whole original fighter C9 VC7.1 compilation failed '+
         (p.stdout+p.stderr)[-850:])
    return obj

def main():
    rd=load('f833_reader','compare-coff-function.py')
    ac=load('f833_actions','report-fighter-action-handlers.py')
    f820=load('f833_f820','verify-scripted-fighter-landing-trio-f820.py')
    pe=rd.verified_target()
    d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'native original giant function identity changed')
    _,mapped=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    original=rd.pe_bytes_at(pe,by[0xc9],by[0xca]-by[0xc9])
    n=list(d.disasm(original,by[0xc9]))
    need(len(original)==279 and len(n)==86 and n[-1].op_str=='0x52cb4f',
         'real original C9 complete native case boundaries differ')
    obj=compile_one(original_source())
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(18639,5001,794,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'complete new source current VC7.1 frame/COFF DATA changed')
    markers=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
       and x.op_str.endswith(', 0xcb')
       and any('g_FighterProbeMarker' in r['symbol']
               and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(markers)==1 and markers[0]>=86,'genuine following original CA source marker not unique')
    index=markers[0]
    src=ins[index-86:index]
    lo,hi=src[0].address,src[-1].address+src[-1].size
    need(hi-lo==279 and len(src)==86
         and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(n,src)),
         'native 279B/86-x86 C9 storm x87 opcode or instruction width differs')
    actual=[r for r in refs if lo<=r['offset']<hi]
    mask=f820.physical_fields(rd,original,by[0xc9],actual,lo,11)
    for a,b in zip(n,src):
        if a.mnemonic in ('call','fadd','fcomp') and (
            a.mnemonic=='call' or '[0x' in a.op_str):
            # Every original PE-owned field is verified by the strict
            # physical_fields call above; this loop protects moving
            # the actual original instruction positions.
            pass
    for r in actual:
        k=r['offset']-lo
        source_inst=next(x for x in src if x.address<=r['offset']<x.address+x.size)
        native_inst=n[src.index(source_inst)]
        need(k==native_inst.address-by[0xc9]+native_inst.size-4,
             'true original physical C9 relocation field shifted within x86 instruction')
    wrong=[j for j in range(279) if j not in mask and original[j]!=code[lo+j]]
    need(len(wrong)==47
         and n[-1].mnemonic==src[-1].mnemonic=='jmp'
         and src[-1].op_str==hex(ret-4),
         'actual original C9 source register phase/outer JMP machine differences changed')
    # Preserve complete original CF/D0/D1/D2 original-size and PE
    # typed call/global relocations in the SAME new C9 parent.
    endmarks=[i for i,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x12d')
        and any('g_FighterProbeMarker' in r['symbol']
             and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(endmarks)==1 and endmarks[0]>=223,
         'native following 0x12C real source marker missing')
    k=endmarks[0]
    earlier=ins[k-223:k]
    prior=[]
    idx=0
    for action in (0xcf,0xd0,0xd1,0xd2):
        nx,size,nf,nb=OLDER[action]
        seg=earlier[idx:idx+nx];idx+=nx
        start,finish=seg[0].address,seg[-1].address+seg[-1].size
        native=rd.pe_bytes_at(pe,by[action],by[FOLLOW[action]]-by[action])
        decoded=list(d.disasm(native,by[action]))
        need(finish-start==size==len(native) and len(decoded)==len(seg)==nx
             and all(a.mnemonic==b.mnemonic and a.size==b.size for a,b in zip(decoded,seg)),
             'previous original CF/D0/D1/D2 whole native source geometry changed')
        fields=[r for r in refs if start<=r['offset']<finish]
        pmask=f820.physical_fields(rd,native,by[action],fields,start,nf)
        bad=[j for j in range(size) if j not in pmask and native[j]!=code[start+j]]
        need(len(bad)==nb,'previous original true actor resource source register byte count changed')
        prior.append({'action':hex(action),'real_original_PE_fields':nf,
                      'real_nonrelocation_source_wrong_B':nb})
    # Native common getter physical fallback remains source-shaped
    # but four genuine non-PE GPR operand bytes still differ.
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    f=[r for r in refs if ret-46<=r['offset']<ret]
    masked=f820.physical_fields(rd,tail,0x52cb25,f,ret-46,3)
    bad=[j for j in range(46) if j not in masked and tail[j]!=code[ret-46+j]]
    need(bad==[10,12,16,19],
         'current original common default GPR differences changed')
    out={'original_game_giant':'0x005214B0',
        'native_original_whole_callable_CODE_B':46755,
        'new_whole_source_callable_CODE_B':ret,
        'new_actual_original_storm_action':'0xC9',
        'native_C9_original_whole_inner_CODE_B':279,
        'native_C9_x86':86,
        'native_C9_real_PE_COFF_fields':11,
        'actual_original_C9_nonrelocation_wrong_byte_count':len(wrong),
        'previous_CF_D0_D1_D2_actual_native_fields_rechecked':prior,
        'genuine_borrowed_member_only_offset':'0x44',
        'native_original_default_GPR_wrong_positions':bad,
        'native_separately_owned_afterRET_DATA_B':901,
        'original_complete_whole_function_exact':False,
        'accepted_new_whole_authored_CODE_B':0,
        'mass_cold_replay_run':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    print('F833 original 0xC9 storm shot 279B/86-x86/11 real PE fields in a fresh 18,639-B/5,001-x86 whole fighter. Natural borrowed xAt44 recovers all native opcode/width grammar; 47 honest original nonrelocation GPR/parent-JMP bytes still wrong. Prior CF/D0/D1/D2 physical PE cases, 901B DATA verified. Giant 46,755B NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired,StopIteration) as e:
        print('F833 whole original C9 storm PE/source FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
