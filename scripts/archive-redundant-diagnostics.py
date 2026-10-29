#!/usr/bin/env python3
"""Losslessly compact *frozen, repetitive* old ignored diagnostic JSON.

Deliberately excludes every source, OBJ/PDB, Wine/Ghidra/runtime,
original EXE, accepted manifest, new F-series research and live
.analysis/origin-scan/latest.json. Four narrowly allowlisted batches
only. Archive/receipt are ignored and machine-local, but restoration
logic is tracked. Every tar member is SHA256 checked *before* removing
loose copies. This is NOT a license to remove original game evidence.

scripts/repo-python scripts/archive-redundant-diagnostics.py --plan
scripts/repo-python scripts/archive-redundant-diagnostics.py --archive
scripts/repo-python scripts/archive-redundant-diagnostics.py --verify
scripts/repo-python scripts/archive-redundant-diagnostics.py --restore .analysis/origin-scan/r160-triage.json
scripts/repo-python scripts/archive-redundant-diagnostics.py --recompact-restored .analysis/origin-scan/r160-triage.json
"""
from __future__ import annotations
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tarfile

ROOT = Path(__file__).resolve().parents[1]
ANALYSIS = ROOT / '.analysis'
CACHE = ANALYSIS / 'cache-archives'
INDEX = CACHE / 'frozen-repeated-diagnostics-index.json'
FORM = 'TH075-FROZEN-REPEATED-DIAGNOSTICS-SHA256-v1'
FAMILIES = (
    'historical-origin-triage',
    'historical-50a580-whole-diagnostics',
    'historical-4ac040-whole-diagnostics',
    'historical-r-surveys',
)


def ensure(condition: bool, reason: str) -> None:
    if not condition:
        raise RuntimeError(reason)


def checksum(path: Path) -> tuple[int, str]:
    digest = hashlib.sha256()
    total = 0
    with path.open('rb') as f:
        while block := f.read(1024 * 1024):
            digest.update(block)
            total += len(block)
    return total, digest.hexdigest()


def archive_path(family: str) -> Path:
    ensure(family in FAMILIES, f'Not an approved archive family: {family}')
    return CACHE / f'frozen-repeat-{family}.tar.zst'


def allowed(path: Path, family: str) -> bool:
    if not path.is_file() or path.is_symlink() or path.suffix != '.json':
        return False
    try:
        relative = path.relative_to(ROOT)
    except ValueError:
        return False
    parts = relative.parts
    if not parts or parts[0] != '.analysis' or 'cache-archives' in parts:
        return False
    if family == 'historical-origin-triage':
        return len(parts) == 3 and parts[1] == 'origin-scan' and bool(
            re.fullmatch(r'r\d{3}-(triage|before-acceptance)\.json', path.name))
    if family in ('historical-50a580-whole-diagnostics',
                  'historical-4ac040-whole-diagnostics'):
        root = ('object-action-50a580' if family.startswith('historical-50a580')
                else 'character-move-4ac040')
        return len(parts) == 4 and parts[1] == root and bool(
            re.fullmatch(r'f\d{3}', parts[2])) and path.name.endswith('-whole-diagnostic.json')
    if family == 'historical-r-surveys':
        match = re.fullmatch(r'r(\d{3})-.+\.json', path.name)
        return (len(parts) == 2 and match is not None and int(match.group(1)) <= 270
                and path.stat().st_size > 1_000_000)
    return False


def files_for(family: str) -> list[Path]:
    if family == 'historical-origin-triage':
        candidates = (ANALYSIS / 'origin-scan').glob('r*.json')
    elif family == 'historical-50a580-whole-diagnostics':
        candidates = (ANALYSIS / 'object-action-50a580').glob('f???/*-whole-diagnostic.json')
    elif family == 'historical-4ac040-whole-diagnostics':
        candidates = (ANALYSIS / 'character-move-4ac040').glob('f???/*-whole-diagnostic.json')
    elif family == 'historical-r-surveys':
        candidates = ANALYSIS.glob('r???-*.json')
    else:
        raise RuntimeError(f'Invalid family {family}')
    return sorted((p for p in candidates if allowed(p, family)), key=str)


def checked_relative(relative: str) -> Path:
    p = Path(relative)
    ensure(not p.is_absolute() and '..' not in p.parts and '\\' not in relative
           and p.parts and p.parts[0] == '.analysis',
           f'Unsafe original diagnostic path {relative!r}')
    return ROOT / p


def save_index(index: dict) -> None:
    CACHE.mkdir(parents=True, exist_ok=True)
    temp = INDEX.with_name(INDEX.name + '.atomic')
    ensure(not temp.exists(), f'Existing unfinished archive receipt: {temp}')
    temp.write_text(json.dumps(index,indent=2,sort_keys=True) + '\n')
    temp.replace(INDEX)


def read_index() -> dict:
    if not INDEX.exists():
        return {'format': FORM,
                'description': 'Ignored machine-local SHA256-recoverable frozen repetitive historical diagnostics',
                'groups': {}}
    raw = json.loads(INDEX.read_text())
    ensure(raw.get('format') == FORM and isinstance(raw.get('groups'), dict),
           'Unrecognized existing cache archive manifest; do not overwrite')
    return raw


def verify_group(family: str, entry: dict) -> tuple[int, int]:
    archive = archive_path(family)
    ensure(archive.is_file() and not archive.is_symlink(),
           f'Historical archived diagnostic evidence is missing: {archive}')
    ensure(list(checksum(archive)) == [entry['archive_bytes'], entry['archive_sha256']],
           f'Archive data or SHA256 receipt changed: {archive}')
    expected = entry['files']
    ensure(expected and all(isinstance(x,dict) for x in expected.values()),
           f'Missing original per-file receipts for {family}')
    cmd = subprocess.Popen(['zstd','-q','-d','-c',str(archive)],
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    assert cmd.stdout is not None
    seen = set()
    try:
        with tarfile.open(fileobj=cmd.stdout,mode='r|') as tar:
            for member in tar:
                rel = member.name
                ensure(member.isfile() and rel in expected and rel not in seen,
                       f'Unexpected/duplicate/nonfile tar member {rel!r}: {family}')
                ensure(checked_relative(rel).is_relative_to(ANALYSIS),
                       f'Unsafe archive path: {rel}')
                payload = tar.extractfile(member)
                ensure(payload is not None, f'Cannot read original member {rel}')
                digest = hashlib.sha256()
                size = 0
                with payload:
                    while chunk := payload.read(1024*1024):
                        digest.update(chunk)
                        size += len(chunk)
                ensure(size == expected[rel]['bytes']
                       and digest.hexdigest() == expected[rel]['sha256'],
                       f'Original native diagnostic bytes/sha256 FAILED: {rel}')
                seen.add(rel)
        ensure(seen == set(expected), f'Archive missing {len(set(expected)-seen)} original members: {family}')
    finally:
        cmd.stdout.close()
    stderr = cmd.communicate()[1]
    ensure(cmd.returncode == 0, f'Broken zstd stream in {family}: {stderr[-250:]}')
    return sum(x['bytes'] for x in expected.values()), entry['archive_bytes']


def write_group(family: str, paths: list[Path], index: dict) -> dict:
    ensure(family not in index['groups'], 'Do not overwrite an existing verified archive')
    archive = archive_path(family)
    partial = archive.with_name(archive.name + '.partial')
    ensure(not archive.exists() and not partial.exists(),
           f'Unpaired archive or prior partial exists; inspect without overwrite: {archive}')
    ensure(paths, f'No eligible historical frozen diagnostics for {family}')
    receipts = {}
    for p in paths:
        rel = p.relative_to(ROOT).as_posix()
        size,digest = checksum(p)
        receipts[rel] = {'bytes':size,'sha256':digest}
    CACHE.mkdir(parents=True,exist_ok=True)
    with partial.open('wb') as out:
        proc = subprocess.Popen(['zstd','-q','-6','-T2','-c'],
                                stdin=subprocess.PIPE, stdout=out, stderr=subprocess.PIPE)
        assert proc.stdin is not None
        with tarfile.open(fileobj=proc.stdin,mode='w|') as tar:
            for path in paths:
                arc = path.relative_to(ROOT).as_posix()
                ensure(allowed(path,family), f'Eligibility changed while archiving {path}')
                info = tar.gettarinfo(str(path),arcname=arc)
                info.uid=info.gid=0
                info.uname=info.gname=''
                info.mtime=0
                with path.open('rb') as source:
                    tar.addfile(info,source)
        proc.stdin.close()
        stderr=proc.stderr.read() if proc.stderr else b''
        ensure(proc.wait()==0,f'Compressor failed, original files preserved: {stderr[-400:]}')
    size,digest=checksum(partial)
    partial.rename(archive)
    entry={'archive_bytes':size,'archive_sha256':digest,'files':receipts}
    # Independently extract and compare EVERY original SHA256 first.
    verify_group(family,entry)
    index['groups'][family]=entry
    save_index(index)  # durable receipt BEFORE any original removed
    return entry


def recompact(family: str, entry: dict) -> int:
    verify_group(family,entry)  # archive must be independently intact
    total=0
    for rel,meta in entry['files'].items():
        path=checked_relative(rel)
        if not path.exists():continue
        ensure(allowed(path,family), f'Historical original no longer eligible: {rel}')
        ensure(list(checksum(path)) == [meta['bytes'],meta['sha256']],
               f'Original loose evidence CHANGED since archive: {rel}. Preserve it.')
        path.unlink()
        total+=meta['bytes']
    return total


def restore(index: dict, rel: str) -> None:
    path=checked_relative(rel)
    group=next(((name,data) for name,data in index['groups'].items()
                if rel in data['files']),None)
    ensure(group is not None, f'No verified archived original file receipt: {rel}')
    family,entry=group
    ensure(allowed_or_receipted(path,family,entry), f'Refuse unexpected restore target {rel}')
    verify_group(family,entry)
    expected=entry['files'][rel]
    if path.exists():
        ensure(list(checksum(path))==[expected['bytes'],expected['sha256']],
               f'Existing original differs, preserve without overwrite: {rel}')
        print('Original already verified/restored:', rel)
        return
    partial=path.with_name(path.name+'.restore-partial')
    ensure(not partial.exists(), f'Existing restore partial; inspect manually: {partial}')
    path.parent.mkdir(parents=True,exist_ok=True)
    proc=subprocess.Popen(['zstd','-q','-d','-c',str(archive_path(family))],stdout=subprocess.PIPE)
    assert proc.stdout is not None
    found=False
    with tarfile.open(fileobj=proc.stdout, mode='r|') as tar:
        for member in tar:
            if member.name != rel:continue
            ensure(not found and member.isfile(),f'Duplicate/unexpected member {rel}')
            src=tar.extractfile(member)
            ensure(src is not None,f'Cannot extract original {rel}')
            with partial.open('wb') as target,src:
                while chunk:=src.read(1024*1024):target.write(chunk)
            found=True
    proc.stdout.close()
    ensure(proc.wait()==0 and found, f'Failed to decompress original {rel}')
    ensure(list(checksum(partial)) == [expected['bytes'],expected['sha256']],
           f'Restored original SHA256 mismatch: {partial}; preserve for inspection')
    partial.rename(path)
    print(f'SHA256-verified historical original restored: {rel} ({expected["bytes"]:,} bytes)')


def allowed_or_receipted(path: Path, family: str, entry: dict) -> bool:
    return path.relative_to(ROOT).as_posix() in entry['files'] and (
        allowed(path,family) if path.exists() else path.parent.is_dir())


def main() -> None:
    parser=argparse.ArgumentParser(description=__doc__)
    actions=parser.add_mutually_exclusive_group()
    actions.add_argument('--plan',action='store_true')
    actions.add_argument('--archive',action='store_true')
    actions.add_argument('--verify',action='store_true')
    actions.add_argument('--restore',metavar='ORIGINAL_RELATIVE_PATH')
    actions.add_argument('--recompact-restored',metavar='ORIGINAL_RELATIVE_PATH')
    args=parser.parse_args()
    os.chdir(ROOT)
    index=read_index()
    if args.verify:
        total=packed=0
        for family,entry in sorted(index['groups'].items()):
            a,b=verify_group(family,entry)
            total+=a;packed+=b
            print(f'Verified {family}: {len(entry["files"])} original SHA256s, {a:,}→{b:,} bytes')
        print(f'All {sum(len(g["files"]) for g in index["groups"].values())} archived original members verified; '
              f'{total:,}→{packed:,} bytes, {total-packed:,} bytes storage reclaimed (excludes manifest)')
        return
    if args.restore:
        restore(index,args.restore)
        return
    if args.recompact_restored:
        rel=args.recompact_restored
        group=next(((n,x) for n,x in index['groups'].items() if rel in x['files']),None)
        ensure(group is not None, f'No archived receipt for {rel}')
        n,entry=group;archive=archive_path(n)
        ensure(list(checksum(archive))==[entry['archive_bytes'],entry['archive_sha256']],
               f'Archived evidence missing before recompact: {archive}')
        path=checked_relative(rel)
        ensure(path.exists() and list(checksum(path))==[
            entry['files'][rel]['bytes'],entry['files'][rel]['sha256']],
               f'Original restored bytes differ or missing: {rel}')
        path.unlink()
        print('Exact restored duplicate safely re-compacted (archive preserved):',rel)
        return
    total=0
    for family in FAMILIES:
        loose=files_for(family)
        original=sum(p.stat().st_size for p in loose)
        old=index['groups'].get(family)
        recorded=len(old['files']) if old else 0
        print(f'{family}: loose {len(loose)} files / {original:,} bytes; archived {recorded} files')
        total+=original
        if not args.archive:continue
        if old is None:
            if not loose:continue
            old=write_group(family,loose,index)
        deleted=recompact(family,old)
        print(f'{family}: verified archived {len(old["files"])} SHA256s, '
              f'freed {deleted:,} original loose bytes, archive {old["archive_bytes"]:,} bytes')
    if args.archive:
        print('Archive operation complete; run --verify, then test --restore one member.')
    else:
        print(f'Dry run ONLY: {total:,} loose bytes ({total/1048576:.1f} MiB). '
              'Use --archive for verified recoverable compaction.')


if __name__=='__main__':
    try:main()
    except (OSError,RuntimeError,ValueError,tarfile.TarError,KeyError) as error:
        print('SAFE FROZEN DIAGNOSTIC ARCHIVE ABORTED:',error,file=sys.stderr)
        raise SystemExit(1)
