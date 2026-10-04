#!/usr/bin/env python3
"""Cold-replay complete deque endpoints, actual dispatch and category/operation alternatives."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_SHA256 = '9dc0301feef6a7847244ef93221fb171ae4e488b91cc77d794b69c921dd3a6d4'
CONFIDENCE = 'complete-vc7-endpoint-category-operation-typed-parent-and-alternative-provenance'
KEYS = {'0x00422B50': 35, '0x00422B80': 41, '0x00422CB0': 67, '0x00423680': 55,
        '0x004236C0': 43, '0x00422D60': 11, '0x004237E0': 27, '0x00423800': 17}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


COPY = module('endpoint_copy', 'verify-deque-copy-insert-origins.py')
PAIRED = COPY.PAIRED


def manifest():
    return json.loads((ROOT / 'config/deque-endpoint-dispatch-origin-evidence.json').read_text())


def verify_plan(m):
    prior = PAIRED.manifest(); PAIRED.verify_plan(prior)
    if (m['evidence_id'] != 'R159' or m['target_sha256'] != prior['target_sha256']
            or m['retained_manifest'] != 'config/paired-deque-producer-origin-evidence.json'
            or m['retained_sha256'] != PAIRED.MANIFEST_SHA256
            or m['copy_manifest'] != 'config/deque-copy-insert-origin-evidence.json' or m['copy_sha256'] != COPY.MANIFEST_SHA256
            or m['probe'] != 'probes/VC7DequeEndpointDispatch.cpp' or m['profile'] != prior['profile']
            or m['headers'] != dict(prior['headers'], **{prior['probe']: prior['probe_sha256']})
            or len(m['functions']) != 8 or {r['address']: r['size'] for r in m['functions']} != KEYS
            or len(m['controls']) != 12 or sum(r['size'] for r in m['controls']) != 2104
            or sum(len(r['bindings']) for r in m['controls']) != 76
            or len(m['emission']) != 197 or sum(r['size'] for r in m['emission']) != 12245
            or m['layout_values'] != [8,20,60,20,20,4,8,8,20,8,4,1,1,1,1,1,1,1]
            or m['layout'] not in m['emission'] or m['layout']['size'] != 72
            or [r['address'] for r in m['parents']] != ['0x00422A50', '0x00422D70']
            or [(r['method'], r['tag'], r['compared_address'], r['section']['size']) for r in m['negative_operations']] !=
               [('_Iter_cat', 'input_iterator_tag', '0x00422D60', 11), ('_Distance2', 'input_iterator_tag', '0x004237E0', 49), ('_Advance', 'bidirectional_iterator_tag', '0x00423800', 59)]
            or [r['address'] for r in m['legacy']] != ['0x004236F0', '0x00423740', '0x00423790']
            or any(r['origin']['origin'] != 'library' or r['origin']['evidence_id'] != 'R085' for r in m['legacy'])):
        raise ValueError('endpoint/dispatch loses entire source/parent/alternative/layout/legacy evidence')
    source = {r['symbol']: r for r in prior['code']}
    routes = {'0x00422B50': ['0x00422660'], '0x00422B80': ['0x00422660'],
              '0x00422CB0': ['0x00422D60', '0x00422D70'], '0x00423680': ['0x00422D60', '0x004237E0'],
              '0x004236C0': ['0x00422D60', '0x00423800'], '0x00422D60': [],
              '0x004237E0': ['0x004235F0'], '0x00423800': ['0x004239A0']}
    for row in m['functions']:
        original = source.get(row['symbol']); old, accepted = row['original_function'], row['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (row['decision'] != 'library' or original is None or (original['address'], original['size']) != (row['address'], row['size'])
                or [r['target_address'] for r in original['bindings']] != routes[row['address']]
                or old['status'] != 'unclassified' or row['original_origin']['origin'] != 'unknown'
                or row['original_origin']['disposition'] != 'review'
                or {k: v for k, v in old.items() if k not in mutable} != {k: v for k, v in accepted.items() if k not in mutable}
                or accepted['owner'] != 'library' or accepted['module'] != 'VC7STL' or accepted['status'] != 'excluded'
                or accepted['source_file'] or accepted['calling_convention'] or accepted['signature'] or accepted['match_percent'] != '0.00'
                or row['accepted_origin'] != dict(address=row['address'], origin='library', subsystem='VC7STL', disposition='exclude', confidence=CONFIDENCE, evidence_id='R159')):
            raise ValueError('endpoint/dispatch changes real source routes or grants false origin/extent/ABI/exact')
    copy_records = COPY.manifest()['functions']
    for parent in m['parents']:
        if parent['record'] not in copy_records or parent['record']['decision'] != 'library':
            raise ValueError('endpoint/dispatch parent lacks independently whole R158 source ownership')
        COPY.check_ledger(parent['record'], parent['function'], parent['origin'])
    if [r['role'] for r in m['controls']] != ['sdk-owner'] * 8 + ['whole-sdk-parent'] * 2 + ['byte-equal-category-alternative'] * 2:
        raise ValueError('endpoint/dispatch omits a whole owner/parent/category control')
    for control in m['controls']:
        old = source.get(control['retained_symbol'])
        if (old is None or any(control[k] != old[k] for k in ('address', 'size', 'body_sha256', 'source_sha256'))
                or control['section'] not in m['emission'] or control['source_definition'] not in control['section']['definitions']
                or control['size'] != control['section']['size'] or control['source_sha256'] != control['section']['source_sha256']
                or [(r['offset'], r['type'], r['addend'], r['target_address']) for r in control['bindings']] !=
                   [(r['offset'], r['type'], r['addend'], r['target_address']) for r in old['bindings']]):
            raise ValueError('endpoint/dispatch hides a full independent source owner or genuine field')
        if control['role'] != 'byte-equal-category-alternative' and control['source_definition']['symbol'] != old['source_definition']['symbol']:
            raise ValueError('endpoint/dispatch source identity changes its actual complete SDK owner')
        for a, b in zip(control['section']['fields'], old['section']['fields']):
            if a['symbol']['symbol'] != b['symbol']['symbol'] or any(a['symbol'][k] != b['symbol'][k] for k in ('offset', 'storage', 'type')):
                raise ValueError('endpoint/dispatch substitutes an unrelated actual SDK field owner')
    if (not m['controls'][10]['source_definition']['symbol'].startswith('??$_Iter_cat@UForwardCategoryTraitsObservation@@')
            or not m['controls'][11]['source_definition']['symbol'].startswith('??$_Iter_cat@UBidirectionalCategoryTraitsObservation@@')):
        raise ValueError('byte-equal category evidence loses different complete SDK traits')
    for alternative in m['negative_operations']:
        if (alternative['section'] not in m['emission'] or alternative['source_definition'] not in alternative['section']['definitions']
                or not alternative['source_definition']['symbol'].startswith('??$' + alternative['method'] + '@')
                or alternative['tag'] not in alternative['source_definition']['symbol']):
            raise ValueError('different category/operation control loses its full real SDK definition')


def accepted_snapshot(snapshot, function, origin):
    m = manifest()
    if PAIRED.digest((ROOT / 'config/deque-endpoint-dispatch-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('endpoint/dispatch follow-up evidence differs')
    verify_plan(m)
    row = next((r for r in m['functions'] if r['address'] == function['address']), None)
    return bool(row and snapshot == dict(function=row['original_function'], origin=row['original_origin'])
                and function == row['accepted_function'] and origin == row['accepted_origin'])


def check_ledger(row, function, origin, evidence_only=False):
    if evidence_only and function == row['original_function'] and origin == row['original_origin']:
        return
    if function != row['accepted_function'] or origin != row['accepted_origin']:
        raise ValueError('endpoint/dispatch canonical exact bounded acceptance differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = manifest(); verify_plan(m)
    for path, expected in [('config/deque-endpoint-dispatch-origin-evidence.json', MANIFEST_SHA256),
                           (m['retained_manifest'], m['retained_sha256']), (m['copy_manifest'], m['copy_sha256']), (m['probe'], m['probe_sha256'])]:
        if PAIRED.digest((ROOT / path).read_bytes()) != expected:
            raise ValueError('endpoint/dispatch immutable source/evidence differs: ' + path)
    c = module('endpoint_target', 'compare-coff-function.py'); coff = module('endpoint_coff', 'coff_data.py')
    extent = module('endpoint_extent', 'verify-vendor-record-origins.py'); cfg = module('endpoint_cfg', 'verify-authored-origins.py')
    target = c.verified_target()
    if PAIRED.digest(target) != m['target_sha256']:
        raise ValueError('endpoint/dispatch target differs')
    functions = {r['address']: r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('functions.csv')}
    origins = {r['address']: r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('function-origins.csv')}
    for row in m['functions']:
        check_ledger(row, functions[row['address']], origins[row['address']], args.evidence_only)
    for row in m['parents'] + m['legacy']:
        if functions[row['address']] != row['function'] or origins[row['address']] != row['origin']:
            raise ValueError('endpoint/dispatch alters original whole parents or prior R085 algorithms')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-deque-copy-insert-origins.py')], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('endpoint/dispatch independent whole retained cold evidence failed: ' + result.stderr[-1500:])
    print('retained copy/insertion: ' + result.stdout.splitlines()[-1], flush=True)
    prior = PAIRED.manifest(); catalog = {k: v for k, v in PAIRED.source_catalog(prior, []).items() if not k.startswith('$')}
    scratch = ROOT / 'build/origin-deque-endpoint-dispatch-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path = Path(dirname) / 'VC7DequeEndpointDispatch.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *m['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or COPY.ELEMENT.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('endpoint/dispatch actual cold source/header ownership differs')
        data = path.read_bytes(); inventory = PAIRED.BUFFER.inventory(data, c, coff)
        if inventory != m['emission']:
            raise ValueError('endpoint/dispatch entire ordinary emission differs or omits an owner')
        sections = {r['section']: r for r in inventory}
        for control in m['controls']:
            for definition in control['section']['definitions']:
                if definition['storage'] in (2, 3) and not definition['symbol'].startswith('.'):
                    address = int(control['address'], 16) + definition['offset']
                    if definition['symbol'] in catalog and catalog[definition['symbol']] != address:
                        raise ValueError('endpoint/dispatch source definition overrides independent whole ownership')
                    catalog[definition['symbol']] = address
        for control in m['controls']:
            section = sections[control['section']['section']]
            if section != control['section']:
                raise ValueError('endpoint/dispatch complete defining source owner differs')
            head = struct.unpack_from('<8sIIIIIIHHI', data, 20 + (section['section'] - 1) * 40); raw = data[head[4]:head[4] + head[3]]
            fields = [dict(offset=r['offset'], type=r['type'], symbol=r['symbol']['symbol'], addend=r['addend']) for r in section['fields']]
            actual = c.pe_bytes_at(target, int(control['address'], 16), control['size'])
            if (PAIRED.digest(raw) != control['source_sha256'] or PAIRED.digest(actual) != control['body_sha256']
                    or PAIRED.BUFFER.PRIOR.link_complete(raw, fields, int(control['address'], 16), control['bindings'], catalog) != actual
                    or extent.complete_aux_section_size(data, control['source_definition']['symbol'], c.coff_name) != control['size']):
                raise ValueError('endpoint/dispatch whole positive AUX owner fails actual unmasked field comparison')
            cfg.verify_body(actual, int(control['address'], 16))
        for alternative in m['negative_operations']:
            size = alternative['section']['size']; symbol = alternative['source_definition']['symbol']
            raw, _ = c.object_function(path, symbol)
            if len(raw) != size or extent.complete_aux_section_size(data, symbol, c.coff_name) != size:
                raise ValueError('different SDK operation/category lacks its whole positive own AUX')
            if alternative['method'] == '_Iter_cat':
                actual = c.pe_bytes_at(target, int(alternative['compared_address'], 16), 11)
                if raw == actual or len(raw) != len(actual):
                    raise ValueError('input category control is not a complete same-length differing body')
            elif size == KEYS[alternative['compared_address']]:
                raise ValueError('input/bidirectional operation control is falsely used as a target-prefix match')
        raw, _ = coff.readonly_section(data, m['layout']['section'], c.coff_name)
        if list(struct.unpack('<18I', raw)) != m['layout_values']:
            raise ValueError('endpoint/dispatch whole actual SDK/traits layout differs')
    print('R159 origins OK: eight whole SDK endpoint/dispatch owners / 296 bytes; twelve complete code controls / 2104 bytes and 76 unmasked genuine fields through whole R158 parents; forward/bidirectional category controls agree in all eleven bytes while input category differs at the same full size; complete input-distance / 49 and bidirectional-advance / 59 are different operations, not target-prefix comparisons; all 197 cold ordinary sections / 12245 bytes, actual headers and whole 72-byte layout; original R085 algorithms, source/runtime/authored policy and unrelated canonical evidence preserved; original element/category declarations, original source and live outcomes unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
