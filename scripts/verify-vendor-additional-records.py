#!/usr/bin/env python3
"""Cold-check VC7 STL helpers from independently varied record widths."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import re
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


def family(symbol):
    return re.sub(r"Rec[0-9]+", "RecN", symbol)


def source_definitions(data, path, comparison, record):
    _, _, _, symbol_offset, symbol_count, _, _ = struct.unpack_from("<HHIIIHH", data)
    strings = data[symbol_offset + symbol_count * 18:]
    result = []
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        raw, value, section, kind, storage, auxiliary = struct.unpack_from(
            "<8sIhHBB", data, offset)
        if index + auxiliary >= symbol_count:
            raise ValueError("truncated additional-record source symbol table")
        name = comparison.coff_name(raw, strings)
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and "Rec" in name and not name.startswith("?ProbeRecord")):
            size = struct.unpack_from("<I", data, offset + 18 + 4)[0]
            if size >= 32:
                if record.complete_aux_section_size(data, name, comparison.coff_name) != size:
                    raise ValueError("additional-record source extent differs")
                code, relocations = comparison.object_function(path, name, size)
                masked = set()
                for relocation in relocations:
                    masked.update(range(relocation["offset"], relocation["offset"] + 4))
                result.append((name, size, code, relocations, masked, family(name)))
        index += 1 + auxiliary
    if len(result) != 336:
        raise ValueError("additional-record source definition set changed")
    return result


def unique_family(actual, definitions, selected, expected):
    matches = sorted(symbol for symbol, size, code, relocations, masked, key in definitions
                     if size == len(actual) and all(code[index] == actual[index]
                                                    for index in range(size)
                                                    if index not in masked))
    if (not matches or selected not in matches
            or {family(symbol) for symbol in matches} != {expected}):
        raise ValueError("additional-record target lacks one complete template family")
    return matches


def main():
    comparison = module("additional_target", "compare-coff-function.py")
    record = module("additional_record", "verify-vendor-record-origins.py")
    sdk = module("additional_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    with (ROOT / "config/vendor-additional-record-origins.csv").open() as stream:
        evidence = list(csv.DictReader(stream))
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    if (len(evidence) != 31
            or len({row["address"] for row in evidence}) != len(evidence)):
        raise ValueError("expected 31 unique additional-record origins")
    scratch = ROOT / "build/origin-additional-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7AdditionalRecordContainers.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7AdditionalRecordContainers.cpp"), str(object_path),
             *PROFILE], cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 additional-record compilation failed")
        definitions = source_definitions(object_path.read_bytes(), object_path,
                                         comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        total = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (size < 32 or int(function["size"]) != size
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"):
                raise ValueError("additional-record origin ledger differs")
            actual = comparison.pe_bytes_at(target, address, size)
            if hashlib.sha256(actual).hexdigest() != row["body_sha256"]:
                raise ValueError("additional-record target body hash differs")
            matches = unique_family(actual, definitions, row["coff_symbol"],
                                    row["family_key"])
            if matches != json.loads(row["matching_symbols"]):
                raise ValueError("additional-record source aliases changed")
            selected = by_symbol[row["coff_symbol"]]
            if (selected[1] != size or selected[5] != row["family_key"]
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("additional-record source body changed")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("additional-record CFG changed")
            total += size
    print(f"VC7 additional-record origins OK: {len(evidence)} whole helper bodies, "
          f"{total} bytes, unique families and complete typed relocations; "
          "no original record types, callee, source, or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
