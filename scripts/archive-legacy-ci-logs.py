#!/usr/bin/env python3
"""Losslessly archive pre-F301 *redundant CI log output* under .analysis.

Only old, Git-ignored F001..F300 paths, filename whose stem has an
independent `ci` token and `.log` suffix, never H184 protected evidence
or toolchains. Uses SHA256 + full archive member read-back + atomic
receipt before deleting ANY originals. Reversible per archived path.
NO source, JSON, PDB, OBJ, test, tracking, target or compiler removal.

  scripts/repo-python scripts/archive-legacy-ci-logs.py --plan
  scripts/repo-python scripts/archive-legacy-ci-logs.py --archive
  scripts/repo-python scripts/archive-legacy-ci-logs.py --verify
  scripts/repo-python scripts/archive-legacy-ci-logs.py --restore .analysis/f179-ci.log

The tar and manifest are PRIVATE ignored local artifacts, not distributed
in Git. Historical old-CI logs are retained byte-for-byte on recovery.
"""
from __future__ import annotations

import argparse
import hashlib
import io
import json
import os
from pathlib import Path
import re
import sys
import tarfile

ROOT=Path(__file__).resolve().parents[1]
ANALYSIS=ROOT/'.analysis'
CACHE=ANALYSIS/'cache-archives'
TAR=CACHE/'legacy-ci-logs-pre-f301.tar.gz'
RECEIPT=CACHE/'legacy-ci-logs-pre-f301-receipt.json'
TEMP=CACHE/'legacy-ci-logs-pre-f301.tar.gz.partial'
TRUSTED_BASE='.analysis/'


def ensure(condition,msg):
    if not condition:raise RuntimeError(msg)


def sha256_bytes(raw:bytes)->str:
    return hashlib.sha256(raw).hexdigest()


def sha256_file(path:Path)->str:
    h=hashlib.sha256()
    with path.open('rb') as f:
        while raw:=f.read(1024*1024):h.update(raw)
    return h.hexdigest()


def eligible(path:Path)->bool:
    if not path.is_file() or path.is_symlink() or path.suffix!='.log':return False
    rel=path.relative_to(ROOT)
    if not str(rel).startswith(TRUSTED_BASE):return False
    if any(x in rel.parts for x in ('vc71-wine','h184-handoff','cache-archives')):return False
    nums=[int(m.group(1)) for part in rel.parts
          if (m:=re.match(r'^f(\d{3})(?:[-_.]|$)',part,re.I))]
    if not nums or max(nums)>300:return False
    return bool(re.search(r'(^|[-_.])ci([-_.]|$)',path.stem,re.I))


def gather()->list[Path]:
    return sorted((p for p in ANALYSIS.rglob('*.log') if eligible(p)),key=str)


def validate_safe_path(path:str)->Path:
    ensure(path.startswith(TRUSTED_BASE) and '\\' not in path,
           'archive path outside analysis')
    rel=Path(path)
    ensure('..' not in rel.parts and rel.parts[0]=='.analysis',
           'unsafe archive member traversal')
    out=ROOT/rel
    ensure(eligible(out) if out.is_file() else
           (out.suffix=='.log' and re.search(r'(^|[-_.])ci([-_.]|$)',out.stem,re.I) is not None
            and not any(x in out.parts for x in ('vc71-wine','h184-handoff'))),
           'refuse restore target other than frozen CI output')
    return out


def read_receipt()->dict:
    ensure(TAR.is_file() and RECEIPT.is_file(),
           'verified historical tar/receipt are missing: nothing to restore')
    receipt=json.loads(RECEIPT.read_text())
    ensure(receipt.get('format')=='TH075-LEGACY-CI-SHA256-v1' and
           receipt.get('archive')==str(TAR.relative_to(ROOT)) and
           receipt.get('archive_sha256')==sha256_file(TAR),
           'verified archive SHA256/receipt mismatch')
    return receipt


def verify()->dict:
    receipt=read_receipt()
    meta=receipt['files']
    ensure(len(meta)==receipt['members'] and len(meta)>0,
           'archive receipt member counts differ')
    found=set();count=0;size=0
    with tarfile.open(TAR,'r:gz') as archive:
        for member in archive:
            ensure(member.isfile() and member.name in meta and member.name not in found,
                   f'unexpected/non-file/duplicate tar member {member.name}')
            safe=validate_safe_path(member.name)
            expected=meta[member.name]
            ensure(member.size==expected['size'],
                   f'archive member size mismatch {member.name}')
            data=archive.extractfile(member)
            ensure(data is not None,f'archive member missing data {member.name}')
            digest=hashlib.sha256()
            received=0
            while chunk:=data.read(1024*1024):
                digest.update(chunk);received+=len(chunk)
            ensure(received==member.size and digest.hexdigest()==expected['sha256'],
                   f'original per-file SHA256 mismatch {member.name}')
            if safe.exists():
                ensure(safe.is_file() and safe.stat().st_size==expected['size']
                       and sha256_file(safe)==expected['sha256'],
                       f'loose original CI log has since changed {member.name}')
            found.add(member.name);count+=1;size+=received
    ensure(found==set(meta) and count==receipt['members'] and
           size==receipt['original_total_bytes'],
           'not all old CI logs were independently read back')
    print(f'Verified {count} original historical CI log members / '
          f'{size:,} original bytes / {TAR.stat().st_size:,} archived bytes; '
          'ALL member SHA256 checks passed.')
    return receipt


def archive()->None:
    ensure(not TAR.exists() and not RECEIPT.exists() and not TEMP.exists(),
           'archive exists or interrupted partial archive; verify/inspect, never overwrite')
    files=gather()
    ensure(files,'no safe old CI logs exist for archival')
    CACHE.mkdir(parents=True,exist_ok=True)
    original_bytes=sum(p.stat().st_size for p in files)
    print(f'Archiving ONLY {len(files)} frozen pre-F301 CI logs '
          f'({original_bytes:,} bytes); preserving every SHA256 and original path.',flush=True)
    records={}
    try:
        with tarfile.open(TEMP,'w:gz',compresslevel=6) as out:
            for path in files:
                name=path.relative_to(ROOT).as_posix()
                ensure(eligible(path),f'candidate no longer safely eligible {name}')
                length=path.stat().st_size
                original_sha=sha256_file(path)
                info=tarfile.TarInfo(name)
                info.size=length
                info.mode=0o644
                info.mtime=0
                info.uid=info.gid=0
                info.uname=info.gname=''
                with path.open('rb') as stream:
                    out.addfile(info,stream)
                ensure(path.stat().st_size==length and sha256_file(path)==original_sha,
                       f'original changed during archival {name}')
                records[name]={'size':length,'sha256':original_sha}
        os.replace(TEMP,TAR)
        doc={'format':'TH075-LEGACY-CI-SHA256-v1',
             'description':'Historical CI output only; original C++ and native evidence left untouched',
             'archive':TAR.relative_to(ROOT).as_posix(),
             'archive_sha256':sha256_file(TAR),
             'members':len(records),
             'original_total_bytes':original_bytes,
             'files':records}
        temp_receipt=RECEIPT.with_suffix('.json.partial')
        with temp_receipt.open('w') as stream:
            json.dump(doc,stream,indent=2,sort_keys=True)
            stream.write('\n');stream.flush();os.fsync(stream.fileno())
        os.replace(temp_receipt,RECEIPT)
        # CRITICAL: full tar SHA and every uncompressed member read back
        # with original files still present BEFORE removing even one.
        verify()
        for path in files:
            ensure(eligible(path) and
                   sha256_file(path)==records[path.relative_to(ROOT).as_posix()]['sha256'],
                   f'original CI changed before deletion {path}')
            path.unlink()
        print(f'Compacted {len(files)} original CI logs: reclaimed '
              f'{original_bytes-TAR.stat().st_size-RECEIPT.stat().st_size:,} '
              'bytes net after verified recoverable tar and receipt.')
    except Exception:
        print('Archive interrupted: NEVER discard original files unless a '
              'fully verified tar+receipt exists.',file=sys.stderr)
        raise


def restore(spec:str)->None:
    desired=validate_safe_path(spec)
    name=desired.relative_to(ROOT).as_posix()
    receipt=verify()
    ensure(name in receipt['files'],f'not a recorded original legacy CI file: {name}')
    expect=receipt['files'][name]
    if desired.exists():
        ensure(sha256_file(desired)==expect['sha256'],
               f'restore would overwrite modified {name}')
        print(f'Already restored unchanged {name}')
        return
    with tarfile.open(TAR,'r:gz') as archive:
        entry=archive.getmember(name)
        file=archive.extractfile(entry)
        ensure(file is not None,'old CI member has no content')
        data=file.read()
    ensure(len(data)==expect['size'] and sha256_bytes(data)==expect['sha256'],
           'recovered historical CI bytes differ')
    desired.parent.mkdir(parents=True,exist_ok=True)
    tmp=desired.with_suffix('.log.restore-partial')
    ensure(not tmp.exists(),f'restored-path partial collision {tmp}')
    with tmp.open('xb') as out:
        out.write(data);out.flush();os.fsync(out.fileno())
    os.replace(tmp,desired)
    ensure(sha256_file(desired)==expect['sha256'],
           'restored path SHA256 differs')
    print(f'Restored exact original {name}: {len(data)} bytes, SHA256 OK.')


def main()->None:
    p=argparse.ArgumentParser(description=__doc__)
    group=p.add_mutually_exclusive_group(required=True)
    group.add_argument('--plan',action='store_true')
    group.add_argument('--archive',action='store_true')
    group.add_argument('--verify',action='store_true')
    group.add_argument('--restore',metavar='ORIGINAL_PATH')
    args=p.parse_args()
    if args.plan:
        files=gather()
        print(f'Eligible frozen CI logs: {len(files)} files / '
              f'{sum(x.stat().st_size for x in files):,} original bytes; '
              f'archive status: {TAR.exists()} receipt status: {RECEIPT.exists()}')
        print('Protected: current F301+ logs, H184, VC71/Wine, '
              'original native PE, Ghidra, src/config/probes, build/*, JSON evidence, PDB/OBJ.')
    elif args.archive:archive()
    elif args.verify:verify()
    elif args.restore:restore(args.restore)


if __name__=='__main__':
    try:main()
    except (RuntimeError,OSError,tarfile.TarError) as exc:
        print(f'Legacy CI archival FAILED safely: {exc}',file=sys.stderr)
        raise SystemExit(1)
