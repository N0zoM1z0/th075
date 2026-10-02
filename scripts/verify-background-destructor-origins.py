#!/usr/bin/env python3
"""Cold-verify explicit empty VC7.1 background destructor bodies."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "??1BackgroundDerivedProbe@@UAE@XZ"
IMPLICIT_SYMBOL = "??1BackgroundImplicitProbe@@UAE@XZ"
FIELDS = ((12, "DIR32", "??_7BackgroundDerivedProbe@@6B@"),
          (20, "REL32", "??1BackgroundBaseProbe@@UAE@XZ"))
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
        raise ValueError("probe lacks one complete destructor definition")
    section_number = found[0]["section"]
    if not 1 <= section_number <= count:
        raise ValueError("probe destructor section is invalid")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (section_number - 1) * 40)
    peers = [row for row in symbols if row["section"] == section_number and row["type"] == 0x20]
    if (section[3] != 28 or section[7] != 2 or not section[9] & 0x20
            or not section[9] & 0x1000 or len(peers) != 1):
        raise ValueError("probe destructor is not a sole complete code COMDAT")
    source, relocations = comparison.object_function(path, SYMBOL, 28)
    observed = [(row["offset"], row["type"], row["symbol"], row["addend"])
                for row in relocations]
    expected = [(offset, kind, symbol, 0) for offset, kind, symbol in FIELDS]
    if observed != expected:
        raise ValueError("probe destructor relocation definitions differ")
    implicit = [row for row in symbols
                if row["symbol"] == IMPLICIT_SYMBOL and row["section"] > 0]
    if len(implicit) != 1 or implicit[0]["offset"] != 0 or implicit[0]["type"] != 0x20:
        raise ValueError("probe lacks one complete implicit destructor definition")
    implicit_section = implicit[0]["section"]
    if not 1 <= implicit_section <= count:
        raise ValueError("probe implicit destructor section is invalid")
    implicit_header = struct.unpack_from(
        "<8sIIIIIIHHI", data, 20 + (implicit_section - 1) * 40)
    implicit_peers = [row for row in symbols
                      if row["section"] == implicit_section and row["type"] == 0x20]
    if (implicit_header[3] != 19 or implicit_header[7] != 1
            or not implicit_header[9] & 0x20 or not implicit_header[9] & 0x1000
            or len(implicit_peers) != 1):
        raise ValueError("probe implicit destructor is not a distinct complete COMDAT")
    _, implicit_relocations = comparison.object_function(path, IMPLICIT_SYMBOL, 19)
    if [(row["offset"], row["type"], row["symbol"], row["addend"])
            for row in implicit_relocations] != [
                (11, "REL32", "??1BackgroundBaseProbe@@UAE@XZ", 0)]:
        raise ValueError("probe implicit destructor source shape differs")
    return source


def constructor_vtables(target, comparison, background):
    background.main()
    functions = {row["address"]: row for row in rows("functions.csv")}
    result = {}
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    for witness in rows("background-origin-evidence.csv"):
        if witness["kind"] != "asset-constructor":
            continue
        address = int(witness["address"], 16)
        body = comparison.pe_bytes_at(target, address, int(functions[witness["address"]]["size"]))
        values = [item.operands[1].imm for item in decoder.disasm(body, address)
                  if item.mnemonic == "mov" and len(item.operands) == 2
                  and item.operands[0].type == X86_OP_MEM
                  and item.operands[1].type == X86_OP_IMM
                  and 0x00650000 <= item.operands[1].imm < 0x00660000]
        if len(values) != 1 or values[0] in result:
            raise ValueError("background constructor lacks a unique derived vtable")
        result[values[0]] = witness["address"]
    if len(result) != 34:
        raise ValueError("background constructor vtable set is incomplete")
    return result


def main():
    comparison = module("background_destructor_target", "compare-coff-function.py")
    coff_data = module("background_destructor_coff", "coff_data.py")
    authored = module("background_destructor_authored", "verify-authored-origins.py")
    background = module("background_destructor_ctor", "verify-background-origins.py")
    target = comparison.verified_target()
    vtables = constructor_vtables(target, comparison, background)
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    authored_evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    evidence = rows("background-destructor-origin-evidence.csv")
    if len(evidence) != 34 or len({row["address"] for row in evidence}) != 34:
        raise ValueError("background destructor cohort is incomplete or duplicated")
    scratch = ROOT / "build/origin-background-destructor-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7BackgroundDestructor.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7BackgroundDestructor.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 background destructor probe failed to compile")
        source = source_definition(object_path, comparison, coff_data)
    source_hash = hashlib.sha256(source).hexdigest()
    mask = {index for offset, _, _ in FIELDS for index in range(offset, offset + 4)}
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    found_vtables = set()
    for row in evidence:
        key = row["address"]
        address = int(key, 16)
        function, origin, body_record = functions[key], origins[key], authored_evidence[key]
        if (row["evidence_id"] != "R057" or origin["evidence_id"] != "R057"
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or body_record["evidence_id"] != "R057" or int(function["size"]) != 28
                or function["proposed_name"] != body_record["inferred_role"]
                or row["source_sha256"] != source_hash):
            raise ValueError("background destructor witness/ledger differs")
        body = comparison.pe_bytes_at(target, address, 28)
        if (hashlib.sha256(body).hexdigest() != row["body_sha256"]
                or body_record["body_sha256"] != row["body_sha256"]
                or any(body[index] != source[index] for index in range(28) if index not in mask)
                or authored.verify_body(body, address) != (1, 0)):
            raise ValueError("background destructor whole body/CFG differs")
        instructions = list(decoder.disasm(body, address))
        if (len(instructions) < 8 or instructions[5].mnemonic != "mov"
                or instructions[5].imm_offset + instructions[5].address - address != 12
                or instructions[7].mnemonic != "call"
                or instructions[7].imm_offset + instructions[7].address - address != 20):
            raise ValueError("background destructor fields are not decoded vtable/call fields")
        vtable = struct.unpack_from("<I", body, 12)[0]
        callee = (address + 24 + struct.unpack_from("<i", body, 20)[0]) & 0xFFFFFFFF
        if (row["vtable_address"] != f"0x{vtable:08X}"
                or row["constructor_address"] != vtables.get(vtable)
                or row["base_destructor_address"] != f"0x{callee:08X}"
                or callee != 0x00449D40 or vtable in found_vtables):
            raise ValueError("background destructor vtable/base binding differs")
        found_vtables.add(vtable)
    if found_vtables != set(vtables):
        raise ValueError("background destructor cohort misses a constructor vtable")
    print("Background destructor origins OK: 34 explicit-source-shaped complete "
          "28-byte bodies, matched derived vtables and common base destructor; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
