#!/usr/bin/env python3
"""Cold-check R112 postfix overloads and complete independent game policies."""
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
POSTFIX = {'0x00414970': '0x00415580', '0x00414A20': '0x00415690',
           '0x00414AD0': '0x004157A0', '0x0041DF90': '0x0041ECA0',
           '0x0041E020': '0x0041EE00', '0x00423F90': '0x004244A0'}
POLICIES = {'0x00455800': 'BattleInput::MatchSequenceAt00455800',
            '0x00423B40': 'EventQueue::RunWorkerAt00423B40'}
CALLBACK = {'parent_address': '0x004239F0', 'site': '0x00423A49',
            'target': '0x00423B40', 'iat_site': '0x00423A52', 'iat_slot': '0x0065713C'}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def verify_graph(manifest):
    posts, prefixes, contexts = manifest['postfix'], manifest['prefix'], manifest['contexts']
    if ({r['address']: r['callee_address'] for r in posts} != POSTFIX or len(posts) != 6
            or {r['address'] for r in prefixes} != set(POSTFIX.values()) or len(prefixes) != 6
            or len(contexts) != 22 or len({r['address'] for r in contexts}) != 22
            or sum(r['size'] for r in contexts) != 6407
            or {r['address']: r['role'] for r in contexts if r['accepted']} != POLICIES
            or sum(r['size'] for r in contexts if r['accepted']) != 968
            or sum(len(r['instruction_witnesses']) for r in contexts) != 112
            or len(manifest['parent_edges']) != 41):
        raise ValueError('R112 complete evidence cohort differs')
    for row in posts:
        bindings = row['relocation_bindings']
        if (row['size'] != 54 or len(row['shape_symbols']) != 26
                or len(row['matching_symbols']) != 13 or len(bindings) != 1
                or not row['coff_symbol'].startswith('??Eiterator@')
                or not row['coff_symbol'].endswith('QAE?AV012@H@Z')
                or row['coff_symbol'] not in row['matching_symbols']
                or (bindings[0]['offset'], bindings[0]['type'], bindings[0]['addend'],
                    bindings[0]['target_address']) != (27, 'REL32', 0, POSTFIX[row['address']])
                or not bindings[0]['symbol'].startswith('??Eiterator@')
                or not bindings[0]['symbol'].endswith('QAEAAV012@XZ')):
            raise ValueError('postfix increment lacks its actual complete prefix callee')
    if manifest['callback'] != CALLBACK:
        raise ValueError('worker callback or CreateThread binding differs')
    by_address = {r['address']: r for r in contexts}
    for key in ('0x004724B0', '0x0043B0B0', '0x00445A00', '0x00423C60'):
        if by_address[key]['origin'] != 'authored' or by_address[key]['accepted']:
            raise ValueError('policy lacks its independently authored game control')
    edges = manifest['parent_edges']
    for parent, child in [('0x004724B0', '0x00455800'), ('0x0043B0B0', '0x00423C60'),
                          ('0x00445A00', '0x00423C60')]:
        if not any(e['parent_address'] == parent and e['target'] == child for e in edges):
            raise ValueError('policy lacks its independently authored game control')


def check_ledger(row, functions, origins, evidence_only, kind):
    key, size = row['address'], row['size']
    function, origin = functions[key], origins[key]
    address = int(key, 16)
    if (int(function['size']) != size or function['span_end'] != row['span_end']
            or int(row['span_end'], 16) != address + size - 1
            or any(address < int(k, 16) < address + size for k in functions)):
        raise ValueError('R112 complete ledger extent differs: ' + key)
    if kind in ('library', 'authored') and not evidence_only:
        if (origin['origin'] != kind or origin['evidence_id'] != 'R112'
                or origin['disposition'] != ('exclude' if kind == 'library' else 'authored')
                or function['owner'] != kind or function['source_file']
                or function['match_percent'] != '0.00'
                or function['status'] != ('excluded' if kind == 'library' else 'unclassified')):
            raise ValueError('R112 acceptance grants incorrect origin/source/exact credit')
    elif kind == 'anchor' and row['origin'] != 'unknown':
        if (origin['origin'] != row['origin'] or origin['evidence_id'] != row['origin_evidence']
                or function['owner'] != row['origin']):
            raise ValueError('R112 independent context ownership differs')


def matching_alternatives(actual, prefix, definitions):
    """Resolve the overload with the full actual callee, not its postfix shape."""
    shapes, matches = [], []
    for symbol, (source, relocations) in definitions.items():
        if len(source) != 54 or len(relocations) != 1:
            continue
        call = relocations[0]
        if call['offset'] != 27 or call['type'] != 'REL32' or call['addend']:
            continue
        if source[:27] != actual[:27] or source[31:] != actual[31:]:
            continue
        shapes.append(symbol)
        callee = definitions.get(call['symbol'])
        if callee is not None and callee == (prefix, []):
            matches.append(symbol)
    return sorted(shapes), sorted(matches)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    comparison = module('postfix_target', 'compare-coff-function.py')
    record = module('postfix_comdat', 'verify-vendor-record-origins.py')
    sdk = module('postfix_cfg', 'verify-sdk-origins.py')
    authored = module('postfix_authored', 'verify-authored-origins.py')
    context = module('postfix_context', 'verify-game-context-origins.py')
    lifetime = module('postfix_facts', 'verify-game-lifetime-origins.py')
    imports_module = module('postfix_imports', 'verify-import-origins.py')
    coff = module('postfix_symbols', 'coff_data.py')
    target = comparison.verified_target()
    manifest = json.loads((ROOT / 'config/deque-postfix-context-origins.json').read_text())
    if (manifest['evidence_id'] != 'R112' or manifest['profile'] != PROFILE
            or manifest['target_sha256'] != hashlib.sha256(target).hexdigest()
            or manifest['probe'] != 'probes/VC7DequePostfix.cpp'):
        raise ValueError('R112 pinned target or reproducibility profile differs')
    probe = ROOT / manifest['probe']
    if hashlib.sha256(probe.read_bytes()).hexdigest() != manifest['probe_sha256']:
        raise ValueError('R112 natural source probe differs')
    for filename, digest in manifest['vendor_headers'].items():
        if hashlib.sha256((ROOT / '.tools/msvc710/Vc7/include' / filename).read_bytes()).hexdigest() != digest:
            raise ValueError('R112 pinned vendor header differs')
    verify_graph(manifest)
    functions = {r['address']: r for r in record.rows('functions.csv')}
    origins = {r['address']: r for r in record.rows('function-origins.csv')}
    old = {r['address']: r for r in record.rows('vendor-deque-algorithm-origins.csv')}
    peers = {r['address']: r for r in json.loads((ROOT / 'config/vendor-peer-origin-evidence.json').read_text())['functions']}
    # Rebuild the independent algorithm parents; rechecking names alone proves nothing.
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), 'scripts/verify-vendor-deque-algorithm-origins.py'],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('R085 complete typed prefix anchors failed: ' + result.stderr[-1000:])
    prefixes = {}
    for row in manifest['prefix']:
        key = row['address']
        anchor_row = dict(row, origin='library')
        check_ledger(anchor_row, functions, origins, False, 'anchor')
        witness = row['independent_witness']
        if witness['kind'] == 'R085':
            if witness['record'] != old[key]:
                raise ValueError('independent R085 complete source witness differs')
        elif witness['kind'] == 'R106':
            if (witness['record'] != peers[key] or witness['anchor_record'] != old['0x00415580']
                    or peers[key]['anchor'] != '0x00415580' or peers[key]['direct_calls']):
                raise ValueError('independent R106 whole prefix witness differs')
        else:
            raise ValueError('prefix lacks independent source ownership')
        code = comparison.pe_bytes_at(target, int(key, 16), row['size'])
        if row['size'] != 29 or hashlib.sha256(code).hexdigest() != row['body_sha256']:
            raise ValueError('complete prefix bytes differ')
        prefixes[key] = code
    scratch = ROOT / 'build/origin-deque-postfix-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        object_path = Path(temporary) / 'VC7DequePostfix.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(probe), str(object_path), *PROFILE],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('R112 pinned VC7 cold build failed: ' + result.stdout[-1000:])
        data, definitions = object_path.read_bytes(), {}
        for entry in coff.parse_symbols(data, comparison.coff_name)[1]:
            symbol = entry['symbol']
            if entry['section'] > 0 and entry['storage'] == 2 and entry['type'] == 0x20 and symbol.startswith(('??Eiterator@', '??Fiterator@')):
                size = record.complete_aux_section_size(data, symbol, comparison.coff_name)
                definitions[symbol] = comparison.object_function(object_path, symbol, size)
        if Counter((s[:3], len(body)) for s, (body, _) in definitions.items()) != {
                ('??E', 54): 13, ('??F', 54): 13, ('??E', 29): 13, ('??F', 29): 13}:
            raise ValueError('cold probe lacks all 52 complete overload controls')
        for row in manifest['postfix']:
            check_ledger(row, functions, origins, args.evidence_only, 'library')
            key, address = row['address'], int(row['address'], 16)
            actual = comparison.pe_bytes_at(target, address, row['size'])
            shapes, matches = matching_alternatives(actual, prefixes[row['callee_address']], definitions)
            if shapes != row['shape_symbols'] or matches != row['matching_symbols']:
                raise ValueError('postfix overload alternatives lack their actual whole callee')
            source, relocations = definitions[row['coff_symbol']]
            if (hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('whole postfix source or target hash differs')
            for symbol in matches:
                source, relocations = definitions[symbol]
                bindings = [{k: relocations[0][k] for k in ('offset', 'type', 'symbol', 'addend')}]
                bindings[0]['target_address'] = row['callee_address']
                if record.compare_complete_body(source, relocations, actual, address, bindings, comparison, sdk):
                    raise ValueError('postfix contains an unexpected indirect call')
            if [dict({k: r[k] for k in ('offset', 'type', 'symbol', 'addend')}, target_address=row['callee_address']) for r in definitions[row['coff_symbol']][1]] != row['relocation_bindings']:
                raise ValueError('canonical postfix relocation differs')
    switches = record.rows('authored-origin-switches.csv')
    directs = record.rows('authored-origin-direct-switches.csv')
    if args.evidence_only:
        switches = [r for r in switches if r['address'] not in POLICIES] + manifest['switches']
    elif [r for r in switches if r['address'] in POLICIES] != manifest['switches']:
        raise ValueError('R112 complete switch ledger differs')
    evidence = {r['address']: r for r in record.rows('authored-origin-evidence.csv')}
    imports = imports_module.pe_imports(target, comparison)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded = {}
    for row in manifest['contexts']:
        key, address = row['address'], int(row['address'], 16)
        check_ledger(row, functions, origins, args.evidence_only, 'authored' if row['accepted'] else 'anchor')
        code = comparison.pe_bytes_at(target, address, row['size'])
        if hashlib.sha256(code).hexdigest() != row['body_sha256']:
            raise ValueError('complete game context hash differs: ' + key)
        if row['accepted'] or row['origin'] == 'authored':
            cfg = list(authored.verify_body(code, address, [s for s in switches if s['address'] == key],
                        lambda a, n: comparison.pe_bytes_at(target, a, n), [s for s in directs if s['address'] == key]))
        else:
            cfg = context.verify_bounded_context(code, address, row['external_tails'])
        if cfg != row['cfg']:
            raise ValueError('complete game context control flow differs: ' + key)
        decoded[key] = list(decoder.disasm(code, address))
        if (not row['accepted'] and row['origin'] == 'authored'
                and not authored.role_matches(functions[key], row['role'])):
            raise ValueError('independent authored context role differs')
        if lifetime.body_facts(decoded[key]) != row['body_facts']:
            raise ValueError('game context calls, returns or fields differ')
        indirect = [i for i in decoded[key] if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
        if [(f'0x{i.address:08X}', i.op_str) for i in indirect] != [(r['site'], r['operand']) for r in row['indirect_calls']]:
            raise ValueError('game context indirect call differs')
        for instruction, call in zip(indirect, row['indirect_calls']):
            if 'iat_slot' in call:
                slot, op = int(call['iat_slot'], 16), instruction.operands[0]
                if (op.type != X86_OP_MEM or op.mem.base or op.mem.index or op.mem.disp != slot
                        or imports.get(slot) != (call['dll'], call['symbol'])):
                    raise ValueError('game context import lacks raw PE identity')
        by_site = {f'0x{i.address:08X}': i for i in decoded[key]}
        for witness in row['instruction_witnesses']:
            instruction = by_site[witness['site']]
            if (instruction.mnemonic, instruction.op_str) != (witness['mnemonic'], witness['operands']):
                raise ValueError('game policy field, literal or global differs')
        if row['accepted']:
            if any(c['target'] not in decoded and c['target'] not in POSTFIX
                   and c['target'] not in {r['address'] for r in manifest['contexts']}
                   for c in row['body_facts']['direct_calls']):
                raise ValueError('game policy callee lacks complete context')
            if not args.evidence_only:
                body = evidence[key]
                if (body['evidence_id'] != 'R112' or body['inferred_role'] != row['role']
                        or body['body_sha256'] != row['body_sha256']
                        or [int(body['return_count']), int(body['internal_branch_count'])] != row['cfg']
                        or body['external_branch_count'] != '0'
                        or not authored.role_matches(functions[key], row['role'])):
                    raise ValueError('accepted game policy body evidence differs')
    expected_edges = []
    for key, instructions in decoded.items():
        expected_edges.extend(dict(parent_address=key, site=c['site'], target=c['target'])
                              for c in lifetime.body_facts(instructions)['direct_calls']
                              if c['target'] in set(POSTFIX) | set(POLICIES) | {'0x00423C60'})
    if expected_edges != manifest['parent_edges']:
        raise ValueError('complete parent edges differ')
    cb = manifest['callback']
    by_site = {f'0x{i.address:08X}': i for i in decoded[cb['parent_address']]}
    push, call = by_site[cb['site']], by_site[cb['iat_site']]
    if (push.mnemonic != 'push' or push.operands[0].type != X86_OP_IMM
            or push.operands[0].imm != int(cb['target'], 16) or call.mnemonic != 'call'
            or call.operands[0].type != X86_OP_MEM or call.operands[0].mem.disp != int(cb['iat_slot'], 16)
            or imports[int(cb['iat_slot'], 16)] != ('KERNEL32.dll', 'CreateThread')):
        raise ValueError('worker callback lacks its raw CreateThread reference')
    print('R112 origins OK: six library postfix bodies / 324 bytes, two authored policies / 968 bytes; '
          '52 cold overload controls, six independently typed prefix callees, 22 complete contexts / 6407 bytes, '
          '41 parent edges, 112 policy witnesses and complete 108-byte switch data; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, ValueError, struct.error) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
