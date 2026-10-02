#!/usr/bin/env python3
"""Verify complete options, music-room, and progress decision bodies."""
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
    "0x00428F00": (951, 37, {0x00428FD3}, "OptionsScene::AdvanceAt00428F00"),
    "0x00426DD0": (916, 27, {0x00426F4E}, "MusicRoom::LoadCatalogAt00426DD0"),
    "0x00419E10": (671, 21, {0x00419E45, 0x0041A02C},
                   "GameProgress::CheckSelectionAt00419E10"),
    "0x00429F00": (563, 13, {0x00429F49},
                   "OptionsScene::ApplySelectionAt00429F00"),
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
    comparison = module("medium_game_target", "compare-coff-function.py")
    authored = module("medium_game_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = {row["address"]: row for row in rows("authored-origin-evidence.csv")}
    direct = rows("authored-origin-direct-switches.csv")
    if {key for key, row in evidence.items() if row["evidence_id"] == "R066"} != set(CASES):
        raise ValueError("medium game origin cohort differs")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    total_bytes = table_entries = 0
    for key, (size, branches, sites, role) in CASES.items():
        address = int(key, 16)
        record, function, origin = evidence[key], functions[key], origins[key]
        tables = [row for row in direct if row["address"] == key]
        if (int(record["size"]) != size or int(function["size"]) != size
                or record["inferred_role"] != role or function["proposed_name"] != role
                or origin["origin"] != "authored" or origin["disposition"] != "authored"
                or origin["evidence_id"] != "R066" or function["owner"] != "authored"
                or {int(row["jump_site"], 16) for row in tables} != sites
                or any(row["evidence_id"] != "R066" for row in tables)):
            raise ValueError("medium game origin witness or ledger differs")
        body = comparison.pe_bytes_at(target, address, size)
        counts = authored.verify_body(
            body, address, (),
            lambda pointer, extent: comparison.pe_bytes_at(target, pointer, extent), tables)
        if (hashlib.sha256(body).hexdigest() != record["body_sha256"]
                or counts != (1, branches)
                or counts != (int(record["return_count"]),
                              int(record["internal_branch_count"]))):
            raise ValueError("medium game complete body or CFG differs")
        instructions = list(decoder.disasm(body, address))
        call_targets = {item.operands[0].imm for item in instructions
                        if item.mnemonic == "call" and item.operands[0].type == X86_OP_IMM}
        if key == "0x00426DD0":
            strings = set()
            for item in instructions:
                if item.mnemonic == "push" and item.operands[0].type == X86_OP_IMM:
                    pointer = item.operands[0].imm
                    if 0x00650000 <= pointer < 0x00660000:
                        strings.add(comparison.pe_bytes_at(target, pointer, 14).split(b"\0")[0])
            if (b"musicroom.dat" not in strings or b"datab" not in strings
                    or 0x0041D800 not in call_targets
                    or origins["0x0041D800"]["origin"] != "authored"):
                raise ValueError("music-room catalog literal or archive call differs")
        if key == "0x00428F00" and (0x004079C0 not in call_targets
                                      or origins["0x004079C0"]["origin"] != "authored"):
            raise ValueError("options update lacks reviewed game sound call")
        if key == "0x00419E10" and 0x00416DC0 not in call_targets:
            raise ValueError("progress decision helper calls differ")
        total_bytes += size
        table_entries += sum(int(row["table_size"]) // 4 for row in tables)
    if total_bytes != 3101 or table_entries != 28:
        raise ValueError("medium game total extent or table coverage differs")
    print("Medium game origins OK: four complete authored bodies / 3,101 "
          "bytes, five guarded switches / 28 entries and music-room literal; "
          "no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
