#!/usr/bin/env python3
"""Reopen complete SDK x86 dispatch/math and Direct3D registry source policies."""
from __future__ import annotations
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-x86-policy-origin-evidence.json'
MANIFEST_SHA256 = 'dfba474686f4032271ad6ba4f2f9fde62ed221590e40c13f354bf7086e2872f1'
KEYS = {'0x006292BC': 60, '0x006209EF': 92, '0x00629081': 202}
CONTROL_KEYS = {**KEYS, '0x00628E1B': 105, '0x00628EB9': 139,
                '0x00628FA3': 153, '0x0062914B': 227, '0x0062922E': 142,
                '0x00628E84': 53, '0x00628F44': 95}
CONFIDENCE = 'whole-pinned-sdk-explicit-x86-dispatch-math-and-registry-policy-with-complete-data-imports'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def digest(data):
    return hashlib.sha256(data).hexdigest()


def verify_plan(m):
    if (m['evidence_id'] != 'R188' or len(m['functions']) != 3
            or {r['address']: r['size'] for r in m['functions']} != KEYS
            or len(m['controls']) != 10 or {r['address']: r['size'] for r in m['controls']} != CONTROL_KEYS
            or sum(len(r['fields']) for r in m['controls']) != 14
            or len(m['data']) != 2 or [r['size'] for r in m['data']] != [4104, 28]
            or [r['writable'] for r in m['data']] != [True, False]
            or len(m['imports']) != 3
            or {(r['dll'].upper(), r['name']) for r in m['imports']} !=
               {('ADVAPI32.DLL', n) for n in ('RegOpenKeyA', 'RegQueryValueExA', 'RegCloseKey')}
            or {r['address']: r['size'] for r in m['pending']} != {'0x0061AF34': 6, '0x0061CA33': 328}
            or m['cpu_context']['address'] != '0x00620C9A' or m['cpu_context']['size'] != 221):
        raise ValueError('SDK x86 policy loses complete source/data/import or pending scope')
    mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
    by = {r['address']: r for r in m['controls']}
    for r in m['functions']:
        a = r['address']; old, new = r['original_function'], r['accepted_function']
        if (by[a]['function'] != old or by[a]['origin'] != r['original_origin']
                or r['original_origin']['origin'] != 'unknown'
                or {k: v for k, v in old.items() if k not in mutable} != {k: v for k, v in new.items() if k not in mutable}
                or int(old['size']) != r['size'] or int(old['span_end'], 16) != int(a, 16) + r['size'] - 1
                or new['status'] != 'excluded' or new['owner'] != 'library' or new['module'] != 'D3DX8'
                or new['proposed_name'] != by[a]['symbol'] or new['evidence'] != 'R188'
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent'] != '0.00'
                or r['accepted_origin'] != dict(address=a, origin='library', subsystem='D3DX8', disposition='exclude', confidence=CONFIDENCE, evidence_id='R188')):
            raise ValueError('SDK x86 origin alters extent or grants source/ABI/mapping/exact credit')
    carrier = m['carrier']
    if (carrier['size'] != 460 or len(carrier['fields']) != 112 or carrier['base'] != '0x0066D070'
            or carrier['comparison'] != 'full-original-pointer-context-only-no-unrelated-callee-acceptance'
            or 'bindings' in carrier or 'target_positive' in carrier):
        raise ValueError('SDK full original carrier becomes truncated or falsely accepted linkage')
    for r in [m['cpu_context'], *m['pending']]:
        if ('bindings' in r or 'target_positive' in r or r['origin']['origin'] != 'unknown'
                or 'context-only' not in r['comparison']):
            raise ValueError('SDK unresolved runtime scope gains a false body/origin claim')
    normalizer = by['0x00629081']
    if ([(f['type'], f['symbol'], f['addend']) for f in normalizer['fields']] !=
            [('DIR32', '_invSqrtTab', 0), ('DIR32', '_invSqrtTab', 4)]
            or [b['target_address'] for b in normalizer['bindings']] != ['0x0066D2A0', '0x0066D2A4']):
        raise ValueError('SDK normalizer loses genuine indexed table field/addend')
    initializer = by['0x006292BC']
    implementations = {r['symbol']: r['address'] for r in m['controls'] if r['member_offset'] == 767378 and r['address'] != '0x006292BC'}
    if (len(initializer['fields']) != 8 or len(implementations) != 8
            or [f['offset'] for f in initializer['fields']] != [6, 13, 20, 27, 34, 41, 48, 55]
            or any(f['type'] != 'DIR32' or f['addend'] or f['local_symbol_offset'] is not None for f in initializer['fields'])
            or {b['symbol']: b['target_address'] for b in initializer['bindings']} != implementations):
        raise ValueError('SDK initializer loses complete independent pointer implementations')


def source_data(body, section, c, coff):
    count, definitions = coff.parse_symbols(body, c.coff_name)
    if not 1 <= section <= count:
        raise ValueError('SDK policy data section number differs')
    h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + (section - 1) * 40)
    if (not h[3] or not h[4] or h[4] + h[3] > len(body) or h[7] or h[9] & 0x20
            or not h[9] & 0x40 or not h[9] & 0x40000000):
        raise ValueError('SDK policy requires an entire initialized non-code data section')
    return body[h[4]:h[4]+h[3]], h[9], [d for d in definitions if d['section'] == section and not d['symbol'].startswith('.')]


def link_fields(raw, fields, bindings, catalogue, address):
    if len(fields) != len(bindings):
        raise ValueError('SDK policy drops real source fields')
    linked = bytearray(raw); data = {}; used = set()
    for f, b in zip(fields, bindings):
        at = f['offset']; sn = f['symbol']; dest = int(b['target_address'], 16)
        if (at in used or at < 1 or at + 4 > len(raw) or f['type'] != 'DIR32' or f['type_id'] != 6
                or f['local_symbol_offset'] is not None or {k: b[k] for k in f} != f
                or f['addend'] not in (0, 4) or (f['addend'] and sn != '_invSqrtTab')
                or catalogue.get(sn) != dest - f['addend'] or int(b['source_base'], 16) != dest - f['addend']
                or struct.unpack_from('<I', raw, at)[0] != f['addend']):
            raise ValueError('SDK policy masks/renames or overrides an actual field/addend')
        used.add(at); struct.pack_into('<I', linked, at, dest); data[address + at] = dest
    return linked, data


def main():
    parser = argparse.ArgumentParser(); parser.add_argument('--evidence-only', action='store_true'); args = parser.parse_args()
    m = json.loads((ROOT / EVIDENCE).read_text())
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('SDK x86 immutable manifest differs')
    verify_plan(m)
    for path, expected in m['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != expected:
            raise ValueError('SDK x86 changes earlier source/evidence input: ' + path)
    c = module('x86_policy_coff', 'compare-coff-function.py'); rt = module('x86_policy_runtime', 'verify-runtime-origins.py')
    coff = module('x86_policy_data', 'coff_data.py'); sdk = module('x86_policy_sdk', 'verify-sdk-origins.py')
    target = c.verified_target(); archive = (ROOT / '.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(target) != m['target_sha256'] or digest(archive) != m['archive_sha256']:
        raise ValueError('SDK x86 target/archive identity differs')
    members = {off: (name, body) for off, name, body in rt.archive_members(archive)}
    def member(r):
        name, body = members[r['member_offset']]
        if name != r['member'] or digest(body) != r['member_sha256']:
            raise ValueError('SDK x86 actual source member differs')
        return body
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}
    for a, r in selected.items():
        mode = 'original' if args.evidence_only else 'accepted'
        if functions[a] != r[mode + '_function'] or origins[a] != r[mode + '_origin']:
            raise ValueError('SDK x86 bounded ledger snapshot differs')
    catalogue = {r['symbol']: int(r['address'], 16) for r in m['controls']}
    for r in m['data']:
        raw, flags, definitions = source_data(member(r), r['section'], c, coff)
        native = c.pe_bytes_at(target, int(r['base'], 16), len(raw))
        if (len(raw) != r['size'] or flags != r['flags'] or definitions != r['definitions']
                or bool(flags & 0x80000000) != r['writable'] or digest(raw) != r['source_sha256']
                or digest(native) != r['body_sha256'] or raw != native):
            raise ValueError('SDK x86 whole data image/definitions/permissions differ')
        catalogue.update({d['symbol']: int(r['base'], 16) + d['offset'] for d in definitions})
    imports = module('x86_policy_imports', 'verify-import-origins.py').pe_imports(target, c)
    for r in m['imports']:
        if imports.get(int(r['address'], 16)) != (r['dll'], r['name']) or r['symbol'].split('@')[0] != '__imp__' + r['name']:
            raise ValueError('SDK registry field lacks the actual imported API identity')
        catalogue[r['symbol']] = int(r['address'], 16)
    old_sdk = {r['address']: r for r in csv.DictReader((ROOT / 'config/sdk-origin-evidence.csv').open())}
    with tempfile.TemporaryDirectory(dir=ROOT / '.analysis') as directory:
        obj = Path(directory) / 'vendor.obj'
        for r in m['controls']:
            a = r['address']; body = member(r); obj.write_bytes(body)
            size = sdk.complete_comdat_size(body, r['symbol'], c.coff_name)
            raw, fields = c.object_function(obj, r['symbol'], size)
            if size != r['size'] or digest(raw) != r['source_sha256'] or fields != r['fields']:
                raise ValueError('SDK policy loses its entire original COMDAT or real fields')
            if a not in selected and (functions.get(a) != r['function'] or origins.get(a) != r['origin']):
                raise ValueError('SDK x86 context changes an unrelated or non-inventory row')
            if r['old_sdk_record'] is not None and old_sdk.get(a) != r['old_sdk_record']:
                raise ValueError('SDK x86 modifies previous complete implementation evidence')
            linked, data = link_fields(raw, fields, r['bindings'], catalogue, int(a, 16))
            native = c.pe_bytes_at(target, int(a, 16), size)
            if (linked != native or digest(native) != r['body_sha256']
                    or sdk.verify_control_flow(linked, int(a, 16), {}, data) != r['indirect_call_count']):
                raise ValueError('SDK whole linked policy or complete branches/exits differ')
        # The larger initial carrier is retained as observed context. Its other
        # pointer destinations do not receive independent source linkage claims.
        r = m['carrier']; body = member(r)
        count, defs = coff.parse_symbols(body, c.coff_name)
        h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + (r['section'] - 1) * 40)
        raw = body[h[4]:h[4]+h[3]]
        if (len(raw) != r['size'] or h[9] != r['flags'] or h[7] != 112
                or [d for d in defs if d['section'] == r['section'] and not d['symbol'].startswith('.')] != r['definitions']
                or digest(raw) != r['source_sha256'] or digest(c.pe_bytes_at(target, int(r['base'], 16), len(raw))) != r['body_sha256']):
            raise ValueError('SDK full original runtime carrier context differs')
        syoff, count = struct.unpack_from('<II', body, 8); strings = body[syoff+count*18:]; names = {}; i = 0
        while i < count:
            nm, _, _, _, _, aux = struct.unpack_from('<8sIhHBB', body, syoff+i*18); names[i] = c.coff_name(nm, strings); i += 1+aux
        native = c.pe_bytes_at(target, int(r['base'], 16), len(raw)); occupied = set()
        for i, f in enumerate(r['fields']):
            at, si, typ = struct.unpack_from('<IIH', body, h[5]+10*i)
            if (at in occupied or typ != 6 or at != f['offset'] or names[si] != f['symbol']
                    or struct.unpack_from('<I', raw, at)[0] or struct.unpack_from('<I', native, at)[0] != int(f['address'], 16)):
                raise ValueError('SDK original context pointer field differs')
            occupied.update(range(at, at+4))
        if any(raw[i] != native[i] for i in range(len(raw)) if i not in occupied):
            raise ValueError('SDK original full carrier non-pointer bytes differ')
        for r in [m['cpu_context'], *m['pending']]:
            body = member(r); obj.write_bytes(body); size = sdk.complete_comdat_size(body, r['symbol'], c.coff_name)
            raw, fields = c.object_function(obj, r['symbol'], size)
            if (size != r['size'] or fields != r['fields'] or digest(raw) != r['source_sha256']
                    or digest(c.pe_bytes_at(target, int(r['address'], 16), size)) != r['body_sha256']
                    or ((functions[r['address']] != r['function'] or origins[r['address']] != r['origin'])
                        and not module('x86_dispatch_transition', 'verify-sdk-dispatch-origins.py').allows_transition(
                            r['address'], r['function'], r['origin'], functions[r['address']], origins[r['address']]))):
                raise ValueError('SDK unresolved full context/fields/snapshot differs')
    print('R188 origins OK: three complete explicit SDK dependencies /354 bytes; ten whole source bodies /1268 bytes with all14 real fields; eight independent x86 pointer implementations; full writable 4104-byte source data image and readonly registry path /28 bytes; three actual registry APIs; whole 460-byte /112-pointer carrier, historical CPU/public context retained with only immutable R192 snapshot transitions; prior evidence/ownership preserved; no source/ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print('error: ' + str(exc), file=sys.stderr)
        raise SystemExit(1)
