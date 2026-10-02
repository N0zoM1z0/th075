#!/usr/bin/env python3
"""Cold-verify complete compiler-generated character destructor origins."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "??1BackgroundImplicitProbe@@UAE@XZ"
BASE_SYMBOL = "??1BackgroundBaseProbe@@UAE@XZ"
BASE_ADDRESS = 0x00456910
PROFILE = ("/Od", "/Ob0", "/Gy", "/GR-", "/GX-", "/Zi", "/GS", "/I", "src")


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def source_definition(path, comparison, coff_data):
    data = path.read_bytes()
    count, symbols = coff_data.parse_symbols(data, comparison.coff_name)
    found = [row for row in symbols if row["symbol"] == SYMBOL and row["section"] > 0]
    if len(found) != 1 or found[0]["offset"] != 0 or found[0]["type"] != 0x20:
        raise ValueError("implicit destructor probe lacks one full function definition")
    section_number = found[0]["section"]
    if not 1 <= section_number <= count:
        raise ValueError("implicit destructor section is invalid")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (section_number - 1) * 40)
    peers = [row for row in symbols if row["section"] == section_number and row["type"] == 0x20]
    if (section[3] != 19 or section[7] != 1 or not section[9] & 0x20
            or not section[9] & 0x1000 or len(peers) != 1):
        raise ValueError("implicit destructor source is not a sole complete code COMDAT")
    code, relocations = comparison.object_function(path, SYMBOL, 19)
    if [(row["offset"], row["type"], row["symbol"], row["addend"])
            for row in relocations] != [(11, "REL32", BASE_SYMBOL, 0)]:
        raise ValueError("implicit destructor source relocation differs")
    return bytes(code)


def main():
    comparison = module("implicit_target", "compare-coff-function.py")
    coff_data = module("implicit_coff", "coff_data.py")
    authored = module("implicit_cfg", "verify-authored-origins.py")
    scalar = module("implicit_scalar", "verify-scalar-deleting-origins.py")
    target = comparison.verified_target()
    scalar.main()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    wrappers = {row["destructor_address"]: row
                for row in rows("scalar-deleting-origin-evidence.csv")}
    records = rows("character-implicit-destructor-origins.csv")
    if len(records) != 10 or len({row["address"] for row in records}) != 10:
        raise ValueError("character implicit destructor cohort is incomplete or duplicated")
    if (origins[f"0x{BASE_ADDRESS:08X}"]["origin"] != "authored"
            or origins[f"0x{BASE_ADDRESS:08X}"]["evidence_id"] != "R045"):
        raise ValueError("shared base cleanup lacks independently reviewed game origin")
    scratch = ROOT / "build/origin-character-implicit-destructor-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7BackgroundDestructor.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7BackgroundDestructor.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 implicit destructor probe failed to compile")
        source = source_definition(object_path, comparison, coff_data)
    source_hash = hashlib.sha256(source).hexdigest()
    mask = set(range(11, 15))
    for row in records:
        key, address = row["address"], int(row["address"], 16)
        function, origin = functions[key], origins[key]
        wrapper = wrappers.get(key)
        if (row["evidence_id"] != "R061" or origin["evidence_id"] != "R061"
                or origin["origin"] != "compiler" or origin["disposition"] != "exclude"
                or function["status"] != "excluded" or function["owner"] != "compiler"
                or function["proposed_name"] != f"VC7::ImplicitDerivedDestructor_{address:08X}"
                or int(function["size"]) != 19 or int(row["size"]) != 19
                or row["source_sha256"] != source_hash or wrapper is None
                or row["scalar_wrapper_address"] != wrapper["address"]
                or row["base_destructor_address"] != f"0x{BASE_ADDRESS:08X}"):
            raise ValueError("implicit destructor witness or ledger differs")
        wrapper_address = int(wrapper["address"], 16)
        wrapper_body = comparison.pe_bytes_at(target, wrapper_address, 44)
        if (wrapper["evidence_id"] != "R037"
                or origins[wrapper["address"]]["origin"] != "compiler"
                or hashlib.sha256(wrapper_body).hexdigest() != wrapper["body_sha256"]):
            raise ValueError("independent scalar deleting wrapper differs")
        if (wrapper_body[10] != 0xE8
                or wrapper_address + 15 + struct.unpack_from("<i", wrapper_body, 11)[0] != address):
            raise ValueError("scalar deleting wrapper does not call this destructor")
        body = comparison.pe_bytes_at(target, address, 19)
        if (hashlib.sha256(body).hexdigest() != row["body_sha256"]
                or any(body[index] != source[index] for index in range(19) if index not in mask)
                or body[10] != 0xE8 or authored.verify_body(body, address) != (1, 0)):
            raise ValueError("implicit destructor complete target body or CFG differs")
        destination = address + 15 + struct.unpack_from("<i", body, 11)[0]
        if destination != BASE_ADDRESS:
            raise ValueError("implicit destructor does not call the reviewed base cleanup")
    print("Character implicit destructor origins OK: 10 complete generated "
          "19-byte bodies, ten verified scalar deleting callers and the reviewed "
          "shared base cleanup; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
