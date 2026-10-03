#!/usr/bin/env python3
"""Verify whole CRT bodies with independently decoded imports and scalar data."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import struct
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_MEM


ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def check_import(symbol, destination, binding, imports):
    """The COFF spelling alone cannot establish which target IAT slot it uses."""
    match = re.fullmatch(r"__imp__([A-Za-z][A-Za-z0-9_]*)@([0-9]+)", symbol)
    if (match is None or binding.get("import_name") != match[1]
            or binding.get("import_dll") != "KERNEL32.dll"
            or imports.get(destination) != (binding["import_dll"], match[1])):
        raise ValueError("CRT import binding differs from the raw PE import directory")


def check_scalar(source, actual, recorded_size, sections, address):
    if (len(source) != recorded_size or actual != source
            or not any(base <= address and address + len(source) <= base + size
                       and flags & 0x40000000 and not flags & 0xA0000000
                       for base, size, flags in sections)):
        raise ValueError("CRT scalar requires its complete readonly target definition")


def readonly_member_data(member, symbol, binding, coff_name):
    """Require the entire defining section and its symbol topology, never a prefix."""
    reader = module("crt_external_readonly", "coff_data.py")
    _, symbols = reader.parse_symbols(member, coff_name)
    definitions = [entry for entry in symbols
                   if entry["symbol"] == symbol and entry["section"] > 0]
    if len(definitions) != 1 or definitions[0]["offset"] != 0:
        raise ValueError("CRT readonly binding lacks one definition at section start")
    source, names = reader.readonly_section(member, definitions[0]["section"], coff_name)
    if (len(source) != binding["data_size"] or names != binding["data_definitions"]
            or hashlib.sha256(source).hexdigest() != binding["source_data_sha256"]):
        raise ValueError("CRT readonly whole section or symbol definitions differ")
    return source


def bind_body(code, relocations, bindings, symbols, address, member,
              comparison, runtime, sdk, target, imports, sections):
    if len(relocations) != len(bindings):
        raise ValueError("CRT external relocation coverage differs")
    calls, call_bindings, data_fields, import_fields = [], [], {}, {}
    offsets = set()
    for relocation, binding in zip(relocations, bindings):
        offset = relocation["offset"]
        if (offset in offsets or offset < 0 or offset + 4 > len(code)
                or binding["offset"] != offset or binding["type"] != relocation["type"]
                or binding["symbol"] != relocation["symbol"]
                or binding["addend"] != relocation["addend"] or relocation["addend"] != 0
                or relocation["local_symbol_offset"] is not None):
            raise ValueError("CRT external relocation metadata differs")
        offsets.add(offset)
        destination = int(binding["target_address"], 16)
        kind = binding["target_kind"]
        if kind == "callee" and relocation["type"] == "REL32":
            calls.append(relocation)
            call_bindings.append({**binding, "offset": hex(offset)})
        elif kind == "import" and relocation["type"] == "DIR32":
            check_import(relocation["symbol"], destination, binding, imports)
            import_fields[address + offset] = destination
            data_fields[address + offset] = destination
        elif kind == "scalar" and relocation["type"] == "DIR32":
            scalar = sdk.real_constant(member, relocation["symbol"], comparison.coff_name)
            check_scalar(scalar, comparison.pe_bytes_at(target, destination, len(scalar)),
                         binding["data_size"], sections, destination)
            data_fields[address + offset] = destination
        elif kind == "readonly-section" and relocation["type"] == "DIR32":
            source = readonly_member_data(member, relocation["symbol"], binding,
                                          comparison.coff_name)
            check_scalar(source, comparison.pe_bytes_at(target, destination, len(source)),
                         binding["data_size"], sections, destination)
            data_fields[address + offset] = destination
        else:
            raise ValueError("unsupported CRT external binding kind")
    linked = runtime.bind_calls(code, calls, call_bindings, symbols, address)
    for field, destination in data_fields.items():
        struct.pack_into("<I", linked, field - address, destination)
    call_fields = {address + row["offset"]: int(row["target_address"], 16)
                   for row in bindings if row["target_kind"] == "callee"}
    indirect = sdk.verify_control_flow(linked, address, call_fields, data_fields)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    used_imports = set()
    for instruction in decoder.disasm(linked, address):
        field = instruction.address + instruction.disp_offset
        if field in import_fields:
            if (instruction.mnemonic != "call" or len(instruction.operands) != 1
                    or instruction.disp_size != 4 or instruction.operands[0].type != X86_OP_MEM
                    or instruction.operands[0].size != 4
                    or instruction.operands[0].mem.base or instruction.operands[0].mem.index
                    or instruction.operands[0].mem.disp != import_fields[field]):
                raise ValueError("CRT import relocation is not a complete absolute IAT call")
            used_imports.add(field)
    if used_imports != set(import_fields) or indirect != len(import_fields):
        raise ValueError("CRT has an unresolved indirect call or unused IAT binding")
    return linked


def rows(filename):
    with (ROOT / "config" / filename).open() as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("crt_external_compare", "compare-coff-function.py")
    runtime = module("crt_external_runtime", "verify-runtime-origins.py")
    sdk = module("crt_external_cfg", "verify-sdk-origins.py")
    imports_module = module("crt_external_imports", "verify-import-origins.py")
    compiler = module("crt_external_sections", "verify-compiler-origins.py")
    target = comparison.verified_target()
    records = json.loads((ROOT / "config/runtime-external-origin-evidence.json").read_text())
    if not records or len({row["address"] for row in records}) != len(records):
        raise ValueError("CRT external evidence is empty or duplicated")
    # Every call anchor is checked from the pinned vendor archive, not a mapped name.
    if runtime.main() != 0:
        raise ValueError("CRT complete call anchors failed replay")
    symbols = {int(row["address"], 16): row["coff_symbol"]
               for filename in ("runtime-origin-evidence.csv", "runtime-local-evidence.csv")
               for row in rows(filename)}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    functions = {row["address"]: row for row in rows("functions.csv")}
    imports = imports_module.pe_imports(target, comparison)
    sections = compiler.sections(target)
    archives = {}
    scratch = ROOT / ".analysis/runtime-external-origin-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary) / "vendor.obj"
        for record in records:
            address = int(record["address"], 16)
            size = record["size"]
            origin, function = origins[record["address"]], functions[record["address"]]
            if (record["evidence_id"] != origin["evidence_id"]
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or function["owner"] != "library" or function["status"] != "excluded"
                    or function["proposed_name"] != record["coff_symbol"]
                    or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or any(address < int(other["address"], 16) < address + size
                           for other in functions.values())):
                raise ValueError("CRT external origin or complete extent differs from the ledger")
            library = record["library"]
            if Path(library).name != library:
                raise ValueError("CRT archive must be a basename")
            if library not in archives:
                raw = (ROOT / ".tools/msvc710/Vc7/lib" / library).read_bytes()
                archives[library] = (hashlib.sha256(raw).hexdigest(),
                                     {offset: (name, data) for offset, name, data
                                      in runtime.archive_members(raw)})
            digest, members = archives[library]
            name, member = members[record["member_offset"]]
            if (digest != record["archive_sha256"] or name != record["member"]
                    or hashlib.sha256(member).hexdigest() != record["member_sha256"]):
                raise ValueError("CRT external archive/member identity differs")
            path.write_bytes(member)
            # Require the function's own definition auxiliary record; no size fallback.
            source, relocations = comparison.object_function(path, record["coff_symbol"])
            actual = comparison.pe_bytes_at(target, address, size)
            if (record["extent_basis"] != "function-auxiliary-record" or len(source) != size
                    or hashlib.sha256(source).hexdigest() != record["source_body_sha256"]
                    or hashlib.sha256(actual).hexdigest() != record["target_body_sha256"]):
                raise ValueError("CRT external full source/target body differs")
            linked = bind_body(source, relocations, record["relocations"], symbols,
                               address, member, comparison, runtime, sdk, target, imports, sections)
            if linked != actual:
                raise ValueError("CRT external complete comparison differs")
    print(f"CRT external origins OK: {len(records)} complete vendor bodies / "
          f"{sum(row['size'] for row in records)} bytes; full readonly definitions, raw PE imports "
          "and independently replayed callees; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
