#!/usr/bin/env python3
"""Cold-check whole script buffer lifetime controls and independent pointer ownership."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
KEYS = {'0x00421200': 24, '0x00421220': 43}
CONFIDENCE = 'complete-script-buffer-policy-typed-array-delete-and-lifetime-controls'
MANIFEST_SHA256 = '5cd6870dd2339ac7bd536914492765f22d5c3208789866d63113196bc6280329'
PROFILE = ['/Od', '/Ob0', '/Gy', '/GR-', '/GX', '/Zi', '/GS', '/I', 'src', '/showIncludes']


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


PRIOR = module('script_buffer_prior', 'verify-nested-deque-size-origins.py')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest():
    return json.loads((ROOT / 'config/script-buffer-origin-evidence.json').read_text())


def inventory(data, comparison, coff):
    """Freeze every ordinary whole defining section and every actual typed field."""
    count, definitions = coff.parse_symbols(data, comparison.coff_name)
    _, _, _, symbol_offset, symbol_count, _, _ = struct.unpack_from('<HHIIIHH', data)
    strings_offset = symbol_offset + symbol_count * 18
    strings = data[strings_offset:strings_offset + struct.unpack_from('<I', data, strings_offset)[0]]
    symbols = {}
    index = 0
    while index < symbol_count:
        name, offset, section, kind, storage, aux = struct.unpack_from('<8sIhHBB', data, symbol_offset + index * 18)
        symbols[index] = dict(symbol=comparison.coff_name(name, strings), offset=offset,
                              section=section, type=kind, storage=storage)
        index += 1 + aux
    result = []
    for index in range(count):
        h = struct.unpack_from('<8sIIIIIIHHI', data, 20 + index * 40)
        if not h[3] or not h[9] & 0xE0 or h[0].startswith(b'.debug'):
            continue
        if not h[4] or h[4] + h[3] > len(data):
            raise ValueError('script buffer carrier is not a complete initialized section')
        raw = data[h[4]:h[4] + h[3]]
        fields = []
        for j in range(h[7]):
            offset, number, kind = struct.unpack_from('<IIH', data, h[5] + j * 10)
            if kind not in (6, 20) or offset + 4 > len(raw) or number not in symbols:
                raise ValueError('script buffer carrier has an unresolved or partial source field')
            fields.append(dict(offset=offset, type='DIR32' if kind == 6 else 'REL32',
                               symbol=symbols[number], addend=struct.unpack_from('<I', raw, offset)[0]))
        result.append(dict(section=index + 1, name=h[0].rstrip(b'\0').decode(), size=h[3], flags=h[9],
                           source_sha256=digest(raw), fields=fields,
                           definitions=[d for d in definitions if d['section'] == index + 1]))
    return result


def verify_plan(m):
    if (m['evidence_id'] != 'R153' or m['probe'] != 'probes/VC7ScriptBufferLifetimes.cpp'
            or len(m['functions']) != 2 or {r['address']: r['size'] for r in m['functions']} != KEYS
            or any(r['decision'] != 'authored' for r in m['functions'])
            or len(m['families']) != 4 or len(m['profiles']) != 3
            or [p['flags'][1] for p in m['profiles']] != ['/Ob0', '/Ob1', '/Ob2']
            or any(p['flags'] != PROFILE[:1] + [p['flags'][1]] + PROFILE[2:] for p in m['profiles'])
            or [len(p['functions']) for p in m['profiles']] != [48, 21, 21]
            or [sum(r['size'] for r in p['functions']) for p in m['profiles']] != [1933, 982, 982]
            or [len(p['sections']) for p in m['profiles']] != [63, 22, 22]
            or [sum(r['size'] for r in p['sections']) for p in m['profiles']] != [2414, 1022, 1022]
            or any(len(p['headers']) != 24 for p in m['profiles'])
            or any(r['size'] in (24, 43) for p in m['profiles'][1:] for r in p['functions'])
            or m['layout'] != [8, 4, 8, 4, 8, 4, 4, 8, 4, 4]
            or m['runtime']['address'] != '0x0064169D' or m['runtime']['size'] != 5
            or m['runtime']['symbol'] != '??_V@YAXPAX@Z' or m['runtime']['member_offset'] != 854462
            or m['runtime']['callee']['address'] != '0x00640F15'
            or m['runtime']['callee']['coff_symbol'] != '??3@YAXPAX@Z'
            or m['runtime']['free']['address'] != '0x00642A61' or m['runtime']['free']['size'] != 113
            or m['parser']['address'] != '0x00420880' or m['parser']['size'] != 2301
            or m['parser']['evidence']['evidence_id'] != 'R070'
            or len(m['cleanup_entries']) != 8 or m['frame']['handler_address'] != '0x006555B8'
            or m['scalar_deleting']['address'] != '0x004229F0' or m['scalar_deleting']['size'] != '44'):
        raise ValueError('script buffer loses whole source-family, original parser or typed runtime provenance')
    binding = m['runtime']['bindings']
    if (len(binding) != 1 or binding[0]['offset'] != 1 or binding[0]['type'] != 'REL32'
            or binding[0]['symbol'] != '??3@YAXPAX@Z' or binding[0]['target_address'] != '0x00640F15'
            or binding[0]['addend']
            or m['scalar_deleting']['destructor_address'] != '0x00421220'
            or m['scalar_deleting']['delete_address'] != '0x00640F15'):
        raise ValueError('script array release loses its independently complete scalar-delete owner')
    for family in m['families']:
        ctor, dtor = family['constructor'], family['destructor']
        if (ctor['size'] != 24 or ctor['fields'] or not ctor['symbol'].startswith('??0?$GuardedArrayRecord@')
                or dtor['size'] != 43 or not dtor['symbol'].startswith('??1?$GuardedArrayRecord@')
                or len(dtor['fields']) != 1 or dtor['fields'][0]['offset'] != 32
                or dtor['fields'][0]['symbol'] != '??_V@YAXPAX@Z'
                or dtor['fields'][0]['type'] != 'REL32' or dtor['fields'][0]['addend']):
            raise ValueError('script record substitutes a partial owner or scalar-delete field')
    if (len(m['rejected']) != 8 or not any(r['symbol'] == '??1ScalarRecord@@QAE@XZ'
            and r['size'] == 43 and r['typed_difference'] > 0 for r in m['rejected'])
            or any(not (r['size_difference'] or r['typed_difference']) for r in m['rejected'])):
        raise ValueError('script buffer gains credit from an equal-shaped wrong typed owner')
    operations = [(r['mnemonic'], r['operands']) for r in m['parser']['pointer_window']]
    if (len(operations) != 35 or ('call', '0x6416a2') not in operations
            or ('mov', 'dword ptr [eax + 4], edx') not in operations
            or ('mov', 'eax, dword ptr [eax + 4]') not in operations
            or ('mov', 'ecx, eax') not in operations
            or operations[-1] != ('mov', 'byte ptr [edx + ecx], 0')):
        raise ValueError('script record lacks actual parser allocation/store/read pointer ownership')
    if (len(m['parser']['lifetime_pairs']) != 8
            or m['parser']['producer']['address'] != '0x004213E0'
            or m['parser']['producer']['size'] != '215' or m['parser']['producer']['evidence_id'] != 'R072'
            or 'DequeProbeRecord@$07' not in m['parser']['producer']['coff_symbol']):
        raise ValueError('script lifetime loses its independently complete eight-byte record producer')
    for pair in m['parser']['lifetime_pairs']:
        construct, release = operations_of(pair['construct']), operations_of(pair['release'])
        if (len(construct) != 10 or len(release) != 2
                or construct[0][0] != 'lea' or not construct[0][1].startswith('ecx, [ebp - ')
                or construct[1] != ('call', '0x421200')
                or construct[-2:] != [('mov', 'ecx, eax'), ('call', '0x4213e0')]
                or release != [construct[0], ('call', '0x421220')]):
            raise ValueError('script lifetime changes actual local constructor/copy/cleanup pairing')


def operations_of(window):
    return [(r['mnemonic'], r['operands']) for r in window]


def check_ledger(r, function, origin, evidence_only=False):
    if (int(function['size']) != r['size'] or function['span_end'] != r['span_end']
            or function['source_file'] or function['signature'] or function['calling_convention']
            or function['match_percent'] != '0.00'):
        raise ValueError('script record changes own extent or grants source/ABI/exact')
    if not evidence_only and (origin['origin'] != 'authored' or origin['disposition'] != 'authored'
            or origin['subsystem'] != 'FighterScript' or origin['evidence_id'] != 'R153'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'authored'
            or function['module'] != 'FighterScript' or function['status'] != 'unclassified'
            or function['proposed_name'] != r['inferred_role']):
        raise ValueError('script record canonical whole policy acceptance differs')


def check_authored_records(m, rows):
    expected = [dict(address=r['address'], size=str(r['size']), body_sha256=r['body_sha256'],
                     inferred_role=r['inferred_role'], return_count='1',
                     internal_branch_count=str(r['internal_branch_count']), external_branch_count='0', evidence_id='R153')
                for r in m['functions']]
    if sorted((r for r in rows if r['address'] in KEYS), key=lambda r: r['address']) != expected:
        raise ValueError('script lifetime loses its unique complete authored body/CFG records')


def verify_runtime(m, archive, comparison, record, target, temporary):
    runtime = module('script_buffer_archive', 'verify-runtime-origins.py')
    members = {offset: (name, data) for offset, name, data in runtime.archive_members(archive)}
    row = m['runtime']
    catalog = {'??_V@YAXPAX@Z': 0x0064169D, '??3@YAXPAX@Z': 0x00640F15, '_free': 0x00642A61}
    for entry, symbol_key, fields_key in [(row, 'symbol', 'bindings'), (row['callee'], 'coff_symbol', 'relocation_bindings')]:
        name, data = members[entry['member_offset']]
        symbol = entry[symbol_key]
        if name != entry['member'] or digest(data) != entry['member_sha256']:
            raise ValueError('script buffer runtime changes its pinned whole archive member')
        path = temporary / ('runtime' + str(entry['member_offset']) + '.obj')
        path.write_bytes(data)
        n = record.complete_aux_section_size(data, symbol, comparison.coff_name)
        source, fields = comparison.object_function(path, symbol, n)
        actual = comparison.pe_bytes_at(target, int(entry['address'], 16), n)
        if (n != 5 or digest(source) != entry['source_sha256'] or digest(actual) != entry['body_sha256']
                or PRIOR.link_complete(source, fields, int(entry['address'], 16), entry[fields_key], catalog) != actual):
            raise ValueError('array/scalar delete whole source fields fail independently bound unmasked comparison')
    free = row['free']
    _, data = members[free['member_offset']]
    path = temporary / 'free.obj'
    path.write_bytes(data)
    size = record.complete_aux_section_size(data, free['coff_symbol'], comparison.coff_name)
    source, fields = comparison.object_function(path, free['coff_symbol'], size)
    if (size != 113 or digest(data) != free['member_sha256'] or digest(source) != free['source_sha256']
            or digest(comparison.pe_bytes_at(target, 0x00642A61, size)) != free['body_sha256']):
        raise ValueError('typed delete fields lose their independently complete unchanged accepted free owner')
    return catalog


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    m = manifest()
    verify_plan(m)
    if digest((ROOT / 'config/script-buffer-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('reviewed whole script buffer metadata differs')
    comparison = module('script_buffer_target', 'compare-coff-function.py')
    record = module('script_buffer_extent', 'verify-vendor-record-origins.py')
    coff = module('script_buffer_coff', 'coff_data.py')
    authored = module('script_buffer_cfg', 'verify-authored-origins.py')
    target = comparison.verified_target()
    if digest(target) != m['target_sha256'] or digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('script buffer target or natural observation source differs')
    functions = {r['address']: r for r in authored.rows('functions.csv')}
    origins = {r['address']: r for r in authored.rows('function-origins.csv')}
    for r in m['functions']:
        check_ledger(r, functions[r['address']], origins[r['address']], args.evidence_only)
        raw = comparison.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if digest(raw) != r['body_sha256'] or authored.verify_body(raw, int(r['address'], 16)) != (1, r['internal_branch_count']):
            raise ValueError('script record complete body or all exits/control flow differ')
        padding_size = 8 if r['address'] == '0x00421200' else 5
        if comparison.pe_bytes_at(target, int(r['address'], 16) + r['size'], padding_size) != bytes([204]) * padding_size:
            raise ValueError('script record changes alignment or an adjacent original owner')
    if not args.evidence_only:
        check_authored_records(m, authored.rows('authored-origin-evidence.csv'))
    standard = json.loads((ROOT / 'config/standard-exception-origin-evidence.json').read_text())
    if (m['runtime']['callee'] not in standard['functions'] or m['runtime']['free'] not in standard['anchors']
            or origins['0x00640F15']['evidence_id'] != 'R142' or origins['0x00640F15']['origin'] != 'library'
            or origins['0x00642A61']['evidence_id'] != 'R120' or origins['0x00642A61']['origin'] != 'library'):
        raise ValueError('script record rewrites independently accepted whole runtime owners')
    p = m['parser']
    if (p['evidence'] not in authored.rows('authored-origin-evidence.csv')
            or origins[p['address']]['evidence_id'] != 'R070' or origins[p['address']]['origin'] != 'authored'
            or not authored.role_matches(functions[p['address']], p['evidence']['inferred_role'])
            or p['switches'] != [r for r in authored.rows('authored-origin-switches.csv') if r['address'] == p['address']]):
        raise ValueError('script record loses the independently authored complete parser')
    raw = comparison.pe_bytes_at(target, 0x00420880, p['size'])
    if (digest(raw) != p['body_sha256'] or int(functions[p['address']]['size']) != 2301
            or authored.verify_body(raw, 0x00420880, p['switches'], lambda a, n: comparison.pe_bytes_at(target, a, n)) != (1, 63)):
        raise ValueError('script parser whole body/guarded switch/control flow differs')
    ins = [dict(address=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str)
           for i in Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, 0x00420880)]
    start = next(i for i, row in enumerate(ins) if row['address'] == p['pointer_window'][0]['address'])
    if ins[start:start + len(p['pointer_window'])] != p['pointer_window']:
        raise ValueError('script pointer producer is not actual uninterrupted complete parent context')
    for pair in p['lifetime_pairs']:
        for window in pair.values():
            start = next(i for i, row in enumerate(ins) if row['address'] == window[0]['address'])
            if ins[start:start + len(window)] != window:
                raise ValueError('script lifetime pair loses actual uninterrupted whole-parser instructions')
    producer = p['producer']
    if (producer not in authored.rows('vendor-deque-operation-origins.csv')
            or origins[producer['address']]['origin'] != 'library'
            or digest(comparison.pe_bytes_at(target, 0x004213E0, 215)) != producer['body_sha256']):
        raise ValueError('script lifetime rewrites the accepted whole R072 byte-record producer')
    eh = module('script_buffer_eh', 'compiler_eh.py')
    if m['frame'] not in authored.rows('compiler-eh-frames.csv'):
        raise ValueError('script parser loses the original full frame record')
    eh.verify_frame(m['frame'], lambda a, n: comparison.pe_bytes_at(target, a, n),
                    lambda a, n: comparison.pe_bytes_at(target, a, n), {int(k, 16) for k in functions}, set())
    for row in m['cleanup_entries']:
        if (row not in authored.rows('compiler-origin-evidence.csv') or row['callee_address'] != '0x00421220'
                or digest(comparison.pe_bytes_at(target, int(row['address'], 16), int(row['size']))) != row['body_sha256']):
            raise ValueError('script lifetime loses complete original compiler cleanup entries')
    scalar = m['scalar_deleting']
    if (scalar not in authored.rows('scalar-deleting-origin-evidence.csv')
            or digest(comparison.pe_bytes_at(target, 0x004229F0, 44)) != scalar['body_sha256']):
        raise ValueError('script lifetime loses the entire independent original deleting destructor')
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(archive) != m['archive_sha256']:
        raise ValueError('script buffer runtime uses a different archive')
    scratch = ROOT / 'build/origin-script-buffer-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as name:
        temporary = Path(name)
        catalog = verify_runtime(m, archive, comparison, record, target, temporary)
        for profile in m['profiles']:
            path = temporary / (profile['name'] + '.obj')
            result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *profile['flags']],
                                    cwd=ROOT, capture_output=True, text=True)
            if result.returncode or PRIOR.PRIOR.included_headers(result.stdout + result.stderr) != profile['headers']:
                raise ValueError('script buffer cold compiler/actual SDK include provenance differs')
            data = path.read_bytes()
            if inventory(data, comparison, coff) != profile['sections']:
                raise ValueError('script buffer loses a whole cold code/data/EH carrier or actual field')
            for r in profile['functions']:
                source, fields = comparison.object_function(path, r['symbol'], r['size'])
                if digest(source) != r['source_sha256'] or fields != r['fields']:
                    raise ValueError('whole cold script lifetime source function differs')
                if r['extent_kind'] == 'own-complete-aux' and record.complete_aux_section_size(data, r['symbol'], comparison.coff_name) != r['size']:
                    raise ValueError('script lifetime truncates an actual own function AUX')
                if r['extent_kind'] == 'whole-defining-code-section':
                    section = next(s for s in profile['sections'] if s['section'] == r['source_definition']['section'])
                    if (r['source_definition']['offset'] or section['size'] != r['size']
                            or r['source_definition'] not in section['definitions']):
                        raise ValueError('script lifetime truncates a complete no-AUX source owner')
            if profile['name'] == 'ob0':
                layout = next(s for s in profile['sections'] if any(d['symbol'] == '_ScriptBufferLayout' for d in s['definitions']))
                raw_layout, _ = coff.readonly_section(data, layout['section'], comparison.coff_name)
                if list(struct.unpack('<10I', raw_layout)) != m['layout']:
                    raise ValueError('script buffer observation substitutes partial layout data')
                for family in m['families']:
                    for kind, key in [('constructor', '0x00421200'), ('destructor', '0x00421220')]:
                        r = family[kind]
                        n = record.complete_aux_section_size(data, r['symbol'], comparison.coff_name)
                        source, fields = comparison.object_function(path, r['symbol'], n)
                        bindings = [dict(**b, target_address='0x0064169D') for b in fields]
                        actual = comparison.pe_bytes_at(target, int(key, 16), n)
                        if PRIOR.link_complete(source, fields, int(key, 16), bindings, catalog) != actual:
                            raise ValueError('whole typed array lifetime body fails unmasked comparison')
                for rejected in m['rejected']:
                    source, fields = comparison.object_function(path, rejected['symbol'], rejected['size'])
                    actual = comparison.pe_bytes_at(target, int(rejected['target'], 16), KEYS[rejected['target']])
                    if len(source) == len(actual):
                        bindings = [dict(**b, target_address=f'0x{catalog[b["symbol"]]:08X}') for b in fields]
                        linked = PRIOR.link_complete(source, fields, int(rejected['target'], 16), bindings, catalog)
                        difference = sum(a != b for a, b in zip(linked, actual))
                        if difference != rejected['typed_difference'] or not difference:
                            raise ValueError('a whole differing SDK/scalar lifetime alternative gains typed credit')
    print('R153 origins OK: two complete authored script buffer policies / 67 bytes; four whole typed array '
          'constructor/destructor families; scalar-delete shape rejected through independent full runtime owners; '
          'three cold SDK/raw/explicit/implicit source profiles and every ordinary code/data/EH carrier; '
          'complete parser pointer producer, original frame/eight cleanups and scalar-deleting context; '
          'original types/full layouts unknown; no auxiliary/source/mapping/private ABI/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, StopIteration, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
