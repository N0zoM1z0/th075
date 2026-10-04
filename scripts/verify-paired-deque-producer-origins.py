#!/usr/bin/env python3
"""Cold-replay complete paired deque producers and independent source/callee/data context."""
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
KEYS = {'0x004215F0': 211, '0x00421EE0': 27, '0x00421F00': 29,
        '0x0042DBE0': 211, '0x0042E000': 27, '0x0042E020': 29}
CONFIDENCE = 'complete-vc7-paired-deque-producer-code-data-eh-typed-parent-provenance'
MANIFEST_SHA256 = '3657c5e0c147c4db60c81463bb648f29bf8c79d522d5be15b83563d495892017'
LAYOUT = [8, 20, 60, 20, 20, 4, 8, 8]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


BUFFER = module('paired_deque_buffer', 'verify-script-buffer-origins.py')
WEAK = module('paired_deque_weak', 'verify-jump-unwind-origins.py')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest():
    return json.loads((ROOT / 'config/paired-deque-producer-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id'] != 'R156' or m['probe'] != 'probes/VC7PairedDequeProducers.cpp'
            or m['profile'] != BUFFER.PROFILE or m['layout'] != LAYOUT
            or len(m['functions']) != 6 or {r['address']: r['size'] for r in m['functions']} != KEYS
            or any(r['decision'] != 'library' for r in m['functions'])
            or len(m['code']) != 162 or sum(r['size'] for r in m['code']) != 11016
            or len(m['state_data']) != 22 or sum(r['size'] for r in m['state_data']) != 835
            or sum(len(r['bindings']) for r in m['code'] + m['state_data']) != 436
            or len(m['emission']) != 187 or sum(r['size'] for r in m['emission']) != 11917
            or len(m['headers']) != 27 or len(m['external']) != 15 or len(m['weak']) != 2
            or len(m['retained_frames']) != 10 or len(m['retained_growth']) != 2
            or [(r['address'], r['size'], r['candidate'], r['site']) for r in m['contexts']] !=
               [('0x00420880', 2301, '0x004215F0', '0x00420CE4'),
                ('0x0042D470', 613, '0x0042DBE0', '0x0042D684')]
            or m['retained_verifiers'] != ['verify-allocation-api-origins.py', 'verify-standard-exception-origins.py']):
        raise ValueError('paired producers lose bounded full source/code/data/EH/parent provenance')
    code = {r['symbol']: r for r in m['code']}
    for r in m['functions']:
        owner = code.get(r['symbol'])
        if not owner or (owner['address'], owner['size']) != (r['address'], r['size']):
            raise ValueError('paired root is not its complete own source owner')
    roles = {'0x004215F0': ('QueueRecordObservation', 'push_back', ['0x00421BD0', '0x00421EE0', '0x00421F00']),
             '0x00421EE0': ('QueueRecordObservation', 'allocate', ['0x004228A0']),
             '0x00421F00': ('QueueRecordObservation', 'construct', ['0x004228C0']),
             '0x0042DBE0': ('FileRecordObservation', 'push_back', ['0x0042DCF0', '0x0042E000', '0x0042E020']),
             '0x0042E000': ('FileRecordObservation', 'allocate', ['0x0042E4D0']),
             '0x0042E020': ('FileRecordObservation', 'construct', ['0x0042E4F0'])}
    for root in m['functions']:
        typename, method, targets = roles[root['address']]
        row = code[root['symbol']]
        if (not root['symbol'].startswith('?' + method + '@') or ('?$' + ('deque' if method == 'push_back' else 'allocator') + '@U' + typename) not in root['symbol']
                or [f['target_address'] for f in row['bindings']] != targets
                or any(f['type'] != 'REL32' or f['addend'] for f in row['bindings'])):
            raise ValueError('paired source routes element/pointer/scalar operations through unrelated owners')
    for weak in m['weak']:
        if (weak['search_characteristics'] != 2 or weak['strong_archive_definitions']
                or weak['fallback_definition']['symbol'] not in code
                or m['symbol_targets'][weak['symbol']] != m['symbol_targets'][weak['fallback_definition']['symbol']]):
            raise ValueError('paired actual weak field loses its complete strong source fallback')
    policy = [r for r in m['external'] if r['kind'] == 'independent-authored-policy']
    if (len(policy) != 1 or policy[0]['address'] != '0x00421220' or policy[0]['size'] != 43
            or policy[0]['record']['decision'] != 'authored'):
        raise ValueError('inner policy declaration lacks independently complete authored lifetime evidence')
    for row in m['code'] + m['state_data']:
        if row['size'] != row['section']['size'] or row['source_sha256'] != row['section']['source_sha256']:
            raise ValueError('paired defining source carrier is truncated')
        definition = row['source_definition']
        if definition not in row['section']['definitions']:
            raise ValueError('paired source owner is absent from its entire defining section')
    # These complete controls exceed historical provisional parents. Preserve
    # those original ledgers; never truncate source comparison to a partial CFG.
    for address, size in [('0x00422A50', 241), ('0x00422D70', 1545)]:
        if len([r for r in m['code'] if r['address'] == address and r['size'] == size]) != 1:
            raise ValueError('paired complete copy/insert shared tails are hidden')


def check_ledger(row, function, origin, evidence_only=False):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['calling_convention'] or function['signature']
            or function['match_percent'] != '0.00'):
        raise ValueError('paired producer loses complete extent or grants source/private ABI/exact')
    if not evidence_only and (origin['origin'] != 'library' or origin['subsystem'] != 'VC7STL'
            or origin['disposition'] != 'exclude' or origin['evidence_id'] != 'R156' or origin['confidence'] != CONFIDENCE
            or function['owner'] != 'library' or function['module'] != 'VC7STL' or function['status'] != 'excluded'):
        raise ValueError('paired producer canonical complete library acceptance differs')


def source_catalog(m, definitions):
    result = {}
    def add(symbol, address):
        if symbol in result and result[symbol] != address:
            raise ValueError('paired source symbol has inconsistent independent full owners')
        result[symbol] = address
    for row in m['code'] + m['state_data']:
        for d in row['section']['definitions']:
            if d['storage'] in (2, 3) and not d['symbol'].startswith('.'):
                add(d['symbol'], int(row['address'], 16) + d['offset'])
    for r in m['external']:
        add(r['symbol'], int(r['address'], 16))
    for r in m['weak']:
        add(r['symbol'], result[r['fallback_definition']['symbol']])
    if any(result.get(s) != int(a, 16) for s, a in m['symbol_targets'].items()):
        raise ValueError('paired field cannot override full source/callee/data/weak ownership')
    return result


def preserved_snapshot(snapshot, function, origin):
    if function == snapshot['function'] and origin == snapshot['origin']:
        return True
    # R157 independently reviews only four original lower-level snapshots.
    # Its immutable manifest permits those exact transitions and no others.
    followup = module('paired_element_followup', 'verify-deque-element-origins.py')
    if followup.accepted_snapshot(snapshot, function, origin):
        return True
    # R158 reconciles two whole SDK owners and three interior source catches,
    # and records one remaining byte-equal copy ambiguity. All six exact
    # transitions retain their original immutable snapshots in that evidence.
    copy_followup = module('paired_copy_followup', 'verify-deque-copy-insert-origins.py')
    if copy_followup.accepted_snapshot(snapshot, function, origin):
        return True
    endpoint_followup = module('paired_endpoint_followup', 'verify-deque-endpoint-dispatch-origins.py')
    if endpoint_followup.accepted_snapshot(snapshot, function, origin):
        return True
    leaf_followup = module('paired_leaf_followup', 'verify-deque-leaf-origins.py')
    return leaf_followup.accepted_snapshot(snapshot, function, origin)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    m = manifest()
    verify_plan(m)
    if digest((ROOT / 'config/paired-deque-producer-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('reviewed paired producer metadata differs')
    c = module('paired_target', 'compare-coff-function.py')
    coff = module('paired_coff', 'coff_data.py')
    record = module('paired_extent', 'verify-vendor-record-origins.py')
    authored = module('paired_authored', 'verify-authored-origins.py')
    eh = module('paired_eh', 'compiler_eh.py')
    target = c.verified_target()
    if digest(target) != m['target_sha256'] or digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('paired target or natural complete observation source differs')
    functions = {r['address']: r for r in BUFFER.PRIOR.PRIOR.rows('functions.csv')}
    origins = {r['address']: r for r in BUFFER.PRIOR.PRIOR.rows('function-origins.csv')}
    for row in m['functions']:
        check_ledger(row, functions[row['address']], origins[row['address']], args.evidence_only)
    for row in m['code']:
        for snapshot in row['canonical_rows']:
            key = snapshot['function']['address']
            if key not in KEYS and not preserved_snapshot(snapshot, functions[key], origins[key]):
                raise ValueError('paired auxiliary association changes original accepted/provisional extent/origin')
    for row in m['retained_growth']:
        if (row not in BUFFER.PRIOR.PRIOR.rows('vendor-deque-growmap-origins.csv')
                or origins[row['address']]['evidence_id'] != 'R071' or origins[row['address']]['origin'] != 'library'
                or digest(c.pe_bytes_at(target, int(row['address'], 16), int(row['size']))) != row['body_sha256']):
            raise ValueError('paired growth source loses original full R071 owner')
    for row in m['external']:
        if row['kind'] == 'fs-exception-list-offset':
            if row['symbol'] != '__except_list' or row['address'] != '0x00000000':
                raise ValueError('paired absolute FS field is not ordinary target storage')
            continue
        prior = json.loads((ROOT / 'config' / row['manifest']).read_text())
        inventory = prior['state_data'] if row['kind'] == 'retained-whole-data' else prior['boundaries'] if row['kind'] == 'retained-external-snapshot' else prior['functions'] + prior.get('anchors', [])
        if row['record'] not in inventory:
            raise ValueError('paired external operation loses independently complete original evidence')
        old = row['record']; address = old.get('address', old.get('target_address'))
        expected = old.get('body_sha256', old.get('target_sha256'))
        if expected and digest(c.pe_bytes_at(target, int(address, 16), row['size'])) != expected:
            raise ValueError('paired complete runtime/policy/opaque snapshot differs')
    if origins['0x00421220']['origin'] != 'authored' or origins['0x00421220']['evidence_id'] != 'R153':
        raise ValueError('paired SDK policy declaration cannot infer an unreviewed game owner')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    for row in m['contexts']:
        a = int(row['address'], 16); actual = c.pe_bytes_at(target, a, row['size'])
        if (functions[row['address']] != row['function'] or origins[row['address']] != row['origin']
                or row['authored_record'] not in BUFFER.PRIOR.PRIOR.rows('authored-origin-evidence.csv')
                or digest(actual) != row['body_sha256']):
            raise ValueError('paired producer inherits parent origin without complete original context')
        authored.verify_body(actual, a, [r for r in BUFFER.PRIOR.PRIOR.rows('authored-origin-switches.csv') if r['address'] == row['address']],
                             lambda x, n: c.pe_bytes_at(target, x, n),
                             [r for r in BUFFER.PRIOR.PRIOR.rows('authored-origin-direct-switches.csv') if r['address'] == row['address']])
        instructions = list(decoder.disasm(actual, a)); window = row['instruction_window']
        index = next(i for i, ins in enumerate(instructions) if ins.address == int(window[0]['address'], 16))
        observed = [dict(address=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str) for i in instructions[index:index + len(window)]]
        if observed != window or not any(i['address'] == row['site'] and i['mnemonic'] == 'call' and int(i['operands'], 16) == int(row['candidate'], 16) for i in window):
            raise ValueError('paired actual receiver/value/typed parent call differs')
    for frame in m['retained_frames']:
        if frame not in BUFFER.PRIOR.PRIOR.rows('compiler-eh-frames.csv'):
            raise ValueError('paired source loses complete original frame registration')
        eh.verify_frame(frame, lambda a, n: c.pe_bytes_at(target, a, n),
                        lambda a, n: c.pe_bytes_at(target, a, n), {int(k, 16) for k in functions}, set())
    for name in m['retained_verifiers']:
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts' / name)], cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('paired independent full retained cold provenance failed: ' + name + ': ' + result.stderr[-1500:])
        print('retained ' + name + ': ' + result.stdout.splitlines()[-1], flush=True)
    scratch = ROOT / 'build/origin-paired-deque-producer-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path = Path(dirname) / 'VC7PairedDequeProducers.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *m['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or BUFFER.PRIOR.PRIOR.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('paired cold compiler/header provenance differs')
        data = path.read_bytes(); definitions = coff.parse_symbols(data, c.coff_name)[1]
        inventory = BUFFER.inventory(data, c, coff)
        if inventory != m['emission']:
            raise ValueError('paired cold ordinary code/data/EH emission has an omitted or changed carrier')
        sections = {r['section']: r for r in inventory}; catalog = source_catalog(m, definitions)
        for weak in m['weak']:
            if WEAK.read_weak_reference(data, weak['symbol'], c, coff, 0) != weak:
                raise ValueError('paired actual weak AUX/fallback metadata differs')
        for row in m['code'] + m['state_data']:
            section = sections[row['section']['section']]
            if section != row['section'] or row['source_definition'] not in definitions:
                raise ValueError('paired full defining source owner/fields/primary definition differs')
            head = struct.unpack_from('<8sIIIIIIHHI', data, 20 + (section['section'] - 1) * 40)
            source = data[head[4]:head[4] + head[3]]
            fields = [dict(offset=f['offset'], type=f['type'], symbol=f['symbol']['symbol'], addend=f['addend']) for f in section['fields']]
            actual = c.pe_bytes_at(target, int(row['address'], 16), row['size'])
            if (digest(actual) != row['body_sha256'] or digest(source) != row['source_sha256']
                    or BUFFER.PRIOR.link_complete(source, fields, int(row['address'], 16), row['bindings'], catalog) != actual):
                raise ValueError('paired entire defining code/data/EH owner fails actual unmasked field comparison')
            if row in m['code']:
                instructions = [dict(address=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str) for i in decoder.disasm(actual, int(row['address'], 16))]
                if instructions != row['instructions']:
                    raise ValueError('paired complete branch/shared-tail/return inventory differs')
        for row in m['functions']:
            size = record.complete_aux_section_size(data, row['symbol'], c.coff_name)
            source, _ = c.object_function(path, row['symbol'])
            if size != row['size'] or len(source) != size:
                raise ValueError('paired accepted root lacks its complete positive own AUX extent')
        layout = next(r for r in inventory if any(d['symbol'] == '_PairedDequeLayout' for d in r['definitions']))
        source, _ = coff.readonly_section(data, layout['section'], c.coff_name)
        if list(struct.unpack('<8I', source)) != LAYOUT:
            raise ValueError('paired full actual SDK/observation layout differs')
    print('R156 origins OK: six complete library producer/allocator owners / 534 bytes; 162 whole linked code/EH carriers / 11016 bytes, 22 whole data owners / 835 bytes and 436 actual unmasked fields; all 187 ordinary cold emission sections / 11917 bytes, 27 actual headers and full 32-byte layout; two unchanged whole growth owners, two complete original game parents and ten original full registered frames; independently authored inner destruction and complete runtime/weak/opaque boundaries; unrelated auxiliary/shared-tail classifications preserved, with only exact hash-pinned independently reviewed R157/R158/R159/R160 follow-up snapshots permitted; original game types and runtime outcomes unknown; no source/mapping/private ABI/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, StopIteration, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
