#!/usr/bin/env python3
"""Cold-verify complete VC7.1 /O1 scalar deleting destructor origins."""
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
SIZE = 28
FIELDS = ((4, "??1ProbeDeletingDestructor@@UAE@XZ"),
          (17, "??3@YAXPAX@Z"))
PROFILE = ("/O1", "/Ob0", "/Gy", "/GR-", "/GX-", "/Zi", "/GS", "/I", "src")


def module(name: str, filename: str):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename: str):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("optimized_scalar_target", "compare-coff-function.py")
    coff_data = module("optimized_scalar_coff", "coff_data.py")
    cfg = module("optimized_scalar_cfg", "verify-authored-origins.py")
    scalar = module("optimized_scalar_template", "verify-scalar-deleting-origins.py")
    target = comparison.verified_target()
    functions = {row["address"]: row for row in rows("functions.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    evidence = rows("optimized-deleting-origin-evidence.csv")
    starts = {int(address, 16) for address in functions}
    if len(evidence) != 53 or len({row["address"] for row in evidence}) != len(evidence):
        raise ValueError("expected 53 distinct optimized deleting-destructor records")

    scratch = ROOT / "build/origin-optimized-deleting-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7DeletingDestructorO1.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7DeletingDestructor.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 /O1 deleting-destructor probe failed to compile")
        source = scalar.source_definition(object_path, comparison, coff_data,
                                          size=SIZE, fields=FIELDS)
        source_hash = hashlib.sha256(source).hexdigest()
        for row in evidence:
            key, address, size = row["address"], int(row["address"], 16), int(row["size"])
            function, origin = functions[key], origins[key]
            if (size != SIZE or int(function["size"]) != SIZE
                    or function["proposed_name"] != row["inferred_role"]
                    or function["status"] != "excluded" or function["owner"] != "compiler"
                    or origin["origin"] != "compiler" or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != row["evidence_id"] or row["evidence_id"] != "R038"
                    or row["source_sha256"] != source_hash):
                raise ValueError("optimized deleting-destructor ledger differs from evidence")
            code = comparison.pe_bytes_at(target, address, SIZE)
            if hashlib.sha256(code).hexdigest() != row["body_sha256"]:
                raise ValueError("optimized deleting-destructor whole target hash differs")
            destination = scalar.verify_target_body(code, address, source, starts, cfg,
                                                     size=SIZE, fields=FIELDS)
            if (row["destructor_address"] != f"0x{destination:08X}"
                    or row["delete_address"] != f"0x{scalar.DELETE_ADDRESS:08X}"):
                raise ValueError("optimized deleting-destructor call binding differs")
    print(f"VC7 /O1 scalar deleting destructors OK: {len(evidence)} whole bodies, "
          f"{len(evidence) * SIZE} bytes; called destructors retain independent origins; "
          "no authored source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
