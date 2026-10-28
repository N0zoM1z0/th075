#!/usr/bin/env python3
"""Attest TH075 original WinMain full function, 15-case DATA and four cleanup paths.

Pinned original Japanese PE, read-only evidence. NOT an exact C++ match and no
cold replay or CODE coverage adoption. Case data is original post-RET DATA.
"""
from __future__ import annotations

import hashlib
import importlib.util
import sys
from pathlib import Path

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
START = 0x00602A60
CODE_SIZE = 2987
CODE_SHA256 = "780862e0f784ac2cbd16ed20eaff12c0da49a0c831ce4a9f56e85fc2edb3ffa0"
TABLE_SHA256 = "840a0d5ad8c1d5ad0a26f5ff4beae4c657cb03640df58b0aa1b71abba243fe86"
ALLOCATIONS = (0x11C, 0x10, 0x3C, 0xF4, 0x10, 0x54, 0x4C, 0x120,
               0xC, 0x1C, 0x124, 0x14, 0x3E0, 0x14, 0x1D0)
EXPECTED_CLEANUP_CALLS = (0x00406650, 0x00403BE0, 0x00401020, 0x00423A90)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    spec = importlib.util.spec_from_file_location(
        "winmain_native_checker", ROOT / "scripts/compare-coff-function.py"
    )
    if spec is None or spec.loader is None:
        raise RuntimeError("Cannot load the pinned original target checker")
    m = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = m
    spec.loader.exec_module(m)
    pe = m.verified_target()
    code = m.pe_bytes_at(pe, START, CODE_SIZE)
    assert digest(code) == CODE_SHA256, "Original WinMain CODE changed"
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, START))
    assert len(ins) == 654, "Wrong original complete x86 count"
    assert ins[-1].address + ins[-1].size == START + CODE_SIZE
    assert ins[-1].mnemonic == "ret" and ins[-1].op_str == "0x10"
    boundary = {x.address: x for x in ins}
    assert len(boundary) == 654
    table_start = START + CODE_SIZE  # 0060360B, not authored CODE
    table = m.pe_bytes_at(pe, table_start, 15 * 4)
    assert digest(table) == TABLE_SHA256
    targets = [int.from_bytes(table[i * 4:i * 4 + 4], "little") for i in range(15)]
    assert len(set(targets)) == 15
    assert all(t in boundary for t in targets), "Bad original case CODE target"
    assert targets[4] == min(targets), "Original case 4 is physically first"
    assert boundary[START + 0x5EB].op_str == f"dword ptr [ecx*4 + 0x{table_start:x}]"

    print("TH075 ORIGINAL WinMain full function dispatch audit (NOT exact source)")
    print(f"CODE: {CODE_SIZE} bytes / {len(ins)} x86 instructions / pinned SHA256 {CODE_SHA256}")
    for case, (where, nbytes) in enumerate(zip(targets, ALLOCATIONS)):
        first = boundary[where]
        assert first.mnemonic == "push" and int(first.op_str, 16) == nbytes
        next_insn = boundary[where + first.size]
        assert next_insn.mnemonic == "call" and int(next_insn.op_str, 16) == 0x0064159D
        print(f"  scene {case:2}: original new({nbytes:#05x}) at {where:#010x}, "+
              "native original operator new 0064159D")

    actual_cleanups = [i for i in ins if i.mnemonic == "call"
                       and i.op_str.startswith("0x")
                       and int(i.op_str, 16) in EXPECTED_CLEANUP_CALLS]
    assert len(actual_cleanups) == 16
    groups = [actual_cleanups[i:i + 4] for i in range(0, len(actual_cleanups), 4)]
    assert len(groups) == 4
    for ix, group in enumerate(groups):
        assert tuple(int(x.op_str, 16) for x in group) == EXPECTED_CLEANUP_CALLS
        assert all(group[j].address < group[j + 1].address for j in range(3))
        print(f"  {['RegisterClassExA failure','CreateWindowExA failure', 'CoInitialize failure', 'successful shutdown'][ix]} "
              f"destructor chain from {group[0].address:#010x}: sound → input → graphics → app mode")

    # Original scene pointer and path buffer are *separate actual locals*.
    assert boundary[START + 0x1C].mnemonic == "mov"
    assert boundary[START + 0x1C].op_str == "dword ptr [ebp - 0x184], 0"
    assert boundary[START + 0x46].op_str == "eax, [ebp - 0x180]"
    # The complete native startup and shutdown each reveal actual C++
    # automatic resource lifetimes, not a synthetic single cleanup tail.
    # The same physical EBP local is passed to each ctor/dtor pair.
    native_owners = (
        ('ArchiveCatalog', 0x2AF, 0x2B2, 0xB6B, 0xB6E,
         'ecx, [ebp - 0x35]', 0x0041CE10, 0x0041CE50),
        ('GameDataResources', 0x307, 0x30A, 0xB63, 0xB66,
         'ecx, [ebp - 0x36]', 0x00417210, 0x00417430),
    )
    for name, ctor_lea, ctor_call, dtor_lea, dtor_call, slot, ctor, dtor in native_owners:
        for offset in (ctor_lea, dtor_lea):
            instruction = boundary[START + offset]
            assert instruction.mnemonic == 'lea' and instruction.op_str == slot, name
        assert boundary[START + ctor_call].mnemonic == 'call'
        assert boundary[START + ctor_call].op_str == f'0x{ctor:x}', name
        assert boundary[START + dtor_call].mnemonic == 'call'
        assert boundary[START + dtor_call].op_str == f'0x{dtor:x}', name
        print(f'  Native C++ {name} lifetime: {slot}, ctor {ctor:#010x}, dtor {dtor:#010x}')

    # Three actual archive-open operations are *two-argument cdecl*.
    # Old complete C++ probes mistakenly expressed these as thiscall
    # ArchiveCatalog methods (MOV ECX, owner before call), violating the
    # original push/push/call/add esp,8 ABI at each physical call site.
    for offset in (0x2C1, 0x2D3, 0x2E5):
        assert boundary[START + offset - 10].mnemonic == 'push'
        assert boundary[START + offset - 5].mnemonic == 'push'
        assert boundary[START + offset].mnemonic == 'call'
        assert boundary[START + offset].op_str == '0x41cf80'
        assert boundary[START + offset + 5].mnemonic == 'add'
        assert boundary[START + offset + 5].op_str == 'esp, 8'
    print('  Three original cdecl archive opens 0041CF80: two pushed args, caller POP8')

    # Original replay-related global receiver is physically supplied in
    # ECX for each method, never a no-receiver cdecl function call.
    for move_at, call_at, destination in (
        (0x4B7, 0x4BC, 0x00416B10),
        (0xAEA, 0xAEF, 0x004169E0),
    ):
        assert boundary[START + move_at].mnemonic == 'mov'
        assert boundary[START + move_at].op_str == 'ecx, 0x6718f8'
        assert boundary[START + call_at].mnemonic == 'call'
        assert boundary[START + call_at].op_str == f'0x{destination:x}'
    print('  True replay global 006718F8 thiscalls at 00416B10 / 004169E0')

    # A real first-scene construction pointer (not an inert stack temp)
    # receives the Scene4 ctor result before it is copied to currentScene.
    native_initialization = (
        (0x48B, 'mov', 'dword ptr [ebp - 0x19c], ecx'),
        (0x491, 'mov', 'edx, dword ptr [ebp - 0x19c]'),
        (0x497, 'mov', 'dword ptr [ebp - 0x184], edx'),
        (0x49D, 'mov', 'word ptr [ebp - 0x3c], 0x2004'),
        (0x4A3, 'mov', 'ax, word ptr [ebp - 0x3c]'),
        (0x4C1, 'mov', 'ecx, 1'),
        (0x4C6, 'test', 'ecx, ecx'),
    )
    for offset, opcode, operands in native_initialization:
        instruction = boundary[START + offset]
        assert instruction.mnemonic == opcode and instruction.op_str == operands
    assert boundary[START + 0x4C8].mnemonic == 'je'
    print('  First constructed scene pointer EBP-0x19C → current scene EBP-0x184')
    print('  Initial scene state EBP-0x3C and genuine while(1) MOV/TEST/JE guard')

    # Initial and subsequent scene-state policy use an original instance
    # method, not a cdecl free function. Both point to original 00431F60.
    scene_calls = [x for x in ins if x.mnemonic == "call" and x.op_str == "0x431f60"]
    assert len(scene_calls) == 2
    assert {x.address for x in scene_calls} == {START + 0x4AE, START + 0x535}
    # Original single PeekMessage branch; the nested C++ source probe
    # incorrectly generated duplicate call blocks at some branch layouts.
    imports = {"PeekMessageA":0x65722C, "GetMessageA":0x657228,
               "TranslateMessage":0x657224, "DispatchMessageA":0x657220}
    for name, address in imports.items():
        actual = [x for x in ins if x.mnemonic == "call"
                  and x.op_str == f"dword ptr [{address:#x}]"]
        assert len(actual) == 1, (name, len(actual))
        print(f"  Windows pump: one native {name} IAT call at {actual[0].address:#010x}")

    assert table_start == 0x0060360B
    assert m.pe_bytes_at(pe, table_start + 60, 9) == b"\xCC" * 9
    assert table_start + 60 + 9 == 0x00603650
    print("Post-RET DATA: 15 distinct aligned DWORD case targets, 60 bytes; 9 CC padding bytes")
    print("Following original WindowCallback is at 00603650 (already separately cold-exact)")
    print("No WinMain source CODE or case-table DATA accepted or credited")


if __name__ == "__main__":
    main()
