#!/usr/bin/env python3
"""Verify complete relocation-free and segment-zero VC7 runtime leaves."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("runtime_leaf_target", "compare-coff-function.py")
    runtime = module("runtime_leaf_archive", "verify-runtime-origins.py")
    authored = module("runtime_leaf_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config/runtime-leaf-origin-evidence.json").read_text())
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    records = manifest["functions"]
    if (manifest["evidence_id"] != "R107" or len(records) != 4
            or len({row["address"] for row in records}) != 4
            or sum(row["size"] for row in records) != 199):
        raise ValueError("runtime leaf evidence set changed")
    archives = {}
    scratch = ROOT / "build/origin-runtime-leaf-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "runtime.obj"
        for record in records:
            library = record["library"]
            if Path(library).name != library:
                raise ValueError("runtime leaf library must be a basename")
            archive_path = ROOT / ".tools/msvc710/Vc7/lib" / library
            if library not in archives:
                data = archive_path.read_bytes()
                archives[library] = (
                    hashlib.sha256(data).hexdigest(),
                    {offset: (name, body) for offset, name, body in runtime.archive_members(data)},
                )
            digest, members = archives[library]
            if digest != record["archive_sha256"]:
                raise ValueError("runtime leaf archive identity changed")
            name, body = members[record["member_offset"]]
            if name != record["member"]:
                raise ValueError("runtime leaf archive member changed")
            object_path.write_bytes(body)
            code, relocations = comparison.object_function(object_path, record["coff_symbol"])
            simplified = [{key: relocation[key] for key in
                           ("offset", "type", "symbol", "addend", "local_symbol_offset")}
                          for relocation in relocations]
            address, size = int(record["address"], 16), record["size"]
            actual = comparison.pe_bytes_at(target, address, size)
            function, origin = functions[record["address"]], origins[record["address"]]
            if (len(code) != size or simplified != record["relocations"]
                    or hashlib.sha256(code).hexdigest() != record["body_sha256"]
                    or code != actual or int(function["size"]) != size
                    or int(function["span_end"], 16) != address + size - 1
                    or origin["origin"] != "library" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != "R107"
                    or function["owner"] != "library" or function["status"] != "excluded"):
                raise ValueError("runtime leaf body, extent or ownership changed: " + record["address"])
            authored.verify_body(actual, address)
            if simplified:
                expected = [{"offset": 40, "type": "DIR32", "symbol": "__except_list",
                             "addend": 0, "local_symbol_offset": None}]
                if (record["coff_symbol"] != "__setjmp3" or simplified != expected
                        or code[38:44] != bytes.fromhex("64a100000000")):
                    raise ValueError("runtime leaf segment-zero relocation changed")
    print("Runtime leaf origins OK: 4 complete pinned-VC7 bodies / 199 bytes; "
          "three relocation-free and one explicit FS:[0] __except_list field; no exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, UnicodeDecodeError, ValueError) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
