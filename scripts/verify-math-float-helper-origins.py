#!/usr/bin/env python3
"""Verify the complete authored float wrappers and their game call contexts."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]


def load_rows(name):
    with (ROOT / "config" / name).open(newline="") as stream:
        return list(csv.DictReader(stream))


def unique(rows, key, value):
    found = [row for row in rows if row[key] == value]
    if len(found) != 1:
        raise ValueError(f"expected one {key}={value}, found {len(found)}")
    return found[0]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    evidence = json.loads((ROOT / "config/math-float-helper-origin-evidence.json").read_text())
    if evidence["evidence_id"] != "R271":
        raise ValueError("wrong math-float evidence batch")

    spec = importlib.util.spec_from_file_location("math_float_coff", ROOT / "scripts/compare-coff-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    auth_spec = importlib.util.spec_from_file_location("math_float_authored", ROOT / "scripts/verify-authored-origins.py")
    authored = importlib.util.module_from_spec(auth_spec)
    auth_spec.loader.exec_module(authored)
    target = compare.verified_target()
    target_hash = sha((ROOT / "resources/th075.exe").read_bytes())
    if target_hash != evidence["target_sha256"]:
        raise ValueError("pinned target changed")

    source = ROOT / evidence["source"]
    header = ROOT / evidence["sdk_header"]
    if sha(source.read_bytes()) != evidence["source_sha256"]:
        raise ValueError("natural source hash changed")
    if sha(header.read_bytes()) != evidence["sdk_header_sha256"]:
        raise ValueError("pinned SDK math.h hash changed")
    source_text = source.read_text()
    header_lines = header.read_text(errors="strict").splitlines()
    for name, expected in (("fabsf", "fabs((double)_X)"),
                           ("sqrtf", "sqrt((double)_X)")):
        if expected not in source_text and name not in source_text:
            raise ValueError("natural source omits " + name)
    for overload in evidence["sdk_inline_float_overloads"]:
        line = header_lines[overload["line"] - 1]
        if not line.strip().startswith("inline float " + overload["name"] + "("):
            raise ValueError("SDK inline overload line changed: " + overload["name"])

    functions = load_rows("functions.csv")
    origins = load_rows("function-origins.csv")
    matches = load_rows("matches.csv")
    authored_rows = load_rows("authored-origin-evidence.csv")
    with (ROOT / "config/match-units.toml").open("rb") as stream:
        units = tomllib.load(stream)["units"]

    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    total_bytes = total_callers = total_calls = 0
    for item in evidence["wrappers"]:
        address, size = item["address"], item["size"]
        code = compare.pe_bytes_at(target, int(address, 16), size)
        if sha(code) != item["body_sha256"]:
            raise ValueError("whole wrapper body hash mismatch: " + address)
        cfg = authored.verify_body(code, int(address, 16))
        if cfg != (1, 0):
            raise ValueError("wrapper CFG mismatch: " + address)

        function = unique(functions, "address", address)
        origin = unique(origins, "address", address)
        match = unique(matches, "address", address)
        authored_row = unique(authored_rows, "address", address)
        evidence_id = item.get("evidence_id", evidence["evidence_id"])
        origin_confidence = item.get("origin_confidence", "high")
        if (int(function["size"]) != size or function["proposed_name"] != item["source_function"]
                or function["module"] != "MathLookup" or function["status"] != "matching"
                or function["calling_convention"] != "cdecl" or function["source_file"] != evidence["source"]):
            raise ValueError("function ledger mismatch: " + address)
        if (origin["origin"] != "authored" or origin["subsystem"] != "MathLookup"
                or origin["disposition"] != "authored" or origin["confidence"] != origin_confidence
                or origin["evidence_id"] != evidence_id):
            raise ValueError("origin ledger mismatch: " + address)
        if (authored_row["body_sha256"] != item["body_sha256"] or int(authored_row["size"]) != size
                or authored_row["evidence_id"] != evidence_id or int(authored_row["return_count"]) != 1
                or int(authored_row["internal_branch_count"]) != 0
                or int(authored_row["external_branch_count"]) != 0):
            raise ValueError("authored body ledger mismatch: " + address)
        if (match["status"] != "matching" or int(match["size"]) != size
                or match["unit"] != item["unit"] or match["match_percent"] != "100.00"):
            raise ValueError("exact match ledger mismatch: " + address)

        unit = unique([{"name": name, **value} for name, value in units.items()], "name", item["unit"])
        if (unit["source"] != evidence["source"] or unit["object"] != "build/matching/MathFloatHelpers.obj"
                or unit["symbol"] != item["symbol"] or int(unit["target_address"]) != int(address, 16)
                or int(unit["size"]) != size):
            raise ValueError("match unit mismatch: " + address)
        if (len(unit.get("relocations", [])) != 1
                or int(unit["relocations"][0]["offset"]) != item["relocation_offset"]
                or unit["relocations"][0]["type"] != "REL32"
                or int(unit["relocations"][0]["target"]) != int(item["worker_address"], 16)):
            raise ValueError("wrapper's real worker relocation changed: " + address)
        wrapper_calls = [ins for ins in decoder.disasm(code, int(address, 16))
                         if ins.group(CS_GRP_CALL) and ins.operands
                         and ins.operands[0].type == X86_OP_IMM]
        if len(wrapper_calls) != 1 or wrapper_calls[0].operands[0].imm != int(item["worker_address"], 16):
            raise ValueError("wrapper does not call its recorded SDK worker: " + address)

        worker_code = compare.pe_bytes_at(target, int(item["worker_address"], 16), item["worker_size"])
        if sha(worker_code) != item["worker_body_sha256"]:
            raise ValueError("inline SDK worker body changed: " + item["worker_address"])
        worker_calls = [ins for ins in decoder.disasm(worker_code, int(item["worker_address"], 16))
                        if ins.group(CS_GRP_CALL) and ins.operands
                        and ins.operands[0].type == X86_OP_IMM]
        if len(worker_calls) != 1 or worker_calls[0].operands[0].imm != int(item["worker_callee"], 16):
            raise ValueError("inline worker's CRT destination changed: " + item["worker_address"])

        callers = item["callers"]
        if len(callers) != item["caller_count"]:
            raise ValueError("caller count metadata mismatch: " + address)
        found_sites = 0
        for parent in callers:
            parent_address = parent["address"]
            parent_function = unique(functions, "address", parent_address)
            parent_origin = unique(origins, "address", parent_address)
            parent_authored = unique(authored_rows, "address", parent_address)
            if (parent_origin["origin"] != "authored" or parent_origin["evidence_id"] != parent["origin_evidence_id"]
                    or parent_authored["evidence_id"] != parent["origin_evidence_id"]
                    or parent_authored["body_sha256"] != parent["body_sha256"]
                    or int(parent_function["size"]) != int(parent["size"])):
                raise ValueError("caller is not a complete independently authored parent: " + parent_address)
            parent_code = compare.pe_bytes_at(target, int(parent_address, 16), int(parent["size"]))
            if sha(parent_code) != parent["body_sha256"]:
                raise ValueError("caller whole-body hash changed: " + parent_address)
            actual_sites = [hex(ins.address) for ins in decoder.disasm(parent_code, int(parent_address, 16))
                            if ins.group(CS_GRP_CALL) and ins.operands
                            and ins.operands[0].type == X86_OP_IMM
                            and ins.operands[0].imm == int(address, 16)]
            if actual_sites != parent["call_sites"]:
                raise ValueError("direct callsite evidence changed: " + parent_address)
            found_sites += len(actual_sites)
        if found_sites != item["call_site_count"]:
            raise ValueError("aggregate callsite count mismatch: " + address)

        # The atan2f header worker has its own VC71CRT origin record; the
        # fabsf/sqrtf workers remain unclassified under the preserved R163 cohort.
        worker_origin = unique(origins, "address", item["worker_address"])
        worker_function = unique(functions, "address", item["worker_address"])
        if item["worker_address"] == "0x00483320":
            if (worker_origin["origin"] != "library" or worker_origin["subsystem"] != "VC71CRT"
                    or worker_origin["disposition"] != "exclude" or worker_origin["evidence_id"] != "R270"
                    or worker_function["module"] != "VC71CRT" or worker_function["status"] != "excluded"
                    or worker_function["owner"] != "library"):
                raise ValueError("atan2f inline worker lost its separate VC71CRT origin")
        elif (worker_origin["origin"] != "unknown" or worker_origin["disposition"] != "review"
              or worker_function["status"] != "unclassified"):
            raise ValueError("fabsf/sqrtf inline workers must remain uncredited: " + item["worker_address"])
        if any(row["address"] == item["worker_address"] for row in matches):
            raise ValueError("SDK inline worker was incorrectly added as an exact unit")

        total_bytes += size
        total_callers += len(callers)
        total_calls += found_sites
        print(f"{address}: authored {size}B, {len(callers)} authored parents / {found_sites} direct calls; worker remains uncredited")

    # The angle wrapper was accepted earlier under R269/R270; preserve its
    # distinct, already-reviewed source/worker ownership rather than re-crediting it.
    prior = unique(functions, "address", "0x00483300")
    prior_origin = unique(origins, "address", "0x00483300")
    prior_match = unique(matches, "address", "0x00483300")
    prior_authored = unique(authored_rows, "address", "0x00483300")
    angle_evidence = json.loads((ROOT / "config/angle-at-00483300-origin-evidence.json").read_text())
    if (prior["status"] != "matching" or prior_origin["evidence_id"] != "R269"
            or prior_match["unit"] != "math-angle-at-00483300"
            or prior_authored["evidence_id"] != "R269"
            or angle_evidence["source"]["path"] != evidence["source"]
            or angle_evidence["source"]["sha256"] != evidence["source_sha256"]):
        raise ValueError("prior R269/R270 angle-wrapper acceptance was not preserved")
    print(f"Math float helper origins OK: 2 new wrappers / {total_bytes} bytes; {total_callers} complete authored parents / {total_calls} original callsites; prior R269 angle pair preserved.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, TypeError, ValueError) as exc:
        import sys
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
