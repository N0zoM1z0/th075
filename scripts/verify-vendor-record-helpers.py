#!/usr/bin/env python3
"""Cold-check unambiguous VC7 record-helper template origins, not source credit."""
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


def template_family(symbol):
    return re.sub(r"Record(?:16|44|116)", "RecordN", symbol)


def source_functions(data, path, comparison, record_verifier):
    _, _, _, symbols_offset, symbol_count, _, _ = struct.unpack_from("<HHIIIHH", data)
    strings_offset = symbols_offset + symbol_count * 18
    strings = data[strings_offset:]
    definitions = []
    index = 0
    while index < symbol_count:
        offset = symbols_offset + index * 18
        raw, value, section, kind, storage, auxiliary = struct.unpack_from(
            "<8sIhHBB", data, offset)
        if index + auxiliary >= symbol_count:
            raise ValueError("truncated VC7 helper symbol table")
        name = comparison.coff_name(raw, strings)
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and "Record" in name):
            size = struct.unpack_from("<I", data, offset + 18 + 4)[0]
            if size >= 32:
                whole = record_verifier.complete_aux_section_size(
                    data, name, comparison.coff_name)
                if whole != size:
                    raise ValueError("VC7 helper extent differs from complete section")
                code, relocations = comparison.object_function(path, name, size)
                masked = set()
                for relocation in relocations:
                    masked.update(range(relocation["offset"], relocation["offset"] + 4))
                definitions.append((name, size, code, relocations, masked,
                                    template_family(name)))
        index += 1 + auxiliary
    if not definitions:
        raise ValueError("record probe emitted no complete helper functions")
    return definitions


def unique_family(actual, definitions, recorded_symbol, recorded_family):
    matches = []
    for symbol, size, code, relocations, masked, family in definitions:
        if size == len(actual) and all(code[index] == actual[index]
                                       for index in range(size) if index not in masked):
            matches.append(symbol)
    families = {template_family(symbol) for symbol in matches}
    if (not matches or families != {recorded_family}
            or recorded_symbol not in matches):
        raise ValueError("record helper has no unique VC7 template family")
    return sorted(matches)


def main():
    comparison = module("helper_target", "compare-coff-function.py")
    record_verifier = module("record_verifier", "verify-vendor-record-origins.py")
    sdk = module("helper_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    with (ROOT / "config/vendor-record-helper-origins.csv").open() as stream:
        evidence = list(csv.DictReader(stream))
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    if (len(evidence) != 129
            or len({row["address"] for row in evidence}) != len(evidence)):
        raise ValueError("expected 129 unique reviewed record helper origins")
    scratch = ROOT / "build/origin-helper-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7OriginRecordContainers.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7OriginRecordContainers.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 helper probe compilation failed")
        source_data = object_path.read_bytes()
        definitions = source_functions(source_data, object_path, comparison,
                                       record_verifier)
        if len(definitions) != 72:
            raise ValueError("VC7 helper probe definition set changed")
        by_symbol = {entry[0]: entry for entry in definitions}
        total = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (size < 32 or int(function["size"]) != size
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"):
                raise ValueError("record helper ledger differs from origin evidence")
            actual = comparison.pe_bytes_at(target, address, size)
            if hashlib.sha256(actual).hexdigest() != row["body_sha256"]:
                raise ValueError("record helper complete target hash mismatch")
            matches = unique_family(actual, definitions, row["coff_symbol"],
                                    row["family_key"])
            if matches != json.loads(row["matching_symbols"]):
                raise ValueError("record helper probe alias set changed")
            symbol, source_size, source, relocations, masked, family = by_symbol[
                row["coff_symbol"]]
            if (source_size != size or family != row["family_key"]
                    or hashlib.sha256(source).hexdigest() != row["source_sha256"]):
                raise ValueError("record helper complete source definition changed")
            indirect = record_verifier.compare_complete_body(
                source, relocations, actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("record helper control flow differs")
            total += size
    print(f"VC7 record helper origins OK: {len(evidence)} complete COMDAT bodies, "
          f"{total} bytes, unique template families and all typed relocations; "
          "no inferred record types, callees, source, or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
