#!/usr/bin/env python3
"""Recheck typed vendor-call witnesses for short whole SDK COMDAT origins."""
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


SDK = module("short_sdk", "verify-sdk-origins.py")
RUNTIME = module("short_runtime", "verify-runtime-origins.py")
COFF = module("short_coff", "compare-coff-function.py")


def typed_call_witness(source, actual, relocations, offset, symbol, parent, destination):
    """Only a full-body COFF fingerprint and its own typed CALL may name a short callee."""
    if len(source) != len(actual) or not source:
        raise ValueError("typed caller has a different complete extent")
    masked = {index for relocation in relocations
              for index in range(relocation["offset"], relocation["offset"] + 4)}
    if any(source[index] != actual[index] for index in range(len(source)) if index not in masked):
        raise ValueError("typed caller differs outside complete COFF relocation fields")
    matches = [relocation for relocation in relocations if relocation["offset"] == offset]
    if (len(matches) != 1 or offset < 1 or offset + 4 > len(source)
            or source[offset - 1] != actual[offset - 1] or actual[offset - 1] != 0xE8
            or matches[0]["type"] != "REL32" or matches[0]["symbol"] != symbol
            or matches[0]["addend"] != 0 or matches[0]["local_symbol_offset"] is not None
            or (parent + offset + 4 + struct.unpack_from("<i", actual, offset)[0]) & 0xFFFFFFFF
            != destination):
        raise ValueError("typed caller's actual direct CALL differs from vendor definition")


def main():
    with (ROOT / "config/sdk-short-origin-witnesses.csv").open() as stream:
        witnesses = list(csv.DictReader(stream))
    with (ROOT / "config/sdk-origin-evidence.csv").open() as stream:
        sdk = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    if len(witnesses) != 31 or len({row["address"] for row in witnesses}) != len(witnesses):
        raise ValueError("short SDK witness cohort is incomplete or duplicated")
    target = COFF.verified_target()
    archive = (ROOT / ".tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib").read_bytes()
    digest = hashlib.sha256(archive).hexdigest()
    members = {offset: (name, body) for offset, name, body in RUNTIME.archive_members(archive)}
    with tempfile.TemporaryDirectory(dir=ROOT / ".analysis") as directory:
        path = Path(directory) / "vendor.obj"
        for witness in witnesses:
            key = witness["address"]
            record = sdk[key]
            if (record["evidence_id"] != "R026" or witness["evidence_id"] != "R026"
                    or origins[key]["origin"] != "library"
                    or origins[key]["disposition"] != "exclude"
                    or origins[key]["evidence_id"] != "R026"
                    or record["coff_symbol"] != witness["source_symbol"]
                    or record["library"] != "d3dx8.lib"
                    or record["archive_sha256"] != digest
                    or int(record["size"]) > 31):
                raise ValueError("short SDK body/witness provenance differs")
            name, body = members[int(witness["caller_member_offset"])]
            if name != witness["caller_member"]:
                raise ValueError("typed caller source member differs")
            source_size = SDK.complete_comdat_size(body, witness["caller_symbol"], COFF.coff_name)
            if (source_size != int(witness["caller_size"])
                    or source_size != int(functions[witness["caller_address"]]["size"])):
                raise ValueError("typed caller lacks its own complete source boundary")
            path.write_bytes(body)
            source, relocations = COFF.object_function(path, witness["caller_symbol"], source_size)
            parent = int(witness["caller_address"], 16)
            actual = COFF.pe_bytes_at(target, parent, source_size)
            typed_call_witness(source, actual, relocations, int(witness["call_offset"]),
                               witness["source_symbol"], parent, int(key, 16))
    print(f"Short SDK origin witnesses OK: {len(witnesses)} complete vendor caller bodies, "
          "typed direct-call fields and distinct complete short callee extents; "
          "caller origin remains independent; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
