#!/usr/bin/env python3
"""Verify complete guarded combat reaction dispatchers and their call edge."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
CASES = {
    "0x004439A0": (1185, 27, "BattleCombat::ApplyHitResponseAt004439A0"),
    "0x00455140": (944, 66, "BattleCombat::SelectHitResponseAt00455140"),
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
    comparison = module("combat_reaction_target", "compare-coff-function.py")
    authored = module("combat_reaction_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")
                if row["evidence_id"] == "R069"}
    remapped = [row for row in rows("authored-origin-switches.csv")
                if row["evidence_id"] == "R069"]
    direct = [row for row in rows("authored-origin-direct-switches.csv")
              if row["evidence_id"] == "R069"]
    if (set(evidence) != set(CASES) or len(remapped) != 1 or len(direct) != 1
            or remapped[0]["address"] != "0x004439A0"
            or direct[0]["address"] != "0x00455140"):
        raise ValueError("combat reaction cohort or switch records differ")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    for key, (size, branches, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R069" or function["owner"] != "authored"):
            raise ValueError("combat reaction ledger differs: " + key)
        body = comparison.pe_bytes_at(target, address, size)
        counts = authored.verify_body(
            body, address, [row for row in remapped if row["address"] == key],
            lambda pointer, extent: comparison.pe_bytes_at(target, pointer, extent),
            [row for row in direct if row["address"] == key])
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("combat reaction body/CFG differs: " + key)
        if key == "0x004439A0":
            calls = {item.operands[0].imm for item in decoder.disasm(body, address)
                     if item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM}
            if 0x00455140 not in calls:
                raise ValueError("hit response dispatcher call edge differs")
    if (int(remapped[0]["remap_size"]) != 31 or int(remapped[0]["table_size"]) != 36
            or int(direct[0]["table_size"]) != 16):
        raise ValueError("combat reaction complete switch extents differ")
    print("Combat reaction origins OK: two complete authored bodies / 2,129 bytes; "
          "two guarded switches, 13 table entries and 31 remap bytes; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
