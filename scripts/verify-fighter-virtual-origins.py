#!/usr/bin/env python3
"""Cold-verify complete character fighter virtual override bodies and slots."""
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
SOURCE = {
    "forward-base": ("?Action@FighterDerivedProbe@@UAEXXZ", 19,
                     [(11, "REL32", "?Action@FighterBaseProbe@@UAEXXZ", 0)]),
    "no-op": ("?Idle@FighterDerivedProbe@@UAEXXZ", 11, []),
}
PROFILE = ("/Od", "/Ob0", "/Gy", "/GR-", "/GX-", "/Zi", "/GS", "/I", "src")


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(name):
    with (ROOT / "config" / name).open(newline="") as stream:
        return list(csv.DictReader(stream))


def source_definitions(path, comparison, coff_data):
    data = path.read_bytes()
    count, symbols = coff_data.parse_symbols(data, comparison.coff_name)
    result = {}
    for kind, (name, size, expected) in SOURCE.items():
        found = [row for row in symbols if row["symbol"] == name and row["section"] > 0]
        if len(found) != 1 or found[0]["offset"] != 0 or found[0]["type"] != 0x20:
            raise ValueError("fighter probe lacks a unique complete " + kind + " definition")
        section_number = found[0]["section"]
        if not 1 <= section_number <= count:
            raise ValueError("fighter probe source section is invalid")
        section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (section_number - 1) * 40)
        peers = [row for row in symbols if row["section"] == section_number and row["type"] == 0x20]
        if (section[3] != size or section[7] != len(expected)
                or not section[9] & 0x20 or not section[9] & 0x1000 or len(peers) != 1):
            raise ValueError("fighter probe source is not a sole complete code COMDAT")
        code, relocations = comparison.object_function(path, name, size)
        observed = [(row["offset"], row["type"], row["symbol"], row["addend"])
                    for row in relocations]
        if observed != expected:
            raise ValueError("fighter probe source relocation differs")
        result[kind] = code
    return result


def verified_fighter_slots(target, comparison, authored, functions, origins, evidence):
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    result = {}
    constructors = [row for row in evidence.values()
                    if row["inferred_role"].endswith("Fighter::Initialize")
                    and row["evidence_id"] in ("R046", "R050")]
    if len(constructors) != 11:
        raise ValueError("eleven verified character fighter constructors are required")
    for row in constructors:
        key = row["address"]
        function, origin = functions[key], origins[key]
        address = int(key, 16)
        body = comparison.pe_bytes_at(target, address, int(function["size"]))
        if (origin["origin"] != "authored" or origin["evidence_id"] != row["evidence_id"]
                or hashlib.sha256(body).hexdigest() != row["body_sha256"]):
            raise ValueError("fighter constructor lacks complete authored evidence")
        authored.verify_body(body, address)
        vtables = [item.operands[1].imm for item in decoder.disasm(body, address)
                   if item.mnemonic == "mov" and len(item.operands) == 2
                   and item.operands[0].type == X86_OP_MEM
                   and item.operands[1].type == X86_OP_IMM
                   and 0x00650000 <= item.operands[1].imm < 0x00660000]
        if len(vtables) != 1:
            raise ValueError("fighter constructor lacks one derived vtable")
        data = comparison.pe_bytes_at(target, vtables[0], 19 * 4)
        for slot in (8, 9, 18):
            target_address = struct.unpack_from("<I", data, slot * 4)[0]
            result.setdefault(target_address, []).append((key, vtables[0], slot))
    return result


def main():
    comparison = module("fighter_virtual_target", "compare-coff-function.py")
    coff_data = module("fighter_virtual_coff", "coff_data.py")
    authored = module("fighter_virtual_authored", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    authored_evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    slots = verified_fighter_slots(target, comparison, authored, functions, origins, authored_evidence)
    records = rows("fighter-virtual-origin-evidence.csv")
    if len(records) != 32 or len({row["address"] for row in records}) != 32:
        raise ValueError("fighter virtual origin cohort is incomplete or duplicated")
    if (slots.get(0x00497070) is None or len(slots[0x00497070]) != 1
            or slots[0x00497070][0][2] != 9
            or origins["0x00497070"]["origin"] != "authored"):
        raise ValueError("pre-reviewed Marisa slot 9 differs")
    scratch = ROOT / "build/origin-fighter-virtual-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7FighterVirtuals.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7FighterVirtuals.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 fighter virtual probe failed to compile")
        sources = source_definitions(object_path, comparison, coff_data)
    counts = {"forward-base": 0, "no-op": 0}
    for row in records:
        key, address, kind = row["address"], int(row["address"], 16), row["kind"]
        if kind not in sources:
            raise ValueError("unknown fighter virtual origin kind")
        function, origin, body_record = functions[key], origins[key], authored_evidence[key]
        found = slots.get(address, [])
        slot = 8 if kind == "forward-base" else int(row["slot_index"])
        if (row["evidence_id"] != "R060" or origin["evidence_id"] != "R060"
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or body_record["evidence_id"] != "R060"
                or function["proposed_name"] != body_record["inferred_role"]
                or row["source_sha256"] != hashlib.sha256(sources[kind]).hexdigest()
                or len(found) != 1 or row["constructor_address"] != found[0][0]
                or row["vtable_address"] != f"0x{found[0][1]:08X}"
                or slot != found[0][2] or int(row["slot_index"]) != slot
                or (kind == "no-op" and slot not in (9, 18))):
            raise ValueError("fighter virtual witness/ledger/vtable differs")
        source = sources[kind]
        body = comparison.pe_bytes_at(target, address, len(source))
        if (int(function["size"]) != len(source)
                or hashlib.sha256(body).hexdigest() != row["body_sha256"]
                or body_record["body_sha256"] != row["body_sha256"]
                or authored.verify_body(body, address) != (1, 0)):
            raise ValueError("fighter virtual complete target body/CFG differs")
        if kind == "no-op":
            if body != source or row["target_call"]:
                raise ValueError("fighter no-op source or call differs")
        else:
            if (body[:11] != source[:11] or body[15:] != source[15:]
                    or body[10] != 0xE8):
                raise ValueError("fighter base-forward body differs outside typed call")
            destination = (address + 15 + struct.unpack_from("<i", body, 11)[0]) & 0xFFFFFFFF
            if (destination != 0x00451EB0 or row["target_call"] != f"0x{destination:08X}"
                    or origins["0x00451EB0"]["origin"] != "authored"):
                raise ValueError("fighter forward call differs from reviewed game base action")
        counts[kind] += 1
    if counts != {"forward-base": 11, "no-op": 21}:
        raise ValueError("fighter virtual family counts differ")
    print("Fighter virtual origins OK: 11 complete base-action forwards and "
          "21 complete no-op methods in 11 verified character vtables; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
