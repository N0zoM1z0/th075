#!/usr/bin/env python3
"""Verify 22 full original TH075 fighter action bosses and physical switch DATA.

Read-only pinned original PE/Capstone verification; does NOT produce or
accept reconstructed C++, add CODE coverage, or cold-replay exact units.
The checked-in JSON fingerprints are independently frozen original data.
"""
from __future__ import annotations

import collections
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
TARGET_SHA = 'bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98'
CALLS_RE = re.compile(r'0x[0-9a-f]+')
INDIRECT_JMP_RE = re.compile(r'dword ptr \[\w+\*4 \+ 0x[0-9a-f]+\]')
BYTE_MAP_RE = re.compile(r'byte ptr \[\w+ \+ 0x([0-9a-f]+)\]')


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    manifest = json.loads(MANIFEST.read_text())
    assert manifest['target_sha256'] == TARGET_SHA
    expected = manifest['bosses']
    assert len(expected) == 22 and sum(e['size'] for e in expected) == 1102055
    assert sum(e['postret_size'] for e in expected) == 16123
    entries = {int(x['address'], 16): x for x in
               csv.DictReader((ROOT / 'config/functions.csv').open(newline=''))}
    orig = {int(x['address'], 16): x for x in
            csv.DictReader((ROOT / 'config/function-origins.csv').open(newline=''))}
    spec = importlib.util.spec_from_file_location(
        'fighter_family_original_pe', ROOT / 'scripts/compare-coff-function.py')
    assert spec is not None and spec.loader is not None
    m = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = m
    spec.loader.exec_module(m)
    target = m.verified_target()
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    maps = collections.defaultdict(list)
    all_code = all_data = all_ins = all_calls = all_sl = all_maps = 0
    groupcounts = collections.Counter()
    for e in expected:
        a, size = e['address'], e['size']
        record = entries[a]
        assert record['owner'] == 'authored' and record['status'] in ('unclassified', 'matching')
        # This original-only verifier must keep working if future exact
        # whole-function C++ reconstruction closes one of these bosses.
        assert int(record['size']) == size and orig[a]['origin'] == 'authored'
        assert size >= 20000 and e['postret_size'] >= 400
        code = m.pe_bytes_at(target, a, size)
        assert sha(code) == e['sha256'], f'Original full CODE fingerprint: {a:#x}'
        ins = list(disassembler.disasm(code, a))
        assert len(ins) == e['instructions']
        assert len(ins) > 7000 and ins[-1].address + ins[-1].size == a + size
        assert ins[-1].mnemonic == 'ret' and sum(i.mnemonic == 'ret' for i in ins) == 1
        ncall = sum(i.mnemonic == 'call' for i in ins)
        assert ncall == e['calls']
        assert ins[2].op_str == e['stack']
        addresses = {i.address for i in ins}
        jumps = [i for i in ins if i.mnemonic == 'jmp'
                 and INDIRECT_JMP_RE.fullmatch(i.op_str)]
        assert len(jumps) == len(e['tables']) == e['jump_count']
        assert len(jumps) in (1, 6, 7)
        groupcounts[len(jumps)] += 1
        pos = a + size
        targets = set()
        nslots = nsparse = 0
        for num, (i, entry) in enumerate(zip(jumps, e['tables'])):
            assert i.address == entry['jmp']
            match = CALLS_RE.search(i.op_str)
            assert match and int(match.group(), 16) == entry['dense_addr'] == pos
            slots = entry['slots']
            assert 0 < slots < 200
            dense = m.pe_bytes_at(target, pos, 4 * slots)
            assert sha(dense) == entry['dense_sha']
            original_destinations = [int.from_bytes(dense[j:j + 4], 'little')
                                     for j in range(0, len(dense), 4)]
            assert 1 <= len(set(original_destinations)) <= slots
            # Distinct switch *slots* can legitimately converge on a native
            # shared default/epilogue CODE label. Never invent uniqueness.
            assert all(v in addresses for v in original_destinations)
            assert original_destinations[0] == entry['firsttarget']
            assert original_destinations[-1] == entry['lasttarget']
            nslots += slots
            targets.update(original_destinations)
            pos += len(dense)
            if entry['map_addr'] is None:
                assert entry['map_length'] == 0 and entry['map_sha'] is None
                if num + 1 < len(jumps):
                    assert pos == e['tables'][num + 1]['dense_addr']
                continue
            assert pos == entry['map_addr']
            assert 0 < entry['map_length'] <= 800
            byte_map = m.pe_bytes_at(target, pos, entry['map_length'])
            assert sha(byte_map) == entry['map_sha']
            assert all(v < slots for v in byte_map)
            assert set(byte_map) == set(range(slots))
            assert entry['map_distinct'] == slots
            assert any(BYTE_MAP_RE.search(z.op_str)
                       and int(BYTE_MAP_RE.search(z.op_str).group(1), 16) == pos
                       for z in ins[max(0, ins.index(i) - 8): ins.index(i)])
            maps[(len(byte_map), entry['map_sha'])].append((a, num))
            nsparse += len(byte_map)
            pos += len(byte_map)
        assert nslots == e['dense_entries'] and nsparse == e['sparse_bytes']
        assert len(targets) == e['unique_targets']
        assert pos == a + size + e['postret_size']
        assert sha(m.pe_bytes_at(target, a + size, e['postret_size'])) == e['postret_sha']
        assert e['pad_count'] == ((-pos) % 16)
        assert m.pe_bytes_at(target, pos, e['pad_count']) == b'\xCC' * e['pad_count']
        all_code += size
        all_data += e['postret_size']
        all_ins += len(ins)
        all_calls += ncall
        all_sl += nslots
        all_maps += nsparse
        print(f'{a:#010x}: whole {size:,} CODE / {len(ins):,} instructions, '
              f'{len(jumps)} native switches / {nslots} DWORDs / {nsparse} indexed bytes, '
              f'{len(targets)} original CODE destinations, {e["pad_count"]} CC padding')
    assert all_code == 1102055 and all_data == 16123
    assert all_ins == 292761 and all_sl > 1000 and all_maps > 5000
    assert groupcounts == {1: 11, 6: 2, 7: 9}, groupcounts
    reused = sorted(((len(v), length, digest, v) for (length, digest), v in maps.items()
                     if len(v) >= 2), reverse=True)
    assert [x[0] for x in reused] == [8, 8, 3, 2]
    assert sorted((x[1], x[0]) for x in reused) == [(49, 3), (49, 8), (66, 2), (68, 8)]
    print('\nPhysically identical original sparse action-ID maps across distinct bosses:')
    for count, length, digest, members in reused:
        print(f'  {length} bytes {count} copies SHA256 {digest}: '
              + ', '.join(f'{address:#010x}/table{which}' for address, which in members))
    print(f'\nVerified {len(expected)} complete original boss CODE functions, '
          f'{all_code:,} unaccepted authored CODE bytes, '
          f'{all_ins:,} x86 instructions, {all_calls:,} native calls, '
          f'{all_data:,} real after-RET DATA bytes ({all_sl} DWORD slots, '
          f'{all_maps} sparse index bytes)')
    print('No C++ reconstructed, no CODE or DATA credited, no all-unit cold replay')


if __name__ == '__main__':
    main()
