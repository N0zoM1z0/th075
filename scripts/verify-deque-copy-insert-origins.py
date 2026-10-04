#!/usr/bin/env python3
"""Cold-replay whole deque copy/insertion, interior source catches and copy ambiguity."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_SHA256 = '52f3cdecfb551119616e920bbce11dd7bf795724b4bd0862046dbb5ebf8e5d81'
CONFIDENCE = 'complete-vc7-deque-copy-insert-full-source-catch-policy-and-extent-provenance'
KEYS = {'0x004229D0': ('pending', '0x004229D0', 28, 28),
        '0x00422A50': ('library', '0x00422A50', 195, 241),
        '0x00422B13': ('library-interior', '0x00422A50', 46, 46),
        '0x00422D70': ('library', '0x00422D70', 1483, 1545),
        '0x0042308D': ('library-interior', '0x00422D70', 48, 48),
        '0x0042333B': ('library-interior', '0x00422D70', 62, 62)}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


ELEMENT = module('copy_element', 'verify-deque-element-origins.py')
PAIRED = ELEMENT.PAIRED


def manifest():
    return json.loads((ROOT / 'config/deque-copy-insert-origin-evidence.json').read_text())


def verify_plan(m):
    prior = PAIRED.manifest(); PAIRED.verify_plan(prior)
    if (m['evidence_id'] != 'R158' or m['target_sha256'] != prior['target_sha256']
            or m['retained_manifest'] != 'config/paired-deque-producer-origin-evidence.json'
            or m['retained_sha256'] != PAIRED.MANIFEST_SHA256
            or m['element_manifest'] != 'config/deque-element-origin-evidence.json'
            or m['element_sha256'] != ELEMENT.MANIFEST_SHA256
            or m['probe'] != 'probes/VC7DequeCopyAlternatives.cpp' or m['profile'] != prior['profile']
            or m['headers'] != dict(prior['headers'], **{prior['probe']: prior['probe_sha256']})
            or len(m['functions']) != 6 or {r['address'] for r in m['functions']} != set(KEYS)
            or len(m['controls']) != 14 or sum(r['size'] for r in m['controls']) != 2416
            or sum(len(r['bindings']) for r in m['controls']) != 104
            or len(m['emission']) != 194 or sum(r['size'] for r in m['emission']) != 12303
            or m['layout_values'] != [8, 20, 60, 20, 20, 4, 8, 8, 20, 20, 20, 8]
            or m['layout'] not in m['emission'] or m['layout']['size'] != 48
            or len(m['frames']) != 2 or any(r not in prior['retained_frames'] for r in m['frames'])
            or [(r['frame_handler'], r['try_index'], r['low'], r['high'], r['catch_high'], r['entry']) for r in m['catches']] !=
               [('0x006556B0', 0, 0, 0, 1, '0x00422B13'), ('0x006556C0', 0, 0, 0, 1, '0x0042308D'), ('0x006556C0', 1, 2, 2, 3, '0x0042333B')]
            or any(r['adjectives'] or r['type_address'] != '0x00000000' or r['displacement'] for r in m['catches'])):
        raise ValueError('copy/insertion loses complete source/ordinary/state/catch provenance')
    if ([(r['owner'], r['site'], r['target']) for r in m['shared_returns']] !=
            [('0x00422A50', '0x00422B11', '0x00422B24'), ('0x00422D70', '0x004230B8', '0x0042335F'), ('0x00422D70', '0x00423339', '0x0042335F')]
            or [(r['address'], r['size'], r['next_address']) for r in m['alignment']] !=
               [('0x00422B41', 15, '0x00422B50'), ('0x00423379', 7, '0x00423380')]
            or [r['address'] for r in m['parents']] != ['0x004228C0', '0x00422CB0']):
        raise ValueError('copy/insertion hides shared returns, adjacent alignment or actual parents')
    source = {r['symbol']: r for r in prior['code'] + prior['state_data']}
    for row in m['functions']:
        decision, owner, old_size, size = KEYS[row['address']]
        original = source.get(row['owner_symbol'])
        if (row['decision'] != decision or row['owner_address'] != owner or row['size'] != size
                or row['source_offset'] != int(row['address'], 16) - int(owner, 16)
                or original is None or original['address'] != owner
                or row['source_offset'] + size > original['size']):
            raise ValueError('copy/insertion entry is not its complete source owner or true interior span')
        old, accepted = row['original_function'], row['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if decision == 'library':
            mutable |= {'size', 'span_end'}
        if (old['address'] != row['address'] or int(old['size']) != old_size or old['status'] != 'unclassified'
                or row['original_origin']['origin'] != 'unknown' or row['original_origin']['disposition'] != 'review'
                or {k: v for k, v in old.items() if k not in mutable} != {k: v for k, v in accepted.items() if k not in mutable}
                or int(accepted['size']) != size or accepted['span_end'] != f'0x{int(row["address"], 16) + size - 1:08X}'
                or accepted['source_file'] or accepted['calling_convention'] or accepted['signature'] or accepted['match_percent'] != '0.00'):
            raise ValueError('copy/insertion transition changes unrelated extent/source/private ABI/exact')
        if decision == 'pending':
            if (row['accepted_origin'] != row['original_origin'] or accepted['proposed_name'] or accepted['owner']
                    or accepted['module'] or accepted['status'] != 'unclassified'):
                raise ValueError('byte-equal implicit/explicit copy ambiguity gains false ownership')
        elif (row['accepted_origin'] != dict(address=row['address'], origin='library', subsystem='VC7STL', disposition='exclude', confidence=CONFIDENCE, evidence_id='R158')
                or accepted['owner'] != 'library' or accepted['module'] != 'VC7STL' or accepted['status'] != 'excluded'):
            raise ValueError('copy/insertion source policy is mislabeled as unrelated compiler/game ownership')
    expected_roles = ['implicit-record-copy', 'whole-sdk-copy', 'whole-sdk-insert', 'sdk-copy-dispatch', 'sdk-insert-dispatch',
                      'sdk-copy-state', 'sdk-insert-state', 'explicit-record-copy', 'CopyImplicitQueueRecord',
                      'CopyImplicitQueueRecord-eh', 'CopyImplicitQueueRecord-state', 'CopyExplicitQueueRecord',
                      'CopyExplicitQueueRecord-eh', 'CopyExplicitQueueRecord-state']
    if [r['role'] for r in m['controls']] != expected_roles:
        raise ValueError('copy/insertion omits complete implicit/explicit/SDK/exception controls')
    for control in m['controls']:
        old = source.get(control['retained_symbol'])
        if (old is None or any(control[k] != old[k] for k in ('address', 'size', 'body_sha256', 'source_sha256'))
                or control['section'] not in m['emission'] or control['source_definition'] not in control['section']['definitions']
                or control['size'] != control['section']['size'] or control['source_sha256'] != control['section']['source_sha256']
                or [(r['offset'], r['type'], r['addend'], r['target_address']) for r in control['bindings']] !=
                   [(r['offset'], r['type'], r['addend'], r['target_address']) for r in old['bindings']]):
            raise ValueError('copy/insertion loses a whole independent defining owner or genuine field')
        for new, original in zip(control['section']['fields'], old['section']['fields']):
            a, b = new['symbol'], original['symbol']
            explicit = (control['role'] == 'CopyExplicitQueueRecord' and a['symbol'] == '??0ExplicitQueueRecordObservation@@QAE@ABU0@@Z'
                        and b['symbol'] == '??0QueueRecordObservation@@QAE@ABU0@@Z' and a['type'] == b['type'] == 32)
            if a['offset'] != b['offset'] or a['storage'] != b['storage'] or a['type'] != b['type'] and not explicit:
                raise ValueError('copy/insertion actual source field owner role differs')
            if a['symbol'] != b['symbol'] and not (explicit or a['symbol'].startswith('$') and b['symbol'].startswith('$') or
                    a['symbol'].startswith('__ehhandler$?Copy') and b['symbol'].startswith('__ehhandler$??$_Construct@UQueueRecordObservation@@')):
                raise ValueError('copy/insertion routes a field to an unrelated source operation')
    if (m['controls'][0]['source_definition']['symbol'] != '??0QueueRecordObservation@@QAE@ABU0@@Z'
            or m['controls'][7]['source_definition']['symbol'] != '??0ExplicitQueueRecordObservation@@QAE@ABU0@@Z'
            or m['controls'][7]['source_definition']['type'] != 32):
        raise ValueError('implicit/explicit record copy controls lose their independent declarations')


def accepted_snapshot(snapshot, function, origin):
    m = manifest()
    if PAIRED.digest((ROOT / 'config/deque-copy-insert-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('copy/insertion follow-up evidence differs')
    verify_plan(m)
    row = next((r for r in m['functions'] if r['address'] == function['address']), None)
    return bool(row and snapshot == dict(function=row['original_function'], origin=row['original_origin'])
                and function == row['accepted_function'] and origin == row['accepted_origin'])


def check_ledger(row, function, origin, evidence_only=False):
    if evidence_only and function == row['original_function'] and origin == row['original_origin']:
        return
    if function != row['accepted_function'] or origin != row['accepted_origin']:
        raise ValueError('copy/insertion canonical full source/interior/pending acceptance differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = manifest(); verify_plan(m)
    for path, expected in [('config/deque-copy-insert-origin-evidence.json', MANIFEST_SHA256),
                           (m['retained_manifest'], m['retained_sha256']), (m['element_manifest'], m['element_sha256']), (m['probe'], m['probe_sha256'])]:
        if PAIRED.digest((ROOT / path).read_bytes()) != expected:
            raise ValueError('copy/insertion immutable source/evidence differs: ' + path)
    c = module('copy_target', 'compare-coff-function.py'); coff = module('copy_coff', 'coff_data.py')
    extent = module('copy_extent', 'verify-vendor-record-origins.py'); eh = module('copy_eh', 'compiler_eh.py')
    cfg = module('copy_cfg', 'verify-authored-origins.py'); target = c.verified_target()
    if PAIRED.digest(target) != m['target_sha256']:
        raise ValueError('copy/insertion target differs')
    functions = {r['address']: r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('functions.csv')}
    origins = {r['address']: r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('function-origins.csv')}
    for row in m['functions']:
        check_ledger(row, functions[row['address']], origins[row['address']], args.evidence_only)
    for parent in m['parents']:
        if not PAIRED.preserved_snapshot(dict(function=parent['function'], origin=parent['origin']), functions[parent['address']], origins[parent['address']]):
            raise ValueError('copy/insertion changes its independent original parent evidence')
    for alignment in m['alignment']:
        actual = c.pe_bytes_at(target, int(alignment['address'], 16), alignment['size'])
        if (PAIRED.digest(actual) != alignment['sha256'] or any(b != 0xCC for b in actual)
                or not PAIRED.preserved_snapshot(dict(function=alignment['next_function'], origin=alignment['next_origin']), functions[alignment['next_address']], origins[alignment['next_address']])):
            raise ValueError('copy/insertion includes alignment or changes unrelated adjacent owners')
    for frame in m['frames']:
        if frame not in PAIRED.BUFFER.PRIOR.PRIOR.rows('compiler-eh-frames.csv'):
            raise ValueError('copy/insertion original registered frame differs')
        eh.verify_frame(frame, lambda a, n: c.pe_bytes_at(target, a, n), lambda a, n: c.pe_bytes_at(target, a, n), {int(k, 16) for k in functions})
    for catch in m['catches']:
        frame = next(r for r in m['frames'] if r['handler_address'] == catch['frame_handler'])
        low, high, last, count, handlers = struct.unpack('<5I', c.pe_bytes_at(target, int(frame['trymap_address'], 16) + 20 * catch['try_index'], 20))
        raw = c.pe_bytes_at(target, handlers, count * 16)
        if (count != 1 or handlers != int(catch['handler_address'], 16) or (low, high, last) != (catch['low'], catch['high'], catch['catch_high'])
                or PAIRED.digest(raw) != catch['handler_sha256'] or struct.unpack('<4I', raw) !=
                   (catch['adjectives'], int(catch['type_address'], 16), catch['displacement'], int(catch['entry'], 16))):
            raise ValueError('copy/insertion interior entry lacks its actual full registered catch state')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-deque-element-origins.py')], cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('copy/insertion complete independent retained cold evidence failed: ' + result.stderr[-1500:])
    print('retained element: ' + result.stdout.splitlines()[-1], flush=True)
    prior = PAIRED.manifest(); catalog = {k: v for k, v in PAIRED.source_catalog(prior, []).items() if not k.startswith('$')}
    scratch = ROOT / 'build/origin-deque-copy-insert-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path = Path(dirname) / 'VC7DequeCopyAlternatives.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *m['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or ELEMENT.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('copy/insertion actual cold source/header ownership differs')
        data = path.read_bytes(); inventory = PAIRED.BUFFER.inventory(data, c, coff)
        if inventory != m['emission']:
            raise ValueError('copy/insertion entire ordinary emission differs or loses a carrier')
        sections = {r['section']: r for r in inventory}
        for control in m['controls']:
            for definition in control['section']['definitions']:
                if definition['storage'] in (2, 3) and not definition['symbol'].startswith('.'):
                    address = int(control['address'], 16) + definition['offset']
                    if definition['symbol'] in catalog and catalog[definition['symbol']] != address:
                        raise ValueError('copy/insertion source definition overrides independent full ownership')
                    catalog[definition['symbol']] = address
        complete = {}
        for control in m['controls']:
            section = sections[control['section']['section']]
            if section != control['section']:
                raise ValueError('copy/insertion full defining owner differs')
            head = struct.unpack_from('<8sIIIIIIHHI', data, 20 + (section['section'] - 1) * 40); raw = data[head[4]:head[4] + head[3]]
            fields = [dict(offset=r['offset'], type=r['type'], symbol=r['symbol']['symbol'], addend=r['addend']) for r in section['fields']]
            actual = c.pe_bytes_at(target, int(control['address'], 16), control['size'])
            if (PAIRED.digest(raw) != control['source_sha256'] or PAIRED.digest(actual) != control['body_sha256']
                    or PAIRED.BUFFER.PRIOR.link_complete(raw, fields, int(control['address'], 16), control['bindings'], catalog) != actual):
                raise ValueError('copy/insertion entire code/data/EH or source alternative fails unmasked comparison')
            if control['role'].startswith('whole-sdk-'):
                if extent.complete_aux_section_size(data, control['source_definition']['symbol'], c.coff_name) != control['size']:
                    raise ValueError('SDK copy/insertion owner lacks its entire positive own AUX')
                cfg.verify_body(actual, int(control['address'], 16))
                complete[control['address']] = actual
            if control['role'] == 'explicit-record-copy' and extent.complete_aux_section_size(data, control['source_definition']['symbol'], c.coff_name) != 28:
                raise ValueError('ordinary explicit constructor loses its whole positive own AUX')
        for row in m['functions']:
            if row['decision'] == 'library-interior':
                fragment = complete[row['owner_address']][row['source_offset']:row['source_offset'] + row['size']]
                if PAIRED.digest(fragment) != row['body_sha256']:
                    raise ValueError('catch evidence is not inside the entire compared SDK parent')
        decoder = Cs(CS_ARCH_X86, CS_MODE_32)
        for branch in m['shared_returns']:
            ins = next(i for i in decoder.disasm(complete[branch['owner']], int(branch['owner'], 16)) if i.address == int(branch['site'], 16))
            if ins.mnemonic != 'jmp' or int(ins.op_str, 16) != int(branch['target'], 16):
                raise ValueError('SDK normal path no longer reaches its reconciled shared return')
        raw, _ = coff.readonly_section(data, m['layout']['section'], c.coff_name)
        if list(struct.unpack('<12I', raw)) != m['layout_values']:
            raise ValueError('copy/insertion whole real SDK/observation layout differs')
    print('R158 origins OK: two complete SDK library owners / 1786 distinct bytes with reconciled 241-/1545-byte extents; three registered interior library source-policy candidates overlap those owners and are not standalone functions; one entire 28-byte record-copy owner remains unknown after byte-equal implicit/explicit controls; fourteen whole code/data/EH controls / 2416 bytes and 104 unmasked fields; all 194 cold ordinary sections / 12303 bytes, actual headers and full 48-byte layout; original full SDK/runtime/authored-policy evidence, shared normal returns and observed alignment preserved; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, StopIteration, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
