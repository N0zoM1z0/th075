#!/usr/bin/env python3
"""Verify complete game dispatchers, guarded tables, and loader strings."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
CASES = {
    "0x004183D0": (3765, 133, {0x00418460}, "BattleLoader::LoadStageAt004183D0"),
    "0x004176F0": (3232, 97, {0x00417983, 0x00417E5F},
                   "BattleLoader::LoadCharactersAt004176F0"),
    "0x004292E0": (2759, 6, {0x00429557}, "SceneRenderer::DrawAt004292E0"),
    "0x004431D0": (1982, 45, {0x0044385C}, "BattleState::ProcessAt004431D0"),
    "0x00445A00": (1958, 66, {0x00445AAA}, "BattleState::ApplySequenceAt00445A00"),
    "0x0045CE10": (1926, 52, {0x0045CED3}, "FighterState::ProcessActionAt0045CE10"),
    "0x00444850": (1877, 38, {0x00444E70}, "BattleState::ProcessAt00444850"),
    "0x0042E8F0": (1529, 53, {0x0042E9C2, 0x0042ED9E},
                   "SceneController::AdvanceAt0042E8F0"),
}
LOADER_STRINGS = {
    "0x004183D0": (0x00657A4C, b"LoadStage...\r\n\0"),
    "0x004176F0": (0x00657A30, b"LoadCharacter...\r\n\0"),
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("dispatch_target", "compare-coff-function.py")
    authored = module("dispatch_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    remaps = rows("authored-origin-switches.csv")
    directs = rows("authored-origin-direct-switches.csv")
    if {key for key, row in evidence.items() if row["evidence_id"] == "R065"} != set(CASES):
        raise ValueError("game dispatcher cohort differs")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    total_bytes = table_entries = 0
    for key, (size, branches, sites, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        switches = [row for row in remaps if row["address"] == key]
        direct = [row for row in directs if row["address"] == key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R065" or function["owner"] != "authored"
                or {int(row["jump_site"], 16) for row in switches + direct} != sites
                or any(row["evidence_id"] != "R065" for row in switches + direct)):
            raise ValueError("game dispatcher witness or ledger differs")
        body = comparison.pe_bytes_at(target, address, size)
        counts = authored.verify_body(
            body, address, switches,
            lambda pointer, extent: comparison.pe_bytes_at(target, pointer, extent), direct)
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("game dispatcher complete body or CFG differs")
        if key in LOADER_STRINGS:
            string_address, expected = LOADER_STRINGS[key]
            if comparison.pe_bytes_at(target, string_address, len(expected)) != expected:
                raise ValueError("game loader literal differs")
            instructions = list(decoder.disasm(body, address))
            if (not any(item.mnemonic == "push" and item.operands[0].type == X86_OP_IMM
                        and item.operands[0].imm == string_address for item in instructions)
                    or not any(item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM
                               and item.operands[0].imm == 0x0041CC50 for item in instructions)
                    or origins["0x0041CC50"]["origin"] != "authored"):
                raise ValueError("game loader lacks its reviewed diagnostic call")
        total_bytes += size
        table_entries += sum(int(row["table_size"]) // 4 for row in switches + direct)
    if total_bytes != 19028 or table_entries != 75:
        raise ValueError("game dispatcher total extent or table coverage differs")
    print("Game dispatcher origins OK: eight complete authored bodies / 19,028 "
          "bytes, ten guarded switches / 75 table entries, and both loader "
          "literals; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
