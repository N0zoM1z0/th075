#!/usr/bin/env python3
"""Cold-check short VC7 deque/allocator helpers with reviewed template callers."""
from __future__ import annotations

from collections import Counter
import csv
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
COUNTS = {"??0?$allocator": 32, "??$_Ptr_cat": 16, "??$_Destroy_range": 16}
SIZES = {"??0?$allocator": {14, 16}, "??$_Ptr_cat": {11}, "??$_Destroy_range": {5}}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open() as stream:
        return list(csv.DictReader(stream))


def source_definitions(data, path, comparison, record):
    _, _, _, symbols_offset, symbol_count, _, _ = struct.unpack_from("<HHIIIHH", data)
    strings = data[symbols_offset + symbol_count * 18:]
    result = []
    index = 0
    while index < symbol_count:
        offset = symbols_offset + index * 18
        raw, _, section, kind, storage, auxiliary = struct.unpack_from(
            "<8sIhHBB", data, offset)
        if index + auxiliary >= symbol_count:
            raise ValueError("truncated deque leaf source symbol table")
        name = comparison.coff_name(raw, strings)
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and name.split("@", 1)[0] in COUNTS):
            size = record.complete_aux_section_size(data, name, comparison.coff_name)
            source, relocations = comparison.object_function(path, name, size)
            family = name.split("@", 1)[0]
            if size not in SIZES[family]:
                index += 1 + auxiliary
                continue
            if relocations:
                raise ValueError("short deque helper unexpectedly has source relocations")
            masked = {byte for relocation in relocations
                      for byte in range(relocation["offset"], relocation["offset"] + 4)}
            result.append((name, size, source, relocations, masked))
        index += 1 + auxiliary
    if (len(result) != 30 or len({item[0] for item in result}) != 30
            or Counter(item[0].split("@", 1)[0] for item in result)
            != {"??0?$allocator": 16, "??$_Ptr_cat": 7, "??$_Destroy_range": 7}):
        raise ValueError("short deque helper complete source set changed")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, source, _, masked in definitions
                  if size == len(actual) and all(source[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def main():
    comparison = module("deque_leaf_target", "compare-coff-function.py")
    record = module("deque_leaf_record", "verify-vendor-record-origins.py")
    sdk = module("deque_leaf_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-deque-leaf-origins.csv")
    parents = {row["address"]: row for row in rows("vendor-deque-helper-origins.csv")}
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    if (len(evidence) != 64 or len({row["address"] for row in evidence}) != 64
            or Counter(row["family_key"] for row in evidence) != COUNTS
            or sum(int(row["size"]) for row in evidence) != 742):
        raise ValueError("deque leaf evidence set changed")
    result = subprocess.run(
        [str(ROOT / "scripts/repo-python"),
         str(ROOT / "scripts/verify-vendor-deque-helper-origins.py")],
        cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("deque helper parents failed cold verification")
    scratch = ROOT / "build/origin-deque-leaf-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DequeMapGrowth.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DequeMapGrowth.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 deque leaf compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path, comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (row["family_key"] not in SIZES or size not in SIZES[row["family_key"]]
                    or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or row["evidence_id"] != "R087" or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or row["coff_symbol"].split("@", 1)[0] != row["family_key"]
                    or any(address < int(key, 16) < address + size for key in functions)):
                raise ValueError("deque leaf origin extent or ownership differs")
            actual = comparison.pe_bytes_at(target, address, size)
            matches = matching_symbols(actual, definitions)
            selected = by_symbol[row["coff_symbol"]]
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or not matches or matches != json.loads(row["matching_symbols"])
                    or row["coff_symbol"] not in matches
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("deque leaf complete source/target body changed")
            parent = parents[row["parent_address"]]
            field = int(row["parent_call_offset"])
            calls = [binding for binding in json.loads(parent["relocation_bindings"])
                     if binding["offset"] == field]
            parent_body = comparison.pe_bytes_at(target, int(parent["address"], 16), int(parent["size"]))
            if (origins[parent["address"]]["origin"] != "library"
                    or origins[parent["address"]]["evidence_id"] != "R073"
                    or hashlib.sha256(parent_body).hexdigest() != parent["body_sha256"]
                    or len(calls) != 1 or calls[0]["type"] != "REL32" or calls[0]["addend"]
                    or calls[0]["symbol"] != row["coff_symbol"]
                    or calls[0]["target_address"] != row["address"]
                    or field < 1 or field + 4 > len(parent_body) or parent_body[field - 1] != 0xE8
                    or int(parent["address"], 16) + field + 4
                    + struct.unpack_from("<i", parent_body, field)[0] != address):
                raise ValueError("deque leaf exact source-typed parent call differs")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("deque leaf complete control flow changed")
    print("VC7 deque leaf origins OK: 64 complete bodies, 742 bytes, "
          "64 source-typed calls from cold-reverified helper parents; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
