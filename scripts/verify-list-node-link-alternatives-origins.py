#!/usr/bin/env python3
"""Replay complete public/ordinary list node links while preserving opaque origin."""
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


PRIOR = module('node_leaf_prior', 'verify-vector-list-leaf-alternatives-origins.py')
BASE = PRIOR.BASE
digest = BASE.digest
EVIDENCE = 'config/list-node-link-alternatives-origin-evidence.json'
MANIFEST_SHA256 = '19c05f902093e46d3d85daf6c95ea5d2a477ea66049d9a8398b4e5fe6c4b85db'
KEYS = {'0x00411E80': 8, '0x00411E90': 11, '0x004124C0': 11, '0x0041E100': 8,
        '0x0041E110': 11, '0x00531D80': 8, '0x00531D90': 11}
PLAN_DIGESTS = {'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'retained_sha256': '849b1a414938dedef90fd89b1878c4f21639647eeb0d75119446200bf12ceb54', 'prior': 'bc1b965000bbdeafb502ff5cdb8e05f15ef3b55160f39d20bd50d5bc499d2737', 'leaves': 'f1e1cbdd2b00b2322fac39a665c9bcbd21a8a058d89b3cb4c4fee74592224ad9', 'parents': '5cf8862106f24e3c0ce8214389e1792c38c23108a02ffa1365f02865ddfbbd24', 'alternatives': '0e6f2e48d2de0b1ff187b8f784154554044bd33b7898a6e03537d9f8d6039fa5', 'public_control': 'cec1f974cd72236c8ecbfc7d5e8bec7a47c8d4024e472e65121116cea93c8519'}


headers = PRIOR.headers
retained_catalog = PRIOR.retained_catalog


def verify_plan(m):
    if (m['evidence_id'] != 'R207' or len(m['leaves']) != 7
            or {r['address']: r['size'] for r in m['leaves']} != KEYS):
        raise ValueError('Node alternatives lose the bounded whole cohort')
    for key, sha in PLAN_DIGESTS.items():
        if BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Node immutable source/parent/alternative context differs: ' + key)
    if (len(m['prior']) != 3 or len(m['parents']) != 5
            or sum(r['size'] for r in m['parents']) != 556 or len(m['alternatives']) != 12):
        raise ValueError('Node alternatives omit complete independent contexts')
    for r in m['leaves']:
        if (r['decision'] != 'retain-unknown' or r['origin']['origin'] != 'unknown'
                or r['function']['status'] != 'unclassified' or r['function']['owner']
                or r['function']['source_file'] or r['function']['signature']
                or r['function']['calling_convention'] or r['function']['match_percent'] != '0.00'
                or r['fields'] or r['bindings']):
            raise ValueError('Node shape gains unsupported ownership/private ABI/source/exact credit')


def replay(m):
    c = module('leaf_target', 'compare-coff-function.py'); coff = module('leaf_coff', 'coff_data.py')
    extra = module('leaf_carriers', 'sdk_x3d_carriers.py'); flow = module('leaf_flow', 'sdk_image_carriers.py')
    pe = module('leaf_permissions', 'verify-sdk-x3d-origins.py')
    inventory = module('leaf_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Node target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    scratch = ROOT / 'build/origin-vector-list-leaf-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'Leaf.obj'

        def cold(control):
            result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj),
                                     *control['profile']], cwd=ROOT, capture_output=True, text=True)
            if result.returncode or headers(result.stdout + result.stderr) != control['headers']:
                raise ValueError('Node cold source/original include ownership differs')
            body = obj.read_bytes()
            if inventory(body, c, coff) != control['emission']:
                raise ValueError('Node full ordinary code/data/EH emission differs')
            layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
            if list(struct.unpack('<' + str(len(layout) // 4) + 'I', layout)) != control['layout_values']:
                raise ValueError('Node complete original observation layout differs')
            return body

        for i, ref in enumerate(m['prior']):
            retained = json.loads((ROOT / ref['path']).read_text())
            control = retained['prior'][ref['index']]
            if control['path'] != ref['source_path']:
                raise ValueError('Node loses the literal complete retained source graph')
            prior = json.loads((ROOT / control['path']).read_text()); catalog = retained_catalog(prior)
            for key in ['probe', 'profile', 'headers', 'emission', 'layout', 'layout_values']:
                if control[key] != prior[key]: raise ValueError('Node changes retained original source controls')
            body = cold(control)
            for r in [q for q in m['leaves'] + m['parents'] if q['prior'] == i]:
                if r['record'] not in prior['controls'] or r['path'] != control['path']:
                    raise ValueError('Node typed parent is not the whole retained original source')
                raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
                source = BASE.canonical_source(source, body); a = int(r['address'], 16)
                if (source != r['source'] or fields != r['fields'] or len(raw) != r['size']
                        or digest(raw) != r['source_sha256']
                        or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                    raise ValueError('Node complete original source/AUX/actual fields differ')
                linked, calls, data = BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, i, a)
                actual = c.pe_bytes_at(target, a, len(raw))
                if (linked != actual or digest(actual) != r['body_sha256']
                        or flow.flow(actual, a, [0], fields, calls, data, None, None, None) != r['flow']
                        or functions[r['address']] != r['function'] or origins[r['address']] != r['origin']
                        or any(a < int(k, 16) < a + len(raw) for k in functions)):
                    raise ValueError('Node entire source/native/CFG/canonical extent differs')
        body = cold(m['public_control'])
        for r in m['alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            source = BASE.canonical_source(source, body)
            if (source != r['source'] or fields != r['fields'] or fields or len(raw) != r['size']
                    or digest(raw) != r['source_sha256']):
                raise ValueError('Node whole library/ordinary alternative differs')
            for leaf in [q for q in m['leaves'] if q['role'] == r['role']]:
                if raw != c.pe_bytes_at(target, int(leaf['address'], 16), leaf['size']):
                    raise ValueError('Node alternative is not complete unmasked byte-equal evidence')


def main():
    m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']),
                      *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('Node immutable source/evidence differs: ' + path)
    replay(m)
    print('R207 review OK: seven whole list node-link/value leaves68 remain unknown; '
          'five entire retained typed parents556; twelve full public/intrusive source alternatives; '
          'three full original cold emissions/headers/layouts and new complete generic controls retained; '
          'all source/AUX/fields/native/CFG/canonical records preserved; no ownership/source/ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
