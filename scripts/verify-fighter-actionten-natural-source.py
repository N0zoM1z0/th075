#!/usr/bin/env python3
"""Reconstruct whole native action-10 cases in eleven giant fighter contexts.

Every 20-/31-instruction case is bounded by the original first-switch DWORD
case-10 entry and the independently verified case-0x32 singleton entry.
Compile only the selected original-backed natural VC7.1 C++ switch probe,
with previously verified real cases 0..5 and 9. Remaining cases are
explicitly test-only marker stores. No cropped original CODE exact credit.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f549-action-ten-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
NAME={0x0045DD70:'Reimu',0x004AC040:'CharacterMove'}
CALLS={0x00453D60:'PrepareActionAt453D60',0x00453E20:'ResetAt453E20',
       0x0040FA30:'GetNativeActionAt40FA30',0x0040FAC0:'SetNativeActionAt40FAC0'}
OWNER=re.compile(r'(eax|ecx|edx), dword ptr \[ebp - (0x[0-9a-f]+|\d+)\]')


def need(ok,detail):
    if not ok: raise ValueError(detail)


def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None, f'missing original validator {path}')
    result=importlib.util.module_from_spec(spec)
    sys.modules[tag]=result
    spec.loader.exec_module(result)
    return result


def native_ten(reader,target,decoder,boss,report):
    table=boss['tables'][0]
    need(table['slots']==11 and table['map_addr'] is None and boss['jump_count'] in (6,7),
         'wrong original direct first switch')
    entry=int.from_bytes(reader.pe_bytes_at(target,table['dense_addr']+40,4),'little')
    singleton=[r for r in report['singleton_branches'] if r['action']==0x32]
    need(len(singleton)==1,'unverified original action 0x32 branch/next boundary')
    last=int(singleton[0]['handler'],16)
    need(boss['address']<entry<last<boss['address']+boss['size'],
         'native case-10 span outside complete original boss')
    ins=list(decoder.disasm(reader.pe_bytes_at(target,entry,last-entry),entry))
    need(ins and ins[0].address==entry and ins[-1].address+ins[-1].size==last,
         'original action-ten span not contiguous complete x86 instructions')
    need(len(ins) in (20,31) and ins[-1].mnemonic=='jmp',
         'native complete action ten not actual 20-/31-instruction body')
    expected=101 if len(ins)==31 else (87 if boss['address']==0x00564BE0 else 69)
    need(last-entry==expected,'original action-ten natural EBP addressing width changed')
    calls=[int(i.op_str,16) for i in ins if i.mnemonic=='call' and i.op_str.startswith('0x')]
    wanted=([0x453D60] if len(ins)==31 else [])+[0x453E20,0x40FA30,0x40FAC0,0x40FAC0]
    need(calls==wanted,'actual original action-ten call sequence changed')
    push=[int(i.op_str,0) for i in ins if i.mnemonic=='push']
    need(len(push)==(3 if len(ins)==31 else 2), 'native action-ten argument count changed')
    if len(ins)==31: need(push[0]==30,'native first-state call not original 30')
    low,high=push[-2:]
    need((low,high) in ((0,2),(3,2),(0,1)),
         'unexpected original fighter-specific action-ten state transition')
    need(any('+ 0x70' in i.op_str for i in ins)
         and any('+ 0x4e0' in i.op_str for i in ins),
         'native state/current-action member offsets changed')
    if len(ins)==31:
        need(any('+ 0x62' in i.op_str for i in ins) and any('+ 0x64' in i.op_str for i in ins),
             'original first-state guard is incomplete')
    return ins,low,high,len(ins)==31


def source_ten(nine,tag,report,mapped,original9,reader,target,decoder,boss,
               six,switch,zero,one,low,high,prepare):
    base,ncases,aux=nine.source_nine_for(tag,report,mapped,original9,
                     reader,target,decoder,boss,six,switch,zero,one)
    existing=f'FighterSwitchF547_{tag}'
    need(base.count(existing)>=2,'previous verified natural opening/9 source changed')
    base=base.replace(existing,f'FighterSwitchF549_{tag}')
    declaration='void ResetAt453E20();'
    need(base.count(declaration)==1,'native reset class declaration changed')
    base=base.replace(declaration,declaration+' void PrepareActionAt453D60(int);')
    macro='#define I16(off)'
    need(base.count(macro)==1,'original 16-bit source field macro missing')
    base=base.replace(macro,'#define I32(off) *reinterpret_cast<int*>(RAW+(off))\n'+macro)
    label='case 0xA: g_FighterProbeMarker = 11; break;'
    need(base.count(label)==1,'no unique native original case-ten marker label')
    case='''case 0xA:\n'''
    if prepare:
        case+='''            if (I16(0x62) == 0 && I16(0x64) == 0)
                PrepareActionAt453D60(30);
'''
    case+=f'''            ResetAt453E20();
            if (GetNativeActionAt40FA30() == I16(0x70)) {{
                if (I32(0x4E0) == 0)
                    SetNativeActionAt40FAC0({low});
                else
                    SetNativeActionAt40FAC0({high});
            }}
            break;'''
    return base.replace(label,case),ncases,aux


def compile_one(tag,source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}-case-ten.cpp';obj=OUT/f'{tag}-case-ten.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     cwd=ROOT,env=env,text=True,capture_output=True,timeout=120)
    (OUT/f'{tag}-compile.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,f'{tag}: selected VC7.1 natural source failed: {p.stderr}')
    return obj


def candidate_ten(reader,decoder,object_path,tag,boss):
    code,refs=reader.object_function(object_path,f'?Advance@FighterSwitchF549_{tag}@@QAEXXZ')
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret','missing normal generated C++ function RET')
    ret=ins[-1].address+ins[-1].size
    need(len(code)-ret==boss['postret_size'],
         'original post-RET switch DATA physical extent changed')
    start_record=[r for r in refs if r['offset']==ret+40]
    need(len(start_record)==1 and start_record[0]['type']=='DIR32'
         and start_record[0]['local_symbol_offset'] is not None,
         'no real COFF case-ten physical DWORD label')
    start=start_record[0]['local_symbol_offset']
    first_case=[r for r in refs if r['offset']==ret]
    need(len(first_case)==1,'no first original action table slot in source COFF')
    first_case_addr=first_case[0]['local_symbol_offset']
    need(first_case_addr is not None and first_case_addr<start<ret,
         'original action10 source case label not inside normal code')
    found=[]
    for i,x in enumerate(ins[:-1]):
        if x.address>=first_case_addr:break
        if x.mnemonic=='cmp' and x.op_str.endswith(', 0x32') and ins[i+1].mnemonic=='je':
            found.append(int(ins[i+1].op_str,16))
    need(len(found)==1,'generated original 0x32 singleton equality branch lost')
    end=found[0]
    need(start<end<=ret,'C++ action-ten full span to verified singleton invalid')
    sub=list(decoder.disasm(code[start:end],start))
    need(sub and sub[0].address==start and sub[-1].address+sub[-1].size==end,
         'generated action10 not contiguous native complete instructions')
    return code,refs,ins,ret,sub


def physical_calls(original,candidate,refs):
    native=[(i,int(x.op_str,16)) for i,x in enumerate(original)
            if x.mnemonic=='call' and x.op_str.startswith('0x')]
    probe=[(i,x) for i,x in enumerate(candidate) if x.mnemonic=='call']
    need(len(native)==len(probe) and [a for a,b in native]==[a for a,b in probe],
         'physical original action-ten call positions differ')
    for (order,target),(kind,ins) in zip(native,probe):
        need(target in CALLS,'native action10 PE call destination not recognized')
        physical=[r for r in refs if ins.address<=r['offset']<ins.address+ins.size]
        need(len(physical)==1 and physical[0]['type']=='REL32'
             and CALLS[target] in physical[0]['symbol'],
             f'COFF real REL32 position/symbol differs at original case instruction {order}')
    a,b=candidate[0].address,candidate[-1].address+candidate[-1].size
    need(len([r for r in refs if a<=r['offset']<b])==len(native),
         'unexpected extra/missing physical COFF fields inside candidate action ten')
    return len(native)


def owner_dataflow(ins,expected_slot):
    actual=[]
    for i,x in enumerate(ins[:-1]):
        if x.mnemonic!='mov':continue
        m=OWNER.fullmatch(x.op_str)
        if m is None:continue
        reg,slot=m.groups();actual.append(int(slot,0))
        nxt=ins[i+1]
        if nxt.mnemonic=='call':
            need(reg=='ecx','original action ten non-thiscall method receiver')
        else:
            need(f'[{reg} + ' in nxt.op_str,
                 'action-ten member receiver reload not used by next original instruction')
    need(len(actual) in (6,9) and set(actual)=={expected_slot},
         'wrong physical action-ten owner slot or receiver reloads')
    return len(actual)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='Rebuild one original address or Reimu/CharacterMove; default all 11')
    args=parser.parse_args()
    reader=module('f549_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f549_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f549_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f549_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f549_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    six=module('f549_six',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    nine=module('f549_nine',ROOT/'scripts/verify-fighter-actionnine-natural-source.py')
    original=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    fighters=[b for b in json.loads(PINNED.read_text())['bosses'] if b['jump_count']>1]
    need(len(fighters)==11 and sum(b['size'] for b in fighters)==613391,
         'eleven complete native multi-switch boss manifest changed')
    if args.boss:
        names={tag.lower():addr for addr,tag in NAME.items()}
        token=args.boss.lower()
        chosen=names[token] if token in names else int(args.boss,0)
        fighters=[b for b in fighters if b['address']==chosen]
        need(len(fighters)==1,'original address not one of the eleven multi-switch fighters')
    results=[]
    for boss in fighters:
        address=boss['address'];tag=NAME.get(address,f'Boss{address:08X}')
        report,mapped=actions.report_boss(reader,original,decoder,boss)
        native,low,high,prepare=native_ten(reader,original,decoder,boss,report)
        nine_orig=nine.native_case(reader,original,decoder,boss)
        src,case_count,aux=source_ten(nine,tag,report,mapped,nine_orig,
                   reader,original,decoder,boss,six,switch,zero,one,low,high,prepare)
        obj=compile_one(tag,src)
        code,refs,all_ins,ret,candidate=candidate_ten(reader,decoder,obj,tag,boss)
        need(len(native)==len(candidate),'source action ten instruction count changed')
        need(zero.case_grammar(native,False)==zero.case_grammar(candidate,False),
             f'{address:08X}: actual native action-ten instruction/branch/member/control shape differs')
        real_gpr=zero.case_grammar(native,True)==zero.case_grammar(candidate,True)
        native_owner=int(report['case_zero']['this_slot'].split('0x')[1],16)
        nloads=owner_dataflow(native,native_owner)
        need(owner_dataflow(candidate,4)==nloads,
             'source action ten does not use same native number of receiver reloads')
        nrefs=physical_calls(native,candidate,refs)
        nb=sum(x.size for x in native);cb=sum(x.size for x in candidate)
        need(cb==(101 if prepare else 69)
             and nb==cb+(nloads*3 if native_owner>=128 else 0),
             f'{address:08X}: real source/native saved-owner encoding lengths unexplained')
        slots,indexbytes,maps=zero.verify_physical_tables(boss,report,original,
                    reader,switch,all_ins,code,refs,ret)
        row={'boss':f'0x{address:08X}','whole_original_CODE':boss['size'],
             'original_action10_bytes':nb,'probe_action10_bytes':cb,
             'original_action10_instructions':len(native),'original_relocation_calls':nrefs,
             'first_state_prepare':prepare,'original_transition_arguments':[low,high],
             'native_receiver_reload_count':nloads,'exact_GPR_registers':real_gpr,
             'original_switch_COFF_DWORD_fields':slots,
             'original_sparse_index_bytes':indexbytes,'postret_DATA_shape':len(code)-ret,
             'source_explicit_case_count':case_count}
        results.append(row)
        print(f'{address:#010x}: original action10 {len(native)} instructions / {nb} bytes, '
              f'{len(native)}/{len(native)} native control/member/branch roles, '
              f'{nrefs}/{nrefs} real REL32 calls, prepare(30)={prepare}, '
              f'state arguments={low}/{high}, GPR register-identical={real_gpr}, '
              f'{slots} native-style DWORD refs, {indexbytes} byte-exact sparse indexes',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    filename='summary.json' if args.boss is None else f'summary-{fighters[0]["address"]:08X}.json'
    (OUT/filename).write_text(json.dumps(results,indent=2)+'\n')
    print(f'{len(results)}/{len(fighters)} affected original boss contexts with freshly compiled natural C++ '
          'action10 probes; NO giant whole CODE/DATA exact credit, NO all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('TH075 fighter natural action-ten validation failed:',e,file=sys.stderr)
        raise SystemExit(1)
