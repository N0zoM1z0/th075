"""Historical views of the append-only exact ledgers.

Older origin verifiers read each ledger's frozen prefix, so an edit to an old
row is rejected. Appended rows, accepted sources and unit entries are proven
by cold replay instead of frozen hashes.
"""
from __future__ import annotations

import csv
import hashlib
import json
from pathlib import Path
import tomllib

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_SHA256 = "634e75b897803ceb9b4495630289eb6e216143b17ceb9945a8dfb6c22306499d"


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
    # Accepted sources and unit entries are proven by cold replay, not by
    # frozen hashes; readable source edits must stay possible.
    units = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]
    for name in manifest["added_units"]:
        if name not in units:
            raise ValueError("Accepted exact unit removed: " + name)
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open(newline="") as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    for change in manifest["functions"]:
        address = change["after"]["address"]
        if functions.get(address) != change["after"] or origins.get(address) != change["origin"]:
            raise ValueError("Accepted exact function/origin changed: " + address)
