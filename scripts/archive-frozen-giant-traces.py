#!/usr/bin/env python3
"""Lossless archive of *frozen* giant diagnostic text, never source or CODE.

Scoped strictly to historical `.analysis/{character-move-4ac040,
object-action-50a580}/f133..f166/` generated `.asm/.cod/.log`.
C++/INC/headers/OBJ/PDB/JSON receipts, native PE, VC7.1 Wine, Ghidra,
matching objects, H184 and current research remain loose and untouched.

Archive ALL original byte streams with durable relative paths, original
SHA256 and sizes; stream-verify EVERY member before deleting any loose file.
Archives are local/ignored, NOT included in Git or a fresh clone.

scripts/repo-python scripts/archive-frozen-giant-traces.py --plan
scripts/repo-python scripts/archive-frozen-giant-traces.py --archive
scripts/repo-python scripts/archive-frozen-giant-traces.py --verify
scripts/repo-python scripts/archive-frozen-giant-traces.py --restore .analysis/character-move-4ac040/f154/BaselineMapTrace.cod
scripts/repo-python scripts/archive-frozen-giant-traces.py --recompact-restored .analysis/character-move-4ac040/f154/BaselineMapTrace.cod
"""
from __future__ import annotations
import argparse
from collections import Counter
import hashlib
import io
import json
from pathlib import Path
import re
import subprocess
import sys
import tarfile

ROOT = Path(__file__).resolve().parents[1]
LOCAL = ROOT / '.analysis' / 'cache-archives'
ARCHIVE = LOCAL / 'historical-f133-f166-giant-traces.tar.zst'
INDEX = LOCAL / 'historical-f133-f166-giant-traces-index.json'
FORMAT = 'TH075-FROZEN-GIANT-TEXT-TRACES-SHA256-v1'
ROOTS = ('character-move-4ac040', 'object-action-50a580')
EXTS = ('.asm', '.cod', '.log')


def need(ok: bool, message: str) -> None:
    if not ok:
        raise RuntimeError(message)


def digest(path: Path) -> tuple[int,str]:
    h = hashlib.sha256()
    length = 0
    with path.open('rb') as fp:
        while chunk := fp.read(1 << 20):
            h.update(chunk)
            length += len(chunk)
    return length, h.hexdigest()


def safe_relative(raw: str) -> Path:
    path = Path(raw)
    need(not path.is_absolute() and '..' not in path.parts and '\\' not in raw,
         f'unsafe archive path: {raw}')
    parts = path.parts
    need(len(parts) >= 4 and parts[0] == '.analysis' and parts[1] in ROOTS,
         f'non-allowlisted root: {raw}')
    need(re.fullmatch(r'f\d{3}',parts[2]) is not None
         and 133 <= int(parts[2][1:]) <= 166,
         f'non-historical investigation: {raw}')
    need(path.suffix.lower() in EXTS,
         f'not a frozen, generated ASM/COD/LOG text trace: {raw}')
    # This allowlist is the only source of paths in the archive; no
    # workspace-relative symlinks or suspicious OS path traversals.
    for parent in (ROOT / path).parents:
        if parent == ROOT:
            break
        need(not parent.is_symlink(), f'symlinked parent: {raw}')
    return path


def available() -> list[Path]:
    paths = []
    for basename in ROOTS:
        root = ROOT / '.analysis' / basename
        for d in root.glob('f???'):
            if not d.is_dir() or not (d.name[1:].isdigit() and
                                     133 <= int(d.name[1:]) <= 166):
                continue
            for p in d.rglob('*'):
                if p.is_file() and not p.is_symlink() and p.suffix.lower() in EXTS:
                    safe_relative(p.relative_to(ROOT).as_posix())
                    paths.append(p)
    return sorted(paths)


def load_index() -> dict:
    need(INDEX.is_file() and not INDEX.is_symlink(),
         'archive index missing; refuse to infer original member bytes')
    obj = json.loads(INDEX.read_text())
    need(obj.get('format') == FORMAT and isinstance(obj.get('files'),dict)
         and obj['files'], 'unknown/empty archive index')
    return obj


def verify_archive(index: dict) -> tuple[int,int]:
    need(ARCHIVE.is_file() and not ARCHIVE.is_symlink(), 'actual archive missing')
    size, sha = digest(ARCHIVE)
    need(size == index['archive_bytes'] and sha == index['archive_sha256'],
         'archive size/SHA256 mismatch')
    expected = index['files']
    process = subprocess.Popen(['zstd','-q','-d','-c',str(ARCHIVE)],
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    assert process.stdout is not None
    seen = set()
    total = 0
    try:
        with tarfile.open(fileobj=process.stdout, mode='r|') as tar:
            for member in tar:
                raw = member.name
                safe_relative(raw)
                need(member.isfile() and raw in expected and raw not in seen,
                     f'unexpected/duplicate/nonfile archive member: {raw}')
                stream = tar.extractfile(member)
                need(stream is not None, f'broken member stream {raw}')
                h = hashlib.sha256()
                member_size = 0
                with stream:
                    while block := stream.read(1 << 20):
                        h.update(block)
                        member_size += len(block)
                need(member_size == expected[raw]['bytes']
                     and h.hexdigest() == expected[raw]['sha256'],
                     f'original SHA256/size mismatch in {raw}')
                total += member_size
                seen.add(raw)
        need(seen == set(expected), f'missing {len(set(expected)-seen)} original trace members')
    finally:
        process.stdout.close()
    stderr = process.communicate()[1]
    need(process.returncode == 0, f'zstd archive corrupt: {stderr[-256:]}')
    need(total == index['total_original_bytes'], 'archive total bytes changed')
    return len(seen),total


def archive_files(paths: list[Path]) -> None:
    need(paths, 'no historical generated traces to archive')
    need(not INDEX.exists() and not ARCHIVE.exists(),
         'existing archive/receipt: refusing overwrite or duplicate compaction')
    partial = ARCHIVE.with_name(ARCHIVE.name+'.partial')
    need(not partial.exists(), f'unfinished archive present: {partial}')
    records = {}
    for p in paths:
        rel = p.relative_to(ROOT).as_posix()
        size, sha = digest(p)
        records[rel] = {'bytes':size,'sha256':sha}
    LOCAL.mkdir(parents=True,exist_ok=True)
    with partial.open('wb') as out:
        compressor = subprocess.Popen(['zstd','-q','-8','-T2','-c'],
                                      stdin=subprocess.PIPE,stdout=out,stderr=subprocess.PIPE)
        assert compressor.stdin is not None
        try:
            with tarfile.open(fileobj=compressor.stdin,mode='w|') as tar:
                for p in paths:
                    tar.add(p,arcname=p.relative_to(ROOT).as_posix(),recursive=False)
        finally:
            try: compressor.stdin.close()
            except BrokenPipeError: pass
        error = compressor.stderr.read() if compressor.stderr else b''
        need(compressor.wait() == 0, f'compression failed: {error[-500:]}')
    packed,dsha = digest(partial)
    index = {'format':FORMAT,
             'description':'Local ignored, lossless native giant historical generated ASM/COD/LOG; no C++/OBJ/PDB/JSON/PE touched',
             'archive':ARCHIVE.relative_to(ROOT).as_posix(),
             'archive_bytes':packed,'archive_sha256':dsha,
             'total_original_bytes':sum(x['bytes'] for x in records.values()),
             'file_count':len(records),'files':records}
    # Atomically materialize archive and receipt, then re-read every member
    # of the new archive by SHA256 BEFORE removing even one original file.
    partial.rename(ARCHIVE)
    pending = INDEX.with_suffix('.json.partial')
    need(not pending.exists(), f'unfinished receipt index: {pending}')
    pending.write_text(json.dumps(index,sort_keys=True,indent=2)+'\n')
    pending.rename(INDEX)
    verify_archive(index)
    for p in paths:
        rel = p.relative_to(ROOT).as_posix()
        need(p.is_file() and not p.is_symlink() and
             list(digest(p)) == [records[rel]['bytes'],records[rel]['sha256']],
             f'original generated trace changed while archiving: {rel}')
    # All originals have now been independently hash checked twice.
    for p in paths:
        p.unlink()
    verify_archive(index)
    print(f'Archived and deleted ONLY {len(records)} original generated frozen ASM/COD/LOG traces; '
          f'{index["total_original_bytes"]:,} plain bytes -> {packed:,} archive bytes; '
          f'{index["total_original_bytes"]-packed-INDEX.stat().st_size:,} net bytes reclaimed '
          f'including full per-path receipt. All members SHA256-verified BEFORE and AFTER removal.')


def archived_member(index: dict, raw: str) -> tuple[Path,str]:
    path = safe_relative(raw)
    rel = path.as_posix()
    need(rel in index['files'],f'not an archived source: {rel}')
    return ROOT / path,rel


def restore(index: dict, raw: str) -> None:
    target,rel = archived_member(index,raw)
    verify_archive(index)
    record = index['files'][rel]
    if target.exists():
        need(target.is_file() and not target.is_symlink()
             and list(digest(target)) == [record['bytes'],record['sha256']],
             'target already exists with DIFFERENT/unsafe bytes: refusing overwrite')
        print('Identical archived trace already restored:',rel)
        return
    process = subprocess.Popen(['zstd','-q','-d','-c',str(ARCHIVE)],
                               stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    assert process.stdout is not None
    payload = None
    try:
        with tarfile.open(fileobj=process.stdout,mode='r|') as tar:
            for member in tar:
                if member.name == rel:
                    stream=tar.extractfile(member)
                    need(stream is not None,'original archived source unreadable')
                    with stream:payload=stream.read()
                    break
    finally:
        process.stdout.close()
        process.communicate()
    need(payload is not None and len(payload) == record['bytes']
         and hashlib.sha256(payload).hexdigest() == record['sha256'],
         f'original restored payload SHA256 mismatch: {rel}')
    target.parent.mkdir(parents=True,exist_ok=True)
    with target.open('xb') as fp:
        fp.write(payload)
    need(list(digest(target)) == [record['bytes'],record['sha256']],
         'on-disk restored trace differs from archived original')
    print('Restored SHA256-exact original at:',rel,record['bytes'],'bytes')


def main() -> None:
    ap=argparse.ArgumentParser(description=__doc__)
    actions=ap.add_mutually_exclusive_group(required=True)
    actions.add_argument('--plan',action='store_true')
    actions.add_argument('--archive',action='store_true')
    actions.add_argument('--verify',action='store_true')
    actions.add_argument('--restore',metavar='ORIGINAL_RELATIVE_PATH')
    actions.add_argument('--recompact-restored',metavar='ORIGINAL_RELATIVE_PATH')
    args=ap.parse_args()
    if args.plan:
        paths=available()
        total=sum(p.stat().st_size for p in paths)
        types=Counter(p.suffix for p in paths)
        print(f'Frozen historical generated trace plan: {len(paths):,} loose files, '
              f'{total:,} bytes ({total/2**20:.2f} MiB), by suffix {dict(types)}.')
        print('No C++/INC/OBJ/PDB/JSON/PE/Wine/Ghidra/accepted match inputs in scope.')
        if ARCHIVE.exists() or INDEX.exists():
            print('Archive/receipt already present; subsequent --archive will REFUSE overwrite.')
        return
    if args.archive:
        archive_files(available())
        return
    index=load_index()
    if args.verify:
        count,size=verify_archive(index)
        present=[]
        changed=[]
        for rel,record in index['files'].items():
            path=ROOT/safe_relative(rel)
            if path.exists():
                if not path.is_file() or path.is_symlink() or list(digest(path)) != [record['bytes'],record['sha256']]:
                    changed.append(rel)
                else:present.append(rel)
        print(f'Frozen archive verified: {count:,} original member SHA256s, '
              f'{size:,} original bytes, {index["archive_bytes"]:,} packed bytes; '
              f'{len(present)} restored-identical loose files, '
              f'{len(changed)} newly changed loose copies (not removed).')
        for rel in changed[:8]:print('WARNING: regenerated/changed loose trace, KEEP:',rel)
        return
    if args.restore:
        restore(index,args.restore)
        return
    if args.recompact_restored:
        target,rel=archived_member(index,args.recompact_restored)
        verify_archive(index)
        record=index['files'][rel]
        need(target.is_file() and not target.is_symlink()
             and list(digest(target)) == [record['bytes'],record['sha256']],
             'original restored file changed or absent: REFUSE removal')
        target.unlink()
        print('Removed only SHA256-identical restored loose duplicate:',rel)


if __name__ == '__main__':
    try:main()
    except (RuntimeError, OSError, subprocess.SubprocessError, ValueError, KeyError) as exc:
        print(f'FROZEN TRACE ARCHIVE SAFETY FAILURE: {exc}', file=sys.stderr)
        raise SystemExit(1)
