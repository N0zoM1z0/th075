#!/usr/bin/env python3
"""Cold-check whole relocation-free VC7 STL COMDAT aliases in the target."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
PROFILE = ["/Od", "/Ob0", "/Gy", "/GR-", "/GX", "/Zi", "/GS", "/I", "src"]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def rows(filename):
    with (ROOT / "config" / filename).open(newline="") as stream:
        return list(csv.DictReader(stream))


def main():
    comparison = module("identical_vendor_coff", "compare-coff-function.py")
    vendor = module("identical_vendor_extent", "verify-vendor-record-origins.py")
    sdk = module("identical_vendor_cfg", "verify-sdk-origins.py")
    target = comparison.verified_target()
    evidence = rows("vendor-identical-origin-evidence.csv")
    bases = {row["address"]: row for row in rows("vendor-origin-evidence.csv")}
    origins = {row["address"]: row for row in rows("function-origins.csv")}
    functions = {row["address"]: row for row in rows("functions.csv")}
    if len(evidence) != 25 or len({row["address"] for row in evidence}) != len(evidence):
        raise ValueError("identical vendor aliases must contain 25 unique candidates")
    if {row["base_address"] for row in evidence} != {
            "0x00405270", "0x00405B20", "0x00405D90", "0x00406260"}:
        raise ValueError("identical vendor aliases name an unexpected source family")
    scratch = ROOT / "build/origin-identical-vendor-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / "VC7InputContainers.obj"
        result = subprocess.run(
            [str(ROOT / "scripts/compile-probe.sh"),
             str(ROOT / "probes/VC7InputContainers.cpp"), str(object_path), *PROFILE],
            cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("pinned VC7 STL probe compilation failed: " + result.stderr[-500:])
        object_data = object_path.read_bytes()
        source = {}
        for key in {row["base_address"] for row in evidence}:
            base = bases[key]
            size = int(base["size"])
            if (size < 32 or base["relocation_bindings"] != "[]"
                    or origins[key]["origin"] != "library"
                    or origins[key]["disposition"] != "exclude"):
                raise ValueError("base does not have independent relocation-free vendor evidence")
            whole_size = vendor.complete_aux_section_size(
                object_data, base["coff_symbol"], comparison.coff_name)
            body, relocations = comparison.object_function(
                object_path, base["coff_symbol"], size)
            if (whole_size != size or len(body) != size or relocations
                    or hashlib.sha256(body).hexdigest() != base["nonrelocation_sha256"]
                    or body != comparison.pe_bytes_at(target, int(key, 16), size)):
                raise ValueError("base differs from the complete cold VC7 STL source body")
            sdk.verify_control_flow(body, int(key, 16))
            source[key] = bytes(body)
        total = 0
        for row in evidence:
            key, base = row["address"], row["base_address"]
            size = int(row["size"])
            code = comparison.pe_bytes_at(target, int(key, 16), size)
            origin, function = origins[key], functions[key]
            if (key == base or size != len(source[base]) or code != source[base]
                    or hashlib.sha256(code).hexdigest() != row["body_sha256"]
                    or row["evidence_id"] != "R051"
                    or origin["origin"] != "library"
                    or origin["disposition"] != "exclude"
                    or origin["evidence_id"] != "R051"
                    or function["status"] != "excluded"
                    or function["owner"] != "library"
                    or int(function["size"]) != size):
                raise ValueError("identical vendor alias or ledger differs: " + key)
            sdk.verify_control_flow(code, int(key, 16))
            total += size
    print(f"Identical VC7 STL origins OK: {len(evidence)} complete aliases, "
          f"{total} bytes across four cold-compiled source COMDATs; "
          "no authored, source, or exact credit.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, KeyError, IndexError, ValueError, subprocess.CalledProcessError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
