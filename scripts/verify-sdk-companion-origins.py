#!/usr/bin/env python3
"""Replay three whole SDK math companions through the independent R192 graph."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-companion-origin-evidence.json'
MANIFEST_SHA256 = '979517c54be5b7787e8558af22c4d067207619388fe9d20be6ed5d9c3e5d0180'
CONFIDENCE = 'whole-original-sdk-companions-independent-dispatch-graph-and-explicit-header-policy'
KEYS = {'0x0061C89D': ('_D3DXMatrixTransformation@28', 6),
        '0x0061CB7B': ('_D3DXMatrixLookAtLH@16', 328),
        '0x0061E853': ('??DD3DXQUATERNION@@QBE?AU0@ABU0@@Z', 39)}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(data):
    return hashlib.sha256(data).hexdigest()


def verify_plan(m):
    if (m['evidence_id'] != 'R193' or len(m['functions']) != 3
            or {r['address']: (r['symbol'], r['size']) for r in m['controls']} != KEYS
            or len(m['controls']) != 3 or sum(len(r['fields']) for r in m['controls']) != 4
            or set(m['dependencies']) != {'_D3DXVec3Normalize@8', '_D3DXQuaternionMultiply@12'}):
        raise ValueError('SDK companion bounded whole graph differs')
    controls = {r['address']: r for r in m['controls']}
    if {r['address'] for r in m['functions']} != set(KEYS):
        raise ValueError('SDK companion canonical selection differs')
    for r in m['functions']:
        a = r['address']; old = r['original_function']; code = controls[a]
        expected = dict(old, proposed_name=KEYS[a][0], module='D3DX8', owner='library',
                        status='excluded', evidence='R193', notes=r['notes'])
        if (old != code['function'] or r['original_origin'] != code['origin']
                or r['original_origin']['origin'] != 'unknown' or old['owner']
                or old['status'] != 'unclassified' or old['source_file'] or old['signature']
                or old['calling_convention'] or old['match_percent'] != '0.00'
                or int(old['size']) != KEYS[a][1] or r['accepted_function'] != expected
                or r['accepted_origin'] != dict(address=a, origin='library', subsystem='D3DX8',
                    disposition='exclude', confidence=CONFIDENCE, evidence_id='R193')
                or code['flow']['extent'] != KEYS[a][1] or code['flow']['table_size']
                or code['flow']['alignment_size'] or code['member_offset'] != 684528):
            raise ValueError('SDK companion grants unsupported extent/source/ABI/mapping/exact credit')
    tail = controls['0x0061C89D']
    if (tail['fields'][0]['symbol'] != '?g_D3DXFastTable@@3UD3DXFASTTABLE@@A'
            or tail['fields'][0]['addend'] != 156
            or tail['flow']['external_tails'] != [dict(site=0, slot='0x0066D10C', runtime_selected=True)]):
        raise ValueError('SDK Transformation loses its genuine runtime-selected slot')
    if ([f['symbol'] for f in controls['0x0061CB7B']['fields']] != ['_D3DXVec3Normalize@8']*2
            or [f['symbol'] for f in controls['0x0061E853']['fields']] != ['_D3DXQuaternionMultiply@12']):
        raise ValueError('SDK companions lose independently typed actual callees')
    if set(m['header_evidence']) != {'math-declarations', 'quaternion-multiply-body'}:
        raise ValueError('SDK companion header policy evidence differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true'); args = parser.parse_args()
    m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('SDK companion immutable evidence differs')
    for path, sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha:
            raise ValueError('SDK companion retained evidence/source differs: '+path)
    # Reopen the full independent graph, including every callback, initial image and prior anchor.
    result = subprocess.run([str(ROOT/'scripts/repo-python'), 'scripts/verify-sdk-dispatch-origins.py'],
                            cwd=ROOT, check=True, capture_output=True, text=True)
    print('retained R192: '+result.stdout.strip())
    for r in m['header_evidence'].values():
        body = (ROOT/r['path']).read_bytes(); lines = body.splitlines(keepends=True)
        if (digest(body) != r['sha256'] or digest(b''.join(lines[r['first_line']-1:r['last_line']])) != r['region_sha256']):
            raise ValueError('SDK companion actual original header policy differs')
    prior = json.loads((ROOT/'config/sdk-dispatch-origin-evidence.json').read_text())
    catalog = {r['symbol']: int(r['address'], 16) for r in prior['controls']+prior['anchors']}
    table = next(r for r in prior['data'] if (r['member_offset'], r['source']['section']) == (684528, 3))
    base = int(table['base'], 16)
    catalog['?g_D3DXFastTable@@3UD3DXFASTTABLE@@A'] = base
    for sn, r in m['dependencies'].items():
        if next(x for x in prior['controls'] if x['symbol'] == sn) != r:
            raise ValueError('SDK companion independently accepted whole callee differs')
    slots = {base+f['offset']-232 for f in table['fields'] if f['offset'] >= 232}
    c = module('companion_coff', 'compare-coff-function.py'); coff = module('companion_data', 'coff_data.py')
    rt = module('companion_archive', 'verify-runtime-origins.py'); cr = module('companion_code', 'sdk_code_carriers.py')
    cfg = module('companion_cfg', 'sdk_dispatch_carriers.py'); prior_v = module('companion_bind', 'verify-sdk-dispatch-origins.py')
    pe = module('companion_pe', 'verify-sdk-x3d-origins.py')
    target = c.verified_target(); archive = (ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(target) != m['target_sha256'] or digest(archive) != m['archive_sha256']:
        raise ValueError('SDK companion target/archive identity differs')
    members = {o: (n, b) for o, n, b in rt.archive_members(archive)}
    functions = {r['address']: r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; mode = 'original' if args.evidence_only else 'accepted'
    for r in m['controls']:
        address = int(r['address'], 16); name, body = members[r['member_offset']]
        if name != r['member'] or digest(body) != r['member_sha256']:
            raise ValueError('SDK companion original source owner differs')
        raw, fields, source = cr.code_carrier(body, r['symbol'], c, coff)
        if (source != r['source'] or fields != r['fields'] or len(raw) != r['size']
                or digest(raw) != r['source_sha256'] or pe.image_permissions(target, address, len(raw)) != source['flags']&0xe0000000):
            raise ValueError('SDK companion entire original COMDAT/AUX/definitions/fields differ')
        linked, calls, data = prior_v.bind(raw, fields, r['bindings'], catalog, r['member_offset'], address)
        if linked != c.pe_bytes_at(target, address, len(raw)) or digest(linked) != r['body_sha256']:
            raise ValueError('SDK companion whole unmasked target/source comparison differs')
        if cfg.flow(linked, address, [d['offset'] for d in source['peers']], fields, calls, data, slots=slots) != r['flow']:
            raise ValueError('SDK companion whole CFG or runtime-selection policy differs')
        row = selected[r['address']]
        if functions[r['address']] != row[mode+'_function'] or origins[r['address']] != row[mode+'_origin']:
            raise ValueError('SDK companion exact bounded ledger snapshot differs')
        if any(address < int(a, 16) < address+len(raw) for a in functions):
            raise ValueError('SDK companion whole source carrier hides an inventoried entry')
    print('R193 origins OK:three complete library companions /373 bytes /four actual fields;full R192 graph replay;original Transformation runtime slot,whole LookAtLH and explicit quaternion multiplication operator;header policy independently retained;no source/ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
