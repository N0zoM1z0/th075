#!/usr/bin/env python3
"""Verify whole game effect forwarders, fixed transforms and observed x86 cleanup."""
from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM


ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def check_return(instructions, expected):
    last = instructions[-1]
    if (last.mnemonic != "ret" or len(last.operands) != 1
            or last.operands[0].type != X86_OP_IMM or last.operands[0].imm != expected):
        raise ValueError("effect forwarder RET cleanup differs; unused parameters cannot be folded")


def check_policy(instructions, row):
    texts = [f"{item.mnemonic} {item.op_str}" for item in instructions]
    if row["manager_instruction"] and row["manager_instruction"] not in texts:
        raise ValueError("effect forwarder game manager field differs")
    if row["kind"] == "transform":
        pushes = [item.operands[0].imm for item in instructions if item.mnemonic == "push"
                  and item.operands[0].type == X86_OP_IMM]
        colors = [item.operands[1].imm & 0xFFFFFFFF for item in instructions
                  if item.mnemonic == "mov" and len(item.operands) == 2
                  and item.operands[0].type == X86_OP_MEM and item.operands[0].size == 4
                  and item.operands[1].type == X86_OP_IMM]
        if (pushes != [0, 0x3E99999A, 0x3F800000, 0, 0, 0, 0, 0, 0x43200000, 0, 0, 0]
                or colors != [int(row["colour"], 16)]
                or "mov ecx, 0x21" not in texts
                or sum(item.mnemonic == "rep movsd" for item in instructions) != 1):
            raise ValueError("fixed game transform parameters, 132-byte copy or color differs")
    elif row["kind"] == "midpoint":
        required = {"mov edx, dword ptr [ecx + 0x38]", "add edx, dword ptr [eax + 0x40]",
                    "mov edx, dword ptr [ecx + 0x34]", "add edx, dword ptr [eax + 0x3c]"}
        if (not required <= set(texts)
                or texts.count("fdiv dword ptr [0x657480]") != 2):
            raise ValueError("game midpoint coordinate pairs or divisor fields differ")
    elif row["kind"] == "spawn":
        if "add eax, " + row["argument_pointer_offset"].lower() not in texts:
            raise ValueError("effect forwarder argument-owner field differs")
    else:
        raise ValueError("unknown effect forwarder policy")


def main():
    comparison = module("effect_forwarder_target", "compare-coff-function.py")
    authored = module("effect_forwarder_cfg", "verify-authored-origins.py")
    compiler = module("effect_forwarder_sections", "verify-compiler-origins.py")
    edges = module("effect_forwarder_calls", "verify-short-game-origins.py")
    target = comparison.verified_target()
    records = authored.rows("effect-forwarder-origin-evidence.csv")
    context = json.loads((ROOT / "config/effect-forwarder-origin-context.json").read_text())
    keys = {row["address"] for row in records}
    if (len(records) != 11 or len(keys) != 11 or sum(int(row["size"]) for row in records) != 814
            or context["evidence_id"] != "R101"):
        raise ValueError("effect forwarder origin cohort differs")
    functions = {row["address"]: row for row in authored.rows("functions.csv")}
    origins = {row["address"]: row for row in authored.rows("function-origins.csv")}
    evidence = {row["address"]: row for row in authored.rows("authored-origin-evidence.csv")}
    if {key for key, row in evidence.items() if row["evidence_id"] == "R101"} != keys:
        raise ValueError("effect forwarder authored evidence cohort differs")
    if authored.main() != 0:
        raise ValueError("effect forwarder complete authored context failed replay")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded = {}
    anchors = context["anchors"]
    if len(anchors) != 8 or len({row["address"] for row in anchors}) != 8:
        raise ValueError("effect forwarder independent anchor cohort differs")
    for anchor in anchors:
        key = anchor["address"]
        function, origin, body_record = functions[key], origins[key], evidence[key]
        if (key in keys or origin["origin"] != "authored"
                or origin["evidence_id"] != anchor["origin_evidence"]
                or function["proposed_name"] != anchor["role"]
                or int(function["size"]) != anchor["size"]
                or body_record["body_sha256"] != anchor["body_sha256"]):
            raise ValueError("effect forwarder anchor lacks independent full game evidence")
        code = comparison.pe_bytes_at(target, int(key, 16), anchor["size"])
        if hashlib.sha256(code).hexdigest() != anchor["body_sha256"]:
            raise ValueError("effect forwarder complete anchor body differs")
        decoded[key] = list(decoder.disasm(code, int(key, 16)))
    for row in records:
        key, address, size = row["address"], int(row["address"], 16), int(row["size"])
        function, origin, body_record = functions[key], origins[key], evidence[key]
        if (row["evidence_id"] != "R101" or origin["evidence_id"] != "R101"
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or function["owner"] != "authored" or function["status"] != "unclassified"
                or function["proposed_name"] != row["inferred_role"]
                or body_record["inferred_role"] != row["inferred_role"]
                or int(function["size"]) != size
                or int(function["span_end"], 16) != address + size - 1
                or any(address < int(other["address"], 16) < address + size
                       for other in functions.values())):
            raise ValueError("effect forwarder origin or complete extent differs")
        code = comparison.pe_bytes_at(target, address, size)
        if (hashlib.sha256(code).hexdigest() != row["body_sha256"]
                or row["body_sha256"] != body_record["body_sha256"]
                or authored.verify_body(code, address) != (1, 0)):
            raise ValueError("effect forwarder complete body or CFG differs")
        instructions = list(decoder.disasm(code, address))
        decoded[key] = instructions
        calls = [item for item in instructions if item.mnemonic == "call"]
        callees = row["callees"].split(";")
        if len(calls) != len(callees) or any(key not in decoded for key in callees):
            raise ValueError("effect forwarder callee lacks complete independent context")
        edges.check_calls(instructions, [{"site": f"0x{item.address:08X}", "target": callee}
                                        for item, callee in zip(calls, callees)], origins)
        check_return(instructions, int(row["return_pop"]))
        check_policy(instructions, row)
    for edge in context["parent_calls"]:
        sites = [f"0x{item.address:08X}" for item in decoded[edge["parent"]]
                 if item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM
                 and item.operands[0].imm == int(edge["child"], 16)]
        if sites != edge["sites"] or not sites:
            raise ValueError("effect forwarder parent call lacks full game owner context")
    sections = compiler.sections(target)
    for row in context["virtual_slots"]:
        slot = int(row["address"], 16)
        if (row["target"] not in keys
                or struct.unpack("<I", comparison.pe_bytes_at(target, slot, 4))[0]
                != int(row["target"], 16)
                or not any(base <= slot and slot + 4 <= base + size and flags & 0x40000000
                           and not flags & 0xA0000000 for base, size, flags in sections)):
            raise ValueError("effect forwarder selected readonly virtual slot differs")
    # Complete observed float divisor; no inferred data owner or global layout credit.
    if (struct.unpack("<f", comparison.pe_bytes_at(target, 0x00657480, 4))[0] != 2.0
            or not any(base <= 0x00657480 and 0x00657484 <= base + size
                       and flags & 0x40000000 and not flags & 0xA0000000
                       for base, size, flags in sections)):
        raise ValueError("effect midpoint divisor lacks its full readonly float value")
    print("Effect forwarder origins OK: 11 whole authored bodies / 814 bytes; eight whole game "
          "anchors, explicit transform/spawn policies, selected virtual slots and distinct RET cleanup; "
          "names/layouts inferred, no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
