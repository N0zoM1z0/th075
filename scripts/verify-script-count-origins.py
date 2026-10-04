#!/usr/bin/env python3
"""Recheck complete script count policy, its producers and independent game consumers."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
KEY = '0x0045DD00'
CONFIDENCE = 'complete-script-map-producer-and-game-consumer-policy'
MANIFEST_SHA256 = 'e2c2c76072de2d0190849ce4604b50c73402a899aa4228458a64510c9bb2c789'
ANCHORS = {'0x00420440': (130, 'R076'), '0x00420530': (53, 'R076'),
           '0x00420570': (55, 'R076'), '0x00420880': (2301, 'R070'),
           '0x0045CE10': (1926, 'R065'), '0x0045D810': (1264, 'R045')}
SITES = {'0x0045CE10': ['0x0045CE38', '0x0045D46E', '0x0045D571'],
         '0x0045D810': ['0x0045D877', '0x0045D95A', '0x0045DA19', '0x0045DA5F',
                        '0x0045DAB7', '0x0045DB9A', '0x0045DC59', '0x0045DC9F']}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


PRIOR = module('script_count_prior', 'verify-nested-deque-size-origins.py')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest():
    return json.loads((ROOT / 'config/script-count-origin-evidence.json').read_text())


def operations(window):
    return [(r['mnemonic'], r['operands']) for r in window]


def verify_plan(m):
    if (m['evidence_id'] != 'R152' or len(m['functions']) != 1
            or m['retained_manifest'] != 'nested-deque-size-origin-evidence.json'
            or m['retained_verifier'] != 'verify-nested-deque-size-origins.py'
            or len(m['anchors']) != 6 or len(m['instruction_windows']) != 15):
        raise ValueError('script policy loses its bounded whole independent context')
    r = m['functions'][0]
    if (r['address'] != KEY or r['size'] != 66 or r['span_end'] != '0x0045DD41'
            or r['decision'] != 'authored' or r['source_file']
            or r['inferred_role'] != 'FighterScript::CountPatternEntries'
            or r['return_count'] != 1 or r['internal_branch_count'] != 2
            or r['alignment'] != dict(address='0x0045DD42', size=14, value=204)
            or r['retained_source']['address'] != KEY or r['retained_source']['size'] != 66
            or r['retained_source']['symbol'] != '?Count@NestedSizeObservation@@QAEFF@Z'):
        raise ValueError('script count substitutes a prefix, source credit or different operation')
    expected = [('push', 'ebp'), ('mov', 'ebp, esp'), ('push', 'ecx'),
                ('mov', 'dword ptr [ebp - 4], ecx'), ('movsx', 'eax, word ptr [ebp + 8]'),
                ('mov', 'ecx, dword ptr [ebp - 4]'), ('movsx', 'edx, word ptr [ecx + eax*2]'),
                ('test', 'edx, edx'), ('jge', '0x45dd1b'), ('xor', 'ax, ax'), ('jmp', '0x45dd3c'),
                ('movsx', 'eax, word ptr [ebp + 8]'), ('mov', 'ecx, dword ptr [ebp - 4]'),
                ('movsx', 'edx, word ptr [ecx + eax*2]'), ('push', 'edx'),
                ('mov', 'ecx, dword ptr [ebp - 4]'), ('add', 'ecx, 0x7d0'),
                ('call', '0x421570'), ('mov', 'ecx, eax'), ('call', '0x45dd50'),
                ('mov', 'esp, ebp'), ('pop', 'ebp'), ('ret', '4')]
    if operations(r['instructions']) != expected:
        raise ValueError('script count loses signed map/missing-zero/returned-inner policy or real ABI')
    if m['observed_policy'] != dict(index_width=2, index_signed=True, map_slots=1000,
                                    map_missing=-1, container_offset=2000,
                                    fighter_receiver_offset=1812, missing_count=0, return_width=2):
        raise ValueError('script policy invents widths, bounds or a different map domain')
    if {r['address']: (r['size'], r['evidence']['evidence_id']) for r in m['anchors']} != ANCHORS:
        raise ValueError('script policy changes an independent original authored owner')
    windows = m['instruction_windows']
    initial = [w for w in windows if w['kind'] == 'sentinel-initializer']
    if len(initial) != 1 or initial[0]['owner'] != '0x00420440':
        raise ValueError('script policy lacks its independent initializer')
    op = operations(initial[0]['instructions'])
    if (len(op) != 11 or op[0] != ('mov', 'dword ptr [ebp - 0x10], 0')
            or ('cmp', 'dword ptr [ebp - 0x10], 0x3e8') not in op
            or op[-2:] != [('mov', 'word ptr [edx + ecx*2], 0xffff'), ('jmp', '0x42048a')]):
        raise ValueError('script policy loses its actual 1000 signed-short missing entries')
    producer = [w for w in windows if w['kind'] == 'numeric-label-map-producer']
    if len(producer) != 3 or any(w['owner'] != '0x00420880' for w in producer):
        raise ValueError('script count lacks an independently authored full map producer')
    p0, p1, p2 = [operations(w['instructions']) for w in producer]
    if (len(p0) != 10 or ('cmp', 'eax, 0x30') not in p0 or ('cmp', 'edx, 0x39') not in p0
            or len(p1) != 12 or p1[-5:] != [('call', '0x421550'), ('sub', 'eax, 1'),
                ('movsx', 'ecx, word ptr [ebp - 0x14]'), ('mov', 'edx, dword ptr [ebp - 0x7c]'),
                ('mov', 'word ptr [edx + ecx*2], ax')]
            or len(p2) != 8 or p2[1] != ('imul', 'ecx, ecx, 0xa')
            or p2[5:7] != [('lea', 'ecx, [ecx + eax - 0x30]'), ('mov', 'word ptr [ebp - 0x14], cx')]):
        raise ValueError('script count loses decimal-label-to-actual-outer-index writes')
    observed = {key: [] for key in SITES}
    for w in windows:
        if w['kind'] != 'game-count-consumer':
            continue
        op = operations(w['instructions'])
        if (w['owner'] not in SITES or len(op) != 9 or op[1][0] != 'mov' or 'word ptr' not in op[1][1]
                or op[1][1].split(',')[0] not in ('ax', 'cx', 'dx')
                or op[2] != ('push', 'e' + op[1][1].split(',')[0])
                or op[4:6] != [('add', 'ecx, 0x714'), ('call', '0x45dd00')]
                or op[6][0] != 'movsx' or not op[6][1].endswith(', ax')
                or op[7][0] != 'cmp' or op[8][0] not in ('jge', 'jne')):
            raise ValueError('script count loses actual game receiver/short argument/AX loop-bound use')
        observed[w['owner']].append(w['instructions'][5]['address'])
    if observed != SITES:
        raise ValueError('script count omits or substitutes an actual game call site')


def check_ledger(r, function, origin, evidence_only=False):
    if (int(function['size']) != r['size'] or function['span_end'] != r['span_end']
            or function['source_file'] or function['signature'] or function['calling_convention']
            or function['match_percent'] != '0.00'):
        raise ValueError('script count changes its own extent or grants source/ABI/exact')
    if not evidence_only and (origin['origin'] != 'authored' or origin['disposition'] != 'authored'
            or origin['subsystem'] != 'FighterScript' or origin['evidence_id'] != 'R152'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'authored'
            or function['module'] != 'FighterScript' or function['status'] != 'unclassified'
            or function['proposed_name'] != r['inferred_role']):
        raise ValueError('script count canonical policy acceptance differs')


def check_authored_record(r, rows):
    expected = dict(address=KEY, size='66', body_sha256=r['body_sha256'], inferred_role=r['inferred_role'],
                    return_count='1', internal_branch_count='2', external_branch_count='0', evidence_id='R152')
    if [row for row in rows if row['address'] == KEY] != [expected]:
        raise ValueError('script count loses its unique complete authored extent/CFG record')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    m = manifest()
    verify_plan(m)
    if digest((ROOT / 'config/script-count-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('reviewed full script policy metadata differs')
    comparison = module('script_count_target', 'compare-coff-function.py')
    authored = module('script_count_cfg', 'verify-authored-origins.py')
    target = comparison.verified_target()
    if digest(target) != m['target_sha256']:
        raise ValueError('script policy uses a different target')
    functions = {r['address']: r for r in authored.rows('functions.csv')}
    origins = {r['address']: r for r in authored.rows('function-origins.csv')}
    r = m['functions'][0]
    check_ledger(r, functions[KEY], origins[KEY], args.evidence_only)
    if not args.evidence_only:
        check_authored_record(r, authored.rows('authored-origin-evidence.csv'))
    retained = json.loads((ROOT / 'config' / m['retained_manifest']).read_text())
    if r['retained_source'] not in retained['code']:
        raise ValueError('script policy loses its whole independent cold synthetic control')
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded = {}
    for owner in [r] + m['anchors']:
        key, a, n = owner['address'], int(owner['address'], 16), owner['size']
        raw = comparison.pe_bytes_at(target, a, n)
        if digest(raw) != owner['body_sha256'] or int(functions[key]['size']) != n:
            raise ValueError('whole script owner extent/body differs')
        switches = owner.get('switches', [])
        directs = owner.get('direct_switches', [])
        counts = authored.verify_body(raw, a, switches, lambda p, size: comparison.pe_bytes_at(target, p, size), directs)
        if key == KEY:
            if counts != (1, 2):
                raise ValueError('script count complete control flow differs')
        else:
            evidence = owner['evidence']
            if (evidence not in authored.rows('authored-origin-evidence.csv')
                    or origins[key]['origin'] != 'authored' or origins[key]['evidence_id'] != evidence['evidence_id']
                    or not authored.role_matches(functions[key], evidence['inferred_role'])
                    or switches != [s for s in authored.rows('authored-origin-switches.csv') if s['address'] == key]
                    or directs != [s for s in authored.rows('authored-origin-direct-switches.csv') if s['address'] == key]
                    or counts != (int(evidence['return_count']), int(evidence['internal_branch_count']))):
                raise ValueError('script policy rewrites an independent authored body/switch proof')
        decoded[key] = [dict(address=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str)
                        for i in decoder.disasm(raw, a)]
    if decoded[KEY] != r['instructions']:
        raise ValueError('script count instruction inventory differs')
    padding = r['alignment']
    if comparison.pe_bytes_at(target, int(padding['address'], 16), padding['size']) != bytes([padding['value']]) * padding['size']:
        raise ValueError('script count alignment or next-owner boundary differs')
    for w in m['instruction_windows']:
        ins = decoded[w['owner']]
        start = next(i for i, row in enumerate(ins) if row['address'] == w['instructions'][0]['address'])
        if ins[start:start + len(w['instructions'])] != w['instructions']:
            raise ValueError('script policy window is not actual uninterrupted full-owner context')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts' / m['retained_verifier'])],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise ValueError('complete independent R150 cold provenance failed: ' + result.stderr[-1000:])
    print('R152 origins OK: one complete authored script count / 66 bytes; six independent whole authored '
          'owners / 5729 bytes with original switch/CFG proofs; actual 1000-slot missing-map initializer, '
          'decimal-label producer and eleven game short-count consumers; complete retained R150 cold '
          'code/data/EH and synthetic count model; original types/full layouts/input safety unknown; '
          'all prior owners/extents preserved; no source/mapping/private ABI/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, StopIteration, ValueError, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
