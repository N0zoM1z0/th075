#!/usr/bin/env python3
"""Replay whole short game policies and their independently reviewed context."""
from __future__ import annotations

import hashlib
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM


ROOT = Path(__file__).resolve().parents[1]
COHORTS = {
    "R100": ("short-game-origin-evidence.json", 12, 780, 27),
    "R102": ("batch-game-origin-evidence.json", 17, 2051, 33),
    "R103": ("batch-state-origin-evidence.json", 33, 2600, 22),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def check_calls(instructions, recorded, origins):
    actual = [(f"0x{item.address:08X}", f"0x{item.operands[0].imm:08X}")
              for item in instructions if item.mnemonic == "call"
              and item.operands[0].type == X86_OP_IMM]
    expected = [(row["site"], row["target"]) for row in recorded]
    if actual != expected or any(origins.get(key, {}).get("origin") != "authored"
                                 for _, key in actual):
        raise ValueError("short game direct calls differ or lack reviewed game ownership")


def check_readonly_float32(row, target, comparison, sections, decoded):
    """Bind each observed scalar to complete readonly storage and actual uses."""
    pointer = int(row["address"], 16)
    if (comparison.pe_bytes_at(target, pointer, 4) != struct.pack("<f", row["value"])
            or not any(base <= pointer and pointer + 4 <= base + size and flags & 0x40000000
                       and not flags & 0xA0000000 for base, size, flags in sections)
            or not row["uses"]):
        raise ValueError("short game float scalar lacks complete readonly target storage")
    for use in row["uses"]:
        instruction = next((item for item in decoded[use["address"]]
                            if f"0x{item.address:08X}" == use["site"]), None)
        if instruction is None or not any(
                operand.type == X86_OP_MEM and operand.size == 4
                and not operand.mem.base and not operand.mem.index
                and operand.mem.disp == pointer for operand in instruction.operands):
            raise ValueError("short game float scalar lacks its full-width instruction binding")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cohort", choices=COHORTS, default="R100")
    args = parser.parse_args()
    batch = args.cohort
    filename, expected_count, expected_bytes, expected_anchors = COHORTS[batch]
    comparison = module("short_game_target", "compare-coff-function.py")
    authored = module("short_game_cfg", "verify-authored-origins.py")
    imports_module = module("short_game_imports", "verify-import-origins.py")
    compiler = module("short_game_sections", "verify-compiler-origins.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config" / filename).read_text())
    records = manifest["functions"]
    keys = {row["address"] for row in records}
    if (manifest["evidence_id"] != batch or len(records) != expected_count or len(keys) != expected_count
            or sum(row["size"] for row in records) != expected_bytes):
        raise ValueError("short game origin cohort differs")
    functions = {row["address"]: row for row in authored.rows("functions.csv")}
    origins = {row["address"]: row for row in authored.rows("function-origins.csv")}
    evidence = {row["address"]: row for row in authored.rows("authored-origin-evidence.csv")}
    if {key for key, row in evidence.items() if row["evidence_id"] == batch} != keys:
        raise ValueError("short game authored evidence cohort differs")
    # Replay complete extents and guarded tables of previously reviewed game context.
    if authored.main() != 0:
        raise ValueError("short game authored context failed complete replay")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    imports = imports_module.pe_imports(target, comparison)
    sections = compiler.sections(target)
    decoded = {}
    remaps = authored.rows("authored-origin-switches.csv")
    directs = authored.rows("authored-origin-direct-switches.csv")
    anchors = manifest["anchors"]
    if len(anchors) != expected_anchors or len({row["address"] for row in anchors}) != len(anchors):
        raise ValueError("short game independent anchor cohort differs")
    for anchor in anchors:
        key = anchor["address"]
        function, origin = functions[key], origins[key]
        address = int(key, 16)
        size = anchor["size"]
        if (key in keys or origin["origin"] != "authored"
                or origin["evidence_id"] != anchor["origin_evidence"]
                or function["proposed_name"] != anchor["role"]
                or int(function["size"]) != size
                or int(function["span_end"], 16) != address + size - 1):
            raise ValueError("short game independent owner anchor differs")
        code = comparison.pe_bytes_at(target, address, size)
        if hashlib.sha256(code).hexdigest() != anchor["body_sha256"]:
            raise ValueError("short game complete anchor body differs")
        if "exact_unit" in anchor:
            # SetBlendMode's complete COMDAT includes its eight-entry jump table.
            # Replay all 495 bytes and typed table relocations, never a code-only prefix.
            with (ROOT / "config/match-units.toml").open("rb") as stream:
                units = tomllib.load(stream)["units"]
            unit = units[anchor["exact_unit"]]
            if unit["target_address"] != address or unit["size"] != size:
                raise ValueError("short game exact context unit has a different full extent")
            result = subprocess.run([str(ROOT / "scripts/repo-python"),
                                     str(ROOT / "scripts/replay-exact-units.py"),
                                     "--unit", anchor["exact_unit"]],
                                    cwd=ROOT, capture_output=True, text=True)
            if result.returncode:
                raise ValueError("short game whole switch context failed cold replay")
        else:
            authored.verify_body(code, address,
                                 [row for row in remaps if row["address"] == key],
                                 lambda pointer, extent: comparison.pe_bytes_at(target, pointer, extent),
                                 [row for row in directs if row["address"] == key])
        decoded[key] = list(decoder.disasm(code, address))
    for record in records:
        key = record["address"]
        address, size = int(key, 16), record["size"]
        function, origin, body_record = functions[key], origins[key], evidence[key]
        if (record["evidence_id"] != batch or origin["evidence_id"] != batch
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or function["owner"] != "authored" or function["status"] != "unclassified"
                or function["proposed_name"] != record["role"]
                or body_record["inferred_role"] != record["role"]
                or int(function["size"]) != size
                or int(function["span_end"], 16) != address + size - 1
                or any(address < int(other["address"], 16) < address + size
                       for other in functions.values())):
            raise ValueError("short game function origin or full extent differs")
        code = comparison.pe_bytes_at(target, address, size)
        if (hashlib.sha256(code).hexdigest() != record["body_sha256"]
                or record["body_sha256"] != body_record["body_sha256"]
                or authored.verify_body(code, address) !=
                (record["return_count"], record["internal_branch_count"])):
            raise ValueError("short game complete body or CFG differs")
        instructions = list(decoder.disasm(code, address))
        decoded[key] = instructions
        check_calls(instructions, record["direct_calls"], origins)
        if any(row["target"] not in decoded and row["target"] not in keys
               for row in record["direct_calls"]):
            raise ValueError("short game call lacks a complete independent anchor")
        indirect = [item for item in instructions if item.mnemonic == "call"
                    and item.operands[0].type != X86_OP_IMM]
        if [(f"0x{item.address:08X}", item.op_str) for item in indirect] != [
                (row["site"], row["operand"]) for row in record["indirect_calls"]]:
            raise ValueError("short game virtual/import dispatch differs")
        for instruction, row in zip(indirect, record["indirect_calls"]):
            if "iat_slot" in row:
                slot = int(row["iat_slot"], 16)
                operand = instruction.operands[0]
                if (operand.type != X86_OP_MEM or operand.mem.base or operand.mem.index
                        or operand.size != 4 or operand.mem.disp != slot
                        or imports.get(slot) != (row["dll"], row["symbol"])):
                    raise ValueError("short game IAT call lacks raw PE import identity")
        by_site = {f"0x{item.address:08X}": item for item in instructions}
        for witness in record["instruction_witnesses"]:
            instruction = by_site[witness["site"]]
            if (instruction.mnemonic, instruction.op_str) != (
                    witness["mnemonic"], witness["operands"]):
                raise ValueError("short game policy field or literal differs")
    for edge in manifest["parent_calls"]:
        parent = decoded[edge["parent"]]
        actual = [f"0x{item.address:08X}" for item in parent if item.mnemonic == "call"
                  and item.operands[0].type == X86_OP_IMM
                  and item.operands[0].imm == int(edge["child"], 16)]
        if actual != edge["sites"] or not actual:
            raise ValueError("short game complete parent lacks its recorded child call")
    callback = manifest.get("callback")
    if callback:
        installer = {f"0x{item.address:08X}": item for item in decoded[callback["installer"]]}
        push = installer[callback["site"]]
        if (callback["target"] not in keys or push.mnemonic != "push"
                or push.operands[0].type != X86_OP_IMM
                or push.operands[0].imm != int(callback["target"], 16)):
            raise ValueError("short game installer does not bind the complete present callback")
    for peer in manifest.get("whole_body_peers", []):
        scanner = module("short_game_peer_signature", "scan-origin-candidates.py")
        signatures = []
        for key in (peer["address"], peer["reviewed_address"]):
            function = functions[key]
            code = comparison.pe_bytes_at(target, int(key, 16), int(function["size"]))
            signatures.append(scanner.body_signature(code, decoded[key], int(key, 16)))
        if peer["address"] not in keys or peer["reviewed_address"] in keys or signatures[0] != signatures[1]:
            raise ValueError("short game whole reviewed peer differs outside typed direct-call fields")
    # Only selected slots are observed; this does not assert a full game vtable layout.
    for row in manifest["virtual_slots"]:
        slot = int(row["address"], 16)
        if (row["target"] not in keys
                or struct.unpack("<I", comparison.pe_bytes_at(target, slot, 4))[0]
                != int(row["target"], 16)
                or not any(base <= slot and slot + 4 <= base + size and flags & 0x40000000
                           and not flags & 0xA0000000 for base, size, flags in sections)):
            raise ValueError("short game selected readonly virtual slot differs")
    for row in manifest["strings"]:
        pointer = int(row["address"], 16)
        literal = row["value"].encode("ascii") + b"\0"
        if comparison.pe_bytes_at(target, pointer, len(literal)) != literal:
            raise ValueError("short game resource/log literal differs")
    for row in manifest.get("readonly_float32", []):
        if any(use["address"] not in keys for use in row["uses"]):
            raise ValueError("short game float scalar use falls outside the cohort")
        check_readonly_float32(row, target, comparison, sections, decoded)
    print(f"Short game origins {batch} OK: {expected_count} whole authored bodies / {expected_bytes} bytes; "
          f"{expected_anchors} independently reviewed "
          "whole anchors and complete call/parent/policy contexts; "
          "names/layouts inferred, no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
