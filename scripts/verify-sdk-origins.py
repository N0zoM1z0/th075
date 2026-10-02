#!/usr/bin/env python3
"""Recheck whole D3DX COMDAT bodies; grant origin evidence only."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile

import capstone

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def complete_comdat_size(data, wanted, coff_name):
    """Derive the whole section extent without a target-supplied size fallback."""
    if len(data) < 20:
        raise ValueError("truncated vendor object")
    machine, count, _, symbol_offset, symbol_count, optional, _ = struct.unpack_from(
        "<HHIIIHH", data)
    if machine != 0x14C or optional or not count:
        raise ValueError("expected an i386 COFF object")
    strings_offset = symbol_offset + symbol_count * 18
    if strings_offset + 4 > len(data):
        raise ValueError("truncated vendor symbol table")
    strings_size = struct.unpack_from("<I", data, strings_offset)[0]
    if strings_size < 4 or strings_offset + strings_size > len(data):
        raise ValueError("truncated vendor string table")
    strings = data[strings_offset:strings_offset + strings_size]
    symbols = []
    index = 0
    while index < symbol_count:
        raw, value, section, typ, storage, aux = struct.unpack_from(
            "<8sIhHBB", data, symbol_offset + index * 18)
        if index + aux >= symbol_count:
            raise ValueError("truncated vendor auxiliary records")
        symbols.append((coff_name(raw, strings), value, section, typ, storage))
        index += 1 + aux
    matches = [symbol for symbol in symbols if symbol[0] == wanted and symbol[2] > 0]
    if len(matches) != 1:
        raise ValueError("expected one defined vendor function")
    symbol = matches[0]
    section_number = symbol[2]
    if section_number > count or 20 + section_number * 40 > len(data):
        raise ValueError("invalid vendor function section")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (section_number - 1) * 40)
    peers = [entry for entry in symbols if entry[2] == section_number and entry[3] == 0x20]
    if (symbol[1] != 0 or symbol[3] != 0x20 or symbol[4] not in (2, 3)
            or len(peers) != 1 or not section[9] & 0x20 or not section[9] & 0x1000
            or not section[3] or section[4] + section[3] > len(data)):
        raise ValueError("vendor extent is not one complete function COMDAT")
    return section[3]


def verify_control_flow(code, address):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(bytes(code), address))
    starts = {instruction.address for instruction in instructions}
    if (sum(instruction.size for instruction in instructions) != len(code)
            or not instructions or not instructions[-1].group(capstone.CS_GRP_RET)):
        raise ValueError("incomplete vendor decoding or unresolved trailing body")
    indirect_calls = 0
    for instruction in instructions:
        if instruction.group(capstone.CS_GRP_JUMP):
            if (len(instruction.operands) != 1
                    or instruction.operands[0].type != capstone.x86.X86_OP_IMM
                    or instruction.operands[0].imm not in starts):
                raise ValueError("external or unresolved vendor jump")
        elif instruction.group(capstone.CS_GRP_CALL):
            if len(instruction.operands) != 1:
                raise ValueError("unresolved vendor call")
            if instruction.operands[0].type == capstone.x86.X86_OP_IMM:
                if instruction.operands[0].imm not in starts:
                    raise ValueError("unbound external vendor call")
            else:
                # These instructions are unmasked, byte-identical SDK dispatch.
                # Their callees receive no origin credit from this caller.
                indirect_calls += 1
    return indirect_calls


def main():
    comparison = module("sdk_coff", "compare-coff-function.py")
    runtime = module("sdk_archive", "verify-runtime-origins.py")
    target = comparison.verified_target()
    with (ROOT / "config/sdk-origin-evidence.csv").open() as stream:
        records = list(csv.DictReader(stream))
    if not records or len({record["address"] for record in records}) != len(records):
        raise ValueError("empty or duplicated SDK origin evidence")
    archives = {}
    directory = ROOT / ".analysis/sdk-origin-verification"
    directory.mkdir(parents=True, exist_ok=True)
    total = indirect = 0
    with tempfile.TemporaryDirectory(dir=directory) as temporary:
        object_path = Path(temporary) / "vendor.obj"
        for record in records:
            library = record["library"]
            if library not in {"d3dx8.lib", "d3dx8dt.lib"}:
                raise ValueError("unsupported SDK archive")
            if library not in archives:
                data = (ROOT / ".tools/msvc710/Vc7/PlatformSDK/Lib" / library).read_bytes()
                archives[library] = (hashlib.sha256(data).hexdigest(),
                                    {offset: (name, body) for offset, name, body
                                     in runtime.archive_members(data)})
            digest, members = archives[library]
            if digest != record["archive_sha256"]:
                raise ValueError("SDK archive identity mismatch")
            name, body = members[int(record["member_offset"])]
            if name != record["member"]:
                raise ValueError("SDK member identity mismatch")
            size = complete_comdat_size(body, record["coff_symbol"], comparison.coff_name)
            if size != int(record["size"]) or record["extent_basis"] != "single-function-complete-code-section":
                raise ValueError("SDK complete section extent mismatch")
            object_path.write_bytes(body)
            code, relocations = comparison.object_function(object_path, record["coff_symbol"], size)
            if relocations or record["relocation_count"] != "0":
                raise ValueError("relocated SDK body requires separate binding evidence")
            if hashlib.sha256(code).hexdigest() != record["body_sha256"]:
                raise ValueError("SDK complete body fingerprint mismatch")
            address = int(record["address"], 16)
            if bytes(code) != comparison.pe_bytes_at(target, address, size):
                raise ValueError("SDK complete target bytes mismatch: " + record["address"])
            calls = verify_control_flow(code, address)
            if calls != int(record["indirect_call_count"]):
                raise ValueError("SDK dispatch count mismatch")
            total += size
            indirect += calls
    print(f"SDK origin evidence OK: {len(records)} whole COMDAT bodies, {total} bytes, "
          f"{indirect} unchanged indirect calls; no reconstruction exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
