#!/usr/bin/env python3
"""Verify complete custom background constructors and paired sprite drawers."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]


def module(name: str, path: str):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(name: str):
    with (ROOT / "config" / name).open(newline="") as stream:
        return list(csv.DictReader(stream))


def direct_calls(instructions):
    return [item.operands[0].imm for item in instructions
            if item.mnemonic == "call" and len(item.operands) == 1
            and item.operands[0].type == X86_OP_IMM]


def literal_string(target, comparison, address):
    if not 0x00650000 <= address < 0x00660000:
        return None
    try:
        data = comparison.pe_bytes_at(target, address, 80)
    except ValueError:
        return None
    result = data.split(b"\0", 1)[0]
    if not result or len(result) == len(data):
        return None
    try:
        return result.decode("ascii")
    except UnicodeDecodeError:
        return None


def verify_witness(record, body, target, comparison, decoder):
    address = int(record["address"], 16)
    instructions = list(decoder.disasm(body, address))
    if not instructions or sum(item.size for item in instructions) != len(body):
        raise ValueError("incomplete background body: " + record["address"])
    calls = direct_calls(instructions)
    if record["kind"] == "asset-constructor":
        if not record["asset_path"].startswith("data\\background\\BG"):
            raise ValueError("background witness lacks a BG asset name")
        if calls.count(0x00449DE0) != 1 or calls.count(0x0040BB80) != 1:
            raise ValueError("background constructor lacks base/asset calls")
        strings = [literal_string(target, comparison, item.operands[0].imm)
                   for item in instructions if item.mnemonic == "push"
                   and len(item.operands) == 1 and item.operands[0].type == X86_OP_IMM]
        paths = [string for string in strings
                 if string and string.startswith("data\\background\\BG")
                 and string.endswith(".dat")]
        if paths != [record["asset_path"]]:
            raise ValueError("background constructor asset path differs")
    elif record["kind"] == "side-pair-drawer":
        if record["asset_path"] or calls.count(0x0040CA80) != 2 or calls.count(0x006406AC) != 2:
            raise ValueError("background side-pair drawing calls differ")
    else:
        raise ValueError("unknown background witness kind")


def main():
    comparison = module("background_target", "compare-coff-function.py")
    authored = module("background_authored", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    witnesses = rows("background-origin-evidence.csv")
    if len(witnesses) != 52 or len({row["address"] for row in witnesses}) != 52:
        raise ValueError("background witness cohort is incomplete or duplicated")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    totals = {"asset-constructor": 0, "side-pair-drawer": 0}
    for row in witnesses:
        key = row["address"]
        origin, function, body_record = origins[key], functions[key], evidence[key]
        if (row["evidence_id"] != "R055" or origin["evidence_id"] != "R055"
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or body_record["evidence_id"] != "R055"
                or function["proposed_name"] != body_record["inferred_role"]):
            raise ValueError("background witness/ledger origin mismatch")
        expected_role = ("BackgroundStage::Load" + row["asset_path"].rsplit("\\", 1)[-1][:-4]
                         if row["kind"] == "asset-constructor" else
                         "BackgroundStage::DrawSidePairAt" + key[2:])
        if function["proposed_name"] != expected_role:
            raise ValueError("background role differs from observed asset or address")
        address = int(key, 16)
        body = comparison.pe_bytes_at(target, address, int(function["size"]))
        if hashlib.sha256(body).hexdigest() != body_record["body_sha256"]:
            raise ValueError("background whole-body hash mismatch")
        authored.verify_body(body, address)
        verify_witness(row, body, target, comparison, decoder)
        totals[row["kind"]] += 1
    if totals != {"asset-constructor": 34, "side-pair-drawer": 18}:
        raise ValueError("background family counts differ")
    print("Background origins OK: 34 asset constructors, 18 side-pair drawers; "
          "52 complete authored bodies, no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
