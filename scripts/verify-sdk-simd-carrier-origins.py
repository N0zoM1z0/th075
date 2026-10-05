#!/usr/bin/env python3
"""Reopen complete SIMD SDK source carriers, data allocations and function CFG."""
from __future__ import annotations
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-simd-carrier-origin-evidence.json'
MANIFEST_SHA256 = '6edf1ccbd7727169fe70054fb036f5bb3d36cc3b44cc77ce036e417425fd7ec1'
KEYS = {'0x00628900': 262, '0x00628A10': 266, '0x00630A90': 89,
        '0x0063C1C0': 492, '0x0063C990': 329, '0x0063C8A0': 232}
CONFIDENCE = 'whole-pinned-sdk-simd-carriers-with-reachable-cfg-alignment-and-complete-data-provenance'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(data):
    return hashlib.sha256(data).hexdigest()


def field_key(member_offset, field):
    if field['symbol_section'] > 0 and field['symbol_type'] != 32 and field['symbol_storage'] == 3:
        return member_offset, field['symbol_section'], field['symbol_index']
    return field['symbol']


def verify_plan(m):
    if (m['evidence_id'] != 'R189' or len(m['functions']) != 6
            or {r['address']: r['size'] for r in m['functions']} != KEYS
            or len(m['controls']) != 56 or len({r['symbol'] for r in m['controls']}) != 56
            or sum(r['size'] for r in m['controls']) != 12960
            or sum(r['flow']['extent'] for r in m['controls']) != 12463
            or sum(r['flow']['alignment_size'] for r in m['controls']) != 497
            or sum(len(r['fields']) for r in m['controls']) != 264 or len(m['data']) != 16):
        raise ValueError('SIMD SDK loses complete carrier/field/extent/data scope')
    by = {r['address']: r for r in m['controls']}; mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
    for r in m['functions']:
        a = r['address']; old, new = r['original_function'], r['accepted_function']
        if (by[a]['function'] != old or by[a]['origin'] != r['original_origin'] or r['original_origin']['origin'] != 'unknown'
                or {k: v for k, v in old.items() if k not in mutable} != {k: v for k, v in new.items() if k not in mutable}
                or int(old['size']) != r['size'] or int(old['span_end'], 16) != int(a, 16) + r['size'] - 1
                or by[a]['flow']['extent'] != r['size'] or new['proposed_name'] != by[a]['symbol']
                or new['module'] != 'D3DX8' or new['owner'] != 'library' or new['status'] != 'excluded' or new['evidence'] != 'R189'
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent'] != '0.00'
                or r['accepted_origin'] != dict(address=a, origin='library', subsystem='D3DX8', disposition='exclude', confidence=CONFIDENCE, evidence_id='R189')):
            raise ValueError('SIMD origin modifies extent or grants source/ABI/mapping/exact credit')
    for a, count, padding in [('0x00628900', 33, 10), ('0x00628A10', 34, 6)]:
        r = by[a]
        if (r['size'] != 272 or len(r['fields']) != count or r['flow']['alignment_size'] != padding
                or any(f['type'] != 'DIR32' or f['addend'] or f['symbol_type'] != 32 for f in r['fields'])
                or len(r['bindings']) != count):
            raise ValueError('SIMD initializer truncates its real carrier or callback set')
    initialized = [r for r in m['data'] if r['kind'] == 'source-initialized-section']
    common = [r for r in m['data'] if r['kind'] == 'source-common-zero-fill']
    zero = [r for r in m['data'] if r['kind'] == 'source-zero-fill-section']
    if (len(initialized) != 9 or sum(r['size'] for r in initialized) != 2816
            or any(not r['flags'] & 0x80000000 for r in initialized)
            or len(common) != 6 or {(r['base'], r['size']) for r in common} !=
                {('0x0068E7F0', 4), ('0x0068E7D0', 16), ('0x0068E7E0', 16)}
            or any(r['declaration']['section'] or r['declaration']['type'] or r['declaration']['storage'] != 2
                   or r['declaration']['offset'] != r['size'] for r in common)
            or len(zero) != 1 or zero[0]['size'] != 32 or zero[0]['base'] != '0x0068E2A0'):
        raise ValueError('SIMD source data loses initialized/common/zero-fill distinction')
    for r in m['controls']:
        if r['size'] != r['source']['size'] or r['size'] != r['flow']['extent'] + r['flow']['alignment_size']:
            raise ValueError('SIMD whole source carrier is cut to native function/padding')
        if r['flow']['roots'] != sorted(int(r['address'], 16)+p['offset'] for p in r['source']['peers']):
            raise ValueError('SIMD source secondary entry is hidden from complete CFG')


def bind_fields(raw, fields, bindings, catalogue, member_offset, address):
    if len(fields) != len(bindings):
        raise ValueError('SIMD field coverage differs')
    linked = bytearray(raw); calls = {}; data = {}; occupied = set()
    for f, b in zip(fields, bindings):
        at = f['offset']; dest = int(b['target_address'], 16); base = dest-f['addend']
        if (at < 1 or at+4 > len(raw) or any(i in occupied for i in range(at, at+4))
                or f['local_symbol_offset'] is not None or {k: b[k] for k in f} != f
                or catalogue.get(field_key(member_offset, f)) != base or int(b['source_base'], 16) != base
                or struct.unpack_from('<I', raw, at)[0] != f['addend']):
            raise ValueError('SIMD field drops source scope/definition/addend or overlaps another field')
        occupied.update(range(at, at+4))
        if f['type'] == 'REL32' and f['type_id'] == 20 and not f['addend'] and raw[at-1] == 0xe8:
            struct.pack_into('<I', linked, at, (dest-address-at-4)&0xffffffff); calls[address+at] = dest
        elif f['type'] == 'DIR32' and f['type_id'] == 6:
            struct.pack_into('<I', linked, at, dest); data[address+at] = dest
        else:
            raise ValueError('SIMD unsupported real field kind or external tail')
    return linked, calls, data


def main():
    p = argparse.ArgumentParser(); p.add_argument('--evidence-only', action='store_true'); args = p.parse_args()
    m = json.loads((ROOT/EVIDENCE).read_text())
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('SIMD SDK immutable manifest differs')
    verify_plan(m)
    for path, sha in m['retained_sha256'].items():
        actual = digest((ROOT/path).read_bytes())
        if actual != sha:
            # The old source hash remains immutable; only its exact R192 transition gate may replace it.
            transition = module('simd_dispatch_transition', 'verify-sdk-dispatch-origins.py')
            if (path != 'scripts/verify-sdk-x86-policy-origins.py'
                    or sha != '8a67df2c2e883cc9f18ed65295d86ae0fa8182427e363afbfef4c0c3dbed9561'
                    or actual != '7f6222b4d41f2dbde61eccf3ed7c3c07a3f54a33825633956342852b7056129e'
                    or digest((ROOT/transition.EVIDENCE).read_bytes()) != transition.MANIFEST_SHA256):
                raise ValueError('SIMD SDK changes a retained evidence/source input: '+path)
            transition.verify_plan(json.loads((ROOT/transition.EVIDENCE).read_text()))
    c = module('simd_coff', 'compare-coff-function.py'); rt = module('simd_runtime', 'verify-runtime-origins.py')
    coff = module('simd_data', 'coff_data.py'); sdk = module('simd_sdk', 'verify-sdk-origins.py')
    carrier = module('simd_carriers', 'sdk_code_carriers.py')
    target = c.verified_target(); archive = (ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(target) != m['target_sha256'] or digest(archive) != m['archive_sha256']:
        raise ValueError('SIMD SDK target/archive identity differs')
    members = {off: (name, body) for off, name, body in rt.archive_members(archive)}
    def member(r):
        name, body = members[r['member_offset']]
        if name != r['member'] or digest(body) != r['member_sha256']:
            raise ValueError('SIMD actual source member differs')
        return body
    selected = {r['address']: r for r in m['functions']}
    functions = {r['address']: r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    old_sdk = {r['address']: r for r in csv.DictReader((ROOT/'config/sdk-origin-evidence.csv').open())}
    catalogue = {r['symbol']: int(r['address'], 16) for r in m['controls']}
    data_sections = {}; commons = {}; observed = set()
    for r in m['data']:
        body = member(r); _, defs = coff.parse_symbols(body, c.coff_name)
        if r['kind'] == 'source-common-zero-fill':
            actual = [d for d in defs if d['symbol'] == r['symbol'] and d['section'] == 0]
            if actual != [r['declaration']] or actual[0]['offset'] != r['size']:
                raise ValueError('SIMD COMMON allocation loses its actual COFF declaration/size')
            if carrier.zero_region(target, int(r['base'], 16), r['size']) != r['pe_region']:
                raise ValueError('SIMD COMMON allocation is not entirely original PE zero-fill')
            sn = r['symbol']; value = int(r['base'], 16)
            if sn in catalogue and catalogue[sn] != value:
                raise ValueError('SIMD source COMMON symbol gets conflicting addresses')
            catalogue[sn] = value; commons[r['member_offset'], r['symbol_index']] = r
        else:
            h = struct.unpack_from('<8sIIIIIIHHI', body, 20+(r['section']-1)*40)
            definitions = [d for d in defs if d['section'] == r['section'] and not d['symbol'].startswith('.')]
            if h[3] != r['size'] or h[7] or h[9] != r['flags'] or definitions != r['definitions']:
                raise ValueError('SIMD entire source data section or definitions differ')
            if r['kind'] == 'source-zero-fill-section':
                if (h[4] or not h[9]&0x80 or h[9]&0x20
                        or carrier.zero_region(target, int(r['base'], 16), r['size']) != r['pe_region']):
                    raise ValueError('SIMD BSS allocation is not full source/PE zero-fill')
            elif r['kind'] == 'source-initialized-section':
                raw = body[h[4]:h[4]+h[3]]; native = c.pe_bytes_at(target, int(r['base'], 16), r['size'])
                if (not h[4] or h[9]&0x20 or not h[9]&0x40 or len(raw) != r['size']
                        or digest(raw) != r['source_sha256'] or digest(native) != r['body_sha256'] or raw != native):
                    raise ValueError('SIMD complete initialized data image differs')
            else:
                raise ValueError('SIMD source data kind differs')
            data_sections[r['member_offset'], r['section']] = r
    for r in m['controls']:
        a = r['address']; body = member(r)
        raw, fields, source = carrier.code_carrier(body, r['symbol'], c, coff)
        if (source != r['source'] or len(raw) != r['size'] or digest(raw) != r['source_sha256'] or fields != r['fields']):
            raise ValueError('SIMD entire source code carrier, entries or real fields differ')
        for f, b in zip(fields, r['bindings']):
            key = field_key(r['member_offset'], f); base = int(b['source_base'], 16)
            if f['symbol_type'] == 32:
                if f['symbol'] not in catalogue:
                    raise ValueError('SIMD pointer/call lacks a separately whole code owner')
                continue
            if f['symbol_section'] == 0:
                d = commons.get((r['member_offset'], f['symbol_index']))
                if d is None or d['symbol'] != f['symbol'] or d['size'] != f['symbol_offset']:
                    raise ValueError('SIMD external data field has no full source COMMON allocation')
                observed.add(('common', r['member_offset'], f['symbol_index']))
            else:
                d = data_sections.get((r['member_offset'], f['symbol_section']))
                if d is None or base != int(d['base'], 16)+f['symbol_offset']:
                    raise ValueError('SIMD local field uses another source member/section/definition')
                if not 0 <= f['symbol_offset']+f['addend'] < d['size']:
                    raise ValueError('SIMD source data field escapes its entire source section')
                if key in catalogue and catalogue[key] != base:
                    raise ValueError('SIMD local data symbol gets conflicting addresses')
                catalogue[key] = base; observed.add(('section', r['member_offset'], f['symbol_section']))
    if observed != {('common', off, index) for off, index in commons} | {('section', off, section) for off, section in data_sections}:
        raise ValueError('SIMD whole data evidence includes an unobserved or omitted allocation')
    for r in m['controls']:
        a = r['address']; raw, fields, source = carrier.code_carrier(member(r), r['symbol'], c, coff)
        linked, calls, data = bind_fields(raw, fields, r['bindings'], catalogue, r['member_offset'], int(a, 16))
        native = c.pe_bytes_at(target, int(a, 16), r['size'])
        if linked != native or digest(native) != r['body_sha256']:
            raise ValueError('SIMD entire linked carrier differs; alignment or fields cannot be masked')
        flow = carrier.carrier_flow(linked, int(a, 16), source, fields, calls, data, sdk)
        if flow != r['flow'] or flow['indirect_call_count'] != r['indirect_call_count']:
            raise ValueError('SIMD full CFG, entries, reachable extent or alignment differ')
        if a in selected:
            rec = selected[a]; mode = 'original' if args.evidence_only else 'accepted'
            expected_function, expected_origin = rec[mode+'_function'], rec[mode+'_origin']
        else:
            expected_function, expected_origin = r['function'], r['origin']
        if functions.get(a) != expected_function or origins.get(a) != expected_origin:
            raise ValueError('SIMD bounded or non-inventory ledger snapshot differs')
        if r['old_sdk_record'] is not None and old_sdk.get(a) != r['old_sdk_record']:
            raise ValueError('SIMD previous complete SDK evidence differs')
    print('R189 origins OK: six entire library policies /1670 function bytes; 56 whole source carriers /12960 bytes, 12463 reachable function bytes and497 independently decoded alignment bytes; all264 actual fields; both full272-byte initializers with67 pointers; nine whole writable initialized data sections /2816 bytes, real32-byte BSS and six source COMMON declarations for three shared allocations /36 bytes; original secondary entries and prior/non-inventory rows retained; no source/ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError) as exc:
        print('error: '+str(exc), file=sys.stderr)
        raise SystemExit(1)
