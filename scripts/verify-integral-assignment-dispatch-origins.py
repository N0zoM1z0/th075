#!/usr/bin/env python3
"""Cold-replay whole integral assignment dispatch graphs and independent game receivers."""
import argparse
import csv
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
import importlib.util
SPEC = importlib.util.spec_from_file_location('integral_source', ROOT/'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/integral-assignment-dispatch-origin-evidence.json'
MANIFEST_SHA256 = 'f95e13955f5707d534f1125fc44d7c4217a1a08744a2a41274ac270b601c2cf7'
PLAN_DIGESTS = {'groups': 'b59a5f62b51c55738a819ea7f42ecd9c57227a108767f9fb626781c76daf747b', 'sections': '9398690d1448bc129a458d5564b37c2bf796913bf02b1e316b6b3de3f26c7154', 'weak_references': '61b96065290e2b6b9b4b92f85eac3b3fc650a651bbd87c2700980300220af577', 'evidence_id': '89de37b761349713c67b473247bf41d981cc1515872743a7c5442a03b638aadb', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '15f3f14bc2de4d4fc540392269f7853178917fc6f843533fe21b10eb038dc462', 'parents': '90a5adbb69b2d46b889da876a40727ede0f9d8710a1c7c66b3ccff46fbb7a6f2', 'boundaries': '1d6d22c6c99a3e6ed5612fef34dc547de1476bddad944ce6730836ae773c7ce4', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'ordinary_members': 'a5eb47fed245ebe0bc15c4ead30fac7c856300aca0eeb94a9a1b8728cd694d34', 'range_controls': '984db969e5dec1b0ad2680a99dc72c46986b7db514e9f4c2a1249c79072833cf', 'header_definitions': 'bee46c614b4e264e6644bbd563fca2fcfb137ce12db07d78ce752497adc5a7b4', 'shared': 'f18d7e857fc9d7e277ad2553c801ec62e9ccc613e88b8b050acfdf1c5e846408', 'absolute': 'a5f696161bd89e1af316398c9deb61101d6e3e81897548711df250b8f15681ff', 'crt_archive_sha256': '69d0301fde85b097b2afc8e5732879473468d247ae0b55492fdc2063da1f7f6c', 'retained_provider': '734c055c6c88f9ee7263ded983b2614edacca8fc5620ace85901fefa20d3b6fb', 'unselected_sha256': 'e2d2d7b838980092847ef56df64109e48ba3999c2b96ecc078234bbadf9322eb', 'public_control': 'f772bca1a1fdc3ee30b724c048d4daf89d2a81ff8ab31a6ee975c44f8e4002af', 'canonical': 'a2659ea9aff83296a2861a448c2fe01117b6c837fbee5076787cdaf764a0ef25', 'retained_sha256': 'c8af60b0b04626493ba962ab133074368b17195d17f3ceb0d6f5af71666d855c', 'interpretation': '2b3a93924b11fa4f3de5697ec4f4dbac2f279fdfbd52fcad9a5b66271115f779'}
CONFIDENCE = 'complete-original-integral-assignment-dispatch-and-count-value-game-context'
WHOLE = {'0x0040A6C0': 50, '0x0040AA20': 11, '0x0040AA30': 37,
         '0x0045A620': 50, '0x0045ADD0': 37}
HEADERS = module('integral_headers', 'verify-vector-endpoint-route-origins.py').headers


def rows(name):
    with (ROOT/'config'/name).open() as source:
        return list(csv.DictReader(source))


def unselected_digest(records):
    return SOURCE.BASE.metadata_digest([r for r in records if r['address'] not in WHOLE])


def verify_plan(m):
    if set(m) != set(PLAN_DIGESTS):
        raise ValueError('Integral assignment evidence schema differs')
    for key, sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Integral assignment immutable complete evidence differs: '+key)
    if (m['evidence_id'] != 'R228' or {r['address']: r['size'] for r in m['functions']} != WHOLE
            or len(m['groups']) != 2 or len(m['sections']) != 221
            or sum(r['size'] for r in m['sections']) != 13561
            or sum(len(r['fields']) for r in m['sections']) != 545
            or sum(r['kind'] == 'code' for r in m['sections']) != 185
            or len(m['weak_references']) != 2 or len(m['ordinary_members']) != 4
            or len(m['range_controls']) != 6 or len(m['shared']) != 13
            or len(m['parents']) != 3 or sum(r['size'] for r in m['parents']) != 996
            or m['historical_snapshots']):
        raise ValueError('Integral assignment loses whole source/native/receiver/control coverage')
    for r in m['functions']:
        f, o, af, ao = [r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin']]
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified'
                or af['owner'] != 'library' or af['status'] != 'excluded'
                or any(af[k] != f[k] for k in ['address', 'size', 'span_end', 'current_name'])
                or any(af[k] for k in ['source_file', 'signature', 'calling_convention'])
                or af['match_percent'] != '0.00'
                or ao != dict(address=r['address'], origin='library', subsystem='VC71STL',
                              disposition='exclude', confidence=CONFIDENCE, evidence_id='R228')):
            raise ValueError('Integral assignment grants unsupported extent/source/ABI/exact credit')


def verify_canonical(m, evidence_only=False, *, check_unselected=False):
    fs, origins = rows('functions.csv'), rows('function-origins.csv')
    # The original transition protects every unrelated row. Later independently
    # accepted cohorts can update owners outside this complete source graph.
    if check_unselected:
        for name, records in [('functions.csv', fs), ('function-origins.csv', origins)]:
            if unselected_digest(records) != m['unselected_sha256'][name]:
                raise ValueError('Integral assignment changes unrelated canonical records: '+name)
    fs = {r['address']: r for r in fs}; origins = {r['address']: r for r in origins}
    selected = {r['address']: r for r in m['functions']}
    state = 'original' if evidence_only else 'accepted'
    for q in m['canonical']:
        key = q['function']['address']
        expected = q if key not in selected else dict(function=selected[key][state+'_function'],
                                                      origin=selected[key][state+'_origin'])
        if dict(function=fs[key], origin=origins[key]) != expected:
            raise ValueError('Integral assignment complete canonical owner differs: '+key)


def verify_native(m, target, c, flow):
    authored = module('integral_native', 'verify-authored-origins.py')
    for r in m['functions']+m['parents']:
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (digest(raw) != r['body_sha256'] or SOURCE.instructions(raw, a, flow) != r['instructions']
                or list(authored.verify_body(raw, a, r.get('switches', []),
                    lambda x, n: c.pe_bytes_at(target, x, n), r.get('direct_switches', []))) != r['cfg']):
            raise ValueError('Integral assignment complete native owner/CFG differs')
        if 'record' in r:
            if (r['record'] not in rows('authored-origin-evidence.csv') or r['origin']['origin'] != 'authored'
                    or r['record']['body_sha256'] != digest(raw)
                    or [q for q in rows('authored-origin-switches.csv') if q['address'] == r['address']] != r['switches']
                    or [q for q in rows('authored-origin-direct-switches.csv') if q['address'] == r['address']] != r['direct_switches']):
                raise ValueError('Integral assignment loses independent complete game context')
        for w in r.get('call_sequences', []):
            ins = r['instructions']; sequence = w['instructions']
            start = next(i for i, q in enumerate(ins) if q['offset'] == sequence[0]['offset'])
            if ins[start:start+len(sequence)] != sequence or not any(
                    q['mnemonic'] == 'call' and q['operands'] == hex(int(w['target'], 16))
                    and a+q['offset'] == int(w['site'], 16) for q in sequence):
                raise ValueError('Integral assignment loses actual count/value/receiver call window')
    for r in m['boundaries']:
        raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if raw.hex() != r['hex'] or digest(raw) != r['sha256'] or raw != b'\xcc'*r['size']:
            raise ValueError('Integral assignment includes external alignment in its extent')


def verify_shared(m, target, c, coff):
    prior = json.loads((ROOT/m['retained_provider']['path']).read_text())
    prior_catalog = SOURCE.BASE.retained_catalog(prior); shared = {}
    for r in m['shared']:
        owner = r['owner']; q = prior[owner['collection']][owner['index']]
        if q != owner['record'] or prior_catalog.get(r['symbol']) != int(r['address'], 16):
            raise ValueError('Integral assignment invents independent retained source ownership')
        shared[r['symbol']] = prior_catalog[r['symbol']]
    rt = module('integral_crt', 'verify-runtime-origins.py')
    crt = (ROOT/m['absolute']['archive']).read_bytes()
    if digest(crt) != m['crt_archive_sha256']:
        raise ValueError('Integral assignment original CRT archive differs')
    members = {a: (n, b) for a, n, b in rt.archive_members(crt)}
    name, body = members[m['absolute']['member_offset']]
    if (name != m['absolute']['member'] or digest(body) != m['absolute']['member_sha256']
            or [d for d in coff.parse_symbols(body, c.coff_name)[1] if d['symbol'] == '__except_list' and d['section'] != 0]
            != [m['absolute']['definition']] or m['absolute']['definition']['section'] != -1
            or m['absolute']['definition']['offset']):
        raise ValueError('Integral assignment replaces the actual absolute CRT definition')
    shared['__except_list'] = 0
    return shared


def verify_control(m, body, target, c, coff, flow, shared):
    extra = module('integral_sections', 'sdk_x3d_carriers.py')
    pe = module('integral_permissions', 'verify-sdk-x3d-origins.py')
    inventory = module('integral_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body, c, coff) != control['emission']:
        raise ValueError('Integral assignment full ordinary emission differs')
    raw, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
    if list(struct.unpack('<7I', raw)) != control['layout_values']:
        raise ValueError('Integral assignment crops the merged readonly layout observation')
    if [SOURCE.weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
        raise ValueError('Integral assignment loses actual weak AUX/fallback definition')
    decoded = {}
    for r in m['sections']:
        raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
        a = int(r['base'], 16)
        if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
            raise ValueError('Integral assignment complete defining source/AUX/fields/permissions differ')
        decoded[r['source']['section']] = raw, fields
    for g in m['groups']:
        scoped = [r for r in m['sections'] if r['group'] == g['id']]
        refs = [r for r in m['weak_references'] if r['symbol'] in g['weak_symbols']]
        catalog = SOURCE.owned_catalog(scoped, shared, g['id'], refs)
        for r in scoped:
            raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
            linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a,
                                                            data_image=r['kind'] == 'data')
            native = c.pe_bytes_at(target, a, len(raw))
            if linked != native or digest(native) != r['body_sha256']:
                raise ValueError('Integral assignment whole unmasked source/native body differs')
            if r['kind'] == 'code':
                roots = {0}
                roots.update(d['offset'] for d in r['source']['definitions'] if d['type'] == 32 and d['storage'] == 3)
                roots.update(f['symbol_offset']+f['addend'] for q in scoped for f in q['fields']
                             if f['symbol_section'] == r['source']['section'] and f['symbol_storage'] == 6)
                if sorted(roots) != r['roots'] or flow.flow(native, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                    raise ValueError('Integral assignment whole normal/EH/unwind graph differs')
        for q in [q for q in m['range_controls'] if q['group'] == g['id']]:
            raw, fields, source = extra.section_carrier(body, q['source']['section'], c, coff)
            native = c.pe_bytes_at(target, int(q['native'], 16), q['native_size'])
            if (SOURCE.BASE.canonical_source(source, body) != q['source'] or fields != q['fields']
                    or len(raw) != q['size'] or digest(raw) != q['source_sha256']
                    or SOURCE.instructions(raw, 0, flow) != q['instructions']
                    or digest(native) != q['native_sha256'] or (raw == native) != q['raw_byte_equal']):
                raise ValueError('Integral assignment complete pointer-range control differs')
            if q['role'] == 'range-dispatch':
                if len(raw) != 51 or len(fields) != 2 or any(f['symbol'] in catalog for f in fields):
                    raise ValueError('Integral assignment confuses pointer and integer defining routes')
            elif q['role'] == 'empty-pointer-category':
                if fields or len(raw) != 11 or q['raw_byte_equal']:
                    raise ValueError('Integral assignment loses the distinct entire empty category control')
            elif q['role'] == 'range-policy':
                if len(raw) == 37 or len(fields) != 5 or q['raw_byte_equal']:
                    raise ValueError('Integral assignment merges range and count/value policy bodies')
            else:
                raise ValueError('Integral assignment unknown range-control role')


def replay(m, evidence_only=False):
    c = module('integral_target', 'compare-coff-function.py'); coff = module('integral_coff', 'coff_data.py')
    flow = module('integral_flow', 'sdk_image_carriers.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']:
        raise ValueError('Integral assignment target identity differs')
    for path, sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha:
            raise ValueError('Integral assignment retained source/evidence differs: '+path)
    for q in m['header_definitions']:
        if ((ROOT/q['path']).read_text().splitlines()[q['start']-1:q['end']] != q['lines']
                or q['path'] not in m['public_control']['headers']):
            raise ValueError('Integral assignment original SDK definition differs')
    verify_canonical(m, evidence_only, check_unselected=evidence_only)
    verify_native(m, target, c, flow)
    provider = m['retained_provider']
    result = subprocess.run([str(ROOT/'scripts/repo-python'), str(ROOT/provider['script'])],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('Integral assignment independent retained cold graph failed: '+result.stderr)
    print(result.stdout.strip(), flush=True)
    shared = verify_shared(m, target, c, coff)
    scratch = ROOT/'build/origin-integral-assignment-verification'; scratch.mkdir(parents=True, exist_ok=True)
    control = m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'IntegralAssignmentDispatch.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'), str(ROOT/control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or HEADERS(result.stdout+result.stderr) != control['headers']:
            raise ValueError('Integral assignment cold source/includes differ')
        verify_control(m, obj.read_bytes(), target, c, coff, flow, shared)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true'); args = parser.parse_args()
    m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Integral assignment immutable manifest differs')
    replay(m, args.evidence_only)
    print('R228: five whole integral assignment dispatch origins185; complete source-owned code/data/normal/EH graphs, '
          'natural byte-equal ordinary members, distinct whole pointer-range controls and independent full game callers; '
          'original element declarations and historical replacement absence remain unknown; no source/ABI/exact credit.')


if __name__ == '__main__': main()
