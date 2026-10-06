"""Cold-replay immutable origin proofs in their actual historical Git states.

VC7 debug AUX indexes depend on the source path length. Historical roots keep
that length. Hash-pinned CSV CRLF representations are restored only when their
normalized bytes equal the historical Git blob; no ledger content is projected.
"""
import hashlib
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def digest(body):
    return hashlib.sha256(body).hexdigest()


def run(args, root=ROOT):
    result = subprocess.run(args, cwd=root, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('Historical command failed: ' + result.stdout[-2000:] + result.stderr[-2000:])
    return result.stdout


def pins(root):
    result = {}
    for path in (root / 'config').glob('*.json'):
        document = json.loads(path.read_text())
        value = document.get('retained_sha256', {}) if isinstance(document, dict) else {}
        if isinstance(value, dict):
            for name, sha in value.items():
                if isinstance(sha, str):
                    result.setdefault(name, set()).add(sha)
    return result


def tracked(root, commit):
    listing = subprocess.check_output(['git', 'ls-tree', '-rz', commit], cwd=root)
    records = []
    for entry in listing.split(b'\0'):
        if not entry:
            continue
        header, filename = entry.split(b'\t', 1)
        mode, kind, sha = header.decode().split()
        if kind != 'blob' or mode not in ['100644', '100755']:
            raise ValueError('Historical tree has unsupported tracked storage')
        records.append((filename.decode(), sha))
    request = ''.join(sha + '\n' for _, sha in records).encode()
    raw = subprocess.check_output(['git', 'cat-file', '--batch'], input=request, cwd=root)
    offset = 0
    result = []
    for filename, sha in records:
        end = raw.index(b'\n', offset)
        actual, kind, size = raw[offset:end].decode().split()
        if actual != sha or kind != 'blob':
            raise ValueError('Historical Git blob identity differs')
        size = int(size)
        result.append((filename, raw[end + 1:end + 1 + size]))
        offset = end + size + 2
    if offset != len(raw):
        raise ValueError('Historical Git object stream is incomplete')
    return result


def check_representation(name, body, blob, pinned):
    if body == blob:
        return
    if (not name.endswith('.csv') or digest(body) not in pinned.get(name, set())
            or body.replace(b'\r\n', b'\n') != blob.replace(b'\r\n', b'\n')):
        raise ValueError('Historical tracked content differs: ' + name)


def prepare(item):
    name = item['root_name']
    if Path(name).name != name or name in ['.', '..']:
        raise ValueError('Historical root must be a bounded sibling directory')
    root = ROOT.parent / name
    if len(str(root)) != item['source_root_characters'] or len(str(ROOT)) != len(str(root)):
        raise ValueError('Historical VC7 source path/AUX reproducibility setting differs')
    commit = item['commit']
    if not root.exists():
        run(['git', 'worktree', 'add', '--detach', str(root), commit])
    if run(['git', 'rev-parse', 'HEAD'], root).strip() != commit:
        raise ValueError('Historical root has a different Git revision')
    pinned = pins(root)
    records = tracked(root, commit)
    for filename, blob in records:
        path = root / filename
        if path.is_symlink():
            raise ValueError('Historical tracked input became a symlink')
        body = path.read_bytes()
        check_representation(filename, body, blob, pinned)
        # Only a pin present in the actual historical manifest permits an EOL
        # restoration. Code, JSON, extent and semantic CSV bytes stay untouched.
        if filename.endswith('.csv') and filename in pinned and digest(body) not in pinned[filename]:
            candidates = [body.replace(b'\r\n', b'\n'),
                          body.replace(b'\r\n', b'\n').replace(b'\n', b'\r\n')]
            matching = [b for b in candidates if digest(b) in pinned[filename]]
            if matching:
                path.chmod(path.stat().st_mode | 0o200)
                path.write_bytes(matching[0])
                check_representation(filename, matching[0], blob, pinned)
        path.chmod(path.stat().st_mode & ~0o222)
    for filename, expected in item['input_sha256'].items():
        if digest((root / filename).read_bytes()) != expected:
            raise ValueError('Historical original proof input differs: ' + filename)
    for path, actual in [(root / '.tools', ROOT / '.tools'),
                         (root / 'resources/th075.exe', ROOT / 'resources/th075.exe')]:
        if path.exists() or path.is_symlink():
            if not path.is_symlink() or path.resolve() != actual.resolve():
                raise ValueError('Historical private tool/target link differs')
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.symlink_to(actual.resolve(), target_is_directory=actual.is_dir())
    return root


def replay(item):
    root = prepare(item)
    for probe in item['cold_prerequisites']:
        run([str(root / 'scripts/compile-probe.sh'), str(root / probe['source']),
             str(root / probe['object']), *probe['profile']], root)
    print('Cold historical ' + item['evidence_id'] + ' at ' + item['commit'] + '.', flush=True)
    output = run([str(root / 'scripts/repo-python'), str(root / item['verifier'])], root)
    # Check the entire tree again: the unchanged legacy verifier must never
    # rewrite its historical source, ledgers, acceptance predicates or manifest.
    pinned = pins(root)
    for filename, blob in tracked(root, item['commit']):
        check_representation(filename, (root / filename).read_bytes(), blob, pinned)
    print(output.strip(), flush=True)
