#!/usr/bin/env python3
"""Verify complete D3DX8 five-byte forwarding COMDATs and their typed targets."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def module(name: str, filename: str):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename: str):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def forward_destination(code: bytes, address: int):
    if len(code) != 5 or code[0] != 0xe9:
        raise ValueError("SDK forwarder is not one complete relative JMP")
    return (address + 5 + struct.unpack_from("<i", code, 1)[0]) & 0xffffffff


def typed_source_forward(source, relocations, callee_symbol):
    return (len(source) == 5 and bytes(source) == b"\xe9\0\0\0\0"
            and len(relocations) == 1 and relocations[0]["offset"] == 1
            and relocations[0]["type"] == "REL32"
            and relocations[0]["symbol"] == callee_symbol
            and relocations[0]["addend"] == 0)


def section(member: bytes, number: int):
    count = struct.unpack_from("<H", member, 2)[0]
    if not 1 <= number <= count:
        raise ValueError("invalid SDK COFF section number")
    head = struct.unpack_from("<8sIIIIIIHHI", member, 20 + (number - 1) * 40)
    if head[4] + head[3] > len(member) or head[5] + head[7] * 10 > len(member):
        raise ValueError("SDK COFF section or relocations are incomplete")
    return head


def raw_symbol_names(member: bytes, comparison):
    _, _, _, symbol_offset, count, _, _ = struct.unpack_from("<HHIIIHH", member)
    strings_offset = symbol_offset + count * 18
    strings_size = struct.unpack_from("<I", member, strings_offset)[0]
    if strings_size < 4 or strings_offset + strings_size > len(member):
        raise ValueError("SDK COFF string table is incomplete")
    strings = member[strings_offset:strings_offset + strings_size]
    names = {}
    index = 0
    while index < count:
        raw, _, _, _, _, aux = struct.unpack_from("<8sIhHBB", member,
                                                  symbol_offset + index * 18)
        names[index] = comparison.coff_name(raw, strings)
        index += 1 + aux
    return names


def vtable_section(member, group, comparison, data_reader, target, pe_sections):
    record = group.get("vtable")
    if record is None:
        if any(row["symbol"].startswith("??_7") for row in group["callee_relocations"]):
            raise ValueError("SDK callee vtable evidence is missing")
        return
    definitions = [row for row in data_reader.parse_symbols(member, comparison.coff_name)[1]
                   if row["symbol"] == record["symbol"] and row["section"] > 0]
    if len(definitions) != 1 or definitions[0]["offset"] != 0:
        raise ValueError("SDK vtable lacks one complete source definition")
    head = section(member, definitions[0]["section"])
    size, flags = head[3], head[9]
    if (size != record["size"] or size != 16 or head[7] != 4 or flags & 0x20
            or flags & 0x80000000 or not flags & 0x40000000):
        raise ValueError("SDK vtable is not a complete readonly COFF section")
    source = member[head[4]:head[4]+size]
    address = int(record["target_address"], 16)
    actual = comparison.pe_bytes_at(target, address, size)
    if (hashlib.sha256(source).hexdigest() != record["source_sha256"]
            or hashlib.sha256(actual).hexdigest() != record["body_sha256"]):
        raise ValueError("SDK vtable whole source or target hash differs")
    if not any(base <= address and address + size <= base + extent
               and flags & 0x40000000 and not flags & 0x80000000
               and not flags & 0x20000000 for base, extent, flags in pe_sections):
        raise ValueError("SDK target vtable is outside readonly nonexecutable data")
    names = raw_symbol_names(member, comparison)
    relocations = []
    for index in range(head[7]):
        offset, symbol_index, kind = struct.unpack_from("<IIH", member, head[5] + index * 10)
        if offset != index * 4 or kind != 6 or symbol_index not in names:
            raise ValueError("SDK vtable pointer relocation differs")
        destination = struct.unpack_from("<I", actual, offset)[0]
        if not any(base <= destination < base + extent and flags & 0x20000000
                   for base, extent, flags in pe_sections):
            raise ValueError("SDK vtable slot does not point into executable code")
        relocations.append({"offset": offset, "type": "DIR32",
                            "symbol": names[symbol_index],
                            "target_value": f"0x{destination:08X}"})
    if relocations != record["relocations"]:
        raise ValueError("SDK vtable whole pointer bindings differ")
    if not any(row["symbol"] == record["symbol"]
               and row["target_value"] == record["target_address"]
               for row in group["callee_relocations"]):
        raise ValueError("SDK callee does not actually reference its recorded vtable")


def source_aliases(member, group, path, comparison, sdk, data_reader):
    _, symbols = data_reader.parse_symbols(member, comparison.coff_name)
    result = []
    for symbol in symbols:
        if symbol["section"] <= 0 or symbol["type"] != 0x20 or symbol["offset"] != 0:
            continue
        if section(member, symbol["section"])[3] != 5:
            continue
        try:
            size = sdk.complete_comdat_size(member, symbol["symbol"], comparison.coff_name)
            source, relocations = comparison.object_function(path, symbol["symbol"], size)
        except ValueError:
            continue
        if size == 5 and typed_source_forward(source, relocations, group["callee_symbol"]):
            result.append(symbol["symbol"])
    if sorted(result) != group["source_symbols"]:
        raise ValueError("SDK five-byte source alias set differs")


def callee_body(member, group, path, comparison, sdk, cfg, target):
    symbol = group["callee_symbol"]
    size = sdk.complete_comdat_size(member, symbol, comparison.coff_name)
    if size != group["callee_size"]:
        raise ValueError("SDK forwarding destination lacks its full source extent")
    source, relocations = comparison.object_function(path, symbol, size)
    address = int(group["callee_address"], 16)
    actual = comparison.pe_bytes_at(target, address, size)
    if (hashlib.sha256(source).hexdigest() != group["callee_source_sha256"]
            or hashlib.sha256(actual).hexdigest() != group["callee_body_sha256"]):
        raise ValueError("SDK forwarding destination whole source or target hash differs")
    fields = {index for row in relocations
              for index in range(row["offset"], row["offset"] + 4)}
    if (any(source[index] != actual[index] for index in range(size) if index not in fields)
            or cfg.verify_body(actual, address)[0] != 1):
        raise ValueError("SDK forwarding destination body or decoded CFG differs")
    observed = []
    for row in relocations:
        offset = row["offset"]
        if not 0 <= offset <= size - 4:
            raise ValueError("SDK callee relocation exceeds its complete extent")
        if row["type"] == "REL32":
            value = address + offset + 4 + struct.unpack_from("<i", actual, offset)[0]
        elif row["type"] == "DIR32":
            value = struct.unpack_from("<I", actual, offset)[0]
        else:
            raise ValueError("unsupported SDK forwarding callee relocation")
        observed.append({"offset": offset, "type": row["type"], "symbol": row["symbol"],
                         "addend": row["addend"], "target_value": f"0x{value & 0xffffffff:08X}"})
    if observed != group["callee_relocations"]:
        raise ValueError("SDK forwarding destination relocation bindings differ")


def main():
    comparison = module("jump_coff", "compare-coff-function.py")
    runtime = module("jump_archive", "verify-runtime-origins.py")
    sdk = module("jump_sdk", "verify-sdk-origins.py")
    data_reader = module("jump_data", "coff_data.py")
    cfg = module("jump_cfg", "verify-authored-origins.py")
    compiler = module("jump_sections", "verify-compiler-origins.py")
    target = comparison.verified_target()
    with (ROOT / "config/sdk-jump-groups.json").open() as stream:
        manifest = json.load(stream)
    evidence = rows("sdk-jump-origin-evidence.csv")
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    verified_sdk = {row["address"]: row for row in rows("sdk-origin-evidence.csv")}
    groups = {group["id"]: group for group in manifest["groups"]}
    if (manifest["archive"] != "d3dx8.lib" or len(groups) != 5
            or len(evidence) != 39
            or len({row["address"] for row in evidence}) != len(evidence)):
        raise ValueError("SDK forwarding evidence cohort differs")
    archive = (ROOT / ".tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib").read_bytes()
    if hashlib.sha256(archive).hexdigest() != manifest["archive_sha256"]:
        raise ValueError("SDK forwarding archive identity differs")
    members = {offset: (name, body) for offset, name, body in runtime.archive_members(archive)}
    pe_sections = compiler.sections(target)
    scratch = ROOT / "build/origin-sdk-jump-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary) / "sdk.obj"
        for group_id, group in groups.items():
            name, member = members[int(group["member_offset"])]
            if name != group["member"]:
                raise ValueError("SDK forwarding source member differs")
            path.write_bytes(member)
            source_aliases(member, group, path, comparison, sdk, data_reader)
            callee_body(member, group, path, comparison, sdk, cfg, target)
            vtable_section(member, group, comparison, data_reader, target, pe_sections)
            callee_key = group["callee_address"]
            if int(functions[callee_key]["size"]) != group["callee_size"]:
                raise ValueError("SDK callee inventory boundary differs")
            if group_id.startswith("lock_") and (origins[callee_key]["origin"] != "library"
                    or verified_sdk[callee_key]["coff_symbol"] != group["callee_symbol"]):
                raise ValueError("SDK lock forwarding destination lost independent provenance")
            group_rows = [row for row in evidence if row["group_id"] == group_id]
            if len(group_rows) != len(group["source_symbols"]):
                raise ValueError("SDK forwarding target/source alias counts differ")
            destination = int(callee_key, 16)
            candidates = []
            for key, function in functions.items():
                if int(function["size"]) != 5:
                    continue
                address = int(key, 16)
                code = comparison.pe_bytes_at(target, address, 5)
                if code[0] == 0xe9 and forward_destination(code, address) == destination:
                    candidates.append(key)
            if sorted(candidates) != sorted(row["address"] for row in group_rows):
                raise ValueError("SDK forwarding group omits a complete candidate")
            for row in group_rows:
                key, address = row["address"], int(row["address"], 16)
                function, origin = functions[key], origins[key]
                if (row["evidence_id"] != "R039" or row["size"] != "5"
                        or row["destination"] != callee_key
                        or function["proposed_name"] != row["inferred_role"]
                        or function["owner"] != "library" or function["status"] != "excluded"
                        or origin["origin"] != "library" or origin["disposition"] != "exclude"
                        or origin["evidence_id"] != "R039"):
                    raise ValueError("SDK forwarding origin ledger differs")
                code = comparison.pe_bytes_at(target, address, 5)
                if (hashlib.sha256(code).hexdigest() != row["body_sha256"]
                        or forward_destination(code, address) != destination):
                    raise ValueError("SDK forwarding whole target hash differs")
    print(f"D3DX8 forwarding COMDATs OK: {len(evidence)} whole five-byte bodies, "
          f"{len(evidence)*5} bytes; repeated source aliases do not establish "
          "original class names or callee origin; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error,
            json.JSONDecodeError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
