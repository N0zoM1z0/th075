#!/usr/bin/env python3
"""Reproduce the complete Reimu dispatch map; grant no reconstruction credit."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
ADDRESS = 0x45DD70
SIZE = 60999


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return [row for row in csv.DictReader(stream)
                if int(row["address"], 0) == ADDRESS]


def audit():
    comparison = module("reimu_comparison", "compare-coff-function.py")
    origins = module("reimu_origins", "verify-authored-origins.py")
    target = comparison.verified_target()
    read = lambda address, size: comparison.pe_bytes_at(target, address, size)
    body = read(ADDRESS, SIZE)
    origin, = rows("authored-origin-evidence.csv")
    assert int(origin["size"]) == SIZE
    assert hashlib.sha256(body).hexdigest() == origin["body_sha256"]
    remapped = rows("authored-origin-switches.csv")
    direct = rows("authored-origin-direct-switches.csv")
    assert len(remapped) == 4 and len(direct) == 2
    counts = origins.verify_body(body, ADDRESS, switches=remapped,
                                direct_switches=direct, read=read)
    assert counts == (int(origin["return_count"]),
                      int(origin["internal_branch_count"])) == (1, 1690)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(body, ADDRESS))
    by_address = {item.address: item for item in instructions}
    # Native subtract instructions establish the lower case values. Guard and
    # table verification above independently covers the complete upper ranges.
    bases = {0x45DDCB: (0, None), 0x45DE05: (51, 0x45DDEB),
             0x45DE42: (143, 0x45DE25), 0x45DE78: (301, 0x45DE62),
             0x45DEB8: (391, 0x45DE98), 0x45DEE2: (604, 0x45DEC2)}
    groups = {}
    regions = []

    def add(case, destination):
        assert destination in by_address
        groups.setdefault(f"0x{destination:08X}", []).append(case)

    def checked_region(row, prefix):
        address = int(row[prefix + "_address"], 0)
        size = int(row[prefix + "_size"])
        raw = read(address, size)
        assert hashlib.sha256(raw).hexdigest() == row[prefix + "_sha256"]
        regions.append({"address": address, "size": size,
                        "sha256": hashlib.sha256(raw).hexdigest()})
        return raw

    for row in direct + remapped:
        base, subtract = bases[int(row["jump_site"], 0)]
        if subtract is not None:
            instruction = by_address[subtract]
            assert instruction.mnemonic == "sub"
            assert instruction.operands[1].type == X86_OP_IMM
            assert instruction.operands[1].imm == base
        table_raw = checked_region(row, "table")
        table = struct.unpack("<" + "I" * (len(table_raw) // 4), table_raw)
        if "remap_address" in row:
            indices = checked_region(row, "remap")
        else:
            indices = range(len(table))
        for index, entry in enumerate(indices):
            assert entry < len(table)
            add(base + index, table[entry])

    for case, compare, jump in [(50, 0x45DDB4, 0x45DDB8),
                                (140, 0x45DDDB, 0x45DDE2),
                                (300, 0x45DE15, 0x45DE1C),
                                (390, 0x45DE52, 0x45DE59),
                                (603, 0x45DE88, 0x45DE8F)]:
        condition, branch = by_address[compare], by_address[jump]
        assert condition.mnemonic == "cmp" and condition.operands[1].imm == case
        assert branch.mnemonic == "je" and branch.operands[0].type == X86_OP_IMM
        add(case, branch.operands[0].imm)

    cursor = ADDRESS + SIZE
    for region in sorted(regions, key=lambda item: item["address"]):
        assert region["address"] == cursor
        cursor += region["size"]
    assert cursor == 0x46CFF9 and read(cursor, 7) == b"\xcc" * 7
    assert len(groups) == 144 and "0x0046CB88" in groups
    direct_calls = {}
    indirect_calls = []
    for instruction in instructions:
        if not instruction.group(CS_GRP_CALL):
            continue
        if instruction.operands[0].type == X86_OP_IMM:
            key = f"0x{instruction.operands[0].imm:08X}"
            direct_calls.setdefault(key, []).append(f"0x{instruction.address:08X}")
        else:
            indirect_calls.append({"site": f"0x{instruction.address:08X}",
                                   "operand": instruction.op_str})
    return {"address": f"0x{ADDRESS:08X}", "code_size": SIZE,
            "body_sha256": origin["body_sha256"], "returns": counts[0],
            "internal_branches": counts[1], "table_bytes": cursor - ADDRESS - SIZE,
            "compare_size": cursor - ADDRESS, "alignment": 7,
            "default": "0x0046CB88", "groups": dict(sorted(groups.items())),
            "regions": regions, "direct_calls": direct_calls,
            "indirect_calls": indirect_calls, "exact_credit": False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    result = audit()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n")
    print(f"Reimu dispatch: {result['code_size']} code bytes, "
          f"{result['table_bytes']} table bytes, 143 non-default destinations; "
          "no exact credit")


if __name__ == "__main__":
    main()
