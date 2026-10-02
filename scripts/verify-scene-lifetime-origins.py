#!/usr/bin/env python3
"""Verify complete scene-lifetime bodies and their game-specific bindings."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
CASES = {
    "0x00431F40": ("SceneBase::ReleaseGameGlobalsAt00431F40", 0x00657B88,
                   {0x00417430}, None),
    "0x00438BA0": ("StaffRollScene::DestroyAt00438BA0", 0x006582BC,
                   {0x00425460, 0x00431F40}, "0x00438AC0"),
    "0x0043A1E0": ("TitleScene::DestroyAt0043A1E0", 0x00658308,
                   {0x00425460, 0x00431F40}, "0x0043A020"),
    "0x0043B5D0": ("BattleScene::PresentAt0043B5D0", None,
                   {0x004028F0}, None),
}
CALLEE_EVIDENCE = {
    0x00417430: ("authored", "R052"),
    0x00425460: ("compiler", "R037"),
    0x00431F40: ("authored", "R062"),
    0x004028F0: ("authored", "F002"),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("scene_target", "compare-coff-function.py")
    authored = module("scene_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    if {key for key, row in evidence.items() if row["evidence_id"] == "R062"} != set(CASES):
        raise ValueError("scene lifecycle cohort differs")
    for key, (role, vtable, expected_calls, constructor) in CASES.items():
        address = int(key, 16)
        function, origin, record = functions[key], origins[key], evidence[key]
        if (origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R062" or function["owner"] != "authored"
                or function["proposed_name"] != role or record["inferred_role"] != role
                or int(function["size"]) != int(record["size"])):
            raise ValueError("scene lifecycle ledger differs")
        body = comparison.pe_bytes_at(target, address, int(function["size"]))
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or authored.verify_body(body, address) != (
                    int(record["return_count"]), int(record["internal_branch_count"]))):
            raise ValueError("scene lifecycle complete body or CFG differs")
        instructions = list(decoder.disasm(body, address))
        calls = {item.operands[0].imm for item in instructions
                 if item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM}
        vtables = {item.operands[1].imm for item in instructions
                   if item.mnemonic == "mov" and len(item.operands) == 2
                   and item.operands[0].type == X86_OP_MEM
                   and item.operands[1].type == X86_OP_IMM
                   and 0x00650000 <= item.operands[1].imm < 0x00660000}
        if calls != expected_calls or vtables != ({vtable} if vtable else set()):
            raise ValueError("scene lifecycle vtable or direct calls differ")
        for callee in expected_calls:
            callee_key = f"0x{callee:08X}"
            expected_origin, expected_evidence = CALLEE_EVIDENCE[callee]
            if (origins[callee_key]["origin"] != expected_origin
                    or not origins[callee_key]["evidence_id"].startswith(expected_evidence)):
                raise ValueError("scene lifecycle call target lacks independent origin")
        if constructor:
            ctor = evidence[constructor]
            ctor_address = int(constructor, 16)
            ctor_body = comparison.pe_bytes_at(target, ctor_address, int(ctor["size"]))
            ctor_vtables = {item.operands[1].imm for item in decoder.disasm(ctor_body, ctor_address)
                            if item.mnemonic == "mov" and len(item.operands) == 2
                            and item.operands[0].type == X86_OP_MEM
                            and item.operands[1].type == X86_OP_IMM
                            and 0x00650000 <= item.operands[1].imm < 0x00660000}
            if (hashlib.sha256(ctor_body).hexdigest() != ctor["body_sha256"]
                    or authored.verify_body(ctor_body, ctor_address) != (
                        int(ctor["return_count"]), int(ctor["internal_branch_count"]))
                    or origins[constructor]["origin"] != "authored"
                    or ctor_vtables != {vtable}):
                raise ValueError("scene constructor does not bind the destructor vtable")
        if key == "0x0043A1E0":
            globals_written = {item.operands[0].mem.disp for item in instructions
                               if item.mnemonic == "mov" and item.operands[0].type == X86_OP_MEM}
            if 0x00671630 not in globals_written:
                raise ValueError("title scene no longer publishes its selected value")
    print("Scene lifecycle origins OK: four complete authored bodies, "
          "two constructor-bound vtables, reviewed cleanup/present calls and "
          "title-state write; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
