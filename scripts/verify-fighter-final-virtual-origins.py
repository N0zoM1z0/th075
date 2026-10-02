#!/usr/bin/env python3
"""Verify the remaining two playable-fighter vtable origin decisions."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
CASES = {
    "0x00453D80": (149, 0, "FighterBase::BindAnimationAt00453D80"),
    "0x004E62A0": (256, 8, "AliceFighter::UpdateSpecialStateAt004E62A0"),
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
    comparison = module("fighter_final_target", "compare-coff-function.py")
    authored = module("fighter_final_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")
                if row["evidence_id"] == "R068"}
    if set(evidence) != set(CASES):
        raise ValueError("fighter final-virtual cohort differs")
    for key, (size, branches, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R068" or function["owner"] != "authored"):
            raise ValueError("fighter final-virtual ledger differs: " + key)
        body = comparison.pe_bytes_at(target, address, size)
        counts = authored.verify_body(body, address)
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("fighter final-virtual body/CFG differs: " + key)
    vtables = {int(row["vtable_address"], 16) for row in
               rows("fighter-virtual-origin-evidence.csv")}
    if len(vtables) != 11:
        raise ValueError("playable fighter vtable count differs")
    for base in vtables:
        slot0 = struct.unpack("<I", comparison.pe_bytes_at(target, base, 4))[0]
        if slot0 != 0x00453D80:
            raise ValueError("shared fighter slot zero differs")
    alice_slot19 = struct.unpack("<I", comparison.pe_bytes_at(
        target, 0x00659608 + 19 * 4, 4))[0]
    if alice_slot19 != 0x004E62A0:
        raise ValueError("Alice fighter slot 19 differs")
    print("Final fighter virtual origins OK: two complete authored bodies / 405 bytes; "
          "all eleven slot-0 pointers and Alice slot 19 bound; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
