#!/usr/bin/env python3
"""Recheck compiler cleanup provenance without granting authored exact credit."""
from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]


def load_module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


EH = load_module("compiler_eh", "compiler_eh.py")
DATA = load_module("compiler_data", "coff_data.py")


def verify_emission_probe(path, comparison):
    """Derive the handler and 28-byte FunctionInfo from independent COFF sections."""
    data = path.read_bytes()
    _, symbols = DATA.parse_symbols(data, comparison.coff_name)
    checked = 0
    for symbol in symbols:
        if not symbol["symbol"].startswith("__ehhandler$") or symbol["section"] <= 0:
            continue
        section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (symbol["section"] - 1) * 40)
        if symbol["offset"] != 0 or section[3] != 10:
            continue  # Shared compiler sections require separate extent evidence.
        code, relocations = comparison.object_function(path, symbol["symbol"], section[3])
        if (code != b"\xb8\0\0\0\0\xe9\0\0\0\0" or len(relocations) != 2
                or relocations[0]["offset"] != 1 or relocations[0]["type"] != "DIR32"
                or relocations[1]["offset"] != 6 or relocations[1]["type"] != "REL32"
                or relocations[1]["symbol"] != "___CxxFrameHandler"
                or any(row["addend"] for row in relocations)):
            raise ValueError("compiler probe differs from the full generated EH handler")
        definitions = [row for row in symbols if row["symbol"] == relocations[0]["symbol"]
                       and row["section"] > 0]
        if len(definitions) != 1:
            raise ValueError("compiler probe lacks its independent FunctionInfo definition")
        definition = definitions[0]
        header = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (definition["section"] - 1) * 40)
        if header[3] - definition["offset"] != 28:
            raise ValueError("compiler probe FunctionInfo has a different complete extent")
        words = struct.unpack_from("<7I", data, header[4] + definition["offset"])
        if words[0] != 0x19930520 or not words[1] or any(words[index] for index in [2, 4, 5, 6]):
            raise ValueError("compiler probe has an unsupported FunctionInfo schema")
        checked += 1
    if not checked:
        raise ValueError("no complete compiler-generated EH frame in the probe")
    return checked


def sections(target):
    pe = struct.unpack_from("<I", target, 0x3C)[0]
    count, optional = struct.unpack_from("<H", target, pe + 6)[0], struct.unpack_from("<H", target, pe + 20)[0]
    base = struct.unpack_from("<I", target, pe + 24 + 28)[0]
    result = []
    for index in range(count):
        offset = pe + 24 + optional + index * 40
        virtual = struct.unpack_from("<I", target, offset + 12)[0]
        raw_size = struct.unpack_from("<I", target, offset + 16)[0]
        flags = struct.unpack_from("<I", target, offset + 36)[0]
        result.append((base + virtual, raw_size, flags))
    return result


def verify_parameter_probe(path, comparison):
    data = path.read_bytes()
    _, symbols = DATA.parse_symbols(data, comparison.coff_name)
    for symbol in symbols:
        if not symbol["symbol"].startswith("__ehhandler$?ProbeCompilerStringParameter@@"):
            continue
        section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (symbol["section"] - 1) * 40)
        definitions = sorted((row for row in symbols if row["section"] == symbol["section"]
                              and row["type"] == 0x20), key=lambda row: row["offset"])
        if section[3] != 26 or [row["offset"] for row in definitions] != [0, 8, 16]:
            raise ValueError("parameter probe lacks the independent complete funclet extents")
        extent = definitions[1]["offset"] - definitions[0]["offset"]
        code, relocations = comparison.object_function(path, definitions[0]["symbol"], extent)
        if (code != b"\x8d\x4d\x08\xe9\0\0\0\0" or len(relocations) != 1
                or relocations[0]["offset"] != 4 or relocations[0]["type"] != "REL32"
                or relocations[0]["addend"]
                or not relocations[0]["symbol"].startswith("??1?$basic_string@")):
            raise ValueError("parameter probe does not emit complete argument cleanup dispatch")
        return
    raise ValueError("parameter probe lacks its named generated EH owner")


def verify_placement_probe(path, comparison):
    data = path.read_bytes()
    _, symbols = DATA.parse_symbols(data, comparison.coff_name)
    for symbol in symbols:
        if not symbol["symbol"].startswith("__ehhandler$?ProbeCompilerPlacementCleanup@@"):
            continue
        section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (symbol["section"] - 1) * 40)
        definitions = sorted((row for row in symbols if row["section"] == symbol["section"]
                              and row["type"] == 0x20), key=lambda row: row["offset"])
        if section[3] != 27 or [row["offset"] for row in definitions] != [0, 17]:
            raise ValueError("placement probe lacks its independent complete cleanup extent")
        code, relocations = comparison.object_function(path, definitions[0]["symbol"], definitions[1]["offset"])
        if (code != b"\x8b\x45\x08\x50\x8b\x4d\xec\x51\xe8\0\0\0\0\x83\xc4\x08\xc3"
                or len(relocations) != 1 or relocations[0]["offset"] != 9
                or relocations[0]["type"] != "REL32" or relocations[0]["addend"]
                or relocations[0]["symbol"] != "??3@YAXPAX0@Z"):
            raise ValueError("placement probe does not emit complete context cleanup dispatch")
        return
    raise ValueError("placement probe lacks its named generated EH owner")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, default=ROOT / "build/probes/CompilerEHOriginTemplates.obj")
    parser.add_argument("--parameter-probe", type=Path, default=ROOT / "build/probes/CompilerEHParameterTemplates.obj")
    arguments = parser.parse_args()
    comparison = load_module("compiler_coff", "compare-coff-function.py")
    templates = verify_emission_probe(arguments.probe, comparison)
    target = comparison.verified_target()
    mapping = sections(target)

    def read(address, size, executable):
        for base, extent, flags in mapping:
            if base <= address and address + size <= base + extent:
                if (not flags & 0x40000000 or bool(flags & 0x20000000) != executable
                        or not executable and flags & 0x80000000):
                    raise ValueError("EH evidence is outside immutable data or executable code")
                return comparison.pe_bytes_at(target, address, size)
        raise ValueError("EH evidence exceeds a complete mapped PE section")

    def rows(name):
        with (ROOT / "config" / name).open() as stream:
            return list(csv.DictReader(stream))

    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    function_entries = {int(address, 16) for address in functions}
    frames = rows("compiler-eh-frames.csv")
    references = {}
    if not frames or len({row["handler_address"] for row in frames}) != len(frames):
        raise ValueError("empty or duplicate EH frame evidence")
    for row in frames:
        entries = EH.verify_frame(row, lambda a, n: read(a, n, True),
                               lambda a, n: read(a, n, False), function_entries)
        for entry in entries:
            if int(entry["cleanup_address"], 16):
                references.setdefault(entry["cleanup_address"], []).append({
                    "handler_address": row["handler_address"],
                    "funcinfo_address": row["funcinfo_address"],
                    "state_index": entry["state_index"]})
    evidence = rows("compiler-origin-evidence.csv")
    if not evidence or len({row["address"] for row in evidence}) != len(evidence):
        raise ValueError("empty or duplicate compiler cleanup evidence")
    if any(row["template_kind"] == "parameter-object" for row in evidence):
        verify_parameter_probe(arguments.parameter_probe, comparison)
    if any(row["template_kind"] == "placement-allocation" for row in evidence):
        verify_placement_probe(arguments.parameter_probe, comparison)
    total = 0
    for row in evidence:
        key, size = row["address"], int(row["size"])
        code = read(int(key, 16), size, True)
        if hashlib.sha256(code).hexdigest() != row["body_sha256"]:
            raise ValueError("complete compiler cleanup target hash mismatch")
        kind, destination = EH.cleanup_template(code, int(key, 16), function_entries)
        if (kind != row["template_kind"] or destination != int(row["callee_address"], 16)
                or references.get(key) != json.loads(row["frame_references"])
                or int(functions[key]["size"]) != size or origins[key]["origin"] != "compiler"
                or origins[key]["disposition"] != "exclude"
                or origins[key]["evidence_id"] != row["evidence_id"]):
            raise ValueError("compiler cleanup shape, metadata binding or ledger mismatch")
        total += size
    print(f"Compiler EH origin evidence OK: {len(evidence)} complete cleanup bodies, {total} bytes; "
          f"{len(frames)} registered frames, {templates} independent generated handler/metadata templates; "
          "no ownership credit to callees or parent bodies; no reconstruction exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
