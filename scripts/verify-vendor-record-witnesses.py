#!/usr/bin/env python3
"""Prove short VC7 helpers and copy aliases with complete typed caller witnesses."""
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


def rows(name):
    with (ROOT / "config" / name).open() as stream:
        return list(csv.DictReader(stream))


def matching_symbols(actual, definitions):
    result = []
    for symbol, size, code, relocations, masked, family in definitions:
        if size == len(actual) and all(code[index] == actual[index]
                                       for index in range(size) if index not in masked):
            result.append(symbol)
    return sorted(result)


def require_typed_caller(bindings, field, symbol, destination):
    matches = [row for row in bindings
               if row["type"] == "REL32" and row["offset"] == field
               and row["symbol"] == symbol and row["target_address"] == destination]
    if len(matches) != 1:
        raise ValueError("short/alias helper lacks one complete typed caller witness")


def main():
    comparison = module("witness_target", "compare-coff-function.py")
    record = module("witness_record", "verify-vendor-record-origins.py")
    helper = module("witness_helper", "verify-vendor-record-helpers.py")
    sdk = module("witness_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-record-witness-origins.csv")
    helpers = {row["address"]: row for row in rows("vendor-record-helper-origins.csv")}
    spans = {row["address"]: row for row in rows("vendor-record-origin-spans.csv")}
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    if (len(evidence) != 26
            or len({row["address"] for row in evidence}) != len(evidence)):
        raise ValueError("expected 26 unique typed-witness origin records")
    scratch = ROOT / "build/origin-witness-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7OriginRecordContainers.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7OriginRecordContainers.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 witness probe compilation failed")
        definitions = helper.source_functions(object_path.read_bytes(), object_path,
                                              comparison, record, minimum_size=8)
        by_symbol = {entry[0]: entry for entry in definitions}
        total = short_count = alias_count = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (int(function["size"]) != size or origin["origin"] != "library"
                    or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"):
                raise ValueError("typed-witness helper ledger differs")
            actual = comparison.pe_bytes_at(target, address, size)
            if hashlib.sha256(actual).hexdigest() != row["body_sha256"]:
                raise ValueError("typed-witness target whole hash mismatch")
            matches = matching_symbols(actual, definitions)
            families = sorted({helper.template_family(symbol) for symbol in matches})
            if (matches != json.loads(row["matching_symbols"])
                    or families != json.loads(row["matching_families"])
                    or row["coff_symbol"] not in matches
                    or row["family_key"] not in families):
                raise ValueError("typed-witness source alias set changed")
            if row["kind"] == "short":
                if not 8 <= size < 32 or families != [row["family_key"]]:
                    raise ValueError("short helper lacks one template family")
                short_count += 1
            elif row["kind"] == "copy_alias":
                if size != 51 or len(families) != 2:
                    raise ValueError("copy alias source ambiguity changed")
                alias_count += 1
            else:
                raise ValueError("unknown typed-witness helper kind")
            source = by_symbol[row["coff_symbol"]]
            if (source[1] != size
                    or hashlib.sha256(source[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("typed-witness source whole definition changed")
            record.compare_complete_body(source[2], source[3], actual, address,
                                         json.loads(row["relocation_bindings"]),
                                         comparison, sdk)
            caller_address = row["caller_address"]
            if row["caller_kind"] not in ("helper", "span"):
                raise ValueError("unsupported typed-witness caller ledger")
            caller = (helpers if row["caller_kind"] == "helper" else spans).get(caller_address)
            if caller is None or origins[caller_address]["origin"] != "library":
                raise ValueError("typed witness lacks an independently reviewed caller")
            caller_size = int(caller["size"])
            caller_body = comparison.pe_bytes_at(target, int(caller_address, 16), caller_size)
            caller_source = by_symbol[caller["coff_symbol"]]
            if (caller_source[1] != caller_size
                    or hashlib.sha256(caller_body).hexdigest() != caller["body_sha256"]
                    or hashlib.sha256(caller_source[2]).hexdigest() != caller["source_sha256"]):
                raise ValueError("typed witness caller whole body differs")
            record.compare_complete_body(caller_source[2], caller_source[3], caller_body,
                                         int(caller_address, 16),
                                         json.loads(caller["relocation_bindings"]),
                                         comparison, sdk)
            if row["caller_kind"] == "helper":
                helper.unique_family(caller_body, [entry for entry in definitions
                                                   if entry[1] >= 32],
                                     caller["coff_symbol"], caller["family_key"])
            require_typed_caller(json.loads(caller["relocation_bindings"]),
                                 int(row["caller_call_offset"]), row["coff_symbol"],
                                 row["address"])
            total += size
    if short_count != 23 or alias_count != 3:
        raise ValueError("typed witness cohort composition changed")
    print(f"VC7 typed caller witnesses OK: {short_count} short helpers and "
          f"{alias_count} copy aliases, {total} complete bytes; caller and callee "
          "origins remain independent; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
