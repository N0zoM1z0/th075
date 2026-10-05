#!/usr/bin/env python3
"""Cold-replay paired_clearing authored policies and original vector count assignment."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('paired_clear_prior', ROOT / 'scripts/verify-neighbor-policy-origins.py')
PRIOR = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(PRIOR)
SOURCE = PRIOR.SOURCE
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/paired-clear-policy-origin-evidence.json'
MANIFEST_SHA256 = '13478d1b711301bca5523c3a2bb2be0728caf55d077581ab01f2b1479b4bc3d7'
PLAN_DIGESTS = {'groups': 'e36708480e629b25440c21d173655d7dbb29a72afb8c26363313b973057f046c', 'sections': '4f7099dbc1e555cf0e38917b47e06ac63950a5cc6b60598735f52748d326c657', 'weak_references': 'dff0ccf6b339d0d087639d3aecbf880f7a9324496a512aa5f28590fb4edfe09d', 'evidence_id': '6ff4b8172930cc7800c93a500838b2f4f9d205b58d713391ff2b45dce65de4e1', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'prior': 'bafd279e278bf5f28b7a9f51da21e4786ee59c8b27fdae6eb3ffb009349833d1', 'functions': '206819931037a0529900d5ccf41f8bc97fb8b5a12bbeed7e3b82181c5b460e42', 'retained_unknowns': 'd0af285abc8abdf96037d2f2d69910c6d223712d8d0079c225ebac8c97166bb1', 'parents': '54448a7a6f9901a89f94a4f64edb1ad0b86686d1204132809c4fc3558cfef4d9', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'memset': '078e6f9e489d82cafd1e133ba0dcc33afcd8b9a83cfcdd5036aae782d06342f2', 'authored_path': '4688f6022f8b7d3ed2262bab79e270998f07dfe64b7e292c3b67977bdf67f271', 'opaque_destructor': '071eeb3cf36f22391a69b2c86d02ed358c0f2f598fcbb1d86fd7ad14fd8d4c85', 'bit_context': '1ec22b52d7a2fd97fe11dfc69ca09033b11d17a7465db5745bc6175ecbc87d31', 'background_context': '3ba3f502e06b0a72e7c2ef5607607c59df47a2c5dd8377af323bcc774298f6ea', 'native_unknowns': '9f087b8e301a36e3f8757d5fe0752db6a9509c87afed3f8d338a6f7f91ce0023', 'public_control': '3310b88f67125a5612f507eadeb5f4bf0f5b6e071ae5bbe74068e90a9cd14ef9', 'alternatives': 'aa9b76227485a3dab51d31ce3d94f6e6eb610044cb0630e69172254d25be449d', 'retained_sha256': 'ee6d97357b53adb6854cf254500e302dde1057d6c521cc3d6deee3e83d678bde'}
WHOLE = {'0x00421250': 75, '0x005F7F20': 75, '0x00416D50': 111, '0x0044E8D0': 94}


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
        if value[:3].lower() != 'z:/': raise ValueError('PairedClear original include loses host mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/') and relative not in (
                'tests/origin_probes/VectorInsertionCarriers.cpp',):
            raise ValueError('PairedClear original include imports an unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('PairedClear immutable complete evidence differs: ' + key)
    if (m['evidence_id'] != 'R212' or {r['address']: r['size'] for r in m['functions']} != WHOLE
            or len(m['functions']) != 4 or len(m['groups']) != 2
            or len(m['sections']) != 58 or sum(r['size'] for r in m['sections']) != 2184
            or sum(len(r['fields']) for r in m['sections']) != 100
            or sum(r['kind'] == 'code' for r in m['sections']) != 49
            or len(m['retained_unknowns']) != 4 or len(m['parents']) != 7 or m['historical_snapshots']
            or len(m['native_unknowns']) != 1 or m['opaque_destructor']['size'] != 43
            or len(m['public_control']['emission']) != 381
            or sum(r['size'] for r in m['public_control']['emission']) != 22716
            or [r['size'] for r in m['alternatives']] != [22, 22]):
        raise ValueError('PairedClear loses complete bounded policies and carrier/default controls')
    for r in m['functions']:
        f, o, af, ao = (r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin'])
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified'
                or any(f[k] or af[k] for k in ['source_file', 'signature', 'calling_convention']) or f['owner']
                or f['match_percent'] != '0.00' or af['match_percent'] != '0.00'
                or any(af[k] != f[k] for k in ['address', 'size', 'span_end', 'current_name'])
                or af['size'] != str(r['size']) or ao['evidence_id'] != 'R212'
                or af['owner'] or af['status'] != 'unclassified' or ao['origin'] != 'authored'
                or ao['disposition'] != 'authored'):
            raise ValueError('PairedClear gains unsupported extent/private ABI/source/origin/exact credit')

    for r in m['retained_unknowns']:
        if (r['origin']['origin'] != 'unknown' or r['function']['status'] != 'unclassified'
                or r['function']['owner'] or r['function']['source_file']):
            raise ValueError('PairedClear assigns unresolved short/private ownership')


def check_call(raw, address, call):
    site = int(call['site'], 16); offset = site - address
    if (offset < 0 or offset + 5 > len(raw) or raw[offset] != 0xe8
            or site + 5 + struct.unpack_from('<i', raw, offset + 1)[0] != int(call['target'], 16)):
        raise ValueError('PairedClear loses complete native parent/policy call evidence')


def verify_native_context(m, target, c, flow, pe, authored, functions, origins):
    """Read actual instructions and owned data without claiming original private layouts."""
    by_address = {r['address']: r for r in [*m['functions'], *m['parents']]}

    def instruction(address, site):
        r = by_address[address]
        return next(i for i in r['instructions'] if int(address, 16) + i['offset'] == int(site, 16))

    bit = m['bit_context']
    if (bit['field_offset'], bit['index_min'], bit['index_max_inclusive'], bit['divisor']) != (0x16a9c, 0, 320, 32):
        raise ValueError('PairedClear changes the native inclusive signed-short bit domain')
    for address in ['0x00416D50', *bit['anchors']]:
        ins = by_address[address]['instructions']
        pairs = [(i['mnemonic'], i['operands']) for i in ins]
        if (not any(a == 'movsx' and 'word ptr [ebp + 8]' in b for a, b in pairs)
                or not any(a == 'cmp' and b.endswith(', 0x140') for a, b in pairs)
                or not all(any(i['mnemonic'] == op for i in ins) for op in ['jg', 'jge', 'sar'])
                or len([i for i in ins if i['mnemonic'] == 'sar']) != (1 if address == '0x00416DC0' else 2)
                or not all(i['operands'].endswith(', 5') for i in ins if i['mnemonic'] == 'sar')
                or not any(a == 'and' and b.endswith(', 0x1f') for a, b in pairs)):
            raise ValueError('PairedClear loses the actual signed guard/division in the bit-policy family')
    clear = by_address['0x00416D50']['instructions']
    if (clear[-1]['operands'] != '4' or clear[26]['mnemonic'] != 'sub'
            or clear[25]['operands'] != 'ecx, 0xffffffff'
            or clear[28]['mnemonic'] != 'and' or 'eax*4 + 0x16a9c' not in clear[28]['operands']
            or clear[-4]['mnemonic'] != 'mov' or 'eax*4 + 0x16a9c' not in clear[-4]['operands']):
        raise ValueError('PairedClear loses the complete complement-mask clear/store or RET4')
    for site in bit['sites']:
        i = instruction(site['parent'], site['site'])
        if i['mnemonic'] != site['mnemonic'] or 'eax*4 + 0x16a9c' not in i['operands']:
            raise ValueError('PairedClear bit context borrows an unrelated relative field')
    bg = m['background_context']
    slot = int(bg['slot_address'], 16)
    if (bg['table_extent_claim'] is not None or bg['slot_index'] != 1
            or slot != int(bg['table_address'], 16) + 4
            or c.pe_bytes_at(target, slot, 4).hex() != bg['slot_bytes']
            or struct.unpack('<I', bytes.fromhex(bg['slot_bytes']))[0] != int(bg['target'], 16)
            or pe.image_permissions(target, slot, 4) != 0x40000000):
        raise ValueError('PairedClear loses the actual readonly selected BG05b callback slot')
    for site in bg['owner_table_writes']:
        i = instruction(site['parent'], site['site'])
        raw = c.pe_bytes_at(target, int(site['site'], 16), i['size'])
        if (i['mnemonic'] != 'mov' or raw.hex() != site['instruction_bytes']
                or struct.unpack_from('<I', raw, 2)[0] != int(bg['table_address'], 16)):
            raise ValueError('PairedClear callback table lacks its complete accepted game owners')
    for site in bg['counter_initialization']:
        i = instruction('0x0044E810', site['site'])
        if i['mnemonic'] != 'mov' or f'+ {hex(site["field"])}], 0' not in i['operands']:
            raise ValueError('PairedClear counters lack their actual game initialization')
    literal = bytes.fromhex(bg['literal_bytes']); address = int(bg['literal_address'], 16)
    if (literal != b'data\\background\\BG05b.dat\0' or c.pe_bytes_at(target, address, len(literal)) != literal
            or pe.image_permissions(target, address, len(literal)) != 0x40000000
            or instruction('0x0044E810', bg['literal_push'])['operands'] != hex(address)):
        raise ValueError('PairedClear loses the complete BG05b resource-path identity')
    counter = by_address[bg['target']]['instructions']
    if (bg['wrap_values'] != [3840, 42]
            or not any(i['operands'].endswith('+ 0x68], 0xf00') for i in counter)
            or not any(i['mnemonic'] == 'cmp' and i['operands'].endswith('+ 0x6c], 0x2a') for i in counter)
            or not all(any(f'+ {hex(field)}]' in i['operands'] for i in counter) for field in [0x68, 0x6c, 0x70])):
        raise ValueError('PairedClear loses a complete game counter or its wrap value')
    for r in m['native_unknowns']:
        f, o = r['function'], r['origin']; a = int(f['address'], 16)
        raw = c.pe_bytes_at(target, a, int(f['size']))
        if (functions[f['address']] != f or origins[o['address']] != o or o['origin'] != 'unknown'
                or digest(raw) != r['body_sha256'] or list(authored.verify_body(raw, a)) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('PairedClear changes or crops the protected coordinate unknown')
        for scalar in r['scalars']:
            address = int(scalar['address'], 16); data = c.pe_bytes_at(target, address, 4)
            if (data.hex() != scalar['bytes'] or struct.unpack('<f', data)[0] != scalar['value']
                    or pe.image_permissions(target, address, 4) != 0x40000000):
                raise ValueError('PairedClear coordinate scalar loses its actual readonly definition')
        for site in r['writable_fields']:
            i = next(i for i in r['instructions'] if a + i['offset'] == int(site['site'], 16))
            if (i['mnemonic'] != 'fstp' or i['operands'] != f'dword ptr [{hex(int(site["address"], 16))}]'
                    or pe.image_permissions(target, int(site['address'], 16), 4) != 0xc0000000):
                raise ValueError('PairedClear coordinate output lacks its actual writable destination')
        if not all(any(f'+ {hex(field)}]' in i['operands'] for i in r['instructions']) for field in r['receiver_fields']):
            raise ValueError('PairedClear coordinate diagnostic omits an observed receiver field')


def replay(m, evidence_only=False):
    c = module('paired_clear_target', 'compare-coff-function.py'); coff = module('paired_clear_coff', 'coff_data.py')
    extra = module('paired_clear_carriers', 'sdk_x3d_carriers.py'); flow = module('paired_clear_flow', 'sdk_image_carriers.py')
    pe = module('paired_clear_permissions', 'verify-sdk-x3d-origins.py'); rt = module('paired_clear_crt', 'verify-runtime-origins.py')
    authored = module('paired_clear_authored', 'verify-authored-origins.py')
    inventory = module('paired_clear_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('PairedClear target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    own = list(csv.DictReader((ROOT / m['authored_path']).open()))
    if own != [r['record'] for r in m['functions'] if r['accepted_origin']['origin'] == 'authored']: raise ValueError('PairedClear own authored records differ')
    for r in m['functions']:
        if digest(c.pe_bytes_at(target, int(r['address'], 16), r['size'])) != r['record']['body_sha256']:
            raise ValueError('PairedClear own authored record lacks the complete body')
        if functions[r['address']] != r[state + '_function'] or origins[r['address']] != r[state + '_origin']:
            raise ValueError('PairedClear bounded canonical transition differs')
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (digest(raw) != r['body_sha256'] or list(authored.verify_body(raw, a)) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('PairedClear complete authored native body/CFG differs')
        for call in r['calls']: check_call(raw, a, call)
    for r in m['retained_unknowns']:
        if functions[r['function']['address']] != r['function'] or origins[r['origin']['address']] != r['origin']:
            raise ValueError('PairedClear changes a protected short/private unknown')
    prior = json.loads((ROOT / m['prior']['path']).read_text())
    if (digest((ROOT / m['prior']['path']).read_bytes()) != m['prior']['manifest_sha256']
            or prior['prior']['shared'] != m['prior']['shared'] or prior['prior']['absolute'] != m['prior']['absolute']
            or prior['prior']['crt_archive_sha256'] != m['prior']['crt_archive_sha256']):
        raise ValueError('PairedClear replaces independent prior source ownership')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-neighbor-policy-origins.py')],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode: raise ValueError('PairedClear complete prior cold graph failed: ' + result.stderr)
    print(result.stdout.strip(), flush=True)
    old = json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())
    source_catalog = SOURCE.BASE.retained_catalog(old); shared = {'__except_list': 0}
    for r in m['prior']['shared']:
        owner = r['owner']
        if old[owner['collection']][owner['index']] != owner['record'] or source_catalog.get(r['symbol']) != int(r['address'], 16):
            raise ValueError('PairedClear field observation overrides retained full source definition')
        shared[r['symbol']] = source_catalog[r['symbol']]
    records = list(csv.DictReader((ROOT / 'config/authored-origin-evidence.csv').open()))
    switches = list(csv.DictReader((ROOT / 'config/authored-origin-switches.csv').open()))
    direct = list(csv.DictReader((ROOT / 'config/authored-origin-direct-switches.csv').open()))
    for r in [*m['parents'], m['opaque_destructor']]:
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (r['record'] not in records or functions[r['address']] != r['function'] or origins[r['address']] != r['origin']
                or r['origin']['origin'] != 'authored' or digest(raw) != r['body_sha256']
                or digest(raw) != r['record']['body_sha256']
                or [q for q in switches if q['address'] == r['address']] != r['switches']
                or [q for q in direct if q['address'] == r['address']] != r['direct_switches']
                or list(authored.verify_body(raw, a, r['switches'], lambda x, n: c.pe_bytes_at(target, x, n), r['direct_switches'])) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('PairedClear complete authored game parent/CFG differs')
        for call in r['calls']: check_call(raw, a, call)
    opaque = m['opaque_destructor']
    if digest((ROOT / opaque['prior_path']).read_bytes()) != opaque['prior_sha256']:
        raise ValueError('PairedClear replaces the full accepted external destruction proof')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / opaque['proof'])],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode: raise ValueError('PairedClear external destructor cold proof failed: ' + result.stderr)
    print(result.stdout.strip(), flush=True)
    if (opaque['instructions'][3]['operands'] != 'dword ptr [ebp - 8], ecx'
            or opaque['instructions'][-1]['mnemonic'] != 'ret' or opaque['instructions'][-1]['operands']):
        raise ValueError('PairedClear external destruction loses its receiver/no-stack-argument ABI')
    shared[opaque['symbol']] = int(opaque['address'], 16)
    verify_native_context(m, target, c, flow, pe, authored, functions, origins)
    p = m['memset']; q = p['record']; crt = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(crt) != q['archive_sha256'] or q not in list(csv.DictReader((ROOT / 'config/runtime-origin-evidence.csv').open())):
        raise ValueError('PairedClear original memset archive/record differs')
    name, body = {a: (n, b) for a, n, b in rt.archive_members(crt)}[int(q['member_offset'])]
    raw, fields, source = extra.section_carrier(body, p['source']['section'], c, coff); a = int(q['address'], 16)
    aux = next(x for x in source['aux_records'] if x['symbol'] == '_memset')
    if (name != q['member'] or digest(body) != p['member_sha256'] or SOURCE.BASE.canonical_source(source, body) != p['source']
            or fields != p['fields'] or fields or len(raw) != 96 or aux['aux_count'] != 1
            or struct.unpack_from('<I', bytes.fromhex(aux['aux_hex']), 4)[0] != len(raw)
            or raw != c.pe_bytes_at(target, a, 96) or digest(raw) != q['body_sha256']
            or list(authored.verify_body(raw, a)) != p['cfg'] or SOURCE.instructions(raw, a, flow) != p['instructions']
            or functions[q['address']] != p['function'] or origins[q['address']] != p['origin']):
        raise ValueError('PairedClear memset lacks its complete original own-AUX/native/CFG proof')
    shared['_memset'] = a
    scratch = ROOT / 'build/origin-paired-clear-policy-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'PairedClear.obj'; control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or headers(result.stdout + result.stderr) != control['headers']:
            raise ValueError('PairedClear cold generic source/original includes differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != control['emission']: raise ValueError('PairedClear omits ordinary code/data/EH emission')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 60 or list(struct.unpack('<15I', layout)) != control['layout_values']:
            raise ValueError('PairedClear crops the complete generic observation carrier')
        if [SOURCE.weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
            raise ValueError('PairedClear loses actual weak AUX/strong fallback')
        rows = m['sections']; decoded = {}
        for r in rows:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff); a = int(r['base'], 16)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                    or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                raise ValueError('PairedClear complete source/AUX/fields/permissions differ')
            decoded[r['source']['section']] = (raw, fields)
            if r['kind'] == 'code':
                actual = [dict(function=f, origin=origins[k]) for k, f in functions.items() if a <= int(k, 16) < a + r['size']]
                expected = [dict(function=selected[q['function']['address']][state + '_function'],
                                 origin=selected[q['function']['address']][state + '_origin'])
                            if q['function']['address'] in selected else q for q in r['inventory_entries']]
                if actual != expected: raise ValueError('PairedClear full source hides an inventory entry')
        for g in m['groups']:
            rows = [r for r in m['sections'] if r['group'] == g['id']]
            catalog = SOURCE.owned_catalog(rows, shared, g['id'], [r for r in m['weak_references'] if r['symbol'] in g['weak_symbols']])
            for r in rows:
                raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
                linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a, data_image=r['kind'] == 'data')
                actual = c.pe_bytes_at(target, a, len(raw))
                if linked != actual or digest(actual) != r['body_sha256']: raise ValueError('PairedClear complete unmasked body differs')
                if r['kind'] == 'code':
                    roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type'] == 32 and d['storage'] == 3)
                    roots.update(f['symbol_offset'] + f['addend'] for q in rows for f in q['fields']
                                 if f['symbol_section'] == r['source']['section'] and f['symbol_storage'] == 6)
                    if sorted(roots) != r['roots'] or flow.flow(actual, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                        raise ValueError('PairedClear complete normal/EH/unwind/shared-exit CFG differs')
        for r in m['alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields'] or len(raw) != r['size']
                    or digest(raw) != r['source_sha256'] or SOURCE.instructions(raw, 0x100000, flow) != r['instructions']):
                raise ValueError('PairedClear complete default/value-initialization control differs')
        for root in ['0x00421250', '0x005F7F20']:
            explicit = next(r for r in m['sections'] if r['base'] == root)
            if (sum(f['symbol'].startswith('?clear@') for f in explicit['fields']) != 1
                    or any(f['symbol'].startswith('?clear@') for r in m['alternatives'] for f in r['fields'])):
                raise ValueError('PairedClear implicit constructor22 replaces explicit reset75')



def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']), *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('PairedClear immutable source/evidence differs: ' + path)
    replay(m, args.evidence_only)
    print('R212 origins OK: four authored paired construction/unlock-bit/BG05b policies355; '
          '58 scoped whole code/data carriers2184/all100 fields/49 CFGs; 381 ordinary emissions22716/29 '
          'original includes/full combined observation60; two complete implicit22 controls; seven complete '
          'game contexts6129/two actual calls; full R211 and external destruction R153 cold proofs; '
          'four short controls and coordinate111 remain unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
