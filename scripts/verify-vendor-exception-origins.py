#!/usr/bin/env python3
"""Cold-check standard exception methods with complete vtables and typed bases."""
from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]
PROFILE = ["/Od", "/Ob0", "/Gy", "/GR-", "/GX", "/Zi", "/GS", "/I", "src"]
ACCEPTED = {"constructor": "library", "destructor": "library", "copy_constructor": "compiler"}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def weak_aliases(data, comparison):
    """Read actual COFF fallback records, including undefined fallback declarations."""
    _, _, _, offset, count, _, _ = struct.unpack_from("<HHIIIHH", data)
    strings = data[offset + count * 18:]
    symbols, aliases = {}, []
    index = 0
    while index < count:
        raw, _, section, kind, storage, auxiliary = struct.unpack_from(
            "<8sIhHBB", data, offset + index * 18)
        if index + auxiliary >= count:
            raise ValueError("truncated exception COFF weak external")
        name = comparison.coff_name(raw, strings)
        symbols[index] = name
        if storage == 105:
            if section or kind != 0x20 or auxiliary != 1:
                raise ValueError("unsupported exception weak external record")
            fallback, policy = struct.unpack_from("<II", data, offset + (index + 1) * 18)
            aliases.append((name, fallback, policy))
        index += 1 + auxiliary
    return {name: {"symbol": symbols[fallback], "policy": policy}
            for name, fallback, policy in aliases}


def verify_graph(manifest):
    """Same-shaped game methods cannot replace the source-typed exception hierarchy."""
    if manifest["derived_class"] != "out_of_range":
        raise ValueError("exception type identity differs")
    bodies = manifest["bodies"]
    by_role = {row["role"]: row for row in bodies}
    tables = {row["role"]: row for row in manifest["vtables"]}
    if (len(by_role) != 10 or set(tables) != {"out_of_range", "logic_error"}
            or {row["role"]: row["origin"] for row in bodies if row["accepted"]} != ACCEPTED):
        raise ValueError("exception ownership graph set differs")
    expected_calls = {"constructor": "base_constructor", "copy_constructor": "base_copy_constructor",
                      "destructor": "base_destructor", "deleting_destructor": "destructor",
                      "base_deleting_destructor": "base_destructor", "what": "c_str"}
    for role, callee_role in expected_calls.items():
        calls = [call for call in by_role[role]["relocation_bindings"] if call["type"] == "REL32"]
        callee = by_role[callee_role]
        first = calls[0] if calls else {}
        if (first.get("symbol") != callee["coff_symbol"] or first.get("target_address") != callee["address"]
                or first.get("addend") != 0):
            raise ValueError("exception method lacks its exact source-typed base/callee")
    for role in ("constructor", "copy_constructor", "destructor"):
        fields = [call for call in by_role[role]["relocation_bindings"] if call["type"] == "DIR32"]
        if fields != [{"offset": 12 if role == "destructor" else 24, "type": "DIR32",
                       "symbol": tables["out_of_range"]["coff_symbol"], "addend": 0,
                       "target_address": tables["out_of_range"]["address"]}]:
            raise ValueError("exception method does not reference the complete exception vtable")
    for table_role, deleting_role in (("out_of_range", "deleting_destructor"),
                                      ("logic_error", "base_deleting_destructor")):
        slots = tables[table_role]["relocations"]
        deleting, what = by_role[deleting_role], by_role["what"]
        if (len(slots) != 2 or [slot["offset"] for slot in slots] != [0, 4]
                or slots[0]["target_address"] != deleting["address"]
                or slots[0]["resolved_symbol"] != deleting["coff_symbol"]
                or slots[1]["target_address"] != what["address"]
                or slots[1]["resolved_symbol"] != what["coff_symbol"]):
            raise ValueError("exception vtable lacks the complete deleting/what bodies")

    nodes = {row["role"]: row for row in manifest["data_nodes"]}
    if set(nodes) != {"throw_info", "catch_array", "catchable_type", "type_descriptor"}:
        raise ValueError("exception complete type-metadata graph differs")
    edges = (("throw_info", 4, by_role["destructor"]),
             ("throw_info", 12, nodes["catch_array"]),
             ("catch_array", 4, nodes["catchable_type"]),
             ("catchable_type", 4, nodes["type_descriptor"]),
             ("catchable_type", 24, by_role["copy_constructor"]))
    for role, offset, destination in edges:
        fields = [field for field in nodes[role]["relocation_bindings"] if field["offset"] == offset]
        if (len(fields) != 1 or fields[0]["type"] != "DIR32" or fields[0]["addend"]
                or fields[0]["symbol"] != destination["coff_symbol"]
                or fields[0]["target_address"] != destination["address"]):
            raise ValueError("exception type metadata lacks its exact method/type edges")
    if nodes["type_descriptor"]["type_name"] != ".?AVout_of_range@std@@":
        raise ValueError("exception type descriptor does not identify out_of_range")


def verify_table(row, object_data, comparison, reader, sections, target, aliases):
    symbols = reader.parse_symbols(object_data, comparison.coff_name)[1]
    definitions = [symbol for symbol in symbols
                   if symbol["symbol"] == row["coff_symbol"] and symbol["section"] > 0]
    if len(definitions) != 1 or definitions[0]["offset"]:
        raise ValueError("exception vtable lacks one complete source definition")
    number = definitions[0]["section"]
    head = struct.unpack_from("<8sIIIIIIHHI", object_data, 20 + (number - 1) * 40)
    peers = [symbol for symbol in symbols if symbol["section"] == number and symbol["storage"] == 2]
    if (head[3] != 8 or head[7] != 2 or not head[9] & 0x1000 or head[9] & 0xA0000020
            or not head[9] & 0x40000000 or len(peers) != 1
            or head[4] + 8 > len(object_data) or head[5] + 20 > len(object_data)):
        raise ValueError("exception vtable is not one full readonly eight-byte COMDAT")
    source = object_data[head[4]:head[4] + 8]
    address = int(row["address"], 16)
    actual = comparison.pe_bytes_at(target, address, 8)
    if (source != bytes(8) or hashlib.sha256(source).hexdigest() != row["source_sha256"]
            or hashlib.sha256(actual).hexdigest() != row["body_sha256"]
            or not any(base <= address and address + 8 <= base + size and flags & 0x40000000
                       and not flags & 0xA0000000 for base, size, flags in sections)):
        raise ValueError("exception vtable whole bytes or readonly target mapping differ")
    names = module("exception_symbol_names", "verify-sdk-jump-origins.py").raw_symbol_names(
        object_data, comparison)
    observed = []
    for index in range(2):
        offset, symbol_index, kind = struct.unpack_from("<IIH", object_data, head[5] + index * 10)
        if offset != index * 4 or kind != 6:
            raise ValueError("exception vtable pointer fields differ")
        symbol = names[symbol_index]
        alias = aliases.get(symbol)
        if alias and alias["policy"] != 2:
            raise ValueError("exception vtable weak fallback policy differs")
        observed.append({"offset": offset, "type": "DIR32", "symbol": symbol,
                         "resolved_symbol": alias["symbol"] if alias else symbol,
                         "target_address": f"0x{struct.unpack_from('<I', actual, offset)[0]:08X}"})
    if observed != row["relocations"]:
        raise ValueError("exception vtable typed pointer/fallback bindings differ")


def verify_data_node(row, object_data, comparison, reader, sections, target):
    """Link each complete compiler data COMDAT, retaining its emitted type name."""
    symbols = reader.parse_symbols(object_data, comparison.coff_name)[1]
    definitions = [symbol for symbol in symbols
                   if symbol["symbol"] == row["coff_symbol"] and symbol["section"] > 0]
    if len(definitions) != 1 or definitions[0]["offset"]:
        raise ValueError("exception metadata lacks one whole source definition")
    number = definitions[0]["section"]
    head = struct.unpack_from("<8sIIIIIIHHI", object_data, 20 + (number - 1) * 40)
    size, flags = head[3], head[9]
    expected_size = {"throw_info": 16, "catch_array": 16, "catchable_type": 28, "type_descriptor": 31}
    peers = [symbol for symbol in symbols if symbol["section"] == number and symbol["storage"] == 2]
    if (size != expected_size[row["role"]] or size != row["size"] or not flags & 0x1000
            or flags & 0x20000020 or not flags & 0x40000000 or len(peers) != 1
            or head[4] + size > len(object_data) or head[5] + head[7] * 10 > len(object_data)):
        raise ValueError("exception metadata is not its complete initialized data COMDAT")
    source = object_data[head[4]:head[4] + size]
    address = int(row["address"], 16)
    actual = comparison.pe_bytes_at(target, address, size)
    if (hashlib.sha256(source).hexdigest() != row["source_sha256"]
            or hashlib.sha256(actual).hexdigest() != row["body_sha256"]
            or not any(base <= address and address + size <= base + extent and pe_flags & 0x40000000
                       and not pe_flags & 0x20000000
                       and bool(pe_flags & 0x80000000) == bool(flags & 0x80000000)
                       for base, extent, pe_flags in sections)):
        raise ValueError("exception metadata full bytes or target data mapping differ")
    names = module("exception_data_names", "verify-sdk-jump-origins.py").raw_symbol_names(
        object_data, comparison)
    observed, occupied = [], set()
    linked = bytearray(source)
    for index in range(head[7]):
        offset, symbol_index, kind = struct.unpack_from("<IIH", object_data, head[5] + index * 10)
        if kind != 6 or offset + 4 > size or any(byte in occupied for byte in range(offset, offset + 4)):
            raise ValueError("exception metadata has unsupported/overlapping relocation fields")
        occupied.update(range(offset, offset + 4))
        addend = struct.unpack_from("<I", source, offset)[0]
        destination = struct.unpack_from("<I", actual, offset)[0]
        observed.append({"offset": offset, "type": "DIR32", "symbol": names[symbol_index],
                         "addend": addend, "target_address": f"0x{destination:08X}"})
        struct.pack_into("<I", linked, offset, destination)
    if observed != row["relocation_bindings"] or bytes(linked) != actual:
        raise ValueError("exception metadata whole linked bytes or typed fields differ")
    if row["role"] == "type_descriptor":
        if source[8:] != (row["type_name"] + "\0").encode("ascii") or actual[8:] != source[8:]:
            raise ValueError("exception emitted type name differs from the complete descriptor")


def main():
    vector = module("exception_rows", "verify-vendor-vector-operation-origins.py")
    comparison = module("exception_target", "compare-coff-function.py")
    record = module("exception_body", "verify-vendor-record-origins.py")
    sdk = module("exception_extent", "verify-sdk-origins.py")
    reader = module("exception_data", "coff_data.py")
    compiler = module("exception_sections", "verify-compiler-origins.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config/vendor-exception-groups.json").read_text())
    verify_graph(manifest)
    if (manifest["evidence_id"] != "R096" or manifest["profile"] != PROFILE
            or len(manifest["bodies"]) != 10 or sum(row["size"] for row in manifest["bodies"]) != 508):
        raise ValueError("exception manifest profile or full body set differs")
    for filename, digest in manifest["vendor_headers"].items():
        if hashlib.sha256((ROOT / ".tools/msvc710/Vc7/include" / filename).read_bytes()).hexdigest() != digest:
            raise ValueError("exception vendor header identity differs")
    result = subprocess.run([str(ROOT / "scripts/repo-python"),
                             str(ROOT / "scripts/verify-scalar-deleting-origins.py")],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError("exception deleting-destructor anchors failed cold replay")
    functions = {row["address"]: row for row in vector.rows("functions.csv")}
    origins = {row["address"]: row for row in vector.rows("function-origins.csv")}
    scratch = ROOT / "build/origin-exception-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary) / "VC7StandardExceptions.obj"
        result = subprocess.run([str(ROOT / "scripts/compile-probe.sh"),
                                 str(ROOT / "probes/VC7StandardExceptions.cpp"), str(path), *PROFILE],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 exception compilation failed: " + result.stderr[-1000:])
        object_data = path.read_bytes()
        for row in manifest["bodies"]:
            key, address, size = row["address"], int(row["address"], 16), row["size"]
            function, origin = functions[key], origins[key]
            if (int(function["size"]) != size or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != row["origin"] or origin["disposition"] != "exclude"
                    or function["owner"] != row["origin"] or function["status"] != "excluded"
                    or row["accepted"] and origin["evidence_id"] != "R096"
                    or any(address < int(other, 16) < address + size for other in functions)):
                raise ValueError("exception complete function extent or ownership differs")
            if sdk.complete_comdat_size(object_data, row["coff_symbol"], comparison.coff_name) != size:
                raise ValueError("exception source is not one complete function COMDAT")
            source, relocations = comparison.object_function(path, row["coff_symbol"], size)
            actual = comparison.pe_bytes_at(target, address, size)
            if (hashlib.sha256(source).hexdigest() != row["source_sha256"]
                    or hashlib.sha256(actual).hexdigest() != row["body_sha256"]):
                raise ValueError("exception complete source/target hash differs")
            indirect = record.compare_complete_body(
                source, relocations, actual, address, row["relocation_bindings"], comparison, sdk)
            if indirect != row["indirect_call_count"]:
                raise ValueError("exception complete control flow differs")
        aliases = weak_aliases(object_data, comparison)
        for table in manifest["vtables"]:
            verify_table(table, object_data, comparison, reader, compiler.sections(target), target, aliases)
        for node in manifest["data_nodes"]:
            verify_data_node(node, object_data, comparison, reader, compiler.sections(target), target)
    print("VC7 exception origins OK: 3 new bodies / 102 bytes (2 library, 1 compiler); "
          "10 complete bodies / 508 bytes, two full vtables, weak fallbacks and complete named throw metadata cold-replayed; "
          "no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, json.JSONDecodeError, struct.error) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
