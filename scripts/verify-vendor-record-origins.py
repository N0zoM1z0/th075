#!/usr/bin/env python3
"""Cold-check complete VC7 STL record templates and their split inventory rows."""
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


def rows(filename):
    with (ROOT / "config" / filename).open() as stream:
        return list(csv.DictReader(stream))


def complete_aux_section_size(data, wanted, coff_name):
    """Require the primary definition's auxiliary extent to cover its whole COMDAT.

    VC7 emits a local `$L...` catch label typed as a function in this same
    section. That label is internal, whereas a second external function is not.
    """
    if len(data) < 20:
        raise ValueError("truncated VC7 record probe")
    machine, count, _, symbols_offset, symbol_count, optional, _ = struct.unpack_from(
        "<HHIIIHH", data)
    strings_offset = symbols_offset + symbol_count * 18
    if (machine != 0x14C or not count or optional or strings_offset + 4 > len(data)):
        raise ValueError("invalid VC7 record COFF header")
    strings_size = struct.unpack_from("<I", data, strings_offset)[0]
    if strings_size < 4 or strings_offset + strings_size > len(data):
        raise ValueError("truncated VC7 record COFF strings")
    strings = data[strings_offset:strings_offset + strings_size]
    definitions = []
    index = 0
    while index < symbol_count:
        offset = symbols_offset + index * 18
        raw, value, section, kind, storage, aux = struct.unpack_from("<8sIhHBB", data, offset)
        if index + aux >= symbol_count:
            raise ValueError("truncated VC7 record COFF auxiliary definition")
        auxiliary = data[offset + 18:offset + 18 * (aux + 1)]
        definitions.append((coff_name(raw, strings), value, section, kind, storage, auxiliary))
        index += 1 + aux
    matches = [entry for entry in definitions if entry[0] == wanted and entry[2] > 0]
    if len(matches) != 1:
        raise ValueError("record probe lacks one defined template function")
    name, value, number, kind, storage, auxiliary = matches[0]
    if number > count or 20 + number * 40 > len(data):
        raise ValueError("record probe has an invalid code section")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (number - 1) * 40)
    peers = [entry for entry in definitions if entry[2] == number
             and entry[3] == 0x20 and entry[4] == 2]
    if (value or kind != 0x20 or storage != 2 or len(auxiliary) < 8
            or len(peers) != 1 or peers[0][0] != name
            or not section[9] & 0x20 or not section[9] & 0x1000
            or not section[3] or section[4] + section[3] > len(data)
            or struct.unpack_from("<I", auxiliary, 4)[0] != section[3]):
        raise ValueError("record probe definition is not one complete code COMDAT")
    return section[3]


def compare_complete_body(source, relocations, actual, address, recorded, comparison, sdk):
    if len(source) != len(actual) or len(recorded) != len(relocations):
        raise ValueError("record template extent or relocation count differs")
    solved = comparison.solved_relocations(source, actual, relocations, address)
    masked = set()
    call_fields, data_fields = {}, {}
    for source_relocation, resolution, binding in zip(relocations, solved, recorded):
        offset = source_relocation["offset"]
        if (offset < 0 or offset + 4 > len(source)
                or binding != {
                    "offset": offset,
                    "type": source_relocation["type"],
                    "symbol": source_relocation["symbol"],
                    "addend": source_relocation["addend"],
                    "target_address": resolution["solved_destination"],
                }):
            raise ValueError("record template typed relocation differs from target")
        if source_relocation["type"] not in ("DIR32", "REL32"):
            raise ValueError("unsupported record template relocation")
        field = address + offset
        if any(index in masked for index in range(offset, offset + 4)):
            raise ValueError("overlapping record template relocations")
        masked.update(range(offset, offset + 4))
        destination = int(binding["target_address"], 16)
        if source_relocation["type"] == "REL32":
            call_fields[field] = destination
        else:
            data_fields[field] = struct.unpack_from("<I", actual, offset)[0]
    if any(source[index] != actual[index]
           for index in range(len(source)) if index not in masked):
        raise ValueError("record template differs outside declared relocation fields")
    return sdk.verify_control_flow(actual, address, call_fields, data_fields)


def main():
    comparison = module("record_target", "compare-coff-function.py")
    sdk = module("record_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = rows("vendor-record-origin-spans.csv")
    if len(evidence) != 8 or len({row["address"] for row in evidence}) != len(evidence):
        raise ValueError("record template evidence must contain eight unique complete bodies")
    scratch = ROOT / "build/origin-record-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7OriginRecordContainers.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7OriginRecordContainers.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 record probe compilation failed")
        object_data = object_path.read_bytes()
        covered = set()
        total = 0
        for row in evidence:
            address, size = int(row["address"], 16), int(row["size"])
            source_size = complete_aux_section_size(object_data, row["coff_symbol"],
                                                    comparison.coff_name)
            source, relocations = comparison.object_function(
                object_path, row["coff_symbol"], source_size)
            actual = comparison.pe_bytes_at(target, address, size)
            if (size != source_size
                    or hashlib.sha256(source).hexdigest() != row["source_sha256"]
                    or hashlib.sha256(actual).hexdigest() != row["body_sha256"]):
                raise ValueError("record template source/target whole-body hash mismatch")
            parts = json.loads(row["covered_candidates"])
            cursor = address
            for index, part in enumerate(parts):
                key, part_size = part["address"], part["size"]
                if int(key, 16) != cursor or key in covered or part_size <= 0:
                    raise ValueError("record template inventory pieces have a gap or overlap")
                cursor += part_size
                covered.add(key)
                origin, function = origins[key], functions[key]
                if (origin["origin"] != "library" or origin["disposition"] != "exclude"
                        or origin["evidence_id"] != row["evidence_id"]
                        or function["owner"] != "library" or function["status"] != "excluded"
                        or int(function["size"]) != (size if index == 0 else part_size)):
                    raise ValueError("record template inventory ownership differs")
            if cursor != address + size:
                raise ValueError("record template pieces omit part of the whole body")
            interior = {key for key in functions if address <= int(key, 16) < cursor}
            if interior != {part["address"] for part in parts}:
                raise ValueError("record template has an unreviewed interior candidate")
            indirect = compare_complete_body(source, relocations, actual, address,
                                             json.loads(row["relocation_bindings"]),
                                             comparison, sdk)
            if indirect != int(row["indirect_call_count"]):
                raise ValueError("record template indirect-call count differs")
            total += size
    if len(covered) != 32:
        raise ValueError("record template fragments were not all reviewed")
    print(f"VC7 vendor record origins OK: {len(evidence)} whole COMDAT bodies, "
          f"{total} distinct bytes, {len(covered)} covered inventory candidates; "
          "no callee, source, or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError,
            json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
