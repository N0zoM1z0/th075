#!/usr/bin/env python3
"""Cold-replay complete nested deque helper families and their actual typed parents."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
KEYS = {'0x004215C0': 45, '0x00421FC0': 19, '0x00422540': 27, '0x00422560': 83}
CONFIDENCE = 'complete-vc7-nested-helper-family-typed-parent-provenance'
MANIFEST_SHA256 = '26621b960371d69a3cc15d07a070cf0d65cc19cc1f96eba54fc5c95ed05cf7b3'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


PRIOR = module('nested_helper_prior', 'verify-nested-deque-size-origins.py')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest():
    return json.loads((ROOT / 'config/nested-deque-helper-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id'] != 'R151' or m['probe'] != 'probes/VC7NestedDequeHelpers.cpp'
            or m['profile'] != PRIOR.PRIOR.PROFILE or len(m['functions']) != 4
            or {r['address']: r['size'] for r in m['functions']} != KEYS
            or any(r['decision'] != 'library' for r in m['functions'])
            or len(m['solutions']) != 4 or len(m['rejected_families']) != 9
            or len(m['emission_code']) != 169 or sum(r['size'] for r in m['emission_code']) != 5537
            or len(m['headers']) != 27 or m['sdk_layout']['size'] != 32
            or m['sdk_layout']['values'] != [20, 20, 20, 20, 20, 8, 8, 4]
            or m['retained_manifest'] != 'nested-deque-size-origin-evidence.json'
            or m['retained_verifier'] != 'verify-nested-deque-size-origins.py'):
        raise ValueError('bounded complete nested helper/source-family inventory differs')
    counts = {'0x004215C0': 13, '0x00421FC0': 13, '0x00422540': 13, '0x00422560': 4}
    for r in m['functions']:
        if (len(r['shape_symbols']) != counts[r['address']] or r['shape_symbols'] != sorted(set(r['shape_symbols']))
                or r['retained_source']['address'] != r['address'] or r['retained_source']['size'] != r['size']):
            raise ValueError('nested helper loses whole source alternatives or retained own extent')
    positive = set()
    expected = set(KEYS) | {'0x00421B40', '0x00422020', '0x00422500', '0x00422520', '0x00422690'}
    for solution in m['solutions']:
        graph = {r['address']: r for r in solution['nodes']}
        if (len(graph) != 9 or len(solution['nodes']) != 9 or set(graph) != expected
                or sum(r['size'] for r in graph.values()) != 368
                or solution['root'] != graph['0x004215C0']['symbol']):
            raise ValueError('nested helper accepts an incomplete source-typed back/iterator graph')
        positive.add(solution['root'])
        for r in graph.values():
            if r['ledger_size'] != r['size']:
                raise ValueError('nested helper changes an original whole candidate extent')
            for b in r['relocations']:
                callee = graph.get(b['target_address'])
                if (b['type'] != 'REL32' or b['addend'] or callee is None or b['symbol'] != callee['symbol']):
                    raise ValueError('nested helper edge lacks its actual independently complete typed callee')
        calls = {'0x004215C0': [(23, '0x00421B40'), (30, '0x00422020'), (37, '0x00421FC0')],
                 '0x00421FC0': [(11, '0x00422560')], '0x00422540': [(17, '0x00422520')]}
        for key, required in calls.items():
            if [(b['offset'], b['target_address']) for b in graph[key]['relocations']] != required:
                raise ValueError('nested helper changes back/subtract/mutable-to-const operation identity')
        if (not graph['0x00422540']['symbol'].startswith('??Ziterator@')
                or not graph['0x00422540']['symbol'].endswith('QAEAAV012@H@Z')
                or not graph['0x00422520']['symbol'].startswith('??Yiterator@')
                or graph['0x00422560']['relocations']):
            raise ValueError('nested helper loses actual signed -= argument/reference return or width-dependent dereference')
    rejected = {r['root'] for r in m['rejected_families']}
    if (len(positive) != 4 or len(rejected) != 9 or positive & rejected
            or positive | rejected != set(m['functions'][0]['shape_symbols'])):
        raise ValueError('equal-shaped back families bypass full complete source graph resolution')
    for r in m['rejected_families']:
        owner = r['complete_const_owner']
        if (len(r['complete_source_symbols']) != 9 or r['root'] not in r['complete_source_symbols']
                or owner['symbol'] not in r['complete_source_symbols']
                or not owner['symbol'].startswith('??Dconst_iterator@')
                or owner['source_relocations']
                or not (owner['size_difference'] or owner['non_field_differences'])):
            raise ValueError('rejected type family loses its complete differing source owner')


def check_ledger(row, function, origin, evidence_only=False):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['calling_convention'] or function['signature']
            or function['match_percent'] != '0.00'):
        raise ValueError('nested helper grants source/private ABI/exact or changes own extent')
    if not evidence_only and (origin['origin'] != 'library' or origin['evidence_id'] != 'R151'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC7STL'
            or origin['confidence'] != CONFIDENCE or function['module'] != 'VC7STL'
            or function['owner'] != 'library' or function['status'] != 'excluded'
            or function['proposed_name'] != row['proposed_name']):
        raise ValueError('nested helper canonical complete library acceptance differs')


def verify_cold_object(m, path, comparison, record, coff, target):
    data = path.read_bytes()
    definitions = coff.parse_symbols(data, comparison.coff_name)[1]
    emitted = [d for d in definitions if d['section'] > 0 and d['type'] == 32 and d['storage'] == 2]
    if emitted != [r['source_definition'] for r in m['emission_code']]:
        raise ValueError('cold helper source gains or loses an ordinary emitted function')
    sources = {}
    fields_by_symbol = {}
    for row in m['emission_code']:
        size = record.complete_aux_section_size(data, row['symbol'], comparison.coff_name)
        source, fields = comparison.object_function(path, row['symbol'], size)
        if size != row['size'] or digest(source) != row['source_sha256'] or fields != row['fields']:
            raise ValueError('complete cold helper source/AUX/typed field inventory differs')
        sources[row['symbol']] = source
        fields_by_symbol[row['symbol']] = fields
    sdk = module('nested_helper_cfg', 'verify-sdk-origins.py')
    for solution in m['solutions']:
        # Every callee owns its entire independent source body in this graph.
        catalog = {r['symbol']: int(r['address'], 16) for r in solution['nodes']}
        for row in solution['nodes']:
            source = sources[row['symbol']]
            fields = fields_by_symbol[row['symbol']]
            actual = comparison.pe_bytes_at(target, int(row['address'], 16), row['size'])
            if (fields != row['source_relocations'] or digest(source) != row['source_sha256']
                    or digest(actual) != row['body_sha256']
                    or PRIOR.link_complete(source, fields, int(row['address'], 16), row['relocations'], catalog) != actual):
                raise ValueError('complete typed helper graph fails independent unmasked comparison')
            record.compare_complete_body(source, fields, actual, int(row['address'], 16), row['relocations'], comparison, sdk)
    for row in m['functions']:
        actual = comparison.pe_bytes_at(target, int(row['address'], 16), row['size'])
        for symbol in row['shape_symbols']:
            source, fields = sources[symbol], fields_by_symbol[symbol]
            omitted = {i for b in fields for i in range(b['offset'], b['offset'] + 4)}
            if len(source) != len(actual) or any(source[i] != actual[i] for i in range(len(actual)) if i not in omitted):
                raise ValueError('diagnostic full source shape family differs')
    actual = comparison.pe_bytes_at(target, 0x00422560, 83)
    for row in m['rejected_families']:
        owner = row['complete_const_owner']
        source = sources[owner['symbol']]
        if (fields_by_symbol[owner['symbol']] or len(source) != owner['size']
                or digest(source) != owner['source_sha256'] or len(source) - 83 != owner['size_difference']):
            raise ValueError('rejected full type-dependent source extent differs')
        difference = None if len(source) != 83 else sum(a != b for a, b in zip(source, actual))
        if difference != owner['non_field_differences'] or not (len(source) != 83 or difference):
            raise ValueError('whole rejected type family incorrectly gains source agreement')
    layout = m['sdk_layout']
    d = next(d for d in definitions if d['symbol'] == layout['symbol'])
    raw, section = coff.readonly_section(data, d['section'], comparison.coff_name)
    if (d != layout['source_definition'] or section != layout['source_section']
            or digest(raw) != layout['source_sha256'] or list(struct.unpack('<8I', raw)) != layout['values']):
        raise ValueError('helper SDK proof truncates or substitutes its complete defining layout section')
    covered = {r['source_definition']['section'] for r in m['emission_code']} | {d['section']}
    count = struct.unpack_from('<H', data, 2)[0]
    for index in range(count):
        header = struct.unpack_from('<8sIIIIIIHHI', data, 20 + index * 40)
        if header[3] and header[9] & 0xE0 and not header[0].startswith(b'.debug') and index + 1 not in covered:
            raise ValueError('helper source has an uncovered ordinary code/data carrier')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    m = manifest()
    verify_plan(m)
    if digest((ROOT / 'config/nested-deque-helper-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('reviewed complete nested helper metadata differs')
    comparison = module('nested_helper_target', 'compare-coff-function.py')
    record = module('nested_helper_record', 'verify-vendor-record-origins.py')
    coff = module('nested_helper_coff', 'coff_data.py')
    target = comparison.verified_target()
    if digest(target) != m['target_sha256'] or digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('helper target or real complete SDK source identity differs')
    functions = {r['address']: r for r in PRIOR.PRIOR.rows('functions.csv')}
    origins = {r['address']: r for r in PRIOR.PRIOR.rows('function-origins.csv')}
    retained = json.loads((ROOT / 'config' / m['retained_manifest']).read_text())
    for row in m['functions']:
        check_ledger(row, functions[row['address']], origins[row['address']], args.evidence_only)
        if row['retained_source'] not in retained['code']:
            raise ValueError('helper loses its independent complete R150 source context')
    for solution in m['solutions']:
        for row in solution['nodes']:
            key = row['address']
            if int(functions[key]['size']) != row['ledger_size']:
                raise ValueError('helper source graph changes an independently accepted extent')
            if key not in KEYS and (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']):
                raise ValueError('helper rewrites a prior independent anchor origin')
    for filename, expected in m['headers'].items():
        if digest((ROOT / filename).read_bytes()) != expected:
            raise ValueError('complete actual helper SDK header dependency differs')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts' / m['retained_verifier'])], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('full independent R150 cold source/code/data/EH provenance failed: ' + result.stderr[-1000:])
    scratch = ROOT / 'build/origin-nested-deque-helper-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary) / 'VC7NestedDequeHelpers.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *m['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or PRIOR.PRIOR.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('helper actual cold compiler/include provenance differs')
        verify_cold_object(m, path, comparison, record, coff, target)
    print('R151 origins OK: four complete nested deque helpers / 174 bytes; four independent full source-typed graphs / '
          '36 bodies / 1472 bytes; nine complete rejected type families retain actual differing const owners; '
          '169 cold SDK controls / 5537 bytes and whole 32-byte layout / 27 actual headers / no orphan carriers; '
          'full retained R150 code/data/EH/receiver proof; original element types and all prior owners/extents preserved; '
          'no count-wrapper/source/mapping/private ABI/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
