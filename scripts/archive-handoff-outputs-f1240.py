#!/usr/bin/env python3
"""F1240: reversible compaction of frozen F1133-F1230 compiler outputs.

Uses the existing F1031 per-member SHA256 archive/restore engine without
changing it. Only regular OBJ/PDB or generated COFF ASM/COD listings in this
explicit epoch are selected by --plan/--archive. Current parent/proof
directories are excluded wholesale. The first listings batch also included
91 native-*.asm views: every original was restored and SHA256-verified, and
they are excluded from further compaction. The archive retains backup copies;
--verify/--restore support those entries, --recompact-restored refuses them.
Sources, JSON, logs, build/, toolchains, Ghidra and older archives are preserved.
Keep each ignored archive and its receipt together during workspace transfer.

Run through scripts/repo-python with --family binaries|listings and one of
--plan, --archive, --verify, --restore PATH, --recompact-restored PATH.
"""
from __future__ import annotations

import importlib.util
from pathlib import Path
import re
import sys
import tarfile

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    'f1240_sha256_archiver', ROOT / 'scripts/archive-recent-probe-objects-f1031.py')
if spec is None or spec.loader is None:
    raise RuntimeError('F1031 SHA256 archive/restore engine unavailable')
archiver = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = archiver
spec.loader.exec_module(archiver)

archiver.FORMAT = 'TH075-F1240-F1133-F1230-COMPILER-OUTPUTS-SHA256-v1'
archiver.NAMES = {
    'binaries': 'f1133-f1230-frozen-obj-pdb-2026-11-06',
    'listings': 'f1133-f1230-frozen-asm-cod-2026-11-06',
}
EXTENSIONS = {'binaries': {'.obj', '.pdb'}, 'listings': {'.asm', '.cod'}}
# Preserve selected parents and their immediate proof contexts as loose files.
# Older F901/F917/F1020/F1068 and all F1231+ work are outside the epoch.
archiver.PROTECTED_DIRS |= {
    'f1138-boss-native-windows',
    'f1155-archive-array-delete',
    'f1156-source-pin-reconciliation',
    'f1157-scene-object-delete',
    'f1171-winmain-whole-exact',
    'f1192-reimu-final-states',
    'f1193-reimu-register-boundary',
    'f1194-remilia-whole-recovery',
    'f1196-58kb-whole-cfg',
    'f1197-46kb-whole-cfg',
    'f1203-third-native-call-abi',
    'f1205-object-4ebda0-recovery',
    'f1209-object-5eb520-virtual-abi',
    'f1214-object-536400-complete',
    'f1219-object-5c9cc0-late',
    'f1227-object-4ca6e0-complete',
}


def native_view(relative: str) -> bool:
    path = Path(relative)
    return (path.suffix.lower() in EXTENSIONS['listings'] and
            path.name.lower().startswith('native-'))


def eligible_relative(relative: str, family: str) -> bool:
    # Includes already archived native views for authenticated verify/restore.
    # gather() and safe_restore_or_recompact() preserve their loose originals.
    if family not in EXTENSIONS or '\\' in relative:
        return False
    path = Path(relative)
    if (path.is_absolute() or '..' in path.parts or len(path.parts) < 3 or
            path.parts[0] != '.analysis' or
            path.suffix.lower() not in EXTENSIONS[family] or
            any(part in archiver.PROTECTED_DIRS for part in path.parts)):
        return False
    match = re.fullmatch(r'f(\d{4})[-_].+', path.parts[1], re.I)
    return bool(match and 1133 <= int(match[1]) <= 1230 and
                relative not in archiver.SELECTED_KEEP)


def gather(family: str) -> list[Path]:
    archiver.ensure(family in EXTENSIONS, 'unsupported compiler output family')
    found = []
    for folder in archiver.ANALYSIS.iterdir():
        match = re.fullmatch(r'f(\d{4})[-_].+', folder.name, re.I)
        if (folder.is_symlink() or not folder.is_dir() or not match or
                not 1133 <= int(match[1]) <= 1230 or
                folder.name in archiver.PROTECTED_DIRS):
            continue
        for path in folder.rglob('*'):
            if path.is_symlink() or not path.is_file():
                continue
            relative = path.relative_to(ROOT).as_posix()
            if eligible_relative(relative, family) and not native_view(relative):
                archiver.safe_file(relative, family)
                found.append(path)
    return sorted(found, key=lambda p: p.relative_to(ROOT).as_posix())


archiver.eligible_relative = eligible_relative
archiver.gather = gather
original_restore_or_recompact = archiver.restore_or_recompact


def safe_restore_or_recompact(family: str, name: str, *, recompact: bool) -> None:
    archiver.ensure(not (recompact and native_view(name)),
                    'original native views must remain loose; compaction refused')
    original_restore_or_recompact(family, name, recompact=recompact)


archiver.restore_or_recompact = safe_restore_or_recompact

if __name__ == '__main__':
    try:
        print('F1240: frozen outputs; native views remain restored loose. '
              'The unchanged F1031 engine labels generic diagnostics F1031/OBJ/PDB; '
              'family=listings also retains native-view backup copies.', flush=True)
        archiver.main()
    except (RuntimeError, OSError, ValueError, tarfile.TarError) as exc:
        print(f'F1240 safe compaction FAILED: {exc}', file=sys.stderr)
        raise SystemExit(1)
