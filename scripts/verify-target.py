#!/usr/bin/env python3
"""Fail-closed identity check for the one supported TH075 executable."""

from __future__ import annotations

import argparse
import hashlib
import os
from pathlib import Path
import sys
import tomllib


ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config" / "target.toml"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Verify the pinned user-supplied Japanese TH075 v1.11 executable"
    )
    parser.add_argument(
        "executable",
        nargs="?",
        type=Path,
        help=(
            "path to th075.exe (default: TH075_TARGET_PATH or "
            "resources/th075.exe)"
        ),
    )
    return parser.parse_args()


def file_hashes(path: Path) -> tuple[str, str]:
    sha256 = hashlib.sha256()
    md5 = hashlib.md5(usedforsecurity=False)
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            sha256.update(block)
            md5.update(block)
    return sha256.hexdigest(), md5.hexdigest()


def main() -> int:
    args = parse_args()
    try:
        with CONFIG.open("rb") as stream:
            expected = tomllib.load(stream)["target"]
    except (OSError, KeyError, tomllib.TOMLDecodeError) as exc:
        print(f"invalid target manifest: {exc}", file=sys.stderr)
        return 2

    configured = os.environ.get("TH075_TARGET_PATH")
    default = (
        Path(configured)
        if configured
        else ROOT / "resources" / str(expected["filename"])
    )
    path = (args.executable or default).expanduser().resolve()
    if not path.is_file():
        print(f"missing target: {path}", file=sys.stderr)
        print(
            "copy the pinned Japanese v1.11 th075.exe to "
            "resources/th075.exe, set TH075_TARGET_PATH, or pass its path explicitly",
            file=sys.stderr,
        )
        return 1

    size = path.stat().st_size
    sha256, md5 = file_hashes(path)
    problems: list[str] = []
    if size != int(expected["size"]):
        problems.append(f"size:   {size} (expected {expected['size']})")
    if sha256 != str(expected["sha256"]).lower():
        problems.append(f"sha256: {sha256} (expected {expected['sha256']})")
    if md5 != str(expected["md5"]).lower():
        problems.append(f"md5:    {md5} (expected {expected['md5']})")
    if problems:
        print(f"unsupported executable: {path}", file=sys.stderr)
        for problem in problems:
            print(f"  {problem}", file=sys.stderr)
        return 1

    print(f"target OK: {path}")
    print(f"sha256: {sha256}")
    print(f"md5:    {md5}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
