#!/usr/bin/env python3
"""Cold-check complete VC7 deque erase graphs and their source-typed helpers."""
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
PROFILE = ["/Od", "/Ob0", "/Gy", "/GR-", "/GX", "/Zi", "/GS", "/I", "src"]
RANGES = {"0x0041E380", "0x0041E800", "0x00424000", "0x00455D30", "0x0045C100"}
WRAPPERS = {"0x0041DC90": ("0x0041EE20", "0x0041E380"),
            "0x0041DF10": ("0x0041ECC0", "0x0041E800"),
            "0x00423EF0": ("0x004244C0", "0x00424000"),
            "0x0045C0A0": ("0x0045C5D0", "0x0045C100")}
CHILDREN = {"0x004143D0", "0x00414400", "0x00415560"}
ACCEPTED = RANGES | set(WRAPPERS) | CHILDREN
RANGE_CALL_OFFSETS = [17, 26, 41, 60, 67, 100, 116, 144, 168, 192, 220, 242, 249]
RANGE_CALL_FAMILIES = ["?begin", "??Giterator", "??Giterator", "?end", "??Giterator",
                       "?begin", "??$copy_backward", "?pop_front", "?end", "??$copy",
                       "?pop_back", "?begin", "??Hiterator"]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def typed_bindings(relocations, canonical, nodes):
    """Bind every source alternative to the same complete target graph."""
    if len(relocations) != len(canonical):
        raise ValueError("deque erase source alternative changes relocation count")
    result = []
    for source, recorded in zip(relocations, canonical):
        if (source["type"] != "REL32" or source["addend"]
                or (source["offset"], source["type"], source["addend"])
                != (recorded["offset"], recorded["type"], recorded["addend"])):
            raise ValueError("deque erase source alternative changes a typed call field")
        callee = nodes.get(recorded["target_address"])
        if callee is None or source["symbol"] not in callee["matching_symbols"]:
            raise ValueError("deque erase call lacks its whole source-typed callee")
        result.append({"offset": source["offset"], "type": source["type"],
                       "symbol": source["symbol"], "addend": source["addend"],
                       "target_address": recorded["target_address"]})
    return result


def verify_graph(manifest):
    nodes = manifest["nodes"]
    by_address = {n["address"]: n for n in nodes}
    if (len(nodes) != 129 or len(by_address) != 129
            or set(manifest["accepted_addresses"]) != ACCEPTED
            or set(manifest["root_addresses"]) != RANGES | set(WRAPPERS)
            or Counter(n["evidence_role"] for n in nodes) != {"accepted": 12, "anchor": 117}
            or {n["address"] for n in nodes if n["evidence_role"] == "accepted"} != ACCEPTED
            or sum(n["size"] for n in nodes) != 7958
            or sum(n["size"] for n in nodes if n["evidence_role"] == "accepted") != 1654
            or sum(len(n["relocation_bindings"]) for n in nodes) != 203
            or sum(len(n["matching_symbols"]) for n in nodes) != 337):
        raise ValueError("R111 complete erase evidence cohort differs")
    edges = {}
    for node in nodes:
        symbols = node["matching_symbols"]
        if (symbols != sorted(set(symbols)) or node["coff_symbol"] not in symbols
                or node["family_key"] != node["coff_symbol"].split("@", 1)[0]
                or any(s.split("@", 1)[0] != node["family_key"] for s in symbols)):
            raise ValueError("deque erase complete source alternatives cross method families")
        bindings = node["relocation_bindings"]
        if typed_bindings(bindings, bindings, by_address) != bindings:
            raise ValueError("deque erase canonical typed calls differ")
        edges[node["address"]] = [b["target_address"] for b in bindings]
    for key in RANGES:
        node = by_address[key]
        if (node["size"] != 262 or node["family_key"] != "?erase"
                or any(not s.endswith("QAE?AViterator@12@V312@0@Z") for s in node["matching_symbols"])
                or [b["offset"] for b in node["relocation_bindings"]] != RANGE_CALL_OFFSETS
                or [by_address[b["target_address"]]["family_key"] for b in node["relocation_bindings"]]
                != RANGE_CALL_FAMILIES):
            raise ValueError("deque range erase lacks both complete copy/pop paths")
    for key, (addition, erase) in WRAPPERS.items():
        node = by_address[key]
        if (node["size"] != 59 or node["family_key"] != "?erase"
                or any(not s.endswith("QAE?AViterator@12@V312@@Z") for s in node["matching_symbols"])
                or [(b["offset"], b["target_address"]) for b in node["relocation_bindings"]]
                != [(19, addition), (46, erase)]
                or by_address[addition]["family_key"] != "??Hiterator"):
            raise ValueError("single erase lacks its complete addition/range-erase witnesses")
    for key, field, callee, family in (("0x004143D0", 22, "0x00415560", "?begin"),
                                       ("0x00414400", 28, "0x00415560", "?end"),
                                       ("0x00415560", 19, "0x00415E60", "??0iterator")):
        node = by_address[key]
        if (node["family_key"] != family
                or [(b["offset"], b["target_address"]) for b in node["relocation_bindings"]] != [(field, callee)]):
            raise ValueError("byte deque short helper lacks its complete typed constructor chain")
    reachable, pending = set(), list(RANGES | set(WRAPPERS))
    while pending:
        key = pending.pop()
        if key in reachable:
            continue
        reachable.add(key)
        pending.extend(edges[key])
    if reachable != set(by_address):
        raise ValueError("deque erase helper is not rooted in a complete library parent")


def check_ledger(row, functions, origins, evidence_only):
    key, size = row["address"], row["size"]
    function, origin = functions[key], origins[key]
    address = int(key, 16)
    if (int(function["size"]) != size or function["span_end"] != row["span_end"]
            or int(row["span_end"], 16) != address + size - 1
            or any(address < int(other, 16) < address + size for other in functions)):
        raise ValueError("deque erase full ledger extent differs: " + key)
    if row["evidence_role"] == "accepted":
        if function["source_file"] or function["match_percent"] != "0.00":
            raise ValueError("deque erase origin probe cannot grant source/exact credit")
        if not evidence_only and (origin["origin"] != "library" or origin["disposition"] != "exclude"
                or origin["evidence_id"] != "R111" or function["owner"] != "library"
                or function["status"] != "excluded"):
            raise ValueError("deque erase acceptance origin ledger differs")
    elif (row["origin"] != "library" or origin["origin"] != "library"
            or origin["evidence_id"] != row["origin_evidence"] or function["owner"] != "library"):
        raise ValueError("deque erase independent anchor ownership differs")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--evidence-only", action="store_true")
    args = parser.parse_args()
    comparison = module("erase_target", "compare-coff-function.py")
    record = module("erase_extent", "verify-vendor-record-origins.py")
    sdk = module("erase_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config/vendor-deque-erase-origins.json").read_text())
    if (manifest["evidence_id"] != "R111" or manifest["profile"] != PROFILE
            or manifest["target_sha256"] != hashlib.sha256(target).hexdigest()
            or manifest["probe"] != "probes/VC7DequeErase.cpp"):
        raise ValueError("R111 target or source profile differs")
    probe = ROOT / manifest["probe"]
    if hashlib.sha256(probe.read_bytes()).hexdigest() != manifest["probe_sha256"]:
        raise ValueError("R111 independent source probe differs")
    for filename, expected in manifest["vendor_headers"].items():
        if hashlib.sha256((ROOT / ".tools/msvc710/Vc7/include" / filename).read_bytes()).hexdigest() != expected:
            raise ValueError("R111 pinned vendor header differs")
    verify_graph(manifest)
    by_address = {n["address"]: n for n in manifest["nodes"]}
    functions = {r["address"]: r for r in record.rows("functions.csv")}
    origins = {r["address"]: r for r in record.rows("function-origins.csv")}
    scratch = ROOT / "build/origin-deque-erase-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DequeErase.obj"
        result = subprocess.run([str(ROOT / "scripts/compile-probe.sh"), str(probe),
                                 str(object_path), *PROFILE],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("R111 pinned VC7 cold build failed: " + result.stdout[-1000:])
        data = object_path.read_bytes()
        definitions = {}
        for row in manifest["nodes"]:
            check_ledger(row, functions, origins, args.evidence_only)
            key, size = row["address"], row["size"]
            actual = comparison.pe_bytes_at(target, int(key, 16), size)
            if hashlib.sha256(actual).hexdigest() != row["body_sha256"]:
                raise ValueError("deque erase complete target body differs: " + key)
            for symbol in row["matching_symbols"]:
                if symbol not in definitions:
                    source_size = record.complete_aux_section_size(data, symbol, comparison.coff_name)
                    source, relocations = comparison.object_function(object_path, symbol, source_size)
                    definitions[symbol] = (source_size, source, relocations)
                source_size, source, relocations = definitions[symbol]
                if (source_size != size or hashlib.sha256(source).hexdigest() != row["source_sha256"]):
                    raise ValueError("deque erase whole source alternative differs: " + key)
                bindings = typed_bindings(relocations, row["relocation_bindings"], by_address)
                if symbol == row["coff_symbol"] and bindings != row["relocation_bindings"]:
                    raise ValueError("deque erase canonical source identity differs")
                indirect = record.compare_complete_body(source, relocations, actual, int(key, 16),
                                                        bindings, comparison, sdk)
                if indirect != row["indirect_call_count"]:
                    raise ValueError("deque erase complete control flow differs")
    print("R111 VC7 deque erase origins OK: 12 new library bodies / 1654 bytes; "
          "129 whole target bodies / 7958 bytes / 203 typed calls; "
          "337 cold complete source alternatives, closed graph; "
          "original element types unknown; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
