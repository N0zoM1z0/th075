#!/usr/bin/env python3
"""Verify complete fighter script loading and parser origin evidence."""
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
    "0x004205F0": (217, 5, "FighterScript::LoadArchiveEntryAt004205F0"),
    "0x00420880": (2301, 63, "FighterScript::ParseAt00420880"),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def direct_calls(decoder, body, address):
    return {item.operands[0].imm for item in decoder.disasm(body, address)
            if item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM}


def main():
    comparison = module("fighter_script_target", "compare-coff-function.py")
    authored = module("fighter_script_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")
                if row["evidence_id"] == "R070"}
    switches = [row for row in rows("authored-origin-switches.csv")
                if row["evidence_id"] == "R070"]
    if (set(evidence) != set(CASES) or len(switches) != 1
            or switches[0]["address"] != "0x00420880"
            or switches[0]["jump_site"] != "0x004208D7"
            or int(switches[0]["remap_size"]) != 100
            or int(switches[0]["table_size"]) != 28):
        raise ValueError("fighter script cohort or bounded switch differs")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    for key, (size, branches, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R070" or function["owner"] != "authored"):
            raise ValueError("fighter script ledger differs: " + key)
        body = comparison.pe_bytes_at(target, address, size)
        counts = authored.verify_body(
            body, address, switches if address == 0x00420880 else (),
            lambda pointer, extent: comparison.pe_bytes_at(target, pointer, extent))
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("fighter script body or CFG differs: " + key)
        calls = direct_calls(decoder, body, address)
        if address == 0x004205F0 and not {0x0041D800, 0x00420880} <= calls:
            raise ValueError("archive loader or parser call edge differs")
        if address == 0x00420880 and 0x00641DE0 not in calls:
            raise ValueError("script token comparisons differ")
    if (origins["0x0041D800"]["origin"] != "authored"
            or origins["0x004206D0"]["origin"] != "authored"
            or origins["0x00456B60"]["origin"] != "authored"):
        raise ValueError("reviewed archive, file loader or fighter owner is missing")
    file_loader = comparison.pe_bytes_at(target, 0x004206D0,
                                         int(functions["0x004206D0"]["size"]))
    if 0x00420880 not in direct_calls(decoder, file_loader, 0x004206D0):
        raise ValueError("reviewed file loader does not call script parser")
    fighter_loader = comparison.pe_bytes_at(target, 0x00456B60,
                                            int(functions["0x00456B60"]["size"]))
    instructions = list(decoder.disasm(fighter_loader, 0x00456B60))
    pushed = {item.operands[0].imm for item in instructions
              if item.mnemonic == "push" and item.operands[0].type == X86_OP_IMM}
    literal = b"data\\character\\%s\\%s.sce\0"
    if (0x00658F78 not in pushed
            or comparison.pe_bytes_at(target, 0x00658F78, len(literal)) != literal
            or not {0x004205F0, 0x004206D0} <= direct_calls(
                decoder, fighter_loader, 0x00456B60)):
        raise ValueError("fighter script filename or loader bindings differ")
    print("Fighter script origins OK: two complete authored bodies / 2,518 bytes; "
          "100-byte guarded remap, seven table entries and reviewed .sce owner calls; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
