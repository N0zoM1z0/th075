#!/usr/bin/env python3
"""Cold-verify source-defined empty virtual background methods and vtable slots."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "?NoOp@BackgroundNoOpProbe@@UAEXXZ"
PROFILE = ("/Od", "/Ob0", "/Gy", "/GR-", "/GX-", "/Zi", "/GS", "/I", "src")


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(name):
    with (ROOT / "config" / name).open(newline="") as stream:
        return list(csv.DictReader(stream))


def source_definition(path, comparison, coff_data):
    data = path.read_bytes()
    count, symbols = coff_data.parse_symbols(data, comparison.coff_name)
    found = [row for row in symbols if row["symbol"] == SYMBOL and row["section"] > 0]
    if len(found) != 1 or found[0]["offset"] != 0 or found[0]["type"] != 0x20:
        raise ValueError("no-op probe lacks one function definition")
    section_number = found[0]["section"]
    if not 1 <= section_number <= count:
        raise ValueError("no-op probe section is invalid")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (section_number - 1) * 40)
    peers = [row for row in symbols if row["section"] == section_number and row["type"] == 0x20]
    if (section[3] != 11 or section[7] or not section[9] & 0x20
            or not section[9] & 0x1000 or len(peers) != 1):
        raise ValueError("no-op probe lacks a sole complete code COMDAT")
    code, relocations = comparison.object_function(path, SYMBOL, 11)
    if relocations:
        raise ValueError("no-op probe body has unexpected relocations")
    return code


def main():
    comparison = module("background_noop_target", "compare-coff-function.py")
    coff_data = module("background_noop_coff", "coff_data.py")
    authored = module("background_noop_authored", "verify-authored-origins.py")
    destructors = module("background_noop_vtables", "verify-background-destructor-origins.py")
    background = module("background_noop_constructors", "verify-background-origins.py")
    target = comparison.verified_target()
    vtables = destructors.constructor_vtables(target, comparison, background)
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    authored_evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    evidence = rows("background-noop-origin-evidence.csv")
    if len(evidence) != 89 or len({row["address"] for row in evidence}) != 89:
        raise ValueError("background no-op cohort is incomplete or duplicated")
    scratch = ROOT / "build/origin-background-noop-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7BackgroundNoOp.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7BackgroundNoOp.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 no-op virtual method probe failed to compile")
        source = source_definition(object_path, comparison, coff_data)
    source_hash = hashlib.sha256(source).hexdigest()
    slots = {}
    for vtable, constructor in vtables.items():
        data = comparison.pe_bytes_at(target, vtable, 60)
        for index in range(15):
            address = struct.unpack_from("<I", data, index * 4)[0]
            slots.setdefault(address, []).append((vtable, constructor, index))
    for row in evidence:
        key, address = row["address"], int(row["address"], 16)
        function, origin, body_record = functions[key], origins[key], authored_evidence[key]
        if (row["evidence_id"] not in ("R058", "R059")
                or origin["evidence_id"] != row["evidence_id"]
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or body_record["evidence_id"] != row["evidence_id"]
                or int(function["size"]) != 11
                or function["proposed_name"] != body_record["inferred_role"]
                or function["proposed_name"] != "BackgroundStage::NoOpVirtualAt" + key[2:]
                or row["source_sha256"] != source_hash):
            raise ValueError("background no-op witness/ledger differs")
        body = comparison.pe_bytes_at(target, address, 11)
        if (body != source or hashlib.sha256(body).hexdigest() != row["body_sha256"]
                or body_record["body_sha256"] != row["body_sha256"]
                or authored.verify_body(body, address) != (1, 0)):
            raise ValueError("background no-op whole target body/CFG differs")
        found = slots.get(address, [])
        if (len(found) != 1 or row["vtable_address"] != f"0x{found[0][0]:08X}"
                or row["constructor_address"] != found[0][1]
                or int(row["slot_index"]) != found[0][2]
                or found[0][2] not in (1, 2, 3)):
            raise ValueError("background no-op vtable slot lacks a unique constructor binding")
    print("Background no-op origins OK: 89 complete VC7 source-shaped virtual "
          "methods, each in one verified game background vtable; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
