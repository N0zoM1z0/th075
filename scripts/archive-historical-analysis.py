#!/usr/bin/env python3
"""Losslessly compact old, ignored historical analysis snapshots.

Only historical parent/adoption snapshots under .analysis are eligible.
Keep source probes, originals, current match units, Wine, Ghidra, COFF
objects and all H184-protected artifacts untouched. Recover archived
snapshots individually with --restore; detailed hashes live in the local
ignored .analysis/cache-archives/snapshot-compaction-index.json.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
# Only the *completed* older F-series parent snapshots are archival.
# A newly created in-progress F536+ parent-and-seed file is NOT eligible.
LAST_FROZEN_PARENT_BATCH = 184
INDEX = ROOT / '.analysis/cache-archives/snapshot-compaction-index.json'
SCHEMA = 1


def file_digest(path: Path) -> tuple[str, int]:
    digest = hashlib.sha256()
    size = 0
    with path.open('rb') as source:
        while part := source.read(1024 * 1024):
            digest.update(part)
            size += len(part)
    return digest.hexdigest(), size


def decompressed_digest(path: Path) -> tuple[str, int]:
    process = subprocess.Popen(['zstd', '-q', '-d', '-c', str(path)], stdout=subprocess.PIPE)
    assert process.stdout is not None
    digest = hashlib.sha256()
    size = 0
    for part in iter(lambda: process.stdout.read(1024 * 1024), b''):
        digest.update(part)
        size += len(part)
    process.stdout.close()
    if process.wait() != 0:
        raise RuntimeError(f'Cannot decompress and attest {path}')
    return digest.hexdigest(), size


def save_index(index: dict) -> None:
    INDEX.parent.mkdir(parents=True, exist_ok=True)
    tmp = INDEX.with_name(INDEX.name + '.atomic')
    if tmp.exists():
        raise RuntimeError(f'Existing partial index: inspect instead of overwriting {tmp}')
    try:
        tmp.write_text(json.dumps(index, indent=2, ensure_ascii=False) + '\n')
        tmp.replace(INDEX)
    finally:
        if tmp.exists():
            tmp.unlink()


def load_index() -> dict:
    if INDEX.exists():
        index = json.loads(INDEX.read_text())
        if index.get('schema') != SCHEMA:
            raise RuntimeError('Unknown archive manifest format: do not overwrite it')
        return index
    return {'schema': SCHEMA,
            'description': 'Ignored local historical JSON snapshots, independently checked SHA256 before source removal',
            'files': {}}


def eligible() -> list[tuple[Path, str]]:
    root = ROOT / '.analysis'
    result = []
    for path in root.rglob('*.json'):
        if path.is_symlink() or not path.is_file():
            continue
        name = path.name
        if name in ('parent-and-seed.json', 'resumption-seed.json'):
            family = 'seed'
        elif re.fullmatch(r'f\d{3}-adoption-parent\.json', name):
            family = 'adoption'
        else:
            continue
        # Never compress a protected object/PDB or a live current source.
        if 'cache-archives' in path.parts or 'vc71-wine' in path.parts:
            continue
        if name == 'resumption-seed.json':
            if path.parent.name != 'h184-handoff':
                continue
        elif name == 'parent-and-seed.json':
            prior_batches = [int(hit.group(1))
                             for component in path.relative_to(root).parts
                             if (hit := re.match(r'f(\d{3})(?:-|$)', component))]
            if not prior_batches or min(prior_batches) > LAST_FROZEN_PARENT_BATCH:
                continue
        else:  # canonical adoption-parent, numbered at root
            match = re.fullmatch(r'f(\d{3})-adoption-parent\.json', name)
            if not match or int(match.group(1)) > LAST_FROZEN_PARENT_BATCH:
                continue
        result.append((path, family))
    return sorted(result)


def safely_archive(path: Path, family: str, index: dict) -> tuple[int, int]:
    rel = path.relative_to(ROOT).as_posix()
    original_hash, original_size = file_digest(path)
    if rel in index['files']:
        prior = index['files'][rel]
        if original_hash != prior['sha256'] or original_size != prior['bytes']:
            raise RuntimeError(f'Snapshot changed since archive: {rel}; preserve and inspect')
        archive = ROOT / prior['archive']
        if not archive.exists() or file_digest(archive) != (prior['archive_sha256'], prior['archive_bytes']):
            raise RuntimeError(f'Previously archived backup missing or altered: {archive}')
        if decompressed_digest(archive) != (original_hash, original_size):
            raise RuntimeError(f'Previously archived content mismatch: {archive}')
        path.unlink()  # recovers an interrupted last run after a durable manifest write
        return original_size, prior['archive_bytes']
    archive = path.with_name(path.name + '.zst')
    part = archive.with_name(archive.name + '.partial')
    if archive.exists() or part.exists():
        raise RuntimeError(f'Existing unmatched archive or interrupted partial: inspect {archive} / {part}')
    if not shutil.which('zstd'):
        raise RuntimeError('zstd missing; cannot losslessly archive')
    try:
        subprocess.run(['zstd', '-3', '-T2', '-q', '-o', str(part), str(path)], check=True)
        if decompressed_digest(part) != (original_hash, original_size):
            raise RuntimeError(f'Archive is NOT bit-for-bit reversible: {path}')
        part.rename(archive)
        archive_sha, compressed_size = file_digest(archive)
        entry = {'family': family, 'sha256': original_hash,
                 'bytes': original_size,
                 'archive': archive.relative_to(ROOT).as_posix(),
                 'archive_sha256': archive_sha,
                 'archive_bytes': compressed_size}
        index['files'][rel] = entry
        save_index(index)  # receipt is durable BEFORE deleting uncompressed data
        path.unlink()
        return original_size, compressed_size
    finally:
        if part.exists():
            # Failed verification is not automatically discarded: the original
            # is still present and a failed .partial requires manual inspection.
            print('NOTICE: partial archive preserved for inspection:', part, file=sys.stderr)


def restore(index: dict, rel: str) -> None:
    if Path(rel).is_absolute() or '..' in Path(rel).parts:
        raise ValueError('Restore requires a safe repository-relative path')
    if rel not in index['files']:
        raise ValueError(f'No archived snapshot recorded for {rel}')
    entry = index['files'][rel]
    path = ROOT / rel
    archive = ROOT / entry['archive']
    assert file_digest(archive) == (entry['archive_sha256'], entry['archive_bytes'])
    if path.exists():
        assert file_digest(path) == (entry['sha256'], entry['bytes'])
        print('Original already safely restored:', rel)
        return
    partial = path.with_name(path.name + '.restore-partial')
    if partial.exists():
        raise RuntimeError(f'Existing restore partial: inspect {partial}')
    with partial.open('wb') as out:
        subprocess.run(['zstd', '-q', '-d', '-c', str(archive)], stdout=out, check=True)
    if file_digest(partial) != (entry['sha256'], entry['bytes']):
        raise RuntimeError(f'Restored contents incorrect: {partial}; preserve for inspection')
    partial.rename(path)
    print('SHA256-verified original restored:', rel, entry['bytes'], 'bytes')


def verify(index: dict) -> None:
    if not index['files']:
        print('No archived snapshots recorded')
        return
    for rel, entry in sorted(index['files'].items()):
        archive = ROOT / entry['archive']
        assert file_digest(archive) == (entry['archive_sha256'], entry['archive_bytes']), rel
        assert decompressed_digest(archive) == (entry['sha256'], entry['bytes']), rel
    total = sum(x['bytes'] for x in index['files'].values())
    packed = sum(x['archive_bytes'] for x in index['files'].values())
    print(f'Verified {len(index["files"])} independently lossless original snapshots, '
          f'original {total:,} bytes, archived {packed:,} bytes; '
          f'compression saves {total-packed:,} bytes if loose originals absent')


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    group = parser.add_mutually_exclusive_group()
    group.add_argument('--archive', action='store_true', help='hash-verify and archive eligible historical snapshots')
    group.add_argument('--verify', action='store_true', help='independently verify all archived original bytes and SHA256')
    group.add_argument('--restore', metavar='REPOSITORY_RELATIVE_PATH', help='recover one original source snapshot')
    parser.add_argument('--family', choices=('all', 'seed', 'adoption'), default='all')
    args = parser.parse_args()
    os.chdir(ROOT)
    index = load_index()
    if args.restore:
        restore(index, args.restore)
    elif args.verify:
        verify(index)
    else:
        files = [(p, kind) for p, kind in eligible() if args.family in ('all', kind)]
        original = sum(p.stat().st_size for p, _ in files)
        print(f'Eligible historical parent/adoption snapshots: {len(files)}, {original:,} bytes '
              f'({original/1048576:.1f} MiB), family={args.family}; '
              f'already archived={len(index["files"])}')
        if not args.archive:
            print('Dry run only; use --archive to losslessly compact; use --restore PATH to recover')
            return
        saved = 0
        for number, (path, kind) in enumerate(files, 1):
            before, after = safely_archive(path, kind, index)
            saved += before - after
            if number % 10 == 0 or number == len(files):
                print(f'[{number}/{len(files)}] individually SHA256-verified; '
                      f'cumulative {saved/1048576:.1f} MiB recovered')
        verify(index)


if __name__ == '__main__':
    main()
