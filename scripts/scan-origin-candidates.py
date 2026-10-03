#!/usr/bin/env python3
"""Batch origin triage from full extents and reviewed context; never accept origins."""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
import hashlib
import importlib.util
import json
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM


ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def body_signature(code, instructions, address):
    """Normalize only complete direct-call fields, retaining each exact destination."""
    normalized = bytearray(code)
    calls = []
    for instruction in instructions:
        if instruction.mnemonic != "call":
            continue
        if (len(instruction.operands) != 1 or instruction.operands[0].type != X86_OP_IMM
                or instruction.imm_size != 4):
            # Indirect dispatch and every data/vtable field stay byte-identical.
            continue
        offset = instruction.address - address + instruction.imm_offset
        if offset < 0 or offset + 4 > len(code):
            raise ValueError("batch signature call field exceeds complete extent")
        normalized[offset:offset + 4] = bytes(4)
        calls.append((offset, instruction.operands[0].imm))
    digest = hashlib.sha256(normalized).hexdigest()
    return digest + ":" + json.dumps(calls, separators=(",", ":"))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", default=".analysis/origin-scan/latest.json")
    args = parser.parse_args()
    output = (ROOT / args.output).resolve()
    if not output.is_relative_to((ROOT / ".analysis").resolve()) or output.suffix != ".json":
        raise ValueError("batch origin report must be private JSON below .analysis/")
    comparison = module("origin_scan_target", "compare-coff-function.py")
    authored = module("origin_scan_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in authored.rows("functions.csv")}
    origins = {row["address"]: row for row in authored.rows("function-origins.csv")}
    if set(functions) != set(origins):
        raise ValueError("batch origin ledger address sets differ")
    remaps = defaultdict(list)
    directs = defaultdict(list)
    for row in authored.rows("authored-origin-switches.csv"):
        remaps[row["address"]].append(row)
    for row in authored.rows("authored-origin-direct-switches.csv"):
        directs[row["address"]].append(row)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded = {}
    callers = defaultdict(list)
    families = defaultdict(list)
    addresses = sorted(int(key, 16) for key in functions)
    for key, function in functions.items():
        address, size = int(key, 16), int(function["size"])
        code = comparison.pe_bytes_at(target, address, size)
        instructions = list(decoder.disasm(code, address))
        error = ""
        try:
            next_index = bisect_right(addresses, address)
            if (int(function["span_end"], 16) != address + size - 1
                    or (next_index < len(addresses) and addresses[next_index] < address + size)):
                raise ValueError("extent overlaps another candidate or span differs")
            counts = authored.verify_body(
                code, address, remaps[key],
                lambda pointer, extent: comparison.pe_bytes_at(target, pointer, extent), directs[key])
        except ValueError as exc:
            error = str(exc)
            counts = None
        calls = [{"site": f"0x{item.address:08X}", "target": f"0x{item.operands[0].imm:08X}"}
                 for item in instructions if item.mnemonic == "call"
                 and item.operands[0].type == X86_OP_IMM]
        indirect = sum(item.mnemonic == "call" and item.operands[0].type != X86_OP_IMM
                       for item in instructions)
        signature = body_signature(code, instructions, address) if not error else None
        record = {"address": key, "size": size, "role": function["proposed_name"],
                  "origin": origins[key]["origin"], "origin_evidence": origins[key]["evidence_id"],
                  "body_sha256": hashlib.sha256(code).hexdigest(), "complete_cfg": counts,
                  "extent_question": error, "calls": calls, "indirect_calls": indirect,
                  "signature": signature}
        decoded[key] = record
        if signature is not None:
            families[signature].append(key)
            # Data/table misdecoding cannot supply a reviewed caller witness.
            for call in calls:
                callers[call["target"]].append({"parent": key, "site": call["site"],
                                                 "origin": origins[key]["origin"]})
    pending = []
    for key, record in decoded.items():
        if origins[key]["origin"] != "unknown":
            continue
        call_kinds = Counter(origins.get(row["target"], {}).get("origin", "unmapped")
                             for row in record["calls"])
        parents = callers[key]
        reviewed_parents = [row for row in parents if row["origin"] != "unknown"]
        peers = [peer for peer in families.get(record["signature"], []) if peer != key]
        reviewed_peers = [peer for peer in peers if origins[peer]["origin"] != "unknown"]
        if record["extent_question"]:
            lane = "reconcile-extent"
        elif reviewed_peers and record["size"] >= 24:
            lane = "whole-reviewed-peer"
        elif record["calls"] and set(call_kinds) == {"authored"}:
            lane = ("game-callees-and-parent" if any(row["origin"] == "authored" for row in parents)
                    else "game-callees")
        elif reviewed_parents and any(row["origin"] == "authored" for row in parents):
            lane = "game-parent"
        elif reviewed_parents:
            lane = "vendor-or-compiler-parent"
        else:
            lane = "unresolved-context"
        pending.append({**record, "lane": lane, "call_origins": dict(call_kinds),
                        "reviewed_parents": reviewed_parents, "pending_peer_addresses": [
                            peer for peer in peers if origins[peer]["origin"] == "unknown"],
                        "pending_parents": [row for row in parents
                                            if row["origin"] == "unknown"],
                        "reviewed_peers": [{"address": peer, "origin": origins[peer]["origin"],
                                             "role": functions[peer]["proposed_name"]}
                                            for peer in reviewed_peers]})
    groups = [{"signature": signature, "pending": [key for key in keys
                                                      if origins[key]["origin"] == "unknown"],
               "reviewed": [key for key in keys if origins[key]["origin"] != "unknown"]}
              for signature, keys in families.items()
              if len(keys) > 1 and any(origins[key]["origin"] == "unknown" for key in keys)]
    groups.sort(key=lambda row: (-len(row["pending"]), row["pending"][0]))
    report = {"result": "diagnostic-only", "target_sha256": hashlib.sha256(target).hexdigest(),
              "ledger_sha256": {name: hashlib.sha256((ROOT / "config" / name).read_bytes()).hexdigest()
                                for name in ("functions.csv", "function-origins.csv")},
              "pending_count": len(pending), "lanes": dict(Counter(row["lane"] for row in pending)),
              "candidates": pending, "whole_body_groups": groups,
              "limitations": ["A shape, caller or known callee is triage, not origin acceptance.",
                              "Provisional spans require independent source/control-flow reconciliation.",
                              "Only direct-call fields are normalized; exact destinations and RET remain.",
                              "No ledgers, database, source presence or exact credit are changed."]}
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"Batch origin triage: {len(pending)} pending candidates; diagnostic only.")
    for lane, count in sorted(report["lanes"].items()):
        print(f"  {lane}: {count}")
    print(f"Whole-body groups with pending members: {len(groups)}; private report: {output.relative_to(ROOT)}")
    for group in groups[:8]:
        print(f"  group: {len(group['pending'])} pending, {len(group['reviewed'])} reviewed; "
              f"first pending {group['pending'][0]}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
