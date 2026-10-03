#!/usr/bin/env python3
"""Cold-check VC7 deque destructors bound to verified deque cleanup bodies."""
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
METHODS = {"??1?$deque"}


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
            raise ValueError("truncated deque operation source symbol table")
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
    if len(result) != 7 or len({item[0] for item in result}) != 7:
        raise ValueError("expected seven unique VC7 deque destructor definitions")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, code, _, masked, _ in definitions
                  if size == len(actual) and all(code[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def main():
    comparison = module("deque_destructors_target", "compare-coff-function.py")
    record = module("deque_destructors_record", "verify-vendor-record-origins.py")
    sdk = module("deque_destructors_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    with (ROOT / "config/vendor-deque-destructor-origins.csv").open() as stream:
        evidence = list(csv.DictReader(stream))
    with (ROOT / "config/vendor-deque-operation-origins.csv").open() as stream:
        tidy = {row["address"]: row for row in csv.DictReader(stream)
                if row["family_key"] == "?_Tidy"}
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    if (len(evidence) != 24 or len({row["address"] for row in evidence}) != 24
            or {row["family_key"] for row in evidence} != METHODS):
        raise ValueError("deque destructor evidence set changed")
    result = subprocess.run(
        [str(ROOT / "scripts/repo-python"),
         str(ROOT / "scripts/verify-vendor-deque-operation-origins.py")],
        cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("deque _Tidy parent evidence failed cold verification")
    scratch = ROOT / "build/origin-deque-destructor-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DequeMapGrowth.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DequeMapGrowth.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 deque destructor compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path,
                                         comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        total = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (size != 19 or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"):
                raise ValueError("deque destructor origin ledger differs")
            actual = comparison.pe_bytes_at(target, address, size)
            if hashlib.sha256(actual).hexdigest() != row["body_sha256"]:
                raise ValueError("deque destructor target body hash differs")
            matches = matching_symbols(actual, definitions)
            if (not matches or matches != json.loads(row["matching_symbols"])
                    or {by_symbol[name][5] for name in matches} != {row["family_key"]}):
                raise ValueError("deque destructor template family changed")
            selected = by_symbol[row["coff_symbol"]]
            if (row["coff_symbol"] not in matches or selected[1] != size
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("deque destructor selected source changed")
            bindings = json.loads(row["relocation_bindings"])
            callee_key = row["callee_address"]
            callee = tidy.get(callee_key)
            if (len(bindings) != 1 or bindings[0]["type"] != "REL32"
                    or bindings[0]["symbol"].split("@", 1)[0] != "?_Tidy"
                    or bindings[0]["target_address"] != callee_key or callee is None
                    or origins[callee_key]["origin"] != "library"
                    or functions[callee_key]["owner"] != "library"
                    or hashlib.sha256(comparison.pe_bytes_at(
                        target, int(callee_key, 16), int(callee["size"]))).hexdigest()
                    != callee["body_sha256"]):
                raise ValueError("deque destructor does not call verified deque _Tidy")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                bindings, comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("deque destructor target CFG changed")
            total += size
    print(f"VC7 deque destructor origins OK: {len(evidence)} complete bodies, "
          f"{total} bytes, typed _Tidy calls and complete CFG; "
          "original record types and callees remain unclaimed.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
