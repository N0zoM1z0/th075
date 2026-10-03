#!/usr/bin/env python3
"""Cold-check VC7 deque callees through whole bodies and reviewed callers."""
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
METHODS = {"?allocate", "?construct", "?destroy", "?max_size", "?deallocate",
           "??$_Uninit_fill_n", "??0?$_Deque_map"}
PARENT_FILES = {
    "R071": "vendor-deque-growmap-origins.csv",
    "R072": "vendor-deque-operation-origins.csv",
    "R073": "vendor-deque-helper-origins.csv",
}
PARENT_SCRIPTS = (
    "verify-vendor-deque-growmap-origins.py",
    "verify-vendor-deque-operation-origins.py",
    "verify-vendor-deque-helper-origins.py",
)


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


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
            raise ValueError("truncated deque callee source symbol table")
        name = comparison.coff_name(raw, strings)
        method = name.split("@", 1)[0]
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and method in METHODS and "DequeProbeRecord" in name):
            size = record.complete_aux_section_size(data, name, comparison.coff_name)
            code, relocations = comparison.object_function(path, name, size)
            masked = set()
            for relocation in relocations:
                masked.update(range(relocation["offset"], relocation["offset"] + 4))
            result.append((name, size, code, relocations, masked, method))
        index += 1 + auxiliary
    if len(result) != 77 or len({item[0] for item in result}) != 77:
        raise ValueError("expected 77 unique VC7 deque callee definitions")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, code, _, masked, _ in definitions
                  if size == len(actual) and all(code[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def checked_parent(row, target, comparison, functions, origins, parents):
    parent_key = row["parent_address"]
    parent = parents[parent_key]
    parent_address = int(parent_key, 16)
    parent_size = int(parent["size"])
    parent_body = comparison.pe_bytes_at(target, parent_address, parent_size)
    if (parent["evidence_id"] not in PARENT_FILES
            or origins[parent_key]["origin"] != "library"
            or functions[parent_key]["owner"] != "library"
            or hashlib.sha256(parent_body).hexdigest() != parent["body_sha256"]):
        raise ValueError("deque callee parent lost its reviewed library evidence")
    offset = int(row["parent_call_offset"])
    calls = [binding for binding in json.loads(parent["relocation_bindings"])
             if binding["offset"] == offset and binding["type"] == "REL32"
             and binding["symbol"].split("@", 1)[0] == row["family_key"]
             and binding["target_address"] == row["address"]]
    if len(calls) != 1 or not 1 <= offset <= parent_size - 4:
        raise ValueError("deque callee lacks a same-family typed parent call")
    field = struct.unpack_from("<i", parent_body, offset)[0]
    if parent_body[offset - 1] != 0xE8 or parent_address + offset + 4 + field != int(row["address"], 16):
        raise ValueError("deque callee parent call instruction differs")


def main():
    comparison = module("deque_callees_target", "compare-coff-function.py")
    record = module("deque_callees_record", "verify-vendor-record-origins.py")
    sdk = module("deque_callees_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    with (ROOT / "config/vendor-deque-callee-origins.csv").open() as stream:
        evidence = list(csv.DictReader(stream))
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    if (len(evidence) != 126 or len({row["address"] for row in evidence}) != 126
            or {row["family_key"] for row in evidence} != METHODS):
        raise ValueError("deque callee evidence set changed")
    parents = {}
    for batch, filename in PARENT_FILES.items():
        with (ROOT / "config" / filename).open() as stream:
            for parent in csv.DictReader(stream):
                if parent["address"] in parents or parent["evidence_id"] != batch:
                    raise ValueError("deque parent evidence is duplicated or misidentified")
                parents[parent["address"]] = parent
    for filename in PARENT_SCRIPTS:
        result = subprocess.run(
            [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts" / filename)],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("deque parent cold verification failed: " + filename)
    scratch = ROOT / "build/origin-deque-callee-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DequeMapGrowth.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DequeMapGrowth.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 deque callee compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path,
                                         comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        total = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (size < 20 or size > 29 or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"):
                raise ValueError("deque callee origin ledger differs")
            checked_parent(row, target, comparison, functions, origins, parents)
            actual = comparison.pe_bytes_at(target, address, size)
            if hashlib.sha256(actual).hexdigest() != row["body_sha256"]:
                raise ValueError("deque callee target body hash differs")
            matches = matching_symbols(actual, definitions)
            if (not matches or matches != json.loads(row["matching_symbols"])
                    or {by_symbol[name][5] for name in matches} != {row["family_key"]}):
                raise ValueError("deque callee template family changed")
            selected = by_symbol[row["coff_symbol"]]
            if (row["coff_symbol"] not in matches or selected[1] != size
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("deque callee selected source changed")
            if not selected[3]:
                raise ValueError("deque callee lacks a typed relocation witness")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("deque callee target CFG changed")
            total += size
    print(f"VC7 deque callee origins OK: {len(evidence)} complete bodies, "
          f"{total} bytes, typed relocations, reviewed parent calls and complete CFG; "
          "original record types and callees remain unclaimed.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
