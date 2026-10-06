#!/usr/bin/env python3
"""Replay whole SDK font/save wrappers, independent owners and cold public controls."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('public_wrapper_source', ROOT/'scripts/verify-sdk-presentation-origins.py')
BASE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(BASE)
module = BASE.module
digest = BASE.digest
metadata_digest = BASE.metadata_digest
EVIDENCE = 'config/sdk-public-wrapper-origin-evidence.json'
MANIFEST_SHA256 = '7995f491ec17ac705a543d8cc32d3ede2e72bf429d47e103d3c4138d2553195c'
PLAN_DIGESTS = {'evidence_id': '80ca039e447430572e648fe28f928255dd31580e0eac789a82adcd91e17b980b', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'archive_sha256': '2cfb6758c3611ae3f9310a032a3fde938b2bf4b0a0682c1677a868ab6cc1f1af', 'functions': 'af33ad883777520ea28e332acdee2cbf017f97c71d1b45636773359eebe5ff6f', 'providers': 'f87913cbfe30902735bce78301968e5b38ef33f9abb24a8ed04ebb7a231e643d', 'ordinary_controls': 'a7a05fa2436341f3ceb7b243958250d7f670448b7fdbcb9518be0bf5d465c0a0', 'clients': '203d5c6bacce8fd4e0c081092ef70032a43a3bf27b84490232c4c03b2412b3fc', 'peer_controls': '9785243e7da8522559aab48edaa964544d741949a2a24f008aa1edafa817528f', 'boundaries': '110c4001d1485008d6726130b862720ce3261e58947ae3512077fe0da9d36e14', 'adjacent_carriers': 'd2521e1c30d62b57d7db1cb40c322c70c1b19c4abf6385a5b69a85328a71cf2c', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'canonical': '430a6bb56056c713b9e1a2b964a48c0c0a7004c9d3a2a089a2849ffafb361dea', 'unselected_sha256': '166697403012a49a8d757543172e0b1afc8cb66ff5608de685af494f1492606b', 'public_control': 'a633a09aa46ca5ffe72970e5861e4a79dd8c156f40e4e86f0300f681dbeb92c7', 'retained_sha256': '20ccfcd045afa1d5ddae57038433047b3a68ec7cc6d26a3742a2a5612824959f', 'interpretation': '43849e3974874449a6c3c75af620bcab2534a895a0aec0c2521362dc2bfd7983'}
WHOLE = {'0x00605185': 51, '0x006055A2': 32, '0x006055C2': 32,
         '0x0060577E': 32, '0x0060579E': 32}
CONFIDENCE = 'whole-original-sdk-public-wrapper-scoped-source-import-and-distinct-save-owner-routes'
SOURCE = module('wrapper_source_metadata', 'verify-vector-insertion-carrier-origins.py')
HEADERS = module('wrapper_headers', 'verify-sdk-interface-origins.py').included_headers


def rows(name):
    with (ROOT/'config'/name).open() as source:
        return list(csv.DictReader(source))


def unselected_digest(records):
    return metadata_digest([r for r in records if r['address'] not in WHOLE])


def verify_plan(m):
    if set(m) != set(PLAN_DIGESTS):
        raise ValueError('Public wrapper immutable schema differs')
    for key, sha in PLAN_DIGESTS.items():
        if metadata_digest(m[key]) != sha:
            raise ValueError('Public wrapper complete immutable evidence differs: '+key)
    if (m['evidence_id'] != 'R229' or {r['address']: r['size'] for r in m['functions']} != WHOLE
            or sum(len(r['fields']) for r in m['functions']) != 6
            or len(m['providers']) != 3 or sum(r['record']['size'] for r in m['providers']) != 463
            or len(m['ordinary_controls']) != 5 or len(m['peer_controls']) != 8
            or len(m['adjacent_carriers']) != 1 or m['adjacent_carriers'][0]['size'] != 25
            or m['historical_snapshots'] or len(m['clients']) != 5
            or m['archive_sha256'] != '39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28'):
        raise ValueError('Public wrapper loses bounded full owners/fields/controls/history')
    for r in m['functions']:
        f, o, af, ao = [r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin']]
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified'
                or {k: v for k, v in f.items() if k not in mutable} != {k: v for k, v in af.items() if k not in mutable}
                or af['owner'] != 'library' or af['status'] != 'excluded' or af['module'] != 'D3DX8'
                or af['source_file'] or af['signature'] or af['calling_convention'] or af['match_percent'] != '0.00'
                or ao != dict(address=r['address'], origin='library', subsystem='D3DX8', disposition='exclude',
                              confidence=CONFIDENCE, evidence_id='R229')):
            raise ValueError('Public wrapper changes extent or grants source/private ABI/exact credit')


def verify_canonical(m, evidence_only=False):
    fs, origins = rows('functions.csv'), rows('function-origins.csv')
    if evidence_only:
        for name, records in [('functions.csv', fs), ('function-origins.csv', origins)]:
            if unselected_digest(records) != m['unselected_sha256'][name]:
                raise ValueError('Public wrapper original transition changes unrelated canonical rows')
    fs = {r['address']: r for r in fs}; origins = {r['address']: r for r in origins}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    for q in m['canonical']:
        a = q['function']['address']
        expected = q if a not in selected else dict(function=selected[a][state+'_function'], origin=selected[a][state+'_origin'])
        if dict(function=fs[a], origin=origins[a]) != expected:
            raise ValueError('Public wrapper scoped canonical owner differs: '+a)


def provider_catalog(m, fields, member_offset, imports):
    """Use actual defining owners and named PE imports, never encoded call destinations."""
    keys = module('wrapper_local_keys', 'verify-sdk-x3d-origins.py'); catalog = {}
    for f in fields:
        key = BASE.source_key(member_offset, f, keys)
        if f['symbol'] == '__imp__GetObjectA@12':
            found = [a for a, (dll, name) in imports.items() if dll.lower() == 'gdi32.dll' and name == 'GetObjectA']
            if len(found) != 1 or f['symbol_storage'] != 2 or f['symbol_section'] != 0 or f['type'] != 'DIR32':
                raise ValueError('Public wrapper import lacks unique actual named GDI32 source identity')
            value = found[0]
        else:
            owners = [p['record'] for p in m['providers'] if p['record']['symbol'] == f['symbol']]
            if len(owners) != 1:
                raise ValueError('Public wrapper field lacks independent whole defining owner')
            r = owners[0]
            definitions = [d for d in r['source']['definitions'] if d['symbol'] == f['symbol']]
            if (len(definitions) != 1 or r['member_offset'] != member_offset
                    or r['source']['section'] != f['symbol_section']
                    or definitions[0]['offset'] != f['symbol_offset']
                    or definitions[0]['type'] != f['symbol_type'] or f['symbol_type'] != 32
                    or definitions[0]['storage'] != f['symbol_storage']):
                raise ValueError('Public wrapper local/global source definition differs')
            value = int(r['base'], 16)+definitions[0]['offset']
        if key in catalog and catalog[key] != value:
            raise ValueError('Public wrapper conflicting scoped source ownership')
        catalog[key] = value
    return catalog


def verify_native(m, target, c, flow):
    authored = module('wrapper_native', 'verify-authored-origins.py')
    for r in m['functions']:
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (digest(raw) != r['body_sha256'] or SOURCE.instructions(raw, a, flow) != r['instructions']
                or list(authored.verify_body(raw, a)) != r['cfg']):
            raise ValueError('Public wrapper full native body/CFG/exits differs')
    for r in m['boundaries']:
        raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if digest(raw) != r['sha256']:
            raise ValueError('Public wrapper folds external alignment into the full source extent')
        if r['kind'] == 'alignment':
            if raw.hex() != r['hex'] or raw != b'\xcc'*r['size']:
                raise ValueError('Public wrapper loses actual outside INT3 alignment')
        elif r['kind'] == 'complete-noninventory-code':
            if (SOURCE.instructions(raw, int(r['address'], 16), flow) != r['instructions']
                    or list(authored.verify_body(raw, int(r['address'], 16))) != r['cfg']):
                raise ValueError('Public wrapper hides adjacent complete code as alignment')
        else: raise ValueError('Public wrapper unknown boundary evidence')


def verify_archived(m, target, c, coff, flow):
    runtime = module('wrapper_archive', 'verify-runtime-origins.py')
    extra = module('wrapper_sections', 'sdk_x3d_carriers.py')
    pe = module('wrapper_permissions', 'verify-sdk-x3d-origins.py')
    imports = module('wrapper_imports', 'verify-import-origins.py').pe_imports(target, c)
    archive = (ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(archive) != m['archive_sha256']:
        raise ValueError('Public wrapper original SDK archive differs')
    members = {o: (name, body) for o, name, body in runtime.archive_members(archive)}
    for r in m['adjacent_carriers']:
        name, body = members[r['member_offset']]
        raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
        a = int(r['address'], 16); native = c.pe_bytes_at(target, a, r['size'])
        if (name != r['member'] or digest(body) != r['member_sha256'] or source != r['source']
                or fields != r['fields'] or fields or len(raw) != r['size'] or raw != native
                or digest(raw) != r['source_sha256'] or digest(native) != r['body_sha256']
                or any(a <= int(q['address'], 16) < a+len(raw) for q in rows('functions.csv'))
                or not any(d['symbol'] == r['symbol'] and d['type'] == 32 and d['storage'] == 2 and d['offset'] == 0
                           for d in source['definitions'])):
            raise ValueError('Public wrapper adjacent whole defining source carrier differs or gains credit')
    for r in m['functions']+m['peer_controls']:
        name, body = members[r['member_offset']]
        raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
        a = int(r.get('address', r.get('native')), 16)
        if (name != r['member'] or digest(body) != r['member_sha256'] or source != r['source']
                or fields != r['fields'] or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000
                or not any(d['symbol'] == r['symbol'] and d['type'] == 32 and d['storage'] == 2 and d['offset'] == 0
                           for d in source['definitions'])):
            raise ValueError('Public wrapper complete original COFF/AUX/fields/extent differs')
        catalog = provider_catalog(m, fields, r['member_offset'], imports)
        linked, calls, data = BASE.bind_fields(raw, fields, r['bindings'], catalog, r['member_offset'], a)
        native = c.pe_bytes_at(target, a, r['size'])
        if 'address' in r:
            if (linked != native or digest(native) != r['body_sha256']
                    or flow.flow(native, a, [0], fields, calls, data, None, None, None) != r['flow']):
                raise ValueError('Public wrapper whole unmasked original source/native comparison differs')
        else:
            differences = [i for i, (x, y) in enumerate(zip(linked, native)) if x != y]
            if not differences or differences != r['whole_differences'] or digest(native) != r['native_sha256']:
                raise ValueError('Public wrapper complete original wrong-route peer is not rejected')
            if r['kind'] == 'wrong-A-W':
                if differences != [4]: raise ValueError('Public wrapper merges distinct encoding flag routes')
            elif r['kind'] == 'wrong-surface-volume':
                if not set(differences) <= {i for f in fields for i in range(f['offset'], f['offset']+4)}:
                    raise ValueError('Public wrapper peer differs beyond its independently defining helper field')
            else: raise ValueError('Public wrapper unknown peer role')


def verify_cold(m, body, target, c, coff, flow):
    extra = module('wrapper_cold_sections', 'sdk_x3d_carriers.py')
    inventory = module('wrapper_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body, c, coff) != control['emission']:
        raise ValueError('Public wrapper full cold ordinary emission differs')
    raw, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
    if list(struct.unpack('<8I', raw)) != control['layout_values']:
        raise ValueError('Public wrapper loses the complete readonly SDK layout observation')
    selected = {r['address']: r for r in m['functions']}
    for r in m['ordinary_controls']+m['clients']:
        raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
        if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or SOURCE.instructions(raw, 0, flow) != r['instructions']):
            raise ValueError('Public wrapper complete cold source/AUX/fields/instructions differ')
        if 'native' in r:
            positive = selected[r['native']]; a = int(r['native'], 16); catalog = {}
            for f in fields:
                # These are compatible ordinary declarations, not recovered game
                # signatures. Their bindings refer to the independently proved
                # SDK helper/import owners of this same complete positive route.
                owners = [b for b in positive['bindings'] if b['type'] == f['type']]
                if len(owners) != 1: raise ValueError('Public wrapper ordinary model lacks one independent route owner')
                catalog[f['symbol']] = int(owners[0]['source_base'], 16)
            linked, calls, data = BASE.bind_fields(raw, fields, r['bindings'], catalog, 0, a)
            native = c.pe_bytes_at(target, a, positive['size'])
            if linked != native or len(raw) != positive['size'] or not r['unmasked_byte_equal']:
                raise ValueError('Public wrapper whole ordinary compatibility differs')
            if flow.flow(native, a, [0], fields, calls, data, None, None, None) != r['flow']:
                raise ValueError('Public wrapper complete ordinary call/return graph differs')
        elif len(fields) != 1 or fields[0]['type'] != 'REL32' or fields[0]['symbol'] != r['api']:
            raise ValueError('Public wrapper actual SDK public declaration/call symbol differs')


def replay(m, evidence_only=False):
    c = module('wrapper_target', 'compare-coff-function.py'); coff = module('wrapper_coff', 'coff_data.py')
    flow = module('wrapper_flow', 'sdk_image_carriers.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Public wrapper target identity differs')
    for path, sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha: raise ValueError('Public wrapper retained evidence/source differs: '+path)
    verify_canonical(m, evidence_only)
    verify_native(m, target, c, flow)
    seen = set()
    for p in m['providers']:
        prior = json.loads((ROOT/p['path']).read_text()); old = module('wrapper_retained_'+str(len(seen)), Path(p['script']).name)
        old.verify_plan(prior)
        if (old.EVIDENCE != p['path'] or old.MANIFEST_SHA256 != p['manifest_sha256']
                or digest((ROOT/p['path']).read_bytes()) != p['manifest_sha256']
                or digest((ROOT/p['script']).read_bytes()) != p['script_sha256']
                or metadata_digest(prior) != p['plan_sha256'] or prior['sections'][p['section_index']] != p['record']):
            raise ValueError('Public wrapper replaces immutable whole retained owner/proof')
        if p['script'] not in seen:
            result = subprocess.run([str(ROOT/'scripts/repo-python'), str(ROOT/p['script'])], cwd=ROOT, capture_output=True, text=True)
            if result.returncode: raise ValueError('Public wrapper retained whole cold proof failed: '+result.stderr)
            print(result.stdout.strip(), flush=True); seen.add(p['script'])
    verify_archived(m, target, c, coff, flow)
    control = m['public_control']; scratch = ROOT/'build/origin-sdk-public-wrapper-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'SdkPublicWrappers.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'), str(ROOT/control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or HEADERS(result.stdout+result.stderr) != control['headers']:
            raise ValueError('Public wrapper cold source/original headers differ')
        verify_cold(m, obj.read_bytes(), target, c, coff, flow)


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256: raise ValueError('Public wrapper immutable manifest differs')
    replay(m, args.evidence_only)
    print('R229:five whole SDK public font/surface/volume wrappers179/all6 fields; three independent source owners463 '
          'and whole R201/R202 cold graphs; five byte-equal ordinary controls, eight whole rejected route peers and actual public ABI declarations; '
          'historical replacement absence remains unproven; no source/private ABI/mapping/exact credit.')


if __name__ == '__main__': main()
