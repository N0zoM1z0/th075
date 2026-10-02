#!/usr/bin/env python3
"""Verify complete runtime bodies and independently anchored callee bindings."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import sys
import struct
import tempfile

import capstone

ROOT = Path(__file__).resolve().parents[1]


def bind_calls(code, relocations, bindings, verified_symbols, address):
    """Link only zero-addend calls to full, separately verified vendor bodies."""
    if len(relocations) != len(bindings):
        raise ValueError("runtime relocation coverage mismatch")
    result = bytearray(code)
    offsets = set()
    for relocation, binding in zip(relocations, bindings):
        offset = int(relocation["offset"])
        destination = int(binding["target_address"], 16)
        if (offset in offsets or offset < 1 or offset + 4 > len(code)
                or relocation["type"] != "REL32"
                or relocation["addend"] != 0
                or relocation["local_symbol_offset"] is not None
                or code[offset - 1] != 0xE8
                or int(binding["offset"], 0) != offset
                or binding["type"] != "REL32"
                or binding["symbol"] != relocation["symbol"]):
            raise ValueError("unsupported or mismatched runtime call relocation")
        if verified_symbols.get(destination) != relocation["symbol"]:
            raise ValueError("runtime callee is not an independently verified vendor symbol")
        offsets.add(offset)
        struct.pack_into("<I", result, offset,
                         (destination - address - offset - 4) & 0xFFFFFFFF)
    return result


def archive_members(data: bytes):
    if data[:8] != b"!<arch>\n":
        raise ValueError("expected a COFF archive")
    offset = 8
    names = b""
    while offset < len(data):
        header = data[offset:offset + 60]
        if len(header) != 60 or header[58:] != b"`\n":
            raise ValueError("invalid archive member header")
        size = int(header[48:58])
        body = data[offset + 60:offset + 60 + size]
        if size < 0 or len(body) != size:
            raise ValueError("truncated archive member")
        raw_name = header[:16].rstrip()
        if raw_name == b"//":
            names = body
        elif raw_name not in (b"/", b"/SYM64/"):
            if raw_name.startswith(b"/") and raw_name[1:].isdigit():
                name_offset = int(raw_name[1:])
                if name_offset >= len(names):
                    raise ValueError("invalid archive long-name offset")
                name = names[name_offset:].split(b"\0", 1)[0].decode("ascii")
            else:
                name = raw_name.rstrip(b"/").decode("ascii")
            yield offset, name, body
        offset += 60 + size + size % 2


def main() -> int:
    spec = importlib.util.spec_from_file_location(
        "coff_compare", ROOT / "scripts/compare-coff-function.py"
    )
    comparison = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(comparison)
    target = comparison.verified_target()
    with (ROOT / "config/runtime-origin-evidence.csv").open() as stream:
        records = list(csv.DictReader(stream))
    if not records:
        raise ValueError("empty runtime-origin evidence")
    relocation_path = ROOT / "config/runtime-origin-relocations.csv"
    bindings = {}
    if relocation_path.exists():
        with relocation_path.open() as stream:
            for binding in csv.DictReader(stream):
                bindings.setdefault(binding["address"], []).append(binding)
    symbols = {int(record["address"], 16): record["coff_symbol"] for record in records}
    if len(symbols) != len(records) or set(bindings) - {record["address"] for record in records}:
        raise ValueError("duplicate runtime origins or orphan relocation bindings")
    archives = {}
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    directory = ROOT / ".analysis/runtime-origin-verification"
    directory.mkdir(parents=True, exist_ok=True)
    total_bytes = 0
    total_relocations = 0
    checked = []
    with tempfile.TemporaryDirectory(dir=directory) as temporary:
        object_path = Path(temporary) / "vendor.obj"
        for record in records:
            library = record["library"]
            if Path(library).name != library:
                raise ValueError("library must be an archive basename")
            path = ROOT / ".tools/msvc710/Vc7/lib" / library
            if library not in archives:
                data = path.read_bytes()
                archives[library] = (
                    hashlib.sha256(data).hexdigest(),
                    {offset: (name, body) for offset, name, body in archive_members(data)},
                )
            digest, members = archives[library]
            if digest != record["archive_sha256"]:
                raise ValueError("runtime archive identity mismatch: " + library)
            name, body = members[int(record["member_offset"])]
            if name != record["member"]:
                raise ValueError("runtime archive member identity mismatch")
            object_path.write_bytes(body)
            # Require the vendor function's own definition auxiliary record.
            # No caller-supplied size fallback or chosen section prefix is used.
            code, relocations = comparison.object_function(object_path, record["coff_symbol"])
            size = int(record["size"])
            address = int(record["address"], 16)
            if len(code) != size or len(relocations) != int(record["relocation_count"]):
                raise ValueError("vendor extent or relocation count mismatch")
            if hashlib.sha256(code).hexdigest() != record["body_sha256"]:
                raise ValueError("runtime body fingerprint mismatch")
            linked = bind_calls(code, relocations, bindings.get(record["address"], []),
                                symbols, address)
            if bytes(linked) != comparison.pe_bytes_at(target, address, size):
                raise ValueError("target runtime body mismatch: " + record["address"])
            checked.append((record, linked, relocations))
            total_bytes += size
            total_relocations += len(relocations)
        # Every prospective callee has now passed its complete byte comparison.
        # A binding cannot bootstrap an unverified callee from a guessed name.
        for record, linked, relocations in checked:
            address = int(record["address"], 16)
            size = int(record["size"])
            instructions = list(decoder.disasm(bytes(linked), address))
            starts = {instruction.address for instruction in instructions}
            if sum(instruction.size for instruction in instructions) != size:
                raise ValueError("incomplete runtime body decoding")
            if not any(instruction.group(capstone.CS_GRP_RET) for instruction in instructions):
                raise ValueError("runtime body has no return")
            call_fields = {address + int(relocation["offset"]) for relocation in relocations}
            used_fields = set()
            for instruction in instructions:
                if instruction.group(capstone.CS_GRP_JUMP) or instruction.group(capstone.CS_GRP_CALL):
                    if (len(instruction.operands) != 1
                            or instruction.operands[0].type != capstone.x86.X86_OP_IMM):
                        raise ValueError("unresolved runtime control flow: " + record["address"])
                    destination = instruction.operands[0].imm
                    field = instruction.address + instruction.imm_offset
                    if field in call_fields:
                        if (not instruction.group(capstone.CS_GRP_CALL)
                                or instruction.imm_size != 4 or destination not in symbols):
                            raise ValueError("runtime binding is not a verified direct call")
                        used_fields.add(field)
                    elif destination not in starts:
                        raise ValueError("unbound external runtime control flow")
            if used_fields != call_fields:
                raise ValueError("runtime relocation hides a non-call instruction field")
    print(f"Runtime origin evidence OK: {len(records)} complete vendor bodies, {total_bytes} bytes, {total_relocations} verified call bindings; no reconstruction exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
