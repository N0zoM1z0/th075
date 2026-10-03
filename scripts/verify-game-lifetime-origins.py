#!/usr/bin/env python3
"""Cold-replay R108 lifetime ownership and explicit/implicit ambiguity evidence."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
KEYS = {"0x0040D8C0", "0x0040D8E0", "0x00411C10", "0x004251C0", "0x00449D40", "0x00449DE0"}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def complete_definition(path, row, comparison, coff):
    """Include the whole sole-function COMDAT, including aux-less implicit methods."""
    data = path.read_bytes()
    count, symbols = coff.parse_symbols(data, comparison.coff_name)
    found = [s for s in symbols if s["symbol"] == row["symbol"] and s["section"] > 0]
    if len(found) != 1:
        raise ValueError("lifetime probe lacks one source definition")
    symbol = found[0]
    number = symbol["section"]
    if not 1 <= number <= count or symbol["offset"] or symbol["type"] != 0x20:
        raise ValueError("lifetime source symbol is not a whole function")
    header = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (number - 1) * 40)
    peers = [s for s in symbols if s["section"] == number and s["type"] == 0x20]
    if (len(peers) != 1 or header[3] != row["size"] or not header[9] & 0x20
            or not header[9] & 0x1000 or header[7] != len(row["relocations"])
            or header[4] + header[3] > len(data)):
        raise ValueError("lifetime source extent or COMDAT differs")
    code, relocations = comparison.object_function(path, row["symbol"], row["size"])
    if len(code) != row["size"] or hashlib.sha256(code).hexdigest() != row["body_sha256"]:
        raise ValueError("complete lifetime source bytes differ")
    if [(r["offset"], r["type"], r["symbol"], r["addend"]) for r in relocations] != [
            (r["offset"], r["type"], r["symbol"], r["addend"]) for r in row["relocations"]]:
        raise ValueError("lifetime source typed relocations differ")
    return code, relocations


def body_facts(instructions):
    return {
        "returns": [{"site": f"0x{i.address:08X}", "cleanup": i.operands[0].imm if i.operands else 0}
                    for i in instructions if i.mnemonic == "ret"],
        "direct_calls": [{"site": f"0x{i.address:08X}", "target": f"0x{i.operands[0].imm:08X}"}
                         for i in instructions if i.mnemonic == "call" and i.operands[0].type == X86_OP_IMM],
        "vtable_writes": [{"site": f"0x{i.address:08X}", "target": f"0x{i.operands[1].imm:08X}", "operand": i.op_str}
                          for i in instructions if i.mnemonic == "mov" and len(i.operands) == 2
                          and i.operands[0].type == X86_OP_MEM and i.operands[1].type == X86_OP_IMM
                          and 0x650000 <= i.operands[1].imm < 0x660000],
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--evidence-only", action="store_true", help="verify target/source before accepting ledger changes")
    args = parser.parse_args()
    comparison = module("lifetime_target", "compare-coff-function.py")
    authored = module("lifetime_cfg", "verify-authored-origins.py")
    coff = module("lifetime_coff", "coff_data.py")
    record = module("lifetime_compare", "verify-vendor-record-origins.py")
    sdk = module("lifetime_source_cfg", "verify-sdk-origins.py")
    sections = module("lifetime_sections", "verify-compiler-origins.py")
    target = comparison.verified_target()
    manifest = json.loads((ROOT / "config/game-lifetime-origin-evidence.json").read_text())
    records = manifest["functions"]
    anchors = manifest["anchors"]
    if (manifest["evidence_id"] != "R108" or manifest["target_sha256"] != hashlib.sha256(target).hexdigest()
            or len(records) != 6 or {r["address"] for r in records} != KEYS
            or sum(r["size"] for r in records) != 176
            or [r["address"] for r in records if r["decision"] == "authored"] != ["0x00449D40"]
            or sum(r["decision"] == "pending" for r in records) != 5
            or len(anchors) != 103 or len({r["address"] for r in anchors}) != 103
            or len(manifest["parent_calls"]) != 98):
        raise ValueError("R108 cohort or ownership decisions differ")
    functions = {r["address"]: r for r in authored.rows("functions.csv")}
    origins = {r["address"]: r for r in authored.rows("function-origins.csv")}
    evidence = {r["address"]: r for r in authored.rows("authored-origin-evidence.csv")}
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded, bodies = {}, {}
    switches = authored.rows("authored-origin-switches.csv")
    directs = authored.rows("authored-origin-direct-switches.csv")
    for row in records + anchors:
        key = row["address"]
        address, size = int(key, 16), row["size"]
        function = functions[key]
        if (int(function["size"]) != size or function["span_end"] != row["span_end"]
                or int(row["span_end"], 16) != address + size - 1
                or any(address < int(k, 16) < address + size for k in functions)):
            raise ValueError("lifetime target ledger extent differs: " + key)
        body = comparison.pe_bytes_at(target, address, size)
        if hashlib.sha256(body).hexdigest() != row["body_sha256"]:
            raise ValueError("lifetime complete target/candidate hash differs: " + key)
        if row["extent_status"] == "complete":
            counts = authored.verify_body(body, address, [r for r in switches if r["address"] == key],
                                          lambda a, n: comparison.pe_bytes_at(target, a, n),
                                          [r for r in directs if r["address"] == key])
            if list(counts) != row["cfg"]:
                raise ValueError("lifetime target CFG differs: " + key)
        elif key != "0x0040EC8A" or row["cfg"] is not None:
            raise ValueError("unexpected unresolved lifetime parent extent")
        decoded[key] = list(decoder.disasm(body, address))
        bodies[key] = body
        facts = body_facts(decoded[key])
        for field in facts:
            if field in row and facts[field] != row[field]:
                raise ValueError("lifetime calls, returns or vtable writes differ: " + key)
        if key not in KEYS and row["origin"] != "unknown":
            if (origins[key]["origin"] != row["origin"]
                    or origins[key]["evidence_id"] != row["origin_evidence"]
                    or function["proposed_name"] != row["role"]):
                raise ValueError("independent lifetime anchor ownership differs")
    for edge in manifest["parent_calls"]:
        if not any(r["site"] == edge["site"] and r["target"] == edge["child"]
                   for r in body_facts(decoded[edge["parent"]])["direct_calls"]):
            raise ValueError("whole lifetime parent lacks its recorded call")
    pe_sections = sections.sections(target)
    for row in manifest["vtables"]:
        address, size = int(row["address"], 16), row["size"]
        body = comparison.pe_bytes_at(target, address, size)
        if (hashlib.sha256(body).hexdigest() != row["body_sha256"]
                or [f"0x{v:08X}" for v in struct.unpack("<" + "I" * (size // 4), body)] != row["slots"]
                or not any(a <= address and address + size <= a + n and flags & 0x40000000
                           and not flags & 0xA0000000 for a, n, flags in pe_sections)):
            raise ValueError("selected readonly lifetime vtable slots differ")
    if (manifest["vtables"][1]["slots"][0] != "0x00449D60"
            or body_facts(decoded["0x00449D60"])["direct_calls"][0]["target"] != "0x00449D40"):
        raise ValueError("stage virtual deleting slot does not bind this destructor")
    scratch = ROOT / "build/origin-game-lifetime-verification"
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary) / "VC7GameLifetimeAlternatives.obj"
        subprocess.run([str(ROOT / "scripts/compile-probe.sh"), str(ROOT / manifest["probe"]),
                        str(path), *manifest["profile"]], cwd=ROOT, capture_output=True, text=True, check=True)
        for row in records:
            for alternative in row["source_alternatives"]:
                source, relocations = complete_definition(path, alternative, comparison, coff)
                record.compare_complete_body(source, relocations, bodies[row["address"]],
                                             int(row["address"], 16), alternative["relocations"], comparison, sdk)
            if row["decision"] == "pending" and len(row["source_alternatives"]) != 2:
                raise ValueError("pending lifetime decision lacks both whole source alternatives")
        for control in manifest["implicit_destructor_controls"]:
            source, _ = complete_definition(path, control, comparison, coff)
            if len(source) == len(bodies["0x00449D40"]):
                raise ValueError("implicit cleanup control no longer distinguishes the destructor")
    if not args.evidence_only:
        for row in records:
            key = row["address"]
            if row["decision"] == "authored":
                body_record = evidence[key]
                if (origins[key]["origin"] != "authored" or origins[key]["evidence_id"] != "R108"
                        or functions[key]["owner"] != "authored" or functions[key]["proposed_name"] != row["role"]
                        or body_record["evidence_id"] != "R108" or body_record["body_sha256"] != row["body_sha256"]):
                    raise ValueError("R108 accepted authored ledger differs")
            elif (origins[key]["origin"] != "unknown" or origins[key]["disposition"] != "review"
                  or origins[key]["evidence_id"] != "R108"
                  or origins[key]["confidence"] != "explicit-implicit-source-ambiguity"):
                raise ValueError("ambiguous lifetime function received unsupported origin credit")
        if authored.main() != 0:
            raise ValueError("authored context replay failed")
    print("R108 lifetime origins OK: six complete bodies / 176 bytes, 103 whole/candidate anchors, "
          "98 parent edges, cold typed source alternatives and selected vtable slots; "
          "one authored destructor / 31 bytes, five origins still pending; no source or exact credit.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, struct.error, subprocess.CalledProcessError) as error:
        print("error: " + str(error), file=sys.stderr)
        raise SystemExit(1)
