#!/usr/bin/env python3
"""Cold-check complete deque::empty bodies with reviewed operation callers."""
from __future__ import annotations

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
            raise ValueError("truncated deque empty source symbol table")
        name = comparison.coff_name(raw, strings)
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and name.split("@", 1)[0] == "?empty" and "DequeProbeRecord" in name):
            size = record.complete_aux_section_size(data, name, comparison.coff_name)
            source, relocations = comparison.object_function(path, name, size)
            if size != 25 or relocations:
                raise ValueError("deque empty source extent or relocation count changed")
            masked = {byte for relocation in relocations
                      for byte in range(relocation["offset"], relocation["offset"] + 4)}
            result.append((name, size, source, relocations, masked))
        index += 1 + auxiliary
    if len(result) != 7 or len({item[0] for item in result}) != 7:
        raise ValueError("expected seven complete deque empty source definitions")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, source, _, masked in definitions
                  if size == len(actual) and all(source[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def main():
    comparison = module("deque_empty_target", "compare-coff-function.py")
    record = module("deque_empty_record", "verify-vendor-record-origins.py")
    sdk = module("deque_empty_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-deque-empty-origins.csv")
    parents = {row["address"]: row for row in rows("vendor-deque-operation-origins.csv")}
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    if len(evidence) != 13 or len({row["address"] for row in evidence}) != 13:
        raise ValueError("deque empty evidence set changed")
    result = subprocess.run(
        [str(ROOT / "scripts/repo-python"),
         str(ROOT / "scripts/verify-vendor-deque-operation-origins.py")],
        cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("deque operation parents failed cold verification")
    scratch = ROOT / "build/origin-deque-empty-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DequeMapGrowth.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DequeMapGrowth.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 deque empty compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path, comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (size != 25 or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or row["evidence_id"] != "R086" or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or row["family_key"] != "?empty"
                    or any(address < int(key, 16) < address + size for key in functions)):
                raise ValueError("deque empty origin extent or ownership differs")
            actual = comparison.pe_bytes_at(target, address, size)
            matches = matching_symbols(actual, definitions)
            selected = by_symbol[row["coff_symbol"]]
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or not matches or matches != json.loads(row["matching_symbols"])
                    or row["coff_symbol"] not in matches
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("deque empty complete source/target body changed")
            parent = parents[row["parent_address"]]
            field = int(row["parent_call_offset"])
            calls = [binding for binding in json.loads(parent["relocation_bindings"])
                     if binding["offset"] == field]
            parent_body = comparison.pe_bytes_at(target, int(parent["address"], 16), int(parent["size"]))
            if (origins[parent["address"]]["origin"] != "library"
                    or origins[parent["address"]]["evidence_id"] != "R072"
                    or hashlib.sha256(parent_body).hexdigest() != parent["body_sha256"]
                    or len(calls) != 1 or calls[0]["type"] != "REL32" or calls[0]["addend"]
                    or calls[0]["symbol"] != row["coff_symbol"]
                    or calls[0]["target_address"] != row["address"]
                    or field < 1 or field + 4 > len(parent_body) or parent_body[field - 1] != 0xE8
                    or int(parent["address"], 16) + field + 4
                    + struct.unpack_from("<i", parent_body, field)[0] != address):
                raise ValueError("deque empty exact source-typed parent call differs")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("deque empty complete control flow changed")
    print("VC7 deque empty origins OK: 13 complete bodies, 325 bytes, "
          "13 source-typed calls from cold-reverified operation parents; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
