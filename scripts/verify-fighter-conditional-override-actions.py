#!/usr/bin/env python3
"""F563: compile all native 125/127/104 and 125/115/102 actor cases.

Original whole Japanese TH075 v1.11 fighter CODE, every post-RET jump DATA
byte, physically bounded case6/7/8 ranges and all character-specific
stage/velocity/positive-flag overrides are independently PE-verified.
Generate one natural MSVC7.1 C++ source per requested boss, retaining
real cases 6/7/8 and diagnostic-only marker stores elsewhere. Inner cases
are NOT separate exact functions; never do an all-unit cold replay.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f563-conditional-override-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
BOSSES={0x004F7130:'Boss004F7130',0x005AEEC0:'Boss005AEEC0'}


def need(ok,detail):
    if not ok:raise ValueError(detail)


def module(tag,path):
    spec=importlib.util.spec_from_file_location(tag,path)
    need(spec is not None and spec.loader is not None,
         f'missing original-PE/source helper {path}')
    m=importlib.util.module_from_spec(spec);sys.modules[tag]=m;spec.loader.exec_module(m)
    return m


def float_literal(bits,core):
    """Source-level float with binary32 round-trip, never grafted machine code."""
    bits=int(bits)
    value=struct.unpack('<f',bits.to_bytes(4,'little'))[0]
    if value==0.0:
        need(bits==0,'unexpected signed-zero initialization')
        return '0.0f'
    if value.is_integer() and abs(value)<100:
        return f'{int(value)}.0f'
    if value<0:
        positive=int.from_bytes(struct.pack('<f',-value),'little')
        return '-'+core.literal_float(positive)
    return core.literal_float(bits)


def immediate(ins):
    need(ins.mnemonic=='mov' and ', ' in ins.op_str,
         'original source float field not an immediate native MOV')
    return int(ins.op_str.rsplit(', ',1)[-1],0)


def native_three(reader,pe,decoder,boss,core):
    addr=boss['address']
    need(addr in BOSSES and boss['jump_count']==7 and boss['tables'][0]['slots']==11
         and boss['tables'][0]['map_addr'] is None,
         'original target not an independently evidenced seven-switch fighter')
    raw=reader.pe_bytes_at(pe,boss['tables'][0]['dense_addr']+24,16)
    entries=[int.from_bytes(raw[k:k+4],'little') for k in (0,4,8,12)]
    need(entries==sorted(set(entries)) and
         all(addr<=v<addr+boss['size'] for v in entries),
         'full original game switch cases 6/7/8 physical boundaries invalid')
    expected=([125,127,104] if addr==0x004F7130 else [125,115,102])
    real=[]
    for index,want in enumerate(expected):
        a,b=entries[index:index+2]
        ins=list(decoder.disasm(reader.pe_bytes_at(pe,a,b-a),a))
        want_bytes=([441,451,362] if addr==0x004F7130 else [441,393,352])[index]
        need(len(ins)==want and b-a==want_bytes and
             ins[0].address==a and ins[-1].address+ins[-1].size==b,
             f'{addr:08X}: complete native action {6+index} instruction/byte extent differs')
        need(ins[10].mnemonic=='cmp' and
             ins[10].op_str.endswith(', '+str((3,5,4)[index]))
             and ins[16].mnemonic=='push' and
             ins[16].op_str==('0xcc','0xcd','0xce')[index],
             f'{addr:08X}: native first signed state or real callback argument changed')
        calls=[(j,x.op_str) for j,x in enumerate(ins) if x.mnemonic=='call' and
               x.op_str.startswith('0x')]
        expected_calls=[(18,'0x40fac0'),(29,'0x453e20'),
                        (52,'0x40fac0'),(56,'0x453e20')]
        if index<2:expected_calls.append((70,'0x40fb40'))
        need(calls==expected_calls and
             ins[-2].mnemonic=='call' and ins[-2].op_str=='dword ptr [edx]',
             f'{addr:08X}: actual original real-call/virtual-call roles changed')
        if index<2:
            need(ins[60].mnemonic=='cmp' and ins[60].op_str.endswith(', 4')
                 and ins[64].mnemonic=='fcomp' and
                 ins[64].op_str=='dword ptr [0x657d14]'
                 and ins[68].mnemonic=='push' and ins[68].op_str=='5',
                 'native four-stage float extra-state condition not observed')
        stage_idx=91 if index<2 else 78
        need(ins[stage_idx].mnemonic=='cmp' and
             ins[stage_idx].op_str.endswith(', 2'),
             'original stage-two actor source threshold changed')
        real.append(ins)
    def three(ins,ordinal):
        return [float_literal(immediate(ins[k]),core) for k in ordinal]
    original_stage=three(real[0],(94,96,98))
    first_alt=three(real[0],(104,106,108))
    primary7=three(real[1],(94,96,98))
    second_alt=(three(real[1],(104,106,108)) if len(real[1])==127 else None)
    native8=real[2]
    final8=three(native8,(81,85,87) if len(native8)==104 else (81,83,85))
    need(original_stage[0]=='0.0f'
         and [original_stage[1],original_stage[2]]==([ '13.0f','0.4f'] if addr==0x004F7130
                                                   else ['16.0f','0.75f']),
         'native primary fighter stage/velocity/speed differs from observed original')
    if addr==0x004F7130:
        need(first_alt==['2.0f','10.0f','0.25f'] and
             primary7==['3.0f','13.0f','0.4f'] and
             second_alt==['4.5f','10.0f','0.25f'] and
             final8==['-4.0f','13.0f','0.4f'],
             'native fighter first two conditional motion overrides changed')
        need(real[0][100].mnemonic=='movsx' and real[0][101].mnemonic=='test'
             and real[0][102].mnemonic=='jle' and
             real[1][100].mnemonic=='movsx' and real[1][102].mnemonic=='jle',
             'original positive-FLAG motion override branch changed')
        need(real[1][110].mnemonic=='mov' and
             real[1][110].op_str.endswith(', 0') and '+ 0x3ac]' in real[1][110].op_str,
             'native case7 conditional flag-clear after override missing')
        need(native8[83].mnemonic=='mov' and
             '+ 0x3ac]' in native8[83].op_str and native8[83].op_str.endswith(', 0'),
             'original case8 requires position-flag-velocity store order')
    else:
        need(first_alt==['3.0f','15.0f','1.25f'] and
             primary7==['8.0f','16.0f','0.75f'] and second_alt is None and
             final8==['-8.0f','16.0f','0.75f'],
             'native fighter extra motion state float immediates changed')
        need(real[0][100].mnemonic=='movsx' and real[0][102].mnemonic=='jle'
             and not any('+ 0x3ac]' in x.op_str and x.mnemonic=='mov'
                         for block in real for x in block),
             'original case7/8 flag clear unexpectedly present in 71K actor')
    return real, dict(primary=original_stage,override6=first_alt,
                      primary7=primary7,override7=second_alt,primary8=final8,
                      original_flag_clear=(addr==0x004F7130))


def source_for(tag,context,native_report,mapped,boss,reader,pe,decoder,
               core,opening,switch,zero,one):
    stage_vel,stage_speed=context['primary'][1:]
    src=core.generate_source(tag,2,[stage_vel,stage_speed],native_report,mapped,
                             opening,switch,zero,one,reader,pe,decoder,boss)
    case6_name='case 0x6:'
    marker7='case 0x7: g_FighterProbeMarker = 8; break;'
    marker8='case 0x8: g_FighterProbeMarker = 9; break;'
    need(all(src.count(mark)==1 for mark in (case6_name,marker7,marker8)),
         'native source generator lost unique original first action labels')
    normal=src[src.index(case6_name):src.index(marker7)]
    need(normal.count('                    FLAG = 0;')==1 and
         normal.count('U8(0x511) == 3')==1 and
         normal.count('SetNativeActionAt40FAC0(0xCC)')==1,
         'previous native-sourced core has unexpected action6 literals or assignments')
    regular=normal.replace('                    FLAG = 0;\n','')
    extra='''            if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(5);
'''
    count='            ++S16(0x64);'
    need(regular.count(count)==1,'previous verified native frame increment moved')
    regular=regular.replace(count,extra+count)
    pri=context['primary'];secondary=context['override6']
    original='''                    POS = 0.0f;
                    POS54 = '''+pri[1]+''';
                    POS5C = '''+pri[2]+''';'''
    need(regular.count(original)==1,'native original first stage motion stores missing')
    def alternate(values,clear):
        return '''                    if (FLAG > 0) {
                        POS = '''+values[0]+''';
                        POS54 = '''+values[1]+''';
                        POS5C = '''+values[2]+''';'''+(
                  '''
                        FLAG = 0;''' if clear else '')+'''
                    }'''
    case6=regular.replace(original,original+'\n'+alternate(secondary,False))
    case7=(regular.replace('case 0x6:','case 0x7:',1)
            .replace('U8(0x511) == 3','U8(0x511) == 5')
            .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCD)')
            .replace('POS = 0.0f;',f'POS = {context["primary7"][0]};'))
    if context['override7'] is not None:
        first='''                    POS = '''+context['primary7'][0]+''';
                    POS54 = '''+stage_vel+''';
                    POS5C = '''+stage_speed+''';'''
        need(case7.count(first)==1,'native case7 first primary motion writes changed')
        case7=case7.replace(first,first+'\n'+alternate(context['override7'],True))
    case8=(normal.replace('case 0x6:','case 0x8:',1)
            .replace('U8(0x511) == 3','U8(0x511) == 4')
            .replace('SetNativeActionAt40FAC0(0xCC)','SetNativeActionAt40FAC0(0xCE)')
            .replace('POS = 0.0f;',f'POS = {context["primary8"][0]};'))
    if context['original_flag_clear']:
        before='''                    POS = -4.0f;
                    POS54 = '''+stage_vel+''';
                    POS5C = '''+stage_speed+''';
                    FLAG = 0;'''
        after='''                    POS = -4.0f;
                    FLAG = 0;
                    POS54 = '''+stage_vel+''';
                    POS5C = '''+stage_speed+''';'''
        need(case8.count(before)==1,'original case8 FLAG store order missing')
        case8=case8.replace(before,after)
    else:
        need(case8.count('                    FLAG = 0;')==1,
             'original case8 omit-FLAG source not unique')
        case8=case8.replace('                    FLAG = 0;\n','')
    first=src[:src.index(case6_name)]
    tail=src[src.index(marker7)+len(marker7):]
    need(tail.count(marker8)==1,'unreconstructed case8 marker lost')
    tail=tail.replace(marker8,'')
    combined=first+case6+case7.rstrip()+'\n'+case8.rstrip()+tail
    method='void SetNativeActionAt40FAC0(int);'
    field='extern float g_ThresholdAt0065782C;'
    need(combined.count(method)==combined.count(field)==1,
         'prior fighter C++ source ABI/float declaration changed')
    combined=combined.replace(method,method+' void SetAuxActionAt40FB40(int);')
    combined=combined.replace(field,field+'\nextern float g_ExtraThresholdAt00657D14;')
    owner=f'FighterSwitchF548_{tag}'
    need(combined.count(owner)>=2,'borrowed fighter source interface missing')
    combined=combined.replace(owner,f'FighterSwitchF563_{tag}')
    need(all(combined.count(f'case 0x{i:X}:')==1 for i in (6,7,8)),
         'original C++ switch case labels accidentally duplicated')
    return combined


def compile_one(tag,src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}-three-cases.cpp'
    obj=OUT/f'{tag}-three-cases.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                        cwd=ROOT,env=env,text=True,capture_output=True,timeout=120)
    (OUT/f'{tag}-compile.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'{tag}: new selected MSVC7.1 TU failed: {proc.stderr}')
    return obj


def candidate_three(reader,decoder,obj,tag,boss,real):
    code,relocs=reader.object_function(obj,f'?Advance@FighterSwitchF563_{tag}@@QAEXXZ')
    whole=[]
    for i in decoder.disasm(code,0):
        whole.append(i)
        if i.mnemonic=='ret':break
    need(whole and whole[-1].mnemonic=='ret','normal candidate source RET missing')
    postret=whole[-1].address+whole[-1].size
    need(len(code)-postret==boss['postret_size'],
         f'{tag}: complete physical original switch DATA size differs')
    rows=sorted((r for r in relocs if postret+24<=r['offset']<postret+40),
                key=lambda r:r['offset'])
    need(len(rows)==4 and all(r['type']=='DIR32' and r['offset']==postret+24+i*4
              and r['local_symbol_offset'] is not None for i,r in enumerate(rows)),
         f'{tag}: generated real first-table four physical COFF jump destinations missing')
    places=[r['local_symbol_offset'] for r in rows]
    need(places==sorted(set(places)) and 0<=places[0]<places[-1]<postret,
         'original case6/7/8 code labels overlap or exceed CODE')
    generated=[]
    for k,original in enumerate(real):
        start,end=places[k:k+2]
        ins=list(decoder.disasm(code[start:end],start))
        need(len(ins)==len(original) and sum(i.size for i in ins)==sum(i.size for i in original),
             f'{tag}: complete original case {6+k} CODE geometry does not match source')
        generated.append(ins)
    return code,relocs,whole,postret,generated


def verify_typed_fields(native,compiled,refs,action,core,extra):
    expected=(extra.REAL_REFS if action in (6,7) else
              {i:(kind,addr,sym) for i,(_,kind,addr,sym) in core.ORIGINAL_REFS.items()})
    start,end=compiled[0].address,compiled[-1].address+compiled[-1].size
    physical=[r for r in refs if start<=r['offset']<end]
    need(len(physical)==len(expected),
         'candidate has extra or missing actual native COFF call/global refs')
    for ordinal,(kind,address,symbol) in expected.items():
        orig,generated=native[ordinal],compiled[ordinal]
        need(orig.mnemonic==generated.mnemonic==('call' if kind=='REL32' else 'fcomp'),
             'source/native COFF ordinal changed')
        real_dest=(f'0x{address:x}' if kind=='REL32' else f'dword ptr [0x{address:x}]')
        need(orig.op_str==real_dest,'original PE callee/global destination differs')
        loc=[r for r in physical if generated.address<=r['offset']<generated.address+generated.size]
        need(len(loc)==1 and loc[0]['type']==kind and symbol in loc[0]['symbol'],
             'compiler emitted a wrong physical native call/global COFF symbol/type')
    need(native[-2].mnemonic==compiled[-2].mnemonic=='call' and
         native[-2].op_str==compiled[-2].op_str=='dword ptr [edx]',
         'per-fighter original physical virtual frame call differs')
    return len(physical)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='Original PE address 0x004F7130/0x005AEEC0; default both')
    args=parser.parse_args()
    reader=module('f563_reader',ROOT/'scripts/compare-coff-function.py')
    action=module('f563_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    core=module('f563_core',ROOT/'scripts/verify-fighter-action-six-natural-source.py')
    extra=module('f563_extra',ROOT/'scripts/verify-fighter-extra-stage-action-source.py')
    opening=module('f563_opening',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    switch=module('f563_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f563_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f563_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    manifest={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    need(sum(manifest[addr]['size'] for addr in BOSSES)==115827,
         'original whole giant source-cohort CODE extents drifted')
    selected=list(BOSSES)
    if args.boss:
        target=int(args.boss,0)
        need(target in BOSSES,'original fighter not one of the new conditional-override cohort')
        selected=[target]
    results=[]
    for address in selected:
        boss=manifest[address];tag=BOSSES[address]
        report,mapped=action.report_boss(reader,pe,decoder,boss)
        real,params=native_three(reader,pe,decoder,boss,core)
        cpp=source_for(tag,params,report,mapped,boss,reader,pe,decoder,
                       core,opening,switch,zero,one)
        obj=compile_one(tag,cpp)
        code,refs,whole,ret,candidates=candidate_three(reader,decoder,obj,tag,boss,real)
        actual_relocs=0
        for i,(orig,compiled) in enumerate(zip(real,candidates)):
            core.compare_grammar(orig,compiled)
            need(all(x.size==y.size for x,y in zip(orig,compiled)),
                 f'{address:08X}: real native per-instruction x86 length differs at case {6+i}')
            actual_relocs+=verify_typed_fields(orig,compiled,refs,6+i,core,extra)
        need(actual_relocs==22,f'{address:08X}: original six/seven/eight need 8+8+6 physical refs')
        dense,sparse,_=zero.verify_physical_tables(boss,report,pe,reader,switch,
                                                   whole,code,refs,ret)
        row={'boss':f'0x{address:08X}','whole_original_CODE':boss['size'],
             'native_case_instructions':[len(x) for x in real],
             'native_case_CODE_bytes':[sum(y.size for y in x) for x in real],
             'authentic_case_COFF_call_and_global_fields':actual_relocs,
             'original_stage2_motion':params['primary'],
             'positive_FLAG_case6_override':params['override6'],
             'original_case7_motion':params['primary7'],
             'positive_FLAG_case7_override':params['override7'],
             'original_case8_motion':params['primary8'],
             'case7_positive_FLAG_cleared':params['override7'] is not None,
             'physical_original_switch_DWORD_COFF_fields':dense,
             'literal_original_sparse_index_bytes':sparse,
             'whole_original_afterret_DATA_shape':len(code)-ret}
        results.append(row)
        print(f'{address:#010x}: whole original {boss["size"]:,} CODE, '
              f'case6/7/8 native {row["native_case_instructions"]} instructions / '
              f'{row["native_case_CODE_bytes"]} bytes; 22/22 authentic typed COFF fields, '
              f'{dense} native switch table DWORD ref fields, {sparse} identical sparse bytes; '
              f'positive FLAG alters primary motion {params["override6"]}',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    summary='summary.json' if args.boss is None else f'summary-{selected[0]:08X}.json'
    (OUT/summary).write_text(json.dumps(results,indent=2)+'\n')
    print(f'{len(results)}/{len(selected)} whole native fighter contexts compiled in affected-only MSVC7.1 TUs; '
          'zero exact full giant/subfunction CODE/DATA credit; no all-unit cold replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('TH075 original conditional-override native source verifier failed:',e,file=sys.stderr)
        raise SystemExit(1)
