"""Historical views of the append-only exact ledgers.

Older origin verifiers read each ledger's frozen prefix, so an edit to an old
row is rejected. Appended rows, accepted sources and unit entries are proven
by cold replay instead of frozen hashes.
"""
from __future__ import annotations

import csv
from functools import cache
import hashlib
import json
import subprocess
from pathlib import Path
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def digest(data):
    return hashlib.sha256(data).hexdigest()


def plan():
    return json.loads((ROOT / "config/exact-adoptions.json").read_bytes())


@cache
def frozen_files():
    # Later adoption records describe the current sources. The original plan
    # supplies the historical lengths as well as the historical digests.
    raw = subprocess.check_output(
        ["git", "show", "e2c088b8:config/exact-adoptions.json"], cwd=ROOT,
    )
    return json.loads(raw)["files"]


def retained_bytes(path):
    """Return a hash-verified historical prefix, never an unchecked replacement."""
    path = Path(path)
    raw = path.read_bytes()
    relative = path.relative_to(ROOT).as_posix()
    record = frozen_files().get(relative)
    if record is None:
        return raw
    prefix = raw[:record["size"]]
    if digest(prefix) == record["sha256"]:
        return prefix
    # Old rows were edited since this view was frozen; git holds the version.
    return _historical_prefix(relative, record["size"], record["sha256"])


_HISTORY = {}


def _historical_prefix(relative, size, sha):
    key = (relative, size, sha)
    if key not in _HISTORY:
        commits = subprocess.check_output(
            ["git", "log", "--format=%H", "--", relative], cwd=ROOT, text=True).split()
        for commit in commits:
            blob = subprocess.run(["git", "show", f"{commit}:{relative}"], cwd=ROOT,
                                  capture_output=True).stdout
            if len(blob) >= size and digest(blob[:size]) == sha:
                _HISTORY[key] = blob[:size]
                break
        else:
            raise ValueError("Historical exact ledger prefix not found in git: " + relative)
    return _HISTORY[key]


# Provisional names, module labels and source paths can change after adoption.
# The cold replay verifies the accepted extent and relocations.
LABEL_COLUMNS = {"proposed_name", "module", "signature", "notes", "source_file"}


def _same_but_labels(row, expected):
    keys = set(row) | set(expected)
    return all(row.get(k) == expected.get(k) for k in keys - LABEL_COLUMNS)


def historical_functions(records):
    """Project only complete, explicitly accepted function metadata transitions."""
    changes = {row["after"]["address"]: row for row in plan()["functions"]}
    result = []
    for row in records:
        change = changes.get(row["address"])
        if change is None:
            result.append(row)
        elif row == change["after"] or row == change["before"] or _same_but_labels(row, change["after"]):
            result.append(dict(change["before"]))
        else:
            raise ValueError("Unapproved exact function transition: " + row["address"])
    return result


def verify_adoptions():
    """Check the current additions as well as every retained historical prefix."""
    manifest = plan()
    for relative in frozen_files():
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
        if not _same_but_labels(functions.get(address) or {}, change["after"]) or origins.get(address) != change["origin"]:
            raise ValueError("Accepted exact function/origin changed: " + address)
