#!/usr/bin/env python3
"""Cold-replay explicit nested initialization and preserve unresolved short owners."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('initialization_prior', ROOT / 'scripts/verify-nested-vector-insertion-origins.py')
PRIOR = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(PRIOR)
SOURCE = PRIOR.PRIOR
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/nested-initialization-origin-evidence.json'
MANIFEST_SHA256 = '0b693e67bc49d4618028f5b9d4a1d61142abfa0911167207bfa0a77bc9403c47'
PLAN_DIGESTS = {'groups': '995146f5459237347e37065ec3e6099425346c3880aeba01873ac4ab3966ed40', 'sections': 'e16338535df93f94a84211c6d4168cf7d8a93afb80c77e3b3fd11c4821073397', 'weak_references': 'f7ad6a263a2d1a898771486fcf6e7a95a8f75b7fbb152387bc4255c592c72228', 'evidence_id': '7933ba600810386390b907a34a54e14ba336a6d14f7002a5e38c812fa744925d', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'prior': '294909e7c2b96c02723fffb7ae69523a72e471f15bc77d0e542fbdeb5d0861a5', 'functions': '3728cb506b895ee6189040f74ec374400b90dc9df9ad5d9a6e20cca545855882', 'retained_unknowns': 'ef21cb6c8d592280ab816bbd5eb1dca412c72137853aa2e1c5a8c3dc3e64c550', 'parents': 'eb9a26ad70d84ee7ce44df8eefc7877b9d5574c197280f485ed41fcb433e7ac0', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'authored_path': 'da29b2e33a323688b9bb6a07ea972dc66bb7ba9ae840358d5ca205a566e8ebb6', 'memset': '078e6f9e489d82cafd1e133ba0dcc33afcd8b9a83cfcdd5036aae782d06342f2', 'public_control': '3f2a0f1805dd4f9e813233b7d3e68d8e8b478410935a6650a616220e081b02b6', 'alternatives': '2d6227314a57cba9c8d93e2b1fe27bfe5f5710fbda182268fdd38d75f5b8f37d', 'retained_sha256': '6f723be4c5db1e98489da6134ecdb9cc5c229233537bb6e1e2071778531f9543'}
WHOLE = {'0x004587E0': 145, '0x00458880': 47}


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Initialization immutable complete evidence differs: ' + key)
    if (m['evidence_id'] != 'R210' or {r['address']: r['size'] for r in m['functions']} != WHOLE
            or len(m['functions']) != 2 or len(m['groups']) != 1
            or len(m['sections']) != 37 or sum(r['size'] for r in m['sections']) != 1400
            or sum(len(r['fields']) for r in m['sections']) != 73
            or sum(r['kind'] == 'code' for r in m['sections']) != 29
            or len(m['retained_unknowns']) != 4 or len(m['parents']) != 2 or m['historical_snapshots']
            or len(m['public_control']['emission']) != 100
            or sum(r['size'] for r in m['public_control']['emission']) != 4743
            or [r['size'] for r in m['alternatives']] != [93, 81, 104]):
        raise ValueError('Initialization loses complete bounded policy/carrier/default controls')
    for r in m['functions']:
        f, o, af, ao = (r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin'])
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified'
                or any(f[k] or af[k] for k in ['owner', 'source_file', 'signature', 'calling_convention'])
                or af['status'] != 'unclassified' or f['match_percent'] != '0.00' or af['match_percent'] != '0.00'
                or any(af[k] != f[k] for k in ['address', 'size', 'span_end', 'current_name'])
                or af['size'] != str(r['size']) or r['cfg'] != [1, 0]
                or ao['origin'] != 'authored' or ao['disposition'] != 'authored' or ao['evidence_id'] != 'R210'):
            raise ValueError('Initialization gains unsupported extent/private ABI/source/exact credit')
    for r in m['retained_unknowns']:
        if (r['origin']['origin'] != 'unknown' or r['function']['status'] != 'unclassified'
                or r['function']['owner'] or r['function']['source_file']):
            raise ValueError('Initialization assigns unresolved short/private ownership')


def check_call(raw, address, call):
    site = int(call['site'], 16); offset = site - address
    if (offset < 0 or offset + 5 > len(raw) or raw[offset] != 0xe8
            or site + 5 + struct.unpack_from('<i', raw, offset + 1)[0] != int(call['target'], 16)):
        raise ValueError('Initialization loses complete native parent/policy call evidence')


def replay(m, evidence_only=False):
    c = module('initialization_target', 'compare-coff-function.py'); coff = module('initialization_coff', 'coff_data.py')
    extra = module('initialization_carriers', 'sdk_x3d_carriers.py'); flow = module('initialization_flow', 'sdk_image_carriers.py')
    pe = module('initialization_permissions', 'verify-sdk-x3d-origins.py'); rt = module('initialization_crt', 'verify-runtime-origins.py')
    authored = module('initialization_authored', 'verify-authored-origins.py')
    inventory = module('initialization_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Initialization target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    own = list(csv.DictReader((ROOT / m['authored_path']).open()))
    if own != [r['record'] for r in m['functions']]: raise ValueError('Initialization own authored records differ')
    for r in m['functions']:
        if functions[r['address']] != r[state + '_function'] or origins[r['address']] != r[state + '_origin']:
            raise ValueError('Initialization bounded canonical transition differs')
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (digest(raw) != r['record']['body_sha256'] or list(authored.verify_body(raw, a)) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('Initialization complete authored native body/CFG differs')
        for call in r['calls']: check_call(raw, a, call)
    for r in m['retained_unknowns']:
        if functions[r['function']['address']] != r['function'] or origins[r['origin']['address']] != r['origin']:
            raise ValueError('Initialization changes a protected short/private unknown')
    prior = json.loads((ROOT / m['prior']['path']).read_text())
    if (digest((ROOT / m['prior']['path']).read_bytes()) != m['prior']['manifest_sha256']
            or prior['prior']['shared'] != m['prior']['shared'] or prior['prior']['absolute'] != m['prior']['absolute']
            or prior['prior']['crt_archive_sha256'] != m['prior']['crt_archive_sha256']):
        raise ValueError('Initialization replaces independent prior source ownership')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-nested-vector-insertion-origins.py')],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode: raise ValueError('Initialization complete prior cold graph failed: ' + result.stderr)
    print(result.stdout.strip(), flush=True)
    old = json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())
    source_catalog = SOURCE.BASE.retained_catalog(old); shared = {'__except_list': 0}
    for r in m['prior']['shared']:
        owner = r['owner']
        if old[owner['collection']][owner['index']] != owner['record'] or source_catalog.get(r['symbol']) != int(r['address'], 16):
            raise ValueError('Initialization field observation overrides retained full source definition')
        shared[r['symbol']] = source_catalog[r['symbol']]
    records = list(csv.DictReader((ROOT / 'config/authored-origin-evidence.csv').open()))
    switches = list(csv.DictReader((ROOT / 'config/authored-origin-switches.csv').open()))
    direct = list(csv.DictReader((ROOT / 'config/authored-origin-direct-switches.csv').open()))
    for r in m['parents']:
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (r['record'] not in records or functions[r['address']] != r['function'] or origins[r['address']] != r['origin']
                or r['origin']['origin'] != 'authored' or digest(raw) != r['body_sha256']
                or digest(raw) != r['record']['body_sha256']
                or [q for q in switches if q['address'] == r['address']] != r['switches']
                or [q for q in direct if q['address'] == r['address']] != r['direct_switches']
                or list(authored.verify_body(raw, a, r['switches'], lambda x, n: c.pe_bytes_at(target, x, n), r['direct_switches'])) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('Initialization complete authored game parent/CFG differs')
        check_call(raw, a, r['call'])
    p = m['memset']; q = p['record']; crt = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(crt) != q['archive_sha256'] or q not in list(csv.DictReader((ROOT / 'config/runtime-origin-evidence.csv').open())):
        raise ValueError('Initialization original memset archive/record differs')
    name, body = {a: (n, b) for a, n, b in rt.archive_members(crt)}[int(q['member_offset'])]
    raw, fields, source = extra.section_carrier(body, p['source']['section'], c, coff); a = int(q['address'], 16)
    aux = next(x for x in source['aux_records'] if x['symbol'] == '_memset')
    if (name != q['member'] or digest(body) != p['member_sha256'] or SOURCE.BASE.canonical_source(source, body) != p['source']
            or fields != p['fields'] or fields or len(raw) != 96 or aux['aux_count'] != 1
            or struct.unpack_from('<I', bytes.fromhex(aux['aux_hex']), 4)[0] != len(raw)
            or raw != c.pe_bytes_at(target, a, 96) or digest(raw) != q['body_sha256']
            or list(authored.verify_body(raw, a)) != p['cfg'] or SOURCE.instructions(raw, a, flow) != p['instructions']
            or functions[q['address']] != p['function'] or origins[q['address']] != p['origin']):
        raise ValueError('Initialization memset lacks its complete original own-AUX/native/CFG proof')
    shared['_memset'] = a
    scratch = ROOT / 'build/origin-nested-initialization-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'Initialization.obj'; control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or SOURCE.HEADERS(result.stdout + result.stderr) != control['headers']:
            raise ValueError('Initialization cold generic source/original includes differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != control['emission']: raise ValueError('Initialization omits ordinary code/data/EH emission')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 40 or list(struct.unpack('<10I', layout)) != control['layout_values']:
            raise ValueError('Initialization crops the complete generic observation carrier')
        if [SOURCE.weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
            raise ValueError('Initialization loses actual weak AUX/strong fallback')
        rows = m['sections']; decoded = {}
        for r in rows:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff); a = int(r['base'], 16)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                    or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                raise ValueError('Initialization complete source/AUX/fields/permissions differ')
            decoded[r['source']['section']] = (raw, fields)
            if r['kind'] == 'code':
                actual = [dict(function=f, origin=origins[k]) for k, f in functions.items() if a <= int(k, 16) < a + r['size']]
                expected = [dict(function=selected[q['function']['address']][state + '_function'],
                                 origin=selected[q['function']['address']][state + '_origin'])
                            if q['function']['address'] in selected else q for q in r['inventory_entries']]
                if actual != expected: raise ValueError('Initialization full source hides an inventory entry')
        catalog = SOURCE.owned_catalog(rows, shared, 0, m['weak_references'])
        for r in rows:
            raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
            linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, 0, a, data_image=r['kind'] == 'data')
            actual = c.pe_bytes_at(target, a, len(raw))
            if linked != actual or digest(actual) != r['body_sha256']: raise ValueError('Initialization complete unmasked body differs')
            if r['kind'] == 'code':
                roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type'] == 32 and d['storage'] == 3)
                roots.update(f['symbol_offset'] + f['addend'] for q in rows for f in q['fields']
                             if f['symbol_section'] == r['source']['section'] and f['symbol_storage'] == 6)
                if sorted(roots) != r['roots'] or flow.flow(actual, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                    raise ValueError('Initialization complete normal/EH/unwind/shared-exit CFG differs')
        for r in m['alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields'] or len(raw) != r['size']
                    or digest(raw) != r['source_sha256'] or SOURCE.instructions(raw, 0x100000, flow) != r['instructions']):
                raise ValueError('Initialization complete default/value-initialization control differs')
        implicit = m['alternatives'][0]
        explicit = next(r for r in rows if r['base'] == '0x004587E0')
        if (any(f['symbol'] == '_memset' or f['symbol'].startswith('?clear@') for f in implicit['fields'])
                or sum(f['symbol'].startswith('?clear@') for f in explicit['fields']) != 2
                or sum(f['symbol'] == '_memset' for f in explicit['fields']) != 1):
            raise ValueError('Initialization default constructor can replace explicit whole-zero/two-clear policy')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']), *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('Initialization immutable source/evidence differs: ' + path)
    replay(m, args.evidence_only)
    print('R210 origins OK: two authored initialization policies192; complete generic/default controls145/47/93/81/104; '
          '37 whole code/data carriers1400/all73 actual fields/29 CFGs; 100 ordinary emissions4743/27 original includes; '
          'two complete authored parents5418/native call sites; original CRT memset96/own AUX/CFG; complete retained '
          'R209/R208/R150 cold proof; four short/private controls remain unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
