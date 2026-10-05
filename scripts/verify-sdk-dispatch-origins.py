#!/usr/bin/env python3
"""Replay complete original SDK default-table, selector and dispatch provenance."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-dispatch-origin-evidence.json'
MANIFEST_SHA256 = '41530c573f88cd39b09d53051ed9c5268f4efbafd53ec92cfeb16c2364416b51'
CONFIDENCE = 'whole-original-sdk-default-table-callbacks-runtime-dispatch-and-independent-crt-callers'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(data):
    return hashlib.sha256(data).hexdigest()


def verify_plan(m):
    if (m['evidence_id'] != 'R192' or len(m['functions']) != 53
            or sum(r['size'] for r in m['functions']) != 3468
            or len(m['controls']) != 129 or sum(r['size'] for r in m['controls']) != 14378
            or sum(len(r['fields']) for r in m['controls']) != 298
            or len(m['data']) != 18 or sum(r['size'] for r in m['data']) != 544
            or sum(len(r['fields']) for r in m['data']) != 112
            or len(m['anchors']) != 7):
        raise ValueError('SDK dispatch bounded graph differs')
    selected = {r['address']: r for r in m['functions']}
    code = {r['address']: r for r in m['controls']}
    if len(selected) != 53 or len(code) != 129:
        raise ValueError('SDK dispatch duplicate source entry')
    for a, r in selected.items():
        old, new = r['original_function'], r['accepted_function']
        origin = r['accepted_origin']; subsystem = 'VC71CRT' if a == '0x00643FC6' else 'D3DX8'
        expected = dict(old, proposed_name=code[a]['symbol'], module=subsystem,
                        status='excluded', owner='library', evidence='R192', notes=r['notes'])
        if (new != expected or r['original_origin']['origin'] != 'unknown'
                or origin != dict(address=a, origin='library', subsystem=subsystem,
                                  disposition='exclude', confidence=CONFIDENCE, evidence_id='R192')
                or r['size'] != int(old['size']) or r['size'] != code[a]['flow']['extent']
                or old['source_file'] or old['signature'] or old['calling_convention']
                or old['match_percent'] != '0.00' or old['owner'] or old['status'] != 'unclassified'):
            raise ValueError('SDK dispatch grants unsupported extent/source/ABI/mapping/exact credit')
    table = next(r for r in m['data'] if (r['member_offset'], r['source']['section']) == (684528, 3))
    if (table['base'] != '0x0066D070' or table['size'] != 460
            or [f['offset'] for f in table['fields'] if f['offset'] >= 232] != list(range(232, 460, 4))):
        raise ValueError('SDK dispatch loses the whole original default bank')
    # Null Ln/Exp slots are genuine initial bytes; all57 defaults are separately owned.
    if {r['symbol'] for r in m['anchors']} != {
            '?x86_D3DXInitFastTable@@YAXPAUD3DXFASTTABLE@@@Z',
            '?GetD3DRegValue@@YAHKPADPAXK@Z', '?D3DXIsProcessorFeaturePresent@@YAHI@Z',
            '?x3d_D3DXInitFastTable@@YAXPAUD3DXFASTTABLE@@@Z',
            '?sse2_D3DXInitFastTable@@YAXPAUD3DXFASTTABLE@@@Z',
            '?sse_D3DXInitFastTable@@YAXPAUD3DXFASTTABLE@@@Z', '__CIacos'}:
        raise ValueError('SDK dispatch loses an independent prior dependency')
    finite_calls = [(r['address'], f['offset']) for r in m['controls'] for f in r['fields'] if f['symbol'] == '__finite']
    if finite_calls != [('0x0061BE75', 756), ('0x0061DD91', 98)]:
        raise ValueError('SDK finite loses either complete independent actual caller')
    for r in m['controls']:
        if (r['function'] is not None and r['origin']['origin'] == 'unknown') != (r['address'] in selected):
            raise ValueError('SDK dispatch selection differs from complete source graph')
        if r['switch'] is not None and (r['address'], r['size'], r['flow']['extent'], r['flow']['table_size']) not in {
                ('0x0061E467', 397, 365, 32), ('0x0061E5F4', 422, 390, 32)}:
            raise ValueError('SDK dispatch truncates or mislabels an actual C switch')


def allows_transition(address, original_function, original_origin, function, origin):
    """Only four historical pending snapshots may advance through immutable R192 evidence."""
    if address not in {'0x0061AF34', '0x0061CA33', '0x00620C9A', '0x00643FC6'}:
        return False
    blob = (ROOT/EVIDENCE).read_bytes()
    if digest(blob) != MANIFEST_SHA256:
        raise ValueError('SDK dispatch transition evidence differs')
    m = json.loads(blob); verify_plan(m)
    row = next(r for r in m['functions'] if r['address'] == address)
    return (original_function == row['original_function'] and original_origin == row['original_origin']
            and function == row['accepted_function'] and origin == row['accepted_origin'])


def bind(raw, fields, bindings, catalog, owner, address, data_image=False):
    v = module('dispatch_bind', 'verify-sdk-x3d-origins.py')
    linked = bytearray(raw); occupied = set(); calls = {}; data = {}
    if len(fields) != len(bindings):
        raise ValueError('SDK dispatch omitted a genuine field')
    for f, b in zip(fields, bindings):
        at = f['offset']; key = v.field_key(owner, f)
        if (any(i in occupied for i in range(at, at+4)) or at < (0 if data_image else 1)
                or at+4 > len(raw) or any(b[k] != value for k, value in f.items())
                or catalog.get(key) != int(b['source_base'], 16)):
            raise ValueError('SDK dispatch real field or source definition differs')
        dest = (catalog[key] + f['addend']) & 0xffffffff
        if dest != int(b['target_address'], 16):
            raise ValueError('SDK dispatch field uses a guessed destination/addend')
        if f['type'] == 'REL32' and not data_image and raw[at-1] in (0xe8, 0xe9):
            struct.pack_into('<I', linked, at, (dest-address-at-4)&0xffffffff); calls[address+at] = dest
        elif f['type'] == 'DIR32':
            struct.pack_into('<I', linked, at, dest); data[address+at] = dest
        else:
            raise ValueError('SDK dispatch unsupported actual field/opcode')
        occupied.update(range(at, at+4))
    return linked, calls, data


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true'); args = parser.parse_args()
    m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('SDK dispatch immutable evidence differs')
    for path, sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha:
            raise ValueError('SDK dispatch retained source/evidence differs: '+path)
    c = module('dispatch_coff', 'compare-coff-function.py'); coff = module('dispatch_data', 'coff_data.py')
    rt = module('dispatch_archive', 'verify-runtime-origins.py')
    cr = module('dispatch_code', 'sdk_code_carriers.py'); extra = module('dispatch_sections', 'sdk_x3d_carriers.py')
    cfg = module('dispatch_cfg', 'sdk_dispatch_carriers.py'); v = module('dispatch_prior', 'verify-sdk-x3d-origins.py')
    target = c.verified_target(); members = {}
    for kind, path in [('d3dx8', '.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib'), ('libcmt', '.tools/msvc710/Vc7/lib/libcmt.lib')]:
        archive = (ROOT/path).read_bytes()
        if digest(archive) != m['archive_sha256'][kind]:
            raise ValueError('SDK dispatch source archive identity differs')
        members[kind] = {o: (n, b) for o, n, b in rt.archive_members(archive)}
    if digest(target) != m['target_sha256']:
        raise ValueError('SDK dispatch target identity differs')
    def member(r):
        n, b = members[r.get('archive', 'd3dx8')][r['member_offset']]
        if n != r['member'] or digest(b) != r['member_sha256']:
            raise ValueError('SDK dispatch actual source owner differs')
        return b
    catalog = {r['symbol']: int(r['address'], 16) for r in m['controls']}
    # Retained manifests hold their complete dependency graphs; fresh source/body readback prevents stale anchors.
    for r in m['anchors']:
        prior = json.loads((ROOT/r['path']).read_text()); a = int(r['address'], 16)
        if 'controls' in prior:
            proof = next(x for x in prior['controls'] if x['symbol'] == r['symbol'])
            if any(proof[k] != r[k] for k in r if k != 'path'):
                raise ValueError('SDK dispatch prior whole source association differs')
            body = member(proof)
            if 'source' in proof:
                raw, fields, source = cr.code_carrier(body, proof['symbol'], c, coff)
            else:
                _, defs = coff.parse_symbols(body, c.coff_name)
                definition = next(d for d in defs if d['symbol'] == proof['symbol'] and d['section'] > 0)
                if definition['offset'] or definition['type'] != 32:
                    raise ValueError('SDK prior source entry is not a whole section')
                raw, fields, source = extra.section_carrier(body, definition['section'], c, coff)
                if len(raw) != proof['size']:
                    raise ValueError('SDK prior source carrier is incomplete')
            if digest(raw) != proof['source_sha256'] or any({k: f[k] for k in old} != old for f, old in zip(fields, proof['fields'])) or len(fields) != len(proof['fields']) or ('source' in proof and source != proof['source']):
                raise ValueError('SDK dispatch prior whole COMDAT differs')
        elif r['symbol'] == '__CIacos':
            proof = dict(prior['functions'][0], archive='libcmt')
            with tempfile.TemporaryDirectory(dir=ROOT/'.analysis') as directory:
                p = Path(directory)/'original.obj'; p.write_bytes(member(proof)); raw, fields = c.object_function(p, '__CIacos')
            if len(raw) != 203 or digest(raw) != proof['source_sha256'] or len(fields) != len(proof['relocation_bindings']):
                raise ValueError('SDK dispatch acos whole original AUX/field carrier differs')
        else:
            proof = next(x for x in prior['sections'] if int(x['address'], 16) == a)
            n, body = members['d3dx8'][776284]
            if digest(body) != prior['member']['member_sha256']:
                raise ValueError('SDK dispatch prior CPU source owner differs')
            raw, fields, source = extra.section_carrier(body, proof['source']['section'], c, coff)
            if digest(raw) != proof['source']['source_sha256'] or len(raw) != proof['source']['size']:
                raise ValueError('SDK dispatch prior CPU whole carrier differs')
        if digest(c.pe_bytes_at(target, a, len(raw))) != proof['body_sha256']:
            raise ValueError('SDK dispatch prior whole target carrier differs')
        catalog[r['symbol']] = a
    sections = {(r['member_offset'], r['source']['section']): r for r in m['data']}
    for r in m['data']:
        for d in r['source']['definitions']:
            if d['storage'] == 2 and d['type'] == 0:
                value = int(r['base'], 16)+d['offset']
                if d['symbol'] in catalog and catalog[d['symbol']] != value:
                    raise ValueError('SDK dispatch source global has conflicting owners')
                catalog[d['symbol']] = value
    observed = set()
    for r in [*m['controls'], *m['data']]:
        owner = r['member_offset']; address = int(r.get('address', r.get('base')), 16)
        for f, b in zip(r['fields'], r['bindings']):
            key = v.field_key(owner, f); base = int(b['source_base'], 16)
            if f['local_symbol_offset'] is not None:
                if (f['symbol_section'] != r['source']['section'] or f['symbol_type'] or base != address+f['symbol_offset']):
                    raise ValueError('SDK dispatch local switch uses a foreign definition')
            elif f['symbol_type'] == 32:
                if catalog.get(f['symbol']) != base:
                    raise ValueError('SDK dispatch callback/callee lacks a separately whole original owner')
                continue
            elif f['symbol_section'] == 0:
                if f['symbol'] not in ('?g_D3DXFastTable@@3UD3DXFASTTABLE@@A', '?g_D3DXFastTableC@@3UD3DXFASTTABLE@@A') or catalog.get(key) != base:
                    raise ValueError('SDK dispatch cross-member data loses actual source definition')
                observed.add((684528, 3)); continue
            else:
                section = sections.get((owner, f['symbol_section']))
                if (section is None or base != int(section['base'], 16)+f['symbol_offset']
                        or not 0 <= f['symbol_offset']+f['addend'] < section['size']):
                    raise ValueError('SDK dispatch data loses its whole original section')
                observed.add((owner, f['symbol_section']))
            if key in catalog and catalog[key] != base:
                raise ValueError('SDK dispatch scoped definition conflicts')
            catalog[key] = base
    if observed != set(sections):
        raise ValueError('SDK dispatch omits or invents a whole observed data section')
    table = sections[684528, 3]; table_base = int(table['base'], 16)
    slots = {table_base+f['offset']-232 for f in table['fields'] if f['offset'] >= 232}
    functions = {r['address']: r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; mode = 'original' if args.evidence_only else 'accepted'
    for r in [*m['data'], *m['controls']]:
        is_data = 'base' in r; a = int(r['base'] if is_data else r['address'], 16); body = member(r)
        if is_data or r.get('symbol') in ('__finite', '?WithinEpsilon@@YAHMM@Z'):
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
        else:
            raw, fields, source = cr.code_carrier(body, r['symbol'], c, coff)
        if source != r['source'] or fields != r['fields'] or len(raw) != r['size'] or digest(raw) != r['source_sha256']:
            raise ValueError('SDK dispatch whole source/AUX/definitions/fields differ')
        if v.image_permissions(target, a, len(raw)) != source['flags']&0xe0000000:
            raise ValueError('SDK dispatch complete source/PE permissions differ')
        linked, calls, data = bind(raw, fields, r['bindings'], catalog, r['member_offset'], a, is_data)
        if linked != c.pe_bytes_at(target, a, len(raw)) or digest(linked) != r['body_sha256']:
            raise ValueError('SDK dispatch entire unmasked linked carrier differs')
        if is_data:
            if source['flags']&0x20 or not source['flags']&0x40:
                raise ValueError('SDK dispatch data is not an original initialized image')
            continue
        roots = [0] if r['symbol'] in ('__finite', '?WithinEpsilon@@YAHMM@Z') else [d['offset'] for d in source['peers']]
        if cfg.flow(linked, a, roots, fields, calls, data, r['switch'], slots) != r['flow']:
            raise ValueError('SDK dispatch whole CFG/table/tail/runtime slot differs')
        snap = selected.get(r['address']); expected_function = snap[mode+'_function'] if snap else r['function']
        expected_origin = snap[mode+'_origin'] if snap else r['origin']
        if functions.get(r['address']) != expected_function or origins.get(r['address']) != expected_origin:
            raise ValueError('SDK dispatch selected/prior/noninventory snapshot differs')
        if any(a < int(k, 16) < a+r['flow']['extent'] for k in functions):
            raise ValueError('SDK dispatch source extent hides an inventoried entry')
    print('R192 origins OK:53 complete library functions /3468 bytes;129 whole original code carriers /14378 bytes /298 fields;complete460-byte mutable table /112 callback fields,57 independently owned C defaults;18 initialized data images /544 bytes;two full C switches /64 bytes;two actual finite callers and retained complete acos graph;runtime-selected slots preserved;no source/ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
