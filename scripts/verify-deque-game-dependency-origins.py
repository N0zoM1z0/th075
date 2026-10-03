#!/usr/bin/env python3
"""Cold-check R110 deque dependencies through complete, source-typed game loops."""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
ACCEPTED = {"0x004453C0", "0x00445400", "0x00445530", "0x005F8110",
            "0x005F8290", "0x005F8420", "0x005F8680"}
PARENTS = {"0x0045BA30", "0x005F7D80"}
PROFILE = ["/Od", "/Ob0", "/Gy", "/GR-", "/GX", "/Zi", "/GS", "/I", "src"]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def verify_graph(manifest):
    """A byte-shape match is insufficient without the exact typed, rooted edges."""
    nodes, boundaries = manifest["nodes"], manifest["boundaries"]
    by_address = {r["address"]: r for r in nodes + boundaries}
    if (len(nodes) != 53 or len(boundaries) != 2 or len(by_address) != 55
            or set(manifest["accepted_addresses"]) != ACCEPTED
            or set(manifest["game_parents"]) != PARENTS
            or Counter(r["evidence_role"] for r in nodes)
            != {"accepted": 7, "game_parent": 2, "library_anchor": 44}
            or {r["address"] for r in nodes if r["evidence_role"] == "accepted"} != ACCEPTED
            or {r["address"] for r in nodes if r["evidence_role"] == "game_parent"} != PARENTS
            or sum(r["size"] for r in nodes) != 3207
            or sum(r["size"] for r in nodes if r["evidence_role"] == "accepted") != 501
            or sum(len(r["relocation_bindings"]) for r in nodes) != 85):
        raise ValueError("R110 complete ownership graph differs")
    edges = {}
    for node in nodes:
        edges[node["address"]] = []
        for call in node["relocation_bindings"]:
            callee = by_address.get(call["target_address"])
            if (call["type"] != "REL32" or call["addend"] or callee is None
                    or call["symbol"] != callee["coff_symbol"]):
                raise ValueError("R110 call lacks its exact source-typed callee")
            edges[node["address"]].append(callee["address"])
    visited, pending = set(), list(PARENTS)
    while pending:
        key = pending.pop()
        if key in visited:
            continue
        visited.add(key)
        pending.extend(edges.get(key, []))
    if visited != set(by_address):
        raise ValueError("R110 body lacks an independent source-typed game parent")
    # Preserve prefix/postfix overloads: ++ and -- have identical postfix shapes.
    required = {"0x004453C0": [(11, "0x00445530")],
                "0x00445400": [(27, "0x00445510")],
                "0x005F8420": [(27, "0x005F8D10")],
                "0x005F8290": [(19, "0x005F8D30"), (46, "0x005F8680")]}
    for key, calls in required.items():
        if [(r["offset"], r["target_address"]) for r in by_address[key]["relocation_bindings"]] != calls:
            raise ValueError("R110 default/postfix/erase overload chain differs")
    for key in ("0x00445400", "0x005F8420"):
        symbol = by_address[key]["coff_symbol"]
        callee = by_address[by_address[key]["relocation_bindings"][0]["target_address"]]
        if (not symbol.startswith("??Eiterator@") or not symbol.endswith("QAE?AV012@H@Z")
                or not callee["coff_symbol"].startswith("??Eiterator@")
                or not callee["coff_symbol"].endswith("QAEAAV012@XZ")):
            raise ValueError("R110 postfix increment is confused with another overload")
    if not by_address["0x005F8110"]["coff_symbol"].startswith("?size@?$deque@"):
        raise ValueError("R110 getter lacks its independently typed deque identity")


def check_ledger(row, functions, origins, evidence_only):
    key, size = row["address"], row["size"]
    function, origin = functions[key], origins[key]
    address = int(key, 16)
    if (int(function["size"]) != size or function["span_end"] != row["span_end"]
            or int(row["span_end"], 16) != address + size - 1
            or any(address < int(other, 16) < address + size for other in functions)):
        raise ValueError("R110 full ledger extent differs: " + key)
    if row.get("evidence_role") == "accepted":
        if not evidence_only and (origin["origin"] != "library" or origin["disposition"] != "exclude"
                or origin["evidence_id"] != "R110" or function["owner"] != "library"
                or function["status"] != "excluded" or function["source_file"]
                or function["match_percent"] != "0.00"):
            raise ValueError("R110 acceptance ledger grants incorrect origin/source/exact credit")
    elif row["origin"] != "unknown":
        if (origin["origin"] != row["origin"] or origin["evidence_id"] != row["origin_evidence"]
                or function["owner"] != row["origin"]):
            raise ValueError("R110 independent anchor ownership differs")
    # A frozen unknown context may gain separate evidence in a later review.


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--evidence-only", action="store_true")
    args = parser.parse_args()
    comparison = module("dependency_target", "compare-coff-function.py")
    record = module("dependency_comdat", "verify-vendor-record-origins.py")
    sdk = module("dependency_cfg", "verify-sdk-origins.py")
    context = module("dependency_context", "verify-game-context-origins.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config/deque-game-dependency-origin-evidence.json").read_text())
    if (manifest["evidence_id"] != "R110" or manifest["profile"] != PROFILE
            or manifest["target_sha256"] != hashlib.sha256(target).hexdigest()
            or manifest["probe"] != "probes/VC7GameDequeDependencies.cpp"):
        raise ValueError("R110 target or reproducibility profile differs")
    probe = ROOT / manifest["probe"]
    if hashlib.sha256(probe.read_bytes()).hexdigest() != manifest["probe_sha256"]:
        raise ValueError("R110 independent natural source probe differs")
    for filename, expected in manifest["vendor_headers"].items():
        path = ROOT / ".tools/msvc710/Vc7/include" / filename
        if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            raise ValueError("R110 pinned vendor header differs")
    verify_graph(manifest)
    functions = {r["address"]: r for r in record.rows("functions.csv")}
    origins = {r["address"]: r for r in record.rows("function-origins.csv")}
    # Independent game ownership and the entire original policies are rechecked.
    result = subprocess.run([str(ROOT / "scripts/repo-python"),
                             str(ROOT / "scripts/verify-game-context-origins.py")],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("R109 complete game-parent evidence failed: " + result.stderr[-1000:])
    scratch = ROOT / "build/origin-deque-game-dependency-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7GameDequeDependencies.obj"
        result = subprocess.run([str(ROOT / "scripts/compile-probe.sh"), str(probe),
                                 str(object_path), *PROFILE],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("R110 pinned VC7 cold build failed: " + result.stdout[-1000:])
        data = object_path.read_bytes()
        for row in manifest["nodes"]:
            check_ledger(row, functions, origins, args.evidence_only)
            key, size = row["address"], row["size"]
            source_size = record.complete_aux_section_size(data, row["coff_symbol"], comparison.coff_name)
            source, relocations = comparison.object_function(object_path, row["coff_symbol"], source_size)
            actual = comparison.pe_bytes_at(target, int(key, 16), size)
            if (size != source_size or hashlib.sha256(source).hexdigest() != row["source_sha256"]
                    or hashlib.sha256(actual).hexdigest() != row["body_sha256"]):
                raise ValueError("R110 complete source/target bytes differ: " + key)
            indirect = record.compare_complete_body(source, relocations, actual, int(key, 16),
                                                    row["relocation_bindings"], comparison, sdk)
            if indirect != row["indirect_call_count"]:
                raise ValueError("R110 complete control flow differs")
        for row in manifest["boundaries"]:
            check_ledger(row, functions, origins, args.evidence_only)
            actual = comparison.pe_bytes_at(target, int(row["address"], 16), row["size"])
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or context.verify_bounded_context(actual, int(row["address"], 16), row["external_tails"])
                    != row["cfg"]):
                raise ValueError("R110 independent/unknown boundary context differs")
    print("R110 deque game dependencies OK: 7 new library bodies / 501 bytes; "
          "53 complete cold source bodies / 3207 bytes / 85 typed calls; "
          "two bounded external contexts; no game source, layout, or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
