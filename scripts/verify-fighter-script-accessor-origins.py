#!/usr/bin/env python3
"""Verify the fighter script initializer and three field-accessor origins."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_EAX


ROOT = Path(__file__).resolve().parents[1]
CASES = {
    "0x00420440": (130, 3, "FighterScript::InitializeAt00420440"),
    "0x00420530": (53, 0, "FighterScript::GetByteFieldAt00420530"),
    "0x00420570": (55, 0, "FighterScript::GetWordFieldAt00420570"),
    "0x004205B0": (54, 0, "FighterScript::GetDwordFieldAt004205B0"),
}
FIELDS = {
    "0x00420530": (0, 1),
    "0x00420570": (2, 2),
    "0x004205B0": (4, 4),
}
CALLERS = {
    "0x004567B0": {0x00420440},
    "0x0045CE10": {0x00420530, 0x00420570, 0x004205B0},
    "0x0045D810": {0x00420530, 0x00420570, 0x004205B0},
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def calls(instructions):
    return {item.operands[0].imm for item in instructions
            if item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM}


def main():
    comparison = module("fighter_access_target", "compare-coff-function.py")
    authored = module("fighter_access_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")
                if row["evidence_id"] == "R076"}
    if set(evidence) != set(CASES):
        raise ValueError("fighter script accessor evidence set changed")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    for key, (size, branches, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or int(function["span_end"], 16) != address + size - 1
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R076" or function["owner"] != "authored"):
            raise ValueError("fighter script accessor ledger differs: " + key)
        body = comparison.pe_bytes_at(target, address, size)
        counts = authored.verify_body(body, address, (),
                                      lambda pointer, extent: comparison.pe_bytes_at(
                                          target, pointer, extent))
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("fighter script accessor body or CFG differs: " + key)
        instructions = list(decoder.disasm(body, address))
        if key == "0x00420440":
            by_address = {item.address: item for item in instructions}
            bound = by_address[0x00420493]
            store = by_address[0x004204A2]
            if (not {0x004214E0, 0x004216D0} <= calls(instructions)
                    or bound.mnemonic != "cmp" or bound.operands[1].imm != 1000
                    or store.mnemonic != "mov" or store.operands[0].type != X86_OP_MEM
                    or store.operands[0].size != 2 or store.operands[1].imm & 0xFFFF != 0xFFFF
                    or sum(item.mnemonic == "add" and len(item.operands) == 2
                           and item.operands[1].type == X86_OP_IMM
                           and item.operands[1].imm == 0x7D0 for item in instructions) != 2):
                raise ValueError("fighter script initializer sentinel policy differs")
        else:
            displacement, width = FIELDS[key]
            fields = [item.operands[1] for item in instructions
                      if item.mnemonic == "mov" and len(item.operands) == 2
                      and item.operands[1].type == X86_OP_MEM
                      and item.operands[1].mem.base == X86_REG_EAX
                      and item.operands[1].mem.disp == displacement
                      and item.operands[1].size == width]
            if (len(fields) != 1
                    or not {0x00421570, 0x00421360} <= calls(instructions)):
                raise ValueError("fighter script field lookup or width differs: " + key)
    for key, required in CALLERS.items():
        if origins[key]["origin"] != "authored":
            raise ValueError("fighter script caller lost authored origin")
        address = int(key, 16)
        body = comparison.pe_bytes_at(target, address, int(functions[key]["size"]))
        if not required <= calls(decoder.disasm(body, address)):
            raise ValueError("fighter script caller edge differs: " + key)
    print("Fighter script accessor origins OK: four complete authored bodies / "
          "292 bytes; 1,000-slot sentinel initialization, three field widths and "
          "reviewed fighter caller edges; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
