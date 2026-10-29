#!/usr/bin/env python3
"""F653: strict native 0x12C/0x12D/0x12E in full 00543210 C++ fighter.

Cold-build ONE selected 58K original parent source TU; independently check
complete native case extents, every original PE-targeted typed COFF field,
GPR/x87/branch roles and the previously strict CF/D0/D1/D2 prefix and
full after-RET switch table. Inner-case success is never whole function credit.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f653-fighter-falling-recovery'
ACTOR=0x00543210
ACTIONS=(0x12C,0x12D,0x12E)
NEXT={0x12C:0x12D,0x12D:0x12E,0x12E:0x12F}
PARAMS={0x12C:(0,2,0x1B,0),0x12D:(0,4,0x1D,1),0x12E:(2,2,0x1D,0)}
# Native instruction index: physical original PE address, x86 mnemonic,
# genuine COFF relocation target name in the source (not an invented mask).
FIELDS={
  13:(0x00453E20,'call','ResetAt453E20'),
  24:(0x00658058,'fsub','g_JumpGroundCorrectionAt00658058'),
  29:(0x0065782C,'fcomp','g_ThresholdAt0065782C'),
  38:(0x0040FA30,'call','GetNativeActionAt40FA30'),
  46:(0x0040FAC0,'call','SetNativeActionAt40FAC0'),
}


def need(ok,reason):
    if not ok:raise ValueError(reason)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,path)
    need(sp is not None and sp.loader is not None,'missing source '+str(path))
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def native_cases(reader,pe,decoder,boss,mapped):
    by={r['action']:int(r['handler'],16) for r in mapped}
    found={}
    for action in ACTIONS:
        first,last=by[action],by[NEXT[action]]
        orig=list(decoder.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        want_count=61 if action==0x12D else 59
        want_size=219 if action==0x12D else 207
        need(boss['address']<first<last<boss['address']+boss['size']
             and last-first==want_size and len(orig)==want_count
             and sum(x.size for x in orig)==want_size,
             f'original complete physical 0x{action:X} bounds/decoder differ')
        need(orig[0].mnemonic=='mov' and orig[-1].mnemonic=='jmp'
             and orig[-1].op_str=='0x5515c2'
             and orig[23].mnemonic=='fld' and '+ 0x50]' in orig[23].op_str
             and orig[31].mnemonic=='test' and orig[31].op_str=='ah, 5'
             and orig[32].mnemonic=='jp'
             and orig[44].mnemonic=='push' and orig[44].op_str==str(PARAMS[action][0])
             and orig[49 if action!=0x12D else 51].mnemonic=='cmp',
             f'original 0x{action:X} native movement/CFG/state pattern differs')
        last_prepare=59 if action==0x12D else 57
        need(orig[last_prepare].mnemonic=='call'
             and orig[last_prepare].op_str=='0x453d60'
             and orig[last_prepare-2].mnemonic=='push'
             and orig[last_prepare-2].op_str==hex(PARAMS[action][2])
             and orig[last_prepare-8].mnemonic=='cmp'
             and orig[last_prepare-8].op_str.endswith(', '+str(PARAMS[action][1])),
             f'original 0x{action:X} authentic native animation stage differs')
        if action==0x12D:
            need(orig[48].mnemonic=='mov' and '+ 0xf00]' in orig[48].op_str,
                 'original 0x12D must clear its extra native word state')
        physical=FIELDS|{last_prepare:(0x00453D60,'call','PrepareActionAt453D60')}
        for ordinal,(target,mn,_) in physical.items():
            x=orig[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(x.mnemonic==mn and x.op_str==want,
                 f'original PE physical x86 ordinal {ordinal} target {target:#x} differs')
        found[action]=(orig,physical,first,last)
    return found


def replace_following_cases(src):
    for action in ACTIONS:
        next_action,frame,anim,clear=PARAMS[action]
        marker=f'        case 0x{action:X}: g_FighterProbeMarker = {action+1}; break;'
        need(src.count(marker)==1,f'expected native 0x{action:X} source marker missing')
        macros={'F653_ACTION':f'0x{action:X}', 'F653_NEXT_ACTION':str(next_action),
                'F653_PREPARE_FRAME':str(frame), 'F653_PREPARE_ANIM':f'0x{anim:X}',
                'F653_CLEAR_F00':str(clear)}
        fragment='\n'.join(f'#define {k} {v}' for k,v in macros.items())
        fragment+='\n#include "FighterFallingRecoveryF653.inc"\n'
        fragment+='\n'.join(f'#undef {k}' for k in macros)
        src=src.replace(marker,fragment)
    need(src.count('        case 0x12F: g_FighterProbeMarker = 304; break;')==1,
         'real following 0x12F handler/source case lost')
    return src


def verify_new(reader,pe,decoder,code,refs,old,originals,h,following_native=None):
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    offset=old['continuation_source_ordinal']
    strict=[]
    for action in ACTIONS:
        original,fields,lo,hi=originals[action]
        generated=ins[offset:offset+len(original)]
        need(len(generated)==len(original) and generated[-1].mnemonic=='jmp'
             and all(a.size==b.size for a,b in zip(original,generated))
             and generated[-1].op_str==ins[old['continuation_source_ordinal']-1].op_str,
             f'0x{action:X}: native x86 widths/count/jump-tail changed')
        # Last instruction is an external shared exit; its exact label is
        # compared by the normalized original/generator branch role below.
        code_bytes=generated[-1].address+generated[-1].size-generated[0].address
        need(code_bytes==hi-lo,f'0x{action:X}: entire native physical CODE size differs')
        physical=[f for f in refs if generated[0].address<=f['offset']<generated[-1].address+generated[-1].size]
        need(len(physical)==len(fields),
             f'0x{action:X}: true original 6 PE/COFF fields no longer owned whole')
        for ordinal,(target,mn,symbol) in fields.items():
            orig,gen=original[ordinal],generated[ordinal]
            want=f'0x{target:x}' if mn=='call' else f'dword ptr [0x{target:x}]'
            need(orig.mnemonic==mn and orig.op_str==want and gen.mnemonic==mn,
                 f'0x{action:X} source x86{ordinal}: true original PE targeted operation differs')
            linked=[f for f in physical if gen.address<=f['offset']<gen.address+gen.size]
            need(len(linked)==1 and linked[0]['type']==('REL32' if mn=='call' else 'DIR32')
                 and linked[0]['addend']==0
                 and linked[0]['local_symbol_offset'] is None
                 and symbol in linked[0]['symbol'],
                 f'0x{action:X} source x86{ordinal}: not genuine typed original {target:#x} PE/COFF field')
        lhs,rhs=h['f598'].normalized(original),h['f598'].normalized(generated)
        # The original executable contains linked absolute PE floats; our
        # fresh unlinked COFF object contains zero at these fields. Only
        # physically validated float fields may differ here.
        absfields={ordinal for ordinal,(_,mn,_) in fields.items() if mn!='call'}
        wrong=[(i,x,y) for i,(x,y) in enumerate(zip(lhs,rhs)) if x!=y and i not in absfields]
        need(not wrong,f'0x{action:X}: genuine native GPR/x87/CFG roles differ: {wrong[:8]}')
        strict.append({'original_action':f'0x{action:X}',
                       'original_native_physical_start':f'0x{lo:08X}',
                       'original_native_physical_next':f'0x{hi:08X}',
                       'entire_original_native_x86_instructions':len(original),
                       'entire_original_inner_CODE_bytes':hi-lo,
                       'real_typed_PE_COFF_fields':len(physical),
                       'independently_accepted_whole_function':False})
        offset+=len(original)
    if following_native is None:
        need(ins[offset].mnemonic=='mov' and ins[offset].op_str.endswith(', 0x130'),
             '0x12E must end directly before the original following 0x12F marker')
    else:
        need(following_native==0x12F and ins[offset].mnemonic=='mov'
             and ins[offset].op_str=='edx, dword ptr [ebp - 8]'
             and ins[offset+1].mnemonic=='movsx'
             and ins[offset+1].op_str=='eax, word ptr [edx + 0x62]',
             'native 0x12F continuation does not immediately follow 0x12E')
    return strict,offset


def main():
    f651=load('f653_prev_f651',ROOT/'scripts/verify-fighter-resource-shots-f651.py')
    h=f651.load_helpers()
    reader=load('f653_reader',ROOT/'scripts/compare-coff-function.py')
    acts=load('f653_acts',ROOT/'scripts/report-fighter-action-handlers.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if x['address']==ACTOR)
    report,mapped=acts.report_boss(reader,pe,decoder,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    originals=native_cases(reader,pe,decoder,boss,mapped)
    older={a:f651.true_native(reader,pe,decoder,boss,by,a) for a in (0xD1,0xD2)}
    source=f651.source_with_d1_d2(reader,pe,decoder,boss,report,mapped,h)
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-CF-D0-D1-D2-12C-12D-12E.cpp'
    obj=OUT/'Boss00543210-CF-D0-D1-D2-12C-12D-12E.obj'
    cpp.write_text(replace_following_cases(source))
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
    (OUT/'compiler.log').write_text(cp.stdout+cp.stderr)
    need(cp.returncode==0,'actual pinned VC7.1 whole parent compile failed: '+cp.stderr[-550:])
    code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF598_Boss{ACTOR:08X}@@QAEXXZ')
    old=f651.verify_full(reader,pe,decoder,boss,report,mapped,code,refs,older,h,following_native=0x12C)
    strict,_=verify_new(reader,pe,decoder,code,refs,old,originals,h)
    receipt={'pinned_original_parent':'0x00543210','complete_original_parent_NONEXACT':True,
             'parent_original_CODE_bytes':boss['size'],'parent_original_after_RET_DATA_bytes':boss['postret_size'],
             'older_CF_D0_D1_D2_and_jump_tables_verified_same_fresh_parent':True,
             'strict_new_native_handlers':strict,
             'strict_new_internal_native_CODE_bytes':sum(r['entire_original_inner_CODE_bytes'] for r in strict),
             'accepted_new_independent_whole_function_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('F653 selected original whole parent 00543210: '
          f'{len(strict)} new strict physical native case interiors, '
          f'{receipt["strict_new_internal_native_CODE_bytes"]} real uncredited CODE B, '
          f'{sum(r["entire_original_native_x86_instructions"] for r in strict)} original x86 roles, '
          f'{sum(r["real_typed_PE_COFF_fields"] for r in strict)} physical typed PE/COFF fields. '
          'Same newly compiled parent retained CF/D0/D1/D2 and full afterRET DATA; '
          '22 giant parents still NONEXACT; no 943-unit cold replay.')


if __name__=='__main__':
    main()
