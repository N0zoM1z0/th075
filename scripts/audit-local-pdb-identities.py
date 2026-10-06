#!/usr/bin/env python3
"""Audit named local PDB identities read-only; keep paths and metadata private."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('local_pdb_identity', ROOT / 'scripts/pdb_identity.py')
P = importlib.util.module_from_spec(spec)
spec.loader.exec_module(P)
REFERENCE = ROOT / 'config/sdk-inline-special-member-review-evidence.json'
REFERENCE_SHA256 = '399e138ed205302ab549415671a8ce3d00212b19ee6e84d1b2bd8ebf6259d48d'


def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=False).encode()).hexdigest()


def audit(paths, reference):
    grouped, failures, records = {}, [], []
    for name in paths:
        try:
            path = Path(name)
            stat = path.stat()
            key = (stat.st_dev, stat.st_ino)
            if key not in grouped:
                grouped[key] = dict(path=str(path.resolve()), aliases=[], size=stat.st_size)
            grouped[key]['aliases'].append(name)
        except OSError as exc:
            failures.append(dict(path=name, error=str(exc)))
    for record in grouped.values():
        try:
            before = Path(record['path']).stat()
            record['identity'] = P.read_identity(record['path'], allow_trailing=True)
            after = Path(record['path']).stat()
            if (before.st_dev, before.st_ino, before.st_size, before.st_mtime_ns) != (
                    after.st_dev, after.st_ino, after.st_size, after.st_mtime_ns):
                raise ValueError('candidate changed during identity read')
            record['status'] = 'match' if P.matches(record['identity'], reference) else 'parsed-nonmatch'
        except P.UnsupportedPDB as exc:
            record['status'], record['error'] = 'unsupported', str(exc)
        except (OSError, ValueError) as exc:
            record['status'], record['error'] = 'unparsed', str(exc)
        records.append(record)
    # Preserve multiplicity, but publish neither filenames nor private root paths.
    witnesses = sorted(metadata_digest({k: v for k, v in r.items() if k not in ['path', 'aliases']}) for r in records)
    summary = dict(path_count=len(paths), unique_physical_files=len(records),
                   enumeration_errors=len(failures), statuses=dict(sorted(Counter(r['status'] for r in records).items())),
                   formats=dict(sorted(Counter(r['identity']['format'] for r in records if 'identity' in r).items())),
                   msf_trailing_extents=sum(not r.get('identity', {}).get('file_extent_equal', True) for r in records),
                   identity_witnesses_sha256=metadata_digest(witnesses))
    return dict(summary=summary, enumeration_errors=failures, records=records)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, action='append', required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    output = args.output.resolve()
    if not output.is_relative_to(ROOT / '.analysis'):
        raise ValueError('identity reports must remain under private .analysis/')
    if hashlib.sha256(REFERENCE.read_bytes()).hexdigest() != REFERENCE_SHA256:
        raise ValueError('frozen R266 target reference differs')
    plan = json.loads(REFERENCE.read_text())
    spec = importlib.util.spec_from_file_location('pdb_original_reference', ROOT / 'scripts/verify-sdk-inline-special-member-review.py')
    prior = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(prior)
    target = prior.V.C.verified_target()
    reference = prior.target_symbol_reference(target)
    if reference != plan['target_symbol_reference']:
        raise ValueError('whole actual RSDS/RVA/file witness differs')
    command = ['rg', '--files', '-uuu', '-g', '*.[pP][dD][bB]', '--', *[str(p.resolve()) for p in args.root]]
    result = subprocess.run(command, capture_output=True, check=False)
    if result.returncode not in [0, 1] or result.stderr:
        raise ValueError('rg enumeration failed; no absence conclusion is permitted')
    paths = sorted(result.stdout.decode('utf-8').splitlines())
    report = audit(paths, reference)
    report.update(roots=[str(p.resolve()) for p in args.root], glob='*.[pP][dD][bB]',
                  follow_directory_symlinks=False, target_reference=reference,
                  path_inventory_sha256=metadata_digest(paths),
                  limitation='Named local files only; no recursive archive/content search or full PDB validity, source, origin or exact credit. Errors remain coverage gaps.')
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n')
    print(json.dumps(report['summary'], sort_keys=True))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
