#!/usr/bin/env python3
"""Reproduce actual 104-insn action-six C++ in three original huge fighters.

The entire native 43K-61K boss SHA, all original jump-table targets and
post-RET sparse bytes are checked before fresh VC7.1 serial compilation of
only the affected natural C++ diagnostic source TU. No cropped function is
accepted as exact CODE; no all-unit cold replay and no fake native padding.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f548-action-six-source'
PINNED=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
SELECTED={0x0045DD70:'Reimu',0x0058AF60:'Boss0058AF60',0x005D73C0:'Boss005D73C0'}
SLOT_RE=re.compile(r'\[ebp - (?:0x[0-9a-f]+|[0-9]+)\]')
DIRECT_RE=re.compile(r'0x[0-9a-f]+')
X87_ABS_RE=re.compile(r'\[(?:0x[0-9a-f]+|0)\]')
ORIGINAL_REFS={18:('call','REL32',0x0040FAC0,'SetNativeActionAt40FAC0'),
               29:('call','REL32',0x00453E20,'ResetAt453E20'),
               32:('fcomp','DIR32',0x0065782C,'g_ThresholdAt0065782C'),
               46:('fcomp','DIR32',0x0065782C,'g_ThresholdAt0065782C'),
               52:('call','REL32',0x0040FAC0,'SetNativeActionAt40FAC0'),
               56:('call','REL32',0x00453E20,'ResetAt453E20')}


def require(condition,detail):
    if not condition: raise ValueError(detail)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    require(spec is not None and spec.loader is not None,f'missing project tool: {path}')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def literal_float(native_field):
    """Meaningful real C++ float literal, not a target DWORD byte graft."""
    x=struct.unpack('<f',native_field.to_bytes(4,'little'))[0]
    require(x > 0 and x < 32,'unexpected original positive frame float')
    for digit in range(1,10):
        text=format(x,f'.{digit}g')
        if struct.unpack('<I',struct.pack('<f',float(text)))[0]==native_field:
            if '.' not in text and 'e' not in text.lower():text+='.0'
            return text+'f'
    raise ValueError('native float requires unexplained original literal precision')


def native_case(reader,target,decoder,boss):
    tab=boss['tables'][0]
    require(tab['slots']==11 and tab['map_addr'] is None and boss['jump_count'] in (6,7),
            'not a pinned original giant multi-table first switch')
    original=reader.pe_bytes_at(target,tab['dense_addr']+24,8)
    start,end=[int.from_bytes(original[k:k+4],'little') for k in (0,4)]
    require(boss['address']<start<end<boss['address']+boss['size'],
            'action-six owned original function boundaries invalid')
    instructions=list(decoder.disasm(reader.pe_bytes_at(target,start,end-start),start))
    require(len(instructions)==104 and instructions[0].address==start and
            instructions[-1].address+instructions[-1].size==end and end-start==362,
            'not the complete native 362-byte/104-insn action-six case')
    require(instructions[10].mnemonic=='cmp' and instructions[10].op_str.endswith(', 3')
            and instructions[16].mnemonic=='push' and instructions[16].op_str=='0xcc',
            'original first-state policy native guard/0xCC call argument changed')
    require(instructions[78].mnemonic=='cmp', 'original second-state threshold changed')
    stage=int(instructions[78].op_str.split(', ')[-1],0)
    require(stage in (2,4),'unrecognized real stage-two/four threshold')
    require(instructions[83].mnemonic==instructions[85].mnemonic=='mov',
            'original native action-six real float initializations absent')
    values=[]
    for index,off in ((83,'0x54'),(85,'0x5c')):
        x=instructions[index].op_str
        require(f' + {off}]' in x,'original action-six writes wrong real float field')
        literal=int(x.split(', ')[-1],16)
        values.append(literal_float(literal))
    require(instructions[102].mnemonic=='call' and
            instructions[102].op_str in ('dword ptr [eax]','dword ptr [edx]'),
            'actual original action-six virtual dispatch instruction missing')
    return instructions,stage,values


def generate_source(tag,stage,floats,real_report,mapped,six,switch,zero,one,reader,target,decoder,boss):
    first=six.native_six(reader,target,decoder,boss)
    source,_,_=six.source_for(switch,zero,one,real_report,mapped,tag,first)
    original=f'FighterSwitchF545_{tag}'
    require(source.count(original)>=2, 'existing six-case native C++ owner changed')
    source=source.replace(f'class {original} {{ public:',
                          'class FighterSwitchF548_'+tag+' { public: virtual void NativeVirtualFrameAdvance();')
    source=source.replace(original,'FighterSwitchF548_'+tag)
    anchor='#define POS (*reinterpret_cast<float*>(RAW+0x50))'
    require(source.count(anchor)==1,'genuine float member +0x50 absent')
    source=source.replace(anchor,anchor+'''
#define POS48 *reinterpret_cast<float*>(RAW+0x48)
#define POS54 *reinterpret_cast<float*>(RAW+0x54)
#define POS5C *reinterpret_cast<float*>(RAW+0x5C)
#define S16(off) (*reinterpret_cast<signed short*>(RAW+(off)))
#define U8(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))''')
    original_case='case 0x6: g_FighterProbeMarker = 7; break;'
    require(source.count(original_case)==1, 'missing native action six label')
    # Natural unparenthesized x87 field lvalues and genuine source-level
    # increment operations deliberately preserve the original VC7.1 order.
    body='''case 0x6:
            if (S16(0x62) == 0 && S16(0x64) == 0 &&
                    (U8(0x511) == 3 || FLAG > 0)) {
                SetNativeActionAt40FAC0(0xCC);
                return;
            }
            if (S16(0x62) == 0 && FLAG == 0)
                ResetAt453E20();
            if (POS48 > g_ThresholdAt0065782C) {
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }
            }
            ++S16(0x64);
            if (S16(0x64) >= S16(0x72)) {
                S16(0x64) = 0;
                ++S16(0x62);
                if (S16(0x62) == NATIVE_STAGE) {
                    POS = 0.0f;
                    POS54 = NATIVE_POS54;
                    POS5C = NATIVE_POS5C;
                    FLAG = 0;
                }
                if (S16(0x62) >= S16(0x70))
                    S16(0x62) -= 2;
                NativeVirtualFrameAdvance();
            }
            break;'''
    body=body.replace('NATIVE_STAGE',str(stage)).replace('NATIVE_POS54',floats[0]).replace('NATIVE_POS5C',floats[1])
    return source.replace(original_case,body)


def compile_one(tag,src):
    OUT.mkdir(parents=True,exist_ok=True)
    cpp=OUT/f'{tag}-action-six.cpp';obj=OUT/f'{tag}-action-six.obj'
    cpp.write_text(src)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
                      '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
                     env=env,cwd=ROOT,capture_output=True,text=True,timeout=120)
    (OUT/f'{tag}-compile.log').write_text(p.stdout+p.stderr)
    require(p.returncode==0,f'{tag}: pinned VC7.1 compile failed: {p.stderr}')
    return obj


def compare_grammar(original,probe):
    """Keep exact native GPRs/calls/x87 fields and full internal branch graph."""
    def names(ins):
        addresses={x.address:k for k,x in enumerate(ins)}
        result=[]
        for x in ins:
            op=SLOT_RE.sub('[ORIGINAL_LARGER_FRAME_OWNER]',x.op_str)
            if x.mnemonic.startswith('j') and DIRECT_RE.fullmatch(op):
                val=int(op,16)
                op=('CASE_INSTRUCTION_'+str(addresses[val]) if val in addresses
                    else 'EXIT_TO_WHOLE_FUNCTION')
            elif x.mnemonic=='call' and DIRECT_RE.fullmatch(op):
                op='TYPED_SOURCE_NATIVE_CALL'
            elif x.mnemonic in ('fcomp','fsub','fadd','fld'):
                op=X87_ABS_RE.sub('[AUTHENTIC_GLOBAL_RELOCATION]',op)
            result.append((x.mnemonic,op))
        return result
    a,b=names(original),names(probe)
    require(a==b,'source case-six real native GPR/x87/member/branch operands differ: '+str([(i,x,y) for i,(x,y) in enumerate(zip(a,b)) if x!=y][:5]))


def verify_fields(original,probe,relocations):
    source_fields=[]
    for ordinal,(mnemonic,typ,target,source) in ORIGINAL_REFS.items():
        a,b=original[ordinal],probe[ordinal]
        require(a.mnemonic==b.mnemonic==mnemonic,'original case-six call/global instruction moved')
        if typ=='REL32':
            require(a.op_str==f'0x{target:x}','wrong original native full-PE call target')
        else:
            require(a.op_str==f'dword ptr [0x{target:x}]','wrong original native global target')
        found=[x for x in relocations if b.address<=x['offset']<b.address+b.size]
        require(len(found)==1 and found[0]['type']==typ and source in found[0]['symbol'],
                'actual physical candidate COFF relocation not native typed original')
        source_fields.append((ordinal,typ,target))
    first,last=probe[0].address,probe[-1].address+probe[-1].size
    require(len([x for x in relocations if first<=x['offset']<last])==6,
            'candidate source case-six has extra or missing physical relocation fields')
    require(original[102].op_str==probe[102].op_str and
            original[102].mnemonic==probe[102].mnemonic=='call'
            and original[102].op_str.startswith('dword ptr ['),
            'natural C++ virtual dispatch did not reproduce original vtbl[0] indirect call')
    return source_fields


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='One registered PE address or Reimu (default three 104-insn originals)')
    args=parser.parse_args()
    reader=module('f548_reader',ROOT/'scripts/compare-coff-function.py')
    action=module('f548_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f548_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    zero=module('f548_zero',ROOT/'scripts/verify-fighter-actionzero-natural-source.py')
    one=module('f548_one',ROOT/'scripts/verify-fighter-actionone-natural-source.py')
    six=module('f548_six',ROOT/'scripts/verify-fighter-opening-actions-natural-source.py')
    target=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    full={b['address']:b for b in json.loads(PINNED.read_text())['bosses']}
    selected=list(SELECTED)
    if args.boss:
        pick=0x0045DD70 if args.boss.lower()=='reimu' else int(args.boss,0)
        selected=[pick];require(pick in SELECTED,'unregistered 104-insn first-action-six native giant')
    results=[]
    for address in selected:
        tag=SELECTED[address];boss=full[address]
        # Original whole native body and all original native switch DATA are
        # attested first; we never fabricate standalone case-function credit.
        report,mapped=action.report_boss(reader,target,decoder,boss)
        original,stage,floats=native_case(reader,target,decoder,boss)
        generated=generate_source(tag,stage,floats,report,mapped,six,switch,zero,one,
                                  reader,target,decoder,boss)
        obj=compile_one(tag,generated)
        code,refs=reader.object_function(obj,f'?Advance@FighterSwitchF548_{tag}@@QAEXXZ')
        inst,ret=zero.candidate_instructions(code,decoder)
        require(len(code)-ret==boss['postret_size'],'native source object post-RET table shape incorrect')
        bounds=sorted((r for r in refs if ret+24<=r['offset']<ret+32),key=lambda r:r['offset'])
        require(len(bounds)==2 and all(r['type']=='DIR32' and
                r['offset']==ret+24+4*i and r['local_symbol_offset'] is not None
                for i,r in enumerate(bounds)), 'missing real physical case-six/seven native COFF targets')
        start,end=[r['local_symbol_offset'] for r in bounds]
        require(0<=start<end<=ret,'native source case-six reaches outside object CODE')
        candidate=list(decoder.disasm(code[start:end],start))
        require(len(candidate)==104 and sum(x.size for x in candidate)==362,
                'native C++ did not emit complete original 362-byte/104-insn case six')
        compare_grammar(original,candidate)
        refs_six=verify_fields(original,candidate,refs)
        dense,index,map_count=zero.verify_physical_tables(boss,report,target,reader,switch,
                                                           inst,code,refs,ret)
        row={'original_boss':f'0x{address:08X}','whole_original_CODE':boss['size'],
             'action_six_native_bytes':362,'candidate_action_six_bytes':362,
             'native_instructions':104,'genuine_typed_case_COFF_fields':len(refs_six),
             'real_native_virtual_call':original[102].op_str,
             'native_stage_threshold':stage,'original_position_literal':floats[0],
             'original_speed_literal':floats[1],'dense_table_COFF_fields':dense,
             'original_sparse_index_bytes':index,'postret_DATA_shape':len(code)-ret}
        results.append(row)
        print(f'{address:#010x}: 362/362 native action6 length, 104/104 complete original GPR/x87/branch instructions, '
              f'6/6 true COFF call/data refs, real virtual {original[102].op_str}, '
              f'{dense} table refs, {index} identical sparse indices; stage={stage}, '
              f'position={floats[0]}, speed={floats[1]}',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(results,indent=2)+'\n')
    print(f'{len(results)}/{len(selected)} original whole-giant contexts independently compiled; '
          'NO entire fighter source exact, no partial CODE/DATA accepted, no all-unit replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('native action-six VC7.1/PE check failed:',e,file=sys.stderr)
        raise SystemExit(1)
