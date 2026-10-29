#!/usr/bin/env python3
"""F566: integrate eleven native script-state action cases in 005214B0.

The complete original 46,755-byte Japanese fighter is SHA-verified first.
A fresh, ordinary VC7.1 C++ Advance() implements physical original cases
0..10 *together* in a single TU. Every original case length, x86 GPR/x87/
control grammar, genuine typed COFF call/global ref, full native switch
DWORD and sparse DATA byte is independently checked. Remaining actions
stay diagnostic markers; no whole/split CODE exactness or full cold replay.
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
OUT=ROOT/'.analysis/f566-integrated-scripted-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
ADDR=0x005214B0
TAG='Boss005214B0'

def need(ok,msg):
    if not ok:raise ValueError(msg)

def module(tag,p):
    spec=importlib.util.spec_from_file_location(tag,p)
    need(spec is not None and spec.loader is not None,f'missing native source helper {p}')
    m=importlib.util.module_from_spec(spec)
    sys.modules[tag]=m
    spec.loader.exec_module(m)
    return m

def make_source(reader,pe,dec,boss,report,mapped,
                opening,switch,zero,one,script,nine,ten):
    real678=script.whole_original_cases(reader,pe,dec,boss,None)
    real0to5=opening.native_six(reader,pe,dec,boss)
    generated=script.source_for(reader,pe,dec,boss,report,mapped,
                                opening,switch,zero,one)
    real9=nine.native_case(reader,pe,dec,boss)
    real10,low,high,prepare=ten.native_ten(reader,pe,dec,boss,report)
    need(not prepare and len(real10)==20,
         'original scripted fighter 20-instruction action10 suddenly has prepare call')
    other,case_count,aux=ten.source_ten(nine,TAG,report,mapped,real9,
                    reader,pe,dec,boss,opening,switch,zero,one,low,high,prepare)
    ix9,ix10,ix32=(other.index('case 0x9:'),other.index('case 0xA:'),
                   other.index('case 0x32:'))
    need(ix9<ix10<ix32,'native source independent action9/10 markers changed')
    for k,body in ((9,other[ix9:ix10].rstrip()),(10,other[ix10:ix32].rstrip())):
        old=f'case 0x{k:X}: g_FighterProbeMarker = {k+1}; break;'
        need(generated.count(old)==1,'original scripted switch marker missing')
        generated=generated.replace(old,body)
    dec_method='void ResetAt453E20();'
    need(generated.count(dec_method)==1,'original native actor reset method missing')
    generated=generated.replace(dec_method,dec_method+' void PrepareActionAt453D60(int);')
    macro='#define I16(off)'
    need(generated.count(macro)==1,'native signed-short owner field macro missing')
    generated=generated.replace(macro,
                    '#define I32(off) *reinterpret_cast<int*>(RAW+(off))\n'+macro)
    prev=f'FighterSwitchF565_{TAG}'
    need(generated.count(prev)>=2,'borrowed original game actor type changed')
    generated=generated.replace(prev,f'FighterSwitchF566_{TAG}')
    need(all(generated.count(f'case 0x{i:X}:')==1 for i in range(11)),
         'source no longer contains exactly eleven complete original cases')
    return generated,real0to5+real678+[real9,real10]

def compile_one(source):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/'Boss005214B0-original-eleven.cpp'
    obj=OUT/'Boss005214B0-original-eleven.obj'
    cpp.write_text(source)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,f'original-profile new C++ compilation failed: {p.stderr}')
    return obj

def physical_cases(reader,pe,decoder,obj,boss,report,native):
    code,refs=reader.object_function(obj,
              f'?Advance@FighterSwitchF566_{TAG}@@QAEXXZ')
    inst=[]
    for i in decoder.disasm(code,0):
        inst.append(i)
        if i.mnemonic=='ret':break
    need(inst and inst[-1].mnemonic=='ret','native source switch missing normal RET')
    ret=inst[-1].address+inst[-1].size
    need(len(code)-ret==boss['postret_size']==901,
         'full after-RET original switch DATA layout changed')
    table=boss['tables'][0]
    need(table['slots']==11 and table['map_addr'] is None,
         'not the verified direct original eleven-action switch')
    physical=sorted((r for r in refs if ret<=r['offset']<ret+44),
                    key=lambda r:r['offset'])
    need(len(physical)==11 and all(r['offset']==ret+4*k and r['type']=='DIR32'
         and r['local_symbol_offset'] is not None for k,r in enumerate(physical)),
         'original first eleven native physical DWORD COFF case references missing')
    cpos=[r['local_symbol_offset'] for r in physical]
    ending=[int(inst[i+1].op_str,16) for i in range(len(inst)-1)
            if inst[i].mnemonic=='cmp' and inst[i].op_str.endswith(', 0x32')
            and inst[i+1].mnemonic=='je' and inst[i+1].op_str.startswith('0x')]
    need(len(ending)==1,'native independent action-0x32 singleton case not correctly generated')
    cpos+=ending
    opos=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*k,4),'little')
          for k in range(11)]
    original10end=[int(r['handler'],16) for r in report['singleton_branches']
                   if r['action']==0x32]
    need(len(original10end)==1,'native original case10 physical singleton target absent')
    opos+=original10end
    need(cpos==sorted(set(cpos)) and opos==sorted(set(opos)),
         'native C++ action labels overlap')
    need(all(boss['address']<=x<boss['address']+boss['size'] for x in opos),
         'full native case bounds outside original whole fighter')
    result=[]
    for k in range(11):
        a,b=cpos[k:k+2]
        ins=list(decoder.disasm(code[a:b],a))
        orig=native[k]
        need(ins and ins[0].address==a and ins[-1].address+ins[-1].size==b
             and len(ins)==len(orig) and sum(x.size for x in ins)==opos[k+1]-opos[k],
             f'case {k}: complete original native CODE byte/instruction span not reproduced')
        result.append(ins)
    return code,refs,inst,ret,result

def validate_case(index,native,probe,relocs,script,core,zero,one,nine,ten):
    start,end=probe[0].address,probe[-1].address+probe[-1].size
    physical=[r for r in relocs if start<=r['offset']<end]
    if index in (0,2):
        need(zero.reference_sequence(native)==zero.reference_sequence(probe,relocs),
             'original actor action0/2 genuine reset/x87 COFF roles changed')
    elif index in (1,3):
        need(one.inspect_field_grammar(native)==one.inspect_field_grammar(probe,relocs),
             'original actor action1/3 native state COFF roles changed')
    elif index in (4,5):
        need(len(native)==len(probe)==3 and len(physical)==0
             and native[1].op_str==probe[1].op_str,'original 3-insn motion literal changed')
    elif index in (6,7,8):
        need(script.verify_typed_fields(native,probe,relocs,index)==(9 if index==6 else 7),
             'native scripted-state action6/7/8 original COFF relocations changed')
    elif index==9:
        need(nine.typed_references(native)==nine.typed_references(probe,relocs),
             'original action9 true COFF x87/callback destinations changed')
    else:
        need(index==10 and ten.physical_calls(native,probe,relocs)==4,
             'native action10 20-instruction call state path differs')
    n=(9,11,9,11,0,0,9,7,7,6,4)[index]
    need(len(physical)==n,'original physical typed COFF case field count differs')
    return len(physical)

def main():
    reader=module('f566_reader',ROOT/'scripts/compare-coff-function.py')
    action=module('f566_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    opening=module('f566_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    switch=module('f566_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f566_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f566_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    core=module('f566_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    script=module('f566_script',ROOT/'scripts/verify-fighter-scripted-stage-actions.py')
    nine=module('f566_nine',ROOT/'scripts/verify-fighter-actionnine-natural-source.py')
    ten=module('f566_ten',ROOT/'scripts/verify-fighter-actionten-natural-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads(PINNED.read_text())['bosses'] if x['address']==ADDR)
    need(boss['size']==46755 and boss['postret_size']==901,
         'whole original scripted giant/switch DATA extent drift')
    report,mapped=action.report_boss(reader,pe,decoder,boss)
    source,original=make_source(reader,pe,decoder,boss,report,mapped,
                  opening,switch,zero,one,script,nine,ten)
    need(len(original)==11 and [len(x) for x in original][6:9]==[96,83,83],
         'scripted source original native action inventory wrong')
    obj=compile_one(source)
    code,refs,inst,ret,candidates=physical_cases(reader,pe,decoder,obj,boss,report,original)
    fields=0
    for index,(native,candidate) in enumerate(zip(original,candidates)):
        core.compare_grammar(native,candidate)
        need(all(x.size==y.size for x,y in zip(native,candidate)),
             'native original case instruction/branch length differs')
        fields+=validate_case(index,native,candidate,refs,script,core,zero,one,nine,ten)
    need(fields==73,'native scripted all-eleven action body must have exactly 73 real COFF fields')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,reader,
                                                   switch,inst,code,refs,ret)
    output={'boss':f'0x{ADDR:08X}','whole_original_CODE_unaccepted':boss['size'],
            'native_first_eleven_case_instructions':[len(x) for x in original],
            'native_first_eleven_case_CODE_bytes':[sum(i.size for i in x) for x in original],
            'authentic_original_case_COFF_fields':fields,
            'whole_physical_original_switch_DWORD_refs':dense,
            'original_sparse_index_bytes':sparse,
            'native_afterret_DATA_shape':len(code)-ret}
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(output,indent=2)+'\n')
    print(f'{ADDR:#010x}: one newly compiled natural VC7.1 function with 11/11 '
          f'original game actions, {sum(output["native_first_eleven_case_instructions"])} '
          f'actual x86 instructions, {sum(output["native_first_eleven_case_CODE_bytes"])} '
          f'original internal CODE bytes, {fields}/73 genuine COFF refs, '
          f'{dense} native physical switch DWORD fields, {sparse} exact sparse bytes')
    print('The original 46,755-byte giant is still NOT exact; later actions are '
          'diagnostic markers, no split CODE/DATA credit and no full cold replay')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 integrated scripted native C++ source verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
