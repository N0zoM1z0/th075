#!/usr/bin/env python3
"""Verify complete vendor aliases against independently reviewed VC7 families."""
from __future__ import annotations

from collections import Counter
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM


ROOT = Path(__file__).resolve().parents[1]
EXPECTED_FAMILIES = {
    "vector-const-iterator-constructor": ("0x00405A10", 10),
    "deque-iterator-advance": ("0x0041F630", 2),
    "deque-const-iterator-constructor": ("0x0041F6A0", 5),
    "allocator-deallocate": ("0x004050E0", 3),
    "deque-iterator-increment": ("0x00415580", 2),
    "deque-iterator-decrement": ("0x00420130", 1),
    "vector-iterator-advance": ("0x004456A0", 1),
}
ANCHOR_VERIFIERS = (
    "verify-vendor-deque-iterator-advance-origins.py",
    "verify-vendor-deque-const-iterator-origins.py",
    "verify-vendor-deque-algorithm-origins.py",
    "verify-vendor-vector-callee-origins.py",
)


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("vendor_peer_target", "compare-coff-function.py")
    authored = module("vendor_peer_cfg", "verify-authored-origins.py")
    scanner = module("vendor_peer_signature", "scan-origin-candidates.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config/vendor-peer-origin-evidence.json").read_text())
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    base_evidence = {row["address"]: row for row in rows("vendor-origin-evidence.csv")}
    records = manifest["functions"]
    if (manifest["evidence_id"] != "R106" or len(records) != 24
            or len({row["address"] for row in records}) != 24
            or sum(row["size"] for row in records) != 661
            or Counter(row["family"] for row in records)
            != Counter({family: count for family, (_, count) in EXPECTED_FAMILIES.items()})):
        raise ValueError("vendor peer evidence set changed")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    anchor_signatures = {}
    for family, (anchor, _) in EXPECTED_FAMILIES.items():
        origin, function = origins[anchor], functions[anchor]
        size, address = int(function["size"]), int(anchor, 16)
        code = comparison.pe_bytes_at(target, address, size)
        instructions = list(decoder.disasm(code, address))
        authored.verify_body(code, address)
        if (origin["origin"] != "library" or origin["disposition"] != "exclude"
                or function["owner"] != "library" or function["status"] != "excluded"):
            raise ValueError("vendor peer anchor ownership changed: " + anchor)
        if (anchor in base_evidence and base_evidence[anchor]["relocation_bindings"] == "[]"
                and hashlib.sha256(code).hexdigest()
                != base_evidence[anchor]["nonrelocation_sha256"]):
            raise ValueError("relocation-free vendor peer anchor body changed: " + anchor)
        anchor_signatures[family] = scanner.body_signature(code, instructions, address)
    for filename in ANCHOR_VERIFIERS:
        result = subprocess.run(
            [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts" / filename)],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("vendor peer anchor failed cold verification: " + filename)
    for record in records:
        key, family = record["address"], record["family"]
        address, size = int(key, 16), int(record["size"])
        function, origin = functions[key], origins[key]
        code = comparison.pe_bytes_at(target, address, size)
        instructions = list(decoder.disasm(code, address))
        authored.verify_body(code, address)
        calls = [{"site": f"0x{item.address:08X}",
                  "target": f"0x{item.operands[0].imm:08X}"}
                 for item in instructions if item.mnemonic == "call"
                 and item.operands[0].type == X86_OP_IMM]
        indirect = sum(item.mnemonic == "call" and item.operands[0].type != X86_OP_IMM
                       for item in instructions)
        if (family not in EXPECTED_FAMILIES
                or record["anchor"] != EXPECTED_FAMILIES[family][0]
                or int(function["size"]) != size
                or int(function["span_end"], 16) != address + size - 1
                or any(address < int(other, 16) < address + size for other in functions)
                or hashlib.sha256(code).hexdigest() != record["body_sha256"]
                or scanner.body_signature(code, instructions, address) != anchor_signatures[family]
                or calls != record["direct_calls"] or indirect
                or origin["origin"] != "library" or origin["disposition"] != "exclude"
                or origin["evidence_id"] != "R106"
                or function["owner"] != "library" or function["status"] != "excluded"):
            raise ValueError("vendor peer extent, family, calls or ownership changed: " + key)
    print("Vendor peer origins OK: 24 complete bodies / 661 bytes across seven "
          "independently reviewed VC7 families; call destinations retained; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
