#!/usr/bin/env python3
"""Cold-replay complete nested deque receivers and their independent code/data/EH graph."""
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
KEYS = {'0x00421550', '0x0045DD50'}
CONFIDENCE = 'complete-nested-deque-code-data-eh-receiver-provenance'
MANIFEST_SHA256 = '5e6ccb4a95135d5cdb202e2511dc4594cac09b672d545ae258d26ffa5729ed42'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


PRIOR = module('nested_size_prior', 'verify-deque-size-context-origins.py')
STANDARD = module('nested_size_standard', 'verify-standard-exception-origins.py')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest():
    return json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id'] != 'R150' or m['profile'] != PRIOR.PROFILE
            or m['probe'] != 'probes/VC7NestedDequeSizeContexts.cpp'
            or len(m['functions']) != 2 or {r['address'] for r in m['functions']} != KEYS
            or any(r['size'] != 17 or r['decision'] != 'library' for r in m['functions'])
            or len(m['code']) != 53 or sum(r['size'] for r in m['code']) != 2980
            or len(m['state_data']) != 17 or sum(r['size'] for r in m['state_data']) != 524
            or len(m['code_carriers']) != 5 or sum(r['size'] for r in m['code_carriers']) != 82
            or len(m['emission_code']) != 82 or len(m['emission_data']) != 18 or len(m['headers']) != 27
            or len(m['external']) != 14 or len(m['retained_frames']) != 5):
        raise ValueError('complete bounded nested source/code/data/EH inventory differs')
    graph = {r['address']: r for r in m['code']}
    if graph['0x0045DD00']['size'] != 66 or graph['0x004215C0']['size'] != 45:
        raise ValueError('nested observation/control parent loses complete source extent')
    if not graph['0x00421550']['symbol'].startswith('?size@?$deque@V?$deque@'):
        raise ValueError('outer size loses its actual nested SDK source typing')
    if not graph['0x0045DD50']['symbol'].startswith('?size@?$deque@E'):
        raise ValueError('inner size loses its independent returned-container source typing')
    for r in m['functions']:
        if r['symbol'] != graph[r['address']]['symbol'] or graph[r['address']]['size'] != 17:
            raise ValueError('nested getter loses complete actual own source body')
    data = {r['address']: r for r in m['state_data']}
    if data['0x00657B34']['size'] != 27 or data['0x00667D60']['size'] != 16:
        raise ValueError('nested error identity loses whole literal/throw owner')
    if {a: data[a]['size'] for a in ('0x0066886C', '0x00667A6C', '0x00667AD8')} != {
            '0x0066886C': 36, '0x00667A6C': 36, '0x00667AD8': 132}:
        raise ValueError('nested EH provenance truncates an actual complete defining section')
    if {(r['address'], r['size']) for r in m['contexts']} != {('0x00420880', 2301), ('0x0045DD00', 66)}:
        raise ValueError('nested producer/count receiver context is incomplete')
    if (len(m['contexts'][0]['instruction_windows']) != 3
            or len(m['contexts'][1]['instruction_windows']) != 2):
        raise ValueError('nested caller loses actual outer/returned-inner receiver evidence')
    if m['retained_verifiers'] != ['verify-deque-size-context-origins.py', 'verify-standard-exception-origins.py']:
        raise ValueError('nested source loses complete independent retained cold evidence')
    check_receiver_protocol(m)
    if m['retained_legacy_helper']['address'] != '0x00421B70' or m['retained_legacy_helper']['evidence_id'] != 'R032':
        raise ValueError('new nested source silently rewrites the legacy shape observation')


def check_receiver_protocol(m):
    contexts = {r['address']: r for r in m['contexts']}
    witnesses = {i['address']: (i['mnemonic'], i['operands'])
                 for r in contexts.values() for window in r['instruction_windows'] for i in window}
    required = {
        '0x00420939': ('mov', 'ecx, dword ptr [ebp - 0x7c]'),
        '0x0042093C': ('add', 'ecx, 0x7d0'),
        '0x00420942': ('call', '0x4215c0'),
        '0x00420947': ('mov', 'ecx, eax'),
        '0x00420949': ('call', '0x4213e0'),
        '0x00420CE9': ('mov', 'ecx, dword ptr [ebp - 0x7c]'),
        '0x00420CEC': ('add', 'ecx, 0x7d0'),
        '0x00420CF2': ('call', '0x421550'),
        '0x0045DD27': ('mov', 'ecx, dword ptr [ebp - 4]'),
        '0x0045DD2A': ('add', 'ecx, 0x7d0'),
        '0x0045DD30': ('call', '0x421570'),
        '0x0045DD35': ('mov', 'ecx, eax'),
        '0x0045DD37': ('call', '0x45dd50'),
    }
    if any(witnesses.get(site) != operation for site, operation in required.items()):
        raise ValueError('nested typing loses the real equal outer/returned-inner receiver protocol')


def check_ledger(row, function, origin, evidence_only=False):
    if (int(function['size']) != 17 or function['span_end'] != row['span_end']
            or function['source_file'] or function['signature'] or function['calling_convention']
            or function['match_percent'] != '0.00'):
        raise ValueError('nested origin grants source/private ABI/exact or truncates its extent')
    if not evidence_only and (origin['origin'] != 'library' or origin['evidence_id'] != 'R150'
            or origin['disposition'] != 'exclude' or origin['confidence'] != CONFIDENCE
            or origin['subsystem'] != 'VC7STL' or function['owner'] != 'library'
            or function['status'] != 'excluded' or function['module'] != 'VC7STL'
            or function['proposed_name'] != 'VC7::deque_Size_' + row['address'][2:]):
        raise ValueError('nested canonical complete library acceptance differs')


def code_extent(data, row, comparison, record):
    if row['extent_basis'] == 'function-auxiliary-record':
        size = record.complete_aux_section_size(data, row['symbol'], comparison.coff_name)
    elif row['extent_basis'] == 'whole-defining-code-section-without-AUX':
        d = row['source_definition']
        header = struct.unpack_from('<8sIIIIIIHHI', data, 20 + (d['section'] - 1) * 40)
        if d['offset'] or not header[9] & 32:
            raise ValueError('aux-less nested control loses its whole actual code owner')
        size = header[3]
    else:
        raise ValueError('nested source extent has no independent complete definition')
    if size != row['size']:
        raise ValueError('nested own AUX/complete code section extent differs')
    return size


def build_catalog(m, definitions):
    """Resolve fields only through separately complete source owners or retained controls."""
    catalog = {}

    def add(symbol, address):
        if symbol in catalog and catalog[symbol] != address:
            raise ValueError('nested source has inconsistent independent ownership for one symbol')
        catalog[symbol] = address

    for row in m['code']:
        d = row['source_definition']
        for entry in definitions:
            if (entry['section'] == d['section'] and d['offset'] <= entry['offset'] < d['offset'] + row['size']
                    and entry['storage'] in (2, 3) and not entry['symbol'].startswith('.')):
                add(entry['symbol'], int(row['address'], 16) + entry['offset'] - d['offset'])
    for row in m['state_data']:
        for entry in row['source_section']['definitions']:
            add(entry['symbol'], int(row['address'], 16) + entry['offset'])
    for row in m['code_carriers']:
        for entry in row['source_definitions']:
            add(entry['symbol'], int(row['address'], 16) + entry['offset'])
    for row in m['external']:
        if row['kind'] == 'fs-exception-list-offset' and (row['symbol'] != '__except_list' or row['address'] != '0x00000000'):
            raise ValueError('FS exception-list offset is misdeclared as ordinary target storage')
        add(row['symbol'], int(row['address'], 16))
    for weak, fallback in m['weak'].items():
        if fallback not in catalog:
            raise ValueError('nested weak alias lacks its complete actual strong fallback owner')
        add(weak, catalog[fallback])
    if any(catalog.get(symbol) != int(address, 16) for symbol, address in m['symbol_addresses'].items()):
        raise ValueError('nested observation cannot override independent complete source ownership')
    return catalog


def link_complete(source, fields, address, recorded, catalog):
    if len(fields) != len(recorded):
        raise ValueError('nested whole owner loses a typed relocation')
    linked = bytearray(source)
    occupied = set()
    for field, binding in zip(fields, recorded):
        if any(field[k] != binding[k] for k in ('offset', 'type', 'symbol', 'addend')):
            raise ValueError('nested cold source field topology differs')
        offset = field['offset']
        span = set(range(offset, offset + 4))
        if offset < 0 or offset + 4 > len(source) or occupied & span or field['type'] not in ('DIR32', 'REL32'):
            raise ValueError('nested field overlaps or escapes its complete owner')
        occupied |= span
        destination = catalog.get(field['symbol'])
        if destination is None or destination != int(binding['target_address'], 16):
            raise ValueError('nested field loses independent whole code/data/retained ownership')
        value = destination + field['addend']
        if field['type'] == 'REL32':
            value -= address + offset + 4
        struct.pack_into('<I', linked, offset, value & 0xffffffff)
    return bytes(linked)


def verify_cold_object(m, object_path, comparison, record, coff, target):
    data = object_path.read_bytes()
    definitions = coff.parse_symbols(data, comparison.coff_name)[1]
    emitted = [d for d in definitions if d['section'] > 0 and d['type'] == 32 and d['storage'] == 2]
    if emitted != [r['source_definition'] for r in m['emission_code']]:
        raise ValueError('nested cold SDK gains or loses an ordinary source function')
    for row in m['emission_code']:
        size = code_extent(data, row, comparison, record)
        source, fields = comparison.object_function(object_path, row['symbol'], size)
        if digest(source) != row['source_sha256'] or fields != row['relocations']:
            raise ValueError('complete natural nested emitted control differs')
    for row in m['emission_data']:
        raw, section, anchor = STANDARD.whole_defining_section(data, row['symbol'], comparison, coff)
        if section != row['source_section'] or anchor != row['source_anchor'] or digest(raw) != row['source_sha256']:
            raise ValueError('nested cold model loses a whole emitted data carrier')
    for weak, fallback in m['weak'].items():
        evidence = STANDARD.read_weak_reference(data, weak, comparison, coff, None)
        owner = next(r for r in m['code'] if r['symbol'] == fallback)
        if evidence['fallback_symbol'] != fallback or evidence['fallback_definition'] != owner['source_definition']:
            raise ValueError('cold nested weak alias loses its actual whole strong fallback record')
    catalog = build_catalog(m, definitions)
    sdk = module('nested_sdk_cfg', 'verify-sdk-origins.py')
    for row in m['code']:
        size = code_extent(data, row, comparison, record)
        source, fields = comparison.object_function(object_path, row['symbol'], size)
        actual = comparison.pe_bytes_at(target, int(row['address'], 16), size)
        if (fields != row['source_relocations'] or digest(source) != row['source_sha256']
                or digest(actual) != row['body_sha256']
                or link_complete(source, fields, int(row['address'], 16), row['relocations'], catalog) != actual):
            raise ValueError('nested complete unmasked source/body/fields differ')
        record.compare_complete_body(source, fields, actual, int(row['address'], 16), row['relocations'], comparison, sdk)
    for row in m['state_data']:
        raw, section, anchor = STANDARD.whole_defining_section(data, row['symbol'], comparison, coff)
        actual = comparison.pe_bytes_at(target, int(row['address'], 16), row['size'])
        if (section != row['source_section'] or anchor != row['source_anchor']
                or digest(raw) != row['source_sha256'] or digest(actual) != row['body_sha256']
                or link_complete(raw, section['relocations'], int(row['address'], 16), row['relocations'], catalog) != actual):
            raise ValueError('nested field/data identity truncates or masks a whole defining section')
    context = module('nested_cfg', 'verify-game-context-origins.py')
    for row in m['code_carriers']:
        first = row['source_definitions'][0]
        header = struct.unpack_from('<8sIIIIIIHHI', data, 20 + (first['section'] - 1) * 40)
        actual_definitions = sorted([d for d in definitions if d['section'] == first['section'] and d['type'] == 32], key=lambda d: d['offset'])
        if header[3] != row['size'] or first['offset'] or actual_definitions != row['source_definitions']:
            raise ValueError('nested EH carrier loses its actual complete partition')
        source, fields = comparison.object_function(object_path, first['symbol'], row['size'])
        actual = comparison.pe_bytes_at(target, int(row['address'], 16), row['size'])
        if (fields != row['source_relocations'] or digest(source) != row['source_sha256']
                or digest(actual) != row['body_sha256']
                or link_complete(source, fields, int(row['address'], 16), row['relocations'], catalog) != actual):
            raise ValueError('whole nested EH code carrier fails unmasked replay')
        for index, entry in enumerate(actual_definitions):
            end = actual_definitions[index + 1]['offset'] if index + 1 < len(actual_definitions) else row['size']
            start = entry['offset']
            a = int(row['address'], 16) + start
            decoder = Cs(CS_ARCH_X86, CS_MODE_32)
            decoder.detail = True
            instructions = list(decoder.disasm(actual[start:end], a))
            tails = [dict(site=f'0x{i.address:08X}', target=f'0x{i.operands[0].imm:08X}')
                     for i in instructions if i.mnemonic == 'jmp' and not a <= i.operands[0].imm < a + end - start]
            context.verify_bounded_context(actual[start:end], a, tails)
    layout = m['sdk_layout']
    raw, _, _ = STANDARD.whole_defining_section(data, layout['symbol'], comparison, coff)
    if list(struct.unpack('<10I', raw)) != [20, 20, 20, 20, 20, 20, 8, 8, 4, 2000]:
        raise ValueError('complete SDK nested/iterator/index-map observation layout differs')
    covered = ({r['source_definition']['section'] for r in m['emission_code']}
               | {r['source_definition']['section'] for r in m['code_carriers']}
               | {r['source_anchor']['section'] for r in m['emission_data']})
    count = struct.unpack_from('<H', data, 2)[0]
    for index in range(count):
        header = struct.unpack_from('<8sIIIIIIHHI', data, 20 + index * 40)
        if header[3] and header[9] & 0xE0 and not header[0].startswith(b'.debug') and index + 1 not in covered:
            raise ValueError('nested source has an unaccounted ordinary code/data carrier')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    m = manifest()
    verify_plan(m)
    if digest((ROOT / 'config/nested-deque-size-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('reviewed complete nested metadata differs')
    comparison = module('nested_target', 'compare-coff-function.py')
    record = module('nested_record', 'verify-vendor-record-origins.py')
    coff = module('nested_coff', 'coff_data.py')
    target = comparison.verified_target()
    if digest(target) != m['target_sha256'] or digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('nested target or actual natural SDK probe identity differs')
    functions = {r['address']: r for r in PRIOR.rows('functions.csv')}
    origins = {r['address']: r for r in PRIOR.rows('function-origins.csv')}
    for row in m['functions']:
        check_ledger(row, functions[row['address']], origins[row['address']], args.evidence_only)
    for row in m['code']:
        key = row['address']
        if row['ledger_size'] is not None and int(functions[key]['size']) != row['ledger_size']:
            raise ValueError('nested graph rewrites an independently accepted/provisional ledger extent')
        if key not in KEYS and row['origin'] != 'unknown' and (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']):
            raise ValueError('nested source overwrites a retained independent owner')
    for row in m['external']:
        if row['kind'] == 'fs-exception-list-offset':
            continue
        previous = json.loads((ROOT / 'config' / row['manifest']).read_text())
        inventory = previous['state_data'] if row['kind'] == 'retained-whole-data' else previous['boundaries'] if row['kind'] == 'retained-external-snapshot' else previous['functions'] + previous['anchors']
        if row['record'] not in inventory:
            raise ValueError('nested boundary loses its independent whole retained record')
        old = row['record']
        address = old.get('address', old.get('target_address'))
        expected = old.get('body_sha256', old.get('target_sha256'))
        if expected is not None and digest(comparison.pe_bytes_at(target, int(address, 16), row['size'])) != expected:
            raise ValueError('nested external owner loses its complete original snapshot')
    if m['retained_legacy_helper'] not in PRIOR.rows('vendor-record-helper-origins.csv'):
        raise ValueError('nested source rewrites an earlier provisional operation control')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    authored = module('nested_authored', 'verify-authored-origins.py')
    for row in m['contexts']:
        key, address = row['address'], int(row['address'], 16)
        actual = comparison.pe_bytes_at(target, address, row['size'])
        if digest(actual) != row['body_sha256'] or int(functions[key]['size']) != row['size']:
            raise ValueError('complete nested producer/count context differs')
        if row['origin'] != 'unknown' and (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']):
            raise ValueError('nested producer loses independent game ownership')
        authored.verify_body(actual, address, [r for r in PRIOR.rows('authored-origin-switches.csv') if r['address'] == key],
                             lambda a, n: comparison.pe_bytes_at(target, a, n),
                             [r for r in PRIOR.rows('authored-origin-direct-switches.csv') if r['address'] == key])
        instructions = list(decoder.disasm(actual, address))
        for window in row['instruction_windows']:
            start = next(i for i, insn in enumerate(instructions) if insn.address == int(window[0]['address'], 16))
            observed = [dict(address=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str) for i in instructions[start:start + len(window)]]
            if observed != window:
                raise ValueError('nested actual receiver/returned-object transfer differs')
    producer = next(r for r in PRIOR.rows('vendor-deque-operation-origins.csv') if r['address'] == '0x004213E0')
    if (producer['evidence_id'] != 'R072' or producer['family_key'] != '?push_back'
            or origins['0x004213E0']['origin'] != 'library'
            or digest(comparison.pe_bytes_at(target, 0x004213E0, int(producer['size']))) != producer['body_sha256']):
        raise ValueError('nested returned-inner typing loses its independently cold-replayed whole byte producer')
    eh = module('nested_eh', 'compiler_eh.py')
    for frame in m['retained_frames']:
        if frame not in PRIOR.rows('compiler-eh-frames.csv'):
            raise ValueError('nested EH frame loses independent R020 provenance')
        eh.verify_frame(frame, lambda a, n: comparison.pe_bytes_at(target, a, n),
                        lambda a, n: comparison.pe_bytes_at(target, a, n), {int(k, 16) for k in functions}, set())
    for filename, expected in m['headers'].items():
        if digest((ROOT / filename).read_bytes()) != expected:
            raise ValueError('nested complete actual SDK include differs')
    for verifier in m['retained_verifiers']:
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts' / verifier)], cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('nested retained full cold evidence failed: ' + verifier + ': ' + result.stderr[-1000:])
    scratch = ROOT / 'build/origin-nested-deque-size-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / 'VC7NestedDequeSizeContexts.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(object_path), *m['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or PRIOR.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('nested cold compiler/include provenance differs')
        verify_cold_object(m, object_path, comparison, record, coff, target)
    print('R150 origins OK: two complete nested deque size bodies / 34 bytes; 53 complete code controls / 2980 bytes; '
          '17 whole defining data owners / 524 bytes and five whole EH carriers / 82 bytes; '
          'complete outer parser/count/returned-inner source typing; full retained R149/R119 cold proofs; '
          '82 emitted functions and 18 whole data controls / 27 actual headers / no orphan carriers; '
          'prior owners and all extents preserved; no auxiliary/source/mapping/private ABI/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
