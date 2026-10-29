#!/usr/bin/env python3
"""F567: integrated genuine action 0..10 VC7.1 source in eight more giant fighters.

Together with F564 (two) and F566 (one), this covers all eleven original
multi-switch giant fighter *opening action* C++ source families. Every
original entire SHA-pinned fighter CODE and all post-RET jump DATA are
checked before compiling one new selected natural C++ TU. Each entire
original physical action case is checked for strict GPR/x87/control
grammar, COFF call/global typed ref identity and original source frame
width. All other cases remain diagnostic marker stores, NOT restored
whole function. NO exact split/whole CODE credit and NO all-unit replay.
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
OUT=ROOT/'.analysis/f567-all-integrated-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
BOSSES={0x0045DD70:'f553',0x0058AF60:'f553',0x005D73C0:'f553',
        0x00486550:'f558',0x004AC040:'f558',
        0x00543210:'f560',0x00564BE0:'f559',0x004D7E70:'f562'}
NAMES={0x0045DD70:'Reimu',0x004AC040:'CharacterMove'}
KNOWN_COFS={
  0x0040FAC0:('REL32','SetNativeActionAt40FAC0'),
  0x00453E20:('REL32','ResetAt453E20'),
  0x0040FB40:('REL32','SetAuxActionAt40FB40'),
  0x0065782C:('DIR32','g_ThresholdAt0065782C'),
  0x00657D14:('DIR32','g_ExtraThresholdAt00657D14'),
}

def need(ok,why):
    if not ok:raise ValueError(why)

def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,f'missing native helper {path}')
    obj=importlib.util.module_from_spec(spec)
    sys.modules[tag]=obj
    spec.loader.exec_module(obj)
    return obj

def helpers():
    prefix=ROOT/'scripts'
    filenames={
       'reader':'compare-coff-function.py',
       'actions':'report-fighter-action-handlers.py',
       'switch':'verify-fighter-natural-switch-probes.py',
       'zero':'verify-fighter-actionzero-natural-source.py',
       'one':'verify-fighter-actionone-natural-source.py',
       'opening':'verify-fighter-opening-actions-natural-source.py',
       'core':'verify-fighter-action-six-natural-source.py',
       'f551':'verify-fighter-action-seven-natural-source.py',
       'f553':'verify-fighter-action-eight-natural-source.py',
       'f556':'verify-fighter-extra-stage-action-source.py',
       'f558':'verify-fighter-extra-stage-action-eight.py',
       'stage':'verify-fighter-stage-no-flag-source.py',
       'f559':'verify-fighter-wide-action-eight-source.py',
       'f560':'verify-fighter-precontact-stage-action-eight.py',
       'f562':'verify-fighter-split-stage-4d7e70.py',
       'nine':'verify-fighter-actionnine-natural-source.py',
       'ten':'verify-fighter-actionten-natural-source.py',
    }
    return {tag:module('f567_'+tag,prefix/filename)
            for tag,filename in filenames.items()}

def actual_case_source(address,boss,report,mapped,reader,pe,dec,h):
    """Regenerate cases 0..8 from original PE, not ignored prior C++ dumps."""
    tag=NAMES.get(address,f'Boss{address:08X}')
    s=h['switch'];z=h['zero'];o=h['one'];opening=h['opening'];core=h['core']
    family=BOSSES[address]
    if family=='f553':
        n6,stage,floats=core.native_case(reader,pe,dec,boss)
        n7,pos=h['f551'].native_seven(reader,pe,dec,boss,n6)
        n8,omit=h['f553'].real_eight(reader,pe,dec,boss)
        first=core.generate_source(tag,stage,floats,report,mapped,opening,
                                   s,z,o,reader,pe,dec,boss)
        second,_=h['f551'].generate_source(tag,first,n7,pos,core)
        src=h['f553'].create_source(tag,second,n8,omit,core)
        original_type=f'FighterSwitchF553_{tag}'
    elif family=='f558':
        old=h['f556']
        pair=[old.native_case(reader,pe,dec,boss,k,core) for k in (6,7)]
        n8,order,floats=h['f558'].original_eight(reader,pe,dec,boss,core,pair[0])
        src=h['f558'].generate_source(tag,report,mapped,pair,n8,order,
                 reader,pe,dec,boss,old,core,opening,s,z,o)
        original_type=f'FighterSwitchF558_{tag}'
    elif family in ('f559','f560'):
        old=h['stage']
        real6=old.original_case(reader,pe,dec,boss,6,core)
        real7=old.original_case(reader,pe,dec,boss,7,core)
        if family=='f559':
            h['f559'].original_eight(reader,pe,dec,boss,core)
            src=h['f559'].source_for(real6,real7,report,mapped,
                        reader,pe,dec,boss,old,core,opening,s,z,o)
            original_type=f'FighterSwitchF559_{tag}'
        else:
            h['f560'].original_eight(reader,pe,dec,boss,core)
            context={'native_report':report,'mapped':mapped,'reader':reader,
                     'pe':pe,'decoder':dec,'boss':boss,'source6':core,
                     'opening':opening,'switch':s,'zero':z,'one':o}
            src=h['f560'].generate_source(old,real6,real7,context)
            original_type=f'FighterSwitchF560_{tag}'
    elif family=='f562':
        real=h['f562'].native_cases(reader,pe,dec,boss,core)
        src=h['f562'].source_for(core,opening,s,z,o,
                  reader,pe,dec,boss,report,mapped,real)
        original_type=f'FighterSwitchF562_{tag}'
    else:
        raise ValueError('unregistered original fighter family')
    need(src.count(original_type)>=2,
         f'{tag}: actual original actor class source interface missing')
    return src,original_type

def compose_source(address,boss,report,mapped,reader,pe,dec,h):
    tag=NAMES.get(address,f'Boss{address:08X}')
    src,oldname=actual_case_source(address,boss,report,mapped,reader,pe,dec,h)
    native9=h['nine'].native_case(reader,pe,dec,boss)
    original10,low,high,prepare=h['ten'].native_ten(reader,pe,dec,boss,report)
    other,count,aux=h['ten'].source_ten(h['nine'],tag,report,mapped,native9,
            reader,pe,dec,boss,h['opening'],h['switch'],h['zero'],h['one'],
            low,high,prepare)
    p9,p10,p32=(other.index('case 0x9:'),other.index('case 0xA:'),
                other.index('case 0x32:'))
    need(p9<p10<p32,f'{tag}: actual source cases9/10 not physically bounded')
    for k,body in ((9,other[p9:p10].rstrip()),
                   (10,other[p10:p32].rstrip())):
        marker=f'case 0x{k:X}: g_FighterProbeMarker = {k+1}; break;'
        need(src.count(marker)==1,f'{tag}: original case{k} C++ label missing')
        src=src.replace(marker,body)
    if 'void SetAuxActionAt40FB40(int);' not in src:
        decl='void SetNativeActionAt40FAC0(int);'
        need(src.count(decl)==1,'true auxiliary thiscall source requires actual method')
        src=src.replace(decl,decl+' void SetAuxActionAt40FB40(int);')
    decl='void ResetAt453E20();'
    need(src.count(decl)==1,'native state reset source declaration missing')
    src=src.replace(decl,decl+' void PrepareActionAt453D60(int);')
    macro='#define I16(off)'
    need(src.count(macro)==1,'native signed-short owner field missing')
    src=src.replace(macro,
          '#define I32(off) *reinterpret_cast<int*>(RAW+(off))\n'+macro)
    src=src.replace(oldname,f'FighterSwitchF567_{tag}')
    need(all(src.count(f'case 0x{k:X}:')==1 for k in range(11)),
         'integrated native C++ contains missing/duplicated action labels')
    need('SetAuxActionAt40FB40' in src and
         ('PrepareActionAt453D60(30);' in src)==prepare,
         'real per-fighter prepare/auxiliary native call source differs')
    return src

def compile_one(tag,src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}-integrated-eleven.cpp'
    obj=OUT/f'{tag}-integrated-eleven.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),
         str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/f'{tag}-compile.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'{tag}: fresh VC7.1 source compile failed: {proc.stderr}')
    return obj

def case_boundaries(reader,pe,dec,boss,report,code,refs):
    ins=[]
    for i in dec.disasm(code,0):
        ins.append(i)
        if i.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret','generated natural C++ no normal RET')
    end=ins[-1].address+ins[-1].size
    need(len(code)-end==boss['postret_size'],
         'whole native original after-RET CODE/DATA boundary differs')
    table=boss['tables'][0]
    need(table['slots']==11 and table['map_addr'] is None,
         'not the real first 11-slot direct fighter switch')
    original=[int.from_bytes(reader.pe_bytes_at(pe,table['dense_addr']+4*k,4),'little')
              for k in range(11)]
    actual_end=[int(x['handler'],16) for x in report['singleton_branches']
                if x['action']==50]
    need(len(actual_end)==1,'original separate action0x32 singleton not verified')
    original+=actual_end
    physical=sorted((r for r in refs if end<=r['offset']<end+44),
                    key=lambda r:r['offset'])
    need(len(physical)==11 and all(r['type']=='DIR32'
         and r['offset']==end+4*k and r['local_symbol_offset'] is not None
         for k,r in enumerate(physical)),
         'new C++ does not emit eleven genuine physical COFF case pointers')
    candidate=[r['local_symbol_offset'] for r in physical]
    singleton=[int(ins[i+1].op_str,16) for i in range(len(ins)-1)
               if ins[i].mnemonic=='cmp' and
               ins[i].op_str.endswith(', 0x32') and
               ins[i+1].mnemonic=='je' and ins[i+1].op_str.startswith('0x')]
    need(len(singleton)==1,'native original actor singleton action50 missing')
    candidate+=singleton
    need(original==sorted(set(original)) and
         candidate==sorted(set(candidate)) and
         all(boss['address']<=x<boss['address']+boss['size'] for x in original),
         'case bounds alias outside actual original whole native function')
    return ins,end,original,candidate

def typed_fields(native,candidate,refs,action,h):
    first,last=candidate[0].address,candidate[-1].address+candidate[-1].size
    actual=[r for r in refs if first<=r['offset']<last]
    if action in (0,2):
        need(h['zero'].reference_sequence(native)==
             h['zero'].reference_sequence(candidate,refs),
             'native action0/2 typed x87/Reset physical refs differ')
    elif action in (1,3):
        need(h['one'].inspect_field_grammar(native)==
             h['one'].inspect_field_grammar(candidate,refs),
             'native action1/3 typed x87/Reset physical refs differ')
    elif action in (4,5):
        need(len(native)==len(candidate)==3 and len(actual)==0
             and native[1].op_str==candidate[1].op_str,
             'original three-insn literal motion assignment changed')
    elif action in (6,7,8):
        entries=[]
        for ordinal,x in enumerate(native):
            if x.mnemonic=='call' and x.op_str.startswith('0x'):
                address=int(x.op_str,16)
            elif x.mnemonic=='fcomp' and x.op_str.startswith('dword ptr [0x'):
                address=int(x.op_str.split('[',1)[1].split(']',1)[0],16)
            else:continue
            need(address in KNOWN_COFS,
                 f'new previously unmodeled actual fighter COFF ref {address:x}')
            typ,symbol=KNOWN_COFS[address]
            c=candidate[ordinal]
            need(x.mnemonic==c.mnemonic,
                 f'native case {action} original COFF instruction moved')
            physical=[r for r in actual if c.address<=r['offset']<c.address+c.size]
            need(len(physical)==1 and physical[0]['type']==typ
                 and symbol in physical[0]['symbol'],
                 f'native case {action} actual COFF symbol/kind/ordinal changed')
            entries.append((ordinal,typ,address))
        need(len(entries)==len(actual) and len(entries) in (6,8),
             'native case6/7/8 added or omitted physical COFF fields')
        need(native[-2].mnemonic==candidate[-2].mnemonic=='call'
             and native[-2].op_str==candidate[-2].op_str
             and native[-2].op_str.startswith('dword ptr ['),
             'native original actor vtable call/receiver register differs')
    elif action==9:
        need(h['nine'].typed_references(native)==
             h['nine'].typed_references(candidate,refs),
             'native action9 typed physical original call/x87 fields wrong')
    elif action==10:
        expected=4 if len(native)==20 else 5
        need(h['ten'].physical_calls(native,candidate,refs)==expected,
             'actual native action10 state-method COFF target differs')
    return len(actual)

def native_size_encoding(original,generated,wide):
    need(len(original)==len(generated),'native original case truncated')
    diffs=[(n,c,n.size-c.size) for n,c in zip(original,generated)
           if n.size!=c.size]
    if not wide:
        need(not diffs,'nonwide original native case/source byte sizes differ')
        return (0,0,0)
    widened=[x for x in diffs if x[2]==3 and x[0].mnemonic=='mov'
             and '[ebp - 0x88]' in x[0].op_str]
    longjl=[x for x in diffs if x[2]==4 and
            x[0].mnemonic==x[1].mnemonic=='jl']
    need(len(widened)+len(longjl)==len(diffs),
         'wide-frame native EBP/long-branch byte explanation incomplete')
    return (len(widened),len(longjl),sum(d[2] for d in diffs))

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='One original PE address from eight remaining multi-switch giants; default all')
    options=parser.parse_args()
    h=helpers()
    m=h['reader']
    pe=m.verified_target()
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    whole={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    need(sum(whole[b]['size'] for b in BOSSES)==450809,
         'native original eight giant CODE SHA cohort sizes drifted')
    selected=list(BOSSES)
    if options.boss:
        requested=int(options.boss,0)
        need(requested in BOSSES,'not one of the eight unintegrated fighter originals')
        selected=[requested]
    results=[]
    for address in selected:
        boss=whole[address]
        tag=NAMES.get(address,f'Boss{address:08X}')
        report,mapped=h['actions'].report_boss(m,pe,dec,boss)
        source=compose_source(address,boss,report,mapped,m,pe,dec,h)
        obj=compile_one(tag,source)
        code,refs=m.object_function(obj,f'?Advance@FighterSwitchF567_{tag}@@QAEXXZ')
        wholeins,ret,starts,offsets=case_boundaries(m,pe,dec,boss,report,code,refs)
        count=0;bytes_=0;typed=0;wide_reads=0;long_jl=0;extra_bytes=0
        origsizes=[];cand_sizes=[];casecounts=[];casefields=[]
        for k in range(11):
            a,b=starts[k:k+2]
            native=list(dec.disasm(m.pe_bytes_at(pe,a,b-a),a))
            start,finish=offsets[k:k+2]
            generated=list(dec.disasm(code[start:finish],start))
            need(native and generated and
                 native[0].address==a and
                 native[-1].address+native[-1].size==b and
                 generated[0].address==start and
                 generated[-1].address+generated[-1].size==finish,
                 'native original/compiled complete inner case boundaries invalid')
            h['core'].compare_grammar(native,generated)
            r,j,extra=native_size_encoding(native,generated,address==0x00564BE0)
            wide_reads+=r;long_jl+=j;extra_bytes+=extra
            nfields=typed_fields(native,generated,refs,k,h)
            count+=len(native);bytes_+=b-a;typed+=nfields
            origsizes.append(b-a);cand_sizes.append(finish-start)
            casecounts.append(len(native));casefields.append(nfields)
            print(f'{address:#010x} case{k}: {len(native)}/{len(generated)} '
                  f'native GPR/x87/control instructions, {b-a}/{finish-start} '
                  f'original/probe bytes, {nfields} actual COFF fields, '
                  f'width extra {extra}',flush=True)
        if address==0x00564BE0:
            need((wide_reads,long_jl,extra_bytes)==(191,3,585),
                 'wide 00564BE0 original byte expansion not fully accounted')
        else:
            need((wide_reads,long_jl,extra_bytes)==(0,0,0),
                 'unexpected physical encoding drift for regular actor frame')
        dense,sparse,maps=h['zero'].verify_physical_tables(
                           boss,report,pe,m,h['switch'],wholeins,code,refs,ret)
        results.append({'boss':f'0x{address:08X}',
                 'family':BOSSES[address],
                 'whole_original_CODE_unaccepted':boss['size'],
                 'complete_first_eleven_original_instructions':casecounts,
                 'complete_original_inner_CODE_bytes':origsizes,
                 'candidate_inner_CODE_bytes':cand_sizes,
                 'native_typed_case_COFF_fields':casefields,
                 'total_actual_COFF_fields':typed,
                 'original_wide_EBP_loads':wide_reads,
                 'extra_original_near_JL':long_jl,
                 'total_explained_native_width_extra_bytes':extra_bytes,
                 'complete_original_switch_DWORD_COFF_fields':dense,
                 'byte_identical_native_sparse_index_bytes':sparse,
                 'separate_original_afterret_DATA_shape':len(code)-ret})
        print(f'WHOLE ORIGINAL {address:#010x} {boss["size"]:,} CODE: '
              f'11 genuine case source bodies, {count} native instructions, '
              f'{bytes_} original inner CODE bytes, {typed} physical COFF refs; '
              f'{dense} whole jump-table DWORD refs and {sparse} original sparse bytes; '
              f'GIANT STILL NONEXACT',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    filename='summary.json' if options.boss is None else f'summary-{selected[0]:08X}.json'
    (OUT/filename).write_text(json.dumps(results,indent=2)+'\n')
    print(f'{len(results)}/{len(selected)} original giant contexts integrated in '
          'new separate native VC7.1 source TUs; no whole/split exact '
          'CODE/DATA or all-unit cold replay')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 eight giant integrated native source check failed:',exc,file=sys.stderr)
        raise SystemExit(1)
