#!/usr/bin/env python3
"""Recheck compiler static-lifetime origins without source or exact credit."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


STATIC = module("static_lifetime", "static_lifetime.py")
COFF_DATA = module("static_coff_data", "coff_data.py")
RUNTIME = module("static_runtime", "verify-runtime-origins.py")
COMPARISON = module("static_comparison", "compare-coff-function.py")
SECTIONS = module("static_compiler_sections", "verify-compiler-origins.py")


def rows(name):
    with (ROOT / "config" / name).open() as stream:
        return list(csv.DictReader(stream))


def mask_relocations(code, relocations, actual):
    if len(code) != len(actual):
        raise ValueError("vendor body has a different complete target extent")
    masked = {index for relocation in relocations
              for index in range(relocation["offset"], relocation["offset"] + 4)}
    if any(code[index] != actual[index] for index in range(len(code)) if index not in masked):
        raise ValueError("vendor body differs outside explicit relocation fields")


def verify_registration_vendor(target):
    archive = (ROOT / ".tools/msvc710/Vc7/lib/libcmt.lib").read_bytes()
    if hashlib.sha256(archive).hexdigest() != "6e2b3742e58245de52149137f64281b73db1487a07a31e165fff269fbf9b2ee8":
        raise ValueError("pinned CRT archive differs")
    for offset, name, body in RUNTIME.archive_members(archive):
        if offset == 1411494 and name == "build\\intel\\mt_obj\\onexit.obj":
            break
    else:
        raise ValueError("pinned onexit archive member is missing")
    with tempfile.TemporaryDirectory(dir=ROOT / ".analysis") as temporary:
        path = Path(temporary) / "onexit.obj"
        path.write_bytes(body)
        onexit, onexit_reloc = COMPARISON.object_function(path, "__onexit")
        atexit, atexit_reloc = COMPARISON.object_function(path, "_atexit")
    if (len(onexit) != 56 or len(atexit) != 18 or len(onexit_reloc) != 6
            or [(item["offset"], item["type"], item["symbol"]) for item in atexit_reloc]
            != [(5, "REL32", "__onexit")]):
        raise ValueError("CRT exit registration has different own COFF extents/bindings")
    mask_relocations(onexit, onexit_reloc, COMPARISON.pe_bytes_at(target, 0x641653, 56))
    actual = COMPARISON.pe_bytes_at(target, 0x64168B, 18)
    mask_relocations(atexit, atexit_reloc, actual)
    destination = 0x64168B + 9 + struct.unpack_from("<i", actual, 5)[0]
    if destination != 0x641653:
        raise ValueError("exit registration call does not reach the checked CRT body")


def verify_generated_probe(path):
    data = path.read_bytes()
    _, symbols = COFF_DATA.parse_symbols(data, COMPARISON.coff_name)
    by_kind = {28: "object-init", 42: "array-init", 24: "array-finalizer"}
    observed = {kind: 0 for kind in STATIC.KINDS}
    for symbol in symbols:
        if not symbol["symbol"].startswith("_$E") or symbol["section"] <= 0:
            continue
        section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (symbol["section"] - 1) * 40)
        if (symbol["offset"] or not section[9] & 0x20 or not section[9] & 0x20000000
                or section[3] not in (15, 24, 28, 42)):
            raise ValueError("compiler probe wrapper is not a complete code section")
        code, relocations = COMPARISON.object_function(path, symbol["symbol"], section[3])
        if len(code) == 15:
            kind = "init-only" if "probe_global_counter" in str(relocations) else "object-finalizer"
        else:
            kind = by_kind[len(code)]
        STATIC.decode(code, 0, kind)
        expected = {
            "object-init": [(4, "DIR32"), (9, "REL32"), (14, "DIR32"), (19, "REL32")],
            "init-only": [(4, "DIR32"), (9, "REL32")],
            "object-finalizer": [(4, "DIR32"), (9, "REL32")],
            "array-init": [(4, "DIR32"), (9, "DIR32"), (18, "DIR32"),
                           (23, "REL32"), (28, "DIR32"), (33, "REL32")],
            "array-finalizer": [(4, "DIR32"), (13, "DIR32"), (18, "REL32")],
        }[kind]
        if ([(item["offset"], item["type"]) for item in relocations] != expected
                or any(item["addend"] for item in relocations)):
            raise ValueError("compiler probe has different complete relocation fields")
        if kind in ("object-init", "array-init") and relocations[-1]["symbol"] != "_atexit":
            raise ValueError("compiler probe does not register the generated finalizer")
        observed[kind] += 1
    if observed != {"object-init": 2, "init-only": 1, "object-finalizer": 2,
                    "array-init": 1, "array-finalizer": 1}:
        raise ValueError("incomplete independent compiler static-lifetime fixture")


def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, default=ROOT / "build/probes/StaticLifetimeOrigins.obj")
    args = parser.parse_args()
    verify_generated_probe(args.probe)
    target = COMPARISON.verified_target()
    verify_registration_vendor(target)
    sections = SECTIONS.sections(target)
    pe = struct.unpack_from("<I", target, 0x3C)[0]
    count = struct.unpack_from("<H", target, pe + 6)[0]
    optional = struct.unpack_from("<H", target, pe + 20)[0]
    base = struct.unpack_from("<I", target, pe + 24 + 28)[0]
    virtual_sections = []
    for index in range(count):
        entry = struct.unpack_from("<8sIIIIIIHHI", target, pe + 24 + optional + index * 40)
        virtual_sections.append((base + entry[2], max(entry[1], entry[3]), entry[9]))
    def writable_global(address):
        if not any(start <= address < start + extent and flags & 0x80000000
                   and not flags & 0x20000000 for start, extent, flags in virtual_sections):
            raise ValueError("global object is outside writable mapped PE memory")
    def mapped(address, size, executable=None, writable=None):
        for base, extent, flags in sections:
            if base <= address and address + size <= base + extent:
                if (not flags & 0x40000000
                        or executable is not None and bool(flags & 0x20000000) != executable
                        or writable is not None and bool(flags & 0x80000000) != writable):
                    raise ValueError("static-lifetime field has incorrect PE section flags")
                return COMPARISON.pe_bytes_at(target, address, size)
        raise ValueError("static-lifetime field exceeds a mapped section")
    # The complete startup range is walked by the executable's own 106-byte runner.
    runner = mapped(0x64411D, 106, executable=True)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    instructions = list(decoder.disasm(runner, 0x64411D))
    if (sum(item.size for item in instructions) != len(runner)
            or instructions[-1].mnemonic != "ret"
            or runner[0x45:0x51] != b"\xbe\x00\xc0\x66\x00\x8b\xc6\xbf\x34\xc0\x66\x00"
            or not any(item.mnemonic == "call" and item.op_str == "eax" for item in instructions)):
        raise ValueError("target startup runner does not walk the recorded table")
    table = mapped(0x66C000, 0x38, executable=False, writable=True)
    pointers = struct.unpack_from("<14I", table)
    if pointers[0] or pointers[1] != 0x645238 or pointers[-1] or not all(pointers[2:13]):
        raise ValueError("startup table sentinels or security-init entry differ")
    startup = list(pointers[2:13])
    evidence = rows("compiler-static-evidence.csv")
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    entries = {int(address, 16) for address in functions}
    if len(evidence) != 21:
        raise ValueError("static-lifetime cohort is incomplete")
    for row in evidence:
        address, size, kind = int(row["address"], 16), int(row["size"]), row["template_kind"]
        code = mapped(address, size, executable=True)
        actual = STATIC.decode(code, address, kind)
        if (hashlib.sha256(code).hexdigest() != row["body_sha256"]
                or size != int(functions[row["address"]]["size"])
                or origins[row["address"]]["origin"] != "compiler"
                or origins[row["address"]]["disposition"] != "exclude"
                or origins[row["address"]]["evidence_id"] != row["evidence_id"]):
            raise ValueError("static wrapper body, extent or origin ledger differs")
        for key in ("object_address", "callee_address", "constructor_callback",
                    "destructor_callback", "count", "stride", "registered_callback",
                    "registration_target"):
            recorded = row[key]
            observed = actual.get(key)
            if (int(recorded, 16) if recorded else None) != observed:
                raise ValueError("static wrapper instruction field differs: " + key)
        writable_global(actual["object_address"])
        for key in ("callee_address", "constructor_callback", "destructor_callback", "registered_callback"):
            if key in actual and actual[key] not in entries:
                raise ValueError("static wrapper target is not a known function entry")
        if kind in ("object-init", "array-init") and actual["registration_target"] != 0x64168B:
            raise ValueError("static wrapper does not call the independently checked CRT registration")
        if kind == "array-init" and actual["callee_address"] != 0x641C78:
            raise ValueError("array initializer does not call the observed vector constructor helper")
        if kind == "array-finalizer" and actual["callee_address"] != 0x641D4A:
            raise ValueError("array finalizer does not call the observed vector destructor helper")
    finals = STATIC.check_links(evidence, startup)
    print(f"Static lifetime origin evidence OK: {len(evidence)} complete compiler wrappers, "
          f"{sum(int(row['size']) for row in evidence)} bytes, 11 startup entries, "
          f"{len(finals)} paired finalizers; no callee or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
