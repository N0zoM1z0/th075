#!/usr/bin/env python3
"""F694: reversible, SHA256-indexed compaction of two frozen generated cohorts.

Only these two intentionally narrow classes of Git-ignored files:
  * `.analysis/f500-*` ... `.analysis/f649-*` compiler `.pdb` outputs,
    EXCEPT the currently significant F593/F596 whole-boss source proofs;
  * `.analysis/r001-...-ci*.log` ... `r259-...-ci*.log` root CI output,
    EXCEPT R260+ accepted/checkpoint CI and all non-CI native evidence.

No original PE, source, CPP/INC/ASM, CODE/COFF OBJ, JSON diagnostic,
active F650+ evidence, accepted build, H184, Git, Wine or Ghidra file is
eligible. Each archive is only local/ignored; new clones won't contain it.
Write both tar and atomic per-file SHA256 receipt, then STREAM-VERIFY EVERY
original tar member against the still-present original before unlinking a
single loose copy. Retain the tar indefinitely unless separately backed up.

  scripts/repo-python scripts/archive-redundant-native-research.py --family pdb --plan
  scripts/repo-python scripts/archive-redundant-native-research.py --family logs --plan
  scripts/repo-python scripts/archive-redundant-native-research.py --family pdb --archive
  scripts/repo-python scripts/archive-redundant-native-research.py --family logs --verify
  scripts/repo-python scripts/archive-redundant-native-research.py --family pdb --restore .analysis/f612-scene-types/voidptr.pdb
  scripts/repo-python scripts/archive-redundant-native-research.py --family pdb --recompact-restored .analysis/f612-scene-types/voidptr.pdb
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import sys
import tarfile

ROOT = Path(__file__).resolve().parents[1]
ANALYSIS = ROOT / '.analysis'
CACHE = ANALYSIS / 'cache-archives'
FORMAT = 'TH075-F694-FROZEN-RESEARCH-CACHE-SHA256-v1'
NAMES = {
    'pdb': 'f500-f649-unprotected-probe-pdb-2026-10-30',
    'logs': 'r001-r259-legacy-ci-output-2026-10-30',
}
PDB_EXCLUDED = {'f593-characterobject-whole-source',
                'f596-characterobject-native-collision-source'}
PROTECTED_DIRS = {'h184-handoff', 'cache-archives', 'vc71-wine',
                  'ghidra', 'origin-scan'}


def ensure(ok: bool, reason: str) -> None:
    if not ok:
        raise RuntimeError(reason)


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open('rb') as stream:
        while data := stream.read(1024 * 1024):
            h.update(data)
    return h.hexdigest()


def locations(family: str) -> tuple[Path, Path, Path]:
    ensure(family in NAMES, 'unsupported source preservation family')
    name = NAMES[family]
    return (CACHE / (name + '.tar.gz'), CACHE / (name + '-receipt.json'),
            CACHE / (name + '.tar.gz.partial'))


def eligible_relative(path: str, family: str) -> bool:
    rel = Path(path)
    if ('\\' in path or not path.startswith('.analysis/') or
            '..' in rel.parts or rel.is_absolute() or
            not rel.parts or rel.parts[0] != '.analysis' or
            any(x in PROTECTED_DIRS for x in rel.parts)):
        return False
    parts = rel.parts[1:]
    if family == 'pdb':
        if len(parts) < 2 or rel.suffix.lower() != '.pdb':
            return False
        match = re.fullmatch(r'f(\d{3})[-_].+', parts[0], re.I)
        return bool(match and 500 <= int(match.group(1)) <= 649
                    and parts[0] not in PDB_EXCLUDED)
    if family == 'logs':
        if len(parts) != 1 or rel.suffix.lower() != '.log':
            return False
        match = re.fullmatch(r'r(\d{1,3})[-_].+', parts[0], re.I)
        return bool(match and 1 <= int(match.group(1)) <= 259
                    and re.search(r'(^|[-_.])ci(?=[-_.]|$)', rel.stem, re.I))
    return False


def safe_file(path: str, family: str) -> Path:
    ensure(eligible_relative(path, family),
           f'refusing path outside narrow {family} archival allowlist: {path}')
    target = ROOT / path
    # No symlinks anywhere in a target path, even on restore where the leaf
    # need not exist yet. Protect the sole real worktree from redirection.
    parent = ROOT
    for part in Path(path).parts:
        parent = parent / part
        ensure(not parent.is_symlink(), f'symlink not allowed: {parent}')
    return target


def gather(family: str) -> list[Path]:
    if family == 'pdb':
        candidates = []
        for folder in ANALYSIS.iterdir():
            if not folder.is_dir() or folder.is_symlink():
                continue
            if not re.fullmatch(r'f\d{3}[-_].+', folder.name, re.I):
                continue
            candidates.extend(folder.rglob('*.pdb'))
    else:
        candidates = ANALYSIS.glob('r*.log')
    safe = []
    for file in candidates:
        relative = file.relative_to(ROOT).as_posix()
        if eligible_relative(relative, family) and file.is_file() and not file.is_symlink():
            safe_file(relative, family)
            safe.append(file)
    return sorted(safe, key=lambda f: f.relative_to(ROOT).as_posix())


def read_receipt(family: str) -> dict:
    archive, receipt, _ = locations(family)
    ensure(archive.is_file() and receipt.is_file(),
           'missing local archive or receipt; it is not stored in Git')
    document = json.loads(receipt.read_text())
    ensure(document.get('format') == FORMAT and
           document.get('family') == family and
           document.get('archive') == archive.relative_to(ROOT).as_posix() and
           document.get('archive_sha256') == sha256(archive),
           'local archive digest or receipt identity mismatch')
    ensure(document.get('members') == len(document.get('files', {})) and
           document['members'] > 0,
           'empty/broken archive file-index count')
    return document


def verify(family: str, *, report: bool = True) -> dict:
    archive, _, _ = locations(family)
    receipt = read_receipt(family)
    originals = receipt['files']
    seen: set[str] = set()
    total = 0
    with tarfile.open(archive, 'r:gz') as tar:
        for member in tar:
            name = member.name
            ensure(member.isfile() and name in originals and name not in seen,
                   f'invalid or duplicate archive entry: {name}')
            existing = safe_file(name, family)
            info = originals[name]
            ensure(member.size == info['size'],
                   f'tar/original size mismatch: {name}')
            stream = tar.extractfile(member)
            ensure(stream is not None, f'missing archive bytes: {name}')
            h = hashlib.sha256()
            length = 0
            while block := stream.read(1024 * 1024):
                h.update(block)
                length += len(block)
            ensure(length == info['size'] and h.hexdigest() == info['sha256'],
                   f'tar/original SHA256 mismatch: {name}')
            if existing.exists():
                ensure(existing.is_file() and existing.stat().st_size == length and
                       sha256(existing) == info['sha256'],
                       f'loose file has been modified: {name}')
            seen.add(name)
            total += length
    ensure(seen == set(originals) and total == receipt['original_total_bytes'],
           'not every original file was read and hashed from archive')
    if report:
        print(f'F694 {family}: verified {len(seen)} original files, '
              f'{total:,} uncompressed bytes, {archive.stat().st_size:,} '
              'archive bytes; 100% member SHA256 correct.', flush=True)
    return receipt


def archive_selected(family: str) -> None:
    tar, receipt, tmp = locations(family)
    ensure(not tar.exists() and not receipt.exists() and not tmp.exists(),
           'archive/receipt/partial exists: verify/inspect, never overwrite')
    files = gather(family)
    ensure(files, 'no currently eligible files; nothing to compact')
    originals_bytes = sum(p.stat().st_size for p in files)
    print(f'F694 {family}: preserving {len(files)} originals '
          f'({originals_bytes:,} bytes) losslessly before removing any.',
          flush=True)
    CACHE.mkdir(parents=True, exist_ok=True)
    records: dict[str, dict] = {}
    try:
        with tarfile.open(tmp, 'w:gz', compresslevel=6) as out:
            for file in files:
                name = file.relative_to(ROOT).as_posix()
                ensure(safe_file(name, family) == file and file.is_file(),
                       f'candidate path changed: {name}')
                size = file.stat().st_size
                digest = sha256(file)
                item = tarfile.TarInfo(name)
                item.size = size
                item.mode = 0o644
                item.mtime = 0
                item.uid = item.gid = 0
                item.uname = item.gname = ''
                with file.open('rb') as body:
                    out.addfile(item, body)
                ensure(file.stat().st_size == size and sha256(file) == digest,
                       f'candidate modified while archiving: {name}')
                records[name] = {'size': size, 'sha256': digest}
        os.replace(tmp, tar)
        index = {'format': FORMAT, 'family': family,
                 'description': 'Private ignored lossless original generated-file archive; no source/OBJ/target deletion',
                 'archive': tar.relative_to(ROOT).as_posix(),
                 'archive_sha256': sha256(tar),
                 'members': len(records),
                 'original_total_bytes': originals_bytes,
                 'files': records}
        receipt_tmp = receipt.with_suffix('.json.partial')
        with receipt_tmp.open('x') as out:
            json.dump(index, out, sort_keys=True, indent=2)
            out.write('\n')
            out.flush()
            os.fsync(out.fileno())
        os.replace(receipt_tmp, receipt)
        # Critical: test every exact member while every loose original still
        # exists. A failure leaves the originals untouched for recovery.
        verify(family)
        for file in files:
            name = file.relative_to(ROOT).as_posix()
            ensure(safe_file(name, family).is_file() and
                   sha256(file) == records[name]['sha256'],
                   f'original changed before unlink: {name}')
            file.unlink()
        verify(family)
        gain = originals_bytes - tar.stat().st_size - receipt.stat().st_size
        print(f'F694 {family}: reclaimed {gain:,} bytes NET after '
              'complete pre/post SHA256 validation; restore supported.',
              flush=True)
    except Exception:
        print('Interrupted: keep any original files and archive/receipt; '
              'never discard a failed or partial artifact blindly.',
              file=sys.stderr)
        raise


def restore_or_recompact(family: str, name: str, *, recompact: bool) -> None:
    path = safe_file(name, family)
    index = verify(family)
    ensure(name in index['files'], 'path not present in authenticated receipt')
    info = index['files'][name]
    if recompact:
        ensure(path.is_file() and path.stat().st_size == info['size'] and
               sha256(path) == info['sha256'],
               'refusing to remove a modified or absent restored file')
        path.unlink()
        print(f'F694 {family}: removed only unchanged restored copy {name}; '
              'original bytes remain SHA256-indexed in archive.')
        return
    if path.exists():
        ensure(path.is_file() and sha256(path) == info['sha256'],
               'refusing overwrite of changed file')
        print(f'F694 {family}: already restored unchanged {name}')
        return
    tar, _, _ = locations(family)
    with tarfile.open(tar, 'r:gz') as arc:
        member = arc.getmember(name)
        body = arc.extractfile(member)
        ensure(body is not None, 'archive member missing its byte stream')
        content = body.read()
    ensure(len(content) == info['size'] and
           hashlib.sha256(content).hexdigest() == info['sha256'],
           'restored member did not match original receipt')
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(path.suffix + '.restore-partial')
    with tmp.open('xb') as out:
        out.write(content)
        out.flush()
        os.fsync(out.fileno())
    os.replace(tmp, path)
    ensure(sha256(path) == info['sha256'], 'restored loose file hash mismatch')
    print(f'F694 {family}: restored exact original {name} '
          f'({info["size"]:,} bytes, SHA256 verified).')


def main() -> None:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--family', choices=sorted(NAMES), required=True)
    group = p.add_mutually_exclusive_group(required=True)
    group.add_argument('--plan', action='store_true')
    group.add_argument('--archive', action='store_true')
    group.add_argument('--verify', action='store_true')
    group.add_argument('--restore', metavar='ORIGINAL_RELPATH')
    group.add_argument('--recompact-restored', metavar='ORIGINAL_RELPATH')
    args = p.parse_args()
    if args.plan:
        files = gather(args.family)
        size = sum(x.stat().st_size for x in files)
        tar, receipt, _ = locations(args.family)
        print(f'F694 {args.family}: {len(files)} safely eligible loose files, '
              f'{size:,} bytes; archive present={tar.exists()} receipt={receipt.exists()}')
        print('Never compact sources, CODE/COFF objects, EH/native data, '
              'H184, Wine/VC7.1, Ghidra, F650+ PDB, R260+ CI, '
              'accepted match build, or original executable.')
    elif args.archive:
        archive_selected(args.family)
    elif args.verify:
        verify(args.family)
    elif args.restore:
        restore_or_recompact(args.family, args.restore, recompact=False)
    else:
        restore_or_recompact(args.family, args.recompact_restored, recompact=True)


if __name__ == '__main__':
    try:
        main()
    except (RuntimeError, OSError, tarfile.TarError, ValueError) as exc:
        print(f'F694 safe archival FAILED: {exc}', file=sys.stderr)
        sys.exit(1)
