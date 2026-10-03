#!/usr/bin/env python3
"""Cold-check short VC7 vector helpers through reviewed storage call chains."""
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
COUNTS = {"??0?$vector": 10, "??0?$_Vector_val": 10, "??0?$allocator": 20,
          "?max_size": 8, "?allocate": 8, "?deallocate": 8, "??$_Allocate": 8}
SIZES = {"??0?$vector": {42}, "??0?$_Vector_val": {28}, "??0?$allocator": {14, 16},
         "?max_size": {19}, "?allocate": {27}, "?deallocate": {25}, "??$_Allocate": {20}}
SOURCE_COUNTS = {"??0?$vector": 16, "??0?$_Vector_val": 16, "??0?$allocator": 34,
                 "?max_size": 16, "?allocate": 17, "?deallocate": 17, "??$_Allocate": 12}
PARENT_FAMILIES = {"??0?$_Vector_val": {"??0?$vector"},
                   "??0?$allocator": {"??0?$vector", "??0?$_Vector_val"},
                   "?max_size": {"?_Buy"}, "?allocate": {"?_Buy"},
                   "?deallocate": {"?_Tidy"}, "??$_Allocate": {"?allocate"}}


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
            raise ValueError("truncated vector helper source symbol table")
        name = comparison.coff_name(raw, strings)
        family = name.split("@", 1)[0]
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and family in COUNTS and "std@@" in name):
            size = record.complete_aux_section_size(data, name, comparison.coff_name)
            if size not in SIZES[family]:
                index += 1 + auxiliary
                continue
            source, relocations = comparison.object_function(path, name, size)
            masked = {byte for relocation in relocations
                      for byte in range(relocation["offset"], relocation["offset"] + 4)}
            result.append((name, size, source, relocations, masked, family))
        index += 1 + auxiliary
    if (len(result) != 128 or len({item[0] for item in result}) != 128
            or Counter(item[5] for item in result) != SOURCE_COUNTS):
        raise ValueError("vector helper complete source set changed")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, source, _, masked, _ in definitions
                  if size == len(actual) and all(source[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def verify_witness(row, evidence, storage, visiting=None):
    """Every short node must reach an independently cold-replayed storage body."""
    visiting = set() if visiting is None else visiting
    if row["address"] in visiting:
        raise ValueError("circular vector helper ownership witness")
    visiting = visiting | {row["address"]}
    family, role = row["family_key"], row["witness_role"]
    if role == "constructor":
        callee = storage.get(row["callee_address"])
        calls = json.loads(row["relocation_bindings"])
        if (family != "??0?$vector" or callee is None or callee["family_key"] != "?_Buy"
                or row["parent_address"] or row["parent_call_offset"] or len(calls) != 3
                or [call["offset"] for call in calls] != [13, 21, 31]
                or [call["symbol"].split("@", 1)[0] for call in calls]
                != ["??0?$allocator", "??0?$_Vector_val", "?_Buy"]
                or calls[2]["target_address"] != callee["address"]
                or calls[2]["symbol"] != callee["coff_symbol"]
                or any(call["type"] != "REL32" or call["addend"] for call in calls)):
            raise ValueError("vector constructor lacks its complete typed storage callee")
    elif role == "child":
        if family not in PARENT_FAMILIES or row["callee_address"]:
            raise ValueError("invalid vector helper parent witness")
        key = row["parent_address"]
        parent = evidence.get(key) or storage.get(key)
        if parent is None or parent["family_key"] not in PARENT_FAMILIES[family]:
            raise ValueError("vector helper lacks a same-family template parent")
        calls = [binding for binding in json.loads(parent["relocation_bindings"])
                 if binding["offset"] == int(row["parent_call_offset"])]
        if (len(calls) != 1 or calls[0]["type"] != "REL32" or calls[0]["addend"]
                or calls[0]["target_address"] != row["address"]
                or calls[0]["symbol"] != row["coff_symbol"]):
            raise ValueError("vector helper's exact source-typed parent call differs")
        if key in evidence:
            verify_witness(parent, evidence, storage, visiting)
    else:
        raise ValueError("unknown vector helper ownership witness")


def main():
    comparison = module("vector_helper_target", "compare-coff-function.py")
    record = module("vector_helper_record", "verify-vendor-record-origins.py")
    sdk = module("vector_helper_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-vector-helper-origins.csv")
    storage = {row["address"]: row for row in rows("vendor-vector-storage-origins.csv")}
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    if (len(evidence) != 72 or len({row["address"] for row in evidence}) != 72
            or Counter(row["family_key"] for row in evidence) != COUNTS
            or Counter(row["witness_role"] for row in evidence) != {"constructor": 10, "child": 62}
            or sum(int(row["size"]) for row in evidence) != 1728):
        raise ValueError("vector helper evidence set changed")
    result = subprocess.run(
        [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts/verify-vendor-vector-storage-origins.py")],
        cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("vector storage witnesses failed cold verification")
    scratch = ROOT / "build/origin-vector-helper-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7VectorOperations.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7VectorOperations.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 vector helper compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path, comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        relocation_count = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (row["family_key"] not in SIZES or size not in SIZES[row["family_key"]]
                    or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or row["evidence_id"] != "R090" or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or any(address < int(key, 16) < address + size for key in functions)):
                raise ValueError("vector helper origin extent or ownership differs")
            actual = comparison.pe_bytes_at(target, address, size)
            matches = matching_symbols(actual, definitions)
            selected = by_symbol[row["coff_symbol"]]
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or not matches or matches != json.loads(row["matching_symbols"])
                    or row["coff_symbol"] not in matches or selected[1] != size
                    or selected[5] != row["family_key"]
                    or {by_symbol[name][5] for name in matches} != {row["family_key"]}
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("vector helper complete source/target body changed")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("vector helper complete control flow changed")
            relocation_count += len(selected[3])
        by_address = {row["address"]: row for row in evidence}
        for row in evidence:
            verify_witness(row, by_address, storage)
    if relocation_count != 72:
        raise ValueError("vector helper typed relocation total changed")
    print("VC7 vector helper origins OK: 72 complete bodies, 1728 bytes, 72 typed relocations; "
          "all short bodies reach cold-reverified storage witnesses; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
