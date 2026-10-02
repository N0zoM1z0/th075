#!/usr/bin/env python3
"""Verify two character action switch bodies and their vtable witnesses."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
CASES = {
    "0x005FAB10": (116, 0, "CharacterAuxObject::InitializeAt005FAB10"),
    "0x005FAE30": (31352, 630, "CharacterAuxObject::AdvanceActionAt005FAE30"),
    "0x005F3D60": (12400, 350, "MeilingFighter::DispatchSpecialStatesAt005F3D60"),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def vtables_written(body, address, decoder):
    return {item.operands[1].imm for item in decoder.disasm(body, address)
            if item.mnemonic == "mov" and len(item.operands) == 2
            and item.operands[0].type == X86_OP_MEM
            and item.operands[1].type == X86_OP_IMM
            and 0x00650000 <= item.operands[1].imm < 0x00660000}


def main():
    comparison = module("aux_target", "compare-coff-function.py")
    authored = module("aux_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    remaps = rows("authored-origin-switches.csv")
    directs = rows("authored-origin-direct-switches.csv")
    if ({key for key, row in evidence.items() if row["evidence_id"] == "R064"}
            != set(CASES)):
        raise ValueError("character auxiliary action cohort differs")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    bodies = {}
    for key, (size, branches, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R064" or function["owner"] != "authored"):
            raise ValueError("character auxiliary action ledger differs")
        body = comparison.pe_bytes_at(target, address, size)
        switches = [row for row in remaps if row["address"] == key]
        direct = [row for row in directs if row["address"] == key]
        expected = (0, 0)
        if key == "0x005FAE30":
            expected = (1, 0)
            sites = {0x005FAE66}
        elif key == "0x005F3D60":
            expected = (0, 1)
            sites = {0x005F3D83}
        else:
            sites = set()
        if (len(switches), len(direct)) != expected:
            raise ValueError("character auxiliary switch composition differs")
        if ({int(row["jump_site"], 16) for row in switches + direct} != sites
                or any(row["evidence_id"] != "R064" for row in switches + direct)):
            raise ValueError("character auxiliary switch site differs")
        counts = authored.verify_body(
            body, address, switches,
            lambda pointer, extent: comparison.pe_bytes_at(target, pointer, extent), direct)
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("character auxiliary complete body or CFG differs")
        bodies[key] = body
    if (vtables_written(bodies["0x005FAB10"], 0x005FAB10, decoder) != {0x0065A0E0}
            or struct.unpack_from("<I", comparison.pe_bytes_at(target, 0x0065A0E0, 8), 4)[0]
            != 0x005FAE30):
        raise ValueError("auxiliary constructor vtable does not bind its action method")
    fighter_key = "0x005E2090"
    fighter_record = evidence[fighter_key]
    fighter_body = comparison.pe_bytes_at(target, 0x005E2090, int(fighter_record["size"]))
    if (origins[fighter_key]["origin"] != "authored"
            or origins[fighter_key]["evidence_id"] != "R050"
            or hashlib.sha256(fighter_body).hexdigest() != fighter_record["body_sha256"]
            or authored.verify_body(fighter_body, 0x005E2090) != (
                int(fighter_record["return_count"]),
                int(fighter_record["internal_branch_count"]))
            or vtables_written(fighter_body, 0x005E2090, decoder) != {0x00659F50}
            or struct.unpack_from("<I", comparison.pe_bytes_at(target, 0x00659F50, 68), 64)[0]
            != 0x005F3D60):
        raise ValueError("Meiling constructor vtable slot 16 differs")
    print("Character auxiliary action origins OK: three complete authored bodies "
          "(43,868 bytes), two guarded switches and constructor-bound action slots; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
