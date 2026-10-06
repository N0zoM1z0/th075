#!/usr/bin/env python3
"""Replay whole SDK stack contributions while retaining special-member ambiguity."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


PRIOR = module('sdk_stack_contribution_prior', 'verify-vendor-zeroing-contribution-origins.py')
digest = PRIOR.digest
metadata_digest = PRIOR.metadata_digest
rows = PRIOR.rows
linked = PRIOR.linked
EVIDENCE = 'config/sdk-stack-contribution-origin-evidence.json'
MANIFEST_SHA256 = 'fbfaecc9b9173df3a12aa307918212b8ef16a236603b42150d7ef55afb2eeaba'
PLAN_SHA256 = '0d2aa18db1099ab48f7abe880a6215f7d62afe276d9b8886b7aeb8fa1098019b'
WHOLE = {'0x0061FBE7': 8, '0x0061FD1A': 8}


def verify_plan(plan):
    if metadata_digest(plan) != PLAN_SHA256:
        raise ValueError('SDK stack immutable complete evidence differs')
    if plan['evidence_id'] != 'R261' or {r['address']: r['size'] for r in plan['functions']} != WHOLE:
        raise ValueError('SDK stack bounded getter scope differs')
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (r['original_origin']['origin'] != 'unknown' or r['accepted_origin']['origin'] != 'library'
                or not r['accepted_origin']['confidence'].startswith('inferred-')
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or any(new[k] for k in ['signature', 'calling_convention', 'source_file'])
                or new['match_percent'] != '0.00' or new['status'] != 'excluded'):
            raise ValueError('SDK stack gains unsupported source/ABI/extent/exact credit')
    verify_context(plan)


def verify_context(plan):
    primary = [r for r in plan['code'] if r['source']['section'] != 24]
    if (len(primary) != 11 or sum(r['size'] for r in primary) != 739
            or len(plan['code']) != 12 or len(plan['data']) != 1
            or sum(len(r['fields']) for r in plan['code'] + plan['data']) != 18):
        raise ValueError('SDK stack omits its whole primary/EH/data contribution')
    at = int(plan['span']['address'], 16)
    if [r['source']['section'] for r in primary] != list(range(3, 24, 2)):
        raise ValueError('SDK stack original source section order differs')
    for r in primary:
        if int(r['address'], 16) != at or r['size'] != r['source']['size']:
            raise ValueError('SDK stack source-order placement is truncated or discontinuous')
        at += r['size']
    if at != int(plan['span']['end'], 16) or at != 0x61fe0a:
        raise ValueError('SDK stack primary whole span differs')
    handler = next(r for r in plan['code'] if r['source']['section'] == 24)
    data = plan['data'][0]
    if (handler['address'], handler['size'], handler['roots'], data['address'], data['size']) != (
            '0x00656CB2', 20, [0, 10], '0x0066A8F4', 36):
        raise ValueError('SDK stack loses separate full two-root EH20/data36')
    protected = {r['function']['address']: r for r in plan['protected_pairs']}
    for a in ['0x0061FB37', '0x006200DA']:
        if protected[a]['origin']['origin'] != 'unknown':
            raise ValueError('SDK stack falsely credits an unresolved special-member provider')
    control = plan['controls'][1]
    comparisons = {(r['symbol'], r['address']): r for r in control['comparisons']}
    for prefix, address, size in [('??0', '0x0061FB27', 16), ('??1', '0x0061FB37', 14)]:
        implicit = comparisons[(prefix + 'ImplicitStackObservation@@QAE@XZ', address)]
        explicit = comparisons[(prefix + 'ExplicitStackObservation@@QAE@XZ', address)]
        if implicit['size'] != size or explicit['size'] != size or implicit['source_sha256'] != explicit['source_sha256']:
            raise ValueError('SDK stack erases coherent explicit/implicit ctor16-dtor14 equality')
    original = {r['symbol']: r for r in plan['controls'][0]['alternatives']}
    if (original['??0ImplicitStackObservation@@QAE@XZ']['size'],
            original['??1ImplicitStackObservation@@QAE@XZ']['size']) != (12, 5):
        raise ValueError('SDK stack crops original non-inlined implicit12/5 alternatives')


def historical_rows(plan, name, actual, evidence_only=False):
    """Return only the two independently checked literal predecessor rows."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    verify_plan(plan)
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['functions']}
    state = 'original_' if evidence_only else 'accepted_'
    for a, r in selected.items():
        if [q for q in actual if q['address'] == a] != [r[state + kind]]:
            raise ValueError('SDK stack loses, duplicates or substitutes a literal getter pair')
    return [selected[r['address']]['original_' + kind] if r['address'] in selected else r for r in actual]


def allows_transition(address, old_function, old_origin, function, origin):
    plan = json.loads((ROOT / EVIDENCE).read_text())
    verify_plan(plan)
    return any(r['address'] == address and r['original_function'] == old_function
               and r['original_origin'] == old_origin and r['accepted_function'] == function
               and r['accepted_origin'] == origin for r in plan['functions'])


def verify_canonical(plan, evidence_only=False):
    fs, origins = ({r['address']: r for r in rows(n)} for n in ['functions.csv', 'function-origins.csv'])
    for name in ['functions.csv', 'function-origins.csv']:
        actual = rows(name)
        historical_rows(plan, name, actual, evidence_only)
        if metadata_digest([r for r in actual if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('SDK stack changes unrelated canonical rows')
    for r in plan['code'] + plan['protected_pairs']:
        f = r['function']; a = f['address'] if f else r['address']
        if a not in WHOLE and (fs.get(a) != f or origins.get(a) != r['origin']):
            raise ValueError('SDK stack changes a provider or adds an auxiliary candidate')


def verify_native(plan):
    c = module('sdk_stack_target', 'compare-coff-function.py')
    coff = module('sdk_stack_coff', 'coff_data.py')
    extra = module('sdk_stack_sections', 'sdk_x3d_carriers.py')
    flow = module('sdk_stack_flow', 'sdk_graphics_carriers.py')
    rt = module('sdk_stack_archive', 'verify-runtime-origins.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('SDK stack target identity differs')
    for path, sha in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('SDK stack original manifest differs: ' + path)
    s = plan['source']; archives = {}
    for path, sha in [(s['archive'], s['archive_sha256']), (s['crt_archive'], s['crt_archive_sha256'])]:
        body = (ROOT / path).read_bytes()
        if digest(body) != sha:
            raise ValueError('SDK stack original archive differs')
        archives[path] = {o: (n, b) for o, n, b in rt.archive_members(body)}
    catalog = {}
    absolute = plan['absolute']
    name, body = archives[s['crt_archive']][absolute['member_offset']]
    if (name != absolute['member'] or digest(body) != absolute['member_sha256']
            or [d for d in coff.parse_symbols(body, c.coff_name)[1] if d['symbol'] == '__except_list' and d['section'] != 0] != [absolute['definition']]
            or absolute['definition']['section'] != -1 or absolute['definition']['offset']):
        raise ValueError('SDK stack FS displacement loses original absolute definition')
    catalog['__except_list'] = 0
    with tempfile.TemporaryDirectory(prefix='th075-sdk-stack-providers-') as directory:
        obj = Path(directory) / 'provider.obj'
        for p in plan['providers']:
            doc = json.loads((ROOT / p['path']).read_text()); record = doc
            for k in p['trail']:
                record = record[k]
            if record != p['record']:
                raise ValueError('SDK stack original full provider record differs')
            if p['trail'][0] == 'anchors':
                r = record['record']; q = record['comparison']; a = int(record['address'], 16)
                archive = s['crt_archive']
                bindings = q['bindings']; expected_size = q['size']; expected_sha = q['source_sha256']; symbol = q['symbol']
                member_sha = q['member_sha256']; expected_native_sha = q['body_sha256']
            elif p['trail'][0] == 'sections':
                r = record; a = int(r['base'], 16); archive = s['archive']
                bindings = r['bindings']; expected_size = r['size']; expected_sha = r['source_sha256']; symbol = r['symbol']
                member_sha = r['member_sha256']; expected_native_sha = r['body_sha256']
            else:
                r = record['record']; a = int(r['address'], 16); archive = s['archive']
                bindings = r['fields']; expected_size = r['size']; expected_sha = r['source_sha256']; symbol = r['symbol']
                member_sha = r['member_sha256']; expected_native_sha = r['body_sha256']
            name, body = archives[archive][int(r['member_offset'])]
            if name != r['member'] or digest(body) != member_sha:
                raise ValueError('SDK stack original provider object differs')
            definition = next(d for d in coff.parse_symbols(body, c.coff_name)[1] if d['symbol'] == symbol and d['section'] > 0)
            if p['trail'][0] == 'data_anchors':
                raw, fields, source = extra.section_carrier(body, definition['section'], c, coff)
                if definition != r['definition']:
                    raise ValueError('SDK stack real whole vtable definition differs')
            else:
                obj.write_bytes(body)
                raw, fields = c.object_function(obj, symbol, expected_size)
            if len(raw) != expected_size or digest(raw) != expected_sha or len(fields) != len(bindings):
                raise ValueError('SDK stack original whole provider source/fields differ')
            for f, b in zip(fields, bindings):
                keys = ['offset', 'symbol', 'type_id'] if p['trail'][0] == 'data_anchors' else ['offset', 'symbol', 'type', 'addend']
                if any(f[k] != b[k] for k in keys):
                    raise ValueError('SDK stack original typed provider field differs')
            native = c.pe_bytes_at(target, a, expected_size)
            if linked(raw, fields, bindings, a) != native or digest(native) != expected_native_sha:
                raise ValueError('SDK stack complete unmasked provider differs')
            catalog[symbol] = a
    name, body = archives[s['archive']][s['member_offset']]
    if name != s['member'] or digest(body) != s['member_sha256']:
        raise ValueError('SDK stack original whole source object differs')
    actual = []
    for n in range(1, struct.unpack_from('<H', body, 2)[0] + 1):
        h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * (n - 1))
        if not h[3] or not h[4]:
            continue
        raw, fields, source = extra.section_carrier(body, n, c, coff)
        actual.append(dict(source=source, fields=fields, source_sha256=digest(raw)))
    if actual != s['inventory']:
        raise ValueError('SDK stack whole original source/AUX/COMDAT/field inventory differs')
    bases = {r['source']['section']: int(r['address'], 16) for r in plan['code'] + plan['data']}
    for r in plan['code'] + plan['data']:
        a = int(r['address'], 16)
        raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
        if fields != r['fields'] or source != r['source'] or digest(raw) != r['source_sha256']:
            raise ValueError('SDK stack full original defining section differs')
        calls, data = {}, {}
        for f, b in zip(fields, r['bindings']):
            base = bases[f['symbol_section']] + f['symbol_offset'] if f['symbol_section'] > 0 else catalog[f['symbol']]
            dest = (base + f['addend']) & 0xffffffff
            if b['field'] != f or int(b['target_address'], 16) != dest:
                raise ValueError('SDK stack source field loses its actual complete defining provider')
            (calls if f['type'] == 'REL32' else data)[a + f['offset']] = dest
        native = c.pe_bytes_at(target, a, r['size'])
        if linked(raw, fields, r['bindings'], a) != native or digest(native) != r['body_sha256']:
            raise ValueError('SDK stack complete unmasked code/data differs')
        if r in plan['code'] and flow.flow(native, a, r['roots'], fields, calls, data, None, None) != r['flow']:
            raise ValueError('SDK stack whole native primary/two-root compiler CFG differs')
    eh = module('sdk_stack_eh', 'compiler_eh.py')
    if plan['frame'] not in rows('compiler-eh-frames.csv'):
        raise ValueError('SDK stack original one-state lifetime frame differs')
    eh.verify_frame(plan['frame'], lambda a, n: c.pe_bytes_at(target, a, n), lambda a, n: c.pe_bytes_at(target, a, n), {int(r['address'], 16) for r in rows('functions.csv')}, {catalog['__EH_prolog']})
    return c, coff, extra, target


def cold_controls(plan, c, coff, extra, target):
    common = module('sdk_stack_observation_common', 'verify-sdk-row-deleting-helper-origins.py')
    inventory = module('sdk_stack_observation_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    for ctl in plan['controls']:
        if digest((ROOT / ctl['source']).read_bytes()) != ctl['source_sha256']:
            raise ValueError('SDK stack genuine ordinary source differs')
        with tempfile.TemporaryDirectory(prefix='th075-sdk-stack-control-') as directory:
            obj = Path(directory) / 'stack.obj'
            result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['source']), str(obj), *ctl['profile']], cwd=ROOT, capture_output=True, text=True)
            if result.returncode or common.included_headers(result.stdout + result.stderr) != ctl['headers']:
                raise ValueError('SDK stack cold compiler/header identity differs')
            body = obj.read_bytes()
            if inventory(body, c, coff) != ctl['emission']:
                raise ValueError('SDK stack entire ordinary emission differs')
            for r in ctl['sections']:
                raw, fields, source = extra.section_carrier(body, r['section'], c, coff)
                if (common.SOURCE.BASE.canonical_source(source, body) != r['source']
                        or fields != r['fields'] or digest(raw) != r['source_sha256']):
                    raise ValueError('SDK stack whole ordinary AUX/fields/code-data differs')
            for r in ctl['comparisons']:
                raw, fields = c.object_function(obj, r['symbol'], r['size'])
                if (len(raw) != r['size'] or digest(raw) != r['source_sha256'] or fields != [{k: v for k, v in f.items() if k in ['offset', 'type_id', 'type', 'symbol', 'addend', 'local_symbol_offset']} for f in r['fields']]
                        or linked(raw, fields, r['bindings'], int(r['address'], 16)) != c.pe_bytes_at(target, int(r['address'], 16), r['size'])):
                    raise ValueError('SDK stack complete ordinary lifetime/getter alternative differs')
            raw, _ = coff.readonly_section(body, ctl['layout']['section'], c.coff_name)
            if list(struct.unpack('<8I', raw)) != ctl['layout']['values']:
                raise ValueError('SDK stack complete observation sizes/offsets differ')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    verify_plan(plan)
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('SDK stack manifest bytes differ')
    verify_canonical(plan, args.evidence_only)
    c, coff, extra, target = verify_native(plan)
    cold_controls(plan, c, coff, extra, target)
    module('sdk_stack_history', 'origin_history.py').replay(plan['history'])
    print('R261 origins OK: two inferred library error read/reset8 leaves16; complete source-order11 primary functions739 plus separate two-root EH20/data36/all18 fields; original providers128/vtable28 and absolute FS definition; two cold full ordinary profiles196/203, coherent explicit/implicit ctor16-dtor14 ambiguity preserved; entire unchanged historical R195 cold CLI; no source/ABI/exact credit.')


if __name__ == '__main__':
    main()
