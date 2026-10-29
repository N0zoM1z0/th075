#!/usr/bin/env python3
"""F556: original complete 117-insn action 6/7 in two giant controllers.

New native-backed game C++ has a stage/floating threshold and extra action
callback absent from earlier 104-insn fighters. Derive every member/float
and real original table slot afresh from the complete SHA-pinned original.
Cold-compile only selected small VC7.1 C++ probes; NEVER register inner
case blocks as standalone exact functions or run an all-unit cold replay.
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
OUT=ROOT/'.analysis/f556-extra-stage-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
FIGHTERS={0x00486550:'Boss00486550',0x004AC040:'CharacterMove'}
REAL_REFS={18:('REL32',0x0040FAC0,'SetNativeActionAt40FAC0'),
           29:('REL32',0x00453E20,'ResetAt453E20'),
           32:('DIR32',0x0065782C,'g_ThresholdAt0065782C'),
           46:('DIR32',0x0065782C,'g_ThresholdAt0065782C'),
           52:('REL32',0x0040FAC0,'SetNativeActionAt40FAC0'),
           56:('REL32',0x00453E20,'ResetAt453E20'),
           64:('DIR32',0x00657D14,'g_ExtraThresholdAt00657D14'),
           70:('REL32',0x0040FB40,'SetAuxActionAt40FB40')}


def require(ok,description):
    if not ok:raise ValueError(description)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    require(spec is not None and spec.loader is not None,f'missing source/native evidence helper {path}')
    result=importlib.util.module_from_spec(spec)
    sys.modules[name]=result
    spec.loader.exec_module(result)
    return result


def native_case(reader,pe,decoder,boss,index,source6):
    table=boss['tables'][0]
    require(table['map_addr'] is None and table['slots']==11,
            'not original native 11-way first switch')
    data=reader.pe_bytes_at(pe,table['dense_addr']+4*index,8)
    start,end=[int.from_bytes(data[k:k+4],'little') for k in (0,4)]
    require(boss['address']<start<end<boss['address']+boss['size'],
            'case outside original whole giant CODE')
    orig=list(decoder.disasm(reader.pe_bytes_at(pe,start,end-start),start))
    require(len(orig)==117 and end-start==403 and
            orig[0].address==start and orig[-1].address+orig[-1].size==end,
            'not complete original 403-byte/117-insn native case')
    require(orig[10].mnemonic=='cmp' and orig[10].op_str.endswith(', '+str(3 if index==6 else 5))
            and orig[16].mnemonic=='push' and orig[16].op_str==('0xcc' if index==6 else '0xcd'),
            'original action-six/seven byte state and transition changed')
    require(orig[60].mnemonic=='cmp' and orig[60].op_str.endswith(', 4')
            and orig[64].mnemonic=='fcomp' and orig[64].op_str=='dword ptr [0x657d14]'
            and orig[68].mnemonic=='push' and orig[68].op_str=='5'
            and orig[70].mnemonic=='call' and orig[70].op_str=='0x40fb40',
            'native 13-instruction stage/floating call policy not observed')
    require(orig[91].mnemonic=='cmp', 'original stage threshold is not native index 91')
    stage=int(orig[91].op_str.split(', ')[-1],0)
    require(stage in (2,4),'original stage transition differs')
    if index==6:
        require(orig[94].mnemonic=='mov' and '+ 0x50], 0' in orig[94].op_str,
                'native action6 initial position is not 0')
        require(orig[100].mnemonic=='mov' and '+ 0x3ac], 0' in orig[100].op_str,
                'native action6 original flag clear absent')
        floats=[source6.literal_float(int(orig[k].op_str.rsplit(', ',1)[-1],16)) for k in (96,98)]
        flag_before=False;position='0.0f'
    else:
        flag_before=bool('+ 0x3ac], 0' in orig[94].op_str)
        if flag_before:
            require('+ 0x50]' in orig[96].op_str and '+ 0x3ac]' in orig[94].op_str,
                    'true action7 flag-first dataflow changed')
            position=source6.literal_float(int(orig[96].op_str.rsplit(', ',1)[-1],16))
            # Original action7 orders FLAG, position, velocity, speed.
            floats=[source6.literal_float(int(orig[k].op_str.rsplit(', ',1)[-1],16)) for k in (98,100)]
        else:
            require('+ 0x50]' in orig[94].op_str and '+ 0x3ac]' in orig[100].op_str,
                    'true action7 position-first dataflow changed')
            position=source6.literal_float(int(orig[94].op_str.rsplit(', ',1)[-1],16))
            floats=[source6.literal_float(int(orig[k].op_str.rsplit(', ',1)[-1],16)) for k in (96,98)]
        require(position=='5.0f', 'native fighter action7 position is not 5.0f')
    require(orig[-2].mnemonic=='call' and orig[-2].op_str=='dword ptr [edx]',
            'actual native C++ virtual call must be dword ptr [edx]')
    return orig,stage,floats,position,flag_before


def source_for(tag,originals,report,mapped,reader,pe,decoder,boss,
               source6,first6,switch,zero,one):
    real6,stage,floats,_,_=originals[0]
    real7,stage7,floats7,position7,flag_first=originals[1]
    require(stage==stage7 and floats==floats7,
            'native action7 different original stage/float velocity from action6')
    # Reuse real C++ for 104-insn baseline but insert independently native
    # new stage-4 x87 condition before the real C++ frame counter increment.
    six=source6.generate_source(tag,stage,floats,report,mapped,
                                 first6,switch,zero,one,reader,pe,decoder,boss)
    declaration='void SetNativeActionAt40FAC0(int);'
    require(six.count(declaration)==1,'earlier true source action-6 owner declaration changed')
    six=six.replace(declaration,declaration+' void SetAuxActionAt40FB40(int);')
    global_decl='extern float g_ThresholdAt0065782C;'
    require(six.count(global_decl)==1,'actual threshold C++ source missing')
    six=six.replace(global_decl,global_decl+'\nextern float g_ExtraThresholdAt00657D14;')
    marker='            ++S16(0x64);'
    require(six.count(marker)==1,'true source ++frame position changed')
    block='''            if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(5);
'''
    six=six.replace(marker,block+marker)
    this_name=f'FighterSwitchF548_{tag}'
    require(six.count(this_name)>=2,'borrowed native F548 C++ owner absent')
    six=six.replace(this_name,f'FighterSwitchF556_{tag}')
    label='case 0x7: g_FighterProbeMarker = 8; break;'
    require(six.count(label)==1,'candidate no longer has original case-7 label')
    body=six[six.index('case 0x6:'):six.index(label)]
    require(body.count('U8(0x511) == 3')==1
            and body.count('SetNativeActionAt40FAC0(0xCC)')==1
            and body.count('POS = 0.0f;')==1,
            'action6 natural source no longer permits native 3-location differences')
    body=(body.replace('case 0x6:','case 0x7:',1)
              .replace('U8(0x511) == 3','U8(0x511) == 5')
              .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCD)')
              .replace('POS = 0.0f;','POS = '+position7+';'))
    if flag_first:
        old='''                    POS = 5.0f;
                    POS54 = '''+floats[0]+''';
                    POS5C = '''+floats[1]+''';
                    FLAG = 0;'''
        new='''                    FLAG = 0;
                    POS = 5.0f;
                    POS54 = '''+floats[0]+''';
                    POS5C = '''+floats[1]+''';'''
        require(old in body,'original early FLAG=0 source dataflow not found')
        body=body.replace(old,new)
    return six.replace(label,body.rstrip())


def compile_one(tag,source):
    OUT.mkdir(parents=True,exist_ok=True)
    path=OUT/f'{tag}-117-case6-7.cpp';obj=OUT/f'{tag}-117-case6-7.obj'
    path.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(path),str(obj),
                           '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                          cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/f'{tag}-compiler.log').write_text(result.stdout+result.stderr)
    require(result.returncode==0,f'{tag}: original-profile VC7.1 compiler failed: {result.stderr}')
    return obj


def candidate_two(reader,decoder,obj,tag,boss):
    code,relocs=reader.object_function(obj,f'?Advance@FighterSwitchF556_{tag}@@QAEXXZ')
    ins=[]
    for x in decoder.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    require(ins and ins[-1].mnemonic=='ret','missing natural original-style RET')
    ret=ins[-1].address+ins[-1].size
    require(len(code)-ret==boss['postret_size'],
            'after-RET dense/sparse original switch DATA size changed')
    physical=sorted((r for r in relocs if ret+24<=r['offset']<ret+36),
                     key=lambda r:r['offset'])
    require(len(physical)==3 and all(r['offset']==ret+24+4*i and r['type']=='DIR32'
                   and r['local_symbol_offset'] is not None for i,r in enumerate(physical)),
            'candidate lacks genuine physical first-table jump destinations 6/7/8')
    addr=[r['local_symbol_offset'] for r in physical]
    require(addr==sorted(set(addr)) and 0<=addr[0]<addr[-1]<ret,
            'generated native case 6/7 addresses alias/escape code')
    result=[]
    for i in range(2):
        a,b=addr[i:i+2]
        block=list(decoder.disasm(code[a:b],a))
        require(len(block)==117 and sum(x.size for x in block)==403,
                'the complete generated C++ 117-instruction case CODE length mismatches original')
        result.append(block)
    return code,relocs,ins,ret,result


def verify_physical_fields(native,candidate,refs):
    first,last=candidate[0].address,candidate[-1].address+candidate[-1].size
    all_fields=[r for r in refs if first<=r['offset']<last]
    require(len(all_fields)==8,'actual 117-instruction case must contain exactly 8 COFF fields')
    for ordinal,(type_,target,name) in REAL_REFS.items():
        u,v=native[ordinal],candidate[ordinal]
        if type_=='REL32':
            require(u.mnemonic==v.mnemonic=='call' and u.op_str==f'0x{target:x}',
                    f'original {ordinal} native call destination differs')
        else:
            require(u.mnemonic==v.mnemonic=='fcomp' and u.op_str==f'dword ptr [0x{target:x}]',
                    f'original {ordinal} native x87 float operand differs')
        match=[r for r in refs if v.address<=r['offset']<v.address+v.size]
        require(len(match)==1 and match[0]['type']==type_ and name in match[0]['symbol'],
                f'candidate physical COFF field missing at native 117-case ordinal {ordinal}')
    require(native[-2].mnemonic==candidate[-2].mnemonic=='call' and
            native[-2].op_str==candidate[-2].op_str=='dword ptr [edx]',
            'original native real virtual vtable call not recreated')
    return len(all_fields)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='Build one original 0x00486550 or 0x004AC040 giant, or CharacterMove')
    args=parser.parse_args()
    reader=module('f556_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f556_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f556_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f556_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f556_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    opening=module('f556_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    source6=module('f556_six',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    byaddress={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    require(sum(byaddress[a]['size'] for a in FIGHTERS)==133531,
            'complete native 50K/82K fighter original extents changed')
    chosen=list(FIGHTERS)
    if args.boss:
        token=args.boss.lower()
        a=0x004AC040 if token=='charactermove' else int(args.boss,0)
        require(a in FIGHTERS,'not one of the two independently verified 117-case originals')
        chosen=[a]
    outcomes=[]
    for address in chosen:
        tag=FIGHTERS[address];boss=byaddress[address]
        native_report,mapped=actions.report_boss(reader,pe,decoder,boss)
        cases=[native_case(reader,pe,decoder,boss,index,source6) for index in (6,7)]
        src=source_for(tag,cases,native_report,mapped,reader,pe,decoder,boss,
                       source6,opening,switch,zero,one)
        obj=compile_one(tag,src)
        code,refs,allins,ret,generated=candidate_two(reader,decoder,obj,tag,boss)
        genuine=0
        for (native,stage,floats,position,flag_first),compiled in zip(cases,generated):
            source6.compare_grammar(native,compiled)
            require(all(a.size==b.size for a,b in zip(native,compiled)),
                    'candidate source has different original physical instruction lengths')
            genuine+=verify_physical_fields(native,compiled,refs)
        require(genuine==16,'two original 117-case blocks require 16 genuine COFF references')
        dense,indexbytes,_=zero.verify_physical_tables(boss,native_report,pe,reader,
                                                        switch,allins,code,refs,ret)
        result={'boss':f'0x{address:08X}','whole_original_CODE':boss['size'],
                'native_case6_and_case7_bytes':806,'native_instructions_per_case':117,
                'real_case_COFF_relocation_fields':genuine,
                'native_action6_stage':cases[0][1],'native_position_and_speed_floats':cases[0][2],
                'native_action7_position':cases[1][3],
                'native_action7_flag_first':cases[1][4],
                'native_stage_guard':4,'native_aux_callback_arg':5,
                'native_table_DWORD_COFF_fields':dense,
                'identical_original_sparse_bytes':indexbytes,
                'complete_original_postret_DATA_shape':len(code)-ret}
        outcomes.append(result)
        print(f'{address:#010x}: whole original {boss["size"]} CODE bytes; '
              f'action 6 and 7 each 403/403 original native CODE, '
              f'117/117 true GPR/x87/branch native instructions and '
              f'8/8 genuine COFF ref fields; original stage={cases[0][1]}, '
              f'position/speed={cases[0][2]}, case7 FLAG first={cases[1][4]}; '
              f'{dense} physical DWORD ref slots, {indexbytes} exact sparse bytes',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    name='summary.json' if args.boss is None else f'summary-{chosen[0]:08X}.json'
    (OUT/name).write_text(json.dumps(outcomes,indent=2)+'\n')
    print(f'{len(outcomes)}/{len(chosen)} original giant contexts freshly compiled; '
          'NO split/whole source CODE exactness claim or all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original 117-instruction fighter source probe failed:',exc,file=sys.stderr)
        raise SystemExit(1)
