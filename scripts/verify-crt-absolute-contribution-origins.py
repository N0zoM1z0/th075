#!/usr/bin/env python3
"""Replay the complete CRT abs contribution while retaining abs/labs alternatives."""
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


PRIOR = module('crt_absolute_prior', 'verify-vendor-zeroing-contribution-origins.py')
digest, metadata_digest, rows = PRIOR.digest, PRIOR.metadata_digest, PRIOR.rows
EVIDENCE = 'config/crt-absolute-contribution-origin-evidence.json'
MANIFEST_SHA256 = 'f190d6038b0439b8092248069e49a63566514a346d4c5b98959ccd062e53ca0f'
PLAN_SHA256 = 'a64576b784bfc66ee395a5824a325118cdf280dd12fb802927a35d0f1ab1afe7'
WHOLE = {'0x00641DAA': 11}


def verify_context(plan):
    source = plan['source']; code = plan['code']
    if (source['member_offset'] != 1282072 or len(source['inventory']) != 8
            or sum(r['source']['size'] for r in source['inventory']) != 642
            or [(r['source']['section'], r['symbol'], r['address'], r['size']) for r in code]
            != [(2, '_abs', '0x00641DAA', 11), (5, '__abs64', '0x00641DB5', 28)]):
        raise ValueError('CRT abs loses its whole original two-function contribution')
    at = int(plan['span']['address'], 16)
    for r in code:
        aux = next(a for a in r['source']['aux_records'] if a['symbol'] == '.text')
        if (int(r['address'], 16) != at or r['size'] != r['source']['size']
                or r['source']['flags'] != 0x60101020 or bytes.fromhex(aux['aux_hex'])[14] != 1
                or r['fields'] or r['flow']['whole_size'] != r['size']
                or r['flow']['returns'] != [dict(offset=r['size'] - 1, cleanup=0)]):
            raise ValueError('CRT abs source-order extent/COMDAT/complete exit differs')
        at += r['size']
    if (plan['span']['order'] != [2, 5] or at != 0x641dd1 or plan['span']['size'] != 39
            or at != int(plan['span']['end'], 16) or code[1]['function'] is not None
            or code[1]['origin'] is not None):
        raise ValueError('CRT abs auxiliary28 is cropped or gains an invented canonical candidate')
    ctl = plan['control']
    if (len(ctl['emission']) != 5 or sum(r['size'] for r in ctl['emission']) != 84
            or ctl['layout'] != [4, 4, 8] or len(ctl['comparisons']) != 4
            or {(r['symbol'], r['address'], r['size']) for r in ctl['comparisons']} != {
                (s, a, 11) for s in ['?OrdinaryAbsoluteInt@@YAHH@Z', '?OrdinaryAbsoluteLong@@YAJJ@Z']
                for a in ['0x00641DAA', '0x00641FB8']}
            or [(r['size'], r['target_size'], r['whole_equal'], r['whole_same_size_differences'])
                for r in ctl['alternatives']] != [(28, 28, False, 4), (22, 28, False, None)]):
        raise ValueError('CRT abs loses whole ordinary int/long positives or wide28/public22 negatives')
    if any(r['origin']['origin'] != 'unknown' for r in plan['protected_pairs']):
        raise ValueError('CRT abs resolves an independent labs/overload/lifetime ambiguity')
    if [(r['evidence_id'], r['commit']) for r in plan['history']] != [('R129', plan['baseline_commit']), ('R163', plan['baseline_commit'])]:
        raise ValueError('CRT abs substitutes an old full unknown snapshot or drops its original proof')


def verify_plan(plan):
    if metadata_digest(plan) != PLAN_SHA256:
        raise ValueError('CRT abs immutable complete evidence differs')
    if plan['evidence_id'] != 'R263' or {r['address']: r['size'] for r in plan['functions']} != WHOLE:
        raise ValueError('CRT abs bounded single-candidate scope differs')
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (r['original_origin']['origin'] != 'unknown' or r['accepted_origin']['origin'] != 'library'
                or not r['accepted_origin']['confidence'].startswith('inferred-')
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or any(new[k] for k in ['signature', 'calling_convention', 'source_file'])
                or new['match_percent'] != '0.00' or new['status'] != 'excluded'):
            raise ValueError('CRT abs gains unsupported source/type/ABI/extent/exact credit')
    verify_context(plan)


def historical_rows(plan, name, actual, evidence_only=False):
    """Expose only the single independently validated literal predecessor pair."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    verify_plan(plan)
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['functions']}
    state = 'original_' if evidence_only else 'accepted_'
    for a, r in selected.items():
        if [q for q in actual if q['address'] == a] != [r[state + kind]]:
            raise ValueError('CRT abs loses, duplicates or substitutes a literal selected pair')
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
            raise ValueError('CRT abs changes unrelated canonical rows')
    fs, origins = ({r['address']: r for r in rows(n)} for n in ['functions.csv', 'function-origins.csv'])
    if '0x00641DB5' in fs or '0x00641DB5' in origins:
        raise ValueError('CRT abs adds an auxiliary candidate')
    for r in plan['protected_pairs']:
        a = r['function']['address']
        if fs.get(a) != r['function'] or origins.get(a) != r['origin']:
            raise ValueError('CRT abs changes an independent protected pair')


def inventory(body, c, coff, extra):
    actual = []
    for n in range(1, struct.unpack_from('<H', body, 2)[0] + 1):
        h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * (n - 1))
        if h[3] and h[4]:
            raw, fields, source = extra.section_carrier(body, n, c, coff)
            actual.append(dict(source=source, fields=fields, source_sha256=digest(raw)))
    return actual


def verify_native(plan):
    c = module('crt_absolute_target', 'compare-coff-function.py')
    coff = module('crt_absolute_coff', 'coff_data.py')
    extra = module('crt_absolute_sections', 'sdk_x3d_carriers.py')
    flow = module('crt_absolute_flow', 'sdk_graphics_carriers.py')
    rt = module('crt_absolute_archive', 'verify-runtime-origins.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('CRT abs target identity differs')
    for path, sha in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('CRT abs retained original proof differs: ' + path)
    source = plan['source']; archive = (ROOT / source['archive']).read_bytes()
    if digest(archive) != source['archive_sha256']:
        raise ValueError('CRT abs source archive differs')
    members = {o: (n, b) for o, n, b in rt.archive_members(archive)}
    name, body = members[source['member_offset']]
    if name != source['member'] or digest(body) != source['member_sha256'] or inventory(body, c, coff, extra) != source['inventory']:
        raise ValueError('CRT abs full original source/AUX/field inventory differs')
    with tempfile.TemporaryDirectory(prefix='th075-crt-abs-source-') as directory:
        obj = Path(directory) / 'Abs.obj'; obj.write_bytes(body)
        for r in plan['code']:
            raw, fields, src = extra.section_carrier(body, r['source']['section'], c, coff)
            own, own_fields = c.object_function(obj, r['symbol'])
            a = int(r['address'], 16); native = c.pe_bytes_at(target, a, r['size'])
            if (src != r['source'] or fields != r['fields'] or own != raw or own_fields
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                    or raw != native or digest(native) != r['body_sha256']
                    or flow.flow(native, a, [0], fields, {}, {}, None, None) != r['flow']):
                raise ValueError('CRT abs complete auxiliary/source/native CFG comparison differs')
    for survey in plan['survey']['archives']:
        archive = (ROOT / survey['archive']).read_bytes()
        if digest(archive) != survey['archive_sha256']:
            raise ValueError('CRT abs alternate archive differs')
        found = []; scanned = 0
        for off, name, body in rt.archive_members(archive):
            if len(body) < 20 or body[:2] != b'\x4c\x01':
                continue
            scanned += 1
            for n in range(1, struct.unpack_from('<H', body, 2)[0] + 1):
                h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * (n - 1))
                if not h[9] & 32 or h[3] != 11 or h[7]:
                    continue
                raw = body[h[4]:h[4] + h[3]]
                matches = [f'0x{a:08X}' for a in [0x641daa, 0x641fb8] if raw == c.pe_bytes_at(target, a, 11)]
                if matches:
                    raw, fields, src = extra.section_carrier(body, n, c, coff)
                    found.append(dict(member_offset=off, member=name, member_sha256=digest(body), source=src,
                                      fields=fields, source_sha256=digest(raw), targets=matches,
                                      inventory=inventory(body, c, coff, extra)))
        if found != survey['matches'] or scanned != survey['scanned_coff_members']:
            raise ValueError('CRT abs loses complete original abs/labs/source alternatives')
    return c, coff, extra, target


def cold_control(plan, c, coff, extra, target):
    ctl = plan['control']
    common = module('crt_absolute_headers', 'verify-sdk-row-deleting-helper-origins.py')
    ordinary_inventory = module('crt_absolute_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    flow = module('crt_absolute_ordinary_flow', 'sdk_graphics_carriers.py')
    if digest((ROOT / ctl['source']).read_bytes()) != ctl['source_sha256']:
        raise ValueError('CRT abs ordinary control source differs')
    with tempfile.TemporaryDirectory(prefix='th075-crt-abs-control-') as directory:
        obj = Path(directory) / 'Absolute.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['source']), str(obj), *ctl['profile']],
                                cwd=ROOT, capture_output=True, text=True, check=True)
        if common.included_headers(result.stdout + result.stderr) != ctl['headers']:
            raise ValueError('CRT abs actual ordinary included headers differ')
        body = obj.read_bytes()
        if ordinary_inventory(body, c, coff) != ctl['emission']:
            raise ValueError('CRT abs whole ordinary cold emission differs')
        definitions = {}; values = None
        for r in ctl['sections']:
            raw, fields, src = extra.section_carrier(body, r['section'], c, coff)
            if (common.SOURCE.BASE.canonical_source(src, body) != r['source']
                    or fields != r['fields'] or digest(raw) != r['source_sha256']):
                raise ValueError('CRT abs complete ordinary source section differs')
            for definition in src['definitions']:
                if definition['type'] == 32:
                    definitions[definition['symbol']] = (definition, raw, fields)
                if definition['symbol'] == '?AbsoluteValueLayout@@3QBKB':
                    values = list(struct.unpack('<3I', raw))
        for r in ctl['comparisons']:
            definition, raw, fields = definitions[r['symbol']]
            if (definition != r['definition'] or fields != r['fields'] or fields or len(raw) != r['size']
                    or digest(raw) != r['source_sha256'] or raw != c.pe_bytes_at(target, int(r['address'], 16), r['size'])):
                raise ValueError('CRT abs genuine complete int/long11 positive differs')
        for r in ctl['alternatives']:
            definition, raw, fields = definitions[r['symbol']]
            native = c.pe_bytes_at(target, int(r['target'], 16), r['target_size'])
            instructions = [dict(offset=i.address, mnemonic=i.mnemonic, operands=i.op_str) for i in flow.instructions(raw, 0, len(raw))]
            differences = sum(x != y for x, y in zip(raw, native)) if len(raw) == len(native) else None
            if (definition != r['definition'] or len(raw) != r['size'] or fields != r['fields']
                    or digest(raw) != r['source_sha256'] or instructions != r['instructions']
                    or digest(native) != r['target_sha256'] or (raw == native) != r['whole_equal']
                    or differences != r['whole_same_size_differences']):
                raise ValueError('CRT abs crops or erases whole wide28/public22 alternatives')
        if values != ctl['layout'] or len(definitions) != 4:
            raise ValueError('CRT abs complete ordinary definition/layout absent')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('CRT abs original complete manifest differs')
    verify_plan(plan)
    verify_canonical(plan, args.evidence_only)
    c, coff, extra, target = verify_native(plan)
    history = module('crt_absolute_history', 'origin_history.py')
    for item in plan['history']:
        history.replay(item)
    cold_control(plan, c, coff, extra, target)
    print('R263 origins OK:one inferred-library abs11;whole original source-order abs11/abs64 auxiliary28 contribution39;'
          'all eight initialized source inventory sections642/real definitions/AUX/fields;'
          'original abs/labs whole alternatives and separate labs11 remain unknown;'
          'four cold int/long positives44,whole wide28/four differences and intrinsic public22 retained,'
          'all five ordinary sections84/one header/layout12;entire unchanged historical R129/R128 and R163 cold graphs;'
          'no auxiliary candidate/source/ABI/mapping/exact credit;original spelling/type remains provisional.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
