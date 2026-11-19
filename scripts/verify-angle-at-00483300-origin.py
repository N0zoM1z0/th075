#!/usr/bin/env python3
"""Verify the authored game angle wrapper and its VC7.1 inline atan2f worker."""
from __future__ import annotations
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess
import tempfile
import tomllib
from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_RET, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / 'config/angle-at-00483300-origin-evidence.json'


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def rows(name: str) -> dict[str, dict[str, str]]:
    with (ROOT / 'config' / name).open(newline='') as f:
        return {r['address']: r for r in csv.DictReader(f)}


def module(name: str, filename: str):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


def direct_calls(body: bytes, address: int, target: int) -> list[int]:
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    return [i.address for i in decoder.disasm(body, address)
            if i.group(CS_GRP_CALL) and i.operands
            and i.operands[0].type == X86_OP_IMM and i.operands[0].imm == target]


def compare_object_function(cmp, body: bytes, relocations: list[dict], address: int,
                            size: int, expected_relocation: dict) -> None:
    target = cmp.pe_bytes_at(cmp.verified_target(), address, size)
    if len(body) != size or len(target) != size:
        raise ValueError(f'whole function extent differs at 0x{address:08X}')
    actual = [{'offset': r['offset'], 'type': r['type'], 'symbol': r['symbol']}
              for r in relocations]
    expected = [{key: expected_relocation[key] for key in ('offset', 'type', 'symbol')}]
    if actual != expected:
        raise ValueError(f'actual COFF relocation differs at 0x{address:08X}: {actual}')
    mask = set(range(expected_relocation['offset'], expected_relocation['offset'] + 4))
    if any(body[i] != target[i] for i in range(size) if i not in mask):
        raise ValueError(f'non-relocation source bytes differ at 0x{address:08X}')


def main() -> int:
    m = json.loads(MANIFEST.read_text())
    cmp = module('angle_cmp', 'compare-coff-function.py')
    target = cmp.verified_target()
    if digest(target) != m['target_sha256']:
        raise ValueError('pinned TH075 target identity differs')

    source = ROOT / m['source']['path']
    header = ROOT / m['header']['path']
    if digest(source.read_bytes()) != m['source']['sha256']:
        raise ValueError('natural C++ source changed without updating its evidence')
    if digest(header.read_bytes()) != m['header']['sha256']:
        raise ValueError('VC7.1 math.h changed without updating its evidence')
    header_text = header.read_text(errors='replace').replace('\r\n', '\n')
    if m['header']['inline_definition'] not in header_text:
        raise ValueError('the exact VC7.1 inline atan2f definition is absent')

    functions = rows('functions.csv')
    origins = rows('function-origins.csv')
    authored = rows('authored-origin-evidence.csv')
    matches = rows('matches.csv')
    outer = m['outer']; worker = m['worker']
    outer_row = functions[outer['address']]; outer_origin = origins[outer['address']]
    if (outer_row['proposed_name'] != outer['name'] or outer_row['module'] != 'MathLookup'
            or outer_row['status'] != 'matching' or outer_row['match_percent'] != '100.00'
            or outer_row['calling_convention'] != 'cdecl'
            or outer_row['signature'] != 'float __cdecl AngleAt00483300(float y, float x)'
            or outer_row['source_file'] != m['source']['path'] or outer_row['owner'] != 'authored'
            or outer_origin != {'address': outer['address'], 'origin': 'authored',
                                'subsystem': 'MathLookup', 'disposition': 'authored',
                                'confidence': 'complete-shared-game-angle-wrapper-with-16-authored-callers',
                                'evidence_id': m['evidence_id_outer']}):
        raise ValueError('canonical authored angle-wrapper record differs')
    a = authored.get(outer['address'])
    if (not a or int(a['size']) != outer['size'] or a['body_sha256'] != outer['body_sha256']
            or a['inferred_role'] != outer['name'] or int(a['return_count']) != outer['return_count']
            or int(a['internal_branch_count']) != outer['internal_branch_count']
            or a['evidence_id'] != m['evidence_id_outer']):
        raise ValueError('complete authored body/CFG evidence differs')
    match = matches.get(outer['address'])
    if (not match or match['name'] != outer['name'] or int(match['size']) != outer['size']
            or match['status'] != 'matching' or match['match_percent'] != '100.00'
            or match['unit'] != 'math-angle-at-00483300'):
        raise ValueError('complete exact-match ledger record differs')

    worker_row = functions[worker['address']]; worker_origin = origins[worker['address']]
    if (worker_row['proposed_name'] != '_atan2f' or worker_row['module'] != 'VC71CRT'
            or worker_row['status'] != 'excluded' or worker_row['match_percent'] != '0.00'
            or worker_row['owner'] != 'library' or worker_row['source_file']
            or worker_origin != {'address': worker['address'], 'origin': 'library',
                                 'subsystem': 'VC71CRT', 'disposition': 'exclude',
                                 'confidence': 'complete-vc71-math-h-inline-atan2f-worker',
                                 'evidence_id': m['evidence_id_worker']}):
        raise ValueError('header-inline worker must remain a separately excluded library function')
    if worker['address'] in authored or worker['address'] in matches:
        raise ValueError('library inline worker gained authored or exact-game credit')

    runtime = functions[m['runtime_callee']['address']]
    runtime_origin = origins[m['runtime_callee']['address']]
    if (runtime['module'] != 'VC71CRT' or runtime['owner'] != 'library'
            or runtime_origin['origin'] != 'library'
            or runtime_origin['evidence_id'] != m['runtime_callee']['evidence_id']):
        raise ValueError('the underlying _atan2 runtime callee lost its independent library owner')

    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    outer_bytes = cmp.pe_bytes_at(target, int(outer['address'], 16), outer['size'])
    worker_bytes = cmp.pe_bytes_at(target, int(worker['address'], 16), worker['size'])
    if digest(outer_bytes) != outer['body_sha256'] or digest(worker_bytes) != worker['body_sha256']:
        raise ValueError('complete original wrapper/worker bytes differ')
    outer_calls = direct_calls(outer_bytes, int(outer['address'], 16), int(worker['address'], 16))
    worker_calls = direct_calls(worker_bytes, int(worker['address'], 16), int(m['runtime_callee']['address'], 16))
    if len(outer_calls) != 1 or len(worker_calls) != 1:
        raise ValueError('the two original call edges are not complete and direct')

    caller_functions = rows('functions.csv')
    caller_origins = rows('function-origins.csv')
    caller_total = 0
    if len(m['callers']) != m['call_counts']['unique_authored_callers']:
        raise ValueError('authored caller set is incomplete')
    for caller in m['callers']:
        address = caller['address']; f = caller_functions[address]; o = caller_origins[address]
        if (int(f['size']) != caller['size'] or o['origin'] != 'authored'
                or o['evidence_id'] != caller['origin_evidence_id']):
            raise ValueError('an angle-wrapper caller is not a complete reviewed authored game function')
        body = cmp.pe_bytes_at(target, int(address, 16), caller['size'])
        count = len(direct_calls(body, int(address, 16), int(outer['address'], 16)))
        if count != caller['call_count']:
            raise ValueError(f'angle call-site count changed in {address}')
        caller_total += count
    if caller_total != m['call_counts']['direct_call_sites']:
        raise ValueError('whole authored call-site total differs')

    units = tomllib.loads((ROOT / 'config/match-units.toml').read_text())['units']
    unit = units['math-angle-at-00483300']
    if (unit['source'] != m['source']['path'] or unit['symbol'] != '?AngleAt00483300@@YAMMM@Z'
            or unit['target_address'] != int(outer['address'], 16) or unit['size'] != outer['size']
            or unit['relocations'] != [{'offset': outer['relocation']['offset'],
                                       'type': outer['relocation']['type'],
                                       'symbol': outer['relocation']['symbol'],
                                       'target': int(outer['relocation']['target_address'], 16)}]):
        raise ValueError('single-function exact replay unit differs')

    with tempfile.TemporaryDirectory(prefix='angle-at-00483300-', dir=ROOT / 'build') as tmp:
        obj = Path(tmp) / 'AngleAtan2.obj'
        run = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(source), str(obj),
                              *m['profile']], cwd=ROOT, capture_output=True, text=True)
        if run.returncode:
            raise ValueError('natural VC7.1 source compile failed: ' + (run.stdout + run.stderr)[-1200:])
        outer_body, outer_relocs = cmp.object_function(obj, '?AngleAt00483300@@YAMMM@Z')
        worker_body, worker_relocs = cmp.object_function(obj, '_atan2f')
        compare_object_function(cmp, outer_body, outer_relocs, int(outer['address'], 16),
                                outer['size'], outer['relocation'])
        compare_object_function(cmp, worker_body, worker_relocs, int(worker['address'], 16),
                                worker['size'], worker['relocation'])

    print('R269/R270 angle origin OK: one complete 21-byte authored game wrapper; '
          '16 authored callers / 211 original direct calls; one 37-byte VC7.1 math.h '
          'inline atan2f worker separately excluded as VC71CRT; underlying _atan2 '
          'callee independently library-owned; both natural C++/header bodies and '
          'all original call edges verified; no CRT/library code double credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
