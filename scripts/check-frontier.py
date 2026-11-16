"""Ratchet the nonexact giant research parents so they never get worse.

usage: scripts/repo-python scripts/check-frontier.py [--update] [NAME ...]

config/frontiers.toml lists each research parent: its probe source, flags,
COFF symbol, original address and size, the SHA-256 of the original extent,
the size of the built body and the byte offsets that still differ from the
original once relocation fields are masked. Each named parent (default: all)
is cold-built and compared again. The check fails if the body size changes
or a byte that matched before now differs. Fewer differing bytes is an
improvement; `--update` records it (and is the only way the file changes).
This is a diagnostic ratchet: exact credit still needs a complete replay unit.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import subprocess
import sys
import tempfile
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
FRONTIERS = ROOT / "config" / "frontiers.toml"
_spec = importlib.util.spec_from_file_location("coff_compare", ROOT / "scripts/compare-coff-function.py")
COFF = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(COFF)

KEYS = ("character", "kind", "source", "flags", "symbol", "address", "size",
        "target_sha256", "object_size", "differing")


def load(path: Path | None = None) -> dict[str, dict]:
    with (path or FRONTIERS).open("rb") as stream:
        return tomllib.load(stream)["frontiers"]


def parse_ranges(text: str) -> set[int]:
    result: set[int] = set()
    for part in filter(None, text.split(",")):
        first, _, last = part.partition("-")
        result.update(range(int(first), int(last or first) + 1))
    return result


def format_ranges(offsets: set[int]) -> str:
    parts, ordered, i = [], sorted(offsets), 0
    while i < len(ordered):
        j = i
        while j + 1 < len(ordered) and ordered[j + 1] == ordered[j] + 1:
            j += 1
        parts.append(str(ordered[i]) if i == j else f"{ordered[i]}-{ordered[j]}")
        i = j + 1
    return ",".join(parts)


def differing(code: bytes, relocations: list[dict], target: bytes) -> set[int]:
    """Offsets that differ outside relocation fields; bytes past either end differ."""
    masked = set()
    for relocation in relocations:
        masked.update(range(int(relocation["offset"]), int(relocation["offset"]) + 4))
    common = min(len(code), len(target))
    result = {i for i in range(common) if i not in masked and code[i] != target[i]}
    result.update(range(common, max(len(code), len(target))))
    return result


def build(entry: dict) -> tuple[bytes, list[dict]]:
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as tmp:
        obj = Path(tmp) / "parent.obj"
        run = subprocess.run([str(ROOT / "scripts/compile-probe.sh"), entry["source"], str(obj),
                              *entry["flags"]], cwd=ROOT, capture_output=True, text=True)
        if run.returncode or not obj.exists():
            raise RuntimeError(f"build failed\n{run.stdout[-800:]}{run.stderr[-800:]}")
        code, relocations = COFF.object_function(obj, entry["symbol"])
    return bytes(code), relocations


def target_extent(entry: dict) -> bytes:
    data = COFF.pe_bytes_at(COFF.verified_target(), entry["address"], entry["size"])
    if hashlib.sha256(data).hexdigest() != entry["target_sha256"]:
        raise RuntimeError("original extent SHA-256 differs from the recorded one")
    return data


def check(name: str, entry: dict, update: bool) -> tuple[bool, dict]:
    """Return (ok, entry to keep) and print one line for the parent."""
    target = target_extent(entry)
    code, relocations = build(entry)
    now = differing(code, relocations, target)
    before = parse_ranges(entry["differing"])
    if len(code) != entry["object_size"]:
        print(f"FAIL {name}: body size {len(code)} != recorded {entry['object_size']}")
        return False, entry
    regressed = now - before
    if regressed:
        print(f"FAIL {name}: {len(regressed)} matching bytes now differ, first at "
              f"{min(regressed):#x}")
        return False, entry
    fixed = before - now
    status = f"{len(now)} differing of {entry['size']}"
    if not fixed:
        print(f"ok   {name}: {status}")
        return True, entry
    if update:
        print(f"ok   {name}: {status}, recorded {len(fixed)} newly matching bytes")
        return True, {**entry, "differing": format_ranges(now)}
    print(f"ok   {name}: {status}, {len(fixed)} newly matching; run with --update to record")
    return True, entry


def dump(frontiers: dict[str, dict]) -> str:
    def value(item):
        if isinstance(item, str):
            return '"' + item.replace("\\", "\\\\").replace('"', '\\"') + '"'
        if isinstance(item, list):
            return "[" + ", ".join(value(v) for v in item) + "]"
        return str(item)
    lines = [line for line in FRONTIERS.read_text().splitlines() if line.startswith("#")] + [""]
    for name, entry in frontiers.items():
        lines.append(f"[frontiers.{name}]")
        for key in KEYS:
            item = entry[key]
            text = f"0x{item:08X}" if key == "address" else value(item)
            lines.append(f"{key} = {text}")
        lines.append("")
    return "\n".join(lines).rstrip("\n") + "\n"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--update", action="store_true", help="record improvements")
    parser.add_argument("names", nargs="*")
    args = parser.parse_args(argv)
    frontiers = load()
    unknown = [name for name in args.names if name not in frontiers]
    if unknown:
        print("unknown frontier: " + ", ".join(unknown), file=sys.stderr)
        return 2
    ok = True
    for name in args.names or list(frontiers):
        try:
            passed, frontiers[name] = check(name, frontiers[name], args.update)
        except (RuntimeError, ValueError) as error:
            print(f"FAIL {name}: {error}")
            passed = False
        ok &= passed
    if args.update:
        FRONTIERS.write_text(dump(frontiers))
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
