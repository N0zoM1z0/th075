#!/usr/bin/env python3
"""Original-PE-check + fresh VC7.1 C++ experiments for fighter action 1.

Reconstruct the complete 60-native-instruction action-1 case in each of the
11 huge multi-switch fighters (not a standalone function!). Each native
function's entire CODE SHA and every owned post-RET physical jump table are
validated before building one targeted natural C++ switch probe. Candidate
code/data are diagnostic, NOT accepted as whole-function exact coverage.
Never invokes an all-unit replay.
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

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / '.analysis/f542-action-one-natural-source'
PINNED = ROOT / 'config/fighter-boss-dispatch-fingerprints.json'
NAMES = {0x0045DD70: 'Reimu', 0x004AC040: 'CharacterMove'}
COFF = ROOT / 'scripts/compare-coff-function.py'
ACTIONS = ROOT / 'scripts/report-fighter-action-handlers.py'
SWITCH = ROOT / 'scripts/verify-fighter-natural-switch-probes.py'
CASE0 = ROOT / 'scripts/verify-fighter-actionzero-natural-source.py'


def require(ok, message):
    if not ok:
        raise ValueError(message)


def load_module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    require(spec is not None and spec.loader is not None, f'missing helper {path}')
    m = importlib.util.module_from_spec(spec)
    sys.modules[name] = m
    spec.loader.exec_module(m)
    return m


def case_source(switch_src, casezero, tag):
    src = casezero.generate(switch_src, tag)
    base = f'FighterSwitchF540_{tag}'
    src = src.replace(base, f'FighterSwitchF542_{tag}')
    declaration = 'void ResetAt453E20();'
    require(src.count(declaration) == 1, 'case-zero owner member declarations changed')
    src = src.replace(declaration, declaration +
                      ' short GetNativeActionAt40FA30(); void SetNativeActionAt40FAC0(int);')
    first = '''        case 0x0:
'''
    second = '''        case 0x1: g_FighterProbeMarker = 2; break;'''
    require(src.count(first) == 1 and src.count(second) == 1,
            'one native-case body expected in original-shaped switch')
    # The C++ for action zero has already been independently native-probed.
    # Duplicate its *real gameplay behavior*, then append action-one's
    # original Get/compare/Set state policy. Avoid C++ helper extra calls.
    initial = src.index(first)
    after = src.index(second, initial)
    action_zero = src[initial+len(first):after]
    require(action_zero.rstrip().endswith('break;'), 'action-zero case lost break')
    action_one = action_zero.rsplit('            break;', 1)[0]
    require('if (FLAG == 0)' in action_one and 'POS += g_RiseAt00658050;' in action_one,
            'action-zero real signed/x87 case body lost')
    action_one += '''            if (GetNativeActionAt40FA30() == I16(0x70))
                SetNativeActionAt40FAC0(2);
            break;\n'''
    src = src.replace(second, '        case 0x1:\n' + action_one.rstrip('\n'))
    require(src.count('case 0x1:') == 1, 'duplicate native action-one case')
    return src


def compile_one(tag, source):
    OUT.mkdir(parents=True, exist_ok=True)
    path = OUT / f'{tag}-action-one.cpp'
    obj = OUT / f'{tag}-action-one.obj'
    path.write_text(source)
    env = os.environ.copy()
    env.pop('DISPLAY', None)
    env.pop('WAYLAND_DISPLAY', None)
    env['WINEPREFIX'] = str(ROOT / '.analysis/vc71-wine')
    env['WINEDLLOVERRIDES'] = 'winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(path), str(obj),
                             '/Od', '/Ob0', '/Gy', '/GR-', '/GX-', '/GS', '/Zi', '/I', 'src'],
                            cwd=ROOT, env=env, capture_output=True, text=True, timeout=120)
    (OUT / f'{tag}-compile.log').write_text(result.stdout + result.stderr)
    require(result.returncode == 0, f'{tag}: VC7.1 compilation failed: {result.stderr}')
    return obj


def case_native(reader, original, decoder, boss):
    """Bounds are 2nd and 3rd physical native first jump-table slots."""
    require(len(boss['tables']) in (6, 7) and boss['tables'][0]['slots'] == 11,
            'not an original multi-switch fighter')
    table = boss['tables'][0]
    native = reader.pe_bytes_at(original, table['dense_addr']+4, 8)
    first = int.from_bytes(native[0:4], 'little')
    last = int.from_bytes(native[4:8], 'little')
    require(boss['address'] < first < last < boss['address']+boss['size'],
            'original native action one case boundaries invalid')
    ins = list(decoder.disasm(reader.pe_bytes_at(original, first, last-first), first))
    require(len(ins) == 60 and ins[0].address == first
            and ins[-1].address+ins[-1].size == last,
            'original action one 60 native instructions are not contiguous')
    return ins, first, last


def case_candidate(reader, obj, decoder, tag, expected_total, expected_jump_count):
    code, refs = reader.object_function(obj, f'?Advance@FighterSwitchF542_{tag}@@QAEXXZ')
    instructions = []
    for ins in decoder.disasm(code, 0):
        instructions.append(ins)
        if ins.mnemonic == 'ret':
            break
    require(instructions and instructions[-1].mnemonic == 'ret', 'candidate normal return absent')
    after_ret = instructions[-1].address + instructions[-1].size
    require(len(code)-after_ret == expected_total, 'original-shaped post-RET DATA length changed')
    # Physically compare the first three genuine switch data relocations.
    fields = sorted((r for r in refs if after_ret <= r['offset'] < after_ret+12),
                    key=lambda r: r['offset'])
    require(len(fields) == 3 and all(r['type'] == 'DIR32' and
            r['offset'] == after_ret+4*i and r['local_symbol_offset'] is not None
            for i,r in enumerate(fields)),
            'missing authentic COFF jump-table labels for case 0/1/2')
    first, last = (r['local_symbol_offset'] for r in fields[1:3])
    require(0 <= first < last < after_ret, 'candidate action-one physical bounds invalid')
    part = list(decoder.disasm(code[first:last], first))
    require(len(part) == 60 and sum(x.size for x in part) == last-first,
            'candidate natural C++ action-one body is not whole')
    return code, refs, instructions, after_ret, part


ORIGINAL_FIELDS = {
    '0x453e20': ('REL32', 'ResetAt453E20'),
    '0x40fa30': ('REL32', 'GetNativeActionAt40FA30'),
    '0x40fac0': ('REL32', 'SetNativeActionAt40FAC0'),
    '0x65782c': ('DIR32', 'g_ThresholdAt0065782C'),
    '0x657478': ('DIR32', 'g_SubtractAt00657478'),
    '0x658050': ('DIR32', 'g_RiseAt00658050'),
}


def inspect_field_grammar(ins, relocs=None):
    """Resolve 11 genuinely native original call/global operand positions."""
    locations = []
    for index, instruction in enumerate(ins):
        if instruction.mnemonic not in ('call', 'fcomp', 'fsub', 'fadd'):
            continue
        if relocs is None:
            if instruction.mnemonic == 'call':
                symbol = instruction.op_str
            else:
                require(instruction.op_str.startswith('dword ptr [') or
                        instruction.op_str.startswith('qword ptr ['),
                        'non-global native x87 operand')
                symbol = instruction.op_str.split('[', 1)[-1].split(']', 1)[0]
            require(symbol in ORIGINAL_FIELDS,
                    f'original call/global unexpected at instruction {index}: {symbol}')
            typ, name = ORIGINAL_FIELDS[symbol]
            locations.append((index, instruction.mnemonic, typ, symbol))
        else:
            real = [r for r in relocs if instruction.address <= r['offset'] < instruction.address+instruction.size]
            require(len(real) == 1, f'candidate missing physical COFF field at instruction {index}')
            reloc = real[0]
            supported = [(symbol, typ, name) for symbol, (typ, name) in ORIGINAL_FIELDS.items()
                         if reloc['type'] == typ and name in reloc['symbol']]
            require(len(supported) == 1, f'candidate wrong COFF symbol/type at {index}')
            symbol, typ, name = supported[0]
            locations.append((index, instruction.mnemonic, typ, symbol))
    require(len(locations) == 11 and sum(r[2] == 'REL32' for r in locations) == 5,
            f'original/compiled action-one requires eleven physical references: {locations}')
    require([int(x[3], 16) for x in locations if x[2]=='REL32']==
            [0x453e20, 0x453e20, 0x453e20, 0x40fa30, 0x40fac0],
            'native call sequence changed')
    return locations


def check_receiver_dataflow(ins):
    """Check all 17 actual receiver reloads, their use and thiscall ECX."""
    real = []
    for index, inst in enumerate(ins[:-1]):
        if inst.mnemonic == 'movsx' and 'byte ptr [' in inst.op_str:
            m = re.fullmatch(r'(eax|ecx|edx), byte ptr \[([a-z]{3}) \+ 0x3ac\]', inst.op_str)
            require(m is not None and ins[index+1].mnemonic == 'test'
                    and ins[index+1].op_str == f'{m.group(1)}, {m.group(1)}',
                    'signed flag load not consumed by correct native TEST')
        if inst.mnemonic != 'mov':
            continue
        m = re.fullmatch(r'(eax|ecx|edx), dword ptr \[ebp - (0x[0-9a-f]+|\d+)\]', inst.op_str)
        if m is None:
            continue
        reg, slot = m.groups()
        real.append(slot)
        nxt = ins[index+1]
        if nxt.mnemonic == 'call':
            require(reg == 'ecx', 'native action one receiver call not thiscall ECX')
        else:
            require(f'[{reg} + ' in nxt.op_str,
                    'native action one owner reload not consumed immediately')
    require(len(real) == 17 and len(set(real)) == 1,
            'action one must have seventeen real receiver reloads from one saved local')
    return real[0]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss', help='One original PE address, Reimu, or CharacterMove (default all 11)')
    args = parser.parse_args()
    reader = load_module('f542_coff', COFF)
    actions = load_module('f542_actions', ACTIONS)
    switch = load_module('f542_switch', SWITCH)
    casezero = load_module('f542_casezero', CASE0)
    pe = reader.verified_target()
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    manifest = json.loads(PINNED.read_text())
    originals = [b for b in manifest['bosses'] if b['jump_count'] > 1]
    require(len(originals) == 11 and sum(b['size'] for b in originals)==613391,
            'native multi-switch complete original inventory changed')
    if args.boss:
        by_name = {tag.lower():addr for addr,tag in NAMES.items()}
        key = args.boss.lower()
        addr = by_name[key] if key in by_name else int(args.boss, 0)
        originals = [x for x in originals if x['address']==addr]
        require(len(originals)==1, 'unregistered fighter boss requested')
    outcomes=[]
    for b in originals:
        addr = b['address']; tag = NAMES.get(addr, f'Boss{addr:08X}')
        native, mapped = actions.report_boss(reader, pe, decoder, b)
        native_case, start, end = case_native(reader, pe, decoder, b)
        # Consume the previous independently verified case-zero/natural switch
        # compilers and extend only one actual gameplay case in this probe.
        source, ncases = switch.generate_probe(tag, mapped, native['default'])
        cpp = case_source(source, casezero, tag)
        obj = compile_one(tag, cpp)
        code, refs, cand_ins, postret, candidate = case_candidate(reader,obj,decoder,tag,b['postret_size'],b['jump_count'])
        require([x.mnemonic for x in candidate] == [x.mnemonic for x in native_case],
                f'{addr:08X}: action 1 mnemonic sequence differs')
        require(casezero.case_grammar(native_case, register_sensitive=True)==
                casezero.case_grammar(candidate, register_sensitive=True),
                f'{addr:08X}: action 1 genuine per-fighter register/x87/branch grammar differs')
        check_receiver_dataflow(native_case)
        check_receiver_dataflow(candidate)
        assert_original = inspect_field_grammar(native_case)
        assert_candidate = inspect_field_grammar(candidate,refs)
        require(assert_original == assert_candidate, f'{addr:08X}: 11 source/native physical relocation roles differ')
        owner = native['case_zero']['this_slot']
        ebp = int(owner.split('0x')[1], 16)
        length = end-start
        require(length == (263 if ebp >=128 else 212),
                f'{addr:08X}: original 17 natural receiver EBP encodings inconsistent')
        require(sum(x.size for x in candidate)==212,
                f'{addr:08X}: small generated C++ action-one body length mismatch')
        slots, mapbytes, maps=casezero.verify_physical_tables(b,native,pe,reader,switch,cand_ins,code,refs,postret)
        outcome = {'boss':f'0x{addr:08X}','whole_original_CODE':b['size'],
                   'case_one_native':length,'case_one_probe':sum(x.size for x in candidate),
                   'native_instructions':len(candidate),'native_typed_refs':len(assert_candidate),
                   'native_switches':b['jump_count'],'dense_COFF_refs':slots,
                   'identical_sparse_bytes':mapbytes,'native_postret_shape':len(code)-postret,
                   'cpp_probed_cases':ncases}
        outcomes.append(outcome)
        print(f'{addr:#010x}: original action-1 {length} native bytes, 60/60 actual GPR/x87/branch '
              f'instructions, 11/11 typed COFF call/data refs; '
              f'{slots} real DWORD switch COFF refs, {mapbytes} original sparse bytes, '
              f'original post-RET {len(code)-postret} DATA-shape; natural test case {sum(x.size for x in candidate)} bytes', flush=True)
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT/'summary.json').write_text(json.dumps(outcomes,indent=2)+'\n')
    print(f'New/affected local compiler probes only: {len(outcomes)}/{len(originals)} original whole-fighter contexts '
          'validated; zero giant exact CODE or DATA credit, no all-unit replay')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as error:
        print('original fighter action-one source/COFF verification failed:',error,file=sys.stderr)
        raise SystemExit(1)
