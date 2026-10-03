#!/usr/bin/env python3
"""Replay R109 game policies with independently reviewed and unresolved context."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
KEYS = {"0x0041C130", "0x0041CF00", "0x00428D60", "0x0042B110", "0x0042B1F0",
        "0x004491E0", "0x00452B30", "0x00455580", "0x0045BA30", "0x0045BC30",
        "0x0045BCE0", "0x005F7D00", "0x005F7D80"}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def verify_bounded_context(code, address, tails):
    """Check whole context bytes without granting ownership to an unresolved tail."""
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, address))
    if not instructions or sum(i.size for i in instructions) != len(code):
        raise ValueError("context extent has an incomplete instruction")
    starts = {i.address for i in instructions}
    observed = []
    jumps = [i for i in instructions if i.group(CS_GRP_JUMP)]
    for jump in jumps:
        if len(jump.operands) != 1 or jump.operands[0].type != X86_OP_IMM:
            raise ValueError("context has an unresolved computed jump")
        destination = jump.operands[0].imm
        if address <= destination < address + len(code) and destination not in starts:
            raise ValueError("context branch enters a partial instruction")
        if destination not in starts:
            observed.append({"site": f"0x{jump.address:08X}", "target": f"0x{destination:08X}"})
    if observed != tails:
        raise ValueError("context external tails differ")
    if instructions[-1].mnemonic not in ("ret", "jmp"):
        raise ValueError("context extent has unresolved trailing fallthrough")
    return [sum(i.mnemonic == "ret" for i in instructions), len(jumps) - len(observed)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--evidence-only", action="store_true", help="verify target evidence before accepting ledgers")
    args = parser.parse_args()
    comparison = module("context_target", "compare-coff-function.py")
    authored = module("context_authored", "verify-authored-origins.py")
    lifetime = module("context_facts", "verify-game-lifetime-origins.py")
    short = module("context_scalars", "verify-short-game-origins.py")
    compiler = module("context_sections", "verify-compiler-origins.py")
    imports_module = module("context_imports", "verify-import-origins.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config/game-context-origin-evidence.json").read_text())
    records, anchors = manifest["functions"], manifest["anchors"]
    if (manifest["evidence_id"] != "R109" or manifest["target_sha256"] != hashlib.sha256(target).hexdigest()
            or len(records) != 13 or {r["address"] for r in records} != KEYS
            or sum(r["size"] for r in records) != 2465 or len(anchors) != 51
            or len({r["address"] for r in anchors}) != 51 or len(manifest["parent_calls"]) != 11
            or sum(len(r["instruction_witnesses"]) for r in records) != 157):
        raise ValueError("R109 game policy cohort differs")
    functions = {r["address"]: r for r in authored.rows("functions.csv")}
    origins = {r["address"]: r for r in authored.rows("function-origins.csv")}
    evidence = {r["address"]: r for r in authored.rows("authored-origin-evidence.csv")}
    switches = authored.rows("authored-origin-switches.csv")
    directs = authored.rows("authored-origin-direct-switches.csv")
    sections = compiler.sections(target)
    imports = imports_module.pe_imports(target, comparison)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded = {}
    for row in records + anchors:
        key = row["address"]
        address, size = int(key, 16), row["size"]
        function = functions[key]
        if (int(function["size"]) != size or function["span_end"] != row["span_end"]
                or int(row["span_end"], 16) != address + size - 1
                or any(address < int(k, 16) < address + size for k in functions)):
            raise ValueError("game policy/context full ledger extent differs: " + key)
        code = comparison.pe_bytes_at(target, address, size)
        if hashlib.sha256(code).hexdigest() != row["body_sha256"]:
            raise ValueError("game policy/context whole target hash differs: " + key)
        if key in KEYS or row["origin"] == "authored":
            if row["external_tails"]:
                raise ValueError("game ownership has an unresolved external tail")
            cfg = list(authored.verify_body(code, address, [r for r in switches if r["address"] == key],
                                           lambda a, n: comparison.pe_bytes_at(target, a, n),
                                           [r for r in directs if r["address"] == key]))
        else:
            cfg = verify_bounded_context(code, address, row["external_tails"])
        if cfg != row["cfg"]:
            raise ValueError("game policy/context full CFG differs: " + key)
        decoded[key] = list(decoder.disasm(code, address))
        if key not in KEYS:
            # Unknown snapshots freeze context; they do not restrict later independent review.
            if row["origin"] != "unknown" and (origins[key]["origin"] != row["origin"]
                    or origins[key]["evidence_id"] != row["origin_evidence"]
                    or not authored.role_matches(function, row["role"])):
                raise ValueError("independently reviewed game context ownership differs")
            continue
        facts = lifetime.body_facts(decoded[key])
        if facts["returns"] != row["returns"]:
            raise ValueError("game policy RET cleanup differs")
        calls = [{"site": r["site"], "target": r["target"]} for r in row["direct_calls"]]
        if facts["direct_calls"] != calls or any(
                r["target"] not in {a["address"] for a in anchors} | KEYS for r in calls):
            raise ValueError("game policy direct calls lack their full context")
        for call in row["direct_calls"]:
            if call["origin"] != "unknown" and origins[call["target"]]["origin"] != call["origin"]:
                raise ValueError("game policy callee ownership differs")
        indirect = [i for i in decoded[key] if i.mnemonic == "call" and i.operands[0].type != X86_OP_IMM]
        if [(f"0x{i.address:08X}", i.op_str) for i in indirect] != [(r["site"], r["operand"]) for r in row["indirect_calls"]]:
            raise ValueError("game policy import/virtual call differs")
        for instruction, call in zip(indirect, row["indirect_calls"]):
            if "iat_slot" in call:
                slot = int(call["iat_slot"], 16)
                op = instruction.operands[0]
                if (op.type != X86_OP_MEM or op.mem.base or op.mem.index or op.size != 4
                        or op.mem.disp != slot or imports.get(slot) != (call["dll"], call["symbol"])):
                    raise ValueError("game policy import lacks its raw PE identity")
        by_site = {f"0x{i.address:08X}": i for i in decoded[key]}
        for witness in row["instruction_witnesses"]:
            instruction = by_site[witness["site"]]
            if (instruction.mnemonic, instruction.op_str) != (witness["mnemonic"], witness["operands"]):
                raise ValueError("game policy object/global field or literal differs")
        if not args.evidence_only:
            body_record = evidence[key]
            if (origins[key]["origin"] != "authored" or origins[key]["disposition"] != "authored"
                    or origins[key]["evidence_id"] != "R109" or function["owner"] != "authored"
                    or not authored.role_matches(function, row["role"])
                    or body_record["evidence_id"] != "R109" or body_record["body_sha256"] != row["body_sha256"]
                    or body_record["inferred_role"] != row["role"]):
                raise ValueError("R109 game policy accepted ledger differs")
    for edge in manifest["parent_calls"]:
        actual = [r["site"] for r in lifetime.body_facts(decoded[edge["parent"]])["direct_calls"]
                  if r["target"] == edge["child"]]
        if not set(edge["sites"]) <= set(actual) or not edge["sites"]:
            raise ValueError("complete reviewed game parent lacks its policy call")
    for row in manifest["virtual_slots"]:
        address = int(row["address"], 16)
        writes = lifetime.body_facts(decoded[row["constructor"]])["vtable_writes"]
        if (row["target"] not in decoded or origins[row["target"]]["origin"] != "authored"
                or not any(r["target"] == row["vtable"] for r in writes)
                or struct.unpack("<I", comparison.pe_bytes_at(target, address, 4))[0] != int(row["target"], 16)
                or not any(a <= address and address + 4 <= a + n and flags & 0x40000000
                           and not flags & 0xA0000000 for a, n, flags in sections)):
            raise ValueError("scene constructor vtable lacks its reviewed selected game slot")
    for row in manifest["readonly_float32"]:
        short.check_readonly_float32(row, target, comparison, sections, decoded)
    for row in manifest["strings"]:
        literal = row["value"].encode("ascii") + b"\0"
        if comparison.pe_bytes_at(target, int(row["address"], 16), len(literal)) != literal:
            raise ValueError("whole game resource literal differs")
    if not args.evidence_only and authored.main() != 0:
        raise ValueError("previously accepted authored context failed replay")
    print("R109 game context origins OK: 13 complete authored policies / 2465 bytes, 51 complete "
          "context bodies, 11 parent edges, 157 policy witnesses, raw PE imports, four scene slots "
          "and four readonly scalars; unresolved callees/tails retain their independent origins; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
