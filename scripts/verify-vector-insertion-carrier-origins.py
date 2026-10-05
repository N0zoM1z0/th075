#!/usr/bin/env python3
"""Cold-replay whole public vector insertion graphs and audited interior origins."""
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
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result); return result


BASE = module('insertion_source', 'verify-vector-at-policy-origins.py')
HEADERS = module('insertion_headers', 'verify-vector-list-leaf-alternatives-origins.py').headers
digest = BASE.digest
EVIDENCE = 'config/vector-insertion-carrier-origin-evidence.json'
MANIFEST_SHA256 = 'fe3ac742c24edcbdd5d3f5d5f938071edf8eac728c1ef8f3016bf45b0a5468cd'
PLAN_DIGESTS = {'groups': 'f13d788b71c9bb2b76686a5756f56d8d56c7cb1a8b55a532b51f80b1209d9b72', 'sections': '0abbef5b24f4fda4aa4deb71e941e97af1846de6dc175172c8be1b95f3192e1e', 'weak_references': 'ab68dcbaf46a5add59e8e06f231309ad2047397005985194547aacbc9f9f1e0c', 'evidence_id': 'c060396bc944fb8bd8d37d56b7127875b9c9454a7a377e0ba457372a543d184b', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'crt_archive_sha256': '69d0301fde85b097b2afc8e5732879473468d247ae0b55492fdc2063da1f7f6c', 'retained_sha256': '076872d076c70905bb58e356a2e7ad0a475135e82f5cd4304f6af8109e57d565', 'functions': '8d7723813622fcbeed46e038d03aca23de94b9a96c7bbd61f09bdff91fbfcced', 'interiors': '874473c26e9f4f37168f66441628693821055e07f2bde8a45872c8b579d75599', 'shared': 'f110ddebfdd8f17bd3e6b705ba61f31fd66559a3ca3cb3e35c349eb0514ad423', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'opaque_api': '19a0f23a40d08dc1558bcb66d53232ad2f65e4b789c8b50ca60f18de6a07dfd2', 'public_control': 'a243e70b477ee122e641fc6acf224ba6ecf18460ff72efacea82a66899bda9bb', 'alternatives': 'c8d1e5c0880292cc0d094298e82c61ef9df970fdbb3f97c83decc84c8b918466', 'historical_snapshots': '1f67ab62586d5bed46a6ad616cffbcf270fdfc08f8781ed15bf0d55c0cd1fe11', 'retained_unknowns': 'f31f5b151e1979f44cb5ca1f7687e9cfbc7708c785bd4c72ea505ae03607a1eb'}
ROOTS = {'0x0040A210': 796, '0x0040EDB0': 796, '0x0045A130': 796,
         '0x004594B0': 814, '0x0040EA30': 834, '0x005F9650': 830}
CONFIDENCE = 'complete-original-vector-insertion-source-scoped-normal-eh-graph'
COMPILER_CONFIDENCE = 'complete-source-carrier-shared-eh-register-and-chain-restoration'


def instructions(raw, address, flow):
    return [dict(offset=i.address-address, size=i.size, mnemonic=i.mnemonic, operands=i.op_str)
            for i in flow.instructions(bytes(raw), address, len(raw))]


def weak_record(body, symbol, c, coff):
    weak = module('insertion_weak', 'verify-standard-exception-origins.py')
    result = weak.read_weak_reference(body, symbol, c, coff, 0)
    result.pop('member_offset'); result.pop('strong_archive_definitions')
    table = struct.unpack_from('<I', body, 8)[0]
    at = table + (result['symbol_index'] + 1) * 18
    result['aux_hex'] = body[at:at+18].hex()
    result['source_kind'] = 'standalone-cold-public-object; no archive selection claim'
    return result


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Insertion immutable complete evidence differs: ' + key)
    if (m['evidence_id'] != 'R208' or len(m['functions']) != 20 or len(m['interiors']) != 14
            or len(m['groups']) != 6 or [g['width'] for g in m['groups']] != [4, 4, 4, 16, 44, 16]
            or {g['root']: g['whole_size'] for g in m['groups']} != ROOTS
            or len(m['sections']) != 263 or sum(r['size'] for r in m['sections']) != 15334
            or sum(len(r['fields']) for r in m['sections']) != 638
            or sum(r['kind'] == 'code' for r in m['sections']) != 209
            or len(m['shared']) != 15 or len(m['weak_references']) != 1
            or len(m['historical_snapshots']) != 4 or len(m['retained_unknowns']) != 5
            or len(m['alternatives']) != 7):
        raise ValueError('Insertion loses bounded whole code/data/field/interior context')
    for r in m['functions']:
        old, origin = r['original_function'], r['original_origin']; accepted = r['accepted_function']
        compiler = r['role'] == 'shared-eh-epilogue'; kind = 'compiler' if compiler else 'library'
        subsystem = 'VC71Compiler' if compiler else 'VC71STL'
        expected = dict(old, size=str(r['size']), span_end=f"0x{int(r['address'],16)+r['size']-1:08X}",
                        proposed_name=('VC7.1 shared EH epilogue [interior]' if compiler else
                            ('std::vector::_Insert_n [element type unknown]' if r['role'] == 'whole-insertion-policy'
                             else 'std::vector::_Insert_n catch [interior; element type unknown]')),
                        module=subsystem, status='excluded', owner=kind,
                        evidence='R208; ' + EVIDENCE + '; scripts/repo-python scripts/verify-vector-insertion-carrier-origins.py',
                        notes=r['notes'])
        if (origin['origin'] != 'unknown' or old['status'] != 'unclassified' or accepted != expected
                or old['match_percent'] != '0.00' or any(old[k] for k in ['source_file', 'owner', 'signature', 'calling_convention'])
                or (r['role'] != 'whole-insertion-policy' and (old['size'] != str(r['size']) or old['span_end'] != accepted['span_end']))
                or (compiler and (r['size'] != 19 or r['source_definitions']))
                or r['accepted_origin'] != dict(address=r['address'], origin=kind, subsystem=subsystem, disposition='exclude',
                    confidence=COMPILER_CONFIDENCE if compiler else CONFIDENCE, evidence_id='R208')):
            raise ValueError('Insertion changes unsupported declaration/extent/exact or origin state')
    for r in m['retained_unknowns']:
        if (r['origin']['origin'] != 'unknown' or r['function']['status'] != 'unclassified'
                or r['function']['owner'] or r['function']['source_file'] or r['function']['calling_convention']
                or r['function']['signature'] or r['function']['match_percent'] != '0.00'):
            raise ValueError('Insertion generic cleanup alternatives gain private ownership or exact credit')


def owned_catalog(rows, shared, group, weak):
    """Use complete source owners and actual local indices, never field observations."""
    catalog = dict(shared); owners = {}
    for r in rows:
        section = r['source']['section']; address = int(r['base'], 16)
        if section in owners: raise ValueError('Insertion duplicates a scoped whole source owner')
        owners[section] = address
        for d in r['source']['definitions']:
            if d['storage'] != 2: continue
            value = address + d['offset']
            if d['symbol'] in catalog and catalog[d['symbol']] != value:
                raise ValueError('Insertion replaces independent retained source ownership')
            catalog[d['symbol']] = value
    for r in rows:
        for f in r['fields']:
            if f['symbol_storage'] == 3 and f['symbol_section'] > 0:
                owner = owners.get(f['symbol_section'])
                if owner is None: raise ValueError('Insertion local field has no whole scoped source owner')
                key = (group, f['symbol_section'], f['symbol_index'])
                value = owner + f['symbol_offset']
                if key in catalog and catalog[key] != value: raise ValueError('Insertion local index changes ownership')
                catalog[key] = value
    for ref in weak:
        fallback = ref['fallback_symbol']
        definition = ref['fallback_definition']; owner = owners.get(definition['section'])
        if owner is None or catalog.get(fallback) != owner + definition['offset']:
            raise ValueError('Insertion actual weak fallback lacks its complete strong source body')
        catalog[ref['symbol']] = catalog[fallback]
    return catalog


def replay(m, evidence_only=False):
    c = module('insertion_target', 'compare-coff-function.py'); coff = module('insertion_coff', 'coff_data.py')
    extra = module('insertion_carriers', 'sdk_x3d_carriers.py'); flow = module('insertion_flow', 'sdk_image_carriers.py')
    pe = module('insertion_permissions', 'verify-sdk-x3d-origins.py'); rt = module('insertion_crt', 'verify-runtime-origins.py')
    authored = module('insertion_authored', 'verify-authored-origins.py')
    inventory = module('insertion_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Insertion target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    for r in m['functions']:
        if functions[r['address']] != r[state + '_function'] or origins[r['address']] != r[state + '_origin']:
            raise ValueError('Insertion canonical selected transition differs: ' + r['address'])
    for r in m['retained_unknowns']:
        if functions[r['function']['address']] != r['function'] or origins[r['origin']['address']] != r['origin']:
            raise ValueError('Insertion changes protected unknown lifetime/destruction evidence')
    # R150 independently cold-replays all its complete original owners and original
    # CRT dependencies. Its ledger selections are disjoint from this successor.
    prior = json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-nested-deque-size-origins.py')],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode: raise ValueError('Insertion independent retained cold graph failed: ' + result.stderr)
    print(result.stdout.strip(), flush=True)
    prior_catalog = BASE.retained_catalog(prior); shared = {}
    for r in m['shared']:
        owner = r['owner']; q = prior[owner['collection']][owner['index']]
        if q != owner['record'] or prior_catalog.get(r['symbol']) != int(r['address'], 16):
            raise ValueError('Insertion replaces independently defined retained owner')
        shared[r['symbol']] = prior_catalog[r['symbol']]
        if r['body_sha256'] is not None and digest(c.pe_bytes_at(target, int(q['address'], 16), q['size'])) != r['body_sha256']:
            raise ValueError('Insertion whole retained owner body differs')
        if 'function' in r and (functions[r['address']] != r['function'] or origins[r['address']] != r['origin']):
            raise ValueError('Insertion changes retained canonical ownership')
    crt = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(crt) != m['crt_archive_sha256']: raise ValueError('Insertion original CRT archive differs')
    absolute = m['absolute']['__except_list']; members = {a: (n, b) for a, n, b in rt.archive_members(crt)}
    name, body = members[absolute['member_offset']]
    if (name != absolute['member'] or digest(body) != absolute['member_sha256']
            or [d for d in coff.parse_symbols(body, c.coff_name)[1] if d['symbol'] == '__except_list' and d['section'] != 0]
            != [absolute['definition']] or absolute['definition']['section'] != -1 or absolute['definition']['offset']):
        raise ValueError('Insertion loses original absolute CRT AUX owner')
    shared['__except_list'] = 0
    p = m['opaque_api']; a = int(p['address'], 16); raw = c.pe_bytes_at(target, a, int(p['function']['size']))
    evidence = list(csv.DictReader((ROOT / 'config/authored-origin-evidence.csv').open()))
    switches = [r for r in csv.DictReader((ROOT / 'config/authored-origin-switches.csv').open()) if r['address'] == p['address']]
    direct = [r for r in csv.DictReader((ROOT / 'config/authored-origin-direct-switches.csv').open()) if r['address'] == p['address']]
    if (p['record'] not in evidence or p['origin']['origin'] != 'authored' or len(raw) != 75
            or functions[p['address']] != p['function'] or origins[p['address']] != p['origin']
            or digest(raw) != p['body_sha256'] or p['record']['body_sha256'] != digest(raw)
            or switches != p['switches'] or direct != p['direct_switches']
            or list(authored.verify_body(raw, a, switches, lambda x, n: c.pe_bytes_at(target, x, n), direct)) != p['cfg']
            or instructions(raw, a, flow) != p['instructions']
            or p['instructions'][3]['operands'] != 'dword ptr [ebp - 0xc], ecx'
            or p['instructions'][-1]['mnemonic'] != 'ret' or p['instructions'][-1]['operands']):
        raise ValueError('Insertion complete opaque target policy/receiver ABI differs')
    # This is a target-observed compatible receiver binding, not recovery of an
    # original mangled declaration or proof of the generic fixture's target type.
    shared[p['symbol']] = a
    for old in m['historical_snapshots']:
        history = json.loads((ROOT / old['path']).read_text()); q = old['record']; r = selected[q['address']]
        if (q not in history['snapshots'] or q['function'] != r['original_function'] or q['origin'] != r['original_origin']
                or digest(c.pe_bytes_at(target, int(q['address'], 16), q['size'])) != q['body_sha256']):
            raise ValueError('Insertion alters original protected R161/R162 history')
    scratch = ROOT / 'build/origin-vector-insertion-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'VectorInsertion.obj'; control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or HEADERS(result.stdout + result.stderr) != control['headers']:
            raise ValueError('Insertion cold public source/original includes differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != control['emission']: raise ValueError('Insertion full ordinary code/data/EH emission differs')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 40 or list(struct.unpack('<10I', layout)) != control['layout_values']:
            raise ValueError('Insertion complete generic payload observations differ')
        if [weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
            raise ValueError('Insertion original weak AUX tag/search/strong definition differs')
        decoded = {}; catalogs = {}
        for g in m['groups']:
            rows = [r for r in m['sections'] if r['group'] == g['id']]
            for r in rows:
                raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
                source = BASE.canonical_source(source, body); a = int(r['base'], 16)
                if (source != r['source'] or fields != r['fields'] or digest(raw) != r['source_sha256'] or len(raw) != r['size']
                        or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                    raise ValueError('Insertion whole source/AUX/actual fields differ')
                decoded[(g['id'], source['section'])] = (raw, fields)
                if r['kind'] == 'code':
                    current = [dict(function=f, origin=origins[k]) for k, f in functions.items() if a <= int(k, 16) < a + r['size']]
                    expected = [dict(function=selected[q['function']['address']][state+'_function'],
                                     origin=selected[q['function']['address']][state+'_origin'])
                                if q['function']['address'] in selected else q for q in r['inventory_entries']]
                    if current != expected: raise ValueError('Insertion whole carrier hides/changes a canonical interior')
            catalog = owned_catalog(rows, shared, g['id'], m['weak_references']); catalogs[g['id']] = catalog
            for r in rows:
                raw, fields = decoded[(g['id'], r['source']['section'])]; a = int(r['base'], 16)
                linked, calls, data = BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a, data_image=r['kind']=='data')
                actual = c.pe_bytes_at(target, a, len(raw))
                if linked != actual or digest(actual) != r['body_sha256']:
                    raise ValueError('Insertion entire unmasked source/native body differs')
                if r['kind'] == 'code':
                    roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type']==32 and d['storage']==3)
                    roots.update(f['symbol_offset']+f['addend'] for q in rows for f in q['fields']
                                 if f['symbol_section']==r['source']['section'] and f['symbol_storage']==6)
                    if sorted(roots) != r['roots'] or flow.flow(actual, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                        raise ValueError('Insertion complete normal/catch/unwind/shared-tail CFG differs')
        for r in m['interiors']:
            parent = next(q for q in m['sections'] if q['group']==r['group'] and q['base']==r['parent'])
            raw, fields = decoded[(r['group'], parent['source']['section'])]; a = int(r['address'], 16)
            actual = c.pe_bytes_at(target, a, r['size'])
            definitions = [d for d in parent['source']['definitions'] if d['offset']==r['offset'] and d['type']==32]
            if (definitions != r['source_definitions'] or digest(actual) != r['body_sha256']
                    or instructions(actual, a, flow) != r['instructions'] or r['offset']+r['size'] > parent['size']
                    or r['offset'] not in {i.address-int(parent['base'],16) for i in flow.instructions(
                        c.pe_bytes_at(target, int(parent['base'],16), parent['size']), int(parent['base'],16), parent['size'])}):
                raise ValueError('Insertion interior lacks whole real parent ownership')
            if r['role']=='shared-eh-epilogue':
                if [(i['mnemonic'],i['operands']) for i in r['instructions']] != [
                        ('mov','ecx, dword ptr [ebp - 0xc]'),('mov','dword ptr fs:[0], ecx'),
                        ('pop','edi'),('pop','esi'),('pop','ebx'),('mov','esp, ebp'),('pop','ebp'),('ret','0xc')]:
                    raise ValueError('Insertion compiler interior has non-restoration semantics')
        for r in m['alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            reference, _ = decoded[(r['reference_group'], r['reference_section'])]
            if (BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']):
                raise ValueError('Insertion complete generic alternative source differs')
            if r['role']=='rejected-full-fill':
                differences = [dict(offset=i,alternative=x,reference=y) for i,(x,y) in enumerate(zip(raw,reference)) if x!=y]
                if fields or len(raw)!=36 or len(reference)!=36 or differences != r['differences'] or len(differences)!=5:
                    raise ValueError('Insertion scalar/aggregate whole fill rejection differs')
            elif r['role']=='rejected-direct-delete':
                if len(raw)!=34 or len(reference)!=43 or raw==reference:
                    raise ValueError('Insertion guarded/direct delete whole alternative is not rejected')
            else:
                if raw != reference: raise ValueError('Insertion whole byte-equal alternative differs')
                if r['role']=='byte-equal-whole-destruction':
                    linked, _, _ = BASE.BASE.bind_fields(raw, fields, r['bindings'], catalogs[r['reference_group']],
                                                        r['reference_group'], int(r['reference'],16))
                    if linked != c.pe_bytes_at(target,int(r['reference'],16),len(raw)):
                        raise ValueError('Insertion ordinary destruction changes its actual private callee')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE,MANIFEST_SHA256),(m['public_control']['probe'],m['public_control']['probe_sha256']),
                      *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('Insertion immutable evidence/source differs: '+path)
    replay(m, args.evidence_only)
    print('R208 origins OK: six complete insertion carriers4866; twelve library catch interiors and two compiler shared '
          'epilogues19 each; 20 audited transitions; 263 complete scoped code/data sections15334/all638 actual fields; '
          '209 complete CFGs; full334 ordinary cold emissions20598/27 headers/layout40; actual weak and absolute CRT '
          'owners; full independent R150 cold graph and whole authored receiver policy75; five cleanup alternatives '
          'remain unknown; R161/R162 history preserved under the explicit successor transition; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
