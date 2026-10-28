#!/usr/bin/env python3
"""Verify the six original Reimu action-dispatch jump tables in Japanese TH075.

This is original PE reconnaissance, NOT source reconstruction or exact credit.
The 60,999-byte native function and 1,090-byte owned post-RET DATA are
separately measured. No all-unit cold replay, compiler, PE write or byte graft.
"""
from __future__ import annotations

import hashlib
import importlib.util
from pathlib import Path

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
BASE = 0x0045DD70
CODE_SIZE = 60999
CODE_SHA256 = "b78fa89a709b1cbbafdf4310c6fd81dd68369a9fa528a1852a64bb105ee93bc2"
POST_RET_DATA_SHA256 = "12ff143bc7e1263db16b4c6629827a16e70973f339e7cc787c2aed9ee57d98eb"

# Label, inclusive original fighter state range, native indexed-JMP address,
# absolute dense DWORD table address and count, optional byte-index-map address.
TABLES = (
    ("0x000..0x00A", 0x000, 0x00A, 0x45DDCB, 0x46CBB7, 11, None,
     "fcaca1d8e6d287a04aba98ccdd77fe42b175924afa0c40ee027dfbf520802a4a", None),
    ("0x033..0x063", 0x033, 0x063, 0x45DE05, 0x46CBE3, 26, 0x46CC4B,
     "d7a6ad1bc04bcd0bccc549492fcaf2d365ff19f21d09fda589beb5ce56ddd9b1",
     "924429b5c10b434d789b073c634207abb2c0d31243bb71bf07d921c6879f7d1b"),
    ("0x08F..0x0D2", 0x08F, 0x0D2, 0x45DE42, 0x46CC7C, 32, 0x46CCFC,
     "516173b08a087c5aaa0031fc4b3f2eba177aa783835a2e60488dbbe6633ea045",
     "a5a34134b8e8e16d03f131a259adb2621cc4cf6499be28366ab35d452f1f48f6"),
    ("0x12D..0x136", 0x12D, 0x136, 0x45DE78, 0x46CD40, 10, None,
     "78523e65f9c4e37a96e6f7116b4f97ba3a7028290abf285c111d7817893dfb21", None),
    ("0x187..0x25A", 0x187, 0x25A, 0x45DEB8, 0x46CD68, 32, 0x46CDE8,
     "c3b396488b702612c7b280bc70dd4542c427ec029c537eaa98e6c23d6b9108c9",
     "0867b04f718821ba361456e52699e05f299254e2cf81f7107be5671d6ce7cee8"),
    ("0x25C..0x31C", 0x25C, 0x31C, 0x45DEE2, 0x46CEBC, 31, 0x46CF38,
     "99f97556c45fbb7c9ec670bb7cdd4bed5caa0ddbddf3218d131bcbe28d824433",
     "4132b946e3f4ba079c8af65a2b666613a4da968a66d91cd62b25dca2831df1f3"),
)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def check() -> None:
    spec = importlib.util.spec_from_file_location(
        "original_coff_checker", ROOT / "scripts/compare-coff-function.py"
    )
    if spec is None or spec.loader is None:
        raise RuntimeError("Cannot load the repository's pinned PE checker")
    import sys
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    pe = module.verified_target()  # enforces SHA256 and pinned original PE
    code = module.pe_bytes_at(pe, BASE, CODE_SIZE)
    assert digest(code) == CODE_SHA256, "Original Reimu CODE changed"
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, BASE))
    assert len(instructions) == 16837, "Wrong full native instruction stream"
    assert instructions[-1].address + instructions[-1].size == BASE + CODE_SIZE
    assert instructions[-1].mnemonic == "ret"
    assert sum(i.mnemonic == "ret" for i in instructions) == 1
    boundaries = {i.address: i for i in instructions}
    expected_next = BASE + CODE_SIZE
    destinations = set()
    dense_count = sparse_count = 0
    print("ReimuFighter action boss ORIGINAL-PE dispatch verification (NOT exact)")
    print(f"CODE: {CODE_SIZE} bytes; {len(instructions)} complete x86 instructions")

    for label, low, high, instruction_addr, address, count, index_at, table_hash, index_hash in TABLES:
        assert expected_next == address, f"Noncontiguous owned DATA preceding {label}"
        jump = boundaries[instruction_addr]
        assert jump.mnemonic == "jmp" and "dword ptr [" in jump.op_str
        assert f"0x{address:x}" in jump.op_str, f"Wrong native jump operand: {label}"
        raw = module.pe_bytes_at(pe, address, 4 * count)
        assert digest(raw) == table_hash, f"Native table bytes changed: {label}"
        target_list = [int.from_bytes(raw[4 * i:4 * i + 4], "little") for i in range(count)]
        assert all(t in boundaries for t in target_list), f"Out-of-CODE or unaligned target: {label}"
        assert len(set(target_list)) == count, f"Repeated dense dispatch destinations: {label}"
        destinations.update(target_list)
        dense_count += count
        expected_next = address + 4 * count
        if index_at is None:
            assert count == high - low + 1, f"Wrong dense state range: {label}"
            print(f"  {label}: {count} direct DWORD targets, {4 * count} DATA bytes @ {address:#010x}")
        else:
            assert expected_next == index_at, f"Sparse-index map not adjacent: {label}"
            indices = module.pe_bytes_at(pe, index_at, high - low + 1)
            assert digest(indices) == index_hash, f"Original sparse-byte map changed: {label}"
            assert len(indices) == high - low + 1 and max(indices) < count
            assert set(indices) == set(range(count)), f"Native map has unreachable dispatch target: {label}"
            sparse_count += len(indices)
            expected_next += len(indices)
            print(
                f"  {label}: {count} DWORD targets @ {address:#010x}; "
                f"{len(indices)} original sparse byte indices @ {index_at:#010x}"
            )

    assert dense_count == 142 and sparse_count == 522
    assert expected_next == 0x46CFF9 and expected_next - (BASE + CODE_SIZE) == 1090
    assert len(destinations) == 139, "Unexpected shared native case destinations"
    owned_data = module.pe_bytes_at(pe, BASE + CODE_SIZE, 1090)
    assert digest(owned_data) == POST_RET_DATA_SHA256
    assert module.pe_bytes_at(pe, expected_next, 7) == b"\xCC" * 7
    assert expected_next + 7 == 0x46D000
    print(
        f"Verified: {dense_count} original DWORD jump slots ({4 * dense_count} bytes), "
        f"{sparse_count} original index bytes, {len(destinations)} distinct native "
        f"instruction-aligned targets"
    )
    print("Whole owned after-RET DATA: 1090 bytes; seven CC alignment bytes not credited")
    print("No reconstructed source, cold replay or exact CODE credit claimed")


if __name__ == "__main__":
    check()
