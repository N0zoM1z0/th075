#!/usr/bin/env python3
"""Verify complete linker import thunks against the pinned PE import directory."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys


ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def c_string(read, address, limit=256):
    result = bytearray()
    for offset in range(limit):
        value = read(address + offset, 1)[0]
        if not value:
            return result.decode("ascii")
        result.append(value)
    raise ValueError("unterminated PE import string")


def import_table(read, image_base, directory_rva, directory_size):
    """Read every complete descriptor and original/IAT thunk from the raw PE."""
    if not directory_rva or directory_size < 40 or directory_size % 20:
        raise ValueError("invalid PE import directory extent")
    slots = {}
    terminated = False
    for descriptor in range(directory_size // 20):
        raw = read(image_base + directory_rva + descriptor * 20, 20)
        if raw == bytes(20):
            terminated = True
            break
        original_rva, stamp, forwarder, name_rva, iat_rva = struct.unpack("<IIIII", raw)
        if not name_rva or not iat_rva or stamp or forwarder:
            raise ValueError("unsupported PE import descriptor")
        dll = c_string(read, image_base + name_rva)
        if not dll:
            raise ValueError("empty PE import library name")
        lookup_rva = original_rva or iat_rva
        ended = False
        for index in range(512):
            raw_lookup = read(image_base + lookup_rva + index * 4, 4)
            lookup = struct.unpack("<I", raw_lookup)[0]
            slot = image_base + iat_rva + index * 4
            actual = struct.unpack("<I", read(slot, 4))[0]
            if not lookup:
                if actual:
                    raise ValueError("PE IAT extends beyond its lookup table")
                ended = True
                break
            if actual != lookup or slot in slots:
                raise ValueError("PE IAT slot differs from its unique lookup")
            if lookup & 0x80000000:
                name = "#" + str(lookup & 0xFFFF)
            else:
                name = c_string(read, image_base + lookup + 2)
                if not name:
                    raise ValueError("empty PE import symbol")
            slots[slot] = (dll, name)
        if not ended:
            raise ValueError("unterminated PE import lookup")
    if not terminated or not slots:
        raise ValueError("unterminated or empty PE import directory")
    return slots


def pe_imports(target, comparison):
    if len(target) < 0x40 or target[:2] != b"MZ":
        raise ValueError("target lacks DOS/PE header")
    pe = struct.unpack_from("<I", target, 0x3C)[0]
    if (pe + 24 + 112 > len(target) or target[pe:pe + 4] != b"PE\0\0"
            or struct.unpack_from("<H", target, pe + 4)[0] != 0x14C):
        raise ValueError("target lacks i386 PE header")
    optional = pe + 24
    if (struct.unpack_from("<H", target, optional)[0] != 0x10B
            or struct.unpack_from("<I", target, optional + 92)[0] < 2):
        raise ValueError("target lacks PE32 import directory")
    base = struct.unpack_from("<I", target, optional + 28)[0]
    rva, size = struct.unpack_from("<II", target, optional + 104)
    return import_table(lambda address, extent: comparison.pe_bytes_at(
        target, address, extent), base, rva, size)


def check_thunk(body, slot, imported, expected_dll, expected_name):
    if (len(body) != 6 or body[:2] != b"\xFF\x25"
            or struct.unpack_from("<I", body, 2)[0] != slot):
        raise ValueError("import thunk is not one complete FF 25 instruction")
    if imported != (expected_dll, expected_name):
        raise ValueError("import thunk slot does not name the recorded import")


def main():
    comparison = module("import_target", "compare-coff-function.py")
    target = comparison.verified_target()
    slots = pe_imports(target, comparison)
    with (ROOT / "config/import-origin-evidence.csv").open() as stream:
        records = list(csv.DictReader(stream))
    with (ROOT / "config/function-origins.csv").open() as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/functions.csv").open() as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    if not records or len({row["address"] for row in records}) != len(records):
        raise ValueError("empty or duplicate import origin evidence")
    for record in records:
        address = record["address"]
        slot = int(record["iat_slot"], 16)
        origin = origins[address]
        function = functions[address]
        if (record["evidence_id"] != origin["evidence_id"]
                or origin["origin"] != "compiler" or origin["disposition"] != "exclude"
                or int(function["size"]) != 6 or function["owner"] != "compiler"
                or function["status"] != "excluded"):
            raise ValueError("import origin ledger differs from evidence")
        body = comparison.pe_bytes_at(target, int(address, 16), 6)
        if hashlib.sha256(body).hexdigest() != record["body_sha256"]:
            raise ValueError("complete import thunk hash differs from target")
        check_thunk(body, slot, slots.get(slot), record["dll"], record["symbol"])
    print(f"PE import origin evidence OK: {len(records)} complete six-byte linker thunks, "
          f"{len(slots)} independently decoded IAT slots; no callee or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
