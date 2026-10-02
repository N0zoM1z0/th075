#!/usr/bin/env python3
"""Verify a repeated complete game background transform/copy body."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
BASE = "0x00449CE0"


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(name):
    with (ROOT / "config" / name).open(newline="") as stream:
        return list(csv.DictReader(stream))


def normalized_body(body, address, decoder):
    instructions = list(decoder.disasm(body, address))
    if sum(item.size for item in instructions) != 91:
        raise ValueError("background transform body does not decode completely")
    calls = [item for item in instructions if item.mnemonic == "call"]
    if (len(calls) != 2 or [item.operands[0].imm for item in calls
            if len(item.operands) == 1 and item.operands[0].type == X86_OP_IMM]
            != [0x004115C0, 0x004116F0]):
        raise ValueError("background transform calls differ")
    normalized = bytearray(body)
    for item in calls:
        if item.imm_size != 4:
            raise ValueError("background transform call field is not REL32")
        offset = item.address - address + item.imm_offset
        normalized[offset:offset + 4] = bytes(4)
    return bytes(normalized)


def main():
    comparison = module("background_transform_target", "compare-coff-function.py")
    authored = module("background_transform_authored", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    records = rows("background-transform-origin-evidence.csv")
    if len(records) != 32 or len({row["address"] for row in records}) != 32 or BASE not in {row["address"] for row in records}:
        raise ValueError("background transform cohort is incomplete or duplicated")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    normalized_base = None
    for row in sorted(records, key=lambda record: record["address"]):
        key = row["address"]
        address = int(key, 16)
        function, origin, body_record = functions[key], origins[key], evidence[key]
        if (row["evidence_id"] != "R056" or origin["evidence_id"] != "R056"
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or body_record["evidence_id"] != "R056" or int(function["size"]) != 91
                or function["proposed_name"] != body_record["inferred_role"]):
            raise ValueError("background transform witness/ledger mismatch")
        body = comparison.pe_bytes_at(target, address, 91)
        if hashlib.sha256(body).hexdigest() != body_record["body_sha256"]:
            raise ValueError("background transform complete target body differs")
        authored.verify_body(body, address)
        normalized = normalized_body(body, address, decoder)
        if key == BASE:
            normalized_base = normalized
        elif normalized != normalized_base:
            raise ValueError("background transform differs outside both call fields")
    print("Background transform origins OK: 32 complete 91-byte bodies, "
          "same non-call bytes and two checked game calls; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
