#!/usr/bin/env python3
"""Cold-replay original deque count policies with complete source-owned recoveries."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('deque_count_prior', ROOT / 'scripts/verify-frame-index-policy-origins.py')
PRIOR = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(PRIOR)
SOURCE = PRIOR.SOURCE
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/byte-deque-count-origin-evidence.json'
MANIFEST_SHA256 = '13c86296cc9f4b42fd09474f9dabcef5c9fba40b855a1150eb73f24c5d8b20f3'
PLAN_DIGESTS = {'groups': 'f805d8c07460b5c55ae197992bf67ded87f20a87b5582b87e0b649f224f4d345', 'sections': '139258469dd58463c86e3162bbdd6e4a952b34de875abc85fa5e2e8185620d7c', 'weak_references': 'b49d31a5f6de14e3ccfbfe6400b8a22c23cf9f2f7ac29e9bc82bab3d1800a0b7', 'evidence_id': 'bd62a2dfd8e3d317322052e15c6c722145375027336dd413a3ed6e6016dc6dfa', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'prior': '97daf3fca6aa7ada49e526adfb5f4ec5fba477dea1a91716d1851da1d851f42a', 'functions': 'b57f1fe2ae7a0f10817098daa75bb27e9110bae12be7de5f51e554d725867554', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'recovery': '6200129e57a7266ea5e5650a0191f9ec890d773fa5128b461d93be527a450d6d', 'extent': '4d6c981410bf0f89854058429235a8f9a2c9f50cb9723507d765bdd90c246ff6', 'public_control': '507101291649c647288939af2e5fd41f91b09ee778ba9b782ec5bfc60c1993c7', 'public_insert_control': '492af9af69b7432ff329ea8ac4bac886fe14c1e5740dbb3aee2277e4fa4cd6b0', 'erase_prior': 'dfa37fe21adb00b508a110e719ec965beebc61e6f4a66b14b5e8f0e8070a9820', 'retained_sha256': '373b1b372d17a01fbf1f682dec76d172f95c0810c1a06b2813c47568aba92c06'}
WHOLE = {'0x00455C40': 29, '0x00455CA0': 108, '0x00455E40': 1521, '0x00456137': 48, '0x004563F3': 62, '0x00456560': 38}

def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
        if value[:3].lower() != 'z:/': raise ValueError('DequeCount original include loses host mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('DequeCount original include imports an unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('DequeCount immutable complete evidence differs: ' + key)
    if (m['evidence_id'] != 'R214' or {r['address']: r['size'] for r in m['functions']} != WHOLE
            or len(m['functions']) != 6 or len(m['groups']) != 1
            or len(m['sections']) != 70 or sum(r['size'] for r in m['sections']) != 5500
            or sum(len(r['fields']) for r in m['sections']) != 178
            or sum(r['kind'] == 'code' for r in m['sections']) != 62
            or m['historical_snapshots'] or len(m['recovery']) != 2
            or len(m['public_control']['emission']) != 121
            or sum(r['size'] for r in m['public_control']['emission']) != 8145
            or m['public_control']['layout_values'] != [1, 20, 8, 8]
            or m['public_insert_control']['size'] != 37):
        raise ValueError('DequeCount loses complete source policies and public controls')
    for r in m['functions']:
        f, o, af, ao = (r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin'])
        expected_size = 1459 if r['address'] == '0x00455E40' else r['size']
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified' or f['owner']
                or any(f[k] or af[k] for k in ['source_file', 'signature', 'calling_convention'])
                or f['match_percent'] != '0.00' or af['match_percent'] != '0.00'
                or any(af[k] != f[k] for k in ['address', 'current_name'])
                or int(f['size']) != expected_size or int(af['size']) != r['size']
                or af['span_end'] != f"0x{int(r['address'], 16) + r['size'] - 1:08X}"
                or ao['evidence_id'] != 'R214' or af['owner'] != 'library' or af['status'] != 'excluded'
                or ao['origin'] != 'library' or ao['disposition'] != 'exclude'):
            raise ValueError('DequeCount gains unsupported extent/private ABI/source/origin/exact credit')
    rows = {r['base']: r for r in m['sections']}; root = rows['0x00455E40']; eh = rows['0x006695B8']
    if (root['size'] != 1521 or root['roots'] != [0, 759, 1459] or eh['size'] != 132
            or root['flow']['code_size'] != 1521 or m['extent']['unique_policy_bytes'] != 1696):
        raise ValueError('DequeCount crops the complete insertion owner/recovery graph')
    for recovery in m['recovery']:
        d, field = recovery['definition'], recovery['eh_field']
        if (d not in root['source']['definitions'] or field not in eh['fields']
                or d['offset'] != recovery['offset'] or d['storage'] != 3 or d['type'] != 32
                or field['symbol'] != d['symbol'] or field['symbol_section'] != root['source']['section']
                or field['symbol_offset'] != d['offset'] or field['symbol_storage'] != 3 or field['addend'] != 0
                or int(recovery['address'], 16) != int(root['base'], 16) + recovery['offset']
                or recovery['offset'] + recovery['size'] > root['size']
                or recovery['common_exit'] != '0x00456417'):
            raise ValueError('DequeCount invents an independent recovery or borrows an EH pointer')


def verify_recovery(m, target, c, flow):
    """The front recovery's external edge is internal to its whole source owner."""
    root = next(r for r in m['sections'] if r['base'] == '0x00455E40')
    a = int(root['base'], 16); raw = c.pe_bytes_at(target, a, root['size'])
    complete = SOURCE.instructions(raw, a, flow)
    boundaries = {a + i['offset'] for i in complete}
    for r in m['functions']:
        start = int(r['address'], 16); native = c.pe_bytes_at(target, start, r['size'])
        if digest(native) != r['body_sha256'] or SOURCE.instructions(native, start, flow) != r['instructions']:
            raise ValueError('DequeCount complete native entry/recovery view differs')
        owner = next(q for q in m['sections'] if q['base'] == r['source_owner'])
        if (owner['kind'] != 'code' or int(owner['base'], 16) + r['source_offset'] != start
                or r['source_offset'] + r['size'] > owner['size']):
            raise ValueError('DequeCount entry escapes its complete source owner')
    for q, pop in zip(m['recovery'], ['0x454d70', '0x4158d0']):
        start = int(q['address'], 16); view = next(r for r in m['functions'] if r['address'] == q['address'])
        ins = view['instructions']; pairs = [(i['mnemonic'], i['operands']) for i in ins]
        if (start not in boundaries or int(q['common_exit'], 16) not in boundaries
                or [(i['offset'], i['operands']) for i in ins if i['mnemonic'] == 'call'] != [(20, pop), (31, '0x640c12')]
                or pairs[0] not in [('mov', 'ecx, dword ptr [ebp - 0x100]'), ('mov', 'edx, dword ptr [ebp - 0x100]')]
                or not any(i['offset'] == 25 and i['mnemonic'] == 'jmp' and int(i['operands'], 16) == start for i in ins)
                or not any(i['offset'] == 36 and i['mnemonic'] == 'mov' and i['operands'] == 'dword ptr [ebp - 4], 0xffffffff' for i in ins)):
            raise ValueError('DequeCount loses full original rollback/rethrow/shared-exit protocol')
    front, back = [next(r for r in m['functions'] if r['address'] == q['address']) for q in m['recovery']]
    if (front['instructions'][-1]['mnemonic'] != 'jmp' or front['instructions'][-1]['operands'] != '0x456417'
            or back['instructions'][-1]['mnemonic'] != 'ret' or back['instructions'][-1]['operands'] != '0x10'):
        raise ValueError('DequeCount truncates the front recovery or drops the real RET16')
    p = m['extent']['alignment']; alignment = c.pe_bytes_at(target, int(p['address'], 16), p['size'])
    if alignment.hex() != p['hex'] or digest(alignment) != p['sha256'] or alignment != b'\xcc' * 15:
        raise ValueError('DequeCount absorbs alignment into the source extent')


def replay(m, evidence_only=False):
    c = module('deque_count_target', 'compare-coff-function.py'); coff = module('deque_count_coff', 'coff_data.py')
    extra = module('deque_count_carriers', 'sdk_x3d_carriers.py'); flow = module('deque_count_flow', 'sdk_image_carriers.py')
    pe = module('deque_count_permissions', 'verify-sdk-x3d-origins.py')
    inventory = module('deque_count_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('DequeCount target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    for r in m['functions']:
        if functions[r['address']] != r[state + '_function'] or origins[r['address']] != r[state + '_origin']:
            raise ValueError('DequeCount bounded canonical transition differs')
    p = m['extent']['next_owner']
    if functions[p['base']] != p['function'] or origins[p['base']] != p['origin'] or p['size'] != 226:
        raise ValueError('DequeCount changes the next independent full source owner')
    verify_recovery(m, target, c, flow)
    prior = json.loads((ROOT / m['prior']['path']).read_text())
    if (digest((ROOT / m['prior']['path']).read_bytes()) != m['prior']['manifest_sha256']
            or prior['prior']['shared'] != m['prior']['shared'] or prior['prior']['absolute'] != m['prior']['absolute']
            or prior['prior']['crt_archive_sha256'] != m['prior']['crt_archive_sha256']):
        raise ValueError('DequeCount replaces independent prior source ownership')
    for verifier in ['scripts/verify-frame-index-policy-origins.py', m['erase_prior']['verifier']]:
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / verifier)], cwd=ROOT, capture_output=True, text=True)
        if result.returncode: raise ValueError('DequeCount complete prior cold graph failed: ' + result.stderr)
        print(result.stdout.strip(), flush=True)
    old = json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())
    source_catalog = SOURCE.BASE.retained_catalog(old); shared = {'__except_list': 0}
    for r in m['prior']['shared']:
        owner = r['owner']
        if old[owner['collection']][owner['index']] != owner['record'] or source_catalog.get(r['symbol']) != int(r['address'], 16):
            raise ValueError('DequeCount native field overrides retained complete source definition')
        shared[r['symbol']] = source_catalog[r['symbol']]
    scratch = ROOT / 'build/origin-byte-deque-count-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'ByteDequeCount.obj'; control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or headers(result.stdout + result.stderr) != control['headers']:
            raise ValueError('DequeCount cold generic source/original includes differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != control['emission']: raise ValueError('DequeCount omits ordinary code/data/EH emission')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 16 or list(struct.unpack('<4I', layout)) != control['layout_values']:
            raise ValueError('DequeCount crops the complete byte observation carrier')
        if [SOURCE.weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
            raise ValueError('DequeCount loses actual weak AUX/strong fallback')
        rows = m['sections']; decoded = {}
        for r in rows:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff); a = int(r['base'], 16)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                    or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                raise ValueError('DequeCount complete source/AUX/fields/permissions differ')
            decoded[r['source']['section']] = (raw, fields)
            if r['kind'] == 'code':
                actual = [dict(function=f, origin=origins[k]) for k, f in functions.items() if a <= int(k, 16) < a + r['size']]
                expected = [dict(function=selected[q['function']['address']][state + '_function'],
                                 origin=selected[q['function']['address']][state + '_origin'])
                            if q['function']['address'] in selected else q for q in r['inventory_entries']]
                if actual != expected: raise ValueError('DequeCount full source hides an inventory entry')
        for g in m['groups']:
            rows = [r for r in m['sections'] if r['group'] == g['id']]
            catalog = SOURCE.owned_catalog(rows, shared, g['id'], [r for r in m['weak_references'] if r['symbol'] in g['weak_symbols']])
            for r in rows:
                raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
                linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a, data_image=r['kind'] == 'data')
                actual = c.pe_bytes_at(target, a, len(raw))
                if linked != actual or digest(actual) != r['body_sha256']: raise ValueError('DequeCount complete unmasked body differs')
                if r['kind'] == 'code':
                    roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type'] == 32 and d['storage'] == 3)
                    roots.update(f['symbol_offset'] + f['addend'] for q in rows for f in q['fields']
                                 if f['symbol_section'] == r['source']['section'] and f['symbol_storage'] == 6)
                    if sorted(roots) != r['roots'] or flow.flow(actual, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                        raise ValueError('DequeCount complete normal/EH/unwind/shared-exit CFG differs')
        control = m['public_insert_control']
        raw, fields, source = extra.section_carrier(body, control['source']['section'], c, coff)
        if (SOURCE.BASE.canonical_source(source, body) != control['source'] or fields != control['fields']
                or len(raw) != 37 or digest(raw) != control['source_sha256']
                or SOURCE.instructions(raw, 0x100000, flow) != control['instructions']
                or len(fields) != 1 or not fields[0]['symbol'].startswith('?_Insert_n@?$deque@E')):
            raise ValueError('DequeCount substitutes the public insert wrapper for its complete protected worker')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']), *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('DequeCount immutable source/evidence differs: ' + path)
    replay(m, args.evidence_only)
    print('R214 origins OK: six library entries1806 including two source-owned interiors48/62; '
          'four unique count/index policies1696; complete insertion1521 with normal/front/back roots and RET16; '
          '70 whole code/data carriers5500/all178 fields/62 CFGs; 121 ordinary emissions8145/27 original includes/'
          'full layout16; independent cold R213 and R111 proofs; public insert37 control; '
          '15-byte alignment and next full owner226; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
