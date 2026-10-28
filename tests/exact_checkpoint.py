"""Read the frozen F009 inputs while explicitly validating later exact additions.

Origin evidence and verifier hashes stay unchanged. Only the seven reviewed
append-only ledgers and the literal F010-F020, F022-F047, F049-F060, F062-F065, F067-F084 and F086-F131/F135-F137/F139/F146/F152/F154/F155/F156/F158/F159/F160/F161/F162/F163/F164/F165/F167/F168/F169/F170/F171/F172/F173/F174/F175/F176/F177/F178/F179/F180/F181/F182/F183/F184/F185/F186/F187/F188/F190/F191/F192/F193/F194/F195/F196/F197/F198/F199 function
transitions have a historical view; all other bytes and rows retain their original guards.
"""
from __future__ import annotations

import csv
import hashlib
import json
from pathlib import Path
import tomllib

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_SHA256 = "3487d84c8163589b4a1fd26969d52626d93e1e3cafb1a5033aefcad03573fa0e"


def digest(data):
    return hashlib.sha256(data).hexdigest()


def plan():
    raw = (ROOT / "config/exact-adoptions.json").read_bytes()
    if digest(raw) != MANIFEST_SHA256:
        raise ValueError("Exact adoption evidence changed without review")
    return json.loads(raw)


def retained_bytes(path):
    """Return a hash-verified historical prefix, never an unchecked replacement."""
    path = Path(path)
    raw = path.read_bytes()
    relative = path.relative_to(ROOT).as_posix()
    record = plan()["files"].get(relative)
    if record is None:
        return raw
    if digest(raw) != record["current_sha256"]:
        raise ValueError("Unapproved exact ledger change: " + relative)
    prefix = raw[:record["size"]]
    if digest(prefix) != record["sha256"]:
        raise ValueError("Historical exact ledger prefix changed: " + relative)
    return prefix


def historical_functions(records):
    """Project only complete, explicitly accepted function metadata transitions."""
    changes = {row["after"]["address"]: row for row in plan()["functions"]}
    result = []
    for row in records:
        change = changes.get(row["address"])
        if change is None:
            result.append(row)
        elif row == change["after"] or row == change["before"]:
            result.append(dict(change["before"]))
        else:
            raise ValueError("Unapproved exact function transition: " + row["address"])
    return result


def verify_adoptions():
    """Check the current additions as well as every retained historical prefix."""
    manifest = plan()
    for relative in manifest["files"]:
        retained_bytes(ROOT / relative)
    for relative, sha in manifest["source_sha256"].items():
        if digest((ROOT / relative).read_bytes()) != sha:
            raise ValueError("Accepted exact source changed: " + relative)
    units = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]
    for name, expected in manifest["added_units"].items():
        if units.get(name) != expected:
            raise ValueError("Accepted exact unit changed: " + name)
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open(newline="") as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    for change in manifest["functions"]:
        address = change["after"]["address"]
        if functions.get(address) != change["after"] or origins.get(address) != change["origin"]:
            raise ValueError("Accepted exact function/origin changed: " + address)
