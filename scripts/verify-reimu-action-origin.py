#!/usr/bin/env python3
"""Verify the complete Reimu action-state body, switches, and fighter slot."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
ADDRESS = 0x0045DD70
CONSTRUCTOR = 0x0046D080
VTABLE = 0x006590D8
SWITCH_SITES = {0x0045DDCB, 0x0045DE05, 0x0045DE42,
                0x0045DE78, 0x0045DEB8, 0x0045DEE2}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("reimu_target", "compare-coff-function.py")
    authored = module("reimu_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    key, ctor_key = f"0x{ADDRESS:08X}", f"0x{CONSTRUCTOR:08X}"
    record, function, origin = evidence[key], functions[key], origins[key]
    if (origin["origin"] != "authored" or origin["disposition"] != "authored"
            or origin["evidence_id"] != "R063" or function["owner"] != "authored"
            or function["proposed_name"] != record["inferred_role"]
            or not record["inferred_role"].startswith("ReimuFighter::")
            or int(function["size"]) != 60999 or int(record["size"]) != 60999):
        raise ValueError("Reimu action extent or ledger differs")
    switches = [row for row in rows("authored-origin-switches.csv")
                if row["address"] == key]
    direct = [row for row in rows("authored-origin-direct-switches.csv")
              if row["address"] == key]
    if (len(switches) != 4 or len(direct) != 2
            or {int(row["jump_site"], 16) for row in switches + direct} != SWITCH_SITES
            or any(row["evidence_id"] != "R063" for row in switches + direct)):
        raise ValueError("Reimu switch cohort differs")
    body = comparison.pe_bytes_at(target, ADDRESS, 60999)
    if hashlib.sha256(body).hexdigest() != record["body_sha256"]:
        raise ValueError("Reimu complete target body differs")
    counts = authored.verify_body(
        body, ADDRESS, switches,
        lambda address, size: comparison.pe_bytes_at(target, address, size), direct)
    if counts != (1, 1690) or counts != (
            int(record["return_count"]), int(record["internal_branch_count"])):
        raise ValueError("Reimu complete control flow differs")
    ctor = evidence[ctor_key]
    ctor_body = comparison.pe_bytes_at(target, CONSTRUCTOR, int(ctor["size"]))
    if (origins[ctor_key]["origin"] != "authored"
            or origins[ctor_key]["evidence_id"] != "R046"
            or hashlib.sha256(ctor_body).hexdigest() != ctor["body_sha256"]
            or authored.verify_body(ctor_body, CONSTRUCTOR) != (
                int(ctor["return_count"]), int(ctor["internal_branch_count"]))):
        raise ValueError("Reimu constructor independent evidence differs")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    vtables = {item.operands[1].imm for item in decoder.disasm(ctor_body, CONSTRUCTOR)
               if item.mnemonic == "mov" and len(item.operands) == 2
               and item.operands[0].type == X86_OP_MEM
               and item.operands[1].type == X86_OP_IMM
               and 0x00650000 <= item.operands[1].imm < 0x00660000}
    slots = comparison.pe_bytes_at(target, VTABLE, 8)
    if vtables != {VTABLE} or struct.unpack_from("<I", slots, 4)[0] != ADDRESS:
        raise ValueError("Reimu constructor vtable slot 1 differs")
    fighter_vtables = {}
    for witness in rows("fighter-virtual-origin-evidence.csv"):
        pair = witness["vtable_address"], witness["constructor_address"]
        previous = fighter_vtables.setdefault(pair[0], pair[1])
        if previous != pair[1]:
            raise ValueError("fighter vtable has conflicting constructors")
    if len(fighter_vtables) != 11:
        raise ValueError("eleven fighter vtables are required")
    action_addresses = set()
    action_bytes = 0
    for vtable_key, constructor_key in fighter_vtables.items():
        constructor_record = evidence[constructor_key]
        constructor_address = int(constructor_key, 16)
        constructor_body = comparison.pe_bytes_at(
            target, constructor_address, int(constructor_record["size"]))
        written = {item.operands[1].imm for item in decoder.disasm(
            constructor_body, constructor_address)
                   if item.mnemonic == "mov" and len(item.operands) == 2
                   and item.operands[0].type == X86_OP_MEM
                   and item.operands[1].type == X86_OP_IMM
                   and 0x00650000 <= item.operands[1].imm < 0x00660000}
        if (origins[constructor_key]["origin"] != "authored"
                or constructor_record["evidence_id"] not in ("R046", "R050")
                or hashlib.sha256(constructor_body).hexdigest() != constructor_record["body_sha256"]
                or written != {int(vtable_key, 16)}):
            raise ValueError("fighter action constructor witness differs")
        pointer = comparison.pe_bytes_at(target, int(vtable_key, 16), 8)
        action_address = struct.unpack_from("<I", pointer, 4)[0]
        action_key = f"0x{action_address:08X}"
        action_record = evidence[action_key]
        action_body = comparison.pe_bytes_at(
            target, action_address, int(action_record["size"]))
        if (action_key in action_addresses or origins[action_key]["origin"] != "authored"
                or action_record["evidence_id"] not in ("R048", "R063")
                or hashlib.sha256(action_body).hexdigest() != action_record["body_sha256"]):
            raise ValueError("fighter action slot lacks its complete authored body")
        action_addresses.add(action_key)
        action_bytes += len(action_body)
    if key not in action_addresses or action_bytes != 613391:
        raise ValueError("eleven fighter action dispatchers differ")
    print("Reimu action origin OK: one complete 60,999-byte authored body, "
          "six guarded switch tables, 1,690 internal branches and eleven "
          "fighter action slots totaling 613,391 bytes; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
