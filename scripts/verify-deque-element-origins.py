#!/usr/bin/env python3
"""Cold-replay complete deque element operations, ordinary alternatives and typed parents."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import importlib.util

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_SHA256 = '889339904d8c194624a5b2ad59335cbefd96eb2f6ad6ae5545bdd91bcbee89ab'
KEYS = {'0x004228A0': 20, '0x004228C0': 108, '0x0042E4D0': 20, '0x0042E4F0': 65}
CONFIDENCE = 'complete-vc7-element-operation-typed-parent-and-ordinary-source-provenance'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


PAIRED = module('element_paired', 'verify-paired-deque-producer-origins.py')


def manifest():
    return json.loads((ROOT / 'config/deque-element-origin-evidence.json').read_text())


def verify_plan(m):
    prior = PAIRED.manifest()
    PAIRED.verify_plan(prior)
    if (m['evidence_id'] != 'R157' or m['target_sha256'] != prior['target_sha256']
            or m['retained_manifest'] != 'config/paired-deque-producer-origin-evidence.json'
            or m['retained_sha256'] != PAIRED.MANIFEST_SHA256
            or m['probe'] != 'probes/VC7DequeElementAlternatives.cpp' or m['profile'] != prior['profile']
            or m['retained_layout'] != prior['layout'] or len(m['headers']) != 28
            or {k: v for k, v in m['headers'].items() if k.startswith('.tools/')} != prior['headers']
            or m['headers'].get(prior['probe']) != prior['probe_sha256']
            or len(m['functions']) != 4 or {r['address']: r['size'] for r in m['functions']} != KEYS
            or len(m['parents']) != 4 or len(m['controls']) != 6
            or sum(r['size'] for r in m['controls']) != 276
            or sum(len(r['bindings']) for r in m['controls']) != 14
            or len(m['emission']) != 193 or sum(r['size'] for r in m['emission']) != 12193):
        raise ValueError('element evidence loses complete bounded source/ordinary/state/parent provenance')
    roles = [('0x004228A0', '0x00421EE0', '_Allocate', 'QueueRecordObservation', 'AllocateQueueOrdinary'),
             ('0x004228C0', '0x00421F00', '_Construct', 'QueueRecordObservation', 'ConstructQueueOrdinary'),
             ('0x0042E4D0', '0x0042E000', '_Allocate', 'FileRecordObservation', 'AllocateFileOrdinary'),
             ('0x0042E4F0', '0x0042E020', '_Construct', 'FileRecordObservation', 'ConstructFileOrdinary')]
    for row, parent, control, role in zip(m['functions'], m['parents'], m['controls'], roles):
        address, owner, method, typename, ordinary = role
        if (row['address'], row['parent'], row['method'], row['observation_type']) != (address, owner, method, typename):
            raise ValueError('element parent/source scalar versus pointer operation changes')
        original = next(r for r in prior['code'] if r['address'] == address)
        root = next(r for r in prior['functions'] if r['address'] == owner)
        caller = next(r for r in prior['code'] if r['symbol'] == root['symbol'])
        if (row['decision'] != 'library' or row['symbol'] != original['symbol']
                or not row['symbol'].startswith('??$' + method + '@U' + typename + '@@')
                or control['address'] != address or control['retained_symbol'] != row['symbol']
                or row['ordinary_symbol'] != control['source_definition']['symbol']
                or not row['ordinary_symbol'].startswith('?' + ordinary + '@')
                or parent['address'] != owner or parent['record'] != root
                or [f['target_address'] for f in caller['bindings']] != [address]):
            raise ValueError('element provenance lacks its actual complete SDK typed parent')
        PAIRED.check_ledger(root, parent['function'], parent['origin'])
        old = row['original_function']; accepted = row['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (old['address'] != address or int(old['size']) != row['size'] or old['span_end'] != row['span_end']
                or old['status'] != 'unclassified' or row['original_origin']['origin'] != 'unknown'
                or row['original_origin']['disposition'] != 'review'
                or {k: v for k, v in old.items() if k not in mutable} != {k: v for k, v in accepted.items() if k not in mutable}
                or accepted['owner'] != 'library' or accepted['module'] != 'VC7STL' or accepted['status'] != 'excluded'
                or accepted['source_file'] or accepted['calling_convention'] or accepted['signature']
                or accepted['match_percent'] != '0.00'
                or row['accepted_origin'] != dict(address=address, origin='library', subsystem='VC7STL', disposition='exclude', confidence=CONFIDENCE, evidence_id='R157')):
            raise ValueError('element transition grants unrelated extent/source/ABI/exact credit')
    for control in m['controls']:
        old = next((r for r in prior['code'] + prior['state_data'] if r['symbol'] == control['retained_symbol']), None)
        if (old is None or any(control[k] != old[k] for k in ('address', 'size', 'body_sha256', 'source_sha256'))
                or control['section'] not in m['emission'] or control['source_definition'] not in control['section']['definitions']
                or control['size'] != control['section']['size'] or control['source_sha256'] != control['section']['source_sha256']
                or [(r['offset'], r['type'], r['addend'], r['target_address']) for r in control['bindings']] !=
                   [(r['offset'], r['type'], r['addend'], r['target_address']) for r in old['bindings']]):
            raise ValueError('ordinary alternative loses its whole independent SDK owner or actual field')
        for new, original in zip(control['section']['fields'], old['section']['fields']):
            a, b = new['symbol'], original['symbol']
            if any(a[k] != b[k] for k in ('offset', 'type', 'storage')):
                raise ValueError('ordinary field changes the real source owner role')
            if a['symbol'] != b['symbol'] and not (a['symbol'].startswith('$') and b['symbol'].startswith('$') or
                    a['symbol'].startswith('__ehhandler$?ConstructQueueOrdinary@') and b['symbol'].startswith('__ehhandler$??$_Construct@UQueueRecordObservation@@')):
                raise ValueError('ordinary alternative binds an unrelated SDK/runtime operation')
    if [(r['address'], r['size']) for r in m['controls'][4:]] != [('0x00655690', 27), ('0x006688D8', 36)]:
        raise ValueError('ordinary queue alternative hides full cleanup/dispatch or embedded FuncInfo state')


def accepted_snapshot(snapshot, function, origin):
    """Permit only the hash-pinned R157 transition of four original R156 snapshots."""
    m = manifest()
    if PAIRED.digest((ROOT / 'config/deque-element-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('element follow-up manifest differs')
    verify_plan(m)
    row = next((r for r in m['functions'] if r['address'] == function['address']), None)
    return bool(row and snapshot == dict(function=row['original_function'], origin=row['original_origin'])
                and function == row['accepted_function'] and origin == row['accepted_origin'])


def check_ledger(row, function, origin, evidence_only=False):
    if evidence_only and function == row['original_function'] and origin == row['original_origin']:
        return
    if function != row['accepted_function'] or origin != row['accepted_origin']:
        raise ValueError('element canonical acceptance differs or grants false evidence')


def included_headers(output):
    sdk = []; local = {}
    for line in output.splitlines():
        if 'Note: including file:' in line:
            path = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
            if path[:3].lower() == 'z:/' and path[2:] == str(ROOT / 'probes/VC7PairedDequeProducers.cpp'):
                local['probes/VC7PairedDequeProducers.cpp'] = PAIRED.digest(Path(path[2:]).read_bytes())
                continue
        sdk.append(line)
    return dict(PAIRED.BUFFER.PRIOR.PRIOR.included_headers('\n'.join(sdk)), **local)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = manifest(); verify_plan(m)
    if PAIRED.digest((ROOT / 'config/deque-element-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('element metadata differs')
    c = module('element_target', 'compare-coff-function.py'); coff = module('element_coff', 'coff_data.py')
    extent = module('element_extent', 'verify-vendor-record-origins.py')
    target = c.verified_target()
    if PAIRED.digest(target) != m['target_sha256'] or PAIRED.digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('element target/natural source differs')
    functions = {r['address']: r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('functions.csv')}
    origins = {r['address']: r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('function-origins.csv')}
    for row in m['functions']:
        check_ledger(row, functions[row['address']], origins[row['address']], args.evidence_only)
    for row in m['parents']:
        if functions[row['address']] != row['function'] or origins[row['address']] != row['origin']:
            raise ValueError('element original typed parent metadata differs')
        PAIRED.check_ledger(row['record'], functions[row['address']], origins[row['address']])
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-paired-deque-producer-origins.py')], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('element complete independent paired source/code/data/EH/runtime replay failed: ' + result.stderr[-1500:])
    print('retained paired: ' + result.stdout.splitlines()[-1], flush=True)
    prior = PAIRED.manifest()
    if PAIRED.digest((ROOT / m['retained_manifest']).read_bytes()) != m['retained_sha256']:
        raise ValueError('element retained entire source-family evidence differs')
    # Compiler-local labels belong to their own COFF object; their numbers
    # may recur with different meanings in this independently compiled control.
    catalog = {k: v for k, v in PAIRED.source_catalog(prior, []).items() if not k.startswith('$')}
    scratch = ROOT / 'build/origin-deque-element-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path = Path(dirname) / 'VC7DequeElementAlternatives.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *m['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('element complete cold source/header ownership differs')
        data = path.read_bytes(); inventory = PAIRED.BUFFER.inventory(data, c, coff)
        if inventory != m['emission']:
            raise ValueError('element entire ordinary emission differs or has an omitted owner')
        sections = {r['section']: r for r in inventory}
        for control in m['controls']:
            for definition in control['section']['definitions']:
                if definition['storage'] in (2, 3) and not definition['symbol'].startswith('.'):
                    address = int(control['address'], 16) + definition['offset']
                    if definition['symbol'] in catalog and catalog[definition['symbol']] != address:
                        raise ValueError('ordinary source definition overrides independent provenance')
                    catalog[definition['symbol']] = address
        for control in m['controls']:
            section = sections[control['section']['section']]
            if section != control['section']:
                raise ValueError('ordinary complete defining code/data carrier differs')
            head = struct.unpack_from('<8sIIIIIIHHI', data, 20 + (section['section'] - 1) * 40)
            raw = data[head[4]:head[4] + head[3]]
            fields = [dict(offset=r['offset'], type=r['type'], symbol=r['symbol']['symbol'], addend=r['addend']) for r in section['fields']]
            actual = c.pe_bytes_at(target, int(control['address'], 16), control['size'])
            if (PAIRED.digest(raw) != control['source_sha256'] or PAIRED.digest(actual) != control['body_sha256']
                    or PAIRED.BUFFER.PRIOR.link_complete(raw, fields, int(control['address'], 16), control['bindings'], catalog) != actual):
                raise ValueError('ordinary entire code/EH/state alternative fails unmasked real field comparison')
        for row in m['functions']:
            for symbol in (row['symbol'], row['ordinary_symbol']):
                if extent.complete_aux_section_size(data, symbol, c.coff_name) != row['size'] or len(c.object_function(path, symbol)[0]) != row['size']:
                    raise ValueError('element SDK/ordinary control loses positive whole own AUX extent')
    print('R157 origins OK: four whole typed SDK element operations / 213 bytes; four byte-equal ordinary bodies plus whole 27-byte EH and 36-byte data carriers / 276 bytes and fourteen unmasked real fields; all 193 ordinary cold sections / 12193 bytes, 27 SDK headers and actual retained observation include; independent full R156 parent/source/code/data/EH/runtime replay, original auxiliary and authored policy evidence preserved; library inference uses actual complete typed parents, not body equality alone; original types/source spelling/runtime outcomes unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, IndexError, StopIteration, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
