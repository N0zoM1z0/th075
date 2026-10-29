#!/usr/bin/env python3
"""Resolve every original fighter boss action ID to its physical case instruction.

This is *original-PE analysis*, not a C++ implementation, accepted exactness,
semantic ownership, or a substitute for whole-function reconstruction. It
verifies whole CODE and jump DATA before deriving the action-to-handler map.
Requires the repository's pinned Python/Capstone environment.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / 'config/fighter-boss-dispatch-fingerprints.json'
COFF = ROOT / 'scripts/compare-coff-function.py'
STACK_COMPARE = re.compile(r'^dword ptr (\[ebp - (?:0x[0-9a-f]+|\d+)\]), (0x[0-9a-f]+|\d+)$')
SUBTRACT = re.compile(r'^([a-z]{3}), (0x[0-9a-f]+|\d+)$')
STORE_STACK = re.compile(r'^dword ptr (\[ebp - (?:0x[0-9a-f]+|\d+)\]), ([a-z]{3})$')
LOAD_STACK = re.compile(r'^([a-z]{3}), dword ptr (\[ebp - (?:0x[0-9a-f]+|\d+)\])$')
INDIRECT_JUMP = re.compile(r'^dword ptr \[([a-z]{3})\*4 \+ (0x[0-9a-f]+)\]$')
BYTE_INDEX = re.compile(r'^([a-z]{3}), byte ptr \[([a-z]{3}) \+ (0x[0-9a-f]+)\]$')


def die(message: str) -> None:
    raise ValueError(message)


def check(ok: bool, message: str) -> None:
    if not ok:
        die(message)


def sha(raw: bytes) -> str:
    return hashlib.sha256(raw).hexdigest()


def original_data_reader():
    spec = importlib.util.spec_from_file_location('f537_coff_reader', COFF)
    check(spec is not None and spec.loader is not None, 'missing original PE reader')
    reader = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = reader
    spec.loader.exec_module(reader)
    return reader


def read_u32(raw: bytes, index: int) -> int:
    return int.from_bytes(raw[index:index + 4], 'little')


def direct_target(ins) -> int:
    # Capstone returns one direct target for the short/near conditional branch.
    check(ins.mnemonic in ('ja', 'je'), f'not a guarded native branch: {ins}')
    check(re.fullmatch(r'0x[0-9a-f]+', ins.op_str) is not None, f'non-direct branch {ins}')
    return int(ins.op_str, 16)


def recover_range(prefix, location: int, table: dict) -> tuple[int, int, int, str]:
    """Recover compiler-emitted action normalization and upper bound from CODE.

    A normal range is: SUB reg, base; MOV [state_slot], reg; CMP [slot], upper;
    JA default; MOV idx,[slot]; optionally MOVZX idx,[byte_map+idx]; JMP table.
    The zero-base range omits SUB/STORE but requires a genuine CMP/JA.
    """
    positions = {i.address: p for p, i in enumerate(prefix)}
    check(location in positions, f'{location:08X}: native switch instruction absent')
    p = positions[location]
    jump = prefix[p]
    jmatch = INDIRECT_JUMP.fullmatch(jump.op_str)
    check(jump.mnemonic == 'jmp' and jmatch is not None, f'{location:08X}: not an indexed jump')
    check(int(jmatch.group(2), 16) == table['dense_addr'], f'{location:08X}: wrong dense table operand')
    if table['map_addr'] is None:
        cmp_pos = p - 3
    else:
        move = prefix[p - 1]
        mm = BYTE_INDEX.fullmatch(move.op_str)
        check(move.mnemonic == 'movzx' and mm is not None,
              f'{location:08X}: missing physical byte-index load')
        check(int(mm.group(3), 16) == table['map_addr'],
              f'{location:08X}: sparse map points to wrong physical PE location')
        check(mm.group(1) == jmatch.group(1), f'{location:08X}: sparse-map register mismatch')
        cmp_pos = p - 4
    check(prefix[cmp_pos + 1].mnemonic == 'ja', f'{location:08X}: missing native unsigned JA bound guard')
    default = direct_target(prefix[cmp_pos + 1])
    cmp_inst = prefix[cmp_pos]
    cm = STACK_COMPARE.fullmatch(cmp_inst.op_str)
    check(cmp_inst.mnemonic == 'cmp' and cm is not None,
          f'{location:08X}: missing original state-slot bound compare')
    load = prefix[cmp_pos + 2]
    lm = LOAD_STACK.fullmatch(load.op_str)
    check(load.mnemonic == 'mov' and lm is not None and lm.group(2) == cm.group(1),
          f'{location:08X}: jump index is not freshly loaded from the guarded native slot')
    if table['map_addr'] is None:
        check(lm.group(1) == jmatch.group(1), f'{location:08X}: direct index register drift')
    else:
        check(lm.group(1) == mm.group(2), f'{location:08X}: byte-map input register drift')
    upper = int(cm.group(2), 0)
    expected = table['map_length'] if table['map_addr'] is not None else table['slots']
    check(upper + 1 == expected,
          f'{location:08X}: original action bound {upper + 1} disagrees with physical table {expected}')
    previous = prefix[cmp_pos - 1]
    before = prefix[cmp_pos - 2]
    store = STORE_STACK.fullmatch(previous.op_str)
    if previous.mnemonic == 'mov' and store is not None and store.group(1) == cm.group(1):
        sub = SUBTRACT.fullmatch(before.op_str)
        check(sub is not None and before.mnemonic == 'sub' and sub.group(1) == store.group(2),
              f'{location:08X}: unverified action normalization to native state-slot')
        base = int(sub.group(2), 0)
    else:
        # No subtraction on the initial 0-based switch. Ensure a real load
        # from that same slot and only legal 0..upper indexed input.
        check(table['map_addr'] is None and upper == 10 and location != 0,
              f'{location:08X}: unrecognized original action-lowering pattern')
        base = 0
    return base, upper, default, cm.group(1)


def report_boss(reader, target, decoder, boss) -> tuple[dict, list[dict]]:
    start, size = boss['address'], boss['size']
    code = reader.pe_bytes_at(target, start, size)
    check(sha(code) == boss['sha256'], f'{start:08X}: complete native CODE changed')
    ins = list(decoder.disasm(code, start))
    check(len(ins) == boss['instructions'], f'{start:08X}: instruction-boundary drift')
    check(ins[-1].mnemonic == 'ret' and ins[-1].address + ins[-1].size == start + size,
          f'{start:08X}: last instruction is not the full original RET')
    check(sum(i.mnemonic == 'ret' for i in ins) == 1, f'{start:08X}: unexpected RET count')
    instruction_starts = {i.address for i in ins}
    switches = [i for i in ins if i.mnemonic == 'jmp' and INDIRECT_JUMP.fullmatch(i.op_str)]
    check(len(switches) == boss['jump_count'] == len(boss['tables']),
          f'{start:08X}: incomplete native switch inventory')
    # Only compiler dispatch, never the first ordinary case-body instruction.
    prefix = [i for i in ins if i.address <= max(j.address for j in switches)]
    mapped: list[dict] = []
    ranges = []
    default_targets = set()
    slots_count = 0
    table_bytes_count = 0
    physical_target_set = set()
    for switch, table in zip(switches, boss['tables']):
        check(switch.address == table['jmp'], f'{start:08X}: switch address drift')
        base, upper, default, slot = recover_range(prefix, switch.address, table)
        check(default in instruction_starts, f'{start:08X}: default is not a native instruction')
        default_targets.add(default)
        dense = reader.pe_bytes_at(target, table['dense_addr'], 4 * table['slots'])
        check(sha(dense) == table['dense_sha'], f'{start:08X}: native DWORD table changed')
        destinations = [read_u32(dense, 4 * n) for n in range(table['slots'])]
        check(all(x in instruction_starts for x in destinations),
              f'{start:08X}: invalid original handler instruction boundary')
        physical_target_set.update(destinations)
        slots_count += table['slots']
        if table['map_addr'] is not None:
            indices = reader.pe_bytes_at(target, table['map_addr'], table['map_length'])
            check(sha(indices) == table['map_sha'], f'{start:08X}: compressed native index map changed')
        else:
            indices = bytes(range(table['slots']))
        table_bytes_count += len(indices) if table['map_addr'] is not None else 0
        check(len(indices) == upper + 1 and all(x < len(destinations) for x in indices),
              f'{start:08X}: missing/invalid native input mapping')
        check(set(indices) == set(range(len(destinations))),
              f'{start:08X}: native table has action-unreachable slots')
        for input_offset, row_index in enumerate(indices):
            mapped.append({'boss':f'0x{start:08X}', 'action':base+input_offset,
                           'table':f'0x{switch.address:08X}', 'slot':row_index,
                           'handler':f'0x{destinations[row_index]:08X}',
                           'kind':'dense' if table['map_addr'] is None else 'sparse'})
        ranges.append({'start':base, 'end':base+upper, 'slot':slot,
                       'jmp':f'0x{switch.address:08X}', 'default':f'0x{default:08X}',
                       'handlers':len(set(destinations)), 'used':len(indices)})
    check(len(default_targets) == 1, f'{start:08X}: unexpectedly different default branches')
    check(slots_count == boss['dense_entries'] and table_bytes_count == boss['sparse_bytes'],
          f'{start:08X}: wrong original table slot accounting')
    check(len(physical_target_set) == boss['unique_targets'],
          f'{start:08X}: whole boss original native destination count mismatch')
    mapped_actions = {v['action'] for v in mapped}
    check(len(mapped_actions) == len(mapped), f'{start:08X}: action overlap between native tables')
    check(all(v['handler'] != '' for v in mapped), f'{start:08X}: missing native handler')
    slot_id = ranges[0]['slot']
    singled = []
    for p in range(len(prefix)-1):
        x,y = prefix[p:p+2]
        cm = STACK_COMPARE.fullmatch(x.op_str)
        if cm is None or x.mnemonic != 'cmp' or cm.group(1) != slot_id or y.mnemonic != 'je':
            continue
        action = int(cm.group(2), 0)
        if action in mapped_actions:
            continue
        dest=direct_target(y)
        check(dest in instruction_starts, f'{start:08X}: isolated action handler outside original CODE')
        singled.append({'action':action,'handler':f'0x{dest:08X}', 'branch':f'0x{y.address:08X}'})
    singleton_map = {}
    for row in singled:
        existing = singleton_map.get(row['action'])
        check(existing is None or existing['handler'] == row['handler'],
              f'{start:08X}: same isolated action has contradictory physical native branches')
        singleton_map[row['action']] = row
    singled = sorted(singleton_map.values(), key=lambda r:r['action'])
    check(not set(x['action'] for x in singled) & mapped_actions,
          f'{start:08X}: singleton also in indexed action range')
    total_code_end = start + size
    stored_data=reader.pe_bytes_at(target,total_code_end,boss['postret_size'])
    check(sha(stored_data) == boss['postret_sha'], f'{start:08X}: after-RET original data drift')
    singleton_entries=[{'boss':f'0x{start:08X}', 'action':v['action'],
                        'table':v['branch'], 'slot':'', 'handler':v['handler'],
                        'kind':'singleton'} for v in singled]
    default_entry = f'0x{next(iter(default_targets)):08X}'
    default_rows = sum(row['handler'] == default_entry for row in mapped)
    # Inspect the *entire* physical action-zero handler body in each multi-table
    # boss, bounded by the next independently native first-table case address.
    # The same mnemonic-level action-zero policy appears in all 11 bosses, but
    # its individual machine-code bytes/receiver stack slots are NOT shared.
    case_zero = None
    first_case_signature = None
    if len(switches) > 1:
        check(boss['tables'][0]['map_addr'] is None and boss['tables'][0]['slots'] == 11,
              f'{start:08X}: no original eleven-slot zero-based initial switch')
        first_two = reader.pe_bytes_at(target, boss['tables'][0]['dense_addr'], 8)
        first, second = read_u32(first_two, 0), read_u32(first_two, 4)
        check(first in instruction_starts and second in instruction_starts and first < second,
              f'{start:08X}: action zero and one native boundaries invalid')
        block = [i for i in ins if first <= i.address < second]
        check(block[0].address == first and block[-1].address + block[-1].size == second,
              f'{start:08X}: action-zero block is not complete native instructions')
        check(len(block) == 50 and sum(i.mnemonic == 'call' for i in block) == 3,
              f'{start:08X}: unexpected action-zero native case control flow')
        check(all(i.op_str == '0x453e20' for i in block if i.mnemonic == 'call'),
              f'{start:08X}: native action-zero callee changed')
        check(sum(i.mnemonic in ('fld', 'fcomp', 'fnstsw', 'fstp', 'fsub', 'fadd') for i in block) == 18,
              f'{start:08X}: native action-zero x87 pipeline changed')
        check(all(any(constant in i.op_str for i in block)
                  for constant in ('0x65782c', '0x657478', '0x658050')),
              f'{start:08X}: native action-zero float constant identity changed')
        check(any('0x3ac' in i.op_str for i in block)
              and any('0x50' in i.op_str for i in block),
              f'{start:08X}: native action-zero flag/position fields changed')
        # All 14 real receiver loads use the same EBP stack slot; encoding
        # switches from disp8 to disp32 when the slot is beyond +/-127.
        this_loads = [i for i in block if i.mnemonic == 'mov'
                      and re.fullmatch(r'(?:eax|ecx|edx), dword ptr \[ebp - 0x[0-9a-f]+\]', i.op_str)]
        check(len(this_loads) == 14 and len({i.op_str.split('[')[1] for i in this_loads}) == 1,
              f'{start:08X}: native action-zero receiver stack-slot uses changed')
        this_slot = int(this_loads[0].op_str.split('- 0x')[1].rstrip(']'), 16)
        block_len = second - first
        check(block_len == (222 if this_slot >= 128 else 180),
              f'{start:08X}: native disp8/disp32 action-zero body length mismatch')
        case_zero = {'start':f'0x{first:08X}', 'end_exclusive':f'0x{second:08X}',
                     'bytes':block_len, 'instructions':len(block), 'calls':3,
                     'this_slot':f'EBP-0x{this_slot:X}',
                     'this_slot_reads':len(this_loads),
                     'sha256':sha(reader.pe_bytes_at(target, first, block_len))}
        first_case_signature = tuple(i.mnemonic for i in block)
    return ({'boss':f'0x{start:08X}', 'code':size, 'instruction_count':len(ins),
             'action_cases':len(mapped), 'default_mapped_actions':default_rows,
             'nondefault_mapped_actions':len(mapped)-default_rows,
             'unique_mapped_handlers':len(set(v['handler'] for v in mapped)),
             'default':f'0x{next(iter(default_targets)):08X}', 'singleton_branches':singled,
             'ranges':ranges, 'case_zero':case_zero, '_first_case_signature':first_case_signature},mapped+singleton_entries)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--boss',help='Print only one boss by original hexadecimal PE address (otherwise all 22)')
    parser.add_argument('--csv',help='Write every physical action-ID -> handler mapping to an output CSV')
    parser.add_argument('--json',action='store_true',help='Print a structured summary of all the native ranges and singleton branches')
    args=parser.parse_args()
    reader=original_data_reader()
    target=reader.verified_target()
    manifest=json.loads(MANIFEST.read_text())
    check(sha(target)==manifest['target_sha256'], 'target manifest disagreement')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    selected=manifest['bosses']
    if args.boss:
        requested=int(args.boss,0)
        selected=[r for r in selected if r['address']==requested]
        check(len(selected)==1,'unknown registered fighter boss address')
    summaries,entries=[],[]
    indexed_total = 0
    singleton_total = 0
    default_total = 0
    case_zero_signatures = []
    for boss in selected:
        summary, action_rows=report_boss(reader,target,decoder,boss)
        signature = summary.pop('_first_case_signature')
        if signature is not None:
            case_zero_signatures.append(signature)
        summaries.append(summary); entries.extend(action_rows)
        indexed_total += summary['action_cases']
        singleton_total += len(summary['singleton_branches'])
        default_total += summary['default_mapped_actions']
    check(len(set(case_zero_signatures)) <= 1, 'original eleven-boss action-zero mnemonic signatures diverged')
    if not args.boss:
        check(len(case_zero_signatures) == 11, 'not all original multi-table action-zero cases were verified')
    if args.csv:
        with Path(args.csv).open('w',newline='') as f:
            w=csv.DictWriter(f,fieldnames=['boss','action','table','slot','handler','kind'],lineterminator='\n')
            w.writeheader();w.writerows(entries)
    if args.json:
        print(json.dumps({'bosses':summaries, 'indexed_actions': indexed_total,
                          'singleton_actions':singleton_total, 'resolved_actions':len(entries),
                          'default_table_actions':default_total},indent=2))
    else:
        for row in summaries:
            parts=[f'{x["start"]:#05x}..{x["end"]:#05x}: {x["handlers"]} original destinations'
                   for x in row['ranges']]
            singles=','.join(f'{v["action"]:#x}->{v["handler"]}' for v in row['singleton_branches']) or 'none'
            print(f'{row["boss"]}: {row["code"]:,} complete native CODE, '
                  f'{row["action_cases"]} action IDs / {row["unique_mapped_handlers"]} '
                  f'physical mapped handlers ({row["default_mapped_actions"]} to JA default); '
                  f'default {row["default"]}')
            print('   ranges: '+'; '.join(parts))
            print('   singleton branches: '+singles)
            if row['case_zero'] is not None:
                c = row['case_zero']
                print(f'   action zero: {c["start"]}..{c["end_exclusive"]} '
                      f'{c["bytes"]} CODE bytes / {c["instructions"]} instructions, '
                      f'14 real receiver reloads from {c["this_slot"]}')
        print(f'Original PE verified: {len(summaries)} entire native bosses, '
              f'{indexed_total} table-dispatched ({default_total} shared-default) and '
              f'{singleton_total} separately branched action IDs '
              f'({len(entries)} complete direct mappings); no C++ CODE credited, '
              'no all-unit cold replay')


if __name__ == '__main__':
    try:
        main()
    except (ValueError, OSError) as exc:
        print(f'error: fighter action resolution: {exc}',file=sys.stderr)
        raise SystemExit(1)
