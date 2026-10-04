#!/usr/bin/env python3
"""Cold-check complete VC7 size families against independent whole receiver contexts."""
from __future__ import annotations
import argparse
import csv
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
KEYS = {'0x004094B0', '0x00414430', '0x00414620', '0x00414810', '0x0041DD50', '0x0045BF50'}
PENDING = {'0x00421550', '0x0045DD50'}
PROFILE = ['/Od', '/Ob0', '/Gy', '/GR-', '/GX', '/Zi', '/GS', '/I', 'src', '/showIncludes']
CONFIDENCE = 'complete-vc7-size-family-shared-receiver-context'
MANIFEST_SHA256 = 'a65f343268cfc960130c420b2b9cc3061986f4ad2db1ecd23a23285a47a24c3b'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def digest(data):
    return hashlib.sha256(data).hexdigest()


def rows(filename):
    with (ROOT / 'config' / filename).open(newline='') as stream:
        return list(csv.DictReader(stream))


def receiver(window):
    """Prove an actual receiver-producing sequence, not a guessed member type."""
    operations = [(r['mnemonic'], r['operands']) for r in window]
    if len(operations) == 2 and operations[0][0] == 'mov' and operations[0][1].startswith('ecx, 0x'):
        value = int(operations[0][1].split(', ')[1], 16)
        result = ('global', value)
    elif operations[:-1] == [('mov', 'ecx, dword ptr [ebp - 4]'), ('imul', 'ecx, ecx, 0x14'),
                             ('mov', 'edx, dword ptr [ebp - 0x34]'), ('lea', 'ecx, [edx + ecx + 4]')]:
        result = ('indexed-local', -52, -4, 20, 4)
    elif operations[:-1] == [('mov', 'eax, dword ptr [ebp - 4]'), ('imul', 'eax, eax, 0x14'),
                             ('mov', 'ecx, dword ptr [ebp - 0x34]'), ('lea', 'ecx, [ecx + eax + 4]')]:
        result = ('indexed-local', -52, -4, 20, 4)
    else:
        raise ValueError('size context lacks its complete receiver-producing sequence')
    if operations[-1][0] != 'call' or not operations[-1][1].startswith('0x'):
        raise ValueError('receiver witness loses its direct complete call')
    return result


def verify_plan(m):
    functions = {r['address']: r for r in m['functions']}
    if (m['evidence_id'] != 'R149' or m['profile'] != PROFILE
            or m['probe'] != 'probes/VC7DequeSizeContexts.cpp'
            or len(functions) != 6 or len(m['functions']) != 6 or set(functions) != KEYS
            or {r['address'] for r in m['pending']} != PENDING or len(m['pending']) != 2
            or len(m['contexts']) != 6 or sum(r['size'] for r in m['contexts']) != 5610
            or len(m['anchors']) != 6 or len(m['controls']) != 26
            or sum(r['size'] for r in m['controls']) != 390 or len(m['headers']) != 27):
        raise ValueError('bounded size-family/context inventory differs')
    families = sorted(r['coff_symbol'] for r in m['controls'] if r['coff_symbol'].startswith('?size@?$deque@'))
    if len(families) != 13 or any(r['size'] != 17 or r['relocations'] for r in m['controls'] if r['coff_symbol'] in families):
        raise ValueError('complete no-field size source family differs')
    for r in m['functions']:
        if (r['size'] != 17 or r['decision'] != 'library' or r['shape_symbols'] != families
                or r['coff_symbol'] not in families or int(r['span_end'], 16) != int(r['address'], 16) + 16):
            raise ValueError('size decision loses full extent or original-type uncertainty')
    anchors = {r['address']: r for r in m['anchors']}
    for context in m['contexts']:
        r = functions[context['candidate']]
        if (context['origin'] != 'authored' or r['parent'] != context['address']
                or r['anchor'] != context['anchor'] or context['anchor'] not in anchors
                or anchors[context['anchor']]['origin'] != 'library'):
            raise ValueError('size lacks an independent whole game/library context')
        windows = context['instruction_windows']
        if len(windows) != 2 or receiver(windows[0]) != receiver(windows[1]):
            raise ValueError('size and independent library operation use different receivers')
        for window, site, destination in zip(windows, [context['candidate_site'], context['anchor_site']],
                                              [context['candidate'], context['anchor']]):
            if (window[-1]['address'] != site or int(window[-1]['operands'], 16) != int(destination, 16)):
                raise ValueError('size receiver witness changes the actual typed call')
    layout = m['sdk_layout']
    if layout['size'] != 32 or layout['values'] != [20, 20, 20, 20, 20, 8, 8, 4]:
        raise ValueError('actual complete SDK container/iterator layout differs')
    if any(r['decision'] != 'pending' or r['size'] != 17 for r in m['pending']):
        raise ValueError('nested diagnostics gain unsupported ownership')
    if m['retained_verifiers'] != ['verify-vendor-deque-operation-origins.py', 'verify-vendor-deque-access-origins.py',
                                  'verify-deque-game-dependency-origins.py', 'verify-event-queue-origins.py']:
        raise ValueError('size loses independent complete retained cold provenance')


def check_ledger(r, function, origin, evidence_only=False):
    if (int(function['size']) != 17 or function['span_end'] != r['span_end']
            or function['source_file'] or function['calling_convention'] or function['signature']
            or function['match_percent'] != '0.00'):
        raise ValueError('size origin grants source/private ABI/exact or loses extent')
    if not evidence_only and (origin['origin'] != 'library' or origin['disposition'] != 'exclude'
            or origin['evidence_id'] != 'R149' or origin['subsystem'] != 'VC7STL'
            or origin['confidence'] != CONFIDENCE or function['module'] != 'VC7STL'
            or function['owner'] != 'library' or function['status'] != 'excluded'
            or function['proposed_name'] != 'VC7::deque_Size_' + r['address'][2:]):
        raise ValueError('canonical complete size-family acceptance differs')


def included_headers(output):
    found = {}
    for line in output.splitlines():
        if 'Note: including file:' not in line:
            continue
        text = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
        if not text.startswith('Z:/'):
            raise ValueError('cold compiler include lacks its actual host mapping')
        path = Path(text[2:])
        relative = path.relative_to(ROOT)
        if not str(relative).startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('size source gains an unreviewed include owner')
        found[str(relative)] = digest(path.read_bytes())
    return found


def verify_controls(m, object_path, comparison, record, coff, target):
    data = object_path.read_bytes()
    definitions = coff.parse_symbols(data, comparison.coff_name)[1]
    actual_functions = [r for r in definitions if r['section'] > 0 and r['type'] == 32 and r['storage'] == 2]
    if actual_functions != [r['source_definition'] for r in m['controls']]:
        raise ValueError('cold size model gains or loses a complete emitted source function')
    sources = {}
    for r in m['controls']:
        size = record.complete_aux_section_size(data, r['coff_symbol'], comparison.coff_name)
        source, relocations = comparison.object_function(object_path, r['coff_symbol'], size)
        if size != r['size'] or digest(source) != r['source_sha256'] or relocations != r['relocations']:
            raise ValueError('complete cold size control/AUX/fields differ')
        sources[r['coff_symbol']] = source
    for r in m['functions']:
        actual = comparison.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if digest(actual) != r['body_sha256'] or any(sources[symbol] != actual for symbol in r['shape_symbols']):
            raise ValueError('complete unmasked thirteen-member size family differs')
    for r in m['controls']:
        if r['coff_symbol'].startswith('?SizeControl'):
            if (len(r['relocations']) != 1 or r['relocations'][0]['type'] != 'REL32'
                    or r['relocations'][0]['addend'] or r['relocations'][0]['symbol'] not in sources
                    or not r['relocations'][0]['symbol'].startswith('?size@?$deque@')):
                raise ValueError('natural public const-receiver control loses its typed size callee')
    layout = m['sdk_layout']
    definition = next(r for r in definitions if r['symbol'] == layout['symbol'])
    raw, section = coff.readonly_section(data, definition['section'], comparison.coff_name)
    if (definition != layout['source_definition'] or section != layout['source_section']
            or digest(raw) != layout['source_sha256'] or list(struct.unpack('<8I', raw)) != layout['values']):
        raise ValueError('cold SDK proof loses its whole actual defining data section')
    # All ordinary emitted code/data carriers are accounted for; debug/link records are metadata.
    covered = {r['source_definition']['section'] for r in m['controls']} | {definition['section']}
    count = struct.unpack_from('<H', data, 2)[0]
    for index in range(count):
        header = struct.unpack_from('<8sIIIIIIHHI', data, 20 + index * 40)
        name = header[0].rstrip(b'\0').decode('ascii')
        if header[3] and header[9] & 0xE0 and not name.startswith('.debug') and index + 1 not in covered:
            raise ValueError('cold size model has an uncovered code/data carrier')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    path = ROOT / 'config/deque-size-context-origin-evidence.json'
    raw = path.read_bytes()
    m = json.loads(raw)
    verify_plan(m)
    if digest(raw) != MANIFEST_SHA256:
        raise ValueError('reviewed complete size/context metadata differs')
    comparison = module('size_target', 'compare-coff-function.py')
    record = module('size_record', 'verify-vendor-record-origins.py')
    authored = module('size_authored', 'verify-authored-origins.py')
    coff = module('size_coff', 'coff_data.py')
    target = comparison.verified_target()
    if digest(target) != m['target_sha256'] or digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('size target or natural probe identity differs')
    for filename, expected in m['headers'].items():
        if digest((ROOT / filename).read_bytes()) != expected:
            raise ValueError('complete actual SDK dependency differs')
    functions = {r['address']: r for r in rows('functions.csv')}
    origins = {r['address']: r for r in rows('function-origins.csv')}
    for r in m['functions']:
        check_ledger(r, functions[r['address']], origins[r['address']], args.evidence_only)
    for r in m['anchors']:
        previous = next(row for row in rows(r['manifest']) if row['address'] == r['address'])
        origin = origins[r['address']]
        if previous != r['record'] or origin['origin'] != 'library' or origin['evidence_id'] != r['origin_evidence']:
            raise ValueError('size changes an independently retained library owner')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    remaps, directs = rows('authored-origin-switches.csv'), rows('authored-origin-direct-switches.csv')
    for r in m['contexts']:
        key, address = r['address'], int(r['address'], 16)
        f, o = functions[key], origins[key]
        if (int(f['size']) != r['size'] or f['span_end'] != r['span_end']
                or o['origin'] != r['origin'] or o['evidence_id'] != r['origin_evidence']):
            raise ValueError('size loses its independent complete game parent')
        actual = comparison.pe_bytes_at(target, address, r['size'])
        if digest(actual) != r['body_sha256']:
            raise ValueError('whole size receiver context differs')
        authored.verify_body(actual, address, [row for row in remaps if row['address'] == key],
                             lambda a, n: comparison.pe_bytes_at(target, a, n),
                             [row for row in directs if row['address'] == key])
        instructions = list(decoder.disasm(actual, address))
        for window in r['instruction_windows']:
            start = next(i for i, insn in enumerate(instructions) if insn.address == int(window[0]['address'], 16))
            observed = [dict(address=f'0x{insn.address:08X}', mnemonic=insn.mnemonic, operands=insn.op_str)
                        for insn in instructions[start:start + len(window)]]
            if observed != window:
                raise ValueError('actual complete receiver/call instruction sequence differs')
    for r in m['pending']:
        if (digest(comparison.pe_bytes_at(target, int(r['address'], 16), r['size'])) != r['body_sha256']
                or origins[r['address']]['evidence_id'] == 'R149'):
            raise ValueError('nested diagnostic gains unsupported R149 origin credit')
    # Independent complete source/context proofs are replayed serially before new acceptance.
    for verifier in m['retained_verifiers']:
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts' / verifier)],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('retained complete size provenance failed: ' + verifier + ': ' + result.stderr[-1000:])
    scratch = ROOT / 'build/origin-deque-size-context-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / 'VC7DequeSizeContexts.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']),
                                 str(object_path), *PROFILE], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('cold actual size SDK source/include set differs')
        verify_controls(m, object_path, comparison, record, coff, target)
    print('R149 origins OK: six complete library size bodies / 102 bytes; thirteen whole size source alternatives; '
          'six independently typed shared-receiver contexts / 5610 bytes and six complete retained library owners; '
          '26 cold natural controls / 390 bytes, complete 32-byte SDK layout / 27 actual headers / every code/data carrier; '
          'full retained R072/R078/R110/R113 cold proofs; both nested candidates remain pending; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
