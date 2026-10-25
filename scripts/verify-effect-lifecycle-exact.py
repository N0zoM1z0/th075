#!/usr/bin/env python3
"""Verify the complete source-owned effect lifecycle code and EH sections.

This supplements canonical function cold replay; compiler/library sections add
no authored-byte credit. Local cross-section destinations always follow the
actual COFF definitions, including the cleanup/handler and unwind/state roots.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
PLAN = ROOT / "config/effect-lifecycle-exact-sections.json"


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


def object_sections(data, name_decoder):
    """Read entire non-debug sections, retaining physical COFF symbol indices."""
    machine, count, _, symbol_at, symbol_count, optional, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional or not count or 20 + count * 40 > len(data):
        raise ValueError("invalid effect lifecycle COFF")
    strings_at = symbol_at + symbol_count * 18
    strings_size = struct.unpack_from("<I", data, strings_at)[0]
    if strings_size < 4 or strings_at + strings_size > len(data):
        raise ValueError("truncated effect lifecycle strings")
    strings = data[strings_at:strings_at + strings_size]
    symbols = {}
    index = 0
    while index < symbol_count:
        name, offset, section, typ, storage, aux = struct.unpack_from(
            "<8sIhHBB", data, symbol_at + index * 18)
        if index + aux >= symbol_count:
            raise ValueError("truncated effect lifecycle symbol AUX")
        symbols[index] = dict(symbol=name_decoder(name, strings), offset=offset,
                              section=section, type=typ, storage=storage)
        index += aux + 1
    sections = {}
    for number in range(1, count + 1):
        row = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (number - 1) * 40)
        name, size, raw_at, reloc_at, reloc_count, flags = (
            row[0].split(b"\0", 1)[0].decode("ascii"), row[3], row[4], row[5], row[7], row[9])
        if not size or name.startswith((".debug", ".drectve")):
            continue
        if not raw_at or raw_at + size > len(data) or reloc_at + reloc_count * 10 > len(data):
            raise ValueError("truncated effect lifecycle section")
        raw = data[raw_at:raw_at + size]
        fields = []
        for index in range(reloc_count):
            offset, target, kind = struct.unpack_from("<IIH", data, reloc_at + index * 10)
            if kind not in (6, 20) or not 0 <= offset <= size - 4 or target not in symbols:
                raise ValueError("invalid effect lifecycle relocation")
            fields.append(dict(offset=offset, type="DIR32" if kind == 6 else "REL32",
                               symbol=symbols[target]["symbol"],
                               addend=struct.unpack_from("<I", raw, offset)[0]))
        offsets = sorted(f["offset"] for f in fields)
        if any(right < left + 4 for left, right in zip(offsets, offsets[1:])):
            raise ValueError("overlapping effect lifecycle relocations")
        definitions = [{k: s[k] for k in ("symbol", "offset", "type", "storage")}
                       for s in symbols.values() if s["section"] == number
                       and s["storage"] in (2, 3) and not s["symbol"].startswith(".")]
        sections[number] = dict(name=name, flags=flags, raw=raw,
                                definitions=definitions, relocations=fields)
    return sections, symbols


def verify_sections(sections, symbols, plan, read_target):
    """Require all emitted code/data, exact fields, and source-local graph edges."""
    by_name = {}
    for number, section in sections.items():
        for definition in section["definitions"]:
            name = definition["symbol"]
            if name in by_name:
                raise ValueError("duplicate effect lifecycle definition")
            by_name[name] = (number, definition["offset"])
    bases = {}
    selected = []
    for part in plan["sections"]:
        number, offset = by_name[part["symbol"]]
        if number in bases or offset != part["symbol_offset"]:
            raise ValueError("effect lifecycle section root moved or reused")
        section = sections[number]
        if (len(section["raw"]) != part["size"] or section["name"] != part["name"]
                or section["flags"] != part["flags"]
                or section["definitions"] != part["definitions"]):
            raise ValueError("effect lifecycle complete section extent/definitions differ")
        bases[number] = part["address"]
        selected.append((part, section))
    safe = [s for n, s in sections.items() if n not in bases]
    if len(safe) != 1 or safe[0]["name"] != ".sxdata" or safe[0]["relocations"]:
        raise ValueError("unverified effect lifecycle source section")
    data = safe[0]["raw"]
    if len(data) != 4 * len(plan["safe_handlers"]):
        raise ValueError("effect lifecycle SafeSEH list extent differs")
    handlers = []
    for index in range(0, len(data), 4):
        symbol = symbols[struct.unpack_from("<I", data, index)[0]]
        if symbol["section"] not in bases or by_name[symbol["symbol"]] != (
                symbol["section"], symbol["offset"]):
            raise ValueError("effect lifecycle SafeSEH loses actual handler root")
        handlers.append(symbol["symbol"])
    if handlers != plan["safe_handlers"]:
        raise ValueError("effect lifecycle SafeSEH roots differ")
    results = []
    for part, section in selected:
        expected = [{k: f[k] for k in ("offset", "type", "symbol", "addend")}
                    for f in part["relocations"]]
        if section["relocations"] != expected:
            raise ValueError("effect lifecycle actual relocation fields differ")
        linked = bytearray(section["raw"])
        for field in part["relocations"]:
            name = field["symbol"]
            if name in by_name:
                number, offset = by_name[name]
                if field["target"] != bases[number] + offset:
                    raise ValueError("effect lifecycle local destination differs from actual COFF")
            value = field["target"] + field["addend"]
            if field["type"] == "REL32":
                value -= part["address"] + field["offset"] + 4
            struct.pack_into("<I", linked, field["offset"], value & 0xFFFFFFFF)
        target = read_target(part["address"], part["size"])
        if hashlib.sha256(target).hexdigest() != part["target_sha256"]:
            raise ValueError("effect lifecycle complete target section differs")
        if bytes(linked) != target:
            raise ValueError("effect lifecycle complete section byte mismatch")
        results.append(dict(symbol=part["symbol"], address=part["address"],
                            size=part["size"], fields=len(part["relocations"]),
                            kind=part["kind"], exact=True))
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--receipt", type=Path)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    plan = json.loads(PLAN.read_text())
    if plan["schema_version"] != 1:
        raise ValueError("effect lifecycle section schema differs")
    c = module("effect_exact_compare", "scripts/compare-coff-function.py")
    target = c.verified_target()
    if hashlib.sha256(target).hexdigest() != plan["target_sha256"]:
        raise ValueError("effect lifecycle target identity differs")
    for path, expected in {**plan["inputs"], **plan["origin_evidence"], **plan["vendor_headers"]}.items():
        if hashlib.sha256((ROOT / path).read_bytes()).hexdigest() != expected:
            raise ValueError("effect lifecycle guarded input differs: " + path)
    path = args.object or ROOT / plan["object"]
    data = path.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    sections, symbols = object_sections(data, c.coff_name)
    results = verify_sections(sections, symbols, plan,
                              lambda a, n: c.pe_bytes_at(target, a, n))
    if args.receipt:
        receipts = json.loads(args.receipt.read_text())
        if len(receipts) != len(plan["units"]) or {r["unit"] for r in receipts} != set(plan["units"]):
            raise ValueError("effect lifecycle cold receipt scope differs")
        for row in receipts:
            part = next(p for p in plan["sections"] if p["symbol"] == row["symbol"])
            if (row["result"] != "exact" or row["first_differences"]
                    or row["object_sha256"] != digest or row["object"] != plan["object"]
                    or row["source_sha256"] != plan["inputs"][plan["source"]]
                    or row["target_sha256"] != plan["target_sha256"]
                    or row["profile"] != plan["profile"] or part["kind"] != "authored"
                    or int(row["target_address"], 0) != part["address"]
                    or any(row[k] != part["size"] for k in (
                        "size", "matched_bytes", "compared_size", "matched_compared_bytes"))):
                raise ValueError("effect lifecycle fresh canonical receipt differs")
    report = dict(object=str(path), object_sha256=digest, sections=results,
                  safe_handlers=plan["safe_handlers"],
                  canonical_receipt_verified=bool(args.receipt),
                  authored_code_bytes=sum(r["size"] for r in results if r["kind"] == "authored"),
                  limits="Whole source code/data and every actual local definition/field; compiler/library/EH data add no credit. No complete original owner size/type claim.")
    if args.report:
        args.report.write_text(json.dumps(report, indent=2) + "\n")
    print(f"Effect lifecycle: {len(results)} whole sections exact; "
          f"{report['authored_code_bytes']} authored bytes; "
          f"{len(plan['safe_handlers'])} actual SafeSEH roots; "
          f"cold receipt verified={bool(args.receipt)}")


if __name__ == "__main__":
    main()
