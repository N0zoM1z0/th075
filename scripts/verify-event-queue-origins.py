#!/usr/bin/env python3
"""Cold-check R113 event-queue dependencies and the complete game main loop."""
from __future__ import annotations
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
PROFILE = ['/Od', '/Ob0', '/Gy', '/GR-', '/GX', '/Zi', '/GS', '/I', 'src']
LIBRARY = {'0x00423F50': '??0iterator', '0x00424500': '??0const_iterator',
           '0x00423D40': '?size', '0x00423DB0': '??A?$deque', '0x00423DF0': '?front'}
GAME = {'0x00423C80': 'EventQueue::EnqueueUniqueAt00423C80',
        '0x00602A60': 'GameApplication::RunAt00602A60'}
ROOTS = set(LIBRARY) | {'0x00423C80'}
GLOBAL = '0x0068BE44'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def verify_graph(manifest):
    nodes, boundaries = manifest['nodes'], manifest['boundaries']
    by_address = {r['address']: r for r in nodes + boundaries}
    if (len(nodes) != 65 or len(boundaries) != 9 or len(by_address) != 74
            or sum(r['size'] for r in nodes) != 4002
            or sum(r['size'] for r in boundaries) != 2019
            or sum(len(r['relocation_bindings']) for r in nodes) != 150
            or Counter(r['evidence_role'] for r in nodes) != {'accepted_library': 5, 'accepted_game': 1, 'anchor': 59}
            or {r['address'] for r in nodes if r['evidence_role'] == 'accepted_library'} != set(LIBRARY)
            or {r['address'] for r in nodes if r['evidence_role'] == 'accepted_game'} != {'0x00423C80'}):
        raise ValueError('R113 complete source graph differs')
    edges = {}
    for row in nodes:
        edges[row['address']] = []
        if row['evidence_role'] == 'anchor' and row['origin'] != 'library':
            raise ValueError('source graph anchor loses its independent library ownership')
        for call in row['relocation_bindings']:
            if call['type'] == 'REL32':
                callee = by_address.get(call['target_address'])
                if callee is None or callee['coff_symbol'] != call['symbol'] or call['addend']:
                    raise ValueError('queue dependency lacks its source-typed whole callee or boundary')
                edges[row['address']].append(callee['address'])
        if row['address'] in LIBRARY:
            symbols = row['shape_symbols']
            if (len(symbols) != 13 or symbols != sorted(set(symbols)) or row['coff_symbol'] not in symbols
                    or any(s.split('@', 1)[0] != LIBRARY[row['address']] for s in symbols)):
                raise ValueError('queue helper source family differs')
            if row['address'] in ('0x00423F50', '0x00424500') and not row['coff_symbol'].endswith('QAE@XZ'):
                raise ValueError('default iterator constructor changes overload')
    required = {'0x00423F50': [(11, '0x00424500')],
                '0x00423DB0': [(25, '0x00423CE0'), (32, '0x004244C0'), (39, '0x00423F70')],
                '0x00423DF0': [(17, '0x00423CE0'), (24, '0x00423F70')],
                '0x00423C80': [(34, '0x00423D40'), (53, '0x00423D60'), (88, '0x00423E10')]}
    for key, calls in required.items():
        if [(b['offset'], b['target_address']) for b in by_address[key]['relocation_bindings'] if b['type'] == 'REL32'] != calls:
            raise ValueError('queue helper or policy changes its actual typed calls')
    global_fields = [b for b in by_address['0x00423C80']['relocation_bindings'] if b['type'] == 'DIR32']
    if ([(b['offset'], b['target_address']) for b in global_fields] != [(29, GLOBAL), (48, GLOBAL), (83, GLOBAL)]
            or len({b['symbol'] for b in global_fields}) != 1 or any(b['addend'] for b in global_fields)):
        raise ValueError('queue policy loses the independently observed worker global')
    visited, pending = set(), list(ROOTS)
    while pending:
        key = pending.pop()
        if key in visited:
            continue
        visited.add(key)
        pending.extend(edges.get(key, []))
    if visited != set(by_address):
        raise ValueError('queue dependency is not rooted in the typed source policies')
    contexts = manifest['contexts']
    if (len(contexts) != 9 or len({r['address'] for r in contexts}) != 9
            or sum(r['size'] for r in contexts) != 5063
            or sum(len(r['instruction_witnesses']) for r in contexts) != 234
            or {r['address']: r['role'] for r in contexts if r['accepted']} != GAME):
        raise ValueError('R113 complete game ownership contexts differ')
    anchors = {r['address']: r for r in contexts}
    if (anchors['0x00423B40']['origin'] != 'authored' or anchors['0x00423B40']['origin_evidence'] != 'R112'
            or any(anchors[k]['origin'] != 'authored' for k in ('0x00417210', '0x00431F60', '0x00425490'))):
        raise ValueError('queue/main policy lacks independent game ownership')
    if {'site': '0x00602D02', 'target': '0x00423C80'} not in anchors['0x00602A60']['body_facts']['direct_calls']:
        raise ValueError('game main loop loses its actual enqueue call')
    # Both local default iterators are used in the independently reviewed worker.
    defaults = [c['site'] for c in anchors['0x00423B40']['body_facts']['direct_calls'] if c['target'] == '0x00423F50']
    if defaults != ['0x00423B5E', '0x00423B66']:
        raise ValueError('default constructors lack the independent iterator-use context')


def check_ledger(row, functions, origins, evidence_only, kind):
    key, size = row['address'], row['size']
    function, origin = functions[key], origins[key]
    address = int(key, 16)
    if (int(function['size']) != size or function['span_end'] != row['span_end']
            or int(row['span_end'], 16) != address + size - 1
            or sorted(k for k in functions if address < int(k, 16) < address + size)
            != row.get('retained_interior_candidates', [])):
        raise ValueError('R113 complete ledger extent differs: ' + key)
    if kind in ('library', 'authored'):
        if row.get('retained_interior_candidates'):
            raise ValueError('new queue acceptance retains an unresolved interior candidate')
        if function['source_file'] or function['match_percent'] != '0.00':
            raise ValueError('origin probe cannot grant source or exact credit')
        if not evidence_only and (origin['origin'] != kind or origin['evidence_id'] != 'R113'
                or origin['disposition'] != ('exclude' if kind == 'library' else 'authored')
                or function['owner'] != kind or function['status'] != ('excluded' if kind == 'library' else 'unclassified')):
            raise ValueError('R113 acceptance ledger differs')
    elif row['origin'] != 'unknown' and (origin['origin'] != row['origin']
            or origin['evidence_id'] != row['origin_evidence'] or function['owner'] != row['origin']):
        raise ValueError('independently reviewed boundary/context ownership differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    comparison = module('queue_target', 'compare-coff-function.py')
    record = module('queue_comdat', 'verify-vendor-record-origins.py')
    sdk = module('queue_cfg', 'verify-sdk-origins.py')
    authored = module('queue_authored', 'verify-authored-origins.py')
    lifetime = module('queue_facts', 'verify-game-lifetime-origins.py')
    imports_module = module('queue_imports', 'verify-import-origins.py')
    coff = module('queue_symbols', 'coff_data.py')
    target = comparison.verified_target()
    manifest = json.loads((ROOT / 'config/event-queue-origin-evidence.json').read_text())
    if (manifest['evidence_id'] != 'R113' or manifest['profile'] != PROFILE
            or manifest['target_sha256'] != hashlib.sha256(target).hexdigest()
            or manifest['probe'] != 'probes/VC7EventQueueDependencies.cpp'):
        raise ValueError('R113 pinned target or profile differs')
    probe = ROOT / manifest['probe']
    if hashlib.sha256(probe.read_bytes()).hexdigest() != manifest['probe_sha256']:
        raise ValueError('R113 natural source probe differs')
    for filename, digest in manifest['vendor_headers'].items():
        if hashlib.sha256((ROOT / '.tools/msvc710/Vc7/include' / filename).read_bytes()).hexdigest() != digest:
            raise ValueError('R113 vendor header differs')
    verify_graph(manifest)
    functions = {r['address']: r for r in record.rows('functions.csv')}
    origins = {r['address']: r for r in record.rows('function-origins.csv')}
    # Archive evidence owns the CRT boundaries, including their embedded tables.
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-runtime-origins.py'],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('complete independent CRT boundary evidence failed: ' + result.stderr[-1000:])
    scratch = ROOT / 'build/origin-event-queue-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        obj = Path(temporary) / 'VC7EventQueueDependencies.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(probe), str(obj), *PROFILE],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('R113 pinned VC7 cold build failed: ' + result.stdout[-1000:])
        data = obj.read_bytes()
        definitions = {}
        wanted = {r['coff_symbol'] for r in manifest['nodes']}
        wanted.update(s for r in manifest['nodes'] for s in r.get('shape_symbols', []))
        for symbol in wanted:
            size = record.complete_aux_section_size(data, symbol, comparison.coff_name)
            definitions[symbol] = comparison.object_function(obj, symbol, size)
        for row in manifest['nodes']:
            key, address = row['address'], int(row['address'], 16)
            kind = 'library' if key in LIBRARY else ('authored' if key in GAME else 'anchor')
            check_ledger(row, functions, origins, args.evidence_only, kind)
            actual = comparison.pe_bytes_at(target, address, row['size'])
            source, relocations = definitions[row['coff_symbol']]
            if (len(source) != row['size'] or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('complete queue source/target body differs: ' + key)
            if record.compare_complete_body(source, relocations, actual, address, row['relocation_bindings'], comparison, sdk):
                raise ValueError('queue source graph contains an unexpected indirect call')
            for symbol in row.get('shape_symbols', []):
                control, fields = definitions[symbol]
                masked = {i for b in fields for i in range(b['offset'], b['offset'] + 4)}
                if len(control) != row['size'] or any(control[i] != actual[i] for i in range(len(actual)) if i not in masked):
                    raise ValueError('whole queue source control differs')
        # These are external snapshots, not new source-typed or reconciled bodies.
        for row in manifest['boundaries']:
            check_ledger(row, functions, origins, args.evidence_only, 'anchor')
            actual = comparison.pe_bytes_at(target, int(row['address'], 16), row['size'])
            if hashlib.sha256(actual).hexdigest() != row['body_sha256']:
                raise ValueError('external boundary whole recorded bytes differ')
        for row in manifest['strings']:
            expected = row['value'].encode(row['encoding']) + b'\0'
            if (len(expected) != row['size'] or hashlib.sha256(expected).hexdigest() != row['sha256']
                    or comparison.pe_bytes_at(target, int(row['address'], 16), row['size']) != expected):
                raise ValueError('whole game/vendor literal differs')
            if row['address'] in ('0x00657B34', '0x006577E0'):
                symbol = next(b['symbol'] for n in manifest['nodes'] for b in n['relocation_bindings']
                              if b['type'] == 'DIR32' and b['target_address'] == row['address'])
                entry = next(e for e in coff.parse_symbols(data, comparison.coff_name)[1] if e['symbol'] == symbol and e['section'] > 0)
                raw, _ = coff.readonly_section(data, entry['section'], comparison.coff_name)
                if raw != expected:
                    raise ValueError('vendor literal source does not cover its whole COMDAT')
    evidence = {r['address']: r for r in record.rows('authored-origin-evidence.csv')}
    switches = record.rows('authored-origin-direct-switches.csv')
    if args.evidence_only:
        switches = [s for s in switches if s['address'] != '0x00602A60'] + manifest['direct_switches']
    elif [s for s in switches if s['address'] == '0x00602A60'] != manifest['direct_switches']:
        raise ValueError('game main loop switch ledger differs')
    imports = imports_module.pe_imports(target, comparison)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded = {}
    for row in manifest['contexts']:
        key, address = row['address'], int(row['address'], 16)
        check_ledger(row, functions, origins, args.evidence_only, 'authored' if row['accepted'] else 'anchor')
        code = comparison.pe_bytes_at(target, address, row['size'])
        cfg = list(authored.verify_body(code, address, [], lambda a, n: comparison.pe_bytes_at(target, a, n),
                                       [s for s in switches if s['address'] == key]))
        if hashlib.sha256(code).hexdigest() != row['body_sha256'] or cfg != row['cfg']:
            raise ValueError('complete game context hash/CFG differs')
        decoded[key] = list(decoder.disasm(code, address))
        if lifetime.body_facts(decoded[key]) != row['body_facts']:
            raise ValueError('game context calls/returns/fields differ')
        if row['origin'] == 'authored' and not row['accepted'] and not authored.role_matches(functions[key], row['role']):
            raise ValueError('independent game context role differs')
        indirect = [i for i in decoded[key] if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
        if [(f'0x{i.address:08X}', i.op_str) for i in indirect] != [(r['site'], r['operand']) for r in row['indirect_calls']]:
            raise ValueError('game context indirect calls differ')
        for instruction, call in zip(indirect, row['indirect_calls']):
            if 'iat_slot' in call:
                op, slot = instruction.operands[0], int(call['iat_slot'], 16)
                if (op.type != X86_OP_MEM or op.mem.base or op.mem.index or op.mem.disp != slot
                        or imports.get(slot) != (call['dll'], call['symbol'])):
                    raise ValueError('game context import lacks raw PE identity')
        by_site = {f'0x{i.address:08X}': i for i in decoded[key]}
        for witness in row['instruction_witnesses']:
            instruction = by_site[witness['site']]
            if (instruction.mnemonic, instruction.op_str) != (witness['mnemonic'], witness['operands']):
                raise ValueError('game field, literal or policy witness differs')
        if row['accepted'] and not args.evidence_only:
            body = evidence[key]
            if (body['evidence_id'] != 'R113' or body['body_sha256'] != row['body_sha256']
                    or body['inferred_role'] != row['role'] or not authored.role_matches(functions[key], row['role'])
                    or [int(body['return_count']), int(body['internal_branch_count'])] != cfg
                    or body['external_branch_count'] != '0'):
                raise ValueError('R113 accepted game evidence differs')
    print('R113 origins OK: five library helpers / 153 bytes and two authored policies / 3083 bytes; '
          '65 complete cold source bodies / 4002 bytes / 150 typed fields, 65 whole shape controls, '
          'nine external snapshots, nine game contexts / 5063 bytes, 234 witnesses and a complete 60-byte scene table; '
          'unknown external bodies retain their origins; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
