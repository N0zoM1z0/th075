#!/usr/bin/env python3
"""Validate entire TH075 82,796-byte original CharacterMove dispatcher, read-only.

The original PE tables are DATA after the actual RET, NOT reconstructed CODE.
This script neither modifies PE bytes nor cold replays any matching units.
"""
from __future__ import annotations

import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
BASE = 0x004AC040
CODE_SIZE = 82796
CODE_SHA256 = "4dced8c8583edf4b8234505793e28732e19af2adb311d0d39a755f0036e59cfc"
DATA_SHA256 = "bd3fbb666cc78c750efbf154d066c8087cb36225fd34593994240e77ed392377"
SHARED_REIMU_SPAN = (0x0046CCFC, "a5a34134b8e8e16d03f131a259adb2621cc4cf6499be28366ab35d452f1f48f6")

# State range, original physical indexed jump instruction, DWORD table start,
# number of DWORD slots, optional 1-byte index table, all independently
# original-PE SHA256 values. No guessed C++ case labels or default semantics.
TABLES = (
    ("0x000..0x00A", 0x000, 0x00A, 0x4AC09B, 0x4C03AC, 11, None,
     "8e1ca7d1b35f074637761d01f88ae0be475ec2eeebc1412823aaa72f4e265871", None),
    ("0x033..0x063", 0x033, 0x063, 0x4AC0D5, 0x4C03D8, 27, 0x4C0444,
     "64315e0c416844390e68fc63250f467e2d9fcabbafe4c47df4fbac5810855ef0",
     "8f5c9622c9e01faae1a5f158935e3342837c189bde690936e98cc5821dfbf978"),
    ("0x08F..0x0D2", 0x08F, 0x0D2, 0x4AC112, 0x4C0475, 32, 0x4C04F5,
     "6707c429dd9700dcae2310d23f3ce7df153bc7d6cbf177c7f4be1ccb55f81fb8",
     "a5a34134b8e8e16d03f131a259adb2621cc4cf6499be28366ab35d452f1f48f6"),
    ("0x12D..0x136", 0x12D, 0x136, 0x4AC148, 0x4C0539, 10, None,
     "2acb5dd57be83506d68bd2ffc4804746b2b1b8040c043d6dcc0e6d9292085ef8", None),
    ("0x187..0x253", 0x187, 0x253, 0x4AC188, 0x4C0561, 36, 0x4C05F1,
     "5619563bbe9c5c3c00bfceb4ea4610b6f16b5dc24350a17d36745c8b471bc627",
     "0d042aae0f00e2a489c9f6962ac5027f916135337fefea084fe3b339a9ab7308"),
    ("0x255..0x31C", 0x255, 0x31C, 0x4AC1B2, 0x4C06BE, 35, 0x4C074A,
     "0f99da91e0313d09e36d338d3959a7a7d633c47f58c9ae4eb8d5bb0b57a486cd",
     "4f882cdef29ade3d6ff00604da18927989a0cf0364063ca1a0953fac9407c271"),
)


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def check() -> None:
    spec = importlib.util.spec_from_file_location(
        "pinned_original_checker_for_character_move", ROOT / "scripts/compare-coff-function.py"
    )
    assert spec is not None and spec.loader is not None
    checker = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = checker
    spec.loader.exec_module(checker)
    pe = checker.verified_target()
    code = checker.pe_bytes_at(pe, BASE, CODE_SIZE)
    assert sha(code) == CODE_SHA256
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, BASE))
    assert len(ins) == 22721
    assert ins[-1].mnemonic == "ret" and ins[-1].address + ins[-1].size == BASE + CODE_SIZE
    assert sum(x.mnemonic == "ret" for x in ins) == 1
    assert sum(x.mnemonic == "call" for x in ins) == 1361
    assert ins[2].op_str == "esp, 0x720"
    original = {i.address: i for i in ins}
    assert original[BASE + 0x0A].op_str == "dword ptr [ebp - 0x64], ecx"
    assert original[BASE + 0x37].op_str == "eax, word ptr [edx + 0x60]"
    assert original[BASE + 0x3B].op_str == "dword ptr [ebp - 0x68], eax"
    expected = BASE + CODE_SIZE
    dense_entries = sparse_bytes = 0
    targets = set()
    print("TH075 CharacterMove::AdvanceAt004AC040 original PE audit (NOT exact source)")
    print(f"  Whole original CODE: {CODE_SIZE} bytes; {len(ins)} instructions; 1361 calls")
    for label, low, high, jump_address, start, entries, map_start, dense_sha, map_sha in TABLES:
        assert start == expected, f"Noncontiguous original table at {label}"
        jump = original[jump_address]
        assert jump.mnemonic == "jmp" and "dword ptr [" in jump.op_str
        assert f"0x{start:x}" in jump.op_str, (label, jump.op_str)
        dense = checker.pe_bytes_at(pe, start, 4 * entries)
        assert sha(dense) == dense_sha, f"Native DWORD slot contents changed: {label}"
        addresses = [int.from_bytes(dense[4 * i:4 * i + 4], "little") for i in range(entries)]
        assert len(set(addresses)) == entries
        assert all(address in original for address in addresses)
        targets.update(addresses)
        dense_entries += entries
        expected += 4 * entries
        if map_start is None:
            assert entries == high - low + 1
            print(f"  {label}: {entries} native direct DWORD targets @ {start:#010x}")
        else:
            assert expected == map_start
            indices = checker.pe_bytes_at(pe, map_start, high - low + 1)
            assert sha(indices) == map_sha
            assert len(indices) == high - low + 1
            assert all(index < entries for index in indices)
            assert set(indices) == set(range(entries))
            sparse_bytes += len(indices)
            expected += len(indices)
            print(f"  {label}: {entries} original DWORD targets @ {start:#010x}; "
                  f"{len(indices)} sparse byte indexes @ {map_start:#010x}")
    assert dense_entries == 151 and sparse_bytes == 522
    assert expected - (BASE + CODE_SIZE) == 1126
    assert expected == 0x004C0812 and len(targets) == 147
    assert sha(checker.pe_bytes_at(pe, BASE + CODE_SIZE, 1126)) == DATA_SHA256
    assert checker.pe_bytes_at(pe, expected, 14) == b"\xCC" * 14
    assert expected + 14 == 0x004C0820
    # Original Reimu and this independently authored fighter genuinely share
    # the exact *third sparse byte map*, but not their whole code or tables.
    reimu_index, shared_sha = SHARED_REIMU_SPAN
    assert sha(checker.pe_bytes_at(pe, reimu_index, 68)) == shared_sha
    assert checker.pe_bytes_at(pe, 0x004C04F5, 68) == checker.pe_bytes_at(pe, reimu_index, 68)
    print(f"  Validated {dense_entries} original DWORD slots / {dense_entries * 4} bytes; "
          f"{sparse_bytes} sparse-index bytes; {len(targets)} distinct instruction-aligned entries")
    print("  Entire post-RET DATA: 1126 bytes, followed by 14 CC alignment bytes")
    print("  Confirmed identical original 68-byte 0x08F..0x0D2 sparse index map in Reimu boss")
    print("  NO reconstructed CharacterMove CODE, jump DATA, or other function credit claimed")


if __name__ == "__main__":
    check()
