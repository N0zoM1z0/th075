#!/usr/bin/env python3
"""Cold-check complete VC7 deque algorithms and corroborated short helpers."""
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
COUNTS = {"??$_Copy_opt": 8, "??$_Copy_backward_opt": 7, "??$fill": 1,
          "??$copy": 8, "??$copy_backward": 7, "??$_Ptr_cat": 8,
          "??Eiterator": 8, "??Fiterator": 7}
ROOT_FAMILIES = {"??$_Copy_opt", "??$_Copy_backward_opt", "??$fill"}
WRAPPER_CALLEES = {"??$copy": "??$_Copy_opt",
                   "??$copy_backward": "??$_Copy_backward_opt"}
CHILD_PARENTS = {"??Eiterator": ROOT_FAMILIES,
                 "??Fiterator": {"??$_Copy_backward_opt"},
                 "??$_Ptr_cat": set(WRAPPER_CALLEES)}


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
            raise ValueError("truncated deque algorithm source symbol table")
        name = comparison.coff_name(raw, strings)
        family = name.split("@", 1)[0]
        if (section > 0 and kind == 0x20 and storage == 2 and auxiliary
                and family in COUNTS and "?$deque@" in name):
            size = record.complete_aux_section_size(data, name, comparison.coff_name)
            source, relocations = comparison.object_function(path, name, size)
            masked = {byte for relocation in relocations
                      for byte in range(relocation["offset"], relocation["offset"] + 4)}
            result.append((name, size, source, relocations, masked, family))
        index += 1 + auxiliary
    if (len(result) != 104 or len({item[0] for item in result}) != 104
            or Counter(item[5] for item in result) != {key: 13 for key in COUNTS}):
        raise ValueError("expected thirteen complete source definitions per algorithm family")
    return result


def matching_symbols(actual, definitions):
    return sorted(name for name, size, source, _, masked, _ in definitions
                  if size == len(actual) and all(source[index] == actual[index]
                                                 for index in range(size)
                                                 if index not in masked))


def corroborate(row, by_address):
    """Require a source-typed parent/callee witness for every short body."""
    family, role = row["family_key"], row["evidence_role"]
    bindings = json.loads(row["relocation_bindings"])
    if role == "root":
        if family not in ROOT_FAMILIES or any(row[key] for key in (
                "parent_address", "parent_call_offset", "callee_address")):
            raise ValueError("invalid complete algorithm root witness")
    elif role == "wrapper":
        callee = by_address.get(row["callee_address"])
        if (family not in WRAPPER_CALLEES or callee is None
                or callee["evidence_role"] != "root"
                or callee["family_key"] != WRAPPER_CALLEES[family]
                or len(bindings) != 2 or row["parent_address"] or row["parent_call_offset"]):
            raise ValueError("copy wrapper lacks the complete same-family algorithm callee")
        tag, call = bindings
        tag_body = by_address.get(tag["target_address"])
        if (call["offset"] != 56 or call["type"] != "REL32" or call["addend"]
                or call["target_address"] != callee["address"]
                or call["symbol"] not in json.loads(callee["matching_symbols"])
                or tag["offset"] != 13 or tag["type"] != "REL32" or tag["addend"]
                or tag["symbol"].split("@", 1)[0] != "??$_Ptr_cat"
                or tag_body is None or tag_body["evidence_role"] != "child"
                or tag_body["family_key"] != "??$_Ptr_cat"
                or tag["symbol"] not in json.loads(tag_body["matching_symbols"])):
            raise ValueError("copy wrapper's typed algorithm/tag binding differs")
    elif role == "child":
        parent = by_address.get(row["parent_address"])
        if (family not in CHILD_PARENTS or parent is None or row["callee_address"]
                or parent["family_key"] not in CHILD_PARENTS[family]
                or parent["evidence_role"] not in ("root", "wrapper") or bindings):
            raise ValueError("short deque helper lacks an independently verified parent")
        calls = [binding for binding in json.loads(parent["relocation_bindings"])
                 if binding["offset"] == int(row["parent_call_offset"])]
        if (len(calls) != 1 or calls[0]["type"] != "REL32" or calls[0]["addend"]
                or calls[0]["target_address"] != row["address"]
                or calls[0]["symbol"] != row["coff_symbol"]):
            raise ValueError("short deque helper's exact source-typed parent call differs")
    else:
        raise ValueError("unknown deque algorithm witness role")


def main():
    comparison = module("deque_algorithm_target", "compare-coff-function.py")
    record = module("deque_algorithm_record", "verify-vendor-record-origins.py")
    sdk = module("deque_algorithm_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-deque-algorithm-origins.csv")
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    if (len(evidence) != 54 or len({row["address"] for row in evidence}) != 54
            or Counter(row["family_key"] for row in evidence) != COUNTS
            or Counter(row["evidence_role"] for row in evidence)
            != {"root": 16, "wrapper": 15, "child": 23}):
        raise ValueError("deque algorithm evidence set changed")
    by_address = {row["address"]: row for row in evidence}
    scratch = ROOT / "build/origin-deque-algorithm-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DequeAlgorithms.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DequeAlgorithms.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 deque algorithm compilation failed: " + result.stderr[-1000:])
        definitions = source_definitions(object_path.read_bytes(), object_path, comparison, record)
        by_symbol = {definition[0]: definition for definition in definitions}
        total, relocation_count = 0, 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            function, origin = functions[row["address"]], origins[row["address"]]
            if (size < 1 or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or row["evidence_id"] != "R085" or origin["evidence_id"] != row["evidence_id"]
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or any(address < int(key, 16) < address + size for key in functions)):
                raise ValueError("deque algorithm origin extent or ownership ledger differs")
            actual = comparison.pe_bytes_at(target, address, size)
            matches = matching_symbols(actual, definitions)
            selected = by_symbol[row["coff_symbol"]]
            if (hashlib.sha256(actual).hexdigest() != row["body_sha256"]
                    or not matches or matches != json.loads(row["matching_symbols"])
                    or row["coff_symbol"] not in matches or selected[1] != size
                    or selected[5] != row["family_key"]
                    or hashlib.sha256(selected[2]).hexdigest() != row["source_sha256"]):
                raise ValueError("deque algorithm complete source/target body changed")
            families = {by_symbol[name][5] for name in matches}
            if (families != {row["family_key"]}
                    and families != set(WRAPPER_CALLEES)):
                raise ValueError("ambiguous deque algorithm template family")
            indirect = record.compare_complete_body(
                selected[2], selected[3], actual, address,
                json.loads(row["relocation_bindings"]), comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("deque algorithm complete control flow changed")
            total += size
            relocation_count += len(selected[3])
        for row in evidence:
            corroborate(row, by_address)
    if total != 2889 or relocation_count != 108:
        raise ValueError("deque algorithm complete extent or relocation totals changed")
    print(f"VC7 deque algorithm origins OK: {len(evidence)} complete bodies, "
          f"{total} bytes, {relocation_count} typed relocations; "
          "all short helpers have source-typed parent/callee witnesses; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
