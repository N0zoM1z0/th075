#!/usr/bin/env python3
"""Replay complete public/ordinary getters while preserving opaque leaf origin."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    s = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    v = importlib.util.module_from_spec(s); s.loader.exec_module(v); return v


BASE = module('leaf_vector_at', 'verify-vector-at-policy-origins.py')
digest = BASE.digest
EVIDENCE = 'config/vector-list-leaf-alternatives-origin-evidence.json'
MANIFEST_SHA256 = '42c0eee2fd8764c7871e8a251c0e0dba789b1c850849a1182493f294cbbe7209'
KEYS = {'0x0040E9B0': 16, '0x0040EA20': 16, '0x004124B0': 16,
        '0x0041F7E0': 16, '0x00532350': 16, '0x005F9640': 16}
PLAN_DIGESTS = {'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'retained_sha256': '582024655e1c9252823c71e5b6179e9aefd8d639208e18d0e0cbe61717123a21', 'prior': 'eb6e0875c6a232f43c4bf271d7da24e2ae3971141904530d2afb74a990ff9754', 'leaves': '9faa0cceb876b39cb252db26f64f48f70bd03835fa86fb6f60ef74daaf1c6522', 'parents': '7bd8ffabd007967632ee27cb327d66e80f7d2c05c7e83537875b764f78caf54a', 'alternatives': '4bc540154bb962c39954c51570b95a59a9aef31c925a9ea51272a541d427a169', 'public_control': '67c1ebeb45aecf947a37c99cac50ea2beb4f9ec80b5d6012860c96b9c1c1d98c'}


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        text = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
        if text[:3].lower() != 'z:/': raise ValueError('Leaf original include loses host mapping')
        path = Path(text[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith(('.tools/msvc710/Vc7/include/', 'probes/')):
            raise ValueError('Leaf include gains an unrelated owner')
        found[relative] = digest(path.read_bytes())
    return found


def retained_catalog(prior):
    catalog = {}
    for r in prior['controls']:
        for d in r['section']['definitions']:
            if d['storage'] not in (2, 3) or d['symbol'].startswith('.'): continue
            address = int(r['address'], 16) + d['offset']
            if d['symbol'] in catalog and catalog[d['symbol']] != address:
                raise ValueError('Leaf retained complete source owner is incoherent')
            catalog[d['symbol']] = address
    for symbol, address in prior['external'].items():
        address = int(address, 16)
        if symbol in catalog and catalog[symbol] != address:
            raise ValueError('Leaf external symbol overrides complete source owner')
        catalog[symbol] = address
    return catalog


def verify_plan(m):
    if (m['evidence_id'] != 'R206' or len(m['leaves']) != 6
            or {r['address']: r['size'] for r in m['leaves']} != KEYS):
        raise ValueError('Leaf alternatives lose the bounded whole cohort')
    for key, sha in PLAN_DIGESTS.items():
        if BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Leaf immutable source/parent/alternative context differs: ' + key)
    if (len(m['prior']) != 6 or len(m['parents']) != 7
            or sum(r['size'] for r in m['parents']) != 588 or len(m['alternatives']) != 6):
        raise ValueError('Leaf alternatives omit complete independent contexts')
    for r in m['leaves']:
        if (r['decision'] != 'retain-unknown' or r['origin']['origin'] != 'unknown'
                or r['function']['status'] != 'unclassified' or r['function']['owner']
                or r['function']['source_file'] or r['function']['signature']
                or r['function']['calling_convention'] or r['function']['match_percent'] != '0.00'
                or r['fields'] or r['bindings']):
            raise ValueError('Leaf shape gains unsupported ownership/private ABI/source/exact credit')


def replay(m):
    c = module('leaf_target', 'compare-coff-function.py'); coff = module('leaf_coff', 'coff_data.py')
    extra = module('leaf_carriers', 'sdk_x3d_carriers.py'); flow = module('leaf_flow', 'sdk_image_carriers.py')
    pe = module('leaf_permissions', 'verify-sdk-x3d-origins.py')
    inventory = module('leaf_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Leaf target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    scratch = ROOT / 'build/origin-vector-list-leaf-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'Leaf.obj'

        def cold(control):
            result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj),
                                     *control['profile']], cwd=ROOT, capture_output=True, text=True)
            if result.returncode or headers(result.stdout + result.stderr) != control['headers']:
                raise ValueError('Leaf cold source/original include ownership differs')
            body = obj.read_bytes()
            if inventory(body, c, coff) != control['emission']:
                raise ValueError('Leaf full ordinary code/data/EH emission differs')
            layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
            if list(struct.unpack('<' + str(len(layout) // 4) + 'I', layout)) != control['layout_values']:
                raise ValueError('Leaf complete original observation layout differs')
            return body

        for i, control in enumerate(m['prior']):
            prior = json.loads((ROOT / control['path']).read_text()); catalog = retained_catalog(prior)
            for key in ['probe', 'profile', 'headers', 'emission', 'layout', 'layout_values']:
                if control[key] != prior[key]: raise ValueError('Leaf changes retained original source controls')
            body = cold(control)
            for r in [q for q in m['leaves'] + m['parents'] if q['prior'] == i]:
                if r['record'] not in prior['controls'] or r['path'] != control['path']:
                    raise ValueError('Leaf typed parent is not the whole retained original source')
                raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
                source = BASE.canonical_source(source, body); a = int(r['address'], 16)
                if (source != r['source'] or fields != r['fields'] or len(raw) != r['size']
                        or digest(raw) != r['source_sha256']
                        or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                    raise ValueError('Leaf complete original source/AUX/actual fields differ')
                linked, calls, data = BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, i, a)
                actual = c.pe_bytes_at(target, a, len(raw))
                if (linked != actual or digest(actual) != r['body_sha256']
                        or flow.flow(actual, a, [0], fields, calls, data, None, None, None) != r['flow']
                        or functions[r['address']] != r['function'] or origins[r['address']] != r['origin']
                        or any(a < int(k, 16) < a + len(raw) for k in functions)):
                    raise ValueError('Leaf entire source/native/CFG/canonical extent differs')
        body = cold(m['public_control'])
        for r in m['alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            source = BASE.canonical_source(source, body)
            if (source != r['source'] or fields != r['fields'] or fields or len(raw) != 16
                    or digest(raw) != r['source_sha256']):
                raise ValueError('Leaf whole library/ordinary alternative differs')
            for leaf in m['leaves']:
                if raw != c.pe_bytes_at(target, int(leaf['address'], 16), 16):
                    raise ValueError('Leaf alternative is not complete unmasked byte-equal evidence')


def main():
    m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']),
                      *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('Leaf immutable source/evidence differs: ' + path)
    replay(m)
    print('R206 review OK: six complete opaque leaves96 remain unknown; seven whole typed retained parents588; '
          'six complete public vector/list and ordinary getter alternatives16 each are byte-equal; '
          'six complete original cold emissions/headers/layouts and new generic controls retained; '
          'all source/AUX/fields/native bytes/CFG/canonical rows preserved; no ownership/source/ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
