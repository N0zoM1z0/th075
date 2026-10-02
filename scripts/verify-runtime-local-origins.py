#!/usr/bin/env python3
"""Recheck whole CRT bodies whose relocations resolve within one vendor member."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


RUNTIME = module("local_runtime", "verify-runtime-origins.py")
COFF = module("local_coff", "compare-coff-function.py")


def bind_local(code, relocations, address, allowed_external):
    result = bytearray(code)
    destinations = []
    occupied = set()
    for relocation in relocations:
        offset = relocation["offset"]
        local = relocation["local_symbol_offset"]
        if (relocation["type"] != "DIR32" or local is None or offset < 0
                or offset + 4 > len(code) or any(i in occupied for i in range(offset, offset + 4))):
            raise ValueError("vendor body has unsupported or overlapping relocation")
        occupied.update(range(offset, offset + 4))
        destination = (address + local + relocation["addend"]) & 0xFFFFFFFF
        if not (address <= destination < address + len(code) or destination in allowed_external):
            raise ValueError("vendor-local relocation escapes the verified complete member")
        struct.pack_into("<I", result, offset, destination)
        destinations.append(destination)
    return bytes(result), destinations


def main():
    target = COFF.verified_target()
    with (ROOT / "config/runtime-local-evidence.csv").open() as stream:
        evidence = list(csv.DictReader(stream))
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    if len(evidence) != 3 or len({row["address"] for row in evidence}) != len(evidence):
        raise ValueError("runtime-local cohort is incomplete or duplicated")
    archives = {}
    total = 0
    relocations_checked = 0
    with tempfile.TemporaryDirectory(dir=ROOT / ".analysis") as directory:
        path = Path(directory) / "vendor.obj"
        for row in evidence:
            lib = row["library"]
            if lib != "libcmt.lib":
                raise ValueError("unsupported CRT archive identity")
            if lib not in archives:
                data = (ROOT / ".tools/msvc710/Vc7/lib" / lib).read_bytes()
                archives[lib] = (hashlib.sha256(data).hexdigest(),
                                 {offset: (name, body) for offset, name, body
                                  in RUNTIME.archive_members(data)})
            digest, members = archives[lib]
            if digest != row["archive_sha256"]:
                raise ValueError("CRT local archive SHA differs")
            name, body = members[int(row["member_offset"])]
            if name != row["member"]:
                raise ValueError("CRT local archive member differs")
            path.write_bytes(body)
            code, relocs = COFF.object_function(path, row["coff_symbol"])
            address, size = int(row["address"], 16), int(row["size"])
            if (len(code) != size or code[-1] != 0xC3
                    or hashlib.sha256(code).hexdigest() != row["body_sha256"]
                    or len(relocs) != int(row["relocation_count"])
                    or row["extent_basis"] != "function-auxiliary-record"
                    or int(functions[row["address"]]["size"]) != size
                    or origins[row["address"]]["origin"] != "library"
                    or origins[row["address"]]["disposition"] != "exclude"
                    or origins[row["address"]]["evidence_id"] != row["evidence_id"]):
                raise ValueError("CRT local complete extent/hash/ledger differs")
            dependencies = set()
            if row["dependency_symbol"]:
                dependency, dependency_relocs = COFF.object_function(path, row["dependency_symbol"])
                if (dependency_relocs or len(dependency) != int(row["dependency_size"])
                        or dependency != COFF.pe_bytes_at(target, int(row["dependency_address"], 16), len(dependency))):
                    raise ValueError("CRT member-local dependency lacks its own complete vendor body")
                dependencies.add(int(row["dependency_address"], 16))
            elif row["dependency_address"] or row["dependency_size"]:
                raise ValueError("partial CRT member-local dependency evidence")
            linked, destinations = bind_local(code, relocs, address, dependencies)
            if (len(destinations) != int(row["relocation_count"])
                    or linked != COFF.pe_bytes_at(target, address, size)
                    or dependencies - set(destinations)):
                raise ValueError("CRT complete linked local body differs from target")
            total += size
            relocations_checked += len(relocs)
    print(f"CRT local origin evidence OK: {len(evidence)} whole vendor bodies, "
          f"{total} bytes, {relocations_checked} completely linked local relocations; "
          "external helper dependency independently checked; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
