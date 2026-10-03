#!/usr/bin/env python3
"""Cold-check complete VC7 construction, copy and vector insertion wrappers."""
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
COUNTS = {"??$_Construct": 11, "??$_Copy_backward_opt": 4, "?push_back": 1, "?insert": 1}
RELOCATIONS = {"??$_Construct": 1, "??$_Copy_backward_opt": 1, "?push_back": 5, "?insert": 6}
SIZES = {"??$_Construct": {58, 60}, "??$_Copy_backward_opt": {51}, "?push_back": {99}, "?insert": {114}}
SOURCE_COUNTS = {"??$_Construct": 9, "??$_Copy_backward_opt": 4, "?push_back": 16, "?insert": 16}


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
            raise ValueError("truncated vector operation source symbol table")
        name = comparison.coff_name(raw, strings)
        family = name.split("@", 1)[0]
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and family in COUNTS and "std@@" in name):
            size = record.complete_aux_section_size(data, name, comparison.coff_name)
            if size not in SIZES[family]:
                index += 1 + auxiliary
                continue
            source, relocations = comparison.object_function(path, name, size)
            if len(relocations) != RELOCATIONS[family]:
                raise ValueError("vector operation source relocation count changed")
            masked = {byte for relocation in relocations
                      for byte in range(relocation["offset"], relocation["offset"] + 4)}
            result.append((name, size, source, relocations, masked, family))
        index += 1 + auxiliary
    if (len(result) != 45 or len({item[0] for item in result}) != 45
            or Counter(item[5] for item in result) != SOURCE_COUNTS):
        raise ValueError("vector operation complete source set changed")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, source, _, masked, _ in definitions
                  if size == len(actual) and all(source[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def main():
    comparison = module("vector_operation_target", "compare-coff-function.py")
    record = module("vector_operation_record", "verify-vendor-record-origins.py")
    sdk = module("vector_operation_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-vector-operation-origins.csv")
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    if (len(evidence) != 17 or len({row["address"] for row in evidence}) != 17
            or Counter(row["family_key"] for row in evidence) != COUNTS
            or sum(int(row["size"]) for row in evidence) != 1057):
        raise ValueError("vector operation evidence set changed")
    result = subprocess.run(
        [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts/verify-runtime-local-origins.py")],
        cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("CRT memmove anchor failed complete vendor replay")
    scratch = ROOT / "build/origin-vector-operation-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7VectorOperations.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7VectorOperations.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 vector operation compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path, comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        placement_symbol = "??2@YAPAXIPAX@Z"
        placement_size = record.complete_aux_section_size(
            object_path.read_bytes(), placement_symbol, comparison.coff_name)
        placement, placement_relocations = comparison.object_function(
            object_path, placement_symbol, placement_size)
        if (placement_size != 8 or placement_relocations
                or placement != comparison.pe_bytes_at(target, 0x004063D0, 8)
                or origins["0x004063D0"]["origin"] != "library"
                or int(functions["0x004063D0"]["size"]) != 8
                or origins["0x00641260"]["origin"] != "library"
                or int(functions["0x00641260"]["size"]) != 829):
            raise ValueError("placement-new or CRT memmove complete anchor differs")
        relocation_count = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (row["family_key"] not in SIZES or size not in SIZES[row["family_key"]] or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or row["evidence_id"] != "R091" or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or any(address < int(key, 16) < address + size for key in functions)):
                raise ValueError("vector operation origin extent or ownership differs")
            actual = comparison.pe_bytes_at(target, address, size)
            matches = matching_symbols(actual, definitions)
            selected = by_symbol[row["coff_symbol"]]
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or not matches or matches != json.loads(row["matching_symbols"])
                    or row["coff_symbol"] not in matches or selected[1] != size
                    or selected[5] != row["family_key"]
                    or {by_symbol[name][5] for name in matches} != {row["family_key"]}
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("vector operation complete source/target body changed")
            bindings = json.loads(row["relocation_bindings"])
            if row["family_key"] in ("??$_Construct", "??$_Copy_backward_opt"):
                expected = ((placement_symbol, "0x004063D0") if row["family_key"] == "??$_Construct"
                            else ("_memmove", "0x00641260"))
                if (len(bindings) != 1 or bindings[0]["type"] != "REL32"
                        or bindings[0]["addend"]
                        or (bindings[0]["symbol"], bindings[0]["target_address"]) != expected):
                    raise ValueError("construction/copy helper typed anchor differs")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("vector operation complete control flow changed")
            relocation_count += len(selected[3])
    if relocation_count != 26:
        raise ValueError("vector operation typed relocation total changed")
    print("VC7 vector operation origins OK: 17 complete bodies, 1057 bytes, "
          "26 typed relocations and complete CFG; construction/copy anchors replayed; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
