#!/usr/bin/env python3
"""F560: original native action 8 before x87 contact, inside giant 00543210.

Regenerate full actual actor actions 6, 7 and 8 as natural MSVC7.1 C++,
then verify all native x86 GPR/x87/branch instruction roles, physical
COFF refs and native original whole-switch DATA. Each original huge boss
CODE extent is attested first. Only this NEW TU compiles; no all-unit cold
replay, accepted subrange credit, source padding or target assembly graft.
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
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
OUT=ROOT/'.analysis/f560-precontact-stage-source'
ADDRESS=0x00543210
TAG='Boss00543210'
REAL_REFS={
  18:('REL32',0x0040FAC0,'SetNativeActionAt40FAC0'),
  29:('REL32',0x00453E20,'ResetAt453E20'),
  36:('DIR32',0x00657D14,'g_ExtraThresholdAt00657D14'),
  42:('REL32',0x0040FB40,'SetAuxActionAt40FB40'),
  45:('DIR32',0x0065782C,'g_ThresholdAt0065782C'),
  59:('DIR32',0x0065782C,'g_ThresholdAt0065782C'),
  65:('REL32',0x0040FAC0,'SetNativeActionAt40FAC0'),
  69:('REL32',0x00453E20,'ResetAt453E20')}


def need(ok,why):
    if not ok: raise ValueError(why)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,f'missing original-only source helper {path}')
    obj=importlib.util.module_from_spec(spec)
    sys.modules[name]=obj
    spec.loader.exec_module(obj)
    return obj


def original_eight(reader,pe,decoder,boss,source6):
    table=boss['tables'][0]
    need(boss['jump_count']==7 and table['slots']==11 and table['map_addr'] is None,
         'not the original native seven-way giant with 11-slot first table')
    raw=reader.pe_bytes_at(pe,table['dense_addr']+32,8)
    a,b=(int.from_bytes(raw[i:i+4],'little') for i in (0,4))
    need(boss['address']<a<b<boss['address']+boss['size'],
         'original complete native case-8 instruction bounds exceed huge function')
    ins=list(decoder.disasm(reader.pe_bytes_at(pe,a,b-a),a))
    need(len(ins)==117 and b-a==403 and ins[0].address==a
         and ins[-1].address+ins[-1].size==b,
         'not the full original 117-instruction/403-byte precontact actor case')
    need(ins[10].mnemonic=='cmp' and ins[10].op_str.endswith(', 4')
         and ins[16].mnemonic=='push' and ins[16].op_str=='0xce',
         'original byte state/transition argument differs')
    need(ins[32].mnemonic=='cmp' and ins[32].op_str.endswith(', 3')
         and ins[36].mnemonic=='fcomp' and ins[36].op_str=='dword ptr [0x657d14]'
         and ins[40].mnemonic=='push' and ins[40].op_str=='4'
         and ins[42].mnemonic=='call' and ins[42].op_str=='0x40fb40',
         'native 13-insn stage-3 bonus callback does not precede x87 contact')
    need(ins[45].mnemonic==ins[59].mnemonic=='fcomp'
         and ins[45].op_str==ins[59].op_str=='dword ptr [0x65782c]',
         'original contact x87 threshold fields changed')
    need(ins[91].mnemonic=='cmp' and ins[91].op_str.endswith(', 3'),
         'native after-counter stage transition no longer equals three')
    need(ins[94].mnemonic==ins[96].mnemonic==ins[98].mnemonic==ins[100].mnemonic=='mov',
         'native motion/flag initialization sequence moved')
    need('+ 0x50]' in ins[94].op_str and ins[94].op_str.endswith(', 0xc0e00000')
         and '+ 0x3ac]' in ins[96].op_str and ins[96].op_str.endswith(', 0')
         and '+ 0x54]' in ins[98].op_str and '+ 0x5c]' in ins[100].op_str,
         'native original source order must be position, flag, velocity, speed')
    floats=[source6.literal_float(int(ins[k].op_str.split(', ')[-1],16)) for k in (98,100)]
    need(floats==['18.0f','0.95f'], 'native actor role speed/velocity original changed')
    need(ins[-2].mnemonic=='call' and ins[-2].op_str=='dword ptr [edx]',
         'actual original native actor virtual dispatch not at vtable[0]')
    return ins,floats


def generate_source(stage,real6,real7,base_source):
    natural=stage.generate(TAG,real6,real7,base_source['native_report'],
        base_source['mapped'],base_source['reader'],base_source['pe'],
        base_source['decoder'],base_source['boss'],base_source['source6'],
        base_source['opening'],base_source['switch'],base_source['zero'],
        base_source['one'])
    original_name=f'FighterSwitchF557_{TAG}'
    need(natural.count(original_name)>=2,'older native no-flag C++ source owner missing')
    mark='case 0x8: g_FighterProbeMarker = 9; break;'
    start='case 0x6:'
    next_case='case 0x7:'
    need(natural.count(start)==natural.count(next_case)==natural.count(mark)==1,
         'previous native C++ six/seven sources no longer unique')
    core=natural[natural.index(start):natural.index(next_case)]
    expected='''            if (S16(0x62) == 3 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(4);'''
    need(core.count(expected)==1 and core.count('            if (POS48 > g_ThresholdAt0065782C) {')==1,
         'original native stage/x87 check expression was not found')
    case=(core.replace(start,'case 0x8:',1)
         .replace('U8(0x511) == 3','U8(0x511) == 4')
         .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCE)')
         .replace(expected+'\n','')
         .replace('POS = 0.0f;','POS = -7.0f;')
         .replace('POS54 = 19.0f;','POS54 = 18.0f;'))
    contact='            if (POS48 > g_ThresholdAt0065782C) {'
    need(case.count(contact)==1,'native x87 threshold contact branch changed')
    case=case.replace(contact,expected+'\n'+contact)
    stores='''                    POS = -7.0f;
                    POS54 = 18.0f;
                    POS5C = 0.95f;'''
    need(case.count(stores)==1,'native role source float store statement sequence changed')
    case=case.replace(stores,'''                    POS = -7.0f;
                    FLAG = 0;
                    POS54 = 18.0f;
                    POS5C = 0.95f;''')
    need(case.count('SetAuxActionAt40FB40(4)')==1
         and case.count('                    FLAG = 0;')==1,
         'native new case has incorrect guarded callback or flag store')
    return natural.replace(mark,case.rstrip()).replace(original_name,
                       f'FighterSwitchF560_{TAG}')


def compile_one(src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss00543210-precontact-action8.cpp'
    obj=OUT/'Boss00543210-precontact-action8.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                        env=env,cwd=ROOT,text=True,capture_output=True,timeout=120)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'original VC7.1 selected source failed: {proc.stderr}')
    return obj


def candidate_three(reader,decoder,obj,boss):
    code,refs=reader.object_function(obj,
                   '?Advance@FighterSwitchF560_Boss00543210@@QAEXXZ')
    allins=[]
    for ins in decoder.disasm(code,0):
        allins.append(ins)
        if ins.mnemonic=='ret':break
    need(allins and allins[-1].mnemonic=='ret','generated original-style normal RET missing')
    postret=allins[-1].address+allins[-1].size
    need(len(code)-postret==boss['postret_size'],
         'complete native post-RET dense/sparse jump DATA shape changed')
    entries=sorted((r for r in refs if postret+24<=r['offset']<postret+40),
                  key=lambda r:r['offset'])
    need(len(entries)==4 and all(r['type']=='DIR32'
             and r['offset']==postret+24+i*4 and r['local_symbol_offset'] is not None
             for i,r in enumerate(entries)),
         'original native case6/7/8/9 physical jump-table COFF labels missing')
    starts=[r['local_symbol_offset'] for r in entries]
    need(starts==sorted(set(starts)) and 0<=starts[0]<starts[-1]<postret,
         'original source-candidate case spans overlap or leave CODE')
    actual=[]
    for k,expected in enumerate((115,115,117)):
        a,b=starts[k:k+2]
        ins=list(decoder.disasm(code[a:b],a))
        expected_bytes=(393,393,403)[k]
        need(len(ins)==expected and sum(x.size for x in ins)==expected_bytes,
             'native C++ source failed to emit entire original case size/instructions')
        actual.append(ins)
    return code,refs,allins,postret,actual


def case8_typed_refs(original,probe,refs):
    a,b=probe[0].address,probe[-1].address+probe[-1].size
    fields=[r for r in refs if a<=r['offset']<b]
    need(len(fields)==8,'new original action8 requires exactly eight COFF fields')
    for index,(kind,target,sym) in REAL_REFS.items():
        nat=original[index];cand=probe[index]
        need(nat.mnemonic==cand.mnemonic==('call' if kind=='REL32' else 'fcomp'),
             f'original native COFF call/float instruction differs at {index}')
        expected=(f'0x{target:x}' if kind=='REL32' else f'dword ptr [0x{target:x}]')
        need(nat.op_str==expected,'original native target operand differs from actual physical PE')
        source=[r for r in fields if cand.address<=r['offset']<cand.address+cand.size]
        need(len(source)==1 and source[0]['type']==kind and sym in source[0]['symbol'],
             f'actual source COFF target and type incorrect at {index}')
    need(original[-2].mnemonic==probe[-2].mnemonic=='call'
         and original[-2].op_str==probe[-2].op_str=='dword ptr [edx]',
         'original native vtable[0] actor call register/method not matched')
    return len(fields)


def main():
    reader=module('f560_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f560_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f560_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f560_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f560_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    opening=module('f560_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    core=module('f560_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    stage=module('f560_stage',ROOT/'scripts/verify-fighter-stage-no-flag-source.py')
    bonus=module('f560_bonus',ROOT/'scripts/verify-fighter-extra-stage-action-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads(PINNED.read_text())['bosses'] if b['address']==ADDRESS)
    need(boss['size']==58294 and boss['postret_size']==943,
         'whole original boss CODE or after-RET DATA extent drift')
    report,mapped=actions.report_boss(reader,pe,decoder,boss)
    original6=stage.original_case(reader,pe,decoder,boss,6,core)
    original7=stage.original_case(reader,pe,decoder,boss,7,core)
    original8,floats=original_eight(reader,pe,decoder,boss,core)
    args={'native_report':report,'mapped':mapped,'reader':reader,'pe':pe,
          'decoder':decoder,'boss':boss,'source6':core,'opening':opening,
          'switch':switch,'zero':zero,'one':one}
    source=generate_source(stage,original6,original7,args)
    obj=compile_one(source)
    code,refs,allins,postret,cases=candidate_three(reader,decoder,obj,boss)
    total=0
    for (native,policy),compiled in zip((original6,original7),cases[:2]):
        core.compare_grammar(native,compiled)
        wide,long=stage.verify_wide_encodings(native,compiled,boss)
        need((wide,long)==(0,0), 'original nonwide EBP frame unexpectedly changed')
        total+=bonus.verify_physical_fields(native,compiled,refs)
    core.compare_grammar(original8,cases[2])
    need(all(a.size==b.size for a,b in zip(original8,cases[2])),
         'original 403-byte action8 does not have matching physical instruction widths')
    total+=case8_typed_refs(original8,cases[2],refs)
    need(total==24, 'complete action6/7/8 native COFF fields must be exactly 8 per case')
    dense,bytecount,maps=zero.verify_physical_tables(boss,report,pe,reader,
                                                     switch,allins,code,refs,postret)
    output={'boss':f'0x{ADDRESS:08X}','whole_original_CODE':boss['size'],
      'original_case_bytes':[393,393,403], 'candidate_case_bytes':[393,393,403],
      'original_instructions':[115,115,117],
      'original_real_case_COFF_fields':total,
      'precontact_stage':3,'precontact_aux_callback':4,
      'native_position_and_motion_floats':['-7.0f',*floats],
      'original_actor_vtable_call':'dword ptr [edx]',
      'physical_original_DWORD_COFF_fields':dense,
      'original_literal_sparse_bytes':bytecount,
      'full_original_postret_DATA_shape':len(code)-postret}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(output,indent=2)+'\n')
    print(f'{ADDRESS:#010x}: SHA-verified whole native 58,294-byte giant, '
          f'complete natural action6/7/8 = 115+115+117 x86 original GPR/x87/branch instructions, '
          f'393+393+403 original and new C++ candidate CODE lengths; '
          f'{total}/{total} physical authentic COFF call/global fields, '
          f'original first stage3 bonus callback 0040FB40(4) before x87 contact; '
          f'{dense} original-style DWORD jump COFF fields, '
          f'{bytecount} real compressed index bytes')
    print('Single newly affected VC7.1 C++ probe only; '
          'NO complete fighter/split exact CODE credit or all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original 117-insn precontact action-eight source failed:',exc,file=sys.stderr)
        raise SystemExit(1)
