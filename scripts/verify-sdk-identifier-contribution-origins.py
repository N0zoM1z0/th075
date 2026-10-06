#!/usr/bin/env python3
"""Replay complete SDK identifier contributions and ordinary equality alternatives."""
import argparse
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import importlib.util

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


PRIOR = module('identifier_contribution_prior', 'verify-vendor-zeroing-contribution-origins.py')
digest, metadata_digest, rows, linked = PRIOR.digest, PRIOR.metadata_digest, PRIOR.rows, PRIOR.linked
EVIDENCE = 'config/sdk-identifier-contribution-origin-evidence.json'
MANIFEST_SHA256 = '611d872cdf46766f61eba3abdbed4190158e45726c5a9ef295b8d574c502db6d'
PLAN_SHA256 = 'ed195a290b64618344bc8258648859d4356254c7340c6bd4da7b8fc4c4aa88c2'
WHOLE = {'0x00608E33': 23, '0x00609B1E': 23}


def verify_context(plan):
    if [u['member_offset'] for u in plan['units']] != [354064, 393840]:
        raise ValueError('Identifier original complete Font/Surface owners differ')
    code = [r for u in plan['units'] for r in u['code']]
    data = [r for u in plan['units'] for r in u['data']]
    if (len(code), sum(r['size'] for r in code), len(data), sum(r['size'] for r in data),
            sum(len(r['fields']) for r in code + data)) != (35, 1849, 2, 80, 46):
        raise ValueError('Identifier loses whole original code/vtable/field context')
    for u, omitted in zip(plan['units'], [[10], [3, 9, 32]]):
        by = {r['source']['section']: r for r in u['code']}
        if u['span']['order'] != [n for n in by if n not in omitted]:
            raise ValueError('Identifier omits a real source-order function')
        at = int(u['span']['address'], 16)
        for n in u['span']['order']:
            r = by[n]
            if (int(r['address'], 16) != at or r['size'] != r['source']['size']
                    or r['source']['flags'] != 0x60101020):
                raise ValueError('Identifier whole source-order contribution differs')
            at += r['size']
        if at != int(u['span']['end'], 16):
            raise ValueError('Identifier complete source-order end differs')
    font, surface = plan['units']
    f = {r['source']['section']: r for r in font['code']}
    s = {r['source']['section']: r for r in surface['code']}
    if (f[14]['symbol'], f[14]['address'], s[9]['symbol'], s[9]['address'],
            s[11]['symbol'], s[11]['address']) != (
            '_IsEqualGUID', '0x00608E33', '_IsEqualGUID', '0x00608E33', '_==', '0x00609B1E'):
        raise ValueError('Identifier duplicate GUID and distinct operator placement differs')
    for r in [f[14], s[9], s[11]]:
        aux = next(a for a in r['source']['aux_records'] if a['symbol'] == '.text')
        if (r['size'] != 23 or r['fields'] or bytes.fromhex(aux['aux_hex'])[14] != 2
                or r['flow']['returns'] != [{'offset': 22, 'cleanup': 0}]):
            raise ValueError('Identifier original complete COMDAT ANY/body/return differs')
    if (f[10]['address'], s[32]['address'], s[3]['address']) != (
            '0x006049A0', '0x006049D8', '0x00608D8B'):
        raise ValueError('Identifier forces displaced/reused sections into its primary spans')
    if (plan['control']['layout'] != [16, 4] or plan['control']['targets'] != list(WHOLE)
            or len(plan['control']['emission']) != 2):
        raise ValueError('Identifier loses genuine complete ordinary storage equality')
    if any(p['origin']['origin'] != 'unknown' for p in plan['protected_pairs']):
        raise ValueError('Identifier falsely resolves explicit/generated private lifetimes')


def verify_plan(plan):
    if metadata_digest(plan) != PLAN_SHA256:
        raise ValueError('Identifier immutable complete evidence differs')
    if plan['evidence_id'] != 'R262' or {r['address']: r['size'] for r in plan['functions']} != WHOLE:
        raise ValueError('Identifier bounded two-leaf scope differs')
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (r['original_origin']['origin'] != 'unknown' or r['accepted_origin']['origin'] != 'library'
                or not r['accepted_origin']['confidence'].startswith('inferred-')
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or any(new[k] for k in ['signature', 'calling_convention', 'source_file'])
                or new['match_percent'] != '0.00' or new['status'] != 'excluded'):
            raise ValueError('Identifier gains unsupported type/source/ABI/extent/exact credit')
    verify_context(plan)


def historical_rows(plan, name, actual, evidence_only=False):
    """Return only these two checked literal predecessor rows for older guards."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    verify_plan(plan)
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['functions']}
    state = 'original_' if evidence_only else 'accepted_'
    for a, r in selected.items():
        if [q for q in actual if q['address'] == a] != [r[state + kind]]:
            raise ValueError('Identifier loses, duplicates or substitutes a literal selected pair')
    return [selected[r['address']]['original_' + kind] if r['address'] in selected else r for r in actual]


def allows_transition(address, old_function, old_origin, function, origin):
    plan = json.loads((ROOT / EVIDENCE).read_text())
    verify_plan(plan)
    return any(r['address'] == address and r['original_function'] == old_function
               and r['original_origin'] == old_origin and r['accepted_function'] == function
               and r['accepted_origin'] == origin for r in plan['functions'])


def verify_canonical(plan, evidence_only=False):
    for name in ['functions.csv', 'function-origins.csv']:
        actual = rows(name)
        historical_rows(plan, name, actual, evidence_only)
        if metadata_digest([r for r in actual if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('Identifier changes unrelated canonical rows')
    fs, origins = ({r['address']: r for r in rows(n)} for n in ['functions.csv', 'function-origins.csv'])
    for r in [r for u in plan['units'] for r in u['code']] + plan['protected_pairs']:
        f = r['function']
        if f and f['address'] not in WHOLE and (fs.get(f['address']) != f or origins.get(f['address']) != r['origin']):
            raise ValueError('Identifier changes an existing owner or adds an auxiliary candidate')


def provider_catalog(plan):
    # Each provider is recovered from an unchanged independently replayed full
    # original proof, never from this cohort's native relocation destinations.
    old201 = json.loads((ROOT / plan['retained_proofs'][0]['manifest']).read_text())
    old186 = json.loads((ROOT / plan['retained_proofs'][1]['manifest']).read_text())
    catalog = dict(old186['catalog'])
    for r in old201['anchors']:
        catalog[r['comparison']['symbol']] = r['address']
    for r in old201['sections']:
        if r.get('symbol'):
            catalog[r['symbol']] = r['base']
    for r in old201['imports']:
        catalog[r['symbol']] = r['address']
    if any(catalog.get(s) != a for s, a in plan['providers'].items()):
        raise ValueError('Identifier provider loses its independent complete original proof')
    return plan['providers']


def verify_native(plan):
    c = module('identifier_target', 'compare-coff-function.py')
    coff = module('identifier_coff', 'coff_data.py')
    extra = module('identifier_sections', 'sdk_x3d_carriers.py')
    flow = module('identifier_flow', 'sdk_graphics_carriers.py')
    rt = module('identifier_archive', 'verify-runtime-origins.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('Identifier target identity differs')
    for path, sha in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('Identifier retained original proof differs: ' + path)
    archive = (ROOT / plan['archive']).read_bytes()
    if digest(archive) != plan['archive_sha256']:
        raise ValueError('Identifier source archive differs')
    members = {o: (n, b) for o, n, b in rt.archive_members(archive)}
    providers = provider_catalog(plan)
    for u in plan['units']:
        name, body = members[u['member_offset']]
        if name != u['member'] or digest(body) != u['member_sha256']:
            raise ValueError('Identifier complete original object differs')
        actual = []
        for n in range(1, struct.unpack_from('<H', body, 2)[0] + 1):
            h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * (n - 1))
            if h[3] and h[4]:
                raw, fields, source = extra.section_carrier(body, n, c, coff)
                actual.append(dict(source=source, fields=fields, source_sha256=digest(raw)))
        if actual != u['inventory']:
            raise ValueError('Identifier whole source/AUX/COMDAT/field inventory differs')
        bases = {r['source']['section']: int(r['address'], 16) for r in u['code'] + u['data']}
        for r in u['code'] + u['data']:
            a = int(r['address'], 16)
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            if fields != r['fields'] or source != r['source'] or digest(raw) != r['source_sha256']:
                raise ValueError('Identifier complete original defining section differs')
            calls, data = {}, {}
            for f, b in zip(fields, r['bindings']):
                base = bases[f['symbol_section']] + f['symbol_offset'] if f['symbol_section'] > 0 else int(providers[f['symbol']], 16)
                dest = (base + f['addend']) & 0xffffffff
                if b['field'] != f or int(b['target_address'], 16) != dest:
                    raise ValueError('Identifier genuine field loses its full source/provider namespace')
                (calls if f['type'] == 'REL32' else data)[a + f['offset']] = dest
            native = c.pe_bytes_at(target, a, r['size'])
            if linked(raw, fields, r['bindings'], a) != native or digest(native) != r['body_sha256']:
                raise ValueError('Identifier complete unmasked code/vtable differs')
            if r in u['code'] and flow.flow(native, a, [0], fields, calls, data, None, None) != r['flow']:
                raise ValueError('Identifier whole native CFG differs')
    found = []; scanned = 0
    for off, name, body in rt.archive_members(archive):
        if len(body) < 20 or body[:2] != b'\x4c\x01':
            continue
        scanned += 1
        for n in range(1, struct.unpack_from('<H', body, 2)[0] + 1):
            h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * (n - 1))
            if not h[9] & 32 or h[3] != 23 or h[7]:
                continue
            raw = body[h[4]:h[4] + h[3]]
            matches = [a for a in WHOLE if raw == c.pe_bytes_at(target, int(a, 16), 23)]
            if matches:
                raw, fields, source = extra.section_carrier(body, n, c, coff)
                found.append(dict(member_offset=off, member=name, member_sha256=digest(body), source=source,
                                  fields=fields, source_sha256=digest(raw), targets=matches))
    if found != plan['survey']['matches'] or scanned != plan['survey']['scanned_coff_members']:
        raise ValueError('Identifier loses original duplicate source alternatives')
    return c, coff, extra, target


def cold_control(plan, c, coff, extra, target):
    ctl = plan['control']
    common = module('identifier_headers', 'verify-sdk-row-deleting-helper-origins.py')
    inventory = module('identifier_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    if digest((ROOT / ctl['source']).read_bytes()) != ctl['source_sha256']:
        raise ValueError('Identifier ordinary control source differs')
    with tempfile.TemporaryDirectory(prefix='th075-identifier-control-') as directory:
        obj = Path(directory) / 'Identifier.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['source']), str(obj), *ctl['profile']],
                                cwd=ROOT, capture_output=True, text=True, check=True)
        if common.included_headers(result.stdout + result.stderr) != ctl['headers']:
            raise ValueError('Identifier actual ordinary included headers differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != ctl['emission']:
            raise ValueError('Identifier whole cold ordinary emission differs')
        code = []; values = None
        for r in ctl['sections']:
            raw, fields, source = extra.section_carrier(body, r['section'], c, coff)
            if (common.SOURCE.BASE.canonical_source(source, body) != r['source']
                    or fields != r['fields'] or digest(raw) != r['source_sha256']):
                raise ValueError('Identifier complete ordinary source section differs')
            if any(d['symbol'] == ctl['symbol'] and d['type'] == 32 for d in source['definitions']):
                code.append(raw)
                if fields or len(raw) != 23 or any(raw != c.pe_bytes_at(target, int(a, 16), 23) for a in ctl['targets']):
                    raise ValueError('Identifier genuine whole ordinary equality23 differs')
            if any(d['symbol'] == '?IdentifierComparisonLayout@@3QBKB' for d in source['definitions']):
                values = list(struct.unpack('<2I', raw))
        if len(code) != 1 or values != ctl['layout']:
            raise ValueError('Identifier ordinary complete definition/layout absent')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Identifier original complete manifest differs')
    verify_plan(plan)
    verify_canonical(plan, args.evidence_only)
    c, coff, extra, target = verify_native(plan)
    for proof in plan['retained_proofs']:
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / proof['verifier'])],
                                cwd=ROOT, capture_output=True, text=True, check=True)
        print('Complete retained ' + proof['evidence_id'] + ': ' + result.stdout.strip().splitlines()[-1], flush=True)
    cold_control(plan, c, coff, extra, target)
    print('R262 origins OK:two inferred-library identifier leaves46;whole Font523/Surface1244 primary spans,'
          'two displaced deleting wrappers56,two source reuse placements;35 complete source code sections1849,'
          '33 unique native bodies1823,vtable80/all46 fields;whole source inventories76/2884;'
          '12 duplicate source23 definitions from eight original objects;complete unchanged R201/R186 cold proofs;'
          'ordinary storage equality23/full layout8/one actual header;five private lifetimes remain unknown;'
          'original names/link map/type remain provisional;no source/ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
