#!/usr/bin/env python3
"""F1144: SHA256-reversible local compaction of historical F1030-F1132 OBJ/PDB.

This is a narrow newer-range adapter to the proven F1031 tar+JSON archiver.
It keeps original/native target and current proof objects, all C++/PDB source
contexts, historical JSON/log/text evidence, accepted build/matching, VC7.1/Wine,
Ghidra and prior SHA256-indexed local archives untouched. The new archive and
SHA256 receipt are machine-local, ignored by Git; retain BOTH during handoff.

Run from this repository under scripts/repo-python:
  --family binaries --plan
  --family binaries --archive
  --family binaries --verify
  --family binaries --restore .analysis/fNNNN-.../some-probe.obj
  --family binaries --recompact-restored .analysis/fNNNN-.../some-probe.obj

NEVER rerun --archive once an archive+receipt exists, and never delete either.
"""
from __future__ import annotations

import importlib.util
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'scripts/archive-recent-probe-objects-f1031.py'
spec = importlib.util.spec_from_file_location('f1144_sha256_archiver', SOURCE)
if spec is None or spec.loader is None:
    raise RuntimeError('F1031 SHA256 archiver source unavailable')
archiver = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = archiver
spec.loader.exec_module(archiver)

# Independent version identity: never replace an earlier F907/F1031 archive.
archiver.FORMAT = 'TH075-F1144-F1030-F1132-VC71-RESEARCH-SHA256-v1'
archiver.NAMES = {
    'binaries': 'f1030-f1132-research-obj-pdb-2026-11-04'
}
# Do not archive any live current-parent COFF or selected active native proof.
# These are either verification inputs or immediate next-agent research state.
archiver.PROTECTED_DIRS = archiver.PROTECTED_DIRS | {
    'f1068-boss-live-all-native',
    'f1126-native391',  # unresolved FUCOMPP proof, active source tests
    'f1130-native3e5-continuation',
    'f1131-native3e3',
    'f1132-native3e4',
    'f1138-boss-native-windows',
}


def eligible_relative(relative: str, family: str) -> bool:
    """Only reproducible OBJ/PDB in explicit research epoch, no symlinks."""
    if family != 'binaries' or '\\' in relative:
        return False
    path = Path(relative)
    if (path.is_absolute() or '..' in path.parts or
            len(path.parts) < 3 or path.parts[0] != '.analysis' or
            path.suffix.lower() not in {'.obj', '.pdb'} or
            any(part in archiver.PROTECTED_DIRS for part in path.parts)):
        return False
    match = re.fullmatch(r'f(\d{4})[-_].+', path.parts[1], re.I)
    return bool(match and 1030 <= int(match.group(1)) <= 1132 and
                relative not in archiver.SELECTED_KEEP)


def gather(family: str) -> list[Path]:
    if family != 'binaries':
        raise RuntimeError('unsupported original research binary family')
    found: list[Path] = []
    for folder in archiver.ANALYSIS.iterdir():
        if folder.is_symlink() or not folder.is_dir():
            continue
        if not re.fullmatch(r'f(\d{4})[-_].+', folder.name, re.I):
            continue
        for path in folder.rglob('*'):
            if path.is_symlink() or not path.is_file():
                continue
            relative = path.relative_to(ROOT).as_posix()
            if eligible_relative(relative, family):
                archiver.safe_file(relative, family)
                found.append(path)
    return sorted(found, key=lambda p: p.relative_to(ROOT).as_posix())


archiver.eligible_relative = eligible_relative
archiver.gather = gather

if __name__ == '__main__':
    try:
        archiver.main()
    except (RuntimeError, OSError, ValueError) as exc:
        print(f'F1144 safe local compaction FAILED: {exc}', file=sys.stderr)
        raise SystemExit(1)
