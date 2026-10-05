#!/usr/bin/env python3
"""Cold-replay neighboring authored policies and original vector count assignment."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('neighbor_prior', ROOT / 'scripts/verify-nested-initialization-origins.py')
PRIOR = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(PRIOR)
SOURCE = PRIOR.SOURCE
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/neighbor-policy-origin-evidence.json'
MANIFEST_SHA256 = 'fc61cbd578dd4a0a44dd6a724d34502520888a19e3064ec212a05e656781decf'
PLAN_DIGESTS = {'groups': 'eb70875d2b62695e988176f2f3fea7d2133a1b9d2a1f6a499ae9555b883d1571', 'sections': '881c03cb9a742eb07bfe9281372dc28b65a96a969bebe2a3e60428fdbc022c4d', 'weak_references': '7c4b9afae016bc6200d47e9cabac91c01bd145cc5c1d5854a71b1ea9c977301c', 'evidence_id': 'dc05457a2a7b00684657957205be5fad21f1468273eb71d3086f3e0542884a21', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'prior': '2c5e0a4071acb34ee2a77475df5be845739e2527e6ba0015cd0e010d1efc9198', 'functions': '3f37a5283fc19810e47341acb413602dfa63f1d8f9896fb03513a42288c86d54', 'retained_unknowns': '89522da3bc09e0d49a1df9743ae236bc9ad85d0c0e48ef499929ea6d2097f1f4', 'parents': 'ecbc1192e2ba251399786e3f3099e7d9c53a476efe374d71d82bac17b2d0477c', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'memset': '078e6f9e489d82cafd1e133ba0dcc33afcd8b9a83cfcdd5036aae782d06342f2', 'authored_path': '77981ab1a451ca11c5ce89b71cbcf1a21d0fea96dfd8b5de30d4985a77b062eb', 'public_control': '1d56a730bde7b42a3e5bdd0116de9be33217349ffdc744f07079568abe5fbda3', 'alternatives': 'a54906957a4ef0e59709a1c66f9f9c184310eef9689d3db02b27de38c9c18ac6', 'retained_sha256': 'a95777abb2bd99b7749283d70bb3274ee54ac5834f30d538d9d31a3ac04e07e5'}
WHOLE = {'0x00458790': 70, '0x00458960': 93, '0x00458E70': 195, '0x00458B30': 29}


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
        if value[:3].lower() != 'z:/': raise ValueError('Neighbor original include loses host mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/') and relative not in (
                'tests/origin_probes/NestedVectorInsertionCarriers.cpp', 'tests/origin_probes/VectorInsertionCarriers.cpp'):
            raise ValueError('Neighbor original include imports an unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Neighbor immutable complete evidence differs: ' + key)
    if (m['evidence_id'] != 'R211' or {r['address']: r['size'] for r in m['functions']} != WHOLE
            or len(m['functions']) != 4 or len(m['groups']) != 3
            or len(m['sections']) != 170 or sum(r['size'] for r in m['sections']) != 9581
            or sum(len(r['fields']) for r in m['sections']) != 402
            or sum(r['kind'] == 'code' for r in m['sections']) != 143
            or len(m['retained_unknowns']) != 13 or len(m['parents']) != 2 or m['historical_snapshots']
            or len(m['public_control']['emission']) != 454
            or sum(r['size'] for r in m['public_control']['emission']) != 28704
            or [r['size'] for r in m['alternatives']] != [22, 40, 114]):
        raise ValueError('Neighbor loses complete bounded policy/carrier/default controls')
    for r in m['functions']:
        f, o, af, ao = (r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin'])
        authored = r['address'] in ['0x00458790', '0x00458960']
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified'
                or any(f[k] or af[k] for k in ['source_file', 'signature', 'calling_convention']) or f['owner']
                or f['match_percent'] != '0.00' or af['match_percent'] != '0.00'
                or any(af[k] != f[k] for k in ['address', 'size', 'span_end', 'current_name'])
                or af['size'] != str(r['size']) or ao['evidence_id'] != 'R211'
                or (authored and (af['owner'] or af['status'] != 'unclassified' or ao['origin'] != 'authored'
                    or ao['disposition'] != 'authored'))
                or (not authored and (af['owner'] != 'library' or af['status'] != 'excluded' or ao['origin'] != 'library'
                    or ao['disposition'] != 'exclude'))):
            raise ValueError('Neighbor gains unsupported extent/private ABI/source/origin/exact credit')
    for r in m['retained_unknowns']:
        if (r['origin']['origin'] != 'unknown' or r['function']['status'] != 'unclassified'
                or r['function']['owner'] or r['function']['source_file']):
            raise ValueError('Neighbor assigns unresolved short/private ownership')


def check_call(raw, address, call):
    site = int(call['site'], 16); offset = site - address
    if (offset < 0 or offset + 5 > len(raw) or raw[offset] != 0xe8
            or site + 5 + struct.unpack_from('<i', raw, offset + 1)[0] != int(call['target'], 16)):
        raise ValueError('Neighbor loses complete native parent/policy call evidence')


def replay(m, evidence_only=False):
    c = module('neighbor_target', 'compare-coff-function.py'); coff = module('neighbor_coff', 'coff_data.py')
    extra = module('neighbor_carriers', 'sdk_x3d_carriers.py'); flow = module('neighbor_flow', 'sdk_image_carriers.py')
    pe = module('neighbor_permissions', 'verify-sdk-x3d-origins.py'); rt = module('neighbor_crt', 'verify-runtime-origins.py')
    authored = module('neighbor_authored', 'verify-authored-origins.py')
    inventory = module('neighbor_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Neighbor target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    own = list(csv.DictReader((ROOT / m['authored_path']).open()))
    if own != [r['record'] for r in m['functions'] if r['accepted_origin']['origin'] == 'authored']: raise ValueError('Neighbor own authored records differ')
    for r in m['functions']:
        if functions[r['address']] != r[state + '_function'] or origins[r['address']] != r[state + '_origin']:
            raise ValueError('Neighbor bounded canonical transition differs')
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (digest(raw) != r['body_sha256'] or list(authored.verify_body(raw, a)) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('Neighbor complete authored native body/CFG differs')
        for call in r['calls']: check_call(raw, a, call)
    for r in m['retained_unknowns']:
        if functions[r['function']['address']] != r['function'] or origins[r['origin']['address']] != r['origin']:
            raise ValueError('Neighbor changes a protected short/private unknown')
    prior = json.loads((ROOT / m['prior']['path']).read_text())
    if (digest((ROOT / m['prior']['path']).read_bytes()) != m['prior']['manifest_sha256']
            or prior['prior']['shared'] != m['prior']['shared'] or prior['prior']['absolute'] != m['prior']['absolute']
            or prior['prior']['crt_archive_sha256'] != m['prior']['crt_archive_sha256']):
        raise ValueError('Neighbor replaces independent prior source ownership')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-nested-initialization-origins.py')],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode: raise ValueError('Neighbor complete prior cold graph failed: ' + result.stderr)
    print(result.stdout.strip(), flush=True)
    old = json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())
    source_catalog = SOURCE.BASE.retained_catalog(old); shared = {'__except_list': 0}
    for r in m['prior']['shared']:
        owner = r['owner']
        if old[owner['collection']][owner['index']] != owner['record'] or source_catalog.get(r['symbol']) != int(r['address'], 16):
            raise ValueError('Neighbor field observation overrides retained full source definition')
        shared[r['symbol']] = source_catalog[r['symbol']]
    records = list(csv.DictReader((ROOT / 'config/authored-origin-evidence.csv').open()))
    switches = list(csv.DictReader((ROOT / 'config/authored-origin-switches.csv').open()))
    direct = list(csv.DictReader((ROOT / 'config/authored-origin-direct-switches.csv').open()))
    for r in m['parents']:
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (r['record'] not in records or functions[r['address']] != r['function'] or origins[r['address']] != r['origin']
                or r['origin']['origin'] != 'authored' or digest(raw) != r['body_sha256']
                or digest(raw) != r['record']['body_sha256']
                or [q for q in switches if q['address'] == r['address']] != r['switches']
                or [q for q in direct if q['address'] == r['address']] != r['direct_switches']
                or list(authored.verify_body(raw, a, r['switches'], lambda x, n: c.pe_bytes_at(target, x, n), r['direct_switches'])) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('Neighbor complete authored game parent/CFG differs')
        for call in r['calls']: check_call(raw, a, call)
    p = m['memset']; q = p['record']; crt = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(crt) != q['archive_sha256'] or q not in list(csv.DictReader((ROOT / 'config/runtime-origin-evidence.csv').open())):
        raise ValueError('Neighbor original memset archive/record differs')
    name, body = {a: (n, b) for a, n, b in rt.archive_members(crt)}[int(q['member_offset'])]
    raw, fields, source = extra.section_carrier(body, p['source']['section'], c, coff); a = int(q['address'], 16)
    aux = next(x for x in source['aux_records'] if x['symbol'] == '_memset')
    if (name != q['member'] or digest(body) != p['member_sha256'] or SOURCE.BASE.canonical_source(source, body) != p['source']
            or fields != p['fields'] or fields or len(raw) != 96 or aux['aux_count'] != 1
            or struct.unpack_from('<I', bytes.fromhex(aux['aux_hex']), 4)[0] != len(raw)
            or raw != c.pe_bytes_at(target, a, 96) or digest(raw) != q['body_sha256']
            or list(authored.verify_body(raw, a)) != p['cfg'] or SOURCE.instructions(raw, a, flow) != p['instructions']
            or functions[q['address']] != p['function'] or origins[q['address']] != p['origin']):
        raise ValueError('Neighbor memset lacks its complete original own-AUX/native/CFG proof')
    shared['_memset'] = a
    scratch = ROOT / 'build/origin-neighbor-policy-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'Neighbor.obj'; control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or headers(result.stdout + result.stderr) != control['headers']:
            raise ValueError('Neighbor cold generic source/original includes differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != control['emission']: raise ValueError('Neighbor omits ordinary code/data/EH emission')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 96 or list(struct.unpack('<24I', layout)) != control['layout_values']:
            raise ValueError('Neighbor crops the complete generic observation carrier')
        if [SOURCE.weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
            raise ValueError('Neighbor loses actual weak AUX/strong fallback')
        rows = m['sections']; decoded = {}
        for r in rows:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff); a = int(r['base'], 16)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                    or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                raise ValueError('Neighbor complete source/AUX/fields/permissions differ')
            decoded[r['source']['section']] = (raw, fields)
            if r['kind'] == 'code':
                actual = [dict(function=f, origin=origins[k]) for k, f in functions.items() if a <= int(k, 16) < a + r['size']]
                expected = [dict(function=selected[q['function']['address']][state + '_function'],
                                 origin=selected[q['function']['address']][state + '_origin'])
                            if q['function']['address'] in selected else q for q in r['inventory_entries']]
                if actual != expected: raise ValueError('Neighbor full source hides an inventory entry')
        for g in m['groups']:
            rows = [r for r in m['sections'] if r['group'] == g['id']]
            catalog = SOURCE.owned_catalog(rows, shared, g['id'], [r for r in m['weak_references'] if r['symbol'] in g['weak_symbols']])
            for r in rows:
                raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
                linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a, data_image=r['kind'] == 'data')
                actual = c.pe_bytes_at(target, a, len(raw))
                if linked != actual or digest(actual) != r['body_sha256']: raise ValueError('Neighbor complete unmasked body differs')
                if r['kind'] == 'code':
                    roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type'] == 32 and d['storage'] == 3)
                    roots.update(f['symbol_offset'] + f['addend'] for q in rows for f in q['fields']
                                 if f['symbol_section'] == r['source']['section'] and f['symbol_storage'] == 6)
                    if sorted(roots) != r['roots'] or flow.flow(actual, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                        raise ValueError('Neighbor complete normal/EH/unwind/shared-exit CFG differs')
        for r in m['alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields'] or len(raw) != r['size']
                    or digest(raw) != r['source_sha256'] or SOURCE.instructions(raw, 0x100000, flow) != r['instructions']):
                raise ValueError('Neighbor complete default/value-initialization control differs')
        explicit = next(r for r in m['sections'] if r['base'] == '0x00458960')
        if (any(f['symbol'].startswith('?clear@') for r in m['alternatives'][:2] for f in r['fields'])
                or sum(f['symbol'].startswith('?clear@') for f in explicit['fields']) != 1):
            raise ValueError('Neighbor implicit/member-zero constructor can replace explicit clear policy93')
        assignment = next(r for r in m['sections'] if r['base'] == '0x00458E70')
        public = next(r for r in m['sections'] if r['base'] == '0x00458B30')
        if (not assignment['symbol'].startswith('?_Assign_n@') or assignment['size'] != 195
                or public['size'] != 29 or len(public['fields']) != 1
                or public['fields'][0]['symbol'] != assignment['symbol']
                or m['alternatives'][2]['size'] != 114):
            raise ValueError('Neighbor replaces count-assignment source with unrelated single insertion')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']), *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('Neighbor immutable source/evidence differs: ' + path)
    replay(m, args.evidence_only)
    print('R211 origins OK: two authored allocation/clear-word policies163 and two original count-assignment '
          'library policies224; 170 scoped whole code/data carriers9581/all402 fields/143 CFGs; 454 ordinary '
          'emissions28704/29 original includes/full combined observation96; default22/member-zero40/single-insert114 '
          'controls; two whole game parents5418/three actual calls; complete original CRT/retained R210 cold proof; '
          'thirteen short/private controls remain unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
