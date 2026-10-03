#!/usr/bin/env python3
"""Cold-check VC7 deque iterator comparison and end helpers."""
from __future__ import annotations

import csv
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
COUNTS = {"??Gconst_iterator": 7, "??8const_iterator": 9,
          "??Giterator": 7, "?end": 7}
RELOCATIONS = {"??Gconst_iterator": 0, "??8const_iterator": 0,
               "??Giterator": 1, "?end": 1}


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
            raise ValueError("truncated deque access source symbol table")
        name = comparison.coff_name(raw, strings)
        method = name.split("@", 1)[0]
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and method in COUNTS and "DequeIteratorRecord" in name):
            size = record.complete_aux_section_size(data, name, comparison.coff_name)
            code, relocations = comparison.object_function(path, name, size)
            masked = set()
            for relocation in relocations:
                masked.update(range(relocation["offset"], relocation["offset"] + 4))
            result.append((name, size, code, relocations, masked, method))
        index += 1 + auxiliary
    if len(result) != 28 or len({item[0] for item in result}) != 28:
        raise ValueError("expected 28 unique VC7 deque comparison definitions")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, code, _, masked, _ in definitions
                  if size == len(actual) and all(code[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def main():
    comparison = module("deque_comparison_target", "compare-coff-function.py")
    record = module("deque_comparison_record", "verify-vendor-record-origins.py")
    sdk = module("deque_comparison_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    with (ROOT / "config/vendor-deque-comparison-origins.csv").open() as stream:
        evidence = list(csv.DictReader(stream))
    with (ROOT / "config/vendor-deque-iterator-origins.csv").open() as stream:
        iterator_constructors = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    if (len(evidence) != 30 or len({row["address"] for row in evidence}) != 30
            or Counter(row["family_key"] for row in evidence) != COUNTS):
        raise ValueError("deque comparison evidence set changed")
    result = subprocess.run(
        [str(ROOT / "scripts/repo-python"),
         str(ROOT / "scripts/verify-vendor-deque-iterator-origins.py")],
        cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("deque iterator constructor chain failed cold verification")
    by_address = {row["address"]: row for row in evidence}
    scratch = ROOT / "build/origin-deque-comparison-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DequeIterators.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DequeIterators.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 deque comparison compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path,
                                         comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        total = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (size not in (41, 60, 66) or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"):
                raise ValueError("deque comparison origin ledger differs")
            actual = comparison.pe_bytes_at(target, address, size)
            if hashlib.sha256(actual).hexdigest() != row["body_sha256"]:
                raise ValueError("deque comparison target body hash differs")
            matches = matching_symbols(actual, definitions)
            if (not matches or matches != json.loads(row["matching_symbols"])
                    or {by_symbol[name][5] for name in matches} != {row["family_key"]}):
                raise ValueError("deque comparison template family changed")
            selected = by_symbol[row["coff_symbol"]]
            if (row["coff_symbol"] not in matches or selected[1] != size
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("deque comparison selected source changed")
            if len(selected[3]) != RELOCATIONS[row["family_key"]]:
                raise ValueError("deque comparison family relocation count changed")
            bindings = json.loads(row["relocation_bindings"])
            if bindings:
                callee_key = row["callee_address"]
                if row["family_key"] == "??Giterator":
                    callee = by_address.get(callee_key)
                    expected_family = "??Gconst_iterator"
                    expected_symbol = "??Gconst_iterator"
                else:
                    callee = iterator_constructors.get(callee_key)
                    expected_family = "??0iterator"
                    expected_symbol = "??0iterator"
                if (len(bindings) != 1 or callee is None
                        or callee["family_key"] != expected_family
                        or bindings[0]["type"] != "REL32"
                        or bindings[0]["symbol"].split("@", 1)[0] != expected_symbol
                        or bindings[0]["target_address"] != callee_key
                        or origins[callee_key]["origin"] != "library"
                        or hashlib.sha256(comparison.pe_bytes_at(
                            target, int(callee_key, 16), int(callee["size"]))).hexdigest()
                        != callee["body_sha256"]):
                    raise ValueError("deque comparison callee binding differs")
            elif row["callee_address"]:
                raise ValueError("no-relocation comparison records a callee")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                bindings, comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("deque comparison target CFG changed")
            total += size
    print(f"VC7 deque comparison origins OK: {len(evidence)} complete bodies, "
          f"{total} bytes, typed relocations and complete CFG; "
          "original record types and callees remain unclaimed.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
