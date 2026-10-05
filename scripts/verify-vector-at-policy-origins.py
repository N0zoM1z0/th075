#!/usr/bin/env python3
"""Cold-replay complete original vector bounds and iterator source policies."""
import argparse
import csv
import copy
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    s = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    v = importlib.util.module_from_spec(s); s.loader.exec_module(v); return v


BASE = module('vector_at_binder', 'verify-sdk-presentation-origins.py')
digest = BASE.digest


def metadata_digest(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':')).encode())


def canonical_source(source, body):
    """Relativize validated COFF debug line pointers; retain every line record."""
    result = copy.deepcopy(source)
    h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + (source['section'] - 1) * 40)
    line_base, line_count = h[6], h[8]
    if line_count and (not line_base or line_base + line_count * 6 > len(body)):
        raise ValueError('Vector at truncated own COFF line table')
    result['coff_line_table'] = [list(struct.unpack_from('<IH', body, line_base + i * 6)) for i in range(line_count)]
    definitions = {d['symbol']: d for d in source['definitions']}
    for a in result['aux_records']:
        if definitions[a['symbol']]['type'] != 32 or a['aux_count'] != 1: continue
        raw = bytearray.fromhex(a['aux_hex']); pointer = struct.unpack_from('<I', raw, 8)[0]
        if not pointer: continue
        relative = pointer - line_base
        if (relative < 0 or relative % 6 or relative >= line_count * 6
                or struct.unpack_from('<IH', body, pointer) != (a['index'], 0)):
            raise ValueError('Vector at function AUX does not own its actual COFF line entry')
        struct.pack_into('<I', raw, 8, relative)
        a['aux_hex'] = raw.hex(); a['line_pointer_basis'] = 'own-section-coff-line-table-offset'
    return result


def verify_plan(m):
    if m['evidence_id'] != 'R205' or {r['address']: r['size'] for r in m['functions']} != KEYS:
        raise ValueError('Vector at loses bounded complete source policy cohort')
    for key, sha in PLAN_DIGESTS.items():
        if metadata_digest(m[key]) != sha:
            raise ValueError('Vector at frozen complete provenance differs: ' + key)
    if (len(m['sections']) != 52 or sum(r['size'] for r in m['sections']) != 1961
            or sum(len(r['fields']) for r in m['sections']) != 92
            or sum(r['kind'] == 'code' for r in m['sections']) != 44
            or len(m['shared']) != 6 or len(m['crt_anchors']) != 2 or m['interiors']
            or len(m['groups']) != 4 or [g['stride'] for g in m['groups']] != [4, 116, 4, 16]
            or len(m['parents']) != 4 or len(m['rejected_stride_alternatives']) != 4 or len(m['const_routes']) != 4):
        raise ValueError('Vector at omits complete group/field/exception/alternative context')
    for r in m['functions']:
        old = r['original_function']; q = next(q for q in m['sections'] if q['group'] == r['group'] and q['base'] == r['address'])
        if (q['function'] != old or q['origin'] != r['original_origin'] or q['symbol'] != r['symbol']
                or r['original_origin']['origin'] != 'unknown' or old['status'] != 'unclassified'
                or old['match_percent'] != '0.00' or int(old['size']) != r['size']
                or any(old[k] for k in ['source_file', 'owner', 'signature', 'calling_convention'])
                or r['accepted_function'] != dict(old, proposed_name=NAMES[r['symbol'].split('@')[0]] + ' [element type unknown]',
                    module='VC71STL', status='excluded', owner='library', evidence='R205', notes=r['notes'])
                or not r['accepted_function']['proposed_name'].endswith(' [element type unknown]')
                or r['accepted_origin'] != dict(address=r['address'], origin='library', subsystem='VC71STL',
                    disposition='exclude', confidence=CONFIDENCE, evidence_id='R205')):
            raise ValueError('Vector at changes extent or gives private type/source/ABI/mapping/exact credit')


def retained_catalog(m):
    """Derive retained owners from their source records, never recorded field values."""
    catalog = {}
    for r in m['code']: catalog[r['symbol']] = int(r['address'], 16)
    for r in m['state_data']:
        for d in r['source_section']['definitions']: catalog[d['symbol']] = int(r['address'], 16) + d['offset']
    for r in m['code_carriers']:
        for d in r['source_definitions']: catalog[d['symbol']] = int(r['address'], 16) + d['offset']
    for r in m['external']: catalog[r['symbol']] = int(r['address'], 16)
    for alias, fallback in m['weak'].items(): catalog[alias] = catalog[fallback]
    if any(m['symbol_addresses'].get(sn) != f'0x{a:08X}' for sn, a in catalog.items()):
        raise ValueError('Vector at retained symbolic observations override original owners')
    return catalog


def replay(m, evidence_only=False):
    c = module('at_coff', 'compare-coff-function.py'); coff = module('at_data', 'coff_data.py')
    extra = module('at_carriers', 'sdk_x3d_carriers.py'); flow = module('at_flow', 'sdk_image_carriers.py')
    rt = module('at_archive', 'verify-runtime-origins.py'); link = module('at_prior_link', 'verify-nested-deque-size-origins.py')
    pe = module('at_permissions', 'verify-sdk-x3d-origins.py'); api = module('at_headers', 'verify-sdk-interface-origins.py')
    inventory = module('at_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target(); functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    if digest(target) != m['target_sha256']: raise ValueError('Vector at target identity differs')
    crt = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(crt) != m['crt_archive_sha256']: raise ValueError('Vector at CRT archive differs')
    members = {o: (n, b) for o, n, b in rt.archive_members(crt)}
    absolute = m['absolute']['__except_list']; name, body = members[absolute['member_offset']]
    if (name != absolute['member'] or digest(body) != absolute['member_sha256']
            or [d for d in coff.parse_symbols(body, c.coff_name)[1] if d['symbol'] == '__except_list' and d['section'] != 0]
            != [absolute['definition']] or absolute['definition']['section'] != -1 or absolute['definition']['offset']):
        raise ValueError('Vector at invents an owner for the absolute CRT symbol')
    prior = json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())
    prior_catalog = retained_catalog(prior)
    scratch = ROOT / 'build/origin-vector-at-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'VectorAt.obj'
        for a in m['crt_anchors']:
            q = a['record']; n, body = members[q['member_offset']]
            if (not BASE.contains(json.loads((ROOT / a['path']).read_text()), q) or n != q['member']
                    or digest(body) != q['member_sha256'] or functions[q['address']] != a['function'] or origins[q['address']] != a['origin']):
                raise ValueError('Vector at changes retained original CRT ownership')
            obj.write_bytes(body); raw, fields = c.object_function(obj, q['coff_symbol'], None)
            if len(raw) != q['size'] or digest(raw) != q['source_sha256']:
                raise ValueError('Vector at crops the original CRT own-AUX function')
            recorded = q['relocation_bindings']; catalog = {f['symbol']: int(f['target_address'], 16) for f in recorded}
            # Immutable R142 independently owns these typed state/import/code entries;
            # reopening the whole original source retains every original field.
            if (link.link_complete(raw, fields, int(q['address'], 16), recorded, catalog)
                    != c.pe_bytes_at(target, int(q['address'], 16), q['size'])):
                raise ValueError('Vector at whole retained CRT source differs')
        control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode: raise ValueError('Vector at cold public template build failed')
        body = obj.read_bytes()
        if api.included_headers(result.stdout + result.stderr) != control['headers'] or inventory(body, c, coff) != control['emission']:
            raise ValueError('Vector at loses actual headers or complete ordinary emission')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 36 or list(struct.unpack('<9I', layout)) != control['layout']['values']:
            raise ValueError('Vector at full generic observation differs')
        shared_catalog = {'__except_list': 0}
        for a in m['shared']:
            q = a['record']; sn = q['symbol']; address = int(q['address'], 16)
            if not BASE.contains(prior, q): raise ValueError('Vector at changes retained source record')
            shared_catalog[sn] = address
            if 'function' in a and (functions[q['address']] != a['function'] or origins[q['address']] != a['origin']):
                raise ValueError('Vector at changes retained canonical owner')
            if 'cold_source' not in a: continue
            raw, fields, source = extra.section_carrier(body, a['cold_source']['section'], c, coff)
            source = canonical_source(source, body)
            if source != a['cold_source'] or fields != a['cold_fields'] or len(raw) != q['size'] or digest(raw) != q['source_sha256']:
                raise ValueError('Vector at retained whole cold owner differs: ' + sn + ' ' + repr((
                    source == a['cold_source'], fields == a['cold_fields'], len(raw), q['size'], digest(raw) == q['source_sha256'])))
            if (link.link_complete(raw, fields, address, q['relocations'], prior_catalog) != c.pe_bytes_at(target, address, len(raw))
                    or digest(c.pe_bytes_at(target, address, len(raw))) != q['body_sha256']):
                raise ValueError('Vector at full retained unmasked code/data differs')
        for g in m['groups']:
            rows = [r for r in m['sections'] if r['group'] == g['id']]; catalog = dict(shared_catalog); owners = {}; decoded = {}
            for r in rows:
                raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
                source = canonical_source(source, body)
                if (source != r['source'] or fields != r['fields'] or digest(raw) != r['source_sha256'] or len(raw) != r['size']
                        or pe.image_permissions(target, int(r['base'], 16), len(raw)) != source['flags'] & 0xe0000000):
                    raise ValueError('Vector at whole source/AUX/fields differ')
                a = int(r['base'], 16); owners[source['section']] = a; decoded[source['section']] = (raw, fields)
                for d in source['definitions']:
                    if d['storage'] == 2: catalog[d['symbol']] = a + d['offset']
                if r['kind'] == 'code':
                    q = selected.get(r['base']); f = q[state + '_function'] if q else r['function']; o = q[state + '_origin'] if q else r['origin']
                    if functions.get(r['base']) != f or origins.get(r['base']) != o:
                        raise ValueError('Vector at canonical selected/retained snapshot differs')
                    if any(a < int(k, 16) < a + r['size'] for k in functions):
                        raise ValueError('Vector at full source extent hides an inventory entry')
            for r in rows:
                for f in r['fields']:
                    if f['symbol_storage'] == 3 and f['symbol_section'] > 0:
                        own = owners.get(f['symbol_section'])
                        if own is None: raise ValueError('Vector at local field has no whole scoped source owner')
                        catalog[(g['id'], f['symbol_section'], f['symbol_index'])] = own + f['symbol_offset']
            for r in rows:
                raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
                linked, calls, data = BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a, data_image=r['kind'] == 'data')
                actual = c.pe_bytes_at(target, a, len(raw))
                if linked != actual or digest(actual) != r['body_sha256']:
                    raise ValueError('Vector at entire unmasked source/native body differs')
                if r['kind'] == 'code' and flow.flow(linked, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                    raise ValueError('Vector at complete normal/EH CFG differs')
        for r in m['rejected_stride_alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            source = canonical_source(source, body)
            actual = c.pe_bytes_at(target, int(r['address'], 16), r['target_size'])
            if (source != r['source'] or fields != r['fields'] or fields or len(raw) != r['size']
                    or digest(raw) != r['source_sha256'] or digest(actual) != r['target_sha256'] or raw == actual):
                raise ValueError('Vector at complete wrong-stride alternative is not independently rejected')
        for r in m['const_routes']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            d = r['dereference']; dr, df, ds = extra.section_carrier(body, d['source']['section'], c, coff)
            source = canonical_source(source, body); ds = canonical_source(ds, body)
            if (source != r['source'] or fields != r['fields'] or len(raw) != 70 or digest(raw) != r['source_sha256']
                    or ds != d['source'] or df != d['fields'] or df or len(dr) != 16 or digest(dr) != d['source_sha256']):
                raise ValueError('Vector at whole const-route negative evidence differs')
    authored = module('at_authored', 'verify-authored-origins.py')
    for p in m['parents']:
        f = p['function']; a = int(f['address'], 16); raw = c.pe_bytes_at(target, a, int(f['size'])); site = int(p['call_site'], 16)
        switches = [r for r in csv.DictReader((ROOT / 'config/authored-origin-switches.csv').open()) if r['address'] == f['address']]
        direct = [r for r in csv.DictReader((ROOT / 'config/authored-origin-direct-switches.csv').open()) if r['address'] == f['address']]
        if (functions[f['address']] != f or origins[f['address']] != p['origin'] or p['origin']['origin'] != 'authored'
                or digest(raw) != p['body_sha256'] or list(authored.verify_body(raw, a, switches, lambda x, n: c.pe_bytes_at(target, x, n), direct)) != p['cfg']
                or raw[site - a] != 0xe8 or site + 5 + struct.unpack_from('<i', raw, site - a + 1)[0] != int(p['destination'], 16)):
            raise ValueError('Vector at independent whole game parent/call differs')


def main():
    p = argparse.ArgumentParser(description=__doc__); p.add_argument('--evidence-only', action='store_true'); args = p.parse_args()
    m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']), *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('Vector at immutable source/evidence differs: ' + path)
    replay(m, args.evidence_only)
    print('R205 origins OK:18 whole original public vector/iterator library policies615; '
          'four group-scoped source graphs52 sections1961/all92 fields,44 complete normal/EH CFGs; '
          'real _Xran/out_of_range owners, two original CRT helpers and absolute definition; '
          'four complete wrong-stride and four const-route alternatives; full game parents; '
          '130 cold ordinary sections5548,27 actual headers and whole generic observation36; '
          'element types/private owners remain unknown; no reconstructed source/ABI/mapping/exact credit.')
    return 0


EVIDENCE = 'config/vector-at-policy-origin-evidence.json'
MANIFEST_SHA256 = '50d18e8f574de56e427454e9eaaabfd257d0567a4fa9d5c68a463150a4bf635c'
CONFIDENCE = 'complete-original-vc7-vector-bounds-and-iterator-source-scoped-policy-graph-with-exception-and-game-context'
NAMES = {'?at': 'std::vector::at', '?begin': 'std::vector::begin', '??Diterator': 'std::vector::iterator::operator*',
         '??Dconst_iterator': 'std::vector::const_iterator::operator*', '??Hiterator': 'std::vector::iterator::operator+',
         '??Yiterator': 'std::vector::iterator::operator+=', '??0iterator': 'std::vector::iterator::iterator'}
KEYS = {'0x004093E0': 70, '0x00409D80': 19, '0x0040A160': 16, '0x00442060': 70, '0x004420B0': 70, '0x00442100': 31, '0x004421C0': 31, '0x00442280': 19, '0x004422A0': 45, '0x004422D0': 19, '0x00442320': 28, '0x00442340': 32, '0x00442360': 16, '0x00442370': 28, '0x004423B0': 16, '0x00445310': 70, '0x00445600': 19, '0x004456C0': 16}
PLAN_DIGESTS = {'groups': '8b013075eca124597b4bfd1ebf50ca2eebab33dc368ceb78c74bee0117af3330', 'sections': 'b8e1a094d3ec46a515cbb8cf20122f0974d9a3d42b25abfdc064704991cd6154', 'shared': 'a67c2d5625c550ed166cd4287d6e58c23b36481295ce5b8e81bcedb21a486f71', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'parents': '5ca44df10d00a851d09589206c2de3a90a1316fa75fdc30aa4f8e7a220a04263', 'public_control': '9e4fa172ef9fed9653029d6492cd3dc08181905c1f7cbabb0c702e8d5bf1ba70', 'interiors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'crt_anchors': 'f0615d80d7a89760c0779bb36e191827504b40e5626e291140abf3117609fdf6', 'rejected_stride_alternatives': '84225171f7109f8a239f5f6e121104a6b423a4d2afb061d20859d03c4def0f48', 'const_routes': '3843225b24aeb4d30c7a4dcec4eeb2abf4dbb5cd1872e07230c8c5e9f8f43947', 'retained_sha256': 'd6adf87c68f4f6203286a37b90dc7158fb750df322db5b7f818f32cb9196fa20'}

if __name__ == '__main__': raise SystemExit(main())
