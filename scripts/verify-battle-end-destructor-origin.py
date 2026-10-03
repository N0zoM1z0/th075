#!/usr/bin/env python3
"""Verify the whole scene destructor with constructor, virtual and cleanup witnesses."""
from __future__ import annotations

import hashlib
import importlib.util
import struct
import subprocess
from pathlib import Path
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM


ROOT = Path(__file__).resolve().parents[1]
ADDRESS = "0x00424F40"
ROLE = "BattleEndScene::DestroyAt00424F40"
VTABLE = 0x00657B7C
PREFIX_SHA256 = "c61a356999ddf964879e775a379a273f42fddcb3a32d5a2ad72e4089c4a94a25"


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def main():
    comparison = module("battle_end_target", "compare-coff-function.py")
    background = module("battle_end_source", "verify-background-destructor-origins.py")
    reader = module("battle_end_coff", "coff_data.py")
    record = module("battle_end_compare", "verify-vendor-record-origins.py")
    sdk = module("battle_end_cfg", "verify-sdk-origins.py")
    authored = module("battle_end_authored", "verify-authored-origins.py")
    compiler = module("battle_end_sections", "verify-compiler-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in authored.rows("functions.csv")}
    origins = {row["address"]: row for row in authored.rows("function-origins.csv")}
    evidence = {row["address"]: row for row in authored.rows("authored-origin-evidence.csv")}
    function, origin, body_record = functions[ADDRESS], origins[ADDRESS], evidence[ADDRESS]
    address = int(ADDRESS, 16)
    if (int(function["size"]) != 28 or int(function["span_end"], 16) != address + 27
            or origin["origin"] != "authored" or origin["disposition"] != "authored"
            or origin["evidence_id"] != "R097" or body_record["evidence_id"] != "R097"
            or function["owner"] != "authored" or function["proposed_name"] != ROLE
            or body_record["inferred_role"] != ROLE):
        raise ValueError("battle-end destructor origin ledger differs")
    body = comparison.pe_bytes_at(target, address, 28)
    if (hashlib.sha256(body).hexdigest() != body_record["body_sha256"]
            or authored.verify_body(body, address) != (1, 0)):
        raise ValueError("battle-end destructor full extent or CFG differs")
    # These are two observed slots, not a claim about the full vtable or class layout.
    prefix = comparison.pe_bytes_at(target, VTABLE, 8)
    if (hashlib.sha256(prefix).hexdigest() != PREFIX_SHA256
            or struct.unpack("<II", prefix) != (0x00425190, 0x00424F60)
            or not any(base <= VTABLE and VTABLE + 8 <= base + size and flags & 0x40000000
                       and not flags & 0xA0000000 for base, size, flags in compiler.sections(target))):
        raise ValueError("battle-end selected readonly vtable slots differ")
    for key, kind, batch in (("0x00424E00", "authored", "R053"),
                             ("0x00424F60", "authored", "R053"),
                             ("0x00431F40", "authored", "R062"),
                             ("0x00425190", "compiler", "R037")):
        if origins[key]["origin"] != kind or origins[key]["evidence_id"] != batch:
            raise ValueError("battle-end lifetime witness lacks its independent origin")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    for key in ("0x00424E00", "0x00424F60"):
        witness = evidence[key]
        code = comparison.pe_bytes_at(target, int(key, 16), int(witness["size"]))
        if (hashlib.sha256(code).hexdigest() != witness["body_sha256"]
                or authored.verify_body(code, int(key, 16)) != (
                    int(witness["return_count"]), int(witness["internal_branch_count"]))):
            raise ValueError("battle-end constructor/update complete body changed")
        if key == "0x00424E00":
            vtables = [item.operands[1].imm for item in decoder.disasm(code, int(key, 16))
                       if item.mnemonic == "mov" and len(item.operands) == 2
                       and item.operands[0].type == X86_OP_MEM and item.operands[1].type == X86_OP_IMM
                       and 0x00650000 <= item.operands[1].imm < 0x00660000]
            if vtables != [VTABLE]:
                raise ValueError("battle-end constructor does not write the destructor's vtable")
    for filename in ("verify-scene-lifetime-origins.py", "verify-scalar-deleting-origins.py"):
        result = subprocess.run([str(ROOT / "scripts/repo-python"), str(ROOT / "scripts" / filename)],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("battle-end cleanup/deleting witnesses failed replay: " + filename)
    deleting = comparison.pe_bytes_at(target, 0x00425190, 44)
    if 0x00425190 + 15 + struct.unpack_from("<i", deleting, 11)[0] != address:
        raise ValueError("battle-end selected deleting slot does not call this destructor")
    scratch = ROOT / "build/origin-battle-end-destructor-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary) / "VC7BackgroundDestructor.obj"
        result = subprocess.run([str(ROOT / "scripts/compile-probe.sh"),
                                 str(ROOT / "probes/VC7BackgroundDestructor.cpp"), str(path), *background.PROFILE],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 explicit/implicit destructor probe failed")
        source = background.source_definition(path, comparison, reader)
        _, relocations = comparison.object_function(path, background.SYMBOL, 28)
        bindings = [{"offset": 12, "type": "DIR32", "symbol": background.FIELDS[0][2], "addend": 0,
                     "target_address": "0x00657B7C"},
                    {"offset": 20, "type": "REL32", "symbol": background.FIELDS[1][2], "addend": 0,
                     "target_address": "0x00431F40"}]
        record.compare_complete_body(source, relocations, body, address, bindings, comparison, sdk)
    print("Battle-end destructor origin OK: one complete 28-byte authored body; constructor-written "
          "vtable, two checked virtual slots, game cleanup and cold explicit/implicit source witnesses; "
          "name inferred, class layout incomplete, no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
