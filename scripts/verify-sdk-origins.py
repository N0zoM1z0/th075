#!/usr/bin/env python3
"""Recheck whole D3DX COMDAT bodies; grant origin evidence only."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
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


def real_constant(data, name, coff_name):
    """Require the complete scalar constant definition from the same member."""
    digits = name.removeprefix("__real@")
    if not name.startswith("__real@") or len(digits) not in (8, 16):
        raise ValueError("unsupported vendor real constant")
    expected = int(digits, 16).to_bytes(len(digits) // 2, "little")
    machine, count, _, symbol_offset, symbol_count, optional, _ = struct.unpack_from(
        "<HHIIIHH", data)
    if machine != 0x14C or optional or not count:
        raise ValueError("invalid vendor constant object")
    strings = data[symbol_offset + symbol_count * 18:]
    matches = []
    index = 0
    while index < symbol_count:
        raw, value, section, typ, storage, aux = struct.unpack_from(
            "<8sIhHBB", data, symbol_offset + index * 18)
        if coff_name(raw, strings) == name and section > 0:
            matches.append((value, section, storage))
        index += 1 + aux
    if len(matches) != 1:
        raise ValueError("vendor real constant lacks one complete definition")
    value, section_number, storage = matches[0]
    if section_number > count:
        raise ValueError("invalid vendor constant section")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (section_number - 1) * 40)
    actual = data[section[4]:section[4] + section[3]]
    if (value or storage not in (2, 3) or section[3] != len(expected)
            or section[7] or not section[9] & 0x40 or not section[9] & 0x1000
            or section[9] & 0x20 or actual != expected):
        raise ValueError("vendor real constant definition differs from its scalar bits")
    return expected


def bind_sdk_function(code, relocations, bindings, symbols, address,
                      member, comparison, runtime, target, readonly_sections=None):
    readonly_sections = readonly_sections or {}
    if len(relocations) != len(bindings):
        raise ValueError("SDK relocation coverage mismatch")
    calls, call_bindings, data_fields = [], [], {}
    offsets = set()
    for relocation, binding in zip(relocations, bindings):
        offset = int(relocation["offset"])
        if (offset in offsets or offset < 0 or offset + 4 > len(code)
                or int(binding["offset"], 0) != offset
                or binding["type"] != relocation["type"]
                or binding["symbol"] != relocation["symbol"]):
            raise ValueError("SDK relocation metadata mismatch")
        offsets.add(offset)
        target_kind = binding.get("target_kind", "")
        if target_kind not in ("", "function"):
            raise ValueError("unsupported SDK relocation target kind")
        if relocation["type"] == "REL32":
            if (binding.get("literal_hex", "") or binding.get("data_section_id", "")
                    or target_kind):
                raise ValueError("SDK call cannot claim scalar literal evidence")
            calls.append(relocation)
            call_bindings.append(binding)
        elif (relocation["type"] == "DIR32"
              and relocation["local_symbol_offset"] is None):
            destination = int(binding["target_address"], 16)
            section_id = binding.get("data_section_id", "")
            if target_kind == "function":
                if (relocation["addend"] != 0 or section_id or binding.get("literal_hex", "")
                        or symbols.get(destination) != relocation["symbol"]):
                    raise ValueError("SDK function pointer lacks a verified complete callee")
            elif section_id:
                if binding.get("literal_hex", "") or relocation["symbol"].startswith("__real@"):
                    raise ValueError("SDK scalar and readonly section evidence cannot be mixed")
                section = readonly_sections[section_id]
                addend = relocation["addend"]
                source = section["symbols"].get(relocation["symbol"])
                if (source is None or addend < 0
                        or source + addend > section["base"] + section["size"]
                        or source + addend != destination):
                    raise ValueError("SDK data binding differs from the complete section definition")
                data_reader = module("sdk_data_binding", "coff_data.py")
                _, source_symbols = data_reader.parse_symbols(member, comparison.coff_name)
                if any(entry["symbol"] == relocation["symbol"] and entry["section"] > 0
                       for entry in source_symbols):
                    if hashlib.sha256(member).hexdigest() != section["member_sha256"]:
                        raise ValueError("SDK locally defined data requires the same source member")
            else:
                if relocation["addend"] != 0:
                    raise ValueError("SDK scalar constant cannot have a source addend")
                literal = real_constant(member, relocation["symbol"], comparison.coff_name)
                if bytes.fromhex(binding["literal_hex"]) != literal:
                    raise ValueError("SDK recorded scalar literal differs from vendor definition")
                if comparison.pe_bytes_at(target, destination, len(literal)) != literal:
                    raise ValueError("SDK target scalar literal differs from vendor definition")
            data_fields[address + offset] = destination
        else:
            raise ValueError("unsupported SDK relocation")
    linked = runtime.bind_calls(code, calls, call_bindings, symbols, address)
    for field, destination in data_fields.items():
        struct.pack_into("<I", linked, field - address, destination)
    return linked, data_fields


def verify_readonly_sections(comparison, runtime, target):
    path = ROOT / "config/sdk-origin-data.csv"
    if not path.exists():
        return {}
    data_reader = module("sdk_readonly_data", "coff_data.py")
    with path.open() as stream:
        records = list(csv.DictReader(stream))
    result, archives = {}, {}
    for record in records:
        identifier, library = record["id"], record["library"]
        if identifier in result or library not in {"d3dx8.lib", "d3dx8dt.lib"}:
            raise ValueError("invalid readonly SDK data identity")
        if library not in archives:
            data = (ROOT / ".tools/msvc710/Vc7/PlatformSDK/Lib" / library).read_bytes()
            archives[library] = (hashlib.sha256(data).hexdigest(),
                                {offset: (name, body) for offset, name, body
                                 in runtime.archive_members(data)})
        digest, members = archives[library]
        if digest != record["archive_sha256"]:
            raise ValueError("readonly SDK archive identity mismatch")
        name, body = members[int(record["member_offset"])]
        if name != record["member"]:
            raise ValueError("readonly SDK member identity mismatch")
        data, definitions = data_reader.readonly_section(
            body, int(record["section_number"]), comparison.coff_name)
        if (len(data) != int(record["size"])
                or hashlib.sha256(data).hexdigest() != record["section_sha256"]
                or definitions != json.loads(record["definitions"])):
            raise ValueError("readonly SDK complete section metadata mismatch")
        base = int(record["target_address"], 16)
        if comparison.pe_bytes_at(target, base, len(data)) != data:
            raise ValueError("readonly SDK complete target section mismatch")
        symbols = {entry["symbol"]: base + entry["offset"] for entry in definitions}
        if len(symbols) != len(definitions):
            raise ValueError("duplicate readonly SDK symbol definitions")
        result[identifier] = {"symbols": symbols, "base": base, "size": len(data),
                              "member_sha256": hashlib.sha256(body).hexdigest()}
    return result


def verify_control_flow(code, address, bound_calls=None, bound_constants=None):
    bound_calls = bound_calls or {}
    bound_constants = bound_constants or {}
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(bytes(code), address))
    starts = {instruction.address for instruction in instructions}
    if (sum(instruction.size for instruction in instructions) != len(code)
            or not instructions
            or not any(instruction.group(capstone.CS_GRP_RET) for instruction in instructions)):
        raise ValueError("incomplete vendor decoding or unresolved trailing body")
    final = instructions[-1]
    if (not final.group(capstone.CS_GRP_RET)
            and not (final.mnemonic == "jmp" and len(final.operands) == 1
                     and final.operands[0].type == capstone.x86.X86_OP_IMM
                     and final.operands[0].imm in starts)):
        raise ValueError("unresolved vendor trailing fallthrough or tail")
    indirect_calls = 0
    used_fields = set()
    used_constants = set()
    for instruction in instructions:
        for offset, size in [(instruction.disp_offset, instruction.disp_size),
                             (instruction.imm_offset, instruction.imm_size)]:
            field = instruction.address + offset
            if size == 4 and field in bound_constants:
                if struct.unpack_from("<I", code, field - address)[0] != bound_constants[field]:
                    raise ValueError("SDK constant binding differs from decoded field")
                used_constants.add(field)
        if instruction.group(capstone.CS_GRP_JUMP):
            if (len(instruction.operands) != 1
                    or instruction.operands[0].type != capstone.x86.X86_OP_IMM
                    or instruction.operands[0].imm not in starts):
                raise ValueError("external or unresolved vendor jump")
        elif instruction.group(capstone.CS_GRP_CALL):
            if len(instruction.operands) != 1:
                raise ValueError("unresolved vendor call")
            if instruction.operands[0].type == capstone.x86.X86_OP_IMM:
                field = instruction.address + instruction.imm_offset
                if field in bound_calls:
                    if (instruction.imm_size != 4
                            or instruction.operands[0].imm != bound_calls[field]):
                        raise ValueError("SDK call binding differs from decoded destination")
                    used_fields.add(field)
                elif instruction.operands[0].imm not in starts:
                    raise ValueError("unbound external vendor call")
            else:
                # These instructions are unmasked, byte-identical SDK dispatch.
                # Their callees receive no origin credit from this caller.
                indirect_calls += 1
    if used_fields != set(bound_calls):
        raise ValueError("SDK binding hides a non-call instruction field")
    if used_constants != set(bound_constants):
        raise ValueError("SDK constant binding hides an opcode or partial field")
    return indirect_calls


def main():
    comparison = module("sdk_coff", "compare-coff-function.py")
    runtime = module("sdk_archive", "verify-runtime-origins.py")
    target = comparison.verified_target()
    readonly_sections = verify_readonly_sections(comparison, runtime, target)
    with (ROOT / "config/sdk-origin-evidence.csv").open() as stream:
        records = list(csv.DictReader(stream))
    if not records or len({record["address"] for record in records}) != len(records):
        raise ValueError("empty or duplicated SDK origin evidence")
    bindings = {}
    relocation_path = ROOT / "config/sdk-origin-relocations.csv"
    if relocation_path.exists():
        with relocation_path.open() as stream:
            for binding in csv.DictReader(stream):
                bindings.setdefault(binding["address"], []).append(binding)
    symbols = {int(record["address"], 16): record["coff_symbol"] for record in records}
    if set(bindings) - {record["address"] for record in records}:
        raise ValueError("orphan SDK call bindings")
    archives = {}
    directory = ROOT / ".analysis/sdk-origin-verification"
    directory.mkdir(parents=True, exist_ok=True)
    total = indirect = total_relocations = total_constants = total_section_fields = total_function_fields = 0
    checked = []
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
            if len(relocations) != int(record["relocation_count"]):
                raise ValueError("SDK relocation count mismatch")
            if hashlib.sha256(code).hexdigest() != record["body_sha256"]:
                raise ValueError("SDK complete body fingerprint mismatch")
            address = int(record["address"], 16)
            linked, data_fields = bind_sdk_function(
                code, relocations, bindings.get(record["address"], []), symbols, address,
                body, comparison, runtime, target, readonly_sections)
            if bytes(linked) != comparison.pe_bytes_at(target, address, size):
                raise ValueError("SDK complete target bytes mismatch: " + record["address"])
            checked.append((record, linked, data_fields))
            total += size
            total_relocations += len(relocations) - len(data_fields)
            total_constants += len(data_fields)
            total_section_fields += sum(bool(binding.get("data_section_id"))
                                        for binding in bindings.get(record["address"], []))
            total_function_fields += sum(binding.get("target_kind", "") == "function"
                                         for binding in bindings.get(record["address"], []))
        # All callee records passed complete byte comparison before CFG checks.
        for record, linked, data_fields in checked:
            address = int(record["address"], 16)
            call_fields = {address + int(binding["offset"], 0):
                           int(binding["target_address"], 16)
                           for binding in bindings.get(record["address"], [])
                           if binding["type"] == "REL32"}
            calls = verify_control_flow(linked, address, call_fields, data_fields)
            if calls != int(record["indirect_call_count"]):
                raise ValueError("SDK dispatch count mismatch")
            indirect += calls
    if any(record["evidence_id"] == "R026" for record in records):
        witness = module("short_sdk_witness", "verify-sdk-short-origins.py")
        if witness.main() != 0:
            raise ValueError("short SDK typed caller evidence failed")
    print(f"SDK origin evidence OK: {len(records)} whole COMDAT bodies, {total} bytes, "
          f"{total_relocations} verified call bindings, {indirect} unchanged indirect calls; "
          f"{total_constants - total_section_fields - total_function_fields} scalar bindings, "
          f"{total_function_fields} function-pointer bindings, "
          f"{total_section_fields} readonly-section bindings ({len(readonly_sections)} whole sections); "
          "no reconstruction exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
