#!/usr/bin/env python3
"""Cold-check scalar copy wrappers with complete, explicitly ambiguous callees."""
from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


VECTOR = module("vector_copy_source", "verify-vendor-vector-callee-origins.py")


def verify_witness(row, anchors):
    """A different source family requires the same complete reviewed target body."""
    callee = anchors.get(row["callee_address"])
    calls = json.loads(row["relocation_bindings"])
    if (row["family_key"] != "??$copy" or callee is None
            or callee["family_key"] != "??$_Uninit_copy"
            or row["callee_source_symbol"].split("@", 1)[0] != "??$_Copy_opt"
            or len(calls) != 2 or [call["offset"] for call in calls] != [13, 40]
            or any(call["type"] != "REL32" or call["addend"] for call in calls)
            or calls[1]["target_address"] != row["callee_address"]
            or calls[1]["symbol"] != row["callee_source_symbol"]
            or row["callee_body_sha256"] != callee["body_sha256"]
            or int(callee["size"]) != 49):
        raise ValueError("scalar copy wrapper lacks its complete ambiguous callee witness")


def main():
    comparison = module("vector_copy_target", "compare-coff-function.py")
    record = module("vector_copy_record", "verify-vendor-record-origins.py")
    sdk = module("vector_copy_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = VECTOR.rows("vendor-vector-copy-origins.csv")
    anchors = {row["address"]: row for row in VECTOR.rows("vendor-deque-helper-origins.csv")}
    functions = {row["address"]: row for row in VECTOR.rows("functions.csv")}
    origins = {row["address"]: row for row in VECTOR.rows("function-origins.csv")}
    if (len(evidence) != 4 or len({row["address"] for row in evidence}) != 4
            or sum(int(row["size"]) for row in evidence) != 204):
        raise ValueError("scalar copy wrapper evidence set changed")
    for filename in ("verify-runtime-local-origins.py", "verify-vendor-deque-helper-origins.py"):
        result = subprocess.run(
            [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts" / filename)],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("scalar copy callee/CRT anchor failed cold replay: " + filename)
    scratch = ROOT / "build/origin-vector-copy-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7VectorOperations.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7VectorOperations.cpp"), str(object_path), *VECTOR.PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 scalar copy compilation failed: " + result.stderr[-1000:])
        definitions = [item for item in VECTOR.source_definitions(
            object_path.read_bytes(), object_path, comparison, record) if item[5] == "??$copy"]
        by_symbol = {item[0]: item for item in definitions}
        relocation_count = 0
        for row in evidence:
            key, size = row["address"], int(row["size"])
            address = int(key, 16)
            function, origin = functions[key], origins[key]
            if (size != 51 or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or row["evidence_id"] != "R094" or origin["evidence_id"] != "R094"
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or any(address < int(other, 16) < address + size for other in functions)):
                raise ValueError("scalar copy wrapper extent or origin differs")
            actual = comparison.pe_bytes_at(target, address, size)
            selected = by_symbol[row["coff_symbol"]]
            matches = VECTOR.matching_symbols(actual, definitions)
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or matches != json.loads(row["matching_symbols"])
                    or row["coff_symbol"] not in matches
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("scalar copy wrapper complete source/target body changed")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("scalar copy wrapper control flow differs")
            verify_witness(row, anchors)
            callee_key = row["callee_address"]
            callee_address = int(callee_key, 16)
            if (int(functions[callee_key]["size"]) != 49
                    or origins[callee_key]["origin"] != "library"):
                raise ValueError("scalar copy callee ledger differs")
            size = record.complete_aux_section_size(
                object_path.read_bytes(), row["callee_source_symbol"], comparison.coff_name)
            source, relocations = comparison.object_function(
                object_path, row["callee_source_symbol"], size)
            actual = comparison.pe_bytes_at(target, callee_address, size)
            calls = json.loads(row["callee_relocation_bindings"])
            if (size != 49 or hashlib.sha256(actual).hexdigest() != row["callee_body_sha256"]
                    or hashlib.sha256(source).hexdigest() != row["callee_source_sha256"]
                    or calls != [{"offset": 32, "type": "REL32", "symbol": "_memmove",
                                  "addend": 0, "target_address": "0x00641260"}]):
                raise ValueError("scalar copy complete callee or memmove binding differs")
            indirect = record.compare_complete_body(
                source, relocations, actual, callee_address, calls, comparison, sdk)
            if indirect != int(row["callee_indirect_call_count"]):
                raise ValueError("scalar copy complete callee control flow differs")
            relocation_count += len(selected[3])
    if relocation_count != 8:
        raise ValueError("scalar copy wrapper relocation total changed")
    print("VC7 scalar copy origins OK: 4 complete wrappers, 204 bytes, 8 typed relocations; "
          "four complete callee source aliases and CRT memmove reverified; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, json.JSONDecodeError) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
