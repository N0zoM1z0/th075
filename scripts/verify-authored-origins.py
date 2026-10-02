#!/usr/bin/env python3
"""Recheck recorded authored extents and CFG; semantic ownership stays manual."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP, CS_GRP_RET
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("authored_switches", ROOT / "scripts/authored_switches.py")
SWITCHES = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SWITCHES)


def verify_body(code, address, switches=(), read=None):
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, address))
    if (not instructions or sum(item.size for item in instructions) != len(code)
            or not instructions[-1].group(CS_GRP_RET)):
        raise ValueError("authored extent is incomplete or lacks its final RET")
    starts = {item.address for item in instructions}
    switch_targets = SWITCHES.verify_switches(code, address, switches, read) if switches else {}
    jumps = [item for item in instructions if item.group(CS_GRP_JUMP)]
    for jump in jumps:
        if jump.address in switch_targets:
            continue
        if (not jump.operands or jump.operands[0].type != X86_OP_IMM
                or jump.operands[0].imm not in starts):
            raise ValueError("unresolved authored jump or external/shared tail")
    return sum(item.group(CS_GRP_RET) for item in instructions), len(jumps)


def rows(name):
    with (ROOT / "config" / name).open() as stream:
        return list(csv.DictReader(stream))


def main():
    spec = importlib.util.spec_from_file_location("authored_coff", ROOT / "scripts/compare-coff-function.py")
    comparison = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(comparison)
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = rows("authored-origin-evidence.csv")
    switches = {}
    switch_path = ROOT / "config/authored-origin-switches.csv"
    if switch_path.exists():
        for row in rows("authored-origin-switches.csv"):
            switches.setdefault(row["address"], []).append(row)
    if not evidence or len({row["address"] for row in evidence}) != len(evidence):
        raise ValueError("empty or duplicate authored origin evidence")
    if set(switches) - {row["address"] for row in evidence}:
        raise ValueError("orphan authored switch evidence")
    total = 0
    for row in evidence:
        key, size = row["address"], int(row["size"])
        origin, function = origins[key], functions[key]
        if (size <= 0 or int(function["size"]) != size
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != row["evidence_id"]
                or function["proposed_name"] != row["inferred_role"]):
            raise ValueError("authored origin ledger differs from recorded evidence")
        code = comparison.pe_bytes_at(target, int(key, 16), size)
        if hashlib.sha256(code).hexdigest() != row["body_sha256"]:
            raise ValueError("authored target body hash mismatch: " + key)
        for switch in switches.get(key, []):
            if switch["evidence_id"] != row["evidence_id"]:
                raise ValueError("authored switch origin batch differs from body evidence")
        counts = verify_body(code, int(key, 16), switches.get(key, []),
                             lambda address, extent: comparison.pe_bytes_at(target, address, extent))
        if (counts != (int(row["return_count"]), int(row["internal_branch_count"]))
                or int(row["external_branch_count"]) != 0):
            raise ValueError("authored complete CFG metadata mismatch: " + key)
        total += size
    print(f"Authored origin extents OK: {len(evidence)} bodies, {total} bytes; "
          "semantic ownership is documented separately; no reconstruction exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
