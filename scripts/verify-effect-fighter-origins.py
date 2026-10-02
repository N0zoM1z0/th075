#!/usr/bin/env python3
"""Recheck complete effect and fighter origin bodies and their owner bindings."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
CASES = {
    "0x005F71F0": (1722, 20, "Effects::LoadPatternCatalogAt005F71F0"),
    "0x005F78B0": (487, 9, "Effects::SpawnAuxObjectAt005F78B0"),
    "0x005F7AA0": (602, 9, "Effects::SpawnConfiguredAuxObjectAt005F7AA0"),
    "0x005C3FB0": (874, 24, "SuikaFighter::UpdateSpecialStateAt005C3FB0"),
    "0x0059B490": (679, 18, "YukariFighter::UpdateSpecialStateAt0059B490"),
    "0x004F4170": (855, 26, "CharacterProjectile::AdvanceAt004F4170"),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("effect_fighter_target", "compare-coff-function.py")
    authored = module("effect_fighter_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")
                if row["evidence_id"] == "R067"}
    if set(evidence) != set(CASES):
        raise ValueError("effect/fighter cohort differs")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    for key, (size, branches, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R067" or function["owner"] != "authored"):
            raise ValueError("effect/fighter origin ledger differs: " + key)
        body = comparison.pe_bytes_at(target, address, size)
        counts = authored.verify_body(body, address)
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("effect/fighter body or complete CFG differs: " + key)
        calls = {item.operands[0].imm for item in decoder.disasm(body, address)
                 if item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM}
        if key == "0x005F71F0":
            literal = b"data\\system\\effect\\effect.pat\0"
            if (literal not in target or 0x0041D750 not in calls
                    or origins["0x0041D750"]["origin"] != "authored"):
                raise ValueError("effect catalog literal/archive binding differs")
        if key in ("0x005F78B0", "0x005F7AA0") and (
                0x005FAB10 not in calls
                or origins["0x005FAB10"]["origin"] != "authored"):
            raise ValueError("auxiliary object constructor binding differs")
        if key in ("0x005C3FB0", "0x0059B490"):
            vtable = 0x00659E30 if key == "0x005C3FB0" else 0x00659CC0
            slot = struct.unpack("<I", comparison.pe_bytes_at(target, vtable + 19 * 4, 4))[0]
            if slot != address:
                raise ValueError("fighter vtable slot 19 differs: " + key)
    print("Effect/fighter origins OK: six complete authored bodies / 5,219 bytes; "
          "effect archive, auxiliary constructor and two fighter vtable bindings; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
