#!/usr/bin/env python3
"""Cold-check vector iterator and copy wrappers through reviewed call witnesses."""
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
COUNTS = {"?end": 1, "?begin": 1, "??Giterator": 1, "??Hiterator": 1,
          "??0iterator": 1, "??Gconst_iterator": 1, "??Yiterator": 1,
          "??0const_iterator": 1, "??$copy_backward": 7, "??$copy": 1}
SIZES = {"?end": {31}, "?begin": {31}, "??Giterator": {35}, "??Hiterator": {45},
         "??0iterator": {28}, "??Gconst_iterator": {26}, "??Yiterator": {32},
         "??0const_iterator": {24}, "??$copy_backward": {51}, "??$copy": {51}}
SOURCE_COUNTS = {family: 16 for family in COUNTS}
SOURCE_COUNTS.update({"??Gconst_iterator": 9, "??Yiterator": 14})
PARENT_FAMILIES = {"?end": {"?push_back"}, "?begin": {"?insert"},
                   "??Giterator": {"?insert"}, "??Hiterator": {"?insert"},
                   "??0iterator": {"?begin", "?end"},
                   "??Gconst_iterator": {"??Giterator"}, "??Yiterator": {"??Hiterator"},
                   "??0const_iterator": {"??0iterator"}}
ANCHOR_FILES = {"vendor-vector-operation-origins.csv", "vendor-record-helper-origins.csv"}


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
            raise ValueError("truncated vector callee source symbol table")
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
    if (len(result) != 151 or len({item[0] for item in result}) != 151
            or Counter(item[5] for item in result) != SOURCE_COUNTS):
        raise ValueError("vector callee complete source set changed")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, source, _, masked, _ in definitions
                  if size == len(actual) and all(source[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def verify_witness(row, evidence, operations, anchors, visiting=None):
    """A short match needs a rooted source-typed caller or a complete copy callee."""
    visiting = set() if visiting is None else visiting
    if row["address"] in visiting:
        raise ValueError("circular vector callee ownership witness")
    visiting = visiting | {row["address"]}
    family, role = row["family_key"], row["witness_role"]
    if role == "child":
        if family not in PARENT_FAMILIES or row["callee_address"] or row["callee_file"]:
            raise ValueError("invalid vector callee parent witness")
        key = row["parent_address"]
        parent = evidence.get(key) or operations.get(key)
        if parent is None or parent["family_key"] not in PARENT_FAMILIES[family]:
            raise ValueError("vector callee lacks its same-family template parent")
        calls = [binding for binding in json.loads(parent["relocation_bindings"])
                 if binding["offset"] == int(row["parent_call_offset"])]
        if (len(calls) != 1 or calls[0]["type"] != "REL32" or calls[0]["addend"]
                or calls[0]["target_address"] != row["address"]
                or calls[0]["symbol"] != row["coff_symbol"]):
            raise ValueError("vector callee's exact source-typed parent call differs")
        if key in evidence:
            verify_witness(parent, evidence, operations, anchors, visiting)
    elif role == "wrapper":
        expected = {"??$copy": "??$_Copy_opt", "??$copy_backward": "??$_Copy_backward_opt"}
        if (family not in expected or row["parent_address"] or row["parent_call_offset"]
                or row["callee_file"] not in ANCHOR_FILES):
            raise ValueError("invalid copy wrapper callee witness")
        callee = anchors.get((row["callee_file"], row["callee_address"]))
        calls = json.loads(row["relocation_bindings"])
        if (callee is None or callee["coff_symbol"].split("@", 1)[0] != expected[family]
                or len(calls) != 2 or [call["offset"] for call in calls] != [13, 40]
                or any(call["type"] != "REL32" or call["addend"] for call in calls)
                or calls[1]["target_address"] != row["callee_address"]
                or calls[1]["symbol"] != row["callee_source_symbol"]
                or calls[1]["symbol"].split("@", 1)[0] != expected[family]
                or row["callee_body_sha256"] != callee["body_sha256"]):
            raise ValueError("copy wrapper lacks its complete typed copy callee")
    else:
        raise ValueError("unknown vector callee ownership witness")


def verify_callee_variant(row, object_path, comparison, record, sdk, target, anchors):
    """Replay the wrapper's exact source variant against the entire reviewed callee."""
    anchor = anchors[(row["callee_file"], row["callee_address"])]
    symbol = row["callee_source_symbol"]
    size = record.complete_aux_section_size(object_path.read_bytes(), symbol, comparison.coff_name)
    source, relocations = comparison.object_function(object_path, symbol, size)
    address = int(row["callee_address"], 16)
    actual = comparison.pe_bytes_at(target, address, size)
    if (size != int(anchor["size"])
            or hashlib.sha256(actual).hexdigest() != anchor["body_sha256"]
            or hashlib.sha256(source).hexdigest() != row["callee_source_sha256"]):
        raise ValueError("copy wrapper's complete callee variant changed")
    indirect = record.compare_complete_body(
        source, relocations, actual, address,
        json.loads(row["callee_relocation_bindings"]), comparison, sdk)
    if indirect != int(row["callee_indirect_call_count"]):
        raise ValueError("copy wrapper callee variant control flow differs")


def main():
    comparison = module("vector_callee_target", "compare-coff-function.py")
    record = module("vector_callee_record", "verify-vendor-record-origins.py")
    sdk = module("vector_callee_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-vector-callee-origins.csv")
    operations = {row["address"]: row for row in rows("vendor-vector-operation-origins.csv")}
    anchors = {(filename, row["address"]): row for filename in ANCHOR_FILES for row in rows(filename)}
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    if (len(evidence) != 16 or len({row["address"] for row in evidence}) != 16
            or Counter(row["family_key"] for row in evidence) != COUNTS
            or Counter(row["witness_role"] for row in evidence) != {"wrapper": 8, "child": 8}
            or sum(int(row["size"]) for row in evidence) != 660):
        raise ValueError("vector callee evidence set changed")
    for filename in ("verify-vendor-vector-operation-origins.py", "verify-vendor-record-helpers.py"):
        result = subprocess.run(
            [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts" / filename)],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("vector/copy anchor failed cold verification: " + filename)
    scratch = ROOT / "build/origin-vector-callee-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7VectorOperations.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7VectorOperations.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 vector callee compilation failed: " + result.stderr[-1000:])
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
                    or row["evidence_id"] != "R092" or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or any(address < int(key, 16) < address + size for key in functions)):
                raise ValueError("vector callee origin extent or ownership differs")
            actual = comparison.pe_bytes_at(target, address, size)
            matches = matching_symbols(actual, [item for item in definitions if item[5] == row["family_key"]])
            selected = by_symbol[row["coff_symbol"]]
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or not matches or matches != json.loads(row["matching_symbols"])
                    or row["coff_symbol"] not in matches or selected[1] != size
                    or selected[5] != row["family_key"]
                    or {by_symbol[name][5] for name in matches} != {row["family_key"]}
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("vector callee complete source/target body changed")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("vector callee complete control flow changed")
            relocation_count += len(selected[3])
        by_address = {row["address"]: row for row in evidence}
        for row in evidence:
            verify_witness(row, by_address, operations, anchors)
            if row["witness_role"] == "wrapper":
                verify_callee_variant(row, object_path, comparison, record, sdk, target, anchors)
    if relocation_count != 21:
        raise ValueError("vector callee typed relocation total changed")
    print("VC7 vector callee origins OK: 16 complete bodies, 660 bytes, 21 typed relocations; "
          "all short bodies have cold-reverified call witnesses; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
