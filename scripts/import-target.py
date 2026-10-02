#!/usr/bin/env python3
"""Import the pinned executable from an EXE or the supplied RAR archive."""
from __future__ import annotations
import argparse
import hashlib
from pathlib import Path
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    args = parser.parse_args()
    try:
        with (ROOT / "config/target.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        source = args.source.expanduser().resolve()
        if source.suffix.lower() == ".rar":
            data = subprocess.check_output([
                "unrar", "p", "-inul", str(source), manifest["provenance"]["archive_member"],
            ])
        else:
            data = source.read_bytes()
        target = manifest["target"]
        if len(data) != target["size"] or hashlib.sha256(data).hexdigest() != target["sha256"]:
            raise ValueError("unsupported target; existing resources are unchanged")
        destination = ROOT / "resources" / target["filename"]
        destination.parent.mkdir(parents=True, exist_ok=True)
        if not destination.is_file() or destination.read_bytes() != data:
            temporary = destination.with_suffix(".exe.importing")
            try:
                temporary.write_bytes(data)
                temporary.replace(destination)
            finally:
                temporary.unlink(missing_ok=True)
        print("Pinned target imported: " + str(destination))
        return 0
    except (OSError, KeyError, ValueError, subprocess.CalledProcessError) as exc:
        print("error: target import failed: " + str(exc), file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
