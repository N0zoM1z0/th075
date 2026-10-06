#!/usr/bin/env python3
"""Cold-check paired global vector lifetimes and genuine outer-source alternatives."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/global-vector-lifetime-origin-evidence.json'
MANIFEST_SHA256 = '56c0dc8d22cd68374435b6c54b509a30ef06a60ec9d25f471e5b1c6ffa152770'
PLAN_DIGESTS = {'evidence_id': '0e083f1ee126453db804eb87477a76b8728563dec1ff90fa7f004f2e5c36d550', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'baseline_commit': '69c5e762c61ce88c79f81b33e83cdd129eb7498c0fe54eb6d238e64409423107', 'functions': '170b9e1c170ae43d2df636e5553128cbeff0cadc23a890262dbff86087dc863d', 'native': 'abba38b5512abafcc546c29ef518d02c7e97ea6b8cdb95d0437e7179b07930d6', 'canonical': 'db9581d5a94f3f5d8004dd4fb6e59169332bc174376bd6662e31b1cfd2ae0b6c', 'unselected_sha256': '1a5172e9105c75e72e0ed20dc94b9958fbed41d034dce0edebfeb4f34f03e29d', 'context': '895553cc65eaa1906c25b2449c826616ad69dc94d8cbe66c7c38f4e03abb44b7', 'controls': 'a423a4ef62cd759b28730d10d87f18a3c8920d862a6693e3e01d3adcb9c49a24', 'retained_commands': 'f77062258986a4dd1d4d52db5c4807803996bed3b25a071d0d38891b2ac459e7', 'retained_sha256': 'b9b84eb64f2bffc8a0a5829115f4d5973a8063379cba60e3f08df8845a68c171', 'interpretation': '3c4748cc1204bf9aac7d566711e9fbd32a1fdf1300ba3d55ea93e8ef4629fab0'}
WHOLE = {'0x004065D0': 19, '0x004065F0': 19}
PROFILE = ['/Od', '/Ob0', '/Gy', '/GR-', '/GX', '/Zi', '/GS', '/showIncludes']


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


COMMON = module('global_vector_common', 'verify-sdk-row-deleting-helper-origins.py')
digest = COMMON.digest
metadata_digest = COMMON.metadata_digest
rows = COMMON.rows


def inventory(body, c, coff, carrier):
    """Include every ordinary code/data/directive section and whole BSS storage."""
    count, definitions = coff.parse_symbols(body, c.coff_name)
    initialized, bss = [], []
    for number in range(1, count + 1):
        h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + (number - 1) * 40)
        name = h[0].rstrip(b'\0').decode('ascii')
        if not h[3] or name.startswith('.debug'):
            continue
        if h[4]:
            raw, fields, source = carrier.section_carrier(body, number, c, coff)
            initialized.append(dict(name=name, source=COMMON.SOURCE.BASE.canonical_source(source, body),
                                    sha256=digest(raw), fields=fields))
        else:
            if not h[9] & 0x80 or h[7] or h[5]:
                raise ValueError('Global vector source omits non-initialized storage')
            bss.append(dict(section=number, name=name, size=h[3], flags=h[9],
                            definitions=[d for d in definitions if d['section'] == number]))
    weak = module('global_vector_weak', 'verify-standard-exception-origins.py')
    references = [weak.read_weak_reference(body, d['symbol'], c, coff, 0)
                  for d in definitions if d['storage'] == 105]
    return dict(initialized=initialized, bss=bss, weak_references=references)


def verify_plan(plan):
    if set(plan) != set(PLAN_DIGESTS):
        raise ValueError('Global vector immutable schema differs')
    for key, value in PLAN_DIGESTS.items():
        if metadata_digest(plan[key]) != value:
            raise ValueError('Global vector immutable whole evidence differs: ' + key)
    if plan['evidence_id'] != 'R253' or {r['address']: r['size'] for r in plan['functions']} != WHOLE:
        raise ValueError('Global vector selected scope differs')
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (r['original_origin']['origin'] != 'unknown' or old['owner']
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or new['owner'] != 'library' or new['status'] != 'excluded'
                or any(new[k] for k in ['source_file', 'signature', 'calling_convention'])
                or new['match_percent'] != '0.00'
                or r['accepted_origin']['origin'] != 'library'
                or r['accepted_origin']['disposition'] != 'exclude'
                or r['accepted_origin']['evidence_id'] != 'R253'):
            raise ValueError('Global vector transition gains unsupported extent/ABI/source/exact credit')


def verify_canonical(plan, evidence_only=False):
    for name in ['functions.csv', 'function-origins.csv']:
        actual = rows(name)
        if metadata_digest([r for r in actual if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('Global vector changes unrelated canonical rows: ' + name)
    fs = {r['address']: r for r in rows('functions.csv')}
    os = {r['address']: r for r in rows('function-origins.csv')}
    selected = {r['address']: r for r in plan['functions']}
    for pair in plan['canonical']:
        a = pair['function']['address']
        expected = pair
        if a in selected:
            state = 'original' if evidence_only else 'accepted'
            expected = dict(function=selected[a][state + '_function'], origin=selected[a][state + '_origin'])
        if dict(function=fs[a], origin=os[a]) != expected:
            raise ValueError('Global vector complete canonical pair differs: ' + a)


def verify_context(plan):
    """Use the complete same-global source chain, never a short callee alone."""
    control = plan['controls'][0]
    comparisons = control['comparisons']
    statics = {r['address']: r for r in plan['context']['static_records']}
    for selected, init, final, ctor, tidy, global_address in [
            ('0x004065D0', '0x00656D00', '0x00656E60', '0x004063F0', '0x004044F0', '0x00671368'),
            ('0x004065F0', '0x00656D20', '0x00656E70', '0x004064E0', '0x00404630', '0x00671358')]:
        def one(address, role):
            matches = [r for r in comparisons if r['address'] == address and r['role'] == role]
            if len(matches) != 1:
                raise ValueError('Global vector loses its unique whole source carrier')
            return matches[0]
        start = one(init, 'direct-vector-initializer28')
        end = one(final, 'direct-vector-finalizer15')
        construction = one(ctor, 'original-R090-constructor42')
        destruction = one(selected, 'vendor-destructor19')
        cleanup = one(tidy, 'original-R004-cleanup-whole')
        chain = [(start, 1, construction), (end, 1, destruction), (destruction, 0, cleanup)]
        for parent, index, provider in chain:
            field, binding = parent['fields'][index], parent['bindings'][index]
            if (field['symbol'] != provider['symbol'] or field['addend']
                    or field['symbol_section'] != provider['section'] or field['symbol_offset']
                    or binding['target'] != provider['address']):
                raise ValueError('Global vector substitutes an actual whole provider in its lifetime chain')
        if (start['fields'][0]['symbol'] != end['fields'][0]['symbol']
                or start['fields'][0]['symbol_section'] != end['fields'][0]['symbol_section']
                or start['fields'][0]['symbol_offset'] != end['fields'][0]['symbol_offset']
                or start['bindings'][0]['target'] != global_address
                or end['bindings'][0]['target'] != global_address
                or start['bindings'][2]['target'] != final
                or start['fields'][2]['symbol_section'] != end['section']
                or start['bindings'][3]['target'] != '0x0064168B'):
            raise ValueError('Global vector loses the actual same-global initialization/finalization')
        if (not construction['symbol'].startswith('??0?$vector@')
                or not destruction['symbol'].startswith('??1?$vector@')
                or construction['symbol'][3:] != destruction['symbol'][3:]
                or construction['size'] != 42 or destruction['size'] != 19
                or [f['offset'] for f in construction['fields']] != [13, 21, 31]):
            raise ValueError('Global vector replaces the genuine paired vendor lifetime declarations')
        first, last = statics[init], statics[final]
        if (first['object_address'] != global_address or last['object_address'] != global_address
                or first['callee_address'] != ctor or last['callee_address'] != selected
                or first['registered_callback'] != final or first['registration_target'] != '0x0064168B'):
            raise ValueError('Global vector disagrees with its independent original static witness')
    old = json.loads((ROOT / 'config/runtime-cycle-origin-evidence.json').read_text())
    if plan['context']['interior_labels'] != [r for r in old['interior_labels']
                                             if r['parent'] == '0x00642A61']:
        raise ValueError('Global vector loses the whole free113 interior finally label')


def verify_native(plan, target, c, flow):
    authored = module('global_vector_cfg', 'verify-authored-origins.py')
    records = {r['address']: r for r in plan['native']}
    for a, r in records.items():
        at = int(a, 16)
        raw = c.pe_bytes_at(target, at, r['size'])
        instructions = COMMON.SOURCE.instructions(raw, at, flow)
        if digest(raw) != r['body_sha256'] or instructions != r['instructions']:
            raise ValueError('Global vector whole native body differs: ' + a)
        if a == '0x00640F15':
            cfg = flow.flow(raw, at, [0], [], {at + 1: 0x642A61}, {})
        else:
            cfg = list(authored.verify_body(raw, at, [], lambda x, n: c.pe_bytes_at(target, x, n), []))
        if cfg != r['cfg']:
            raise ValueError('Global vector whole native flow differs: ' + a)
    for key, witnesses in plan['context']['witnesses'].items():
        COMMON.BASE.BASE.BASE.require(records[key]['instructions'],
                                     {int(k): tuple(v) for k, v in witnesses.items()})
    for r in plan['context']['alignment']:
        raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if raw != b'\xcc' * r['size'] or digest(raw) != r['sha256']:
            raise ValueError('Global vector includes external alignment')
    if plan['context']['static_records'] != [r for r in rows('compiler-static-evidence.csv')
                                             if r['address'] in plan['context']['static_addresses']]:
        raise ValueError('Global vector original paired static records differ')
    verify_context(plan)


def verify_control(control, body, target, c, coff, carrier, flow):
    if inventory(body, c, coff, carrier) != control['emission']:
        raise ValueError('Global vector whole ordinary emission/AUX/fields/storage differs')
    for r in control['comparisons']:
        raw, fields, source = carrier.section_carrier(body, r['section'], c, coff)
        if r['definition'] not in source['definitions'] or fields != r['fields']:
            raise ValueError('Global vector replaces genuine source definition/fields')
        linked, proof = COMMON.bind(raw, fields, int(r['address'], 16), r['bindings'], flow, [0])
        if proof != r['linked_flow'] or len(linked) != r['size']:
            raise ValueError('Global vector complete linked flow differs')
        if linked != c.pe_bytes_at(target, int(r['address'], 16), r['size']):
            raise ValueError('Global vector unmasked source comparison differs')
    for r in control['layouts']:
        raw, fields, _ = carrier.section_carrier(body, r['section'], c, coff)
        if fields or list(struct.unpack('<' + 'I' * len(r['values']), raw)) != r['values']:
            raise ValueError('Global vector whole ordinary layout differs')
    definitions = {d['symbol']: d for d in coff.parse_symbols(body, c.coff_name)[1]}
    for r in control['alternatives']:
        d = definitions[r['symbol']]
        raw, fields, source = carrier.section_carrier(body, d['section'], c, coff)
        if (len(raw) != r['size'] or digest(raw) != r['sha256'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(source, body) != r['source']):
            raise ValueError('Global vector ordinary alternative loses full body/actual providers')


def run_checked(command, description):
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError(description + ': ' + result.stdout[-1200:] + result.stderr[-1200:])
    return result


def replay(plan, evidence_only=False):
    c = module('global_vector_target', 'compare-coff-function.py')
    coff = module('global_vector_coff', 'coff_data.py')
    carrier = module('global_vector_carrier', 'sdk_x3d_carriers.py')
    flow = module('global_vector_flow', 'sdk_image_carriers.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('Global vector target identity differs')
    for path, value in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != value:
            raise ValueError('Global vector original retained input differs: ' + path)
    verify_canonical(plan, evidence_only)
    verify_native(plan, target, c, flow)
    scratch = ROOT / 'build/origin-global-vector-lifetime-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        for control in plan['controls']:
            obj = Path(temp) / control['object_name']
            result = run_checked([str(ROOT / 'scripts/compile-probe.sh'),
                                  str(ROOT / control['probe']), str(obj), *control['profile']],
                                 'Global vector fresh compiler failed; no cached fallback')
            if COMMON.included_headers(result.stdout + result.stderr) != control['headers']:
                raise ValueError('Global vector actual complete header set differs')
            verify_control(control, obj.read_bytes(), target, c, coff, carrier, flow)
        obj = Path(temp) / 'StaticLifetimeOrigins.obj'
        run_checked([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / 'probes/VC7StaticLifetime.cpp'),
                     str(obj), '/Od', '/Ob0', '/Gy', '/GR-', '/GX', '/Zi', '/GS', '/I', 'src'],
                    'Global vector retained static source cold build failed')
        result = run_checked([str(ROOT / 'scripts/repo-python'), 'scripts/verify-static-origins.py',
                              '--probe', str(obj)], 'Global vector entire original R024 proof failed')
        print(result.stdout.strip())
    for filename in plan['retained_commands']:
        result = run_checked([str(ROOT / 'scripts/repo-python'), 'scripts/' + filename],
                             'Global vector entire retained proof failed: ' + filename)
        print(result.stdout.strip())


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Global vector immutable manifest identity differs')
    verify_plan(plan)
    replay(plan, args.evidence_only)
    print('R253: two complete vendor vector lifetime bodies /38 bytes; paired same-global startup '
          'construction/finalization and full fresh library cleanup graph; original R024, R090/R089, '
          'R142/R141/R038 and R121 cold proofs; genuine inherited and ordinary alternatives retained; '
          'no original private type, ABI, source, mapping or exact credit.')


if __name__ == '__main__':
    main()
