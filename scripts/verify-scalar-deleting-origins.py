#!/usr/bin/env python3
"""Cold-verify complete VC7.1 scalar deleting destructor origin records."""
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
SYMBOL = "??_GProbeDeletingDestructor@@UAEPAXI@Z"
DESTRUCTOR_SYMBOL = "??1ProbeDeletingDestructor@@UAE@XZ"
DELETE_SYMBOL = "??3@YAXPAX@Z"
DELETE_ADDRESS = 0x00640F15
SIZE = 44
FIELDS = ((11, DESTRUCTOR_SYMBOL), (28, DELETE_SYMBOL))
PROFILE = ("/Od", "/Ob0", "/Gy", "/GR-", "/GX-", "/Zi", "/GS", "/I", "src")


def module(name: str, filename: str):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename: str):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def source_definition(path: Path, comparison, coff_data, size=SIZE, fields=FIELDS):
    """Require the generated symbol to occupy its entire executable COMDAT."""
    data = path.read_bytes()
    count, symbols = coff_data.parse_symbols(data, comparison.coff_name)
    definitions = [row for row in symbols if row["symbol"] == SYMBOL and row["section"] > 0]
    if len(definitions) != 1 or definitions[0]["offset"] != 0 or definitions[0]["type"] != 0x20:
        raise ValueError("probe lacks one full generated deleting-destructor definition")
    section_number = definitions[0]["section"]
    if not 1 <= section_number <= count:
        raise ValueError("probe deleting-destructor section is invalid")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (section_number - 1) * 40)
    if (section[3] != size or section[7] != len(fields) or not section[9] & 0x20
            or not section[9] & 0x20000000 or section[4] + size > len(data)):
        raise ValueError("probe generated function does not own one complete code section")
    peers = [row for row in symbols if row["section"] == section_number and row["type"] == 0x20]
    if len(peers) != 1:
        raise ValueError("probe generated section has another function definition")
    code, relocations = comparison.object_function(path, SYMBOL, size)
    if (len(code) != size or [(row["offset"], row["type"], row["symbol"], row["addend"])
            for row in relocations] != [(field, "REL32", symbol, 0) for field, symbol in fields]):
        raise ValueError("probe generated relocations differ from the VC7 pattern")
    return bytes(code)


def verify_target_body(code: bytes, address: int, source: bytes, starts: set[int], cfg,
                       size=SIZE, fields=FIELDS):
    """Check every nonrelocated byte, both calls, and the complete local CFG."""
    mask = {byte for field, _ in fields for byte in range(field, field + 4)}
    if len(code) != size or len(source) != size or any(
            code[index] != source[index] for index in range(size) if index not in mask):
        raise ValueError("whole deleting-destructor body differs from source emission")
    if cfg.verify_body(code, address) != (1, 1):
        raise ValueError("deleting-destructor return or local branch differs")
    destinations = []
    for field, _ in fields:
        if code[field - 1] != 0xE8:
            raise ValueError("relocation field is not a direct CALL")
        destinations.append(address + field + 4 + struct.unpack_from("<i", code, field)[0])
    if destinations[0] not in starts:
        raise ValueError("deleting destructor does not call a recorded function entry")
    if destinations[1] != DELETE_ADDRESS:
        raise ValueError("deleting destructor does not call the known operator delete")
    return destinations[0]


def main():
    comparison = module("scalar_target", "compare-coff-function.py")
    coff_data = module("scalar_coff", "coff_data.py")
    cfg = module("scalar_cfg", "verify-authored-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = rows("scalar-deleting-origin-evidence.csv")
    starts = {int(address, 16) for address in functions}
    if len(evidence) != 80 or len({row["address"] for row in evidence}) != len(evidence):
        raise ValueError("expected 80 distinct scalar deleting-destructor records")

    scratch = ROOT / "build/origin-scalar-deleting-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DeletingDestructor.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DeletingDestructor.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 deleting-destructor probe failed to compile")
        source = source_definition(object_path, comparison, coff_data)
        source_hash = hashlib.sha256(source).hexdigest()
        for row in evidence:
            key, address, size = row["address"], int(row["address"], 16), int(row["size"])
            function, origin = functions[key], origins[key]
            if (size != SIZE or int(function["size"]) != SIZE
                    or function["proposed_name"] != row["inferred_role"]
                    or function["status"] != "excluded" or function["owner"] != "compiler"
                    or origin["origin"] != "compiler" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"] or row["evidence_id"] != "R037"
                    or row["source_sha256"] != source_hash):
                raise ValueError("scalar deleting-destructor ledger differs from evidence")
            code = comparison.pe_bytes_at(target, address, SIZE)
            if hashlib.sha256(code).hexdigest() != row["body_sha256"]:
                raise ValueError("scalar deleting-destructor whole target hash differs")
            destination = verify_target_body(code, address, source, starts, cfg)
            if (row["destructor_address"] != f"0x{destination:08X}"
                    or row["delete_address"] != f"0x{DELETE_ADDRESS:08X}"):
                raise ValueError("scalar deleting-destructor call binding differs")
    print(f"VC7 scalar deleting destructors OK: {len(evidence)} whole bodies, "
          f"{len(evidence) * SIZE} bytes; called destructors retain independent origins; "
          "no authored source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
