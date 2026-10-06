#!/usr/bin/env python3
"""Replay inferred vendor zeroing origins from complete object contributions."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/vendor-zeroing-contribution-origin-evidence.json'
MANIFEST_SHA256 = '230aff10d00fba14be7d69005cf628f91027eb67e9e3df6994d37b600801cbc2'
WHOLE = {'0x00625575': 14, '0x0064F513': 12}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


def digest(body):
    return hashlib.sha256(body).hexdigest()


def metadata_digest(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':')).encode())


def rows(name):
    with (ROOT / 'config' / name).open(newline='') as stream:
        return list(csv.DictReader(stream))


def verify_plan(plan):
    if metadata_digest(plan) != PLAN_SHA256:
        raise ValueError('Vendor contribution immutable full evidence differs')
    if plan['evidence_id'] != 'R260' or {r['address']: r['size'] for r in plan['functions']} != WHOLE:
        raise ValueError('Vendor contribution bounded scope differs')
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (r['original_origin']['origin'] != 'unknown'
                or r['accepted_origin']['origin'] != 'library'
                or not r['accepted_origin']['confidence'].startswith('inferred-')
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or any(new[k] for k in ['source_file', 'signature', 'calling_convention'])
                or new['match_percent'] != '0.00' or new['status'] != 'excluded'):
            raise ValueError('Vendor contribution gains unsupported extent/source/ABI/exact credit')
    for u, count, size in zip(plan['units'], [15, 14], [441, 1124]):
        if len(u['code']) != count or u['span']['size'] != size:
            raise ValueError('Vendor contribution omits complete source code')
        at = int(u['span']['address'], 16)
        code_sections = [r['source']['section'] for r in u['whole_source_inventory'] if r['source']['flags'] & 32]
        if code_sections != [r['source']['section'] for r in u['code']]:
            raise ValueError('Vendor contribution source section order differs')
        for r in u['code']:
            if (int(r['address'], 16) != at or r['source']['flags'] != 0x60101020
                    or r['size'] != r['source']['size']):
                raise ValueError('Vendor contribution loses whole COMDAT/alignment topology')
            at += r['size']
        if at != int(u['span']['end'], 16):
            raise ValueError('Vendor contribution complete span differs')


def historical_rows(plan, name, actual, evidence_only=False):
    """Expose only the two verified literal predecessors, without modifying CSVs."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    verify_plan(plan)
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['functions']}
    expected = 'original_' if evidence_only else 'accepted_'
    for a, r in selected.items():
        if [q for q in actual if q['address'] == a] != [r[expected + kind]]:
            raise ValueError('Vendor contribution loses or substitutes a literal pair')
    return [selected[r['address']]['original_' + kind] if r['address'] in selected else r for r in actual]


def allows_transition(address, original_function, original_origin, function, origin):
    plan = json.loads((ROOT / EVIDENCE).read_text())
    verify_plan(plan)
    return any(r['address'] == address and r['original_function'] == original_function
               and r['original_origin'] == original_origin and r['accepted_function'] == function
               and r['accepted_origin'] == origin for r in plan['functions'])


def verify_canonical(plan, evidence_only=False):
    for name in ['functions.csv', 'function-origins.csv']:
        actual = rows(name)
        historical_rows(plan, name, actual, evidence_only)
        if metadata_digest([r for r in actual if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('Vendor contribution changes unrelated canonical rows')
    fs, origins = ({r['address']: r for r in rows(n)} for n in ['functions.csv', 'function-origins.csv'])
    for u in plan['units']:
        for r in u['code'] + u['external_providers']:
            a = r['address']
            if a in WHOLE:
                continue
            if fs.get(a) != r['function'] or origins.get(a) != r['origin']:
                raise ValueError('Vendor contribution alters an independent provider or adds a candidate')


def linked(raw, fields, bindings, address):
    if len(fields) != len(bindings):
        raise ValueError('Vendor contribution drops an actual field')
    result = bytearray(raw)
    occupied = set()
    for f, b in zip(fields, bindings):
        at = f['offset']
        if any(i in occupied for i in range(at, at + 4)) or at < 0 or at + 4 > len(raw):
            raise ValueError('Vendor contribution invalid overlapping field')
        occupied.update(range(at, at + 4))
        dest = int(b['target_address'], 16)
        if f['type'] == 'REL32':
            if at < 1 or raw[at - 1] not in [0xe8, 0xe9]:
                raise ValueError('Vendor contribution unsupported actual relative opcode')
            value = (dest - address - at - 4) & 0xffffffff
        elif f['type'] == 'DIR32':
            value = dest
        else:
            raise ValueError('Vendor contribution unsupported actual field kind')
        struct.pack_into('<I', result, at, value)
    return result


def verify_native(plan):
    c = module('zeroing_target', 'compare-coff-function.py')
    coff = module('zeroing_coff', 'coff_data.py')
    extra = module('zeroing_sections', 'sdk_x3d_carriers.py')
    flow = module('zeroing_flow', 'sdk_image_carriers.py')
    runtime = module('zeroing_archive', 'verify-runtime-origins.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('Vendor contribution target differs')
    archives = {}
    for u in plan['units']:
        s = u['source']; archive = (ROOT / s['archive']).read_bytes()
        if digest(archive) != s['archive_sha256']:
            raise ValueError('Vendor contribution archive differs')
        archives[s['archive']] = {o: (n, b) for o, n, b in runtime.archive_members(archive)}
    catalog = {}
    with tempfile.TemporaryDirectory(prefix='th075-vendor-contribution-') as directory:
        obj = Path(directory) / 'original.obj'
        for p in plan['providers']:
            doc = json.loads((ROOT / p['path']).read_text()); record = doc
            if digest((ROOT / p['path']).read_bytes()) != p['path_sha256']:
                raise ValueError('Vendor contribution original provider manifest differs')
            for k in p['trail']:
                record = record[k]
            if record != p['record']:
                raise ValueError('Vendor contribution original provider record differs')
            path = '.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib' if 'sdk-' in p['path'] else '.tools/msvc710/Vc7/lib/libcmt.lib'
            name, body = archives[path][int(record['member_offset'])]
            if name != record['member']:
                raise ValueError('Vendor contribution original provider member differs')
            symbol = record.get('symbol', record.get('coff_symbol'))
            a = int(record.get('base', record.get('address', record.get('target_address'))), 16)
            comparison = record
            if symbol.startswith('?crc32@'):
                comparison = doc['anchors'][55]['comparison']
            if digest(body) != comparison.get('member_sha256', record.get('member_sha256')):
                raise ValueError('Vendor contribution original provider object differs')
            definition = next(r for r in coff.parse_symbols(body, c.coff_name)[1] if r['symbol'] == symbol and r['section'] > 0)
            if symbol == '___security_cookie':
                raw, fields, _ = extra.section_carrier(body, definition['section'], c, coff)
                bindings = record['relocations']
            else:
                obj.write_bytes(body)
                raw, fields = c.object_function(obj, symbol, int(record['size']))
                bindings = comparison.get('bindings', comparison.get('relocation_bindings', []))
            if len(raw) != int(record['size']) or digest(raw) != comparison['source_sha256']:
                raise ValueError('Vendor contribution original whole provider source differs')
            for f, b in zip(fields, bindings):
                for key in ['offset', 'type', 'symbol', 'addend']:
                    if f[key] != b[key]:
                        raise ValueError('Vendor contribution original typed provider field differs')
            native = c.pe_bytes_at(target, a, len(raw))
            if linked(raw, fields, bindings, a) != native or digest(native) != comparison['body_sha256']:
                raise ValueError('Vendor contribution whole external provider differs')
            catalog[symbol] = a
        for u in plan['units']:
            s = u['source']; name, body = archives[s['archive']][s['member_offset']]
            if name != s['member'] or digest(body) != s['member_sha256']:
                raise ValueError('Vendor contribution whole original object differs')
            actual = []
            for n in range(1, struct.unpack_from('<H', body, 2)[0] + 1):
                h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * (n - 1))
                if not h[3] or not h[4]:
                    continue
                raw, fields, source = extra.section_carrier(body, n, c, coff)
                actual.append(dict(source=source, raw_sha256=digest(raw), fields=fields))
            if actual != u['whole_source_inventory']:
                raise ValueError('Vendor contribution whole source/AUX/field inventory differs')
            bases = {r['source']['section']: int(r['address'], 16) for r in u['code'] + u['defining_data']}
            for r in u['defining_data']:
                raw, fields, _ = extra.section_carrier(body, r['source']['section'], c, coff)
                if fields or digest(raw) != r['source_sha256'] or raw != c.pe_bytes_at(target, int(r['address'], 16), r['size']):
                    raise ValueError('Vendor contribution whole defining data differs')
            for r in u['code']:
                a = int(r['address'], 16)
                raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
                if fields != r['fields'] or source != r['source'] or digest(raw) != r['source_sha256']:
                    raise ValueError('Vendor contribution whole code topology differs')
                calls, data = {}, {}
                bindings = []
                for f, b in zip(fields, r['bindings']):
                    base = bases[f['symbol_section']] if f['symbol_section'] > 0 else catalog[f['symbol']]
                    dest = (base + f['symbol_offset'] + f['addend']) & 0xffffffff
                    if (b['field'] != f or int(b['source_section_base'], 16) != base
                            or int(b['target_address'], 16) != dest):
                        raise ValueError('Vendor contribution field loses its actual defining source provider')
                    bindings.append(b)
                    (calls if f['type'] == 'REL32' else data)[a + f['offset']] = dest
                native = c.pe_bytes_at(target, a, r['size'])
                if (linked(raw, fields, bindings, a) != native or digest(native) != r['body_sha256']
                        or flow.flow(native, a, [0], fields, calls, data) != r['flow']):
                    raise ValueError('Vendor contribution complete unmasked code/CFG differs')
    return c, coff, extra, target


def cold_control(plan, c, coff, extra, target):
    common = module('zeroing_common', 'verify-sdk-row-deleting-helper-origins.py')
    inventory = module('zeroing_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    ctl = plan['ordinary_control']
    if digest((ROOT / ctl['source']).read_bytes()) != ctl['source_sha256']:
        raise ValueError('Vendor contribution genuine ordinary source differs')
    with tempfile.TemporaryDirectory(prefix='th075-zeroing-control-') as directory:
        obj = Path(directory) / 'zeroing.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['source']), str(obj), *ctl['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or common.included_headers(result.stdout + result.stderr) != ctl['headers']:
            raise ValueError('Vendor contribution cold control or header identity differs')
        body = obj.read_bytes()
        if inventory(body, c, coff) != ctl['emission']:
            raise ValueError('Vendor contribution complete ordinary emission differs')
        layout = next(r for r in ctl['emission'] if any(d['symbol'] == '?ZeroWordControlSizes@@3QBKB' for d in r['definitions']))
        raw, _ = coff.readonly_section(body, layout['section'], c.coff_name)
        if list(struct.unpack('<3I', raw)) != [64, 12, 4]:
            raise ValueError('Vendor contribution whole ordinary layout differs')
        for r in ctl['comparisons']:
            raw, fields = c.object_function(obj, r['symbol'])
            if (len(raw) != r['size'] or fields != r['fields'] or digest(raw) != r['source_sha256']
                    or raw != c.pe_bytes_at(target, int(r['address'], 16), r['size'])):
                raise ValueError('Vendor contribution genuine whole ordinary alternative differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    verify_plan(plan)
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Vendor contribution manifest bytes differ')
    verify_canonical(plan, args.evidence_only)
    c, coff, extra, target = verify_native(plan)
    cold_control(plan, c, coff, extra, target)
    module('zeroing_history', 'origin_history.py').replay(plan['history'])
    print('R260 origins OK: two inferred library leaves26; two complete source-order contributions29 functions1565/all42 fields and whole defining data340; ten original whole external providers; genuine cold ordinary14/12 alternatives retained; entire unchanged historical R155 cold replay; no source/ABI/exact credit.')


PLAN_SHA256 = 'ebd336595cbe15d8ac10edb9b5151256cee73fcc5a25b99c4fc832abeec9dd09'

if __name__ == '__main__':
    main()
